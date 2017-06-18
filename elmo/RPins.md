# Summary of the pins

2x9 bits ADCs

http://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/06/Raspberry-Pi-GPIO-Layout-Model-B-Plus-rotated-2700x900.png

40 pins in total 
12 pins taken (GND, 3.3, 5V)
that leaves 28 pins remaining
-> 18 are used by the ADCs
-> 10 remaining
-> -2 (the I2C v2)
-> 8 left for the core functions


```
-> Core
#define clock	 4
#define RPIn	 5
#define PWM	 6
#define Puls_ON	 23
#define Puls_OFF 24
#define BIT_TRACKER 21
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

# ADC 

* +-750mV gives 2.4V //
* +-1V gives 3.3V //


