# Doing a proper motherboard for the modules

Updating Doj for a PCB v2

## Brief

__As small as possible.__

* Adapt power supply from v2 - smaller board footprint
    * Good footprint this time
    * through holes
    * add pads for the signals
    * micro usb below the power supply

* Add a level shifter been Pon 3.3 and 5 and Poff 3.3 and 5

* A bit more space around the Pi0/PiW headers

* Proper silkscreening around the Pi0 headers (they are reversed)

* Exposed pads for
    * 5V
    * GND
    * amplified signal
    * Enveloppe
    * Pulser in to one of the pins

* Jumper for the ADC in:
    * 0-3.3V for enveloppe
    * Raw signal
    * Raw signal, shifted

* SPI from RPi to Oled... or SPI to screen (to be checked in both case) .. or both kept, there are two SPI

## RPi

Check the RPins - see


## ADCs

12 bits taken

```
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
