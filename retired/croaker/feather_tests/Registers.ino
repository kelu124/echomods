/*
	Author: Kelu124
	Copyright 2016
	Repo:https://github.com/kelu124/echomods/tree/master/croaker
	Contributor:Jean-Pierre Redonnet inphilly@gmail.com for his "Fast dual conversion with ADC1 + ADC2"
	Description: Trying to get to work with direct ADC registers 
	Licence: GNU GPL 2

*/

//#include <libmaple/adc.h>
//#include <libmaple/adc.c>

#define BUFFERSIZE 1000

int sensorPin1 = PA1;
int sensorPin2 = PA2;
int i;
int val1[BUFFERSIZE + 1];
int val2[BUFFERSIZE + 1];
int led1 = PA4;
int led2 = PB4;
int led3 = PA15;
char serialReadString[50];
boolean waitFlag;

int serialReader() {
  int makeSerialStringPosition;
  int inByte;

  if ( Serial.available() < 3 ) return 0; //nothing

  const int terminatingChar = 13; // Terminate lines with CR

  inByte = Serial.read();
  makeSerialStringPosition = 0;

  if (inByte > 0 && inByte != terminatingChar) { //If we see data (inByte > 0) and that data isn't a carriage return
    delay(10); //Allow serial data time to collect

    while (inByte != terminatingChar && Serial.available() > 0) { // As long as EOL not found and there's more to read, keep reading
      serialReadString[makeSerialStringPosition] = inByte; // Save the data in a character array
      makeSerialStringPosition++; // Increment position in array
      inByte = Serial.read(); // Read next byte
    }

    if (inByte == terminatingChar) { //If we terminated properly
      serialReadString[makeSerialStringPosition] = 0; //Null terminate the serialReadString (Overwrites last position char (terminating char) with 0
      return (makeSerialStringPosition);
    }
    else return (0);
  }
}


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(sensorPin1, INPUT_ANALOG);
  pinMode(sensorPin2, INPUT_ANALOG);

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) { yield(); }

  // We configure the ADC1 and ADC2

  //1.5µs sample time
  //adc_set_prescaler(RCC_ADCPRE_PCLK_DIV_2); // the following lines replaces the above
  rcc_set_prescaler(RCC_PRESCALER_ADC, RCC_ADCPRE_PCLK_DIV_2);

  adc_set_sample_rate(ADC1, ADC_SMPR_3); // there's no ADC_SMPR_1_5 for 
  adc_set_sample_rate(ADC2, ADC_SMPR_3);

  //6=0110 for dual regular simultaneous mode
  ADC1->regs->CR1 |= 6 << 16;

  //only one input in the sequence for both ADC
  adc_set_reg_seqlen(ADC1, 1);
  adc_set_reg_seqlen(ADC2, 1);

  //channel 1 (PA1) on ADC1
  ADC1->regs->SQR1 |= 0;
  ADC1->regs->SQR2 = 0;
  ADC1->regs->SQR3 = 1; //00000.00000.00001
  //channel 2 (PA2) on ADC2
  ADC2->regs->SQR1 |= 0;
  ADC2->regs->SQR2 = 0; //00000.00000.00000
  ADC2->regs->SQR3 = 2; //00000.00000.00010

}

void loop() {
  //wait for start
  Serial.println("Initiating");
  digitalWrite(led3, HIGH);
  waitFlag = 1;
  Serial.println("Type 'startADC' to start the acquisition");
  delay(5000); 
  digitalWrite(led3, LOW);
  //read analog inputs
  i = 0;
  digitalWrite(led1, HIGH);
  int t1 = micros();
  while (i < BUFFERSIZE) {
    //start conversion
    ADC1->regs->CR2 |= ADC_CR2_SWSTART;
    // Wait the end of the conversion
    while (!(ADC1->regs->SR & ADC_SR_EOC)) ;
    while (!(ADC2->regs->SR & ADC_SR_EOC)) ;
    //get the values converted
    val1[i] = (int16)(ADC1->regs->DR & ADC_DR_DATA);
    val2[i] = (int16)(ADC2->regs->DR & ADC_DR_DATA);
    //next
    i++;
  }
  int t2 = micros();
  digitalWrite(led3, HIGH);
  // Send data
  digitalWrite(led2, HIGH);
  Serial.println();
  Serial.println("Duration");
  Serial.println(t2 - t1);
  i = 0;
  while (i < BUFFERSIZE) {
    Serial.print(val1[i]);
    Serial.print("/");
    Serial.print(val2[i]);
    Serial.print("-");
    i++;
  }
  Serial.println(); //terminate the line
  Serial.println();
  Serial.flush();
  digitalWrite(led2, LOW);
}

