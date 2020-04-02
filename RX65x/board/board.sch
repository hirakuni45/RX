EESchema Schematic File Version 4
LIBS:board-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 9
Title "Renesas RX65N BASE"
Date ""
Rev ""
Comp "G.P.L."
Comment1 "hira@rvf-rc45.net"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L board-rescue:RX65N_176-renesas-board-rescue U1
U 1 1 5C66B59D
P 4100 3250
F 0 "U1" H 4100 5515 50  0000 C CNN
F 1 "RX65N_176" H 4100 5424 50  0000 C CNN
F 2 "" H 4100 3250 50  0001 C CNN
F 3 "" H 4100 3250 50  0001 C CNN
	1    4100 3250
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:RX65N_176-renesas-board-rescue U1
U 2 1 5C66B614
P 7050 3200
F 0 "U1" H 7050 5415 50  0000 C CNN
F 1 "RX65N_176" H 7050 5324 50  0000 C CNN
F 2 "" H 7050 3200 50  0001 C CNN
F 3 "" H 7050 3200 50  0001 C CNN
	2    7050 3200
	1    0    0    -1  
$EndComp
$Sheet
S 950  6000 950  1400
U 5C66C44B
F0 "POWER" 50
F1 "POWER.sch" 50
$EndSheet
$Sheet
S 950  4400 950  1100
U 5C66CA1D
F0 "SDC_IF" 50
F1 "SDC_IF.sch" 50
F2 "SD_CMD" I R 1900 4550 50 
F3 "SD_CLK" U R 1900 4650 50 
F4 "SD_CD" O R 1900 5250 50 
F5 "SD_WP" O R 1900 5350 50 
F6 "SD_D0" B R 1900 4750 50 
F7 "SD_D1" B R 1900 4850 50 
F8 "SD_D2" B R 1900 4950 50 
F9 "SD_D3" B R 1900 5050 50 
$EndSheet
$Sheet
S 9100 700  900  1400
U 5C66CC8A
F0 "LCD_IF" 50
F1 "LCD_IF.sch" 50
F2 "LD0" I L 9100 850 50 
F3 "LD1" I L 9100 950 50 
F4 "LD2" I L 9100 1050 50 
F5 "LD3" I L 9100 1150 50 
F6 "LD4" I L 9100 1250 50 
F7 "LD5" I L 9100 1350 50 
F8 "LD6" I L 9100 1450 50 
F9 "LD7" I L 9100 1550 50 
F10 "HSYNC" I L 9100 1650 50 
F11 "VSYNC" I L 9100 1750 50 
$EndSheet
$Sheet
S 3750 6000 850  1400
U 5C71B0A3
F0 "ETHER_PHY" 50
F1 "ETHER_PHY.sch" 50
F2 "ET_R50CK" U R 4600 6250 50 
F3 "ET_TX0" O R 4600 6350 50 
F4 "ET_TX1" O R 4600 6450 50 
F5 "ET_TXEN" O R 4600 6550 50 
F6 "ET_RX0" I R 4600 6650 50 
F7 "ET_RX1" I R 4600 6750 50 
F8 "ET_ERR" O R 4600 6850 50 
F9 "ET_MDIO" B R 4600 6950 50 
F10 "ET_MDC" I R 4600 7050 50 
F11 "ET_CRS" I R 4600 7150 50 
$EndSheet
Wire Wire Line
	4800 3600 5100 3600
Wire Wire Line
	7750 4150 8000 4150
Text Label 7850 5100 0    50   ~ 0
D0
Wire Wire Line
	7750 4250 8000 4250
Wire Wire Line
	7750 4350 8000 4350
Wire Wire Line
	7750 4450 8000 4450
Wire Wire Line
	7750 4550 8000 4550
Wire Wire Line
	7750 4650 8000 4650
Wire Wire Line
	7750 4750 8000 4750
Wire Wire Line
	7750 4850 8000 4850
Wire Wire Line
	7750 5100 8000 5100
Wire Wire Line
	7750 5200 8000 5200
Wire Wire Line
	7750 5300 8000 5300
Wire Wire Line
	7750 5400 8000 5400
Wire Wire Line
	7750 5500 8000 5500
Wire Wire Line
	7750 5600 8000 5600
Wire Wire Line
	7750 5700 8000 5700
Wire Wire Line
	7750 5800 8000 5800
Text Label 7850 5200 0    50   ~ 0
D1
Text Label 7850 5300 0    50   ~ 0
D2
Text Label 7850 5400 0    50   ~ 0
D3
Text Label 7850 5500 0    50   ~ 0
D4
Text Label 7850 5600 0    50   ~ 0
D5
Text Label 7850 5700 0    50   ~ 0
D6
Text Label 7850 5800 0    50   ~ 0
D7
Text Label 7850 4150 0    50   ~ 0
D8
Text Label 7850 4250 0    50   ~ 0
D9
Text Label 7850 4350 0    50   ~ 0
D10
Text Label 7850 4450 0    50   ~ 0
D11
Text Label 7850 4550 0    50   ~ 0
D12
Text Label 7850 4650 0    50   ~ 0
D13
Text Label 7850 4750 0    50   ~ 0
D14
Text Label 7850 4850 0    50   ~ 0
D15
Wire Wire Line
	7750 1300 8000 1300
