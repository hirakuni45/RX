EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
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
L Connector:Micro_SD_Card_Det_Hirose_DM3AT J?
U 1 1 6107910E
P 7650 3600
F 0 "J?" H 7600 4417 50  0000 C CNN
F 1 "Micro_SD_Card_Det_Hirose_DM3AT" H 7600 4326 50  0000 C CNN
F 2 "" H 9700 4300 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 7650 3700 50  0001 C CNN
	1    7650 3600
	1    0    0    -1  
$EndComp
Text HLabel 2750 3250 0    50   BiDi ~ 0
MOSI
Text HLabel 2750 3800 0    50   BiDi ~ 0
MISO
Text HLabel 2750 3600 0    50   BiDi ~ 0
SPCK
Text HLabel 2750 3000 0    50   BiDi ~ 0
SEL
Text HLabel 4000 1050 0    50   BiDi ~ 0
POW
Text HLabel 2750 4100 0    50   BiDi ~ 0
INS
$Comp
L Power_Management:MIC2026-1BM U?
U 1 1 620C0CEA
P 5350 1350
F 0 "U?" H 5350 1917 50  0000 C CNN
F 1 "MIC2026-1BM" H 5350 1826 50  0000 C CNN
F 2 "" H 5350 1350 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/mic2026.pdf" H 5350 1350 50  0001 C CNN
	1    5350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 3500 6100 3500
Wire Wire Line
	5750 1050 6100 1050
Wire Wire Line
	6100 1050 6100 800 
$Comp
L power:+3.3V #PWR?
U 1 1 620C24E9
P 6100 800
F 0 "#PWR?" H 6100 650 50  0001 C CNN
F 1 "+3.3V" H 6115 973 50  0000 C CNN
F 2 "" H 6100 800 50  0001 C CNN
F 3 "" H 6100 800 50  0001 C CNN
	1    6100 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1850 5350 2000
$Comp
L power:GND #PWR?
U 1 1 620C2758
P 5350 2000
F 0 "#PWR?" H 5350 1750 50  0001 C CNN
F 1 "GND" H 5355 1827 50  0000 C CNN
F 2 "" H 5350 2000 50  0001 C CNN
F 3 "" H 5350 2000 50  0001 C CNN
	1    5350 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1050 4950 1050
NoConn ~ 5750 1450
NoConn ~ 4950 1450
NoConn ~ 4950 1350
NoConn ~ 4950 1150
Wire Wire Line
	6500 1250 6500 1400
$Comp
L akizuki:C C?
U 1 1 620C2BB9
P 6500 1550
F 0 "C?" H 6583 1603 60  0000 L CNN
F 1 "0.1uF" H 6583 1497 60  0000 L CNN
F 2 "" V 6500 1550 60  0000 C CNN
F 3 "" V 6500 1550 60  0000 C CNN
	1    6500 1550
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C-POL C?
U 1 1 620C3280
P 7000 1550
F 0 "C?" H 7083 1603 60  0000 L CNN
F 1 "10uF" H 7083 1497 60  0000 L CNN
F 2 "" V 7000 1550 60  0000 C CNN
F 3 "" V 7000 1550 60  0000 C CNN
	1    7000 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1400 7000 1250
Wire Wire Line
	7000 1250 6500 1250
Connection ~ 6500 1250
Wire Wire Line
	7000 1700 7000 1850
Wire Wire Line
	6500 1850 6500 1700
Wire Wire Line
	6500 3700 6750 3700
Wire Wire Line
	6500 3700 6500 4000
$Comp
L power:GND #PWR?
U 1 1 620C3E00
P 6500 4600
F 0 "#PWR?" H 6500 4350 50  0001 C CNN
F 1 "GND" H 6505 4427 50  0000 C CNN
F 2 "" H 6500 4600 50  0001 C CNN
F 3 "" H 6500 4600 50  0001 C CNN
	1    6500 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 4100 8600 4100
Wire Wire Line
	8600 4100 8600 4300
$Comp
L power:GND #PWR?
U 1 1 620C4292
P 8600 4300
F 0 "#PWR?" H 8600 4050 50  0001 C CNN
F 1 "GND" H 8605 4127 50  0000 C CNN
F 2 "" H 8600 4300 50  0001 C CNN
F 3 "" H 8600 4300 50  0001 C CNN
	1    8600 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 4000 6500 4000
Connection ~ 6500 4000
Wire Wire Line
	6500 4000 6500 4600
