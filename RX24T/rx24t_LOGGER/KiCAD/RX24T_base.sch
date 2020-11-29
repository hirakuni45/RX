EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:akizuki
LIBS:analog
LIBS:ftdi
LIBS:renesas
LIBS:MotorLogger-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L RX24T U?
U 1 1 598D66E6
P 5400 3600
F 0 "U?" H 4725 975 60  0000 C CNN
F 1 "RX24T" H 6025 6225 60  0000 C CNN
F 2 "" H 4725 975 60  0000 C CNN
F 3 "" H 4725 975 60  0000 C CNN
	1    5400 3600
	1    0    0    -1  
$EndComp
Text HLabel 3450 3050 0    60   Input ~ 0
RXD1
Text HLabel 3450 3250 0    60   Output ~ 0
TXD1
$Comp
L CRYSTAL X?
U 1 1 598D9363
P 3400 2250
F 0 "X?" V 3550 2250 60  0000 C CNN
F 1 "10MHz" V 3250 2250 60  0000 C CNN
F 2 "" V 3400 2250 60  0000 C CNN
F 3 "" V 3400 2250 60  0000 C CNN
	1    3400 2250
	0    1    1    0   
$EndComp
$Comp
L CAP C?
U 1 1 598D9414
P 2900 2150
F 0 "C?" V 3000 2250 60  0000 C CNN
F 1 "7pF" V 2800 2050 60  0000 C CNN
F 2 "" V 2900 2150 60  0000 C CNN
F 3 "" V 2900 2150 60  0000 C CNN
	1    2900 2150
	0    1    1    0   
$EndComp
$Comp
L CAP C?
U 1 1 598D945D
P 2900 2350
F 0 "C?" V 3000 2450 60  0000 C CNN
F 1 "7pF" V 2800 2250 60  0000 C CNN
F 2 "" V 2900 2350 60  0000 C CNN
F 3 "" V 2900 2350 60  0000 C CNN
	1    2900 2350
	0    1    1    0   
$EndComp
$Comp
L CAP C?
U 1 1 598D9482
P 3450 1550
F 0 "C?" V 3550 1650 60  0000 C CNN
F 1 "0.1uF" V 3350 1450 60  0000 C CNN
F 2 "" V 3450 1550 60  0000 C CNN
F 3 "" V 3450 1550 60  0000 C CNN
	1    3450 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 1550 3600 1550
Wire Wire Line
	2600 1550 3300 1550
$Comp
L GND #PWR?
U 1 1 598D952D
P 2600 2550
F 0 "#PWR?" H 2600 2300 50  0001 C CNN
F 1 "GND" H 2600 2400 50  0000 C CNN
F 2 "" H 2600 2550 50  0000 C CNN
F 3 "" H 2600 2550 50  0000 C CNN
	1    2600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2550 2600 1550
Wire Wire Line
	3050 2150 4450 2150
Wire Wire Line
	3050 2350 4450 2350
Wire Wire Line
	3250 2250 3150 2250
Wire Wire Line
	3150 2250 3150 2150
Connection ~ 3150 2150
Wire Wire Line
	3550 2250 3700 2250
Wire Wire Line
	3700 2250 3700 2350
Connection ~ 3700 2350
Wire Wire Line
	2750 2150 2600 2150
Connection ~ 2600 2150
Wire Wire Line
	2750 2350 2600 2350
Connection ~ 2600 2350
Wire Wire Line
	4450 1350 4300 1350
Wire Wire Line
	4300 1350 4300 6450
Wire Wire Line
	4300 2250 4450 2250
Wire Wire Line
	4300 5450 4450 5450
Connection ~ 4300 2250
Wire Wire Line
	4450 4150 4300 4150
Connection ~ 4300 4150
Connection ~ 4300 5450
$Comp
L GND #PWR?
U 1 1 598D985C
P 4300 6450
F 0 "#PWR?" H 4300 6200 50  0001 C CNN
F 1 "GND" H 4300 6300 50  0000 C CNN
F 2 "" H 4300 6450 50  0000 C CNN
F 3 "" H 4300 6450 50  0000 C CNN
	1    4300 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2450 4100 2450
Wire Wire Line
	4100 3950 4450 3950
Connection ~ 4100 2450
Wire Wire Line
	4100 5250 4450 5250
Connection ~ 4100 3950
$Comp
L +3.3V #PWR?
U 1 1 598D98F6
P 4100 750
F 0 "#PWR?" H 4100 600 50  0001 C CNN
F 1 "+3.3V" H 4100 890 50  0000 C CNN
F 2 "" H 4100 750 50  0000 C CNN
F 3 "" H 4100 750 50  0000 C CNN
	1    4100 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3050 3450 3050