Text Label 7850 1300 0    50   ~ 0
L0
Wire Wire Line
	6350 1800 6100 1800
Text Label 6150 1800 0    50   ~ 0
LD1
Wire Wire Line
	6350 1700 6100 1700
Text Label 6150 1700 0    50   ~ 0
LD2
Wire Wire Line
	4800 3800 5100 3800
Text Label 4950 3800 0    50   ~ 0
LD3
Wire Wire Line
	4800 3700 5100 3700
Text Label 4950 3700 0    50   ~ 0
LD4
Text Label 4950 3600 0    50   ~ 0
LD5
Wire Wire Line
	4800 3500 5100 3500
Text Label 4950 3500 0    50   ~ 0
LD6
Wire Wire Line
	3400 3900 3100 3900
Text Label 3150 3900 0    50   ~ 0
LD7
Wire Wire Line
	6350 1600 6000 1600
Wire Wire Line
	6350 1500 6000 1500
Wire Wire Line
	6350 1400 6000 1400
Wire Wire Line
	6350 1300 6000 1300
Wire Wire Line
	6350 3400 6100 3400
Text Label 6150 3400 0    50   ~ 0
A2
Wire Wire Line
	6350 3300 6100 3300
Text Label 6150 3300 0    50   ~ 0
A1
Wire Wire Line
	6350 3500 6100 3500
Wire Wire Line
	6350 3600 6100 3600
Wire Wire Line
	6350 3700 6100 3700
Wire Wire Line
	6350 3800 6100 3800
Wire Wire Line
	6350 3900 6100 3900
Text Label 6150 3500 0    50   ~ 0
A3
Text Label 6150 3600 0    50   ~ 0
A4
Text Label 6150 3700 0    50   ~ 0
A5
Text Label 6150 3800 0    50   ~ 0
A6
Text Label 6150 3900 0    50   ~ 0
A7
Wire Wire Line
	6350 4150 6100 4150
Wire Wire Line
	6350 4250 6100 4250
Wire Wire Line
	6350 4350 6100 4350
Wire Wire Line
	6350 4450 6100 4450
Text Label 6150 4150 0    50   ~ 0
A8
Text Label 6150 4250 0    50   ~ 0
A9
Text Label 6150 4350 0    50   ~ 0
A10
Text Label 6150 4450 0    50   ~ 0
A11
Wire Wire Line
	6350 4550 6100 4550
Wire Wire Line
	6350 4650 6100 4650
Wire Wire Line
	6350 4750 6100 4750
Wire Wire Line
	6350 4850 6100 4850
Text Label 6150 4550 0    50   ~ 0
A12
Text Label 6150 4650 0    50   ~ 0
A13
Text Label 6150 4750 0    50   ~ 0
A14
Text Label 6150 4850 0    50   ~ 0
A15
Text Label 4850 2800 0    50   ~ 0
DQM0
Text Label 4850 2900 0    50   ~ 0
DQM1
Text Label 4850 1300 0    50   ~ 0
SDCLK
Text Label 4850 2700 0    50   ~ 0
CKE
Text Label 4850 2600 0    50   ~ 0
~WE
Text Label 4850 2500 0    50   ~ 0
~CAS
Text Label 4850 2400 0    50   ~ 0
~RAS
Wire Wire Line
	4800 2800 5400 2800
Wire Wire Line
	4800 2900 5400 2900
Wire Wire Line
	4800 2700 5400 2700
Wire Wire Line
	4800 2600 5400 2600
Wire Wire Line
	4800 2500 5400 2500
Wire Wire Line
	4800 2400 5400 2400
Wire Wire Line
	3400 4900 3050 4900
Text Label 3050 4900 0    50   ~ 0
SD_D0
Wire Wire Line
	3400 5000 3050 5000
Text Label 3050 5000 0    50   ~ 0
SD_D1
Text Label 3100 5700 0    50   ~ 0
SD_D2
Wire Wire Line
	3400 4500 3050 4500
Text Label 3050 4500 0    50   ~ 0
SD_D3
Wire Wire Line
	3400 4700 3050 4700
Text Label 3050 4700 0    50   ~ 0
SD_CMD
Wire Wire Line
	3400 4800 3050 4800
Text Label 3050 4800 0    50   ~ 0
SD_CLK
Wire Wire Line
	3400 5100 3050 5100
Wire Wire Line
	3400 5200 3050 5200
Text Label 3050 5100 0    50   ~ 0
SD_WP
Text Label 3050 5200 0    50   ~ 0
SD_CD
Wire Wire Line
	3400 4200 3100 4200
Text Label 3150 4200 0    50   ~ 0
LCLK
Wire Wire Line
	3400 4100 3100 4100
