Renesas RX62N, RX24T, RX64M, RX71M, RX65N, RX66T, RX72T, RX72N MTU sample
=========

[Japanese](READMEja.md)

---

## Overview

MTU sample program using RX microcontroller

---

## Project list
 - main.cpp
 - RX62N/Makefile
 - RX24T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
 - RX66T/Makefile
 - RX72T/Makefile
 - RX72N/Makefile
   
---

## Hardware preparation (general)
 - If the base crystal is different, change the typedef parameter.
 - Makefile declares the set frequency for each module.
 - RX24T:  80MHz (10MHz)
 - RX64M: 120MHz (12MHz)
 - RX71M: 240MHz (12MHz)
 - RX65N: 120MHz (12MHz)
 - RX66T: 160MHz (10MHz)
 - RX72T: 192MHz (16MHz)
 - RX72N: 240MHz (16MHz)
 - Connect the indicator LED to the specified port.
 - Connect the USB serial and SCI ports.
 - Refer to RX600/port_map.hpp for the RX64M/RX71M SCI standard port.
 - Refer to RX24T/port_map.hpp for the RX24T SCI standard port.
 - Refer to RX65x/port_map.hpp for the RX65x SCI standard port.
 - Refer to RX72N/port_map.hpp for the RX72N SCI standard port.
 
```C++
#if defined(SIG_RX62N)
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	typedef device::PORT<device::PORT0, device::bitpos::B5, false> LED;
	typedef device::SCI0 SCI_CH;
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N Envision Kit" };
	typedef device::PORT<device::PORT7, device::bitpos::B0, false> LED;
	typedef device::SCI9 SCI_CH;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0, false> LED;
	typedef device::SCI2 SCI_CH;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B1, false> LED;
	typedef device::SCI1 SCI_CH;
#endif
```

 - The standard crystal value is 10MHz for the RX24T and RX66T, and 12MHz for other CPUs.
 - RX72N Envision kit is a "16MHz" crystal
 - RX72T is a "16MHz" crystal
 - For the Envision kit RX65N, the indicator LED uses the blue color on the board.
 - For the Envision kit RX72N, the indicator LED uses the blue color on the board.

---

## Prepare your hardware resources.
 - Connect a converter, such as USB serial, to the port specified in SCI.
 - Connect the RXD terminal on the microcontroller side to the TXD of USB serial.
 - Connect the TXD terminal on the microcontroller side to the RXD of USB serial.
 - The RX72N Envision kit connects a PC to the CN8 micro USB on board.
   
---

## Build method
 - Go to each platform directory and make it.
 - Write the sci_sample.mot file.

---

## Operation
 - LED blinks at 0.25 second intervals.
 - TX (transmit) and RX (receive) are performed on the port specified by SCI.
 - Check with TeraTerm or other software.
 - TeraTerm serial setting: 115200 baud, 8-bit data, 1 stop, no parity. 1 stop, no parity.
 - The baud rate can be freely set by initializing SCI in main.cpp.
 - If the baud rate cannot be set, the initialization will fail. (Extremely slow or fast)
 - The utils::command class provides a one-line input function.
 - The received characters are parsed and displayed.

---

## Remarks
 - The FIFO buffer is 256 bytes on the receive side and 512 bytes on the transmit side.
 - Adjust to an appropriate value considering baud rate, frequency of reception, frequency of transmission, etc.
 - The minimum should be about 16 bytes.
 - When sending a string larger than the FIFO buffer, wait until the buffer is empty.
 - If the speed of retrieval from the buffer is less than the speed of reception, it will overflow and characters will be lost.
 - To change the SCI channel, modify the "typedef" definition in "main.cpp".
 - See RXxxx/port_map.hpp for the relationship between SCIx and port connections.
 - Except for the pin number, it works the same for 144-pin, 100-pin, and devices.
 - To select the second candidate, add "device::port_map::ORDER::SECOND" in sci_io typedef.
 - There are applications that attempt to generate source code by automating miscellaneous settings by a separate program, but it seems to me that this is fundamentally the wrong way to go, and if you need to modify the settings, you must always go back to the generated program and start over from generation.
 - C++ templates can absorb differences in channels, ports, and devices in a flexible, straightforward manner.

---

Translated with www.DeepL.com/Translator (free version)

---
   
## License
   
[MIT](../LICENSE)
