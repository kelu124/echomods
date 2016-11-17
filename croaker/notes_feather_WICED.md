# Feather WICED [](@description Random notes on WICED)

## Facts

### General

* Throughput test : https://learn.adafruit.com/introducing-the-adafruit-wiced-feather-wifi/throughput
* Built-in WiFi ( Broadcom radio )
* Built in battery adapter
* __Double M3__ ! Based on a STM32F205 -- 120MHz ARM Cortex M3 MCU + BCM43362 (Broadcom radio avec un M3)
* BSP required : https://learn.adafruit.com/introducing-the-adafruit-wiced-feather-wifi/get-the-wiced-bsp

### Specs:

* STM32F205
* 

## Setup ?

* https://learn.adafruit.com/introducing-the-adafruit-wiced-feather-wifi/arduino-ide-setup

## Getting more on the ADC.

* https://forum.arduino.cc/index.php?topic=346761.0
* http://microcontroleurs.blogspot.fr/2015_07_01_archive.html?view=sidebar interessant!
* These two (fond on [github](https://github.com/search?l=arduino&q=adc_init%28+libmaple&type=Code&utf8=%E2%9C%93)) are lacking the __'ADC_PRE_PCLK2_DIV_2' was not declared in this scope__
    * https://github.com/stevstrong/Audio-sample/blob/a6d27773162579423c97a262097aec18fad0362c/stm32/STM32_Simple_AnalogInput.ino
    * https://github.com/RhoneAlpes/stm32f123c8t6_data_acquisition/blob/c1c0d09526451c6f4039de78bfb6487f13173192/STM32_DATA_ACQ_V02.ino
* http://www.stm32duino.com/viewtopic.php?t=847 1Msps acquisition

 RCC_ADCPRE_PCLK_DIV_2 can replace ADC_PRE_PCLK2_DIV_2 .. or so it seems

 #include <libmaple/adc.h>

## For getting more on the ADCs:

* http://www.stm32duino.com/viewtopic.php?t=757&start=10





