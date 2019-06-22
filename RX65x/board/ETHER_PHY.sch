EESchema Schematic File Version 4
LIBS:board-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 8
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
L Interface_Ethernet:LAN8720A U2
U 1 1 5C72A19C
P 6000 3800
F 0 "U2" H 5350 4950 50  0000 C CNN
F 1 "LAN8720A" H 5300 2700 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm" H 6050 2750 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/8720a.pdf" H 5800 2850 50  0001 C CNN
	1    6000 3800
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:J0011D21BNL-akizuki J?
U 1 1 5C74EDFE
P 8750 3700
F 0 "J?" H 9328 3746 50  0000 L CNN
F 1 "J0011D21BNL" H 9328 3655 50  0000 L CNN
F 2 "" H 8750 3700 50  0001 C CNN
F 3 "" H 8750 3700 50  0001 C CNN
	1    8750 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3300 6800 3300
Wire Wire Line
	6800 3300 6800 3100
Wire Wire Line
	6800 3100 8000 3100
Wire Wire Line
	6700 3400 6900 3400
Wire Wire Line
	6900 3400 6900 3300
Wire Wire Line
	6900 3300 8000 3300
Wire Wire Line
	7000 3500 7000 3400
Wire Wire Line
	7000 3400 8000 3400
Wire Wire Line
	6700 3500 7000 3500
Wire Wire Line
	6700 3600 8000 3600
Wire Wire Line
	6000 2600 6000 2500
Wire Wire Line
	6000 2500 6100 2500
Wire Wire Line
	7900 2500 7900 3200
Wire Wire Line
	7900 3500 8000 3500
Wire Wire Line
	8000 3200 7900 3200
Connection ~ 7900 3200
Wire Wire Line
	7900 3200 7900 3500
Wire Wire Line
	6100 2600 6100 2500
Connection ~ 6100 2500
Wire Wire Line
	6100 2500 7900 2500
Wire Wire Line
	8000 3800 7900 3800
Wire Wire Line
	7900 3800 7900 4100
$Comp
L power:GND #PWR?
U 1 1 5C74F3B1
P 7900 4800
F 0 "#PWR?" H 7900 4550 50  0001 C CNN
F 1 "GND" H 7905 4627 50  0000 C CNN
F 2 "" H 7900 4800 50  0001 C CNN
F 3 "" H 7900 4800 50  0001 C CNN
	1    7900 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 2500 7900 2400
Connection ~ 7900 2500
$Comp
L power:+3.3V #PWR?
U 1 1 5C74F57D
P 7900 2400
F 0 "#PWR?" H 7900 2250 50  0001 C CNN
F 1 "+3.3V" H 7915 2573 50  0000 C CNN
F 2 "" H 7900 2400 50  0001 C CNN
F 3 "" H 7900 2400 50  0001 C CNN
	1    7900 2400
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C74F5AA
P 7650 4000
F 0 "R?" H 7650 3900 50  0000 C CNN
F 1 "330" H 7650 4000 50  0000 C CNN
F 2 "" V 7580 4000 50  0000 C CNN
F 3 "" H 7650 4000 50  0000 C CNN
	1    7650 4000
	-1   0    0    1   
$EndComp
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C74F61C
P 7650 4200
F 0 "R?" H 7650 4100 50  0000 C CNN
F 1 "330" H 7650 4200 50  0000 C CNN
F 2 "" V 7580 4200 50  0000 C CNN
F 3 "" H 7650 4200 50  0000 C CNN
	1    7650 4200
	-1   0    0    1   
$EndComp
Wire Wire Line
	7800 4000 8000 4000
Wire Wire Line
	8000 4200 7800 4200
Wire Wire Line
	8000 4100 7900 4100
Connection ~ 7900 4100
Wire Wire Line
	7900 4100 7900 4300
Wire Wire Line
	8000 4300 7900 4300
Connection ~ 7900 4300
Wire Wire Line
	7900 4300 7900 4800
Wire Wire Line
	7500 4000 7000 4000
Wire Wire Line
	7000 4000 7000 4200
Wire Wire Line
	7000 4200 6700 4200
Wire Wire Line
	6700 4100 7100 4100
Wire Wire Line
	7100 4100 7100 4200
Wire Wire Line
	7100 4200 7500 4200
Wire Wire Line
	6000 4900 6000 5100
$Comp
L power:GND #PWR?
U 1 1 5C750D3F
P 6000 5100
F 0 "#PWR?" H 6000 4850 50  0001 C CNN
F 1 "GND" H 6005 4927 50  0000 C CNN
F 2 "" H 6000 5100 50  0001 C CNN
F 3 "" H 6000 5100 50  0001 C CNN
	1    6000 5100
	1    0    0    -1  
$EndComp
Text HLabel 4050 4300 0    50   Input ~ 0
ET_R50CK
Wire Wire Line
	5200 4300 4050 4300
$EndSCHEMATC
