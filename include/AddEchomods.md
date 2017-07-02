## What are the arduino-like ultrasound module ?

__Creating modules to facilitate ultrasound hacking__ : the principles of the echOmods is to enable a full chain of ultrasound image processing and hardware control.

We have chosen to use a module approach to make sure that each key component inside ultrasound image processing can easily be replaced and compared with another module, while providing logical _logic blocks_ and corresponding interfaces for these modules to communicate. There's a module for [high-voltage pulsing](/tobo/), one for the [transducer](/retroATL3/), one for the [analog processing](/goblin/), one for [data acquisiton](/toadkiller/), ... and many more!

## What images does it give ?

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg)

## What does it look like?

The modules sit on a breadboard, and communicate through the tracks laying below. The configuration represented below show the Basic dev kit.

![](/doj/images/doj_v2_notes.jpg)

and used in a wider context:

![](/elmo/data/arduino/setup.png)
