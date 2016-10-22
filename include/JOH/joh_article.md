

Template of Hardware Metapaper
------

For submission to the _Journal of Open Hardware_
 	

# (1) Overview

## Title

__A low-cost, arduino-like dev-kit for single-element ultrasound imaging__

## Paper authors

__Luc K. JONVEAUX (Lead)__

## Paper author roles and affiliations

__Luc K. JONVEAUX (independant maker)__

## Abstract

_A short (up to 250 words) summary of the hardware being described: what problem(s) the hardware addresses, what it does, how it technically/methodologically advances the state-of-the-art, how it was designed and implemented, and its applicability to other issues/research/areas of reuse._
@todo

## Metadata Overview

* First iteration as a beaglebone black cape : https://github.com/kelu124/murgen-dev-kit/ 
* Second iteration of breadboard modules: https://github.com/kelu124/echomods
* Target group: Ultrasound researchers, engineering school students, students, general hackers, ...
* Skills required: For each main manufacturing method, provide information pairs (method - easy / advanced / specialist). E.g. desktop 3d printing - easy; surface mount PCB - advanced; injection moulding - specialistSurface mount PCB – advancedAssembly – easy
* Replication: The first iteration was developed within echopen&#39;s community, and a first series of experimentation done in Vanderbilt University.
* Documentation for the second iteration of hardware has been released on github, on a separate repository. 
* Kits might become available online.

## Keywords

* Ultrasound, electronics, imaging, modules


## Introduction

_An overview of the hardware, what it does, how it was produced, and the research for which it has been used. If the hardware addresses a specific lack or problem, describe the problem in this section and how the hardware addresses the problem. Elaborate how it technically/methodologically advances the state-of-the-art including references to relevant research articles and online references._

Ultrasound imaging has evolved since the first ultrasound machine appeared. The first machines were using single-transducers techniques, coupled to mechanical scanning. This technology was then replaced by more resource-consuming transducer-array-based probes – with the exception of endo probes, where the physical size of the probe is a limiting factor.

Mechanical scanning has its limitation, but also its strengths: the single element means that corresponding analog electronics are simplified, and the cost reduced. Moreover, with progress made in different technical fields, mechanical probes are seen on the market again.Search found little to no documentation of previous research to rebuild these mechanical ultrasound imaging machine functions.

The aim of this work is to provide pieces of kit to allow anyone to understand and recreate the inside of an ultrasound machine. Each electronic module takes the place of a function in the signal processing chain, or allows tapping into the different signals circulating between the blocks. We have chosen to use a module approach to make sure that each key component inside ultrasound image processing can easily be replaced and compared with another module.

A focus has been put on documentation and corresponding infrastructure. The project&#39;s documentation is backed by a script, extracting relevant information from the work logs in the repository, allowing a continuous update of information.

## Overall Implementation and design

_Describe how the hardware was implemented/created, with relevant details of the architecture and design, including general materials (Note: specific details on materials can be addressed in later section &quot;Availability of materials and methods&quot;). The use of diagrams and pictures of the assembled hardware is appropriate. Please also describe any variants and associated implementation differences._

_Note: This is not meant to be an assembly instruction. Assembly instructions, detailed material lists, and construction files must be deposited in an appropriate repository (see Repositories document) and referenced in section &quot;Build Details&quot;._

### Towards simpler and smaller ultrasound devices

Several publication point at the integration of such hardware in the scan head itself, and describe prototypes of single element transducers [4][5][9] or piezo arrays [1][3][7], in integrated, hand-held devices. 

### Using echoes for imaging

Ultrasounds, high frequency sound waves, are used in medical application for both diagnosis and treatment of patients. Their frequencies can vary from 2 to approximately 15 MHz for regular imaging, sometimes higher frequencies are used for delicated, surface imaging.

The ultrasound waves comes from the mechanical oscillations of a crystal in a transducer, excited by electrical pulses (which is called the piezoelectric effect). These pulses of sound are sent by the transducer, propagate through the different media being imaged, and then come back to the transducer as "reflected echoes". These reflected echoes are converted back into an electrical signal by the transducer and are further processed so to form the final image.

