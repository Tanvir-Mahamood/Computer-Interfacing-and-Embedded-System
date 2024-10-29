const int LED = PA0;
const int Button = PA2;

boolean lastButton = LOW;
boolean currentButton = LOW;

int count = 0;
int play = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT);
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(Button);
  if(last != current)
  {
    delay(5);
    current = digitalRead(Button);
  }
  return current;
}

void loop() {
  currentButton = debounce(lastButton);

  if(currentButton == LOW && lastButton == HIGH)
  {
    count += 1;
    play = 0;
  }
  else if(currentButton == LOW && lastButton == LOW)
  {
    delay(100);
    play += 1;
  }

  lastButton = currentButton;


  if(play >= 30) // input is completed
  {
    for(int i=0; i<count; i++)
    {
      digitalWrite(LED, HIGH);
      delay(1000);
      digitalWrite(LED, LOW);
      delay(1000);
    }
    count = 0;
    play = 0;
  }

}
