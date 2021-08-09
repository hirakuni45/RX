EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 8
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
L renesas:E1_E2_Lite J9
U 1 1 61062D7C
P 3600 3300
F 0 "J9" H 3600 4115 50  0000 C CNN
F 1 "E1_E2_Lite" H 3600 4024 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x07_P2.54mm_Vertical" H 3600 4000 50  0001 C CNN
F 3 "" H 3600 4000 50  0001 C CNN
	1    3600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3650 2850 3650
Wire Wire Line
	2850 3650 2850 3750
Wire Wire Line
	3150 3750 2850 3750
Wire Wire Line
	3150 3850 2850 3850
Wire Wire Line
	2850 3850 2850 3750
Connection ~ 2850 3750
Wire Wire Line
	2850 3850 2850 4100
Connection ~ 2850 3850
$Comp
L power:GND #PWR022
U 1 1 61063838
P 2850 4100
F 0 "#PWR022" H 2850 3850 50  0001 C CNN
F 1 "GND" H 2855 3927 50  0000 C CNN
F 2 "" H 2850 4100 50  0001 C CNN
F 3 "" H 2850 4100 50  0001 C CNN
	1    2850 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2750 4350 2750
Wire Wire Line
	4050 2850 4650 2850
Wire Wire Line
	4050 3050 4950 3050
Wire Wire Line
	4050 3150 5250 3150
Wire Wire Line
	4050 3350 5850 3350
Text HLabel 6350 2750 2    50   Output ~ 0
TCK_FINEC
Text HLabel 6350 2850 2    50   Output ~ 0
TMS
Text HLabel 6350 2950 2    50   Output ~ 0
TRSTn
Text HLabel 6350 3050 2    50   Output ~ 0
TDI_RXD1
Text HLabel 6350 3150 2    50   Input ~ 0
TDO_TXD1
Text HLabel 6350 3350 2    50   BiDi ~ 0
RESn
Text HLabel 6350 3650 2    50   BiDi ~ 0
UB
Text HLabel 6350 3750 2    50   BiDi ~ 0
MD_FINED
Text HLabel 6350 3850 2    50   BiDi ~ 0
EMLE
$Comp
L akizuki:R R3
U 1 1 61159332
P 4350 2250
F 0 "R3" V 4304 2320 50  0000 L CNN
F 1 "4.7K" V 4395 2320 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4350 2180 50  0001 C CNN
F 3 "" V 4350 2250 50  0001 C CNN
	1    4350 2250
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R4
U 1 1 61159435
P 4650 2250
F 0 "R4" V 4604 2320 50  0000 L CNN
F 1 "4.7K" V 4695 2320 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4650 2180 50  0001 C CNN
F 3 "" V 4650 2250 50  0001 C CNN
	1    4650 2250
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R6
U 1 1 6115953D
P 4950 2250
F 0 "R6" V 4996 2180 50  0000 R CNN
F 1 "4.7K" V 4905 2180 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4950 2180 50  0001 C CNN
F 3 "" V 4950 2250 50  0001 C CNN
	1    4950 2250
	0    -1   -1   0   
$EndComp
$Comp
L akizuki:R R7
U 1 1 61159693
P 5250 2250
F 0 "R7" V 5204 2320 50  0000 L CNN
F 1 "4.7K" V 5295 2320 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5250 2180 50  0001 C CNN
F 3 "" V 5250 2250 50  0001 C CNN
	1    5250 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 2400 4350 2750
Connection ~ 4350 2750
Wire Wire Line
	4350 2750 6350 2750
Wire Wire Line
	4650 2400 4650 2850
Connection ~ 4650 2850
Wire Wire Line
	4650 2850 6350 2850
Wire Wire Line
	5250 2400 5250 3150
Connection ~ 5250 3150
Wire Wire Line
	4050 2950 4800 2950
Wire Wire Line
	4950 2400 4950 3050
Connection ~ 4950 3050
$Comp
L akizuki:R R5
U 1 1 6115A2FE
P 4800 4250
F 0 "R5" V 4846 4180 50  0000 R CNN
F 1 "4.7K" V 4755 4180 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4800 4180 50  0001 C CNN
F 3 "" V 4800 4250 50  0001 C CNN
	1    4800 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4800 4100 4800 2950
Connection ~ 4800 2950
Wire Wire Line
	4800 2950 6350 2950
Wire Wire Line
	4350 2100 4350 1900
Wire Wire Line
	4350 1900 4650 1900
Wire Wire Line
	4650 1900 4650 2100
Wire Wire Line
	4950 1900 4950 2100
Connection ~ 4650 1900
Wire Wire Line
	4950 1900 5250 1900
Wire Wire Line
	5250 1900 5250 2100
Connection ~ 4950 1900
Wire Wire Line
	4800 4400 4800 4600
$Comp
L power:GND #PWR025
U 1 1 6115BD12
P 4800 4600
F 0 "#PWR025" H 4800 4350 50  0001 C CNN
F 1 "GND" H 4805 4427 50  0000 C CNN
F 2 "" H 4800 4600 50  0001 C CNN
F 3 "" H 4800 4600 50  0001 C CNN
	1    4800 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1900 4350 1600
