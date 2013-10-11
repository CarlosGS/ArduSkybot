/*
 ArduSkyBot example code
 
 Author: Carlos Garcia Saura
 July 2012
 */

/*
 ArduSkyBot library v1.0
 
 Uses part of the "Rueda V1.0" library by Santiago Lopez
 
 Author: Carlos Garcia Saura
 July 2012
 */

// Include the necessary libraries
#include <Servo.h> 

// --- PIN DEFINITIONS ---

#define LED_RED 3      // LED Lights
#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_ORANGE 13

#define BUTTON 12

#define LDR_LEFT A5   // Pins for the light sensors
#define LDR_RIGHT A4

#define MOTOR_LEFT 7  // Pins for the motors
#define MOTOR_RIGHT 8

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


// --- MOTORS ---

Servo S_MOTOR_LEFT;
Servo S_MOTOR_RIGHT;
int S_MOTOR_LEFT_CENTER = 1400;
int S_MOTOR_RIGHT_CENTER = 1400;

// Function that inits the motors
void init_motors() {
  /*S_MOTOR_LEFT.attach(MOTOR_LEFT);    // Init servo library
   S_MOTOR_RIGHT.attach(MOTOR_RIGHT);
   
   S_MOTOR_LEFT.writeMicroseconds(S_MOTOR_LEFT_CENTER);                  // Make the motors stop
   delay(200);
   S_MOTOR_RIGHT.writeMicroseconds(S_MOTOR_RIGHT_CENTER);*/
}

// Functions for controlling the motors
// They take a parameter that ranges within -100 and 100, that indicates the speed and direction of rotation.
void motor_left(int m_speed) {
  m_speed = constrain(m_speed,-100,100); // Make sure the value is on the range

  if(m_speed != 0) {
    if(!S_MOTOR_LEFT.attached()) S_MOTOR_LEFT.attach(MOTOR_LEFT);
    S_MOTOR_LEFT.writeMicroseconds(map(m_speed,-100,100,S_MOTOR_LEFT_CENTER-500,S_MOTOR_LEFT_CENTER+500)); // Set the speed
  } 
  else {
    if(S_MOTOR_LEFT.attached()) S_MOTOR_LEFT.detach();
  }
}

// Same but for right motor
void motor_right(int m_speed) {
  m_speed = constrain(m_speed,-100,100); // Make sure the value is on the range

  if(m_speed != 0) {
    if(!S_MOTOR_RIGHT.attached()) S_MOTOR_RIGHT.attach(MOTOR_RIGHT);
    S_MOTOR_RIGHT.writeMicroseconds(map(m_speed,-100,100,S_MOTOR_RIGHT_CENTER+500,S_MOTOR_RIGHT_CENTER-500)); // Set the speed (note: the direction is opposite to left motor)
  } 
  else {
    if(S_MOTOR_RIGHT.attached()) S_MOTOR_RIGHT.detach();
  }
}

int speed_motors = 20;

void robot_stop() {
  motor_left(0);
  motor_right(0);
}

void robot_forward() {
  motor_left(speed_motors);
  motor_right(speed_motors);
  delay(1000);
  robot_stop();
}

void robot_backward() {
  motor_left(-speed_motors);
  motor_right(-speed_motors);
  delay(1000);
  robot_stop();
}

void robot_left() {
  motor_left(-speed_motors);
  motor_right(+speed_motors);
  delay(500);
  robot_stop();
}

void robot_right() {
  motor_left(+speed_motors);
  motor_right(-speed_motors);
  delay(500);
  robot_stop();
}




// This function runs only once at the begining
void setup() {                
  // Initialization functions
  init_motors();
  init_pins_distance_sensor();
  init_LED_pins();
  init_button_pin();

  // Waits until the button is pressed
  while( button_is_pressed() == 0 ) {
    delay(100);
  }

  // We turn on the ORANGE LED so we know our program is running
  digitalWrite(LED_ORANGE, HIGH);
}

void makeSound(int lenght, int num) {
  int i,j;
    for(i=1; i<num; i++) {
      tone(SPEAKER,10*i);
      delay(lenght);
    }
  delay(2*lenght);
  noTone(SPEAKER);
}

/// WRITE YOUR CODE HERE ///
void loop() { // The loop function runs forever
  // Turns the RED LED on
  digitalWrite(LED_RED, HIGH);
  robot_forward();

  // Waits for one second
  delay(1000);

  // Turns the RED LED off
  digitalWrite(LED_RED, LOW);
  robot_backward();

  // Waits for one second
  delay(1000);
  
  // Play a sound
  makeSound(100, 5);

  robot_left();
  robot_forward();
  robot_right();
  
  
  
  
  
  // Waits until the button is pressed
  while( button_is_pressed() == 0 ) {
    delay(100);
  }
}

