Wire Wire Line
	4450 3250 3450 3250
Wire Wire Line
	6350 1650 6900 1650
Wire Wire Line
	6500 1650 6500 3850
Wire Wire Line
	6500 1750 6350 1750
Wire Wire Line
	6500 3850 6350 3850
Connection ~ 6500 1750
Wire Wire Line
	6350 1850 6600 1850
Wire Wire Line
	6600 1850 6600 4050
Wire Wire Line
	6350 1950 8800 1950
Wire Wire Line
	6600 4050 6350 4050
Connection ~ 6600 1950
Wire Wire Line
	6350 4950 6500 4950
Wire Wire Line
	6500 4950 6500 6450
$Comp
L GND #PWR?
U 1 1 598F554A
P 6500 6450
F 0 "#PWR?" H 6500 6200 50  0001 C CNN
F 1 "GND" H 6500 6300 50  0000 C CNN
F 2 "" H 6500 6450 50  0000 C CNN
F 3 "" H 6500 6450 50  0000 C CNN
	1    6500 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 5150 6700 5150
Connection ~ 4100 5250
Wire Wire Line
	6700 5150 6700 6800
Wire Wire Line
	6700 6800 4100 6800
Wire Wire Line
	4100 6800 4100 750 
Wire Wire Line
	3700 2050 4450 2050
Wire Wire Line
	3700 1000 3700 2050
Wire Wire Line
	3700 1150 2600 1150
$Comp
L 2P-SW SW?
U 1 1 598F56D7
P 2350 1150
F 0 "SW?" H 2400 1350 60  0000 C CNN
F 1 "RESET" H 2300 950 60  0000 C CNN
F 2 "" H 2355 1150 60  0000 C CNN
F 3 "" H 2355 1150 60  0000 C CNN
	1    2350 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1150 2100 1150
$Comp
L GND #PWR?
U 1 1 598F5743
P 1900 2550
F 0 "#PWR?" H 1900 2300 50  0001 C CNN
F 1 "GND" H 1900 2400 50  0000 C CNN
F 2 "" H 1900 2550 50  0000 C CNN
F 3 "" H 1900 2550 50  0000 C CNN
	1    1900 2550
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 598F5763
P 3700 850
F 0 "R?" V 3780 850 50  0000 C CNN
F 1 "10K" V 3700 850 50  0000 C CNN
F 2 "" V 3630 850 50  0000 C CNN
F 3 "" H 3700 850 50  0000 C CNN
	1    3700 850 
	1    0    0    -1  
$EndComp
Connection ~ 3700 1150
Wire Wire Line
	3700 700  3700 600 
Wire Wire Line
	1900 600  3900 600 
Wire Wire Line
	6900 1650 6900 1750
Connection ~ 6500 1650
$Comp
L GNDA #PWR?
U 1 1 598F5BA3
P 6900 1750
F 0 "#PWR?" H 6900 1500 50  0001 C CNN
F 1 "GNDA" H 6900 1600 50  0000 C CNN
F 2 "" H 6900 1750 50  0000 C CNN
F 3 "" H 6900 1750 50  0000 C CNN
	1    6900 1750
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 598F5C4A
P 6500 7400
F 0 "#PWR?" H 6500 7150 50  0001 C CNN
F 1 "GNDA" H 6500 7250 50  0000 C CNN
F 2 "" H 6500 7400 50  0000 C CNN
F 3 "" H 6500 7400 50  0000 C CNN
	1    6500 7400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 598F5C6C
P 6100 7400
F 0 "#PWR?" H 6100 7150 50  0001 C CNN
F 1 "GND" H 6100 7250 50  0000 C CNN
F 2 "" H 6100 7400 50  0000 C CNN
F 3 "" H 6100 7400 50  0000 C CNN
	1    6100 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 7100 6100 7400
Wire Wire Line
	6500 7100 6500 7400
$Comp
L R FB?
U 1 1 598F5FF2
P 8950 1950
F 0 "FB?" V 9050 1950 50  0000 C CNN
F 1 "FB_ADC" V 8850 1950 50  0000 C CNN
F 2 "" V 8880 1950 50  0000 C CNN
F 3 "" H 8950 1950 50  0000 C CNN
	1    8950 1950
	0    1    1    0   
