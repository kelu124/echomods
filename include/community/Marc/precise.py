import pigpio
import time
pi = pigpio.pi()
# exit script if no connection
if not pi.connected:
    print('could not connect')
    exit()
else:
    print('program initiated')
    print(pi.get_hardware_revision())

pi.set_mode(23, pigpio.OUTPUT) # GPIO 16 pulse off as output
pi.set_mode(24, pigpio.OUTPUT) # GPIO 18 pulse on as output

pi.gpio_trigger(23, 1, 1)
pi.gpio_trigger(24, 50, 1)

time.sleep(1)
pi.stop()
