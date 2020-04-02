EESchema Schematic File Version 4
LIBS:MaxRX72T-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
U 5 1 5E88F655
P 3300 2250
F 0 "U1" H 3728 2271 50  0000 L CNN
F 1 "RX72T_144" H 3728 2180 50  0000 L CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 3750 3300 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 3750 3300 50  0001 C CNN
	5    3300 2250
	1    0    0    -1  
$EndComp
$Comp
L Power_Management:MIC2026-1BM U?
U 1 1 5E80AED6
P 5700 2400
AR Path="/5E88AC7A/5E80AED6" Ref="U?"  Part="1" 
AR Path="/5E88F588/5E80AED6" Ref="U3"  Part="1" 
F 0 "U3" H 5700 2967 50  0000 C CNN
F 1 "MIC2026-1BM" H 5700 2876 50  0000 C CNN
F 2 "Package_SO:HSOP-8-1EP_3.9x4.9mm_P1.27mm_EP2.41x3.1mm" H 5700 2400 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/mic2026.pdf" H 5700 2400 50  0001 C CNN
	1    5700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2900 5700 3100
$Comp
L power:GND #PWR053
U 1 1 5E819170
P 5700 3100
F 0 "#PWR053" H 5700 2850 50  0001 C CNN
F 1 "GND" H 5705 2927 50  0000 C CNN
F 2 "" H 5700 3100 50  0001 C CNN
F 3 "" H 5700 3100 50  0001 C CNN
	1    5700 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2100 6250 2100
Wire Wire Line
	6250 2100 6250 1700
$Comp
L power:VCC #PWR054
U 1 1 5E8197E3
P 6250 1700
F 0 "#PWR054" H 6250 1550 50  0001 C CNN
F 1 "VCC" H 6267 1873 50  0000 C CNN
F 2 "" H 6250 1700 50  0001 C CNN
F 3 "" H 6250 1700 50  0001 C CNN
	1    6250 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_A J12
U 1 1 5E819AAE
P 1500 2200
F 0 "J12" H 1557 2667 50  0000 C CNN
F 1 "USB_A" H 1557 2576 50  0000 C CNN
F 2 "Connector_USB:USB_A_Stewart_SS-52100-001_Horizontal" H 1650 2150 50  0001 C CNN
F 3 " ~" H 1650 2150 50  0001 C CNN
	1    1500 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2600 1500 2800
$Comp
L power:GND #PWR050
U 1 1 5E81EBC9
P 1500 2800
F 0 "#PWR050" H 1500 2550 50  0001 C CNN
F 1 "GND" H 1505 2627 50  0000 C CNN
F 2 "" H 1500 2800 50  0001 C CNN
F 3 "" H 1500 2800 50  0001 C CNN
	1    1500 2800
	1    0    0    -1  
$EndComp
$Comp
L akizuki:R R12
U 1 1 5E81F0E3
P 1150 2750
F 0 "R12" H 1150 2957 50  0000 C CNN
F 1 "0" H 1150 2866 50  0000 C CNN
F 2 "" H 1150 2680 50  0000 C CNN
F 3 "" V 1150 2750 50  0000 C CNN
	1    1150 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2750 1400 2750
Wire Wire Line
	1400 2750 1400 2600
Wire Wire Line
	1000 2750 900  2750
Wire Wire Line
	900  2750 900  3000
$Comp
L power:GND #PWR049
U 1 1 5E82D652
P 900 3000
F 0 "#PWR049" H 900 2750 50  0001 C CNN
F 1 "GND" H 905 2827 50  0000 C CNN
F 2 "" H 900 3000 50  0001 C CNN
F 3 "" H 900 3000 50  0001 C CNN
	1    900  3000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J13
U 1 1 5E82DA09
P 2450 1300
F 0 "J13" H 2530 1342 50  0000 L CNN
F 1 "USB Host/Client" H 2530 1251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2450 1300 50  0001 C CNN
F 3 "~" H 2450 1300 50  0001 C CNN
	1    2450 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2200 2700 2200
Wire Wire Line
	2700 2300 1800 2300
Text HLabel 2100 4850 0    50   BiDi ~ 0
CTX0
Text HLabel 2100 4950 0    50   BiDi ~ 0
CRX0
$Comp
L Interface_CAN_LIN:MCP2562-E-P U2
U 1 1 5E82BA2F
P 3300 5050
F 0 "U2" H 3650 5400 50  0000 C CNN
F 1 "MCP2562-E-P" H 2950 4700 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 3300 4550 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/25167A.pdf" H 3300 5050 50  0001 C CNN
	1    3300 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4850 2100 4850
