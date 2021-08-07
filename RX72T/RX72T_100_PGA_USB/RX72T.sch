EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 8
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
L renesas:RX72T_100_PGA_USB U6
U 1 1 61044B29
P 4400 6150
F 0 "U6" H 4400 6665 50  0000 C CNN
F 1 "RX72T_100_PGA_USB" H 4400 6574 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 4450 3950 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 4850 6150 50  0001 C CNN
	1    4400 6150
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U6
U 2 1 6104B1A9
P 4400 3150
F 0 "U6" H 4400 5365 50  0000 C CNN
F 1 "RX72T_100_PGA_USB" H 4400 5274 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 4450 950 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 4850 3150 50  0001 C CNN
	2    4400 3150
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U6
U 3 1 6104CDE3
P 6900 3150
F 0 "U6" H 6900 5365 50  0000 C CNN
F 1 "RX72T_100_PGA_USB" H 6900 5274 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 6950 950 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 7350 3150 50  0001 C CNN
	3    6900 3150
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U6
U 4 1 610504F8
P 1950 4050
F 0 "U6" H 2378 4071 50  0000 L CNN
F 1 "RX72T_100_PGA_USB" H 2378 3980 50  0000 L CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 2000 1850 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 2400 4050 50  0001 C CNN
	4    1950 4050
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U6
U 5 1 6105436B
P 1950 1850
F 0 "U6" H 2378 1896 50  0000 L CNN
F 1 "RX72T_100_PGA_USB" H 2378 1805 50  0000 L CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 2000 -350 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 2400 1850 50  0001 C CNN
	5    1950 1850
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U6
U 6 1 6105BF51
P 9650 3500
F 0 "U6" H 10278 3571 50  0000 L CNN
F 1 "RX72T_100_PGA_USB" H 10278 3480 50  0000 L CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 9700 1300 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 10100 3500 50  0001 C CNN
	6    9650 3500
	1    0    0    -1  
$EndComp
Text HLabel 6300 3300 0    50   Output ~ 0
PA0_TXD11
Text HLabel 6300 3400 0    50   Input ~ 0
PA1_RXD11
Text HLabel 3800 3300 0    50   Output ~ 0
P20_RSPCK
Text HLabel 3800 3400 0    50   Output ~ 0
P21_MOSI
Text HLabel 3800 3500 0    50   Input ~ 0
P22_MISO
Text HLabel 3800 4300 0    50   Output ~ 0
P30_SSL0
Text HLabel 3800 4400 0    50   Output ~ 0
P31_SSL1
Text HLabel 6300 4400 0    50   BiDi ~ 0
PB1_SCL
Text HLabel 6300 4500 0    50   BiDi ~ 0
PB2_SDA
Wire Wire Line
	9150 4350 9150 4600
Wire Wire Line
	9150 4600 9250 4600
Wire Wire Line
	9450 4600 9450 4350
Wire Wire Line
	9350 4350 9350 4600
Connection ~ 9350 4600
Wire Wire Line
	9350 4600 9450 4600
Wire Wire Line
	9250 4350 9250 4600
Connection ~ 9250 4600
Wire Wire Line
	9250 4600 9350 4600
Wire Wire Line
	9150 4600 9150 4750
Connection ~ 9150 4600
$Comp
L power:GND #PWR088
U 1 1 61068AD5
P 9150 4750
F 0 "#PWR088" H 9150 4500 50  0001 C CNN
F 1 "GND" H 9155 4577 50  0000 C CNN
F 2 "" H 9150 4750 50  0001 C CNN
F 3 "" H 9150 4750 50  0001 C CNN
	1    9150 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 2600 9550 2250
Wire Wire Line
	9550 2250 9450 2250
Wire Wire Line
	9250 2250 9250 2600
Wire Wire Line
	9350 2600 9350 2250
Connection ~ 9350 2250
Wire Wire Line
	9350 2250 9250 2250
Wire Wire Line
	9450 2600 9450 2250
Connection ~ 9450 2250
Wire Wire Line
	9450 2250 9350 2250
Wire Wire Line
	9250 2250 9250 2150
