/*
  SimplePulse (simple way)
  Using the Hackaday Trinket Pro.
  Creates two contiguous pulses one after the other, then sleeps till the next time.
  This example code is in the public domain. Inspired from Blink.
 */


 
void setup() 
{ 
  DDRB = B11111111; // set PORTB (digital 13~8) to outputs 
} 
 
 
void loop() 
{ 

    // Creating the pulse
    PORTB = B00010000;               // Pin 12 = Pon pulse
    __asm__("nop\n\t");		     // wait only
    PORTB = B00100000;               // Pin 13  = pulse negatif
    delayMicroseconds(10);
    //__asm__("nop\n\t""nop\n\t");
    //__asm__("nop\n\t""nop\n\t");
    PORTB = B00000000;
    delayMicroseconds(500);

} 
