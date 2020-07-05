EESchema Schematic File Version 4
LIBS:DSO_FE-cache
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
L Connector:Conn_Coaxial J?
U 1 1 5EF694A4
P 950 1050
F 0 "J?" H 878 1288 50  0000 C CNN
F 1 "Conn_Coaxial" H 878 1197 50  0000 C CNN
F 2 "" H 950 1050 50  0001 C CNN
F 3 " ~" H 950 1050 50  0001 C CNN
	1    950  1050
	-1   0    0    -1  
$EndComp
$Comp
L Device:CTRIM C?
U 1 1 5EF6B220
P 2800 2550
F 0 "C?" H 2916 2596 50  0000 L CNN
F 1 "5-20pF" H 2916 2505 50  0000 L CNN
F 2 "" H 2800 2550 50  0001 C CNN
F 3 "~" H 2800 2550 50  0001 C CNN
	1    2800 2550
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EF6CDF9
P 3400 2300
F 0 "C?" H 3483 2353 60  0000 L CNN
F 1 "3pF" H 3483 2247 60  0000 L CNN
F 2 "" V 3400 2300 60  0000 C CNN
F 3 "" V 3400 2300 60  0000 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EF6D8BD
P 3400 2800
F 0 "C?" H 3483 2853 60  0000 L CNN
F 1 "1pF" H 3483 2747 60  0000 L CNN
F 2 "" V 3400 2800 60  0000 C CNN
F 3 "" V 3400 2800 60  0000 C CNN
	1    3400 2800
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EF6DA24
P 3900 2800
F 0 "C?" H 3983 2853 60  0000 L CNN
F 1 "0.001uF" H 3983 2747 60  0000 L CNN
F 2 "" V 3900 2800 60  0000 C CNN
F 3 "" V 3900 2800 60  0000 C CNN
	1    3900 2800
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EF6DB52
P 3900 2300
F 0 "C?" H 3982 2353 60  0000 L CNN
F 1 "82pF" H 3982 2247 60  0000 L CNN
F 2 "" V 3900 2300 60  0000 C CNN
F 3 "" V 3900 2300 60  0000 C CNN
	1    3900 2300
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EF6DC0A
P 3900 1800
F 0 "C?" H 3982 1853 60  0000 L CNN
F 1 "39pF" H 3982 1747 60  0000 L CNN
F 2 "" V 3900 1800 60  0000 C CNN
F 3 "" V 3900 1800 60  0000 C CNN
	1    3900 1800
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EF6E777
P 4400 1800
F 0 "R?" V 4354 1870 50  0000 L CNN
F 1 "820K" V 4445 1870 50  0000 L CNN
F 2 "" H 4400 1730 50  0000 C CNN
F 3 "" V 4400 1800 50  0000 C CNN
	1    4400 1800
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EF6ED96
P 4400 2300
F 0 "R?" V 4354 2370 50  0000 L CNN
F 1 "200K" V 4445 2370 50  0000 L CNN
F 2 "" H 4400 2230 50  0000 C CNN
F 3 "" V 4400 2300 50  0000 C CNN
	1    4400 2300
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EF6EFE8
P 4400 2800
F 0 "R?" V 4354 2870 50  0000 L CNN
F 1 "21K" V 4445 2870 50  0000 L CNN
F 2 "" H 4400 2730 50  0000 C CNN
F 3 "" V 4400 2800 50  0000 C CNN
	1    4400 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	2800 3150 2800 3050
Wire Wire Line
	3400 3050 3400 2950
Wire Wire Line
	3400 3050 3900 3050
Wire Wire Line
	3900 3050 3900 2950
Connection ~ 3400 3050
Wire Wire Line
	3900 3050 4400 3050
Wire Wire Line
	4400 3050 4400 2950
Connection ~ 3900 3050
Wire Wire Line
	3900 1550 3900 1650
Wire Wire Line
	3900 1550 4400 1550
Wire Wire Line
	4400 1550 4400 1650
