EESchema Schematic File Version 4
LIBS:MaxRX72T-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
L renesas:RX72T_144 U1
U 1 1 5E7FA70B
P 5050 6450
F 0 "U1" H 5050 6965 50  0000 C CNN
F 1 "RX72T_144" H 5050 6874 50  0000 C CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 5500 7500 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 5500 7500 50  0001 C CNN
	1    5050 6450
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_144 U1
U 2 1 5E806460
P 2900 3050
F 0 "U1" H 2900 5150 50  0000 C CNN
F 1 "RX72T_144" H 2900 950 50  0000 C CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 3350 4100 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 3350 4100 50  0001 C CNN
	2    2900 3050
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_144 U1
U 3 1 5E809510
P 5900 3050
F 0 "U1" H 5900 5150 50  0000 C CNN
F 1 "RX72T_144" H 5900 950 50  0000 C CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 6350 4100 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 6350 4100 50  0001 C CNN
	3    5900 3050
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_144 U1
U 4 1 5E80D844
P 8900 2000
F 0 "U1" H 8900 3050 50  0000 C CNN
F 1 "RX72T_144" H 8900 900 50  0000 C CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 9350 3050 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 9350 3050 50  0001 C CNN
	4    8900 2000
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CRYSTAL X1
U 1 1 5E84009A
P 6150 6350
F 0 "X1" V 5893 6350 60  0000 C CNN
F 1 "8MHz" V 5999 6350 60  0000 C CNN
F 2 "Crystal:Crystal_SMD_HC49-SD_HandSoldering" V 5950 6350 60  0001 C CNN
F 3 "" V 6150 6350 60  0000 C CNN
	1    6150 6350
	0    1    1    0   
$EndComp
Wire Wire Line
	5650 6350 5900 6350
Wire Wire Line
	5650 6550 6450 6550
Wire Wire Line
	6450 6550 6450 6350
Wire Wire Line
	6450 6350 6300 6350
$Comp
L akizuki:C C16
U 1 1 5E84175C
P 6450 6800
F 0 "C16" H 6532 6853 60  0000 L CNN
F 1 "15pF" H 6532 6747 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6450 6800 60  0001 C CNN
F 3 "" V 6450 6800 60  0000 C CNN
	1    6450 6800
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C15
U 1 1 5E842CAB
P 5900 6800
F 0 "C15" H 5982 6853 60  0000 L CNN
F 1 "15pF" H 5982 6747 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5900 6800 60  0001 C CNN
F 3 "" V 5900 6800 60  0000 C CNN
	1    5900 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 6650 6450 6550
Connection ~ 6450 6550
Wire Wire Line
	5900 6650 5900 6350
Connection ~ 5900 6350
Wire Wire Line
	5900 6350 6000 6350
Wire Wire Line
	5900 6950 5900 7050
Wire Wire Line
	5900 7050 6450 7050
Wire Wire Line
	6450 7050 6450 7150
Wire Wire Line
	6450 6950 6450 7050
Connection ~ 6450 7050
$Comp
L power:GND #PWR040
U 1 1 5E844ED0
P 6450 7150
F 0 "#PWR040" H 6450 6900 50  0001 C CNN
F 1 "GND" H 6455 6977 50  0000 C CNN
F 2 "" H 6450 7150 50  0001 C CNN
F 3 "" H 6450 7150 50  0001 C CNN
	1    6450 7150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J9
U 1 1 5E84BA47
P 2450 6500
F 0 "J9" H 2500 7017 50  0000 C CNN
F 1 "E1/E2 Lite" H 2500 6926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x07_P2.54mm_Vertical" H 2450 6500 50  0001 C CNN
F 3 "~" H 2450 6500 50  0001 C CNN
	1    2450 6500
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR037
U 1 1 5E84E68F
P 3050 5800
F 0 "#PWR037" H 3050 5650 50  0001 C CNN
F 1 "VCC" H 3067 5973 50  0000 C CNN
F 2 "" H 3050 5800 50  0001 C CNN
F 3 "" H 3050 5800 50  0001 C CNN
	1    3050 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 6500 3050 6500
Wire Wire Line
	3050 6500 3050 5800
$Comp
L power:GND #PWR038
U 1 1 5E84F163
P 3300 7250
F 0 "#PWR038" H 3300 7000 50  0001 C CNN
F 1 "GND" H 3305 7077 50  0000 C CNN
F 2 "" H 3300 7250 50  0001 C CNN
F 3 "" H 3300 7250 50  0001 C CNN
	1    3300 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 6200 3300 6200
