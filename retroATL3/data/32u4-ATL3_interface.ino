/*


The clock signal goes to pinClock (11) and each Top from the probe goes to pinTop.

Both are recorded on track GPIO21 and PWM (GPIO6) from the Raspberry pi, using the ADC code.


test1 and test2 do not have the nop instructions between pin11 output
test3 and test4 have.

#define SAMPLE_SIZE 	1000000 (both in scope.c -- the module, and in read.cpp) 

*/


int pos = 0;
int pinClock = 11; //analog pin 12
int pinTop = 12; //analog pin 12

int pinLED = 13;
int pinLEDSD = 8;

int LEDStatus = 0;
int LEDStatusSD = 0;


void setup() {

  pinMode(pinLED, OUTPUT);
  pinMode(pinLEDSD, OUTPUT);
  pinMode(pinClock, OUTPUT);
  pinMode(pinTop, OUTPUT);

  digitalWrite(pinLEDSD, LEDStatusSD);
  digitalWrite(pinLED, LEDStatus);

  attachInterrupt(2, updatePos, RISING);



}


void loop() {
  // put your main code here, to run repeatedly:
  StreamPos();
}

void updatePos() {

  pos = 0;
  digitalWrite(pinTop, HIGH);
  LEDStatus = !LEDStatus;
  digitalWrite(pinLED, LEDStatus);
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinTop, LOW);

}

void StreamPos() {
  pos = pos + 1;
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, HIGH && (pos & B00100000));
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, LOW);
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, HIGH && (pos & B00010000));
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, LOW);
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, HIGH && (pos & B00001000));
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, LOW);
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, HIGH && (pos & B00000100));
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, LOW);
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, HIGH && (pos & B00000010));
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, LOW);
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, HIGH && (pos & B00000001));
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(pinClock, LOW);
    __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");

      __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
      __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
      __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
      __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  __asm__("nop\n\t");
}

