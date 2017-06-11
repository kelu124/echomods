#include <Servo.h>
Servo myServo;


int pos = 14;
int pinServo = 12; //analog pin 12
int pinInterrup = 10; //analog pin 12
int pinLED = 13;
int pinLEDSD = 8;
int LEDStatus = 0;
int LEDStatusSD = 0;
int pinPWM = 9;
int Flag = 0;

void setup() {
  // put your setup code here, to run once:
  //pinMode(1, OUTPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinLEDSD, OUTPUT);
  pinMode(pinServo, OUTPUT);
  pinMode(pinPWM, OUTPUT);

  pinMode(pinInterrup, INPUT);
  myServo.attach(pinServo); //analog pin 12
  myServo.write(pos);


  digitalWrite(pinLEDSD, LEDStatusSD);
  digitalWrite(pinLED, LEDStatus);


  attachInterrupt(2, updatePos, RISING);

  digitalWrite(pinServo, LOW);
  digitalWrite(pinPWM, LOW);


}


void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);

}

void updatePos() {


  LEDStatus = !LEDStatus;
  digitalWrite(pinLED, LEDStatus);
  myServo.write( pos );
  delay(30);
  if (Flag == 3) {
    pos = pos + 1 ;
    if (pos == 75) {
      pos = 14;
    }
    LEDStatusSD = !LEDStatusSD;
    digitalWrite(pinLEDSD, LEDStatusSD);

    Flag = 1;
  } else {
    Flag = Flag + 1;
  }
  delay(30);
  digitalWrite(pinPWM, HIGH);
  delay(40 + pos);
  digitalWrite(pinPWM, LOW);








}