Wire Wire Line
	3300 6200 3300 6700
Wire Wire Line
	2750 6700 3300 6700
Connection ~ 3300 6700
Wire Wire Line
	3300 6700 3300 6800
Wire Wire Line
	2750 6800 3300 6800
Text GLabel 4200 6300 0    50   Input ~ 0
~RES
Wire Wire Line
	4450 6300 4200 6300
Text GLabel 1100 6800 0    50   Input ~ 0
~RES
Wire Wire Line
	2250 6800 1100 6800
Text GLabel 3450 6300 2    50   Input ~ 0
EMLE
Text GLabel 1100 6500 0    50   Input ~ 0
MD_FINED
Wire Wire Line
	2250 6500 1100 6500
Text GLabel 3450 6600 2    50   Input ~ 0
UB
Wire Wire Line
	3450 6600 2750 6600
Text GLabel 1100 6200 0    50   Input ~ 0
TCK_FINEC
Text GLabel 1100 6300 0    50   Input ~ 0
TRSTn
Text GLabel 1100 6400 0    50   Input ~ 0
TDO
Text GLabel 1100 6600 0    50   Input ~ 0
TMS
Text GLabel 1100 6700 0    50   Input ~ 0
TDI
Wire Wire Line
	2250 6200 1200 6200
Wire Wire Line
	2250 6400 1450 6400
Wire Wire Line
	2250 6600 1700 6600
Wire Wire Line
	2250 6700 1950 6700
Text GLabel 4200 6450 0    50   Input ~ 0
EMLE
Text GLabel 4200 6600 0    50   Input ~ 0
MD_FINED
Wire Wire Line
	4450 6600 4200 6600
$Comp
L akizuki:R R8
U 1 1 5E864D5C
P 4350 6950
F 0 "R8" V 4304 7020 50  0000 L CNN
F 1 "4.7K" V 4395 7020 50  0000 L CNN
F 2 "" H 4350 6880 50  0000 C CNN
F 3 "" V 4350 6950 50  0000 C CNN
	1    4350 6950
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R3
U 1 1 5E86FD86
P 1200 5850
F 0 "R3" V 1154 5920 50  0000 L CNN
F 1 "4.7K" V 1245 5920 50  0000 L CNN
F 2 "" H 1200 5780 50  0000 C CNN
F 3 "" V 1200 5850 50  0000 C CNN
	1    1200 5850
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R4
U 1 1 5E870AFE
P 1450 5850
F 0 "R4" V 1404 5920 50  0000 L CNN
F 1 "4.7K" V 1495 5920 50  0000 L CNN
F 2 "" H 1450 5780 50  0000 C CNN
F 3 "" V 1450 5850 50  0000 C CNN
	1    1450 5850
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R6
U 1 1 5E870BBD
P 1700 5850
F 0 "R6" V 1654 5920 50  0000 L CNN
F 1 "4.7K" V 1745 5920 50  0000 L CNN
F 2 "" H 1700 5780 50  0000 C CNN
F 3 "" V 1700 5850 50  0000 C CNN
	1    1700 5850
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R7
U 1 1 5E871237
P 1950 5850
F 0 "R7" V 1904 5920 50  0000 L CNN
F 1 "4.7K" V 1995 5920 50  0000 L CNN
F 2 "" H 1950 5780 50  0000 C CNN
F 3 "" V 1950 5850 50  0000 C CNN
	1    1950 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 6000 1200 6200
Connection ~ 1200 6200
Wire Wire Line
	1200 6200 1100 6200
Wire Wire Line
	1450 6000 1450 6400
Connection ~ 1450 6400
Wire Wire Line
	1450 6400 1100 6400
Wire Wire Line
	1700 6000 1700 6600
Connection ~ 1700 6600
Wire Wire Line
	1700 6600 1100 6600
Wire Wire Line
	1950 6000 1950 6700
Connection ~ 1950 6700
Wire Wire Line
	1950 6700 1100 6700
Wire Wire Line
	1200 5700 1200 5600
Wire Wire Line
	1200 5600 1450 5600
Wire Wire Line
	1450 5600 1450 5700
Wire Wire Line
	1450 5600 1700 5600
Wire Wire Line
	1700 5600 1700 5700