Text Label 3150 4100 0    50   ~ 0
LCON0
Wire Wire Line
	3400 4000 3100 4000
Text Label 3150 4000 0    50   ~ 0
LCON1
Wire Wire Line
	7750 1400 8000 1400
Wire Wire Line
	7750 1500 8000 1500
Text Label 7750 1400 0    50   ~ 0
LCON3
Text Label 7750 1500 0    50   ~ 0
LCON2
Wire Wire Line
	4800 1900 5200 1900
Text Label 4850 1900 0    50   ~ 0
ET_R50CK
Wire Wire Line
	4800 2000 5200 2000
Text Label 4850 2000 0    50   ~ 0
ET_ERR
Wire Wire Line
	4800 1800 5200 1800
Wire Wire Line
	4800 1700 5200 1700
Wire Wire Line
	4800 1500 5200 1500
Text Label 4850 1800 0    50   ~ 0
ET_RX0
Text Label 4850 1700 0    50   ~ 0
ET_RX1
Wire Wire Line
	4800 1400 5200 1400
Text Label 4850 1400 0    50   ~ 0
ET_MDIO
Text Label 4850 1500 0    50   ~ 0
ET_MDC
Text Label 6000 1400 0    50   ~ 0
ET_TX0
Text Label 6000 1500 0    50   ~ 0
ET_TX1
Text Label 6000 1600 0    50   ~ 0
ET_CRS
Wire Wire Line
	7750 3200 8100 3200
Text Label 7950 3200 0    50   ~ 0
TDO
Wire Wire Line
	7750 3300 8100 3300
Text Label 7950 3300 0    50   ~ 0
TCK
Wire Wire Line
	7750 3400 8100 3400
Text Label 7950 3400 0    50   ~ 0
TDI
Wire Wire Line
	7750 3500 8100 3500
Text Label 7950 3500 0    50   ~ 0
TMS
Wire Wire Line
	7750 3600 8100 3600
Text Label 7950 3600 0    50   ~ 0
~TRST
Text Label 6000 1300 0    50   ~ 0
ET_TXEN
$Sheet
S 9100 2400 900  1100
U 5C697E34
F0 "JTAG_IF" 50
F1 "JTAG_IF.sch" 50
F2 "~RES" I L 9100 2550 50 
F3 "MD" I L 9100 2650 50 
F4 "EMLE" I L 9100 2750 50 
F5 "TDO" I L 9100 2850 50 
F6 "TCK" I L 9100 2950 50 
F7 "TDI" I L 9100 3050 50 
F8 "TMS" I L 9100 3150 50 
F9 "~TRST" I L 9100 3250 50 
F10 "UB" I L 9100 3350 50 
$EndSheet
Wire Wire Line
	1900 4550 2300 4550
Wire Wire Line
	1900 4650 2300 4650
Wire Wire Line
	1900 4750 2300 4750
Wire Wire Line
	1900 4850 2300 4850
Wire Wire Line
	1900 4950 2300 4950
Wire Wire Line
	1900 5050 2300 5050
Wire Wire Line
	1900 5250 2300 5250
Wire Wire Line
	1900 5350 2300 5350
Text Label 2000 4550 0    50   ~ 0
SD_CMD
Text Label 2000 4650 0    50   ~ 0
SD_CLK
Text Label 2000 4750 0    50   ~ 0
SD_D0
Text Label 2000 4850 0    50   ~ 0
SD_D1
Text Label 2000 4950 0    50   ~ 0
SD_D2
Text Label 2000 5050 0    50   ~ 0
SD_D3
Text Label 2000 5250 0    50   ~ 0
SD_CD
Text Label 2000 5350 0    50   ~ 0
SD_WP
Entry Wire Line
	2300 4550 2400 4650
Entry Wire Line
	2300 4650 2400 4750
Entry Wire Line
	2300 4750 2400 4850
Entry Wire Line
	2300 4850 2400 4950
Entry Wire Line
	2300 4950 2400 5050
Entry Wire Line
	2300 5050 2400 5150
Entry Wire Line
	2300 5250 2400 5350
Entry Wire Line
	2300 5350 2400 5450
Entry Wire Line
	2950 4600 3050 4500
Entry Wire Line
	2950 4800 3050 4700
Entry Wire Line
	2950 4900 3050 4800
Entry Wire Line
	2950 5000 3050 4900
Entry Wire Line
	2950 5100 3050 5000
Entry Wire Line
	2950 5200 3050 5100
Entry Wire Line
	2950 5300 3050 5200
Wire Bus Line
	2950 5600 2850 5700
Wire Bus Line
	2850 5700 2500 5700
Wire Bus Line
	2500 5700 2400 5600
Entry Wire Line
	5900 1200 6000 1300
Entry Wire Line
	5900 1300 6000 1400
Entry Wire Line
	5900 1400 6000 1500
Entry Wire Line
	5900 1500 6000 1600
Entry Wire Line
	5200 1400 5300 1300
Entry Wire Line
	5200 1500 5300 1400
Entry Wire Line
	5200 1700 5300 1600
