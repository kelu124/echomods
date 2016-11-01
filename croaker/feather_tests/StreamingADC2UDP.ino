/*
	Author: Kelu124
	Copyright 2016
	Repo:https://github.com/kelu124/echomods/tree/master/croaker
	Contributor:Jean-Pierre Redonnet inphilly@gmail.com for his "Fast dual conversion with ADC1 + ADC2"
	Adapted to STM32F205 of the Feather WICED 
	Description: First test to get the UDP working
	Licence: GNU GPL 2

*/

// DISPLAY
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wifi
#include <adafruit_feather.h>
#define WLAN_SSID     "XX"
#define WLAN_PASS     "XX"
#define ENC_TYPE ENC_TYPE_WPA2_AES
const uint16_t LOCAL_PORT = 5005;
AdafruitUDP udp;
// the IP of your server -- type "nc -lu 5005" to get the image
IPAddress server_ip(192, 168, 1, 9);

char *BUFFER = "lol";

// Servo
Servo myservo;
uint32_t pos = 60;

// Screen
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Getting the data
#define BUFFERSIZE 128
#define DECIMATION BUFFERSIZE/128
#define MaxAverage 100

// Setup
int servoPin = PC7;
int sensorPin1 = PA1;
int sensorPin2 = PA2;
int GlobalCount = 0;
uint32_t j = 0;
uint32_t i = 0;
uint32_t jj = 0;
uint32_t ii = 0;
uint32_t val1[BUFFERSIZE + 1];
uint8_t Image[7809];
uint32_t GlobalLine[128 + 1];
uint32_t MyLine[128 + 1];
int led3 = PA15;
boolean waitFlag;
boolean waitServo;
uint32_t kImg = 0;
const int  TRIG_PIN = PB5;
char* input;
boolean send_command;

void setup() {
  send_command = false;
  // Servo
  myservo.attach(servoPin);
  myservo.write(60);
  // Pins
  pinMode(led3, OUTPUT);
  pinMode(sensorPin1, INPUT_ANALOG);
  pinMode(sensorPin2, INPUT_ANALOG);
  // Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("== Test starting == ");
  display.display();



  // We Clean the data
  i = 0;
  while (i < 128) {
    GlobalLine[i] = 0;
    i++;
  }

  i = 0;
  while (i < 7809) {
    Image[i] = 0;
    i++;
  }

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


  while ( !connectAP() )
  {
    delay(500); // delay between each attempt

  }



  waitFlag = 0;
  delay(500);

  udp.begin(LOCAL_PORT);

  udp.beginPacket(server_ip, LOCAL_PORT);
  udp.print("Connected to you: ");// send with newline
  udp.println(IPAddress(Feather.localIP()));
  udp.endPacket();


  pinMode(TRIG_PIN, INPUT_PULLDOWN);
  attachInterrupt(TRIG_PIN, acquire_trigged, RISING);

}

void acquire_trigged() {
  //wait for start


  if (!waitFlag) {
    waitFlag = 1;
    //noInterrupts();
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
      send_command = true;
      while (i < 128 ) {
        display.drawFastVLine(i, 0, ((( GlobalLine[i]) / (4 * 8 * DECIMATION * MaxAverage))), WHITE);
        // on prepare le buffer
        Image[(pos - 60) * 128 + i] = (int8)(GlobalLine[i]);
        MyLine[i] = GlobalLine[i] / (4 * 8 * DECIMATION * MaxAverage);
        i++;
      }
      display.setCursor(100, 10);
      display.println(pos - 60);
      display.display();
      i = 0;

      while (i < 128 ) {
        GlobalLine[i] = 0;
        i++;
      }
      // On reset l'ensemble
      GlobalCount = 0;
      display.clearDisplay();
      // On se met sur une nouvelle ligne
      if (pos < 120) {
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);                        // waits 5ms for the servo to reach the position
      } else {
        display.clearDisplay();
        pos = 60;
        kImg++;
        //Original code for UDP


      }
      pos++;
    }
  }
  waitFlag = 0;

}


void loop() {
  if (send_command)
  {
    noInterrupts();
    send_command = false;
    SendImage();
    interrupts();
  }
}

bool SendImage() {

  detachInterrupt(TRIG_PIN);
  ii = 0; jj = 0;
  udp.beginPacket(server_ip, LOCAL_PORT);
  udp.print("Image:"); udp.print(kImg); udp.print(" - Position:"); udp.println(pos - 60);
  while (ii < 128) {
    udp.print(MyLine[ii]); udp.print(";");
    ii++;
  }
  udp.println("");
  udp.endPacket();
  attachInterrupt(TRIG_PIN, acquire_trigged, RISING);
  return 1;

}

bool connectAP(void)
{
  Feather.connect();
  delay(500);
  if (!Feather.connected()) {


    // Attempt to connect to an AP
    if ( Feather.connect(WLAN_SSID, WLAN_PASS) ) {
      display.clearDisplay(); display.setCursor(0, 0);
      display.println("Connected!"); display.println(IPAddress(Feather.localIP())); display.display();
      delay(1000);

      if ( Feather.checkProfile(WLAN_SSID) ) {
        display.printf("\"%s\" exists \r\n", WLAN_SSID); display.display();
      } else {
        display.print("Adding "); display.println(WLAN_SSID); display.display();
        Feather.addProfile(WLAN_SSID, WLAN_PASS, ENC_TYPE);
      }
      delay(1000);

    } else {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.printf("Failed! %s (%d)", Feather.errstr(), Feather.errno());
      display.display();
      delay(2000);
    }
  }

  return Feather.connected();
}

