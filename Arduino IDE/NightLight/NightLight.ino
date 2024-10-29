const int LED=PA10; // White LED Anode on pin PA0 (PWM)
const int LIGHT=PA0; // Light Sensor on Analog Pin PA1
const int MIN_LIGHT=200; // Minimum Expected light value
const int MAX_LIGHT=900; // Maximum Expected Light value
int val ; // Variable to hold the analog reading

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LIGHT,INPUT);// Set White LED pin as output
}
void loop() {
//  digitalWrite(WLED,HIGH);
  val = analogRead(LIGHT); // Read the light sensor
  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0); // Map the light reading
  val = constrain(val, 0, 255); // Constrain light value
  analogWrite(LED, 255); // Control the White LED
}
