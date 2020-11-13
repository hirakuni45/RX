Renesas RX Microcontroller
=========
![R5F564ML](docs/RX600_group.jpg)
   
[Japanese](READMEja.md)
   
## Overview
   
This is a program by Renesas RX microcontroller and its compiler rx-elf-gcc, g++.   
   
Currently, a dedicated writing program has been implemented that has been tested on Windows, OS-X, and Linux.   
Development is now possible in multiple environments.   
   
- Currently supported and tested devices are RX24T, RX66T, RX64M, RX65N, RX71M, RX72N.   
I extend the device class daily.
- The RX72T and RX72M are scheduled to be supported in the future.
- I update it daily including directory configuration.   
- The RX62N(RX621) and RX63T are not currently supported. (It's in the LEGACY folder.)
   
Project consists of Makefile, related header, source code, dedicated startup It consists of routines and linker scripts.   
   
<img src="docs/RTK5_side.jpg" width="40%"> <img src="docs/NES_001.jpg" width="40%">   
Space Invaders Emulator, NES Emulator, for RX65N/RX72N Envision kit   
<img src="docs/AudioPlayer001.jpg" width="40%"> <img src="docs/Filer.jpg" width="40%">   
WAV/MP3 Audio Player, File selector, for RX65N/RX72N Envision kit   
   
<a href="http://www.youtube.com/watch?v=frRI-cbzGus" target="_blank"><img src="http://img.youtube.com/vi/frRI-cbzGus/0.jpg" width="40%" alt="YouTube Link for 'frRI-cbzGus'"></a>   
YouTube: NES Emulator for RX65N Envision kit
   
Device control classes with template design patterns provide flexible and concise functionality.   
Due to its functionality, it does not require difficult or complicated settings or code generation by separate programs.   
   
```
// LED flashing program
#include "common/renesas.hpp"

namespace {
    typedef device::system_io<12000000> SYSTEM_IO;  // External connection crystal is 12MHz
    typedef device::PORT<device::PORT0, device::bitpos::B7> LED;  // LED connection port
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
    SYSTEM_IO::setup_system_clock();

    LED::OUTPUT();
    while(1) {
        utils::delay::milli_second(250);
        LED::P = 0;
        utils::delay::milli_second(250);
        LED::P = 1;
    }
}
```
   
In order to complete the process from dependency rule generation to compilation and linking, usually with a single "make" command,
 I do not need it.   
No need for a dedicated boot program or loader I can write and execute.   
For development, we recommend using "Visual Studio Code" that can be used on multiple platforms.   
   
---
## Description
   
In device I / O operation, a dedicated header is prepared using template class library implemented in C++, and utility and class library are also enhanced.   
- Some of them use a library made by Renesas.   
   
|Directory/file|Contents|
|-----------------------|----------------------------------------------|
|all_project_build.sh   |All project builds (shell script)|
|[/RX600](./RX600)      |RX microcontroller common device definition class|
|[/RX24T](./RX24T)      |Device definition class dedicated to RX24T, linker script|
|[/RX64M](./RX64M)      |Device definition class dedicated to RX64M, linker script|
|[/RX71M](./RX71M)      |Device definition class dedicated to RX71M, linker script|
|[/RX65x](./RX65x)      |Device definition class dedicated to RX65(1N), linker script|
|[/RX66T](./RX66T)      |Device definition class dedicated to RX66T, linker script|
|[/RX72N](./RX72N)      |Device definition class dedicated to RX72N, linker script|
|[/FreeRTOS](./FreeRTOS)|FreeRTOS RX microcontroller compatible version and a simple sample|
|[/ff14](./ff14)        |ChaN's fatfs source code and handler for RX microcontroller|
|[/common](./common)    |Shared classes, utilities, etc.|
|[/chip](./chip)        |Device-specific control driver library for I2C, SPI, etc.|
|[/graphics](./graphics)|Graphics drawing relation class|
|[/sound](./sound)      |Sound, audio relationship class|
|/r_net                 |Renesas T4 (TCP / UDP) library, C ++ handler, wrapper|
|[/libmad](./libmad)    |MP3 decoding, mad library|
|[/libpng](./libpng)    |PNG library|
|[/rxprog](./rxprog)    |Program writing tool to RX microcontroller flash (Windows, OS-X, Linux compatible)|
|[/FIRST_sample](./FIRST_sample)|LED flashing program for each platform|
|[/SCI_sample](./SCI_sample)|Each platform, corresponding SCI sample program|
|[/CAN_sample](./CAN_sample)|RX64M/RX71M/RX66T/RX72N CAN sample program|
|[/FLASH_sample](./FLASH_sample)|Built-in data flash operation sample for each platform|
|[/RAYTRACER_sample](./RAYTRACER_sample)|For each platform, Ray tracing benchmark|
|[/SDCARD_sample](./SDCARD_sample)|For each platform, SD card operation sample|
|[/SIDE_sample](./SIDE_sample)|Renesas RX65N/RX72N Envision Kit, Space Invaders emulator|
|[/NESEMU_sample](./NESEMU_sample)|Renesas RX65N/RX72N Envision Kit, NES emulator|
|[/AUDIO_sample](./AUDIO_sample)|For each platform, MP3/WAV Audio player|
|[/SYNTH_sample](./SYNTH_sample)|FM Sound Source Synthesizer and Emulato|
|[LICENSE](./LICENSE)  |License notation file|
   
- Although not in the above list, please think that directories and files that exist when you check out are working.   

---

## Installation and features of Renesas GNU-RX
   
The former KPIT support for the GNU toolchain has been replaced by [GNU Tools]( https://gcc-renesas.com/) has added a new GNU tools.      
   
As the latest (as of July 2020) GNU toolchain for RX microcontrollers,   
 - binutils-2.24
 - gcc-8.3.0
 - newlib-3.1.0
 - gdb-7.8.2

You can download a toolchain for RX microcontrollers based on the above files.      
   
The tool can be downloaded by anyone who registers, and there is no binary limit.   
It also seems to have optimizations in RX microcomputers and support for the latest cores.   
Since gcc is based on 8.3.0, it supports C++17.   
It has deeper optimizations than normal gcc and supports the latest CPU cores.   
All projects using the C++ framework published here are compileable.   

They are also providing support.（CyberTHOR Studios Limited）   

To use this tool, install the toolchain and add ".bash_profile Set the command path to   

```
# rx-elf path
# PATH=$PATH:/usr/local/rx-elf/bin
PATH=$PATH:/C/'Program Files (x86)'/'GCC for Renesas RX 8.3.0.202002-GNURX-ELF'/rx-elf/rx-elf/bin
```

Features in Renesas GNU-RX 8.3.0：

- RXv3 Core Support
- Generation of double-precision floating-point instructions
- RX72N Built-in trigonometric function unit (TFU) support

---
## RX Development environment preparation (Windows、MSYS2)
   
 - On Windows, install the MSYS2 environment in advance.   
 - MSYS2 has msys2, mingw32, mingw64 and 3 different environments, but gcc for RX microcontroller
   Because it is necessary to build of, do with msys2.   
1. MSYS2 is a UNIX-based application development environment.
2. MINGW32 is an environment for i686 that the exception model of gcc is not war related to SEH because of Borland patent.
3. MINGW64 is an environment for developing Windows-based applications.   
 - If you have installed any software other than Microsoft's anti-virus software, please disable it.
1. The GCC build may take an unusually long time or may fail to build.   

 - MSYS2 upgrade
```
   pacman -Sy pacman
   pacman -Syu
```
   
- Open the console again. (You should see a message as you reopen the console)   
   
```
   pacman -Su
```
- The update is done multiple times, then follow the instructions on the console.
- You need to reopen the console several times.

- Install gcc, texinfo, gmp, mpfr, mpc, diffutils, automake, zlib, tar, make, unzip, git commands etc
```
   pacman -S gcc
   pacman -S texinfo
   pacman -S mpc-devel
   pacman -S diffutils
   pacman -S automake
   pacman -S zlib
   pacman -S tar
   pacman -S make
   pacman -S unzip
   pacman -S zlib-devel
   pacman -S git
```
   
---
## RX Development environment preparation (OS-X)
   
- In OS-X, install macports in advance.   
  brew is not recommended because it has less flexibility   
- Depending on the version of OS-X, you may need to install X-Code, Command Line Tools, etc. in advance   
 - macports upgrade   
```
   sudo port -d self update
```
- As you probably know, in the early stage of OS-X, llvm starts by calling gcc.
- However, llvm can not currently build gcc cross compilers.
- So, I will install gcc on macports, I will use the 5 series version.
```
   sudo port install gcc5
   sudo ln -sf /opt/local/bin/gcc-mp-5  /usr/local/bin/gcc
   sudo ln -sf /opt/local/bin/g++-mp-5  /usr/local/bin/g++
   sudo ln -sf /opt/local/bin/g++-mp-5  /usr/local/bin/c++
```
- You may need to reboot.
- For now, please check.
```
   gcc --version
```
   
```
   gcc (MacPorts gcc5 5.4.0_0) 5.4.0
   Copyright (C) 2015 Free Software Foundation, Inc.
   This is free software; see the source for copying conditions.  There is NO
   warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
   
 - Install texinfo, gmp, mpfr, mpc, diffutils, automake command etc
```
   sudo port install texinfo
   sudo port install gmp
   sudo port install mpfr
   sudo port install libmpc
   sudo port install diffutils
   sudo port install automake
```
   
---
## RX Development environment preparation (Ubuntu)

- There are multiple Linux environments, so here we will write the case for the "Ubuntu 16.04 LTS" environment.
   
- Install texinfo, gmp, mpfr, mpc, diffutils, automake command etc
```
   sudo apt-get install texinfo
   sudo apt-get install libgmp-dev
   sudo apt-get install libmpfr-dev
   sudo apt-get install libmpc-dev
   sudo apt-get install diffutils
   sudo apt-get install automake
   sudo apt-get install zlib1g-dev
```
   
---
## RX Development environment construction
   
- The RX compiler (rx-elf-gcc, g++) uses "gcc-7.5.0".   
- Download "binutils-2.34.tar.gz".   
- Download "gcc-7.5.0.tar.gz".   
- Download "newlib-2.4.0.tar.gz".   
- There are multiple versions of binutils, gcc and newlib, but some combinations   
  It has been found that ineligible binaries (which have subtle problems with operation) will be built.
- This bug occurs when using Renesas network stack (net_T4).
- It is not possible to identify the cause why such malfunction occurs.
- Here is a list of combinations that we have investigated.
```
   binutils-2.27, gcc-4.9.4, newlib-2.2.0 ---> OK
   binutils-2.27, gcc-5.5.0, newlib-2.2.0 ---> OK
   binutils-2.27, gcc-5.5.0, newlib-2.4.0 ---> OK
   binutils-2.27, gcc-6.4.0, newlib-2.4.0 ---> OK
   binutils-2.28, gcc-6.4.0, newlib-2.4.0 ---> OK
   binutils-2.30, gcc-6.4.0, newlib-2.4.0 ---> OK (old current)
   binutils-2.30, gcc-6.4.0, newlib-3.0.0 ---> NG
   binutils-2.34, gcc-7.5.0, newlib-2.4.0 ---> OK (new current)
```
- Using the latest gcc seems to be faster code, especially for C++.
   
---
#### build binutils-2.34
```
   cd
   tar xfvz binutils-2.34.tar.gz
   cd binutils-2.34
   mkdir rx_build
   cd rx_build
   ../configure --target=rx-elf --prefix=/usr/local/rx-elf --disable-nls
   make
   make install     OS-X,Linux: (sudo make install)
```

-  Pass PATH to /usr/local/rx-elf/bin (edit .bash_profile and add path)

```
   PATH=$PATH:/usr/local/rx-elf/bin
```

- Open the console again.

```
   rx-elf-as --version
```

- Execute the assembler command and check if the path is valid.
  
#### Build C compiler
```
    cd
    tar xfvz gcc-7.5.0.tar.gz
    cd gcc-7.5.0
    mkdir rx_build
	cd rx_build
    ../configure --prefix=/usr/local/rx-elf --target=rx-elf --enable-languages=c --disable-libssp --with-newlib --disable-nls --disable-threads --disable-libgomp --disable-libmudflap --disable-libstdcxx-pch --disable-multilib --enable-lto
    make
    make install     OS-X,Linux: (sudo make install)
```
  
#### Build newlib
```
    cd
    tar xfvz newlib-2.4.0.tar.gz
	cd newlib-2.4.0
    mkdir rx_build
    cd rx_build
    ../configure --target=rx-elf --prefix=/usr/local/rx-elf
	make
    make install     OS-X: (sudo make install)
```
- In Linux environment, sudo command does not recognize the path of binutils set up locally.
"Make install" will fail, so write the following script and execute it.
```
#!/bin/sh
# file: rx_install.sh

PATH=${PATH}:/usr/local/rx-elf/bin
make install
```
   
```
    sudo rx_install.sh
```
   
#### Build C++ compiler
```
    cd
    cd gcc-7.5.0
    cd rx_build
    ../configure --prefix=/usr/local/rx-elf --target=rx-elf --enable-languages=c,c++ --disable-libssp --with-newlib --disable-nls --disable-threads --disable-libgomp --disable-libmudflap --disable-libstdcxx-pch --disable-multilib --enable-lto --with-system-zlib
    make
    make install     OS-X,Linux: (sudo make install)
```
---
   
 - The built compiler collection is listed in the link below. (MSYS2 only)   
http://www.rvf-rc45.net/Renesas_GNU_Tools/ 

---
## Get RX Framework Source Code
```
    git clone git://github.com/hirakuni45/RX.git
```
   
---
### Boost installation used by RX framework
```
    pacman -S mingw-w64-x86_64-boost   (for MSYS2)
    sudo port install boost   (for OS-X)
    sudo apt-get install boost    (for Linux)
```
   
---
## RX Build all projects
```
    sh all_project_build.sh [clean]
```
--- 
## How to write program to RX microcontroller

There are several ways, but the easiest and least expensive way is to use the serial interface
It is a method of writing.   
- However, the writing speed is not very fast.   
   
In case of RX microcontroller with built-in USB interface, you can boot and connect with USB, but the driver Seems to only support the Windows version.
- The circumstances around here may be wrong as we have not investigated in detail.   
   
The most common, because not all RX microcontrollers have built-in USB interface We will show you how to write using serial interface.
   
- Writing at the serial interface is reasonably fast but easy and secure, and easy to connect.   
   
- The hardware manual describes the connection with the serial port and switching to boot mode.
  Please refer to it.   
- Normally, setting MD terminal to L or H allows switching between program and internal ROM execution.   
- It is also necessary to control the state of the UB terminal.   
- If you use a USB serial conversion module etc., it is easy to get power.   

1. RXD serial reception   
2. TXD serial transmission   
3. VCC power (5V or 3.3V)   
4. GND power 0V   
- As 3.3V can only extract a limited current, a regulator is always required.   
- Details on the connection method, boot mode settings, etc. can be found in the hardware manual for each device.   
   
## Construction of flash programmer for RX microcontroller
- Currently, flash writing to RX63T, RX24T, RX64M, and RX71M is confirmed.
- Since the reset is not controlled, it is necessary to assert the reset signal at the time of writing.
- In the current version, only erase, write and compare operations are implemented.
- Code protection ID settings and operations are not implemented yet.
- In the RX24T and RX63T, the erase operation is ignored because the erase is performed automatically when the connection is established.
   
- Build rxprog in MSYS2 environment.
- Copy the built executable file to "/usr/local/bin".
- Pass the PATH to /usr/local/bin.
```
    cd rxprog
    make
    make install
```
```
Renesas RX Series Programmer Version 0.90b
Copyright (C) 2016,2018 Hiramatsu Kunihito (hira@rvf-rc45.net)
usage:
rx_prog [options] [mot file] ...

Options :
    -P PORT,   --port=PORT     Specify serial port
    -s SPEED,  --speed=SPEED   Specify serial speed
    -d DEVICE, --device=DEVICE Specify device name
    -e, --erase                Perform a device erase to a minimum
    -v, --verify               Perform data verify
    -w, --write                Perform data write
    --progress                 display Progress output
    --device-list              Display device list
    --verbose                  Verbose output
    -h, --help                 Display this
```
- Edit rx_prog.conf and set the COM port to connect and the baud rate.
- Ports and baud rates can be set for each of Windows, OS-X and Linux environments.
- You can write a standard serial port in "rx_prog.conf", and you should set it according to your environment.
- Each project's "Makefile" contains a script that can be written using "make run".
   
rx_prog.conf:
```
port_win   = COM12
port_osx   = /dev/tty.usbserial-DA00X2QP
port_linux = /dev/ttyUSB0
speed_win = 230400
speed_osx = 230400
speed_linux = 230400
```
---
## Development using Renesus RX72N Envision Kit
<img src="docs/rx72n-envision-kit.jpg" width="50%">
<img src="docs/rx72n-envision-kit-board.jpg" width="80%">
   

   
---
## Programming environment using C++ framework
   
- The following is an example program to communicate with SCI in C++.   
1. The port of SCI is defined by "port_map.hpp", and there is more than one port to select
There is no need to make complicated settings if you set "second candidate" or "third candidate".   
2. The baud rate can be set as an integer, and is automatically calculated internally from the set frequency.   
3. Even if you use interrupts, you can use them without polling (polling).   
4. Transmission and reception are performed through a fixed length FIFO class, and the size can be freely defined.   
5. The sci_putch and sci_getch functions are called from POSIX file functions, so they can be linked externally.   
6. The above functions are accessed from stdout, stdin, stderr descriptors, so you can also use the printf function, but for various reasons we do not recommend using "utils :: format", which is the size It is smaller, more flexible, convenient and safe.   
```
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"

namespace {
    typedef device::system_io<12000000> SYSTEM_IO;  // External connection crystal is 12MHz

//  Use SCI9
    typedef device::SCI9 SCI_CH;

    typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) buffer definition at 512 bytes
    typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) buffer definition at 256 buyes

    typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
//    When selecting a second candidate for the SCI port
//    typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::option::SECOND> SCI;
    SCI     sci_;
}

extern "C" {
    // standard output, called from "syscalls.c"（stdout, stderr）
    void sci_putch(char ch) { sci_.putch(ch); }

    void sci_puts(const char* str) { sci_.puts(str); }

    // standard input, called from "syscalls.c"（stdin）
    char sci_getch(void) { return sci_.getch(); }

    uint16_t sci_length() { return sci_.recv_length(); }
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
    SYSTEM_IO::setup_system_clock();

    {  // Start SCI
       uint8_t intr = 2;        // Interrupt level
       uint32_t baud = 115200;  // baudrate
       sci_.start(baud, intr);
    }

    //-----
    {  // main、SCI output
       utils::format("Start SCI\n");
    }

    // to loop
    while(1) ;
}
```
---
## License

[MIT](../LICENSE)

```
Copyright (c) 2017 2019, Hiramatsu Kunihito
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, 
  this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, 
  this list of conditions and the following disclaimer in the documentation 
  and/or other materials provided with the distribution.
* Neither the name of the <organization> nor the　names of its contributors 
  may be used to endorse or promote products derived from this software 
  without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
