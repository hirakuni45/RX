EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 6150 5700 700  1250
U 6106749E
F0 "JTAG_IF" 50
F1 "JTAG_IF.sch" 50
F2 "TCK_FINEC" O L 6150 5850 50 
F3 "TMS" O L 6150 5950 50 
F4 "TRSTn" O L 6150 6050 50 
F5 "RESn" B L 6150 6400 50 
F6 "UB" B L 6150 6600 50 
F7 "MD_FINED" B L 6150 6700 50 
F8 "EMLE" B L 6150 6800 50 
F9 "TDI_RXD1" O L 6150 6150 50 
F10 "TDO_TXD1" I L 6150 6250 50 
$EndSheet
$Sheet
S 9950 850  900  1650
U 610674D7
F0 "POWER" 50
F1 "POWER.sch" 50
$EndSheet
$Sheet
S 7300 2800 700  400 
U 61067526
F0 "CAN_IF" 50
F1 "CAN_IF.sch" 50
F2 "CTX" I L 7300 2950 50 
F3 "CRX" O L 7300 3050 50 
$EndSheet
$Sheet
S 5650 950  700  850 
U 61067568
F0 "SDC_IF" 50
F1 "SDC_IF.sch" 50
F2 "MOSI" B L 5650 1200 50 
F3 "MISO" B L 5650 1300 50 
F4 "SPCK" B L 5650 1100 50 
F5 "SEL" B L 5650 1400 50 
F6 "POW" B L 5650 1600 50 
F7 "INS" B L 5650 1700 50 
$EndSheet
$Sheet
S 1950 6250 700  900 
U 6106759C
F0 "USB_IF" 50
F1 "USB_IF.sch" 50
F2 "USB_DP" B R 2650 6600 50 
F3 "USB_DM" B R 2650 6700 50 
F4 "USB_VCC" U R 2650 6400 50 
F5 "USB_VSS" U R 2650 6500 50 
F6 "USB_OVRCUR" B R 2650 6800 50 
F7 "USB_VBUSEN" B R 2650 6900 50 
F8 "USB_VBUS" B R 2650 7000 50 
$EndSheet
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J2
U 1 1 611607D5
P 1550 1350
F 0 "J2" H 1600 1867 50  0000 C CNN
F 1 "GPTW_012" H 1600 1776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x08_P2.54mm_Vertical" H 1550 1350 50  0001 C CNN
F 3 "~" H 1550 1350 50  0001 C CNN
	1    1550 1350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J3
U 1 1 61162096
P 1550 2550
F 0 "J3" H 1600 3067 50  0000 C CNN
F 1 "GPTW_456" H 1600 2976 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x08_P2.54mm_Vertical" H 1550 2550 50  0001 C CNN
F 3 "~" H 1550 2550 50  0001 C CNN
	1    1550 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1100 3000 1100
Wire Wire Line
	2750 1200 3000 1200
Wire Wire Line
	2750 1300 3000 1300
Wire Wire Line
	2750 1400 3000 1400
Wire Wire Line
	2750 1500 3000 1500
Wire Wire Line
	2750 1600 3000 1600
Wire Wire Line
	2750 1700 3000 1700
Wire Wire Line
	2750 1900 3000 1900
Wire Wire Line
	2750 2000 3000 2000
Wire Wire Line
	2750 2100 3000 2100
Wire Wire Line
	2750 2200 3000 2200
Wire Wire Line
	2750 2300 3000 2300
Wire Wire Line
	2750 2400 3000 2400
Wire Wire Line
	2750 2500 3000 2500
Text Label 2750 1100 0    50   ~ 0
P70
Text Label 2750 1200 0    50   ~ 0
P71
Text Label 2750 1300 0    50   ~ 0
P72
Text Label 2750 1400 0    50   ~ 0
P73
Text Label 2750 1500 0    50   ~ 0
P74
Text Label 2750 1600 0    50   ~ 0
P75
Text Label 2750 1700 0    50   ~ 0
P76
Text Label 2750 1900 0    50   ~ 0
P90
Text Label 2750 2000 0    50   ~ 0
P91
Text Label 2750 2100 0    50   ~ 0
P92
Text Label 2750 2200 0    50   ~ 0
P93
Text Label 2750 2300 0    50   ~ 0
P94
Text Label 2750 2400 0    50   ~ 0
P95
Text Label 2750 2500 0    50   ~ 0
P96
Entry Wire Line
	2650 1200 2750 1100
Entry Wire Line
	2650 1300 2750 1200
Entry Wire Line
	2650 1400 2750 1300
Entry Wire Line
	2650 1500 2750 1400
Entry Wire Line
	2650 1600 2750 1500
Entry Wire Line
	2650 1700 2750 1600
Entry Wire Line
	2650 2000 2750 1900
Entry Wire Line
	2650 2100 2750 2000
Entry Wire Line
	2650 2200 2750 2100
Entry Wire Line
	2650 2300 2750 2200
Entry Wire Line
	2650 2400 2750 2300
Entry Wire Line
	2650 2500 2750 2400
Entry Wire Line
	2650 2600 2750 2500
Entry Wire Line
	2650 1800 2750 1700
Wire Wire Line
	1850 1050 2100 1050
Wire Wire Line
	1350 1050 1100 1050
Wire Wire Line
	1350 1150 1100 1150
Wire Wire Line
	1850 1150 2100 1150
Wire Wire Line
	1850 1350 2100 1350
Wire Wire Line
	1350 1350 1100 1350
Text Label 1100 1050 0    50   ~ 0
P71
Text Label 1950 1050 0    50   ~ 0
P74
Text Label 1100 1150 0    50   ~ 0
P72
Text Label 1950 1150 0    50   ~ 0
P75
Text Label 1100 1350 0    50   ~ 0
P73
Text Label 1950 1350 0    50   ~ 0
P76
Wire Wire Line
	1850 2250 2100 2250
