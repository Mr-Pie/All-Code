#define SERVO_PIN         10  // Any pin on the Arduino or Mega will work.
#define FWD_PIN    12
#define BWD_PIN    13
float incomingbyte = 0;

void setup()
{
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(FWD_PIN, INPUT_PULLUP);
  pinMode(BWD_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

int lenMicroSecondsOfPeriod = 25 * 1000; // 20 milliseconds (ms)
int len = 1000; // 1.0 ms is 0 degrees**MOD THIS VALUE TO CHANGE POSITION**
int lenMicroSecondsOfPulse = 0;
float currentposition = 0;

void loop()
{
  if(digitalRead(FWD_PIN) == LOW)
  {
  lenMicroSecondsOfPulse = 1800;
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(lenMicroSecondsOfPulse);
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(lenMicroSecondsOfPeriod - lenMicroSecondsOfPulse); 
  delay(50);
  Serial.print("AntiClockwise:");
  Serial.print("\n");
  }
  if(digitalRead(BWD_PIN) == LOW)
  {
  currentposition = 0;
  lenMicroSecondsOfPulse = currentposition*len;
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(lenMicroSecondsOfPulse);
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(lenMicroSecondsOfPeriod - lenMicroSecondsOfPulse); 
  
  delay(50);
  Serial.print("Clockwise:");
  Serial.print("\n");
  }

 // Servos work by sending a 20 ms pulse.  
 // 1.0 ms at the start of the pulse will turn the servo to the 0 degree position
 // 1.5 ms at the start of the pulse will turn the servo to the 90 degree position 
 // 2.0 ms at the start of the pulse will turn the servo to the 180 degree position 
 // Turn voltage high to start the period and pulse
 //digitalWrite(SERVO_PIN, HIGH);

 // Delay for the length of the pulse
// delayMicroseconds(lenMicroSecondsOfPulse);

 // Turn the voltage low for the remainder of the pulse
// digitalWrite(SERVO_PIN, LOW);

 // Delay this loop for the remainder of the period so we don't
 // send the next signal too soon or too late
// delayMicroseconds(lenMicroSecondsOfPeriod - lenMicroSecondsOfPulse); 
// delay(100);

}