Connection ~ 1450 5600
Wire Wire Line
	1700 5600 1950 5600
Wire Wire Line
	1950 5600 1950 5700
Connection ~ 1700 5600
$Comp
L akizuki:R R5
U 1 1 5E878D02
P 1600 7050
F 0 "R5" V 1554 7120 50  0000 L CNN
F 1 "4.7K" V 1645 7120 50  0000 L CNN
F 2 "" H 1600 6980 50  0000 C CNN
F 3 "" V 1600 7050 50  0000 C CNN
	1    1600 7050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR036
U 1 1 5E87D0C4
P 1600 7250
F 0 "#PWR036" H 1600 7000 50  0001 C CNN
F 1 "GND" H 1605 7077 50  0000 C CNN
F 2 "" H 1600 7250 50  0001 C CNN
F 3 "" H 1600 7250 50  0001 C CNN
	1    1600 7250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR039
U 1 1 5E88109C
P 4350 7250
F 0 "#PWR039" H 4350 7000 50  0001 C CNN
F 1 "GND" H 4355 7077 50  0000 C CNN
F 2 "" H 4350 7250 50  0001 C CNN
F 3 "" H 4350 7250 50  0001 C CNN
	1    4350 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 6300 3450 6300
Text GLabel 6750 3900 2    50   Input ~ 0
TRSTn
Text GLabel 6750 3800 2    50   Input ~ 0
TMS
Text GLabel 6750 3700 2    50   Input ~ 0
TDI
Text GLabel 6750 3500 2    50   Input ~ 0
TDO
Text GLabel 6750 3600 2    50   Input ~ 0
TCK_FINEC
Wire Wire Line
	6750 3500 6500 3500
Wire Wire Line
	6750 3700 6500 3700
$Comp
L akizuki:R R9
U 1 1 5E843C29
P 7000 5750
F 0 "R9" V 6954 5820 50  0000 L CNN
F 1 "10K" V 7045 5820 50  0000 L CNN
F 2 "" H 7000 5680 50  0000 C CNN
F 3 "" V 7000 5750 50  0000 C CNN
	1    7000 5750
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 5600 7000 5500
Wire Wire Line
	7000 5900 7000 6000
Wire Wire Line
	7000 6000 7250 6000
Text GLabel 6750 6000 0    50   Input ~ 0
~RES
$Comp
L power:VCC #PWR041
U 1 1 5E848D4A
P 7000 5500
F 0 "#PWR041" H 7000 5350 50  0001 C CNN
F 1 "VCC" H 7017 5673 50  0000 C CNN
F 2 "" H 7000 5500 50  0001 C CNN
F 3 "" H 7000 5500 50  0001 C CNN
	1    7000 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 6000 6750 6000
Connection ~ 7000 6000
Wire Wire Line
	4200 6450 4350 6450
Wire Wire Line
	4350 6800 4350 6450
Connection ~ 4350 6450
Wire Wire Line
	4350 6450 4450 6450
Wire Wire Line
	4350 7250 4350 7100
Wire Wire Line
	3300 7250 3300 6800
Connection ~ 3300 6800
Wire Wire Line
	1100 6300 1600 6300
Wire Wire Line
	1600 6900 1600 6300
Connection ~ 1600 6300
Wire Wire Line
	1600 6300 2250 6300
Wire Wire Line
	1600 7250 1600 7200
Text GLabel 8400 6000 0    50   Input ~ 0
MD_FINED
$Comp
L akizuki:R R10
U 1 1 5E85F9B3
P 8600 5750
F 0 "R10" V 8554 5820 50  0000 L CNN
F 1 "10K" V 8645 5820 50  0000 L CNN
F 2 "" H 8600 5680 50  0000 C CNN
F 3 "" V 8600 5750 50  0000 C CNN
	1    8600 5750
	0    1    1    0   
$EndComp
Wire Wire Line
	8400 6000 8600 6000
Wire Wire Line
	8600 6000 8600 5900
Wire Wire Line
	8600 5600 8600 5500
$Comp
L power:VCC #PWR043
U 1 1 5E86269E
P 8600 5500
F 0 "#PWR043" H 8600 5350 50  0001 C CNN
F 1 "VCC" H 8617 5673 50  0000 C CNN
F 2 "" H 8600 5500 50  0001 C CNN
F 3 "" H 8600 5500 50  0001 C CNN
	1    8600 5500
	1    0    0    -1  
