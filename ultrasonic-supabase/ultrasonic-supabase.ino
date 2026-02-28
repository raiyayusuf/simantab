// ultrasonic test - supabase

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define WIFI_SSID "R.66 (Lab Elka Atas A)"
#define WIFI_PASSWORD "ayosinau"
#define SUPABASE_URL "https://jhplwycvxybedmcbhkrv.supabase.co"
#define SUPABASE_KEY "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImpocGx3eWN2eHliZWRtY2Joa3J2Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3NzE5MDUwNTcsImV4cCI6MjA4NzQ4MTA1N30.ZQyiMIN6MOMLmbFDcY_Ph1ODptB3XBwYHZGw9sw--0c"

#define TRIG_PIN 5
#define ECHO_PIN 18

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
  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(String(SUPABASE_URL) + "/rest/v1/sensors");
    http.addHeader("apikey", SUPABASE_KEY);
    http.addHeader("Authorization", "Bearer " + String(SUPABASE_KEY));
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Prefer", "return=minimal");
    
    StaticJsonDocument<200> doc;
    doc["jarak"] = distance;
    
    String requestBody;
    serializeJson(doc, requestBody);
    
    int httpResponseCode = http.POST(requestBody);
    
    if (httpResponseCode > 0) {
      Serial.print("Data terkirim ke Supabase. Kode: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Gagal mengirim. Error: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  } else {
    Serial.println("WiFi disconnected");
  }
  
  delay(2000);
}