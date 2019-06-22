EESchema Schematic File Version 4
LIBS:board-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
Title "256Mbits SDRAM"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2250 4900 0    50   Input ~ 0
~RAS
Text HLabel 2250 4800 0    50   Input ~ 0
~CAS
Text HLabel 2250 4700 0    50   Input ~ 0
~WE
Text HLabel 2250 4300 0    50   Input ~ 0
CKE
$Comp
L SDRAM:IS42S16160G-xT U?
U 1 1 5C670664
P 4900 3800
F 0 "U?" H 4350 5150 50  0000 C CNN
F 1 "IS42S16160G-xT" H 4000 2550 50  0000 C CNN
F 2 "Package_SO:TSOP-II-54_10.16x22.22mm_P0.8mm" H 4900 3900 50  0001 C CNN
F 3 "http://www.issi.com/WW/pdf/42-45S83200G-16160G.pdf" H 4300 5150 50  0001 C CNN
	1    4900 3800
	1    0    0    -1  
$EndComp
Text HLabel 3550 2800 0    50   Input ~ 0
A1
Text HLabel 3550 2900 0    50   Input ~ 0
A2
Text HLabel 3550 3000 0    50   Input ~ 0
A3
Text HLabel 3550 3100 0    50   Input ~ 0
A4
Text HLabel 3550 3200 0    50   Input ~ 0
A5
Text HLabel 3550 3300 0    50   Input ~ 0
A6
Text HLabel 3550 3400 0    50   Input ~ 0
A7
Text HLabel 3550 3500 0    50   Input ~ 0
A8
Text HLabel 3550 3600 0    50   Input ~ 0
A9
Text HLabel 3550 3700 0    50   Input ~ 0
A10
Text HLabel 3550 3800 0    50   Input ~ 0
A11
Text HLabel 3550 3900 0    50   Input ~ 0
A12
Text HLabel 3550 4000 0    50   Input ~ 0
A13
Text HLabel 3550 2600 0    50   Input ~ 0
A14
Text HLabel 3550 2700 0    50   Input ~ 0
A15
Wire Wire Line
	3550 2600 4100 2600
Wire Wire Line
	4100 2700 3550 2700
Wire Wire Line
	3550 2800 4100 2800
Wire Wire Line
	4100 2900 3550 2900
Wire Wire Line
	3550 3000 4100 3000
Wire Wire Line
	4100 3100 3550 3100
Wire Wire Line
	3550 3200 4100 3200
Wire Wire Line
	4100 3300 3550 3300
Wire Wire Line
	3550 3400 4100 3400
Wire Wire Line
	4100 3500 3550 3500
Wire Wire Line
	3550 3600 4100 3600
Wire Wire Line
	4100 3700 3550 3700
Wire Wire Line
	3550 3800 4100 3800
Wire Wire Line
	4100 3900 3550 3900
Wire Wire Line
	3550 4000 4100 4000
Text HLabel 6100 2600 2    50   BiDi ~ 0
D0
Text HLabel 6100 2700 2    50   BiDi ~ 0
D1
Text HLabel 6100 2800 2    50   BiDi ~ 0
D2
Text HLabel 6100 2900 2    50   BiDi ~ 0
D3
Text HLabel 6100 3000 2    50   BiDi ~ 0
D4
Text HLabel 6100 3100 2    50   BiDi ~ 0
D5
Text HLabel 6100 3200 2    50   BiDi ~ 0
D6
Text HLabel 6100 3300 2    50   BiDi ~ 0
D7
Text HLabel 6100 3400 2    50   BiDi ~ 0
D8
Text HLabel 6100 3500 2    50   BiDi ~ 0
D9
Text HLabel 6100 3600 2    50   BiDi ~ 0
D10
Text HLabel 6100 3700 2    50   BiDi ~ 0
D11
Text HLabel 6100 3800 2    50   BiDi ~ 0
D12
Text HLabel 6100 3900 2    50   BiDi ~ 0
D13
Text HLabel 6100 4000 2    50   BiDi ~ 0
D14
Text HLabel 6100 4100 2    50   BiDi ~ 0
D15
Wire Wire Line
	5700 2600 6100 2600
Wire Wire Line
	6100 2700 5700 2700
Wire Wire Line
	5700 2800 6100 2800
Wire Wire Line
	6100 2900 5700 2900