$EndComp
Text GLabel 2000 1200 0    50   Input ~ 0
UB
Wire Wire Line
	6500 4600 6750 4600
Wire Wire Line
	6500 4700 6750 4700
Text HLabel 6750 4600 2    50   BiDi ~ 0
CTX0
Text HLabel 6750 4700 2    50   BiDi ~ 0
CRX0
Text HLabel 6750 4300 2    50   BiDi ~ 0
USB_VBUSEN
Text HLabel 6750 4400 2    50   BiDi ~ 0
USB0_OVRCURA
Wire Wire Line
	6750 4200 6500 4200
Wire Wire Line
	6750 4300 6500 4300
Wire Wire Line
	6500 3200 6750 3200
Wire Wire Line
	6500 3300 6750 3300
Wire Wire Line
	6500 3400 6750 3400
Text HLabel 6750 3200 2    50   BiDi ~ 0
RSPCKA
Text HLabel 6750 3300 2    50   BiDi ~ 0
MISOA
Text HLabel 6750 3400 2    50   BiDi ~ 0
MOSIA
Text HLabel 7100 3800 2    50   BiDi ~ 0
SSLA0
Text HLabel 7100 3900 2    50   BiDi ~ 0
SSLA1
Wire Wire Line
	6500 3800 7100 3800
Wire Wire Line
	6500 3900 7100 3900
Wire Wire Line
	3500 2600 3700 2600
Wire Wire Line
	3500 2700 3700 2700
Text HLabel 3700 2600 2    50   BiDi ~ 0
P64
Text HLabel 3700 2700 2    50   BiDi ~ 0
P65
Wire Wire Line
	3500 2500 3700 2500
Wire Wire Line
	3500 2400 3700 2400
Wire Wire Line
	3500 2300 3700 2300
Wire Wire Line
	3500 2200 3700 2200
Text HLabel 3700 2200 2    50   BiDi ~ 0
P60
Text HLabel 3700 2300 2    50   BiDi ~ 0
P61
Text HLabel 3700 2400 2    50   BiDi ~ 0
P62
Text HLabel 3700 2500 2    50   BiDi ~ 0
P63
Wire Wire Line
	1200 5600 1200 5400
Connection ~ 1200 5600
$Comp
L power:VCC #PWR035
U 1 1 5E88F1D4
P 1200 5400
F 0 "#PWR035" H 1200 5250 50  0001 C CNN
F 1 "VCC" H 1217 5573 50  0000 C CNN
F 2 "" H 1200 5400 50  0001 C CNN
F 3 "" H 1200 5400 50  0001 C CNN
	1    1200 5400
	1    0    0    -1  
$EndComp
$Comp
L akizuki:2P-SW SW1
U 1 1 5E7FD187
P 7500 6000
F 0 "SW1" H 7500 6349 60  0000 C CNN
F 1 "~RESET" H 7500 6237 60  0000 C CNN
F 2 "" H 7505 6000 60  0000 C CNN
F 3 "" H 7505 6000 60  0000 C CNN
	1    7500 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 5E7FEC8C
P 7850 6100
F 0 "#PWR042" H 7850 5850 50  0001 C CNN
F 1 "GND" H 7855 5927 50  0000 C CNN
F 2 "" H 7850 6100 50  0001 C CNN
F 3 "" H 7850 6100 50  0001 C CNN
	1    7850 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 6100 7850 6000
Wire Wire Line
	7850 6000 7750 6000
$Comp
L akizuki:3P-SW SW2
U 1 1 5E805A79
P 9300 6000
F 0 "SW2" H 9428 6058 60  0000 L CNN
F 1 "BOOT" H 9428 5952 60  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9285 6000 60  0001 C CNN
F 3 "" H 9285 6000 60  0000 C CNN
	1    9300 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 6000 8600 6000
Connection ~ 8600 6000
Wire Wire Line
	9100 6150 9000 6150
$Comp
L power:GND #PWR044
U 1 1 5E80B6C3
P 9000 6250
F 0 "#PWR044" H 9000 6000 50  0001 C CNN
F 1 "GND" H 9005 6077 50  0000 C CNN
F 2 "" H 9000 6250 50  0001 C CNN
F 3 "" H 9000 6250 50  0001 C CNN
	1    9000 6250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J11
