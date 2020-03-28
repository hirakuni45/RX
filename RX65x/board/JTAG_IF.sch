EESchema Schematic File Version 4
LIBS:board-cache
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
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J1
U 1 1 5C729D96
P 5150 2700
F 0 "J1" H 5200 3150 50  0000 C CNN
F 1 "JTAG" H 5200 2250 50  0000 C CNN
F 2 "" H 5150 2700 50  0001 C CNN
F 3 "~" H 5150 2700 50  0001 C CNN
	1    5150 2700
	1    0    0    -1  
$EndComp
Text HLabel 2250 3000 0    50   Input ~ 0
~RES
Text HLabel 2250 2700 0    50   Input ~ 0
MD
Text HLabel 2250 2150 0    50   Input ~ 0
EMLE
Text HLabel 2250 2600 0    50   Input ~ 0
TDO
Text HLabel 2250 2400 0    50   Input ~ 0
TCK
Text HLabel 2250 2900 0    50   Input ~ 0
TDI
Text HLabel 2250 2800 0    50   Input ~ 0
TMS
Text HLabel 2250 2500 0    50   Input ~ 0
~TRST
Wire Wire Line
	5450 2500 5750 2500
Wire Wire Line
	5750 2500 5750 2150
Wire Wire Line
	5750 2150 2250 2150
Wire Wire Line
	4950 3000 4350 3000
Wire Wire Line
	4950 2900 4050 2900
Wire Wire Line
	4950 2800 3750 2800
Wire Wire Line
	4950 2700 3450 2700
Wire Wire Line
	4950 2600 3150 2600
Wire Wire Line
	4950 2400 2850 2400
Wire Wire Line
	5450 2400 5600 2400
Wire Wire Line
	5600 2400 5600 2900
Wire Wire Line
	5600 2900 5450 2900
Wire Wire Line
	5450 3000 5600 3000
Wire Wire Line
	5600 3000 5600 2900
Connection ~ 5600 2900
Wire Wire Line
	5600 3000 5600 3200
Connection ~ 5600 3000
$Comp
L power:GND #PWR?
U 1 1 5CAFEC79
P 5600 3200
F 0 "#PWR?" H 5600 2950 50  0001 C CNN
F 1 "GND" H 5605 3027 50  0000 C CNN
F 2 "" H 5600 3200 50  0001 C CNN
F 3 "" H 5600 3200 50  0001 C CNN
	1    5600 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2700 5950 2700
Wire Wire Line
	5950 2700 5950 1950
$Comp
L power:+3.3V #PWR?
U 1 1 5CAFEE21
P 5950 1950
F 0 "#PWR?" H 5950 1800 50  0001 C CNN
F 1 "+3.3V" H 5965 2123 50  0000 C CNN
F 2 "" H 5950 1950 50  0001 C CNN
F 3 "" H 5950 1950 50  0001 C CNN
	1    5950 1950
	1    0    0    -1  
$EndComp
Text Notes 4350 3250 0    50   ~ 0
RENESAS External Programmer
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J?
U 1 1 5C66AC75
P 4700 4100
F 0 "J?" H 4750 4350 50  0000 C CNN
F 1 "SCI1" H 4750 3850 50  0000 C CNN
F 2 "" H 4700 4100 50  0001 C CNN
F 3 "~" H 4700 4100 50  0001 C CNN
	1    4700 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2600 2850 4000
Wire Wire Line
	2850 4000 4500 4000
Connection ~ 2850 2600
Wire Wire Line
	2850 2600 2250 2600
Wire Wire Line
	2950 2900 2950 3750
Wire Wire Line
	5150 3750 5150 4000
Wire Wire Line
	5150 4000 5000 4000
Connection ~ 2950 2900
Wire Wire Line
	2950 2900 2250 2900
Wire Wire Line
	4300 4100 4300 4600
$Comp
L power:GND #PWR?
U 1 1 5C66B569
P 4300 5050
F 0 "#PWR?" H 4300 4800 50  0001 C CNN
F 1 "GND" H 4305 4877 50  0000 C CNN
F 2 "" H 4300 5050 50  0001 C CNN
F 3 "" H 4300 5050 50  0001 C CNN
	1    4300 5050
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66B596
P 6150 2400
F 0 "R?" V 6104 2470 50  0000 L CNN
F 1 "4.7K" V 6195 2470 50  0000 L CNN
F 2 "" H 6150 2330 50  0000 C CNN
F 3 "" V 6150 2400 50  0000 C CNN
	1    6150 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 2150 6150 2150
Wire Wire Line
	6150 2150 6150 2250
Connection ~ 5750 2150
Wire Wire Line
	5600 3000 6150 3000
