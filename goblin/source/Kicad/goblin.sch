EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:goblin
LIBS:goblin-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Header19 K2
U 1 1 580B5463
P 750 6400
F 0 "K2" H 750 6800 60  0000 L CNN
F 1 "Header19" H 750 4700 60  0001 L CNN
F 2 "footprint:PLS_2.54mm-19" H 750 6400 60  0001 C CNN
F 3 "" H 750 6800 60  0001 C CNN
F 4 "PLS_2.54mm-19" H 750 4600 60  0001 L CNN "Comment"
	1    750  6400
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR01
U 1 1 580B5447
P 1600 5950
F 0 "#PWR01" H 1600 5700 50  0001 C CNN
F 1 "AGND" H 1600 5800 50  0000 C CNN
F 2 "" H 1600 5950 50  0000 C CNN
F 3 "" H 1600 5950 50  0000 C CNN
	1    1600 5950
	1    0    0    -1  
$EndComp
Text Label 1250 6450 0    60   ~ 0
VGA_OUT2
$Comp
L VDD_5V #PWR02
U 1 1 580B568B
P 1850 6250
F 0 "#PWR02" H 1850 6050 50  0001 C CNN
F 1 "VDD_5V" V 1850 5900 50  0000 L CNN
F 2 "" H 1850 6250 50  0000 C CNN
F 3 "" H 1850 6250 50  0000 C CNN
	1    1850 6250
	0    -1   -1   0   
