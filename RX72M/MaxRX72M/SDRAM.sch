EESchema Schematic File Version 4
LIBS:MaxRX72M-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 9
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
L SDRAM:IS42S16160G-xT U?
U 1 1 5DBD840C
P 4450 4200
F 0 "U?" H 3900 5600 50  0000 C CNN
F 1 "IS42S16160G-xT" H 5400 3050 50  0000 C CNN
F 2 "Package_SO:TSOP-II-54_10.16x22.22mm_P0.8mm" H 4450 4300 50  0001 C CNN
F 3 "http://www.issi.com/WW/pdf/42-45S83200G-16160G.pdf" H 3850 5550 50  0001 C CNN
	1    4450 4200
	1    0    0    -1  
$EndComp
Text HLabel 5450 3000 2    50   BiDi ~ 10
D0
Text HLabel 5450 3100 2    50   BiDi ~ 10
D1
Text HLabel 5450 3200 2    50   BiDi ~ 10
D2
Text HLabel 5450 3300 2    50   BiDi ~ 10
D3
Text HLabel 5450 3400 2    50   BiDi ~ 10
D4
Text HLabel 5450 3500 2    50   BiDi ~ 10
D5
Text HLabel 5450 3600 2    50   BiDi ~ 10
D6
Text HLabel 5450 3700 2    50   BiDi ~ 10
D7
Text HLabel 5450 3800 2    50   BiDi ~ 10
D8
Text HLabel 5450 3900 2    50   BiDi ~ 10
D9
Text HLabel 5450 4000 2    50   BiDi ~ 10
D10
Text HLabel 5450 4100 2    50   BiDi ~ 10
D11
Text HLabel 5450 4200 2    50   BiDi ~ 10
D12
Text HLabel 5450 4300 2    50   BiDi ~ 10
D13
Text HLabel 5450 4400 2    50   BiDi ~ 10
D14
Text HLabel 5450 4500 2    50   BiDi ~ 10
D15
Wire Wire Line
	5250 3000 5450 3000
Wire Wire Line
	5450 3100 5250 3100
Wire Wire Line
	5250 3200 5450 3200
Wire Wire Line
	5450 3300 5250 3300
Wire Wire Line
	5250 3400 5450 3400
Wire Wire Line
	5450 3500 5250 3500
Wire Wire Line
	5250 3600 5450 3600
Wire Wire Line
	5450 3700 5250 3700
Wire Wire Line
	5250 3800 5450 3800
Wire Wire Line
	5450 3900 5250 3900
Wire Wire Line
	5250 4000 5450 4000
Wire Wire Line
	5450 4100 5250 4100
Wire Wire Line
	5250 4200 5450 4200
Wire Wire Line
	5450 4300 5250 4300
Wire Wire Line
	5250 4400 5450 4400
Wire Wire Line
	5450 4500 5250 4500
Text HLabel 3450 3200 0    50   Input ~ 10
A1
Text HLabel 3450 3300 0    50   Input ~ 10
A2
Text HLabel 3450 3400 0    50   Input ~ 10
A3
Text HLabel 3450 3500 0    50   Input ~ 10
A4
Text HLabel 3450 3600 0    50   Input ~ 10
A5
Text HLabel 3450 3700 0    50   Input ~ 10
A6
Text HLabel 3450 3800 0    50   Input ~ 10
A7
Text HLabel 3450 3900 0    50   Input ~ 10
A8
Text HLabel 3450 4000 0    50   Input ~ 10
A9
Text HLabel 3450 4100 0    50   Input ~ 10
A10
Text HLabel 3450 4200 0    50   Input ~ 10
A11
Text HLabel 3450 4300 0    50   Input ~ 10
A12
Text HLabel 3450 4400 0    50   Input ~ 10
A13
Text HLabel 3450 3000 0    50   Input ~ 10
A14
Text HLabel 3450 3100 0    50   Input ~ 10
A15
Wire Wire Line
	3450 3000 3650 3000
Wire Wire Line
	3650 3100 3450 3100
Wire Wire Line
	3450 3200 3650 3200
Wire Wire Line
	3650 3300 3450 3300
Wire Wire Line
	3450 3400 3650 3400
Wire Wire Line
	3650 3500 3450 3500
Wire Wire Line
	3450 3600 3650 3600
Wire Wire Line
	3650 3700 3450 3700
Wire Wire Line
	3450 3800 3650 3800
Wire Wire Line
	3650 3900 3450 3900
