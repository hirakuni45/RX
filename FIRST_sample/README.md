Renesas RX microcontroller LED flashing sample
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
- RX140/Makefile
- RX220/Makefile
- RX231/Makefile
- RX62N/Makefile (BlueBoard-RX62N_100pin / FRK-RX62N)
- RX631/Makefile (GR-CITRUS)
- RX63T/Makefile
- RX24T/Makefile
- RX26T/Makefile
- RX66T/Makefile
- RX72T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile (RX65N Envision Kit)
- RX72N/Makefile (RX72N Envision Kit)

---

## Hardware Preparation (General)
- Refer to RXxxx/clock_profile.hpp for the crystal frequency of each microcontroller and each module.
- Refer to RXxxx/board_profile.hpp for the LED connection port of each microcontroller.
- Connect the indicator LEDs to the specified ports.
- The LEDs are connected so that they light up at the LOW level output by default.
- By changing the typedef of the LED, it can be made to turn on at the HIGH level.
- For BlueBoard-RX62N_100pin,  use the red LED (D2) on the board.
- For FRK-RX62N, use LED1 on the board. (yellow) 
- For GR-CITRUS, use the red LED1 on the board.  (red) 
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
	using namespace board_profile;

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
