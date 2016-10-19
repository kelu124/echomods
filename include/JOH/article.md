

## Template of Hardware Metapaper

For submission to the _Journal of Open Hardware_

To complete this template, please replace the blue text with your own. The paper has five main sections: (1) Overview; (2) Quality Control; (3) Application (4) Build Details (5) Discussion.

# (1) Overview

## ** ** Title

The title of the hardware paper should focus on the hardware, e.g. &quot;[type of hardware] to automate laboratory protocol X&quot; or &quot;Surface Trawl for Collecting Marine Microplastics.&quot; If the hardware is closely linked to a specific research paper, then &quot;[Hardware type] from [Paper Title]&quot; is appropriate. The title should relate to the functionality of the hardware and the area it relates, to rather than making claims about the usability or user characteristics of hardware, e.g. &quot;Easy-to-use&quot;. **A**  **low-cost,**  **module-based dev-kit**  **for**  **single-element ultrasound imaging**

## Paper authors

1. Last name, first name; _(Lead/corresponding author first)_

2. Last name, first name; _etc. __Luc K.__ JONVEAUX (Lead)_

## Paper author roles and affiliations

1. First author role and affiliation

2. Second author role and affiliation _etc._

_Note: One author can have multiple affiliations and affiliations can include &quot;independent&quot;.__Luc K. JONVEAUX (inde__p __en__ de __n__ t__)_

## Abstract

A short (up to 250 words) summary of the hardware being described: what problem(s) the hardware addresses, what it does, how it technically/methodologically advances the state-of-the-art, how it was designed and implemented, and its applicability to other issues/research/areas of reuse.

|
## Metadata Overview
_Please provide the following overview and self-assessment_Main design files: link to repository with design files and assembly instructionsFirst iteration as a beaglebone black cape : https://github.com/kelu124/murgen-dev-kit/ Second iteration of breadboard modules: https://github.com/kelu124/echomodsTarget group:e.g. secondary school students, layperson, undergraduate students, scientists in [discipline], trained engineers, use of professional servicesUltrasound researchers, engineering school students, students, general hackers, Skills required: For each main manufacturing method, provide information pairs (method - easy / advanced / specialist). E.g. desktop 3d printing - easy; surface mount PCB - advanced; injection moulding - specialistSurface mount PCB – advancedAssembly – easyReplication: Project has been replicated at time of publication? Include reference (possibly way of contact). Links to places where future builds and kits might be found (repository, group website, collaboration site, etc.).The first iteration was developed within echopen&#39;s community, and a first series of experimentation done in Vanderbilt University.Documentation for the second iteration of hardware has been released on github, on a separate repository. Kits might become available online._See section &quot;Build Details&quot; for more detail._
## Keywords
_(required)_ keyword 1; keyword 2; etc.Keywords should make it easy to identify who and what the hardware will be useful for. Maximum of 5 keywords. E.g.: microbiology; laboratory; microfluidics; single cell analysis; fluorescenceUltrasound, electronics, imaging, modules, |
| --- |

## Introduction

_An overview of the hardware, what it does, how it was produced, and the research for which it has been used. If the hardware addresses a specific lack or problem, describe the problem in this section and how the hardware addresses the problem. Elaborate how it technically/methodologically advances the state-of-the-art including references to relevant research articles and online references._

Ultrasound imaging has evolved since the first ultrasound machine appeared. The first machines were using single-transducers techniques, coupled to mechanical scanning. This technology was then replaced by more resource-consuming transducer-array-based probes – with the exception of endo probes, where the physical size of the probe is a limiting factor.

Mechanical scanning has its limitation, but also its strengths: the single element means that corresponding analog electronics are simplified, and the cost reduced. Moreover, with progress made in different technical fields, mechanical probes are seen on the market again.Search found little to no documentation of previous research to rebuild these mechanical ultrasound imaging machine functions.

The aim of this work is to provide pieces of kit to allow anyone to understand and recreate the inside of an ultrasound machine. Each electronic module takes the place of a function in the signal processing chain, or allows tapping into the different signals circulating between the blocks. We have chosen to use a module approach to make sure that each key component inside ultrasound image processing can easily be replaced and compared with another module.

A focus has been put on documentation and corresponding infrastructure. The project&#39;s documentation is backed by a script, extracting relevant information from the work logs in the repository, allowing a continuous update of information.

## Overall Implementation and design

### Describe how the hardware was implemented/created, with relevant details of the architecture and design, including general materials (Note: specific details on materials can be addressed in later section &quot;Availability of materials and methods&quot;). The use of diagrams and pictures of the assembled hardware is appropriate. Please also describe any variants and associated implementation differences.

