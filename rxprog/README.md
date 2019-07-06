Renesas RX microcontroller flash programming tool (rx_prog)
=========
![R5F564ML](../docs/RX600_group.jpg)

[Japanese](READMEja.md)

## Overview
Tool to write program to flash memory of RX microcontroller using serial interface
   
---
## Project list
 - main.cpp
 - area.hpp
 - conf_in.hpp
 - file_io.cpp
 - file_io.hpp
 - motsx_io.hpp
 - rs232c_io.hpp
 - rx_prog.hpp
 - rx_protocol.hpp
 - rx24t_protocol.hpp
 - rx63t_protocol.hpp
 - rx64m_protocol.hpp
 - rx65x_protocol.hpp
 - rx66t_protocol.hpp
 - sjis_utf16.cpp
 - sjis_utf16.hpp
 - string_utils.cpp
 - string_utils.hpp
 - Makefile
 - rx_prog.conf
   
---
## Preparation of build (compilation) environment (Windows)
 - MSYS2 setup
 - gcc related installation
 - Install boost (use pacman to install for mingw64 environment)
   
See development environment preparation of 'RX/README.md'
   
---
## Build method, environment setting
 - make
 - Copy configuration file and executable file by make install
 - pass the path to / usr / local / bin
   
---
## Connection preparation (serial connection)
- Connect the VSS pin of the microcontroller to the GND of USB serial.
- Connect the RXD1 pin on the microcontroller side with the USB serial TXD.
- Connect the TXD1 pin on the microcontroller side with the USB serial RXD.
※SCI port at boot (usually SCI1, hardware manual for confirmation)   
- Pull down if the device has a UB terminal. (4.7K)
- Pull down if there is an EMLE terminal. (4.7K)
- Set the MD terminal to "Low" and input the "Reset" signal.
- When executing an internal program, set the MD pin to "High level" and input reset signal.
   
---
## Connection terminal list
|Terminal|RX24T (100 Pin)|RX66T (100 Pin)|RX64M (176 Pin)|RX71M (176 Pin)|RX65N (176 Pin)|
|---|---|---|---|---|---|
|UB|X|UB/P00 (4)|PC7/UB (76)|PC7/UB (76)|PC7/UB (76)|
|MD|MD (6)|MD/FINED (6)|MD/FINED (18)|MD/FINED (18)|MD/FINED (18)|
|EMLE|X|EMLE (2)|EMLE (10)|EMLE (10)|EMLE (10)|
|RXD|PD5/RXD1 (20)|PD5/RXD1 (20)|PF2/RXD1 (31)|PF2/RXD1 (31)|PF2/RXD1 (31)|
|TXD|PD3/TXD1 (22)|PD3/TXD1 (22)|PF0/TXD1 (35)|PF0/TXD1 (35)|PF0/TXD1 (35)|
   
- UB, MD, and EMLE terminals are pulled up or down with a resistor (approximately 4.7K).
- Connect appropriate crystals to XTAL and EXTAL.
- Connect all the power supplies such as VSS, VCC, AVSS, AVCC etc.
- Connect USB power sources such as USB_VSS and USB_VCC properly.
   
※For details, refer to the hardware manual for each device, "Overview, Pin Assignment", "Flash Memory, Boot Mode".   
※The circuit diagram of the Renesas board is available for reference.   
   
---
## Method of operation
![R5F564ML](../docs/USB_Serial.jpg)
### Confirm start of rx_prog
 - Run rx_prog and verify that it works (help is listed)
```
rx_prog
Renesas RX Series Programmer Version 1.10b
Copyright (C) 2016,2019 Hiramatsu Kunihito (hira@rvf-rc45.net)
usage:
rx_prog [options] [mot file] ...

Options :
    -P PORT,   --port=PORT     Specify serial port
    -s SPEED,  --speed=SPEED   Specify serial speed
    -d DEVICE, --device=DEVICE Specify device name
    -e, --erase                Perform a device erase to a minimum
    -v, --verify               Perform data verify
    -w, --write                Perform data write
    --progress                 display Progress output
    --device-list              Display device list
    --verbose                  Verbose output
    -h, --help                 Display this
```
   
### rx_prog.conf settings
 - Describe the settings of each device, port, baud rate, and so on.
 - You can specify the serial device port path individually so that settings can be shared between platforms.
 - Set the port name, baud rate, etc. according to your environment.
   
