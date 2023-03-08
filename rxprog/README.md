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
 - rx220_protocol.hpp
 - rx24t_protocol.hpp
 - rx62x_protocol.hpp
 - rx63x_protocol.hpp
 - rx64m_protocol.hpp
 - rx65x_protocol.hpp
 - rx66t_protocol.hpp
 - rx72t_protocol.hpp
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
- Install boost 
- Since boost uses 1.74.0, please download it in advance (place it in D:\Download). (boost_1_74_0.tar.gz)
- Extract to the root of the C drive

```
cd /c/
tar xfvz /d/Download/boost_1_74_0.tar.gz
```
   
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
- MDE(13) is 0 (assumed little-endian)

---

## Connection terminal list

### RX220:
|Terminal|RX220 (64)|
|---|---|
|MD|MD(3)|
|B/UB|PC7(27)|
|RXD|P30/RXD1(14)|
|TXD|P26/TXD1(16)|

|Mode|B/UB|MD|
|---|:---:|:---:|
|Boot Mode|0|0|
|User Boot Mode|1|0|
|Single Chip|-|1|

---
### RX621/RX62N:
|Terminal|RX621/RX62N (144)|
|---|---|
|MD0|MD0(16)|
|MD1|MD1(15)|
|EMLE|EMLE(10)|
|RXD|P30/RXD1(29)|
|TXD|P26/TXD1(31)|
   
|Mode|MD0|MD1|
|---|---|---|
|Serial Boot|1|0|
|USB Boot|0|1|
|Single Chip|1|1|

---
### RX631/RX63N:
|Terminal|LQFP 48|LQFP 64|TFLGA 64|LQFP 100|TFLGA 100|LQFP 144|TFLGA 145|LQFP 176|LFBGA 176|TFLGA 177|
|---|---|---|---|---|---|---|---|---|---|---|
|UB|PC7(21)|PC7(27)|PA6(D5)|PC7(45)|PC7(H7)|PC7(60)|PC7(N9)|PC7(76)|PC7(N10)|PC7(N10)|
|MD|MD/FINED(2)|MD/FINED(3)|MD/FINED(C2)|MD/FINED(7)|MD/FINED(D3)|MD/FINED(16)|MD/FINED(G3)|MD/FINED(18)|MD/FINED(G3)|MD/FINED(G3)|
|EMLE|-|EMLE(1)|EMLE(C3)|EMLE(2)|EMLE(B1)|EMLE(10)|EMLE(E4)|EMLE(10)|EMLE(E2)|EMLE(E2)|
|RXD|P30/RXD1(10)|P30/RXD1(14)|P30/RXD1(E3)|P30/RXD1(20)|P30/RXD1(G3)|P30/RXD1(29)|P30/RXD1(J4)|PF2/RXD1(31)|PF2/RXD1(K3)|PF2/RXD1(K3)|
|TXD|P26/TXD1(12)|P26/TXD1(16)|P26/TXD1(G2)|P26/TXD1(22)|P26/RXD1(H1)|P26/RXD1(31)|P26/RXD1(K2)|PF0/RXD1(35)|PF0/RXD1(L3)|PF0/RXD1(L3)|

|Mode|UB|MD|
|---|:---:|:---:|
|Serial Boot|0|0|
|USB Boot|1|0|
|Single Chip|-|1|

---
### RX63T/RX24T/RX66T/RX72T:
|Terminal|RX63T (64)|RX24T (100)|RX66T (100)|RX72T (144)|
|---|---|---|---|------|
|UB|P00(2)|-|UB/P00(4)|UB/P00(9)|
|MD|MD(5)|MD(6)|MD/FINED(6)|MD/FINED(11)|
|EMLE|EMLE(1)|-|EMLE(2)|EMLE(7)|
|RXD|PD5/RXD1(14)|PD5/RXD1(20)|PD5/RXD1(20)|PD5/RXD1(25)|
|TXD|PD3/TXD1(16)|PD3/TXD1(22)|PD3/TXD1(22)|PD3/TXD1(27)|

|Mode|UB|MD|
|---|:---:|:---:|
|Serial Boot|0|0|
|USB Boot|1|0|
|Single Chip|-|1|