Connection ~ 9250 2250
$Comp
L power:+3.3V #PWR089
U 1 1 6106AC36
P 9250 2150
F 0 "#PWR089" H 9250 2000 50  0001 C CNN
F 1 "+3.3V" H 9265 2323 50  0000 C CNN
F 2 "" H 9250 2150 50  0001 C CNN
F 3 "" H 9250 2150 50  0001 C CNN
	1    9250 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 2600 9850 2250
Wire Wire Line
	9850 2250 9950 2250
Wire Wire Line
	10050 2250 10050 2600
Wire Wire Line
	9950 2600 9950 2250
Connection ~ 9950 2250
Wire Wire Line
	9950 2250 10050 2250
Wire Wire Line
	9850 4350 9850 4600
Wire Wire Line
	9850 4600 9950 4600
Wire Wire Line
	10050 4600 10050 4350
Wire Wire Line
	9950 4600 9950 4350
Connection ~ 9950 4600
Wire Wire Line
	9950 4600 10050 4600
Wire Wire Line
	9950 4600 9950 4750
$Comp
L power:GNDA #PWR093
U 1 1 6106E9A2
P 9950 4750
F 0 "#PWR093" H 9950 4500 50  0001 C CNN
F 1 "GNDA" H 9955 4577 50  0000 C CNN
F 2 "" H 9950 4750 50  0001 C CNN
F 3 "" H 9950 4750 50  0001 C CNN
	1    9950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 2250 9950 2150
$Comp
L power:+3.3VA #PWR092
U 1 1 6106F4A9
P 9950 2150
F 0 "#PWR092" H 9950 2000 50  0001 C CNN
F 1 "+3.3VA" H 9965 2323 50  0000 C CNN
F 2 "" H 9950 2150 50  0001 C CNN
F 3 "" H 9950 2150 50  0001 C CNN
	1    9950 2150
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C22
U 1 1 610705E1
P 8600 3900
F 0 "C22" H 8682 3953 60  0000 L CNN
F 1 "0.47uF" H 8682 3847 60  0000 L CNN
F 2 "" V 8600 3900 60  0000 C CNN
F 3 "" V 8600 3900 60  0000 C CNN
	1    8600 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 3750 8600 3500
Wire Wire Line
	8600 3500 8850 3500
Wire Wire Line
	8600 4050 8600 4400
$Comp
L power:GND #PWR085
U 1 1 61073BB3
P 8600 4400
F 0 "#PWR085" H 8600 4150 50  0001 C CNN
F 1 "GND" H 8605 4227 50  0000 C CNN
F 2 "" H 8600 4400 50  0001 C CNN
F 3 "" H 8600 4400 50  0001 C CNN
	1    8600 4400
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C23
U 1 1 6107454C
P 8800 1350
F 0 "C23" H 8883 1403 60  0000 L CNN
F 1 "104" H 8883 1297 60  0000 L CNN
F 2 "" V 8800 1350 60  0000 C CNN
F 3 "" V 8800 1350 60  0000 C CNN
	1    8800 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C24
U 1 1 61074C76
P 9150 1350
F 0 "C24" H 9233 1403 60  0000 L CNN
F 1 "104" H 9233 1297 60  0000 L CNN
F 2 "" V 9150 1350 60  0000 C CNN
F 3 "" V 9150 1350 60  0000 C CNN
	1    9150 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C26
U 1 1 6107532A
P 9500 1350
F 0 "C26" H 9583 1403 60  0000 L CNN
F 1 "104" H 9583 1297 60  0000 L CNN
F 2 "" V 9500 1350 60  0000 C CNN
F 3 "" V 9500 1350 60  0000 C CNN
	1    9500 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C28
U 1 1 61075A96
P 9850 1350
F 0 "C28" H 9933 1403 60  0000 L CNN
F 1 "104" H 9933 1297 60  0000 L CNN
F 2 "" V 9850 1350 60  0000 C CNN
F 3 "" V 9850 1350 60  0000 C CNN
	1    9850 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CP C30
