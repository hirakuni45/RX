EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
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
Text HLabel 3050 1200 0    50   BiDi ~ 0
MISO
Text HLabel 3050 1300 0    50   BiDi ~ 0
MOSI
Text HLabel 3050 1400 0    50   BiDi ~ 0
SPCK
Text HLabel 3050 1500 0    50   BiDi ~ 0
SEL
Wire Wire Line
	3300 1600 3300 1050
Wire Wire Line
	3300 1700 3300 1800
$Comp
L power:GND #PWR065
U 1 1 61644132
P 3300 1800
F 0 "#PWR065" H 3300 1550 50  0001 C CNN
F 1 "GND" H 3305 1627 50  0000 C CNN
F 2 "" H 3300 1800 50  0001 C CNN
F 3 "" H 3300 1800 50  0001 C CNN
	1    3300 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR064
U 1 1 61644241
P 3300 1050
F 0 "#PWR064" H 3300 900 50  0001 C CNN
F 1 "+3.3V" H 3315 1223 50  0000 C CNN
F 2 "" H 3300 1050 50  0001 C CNN
F 3 "" H 3300 1050 50  0001 C CNN
	1    3300 1050
	1    0    0    -1  
$EndComp
Text HLabel 2100 3250 0    50   BiDi ~ 0
SCL
Text HLabel 2100 3350 0    50   BiDi ~ 0
SDA
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J18
U 1 1 616D64D6
P 3600 3350
F 0 "J18" H 3650 3667 50  0000 C CNN
F 1 "I2C_B" H 3650 3576 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 3600 3350 50  0001 C CNN
F 3 "~" H 3600 3350 50  0001 C CNN
	1    3600 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3250 3300 2950
Wire Wire Line
	3300 2950 4000 2950
Wire Wire Line
	4000 2950 4000 3250
Wire Wire Line
	4000 3250 3900 3250
Wire Wire Line
	3300 3250 3400 3250
Wire Wire Line
	3300 3350 3300 3700
Wire Wire Line
	3300 3700 4000 3700
Wire Wire Line
	4000 3700 4000 3350
Wire Wire Line
	4000 3350 3900 3350
Wire Wire Line
	3300 3350 3400 3350
Wire Wire Line
	3400 3450 3200 3450
Wire Wire Line
	3400 3550 3200 3550
Wire Wire Line
	3200 3550 3200 3700
Wire Wire Line
	3900 3550 4100 3550
Wire Wire Line
	4100 3550 4100 3700
Wire Wire Line
	3900 3450 4100 3450
$Comp
L power:+3.3V #PWR067
U 1 1 616D8F32
P 4100 3450
F 0 "#PWR067" H 4100 3300 50  0001 C CNN
F 1 "+3.3V" V 4115 3578 50  0000 L CNN
F 2 "" H 4100 3450 50  0001 C CNN
F 3 "" H 4100 3450 50  0001 C CNN
	1    4100 3450
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR061
U 1 1 616D90DF
P 3200 3450
F 0 "#PWR061" H 3200 3300 50  0001 C CNN
F 1 "+3.3V" V 3215 3578 50  0000 L CNN
F 2 "" H 3200 3450 50  0001 C CNN
F 3 "" H 3200 3450 50  0001 C CNN
	1    3200 3450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR062
U 1 1 616D9BC9
P 3200 3700
F 0 "#PWR062" H 3200 3450 50  0001 C CNN
F 1 "GND" H 3205 3527 50  0000 C CNN
F 2 "" H 3200 3700 50  0001 C CNN
F 3 "" H 3200 3700 50  0001 C CNN
	1    3200 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR068
U 1 1 616DA06C
P 4100 3700
F 0 "#PWR068" H 4100 3450 50  0001 C CNN
F 1 "GND" H 4105 3527 50  0000 C CNN
F 2 "" H 4100 3700 50  0001 C CNN
F 3 "" H 4100 3700 50  0001 C CNN
	1    4100 3700
	1    0    0    -1  
$EndComp
Text HLabel 5500 1850 0    50   BiDi ~ 0
RXD8
Text HLabel 5500 1950 0    50   BiDi ~ 0
TXD8
Text HLabel 5500 2050 0    50   BiDi ~ 0
SCK8
Wire Wire Line
	2100 3250 2250 3250
Connection ~ 3300 3250
Wire Wire Line
	2100 3350 2600 3350
