/* CS 207 Final Project
  Automated Titrator
  by Becky Jamieson
  
  Description
  
  Based on The Titration Machine by Enginerds2015
  https://www.instructables.com/id/Arduino-Based-Chemical-Titration-aka-The-Titration/

*/


//declare constants for pin assignments
const int pHpin = A4;
const int servoPin = 3;
const int button1Pin = 6;
const int button2Pin = 7;
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
int stage = beforeStage;   //keeps the titration from starting before the button is pushed
int volumeChange = 0;      //titrant volume added
float pHold;               //stores previous pH reading
float pHnew;  
float derivativeOld = 0.0; //stores previous derivative
float derivativeNew;
button1State = LOW;     //pull down buttons used
button2State = LOW;     //pull down buttons used

//set up the pins
void setup() {
  pinMode(pHpin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLDOWN);
  pinMode(button2Pin, INPUT_PULLDOWN);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(piezoPin, OUTPUT);
}

void loop() {

  if (stage == beforeStage) {
  
    button1State = digitalRead(button1Pin);   //check if button1 has been pressed
    
    if (button1State == HIGH) {
      stage = stabilizeStage;  //if the button has been pressed, move forward with the titration
     }
     else delay(150);
   }
   
   if (stage == stabilizeStage) {
   
   }
}

