# echomods

Creating modules out of the murgen board

## What is it?

The principles of the echOmods is to enable a full chain of ultrasound image processing and hardware control. Four basic modules are considered. Each of this module will be landing on a motherboard, more or less a stripboard.

Key interfaces, signals and alims will be available on each of the 19 tracks on the motherboard, and will enable communication between modules. However, some tracks can be unused by the modules. These modules can have a form factor close to the arduino trinket pro, with a row of 19 pins on the side.

## Modules

* [Goblin](/goblin/Readme.md): the __analog processing module__, was drafted as well during Murgen. 
* [Tobo](/tobo/Readme.md): the __HV and pulser module__, based on a drafted close to Murgen. 
* [Cletus](/cletus/Readme.md): the __piezo and servo module__. Did not change. 
* [One-Eye](/oneeye/Readme.md) is the __MicroControler module__, to be working with Arduinos at first, such as the Trinket Pro.
* [Mogaba](/mogaba/Readme.md) is the __Alimentation Module__.
* and ... the __motherboard__.

Other modules, such as Silent (_analog processing testing module_) and Croaker (_advanced microcontroler module_), are in the teaser stage... More to come later on =)

## Illustration

![Modules organisation](/include/images/modules.png)








# The modules organization 

![Graph](/include/ModulesGraph.png) 

# A recap of our modules 


| ThumbnailImage | Name | In | Out |
|------|-------|----|------|
|<img src='https://github.com/kelu124/echomods/blob/master/tobo/viewme.png' align='center' width='150'>|**[tobo](/tobo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|ITF-A_gnd, ITF-B_5v, ITF-I_pulse_on, ITF-J_pulse_off, ITF-S_3_3v|ITF-R_reserved, ITF-mET_SMA, ITF-mET_Transducer|
|<img src='https://github.com/kelu124/echomods/blob/master/cletus/viewme.png' align='center' width='150'>|**[cletus](/cletus/Readme.md)**: The aim of this module is to interface the transducer and the servo, aka the physical parts, to the analog part of the modules chain.|ITF-A_gnd, ITF-B_5v, ITF-N_cc_motor_pwm, ITF-S_3_3v, ITF-mET_Transducer, ITF-mET_Piezo|ITF-mET_Piezo, ITF-mET_Transducer|
|<img src='https://github.com/kelu124/echomods/blob/master/oneeye/viewme.png' align='center' width='150'>|**[oneeye](/oneeye/Readme.md)**: The module aims at making a microcontroler, for the moment the <code>ArduinoTrinketPro</code>, usable with the motherboard and the set of modules.|ITF-A_gnd, ITF-B_5v, ITF-S_3_3v|ITF-G_gain_control, ITF-I_pulse_on, ITF-J_pulse_off, ITF-N_cc_motor_pwm|
|<img src='https://github.com/kelu124/echomods/blob/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed.|ITF-A_gnd, ITF-B_5v, ITF-S_3_3v, ITF-G_gain_control, ITF-C_amplified_raw_signal, ITF-E_signal_envelope, ITF-R_reserved, ITF-mET_SMA|ITF-C_amplified_raw_signal, ADL5511, ITF-E_signal_envelope, ITF-mEG_SPI|
|<img src='https://github.com/kelu124/echomods/blob/master/mogaba/viewme.png' align='center' width='150'>|**[mogaba](/mogaba/Readme.md)**: The aim of this echOmod is to get 3.3V and 5V done.|ITF-mEM_Alimentation|ITF-A_gnd, ITF-B_5v, ITF-S_3_3v|

# License

## echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

## Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018