Wire Wire Line
	1850 2350 2100 2350
Wire Wire Line
	1850 2550 2100 2550
Wire Wire Line
	1350 2250 1100 2250
Wire Wire Line
	1350 2350 1100 2350
Wire Wire Line
	1350 2550 1100 2550
Text Label 1100 2250 0    50   ~ 0
P90
Text Label 1950 2250 0    50   ~ 0
P93
Text Label 1100 2350 0    50   ~ 0
P91
Text Label 1100 2550 0    50   ~ 0
P92
Text Label 1950 2350 0    50   ~ 0
P94
Text Label 1950 2550 0    50   ~ 0
P95
Entry Wire Line
	2100 1050 2200 1150
Entry Wire Line
	2100 1150 2200 1250
Entry Wire Line
	2100 1350 2200 1450
Entry Wire Line
	2100 2250 2200 2350
Entry Wire Line
	2100 2350 2200 2450
Entry Wire Line
	2100 2550 2200 2650
Entry Wire Line
	1000 1150 1100 1050
Entry Wire Line
	1000 1250 1100 1150
Entry Wire Line
	1000 1450 1100 1350
Entry Wire Line
	1000 2350 1100 2250
Entry Wire Line
	1000 2450 1100 2350
Entry Wire Line
	1000 2650 1100 2550
Wire Wire Line
	3000 2700 2750 2700
Wire Wire Line
	3000 2800 2750 2800
Wire Wire Line
	3000 2900 2750 2900
Wire Wire Line
	3000 3000 2750 3000
Wire Wire Line
	3000 3100 2750 3100
Wire Wire Line
	3000 3200 2750 3200
Wire Wire Line
	3000 3300 2750 3300
Wire Wire Line
	3000 3400 2750 3400
Text Label 2750 2700 0    50   ~ 0
P40
Text Label 2750 2800 0    50   ~ 0
P41
Text Label 2750 2900 0    50   ~ 0
P42
Text Label 2750 3000 0    50   ~ 0
P43
Text Label 2750 3100 0    50   ~ 0
P44
Text Label 2750 3200 0    50   ~ 0
P45
Text Label 2750 3300 0    50   ~ 0
P46
Text Label 2750 3400 0    50   ~ 0
P47
Entry Wire Line
	2650 2800 2750 2700
Entry Wire Line
	2650 2900 2750 2800
Entry Wire Line
	2650 3000 2750 2900
Entry Wire Line
	2650 3100 2750 3000
Entry Wire Line
	2650 3200 2750 3100
Entry Wire Line
	2650 3300 2750 3200
Entry Wire Line
	2650 3400 2750 3300
Entry Wire Line
	2650 3500 2750 3400
Wire Wire Line
	1850 2950 2100 2950
Wire Wire Line
	1350 2950 1100 2950
Wire Wire Line
	1350 1750 1100 1750
Wire Wire Line
	1850 1750 2100 1750
Wire Wire Line
	1850 1550 2100 1550
Wire Wire Line
	1350 1550 1100 1550
Wire Wire Line
	1850 2750 2100 2750
Wire Wire Line
	1350 2750 1100 2750
Entry Wire Line
	2100 2750 2200 2850
Entry Wire Line
	2100 2950 2200 3050
Entry Wire Line
	1000 3050 1100 2950
Entry Wire Line
	1000 2850 1100 2750
Entry Wire Line
	2100 1550 2200 1650
Entry Wire Line
	2100 1750 2200 1850
Entry Wire Line
	1000 1850 1100 1750
Entry Wire Line
	1000 1650 1100 1550
Text Label 1100 1550 0    50   ~ 0
P40
Text Label 1950 1550 0    50   ~ 0
P41
Text Label 1100 1750 0    50   ~ 0
P42
Text Label 1950 1750 0    50   ~ 0
P43
Text Label 1100 2750 0    50   ~ 0
P44
Text Label 1950 2750 0    50   ~ 0
P45
Text Label 1100 2950 0    50   ~ 0
P46
Text Label 1950 2950 0    50   ~ 0
P47
Wire Bus Line
	2650 3550 2600 3600
Wire Bus Line
	1050 3600 1000 3550
Wire Bus Line
	2200 3550 2250 3600
Wire Bus Line
	2250 3600 1050 3600
Wire Wire Line
	1900 2850 1850 2850
Wire Wire Line
	1350 2650 1300 2650
Wire Wire Line
	1300 2650 1300 2850
Wire Wire Line
	1300 2850 1350 2850
Wire Wire Line
	1350 1450 1300 1450
Wire Wire Line
	1300 1450 1300 1650
Wire Wire Line
	1300 1650 1350 1650
Wire Wire Line
	1300 1650 1300 1850
Connection ~ 1300 1650
Wire Wire Line
	1900 1650 1850 1650
Wire Wire Line
	1900 1650 1900 1850
Wire Wire Line
	1300 2850 1300 3050
Connection ~ 1300 2850
Wire Wire Line
	1900 2850 1900 3050
$Comp
L power:GNDA #PWR06
U 1 1 61212504
P 1300 1850
F 0 "#PWR06" H 1300 1600 50  0001 C CNN
F 1 "GNDA" H 1305 1677 50  0000 C CNN
F 2 "" H 1300 1850 50  0001 C CNN
F 3 "" H 1300 1850 50  0001 C CNN
	1    1300 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR010
U 1 1 61212594
P 1900 1850
F 0 "#PWR010" H 1900 1600 50  0001 C CNN
F 1 "GNDA" H 1905 1677 50  0000 C CNN
F 2 "" H 1900 1850 50  0001 C CNN
F 3 "" H 1900 1850 50  0001 C CNN
	1    1900 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR07
