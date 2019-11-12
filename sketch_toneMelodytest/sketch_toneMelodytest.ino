/*
  Test for the Annie theme Easter Egg

  A piezo speaker attached to pin 11 (and ground) will play the tune from Annie.

  Adapted from Melody:
  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/Tone
*/

// notes in the melody
int melody[] = {
  262, 220, 233, 262, 349, 440, 392, 349, 0, 440, 392, 349, 330, 294, 392, 330, 262,
  220, 349, 392, 440, 233
};

// note durations as multiples of 1/16
int noteLength[] = { 1, 3, 1, 2, 6, 2, 2, 2, 2, 3, 1, 2, 2, 1, 3, 2, 2, 1, 11, 1, 3, 8 };

const int piezoPin = 11;

void setup() {
  
  for (int note = 0; note < 22; note++) {  // play each note of the melody

    int actualLength = 125 * noteLength[note];  // 1/16th note plays for 125 ms
    tone(piezoPin, melody[note], actualLength);
    
    int betweenNotes = actualLength * 1.3; // rest for an extra 30% of time between notes
    delay(betweenNotes);
    
    noTone(piezoPin);
  }
}

void loop() {
  // no need to repeat the melody.
}
