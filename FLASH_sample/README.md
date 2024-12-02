Renesas RX microcontroller Data Flash サンプル
=========

[Japanese](READMEja.md)

## Overview
- Access to internal data flash using RX microcontroller, sample program.
- Using the terminal, the data flash memory is operated in an interactive manner.
- Display of the unique ID built into the microcontroller
---
   
## Project list
|File/Group|flash_io|Operation check|
|---|---|:-:|
|[main.cpp](main.cpp)|-|-|
|RX111|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|RX113|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|RX130|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|[RX140/Makefile](RX140/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX220/Makefile](RX220/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX231/Makefile](RX231/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX24T/Makefile](RX24T/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|RX261|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|[RX26T/Makefile](RX26T/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX62N/Makefile](RX62N/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX631/Makefile](RX631/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|RX63T|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)||
|[RX64M/Makefile](RX64M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX71M/Makefile](RX71M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX65N/Makefile](RX65N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|RX660|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
|RX66N|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
|RX671|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
|[RX72N/Makefile](RX72N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|RX72M|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
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

### checkw [org]
- Erase data flash erase check (per word).

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

|Serise|Group|Capacity|Bank size|Write unit|Value after elimination|Number of unique IDs (32bits)|
|---|:--:|:-:|:-:|:-:|:-:|:-:|
|RX110|A|0K|-|-|-|4|
|RX111|A|8K|1024|1|0xFF|4|
|RX113|A|8K|1024|1|0xFF|4|
|RX130|A|8K|1024|1|0xFF|4|
|RX13T|A|0K|-|-|-|4|
|RX140|A|4K|256|1|0xFF|4|
|RX220|B|8K|2048|2|0x??|4|
|RX23[01]|A|8K|1024|1|0xFF|4|
|RX23T|A|0K|-|-|-|4|
|RX24T|A|8K|1024|1|0xFF|4|
|RX26[01]|A|8K|256|1|0xFF|4|
|RX26T|B|16K|64|4|0x??|3|
|RX62[1N]|B|32K|2048|8|0x??|0|
|RX63[1N]|B|32K|2048|4|0x??|4|
|RX63T|B|8K/32K|32|2|0x??|0|
|RX64M|C|64K|64|4|0x??|3|
|RX71M|C|64K|64|4|0x??|3|
|RX65[1N]|C|32K|64|4|0x??|4|
|RX660|C|32K|64|4|0x??|4|
|RX66N|C|32K|64|4|0x??|4|
|RX671|C|8K|64|4|0x??|4|
|RX72N|C|32K|64|4|0x??|4|
|RX66T|C|32K|64|4|0x??|3|
|RX72T|C|32K|64|4|0x??|3|

---

Characteristics of each system, data flash memory, etc：

|Group|Program [uS]|Erase [mS]|Blank check [uS]|
|:-:|:-:|:-:|:-:|
|A|375.5 (1)|229.4 (1K)|16.1 (1)|
|B (RX62x)|2000 (8)|250 (2K)|30 (8)|
|B (RX63x)|2000 (2)|20 (32)|30 (2)|
|C|1700 (4)|10 (64)|30 (4)|

- FCLK Max.
- Worst case.
- More than 100 writes and erases.

---
   
License
----

MIT
