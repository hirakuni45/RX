EESchema Schematic File Version 4
LIBS:rx72t_100_pga_usb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3050 1850 0    50   BiDi ~ 0
MISO
Text HLabel 3050 1950 0    50   BiDi ~ 0
MOSI
Text HLabel 3050 2050 0    50   BiDi ~ 0
SPCK
Text HLabel 3050 2150 0    50   BiDi ~ 0
SEL
Wire Wire Line
	3300 2250 3300 1700
Wire Wire Line
	3300 2350 3300 2450
$Comp
L power:GND #PWR?
U 1 1 61644132
P 3300 2450
F 0 "#PWR?" H 3300 2200 50  0001 C CNN
F 1 "GND" H 3305 2277 50  0000 C CNN
F 2 "" H 3300 2450 50  0001 C CNN
F 3 "" H 3300 2450 50  0001 C CNN
	1    3300 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61644241
P 3300 1700
F 0 "#PWR?" H 3300 1550 50  0001 C CNN
F 1 "+3.3V" H 3315 1873 50  0000 C CNN
F 2 "" H 3300 1700 50  0001 C CNN
F 3 "" H 3300 1700 50  0001 C CNN
	1    3300 1700
	1    0    0    -1  
$EndComp
Text HLabel 2100 3900 0    50   BiDi ~ 0
SCL
Text HLabel 2100 4000 0    50   BiDi ~ 0
SDA
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J?
U 1 1 616D64D6
P 3600 4000
F 0 "J?" H 3650 4317 50  0000 C CNN
F 1 "I2C_B" H 3650 4226 50  0000 C CNN
F 2 "" H 3600 4000 50  0001 C CNN
F 3 "~" H 3600 4000 50  0001 C CNN
	1    3600 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3900 3300 3600
Wire Wire Line
	3300 3600 4000 3600
Wire Wire Line
	4000 3600 4000 3900
Wire Wire Line
	4000 3900 3900 3900
Wire Wire Line
	3300 3900 3400 3900
Wire Wire Line
	3300 4000 3300 4350
Wire Wire Line
	3300 4350 4000 4350
Wire Wire Line
	4000 4350 4000 4000
Wire Wire Line
	4000 4000 3900 4000
Wire Wire Line
	3300 4000 3400 4000
Wire Wire Line
	3400 4100 3200 4100
Wire Wire Line
	3400 4200 3200 4200
Wire Wire Line
	3200 4200 3200 4350
Wire Wire Line
	3900 4200 4100 4200
Wire Wire Line
	4100 4200 4100 4350
Wire Wire Line
	3900 4100 4100 4100
$Comp
L power:+3.3V #PWR?
U 1 1 616D8F32
P 4100 4100
F 0 "#PWR?" H 4100 3950 50  0001 C CNN
F 1 "+3.3V" V 4115 4228 50  0000 L CNN
F 2 "" H 4100 4100 50  0001 C CNN
F 3 "" H 4100 4100 50  0001 C CNN
	1    4100 4100
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 616D90DF
P 3200 4100
F 0 "#PWR?" H 3200 3950 50  0001 C CNN
F 1 "+3.3V" V 3215 4228 50  0000 L CNN
F 2 "" H 3200 4100 50  0001 C CNN
F 3 "" H 3200 4100 50  0001 C CNN
	1    3200 4100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 616D9BC9
P 3200 4350
F 0 "#PWR?" H 3200 4100 50  0001 C CNN
F 1 "GND" H 3205 4177 50  0000 C CNN
F 2 "" H 3200 4350 50  0001 C CNN
F 3 "" H 3200 4350 50  0001 C CNN
	1    3200 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 616DA06C
P 4100 4350
F 0 "#PWR?" H 4100 4100 50  0001 C CNN
F 1 "GND" H 4105 4177 50  0000 C CNN
F 2 "" H 4100 4350 50  0001 C CNN
F 3 "" H 4100 4350 50  0001 C CNN
	1    4100 4350
	1    0    0    -1  
$EndComp
Text HLabel 5500 2500 0    50   BiDi ~ 0
RXD8
Text HLabel 5500 2600 0    50   BiDi ~ 0
TXD8
Text HLabel 5500 2700 0    50   BiDi ~ 0
SCK8
Wire Wire Line
	2100 3900 2250 3900
