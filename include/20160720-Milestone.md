% Summer Milestone, playing with modules
% @kelu124
% July 20, 2016

## Objective

The objective of this project is to propose an open-source, low-cost dev-kit ultrasound imaging  to allow scientists, academics, hackers, makers or OSHW fans to hack their way to ultrasound imaging.

## What are modules?

The modules are breadboard compatible functionnal elements of any ultrasound imaging systems. They have in common 19 'public' interfaces available on a motherboard to easily access and understand the signal processing logic.

They are listed on the [echomod repo](https://github.com/kelu124/echomods/)

## What specs?

We aren't doing live imaging for doctors, rather.. building a cheap, open, system. Therefore, we could use the following (more details in the specs detailed in the [Worklog](https://github.com/kelu124/echomods/blob/master/Worklog.md):

* 3MHz ultrasound: travels fasts, has a low enough frequency to avoid using too quick elements (ADC, processing, ...)
     * This gives a depth from 2cm to 15cm.
     * 15 cm back and forth at 1500m/s is 200us.
* Using a single element imposes motors. Our target framerate is 1 image / s
* We're sweeping. We will target an easy 64 lines / image

## More details on specs

* 1 image per second at 64 lines per image gives 15.6ms between lines. That requires a simple servo.
* For a slow ADC (12bit, 2Msps) - 200us is 400 points is 5600 bits is 700 bytes.
* Roughly -- 5600 bits per 10ms is 560,000 bits/s is 70kbytes/s .. which is clearly fine with WiFi UDP (or TCP ?) streaming.
* We'll try to use only 3.3V and 5V - standard voltages.

## High priority modules

* [tobo](https://github.com/kelu124/echomods/tree/master/tobo): the HV and pulser module. PCB made.
* [cletus](https://github.com/kelu124/echomods/tree/master/cletus): interface the transducer and the servo, aka the physical parts, to the analog part of the modules chain.
* [goblin](https://github.com/kelu124/echomods/tree/master/goblin): getting the signal coming back from a transducer, and to deliver the signal, analogically processed. PCB made.
* [silent](https://github.com/kelu124/echomods/tree/master/silent): emulating an enveloppe signal. Dev toolbox.
* [mogaba](https://github.com/kelu124/echomods/tree/master/mogaba): getting 3.3V and 5V done.

## Lower priority modules

* [sleepy](https://github.com/kelu124/echomods/tree/master/sleepy): encasing the whole modules object in a neat case, making it transportable.
* [doj](https://github.com/kelu124/echomods/tree/master/doj): the motherboard itself.
* [Toadkiller](https://github.com/kelu124/echomods/tree/master/toadkiller): PRUDAQ BBB Board : that's a 2x10Msps (or up to 40Msps) board for the BBB. Could be u	seful for the [retroATL3](https://github.com/kelu124/echomods/tree/master/retroATL3).
* [Kina](https://github.com/kelu124/echomods/tree/master/kina): a Wifi module, based on the EMW3165 - a rough UDP-streaming ADC. For slow acquisition.

## Retired modules

Those are retired modules. However, they contain useful info.

* [retroATL3](https://github.com/kelu124/echomods/tree/master/retroATL3): hacking a ATL3. Rotative probe with 3MHz element.
* [retro10PV](https://github.com/kelu124/echomods/tree/master/retro10PV): hacking a ATL10PV. Rotative probe with 5, 7.5 and 10MHz elements.

Along with a real time, high speed DAC (BBB-PRUDAQ ?), retroATL3 could be up and running again.

## Proposed Set 1a: slow speed

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/sets/basic.png)

## Proposed Set 1b: slow speed, wireless

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/sets/wifi-dev-kit.png)

## Proposed Set 2: Emulated signal

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/sets/emulated.png)

## Proposed Set 3: High Speed acquisition 

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/sets/highspeed.png)

## Documentation

Documentation here is key. A website that builds itself based on proper, simple and un-redondant information is needed... and this repo / presentation is a proof it's on the way ;)

## Acquisition

Having played with acquisition, it appears that the BitScope is excellent for 5Msps acquisition - with Xms delays between transfers to PC. Need real time. Options are as follows:

* Beaglebone: either using [Murgen](https://github.com/kelu124/murgen-dev-kit/) (@TODO) onboard ADC (10Msps), or the [PRUDAQ BBB Board](https://github.com/kelu124/echomods/tree/master/toadkiller).
* Beaglebone: bitbanging the [tobo's 3Msps ADC](https://github.com/kelu124/echomods/tree/master/tobo).
* [EMW3165 - Kina ](https://github.com/kelu124/echomods/tree/master/kina): getting the UDP streaming. Would work only with the [servo-powered piezo](https://github.com/kelu124/echomods/tree/master/cletus) along with [goblin](https://github.com/kelu124/echomods/tree/master/goblin).

## Display

Displays are key to see if each line behaves as it should - and of course for us to check if it works. The displays should be part of each module. Several possibilities

* Getting the image displayed on a TFT
* Maybe line by line on the 128x64 OLED screen (using the [EMW3165](https://github.com/kelu124/echomods/tree/master/kina) ?) (@TODO)

## Planning

* Critical path: pulser
    * Aug 10th: starting the work =)
    * Aug 10th: high priority: getting a US pulser emulator (@TODO)
    * Aug 15th: getting and debugging Tobo, the pulser
    * End of August: tested [PRUDAQ BBB Board](https://github.com/kelu124/echomods/tree/master/toadkiller)
* medium priority: small DAC
    * Aug 20th: Getting the [EMW3165 - Kina ](https://github.com/kelu124/echomods/tree/master/kina) working (@TODO)
* Low priority: 
     * Aug 15th: having played with [PRUDAQ BBB Board](https://github.com/kelu124/echomods/tree/master/toadkiller) - maybe with Goblin and retroATL3

## Community

Two main steps:

* Interfacing with echopen -> how to push the modules ?
* Pursuing the documentation effort and community visibility with hackaday.

## Conclusion

Two outputs scheduled:

* A working dev-kit
* An efficient (err, lazy) way of documenting. Only one place to edit information, will be updated everywhere, even in this presentation!

## Pending Work

* Publishing automatically a presentation/ppt of the modules.. will need some inputs from the /include/ folder =)
* Getting a US pulser emulator ([silent](https://github.com/kelu124/echomods/tree/master/silent)) : Teensy, Feather Wiced?
* Graph the different modules - and see to what functional block each belongs
     * Within, create sets for graphing
* Transcribing murgen, tobo and goblin to kicad
* Finding a good "Todo" list.

## Q&A

Ping me @kelu124 / kelu124@gmail.com !

## Names

* __ToadKiller__ for the Beaglebone with [PRUDAQ BBB Board](https://github.com/kelu124/echomods/tree/master/toadkiller) (to test with [retroATL3](https://github.com/kelu124/echomods/tree/master/retroATL3))
* Beaglebone with direct access to tobo (to test with retroATL3 - high prio) (cf Derek Molloy) -> Code to be put in [tobo](https://github.com/kelu124/echomods/tree/master/tobo)
* __Doj__ for the motherboard
* __Kina__ for the [EMW3165](https://github.com/kelu124/echomods/tree/master/kina) module