Wire Wire Line
	5700 3000 6100 3000
Wire Wire Line
	6100 3100 5700 3100
Wire Wire Line
	5700 3200 6100 3200
Wire Wire Line
	6100 3300 5700 3300
Wire Wire Line
	5700 3400 6100 3400
Wire Wire Line
	6100 3500 5700 3500
Wire Wire Line
	5700 3600 6100 3600
Wire Wire Line
	6100 3700 5700 3700
Wire Wire Line
	5700 3800 6100 3800
Wire Wire Line
	6100 3900 5700 3900
Wire Wire Line
	5700 4000 6100 4000
Wire Wire Line
	6100 4100 5700 4100
Wire Wire Line
	4600 5200 4600 5300
Wire Wire Line
	4600 5300 4700 5300
Wire Wire Line
	4700 5300 4700 5200
Wire Wire Line
	4700 5300 4800 5300
Wire Wire Line
	4800 5300 4800 5200
Connection ~ 4700 5300
Wire Wire Line
	4800 5300 4900 5300
Wire Wire Line
	4900 5300 4900 5200
Connection ~ 4800 5300
Wire Wire Line
	4900 5300 5000 5300
Wire Wire Line
	5000 5300 5000 5200
Connection ~ 4900 5300
Wire Wire Line
	5000 5300 5100 5300
Wire Wire Line
	5100 5300 5100 5200
Connection ~ 5000 5300
Wire Wire Line
	5100 5300 5200 5300
Wire Wire Line
	5200 5300 5200 5200
Connection ~ 5100 5300
Wire Wire Line
	4600 5300 4600 5400
Connection ~ 4600 5300
$Comp
L power:GND #PWR?
U 1 1 5C682401
P 4600 5400
F 0 "#PWR?" H 4600 5150 50  0001 C CNN
F 1 "GND" H 4605 5227 50  0000 C CNN
F 2 "" H 4600 5400 50  0001 C CNN
F 3 "" H 4600 5400 50  0001 C CNN
	1    4600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2300 4600 2200
Wire Wire Line
	4600 2200 4700 2200
Wire Wire Line
	4700 2200 4700 2300
Wire Wire Line
	4700 2200 4800 2200
Wire Wire Line
	4800 2200 4800 2300
Connection ~ 4700 2200
Wire Wire Line
	4800 2200 4900 2200
Wire Wire Line
	4900 2200 4900 2300
Connection ~ 4800 2200
Wire Wire Line
	4900 2200 5000 2200
Wire Wire Line
	5000 2200 5000 2300
Connection ~ 4900 2200
Wire Wire Line
	5000 2200 5100 2200
Wire Wire Line
	5100 2200 5100 2300
Connection ~ 5000 2200
Wire Wire Line
	5100 2200 5200 2200
Wire Wire Line
	5200 2200 5200 2300
Connection ~ 5100 2200
Wire Wire Line
	4600 2200 4600 2100
Connection ~ 4600 2200
$Comp
L power:+3.3V #PWR?
U 1 1 5C687E2D
P 4600 2100
F 0 "#PWR?" H 4600 1950 50  0001 C CNN
F 1 "+3.3V" H 4615 2273 50  0000 C CNN
F 2 "" H 4600 2100 50  0001 C CNN
F 3 "" H 4600 2100 50  0001 C CNN
	1    4600 2100
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C687E6E
P 7450 3150
F 0 "C?" H 7533 3203 60  0000 L CNN
F 1 "0.1uF" H 7533 3097 60  0000 L CNN
F 2 "" V 7450 3150 60  0000 C CNN
F 3 "" V 7450 3150 60  0000 C CNN
	1    7450 3150
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C687EF4
P 7850 3150
F 0 "C?" H 7933 3203 60  0000 L CNN
F 1 "0.1uF" H 7933 3097 60  0000 L CNN
F 2 "" V 7850 3150 60  0000 C CNN
F 3 "" V 7850 3150 60  0000 C CNN
	1    7850 3150
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C687F22
P 8250 3150
F 0 "C?" H 8333 3203 60  0000 L CNN
F 1 "0.1uF" H 8333 3097 60  0000 L CNN
F 2 "" V 8250 3150 60  0000 C CNN
F 3 "" V 8250 3150 60  0000 C CNN
	1    8250 3150
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C687F6C
P 8650 3150
F 0 "C?" H 8733 3203 60  0000 L CNN
F 1 "0.1uF" H 8733 3097 60  0000 L CNN
F 2 "" V 8650 3150 60  0000 C CNN
F 3 "" V 8650 3150 60  0000 C CNN
	1    8650 3150
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C687FA2
P 9050 3150
F 0 "C?" H 9133 3203 60  0000 L CNN
F 1 "0.1uF" H 9133 3097 60  0000 L CNN
F 2 "" V 9050 3150 60  0000 C CNN
F 3 "" V 9050 3150 60  0000 C CNN
	1    9050 3150
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C687FDE
P 9450 3150
F 0 "C?" H 9533 3203 60  0000 L CNN
F 1 "0.1uF" H 9533 3097 60  0000 L CNN
F 2 "" V 9450 3150 60  0000 C CNN
F 3 "" V 9450 3150 60  0000 C CNN
	1    9450 3150
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C688016
P 9850 3150
F 0 "C?" H 9933 3203 60  0000 L CNN
F 1 "0.1uF" H 9933 3097 60  0000 L CNN
F 2 "" V 9850 3150 60  0000 C CNN
F 3 "" V 9850 3150 60  0000 C CNN
	1    9850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3000 7450 2900