$Comp
L power:+3.3V #PWR024
U 1 1 6115C288
P 4350 1600
F 0 "#PWR024" H 4350 1450 50  0001 C CNN
F 1 "+3.3V" H 4365 1773 50  0000 C CNN
F 2 "" H 4350 1600 50  0001 C CNN
F 3 "" H 4350 1600 50  0001 C CNN
	1    4350 1600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 61170838
P 4600 5550
AR Path="/61044A6A/61170838" Ref="J?"  Part="1" 
AR Path="/6106749E/61170838" Ref="J10"  Part="1" 
F 0 "J10" H 4518 5867 50  0000 C CNN
F 1 "EMU_MODE" H 4518 5776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4600 5550 50  0001 C CNN
F 3 "~" H 4600 5550 50  0001 C CNN
	1    4600 5550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4800 5450 5000 5450
Wire Wire Line
	5000 5450 5000 5250
Wire Wire Line
	5000 5250 5150 5250
Wire Wire Line
	4800 5650 5000 5650
Wire Wire Line
	5000 5650 5000 5850
Wire Wire Line
	5000 5850 5150 5850
$Comp
L akizuki:R R?
U 1 1 61170845
P 5300 5250
AR Path="/61044A6A/61170845" Ref="R?"  Part="1" 
AR Path="/6106749E/61170845" Ref="R8"  Part="1" 
F 0 "R8" H 5300 5457 50  0000 C CNN
F 1 "1K" H 5300 5366 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5300 5180 50  0001 C CNN
F 3 "" V 5300 5250 50  0001 C CNN
	1    5300 5250
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R?
U 1 1 6117084B
P 5300 5850
AR Path="/61044A6A/6117084B" Ref="R?"  Part="1" 
AR Path="/6106749E/6117084B" Ref="R9"  Part="1" 
F 0 "R9" H 5300 6057 50  0000 C CNN
F 1 "4.7K" H 5300 5966 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5300 5780 50  0001 C CNN
F 3 "" V 5300 5850 50  0001 C CNN
	1    5300 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5850 5550 5850
Wire Wire Line
	5550 5850 5550 6100
Wire Wire Line
	5450 5250 5550 5250
Wire Wire Line
	5550 5250 5550 5100
$Comp
L power:+3.3V #PWR?
U 1 1 61170855
P 5550 5100
AR Path="/61044A6A/61170855" Ref="#PWR?"  Part="1" 
AR Path="/6106749E/61170855" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 5550 4950 50  0001 C CNN
F 1 "+3.3V" H 5565 5273 50  0000 C CNN
F 2 "" H 5550 5100 50  0001 C CNN
F 3 "" H 5550 5100 50  0001 C CNN
	1    5550 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 5550 5850 5550
Wire Wire Line
	5850 5550 5850 3850
Connection ~ 5850 3850
Wire Wire Line
	5850 3850 6350 3850
$Comp
L power:GND #PWR020
U 1 1 611861E1
P 2950 7350
F 0 "#PWR020" H 2950 7100 50  0001 C CNN
F 1 "GND" H 2955 7177 50  0000 C CNN
F 2 "" H 2950 7350 50  0001 C CNN
F 3 "" H 2950 7350 50  0001 C CNN
	1    2950 7350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R1
U 1 1 611861E7
P 4000 6300
F 0 "R1" V 4046 6230 50  0000 R CNN
F 1 "4.7K" V 3955 6230 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4000 6230 50  0001 C CNN
F 3 "" V 4000 6300 50  0001 C CNN
	1    4000 6300
	-1   0    0    1   
$EndComp
$Comp
L akizuki:R R2
U 1 1 611861ED
P 4000 7000
F 0 "R2" V 3954 7070 50  0000 L CNN
F 1 "4.7K" V 4045 7070 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4000 6930 50  0001 C CNN
F 3 "" V 4000 7000 50  0001 C CNN
	1    4000 7000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR023
U 1 1 611861FD
P 3750 5850
F 0 "#PWR023" H 3750 5700 50  0001 C CNN
F 1 "+3.3V" H 3765 6023 50  0000 C CNN
F 2 "" H 3750 5850 50  0001 C CNN
F 3 "" H 3750 5850 50  0001 C CNN
	1    3750 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3850 5850 3850
Wire Wire Line
	3150 2750 2850 2750
Wire Wire Line
	2850 2750 2850 2500
$Comp
L power:+3.3V #PWR021
U 1 1 6118C5F0
P 2850 2500
F 0 "#PWR021" H 2850 2350 50  0001 C CNN
F 1 "+3.3V" H 2865 2673 50  0000 C CNN
F 2 "" H 2850 2500 50  0001 C CNN
F 3 "" H 2850 2500 50  0001 C CNN
	1    2850 2500
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R10
U 1 1 6105AAF8
P 5850 2250
F 0 "R10" V 5804 2320 50  0000 L CNN
F 1 "4.7K" V 5895 2320 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5850 2180 50  0001 C CNN
F 3 "" V 5850 2250 50  0001 C CNN
	1    5850 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 1900 5850 1900
