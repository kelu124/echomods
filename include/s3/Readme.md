# Teardown of a S3 ultrasound probe

## First look

ICs:

* __ADC12020__: TI - 12-Bit, 20-MSPS Analog-to-Digital Converter
* __333L AU1Q__: could be a LMH6551Q Differential, High Speed Op Amp
* __AD9740__: 10-Bit, 210 MSPS TxDAC
* __DRV8834__ : Dual-Bridge Stepper or DC Motor Driver

### Pulser

The period of excitation is 300ns, corresponding to the 3MHz of the piezo. The pulse is 2 periods wide. The signal was captured with a 10x probe, so the Vpp is 96V.

![](/include/s3/pulser/IMAG001.png)