Wire Wire Line
	7450 2900 7850 2900
Wire Wire Line
	7850 2900 7850 3000
Wire Wire Line
	7850 2900 8250 2900
Wire Wire Line
	8250 2900 8250 3000
Connection ~ 7850 2900
Wire Wire Line
	8250 2900 8650 2900
Wire Wire Line
	8650 2900 8650 3000
Connection ~ 8250 2900
Wire Wire Line
	8650 2900 9050 2900
Wire Wire Line
	9050 2900 9050 3000
Connection ~ 8650 2900
Wire Wire Line
	9050 2900 9450 2900
Wire Wire Line
	9450 2900 9450 3000
Connection ~ 9050 2900
Wire Wire Line
	9450 2900 9850 2900
Wire Wire Line
	9850 2900 9850 3000
Connection ~ 9450 2900
Wire Wire Line
	7450 3300 7450 3400
Wire Wire Line
	7450 3400 7850 3400
Wire Wire Line
	7850 3400 7850 3300
Wire Wire Line
	7850 3400 8250 3400
Wire Wire Line
	8250 3400 8250 3300
Connection ~ 7850 3400
Wire Wire Line
	8250 3400 8650 3400
Wire Wire Line
	8650 3400 8650 3300
Connection ~ 8250 3400
Wire Wire Line
	8650 3400 9050 3400
Wire Wire Line
	9050 3400 9050 3300
Connection ~ 8650 3400
Wire Wire Line
	9050 3400 9450 3400
Wire Wire Line
	9450 3400 9450 3300
Connection ~ 9050 3400
Wire Wire Line
	9450 3400 9850 3400
Wire Wire Line
	9850 3400 9850 3300
Connection ~ 9450 3400
Wire Wire Line
	7450 2900 7450 2800
Connection ~ 7450 2900
Wire Wire Line
	7450 3400 7450 3500
Connection ~ 7450 3400
$Comp
L power:+3.3V #PWR?
U 1 1 5C6A0724
P 7450 2800
F 0 "#PWR?" H 7450 2650 50  0001 C CNN
F 1 "+3.3V" H 7465 2973 50  0000 C CNN
F 2 "" H 7450 2800 50  0001 C CNN
F 3 "" H 7450 2800 50  0001 C CNN
	1    7450 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C6A075D
P 7450 3500
F 0 "#PWR?" H 7450 3250 50  0001 C CNN
F 1 "GND" H 7455 3327 50  0000 C CNN
F 2 "" H 7450 3500 50  0001 C CNN
F 3 "" H 7450 3500 50  0001 C CNN
	1    7450 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4900 2350 4900
Wire Wire Line
	4100 4800 2650 4800
Wire Wire Line
	4100 4700 2950 4700
Text HLabel 2250 4200 0    50   Input ~ 0
~SDCS
Wire Wire Line
	4100 4200 2350 4200
Text HLabel 2250 4500 0    50   Input ~ 0
DQM0
Text HLabel 2250 4600 0    50   Input ~ 0
DQM1
Wire Wire Line
	4100 4500 2250 4500
Wire Wire Line
	2250 4600 4100 4600