Connection ~ 3900 1550
Wire Wire Line
	3900 1950 3900 2050
Wire Wire Line
	3900 2450 3900 2550
Wire Wire Line
	3400 2150 3400 2050
Wire Wire Line
	3400 2050 3900 2050
Connection ~ 3900 2050
Wire Wire Line
	3900 2050 3900 2150
Wire Wire Line
	3400 2450 3400 2550
Wire Wire Line
	3400 2550 3900 2550
Connection ~ 3400 2550
Wire Wire Line
	3400 2550 3400 2650
Connection ~ 3900 2550
Wire Wire Line
	3900 2550 3900 2650
Wire Wire Line
	4400 2150 4400 2050
Wire Wire Line
	4400 2650 4400 2550
Wire Wire Line
	3900 2550 4400 2550
Connection ~ 4400 2550
Wire Wire Line
	4400 2550 4400 2450
Wire Wire Line
	3900 2050 4400 2050
Connection ~ 4400 2050
Wire Wire Line
	4400 2050 4400 1950
$Comp
L power:GNDA #PWR?
U 1 1 5EF6FB68
P 2800 3150
F 0 "#PWR?" H 2800 2900 50  0001 C CNN
F 1 "GNDA" H 2805 2977 50  0000 C CNN
F 2 "" H 2800 3150 50  0001 C CNN
F 3 "" H 2800 3150 50  0001 C CNN
	1    2800 3150
	1    0    0    -1  
$EndComp
Connection ~ 2800 3050
Wire Wire Line
	2800 3050 3400 3050
Wire Wire Line
	2800 3050 2800 2700
Wire Wire Line
	2800 2400 2800 2050
Wire Wire Line
	2800 2050 3400 2050
Connection ~ 3400 2050
$Comp
L akizuki:C C?
U 1 1 5EF95B6D
P 2300 2150
F 0 "C?" V 2053 2150 60  0000 C CNN
F 1 "0.1uF" V 2159 2150 60  0000 C CNN
F 2 "" V 2300 2150 60  0000 C CNN
F 3 "" V 2300 2150 60  0000 C CNN
	1    2300 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 1550 2650 1550
Wire Wire Line
	2150 2150 2000 2150
Wire Wire Line
	2650 2150 2650 1550
Connection ~ 2650 1550
Wire Wire Line
	2650 1550 3900 1550
Wire Wire Line
	2000 2350 2100 2350
Wire Wire Line
	2100 2350 2100 1750
Wire Wire Line
	2100 1750 2000 1750
Wire Wire Line
	2100 1750 2100 1050
Wire Wire Line
	2100 1050 1150 1050
Connection ~ 2100 1750
Wire Wire Line
	2450 2150 2650 2150
Wire Wire Line
	950  1250 950  3050
Wire Wire Line
	950  3050 2800 3050
Wire Wire Line
	4400 2050 5250 2050
Wire Wire Line
	4400 2550 4800 2550
Wire Wire Line
	4800 2550 4800 2150
Wire Wire Line
	4800 2150 5250 2150
Wire Wire Line
	5250 2250 4950 2250
Wire Wire Line
	4950 2250 4950 3050
Wire Wire Line
	4950 3050 4400 3050
Connection ~ 4400 3050
Wire Wire Line
	5750 3550 5750 3750
