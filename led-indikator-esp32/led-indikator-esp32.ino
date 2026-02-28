// LED Indicator R Y G 

const int redPin = 14;   
const int yellowPin = 27; 
const int greenPin = 26;  

void setup() {
  Serial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  // set mati
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  
  Serial.println("LED Indicator R Y G");
}

void loop() {
  safe();
  delay(2000);
  
  warning();
  delay(2000);
  
  danger();
  delay(2000);
}

void safe() {
  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  Serial.println("Status: SAFE - LED Hijau ON");
}

void warning() {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  Serial.println("Status: WARNING - LED Kuning ON");
}

void danger() {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  Serial.println("Status: DANGER - LED Merah ON");
}