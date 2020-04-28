# Understanding the piezos impedance matching


## Measurements

|          | Freq | Re(Water) | Im(Water) | Return loss | Target |  C//  |   L=   | L//    | C=  |
|----------|:----:|:---------:|:---------:|-------------|:------:|:-----:|:------:|--------|-----|
|     BiVi |      |           |           |             |        |       |        |        |     |
| Salvaged |  6.7 |     24    |    -21    | -7.3dB      |   50   | 494pF | 1.02µH | 1.14µH | 6nF |
|          |      |           |           |             |        |       |        |        |     |

( generated with [that](https://www.tablesgenerator.com/markdown_tables). )

See [there](/include/impedance/1-s2.0-S1875389210001331-main.pdf)


https://www.analog.com/en/design-center/interactive-design-tools/rf-impedance-matching-calculator.html


### my_adrus

![](/matty/20200416a/piezo/my_adrus_outside.png)
![](/matty/20200416a/piezo/my_adrus_water.png)


### Bard `20200808r` into details

![](/include/bard/images/pins.jpg)

* Pins 4 and 5: piezo.
* 3: gnd
* 1: bobin upper, thin
* 2: bobin lower
* 8: thin (paired to 1? )
* 7 : thick, bobin
* 6: bobin, low, thick

-> Spectrum interesting, resonance below 50kHz between 1/8 pair

Interestingly, the schematics is described in [this patent, US4399703A, by Dymax](https://patents.google.com/patent/US4399703A/en).

#### Bard details


![](/include/20200809r/images/bard/P_20200509_182351.jpg)

![](/include/20200809r/images/bard/P_20200509_182357.jpg)

![](/include/20200809r/images/bard/P_20200509_182411.jpg)

![](/include/20200809r/images/bard/P_20200509_182429.jpg)

![](/include/20200809r/images/bard/P_20200509_182446.jpg)

![](/include/20200809r/images/bard/P_20200509_182456.jpg)

![](/include/20200809r/images/bard/P_20200509_182512.jpg)

