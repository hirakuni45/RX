EESchema Schematic File Version 4
LIBS:canif-cache
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
L analog:SN65HVD230 U?
U 1 1 5FA49842
P 4850 3600
F 0 "U?" H 4850 4125 50  0000 C CNN
F 1 "SN65HVD232" H 4850 4034 50  0000 C CNN
F 2 "Package_SO:SOIC-8-1EP_3.9x4.9mm_P1.27mm_EP2.514x3.2mm" H 4850 4000 50  0001 C CNN
F 3 "" H 4850 4000 50  0001 C CNN
	1    4850 3600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x06_Top_Bottom J?
U 1 1 5FA4BC3F
P 2750 3500
F 0 "J?" H 2800 2975 50  0000 C CNN
F 1 "Pmod1" H 2800 3066 50  0000 C CNN
F 2 "" H 2750 3500 50  0001 C CNN
F 3 "~" H 2750 3500 50  0001 C CNN
	1    2750 3500
	1    0    0    1   
$EndComp
Wire Wire Line
	2550 3200 2350 3200
Wire Wire Line
	2350 3200 2350 2750
Wire Wire Line
	2350 2750 3250 2750
Wire Wire Line
	3250 2750 3250 3200
Wire Wire Line
	3250 3200 3050 3200
Wire Wire Line
	3250 2750 3250 2600
Connection ~ 3250 2750
$Comp
L power:+3V3 #PWR?
U 1 1 5FA4D3AF
P 3250 2600
F 0 "#PWR?" H 3250 2450 50  0001 C CNN
F 1 "+3V3" H 3265 2773 50  0000 C CNN
F 2 "" H 3250 2600 50  0001 C CNN
F 3 "" H 3250 2600 50  0001 C CNN
	1    3250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3300 2350 3300
Wire Wire Line
	2350 3300 2350 4000
Wire Wire Line
	2350 4000 3250 4000
Wire Wire Line
	3250 4000 3250 3300
Wire Wire Line
	3250 3300 3050 3300
Wire Wire Line
	2350 4000 2350 4150
Connection ~ 2350 4000
$Comp
L power:GND #PWR?
U 1 1 5FA4DED2
P 2350 4150
F 0 "#PWR?" H 2350 3900 50  0001 C CNN
F 1 "GND" H 2355 3977 50  0000 C CNN
F 2 "" H 2350 4150 50  0001 C CNN
F 3 "" H 2350 4150 50  0001 C CNN
	1    2350 4150
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R-78E5 M?
U 1 1 5FA4F61B
P 4900 5000
F 0 "M?" H 4900 5315 50  0000 C CNN
F 1 "R-78E5" H 4900 5224 50  0000 C CNN
F 2 "" H 4900 5200 50  0001 C CNN
F 3 "" H 4900 5200 50  0001 C CNN
	1    4900 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5FA52AAB
P 6700 3500
F 0 "J?" H 6780 3492 50  0000 L CNN
F 1 "For ODB2" H 6780 3401 50  0000 L CNN
F 2 "" H 6700 3500 50  0001 C CNN
F 3 "~" H 6700 3500 50  0001 C CNN
	1    6700 3500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5FA53FAF
P 6700 4900
F 0 "J?" H 6780 4892 50  0000 L CNN
F 1 "+5V Out" H 6780 4801 50  0000 L CNN
F 2 "" H 6700 4900 50  0001 C CNN
F 3 "~" H 6700 4900 50  0001 C CNN
	1    6700 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3700 2150 3700
Wire Wire Line
	2150 3700 2150 4500
Wire Wire Line
	3050 3700 4500 3700
Wire Wire Line
	4500 3900 4300 3900
Wire Wire Line
	4300 3900 4300 4150
$Comp
L power:GND #PWR?
U 1 1 5FA5D8BE
P 4300 4150
F 0 "#PWR?" H 4300 3900 50  0001 C CNN
F 1 "GND" H 4305 3977 50  0000 C CNN
F 2 "" H 4300 4150 50  0001 C CNN
F 3 "" H 4300 4150 50  0001 C CNN
	1    4300 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3300 4300 3300
Wire Wire Line
	4300 3300 4300 3000
$Comp
L power:+3V3 #PWR?
U 1 1 5FA5E16A
P 4300 3000
F 0 "#PWR?" H 4300 2850 50  0001 C CNN
F 1 "+3V3" H 4315 3173 50  0000 C CNN
F 2 "" H 4300 3000 50  0001 C CNN
F 3 "" H 4300 3000 50  0001 C CNN
	1    4300 3000
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CAP C?
U 1 1 5FA5EB24
P 4800 2250
F 0 "C?" H 4883 2303 60  0000 L CNN
F 1 "0.1uF" H 4883 2197 60  0000 L CNN
F 2 "" V 4800 2250 60  0000 C CNN
F 3 "" V 4800 2250 60  0000 C CNN
	1    4800 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2400 4800 2600
Wire Wire Line
	4800 2100 4800 1900
$Comp
L power:+3V3 #PWR?
U 1 1 5FA60162
P 4800 1900
F 0 "#PWR?" H 4800 1750 50  0001 C CNN
F 1 "+3V3" H 4815 2073 50  0000 C CNN
F 2 "" H 4800 1900 50  0001 C CNN
F 3 "" H 4800 1900 50  0001 C CNN
	1    4800 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FA6032E
P 4800 2600
F 0 "#PWR?" H 4800 2350 50  0001 C CNN
F 1 "GND" H 4805 2427 50  0000 C CNN
F 2 "" H 4800 2600 50  0001 C CNN
F 3 "" H 4800 2600 50  0001 C CNN
	1    4800 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3500 5500 3500
