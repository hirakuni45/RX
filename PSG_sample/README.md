Renesas RX64M, RX65N, RX71M, RX66T, RX72T, RX72N pseudo PSG music performance sample
=========

<iframe width="560" height="315" src="https://www.youtube.com/watch?v=4ZHuMYcSQko" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[Japanese](READMEja.md)
   
## Overview

This is a sample of a pseudo PSG music performance using an RX microcontroller. 
   
- On the RX72N, digital data is output from the SSIE.
- Normally, analog data is output from DA0/DA1.
- It was originally designed for the R8C, but the RX microcontroller's built-in D/A output produces a very high quality sound.
- The pseudo-PSG class is mainly implemented to play music using square waves (similar to NES).
- Sampling is done at 48KHz.
   
---

## Description

- main.cpp
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile
- RX66T/Makefile
- RX72T/Makefile
- RX72N/Makefile

---

## Hardware preparation

 - Connect the indicator LED to the specified port.
 - Connect the amplifier to DA0/DA1.
 - In the RX72N Envision Kit, the output is provided through the analog output pins.
 - In the DA0/DA1 analog output, the silence level is the middle potential of the supply voltage, so voltage conversion must be performed when connecting to a line amplifier.
 - The reference circuit for analog to line output is [AUDIO_sample](./AUDIO_sample), so please refer to it.

## Resource preparation

- It is not necessary to get it.
- The score for the piano version of Dragon Quest 1, Radatome Castle has been entered. （You can also create your own score.)
- You can also create your own score.
   
## How to build
   
- Move to each platform directory and make it.
- Write the psg_sample.mot file to the microcontroller.
   
## Operation

- The LED flashes every 0.25 seconds.
- Music starts playing, analog output from DA0/DA1. (mono)
- For RX72N, SSIE output.
    
-----
   
License
----

[MIT](../LICENSE)
