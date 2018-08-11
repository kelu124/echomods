/*
  Author: Kelu124
  Copyright 2018
  Repo:https://github.com/kelu124/echomods/
  Description: Servo control for Matty, used in `20180430a` 
  Licence: GNU GPL 2

*/

//#include <libmaple/dac.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>

/*
  Testing servo control for 60 degrees of acquisition
*/

const int  TRIG_PIN = PB5;

Servo myservo;
uint32_t pos = 60;
int servoPin = PC7;

int led3 = PA15;



void emulator() {

  digitalWrite(led3, !digitalRead(led3));

  // let's repeat 3 pulses
  digitalWrite(SS, LOW);
  SPI.transfer(pos); //
  digitalWrite(SS, HIGH);
  digitalWrite(SS, LOW);
  SPI.transfer(pos); //
  digitalWrite(SS, HIGH);
  digitalWrite(SS, LOW);
  SPI.transfer(pos); //
  digitalWrite(SS, HIGH);

  delay(1); // wait for 1 ms for the board to do its acquisition

  myservo.write(pos);

  pos++;

}

void setup()
{

  digitalWrite(SS, HIGH);  // ensure SS stays high // PA4 par default
  SPI.begin ();
  SPI.setBitOrder(MSBFIRST);

  pinMode(TRIG_PIN, INPUT_PULLUP);
  attachInterrupt(TRIG_PIN, emulator, RISING); // update the servo position at each Poff end


  myservo.attach(servoPin);
  myservo.write(60); // initalize at 60

  pinMode(led3, OUTPUT);

}

void loop()
{
  /*
	 Nothing is needed here
  */

}

