EESchema Schematic File Version 2  date 2014/04/18 16:16:18
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
LIBS:special
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
LIBS:akizuki
LIBS:renesas
LIBS:liion_mobile_battery-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "18 apr 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L IR2104 U1
U 1 1 5350C662
P 4300 2800
F 0 "U1" H 4450 3100 60  0000 C CNN
F 1 "IR2104" H 4150 2500 60  0000 C CNN
F 2 "" H 4450 3100 60  0000 C CNN
F 3 "" H 4450 3100 60  0000 C CNN
	1    4300 2800
	1    0    0    -1  
$EndComp
$Comp
L RSS100N03 U2
U 1 1 5350C671
P 5800 2600
F 0 "U2" H 5900 2900 60  0000 C CNN
F 1 "RSS100N03" H 5750 2300 60  0000 C CNN
F 2 "" H 5800 2600 60  0000 C CNN
F 3 "" H 5800 2600 60  0000 C CNN
	1    5800 2600
	1    0    0    -1  
$EndComp
$Comp
L RSS100N03 U3
U 1 1 5350C680
P 5800 3400
F 0 "U3" H 5900 3700 60  0000 C CNN
F 1 "RSS100N03" H 5750 3100 60  0000 C CNN
F 2 "" H 5800 3400 60  0000 C CNN
F 3 "" H 5800 3400 60  0000 C CNN
	1    5800 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2450 5450 2450
Wire Wire Line
	5200 2550 5450 2550
Wire Wire Line
	5200 2650 5450 2650
Wire Wire Line
	6100 3250 6350 3250
Wire Wire Line
	6350 3350 6100 3350
Wire Wire Line
	6350 3450 6100 3450
Wire Wire Line
	5200 2450 5200 3000
Wire Wire Line
	4950 3000 6350 3000
Wire Wire Line
	6350 3000 6350 3550
Connection ~ 5200 2550
Connection ~ 5200 2650
Connection ~ 6350 3250
Connection ~ 6350 3350
Wire Wire Line
	4750 2750 5450 2750
Wire Wire Line
	4750 2950 4850 2950
Wire Wire Line
	4850 2950 4850 3550
Wire Wire Line
	4850 3550 5450 3550
Wire Wire Line
	5450 3250 5200 3250
Wire Wire Line
	5200 3250 5200 3900
Wire Wire Line
	5450 3350 5200 3350
Connection ~ 5200 3350
Wire Wire Line
	5450 3450 5200 3450
Connection ~ 5200 3450
Wire Wire Line
	6100 2750 6350 2750
Wire Wire Line
	6350 2750 6350 2050
Wire Wire Line
	6100 2450 6350 2450
Connection ~ 6350 2450
Wire Wire Line
	6100 2550 6350 2550
Connection ~ 6350 2550
Wire Wire Line
	6100 2650 6350 2650
Connection ~ 6350 2650
$Comp
L VDD #PWR?
U 1 1 5350CB37
P 6350 2050
F 0 "#PWR?" H 6350 2150 30  0001 C CNN
F 1 "VDD" H 6350 2160 30  0000 C CNN
F 2 "" H 6350 2050 60  0000 C CNN
F 3 "" H 6350 2050 60  0000 C CNN
	1    6350 2050
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR?
U 1 1 5350CB64
P 5200 3900
F 0 "#PWR?" H 5200 3900 40  0001 C CNN
F 1 "AGND" H 5200 3830 50  0000 C CNN
F 2 "" H 5200 3900 60  0000 C CNN
F 3 "" H 5200 3900 60  0000 C CNN
	1    5200 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3550 6100 3550
Connection ~ 6350 3450
Wire Wire Line
	4750 2850 4950 2850
Wire Wire Line
	4950 2850 4950 3000
Connection ~ 5200 3000
$EndSCHEMATC
