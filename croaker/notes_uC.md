# Microcontrolers and chips

## Microcontrolers

| ID | Name | Chip | Comments | ADC | Price | COmments | 
| :--: | -------- | -------------- | ---------- | ---- | ---- | ---- | 
| 1 | [WiFiMCU](https://hackspark.fr/fr/wifimcu-wireless-wifi-dev-board-lua-scripting-emw3165-wifi-32bit-mcu.html) | EMW3165 - __STM32F411CE__ | Cortex-M4 core at 100MHz | 1_12-bit, 2.4 MSPS A/D converter: up to 16 channels | 8$ | Has wifi | 
| 2 | Espruino Pico | __STM32F401CDU6__ | ARM Cortex M4, 384kb flash, 96kb RAM | 1_12-bit, 2.4 MSPS A/D converter | 24$ (Adafruit) | No wifi, smart USB plug, DSP instructions | 
| 3 | [Feather Wiced](https://www.adafruit.com/products/3056) | __STM32F205RG__ | 120MHz ARM Cortex M3 MCU + BCM43362 (avec un M3) | 3 x 12-bit, 0.5us ADCs with up to 24 channels and up to 6 MSPS in triple interleaved mode | 34$ | Has wifi, support for battery | 
| 4 | STM32L471QE | __STM32L471QE__ | NoP | 3_ 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling | ?? | ?? | 
| 5 | STM32L476 | __STM32L476VGT6__ | NOP | 3_ 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling | [19$ dev-kit](http://www2.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-discovery-kits/32l476gdiscovery.html?icmp=pf261635_pron_pr_sep2015&sc=stm32l476g-disco) | Cheap, powerfull, nowifi | 
| 6 | ESP32 | ?? | NoP | ?? | ?? | ?? | 
| 7 | ESP8277 | Tensilica Xtensa LX106 | NoP | 80 MHz // 64 KiB of instruction RAM, 96 KiB of data RAM | 3$ | Has WiFi | 
| 8 | [Arduino Otto](http://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-3rd-party-evaluation-tools/ard-otto-stm32.html) | STM32F469BIT6 | NoP | 3×12-bit, 2.4 MSPS ADC: up to 24 channels and 7.2 MSPS in triple interleaved mode | ?? | FAAAAT. Has Wifi through a ESP8266 | 
| 9 | [NanoPi m3](http://nanopi.io/nanopi-m3.html) | Cortex-A53 S5P6818 SoC | ts dynamic frequency scales from 400M up to 1.4GHz. | ?? | ?? | Has WiFi | 
| 10 | [BBC Microbit](https://www.element14.com/community/community/stem-academy/microbit) | ?? | NoP | Not really a uC for us... | ?? | ?? | 
| 11 | [Nucleo F401RE ](http://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-nucleo/nucleo-f401re.html?icmp=nucleo-ipf_pron_pr-nucleo_feb2014) | STM32F401RE | ?? | Joris working with this one | ?? | ?? | 
| 12 | [stm32f3](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32f3-series/stm32f334/stm32f334r8.html) | ?? | NoP | 12-bit ADC 5 MSPS  | 5-10$ | Analog and DSP with FPU ARM Cortex-M4 MCU with 64 Kbytes Flash, 72 MHz CPU, CCM, 12-bit ADC 5 MSPS | 
| 13|  [PIC32MZ](hhttp://eu.mouser.com/new/microchip/microchip-pic32mz-mcus/) | PIC32MZ | NoP | 12-bit, 28MSPS, 48-channel ADC module | 5$ | 200MHz/330 DMIPS, M-Class Core, DSP-enhanced core, 12-bit, 28MSPS, 48-channel ADC module | 

* Feather (inclus un m3) : STM32F205 + BCM43362 qui a un m3
* Feather: meme chose que le photo, mais en compatible Arduino
* https://community.broadcom.com/servlet/JiveServlet/showImage/2-19579-3826/bcm43362-damosys.png

## Studying chips

| ID | Name | Details | Comments | 
| :--: | -------- | -------------- | ---------- | 
| 1 | STM32F411CE | | | 
| 2 | STM32F401CDU6 | | | 
| 3 | stm32f407 | Recommended for data processing by Dmitry (GeekTimesRu) | | 

## Other stuff

| ID | Name | Chip | Comments | ADC | Price | COmments | 
| :--: | -------- | -------------- | ---------- | ---- | ---- | ---- | 
| X | BBC MicroBit | A voir | NoP | ?? | ?? | ?? | 