U 1 1 5E80C4BE
P 10600 6100
F 0 "J11" H 10680 6142 50  0000 L CNN
F 1 "Serial/USB" H 10680 6051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 10600 6100 50  0001 C CNN
F 3 "~" H 10600 6100 50  0001 C CNN
	1    10600 6100
	1    0    0    -1  
$EndComp
Text GLabel 9900 6100 0    50   Input ~ 0
UB
$Comp
L akizuki:R R11
U 1 1 5E818AB4
P 10150 6100
F 0 "R11" H 10150 6307 50  0000 C CNN
F 1 "10K" H 10150 6216 50  0000 C CNN
F 2 "" H 10150 6030 50  0000 C CNN
F 3 "" V 10150 6100 50  0000 C CNN
	1    10150 6100
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR046
U 1 1 5E81E963
P 10300 5800
F 0 "#PWR046" H 10300 5650 50  0001 C CNN
F 1 "VCC" H 10317 5973 50  0000 C CNN
F 2 "" H 10300 5800 50  0001 C CNN
F 3 "" H 10300 5800 50  0001 C CNN
	1    10300 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 6200 10300 6200
Wire Wire Line
	10300 6200 10300 6300
$Comp
L power:GND #PWR047
U 1 1 5E82157D
P 10300 6300
F 0 "#PWR047" H 10300 6050 50  0001 C CNN
F 1 "GND" H 10305 6127 50  0000 C CNN
F 2 "" H 10300 6300 50  0001 C CNN
F 3 "" H 10300 6300 50  0001 C CNN
	1    10300 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 6000 10300 6000
Wire Wire Line
	10300 5800 10300 6000
Wire Wire Line
	10400 6100 10300 6100
Wire Wire Line
	10000 6100 9900 6100
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J10
U 1 1 5E84E0A0
P 10200 5100
F 0 "J10" H 10250 5417 50  0000 C CNN
F 1 "BOOT/Serial(SCI1)" H 10250 5326 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 10200 5100 50  0001 C CNN
F 3 "~" H 10200 5100 50  0001 C CNN
	1    10200 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 5100 9800 5100
Wire Wire Line
	9800 5100 9800 5300
$Comp
L power:GND #PWR045
U 1 1 5E85665E
P 9800 5300
F 0 "#PWR045" H 9800 5050 50  0001 C CNN
F 1 "GND" H 9805 5127 50  0000 C CNN
F 2 "" H 9800 5300 50  0001 C CNN
F 3 "" H 9800 5300 50  0001 C CNN
	1    9800 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 5100 10700 5100
Wire Wire Line
	10700 5100 10700 4900
$Comp
L power:VCC #PWR048
U 1 1 5E8594E4
P 10700 4900
F 0 "#PWR048" H 10700 4750 50  0001 C CNN
F 1 "VCC" H 10717 5073 50  0000 C CNN
F 2 "" H 10700 4900 50  0001 C CNN
F 3 "" H 10700 4900 50  0001 C CNN
	1    10700 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 5000 9700 5000
Text GLabel 9700 5000 0    50   Input ~ 0
TDI
Text GLabel 10800 5000 2    50   Input ~ 0
TDO
Wire Wire Line
	10800 5000 10500 5000
Text HLabel 8000 2150 0    50   BiDi ~ 0
PH0
Text HLabel 8000 2250 0    50   BiDi ~ 0
PH1
Text HLabel 8000 2350 0    50   BiDi ~ 0
PH2
Text HLabel 8000 2450 0    50   BiDi ~ 0
PH3
Text HLabel 8000 2550 0    50   BiDi ~ 0
PH4
Text HLabel 8000 2650 0    50   BiDi ~ 0
PH5
Text HLabel 8000 2750 0    50   BiDi ~ 0
PH6
Text HLabel 8000 2850 0    50   BiDi ~ 0
PH7
Wire Wire Line
	8000 2150 8300 2150
Wire Wire Line
	8000 2250 8300 2250
Wire Wire Line
	8000 2350 8300 2350
Wire Wire Line
	8000 2450 8300 2450
Wire Wire Line
	8000 2550 8300 2550
Wire Wire Line
	8000 2650 8300 2650
Wire Wire Line
	8300 2750 8000 2750
Wire Wire Line
	8300 2850 8000 2850
