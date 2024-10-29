/*
Design a system with a LED and a Button.
As the button is pressed, the blinking rate of
LED increases.
*/

const int LED = PA0;
const int BUTTON = PA2;

boolean lastButton = LOW;
boolean currentButton = LOW;

int del = 10; // 10 times, each time is equal to 100ms

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
  if(lastButton == LOW && currentButton == HIGH) del -= 1;
  lastButton = currentButton;

  digitalWrite(LED, HIGH);
  for(int i=0; i<max(del,0); i++) {
    delay(100);

    currentButton = debounce(lastButton);
    if(lastButton == LOW && currentButton == HIGH) del -= 1;
    lastButton = currentButton;
  }
  

  digitalWrite(LED, LOW);
  for(int i=0; i<max(del,0); i++) {
    delay(100);

    currentButton = debounce(lastButton);
    if(lastButton == LOW && currentButton == HIGH) del -= 1;
    lastButton = currentButton;
  }
}
