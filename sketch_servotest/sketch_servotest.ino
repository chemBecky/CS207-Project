/*
 Servo testing for Auto Titrator

 This code is for testing a servo when attached to a buret.  Adjust the reachOpenDelay and reachClosedDelay to ensure enough
 time for the servo to rotate to the correct position.  Adjust the addTitrantDelay to add the desired volume of titrant from
 the buret.  Adjust the range of angles to reduce time required to move between positions.  The servo is attached to 5V,
 ground, and output pin 9.  The servo library is required.
 
 Based on the "Sweep" example:
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo servo;  // create servo object to control a servo

const int servoPin = 9;

int servoPos;    // variable to store the servo position
int reachOpenDelay = 25;  // delay to allow the servo to reach open position
int addTitrantDelay = 0; // delay while titrant added 
int reachClosedDelay = 25; // delay to allow the servo to return to closed position

void setup() {
  servo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  servoPos = analogRead(servoPin);
  
  for (; servoPos <= 80; servoPos ++) { 
    servo.write(servoPos);              // tell servo to go to position in variable 'servoPos' in steps of 1 degree
    delay(reachOpenDelay);              // waits for the servo to reach the open position
  }
  
  delay(addTitrantDelay);  //delay for titrant to be added
  
  for (; servoPos >= 30; servoPos --) { 
    servo.write(servoPos);              // move servo back to closed position
    delay(reachClosedDelay);                       
  }

  delay(10000);  //10 second delay to allow buret reading
}
