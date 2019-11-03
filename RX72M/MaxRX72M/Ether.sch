EESchema Schematic File Version 4
LIBS:MaxRX72M-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 9
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
L Interface_Ethernet:LAN8720A U?
U 1 1 5DC93B7A
P 6200 3700
F 0 "U?" H 6150 2511 50  0000 C CNN
F 1 "LAN8720A" H 6150 2420 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm" H 6250 2650 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/8720a.pdf" H 6000 2750 50  0001 C CNN
	1    6200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3900 4000 3900
Text HLabel 4000 3900 0    50   Input ~ 10
ET_MDC
Text HLabel 4000 3800 0    50   BiDi ~ 10
ET_MDIO
Text HLabel 4000 3700 0    50   Input ~ 10
ET_CRS
Wire Wire Line
	5400 3800 4000 3800
Wire Wire Line
	4000 3700 5400 3700
Text HLabel 4000 3600 0    50   Input ~ 10
ET_RXER
Text HLabel 4000 3400 0    50   Input ~ 10
ET_RXD0
Text HLabel 4000 3500 0    50   Input ~ 10
ET_RXD1
Text HLabel 4000 3300 0    50   Input ~ 10
ET_TXEN
Text HLabel 4000 3100 0    50   Input ~ 10
ET_TXD0
Text HLabel 4000 3200 0    50   Input ~ 10
ET_TXD1
Wire Wire Line
	5400 3100 4000 3100
Wire Wire Line
	4000 3200 5400 3200
Wire Wire Line
	5400 3300 4000 3300
Wire Wire Line
	4000 3400 5400 3400
Wire Wire Line
	5400 3500 4000 3500
Wire Wire Line
	4000 3600 5400 3600
Text HLabel 4000 4200 0    50   Output ~ 10
ET_REFCK
Wire Wire Line
	5400 4200 4000 4200
Text GLabel 4000 4400 0    50   Input ~ 10
~RESET~
Wire Wire Line
	4000 4400 4100 4400
Wire Wire Line
	4100 4400 4100 4100
Wire Wire Line
	4100 4100 5400 4100
$Comp
L akizuki:J0011D21BNL J?
U 1 1 5DBF1A1C
P 9050 3700
F 0 "J?" H 9628 3746 50  0000 L CNN
F 1 "J0011D21BNL" H 9628 3655 50  0000 L CNN
F 2 "" H 9065 3695 50  0001 C CNN
F 3 "" H 9065 3695 50  0001 C CNN
	1    9050 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3300 8300 3300
Wire Wire Line
	6900 3400 8300 3400
Wire Wire Line
	8300 3600 7000 3600
Wire Wire Line
	7000 3600 7000 3500
Wire Wire Line
	7000 3500 6900 3500
Wire Wire Line
	6900 3200 7000 3200
Wire Wire Line
	7000 3200 7000 3100
Wire Wire Line
	7000 3100 8300 3100
$EndSCHEMATC
