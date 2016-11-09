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
Wire Wire Line
	6700 5100 6900 5100
$Comp
L +3.3V #PWR?
U 1 1 582047DF
P 6900 5100
F 0 "#PWR?" H 6900 4950 50  0001 C CNN
F 1 "+3.3V" H 6900 5240 50  0000 C CNN
F 2 "" H 6900 5100 50  0000 C CNN
F 3 "" H 6900 5100 50  0000 C CNN
	1    6900 5100
	0    1    1    0   
$EndComp
$Comp
L C_Small C?
U 1 1 5822A508
P 4600 6950
F 0 "C?" H 4610 7020 50  0000 L CNN
F 1 "0.1uF" H 4610 6870 50  0000 L CNN
F 2 "" H 4600 6950 50  0000 C CNN
F 3 "" H 4600 6950 50  0000 C CNN
	1    4600 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A54F
P 4950 6950
F 0 "C?" H 4960 7020 50  0000 L CNN
F 1 "0.1uF" H 4960 6870 50  0000 L CNN
F 2 "" H 4950 6950 50  0000 C CNN
F 3 "" H 4950 6950 50  0000 C CNN
	1    4950 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A56C
P 5300 6950
F 0 "C?" H 5310 7020 50  0000 L CNN
F 1 "0.1uF" H 5310 6870 50  0000 L CNN
F 2 "" H 5300 6950 50  0000 C CNN
F 3 "" H 5300 6950 50  0000 C CNN
	1    5300 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A5A1
P 5650 6950
F 0 "C?" H 5660 7020 50  0000 L CNN
F 1 "0.1uF" H 5660 6870 50  0000 L CNN
F 2 "" H 5650 6950 50  0000 C CNN
F 3 "" H 5650 6950 50  0000 C CNN
	1    5650 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A5C4
P 6000 6950
F 0 "C?" H 6010 7020 50  0000 L CNN
F 1 "0.1uF" H 6010 6870 50  0000 L CNN
F 2 "" H 6000 6950 50  0000 C CNN
F 3 "" H 6000 6950 50  0000 C CNN
	1    6000 6950
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822A607
P 6350 6950
F 0 "C?" H 6360 7020 50  0000 L CNN
F 1 "C_Small" H 6360 6870 50  0000 L CNN
F 2 "" H 6350 6950 50  0000 C CNN
F 3 "" H 6350 6950 50  0000 C CNN
	1    6350 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 7200 6000 7200
Wire Wire Line
	4950 7200 4950 7050
Wire Wire Line
	5300 7050 5300 7350
Connection ~ 4950 7200
Wire Wire Line
	5650 7200 5650 7050
Connection ~ 5300 7200
Wire Wire Line
	6000 7200 6000 7050
Connection ~ 5650 7200
Wire Wire Line
	4600 6850 4600 6700
Wire Wire Line
	4950 6850 4950 6700
Connection ~ 4950 6700
Wire Wire Line
	5300 6550 5300 6850
Connection ~ 5300 6700
Wire Wire Line
	5650 6850 5650 6700
Connection ~ 5650 6700
Wire Wire Line
	6000 6850 6000 6700
$Comp
L GND #PWR?
U 1 1 5822A98E
P 5300 7350
F 0 "#PWR?" H 5300 7100 50  0001 C CNN
F 1 "GND" H 5300 7200 50  0000 C CNN
F 2 "" H 5300 7350 50  0000 C CNN
F 3 "" H 5300 7350 50  0000 C CNN
	1    5300 7350
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 5822A9DD
P 5300 6550
F 0 "#PWR?" H 5300 6400 50  0001 C CNN
F 1 "+3.3V" H 5300 6690 50  0000 C CNN
F 2 "" H 5300 6550 50  0000 C CNN
F 3 "" H 5300 6550 50  0000 C CNN
	1    5300 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 7050 4600 7200
Wire Wire Line
	6000 6700 4600 6700
$Comp
L CRYSTAL X?
U 1 1 5822AD07
P 4150 2200
F 0 "X?" H 4250 2300 60  0000 C CNN
F 1 "10MHz" H 4000 2100 60  0000 C CNN
F 2 "" V 4150 2200 60  0000 C CNN
F 3 "" V 4150 2200 60  0000 C CNN
	1    4150 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 2100 4800 2100
Wire Wire Line
	4500 2300 4800 2300
Wire Wire Line
	4150 2050 4150 2000
Wire Wire Line
	3750 2000 4500 2000
Wire Wire Line
	4500 2000 4500 2100
Wire Wire Line
	4500 2400 4500 2300
Wire Wire Line
	3600 2400 4500 2400
Wire Wire Line
	4150 2400 4150 2350
$Comp
L C_Small C?
U 1 1 5822AEEF
P 3750 2200
F 0 "C?" H 3760 2270 50  0000 L CNN
F 1 "10pF" H 3760 2120 50  0000 L CNN
F 2 "" H 3750 2200 50  0000 C CNN
F 3 "" H 3750 2200 50  0000 C CNN
	1    3750 2200
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5822AF20
P 3400 2200
F 0 "C?" H 3410 2270 50  0000 L CNN
F 1 "10pF" H 3410 2120 50  0000 L CNN
F 2 "" H 3400 2200 50  0000 C CNN
F 3 "" H 3400 2200 50  0000 C CNN
	1    3400 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2100 3750 2000
Connection ~ 4150 2000
Wire Wire Line
	3600 2400 3600 2000
Wire Wire Line
	3600 2000 3400 2000
Wire Wire Line
	3400 2000 3400 2100
Connection ~ 4150 2400
$Comp
L C_Small C?
U 1 1 5822B0E4
P 4050 1500
F 0 "C?" H 4060 1570 50  0000 L CNN
F 1 "4.7uF" H 4060 1420 50  0000 L CNN
F 2 "" H 4050 1500 50  0000 C CNN
F 3 "" H 4050 1500 50  0000 C CNN
	1    4050 1500
	0    1    1    0   
$EndComp
$EndSCHEMATC
