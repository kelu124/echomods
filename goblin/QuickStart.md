## Quickstart of the APM module


### The [Analog Processing Board](/goblin/) module

The assembly is detailed below:

![](/goblin/images/QS_goblin.jpg)

Specific points:
* A couple of headers to solder.
* Don't bother soldering SPI (the white header) if you don't plan on using it
* Setup the small jumper (in blue) to get signal from the "Raw Track". Other position is to get signal from SMA. Beware, there's no signal clipping there on this board.
* Setup the small jumper (in red) to get constant gain for TGC from the pot circle in dark red. The other position can be used if you plan on using the "GAIN" track (between 0 to 1V) to control the gain.

Read more on [the dedicated page](/goblin/).

## Testing and calibrating Tobo

__You need to power Tobo with a 3.3V source on track 19, and 5V on track 2__.

Apply a small voltage on Raw Track with jumpers rightly positioned (A). You should get a amplified signal on track RawSig (B), the offset  enveloppe on REnv track (C), and envelopped of the signal on 

BEWARE! Only apply small voltages to input (less than 1 Vpp ideally, here calibration was done with 60mVpp signals) 

![](/goblin/images/slide_principle.png)

## If not using a motherboard, connections are detailed below:

![](/goblin/images/rawtracks.png)