Connection ~ 3300 3900
Wire Wire Line
	2100 4000 2600 4000
Connection ~ 3300 4000
$Comp
L akizuki:R R?
U 1 1 61717E07
P 2250 3550
F 0 "R?" V 2204 3620 50  0000 L CNN
F 1 "1K" V 2295 3620 50  0000 L CNN
F 2 "" H 2250 3480 50  0000 C CNN
F 3 "" V 2250 3550 50  0000 C CNN
	1    2250 3550
	0    1    1    0   
$EndComp
$Comp
L akizuki:R R?
U 1 1 617182E9
P 2600 3550
F 0 "R?" V 2554 3620 50  0000 L CNN
F 1 "1K" V 2645 3620 50  0000 L CNN
F 2 "" H 2600 3480 50  0000 C CNN
F 3 "" V 2600 3550 50  0000 C CNN
	1    2600 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 3700 2250 3900
Connection ~ 2250 3900
Wire Wire Line
	2250 3900 3300 3900
Wire Wire Line
	2600 3700 2600 4000
Connection ~ 2600 4000
Wire Wire Line
	2600 4000 3300 4000
Wire Wire Line
	2250 3400 2250 3250
Wire Wire Line
	2250 3250 2600 3250
Wire Wire Line
	2600 3250 2600 3400
Wire Wire Line
	2250 3250 2250 3100
Connection ~ 2250 3250
$Comp
L power:+3.3V #PWR?
U 1 1 61719A4D
P 2250 3100
F 0 "#PWR?" H 2250 2950 50  0001 C CNN
F 1 "+3.3V" H 2265 3273 50  0000 C CNN
F 2 "" H 2250 3100 50  0001 C CNN
F 3 "" H 2250 3100 50  0001 C CNN
	1    2250 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J?
U 1 1 617A2A5E
P 6450 2000
F 0 "J?" H 6500 2317 50  0000 C CNN
F 1 "SCI8" H 6500 2226 50  0000 C CNN
F 2 "" H 6450 2000 50  0001 C CNN
F 3 "~" H 6450 2000 50  0001 C CNN
	1    6450 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2600 6000 2600
Wire Wire Line
	6000 2600 6000 1900
Wire Wire Line
	6000 1900 6250 1900
Wire Wire Line
	5500 2500 7000 2500
Wire Wire Line
	7000 2500 7000 1900
Wire Wire Line
	7000 1900 6750 1900
Wire Wire Line
	7000 2500 7500 2500
Connection ~ 7000 2500
Wire Wire Line
	6000 2600 7600 2600
Connection ~ 6000 2600
Wire Wire Line
	5500 2700 7700 2700
Text HLabel 5500 2900 0    50   BiDi ~ 0
PB0
Text HLabel 5500 3000 0    50   BiDi ~ 0
PB3
Wire Wire Line
	7500 2500 7500 1800
Wire Wire Line
	7500 1800 8000 1800
Wire Wire Line
	8000 1900 7600 1900
Wire Wire Line
	7600 1900 7600 2600
Wire Wire Line
	7700 2700 7700 2000
Wire Wire Line
	7700 2000 8000 2000
Wire Wire Line
	7800 2900 7800 2100
Wire Wire Line
	7800 2100 8000 2100
$Comp
L Connector_Generic:Conn_01x07 J?
U 1 1 61CA4348
P 8200 2100
F 0 "J?" H 8280 2142 50  0000 L CNN
F 1 "SPI8" H 8280 2051 50  0000 L CNN
F 2 "" H 8200 2100 50  0001 C CNN
F 3 "~" H 8200 2100 50  0001 C CNN
	1    8200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3000 5700 3000
Wire Wire Line
	7900 3000 7900 2200
Wire Wire Line
	7900 2200 8000 2200
Wire Wire Line
	5500 2900 5700 2900
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 61CABB0A
P 3900 2150
F 0 "J?" H 3980 2142 50  0000 L CNN
F 1 "RSPI" H 3980 2051 50  0000 L CNN
F 2 "" H 3900 2150 50  0001 C CNN
F 3 "~" H 3900 2150 50  0001 C CNN
	1    3900 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1850 3700 1850
Wire Wire Line
	3050 1950 3700 1950
Wire Wire Line
	3050 2050 3700 2050
Wire Wire Line
	3050 2150 3700 2150