Connection ~ 3300 3350
$Comp
L akizuki:R R25
U 1 1 61717E07
P 2250 2900
F 0 "R25" V 2204 2970 50  0000 L CNN
F 1 "1K" V 2295 2970 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2250 2830 50  0001 C CNN
F 3 "" V 2250 2900 50  0001 C CNN
	1    2250 2900
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R26
U 1 1 617182E9
P 2600 2900
F 0 "R26" V 2554 2970 50  0000 L CNN
F 1 "1K" V 2645 2970 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2600 2830 50  0001 C CNN
F 3 "" V 2600 2900 50  0001 C CNN
	1    2600 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 3050 2250 3250
Connection ~ 2250 3250
Wire Wire Line
	2250 3250 3300 3250
Wire Wire Line
	2600 3050 2600 3350
Connection ~ 2600 3350
Wire Wire Line
	2600 3350 3300 3350
Wire Wire Line
	2250 2750 2250 2600
Wire Wire Line
	2250 2600 2600 2600
Wire Wire Line
	2600 2600 2600 2750
Wire Wire Line
	2250 2600 2250 2450
Connection ~ 2250 2600
$Comp
L power:+3.3V #PWR060
U 1 1 61719A4D
P 2250 2450
F 0 "#PWR060" H 2250 2300 50  0001 C CNN
F 1 "+3.3V" H 2265 2623 50  0000 C CNN
F 2 "" H 2250 2450 50  0001 C CNN
F 3 "" H 2250 2450 50  0001 C CNN
	1    2250 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J21
U 1 1 617A2A5E
P 6450 1350
F 0 "J21" H 6500 1667 50  0000 C CNN
F 1 "SCI8" H 6500 1576 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" H 6450 1350 50  0001 C CNN
F 3 "~" H 6450 1350 50  0001 C CNN
	1    6450 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1950 6000 1950
Wire Wire Line
	6000 1950 6000 1250
Wire Wire Line
	6000 1250 6250 1250
Wire Wire Line
	5500 1850 7000 1850
Wire Wire Line
	7000 1850 7000 1250
Wire Wire Line
	7000 1250 6750 1250
Wire Wire Line
	7000 1850 7500 1850
Connection ~ 7000 1850
Wire Wire Line
	6000 1950 7600 1950
Connection ~ 6000 1950
Wire Wire Line
	5500 2050 7700 2050
Text HLabel 5500 2250 0    50   BiDi ~ 0
PB0
Text HLabel 5500 2350 0    50   BiDi ~ 0
PB3
Wire Wire Line
	7500 1850 7500 1150
Wire Wire Line
	7500 1150 8000 1150
Wire Wire Line
	8000 1250 7600 1250
Wire Wire Line
	7600 1250 7600 1950
Wire Wire Line
	7700 2050 7700 1350
Wire Wire Line
	7700 1350 8000 1350
Wire Wire Line
	7800 2250 7800 1450
Wire Wire Line
	7800 1450 8000 1450
$Comp
L Connector_Generic:Conn_01x07 J23
U 1 1 61CA4348
P 8200 1450
F 0 "J23" H 8280 1492 50  0000 L CNN
F 1 "SPI8" H 8280 1401 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 8200 1450 50  0001 C CNN
F 3 "~" H 8200 1450 50  0001 C CNN
	1    8200 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2350 5700 2350
Wire Wire Line
	7900 2350 7900 1550
Wire Wire Line
	7900 1550 8000 1550
Wire Wire Line
	5500 2250 5700 2250
$Comp
L Connector_Generic:Conn_01x08 J20
U 1 1 61CABB0A
P 3900 1500
F 0 "J20" H 3980 1492 50  0000 L CNN
F 1 "RSPI" H 3980 1401 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 3900 1500 50  0001 C CNN
F 3 "~" H 3900 1500 50  0001 C CNN
	1    3900 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1200 3700 1200
Wire Wire Line
	3050 1300 3700 1300
Wire Wire Line
	3050 1400 3700 1400
Wire Wire Line
	3050 1500 3700 1500
Wire Wire Line
	3300 1600 3700 1600
Wire Wire Line
	3300 1700 3700 1700
Wire Wire Line
	3700 1800 3500 1800
Wire Wire Line
	3500 1800 3500 2150
Wire Wire Line
	3500 2150 5700 2150
Wire Wire Line
	5700 2150 5700 2250
Connection ~ 5700 2250
Wire Wire Line
	5700 2250 6150 2250
Wire Wire Line
	5700 2350 5700 2450
Wire Wire Line
	5700 2450 3600 2450
Wire Wire Line
	3600 2450 3600 1900
Wire Wire Line
	3600 1900 3700 1900
