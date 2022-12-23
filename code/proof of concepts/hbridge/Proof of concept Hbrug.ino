const int Ain1 = 10;
const int Ain2 = 11;
const int Bin1 = 3;
const int Bin2 = 5;

void setup() {
  // put your setup code here, to run once:
  digitalWrite(Ain1, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin2, LOW);
}

void loop() {
  //Forward1;

  analogWrite(Ain1, 255);
  delay(500);
  digitalWrite(Ain1, LOW);
  delay(50);
  
  //Forward2;

  analogWrite(Bin1, 255);
  delay(500);
  digitalWrite(Bin1, LOW);
  delay(50);

  //Backwards

  analogWrite(Ain2, 255);
  analogWrite(Bin2, 255);

  delay (1000);

  digitalWrite(Ain2, LOW);
  digitalWrite(Bin2, LOW);
  
  delay(50);

  //Speed up

  for(int i=0; i<255; i++)
  {
    analogWrite(Ain1, i);
    analogWrite(Bin1, i);
    delay(20);
  }
  delay(500);

  // Slow Down
  for(int i=255; i>0; i--)
  {
    analogWrite(Ain1, i);
    analogWrite(Bin1, i);
    delay(20);
  }
  //Stop
  digitalWrite(Ain1, LOW);
  digitalWrite(Bin1, LOW);
  delay(2000);
}