![Principles of images](https://raw.githubusercontent.com/kelu124/echomods/master/include/images/JOH/echoimaging.png)

In general, these sound waves, as classical waves, are reflected at the interfaces between the tissues of different accoustic impendance (linked to the density of the medium), the strength of the echo being proportional to the difference in impedance. On the other hand, echoes are not produced if there is no accoustic difference, hence no impedance interface, between media. Homogenous fluidsare seen as echo-free structures.

### A modularized approach

@todo: find article on modules/arduino

The aim of the kit being to allow one to explore the mechanisms of ultrasound processing, and to replace elements of the processing chain as desired, a modularized approach was considered. Each module can be considered as a breakout board of the most central elements, intended for easy experimentation with usual equipment, such as breadboards and standard power supplies.

Using modules also invites to conform to a standard exchange of information between the modules. As stripboards are a common material, it has been decided to make several signals exposed along 19 strips of the board, as per a standard format defined by the echOpen community. It can be noted that current modules leave most of the strips unused.

### Requirements

State-of-the-art publication show a common structure for the different ultrasound systems [3]. One can note that recent developments, and research, show the feasibility to produce compact ultrasound imaging devices, which can interface with a smartphone [8], wirelessly or through USB [21].

A central element in the kit is the sensor, the ultrasound transducer. As we chose a single-channel processing unit, the transducer is a monoelement piezoelectric. This element has a fixed focal depth. For the sake of simplicity, a frequency on the lower range of ultrasound imaging was chosen. Larger characteristic period enable simpler, slower controls and ADCs. A frequency of 3.5MHz was chosen, with a focal distance of 70mm, which is commonly used for obstetric and gynaecological imaging. As a consequence, we chose a repetition period chosen was 300us. This corresponds to an imaging depth of 230mm, more that was is required to image between 20 and 150 mm. This project focused also on single element transducers to avoid developping a more complex beamformer component. The drawback is slow scanning, mechanical fragility, and  insensitivity [12]. To increased the framerate, several transducers and corresponding connections can be integrating in a sweeping or rotating scan head [13].

The kit requires a pulser component: to have the transducer emit a signal, a high voltage pulse, precisely controlled in amplitude and in time, needs to reach the transducer. We chose off-the-shelf components after bibliography and research. Existing ICs exist, such as the MAX14808 [8], but are relatively complex, as they are octal or quad chain components.

The kit then requires an &quot;analog processing&quot; component. After the acoustic wave leaves the transducer, echoes appear due to the acoustic impendance ruptures taking place in the medium being imaged. These echoes are captured by the transducer, and transformed back into a weak electrical signal, which needs to be processed. Classical processing includes filtering the signal around the central frequency of the transducer, then apply a low-noise amplification, then correcting the time-based attenuation. The image being the envelope of this last signal, one also needs to extract the envelope of this signal and pass this image to a digital convertor.
As filtering and band pass consume most of the processing power (up to 80% of processing power)[11], the module allows signal envelope detection with a ADL5511 IC. This also enables a first compression of the data to be transmitted to the user.

On the digitization side, an echo being typically a couple of periods long, the envelope of the signal, hence the ultrasound image, would have a 1 MHz frequency, which would required specific ADCs. Open hardware boards have onboard ADCs, but very few have ADCs above the Msps range, This implies that an analog envelope detection takes place on the board. However, we have used an existing open-source 40Msps DAQ on one of the modules, and have as well tried a 6Msps arduino IDE-compatible microcontroler to acquire the signal and stream it over wifi. 

The design in modules, along with selected easily-accessed signal interfaces, provides access to the different intermediary signals.

### A embedded-linux first iteration

A first iteration of the hardware was embodied in a beaglebone-black extension (cape), where the cape 10Msps ADC would be tapping into the two PRUs to acquire the signal. A special attention was given to simplify power supply, limiting the inputs to 5V and 3.3V, the most common levels.

### Designs of modules

This first iteration permitted tests, and validated parts of the design. Despite its test points, this board did not provide all the insights that can be extracted from the hardware, so a redesign was considered, to expose all key inputs and outputs of the signal processing. While existing compact elements exists, such as the AFE5808 (which which include low  noise amplifiers (LNA)  and  analog­ to-digital converters )[8], we prefered  using separate ICs, so that the user can measure exactly the target signal.
 
For the sake of simplicity, a design of two separated modules emerged.

* One is the pulser module, where the high voltage and connection to the transducer lies.
* The other is the analog processing modules. A dual input for the clipped raw signal from the transducer was integrated, as well as different jumpers and pots, to control the VGA gain, as well as the ADC reference voltage. The high-speed ADC was removed, and replaced with a onboard serial 2Msps ADC.

The remaining modules are microcontrollers, processing units, or power supplies that can be easily obtained and easily modified and programmed.

The latest set of modules is based on a wireless-enabled, arduino-compatible STM32 

# (2) Quality control

## Safety

Describe all relevant safety issues or reference to a risk assessment if included in the hardware documentation. Detail what safety considerations have been included in the hardware design and how these features have been tested, including any official safety standards or criteria that were used in this assessment. If appropriate, discuss the wider context of use of the hardware and safety issues or risks that may arise in the use environment.Most of the modules are found on usual open-source hardware procurement websites. However, the two modules specifically developed for this project fail to enter this category.

One of the modules uses a DC-booster, which can raise the voltage it delivers above 100V.
However, design has limited high-voltage to specific points within the module, and to the SMA connector going to the transducer. The other pins of the module have inputs/outputs that range in the [-5V ; 5V] bracket.

During the tests that took place, the full setup, without the motor, did not use more than 170mA at 9V. The ATL3 probe, alimented at 3.3V, brought the total power envelopeto 330mA at 9V.

The difference of stimulating the transducer causeda 5mA at 9V difference.

## Calibration

If the hardware is used for measurements, please detail here how the reliability of measurements, or other hardware properties that are relevant for measurements, has been quantified and explain the results. Be clear about the processes or procedures used to compare the hardware to a standard, as well as the description of the standard calibrated against.

Detail the general procedures in place for users to calibrate their hardware before or during use. What methods can be used to relate user generated data to data from other sources?

Note: Detailed instructions belong in documentation; here, provide insight into how and why the calibration is valid.

### Calibrating the signal

Calibration of ultrasound electrical signal processing requires a standard signal, which is difficult to provide if using a classical transducer. Moreover, due to the variety of transducers, it would be extremely difficult to obtain a standard setup and signal.A calibration tool has been built (the DAC module), based on a STM32F205 DAC. This permitted to &quot;record&quot; the calibration signal, and to simulate the behaviour of the pulser module.

Qualification and calibration of the high-voltage level on the pulser module is done using an oscilloscope.

Finally, the gain level of the analog processing module is in the tests described below adjusted once and for all at the beginning of the experiment, to use the full range of output signal and obtain the best image possible. The level of gain can be selected, either from one input signal, coming from an external DAC for example, or with a potentiometer, the choice between the two being made possible by a jumper.

### Developping a home-made reference material

A home-made phantom was used to test the first iteration of the board. It was made of a gelatin phantom, with tapioca inclusions of two types (2mm and 8mm), the medium being contained in a condom (as in the picture below). 

![The condom phantom](https://raw.githubusercontent.com/kelu124/echomods/master/include/images/JOH/phantom.jpg)

This type of phantom does not conserve well, and was not reused for the second iteration.

## General testing

_In this section, details can be provided on the testing of hardware functionalities, that are not directly essential for precision operation of the hardware in the given context (which are in turn, where applicable, handled under Calibration), such as automated movements to position the hardware, repeatability of tool exchanges, recyclability, water-tightness, weight or other possibly relevant characteristics. We encourage the authors to characterise all appropriate functionalities of the hardware, if not already described elsewhere (add reference instead). The testing should define the safe/reliable limits in which the components can be operated (e.g. step size and repeatability of linear motion, force ranges, ratio of devices with leaks when built in a workshop, etc). This will enhance the usability of the hardware or method in other contexts._

General testing has been done, especially for the two modules:

* For the pulser, the criteria of the tests were the duration of the pulse, which should match the input signals, as well as the voltage of the pulse, being set by a potentiometer. Tests were done using an oscilloscope.
* For the analog processing unit,the DAC module allowed a standard input to be processed, and the result of the processing analysed.

General conditions of the tests were that of of a 150ns, 70V pulse for the pulser unit, with a repetition every 300us.

_ __Again: Detailed instructions belong in documentation; here, provide a summary_ _ __ instead._

# (3) Application

## Use case(s)

_Describe at least one example of an application of your hardware. This should include some evidence of output, e.g. data produced by the use of the device or a picture of other types of results. Outline how the quality control in the previous section enables the use of the hardware in this context. We encourage the inclusion of experiment results or the reference to a publication (published or to-be-published) where these results are detailed. We also encourage pointers to ongoing work._

_Note: In the spirit of openness, we require authors to provide (or link to) datasets along with the submitted graphic representations. We do not impose arbitrary limits on inclusion of data so please include sufficient empirical detail and results to ensure your data can be easily verified, analysed and clearly interpreted by the wider scientific community._

### General case

The modules can be assembled in a minimum set using power-supply, pulser control, pulser module, and data acquisition.

Setup with the first iteration, the beaglebone cape

The pulser control was realized using a Trinket Pro (point A), controlling the board (B).

@todoimage

Setup with the second iteration, the modules

@todoimage

### Testing a single element transducer

A first test was done using a single-element transducer, salvaged from a used endovaginal S-VRW77AK ultrasound probe. The transducer was moved by a basic servomotor controlled by a Trinket Pro 5V, which doubled as the controller sending the pulse commands. Data was acquired on the first iteration at 5Msps with a bitscope unit (BS10). Noise kept the SNR low, but nonetheless provided a source of data, and permitted to assess the performances of the different blocks.

![Bitscope acquisition](https://raw.githubusercontent.com/kelu124/echomods/master/include/20161016/2619341460036774092.png)

### Testing different a commercial transducer

The dev-kit has been tested with a ATL-3 probe found on ebay. This mechanical probe has 3 rotating transducers, a characteristic of this series of ATL probes. The ATL Access 3 probe connector to the transducers is extremely simple, and consists in a BNC cable. The other connector&#39;s pins may correspond to the control of the probe motor. The probe&#39;s motor was connected to a 3.3V, allowing the transducers to rotate freely in the body of the probe.

A first acquisition try took place using a bitscope micro (BS10), similarly to the previous application. However, the interval between two captures did not lead to satisfactory acquisitions. A second try was done using the PRUDAQ, a faster, real-time acquisition unit, designed as an extension of the beaglebone. The PRUDAQ was connected to the amplified envelope signal of the analog processing module, clipped at 1.4V to protect the DAQ input. 32MB were acquired,

With 32MB containing two signals encored over 16 bits each, there is 8388608 points of data, or approximately 839ms. With a pulser set at 300us intervals, we should see around 2796 lines of data, which was the case. Rebuilding the image, we could see close to 12 full images,for a framerate of 14 fps, meaning that the motor was at approximately 290rpm.

The setup was used on a ultrasound phantom, as well as on a small dice (10mm side) which provided the image below:

![ATL probe image](https://raw.githubusercontent.com/kelu124/echomods/master/include/20160814/sonde3V_1-4.csv-SC.png)

Further testing was done with a ATL 10PV, 

### Datasets

* A small library of images obtained on home-made phantoms with the first iteration is available at : [https://github.com/kelu124/murgen-dev-kit/tree/master/software/examples](https://github.com/kelu124/murgen-dev-kit/tree/master/software/examples)
* Full data from the regular phantom imaging can be found on [https://github.com/kelu124/echomods/blob/master/include/20160822/2016-08-22-Fantom.md](https://github.com/kelu124/echomods/blob/master/include/20160822/2016-08-22-Fantom.md),
* The data corresponding to the image of the dice can be found at [https://github.com/kelu124/echomods/blob/master/include/20160814/2016-08-14-HackingAUltrasoundProbe.md](https://github.com/kelu124/echomods/blob/master/include/20160814/2016-08-14-HackingAUltrasoundProbe.md) . 

## Reuse potential and adaptability

### Reuse potential of the modules

#### Application for non-destructive testing (NDT)

The technology developped here does not differ from the technology used in NDT. Therefore, the whole set of modules can be used as-is in NDT, or its design can be adapted to NDT requirements.

#### High speed DAC

Having worked with the DAC module enables one to be able to work on the acquisition system, based on a known-signal input. This enables repeatability of the input, contrarly to images that are usually capture using a probe on a ultrasound phantom. This DAC can go up to 2MHz, on a limited voltage range, and could be used in testing analog signals processing

#### Pulser

IT is suggested that the pulser can be used in medical ultrasound image devices, or for test applications. Its up to 35 MHz operating frequency and 2 ns matched delay times allow higher frequencies uses, such as superficial imaging or doppler analyses [1].

#### Analog processing

The analogue processing module was tested for signals from 2MHz to 10MHz, with some distortion happening on the higher end of the bracket. However, it can be noted that, with the possibility to measure and control the inputs and outputs of between each processing unit, this module could possibly be used for signal demodulation.

#### High-speed, wireless DAQ

The wireless DAQ module we built can go up to 6Msps, with a 10-bit resolution, on a [0;3.3V] input range, and can work on a battery, as there is a battery management system already built-in. This module could therefore be used in systems where rapid acquisition and wireless streaming need to be used. For example, for Software Defined Radio (SDR), this module can be used after the demodulation step.

### Adaptability of the home-made modules

#### Other uses

The modules source code has been released, it is relatively easy for electronic engineers to reuse this code. 

Apart from the well-know obstetrics and gynecology uses, ultrasound devices have been developped for several uses, which the current hardware could support, such as: doppler ultrasonography, constrast ultrasonography, molecular ultrasonography, elastography, non destructing testing, bladder measurement, ... . An interesting one, suggested by Richard et al [3], would be to provide visual biofeedback to stroke victims relearning to control muscles. The same board could be reused for work on sonar-like systems [14].

#### A low-cost option

Apart from the wireless-enable microcontroler at 35$, the two custom modules components cost 60 and 85 euros respectively. This low-cost lifts the barrier of high-cost equipment purchase, and hance facilitates the reuse of these designs.

### Support

This project benefits from an infrastructure that is completely open: github for the storage of files, and a gitbook to synthetize the complete documentation. A mailing-list gathers the community of different contributors, friends, .. which enables a community-based support.

# (4) Build Details

## Availability of materials and methods

Most of the modules can be sourced from usual, well known open-hardware online suppliers.  Moreover, the two specific modules can either be produced with a proper surface mount equipment, or the manufacturing files sent to a fab. They may also become available through a crowdfunding platform. The HV7360 becoming obsolete, a new version of the board has been published.

## Ease of build

_Have any measures been taken in the design to make the hardware easy to build for other users e.g. reduction of parts, features in the design to make the hardware assembly more reliable?_

When the first iteration had 4 layers, the two newly made modules are 2-layer designs, for the sake of simplicity.

The design also relies on off-the-shelf ICs to limit the number of its components. A trade-off had to be found when some ICs were BGA ICs.

The non-custom modules can be found commercially, or built.

Most of systems are FPGA (or DSP) based, especially for higher imaging frequencies [4][5], as well as using multiple-element transducers [7] -while maintaining costs and power consumption low. We considered that programming FPGA (even DSPs) was a steep requirement for non-specialists, hence we focused on alternatives. However, it can be noted that a FPGA module could be developped to interface with existing modules.  

## Operating software and peripherals

The hardware has modules that require software to operate. These modules relie on the arduino IDE, and their code was compiled using Arduino IDE 1.6.9. For the wireless module, the WICED BSP version used was 0.5.5.

To collect the data, the beaglebone module simply uses the beaglebone black with its PRUDAQ cape installed, where the data being acquired is available on a device (/dev/beaglelogic). With the wireless module, any wifi-enabled device can acquire the UDP stream. 

## Dependencies

_E.g. other hardware or software projects, modular components, libraries, frameworks, incl. minimum version compatibility. Explicitly state if dependencies are proprietary / closed source._

* Most of the processing code is using Python 2.7, which is _GPL-compatible_.
* The Beaglebone module is using a BeagleBone Black, which is under a _Creative Commons Attribution-Share Alike 3.0_ license.
* The Feather WICED module is, Open Hardware and Open Source for its software.
* The code for the arduino-compatible modules is developped under Arduino IDE.
* The two boards developped under this project are following the Open Hardware TAPR license.
* The source documents for these two boards was originally developped using Altium (proprietary), but the source is being ported to KiCad, which is under a GNU General Public License(GPL) version 3.

## Hardware documentation and files location:

@todo Archive for hardware documentation and build files (required. See _Repositories_ document for criteria, DocuBricks and alternative repositories.) _Note: We require the inclusion of modifiable design files as well as a detailed documentation of the functionality of the hardware with assembly instructions. This will be assessed as part of the journal peer review process._

* Name: Github repository for the ultrasound arduino-like modules
* Persistent identifier: https://github.com/kelu124/echomods/
* Licence: TAPR Open hardware license under which the documentation and files are licensed
* Publisher: Luc JONVEAUX
* Date published: 31/10/16
* Modifiable design files (if different from above)


# (5) Discussion

## Conclusions

_Conclusions, learned lessons from design iterations, learned lessons from use cases, summary of results._

As a first try to hardware by the author, this work has been an endlessly source of learning.


We finally obtained a cheap (400$) set of modules for ultrasound imaging, leveraging on existing open-source hardware and integrated circuits.
Power consumption fitting within a USB power envelope, it can easily be powered by off-the-shelf 5V power banks, as well as a small design (A5 format) and light weight, allow for the easy of manipulation. 

Wireless transfer also enable 


## Future Work

_Further work pursued by the authors or collaborators; known issues; suggestions for others to improve on the hardware design or testing,, given what you have learned from your design iterations._

This set of modules shows that ultrasound imaging can profit from a usable dev-kit. Several points in this work however have to be reviewed, if not improved. Indeed:

* In general, the design of the boards can be greatly improved. For example, having only two layers on the current design may be a source of noise. Moreover, applying a RF net to the board or using a RF shield for the sensitive parts may be an idea.
* The pulser-module design uses only two inputs, and one high voltage source. However, the chip enables more complex uses as a pulser, which can be further explored.
* The PRUDAQ has a real-time access to the digital information, as well as a linux userspace. Further programming would enable the beaglebone plateform to be a real server and controller of the setup.
* The modules are slightly too wide for a breadboard: an effort could be done to make the pins available on a standard breadboard.
* A whole field left unexplored so far is that of the transducer. As the key sensor in the kit, it would be interesting to explore relevant technologies to develop a low-cost, good-enough transducer.
* The transducer at the moment lies in water. For ease of work, scan head will have to be developped. A difficulty will be to determine the  acoustic window material and its thickness. Several works already give pointers in that sense. [1]
* An additional module would be a wire phantom, use to qualify the images obtain with such a system. Wire phantoms are commonly used [9], where 20 μm wire would be used.
* From a software point of view, the modules could be wirelessly controled, levelaring the existing wireless communication channel, so that researchers can use a single unit for a laboratory, controlled from personal computers.
* For these high frequencies, a robust scan head can be used to obtain 130 fps, with light-weight transducer, and magnetic drive mechanism [2]. A bimorph actuator would be sufficient to drive the imaging transducer [4][5] immerged in the probe. The advantage of such a scanning device would be to precisely know the position of the line being imaged, while being cheaper, and more robust as there are no mechanical parts. An other alternative would be a ultrasound motor [6].
* An additional module could link the ADC with a USB interface, providing as well the power for the other modules. We have shown that our modules can be run with a power bank, and previous work show is it possible to stay within the USB power envelope [3].

Having a set of unexpensive arduino-like modules will support the development of ultrasound imaging research, and provide the keys to the researchers, makers and curious-minded persons to explore this field.

## Paper author contributions

_Task (e.g. design, assembly, use cases contribution, documentation, paper writing), contribution, author name._

## Acknowledgements

A huge thanks to the friends in the community for their sharing their ideas and giving their support. Thanks as well to Prof Charles and Zach to have given a try at testing the first iteration, Sofian for his help on the hardware, the Hackaday community forgiving me the chance to go to the 2016 finals, the echOpen community (Farad, Benoit, Vincent, Jerome, Virginie, Emilie and the others) who has kept me motivated!

## Funding statement

This project has been funded by personal funds, and supported by two prizes from the hackaday 2016 contest.

## Competing interests

The authors declare that they have no competing interests.

Though LJ is a founder of the echOpen&#39;s project, this work has been pursued individually,the echOpen association has no involvement with this work. LJ is discussing the crowdfunding of these modules&#39; kits with a partner.

## References

@todelete _Please enter references in the Vancouver style and include a DOI where available, citing them in the text with a number in square brackets, e.g._

1. Erickson S, Kruse D, Ferrara K. A hand-held, high frequency ultrasound scanner. In IEEE; 2001 [cité 21 oct 2016]. p. 1465‑8. Disponible sur: http://ieeexplore.ieee.org/document/991996/
2. Lei Sun, Richard WD, Cannata JM, Feng CC, Johnson JA, Yen JT, et al. A High-Frame Rate High-Frequency Ultrasonic System for Cardiac Imaging in Mice. IEEE Transactions on Ultrasonics, Ferroelectrics and Frequency Control. août 2007;54(8):1648‑55. 
3. Richard WD, Zar DM, Solek R. A low-cost B-mode USB ultrasound probe. Ultrason Imaging. janv 2008;30(1):21‑8. 
4. Bezanson AB, Adamson R, Brown JA. A low-cost high frame-rate piezoelectric scanning mechanism for high-frequency ultrasound systems. In IEEE; 2011 [cité 21 oct 2016]. p. 458‑61. Disponible sur: http://ieeexplore.ieee.org/document/6293658/
5. Brown JA, Leadbetter J, Leung M, Bezanson A, Adamson R. A low cost open source high frame-rate high-frequency imaging system. In IEEE; 2013 [cité 21 oct 2016]. p. 549‑52. Disponible sur: http://ieeexplore.ieee.org/document/6725177/
6. Carotenuto R, Caliano G, Caronti A, Savoia A, Pappalardo M. Very fast scanning probe for ophthalmic echography using an ultrasound motor. In IEEE; 2004 [cité 21 oct 2016]. p. 1310‑3. Disponible sur: http://ieeexplore.ieee.org/document/1418032/
7. Lee Y, Kang J, Sunmi Yeo, Lee J, Kim G-D, Yoo Y, et al. A new smart probe system for a tablet PC-based point-of-care ultrasound imaging system: Feasibility study. In IEEE; 2014 [cité 21 oct 2016]. p. 1611‑4. Disponible sur: http://ieeexplore.ieee.org/document/6931891/
8. Ahn S, Kang J, Kim P, Lee G, Jeong E, Jung W, et al. Smartphone-based portable ultrasound imaging system: Prototype implementation and evaluation. In IEEE; 2015 [cité 21 oct 2016]. p. 1‑4. Disponible sur: http://ieeexplore.ieee.org/document/7329474/
9. Ranganathan K, Santy MK, Fuller MI, Zhou S, Blalock TN, Hossack JA, et al. A prototype low-cost handheld ultrasound imaging system. In: Walker WF, Emelianov SY, éditeurs. 2004 [cité 21 oct 2016]. p. 24. Disponible sur: http://proceedings.spiedigitallibrary.org/proceeding.aspx?doi=10.1117/12.537724
10. Leveques P. Architecture d’un processeur dédié aux traitements de signaux ultrasoniques en temps réel en vue d’une intégration sur puce. [Internet]. [École Polytechnique de Montréal]; 2011. Disponible sur: https://publications.polymtl.ca/509/
11. Kyu Cheol Kim, Min Jae Kim, Hyun Suk Joo, Wooyoul Lee, Changhan Yoon, Tai-Kyong Song, et al. Smartphone-based portable ultrasound imaging system: A primary result. In IEEE; 2013 [cité 21 oct 2016]. p. 2061‑3. Disponible sur: http://ieeexplore.ieee.org/document/6725301/
12. Baran JM, Webster JG. Design of low-cost portable ultrasound systems: Review. In IEEE; 2009 [cité 21 oct 2016]. p. 792‑5. Disponible sur: http://ieeexplore.ieee.org/document/5332754/
13. Saijo Y, Nitta S, Kobayashi K, Arai H, Nemoto Y. Development of an ultra-portable echo device connected to USB port. Ultrasonics. avr 2004;42(1-9):699‑703. 
14. Sharma JK. Development of a wide band front end echo sounder receiver circuit. 2015; Disponible sur: http://urn.nb.no/URN:NBN:no-51835
15. Carotenuto R, Caliano G, Caronti A, Savoia A, Pappalardo M. Fast scanning probe for ophthalmic echography using an ultrasound motor. IEEE Transactions on Ultrasonics, Ferroelectrics and Frequency Control. nov 2005;52(11):2039‑46. 
16. Bharath R, Kumar P, Dusa C, Akkala V, Puli S, Ponduri H, et al. FPGA-Based Portable Ultrasound Scanning System with Automatic Kidney Detection. Journal of Imaging. 4 déc 2015;1(1):193‑219. 
17. Dusa C, Rajalakshmi P, Puli S, Desai UB, Merchant SN. Low complex, programmable FPGA based 8-channel ultrasound transmitter for medical imaging researches. In IEEE; 2014 [cité 21 oct 2016]. p. 252‑6. Disponible sur: http://ieeexplore.ieee.org/document/7001850/
18. Raj JR, Rahman SMK, Anand S. Microcontroller USB interfacing with MATLAB GUI for low cost medical ultrasound scanners. Engineering Science and Technology, an International Journal. juin 2016;19(2):964‑9. 
19. Hendy AM, Hassan M, Eldeeb R, Kholy D, Youssef A-B, Kadah YM. PC-based modular digital ultrasound imaging system. In IEEE; 2009 [cité 21 oct 2016]. p. 1330‑3. Disponible sur: http://ieeexplore.ieee.org/document/5441904/
20. Chiang AM, Chang PP, Broadstone SR. PC-based ultrasound imaging system in a probe. In IEEE; 2000 [cité 21 oct 2016]. p. 1255‑60. Disponible sur: http://ieeexplore.ieee.org/document/921551/





### Copyright notice

Authors who publish with this journal agree to the following terms:

* Authors retain copyright and grant the journal right of first publication with the work simultaneously licensed under a [Creative Commons Attribution License](http://creativecommons.org/licenses/by/3.0/) that allows others to share the work with an acknowledgement of the work&#39;s authorship and initial publication in this journal.
* Authors are able to enter into separate, additional contractual arrangements for the non-exclusive distribution of the journal&#39;s published version of the work (e.g., post it to an institutional repository or publish it in a book), with an acknowledgement of its initial publication in this journal.

By submitting this paper you agree to the terms of this Copyright Notice, which will apply to this submission if and when it is published by this journal.

 
