/*
  Author: Kelu124
  Copyright 2016
  Repo:https://github.com/kelu124/echomods/tree/master/croaker
  Contributor:Jean-Pierre Redonnet inphilly@gmail.com for his "Fast dual conversion with ADC1 + ADC2"
  Description: Getting data at 2Msps and streaming it 
  Adapted to STM32F205 of the Feather WICED
  Licence: GNU GPL 2

  WiFi code coming from this example:
  https://github.com/adafruit/Adafruit_WICED_Arduino/blob/42559f96d68d58f7337c33296abe786f829d71e5/libraries/AdafruitWicedExamples/SoftAP/APUdpServer/APUdpServer.ino

*/


// DISPLAY
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wifi
#include <adafruit_feather.h>
// WiFi AP // file at https://github.com/adafruit/Adafruit_WICED_Arduino/blob/master/cores/maple/adafruit_featherap.h
#include <adafruit_featherap.h>

#define WLAN_SSID            "TheProbe"
#define WLAN_PASS            "ILoveTheProbe"
#define WLAN_ENCRYPTION       ENC_TYPE_WPA2_AES
#define WLAN_CHANNEL 1

const uint16_t LOCAL_PORT = 5005;

IPAddress apIP     (192, 168, 2, 1); // IP of the server, the SoftAP itself
IPAddress apGateway(192, 168, 2, 1);
IPAddress apNetmask(255, 255, 255, 0);

IPAddress server_ip(192, 168, 2, 3);

// AdafruitUDP udp(WIFI_INTERFACE_SOFTAP); // @todo, solve this error
// but, WIFI_INTERFACE_SOFTAP = 1,
AdafruitUDP udp;



// Servo
Servo myservo;
uint32_t pos = 60;
int servoPin = PC7;

// Screen
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Getting the data
#define BUFFERSIZE 128
#define DECIMATION BUFFERSIZE/128
#define MaxAverage 128

// Setup
int sensorPin1 = PA1;
int sensorPin2 = PA2;
int GlobalCount = 0;
uint32_t j = 0;
uint32_t i = 0;
uint32_t jj = 0;
uint32_t ii = 0;
uint16_t val1[BUFFERSIZE + 1];
uint16_t val2[BUFFERSIZE + 1];
//uint8_t Image[7809];
uint32_t GlobalLine[128 + 1];
uint32_t GlobalLineTwo[128 + 1];
uint32_t MyLine[256 + 1];
int led3 = PA15;
int value = 0;
int Data = 0;
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
    GlobalLineTwo[i] = 0;
    i++;
  }

  // We configure the ADC1 and ADC2
  //1.5µs sample time
  //adc_set_prescaler(RCC_ADCPRE_PCLK_DIV_2); // the following lines replaces the above
  rcc_set_prescaler(RCC_PRESCALER_ADC, RCC_ADCPRE_PCLK_DIV_2);

  adc_set_sample_rate(ADC1, ADC_SMPR_1_5); // there's no ADC_SMPR_1_5 for
  adc_set_sample_rate(ADC2, ADC_SMPR_1_5); // there's no ADC_SMPR_1_5 for
  //  adc_set_sample_rate(ADC2, ADC_SMPR_3);

  //6=0110 for dual regular simultaneous mode
  // FOR STM32F1 -- DUALMOD[3:0]: Dual mode selection is on ADC control register 1 (ADC_CR1) // Bits 19:16 DUALMOD[3:0]: Dual mode selection
  ADC1->regs->CR1 |= 7 << 16;
  // change to 6 for original setting

  //only one input in the sequence for both ADC
  adc_set_reg_seqlen(ADC1, 1);
  adc_set_reg_seqlen(ADC2, 1);
  adc_set_reg_seqlen(ADC3, 1);
  // Aiming at Interleaved mode on 1 channel in continuous conversion mode: triple ADC mode
  //channel 1 (PA1) on ADC1
  ADC1->regs->SQR1 |= 0;
  ADC1->regs->SQR2 = 0;
  ADC1->regs->SQR3 = 1; //00000.00000.00001
  //channel 1 (PA1) on ADC2
  ADC2->regs->SQR1 |= 0;
  ADC2->regs->SQR2 = 0; //00000.00000.00000
  ADC2->regs->SQR3 = 1; //00000.00000.00010
  //channel 1 (PA1) on ADC3
  ADC3->regs->SQR1 |= 0;
  ADC3->regs->SQR2 = 0; //00000.00000.00000
  ADC3->regs->SQR3 = 1; //00000.00000.00010


  //Serial.println("SoftAP UDP Echo Server Callback Example\r\n");

  // Print all software versions
  Feather.printVersions();

  display.println("Configuring SoftAP\r\n");
  display.display();
  FeatherAP.err_actions(true, true);
  FeatherAP.begin(apIP, apGateway, apNetmask, WLAN_CHANNEL);

  display.println("Starting SoftAP\r\n");
  display.display();
  FeatherAP.start(WLAN_SSID, WLAN_PASS, WLAN_ENCRYPTION);
  //FeatherAP.printNetwork();

  // Tell the UDP client to auto print error codes and halt on errors
  udp.err_actions(true, true);

  FeatherAP.setJoinCallback(client_join_callback);
  FeatherAP.setLeaveCallback(client_leave_callback);

  // Start the UDP server
  display.printf("Openning UDP at port %d ... ", LOCAL_PORT);
  display.display();
  udp.begin(LOCAL_PORT);
  display.println("OK");
  display.display();

  Serial.println("Please use your PC/mobile and send any text to ");
  Serial.print( apIP );
  Serial.print(" UDP port ");
  Serial.println(LOCAL_PORT);

  display.println("AP created");
  display.display();


  waitFlag = 0;
  delay(500);
  /*
    udp.begin(LOCAL_PORT);
    udp.beginPacket(server_ip, LOCAL_PORT);
    udp.print("Connected to you: ");// send with newline
    udp.println(IPAddress(Feather.localIP()));
    udp.endPacket();
  */

  pinMode(TRIG_PIN, INPUT_PULLDOWN);
  attachInterrupt(TRIG_PIN, acquire_trigged, RISING);

}

