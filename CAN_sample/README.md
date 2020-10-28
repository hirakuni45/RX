Renesas RX64M, RX66T CAN sample
=========

[Japanese](READMEja.md)
   
## Overview

   
---
## Description
- main.cpp
- RX64M/Makefile
- RX66T/Makefile

---
## Hardware preparation
- If the base crystal is different, change the typedef parameters.
- The Makefile declares a set frequency for each module.
- RX24T:  80MHz (10MHz)
- RX64M: 120MHz (12MHz)
- RX71M: 240MHz (12MHz)
- RX65N: 120MHz (12MHz)
- RX66T: 160MHz (10MHz)
- RX72N: 240MHz (16MHz)
   
- Connect the LED to the specified port.
   
```
#if defined(SIG_RX71M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX64M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX65N)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
#elif defined(SIG_RX24T)
	typedef device::system_io<10'000'000, 80'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX66T)
	typedef device::system_io<10'000'000, 160'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX72N)
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
#endif
```
- For RX65N Envision kit, use the blue LED on the board.
- For RX72N Envision kit, use the blue LED on the board.
   
## Resource preparation
- None
   
## How to build
- Move to each platform directory and make it.
- Write the led_sample.mot file.
   
## Operation
- The LED flashes every 0.25 seconds.
    
## Remarks
- This project is basic and includes minimum settings etc. Please refer to it when starting a new project.   
   
-----
   
License
----

[MIT](../LICENSE)
