EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 8
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
L Connector:USB_A J17
U 1 1 6107FF45
P 6700 3300
F 0 "J17" H 6470 3289 50  0000 R CNN
F 1 "MASTER" H 6470 3198 50  0000 R CNN
F 2 "KiCAD_lib:USB-4AF103BS" H 6850 3250 50  0001 C CNN
F 3 " ~" H 6850 3250 50  0001 C CNN
	1    6700 3300
	-1   0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J16
U 1 1 61080995
P 4200 3300
F 0 "J16" H 4257 3767 50  0000 C CNN
F 1 "SLAVE" H 4257 3676 50  0000 C CNN
F 2 "KiCAD_lib:USB_MICRO_B-HIROSE-ZX62R-B-5P" H 4350 3250 50  0001 C CNN
F 3 "" H 4350 3250 50  0001 C CNN
	1    4200 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3700 4100 3900
Wire Wire Line
	4100 3900 4200 3900
Wire Wire Line
	4200 3900 4200 3700
Wire Wire Line
	6700 3700 6700 3900
Wire Wire Line
	6700 3900 6800 3900
Wire Wire Line
	6800 3900 6800 3700
Wire Wire Line
	6700 3900 6700 4000
Connection ~ 6700 3900
Wire Wire Line
	4100 3900 4100 4000
Connection ~ 4100 3900
$Comp
L power:GND #PWR059
U 1 1 610834B1
P 6700 4000
F 0 "#PWR059" H 6700 3750 50  0001 C CNN
F 1 "GND" H 6705 3827 50  0000 C CNN
F 2 "" H 6700 4000 50  0001 C CNN
F 3 "" H 6700 4000 50  0001 C CNN
	1    6700 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR053
U 1 1 610835B8
P 4100 4000
F 0 "#PWR053" H 4100 3750 50  0001 C CNN
F 1 "GND" H 4105 3827 50  0000 C CNN
F 2 "" H 4100 4000 50  0001 C CNN
F 3 "" H 4100 4000 50  0001 C CNN
	1    4100 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3300 5200 3300
Wire Wire Line
	4500 3400 5100 3400
Wire Wire Line
	5200 3300 5200 2250
Wire Wire Line
	5200 2250 4550 2250
Connection ~ 5200 3300
Wire Wire Line
	5200 3300 6400 3300
Wire Wire Line
	5100 3400 5100 2350
Wire Wire Line
	5100 2350 4550 2350
Connection ~ 5100 3400
Wire Wire Line
	5100 3400 6400 3400
Text HLabel 4550 2250 0    50   BiDi ~ 0
USB_DP
Text HLabel 4550 2350 0    50   BiDi ~ 0
USB_DM
Text HLabel 4500 1350 0    50   UnSpc ~ 0
USB_VCC
Text HLabel 4500 1900 0    50   UnSpc ~ 0
USB_VSS
NoConn ~ 4500 3500
$Comp
L power:GND #PWR057
U 1 1 610B4FB2
P 5950 2100
F 0 "#PWR057" H 5950 1850 50  0001 C CNN
F 1 "GND" H 5955 1927 50  0000 C CNN
F 2 "" H 5950 2100 50  0001 C CNN
F 3 "" H 5950 2100 50  0001 C CNN
	1    5950 2100
	1    0    0    -1  
$EndComp
Text HLabel 4500 4600 0    50   BiDi ~ 0
USB_OVRCUR
Text HLabel 4500 4500 0    50   BiDi ~ 0
USB_VBUSEN
Text HLabel 1650 3150 0    50   BiDi ~ 0
USB_VBUS
$Comp
L Power_Management:MIC2026-1BM U4
U 1 1 61F83EBA
P 5500 4800
F 0 "U4" H 5500 5367 50  0000 C CNN
F 1 "MIC2026-1BM" H 5500 5276 50  0000 C CNN
F 2 "Package_SO:SOP-8_3.76x4.96mm_P1.27mm" H 5500 4800 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/mic2026.pdf" H 5500 4800 50  0001 C CNN
	1    5500 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4700 6250 4700
Wire Wire Line
	6250 4700 6250 3100
Wire Wire Line
	6250 3100 6400 3100
Wire Wire Line
	5900 4500 6050 4500
Wire Wire Line
	6050 4500 6050 4000
$Comp
L power:+5V #PWR058
U 1 1 61F8660F
P 6050 4000
F 0 "#PWR058" H 6050 3850 50  0001 C CNN
F 1 "+5V" H 6065 4173 50  0000 C CNN
F 2 "" H 6050 4000 50  0001 C CNN
F 3 "" H 6050 4000 50  0001 C CNN
	1    6050 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR055
U 1 1 61F86781
P 5500 5500
F 0 "#PWR055" H 5500 5250 50  0001 C CNN
F 1 "GND" H 5505 5327 50  0000 C CNN
F 2 "" H 5500 5500 50  0001 C CNN
F 3 "" H 5500 5500 50  0001 C CNN
	1    5500 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4500 4500 4500
Wire Wire Line
	4500 4600 5100 4600
$Comp
L akizuki:R R22
U 1 1 61F8848D
P 2000 2850
F 0 "R22" V 1954 2920 50  0000 L CNN
F 1 "15K" V 2045 2920 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2000 2780 50  0001 C CNN
F 3 "" V 2000 2850 50  0001 C CNN
	1    2000 2850
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R23
U 1 1 61F8948D
P 2000 3450
F 0 "R23" V 1954 3520 50  0000 L CNN
F 1 "30K" V 2045 3520 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2000 3380 50  0001 C CNN
F 3 "" V 2000 3450 50  0001 C CNN
	1    2000 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 3000 2000 3150