Wire Wire Line
	6150 3000 6150 2550
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66BF5E
P 3600 3350
F 0 "R?" V 3554 3420 50  0000 L CNN
F 1 "4.7K" V 3645 3420 50  0000 L CNN
F 2 "" H 3600 3280 50  0000 C CNN
F 3 "" V 3600 3350 50  0000 C CNN
	1    3600 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 3200 3600 2500
Wire Wire Line
	3600 3500 3600 4100
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66C9B0
P 2850 1800
F 0 "R?" V 2804 1870 50  0000 L CNN
F 1 "4.7K" V 2895 1870 50  0000 L CNN
F 2 "" H 2850 1730 50  0000 C CNN
F 3 "" V 2850 1800 50  0000 C CNN
	1    2850 1800
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66C9F0
P 3150 1800
F 0 "R?" V 3196 1730 50  0000 R CNN
F 1 "4.7K" V 3105 1730 50  0000 R CNN
F 2 "" H 3150 1730 50  0000 C CNN
F 3 "" V 3150 1800 50  0000 C CNN
	1    3150 1800
	0    -1   -1   0   
$EndComp
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66CA53
P 3450 1800
F 0 "R?" V 3404 1870 50  0000 L CNN
F 1 "4.7K" V 3495 1870 50  0000 L CNN
F 2 "" H 3450 1730 50  0000 C CNN
F 3 "" V 3450 1800 50  0000 C CNN
	1    3450 1800
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66CABD
P 3750 1800
F 0 "R?" V 3704 1870 50  0000 L CNN
F 1 "4.7K" V 3795 1870 50  0000 L CNN
F 2 "" H 3750 1730 50  0000 C CNN
F 3 "" V 3750 1800 50  0000 C CNN
	1    3750 1800
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66CB0A
P 4050 1800
F 0 "R?" V 4004 1870 50  0000 L CNN
F 1 "4.7K" V 4095 1870 50  0000 L CNN
F 2 "" H 4050 1730 50  0000 C CNN
F 3 "" V 4050 1800 50  0000 C CNN
	1    4050 1800
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C66CB6A
P 4350 1800
F 0 "R?" V 4304 1870 50  0000 L CNN
F 1 "4.7K" V 4395 1870 50  0000 L CNN
F 2 "" H 4350 1730 50  0000 C CNN
F 3 "" V 4350 1800 50  0000 C CNN
	1    4350 1800
	0    1    1    0   
$EndComp
Text Notes 4550 4450 0    50   ~ 0
SCI/BOOT
Wire Wire Line
	2850 1950 2850 2400
Connection ~ 2850 2400
Wire Wire Line
	2850 2400 2250 2400
Wire Wire Line
	3150 1950 3150 2600
Connection ~ 3150 2600
Wire Wire Line
	3150 2600 2850 2600
Wire Wire Line
	3450 1950 3450 2700
Connection ~ 3450 2700
Wire Wire Line
	3450 2700 2750 2700
Connection ~ 3600 2500
Wire Wire Line
	3600 2500 2250 2500
Wire Wire Line
	3600 2500 4950 2500
Wire Wire Line
	3750 1950 3750 2800
Connection ~ 3750 2800
Wire Wire Line
	3750 2800 2250 2800
Wire Wire Line
	4050 1950 4050 2900
Connection ~ 4050 2900
Wire Wire Line
	4050 2900 2950 2900
Wire Wire Line
	4350 1950 4350 3000
Connection ~ 4350 3000
Wire Wire Line
	4350 3000 3150 3000
Wire Wire Line
	2850 1650 2850 1450
Wire Wire Line
	2850 1450 3150 1450
Wire Wire Line
	3150 1450 3150 1650
Wire Wire Line
	3150 1450 3450 1450
Wire Wire Line
	3450 1450 3450 1650
Connection ~ 3150 1450
Wire Wire Line
	3450 1450 3750 1450
Wire Wire Line
	3750 1450 3750 1650
Connection ~ 3450 1450
Wire Wire Line
	3750 1450 4050 1450
Wire Wire Line
	4050 1450 4050 1650
Connection ~ 3750 1450
Wire Wire Line
	4050 1450 4350 1450
Wire Wire Line
	4350 1450 4350 1650
Connection ~ 4050 1450
Wire Wire Line
	4350 1450 4350 1250