U 1 1 612126C3
P 1300 3050
F 0 "#PWR07" H 1300 2800 50  0001 C CNN
F 1 "GNDA" H 1305 2877 50  0000 C CNN
F 2 "" H 1300 3050 50  0001 C CNN
F 3 "" H 1300 3050 50  0001 C CNN
	1    1300 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR011
U 1 1 6121280F
P 1900 3050
F 0 "#PWR011" H 1900 2800 50  0001 C CNN
F 1 "GNDA" H 1905 2877 50  0000 C CNN
F 2 "" H 1900 3050 50  0001 C CNN
F 3 "" H 1900 3050 50  0001 C CNN
	1    1900 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  1250 850  2450
Wire Wire Line
	850  2450 850  2600
Connection ~ 850  2450
$Comp
L power:GND #PWR02
U 1 1 612198DB
P 850 2600
F 0 "#PWR02" H 850 2350 50  0001 C CNN
F 1 "GND" H 855 2427 50  0000 C CNN
F 2 "" H 850 2600 50  0001 C CNN
F 3 "" H 850 2600 50  0001 C CNN
	1    850  2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3900 2750 3900
Wire Wire Line
	3000 4000 2750 4000
Wire Wire Line
	3000 4200 2750 4200
Wire Wire Line
	3000 4300 2750 4300
Wire Wire Line
	3000 4400 2750 4400
Wire Wire Line
	3000 4600 2750 4600
Wire Wire Line
	3000 4700 2750 4700
Wire Wire Line
	3000 4800 2750 4800
Wire Wire Line
	3000 4900 2750 4900
Wire Wire Line
	3000 5000 2750 5000
Wire Wire Line
	3000 5100 2750 5100
Wire Wire Line
	3000 5300 2750 5300
Wire Wire Line
	3000 5400 2750 5400
Wire Wire Line
	3000 5500 2750 5500
Wire Wire Line
	3000 5700 2750 5700
Wire Wire Line
	3000 5800 2750 5800
Entry Wire Line
	2650 4000 2750 3900
Entry Wire Line
	2650 4100 2750 4000
Entry Wire Line
	2650 4300 2750 4200
Entry Wire Line
	2650 4400 2750 4300
Entry Wire Line
	2650 4500 2750 4400
Text Label 2750 3900 0    50   ~ 0
P10
Text Label 2750 4000 0    50   ~ 0
P11
Text Label 2750 4200 0    50   ~ 0
P23
Text Label 2750 4300 0    50   ~ 0
P24
Text Label 2750 4400 0    50   ~ 0
P25
Text Label 2750 4600 0    50   ~ 0
P60
Text Label 2750 4700 0    50   ~ 0
P61
Text Label 2750 4800 0    50   ~ 0
P62
Text Label 2750 4900 0    50   ~ 0
P63
Text Label 2750 5000 0    50   ~ 0
P64
Text Label 2750 5100 0    50   ~ 0
P65
Text Label 2750 5300 0    50   ~ 0
P80
Text Label 2750 5400 0    50   ~ 0
P81
Text Label 2750 5500 0    50   ~ 0
P82
Text Label 2750 5700 0    50   ~ 0
PH0
Text Label 2750 5800 0    50   ~ 0
PH4
Entry Wire Line
	2650 4700 2750 4600
Entry Wire Line
	2650 4800 2750 4700
Entry Wire Line
	2650 4900 2750 4800
Entry Wire Line
	2650 5000 2750 4900
Entry Wire Line
	2650 5100 2750 5000
Entry Wire Line
	2650 5200 2750 5100
Entry Wire Line
	2650 5400 2750 5300
Entry Wire Line
	2650 5500 2750 5400
Entry Wire Line
	2650 5600 2750 5500
Entry Wire Line
	2650 5800 2750 5700
Entry Wire Line
	2650 5900 2750 5800
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J4
U 1 1 613039E3
P 1550 4300
F 0 "J4" H 1600 4817 50  0000 C CNN
F 1 "EXT_DG0" H 1600 4726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x07_P2.54mm_Vertical" H 1550 4300 50  0001 C CNN
F 3 "~" H 1550 4300 50  0001 C CNN
	1    1550 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4000 2100 4000
Wire Wire Line
	1350 4000 1100 4000
Wire Wire Line
	1850 4200 2100 4200
Wire Wire Line
	1850 4500 2100 4500
Wire Wire Line
	1100 5100 1350 5100
Wire Wire Line
	1850 5100 2100 5100
Wire Wire Line
	1100 5200 1350 5200
Wire Wire Line
	1850 5200 2100 5200
Wire Wire Line
	1100 5300 1350 5300
Wire Wire Line
	1850 5300 2100 5300
Wire Wire Line
	1100 5500 1350 5500
Wire Wire Line
	1850 5500 2100 5500
Wire Wire Line
	1100 5600 1350 5600
Wire Wire Line
	1100 5800 1350 5800
Wire Wire Line
	1850 5800 2100 5800
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J5
U 1 1 61375AB9
P 1550 5400
F 0 "J5" H 1600 6017 50  0000 C CNN
F 1 "EXT_AN" H 1600 5926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 1550 5400 50  0001 C CNN
F 3 "~" H 1550 5400 50  0001 C CNN
	1    1550 5400
	1    0    0    -1  
$EndComp
Text Label 1100 4000 0    50   ~ 0
P10
Text Label 1950 4000 0    50   ~ 0
P11
Wire Wire Line
	1100 4300 1350 4300
Wire Wire Line
	1850 4300 2100 4300
