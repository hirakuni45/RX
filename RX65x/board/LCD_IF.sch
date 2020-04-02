EESchema Schematic File Version 4
LIBS:board-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 9
Title ""
Date ""
Rev ""
Comp "G.P.L."
Comment1 "hira@rvf-rc45.net"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L board-rescue:CAT4238-akizuki-board-rescue U?
U 1 1 5C70ED58
P 3200 1650
F 0 "U?" H 3000 2000 50  0000 C CNN
F 1 "CAT4238" H 3200 1300 50  0000 C CNN
F 2 "" H 3200 1650 50  0001 C CNN
F 3 "https://www.onsemi.jp/pub/Collateral/CAT4238-D.PDF" H 3200 1650 50  0001 C CNN
	1    3200 1650
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:L-akizuki-board-rescue L?
U 1 1 5C72292B
P 3200 1050
F 0 "L?" V 3050 1050 60  0000 C CNN
F 1 "47uF" V 3300 1050 60  0000 C CNN
F 2 "" V 3195 1015 60  0000 C CNN
F 3 "" V 3195 1015 60  0000 C CNN
	1    3200 1050
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 1450 2650 1450
Wire Wire Line
	2650 1450 2650 1050
Wire Wire Line
	2650 1050 3050 1050
Wire Wire Line
	3350 1050 3750 1050
Wire Wire Line
	3750 1050 3750 1450
Wire Wire Line
	3750 1450 3650 1450
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C7229D5
P 3750 2100
F 0 "R?" V 3704 2170 50  0000 L CNN
F 1 "15" V 3795 2170 50  0000 L CNN
F 2 "" H 3750 2030 50  0000 C CNN
F 3 "" V 3750 2100 50  0000 C CNN
	1    3750 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	3750 2250 3750 2350
Wire Wire Line
	3750 2350 2650 2350
Wire Wire Line
	2650 2350 2650 1850
Wire Wire Line
	2650 1850 2750 1850
Wire Wire Line
	3650 1850 3750 1850
Wire Wire Line
	3750 1850 3750 1950
$Comp
L board-rescue:Shotkey-akizuki-board-rescue D?
U 1 1 5C722B2F
P 4000 1050
F 0 "D?" V 3900 1050 60  0000 C CNN
F 1 "RB160M-30TR" V 4100 1200 60  0000 C CNN
F 2 "" V 3995 1015 60  0000 C CNN
F 3 "" V 3995 1015 60  0000 C CNN
	1    4000 1050
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 1050 3750 1050
Connection ~ 3750 1050
Wire Wire Line
	2650 1050 2100 1050
Wire Wire Line
	2100 1050 2100 850 
Connection ~ 2650 1050
$Comp
L power:+3.3V #PWR?
U 1 1 5C722D00
P 2100 850
F 0 "#PWR?" H 2100 700 50  0001 C CNN
F 1 "+3.3V" H 2115 1023 50  0000 C CNN
F 2 "" H 2100 850 50  0001 C CNN
F 3 "" H 2100 850 50  0001 C CNN
	1    2100 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2350 2650 2550
Connection ~ 2650 2350
$Comp
L power:GND #PWR?
U 1 1 5C722E26
P 2650 2550
F 0 "#PWR?" H 2650 2300 50  0001 C CNN
F 1 "GND" H 2655 2377 50  0000 C CNN
F 2 "" H 2650 2550 50  0001 C CNN
F 3 "" H 2650 2550 50  0001 C CNN
	1    2650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1850 4000 1850
Connection ~ 3750 1850
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C72371A
P 4000 2100
F 0 "R?" V 3954 2170 50  0000 L CNN
F 1 "15" V 4045 2170 50  0000 L CNN
F 2 "" H 4000 2030 50  0000 C CNN
F 3 "" V 4000 2100 50  0000 C CNN
	1    4000 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 1950 4000 1850
Connection ~ 4000 1850
Wire Wire Line
	3750 2350 4000 2350
Wire Wire Line
	4000 2350 4000 2250
Connection ~ 3750 2350
$Comp
L board-rescue:C-akizuki-board-rescue C?
U 1 1 5C723AE3
P 2100 2100
F 0 "C?" H 2183 2153 60  0000 L CNN
F 1 "4.7uF" H 2183 2047 60  0000 L CNN
F 2 "" V 2100 2100 60  0000 C CNN
F 3 "" V 2100 2100 60  0000 C CNN
	1    2100 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2350 2650 2350
