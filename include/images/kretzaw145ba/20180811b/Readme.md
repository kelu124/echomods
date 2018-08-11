#  `20180811b` - Making a probe work

## Experiment

The [20180811a experiment](/include/images/kretzaw145ba/20180811a/20180811a-Processing.ipynb) showed that it's possible to get some echoes from a probe. It yielded some echoes:

![](/include/images/kretzaw145ba/20180811a/20180811a-3first-lines.jpg)

![](/include/images/kretzaw145ba/20180811a/20180811a-3first-lines-fft.jpg)

# Let's see if we can make it move

## Yes! 

With an update of STEP on a DRV8834 pololu driver, it moves. However, the motor is to be plugged in a specific way.

It seemed the bobins of the stepper where:
* Grey (2) + Purple (1)
* Blue (4) + Green (3)
(as per images below)

To have it move, the setup needs to be as follows  

* A1: Green (3)
* A2: Gray (2)
* B1: Blue + Purple (1) + (4)

## How it was plugged

![](/include/images/kretzaw145ba/20180811b/P_20180811_175204.jpg)

![](/include/images/kretzaw145ba/20180811b/P_20180811_175211.jpg)

![](/include/images/kretzaw145ba/20180811b/P_20180811_175217.jpg)