Text Label 1950 4200 0    50   ~ 0
P23
Text Label 1100 4300 0    50   ~ 0
P24
Text Label 1950 4300 0    50   ~ 0
P25
Text Label 1100 4500 0    50   ~ 0
P70
Text Label 1950 4500 0    50   ~ 0
P96
Text Label 1100 5100 0    50   ~ 0
P60
Text Label 1950 5100 0    50   ~ 0
P61
Text Label 1100 5200 0    50   ~ 0
P62
Text Label 1950 5200 0    50   ~ 0
P63
Text Label 1100 5300 0    50   ~ 0
P64
Text Label 1950 5300 0    50   ~ 0
P65
Text Label 1100 5500 0    50   ~ 0
P80
Text Label 1950 5500 0    50   ~ 0
P81
Text Label 1100 5600 0    50   ~ 0
P82
Text Label 1100 5800 0    50   ~ 0
PH0
Text Label 1950 5800 0    50   ~ 0
PH1
Entry Wire Line
	2100 5100 2200 5200
Entry Wire Line
	2100 5200 2200 5300
Entry Wire Line
	2100 5300 2200 5400
Entry Wire Line
	2100 5500 2200 5600
Entry Wire Line
	2100 5800 2200 5900
Entry Wire Line
	1000 5200 1100 5100
Entry Wire Line
	1000 5300 1100 5200
Entry Wire Line
	1000 5400 1100 5300
Entry Wire Line
	1000 5600 1100 5500
Entry Wire Line
	1000 5700 1100 5600
Entry Wire Line
	1000 5900 1100 5800
Entry Wire Line
	900  3550 1000 3450
Entry Wire Line
	900  3650 1000 3550
Wire Wire Line
	900  3650 700  3650
Wire Wire Line
	700  3650 700  4500
Wire Wire Line
	700  4500 1350 4500
Wire Wire Line
	600  3550 600  4700
Wire Wire Line
	600  4700 2100 4700
Wire Wire Line
	2100 4700 2100 4500
Wire Wire Line
	600  3550 900  3550
Entry Wire Line
	2100 4000 2200 4100
Entry Wire Line
	2100 4200 2200 4300
Entry Wire Line
	2100 4300 2200 4400
Entry Wire Line
	1000 4100 1100 4000
Entry Wire Line
	1000 4400 1100 4300
Wire Bus Line
	1000 6000 1050 6050
Wire Bus Line
	1050 6050 2250 6050
Wire Bus Line
	2600 6050 2650 6000
Wire Bus Line
	2200 6000 2250 6050
$Comp
L power:+3.3V #PWR015
U 1 1 61403EF5
P 2400 850
F 0 "#PWR015" H 2400 700 50  0001 C CNN
F 1 "+3.3V" H 2415 1023 50  0000 C CNN
F 2 "" H 2400 850 50  0001 C CNN
F 3 "" H 2400 850 50  0001 C CNN
	1    2400 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1450 1900 1450
$Comp
L power:+3.3VA #PWR09
U 1 1 61415204
P 1900 850
F 0 "#PWR09" H 1900 700 50  0001 C CNN
F 1 "+3.3VA" H 1915 1023 50  0000 C CNN
F 2 "" H 1900 850 50  0001 C CNN
F 3 "" H 1900 850 50  0001 C CNN
	1    1900 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4100 1300 4200
Wire Wire Line
	1300 4600 1350 4600
Wire Wire Line
	1300 4100 1350 4100
Wire Wire Line
	1300 4400 1350 4400
Connection ~ 1300 4400
Wire Wire Line
	1300 4400 1300 4600
Wire Wire Line
	1300 4200 1350 4200
Connection ~ 1300 4200
Wire Wire Line
	1300 4200 1300 4400
$Comp
L power:GND #PWR03
U 1 1 61444B4A
P 850 3850
F 0 "#PWR03" H 850 3600 50  0001 C CNN
F 1 "GND" H 855 3677 50  0000 C CNN
F 2 "" H 850 3850 50  0001 C CNN
F 3 "" H 850 3850 50  0001 C CNN
	1    850  3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4600 1900 4600
Wire Wire Line
	1900 4600 1900 4400
Wire Wire Line
	1900 4100 1850 4100
Wire Wire Line
	1850 4400 1900 4400
Connection ~ 1900 4400
Wire Wire Line
	1900 4400 1900 4100
$Comp
L power:+3.3V #PWR012
U 1 1 6146352E
P 1900 3850
F 0 "#PWR012" H 1900 3700 50  0001 C CNN
F 1 "+3.3V" H 1915 4023 50  0000 C CNN
F 2 "" H 1900 3850 50  0001 C CNN
F 3 "" H 1900 3850 50  0001 C CNN
	1    1900 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 5900 1350 5900
Wire Wire Line
	1300 5900 1300 6200
Connection ~ 1300 5900
Wire Wire Line
	1300 5700 1350 5700
Connection ~ 1300 5700
Wire Wire Line
	1300 5700 1300 5900
Wire Wire Line
	1300 5400 1350 5400
Wire Wire Line
	1300 5400 1300 5700
Wire Wire Line
	1900 5900 1850 5900
Wire Wire Line
	1850 5600 1900 5600
Connection ~ 1900 5600
Wire Wire Line
	1900 5600 1900 5700
Wire Wire Line
	1850 5700 1900 5700
Connection ~ 1900 5700
Wire Wire Line
	1900 5700 1900 5900
Wire Wire Line
	1850 5400 1900 5400
Wire Wire Line
	1900 5400 1900 5600
$Comp
L power:GNDA #PWR08
U 1 1 614DBBE4
P 1300 6200
F 0 "#PWR08" H 1300 5950 50  0001 C CNN
F 1 "GNDA" H 1305 6027 50  0000 C CNN
F 2 "" H 1300 6200 50  0001 C CNN
F 3 "" H 1300 6200 50  0001 C CNN
	1    1300 6200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR014
U 1 1 614E7B57
P 2300 5700
F 0 "#PWR014" H 2300 5550 50  0001 C CNN
F 1 "+3.3VA" H 2315 5873 50  0000 C CNN
F 2 "" H 2300 5700 50  0001 C CNN
F 3 "" H 2300 5700 50  0001 C CNN
	1    2300 5700
	0    1    1    0   
$EndComp
Wire Bus Line
	2250 3600 2600 3600