### Note: This is not meant to be an assembly instruction. Assembly instructions, detailed material lists, and construction files must be deposited in an appropriate repository (see Repositories document) and referenced in section &quot;Build Details&quot;.

### Subsections

### We encourage the use of subsections to highlight the modular functionality of the design or to highlight different design achievements. These questions might help you find appropriate subsections: What parts of the hardware could be used as a component of another project or a variation of this hardware? What solutions do you find most noteworthy given your experiences during the design iterations? What separate actions does the hardware perform?Choosing a module approach

The aim of the kit being to allow one to explore the mechanisms of ultrasound processing, and to replace elements of the processing chain as desired, a modularized approach was considered.

Each module can be considered as a breakout board of the most central elements, intended for easy experimentation with usual equipment, such as breadboards and standard power supplies.

Using modules also invites to conform to a standard exchange of information between the modules. As stripboards are a common material, it has been decided to make several signals exposed along 19 strips of the board. It can be noted that current modules leave most of the strips unused.

### Requirements

A central element in the kit is the sensor, the ultrasound transducer. For the sake of simplicity, a frequency on the lower range of ultrasound imaging was chosen, as longer characteristic times would enable simpler actuators and slower ADCs. A frequency of 3.5MHz was chosen, with a focal distance of 70mm.

The kit requires a pulser component: to have the transducer emit a signal, a high voltage pulse, precisely controlled in amplitude and in time, needs to reach the transducer.

The kit then requires an &quot;analog processing&quot; component. After the acoustic wave leaves the transducer, echoes appear due to the acoustic impendance ruptures taking place in the medium being imaged. These echoes are captured by the transducer, and transformed back into a weak electrical signal, which needs to be processed. Classical processing includes filtering the signal around the central frequency of the transducer, then apply a low-noise amplification, then correcting the time-based attenuation. The image being the envelope of this last signal, one also needs to extract the envelope of this signal and pass this image to a digital convertor.

An echo being typically a couple of periods long, the envelope of the signal, hence the ultrasound image, would have a 1 MHz frequency, which would required specific ADCs. Open hardware boards have onboard ADCs, but very few have ADCs above the Msps range,  This implies that an analog envelope detection takes place on the board.

The repetition period chosen was 300us. This corresponds to an imaging depth of 230mm, more that was is required to image between 20 and 150 mm.

### First iteration

A first iteration of the hardware was embodied in a beaglebone-black extension (cape), where the cape 10Msps ADC would be tapping into the two PRUs to acquire the signal. A special attention was given to simplify power supply, limiting the inputs to 5V and 3.3V, the most common levels.

### Designs of modules

This first iteration permitted tests, and validated parts of the design. Despite its test points, this board did not provide all the insights that can be extracted from the hardware, so a redesign was considered, to expose all key inputs and outputs of the signal processing. For the sake of simplicity, a design of two modules emerged.

- --One is the pulser module, where the high voltage and connection to the transducer lies.
- --The other is the analog processing modules. A dual input for the clipped raw signal from the transducer was integrated, as well as different jumpers and pots, to control the VGA gain, as well as the ADC reference voltage. The high-speed ADC was removed, and replaced with a serial 2Msps ADC.

The remaining modules are microcontrollers, processing units, or power supplies that can be easily obtained and easily modified and programmed.

# (2) Quality control

## Safety

Describe all relevant safety issues or reference to a risk assessment if included in the hardware documentation. Detail what safety considerations have been included in the hardware design and how these features have been tested, including any official safety standards or criteria that were used in this assessment. If appropriate, discuss the wider context of use of the hardware and safety issues or risks that may arise in the use environment.Most of the modules are found on usual open-source hardware procurement websites. However, the two modules specifically developed for this project fail to enter this category.

One of the modules uses a DC-booster,which can raise the voltage it delivers above 100V.
However, design has limited high-voltage to specific points within the module, and to the SMA connector going to the transducer. The other pins of the module have inputs/outputs that range in the [-5V ; 5V] bracket.

During the tests that took place, the full setup, without the motor, did not use more than 170mA at 9V. The ATL3 probe, alimented at 3.3V, brought the total power envelopeto 330mA at 9V.

The difference of stimulating the transducer causeda 5mA at 9V difference.

## Calibration

If the hardware is used for measurements, please detail here how the reliability of measurements, or other hardware properties that are relevant for measurements, has been quantified and explain the results. Be clear about the processes or procedures used to compare the hardware to a standard, as well as the description of the standard calibrated against.

