# How to build a ultrasound imaging dev-kit ?

## Genesis

In early 2014, I met with what would become the echOpen's cofounders. The objective then was to explore old technologies used in ultrasound, and see what one could do with those, in open-source.

Fast-forward summer 2015, got some funds and we settled in Hotel-Dieu. After the "difficult" first steps - none of us were electrical engineers! -, a community started aggregating. In November 2015, a technical meeting took decisions, from which I wanted to diverge, and started exploring an empty fork, based on the idea of using a beaglebone and a maximum of off-the-shelf SMD components to assemble something - a new project was born =)

## A first iteration

The overall design of a Beaglebone took place in Jan '16, especially keeping in mind the possibilities to use the two 200MHz PRUs. The board came in early March, and [first tests were interesting](https://github.com/kelu124/murgen-dev-kit/blob/master/hardware/Readme.md). Images went out cool, and got some first interesting images from a gelatin phantom on end of March:

![](https://raw.githubusercontent.com/kelu124/murgen-dev-kit/master/worklog/Images/Session_7/20160328-141152.data-DEC1-SC-4T.png)

The same summer, Zach worked on the murgen board, and managed to get some good images too!

![](https://raw.githubusercontent.com/ZTaylor39/murgen-dev-kit/zach/worklog/Zach/2016-07-06/tp2.png)

## Going into modules

After a second technical meeting in April, we thought it a good idea to split functions into separate modules. That gave birth to [these echomods](https://github.com/kelu124/echomods/), with a first series of modules based on Murgen. The designs were ready in beginning of May, and they were a great source of fun! Born of these two initial modules ( [pulser](/retired/tobo/) and [analog processing](/goblin/) boards), some siblings were born:
* using a [BeagleBone PRUDAQ board for a DAQ](/retired/toadkiller/), used in Sept '16
* a [ultrasound emulator](/silent/), to calibrate the rest of the signal when there are no transducers, born in Aug '16
* a [STM32 processing and wifi streaming module](/retired/croaker/) born in Sept '16

At the end, the modules also allowed to test some [ATL probes](/retroATL3/) (more details [here](/include/ATL.md)) found on ebay:

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/20160814/sonde3V_1-4.csv-SC.png)

## un0rick / matty

![](https://raw.githubusercontent.com/kelu124/un0rick/master/images/un0desc.png)

After a series of modules, I decided to go "pro" and to develop a more robust iteration, based on an ice40 FPGA, an open-source family of FPGAs.

Ultimately, this yielded a pulse-echo board ( [un0rick](http://un0rick.cc) ) that is capable of 500k points acquisitions, with the logic being fully customisable.

Some hacks also [enable it to acquire up to 128Msps](/include/experiments/auto/20180814a.md).

## Hackaday

Apart from GitHub where I wanted to store code, source and images, I also wanted to document the day to day work. Hackaday was a good option, and I put [Murgen on Hackaday.io](http://hackaday.com/2016/04/12/a-developers-kit-for-medical-ultrasound/). The funny thing is I didn't know I would get out of it, but it appeared the work won two 1000$-prizes. Later on, I've been putting the HSDK project on HAD as well as the [20Msps pHAT](https://hackaday.io/project/20455-20msps-adc-raspberrypi-hat) and the following of the [dev kit (the hardware-software dev kit)](https://hackaday.io/project/10899-a-hsdk-for-ultrasound-imaging).

[un0rick](https://hackaday.io/project/28375-un0rick-an-ice40-ultrasound-board) is also one of these project.

## Documenting

Documenting started on github obviously, I also started a [gitbook](https://kelu124.gitbooks.io/echomods/content/) later on - and as I' quite the lazy one, nothing of it is written by hand. Most of it is compiled through a python documentation assistant. 

On the scientific publication side, when reading around GOSH discussions in Sept '16, I learnt the Journal of Open Hardware would start something.. so an article started to make its way out. A first draft got out on ArXiv on Dec '16, and the [final version of the article got published](http://openhardware.metajnl.com/articles/10.5334/joh.2/) in March '17 - a year after the first tests of Murgen =)

[Read more on the process](/include/autodoc.md).

## Simplifying

That's the idea behind the [Raspberry-based Ultrasound SDK](https://hackaday.io/project/10899-a-debugger-for-ultrasound-imaging).




