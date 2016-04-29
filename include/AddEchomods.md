# echomods

Creating modules out of the murgen board

## What is it?

The principles of the echOmods is to enable a full chain of ultrasound image processing and hardware control. Four basic modules are considered. Each of this module will be landing on a motherboard, more or less a stripboard, which interfaces are described below.

Key interfaces, signals and alims will be available on each of the 19 tracks on the motherboard, and will enable communication between modules. However, some tracks can be unused by the modules.

In this dense version, there are 4 modules electronic modules, the Transducer and the Motor modules are not depicted.

These modules can have a form factor close to the arduino trinket pro, with a row of 19 pins on the side.

Each module will have a function, as described below. At the heart of this project, there will be 4 modules, plus the motherboard. 2 of these modules will be SMD, 2 as modules based on stripboards. Two additional modules will enable replacing the transducer module and getting advanced signal acquisition/streaming, respectively.

## Modules

* [Goblin](/goblin/Readme.md): the __analog processing module__, was drafted as well during Murgen. 
* [Tobo](/tobo/Readme.md): the __HV and pulser module__, based on a drafted close to Murgen. 
* [One-Eye](/oneeye/Readme.md) is the __MicroControler module__, to be working with Arduinos at first, such as the Trinket Pro.
* [Mogaba](/mogaba/Readme.md) is the __Alimentation Module__.
* and ... the __motherboard__.

Other modules, such as Silent (_analog processing testing module_) and Croaker (_advanced microcontroler module_), are in the teaser stage... More to come later on =)

## Illustration

![Modules organisation](/include/images/modules.png)





