/* Smart Classroom Comfort Monitor - CSE 1106 Final Project (Option 1)
 *
 * Build on the Pi:   gcc -o monitor src/main.c -lpigpio
 * Run on the Pi:     sudo ./monitor          (run from the repo root so the data/ path works)
 * Change the range:  sudo ./monitor 70 80    (optional: lower and upper limit in F)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pigpio.h>

#define LED_PIN      17      // GPIO number (physical pin 11)
#define LOG_FILE     "data/temperature_log.csv"
#define STATUS_FILE  "status.txt"

int main(int argc, char *argv[]) {
    double low = 68.0, high = 76.0;    // acceptable range, inclusive, base parameters
    if (argc == 3) { low = atof(argv[1]); high = atof(argv[2]); }

    if (gpioInitialise() < 0) {
        fprintf(stderr, "Hardware initialization failed.\n");
        fprintf(stderr, "Hint: Did you run with 'sudo'? Check your connections and permissions.\n");
        return 1;
    }
    gpioSetMode(LED_PIN, PI_OUTPUT);
    printf("Acceptable range: %.1fF - %.1fF (inclusive)\n", low, high);

    char line[64], *end;
    double t, sum = 0;
    int count = 0;
    for (;;) {
        printf("Enter temperature in F (q to quit): ");
        if (!fgets(line, sizeof line, stdin) || line[0] == 'q') break;

        t = strtod(line, &end);
        if (end == line || (*end != '\n' && *end != '\0') || !isfinite(t)) {
            printf("Invalid input. Enter a number.\n");
            continue;
        }

        int warn = t < low || t > high;
        const char *status = warn ? "WARNING" : "NORMAL";
        gpioWrite(LED_PIN, warn);      // LED on = warning
        sum += t;
        count++;

        FILE *f = fopen(LOG_FILE, "a");
        if (f) {
            if (ftell(f) == 0) fprintf(f, "temperature_F,status\n");
            fprintf(f, "%.1f,%s\n", t, status);
            fclose(f);
        } else fprintf(stderr, "Warning: could not open %s\n", LOG_FILE);

        f = fopen(STATUS_FILE, "w");
        if (f) { fprintf(f, "%s\n", status); fclose(f); }

        printf("%.1fF -> %s | Warning LED %s | Average of %d: %.1fF\n",
               t, status, warn ? "ON" : "OFF", count, sum / count);
    }

    gpioWrite(LED_PIN, 0);
    gpioTerminate();
    return 0;
}
