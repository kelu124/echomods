# Teardown of a S3 ultrasound probe

## First look

ICs:

* __ADC12020__: TI - 12-Bit, 20-MSPS Analog-to-Digital Converter ( [datasheet](/include/s3/datasheets/adc12020.pdf) )
* __333L AU1Q__: could be a LMH6551Q Differential, High Speed Op Amp
* __AD9740__: 10-Bit, 210 MSPS TxDAC
* __DRV8834__ : Dual-Bridge Stepper or DC Motor Driver

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