$Comp
L power:GNDA #PWR?
U 1 1 5EFB5CAF
P 5750 3750
F 0 "#PWR?" H 5750 3500 50  0001 C CNN
F 1 "GNDA" H 5755 3577 50  0000 C CNN
F 2 "" H 5750 3750 50  0001 C CNN
F 3 "" H 5750 3750 50  0001 C CNN
	1    5750 3750
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:OPA2134 U?
U 1 1 5EFB618F
P 7850 1950
F 0 "U?" H 7850 1583 50  0000 C CNN
F 1 "OPA2134" H 7850 1674 50  0000 C CNN
F 2 "" H 7850 1950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 7850 1950 50  0001 C CNN
	1    7850 1950
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:OPA2134 U?
U 2 1 5EFBDA7E
P 9200 1950
F 0 "U?" H 9200 1583 50  0000 C CNN
F 1 "OPA2134" H 9200 1674 50  0000 C CNN
F 2 "" H 9200 1950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 9200 1950 50  0001 C CNN
	2    9200 1950
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:OPA2134 U?
U 3 1 5EFC0444
P 7850 3200
F 0 "U?" H 7808 3246 50  0000 L CNN
F 1 "OPA2134" H 7808 3155 50  0000 L CNN
F 2 "" H 7850 3200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 7850 3200 50  0001 C CNN
	3    7850 3200
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EFC2AF4
P 7050 2050
F 0 "R?" H 7050 2257 50  0000 C CNN
F 1 "5K" H 7050 2166 50  0000 C CNN
F 2 "" H 7050 1980 50  0000 C CNN
F 3 "" V 7050 2050 50  0000 C CNN
	1    7050 2050
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EFC301C
P 7850 1350
F 0 "R?" H 7850 1557 50  0000 C CNN
F 1 "10K" H 7850 1466 50  0000 C CNN
F 2 "" H 7850 1280 50  0000 C CNN
F 3 "" V 7850 1350 50  0000 C CNN
	1    7850 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EFC39B7
P 7050 1650
F 0 "C?" V 6803 1650 60  0000 C CNN
F 1 "100pF" V 6909 1650 60  0000 C CNN
F 2 "" V 7050 1650 60  0000 C CNN
F 3 "" V 7050 1650 60  0000 C CNN
	1    7050 1650
	0    1    1    0   
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EFC41FB
P 7850 950
F 0 "C?" V 7603 950 60  0000 C CNN
F 1 "150pF" V 7709 950 60  0000 C CNN
F 2 "" V 7850 950 60  0000 C CNN
F 3 "" V 7850 950 60  0000 C CNN
	1    7850 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 1850 7450 1850
Wire Wire Line
	7450 1850 7450 1350
Wire Wire Line
	7450 1350 7700 1350
Wire Wire Line
	7450 1350 7450 950 
Wire Wire Line
	7450 950  7700 950 
Connection ~ 7450 1350
Wire Wire Line
	8150 1950 8300 1950
Wire Wire Line
	8300 1950 8300 1350
Wire Wire Line
	8300 1350 8000 1350
Wire Wire Line
	8300 1350 8300 950 
Wire Wire Line
	8300 950  8000 950 
Connection ~ 8300 1350
Wire Wire Line
	7550 2050 7300 2050
Wire Wire Line
	7300 2050 7300 1650
Wire Wire Line
	7300 1650 7200 1650
Connection ~ 7300 2050
Wire Wire Line
	7300 2050 7200 2050
Wire Wire Line
	6900 2050 6800 2050
Wire Wire Line
	6900 1650 6800 1650
Wire Wire Line
	6800 1650 6800 2050
Connection ~ 6800 2050
Wire Wire Line
	6250 2050 6800 2050
$Comp
L 74xx:74HC04 U?
U 1 1 5EFD6638
P 1300 3800
F 0 "U?" H 1300 4117 50  0000 C CNN
F 1 "74HC04" H 1300 4026 50  0000 C CNN
F 2 "" H 1300 3800 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 1300 3800 50  0001 C CNN
	1    1300 3800
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC04 U?
U 2 1 5EFD8188
P 1300 4650
F 0 "U?" H 1300 4967 50  0000 C CNN
F 1 "74HC04" H 1300 4876 50  0000 C CNN
F 2 "" H 1300 4650 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 1300 4650 50  0001 C CNN
	2    1300 4650
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC04 U?
U 3 1 5EFD9CAB
P 1300 5500
F 0 "U?" H 1300 5817 50  0000 C CNN
F 1 "74HC04" H 1300 5726 50  0000 C CNN
F 2 "" H 1300 5500 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 1300 5500 50  0001 C CNN
	3    1300 5500
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EFE1FA4
P 1850 3800
F 0 "R?" H 1850 4007 50  0000 C CNN
F 1 "390" H 1850 3916 50  0000 C CNN
F 2 "" H 1850 3730 50  0000 C CNN
F 3 "" V 1850 3800 50  0000 C CNN
	1    1850 3800
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EFE2578
P 1850 4650
F 0 "R?" H 1850 4857 50  0000 C CNN
F 1 "390" H 1850 4766 50  0000 C CNN
F 2 "" H 1850 4580 50  0000 C CNN
F 3 "" V 1850 4650 50  0000 C CNN
	1    1850 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3800 1600 3800
