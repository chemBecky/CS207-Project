#  Instructions for use of Auto Titrator

1.  Only needs to be done before the first use: Attach the servo to a stopcock.  Use the [sketch_servotest](sketch_servotest/sketch_servotest.ino) to calibrate the movements and add 1.0 mL, 0.3 mL, and a drop from the buret.  If desired, use the [sketch_toneMelodytest](sketch_toneMelodytest/sketch_toneMelodytest.ino) to create a song to play after a successful titration.  Upload [sketch.ino](/sketch/sketch.ino) code onto Arduino board with the values from the servo and tone test sketches.
2.  Attach a clean buret to a retort stand.  Insert the stopcock attached to the servo into buret and secure with o-ring and nut.  Rotate the stopcock to open and rinse buret with titrant.  Check for and remove bubbles that form.  Rotate the stopcock to the closed position.  Fill the buret with at least 20 mL of titrant.
3.  Set up the stir plate, buret height, and solution to be analyzed.  Insert the pH meter into the solution.  Start stirring the solution.
4.  Plug in the 5V adapter to power up the Arduino.  Record the initial buret reading.  The servo should move back to the starting position.
5.  Align the servo parallel to the buret. Tightly clamp the Arduino to a portable retort stand trying not to create any additional torsion or adjustment to the position of the stopcock or servo.
6.  If you are sure that everything is ready, press the GO button.  The green light will turn on to indicate that the titration is in progress.  Close the container to protect the Arduino.
7.  If there are any problems, press the STOP button.  This will stop the titration and you will need to press the GO button to restart the titration.
8.  When the Auto Titrator makes three beeps, the green light turns off, and the red light turns on, the endpoint has been reached.  If you disagree and wish for the titration to continue, press the GO button.  If you agree and wish to stop the titration, press the STOP button.
9.  At the end, the LEDs will turn off, the servo will move back to 0°, and a celebration tune will play.  Rinse the pH meter and store appropriately.   Unplug the Arduino.
10.  Unclamp the servo.  Rotate the stopcock to empty the titrant into an appropriate container.  Remove the nut and o-ring so that the stopcock can be carefully removed from the buret and cleaned.

##  Auto Titrator States:
-  **Flashing green light** - before the titration, push the GO button to start
-  **Green light** - during titration, push the STOP button for emergency stop
-  **Red light** - endpoint reached, push the GO button to continue, push the STOP button to end the titration
