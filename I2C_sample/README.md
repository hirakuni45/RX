Renesas RX62N, RX24T, RX64M, RX71M, RX65N, RX66T, RX72N I2C sample
=========

[Japanese](READMEja.md)

## Overview

- Sample program for I2C using RX microcontroller
- It is possible to interactively check and control the communication with I2C devices through a serial connection to a terminal.
- Dedicated commands are available for communication with the I2C devices shown in "list".
- Multiple peripherals such as IICA and SCI_I2C can be switched.
   
## Project list

 - main.cpp
 - exec_cmd.hap
 - BMP280_exec.hpp
 - DS3231_exec.hpp
 - EEPROM_exec.hpp
 - RX24T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
 - RX66T/Makefile
 - RX72N/Makefile
   
## Prepare your hardware resources.

- Connect the specified I2C signal to the I2C device.
- Set the pull-up resistor accordingly.
- Pay close attention to the voltage to be used.

|I2C Device|Manufacturer|Functions|
|-----------|-------|----|
|BMP280     |Bosch Sensotec|Pressure Sensor|
|DS3231     |Maxim Integrated|Real Time Clock|
|EEPROM[0-7]|Micro Chip|EEPROM|
   
## Build method

 - Go to each platform directory and make it.
 - Write the I2C_sample.mot file.

## Operation

- LED indicator blinks.
- A serial terminal can be connected for interactive operation.

## I2C Master Command

|command|function|
|-------|----|
|list|display of supported devices|
|scan [start=0] [end=127]|Scan for connected I2C devices|
|exec I2C-name|list Launch the displayed device operation|
|adr [X]|set I2C address|
|r [num=1]|display num bytes from device|
|s data...|Write data to the device|

If you start with exec, return with 'exit'.

## BMP280 command

|command|function|
|-------|----|
|list|display temperature, pressure, and elevation|

## DS3231 Command

|command|function|
|-------|----|
|date|display date, time|
|date yyyy/mm/dd hh:mm[:ss]|set date, time|

## EEPROM Commands

|command|function|
|-------|----|
|read ORG [END=+16]|read data from EEPROM and display it|
|write ORG DATA... |Write data to EEPROM|

-----
   
License
----

MIT
