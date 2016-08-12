
# **WiFiMCU** #
[Latest Firmware Download ](https://github.com/SmartArduino/WiFiMCU/releases)[![Download](https://img.shields.io/badge/download-~200k-orange.svg)](https://github.com/SmartArduino/WiFiMCU/releases)<br/>
<br/>
WiFiMCU is developed based on EMW3165 module produced by [MXCHIP.INC](http://www.mxchip.com/). A Lua interpreter is builded inside with hardware support. A light weight file system and socket protocols can help to realize IoT development easily and quickly. Basically, you can load Lua scripts on your device and then run it on board with nothing more than a terminal connection. <br/>
Enjoy Programming!<br/>

<pre>
  ;   .  . .___ .  . __ .  .      ,--.
 ["]  |  |o[__ o|\/|/  `|  | ,<-|__oo|
/[_]\ |/\|||   ||  |\__.|__| /  |//  |
 ] [                            /o|__|  [www.wifimcu.com@2015]
</pre>

#Overview
- Based on Lua 5.1.4 (package, string, table, math modules)<br/>
- Build-in modules: mcu,gpio, timer, wifi, net, file, pwm, uart, adc, spi, i2c, bit<br/>
- Modules to be builded: 1-wire, bit, mqtt...<br/>
- Integer version provided<br/>
- `Free memory >48k bytes`<br/>

##Highlights
#####Cortex-M4 microcotroller<br/>
- `STM32F411CE`<br/>
- 100MHz,Cortex-M4 core<br/>
- 2M bytes of SPI flash and 512K bytes of on-chip flash<br/>
- 128K bytes of RAM<br/>
- Operation Temperature：-30℃ ~ +85℃<br/>

#####Multi-Interface<br/>
- 18 GPIO Pins<br/>
- 2 UARTs<br/>
- ADC(5)/SPI(1)/I2C(1)/USB(1)<br/>
- SWD debug interface<br/>
- 11 PWMs<br/>

#####`Broadcom IEEE 802.11 b/g/n RF Chip`<br/>
- Supports 802.11 b/g/n<br/>
- WEP,WPA/WPA2,PSK/Enterprise<br/>
- 16.5dBm@11b,14.5dBm@11g,13.5dBm@11n<br/>
- Receiver sensitivity：-87 dBm<br/>
- Station,Soft AP and Station+Soft AP<br/>
- CE, FCC suitable<br/>

#GPIO table
<a id="gpio pin table"></a>
<table>
  <tr>
    <th scope="col">GPIO index</th><th scope="col">Alternative Function</th><th scope="col">Discription</th>
  </tr>
  <tr>
    <td>D0</td><td>GPIO/BOOT</td><td>WiFiMCU would enter into Bootloader Mode, if D0 goes to LOW</td>
  </tr>
  <tr>
    <td>D1</td><td>GPIO/PWM/ADC</td><td></td>
  </tr>
  <tr>
    <td>D2</td><td>GPIO</td><td></td>
  </tr>
  <tr>
    <td>D3</td><td>GPIO/PWM</td><td></td>
  </tr>
  <tr>
    <td>D4</td><td>GPIO</td><td></td>
  </tr>
  <tr>
    <td>D5</td><td>GPIO</td><td>SWD Flash Programming Pin: swclk</td>
  </tr>
  <tr>
    <td>D6</td><td>GPIO</td><td>SWD Flash Programming Pin: swdio</td>
  </tr>
  <tr>
    <td>D7</td><td>GPIO</td><td></td>
  </tr>
  <tr>
    <td>D8</td><td>GPIO/PWM</td><td>Uart1 rx pin: RX1</td>
  </tr>
  <tr>
    <td>D9</td><td>GPIO/PWM</td><td>Uart1 tx pin: TX1</td>
  </tr>
  <tr>
    <td>D10</td><td>GPIO/PWM</td><td>I2C interface: SCL</td>
  </tr>
  <tr>
    <td>D11</td><td>GPIO/PWM</td><td>I2C interface: SDA</td>
  </tr>
  <tr>
    <td>D12</td><td>GPIO/PWM</td><td></td>
  </tr>
  <tr>
    <td>D13</td><td>GPIO/PWM/ADC</td><td></td>
  </tr>
  <tr>
    <td>D14</td><td>GPIO/PWM</td><td></td>
  </tr>
  <tr>
    <td>D15</td><td>GPIO/PWM/ADC</td><td></td>
  </tr>
  <tr>
    <td>D16</td><td>GPIO/PWM/ADC</td><td></td>
  </tr>
  <tr>
    <td>D17</td><td>GPIO/ADC</td><td>A LED is connected on WiFiMCU board</td>
  </tr>
</table>

### [Tutorial](https://github.com/SmartArduino/WiFiMCU/tree/master/Document)<br/>
* [Basic](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter1.html)<br/>
  * [Install USB Driver](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter1.html)<br/>
  * [Quickly Start with WiFiMCU STUDIO](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
    * [Prepare](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
    * [Power UP](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
    * [Check the COM Port](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
    * [Run WiFiMCU STUDIO](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
    * [Toggle LED on WiFiMCU board](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
    * [Start AP mode](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
    * [Setup a simply webserver](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/charpter1_1.html)<br/>
  * [Use SecureCRT (Optional)](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter1_2.html)<br/>
* [Adavance](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter2.html)<br/>
  * [Flash LED -use TIMER module](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter2_1.html)<br/>
  * [Breathing LED -use PWM module](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter2_2.html)<br/>
  * [Socket programming –use Net module](https://github.com/SmartArduino/WiFiMCU/tree/master/Document/demos/5%20net)<br/>
  * [WiFi to Serial transparent transmission](https://github.com/SmartArduino/WiFiMCU/blob/master/Document/demos/9%20uart/2%20uart_2_wifi_trans.lua)<br/>
  * [Update Firmware](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter2_5.html)<br/>
    * [Get the latest firmware](https://github.com/SmartArduino/WiFiMCU/releases)<br/>
    * [Use WiFiMCU STUDIO to update firmware](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter2_5.html)<br/>
    * [Use SecureCRT to update firmware](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter2_6.html)<br/>
    * [Use SWD to update firmware](http://fineshang.gitbooks.io/wifimcu-based-on-emw3165-user-manual/content/chapter2_7.html)<br/>

###How to Use
* [Using MCU Module](https://github.com/SmartArduino/WiFiMCU/tree/master/Demos/1%20mcu)<br/>
* [Using GPIO Module](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/2%20gpio)<br/>
  * [GPIO input demo](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/2%20gpio/gpio_input_demo.lua)<br/>
  * [GPIO output demo](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/2%20gpio/gpio_output_demo.lua)<br/>
* [Using TIMER Module](https://github.com/SmartArduino/WiFiMCU/tree/master/Demos/3%20timer)<br/>
* [Using WIFI Module](https://github.com/SmartArduino/WiFiMCU/tree/master/Demos/4%20wifi)<br/>
  * [Set up a simple AP](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/4%20wifi/wifi_ap_demo.lua)<br/>
  * [Set up a advanced AP](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/4%20wifi/wifi_ap_adv_demo.lua)<br/>
* [Using NET Module](https://github.com/SmartArduino/WiFiMCU/tree/master/Demos/5%20net)<br/>
  * [Set up a TCP Server](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/5%20net/1%20net_tcpserver_demo.lua)<br/>
  * [Set up a webserver](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/5%20net/1-1%20webserver.lua)<br/>
  * [Set up a TCP Client](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/5%20net/2%20net_tcpclient_demo.lua)<br/>
  * [Set up a UDP Server](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/5%20net/3%20net_udpserver_demo.lua)<br/>
  * [Set up a UDP Client](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/5%20net/4%20net_udpclient_demo.lua)<br/>
* [Using FILE Module](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/6%20file/file_demo.lua)<br/>
* [Using PWM Module](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/7%20pwm/pwm_breathing_LED.lua)<br/>
* [Using ADC Module](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/8%20adc/adc_demo.lua)<br/>
* [Using UART Module](https://github.com/SmartArduino/WiFiMCU/tree/master/Demos/9%20uart)<br/>
  * [Uart receive data](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/9%20uart/1%20uart_demo.lua)<br/>
  * [WiFi to Serial transparent transmission](https://github.com/SmartArduino/WiFiMCU/blob/master/Demos/9%20uart/2%20uart_2_wifi_trans.lua)<br/>


###Reference
[WiFiMCU Function Refecence](https://github.com/SmartArduino/WiFiMCU/blob/master/Document/WiFiMCU%20Reference_2015-9-5.pdf)<br/>
[WiFiMCU Tutorial](https://raw.githubusercontent.com/SmartArduino/WiFiMCU/master/Document/WiFiMCU_Tutorial.pdf)<br/>
[EMW3165 Datasheet(English)](https://raw.githubusercontent.com/SmartArduino/WiFiMCU/master/Document/EMW3165_datasheet.pdf)<br/>
[EMW3165 Datasheet(Chinese)](https://raw.githubusercontent.com/SmartArduino/WiFiMCU/master/Document/EMW3165_datasheet(Chinese).pdf)<br/>
[WiFiMCU SCH](https://raw.githubusercontent.com/SmartArduino/WiFiMCU/master/Document/WiFiMCU_SCH.pdf/)<br/>
[EMW3165 Datasheet(English)](https://github.com/SmartArduino/WiFiMCU/blob/master/Document/EMW3165_datasheet.pdf)<br/>
[EMW3165 Datasheet(Chinese)](https://github.com/SmartArduino/WiFiMCU/blob/master/Document/EMW3165_datasheet(Chinese).pdf)<br/>
[WiFiMCU SCH](https://github.com/SmartArduino/WiFiMCU/blob/master/Document/WiFiMCU_SCH.pdf/)<br/>


###Resource
Home site:www.wifimcu.com<br/>
discussion:www.emw3165.com<br/>
http://bbs.smartarduino.com<br/>
http://bbs.doit.am<br/>

###The IDE tool for wifimcu can be found here<br/>
[WiFiMCU STUDIO](https://github.com/SmartArduino/WiFiMCU-STUDIO)(supported by WiFiMCU Team)<br/>
[WMC WiFiMCU CLI](https://github.com/zpeters/wmc) [Article](http://thehelpfulhacker.net/2015/11/15/wifimcu-command/)(Thanks for Zpeters' contribution)

#Program demos
####Setup a AP

```lua
    cfg={ssid='Doit_3165',pwd=''}
    wifi.startap(cfg)
```
####WebServer

```lua
   skt = net.new(net.TCP,net.SERVER) 
   net.on(skt,"accept",function(clt,ip,port) 
   print("accept ip:"..ip.." port:"..port.." clt:"..clt) 
   net.send(clt,[[HTTP/1.1 200 OK
   Server: WiFiMCU
   Content-Type:text/html
   Content-Length: 28
   Connection: close
   
   
   <h1>Welcome to WiFiMCU!</h1>]])
   end)
   net.start(skt,80) 
```
####Connect Wireless Router

```lua
   print(wifi.sta.getip())  --check ip
   0.0.0.0
   cfg={ssid="Doit",pwd="123456789"} wifi.startsta(cfg) --sta mode connect
   print(wifi.sta.getip())  --check ip
   0.0.0.0
   print(wifi.sta.getip())  --check ip
   192.168.1.116 
```
####Connect Remote Server

```lua
   clt = net.new(net.TCP,net.CLIENT)
   net.on(clt,"dnsfound",function(clt,ip) print("dnsfound clt:"..clt.." ip:"..ip) end)
   net.on(clt,"connect",function(clt) print("connect:clt:"..clt) end)
   net.on(clt,"disconnect",function(clt) print("disconnect:clt:"..clt) end)
   net.on(clt,"receive",function(clt,data) print("receive:clt:"..clt.."data:"..data) end)
   net.start(clt,6579,"115.29.109.104")
```
####GPIO Operation

```lua
   gpio.mode(17,gpio.OUTPUT)
   gpio.toggle(17)
   gpio.write(17,gpio.HIGH)
   gpio.write(17,gpio.LOW)
   gpio.mode(17,gpio.INPUT)
   =gpio.read(17)
   1
   =gpio.read(17)
   0
```
####Timer

```lua
   function tmr_cb() print('tmr1 is called') end 
   tmr.start(1,1000,tmr_cb)
   tmr1 is called
   tmr1 is called
```
####File Operation

```lua
   file.open ("test.lua","w+")
   file.write("this is a test")
   file.close()
   file.open ("test.lua","r")
   data=file.read()
   print(data)
   this is a test
   file.close()
```
####Auto start

```lua
   file.open ("init.lua","w+")
   file.write("print('Hello WiFiMCU!')")
   file.close()
   mcu.reboot()
```

####Acknowledgements
Thanks to [eLua project](https://github.com/elua/elua),[NodeMCU project](https://github.com/nodemcu/nodemcu-firmware),[spiffs file system](https://github.com/pellepl/spiffs)<br/>

####Doctors of Intelligence & Technology<br/>
[DoIT website](http://www.doit.am) <br/>
[WiFiMCU Dev Kit](http://www.smartarduino.com)<br/>

####Version log<br/>
##### v0.9.8.1 @2016-02-22<br/>
* MQTT module:<br/>
    * Fix mqtt publish bug<br/>

##### v0.9.8 @2015-12-16<br/>
* Add string.md5calc/md5 for md5 calculation<br/>

##### v0.9.7 @2015-12-14<br/>
* (under beta version)<br/>
* Mico SDK Lib:<br/>
    * Update to SDK 2.4.0<br/>
* WiFi module:<br/>
    * Add easylink and airkiss function in wifi module<br/>
    * Add sethostname/sethostname function<br/>
* GPIO module: <br/>
    * Enhance GPIO interrupt code to avoid errors in its callback function<br/>
* Timer module:<br/>
    * Enhance Timer interrupt checking method<br/>
* Uart module: <br/>
    * Use pushlstring for uart recieve data to avoid data missing<br/>
* Net module:<br/>
    * Improve TCP Client connect callback function<br/>
* MQTT module:<br/>
    * Use Mico mqtt lib(V0.1.2)<br/>
    * Demo:https://github.com/SmartArduino/WiFiMCU/tree/master/Demos/12%20mqtt<br/>
* Others:
    * Rearrangement the source code files and folders<br/>
    * Improve wifimcu upload function, LUA_MAXINPUT 128->512<br/>
    * Support utf-8 charset<br/>
    * Optimize WiFiMCU STUDIO upload file function<br/>
    * Set init.lua or init.lc to start up<br/>
    * Fix dofile bug in tmr/gpio<br/>
    * Fix bootloader gpio initize bug,add compiling bootloader switch for MicoKit<br/>
More details see [change.log](https://github.com/SmartArduino/WiFiMCU/blob/master/change.log)<br/>
