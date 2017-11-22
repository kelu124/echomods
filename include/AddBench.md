# Benchmarking components

The aim of this document is to reference the different articles and papers that had precious information on the components used on their respective boards. 

The different Integrated Circuits (ICs) used in these papers are listed here. In bold are the ones used in the present modules.

### HV

* MCP1661 __up to 32V__ ([31]) - mic3172
* LT3958 ([21]) -> 5V to 48V. Other include:
  * LT357 http://www.linear.com/product/LT3571
  * LT3482 is a fixed frequency current mode step-up DC/DC
* MAX5025 ([11]) - interesting setup -- https://www.maximintegrated.com/en/images/appnotes/1751/1751Fig01.gif
* __R05-100B__ ([2]) ([0]) : efficient but expensive. Going to shift to something else for tobo.alt, maybe this one..
* NMT0572SC ([19]) up to 72V --- 24, 48 and 72V V - 14€ -- seems OK
* Interessant for tobo.alt.bis - 2.60€ ! __HV9110NG__ AN-H59DB1 is a high voltage DC/DC converter for HV748 ;)  Based on HV9110NG ([30]) et AN-H59 too
* MAX1771
* TPS61170 ([10]) Boost convertor
* 1470-1353-5-ND  https://www.digikey.com/product-detail/en/xp-power/IA0524S/1470-1353-5-ND/4487734 à +-24
* LTC3813: http://cds.linear.com/docs/en/datasheet/3813fb.pdf 100V Current Mode Synchronous Step-Up Controller
* LT3032 -- +-20V output [datasheet eval board](http://www.st.com/content/ccc/resource/technical/document/data_brief/cc/f0/24/f8/8b/2b/42/53/DM00218354.pdf/files/DM00218354.pdf/jcr:content/translations/en.DM00218354.pdf)
* AN-H59DB1 is a high voltage DC/DC converter

 

### Pulsers

* LM96551 ([28])
* MAX14808 ([3]) ([9])
* TC7320  ([5]) + MD1810 ([5])
* MD1213  + TC6320 ([1])
* MD1210 + TC2320 ([8])
* __HV7360__ ([0]) and/or HV7361  ([27])  ([Application note](http://ww1.microchip.com/downloads/en/DeviceDoc/20005570A.pdf))
* LM96550 ([10]) -- ultrasound Transmit Pulser, Output pulses +-50V
* TC6320 ([25])  ([26]) ([21]) bipolar pulse
* STHV748 Quad ± 90 V, ± 2 A, 3/5 levels, high speed ultrasound pulser [Datasheet](http://www.st.com/content/ccc/resource/technical/document/datasheet/a9/7f/a3/46/99/65/42/02/CD00226856.pdf/files/CD00226856.pdf/jcr:content/translations/en.CD00226856.pdf) 22$.. ([22]) ([23]) and octal with STHV800 
* HV732DB1 High Speed ±100V 2A - interesting pulser ( http://www.mouser.com/catalog/specsheets/HV732DB1.pdf ) 

### Multiplexer / Switch

* LM96530 ([28])
* FANTASTIC : [test](http://www.prnewswire.com/news-releases/mps-launched-180v-16-channel-analog-switch-multiplexer-for-ultrasound-applications-that-requires-no-high-voltage-supplies-300427205.html)
* HV2901 ([3]) 32-output high voltage MUX chip -- differential supply of 200V. [Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/hv2901.pdf)
* TX810 ([10])
* ADG1434 SPDT or ADG333A ([17]) for MEMS  
* ADG426 (Analog multiplexer) ([17]) -- max entry at 44V [datasheet](http://www.analog.com/media/en/technical-documentation/data-sheets/ADG406_407_426.pdf)
* AD8182 ([18]) 2-to-1 multiplexers
* HV748 ([19]) - Four-Channel, High Speed, ±75V 1.25A Ultrasound Pulser
* ADG707 ([20])
* MAX4968

### TGC

* AD8332 ([8])
* __AD8331__ ([0]) ([18]) ([19])   ([25])  ([26])
* SMA231 ([21]) as LNAs
* VCA8500 ([28])

### Analog enveloppe detection

* __ADL5511__ ([0])

### Analog Front end

* AFE5808 ([3]) ([9])
* AFE5801 ([10]) -  8-Channel Variable-Gain Amplifier (VGA) With Octal High-Speed ADC (Rev. D) 
* AFE5851 ([13])
* AD9273 ([15]) : Octal LNA/VGA/AAF/ADC  and Crosspoint Switch
* AD9272-65EBZ ([16])
* AFE5818 ([21]) for the capsule
* AFE5804 
* AD9230  ([25])

### ADCs

* AD9279 ([5])
* ADC10040 ([8]) - à 20MSPS sur 10 bit
* AD9233 ([14])
* ADS826 ([17])
* ADS5517 ([21])
* AD9467  ([28])

### Amplifier

* MAX4107 ([18])

### Beamformer

* LM96570 ([4])  ([28])
* FDC1005-FDD15005 ([18])
* AD8009 ([18]) : adder


### FPGA / CPLD / DSP ...

* Spartan6 LX150 ([3])
* CycloneII2C70F672 + TMS320C6416 ([7])
* Spartan-3 ([6])
* TMS320C6416 ([5])
* TMS320C6455 ([7])
* XC3S1500L-FG320, FPGA Xilinx ([8])
* Spartan 6 LX150, Xilinx Inc. ([9])
* Altera Cyclone III FPGA ([10])
* XC5VSX35T “Virtex 5” FPGA + TMS320DM6446 + XC2C256 ([13])
* Altera EP3C10 ([14])
* Virtex-4  Xilinx  FPGA + TMs320c6455[16])
* Virtex-4 FPGA  ([17])
* XCR3064XL ([20])
* Cyclone IV, EP4CE115F29 ([21])
* CC3200 Wifi ([21]) 
* FPGA Stratix IV 70 GX ([22])
* Cyclone-V 5CGXFC7D7F31C8N  ([25])

### Phantom

* Model 040GSE, CIRS,  USA ([3])
* Model 539 Multipurpose US Phantom ([5])
* Model ATS539, ATS Laboratories ([9])

Thanks to the [Murgen project](https://github.com/kelu124/murgen-dev-kit/blob/master/worklog/bibliographie.md) for the basis of this work =) 

## Suppliers

* US-SPI ([14]): an interesting tool from LeCoeur electronics.
* http://dghtechnology.com/product/scanmate-a/
* http://www.ndt.net/forum/thread.php?admin=&forenID=0&msgID=54166&rootID=54166
* http://ntsu.net.au/software_controlled_ultrasonic_systems.html
* http://www.tribosonics.com/pages/products/small-ultrasonic-system.htm
* http://sci-hub.cc/10.1177/016173460803000104 has a nice picture of a interson pcb + xilinx

## Probes

Kretz-Technik (eg S-VRW77AK-IPx7 )


[0]: https://github.com/kelu124/echomods/ "this project :)"
[1]: https://www.duo.uio.no/bitstream/handle/10852/47813/Sharma_2015.pdf "Shatin Sharma Thesis"
[2]: https://github.com/kelu124/murgen-dev-kit "murgen"
[3]: http://ieeexplore.ieee.org/document/7329474/ "Smartphone-based portable ultrasound imaging system: Prototype implementation and evaluation 10.1109/ULTSYM.2015.0517 -- great schematics"
[4]: http://www.mdpi.com/2313-433X/1/1/193 "FPGA-Based Portable Ultrasound Scanning System with Automatic Kidney Detection doi:10.3390/jimaging1010193 "
[5]: http://ieeexplore.ieee.org/document/7140846/ "A System-on-Chip Solution for Point-of-Care Ultrasound Imaging Systems: Architecture and ASIC Implementation 10.1109/TBCAS.2015.2431272"
[6]: http://ieeexplore.ieee.org/document/6242795/ "A single FPGA-based portable ultrasound imaging system for point-of-care applications 10.1109/TUFFC.2012.2339"
[7]: http://ieeexplore.ieee.org/document/4409966/ "Single-chip solution for ultrasound imaging systems: Initial results  10.1109/ULTSYM.2007.393"
[8]: https://publications.polymtl.ca/509/1/2011_PhilippeL%C3%A9vesque.pdf "ARCHITECTURE D’UN PROCESSEUR DÉDIÉ AUX TRAITEMENTS DE SIGNAUX ULTRASONIQUES EN TEMPS RÉEL EN VUE D’UNE INTÉGRATION SUR PUCE  Philippe Levesque"
[9]: http://ieeexplore.ieee.org/document/6931891/ "A new smart probe system for a tablet PC-based point-of-care ultrasound imaging system: Feasibility study - 10.1109/ULTSYM.2014.0399"
[10]: https://courses.engr.illinois.edu/ece445/getfile.asp?id=5166 "iPhone Ultrasound, Senior Design Project, Design Review"
[11]: https://www.maximintegrated.com/en/app-notes/index.mvp/id/1751 "High-V DC-DC Converter Is Ideal for MEMS (Warning: High-Voltage Circuit)"
[12]: http://www.lecoeur-electronique.net/crbst_16.html "US-SPI Single channel ultrasonic device with SPI interface"	
[13]: https://abm-website-assets.s3.amazonaws.com/mdtmag.com/s3fs-public/legacyfiles/MDT/Articles/2011/05/May11Teardown.pdf "GE Healthcare Vscan teardown"
[14]: http://www.lecoeur-electronique.net/crbst_16.html "US-SPI at LeCoeur" 
[15]: https://github.com/20E214/uprobe "Opening a chinese probe"
[16]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5079523/ "FPGA-Based Reconfigurable Processor for Ultrafast Interlaced Ultrasound and Photoacoustic Imaging - 10.1109/TUFFC.2012.2335" 
[17]: http://sci-hub.cc/10.1109/TUFFC.2012.2351 "An FPGA-based ultrasound imaging system using capacitive micromachined ultrasonic transducers."
[18]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2330166/ "High-frequenhttp://ww1.microchip.com/downloads/en/AppNotes/AN-H59.pdfcy Ultrasound Doppler System for Biomedical Applications with a 30 MHz Linear Array"
[19]: www.mdpi.com/1424-8220/16/10/1681/pdf "Design and Implementation of an Electronic Front-End Based on Square Wave Excitation for Ultrasonic Torsional Guided Wave Viscosity Sensor"
[20]: https://www.ncbi.nlm.nih.gov/pubmed/18269987 "Experimental system Prototype of a Portable, Low-Cost, C-scan Ultrasound Imaging Device - 10.1109/TBME.2007.903517"
[21]: http://sci-hub.cc/10.1109/TMI.2017.2699973 "Development of a mechanical scanning device with high-frequency ultrasound transducer for ultrasonic capsule endoscopy"
[22]: http://ieeexplore.ieee.org/abstract/document/7728843/ "A GPU-based ultrasound Phased-Array research system for non-destructive testing 10.1109/ULTSYM.2016.7728843"
[23]: http://ieeexplore.ieee.org/abstract/document/7319210/ "ARTSENSTouch - A portable device for evaluation of carotid artery stiffness 10.1109/EMBC.2015.7319210"
[24]: http://ieeexplore.ieee.org/document/6932182/ "Design of a multiple-rail high-voltage power supply for ultrasound scanners 10.1109/ULTSYM.2014.0304"
[25]: https://www.ncbi.nlm.nih.gov/pubmed/28368803 "A delayed-excitation data acquisition method for high-frequency ultrasound imaging 10.1109/TBME.2017.2687948"
[26]: http://www.tandfonline.com/doi/abs/10.1080/10402004.2016.1146974?journalCode=utrb20 "Ultrasonic Measurement of Cylindrical Roller–Bearing Lubricant Film Distribution with Two Juxtaposed Transducers"
[27]: http://mgh-courses.ece.gatech.edu/ece6414/S17/Projects/Team8_Draft2_ECE6414_S17.pdf "A Low Power System-on-a-Chip for Ultrasonic Non-Invasive Vein Detection"
[28]: http://file.scirp.org/Html/1-7600391_58398.htm "Reconfigurable Ultrasonic Testing System Development Using Programmable Analog Front-End and Reconfigurable System-on-Chip Hardware"
[29]: http://www.st.com/content/ccc/resource/technical/document/data_brief/cc/f0/24/f8/8b/2b/42/53/DM00218354.pdf/files/DM00218354.pdf/jcr:content/translations/en.DM00218354.pdf "STHV748 eval board"
[30]: http://ww1.microchip.com/downloads/en/AppNotes/AN-H59.pdf "AN-H59DB1  High Voltage Dc/dc Converter For Supertex Ultrasound Transmitter Demoboards "


[31]: http://www.microchip.com.tw/Data_CD/Treelink%20June%2010%202016.pdf "List of DCDC boosts"

