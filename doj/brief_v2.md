# Doing a proper motherboard for the modules

Updating Doj for a PCB v2

## Brief

__As small as possible.__

* [ ] Silkscreen to update (REnv and AmpSignal are reversed)

* [ ] Adapt power supply from v2 - smaller board footprint
    * Good footprint this time
    * through holes
    * add pads for the signals
    * micro usb below the power supply

* Add a level shifter been Pon 3.3 and 5 and Poff 3.3 and 5

* [ ] A bit more space around the Pi0/PiW headers
* [ ] Proper silkscreening around the Pi0 headers (they are reversed)
* [ ] Exposed pads for
    * 5V
    * GND
    
* [ ] Jumper for the ADC in:
    * 0-3.3V for enveloppe
    * Raw signal
    * Raw signal, shifted

* [ ] SPI from RPi to Oled... or SPI to screen (to be checked in both case) .. or both kept, there are two SPI

## Tracks

1. __GND__: Pi.GND
2. __VDD 5V__: Pi.5V 
3. __ENV__: 
4. __RawSig__: 
5. __RENV__: 
6. __P6__: Pi.LCD_SDA (#Pin 27)
7. __GAIN__: 
8. __P8__: Pi.LCD_SCL (#Pin 28)
9. __Pon__: 
10. __Poff__: 
11. __P11__: OffSig
12. __RPIn__: Pi.RPIN (GPIO 05)
13. __P13__: 
14. __PWM__: Pi.PWM (GPIO 06)
15. __P15__: 
16. __POn3__: Pi.PON (GPIO 13)
17. __POff3__: Pi.POff (GPIO 12)
18. __Raw__: 
19. __3.3V__: 

## RPi

Check the RPins - see


## ADCs

12 bits taken

```
//
#define RPIn	 5
#define PWM	 6
#define PON	 13
#define POFF	 12
//ADC 1
#define BIT0_PIN 7
#define BIT1_PIN 8
#define BIT2_PIN 9
#define BIT3_PIN 10
#define BIT4_PIN 11
#define BIT5_PIN 25
//ADC 2
#define BIT0_PIN2 17
#define BIT1_PIN2 18
#define BIT2_PIN2 22
#define BIT3_PIN2 23
#define BIT4_PIN2 24
#define BIT5_PIN2 27
```
