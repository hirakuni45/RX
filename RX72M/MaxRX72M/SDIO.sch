EESchema Schematic File Version 4
LIBS:MaxRX72M-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 9
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4400 4250 0    50   Output ~ 10
SDHI_CD
Text HLabel 4400 5050 0    50   Output ~ 10
SDHI_WP
Text HLabel 4400 3850 0    50   Output ~ 10
SDHI_CLK
Text HLabel 4400 3650 0    50   BiDi ~ 10
SDHI_CMD
Text HLabel 4400 4050 0    50   BiDi ~ 10
SDHI_D0
Text HLabel 4400 4150 0    50   BiDi ~ 10
SDHI_D1
Text HLabel 4400 3550 0    50   BiDi ~ 10
SDHI_D3
Text HLabel 4400 3450 0    50   BiDi ~ 10
SDHI_D2
$Comp
L Connector:Micro_SD_Card_Det_Hirose_DM3AT J?
U 1 1 5DC476E8
P 7450 3850
F 0 "J?" H 7400 4667 50  0000 C CNN
F 1 "Micro_SD_Card_Det_Hirose_DM3AT" H 7400 4576 50  0000 C CNN
F 2 "" H 9500 4550 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 7450 3950 50  0001 C CNN
	1    7450 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4350 6450 4350
Wire Wire Line
	6450 4350 6450 4700
$Comp
L power:GND #PWR?
U 1 1 5DC49AF6
P 6450 4700
F 0 "#PWR?" H 6450 4450 50  0001 C CNN
F 1 "GND" H 6455 4527 50  0000 C CNN
F 2 "" H 6450 4700 50  0001 C CNN
F 3 "" H 6450 4700 50  0001 C CNN
	1    6450 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC49EDF
P 8350 4700
F 0 "#PWR?" H 8350 4450 50  0001 C CNN
F 1 "GND" H 8355 4527 50  0000 C CNN
F 2 "" H 8350 4700 50  0001 C CNN
F 3 "" H 8350 4700 50  0001 C CNN
	1    8350 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 4350 8350 4350
Wire Wire Line
	8350 4350 8350 4700
Wire Wire Line
	6550 3950 6450 3950
Wire Wire Line
	6450 3950 6450 4350
Connection ~ 6450 4350
Wire Wire Line
	6550 3750 6450 3750
$Comp
L Device:R R?
U 1 1 5DC4A789
P 4950 3200
F 0 "R?" H 5020 3246 50  0000 L CNN
F 1 "22K" H 5020 3155 50  0000 L CNN
F 2 "" V 4880 3200 50  0001 C CNN
F 3 "~" H 4950 3200 50  0001 C CNN
	1    4950 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC4B2F9
P 5200 3200
F 0 "R?" H 5270 3246 50  0000 L CNN
F 1 "22K" H 5270 3155 50  0000 L CNN
F 2 "" V 5130 3200 50  0001 C CNN
F 3 "~" H 5200 3200 50  0001 C CNN
	1    5200 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC4B973
P 5450 3200
F 0 "R?" H 5520 3246 50  0000 L CNN
F 1 "22K" H 5520 3155 50  0000 L CNN
F 2 "" V 5380 3200 50  0001 C CNN
F 3 "~" H 5450 3200 50  0001 C CNN
	1    5450 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC4BAE5
P 5700 3200
F 0 "R?" H 5770 3246 50  0000 L CNN
F 1 "22K" H 5770 3155 50  0000 L CNN
F 2 "" V 5630 3200 50  0001 C CNN
F 3 "~" H 5700 3200 50  0001 C CNN
	1    5700 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC4C865
P 4650 3850
F 0 "R?" V 4550 3850 50  0000 C CNN
F 1 "22" V 4650 3850 50  0000 C CNN
F 2 "" V 4580 3850 50  0001 C CNN
F 3 "~" H 4650 3850 50  0001 C CNN
	1    4650 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 3850 4400 3850
Wire Wire Line
	4400 3650 5450 3650
Wire Wire Line
	4400 3550 5200 3550
Wire Wire Line
	4400 3450 4950 3450
Wire Wire Line
	4400 4050 5700 4050
Wire Wire Line
	4400 4150 5950 4150
Wire Wire Line
	4400 4250 6200 4250