Wire Wire Line
	2000 2700 2000 2500
Wire Wire Line
	2000 3600 2000 3900
Wire Wire Line
	2000 3150 1650 3150
Connection ~ 2000 3150
Wire Wire Line
	2000 3150 2000 3300
$Comp
L akizuki:C C16
U 1 1 61F8BED1
P 5950 1650
F 0 "C16" H 6033 1703 60  0000 L CNN
F 1 "0.1uF" H 6033 1597 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5950 1650 60  0001 C CNN
F 3 "" V 5950 1650 60  0001 C CNN
	1    5950 1650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C18
U 1 1 61F8CC16
P 6800 4800
F 0 "C18" H 6883 4853 60  0000 L CNN
F 1 "0.1uF" H 6883 4747 60  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6800 4800 60  0001 C CNN
F 3 "" V 6800 4800 60  0001 C CNN
	1    6800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 4500 6800 4500
Wire Wire Line
	6800 4500 6800 4650
Connection ~ 6050 4500
Wire Wire Line
	5500 5300 5500 5400
Wire Wire Line
	5500 5400 6250 5400
Wire Wire Line
	6800 5400 6800 4950
Connection ~ 5500 5400
Wire Wire Line
	5500 5400 5500 5500
Wire Wire Line
	4500 1350 5950 1350
Wire Wire Line
	5950 1350 5950 1500
Wire Wire Line
	5950 1900 5950 1800
$Comp
L Device:Polyfuse F1
U 1 1 61F92F9E
P 4750 3100
F 0 "F1" V 4525 3100 50  0000 C CNN
F 1 "0.5A" V 4616 3100 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 4800 2900 50  0001 L CNN
F 3 "~" H 4750 3100 50  0001 C CNN
	1    4750 3100
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR054
U 1 1 61F95BEC
P 5400 3100
F 0 "#PWR054" H 5400 2950 50  0001 C CNN
F 1 "+5V" V 5415 3228 50  0000 L CNN
F 2 "" H 5400 3100 50  0001 C CNN
F 3 "" H 5400 3100 50  0001 C CNN
	1    5400 3100
	0    1    1    0   
$EndComp
NoConn ~ 5900 4900
NoConn ~ 5100 4800
NoConn ~ 5100 4900
Wire Wire Line
	4600 3100 4500 3100
Wire Wire Line
	4900 3100 5000 3100
Wire Wire Line
	5000 3100 5000 2500
Connection ~ 5000 3100
Wire Wire Line
	5000 3100 5400 3100
Wire Wire Line
	2000 3900 2500 3900
$Comp
L akizuki:R R24
U 1 1 61F9E3E9
P 3000 2500
F 0 "R24" H 3000 2707 50  0000 C CNN
F 1 "100" H 3000 2616 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3000 2430 50  0001 C CNN
F 3 "" V 3000 2500 50  0001 C CNN
	1    3000 2500
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C14
U 1 1 61F9E4DE
P 2500 2850
F 0 "C14" H 2583 2903 60  0000 L CNN
F 1 "1uF" H 2583 2797 60  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2500 2850 60  0001 C CNN
F 3 "" V 2500 2850 60  0001 C CNN
	1    2500 2850
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C15
U 1 1 61F9EBBE
P 3500 2850
F 0 "C15" H 3583 2903 60  0000 L CNN
F 1 "1uF" H 3583 2797 60  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3500 2850 60  0001 C CNN
F 3 "" V 3500 2850 60  0001 C CNN
	1    3500 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2500 2500 2500
Wire Wire Line
	3150 2500 3500 2500
Wire Wire Line
	3500 2700 3500 2500
Connection ~ 3500 2500
Wire Wire Line
	3500 2500 5000 2500
Wire Wire Line
	2500 2700 2500 2500
Connection ~ 2500 2500
Wire Wire Line
	2500 2500 2850 2500
Wire Wire Line
	2500 3000 2500 3900
Connection ~ 2500 3900
Wire Wire Line
	2500 3900 3500 3900
Wire Wire Line
	3500 3000 3500 3900
Connection ~ 3500 3900
Wire Wire Line
	3500 3900 4100 3900
$Comp
L rx72t_100_pga_usb-rescue:C-POL-akizuki C17
U 1 1 61FA3D3A
P 6250 5050
AR Path="/61FA3D3A" Ref="C17"  Part="1" 
AR Path="/6106759C/61FA3D3A" Ref="C17"  Part="1" 
F 0 "C17" H 6333 5103 60  0000 L CNN
F 1 "100uF" H 6333 4997 60  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" V 6250 5050 60  0001 C CNN
F 3 "" V 6250 5050 60  0001 C CNN
	1    6250 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 4900 6250 4700
Connection ~ 6250 4700
Wire Wire Line
	6250 5200 6250 5400
Connection ~ 6250 5400
Wire Wire Line
	6250 5400 6800 5400
Wire Wire Line
	4500 1900 5950 1900
Wire Wire Line
	5950 2100 5950 1900
Connection ~ 5950 1900
Wire Wire Line
	5950 1350 5950 1200
Connection ~ 5950 1350
$Comp
L power:+3.3V #PWR056
U 1 1 61FABF62
P 5950 1200
F 0 "#PWR056" H 5950 1050 50  0001 C CNN
F 1 "+3.3V" H 5965 1373 50  0000 C CNN
F 2 "" H 5950 1200 50  0001 C CNN
F 3 "" H 5950 1200 50  0001 C CNN
	1    5950 1200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
