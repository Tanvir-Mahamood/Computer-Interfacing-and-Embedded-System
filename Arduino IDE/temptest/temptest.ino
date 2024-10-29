const int TMP = PA0;
const int LED = PA1;
int val, temp;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(TMP, INPUT);
}

void loop() {
  val = (analogRead(TMP) * 5) / 4095;
  temp = val * 100;
  for(int i=0; i<temp; i++)
  {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  delay(5000);
}