$EndComp
$Comp
L C-POL C?
U 1 1 598F60DF
P 8350 2200
F 0 "C?" H 8450 2300 60  0000 C CNN
F 1 "10uF" H 8250 2100 60  0000 C CNN
F 2 "" V 8350 2200 60  0000 C CNN
F 3 "" V 8350 2200 60  0000 C CNN
	1    8350 2200
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F6118
P 8600 2200
F 0 "C?" H 8700 2300 60  0000 C CNN
F 1 "0.1uF" H 8500 2100 60  0000 C CNN
F 2 "" V 8600 2200 60  0000 C CNN
F 3 "" V 8600 2200 60  0000 C CNN
	1    8600 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 2050 8350 1950
Connection ~ 8350 1950
Wire Wire Line
	8600 1500 8600 2050
Connection ~ 8600 1950
Wire Wire Line
	8350 2350 8350 2450
Wire Wire Line
	8350 2450 8600 2450
Wire Wire Line
	8600 2350 8600 2550
Connection ~ 8600 2450
$Comp
L GNDA #PWR?
U 1 1 598F6376
P 8600 2550
F 0 "#PWR?" H 8600 2300 50  0001 C CNN
F 1 "GNDA" H 8600 2400 50  0000 C CNN
F 2 "" H 8600 2550 50  0000 C CNN
F 3 "" H 8600 2550 50  0000 C CNN
	1    8600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1950 9350 1950
Wire Wire Line
	9350 1950 9350 1800
$Comp
L +3.3V #PWR?
U 1 1 598F6438
P 9350 1800
F 0 "#PWR?" H 9350 1650 50  0001 C CNN
F 1 "+3.3V" H 9350 1940 50  0000 C CNN
F 2 "" H 9350 1800 50  0000 C CNN
F 3 "" H 9350 1800 50  0000 C CNN
	1    9350 1800
	1    0    0    -1  
$EndComp
$Comp
L GS2 GS?
U 1 1 598F693B
P 6300 7100
F 0 "GS?" H 6400 7250 50  0000 C CNN
F 1 "GS2" H 6400 6951 50  0000 C CNN
F 2 "GS2" V 6374 7100 50  0000 C CNN
F 3 "" H 6300 7100 50  0000 C CNN
	1    6300 7100
	0    1    1    0   
$EndComp
$Comp
L CAP C?
U 1 1 598F6D56
P 9950 1750
F 0 "C?" H 10050 1850 60  0000 C CNN
F 1 "0.1uF" H 9850 1650 60  0000 C CNN
F 2 "" V 9950 1750 60  0000 C CNN
F 3 "" V 9950 1750 60  0000 C CNN
	1    9950 1750
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F704D
P 1800 7200
F 0 "C?" H 1900 7300 60  0000 C CNN
F 1 "0.1uF" H 1700 7100 60  0000 C CNN
F 2 "" V 1800 7200 60  0000 C CNN
F 3 "" V 1800 7200 60  0000 C CNN
	1    1800 7200
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F707C
P 2150 7200
F 0 "C?" H 2250 7300 60  0000 C CNN
F 1 "0.1uF" H 2050 7100 60  0000 C CNN
F 2 "" V 2150 7200 60  0000 C CNN
F 3 "" V 2150 7200 60  0000 C CNN
	1    2150 7200
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F70AD
P 2500 7200
F 0 "C?" H 2600 7300 60  0000 C CNN
F 1 "0.1uF" H 2400 7100 60  0000 C CNN
F 2 "" V 2500 7200 60  0000 C CNN
F 3 "" V 2500 7200 60  0000 C CNN
	1    2500 7200
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F7150
P 2850 7200
F 0 "C?" H 2950 7300 60  0000 C CNN
F 1 "0.1uF" H 2750 7100 60  0000 C CNN
F 2 "" V 2850 7200 60  0000 C CNN
F 3 "" V 2850 7200 60  0000 C CNN
	1    2850 7200
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F7187
P 3200 7200
F 0 "C?" H 3300 7300 60  0000 C CNN
F 1 "0.1uF" H 3100 7100 60  0000 C CNN
F 2 "" V 3200 7200 60  0000 C CNN
F 3 "" V 3200 7200 60  0000 C CNN
	1    3200 7200
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F71BE
P 9650 1750
F 0 "C?" H 9750 1850 60  0000 C CNN
F 1 "0.1uF" H 9550 1650 60  0000 C CNN
F 2 "" V 9650 1750 60  0000 C CNN
F 3 "" V 9650 1750 60  0000 C CNN
	1    9650 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6950 1800 7050
Wire Wire Line
	2150 6950 2150 7050
Wire Wire Line
	2500 6850 2500 7050
Connection ~ 2150 6950
Wire Wire Line
	2850 6950 2850 7050
Connection ~ 2500 6950
Wire Wire Line
	3200 6950 3200 7050
Connection ~ 2850 6950
Wire Wire Line
	1800 7450 1800 7350
