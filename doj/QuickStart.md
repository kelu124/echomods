## Quickstart of the mother board

## BEWARE !!

As a piece of advice, __don't solder your modules directly on the motherboard__... unless you're sure that they are properly set up, that there's no short, ... and keep the design as modular as possible.

Instead, solder header, 19 slot long, for each side of the modules. These will be the host for the pins coming from the different modules.

Nothing can keep you from soldering round slot headers for ease of using wire jumpers.

Don't forget to put some capacitance on the dedicated slots on the motherboard to smooth the supply - and on Doj v2, to include the 3.3V jumper (above the 5V capa) so that the Pi can provide the necessary 3.3V to the board, and, if using a Pi, to solder the Pon <-> Pon3 and  Poff <-> Poff3 if you want to use a pulser at 3.3V from the Pi.

### Doj v1.2

The PCB can be ordered on [OSHPark](https://oshpark.com/shared_projects/bdv4Rw1z) - or ask me if I have one available (maybe check on [Tindie](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/))

#### How to solder the PCB ?

![](/doj/images/doj12.jpg)

#### Example of Doj v2 powered through Raspberry USB 	

![](/doj/images/20170406_214508.jpg)



### Doj v2

The PCB can be ordered on [OSHPark](https://oshpark.com/shared_projects/rAatPbRg) - or ask me if I have one available.

#### How to solder the PCB ?

![](/doj/images/doj20.jpg)

#### Example of Doj v2 powered through the [Feather](/goblin/) module

![](/doj/images/doj_v2_notes.jpg)




