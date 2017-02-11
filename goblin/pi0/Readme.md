# Raspberry pi 0 test

## Rationale

Trying to get RPi0 plugged into the Goblin 3Msps ADC.


## Worklog

### 2017-02-11 Testing speed of GPIOs

#### Code

* Code found on http://d-fence.sytes.net/raspberry-pis-gpio-speed/

Compiled with gcc [gpio.c](/goblin/pi0/gpio.c) -o gpio

#### Results

![](/goblin/pi0/images/TEK0000.JPG)

Max speed seems to be 33.33MHz, up from 25MHz from the Rpi.


## Tips

* Ethernet over USB does not work really good
* sudo nmap -sn 192.168.1.0/24 to help find the RPi0 on the network