---
### RX64M/RX71M/RX651/RX65N:
|Terminal|RX64M (176)|RX71M (176)|RX651/RX65N (176)|
|---|---|---|---|
|UB|PC7/UB(76)|PC7/UB(76)|PC7/UB(76)|
|MD|MD/FINED(18)|MD/FINED(18)|MD/FINED(18)|
|EMLE|EMLE(10)|EMLE(10)|EMLE(10)|
|RXD|PF2/RXD1(31)|PF2/RXD1(31)|PF2/RXD1(31)|
|TXD|PF0/TXD1(35)|PF0/TXD1(35)|PF0/TXD1(35)|
   
|Mode|UB|MD|
|---|:---:|:---:|
|Serial Boot|0|0|
|USB Boot|1|0|
|Single Chip|-|1|

---

- MD0、MD1、UB、MD、B/UB, and EMLE terminals are pulled up or down with a resistor (approximately 4.7K).
- Connect appropriate crystals to XTAL and EXTAL.
- Connect the specified capacitor to VCL.
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
    --erase-page-wait=WAIT     Delay per read page  (2000) [uS]
    --write-page-wait=WAIT     Delay per write page (5000) [uS]
    --device-list              Display device list
    --verbose                  Verbose output
    -h, --help                 Display this
```
   
### rx_prog.conf settings
 - Describe the settings of each device, port, baud rate, and so on.
 - You can specify the serial device port path individually so that settings can be shared between platforms.
 - Set the port name, baud rate, etc. according to your environment.
 - For the RX62x, the error is limited to 115200 for high baud rates.
   
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

# erase-page command wait [uS]
erase_page_wait = 2000
# write-page command wait [uS]
write_page_wait = 5000
```
rx_prog.conf is scanned and loaded in the following order:   
- Current directory
- Command directory (usually /usr/local/bin)
- The RX621/RX62N internally limits the serial speed to 115200 due to high baud rate errors.
- For devices such as RX621/RX62N and RX63T, external connection crystal frequency and multiplier settings are required when connecting.
- The RX63T internally limits the serial speed to 115200 due to high baud rate errors.
- This is done in the configuration file as shown below.
- If there are multiple settings with the same group name, the first setting found in the group will take effect.

```
R5F56217 {
	group = "RX621"
	clock = 1200
	divide_sys = 8
	divide_ext = 4

...

}
```

---

### Supported device list display

```
 % rx_prog --device-list
R5F52206 (RX220): Program-Flash:  256K, RAM:   16K, Data-Flash:  8K
R5F56217 (RX621): Program-Flash:  384K, RAM:   64K, Data-Flash: 32K
R5F56218 (RX621): Program-Flash:  512K, RAM:   96K, Data-Flash: 32K
R5F562N7 (RX62N): Program-Flash:  384K, RAM:   64K, Data-Flash: 32K
R5F562N8 (RX62N): Program-Flash:  512K, RAM:   96K, Data-Flash: 32K
R5F5631F (RX631): Program-Flash: 2048K, RAM:  256K, Data-Flash: 32K
R5F563NF (RX63N): Program-Flash: 2048K, RAM:  256K, Data-Flash: 32K
R5F563T6 (RX63T): Program-Flash:   64K, RAM:    8K, Data-Flash:  8K
R5F524T8 (RX24T): Program-Flash:  128K, RAM:   16K, Data-Flash:  8K
R5F524TA (RX24T): Program-Flash:  256K, RAM:   16K, Data-Flash:  8K
R5F564MF (RX64M): Program-Flash: 2048K, RAM:  512K, Data-Flash: 64K
R5F5671F (RX71M): Program-Flash: 2048K, RAM:  512K, Data-Flash: 64K
R5F564MG (RX64M): Program-Flash: 2560K, RAM:  512K, Data-Flash: 64K
R5F571MG (RX71M): Program-Flash: 2560K, RAM:  512K, Data-Flash: 64K
R5F564MJ (RX64M): Program-Flash: 3072K, RAM:  512K, Data-Flash: 64K
R5F571MJ (RX71M): Program-Flash: 3072K, RAM:  512K, Data-Flash: 64K
R5F564ML (RX64M): Program-Flash: 4096K, RAM:  512K, Data-Flash: 64K
R5F571ML (RX71M): Program-Flash: 4096K, RAM:  512K, Data-Flash: 64K
R5F5651E (RX651): Program-Flash: 2048K, RAM:  640K, Data-Flash: 32K
R5F565NE (RX65N): Program-Flash: 2048K, RAM:  640K, Data-Flash: 32K
R5F566TA (RX66T): Program-Flash:  256K, RAM:   64K, Data-Flash: 32K
R5F566TE (RX66T): Program-Flash:  512K, RAM:   64K, Data-Flash: 32K
R5F566TF (RX66T): Program-Flash:  512K, RAM:  128K, Data-Flash: 32K
R5F566TK (RX66T): Program-Flash: 1024K, RAM:  128K, Data-Flash: 32K
R5F572MD (RX72M): Program-Flash: 2048K, RAM: 1024K, Data-Flash: 32K
R5F572MN (RX72M): Program-Flash: 4096K, RAM: 1024K, Data-Flash: 32K
R5F572TF (RX72T): Program-Flash:  512K, RAM:  128K, Data-Flash: 32K
R5F572TK (RX72T): Program-Flash: 1024K, RAM:  128K, Data-Flash: 32K
R5F572ND (RX72N): Program-Flash: 2048K, RAM: 1024K, Data-Flash: 32K
R5F572NN (RX72N): Program-Flash: 4096K, RAM: 1024K, Data-Flash: 32K
```
   
