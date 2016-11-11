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
LIBS:ftdi
LIBS:renesas
LIBS:rx24t_core-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
U 1 1 581FF9FA
P 5750 3550
F 0 "U?" H 5075 925 60  0000 C CNN
F 1 "RX24T" H 6375 6175 60  0000 C CNN
F 2 "" H 5075 925 60  0000 C CNN
F 3 "" H 5075 925 60  0000 C CNN
	1    5750 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1300 4700 1300
Wire Wire Line
	4700 1300 4700 6300
Wire Wire Line
	4700 2200 4800 2200
Wire Wire Line
	4700 4100 4800 4100
Connection ~ 4700 2200
Wire Wire Line
	4700 5400 4800 5400
Connection ~ 4700 4100
Connection ~ 4700 5400
$Comp
L GND #PWR?
U 1 1 58200D60
P 4700 6300
F 0 "#PWR?" H 4700 6050 50  0001 C CNN
F 1 "GND" H 4700 6150 50  0000 C CNN
F 2 "" H 4700 6300 50  0000 C CNN
F 3 "" H 4700 6300 50  0000 C CNN
	1    4700 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2400 4600 2400
Wire Wire Line
	4600 900  4600 5200
Wire Wire Line
	4600 3900 4800 3900
Wire Wire Line
	4600 5200 4800 5200
Connection ~ 4600 3900
$Comp
L +3.3V #PWR?
U 1 1 58200DEF
P 4600 900
F 0 "#PWR?" H 4600 750 50  0001 C CNN
F 1 "+3.3V" H 4600 1040 50  0000 C CNN
F 2 "" H 4600 900 50  0000 C CNN
F 3 "" H 4600 900 50  0000 C CNN
	1    4600 900 
	1    0    0    -1  
$EndComp
Connection ~ 4600 2400
Wire Wire Line
	6700 4900 6800 4900
Wire Wire Line
	6800 4900 6800 6300
$Comp
L GND #PWR?
U 1 1 582047B6
P 6800 6300
F 0 "#PWR?" H 6800 6050 50  0001 C CNN
F 1 "GND" H 6800 6150 50  0000 C CNN
F 2 "" H 6800 6300 50  0000 C CNN
F 3 "" H 6800 6300 50  0000 C CNN
	1    6800 6300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 582047DF
P 6900 900
F 0 "#PWR?" H 6900 750 50  0001 C CNN
F 1 "+3.3V" H 6900 1040 50  0000 C CNN
F 2 "" H 6900 900 50  0000 C CNN
F 3 "" H 6900 900 50  0000 C CNN
	1    6900 900 
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A508
P 5100 6950
F 0 "C?" H 5110 7020 50  0000 L CNN
F 1 "0.1uF" H 5110 6870 50  0000 L CNN
F 2 "" H 5100 6950 50  0000 C CNN
F 3 "" H 5100 6950 50  0000 C CNN
	1    5100 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A54F
P 5450 6950
F 0 "C?" H 5460 7020 50  0000 L CNN
F 1 "0.1uF" H 5460 6870 50  0000 L CNN
F 2 "" H 5450 6950 50  0000 C CNN
F 3 "" H 5450 6950 50  0000 C CNN
	1    5450 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A56C
P 5800 6950
F 0 "C?" H 5810 7020 50  0000 L CNN
F 1 "0.1uF" H 5810 6870 50  0000 L CNN
F 2 "" H 5800 6950 50  0000 C CNN
F 3 "" H 5800 6950 50  0000 C CNN
	1    5800 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A5A1
P 6150 6950
F 0 "C?" H 6160 7020 50  0000 L CNN
F 1 "0.1uF" H 6160 6870 50  0000 L CNN
F 2 "" H 6150 6950 50  0000 C CNN
F 3 "" H 6150 6950 50  0000 C CNN
	1    6150 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A5C4
P 6500 6950
F 0 "C?" H 6510 7020 50  0000 L CNN
F 1 "0.1uF" H 6510 6870 50  0000 L CNN
F 2 "" H 6500 6950 50  0000 C CNN
F 3 "" H 6500 6950 50  0000 C CNN
	1    6500 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A607