Wire Wire Line
	1700 4650 1600 4650
Wire Wire Line
	2000 3800 2100 3800
Wire Wire Line
	2100 3800 2100 3400
Wire Wire Line
	2100 3400 1100 3400
Wire Wire Line
	1100 3400 1100 1750
Wire Wire Line
	1100 1750 1400 1750
Wire Wire Line
	1400 2350 1250 2350
Wire Wire Line
	1250 2350 1250 3250
Wire Wire Line
	1250 3250 2250 3250
Wire Wire Line
	2250 3250 2250 4650
Wire Wire Line
	2250 4650 2000 4650
Wire Wire Line
	1000 4650 850  4650
Wire Wire Line
	850  4650 850  5100
Wire Wire Line
	850  5100 1750 5100
Wire Wire Line
	1750 5100 1750 5500
Wire Wire Line
	1750 5500 1600 5500
Wire Wire Line
	1000 5500 700  5500
Wire Wire Line
	700  5500 700  3800
Wire Wire Line
	700  3800 1000 3800
$Comp
L akizuki:PS7200K U?
U 1 1 5F011C0E
P 1700 1650
F 0 "U?" H 1700 1967 50  0000 C CNN
F 1 "PS7200K" H 1700 1876 50  0000 C CNN
F 2 "" H 1700 1850 50  0001 C CNN
F 3 "" H 1700 1850 50  0001 C CNN
	1    1700 1650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:PS7200K U?
U 1 1 5F012572
P 1700 2250
F 0 "U?" H 1700 2567 50  0000 C CNN
F 1 "PS7200K" H 1700 2476 50  0000 C CNN
F 2 "" H 1700 2450 50  0001 C CNN
F 3 "" H 1700 2450 50  0001 C CNN
	1    1700 2250
	1    0    0    -1  
$EndComp
$Comp
L akizuki:MAU106 PM?
U 1 1 5F01B56E
P 9550 5700
F 0 "PM?" H 9550 6115 50  0000 C CNN
F 1 "MAU106" H 9550 6024 50  0000 C CNN
F 2 "" H 9550 5700 50  0001 C CNN
F 3 "" H 9550 5700 50  0001 C CNN
	1    9550 5700
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C-POL C?
U 1 1 5F01E51D
P 8600 5700
F 0 "C?" H 8683 5753 60  0000 L CNN
F 1 "2.2uF" H 8683 5647 60  0000 L CNN
F 2 "" V 8600 5700 60  0000 C CNN
F 3 "" V 8600 5700 60  0000 C CNN
	1    8600 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F01F1B8
P 8600 5350
F 0 "#PWR?" H 8600 5200 50  0001 C CNN
F 1 "+5V" H 8615 5523 50  0000 C CNN
F 2 "" H 8600 5350 50  0001 C CNN
F 3 "" H 8600 5350 50  0001 C CNN
	1    8600 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F020257
P 8600 6050
F 0 "#PWR?" H 8600 5800 50  0001 C CNN
F 1 "GND" H 8605 5877 50  0000 C CNN
F 2 "" H 8600 6050 50  0001 C CNN
F 3 "" H 8600 6050 50  0001 C CNN
	1    8600 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5550 8600 5550
Wire Wire Line
	8600 5550 8600 5350
Connection ~ 8600 5550
Wire Wire Line
	8600 5850 9100 5850
