# Teardown of a S3 ultrasound probe

## First look

Let's have a look on the different ICs

### On top board

* __ADC12020__: TI - 12-Bit, 20-MSPS Analog-to-Digital Converter ( [datasheet](/include/s3/datasheets/adc12020.pdf) )
* __333L AU1Q__: could be a LMH6551Q Differential, High Speed Op Amp
* __AD9740__: 10-Bit, 210 MSPS TxDAC
* __DRV8834__ : Dual-Bridge Stepper or DC Motor Driver

### Below

Close to probe

* __AD8331__ matches the one I have for Goblin
* __CT 62Z__ ??
* __7288 EB Delta W45L__ seems to be __Si7288DP__ -- Dual N-Channel 40-V (D-S) MOSFET
* __M10602__ ??
* __PS 63020__ (x2): High Efficiency Single Inductor Buck-Boost Converter With 4-A Switches

Close to power

* __L111B__ LM3658 is power charger management

### Connectors

* JST 1.25mm - 4 pins for motor control
* JST 1.25mm - 2 pins for transducer

## Parts

### Pulser

The period of excitation is 300ns, corresponding to the 3MHz of the piezo. The pulse is 2 periods wide. The signal was captured with a 10x probe, so the Vpp is 96V.

![](/include/s3/pulser/IMAG001.png)

### Motor control

#### Pins

* Pin 1 (left): 5V
* Pin 2 : Yellow below
* Pin 4 : Blue below

![](/include/s3/counter/IMAG008.png)

* Pin 3 : Regular signal below

![](/include/s3/counter/IMAG009.png)

#### First outputs

* Motor seems controled by a 5V power supply, 3 signals output. 1 regular, 2 others a bit strange =)	

![](/include/s3/counter/IMAG007.png)
