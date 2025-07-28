int sensorValue = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  sensorValue = analogRead(A0); 
  digitalWrite(13, HIGH);
  delay(sensorValue);

  digitalWrite(13, LOW);
  delay(sensorValue);
}