/*
 Nyan Cat
 
 Plays Nyan Cat
 example to fast (old version): http://www.youtube.com/watch?v=eFHfGA5e4n8
 example this version: http://youtu.be/t3gKFuTb4kQ
 circuit:
 * 8-ohm speaker on digital pin 8
 
 By: Bruce Helsen (geobruce) 
 Stan Draulans (purewantfun)
 update (Jrigvd (Jordy v. D.))
 */
#include "pitches.h"

// --- PIN DEFINITIONS ---

#define LED_RED 3      // LED Lights
#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_ORANGE 13

#define SPEAKER 11

#define BUTTON 12

// --- LEDs ---

// Function for initiating the pins used by the LEDs
void init_LED_pins() {
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);
  pinMode(LED_ORANGE,OUTPUT);
}

// --- BUTTON ---

// Function for initiating the pin used by the button
void init_button_pin() {
  pinMode(BUTTON,INPUT);

  digitalWrite(BUTTON, HIGH); // Enable internal pull-up resistor
}

// Function for reading the button value
// Returns 1 if the button is being pressed, 0 if it is not
int button_is_pressed() {
  return !digitalRead(BUTTON);
}

int intro[] = {
  //intro
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B5,
  NOTE_CS6,
  NOTE_DS6,
  NOTE_CS6,
  NOTE_AS5,
  NOTE_B5,
  NOTE_FS5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B5,
  NOTE_CS6,
  NOTE_AS5,
  NOTE_B5,
  NOTE_CS6,
  NOTE_E6,
  NOTE_DS6,
  NOTE_E6,
  NOTE_B5, 

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8, //13
  8,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16 //25 intro
};

void setup() {
  init_button_pin();
  init_LED_pins();

  // Wait until the button is pressed
  while( button_is_pressed() == 0 ) {
    delay(100);
  }

  // We turn on the ORANGE LED so we know our program is running
  digitalWrite(LED_ORANGE, HIGH);

  for (int thisNote = 0; thisNote < 25; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1500/noteDurations[thisNote];
    tone(SPEAKER, intro[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER);
  }
}
int melody[] = {
  //A
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_DS5,
  REST,
  NOTE_B4,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  REST,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_D5,
  NOTE_DS5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_DS5,
  REST,
  NOTE_B4,
  NOTE_D5, 
  NOTE_CS5,
  NOTE_B4,
  REST,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_D5,
  NOTE_DS5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  //end of loop
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_DS4,
  NOTE_E4,
  NOTE_FS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_FS4,
  //
  NOTE_B4,
  NOTE_B4,
  NOTE_AS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_E4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_AS4,
  //
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_DS4,
  NOTE_E4,
  NOTE_FS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_FS4,
  NOTE_B4,
  NOTE_B4,
  NOTE_AS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_CS5 

};
int melodyNoteDurations[] = {
  //a
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16, 
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16, 
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  //
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  //
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  //
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  //
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8 
};
void loop() {


  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 216; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1400/melodyNoteDurations[thisNote];
    tone(SPEAKER, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER);
  }
}

