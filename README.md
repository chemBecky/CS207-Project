# Auto Titrator

## Description

This project uses an Arduino to automate titrations that can be monitored by pH.  A servo motor that is attached to the stopcock of a buret will rotate to add decreasing volumes of titrant depending on the change in pH measured with an electrode.  It is intended to be used independently of a computer at the push of the "Go" button.  An emergency "Stop" button, a red LED, a green LED, and a piezo speaker are also used to communicate information.  When the endpoint has been reached, the red LED turns on and the unit beeps three times. If the user agrees that the titration is complete, they press the Stop button.  If not, they can press the Go button to add another drop of titrant.

## Contents

- [/sketch](/sketch/sketch.ino): Source code for Arduino
- [/circuit and breadboard](circuit%20and%20breadboard): Circuit diagrams
- [/instructions.md](Instructions.md): Instructions for use of Auto Titrator
- [/video and pictures](video%20and%20pictures): pictures of project in action
- other sketch files: [testing servo movements to calibrate volume](/sketch_servotest/sketch_servotest.ino) and [creating a tune to play after a successful titration](/sketch_toneMelodytest)

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
- [ ]	wires
- [ ]	copper wire (highest gauge that will fit through servo propeller) and elastic band to attach motor to buret
- [ ]	plastic container to protect Arduino electronics (cut holes for access to buttons and servo cable)
- [ ]	potentiometer (for testing if desired)
- [ ] for the titration: buret, stir bar, stir plate, acidic/basic solutions, pH indicator