Text HLabel 2050 2200 0    50   BiDi ~ 0
P10
Text HLabel 2050 2300 0    50   BiDi ~ 0
P11
Text HLabel 2050 2400 0    50   BiDi ~ 0
P12
Text HLabel 2050 2500 0    50   BiDi ~ 0
P13
Text HLabel 2050 2600 0    50   BiDi ~ 0
P14
Text HLabel 2050 2700 0    50   BiDi ~ 0
P15
Text HLabel 2050 2800 0    50   BiDi ~ 0
P16
Text HLabel 2050 2900 0    50   BiDi ~ 0
P17
Text HLabel 2050 3200 0    50   BiDi ~ 0
P20
Text HLabel 2050 3300 0    50   BiDi ~ 0
P21
Text HLabel 2050 3400 0    50   BiDi ~ 0
P22
Text HLabel 2050 3500 0    50   BiDi ~ 0
P23
Text HLabel 2050 3600 0    50   BiDi ~ 0
P24
Text HLabel 2050 3700 0    50   BiDi ~ 0
P25
Text HLabel 2050 3800 0    50   BiDi ~ 0
P26
Text HLabel 2050 3900 0    50   BiDi ~ 0
P27
Text HLabel 2050 4200 0    50   BiDi ~ 0
P30
Text HLabel 2050 4300 0    50   BiDi ~ 0
P31
Text HLabel 2050 4400 0    50   BiDi ~ 0
P32
Text HLabel 2050 4500 0    50   BiDi ~ 0
P33
Text HLabel 2050 4600 0    50   BiDi ~ 0
P34
Text HLabel 2050 4700 0    50   BiDi ~ 0
P35
Wire Wire Line
	2300 2200 2050 2200
Wire Wire Line
	2300 2300 2050 2300
Wire Wire Line
	2050 2400 2300 2400
Wire Wire Line
	2300 2500 2050 2500
Wire Wire Line
	2050 2600 2300 2600
Wire Wire Line
	2300 2700 2050 2700
Wire Wire Line
	2050 2800 2300 2800
Wire Wire Line
	2300 2900 2050 2900
Wire Wire Line
	2050 3200 2300 3200
Wire Wire Line
	2300 3300 2050 3300
Wire Wire Line
	2050 3400 2300 3400
Wire Wire Line
	2300 3500 2050 3500
Wire Wire Line
	2050 3600 2300 3600
Wire Wire Line
	2300 3700 2050 3700
Wire Wire Line
	2050 3800 2300 3800
Wire Wire Line
	2300 3900 2050 3900
Wire Wire Line
	2300 4200 2050 4200
Wire Wire Line
	2050 4300 2300 4300
Wire Wire Line
	2300 4400 2050 4400
Wire Wire Line
	2050 4500 2300 4500
Wire Wire Line
	2300 4600 2050 4600
Wire Wire Line
	2050 4700 2300 4700
Text HLabel 8000 1200 0    50   BiDi ~ 0
PG0
Text HLabel 8000 1300 0    50   BiDi ~ 0
PG1
Text HLabel 8000 1400 0    50   BiDi ~ 0
PG2
Text HLabel 5000 1200 0    50   BiDi ~ 0
P80
Text HLabel 5000 1300 0    50   BiDi ~ 0
P81
Text HLabel 5000 1400 0    50   BiDi ~ 0
P82
Text HLabel 5000 2150 0    50   BiDi ~ 0
P90
Text HLabel 5000 2250 0    50   BiDi ~ 0
P91
Text HLabel 5000 2350 0    50   BiDi ~ 0
P92
Text HLabel 5000 2450 0    50   BiDi ~ 0
P93
Text HLabel 5000 2550 0    50   BiDi ~ 0
P94
Text HLabel 5000 2650 0    50   BiDi ~ 0
P95
Text HLabel 5000 2750 0    50   BiDi ~ 0
P96
Text HLabel 5000 3200 0    50   BiDi ~ 0
PA0
Text HLabel 5000 3300 0    50   BiDi ~ 0
PA1
Text HLabel 5000 3400 0    50   BiDi ~ 0
PA2
Text HLabel 5000 3500 0    50   BiDi ~ 0
PA3
Text HLabel 5000 3600 0    50   BiDi ~ 0
PA4
Text HLabel 5000 3700 0    50   BiDi ~ 0
PA5
Text HLabel 5000 3800 0    50   BiDi ~ 0
PA6
Text HLabel 5000 3900 0    50   BiDi ~ 0
PA7
Text HLabel 5000 4200 0    50   BiDi ~ 0
PB0
Text HLabel 5000 4300 0    50   BiDi ~ 0
PB1
Text HLabel 5000 4400 0    50   BiDi ~ 0
PB2
Text HLabel 5000 4500 0    50   BiDi ~ 0
PB3
Text HLabel 5000 4600 0    50   BiDi ~ 0
PB4
Text HLabel 5000 4700 0    50   BiDi ~ 0
PB5
Text HLabel 5000 4800 0    50   BiDi ~ 0
PB6
Text HLabel 5000 4900 0    50   BiDi ~ 0
PB7
Wire Wire Line
	5000 1200 5300 1200
