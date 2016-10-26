= Notes on the STM32F205 Reference manual =

[Source PDF](/croaker/datasheets/en.CD00225773_STM32F2x5_RefManual.pdf).

== ADC ==

=== ADC common control register (ADC_CCR) ===

* MULTI[4:0]: Multi ADC mode selection
* 10001 to 11001: Triple mode: ADC1, 2 and 3 working together
* 10111: interleaved mode only
