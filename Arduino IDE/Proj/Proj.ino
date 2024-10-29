/*
First LED will blink and you have to count no. of blinkings.
In response, you will press button same times as you counted blinking.
If no. of button pressed matches with no. blinking, the system will blink
LED 2 times as correct answer. Otherwise it will blink LED 1 times as 
wrong answer.
*/
const int LED = PA0;
const int Button = PA2;

boolean lastButton = LOW;
boolean currentButton = LOW;

int count = 0, play = 0, temp;
boolean flag = false;

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

void blink(int n)
{
  for(int i=0; i<n; i++)
  {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}

void loop() {
  if(!flag)
  {
    temp = random(5);
    blink(temp);
  }
  flag = true;
  
  currentButton = debounce(lastButton);

  // wait for 2s to understand input is completed.
  while(play < 20 && currentButton == LOW && lastButton == LOW)
  {
    delay(100);
    lastButton = currentButton;
    currentButton = debounce(lastButton);
    play += 1;
  }

  if(play >= 20) // input is completed
  {
    if(count == temp) blink(2); // Right Answer
    else blink(1);              // Wrong answer
    
    count = 0;
    play = 0;
    flag = false;
    delay(5000); // wait 5s for next round.
  }


  if(flag && currentButton == LOW && lastButton == HIGH)
  {
    count += 1;
    play = 0;
  }
  else play = 0;

  lastButton = currentButton;
}
