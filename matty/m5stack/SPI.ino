#include <SPI.h>
#include <M5Stack.h>

#define ICE40RESET 22
#define ICE40CS    21
#define ICE40MISO  19
#define ICE40MOSI  23
#define ICE40CLK   18

bool MSBF = true;
int SPIMODE = 0;

void buttons_test() {
  if (M5.BtnA.wasPressed()) {
    if (MSBF) {
      M5.Lcd.printf("MSBF is now false ");
      SPI.setBitOrder(LSBFIRST);
      MSBF = false;

    } else {
      M5.Lcd.printf("MSBF is now true ");
      SPI.setBitOrder(MSBFIRST);
      MSBF = true;
    }
  }

  if (M5.BtnB.wasPressed()) {
    //
    SPIMODE = (SPIMODE + 1) % 4;
    M5.Lcd.printf("SPIMODE is:%3d\n", SPIMODE);

    switch (SPIMODE) {
      case 0:
        //do something when var equals 0
        SPI.setDataMode(SPI_MODE0);
        break;
      case 1:
        //do something when var equals 1
        SPI.setDataMode(SPI_MODE1);
        break;
      case 2:
        //do something when var equals 2
        SPI.setDataMode(SPI_MODE2);
        break;
      case 3:
        //do something when var equals 3
        SPI.setDataMode(SPI_MODE3);
        break;
      default:
        // if nothing else matches, do the default
        // default is optional
        break;
    }

    SPI.setDataMode(SPI_MODE0);
  }

  if (M5.BtnC.wasPressed()) {
    M5.Lcd.printf("C");
    // kikoo
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(ICE40CS, OUTPUT);
  pinMode(ICE40RESET, OUTPUT);




  // initialize SPI:
  SPI.begin();

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  Serial.begin(115200);         // SERIAL
  M5.begin();                   // M5STACK INITIALIZE
  M5.Lcd.setBrightness(200);    // BRIGHTNESS = MAX 255
  M5.Lcd.fillScreen(BLACK);     // CLEAR SCREEN
  M5.Lcd.setRotation(0);        // SCREEN ROTATION = 0
  M5.Lcd.printf("Init\n");
  digitalWrite(ICE40RESET, LOW);
  delay(500);
  digitalWrite(ICE40RESET, HIGH);
  M5.Lcd.printf("Reset done\n");
}

int WriteFPGA(int address, int value) {

  digitalWrite(ICE40CS, LOW);
  SPI.transfer(0xAA);
  digitalWrite(ICE40CS, HIGH);

  digitalWrite(ICE40CS, LOW);
  SPI.transfer(address);
  digitalWrite(ICE40CS, HIGH);

  digitalWrite(ICE40CS, LOW);
  SPI.transfer(value);
  digitalWrite(ICE40CS, HIGH);

  return 1;
}

int TestFPGA() {
  M5.Lcd.printf("Blink 1 -  ");
  WriteFPGA(0xEB, 0x01);
  delay(500);
  WriteFPGA(0xEB, 0x00);
  delay(500);

}


void loop() {
  // put your main code here, to run repeatedly:
  TestFPGA();

  buttons_test();
  M5.update();
}