P 7450 1500
F 0 "C?" H 7460 1570 50  0000 L CNN
F 1 "0.1uF" H 7460 1420 50  0000 L CNN
F 2 "" H 7450 1500 50  0000 C CNN
F 3 "" H 7450 1500 50  0000 C CNN
	1    7450 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 7200 6500 7200
Wire Wire Line
	5450 7200 5450 7050
Wire Wire Line
	5800 7050 5800 7350
Connection ~ 5450 7200
Wire Wire Line
	6150 7200 6150 7050
Connection ~ 5800 7200
Wire Wire Line
	6500 7200 6500 7050
Connection ~ 6150 7200
Wire Wire Line
	5100 6850 5100 6700
Wire Wire Line
	5450 6850 5450 6700
Connection ~ 5450 6700
Wire Wire Line
	5800 6550 5800 6850
Connection ~ 5800 6700
Wire Wire Line
	6150 6850 6150 6700
Connection ~ 6150 6700
Wire Wire Line
	6500 6850 6500 6700
$Comp
L GND #PWR?
U 1 1 5822A98E
P 5800 7350
F 0 "#PWR?" H 5800 7100 50  0001 C CNN
F 1 "GND" H 5800 7200 50  0000 C CNN
F 2 "" H 5800 7350 50  0000 C CNN
F 3 "" H 5800 7350 50  0000 C CNN
	1    5800 7350
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 5822A9DD
P 5800 6550
F 0 "#PWR?" H 5800 6400 50  0001 C CNN
F 1 "+3.3V" H 5800 6690 50  0000 C CNN
F 2 "" H 5800 6550 50  0000 C CNN
F 3 "" H 5800 6550 50  0000 C CNN
	1    5800 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 7050 5100 7200
Wire Wire Line
	6500 6700 5100 6700
$Comp
L CRYSTAL X?
U 1 1 5822AD07
P 3800 2300
F 0 "X?" H 3900 2400 60  0000 C CNN
F 1 "10MHz" H 3650 2400 60  0000 C CNN
F 2 "" V 3800 2300 60  0000 C CNN
F 3 "" V 3800 2300 60  0000 C CNN
	1    3800 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 2150 3800 2100
Wire Wire Line
	3800 2450 3800 2600
$Comp
L C_Small C?
U 1 1 5822AEEF
P 3400 2300
F 0 "C?" H 3410 2370 50  0000 L CNN
F 1 "10pF" H 3410 2220 50  0000 L CNN
F 2 "" H 3400 2300 50  0000 C CNN
F 3 "" H 3400 2300 50  0000 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822AF20
P 3800 2700
F 0 "C?" H 3810 2770 50  0000 L CNN
F 1 "10pF" H 3810 2620 50  0000 L CNN
F 2 "" H 3800 2700 50  0000 C CNN
F 3 "" H 3800 2700 50  0000 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2200 3400 2100
Connection ~ 3800 2100
Connection ~ 3800 2500
$Comp
L C_Small C?
U 1 1 5822B0E4
P 3400 1700
F 0 "C?" H 3410 1770 50  0000 L CNN
F 1 "4.7uF" H 3410 1620 50  0000 L CNN
F 2 "" H 3400 1700 50  0000 C CNN
F 3 "" H 3400 1700 50  0000 C CNN
	1    3400 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2100 4800 2100
Wire Wire Line
	4800 1100 4400 1100
Wire Wire Line
	4800 1200 4400 1200
Wire Wire Line
	4800 1400 4400 1400
Wire Wire Line
	4800 1700 4400 1700
Wire Wire Line
	4800 1800 4400 1800
Wire Wire Line
	4800 1900 4400 1900
Wire Wire Line
	4800 2500 4400 2500
Wire Wire Line
	4800 2600 4400 2600
Wire Wire Line
	4800 2700 4400 2700
Wire Wire Line
	4800 2800 4400 2800
Wire Wire Line
	4800 2900 4400 2900
Wire Wire Line
	4800 3000 4400 3000
Wire Wire Line
	4800 3100 4400 3100
Wire Wire Line
	4800 3200 4400 3200
Wire Wire Line
	4800 3300 4400 3300
Wire Wire Line
	4800 3400 4400 3400
Wire Wire Line
	4800 3500 4400 3500
Wire Wire Line
	4800 3600 4400 3600
Wire Wire Line
	4800 3700 4400 3700
Wire Wire Line
	4800 3800 4400 3800
