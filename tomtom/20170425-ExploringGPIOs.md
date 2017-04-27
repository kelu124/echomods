# Tomtom 

How can we unlock the GPIOs?

## What I need

![](/tomtom/images/pulses.png)

## Remarks from USBFM

* Looks like the pigpio has a dedicated C interface: http://abyz.co.uk/rpi/pigpio/cif.html

```
#!/bin/bash 
sudo pigpiod cat /dev/pigout& 
echo "mg 18 5" >/dev/pigpio 
echo "hp 18 2250000 100000" >/dev/pigpio
```

* What is HP? See http://abyz.co.uk/rpi/pigpio/pigs.html#HP

* 2250000: frequency in Hz

_In code I defined the pulse to occupy 10% of the duty cycle, which is around 40ns with a period of 440ns_ -- "That magic 5 changes the GPIO18 pin mode to ALT5"

Other stuff:

* uint32_t gpioTick(void)
* Returns the current system tick.
* Tick is the number of microseconds since system boot. 
