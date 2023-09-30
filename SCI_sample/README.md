Renesas RX220, RX62N, RX631, RX63T, RX24T, RX26T, RX66T, RX72T, RX64M, RX71M, RX65N, RX72N SCI (UART) sample
=========

[Japanese](READMEja.md)

---

## Overview

SCI/SCIF/RSCI (UART) sample program using RX microcontroller

---

## Project list
 - main.cpp
 - RX220/Makefile
 - RX62N/Makefile
 - RX631/Makefile
 - RX63T/Makefile
 - RX24T/Makefile
 - RX26T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
 - RX66T/Makefile
 - RX72T/Makefile
 - RX72N/Makefile
   
---

## Hardware preparation (general)

- Refer to RXxxx/clock_profile.hpp for each microcontroller, crystal frequency, and frequency of each module.
- Connect the indicator LEDs to the specified ports.
- Connect USB serial and SCI ports.
- Refer to "RX220/port_map.hpp" for the SCI standard port of RX220.
- For the SCI standard port of RX62N, refer to "RX62x/port_map.hpp".
- For the RX631's SCI standard port, refer to "RX63x/port_map.hpp".
- For the RX63T's SCI standard port, refer to "RX63T/port_map.hpp".
- For the RX24T SCI standard port, refer to "RX24T/port_map.hpp".
- For the RX26T SCI/RSCI standard port, refer to "RX26T/port_map.hpp".
- For the SCI standard port of RX66T, refer to "RX66T/port_map.hpp".
- For the RX72T SCI standard port, refer to "RX72T/port_map.hpp".
- For the RX64M/RX71M SCI/SCIF standard ports, refer to "RX64M/port_map.hpp".
- For the RX65x SCI standard ports, refer to "RX65x/port_map.hpp".
- For the standard SCI port of RX72N, refer to "RX72N/port_map.hpp".
- For BlueBoard-RX62N_100pin, use D2 LED on the board. (red) 
- In case of FRK-RX62N, use LED1 on the board. (Yellow) 
- In case of RX65N Envision kit, the indicator LED on the board is blue.
- For RX72N Envision kit, the indicator LED is blue on the board.

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

```C++
	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義

#if defined(SIG_RX220)
	// 秋月 RX220 ボード
	static const char* system_str_ = { "AE-RX220" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B3, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
#elif defined(SIG_RX62N)
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社)
	static const char* system_str_ = { "RX62N FRK-RX62N" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
  #else
    // BlueBoard-RX62N_100pin
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
  #endif
#elif defined(SIG_RX631)
	// RX631 GR-CITRUS board
	static const char* system_str_ = { "RX631 GR-CITRUS" };
	// GR-CITRUS
	static constexpr bool LED_ACTIVE = 1;
	typedef device::PORT<device::PORTA, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
#elif defined(SIG_RX63T)
	// DIY RX63T board
	static const char* system_str_ = { "RX63T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORTB, device::bitpos::B7, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX26T)
	static const char* system_str_ = { "RX26T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
// RSCI を使う場合：
//	typedef device::rsci_io<device::RSCI8, RXB, TXB> SCI;
#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
// SCIF を使う場合：
//	typedef device::scif_io<device::SCIF8, RXB, TXB> SCI;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
// SCIF を使う場合：
//	typedef device::scif_io<device::SCIF8, RXB, TXB> SCI;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N Envision Kit" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT7, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI9, RXB, TXB> SCI;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B1, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N Envision Kit" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI2, RXB, TXB> SCI;
#endif

	SCI		sci_;
```

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

## Support for standard output
 - In main.cpp, there is a "branch" that can handle standard output (printf), such as "sci_putch".
 - These functions, such as "sci_putch", are implemented in such a way that they are called with a specific descriptor (stdout) from POSIX functions, write, etc. [common/syscalls.c](. /common/syscalls.c)
 - So, the printf function can be used normally, but it is not recommended in C++. (There is no reason to use it.)
 - printf can crash if there is a conflict between the format statement and the argument, since the argument is a variable argument and is passed through the stack, and it is difficult to find a complete "conflict" with compiler checks, so it should not be used, no matter how useful it is.
 - Instead, use the utils::format class, which works almost as well as printf and will not crash even with wrong arguments.
 - The C++ standard output function "std::cout" is deprecated because it consumes a lot of memory and is practically unusable.
 - If you want to use STL such as std::string, add STL library such as stdc++ to USER_LIBS in Makefile.
 - When using STLs, you need to have enough RAM because they use a lot of memory allocation.

---

