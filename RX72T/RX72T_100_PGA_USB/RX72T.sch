EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
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
L renesas:RX72T_100_PGA_USB U?
U 1 1 61044B29
P 4250 6150
F 0 "U?" H 4250 6665 50  0000 C CNN
F 1 "RX72T_100_PGA_USB" H 4250 6574 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 4300 3950 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 4700 6150 50  0001 C CNN
	1    4250 6150
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U?
U 2 1 6104B1A9
P 4200 3150
F 0 "U?" H 4200 5365 50  0000 C CNN
F 1 "RX72T_100_PGA_USB" H 4200 5274 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 4250 950 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 4650 3150 50  0001 C CNN
	2    4200 3150
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U?
U 3 1 6104CDE3
P 6700 3150
F 0 "U?" H 6700 5365 50  0000 C CNN
F 1 "RX72T_100_PGA_USB" H 6700 5274 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 6750 950 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 7150 3150 50  0001 C CNN
	3    6700 3150
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U?
U 4 1 610504F8
P 1700 4050
F 0 "U?" H 2128 4071 50  0000 L CNN
F 1 "RX72T_100_PGA_USB" H 2128 3980 50  0000 L CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 1750 1850 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 2150 4050 50  0001 C CNN
	4    1700 4050
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U?
U 5 1 6105436B
P 1700 1850
F 0 "U?" H 2128 1896 50  0000 L CNN
F 1 "RX72T_100_PGA_USB" H 2128 1805 50  0000 L CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 1750 -350 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 2150 1850 50  0001 C CNN
	5    1700 1850
	1    0    0    -1  
$EndComp
$Comp
L renesas:RX72T_100_PGA_USB U?
U 6 1 6105BF51
P 9650 3500
F 0 "U?" H 10278 3571 50  0000 L CNN
F 1 "RX72T_100_PGA_USB" H 10278 3480 50  0000 L CNN
F 2 "Package_QFP:LQFP-100_20x20mm_P0.5mm" H 9700 1300 50  0001 C CNN
F 3 "https://www.renesas.com/jp/ja/img/products/microcontrollers-microprocessors/rx/rx700/rx72t/r01ds0331ej0100-rx72t.pdf" H 10100 3500 50  0001 C CNN
	6    9650 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3300 5850 3300
Wire Wire Line
	6100 3400 5850 3400
Text HLabel 5850 3300 0    50   Output ~ 0
CTX
Text HLabel 5850 3400 0    50   Input ~ 0
CRX
Wire Wire Line
	3600 3300 3300 3300
Wire Wire Line
	3600 3400 3300 3400
Wire Wire Line
	3600 3500 3300 3500
Text HLabel 3300 3300 0    50   Output ~ 0
RSPCK
Text HLabel 3300 3400 0    50   Output ~ 0
MOSI
Text HLabel 3300 3500 0    50   Input ~ 0
MISO
Wire Wire Line
	3600 4300 3300 4300
Wire Wire Line
	3600 4400 3300 4400
Text HLabel 3300 4300 0    50   Output ~ 0
SSL0
Text HLabel 3300 4400 0    50   Output ~ 0
SSL1
Wire Wire Line
	6100 4400 5850 4400
Wire Wire Line
	6100 4500 5850 4500
Text HLabel 5850 4400 0    50   BiDi ~ 0
SCL
Text HLabel 5850 4500 0    50   BiDi ~ 0
SDA
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
L power:GND #PWR?
U 1 1 61068AD5
P 9150 4750
F 0 "#PWR?" H 9150 4500 50  0001 C CNN
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
L power:+3.3V #PWR?
U 1 1 6106AC36
P 9250 2150
F 0 "#PWR?" H 9250 2000 50  0001 C CNN
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
L power:GNDA #PWR?
U 1 1 6106E9A2
P 9950 4750
F 0 "#PWR?" H 9950 4500 50  0001 C CNN
F 1 "GNDA" H 9955 4577 50  0000 C CNN
F 2 "" H 9950 4750 50  0001 C CNN
F 3 "" H 9950 4750 50  0001 C CNN
	1    9950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 2250 9950 2150