U 1 1 610767BA
P 10250 1350
F 0 "C30" H 10333 1403 60  0000 L CNN
F 1 "47uF" H 10333 1297 60  0000 L CNN
F 2 "" V 10250 1350 60  0000 C CNN
F 3 "" V 10250 1350 60  0000 C CNN
	1    10250 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 1200 8800 1050
Wire Wire Line
	8800 1050 9150 1050
Wire Wire Line
	9150 1050 9150 1200
Wire Wire Line
	9150 1050 9500 1050
Wire Wire Line
	9500 1050 9500 1200
Connection ~ 9150 1050
Wire Wire Line
	9500 1050 9850 1050
Wire Wire Line
	9850 1050 9850 1200
Connection ~ 9500 1050
Wire Wire Line
	9850 1050 10250 1050
Wire Wire Line
	10250 1050 10250 1200
Connection ~ 9850 1050
Wire Wire Line
	8800 1500 8800 1650
Wire Wire Line
	8800 1650 9150 1650
Wire Wire Line
	9150 1650 9150 1500
Wire Wire Line
	9150 1650 9500 1650
Wire Wire Line
	9500 1650 9500 1500
Connection ~ 9150 1650
Wire Wire Line
	9500 1650 9850 1650
Wire Wire Line
	9850 1650 9850 1500
Connection ~ 9500 1650
Wire Wire Line
	9850 1650 10250 1650
Wire Wire Line
	10250 1650 10250 1500
Connection ~ 9850 1650
Wire Wire Line
	8800 1650 8800 1800
Connection ~ 8800 1650
Wire Wire Line
	8800 1050 8800 900 
Connection ~ 8800 1050
$Comp
L power:GND #PWR087
U 1 1 6108508C
P 8800 1800
F 0 "#PWR087" H 8800 1550 50  0001 C CNN
F 1 "GND" H 8805 1627 50  0000 C CNN
F 2 "" H 8800 1800 50  0001 C CNN
F 3 "" H 8800 1800 50  0001 C CNN
	1    8800 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR086
U 1 1 61085D24
P 8800 900
F 0 "#PWR086" H 8800 750 50  0001 C CNN
F 1 "+3.3V" H 8815 1073 50  0000 C CNN
F 2 "" H 8800 900 50  0001 C CNN
F 3 "" H 8800 900 50  0001 C CNN
	1    8800 900 
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C25
U 1 1 61089D5D
P 9400 5650
F 0 "C25" H 9483 5703 60  0000 L CNN
F 1 "104" H 9483 5597 60  0000 L CNN
F 2 "" V 9400 5650 60  0000 C CNN
F 3 "" V 9400 5650 60  0000 C CNN
	1    9400 5650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C27
U 1 1 6108AEB0
P 9800 5650
F 0 "C27" H 9883 5703 60  0000 L CNN
F 1 "104" H 9883 5597 60  0000 L CNN
F 2 "" V 9800 5650 60  0000 C CNN
F 3 "" V 9800 5650 60  0000 C CNN
	1    9800 5650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C29
U 1 1 6108AF83
P 10200 5650
F 0 "C29" H 10283 5703 60  0000 L CNN
F 1 "104" H 10283 5597 60  0000 L CNN
F 2 "" V 10200 5650 60  0000 C CNN
F 3 "" V 10200 5650 60  0000 C CNN
	1    10200 5650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CP C31
U 1 1 6108BB24
P 10600 5650
F 0 "C31" H 10683 5703 60  0000 L CNN
F 1 "47uF" H 10683 5597 60  0000 L CNN
F 2 "" V 10600 5650 60  0000 C CNN
F 3 "" V 10600 5650 60  0000 C CNN
	1    10600 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 5500 9400 5350
Wire Wire Line
	9400 5350 9800 5350
Wire Wire Line
	9800 5350 9800 5500
Wire Wire Line
	9800 5350 10200 5350
Wire Wire Line
	10200 5350 10200 5500
Connection ~ 9800 5350
Wire Wire Line
	10200 5350 10600 5350
Wire Wire Line
	10600 5350 10600 5500
Connection ~ 10200 5350
Wire Wire Line
	9400 5800 9400 6000
Wire Wire Line
	9400 6000 9800 6000
Wire Wire Line
	9800 6000 9800 5800
