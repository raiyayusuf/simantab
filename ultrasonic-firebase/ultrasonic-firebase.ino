// ultrasonic test - firebase

#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "R.66 (Lab Elka Atas A)"
#define WIFI_PASSWORD "ayosinau"
#define FIREBASE_HOST "https://dashboard-simantab-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "SUMoICL7soKHp5VEzWKHdAdYZBBetk4NjgBcMD5Q"

#define TRIG_PIN 5
#define ECHO_PIN 18

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (Firebase.setFloat(firebaseData, "/sensor/jarak", distance)) {
    Serial.println("Data terkirim ke Firebase");
  } else {
    Serial.print("Gagal mengirim: ");
    Serial.println(firebaseData.errorReason());
  }
  
  delay(1000);
}