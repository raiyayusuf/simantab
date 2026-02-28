volatile long pulseCount;
float calibrationFactor = 4.5; 
float flowRate;
unsigned long oldTime;

void setup() {
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(2), pulseCounter, FALLING);
  
  pulseCount = 0;
  oldTime = millis();
  
  Serial.println("Water Flow Sensor YF-S201");
  Serial.println("Siap membaca aliran air...");
  Serial.println();
}

void loop() {
  if ((millis() - oldTime) > 1000) {
    detachInterrupt(digitalPinToInterrupt(2));
    
    flowRate = (pulseCount / calibrationFactor);
    
    Serial.print("Flow rate: ");
    Serial.print(flowRate);
    Serial.print(" L/min");
    Serial.print("\t Pulse: ");
    Serial.println(pulseCount);
    
    pulseCount = 0;
    oldTime = millis();
    
    attachInterrupt(digitalPinToInterrupt(2), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}