$Comp
L board-rescue:C-akizuki-board-rescue C?
U 1 1 5C723EED
P 4550 2100
F 0 "C?" H 4632 2153 60  0000 L CNN
F 1 "0.22uF" H 4632 2047 60  0000 L CNN
F 2 "" V 4550 2100 60  0000 C CNN
F 3 "" V 4550 2100 60  0000 C CNN
	1    4550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1950 4550 1050
Wire Wire Line
	4550 1050 4150 1050
Wire Wire Line
	4000 2350 4550 2350
Wire Wire Line
	4550 2350 4550 2250
Connection ~ 4000 2350
Wire Wire Line
	2100 2250 2100 2350
Wire Wire Line
	2100 1950 2100 1050
Connection ~ 2100 1050
Text HLabel 1450 1650 0    50   Input ~ 0
DISPON
Wire Wire Line
	2750 1650 1700 1650
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C7256C7
P 1700 2100
F 0 "R?" V 1654 2170 50  0000 L CNN
F 1 "10K" V 1745 2170 50  0000 L CNN
F 2 "" H 1700 2030 50  0000 C CNN
F 3 "" V 1700 2100 50  0000 C CNN
	1    1700 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 1950 1700 1650
Connection ~ 1700 1650
Wire Wire Line
	1700 1650 1450 1650
Wire Wire Line
	1700 2250 1700 2350
Wire Wire Line
	1700 2350 2100 2350
Connection ~ 2100 2350
$Comp
L board-rescue:LCD_480_272-akizuki-board-rescue J?
U 1 1 5C74788C
P 9150 3800
F 0 "J?" H 9369 3851 50  0000 L CNN
F 1 "LCD_480_272" H 9369 3760 50  0000 L CNN
F 2 "" H 9150 4700 50  0001 C CNN
F 3 "" H 9150 4700 50  0001 C CNN
	1    9150 3800
	1    0    0    -1  
$EndComp
Text Notes 3200 2600 0    50   ~ 0
Back Light LED Current: 20mA -> 15x1, 40mA -> 15x2
Wire Wire Line
	4000 1850 8800 1850
Wire Wire Line
	8800 1950 5350 1950
Wire Wire Line
	5350 1950 5350 1050
Wire Wire Line
	5350 1050 4550 1050
Connection ~ 4550 1050
Text HLabel 1450 3450 0    50   Input ~ 0
LD0
Text HLabel 1450 3550 0    50   Input ~ 0
LD1
Text HLabel 1450 3650 0    50   Input ~ 0
LD2
Text HLabel 1450 3750 0    50   Input ~ 0
LD3
Text HLabel 1450 3850 0    50   Input ~ 0
LD4
Text HLabel 1450 3950 0    50   Input ~ 0
LD5
Text HLabel 1450 4050 0    50   Input ~ 0
LD6
Text HLabel 1450 4150 0    50   Input ~ 0
LD7
Wire Wire Line
	1450 3450 2000 3450
Wire Wire Line
	1450 3550 2000 3550
Wire Wire Line
	1450 3650 2000 3650
Wire Wire Line
	1450 3750 2000 3750
Wire Wire Line
	1450 3850 2000 3850
Wire Wire Line
	1450 3950 2000 3950
Wire Wire Line
	1450 4050 2000 4050
Wire Wire Line
	1450 4150 2000 4150
$Comp
L 74xx:74HCT574 U?
U 1 1 5C74C75D
P 2500 3950
F 0 "U?" H 2250 4600 50  0000 C CNN
F 1 "74HC574" H 2150 3250 50  0000 C CNN
F 2 "" H 2500 3950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HCT574" H 2500 3950 50  0001 C CNN
	1    2500 3950
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HCT574 U?
U 1 1 5C74D18A
P 4300 3950
F 0 "U?" H 4300 4928 50  0000 C CNN
F 1 "74HC574" H 3950 3250 50  0000 C CNN
F 2 "" H 4300 3950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HCT574" H 4300 3950 50  0001 C CNN
	1    4300 3950
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HCT574 U?
U 1 1 5C74D1EA
P 6150 3950
F 0 "U?" H 6150 4928 50  0000 C CNN
F 1 "74HC574" H 5850 3250 50  0000 C CNN
F 2 "" H 6150 3950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HCT574" H 6150 3950 50  0001 C CNN
	1    6150 3950
	1    0    0    -1  