Detail the general procedures in place for users to calibrate their hardware before or during use. What methods can be used to relate user generated data to data from other sources?

Note: Detailed instructions belong in documentation; here, provide insight into how and why the calibration is valid.

### Subsections

### Calibration of ultrasound electrical signal processing requires a standard signal, which is difficult to provide if using a classical transducer. Moreover, due to the variety of transducers, it would be extremely difficult to obtain a standard setup and signal.A calibration tool has been built (the DAC module), based on a STM32F205 DAC. This permitted to &quot;record&quot; the calibration signal, and to simulate the behaviour of the pulser module.

Calibration of the high-voltage level on the pulser module is done using an oscilloscope.

### Finally, the gain level of the analog processing module is in the tests described below adjusted once and for all at the beginning of the experiment, to use the full range of output signal and obtain the best image possible. The level of gain can be selected, either from one input signal, or with a potentiometer, the choice between the two being made possible by a jumper.

### We encourage the use of subsections within all sections to increase clarity.A home-made phantom was used to test the first iteration of the board. It was made of a gelatin phantom, with tapioca inclusions of two types (2mm and 8mm), the medium being contained in a condom. This type of phantom does not conserve well, and was not reused for the second iteration.

## General testing

In this section, details can be provided on the testing of hardware functionalities, that are not directly essential for precision operation of the hardware in the given context (which are in turn, where applicable, handled under Calibration), such as automated movements to position the hardware, repeatability of tool exchanges, recyclability, water-tightness, weight or other possibly relevant characteristics. We encourage the authors to characterise all appropriate functionalities of the hardware, if not already described elsewhere (add reference instead). The testing should define the safe/reliable limits in which the components can be operated (e.g. step size and repeatability of linear motion, force ranges, ratio of devices with leaks when built in a workshop, etc). This will enhance the usability of the hardware or method in other contexts.General testing has been done, especially for the two modules:

- --For the pulser, the criteria of the tests were the duration of the pulse, which should match the input signals, as well as the voltage of the pulse, being set by a potentiometer. Tests were done using an oscilloscope.
- --For the analog processing unit,the DAC module allowed a standard input to be processed, and the result of the processing analysed.

General conditions of the tests were that of of a 150ns, 70V pulse for the pulser unit, with a repetition every 300us.

_  __Again: Detailed instructions belong in documentation; here, provide a summary_ _ __ instead._

# (3) Application

## Use case(s)

_Describe at least one example of an application of your hardware. This should include some evidence of output, e.g. data produced by the use of the device or a picture of other types of results. Outline how the quality control in the previous section enables the use of the hardware in this context. We encourage the inclusion of experiment results or the reference to a publication (published or to-be-published) where these results are detailed. We also encourage pointers to ongoing work._

_Note: In the spirit of openness, we require authors to provide (or link to) datasets along with the submitted graphic representations. We do not impose arbitrary limits on inclusion of data so please include sufficient empirical detail and results to ensure your data can be easily verified, analysed and clearly interpreted by the wider scientific community._

### Subsections

### We encourage the demonstration of different use cases, divided by sub-sections to guide the reader.General case

The modules can be assembled in a minimum set using power-supply, pulser control, pulser module, and data acquisition.

Setup with the first iteration, the beaglebone cape

The pulser control was realized using a Trinket Pro (point A), controlling the board (B).

@todoimage

Setup with the second iteration, the modules

@todoimage

### Testing a single element transducer

A first test was done using a single-element transducer, salvaged from a used endovaginal S-VRW77AK ultrasound probe. The transducer was moved by a basic servomotor controlled by a Trinket Pro 5V, which doubled as the controller sending the pulse commands.

Data was acquired at 5Msps with a bitscope unit (BS10). Noise kept the SNR low, but nonetheless provided a source of data, and permitted to assess the performances of the different blocks.

### Testing different a commercial transducer

The dev-kit has been tested with a ATL-3 probe found on ebay. This mechanical probe has 3 rotating transducers, a characteristic of this series of ATL probes. The ATL-3 probe connector to the transducers is extremely simple, and consists in a BNC cable. The other connector&#39;s pins may correspond to the control of the probe motor. The probe&#39;s motor was connected to a 3.3V, allowing the transducers to rotate freely in the body of the probe.

A first acquisition try took place using a bitscope micro (BS10), similarly to the previous application. However, the interval between two captures did not lead to satisfactory acquisitions. A second try was done using the PRUDAQ, a faster, real-time acquisition unit, designed as an extension of the beaglebone. The PRUDAQ was connected to the amplified envelope signal of the analog processing module, clipped at 1.4V to protect the DAQ input. 32MB were acquired,

