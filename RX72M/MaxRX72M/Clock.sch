EESchema Schematic File Version 4
LIBS:MaxRX72M-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
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
L Device:Crystal_Small Y?
U 1 1 5DC465B1
P 7050 3600
F 0 "Y?" H 7050 3825 50  0000 C CNN
F 1 "12MHz" H 7050 3734 50  0000 C CNN
F 2 "" H 7050 3600 50  0001 C CNN
F 3 "~" H 7050 3600 50  0001 C CNN
	1    7050 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal_Small Y?
U 1 1 5DC48EED
P 7050 4350
F 0 "Y?" H 7050 4575 50  0000 C CNN
F 1 "32.768K" H 7050 4484 50  0000 C CNN
F 2 "" H 7050 4350 50  0001 C CNN
F 3 "~" H 7050 4350 50  0001 C CNN
	1    7050 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3600 6800 3600
Wire Wire Line
	7150 3600 7350 3600
Wire Wire Line
	7350 3600 7350 3300
Wire Wire Line
	7350 3300 6350 3300
Wire Wire Line
	6350 4350 6800 4350
Wire Wire Line
	7150 4350 7350 4350
Wire Wire Line
	7350 4350 7350 4050
Wire Wire Line
	7350 4050 6350 4050
$Comp
L Device:C C?
U 1 1 5DC4FCCF
P 7550 4200
F 0 "C?" H 7665 4246 50  0000 L CNN
F 1 "12pF" H 7665 4155 50  0000 L CNN
F 2 "" H 7588 4050 50  0001 C CNN
F 3 "~" H 7550 4200 50  0001 C CNN
	1    7550 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DC50904
P 7550 3450
F 0 "C?" H 7665 3496 50  0000 L CNN
F 1 "8pF" H 7665 3405 50  0000 L CNN
F 2 "" H 7588 3300 50  0001 C CNN
F 3 "~" H 7550 3450 50  0001 C CNN
	1    7550 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DC533F5
P 7900 3950
F 0 "C?" H 8015 3996 50  0000 L CNN
F 1 "8pF" H 8015 3905 50  0000 L CNN
F 2 "" H 7938 3800 50  0001 C CNN
F 3 "~" H 7900 3950 50  0001 C CNN
	1    7900 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DC53989
P 7900 4700
F 0 "C?" H 8015 4746 50  0000 L CNN
F 1 "12pF" H 8015 4655 50  0000 L CNN
F 2 "" H 7938 4550 50  0001 C CNN
F 3 "~" H 7900 4700 50  0001 C CNN
	1    7900 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3300 7350 3300
Connection ~ 7350 3300
Wire Wire Line
	7900 3800 6800 3800
Wire Wire Line
	6800 3800 6800 3600
Connection ~ 6800 3600
Wire Wire Line
	6800 3600 6950 3600
Wire Wire Line
	6800 4350 6800 4550
Wire Wire Line
	6800 4550 7900 4550
Connection ~ 6800 4350
Wire Wire Line
	6800 4350 6950 4350
Wire Wire Line
	7550 3600 7550 3700
Wire Wire Line
	7550 3700 8250 3700
Wire Wire Line
	8250 3700 8250 4200
Wire Wire Line
	7550 4050 7350 4050
Connection ~ 7350 4050
Wire Wire Line
	7550 4450 8250 4450
Wire Wire Line
	7550 4350 7550 4450
Connection ~ 8250 4450
Wire Wire Line
	8250 4450 8250 4950
Wire Wire Line
	7900 4100 7900 4200
Wire Wire Line
	7900 4200 8250 4200
Connection ~ 8250 4200
Wire Wire Line
	8250 4200 8250 4450
Wire Wire Line
	7900 4850 7900 4950
Wire Wire Line
	7900 4950 8250 4950
Connection ~ 8250 4950
Wire Wire Line
	8250 4950 8250 5050
$Comp
L power:GND #PWR?
U 1 1 5DC584A5
P 8250 5050
F 0 "#PWR?" H 8250 4800 50  0001 C CNN
F 1 "GND" H 8255 4877 50  0000 C CNN
F 2 "" H 8250 5050 50  0001 C CNN
F 3 "" H 8250 5050 50  0001 C CNN
	1    8250 5050
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72M_176 U?
U 1 1 5DC5E0A8
P 5700 3800
F 0 "U?" H 5700 4755 50  0000 C CNN
F 1 "RX72M_176" H 5700 4664 50  0000 C CNN
F 2 "LQFP-176_24x24mm_Pitch0.5mm" H 5700 4573 50  0000 C CNN
F 3 "" H 5650 3500 50  0001 C CNN
	1    5700 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3300 4050 3300
Text GLabel 4050 3300 0    50   Output ~ 10
~RESET~
$EndSCHEMATC
