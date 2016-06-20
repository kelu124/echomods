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
|<img src='https://github.com/kelu124/echomods/blob/master/oneeye/viewme.png' align='center' width='150'>|**[oneeye](/oneeye/Readme.md)**: The module aims at making a microcontroler, for the moment the <code>ArduinoTrinketPro</code>, usable with the motherboard and the set of modules.|ITF-A_gnd, ITF-B_5v, ITF-S_3_3v|ITF-G_gain_control, ITF-I_pulse_on, ITF-J_pulse_off, ITF-N_cc_motor_pwm|
|<img src='https://github.com/kelu124/echomods/blob/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed.|ITF-A_gnd, ITF-B_5v, ITF-S_3_3v, ITF-G_gain_control, ITF-C_amplified_raw_signal, ITF-E_signal_envelope, ITF-R_reserved, ITF-mET_SMA|ITF-C_amplified_raw_signal, ADL5511, ITF-E_signal_envelope, ITF-mEG_SPI|
|<img src='https://github.com/kelu124/echomods/blob/master/retro10PV/viewme.png' align='center' width='150'>|**[retro10PV](/retro10PV/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former <a href="http://echopen.org/index.php/ATL_Access_10PV">ATL10PV</a>.|ITF-A_gnd, ITF-F_12V, ITF-N_cc_motor_pwm, ITF-mET_Transducer, Motor, Tri-Piezo Head|Motor, ITF-mET_Transducer, Tri-Piezo Head|
|<img src='https://github.com/kelu124/echomods/blob/master/mogaba/viewme.png' align='center' width='150'>|**[mogaba](/mogaba/Readme.md)**: The aim of this echOmod is to get 3.3V and 5V done.|ITF-mEM_Alimentation|ITF-A_gnd, ITF-B_5v, ITF-S_3_3v|


# Progress on building the modules 


| Name of module | ToDo | Done | Contrib | Progress |
|------|-------|----|------|------|
|tobo|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-I_pulse_on</code>, <code>ITF-J_pulse_off</code>, <code>ITF-S_3_3v</code>, <code>ITF-R_reserved</code> : for the signal coming from the transducer, <code>ITF-mET_SMA</code> : for the signal coming out to the signal processing (if through SMA), <code>ITF-mET_Transducer</code> : for the signal coming out of the pulser (if through SMA), <code>HV7360</code>, <code>R05-100B</code>, <code>ITF-I_pulse_on</code>-&gt;<code>HV7360</code>, <code>ITF-J_pulse_off</code>-&gt;<code>HV7360</code>, <code>ITF-B_5v</code>-&gt;<code>R05-100B</code>-&gt;<code>HV7360</code>-&gt;<code>ITF-mET_Transducer</code>, <code>ITF-mET_Transducer</code>-&gt;<code>ITF-mET_SMA</code>, <code>ITF-mET_Transducer</code>-&gt;<code>ITF-R_reserved</code>, Only needs 5V and 3.3V, Energy use : TODO, ADC V_REF is flexible: using PulseOn and PulseOff, Can use the potentiometer to control the tension, Modularity through jumpers and SMA, Takes a lot of space because of the modularity. SMA, jumpers and pots could be removed., Little flexibility from the use of ICs., Send microcircuits to Edgeflex, Receive the module, Test it with different transducers, Publish the sources in KiCAD|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-I_pulse_on</code>, <code>ITF-J_pulse_off</code>, <code>ITF-S_3_3v</code>, <code>ITF-R_reserved</code> : for the signal coming from the transducer, <code>ITF-mET_SMA</code> : for the signal coming out to the signal processing (if through SMA), <code>ITF-mET_Transducer</code> : for the signal coming out of the pulser (if through SMA), <code>HV7360</code>, <code>R05-100B</code>, <code>ITF-I_pulse_on</code>-&gt;<code>HV7360</code>, <code>ITF-J_pulse_off</code>-&gt;<code>HV7360</code>, <code>ITF-B_5v</code>-&gt;<code>R05-100B</code>-&gt;<code>HV7360</code>-&gt;<code>ITF-mET_Transducer</code>, <code>ITF-mET_Transducer</code>-&gt;<code>ITF-mET_SMA</code>, <code>ITF-mET_Transducer</code>-&gt;<code>ITF-R_reserved</code>, Only needs 5V and 3.3V, Energy use : TODO, ADC V_REF is flexible: using PulseOn and PulseOff, Can use the potentiometer to control the tension, Modularity through jumpers and SMA, Takes a lot of space because of the modularity. SMA, jumpers and pots could be removed., Little flexibility from the use of ICs., Send microcircuits to Edgeflex, Receive the module, Test it with different transducers, Publish the sources in KiCAD, Specs to write, Agreeing on the strips , Defining the ICs to use, Getting schematics|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-I_pulse_on</code>, <code>ITF-J_pulse_off</code>, <code>ITF-S_3_3v</code>, <code>ITF-R_reserved</code> : for the signal coming from the transducer, <code>ITF-mET_SMA</code> : for the signal coming out to the signal processing (if through SMA), <code>ITF-mET_Transducer</code> : for the signal coming out of the pulser (if through SMA), <code>HV7360</code>, <code>R05-100B</code>, <code>ITF-I_pulse_on</code>-&gt;<code>HV7360</code>, <code>ITF-J_pulse_off</code>-&gt;<code>HV7360</code>, <code>ITF-B_5v</code>-&gt;<code>R05-100B</code>-&gt;<code>HV7360</code>-&gt;<code>ITF-mET_Transducer</code>, <code>ITF-mET_Transducer</code>-&gt;<code>ITF-mET_SMA</code>, <code>ITF-mET_Transducer</code>-&gt;<code>ITF-R_reserved</code>, Only needs 5V and 3.3V, Energy use : TODO, ADC V_REF is flexible: using PulseOn and PulseOff, Can use the potentiometer to control the tension, Modularity through jumpers and SMA, Takes a lot of space because of the modularity. SMA, jumpers and pots could be removed., Little flexibility from the use of ICs., Send microcircuits to Edgeflex, Receive the module, Test it with different transducers, Publish the sources in KiCAD, Specs to write, Agreeing on the strips , Defining the ICs to use, Getting schematics, Sofian (for preparing the field with Murgen)|53% |
|oneeye|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ITF-G_gain_control</code>, <code>ITF-I_pulse_on</code>, <code>ITF-J_pulse_off</code>, <code>ITF-N_cc_motor_pwm</code>, <code>ArduinoTrinketPro</code>, <code>ITF-B_5v</code>-&gt;<code>ArduinoTrinketPro</code>-&gt;<code>ITF-G_gain_control</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-I_pulse_on</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-J_pulse_off</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-N_cc_motor_pwm</code>, Based on a breadboard alim, Takes a lot of space , Manage to feed it 12V|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ITF-G_gain_control</code>, <code>ITF-I_pulse_on</code>, <code>ITF-J_pulse_off</code>, <code>ITF-N_cc_motor_pwm</code>, <code>ArduinoTrinketPro</code>, <code>ITF-B_5v</code>-&gt;<code>ArduinoTrinketPro</code>-&gt;<code>ITF-G_gain_control</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-I_pulse_on</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-J_pulse_off</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-N_cc_motor_pwm</code>, Based on a breadboard alim, Takes a lot of space , Manage to feed it 12V, Test if 12V OK, Find supplier|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ITF-G_gain_control</code>, <code>ITF-I_pulse_on</code>, <code>ITF-J_pulse_off</code>, <code>ITF-N_cc_motor_pwm</code>, <code>ArduinoTrinketPro</code>, <code>ITF-B_5v</code>-&gt;<code>ArduinoTrinketPro</code>-&gt;<code>ITF-G_gain_control</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-I_pulse_on</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-J_pulse_off</code>, <code>ArduinoTrinketPro</code>-&gt;<code>ITF-N_cc_motor_pwm</code>, Based on a breadboard alim, Takes a lot of space , Manage to feed it 12V, Test if 12V OK, Find supplier|53% |
|goblin|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ITF-G_gain_control</code>, <code>ITF-C_amplified_raw_signal</code> : because it's used internally, <code>ITF-E_signal_envelope</code> : because it's used internally, <code>ITF-R_reserved</code> : for the signal coming from the pulser (if through track R), <code>ITF-mET_SMA</code> : for the signal coming from the pulser (if through SMA), <code>ITF-C_amplified_raw_signal</code>: Amplified Raw Signal, post TGC, before <code>ADL5511</code>, <code>ITF-E_signal_envelope</code>: enveloppe of the signal, post TGC, <code>ITF-mEG_SPI</code> : signal from the ADC, <code>ADL5511</code>: Enveloppe detection , <code>AD8331</code>: TGC, <code>AD7274</code>: 2Msps SPI ADC, <code>ITF-G_gain_control</code>-&gt;<code>AD8331</code>-&gt;<code>ITF-C_amplified_raw_signal</code>-&gt;<code>ADL5511</code>-&gt;<code>ITF-E_signal_envelope</code>-&gt;<code>AD7274</code>-&gt;<code>ITF-mEG_SPI</code>, <code>ITF-R_reserved</code>-&gt;<code>AD8331</code>, <code>ITF-mET_SMA</code>-&gt;<code>AD8331</code>, Only needs 5V and 3.3V, Energy use : TODO, ADC V_REF is flexible: better resolution in output of the ADC, E_REF is being removed from the signal output, better than Murgen, where we lost 1.1V from the signal, Takes a lot of space because of the modularity. Jumpers and pots could be removed., Little flexibility from the use of ICs., Send microcircuits to Edgeflex, Receive the module, Plug it to a RPi0 or BBB or RPi or ..., Publish the sources in KiCAD|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ITF-G_gain_control</code>, <code>ITF-C_amplified_raw_signal</code> : because it's used internally, <code>ITF-E_signal_envelope</code> : because it's used internally, <code>ITF-R_reserved</code> : for the signal coming from the pulser (if through track R), <code>ITF-mET_SMA</code> : for the signal coming from the pulser (if through SMA), <code>ITF-C_amplified_raw_signal</code>: Amplified Raw Signal, post TGC, before <code>ADL5511</code>, <code>ITF-E_signal_envelope</code>: enveloppe of the signal, post TGC, <code>ITF-mEG_SPI</code> : signal from the ADC, <code>ADL5511</code>: Enveloppe detection , <code>AD8331</code>: TGC, <code>AD7274</code>: 2Msps SPI ADC, <code>ITF-G_gain_control</code>-&gt;<code>AD8331</code>-&gt;<code>ITF-C_amplified_raw_signal</code>-&gt;<code>ADL5511</code>-&gt;<code>ITF-E_signal_envelope</code>-&gt;<code>AD7274</code>-&gt;<code>ITF-mEG_SPI</code>, <code>ITF-R_reserved</code>-&gt;<code>AD8331</code>, <code>ITF-mET_SMA</code>-&gt;<code>AD8331</code>, Only needs 5V and 3.3V, Energy use : TODO, ADC V_REF is flexible: better resolution in output of the ADC, E_REF is being removed from the signal output, better than Murgen, where we lost 1.1V from the signal, Takes a lot of space because of the modularity. Jumpers and pots could be removed., Little flexibility from the use of ICs., Send microcircuits to Edgeflex, Receive the module, Plug it to a RPi0 or BBB or RPi or ..., Publish the sources in KiCAD, Specs to write, Agreeing on the strips , Defining the ICs to use, Getting schematics|<code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ITF-G_gain_control</code>, <code>ITF-C_amplified_raw_signal</code> : because it's used internally, <code>ITF-E_signal_envelope</code> : because it's used internally, <code>ITF-R_reserved</code> : for the signal coming from the pulser (if through track R), <code>ITF-mET_SMA</code> : for the signal coming from the pulser (if through SMA), <code>ITF-C_amplified_raw_signal</code>: Amplified Raw Signal, post TGC, before <code>ADL5511</code>, <code>ITF-E_signal_envelope</code>: enveloppe of the signal, post TGC, <code>ITF-mEG_SPI</code> : signal from the ADC, <code>ADL5511</code>: Enveloppe detection , <code>AD8331</code>: TGC, <code>AD7274</code>: 2Msps SPI ADC, <code>ITF-G_gain_control</code>-&gt;<code>AD8331</code>-&gt;<code>ITF-C_amplified_raw_signal</code>-&gt;<code>ADL5511</code>-&gt;<code>ITF-E_signal_envelope</code>-&gt;<code>AD7274</code>-&gt;<code>ITF-mEG_SPI</code>, <code>ITF-R_reserved</code>-&gt;<code>AD8331</code>, <code>ITF-mET_SMA</code>-&gt;<code>AD8331</code>, Only needs 5V and 3.3V, Energy use : TODO, ADC V_REF is flexible: better resolution in output of the ADC, E_REF is being removed from the signal output, better than Murgen, where we lost 1.1V from the signal, Takes a lot of space because of the modularity. Jumpers and pots could be removed., Little flexibility from the use of ICs., Send microcircuits to Edgeflex, Receive the module, Plug it to a RPi0 or BBB or RPi or ..., Publish the sources in KiCAD, Specs to write, Agreeing on the strips , Defining the ICs to use, Getting schematics, Sofian (for preparing the field with Murgen)|53% |
|retro10PV|<code>ITF-A_gnd</code>, <code>ITF-F_12V</code>, <code>ITF-N_cc_motor_pwm</code>, <code>ITF-mET_Transducer</code>, <code>Motor</code>, <code>Tri-Piezo Head</code>, <code>Motor</code>, <code>ITF-mET_Transducer</code>, <code>Tri-Piezo Head</code>, <code>ATL10PV</code>, <code>ITF-mET_Transducer</code>-&gt;<code>Tri-Piezo Head</code>-&gt;<code>ITF-mET_Transducer</code>, <code>ITF-N_cc_motor_pwm</code>-&gt;<code>Motor</code>, Simple to use, We have removed the position system : we don't have the encoding system, Tough to find a old 10PV probe, Motor is a 12V... doesn't move below 10V ... using 300mA@10V -- we could use a <a href="https://www.pololu.com/product/2117/specs">5V to 12V DC/DC boost similar to this one</a>. Could feed onto the 5V entry and leave on the 12V output. Can be found on Gotronics and such. Or the 12V could be delivered to the board itself., 3 piezos are fixed frequency, Oil to be found to replace lost one =)|<code>ITF-A_gnd</code>, <code>ITF-F_12V</code>, <code>ITF-N_cc_motor_pwm</code>, <code>ITF-mET_Transducer</code>, <code>Motor</code>, <code>Tri-Piezo Head</code>, <code>Motor</code>, <code>ITF-mET_Transducer</code>, <code>Tri-Piezo Head</code>, <code>ATL10PV</code>, <code>ITF-mET_Transducer</code>-&gt;<code>Tri-Piezo Head</code>-&gt;<code>ITF-mET_Transducer</code>, <code>ITF-N_cc_motor_pwm</code>-&gt;<code>Motor</code>, Simple to use, We have removed the position system : we don't have the encoding system, Tough to find a old 10PV probe, Motor is a 12V... doesn't move below 10V ... using 300mA@10V -- we could use a <a href="https://www.pololu.com/product/2117/specs">5V to 12V DC/DC boost similar to this one</a>. Could feed onto the 5V entry and leave on the 12V output. Can be found on Gotronics and such. Or the 12V could be delivered to the board itself., 3 piezos are fixed frequency, Oil to be found to replace lost one =)|<code>ITF-A_gnd</code>, <code>ITF-F_12V</code>, <code>ITF-N_cc_motor_pwm</code>, <code>ITF-mET_Transducer</code>, <code>Motor</code>, <code>Tri-Piezo Head</code>, <code>Motor</code>, <code>ITF-mET_Transducer</code>, <code>Tri-Piezo Head</code>, <code>ATL10PV</code>, <code>ITF-mET_Transducer</code>-&gt;<code>Tri-Piezo Head</code>-&gt;<code>ITF-mET_Transducer</code>, <code>ITF-N_cc_motor_pwm</code>-&gt;<code>Motor</code>, Simple to use, We have removed the position system : we don't have the encoding system, Tough to find a old 10PV probe, Motor is a 12V... doesn't move below 10V ... using 300mA@10V -- we could use a <a href="https://www.pololu.com/product/2117/specs">5V to 12V DC/DC boost similar to this one</a>. Could feed onto the 5V entry and leave on the 12V output. Can be found on Gotronics and such. Or the 12V could be delivered to the board itself., 3 piezos are fixed frequency, Oil to be found to replace lost one =), BiVi|50% |
|mogaba|<code>ITF-mEM_Alimentation</code>, <code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ADL5511</code>: Enveloppe detection , <code>AD8331</code>: TGC, <code>AD7274</code>: 2Msps SPI ADC, <code>ITF-mEM_Alimentation</code>-&gt;<code>BreadBoardAlim</code>-&gt;<code>ITF-B_5v</code>, <code>BreadBoardAlim</code>-&gt;<code>ITF-B_3_3v</code>, Based on a breadboard alim, Takes a lot of space , Manage to feed it 12V|<code>ITF-mEM_Alimentation</code>, <code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ADL5511</code>: Enveloppe detection , <code>AD8331</code>: TGC, <code>AD7274</code>: 2Msps SPI ADC, <code>ITF-mEM_Alimentation</code>-&gt;<code>BreadBoardAlim</code>-&gt;<code>ITF-B_5v</code>, <code>BreadBoardAlim</code>-&gt;<code>ITF-B_3_3v</code>, Based on a breadboard alim, Takes a lot of space , Manage to feed it 12V, Test if 12V OK, Find supplier|<code>ITF-mEM_Alimentation</code>, <code>ITF-A_gnd</code>, <code>ITF-B_5v</code>, <code>ITF-S_3_3v</code>, <code>ADL5511</code>: Enveloppe detection , <code>AD8331</code>: TGC, <code>AD7274</code>: 2Msps SPI ADC, <code>ITF-mEM_Alimentation</code>-&gt;<code>BreadBoardAlim</code>-&gt;<code>ITF-B_5v</code>, <code>BreadBoardAlim</code>-&gt;<code>ITF-B_3_3v</code>, Based on a breadboard alim, Takes a lot of space , Manage to feed it 12V, Test if 12V OK, Find supplier|53% |
# Interfaces table for the motherboard

