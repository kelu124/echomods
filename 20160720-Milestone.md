% Summer Milestone, Playing with modules
% @kelu124
% July 27, 2016

## Objective

The objective of this project is to propose an open-source, low-cost dev-kit ultrasound imaging  to allow scientists, academics, hackers, makers or OSHW fans to hack their way to ultrasound imaging.

## What are modules?

The modules are breadboard compatible functionnal elements of any ultrasound imaging systems.

They have in common 19 interfaces available on a motherboard to easily access and understand the signal processing logic.


## What specs?

We aren't doing live imaging for doctors, rather.. building a cheap, open, system. Therefore, we could use the following:

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

## Modules so far

* _High priority:_
    * [tobo](https://github.com/kelu124/echomods/tree/master/tobo): the HV and pulser module
    * [cletus](https://github.com/kelu124/echomods/tree/master/cletus): interface the transducer and the servo, aka the physical parts, to the analog part of the modules chain.
    * [goblin](https://github.com/kelu124/echomods/tree/master/goblin): getting the signal coming back from a transducer, and to deliver the signal, analogically processed.
    * [mogaba](https://github.com/kelu124/echomods/tree/master/mogaba): getting 3.3V and 5V done.

* _Lower priority:_
    * [sleepy](https://github.com/kelu124/echomods/tree/master/sleepy): encasing the whole modules object in a neat case, making it transportable.
    * doj: the motherboard itself.

* _Retired modules:_
    * retroATL3: hacking a ATL3. Rotative probe with 3MHz element.
    * retro10PV: hacking a ATL10PV. Rotative probe with 5, 7.5 and 10MHz elements.

## Documentation

Documentation here is key. A website that builds itself based on proper, simple and un-redondant information is needed.

## Acquisition

Having played with acquisition, it appears that the BitScope is excellent for 5Msps acquisition - with Xms delays between transfers to PC. Need real time. Options are as follows:

* Beaglebone: either using [Murgen](#TODO) onboard ADC (10Msps), or the PRUDAQ Board.
* Beaglebone: bitbanging the Tobo ADC.
* EMW3165: getting the UDP streaming

## Display

Displays are key to see if each line behaves as it should - and of course for us to check if it works. The displays should be part of each module. Several possibilities

* Getting the image displayed on a TFT
* Maybe line by line on the 128x64 OLED screen (using the EMW3165 ?) [](#TODO)

## Planning

* Critical path 
    * Aug 5th: starting the work =)
    * Aug 15th: getting and debugging Tobo, the pulser
    * Aug 10th: high priority: getting a US pulser emulator [](#TODO)

* medium priority
    * Aug 20th: Getting the EMW3165 working [](#TODO)

* Low priority: 
     * Aug 15th: having played with PRUDAQ - maybe with Goblin and retroATL3

## Conclusion

Two outputs scheduled:

* A working dev-kit
* An efficient (err, lazy) way of documenting. Only one place to edit information, will be updated everywhere, even in this presentation!

## Pending Work

* Publishing automatically a presentation of the modules.. will need some inputs from the /include/ folder =)
* getting a US pulser emulator
* Graph the different modules - and see to what functional block each belongs
     * Within, create sets for graphing
* transcribing murgen, tobo and goblin to kicad
* Finding a good "Todo" list.

## Q&A

Ping me @kelu124 / kelu124@gmail.com !

## Names

* __XXXX__ for the Beaglebone with PRUDAQ (to test with retroATL3)
* Beaglebone with direct access to tobo (to test with retroATL3 - high prio) (cf Derek Molloy) -> Code to be put in Tobo
* __Doj__ for the motherboard
* __XXXX__ for the EMW3165 module