Wire Wire Line
	3450 4000 3650 4000
Wire Wire Line
	3650 4100 3450 4100
Wire Wire Line
	3450 4200 3650 4200
Wire Wire Line
	3650 4300 3450 4300
Wire Wire Line
	3450 4400 3650 4400
Text HLabel 3450 4800 0    50   Input ~ 10
SDCLK
Text HLabel 3450 4600 0    50   Input ~ 10
~SDCS~
Text HLabel 3450 4700 0    50   Input ~ 10
CKE
Text HLabel 3450 4900 0    50   Input ~ 10
DQM0
Text HLabel 3450 5000 0    50   Input ~ 10
DQM1
Text HLabel 3450 5100 0    50   Input ~ 10
~WE~
Text HLabel 3450 5200 0    50   Input ~ 10
~CAS~
Text HLabel 3450 5300 0    50   Input ~ 10
~RAS~
Wire Wire Line
	3450 4600 3650 4600
Wire Wire Line
	3450 4700 3650 4700
Wire Wire Line
	3450 4800 3650 4800
Wire Wire Line
	3450 4900 3650 4900
Wire Wire Line
	3450 5000 3650 5000
Wire Wire Line
	3450 5100 3650 5100
Wire Wire Line
	3450 5200 3650 5200
Wire Wire Line
	3450 5300 3650 5300
$Comp
L Device:C C?
U 1 1 5DBF9E02
P 6650 3000
F 0 "C?" H 6765 3046 50  0000 L CNN
F 1 "0.1uF" H 6765 2955 50  0000 L CNN
F 2 "" H 6688 2850 50  0001 C CNN
F 3 "~" H 6650 3000 50  0001 C CNN
	1    6650 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DBFA5A1
P 7100 3000
F 0 "C?" H 7215 3046 50  0000 L CNN
F 1 "0.1uF" H 7215 2955 50  0000 L CNN
F 2 "" H 7138 2850 50  0001 C CNN
F 3 "~" H 7100 3000 50  0001 C CNN
	1    7100 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DBFAFBC
P 7550 3000
F 0 "C?" H 7665 3046 50  0000 L CNN
F 1 "0.1uF" H 7665 2955 50  0000 L CNN
F 2 "" H 7588 2850 50  0001 C CNN
F 3 "~" H 7550 3000 50  0001 C CNN
	1    7550 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DBFB365
P 8000 3000
F 0 "C?" H 8115 3046 50  0000 L CNN
F 1 "0.1uF" H 8115 2955 50  0000 L CNN
F 2 "" H 8038 2850 50  0001 C CNN
F 3 "~" H 8000 3000 50  0001 C CNN
	1    8000 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DBFB4E4
P 8450 3000
F 0 "C?" H 8565 3046 50  0000 L CNN
F 1 "0.1uF" H 8565 2955 50  0000 L CNN
F 2 "" H 8488 2850 50  0001 C CNN
F 3 "~" H 8450 3000 50  0001 C CNN
	1    8450 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DBFE89C
P 4150 5800
F 0 "#PWR?" H 4150 5550 50  0001 C CNN
F 1 "GND" H 4155 5627 50  0000 C CNN
F 2 "" H 4150 5800 50  0001 C CNN
F 3 "" H 4150 5800 50  0001 C CNN
	1    4150 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 5600 4150 5700
Wire Wire Line
	4150 5700 4250 5700
Wire Wire Line
	4250 5700 4250 5600
Connection ~ 4150 5700
Wire Wire Line
	4150 5700 4150 5800
Wire Wire Line
	4250 5700 4350 5700
Wire Wire Line
	4350 5700 4350 5600
Connection ~ 4250 5700
Wire Wire Line
	4350 5700 4450 5700
Wire Wire Line
	4450 5700 4450 5600
Connection ~ 4350 5700
Wire Wire Line
	4450 5700 4550 5700
Wire Wire Line
	4550 5700 4550 5600
Connection ~ 4450 5700
Wire Wire Line
	4550 5700 4650 5700
Wire Wire Line
	4650 5700 4650 5600
Connection ~ 4550 5700
Wire Wire Line
	4650 5700 4750 5700
Wire Wire Line
	4750 5700 4750 5600
Connection ~ 4650 5700
$Comp
L power:+3.3V #PWR?
U 1 1 5DC067AA
P 4150 2500
F 0 "#PWR?" H 4150 2350 50  0001 C CNN
F 1 "+3.3V" H 4165 2673 50  0000 C CNN
F 2 "" H 4150 2500 50  0001 C CNN
F 3 "" H 4150 2500 50  0001 C CNN
	1    4150 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2700 4150 2600
