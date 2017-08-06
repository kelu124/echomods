# Detecting i2c addresses

Source: https://www.raspberrypi.org/forums/viewtopic.php?f=63&t=114401

#### Code source

Before, need to execute __pigpiod__

 sudo pigpiod

````
#!/usr/bin/env python

# 2015-06-30
# i2c_detect.py
# Public Domain

import pigpio

pi = pigpio.pi() # connect to local Pi

for device in range(128):

      h = pi.i2c_open(1, device)
      try:
         pi.i2c_read_byte(h)
         print(hex(device))
      except: # exception if i2c_read_byte fails
         pass
      pi.i2c_close(h)

pi.stop # disconnect from Pi

````

#### Install

See [here for finetuning](https://learn.adafruit.com/ssd1306-oled-displays-with-raspberry-pi-and-beaglebone-black/usage).

````
sudo apt-get update
sudo apt-get install build-essential python-dev python-pip git python-imaging python-smbus
sudo pip install RPi.GPIO 
git clone https://github.com/adafruit/Adafruit_Python_SSD1306.git
cd Adafruit_Python_SSD1306
sudo python setup.py install 
````
