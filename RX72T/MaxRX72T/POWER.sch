EESchema Schematic File Version 4
LIBS:MaxRX72T-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
U 6 1 5E88AD27
P 4250 3700
F 0 "U1" H 4878 3771 50  0000 L CNN
F 1 "RX72T_144" H 4878 3680 50  0000 L CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 4700 4750 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 4700 4750 50  0001 C CNN
	6    4250 3700
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C3
U 1 1 5E7E1FBB
P 3250 4050
F 0 "C3" H 3332 4103 60  0000 L CNN
F 1 "0.47uF" H 3332 3997 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3250 4050 60  0001 C CNN
F 3 "" V 3250 4050 60  0000 C CNN
	1    3250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3900 3250 3700
Wire Wire Line
	3250 3700 3450 3700
Wire Wire Line
	3250 4200 3250 4400
$Comp
L power:GND #PWR027
U 1 1 5E7E43E1
P 3250 4400
F 0 "#PWR027" H 3250 4150 50  0001 C CNN
F 1 "GND" H 3255 4227 50  0000 C CNN
F 2 "" H 3250 4400 50  0001 C CNN
F 3 "" H 3250 4400 50  0001 C CNN
	1    3250 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2800 4150 2700
Wire Wire Line
	4150 2700 4050 2700
Wire Wire Line
	4050 2700 4050 2800
Wire Wire Line
	4050 2700 3950 2700
Wire Wire Line
	3950 2700 3950 2800
Connection ~ 4050 2700
Wire Wire Line
	3950 2700 3850 2700
Wire Wire Line
	3850 2700 3850 2800
Connection ~ 3950 2700
Wire Wire Line
	3850 2700 3750 2700
Wire Wire Line
	3750 2700 3750 2800
Connection ~ 3850 2700
Wire Wire Line
	3750 2700 3750 2500
Connection ~ 3750 2700
Wire Wire Line
	3750 4550 3750 4650
Wire Wire Line
	3750 4650 3850 4650
Wire Wire Line
	3850 4650 3850 4550
Wire Wire Line
	3850 4650 3950 4650
Wire Wire Line
	3950 4650 3950 4550
Connection ~ 3850 4650
Wire Wire Line
	3950 4650 4050 4650
Wire Wire Line
	4050 4650 4050 4550
Connection ~ 3950 4650
Wire Wire Line
	4050 4650 4150 4650
Wire Wire Line
	4150 4650 4150 4550
Connection ~ 4050 4650
Wire Wire Line
	3750 4650 3750 4850
Connection ~ 3750 4650
$Comp
L power:GND #PWR029
U 1 1 5E7E6BA5
P 3750 4850
F 0 "#PWR029" H 3750 4600 50  0001 C CNN
F 1 "GND" H 3755 4677 50  0000 C CNN
F 2 "" H 3750 4850 50  0001 C CNN
F 3 "" H 3750 4850 50  0001 C CNN
	1    3750 4850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR028
U 1 1 5E7E6E15
P 3750 2500
F 0 "#PWR028" H 3750 2350 50  0001 C CNN
F 1 "VCC" H 3767 2673 50  0000 C CNN
F 2 "" H 3750 2500 50  0001 C CNN
F 3 "" H 3750 2500 50  0001 C CNN
	1    3750 2500
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C1
U 1 1 5E7E6EC0
P 2700 1450
F 0 "C1" H 2783 1503 60  0000 L CNN
F 1 "0.1uF" H 2783 1397 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2700 1450 60  0001 C CNN
F 3 "" V 2700 1450 60  0001 C CNN
	1    2700 1450
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C2
U 1 1 5E7E85B2
P 3100 1450
F 0 "C2" H 3183 1503 60  0000 L CNN
F 1 "0.1uF" H 3183 1397 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3100 1450 60  0001 C CNN
F 3 "" V 3100 1450 60  0001 C CNN
	1    3100 1450
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C4
U 1 1 5E7E87F7
P 3500 1450
F 0 "C4" H 3583 1503 60  0000 L CNN
F 1 "0.1uF" H 3583 1397 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3500 1450 60  0001 C CNN
F 3 "" V 3500 1450 60  0001 C CNN
	1    3500 1450
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C5
U 1 1 5E7E8A52
P 3900 1450
F 0 "C5" H 3983 1503 60  0000 L CNN
F 1 "0.1uF" H 3983 1397 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3900 1450 60  0001 C CNN
F 3 "" V 3900 1450 60  0001 C CNN
	1    3900 1450
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C6
U 1 1 5E7E8CC3
P 4300 1450
F 0 "C6" H 4383 1503 60  0000 L CNN
F 1 "0.1uF" H 4383 1397 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4300 1450 60  0001 C CNN
F 3 "" V 4300 1450 60  0001 C CNN
	1    4300 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1600 2700 1800