Wire Wire Line
	4800 4000 4400 4000
Wire Wire Line
	4800 4200 4400 4200
Wire Wire Line
	4800 4300 4400 4300
Wire Wire Line
	4800 4400 4400 4400
Wire Wire Line
	4800 4500 4400 4500
Wire Wire Line
	4800 4600 4400 4600
Wire Wire Line
	4800 4700 4400 4700
Wire Wire Line
	4800 4800 4400 4800
Wire Wire Line
	4800 4900 4400 4900
Wire Wire Line
	4800 5000 4400 5000
Wire Wire Line
	4800 5100 4400 5100
Wire Wire Line
	4800 5300 4400 5300
Wire Wire Line
	4800 5500 4400 5500
Wire Wire Line
	4800 5600 4400 5600
Wire Wire Line
	4800 5700 4400 5700
Wire Wire Line
	4800 5800 4400 5800
Wire Wire Line
	4800 5900 4400 5900
Wire Wire Line
	4800 6000 4400 6000
Entry Wire Line
	4300 6100 4400 6000
Entry Wire Line
	4300 6000 4400 5900
Entry Wire Line
	4300 5900 4400 5800
Entry Wire Line
	4300 5800 4400 5700
Entry Wire Line
	4300 5700 4400 5600
Entry Wire Line
	4300 5600 4400 5500
Entry Wire Line
	4300 5400 4400 5300
Entry Wire Line
	4300 1200 4400 1100
Entry Wire Line
	4300 1300 4400 1200
Entry Wire Line
	4300 5200 4400 5100
Entry Wire Line
	4300 5100 4400 5000
Entry Wire Line
	4300 5000 4400 4900
Entry Wire Line
	4300 4900 4400 4800
Entry Wire Line
	4300 4800 4400 4700
Entry Wire Line
	4300 4700 4400 4600
Entry Wire Line
	4300 4600 4400 4500
Entry Wire Line
	4300 4500 4400 4400
Entry Wire Line
	4300 4400 4400 4300
Entry Wire Line
	4300 4300 4400 4200
Entry Wire Line
	4300 1900 4400 1800
Entry Wire Line
	4300 4100 4400 4000
Entry Wire Line
	4300 2000 4400 1900
Entry Wire Line
	4300 3900 4400 3800
Entry Wire Line
	4300 3800 4400 3700
Entry Wire Line
	4300 3700 4400 3600
Entry Wire Line
	4300 3600 4400 3500
Entry Wire Line
	4300 3500 4400 3400
Entry Wire Line
	4300 3400 4400 3300
Entry Wire Line
	4300 3300 4400 3200
Entry Wire Line
	4300 3200 4400 3100
Entry Wire Line
	4300 3100 4400 3000
Entry Wire Line
	4300 3000 4400 2900
Entry Wire Line
	4300 2900 4400 2800
Entry Wire Line
	4300 2800 4400 2700
Entry Wire Line
	4300 2700 4400 2600
Entry Wire Line
	4300 2600 4400 2500
Entry Wire Line
	4300 1800 4400 1700
Entry Wire Line
	4300 1500 4400 1400
Wire Bus Line
	4300 1200 4300 6200
Wire Bus Line
	4300 6200 4200 6300
Wire Bus Line
	4200 6300 3400 6300