Wire Wire Line
	2150 7450 2150 7350
Wire Wire Line
	2500 7350 2500 7550
Connection ~ 2150 7450
Wire Wire Line
	2850 7450 2850 7350
Connection ~ 2500 7450
Wire Wire Line
	3200 7450 3200 7350
Connection ~ 2850 7450
$Comp
L GND #PWR?
U 1 1 598F7C89
P 2500 7550
F 0 "#PWR?" H 2500 7300 50  0001 C CNN
F 1 "GND" H 2500 7400 50  0000 C CNN
F 2 "" H 2500 7550 50  0000 C CNN
F 3 "" H 2500 7550 50  0000 C CNN
	1    2500 7550
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 598F7CC1
P 2500 6850
F 0 "#PWR?" H 2500 6700 50  0001 C CNN
F 1 "+3.3V" H 2500 6990 50  0000 C CNN
F 2 "" H 2500 6850 50  0000 C CNN
F 3 "" H 2500 6850 50  0000 C CNN
	1    2500 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6950 3200 6950
Wire Wire Line
	1800 7450 3200 7450
$Comp
L CAP C?
U 1 1 598F880F
P 10250 1750
F 0 "C?" H 10350 1850 60  0000 C CNN
F 1 "0.1uF" H 10150 1650 60  0000 C CNN
F 2 "" V 10250 1750 60  0000 C CNN
F 3 "" V 10250 1750 60  0000 C CNN
	1    10250 1750
	1    0    0    -1  
$EndComp
$Comp
L CAP C?
U 1 1 598F884C
P 10550 1750
F 0 "C?" H 10650 1850 60  0000 C CNN
F 1 "0.1uF" H 10450 1650 60  0000 C CNN
F 2 "" V 10550 1750 60  0000 C CNN
F 3 "" V 10550 1750 60  0000 C CNN
	1    10550 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 1900 9650 2000
Wire Wire Line
	9950 2000 9950 1900
Wire Wire Line
	10250 2000 10250 1900
Connection ~ 9950 2000
Wire Wire Line
	10550 2000 10550 1900
Connection ~ 10250 2000
Wire Wire Line
	10100 2000 10100 2100
Connection ~ 10100 2000
Wire Wire Line
	9650 1600 9650 1500
Wire Wire Line
	9950 1500 9950 1600
Wire Wire Line
	10250 1500 10250 1600
Connection ~ 9950 1500
Wire Wire Line
	10550 1500 10550 1600
Connection ~ 10250 1500
$Comp
L GNDA #PWR?
U 1 1 598F8EB2
P 10100 2100
F 0 "#PWR?" H 10100 1850 50  0001 C CNN
F 1 "GNDA" H 10100 1950 50  0000 C CNN
F 2 "" H 10100 2100 50  0000 C CNN
F 3 "" H 10100 2100 50  0000 C CNN
	1    10100 2100
	1    0    0    -1  
$EndComp
Connection ~ 9650 1500
Wire Wire Line
	9650 2000 10550 2000
Wire Wire Line
	10550 1500 8600 1500
$Comp
L R R?
U 1 1 598FA434
P 1900 850
F 0 "R?" V 1980 850 50  0000 C CNN
F 1 "10K" V 1900 850 50  0000 C CNN
F 2 "" V 1830 850 50  0000 C CNN
F 3 "" H 1900 850 50  0000 C CNN
	1    1900 850 
	1    0    0    -1  
$EndComp
Connection ~ 3700 600 
$Comp
L JUMPER3 JP?
U 1 1 598FA78C
P 1900 1650
F 0 "JP?" H 1950 1550 50  0000 L CNN
F 1 "BOOT/RUN" H 1900 1750 50  0000 C BNN
F 2 "" H 1900 1650 50  0000 C CNN
F 3 "" H 1900 1650 50  0000 C CNN
	1    1900 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1900 600  1900 700 
Wire Wire Line
	1900 1000 1900 1400
Wire Wire Line
	2000 1650 4450 1650
$Comp
L R R?
U 1 1 598FAE31
P 1900 2150
F 0 "R?" V 1980 2150 50  0000 C CNN
F 1 "10K" V 1900 2150 50  0000 C CNN
F 2 "" V 1830 2150 50  0000 C CNN
F 3 "" H 1900 2150 50  0000 C CNN
	1    1900 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1900 1900 2000
Wire Wire Line
	1900 2550 1900 2300
Wire Wire Line
	1900 2400 1650 2400
Wire Wire Line
	1650 2400 1650 1150
Connection ~ 1900 2400
Wire Wire Line
	4100 900  3900 900 
Wire Wire Line
	3900 900  3900 600 
