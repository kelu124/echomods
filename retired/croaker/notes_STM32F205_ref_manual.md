# Notes on the STM32F205 Reference manual  [](@description Notes on the STM32F205 for quick ADCs)

* [Source PDF : reference Manual](/retired/croaker/datasheets/en.CD00225773_STM32F2x5_RefManual.pdf).
* [Other interesting : STM32TM’s ADC modes and their applications](/retired/croaker/datasheets/en.CD00258017.pdf)

* [Inspiration for the code](http://microcontroleurs.blogspot.fr/2015/07/realisation-dune-carte-dacquision-moins.html)

Discussions are taking place to use the max speed on the Feather WICED:

* [See on Adafruit GithubRepo](https://github.com/adafruit/Adafruit_WICED_Arduino/issues/58) 
* [on adafruit forums](https://forums.adafruit.com/viewtopic.php?f=57&p=527280)

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

## Calibration

Using the feather WICED to produce a waveform:

![](/silent/software/featherWICED/CalibrationDAC.png)




### Versions of code so far

* [INO for close to 2Msps, 2ADCs interleaved](/retired/croaker/feather_tests/2ADC2UDP.ino)

Compared to the waveform detailed above, gives the following acquisition:

![](/silent/software/featherWICED/CalibrationADC-2ADC2UDPpng.png)

### ADC common control register (ADC_CCR)

When the DMA mode is enabled (DMA bit set to 1 in the ADC_CR2 register), after each conversion of a regular channel, a DMA request is generated. This allows the transfer of the converted data from the ADC_DR register to the destination location selected by the software


* MULTI[4:0]: Multi ADC mode selection
* 10001 to 11001: Triple mode: ADC1, 2 and 3 working together
* 10111: interleaved mode only

### Comment on the code


#### Initialization of the ADC

```c
  // We configure the ADC1 and ADC2
  // Setting max sampling rate
  rcc_set_prescaler(RCC_PRESCALER_ADC, RCC_ADCPRE_PCLK_DIV_2);
  adc_set_sample_rate(ADC1, ADC_SMPR_1_5);
  adc_set_sample_rate(ADC2, ADC_SMPR_1_5);
  //  adc_set_sample_rate(ADC2, ADC_SMPR_3);

  //6=0110 for dual regular simultaneous mode
  // FOR STM32F1 -- DUALMOD[3:0]: Dual mode selection is on ADC control register 1 (ADC_CR1) - has to be changed
  // Bits 19:16 DUALMOD[3:0]: Dual mode selection
  // 7 is for interleaved mode.
  ADC1->regs->CR1 |= 7 << 16;

  //only one input in the sequence for both ADC: the channel 1

  adc_set_reg_seqlen(ADC1, 1);
  adc_set_reg_seqlen(ADC2, 1);
  adc_set_reg_seqlen(ADC3, 1);
  // Aiming at Interleaved mode on 1 channel in continuous conversion mode: triple ADC mode
  //channel 1 (PA1) on ADC1
  ADC1->regs->SQR1 |= 0;
  ADC1->regs->SQR2 = 0;
  ADC1->regs->SQR3 = 1; //00000.00000.00001
  //channel 1 (PA1) on ADC2
  ADC2->regs->SQR1 |= 0;
  ADC2->regs->SQR2 = 0; //00000.00000.00000
  ADC2->regs->SQR3 = 1; //00000.00000.00010
  //channel 1 (PA1) on ADC3
  ADC3->regs->SQR1 |= 0;
  ADC3->regs->SQR2 = 0; //00000.00000.00000
  ADC3->regs->SQR3 = 1; //00000.00000.00010
```


#### Acquisition

Acquisition takes place in a loop, where 2*BUFFERSIZE data is acquired. Values from ADC1 and ADC2 go into val1 and val2.

```c
    while (i < BUFFERSIZE) {
      // ADC : page 212 to 254 in the reference manual

      //start conversion
      ADC1->regs->CR2 |= ADC_CR2_SWSTART;
      ADC2->regs->CR2 |= ADC_CR2_SWSTART;

      // Wait the end of the conversion
      while (!(ADC1->regs->SR & ADC_SR_EOC)) ;
      while (!(ADC2->regs->SR & ADC_SR_EOC)) ;

      // Get the values converted from the two ADCs.
      // They are sharing the same channel, in interleaved mode
      val1[i] = (int16)(ADC1->regs->DR & ADC_DR_DATA);
      val2[i] = (int16)(ADC2->regs->DR & ADC_DR_DATA);
      i++;
   }
```

