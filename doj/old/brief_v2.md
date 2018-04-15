# Doing a proper motherboard for the modules

Updating Doj for a PCB v2

## Brief

__As small as possible.__

* [ ] Silkscreen to update (REnv and AmpSignal are reversed) (to match the tracks names in the next paragraph).

* [ ] Adapt power supply from v2 - smaller board footprint
    * Good footprint this time
    * through holes (larger vias)
    * add exposed pads for the 5V and GND.
    * micro usb below the power supply

* [ ] A bit more space around the Pi0/PiW headers
* [ ] Proper silkscreening around the Pi0 headers (they are reversed)
* [ ] Exposed pads for
    * 5V
    * GND
    
* [ ] Jumper for the ADC in:
    * 0-3.3V for enveloppe
    * Raw signal
    * Raw signal, shifted

* [ ] I2C from RPi to Oled... (using GPIO 02 and GPIO03)

* [ ] Jumpers..
    * see next section

## See module footprint (and vias too small)

![](/doj/images/20170504_204421.jpg)

## Tracks and jumpers

!!! __Important, GPIO 12 and 13 are replaced by 23 and 24 respectively__

![](/doj/images/20170504_215628.jpg)

> + Track 12 (RPin) must only be connected to the header on the right ( on its GPIO 05).  


## Tracks

1. __GND__: Pi.GND
2. __VDD 5V__: Pi.5V 
3. __ENV__: 
4. __RawSig__: 
5. __RENV__: 
6. __P6__: Pi.LCD_SDA (GPIO 02)
7. __GAIN__: 
8. __P8__: Pi.LCD_SCL (GPIO 03)
9. __Pon__: 
10. __Poff__: 
11. __P11__: OffSig
12. __RPIn__: Pi.RPIN (GPIO 05)
13. __P13__: 
14. __PWM__: Pi.PWM (GPIO 06)
15. __P15__: 
16. __POn3__: Pi.PON (GPIO 23)
17. __POff3__: Pi.POff (GPIO 24)
18. __Raw__: 
19. __3.3V__: 

## RPi

Check the RPins - see below and above


## ADCs

12 bits taken

```
//
#define clock	 4
#define RPIn	 5
#define PWM	 6
#define PON	 23
#define POFF	 24
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
#define BIT5_PIN2 21
```

## Power footprint 

![](/doj/images/20170508_192712.jpg)

![](/doj/images/20170508_192840.jpg)

