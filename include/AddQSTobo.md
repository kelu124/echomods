## Quickstart of the Pulser module

### The [pulser](/tobo/) module

The assembly is detailed below:

![](/tobo/images/QS_tobo.jpg)

Read more on [the dedicated page](/tobo/).

### Controlling the pulser

The pulser is controled by a double signal, one, _PulseOn_, to start the pulse, and the other, _PulseOff_, to bring the pulse back to 0. 

Resources for controlling the pulser can be seen using a [dedicated arduino control](/oneeye/) with [this code](/oneeye/oneye_pulser.ino) (for example, to be adjusted), or with a [raspberry pi](/tomtom/20170506-RPiAndTobo.md). You can of course try other ways!

The _PulseOn_, _PulseOff_ and signal output are represented below.

### Controls

Yellow is PulseOn, Blue is PulseOff. The logic is also 3.3V and 5V tolerant.


#### Controls

![](/tobo/images/2017/TEK0007.JPG)

#### Output on the pulser SMA to transducer

![](/tobo/images/2017/TEK0009.JPG)

