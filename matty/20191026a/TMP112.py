# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# TMP112
# This code is designed to work with the TMP112_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Temperature?sku=TMP112_I2CS#tabs-0-product_tabset-2


import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# TMP112 address, 0x48(72)
# Select Configuration register, 0x01(1)
#		0x60A0(24736)		Continous Conversion mode, 12-Bit Resolution, Fault Queue is 1 fault
#					Polarity low, Thermostat in Comparator mode, Disables Shutdown mode
#					Normal mode, 12-bit data
data = [0x60A0]
bus.write_i2c_block_data(0x48, 0x01, data)

time.sleep(0.5)

# TMP112 address, 0x48(72)
# Read data back from 0x00(0), 2 bytes, MSB first
data = bus.read_i2c_block_data(0x48, 0x00, 2)

# Convert the data
temp =(data[0] * 256 + data[1]) / 16
if temp > 2047 :
	temp -= 4096
cTemp = temp * 0.0625
fTemp = cTemp * 1.8 + 32

# Output data to screen
print "Temperature in Celsius is : %.2f C" %cTemp
print "Temperature in Fahrenheit is : %.2f F" %fTemp
