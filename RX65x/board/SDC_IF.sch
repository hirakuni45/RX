EESchema Schematic File Version 4
LIBS:board-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 8
Title ""
Date ""
Rev ""
Comp "G.P.L."
Comment1 "hira@rvf-rc45.net"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3050 3600 0    50   Input ~ 0
SD_CMD
Text GLabel 3050 3300 0    50   Input ~ 0
SD_CLK
Text GLabel 3050 3100 0    50   Input ~ 0
SD_D0
Text GLabel 3050 3000 0    50   Input ~ 0
SD_D1
Text GLabel 3050 3800 0    50   Input ~ 0
SD_D2
Text GLabel 3050 3700 0    50   Input ~ 0
SD_D3
Text GLabel 3050 2600 0    50   Input ~ 0
SD_WP
Text GLabel 3050 2800 0    50   Input ~ 0
SD_CD
$Comp
L board-rescue:SD-CARD-SOCKET-akizuki CN1
U 1 1 5C7298FC
P 4300 3200
F 0 "CN1" H 4578 3253 60  0000 L CNN
F 1 "SD-CARD-SOCKET" H 4578 3147 60  0000 L CNN
F 2 "" H 4225 3125 60  0000 C CNN
F 3 "" H 4225 3125 60  0000 C CNN
	1    4300 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2600 3850 2600
Wire Wire Line
	3050 2800 3850 2800
Wire Wire Line
	3050 3000 3850 3000
Wire Wire Line
	3050 3100 3850 3100
Wire Wire Line
	3050 3800 3850 3800
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C7AFF66
P 3350 3300
F 0 "R?" H 3350 3200 50  0000 C CNN
F 1 "22" H 3350 3300 50  0000 C CNN
F 2 "" V 3280 3300 50  0000 C CNN
F 3 "" H 3350 3300 50  0000 C CNN
	1    3350 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3500 3300 3850 3300
Wire Wire Line
	3200 3300 3050 3300
Wire Wire Line
	3850 3700 3050 3700
$Comp
L board-rescue:R-akizuki R?
U 1 1 5C7B011C
P 3350 3600
F 0 "R?" H 3350 3500 50  0000 C CNN
F 1 "22" H 3350 3600 50  0000 C CNN
F 2 "" V 3280 3600 50  0000 C CNN
F 3 "" H 3350 3600 50  0000 C CNN
	1    3350 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	3050 3600 3200 3600
Wire Wire Line
	3500 3600 3850 3600
Wire Wire Line
	3850 3500 3750 3500
Wire Wire Line
	3750 3500 3750 3200
Wire Wire Line
	3750 3200 3850 3200
Wire Wire Line
	3750 3500 3750 4050
Connection ~ 3750 3500
$Comp
L power:GND #PWR?
U 1 1 5C7B04D3
P 3750 4050
F 0 "#PWR?" H 3750 3800 50  0001 C CNN
F 1 "GND" H 3755 3877 50  0000 C CNN
F 2 "" H 3750 4050 50  0001 C CNN
F 3 "" H 3750 4050 50  0001 C CNN
	1    3750 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3200 3750 2700
Wire Wire Line
	3750 2700 3850 2700
Connection ~ 3750 3200
Wire Wire Line
	3850 3400 3650 3400
Wire Wire Line
	3650 3400 3650 2350
$Comp
L power:+3.3V #PWR?
U 1 1 5C7B07B9
P 3650 2350
F 0 "#PWR?" H 3650 2200 50  0001 C CNN
F 1 "+3.3V" H 3665 2523 50  0000 C CNN
F 2 "" H 3650 2350 50  0001 C CNN
F 3 "" H 3650 2350 50  0001 C CNN
	1    3650 2350
	1    0    0    -1  
$EndComp
$Comp
L board-rescue:C-akizuki C?
U 1 1 5C745830
P 5650 3200
F 0 "C?" H 5732 3253 60  0000 L CNN
F 1 "22uF" H 5732 3147 60  0000 L CNN
F 2 "" V 5650 3200 60  0000 C CNN
F 3 "" V 5650 3200 60  0000 C CNN
	1    5650 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3050 5650 2750
Wire Wire Line
	5650 3350 5650 3650
$Comp
L power:GND #PWR?
U 1 1 5C745D0D
P 5650 3650
F 0 "#PWR?" H 5650 3400 50  0001 C CNN
F 1 "GND" H 5655 3477 50  0000 C CNN
F 2 "" H 5650 3650 50  0001 C CNN
F 3 "" H 5650 3650 50  0001 C CNN
	1    5650 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C745D3E
P 5650 2750
F 0 "#PWR?" H 5650 2600 50  0001 C CNN
F 1 "+3.3V" H 5665 2923 50  0000 C CNN
F 2 "" H 5650 2750 50  0001 C CNN
F 3 "" H 5650 2750 50  0001 C CNN
	1    5650 2750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
