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
Sheet 1 4
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
S 4200 2900 2150 2000
U 598D65C7
F0 "RX24T_base" 60
F1 "RX24T_base.sch" 60
F2 "TXD" I L 4200 3400 60 
F3 "RXD" O L 4200 3600 60 
F4 "MISO" I R 6350 3100 60 
F5 "MOSI" O R 6350 3200 60 
F6 "SPI_CLK" O R 6350 3300 60 
F7 "SD_CS" O R 6350 3400 60 
$EndSheet
$Sheet
S 1000 2900 2000 2000
U 598D660F
F0 "FTDI_serial" 60
F1 "FTDI_serial.sch" 60
F2 "TXD" O R 3000 3400 60 
F3 "RXD" I R 3000 3600 60 
$EndSheet
Wire Wire Line
	3000 3400 4200 3400
Wire Wire Line
	4200 3600 3000 3600
$Sheet
S 7050 2900 1800 2000
U 598D90D8
F0 "SDC_if" 60
F1 "SDC_if.sch" 60
F2 "MISO" O L 7050 3100 60 
F3 "MOSI" I L 7050 3200 60 
F4 "SPI_CLK" I L 7050 3300 60 
F5 "SD_CS" I L 7050 3400 60 
$EndSheet
Wire Wire Line
	7050 3100 6350 3100
Wire Wire Line
	7050 3200 6350 3200
Wire Wire Line
	6350 3300 7050 3300
Wire Wire Line
	6350 3400 7050 3400
$EndSCHEMATC
