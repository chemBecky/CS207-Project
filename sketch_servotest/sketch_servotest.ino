/*
 Servo testing for auto titrator

 This code allows me to test my servo when attached to a buret.
 
 Based on the "Sweep" example:
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo servo;  // create servo object to control a servo

int servoPos = 0;    // variable to store the servo position

void setup() {
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (servoPos = 0; servoPos <= 85; servoPos ++) { 
    // in steps of 1 degree
    servo.write(servoPos);              // tell servo to go to position in variable 'servoPos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (; servoPos >= 0; servoPos --) { 
    servo.write(servoPos);              // tell servo to go to position in variable 'servoPos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
