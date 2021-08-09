EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 8
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
L akizuki:NJU7223DL1-33 U1
U 1 1 61D476EA
P 4200 2700
F 0 "U1" H 4200 3087 60  0000 C CNN
F 1 "NJU7223DL1-33" H 4200 2981 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-252-2" H 4200 2700 60  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/njr/NJU7223_j.pdf" H 4200 2700 60  0001 C CNN
	1    4200 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2600 3500 2600
Wire Wire Line
	3000 2600 3000 2500
$Comp
L power:+5V #PWR030
U 1 1 61D488B6
P 3000 2500
F 0 "#PWR030" H 3000 2350 50  0001 C CNN
F 1 "+5V" H 3015 2673 50  0000 C CNN
F 2 "" H 3000 2500 50  0001 C CNN
F 3 "" H 3000 2500 50  0001 C CNN
	1    3000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2600 5000 2600
$Comp
L power:+3.3V #PWR036
U 1 1 61D48AFC
P 6200 2300
F 0 "#PWR036" H 6200 2150 50  0001 C CNN
F 1 "+3.3V" H 6215 2473 50  0000 C CNN
F 2 "" H 6200 2300 50  0001 C CNN
F 3 "" H 6200 2300 50  0001 C CNN
	1    6200 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2800 4800 2800
Wire Wire Line
	4800 2800 4800 3000
$Comp
L power:GND #PWR033
U 1 1 61D48C9D
P 4800 3000
F 0 "#PWR033" H 4800 2750 50  0001 C CNN
F 1 "GND" H 4805 2827 50  0000 C CNN
F 2 "" H 4800 3000 50  0001 C CNN
F 3 "" H 4800 3000 50  0001 C CNN
	1    4800 3000
	1    0    0    -1  
$EndComp
$Comp
L rx72t_100_pga_usb-rescue:C-POL-akizuki C1
U 1 1 61D48DB7
P 3000 2950
AR Path="/61D48DB7" Ref="C1"  Part="1" 
AR Path="/610674D7/61D48DB7" Ref="C1"  Part="1" 
F 0 "C1" H 3083 3003 60  0000 L CNN
F 1 "47uF" H 3083 2897 60  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" V 3000 2950 60  0001 C CNN
F 3 "" V 3000 2950 60  0001 C CNN
	1    3000 2950
	1    0    0    -1  
$EndComp
$Comp
L rx72t_100_pga_usb-rescue:C-POL-akizuki C6
U 1 1 61D497D6
P 5000 2950
AR Path="/61D497D6" Ref="C6"  Part="1" 
AR Path="/610674D7/61D497D6" Ref="C6"  Part="1" 
F 0 "C6" H 5083 3003 60  0000 L CNN
F 1 "47uF" H 5083 2897 60  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" V 5000 2950 60  0001 C CNN
F 3 "" V 5000 2950 60  0001 C CNN
	1    5000 2950
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C3
U 1 1 61D4A008
P 3500 2950
F 0 "C3" H 3582 3003 60  0000 L CNN
F 1 "0.47uF" H 3582 2897 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3500 2950 60  0001 C CNN
F 3 "" V 3500 2950 60  0001 C CNN
	1    3500 2950
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C8
U 1 1 61D4A4BB
P 5500 2950
F 0 "C8" H 5582 3003 60  0000 L CNN
F 1 "0.47uF" H 5582 2897 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5500 2950 60  0001 C CNN
F 3 "" V 5500 2950 60  0001 C CNN
	1    5500 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2800 5500 2600
Wire Wire Line
	5000 2800 5000 2600
Connection ~ 5000 2600
Wire Wire Line
	3500 2800 3500 2600
Connection ~ 3500 2600
Wire Wire Line
	3500 2600 3000 2600
Wire Wire Line
	3000 2800 3000 2600
Connection ~ 3000 2600
Wire Wire Line
	3000 3100 3000 3300
Wire Wire Line
	3000 3300 3500 3300
Wire Wire Line
	3500 3300 3500 3100
