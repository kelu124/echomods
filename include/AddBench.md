# Benchmarking components


### HV

* R05-100B [2] [0]
* MAX1771
* TPS61170 [10] Boost convertor
* MAX5025 [11] - interesting setup
* NMT0572SC [19] up to 72V

### Pulsers

* MAX14808 [3] [9]
* TC7320  [5] + MD1810 [5]
* MD1213  + TC6320 [1]
* MD1210 + TC2320 [8]
* HV7360 [0]
* LM96550 [10]

### Multiplexer / Switch

* HV2901 [3] 32-output high voltage MUX chip 
* TX810 [10]
* ADG1434 SPDT or ADG333A [17] for MEMS  
* ADG426 (Analog multiplexer) [17]
* AD8182 [18] 2-to-1 multiplexers
* HV748 [19]

### TGC

* AD8332 [8]
* AD8331 [0] [18] [19] 

### Enveloppe detection

* ADL5511 [0]

### Analog Front end

* AFE5808 [3] [9]
* AFE5801 [10]
* AFE5851 [13]
* AD9273 [15]
* AD9272-65EBZ [16]

### ADCs

* AD9279 [5]
* ADC10040 [8]
* AD9233 [14]
* ADS826 [17]

### Amplifier

* MAX4107 [18]

### Beamformer

* LM96570 [4]
* FDC1005-FDD15005 [18]
* AD8009 [18] : adder

### FPGA 

* Spartan6 LX150 [3]
* CycloneII2C70F672 + TMS320C6416 [7]
* Spartan-3 [6]
* TMS320C6416 [5]
* TMS320C6455 [7]
* XC3S1500L-FG320, FPGA Xilinx [8]
* Spartan 6 LX150, Xilinx Inc. [9]
* Altera Cyclone III FPGA [10]
* XC5VSX35T “Virtex 5” FPGA + TMS320DM6446 + XC2C256 [13]
* Altera EP3C10 [14]
* Virtex-4  Xilinx  FPGA + TMs320c6455[16]
* Virtex-4 FPGa  [17]

### Phantom

* Model 040GSE, CIRS,  USA [3]
* Model 539 Multipurpose US Phantom [5]
* ATS539.    ATS    Laboratories [9]

Thanks to the [Murgen project](https://github.com/kelu124/murgen-dev-kit/blob/master/worklog/bibliographie.md) for the basis of this work =) 

## Suppliers

* US-SPI [14]
* http://dghtechnology.com/product/scanmate-a/
* http://www.ndt.net/forum/thread.php?admin=&forenID=0&msgID=54166&rootID=54166
* http://ntsu.net.au/software_controlled_ultrasonic_systems.html
* http://www.tribosonics.com/pages/products/small-ultrasonic-system.htm

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
[18]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2330166/ "High-frequency Ultrasound Doppler System for Biomedical Applications with a 30 MHz Linear Array"
[19]: www.mdpi.com/1424-8220/16/10/1681/pdf "Design and Implementation of an Electronic Front-End Based on Square Wave Excitation for Ultrasonic Torsional Guided Wave Viscosity Sensor"
