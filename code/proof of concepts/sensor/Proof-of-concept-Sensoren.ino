const int sensor [] = {A0, A1, A9, A8, A7, A6};

void setup() {
  Serial.begin(9600);


}

void loop() {
  
  Serial.print("Values: ");
  for (int i = 0; i<6; i++)
  {
    Serial.print(analogRead(sensor[i]));
    Serial.print(" ");
  }
  Serial.println();
  
  delay(1000);

}
