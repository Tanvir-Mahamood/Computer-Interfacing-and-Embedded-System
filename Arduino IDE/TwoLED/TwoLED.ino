/*
Make a system with 2 LED having different blinking rate.
*/

const int LED1 = PA0;
const int LED2 = PA1;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

/*
LED1 : (1 1 0 0 1 1 0 0 1 1 0 0) ...
LED2 : (1 1 1 0 0 0 1 1 1 0 0 0) ...
*/
void loop() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(500);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(1000);
}
