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

### max15031

The MAX15031 consists of a constant-frequency pulse-width modulating (PWM) step-up DC-DC converter with an internal switch and a high-side current monitor with high-speed adjustable current limiting. This device can generate output voltages up to 76V and provides current monitoring up to 4mA (up to 300mW). 

 Internal soft-start circuitry limits the input current when the boost converter starts. The MAX15031 features a shutdown mode to save power.

The MAX15031 includes a current monitor with more than three decades of dynamic range and monitors current ranging from 500nA to 4mA with high accuracy. Resistor-adjustable current limiting protects the APD from optical power transients. A clamp diode protects the monitor's output from overvoltage conditions. Other protection features include cycle-by-cycle current limiting of the boost converter switch, undervoltage lockout, and thermal shutdown if the die temperature reaches +160°C.

https://www.digikey.com/catalog/en/partgroup/max15031-evaluation-kit/50986

![](/matty/HV/MAX15031.gif)

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


