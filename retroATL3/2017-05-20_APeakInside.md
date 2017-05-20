# 2017-05-20

## Content

Counter going in:

* 1st board: counter: 6 wires going out of counter, 6 feeding in [LM339](/retroATL3/pdf/lm2901v.pdf), 6 wires going out. LM339 is Quad Differential Comparators

* 2nd board: 
    * [DM74S287AN](/retroATL3/pdf/DM54S287AJ_to_DM74S287V.pdf): 1 green wire coming from ultrasound machine, 1 connected to LM339, 3 others from machine. Seems a schottky memory 256x4 1024-bit TTL PROM. The 4 pins on this side seem to go to Q0 to D3. Only Q3 is connected to green wire.
    * [HEF4040BT](/retroATL3/pdf/HEF4040B-840917.pdf): a 12-stage binary ripple counter. VDD from 3V to 5V. VDD is fed through the "salmon" wire. CP (Clock) is Wire4 (blue) 

## Guesses

* DM74S287AN stores the probe number / serial / ...
* The LM339 plays with the sensor.

## Images

![](/retroATL3/images/ICsInHead/20170520_132617.jpg)

![](/retroATL3/images/ICsInHead/20170520_132702.jpg)

![](/retroATL3/images/ICsInHead/20170520_132727.jpg)

![](/retroATL3/images/ICsInHead/20170520_132651.jpg)


## From the last image, data from the wires from the sensors

* Blue -> 5V
* White -> 2.2V
* Yellow -> 3.6V

### Orange

20ms of period, that's 50Hz, that could be 50 imgs per sec, or since the periods seem divided in three, maybe that's a full turn of the head, so 3 images. 

![](/retroATL3/images/ICsInHead/orange.JPG)

### Green

The others are 28 to 30kHz, 30us/period. That's a period 1/600 of the period above. That can therefore be 600 lines / image, or rather 

![](/retroATL3/images/ICsInHead/vert.JPG)

### Violet

![](/retroATL3/images/ICsInHead/violet.JPG)

### Sensors

![](/retroATL3/images/ICsInHead/20170520_134634.jpg)

## Pins

* 9 et 10: motor (_which one is the GND?_)

* 16 and 2: what are those?
* 18 + 18
* 17 GND

## Next steps

1. Power the motor
2. Connect intelligence on 16 and 18
3. Try powers around 17 and around


## Possible encoders

![](/retroATL3/images/encoder.png)

## PINS

![](/retroATL3/images/other_pins.jpg)


![](/retroATL3/images/motor_pins.jpg)


