import spidev
import time

spi = spidev.SpiDev()
speed = 16000000
spi.open(0,0) # enabling onboard spi with enable channel 0
spi.max_speed_hz = speed
print spi.max_speed_hz
print spi.bits_per_word

try:
    while True:
        #resp = spi.readbytes(4) # Reads the response from 4 consecutive bytes
        #print(resp)
        # We will want to read in increments of 2 bytes the first 12 bits (/16) have values
except KeyboardInterrupt:
    spi.close()