Wire Wire Line
	4250 2700 4250 2600
Wire Wire Line
	4250 2600 4150 2600
Connection ~ 4150 2600
Wire Wire Line
	4150 2600 4150 2500
Wire Wire Line
	4350 2700 4350 2600
Wire Wire Line
	4350 2600 4250 2600
Connection ~ 4250 2600
Wire Wire Line
	4450 2700 4450 2600
Wire Wire Line
	4450 2600 4350 2600
Connection ~ 4350 2600
Wire Wire Line
	4550 2700 4550 2600
Wire Wire Line
	4550 2600 4450 2600
Connection ~ 4450 2600
Wire Wire Line
	4650 2700 4650 2600
Wire Wire Line
	4650 2600 4550 2600
Connection ~ 4550 2600
Wire Wire Line
	4750 2700 4750 2600
Wire Wire Line
	4750 2600 4650 2600
Connection ~ 4650 2600
$Comp
L power:+3.3V #PWR?
U 1 1 5DC12D86
P 6650 2650
F 0 "#PWR?" H 6650 2500 50  0001 C CNN
F 1 "+3.3V" H 6665 2823 50  0000 C CNN
F 2 "" H 6650 2650 50  0001 C CNN
F 3 "" H 6650 2650 50  0001 C CNN
	1    6650 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2850 6650 2750
Wire Wire Line
	6650 2750 7100 2750
Wire Wire Line
	7100 2750 7100 2850
Connection ~ 6650 2750
Wire Wire Line
	6650 2750 6650 2650
Wire Wire Line
	7100 2750 7550 2750
Wire Wire Line
	7550 2750 7550 2850
Connection ~ 7100 2750
Wire Wire Line
	7550 2750 8000 2750
Wire Wire Line
	8000 2750 8000 2850
Connection ~ 7550 2750
Wire Wire Line
	8000 2750 8450 2750
Wire Wire Line
	8450 2750 8450 2850
Connection ~ 8000 2750
$Comp
L power:GND #PWR?
U 1 1 5DC1B628
P 6650 3350
F 0 "#PWR?" H 6650 3100 50  0001 C CNN
F 1 "GND" H 6655 3177 50  0000 C CNN
F 2 "" H 6650 3350 50  0001 C CNN
F 3 "" H 6650 3350 50  0001 C CNN
	1    6650 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3350 6650 3250
Wire Wire Line
	6650 3250 7100 3250
Wire Wire Line
	7100 3250 7100 3150
Connection ~ 6650 3250
Wire Wire Line
	6650 3250 6650 3150
Wire Wire Line
	7100 3250 7550 3250
Wire Wire Line
	7550 3250 7550 3150
Connection ~ 7100 3250
Wire Wire Line
	7550 3250 8000 3250
Wire Wire Line
	8000 3250 8000 3150
Connection ~ 7550 3250
Wire Wire Line
	8000 3250 8450 3250
Wire Wire Line
	8450 3250 8450 3150
Connection ~ 8000 3250
$Comp
L Device:C C?
U 1 1 5DBA7B66
P 8900 3000
F 0 "C?" H 9015 3046 50  0000 L CNN
F 1 "0.1uF" H 9015 2955 50  0000 L CNN
F 2 "" H 8938 2850 50  0001 C CNN
F 3 "~" H 8900 3000 50  0001 C CNN
	1    8900 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DBA831C
P 9350 3000
F 0 "C?" H 9465 3046 50  0000 L CNN
F 1 "0.1uF" H 9465 2955 50  0000 L CNN
F 2 "" H 9388 2850 50  0001 C CNN
F 3 "~" H 9350 3000 50  0001 C CNN
	1    9350 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2850 8900 2750
Wire Wire Line
	8900 2750 8450 2750
Connection ~ 8450 2750
Wire Wire Line
	8900 3150 8900 3250
Wire Wire Line
	8900 3250 8450 3250
Connection ~ 8450 3250
Wire Wire Line
	9350 3150 9350 3250
Wire Wire Line
	9350 3250 8900 3250
Connection ~ 8900 3250
Wire Wire Line
	9350 2850 9350 2750
Wire Wire Line
	9350 2750 8900 2750
Connection ~ 8900 2750
$EndSCHEMATC
