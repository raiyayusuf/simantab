#include <ESP32Servo.h>

const int servoPin = 19;

Servo myservo;

int safePos = 0;
int dangerPos = 90;

void setup() {
  Serial.begin(9600);

  myservo.attach(servoPin);
  myservo.write(safePos);

  Serial.println("=== Servo ESP32 ===");
  Serial.print("Safe position: ");
  Serial.println(safePos);
  Serial.print("Danger position: ");
  Serial.println(dangerPos);
  Serial.println("-------------------");
}

void loop() {
  Serial.println("SAFE - posisi 0");
  safe();
  delay(3000);

  Serial.println("DANGER - posisi 90");
  danger();
  delay(3000);
}

void safe() {
  myservo.write(safePos);
}

void danger() {
  myservo.write(dangerPos);
}