$EndComp
Entry Wire Line
	7500 2350 7600 2250
Entry Wire Line
	7500 2450 7600 2350
Entry Wire Line
	7500 2550 7600 2450
Entry Wire Line
	7500 2650 7600 2550
Entry Wire Line
	7500 2750 7600 2650
Entry Wire Line
	7500 2850 7600 2750
Entry Wire Line
	7500 2950 7600 2850
Entry Wire Line
	7500 3050 7600 2950
Entry Wire Line
	7500 3150 7600 3050
Entry Wire Line
	7500 3250 7600 3150
Entry Wire Line
	7500 3350 7600 3250
Entry Wire Line
	7500 3450 7600 3350
Entry Wire Line
	7500 3550 7600 3450
Entry Wire Line
	7500 3650 7600 3550
Entry Wire Line
	7500 3750 7600 3650
Entry Wire Line
	7500 3850 7600 3750
Entry Wire Line
	7500 3950 7600 3850
Entry Wire Line
	7500 4050 7600 3950
Entry Wire Line
	7500 4150 7600 4050
Entry Wire Line
	7500 4250 7600 4150
Entry Wire Line
	7500 4350 7600 4250
Entry Wire Line
	7500 4450 7600 4350
Entry Wire Line
	7500 4550 7600 4450
Entry Wire Line
	7500 4650 7600 4550
Text Label 7600 2250 0    50   ~ 0
R0
Text Label 7600 2350 0    50   ~ 0
R1
Text Label 7600 2450 0    50   ~ 0
R2
Text Label 7600 2550 0    50   ~ 0
R3
Text Label 7600 2650 0    50   ~ 0
R4
Text Label 7600 2750 0    50   ~ 0
R5
Text Label 7600 2850 0    50   ~ 0
R6
Text Label 7600 2950 0    50   ~ 0
R7
Text Label 7600 3050 0    50   ~ 0
G0
Text Label 7600 3150 0    50   ~ 0
G1
Text Label 7600 3250 0    50   ~ 0
G2
Text Label 7600 3350 0    50   ~ 0
G3
Text Label 7600 3450 0    50   ~ 0
G4
Text Label 7600 3550 0    50   ~ 0
G5
Text Label 7600 3650 0    50   ~ 0
G6
Text Label 7600 3750 0    50   ~ 0
G7
Text Label 7600 3850 0    50   ~ 0
B0
Text Label 7600 3950 0    50   ~ 0
B1
Text Label 7600 4050 0    50   ~ 0
B2
Text Label 7600 4150 0    50   ~ 0
B3
Text Label 7600 4250 0    50   ~ 0
B4
Text Label 7600 4350 0    50   ~ 0
B5
Text Label 7600 4450 0    50   ~ 0
B6
Text Label 7600 4550 0    50   ~ 0
B7
$Comp
L board-rescue:MR-akizuki-board-rescue MR?
U 1 1 5C6B7A71
P 8300 2400
F 0 "MR?" H 8000 2500 50  0000 C CNN
F 1 "22" H 8550 2300 50  0000 C CNN
F 2 "" H 8300 2400 50  0001 C CNN
F 3 "" H 8300 2400 50  0001 C CNN
	1    8300 2400
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:MR-akizuki-board-rescue MR?
U 1 1 5C6B7ACF
P 8300 2800
F 0 "MR?" H 8000 2900 50  0000 C CNN
F 1 "22" H 8550 2700 50  0000 C CNN
F 2 "" H 8300 2800 50  0001 C CNN
F 3 "" H 8300 2800 50  0001 C CNN
	1    8300 2800
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:MR-akizuki-board-rescue MR?
U 1 1 5C6B7B51
P 8300 3200
F 0 "MR?" H 8000 3300 50  0000 C CNN
F 1 "22" H 8550 3100 50  0000 C CNN
F 2 "" H 8300 3200 50  0001 C CNN
F 3 "" H 8300 3200 50  0001 C CNN
	1    8300 3200
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:MR-akizuki-board-rescue MR?
U 1 1 5C6B7BD1
P 8300 3600
F 0 "MR?" H 8000 3700 50  0000 C CNN
F 1 "22" H 8550 3500 50  0000 C CNN
F 2 "" H 8300 3600 50  0001 C CNN
F 3 "" H 8300 3600 50  0001 C CNN
	1    8300 3600
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:MR-akizuki-board-rescue MR?
U 1 1 5C6B7C1D
P 8300 4000
F 0 "MR?" H 8000 4100 50  0000 C CNN
F 1 "22" H 8550 3900 50  0000 C CNN
F 2 "" H 8300 4000 50  0001 C CNN
F 3 "" H 8300 4000 50  0001 C CNN
	1    8300 4000
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:MR-akizuki-board-rescue MR?
U 1 1 5C6B7C95
P 8300 4400
F 0 "MR?" H 8000 4500 50  0000 C CNN
F 1 "22" H 8550 4300 50  0000 C CNN
F 2 "" H 8300 4400 50  0001 C CNN
F 3 "" H 8300 4400 50  0001 C CNN
	1    8300 4400
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:MR-akizuki-board-rescue MR?
U 1 1 5C6B7CE1
P 8300 4900
F 0 "MR?" H 8000 5000 50  0000 C CNN
F 1 "22" H 8550 4800 50  0000 C CNN
F 2 "" H 8300 4900 50  0001 C CNN
F 3 "" H 8300 4900 50  0001 C CNN
	1    8300 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 2250 8800 2250
