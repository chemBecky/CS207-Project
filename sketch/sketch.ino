/* CS 207 Final Project
  Automated Titrator
  by Becky Jamieson
  
  Description
  
  Based on The Titration Machine by Enginerds2015
  https://www.instructables.com/id/Arduino-Based-Chemical-Titration-aka-The-Titration/

*/

#include <Servo.h>

//declare constants for pin assignments
const int pHpin = A0;
const int goButtonPin = 6;  // Go button for titration start
const int stopButtonPin = 7;  // Stop button for emergency stop
const int servoPin = 9;
const int redLED = 12;
const int greenLED = 13;
const int piezoPin = 11;

//define stages of titration
const int beforeStage = 0;
const int stabilizeStage = 1;
const int largeVolumeStage = 2;
const int smallVolumeStage = 3;
const int dropVolumeStage = 4;
const int endStage = 5;

//declare global variables
int stage = beforeStage;   // keeps the titration from starting before the button is pushed
int servoPos;   // positon of servo where 0 is a closed buret and 90 is fully open
int openDelay;   // time that the servo waits in the 'open' position
float pHold;   // stores previous pH reading
float pHnew;  
float derivative;
int goButtonState = LOW;  // pull down button, HIGH when pushed
int stopButtonState = LOW;  // pull down button

Servo servo;  // create servo object

//set up for tune to play on the piezo when titration complete
int melody[] = {
  262, 220, 233, 262, 349, 440, 392, 349, 0, 440, 392, 349, 330, 294, 392, 330, 262,
  220, 349, 392, 440, 233
};
// note durations as multiples of 1/16
int noteLength[] = { 1, 3, 1, 2, 6, 2, 2, 2, 2, 3, 1, 2, 2, 1, 3, 2, 2, 1, 11, 1, 3, 8 };


//set up the pins
void setup() {
  pinMode(pHpin, INPUT);
  pinMode(goButtonPin, INPUT);
  pinMode(stopButtonPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(piezoPin, OUTPUT);
}

void loop() {

  stopButtonState = digitalRead(stopButtonPin);  // Use stopButton as an emergency stop

  if (stopButtonState == HIGH && stage != endStage) {   // if the emergency stop is pressed, abort titration
    digitalWrite(greenLED, LOW); //turn off green LED
    stage = beforeStage;  
  }
    
  else if (stage == beforeStage) {
    goButtonState = digitalRead(goButtonPin);   // check if Go button has been pressed

    servo.attach(servoPin);  // for stable pH readings, only initiate servo when in use
    servoPos = servo.read();  //read current servo position
    for ( ; servoPos >= 0; servoPos --) {  // reverse servo to 0 degrees to start
      servo.write(servoPos);  
      delay(30);
    }
    servo.detach();
    
    if (goButtonState == HIGH) {
      stage = stabilizeStage;  // if GO button has been pressed, move forward with the titration
      digitalWrite(redLED, LOW);  // turn off the red LED
      digitalWrite(greenLED, HIGH);  // turn on the green LED to indicate titration start
    }
    delay(500);
  }

  else if (stage == stabilizeStage) {
    delay(2000);  // let the pH stabilize
    pHold = getpH();  // get initial pH reading
    stage = largeVolumeStage;  // move forward with titration
  }

  else if (stage == largeVolumeStage) {
    openDelay = 2500;
    addTitrant(openDelay);  // rotate servo to add titrant
    pHnew = getpH();  // read pH after titrant added
    derivative = abs(pHnew - pHold) / 1.0;  // find the rate of change 
    
      if (derivative > 8) {
        stage = smallVolumeStage;  // if large change in pH, move to next stage
      }

    pHold = pHnew;  // store the new pH
  }

  else if (stage == smallVolumeStage) {
    openDelay = 600;
    addTitrant(openDelay);
    pHnew = getpH();
    derivative = abs(pHnew - pHold) / 0.3;
    
      if (derivative > 30) {
        stage = dropVolumeStage;
      }
      
    pHold = pHnew;
  }

  else if (stage == dropVolumeStage) {
    openDelay = 1;
    addTitrant(openDelay);
    delay(5000);
    pHnew = getpH();
    derivative = abs(pHnew - pHold) / 0.1;
    
      if (derivative > 800) {
        stage = endStage;  // if large change in pH, the endpoint is reached
        for(int i = 0; i < 3; i++) {
          analogWrite(piezoPin, 200);  // make three beeps on piezo speaker
          delay(500);
          digitalWrite(piezoPin, 0);
          delay(200);
        }
      }
      
    pHold = pHnew;
  }

  else if (stage == endStage) {
    digitalWrite(greenLED, LOW);  // turn off green LED
    digitalWrite(redLED, HIGH);  // turn on red LED
    goButtonState = digitalRead(goButtonPin);
    stopButtonState = digitalRead(stopButtonPin);

    if (goButtonState == HIGH) {  // if Go button pressed keep titrating 
      stage = dropVolumeStage;
      digitalWrite(redLED, LOW);  // turn off red LED
      digitalWrite(greenLED, HIGH);  // turn on green LED to indicate titration in progress
    }

    else if (stopButtonState == HIGH) {  // if the Stop button is pressed end the titration
      stage = beforeStage; 

      servo.attach(servoPin);
      for ( ; servoPos >= 0; servoPos --) {  // reverse servo to 0 degrees for next time
        servo.write(servoPos);  
        delay(25);
      }
      servo.detach();
      
      for (int note = 0; note < 22; note++) {  //play the Annie theme to celebrate completion
        int actualLength = 125 * noteLength[note];  // play each 1/16th note for 125 ms
        tone(piezoPin, melody[note], actualLength);
        
        int betweenNotes = actualLength * 1.3;  // rest for an extra 30% of time between notes
        delay(betweenNotes);
        noTone(piezoPin);  // turn off pin between notes
      }

       digitalWrite(redLED, LOW);  //turn off both LEDs
    }
  }

  delay(20);
}

//function for getting a stable, average reading from the pH meter
float getpH() {
  delay(2000);
  int total = 0;
  
  for (int i = 0; i < 10; i ++) {
    total += analogRead(pHpin); // total of 10 pH readings over one second
    delay(100); 
  }

  pHnew = total / 10;  //find the average pH value
  return pHnew;
}

//function for adding titrant
void addTitrant(int openDelay) {
  servo.attach(servoPin);
  for ( ; servoPos <= 75; servoPos ++) { 
    servo.write(servoPos);  // move servo to open
    delay(22);
  }
  
  delay(openDelay); //delay while titrant is added
  
  for ( ; servoPos >= 30; servoPos --) { 
    servo.write(servoPos);  // move servo to closed
    delay(30);
  }
  servo.detach();
}
