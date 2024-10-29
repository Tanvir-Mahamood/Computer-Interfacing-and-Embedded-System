const int LED = PA0;
const int BUTTON = PA2;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  if(digitalRead(BUTTON) == LOW) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);
}
