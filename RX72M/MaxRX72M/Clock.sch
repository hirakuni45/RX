EESchema Schematic File Version 4
LIBS:MaxRX72M-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 9
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5050 3300 4050 3300
Text GLabel 4050 3300 0    50   Input ~ 10
~RESET~
$Comp
L renesas:RX72M_176 U?
U 1 1 5E86C3E7
P 5650 3500
F 0 "U?" H 5650 4165 50  0000 C CNN
F 1 "RX72M_176" H 5650 4074 50  0000 C CNN
F 2 "Package_QFP:LQFP-176_24x24mm_P0.5mm" H 5700 1300 50  0001 C CNN
F 3 "" H 5600 3200 50  0001 C CNN
	1    5650 3500
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CRYSTAL X?
U 1 1 5E92D6B0
P 6800 3700
F 0 "X?" H 6703 3647 60  0000 R CNN
F 1 "12MHz" H 6703 3753 60  0000 R CNN
F 2 "" V 6800 3700 60  0000 C CNN
F 3 "" V 6800 3700 60  0000 C CNN
	1    6800 3700
	-1   0    0    1   
$EndComp
$Comp
L akizuki:CRYSTAL X?
U 1 1 5E9309AC
P 6800 3300
F 0 "X?" H 6892 3353 60  0000 L CNN
F 1 "32.768KHz" H 6892 3247 60  0000 L CNN
F 2 "" V 6800 3300 60  0000 C CNN
F 3 "" V 6800 3300 60  0000 C CNN
	1    6800 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3200 6350 3200
Wire Wire Line
	6350 3200 6350 3150
Wire Wire Line
	6350 3150 6800 3150
Wire Wire Line
	6250 3400 6350 3400
Wire Wire Line
	6350 3400 6350 3450
Wire Wire Line
	6350 3450 6600 3450
Wire Wire Line
	6250 3600 6350 3600
Wire Wire Line
	6350 3600 6350 3550
Wire Wire Line
	6350 3550 6800 3550
Wire Wire Line
	6250 3800 6350 3800
Wire Wire Line
	6350 3800 6350 3850
Wire Wire Line
	6350 3850 6600 3850
$Comp
L akizuki:C C?
U 1 1 5E9380C2
P 7500 3300
F 0 "C?" H 7582 3353 60  0000 L CNN
F 1 "12pF" H 7582 3247 60  0000 L CNN
F 2 "" V 7500 3300 60  0000 C CNN
F 3 "" V 7500 3300 60  0000 C CNN
	1    7500 3300
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5E93877B
P 7800 3300
F 0 "C?" H 7882 3353 60  0000 L CNN
F 1 "12pF" H 7882 3247 60  0000 L CNN
F 2 "" V 7800 3300 60  0000 C CNN
F 3 "" V 7800 3300 60  0000 C CNN
	1    7800 3300
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5E938D54
P 7500 3700
F 0 "C?" H 7583 3753 60  0000 L CNN
F 1 "8pF" H 7583 3647 60  0000 L CNN
F 2 "" V 7500 3700 60  0000 C CNN
F 3 "" V 7500 3700 60  0000 C CNN
	1    7500 3700
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5E93922B
P 7800 3700
F 0 "C?" H 7883 3753 60  0000 L CNN
F 1 "8pF" H 7883 3647 60  0000 L CNN
F 2 "" V 7800 3700 60  0000 C CNN
F 3 "" V 7800 3700 60  0000 C CNN
	1    7800 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 3550 7500 3550
Connection ~ 6800 3550
Wire Wire Line
	6800 3150 7500 3150
Connection ~ 6800 3150
Wire Wire Line
	6600 3450 6600 3000
Wire Wire Line
	6600 3000 7800 3000
Wire Wire Line
	7800 3000 7800 3150
Connection ~ 6600 3450
Wire Wire Line
	6600 3450 6800 3450
Wire Wire Line
	6600 3850 6600 4000
Wire Wire Line
	6600 4000 8100 4000
Wire Wire Line
	8100 4000 8100 3550
Wire Wire Line
	8100 3550 7800 3550
Connection ~ 6600 3850
Wire Wire Line
	6600 3850 6800 3850
Wire Wire Line
	7500 3450 7800 3450
Wire Wire Line
	7500 3850 7800 3850
Wire Wire Line
	7500 3450 7350 3450
Wire Wire Line
	7350 3450 7350 3850
Wire Wire Line
	7350 3850 7500 3850
Connection ~ 7500 3450
Connection ~ 7500 3850
Wire Wire Line
	7500 3850 7500 4150
$Comp
L power:GND #PWR?
U 1 1 5E93C283
P 7500 4150
F 0 "#PWR?" H 7500 3900 50  0001 C CNN
F 1 "GND" H 7505 3977 50  0000 C CNN
F 2 "" H 7500 4150 50  0001 C CNN
F 3 "" H 7500 4150 50  0001 C CNN
	1    7500 4150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