Connection ~ 4100 900 
Text HLabel 3450 4450 0    60   BiDi ~ 0
SCL0
Text HLabel 3450 4350 0    60   BiDi ~ 0
SDA0
Wire Wire Line
	4450 4350 3450 4350
Wire Wire Line
	4450 4450 3450 4450
Text HLabel 7500 4550 2    60   Input ~ 0
MISOA
Text HLabel 7500 4650 2    60   Output ~ 0
MOSIA
Text HLabel 7500 4750 2    60   Output ~ 0
RSPCKA
Wire Wire Line
	6350 4550 7500 4550
Wire Wire Line
	7500 4650 6350 4650
Wire Wire Line
	6350 4750 7500 4750
Text HLabel 3450 3150 0    60   Output ~ 0
SCK1
Wire Wire Line
	3450 3150 4450 3150
Text HLabel 3450 3850 0    60   Output ~ 0
TXD5
Text HLabel 3450 3650 0    60   Output ~ 0
SCK5
Text HLabel 3450 3750 0    60   Input ~ 0
RXD5
Wire Wire Line
	3450 3650 4450 3650
Wire Wire Line
	4450 3750 3450 3750
Wire Wire Line
	3450 3850 4450 3850
Text HLabel 3450 4750 0    60   Output ~ 0
SCK6
Text HLabel 3450 4650 0    60   Input ~ 0
RXD6
Text HLabel 3450 4550 0    60   Output ~ 0
TXD6
Wire Wire Line
	3450 4550 4450 4550
Wire Wire Line
	4450 4650 3450 4650
Wire Wire Line
	3450 4750 4450 4750
Text HLabel 7500 4250 2    60   Output ~ 0
SDC_SELECT
Text HLabel 7500 4150 2    60   Output ~ 0
SDC_POWER
Text HLabel 7500 3750 2    60   Input ~ 0
SDC_DETECT
Wire Wire Line
	7500 3750 6350 3750
Wire Wire Line
	6350 4150 7500 4150
Wire Wire Line
	7500 4250 6350 4250
Text HLabel 7500 3550 2    60   Output ~ 0
LCD_SELECT
Text HLabel 7500 3650 2    60   Output ~ 0
LCD_A0
Wire Wire Line
	6350 3550 7500 3550
Wire Wire Line
	7500 3650 6350 3650
Text HLabel 3450 4250 0    60   Input ~ 0
CAP0
Wire Wire Line
	4450 4250 3450 4250
Text HLabel 3450 4850 0    60   Input ~ 0
CAP2
Wire Wire Line
	3450 4850 4450 4850
Text HLabel 7500 5350 2    60   Input ~ 0
CAP3
Wire Wire Line
	7500 5350 6350 5350
Text HLabel 6700 2050 2    60   Input ~ 0
AN000
Text HLabel 6700 2150 2    60   Input ~ 0
AN001
Text HLabel 6700 2250 2    60   Input ~ 0
AN002
Text HLabel 6700 2350 2    60   Input ~ 0
AN003
Text HLabel 6700 2450 2    60   Input ~ 0
AN100
Text HLabel 6700 2550 2    60   Input ~ 0
AN101
Text HLabel 6700 2650 2    60   Input ~ 0
AN102
Text HLabel 6700 2750 2    60   Input ~ 0
AN103
Wire Wire Line
	6350 2050 6700 2050
Wire Wire Line
	6350 2150 6700 2150
Wire Wire Line
	6350 2250 6700 2250
Wire Wire Line
	6350 2350 6700 2350
Wire Wire Line
	6350 2450 6700 2450
Wire Wire Line
	6350 2550 6700 2550
Wire Wire Line
	6350 2650 6700 2650
Wire Wire Line
	6350 2750 6700 2750
$Comp
L JUMPER3 JP?
U 1 1 5990E296
P 8550 3950
F 0 "JP?" H 8600 3850 50  0000 L CNN
F 1 "JUMPER3" H 8550 4050 50  0000 C BNN
F 2 "" H 8550 3950 50  0000 C CNN
F 3 "" H 8550 3950 50  0000 C CNN
	1    8550 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 3950 8450 3950
Wire Wire Line
	6600 3850 8300 3850
Wire Wire Line
	8300 3850 8300 3600
Wire Wire Line
	8300 3600 8550 3600
Wire Wire Line
	8550 3600 8550 3700
Connection ~ 6600 3850
Wire Wire Line
	8550 4200 8550 4300
Wire Wire Line
	8550 4300 8900 4300
Text HLabel 8900 4300 2    60   BiDi ~ 0
VREF
$EndSCHEMATC
