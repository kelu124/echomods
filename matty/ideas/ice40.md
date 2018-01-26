# links



* [ICE40 floorplan/layout viewer](https://knielsen.github.io/ice40_viewer/ice40_viewer.html)


* [Some IceStorm documentation and tools ](https://forum.mystorm.uk/t/some-icestorm-documentation-and-tools/298)
* __I'm just sayin' FT232RL is like $4.50, and a cheap ICE40 FPGA is $1.25, and you can roll yer own USB/Serial interface and have the code for the core itself :)__ (https://twitter.com/dildog/status/929777466700427265)

* [USB IP](https://opencores.org/websvn,listing?repname=usb&path=%2Fusb%2Ftrunk%2Frtl%2Fverilog%2F#path_usb_trunk_rtl_verilog_)

* [Very useful bootloader to load bitstreams on ICE40 FPGA.](https://github.com/tinyfpga/TinyFPGA-B-Series/tree/master/bootloader): The USB Bootloader implements a USB virtual serial port to SPI flash bridge. From the host computer's perspective, it looks like a serial port. This method was chosen because programming with serial ports is generally easier to understand than other USB-specific protocols. Commands boot into the user configuration or access the SPI flash are all transfered over this interface.

* P.S. Beware of several mistakes in Lattice's "Advanced ice40 I2C and SPI Usage Guide." Most notably I²C register set for UltraPlus devices is the "ice40LM and Ultra" set NOT the "ice40 UltraLite and UltraPlus set"! [status](https://twitter.com/fpga_dave/status/935108927603298304)

* May I suggest a TinyFPGA B2 board with an iCE40 LP8K part from @latticesemi? Available on @tindie https://www.tindie.com/products/tinyfpga/tinyfpga-b2/ … [tindie](https://www.tindie.com/products/tinyfpga/tinyfpga-b2/)

* https://blackmesalabs.wordpress.com/2016/10/24/sump2-96-msps-logic-analyzer-for-22/

## PLL source: 

* https://github.com/cliffordwolf/icestorm/commit/9ebed4d055f624274e9a793b7e0e8774ae88ace5

# 






https://twitter.com/openmeddev?cn=ZmF2b3JpdGU%3D&refsrc=email



Open-Source Lab: How to Build Your Own Hardware and Reduce Research Costs


MetaJNL


