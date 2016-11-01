/*
	Author: Kelu124
	Copyright 2016
	Repo:https://github.com/kelu124/echomods/tree/master/croaker
	Contributor:Jean-Pierre Redonnet inphilly@gmail.com for his "Fast dual conversion with ADC1 + ADC2"
	Adapted to STM32F205 of the Feather WICED 
	Description: Unused version
	Licence: GNU GPL 2

*/

// DISPLAY

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Getting the data
#define BUFFERSIZE 128*32 // can go up to 4096*2 @ 8bits
#define DECIMATION BUFFERSIZE/128
#define MaxAverage 10

int sensorPin1 = PA1;
int sensorPin2 = PA2;
int GlobalCount = 0;
uint32_t j = 0;
uint32_t i = 0;
uint8_t val1[BUFFERSIZE + 1]; // depends on the size expected..
int GlobalLine[128 + 1];
int led1 = PA4;
int led2 = PB4;
int led3 = PA15;
boolean waitFlag;
uint32_t kImg = 0;
const int  TRIG_PIN = PB5;



void setup() {

  // preparing the trigger


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
  display.setCursor(0, 0);
  display.println("== Test starting == ");
  display.display();
  delay(2000);


  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  // while (!Serial) {
  // yield();
  // }

  //display.clearDisplay();
  //display.setCursor(0,0);
  display.println("Serial OK");
  display.display();


  // We configure the ADC1 and ADC2
  i = 0;
  while (i < 128) {
    GlobalLine[i] = 0;
    i++;
  }

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
  waitFlag = 0;
  pinMode(TRIG_PIN, INPUT_PULLDOWN);
  attachInterrupt(TRIG_PIN, acquire_trigged, RISING);

}

void acquire_trigged() {
  //wait for start
  if (!waitFlag) {
    waitFlag = 1;

    i = 0;
    int Data = 0;


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

    i = 0;
    int value = 0;
    //display.clearDisplay();
    while (i < 128 ) {
      //Serial.print(val1[i]);
      //Serial.print(": ");
      //display.drawFastVLine(i, 0, (value)/1.5, WHITE);
      j = 0;
      while (j < DECIMATION ) {
        GlobalLine[i] += val1[DECIMATION * i + j]  ;
        j++;
      }
       i++;
    }
    GlobalCount++;

    if ( GlobalCount == MaxAverage) {
      display.clearDisplay();
      i = 0;
      while (i < 128 ) {
        display.drawFastVLine(i, 0, ((( GlobalLine[i]) / (2*DECIMATION*MaxAverage))), WHITE);
        i++;
      }
      display.display();

      i = 0;
      while (i < 128 ) {
        GlobalLine[i] = 0;
        i++;
      }

      GlobalCount = 0;
      display.clearDisplay();
    }


    digitalWrite(led3, LOW);

    Serial.println(" "); //terminate the line
    Serial.println(" ");

    Serial.flush();

    //delay(500);
  }
  waitFlag = 0;
}



void loop() {
  yield();
}

