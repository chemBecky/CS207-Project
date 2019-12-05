# Auto Titrator

## Description

This project uses an Arduino to automate titrations that can be monitored by pH.  A servo motor that is attached to the stopcock of a buret will rotate to add decreasing volumes of titrant depending on the derivative (change in pH over change in volume).  The pH is measured with an electrode attached to a pH-4502c.  It is intended to be used independently of a computer at the push of the "Go" button.  An emergency "Stop" button, a red LED, a green LED, and a piezo speaker are also used to communicate information. There are six stages in the sketch: before, stabilization, large volume, small volume, drop volume, and end.  The before stage moves the servo to 0 degrees and prevents the titration from starting until the Go button is pressed.  The stabilization stage gets the initial pH reading.  The volume adding stages send different delay times for the buret to be in the Open position.  The derivative is calculated after each volume addition and compared to a threshold value to move to the next stage.  When the threshold for the drop volume stage has been exceeded, the end stage is reached. The red LED turns on and the unit beeps three times. If the user agrees that the titration is complete, they press the Stop button.  If not, they can press the Go button to go back to the drop volume stage.  If a successful titration has been achieved, a tune is played on the piezo speaker.

## Contents

- [/sketch](/sketch/sketch.ino): Source code for Arduino
- [/circuit and breadboard](circuit%20and%20breadboard): Circuit diagrams
- [/instructions.md](Instructions.md): Instructions for use of Auto Titrator
- [/video and pictures](video%20and%20pictures): pictures of project in action
- other sketch files: [testing servo movements to calibrate volume](/sketch_servotest/sketch_servotest.ino) and [creating a tune to play after a successful titration](/sketch_toneMelodytest/sketch_toneMelodytest.ino)

## Materials

- [ ]	Arduino UNO
- [ ]	pH meter
- [ ] pH analog reader (pH-4502c)
- [ ]	two buttons
- [ ]	two 10 kΩ resistors for buttons
- [ ]	two LEDs (red and green)
- [ ]	two 560 Ω resistors for LEDs
- [ ]	piezo speaker
- [ ]	High torque servo motor, I used MG-996R with 13 kgcm torque
- [ ]	retort stand and clamp to hold the servo motor tightly
- [ ]	wires
- [ ]	copper wire (highest gauge that will fit through servo propeller) and elastic band to attach motor to buret
- [ ]	plastic container to protect Arduino electronics (cut holes for access to buttons and servo cable)
- [ ]	potentiometer (for testing if desired)
- [ ] for the titration: buret, buret stand, stir bar, stir plate, acidic/basic solutions, pH indicator

## Build Instructions
This is the circuit for the Auto Titrator using a potentiometer as a stand-in for the pH-4502c:

<img src="circuit and breadboard/final project circuit.png" height="300">

Nothing in the circuit is overly complicated.  The buttons are connected to 5V and ground through a 10 kOhm resistor.  They are in a pull-down configuration so the pin is on same side as the ground connection.  The Go button is connected to pin 6 and the Stop button is connected to pin 7.  The piezo speaker is connected to pin 11 and ground.  The LEDs are powered through pins 13 (green) and 12 (red) with 560 Ohm resistors to the ground connection.  The servo motor requires a 5V connection, a ground connection, and is connected to pin 9.  The pH-4502c needs two grounded connections, a 5V source connection, and then is connected to A0.

This is the breadboard view of the same circuit with again, a potentiometer to as a stand-in for the pH-4502c:

<img src="circuit and breadboard/final project breadboard.png" height="250">

The tough parts of the build are getting the servo/buret combination to work.  First, with the servo at 0 degrees, attach the propeller perpendicular to the motor.  Then, make sure that the screw attaching the propeller to the servo is tight.  Next, attach a stopcock to the propeller.  I found that wrapping an elastic band around the two helped with the next step.  With as large of gauge copper wire as can fit into the propeller holes, wrap the propeller and stopcock together.  I also found that lubricating the buret helped.  You will also need a retort stand and clamp to hold the motor in place during the titration.

I should also mention that the pH-4502c needs to be adjust before use.  I followed the ["How to use a pH probe and sensor](https://www.botshop.co.za/how-to-use-a-ph-probe-and-sensor/) tutorial.  Adjust the potentiometers on the board such that pH 7 reads 2.5 V and that the threshold is set as high as possible.

## Usage
Please see the [instructions](instructions.md) for a detailed account of how to use the Auto Titrator.  The [sketch](sketch/sketch.ino) only needs the default [servo.h](https://www.arduino.cc/en/reference/servo) library from Arduino.

## Credits
- [Enginerds2015](https://www.instructables.com/id/Arduino-Based-Chemical-Titration-aka-The-Titration/) for initial coding
- [AdityaMitra5102](https://github.com/AdityaMitra5102/Titrator) for servo-based buret movements
- [botshop.co.za](https://www.botshop.co.za/how-to-use-a-ph-probe-and-sensor/) for instruction to calibrate my pH-4502c
- [Fritzing (version 0.9.3)](www.fritzing.org) for the circuit and breadboard diagram creation software
