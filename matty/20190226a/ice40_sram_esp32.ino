/*
 * 
 * 
 *   ESP32 Wifi & C Array Bitstream Uploader for ice40 FPGA´
 * 
 *  ADAPTED FOR `20190126a` on same date
 * 
 *  usefull Links:
 *  https://github.com/G6EJD/ESP32-ESP8266-File-Download-Upload-Delete-Stream-and-Directory/blob/master/ESP_File_Download_Upload_Dir_Stream_V01.ino
 *  https://stackoverflow.com/questions/8707183/script-tool-to-convert-file-to-c-c-source-code-array
 *  https://www.trenz-electronic.de/fileadmin/docs/Trenz_Electronic/Modules_and_Module_Carriers/3.05x6.5/TE0876/REV01/Documents/SCH-TE0876-01.PDF
 *  https://github.com/cliffordwolf/icotools/blob/master/icoprog/icoprog.cc
 * 
 *  example upload from commandline:
 *  curl -F file=@audiotest.bin http://10.0.1.40/fupload 
 * 
 */
#include <WiFi.h>              // Built-in
#include <WiFiMulti.h>         // Built-in
#include <ESP32WebServer.h>    // https://github.com/Pedroalbuquerque/ESP32WebServer download and place in your Libraries folder
#include <M5Stack.h>
  
 WiFiMulti wifiMulti;
 ESP32WebServer server(80);

// this file contains the bitstream for ice40 FPGA created by xxd -i from bin
#include "ice40.h"


void setup() {
  // put your setup code here, to run once:

    Serial.begin(115200);

    // connect to access point
    wifiMulti.addAP("SSID", "PASSWORD"); 
    while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
       delay(250); Serial.print('.');
    }

  



    Serial.println("\nConnected to "+WiFi.SSID()+" Use IP address: "+WiFi.localIP().toString()); // Report which SSID and IP is in use

    server.on("/",   File_Upload);
    server.on("/fupload",  HTTP_POST,[](){ server.send(200);}, handleFileUpload);
    server.begin();
    Serial.println("HTTP server started");
    

    // use this to upload from ice40.h 
    reset_inout();
    //    prog_bitstream(false);
    //    reset_inout();

    Serial.println("\nFlash FPGA");  
}

// File UploadFile; 
void handleFileUpload(){ // upload a new file to the Filing system
  HTTPUpload& uploadfile = server.upload(); // See https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer/srcv
                                            // For further information on 'status' structure, there are other reasons such as a failed transfer that could be used
  if(uploadfile.status == UPLOAD_FILE_START) {
    String filename = uploadfile.filename;
    if(!filename.startsWith("/")) filename = "/"+filename;
    Serial.print("Upload File Name: "); Serial.println(filename);
    pinMode(2,OUTPUT);
    digitalWrite(2,true);
    prog_bitstream_start();
  } else if (uploadfile.status == UPLOAD_FILE_WRITE) {
    // if(UploadFile) UploadFile.write(uploadfile.buf, uploadfile.currentSize); // Write the received bytes to the file
    Serial.println(String("Upload Chunk: ") + String(uploadfile.currentSize )); 
    digitalWrite(2,!digitalRead(2)); // blinking LED while flashing 2K blocks 
    prog_bitstream_send(uploadfile.buf,uploadfile.currentSize );
    
  } else if (uploadfile.status == UPLOAD_FILE_END) {
      prog_bitstream_finish();
      digitalWrite(2,false);
      // UploadFile.close();   // Close the file again
      Serial.print("Upload Size: "); Serial.println(uploadfile.totalSize);
      String webpage = F("<html> <head><title>ice40</title> </head><body>");
      webpage += F("<h3>File was successfully uploaded</h3>"); 
      webpage += F("<h2>Uploaded File Name: "); webpage += uploadfile.filename+"</h2>";
      server.send(200,"text/html",webpage);
  }
}

void loop() {
  // handle webserver events
  server.handleClient(); // Listen for client connections
}


void File_Upload(){
  String webpage = F("<html> <head><title>ice40</title> </head><body>");
  webpage += F("<h3>Select File to Upload</h3>"); 
  webpage += F("<h3>or by commandline:  curl -F file=@audiotest.bin http://<IP>/fupload </h3>"); 
  webpage += F("<FORM action='/fupload' method='post' enctype='multipart/form-data'>");
  webpage += F("<input class='buttons' style='width:40%' type='file' name='fupload' id = 'fupload' value=''><br>");
  webpage += F("<br><button class='buttons' style='width:10%' type='submit'>Upload File</button><br>");
  webpage += F("<a href='/'>[Back]</a><br><br>");
  webpage += F("</body></html>");
   Serial.println(webpage);  
  server.send(200, "text/html",webpage);
}


// define Pins for my iceZero FPGA Board with Raspberry Pinheaders

