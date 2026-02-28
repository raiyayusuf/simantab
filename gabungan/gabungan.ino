#define BLYNK_TEMPLATE_ID "TMPL6UZBHTEB7"
#define BLYNK_TEMPLATE_NAME "ADAPUBE Ada Alat Deteksi Puting Beliung"
#define BLYNK_AUTH_TOKEN "FcJ4KPI0BSC2eUzt4jiIzZUSasw9MpwX"

#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

// ========== KONFIGURASI PIN ==========
const int sensorPin = 12;          // Optocoupler
const int buzzer = 13;              // Buzzer
#define DHTPIN 14                   // DHT11
#define DHTTYPE DHT11

// ========== OLED ==========
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ========== DHT ==========
DHT dht(DHTPIN, DHTTYPE);

// ========== WIFI ==========
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NOOG";               // Ganti dengan WiFi lo
char pass[] = "rahasialah";          // Ganti dengan password WiFi lo

// ========== VARIABEL GLOBAL ==========
volatile unsigned long pulseCount = 0;
unsigned long lastPulseCount = 0;
unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 1000;

float temperatureReadings[15];
int currentIndex = 0;

WidgetLED led1(V4);
WidgetLED led2(V1);

// ========== INTERRUPT ==========
void IRAM_ATTR handleInterrupt() {
  pulseCount++;
}

// ========== SETUP ==========
void setup() {
  Serial.begin(9600);

  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, RISING);

  dht.begin();

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal");
    for (;;);
  }
  display.clearDisplay();
  display.display();

  // Koneksi Blynk
  Blynk.begin(auth, ssid, pass);
}

// ========== LOOP UTAMA ==========
void loop() {
  Blynk.run();
  tampilkanData();
}

// ========== FUNGSI TAMPILAN ==========
void tampilkanData() {
  unsigned long currentMillis = millis();

  // Baca suhu dan kelembaban
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Gagal baca DHT");
    return;
  }

  // Kirim ke Blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  // Hitung perubahan suhu tiap 15 detik
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    temperatureReadings[currentIndex] = t;
    currentIndex = (currentIndex + 1) % 15;

    if (currentIndex == 0) {
      float temperatureChange = temperatureReadings[14] - temperatureReadings[0];
      Serial.print("Perubahan suhu: ");
      Serial.print(temperatureChange);
      Serial.println(" C");
      Blynk.virtualWrite(V2, temperatureChange);
    }
  }

  // Hitung kecepatan angin tiap 1 detik
  if (currentMillis - lastMillis >= 1000) {
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    unsigned long pulseDiff = pulseCount - lastPulseCount;
    float windSpeed = (float)pulseDiff / 20.0 * 10.0; // 20 pulsa/putaran * 10 = km/jam

    // Kirim ke Blynk
    Blynk.virtualWrite(V3, windSpeed);

    // Update OLED
    display.clearDisplay();

    // Logo bitmap (asumsi ada)
    // display.drawBitmap(0, 0, myBitmap, 128, 64, WHITE);

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(50, 0);
    display.print("Angin (km/j)");
    display.setTextSize(2);
    display.setCursor(50, 10);
    display.print(windSpeed);

    // Status angin
    display.setTextSize(1);
    display.setCursor(0, 35);
    display.print("Status: ");
    display.setCursor(0, 45);

    if (windSpeed < 1.0) {
      display.print("TENANG");
    } else if (windSpeed < 6.0) {
      display.print("SEDIKIT TENANG");
    } else if (windSpeed < 12.0) {
      display.print("SEDIKIT HEMBUSAN");
    } else if (windSpeed < 20.0) {
      display.print("HEMBUSAN PELAN");
    } else if (windSpeed < 30.0) {
      display.print("HEMBUSAN SEDANG");
    } else if (windSpeed < 40.0) {
      display.print("HEMBUSAN SEJUK");
    } else if (windSpeed < 51.0) {
      display.print("HEMBUSAN KUAT");
    } else if (windSpeed < 62.0) {
      display.print("MENDEKATI KENCANG");
    } else if (windSpeed < 75.0) {
      display.print("KENCANG");
    } else if (windSpeed < 88.0) {
      display.print("KENCANG SEKALI");
    } else if (windSpeed < 102.0) {
      display.print("BADAI");
    } else if (windSpeed < 118.0) {
      display.print("BADAI DAHSYAT");
    } else {
      display.print("BADAI TOPAN");
    }

    display.display();

    // Alarm buzzer
    if (windSpeed >= 75.0) {
      led1.on();
      for (int i = 0; i < 3; i++) {
        digitalWrite(buzzer, HIGH); delay(350);
        digitalWrite(buzzer, LOW); delay(150);
      }
    } else {
      led1.off();
    }

    // Reset interrupt
    lastMillis = currentMillis;
    lastPulseCount = pulseCount;
    attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, RISING);
  }
}