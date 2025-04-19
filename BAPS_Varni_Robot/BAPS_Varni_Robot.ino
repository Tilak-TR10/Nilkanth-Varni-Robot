// Right motor driver pins
const int R_EN_right = 2; 
const int L_EN_right = 4;
const int R_PWM_right = 6; // PWM pin for speed control
const int L_PWM_right = 9; // PWM pin for speed control

// Left motor driver pins
const int R_EN_left = 7; 
const int L_EN_left = 8;
const int R_PWM_left = 10; // PWM pin for speed control
const int L_PWM_left = 11; // PWM pin for speed control

// Receiver signal pins
const int ch1Pin = 5;  // Channel 1 for left/right control
const int ch2Pin = 3;  // Channel 2 for forward/backward control
const int ch3Pin = A2;  // Channel 2 for speed

void setup() {
  // Set motor control pins as outputs
  pinMode(R_EN_right, OUTPUT);
  pinMode(L_EN_right, OUTPUT);
  pinMode(R_PWM_right, OUTPUT);
  pinMode(L_PWM_right, OUTPUT);

  pinMode(R_EN_left, OUTPUT);
  pinMode(L_EN_left, OUTPUT);
  pinMode(R_PWM_left, OUTPUT);
  pinMode(L_PWM_left, OUTPUT);

  // Set receiver channel pins as inputs
  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);

  stopMotors();
  Serial.begin(115200);
}

void loop() {
  // Read pulse width from the receiver channels
  int ch1Value = pulseIn(ch1Pin, HIGH); // Channel 1 for left/right
  int ch2Value = pulseIn(ch2Pin, HIGH); // Channel 2 for forward/backward
  int ch3Value = pulseIn(ch3Pin, HIGH); // Channel 2 for forward/backward

  //Print channel values for debugging
  Serial.print("Ch1 (L/R): ");
  Serial.print(ch1Value);
  Serial.print(" us, Ch2 (F/B):");
  Serial.println(ch2Value);
  Serial.print(" us, Speed: ");
  Serial.println(ch3Value);
  
  // Map channel 2 value to PWM duty cycle (0-255) for speed
   int speed = map(ch3Value, 1030, 1875, 0, 255); //Speed
   

//  int speed_FB_1 = map(ch2Value, 995, 2000, 0, 255); // Adjust 1000, 2000 based on range
//  int speed_FB_2 = map(ch2Value, 2000, 995, 0, 255); // Adjust 1000, 2000 based on range
//
//  int speed_LR_1 = map(ch1Value, 1140, 1990, 0, 255); // Adjust 1000, 2000 based on range          _1
//  int speed_LR_2 = map(ch1Value, 1990, 1140, 0, 255); // Adjust 1000, 2000 based on range


  // Determine movement based on channel 2 and channel 1 values
  if (ch2Value > 1550) {
    moveForward(speed);
  } else if (ch2Value < 1400) {
    moveBackward(speed);
  } else if (ch1Value > 1550) {
    turnRight(speed);
  } else if (ch1Value < 1400) {
    turnLeft(speed);
  }else if ((ch1Value == 0) && (ch2Value == 0)){
    stopMotors();
  }
  else{
    stopMotors();
  }

  delay(20); // Adjust delay as needed
}

void moveForward(int speed) {
  // Both motors forward
  // Enable the motor drivers
  digitalWrite(R_EN_right, HIGH);
  digitalWrite(L_EN_right, HIGH);
  digitalWrite(R_EN_left, HIGH);
  digitalWrite(L_EN_left, HIGH);  // Set PWM values for forward movement
  
  analogWrite(R_PWM_right, speed); // Set right motor speed
  analogWrite(L_PWM_right, 0);      // Set left motor speed to 0 for forward
  analogWrite(R_PWM_left, speed);   // Set left motor speed
  analogWrite(L_PWM_left, 0);       // Set right motor speed to 0 for forward
}

void moveBackward(int speed) {
  // Both motors backward
  digitalWrite(R_EN_right, HIGH);
  digitalWrite(L_EN_right, HIGH);
  digitalWrite(R_EN_left, HIGH);
  digitalWrite(L_EN_left, HIGH);

  analogWrite(R_PWM_right, 0);      // Set right motor speed to 0 for backward
  analogWrite(L_PWM_right, speed);   // Set left motor speed
  analogWrite(R_PWM_left, 0);       // Set left motor speed to 0 for backward
  analogWrite(L_PWM_left, speed);   // Set right motor speed
}

void turnRight(int speed) {
  // Right motor backward, Left motor forward
  digitalWrite(R_EN_right, HIGH);
  digitalWrite(L_EN_right, HIGH);
  digitalWrite(R_EN_left, HIGH);
  digitalWrite(L_EN_left, HIGH);

  analogWrite(R_PWM_right, speed);
  analogWrite(L_PWM_right, 0);   
  analogWrite(R_PWM_left, 0);       
  analogWrite(L_PWM_left, speed);   
}

void turnLeft(int speed) {
  // Right motor forward, Left motor backward
  digitalWrite(R_EN_right, HIGH);
  digitalWrite(L_EN_right, HIGH);
  digitalWrite(R_EN_left, HIGH);
  digitalWrite(L_EN_left, HIGH);

  analogWrite(R_PWM_right, 0);
  analogWrite(L_PWM_right, speed);   
  analogWrite(R_PWM_left, speed);       
  analogWrite(L_PWM_left, 0);
}

void stopMotors() {
  // Stop both motors
  digitalWrite(R_EN_right, LOW);
  digitalWrite(L_EN_right, LOW);
  analogWrite(R_PWM_right, 0);

  digitalWrite(R_EN_left, LOW);
  digitalWrite(L_EN_left, LOW);
  analogWrite(L_PWM_left, 0);
}