Connection ~ 2250 3600
Wire Bus Line
	2250 6050 2600 6050
Connection ~ 2250 6050
Wire Wire Line
	2400 850  2400 1250
Wire Wire Line
	1900 850  1900 1450
Connection ~ 2400 1250
Wire Wire Line
	2400 1250 2400 2450
Wire Wire Line
	2300 2650 2300 1450
Connection ~ 1900 1450
Wire Wire Line
	1900 4100 1900 3850
Connection ~ 1900 4100
Wire Wire Line
	1300 4100 1300 3750
Wire Wire Line
	1300 3750 850  3750
Wire Wire Line
	850  3750 850  3850
Connection ~ 1300 4100
Wire Wire Line
	2650 6400 3000 6400
Wire Wire Line
	2650 6500 3000 6500
Wire Wire Line
	2650 6600 3000 6600
Wire Wire Line
	2650 6700 3000 6700
$Sheet
S 5650 2050 650  1700
U 61642C75
F0 "I2C_SPI_SCI" 50
F1 "I2C_SPI_SCI.sch" 50
F2 "MISO" B L 5650 2350 50 
F3 "MOSI" B L 5650 2250 50 
F4 "SPCK" B L 5650 2150 50 
F5 "SEL" B L 5650 2450 50 
F6 "SCL" B L 5650 2550 50 
F7 "SDA" B L 5650 2650 50 
F8 "RXD8" B L 5650 3050 50 
F9 "TXD8" B L 5650 3150 50 
F10 "SCK8" B L 5650 3250 50 
F11 "PB0" B L 5650 3350 50 
F12 "PB3" B L 5650 3450 50 
F13 "P32" B L 5650 3550 50 
F14 "P33" B L 5650 3650 50 
F15 "RXD11" B L 5650 2750 50 
F16 "TXD11" B L 5650 2850 50 
F17 "SCK11" B L 5650 2950 50 
$EndSheet
Wire Wire Line
	4200 1100 5550 1100
Wire Wire Line
	4200 1200 5450 1200
Wire Wire Line
	4200 1300 5350 1300
Wire Wire Line
	4200 1400 5650 1400
Wire Wire Line
	5650 2150 5550 2150
Wire Wire Line
	5550 2150 5550 1100
Connection ~ 5550 1100
Wire Wire Line
	5550 1100 5650 1100
Wire Wire Line
	5650 2250 5450 2250
Wire Wire Line
	5450 2250 5450 1200
Connection ~ 5450 1200
Wire Wire Line
	5450 1200 5650 1200
Wire Wire Line
	5650 2350 5350 2350
Wire Wire Line
	5350 2350 5350 1300
Connection ~ 5350 1300
Wire Wire Line
	5350 1300 5650 1300
Wire Wire Line
	5650 2450 5250 2450
Wire Wire Line
	5250 2450 5250 1500
Wire Wire Line
	5250 1500 4200 1500
Wire Wire Line
	4200 2550 5650 2550
Wire Wire Line
	5650 2650 4200 2650
Wire Wire Line
	5650 3050 4200 3050
Wire Wire Line
	4200 3150 5650 3150
Wire Wire Line
	5650 3250 4200 3250
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 617C561A
P 1400 6800
F 0 "J1" H 1480 6792 50  0000 L CNN
F 1 "DA_OUT" H 1480 6701 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B4B-EH-A_1x04_P2.50mm_Vertical" H 1400 6800 50  0001 C CNN
F 3 "~" H 1400 6800 50  0001 C CNN
	1    1400 6800
	1    0    0    -1  
$EndComp
Entry Wire Line
	900  5900 1000 5800
Entry Wire Line
	900  6050 1000 5950
Wire Wire Line
	900  5900 700  5900
Wire Wire Line
	700  5900 700  6700
Wire Wire Line
	700  6700 1200 6700
Wire Wire Line
	900  6050 800  6050
Wire Wire Line
	800  6050 800  6800
Wire Wire Line
	800  6800 1200 6800
Text Label 1050 6700 0    50   ~ 0
P64
Text Label 1050 6800 0    50   ~ 0
P65
Wire Wire Line
	1200 6900 1000 6900
Wire Wire Line
	1200 7000 1000 7000
Wire Wire Line
	1000 7000 1000 7200
$Comp
L power:GNDA #PWR05
U 1 1 61834BF0
P 1000 7200
F 0 "#PWR05" H 1000 6950 50  0001 C CNN
F 1 "GNDA" H 1005 7027 50  0000 C CNN
F 2 "" H 1000 7200 50  0001 C CNN
F 3 "" H 1000 7200 50  0001 C CNN
	1    1000 7200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR04
U 1 1 61835124
P 1000 6900
F 0 "#PWR04" H 1000 6750 50  0001 C CNN
F 1 "+3.3VA" V 1015 7027 50  0000 L CNN
F 2 "" H 1000 6900 50  0001 C CNN
F 3 "" H 1000 6900 50  0001 C CNN
	1    1000 6900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4200 5850 5300 5850
Wire Wire Line
	4200 5950 5400 5950
Wire Wire Line
	4200 6050 5500 6050
Wire Wire Line
	4200 6400 6150 6400
Wire Wire Line
	4200 6600 5800 6600
Wire Wire Line
	4200 6700 6150 6700
Wire Wire Line
	4200 6800 6150 6800
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J8
U 1 1 618E922B
P 7450 4700
F 0 "J8" H 7500 5317 50  0000 C CNN
F 1 "EXT_DG1" H 7500 5226 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 7450 4700 50  0001 C CNN
F 3 "~" H 7450 4700 50  0001 C CNN
	1    7450 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3850 4500 3850
Wire Wire Line
	4200 3950 4500 3950
Wire Wire Line
	4200 4050 4500 4050
Wire Wire Line
	4200 4150 4500 4150
Wire Wire Line
	4200 4350 4500 4350
