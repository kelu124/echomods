# Uniboard

* [Amp source files](/goblin/source/goblin_altium.zip)
* [Goblin source](/goblin/source/goblin_altium.zip)
* [Pulser source](/alt.tbo/alt.tobo.zip)


## Overall remarks

* Form factor: Raspberry Pi Hat (with screws places for both Raspberry Pi 3 and Raspberry Pi 0)
* Have the __Oled__, __ADC__, __TGC__, __HV__, __Pulser__, __capa touch__ parts clearly separated (rectangle silkcreen + names)
  * Ideally, rectangles with the different functions as defined on a block diagram, over the 6 items above.
* ADC: 48Msps+, 10bit+
* RAM if necessary (1s, 500us repeat, is 2000 lines)
* Acquisitions of up to 150/200us
* Layers: 4 layers, if possible to have the RF noise as low as possible
* Components: easily sourcable in MacroFab (eg: initial transformer on goblin is not easy to find)
* Raspberry Pi headers connections:
  * Trigger
  * i2c
  * spi
* Onboard 5V alim

## OLED 

* Keeping room for the the 0.96" OLED screen variant on the top of the board for quick display + debug

## ADC
 
* As fast a possible
* assorted ram

## TGC (ex goblin board)

* MD0100 or equivalent for protection of VGC
* Jumper : to select gain (3 choices)
  *  from pot (as per goblin) 
  *  from external (0 to 1V - connected to the 6x2 header Gain) as per goblin
  * or from DAC (8 bit DAC, from 0 to 1V, with OpAmp to secure up to 100mA) to gain

## HV (ex tobo board)

* Jumper: Selectable 0, 25, 50 or 75V through MUX + select LEDS to show which is powered

## Pulser (ex tobo board)

* Unipolar, only with Pon and Poff (routed to 2x20 Raspberry header)
* Jumper: route pulse either to SMA or to "artificial" piezo   (see RLC) 
  * "RLC"-like design to be .. designed

## Other

* Power-on LEDs on the 3.3V line and 5V lines
* Would be good to have an onboard miniusb plug for easy power supply
* LEDs indicators for the 3 Muxes

## Capa touch

* The board needs 2 or 3 touch-pad like zones, to be connected to i2c bus + 1 interrupt pin for detection of touching this zones, for controls (single acq, controls, settings, ...)
  * Trig pin to be connected to rpi

# Back and forth




# IOs

## Petite

Using motherboard

* In (buffered)
  * 1: trigger (buffered)
  * 11: ADC + clock

* Out
  * 2: LED status -- IOExpander
  * 1: Pon (buffered)
  * 1: Poff (buffered)
  * 1: GPIO21 (buffered)
  * 2: external logic (buffered)
  * 2: buttons  -- IOExpander

* Both (buffered)
  * 2: I2C  (buffered)

* 3: Programming (SPI selected through Jumper)
  * 3: SPI
  * Slave select via external jumper

Total IOs: 28

## Grande

* 20: In (MUXes controlled by Jumper)
  * 2: Logic MUX HV (0, 25, 50, 75) -- IOExpander (jumpers)
  * 11: ADC (data + clock)
  * 2: MUX Gain (GND, pot, ext, DAC)  -- IOExpander (jumpers)
  * 1: Logic Piezo emulateur MUX -- IOExpander (jumpers)
  * 2: Buttons  -- IOExpander
  * 1: External Input(s) (trackers / uart)

* 13: Out:
  * 1: Pon (for pulser)
  * 1: Poff (for pulser)
  * 2: Status LEDs (or as needed) -- IOExpander
  * 9: DAC (for gain) (8bit +1 clock ?)

* 13: Both:
  * 11: RAM connection (for parallel ram)
  * 2: I2c

* 3: Programming (SPI selected through Jumper)
  * 3: SPI
  * Slave select via external jumper

Total IOs: 
* 39 IOs -> Maybe lower with a SPI-DAC for Gain ?
* 9 IOs

# Code

## Small

* Trig goes high, starts full speed acquisition of the signal, stores into RAM
* If not busy acquiring, acquired data is available through i2c

## 

* 2 modes
  * 1 ligne
  * Full acquisition

* Trig goes high
  * Pon for X ns
  * Poff for Y ms
  * Acquisition starts
  * repeat for as many lines as Z

* i2c gets data
* i2c to set X, Y, and Z


