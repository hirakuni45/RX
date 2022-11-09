Renesas RX63T, RX62N, RX24T, RX64M, RX65N, RX71M, RX66T, RX72T, RX72N LED flashing sample
=========

[Japanese](READMEja.md)
   
## Overview
Sample program of LED blinking using RX microcontroller

- Master clock boost
- Blinking LED
- Delay due to software delay

---

## Description
- main.cpp
- RX63T/Makefile
- RX62N/Makefile (BlueBoard-RX62N_100pin / FRK-RX62N)
- RX24T/Makefile
- RX66T/Makefile
- RX72T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile (for RX65N Envision Kit)
- RX72N/Makefile (for RX72N Envision Kit)

---

## Hardware Preparation (General)
 - Refer to RXxxx/clock_profile.hpp for the crystal frequency of each microcontroller and each module.
 - Connect the indicator LEDs to the specified ports.
 - The LEDs are connected so that they light up at the LOW level output by default.
 - By changing the typedef of the LED, it can be made to turn on at the HIGH level.
   
```C++
/// LED connection port definition
/// LED_ACTIVE = 0 when the LED is to be turned on with "Inhale: Output 0
/// LED_ACTIVE = 1 if the LED is to be turned on at output 1
/// Memo:
// Port outputs have different capabilities when current is drawn (suction) and when current is swept (discharge).
// In general, "sucking in" often allows more current to flow, and it is customary to follow that convention and connect with "sucking in".
#if defined(SIG_RX63T)
	// DIY RX63T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORTB, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX62N)
	// BlueBoard-RX62N_100pin
	static constexpr bool LED_ACTIVE = 0;
  #if defined(CQ_FRK)
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
  #else
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
  #endif
#elif defined(SIG_RX24T)
	// DIY RX24T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX71M)
	// DIY RX72M board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX72M)
	// 工事中
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX72N)
	// RX72N Envision Kit
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX64M)
	// DIY RX64M board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX65N)
	// RX65N Envision Kit
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT7, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX66T)
	// DIY RX66T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX72T)
	// DIY RX72T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B1, LED_ACTIVE> LED;
#endif
```
- For BlueBoard-RX62N_100pin,  use the red LED (D2) on the board.
- For FRK-RX62N, use LED1 on the board. (yellow) 
- For RX65N Envision kit, use the blue LED on the board.
- For RX72N Envision kit, use the blue LED on the board.

---

## Boost the master clock
- Boost the internal instruction clock (ICLK) to maximum speed once the operation is transferred to the main function.
- Also set the clock for the internal device. (The setting is in RXxxx/clock_profile.hpp)

```C++
    SYSTEM_IO::boost_master_clock();
```

---

## Set LED connection port to "output".

```C++
	LED::OUTPUT(); // set LED port to output
```

## Blink.

```C++
	while(1) {
		utils::delay::milli_second(250);
		LED::P = 1; // lights on
		utils::delay::milli_second(250);
		LED::P = 0; // lights off
	}
````

---

## Limiting resistors for LEDs

- Refer to the table below for the value of the limiting resistor to be placed in series with the LEDs.
- The limiting resistor can be either on the Vcc side or on the Vss (GND) side.

When a current of about 1mA is applied:
|Supply voltage|Red(Vf)|Yellow(Vf)|Blue(Vf)|
|:---:|:---:|:---:|:---:|
|3.3V|2K (1.4V)|1.2K (2.1V)|300 (3.0V)|
|5V|3.6K (1.4V)|3K (2.1V)|2K (3.0V)|

Calculation Formula:
  ("Supply voltage" - "Vf of LED") / "Current to LED"   

- The Vf of the LEDs in the table is only a guide and varies depending on the current flowing to the LEDs and the LEDs.
- When Vf is large, the limiting resistor becomes smaller, so be sure that the current flowing through the port does not exceed the limit.
- For the maximum current that can flow through the port, refer to "Electrical Characteristics" and "Allowable Output Current" in the hardware manual.

---
   
## How to build

- Move to each platform directory and make.
- Write led_sample.mot file to the microcontroller.
- FRK-RX62N is R5F562N7 (FlashRom: 374KB), so change the device in Makefile.
- Enable the CQ_FRK variable (compile-time constant) to switch the board dependence.

---
   
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