Wire Wire Line
	5850 1900 5850 2100
Connection ~ 5250 1900
Wire Wire Line
	5850 2400 5850 3350
Connection ~ 5850 3350
Wire Wire Line
	5850 3350 6350 3350
NoConn ~ 4050 3550
Connection ~ 4350 1900
Wire Wire Line
	4650 1900 4950 1900
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J11
U 1 1 610B9F31
P 7650 4750
F 0 "J11" H 7700 5067 50  0000 C CNN
F 1 "SCI1" H 7700 4976 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" H 7650 4750 50  0001 C CNN
F 3 "~" H 7650 4750 50  0001 C CNN
	1    7650 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4650 6000 4650
Wire Wire Line
	7950 4650 8050 4650
Wire Wire Line
	8050 4650 8050 4300
Wire Wire Line
	8050 4300 6100 4300
Wire Wire Line
	5250 3150 6000 3150
Wire Wire Line
	4950 3050 6100 3050
Wire Wire Line
	6000 4650 6000 3150
Connection ~ 6000 3150
Wire Wire Line
	6000 3150 6350 3150
Wire Wire Line
	6100 4300 6100 3050
Connection ~ 6100 3050
Wire Wire Line
	6100 3050 6350 3050
Wire Wire Line
	7050 4750 7050 5250
Wire Wire Line
	7050 4750 7450 4750
$Comp
L power:GND #PWR027
U 1 1 610C36BA
P 7050 5250
F 0 "#PWR027" H 7050 5000 50  0001 C CNN
F 1 "GND" H 7055 5077 50  0000 C CNN
F 2 "" H 7050 5250 50  0001 C CNN
F 3 "" H 7050 5250 50  0001 C CNN
	1    7050 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 4750 8500 4750
NoConn ~ 7950 4850
NoConn ~ 7450 4850
$Comp
L power:+3.3V #PWR?
U 1 1 611CF909
P 8500 4850
AR Path="/611CF909" Ref="#PWR?"  Part="1" 
AR Path="/6106749E/611CF909" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 8500 4700 50  0001 C CNN
F 1 "+3.3V" V 8515 4978 50  0000 L CNN
F 2 "" H 8500 4850 50  0001 C CNN
F 3 "" H 8500 4850 50  0001 C CNN
	1    8500 4850
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 611CF90F
P 8700 4750
AR Path="/611CF90F" Ref="J?"  Part="1" 
AR Path="/6106749E/611CF90F" Ref="J6"  Part="1" 
F 0 "J6" H 8780 4742 50  0000 L CNN
F 1 "SCI1_POW" H 8780 4651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8700 4750 50  0001 C CNN
F 3 "~" H 8700 4750 50  0001 C CNN
	1    8700 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 611735FC
P 4850 6400
F 0 "J7" H 4930 6442 50  0000 L CNN
F 1 "UB" H 4930 6351 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4850 6400 50  0001 C CNN
F 3 "~" H 4850 6400 50  0001 C CNN
	1    4850 6400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J27
U 1 1 61174E7E
P 4850 7100
F 0 "J27" H 4930 7142 50  0000 L CNN
F 1 "MD" H 4930 7051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4850 7100 50  0001 C CNN
F 3 "~" H 4850 7100 50  0001 C CNN
	1    4850 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3650 4400 3650
Wire Wire Line
	4050 3750 4300 3750
Wire Wire Line
	4650 6400 4400 6400
Wire Wire Line
	4400 6400 4400 3650
Connection ~ 4400 3650
Wire Wire Line
	4400 3650 6350 3650
Wire Wire Line
	4650 7100 4300 7100
Wire Wire Line
	4300 7100 4300 3750
Connection ~ 4300 3750
Wire Wire Line
	4300 3750 6350 3750
Wire Wire Line
	4650 6300 4150 6300
Wire Wire Line
	4650 7000 4150 7000
Wire Wire Line
	3850 7000 3750 7000
Wire Wire Line
	3750 7000 3750 6300
Wire Wire Line
	3750 6300 3850 6300
Wire Wire Line
	3750 6300 3750 5850
Connection ~ 3750 6300
$Comp
L akizuki:R R30
U 1 1 6118350E
P 3300 6500
F 0 "R30" H 3300 6707 50  0000 C CNN
F 1 "4.7K" H 3300 6616 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3300 6430 50  0001 C CNN
F 3 "" V 3300 6500 50  0001 C CNN
	1    3300 6500
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R31
U 1 1 611842BE
P 3300 7200
F 0 "R31" H 3300 7407 50  0000 C CNN
F 1 "4.7K" H 3300 7316 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3300 7130 50  0001 C CNN
F 3 "" V 3300 7200 50  0001 C CNN
	1    3300 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 6500 3450 6500
Wire Wire Line
	4650 7200 3450 7200
Wire Wire Line
	3150 6500 2950 6500
Wire Wire Line
	2950 6500 2950 7200
Wire Wire Line
	2950 7200 3150 7200
Wire Wire Line
	2950 7200 2950 7350
Connection ~ 2950 7200
$EndSCHEMATC
