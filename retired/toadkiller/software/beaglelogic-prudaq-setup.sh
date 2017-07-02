#!/bin/bash

if [[ $EUID -ne 0 ]] ; then
  echo Try again as root
  exit 1
fi

cat <<EOF

This script is for use with the BeagleLogic system image as described in
the PRUDAQ QuickStart.  It uses GPIO pins on the BeagleBone to enable the
PRUDAQ, select inputs 0 and 4, and create a 500kHz GPIO clock using a
BeagleBone PWM channel.  You can edit the script if you want to select
other inputs or change the PWM frequency.

The script needs to be run again after a reboot.

EOF

if [[ ! -e /dev/beaglelogic ]] ; then
  echo "Can't find /dev/beaglelogic.  Are you sure you're running a"
  echo 'BeagleLogic system image?'
  exit 1
fi

echo 'Setting up BeagleLogic for continuous capture'
echo 1 > /sys/devices/virtual/misc/beaglelogic/triggerflags

# Enable GPIO 117 only if it's not enabled yet.
if [[ ! -e /sys/class/gpio/gpio117 ]] ; then
  echo 'Pulling down the enable pin (P9_25) to turn on the ADC.'
  echo 117 > /sys/class/gpio/export
fi
# Set it as an output and pull it low
echo out > /sys/class/gpio/gpio117/direction
echo 0 > /sys/class/gpio/gpio117/value

if [[ ! -e /sys/class/gpio/gpio111 ]] ; then
  echo 'Now we enable GPIO pins to control the analog switches that select'
  echo 'which pair of inputs will be read by the ADC'

  echo 111 > /sys/class/gpio/export
fi
if [[ ! -e /sys/class/gpio/gpio112 ]] ; then
  echo 112 > /sys/class/gpio/export
fi
if [[ ! -e /sys/class/gpio/gpio113 ]] ; then
  echo 113 > /sys/class/gpio/export
fi
if [[ ! -e /sys/class/gpio/gpio115 ]] ; then
  echo 115 > /sys/class/gpio/export
fi

# Set them all as outputs
echo out > /sys/class/gpio/gpio111/direction
echo out > /sys/class/gpio/gpio112/direction
echo out > /sys/class/gpio/gpio113/direction
echo out > /sys/class/gpio/gpio115/direction

echo 'Setting the switch control lines all to 0 to select inputs 0 and 4.'
# INPUT0A = GPIO 111 = P9_29
echo 0   > /sys/class/gpio/gpio111/value
# INPUT0B = GPIO 112 = P9_30
echo 0   > /sys/class/gpio/gpio112/value

# INPUT1A = GPIO 113 = P9_28
echo 0   > /sys/class/gpio/gpio113/value
# INPUT1B = GPIO 115 = P9_27
echo 0   > /sys/class/gpio/gpio115/value

# Alternatively, to read the other PRUDAQ inputs:
# Input 0: INPUT0B=0  INPUT0A=0
# Input 1: INPUT0B=0  INPUT0A=1
# Input 2: INPUT0B=1  INPUT0A=0
# Input 3: INPUT0B=1  INPUT0A=1

# Input 4: INPUT1B=0  INPUT1A=0
# Input 5: INPUT1B=0  INPUT1A=1
# Input 6: INPUT1B=1  INPUT1A=0
# Input 7: INPUT1B=1  INPUT1A=1


if [[ ! -e /sys/devices/ocp.3/pwm_test_P9_31.13 ]] ; then

  cat <<EOF
Now we enable PWM for pin P9_31. That pin provides the GPIO-based clock
option to the board.  In the prudaq_capture example code, this pin is
driven by PRU0 instead.  Make sure to set jumper J1 appropriately so that
the clock signal reaches the ADC.
EOF

  echo bone_pwm_P9_31 > /sys/devices/bone_capemgr.9/slots
  echo am33xx_pwm > /sys/devices/bone_capemgr.9/slots
  sleep 1
fi


echo 'Setting GPIO clock frequency to 500kHz.'

# Max period=1e9 (1 second)
# It won't let us set period < duty, so we set duty first.
# 50% duty cycle recommended. Units are nanoseconds.
echo 1000 > /sys/devices/ocp.3/pwm_test_P9_31.13/duty
# 2000ns period = 500kHz frequency
echo 2000 > /sys/devices/ocp.3/pwm_test_P9_31.13/period

cat <<EOF
Success!  Now you can read samples from /dev/beaglelogic

For example: $ hexdump /dev/beaglelogic

EOF
