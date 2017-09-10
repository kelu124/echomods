---
who: Marc
place: Au
pos: -37.9712304,144.4913092
entity: Au
---
 

The [precise.py](/include/community/Marc/precise.py) generates a pulse for the pulser module(tobo).  Got good results with a very sharp pulse measured via oscilloscope.
Before you can run it the first time in the pi terminal you need to run `sudo pigpiod` in the terminal.
The [second is the spi](/include/community/Marc/spi.py) for talking to the adc on the (goblin).

* spi-dev library link: https://github.com/doceme/py-spidev
* installation guide: https://www.raspberrypi.org/forums/viewtopic.php?f=44&t=56669


