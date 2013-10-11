/*
 Printshield example code
 
 Author: Carlos Garcia Saura
 July 2012
 */

// --- PIN DEFINITIONS ---

#define LED_RED 3      // LED Lights
#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_ORANGE 13

#define BUTTON 12

#define LDR_LEFT A5   // Pins for the light sensors
#define LDR_RIGHT A4

#define IR_1 A0       // Pins for the line sensor (four CNY70)
#define IR_2 A1       // IR_1 right, IR_4 left
#define IR_3 A2
#define IR_4 A3

#define ULTRASONIC_TRIG 2 // Pins for the ultrasonic distance sensor
#define ULTRASONIC_ECHO 4

#define SPEAKER 11


// --- ULTRASONIC SENSOR ---

// Function for initiating the pins used by the ultrasonic distance sensor
void init_pins_distance_sensor() {
  pinMode(ULTRASONIC_ECHO, INPUT);
  pinMode(ULTRASONIC_TRIG, OUTPUT);

  // Trigger pin is set low to avoid innecesary measurements
  digitalWrite(ULTRASONIC_TRIG, LOW);
}

// Function for reading the distance read by the ultrasonic sensor
// Returned value is in centimeters
int read_distance() {
  long duration;

  //This triggers the measurement
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);

  //We receive the distance as a pulse length
  duration = pulseIn(ULTRASONIC_ECHO,HIGH);

  //Returns the distance in centimeters. 
  return duration /29 / 2 ; //use "74 / 2" for inches
}


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

void wait_until_button_is_pressed() {
  while( button_is_pressed() == 0 ) delay(100);
}

void setup() {                
  // Pin initialization
  init_pins_distance_sensor();
  init_LED_pins();
  init_button_pin();

  // Wait until the button is pressed
  while( button_is_pressed() == 0 ) {
    delay(100);
  }

  // We turn on the ORANGE LED so we know our program is running
  digitalWrite(LED_ORANGE, HIGH);
}




/// WRITE YOUR CODE HERE ///
void loop() { // The loop function runs forever

  // Turns the RED LED on
  digitalWrite(LED_RED, HIGH);

  // Waits for one second
  delay(1000);

  // Turns the RED LED off
  digitalWrite(LED_RED, LOW);

  // Waits for one second
  delay(1000);

}