## How POSIX functions and character output works and considerations
 - Usually, when outputting text to printf or cout of iostream, it is done via POSIX functions internally.   
 - This is based on historical background and the idea of simple structure.
 - When the application starts, three special files are open.
 - These are stdin(0), stdout(1), and stderr(2), respectively.
 - The application uses this determined file handle to access the file in the same way as a normal file to input and output characters.
 - This C++ framework uses the same mechanism.
 - [common/syscalls.c](. /common/syscalls.c). (POSIX Function County)
 - In it, the write function calls the sci_putch function when output is made to stdout, stderr, or destination.
 - The read function receives data from stdin and from the sci_getch function. (It blocks until the data arrives.)
 - In [main.cpp](main.cpp), sci_putch and sci_getch functions are defined to connect SCI input/output and POSIX functions.
 - Therefore, when implementing an application that performs character input/output, syscalls.c must be linked.
 - Incidentally, by implementing POSIX functions for SD card access, files can be exchanged using standard functions.

In syscalls.c, the sci_putch call of the write function:

```
_READ_WRITE_RETURN_TYPE write(int file, const void *ptr, size_t len)
{
	if(ptr == NULL) return 0;

	_READ_WRITE_RETURN_TYPE l = -1;
	if(file >= 0 && file <= 2) {
		if(file == 1 || file == 2) {
			const char *p = ptr;
			for(int i = 0; i < len; ++i) {
				char ch = *p++;
				sci_putch(ch);
			}
			l = len;
			errno = 0;
		}
	}
```

sci_getch call to the read function in syscalls.c:

```
extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}
}
```

---

## Why std::iostream is deprecated and alternatives
- In C++, iostreams are usually used for character input and output.
- However, iostream is quite huge and consumes a lot of memory.
- In embedded microcontrollers, both RAM and ROM are limited, so it is usually difficult to use iostream.
- Therefore, this C++ framework proposes a method that does not use them.
- This can be done by calling [common/format.hpp](...). /common/format.hpp).
- [common/format.hpp](. /common/format.hpp) replaces iostream and printf.
- Character formatting is mostly based on printf, and parameters are passed in a non-stackable manner.

---

## Supported communication protocols

```
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SCI communication protocol type
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PROTOCOL : uint8_t {
			B7_N_1S,	///< 7 ビット、No-Parity、1 Stop Bit
			B7_E_1S,	///< 7 ビット、Even(偶数)、1 Stop Bit
			B7_O_1S,	///< 7 ビット、Odd (奇数)、1 Stop Bit
			B7_N_2S,	///< 7 ビット、No-Parity、2 Stop Bits
			B7_E_2S,	///< 7 ビット、Even(偶数)、2 Stop Bits
			B7_O_2S,	///< 7 ビット、Odd (奇数)、2 Stop Bits
			B8_N_1S,	///< 8 ビット、No-Parity、1 Stop Bit
			B8_E_1S,	///< 8 ビット、Even(偶数)、1 Stop Bit
			B8_O_1S,	///< 8 ビット、Odd (奇数)、1 Stop Bit
			B8_N_2S,	///< 8 ビット、No-Parity、2 Stop Bits
			B8_E_2S,	///< 8 ビット、Even(偶数)、2 Stop Bits
			B8_O_2S,	///< 8 ビット、Odd (奇数)、2 Stop Bits
		};
```

- If nothing is set, "B8_N_1S" is used as the communication protocol.
   
If you specify otherwise:

```C++
	constexpr uint32_t baud = 115200;        // Baud rate (any integer value can be specified)
	auto intr = device::ICU::LEVEL::_2;      // Interrupt level (specifying NONE results in a polling operation)
	auto protocol = SCI::PROTOCOL::B8_E_2S;  // 8 bits, Even, 2 Stop Bits
	sci_.start(baud, intr, protocol);
```

---

## Baud rate

- The baud rate is specified as an integer.

```C++
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief SCI baud rate type (standardized value specified in serial communication).
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class BAUDRATE : uint32_t {
		B110    =    110,	///<    110 B.P.S.
		B150    =    150,	///<    150 B.P.S.
		B300    =    300,	///<    300 B.P.S.
		B600    =    600,	///<    600 B.P.S.
		B1200   =   1200,	///<   1200 B.P.S.
		B2400   =   2400,	///<   2400 B.P.S.
		B4800   =   4800,	///<   4800 B.P.S.
		B9600   =   9600,	///<   9600 B.P.S.
		B19200  =  19200,	///<  19200 B.P.S.
		B38400  =  38400,	///<  38400 B.P.S.
		B57600  =  57600,	///<  57600 B.P.S.
		B76800  =  76800,	///<  76800 B.P.S.
		B96000  =  96000,	///<  96000 B.P.S.
		B115200 = 115200,	///< 115200 B.P.S.
	};
```

```C++
	auto intr = device::ICU:LEVEL::_2;       // Interrupt level (specifying NONE results in a polling operation)
	auto protocol = SCI::PROTOCOL::B8_E_2S;  // 8 bits, Even, 2 Stop Bits
	sci_.start(SCI::BAUDRATE::B115200, intr, protocol);  // 115200 B.P.S.
```

---

Translated with www.DeepL.com/Translator (free version)

---
   
## License
   
[MIT](../LICENSE)
