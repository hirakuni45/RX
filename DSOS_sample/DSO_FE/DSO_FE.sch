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
L akizuki:TLP222A U?
U 1 1 5EF7E8F3
P 1700 1650
F 0 "U?" H 1700 2002 40  0000 C CNN
F 1 "TLP222A" H 1700 1926 40  0000 C CNN
F 2 "DIP4" H 1700 1859 29  0000 C CNN
F 3 "" H 1660 1655 60  0000 C CNN
	1    1700 1650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:TLP222A U?
U 1 1 5EF8169C
P 1700 2250
F 0 "U?" H 1700 2602 40  0000 C CNN
F 1 "TLP222A" H 1700 2526 40  0000 C CNN
F 2 "DIP4" H 1700 2459 29  0000 C CNN
F 3 "" H 1660 2255 60  0000 C CNN
	1    1700 2250
	1    0    0    -1  
$EndComp
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
$Comp
L Analog_Switch:CD4052B U?
U 1 1 5EFAEDE9
P 5750 2350
F 0 "U?" H 5750 3231 50  0000 C CNN
F 1 "CD4052B" H 5750 3140 50  0000 C CNN
F 2 "" H 5900 1600 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4052b.pdf" H 5730 2550 50  0001 C CNN
	1    5750 2350
	-1   0    0    -1  
$EndComp
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
	5750 3050 5750 3250
$Comp
L power:GNDA #PWR?
U 1 1 5EFB5CAF
P 5750 3250
F 0 "#PWR?" H 5750 3000 50  0001 C CNN
F 1 "GNDA" H 5755 3077 50  0000 C CNN
F 2 "" H 5750 3250 50  0001 C CNN
F 3 "" H 5750 3250 50  0001 C CNN
	1    5750 3250
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:OPA2134 U?
U 1 1 5EFB618F
P 7850 2050
F 0 "U?" H 7850 1683 50  0000 C CNN
F 1 "OPA2134" H 7850 1774 50  0000 C CNN
F 2 "" H 7850 2050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 7850 2050 50  0001 C CNN
	1    7850 2050
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
P 8400 3250
F 0 "U?" H 8358 3296 50  0000 L CNN
F 1 "OPA2134" H 8358 3205 50  0000 L CNN
F 2 "" H 8400 3250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 8400 3250 50  0001 C CNN
	3    8400 3250
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EFC2AF4
P 7050 2150
F 0 "R?" H 7050 2357 50  0000 C CNN
F 1 "5K" H 7050 2266 50  0000 C CNN
F 2 "" H 7050 2080 50  0000 C CNN
F 3 "" V 7050 2150 50  0000 C CNN
	1    7050 2150
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5EFC301C
P 7850 1450
F 0 "R?" H 7850 1657 50  0000 C CNN
F 1 "10K" H 7850 1566 50  0000 C CNN
F 2 "" H 7850 1380 50  0000 C CNN
F 3 "" V 7850 1450 50  0000 C CNN
	1    7850 1450
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EFC39B7
P 7050 1750
F 0 "C?" V 6803 1750 60  0000 C CNN
F 1 "100pF" V 6909 1750 60  0000 C CNN
F 2 "" V 7050 1750 60  0000 C CNN
F 3 "" V 7050 1750 60  0000 C CNN
	1    7050 1750
	0    1    1    0   
$EndComp
$Comp
L akizuki:C C?
U 1 1 5EFC41FB
P 7850 1050
F 0 "C?" V 7603 1050 60  0000 C CNN
F 1 "150pF" V 7709 1050 60  0000 C CNN
F 2 "" V 7850 1050 60  0000 C CNN
F 3 "" V 7850 1050 60  0000 C CNN
	1    7850 1050
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 1950 7450 1950
Wire Wire Line
	7450 1950 7450 1450
Wire Wire Line
	7450 1450 7700 1450
Wire Wire Line
	7450 1450 7450 1050
Wire Wire Line
	7450 1050 7700 1050
Connection ~ 7450 1450
Wire Wire Line
	8150 2050 8300 2050
Wire Wire Line
	8300 2050 8300 1450
Wire Wire Line
	8300 1450 8000 1450
Wire Wire Line
	8300 1450 8300 1050
Wire Wire Line
	8300 1050 8000 1050
Connection ~ 8300 1450
Wire Wire Line
	7550 2150 7300 2150
Wire Wire Line
	7300 2150 7300 1750
Wire Wire Line
	7300 1750 7200 1750
Connection ~ 7300 2150
Wire Wire Line
	7300 2150 7200 2150
Wire Wire Line
	6900 2150 6800 2150
Wire Wire Line
	6900 1750 6800 1750
Wire Wire Line
	6800 1750 6800 2150
Connection ~ 6800 2150
Wire Wire Line
	6250 2150 6800 2150
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
F 1 "R" H 1850 3916 50  0000 C CNN
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
F 1 "R" H 1850 4766 50  0000 C CNN
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
$EndSCHEMATC
