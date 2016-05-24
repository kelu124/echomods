# Microcontrolers and chips

## Microcontrolers

| ID | Name | Chip | Comments | ADC |Price| COmments |
|:--:|--------|--------------|----------|----|----|----|
| 1  | WiFiMCU |  EMW3165 - STM32F411CE | Cortex-M4 core at 100MHz | 1_12-bit, 2.4 MSPS A/D converter: up to 16 channels  | 8$ |Has wifi|
| 2  | Espruino Pico |  STM32F401CDU6 | ARM Cortex M4, 384kb flash, 96kb RAM | 1_12-bit, 2.4 MSPS A/D converter  | 24$ (Adafruit) |No wifi, smart USB plug, DSP instructions|
| 3  | [Feather Wiced](https://www.adafruit.com/products/3056) |  STM32F205RG|  120MHz ARM Cortex M3 MCU + BCM43362 (avec un M3)| 3 _ 12-bit, 0.5 _s ADCs with up to 24 channels and up to 6 MSPS in triple interleaved mode  | 34$ |Has wifi, support for battery|
| 4 | STM32L471QE | STM32L471QE | NoP | 3_ 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling | ?? | ?? |
| 5 | STM32L476 | STM32L476VGT6 | NOP | 3_ 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling, 200 _A/Msps  | [19$ dev-kit](http://www2.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-discovery-kits/32l476gdiscovery.html?icmp=pf261635_pron_pr_sep2015&sc=stm32l476g-disco) | Cheap, powerfull, nowifi |
| 6 | ESP8266 | A voir | NoP | ?? | ?? | ?? |
| 7 | ESP32 | A voir | NoP | ?? | ?? | ?? |

* Feather  (inclus un m3) : STM32F205 + BCM43362 qui a un m3
* Feather: meme chose que le photo, mais en compatible Arduino
* https://community.broadcom.com/servlet/JiveServlet/showImage/2-19579-3826/bcm43362-damosys.png
* ESP8266 -- ultra low power Micro 32bit CPU
* Excellent post - priority level : Important : http://www.eevblog.com/forum/microcontrollers/esp8266-native-spi-hardware-driver/
* _SPI runs at 40Mhz._ - so can be 2.4Msps 10bits
* HSPI -> http://d.av.id.au/blog/esp8266-hardware-spi-hspi-general-info-and-pinout/

## Studying chips

| ID | Name | Details | Comments |
|:--:|--------|--------------|----------|
| 1  | STM32F411CE |              |          |
| 2  | STM32F401CDU6 |              |          |
|3| stm32f407 | Recommended for data processing by Dmitry (GeekTimesRu) | |

