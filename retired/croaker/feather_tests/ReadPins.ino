/*
	Author: Kelu124, Tom Igoe
	Copyright 2016
	Repo:https://github.com/kelu124/echomods/tree/master/croaker
	Contributor:Tom Igoe for his "Analog input, analog output, serial output" 
	Description: Reading pins
	Licence: GNU GPL 2

*/

/*
  

  Reads an analog input pin, maps the result to a range from 0 to
  65535 and uses the result to set the pulse width modulation (PWM) of
  an output pin.  Also prints the results to the serial monitor.

  (You may need to change the pin numbers analogInPin and analogOutPin
  if you're not using a Maple).

  The circuit:
  * Potentiometer connected to analog pin 15.
    Center pin of the potentiometer goes to the analog pin.
    Side pins of the potentiometer go to +3.3V and ground.
  * LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  by 

  ported to Maple
  by LeafLabs
*/

// These constants won't change.  They're used to give names
// to the pins used:

const int analogInPin = PC3; // Analog input pin that the potentiometer
                             // is attached to

// These variables will change:
int Length = 100;
int sensorValue[100];        // value read from the pot


void setup() 
{
  pinMode(analogInPin, INPUT_ANALOG);
  
  Serial.begin(115200); // Ignored by Maple. But needed by boards using Hardware serial via a USB to Serial Adaptor

  // Wait for the Serial Monitor to open
  // (Disable this check to run without Serial Monitor)
  while (!Serial) { yield(); }
}

void loop() 
{
int i;
// Read the analog in value:
  for ( i = 0; i < Length ; i++){
  sensorValue[i] = analogRead(analogInPin);
  }

  // Print the results to the serial monitor:
  Serial.print("Measure\t" );
  for ( i = 0; i <Length; i++ )
  {
  Serial.print(sensorValue[i]);
  Serial.print(";");
  }
  Serial.println(" ");

  
}

