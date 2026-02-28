const int waterFlowPin = 13;

volatile long pulseCount;
float calibrationFactor = 4.5; 
float flowRate;
unsigned long oldTime;

String flowStatus = "";

// Variable buat threshold 
int normalMax = 149;     // 0 - 149
int hujanMax = 300;      // 149 - 300
// Sisanya > hujanMax = Hujan Deras

void setup() {
  Serial.begin(9600);
  
  pinMode(waterFlowPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(waterFlowPin), pulseCounter, FALLING);
  
  pulseCount = 0;
  oldTime = millis();
  
  Serial.println("Water Flow Sensor YF-S201");
  Serial.println("Siap membaca aliran air...");
  Serial.println();
  
  Serial.print("Threshold: Normal < ");
  Serial.print(normalMax);
  Serial.print(" | Hujan ");
  Serial.print(normalMax + 1);
  Serial.print(" - ");
  Serial.print(hujanMax);
  Serial.print(" | Deras > ");
  Serial.println(hujanMax);
  Serial.println();
}

void loop() {
  if ((millis() - oldTime) > 1000) {
    detachInterrupt(digitalPinToInterrupt(waterFlowPin));
    
    flowRate = (pulseCount / calibrationFactor);
    
    if (pulseCount <= normalMax) {
      flowStatus = "Normal";
    } else if (pulseCount <= hujanMax) {
      flowStatus = "Hujan";
    } else {
      flowStatus = "Hujan Deras";
    }
    
    Serial.print("Flow rate: ");
    Serial.print(flowRate);
    Serial.print(" L/min");
    Serial.print("\t Pulse: ");
    Serial.print(pulseCount);
    Serial.print("\t Status: ");
    Serial.println(flowStatus);
    
    pulseCount = 0;
    oldTime = millis();
    
    attachInterrupt(digitalPinToInterrupt(waterFlowPin), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}