Connection ~ 4350 1450
$Comp
L power:+3.3V #PWR?
U 1 1 5C67A15D
P 4350 1250
F 0 "#PWR?" H 4350 1100 50  0001 C CNN
F 1 "+3.3V" H 4365 1423 50  0000 C CNN
F 2 "" H 4350 1250 50  0001 C CNN
F 3 "" H 4350 1250 50  0001 C CNN
	1    4350 1250
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:Shotkey-akizuki-board-rescue D?
U 1 1 5C67A1CB
P 4300 3750
F 0 "D?" V 4200 3750 60  0000 C CNN
F 1 "Shotkey" V 4400 3750 60  0000 C CNN
F 2 "" V 4295 3715 60  0000 C CNN
F 3 "" V 4295 3715 60  0000 C CNN
	1    4300 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 3750 5150 3750
Wire Wire Line
	4150 3750 2950 3750
$Comp
L board-rescue:2P-SW-akizuki-board-rescue SW?
U 1 1 5C67C4B4
P 3600 4600
F 0 "SW?" H 3600 4800 60  0000 C CNN
F 1 "RESET" H 3600 4400 60  0000 C CNN
F 2 "" H 3605 4600 60  0000 C CNN
F 3 "" H 3605 4600 60  0000 C CNN
	1    3600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4100 4300 4100
Connection ~ 4300 4100
Wire Wire Line
	4300 4100 4500 4100
Wire Wire Line
	3850 4600 4300 4600
Connection ~ 4300 4600
Wire Wire Line
	4300 4600 4300 5050
Wire Wire Line
	3150 3000 3150 4600
Wire Wire Line
	3150 4600 3350 4600
Connection ~ 3150 3000
Wire Wire Line
	3150 3000 2250 3000
$Comp
L Connector_Generic:Conn_02x01 J?
U 1 1 5C659E01
P 5650 4900
F 0 "J?" H 5700 5050 50  0000 C CNN
F 1 "Conn_02x01" H 5700 4750 50  0000 C CNN
F 2 "" H 5650 4900 50  0001 C CNN
F 3 "~" H 5650 4900 50  0001 C CNN
	1    5650 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4900 6150 4900
Wire Wire Line
	6150 4900 6150 4650
$Comp
L power:+3.3V #PWR?
U 1 1 5C65C8AC
P 6150 4650
F 0 "#PWR?" H 6150 4500 50  0001 C CNN
F 1 "+3.3V" H 6165 4823 50  0000 C CNN
F 2 "" H 6150 4650 50  0001 C CNN
F 3 "" H 6150 4650 50  0001 C CNN
	1    6150 4650
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:3P-SW-akizuki-board-rescue SW?
U 1 1 5C65C94A
P 3050 5200
F 0 "SW?" H 3177 5258 60  0000 L CNN
F 1 "RUN/BOOT" H 3177 5152 60  0000 L CNN
F 2 "" H 3035 5200 60  0000 C CNN
F 3 "" H 3035 5200 60  0000 C CNN
	1    3050 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 2700 2750 5200
Wire Wire Line
	2750 5200 2850 5200
Connection ~ 2750 2700
Wire Wire Line
	2750 2700 2250 2700
Wire Wire Line
	2850 5350 2750 5350
Wire Wire Line
	2750 5350 2750 5600
$Comp
L power:GND #PWR?
U 1 1 5C66B98B
P 2750 5600
F 0 "#PWR?" H 2750 5350 50  0001 C CNN
F 1 "GND" H 2755 5427 50  0000 C CNN
F 2 "" H 2750 5600 50  0001 C CNN
F 3 "" H 2750 5600 50  0001 C CNN
	1    2750 5600
	1    0    0    -1  
$EndComp
Text HLabel 2200 3600 0    50   Input ~ 0
UB
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C6F121E
P 5750 4100
F 0 "R?" V 5704 4170 50  0000 L CNN
F 1 "10K" V 5795 4170 50  0000 L CNN
F 2 "" H 5750 4030 50  0000 C CNN
F 3 "" V 5750 4100 50  0000 C CNN
	1    5750 4100
	0    1    1    0   
$EndComp
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C6F12B6
P 5200 3600
F 0 "R?" H 5200 3807 50  0000 C CNN
F 1 "10K" H 5200 3716 50  0000 C CNN
F 2 "" H 5200 3530 50  0000 C CNN
F 3 "" V 5200 3600 50  0000 C CNN
	1    5200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3600 2200 3600
Wire Wire Line
	5350 3600 5750 3600
Wire Wire Line
	5750 3600 5750 2800
Wire Wire Line
	5750 2800 5450 2800
Wire Wire Line
	5750 3950 5750 3600
Connection ~ 5750 3600
Wire Wire Line
	4300 4600 5750 4600
Wire Wire Line
	5750 4600 5750 4250
Wire Wire Line
	5450 4900 5150 4900
Wire Wire Line
	5150 4900 5150 4100
Wire Wire Line
	5150 4100 5000 4100
$EndSCHEMATC
