#include <SPI.h>
#include <stdio.h>
#include <stdint.h>

/* CONNECTIONS BETWEEN RPi and NRF52832
  NRF52832 pin30 -> RPi header GPIO 23 (Ice40 reset)
  NRF52832 pin27 -> RPi header GPIO 8 (Ice40 CS)
  NRF52832 MISO -> RPi header GPIO 10 (Rpi MISO)
  NRF52832 MOSI -> RPi header GPIO 9 (Rpi MOSI)
  NRF52832 SCK -> RPi header GPIO 11 (Rpi  CLK)
  NRF52832 GND to RaspberryPi header GND pin
  USB power supply
*/

#define ICE40RESET 30
#define ICE40CS    27
#define ICE40MISO  14
#define ICE40MOSI  13
#define ICE40CLK   12

#define PTS        6000
#define LenAcq      2*PTS+1
#define LenData      PTS+1
#define StartPoint   3400
#define LenWindow    2600

int16_t DATA[LenAcq];
int16_t RAWDATA[LenWindow+1];
float frequency;

    

void SetGain(  ) {
  for (int i = 0; i <= 40; i++) {
    WriteFPGA(16 + i, 400 / 4);
  }
}

void SetupFPGA() {
  SetGain(); // TGC level

  // Duration of Pon
  WriteFPGA(0xE0, 0x19 ); // 200ns Pon
  // Duration between Pon and Poff
  WriteFPGA(0xD0, 0xC ); // 12*7.8125ns delay between Pon and Poff
  // Duration of damper
  WriteFPGA(0xE1, 0 ); //
  WriteFPGA(0xE2, 254 ); //
  // Duration betwen beginning and end of acquisition
  WriteFPGA(0xE3, 2 ); //
  WriteFPGA(0xE4, 128 ); //
  // Length of acquisition
  WriteFPGA(0xE5, 0x60 ); //
  WriteFPGA(0xE6, 0x00 ); // 0x60 * 255 *   7.8125ns duree
  //Freq
  WriteFPGA(0xED, 0X00); // setting freq as 64Msps / (1+arg) eg 3 = 16msps
  //Shoot
  WriteFPGA(0xEB, 0x00); // Doing 1 shot
}


void GetData() {


  for (int i = 0; i <= LenAcq; i++) {
    DATA[i] = 0;
  }

   for (int i = 0; i <= LenWindow; i++) {
    RAWDATA[i] = 0;
  }

  for (int i = 0; i <= LenAcq; i++) {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(ICE40CS, LOW);
    DATA[i] = SPI.transfer(0x00);
    digitalWrite(ICE40CS, HIGH);
    SPI.endTransaction();
  }

  for (int i = 0; i <= LenData ; i++) {

    DATA[i] = 128 * (DATA[2 * i + 1] & 0b111) + DATA[2 * i + 2];
  }

  for (int i = 0; i <= LenWindow; i++) {
    RAWDATA[i] = DATA[StartPoint + i];
  }

}


void setup() {
  // put your setup code here, to run once:
  pinMode(ICE40CS, OUTPUT);
  pinMode(ICE40RESET, OUTPUT);

  // initialize SPI:
  SPI.begin();

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.endTransaction();

  Serial.begin(115200);         // SERIAL
 
  delay(500);
  digitalWrite(ICE40RESET, LOW);
  delay(500);
  digitalWrite(ICE40RESET, HIGH);
  delay(500);
  SetupFPGA();

}

int WriteFPGA(int address, int value) {

  //SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  digitalWrite(ICE40CS, LOW);
  SPI.transfer(0xAA);
  digitalWrite(ICE40CS, HIGH);
  delayMicroseconds(5);
  digitalWrite(ICE40CS, LOW);
  SPI.transfer(address);
  digitalWrite(ICE40CS, HIGH);
  delayMicroseconds(5);
  digitalWrite(ICE40CS, LOW);
  SPI.transfer(value);
  digitalWrite(ICE40CS, HIGH);
  delayMicroseconds(5);
  //SPI.end();
  SPI.endTransaction();
  return 1;
}

int TestFPGA() {
  WriteFPGA(0xEB, 0x01);
  delay(1000);
  WriteFPGA(0xEB, 0x00);
  delay(1000);
  return 1;
}


void loop() {


  // put your main code here, to run repeatedly:
  TestFPGA();

  // Read
  WriteFPGA(0xEF, 0x01); // cleaning pointer
  WriteFPGA(0xEA, 0x01); // trigging acquisition
  delay(200);
  GetData();
  
  for (int i = 0; i <= LenWindow ; i++) {

      Serial.println(RAWDATA[i] );

     
  }

  delay(10000);
   
}
