#include <QTRSensors.h> 

QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

//PID's
float Kp = 0.17; 
float Ki = 0.010; 
float Kd = 8; 

int P;
int I;
int D;


boolean onoff = false;

//Speed param's
const uint8_t maxspeeda = 150;
const uint8_t maxspeedb = 150;
const uint8_t basespeeda = 70;
const uint8_t basespeedb = 70;


//Pinnen H-brug
int aphase = 11;
int aenbl = 10;
int bphase = 5;
int benbl = 3;

//Pinnen Knoppen
int buttoncalibrate = 7; 
int buttonstart = 2;



void setup() {
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A9, A8, A7, A6}, SensorCount);

  Serial.begin(9600);  

  pinMode(aphase, OUTPUT);
  pinMode(aenbl, OUTPUT);
  pinMode(bphase, OUTPUT);
  pinMode(benbl, OUTPUT);
  pinMode(13, OUTPUT);
 
  delay(500);
  
//Calibreren voor starten programma
  boolean Ok = false;
  while (Ok == false) { 
    if(digitalRead(buttoncalibrate) == HIGH) {
      digitalWrite(13, HIGH);
      calibration(); 
      digitalWrite(13, LOW);
      Ok = true;
    }
  }
  forward_brake(0,0,0,0); 
}


void calibration() {
  
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
}


//Start/stop
void loop() {
  if(digitalRead(buttonstart) == HIGH) {
    onoff =! onoff;
    if(onoff == false) {
      delay(1000);
    }
    else {
      delay(50);
    }
  }
  if (onoff == true) {
    PID_control();
  }
  else {
    forward_brake(0,0,0,0); 
  }
}

//Snelheden doorsturen
void forward_brake(int posa, int posb, int posaa, int posbb) {

  analogWrite(aphase, posaa);
  analogWrite(bphase, posbb);
  analogWrite(aenbl, posa);
  analogWrite(benbl, posb);
}

//PID Control
void PID_control() {
  uint16_t position = qtr.readLineBlack(sensorValues); 
  int error = 2500 - position; 

  Serial.print("position ");
  Serial.println(position);

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  int motorspeed = P*Kp + I*Ki + D*Kd; 

  
  int motorspeeda = basespeeda - motorspeed;
  int motorspeedb = basespeedb + motorspeed;
  int motorspeedaa = 0;
  int motorspeedbb = 0;
  
  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeedaa = 25;
    motorspeeda = 0;
  }
  else{motorspeedaa = 0;}

  if (motorspeedb < 0) {
    motorspeedbb = 25;
    motorspeedb = 0;
  } 
  else{motorspeedbb = 0;}

  forward_brake(motorspeeda, motorspeedb, motorspeedaa, motorspeedbb);
}