Wire Wire Line
	4200 4450 4500 4450
Wire Wire Line
	4200 4550 4500 4550
Wire Wire Line
	4200 4650 4500 4650
Wire Wire Line
	4200 4750 4500 4750
Wire Wire Line
	4200 4850 4500 4850
Text Label 4350 3850 0    50   ~ 0
P52
Text Label 4350 3950 0    50   ~ 0
P53
Text Label 4350 4050 0    50   ~ 0
P54
Text Label 4350 4150 0    50   ~ 0
P55
Text Label 4350 4350 0    50   ~ 0
PE0
Text Label 4350 4450 0    50   ~ 0
PE1
Text Label 4350 4550 0    50   ~ 0
PE2
Text Label 4350 4650 0    50   ~ 0
PE3
Text Label 4350 4750 0    50   ~ 0
PE4
Text Label 4350 4850 0    50   ~ 0
PE5
Wire Wire Line
	7250 4300 7000 4300
Wire Wire Line
	7750 4300 8000 4300
Wire Wire Line
	7250 4400 7000 4400
Wire Wire Line
	7750 4400 8000 4400
Text Label 7000 4300 0    50   ~ 0
P52
Text Label 7850 4300 0    50   ~ 0
P53
Text Label 7000 4400 0    50   ~ 0
P54
Text Label 7850 4400 0    50   ~ 0
P55
Wire Wire Line
	7250 4600 7000 4600
Wire Wire Line
	7750 4600 8000 4600
Wire Wire Line
	7250 4700 7000 4700
Wire Wire Line
	7750 4700 8000 4700
Wire Wire Line
	7250 4800 7000 4800
Wire Wire Line
	7750 4800 8000 4800
Wire Wire Line
	7250 5000 7000 5000
Wire Wire Line
	7750 5000 8000 5000
Wire Wire Line
	7000 5100 7250 5100
Wire Wire Line
	7000 5200 7250 5200
Wire Wire Line
	8000 5100 7750 5100
Wire Wire Line
	8000 5200 7750 5200
Text Label 7000 4600 0    50   ~ 0
PE0
Text Label 7850 4600 0    50   ~ 0
PE1
Text Label 7850 4700 0    50   ~ 0
PE3
Text Label 7850 4800 0    50   ~ 0
PE5
Text Label 7000 4700 0    50   ~ 0
PE2
Text Label 7000 4800 0    50   ~ 0
PE4
Text Label 7850 5000 0    50   ~ 0
PD3
Text Label 7000 5100 0    50   ~ 0
PD4
Text Label 7850 5100 0    50   ~ 0
PD5
Text Label 7000 5200 0    50   ~ 0
PD6
Text Label 7850 5200 0    50   ~ 0
PD7
Text Label 7000 5000 0    50   ~ 0
P00
Entry Wire Line
	4600 3950 4500 3850
Entry Wire Line
	4600 4050 4500 3950
Entry Wire Line
	4600 4150 4500 4050
Entry Wire Line
	4600 4250 4500 4150
Entry Wire Line
	4600 4450 4500 4350
Entry Wire Line
	4600 4550 4500 4450
Entry Wire Line
	4600 4650 4500 4550
Entry Wire Line
	4600 4750 4500 4650
Entry Wire Line
	4600 4850 4500 4750
Entry Wire Line
	4600 4950 4500 4850
Entry Wire Line
	8000 4300 8100 4200
Entry Wire Line
	8000 4400 8100 4300
Entry Wire Line
	8000 4600 8100 4500
Entry Wire Line
	8000 4700 8100 4600
Entry Wire Line
	8000 4800 8100 4700
Entry Wire Line
	6900 4200 7000 4300
Entry Wire Line
	6900 4300 7000 4400
Entry Wire Line
	6900 4500 7000 4600
Entry Wire Line
	6900 4600 7000 4700
Entry Wire Line
	6900 4700 7000 4800
Entry Wire Line
	6900 5100 7000 5000
Entry Wire Line
	6900 5200 7000 5100
Entry Wire Line
	6900 5300 7000 5200
Wire Bus Line
	4600 5000 4650 5050
Wire Bus Line
	4650 5050 4800 5050
Wire Bus Line
	4800 5050 4850 5000
Wire Bus Line
	4850 5000 4850 4050
Wire Bus Line
	4850 4050 4900 4000
Wire Bus Line
	4900 4000 6850 4000
Wire Bus Line
	8050 4000 8100 4050
Wire Bus Line
	6900 4050 6850 4000
Connection ~ 6850 4000
Entry Wire Line
	8000 5000 8100 5100
Entry Wire Line
	8000 5100 8100 5200
Entry Wire Line
	8000 5200 8100 5300
Wire Wire Line
	5300 5850 5300 4500
Wire Wire Line
	5300 4500 6400 4500
Connection ~ 5300 5850
Wire Wire Line
	5300 5850 6150 5850
Wire Wire Line
	5400 5950 5400 4600
Wire Wire Line
	5400 4600 6400 4600
Connection ~ 5400 5950
Wire Wire Line
	5400 5950 6150 5950
Wire Wire Line
	5500 6050 5500 4700
Wire Wire Line
	5500 4700 6400 4700
Connection ~ 5500 6050
Wire Wire Line
	5500 6050 6150 6050
Wire Wire Line
	5600 6150 5600 4800
Wire Wire Line
	5600 4800 6400 4800
Connection ~ 5600 6150
Wire Wire Line
	5600 6150 6150 6150
Wire Wire Line
	5700 6250 5700 4900
Wire Wire Line
	5700 4900 6400 4900
Connection ~ 5700 6250
Wire Wire Line
	5700 6250 6150 6250
Wire Wire Line
	5800 6600 5800 5000
Wire Wire Line
	5800 5000 6400 5000
Connection ~ 5800 6600
Wire Wire Line
	5800 6600 6150 6600