$Comp
L Device:R R?
U 1 1 5DC4FF66
P 5950 3200
F 0 "R?" H 6020 3246 50  0000 L CNN
F 1 "22K" H 6020 3155 50  0000 L CNN
F 2 "" V 5880 3200 50  0001 C CNN
F 3 "~" H 5950 3200 50  0001 C CNN
	1    5950 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC502E1
P 6200 3200
F 0 "R?" H 6270 3246 50  0000 L CNN
F 1 "22K" H 6270 3155 50  0000 L CNN
F 2 "" V 6130 3200 50  0001 C CNN
F 3 "~" H 6200 3200 50  0001 C CNN
	1    6200 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3850 5450 3850
Wire Wire Line
	4950 3350 4950 3450
Connection ~ 4950 3450
Wire Wire Line
	5200 3350 5200 3550
Connection ~ 5200 3550
Wire Wire Line
	5450 3350 5450 3650
Connection ~ 5450 3650
Wire Wire Line
	5700 3350 5700 4050
Connection ~ 5700 4050
Wire Wire Line
	5950 3350 5950 4150
Connection ~ 5950 4150
Wire Wire Line
	6200 3350 6200 4250
Connection ~ 6200 4250
Wire Wire Line
	4950 3450 6550 3450
Wire Wire Line
	5200 3550 6550 3550
Wire Wire Line
	5450 3650 6550 3650
Wire Wire Line
	5700 4050 6550 4050
Wire Wire Line
	5950 4150 6550 4150
Wire Wire Line
	6200 4250 6550 4250
$Comp
L Device:R R?
U 1 1 5DC55576
P 4950 4800
F 0 "R?" H 5020 4846 50  0000 L CNN
F 1 "22K" H 5020 4755 50  0000 L CNN
F 2 "" V 4880 4800 50  0001 C CNN
F 3 "~" H 4950 4800 50  0001 C CNN
	1    4950 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5050 4950 5050
Wire Wire Line
	4950 5050 4950 4950
Wire Wire Line
	4950 4650 4950 4550
$Comp
L power:+3.3V #PWR?
U 1 1 5DC56E39
P 4950 4550
F 0 "#PWR?" H 4950 4400 50  0001 C CNN
F 1 "+3.3V" H 4965 4723 50  0000 C CNN
F 2 "" H 4950 4550 50  0001 C CNN
F 3 "" H 4950 4550 50  0001 C CNN
	1    4950 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3050 6200 2950
$Comp
L power:+3.3V #PWR?
U 1 1 5DC58218
P 6200 2950
F 0 "#PWR?" H 6200 2800 50  0001 C CNN
F 1 "+3.3V" H 6215 3123 50  0000 C CNN
F 2 "" H 6200 2950 50  0001 C CNN
F 3 "" H 6200 2950 50  0001 C CNN
	1    6200 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 2550 5950 2550
Wire Wire Line
	5950 2550 5950 3050
Wire Wire Line
	6450 2550 6450 3750
Wire Wire Line
	5950 2550 5700 2550
Wire Wire Line
	5700 2550 5700 3050
Connection ~ 5950 2550
Wire Wire Line
	5700 2550 5450 2550
Wire Wire Line
	5450 2550 5450 3050
Connection ~ 5700 2550
Wire Wire Line
	5450 2550 5200 2550
Wire Wire Line
	5200 2550 5200 3050
Connection ~ 5450 2550
Wire Wire Line
	5200 2550 4950 2550
Wire Wire Line
	4950 2550 4950 3050
Connection ~ 5200 2550
Wire Wire Line
	5450 3850 5450 4700
Connection ~ 5450 3850
Wire Wire Line
	5450 3850 6550 3850
$Comp
L Device:R R?
U 1 1 5DC5B711
P 5700 4700
F 0 "R?" V 5493 4700 50  0000 C CNN
F 1 "R" V 5584 4700 50  0000 C CNN
F 2 "" V 5630 4700 50  0001 C CNN
F 3 "~" H 5700 4700 50  0001 C CNN
	1    5700 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DC5B8FC
P 5700 5050
F 0 "R?" V 5493 5050 50  0000 C CNN
F 1 "R" V 5584 5050 50  0000 C CNN
F 2 "" V 5630 5050 50  0001 C CNN
F 3 "~" H 5700 5050 50  0001 C CNN
	1    5700 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 4700 5450 4700
