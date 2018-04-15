# ESP8266 [](@description Notes on ESP8266)

## Factss
 
* throughput test : http://www.esp8266.com/viewtopic.php?f=5&t=245 + question posee sur http://www.esp8266.com/viewforum.php?f=6
* Livre: http://neilkolban.com/tech/esp8266/
* Question asked at http://stackoverflow.com/questions/37014547/esp8266-and-high-speed-external-adc
* http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family

* http://www.esp8266.com/viewtopic.php?t=669&p=3624 for HSPI
* http://www.eevblog.com/forum/microcontrollers/esp8266-native-spi-hardware-driver/
* https://github.com/MetalPhreak/ESP8266_Microwire_EEPROM
* https://github.com/MetalPhreak/ESP8266_SPI_Driver
* Built-in low-power 32-bit CPU: can double as an application processor 
* 802.11 b / g / n  - Wi-Fi Direct (P2P), soft-AP 
* http://www.instructables.com/id/ESP8266-ADC-Analog-Sensors/
* https://hackaday.io/project/4318-vu-meter-esp8266-ws2812b -- ESP8266+FFT+Teensy -- Person to contact!
* https://forum.pjrc.com/threads/34095-Teensy-3-2-ESP8266-12Q-High-Speed-ADC-Websocket _If you run the esp8266 wifi at 4.6 megabaud, you can get a minimum of 1 megabit per second throughput on wifi, a lot faster if your location does not have a ton of wifi signals, 2 mbit/s is typical. That is decent speed for my application._

* ESP8266 -- ultra low power Micro 32bit CPU
* Excellent post - priority level : Important : http://www.eevblog.com/forum/microcontrollers/esp8266-native-spi-hardware-driver/
* _SPI runs at 40Mhz._ - so can be 2.4Msps 10bits
* HSPI -> http://d.av.id.au/blog/esp8266-hardware-spi-hspi-general-info-and-pinout/

* [ebook on the ESP8266](https://leanpub.com/ESP8266_ESP32)
 
* [Les spores numériques](http://snhack.du-libre.org/doku.php?id=projets:spores_numeriques) sur snahck

* Big brother : __ESP32__

### Other versions

* Now, the ESP8266 v7 and v12, include an ADC (Analog digital converter) pin. This means that the ESP8266 module can process inputs from analog sensors. Light sensors, rheostats, force sensors, etc. 
* Those with many GPIOs : __ESP-04 et ESP-03__
* ESP-12-E/Q -- E-Series and ESP-14 have 22 pins available

* Un dongle ESP8266 ! http://www.aliexpress.com/store/product/latest-ESP8266-Serial-WIFI-wireless-module-development-board-microcontroller-portable-USB-Dongle-in-case/939205_32576358152.html
* https://hackaday.io/project/9309-esp8266-dongle
* http://esp8266-re.foogod.com/wiki/Memory_Map

## Some comments from Timothy

* Well, I have looked into that and figured out that the ESP8266 has 2 SPI interfaces (SPI and HSPI), the Flash memory uses the SPI interface, so we can attach the ADC to the HSPI interface and configure the SPI clock to between 1MHz to 80MHz depending on what we need. Therefore, it turns out it is possible to use an ADC with SPI interface, though it will involve some changes to the SPI registers but it can be done. 
* The HSPI is definitely better than a software SPI. However, without the DMA (the HSPI isn't connected to it) the CPU will be distracted every time when a word is received via the HSPI. This means that the 2M words/sec stream will interrupt the 80 MHz CPU of the module on every 40-th cycle. Depending on the wifi software of the module, this may be a quite long delay for the system. Fortunatelly, we can try to speed up the module to 160 MHz in case of insufficient performance.

## Some comments from Igor

* According to the PDF for ESP8266 it supports up to 40 MHz SPI clock (with default core clock) that is enough for our purpose. However, it doesn't have a DMA for the SPI master, so reading of the data from the ADC will be partially software based. This means that we can definitly pass the data through the SPI, but success of the further operations depends on the free CPU resources.




## Fun piratebox

* [Acolab : les micro pirate box](http://forum.acolab.fr/t/sub-micro-pirate-box-en-esp8266/57)
* [Les partageoirs de Gepeto](https://bricoles.du-libre.org/doku.php?id=esp8266:le_partageoir)
* [On Reddit](https://www.reddit.com/r/esp8266/comments/4awgtr/has_anyone_done_a_piratebox_type_thing_with_an/)
* [Webserver on ESP8266](https://github.com/esp8266/Arduino/blob/d218c4ead3df50ac9cbdfa7144698850a03f2066/hardware/esp8266com/esp8266/libraries/ESP8266WebServer/examples/SDWebServer/SDWebServer.ino)