Wire Wire Line
	9800 6000 10200 6000
Wire Wire Line
	10200 6000 10200 5800
Connection ~ 9800 6000
Wire Wire Line
	10200 6000 10600 6000
Wire Wire Line
	10600 6000 10600 5800
Connection ~ 10200 6000
Wire Wire Line
	9400 6000 9400 6150
Connection ~ 9400 6000
$Comp
L power:GNDA #PWR091
U 1 1 610A221C
P 9400 6150
F 0 "#PWR091" H 9400 5900 50  0001 C CNN
F 1 "GNDA" H 9405 5977 50  0000 C CNN
F 2 "" H 9400 6150 50  0001 C CNN
F 3 "" H 9400 6150 50  0001 C CNN
	1    9400 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 5350 9400 5200
Connection ~ 9400 5350
$Comp
L power:+3.3VA #PWR090
U 1 1 610A448A
P 9400 5200
F 0 "#PWR090" H 9400 5050 50  0001 C CNN
F 1 "+3.3VA" H 9415 5373 50  0000 C CNN
F 2 "" H 9400 5200 50  0001 C CNN
F 3 "" H 9400 5200 50  0001 C CNN
	1    9400 5200
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CRYSTAL X1
U 1 1 610CB66A
P 5450 6050
F 0 "X1" V 5193 6050 60  0000 C CNN
F 1 "16MHz" V 5299 6050 60  0000 C CNN
F 2 "" V 5450 6050 60  0000 C CNN
F 3 "" V 5450 6050 60  0000 C CNN
	1    5450 6050
	0    1    1    0   
$EndComp
Wire Wire Line
	5300 6050 5150 6050
Wire Wire Line
	5000 6250 5850 6250
Wire Wire Line
	5850 6250 5850 6050
Wire Wire Line
	5850 6050 5600 6050
Wire Wire Line
	5150 6050 5150 6450
Connection ~ 5150 6050
Wire Wire Line
	5150 6050 5000 6050
Wire Wire Line
	5850 6250 5850 6450
Connection ~ 5850 6250
$Comp
L akizuki:C C20
U 1 1 610DC851
P 5150 6600
F 0 "C20" H 5233 6653 60  0000 L CNN
F 1 "8pF" H 5233 6547 60  0000 L CNN
F 2 "" V 5150 6600 60  0000 C CNN
F 3 "" V 5150 6600 60  0000 C CNN
	1    5150 6600
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C21
U 1 1 610DD5AB
P 5850 6600
F 0 "C21" H 5933 6653 60  0000 L CNN
F 1 "8pF" H 5933 6547 60  0000 L CNN
F 2 "" V 5850 6600 60  0000 C CNN
F 3 "" V 5850 6600 60  0000 C CNN
	1    5850 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 6750 5150 6900
Wire Wire Line
	5150 6900 5850 6900
Wire Wire Line
	5850 6900 5850 6750
Wire Wire Line
	5150 6900 5150 7050
Connection ~ 5150 6900
$Comp
L power:GND #PWR084
U 1 1 610E2C25
P 5150 7050
F 0 "#PWR084" H 5150 6800 50  0001 C CNN
F 1 "GND" H 5155 6877 50  0000 C CNN
F 2 "" H 5150 7050 50  0001 C CNN
F 3 "" H 5150 7050 50  0001 C CNN
	1    5150 7050
	1    0    0    -1  
$EndComp
Text HLabel 3350 6000 0    50   Input ~ 0
RESn
Text HLabel 3350 6150 0    50   BiDi ~ 0
EMLE
Text HLabel 3350 6300 0    50   BiDi ~ 0
MD_FINED
$Comp
L akizuki:2P-SW SW2
U 1 1 610EBEFE
P 3900 6950
F 0 "SW2" H 3900 7287 60  0000 C CNN
F 1 "RESET" H 3900 7181 60  0000 C CNN
F 2 "" H 3905 6950 60  0000 C CNN
F 3 "" H 3905 6950 60  0000 C CNN
	1    3900 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 6950 3500 6950
Wire Wire Line
	4150 6950 4350 6950
Wire Wire Line
	4350 6950 4350 7150