With 32MB containing two signals encored over 16 bits each, there is 8388608 points of data, or approximately 839ms. With a pulser set at 300us intervals, we should see around 2796 lines of data, which was the case. Rebuilding the image, we could see close to 12 full images,for a framerate of 14 fps, meaning that the motor was at approximately 290rpm.

The setup was used on a ultrasound phantom, as well as on a small dice.

@todoimage

### Examples of images obtained

After converting the raw data into images, which involves cleaning the resulting signal envelope and reconstructing through scan-conversion the images, the following was obtained. For the first iteration:

@todoimage

Whereas the second iteration of the hardware, the images obtained with the PRUDAQ were as follows:

@todoimage

### Datasets

- --A small library of images obtained with the first iteration is available at : [https://github.com/kelu124/murgen-dev-kit/tree/master/software/examples](https://github.com/kelu124/murgen-dev-kit/tree/master/software/examples)
- --Full data from the phantom imaging can be found on [https://github.com/kelu124/echomods/blob/master/include/20160822/2016-08-22-Fantom.md](https://github.com/kelu124/echomods/blob/master/include/20160822/2016-08-22-Fantom.md),
- --The data corresponding to the image of the dice can be found at [https://github.com/kelu124/echomods/blob/master/include/20160814/2016-08-14-HackingAUltrasoundProbe.md](https://github.com/kelu124/echomods/blob/master/include/20160814/2016-08-14-HackingAUltrasoundProbe.md) .

## Reuse potential and adaptability

_Please describe in as much detail as possible the ways in which the hardware could be reused by other researchers both within and outside of your field. This should include the use cases for the hardware, and also details of how the hardware might be modified or extended (including how contributors should contact you) if appropriate. Refer to section &quot;Ease of build&quot; where necessary._

_Please provide your thoughts on the adaptability of the hardware design. What tools and procedures would it require for other users to modify your design without your help in order to adapt them for foreseeable or even unforeseeable use._

_Also you must include details of what support mechanisms there are in place for this hardware and software (even if there is no support or support community)._

### High speed DAC

Having worked with the DAC module enables one to be able to work on the acquisition system, based on a known-signal input. This enables repeatability of the input, contrarly to images that are usually capture using a probe on a ultrasound phantom. This DAC can go up to 2MHz, on a limited voltage range, and could be used in testing analog signals processing

### Pulser

IT is suggested that the pulser can be used in medical ultrasound image devices, but can also can be used for NDT, or for test applications. Its up to 35 MHz operating frequency and 2 ns matched delay times allow higher frequencies uses.

### Analog processing

The analogue processing module was tested for signals from 2MHz to 10MHz, with some distortion happening on the higher end of the bracket. However, it can be noted that, with the possibility to measure and control the inputs and outputs of between each processing unit, this module could possibly be used for signal demodulation.

Modification of the home-made modules

Support

# (4) Build Details

## Availability of materials and methods

_Summarise what materials have been used to construct the hardware and what methods to process the materials as well as the assembly. Provide more details or references where important materials or methods are non-standard, not globally available or produced only by one manufacturer._

Most of the modules can be sourced from usual open-hardware online suppliers. The two specific modules can either be produced with a proper surface mount equipment, or the manufacturing files sent to a fab. They may also become available through a crowdfunding platform. The HV7360 becoming obsolete, it will be necessary to find a replacement for it.

## Ease of build

Have any measures been taken in the design to make the hardware easy to build for other users e.g. reduction of parts, features in the design to make the hardware assembly more reliable?When the first iteration had 4 layers, the two newly made modules are 2-layer designs, for the sake of simplicity.

The design also relies on off-the-shelf ICs to limit the number of its components. A trade-off had to be found when some ICs were BGA ICs.

The non-custom modules can be found commercially, or built.

## Operating software and peripherals

If hardware requires software, details on the operating software and programming language - Please include minimum version compatibility. Additional system requirements, e.g. memory, disk space, processor, input or output devices.

If the hardware does not require software, detail any required supporting processes or protocols required for use.

## Dependencies

E.g. other hardware or software projects, modular components, libraries, frameworks, incl. minimum version compatibility. Explicitly state if dependencies are proprietary / closed source.

Most of the processing code is using python.

The Beaglebone module is using a

The Feather WICED module is using a

## Hardware documentation and files location:

**Archive**** for hardware documentation and build files** (required. See _Repositories_ document for criteria, DocuBricks and alternative repositories.) _Note: We require the inclusion of modifiable design files as well as a detailed documentation of the functionality of the hardware with assembly instructions. This will be assessed as part of the journal peer review process._

**Name:** The name of the archive

**Persistent identifier:** e.g. DOI, etc.

**Licence:** Open hardware license under which the documentation and files are licensed - see _Essential author information_ for more information

**Publisher:** Name of the person who deposited the documentation

**Date published:** dd/mm/yy

**Modifiable design files** (if different from above)

**Name:** The name of the emulation environment

**Persistent identifier:** e.g. DOI, handle, PURL, etc.

**Licence:** Open license under which the software is licensed here

**Publisher:** Name of the person who deposited the documentation

**Date published:** dd/mm/yy

**Software code repository** (e.g. SourceForge, GitHub etc.) (required)

**Name:** The name of the code repository

**Identifier:** The identifier (or URI) used by the repository

**Licence:** Open license under which the software is licensed

**Date published:** dd/mm/yy

### (5) Discussion

## Conclusions

Conclusions, learned lessons from design iterations, learned lessons from use cases, summary of results.

## Future Work

Further work pursued by the authors or collaborators; known issues; suggestions for others to improve on the hardware design or testing,, given what you have learned from your design iterations.This set of modules shows that ultrasound imaging can profit from a usable dev-kit. Several points in this work however have to be reviewed, if not improved. Indeed:

-1: The pulser component, the HV7360LA-G, will see its production stopped.

-2: Having only two layers on the current design may be a source of noise. Moreover, applying a RF net to the sensitive parts may be an idea.

- 3: As a proof of concept, the image is not processed in quasi-realtime, and the framerate is not up to video standards. This can be improved.

- The Pulser designs uses only two inputs, and one high voltage source. However, the chip enables more complex uses as a pulser, which can be further explored.

- The DAC speed is limited to the Msps range. Having a better resolution would help with respect to exploring higher-frequency ultrasound imaging.

- The PRUDAQ has a real-time access to the digital information, as well as a linux userspace. Further programming would enable the beaglebone plateform to be a real server and controller of the setup.

- The modules are slightly too wide for a breadboard: an effort could be done to make the pins available on a standard breadboard.

- A whole field left unexplored so far is that of the transducer. As the key sensor in the kit, it would be interesting to explore relevant technologies to develop a low-cost, good-enough transducer.

## Paper author contributions

Task (e.g. design, assembly, use cases contribution, documentation, paper writing), contribution, author name.

## Acknowledgements

Please add any relevant acknowledgements to anyone else who supported the project in which the hardware was created, but did not work directly on the hardware itself.

Please list anyone who helped to create the hardware and software (who may also not be an author of this paper), including their roles and affiliations. A huge thanks to the friends in the community for their sharing their ideas and giving their support. Thanks as well to Prof Charles and Zach to have given a try at testing the first iteration, the Hackaday community forgiving me the chance to go to the 2016 finals, the echOpen community (Farad, Benoit, Vincent, Jerome, Virginie, Emilie and the others) to have kept me motivated!

## Funding statement

If the hardware resulted from funded research please give the funder and grant number.This project has been funded by personal funds, and supported by two prizes from the hackaday 2016 contest.

## Competing interests

&quot;The authors declare that they have no competing interests.&quot;Though LJ is a founder of the echOpen&#39;s project, this work has been pursued individually,the echOpen association has no involvementwith this work. LJ is discussing the crowdfunding of these modules&#39; kits with a partner.

## References

Please enter references in the Vancouver style and include a DOI where available, citing them in the text with a number in square brackets, e.g.

[1] Piwowar, H A 2011 Who Shares? Who Doesn&#39;t? Factors Associated with Openly Archiving Raw Research Data. PLoS ONE 6(7): e18657. DOI: http://dx.doi.org/10.1371/journal.pone.0018657.

### Copyright notice

Authors who publish with this journal agree to the following terms:

Authors retain copyright and grant the journal right of first publication with the work simultaneously licensed under a [Creative Commons Attribution License](http://creativecommons.org/licenses/by/3.0/) that allows others to share the work with an acknowledgement of the work&#39;s authorship and initial publication in this journal.

Authors are able to enter into separate, additional contractual arrangements for the non-exclusive distribution of the journal&#39;s published version of the work (e.g., post it to an institutional repository or publish it in a book), with an acknowledgement of its initial publication in this journal.

By submitting this paper you agree to the terms of this Copyright Notice, which will apply to this submission if and when it is published by this journal.

 
