---

layout: post

title: 2017-11-11 fpga need to move now

---


**FPGA**

-   Open-source: ICE40 & RPi
-   Perfs: SRAM + HX4K at least: IceZero ? Take the design, throw in 8Mb
    instead of 4Mb
-   IceZero board design can be reused
-   Silkscreening:
-   Keeping a clear markup of the different functions
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
    -   130us acq at 24 Msps over 16 bits: 57.6 kbits
    -   That's more than 130 lines over a 8000000 bit SRAM
-   Transfer back to RPi through SPI
-   Variables (to be stored as a header of the file sent back)
-   Pon length
-   Poff length
-   Tdelay length
-   Tacq
-   RT -- repetition time
-   N acq -- number of acquisition
-   Implicit:
    -   ADC bits used
    -   Mode (loop or single)
-   Expose:
-   i2c: min. a OLED screen space kept on board
-   Gain Output
-   Logic (bidirectionally buffered): Trig, Pon, Poff, 2 top tours, 2
    extra IOs
-   mini USB for power on
-   5V and GND pads

ebay \* is Kretz VSW3-5 linear ? \* same for SW4/5B ?

-   S-VDW5-8B for parts ? endoprobe