Wire Wire Line
	4100 4300 3550 4300
Text HLabel 2250 4400 0    50   UnSpc ~ 0
SDCLK
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C7216D1
P 3150 4400
F 0 "R?" H 3150 4150 50  0000 C CNN
F 1 "0" H 3150 4400 50  0000 C CNN
F 2 "" V 3080 4400 50  0000 C CNN
F 3 "" H 3150 4400 50  0000 C CNN
	1    3150 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	4100 4400 3300 4400
Wire Wire Line
	3000 4400 2250 4400
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C7265C5
P 2350 3850
F 0 "R?" V 2350 3700 50  0000 L CNN
F 1 "4.7K" V 2350 3900 50  0000 L CNN
F 2 "" V 2280 3850 50  0000 C CNN
F 3 "" H 2350 3850 50  0000 C CNN
	1    2350 3850
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C726615
P 2350 5250
F 0 "R?" V 2300 5300 50  0000 L CNN
F 1 "4.7K" V 2400 5300 50  0000 L CNN
F 2 "" V 2280 5250 50  0000 C CNN
F 3 "" H 2350 5250 50  0000 C CNN
	1    2350 5250
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C726653
P 2650 5250
F 0 "R?" V 2600 5300 50  0000 L CNN
F 1 "4.7K" V 2700 5300 50  0000 L CNN
F 2 "" V 2580 5250 50  0000 C CNN
F 3 "" H 2650 5250 50  0000 C CNN
	1    2650 5250
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C726693
P 2950 5250
F 0 "R?" V 2900 5300 50  0000 L CNN
F 1 "4.7K" V 3000 5300 50  0000 L CNN
F 2 "" V 2880 5250 50  0000 C CNN
F 3 "" H 2950 5250 50  0000 C CNN
	1    2950 5250
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C72DECE
P 3550 5250
F 0 "R?" V 3500 5300 50  0000 L CNN
F 1 "4.7K" V 3600 5300 50  0000 L CNN
F 2 "" V 3480 5250 50  0000 C CNN
F 3 "" H 3550 5250 50  0000 C CNN
	1    3550 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 5100 3550 4300
Connection ~ 3550 4300
Wire Wire Line
	3550 4300 2250 4300
Wire Wire Line
	2350 4000 2350 4200
Connection ~ 2350 4200
Wire Wire Line
	2350 4200 2250 4200
Wire Wire Line
	2350 5100 2350 4900
Connection ~ 2350 4900
Wire Wire Line
	2350 4900 2250 4900
Wire Wire Line
	2650 5100 2650 4800
Connection ~ 2650 4800
Wire Wire Line
	2650 4800 2250 4800
Wire Wire Line
	2950 5100 2950 4700
Connection ~ 2950 4700
Wire Wire Line
	2950 4700 2250 4700
Wire Wire Line
	2350 5400 2350 5600
Wire Wire Line
	2350 5600 2650 5600
Wire Wire Line
	2650 5600 2650 5400
Wire Wire Line
	2650 5600 2950 5600
Wire Wire Line
	2950 5600 2950 5400
Connection ~ 2650 5600
Wire Wire Line
	2350 5600 2150 5600
Connection ~ 2350 5600
Wire Wire Line
	2350 3700 2350 3500
Wire Wire Line
	3550 5400 3550 5600
$Comp
L power:GND #PWR?
U 1 1 5C74DDD1
P 3550 5600
F 0 "#PWR?" H 3550 5350 50  0001 C CNN
F 1 "GND" H 3555 5427 50  0000 C CNN
F 2 "" H 3550 5600 50  0001 C CNN
F 3 "" H 3550 5600 50  0001 C CNN
	1    3550 5600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C74DE16
P 2350 3500
F 0 "#PWR?" H 2350 3350 50  0001 C CNN
F 1 "+3.3V" H 2365 3673 50  0000 C CNN
F 2 "" H 2350 3500 50  0001 C CNN
F 3 "" H 2350 3500 50  0001 C CNN
	1    2350 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C74DE54
P 2150 5600
F 0 "#PWR?" H 2150 5450 50  0001 C CNN
F 1 "+3.3V" V 2165 5728 50  0000 L CNN
F 2 "" H 2150 5600 50  0001 C CNN
F 3 "" H 2150 5600 50  0001 C CNN
	1    2150 5600
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
