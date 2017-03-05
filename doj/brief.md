# Doing a proper motherboard for the modules

## Brief

A single "breakout board" several elements:
* A Feather WICED: https://www.adafruit.com/product/3056
* Two home made modules (with KiCad):
    * https://github.com/kelu124/echomods/tree/master/tobo/source/Kicad
    * https://github.com/kelu124/echomods/tree/master/goblin/source/Kicad
* A power supply: http://amzn.to/2kH5VbB
* A OLED screen: http://amzn.to/2lTwYW2
* A trinket pro

* Two headers for raspberry pi should also be present

* The communication between the two modules is purely using the stripboard. There are 19 tracks ( https://kelu124.gitbooks.io/echomods/content/Chapter6/interfaces.html ).
* The trinket provides two pins to the ITF-I_pulse_on and ITF-J_pulse_off tracks -- and needs only 5V in and GND.
* The board will need basically a couple of pullups for the OLED screen, and decoupling capas for the power supply module.
* There will be also to have some headers available for a servo (see: https://raw.githubusercontent.com/kelu124/echomods/master/croaker/images/kit-overaview.png ).
* It would be great to have a double header available for the different tracks at the level of the stripboard.
* And overall, some marking on the board level to easily identify the tracks

### Overall board is

![](/croaker/images/kit-overall.png)

### Full board is

![](/doj/images/doj-loaded.jpg)


### Empty board is

![](/doj/images/doj-unloaded.jpg)


## Connection between modules

Trinket :
* BAT to 5V track (track #2) and GND on GND track  (track #1)
* Pin 12 to Pulse A (#9) and Pin 13 to Pulse B (#10)
Feather :
* Pin A1 to Signal out track (#3)
* Pin B5 to Track Pulse A (#9)
* GND to GND (track #1) and VUSB to 5V (track #2)
Power supply :
* 3.3V connected to 3.3V track (track #19)
* 5V on the 5V track (track #2)
* GND on GND track  (track #1)
OLED :
* VCC to 3.3V track (track #19) and GND on GND track  (track #1)
* SCL to Feather WICED SCL pin
* SDA to Feather WICED SCL pin
Small TFT

Double header not connected to anything (tracks cut). Double header for breakout of TFT screen.


## Outcome ?

Should look like this:

![](/doj/images/pcb_test.png)



