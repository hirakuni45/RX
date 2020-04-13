#pragma once
//=====================================================================//
/*!	@file
	@brief	MCS6502 Emulator クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

namespace cpu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	MCS6502 emulator class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class mcs6502 {
	public:
		static const uint32_t NES6502_NUMBANKS_  = 16;
		static const uint32_t NES6502_BANKSHIFT_ = 12;
		static const uint32_t NES6502_BANKSIZE_  = 0x10000 / NES6502_NUMBANKS_;
		static const uint32_t NES6502_BANKMASK_  = NES6502_BANKSIZE_ - 1;

		/// P (flag) register bitmasks
		struct pstatus_t {
			enum type {
				N = 0x80,
				V = 0x40,
				R = 0x20,  ///< Reserved, always 1
				B = 0x10,
				D = 0x08,
				I = 0x04,
				Z = 0x02,
				C = 0x01
			};
		};

		/// Vector addresses
		static const uint16_t NMI_VECTOR_   = 0xFFFA;
		static const uint16_t RESET_VECTOR_ = 0xFFFC;
		static const uint16_t IRQ_VECTOR_   = 0xFFFE;

		/// cycle counts for interrupts
		static const uint32_t INT_CYCLES_   = 7;
		static const uint32_t RESET_CYCLES_ = 6;

		static const uint32_t NMI_MASK_ = 0x01;
		static const uint32_t IRQ_MASK_ = 0x02;

		/// Stack is located on 6502 page 1
		static const uint32_t STACK_OFFSET_ = 0x0100;

		struct memread_t {
			uint32_t	min_;
			uint32_t	max_;
			uint8_t (*func_)(uint32_t address);
			memread_t() : min_(0), max_(0), func_(nullptr) { }
		};

		struct memwrite_t { 
			uint32_t	min_;
			uint32_t	max_;
			void (*func_)(uint32_t address, uint8_t value);
			memwrite_t() : min_(0), max_(0), func_(nullptr) { }
		};

		private:

		uint8_t*	page[NES6502_NUMBANKS_];

		memread_t	read_[16];
		memwrite_t	write_[16];

		uint32_t	pc_;	///< バンク対応にする為、３２ビット範囲にする
		uint8_t		a_;
		uint8_t		p_;
		uint8_t		x_;
		uint8_t		y_;
		uint8_t		s_;

		bool		jammed_;	///< is processor jammed? */
   
		uint8_t		int_pending_;
		uint8_t		int_latency_;

		int32_t		total_cycles_;
		int32_t		burn_cycles_;

		uint32_t	remaining_cycles_;

		uint8_t		stack_[256];

		uint8_t bank_readbyte_(uint32_t adr) {
			return 0;
		}

		uint16_t bank_readword_(uint32_t adr) {
			return 0;
		}

		uint8_t mem_readbyte_(uint32_t adr) {
			return 0;
		}

		void ADD_CYCLES_(uint8_t x) {
			remaining_cycles_ -= x;
			total_cycles_ += x;
		}

		void PAGE_CROSS_CHECK_(uint16_t addr, uint8_t reg) {
			if(reg > (uint8_t)(addr)) {
				ADD_CYCLES_(1);
			}
		}


#if 0
		void EMPTY_READ_(uint32_t adr) { }

		uint8_t IMMEDIATE_BYTE_() {
			uint8_t value = bank_readbyte_(pc_);
			++pc_;
			return value;
		}

		uint32_t ABSOLUTE_ADDR_() {
			uint16_t address = bank_readword_(pc_);
			pc_ += 2;
			return address;
		}

		void ABSOLUTE(uint32_t& address, uint8_t& value) {
			address = ABSOLUTE_ADDR_();
			value = mem_readbyte(address);
		}

#define ABSOLUTE_BYTE(value) \
{ \
   ABSOLUTE(temp, value); \
}

/* Absolute indexed X */
#define ABS_IND_X_ADDR(address) \
{ \
   ABSOLUTE_ADDR(address); \
   address = (address + X) & 0xFFFF; \
}

#define ABS_IND_X(address, value) \
{ \
   ABS_IND_X_ADDR(address); \
   value = mem_readbyte(address); \
}

#define ABS_IND_X_BYTE(value) \
{ \
   ABS_IND_X(temp, value); \
}