Text Label 4400 6000 0    60   ~ 0
P90
Text Label 4400 5900 0    60   ~ 0
P91
Text Label 4400 5800 0    60   ~ 0
P92
Text Label 4400 5700 0    60   ~ 0
P93
Text Label 4400 5600 0    60   ~ 0
P94
Text Label 4400 5500 0    60   ~ 0
P95
Text Label 4400 5300 0    60   ~ 0
P96
Text Label 4400 5100 0    60   ~ 0
PA0
Text Label 4400 5000 0    60   ~ 0
PA1
Text Label 4400 4900 0    60   ~ 0
PA2
Text Label 4400 4800 0    60   ~ 0
PA3
Text Label 4400 4700 0    60   ~ 0
PA4
Text Label 4400 4600 0    60   ~ 0
PA5
Text Label 4400 4500 0    60   ~ 0
PB0
Text Label 4400 4400 0    60   ~ 0
PB1
Text Label 4400 4300 0    60   ~ 0
PB2
Text Label 4400 4200 0    60   ~ 0
PB3
Text Label 4400 4000 0    60   ~ 0
PB4
Text Label 4400 3800 0    60   ~ 0
PB5
Text Label 4400 3700 0    60   ~ 0
PB6
Text Label 4400 3600 0    60   ~ 0
PB7
Text Label 4400 3500 0    60   ~ 0
PD0
Text Label 4400 3400 0    60   ~ 0
PD1
Text Label 4400 3300 0    60   ~ 0
PD2
Text Label 4400 3200 0    60   ~ 0
PD3
Text Label 4400 3100 0    60   ~ 0
PD4
Text Label 4400 3000 0    60   ~ 0
PD5
Text Label 4400 2900 0    60   ~ 0
PD6
Text Label 4400 2800 0    60   ~ 0
PD7
Text Label 4400 2700 0    60   ~ 0
PE0
Text Label 4400 2600 0    60   ~ 0
PE1
Text Label 4400 2500 0    60   ~ 0
PE2
Text Label 4400 1900 0    60   ~ 0
PE3
Text Label 4400 1800 0    60   ~ 0
PE4
Text Label 4400 1700 0    60   ~ 0
P01
Text Label 4400 1400 0    60   ~ 0
P00
Text Label 4400 1200 0    60   ~ 0
P02
Text Label 4400 1100 0    60   ~ 0
PE5
Wire Wire Line
	3800 2500 4200 2500
Wire Wire Line
	4200 2500 4200 2300
Wire Wire Line
	4200 2300 4800 2300
Wire Wire Line
	3400 2400 3400 2900
Wire Wire Line
	3400 2900 3800 2900
Wire Wire Line
	3800 2900 3800 2800
Wire Wire Line
	3600 2900 3600 3000
Connection ~ 3600 2900
$Comp
L GND #PWR?
U 1 1 58241CAE
P 3600 3000
F 0 "#PWR?" H 3600 2750 50  0001 C CNN
F 1 "GND" H 3600 2850 50  0000 C CNN
F 2 "" H 3600 3000 50  0000 C CNN
F 3 "" H 3600 3000 50  0000 C CNN
	1    3600 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 58241DE0
P 3400 1900
F 0 "#PWR?" H 3400 1650 50  0001 C CNN
F 1 "GND" H 3400 1750 50  0000 C CNN
F 2 "" H 3400 1900 50  0000 C CNN
F 3 "" H 3400 1900 50  0000 C CNN
	1    3400 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1900 3400 1800
Wire Wire Line
	4800 1500 4400 1500
Wire Wire Line
	4400 1500 4400 1550
Wire Wire Line
	4400 1550 3400 1550
Wire Wire Line
	3400 1550 3400 1600
$Comp
L R_Small R?
U 1 1 58242299
P 3800 1200
F 0 "R?" H 3830 1220 50  0000 L CNN
F 1 "10K" H 3830 1160 50  0000 L CNN
F 2 "" H 3800 1200 50  0000 C CNN
F 3 "" H 3800 1200 50  0000 C CNN
	1    3800 1200
	1    0    0    -1  
$EndComp
$Comp
L R_Small R?
U 1 1 582422D6
P 4050 1200
F 0 "R?" H 4080 1220 50  0000 L CNN
F 1 "10K" H 4080 1160 50  0000 L CNN
F 2 "" H 4050 1200 50  0000 C CNN
F 3 "" H 4050 1200 50  0000 C CNN
	1    4050 1200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 582423B3
P 4050 900
F 0 "#PWR?" H 4050 750 50  0001 C CNN
F 1 "+3.3V" H 4050 1040 50  0000 C CNN
F 2 "" H 4050 900 50  0000 C CNN
F 3 "" H 4050 900 50  0000 C CNN
	1    4050 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1600 4800 1600
Wire Wire Line
	4800 2000 4400 2000
Wire Wire Line
	4400 2000 4400 2050
Wire Wire Line
	4400 2050 3800 2050
Wire Wire Line
	4050 1100 4050 900 
Wire Wire Line
	4050 1000 3800 1000
Wire Wire Line
	3800 1000 3800 1100
Connection ~ 4050 1000
Wire Wire Line
	3800 2050 3800 1300
Wire Wire Line
	4050 1600 4050 1300
Wire Wire Line
	6700 6000 7100 6000