Wire Wire Line
	2100 4950 2800 4950
Wire Wire Line
	3300 5450 3300 5550
$Comp
L power:GND #PWR052
U 1 1 5E82D900
P 3300 5550
F 0 "#PWR052" H 3300 5300 50  0001 C CNN
F 1 "GND" H 3305 5377 50  0000 C CNN
F 2 "" H 3300 5550 50  0001 C CNN
F 3 "" H 3300 5550 50  0001 C CNN
	1    3300 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 5150 2650 5150
Wire Wire Line
	2650 5150 2650 4500
$Comp
L power:VCC #PWR051
U 1 1 5E82E88A
P 2650 4500
F 0 "#PWR051" H 2650 4350 50  0001 C CNN
F 1 "VCC" H 2667 4673 50  0000 C CNN
F 2 "" H 2650 4500 50  0001 C CNN
F 3 "" H 2650 4500 50  0001 C CNN
	1    2650 4500
	1    0    0    -1  
$EndComp
Text HLabel 5050 2100 0    50   BiDi ~ 0
USB_VBUSEN
Text HLabel 4450 1850 0    50   BiDi ~ 0
USB_VBUS
Text HLabel 5050 2200 0    50   BiDi ~ 0
USB0_OVRCURA
Text HLabel 4600 3900 0    50   BiDi ~ 0
RSPCKA
Text HLabel 4600 4000 0    50   BiDi ~ 0
MISOA
Text HLabel 4600 4100 0    50   BiDi ~ 0
MOSIA
Text HLabel 4600 4200 0    50   BiDi ~ 0
SSLA0
Text HLabel 4600 4300 0    50   BiDi ~ 0
SSLA1
Text HLabel 4600 4400 0    50   BiDi ~ 0
SDC_ENA
Wire Wire Line
	5300 2100 5050 2100
Wire Wire Line
	5300 2200 5050 2200
Wire Wire Line
	1800 2000 1950 2000
Wire Wire Line
	1950 2000 1950 1300
Wire Wire Line
	1950 1300 2250 1300
Wire Wire Line
	6100 2300 6500 2300
Wire Wire Line
	6500 2300 6500 1000
Wire Wire Line
	6500 1000 1950 1000
Wire Wire Line
	1950 1000 1950 1200
Wire Wire Line
	1950 1200 2250 1200
Wire Wire Line
	2700 2600 2500 2600
Wire Wire Line
	2500 2600 2500 2850
$Comp
L power:GND #PWR?
U 1 1 5E8D8342
P 2500 2850
F 0 "#PWR?" H 2500 2600 50  0001 C CNN
F 1 "GND" H 2505 2677 50  0000 C CNN
F 2 "" H 2500 2850 50  0001 C CNN
F 3 "" H 2500 2850 50  0001 C CNN
	1    2500 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1900 2500 1900
Wire Wire Line
	2500 1900 2500 1700
$Comp
L power:VCC #PWR?
U 1 1 5E8D8B64
P 2500 1700
F 0 "#PWR?" H 2500 1550 50  0001 C CNN
F 1 "VCC" H 2517 1873 50  0000 C CNN
F 2 "" H 2500 1700 50  0001 C CNN
F 3 "" H 2500 1700 50  0001 C CNN
	1    2500 1700
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5E8D8E4D
P 2900 3300
F 0 "C?" H 2983 3353 60  0000 L CNN
F 1 "C" H 2983 3247 60  0000 L CNN
F 2 "" V 2900 3300 60  0000 C CNN
F 3 "" V 2900 3300 60  0000 C CNN
	1    2900 3300
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5E8D9F92
P 2950 6150
F 0 "C?" H 3033 6203 60  0000 L CNN
F 1 "C" H 3033 6097 60  0000 L CNN
F 2 "" V 2950 6150 60  0000 C CNN
F 3 "" V 2950 6150 60  0000 C CNN
	1    2950 6150
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5E8DA065
P 6850 2050
F 0 "C?" H 6933 2103 60  0000 L CNN
F 1 "C" H 6933 1997 60  0000 L CNN
F 2 "" V 6850 2050 60  0000 C CNN
F 3 "" V 6850 2050 60  0000 C CNN
	1    6850 2050
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 5E8DA8C9
P 7250 2050
F 0 "C?" H 7333 2103 60  0000 L CNN
F 1 "C" H 7333 1997 60  0000 L CNN
F 2 "" V 7250 2050 60  0000 C CNN
F 3 "" V 7250 2050 60  0000 C CNN
	1    7250 2050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
