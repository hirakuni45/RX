EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector_Generic:Conn_01x04 J?
U 1 1 5F55B73B
P 10200 2300
F 0 "J?" H 10280 2292 50  0000 L CNN
F 1 "StepMotor" H 10280 2201 50  0000 L CNN
F 2 "" H 10200 2300 50  0001 C CNN
F 3 "~" H 10200 2300 50  0001 C CNN
	1    10200 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2200 10000 2200
Wire Wire Line
	8900 2300 10000 2300
Wire Wire Line
	9700 2400 10000 2400
Wire Wire Line
	10000 2500 9800 2500
Wire Wire Line
	8900 3100 9100 3100
$Comp
L power:GND #PWR?
U 1 1 5F55E3CD
P 9100 3600
F 0 "#PWR?" H 9100 3350 50  0001 C CNN
F 1 "GND" H 9105 3427 50  0000 C CNN
F 2 "" H 9100 3600 50  0001 C CNN
F 3 "" H 9100 3600 50  0001 C CNN
	1    9100 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3100 9100 3200
Wire Wire Line
	8900 3200 9100 3200
Connection ~ 9100 3200
Wire Wire Line
	9100 3200 9100 3300
Wire Wire Line
	8900 3300 9100 3300
Connection ~ 9100 3300
Wire Wire Line
	9100 3300 9100 3400
Wire Wire Line
	8900 3400 9100 3400
$Comp
L akizuki:A3967 U?
U 1 1 5F560802
P 8400 2750
F 0 "U?" H 8400 3665 50  0000 C CNN
F 1 "A3967" H 8400 3574 50  0000 C CNN
F 2 "" H 8400 3550 50  0001 C CNN
F 3 "" H 8400 3550 50  0001 C CNN
	1    8400 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2400 9700 2700
Wire Wire Line
	9700 2700 8900 2700
Wire Wire Line
	8900 2800 9800 2800
Wire Wire Line
	9800 2800 9800 2500
Wire Wire Line
	8900 2600 9000 2600
Wire Wire Line
	9000 2600 9000 2100
Wire Wire Line
	9000 2100 8900 2100
Connection ~ 9000 2100
$Comp
L power:+12V #PWR?
U 1 1 5F563ABF
P 9000 1300
F 0 "#PWR?" H 9000 1150 50  0001 C CNN
F 1 "+12V" H 9015 1473 50  0000 C CNN
F 2 "" H 9000 1300 50  0001 C CNN
F 3 "" H 9000 1300 50  0001 C CNN
	1    9000 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3600 9100 3500
Connection ~ 9100 3400
Wire Wire Line
	9600 2400 9600 3100
Wire Wire Line
	8900 2900 9300 2900
Wire Wire Line
	9300 2900 9300 3100
$Comp
L akizuki:R R?
U 1 1 5F56501E
P 9300 3250
F 0 "R?" V 9346 3180 50  0000 R CNN
F 1 "2" V 9255 3180 50  0000 R CNN
F 2 "" H 9300 3180 50  0000 C CNN
F 3 "" V 9300 3250 50  0000 C CNN
	1    9300 3250
	0    -1   -1   0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 5F565194
P 9600 3250
F 0 "R?" V 9554 3320 50  0000 L CNN
F 1 "2" V 9645 3320 50  0000 L CNN
F 2 "" H 9600 3180 50  0000 C CNN
F 3 "" V 9600 3250 50  0000 C CNN
	1    9600 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 2400 8900 2400
Wire Wire Line
	9300 3400 9300 3500
Wire Wire Line
	9300 3500 9600 3500
Wire Wire Line
	9600 3500 9600 3400
Wire Wire Line
	9300 3500 9100 3500
Connection ~ 9300 3500
Connection ~ 9100 3500
Wire Wire Line
	9100 3500 9100 3400
Text Notes 10450 2000 0    50   ~ 0
多摩川精機\nTS3692N65\n0.35A/Coil
Wire Wire Line
	7900 2750 7600 2750
$Comp
L power:+5V #PWR?
U 1 1 5F567255
P 7600 2750
F 0 "#PWR?" H 7600 2600 50  0001 C CNN
F 1 "+5V" V 7615 2878 50  0000 L CNN
F 2 "" H 7600 2750 50  0001 C CNN
F 3 "" H 7600 2750 50  0001 C CNN
	1    7600 2750
	0    -1   -1   0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 5F577A1C