Wire Wire Line
	2700 1800 3100 1800
Wire Wire Line
	3100 1800 3100 1600
Wire Wire Line
	3100 1800 3500 1800
Wire Wire Line
	3500 1800 3500 1600
Connection ~ 3100 1800
Wire Wire Line
	3500 1800 3900 1800
Wire Wire Line
	3900 1800 3900 1600
Connection ~ 3500 1800
Wire Wire Line
	3900 1800 4300 1800
Wire Wire Line
	4300 1800 4300 1600
Connection ~ 3900 1800
Wire Wire Line
	2700 1300 2700 1100
Wire Wire Line
	2700 1100 3100 1100
Wire Wire Line
	3100 1100 3100 1300
Wire Wire Line
	3100 1100 3500 1100
Wire Wire Line
	3500 1100 3500 1300
Connection ~ 3100 1100
Wire Wire Line
	3500 1100 3900 1100
Wire Wire Line
	3900 1100 3900 1300
Connection ~ 3500 1100
Wire Wire Line
	3900 1100 4300 1100
Wire Wire Line
	4300 1100 4300 1300
Connection ~ 3900 1100
Wire Wire Line
	2700 1100 2700 1000
Connection ~ 2700 1100
Wire Wire Line
	2700 1800 2700 1900
Connection ~ 2700 1800
$Comp
L power:VCC #PWR025
U 1 1 5E7EF3AB
P 2700 1000
F 0 "#PWR025" H 2700 850 50  0001 C CNN
F 1 "VCC" H 2717 1173 50  0000 C CNN
F 2 "" H 2700 1000 50  0001 C CNN
F 3 "" H 2700 1000 50  0001 C CNN
	1    2700 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5E7EF46E
P 2700 1900
F 0 "#PWR026" H 2700 1650 50  0001 C CNN
F 1 "GND" H 2705 1727 50  0000 C CNN
F 2 "" H 2700 1900 50  0001 C CNN
F 3 "" H 2700 1900 50  0001 C CNN
	1    2700 1900
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C-POL C7
U 1 1 5E7FB189
P 4800 1450
F 0 "C7" H 4883 1503 60  0000 L CNN
F 1 "33uF" H 4883 1397 60  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4800 1450 60  0001 C CNN
F 3 "" V 4800 1450 60  0000 C CNN
	1    4800 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1100 4800 1100
Wire Wire Line
	4800 1100 4800 1300
Connection ~ 4300 1100
Wire Wire Line
	4300 1800 4800 1800
Wire Wire Line
	4800 1800 4800 1600
Connection ~ 4300 1800
$Comp
L akizuki:C C8
U 1 1 5E870C75
P 5500 2750
F 0 "C8" H 5583 2803 60  0000 L CNN
F 1 "0.1uF" H 5583 2697 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5500 2750 60  0001 C CNN
F 3 "" V 5500 2750 60  0000 C CNN
	1    5500 2750
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C9
U 1 1 5E87112B
P 6000 2750
F 0 "C9" H 6083 2803 60  0000 L CNN
F 1 "0.1uF" H 6083 2697 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6000 2750 60  0001 C CNN
F 3 "" V 6000 2750 60  0000 C CNN
	1    6000 2750
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C10
U 1 1 5E871418
P 6500 2750
F 0 "C10" H 6583 2803 60  0000 L CNN
F 1 "0.1uF" H 6583 2697 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6500 2750 60  0001 C CNN
F 3 "" V 6500 2750 60  0000 C CNN
	1    6500 2750
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C11
U 1 1 5E87171B
P 7000 2750
F 0 "C11" H 7083 2803 60  0000 L CNN
F 1 "0.1uF" H 7083 2697 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7000 2750 60  0001 C CNN
F 3 "" V 7000 2750 60  0000 C CNN
	1    7000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2600 5500 2500