Wire Wire Line
	6700 5900 7100 5900
Wire Wire Line
	6700 5800 7100 5800
Wire Wire Line
	6700 5700 7100 5700
Wire Wire Line
	6700 5600 7100 5600
Wire Wire Line
	6700 5500 7100 5500
Wire Wire Line
	6700 5400 7100 5400
Wire Wire Line
	6700 5300 7100 5300
Wire Wire Line
	6700 5200 7100 5200
Wire Wire Line
	6700 5000 7100 5000
Wire Wire Line
	6700 4800 7100 4800
Wire Wire Line
	6700 4700 7100 4700
Wire Wire Line
	6700 4600 7100 4600
Wire Wire Line
	6700 4500 7100 4500
Wire Wire Line
	6700 4400 7100 4400
Wire Wire Line
	6700 4300 7100 4300
Wire Wire Line
	6700 4200 7100 4200
Wire Wire Line
	6700 4100 7100 4100
Wire Wire Line
	6700 3700 7100 3700
Wire Wire Line
	6700 3600 7100 3600
Wire Wire Line
	6700 3500 7100 3500
Wire Wire Line
	6700 3400 7100 3400
Wire Wire Line
	6700 3300 7100 3300
Wire Wire Line
	6700 3200 7100 3200
Wire Wire Line
	6700 3100 7100 3100
Wire Wire Line
	6700 3000 7100 3000
Wire Wire Line
	6700 2900 7100 2900
Wire Wire Line
	6700 2800 7100 2800
Wire Wire Line
	6700 2700 7100 2700
Wire Wire Line
	6700 2600 7100 2600
Wire Wire Line
	6700 2500 7100 2500
Wire Wire Line
	6700 2400 7100 2400
Wire Wire Line
	6700 2300 7100 2300
Wire Wire Line
	6700 2200 7100 2200
Wire Wire Line
	6700 2100 7100 2100
Wire Wire Line
	6700 2000 7100 2000
Wire Wire Line
	6700 1500 7100 1500
Wire Wire Line
	6700 1400 7100 1400
Wire Wire Line
	6700 1300 7100 1300
Wire Wire Line
	6700 1200 7100 1200
Wire Wire Line
	6700 1100 7100 1100
Entry Wire Line
	7100 1100 7200 1200
Entry Wire Line
	7100 1200 7200 1300
Entry Wire Line
	7100 1300 7200 1400
Entry Wire Line
	7100 1400 7200 1500
Entry Wire Line
	7100 1500 7200 1600
Entry Wire Line
	7100 2000 7200 2100
Entry Wire Line
	7100 2100 7200 2200
Entry Wire Line
	7100 2200 7200 2300
Entry Wire Line
	7100 2300 7200 2400
Entry Wire Line
	7100 2400 7200 2500
Entry Wire Line
	7100 2500 7200 2600
Entry Wire Line
	7100 2600 7200 2700
Entry Wire Line
	7100 2700 7200 2800
Entry Wire Line
	7100 2800 7200 2900
Entry Wire Line
	7100 2900 7200 3000
Entry Wire Line
	7100 3000 7200 3100
Entry Wire Line
	7100 3100 7200 3200
Entry Wire Line
	7100 3200 7200 3300
Entry Wire Line
	7100 3300 7200 3400
Entry Wire Line
	7100 3400 7200 3500
Entry Wire Line
	7100 3500 7200 3600
Entry Wire Line
	7100 3600 7200 3700
Entry Wire Line
	7100 3700 7200 3800
Entry Wire Line
	7100 4100 7200 4200
Entry Wire Line
	7100 4200 7200 4300
Entry Wire Line
	7100 4300 7200 4400
Entry Wire Line
	7100 4400 7200 4500
Entry Wire Line
	7100 4500 7200 4600
Entry Wire Line
	7100 4600 7200 4700
Entry Wire Line
	7100 4700 7200 4800
Entry Wire Line
	7100 4800 7200 4900
Entry Wire Line
	7100 5000 7200 5100
Entry Wire Line
	7100 5200 7200 5300
Entry Wire Line
	7100 5300 7200 5400
Entry Wire Line
	7100 5400 7200 5500
Entry Wire Line
	7100 5500 7200 5600
Entry Wire Line
	7100 5600 7200 5700
Entry Wire Line
	7100 5700 7200 5800