Wire Wire Line
	8600 5850 8600 6050
Connection ~ 8600 5850
$Comp
L akizuki:C-POL C?
U 1 1 5F02B004
P 10250 5450
F 0 "C?" H 10333 5503 60  0000 L CNN
F 1 "1uF" H 10333 5397 60  0000 L CNN
F 2 "" V 10250 5450 60  0000 C CNN
F 3 "" V 10250 5450 60  0000 C CNN
	1    10250 5450
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C-POL C?
U 1 1 5F02CEF2
P 10250 5950
F 0 "C?" H 10333 6003 60  0000 L CNN
F 1 "1uF" H 10333 5897 60  0000 L CNN
F 2 "" V 10250 5950 60  0000 C CNN
F 3 "" V 10250 5950 60  0000 C CNN
	1    10250 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 5700 10250 5700
Wire Wire Line
	10250 5700 10250 5600
Wire Wire Line
	10250 5800 10250 5700
Connection ~ 10250 5700
Wire Wire Line
	10000 5550 10100 5550
Wire Wire Line
	10100 5550 10100 5200
Wire Wire Line
	10100 5200 10250 5200
Wire Wire Line
	10250 5200 10250 5300
Wire Wire Line
	10000 5850 10100 5850
Wire Wire Line
	10100 5850 10100 6200
Wire Wire Line
	10100 6200 10250 6200
Wire Wire Line
	10250 6200 10250 6100
Wire Wire Line
	10250 5200 10550 5200
Connection ~ 10250 5200
Wire Wire Line
	10250 6200 10550 6200
Connection ~ 10250 6200
$Comp
L power:+5VA #PWR?
U 1 1 5F04050F
P 10550 5200
F 0 "#PWR?" H 10550 5050 50  0001 C CNN
F 1 "+5VA" V 10565 5328 50  0000 L CNN
F 2 "" H 10550 5200 50  0001 C CNN
F 3 "" H 10550 5200 50  0001 C CNN
	1    10550 5200
	0    1    1    0   
$EndComp
$Comp
L power:-5VA #PWR?
U 1 1 5F04171C
P 10550 6200
F 0 "#PWR?" H 10550 6300 50  0001 C CNN
F 1 "-5VA" V 10565 6328 50  0000 L CNN
F 2 "" H 10550 6200 50  0001 C CNN
F 3 "" H 10550 6200 50  0001 C CNN
	1    10550 6200
	0    1    1    0   
$EndComp
$Comp
L 4xxx:4051 U?
U 1 1 5F04E116
P 5750 2650
F 0 "U?" H 6294 2696 50  0000 L CNN
F 1 "74HC4051" H 6294 2605 50  0000 L CNN
F 2 "" H 5750 2650 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 5750 2650 50  0001 C CNN
	1    5750 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5F0591A1
P 10650 5750
F 0 "#PWR?" H 10650 5500 50  0001 C CNN
F 1 "GNDA" H 10655 5577 50  0000 C CNN
F 2 "" H 10650 5750 50  0001 C CNN
F 3 "" H 10650 5750 50  0001 C CNN
	1    10650 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 5700 10650 5700
Wire Wire Line
	10650 5700 10650 5750
$Comp
L Connector_Generic:Conn_02x06_Top_Bottom J?
U 1 1 5F0723E0
P 1650 7000
F 0 "J?" H 1700 6475 50  0000 C CNN
F 1 "Pmod2" H 1700 6566 50  0000 C CNN
F 2 "" H 1650 7000 50  0001 C CNN
F 3 "~" H 1650 7000 50  0001 C CNN
	1    1650 7000
	1    0    0    1   
$EndComp
Text Label 1250 7200 0    50   ~ 0
P93
Text Label 1250 7100 0    50   ~ 0
P90
Text Label 1250 7000 0    50   ~ 0
P92
Text Label 1250 6900 0    50   ~ 0
P91
Text Label 2000 7200 0    50   ~ 0
PD0
Text Label 2000 7100 0    50   ~ 0
PD1
Text Label 2000 7000 0    50   ~ 0
P46
Text Label 2000 6900 0    50   ~ 0
P47
Wire Wire Line
	1950 6900 2200 6900
