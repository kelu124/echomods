https://github.com/m5stack/M5Cloud/issues/3

@todo 

Screen is 320x320 or 320x240.


Say 120us for acquisition

3us per pixel

512KB RAM ?

ESP32 : Mémoire RAM: 520 kB  
Large pour 64*200*2 pts (1 line) - 256kB at 64Msps

32 : 128kB : FFT aussi possible



IDEA:

1. Load
  * Reset
  * Blinky
  * Next screen

2. Acquisition
  * Run Acq
  * FFT/Signal switch
  * Details

3. Details : Acq
  * 0 - 50 us 
  * 50 - 100 us
  * 0 - 120 us


https://github.com/ElectroMagus/M5-FFT

Connecteurs:

* 5V
* GND
* CS
* MISO
* MOSI



