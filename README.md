Option 1 — Smart Classroom Comfort Monitor

Project Description

Your team has been hired to develop a simple classroom monitoring system for a university
facilities department.
The department wants to monitor classroom temperatures and identify when conditions fall
outside an acceptable range.
Your task is to develop a Raspberry Pi–based application that processes temperature readings,
determines whether the classroom environment is acceptable, and provides a visible warning
when a temperature is outside the specified range.

Expected Product Functionality

• Allow the user to enter classroom temperature readings in Fahrenheit.

• Determine whether a temperature is within the acceptable range of 68°F–76°F, inclusive.

• Display an appropriate NORMAL or WARNING status.

• Calculate the average of the recorded temperatures.

• Save temperature readings and their statuses to a file.

• Use an LED connected to the Raspberry Pi to indicate a warning condition.

• Allow the acceptable temperature range to be changed according to a new client
requirement.

Example:

Temperature System Status Warning LED

72°F NORMAL OFF

79°F WARNING ON

65°F WARNING ON

Team Members:

1. Stephen Dinh
   
2.(No other members, i was absent 11/4 and have not had opportunity to join a group)

Member Responisbilities:

1. Stephen Dinh - Everything (that's what happens when you miss class)

LIMITATIONS:

1. Must input int or double, NO TEMPERATURES CAN BE SPELLED OUT!

2. NO prompt for "Acceptable Temperature Range" other than on initialization (e.g. sudo ./monitor (low) (high)) 

3.averages are calculated after every input.

4. Automated temperature input (say from a live feed/active thermostat) was not specified in assignment criteria, manual input only - see first point (line 33)

Description:

(L1-6)

Multiline comment - To run, use gcc command with pigpio library flag. To run on Pi, use sudo from root folder. OPTIONAL: pass two numbers (Lower bound), (Upper bound) to adjust temperature limits.

(L7-15)

Before main, import standard input/output tools, library utls, math funnctions, and Pi gpio's. Follow with macro constants. 

(L16-64)

Main entry point - after accepting commandline arg, set default temp bounds to 68.0 (low) and 76.0 (high). Should the user pass two custom arg on startup, convert those strings > numbers and override the default values. 
Begin initializing the Pi's hardware. If it fails/returns a negative number, print an error and a tip "remember sudo". exit immediately with an error code. OTHERWISE, config GPIO17 as an output pin. Proceed to print the active temp range. 
Allocate a (64) character text buffer and an end-pointer for input parsing. Create a double for current temp, an accumulator var "sum", ini to 0 > all this to set up workspace memory. 
Begin running the (infinite) loop. Print a prompt asking for a manual input of a temp/q = quit. Should the read fail, or "q" is pressed, break the loop and end the program.
Attempt to convert the (!= q) input into a double, stporing the result in "t". Should no number be found, or if there are trailing invalid inputs, or if the number is != finite, print an error message and skip to the next loop iteration.
The program then proceeds to evaluate if "t" is outside the lower/upper bounds, storing the result in the "warn" flag. "WARNING" or "NORMAL" is assigned to the status label. Drive the LED pin to high if warning, or LED > low (off) if normal. finally, add the temperature to the running sum and increment the entry count (++). 
Open the CSV log. If the log is new, write a header row. Append the current "t" and status, then close the file. 
Seperately, open the Status text file, write/overwrite with the current stroing and close.
Print a summary line to the console showing the entered temp, system status, LED state, total count of valid entries, and the running avg. Then loop back to the top.

Should the loop be broken, drive the LED to low. Shut down the Pigpio bg threads and exit the program with code 0.
