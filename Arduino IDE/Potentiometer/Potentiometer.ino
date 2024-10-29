const int LED = PB0;
const int POT = PA0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);
}

void loop() {
  int val = analogRead(POT);
  val = map(val, 0, 4095, 0, 255);
  val = constrain(val, 0, 255);
  analogWrite(LED,val);
}