P 7650 3650
F 0 "R?" V 7604 3720 50  0000 L CNN
F 1 "20K" V 7695 3720 50  0000 L CNN
F 2 "" H 7650 3580 50  0000 C CNN
F 3 "" V 7650 3650 50  0000 C CNN
	1    7650 3650
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 5F578D31
P 6800 3650
F 0 "R?" V 6754 3720 50  0000 L CNN
F 1 "20K" V 6845 3720 50  0000 L CNN
F 2 "" H 6800 3580 50  0000 C CNN
F 3 "" V 6800 3650 50  0000 C CNN
	1    6800 3650
	0    1    1    0   
$EndComp
$Comp
L akizuki:C C?
U 1 1 5F57961C
P 7200 3650
F 0 "C?" H 7283 3703 60  0000 L CNN
F 1 "680pF" H 7283 3597 60  0000 L CNN
F 2 "" V 7200 3650 60  0000 C CNN
F 3 "" V 7200 3650 60  0000 C CNN
	1    7200 3650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5F5797E7
P 6350 3650
F 0 "C?" H 6433 3703 60  0000 L CNN
F 1 "680pF" H 6433 3597 60  0000 L CNN
F 2 "" V 6350 3650 60  0000 C CNN
F 3 "" V 6350 3650 60  0000 C CNN
	1    6350 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3500 7200 3400
Wire Wire Line
	7200 3400 7650 3400
Wire Wire Line
	7650 3500 7650 3400
Connection ~ 7650 3400
Wire Wire Line
	7650 3400 7900 3400
Wire Wire Line
	6350 3500 6350 3300
Wire Wire Line
	6350 3300 6800 3300
Wire Wire Line
	6800 3500 6800 3300
Connection ~ 6800 3300
Wire Wire Line
	6800 3300 7900 3300
Wire Wire Line
	6350 3800 6350 3900
Wire Wire Line
	6350 3900 6800 3900
Wire Wire Line
	6800 3900 6800 3800
Wire Wire Line
	6800 3900 7000 3900
Wire Wire Line
	7200 3900 7200 3800
Connection ~ 6800 3900
Wire Wire Line
	7200 3900 7650 3900
Wire Wire Line
	7650 3900 7650 3800
Connection ~ 7200 3900
Wire Wire Line
	7000 3900 7000 4050
Connection ~ 7000 3900
Wire Wire Line
	7000 3900 7200 3900
$Comp
L power:GND #PWR?
U 1 1 5F581AEB
P 7000 4050
F 0 "#PWR?" H 7000 3800 50  0001 C CNN
F 1 "GND" H 7005 3877 50  0000 C CNN
F 2 "" H 7000 4050 50  0001 C CNN
F 3 "" H 7000 4050 50  0001 C CNN
	1    7000 4050
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5F581C72
P 9450 1600
F 0 "C?" H 9533 1653 60  0000 L CNN
F 1 "0.1uF" H 9533 1547 60  0000 L CNN
F 2 "" V 9450 1600 60  0000 C CNN
F 3 "" V 9450 1600 60  0000 C CNN
	1    9450 1600
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C-POL C?
U 1 1 5F58201B
P 9850 1600
F 0 "C?" H 9933 1653 60  0000 L CNN
F 1 "220uF" H 9933 1547 60  0000 L CNN
F 2 "" V 9850 1600 60  0000 C CNN
F 3 "" V 9850 1600 60  0000 C CNN
	1    9850 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1300 9000 1350
Connection ~ 9000 1350
Wire Wire Line
	9000 1350 9000 2100
Wire Wire Line
	9450 1750 9450 1850
Wire Wire Line
	9450 1850 9850 1850
Wire Wire Line
	9850 1850 9850 1750
Wire Wire Line
	9450 1850 9450 1950
Connection ~ 9450 1850
$Comp
L power:GND #PWR?
U 1 1 5F58782E
P 9450 1950
F 0 "#PWR?" H 9450 1700 50  0001 C CNN
F 1 "GND" H 9455 1777 50  0000 C CNN
F 2 "" H 9450 1950 50  0001 C CNN
F 3 "" H 9450 1950 50  0001 C CNN
	1    9450 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1350 9450 1350
Wire Wire Line
	9850 1450 9850 1350
Wire Wire Line
	9450 1450 9450 1350
Connection ~ 9450 1350
Wire Wire Line
	9450 1350 9850 1350
$EndSCHEMATC