Entry Wire Line
	5200 1800 5300 1700
Entry Wire Line
	5200 1900 5300 1800
Entry Wire Line
	5200 2000 5300 1900
Wire Bus Line
	5900 1100 5800 1000
Wire Bus Line
	5800 1000 5400 1000
Wire Bus Line
	5400 1000 5300 1100
Wire Wire Line
	4600 6250 5200 6250
Wire Wire Line
	4600 6350 5200 6350
Wire Wire Line
	4600 6450 5200 6450
Wire Wire Line
	4600 6550 5200 6550
Wire Wire Line
	4600 6650 5200 6650
Wire Wire Line
	4600 6750 5200 6750
Wire Wire Line
	4600 6850 5200 6850
Wire Wire Line
	4600 6950 5200 6950
Wire Wire Line
	4600 7050 5200 7050
Wire Wire Line
	4600 7150 5200 7150
Entry Wire Line
	5200 6250 5300 6150
Entry Wire Line
	5200 6350 5300 6250
Entry Wire Line
	5200 6450 5300 6350
Entry Wire Line
	5200 6550 5300 6450
Entry Wire Line
	5200 6650 5300 6550
Entry Wire Line
	5200 6750 5300 6650
Entry Wire Line
	5200 6850 5300 6750
Entry Wire Line
	5200 6950 5300 6850
Entry Wire Line
	5200 7050 5300 6950
Entry Wire Line
	5200 7150 5300 7050
Text Label 4800 6250 0    50   ~ 0
ET_R50CK
Text Label 4800 6350 0    50   ~ 0
ET_TX0
Text Label 4800 6450 0    50   ~ 0
ET_TX1
Text Label 4800 6550 0    50   ~ 0
ET_TXEN
Text Label 4800 6650 0    50   ~ 0
ET_RX0
Text Label 4800 6750 0    50   ~ 0
ET_RX1
Text Label 4800 6850 0    50   ~ 0
ET_ERR
Text Label 4800 6950 0    50   ~ 0
ET_MDIO
Text Label 4800 7050 0    50   ~ 0
ET_MDC
Text Label 4800 7150 0    50   ~ 0
ET_CRS
Entry Wire Line
	6000 3400 6100 3300
Entry Wire Line
	6000 3500 6100 3400
Entry Wire Line
	6000 3600 6100 3500
Entry Wire Line
	6000 3700 6100 3600
Entry Wire Line
	6000 3800 6100 3700
Entry Wire Line
	6000 3900 6100 3800
Entry Wire Line
	6000 4000 6100 3900
Entry Wire Line
	6000 4250 6100 4150
Entry Wire Line
	6000 4350 6100 4250
Entry Wire Line
	6000 4450 6100 4350
Entry Wire Line
	6000 4550 6100 4450
Entry Wire Line
	6000 4650 6100 4550
Entry Wire Line
	6000 4750 6100 4650
Entry Wire Line
	6000 4850 6100 4750
Entry Wire Line
	6000 4950 6100 4850
Entry Wire Line
	8000 4150 8100 4250
Entry Wire Line
	8000 4250 8100 4350
Entry Wire Line
	8000 4350 8100 4450
Entry Wire Line
	8000 4450 8100 4550
Entry Wire Line
	8000 4550 8100 4650
Entry Wire Line
	8000 4650 8100 4750
Entry Wire Line
	8000 4750 8100 4850
Entry Wire Line
	8000 4850 8100 4950
Entry Wire Line
	8000 5100 8100 5200
Entry Wire Line
	8000 5200 8100 5300
Entry Wire Line
	8000 5300 8100 5400
Entry Wire Line
	8000 5400 8100 5500
Entry Wire Line
	8000 5500 8100 5600
Entry Wire Line
	8000 5600 8100 5700
Entry Wire Line
	8000 5700 8100 5800
Entry Wire Line
	8000 5800 8100 5900
Entry Wire Line
	5400 2400 5500 2500
Entry Wire Line
	5400 2500 5500 2600
Entry Wire Line
	5400 2600 5500 2700
Entry Wire Line
	5400 2700 5500 2800
Entry Wire Line
	5400 2800 5500 2900
Entry Wire Line
	5400 2900 5500 3000
Wire Bus Line
	5500 3150 5600 3250
Wire Bus Line
	5600 3250 5900 3250
Wire Bus Line
	5900 3250 6000 3350
Wire Bus Line
	6000 6150 6100 6250
Wire Bus Line
	6100 6250 8000 6250
Wire Bus Line
	8000 6250 8100 6150
Wire Wire Line
	10000 4550 10300 4550
Wire Wire Line
	10000 4650 10300 4650
Wire Wire Line
	10000 4750 10300 4750
Wire Wire Line
	10000 4850 10300 4850
Wire Wire Line
	10000 4950 10300 4950
Wire Wire Line
	10000 5050 10300 5050
Wire Wire Line
	10000 5150 10300 5150
Wire Wire Line
	10000 5250 10300 5250
Wire Wire Line
	10000 5350 10300 5350
