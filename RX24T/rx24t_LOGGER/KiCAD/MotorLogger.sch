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
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 4200 2900 2200 3400
U 598D65C7
F0 "RX24T_base" 60
F1 "RX24T_base.sch" 60
F2 "RXD1" I L 4200 3100 60 
F3 "TXD1" O L 4200 3200 60 
F4 "MISO" I R 6400 3100 60 
F5 "MOSI" O R 6400 3200 60 
F6 "SDC_CK" O R 6400 3300 60 
F7 "SDC_CS" O R 6400 3400 60 
F8 "SDC_WP" I R 6400 3500 60 
F9 "SDC_POW" O R 6400 3600 60 
F10 "AN000" I R 6400 4050 60 
F11 "AN101" I R 6400 4150 60 
F12 "AN102" I R 6400 4250 60 
F13 "AN103" I R 6400 4350 60 
F14 "AN100" I R 6400 4450 60 
F15 "AN101" I R 6400 4550 60 
F16 "AN102" I R 6400 4650 60 
F17 "AN103" I R 6400 4750 60 
$EndSheet
$Sheet
S 2300 2900 1100 500 
U 598D660F
F0 "FTDI_serial" 60
F1 "FTDI_serial.sch" 60
F2 "TXD" O R 3400 3100 60 
F3 "RXD" I R 3400 3200 60 
$EndSheet
Wire Wire Line
	6400 3100 7050 3100
Wire Wire Line
	7050 3200 6400 3200
Wire Wire Line
	6400 3300 7050 3300
Wire Wire Line
	7050 3400 6400 3400
Wire Wire Line
	6400 3500 7050 3500
Wire Wire Line
	7050 3600 6400 3600
$Sheet
S 7050 2900 1200 800 
U 598D90D8
F0 "SDC_if" 60
F1 "SDC_if.sch" 60
F2 "SDC_OUT" O L 7050 3100 60 
F3 "SDC_INP" I L 7050 3200 60 
F4 "SDC_CK" I L 7050 3300 60 
F5 "SDC_CS" I L 7050 3400 60 
F6 "SDC_WP" O L 7050 3500 60 
F7 "SDC_POW" I L 7050 3600 60 
$EndSheet
$Sheet
S 7050 3950 1250 950 
U 5990FFB2
F0 "Analog" 60
F1 "Analog.sch" 60
F2 "AN0" O L 7050 4050 60 
F3 "AN1" O L 7050 4150 60 
F4 "AN2" O L 7050 4250 60 
F5 "AN3" O L 7050 4350 60 
F6 "AN4" O L 7050 4450 60 
F7 "AN5" O L 7050 4550 60 
F8 "AN6" O L 7050 4650 60 
F9 "AN7" O L 7050 4750 60 
$EndSheet
Wire Wire Line
	7050 4050 6400 4050
Wire Wire Line
	6400 4150 7050 4150
Wire Wire Line
	7050 4250 6400 4250
Wire Wire Line
	6400 4350 7050 4350
Wire Wire Line
	7050 4450 6400 4450
Wire Wire Line
	6400 4550 7050 4550
Wire Wire Line
	7050 4650 6400 4650
Wire Wire Line
	6400 4750 7050 4750
Wire Wire Line
	3400 3100 4200 3100
Wire Wire Line
	4200 3200 3400 3200
$EndSCHEMATC