---

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
   
---

### Erase, write, compare (with progress bar, "test_sample.mot" file)
```
rx_prog -d RX71M --progress --write --verify test_sample.mot
Erase:  ################################################# 100 %
Write:  ################################################# 100 %
Verify: ################################################# 100 %
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
Erase:  ################################################# 100 %
Write:  ################################################# 100 %
Verify: ################################################# 100 %

real    0m16.617s
user    0m0.202s
sys     0m0.421s
```
   
CP2102:
```
Neptune./d/Git/RX/RAYTRACER_sample/RX66T % time rx_prog -P COM12 -d RX66T --progress --erase --write --verify raytracer_sample.mot
Erase:  ################################################# 100 %
Write:  ################################################# 100 %
Verify: ################################################# 100 %

real    0m6.616s
user    0m0.078s
sys     0m0.187s
```
   
※FTDI devices seem to be slower than silicon lab devices.

---

## RX62N Imprint and Capacity

- The "R5F562N7" with FRK-RX62N is listed in the catalog as a FlashROM: 384K and RAM: 64K item.
- However, when we performed a connection test, it reported a FlashROM area that does not normally exist, as shown below.

```
 % rx_prog -d RX62N --verbose
# Platform: 'Cygwin'
# Configuration file path: 'rx_prog.conf'
# Device: 'RX62N'
# Serial port path: 'COM7'
# Serial port speed: 230400
# Erase Page Wait: 2000 [uS]
# Write Page Wait: 5000 [uS]
# Serial port alias: COM7 ---> /dev/ttyS6
# Serial port path: '/dev/ttyS6'
Connection OK. (RX62x)
#01/01: Device: RX600 Series
#01/01: Device ID: 0x35307936
#01/01: Clock Mode: 0x00
#01/02: Multiplier: 1, 2, 4, 8
#02/02: Multiplier: 1, 2, 4, 8
#01/02: Frequency Min: 8 MHz, Max: 100 MHz
#02/02: Frequency Min: 8 MHz, Max: 50 MHz
#01/01: Change baud rate: 115200
#01/01: Boot Area: FF7FC000, FF7FFFFF
#01/01: Area: FFF80000, FFFFFFFF
#01/54: Area: FFFFF000, FFFFFFFF
#02/54: Area: FFFFE000, FFFFEFFF
#03/54: Area: FFFFD000, FFFFDFFF
#04/54: Area: FFFFC000, FFFFCFFF
#05/54: Area: FFFFB000, FFFFBFFF
#06/54: Area: FFFFA000, FFFFAFFF
#07/54: Area: FFFF9000, FFFF9FFF
#08/54: Area: FFFF8000, FFFF8FFF

...

#50/54: Area: 00102000, 001027FF
#51/54: Area: 00101800, 00101FFF
#52/54: Area: 00101000, 001017FF
#53/54: Area: 00100800, 00100FFF
#54/54: Area: 00100000, 001007FF
#01/01: Program size: 256 Bytes
#01/01: ID Protect: false
```

- As with the R5F562N8, 512K bytes of FlashROM and 96K bytes of RAM are available from FFF80000.
- The actual program is ready and operation has been confirmed.

   
---

Translated with www.DeepL.com/Translator (free version)

---
   
License
---

MIT