Wire Wire Line
	10000 5450 10300 5450
Wire Wire Line
	10000 5550 10300 5550
Wire Wire Line
	10000 5650 10300 5650
Wire Wire Line
	10000 5750 10300 5750
Wire Wire Line
	10000 5850 10300 5850
Wire Wire Line
	10000 5950 10300 5950
Wire Wire Line
	10000 6050 10300 6050
Wire Wire Line
	9100 4650 8800 4650
Wire Wire Line
	9100 4750 8800 4750
Wire Wire Line
	9100 4850 8800 4850
Wire Wire Line
	9100 4950 8800 4950
Wire Wire Line
	9100 5050 8800 5050
Wire Wire Line
	9100 5150 8800 5150
Wire Wire Line
	9100 5250 8800 5250
Wire Wire Line
	9100 5350 8800 5350
Wire Wire Line
	9100 5450 8800 5450
Wire Wire Line
	9100 5550 8800 5550
Wire Wire Line
	9100 5650 8800 5650
Wire Wire Line
	9100 5750 8800 5750
Wire Wire Line
	9100 5850 8800 5850
Wire Wire Line
	9100 5950 8800 5950
Wire Wire Line
	9100 6050 8800 6050
Wire Wire Line
	9100 4350 8800 4350
Wire Wire Line
	9100 4250 8800 4250
Wire Wire Line
	9100 4150 8800 4150
Wire Wire Line
	9100 4050 8800 4050
Wire Wire Line
	9100 3950 8800 3950
Wire Wire Line
	9100 3850 8800 3850
Entry Wire Line
	10300 4550 10400 4650
Entry Wire Line
	10300 4650 10400 4750
Entry Wire Line
	10300 4750 10400 4850
Entry Wire Line
	10300 4850 10400 4950
Entry Wire Line
	10300 4950 10400 5050
Entry Wire Line
	10300 5050 10400 5150
Entry Wire Line
	10300 5150 10400 5250
Entry Wire Line
	10300 5250 10400 5350
Entry Wire Line
	10300 5350 10400 5450
Entry Wire Line
	10300 5450 10400 5550
Entry Wire Line
	10300 5550 10400 5650
Entry Wire Line
	10300 5650 10400 5750
Entry Wire Line
	10300 5750 10400 5850
Entry Wire Line
	10300 5850 10400 5950
Entry Wire Line
	10300 5950 10400 6050
Entry Wire Line
	10300 6050 10400 6150
Entry Wire Line
	8700 6150 8800 6050
Entry Wire Line
	8700 6050 8800 5950
Entry Wire Line
	8700 5950 8800 5850
Entry Wire Line
	8700 5850 8800 5750
Entry Wire Line
	8700 5750 8800 5650
Entry Wire Line
	8700 5650 8800 5550
Entry Wire Line
	8700 5550 8800 5450
Entry Wire Line
	8700 5450 8800 5350
Entry Wire Line
	8700 5350 8800 5250
Entry Wire Line
	8700 5250 8800 5150
Entry Wire Line
	8700 5150 8800 5050
Entry Wire Line
	8700 5050 8800 4950
Entry Wire Line
	8700 4950 8800 4850
Entry Wire Line
	8700 4850 8800 4750
Entry Wire Line
	8700 4750 8800 4650
Entry Wire Line
	8700 4550 8800 4450
Entry Wire Line
	8700 4450 8800 4350
Entry Wire Line
	8700 4350 8800 4250
Entry Wire Line
	8700 4250 8800 4150
Entry Wire Line
	8700 4150 8800 4050
Entry Wire Line
	8700 4050 8800 3950
Text Label 10150 4550 0    50   ~ 0
D0
Text Label 10150 4650 0    50   ~ 0
D1
Text Label 10150 4750 0    50   ~ 0
D2
Text Label 10150 4850 0    50   ~ 0
D3
Text Label 10150 4950 0    50   ~ 0
D4
Text Label 10150 5050 0    50   ~ 0
D5
Text Label 10150 5150 0    50   ~ 0
D6
Text Label 10150 5250 0    50   ~ 0
D7
Text Label 10150 5350 0    50   ~ 0
D8
Text Label 10150 5450 0    50   ~ 0
D9
Text Label 10150 5550 0    50   ~ 0
D10
Text Label 10150 5650 0    50   ~ 0
D11
Text Label 10150 5750 0    50   ~ 0
D12
Text Label 10150 5850 0    50   ~ 0
D13
Text Label 10150 5950 0    50   ~ 0
D14
Text Label 10150 6050 0    50   ~ 0
D15
Text Label 8800 4650 0    50   ~ 0
A1
Text Label 8800 4750 0    50   ~ 0
A2
Text Label 8800 4850 0    50   ~ 0
A3
Text Label 8800 4950 0    50   ~ 0
A4
Text Label 8800 5050 0    50   ~ 0
A5
Text Label 8800 5150 0    50   ~ 0
A6
Text Label 8800 5250 0    50   ~ 0
A7
Text Label 8800 5350 0    50   ~ 0
A8
Text Label 8800 5450 0    50   ~ 0
A9
Text Label 8800 5550 0    50   ~ 0
A10
Text Label 8800 5650 0    50   ~ 0
A11
Text Label 8800 5750 0    50   ~ 0
A12
Text Label 8800 5850 0    50   ~ 0
A13
Text Label 8800 5950 0    50   ~ 0
A14
Text Label 8800 6050 0    50   ~ 0
A15
Text Label 8800 4350 0    50   ~ 0
DQM1
Text Label 8800 4250 0    50   ~ 0
DQM0
Text Label 8800 4150 0    50   ~ 0
CKE
Text Label 8800 4050 0    50   ~ 0
~WE
Text Label 8800 3950 0    50   ~ 0
~CAS
Text Label 8800 3850 0    50   ~ 0
~RAS
Wire Bus Line
	10400 6300 10300 6400