$EndComp
Text Label 1250 7850 0    60   ~ 0
VGA_IN
Text Label 1250 6750 0    60   ~ 0
GAIN
Text Notes 800  10650 0    60   ~ 0
strip legend\n1  - GND\n2 - +5V\n3 - ADC IN\n4 - VGA OUT2 (Tafter transformer)\n5 - Venvelope (ADL5511 out)\n6 - 12V\n7 - Signal analog gain\n8 - -12V\n9 - Pulse plus\n10 - Pulse minus\n11 - Pulse RedPitaya (3.3V)\n12 - 18V\n13 - NewFramePulse\n14 - A1 xor PWM\n15 - A2 xor Encodeur\n16 - B1\n17 - B2\n18 - VGA_IN (after MD0100)\n19 - 3.3V\n\nPCB width (1") - 26 mm.
$Comp
L VDD_3.3V #PWR03
U 1 1 580B6CBA
P 3000 8250
F 0 "#PWR03" H 3000 8050 50  0001 C CNN
F 1 "VDD_3.3V" H 2850 8150 50  0000 L CNN
F 2 "" H 3000 8250 50  0000 C CNN
F 3 "" H 3000 8250 50  0000 C CNN
	1    3000 8250
	-1   0    0    1   
$EndComp
$Comp
L 3.3VA #PWR04
U 1 1 580B6CD1
P 4250 8250
F 0 "#PWR04" H 4250 8050 50  0001 C CNN
F 1 "3.3VA" H 4150 8150 50  0000 L CNN
F 2 "" H 4250 8250 50  0000 C CNN
F 3 "" H 4250 8250 50  0000 C CNN
	1    4250 8250
	-1   0    0    1   
$EndComp
$Comp
L AGND #PWR05
U 1 1 580B6D89
P 4700 10450
F 0 "#PWR05" H 4700 10200 50  0001 C CNN
F 1 "AGND" H 4700 10300 50  0000 C CNN
F 2 "" H 4700 10450 50  0000 C CNN
F 3 "" H 4700 10450 50  0000 C CNN
	1    4700 10450
	1    0    0    -1  
$EndComp
$Comp
L Inductor L6
U 1 1 580B6DA9
P 3400 8400
F 0 "L6" H 3350 8500 60  0000 L CNN
F 1 "Inductor" H 3200 8250 60  0001 L CNN
F 2 "footprint:SM_0805_INDUCTANCE_3D" H 3150 8550 60  0001 L CNN
F 3 "" H 3250 8650 60  0001 L CNN
F 4 "75R@100MHz" H 3200 7650 60  0001 L CNN "Value"
F 5 "Yes" H 3200 8150 60  0001 L CNN "Mounted"
F 6 "SMD EMIFIL Suppression Chip Ferrite Bead" H 3200 8050 60  0001 L CNN "Part Description"
F 7 "IND0805_MURATA_BLM21BB750SN1D" H 3200 7950 60  0001 L CNN "Part Number"
F 8 "2" H 3200 7850 60  0001 L CNN "Pin Count"
F 9 "700mA" H 3350 7850 60  0001 L CNN "Power"
F 10 "0.16R" H 3850 7850 60  0001 C CNN "Resistance"
F 11 "Yes" H 4050 7850 60  0001 L CNN "SMD"
F 12 "No" H 4250 7850 60  0001 L CNN "Socket"
F 13 "None" H 4400 7850 60  0001 L CNN "Status"
F 14 "Inductors SMD" H 3200 7750 60  0001 L CNN "Table"
F 15 "chip inductance" H 3550 7550 60  0001 C CNN "Description"
F 16 "120nH" H 3400 8350 60  0000 C CNN "Inductance"
F 17 "±25%" H 3900 7750 60  0001 L CNN "Tolerance"
F 18 "S. Jafar" H 3200 9100 60  0001 L CNN "Author"
F 19 "0805" H 3200 9000 60  0001 L CNN "Case"
F 20 "Standard" H 3500 9000 60  0001 L CNN "Component Kind"
F 21 "Standard" H 4000 9000 60  0001 L CNN "Component Type"
F 22 "1.05mm" H 3200 8900 60  0001 L CNN "Component Height"
F 23 "12/21/2015" H 3200 8800 60  0001 L CNN "CreateDate"
F 24 "12/21/2015" H 3850 8800 60  0001 L CNN "LatestRevisionDate"
F 25 "MURATA" H 3200 8700 60  0001 L CNN "Manfucaturer"
F 26 "BLM21BB750SN1D" H 3650 8700 60  0001 L CNN "Manfucaturer Part Number"
	1    3400 8400
	1    0    0    -1  
$EndComp
$Comp
L Capacitor C25
U 1 1 580B70B1
P 3800 9350
F 0 "C25" V 3700 9050 60  0000 L CNN
F 1 "Capacitor" H 3750 9100 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 3620 9680 60  0001 C CNN
F 3 "" H 3720 9780 60  0001 C CNN
F 4 "100nF" V 3950 9050 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 3750 9000 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 3750 8900 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 3750 8800 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 3750 8700 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 3750 8600 60  0001 L CNN "Published"
F 10 "Altium Limited" H 3750 8500 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 3750 8400 60  0001 L CNN "Description"
F 12 "cap0603" H 3750 8300 60  0001 L CNN "Comment"
	1    3800 9350
	0    1    1    0   
$EndComp
$Comp
L Resistor R12
U 1 1 580B72D3
P 4700 8850
F 0 "R12" H 4600 8700 60  0000 L CNN
F 1 "Resistor" H 4500 8700 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 4450 9000 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 4550 8000 60  0001 L CNN
F 4 "4k7" H 4500 7900 60  0001 L CNN "Value"
F 5 "Yes" H 4500 8600 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 4500 8500 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 4500 8400 60  0001 L CNN "Part Number"
F 8 "2" H 4500 8300 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 4650 8300 60  0001 L CNN "Power"
F 10 "Yes" H 5000 8300 60  0001 L CNN "SMD"
F 11 "No" H 5250 8300 60  0001 L CNN "Socket"
F 12 "Preffered" H 5450 8300 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 4500 8200 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 4500 8100 60  0001 L CNN "TC"
F 15 "1%" H 4700 8850 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 5250 8100 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 4500 9650 60  0001 L CNN "Author"
F 18 "1206" H 4500 9550 60  0001 L CNN "Case"
F 19 "Standard" H 4800 9550 60  0001 L CNN "Component Kind"
F 20 "Standard" H 5300 9550 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 4500 9450 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 5150 9450 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 4500 9350 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 4500 9250 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 4500 9150 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 4950 9150 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 5800 9150 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "1k1" H 4600 9000 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 4500 7800 60  0001 L CNN "Description"
	1    4700 8850
	0    1    1    0   
$EndComp
$Comp
L TrimPot P1
U 1 1 580B7465
P 4250 9350
F 0 "P1" H 4050 9200 60  0000 L CNN
F 1 "TrimPot" H 4050 8950 60  0001 L CNN
F 2 "footprint:TRIM_BOURNS_3223W" H 4000 9500 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\TRIM_BOURNS_3223W.pdf" H 4100 8250 60  0001 L CNN
F 4 "5k" H 4050 8150 60  0001 L CNN "Value"
F 5 "Yes" H 4050 8850 60  0001 L CNN "Mounted"
F 6 "11 Turns SMD Trimpot® Trimming Potentiometer (Top Adjust)" H 4050 8750 60  0001 L CNN "Part Description"
F 7 "TRIM_11T_5K_BOURNS_3223W-1-502E" H 4050 8650 60  0001 L CNN "Part Number"
F 8 "3" H 4050 8550 60  0001 L CNN "Pin Count"
F 9 "0.125W" H 4200 8550 60  0001 L CNN "Power"
F 10 "Yes" H 4550 8550 60  0001 L CNN "SMD"
F 11 "No" H 4800 8550 60  0001 L CNN "Socket"
F 12 "Potentiometers SMD" H 4050 8450 60  0001 L CNN "Table"
F 13 "±100ppm/°C" H 4050 8350 60  0001 L CNN "TC"
F 14 "±20%" H 4800 8350 60  0001 L CNN "Tolerance"
F 15 "CERN DEM JLC" H 4050 10150 60  0001 L CNN "Author"
F 16 "3223W" H 4050 10050 60  0001 L CNN "Case"
F 17 "Standard" H 4450 10050 60  0001 L CNN "Component Kind"
F 18 "Standard" H 4950 10050 60  0001 L CNN "Component Type"
F 19 "4.16mm" H 5450 10050 60  0001 L CNN "ComponentHeight"
F 20 "3/31/2011" H 4050 9950 60  0001 L CNN "CreateDate"
F 21 "12/18/2012" H 4700 9950 60  0001 L CNN "LatestRevisionDate"
F 22 "BOURNS" H 4050 9850 60  0001 L CNN "Manufacturer"
F 23 "3223W-1-502E" H 4050 9750 60  0001 L CNN "Manufacturer Part Number"
F 24 "5k" H 4200 9500 60  0000 L CNN "Comment"
F 25 "Trimming Potentiometer" H 4050 8050 60  0001 L CNN "Description"
	1    4250 9350
	0    -1   -1   0   
$EndComp
$Comp
L Resistor R13
U 1 1 580B767A
P 4700 9850
F 0 "R13" H 4600 9700 60  0000 L CNN
F 1 "Resistor" H 4500 9700 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 4450 10000 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 4550 9000 60  0001 L CNN
F 4 "4k7" H 4500 8900 60  0001 L CNN "Value"
F 5 "Yes" H 4500 9600 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 4500 9500 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 4500 9400 60  0001 L CNN "Part Number"
F 8 "2" H 4500 9300 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 4650 9300 60  0001 L CNN "Power"
F 10 "Yes" H 5000 9300 60  0001 L CNN "SMD"
F 11 "No" H 5250 9300 60  0001 L CNN "Socket"
F 12 "Preffered" H 5450 9300 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 4500 9200 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 4500 9100 60  0001 L CNN "TC"
F 15 "1%" H 4700 9850 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 5250 9100 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 4500 10650 60  0001 L CNN "Author"
F 18 "1206" H 4500 10550 60  0001 L CNN "Case"
F 19 "Standard" H 4800 10550 60  0001 L CNN "Component Kind"
F 20 "Standard" H 5300 10550 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 4500 10450 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 5150 10450 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 4500 10350 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 4500 10250 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 4500 10150 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 4950 10150 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 5800 10150 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "9k8" H 4600 10000 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 4500 8800 60  0001 L CNN "Description"
	1    4700 9850
	0    1    1    0   
$EndComp
$Comp
L Capacitor C24
U 1 1 580B79A8
P 5150 9850
F 0 "C24" V 5150 10050 60  0000 L CNN
F 1 "Capacitor" H 5100 9600 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 4970 10180 60  0001 C CNN
F 3 "" H 5070 10280 60  0001 C CNN
F 4 "1nF" V 5250 10050 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 5100 9500 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 5100 9400 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 5100 9300 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 5100 9200 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 5100 9100 60  0001 L CNN "Published"
F 10 "Altium Limited" H 5100 9000 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 5100 8900 60  0001 L CNN "Description"
F 12 "cap0603" H 5100 8800 60  0001 L CNN "Comment"
	1    5150 9850
	0    1    1    0   
$EndComp
Text Label 5300 9350 0    60   ~ 0
ADC_VREF
Text Notes 3100 10900 0    60   ~ 0
Reference voltage:  use pot, or use divider R12,R13. Exlusively
$Comp
L AGND #PWR06
U 1 1 580B9A02
P 5200 6800
F 0 "#PWR06" H 5200 6550 50  0001 C CNN
F 1 "AGND" H 5200 6650 50  0000 C CNN
F 2 "" H 5200 6800 50  0000 C CNN
F 3 "" H 5200 6800 50  0000 C CNN
	1    5200 6800
	0    1    1    0   
$EndComp
$Comp
L RF_Transformer_1 TR1
U 1 1 580B9A1D
P 5600 6500
F 0 "TR1" H 5750 6600 60  0000 L CNN
F 1 "RF_Transformer_1" H 5600 5900 60  0001 L CNN
F 2 "footprint:XFMR_MINI-CIRCUITS_KK81" H 5350 6650 60  0001 L CNN
F 3 "" H 5650 6750 60  0001 L CNN
F 4 "1:1" H 5600 5300 60  0001 L CNN "Value"
F 5 "Yes" H 5600 5800 60  0001 L CNN "Mounted"
F 6 "50 Ohms 0.015 To 300MHz RF Transformers" H 5600 5700 60  0001 L CNN "Part Description"
F 7 "XFMR_MINI-CIRCUITS_T1-6T-KK81" H 5600 5600 60  0001 L CNN "Part Number"
F 8 "5" H 5600 5500 60  0001 L CNN "Pin Count"
F 9 "Yes" H 5750 5500 60  0001 L CNN "SMD"
F 10 "No" H 6000 5500 60  0001 L CNN "Socket"
F 11 "None" H 6200 5500 60  0001 L CNN "Status"
F 12 "Transformers" H 5600 5400 60  0001 L CNN "Table"
F 13 "50 Ohm 0.015 To 300MHz RF Transformers" H 6600 5200 60  0001 C CNN "Description"
F 14 "S. Jafar" H 5600 7200 60  0001 L CNN "Author"
F 15 "Standard" H 5600 7100 60  0001 L CNN "Component Kind"
F 16 "Standard" H 6100 7100 60  0001 L CNN "Component Type"
F 17 "6.6mm" H 5600 7000 60  0001 L CNN "ComponentHeight"
F 18 "12/22/2015" H 5600 6900 60  0001 L CNN "CreateDate"
F 19 "1/10/2016" H 6250 6900 60  0001 L CNN "LatestRevisionDate"
F 20 "MINI-CIRCUITS" H 5600 6800 60  0001 L CNN "Manfucaturer"
F 21 "T1-6T-KK81" H 6300 6800 60  0001 L CNN "Manfucaturer Part Number"
	1    5600 6500
	1    0    0    -1  
$EndComp
$Comp
L Resistor R9
U 1 1 580B9B5E
P 6600 7200
F 0 "R9" H 6550 7050 60  0000 L CNN
F 1 "Resistor" H 6400 7050 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 6350 7350 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 6450 6350 60  0001 L CNN
F 4 "4k7" H 6400 6250 60  0001 L CNN "Value"
F 5 "Yes" H 6400 6950 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 6400 6850 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 6400 6750 60  0001 L CNN "Part Number"
F 8 "2" H 6400 6650 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 6550 6650 60  0001 L CNN "Power"
F 10 "Yes" H 6900 6650 60  0001 L CNN "SMD"
F 11 "No" H 7150 6650 60  0001 L CNN "Socket"
F 12 "Preffered" H 7350 6650 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 6400 6550 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 6400 6450 60  0001 L CNN "TC"
F 15 "1%" H 6600 7200 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 7150 6450 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 6400 8000 60  0001 L CNN "Author"
F 18 "1206" H 6400 7900 60  0001 L CNN "Case"
F 19 "Standard" H 6700 7900 60  0001 L CNN "Component Kind"
F 20 "Standard" H 7200 7900 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 6400 7800 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 7050 7800 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 6400 7700 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 6400 7600 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 6400 7500 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 6850 7500 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 7700 7500 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "75" H 6550 7350 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 6400 6150 60  0001 L CNN "Description"
	1    6600 7200
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR07
U 1 1 580B9CDC
P 6350 7800
F 0 "#PWR07" H 6350 7550 50  0001 C CNN
F 1 "AGND" H 6350 7650 50  0000 C CNN
F 2 "" H 6350 7800 50  0000 C CNN
F 3 "" H 6350 7800 50  0000 C CNN
	1    6350 7800
	1    0    0    -1  
$EndComp
$Comp
L Capacitor C17
U 1 1 580B9D6C
P 7000 6700
F 0 "C17" H 6950 6450 60  0000 L CNN
F 1 "Capacitor" H 6950 6450 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 6820 7030 60  0001 C CNN
F 3 "" H 6920 7130 60  0001 C CNN
F 4 "100nF" H 6850 6950 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 6950 6350 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 6950 6250 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 6950 6150 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 6950 6050 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 6950 5950 60  0001 L CNN "Published"
F 10 "Altium Limited" H 6950 5850 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 6950 5750 60  0001 L CNN "Description"
F 12 "cap0603" H 6950 5650 60  0001 L CNN "Comment"
	1    7000 6700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 6450 1700 6450
Wire Wire Line
	1150 6250 1850 6250
Wire Wire Line
	1150 6150 1250 6150
Wire Wire Line
	1250 6150 1250 5850
Wire Wire Line
	1250 5850 1600 5850
Wire Wire Line
	1600 5850 1600 5950
Wire Wire Line
	1150 6750 1700 6750
Wire Wire Line
	1150 7850 1700 7850
Wire Notes Line
	750  10700 2500 10700
Wire Notes Line
	2500 10700 2500 8500
Wire Notes Line
	2500 8500 750  8500
Wire Notes Line
	750  8500 750  10700
Wire Wire Line
	4550 9350 5750 9350
Wire Wire Line
	4700 9250 4700 9450
Connection ~ 4700 9350
Wire Wire Line
	5150 9350 5150 9650
Connection ~ 5150 9350
Wire Wire Line
	4700 10250 4700 10450
Wire Wire Line
	5150 10350 5150 10100
Wire Wire Line
	3800 10350 5150 10350
Connection ~ 4700 10350
Wire Wire Line
	4250 9750 4250 10350
Wire Wire Line
	3800 9600 3800 10350
Connection ~ 4250 10350
Wire Wire Line
	4700 8400 4700 8450
Wire Wire Line
	3750 8400 4700 8400
Wire Wire Line
	4250 8250 4250 8950
Wire Wire Line
	3000 8250 3000 8400
Wire Wire Line
	3000 8400 3050 8400
Connection ~ 4250 8400
Wire Wire Line
	3800 9150 3800 8400
Connection ~ 3800 8400
Wire Wire Line
	6250 6700 6750 6700
Wire Wire Line
	6600 6800 6600 6700
Connection ~ 6600 6700
Wire Wire Line
	6250 6900 6350 6900
Wire Wire Line
	6350 6900 6350 7800
Wire Wire Line
	6600 7600 6600 7700
Wire Wire Line
	6600 7700 6350 7700
Connection ~ 6350 7700
Wire Wire Line
	5200 6800 5400 6800
Wire Wire Line
	5400 6900 5300 6900
Wire Wire Line
	5300 6900 5300 7000
Wire Wire Line
	5300 7000 2650 7000
Wire Wire Line
	5400 6700 5300 6700
Wire Wire Line
	5300 6700 5300 6600
Wire Wire Line
	5300 6600 2750 6600
Text Notes 7250 6700 0    60   Italic 0
RF Net Class
Wire Wire Line
	7200 6700 9800 6700
Text Label 6300 6700 0    60   ~ 0
VGA_OUT2
$Comp
L Capacitor C18
U 1 1 580BA8AB
P 7350 7000
F 0 "C18" V 7350 7200 60  0000 L CNN
F 1 "Capacitor" H 7300 6750 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 7170 7330 60  0001 C CNN
F 3 "" H 7270 7430 60  0001 C CNN
F 4 "39pF" V 7450 7200 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 7300 6650 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 7300 6550 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 7300 6450 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 7300 6350 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 7300 6250 60  0001 L CNN "Published"
F 10 "Altium Limited" H 7300 6150 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 7300 6050 60  0001 L CNN "Description"
F 12 "cap0603" H 7300 5950 60  0001 L CNN "Comment"
	1    7350 7000
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR08
U 1 1 580BA95F
P 7350 7300
F 0 "#PWR08" H 7350 7050 50  0001 C CNN
F 1 "AGND" H 7350 7150 50  0000 C CNN
F 2 "" H 7350 7300 50  0000 C CNN
F 3 "" H 7350 7300 50  0000 C CNN
	1    7350 7300
	1    0    0    -1  
$EndComp
$Comp
L VDD_5V #PWR09
U 1 1 580BAAC5
P 7950 7450
F 0 "#PWR09" H 7950 7250 50  0001 C CNN
F 1 "VDD_5V" V 7950 7100 50  0000 L CNN
F 2 "" H 7950 7450 50  0000 C CNN
F 3 "" H 7950 7450 50  0000 C CNN
	1    7950 7450
	0    1    1    0   
$EndComp
$Comp
L Capacitor C19
U 1 1 580BAB31
P 8300 7150
F 0 "C19" V 8200 6850 60  0000 L CNN
F 1 "Capacitor" H 8250 6900 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 8120 7480 60  0001 C CNN
F 3 "" H 8220 7580 60  0001 C CNN
F 4 "220pF" V 8450 6850 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 8250 6800 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 8250 6700 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 8250 6600 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 8250 6500 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 8250 6400 60  0001 L CNN "Published"
F 10 "Altium Limited" H 8250 6300 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 8250 6200 60  0001 L CNN "Description"
F 12 "cap0603" H 8250 6100 60  0001 L CNN "Comment"
	1    8300 7150
	0    1    1    0   
$EndComp
$Comp
L Capacitor C20
U 1 1 580BACCF
P 8800 7150
F 0 "C20" V 8700 6850 60  0000 L CNN
F 1 "Capacitor" H 8750 6900 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 8620 7480 60  0001 C CNN
F 3 "" H 8720 7580 60  0001 C CNN
F 4 "330pF" V 8950 6850 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 8750 6800 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 8750 6700 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 8750 6600 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 8750 6500 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 8750 6400 60  0001 L CNN "Published"
F 10 "Altium Limited" H 8750 6300 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 8750 6200 60  0001 L CNN "Description"
F 12 "cap0603" H 8750 6100 60  0001 L CNN "Comment"
	1    8800 7150
	0    1    1    0   
$EndComp
$Comp
L Capacitor C21
U 1 1 580BADBB
P 9300 7150
F 0 "C21" V 9200 6850 60  0000 L CNN
F 1 "Capacitor" H 9250 6900 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 9120 7480 60  0001 C CNN
F 3 "" H 9220 7580 60  0001 C CNN
F 4 "220nF" V 9450 6850 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 9250 6800 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 9250 6700 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 9250 6600 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 9250 6500 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 9250 6400 60  0001 L CNN "Published"
F 10 "Altium Limited" H 9250 6300 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 9250 6200 60  0001 L CNN "Description"
F 12 "cap0603" H 9250 6100 60  0001 L CNN "Comment"
	1    9300 7150
	0    1    1    0   
$EndComp
$Comp
L Capacitor C22
U 1 1 580BAF40
P 8800 7700
F 0 "C22" V 8700 7400 60  0000 L CNN
F 1 "Capacitor" H 8750 7450 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 8620 8030 60  0001 C CNN
F 3 "" H 8720 8130 60  0001 C CNN
F 4 "100nF" V 8950 7400 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 8750 7350 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 8750 7250 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 8750 7150 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 8750 7050 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 8750 6950 60  0001 L CNN "Published"
F 10 "Altium Limited" H 8750 6850 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 8750 6750 60  0001 L CNN "Description"
F 12 "cap0603" H 8750 6650 60  0001 L CNN "Comment"
	1    8800 7700
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR010
U 1 1 580BB016
P 8800 8050
F 0 "#PWR010" H 8800 7800 50  0001 C CNN
F 1 "AGND" H 8800 7900 50  0000 C CNN
F 2 "" H 8800 8050 50  0000 C CNN
F 3 "" H 8800 8050 50  0000 C CNN
	1    8800 8050
	1    0    0    -1  
$EndComp
$Comp
L Capacitor C23
U 1 1 580BB0EB
P 9300 7700
F 0 "C23" V 9200 7400 60  0000 L CNN
F 1 "Capacitor" H 9250 7450 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 9120 8030 60  0001 C CNN
F 3 "" H 9220 8130 60  0001 C CNN
F 4 "100nF" V 9450 7400 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 9250 7350 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 9250 7250 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 9250 7150 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 9250 7050 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 9250 6950 60  0001 L CNN "Published"
F 10 "Altium Limited" H 9250 6850 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 9250 6750 60  0001 L CNN "Description"
F 12 "cap0603" H 9250 6650 60  0001 L CNN "Comment"
	1    9300 7700
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 7500 8800 7400
Wire Wire Line
	8800 7950 8800 8050
Wire Wire Line
	9300 7950 9300 8000
Wire Wire Line
	9600 8000 8800 8000
Connection ~ 8800 8000
Wire Wire Line
	7950 7450 9900 7450
Wire Wire Line
	9300 7400 9300 7500
Connection ~ 9300 7450
Wire Wire Line
	8300 7400 8300 7450
Connection ~ 8300 7450
Wire Wire Line
	7350 7300 7350 7250
$Comp
L ADL5511ACPZ-R7 U2
U 1 1 580BC1EE
P 10100 6500
F 0 "U2" H 10350 6650 60  0000 L CNN
F 1 "ADL5511ACPZ-R7" H 9900 4900 60  0001 L CNN
F 2 "footprint:QFN50P300X300X80-17N-S175" H 9850 6650 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\ADL5511ACPZ-R7.pdf" H 9900 4200 60  0001 L CNN
F 4 "Yes" H 9900 4800 60  0001 L CNN "Mounted"
F 5 "QFN, 0.50mm Pitch, Square; 16 Pin, 3.00mm L X 3.00mm W X 0.80mm H Body (w/Thermal Tab 1.75 X 1.75mm),  IPC Medium Density" H 9900 4700 60  0001 L CNN "PackageDescription"
F 6 "DC to 6 GHz Envelope and TruPwr RMS Detector" H 9900 4600 60  0001 L CNN "Part Description"
F 7 "ADL5511ACPZ-R7" H 9900 4500 60  0001 L CNN "Part Number"
F 8 "17" H 9900 4400 60  0001 L CNN "Pin Count"
F 9 "Yes" H 10400 4400 60  0001 L CNN "SMD"
F 10 "No" H 10650 4400 60  0001 L CNN "Socket"
F 11 "Analog & Interface" H 9900 4300 60  0001 L CNN "Table"
F 12 "CERN DEM JLC" H 9900 7300 60  0001 L CNN "Author"
F 13 "QFN16" H 9900 7200 60  0001 L CNN "Case"
F 14 "Standard" H 10300 7200 60  0001 L CNN "Component Kind"
F 15 "Standard" H 10800 7200 60  0001 L CNN "Component Type"
F 16 "0.8mm" H 11300 7200 60  0001 L CNN "ComponentHeight"
F 17 "11/15/2012" H 9900 7100 60  0001 L CNN "CreateDate"
F 18 "ADL5511ACPZ-R7" H 9900 7000 60  0001 L CNN "Device"
F 19 "11/15/2012" H 10550 7100 60  0001 L CNN "LatestRevisionDate"
F 20 "ANALOG DEVICES" H 9900 6900 60  0001 L CNN "Manufacturer"
F 21 "ADL5511ACPZ-R7" H 10750 6900 60  0001 L CNN "Manufacturer Part Number"
F 22 "ADL5511ACPZ-R7" H 10100 5150 60  0000 L CNN "Comment"
F 23 "DC to 6 GHz Envelope and TruPwr RMS Detector" H 9900 4100 60  0001 L CNN "Description"
	1    10100 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 6950 9300 6900
Wire Wire Line
	9300 6900 9550 6900
Wire Wire Line
	9550 6900 9550 7250
Wire Wire Line
	9550 7250 9900 7250
Wire Wire Line
	8800 6950 8800 6850
Wire Wire Line
	8800 6850 9600 6850
Wire Wire Line
	9600 6850 9600 7150
Wire Wire Line
	8300 6950 8300 6800
Wire Wire Line
	8300 6800 9650 6800
Wire Wire Line
	9650 6800 9650 7050
Wire Wire Line
	7350 6800 7350 6750
Wire Wire Line
	7350 6750 9700 6750
Wire Wire Line
	9700 6750 9700 6950
Wire Wire Line
	9900 7550 9600 7550
Wire Wire Line
	9600 7550 9600 8000
Connection ~ 9300 8000
Wire Wire Line
	9900 7650 9600 7650
Connection ~ 9600 7650
$Comp
L VDD_5V #PWR011
U 1 1 580BC726
P 9850 6550
F 0 "#PWR011" H 9850 6350 50  0001 C CNN
F 1 "VDD_5V" V 9850 6200 50  0000 L CNN
F 2 "" H 9850 6550 50  0000 C CNN
F 3 "" H 9850 6550 50  0000 C CNN
	1    9850 6550
	0    1    1    0   
$EndComp
Wire Wire Line
	9850 6550 9900 6550
Wire Wire Line
	9900 6750 9800 6750
Wire Wire Line
	9800 6750 9800 6700
Wire Wire Line
	9700 6950 9900 6950
Wire Wire Line
	9650 7050 9900 7050
Wire Wire Line
	9600 7150 9900 7150
$Comp
L AD8691 U3
U 1 1 580BDE6C
P 12800 6750
F 0 "U3" H 13000 6900 60  0000 L CNN
F 1 "AD8691" H 12800 6050 60  0001 L CNN
F 2 "footprint:TSOT-5(RT-5)" H 12550 6900 60  0001 L CNN
F 3 "" H 12600 4450 60  0001 L CNN
F 4 "AD8691" H 12900 6300 60  0000 L CNN "Comment"
	1    12800 6750
	1    0    0    -1  
$EndComp
$Comp
L Resistor R7
U 1 1 580BE2A9
P 12500 6250
F 0 "R7" H 12450 6100 60  0000 L CNN
F 1 "Resistor" H 12300 6100 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 12250 6400 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 12350 5400 60  0001 L CNN
F 4 "4k7" H 12300 5300 60  0001 L CNN "Value"
F 5 "Yes" H 12300 6000 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 12300 5900 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 12300 5800 60  0001 L CNN "Part Number"
F 8 "2" H 12300 5700 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 12450 5700 60  0001 L CNN "Power"
F 10 "Yes" H 12800 5700 60  0001 L CNN "SMD"
F 11 "No" H 13050 5700 60  0001 L CNN "Socket"
F 12 "Preffered" H 13250 5700 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 12300 5600 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 12300 5500 60  0001 L CNN "TC"
F 15 "1%" H 12500 6250 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 13050 5500 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 12300 7050 60  0001 L CNN "Author"
F 18 "1206" H 12300 6950 60  0001 L CNN "Case"
F 19 "Standard" H 12600 6950 60  0001 L CNN "Component Kind"
F 20 "Standard" H 13100 6950 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 12300 6850 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 12950 6850 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 12300 6750 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 12300 6650 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 12300 6550 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 12750 6550 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 13600 6550 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "13k" H 12450 6400 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 12300 5200 60  0001 L CNN "Description"
	1    12500 6250
	0    1    1    0   
$EndComp
$Comp
L Resistor R8
U 1 1 580BE5A6
P 12000 6750
F 0 "R8" H 12100 6600 60  0000 L CNN
F 1 "Resistor" H 11800 6600 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 11750 6900 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 11850 5900 60  0001 L CNN
F 4 "4k7" H 11800 5800 60  0001 L CNN "Value"
F 5 "Yes" H 11800 6500 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 11800 6400 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 11800 6300 60  0001 L CNN "Part Number"
F 8 "2" H 11800 6200 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 11950 6200 60  0001 L CNN "Power"
F 10 "Yes" H 12300 6200 60  0001 L CNN "SMD"
F 11 "No" H 12550 6200 60  0001 L CNN "Socket"
F 12 "Preffered" H 12750 6200 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 11800 6100 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 11800 6000 60  0001 L CNN "TC"
F 15 "1%" H 12000 6750 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 12550 6000 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 11800 7550 60  0001 L CNN "Author"
F 18 "1206" H 11800 7450 60  0001 L CNN "Case"
F 19 "Standard" H 12100 7450 60  0001 L CNN "Component Kind"
F 20 "Standard" H 12600 7450 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 11800 7350 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 12450 7350 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 11800 7250 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 11800 7150 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 11800 7050 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 12250 7050 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 13100 7050 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "5k1" H 11800 6600 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 11800 5700 60  0001 L CNN "Description"
	1    12000 6750
	-1   0    0    1   
$EndComp
$Comp
L Resistor R10
U 1 1 580BE929
P 12000 7050
F 0 "R10" H 12100 6900 60  0000 L CNN
F 1 "Resistor" H 11800 6900 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 11750 7200 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 11850 6200 60  0001 L CNN
F 4 "4k7" H 11800 6100 60  0001 L CNN "Value"
F 5 "Yes" H 11800 6800 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 11800 6700 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 11800 6600 60  0001 L CNN "Part Number"
F 8 "2" H 11800 6500 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 11950 6500 60  0001 L CNN "Power"
F 10 "Yes" H 12300 6500 60  0001 L CNN "SMD"
F 11 "No" H 12550 6500 60  0001 L CNN "Socket"
F 12 "Preffered" H 12750 6500 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 11800 6400 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 11800 6300 60  0001 L CNN "TC"
F 15 "1%" H 12000 7050 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 12550 6300 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 11800 7850 60  0001 L CNN "Author"
F 18 "1206" H 11800 7750 60  0001 L CNN "Case"
F 19 "Standard" H 12100 7750 60  0001 L CNN "Component Kind"
F 20 "Standard" H 12600 7750 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 11800 7650 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 12450 7650 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 11800 7550 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 11800 7450 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 11800 7350 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 12250 7350 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 13100 7350 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "5k1" H 11800 6900 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 11800 6000 60  0001 L CNN "Description"
	1    12000 7050
	-1   0    0    1   
$EndComp
$Comp
L Resistor R11
U 1 1 580BEAFB
P 13050 7550
F 0 "R11" H 13150 7400 60  0000 L CNN
F 1 "Resistor" H 12850 7400 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 12800 7700 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 12900 6700 60  0001 L CNN
F 4 "4k7" H 12850 6600 60  0001 L CNN "Value"
F 5 "Yes" H 12850 7300 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 12850 7200 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 12850 7100 60  0001 L CNN "Part Number"
F 8 "2" H 12850 7000 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 13000 7000 60  0001 L CNN "Power"
F 10 "Yes" H 13350 7000 60  0001 L CNN "SMD"
F 11 "No" H 13600 7000 60  0001 L CNN "Socket"
F 12 "Preffered" H 13800 7000 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 12850 6900 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 12850 6800 60  0001 L CNN "TC"
F 15 "1%" H 13050 7550 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 13600 6800 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 12850 8350 60  0001 L CNN "Author"
F 18 "1206" H 12850 8250 60  0001 L CNN "Case"
F 19 "Standard" H 13150 8250 60  0001 L CNN "Component Kind"
F 20 "Standard" H 13650 8250 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 12850 8150 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 13500 8150 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 12850 8050 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 12850 7950 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 12850 7850 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 13300 7850 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 14150 7850 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "13k" H 12850 7400 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 12850 6500 60  0001 L CNN "Description"
	1    13050 7550
	-1   0    0    1   
$EndComp
$Comp
L AGND #PWR012
U 1 1 580BF032
P 13850 5900
F 0 "#PWR012" H 13850 5650 50  0001 C CNN
F 1 "AGND" H 13850 5750 50  0000 C CNN
F 2 "" H 13850 5900 50  0000 C CNN
F 3 "" H 13850 5900 50  0000 C CNN
	1    13850 5900
	1    0    0    -1  
$EndComp
$Comp
L 3.3VA #PWR013
U 1 1 580BF06B
P 13600 5700
F 0 "#PWR013" H 13600 5500 50  0001 C CNN
F 1 "3.3VA" H 13450 5600 50  0000 L CNN
F 2 "" H 13600 5700 50  0000 C CNN
F 3 "" H 13600 5700 50  0000 C CNN
	1    13600 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	12500 5850 12500 5800
Wire Wire Line
	12500 5800 13850 5800
Wire Wire Line
	13700 5800 13700 7000
Wire Wire Line
	13700 7000 13550 7000
Wire Wire Line
	13550 6800 13600 6800
Wire Wire Line
	13600 6800 13600 5700
Wire Wire Line
	13850 5800 13850 5900
Connection ~ 13700 5800
Wire Wire Line
	13550 6900 13800 6900
Wire Wire Line
	13800 6900 13800 8000
Wire Wire Line
	13800 7550 13450 7550
Wire Wire Line
	12400 7050 12500 7050
Wire Wire Line
	12500 7000 12500 7550
Wire Wire Line
	12500 7000 12600 7000
Wire Wire Line
	12500 7550 12650 7550
Connection ~ 12500 7050
Wire Wire Line
	12400 6750 12500 6750
Wire Wire Line
	12500 6650 12500 6800
Wire Wire Line
	12500 6800 12600 6800
Connection ~ 12500 6750
Text Label 10950 6750 0    60   ~ 0
V_ENVELOPE
Wire Wire Line
	10850 6750 11600 6750
Wire Wire Line
	10850 6950 11500 6950
Wire Wire Line
	11500 6950 11500 7050
Wire Wire Line
	11500 7050 11600 7050
Text Notes 12100 7800 0    60   Italic 0
offset removal, gain is around 2.5
$Comp
L AD7274 U4
U 1 1 580C0524
P 12550 8350
F 0 "U4" H 12750 8500 60  0000 L CNN
F 1 "AD7274" H 12550 7650 60  0001 L CNN
F 2 "footprint:RM-8" H 12300 8500 60  0001 L CNN
F 3 "" H 12350 6050 60  0001 L CNN
F 4 "AD7274" H 12650 7800 60  0000 L CNN "Comment"
F 5 "adc serial" H 12550 7550 60  0001 L CNN "Description"
	1    12550 8350
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR014
U 1 1 580C0CA6
P 13400 9100
F 0 "#PWR014" H 13400 8850 50  0001 C CNN
F 1 "AGND" H 13400 8950 50  0000 C CNN
F 2 "" H 13400 9100 50  0000 C CNN
F 3 "" H 13400 9100 50  0000 C CNN
	1    13400 9100
	1    0    0    -1  
$EndComp
$Comp
L 3.3VA #PWR015
U 1 1 580C0CF6
P 12250 8200
F 0 "#PWR015" H 12250 8000 50  0001 C CNN
F 1 "3.3VA" H 12100 8100 50  0000 L CNN
F 2 "" H 12250 8200 50  0000 C CNN
F 3 "" H 12250 8200 50  0000 C CNN
	1    12250 8200
	-1   0    0    1   
$EndComp
$Comp
L Header6 K3
U 1 1 580C0D5F
P 14200 8550
F 0 "K3" H 14250 8950 60  0000 L CNN
F 1 "Header6" H 14200 8150 60  0001 L CNN
F 2 "footprint:Molex_89400-061" H 14200 8550 60  0001 C CNN
F 3 "" H 14200 8550 60  0001 C CNN
F 4 "6 pin vertical 2mm" H 14200 8050 60  0001 L CNN "Description"
F 5 "Molex_89400_061" H 14200 7950 60  0001 L CNN "Comment"
	1    14200 8550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	12350 8700 12250 8700
Wire Wire Line
	12250 8700 12250 9000
Wire Wire Line
	12250 9000 13700 9000
Wire Wire Line
	13400 8700 13400 9100
Wire Wire Line
	13400 8700 13300 8700
Connection ~ 13400 9000
Wire Wire Line
	12350 8400 12250 8400
Wire Wire Line
	12250 8400 12250 8200
Wire Wire Line
	12100 8600 12350 8600
Wire Wire Line
	12100 8000 12100 8600
Wire Wire Line
	13300 8600 13500 8600
Wire Wire Line
	13500 8600 13500 8800
Wire Wire Line
	13300 8500 13600 8500
Wire Wire Line
	13600 8500 13600 8600
Wire Wire Line
	13800 8300 13700 8300
Wire Wire Line
	13700 8300 13700 9000
Wire Wire Line
	13300 8400 13800 8400
Wire Wire Line
	13600 8600 13800 8600
Wire Wire Line
	13500 8800 13800 8800
Wire Wire Line
	13800 8500 13700 8500
Connection ~ 13700 8500
Wire Wire Line
	13800 8700 13700 8700
Connection ~ 13700 8700
Wire Wire Line
	13800 8000 12100 8000
Connection ~ 13800 7550
Text Label 13500 8000 0    60   ~ 0
ADC
Wire Wire Line
	12350 8500 11500 8500
Text Label 11550 8500 0    60   ~ 0
ADC_VREF
$Comp
L Inductor L2
U 1 1 580C28A5
P 6400 1500
F 0 "L2" H 6200 1600 60  0000 L CNN
F 1 "Inductor" H 6200 1350 60  0001 L CNN
F 2 "footprint:SM_0805_INDUCTANCE_3D" H 6150 1650 60  0001 L CNN
F 3 "" H 6250 1750 60  0001 L CNN
F 4 "75R@100MHz" H 6200 750 60  0001 L CNN "Value"
F 5 "Yes" H 6200 1250 60  0001 L CNN "Mounted"
F 6 "SMD EMIFIL Suppression Chip Ferrite Bead" H 6200 1150 60  0001 L CNN "Part Description"
F 7 "IND0805_MURATA_BLM21BB750SN1D" H 6200 1050 60  0001 L CNN "Part Number"
F 8 "2" H 6200 950 60  0001 L CNN "Pin Count"
F 9 "700mA" H 6350 950 60  0001 L CNN "Power"
F 10 "0.16R" H 6850 950 60  0001 C CNN "Resistance"
F 11 "Yes" H 7050 950 60  0001 L CNN "SMD"
F 12 "No" H 7250 950 60  0001 L CNN "Socket"
F 13 "None" H 7400 950 60  0001 L CNN "Status"
F 14 "Inductors SMD" H 6200 850 60  0001 L CNN "Table"
F 15 "chip inductance" H 6550 650 60  0001 C CNN "Description"
F 16 "120nH" H 6550 1600 60  0000 C CNN "Inductance"
F 17 "±25%" H 6900 850 60  0001 L CNN "Tolerance"
F 18 "S. Jafar" H 6200 2200 60  0001 L CNN "Author"
F 19 "0805" H 6200 2100 60  0001 L CNN "Case"
F 20 "Standard" H 6500 2100 60  0001 L CNN "Component Kind"
F 21 "Standard" H 7000 2100 60  0001 L CNN "Component Type"
F 22 "1.05mm" H 6200 2000 60  0001 L CNN "Component Height"
F 23 "12/21/2015" H 6200 1900 60  0001 L CNN "CreateDate"
F 24 "12/21/2015" H 6850 1900 60  0001 L CNN "LatestRevisionDate"
F 25 "MURATA" H 6200 1800 60  0001 L CNN "Manfucaturer"
F 26 "BLM21BB750SN1D" H 6650 1800 60  0001 L CNN "Manfucaturer Part Number"
	1    6400 1500
	1    0    0    -1  
$EndComp
$Comp
L Resistor R3
U 1 1 580C2A76
P 6400 1750
F 0 "R3" H 6350 1600 60  0000 L CNN
F 1 "Resistor" H 6200 1600 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 6150 1900 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 6250 900 60  0001 L CNN
F 4 "4k7" H 6200 800 60  0001 L CNN "Value"
F 5 "Yes" H 6200 1500 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 6200 1400 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 6200 1300 60  0001 L CNN "Part Number"
F 8 "2" H 6200 1200 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 6350 1200 60  0001 L CNN "Power"
F 10 "Yes" H 6700 1200 60  0001 L CNN "SMD"
F 11 "No" H 6950 1200 60  0001 L CNN "Socket"
F 12 "Preffered" H 7150 1200 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 6200 1100 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 6200 1000 60  0001 L CNN "TC"
F 15 "1%" H 6400 1750 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 6950 1000 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 6200 2550 60  0001 L CNN "Author"
F 18 "1206" H 6200 2450 60  0001 L CNN "Case"
F 19 "Standard" H 6500 2450 60  0001 L CNN "Component Kind"
F 20 "Standard" H 7000 2450 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 6200 2350 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 6850 2350 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 6200 2250 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 6200 2150 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 6200 2050 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 6650 2050 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 7500 2050 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "100" H 6300 1900 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 6200 700 60  0001 L CNN "Description"
	1    6400 1750
	-1   0    0    1   
$EndComp
$Comp
L Inductor L4
U 1 1 580C3015
P 6400 2150
F 0 "L4" H 6200 2250 60  0000 L CNN
F 1 "Inductor" H 6200 2000 60  0001 L CNN
F 2 "footprint:SM_0805_INDUCTANCE_3D" H 6150 2300 60  0001 L CNN
F 3 "" H 6250 2400 60  0001 L CNN
F 4 "75R@100MHz" H 6200 1400 60  0001 L CNN "Value"
F 5 "Yes" H 6200 1900 60  0001 L CNN "Mounted"
F 6 "SMD EMIFIL Suppression Chip Ferrite Bead" H 6200 1800 60  0001 L CNN "Part Description"
F 7 "IND0805_MURATA_BLM21BB750SN1D" H 6200 1700 60  0001 L CNN "Part Number"
F 8 "2" H 6200 1600 60  0001 L CNN "Pin Count"
F 9 "700mA" H 6350 1600 60  0001 L CNN "Power"
F 10 "0.16R" H 6850 1600 60  0001 C CNN "Resistance"
F 11 "Yes" H 7050 1600 60  0001 L CNN "SMD"
F 12 "No" H 7250 1600 60  0001 L CNN "Socket"
F 13 "None" H 7400 1600 60  0001 L CNN "Status"
F 14 "Inductors SMD" H 6200 1500 60  0001 L CNN "Table"
F 15 "chip inductance" H 6550 1300 60  0001 C CNN "Description"
F 16 "120nH" H 6550 2250 60  0000 C CNN "Inductance"
F 17 "±25%" H 6900 1500 60  0001 L CNN "Tolerance"
F 18 "S. Jafar" H 6200 2850 60  0001 L CNN "Author"
F 19 "0805" H 6200 2750 60  0001 L CNN "Case"
F 20 "Standard" H 6500 2750 60  0001 L CNN "Component Kind"
F 21 "Standard" H 7000 2750 60  0001 L CNN "Component Type"
F 22 "1.05mm" H 6200 2650 60  0001 L CNN "Component Height"
F 23 "12/21/2015" H 6200 2550 60  0001 L CNN "CreateDate"
F 24 "12/21/2015" H 6850 2550 60  0001 L CNN "LatestRevisionDate"
F 25 "MURATA" H 6200 2450 60  0001 L CNN "Manfucaturer"
F 26 "BLM21BB750SN1D" H 6650 2450 60  0001 L CNN "Manfucaturer Part Number"
	1    6400 2150
	1    0    0    -1  
$EndComp
$Comp
L Resistor R5
U 1 1 580C3168
P 6400 2400
F 0 "R5" H 6350 2250 60  0000 L CNN
F 1 "Resistor" H 6200 2250 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 6150 2550 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 6250 1550 60  0001 L CNN
F 4 "4k7" H 6200 1450 60  0001 L CNN "Value"
F 5 "Yes" H 6200 2150 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 6200 2050 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 6200 1950 60  0001 L CNN "Part Number"
F 8 "2" H 6200 1850 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 6350 1850 60  0001 L CNN "Power"
F 10 "Yes" H 6700 1850 60  0001 L CNN "SMD"
F 11 "No" H 6950 1850 60  0001 L CNN "Socket"
F 12 "Preffered" H 7150 1850 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 6200 1750 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 6200 1650 60  0001 L CNN "TC"
F 15 "1%" H 6400 2400 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 6950 1650 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 6200 3200 60  0001 L CNN "Author"
F 18 "1206" H 6200 3100 60  0001 L CNN "Case"
F 19 "Standard" H 6500 3100 60  0001 L CNN "Component Kind"
F 20 "Standard" H 7000 3100 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 6200 3000 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 6850 3000 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 6200 2900 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 6200 2800 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 6200 2700 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 6650 2700 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 7500 2700 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "100" H 6300 2550 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 6200 1350 60  0001 L CNN "Description"
	1    6400 2400
	-1   0    0    1   
$EndComp
$Comp
L Capacitor C5
U 1 1 580C32F4
P 4900 1500
F 0 "C5" H 4850 1250 60  0000 L CNN
F 1 "Capacitor" H 4850 1250 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 4720 1830 60  0001 C CNN
F 3 "" H 4820 1930 60  0001 C CNN
F 4 "100nF" H 4750 1750 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 4850 1150 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 4850 1050 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 4850 950 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 4850 850 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 4850 750 60  0001 L CNN "Published"
F 10 "Altium Limited" H 4850 650 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 4850 550 60  0001 L CNN "Description"
F 12 "cap0603" H 4850 450 60  0001 L CNN "Comment"
	1    4900 1500
	-1   0    0    1   
$EndComp
$Comp
L Capacitor C8
U 1 1 580C3527
P 4900 2400
F 0 "C8" H 4850 2150 60  0000 L CNN
F 1 "Capacitor" H 4850 2150 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 4720 2730 60  0001 C CNN
F 3 "" H 4820 2830 60  0001 C CNN
F 4 "100nF" H 4750 2650 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 4850 2050 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 4850 1950 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 4850 1850 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 4850 1750 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 4850 1650 60  0001 L CNN "Published"
F 10 "Altium Limited" H 4850 1550 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 4850 1450 60  0001 L CNN "Description"
F 12 "cap0603" H 4850 1350 60  0001 L CNN "Comment"
	1    4900 2400
	-1   0    0    1   
$EndComp
Text Notes 5200 1500 0    60   Italic 0
RF Net Class
Text Notes 5200 2400 0    60   Italic 0
RF Net Class
Text Notes 7050 1750 0    60   Italic 0
RF Net Class
Text Notes 7050 2150 0    60   Italic 0
RF Net Class
Wire Wire Line
	5100 1500 6050 1500
Wire Wire Line
	6750 1500 6950 1500
Wire Wire Line
	6950 1500 6950 1750
Wire Wire Line
	6800 1750 7800 1750
Connection ~ 6950 1750
Wire Wire Line
	6750 2150 7700 2150
Wire Wire Line
	6800 2400 6950 2400
Wire Wire Line
	6950 2400 6950 2150
Connection ~ 6950 2150
Wire Wire Line
	5100 2400 6000 2400
Wire Wire Line
	6050 2150 5900 2150
Wire Wire Line
	5900 2150 5900 2400
Connection ~ 5900 2400
Wire Wire Line
	6000 1750 5900 1750
Wire Wire Line
	5900 1750 5900 1500
Connection ~ 5900 1500
Text Notes 4000 1500 0    60   Italic 0
RF Net Class
Text Notes 4000 2400 0    60   Italic 0
RF Net Class
$Comp
L TP TP1
U 1 1 580C43EC
P 3800 1300
F 0 "TP1" H 4200 1300 60  0000 L CNN
F 1 "TP" H 3600 1150 60  0001 L CNN
F 2 "footprint:NICOMATIC_C12000B" H 3550 1450 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\NICOMATIC_C12000B.pdf" H 3600 550 60  0001 L CNN
F 4 "Yes" H 3600 1050 60  0001 L CNN "Mounted"
F 5 "SMD Test Point" H 3600 950 60  0001 L CNN "Part Description"
F 6 "NICOMATIC_C12000B" H 3600 850 60  0001 L CNN "Part Number"
F 7 "1" H 3600 750 60  0001 L CNN "Pin Count"
F 8 "Yes" H 3800 750 60  0001 L CNN "SMD"
F 9 "No" H 4050 750 60  0001 L CNN "Socket"
F 10 "None" H 4250 750 60  0001 L CNN "Status"
F 11 "Miscellaneous" H 3600 650 60  0001 L CNN "Table"
F 12 "CERN DEM JLC" H 3600 2100 60  0001 L CNN "Author"
F 13 "Test Point" H 3600 2000 60  0001 L CNN "Family"
F 14 "Standard" H 4150 2000 60  0001 L CNN "Component Kind"
F 15 "Standard" H 4650 2000 60  0001 L CNN "Component Type"
F 16 "1.5mm" H 3600 1600 60  0001 L CNN "ComponentHeight"
F 17 "3/25/2009" H 3600 1900 60  0001 L CNN "CreateDate"
F 18 "3/25/2009" H 4250 1900 60  0001 L CNN "LatestRevisionDate"
F 19 "NICOMATIC" H 3600 1800 60  0001 L CNN "Manufacturer"
F 20 "C12000B" H 3600 1700 60  0001 L CNN "Manufacturer Part Number"
F 21 "Test Point" H 4200 450 60  0001 L CNN "Comment"
F 22 "Test Point" H 3600 450 60  0001 L CNN "Description"
	1    3800 1300
	-1   0    0    1   
$EndComp
$Comp
L TP TP2
U 1 1 580C4696
P 3800 2200
F 0 "TP2" H 4200 2200 60  0000 L CNN
F 1 "TP" H 3600 2050 60  0001 L CNN
F 2 "footprint:NICOMATIC_C12000B" H 3550 2350 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\NICOMATIC_C12000B.pdf" H 3600 1450 60  0001 L CNN
F 4 "Yes" H 3600 1950 60  0001 L CNN "Mounted"
F 5 "SMD Test Point" H 3600 1850 60  0001 L CNN "Part Description"
F 6 "NICOMATIC_C12000B" H 3600 1750 60  0001 L CNN "Part Number"
F 7 "1" H 3600 1650 60  0001 L CNN "Pin Count"
F 8 "Yes" H 3800 1650 60  0001 L CNN "SMD"
F 9 "No" H 4050 1650 60  0001 L CNN "Socket"
F 10 "None" H 4250 1650 60  0001 L CNN "Status"
F 11 "Miscellaneous" H 3600 1550 60  0001 L CNN "Table"
F 12 "CERN DEM JLC" H 3600 3000 60  0001 L CNN "Author"
F 13 "Test Point" H 3600 2900 60  0001 L CNN "Family"
F 14 "Standard" H 4150 2900 60  0001 L CNN "Component Kind"
F 15 "Standard" H 4650 2900 60  0001 L CNN "Component Type"
F 16 "1.5mm" H 3600 2500 60  0001 L CNN "ComponentHeight"
F 17 "3/25/2009" H 3600 2800 60  0001 L CNN "CreateDate"
F 18 "3/25/2009" H 4250 2800 60  0001 L CNN "LatestRevisionDate"
F 19 "NICOMATIC" H 3600 2700 60  0001 L CNN "Manufacturer"
F 20 "C12000B" H 3600 2600 60  0001 L CNN "Manufacturer Part Number"
F 21 "Test Point" H 4200 1350 60  0001 L CNN "Comment"
F 22 "Test Point" H 3600 1350 60  0001 L CNN "Description"
	1    3800 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2650 1500 4650 1500
Wire Wire Line
	2750 2400 4650 2400
Text Notes 3400 1500 0    60   Italic 0
DIFFPAIR
Wire Wire Line
	3800 1300 3900 1300
Wire Wire Line
	3900 1300 3900 1500
Connection ~ 3900 1500
Text Notes 3400 2400 0    60   Italic 0
DIFFPAIR
Wire Wire Line
	3800 2200 3900 2200
Wire Wire Line
	3900 2200 3900 2400
Connection ~ 3900 2400
Text Label 2850 1500 0    60   ~ 0
VGA_OUT_N
Text Label 2850 2400 0    60   ~ 0
VGA_OUT_P
$Comp
L VDD_5V #PWR016
U 1 1 580C52B0
P 5500 2800
F 0 "#PWR016" H 5500 2600 50  0001 C CNN
F 1 "VDD_5V" V 5500 2450 50  0000 L CNN
F 2 "" H 5500 2800 50  0000 C CNN
F 3 "" H 5500 2800 50  0000 C CNN
	1    5500 2800
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR017
U 1 1 580C531B
P 9400 1950
F 0 "#PWR017" H 9400 1700 50  0001 C CNN
F 1 "AGND" H 9400 1800 50  0000 C CNN
F 2 "" H 9400 1950 50  0000 C CNN
F 3 "" H 9400 1950 50  0000 C CNN
	1    9400 1950
	-1   0    0    1   
$EndComp
$Comp
L Resistor R4
U 1 1 580C54D9
P 8900 2300
F 0 "R4" H 9000 2150 60  0000 L CNN
F 1 "Resistor" H 8700 2150 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 8650 2450 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 8750 1450 60  0001 L CNN
F 4 "4k7" H 8700 1350 60  0001 L CNN "Value"
F 5 "Yes" H 8700 2050 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 8700 1950 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 8700 1850 60  0001 L CNN "Part Number"
F 8 "2" H 8700 1750 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 8850 1750 60  0001 L CNN "Power"
F 10 "Yes" H 9200 1750 60  0001 L CNN "SMD"
F 11 "No" H 9450 1750 60  0001 L CNN "Socket"
F 12 "Preffered" H 9650 1750 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 8700 1650 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 8700 1550 60  0001 L CNN "TC"
F 15 "1%" H 8900 2300 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 9450 1550 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 8700 3100 60  0001 L CNN "Author"
F 18 "1206" H 8700 3000 60  0001 L CNN "Case"
F 19 "Standard" H 9000 3000 60  0001 L CNN "Component Kind"
F 20 "Standard" H 9500 3000 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 8700 2900 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 9350 2900 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 8700 2800 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 8700 2700 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 8700 2600 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 9150 2600 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 10000 2600 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "10k" H 8700 2150 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 8700 1250 60  0001 L CNN "Description"
	1    8900 2300
	-1   0    0    1   
$EndComp
$Comp
L TrimPot P2
U 1 1 580C5800
P 11700 3300
F 0 "P2" H 11500 3450 60  0000 L CNN
F 1 "TrimPot" H 11500 2900 60  0001 L CNN
F 2 "footprint:TRIM_BOURNS_3223W" H 11450 3450 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\TRIM_BOURNS_3223W.pdf" H 11550 2200 60  0001 L CNN
F 4 "5k" H 11500 2100 60  0001 L CNN "Value"
F 5 "Yes" H 11500 2800 60  0001 L CNN "Mounted"
F 6 "11 Turns SMD Trimpot® Trimming Potentiometer (Top Adjust)" H 11500 2700 60  0001 L CNN "Part Description"
F 7 "TRIM_11T_5K_BOURNS_3223W-1-502E" H 11500 2600 60  0001 L CNN "Part Number"
F 8 "3" H 11500 2500 60  0001 L CNN "Pin Count"
F 9 "0.125W" H 11650 2500 60  0001 L CNN "Power"
F 10 "Yes" H 12000 2500 60  0001 L CNN "SMD"
F 11 "No" H 12250 2500 60  0001 L CNN "Socket"
F 12 "Potentiometers SMD" H 11500 2400 60  0001 L CNN "Table"
F 13 "±100ppm/°C" H 11500 2300 60  0001 L CNN "TC"
F 14 "±20%" H 12250 2300 60  0001 L CNN "Tolerance"
F 15 "CERN DEM JLC" H 11500 4100 60  0001 L CNN "Author"
F 16 "3223W" H 11500 4000 60  0001 L CNN "Case"
F 17 "Standard" H 11900 4000 60  0001 L CNN "Component Kind"
F 18 "Standard" H 12400 4000 60  0001 L CNN "Component Type"
F 19 "4.16mm" H 12900 4000 60  0001 L CNN "ComponentHeight"
F 20 "3/31/2011" H 11500 3900 60  0001 L CNN "CreateDate"
F 21 "12/18/2012" H 12150 3900 60  0001 L CNN "LatestRevisionDate"
F 22 "BOURNS" H 11500 3800 60  0001 L CNN "Manufacturer"
F 23 "3223W-1-502E" H 11500 3700 60  0001 L CNN "Manufacturer Part Number"
F 24 "5k" H 11750 3450 60  0000 L CNN "Comment"
F 25 "Trimming Potentiometer" H 11500 2000 60  0001 L CNN "Description"
	1    11700 3300
	1    0    0    -1  
$EndComp
$Comp
L AD8331ARQZ U1
U 1 1 580C87F8
P 10000 2050
F 0 "U1" H 10250 2200 60  0000 L CNN
F 1 "AD8331ARQZ" H 9800 750 60  0001 L CNN
F 2 "footprint:SOP64P600X175-20N" H 9750 2200 60  0001 L CNN
F 3 "" H 9800 50  60  0001 L CNN
F 4 "Yes" H 9800 650 60  0001 L CNN "Mounted"
F 5 "SOP, 20-Leads, Body 8.66x3.91mm, Pitch 0.64mm, IPC Medium Density" H 9800 550 60  0001 L CNN "PackageDescription"
F 6 "Ultralow Noise VGAs with Preamplifier and Programmable RIN" H 9800 450 60  0001 L CNN "Part Description"
F 7 "AD8331ARQZ" H 9800 350 60  0001 L CNN "Part Number"
F 8 "20" H 9800 250 60  0001 L CNN "Pin Count"
F 9 "Yes" H 10300 250 60  0001 L CNN "SMD"
F 10 "No" H 10550 250 60  0001 L CNN "Socket"
F 11 "Analog & Interface" H 9800 150 60  0001 L CNN "Table"
F 12 "S. Jafar" H 9800 2850 60  0001 L CNN "Author"
F 13 "QSOP-20" H 9800 2750 60  0001 L CNN "Case"
F 14 "Standard" H 10300 2750 60  0001 L CNN "Component Kind"
F 15 "Standard" H 10800 2750 60  0001 L CNN "Component Type"
F 16 "1.75mm" H 11300 2750 60  0001 L CNN "ComponentHeight"
F 17 "12/20/2015" H 9800 2650 60  0001 L CNN "CreateDate"
F 18 "AD8331ARQZ" H 9800 2550 60  0001 L CNN "Device"
F 19 "1/6/2016" H 10450 2650 60  0001 L CNN "LatestRevisionDate"
F 20 "ANALOG DEVICES" H 9800 2450 60  0001 L CNN "Manufacturer"
F 21 "AD8331ARQZ" H 10650 2450 60  0001 L CNN "Manufacturer Part Number"
F 22 "AD8331ARQZ" H 10000 900 60  0000 L CNN "Comment"
	1    10000 2050
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR018
U 1 1 580C8D0D
P 9300 3850
F 0 "#PWR018" H 9300 3600 50  0001 C CNN
F 1 "AGND" H 9300 3700 50  0000 C CNN
F 2 "" H 9300 3850 50  0000 C CNN
F 3 "" H 9300 3850 50  0000 C CNN
	1    9300 3850
	1    0    0    -1  
$EndComp
$Comp
L Capacitor C15
U 1 1 580C8D90
P 9700 3350
F 0 "C15" V 9700 3550 60  0000 L CNN
F 1 "Capacitor" H 9650 3100 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 9520 3680 60  0001 C CNN
F 3 "" H 9620 3780 60  0001 C CNN
F 4 "1nF" V 9800 3550 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 9650 3000 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 9650 2900 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 9650 2800 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 9650 2700 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 9650 2600 60  0001 L CNN "Published"
F 10 "Altium Limited" H 9650 2500 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 9650 2400 60  0001 L CNN "Description"
F 12 "cap0603" H 9650 2300 60  0001 L CNN "Comment"
	1    9700 3350
	0    1    1    0   
$EndComp
$Comp
L Capacitor C14
U 1 1 580C9156
P 9000 3350
F 0 "C14" V 9000 3550 60  0000 L CNN
F 1 "Capacitor" H 8950 3100 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 8820 3680 60  0001 C CNN
F 3 "" H 8920 3780 60  0001 C CNN
F 4 "100nF" V 9100 3550 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 8950 3000 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 8950 2900 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 8950 2800 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 8950 2700 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 8950 2600 60  0001 L CNN "Published"
F 10 "Altium Limited" H 8950 2500 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 8950 2400 60  0001 L CNN "Description"
F 12 "cap0603" H 8950 2300 60  0001 L CNN "Comment"
	1    9000 3350
	0    1    1    0   
$EndComp
$Comp
L Capacitor C13
U 1 1 580C9415
P 8300 3350
F 0 "C13" V 8300 3550 60  0000 L CNN
F 1 "Capacitor" H 8250 3100 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 8120 3680 60  0001 C CNN
F 3 "" H 8220 3780 60  0001 C CNN
F 4 "100nF" V 8400 3550 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 8250 3000 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 8250 2900 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 8250 2800 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 8250 2700 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 8250 2600 60  0001 L CNN "Published"
F 10 "Altium Limited" H 8250 2500 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 8250 2400 60  0001 L CNN "Description"
F 12 "cap0603" H 8250 2300 60  0001 L CNN "Comment"
	1    8300 3350
	0    1    1    0   
$EndComp
$Comp
L Resistor R6
U 1 1 580C9586
P 7800 3350
F 0 "R6" H 7750 3200 60  0000 L CNN
F 1 "Resistor" H 7600 3200 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 7550 3500 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 7650 2500 60  0001 L CNN
F 4 "4k7" H 7600 2400 60  0001 L CNN "Value"
F 5 "Yes" H 7600 3100 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 7600 3000 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 7600 2900 60  0001 L CNN "Part Number"
F 8 "2" H 7600 2800 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 7750 2800 60  0001 L CNN "Power"
F 10 "Yes" H 8100 2800 60  0001 L CNN "SMD"
F 11 "No" H 8350 2800 60  0001 L CNN "Socket"
F 12 "Preffered" H 8550 2800 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 7600 2700 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 7600 2600 60  0001 L CNN "TC"
F 15 "1%" H 7800 3350 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 8350 2600 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 7600 4150 60  0001 L CNN "Author"
F 18 "1206" H 7600 4050 60  0001 L CNN "Case"
F 19 "Standard" H 7900 4050 60  0001 L CNN "Component Kind"
F 20 "Standard" H 8400 4050 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 7600 3950 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 8250 3950 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 7600 3850 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 7600 3750 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 7600 3650 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 8050 3650 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 8900 3650 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "11k" H 7700 3500 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 7600 2300 60  0001 L CNN "Description"
	1    7800 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 3750 7800 3800
Wire Wire Line
	7800 3800 9700 3800
Wire Wire Line
	9700 3800 9700 3600
Wire Wire Line
	9300 3850 9300 3800
Connection ~ 9300 3800
Wire Wire Line
	9000 3600 9000 3800
Connection ~ 9000 3800
Wire Wire Line
	8300 3600 8300 3800
Connection ~ 8300 3800
Wire Wire Line
	9000 3150 9000 3050
Wire Wire Line
	9000 3050 9700 3050
Wire Wire Line
	9700 3000 9700 3150
Wire Wire Line
	7800 2950 7800 2900
Wire Wire Line
	7800 2900 9800 2900
Wire Wire Line
	8300 2900 8300 3150
$Comp
L AGND #PWR019
U 1 1 580CA1BC
P 6700 3600
F 0 "#PWR019" H 6700 3350 50  0001 C CNN
F 1 "AGND" H 6700 3450 50  0000 C CNN
F 2 "" H 6700 3600 50  0000 C CNN
F 3 "" H 6700 3600 50  0000 C CNN
	1    6700 3600
	1    0    0    -1  
$EndComp
$Comp
L Capacitor C12
U 1 1 580CA1CB
P 7050 3100
F 0 "C12" V 7050 3300 60  0000 L CNN
F 1 "Capacitor" H 7000 2850 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 6870 3430 60  0001 C CNN
F 3 "" H 6970 3530 60  0001 C CNN
F 4 "100nF" V 7150 3300 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 7000 2750 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 7000 2650 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 7000 2550 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 7000 2450 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 7000 2350 60  0001 L CNN "Published"
F 10 "Altium Limited" H 7000 2250 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 7000 2150 60  0001 L CNN "Description"
F 12 "cap0603" H 7000 2050 60  0001 L CNN "Comment"
	1    7050 3100
	0    1    1    0   
$EndComp
$Comp
L Capacitor C11
U 1 1 580CA1DA
P 6350 3100
F 0 "C11" V 6350 3300 60  0000 L CNN
F 1 "Capacitor" H 6300 2850 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 6170 3430 60  0001 C CNN
F 3 "" H 6270 3530 60  0001 C CNN
F 4 "1nF" V 6450 3300 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 6300 2750 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 6300 2650 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 6300 2550 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 6300 2450 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 6300 2350 60  0001 L CNN "Published"
F 10 "Altium Limited" H 6300 2250 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 6300 2150 60  0001 L CNN "Description"
F 12 "cap0603" H 6300 2050 60  0001 L CNN "Comment"
	1    6350 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 3550 7050 3350
Wire Wire Line
	6700 3600 6700 3550
Connection ~ 6700 3550
Wire Wire Line
	6350 3350 6350 3550
Wire Wire Line
	6350 2900 6350 2800
Wire Wire Line
	6250 2800 9800 2800
Wire Wire Line
	7050 2800 7050 2900
Wire Wire Line
	6350 3550 7050 3550
$Comp
L Inductor L5
U 1 1 580CB151
P 5900 2800
F 0 "L5" H 5700 2900 60  0000 L CNN
F 1 "Inductor" H 5700 2650 60  0001 L CNN
F 2 "footprint:SM_0805_INDUCTANCE_3D" H 5650 2950 60  0001 L CNN
F 3 "" H 5750 3050 60  0001 L CNN
F 4 "75R@100MHz" H 5700 2050 60  0001 L CNN "Value"
F 5 "Yes" H 5700 2550 60  0001 L CNN "Mounted"
F 6 "SMD EMIFIL Suppression Chip Ferrite Bead" H 5700 2450 60  0001 L CNN "Part Description"
F 7 "IND0805_MURATA_BLM21BB750SN1D" H 5700 2350 60  0001 L CNN "Part Number"
F 8 "2" H 5700 2250 60  0001 L CNN "Pin Count"
F 9 "700mA" H 5850 2250 60  0001 L CNN "Power"
F 10 "0.16R" H 6350 2250 60  0001 C CNN "Resistance"
F 11 "Yes" H 6550 2250 60  0001 L CNN "SMD"
F 12 "No" H 6750 2250 60  0001 L CNN "Socket"
F 13 "None" H 6900 2250 60  0001 L CNN "Status"
F 14 "Inductors SMD" H 5700 2150 60  0001 L CNN "Table"
F 15 "chip inductance" H 6050 1950 60  0001 C CNN "Description"
F 16 "120nH" H 6050 2900 60  0000 C CNN "Inductance"
F 17 "±25%" H 6400 2150 60  0001 L CNN "Tolerance"
F 18 "S. Jafar" H 5700 3500 60  0001 L CNN "Author"
F 19 "0805" H 5700 3400 60  0001 L CNN "Case"
F 20 "Standard" H 6000 3400 60  0001 L CNN "Component Kind"
F 21 "Standard" H 6500 3400 60  0001 L CNN "Component Type"
F 22 "1.05mm" H 5700 3300 60  0001 L CNN "Component Height"
F 23 "12/21/2015" H 5700 3200 60  0001 L CNN "CreateDate"
F 24 "12/21/2015" H 6350 3200 60  0001 L CNN "LatestRevisionDate"
F 25 "MURATA" H 5700 3100 60  0001 L CNN "Manfucaturer"
F 26 "BLM21BB750SN1D" H 6150 3100 60  0001 L CNN "Manfucaturer Part Number"
	1    5900 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2800 5550 2800
Connection ~ 6350 2800
$Comp
L AGND #PWR020
U 1 1 580CC0B5
P 9700 1950
F 0 "#PWR020" H 9700 1700 50  0001 C CNN
F 1 "AGND" H 9700 1800 50  0000 C CNN
F 2 "" H 9700 1950 50  0000 C CNN
F 3 "" H 9700 1950 50  0000 C CNN
	1    9700 1950
	-1   0    0    1   
$EndComp
$Comp
L Resistor R1
U 1 1 580CC4E0
P 8400 2050
F 0 "R1" H 8500 1900 60  0000 L CNN
F 1 "Resistor" H 8200 1900 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 8150 2200 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 8250 1200 60  0001 L CNN
F 4 "4k7" H 8200 1100 60  0001 L CNN "Value"
F 5 "Yes" H 8200 1800 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 8200 1700 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 8200 1600 60  0001 L CNN "Part Number"
F 8 "2" H 8200 1500 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 8350 1500 60  0001 L CNN "Power"
F 10 "Yes" H 8700 1500 60  0001 L CNN "SMD"
F 11 "No" H 8950 1500 60  0001 L CNN "Socket"
F 12 "Preffered" H 9150 1500 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 8200 1400 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 8200 1300 60  0001 L CNN "TC"
F 15 "1%" H 8400 2050 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 8950 1300 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 8200 2850 60  0001 L CNN "Author"
F 18 "1206" H 8200 2750 60  0001 L CNN "Case"
F 19 "Standard" H 8500 2750 60  0001 L CNN "Component Kind"
F 20 "Standard" H 9000 2750 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 8200 2650 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 8850 2650 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 8200 2550 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 8200 2450 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 8200 2350 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 8650 2350 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 9500 2350 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "10k" H 8200 1900 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 8200 1000 60  0001 L CNN "Description"
	1    8400 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	9300 2300 9800 2300
Wire Wire Line
	9800 2200 9200 2200
Wire Wire Line
	9200 2200 9200 2050
Wire Wire Line
	9200 2050 8800 2050
Wire Wire Line
	8000 2050 7900 2050
Wire Wire Line
	7900 2050 7900 2800
Wire Wire Line
	9700 2800 9700 2700
Wire Wire Line
	8500 2300 7900 2300
Connection ~ 7900 2300
Wire Wire Line
	9800 2100 9700 2100
Wire Wire Line
	9700 2100 9700 1950
Wire Wire Line
	9800 2400 9400 2400
Wire Wire Line
	9400 2400 9400 1950
Wire Wire Line
	9800 2500 7800 2500
Wire Wire Line
	7700 2600 9800 2600
Connection ~ 9700 2800
Connection ~ 7050 2800
Wire Wire Line
	9700 2700 9800 2700
Connection ~ 7900 2800
Connection ~ 8300 2900
Wire Wire Line
	9800 3000 9700 3000
Connection ~ 9700 3050
Wire Wire Line
	7800 2500 7800 1750
Wire Wire Line
	7700 2150 7700 2600
$Comp
L Capacitor C1
U 1 1 580CFBF6
P 10400 1200
F 0 "C1" V 10400 1400 60  0000 L CNN
F 1 "Capacitor" H 10350 950 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 10220 1530 60  0001 C CNN
F 3 "" H 10320 1630 60  0001 C CNN
F 4 "100nF" V 10500 1400 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 10350 850 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 10350 750 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 10350 650 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 10350 550 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 10350 450 60  0001 L CNN "Published"
F 10 "Altium Limited" H 10350 350 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 10350 250 60  0001 L CNN "Description"
F 12 "cap0603" H 10350 150 60  0001 L CNN "Comment"
	1    10400 1200
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR021
U 1 1 580CFCED
P 10400 1500
F 0 "#PWR021" H 10400 1250 50  0001 C CNN
F 1 "AGND" H 10400 1350 50  0000 C CNN
F 2 "" H 10400 1500 50  0000 C CNN
F 3 "" H 10400 1500 50  0000 C CNN
	1    10400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 1500 10400 1450
Wire Wire Line
	10800 2100 10900 2100
Wire Wire Line
	10900 2100 10900 950 
Wire Wire Line
	10900 950  10400 950 
Wire Wire Line
	10400 950  10400 1000
Wire Wire Line
	10800 2600 10850 2600
Wire Wire Line
	10850 2600 10850 2900
Wire Wire Line
	10800 2900 11100 2900
$Comp
L Capacitor C16
U 1 1 580D071E
P 10850 3350
F 0 "C16" V 10850 3000 60  0000 L CNN
F 1 "Capacitor" H 10800 3100 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 10670 3680 60  0001 C CNN
F 3 "" H 10770 3780 60  0001 C CNN
F 4 "1nF" V 10950 3000 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 10800 3000 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 10800 2900 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 10800 2800 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 10800 2700 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 10800 2600 60  0001 L CNN "Published"
F 10 "Altium Limited" H 10800 2500 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 10800 2400 60  0001 L CNN "Description"
F 12 "cap0603" H 10800 2300 60  0001 L CNN "Comment"
	1    10850 3350
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR022
U 1 1 580D08B8
P 10850 3800
F 0 "#PWR022" H 10850 3550 50  0001 C CNN
F 1 "AGND" H 10850 3650 50  0000 C CNN
F 2 "" H 10850 3800 50  0000 C CNN
F 3 "" H 10850 3800 50  0000 C CNN
	1    10850 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 3600 10850 3800
Wire Wire Line
	10800 3000 11200 3000
Wire Wire Line
	10850 3000 10850 3150
Wire Wire Line
	11100 2900 11100 3700
Wire Wire Line
	11100 3700 10850 3700
Connection ~ 10850 3700
Connection ~ 10850 2900
$Comp
L Capacitor C10
U 1 1 580D12BD
P 11950 2400
F 0 "C10" V 11850 2450 60  0000 L CNN
F 1 "Capacitor" H 11900 2150 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 11770 2730 60  0001 C CNN
F 3 "" H 11870 2830 60  0001 C CNN
F 4 "100nF" V 12100 2450 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 11900 2050 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 11900 1950 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 11900 1850 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 11900 1750 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 11900 1650 60  0001 L CNN "Published"
F 10 "Altium Limited" H 11900 1550 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 11900 1450 60  0001 L CNN "Description"
F 12 "cap0603" H 11900 1350 60  0001 L CNN "Comment"
	1    11950 2400
	0    1    1    0   
$EndComp
$Comp
L Capacitor C9
U 1 1 580D14CB
P 11550 2400
F 0 "C9" V 11450 2450 60  0000 L CNN
F 1 "Capacitor" H 11500 2150 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 11370 2730 60  0001 C CNN
F 3 "" H 11470 2830 60  0001 C CNN
F 4 "100nF" V 11700 2450 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 11500 2050 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 11500 1950 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 11500 1850 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 11500 1750 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 11500 1650 60  0001 L CNN "Published"
F 10 "Altium Limited" H 11500 1550 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 11500 1450 60  0001 L CNN "Description"
F 12 "cap0603" H 11500 1350 60  0001 L CNN "Comment"
	1    11550 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	11000 2200 10800 2200
Wire Wire Line
	10800 2300 11100 2300
Wire Wire Line
	11100 2300 11100 2000
Wire Wire Line
	11200 2400 10800 2400
Wire Wire Line
	11200 1850 11200 2400
Wire Wire Line
	10800 2500 11300 2500
Wire Wire Line
	11300 2500 11300 2150
Wire Wire Line
	11300 2150 11550 2150
Wire Wire Line
	11550 2150 11550 2200
Wire Wire Line
	10800 2700 11550 2700
Wire Wire Line
	11550 2700 11550 2650
Wire Wire Line
	10800 2800 11950 2800
Wire Wire Line
	11950 2800 11950 2650
Wire Wire Line
	11200 2100 11950 2100
Wire Wire Line
	11950 2100 11950 2200
$Comp
L Resistor R2
U 1 1 580D3B33
P 11700 1850
F 0 "R2" H 11800 1700 60  0000 L CNN
F 1 "Resistor" H 11500 1700 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 11450 2000 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 11550 1000 60  0001 L CNN
F 4 "4k7" H 11500 900 60  0001 L CNN "Value"
F 5 "Yes" H 11500 1600 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 11500 1500 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 11500 1400 60  0001 L CNN "Part Number"
F 8 "2" H 11500 1300 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 11650 1300 60  0001 L CNN "Power"
F 10 "Yes" H 12000 1300 60  0001 L CNN "SMD"
F 11 "No" H 12250 1300 60  0001 L CNN "Socket"
F 12 "Preffered" H 12450 1300 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 11500 1200 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 11500 1100 60  0001 L CNN "TC"
F 15 "1%" H 11700 1850 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 12250 1100 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 11500 2650 60  0001 L CNN "Author"
F 18 "1206" H 11500 2550 60  0001 L CNN "Case"
F 19 "Standard" H 11800 2550 60  0001 L CNN "Component Kind"
F 20 "Standard" H 12300 2550 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 11500 2450 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 12150 2450 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 11500 2350 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 11500 2250 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 11500 2150 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 11950 2150 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 12800 2150 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "280" H 11500 1700 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 11500 800 60  0001 L CNN "Description"
	1    11700 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	11300 1850 11200 1850
Connection ~ 11200 2100
$Comp
L Resistor R14
U 1 1 580D45C7
P 12550 3300
F 0 "R14" H 12650 3150 60  0000 L CNN
F 1 "Resistor" H 12350 3150 60  0001 L CNN
F 2 "footprint:SM0603_3D_res" H 12300 3450 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 12400 2450 60  0001 L CNN
F 4 "4k7" H 12350 2350 60  0001 L CNN "Value"
F 5 "Yes" H 12350 3050 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 12350 2950 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 12350 2850 60  0001 L CNN "Part Number"
F 8 "2" H 12350 2750 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 12500 2750 60  0001 L CNN "Power"
F 10 "Yes" H 12850 2750 60  0001 L CNN "SMD"
F 11 "No" H 13100 2750 60  0001 L CNN "Socket"
F 12 "Preffered" H 13300 2750 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 12350 2650 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 12350 2550 60  0001 L CNN "TC"
F 15 "1%" H 12550 3300 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 13100 2550 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 12350 4100 60  0001 L CNN "Author"
F 18 "1206" H 12350 4000 60  0001 L CNN "Case"
F 19 "Standard" H 12650 4000 60  0001 L CNN "Component Kind"
F 20 "Standard" H 13150 4000 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 12350 3900 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 13000 3900 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 12350 3800 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 12350 3700 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 12350 3600 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 12800 3600 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 13650 3600 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "20k" H 12350 3150 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 12350 2250 60  0001 L CNN "Description"
	1    12550 3300
	-1   0    0    1   
$EndComp
$Comp
L VDD_5V #PWR023
U 1 1 580D51C6
P 13900 2000
F 0 "#PWR023" H 13900 1800 50  0001 C CNN
F 1 "VDD_5V" V 13900 1650 50  0000 L CNN
F 2 "" H 13900 2000 50  0000 C CNN
F 3 "" H 13900 2000 50  0000 C CNN
	1    13900 2000
	0    -1   1    0   
$EndComp
$Comp
L AGND #PWR024
U 1 1 580D51CC
P 12950 2800
F 0 "#PWR024" H 12950 2550 50  0001 C CNN
F 1 "AGND" H 12950 2650 50  0000 C CNN
F 2 "" H 12950 2800 50  0000 C CNN
F 3 "" H 12950 2800 50  0000 C CNN
	1    12950 2800
	-1   0    0    -1  
$EndComp
$Comp
L Capacitor C6
U 1 1 580D51DB
P 12600 2300
F 0 "C6" V 12500 2150 60  0000 L CNN
F 1 "Capacitor" H 12550 2050 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 12420 2630 60  0001 C CNN
F 3 "" H 12520 2730 60  0001 C CNN
F 4 "100nF" V 12750 2000 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 12550 1950 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 12550 1850 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 12550 1750 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 12550 1650 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 12550 1550 60  0001 L CNN "Published"
F 10 "Altium Limited" H 12550 1450 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 12550 1350 60  0001 L CNN "Description"
F 12 "cap0603" H 12550 1250 60  0001 L CNN "Comment"
	1    12600 2300
	0    -1   1    0   
$EndComp
$Comp
L Capacitor C7
U 1 1 580D51EA
P 13050 2300
F 0 "C7" V 12950 2150 60  0000 L CNN
F 1 "Capacitor" H 13000 2050 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 12870 2630 60  0001 C CNN
F 3 "" H 12970 2730 60  0001 C CNN
F 4 "1nF" V 13200 2100 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 13000 1950 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 13000 1850 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 13000 1750 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 13000 1650 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 13000 1550 60  0001 L CNN "Published"
F 10 "Altium Limited" H 13000 1450 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 13000 1350 60  0001 L CNN "Description"
F 12 "cap0603" H 13000 1250 60  0001 L CNN "Comment"
	1    13050 2300
	0    -1   1    0   
$EndComp
Wire Wire Line
	12600 2750 12600 2550
Wire Wire Line
	12950 2800 12950 2750
Connection ~ 12950 2750
Wire Wire Line
	13050 2750 13050 2550
Wire Wire Line
	13050 2000 13050 2100
Wire Wire Line
	11100 2000 13150 2000
Wire Wire Line
	12600 2000 12600 2100
Wire Wire Line
	12600 2750 13050 2750
$Comp
L Inductor L3
U 1 1 580D520F
P 13500 2000
F 0 "L3" H 13600 2100 60  0000 L CNN
F 1 "Inductor" H 13300 1850 60  0001 L CNN
F 2 "footprint:SM_0805_INDUCTANCE_3D" H 13250 2150 60  0001 L CNN
F 3 "" H 13350 2250 60  0001 L CNN
F 4 "75R@100MHz" H 13300 1250 60  0001 L CNN "Value"
F 5 "Yes" H 13300 1750 60  0001 L CNN "Mounted"
F 6 "SMD EMIFIL Suppression Chip Ferrite Bead" H 13300 1650 60  0001 L CNN "Part Description"
F 7 "IND0805_MURATA_BLM21BB750SN1D" H 13300 1550 60  0001 L CNN "Part Number"
F 8 "2" H 13300 1450 60  0001 L CNN "Pin Count"
F 9 "700mA" H 13450 1450 60  0001 L CNN "Power"
F 10 "0.16R" H 13950 1450 60  0001 C CNN "Resistance"
F 11 "Yes" H 14150 1450 60  0001 L CNN "SMD"
F 12 "No" H 14350 1450 60  0001 L CNN "Socket"
F 13 "None" H 14500 1450 60  0001 L CNN "Status"
F 14 "Inductors SMD" H 13300 1350 60  0001 L CNN "Table"
F 15 "chip inductance" H 13650 1150 60  0001 C CNN "Description"
F 16 "120nH" H 13400 2100 60  0000 C CNN "Inductance"
F 17 "±25%" H 14000 1350 60  0001 L CNN "Tolerance"
F 18 "S. Jafar" H 13300 2700 60  0001 L CNN "Author"
F 19 "0805" H 13300 2600 60  0001 L CNN "Case"
F 20 "Standard" H 13600 2600 60  0001 L CNN "Component Kind"
F 21 "Standard" H 14100 2600 60  0001 L CNN "Component Type"
F 22 "1.05mm" H 13300 2500 60  0001 L CNN "Component Height"
F 23 "12/21/2015" H 13300 2400 60  0001 L CNN "CreateDate"
F 24 "12/21/2015" H 13950 2400 60  0001 L CNN "LatestRevisionDate"
F 25 "MURATA" H 13300 2300 60  0001 L CNN "Manfucaturer"
F 26 "BLM21BB750SN1D" H 13750 2300 60  0001 L CNN "Manfucaturer Part Number"
	1    13500 2000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	13900 2000 13850 2000
Connection ~ 13050 2000
Connection ~ 12600 2000
Wire Wire Line
	12350 2000 12350 3050
Connection ~ 12350 2000
$Comp
L Capacitor C3
U 1 1 580D8863
P 12150 1400
F 0 "C3" V 12050 1250 60  0000 L CNN
F 1 "Capacitor" H 12100 1150 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 11970 1730 60  0001 C CNN
F 3 "" H 12070 1830 60  0001 C CNN
F 4 "18nF" V 12300 1150 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 12100 1050 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 12100 950 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 12100 850 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 12100 750 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 12100 650 60  0001 L CNN "Published"
F 10 "Altium Limited" H 12100 550 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 12100 450 60  0001 L CNN "Description"
F 12 "cap0603" H 12100 350 60  0001 L CNN "Comment"
	1    12150 1400
	0    -1   1    0   
$EndComp
Wire Wire Line
	12150 1850 12100 1850
Wire Wire Line
	12150 1650 12150 1850
$Comp
L Capacitor C4
U 1 1 580D90EF
P 12650 1400
F 0 "C4" V 12650 1600 60  0000 L CNN
F 1 "Capacitor" H 12600 1150 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 12470 1730 60  0001 C CNN
F 3 "" H 12570 1830 60  0001 C CNN
F 4 "22pF" V 12750 1600 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 12600 1050 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 12600 950 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 12600 850 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 12600 750 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 12600 650 60  0001 L CNN "Published"
F 10 "Altium Limited" H 12600 550 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 12600 450 60  0001 L CNN "Description"
F 12 "cap0603" H 12600 350 60  0001 L CNN "Comment"
	1    12650 1400
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR025
U 1 1 580D90F5
P 12650 1700
F 0 "#PWR025" H 12650 1450 50  0001 C CNN
F 1 "AGND" H 12650 1550 50  0000 C CNN
F 2 "" H 12650 1700 50  0000 C CNN
F 3 "" H 12650 1700 50  0000 C CNN
	1    12650 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	12650 1700 12650 1650
Wire Wire Line
	12650 1150 12650 1200
Wire Wire Line
	11000 2200 11000 1150
Wire Wire Line
	11000 1150 13050 1150
Wire Wire Line
	12150 1200 12150 1150
Connection ~ 12150 1150
Text Notes 11400 1150 0    60   Italic 0
RF Net Class
$Comp
L Capacitor C2
U 1 1 580DA72D
P 13300 1150
F 0 "C2" H 13250 900 60  0000 L CNN
F 1 "Capacitor" H 13250 900 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 13120 1480 60  0001 C CNN
F 3 "" H 13220 1580 60  0001 C CNN
F 4 "100nF" H 13150 1400 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 13250 800 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 13250 700 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 13250 600 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 13250 500 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 13250 400 60  0001 L CNN "Published"
F 10 "Altium Limited" H 13250 300 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 13250 200 60  0001 L CNN "Description"
F 12 "cap0603" H 13250 100 60  0001 L CNN "Comment"
	1    13300 1150
	-1   0    0    1   
$EndComp
Connection ~ 12650 1150
Text Notes 13550 1150 0    60   Italic 0
RF Net Class
Wire Wire Line
	13500 1150 14200 1150
$Comp
L Inductor L1
U 1 1 580DAF40
P 14550 1150
F 0 "L1" H 14650 1250 60  0000 L CNN
F 1 "Inductor" H 14350 1000 60  0001 L CNN
F 2 "footprint:SM_0805_INDUCTANCE_3D" H 14300 1300 60  0001 L CNN
F 3 "" H 14400 1400 60  0001 L CNN
F 4 "75R@100MHz" H 14350 400 60  0001 L CNN "Value"
F 5 "Yes" H 14350 900 60  0001 L CNN "Mounted"
F 6 "SMD EMIFIL Suppression Chip Ferrite Bead" H 14350 800 60  0001 L CNN "Part Description"
F 7 "IND0805_MURATA_BLM21BB750SN1D" H 14350 700 60  0001 L CNN "Part Number"
F 8 "2" H 14350 600 60  0001 L CNN "Pin Count"
F 9 "700mA" H 14500 600 60  0001 L CNN "Power"
F 10 "0.16R" H 15000 600 60  0001 C CNN "Resistance"
F 11 "Yes" H 15200 600 60  0001 L CNN "SMD"
F 12 "No" H 15400 600 60  0001 L CNN "Socket"
F 13 "None" H 15550 600 60  0001 L CNN "Status"
F 14 "Inductors SMD" H 14350 500 60  0001 L CNN "Table"
F 15 "chip inductance" H 14700 300 60  0001 C CNN "Description"
F 16 "120nH" H 14450 1250 60  0000 C CNN "Inductance"
F 17 "±25%" H 15050 500 60  0001 L CNN "Tolerance"
F 18 "S. Jafar" H 14350 1850 60  0001 L CNN "Author"
F 19 "0805" H 14350 1750 60  0001 L CNN "Case"
F 20 "Standard" H 14650 1750 60  0001 L CNN "Component Kind"
F 21 "Standard" H 15150 1750 60  0001 L CNN "Component Type"
F 22 "1.05mm" H 14350 1650 60  0001 L CNN "Component Height"
F 23 "12/21/2015" H 14350 1550 60  0001 L CNN "CreateDate"
F 24 "12/21/2015" H 15000 1550 60  0001 L CNN "LatestRevisionDate"
F 25 "MURATA" H 14350 1450 60  0001 L CNN "Manfucaturer"
F 26 "BLM21BB750SN1D" H 14800 1450 60  0001 L CNN "Manfucaturer Part Number"
	1    14550 1150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	11200 3000 11200 3800
Wire Wire Line
	11200 3800 12650 3800
Connection ~ 10850 3000
Wire Wire Line
	11300 3300 11100 3300
Connection ~ 11100 3300
Wire Wire Line
	12100 3300 12150 3300
Wire Wire Line
	12950 3300 13050 3300
Wire Wire Line
	13050 3300 13050 3050
Wire Wire Line
	13050 3050 12350 3050
$Comp
L AGND #PWR026
U 1 1 580DF4F5
P 15150 1300
F 0 "#PWR026" H 15150 1050 50  0001 C CNN
F 1 "AGND" H 15150 1150 50  0000 C CNN
F 2 "" H 15150 1300 50  0000 C CNN
F 3 "" H 15150 1300 50  0000 C CNN
	1    15150 1300
	1    0    0    -1  
$EndComp
$Comp
L SMA J1
U 1 1 580DF572
P 15400 1100
F 0 "J1" H 15500 1050 60  0000 L CNN
F 1 "SMA" H 15200 800 60  0001 L CNN
F 2 "footprint:AMPHENOL_132357-11" H 15150 1250 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\AMPHENOL_132357-11.pdf" H 15200 200 60  0001 L CNN
F 4 "Yes" H 15200 700 60  0001 L CNN "Mounted"
F 5 "SMA End Launch Jack for 1.58mm PCB, 50 Ohm, Flat Tab Contact" H 15200 600 60  0001 L CNN "Part Description"
F 6 "AMPHENOL_132357-11" H 15200 500 60  0001 L CNN "Part Number"
F 7 "2" H 15200 400 60  0001 L CNN "Pin Count"
F 8 "No" H 15950 400 60  0001 L CNN "Socket"
F 9 "None" H 15200 1550 60  0001 L CNN "Status"
F 10 "AMPHENOL" H 15200 300 60  0001 L CNN "Table"
F 11 "Yes" H 15700 400 60  0001 L CNN "SMD"
F 12 "CERN DEM JLC" H 15200 1650 60  0001 L CNN "Author"
F 13 "SMA" H 17200 3000 60  0001 L CNN "Family"
F 14 "5/14/2012" H 15850 1450 60  0001 L CNN "LatestRevisionDate"
F 15 "AMPHENOL" H 15200 1350 60  0001 L CNN "Manufacturer"
F 16 "132357-11" H 16050 1350 60  0001 L CNN "Manufacturer Part Number"
F 17 "Standard" H 15600 1550 60  0001 L CNN "Component Kind"
F 18 "SMA" H 15800 300 60  0001 L CNN "Comment"
F 19 "Standard" H 16100 1550 60  0001 L CNN "Component Type"
F 20 "7.92mm" H 16600 1550 60  0001 L CNN "ComponentHeight"
F 21 "5/14/2012" H 15200 1450 60  0001 L CNN "CreateDate"
	1    15400 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	15150 1300 15150 1250
Wire Wire Line
	15150 1250 15200 1250
$Comp
L Jumper Jumper1
U 1 1 580DFCF2
P 14900 1950
F 0 "Jumper1" V 15250 1600 60  0000 L CNN
F 1 "Jumper" H 14700 1500 60  0001 L CNN
F 2 "footprint:SULLINS_GRPB031VWVN" H 14650 2100 60  0001 L CNN
F 3 "" H 14700 900 60  0001 L CNN
F 4 "Yes" H 14700 1400 60  0001 L CNN "Mounted"
F 5 "3 Contact 0.5\" Pitch Single-In-Line Vertical Header" H 14700 1300 60  0001 L CNN "Part Description"
F 6 "SULLINS_GRPB031VWVN" H 14700 1200 60  0001 L CNN "Part Number"
F 7 "3" H 14700 1100 60  0001 L CNN "Pin Count"
F 8 "No" H 15200 1100 60  0001 L CNN "SMD"
F 9 "None" H 14700 2400 60  0001 L CNN "Status"
F 10 "Miscellaneous" H 14700 1000 60  0001 L CNN "Table"
F 11 "No" H 15450 1100 60  0001 L CNN "Socket"
F 12 "S. Jafar" H 14700 2500 60  0001 L CNN "Author"
F 13 "Standard" H 15100 2400 60  0001 L CNN "Component Kind"
F 14 "Standard" H 15600 2400 60  0001 L CNN "Component Type"
F 15 "4mm" H 16100 2400 60  0001 L CNN "ComponentHeight"
F 16 "12/29/2015" H 14700 2300 60  0001 L CNN "CreateDate"
F 17 "12/29/2015" H 15350 2300 60  0001 L CNN "LatestRevisionDate"
F 18 "SULLINS" H 14700 2200 60  0001 L CNN "Manufacturer"
F 19 "GRPB031VWVN" H 15550 2200 60  0001 L CNN "Manufacturer Part Number"
F 20 "Connector 3 Male" H 14700 900 60  0001 L CNN "Description"
	1    14900 1950
	0    -1   1    0   
$EndComp
Wire Wire Line
	15150 1750 15150 1550
Wire Wire Line
	15150 1550 14950 1550
Wire Wire Line
	14950 1150 14950 1750
Wire Wire Line
	15050 1750 15050 1650
Wire Wire Line
	15050 1650 15600 1650
Wire Wire Line
	14900 1150 15200 1150
Connection ~ 14950 1150
Connection ~ 14950 1550
Text Label 15250 1650 0    60   ~ 0
VGA_IN
Text Notes 15300 1000 0    60   ~ 0
"VGA_IN"
$Comp
L Jumper Jumper2
U 1 1 580E10D2
P 12850 3950
F 0 "Jumper2" V 13200 3600 60  0000 L CNN
F 1 "Jumper" H 12650 3500 60  0001 L CNN
F 2 "footprint:SULLINS_GRPB031VWVN" H 12600 4100 60  0001 L CNN
F 3 "" H 12650 2900 60  0001 L CNN
F 4 "Yes" H 12650 3400 60  0001 L CNN "Mounted"
F 5 "3 Contact 0.5\" Pitch Single-In-Line Vertical Header" H 12650 3300 60  0001 L CNN "Part Description"
F 6 "SULLINS_GRPB031VWVN" H 12650 3200 60  0001 L CNN "Part Number"
F 7 "3" H 12650 3100 60  0001 L CNN "Pin Count"
F 8 "No" H 13150 3100 60  0001 L CNN "SMD"
F 9 "None" H 12650 4400 60  0001 L CNN "Status"
F 10 "Miscellaneous" H 12650 3000 60  0001 L CNN "Table"
F 11 "No" H 13400 3100 60  0001 L CNN "Socket"
F 12 "S. Jafar" H 12650 4500 60  0001 L CNN "Author"
F 13 "Standard" H 13050 4400 60  0001 L CNN "Component Kind"
F 14 "Standard" H 13550 4400 60  0001 L CNN "Component Type"
F 15 "4mm" H 14050 4400 60  0001 L CNN "ComponentHeight"
F 16 "12/29/2015" H 12650 4300 60  0001 L CNN "CreateDate"
F 17 "12/29/2015" H 13300 4300 60  0001 L CNN "LatestRevisionDate"
F 18 "SULLINS" H 12650 4200 60  0001 L CNN "Manufacturer"
F 19 "GRPB031VWVN" H 13500 4200 60  0001 L CNN "Manufacturer Part Number"
F 20 "Connector 3 Male" H 12650 2900 60  0001 L CNN "Description"
	1    12850 3950
	1    0    0    1   
$EndComp
Wire Wire Line
	11700 3600 11700 3700
Wire Wire Line
	11700 3700 12650 3700
Wire Wire Line
	12650 3900 12300 3900
Wire Wire Line
	12300 3900 12300 4150
Wire Wire Line
	12300 4150 12650 4150
Text Label 12400 4150 0    60   ~ 0
GAIN
$Comp
L Header19 K1
U 1 1 580E312A
P 15750 3650
F 0 "K1" H 15750 4050 60  0000 L CNN
F 1 "Header19" H 15750 1950 60  0001 L CNN
F 2 "footprint:PLS_2.54mm-19" H 15750 3650 60  0001 C CNN
F 3 "" H 15750 4050 60  0001 C CNN
F 4 "PLS_2.54mm-19" H 15750 1850 60  0001 L CNN "Comment"
	1    15750 3650
	-1   0    0    -1  
$EndComp
Text Label 14750 3600 0    60   ~ 0
ADC
Text Label 14750 3800 0    60   ~ 0
V_ENVELOPE
Wire Wire Line
	15350 3600 14700 3600
Wire Wire Line
	15350 3800 14700 3800
$Comp
L VDD_3.3V #PWR027
U 1 1 580E47DE
P 15150 5200
F 0 "#PWR027" H 15150 5000 50  0001 C CNN
F 1 "VDD_3.3V" V 15150 4750 50  0000 L CNN
F 2 "" H 15150 5200 50  0000 C CNN
F 3 "" H 15150 5200 50  0000 C CNN
	1    15150 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	15150 5200 15350 5200
Wire Wire Line
	2750 6600 2750 2400
Wire Wire Line
	2650 7000 2650 1500
$EndSCHEMATC