Wire Wire Line
	1950 7000 2200 7000
Wire Wire Line
	1950 7100 2200 7100
Wire Wire Line
	1950 7200 2200 7200
Wire Wire Line
	1450 7200 1200 7200
Wire Wire Line
	1450 7100 1200 7100
Wire Wire Line
	1450 7000 1200 7000
Wire Wire Line
	1450 6900 1200 6900
Wire Wire Line
	1400 2150 1250 2150
Wire Wire Line
	1250 2150 1250 1550
Wire Wire Line
	1250 1550 1400 1550
Wire Wire Line
	1250 1550 1250 1400
Connection ~ 1250 1550
$Comp
L power:+5V #PWR?
U 1 1 5F09EFB3
P 1250 1400
F 0 "#PWR?" H 1250 1250 50  0001 C CNN
F 1 "+5V" H 1265 1573 50  0000 C CNN
F 2 "" H 1250 1400 50  0001 C CNN
F 3 "" H 1250 1400 50  0001 C CNN
	1    1250 1400
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5F09F253
P 2200 5800
F 0 "R?" H 2200 5593 50  0000 C CNN
F 1 "100K" H 2200 5684 50  0000 C CNN
F 2 "" H 2200 5730 50  0000 C CNN
F 3 "" V 2200 5800 50  0000 C CNN
	1    2200 5800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2050 5800 700  5800
Wire Wire Line
	700  5800 700  5500
Connection ~ 700  5500
Wire Wire Line
	2350 5800 2700 5800
Wire Wire Line
	2700 5800 2700 5950
$Comp
L power:GND #PWR?
U 1 1 5F0A85D6
P 2700 5950
F 0 "#PWR?" H 2700 5700 50  0001 C CNN
F 1 "GND" H 2705 5777 50  0000 C CNN
F 2 "" H 2700 5950 50  0001 C CNN
F 3 "" H 2700 5950 50  0001 C CNN
	1    2700 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 3550 5850 3700
Wire Wire Line
	5850 3700 6250 3700
Wire Wire Line
	5750 1750 5750 1600
Wire Wire Line
	5750 1600 6250 1600
$Comp
L power:+5VA #PWR?
U 1 1 5F0B26AB
P 6250 1600
F 0 "#PWR?" H 6250 1450 50  0001 C CNN
F 1 "+5VA" V 6265 1728 50  0000 L CNN
F 2 "" H 6250 1600 50  0001 C CNN
F 3 "" H 6250 1600 50  0001 C CNN
	1    6250 1600
	0    1    1    0   
$EndComp
$Comp
L power:-5VA #PWR?
U 1 1 5F0B2E21
P 6250 3700
F 0 "#PWR?" H 6250 3800 50  0001 C CNN
F 1 "-5VA" V 6265 3828 50  0000 L CNN
F 2 "" H 6250 3700 50  0001 C CNN
F 3 "" H 6250 3700 50  0001 C CNN
	1    6250 3700
	0    1    1    0   
$EndComp
$Comp
L power:+5VA #PWR?
U 1 1 5F0B3802
P 5750 850
F 0 "#PWR?" H 5750 700 50  0001 C CNN
F 1 "+5VA" H 5765 1023 50  0000 C CNN
F 2 "" H 5750 850 50  0001 C CNN
F 3 "" H 5750 850 50  0001 C CNN
	1    5750 850 
	1    0    0    -1  
$EndComp
$Comp
L power:-5VA #PWR?
U 1 1 5F0B40A1
P 5150 1300
F 0 "#PWR?" H 5150 1400 50  0001 C CNN
F 1 "-5VA" H 5165 1473 50  0000 C CNN
F 2 "" H 5150 1300 50  0001 C CNN
F 3 "" H 5150 1300 50  0001 C CNN
	1    5150 1300
	-1   0    0    1   