Entry Wire Line
	7100 5800 7200 5900
Entry Wire Line
	7100 5900 7200 6000
Entry Wire Line
	7100 6000 7200 6100
Text Label 6950 1100 0    60   ~ 0
P10
Text Label 6950 1200 0    60   ~ 0
P11
Text Label 6950 1300 0    60   ~ 0
P80
Text Label 6950 1400 0    60   ~ 0
P81
Text Label 6950 1500 0    60   ~ 0
P82
Text Label 6950 2000 0    60   ~ 0
P40
Text Label 6950 2100 0    60   ~ 0
P41
Text Label 6950 2200 0    60   ~ 0
P42
Text Label 6950 2300 0    60   ~ 0
P43
Text Label 6950 2400 0    60   ~ 0
P44
Text Label 6950 2500 0    60   ~ 0
P45
Text Label 6950 2600 0    60   ~ 0
P46
Text Label 6950 2700 0    60   ~ 0
P47
Text Label 6950 2800 0    60   ~ 0
P50
Text Label 6950 2900 0    60   ~ 0
P51
Text Label 6950 3000 0    60   ~ 0
P52
Text Label 6950 3100 0    60   ~ 0
P53
Text Label 6950 3200 0    60   ~ 0
P54
Text Label 6950 3300 0    60   ~ 0
P55
Text Label 6950 3400 0    60   ~ 0
P60
Text Label 6950 3500 0    60   ~ 0
P61
Text Label 6950 3600 0    60   ~ 0
P62
Text Label 6950 3700 0    60   ~ 0
P63
Text Label 6950 4100 0    60   ~ 0
P64
Text Label 6950 4200 0    60   ~ 0
P65
Text Label 6950 4300 0    60   ~ 0
P20
Text Label 6950 4400 0    60   ~ 0
P21
Text Label 6950 4500 0    60   ~ 0
P22
Text Label 6950 4600 0    60   ~ 0
P23
Text Label 6950 4700 0    60   ~ 0
P24
Text Label 6950 4800 0    60   ~ 0
P30
Text Label 6950 5000 0    60   ~ 0
P31
Text Label 6950 5200 0    60   ~ 0
P32
Text Label 6950 5300 0    60   ~ 0
P33
Text Label 6950 5400 0    60   ~ 0
P70
Text Label 6950 5500 0    60   ~ 0
P71
Text Label 6950 5600 0    60   ~ 0
P72
Text Label 6950 5700 0    60   ~ 0
P73
Text Label 6950 5800 0    60   ~ 0
P74
Text Label 6950 5900 0    60   ~ 0
P75
Text Label 6950 6000 0    60   ~ 0
P76
Wire Wire Line
	6900 900  6900 5100
Wire Wire Line
	6900 5100 6700 5100
$Comp
L +3.3VADC #PWR?
U 1 1 58245BA0
P 7750 1200
F 0 "#PWR?" H 7900 1150 50  0001 C CNN
F 1 "+3.3VADC" H 7750 1300 50  0000 C CNN
F 2 "" H 7750 1200 50  0000 C CNN
F 3 "" H 7750 1200 50  0000 C CNN
	1    7750 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1800 7300 1800
Wire Wire Line
	6800 1900 6700 1900
Connection ~ 6800 1800
Wire Wire Line
	6800 4000 6700 4000
Connection ~ 6800 1900
Wire Wire Line
	6700 3800 7100 3800
Connection ~ 7000 1700
$Comp
L GNDA #PWR?
U 1 1 5824611C
P 7450 1800
F 0 "#PWR?" H 7450 1550 50  0001 C CNN
F 1 "GNDA" H 7450 1650 50  0000 C CNN
F 2 "" H 7450 1800 50  0000 C CNN
F 3 "" H 7450 1800 50  0000 C CNN
	1    7450 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3800 7100 3900
Wire Wire Line
	7100 3900 7700 3900
Wire Wire Line
	6700 3900 7000 3900
Wire Wire Line
	7000 3900 7000 4000
Wire Wire Line
	7000 4000 7500 4000
Wire Wire Line
	7500 4000 7500 4100