Connection ~ 5450 4700
Wire Wire Line
	5450 4700 5450 5050
Wire Wire Line
	5550 5050 5450 5050
Wire Wire Line
	5850 4700 5950 4700
Wire Wire Line
	5950 4700 5950 4600
Wire Wire Line
	5850 5050 5950 5050
Wire Wire Line
	5950 5050 5950 5150
$Comp
L power:+3.3V #PWR?
U 1 1 5DC5F1F1
P 5950 4600
F 0 "#PWR?" H 5950 4450 50  0001 C CNN
F 1 "+3.3V" H 5965 4773 50  0000 C CNN
F 2 "" H 5950 4600 50  0001 C CNN
F 3 "" H 5950 4600 50  0001 C CNN
	1    5950 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC5F3D1
P 5950 5150
F 0 "#PWR?" H 5950 4900 50  0001 C CNN
F 1 "GND" H 5955 4977 50  0000 C CNN
F 2 "" H 5950 5150 50  0001 C CNN
F 3 "" H 5950 5150 50  0001 C CNN
	1    5950 5150
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:DMG2301L Q?
U 1 1 5DC6DC81
P 4300 1900
F 0 "Q?" V 4643 1900 50  0000 C CNN
F 1 "DMG3415U" V 4552 1900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4500 1825 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2301L.pdf" H 4300 1900 50  0001 L CNN
	1    4300 1900
	0    1    -1   0   
$EndComp
Wire Wire Line
	4100 1800 3800 1800
Wire Wire Line
	3800 1800 3800 1700
$Comp
L power:+3.3V #PWR?
U 1 1 5DC74F4F
P 3800 1700
F 0 "#PWR?" H 3800 1550 50  0001 C CNN
F 1 "+3.3V" H 3815 1873 50  0000 C CNN
F 2 "" H 3800 1700 50  0001 C CNN
F 3 "" H 3800 1700 50  0001 C CNN
	1    3800 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC759E7
P 3800 2050
F 0 "R?" H 3870 2096 50  0000 L CNN
F 1 "10K" H 3870 2005 50  0000 L CNN
F 2 "" V 3730 2050 50  0001 C CNN
F 3 "~" H 3800 2050 50  0001 C CNN
	1    3800 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1900 3800 1800
Connection ~ 3800 1800
Wire Wire Line
	3800 2200 3800 2300
Wire Wire Line
	3800 2300 4300 2300
Wire Wire Line
	4300 2300 4300 2100
Wire Wire Line
	4300 2300 4300 2550
Wire Wire Line
	4300 2550 4100 2550
Connection ~ 4300 2300
Text HLabel 4100 2550 0    50   Input ~ 10
SDHI_PE
$Comp
L Device:R L?
U 1 1 5DC79249
P 5100 1800
F 0 "L?" V 4893 1800 50  0000 C CNN
F 1 "220/1KHz" V 4984 1800 50  0000 C CNN
F 2 "" V 5030 1800 50  0001 C CNN
F 3 "~" H 5100 1800 50  0001 C CNN
	1    5100 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 1800 4950 1800
Wire Wire Line
	5250 1800 5450 1800
Wire Wire Line
	5450 1800 5450 2550
$Comp
L Jumper:Jumper_2_Open JP?
U 1 1 5DC7C168
P 4950 5400
F 0 "JP?" V 4904 5498 50  0000 L CNN
F 1 "Jumper_2_Open" V 4995 5498 50  0000 L CNN
F 2 "" H 4950 5400 50  0001 C CNN
F 3 "~" H 4950 5400 50  0001 C CNN
	1    4950 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	4950 5200 4950 5050
Connection ~ 4950 5050
Wire Wire Line
	4950 5600 4950 5700
$Comp
L power:GND #PWR?
U 1 1 5DC7FB46
P 4950 5700
F 0 "#PWR?" H 4950 5450 50  0001 C CNN
F 1 "GND" H 4955 5527 50  0000 C CNN
F 2 "" H 4950 5700 50  0001 C CNN
F 3 "" H 4950 5700 50  0001 C CNN
	1    4950 5700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