Connection ~ 5700 2350
Wire Wire Line
	5700 2350 6850 2350
Wire Wire Line
	8000 1650 7400 1650
Wire Wire Line
	8000 1750 8000 2450
$Comp
L power:GND #PWR079
U 1 1 61CC9884
P 8000 2450
F 0 "#PWR079" H 8000 2200 50  0001 C CNN
F 1 "GND" H 8005 2277 50  0000 C CNN
F 2 "" H 8000 2450 50  0001 C CNN
F 3 "" H 8000 2450 50  0001 C CNN
	1    8000 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR077
U 1 1 61CC9CD3
P 7400 1650
F 0 "#PWR077" H 7400 1500 50  0001 C CNN
F 1 "+3.3V" V 7415 1778 50  0000 L CNN
F 2 "" H 7400 1650 50  0001 C CNN
F 3 "" H 7400 1650 50  0001 C CNN
	1    7400 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 1450 6150 1450
Wire Wire Line
	6150 1450 6150 2250
Connection ~ 6150 2250
Wire Wire Line
	6150 2250 7800 2250
Wire Wire Line
	6750 1450 6850 1450
Wire Wire Line
	6850 1450 6850 2350
Connection ~ 6850 2350
Wire Wire Line
	6850 2350 7900 2350
Wire Wire Line
	6250 1350 5700 1350
Wire Wire Line
	5700 1350 5700 1450
Wire Wire Line
	6750 1350 6850 1350
Wire Wire Line
	6850 1350 6850 1050
$Comp
L power:+3.3V #PWR073
U 1 1 61CE1FD4
P 6850 1050
F 0 "#PWR073" H 6850 900 50  0001 C CNN
F 1 "+3.3V" H 6865 1223 50  0000 C CNN
F 2 "" H 6850 1050 50  0001 C CNN
F 3 "" H 6850 1050 50  0001 C CNN
	1    6850 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR071
U 1 1 61CE2302
P 5700 1450
F 0 "#PWR071" H 5700 1200 50  0001 C CNN
F 1 "GND" H 5705 1277 50  0000 C CNN
F 2 "" H 5700 1450 50  0001 C CNN
F 3 "" H 5700 1450 50  0001 C CNN
	1    5700 1450
	1    0    0    -1  
$EndComp
Text HLabel 5500 3850 0    50   BiDi ~ 0
RXD11
Text HLabel 5500 3950 0    50   BiDi ~ 0
TXD11
Text HLabel 5500 4050 0    50   BiDi ~ 0
SCK11
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J22
U 1 1 61FCC12D
P 6450 3350
F 0 "J22" H 6500 3667 50  0000 C CNN
F 1 "SCI11" H 6500 3576 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" H 6450 3350 50  0001 C CNN
F 3 "~" H 6450 3350 50  0001 C CNN
	1    6450 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3950 5800 3950
Wire Wire Line
	6000 3950 6000 3250
Wire Wire Line
	6000 3250 6250 3250
Wire Wire Line
	5500 3850 5900 3850
Wire Wire Line
	7000 3850 7000 3250
Wire Wire Line
	7000 3250 6750 3250
Wire Wire Line
	7000 3850 7500 3850
Connection ~ 7000 3850
Wire Wire Line
	6000 3950 7600 3950
Connection ~ 6000 3950
Wire Wire Line
	5500 4050 7700 4050
Text HLabel 5500 4250 0    50   BiDi ~ 0
P32
Text HLabel 5500 4350 0    50   BiDi ~ 0
P33
Wire Wire Line
	7500 3850 7500 3150
Wire Wire Line
	7500 3150 8000 3150
Wire Wire Line
	8000 3250 7600 3250
Wire Wire Line
	7600 3250 7600 3950
Wire Wire Line
	7700 4050 7700 3350
Wire Wire Line
	7700 3350 8000 3350
Wire Wire Line
	7800 4250 7800 3450
Wire Wire Line
	7800 3450 8000 3450
$Comp
L Connector_Generic:Conn_01x07 J24
U 1 1 61FCC148
P 8200 3450
F 0 "J24" H 8280 3492 50  0000 L CNN
F 1 "SPI11" H 8280 3401 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 8200 3450 50  0001 C CNN
F 3 "~" H 8200 3450 50  0001 C CNN
	1    8200 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4350 7900 3550
Wire Wire Line
	7900 3550 8000 3550
Wire Wire Line
	8000 3650 7400 3650
Wire Wire Line
	8000 3750 8000 4450
