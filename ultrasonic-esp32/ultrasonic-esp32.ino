#define TRIG_PIN 5
#define ECHO_PIN 18

// mode 1 = cek tempat ultrasonic di pasang
// mode 2 = pengukuran
int mode = 2; 

int safeMax = 3;
int warningMax = 6;

// set tinggi ultrasonic setelah mode 1 untuk pengukuran
float tinggiSensor = 19.28;

float tinggiAir = 0.0;
String statusAir = "";

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println("=== Ultrasonic Sungai Prototype ===");
  Serial.print("Mode: ");
  Serial.println(mode);
  Serial.println("-----------------------------------");
  
  if (mode == 1) {
    Serial.println("MODE 1: Kalibrasi Sensor");
  } else if (mode == 2) {
    Serial.println("MODE 2: Monitoring Tinggi Air");
    Serial.print("Safe < ");
    Serial.print(safeMax);
    Serial.print(" cm | Warning ");
    Serial.print(safeMax);
    Serial.print("-");
    Serial.print(warningMax);
    Serial.print(" cm | Danger > ");
    Serial.println(warningMax);
    Serial.println("-----------------------------------");
  }
  Serial.println();
}

void loop() {
  if (mode == 1) {
    mode1_kalibrasi();
    delay(1000);
  } else if (mode == 2) {
    mode2_monitoring();
    delay(500);
  }
}

float bacaJarak() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void mode1_kalibrasi() {
  float jarak = bacaJarak();
  tinggiSensor = jarak;
  
  Serial.print("Jarak sensor ke dasar: ");
  Serial.print(tinggiSensor);
  Serial.println(" cm");
  Serial.println("-----------------------------------");
}

void mode2_monitoring() {
  float jarak = bacaJarak();
  tinggiAir = tinggiSensor - jarak;
  
  if (tinggiAir < 0) tinggiAir = 0;
  
  if (tinggiAir <= safeMax) {
    statusAir = "SAFE";
  } else if (tinggiAir <= warningMax) {
    statusAir = "WARNING";
  } else {
    statusAir = "DANGER";
  }
  
  Serial.print("Tinggi air: ");
  Serial.print(tinggiAir);
  Serial.print(" cm | Status: ");
  Serial.println(statusAir);
}