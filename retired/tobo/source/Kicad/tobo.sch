EESchema Schematic File Version 2
LIBS:tobo-rescue
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
LIBS:tobo
LIBS:tobo-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
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
L Header19 K1
U 1 1 580B5463
P 650 1300
F 0 "K1" H 650 1700 60  0000 L CNN
F 1 "Header19" H 650 -400 60  0001 L CNN
F 2 "footprint:PLS_2.54mm-19" H 650 1300 60  0001 C CNN
F 3 "" H 650 1700 60  0001 C CNN
F 4 "PLS_2.54mm-19" H 650 -500 60  0001 L CNN "Comment"
	1    650  1300
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR01
U 1 1 580B5447
P 1500 850
F 0 "#PWR01" H 1500 600 50  0001 C CNN
F 1 "AGND" H 1500 700 50  0000 C CNN
F 2 "" H 1500 850 50  0000 C CNN
F 3 "" H 1500 850 50  0000 C CNN
	1    1500 850 
	1    0    0    -1  
$EndComp
$Comp
L VDD_5V #PWR02
U 1 1 580B568B
P 1750 1150
F 0 "#PWR02" H 1750 950 50  0001 C CNN
F 1 "VDD_5V" V 1750 800 50  0000 L CNN
F 2 "" H 1750 1150 50  0000 C CNN
F 3 "" H 1750 1150 50  0000 C CNN
	1    1750 1150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 1150 1750 1150
Wire Wire Line
	1050 1050 1150 1050
Wire Wire Line
	1150 1050 1150 750 
Wire Wire Line
	1150 750  1500 750 
Wire Wire Line
	1500 750  1500 850 
$Comp
L SMA J2
U 1 1 580DF572
P 9450 3800
F 0 "J2" H 9550 3750 60  0000 L CNN
F 1 "SMA" H 9250 3500 60  0001 L CNN
F 2 "footprint:AMPHENOL_132357-11" H 9200 3950 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\AMPHENOL_132357-11.pdf" H 9250 2900 60  0001 L CNN
F 4 "Yes" H 9250 3400 60  0001 L CNN "Mounted"
F 5 "SMA End Launch Jack for 1.58mm PCB, 50 Ohm, Flat Tab Contact" H 9250 3300 60  0001 L CNN "Part Description"
F 6 "AMPHENOL_132357-11" H 9250 3200 60  0001 L CNN "Part Number"
F 7 "2" H 9250 3100 60  0001 L CNN "Pin Count"
F 8 "No" H 10000 3100 60  0001 L CNN "Socket"
F 9 "None" H 9250 4250 60  0001 L CNN "Status"
F 10 "AMPHENOL" H 9250 3000 60  0001 L CNN "Table"
F 11 "Yes" H 9750 3100 60  0001 L CNN "SMD"
F 12 "CERN DEM JLC" H 9250 4350 60  0001 L CNN "Author"
F 13 "SMA" H 11250 5700 60  0001 L CNN "Family"
F 14 "5/14/2012" H 9900 4150 60  0001 L CNN "LatestRevisionDate"
F 15 "AMPHENOL" H 9250 4050 60  0001 L CNN "Manufacturer"
F 16 "132357-11" H 10100 4050 60  0001 L CNN "Manufacturer Part Number"
F 17 "Standard" H 9650 4250 60  0001 L CNN "Component Kind"
F 18 "SMA" H 9850 3000 60  0001 L CNN "Comment"
F 19 "Standard" H 10150 4250 60  0001 L CNN "Component Type"
F 20 "7.92mm" H 10650 4250 60  0001 L CNN "ComponentHeight"
F 21 "5/14/2012" H 9250 4150 60  0001 L CNN "CreateDate"
	1    9450 3800
	1    0    0    -1  
$EndComp
$Comp
L Header19 K2
U 1 1 580E312A
P 10650 4200
F 0 "K2" H 10650 4600 60  0000 L CNN
F 1 "Header19" H 10650 2500 60  0001 L CNN
F 2 "footprint:PLS_2.54mm-19" H 10650 4200 60  0001 C CNN
F 3 "" H 10650 4600 60  0001 C CNN
F 4 "PLS_2.54mm-19" H 10650 2400 60  0001 L CNN "Comment"
	1    10650 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1050 1850 3800 1850
Wire Wire Line
	1050 1950 3800 1950
Text Label 1150 1850 0    60   ~ 0
PULSE_A
Text Label 1150 1950 0    60   ~ 0
PULSE_B
Wire Notes Line
	8900 650  8900 2850
Wire Notes Line
	10800 650  8900 650 
Wire Notes Line
	10800 2850 10800 650 
Wire Notes Line
	8900 2850 10800 2850