$Comp
L C_Small C?
U 1 1 58246342
P 7500 4200
F 0 "C?" H 7510 4270 50  0000 L CNN
F 1 "1uF" H 7510 4120 50  0000 L CNN
F 2 "" H 7500 4200 50  0000 C CNN
F 3 "" H 7500 4200 50  0000 C CNN
	1    7500 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 4300 7500 4500
$Comp
L GNDA #PWR?
U 1 1 58246573
P 7500 4500
F 0 "#PWR?" H 7500 4250 50  0001 C CNN
F 1 "GNDA" H 7500 4350 50  0000 C CNN
F 2 "" H 7500 4500 50  0000 C CNN
F 3 "" H 7500 4500 50  0000 C CNN
	1    7500 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3900 7700 4400
Wire Wire Line
	7700 4400 7500 4400
Connection ~ 7500 4400
$Comp
L C_Small C?
U 1 1 58246F1D
P 7750 1500
F 0 "C?" H 7760 1570 50  0000 L CNN
F 1 "0.1uF" H 7760 1420 50  0000 L CNN
F 2 "" H 7750 1500 50  0000 C CNN
F 3 "" H 7750 1500 50  0000 C CNN
	1    7750 1500
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 58246F5C
P 8050 1500
F 0 "C?" H 8060 1570 50  0000 L CNN
F 1 "0.1uF" H 8060 1420 50  0000 L CNN
F 2 "" H 8050 1500 50  0000 C CNN
F 3 "" H 8050 1500 50  0000 C CNN
	1    8050 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1600 7750 1850
Connection ~ 7450 1700
Wire Wire Line
	8050 1700 8050 1600
Connection ~ 7750 1700
Wire Wire Line
	7450 1400 7450 1300
Wire Wire Line
	7300 1300 8050 1300
Wire Wire Line
	8050 1300 8050 1400
Connection ~ 7750 1300
Wire Wire Line
	7450 1600 7450 1800
Wire Wire Line
	6700 1700 8050 1700
Wire Wire Line
	6700 1600 7000 1600
Wire Wire Line
	7000 1600 7000 1700
Wire Wire Line
	7300 1300 7300 2650
Connection ~ 7450 1300
Wire Wire Line
	7750 1200 7750 1400
Wire Wire Line
	6800 1800 6800 4000
Wire Bus Line
	3400 6300 3300 6200
Wire Bus Line
	3300 6200 3300 1200
Wire Bus Line
	7200 1200 7200 6200
Wire Bus Line
	7200 6200 7300 6300
Wire Bus Line
	7300 6300 8200 6300
Wire Bus Line
	8200 6300 8300 6200
Wire Bus Line
	8300 6200 8300 1100
$Comp
L GS2 GS?
U 1 1 58248830
P 7750 2050
F 0 "GS?" H 7850 2200 50  0000 C CNN
F 1 "GS2" H 7850 1901 50  0000 C CNN
F 2 "GS2" V 7824 2050 50  0000 C CNN
F 3 "" H 7750 2050 50  0000 C CNN
	1    7750 2050
	1    0    0    -1  
$EndComp
$Comp
L GS2 GS?
U 1 1 58248877
P 7750 2950
F 0 "GS?" H 7850 3100 50  0000 C CNN
F 1 "GS2" H 7850 2801 50  0000 C CNN
F 2 "GS2" V 7824 2950 50  0000 C CNN
F 3 "" H 7750 2950 50  0000 C CNN
	1    7750 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 2250 7750 2350
$Comp
L GND #PWR?
U 1 1 58248B4F
P 7750 2350
F 0 "#PWR?" H 7750 2100 50  0001 C CNN
F 1 "GND" H 7750 2200 50  0000 C CNN
F 2 "" H 7750 2350 50  0000 C CNN
F 3 "" H 7750 2350 50  0000 C CNN
	1    7750 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 2750 7750 2650
Wire Wire Line
	7750 2650 7300 2650
Connection ~ 7300 1800
Wire Wire Line
	7750 3150 7750 3250
$Comp
L +3.3V #PWR?
U 1 1 58248EB4
P 7750 3250
F 0 "#PWR?" H 7750 3100 50  0001 C CNN
F 1 "+3.3V" H 7750 3390 50  0000 C CNN
F 2 "" H 7750 3250 50  0000 C CNN
F 3 "" H 7750 3250 50  0000 C CNN
	1    7750 3250
	-1   0    0    1   
$EndComp
$EndSCHEMATC
