# Notes on the STM32F205 Reference manual 

* [Source PDF : reference Manual](/croaker/datasheets/en.CD00225773_STM32F2x5_RefManual.pdf).
* [Other interesting : STM32TM’s ADC modes and their applications](/croaker/datasheets/en.CD00258017.pdf)

## Calibration

Using the feather WICED to produce a waveform:

![](/silent/software/featherWICED/CalibrationDAC.png)

## ADC 

* Configurable DMA data storage in Dual/Triple ADC mode
* Configurable delay between conversions in Dual/Triple interleaved mode
* ADC conversion time: 0.5 μs with APB2 at 60 MHz
* ADC supply requirements: 2.4 V to 3.6 V at full speed and down to 1.8 V at slower speed
* ADC input range: V REF– ≤ V IN ≤ V REF+
* DMA request generation during regular channel conversion


### Fast conversion mode

It is possible to perform faster conversion by reducing the ADC resolution. The RES bits are used to select the number of bits available in the data register. The minimum conversion time for each resolution is then as follows: 

* 12 bits: 3 + 12 = 15 ADCCLK cycles
* 10 bits: 3 + 10 = 13 ADCCLK cycles
* 8 bits: 3 + 8 = 11 ADCCLK cycles
* 6 bits: 3 + 6 = 9 ADCCLK cycles


### Versions of code so far

* [INO for close to 2Msps, 2ADCs interleaved](/croaker/feather_tests/2ADC2UDP.ino)

Compared to the waveform detailed above, gives the following acquisition:

![](/silent/software/featherWICED/CalibrationADC-2ADC2UDPpng.png)

### ADC common control register (ADC_CCR)

When the DMA mode is enabled (DMA bit set to 1 in the ADC_CR2 register), after each conversion of a regular channel, a DMA request is generated. This allows the transfer of the converted data from the ADC_DR register to the destination location selected by the software


* MULTI[4:0]: Multi ADC mode selection
* 10001 to 11001: Triple mode: ADC1, 2 and 3 working together
* 10111: interleaved mode only
