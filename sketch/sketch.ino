/* CS 207 Final Project
  Automated Titrator
  by Becky Jamieson
  
  Description
  
  Based on The Titration Machine by Enginerds2015
  https://www.instructables.com/id/Arduino-Based-Chemical-Titration-aka-The-Titration/

*/

#include <Servo.h>

//declare constants for pin assignments
const int pHpin = A4;
const int button1Pin = 6;  //for titration start
const int button2Pin = 7;  // for emergency stop
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
int stage = beforeStage;  //keeps the titration from starting before the button is pushed
int servoPosition = 0;  //positon of servo between 0 and 180
float pHold;  //stores previous pH reading
float pHnew;  
float derivativeOld = 0.01; //stores previous derivative
float derivativeNew;
int button1State = LOW;     //pull down button to start titration
int button2State = LOW;     //pull down button

Servo servo;  // create servo object

//set up the pins
void setup() {
  pinMode(pHpin, INPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  servo.attach(9);
}

void loop() {
  if (stage == beforeStage) {
    button1State = digitalRead(button1Pin);   //check if button1 has been pressed
    
    if (button1State == HIGH) {
      stage = stabilizeStage;  //if button1 has been pressed, move forward with the titration
      digitalWrite(greenLED, HIGH);  //turn on the green LED to indicate titration start
    }
    else delay(150);
  }

  else if (button2State == HIGH){
    stage = endStage;  //if the emergency stop is pressed, abort titration
  }
   
  else if (stage == stabilizeStage && button2State == LOW) {
    pHold = getpH();  //get initial pH reading
    stage = largeVolumeStage;  //move forward with titration
  }

  else if (stage == largeVolumeStage && button2State == LOW) {
    addLargeVolume();  //rotate servo to add titrant
    pHnew = getpH();  //read pH after titrant added
    derivativeNew = abs(pHnew - pHold) / 0.5;  //find the rate of change 
    
      if (derivativeNew - derivativeOld > 50){
        stage = smallVolumeStage;  //if large change in pH, move to next stage
      }
      else{
        stage = largeVolumeStage;  //otherwise, add a large volume again
      }
      
    pHold = pHnew;  //store the new pH
    derivativeOld = derivativeNew;  //store the derivative
  }

  else if (stage == smallVolumeStage && button2State == LOW) {
    addSmallVolume();  //rotate servo to add titrant
    pHnew = getpH();  //read pH after titrant added
    derivativeNew = abs(pHnew - pHold) / 0.1;  //find the rate of change 
    
      if (derivativeNew - derivativeOld > 500){
        stage = dropVolumeStage;  //if large change in pH, move to next stage
      }
      else{
        stage = smallVolumeStage;  //otherwise, add a small volume again
      }
      
    pHold = pHnew;  //store the new pH
    derivativeOld = derivativeNew;  //store the derivative
  }

  else if (stage == dropVolumeStage && button2State == LOW) {
    addDropVolume();  //rotate servo to add titrant
    pHnew = getpH();  //read pH after titrant added
    derivativeNew = abs(pHnew - pHold) / 0.05;  //find the rate of change 
    
      if (derivativeNew - derivativeOld > 5000){
        stage = endStage;  //if large change in pH, the endpoint is reached
        //make three beeps on piezo speaker
      }
      else{
        stage = dropVolumeStage;  //otherwise, add a drop again
      }
      
    pHold = pHnew;  //store the new pH
    derivativeOld = derivativeNew;  //store the derivative
  }

  else if (stage == endStage){
    digitalWrite(greenLED, LOW); //turn off green LED
    digitalWrite(redLED, HIGH); // turn on red LED

    if (button2State == HIGH){
      //play piezo song
      stage = beforeStage; //end the titration if the stop button is pressed
    }
    else if (button1State == HIGH){
      stage = dropVolumeStage; //keep titrating if go button pressed
      digitalWrite(redLED, LOW); //turn off red LED
      digitalWrite(greenLED, HIGH); // turn on green LED
    }
  }

  delay(20);
}

//function for getting a stable, average reading from the pH meter
float getpH(){
  delay(200);
  int total = 0;
  for (int i = 0; i < 20; i++){
    total += analogRead(pHpin); //total of 20 pH readings over 2 sec
    delay(100); 
  }

  pHnew = total / 20;  //find the average pH value over 2 sec
  return pHnew;
}

//function for adding largest amount of titrant
void addLargeVolume(){
  //for () move servo, reverse servo with long delay
}

//function for adding small amount of titrant
void addSmallVolume(){
  //for ()move servo, reverse servo with short delay
}

//function for adding titrant drop by drop
void addDropVolume(){
  //for ()move servo, reverse servo with smallest delay
}
