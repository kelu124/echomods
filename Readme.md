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
|<img src='https://github.com/kelu124/echomods/blob/master/sleepy/viewme.png' align='center' width='150'>|**[sleepy](/sleepy/Readme.md)**: The aim of this echOmod is to encase the whole modules object in a neat case, making it transportable.|||
|<img src='https://github.com/kelu124/echomods/blob/master/tobo/viewme.png' align='center' width='150'>|**[tobo](/tobo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-S_3_3v</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-R_reserved</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/oneeye/viewme.png' align='center' width='150'>|**[oneeye](/oneeye/Readme.md)**: The module aims at making a microcontroler, for the moment the <code>ArduinoTrinketPro</code>, usable with the motherboard and the set of modules.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-S_3_3v</li></ul>|<ul><li>ITF-G_gain_control</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-N_cc_motor_pwm</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/croaker/viewme.png' align='center' width='150'>|**[croaker](/croaker/Readme.md)**: The aim of this echOmod is to receive the signal and process it.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-mEG_SPI</li></ul>|<ul><li>Screen</li><li>WiFi</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-S_3_3v</li><li>ITF-G_gain_control</li><li>ITF-InternalPot1_gain_control</li><li>ITF-C_amplified_raw_signal</li><li>ITF-E_signal_envelope</li><li>ITF-R_reserved</li><li>ITF-InternalPot2_ADC_Vref</li><li>ITF-mET_SMA</li></ul>|<ul><li>ITF-C_amplified_raw_signal</li><li>ADL5511</li><li>ITF-E_signal_envelope</li><li>ITF-mEG_SPI</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/retro10PV/viewme.png' align='center' width='150'>|**[retro10PV](/retro10PV/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former <a href="http://echopen.org/index.php/ATL_Access_10PV">ATL10PV</a>.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/mogaba/viewme.png' align='center' width='150'>|**[mogaba](/mogaba/Readme.md)**: The aim of this echOmod is to get 3.3V and 5V done.|<ul><li>ITF-mEM_Alimentation</li><li>ITF-F_12V</li></ul>|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-F_12V</li><li>ITF-S_3_3v</li></ul>|


# Progress on building the modules 


| Name of module | ToDo | Done | Contrib | Progress |
|------|-------|----|------|------|
|sleepy|<ul><li>Choose the design once the modules are done</li><li>Get to work with Arthur</li></ul>|<ul><li>Checking Arthur availability</li></ul>|<ul><li>Arthur</li></ul>|33% |
|tobo|<ul><li>Send microcircuits to Edgeflex</li><li>Receive the module</li><li>Test it with different transducers</li><li>Publish the sources in KiCAD</li></ul>|<ul><li>Specs to write</li><li>Agreeing on the strips/tracks </li><li>Defining the ICs to use to pulse</li><li>Getting schematics</li></ul>|<ul><li>Sofian (for preparing the field with Murgen)</li></ul>|50% |
|oneeye||<ul><li>First test with Arduino Trinket</li></ul>||100% |
|croaker|<ul><li>Choose the platform (BBB, RPi0, STM32, ... ?)</li><li>Getting some codes</li><li>Getting some images</li><li>Getting images onto a screen</li><li>Replace the work done by <a href="/oneeye/">OneEye</a> by <a href="/croaker/">Croaker</a>.</li></ul>|<ul><li>Nothing</li></ul>|<ul><li>??</li></ul>|16% |
|goblin|<ul><li>Send microcircuits to Edgeflex</li><li>Receive the module</li><li>Plug it to a RPi0 or BBB or RPi or ...</li><li>Publish the sources in KiCAD</li></ul>|<ul><li>Specs to write</li><li>Agreeing on the strips </li><li>Defining the ICs to use</li><li>Getting schematics</li></ul>|<ul><li>Sofian (for preparing the field with Murgen)</li></ul>|50% |
|retro10PV|<ul><li>Control the motor with a 12V PWM</li><li>Integrate 12V+PWM in the probe body</li><li>Put plugs into the probe body</li></ul>|<ul><li>Repair the probe</li><li>Simplify it</li></ul>|<ul><li>BiVi</li></ul>|40% |
|mogaba|<ul><li>Manage to feed it 12V</li><li>Bring power to it through the 12V <code>ITF-F_12V</code> track </li></ul>|<ul><li>Test if 12V OK</li><li>Find supplier</li></ul>||50% |
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


