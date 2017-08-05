## Quickstart of the Pulser module

### The [pulser](/tobo/) module

The assembly is detailed below:

![](/tobo/images/QS_tobo.jpg)

Read more on [the dedicated page](/tobo/).

### Controlling the pulser

The pulser is controled by a double signal, one, _PulseOn_, to start the pulse, and the other, _PulseOff_, to bring the pulse back to 0. 

__Note__: The setup presented here was with the [Raspberry Pi + ADC setup](/elmo/data/arduino/20170611-arduino.md). Raspberry Pi kernel modules and software can be found following the previous link.

The _PulseOn_, _PulseOff_ and signal output are represented below.

## Calibration and tests

Yellow is PulseOn, Blue is PulseOff. The logic is also 3.3V and 5V tolerant. Here, the control signals were produced with a raspberry pi. 

__For the sake of testing, keep PulseOn as long as your pulse needs to be, but keep PulseOff (or "Damper") on for something around 5 - 10 us.__ You can test for example with the [simple code here](/tobo/source/tobo_pulser.ino), inspired from the retired pulse control [OneEye](/retired/oneeye/).


#### Controls

![](/tobo/images/2017/TEK0007.JPG)

#### Output on the pulser SMA to transducer

![](/tobo/images/2017/TEK0009.JPG)

