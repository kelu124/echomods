# Implementing HV source. 

## Constraints

* Small footprint
* Settable
* Between 0 to 90V, ideally with another source for 0 to -90V (for bipolar pulses)

## Options

### MAX 668

Maxim has this 150V reference design based on MAX668 that can be controlled via DAC:


![](/matty/HV/MAX668.png)

### MIC3172

Also, Microchip has this other reference design based on MIC3172 that also can be easily modified to add a DAC into FB path.


![](/matty/HV/MIC3172.jpg)
 
 
### LT3494 - used in the pHAT

* +DAC for setup. Up to 39V.

![](/matty/HV/LT3494.png)

### NMT0572SC - used in the un0rick board

* 24, 48, 72V lines

![](/matty/HV/NMT0572SC.png)
