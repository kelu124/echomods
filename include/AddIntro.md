# A wireless, low-cost kit (v1.1)

## Introduction

The aim of this set of modules is to remove the "heavy-weight" beaglebone black and its DAQ ([toadkiller module](/toadkiller/)) and to replace it with a small arduino like, capable of acquiring 6Msps and stream it over wifi, while leveraging the arduino IDE.

Of course, due to its limitation, it cannot properly sample the raw signal coming back from the transducer, but with the help of the [analog processing module](/goblin/), the enveloppe of the signal, ie the bones of the ultrasound image, is ready to be acquired.

For the fun of it, I also put a small 128x60 monochrome screen, to see what the microcontroller is acquiring.

## Examples

### Plugin in the servo+transducer module ([Cletus](/cletus/))

Organizing the modules

![](/croaker/images/kit-overall.png)

#With the overview, and the transducer

![](/croaker/images/kit-overaview.png)


