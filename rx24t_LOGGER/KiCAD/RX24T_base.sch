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
LIBS:akizuki
LIBS:analog
LIBS:ftdi
LIBS:renesas
LIBS:MotorLogger-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L RX24T U?
U 1 1 598D66E6
P 5400 3600
F 0 "U?" H 4725 975 60  0000 C CNN
F 1 "RX24T" H 6025 6225 60  0000 C CNN
F 2 "" H 4725 975 60  0000 C CNN
F 3 "" H 4725 975 60  0000 C CNN
	1    5400 3600
	1    0    0    -1  
$EndComp
Text HLabel 2200 2350 0    60   Output ~ 0
TXD
Text HLabel 2200 2500 0    60   Output ~ 0
RXD
$Comp
L CRYSTAL X?
U 1 1 598D9363
P 3400 2250
F 0 "X?" V 3550 2250 60  0000 C CNN
F 1 "10MHz" V 3250 2250 60  0000 C CNN
F 2 "" V 3400 2250 60  0000 C CNN
F 3 "" V 3400 2250 60  0000 C CNN
	1    3400 2250
	0    1    1    0   
$EndComp
$Comp
L CAP C?
U 1 1 598D9414
P 2900 2150
F 0 "C?" V 3000 2250 60  0000 C CNN
F 1 "22pF" V 2800 2050 60  0000 C CNN
F 2 "" V 2900 2150 60  0000 C CNN
F 3 "" V 2900 2150 60  0000 C CNN
	1    2900 2150
	0    1    1    0   
$EndComp
$Comp
L CAP C?
U 1 1 598D945D
P 2900 2350
F 0 "C?" V 3000 2450 60  0000 C CNN
F 1 "22pF" V 2800 2250 60  0000 C CNN
F 2 "" V 2900 2350 60  0000 C CNN
F 3 "" V 2900 2350 60  0000 C CNN
	1    2900 2350
	0    1    1    0   
$EndComp
$Comp
L CAP C?
U 1 1 598D9482
P 3450 1550
F 0 "C?" V 3550 1650 60  0000 C CNN
F 1 "CAP" V 3350 1450 60  0000 C CNN
F 2 "" V 3450 1550 60  0000 C CNN
F 3 "" V 3450 1550 60  0000 C CNN
	1    3450 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 1550 3600 1550
Wire Wire Line
	2600 1550 3300 1550
$Comp
L GND #PWR?
U 1 1 598D952D
P 2600 2550
F 0 "#PWR?" H 2600 2300 50  0001 C CNN
F 1 "GND" H 2600 2400 50  0000 C CNN
F 2 "" H 2600 2550 50  0000 C CNN
F 3 "" H 2600 2550 50  0000 C CNN
	1    2600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2550 2600 1550
Wire Wire Line
	3050 2150 4450 2150
Wire Wire Line
	3050 2350 4450 2350
Wire Wire Line
	3250 2250 3150 2250
Wire Wire Line
	3150 2250 3150 2150
Connection ~ 3150 2150
Wire Wire Line
	3550 2250 3700 2250
Wire Wire Line
	3700 2250 3700 2350
Connection ~ 3700 2350
Wire Wire Line
	2750 2150 2600 2150
Connection ~ 2600 2150
Wire Wire Line
	2750 2350 2600 2350
Connection ~ 2600 2350
Wire Wire Line
	4450 1350 4300 1350
Wire Wire Line
	4300 1350 4300 6450
Wire Wire Line
	4300 2250 4450 2250
Wire Wire Line
	4300 5450 4450 5450
Connection ~ 4300 2250
Wire Wire Line
	4450 4150 4300 4150
Connection ~ 4300 4150
Connection ~ 4300 5450
$Comp
L GND #PWR?
U 1 1 598D985C
P 4300 6450
F 0 "#PWR?" H 4300 6200 50  0001 C CNN
F 1 "GND" H 4300 6300 50  0000 C CNN
F 2 "" H 4300 6450 50  0000 C CNN
F 3 "" H 4300 6450 50  0000 C CNN
	1    4300 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2450 4100 2450
Wire Wire Line
	4100 900  4100 5250
Wire Wire Line
	4100 3950 4450 3950
Connection ~ 4100 2450
Wire Wire Line
	4100 5250 4450 5250
Connection ~ 4100 3950
$Comp
L +3.3V #PWR?
U 1 1 598D98F6
P 4100 900
F 0 "#PWR?" H 4100 750 50  0001 C CNN
F 1 "+3.3V" H 4100 1040 50  0000 C CNN
F 2 "" H 4100 900 50  0000 C CNN
F 3 "" H 4100 900 50  0000 C CNN
	1    4100 900 
	1    0    0    -1  
$EndComp
$EndSCHEMATC