$Comp
L power:GND #PWR083
U 1 1 610F2F6B
P 4350 7150
F 0 "#PWR083" H 4350 6900 50  0001 C CNN
F 1 "GND" H 4355 6977 50  0000 C CNN
F 2 "" H 4350 7150 50  0001 C CNN
F 3 "" H 4350 7150 50  0001 C CNN
	1    4350 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 6000 3500 6000
Wire Wire Line
	3500 6950 3500 6000
Connection ~ 3500 6000
Wire Wire Line
	3500 6000 3800 6000
Wire Wire Line
	3350 6300 3800 6300
Wire Wire Line
	3350 6150 3800 6150
Wire Wire Line
	7500 4000 7750 4000
Text HLabel 7750 4000 2    50   Input ~ 0
PD7_TRSTn_CTX
Wire Wire Line
	7500 3900 7750 3900
Text HLabel 7750 3900 2    50   Output ~ 0
PD6_TMS
Wire Wire Line
	7500 3800 7750 3800
Wire Wire Line
	7500 3700 7750 3700
Wire Wire Line
	7500 3600 7750 3600
Wire Wire Line
	7500 3500 7750 3500
Text HLabel 7750 3800 2    50   Input ~ 0
PD5_TDI
Text HLabel 7750 3700 2    50   Output ~ 0
PD4_TCK
Text HLabel 7750 3600 2    50   Output ~ 0
PD3_TDO
Text HLabel 3800 1300 0    50   BiDi ~ 0
P00_UB
Text HLabel 1350 1500 0    50   UnSpc ~ 0
VCC_USB
Text HLabel 1350 2200 0    50   UnSpc ~ 0
VSS_USB
Text HLabel 1350 1800 0    50   BiDi ~ 0
USB_DP
Text HLabel 1350 1900 0    50   BiDi ~ 0
USB_DM
Text HLabel 6300 4900 0    50   Output ~ 0
PB6_USB_OVRCUR
Text HLabel 6300 4800 0    50   Output ~ 0
PB5_USB_VBUSEN
Text HLabel 6300 4700 0    50   Output ~ 0
PB4
Text HLabel 5000 1400 2    50   BiDi ~ 0
P71_GTIOC0A
Text HLabel 5000 1700 2    50   BiDi ~ 0
P74_GTIOC0B
Text HLabel 5000 1500 2    50   BiDi ~ 0
P72_GTIOC1A
Text HLabel 5000 1800 2    50   BiDi ~ 0
P75_GTIOC1B
Text HLabel 5000 1600 2    50   BiDi ~ 0
P73_GTIOC2A
Text HLabel 5000 1900 2    50   BiDi ~ 0
P76_GTIOC2B
Text HLabel 6300 2750 0    50   BiDi ~ 0
P95_GTIOC4A
Text HLabel 6300 2450 0    50   BiDi ~ 0
P92_GTIOC4B
Text HLabel 6300 2650 0    50   BiDi ~ 0
P94_GTIOC5A
Text HLabel 6300 2350 0    50   BiDi ~ 0
P91_GTIOC5B
Text HLabel 6300 2250 0    50   BiDi ~ 0
P90_GTIOC6B
Text HLabel 6300 2550 0    50   BiDi ~ 0
P93_GTIOC6A
$Comp
L akizuki:R R28
U 1 1 61122A3E
P 2650 1050
F 0 "R28" V 2604 1120 50  0000 L CNN
F 1 "1.5K" V 2695 1120 50  0000 L CNN
F 2 "" H 2650 980 50  0000 C CNN
F 3 "" V 2650 1050 50  0000 C CNN
	1    2650 1050
	0    1    1    0   
$EndComp
$Comp
L Device:LED D3
U 1 1 61124587
P 3000 1400
F 0 "D3" H 2993 1145 50  0000 C CNN
F 1 "RED" H 2993 1236 50  0000 C CNN
F 2 "" H 3000 1400 50  0001 C CNN
F 3 "~" H 3000 1400 50  0001 C CNN
	1    3000 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 1400 3800 1400
Wire Wire Line
	2850 1400 2650 1400
Wire Wire Line
	2650 1400 2650 1200
