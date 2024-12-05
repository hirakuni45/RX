Renesas RX microcontroller A/D conversion sample
=========

[Japanese](READMEja.md)

---

## Overview

Sample program to perform A/D conversion using RX microcontroller
   
---

## Project list

- main.cpp
- RX140/Makefile
- RX220/Makefile
- RX231/Makefile
- RX24T/Makefile
- RX26T/Makefile
- RX631/Makefile
- RX63T/Makefile
- RX64M/Makefile
- RX72T/Makefile

---

## Hardware preparation

|RX microcontroller|A/D Definition Class|A/D control class|AN000 port|
|:-:|:-:|:-:|:-:|
|RX140|[RX231/s12ade.hpp](../RX231/s12ade.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX220|[RX220/s12ad.hpp](../RX220/s12ad.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX231|[RX231/s12ade.hpp](../RX231/s12ade.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX24T|[RX24T/s12ad.hpp](../RX24T/s12ad.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX26T|[RX26T/s12adh.hpp](../RX26T/s12adh.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX631|[RX63x/s12ad.hpp](../RX63x/s12ad.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX63T|[RX63T/s12adb.hpp](../RX63T/s12adb.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX64M|[RX64M/s12adc.hpp](../RX64M/s12adc.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX72T|[RX72T/s12adh.hpp](../RX72T/s12adh.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|

- A/D conversion unit uses “device::S12AD
- Use “single” conversion theory
- AN000 A/D input is converted, so connect a volume, etc.

---

## Build method

- Move to each platform directory and make
- Write adc_sample.mot file
- In each microcontroller directory, there is “board_profile.hpp” to configure board-specific settings

---

## operation

- TeraTerm serial settings: 115200 baud, 8-bit data, 1 stop, no parity
- LED blinks at 0.25 second intervals
- Convert AN000 analog input and output to terminal at 1 second intervals

---

Translated with DeepL.com (free version)

---

License
   
[MIT](../LICENSE)
