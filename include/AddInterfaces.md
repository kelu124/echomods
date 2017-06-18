# Interfaces table for the motherboard

| Name | Title | Amplitude | Raspberry GPIO | 
|------|-------|-----------|-----------|
|`ITF-1_GND`|_Ground_|[0V]||
|`ITF-2_VDD_5V`|_5V alimentation_|[5V, 5V]||
|`ITF-3_ENV`|_Enveloppe of the signal_|[0V, 2.5V]||
|`ITF-4_RawSig`|_Amplified filtered signal_|[0V, 2.5V]||
|`ITF-5_RENV`|_Raw signal envelope_|[VREF, 2.5V]||
|`ITF-6_P6`|_ OLED SDA_|[0V, 3V]|  GPIO 02 |
|`ITF-7_GAIN`|_Amplifier gain control_|[0V, 1V]||
|`ITF-8_P8`|_-Pi OLED SCL_|[0V, 3V]| GPIO03|
|`ITF-9_Pon`|_Pulse on_|[0V, 5V]| Jumper to connect to GPIO 23 |
|`ITF-10_Poff`|_Pulse off_|[0V, 5V]| Jumper to connect to GPIO 24 |
|`ITF-11_OffSig`|_Signal offset by Vref/2_|[0V, 3.3V]||
|`ITF-12_RPIn`|_Pi ADC DAQ_|[0V, 3.3V]|GPIO 05|
|`ITF-13_P13`|_Unused_|||
|`ITF-14_PWM`|_Servo PWM_|[0V, 3.3V]|GPIO 06|
|`ITF-15_GPIO21`|_GPIO21 connection_|| GPIO 21|
|`ITF-16_POn3`|_Pulse On 3V_|[0V, 3.3V]| GPIO 23|
|`ITF-17_POff3`|_Pulse Off 3V_|[0V, 3.3V]| GPIO 24|
|`ITF-18_Raw`|_Raw signal fro transducer_|[-5V, 5V]||
|`ITF-19_3.3V`|_3.3V alimentation_|[3.3V, 3.3V]||

# Interfaces for Raspberry Pi

```
-> Core
#define ADC_CLK	 4
#define RPIn	 5
#define PWM	 6
#define Puls_ON	 23
#define Puls_OFF 24
#define TRACKER	 21
-> Optional
#define oled_sda 2
#define oled_sdc 3

//ADC 1
#define BIT0_PIN 16
#define BIT1_PIN 17
#define BIT2_PIN 18
#define BIT3_PIN 19
#define BIT4_PIN 20
#define BIT5_PIN 22
#define BIT6_PIN 25
#define BIT7_PIN 26
#define BIT8_PIN 27

//ADC 2 (leaves SPI0 free)
#define BIT0_PIN 7
#define BIT1_PIN 8
#define BIT2_PIN 9
#define BIT3_PIN 10
#define BIT4_PIN 11
#define BIT5_PIN 12
#define BIT6_PIN 13
#define BIT7_PIN 14
#define BIT8_PIN 15
```