Text Notes 8950 2800 0    60   ~ 0
strip legend\n1  - GND\n2 - +5V\n3 - VGA  OUT1 (AAD8331)\n4 - VGA OUT2 (TPx after transformer)\n5 - demodulated (ADL5511 out)\n6 - 12V\n7 - Signal analog gain\n8 - -12V\n9 - Pulse plus\n10 - Pulse minus\n11 - Pulse RedPitaya (3.3V)\n12 - 18V\n13 - NewFramePulse\n14 - A1 xor PWM\n15 - A2 xor Encodeur\n16 - B1\n17 - B2\n18 - VGA_IN (after MD0100)\n19 - 3.3V\n\nPCB width (1") - 26 mm.
$Comp
L Capacitor C1
U 1 1 5812E03E
P 3150 1250
F 0 "C1" H 3100 1000 60  0000 L CNN
F 1 "Capacitor" H 3100 1000 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 2970 1580 60  0001 C CNN
F 3 "" H 3070 1680 60  0001 C CNN
F 4 "100nF" H 3000 1500 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 3100 900 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 3100 800 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 3100 700 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 3100 600 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 3100 500 60  0001 L CNN "Published"
F 10 "Altium Limited" H 3100 400 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 3100 300 60  0001 L CNN "Description"
F 12 "cap0603" H 3100 200 60  0001 L CNN "Comment"
	1    3150 1250
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR03
U 1 1 5812E18E
P 3150 1550
F 0 "#PWR03" H 3150 1300 50  0001 C CNN
F 1 "AGND" H 3150 1400 50  0000 C CNN
F 2 "" H 3150 1550 50  0000 C CNN
F 3 "" H 3150 1550 50  0000 C CNN
	1    3150 1550
	1    0    0    -1  
$EndComp
$Comp
L VDD_5V #PWR04
U 1 1 5812E23E
P 3050 950
F 0 "#PWR04" H 3050 750 50  0001 C CNN
F 1 "VDD_5V" V 3050 600 50  0000 L CNN
F 2 "" H 3050 950 50  0000 C CNN
F 3 "" H 3050 950 50  0000 C CNN
	1    3050 950 
	0    1    1    0   
$EndComp
$Comp
L HV7360LA-G IC2
U 1 1 5812E6F5
P 4000 1500
F 0 "IC2" H 4250 1650 60  0000 L CNN
F 1 "HV7360LA-G" H 3800 -200 60  0001 L CNN
F 2 "BGA22C50P9X14_500X700X105" H 4650 2000 60  0001 L CNN
F 3 "" H 3800 -900 60  0001 L CNN
F 4 "Yes" H 3800 -300 60  0001 L CNN "Mounted"
F 5 "High Speed, ±100V 2.5A Two or Three Level Ultrasound Pulser" H 3800 -400 60  0001 L CNN "PackageDescription"
F 6 "High Speed, ±100V 2.5A Two or Three Level Ultrasound Pulser" H 3800 -500 60  0001 L CNN "Part Description"
F 7 "HV7360LA-G" H 3800 -600 60  0001 L CNN "Part Number"
F 8 "22" H 3800 -700 60  0001 L CNN "Pin Count"
F 9 "Yes" H 4300 -700 60  0001 L CNN "SMD"
F 10 "No" H 4550 -700 60  0001 L CNN "Socket"
F 11 "Analog & Interface" H 3800 -800 60  0001 L CNN "Table"
F 12 "S. Jafar" H 3800 2300 60  0001 L CNN "Author"
F 13 "LFGA-22" H 3800 2200 60  0001 L CNN "Case"
F 14 "Standard" H 4300 2200 60  0001 L CNN "Component Kind"
F 15 "Standard" H 4800 2200 60  0001 L CNN "Component Type"
F 16 "0.85mm" H 5300 2200 60  0001 L CNN "ComponentHeight"
F 17 "12/20/2015" H 3800 2100 60  0001 L CNN "CreateDate"
F 18 "HV7360LA-G" H 3800 2000 60  0001 L CNN "Device"
F 19 "1/6/2016" H 4450 2100 60  0001 L CNN "LatestRevisionDate"
F 20 "Supertex inc." H 3800 1900 60  0001 L CNN "Manufacturer"
F 21 "HV7360LA-G" H 4650 1900 60  0001 L CNN "Manufacturer Part Number"
F 22 "HV7360LA-G" H 4000 50  60  0000 L CNN "Comment"
	1    4000 1500
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR05
U 1 1 5812EA9D
P 3700 2950
F 0 "#PWR05" H 3700 2700 50  0001 C CNN
F 1 "AGND" H 3700 2800 50  0000 C CNN
F 2 "" H 3700 2950 50  0000 C CNN
F 3 "" H 3700 2950 50  0000 C CNN
	1    3700 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2050 3700 2950
Wire Wire Line
	3700 2050 3800 2050
Wire Wire Line
	3800 2150 3700 2150
Connection ~ 3700 2150
Wire Wire Line
	3800 2450 3700 2450
Connection ~ 3700 2450
Wire Wire Line
	3800 2550 3700 2550
Connection ~ 3700 2550
Wire Wire Line
	3800 2650 3700 2650
Connection ~ 3700 2650
Wire Wire Line
	3800 2750 3700 2750
Connection ~ 3700 2750
$Comp
L Capacitor C5
U 1 1 5812F544
P 3100 2650
F 0 "C5" H 3050 2400 60  0000 L CNN
F 1 "Capacitor" H 3050 2400 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 2920 2980 60  0001 C CNN
F 3 "" H 3020 3080 60  0001 C CNN
F 4 "100nF" H 2950 2900 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 3050 2300 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 3050 2200 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 3050 2100 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 3050 2000 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 3050 1900 60  0001 L CNN "Published"
F 10 "Altium Limited" H 3050 1800 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 3050 1700 60  0001 L CNN "Description"
F 12 "cap0603" H 3050 1600 60  0001 L CNN "Comment"
	1    3100 2650
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR06
U 1 1 5812F54A
P 3100 2950
F 0 "#PWR06" H 3100 2700 50  0001 C CNN
F 1 "AGND" H 3100 2800 50  0000 C CNN
F 2 "" H 3100 2950 50  0000 C CNN
F 3 "" H 3100 2950 50  0000 C CNN
	1    3100 2950
	1    0    0    -1  
$EndComp
$Comp
L VDD_5V #PWR07
U 1 1 5812F550
P 3000 2350
F 0 "#PWR07" H 3000 2150 50  0001 C CNN
F 1 "VDD_5V" V 3000 2000 50  0000 L CNN
F 2 "" H 3000 2350 50  0000 C CNN
F 3 "" H 3000 2350 50  0000 C CNN
	1    3000 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 1650 3700 1650
Wire Wire Line
	3700 1650 3700 950 
Wire Wire Line
	3700 950  3050 950 
Wire Wire Line
	3150 1050 3150 950 
Connection ~ 3150 950 
Wire Wire Line
	3150 1500 3150 1550
Wire Wire Line
	3000 2350 3800 2350
Wire Wire Line
	3100 2450 3100 2350
Connection ~ 3100 2350
Wire Wire Line
	3100 2900 3100 2950
$Comp
L AGND #PWR08
U 1 1 58130E1F
P 4900 2950
F 0 "#PWR08" H 4900 2700 50  0001 C CNN
F 1 "AGND" H 4900 2800 50  0000 C CNN
F 2 "" H 4900 2950 50  0000 C CNN
F 3 "" H 4900 2950 50  0000 C CNN
	1    4900 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2150 4900 2150
Wire Wire Line
	4900 2150 4900 2950
Wire Wire Line
	4800 2350 4900 2350
Connection ~ 4900 2350
Wire Wire Line
	4800 2450 4900 2450
Connection ~ 4900 2450
Wire Wire Line
	4800 2550 4900 2550
Connection ~ 4900 2550
Wire Wire Line
	4800 2650 4900 2650
Connection ~ 4900 2650
$Comp
L Capacitor C2
U 1 1 58131F7B
P 5250 1150
F 0 "C2" H 5200 1400 60  0000 L CNN
F 1 "Capacitor" H 5200 900 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 5070 1480 60  0001 C CNN
F 3 "" H 5170 1580 60  0001 C CNN
F 4 "100nF" H 5100 900 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 5200 800 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 5200 700 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 5200 600 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 5200 500 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 5200 400 60  0001 L CNN "Published"
F 10 "Altium Limited" H 5200 300 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 5200 200 60  0001 L CNN "Description"
F 12 "cap0603" H 5200 100 60  0001 L CNN "Comment"
	1    5250 1150
	0    -1   1    0   
$EndComp
$Comp
L AGND #PWR09
U 1 1 58131F81
P 5250 1600
F 0 "#PWR09" H 5250 1350 50  0001 C CNN
F 1 "AGND" H 5250 1450 50  0000 C CNN
F 2 "" H 5250 1600 50  0000 C CNN
F 3 "" H 5250 1600 50  0000 C CNN
	1    5250 1600
	-1   0    0    -1  
$EndComp
$Comp
L VDD_5V #PWR010
U 1 1 58131F87
P 5350 850
F 0 "#PWR010" H 5350 650 50  0001 C CNN
F 1 "VDD_5V" V 5350 500 50  0000 L CNN
F 2 "" H 5350 850 50  0000 C CNN
F 3 "" H 5350 850 50  0000 C CNN
	1    5350 850 
	0    -1   1    0   
$EndComp
Wire Wire Line
	5250 1400 5250 1600
Wire Wire Line
	4800 1650 5050 1650
Wire Wire Line
	5050 1650 5050 1500
Wire Wire Line
	5050 1500 5250 1500
Connection ~ 5250 1500
Wire Wire Line
	4800 1550 4850 1550
Wire Wire Line
	4850 1550 4850 850 
Wire Wire Line
	4850 850  5350 850 
Wire Wire Line
	5250 950  5250 850 
Connection ~ 5250 850 
$Comp
L Diode D1
U 1 1 58135A1B
P 5700 3100
F 0 "D1" H 5450 3200 60  0000 L CNN
F 1 "Diode" H 5800 3500 60  0001 L CNN
F 2 "DIOM5027X244N" H 6100 3500 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\ES1D.pdf" H 5550 2250 60  0001 L CNN
F 4 "Yes" H 5500 2850 60  0001 L CNN "Mounted"
F 5 "DO-214-AC/SMA  Molded Diode, Body 5.0x2.7mm, IPC Medium Density" H 5500 2050 60  0001 L CNN "PackageDescription"
F 6 "Fast Rectifier" H 5500 2750 60  0001 L CNN "Part Description"
F 7 "ES1D" H 5500 2650 60  0001 L CNN "Part Number"
F 8 "2" H 5500 2550 60  0001 L CNN "Pin Count"
F 9 "1A" H 5650 2550 60  0001 L CNN "Power"
F 10 "Yes" H 6000 2550 60  0001 L CNN "SMD"
F 11 "No" H 6250 2550 60  0001 L CNN "Socket"
F 12 "Diodes" H 5500 2450 60  0001 L CNN "Table"
F 13 "200V" H 5500 2350 60  0001 L CNN "Voltage"
F 14 "CERN DEM JLC" H 5500 3900 60  0001 L CNN "Author"
F 15 "DO-214AC" H 5500 3800 60  0001 L CNN "Case"
F 16 "Standard" H 6050 3800 60  0001 L CNN "Component Kind"
F 17 "Standard" H 6550 3800 60  0001 L CNN "Component Type"
F 18 "2.44mm" H 6200 2150 60  0001 L CNN "ComponentHeight"
F 19 "5/6/2008" H 5500 3700 60  0001 L CNN "CreateDate"
F 20 "ES1D" H 5850 2150 60  0001 L CNN "Device"
F 21 "5/6/2008" H 6150 3700 60  0001 L CNN "LatestRevisionDate"
F 22 "FAIRCHILD SEMICONDUCTOR" H 5500 3600 60  0001 L CNN "Manufacturer"
F 23 "ES1D" H 5500 3500 60  0001 L CNN "Manufacturer Part Number"
F 24 "ES1D" H 5950 3200 60  0000 L CNN "Comment"
F 25 "Diode" H 5500 2150 60  0001 L CNN "Description"
	1    5700 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode D2
U 1 1 58135EDD
P 5900 3350
F 0 "D2" H 6250 3450 60  0000 L CNN
F 1 "Diode" H 6000 3750 60  0001 L CNN
F 2 "DIOM5027X244N" H 6300 3750 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\ES1D.pdf" H 5750 2500 60  0001 L CNN
F 4 "Yes" H 5700 3100 60  0001 L CNN "Mounted"
F 5 "DO-214-AC/SMA  Molded Diode, Body 5.0x2.7mm, IPC Medium Density" H 5700 2300 60  0001 L CNN "PackageDescription"
F 6 "Fast Rectifier" H 5700 3000 60  0001 L CNN "Part Description"
F 7 "ES1D" H 5700 2900 60  0001 L CNN "Part Number"
F 8 "2" H 5700 2800 60  0001 L CNN "Pin Count"
F 9 "1A" H 5850 2800 60  0001 L CNN "Power"
F 10 "Yes" H 6200 2800 60  0001 L CNN "SMD"
F 11 "No" H 6450 2800 60  0001 L CNN "Socket"
F 12 "Diodes" H 5700 2700 60  0001 L CNN "Table"
F 13 "200V" H 5700 2600 60  0001 L CNN "Voltage"
F 14 "CERN DEM JLC" H 5700 4150 60  0001 L CNN "Author"
F 15 "DO-214AC" H 5700 4050 60  0001 L CNN "Case"
F 16 "Standard" H 6250 4050 60  0001 L CNN "Component Kind"
F 17 "Standard" H 6750 4050 60  0001 L CNN "Component Type"
F 18 "2.44mm" H 6400 2400 60  0001 L CNN "ComponentHeight"
F 19 "5/6/2008" H 5700 3950 60  0001 L CNN "CreateDate"
F 20 "ES1D" H 6050 2400 60  0001 L CNN "Device"
F 21 "5/6/2008" H 6350 3950 60  0001 L CNN "LatestRevisionDate"
F 22 "FAIRCHILD SEMICONDUCTOR" H 5700 3850 60  0001 L CNN "Manufacturer"
F 23 "ES1D" H 5700 3750 60  0001 L CNN "Manufacturer Part Number"
F 24 "ES1D" H 5600 3450 60  0000 L CNN "Comment"
F 25 "Diode" H 5700 2400 60  0001 L CNN "Description"
	1    5900 3350
	-1   0    0    -1  
$EndComp
$Comp
L Capacitor C3
U 1 1 581369EF
P 6250 1150
F 0 "C3" H 6200 1400 60  0000 L CNN
F 1 "Capacitor" H 6200 900 60  0001 L CNN
F 2 "footprint:SM0603_3D_cap" H 6070 1480 60  0001 C CNN
F 3 "" H 6170 1580 60  0001 C CNN
F 4 "100nF" H 6100 900 60  0000 L CNN "Value"
F 5 "17-Jul-2002" H 6200 800 60  0001 L CNN "LatestRevisionDate"
F 6 "Re-released for DXP Platform." H 6200 700 60  0001 L CNN "LatestRevisionNote"
F 7 "Radial Cap, Thru-Hole; 2 Leads; 0.3 in Pin Spacing" H 6200 600 60  0001 L CNN "PackageDescription"
F 8 "RAD-0.3" H 6200 500 60  0001 L CNN "PackageReference"
F 9 "8-Jun-2000" H 6200 400 60  0001 L CNN "Published"
F 10 "Altium Limited" H 6200 300 60  0001 L CNN "Publlisher"
F 11 "Capacitor  0603 inch" H 6200 200 60  0001 L CNN "Description"
F 12 "cap0603" H 6200 100 60  0001 L CNN "Comment"
	1    6250 1150
	0    -1   1    0   
$EndComp
$Comp
L Capacitor C4
U 1 1 58136AEC
P 6900 1150
F 0 "C4" H 6850 1400 60  0000 L CNN
F 1 "Capacitor" H 6850 900 60  0001 L CNN
F 2 "footprint:CAPC5650X165N" H 6720 1480 60  0001 C CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\CC2220_X7R_KEMET.pdf" H 6820 1580 60  0001 C CNN
F 4 "CERN DEM JLC" H 6900 1150 60  0001 L CNN "Author"
F 5 "2220" H 6900 1150 60  0001 L CNN "Case"
F 6 "Standard" H 6900 1150 60  0001 L CNN "Component Kind"
F 7 "Standard" H 6900 1150 60  0001 L CNN "Component Type"
F 8 "9/16/2009" H 6900 1150 60  0001 L CNN "CreateDate"
F 9 "9/16/2009" H 6850 800 60  0001 L CNN "LatestRevisionDate"
F 10 "GENERIC" H 6900 1150 60  0001 L CNN "Manufacturer"
F 11 "CC2220_1UF_200V_10%_X7R" H 6900 1150 60  0001 L CNN "Manufacturer Part Number"
F 12 "1.65mm" H 6900 1150 60  0001 L CNN "Manufacturer1 PartHeight"
F 13 "KEMET" H 6900 1150 60  0001 L CNN "Manufacturer1 Example"
F 14 "C2220X105K2RAC" H 6900 1150 60  0001 L CNN "Manufacturer1 Part Number"
F 15 "Yes" H 6850 700 60  0001 L CNN "Mounted"
F 16 "SMD Ceramic Chip Capacitor" H 6850 600 60  0001 L CNN "Part Description"
F 17 "CC2220_1UF_200V_10%_X7R" H 6850 500 60  0001 L CNN "Part Number"
F 18 "2" H 6850 400 60  0001 L CNN "Pin Count"
F 19 "Yes" H 6850 300 60  0001 L CNN "SMD"
F 20 "No" H 6900 1150 60  0001 L CNN "Socket"
F 21 "None" H 6900 1150 60  0001 L CNN "Status"
F 22 "Capacitors SMD" H 6900 1150 60  0001 L CNN "Table"
F 23 "X7R" H 6900 1150 60  0001 L CNN "TC"
F 24 "±10%" H 6900 1150 60  0001 L CNN "Tolerance"
F 25 "1uF" H 6850 900 60  0000 L CNN "Value"
F 26 "Non-polarised capacitor" H 6850 200 60  0001 L CNN "Description"
F 27 "200V" H 6850 100 60  0001 L CNN "Voltage"
	1    6900 1150
	0    -1   1    0   
$EndComp
$Comp
L AGND #PWR011
U 1 1 58138260
P 6900 1600
F 0 "#PWR011" H 6900 1350 50  0001 C CNN
F 1 "AGND" H 6900 1450 50  0000 C CNN
F 2 "" H 6900 1600 50  0000 C CNN
F 3 "" H 6900 1600 50  0000 C CNN
	1    6900 1600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6900 1400 6900 1600
Wire Wire Line
	6250 1400 6250 1500
Wire Wire Line
	6250 1500 6900 1500
Connection ~ 6900 1500
Wire Wire Line
	6100 3100 6300 3100
Wire Wire Line
	6300 3100 6300 3850
Wire Wire Line
	6100 3350 9250 3350
Connection ~ 6300 3350
$Comp
L MD0100N8-G IC1
U 1 1 58138F62
P 6600 3800
F 0 "IC1" H 6750 3950 60  0000 L CNN
F 1 "MD0100N8-G" H 6400 2900 60  0001 L CNN
F 2 "footprint:SOT89" H 7150 4300 60  0001 L CNN
F 3 "" H 6400 2200 60  0001 L CNN
F 4 "Yes" H 6400 2800 60  0001 L CNN "Mounted"
F 5 "SOT89-3, 3-Leads, Body 2.44x4.5mm" H 6400 2700 60  0001 L CNN "PackageDescription"
F 6 "Ultra-Sound HV Switch" H 6400 2600 60  0001 L CNN "Part Description"
F 7 "MD0100N8-G" H 6400 2500 60  0001 L CNN "Part Number"
F 8 "4" H 6400 2400 60  0001 L CNN "Pin Count"
F 9 "Yes" H 6900 2400 60  0001 L CNN "SMD"
F 10 "No" H 7150 2400 60  0001 L CNN "Socket"
F 11 "Analog & Interface" H 6400 2300 60  0001 L CNN "Table"
F 12 "S. Jafar" H 6400 4600 60  0001 L CNN "Author"
F 13 "SOT89" H 6400 4500 60  0001 L CNN "Case"
F 14 "Standard" H 6800 4500 60  0001 L CNN "Component Kind"
F 15 "Standard" H 7300 4500 60  0001 L CNN "Component Type"
F 16 "1.6mm" H 7800 4500 60  0001 L CNN "ComponentHeight"
F 17 "12/20/2015" H 6400 4400 60  0001 L CNN "CreateDate"
F 18 "MD0100N8-G" H 6400 4300 60  0001 L CNN "Device"
F 19 "1/6/2016" H 7050 4400 60  0001 L CNN "LatestRevisionDate"
F 20 "Supertex inc." H 6400 4200 60  0001 L CNN "Manufacturer"
F 21 "MD0100N8-G" H 7150 4200 60  0001 L CNN "Manufacturer Part Number"
F 22 "MD0100N8-G" H 6000 3400 60  0000 L CNN "Comment"
F 23 "3-Ultra-Sound HV Switch 1=A 2=COM 3=B" H 6400 2200 60  0001 L CNN "Description"
	1    6600 3800
	1    0    0    -1  
$EndComp
Text Notes 6600 3350 0    60   Italic 0
RF Net Class
Wire Wire Line
	6300 3850 6400 3850
Wire Wire Line
	7200 3850 9250 3850
Text Notes 7300 3850 0    60   Italic 0
RF Net Class
$Comp
L TP TP1
U 1 1 5813A5F1
P 7200 3100
F 0 "TP1" H 7600 3100 60  0000 L CNN
F 1 "TP" H 7000 2950 60  0001 L CNN
F 2 "footprint:NICOMATIC_C12000B" H 6950 3250 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\NICOMATIC_C12000B.pdf" H 7000 2350 60  0001 L CNN
F 4 "Yes" H 7000 2850 60  0001 L CNN "Mounted"
F 5 "SMD Test Point" H 7000 2750 60  0001 L CNN "Part Description"
F 6 "NICOMATIC_C12000B" H 7000 2650 60  0001 L CNN "Part Number"
F 7 "1" H 7000 2550 60  0001 L CNN "Pin Count"
F 8 "Yes" H 7200 2550 60  0001 L CNN "SMD"
F 9 "No" H 7450 2550 60  0001 L CNN "Socket"
F 10 "None" H 7650 2550 60  0001 L CNN "Status"
F 11 "Miscellaneous" H 7000 2450 60  0001 L CNN "Table"
F 12 "CERN DEM JLC" H 7000 3900 60  0001 L CNN "Author"
F 13 "Test Point" H 7000 3800 60  0001 L CNN "Family"
F 14 "Standard" H 7550 3800 60  0001 L CNN "Component Kind"
F 15 "Standard" H 8050 3800 60  0001 L CNN "Component Type"
F 16 "1.5mm" H 7000 3400 60  0001 L CNN "ComponentHeight"
F 17 "3/25/2009" H 7000 3700 60  0001 L CNN "CreateDate"
F 18 "3/25/2009" H 7650 3700 60  0001 L CNN "LatestRevisionDate"
F 19 "NICOMATIC" H 7000 3600 60  0001 L CNN "Manufacturer"
F 20 "C12000B" H 7000 3500 60  0001 L CNN "Manufacturer Part Number"
F 21 "Test Point" H 7600 2250 60  0001 L CNN "Comment"
F 22 "Test Point" H 7000 2250 60  0001 L CNN "Description"
	1    7200 3100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7200 3100 7350 3100
Wire Wire Line
	7350 3100 7350 3350
Connection ~ 7350 3350
$Comp
L BAT64-04W D3
U 1 1 5813B7A9
P 8000 4450
F 0 "D3" H 8000 4600 60  0000 L CNN
F 1 "BAT64-04W" H 8400 4850 60  0001 L CNN
F 2 "SOT65P210X100-3N" H 9050 4850 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\BAT64-04W.pdf" H 7850 3600 60  0001 L CNN
F 4 "Yes" H 7800 4200 60  0001 L CNN "Mounted"
F 5 "SOT323, 0.65mm pitch; 3 pin, 1.25mm W X 2.00mm L, IPC Medium Density" H 7800 3400 60  0001 L CNN "PackageDescription"
F 6 "Silicon Schottky Double Diode" H 7800 4100 60  0001 L CNN "Part Description"
F 7 "BAT64-04W" H 7800 4000 60  0001 L CNN "Part Number"
F 8 "3" H 7800 3900 60  0001 L CNN "Pin Count"
F 9 "250mW" H 7950 3900 60  0001 L CNN "Power"
F 10 "Yes" H 8300 3900 60  0001 L CNN "SMD"
F 11 "No" H 8550 3900 60  0001 L CNN "Socket"
F 12 "Diodes" H 7800 3800 60  0001 L CNN "Table"
F 13 "40V" H 7800 3700 60  0001 L CNN "Voltage"
F 14 "CERN DEM JMW" H 7800 5250 60  0001 L CNN "Author"
F 15 "SOT323" H 7800 5150 60  0001 L CNN "Case"
F 16 "Standard" H 8350 5150 60  0001 L CNN "Component Kind"
F 17 "Standard" H 8850 5150 60  0001 L CNN "Component Type"
F 18 "1mm" H 8800 3500 60  0001 L CNN "ComponentHeight"
F 19 "1/8/2009" H 7800 5050 60  0001 L CNN "CreateDate"
F 20 "BAT64-04W" H 8150 3500 60  0001 L CNN "Device"
F 21 "1/8/2009" H 8450 5050 60  0001 L CNN "LatestRevisionDate"
F 22 "INFINEON" H 7800 4950 60  0001 L CNN "Manufacturer"
F 23 "BAT64-04W" H 7800 4850 60  0001 L CNN "Manufacturer Part Number"
F 24 "BAT64-04W" H 8250 4600 60  0001 L CNN "Comment"
F 25 "Diode" H 7800 3500 60  0001 L CNN "Description"
	1    8000 4450
	0    -1   -1   0   
$EndComp
$Comp
L BAT64-04W D3
U 2 1 5813BA7C
P 8350 4250
F 0 "D3" H 8350 4100 60  0000 L CNN
F 1 "BAT64-04W" H 8750 4650 60  0001 L CNN
F 2 "SOT65P210X100-3N" H 9400 4650 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\BAT64-04W.pdf" H 8200 3400 60  0001 L CNN
F 4 "Yes" H 8150 4000 60  0001 L CNN "Mounted"
F 5 "SOT323, 0.65mm pitch; 3 pin, 1.25mm W X 2.00mm L, IPC Medium Density" H 8150 3200 60  0001 L CNN "PackageDescription"
F 6 "Silicon Schottky Double Diode" H 8150 3900 60  0001 L CNN "Part Description"
F 7 "BAT64-04W" H 8150 3800 60  0001 L CNN "Part Number"
F 8 "3" H 8150 3700 60  0001 L CNN "Pin Count"
F 9 "250mW" H 8300 3700 60  0001 L CNN "Power"
F 10 "Yes" H 8650 3700 60  0001 L CNN "SMD"
F 11 "No" H 8900 3700 60  0001 L CNN "Socket"
F 12 "Diodes" H 8150 3600 60  0001 L CNN "Table"
F 13 "40V" H 8150 3500 60  0001 L CNN "Voltage"
F 14 "CERN DEM JMW" H 8150 5050 60  0001 L CNN "Author"
F 15 "SOT323" H 8150 4950 60  0001 L CNN "Case"
F 16 "Standard" H 8700 4950 60  0001 L CNN "Component Kind"
F 17 "Standard" H 9200 4950 60  0001 L CNN "Component Type"
F 18 "1mm" H 9150 3300 60  0001 L CNN "ComponentHeight"
F 19 "1/8/2009" H 8150 4850 60  0001 L CNN "CreateDate"
F 20 "BAT64-04W" H 8500 3300 60  0001 L CNN "Device"
F 21 "1/8/2009" H 8800 4850 60  0001 L CNN "LatestRevisionDate"
F 22 "INFINEON" H 8150 4750 60  0001 L CNN "Manufacturer"
F 23 "BAT64-04W" H 8150 4650 60  0001 L CNN "Manufacturer Part Number"
F 24 "BAT64-04W" H 8200 4500 60  0000 L CNN "Comment"
F 25 "Diode" H 8150 3300 60  0001 L CNN "Description"
	2    8350 4250
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR012
U 1 1 5813C0D4
P 8000 4950
F 0 "#PWR012" H 8000 4700 50  0001 C CNN
F 1 "AGND" H 8000 4800 50  0000 C CNN
F 2 "" H 8000 4950 50  0000 C CNN
F 3 "" H 8000 4950 50  0000 C CNN
	1    8000 4950
	1    0    0    -1  
$EndComp
Wire Notes Line
	7750 4850 7750 3950
Wire Notes Line
	7750 3950 8500 3950
Wire Notes Line
	8500 3950 8500 4850
Wire Notes Line
	8500 4850 7750 4850
Wire Wire Line
	8000 4650 8000 4950
Wire Wire Line
	8350 4650 8350 4750
Wire Wire Line
	8350 4750 8000 4750
Connection ~ 8000 4750
Wire Wire Line
	8350 3850 8350 4050
Wire Wire Line
	8000 4050 8000 3850
Connection ~ 8000 3850
$Comp
L Jumper Jumper1
U 1 1 5813D4DF
P 9200 4500
F 0 "Jumper1" V 9500 4200 60  0000 L CNN
F 1 "Jumper" H 9000 4050 60  0001 L CNN
F 2 "footprint:SULLINS_GRPB031VWVN" H 8950 4650 60  0001 L CNN
F 3 "" H 9000 3450 60  0001 L CNN
F 4 "Yes" H 9000 3950 60  0001 L CNN "Mounted"
F 5 "3 Contact 0.5\" Pitch Single-In-Line Vertical Header" H 9000 3850 60  0001 L CNN "Part Description"
F 6 "SULLINS_GRPB031VWVN" H 9000 3750 60  0001 L CNN "Part Number"
F 7 "3" H 9000 3650 60  0001 L CNN "Pin Count"
F 8 "No" H 9500 3650 60  0001 L CNN "SMD"
F 9 "None" H 9000 4950 60  0001 L CNN "Status"
F 10 "Miscellaneous" H 9000 3550 60  0001 L CNN "Table"
F 11 "No" H 9750 3650 60  0001 L CNN "Socket"
F 12 "S. Jafar" H 9000 5050 60  0001 L CNN "Author"
F 13 "Standard" H 9400 4950 60  0001 L CNN "Component Kind"
F 14 "Standard" H 9900 4950 60  0001 L CNN "Component Type"
F 15 "4mm" H 10400 4950 60  0001 L CNN "ComponentHeight"
F 16 "12/29/2015" H 9000 4850 60  0001 L CNN "CreateDate"
F 17 "12/29/2015" H 9650 4850 60  0001 L CNN "LatestRevisionDate"
F 18 "SULLINS" H 9000 4750 60  0001 L CNN "Manufacturer"
F 19 "GRPB031VWVN" H 9850 4750 60  0001 L CNN "Manufacturer Part Number"
F 20 "Connector 3 Male" H 9000 3450 60  0001 L CNN "Description"
	1    9200 4500
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR013
U 1 1 5813DFE0
P 9200 4000
F 0 "#PWR013" H 9200 3750 50  0001 C CNN
F 1 "AGND" H 9200 3850 50  0000 C CNN
F 2 "" H 9200 4000 50  0000 C CNN
F 3 "" H 9200 4000 50  0000 C CNN
	1    9200 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 4300 9150 4250
Wire Wire Line
	9150 4250 10000 4250
Wire Wire Line
	9200 4000 9200 3950
Wire Wire Line
	9200 3950 9250 3950
Connection ~ 8350 3850
Wire Wire Line
	9050 4300 9050 3850
Connection ~ 9050 3850
Text Notes 9500 3700 0    60   Italic 0
VGA IN
$Comp
L SMA J1
U 1 1 5813F078
P 9450 3300
F 0 "J1" H 9550 3250 60  0000 L CNN
F 1 "SMA" H 9250 3000 60  0001 L CNN
F 2 "footprint:AMPHENOL_132357-11" H 9200 3450 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\AMPHENOL_132357-11.pdf" H 9250 2400 60  0001 L CNN
F 4 "Yes" H 9250 2900 60  0001 L CNN "Mounted"
F 5 "SMA End Launch Jack for 1.58mm PCB, 50 Ohm, Flat Tab Contact" H 9250 2800 60  0001 L CNN "Part Description"
F 6 "AMPHENOL_132357-11" H 9250 2700 60  0001 L CNN "Part Number"
F 7 "2" H 9250 2600 60  0001 L CNN "Pin Count"
F 8 "No" H 10000 2600 60  0001 L CNN "Socket"
F 9 "None" H 9250 3750 60  0001 L CNN "Status"
F 10 "AMPHENOL" H 9250 2500 60  0001 L CNN "Table"
F 11 "Yes" H 9750 2600 60  0001 L CNN "SMD"
F 12 "CERN DEM JLC" H 9250 3850 60  0001 L CNN "Author"
F 13 "SMA" H 11250 5200 60  0001 L CNN "Family"
F 14 "5/14/2012" H 9900 3650 60  0001 L CNN "LatestRevisionDate"
F 15 "AMPHENOL" H 9250 3550 60  0001 L CNN "Manufacturer"
F 16 "132357-11" H 10100 3550 60  0001 L CNN "Manufacturer Part Number"
F 17 "Standard" H 9650 3750 60  0001 L CNN "Component Kind"
F 18 "SMA" H 9850 2500 60  0001 L CNN "Comment"
F 19 "Standard" H 10150 3750 60  0001 L CNN "Component Type"
F 20 "7.92mm" H 10650 3750 60  0001 L CNN "ComponentHeight"
F 21 "5/14/2012" H 9250 3650 60  0001 L CNN "CreateDate"
	1    9450 3300
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR014
U 1 1 5813F07F
P 9200 3500
F 0 "#PWR014" H 9200 3250 50  0001 C CNN
F 1 "AGND" H 9200 3350 50  0000 C CNN
F 2 "" H 9200 3500 50  0000 C CNN
F 3 "" H 9200 3500 50  0000 C CNN
	1    9200 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 3500 9200 3450
Wire Wire Line
	9200 3450 9250 3450
Text Notes 9500 3200 0    60   Italic 0
Ultrasonic transducer
Wire Wire Line
	4800 1850 5850 1850
Wire Wire Line
	5850 1850 5850 850 
Wire Wire Line
	5850 850  7000 850 
Wire Wire Line
	6900 850  6900 950 
Wire Wire Line
	6250 950  6250 850 
Connection ~ 6250 850 
Wire Wire Line
	4800 1950 5350 1950
Wire Wire Line
	5350 1950 5350 3100
Wire Wire Line
	5350 3100 5500 3100
Wire Wire Line
	4800 2050 5250 2050
Wire Wire Line
	5250 2050 5250 3350
Wire Wire Line
	5250 3350 5500 3350
$Comp
L Resistor R1
U 1 1 58140917
P 7400 850
F 0 "R1" H 7350 700 60  0000 L CNN
F 1 "Resistor" H 7200 700 60  0001 L CNN
F 2 "footprint:RESC3216X65N" H 7150 1000 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\R1206_NIC_NRC.pdf" H 7250 0   60  0001 L CNN
F 4 "4k7" H 7200 -100 60  0001 L CNN "Value"
F 5 "Yes" H 7200 600 60  0001 L CNN "Mounted"
F 6 "General Purpose Thick Film Chip Resistor" H 7200 500 60  0001 L CNN "Part Description"
F 7 "R1206_4K7_1%_0.25W_100PPM" H 7200 400 60  0001 L CNN "Part Number"
F 8 "2" H 7200 300 60  0001 L CNN "Pin Count"
F 9 "0.25W" H 7350 300 60  0001 L CNN "Power"
F 10 "Yes" H 7700 300 60  0001 L CNN "SMD"
F 11 "No" H 7950 300 60  0001 L CNN "Socket"
F 12 "Preffered" H 8150 300 60  0001 L CNN "Status"
F 13 "Resistors SMD" H 7200 200 60  0001 L CNN "Table"
F 14 "±100ppm/°C" H 7200 100 60  0001 L CNN "TC"
F 15 "1%" H 7400 850 60  0000 C CNN "Tolerance_Show"
F 16 "±1%" H 7950 100 60  0001 L CNN "Tolerance"
F 17 "CERN DEM JLC" H 7200 1650 60  0001 L CNN "Author"
F 18 "1206" H 7200 1550 60  0001 L CNN "Case"
F 19 "Standard" H 7500 1550 60  0001 L CNN "Component Kind"
F 20 "Standard" H 8000 1550 60  0001 L CNN "Component Type"
F 21 "12/3/2007" H 7200 1450 60  0001 L CNN "CreateDate"
F 22 "3/13/2008" H 7850 1450 60  0001 L CNN "LatestRevisionDate"
F 23 "GENERIC" H 7200 1350 60  0001 L CNN "Manufacturer"
F 24 "R1206_4K7_1%_0.25W_100PPM" H 7200 1250 60  0001 L CNN "Manufacturer Part Number"
F 25 "0.65mm" H 7200 1150 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 26 "NIC COMPONENT" H 7650 1150 60  0001 L CNN "Manufacturer1 Example"
F 27 "NRC12F4701TRF" H 8500 1150 60  0001 L CNN "Manufacturer1 PartNumber"
F 28 "4k7" H 7300 1000 60  0000 L CNN "Comment"
F 29 "Res_0603_1%_EU" H 7200 -200 60  0001 L CNN "Description"
	1    7400 850 
	-1   0    0    1   
$EndComp
Connection ~ 6900 850 
$Comp
L HVOUT #PWR015
U 1 1 58141F9A
P 7900 850
F 0 "#PWR015" H 7900 650 50  0001 C CNN
F 1 "HVOUT" V 7900 550 50  0000 L CNN
F 2 "" H 7900 850 50  0000 C CNN
F 3 "" H 7900 850 50  0000 C CNN
	1    7900 850 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7900 850  7800 850 
Text Label 9500 4250 0    60   ~ 0
VGA_in
Wire Wire Line
	10000 4250 10000 5650
Wire Wire Line
	10000 5650 10250 5650
$Comp
L Capacitor C8
U 1 1 581452A3
P 2200 5400
F 0 "C8" H 2150 5150 60  0000 L CNN
F 1 "Capacitor" H 2150 5150 60  0001 L CNN
F 2 "footprint:CAPC3216X180N" H 2020 5730 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\CC1206_X5R_TDK_C.pdf" H 2120 5830 60  0001 L CNN
F 4 "CERN DEM JLC" H 2100 5650 60  0001 L CNN "Author"
F 5 "17-Jul-2002" H 2150 5050 60  0001 L CNN "LatestRevisionDate"
F 6 "1206" H 2150 4950 60  0001 L CNN "Case"
F 7 "Standard" H 2150 4850 60  0001 L CNN "Component Kind"
F 8 "Standard" H 2150 4750 60  0001 L CNN "Component Type"
F 9 "1.8mm" H 2150 4650 60  0001 L CNN "ComponentHeight"
F 10 "11/20/2013" H 2150 4550 60  0001 L CNN "CreateData"
F 11 "TDK" H 2150 4450 60  0001 L CNN "manufacturer"
F 12 "C3216X5R1E476M160AC" H 2150 4350 60  0001 L CNN "Manufacturer Part Number"
F 13 "Yes" H 2200 5400 60  0001 L CNN "Mounted"
F 14 "SMD Multilayer Chip Ceramic Capacitor" H 2200 5400 60  0001 L CNN "Part Description"
F 15 "CC1206_47UF_25V_20%_X5R" H 2200 5400 60  0001 L CNN "Part Number"
F 16 "2" H 2200 5400 60  0001 L CNN "Pin Count"
F 17 "Yes" H 2200 5400 60  0001 L CNN "SMD"
F 18 "No" H 2200 5400 60  0001 L CNN "Socket"
F 19 "None" H 2200 5400 60  0001 L CNN "Status"
F 20 "Capacitors SMD" H 2200 5400 60  0001 L CNN "Table"
F 21 "X5R" H 2200 5400 60  0001 L CNN "TC"
F 22 "±20%" H 2200 5400 60  0001 L CNN "Tolerance"
F 23 "47uF" H 2100 5650 60  0000 L CNN "Value"
F 24 "25V" H 2200 5400 60  0001 L CNN "Voltage"
	1    2200 5400
	0    1    1    0   
$EndComp
$Comp
L R05-100B IC3
U 1 1 581477B1
P 2950 5050
F 0 "IC3" H 3200 5200 60  0000 L CNN
F 1 "R05-100B" H 2750 3850 60  0001 L CNN
F 2 "PWS_RECOM_R05-100B" H 3350 5550 60  0001 L CNN
F 3 "" H 2750 3150 60  0001 L CNN
F 4 "Yes" H 2750 3750 60  0001 L CNN "Mounted"
F 5 "55-135V 5W Power Supply, Body 32x21mm" H 2750 3650 60  0001 L CNN "PackageDescription"
F 6 "+5VDC to +55-135VDC 5W Power Supply" H 2750 3550 60  0001 L CNN "Part Description"
F 7 "R05-100B" H 2750 3450 60  0001 L CNN "Part Number"
F 8 "12" H 2750 3350 60  0001 L CNN "Pin Count"
F 9 "No" H 3250 3350 60  0001 L CNN "SMD"
F 10 "No" H 3500 3350 60  0001 L CNN "Socket"
F 11 "None" H 5200 7200 60  0001 L CNN "Status"
F 12 "Power Supplies" H 2750 3250 60  0001 L CNN "Table"
F 13 "S. Jafar" H 2750 5850 60  0001 L CNN "Author"
F 14 "Standard" H 2750 5750 60  0001 L CNN "Component Kind"
F 15 "Standard" H 3250 5750 60  0001 L CNN "Component Type"
F 16 "9.4mm" H 3750 5750 60  0001 L CNN "ComponentHeight"
F 17 "12/21/2015" H 2750 5650 60  0001 L CNN "CreateDate"
F 18 "R05-100B" H 2750 5550 60  0001 L CNN "Device"
F 19 "12/21/2015" H 3400 5650 60  0001 L CNN "LatestRevisionDate"
F 20 "RECOM POWER" H 2750 5450 60  0001 L CNN "Manufacturer"
F 21 "R05-100B" H 3600 5450 60  0001 L CNN "Manufacturer Part Number"
F 22 "R05-100B" H 2950 4000 60  0000 L CNN "Comment"
	1    2950 5050
	1    0    0    -1  
$EndComp
$Comp
L Capacitor_polar C7
U 1 1 581489FB
P 1550 5400
F 0 "C7" H 1500 5150 60  0000 L CNN
F 1 "Capacitor_polar" H 2550 6150 60  0001 L CNN
F 2 "footprint:CAPMP3528X210N" H 1550 5750 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\CTE-LESR_AVX_TPS.pdf" H 1550 5850 60  0001 L CNN
F 4 "CERN DEM JLC" H 1550 7050 60  0001 L CNN "Author"
F 5 "B" H 1550 6950 60  0001 L CNN "Case"
F 6 "Standard" H 1700 6950 60  0001 L CNN "Component Kind"
F 7 "Standard" H 2200 7150 60  0001 L CNN "Component Type"
F 8 "5/5/2008" H 1550 6850 60  0001 L CNN "CreateDate"
F 9 "1/20/2009" H 2100 7050 60  0001 L CNN "LatestRevisionDate"
F 10 "GENERIC" H 1550 6750 60  0001 L CNN "Manufacturer"
F 11 "CTE3528-21_10UF_16V_10%_LESR0800" H 1550 6250 60  0001 L CNN "Manufacturer Part Number"
F 12 "2.1mm" H 1550 6550 60  0001 L CNN "Manufacturer1 ComponentHeight"
F 13 "AVX" H 1950 6750 60  0001 L CNN "Manufacturer1 Example"
F 14 "TPSB106K016R0800" H 2200 6750 60  0001 L CNN "Manufacturer1 Part Number"
F 15 "Yes" H 1700 6150 60  0001 L CNN "Mounted"
F 16 "Low ESR 0R8 Solid Tantalum Chip Capacitor" H 1550 6350 60  0001 L CNN "Part Description"
F 17 "CTE3528-21_10UF_16V_10%_LESR0800" H 1550 6650 60  0001 L CNN "part Number"
F 18 "2" H 1550 6150 60  0001 L CNN "Pin Count"
F 19 "Yes" H 1550 6450 60  0001 L CNN "SMD"
F 20 "No" H 1950 6350 60  0001 L CNN "Socket"
F 21 "Preffered" H 2150 6350 60  0001 L CNN "Status"
F 22 "Capacitors SMD" H 2650 6350 60  0001 L CNN "Table"
F 23 "±10%" H 1550 6050 60  0001 L CNN "Tolerance"
F 24 "10uF" H 1450 5650 60  0000 L CNN "Value"
F 25 "16V" H 1900 6250 60  0001 L CNN "Voltage"
F 26 "Polarised capacitor" H 2000 6150 60  0001 C CNN "Description"
	1    1550 5400
	0    1    1    0   
$EndComp
$Comp
L Capacitor C6
U 1 1 5814A9E1
P 4800 5000
F 0 "C6" H 4750 4750 60  0000 L CNN
F 1 "Capacitor" H 4750 4750 60  0001 L CNN
F 2 "footprint:CAPC2012X110N" H 4620 5330 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\CC1206_X5R_TDK_C.pdf" H 4720 5430 60  0001 L CNN
F 4 "S. Jafar" H 4700 5250 60  0001 L CNN "Author"
F 5 "12/21/2015" H 4750 4650 60  0001 L CNN "LatestRevisionDate"
F 6 "0805" H 4750 4550 60  0001 L CNN "Case"
F 7 "Standard" H 4750 4450 60  0001 L CNN "Component Kind"
F 8 "Standard" H 4750 4350 60  0001 L CNN "Component Type"
F 9 "1.1mm" H 4750 4250 60  0001 L CNN "ComponentHeight"
F 10 "1/10/2016" H 4750 4150 60  0001 L CNN "CreateData"
F 11 "GENERIC" H 4750 4050 60  0001 L CNN "Manufacturer"
F 12 "GRM21AR72E472KW01D" H 4750 3950 60  0001 L CNN "Manufacturer1 Part Number"
F 13 "Yes" H 4800 5000 60  0001 L CNN "Mounted"
F 14 "SMD Multilayer Chip Ceramic Capacitor" H 4800 5000 60  0001 L CNN "Part Description"
F 15 "CC0805_4.7NF_250V_10%_X7R" H 4800 5000 60  0001 L CNN "Part Number"
F 16 "2" H 4800 5000 60  0001 L CNN "Pin Count"
F 17 "Yes" H 4800 5000 60  0001 L CNN "SMD"
F 18 "No" H 4800 5000 60  0001 L CNN "Socket"
F 19 "None" H 4800 5000 60  0001 L CNN "Status"
F 20 "Capacitors SMD" H 4800 5000 60  0001 L CNN "Table"
F 21 "X7R" H 4800 5000 60  0001 L CNN "TC"
F 22 "±10%" H 4800 5000 60  0001 L CNN "Tolerance"
F 23 "4.7nF" H 4700 5250 60  0000 L CNN "Value"
F 24 "250V" H 4800 5000 60  0001 L CNN "Voltage"
	1    4800 5000
	0    1    1    0   
$EndComp
$Comp
L VDD_5V #PWR016
U 1 1 5814BAAB
P 1200 5100
F 0 "#PWR016" H 1200 4900 50  0001 C CNN
F 1 "VDD_5V" V 1200 4750 50  0000 L CNN
F 2 "" H 1200 5100 50  0000 C CNN
F 3 "" H 1200 5100 50  0000 C CNN
	1    1200 5100
	0    1    -1   0   
$EndComp
$Comp
L AGND #PWR017
U 1 1 5814BDC6
P 1200 5800
F 0 "#PWR017" H 1200 5550 50  0001 C CNN
F 1 "AGND" H 1200 5650 50  0000 C CNN
F 2 "" H 1200 5800 50  0000 C CNN
F 3 "" H 1200 5800 50  0000 C CNN
	1    1200 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 5100 2750 5100
Wire Wire Line
	2750 5200 2600 5200
Wire Wire Line
	2600 5200 2600 5100
Connection ~ 2600 5100
Wire Wire Line
	2200 5200 2200 5100
Connection ~ 2200 5100
Wire Wire Line
	1550 5200 1550 5100
Connection ~ 1550 5100
Wire Wire Line
	1200 5700 2750 5700
Wire Wire Line
	1200 5700 1200 5800
Wire Wire Line
	2200 5650 2200 5700
Connection ~ 2200 5700
Wire Wire Line
	1550 5650 1550 5700
Connection ~ 1550 5700
Wire Wire Line
	2750 5600 2600 5600
Wire Wire Line
	2600 5600 2600 5700
Connection ~ 2600 5700
$Comp
L TrimPot P1
U 1 1 5814CCC9
P 4300 6100
F 0 "P1" H 4050 5950 60  0000 L CNN
F 1 "TrimPot" H 4100 5700 60  0001 L CNN
F 2 "footprint:TRIM_BOURNS_3223W" H 4050 6250 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\TRIM_BOURNS_3223W.pdf" H 4150 5000 60  0001 L CNN
F 4 "5k" H 4100 4900 60  0001 L CNN "Value"
F 5 "Yes" H 4100 5600 60  0001 L CNN "Mounted"
F 6 "11 Turns SMD Trimpot® Trimming Potentiometer (Top Adjust)" H 4100 5500 60  0001 L CNN "Part Description"
F 7 "TRIM_11T_5K_BOURNS_3223W-1-502E" H 4100 5400 60  0001 L CNN "Part Number"
F 8 "3" H 4100 5300 60  0001 L CNN "Pin Count"
F 9 "0.125W" H 4250 5300 60  0001 L CNN "Power"
F 10 "Yes" H 4600 5300 60  0001 L CNN "SMD"
F 11 "No" H 4850 5300 60  0001 L CNN "Socket"
F 12 "Potentiometers SMD" H 4100 5200 60  0001 L CNN "Table"
F 13 "±100ppm/°C" H 4100 5100 60  0001 L CNN "TC"
F 14 "±20%" H 4850 5100 60  0001 L CNN "Tolerance"
F 15 "CERN DEM JLC" H 4100 6900 60  0001 L CNN "Author"
F 16 "3223W" H 4100 6800 60  0001 L CNN "Case"
F 17 "Standard" H 4500 6800 60  0001 L CNN "Component Kind"
F 18 "Standard" H 5000 6800 60  0001 L CNN "Component Type"
F 19 "4.16mm" H 5500 6800 60  0001 L CNN "ComponentHeight"
F 20 "3/31/2011" H 4100 6700 60  0001 L CNN "CreateDate"
F 21 "12/18/2012" H 4750 6700 60  0001 L CNN "LatestRevisionDate"
F 22 "BOURNS" H 4100 6600 60  0001 L CNN "Manufacturer"
F 23 "3223W-1-502E" H 4100 6500 60  0001 L CNN "Manufacturer Part Number"
F 24 "5k" H 4250 6250 60  0001 L CNN "Comment"
F 25 "Trimming Potentiometer" H 4100 4800 60  0001 L CNN "Description"
	1    4300 6100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3750 5800 3850 5800
Wire Wire Line
	3850 5800 3850 6100
Wire Wire Line
	3850 5900 3750 5900
Wire Wire Line
	3750 5700 4300 5700
Wire Wire Line
	3850 5700 3850 5600
Wire Wire Line
	3850 5600 3750 5600
Wire Wire Line
	4300 5700 4300 5800
Connection ~ 3850 5700
Wire Wire Line
	3850 6100 3900 6100
Connection ~ 3850 5900
Wire Wire Line
	4800 5250 4800 6200
Wire Wire Line
	4800 6100 4700 6100
Wire Wire Line
	3750 5400 4800 5400
Connection ~ 4800 5400
Wire Wire Line
	3750 5500 4800 5500
Connection ~ 4800 5500
Wire Wire Line
	4150 5200 3750 5200
Wire Wire Line
	4150 4700 4150 5200
Wire Wire Line
	4150 4700 5050 4700
Wire Wire Line
	4800 4700 4800 4800
Wire Wire Line
	3750 5100 4150 5100
Connection ~ 4150 5100
$Comp
L HVOUT #PWR018
U 1 1 5814E221
P 5050 4700
F 0 "#PWR018" H 5050 4500 50  0001 C CNN
F 1 "HVOUT" V 5050 4400 50  0000 L CNN
F 2 "" H 5050 4700 50  0000 C CNN
F 3 "" H 5050 4700 50  0000 C CNN
	1    5050 4700
	0    -1   -1   0   
$EndComp
Connection ~ 4800 4700
$Comp
L AGND #PWR019
U 1 1 5814E639
P 4800 6200
F 0 "#PWR019" H 4800 5950 50  0001 C CNN
F 1 "AGND" H 4800 6050 50  0000 C CNN
F 2 "" H 4800 6200 50  0000 C CNN
F 3 "" H 4800 6200 50  0000 C CNN
	1    4800 6200
	1    0    0    -1  
$EndComp
Connection ~ 4800 6100
$Comp
L TP TP2
U 1 1 581311E9
P 4450 4500
F 0 "TP2" H 4850 4500 60  0000 L CNN
F 1 "TP" H 4250 4350 60  0001 L CNN
F 2 "footprint:NICOMATIC_C12000B" H 4200 4650 60  0001 L CNN
F 3 "\\\\cern.ch\\dfs\\Applications\\Altium\\Datasheets\\NICOMATIC_C12000B.pdf" H 4250 3750 60  0001 L CNN
F 4 "Yes" H 4250 4250 60  0001 L CNN "Mounted"
F 5 "SMD Test Point" H 4250 4150 60  0001 L CNN "Part Description"
F 6 "NICOMATIC_C12000B" H 4250 4050 60  0001 L CNN "Part Number"
F 7 "1" H 4250 3950 60  0001 L CNN "Pin Count"
F 8 "Yes" H 4450 3950 60  0001 L CNN "SMD"
F 9 "No" H 4700 3950 60  0001 L CNN "Socket"
F 10 "None" H 4900 3950 60  0001 L CNN "Status"
F 11 "Miscellaneous" H 4250 3850 60  0001 L CNN "Table"
F 12 "CERN DEM JLC" H 4250 5300 60  0001 L CNN "Author"
F 13 "Test Point" H 4250 5200 60  0001 L CNN "Family"
F 14 "Standard" H 4800 5200 60  0001 L CNN "Component Kind"
F 15 "Standard" H 5300 5200 60  0001 L CNN "Component Type"
F 16 "1.5mm" H 4250 4800 60  0001 L CNN "ComponentHeight"
F 17 "3/25/2009" H 4250 5100 60  0001 L CNN "CreateDate"
F 18 "3/25/2009" H 4900 5100 60  0001 L CNN "LatestRevisionDate"
F 19 "NICOMATIC" H 4250 5000 60  0001 L CNN "Manufacturer"
F 20 "C12000B" H 4250 4900 60  0001 L CNN "Manufacturer Part Number"
F 21 "Test Point" H 4850 3650 60  0001 L CNN "Comment"
F 22 "Test Point" H 4250 3650 60  0001 L CNN "Description"
	1    4450 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4450 4500 4700 4500
Wire Wire Line
	4700 4500 4700 4700
Connection ~ 4700 4700
$EndSCHEMATC
