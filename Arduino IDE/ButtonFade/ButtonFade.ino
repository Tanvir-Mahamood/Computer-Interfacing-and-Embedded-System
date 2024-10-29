/*
Design a system with a LED and a Button.
As button is pressed, brightness of LED increases
*/
const int LED = PA0;
const int BUTTON = PA2;

boolean lastButton = LOW;
boolean currentButton = LOW;

int del = 0, val;

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
  currentButton = debounce(lastButton);
  if(lastButton == LOW && currentButton == HIGH) del += 1;
  if(del < 11) analogWrite(LED, del*25);
  else del = 0;

  lastButton = currentButton;
}