Wire Wire Line
	3300 2250 3700 2250
Wire Wire Line
	3300 2350 3700 2350
Wire Wire Line
	3700 2450 3500 2450
Wire Wire Line
	3500 2450 3500 2800
Wire Wire Line
	3500 2800 5700 2800
Wire Wire Line
	5700 2800 5700 2900
Connection ~ 5700 2900
Wire Wire Line
	5700 2900 6150 2900
Wire Wire Line
	5700 3000 5700 3100
Wire Wire Line
	5700 3100 3600 3100
Wire Wire Line
	3600 3100 3600 2550
Wire Wire Line
	3600 2550 3700 2550
Connection ~ 5700 3000
Wire Wire Line
	5700 3000 6850 3000
Wire Wire Line
	8000 2300 7400 2300
Wire Wire Line
	8000 2400 8000 3100
$Comp
L power:GND #PWR?
U 1 1 61CC9884
P 8000 3100
F 0 "#PWR?" H 8000 2850 50  0001 C CNN
F 1 "GND" H 8005 2927 50  0000 C CNN
F 2 "" H 8000 3100 50  0001 C CNN
F 3 "" H 8000 3100 50  0001 C CNN
	1    8000 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61CC9CD3
P 7400 2300
F 0 "#PWR?" H 7400 2150 50  0001 C CNN
F 1 "+3.3V" V 7415 2428 50  0000 L CNN
F 2 "" H 7400 2300 50  0001 C CNN
F 3 "" H 7400 2300 50  0001 C CNN
	1    7400 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 2100 6150 2100
Wire Wire Line
	6150 2100 6150 2900
Connection ~ 6150 2900
Wire Wire Line
	6150 2900 7800 2900
Wire Wire Line
	6750 2100 6850 2100
Wire Wire Line
	6850 2100 6850 3000
Connection ~ 6850 3000
Wire Wire Line
	6850 3000 7900 3000
Wire Wire Line
	6250 2000 5700 2000
Wire Wire Line
	5700 2000 5700 2100
Wire Wire Line
	6750 2000 6850 2000
Wire Wire Line
	6850 2000 6850 1700
$Comp
L power:+3.3V #PWR?
U 1 1 61CE1FD4
P 6850 1700
F 0 "#PWR?" H 6850 1550 50  0001 C CNN
F 1 "+3.3V" H 6865 1873 50  0000 C CNN
F 2 "" H 6850 1700 50  0001 C CNN
F 3 "" H 6850 1700 50  0001 C CNN
	1    6850 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61CE2302
P 5700 2100
F 0 "#PWR?" H 5700 1850 50  0001 C CNN
F 1 "GND" H 5705 1927 50  0000 C CNN
F 2 "" H 5700 2100 50  0001 C CNN
F 3 "" H 5700 2100 50  0001 C CNN
	1    5700 2100
	1    0    0    -1  
$EndComp
Text HLabel 5500 4500 0    50   BiDi ~ 0
RXD11
Text HLabel 5500 4600 0    50   BiDi ~ 0
TXD11
Text HLabel 5500 4700 0    50   BiDi ~ 0
SCK11
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J?
U 1 1 61FCC12D
P 6450 4000
F 0 "J?" H 6500 4317 50  0000 C CNN
F 1 "SCI11" H 6500 4226 50  0000 C CNN
F 2 "" H 6450 4000 50  0001 C CNN
F 3 "~" H 6450 4000 50  0001 C CNN
	1    6450 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 4600 6000 4600
Wire Wire Line
	6000 4600 6000 3900
Wire Wire Line
	6000 3900 6250 3900
Wire Wire Line
	5500 4500 7000 4500
Wire Wire Line
	7000 4500 7000 3900
Wire Wire Line
	7000 3900 6750 3900
Wire Wire Line
	7000 4500 7500 4500
Connection ~ 7000 4500
Wire Wire Line
	6000 4600 7600 4600
Connection ~ 6000 4600
Wire Wire Line
	5500 4700 7700 4700
Text HLabel 5500 4900 0    50   BiDi ~ 0
P32
Text HLabel 5500 5000 0    50   BiDi ~ 0
P33
Wire Wire Line
	7500 4500 7500 3800
Wire Wire Line
	7500 3800 8000 3800
Wire Wire Line
	8000 3900 7600 3900
