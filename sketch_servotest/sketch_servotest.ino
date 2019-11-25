/*
 Servo testing for auto titrator

 This code is for testing a servo when attached to a buret.  Adjust the reachPosDelay to ensure enough time for the servo
 to rotate to the correct position.  Adjust the addTitrantDelay to add the desired volume of titrant from the buret.  The
 servo is attached to 5V, ground, and output pin 9.  The servo library is required.
 
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
int reachPosDelay = 25;  // delay to allow the servo to reach servoPos
int addTitrantDelay = 0; // delay while titrant added 

void setup() {
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
   for (; servoPos <= 80; servoPos ++) { 
    servo.write(servoPos);              // tell servo to go to position in variable 'servoPos' in steps of 1 degree
    delay(reachPosDelay);                       // waits for the servo to reach the position
  }
  
  delay(addTitrantDelay);  //delay for titrant to be added
  
  for (; servoPos >= 30; servoPos --) { 
    servo.write(servoPos);              // move servo back to starting position
    delay(reachPosDelay);                       
  }

  delay(10000);  //10 second delay to allow buret reading
}