Wire Wire Line
	2650 900  2650 750 
$Comp
L power:+3.3V #PWR082
U 1 1 61131B4D
P 2650 750
F 0 "#PWR082" H 2650 600 50  0001 C CNN
F 1 "+3.3V" H 2665 923 50  0000 C CNN
F 2 "" H 2650 750 50  0001 C CNN
F 3 "" H 2650 750 50  0001 C CNN
	1    2650 750 
	1    0    0    -1  
$EndComp
Text HLabel 5000 1300 2    50   BiDi ~ 0
P70
Text HLabel 6300 2850 0    50   BiDi ~ 0
P96
Text HLabel 7500 2250 2    50   BiDi ~ 0
PE0_CRX
Text HLabel 7500 2350 2    50   BiDi ~ 0
PE1
Text HLabel 7500 2450 2    50   BiDi ~ 0
PE2
Text HLabel 7500 2550 2    50   BiDi ~ 0
PE3
Text HLabel 7500 2650 2    50   BiDi ~ 0
PE4
Text HLabel 7500 2750 2    50   BiDi ~ 0
PE5
Text HLabel 5000 4300 2    50   BiDi ~ 0
P40_AN000
Text HLabel 5000 4400 2    50   BiDi ~ 0
P41_AN001
Text HLabel 5000 4500 2    50   BiDi ~ 0
P42_AN002
Text HLabel 5000 4600 2    50   BiDi ~ 0
P43_AN003
Text HLabel 5000 4700 2    50   BiDi ~ 0
P44_AN100
Text HLabel 5000 4800 2    50   BiDi ~ 0
P45_AN101
Text HLabel 5000 4900 2    50   BiDi ~ 0
P46_AN102
Text HLabel 5000 5000 2    50   BiDi ~ 0
P47_AN103
Text HLabel 6300 4600 0    50   BiDi ~ 0
PB3
Text HLabel 6300 4300 0    50   BiDi ~ 0
PB0
Text HLabel 6300 1300 0    50   BiDi ~ 0
P80
Text HLabel 6300 1400 0    50   BiDi ~ 0
P81
Text HLabel 6300 1500 0    50   BiDi ~ 0
P82
Text HLabel 1350 3350 0    50   BiDi ~ 0
PH0
Text HLabel 1350 3750 0    50   BiDi ~ 0
PH4
Text HLabel 5000 2300 2    50   BiDi ~ 0
P60
Text HLabel 5000 2400 2    50   BiDi ~ 0
P61
Text HLabel 5000 2500 2    50   BiDi ~ 0
P62
Text HLabel 5000 2600 2    50   BiDi ~ 0
P63
Text HLabel 5000 2700 2    50   BiDi ~ 0
P64_DA0
Text HLabel 5000 2800 2    50   BiDi ~ 0
P65_DA1
Text HLabel 5000 3500 2    50   BiDi ~ 0
P52
Text HLabel 5000 3600 2    50   BiDi ~ 0
P53
Text HLabel 5000 3700 2    50   BiDi ~ 0
P54
Text HLabel 5000 3800 2    50   BiDi ~ 0
P55
Text HLabel 7750 3500 2    50   BiDi ~ 0
PD2_USB_VBUS
Text HLabel 3800 2300 0    50   BiDi ~ 0
P10
Text HLabel 3800 2400 0    50   BiDi ~ 0
P11
Text HLabel 3800 3600 0    50   BiDi ~ 0
P23
Text HLabel 3800 3700 0    50   BiDi ~ 0
P24
Text HLabel 3800 4000 0    50   BiDi ~ 0
P27
Text HLabel 3800 4500 0    50   BiDi ~ 0
P32
Text HLabel 3800 4600 0    50   BiDi ~ 0
P33
Text HLabel 6300 3500 0    50   BiDi ~ 0
PA2_SCK11
Text HLabel 6300 3600 0    50   BiDi ~ 0
PA3_SCK8
Text HLabel 6300 3700 0    50   BiDi ~ 0
PA4_TXD8
Text HLabel 6300 3800 0    50   BiDi ~ 0
PA5_RXD8
$EndSCHEMATC
