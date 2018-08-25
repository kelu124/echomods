## Why a FPGA board ?


Non destructive testing and imaging ultrasound modalities have been around since the '50s in . More and more ultrasound-based initiative are emerging, mostly focusing on image processing - while hardware has been left behind. Several teams have produced succesful designs for the different possible uses, mostly efforts from research laboratories. Most have been used on commercial US scanners, traditionaly used as experiment platforms, but they are not cheap, and yield very little in terms of data access and control. Others have been developped in labs, but, sadly, very few have been open-sourced. Let's tackle this!

It has also been shown that simple (be it low-power, low-cost and small) can be achieved - and this, even for relatively complex systems, based on 16 to 64  parallel   channels   front-end  processing and software back-end processing (embedded PC or DSP). This makes it a bit more complex for the layman, hobbyist, or non-specialist researcher to use, not to mention the very little information that is accessible.

## Hardware specifications and features


1. __FPGA__: Lattice iCE40HX4K - TQFP 144 Package
2. __Memory__:
  * 8 Mbit SRAM, 10ns, 512 k x 16, equivalent:
      * 65 full lines of 120us at 64Msps
      * 840 lines of 120us at 10Msps, 8 bits
  * 8 Mb SPI Flash for FPGA configuration 
3. __Ultrasound processing__:
  * __VGA__: AD8331 controled by DAC
  * __Pulser__: MD1210 + TC6320
  * __ADC__: 65Msps ADC10065
    * 10 bits of data / sample
    * 2 bits of line counters
    * 4 bits of IOs (counters, ...) 
4. __Parameters__: Settings programable via USB or Raspberry Pi 
  * Type of acquisition (one line / set of lines)
  * Number of lines
  * Length of lines acquisitions
  * Delay between acquisitions
  * Pulse width 
  * Delay between pulse and beginning of acquisitions
  * 200us time-gain-compensation programmable (8 bits, from 0 to Max), every 5us
5. __Extensibility__:
  * 2 x Pmod connectors
  * SMA plug for transducers
  * RPi GPIO
6. __User Interfaces__:
  * 2 x PMOD for IOs
  * 3 x push button (with software noise debouncing)
  * Jumpers for high voltage selection
7. __Input Voltage__: 
  * 5 V from RPi or USB
  * Uses 350mA-450mA at 5V
8. __Fully Open Source__:
  * Hardware: _github repository_
  * Software: _github repository_
  * Toolchain: _Project IceStorm_
  * Documentation: _gitbook_
9. __Operating Voltage__: 
  * FPGA and logics at at 3.3 V
  * High voltage at 25V, 50V, 75V
10. __Dimensions__: @todo!
11. __Weight__: @todo! 

## Comparative

| Tool           	| Murgen 	| echOmods        	| unoric               	|
|----------------	|--------	|-----------------	|----------------------	|
| Open Source    	| Yes    	| Yes             	| Yes                  	|
| ADC            	| 20Msps 	| 1Msps to 24Msps 	| 65Msps up to 100Msps 	|
| Onboard memory 	| 300 Mb 	| 10 Mb           	| 20Mb                 	|
| Price of a set	| 400$		| 450$			| 400$			|
| Modular		| Np		| Yes			| No			| 
