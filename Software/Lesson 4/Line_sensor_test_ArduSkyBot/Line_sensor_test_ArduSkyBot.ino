/*
 ArduSkyBot example code
 
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


// Music notes
#define DO 262
#define RE 294
#define MI 330
#define FA 349
#define SOL 392
#define LA 440
#define SI 494


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


// Function that waits until an object is detected
void wait_for_distance(int distance) {
  while( read_distance() > distance ) {
    delay(500);
  }
}


// --- LEDs ---

// Function for initiating the pins used by the LEDs
void init_LED_pins() {
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);
  pinMode(LED_ORANGE,OUTPUT);
}

void blinkLED(int pin, int num) {
  int i;
  for(i=0; i<num; i++) {
    digitalWrite(pin, HIGH);
    delay(250);
    digitalWrite(pin, LOW);
    delay(250);
  }
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

// Function that waits until the button is pressed
void wait_for_button_press() {
  while( button_is_pressed() == 0 ) {
    delay(100);
  }
}


// --- MOTORS ---

Servo S_MOTOR_LEFT;
Servo S_MOTOR_RIGHT;
int S_MOTOR_LEFT_CENTER = 1400;
int S_MOTOR_RIGHT_CENTER = 1400;

// Function that inits the motors
// Calibration mode means motors should remain *almost* stopped
void init_motors(int calibration) {
  if(calibration) {
    S_MOTOR_LEFT.attach(MOTOR_LEFT);    // Init servo library
    S_MOTOR_RIGHT.attach(MOTOR_RIGHT);

    S_MOTOR_LEFT.writeMicroseconds(S_MOTOR_LEFT_CENTER);                  // Make the motors stop
    delay(200);
    S_MOTOR_RIGHT.writeMicroseconds(S_MOTOR_RIGHT_CENTER);
  }
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


// SPEAKER FUNCTIONS

void playSound(int lenght, int num) {
  int i,j;
  for(i=1; i<=num; i++) {
    tone(SPEAKER,(DO/4)*i);
    delay(lenght);
  }
  delay(2*lenght);
  noTone(SPEAKER);
}

void playNote(int frequency, int lenght) {
  if(frequency <= 0) frequency = DO;
  if(lenght <= 0) lenght = 100;
  tone(SPEAKER,frequency);
  delay(lenght);
  noTone(SPEAKER);
  delay(100);
}

void playHarmonicScale(int harmonic, int lenght) {
  playNote((DO/4)*harmonic, lenght);
  playNote((MI/4)*harmonic, lenght);
  playNote((SOL/4)*harmonic, lenght);
}

void playMusicScale(int lenght) {
  playNote(DO, lenght);
  playNote(RE, lenght);
  playNote(MI, lenght);
  playNote(FA, lenght);
  playNote(SOL, lenght);
  playNote(LA, lenght);
  playNote(SI, lenght);
}

void playInvertedMusicScale(int lenght) {
  playNote(SI, lenght);
  playNote(LA, lenght);
  playNote(SOL, lenght);
  playNote(FA, lenght);
  playNote(MI, lenght);
  playNote(RE, lenght);
  playNote(DO, lenght);
}


// LIGHT SENSOR FUNCTIONS
int ldr_left_ambient,ldr_right_ambient;
void init_light_sensor() {
  ldr_left_ambient = analogRead(LDR_LEFT);
  ldr_right_ambient = analogRead(LDR_RIGHT);
}

// Returns -10 if light is on the left, +10 if on the right
int light_source() {
  int left = analogRead(LDR_LEFT)-ldr_left_ambient;
  int right = analogRead(LDR_RIGHT)-ldr_right_ambient;

  int pos = left-right;

  pos=map(pos,-500,500,-10,10);

  //if(abs(pos) < 100) pos = 0;

  return pos;
}

int last_line_pos = -4;

int IR_sensor_is_black(int pin) {
  return !digitalRead(pin);
}

int IR_sensor_is_white(int pin) {
  return digitalRead(pin);
}

// Returns -10 if light is on the left, +10 if on the right
int line_pos() {
  if(IR_sensor_is_black(IR_1)) {
    if(IR_sensor_is_black(IR_2))
      return last_line_pos = 2;
    else
      return last_line_pos = 3;
  }

  if(IR_sensor_is_black(IR_2)) {
    if(IR_sensor_is_black(IR_3))
      return last_line_pos = 0;
    else
      return last_line_pos = 1;
  }

  if(IR_sensor_is_black(IR_3)) {
    if(IR_sensor_is_black(IR_4))
      return last_line_pos = -2;
    else
      return last_line_pos = -1;
  }

  if(IR_sensor_is_black(IR_4)) {
    return last_line_pos = -3;
  }

  if(IR_sensor_is_white(IR_1) && IR_sensor_is_white(IR_2) && IR_sensor_is_white(IR_3) && IR_sensor_is_white(IR_4)) {
    if(last_line_pos > 1) {
      return last_line_pos = 4;
    } 
    else if(last_line_pos < -1) {
      return last_line_pos = -4;
    }
  }

  return last_line_pos;
}


void init_ArduSkyBot() {
  init_motors(0);// 0 means normal mode, 1 means calibration mode
  init_pins_distance_sensor();
  init_LED_pins();
  init_button_pin();

  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);
}

int speed_motors = 20;

void robot_stop() {
  motor_left(0);
  motor_right(0);
}

void robot_forward() {
  motor_left(speed_motors);
  motor_right(speed_motors);
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
  delay(350);
  robot_stop();
}

void robot_right() {
  motor_left(+speed_motors);
  motor_right(-speed_motors);
  delay(350);
  robot_stop();
}


// If you put dir=10, robot goes to the right, -10 for the left
void robot_heading(int dir) {
  motor_left(10+dir);
  motor_right(10-dir);
}




// This function runs only once at the begining
void setup() {                

  // Setup all the I/O pins
  init_ArduSkyBot();

  // Waits until the button is pressed
  wait_for_button_press();

  // We turn on the ORANGE LED so we know our program is running
  digitalWrite(LED_ORANGE, HIGH);


  // YOU CAN CUSTOMIZE THIS:
  playNote(RE, 200);
  playNote(FA, 200);
  playNote(LA, 200);

}


void loop() { // The loop function runs forever

  // This line of code heads the robot towards a light source
  //robot_heading(light_source());

  // Play a small tone for each sensor
  if(IR_sensor_is_white(IR_1)) {
    playNote(DO, 100);
  }
  if(IR_sensor_is_white(IR_2)) {
    playNote(RE, 100);
  }
  if(IR_sensor_is_white(IR_3)) {
    playNote(MI, 100);
  }
  if(IR_sensor_is_white(IR_4)) {
    playNote(FA, 100);
  }

  // Wait for a bit
  delay(10);
}