Wire Wire Line
	5000 3100 5000 3300
Wire Wire Line
	5500 3300 5500 3100
Wire Wire Line
	5500 3300 5500 3500
Connection ~ 5500 3300
Wire Wire Line
	3000 3300 3000 3500
Connection ~ 3000 3300
$Comp
L power:GND #PWR034
U 1 1 61D4C6E4
P 5500 3500
F 0 "#PWR034" H 5500 3250 50  0001 C CNN
F 1 "GND" H 5505 3327 50  0000 C CNN
F 2 "" H 5500 3500 50  0001 C CNN
F 3 "" H 5500 3500 50  0001 C CNN
	1    5500 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR031
U 1 1 61D4C820
P 3000 3500
F 0 "#PWR031" H 3000 3250 50  0001 C CNN
F 1 "GND" H 3005 3327 50  0000 C CNN
F 2 "" H 3000 3500 50  0001 C CNN
F 3 "" H 3000 3500 50  0001 C CNN
	1    3000 3500
	1    0    0    -1  
$EndComp
$Comp
L akizuki:FB FB1
U 1 1 61D4CD52
P 6550 2600
F 0 "FB1" H 6550 2825 50  0000 C CNN
F 1 "FB" H 6550 2734 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6700 2600 50  0001 C CNN
F 3 "" H 6700 2600 50  0001 C CNN
	1    6550 2600
	1    0    0    -1  
$EndComp
$Comp
L akizuki:FB FB2
U 1 1 61D4D09A
P 6550 3300
F 0 "FB2" H 6550 3525 50  0000 C CNN
F 1 "FB" H 6550 3434 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6700 3300 50  0001 C CNN
F 3 "" H 6700 3300 50  0001 C CNN
	1    6550 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2600 6900 2600
Wire Wire Line
	6700 3300 6900 3300
Wire Wire Line
	7500 3300 7500 3500
$Comp
L power:GNDA #PWR038
U 1 1 61D4DEF4
P 7500 3500
F 0 "#PWR038" H 7500 3250 50  0001 C CNN
F 1 "GNDA" H 7505 3327 50  0000 C CNN
F 2 "" H 7500 3500 50  0001 C CNN
F 3 "" H 7500 3500 50  0001 C CNN
	1    7500 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR037
U 1 1 61D4E0B0
P 7500 2600
F 0 "#PWR037" H 7500 2450 50  0001 C CNN
F 1 "+3.3VA" V 7515 2728 50  0000 L CNN
F 2 "" H 7500 2600 50  0001 C CNN
F 3 "" H 7500 2600 50  0001 C CNN
	1    7500 2600
	0    1    1    0   
$EndComp
$Comp
L akizuki:C C9
U 1 1 61D4ED11
P 6900 2950
F 0 "C9" H 6982 3003 60  0000 L CNN
F 1 "0.47uF" H 6982 2897 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6900 2950 60  0001 C CNN
F 3 "" V 6900 2950 60  0001 C CNN
	1    6900 2950
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C10
U 1 1 61D4F379
P 7400 2950
F 0 "C10" H 7482 3003 60  0000 L CNN
F 1 "10uF" H 7482 2897 60  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7400 2950 60  0001 C CNN
F 3 "" V 7400 2950 60  0001 C CNN
	1    7400 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2800 6900 2600
Wire Wire Line
	7400 2800 7400 2600
Wire Wire Line
	7400 2600 7500 2600
Wire Wire Line
	7400 3100 7400 3300
Wire Wire Line
	7400 3300 7500 3300
Wire Wire Line
	6900 3100 6900 3300
Wire Wire Line
	5000 2600 5500 2600
Wire Wire Line
	5000 3300 5500 3300
Wire Wire Line
	5500 3300 6400 3300
Wire Wire Line
	6900 3300 7400 3300
Connection ~ 6900 3300
Connection ~ 7400 3300
Wire Wire Line
	6900 2600 7400 2600
