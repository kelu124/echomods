/*
  SimplePulse (simple way)
  Using the Hackaday Trinket Pro.
  Creates two contiguous pulses one after the other, then sleeps till the next time.
  This example code is in the public domain. Inspired from Blink.
 */

 
int pos = 60;    // variable to store the servo position 
 
void setup() 
{ 
  DDRB = B11111111; // set PORTB (digital 13~8) to outputs 
} 
 
 
void loop() 
{ 
  for(pos = 60; pos < 120; pos += 1) // goes from 60 degrees to 120 degrees 
  {                                  // in steps of 1 degree 
    PORTB = B00001000;               // Pin 11
    delayMicroseconds(pos);          // microsecondes
    PORTB = B00010000;               // Pin 12 = pulse positif
    __asm__("nop\n\t");
    PORTB = B00100000;               // Pin 13  = pulse negatif
    //delayMicroseconds(1);
    __asm__("nop\n\t""nop\n\t");
    __asm__("nop\n\t""nop\n\t");
    PORTB = B00000000;
  }
} 