#  define RPI_ICE_CLK     23 // on RaspHeader GPIO 16
#  define RPI_ICE_CDONE   19 // on RaspHeader GPIO  5
#  define RPI_ICE_MOSI    21 // on RaspHeader GPIO  6  
#  define RPI_ICE_MISO    18 // ignore this Pin
#  define LOAD_FROM_FLASH  5 // ignore this Pin
#  define RPI_ICE_CRESET  17 // on RaspHeader GPIO  26
#  define RPI_ICE_CS      16 // on RaspHeader GPIO  12
#  define RPI_ICE_SELECT   3 // ignore this Pin


// leave programming mode
void reset_inout() {
    pinMode(RPI_ICE_CLK,     INPUT);
    pinMode(RPI_ICE_CDONE,   INPUT);
    pinMode(RPI_ICE_MOSI,    INPUT);
    pinMode(RPI_ICE_MISO,    INPUT);
    pinMode(LOAD_FROM_FLASH, INPUT);
    pinMode(RPI_ICE_CRESET,  INPUT);
    pinMode(RPI_ICE_CS,      INPUT);
    pinMode(RPI_ICE_SELECT,  INPUT);
}

// for FPGA timing
void digitalSync(int usec_delay) {
  delayMicroseconds(usec_delay);
}

// SPI clock bitBanging
void iceClock() {
      digitalWrite(RPI_ICE_CLK, LOW);
      digitalSync(1);
      digitalWrite(RPI_ICE_CLK, HIGH);
      digitalSync(1);
}


bool prog_bitstream_start() {
  pinMode(RPI_ICE_CLK,     OUTPUT);
  pinMode(RPI_ICE_MOSI,    OUTPUT);
  pinMode(LOAD_FROM_FLASH, OUTPUT);
  pinMode(RPI_ICE_CRESET,  OUTPUT);
  pinMode(RPI_ICE_CS,      OUTPUT);
  pinMode(RPI_ICE_SELECT,  OUTPUT);
  // enable reset
  digitalWrite(RPI_ICE_CRESET, LOW);
  // start clock high
  digitalWrite(RPI_ICE_CLK, HIGH);

  // select SRAM programming mode
  digitalWrite(LOAD_FROM_FLASH, LOW);
  digitalWrite(RPI_ICE_SELECT, LOW);
  digitalWrite(RPI_ICE_CS, LOW);
  digitalSync(100);

  // release reset
  digitalWrite(RPI_ICE_CRESET, HIGH);
  digitalSync(2000);

  // send start clks
  for (int i = 0; i < 8; i++) {
    iceClock();
  }
  
}

// stream buffer to FPGA
bool prog_bitstream_send(unsigned char * buf, long size) {
 for (int k = 0; k < size; k++) {
    byte d = buf[k]; // getchar();
    for (int i = 7; i >= 0; i--) {
      digitalWrite(RPI_ICE_MOSI, ((d >> i) & 1) ? HIGH : LOW);
      iceClock();
    }
  }
}


// finish upload to FPGA
bool prog_bitstream_finish() {
  for (int i = 0; i < 49; i++) {
      iceClock();
  }
  reset_inout();
}


// Bitstream send to FPGA from static Array
// use xxd -i to generate this header File from xxx.bin and set it to const byte      
bool prog_bitstream(bool reset_only) {
//  assert(enable_prog_port);

  pinMode(RPI_ICE_CLK,     OUTPUT);
  pinMode(RPI_ICE_MOSI,    OUTPUT);
  pinMode(LOAD_FROM_FLASH, OUTPUT);
  pinMode(RPI_ICE_CRESET,  OUTPUT);
  pinMode(RPI_ICE_CS,      OUTPUT);
  pinMode(RPI_ICE_SELECT,  OUTPUT);

  //fprintf(stderr, "reset..\n");

  // enable reset
  digitalWrite(RPI_ICE_CRESET, LOW);

  // start clock high
  digitalWrite(RPI_ICE_CLK, HIGH);

  // select SRAM programming mode
  digitalWrite(LOAD_FROM_FLASH, LOW);
  digitalWrite(RPI_ICE_SELECT, LOW);
  digitalWrite(RPI_ICE_CS, LOW);
  digitalSync(100);

  // release reset
  digitalWrite(RPI_ICE_CRESET, HIGH);
  digitalSync(2000);

  // fprintf(stderr, "cdone: %s\n", digitalRead(RPI_ICE_CDONE) == HIGH ? "high" : "low");

  if (reset_only)
    return true;

  // fprintf(stderr, "programming..\n");

  for (int i = 0; i < 8; i++) {
    iceClock();
  }


  for (int k = 0; k< sizeof(ice40); k++) {
    byte d = ice40[k]; // getchar();

    for (int i = 7; i >= 0; i--) {
      digitalWrite(RPI_ICE_MOSI, ((d >> i) & 1) ? HIGH : LOW);
      iceClock();
    }

    // if (verbose && !(k % 1024) && k)  printf("%3d kB written.\n", k / 1024);
  }

  for (int i = 0; i < 49; i++) {
      iceClock();
  }


  bool cdone_high = digitalRead(RPI_ICE_CDONE) == HIGH;
  // fprintf(stderr, "cdone: %s\n", cdone_high ? "high" : "low");

  reset_inout();

  
  if (!cdone_high) return false;

  return true;
}