$Comp
L power:GND #PWR080
U 1 1 61FCC15C
P 8000 4450
F 0 "#PWR080" H 8000 4200 50  0001 C CNN
F 1 "GND" H 8005 4277 50  0000 C CNN
F 2 "" H 8000 4450 50  0001 C CNN
F 3 "" H 8000 4450 50  0001 C CNN
	1    8000 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR078
U 1 1 61FCC162
P 7400 3650
F 0 "#PWR078" H 7400 3500 50  0001 C CNN
F 1 "+3.3V" V 7415 3778 50  0000 L CNN
F 2 "" H 7400 3650 50  0001 C CNN
F 3 "" H 7400 3650 50  0001 C CNN
	1    7400 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 3450 6150 3450
Wire Wire Line
	6150 3450 6150 4250
Connection ~ 6150 4250
Wire Wire Line
	6150 4250 7800 4250
Wire Wire Line
	6750 3450 6850 3450
Wire Wire Line
	6850 3450 6850 4350
Connection ~ 6850 4350
Wire Wire Line
	6850 4350 7900 4350
Wire Wire Line
	6250 3350 5700 3350
Wire Wire Line
	5700 3350 5700 3450
Wire Wire Line
	6750 3350 6850 3350
Wire Wire Line
	6850 3350 6850 3050
$Comp
L power:+3.3V #PWR074
U 1 1 61FCC174
P 6850 3050
F 0 "#PWR074" H 6850 2900 50  0001 C CNN
F 1 "+3.3V" H 6865 3223 50  0000 C CNN
F 2 "" H 6850 3050 50  0001 C CNN
F 3 "" H 6850 3050 50  0001 C CNN
	1    6850 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR072
U 1 1 61FCC17A
P 5700 3450
F 0 "#PWR072" H 5700 3200 50  0001 C CNN
F 1 "GND" H 5705 3277 50  0000 C CNN
F 2 "" H 5700 3450 50  0001 C CNN
F 3 "" H 5700 3450 50  0001 C CNN
	1    5700 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 4350 5600 4350
Wire Wire Line
	5500 4250 5700 4250
$Comp
L Connector_Generic:Conn_01x04 J19
U 1 1 620F8F3C
P 3700 4350
F 0 "J19" H 3780 4342 50  0000 L CNN
F 1 "I2C_A" H 3780 4251 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B4B-EH-A_1x04_P2.50mm_Vertical" H 3700 4350 50  0001 C CNN
F 3 "~" H 3700 4350 50  0001 C CNN
	1    3700 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4250 2250 4250
Wire Wire Line
	2250 4250 2250 3250
Wire Wire Line
	2600 3350 2600 4350
Wire Wire Line
	2600 4350 3500 4350
Wire Wire Line
	3500 4450 3200 4450
Wire Wire Line
	3500 4550 3350 4550
Wire Wire Line
	3350 4550 3350 4700
$Comp
L power:GND #PWR066
U 1 1 62107820
P 3350 4700
F 0 "#PWR066" H 3350 4450 50  0001 C CNN
F 1 "GND" H 3355 4527 50  0000 C CNN
F 2 "" H 3350 4700 50  0001 C CNN
F 3 "" H 3350 4700 50  0001 C CNN
	1    3350 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR063
U 1 1 62107AEB
P 3200 4450
F 0 "#PWR063" H 3200 4300 50  0001 C CNN
F 1 "+3.3V" V 3215 4578 50  0000 L CNN
F 2 "" H 3200 4450 50  0001 C CNN
F 3 "" H 3200 4450 50  0001 C CNN
	1    3200 4450
	0    -1   -1   0   
$EndComp
$Comp
L akizuki:MAX3485 U5
U 1 1 6111951B
P 6450 5600
F 0 "U5" H 6450 6165 50  0000 C CNN
F 1 "MAX3485" H 6450 6074 50  0000 C CNN
F 2 "Package_SO:SOP-8_3.76x4.96mm_P1.27mm" H 6450 6050 50  0001 C CNN
F 3 "" H 6450 6050 50  0001 C CNN
	1    6450 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 5300 5900 3850
Wire Wire Line
	5900 5300 6100 5300
Connection ~ 5900 3850
Wire Wire Line
	5900 3850 7000 3850
Wire Wire Line
	5800 3950 5800 5900
Wire Wire Line
	5800 5900 6100 5900
Connection ~ 5800 3950
Wire Wire Line
	5800 3950 6000 3950
Wire Wire Line
	6100 5500 5700 5500
Wire Wire Line
	5700 5500 5700 4250
