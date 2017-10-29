## Testing the bipulser capability

* See [Jupyter notebook](/alt.tbo/20171028a/20171028-pulses.ipynb)
* Kernel module [is here](/alt.tbo/20171028a/bilevel.c)

## Schematics

![](/alt.tbo/20171028a/images/pulser_alt.png)

![](/alt.tbo/20171028a/images/pulser_diods.png)

## Pulser at two levels

Seems that one of the pulses does not go off. However, both triggers seems to work.

Checked: the pulses reach R3 and R4 aka the logic on the pulsers.

![](/alt.tbo/20171028a/images/Pulses.png)

and with the damper signal

![](/alt.tbo/20171028a/images/DampPulse.png)


## Screenshot

From the pulses, it seems only one HV pulses.

### 50V pulse

![](/alt.tbo/20171028a/images/Pulse50V-10xProbe.png)

### 75V pulse

![](/alt.tbo/20171028a/images/Pulse75V-10xProbe.png)

## Todo ?

1. check the voltages and polarity on R1, R2. It should be both measured with respect to GND.
2. After that disable the damper circuit. Best way will be to remove D3 diode. In this case one should have pulses with both positive and negative polarity. If not, one has to check D2 and U3 parts