Wire Wire Line
	5200 3700 6000 3700
Wire Wire Line
	6000 3700 6000 3600
Wire Wire Line
	6000 3600 6500 3600
Wire Wire Line
	6500 3700 6350 3700
Wire Wire Line
	6350 3700 6350 3950
$Comp
L power:GND #PWR?
U 1 1 5FA610A3
P 6350 3950
F 0 "#PWR?" H 6350 3700 50  0001 C CNN
F 1 "GND" H 6355 3777 50  0000 C CNN
F 2 "" H 6350 3950 50  0001 C CNN
F 3 "" H 6350 3950 50  0001 C CNN
	1    6350 3950
	1    0    0    -1  
$EndComp
Text Notes 7250 3400 0    50   ~ 0
1: +12V
Text Notes 7250 3500 0    50   ~ 0
2: CANH
Text Notes 7250 3600 0    50   ~ 0
3: CANL
Text Notes 7250 3700 0    50   ~ 0
4: GND
Wire Wire Line
	6500 3400 5800 3400
Wire Wire Line
	5800 3400 5800 4550
$Comp
L power:GND #PWR?
U 1 1 5FA62912
P 4900 5800
F 0 "#PWR?" H 4900 5550 50  0001 C CNN
F 1 "GND" H 4905 5627 50  0000 C CNN
F 2 "" H 4900 5800 50  0001 C CNN
F 3 "" H 4900 5800 50  0001 C CNN
	1    4900 5800
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 5FA62AEF
P 5800 2500
F 0 "R?" H 5800 2707 50  0000 C CNN
F 1 "120" H 5800 2616 50  0000 C CNN
F 2 "" H 5800 2430 50  0000 C CNN
F 3 "" V 5800 2500 50  0000 C CNN
	1    5800 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3500 5500 2500
Wire Wire Line
	5500 2500 5650 2500
Connection ~ 5500 3500
Wire Wire Line
	5500 3500 6500 3500
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5FA64464
P 6400 2600
F 0 "J?" H 6480 2642 50  0000 L CNN
F 1 "Term: Enable(1 to 2), Disable(2-3)" H 6480 2551 50  0000 L CNN
F 2 "" H 6400 2600 50  0001 C CNN
F 3 "~" H 6400 2600 50  0001 C CNN
	1    6400 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2500 5950 2500
Wire Wire Line
	6200 2600 6000 2600
Wire Wire Line
	6000 2600 6000 3600
Connection ~ 6000 3600
Wire Wire Line
	6500 5000 5650 5000
Wire Wire Line
	6500 4900 6250 4900
Wire Wire Line
	6250 4900 6250 5250
$Comp
L power:GND #PWR?
U 1 1 5FA687A7
P 6250 5250
F 0 "#PWR?" H 6250 5000 50  0001 C CNN
F 1 "GND" H 6255 5077 50  0000 C CNN
F 2 "" H 6250 5250 50  0001 C CNN
F 3 "" H 6250 5250 50  0001 C CNN
	1    6250 5250
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C-POL C?
U 1 1 5FA689A7
P 5650 5400
F 0 "C?" H 5733 5453 60  0000 L CNN
F 1 "10uF" H 5733 5347 60  0000 L CNN
F 2 "" V 5650 5400 60  0000 C CNN
F 3 "" V 5650 5400 60  0000 C CNN
	1    5650 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5250 5650 5000
Connection ~ 5650 5000
Wire Wire Line
	5650 5000 5300 5000
$Comp
L akizuki:C-POL C?
U 1 1 5FA6A90A
P 4100 5400
F 0 "C?" H 4183 5453 60  0000 L CNN
F 1 "10uF" H 4183 5347 60  0000 L CNN
F 2 "" V 4100 5400 60  0000 C CNN
F 3 "" V 4100 5400 60  0000 C CNN
	1    4100 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3300 5350 2000
$Comp
L akizuki:R R?
U 1 1 5FA6E11E
P 5800 2000
F 0 "R?" H 5800 2207 50  0000 C CNN
F 1 "47K" H 5800 2116 50  0000 C CNN
F 2 "" H 5800 1930 50  0000 C CNN
F 3 "" V 5800 2000 50  0000 C CNN
	1    5800 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2000 5350 2000
Wire Wire Line
	5950 2000 6200 2000
Wire Wire Line
	6200 2000 6200 2150
$Comp
L power:GND #PWR?
U 1 1 5FA6FCF6
P 6200 2150
F 0 "#PWR?" H 6200 1900 50  0001 C CNN
F 1 "GND" H 6205 1977 50  0000 C CNN
F 2 "" H 6200 2150 50  0001 C CNN
F 3 "" H 6200 2150 50  0001 C CNN
	1    6200 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3300 5350 3300
Wire Wire Line
	4900 5350 4900 5700
Wire Wire Line
	4100 5250 4100 5000
Wire Wire Line
	4100 5000 4500 5000
Wire Wire Line
	4100 5550 4100 5700
Wire Wire Line
	4100 5700 4900 5700
Connection ~ 4900 5700
Wire Wire Line
	4900 5700 4900 5800
Wire Wire Line
	4900 5700 5650 5700
Wire Wire Line
	5650 5700 5650 5550
Wire Wire Line
	4100 5000 4100 4550
Wire Wire Line
	4100 4550 5800 4550
Connection ~ 4100 5000
Text Notes 2150 3700 0    50   ~ 0
CTX
Text Notes 3300 3700 0    50   ~ 0
CRX
Wire Wire Line
	3700 4500 3700 3500
Wire Wire Line
	3700 3500 4500 3500
Wire Wire Line
	2150 4500 3700 4500
$EndSCHEMATC