Wire Wire Line
	5500 2500 6000 2500
Wire Wire Line
	6000 2500 6000 2600
Wire Wire Line
	6000 2500 6500 2500
Wire Wire Line
	6500 2500 6500 2600
Connection ~ 6000 2500
Wire Wire Line
	6500 2500 7000 2500
Wire Wire Line
	7000 2500 7000 2600
Connection ~ 6500 2500
Wire Wire Line
	5500 2900 5500 3000
Wire Wire Line
	5500 3000 6000 3000
Wire Wire Line
	6000 3000 6000 2900
Wire Wire Line
	6000 3000 6500 3000
Wire Wire Line
	6500 3000 6500 2900
Connection ~ 6000 3000
Wire Wire Line
	6500 3000 7000 3000
Wire Wire Line
	7000 3000 7000 2900
Connection ~ 6500 3000
Wire Wire Line
	4450 2800 4450 2500
Wire Wire Line
	4450 2500 4550 2500
Connection ~ 5500 2500
Wire Wire Line
	4550 2800 4550 2500
Connection ~ 4550 2500
Wire Wire Line
	4550 2500 4650 2500
Wire Wire Line
	4650 2800 4650 2500
Connection ~ 4650 2500
Wire Wire Line
	4650 2500 4750 2500
Wire Wire Line
	4750 2800 4750 2500
Connection ~ 4750 2500
Wire Wire Line
	4750 2500 5500 2500
Wire Wire Line
	4650 4550 4650 4650
Wire Wire Line
	4650 4650 5500 4650
Wire Wire Line
	5500 4650 5500 3000
Connection ~ 5500 3000
Wire Wire Line
	4550 4550 4550 4650
Wire Wire Line
	4550 4650 4650 4650
Connection ~ 4650 4650
Wire Wire Line
	4450 4550 4450 4650
Wire Wire Line
	4450 4650 4550 4650
Connection ~ 4550 4650
$Comp
L power:GNDA #PWR032
U 1 1 5E883602
P 6500 3200
F 0 "#PWR032" H 6500 2950 50  0001 C CNN
F 1 "GNDA" H 6505 3027 50  0000 C CNN
F 2 "" H 6500 3200 50  0001 C CNN
F 3 "" H 6500 3200 50  0001 C CNN
	1    6500 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR033
U 1 1 5E883904
P 6750 4050
F 0 "#PWR033" H 6750 3800 50  0001 C CNN
F 1 "GNDA" H 6755 3877 50  0000 C CNN
F 2 "" H 6750 4050 50  0001 C CNN
F 3 "" H 6750 4050 50  0001 C CNN
	1    6750 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5E883C68
P 6250 4050
F 0 "#PWR030" H 6250 3800 50  0001 C CNN
F 1 "GND" H 6255 3877 50  0000 C CNN
F 2 "" H 6250 4050 50  0001 C CNN
F 3 "" H 6250 4050 50  0001 C CNN
	1    6250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3200 6500 3000
$Comp
L akizuki:C-POL C12
U 1 1 5E888894
P 7500 2750
F 0 "C12" H 7583 2803 60  0000 L CNN
F 1 "22uF" H 7583 2697 60  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7500 2750 60  0001 C CNN
F 3 "" V 7500 2750 60  0000 C CNN
	1    7500 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2600 7500 2500
Wire Wire Line
	7500 2500 7000 2500
Connection ~ 7000 2500
Wire Wire Line
	7500 2900 7500 3000