Wire Bus Line
	10300 6400 8800 6400
Wire Bus Line
	8800 6400 8700 6300
Wire Bus Line
	8200 3850 8100 3950
Entry Wire Line
	5400 1300 5500 1400
$Sheet
S 9100 3700 900  2500
U 5C7DD4AF
F0 "SDRAM" 50
F1 "SDRAM.sch" 50
F2 "~RAS" I L 9100 3850 50 
F3 "~CAS" I L 9100 3950 50 
F4 "~WE" I L 9100 4050 50 
F5 "CKE" I L 9100 4150 50 
F6 "DQM0" I L 9100 4250 50 
F7 "DQM1" I L 9100 4350 50 
F8 "A1" I L 9100 4650 50 
F9 "A2" I L 9100 4750 50 
F10 "A3" I L 9100 4850 50 
F11 "A4" I L 9100 4950 50 
F12 "A5" I L 9100 5050 50 
F13 "A6" I L 9100 5150 50 
F14 "A7" I L 9100 5250 50 
F15 "A8" I L 9100 5350 50 
F16 "A9" I L 9100 5450 50 
F17 "A10" I L 9100 5550 50 
F18 "A11" I L 9100 5650 50 
F19 "A12" I L 9100 5750 50 
F20 "A13" I L 9100 5850 50 
F21 "A14" I L 9100 5950 50 
F22 "A15" I L 9100 6050 50 
F23 "D0" B R 10000 4550 50 
F24 "D1" B R 10000 4650 50 
F25 "D2" B R 10000 4750 50 
F26 "D3" B R 10000 4850 50 
F27 "D4" B R 10000 4950 50 
F28 "D5" B R 10000 5050 50 
F29 "D6" B R 10000 5150 50 
F30 "D7" B R 10000 5250 50 
F31 "D8" B R 10000 5350 50 
F32 "D9" B R 10000 5450 50 
F33 "D10" B R 10000 5550 50 
F34 "D11" B R 10000 5650 50 
F35 "D12" B R 10000 5750 50 
F36 "D13" B R 10000 5850 50 
F37 "D14" B R 10000 5950 50 
F38 "D15" B R 10000 6050 50 
F39 "SDCLK" U L 9100 4450 50 
F40 "~SDCS" U L 9100 4550 50 
$EndSheet
Wire Wire Line
	8800 4450 9100 4450
Entry Wire Line
	8700 3950 8800 3850
Wire Bus Line
	8700 3950 8600 3850
Wire Bus Line
	8600 3850 8200 3850
Wire Wire Line
	4800 2300 5400 2300
Entry Wire Line
	5400 2300 5500 2400
Text Label 5050 2300 2    50   ~ 0
~SDCS
Text Label 9050 4450 2    50   ~ 0
SDCLK
Wire Wire Line
	8800 4550 9100 4550
Entry Wire Line
	8700 4650 8800 4550
Text Label 9000 4550 2    50   ~ 0
~SDCS
Wire Wire Line
	6350 5600 5900 5600
Wire Wire Line
	6350 5700 5900 5700
Wire Wire Line
	6350 5800 6300 5800
Text Label 6050 5600 0    50   ~ 0
SPCKA
Text Label 6050 5700 0    50   ~ 0
MOSIA
Text Label 6050 5800 0    50   ~ 0
MISOA
Wire Wire Line
	6350 5500 5900 5500
Text Label 6050 5500 0    50   ~ 0
SSLA
$Sheet
S 2500 6000 850  1400
U 5C785170
F0 "WIFI" 50
F1 "WIFI.sch" 50
F2 "SSLA" I L 2500 6150 50 
F3 "SPCLK" I L 2500 6250 50 
F4 "MOSI" I L 2500 6350 50 
F5 "MISO" I L 2500 6450 50 
$EndSheet
Entry Wire Line
	5800 5600 5900 5500
Entry Wire Line
	5800 5700 5900 5600
Entry Wire Line
	5800 5800 5900 5700
Entry Wire Line
	5800 5900 5900 5800
Wire Bus Line
	5800 7400 5700 7500
Entry Wire Line
	2100 6250 2200 6150
