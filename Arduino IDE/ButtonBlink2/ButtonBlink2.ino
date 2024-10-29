/*
Design a system with a LED and a Button.
As the button is pressed, the blinking rate of
LED increases and then decreases
*/

const int LED = PA0;
const int BUTTON = PA2;

boolean lastButton = LOW;
boolean currentButton = LOW;

int del = 1000; // ms
int sign = -1;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if(last != current)
  {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  if(digitalRead(BUTTON) == HIGH) del = del + 100*sign;
  
  digitalWrite(LED, HIGH);
  del = max(del, 0);
  if(del == 0) sign = +1;
  else if(del >= 1000) sign = -1;
  delay(del);

  if(digitalRead(BUTTON) == HIGH) del = del + 100*sign;
  digitalWrite(LED, LOW);
  del = max(del, 0);
  if(del == 0) sign = +1;
  else if(del >= 1000) sign = -1;
  delay(del);
}