$EndComp
$Comp
L akizuki:C C?
U 1 1 5F0B50A4
P 5750 1000
F 0 "C?" H 5833 1053 60  0000 L CNN
F 1 "0.1uF" H 5833 947 60  0000 L CNN
F 2 "" V 5750 1000 60  0000 C CNN
F 3 "" V 5750 1000 60  0000 C CNN
	1    5750 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5F0CC6AC
P 5750 1300
F 0 "#PWR?" H 5750 1050 50  0001 C CNN
F 1 "GNDA" H 5755 1127 50  0000 C CNN
F 2 "" H 5750 1300 50  0001 C CNN
F 3 "" H 5750 1300 50  0001 C CNN
	1    5750 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1300 5750 1250
$Comp
L akizuki:C C?
U 1 1 5F0DAD00
P 5150 1150
F 0 "C?" H 5233 1203 60  0000 L CNN
F 1 "0.1uF" H 5233 1097 60  0000 L CNN
F 2 "" V 5150 1150 60  0000 C CNN
F 3 "" V 5150 1150 60  0000 C CNN
	1    5150 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1250 5500 1250
Wire Wire Line
	5500 1250 5500 900 
Wire Wire Line
	5500 900  5150 900 
Wire Wire Line
	5150 900  5150 1000
Connection ~ 5750 1250
Wire Wire Line
	5750 1250 5750 1150
$Comp
L akizuki:C C?
U 1 1 5F0E0999
P 8050 2750
F 0 "C?" V 7803 2750 60  0000 C CNN
F 1 "0.1uF" V 7909 2750 60  0000 C CNN
F 2 "" V 8050 2750 60  0000 C CNN
F 3 "" V 8050 2750 60  0000 C CNN
	1    8050 2750
	0    1    1    0   
$EndComp
$Comp
L akizuki:C C?
U 1 1 5F0E0A7B
P 8050 3650
F 0 "C?" V 7803 3650 60  0000 C CNN
F 1 "0.1uF" V 7909 3650 60  0000 C CNN
F 2 "" V 8050 3650 60  0000 C CNN
F 3 "" V 8050 3650 60  0000 C CNN
	1    8050 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 2900 7750 2750
Wire Wire Line
	7750 2750 7900 2750
Wire Wire Line
	7900 3650 7750 3650
Wire Wire Line
	7750 3650 7750 3500
Wire Wire Line
	7750 2750 7600 2750
Connection ~ 7750 2750
Wire Wire Line
	7750 3650 7600 3650
Connection ~ 7750 3650
$Comp
L power:+5VA #PWR?
U 1 1 5F0F66AF
P 7600 2750
F 0 "#PWR?" H 7600 2600 50  0001 C CNN
F 1 "+5VA" V 7615 2877 50  0000 L CNN
F 2 "" H 7600 2750 50  0001 C CNN
F 3 "" H 7600 2750 50  0001 C CNN
	1    7600 2750
	0    -1   -1   0   
$EndComp
$Comp
L power:-5VA #PWR?
U 1 1 5F0F74E0
P 7600 3650
F 0 "#PWR?" H 7600 3750 50  0001 C CNN
F 1 "-5VA" V 7615 3777 50  0000 L CNN
F 2 "" H 7600 3650 50  0001 C CNN
F 3 "" H 7600 3650 50  0001 C CNN
	1    7600 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8200 2750 8300 2750
Wire Wire Line
	8300 2750 8300 3650
Wire Wire Line
	8300 3650 8200 3650
Wire Wire Line
	8300 3650 8300 3750
Connection ~ 8300 3650
$Comp
L power:GNDA #PWR?
U 1 1 5F102AE8
P 8300 3750
F 0 "#PWR?" H 8300 3500 50  0001 C CNN
F 1 "GNDA" H 8305 3577 50  0000 C CNN
F 2 "" H 8300 3750 50  0001 C CNN
F 3 "" H 8300 3750 50  0001 C CNN
	1    8300 3750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