Connection ~ 5700 4250
Wire Wire Line
	5700 4250 6150 4250
Wire Wire Line
	6100 5700 5600 5700
Wire Wire Line
	5600 5700 5600 4350
Connection ~ 5600 4350
Wire Wire Line
	5600 4350 6850 4350
Wire Wire Line
	6800 5300 7000 5300
Wire Wire Line
	7000 5300 7000 5000
Wire Wire Line
	6800 5900 7000 5900
Wire Wire Line
	7000 5900 7000 6150
$Comp
L power:GND #PWR076
U 1 1 61135289
P 7000 6150
F 0 "#PWR076" H 7000 5900 50  0001 C CNN
F 1 "GND" H 7005 5977 50  0000 C CNN
F 2 "" H 7000 6150 50  0001 C CNN
F 3 "" H 7000 6150 50  0001 C CNN
	1    7000 6150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR075
U 1 1 6113A629
P 7000 5000
F 0 "#PWR075" H 7000 4850 50  0001 C CNN
F 1 "+3.3V" H 7015 5173 50  0000 C CNN
F 2 "" H 7000 5000 50  0001 C CNN
F 3 "" H 7000 5000 50  0001 C CNN
	1    7000 5000
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R27
U 1 1 6113A9AB
P 7650 5500
F 0 "R27" H 7650 5293 50  0000 C CNN
F 1 "120" H 7650 5384 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7650 5430 50  0001 C CNN
F 3 "" V 7650 5500 50  0001 C CNN
	1    7650 5500
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J25
U 1 1 6113BA39
P 8200 5500
F 0 "J25" H 8280 5492 50  0000 L CNN
F 1 "RS-485 TERM" H 8280 5401 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8200 5500 50  0001 C CNN
F 3 "~" H 8200 5500 50  0001 C CNN
	1    8200 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 5500 7200 5500
Wire Wire Line
	7800 5500 8000 5500
Wire Wire Line
	8000 5600 7900 5600
Wire Wire Line
	7900 5600 7900 5700
Wire Wire Line
	7900 5700 7200 5700
$Comp
L Connector_Generic:Conn_01x03 J26
U 1 1 6114B3D6
P 9300 5500
F 0 "J26" H 9380 5542 50  0000 L CNN
F 1 "RS-485" H 9380 5451 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B3B-EH-A_1x03_P2.50mm_Vertical" H 9300 5500 50  0001 C CNN
F 3 "~" H 9300 5500 50  0001 C CNN
	1    9300 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5500 7200 5200
Wire Wire Line
	7200 5200 8900 5200
Wire Wire Line
	8900 5200 8900 5400
Wire Wire Line
	8900 5400 9100 5400
Connection ~ 7200 5500
Wire Wire Line
	7200 5500 7500 5500
Wire Wire Line
	9100 5500 8900 5500
Wire Wire Line
	8900 5500 8900 5950
Wire Wire Line
	8900 5950 7200 5950
Wire Wire Line
	7200 5950 7200 5700
Connection ~ 7200 5700
Wire Wire Line
	7200 5700 6800 5700
Wire Wire Line
	9100 5600 9000 5600
Wire Wire Line
	9000 5600 9000 6000
$Comp
L power:GND #PWR081
U 1 1 6115D417
P 9000 6000
F 0 "#PWR081" H 9000 5750 50  0001 C CNN
F 1 "GND" H 9005 5827 50  0000 C CNN
F 2 "" H 9000 6000 50  0001 C CNN
F 3 "" H 9000 6000 50  0001 C CNN
	1    9000 6000
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C19
U 1 1 6115ED0C
P 4600 5550
F 0 "C19" H 4683 5603 60  0000 L CNN
F 1 "0.1uF" H 4683 5497 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4600 5550 60  0001 C CNN
F 3 "" V 4600 5550 60  0001 C CNN
	1    4600 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR070
U 1 1 6115F08A
P 4600 5700
F 0 "#PWR070" H 4600 5450 50  0001 C CNN
F 1 "GND" H 4605 5527 50  0000 C CNN
F 2 "" H 4600 5700 50  0001 C CNN
F 3 "" H 4600 5700 50  0001 C CNN
	1    4600 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR069
U 1 1 6115F4CE
P 4600 5400
F 0 "#PWR069" H 4600 5250 50  0001 C CNN
F 1 "+3.3V" H 4615 5573 50  0000 C CNN
F 2 "" H 4600 5400 50  0001 C CNN
F 3 "" H 4600 5400 50  0001 C CNN
	1    4600 5400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
