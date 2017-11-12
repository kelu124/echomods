---

layout: post

title: 2017-11-11 fpga need to move now

---


**FPGA**

-   Open-source: ICE40 & RPi
-   Perfs: SRAM + HX4K at least: IceZero ? Take the design, throw in 8Mb
    instead of 4Mb
-   Mount it on a Analog Board w/ ADC
-   Expose:
-   i2c: min. a OLED screen space kept on board
-   Gain Output
-   Logic (bidirectionally buffered): Trig, Pon, Poff, 2 top tours, 2
    extra IOs
-   mini USB for power on
-   5V and GND pads
-   ADC: 10 bit, 65Msps
-   10 bits measures (or pseudo-12 with decimation ? by x3)
-   6 bits remaining by acq: 2 top tour, Pon, Poff, 2 IOs
-   Interact
-   2 buttons
    -   Manual Trig
    -   Select mode
-   4 LEDs
    -   Single mode
    -   Loop mode
    -   Acq (ready: on, data in: flashing)
-   Modes:
-   *Single capture*
    -   200us long captures at 65Msps : 208kbits
    -   Capacity of close to 35+ captures if needed in RAM
-   *Loop*
    -   130us acq at 20 Msps over 16 bits: 42kbits
    -   That's 190 lines over a 8192000 bit SRAM
-   Transfer back to RPi through SPI
-   Variables (to be stored as a header of the file sent back)
-   Pon length
-   Poff length
-   Tdelay length
-   Tacq
-   RT -- repetition
-   N acq
-   Implicit:
    -   ADC bits used
    -   Mode
-   Silkscreening:
-   Keeping a clear markup of the different functions

ebay *is Kretz VSW3-5 linear ?* same for SW4/5B ?

-   S-VDW5-8B for parts ? endoprobe

=======

