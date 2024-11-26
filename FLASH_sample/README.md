Renesas RX microcontroller Data Flash サンプル
=========

[Japanese](READMEja.md)

## Overview
- Access to internal data flash using RX microcontroller, sample program.
- Using the terminal, the data flash memory is operated in an interactive manner.
- Display of the unique ID built into the microcontroller
---
   
## Project list
|File|flash_io|Operation check|
|---|---|:-:|
|[main.cpp](main.cpp)|-|-|
|[RX140/Makefile](RX140/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX220/Makefile](RX220/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX231/Makefile](RX231/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX24T/Makefile](RX24T/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX26T/Makefile](RX26T/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX62N/Makefile](RX62N/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX631/Makefile](RX631/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX64M/Makefile](RX64M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX71M/Makefile](RX71M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX65N/Makefile](RX65N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX72N/Makefile](RX72N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX66T/Makefile](RX66T/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX72T/Makefile](RX72T/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|

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
- (on RX231,RX24T, every 1 byte, on others, every 4 bytes)

### uid (unique ID lists)
- Display of unique IDs

---

## Notes

Data flash specifications for each microcontroller:

|CPU|Capacity|Bank size|Write unit|Value after elimination|Number of unique IDs|
|---|:--:|:-:|:-:|:-:|:-:|
|RX140|4K|256|1|0xFF|4|
|RX220|8K|2048|2|0x??|4|
|RX231|8K|1024|1|0xFF|4|
|RX24T|8K|1024|1|0xFF|4|
|RX26T|16K|64|4|0x??|3|
|RX62N|32K|2048|8|0x??|0|
|RX631|32K|2048|4|0x??|4|
|RX64M|64K|64|4|0x??|3|
|RX71M|64K|64|4|0x??|3|
|RX65N|32K|64|4|0x??|4|
|RX72N|32K|64|4|0x??|4|
|RX66T|32K|64|4|0x??|3|
|RX72T|32K|64|4|0x??|3|

-----
   
License
----

MIT
