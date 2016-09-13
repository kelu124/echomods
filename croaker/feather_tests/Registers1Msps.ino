/*

  Jean-Pierre Redonnet
  inphilly@gmail.com
  Version 0.2 - July 26th,2015

  Fast dual conversion with ADC1 + ADC2

  Licence: GNU GPL 2

*/

// DISPLAY 

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Acquisition

#define BUFFERSIZE 1000

int sensorPin1 = PA1;
int sensorPin2 = PA2;
int i;
int val1[BUFFERSIZE + 1];

int led3 = PA15;

boolean waitFlag;




void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(sensorPin1, INPUT_ANALOG);
  pinMode(sensorPin2, INPUT_ANALOG);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64) 
  // init done
  display.clearDisplay();

   // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("== Test starting == ");
  display.display();
  delay(2000);
  

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) { yield(); }
  
  //display.clearDisplay();
  //display.setCursor(0,0);
  display.println("Serial OK");
  display.display();
  
  // We configure the ADC1 and ADC2

  //1.5µs sample time
  //adc_set_prescaler(RCC_ADCPRE_PCLK_DIV_2); // the following lines replaces the above
  rcc_set_prescaler(RCC_PRESCALER_ADC, RCC_ADCPRE_PCLK_DIV_2);

  adc_set_sample_rate(ADC1, ADC_SMPR_1_5); // there's no ADC_SMPR_1_5 for 
//  adc_set_sample_rate(ADC2, ADC_SMPR_3);

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
  waitFlag = 0;
  Serial.println("Type 'startADC' to start the acquisition");
  delay(500); 
  digitalWrite(led3, LOW);
  display.println("Acquisition to start");
  display.display();
  //read analog inputs
  i = 0;
  int Data = 0;
  int t1 = micros();

  while (i < BUFFERSIZE) {

    //start conversion
    ADC1->regs->CR2 |= ADC_CR2_SWSTART;
    // Wait the end of the conversion
    while (!(ADC1->regs->SR & ADC_SR_EOC)) ;
    //get the values converted
    val1[i] = (int16)(ADC1->regs->DR & ADC_DR_DATA);
    
    //next
    i++;
  }
  int t2 = micros();

  
  // Display test speed 
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Duration");
  display.print(t2 - t1);
  display.print("-");
  display.println(val1[101]);
  display.display();
  

  i = 0;
  while (i < BUFFERSIZE) {
    Serial.print(val1[i]);
    Serial.print(": ");

    i++;
  }

  Serial.println(); //terminate the line
  Serial.println();
  Serial.flush();

}

