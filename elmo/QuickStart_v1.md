## Quickstart of the ADC module

[](@description Quickstart of the legacy ADC pHAT)

### Hardware steps

#### For a PCB based solution...

Just plug it into the board!

#### For a standalone version


![](/elmo/images/qs_v1/20171009_170219.jpg)

![](/elmo/images/qs_v1/20171009_170604.jpg)

![](/elmo/images/qs_v1/20171009_171305.jpg)

But it also could work with a ribbon !


__Capture is with the blue cable as GND, and green as the signal.__

### The [ADC](/elmo/) module

The module code is [here](/elmo/data/scope.c) and can be compiled using [these steps](/elmo/data/PrepKernel.sh).

The full procedures are described at on the [raspberry doc page](/tomtom/)


Log now on this raspberry, and run the _run.sh_ command to load the driver of the ADC. You'll see that the module appears as a  __/dev/chardev__ device.

Capture occurs with a 

    cat /dev/chardev > myfilename.dat

Then copy the newly created file on your PC or where you need it. It dumps the raw GPIOs signals as [described here](/elmo/data/20170613-TestWithRawSignal.ipynb). Then a bit of python magic is used to reorder the bits in a way to reconstruct the signal from the two ADCs. __You can see an example of acquisition here on this [jupyter notebook](/elmo/data/20170714-TwoADCs-Probe.ipynb).__

Beware! If you want to get a signal between [-1.5V and 1.5V], consider using a in series with input to remove all DC bias, and make sure the jumper are set as in the images above.

 
