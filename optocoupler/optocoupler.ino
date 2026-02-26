// optocoupler test
#define optocouplerPin 2
#define slotsPerRev 20

volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;
float rpm = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(optocouplerPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(optocouplerPin), countPulse, FALLING);
  lastTime = millis();
}

void loop() {
  calculateRPM();
}

void countPulse() {
  pulseCount++;
}

void calculateRPM() {
  if (millis() - lastTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(optocouplerPin));
    
    rpm = (pulseCount * 60.0) / slotsPerRev;
    Serial.print("RPM: ");
    Serial.println(rpm);
    
    pulseCount = 0;
    attachInterrupt(digitalPinToInterrupt(optocouplerPin), countPulse, FALLING);
    lastTime = millis();
  }
}