$Comp
L akizuki:R R?
U 1 1 620C5894
P 3600 3600
F 0 "R?" H 3600 3500 50  0000 C CNN
F 1 "22" H 3600 3716 50  0000 C CNN
F 2 "" H 3600 3530 50  0000 C CNN
F 3 "" V 3600 3600 50  0000 C CNN
	1    3600 3600
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 620C8061
P 3600 3250
F 0 "R?" H 3600 3150 50  0000 C CNN
F 1 "22" H 3600 3366 50  0000 C CNN
F 2 "" H 3600 3180 50  0000 C CNN
F 3 "" V 3600 3250 50  0000 C CNN
	1    3600 3250
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 620CA31B
P 2900 2750
F 0 "R?" V 2854 2820 50  0000 L CNN
F 1 "22K" V 2945 2820 50  0000 L CNN
F 2 "" H 2900 2680 50  0000 C CNN
F 3 "" V 2900 2750 50  0000 C CNN
	1    2900 2750
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 620CB31E
P 3200 2750
F 0 "R?" V 3154 2820 50  0000 L CNN
F 1 "22K" V 3245 2820 50  0000 L CNN
F 2 "" H 3200 2680 50  0000 C CNN
F 3 "" V 3200 2750 50  0000 C CNN
	1    3200 2750
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 620CB56E
P 4550 2750
F 0 "R?" V 4504 2820 50  0000 L CNN
F 1 "22K" V 4595 2820 50  0000 L CNN
F 2 "" H 4550 2680 50  0000 C CNN
F 3 "" V 4550 2750 50  0000 C CNN
	1    4550 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 1250 6100 1250
Wire Wire Line
	6100 3500 6100 2400
Connection ~ 6100 1250
Wire Wire Line
	6100 1250 6500 1250
Wire Wire Line
	7000 1850 6500 1850
Wire Wire Line
	6500 1850 6500 3700
Connection ~ 6500 1850
Connection ~ 6500 3700
$Comp
L akizuki:R R?
U 1 1 620CFBC5
P 4850 2750
F 0 "R?" V 4804 2820 50  0000 L CNN
F 1 "22K" V 4895 2820 50  0000 L CNN
F 2 "" H 4850 2680 50  0000 C CNN
F 3 "" V 4850 2750 50  0000 C CNN
	1    4850 2750
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 620CFC84
P 5150 2750
F 0 "R?" V 5104 2820 50  0000 L CNN
F 1 "22K" V 5195 2820 50  0000 L CNN
F 2 "" H 5150 2680 50  0000 C CNN
F 3 "" V 5150 2750 50  0000 C CNN
	1    5150 2750
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 620CFE6C
P 5450 2750
F 0 "R?" V 5404 2820 50  0000 L CNN
F 1 "22K" V 5495 2820 50  0000 L CNN
F 2 "" H 5450 2680 50  0000 C CNN
F 3 "" V 5450 2750 50  0000 C CNN
	1    5450 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 3400 3850 3250
Wire Wire Line
	3850 3250 3750 3250
Wire Wire Line
	4850 2900 4850 3800
Connection ~ 4850 3800
Wire Wire Line
	5150 2900 5150 4100
Connection ~ 5150 4100
Wire Wire Line
	5450 2900 5450 3900
$Comp
L akizuki:R R?
U 1 1 620E09FA
P 5750 2750
F 0 "R?" V 5704 2820 50  0000 L CNN
F 1 "22K" V 5795 2820 50  0000 L CNN
F 2 "" H 5750 2680 50  0000 C CNN
F 3 "" V 5750 2750 50  0000 C CNN
	1    5750 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 2900 5750 3200
Wire Wire Line
	5750 3200 6750 3200
Wire Wire Line
	3950 3300 4550 3300
Wire Wire Line
	4850 3800 6750 3800
Wire Wire Line
	5450 3900 6750 3900
Wire Wire Line
	5150 4100 6750 4100
Wire Wire Line
	2750 3000 3950 3000
Wire Wire Line
	3850 3400 6750 3400
Wire Wire Line
	3750 3600 6750 3600
Wire Wire Line
	2750 3250 2900 3250
Wire Wire Line
	2750 3600 3200 3600
Wire Wire Line
	2750 3800 4850 3800
Wire Wire Line
	2750 4100 5150 4100
Wire Wire Line
	2900 2900 2900 3250
Connection ~ 2900 3250
Wire Wire Line
	2900 3250 3450 3250
Wire Wire Line
	3200 2900 3200 3600
Connection ~ 3200 3600
Wire Wire Line
	3200 3600 3450 3600
Wire Wire Line
	3950 3300 3950 3000
Wire Wire Line
	4550 2900 4550 3300
Connection ~ 4550 3300
Wire Wire Line
	4550 3300 6750 3300
Wire Wire Line
	2900 2600 2900 2400
Wire Wire Line
	2900 2400 3200 2400
Connection ~ 6100 2400
Wire Wire Line
	6100 2400 6100 1250
Wire Wire Line
	5750 2600 5750 2400
Connection ~ 5750 2400
Wire Wire Line
	5750 2400 6100 2400
Wire Wire Line
	5450 2600 5450 2400
Connection ~ 5450 2400
Wire Wire Line
	5450 2400 5750 2400
Wire Wire Line
	5150 2600 5150 2400
Connection ~ 5150 2400
Wire Wire Line
	5150 2400 5450 2400
Wire Wire Line
	4850 2600 4850 2400
Connection ~ 4850 2400
Wire Wire Line
	4850 2400 5150 2400
Wire Wire Line
	4550 2600 4550 2400
Connection ~ 4550 2400
Wire Wire Line
	4550 2400 4850 2400
Wire Wire Line
	3200 2600 3200 2400
Connection ~ 3200 2400
Wire Wire Line
	3200 2400 4550 2400
$EndSCHEMATC