Wire Wire Line
	8800 2350 8450 2350
Wire Wire Line
	8450 2450 8800 2450
Wire Wire Line
	8800 2550 8450 2550
Wire Wire Line
	8450 2650 8800 2650
Wire Wire Line
	8800 2750 8450 2750
Wire Wire Line
	8450 2850 8800 2850
Wire Wire Line
	8800 2950 8450 2950
Wire Wire Line
	8450 3050 8800 3050
Wire Wire Line
	8800 3150 8450 3150
Wire Wire Line
	8450 3250 8800 3250
Wire Wire Line
	8800 3350 8450 3350
Wire Wire Line
	8450 3450 8800 3450
Wire Wire Line
	8800 3550 8450 3550
Wire Wire Line
	8450 3650 8800 3650
Wire Wire Line
	8800 3750 8450 3750
Wire Wire Line
	8450 3850 8800 3850
Wire Wire Line
	8800 3950 8450 3950
Wire Wire Line
	8450 4050 8800 4050
Wire Wire Line
	8800 4150 8450 4150
Wire Wire Line
	8450 4250 8800 4250
Wire Wire Line
	8800 4350 8450 4350
Wire Wire Line
	8450 4450 8800 4450
Wire Wire Line
	8800 4550 8450 4550
Wire Wire Line
	8450 4750 8800 4750
Wire Wire Line
	8800 4850 8450 4850
Wire Wire Line
	8450 4950 8800 4950
Wire Wire Line
	8800 5050 8450 5050
Wire Wire Line
	8150 2250 7600 2250
Wire Wire Line
	7600 2350 8150 2350
Wire Wire Line
	8150 2450 7600 2450
Wire Wire Line
	7600 2550 8150 2550
Wire Wire Line
	7600 2650 8150 2650
Wire Wire Line
	7600 2750 8150 2750
Wire Wire Line
	8150 2850 7600 2850
Wire Wire Line
	7600 2950 8150 2950
Wire Wire Line
	8150 3050 7600 3050
Wire Wire Line
	7600 3150 8150 3150
Wire Wire Line
	8150 3250 7600 3250
Wire Wire Line
	7600 3350 8150 3350
Wire Wire Line
	8150 3450 7600 3450
Wire Wire Line
	7600 3550 8150 3550
Wire Wire Line
	8150 3650 7600 3650
Wire Wire Line
	7600 3750 8150 3750
Wire Wire Line
	8150 3850 7600 3850
Wire Wire Line
	7600 3950 8150 3950
Wire Wire Line
	8150 4050 7600 4050
Wire Wire Line
	7600 4150 8150 4150
Wire Wire Line
	8150 4250 7600 4250
Wire Wire Line
	7600 4350 8150 4350
Wire Wire Line
	8150 4450 7600 4450
Wire Wire Line
	7600 4550 8150 4550
$Comp
L board-rescue:R-akizuki-board-rescue R?
U 1 1 5C709A63
P 8300 5150
F 0 "R?" H 8000 5100 50  0000 C CNN
F 1 "22" H 8300 5150 50  0000 C CNN
F 2 "" H 8300 5080 50  0000 C CNN
F 3 "" V 8300 5150 50  0000 C CNN
	1    8300 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 5150 8450 5150
$EndSCHEMATC
