Renesas RX62N, RX24T, RX64M, RX65N, RX71M, RX66T, RX72T, RX72N LED flashing sample
=========

[Japanese](READMEja.md)
   
## Overview
Sample program of LED blinking using RX microcontroller
   
---

## Description
- main.cpp
- RX62N/Makefile (BlueBoard-RX62N_100pin)
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile
- RX66T/Makefile
- RX72T/Makefile
- RX72N/Makefile

---

## Hardware preparation
- If the base crystal is different, change the typedef parameters.
- The Makefile declares a set frequency for each module.
- RX24T:  80MHz (10MHz)
- RX64M: 120MHz (12MHz)
- RX71M: 240MHz (12MHz)
- RX65N: 120MHz (12MHz)
- RX66T: 160MHz (10MHz)
- RX72T: 192MHz (16MHz)
- RX72N: 240MHz (16MHz)
   
- Connect the LED to the specified port.
   
```C++
/// LED connection port definition
/// LED_ASSERT = 0 when the LED is to be turned on with "Inhale: Output 0
/// LED_ASSERT = 1 if the LED is to be turned on at output 1
/// Memo:
// Port outputs have different capabilities when current is drawn (suction) and when current is swept (discharge).
// In general, "sucking in" often allows more current to flow, and it is customary to follow that convention and connect with "sucking in".
#if defined(SIG_RX62N)
	// BlueBoard-RX62N_100pin
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ASSERT> LED;
#elif defined(SIG_RX24T)
	// DIY RX24T board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX71M)
	// DIY RX72M board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ASSERT> LED;
#elif defined(SIG_RX72M)
	// 工事中
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ASSERT> LED;
#elif defined(SIG_RX72N)
	// RX72N Envision Kit
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX64M)
	// DIY RX64M board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ASSERT> LED;
#elif defined(SIG_RX65N)
	// RX65N Envision Kit
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT7, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX66T)
	// DIY RX66T board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX72T)
	// DIY RX72T board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B1, LED_ASSERT> LED;
#endif
```
- For BlueBoard-RX62N_100pin,  use the red LED (D2) on the board.
- For RX65N Envision kit, use the blue LED on the board.
- For RX72N Envision kit, use the blue LED on the board.

---

## Boost the master clock
- Boost the internal instruction clock to maximum speed once the operation is transferred to the main function.
- Also set the clock for the internal device. (The setting is in RXxxx/clock_profile.hpp)

```C++
    SYSTEM_IO::boost_master_clock();
```

---

## Resource preparation
- None
   
## How to build
- Move to each platform directory and make it.
- Write the led_sample.mot file.
   
## Operation
- The LED flashes every 0.25 seconds.
    
## Remarks
- This project is basic and includes minimum settings etc. Please refer to it when starting a new project.   
   
---

Translated with www.DeepL.com/Translator (free version)

---
   
License
----

[MIT](../LICENSE)