void acquire_trigged() {
  //wait for start


  if (!waitFlag) {
    waitFlag = 1;
    //noInterrupts();
    i = 0;
    Data = 0;


    while (i < BUFFERSIZE) {
      // ADC : page 212 to 254 in the reference manual

      //start conversion
      ADC1->regs->CR2 |= ADC_CR2_SWSTART; //SWSTART: Start conversion of regular channels
      ADC2->regs->CR2 |= ADC_CR2_SWSTART;

      // Wait the end of the conversion ( 1: Conversion complete (EOCS=0), or sequence of conversions complete (EOCS=1) )
      while (!(ADC1->regs->SR & ADC_SR_EOC & ADC2->regs->SR )) ;

      //get the values converted from the two ADCs.
      // they are sharing the same channel, in interleaved mode
      val1[i] = (int16)(ADC1->regs->DR & ADC_DR_DATA);
      val2[i] = (int16)(ADC2->regs->DR & ADC_DR_DATA);
      i++;
    }


    i = 0;
    value = 0;
    while (i < 128 ) {
      j = 0;
      while (j < DECIMATION ) {
        GlobalLine[i] += val1[DECIMATION * i + j];
        GlobalLineTwo[i] += val2[DECIMATION * i + j];
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
        value = sqrt((GlobalLine[i] + GlobalLineTwo[i]) / 2 / (DECIMATION * MaxAverage)) / 2;

        display.drawFastVLine(i, 0, value , WHITE);
        // on prepare le buffer
        //Image[(pos - 60) * 128 + i] = (int8)(sqrt(GlobalLine[i]/8));
        MyLine[2 * i] =  GlobalLine[i] / (DECIMATION * MaxAverage);
        MyLine[2 * i + 1] =  GlobalLineTwo[i] / (DECIMATION * MaxAverage);
        i++;
      }
      display.setCursor(105, 10);
      display.println(pos - 60);
      display.display();
      i = 0;

      while (i < 128 ) {
        GlobalLine[i] = 0;
        GlobalLineTwo[i] = 0;
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
  // If we can send the line.. we'll do it
  if (send_command) {
    noInterrupts();
    send_command = false;
    SendImage();
    interrupts();
  }
}

// sending an image

bool SendImage() {
  // Sending the line
  detachInterrupt(TRIG_PIN);
  ii = 0; jj = 0;
  udp.beginPacket(server_ip, LOCAL_PORT);
  udp.print(kImg); udp.print(";"); udp.print(pos - 60); udp.print(";");
  while (ii < 256) {
    udp.print(MyLine[ii]);
    if (ii != 255) {
      udp.print(";");
    }
    ii++;
  }
  udp.println("");
  udp.endPacket();
  attachInterrupt(TRIG_PIN, acquire_trigged, RISING);
  return 1;

}

// Managing the wifi




void client_join_callback(const uint8_t mac[6])
{
  display.print("Client Joined: Mac = ");
  printMAC(mac);
  display.println();
}

void client_leave_callback(const uint8_t mac[6])
{
  display.print("Client Left  : Mac = ");
  printMAC(mac);
  display.println();
}

void printMAC(const uint8_t mac[6])
{
  for (int i = 0; i < 6; i++)
  {
    if (i > 0) display.print(':');
    display.printf("%02X", mac[i]);
  }
}
