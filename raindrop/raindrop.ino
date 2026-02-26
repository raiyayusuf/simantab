// raindrop test
#define raindropPin A0

int rainValue = 0;
String rainStatus = "";

const int DRY_THRESHOLD = 900;
const int DRIZZLE_THRESHOLD = 600;

void setup() {
  Serial.begin(9600);
  pinMode(raindropPin, INPUT);
  Serial.println("Raindrop Sensor Ready!");
}

void loop() {
  checkRain();
  delay(500);
}

void checkRain() {
  rainValue = analogRead(raindropPin);
  
  if (rainValue > DRY_THRESHOLD) {
    rainStatus = "KERING";
  } else if (rainValue > DRIZZLE_THRESHOLD) {
    rainStatus = "GRIMIS";
  } else {
    rainStatus = "HUJAN DERAS";
  }
  
  Serial.print("Nilai: ");
  Serial.print(rainValue);
  Serial.print(" | Status: ");
  Serial.println(rainStatus);
}