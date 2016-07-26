# Playing with a R2R resistor ladder, AKA the quick DAC.

## Playing with a 22kO R ladder

An R–2R Ladder is a simple and inexpensive way to perform digital-to-analog conversion, using repetitive arrangements of precise resistor networks in a ladder-like configuration. A string resistor ladder implements the non-repetitive reference network.

![](/include/images/notes/ladder.png)

Let's try to see if we can do some signal with it!

# Playing with it

What does it look like?

![](/include/images/notes/DSC_0659.JPG)

Playing with the variant 2 of the code below (increase, bit by bit, over 6 bits)

![](/include/images/notes/DSC_0661.JPG)

# Limitations

With the variant 2, the quickest signal is at ~5MHz

![](/include/images/notes/DSC_0668.JPG)

But when feeding the ladder, it slows... see characteristic time below

![](/include/images/notes/DSC_0667.JPG)

# Conclusions

Let's try something with the variant 1, feeding the Arduino a translation of one image! It has 28K of flash, let' remove 2k for code, 26kb, using 6-bit accuracy, is 64, leaves 4k points.

# Trinket pro codes

## Variant 1

The quickest so far

	void setup()
	 {
	  DDRC = 255; // set PORTD (Pins 0-7) to outputs
	  PORTC = 0;  // Set all pins LOW
	 }
	 
	void loop() {
	   PORTC = B0000000;   
	   PORTC = B0000001;   
	   PORTC = B0000010;   
	   PORTC = B0000011;   
	   PORTC = B0000100;   
	   PORTC = B0000101;   
	   PORTC = B0000110;   
	   PORTC = B0000111;
	   PORTC = B0001000;   
	   PORTC = B0001001;   
	   PORTC = B0001010;   
	   PORTC = B0001011;   
	   PORTC = B0001100;   
	   PORTC = B0001101;   
	   PORTC = B0001110;   
	   PORTC = B0001111;
	}


## Variant 2

Using autoincrement of PORTC:

	void setup()
	{
	  DDRC = 255; // set PORTD (Pins 0-7) to outputs
	  PORTC = 0;  // Set all pins LOW
	}
	 
	void loop() {
	   PORTC++;
	}