Connection ~ 6900 2600
Connection ~ 7400 2600
$Comp
L akizuki:Diode D2
U 1 1 61D52979
P 4200 2050
F 0 "D2" V 4422 2050 60  0000 C CNN
F 1 "1A" V 4316 2050 60  0000 C CNN
F 2 "Diode_SMD:D_SOD-123F" V 4100 2050 60  0001 C CNN
F 3 "" V 4195 2015 60  0001 C CNN
	1    4200 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 2050 3500 2050
Wire Wire Line
	3500 2050 3500 2600
Wire Wire Line
	4350 2050 5000 2050
Wire Wire Line
	5000 2050 5000 2600
Wire Wire Line
	6200 2300 6200 2600
Wire Wire Line
	6200 2600 6400 2600
$Comp
L Connector_Generic:Conn_01x02 J12
U 1 1 6210AD6B
P 5950 1750
F 0 "J12" H 6030 1742 50  0000 L CNN
F 1 "5V_POW" H 6030 1651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5950 1750 50  0001 C CNN
F 3 "~" H 5950 1750 50  0001 C CNN
	1    5950 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1850 5650 1850
Wire Wire Line
	5650 1850 5650 2600
Wire Wire Line
	5650 2600 6200 2600
Connection ~ 6200 2600
Wire Wire Line
	5500 2600 5500 1750
Wire Wire Line
	5500 1750 5750 1750
Connection ~ 5500 2600
$Comp
L akizuki:R-78E5 M1
U 1 1 6210ED36
P 4250 4300
F 0 "M1" H 4250 4615 50  0000 C CNN
F 1 "BP5293-5" H 4250 4524 50  0000 C CNN
F 2 "KiCAD_lib:BP5293" H 4250 4500 50  0001 C CNN
F 3 "" H 4250 4500 50  0001 C CNN
	1    4250 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4650 4250 4850
$Comp
L power:GND #PWR032
U 1 1 6210F9E1
P 4250 4900
F 0 "#PWR032" H 4250 4650 50  0001 C CNN
F 1 "GND" H 4255 4727 50  0000 C CNN
F 2 "" H 4250 4900 50  0001 C CNN
F 3 "" H 4250 4900 50  0001 C CNN
	1    4250 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4300 3600 4300
$Comp
L power:+12V #PWR029
U 1 1 62110F2D
P 2500 4300
F 0 "#PWR029" H 2500 4150 50  0001 C CNN
F 1 "+12V" V 2515 4428 50  0000 L CNN
F 2 "" H 2500 4300 50  0001 C CNN
F 3 "" H 2500 4300 50  0001 C CNN
	1    2500 4300
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR035
U 1 1 621115E5
P 5950 4700
F 0 "#PWR035" H 5950 4550 50  0001 C CNN
F 1 "+5V" V 5965 4828 50  0000 L CNN
F 2 "" H 5950 4700 50  0001 C CNN
F 3 "" H 5950 4700 50  0001 C CNN
	1    5950 4700
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J13
U 1 1 62112CCC
P 6150 4300
F 0 "J13" H 6230 4292 50  0000 L CNN
F 1 "12V_POW" H 6230 4201 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6150 4300 50  0001 C CNN
F 3 "~" H 6150 4300 50  0001 C CNN
	1    6150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4400 5850 4400
Wire Wire Line
	5850 4400 5850 4700
$Comp
L akizuki:C C2
U 1 1 62115AFE
P 3200 4600
F 0 "C2" H 3283 4653 60  0000 L CNN
F 1 "0.1uF" H 3283 4547 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3200 4600 60  0001 C CNN
F 3 "" V 3200 4600 60  0001 C CNN
	1    3200 4600
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C5
U 1 1 62115EF1
P 4800 4600
F 0 "C5" H 4883 4653 60  0000 L CNN
F 1 "0.1uF" H 4883 4547 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4800 4600 60  0001 C CNN
F 3 "" V 4800 4600 60  0001 C CNN
	1    4800 4600
	1    0    0    -1  
