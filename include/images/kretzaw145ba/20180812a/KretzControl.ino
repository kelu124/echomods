/*
  Author: Kelu124
  Copyright 2018
  Repo:https://github.com/kelu124/echomods/
  Description: Servo control for Matty, used in `20180430a`
  Licence: GNU GPL 2

*/

#include <Servo.h>
#include <SPI.h>
#include <Wire.h>


unsigned int COUNTER = 0;
int DIR = PA4;
int STEP = PB4;
int LED = PA15;


void setup()
{

  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(DIR, LOW);  //
  digitalWrite(STEP, LOW);  //

  SPI.begin ();
  SPI.setBitOrder(MSBFIRST);

}

void loop()
{


  digitalWrite(STEP, HIGH);
  for (int i = 0; i <= 25; i++) {
    SPI.transfer(255); //
    SPI.transfer(COUNTER);
  }
  
  digitalWrite(STEP, LOW);
  for (int i = 0; i <= 25; i++) {
    SPI.transfer(0); //
    SPI.transfer(COUNTER);
  }

  COUNTER = COUNTER + 1;

}