Wire Wire Line
	5300 1300 5000 1300
Wire Wire Line
	5000 1400 5300 1400
Wire Wire Line
	5300 2150 5000 2150
Wire Wire Line
	5000 2250 5300 2250
Wire Wire Line
	5300 2350 5000 2350
Wire Wire Line
	5000 2450 5300 2450
Wire Wire Line
	5300 2550 5000 2550
Wire Wire Line
	5000 2650 5300 2650
Wire Wire Line
	5300 2750 5000 2750
Wire Wire Line
	5000 3200 5300 3200
Wire Wire Line
	5300 3300 5000 3300
Wire Wire Line
	5000 3400 5300 3400
Wire Wire Line
	5300 3500 5000 3500
Wire Wire Line
	5000 3600 5300 3600
Wire Wire Line
	5300 3700 5000 3700
Wire Wire Line
	5000 3800 5300 3800
Wire Wire Line
	5300 3900 5000 3900
Wire Wire Line
	5000 4200 5300 4200
Wire Wire Line
	5300 4300 5000 4300
Wire Wire Line
	5000 4400 5300 4400
Wire Wire Line
	5300 4500 5000 4500
Wire Wire Line
	5000 4600 5300 4600
Wire Wire Line
	5300 4700 5000 4700
Wire Wire Line
	5000 4800 5300 4800
Wire Wire Line
	5300 4900 5000 4900
Wire Wire Line
	8300 1200 8000 1200
Wire Wire Line
	8300 1300 8000 1300
Wire Wire Line
	8300 1400 8000 1400
Wire Wire Line
	9000 6250 9000 6150
$Comp
L Device:LED_Small_ALT D1
U 1 1 5EA0302B
P 1450 1300
F 0 "D1" H 1450 1095 50  0000 C CNN
F 1 "Indicator" H 1450 1186 50  0000 C CNN
F 2 "" V 1450 1300 50  0001 C CNN
F 3 "~" V 1450 1300 50  0001 C CNN
	1    1450 1300
	-1   0    0    1   
$EndComp
$Comp
L akizuki:R R2
U 1 1 5EA03D93
P 1050 1300
F 0 "R2" H 1050 1507 50  0000 C CNN
F 1 "1K" H 1050 1416 50  0000 C CNN
F 2 "" H 1050 1230 50  0000 C CNN
F 3 "" V 1050 1300 50  0000 C CNN
	1    1050 1300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR034
U 1 1 5EA047FA
P 800 1200
F 0 "#PWR034" H 800 1050 50  0001 C CNN
F 1 "VCC" H 817 1373 50  0000 C CNN
F 2 "" H 800 1200 50  0001 C CNN
F 3 "" H 800 1200 50  0001 C CNN
	1    800  1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  1300 800  1300
Wire Wire Line
	800  1300 800  1200
Wire Wire Line
	1350 1300 1200 1300
Wire Wire Line
	1550 1300 2300 1300
Text HLabel 3700 1200 2    50   BiDi ~ 0
P70
Text HLabel 3700 1300 2    50   BiDi ~ 0
P71
Text HLabel 3700 1400 2    50   BiDi ~ 0
P72
Text HLabel 3700 1500 2    50   BiDi ~ 0
P73
Text HLabel 3700 1600 2    50   BiDi ~ 0
P74
Text HLabel 3700 1700 2    50   BiDi ~ 0
P75
Text HLabel 3700 1800 2    50   BiDi ~ 0
P76
Wire Wire Line
	3500 1200 3700 1200
Wire Wire Line
	3700 1300 3500 1300
Wire Wire Line
	3500 1400 3700 1400
Wire Wire Line
	3700 1500 3500 1500
Wire Wire Line
	3500 1600 3700 1600
Wire Wire Line
	3700 1700 3500 1700
