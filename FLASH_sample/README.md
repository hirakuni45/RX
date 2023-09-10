Renesas RX24T, RX64M, RX71M, RX65N, RX66T, RX72N Data Flash サンプル
=========

[Japanese](READMEja.md)

## Overview
- Access to internal data flash using RX microcontroller, sample program.
- Using the terminal, the data flash memory is operated in an interactive manner.
- Display of the unique ID built into the microcontroller
---
   
## Project list
 - main.cpp
 - RX24T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
 - RX66T/Makefile
 - RX72T/Makefile
 - RX72N/Makefile
 ---
   
## Prepare hardware (general)
See [SCI_sample](../SCI_sample/README.md).

---

## Prepare hardware resources
 - Connect a converter such as USB serial to the port specified for SCI.
 - Connect RXD pin on microcontroller side and TXD pin on USB serial.
 - Connect the TXD terminal on the microcontroller side to the RXD terminal on the USB serial.
 - Use terminal software.

---
   
## How to build
 - Move to each platform directory and make.
 - Write flash_sample.mot file.

--- 
   
## Operation
 - LED blinks at 0.25 second intervals.
 - TX (transmit) and RX (receive) are performed at the port specified by SCI.
 - Check with TeraTerm or other software.
 - TeraTerm serial setting: 115200 baud, 8-bit data, 1 stop, no parity. 1 stop, no parity.
 - The baud rate can be freely set by initializing SCI in main.cpp.
 - If the "value" cannot be set, initialization will fail (extremely slow or fast). (Extremely slow or fast)
 - Interactive, data flash operation.
 - The operation of the data flash is performed in an interactive manner.

---
   
## data flush operation commands

### erase [bank]. 
- Erase data flash (per bank).
- The number of banks is the "capacity" divided by the "bank size".

### check [bank]
- Erase data flash erase check (per bank).

### r org [len] (read)
- read (per bank)

### write org data... (write)
- Write
- (on RX24T, every 1 byte, on others, every 4 bytes)

### uid (unique ID lists)
- Display of unique IDs
- For RX64M, RX71M and other models that do not have unique IDs, display the contents of a specific memory.

---

## Notes

Data flash specifications for each microcontroller:

|CPU|Capacity|Bank size|Write unit|Number of unique IDs|
|---|----|---|---|---|
|RX24T|8K|64|1|4|
|RX66T|32K|64|4|3||
|RX72T|32K|64|4|3|
|RX64M|64K|64|4|3|
|RX71M|64K|64|4|3|
|RX65N|32K|64|4|4|4|-|
|RX72N|32K|64|4|4|4|4
   
-----
   
License
----

MIT
