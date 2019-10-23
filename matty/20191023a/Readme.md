# `20191023a`



## Tools used on the Raspberry 

* [Working binary](/matty/20191023a/tools/C2_w.bin)
* [Icoprog, updated to match lit3rick pins](/matty/20191023a/tools/icoprog)
* [Bash - Program the bin to the FPGA ram](/matty/20191023a/tools/progice40.sh)
* [Obtain the JSONs, RPi side](/matty/20191023a/tools/pyUn0.py)
* [Support to progice](/matty/20191023a/tools/reset.sh)

## Hardware mods

### Shorting C28 on the revision

![](/matty/20191023a/Short_C28.jpeg)

### Nicer clock

![](/matty/20191023a/DCLK_OK.jpeg)

## Script used

* [Script used to process the JSONs](/matty/20191023a/pyUn0.py)

# Results

## First images and tests with C2_w.bin

### HV at 500/1024, HILO high, gain at 600


![](/matty/20191023a/images/20191023a-8.jpg)

### HV at 100/1024, HILO high, gain at 600


![](/matty/20191023a/images/20191023a-9.jpg)

### HV at 900/1024, HILO high, gain at 600


![](/matty/20191023a/images/20191023a-10.jpg)

### HV at 500/1024, HILO low, gain at 100

![](/matty/20191023a/images/20191023a-11.jpg)

### HV at 100/1024, HILO low, gain at 100

![](/matty/20191023a/images/20191023a-12.jpg)