Wire Wire Line
	3500 1800 3700 1800
Text HLabel 3700 3200 2    50   BiDi ~ 0
P50
Text HLabel 3700 3300 2    50   BiDi ~ 0
P51
Text HLabel 3700 3400 2    50   BiDi ~ 0
P52
Text HLabel 3700 3500 2    50   BiDi ~ 0
P53
Text HLabel 3700 3600 2    50   BiDi ~ 0
P54
Text HLabel 3700 3700 2    50   BiDi ~ 0
P55
Text HLabel 3700 4200 2    50   BiDi ~ 0
P40
Text HLabel 3700 4300 2    50   BiDi ~ 0
P41
Text HLabel 3700 4400 2    50   BiDi ~ 0
P42
Text HLabel 3700 4500 2    50   BiDi ~ 0
P43
Text HLabel 3700 4600 2    50   BiDi ~ 0
P44
Text HLabel 3700 4700 2    50   BiDi ~ 0
P45
Text HLabel 3700 4800 2    50   BiDi ~ 0
P46
Text HLabel 3700 4900 2    50   BiDi ~ 0
P47
Wire Wire Line
	3700 3200 3500 3200
Wire Wire Line
	3500 3300 3700 3300
Wire Wire Line
	3700 3400 3500 3400
Wire Wire Line
	3500 3500 3700 3500
Wire Wire Line
	3700 3600 3500 3600
Wire Wire Line
	3500 3700 3700 3700
Wire Wire Line
	3700 4200 3500 4200
Wire Wire Line
	3500 4300 3700 4300
Wire Wire Line
	3700 4400 3500 4400
Wire Wire Line
	3500 4500 3700 4500
Wire Wire Line
	3700 4600 3500 4600
Wire Wire Line
	3500 4700 3700 4700
Wire Wire Line
	3700 4800 3500 4800
Wire Wire Line
	3500 4900 3700 4900
Text HLabel 9800 2150 2    50   BiDi ~ 0
PK0
Text HLabel 9800 2250 2    50   BiDi ~ 0
PK1
Text HLabel 9800 2350 2    50   BiDi ~ 0
PK2
Wire Wire Line
	9800 2150 9500 2150
Wire Wire Line
	9800 2250 9500 2250
Wire Wire Line
	9500 2350 9800 2350
Text HLabel 6750 1200 2    50   BiDi ~ 0
PF0
Text HLabel 6750 1300 2    50   BiDi ~ 0
PF1
Text HLabel 6750 1400 2    50   BiDi ~ 0
PF2
Text HLabel 6750 1500 2    50   BiDi ~ 0
PF3
Text HLabel 6750 2150 2    50   BiDi ~ 0
PE0
Text HLabel 6750 2250 2    50   BiDi ~ 0
PE1
Text HLabel 6750 2350 2    50   BiDi ~ 0
PE2
Text HLabel 6750 2450 2    50   BiDi ~ 0
PE3
Text HLabel 6750 2550 2    50   BiDi ~ 0
PE4
Text HLabel 6750 2650 2    50   BiDi ~ 0
PE5
Text HLabel 6750 2750 2    50   BiDi ~ 0
PE6
Wire Wire Line
	6500 1200 6750 1200
Wire Wire Line
	6750 1300 6500 1300
Wire Wire Line
	6500 1400 6750 1400
Wire Wire Line
	6750 1500 6500 1500
Wire Wire Line
	6500 2150 6750 2150
Wire Wire Line
	6750 2250 6500 2250
Wire Wire Line
	6500 2350 6750 2350
Wire Wire Line
	6750 2450 6500 2450
Wire Wire Line
	6500 2550 6750 2550
Wire Wire Line
	6750 2650 6500 2650
Wire Wire Line
	6500 2750 6750 2750
Text HLabel 6750 4200 2    50   BiDi ~ 0
USB_VBUS
Wire Wire Line
	6750 4400 6500 4400
Text HLabel 6750 4500 2    50   BiDi ~ 0
PC3
Text HLabel 6750 4800 2    50   BiDi ~ 0
PC6
Wire Wire Line
	6750 4500 6500 4500
Wire Wire Line
	6500 4800 6750 4800
Wire Wire Line
	2300 1200 2000 1200
Text HLabel 7300 3600 2    50   BiDi ~ 0
SDC_ENA
Wire Wire Line
	6500 3600 7300 3600
$EndSCHEMATC
