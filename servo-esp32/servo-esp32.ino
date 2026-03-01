#include <ESP32Servo.h>

const int servoPin1 = 13;
const int servoPin2 = 12;

Servo myservo1;
Servo myservo2;

// Servo 1
int safePos1 = 0;
int dangerPos1 = 90;

// Servo 2
int safePos2 = 180;
int dangerPos2 = 90;

void setup() {
  Serial.begin(9600);

  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
  
  myservo1.write(safePos1);
  myservo2.write(safePos2);

  Serial.println("=== Servo ESP32 (2 Servo) ===");
  Serial.print("Servo1 pin: GPIO ");
  Serial.println(servoPin1);
  Serial.print("  Safe: ");
  Serial.print(safePos1);
  Serial.print(" | Danger: ");
  Serial.println(dangerPos1);
  
  Serial.print("Servo2 pin: GPIO ");
  Serial.println(servoPin2);
  Serial.print("  Safe: ");
  Serial.print(safePos2);
  Serial.print(" | Danger: ");
  Serial.println(dangerPos2);
  Serial.println("-------------------------------");
}

void loop() {
  Serial.println("SAFE mode");
  safe();
  delay(3000);

  Serial.println("DANGER mode");
  danger();
  delay(3000);
}

void safe() {
  myservo1.write(safePos1);
  myservo2.write(safePos2);
  Serial.print("Servo1: ");
  Serial.print(safePos1);
  Serial.print(" | Servo2: ");
  Serial.println(safePos2);
}

void danger() {
  myservo1.write(dangerPos1);
  myservo2.write(dangerPos2);
  Serial.print("Servo1: ");
  Serial.print(dangerPos1);
  Serial.print(" | Servo2: ");
  Serial.println(dangerPos2);
}