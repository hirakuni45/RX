EESchema Schematic File Version 4
LIBS:board-cache
EELAYER 26 0
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
L MicroChip:ATWINC1500-MR210PB U?
U 1 1 5C76D029
P 4800 3750
F 0 "U?" H 4200 4900 50  0000 C CNN
F 1 "ATWINC1500-MR210PB" H 4050 2650 50  0000 C CNN
F 2 "" H 4150 3950 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATWINC15x0-MR210xB-IEEE-802.11-b-g-n-SmartConnect-IoT-Module-Data-Sheet-DS70005304C.pdf" H 4150 3950 50  0001 C CNN
	1    4800 3750
	1    0    0    -1  
$EndComp
Text HLabel 2350 3650 0    50   Input ~ 0
SSLA
Text HLabel 2350 3950 0    50   Input ~ 0
SPCLK
Text HLabel 2350 3750 0    50   Input ~ 0
MOSI
Text HLabel 2350 3850 0    50   Input ~ 0
MISO
$Comp
L akizuki:MR MR?
U 1 1 5C733C72
P 2750 3800
F 0 "MR?" H 2750 4175 50  0000 C CNN
F 1 "22" H 2750 4084 50  0000 C CNN
F 2 "" H 2750 3800 50  0001 C CNN
F 3 "" H 2750 3800 50  0001 C CNN
	1    2750 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3650 2350 3650
Wire Wire Line
	2600 3750 2350 3750
Wire Wire Line
	2600 3850 2350 3850
Wire Wire Line
	2600 3950 2350 3950
Wire Wire Line
	2900 3650 4000 3650
Wire Wire Line
	4000 3750 2900 3750
Wire Wire Line
	2900 3850 4000 3850
Wire Wire Line
	4000 3950 2900 3950
Wire Wire Line
	4700 5000 4700 5150
Wire Wire Line
	4700 5150 4800 5150
Wire Wire Line
	4800 5150 4800 5000
Wire Wire Line
	4800 5150 4900 5150
Wire Wire Line
	4900 5150 4900 5000
Connection ~ 4800 5150
Wire Wire Line
	4800 5150 4800 5300
$Comp
L power:GND #PWR?
U 1 1 5C7340A1
P 4800 5300
F 0 "#PWR?" H 4800 5050 50  0001 C CNN
F 1 "GND" H 4805 5127 50  0000 C CNN
F 2 "" H 4800 5300 50  0001 C CNN
F 3 "" H 4800 5300 50  0001 C CNN
	1    4800 5300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
