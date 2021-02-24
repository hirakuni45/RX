Renesas RX65N/RX72N SYNTH (Yamaha DX7 emulator) sample
=========

<img src="../docs/SYNTH_sample.jpg" width="50%">

[Japanese](READMEja.md)

## Overview

Sample program for pronouncing the Yamaha DX7 FM Synthesizer using the RX microcontroller
   
## Project List

 - main.cpp
 - synth_gui.hpp
 - keyboard.hpp
 - RX65N/Makefile
 - RX72N/Makefile
 - DX7_0628.SYX

## FM synthesizer, DX7 emulator (source)

 - RX/sound/synth/

## Standard MIDI File Player (source)

- RX/sound/smf

The original source code is for the "Arduino" environment, so I modified it for this framework.

## Hardware preparation (general)

- In the RX72N Envision Kit, connect an amplifier to the audio jack.
- In the RX65N Envision Kit, connect an appropriate amplifier since analog output is provided from DA0 and DA1.
- For details on how to modify the RX65N Envision Kit, refer to AUDIO_sample.
      
## Build method

 - Move to each platform directory and make.
 - Write the SYNTH_sample.mot file.
   
## Operation

 - Put DX7_0628.SYX in the root of the SD card.
 - There is a delay in loading the tones (about 3 seconds).
 - When you start up the software and press a keyboard key, the sound of the tone will be played. (32 tones in total)
 - Use the "<" and ">" tone change buttons to change the tone.
 - The name of the tone is displayed in the center of the tone change button.
 - The octave range can be changed with the "<<" and ">>" buttons. (5 octaves)
 - Up to four keys can be recognized and sounded simultaneously. (FM synthesizer is capable of 8 simultaneous notes.
 - Press the "@" button to open the "Filer", and select the MID file to play it.
    
## Note

In the case of the RX65N Envision Kit, the number of simultaneous sounds is set to four due to limited processing power.
   
Some MID files are playable and some are not, depending on the standard MIDI format, the limitations of the parser currently installed, and the limitations of the synthesizer.
There are many MID files available on the net, so please search for them and enjoy automatic performance.

-----
   
License
----

MIT

FM Synthsizer License:

  http://www.apache.org/licenses/LICENSE-2.0

smf:

```
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
```