Entry Wire Line
	6400 4500 6500 4600
Entry Wire Line
	6400 4600 6500 4700
Entry Wire Line
	6400 4700 6500 4800
Entry Wire Line
	6400 4800 6500 4900
Entry Wire Line
	6400 4900 6500 5000
Entry Wire Line
	6400 5000 6500 5100
Text Label 6250 4500 0    50   ~ 0
PD4
Text Label 6250 4600 0    50   ~ 0
PD6
Text Label 6250 4700 0    50   ~ 0
PD7
Text Label 6250 4800 0    50   ~ 0
PD5
Text Label 6250 4900 0    50   ~ 0
PD3
Text Label 6250 5000 0    50   ~ 0
P00
Wire Bus Line
	6500 5450 6550 5500
Wire Bus Line
	6550 5500 6850 5500
Wire Bus Line
	8050 5500 8100 5450
Wire Bus Line
	6900 5450 6850 5500
Connection ~ 6850 5500
Wire Bus Line
	6850 5500 8050 5500
Wire Wire Line
	7250 4500 7200 4500
Wire Wire Line
	7200 4500 7200 4900
Wire Wire Line
	7200 4900 7250 4900
Wire Wire Line
	7200 4900 7200 5650
Connection ~ 7200 4900
Wire Wire Line
	7750 4900 7800 4900
Wire Wire Line
	7800 4900 7800 4500
Wire Wire Line
	7800 4500 7750 4500
Wire Wire Line
	7800 4500 7800 3850
Connection ~ 7800 4500
$Comp
L power:+3.3V #PWR019
U 1 1 61C91B56
P 7800 3850
F 0 "#PWR019" H 7800 3700 50  0001 C CNN
F 1 "+3.3V" H 7815 4023 50  0000 C CNN
F 2 "" H 7800 3850 50  0001 C CNN
F 3 "" H 7800 3850 50  0001 C CNN
	1    7800 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 61C92187
P 7200 5650
F 0 "#PWR018" H 7200 5400 50  0001 C CNN
F 1 "GND" H 7205 5477 50  0000 C CNN
F 2 "" H 7200 5650 50  0001 C CNN
F 3 "" H 7200 5650 50  0001 C CNN
	1    7200 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3350 4200 3350
Wire Wire Line
	4200 3450 5650 3450
Wire Wire Line
	5650 3550 4200 3550
Wire Wire Line
	4200 3650 5650 3650
Wire Wire Line
	2300 5700 1900 5700
Wire Wire Line
	700  5000 700  5100
Wire Wire Line
	1850 5000 2300 5000
$Comp
L power:+3.3V #PWR013
U 1 1 61E5B0E9
P 2300 5000
F 0 "#PWR013" H 2300 4850 50  0001 C CNN
F 1 "+3.3V" V 2315 5128 50  0000 L CNN
F 2 "" H 2300 5000 50  0001 C CNN
F 3 "" H 2300 5000 50  0001 C CNN
	1    2300 5000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 61E5B4C7
P 700 5100
F 0 "#PWR01" H 700 4850 50  0001 C CNN
F 1 "GND" H 705 4927 50  0000 C CNN
F 2 "" H 700 5100 50  0001 C CNN
F 3 "" H 700 5100 50  0001 C CNN
	1    700  5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  5000 1350 5000
Wire Wire Line
	3000 6800 2650 6800
Wire Wire Line
	2650 6900 3000 6900
Wire Wire Line
	3000 7000 2650 7000
