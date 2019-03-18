# Implementing HV source. 

## Constraints

* Small footprint
* Settable
* Between 0 to 90V, ideally with another source for 0 to -90V (for bipolar pulses)

## Options

### MAX668

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

### MAX1856

Flyback Transformer Design for MAX1856 SLIC Power Supplies - Application Note - Maxim
* https://www.maximintegrated.com/en/app-notes/index.mvp/id/1166
* -80V and -24V lines

![](/matty/HV/MAX1856.png)

### HV9150 - 16-lead QFN

![](/matty/HV/HV9150.png)

* Ref design : https://www.arrow.com/en/reference-designs/hv9150db1-demo-board-for-the-hv9150-hysteretic-dcdc-controller/efe7863599ea9e7c9404df74b8a14bfb
* Ref design: 0 to 200V: http://ww1.microchip.com/downloads/en/DeviceDoc/20005689A.pdf 

## Chips for US 

[https://www.microchip.com/stellent/groups/analog_sg/documents/devicedoc/cn571283.pdf](/matty/HV/datasheets/cn571283.pdf)


