# Running tests of the new modules `20180415r`

### Setup

#### Required modules 

* [doj](/doj/) as a motherboard
* [elmo](/elmo/) for acquisition
* [lite.tbo](/lite.tbo/) as the pulser
* [goblin](/goblin/) as the analog processing board
* [wirephantom](/wirephantom/) as a target
* A piezo, which an be replaced by a [probe](/include/probes/auto/retroATL3.md), folder for details here](/retroATL3/).

#### Is it compatible with the probe acquisition ?

__Yes!__ This setup can easily be used to replicate the probe image acquisition displayed in [20170715-ProbeTest.ipynb](/elmo/data/20170715-ProbeTest.ipynb) by plugging the probe BNC onto the tobo board.

Only code concerns the _Raspberry Pi drivers_ for acquisition (see below) as well as the post processing (see the previous link). One needs to shoot more lines to rebuild the image.


### Files

* [Jupyter notebook](/include/20180415r/20180415r-lit.tbo.ipynb)
* [Raspberry Pi drivers](/include/20180415r/driver.c)
* [Raw data](/include/20180415r/lit-tbo.DAT)
* [Processed data](/include/20180415r/lit-tbo.npz)

### Setup

![](/include/20180415r/20180415_121351.jpg)

### Acquisition

![](/include/20180415r/Raw_lit-tbo.npz.jpg)

![](/include/20180415r/enveloppe_signal_lit-tbo.npz.jpg)

### Details of the pulser pulse at 24V

Pon has to go high, Poff has to go low.

![](/include/20180415r/scope/RPi-Poff.png)

![](/include/20180415r/scope/RPi-Poff2.png)