$EndComp
$Comp
L rx72t_100_pga_usb-rescue:C-POL-akizuki C4
U 1 1 621163E2
P 3600 4600
AR Path="/621163E2" Ref="C4"  Part="1" 
AR Path="/610674D7/621163E2" Ref="C4"  Part="1" 
F 0 "C4" H 3683 4653 60  0000 L CNN
F 1 "10uF" H 3683 4547 60  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3600 4600 60  0001 C CNN
F 3 "" V 3600 4600 60  0001 C CNN
	1    3600 4600
	1    0    0    -1  
$EndComp
$Comp
L rx72t_100_pga_usb-rescue:C-POL-akizuki C7
U 1 1 6211688B
P 5150 4600
AR Path="/6211688B" Ref="C7"  Part="1" 
AR Path="/610674D7/6211688B" Ref="C7"  Part="1" 
F 0 "C7" H 5233 4653 60  0000 L CNN
F 1 "10uF" H 5233 4547 60  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5150 4600 60  0001 C CNN
F 3 "" V 5150 4600 60  0001 C CNN
	1    5150 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4700 5850 4700
Wire Wire Line
	4650 4300 4800 4300
Wire Wire Line
	3200 4450 3200 4300
Connection ~ 3200 4300
Wire Wire Line
	3200 4300 3000 4300
Wire Wire Line
	3600 4450 3600 4300
Connection ~ 3600 4300
Wire Wire Line
	3600 4300 3200 4300
Wire Wire Line
	4800 4450 4800 4300
Connection ~ 4800 4300
Wire Wire Line
	4800 4300 5150 4300
Wire Wire Line
	5150 4450 5150 4300
Connection ~ 5150 4300
Wire Wire Line
	5150 4300 5950 4300
Wire Wire Line
	4800 4750 4800 4850
Wire Wire Line
	4800 4850 5150 4850
Wire Wire Line
	5150 4850 5150 4750
Wire Wire Line
	3600 4750 3600 4850
Wire Wire Line
	3600 4850 3200 4850
Wire Wire Line
	3200 4850 3200 4750
Wire Wire Line
	3600 4850 4250 4850
Connection ~ 3600 4850
Connection ~ 4250 4850
Wire Wire Line
	4250 4850 4250 4900
Wire Wire Line
	4250 4850 4800 4850
Connection ~ 4800 4850
$Comp
L akizuki:Shotkey D1
U 1 1 6212494A
P 2850 4300
F 0 "D1" V 2623 4300 60  0000 C CNN
F 1 "1A" V 2729 4300 60  0000 C CNN
F 2 "Diode_SMD:D_SOD-123F" V 2950 4300 60  0001 C CNN
F 3 "" V 2845 4265 60  0001 C CNN
	1    2850 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 4300 2500 4300
$Comp
L Device:LED D4
U 1 1 61165795
P 8500 3150
F 0 "D4" V 8539 3033 50  0000 R CNN
F 1 "BLUE" V 8448 3033 50  0000 R CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8500 3150 50  0001 C CNN
F 3 "~" H 8500 3150 50  0001 C CNN
	1    8500 3150
	0    -1   -1   0   
$EndComp
$Comp
L akizuki:R R29
U 1 1 6116696A
P 8500 2850
F 0 "R29" V 8454 2920 50  0000 L CNN
F 1 "330" V 8545 2920 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8591 2920 50  0001 L CNN
F 3 "" V 8500 2850 50  0001 C CNN
	1    8500 2850
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 611671BD
P 8500 2700
F 0 "#PWR017" H 8500 2550 50  0001 C CNN
F 1 "+3.3V" H 8515 2873 50  0000 C CNN
F 2 "" H 8500 2700 50  0001 C CNN
F 3 "" H 8500 2700 50  0001 C CNN
	1    8500 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 61167A93
P 8500 3300
F 0 "#PWR028" H 8500 3050 50  0001 C CNN
F 1 "GND" H 8505 3127 50  0000 C CNN
F 2 "" H 8500 3300 50  0001 C CNN
F 3 "" H 8500 3300 50  0001 C CNN
	1    8500 3300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