| Name | Title | Amplitude |
|------|-------|-----------|
|`ITF-A_gnd`|_Ground_|[0V]|
|`ITF-B_5v`|_5V alimentation_|[5V, 5V]|
|`ITF-C_amplified_raw_signal`|_Amplified raw signal_|[0V, 2.5V]|
|`ITF-D_amplified_filtered_signal`|_Amplified filtered signal_|[0V, 2.5V]|
|`ITF-E_signal_envelope`|_Signal envelope_|[0V, 2.5V]|
|`ITF-F_12v`|_12V alimentation_|[12V, 12V]|
|`ITF-G_gain_control`|_Amplifier gain_|[0V, 1V]|
|`ITF-H_neg_12v`|_-12V alimentation_|[-12V, -12V]|
|`ITF-I_pulse_on`|_Pulse on_|[0V, 3.3V-5V]|
|`ITF-J_pulse_off`|_Pulse off_|[0V, 5V]|
|`ITF-K_pulse_redpitaya`|_Pulse info for Redpitaya_|[0V, 3.3V]|
|`ITF-L_18v_alimentation`|_18V external alimentation_|[15V, 20V]|
|`ITF-M_abs_angle`|_Absolute tranducer position_||
|`ITF-N_cc_motor_pwm`|_CC motor pwm_|[0V, 5V]|
|`ITF-N_stepper_b2`|_Stepper motor B2 signal_|[-5V, 5V]|
|`ITF-O_cc_motor_encoder`|_CC motor incremental encoder_|[0V, 5V]|
|`ITF-O_stepper_b1`|_Stepper motor B1 signal_|[-5V, 5V]|
|`ITF-P_stepper_a1`|_Stepper motor A1 signal_|[-5V, 5V]|
|`ITF-Q_stepper_a2`|_Stepper motor A2 signal_|[-5V, 5V]|
|`ITF-R_reserved`|_reserved track_||
|`ITF-S_3_3v`|_3.3V alimentation_|[3.3V, 3.3V]|



# License

## echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

## Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018


