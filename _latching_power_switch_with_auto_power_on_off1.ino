const int buttonPin = 2;    // Pushbutton on digital pin 2
const int latchPin = 5;     // Transistor base for MOSFET control
const int pwmPin = 9;       // PWM pin for first LED brightness

const unsigned long onDuration = 10000;  // 10 seconds on
const unsigned long offDuration = 5000;  // 5 seconds off
unsigned long lastButtonPress = 0;
bool isPowered = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  digitalWrite(latchPin, LOW);  // MOSFET LED off initially
  analogWrite(pwmPin, 0);       // First LED off initially
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !isPowered) {
    isPowered = true;
    lastButtonPress = millis();
    digitalWrite(latchPin, HIGH);  // Turn on MOSFET LED
    analogWrite(pwmPin, 64);       // Set first LED to 25% brightness
    Serial.println("Power ON");
  }
  if (isPowered && millis() - lastButtonPress >= onDuration) {
    digitalWrite(latchPin, LOW);   // Turn off MOSFET LED
    analogWrite(pwmPin, 0);        // Turn off first LED
    isPowered = false;
    lastButtonPress = millis();
    Serial.println("Power OFF");
  }
  if (!isPowered && millis() - lastButtonPress >= offDuration) {
    isPowered = true;
    lastButtonPress = millis();
    digitalWrite(latchPin, HIGH);  // Turn on MOSFET LED
    analogWrite(pwmPin, 64);       // Set first LED to 25% brightness
    Serial.println("Auto Power ON");
  }
}