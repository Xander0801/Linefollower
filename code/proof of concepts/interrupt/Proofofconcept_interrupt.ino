volatile boolean LedOn = false; 


void setup() {
    pinMode(13, OUTPUT);
    pinMode(2, INPUT);
    attachInterrupt(1,buttonPressed,RISING);

}

void loop() {
  

}

void buttonPressed()
{
  if (LedOn)
  {
    LedOn = false;
    digitalWrite(13,LOW);
  } 
  else
  {
    LedOn = true;
    digitalWrite(13,HIGH);
  }
}