Wire Wire Line
	7500 3000 7000 3000
Connection ~ 7000 3000
$Comp
L akizuki:C C13
U 1 1 5E88C3EC
P 8000 2750
F 0 "C13" H 8082 2803 60  0000 L CNN
F 1 "0.01uF" H 8082 2697 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8000 2750 60  0001 C CNN
F 3 "" V 8000 2750 60  0000 C CNN
	1    8000 2750
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C14
U 1 1 5E88C7A8
P 8500 2750
F 0 "C14" H 8582 2803 60  0000 L CNN
F 1 "0.01uF" H 8582 2697 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8500 2750 60  0001 C CNN
F 3 "" V 8500 2750 60  0000 C CNN
	1    8500 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 2600 8000 2500
Wire Wire Line
	8000 2500 7500 2500
Connection ~ 7500 2500
Wire Wire Line
	8000 2900 8000 3000
Wire Wire Line
	8000 3000 7500 3000
Connection ~ 7500 3000
Wire Wire Line
	8500 2600 8500 2500
Wire Wire Line
	8500 2500 8000 2500
Connection ~ 8000 2500
Wire Wire Line
	8500 2900 8500 3000
Wire Wire Line
	8500 3000 8000 3000
Connection ~ 8000 3000
$Comp
L akizuki:FB FB1
U 1 1 5E8945D3
P 6700 1900
F 0 "FB1" H 6700 2125 50  0000 C CNN
F 1 "BLM18R" H 6700 2034 50  0000 C CNN
F 2 "" H 6850 1900 50  0001 C CNN
F 3 "" H 6850 1900 50  0001 C CNN
	1    6700 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 4050 6750 3950
Wire Wire Line
	6750 3950 6650 3950
Wire Wire Line
	6250 4050 6250 3950
Wire Wire Line
	6250 3950 6350 3950
$Comp
L akizuki:R R1
U 1 1 5E8993C3
P 6500 3950
F 0 "R1" H 6500 4157 50  0000 C CNN
F 1 "0" H 6500 4066 50  0000 C CNN
F 2 "" H 6500 3880 50  0000 C CNN
F 3 "" V 6500 3950 50  0000 C CNN
	1    6500 3950
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR031
U 1 1 5E8A0DEF
P 6350 1800
F 0 "#PWR031" H 6350 1650 50  0001 C CNN
F 1 "VCC" H 6367 1973 50  0000 C CNN
F 2 "" H 6350 1800 50  0001 C CNN
F 3 "" H 6350 1800 50  0001 C CNN
	1    6350 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 5E8A949D
P 7200 2000
F 0 "J7" H 7280 2042 50  0000 L CNN
F 1 "AnaSel" H 7280 1951 50  0000 L CNN
F 2 "" H 7200 2000 50  0001 C CNN
F 3 "~" H 7200 2000 50  0001 C CNN
	1    7200 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2000 6500 2000
Wire Wire Line
	6500 2000 6500 2500
Wire Wire Line
	7000 1900 6850 1900
Wire Wire Line
	6550 1900 6350 1900
Wire Wire Line
	6350 1900 6350 1800
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 5E8BF106
P 8300 2000
F 0 "J8" H 8380 1992 50  0000 L CNN
F 1 "AnaPow" H 8380 1901 50  0000 L CNN
F 2 "" H 8300 2000 50  0001 C CNN
F 3 "~" H 8300 2000 50  0001 C CNN
	1    8300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2100 6900 2100
Wire Wire Line
	6900 2100 6900 2250
Wire Wire Line
	6900 2250 7650 2250
Wire Wire Line
	7650 2250 7650 2000
Wire Wire Line
	7650 2000 8100 2000
Wire Wire Line
	8100 2100 8000 2100
Wire Wire Line
	8000 2100 8000 2250
Wire Wire Line
	8000 2250 9000 2250
Wire Wire Line
	9000 2250 9000 3000
Wire Wire Line
	9000 3000 8500 3000
Connection ~ 8500 3000
$EndSCHEMATC