$Sheet
S 3000 950  1200 6200
U 61044A6A
F0 "RX72T" 50
F1 "RX72T.sch" 50
F2 "RESn" B R 4200 6400 50 
F3 "EMLE" B R 4200 6800 50 
F4 "MD_FINED" B R 4200 6700 50 
F5 "VCC_USB" U L 3000 6400 50 
F6 "VSS_USB" U L 3000 6500 50 
F7 "USB_DP" B L 3000 6600 50 
F8 "USB_DM" B L 3000 6700 50 
F9 "P30_SSL0" O R 4200 1400 50 
F10 "P31_SSL1" O R 4200 1500 50 
F11 "PB1_SCL" B R 4200 2550 50 
F12 "PB2_SDA" B R 4200 2650 50 
F13 "P71_GTIOC0A" B L 3000 1200 50 
F14 "P74_GTIOC0B" B L 3000 1500 50 
F15 "P72_GTIOC1A" B L 3000 1300 50 
F16 "P75_GTIOC1B" B L 3000 1600 50 
F17 "P73_GTIOC2A" B L 3000 1400 50 
F18 "P76_GTIOC2B" B L 3000 1700 50 
F19 "P95_GTIOC4A" B L 3000 2400 50 
F20 "P92_GTIOC4B" B L 3000 2000 50 
F21 "P94_GTIOC5A" B L 3000 2300 50 
F22 "P91_GTIOC5B" B L 3000 2100 50 
F23 "P90_GTIOC6B" B L 3000 1900 50 
F24 "P93_GTIOC6A" B L 3000 2200 50 
F25 "P70" B L 3000 1100 50 
F26 "P96" B L 3000 2500 50 
F27 "PE1" B R 4200 4450 50 
F28 "PE2" B R 4200 4550 50 
F29 "PE3" B R 4200 4650 50 
F30 "PE4" B R 4200 4750 50 
F31 "PE5" B R 4200 4850 50 
F32 "P40_AN000" B L 3000 2700 50 
F33 "P41_AN001" B L 3000 2800 50 
F34 "P42_AN002" B L 3000 2900 50 
F35 "P43_AN003" B L 3000 3000 50 
F36 "P44_AN100" B L 3000 3100 50 
F37 "P45_AN101" B L 3000 3200 50 
F38 "P46_AN102" B L 3000 3300 50 
F39 "P47_AN103" B L 3000 3400 50 
F40 "PB3" B R 4200 3450 50 
F41 "PB0" B R 4200 3350 50 
F42 "P80" B L 3000 5300 50 
F43 "P81" B L 3000 5400 50 
F44 "P82" B L 3000 5500 50 
F45 "P20_RSPCK" O R 4200 1100 50 
F46 "P21_MOSI" O R 4200 1200 50 
F47 "P22_MISO" I R 4200 1300 50 
F48 "PD6_TMS" O R 4200 5950 50 
F49 "PD5_TDI" I R 4200 6150 50 
F50 "PD4_TCK" O R 4200 5850 50 
F51 "PD3_TDO" O R 4200 6250 50 
F52 "P00_UB" B R 4200 6600 50 
F53 "PH0" B L 3000 5700 50 
F54 "PH4" B L 3000 5800 50 
F55 "P60" B L 3000 4600 50 
F56 "P61" B L 3000 4700 50 
F57 "P62" B L 3000 4800 50 
F58 "P63" B L 3000 4900 50 
F59 "P64_DA0" B L 3000 5000 50 
F60 "P65_DA1" B L 3000 5100 50 
F61 "P52" B R 4200 3850 50 
F62 "P53" B R 4200 3950 50 
F63 "P54" B R 4200 4050 50 
F64 "P55" B R 4200 4150 50 
F65 "P10" B L 3000 3900 50 
F66 "P11" B L 3000 4000 50 
F67 "P23" B L 3000 4200 50 
F68 "P24" B L 3000 4300 50 
F69 "P27" B L 3000 4400 50 
F70 "P32" B R 4200 3550 50 
F71 "P33" B R 4200 3650 50 
F72 "PA3_SCK8" B R 4200 3250 50 
F73 "PA4_TXD8" B R 4200 3150 50 
F74 "PA5_RXD8" B R 4200 3050 50 
F75 "PB6_USB_OVRCUR" O L 3000 6800 50 
F76 "PB5_USB_VBUSEN" O L 3000 6900 50 
F77 "PD2_USB_VBUS" B L 3000 7000 50 
F78 "PB4" O R 4200 1700 50 
F79 "PA0_TXD11" O R 4200 2850 50 
F80 "PA1_RXD11" I R 4200 2750 50 
F81 "PD7_TRSTn_CTX" I R 4200 6050 50 
F82 "PE0_CRX" B R 4200 4350 50 
F83 "PA2_SCK11" B R 4200 2950 50 
$EndSheet
Wire Wire Line
	5650 1700 4200 1700
Wire Bus Line
	6850 4000 8050 4000
Wire Wire Line
	4200 2750 5650 2750
Wire Wire Line
	4200 2850 5650 2850
Wire Wire Line
	4200 2950 5150 2950
Wire Wire Line
	7300 2950 7000 2950
Wire Wire Line
	7300 3050 7000 3050
Text Label 7000 3050 0    50   ~ 0
PE0
Text Label 7000 2950 0    50   ~ 0
PD7
Entry Wire Line
	6900 3050 7000 2950
Entry Wire Line
	6900 3150 7000 3050
Wire Bus Line
	6900 3950 6850 4000
Wire Wire Line
	4200 6150 5600 6150
Wire Wire Line
	4200 6250 5700 6250
Wire Wire Line
	5650 1600 5150 1600
Wire Wire Line
	5150 1600 5150 2950
Connection ~ 5150 2950
Wire Wire Line
	5150 2950 5650 2950
Wire Wire Line
	850  1250 1350 1250
Wire Wire Line
	850  2450 1350 2450
Wire Wire Line
	1850 2450 2400 2450
Wire Wire Line
	1850 1250 2400 1250
Wire Wire Line
	1850 2650 2300 2650
Wire Wire Line
	1900 1450 2300 1450
Wire Bus Line
	6900 3050 6900 3950
Wire Bus Line
	6900 5100 6900 5450
Wire Bus Line
	8100 5100 8100 5450
Wire Bus Line
	8100 4050 8100 4700
Wire Bus Line
	6900 4050 6900 4700
Wire Bus Line
	2200 4100 2200 6000
Wire Bus Line
	6500 4600 6500 5450
Wire Bus Line
	1000 1150 1000 3550
Wire Bus Line
	2200 1150 2200 3550
Wire Bus Line
	1000 4100 1000 6000
Wire Bus Line
	4600 3950 4600 5000
Wire Bus Line
	2650 1200 2650 3550
Wire Bus Line
	2650 4000 2650 6000
$Comp
L akizuki:Hole H1
U 1 1 611A8923
P 7350 950
F 0 "H1" H 7379 1018 50  0000 L CNN
F 1 "Hole" H 7379 927 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 7350 900 50  0001 C CNN
F 3 "" H 7350 900 50  0001 C CNN
	1    7350 950 
	1    0    0    -1  
$EndComp
$Comp
L akizuki:Hole H2
U 1 1 611A8C8B
P 7350 1300
F 0 "H2" H 7379 1368 50  0000 L CNN
F 1 "Hole" H 7379 1277 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 7350 1250 50  0001 C CNN
F 3 "" H 7350 1250 50  0001 C CNN
	1    7350 1300
	1    0    0    -1  
$EndComp
$Comp
L akizuki:Hole H3
U 1 1 611A9048
P 7900 950
F 0 "H3" H 7929 1018 50  0000 L CNN
F 1 "Hole" H 7929 927 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 7900 900 50  0001 C CNN
F 3 "" H 7900 900 50  0001 C CNN
	1    7900 950 
	1    0    0    -1  
$EndComp
$Comp
L akizuki:Hole H4
U 1 1 611A9395
P 7900 1300
F 0 "H4" H 7929 1368 50  0000 L CNN
F 1 "Hole" H 7929 1277 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 7900 1250 50  0001 C CNN
F 3 "" H 7900 1250 50  0001 C CNN
	1    7900 1300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
