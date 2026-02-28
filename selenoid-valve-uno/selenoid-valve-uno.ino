// Solenoid Valve Test 
const int relayPin = 13;  

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  
  
  Serial.begin(9600);
  Serial.println("Program Solenoid Valve 12V dengan Relay");
}

void loop() {
  Serial.println("Solenoid ON");
  digitalWrite(relayPin, LOW);  
  delay(3000);          

  Serial.println("Solenoid OFF");
  digitalWrite(relayPin, HIGH); 
  delay(3000);               
}