Entry Wire Line
	2100 6350 2200 6250
Entry Wire Line
	2100 6450 2200 6350
Entry Wire Line
	2100 6550 2200 6450
Text Label 2200 6150 0    50   ~ 0
SSLA
Text Label 2200 6250 0    50   ~ 0
SPCKA
Text Label 2200 6350 0    50   ~ 0
MOSIA
Text Label 2200 6450 0    50   ~ 0
MISOA
Wire Wire Line
	2200 6150 2500 6150
Wire Wire Line
	2500 6250 2200 6250
Wire Wire Line
	2200 6350 2500 6350
Wire Wire Line
	2500 6450 2200 6450
Wire Bus Line
	5700 7500 2200 7500
Wire Bus Line
	2200 7500 2100 7400
Wire Wire Line
	5700 5700 3050 5700
Entry Wire Line
	2950 5600 3050 5700
Wire Wire Line
	5700 2000 6350 2000
Wire Wire Line
	5700 2000 5700 5700
$Comp
L board-rescue:CRYSTAL-akizuki-board-rescue X?
U 1 1 5C8A37E5
P 2850 1800
F 0 "X?" V 2750 1700 60  0000 C CNN
F 1 "32.768KHz" V 3000 2050 60  0000 C CNN
F 2 "" V 2850 1800 60  0000 C CNN
F 3 "" V 2850 1800 60  0000 C CNN
	1    2850 1800
	0    1    1    0   
$EndComp
$Comp
L board-rescue:CRYSTAL-akizuki-board-rescue X?
U 1 1 5C8A384B
P 2850 2400
F 0 "X?" V 2750 2300 60  0000 C CNN
F 1 "12MHz" V 2750 2650 60  0000 C CNN
F 2 "" V 2850 2400 60  0000 C CNN
F 3 "" V 2850 2400 60  0000 C CNN
	1    2850 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 1800 3100 1800
Wire Wire Line
	3400 2000 2600 2000
Wire Wire Line
	2600 2000 2600 1800
Wire Wire Line
	2600 1800 2700 1800
$Comp
L board-rescue:C-akizuki-board-rescue C?
U 1 1 5C8E5EA4
P 2300 2000
F 0 "C?" V 2200 1850 60  0000 C CNN
F 1 "18pF" V 2200 2150 60  0000 C CNN
F 2 "" V 2300 2000 60  0000 C CNN
F 3 "" V 2300 2000 60  0000 C CNN
	1    2300 2000
	0    1    1    0   
$EndComp
$Comp
L board-rescue:C-akizuki-board-rescue C?
U 1 1 5C8E5EFC
P 2300 2200
F 0 "C?" V 2200 2050 60  0000 C CNN
F 1 "8pF" V 2200 2350 60  0000 C CNN
F 2 "" V 2300 2200 60  0000 C CNN
F 3 "" V 2300 2200 60  0000 C CNN
	1    2300 2200
	0    1    1    0   
$EndComp
$Comp
L board-rescue:C-akizuki-board-rescue C?
U 1 1 5C8E5F61
P 2300 1650
F 0 "C?" V 2200 1500 60  0000 C CNN
F 1 "18pF" V 2200 1800 60  0000 C CNN
F 2 "" V 2300 1650 60  0000 C CNN
F 3 "" V 2300 1650 60  0000 C CNN
	1    2300 1650
	0    1    1    0   
$EndComp
$Comp
L board-rescue:C-akizuki-board-rescue C?
U 1 1 5C8E5FDF
P 2300 2550
F 0 "C?" V 2200 2400 60  0000 C CNN
F 1 "8pF" V 2200 2700 60  0000 C CNN
F 2 "" V 2300 2550 60  0000 C CNN
F 3 "" V 2300 2550 60  0000 C CNN
	1    2300 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 2400 3100 2400
Wire Wire Line
	2700 2400 2600 2400
Wire Wire Line
	2600 2400 2600 2200
Wire Wire Line
	2600 2200 3400 2200
Wire Wire Line
	2600 2200 2450 2200
Connection ~ 2600 2200
Wire Wire Line
	2600 2000 2450 2000
Connection ~ 2600 2000
Wire Wire Line
	2450 1650 3100 1650
Wire Wire Line
	3100 1650 3100 1800
Connection ~ 3100 1800
Wire Wire Line
	3100 1800 3000 1800
Wire Wire Line
	2450 2550 3100 2550
Wire Wire Line
	3100 2550 3100 2400
Connection ~ 3100 2400
Wire Wire Line
	3100 2400 3000 2400
Wire Wire Line
	2150 1650 2000 1650
Wire Wire Line
	2000 1650 2000 2000
Wire Wire Line
	2000 2000 2150 2000
Wire Wire Line
	2150 2200 2000 2200
Wire Wire Line
	2000 2200 2000 2000
Connection ~ 2000 2000
Wire Wire Line
	2150 2550 2000 2550
Wire Wire Line
	2000 2550 2000 2200
Connection ~ 2000 2200
Wire Wire Line
	2000 2550 2000 2650