/* special page-cross check version for read instructions */
#define ABS_IND_X_BYTE_READ(value) \
{ \
   ABS_IND_X_ADDR(temp); \
   PAGE_CROSS_CHECK(temp, X); \
   value = mem_readbyte(temp); \
}

/* Absolute indexed Y */
#define ABS_IND_Y_ADDR(address) \
{ \
   ABSOLUTE_ADDR(address); \
   address = (address + Y) & 0xFFFF; \
}

#define ABS_IND_Y(address, value) \
{ \
   ABS_IND_Y_ADDR(address); \
   value = mem_readbyte(address); \
}

#define ABS_IND_Y_BYTE(value) \
{ \
   ABS_IND_Y(temp, value); \
}

/* special page-cross check version for read instructions */
#define ABS_IND_Y_BYTE_READ(value) \
{ \
   ABS_IND_Y_ADDR(temp); \
   PAGE_CROSS_CHECK(temp, Y); \
   value = mem_readbyte(temp); \
}

/* Zero-page */
#define ZERO_PAGE_ADDR(address) \
{ \
   IMMEDIATE_BYTE(address); \
}

#define ZERO_PAGE(address, value) \
{ \
   ZERO_PAGE_ADDR(address); \
   value = ZP_READBYTE(address); \
}

#define ZERO_PAGE_BYTE(value) \
{ \
   ZERO_PAGE(btemp, value); \
}

/* Zero-page indexed X */
#define ZP_IND_X_ADDR(address) \
{ \
   ZERO_PAGE_ADDR(address); \
   address += X; \
}

#define ZP_IND_X(address, value) \
{ \
   ZP_IND_X_ADDR(address); \
   value = ZP_READBYTE(address); \
}

#define ZP_IND_X_BYTE(value) \
{ \
   ZP_IND_X(btemp, value); \
}

/* Zero-page indexed Y */
/* Not really an adressing mode, just for LDx/STx */
#define ZP_IND_Y_ADDR(address) \
{ \
   ZERO_PAGE_ADDR(address); \
   address += Y; \
}

#define ZP_IND_Y_BYTE(value) \
{ \
   ZP_IND_Y_ADDR(btemp); \
   value = ZP_READBYTE(btemp); \
}  

/* Indexed indirect */
#define INDIR_X_ADDR(address) \
{ \
   ZERO_PAGE_ADDR(btemp); \
   btemp += X; \
   address = zp_readword(btemp); \
}

#define INDIR_X(address, value) \
{ \
   INDIR_X_ADDR(address); \
   value = mem_readbyte(address); \
} 

#define INDIR_X_BYTE(value) \
{ \
   INDIR_X(temp, value); \
}

/* Indirect indexed */
#define INDIR_Y_ADDR(address) \
{ \
   ZERO_PAGE_ADDR(btemp); \
   address = (zp_readword(btemp) + Y) & 0xFFFF; \
}

#define INDIR_Y(address, value) \
{ \
   INDIR_Y_ADDR(address); \
   value = mem_readbyte(address); \
} 

#define INDIR_Y_BYTE(value) \
{ \
   INDIR_Y(temp, value); \
}

/* special page-cross check version for read instructions */
#define INDIR_Y_BYTE_READ(value) \
{ \
   INDIR_Y_ADDR(temp); \
   PAGE_CROSS_CHECK(temp, Y); \
   value = mem_readbyte(temp); \
}
#endif

		void PUSH_(uint8_t value) {
			stack_[s_] = value;
			s_--;
		}

		uint8_t PULL_() {
			++s_;
			return stack_[s_];
		}

		template <uint8_t cycle, class src, class dst>
		void STORE() {
			uint8_t v = src();
			dst(pc_, v);
			ADD_CYCLES_(cycle);
		}

#if 0

#define STX(cycles, read_func, write_func, addr) \
{ \
   read_func(addr); \
   write_func(addr, X); \
   ADD_CYCLES(cycles); \
}

#define STY(cycles, read_func, write_func, addr) \
{ \
   read_func(addr); \
   write_func(addr, Y); \
   ADD_CYCLES(cycles); \
}
#endif

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		mcs6502() { }


		//-------------------------------------------------------------//
		/*!
			@brief	実行
		*/
		//-------------------------------------------------------------//
		void exec()
		{
			uint8_t op = mem_readbyte_(pc_);
			++pc_;
			switch(op) {
			case 0x00:
				break;

			case 0x85:   /// STA zero_page
//				STORE_ZP(3, a_);
				break;
			}

		}
	};
}