$Comp
L power:+3.3VA #PWR?
U 1 1 6106F4A9
P 9950 2150
F 0 "#PWR?" H 9950 2000 50  0001 C CNN
F 1 "+3.3VA" H 9965 2323 50  0000 C CNN
F 2 "" H 9950 2150 50  0001 C CNN
F 3 "" H 9950 2150 50  0001 C CNN
	1    9950 2150
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 610705E1
P 8600 3900
F 0 "C?" H 8682 3953 60  0000 L CNN
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
L power:GND #PWR?
U 1 1 61073BB3
P 8600 4400
F 0 "#PWR?" H 8600 4150 50  0001 C CNN
F 1 "GND" H 8605 4227 50  0000 C CNN
F 2 "" H 8600 4400 50  0001 C CNN
F 3 "" H 8600 4400 50  0001 C CNN
	1    8600 4400
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 6107454C
P 8800 1350
F 0 "C?" H 8883 1403 60  0000 L CNN
F 1 "104" H 8883 1297 60  0000 L CNN
F 2 "" V 8800 1350 60  0000 C CNN
F 3 "" V 8800 1350 60  0000 C CNN
	1    8800 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 61074C76
P 9150 1350
F 0 "C?" H 9233 1403 60  0000 L CNN
F 1 "104" H 9233 1297 60  0000 L CNN
F 2 "" V 9150 1350 60  0000 C CNN
F 3 "" V 9150 1350 60  0000 C CNN
	1    9150 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 6107532A
P 9500 1350
F 0 "C?" H 9583 1403 60  0000 L CNN
F 1 "104" H 9583 1297 60  0000 L CNN
F 2 "" V 9500 1350 60  0000 C CNN
F 3 "" V 9500 1350 60  0000 C CNN
	1    9500 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 61075A96
P 9850 1350
F 0 "C?" H 9933 1403 60  0000 L CNN
F 1 "104" H 9933 1297 60  0000 L CNN
F 2 "" V 9850 1350 60  0000 C CNN
F 3 "" V 9850 1350 60  0000 C CNN
	1    9850 1350
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CP C?
U 1 1 610767BA
P 10250 1350
F 0 "C?" H 10333 1403 60  0000 L CNN
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
L power:GND #PWR?
U 1 1 6108508C
P 8800 1800
F 0 "#PWR?" H 8800 1550 50  0001 C CNN
F 1 "GND" H 8805 1627 50  0000 C CNN
F 2 "" H 8800 1800 50  0001 C CNN
F 3 "" H 8800 1800 50  0001 C CNN
	1    8800 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61085D24
P 8800 900
F 0 "#PWR?" H 8800 750 50  0001 C CNN
F 1 "+3.3V" H 8815 1073 50  0000 C CNN
F 2 "" H 8800 900 50  0001 C CNN
F 3 "" H 8800 900 50  0001 C CNN
	1    8800 900 
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 61089D5D
P 9400 5650
F 0 "C?" H 9483 5703 60  0000 L CNN
F 1 "104" H 9483 5597 60  0000 L CNN
F 2 "" V 9400 5650 60  0000 C CNN
F 3 "" V 9400 5650 60  0000 C CNN
	1    9400 5650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 6108AEB0
P 9800 5650
F 0 "C?" H 9883 5703 60  0000 L CNN
F 1 "104" H 9883 5597 60  0000 L CNN
F 2 "" V 9800 5650 60  0000 C CNN
F 3 "" V 9800 5650 60  0000 C CNN
	1    9800 5650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 6108AF83
P 10200 5650
F 0 "C?" H 10283 5703 60  0000 L CNN
F 1 "104" H 10283 5597 60  0000 L CNN
F 2 "" V 10200 5650 60  0000 C CNN
F 3 "" V 10200 5650 60  0000 C CNN
	1    10200 5650
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CP C?
U 1 1 6108BB24
P 10600 5650
F 0 "C?" H 10683 5703 60  0000 L CNN
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
L power:GNDA #PWR?
U 1 1 610A221C
P 9400 6150
F 0 "#PWR?" H 9400 5900 50  0001 C CNN
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
L power:+3.3VA #PWR?
U 1 1 610A448A
P 9400 5200
F 0 "#PWR?" H 9400 5050 50  0001 C CNN
F 1 "+3.3VA" H 9415 5373 50  0000 C CNN
F 2 "" H 9400 5200 50  0001 C CNN
F 3 "" H 9400 5200 50  0001 C CNN
	1    9400 5200
	1    0    0    -1  