Connection ~ 2000 2550
$Comp
L power:GND #PWR?
U 1 1 5C978BA5
P 2000 2650
F 0 "#PWR?" H 2000 2400 50  0001 C CNN
F 1 "GND" H 2005 2477 50  0000 C CNN
F 2 "" H 2000 2650 50  0001 C CNN
F 3 "" H 2000 2650 50  0001 C CNN
	1    2000 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1500 3100 1500
Wire Wire Line
	3400 1400 3100 1400
Wire Wire Line
	3400 1300 3100 1300
Text Label 3150 1300 0    50   ~ 0
~RES
Text Label 3150 1400 0    50   ~ 0
MD
Text Label 3150 1500 0    50   ~ 0
EMLE
Entry Wire Line
	3000 1200 3100 1300
Entry Wire Line
	3000 1300 3100 1400
Entry Wire Line
	3000 1400 3100 1500
Entry Wire Line
	8100 3200 8200 3100
Entry Wire Line
	8100 3300 8200 3200
Entry Wire Line
	8100 3400 8200 3300
Entry Wire Line
	8100 3500 8200 3400
Entry Wire Line
	8100 3600 8200 3500
Wire Wire Line
	9100 2550 8750 2550
Wire Wire Line
	9100 2650 8750 2650
Wire Wire Line
	9100 2750 8750 2750
Wire Wire Line
	9100 2850 8750 2850
Wire Wire Line
	9100 2950 8750 2950
Wire Wire Line
	9100 3050 8750 3050
Wire Wire Line
	9100 3150 8750 3150
Wire Wire Line
	9100 3250 8750 3250
Text Label 8800 2550 0    50   ~ 0
~RES
Text Label 8800 2650 0    50   ~ 0
MD
Text Label 8800 2750 0    50   ~ 0
EMLE
Text Label 8800 2850 0    50   ~ 0
TDO
Text Label 8800 2950 0    50   ~ 0
TCK
Text Label 8800 3050 0    50   ~ 0
TDI
Text Label 8800 3150 0    50   ~ 0
TMS
Text Label 8800 3250 0    50   ~ 0
~TRST
Entry Wire Line
	8650 2650 8750 2550
Entry Wire Line
	8650 2750 8750 2650
Entry Wire Line
	8650 2850 8750 2750
Entry Wire Line
	8650 2950 8750 2850
Entry Wire Line
	8650 3050 8750 2950
Entry Wire Line
	8650 3150 8750 3050
Entry Wire Line
	8650 3250 8750 3150
Entry Wire Line
	8650 3350 8750 3250
Wire Bus Line
	8650 3600 8550 3700
Wire Bus Line
	8550 3700 8300 3700
Wire Bus Line
	8300 3700 8200 3600
Wire Bus Line
	8200 850  8100 750 
Wire Bus Line
	8100 750  3100 750 
Wire Bus Line
	3100 750  3000 850 
Wire Wire Line
	6300 5800 6300 6100
Connection ~ 6300 5800
Wire Wire Line
	6300 5800 5900 5800
Wire Wire Line
	9100 3350 8750 3350
Wire Wire Line
	8750 3350 8750 3750
Wire Wire Line
	8550 3750 8550 6100
Wire Wire Line
	8550 3750 8750 3750
Wire Wire Line
	8550 6100 6300 6100
$Sheet
S 650  1700 850  900 
U 5E7FE04C
F0 "USB_IF" 50
F1 "USB_IF.sch" 50
F2 "USB_DP" U R 1500 2100 50 
F3 "USB_DM" U R 1500 2200 50 
$EndSheet
Wire Wire Line
	3400 2600 2600 2600
Wire Wire Line
	2600 2600 2600 2900
Wire Wire Line
	2600 2900 1850 2900
Wire Wire Line
	1850 2900 1850 2100
Wire Wire Line
	1850 2100 1500 2100
Wire Wire Line
	3400 2700 2700 2700
Wire Wire Line
	2700 2700 2700 2950
Wire Wire Line
	2700 2950 1800 2950
Wire Wire Line
	1800 2950 1800 2200
Wire Wire Line
	1800 2200 1500 2200
Wire Wire Line
	4800 1300 5400 1300
Wire Bus Line
	3000 850  3000 1400
Wire Bus Line
	5900 1100 5900 1500
Wire Bus Line
	5800 5600 5800 7400
Wire Bus Line
	2100 6250 2100 7400
Wire Bus Line
	2950 4600 2950 5600
Wire Bus Line
	8200 850  8200 3600
Wire Bus Line
	5500 1400 5500 3150
Wire Bus Line
	2400 4650 2400 5600
Wire Bus Line
	8650 2650 8650 3600
Wire Bus Line
	5300 1100 5300 7050
Wire Bus Line
	6000 3350 6000 6150
Wire Bus Line
	10400 4650 10400 6300
Wire Bus Line
	8100 3950 8100 6150
Wire Bus Line
	8700 3950 8700 6300
$EndSCHEMATC
