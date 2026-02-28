#include <Servo.h>

// --- Updated Pin Definitions ---
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 8;
const int IN4 = 9;
const int ENB = 3; // Using Pin 3 as we discussed

const int trigPin = A0;
const int echoPin = A1;
const int servoPin = 11;

Servo myServo;
int distance = 0;

// --- Adjusted Speed ---
int carSpeed = 120; // Lowered from 150/255 for better control
const int stopDistance = 25; 

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(90); 
  delay(2000);
}

void loop() {
  distance = getDistance();

  if (distance <= stopDistance) {
    stopMotors();
    delay(300);
    moveBackward(); // This will now correctly move away from the wall
    delay(500);
    stopMotors();
    
    // Scan left/right logic remains the same...
    int rightDist = lookRight();
    int leftDist = lookLeft();

    if (rightDist >= leftDist) {
      turnRight();
    } else {
      turnLeft();
    }
    delay(500);
    stopMotors();
  } else {
    moveForward(); // This will now correctly move toward the wall
  }
}

// --- Direction Logic Swapped Below ---

void moveForward() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  // Logic flipped: changed HIGH/LOW to move toward sensor direction
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  // Logic flipped: changed LOW/HIGH to move away from sensor direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Note: If the car spins in place instead of turning, 
// you may need to flip the logic in turnLeft/turnRight too!

void turnLeft() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

int lookRight() {
  myServo.write(30); 
  delay(500);
  int d = getDistance();
  myServo.write(90); 
  return d;
}

int lookLeft() {
  myServo.write(150); 
  delay(500);
  int d = getDistance();
  myServo.write(90); 
  return d;
}

//
//// For Continuous Flow Code
//#include <Servo.h>
//
//// --- Pin Definitions ---
//const int ENA = 5;
//const int IN1 = 6;
//const int IN2 = 7;
//const int IN3 = 8;
//const int IN4 = 9;
//const int ENB = 3; 
//
//const int trigPin = A0;
//const int echoPin = A1;
//const int servoPin = 11;
//
//Servo myServo;
//int distance = 0;
//
//// --- Settings ---
//int carSpeed = 100;        // Slightly adjusted for better torque
//const int stopDistance = 15; // Only stop if obstacle is within 15cm
//
//void setup() {
//  pinMode(ENA, OUTPUT);
//  pinMode(IN1, OUTPUT);
//  pinMode(IN2, OUTPUT);
//  pinMode(IN3, OUTPUT);
//  pinMode(IN4, OUTPUT);
//  pinMode(ENB, OUTPUT);
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
//
//  myServo.attach(servoPin);
//  myServo.write(90); 
//  delay(1000);
//}
//
//void loop() {
//  distance = getDistance();
//
//  if (distance > 0 && distance <= stopDistance) {
//    // OBSTACLE DETECTED: Start avoidance sequence
//    stopMotors();
//    delay(200);
//    
//    // Back up slightly to give room for the turn
//    moveBackward();
//    delay(400);
//    stopMotors();
//    
//    // Look around
//    int rightDist = lookRight();
//    delay(200);
//    int leftDist = lookLeft();
//    delay(200);
//
//    if (rightDist >= leftDist) {
//      turnRight();
//      delay(500); // Adjust this delay for a perfect 90-degree turn
//    } else {
//      turnLeft();
//      delay(500);
//    }
//    stopMotors();
//    delay(200);
//  } 
//  else {
//    // NO OBSTACLE: Keep moving forward
//    moveForward();
//  }
//}
//
//// --- Movement Functions ---
//
//void moveForward() {
//  analogWrite(ENA, carSpeed);
//  analogWrite(ENB, carSpeed);
//  digitalWrite(IN1, LOW);
//  digitalWrite(IN2, HIGH);
//  digitalWrite(IN3, LOW);
//  digitalWrite(IN4, HIGH);
//}
//
//void moveBackward() {
//  analogWrite(ENA, carSpeed);
//  analogWrite(ENB, carSpeed);
//  digitalWrite(IN1, HIGH);
//  digitalWrite(IN2, LOW);
//  digitalWrite(IN3, HIGH);
//  digitalWrite(IN4, LOW);
//}
//
//void turnLeft() {
//  analogWrite(ENA, carSpeed);
//  analogWrite(ENB, carSpeed);
//  digitalWrite(IN1, HIGH); // Left side backward
//  digitalWrite(IN2, LOW);
//  digitalWrite(IN3, LOW);  // Right side forward
//  digitalWrite(IN4, HIGH);
//}
//
//void turnRight() {
//  analogWrite(ENA, carSpeed);
//  analogWrite(ENB, carSpeed);
//  digitalWrite(IN1, LOW);  // Left side forward
//  digitalWrite(IN2, HIGH);
//  digitalWrite(IN3, HIGH); // Right side backward
//  digitalWrite(IN4, LOW);
//}
//
//void stopMotors() {
//  digitalWrite(IN1, LOW);
//  digitalWrite(IN2, LOW);
//  digitalWrite(IN3, LOW);
//  digitalWrite(IN4, LOW);
//}
//
//int getDistance() {
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  long duration = pulseIn(echoPin, HIGH);
//  int d = duration * 0.034 / 2;
//  return (d == 0) ? 400 : d; // Returns 400 if no echo
//}
//
//int lookRight() {
//  myServo.write(30); 
//  delay(400);
//  int d = getDistance();
//  myServo.write(90); 
//  return d;
//}
//
//int lookLeft() {
//  myServo.write(150); 
//  delay(400);
//  int d = getDistance();
//  myServo.write(90); 
//  return d;
//}