$EndComp
$Comp
L akizuki:CRYSTAL X?
U 1 1 610CB66A
P 5300 6050
F 0 "X?" V 5043 6050 60  0000 C CNN
F 1 "16MHz" V 5149 6050 60  0000 C CNN
F 2 "" V 5300 6050 60  0000 C CNN
F 3 "" V 5300 6050 60  0000 C CNN
	1    5300 6050
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 6050 5000 6050
Wire Wire Line
	4850 6250 5700 6250
Wire Wire Line
	5700 6250 5700 6050
Wire Wire Line
	5700 6050 5450 6050
Wire Wire Line
	5000 6050 5000 6450
Connection ~ 5000 6050
Wire Wire Line
	5000 6050 4850 6050
Wire Wire Line
	5700 6250 5700 6450
Connection ~ 5700 6250
$Comp
L akizuki:C C?
U 1 1 610DC851
P 5000 6600
F 0 "C?" H 5083 6653 60  0000 L CNN
F 1 "8pF" H 5083 6547 60  0000 L CNN
F 2 "" V 5000 6600 60  0000 C CNN
F 3 "" V 5000 6600 60  0000 C CNN
	1    5000 6600
	1    0    0    -1  
$EndComp
$Comp
L akizuki:C C?
U 1 1 610DD5AB
P 5700 6600
F 0 "C?" H 5783 6653 60  0000 L CNN
F 1 "8pF" H 5783 6547 60  0000 L CNN
F 2 "" V 5700 6600 60  0000 C CNN
F 3 "" V 5700 6600 60  0000 C CNN
	1    5700 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 6750 5000 6900
Wire Wire Line
	5000 6900 5700 6900
Wire Wire Line
	5700 6900 5700 6750
Wire Wire Line
	5000 6900 5000 7050
Connection ~ 5000 6900
$Comp
L power:GND #PWR?
U 1 1 610E2C25
P 5000 7050
F 0 "#PWR?" H 5000 6800 50  0001 C CNN
F 1 "GND" H 5005 6877 50  0000 C CNN
F 2 "" H 5000 7050 50  0001 C CNN
F 3 "" H 5000 7050 50  0001 C CNN
	1    5000 7050
	1    0    0    -1  
$EndComp
Text HLabel 3200 6000 0    50   Input ~ 0
RESn
Text HLabel 3200 6150 0    50   BiDi ~ 0
EMLE
Text HLabel 3200 6300 0    50   BiDi ~ 0
MD_FINED
$Comp
L akizuki:2P-SW SW?
U 1 1 610EBEFE
P 3750 6950
F 0 "SW?" H 3750 7287 60  0000 C CNN
F 1 "RESET" H 3750 7181 60  0000 C CNN
F 2 "" H 3755 6950 60  0000 C CNN
F 3 "" H 3755 6950 60  0000 C CNN
	1    3750 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6950 3350 6950
Wire Wire Line
	4000 6950 4200 6950
Wire Wire Line
	4200 6950 4200 7150
$Comp
L power:GND #PWR?
U 1 1 610F2F6B
P 4200 7150
F 0 "#PWR?" H 4200 6900 50  0001 C CNN
F 1 "GND" H 4205 6977 50  0000 C CNN
F 2 "" H 4200 7150 50  0001 C CNN
F 3 "" H 4200 7150 50  0001 C CNN
	1    4200 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 6000 3350 6000
Wire Wire Line
	3350 6950 3350 6000
Connection ~ 3350 6000
Wire Wire Line
	3350 6000 3650 6000
Wire Wire Line
	3200 6300 3650 6300
Wire Wire Line
	3200 6150 3650 6150
Wire Wire Line
	7300 4000 7550 4000
Text HLabel 7550 4000 2    50   Input ~ 0
TRSTn
Wire Wire Line
	7300 3900 7550 3900
Text HLabel 7550 3900 2    50   Output ~ 0
TMS
Wire Wire Line
	7300 3800 7550 3800
Wire Wire Line
	7300 3700 7550 3700
Wire Wire Line
	7300 3600 7550 3600
Wire Wire Line
	7300 3500 7550 3500
Text HLabel 7550 3800 2    50   Output ~ 0
TDI
Text HLabel 7550 3700 2    50   Output ~ 0
TCK
Text HLabel 7550 3600 2    50   Output ~ 0
TDO
Wire Wire Line
	3600 1300 3250 1300
Text HLabel 3250 1300 0    50   Output ~ 0
UB
$EndSCHEMATC