rx_prog.conf configuration example
```
# Standard serial port, platform dependent port name
# port_win, port_osx and port_linux are recognized by platform and take precedence over port.
#port = /dev/ttyS10
#port = COM12
port_win   = COM3
port_osx   = /dev/tty.usbserial-DA00X2QP
port_linux = /dev/ttyUSB0

# Standard serial speed, platform dependent speed
# speed_win, speed_osx and speed_linux are recognized by platform and take precedence over speed.
# ※The maximum speed that can be set varies depending on the platform.
#speed = 230400
speed_win = 230400
speed_osx = 230400
speed_linux = 230400
```
rx_prog.conf is scanned and loaded in the following order:   
- Current directory
- Command directory (usually /usr/local/bin)
   
Supported device list display
```
rx_prog --device-list
R5F563T6 (RAM: 8K, Program-Flash: 64K, Data-Flash: 8K)
R5F524T8 (RAM: 16K, Program-Flash: 128K, Data-Flash: 8K)
R5F524TA (RAM: 16K, Program-Flash: 256K, Data-Flash: 8K)
R5F564MF (RAM: 512K, Program-Flash: 2048K, Data-Flash: 64K)
R5F5671F (RAM: 512K, Program-Flash: 2048K, Data-Flash: 64K)
R5F564MG (RAM: 512K, Program-Flash: 2560K, Data-Flash: 64K)
R5F571MG (RAM: 512K, Program-Flash: 2560K, Data-Flash: 64K)
R5F564MJ (RAM: 512K, Program-Flash: 3072K, Data-Flash: 64K)
R5F571MJ (RAM: 512K, Program-Flash: 3072K, Data-Flash: 64K)
R5F564ML (RAM: 512K, Program-Flash: 4096K, Data-Flash: 64K)
R5F571ML (RAM: 512K, Program-Flash: 4096K, Data-Flash: 64K)
R5F565NE (RAM: 640K, Program-Flash: 2048K, Data-Flash: 32K)
R5F566TA (RAM: 64K, Program-Flash: 256K, Data-Flash: 32K)
R5F566TE (RAM: 64K, Program-Flash: 512K, Data-Flash: 32K)
R5F566TF (RAM: 128K, Program-Flash: 512K, Data-Flash: 32K)
R5F566TK (RAM: 128K, Program-Flash: 1024K, Data-Flash: 32K)
```
   
### Connection check
![R5F564ML](../docs/RX_boards.jpg)
```
rx_prog -d RX71M --verbose
# Platform: 'Cygwin'
# Configuration file path: '/usr/local/bin/rx_prog.conf'
# Device: 'RX71M'
# Serial port path: 'COM3'
# Serial port speed: 230400
# Serial port alias: COM3 ---> /dev/ttyS2
# Serial port path: '/dev/ttyS2'
# Connection OK.
#01/01: Device Type TYP: 20 02 FD 09 01 48 40 00
#01/01: Device Type OSA: 16000000
#01/01: Device Type OSI: 16000000
#01/01: Device Type CPA: 120000000
#01/01: Device Type CPI: 120000000
#01/01: Endian is little.
#01/01: System clock: 120000000
#01/01: Device clock: 60000000
#01/01: Change baud rate: 230400
#01/01: ID: Disable
```
   
### Erase, write, compare (with progress bar, "test_sample.mot" file)
```
rx_prog -d RX71M --progress --write --verify test_sample.mot
Erase:  #################################################
Write:  #################################################
Verify: #################################################
```
   
---
### Delete unnecessary serial port (Windows)
```
set devmgr_show_nonpresent_devices=1
start devmgmt.msc
```
   
- Remove all USB serial devices from your computer.
- Create a BAT file as above, right click and execute with "administrator privileges".
- Check "Display"-"Display Hidden Device".
- Delete unused COM ports.
- Once again, connect USB serial devices to the computer in order.
   
※In the case of the same maker device, since the change of COM port number etc. occur after the second one, it is necessary to take measures such as changing the internal serial ID number with a maker's dedicated tool depending on the situation.
※Please check with the device manufacturer's HP regarding the use of dedicated tools.
   
---
### Difference between FT232RL, FT231XS and CP2102
FT231XS, FT232RL:
```
Neptune./d/Git/RX/RAYTRACER_sample/RX66T % time rx_prog -d RX66T --progress --erase --write --verify raytracer_sample.mot
Erase:  #################################################
Write:  #################################################
Verify: #################################################

real    0m16.617s
user    0m0.202s
sys     0m0.421s
```
   
CP2102:
```
Neptune./d/Git/RX/RAYTRACER_sample/RX66T % time rx_prog -P COM12 -d RX66T --progress --erase --write --verify raytracer_sample.mot
Erase:  #################################################
Write:  #################################################
Verify: #################################################

real    0m6.616s
user    0m0.078s
sys     0m0.187s
```
   
※FTDI devices seem to be slower than silicon lab devices.
   
-----
   
License
----

MIT