Wire Wire Line
	7600 3900 7600 4600
Wire Wire Line
	7700 4700 7700 4000
Wire Wire Line
	7700 4000 8000 4000
Wire Wire Line
	7800 4900 7800 4100
Wire Wire Line
	7800 4100 8000 4100
$Comp
L Connector_Generic:Conn_01x07 J?
U 1 1 61FCC148
P 8200 4100
F 0 "J?" H 8280 4142 50  0000 L CNN
F 1 "SPI11" H 8280 4051 50  0000 L CNN
F 2 "" H 8200 4100 50  0001 C CNN
F 3 "~" H 8200 4100 50  0001 C CNN
	1    8200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 5000 7900 4200
Wire Wire Line
	7900 4200 8000 4200
Wire Wire Line
	8000 4300 7400 4300
Wire Wire Line
	8000 4400 8000 5100
$Comp
L power:GND #PWR?
U 1 1 61FCC15C
P 8000 5100
F 0 "#PWR?" H 8000 4850 50  0001 C CNN
F 1 "GND" H 8005 4927 50  0000 C CNN
F 2 "" H 8000 5100 50  0001 C CNN
F 3 "" H 8000 5100 50  0001 C CNN
	1    8000 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61FCC162
P 7400 4300
F 0 "#PWR?" H 7400 4150 50  0001 C CNN
F 1 "+3.3V" V 7415 4428 50  0000 L CNN
F 2 "" H 7400 4300 50  0001 C CNN
F 3 "" H 7400 4300 50  0001 C CNN
	1    7400 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 4100 6150 4100
Wire Wire Line
	6150 4100 6150 4900
Connection ~ 6150 4900
Wire Wire Line
	6150 4900 7800 4900
Wire Wire Line
	6750 4100 6850 4100
Wire Wire Line
	6850 4100 6850 5000
Connection ~ 6850 5000
Wire Wire Line
	6850 5000 7900 5000
Wire Wire Line
	6250 4000 5700 4000
Wire Wire Line
	5700 4000 5700 4100
Wire Wire Line
	6750 4000 6850 4000
Wire Wire Line
	6850 4000 6850 3700
$Comp
L power:+3.3V #PWR?
U 1 1 61FCC174
P 6850 3700
F 0 "#PWR?" H 6850 3550 50  0001 C CNN
F 1 "+3.3V" H 6865 3873 50  0000 C CNN
F 2 "" H 6850 3700 50  0001 C CNN
F 3 "" H 6850 3700 50  0001 C CNN
	1    6850 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61FCC17A
P 5700 4100
F 0 "#PWR?" H 5700 3850 50  0001 C CNN
F 1 "GND" H 5705 3927 50  0000 C CNN
F 2 "" H 5700 4100 50  0001 C CNN
F 3 "" H 5700 4100 50  0001 C CNN
	1    5700 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5000 6850 5000
Wire Wire Line
	5500 4900 6150 4900
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 620F8F3C
P 3700 5000
F 0 "J?" H 3780 4992 50  0000 L CNN
F 1 "I2C_A" H 3780 4901 50  0000 L CNN
F 2 "" H 3700 5000 50  0001 C CNN
F 3 "~" H 3700 5000 50  0001 C CNN
	1    3700 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4900 2250 4900
Wire Wire Line
	2250 4900 2250 3900
Wire Wire Line
	2600 4000 2600 5000
Wire Wire Line
	2600 5000 3500 5000
Wire Wire Line
	3500 5100 3200 5100
Wire Wire Line
	3500 5200 3350 5200
Wire Wire Line
	3350 5200 3350 5350
$Comp
L power:GND #PWR?
U 1 1 62107820
P 3350 5350
F 0 "#PWR?" H 3350 5100 50  0001 C CNN
F 1 "GND" H 3355 5177 50  0000 C CNN
F 2 "" H 3350 5350 50  0001 C CNN
F 3 "" H 3350 5350 50  0001 C CNN
	1    3350 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 62107AEB
P 3200 5100
F 0 "#PWR?" H 3200 4950 50  0001 C CNN
F 1 "+3.3V" V 3215 5228 50  0000 L CNN
F 2 "" H 3200 5100 50  0001 C CNN
F 3 "" H 3200 5100 50  0001 C CNN
	1    3200 5100
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
