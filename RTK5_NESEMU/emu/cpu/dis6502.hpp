#pragma once
//=====================================================================//
/*!	@file
	@brief	6502 dis assembler クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <cstdio>
#include <functional>

namespace cpu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	6502 dis asm class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class dis6502 {

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バイト・リード関数型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef std::function< uint8_t (uint32_t) > getbyte_type;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バイト・ライト関数型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef std::function< void (uint32_t, uint8_t) > putbyte_type;

	private:
		enum class adrmode {
			imp,
			acc,
			rel,
			imm,
			abs,
			abs_x,
			abs_y,
			zero,
			zero_x, 
			zero_y,
			ind,
			ind_x,
			ind_y
		};

		struct flags {
			static const uint8_t N = 0x80;
			static const uint8_t V = 0x40;
			static const uint8_t R = 0x20;   // Reserved, always 1
			static const uint8_t B = 0x10;
			static const uint8_t D = 0x08;
			static const uint8_t I = 0x04;
			static const uint8_t Z = 0x02;
			static const uint8_t C = 0x01;
		};

		uint32_t	pc_reg_;

		getbyte_type	getbyte_;
		putbyte_type	putbyte_;

		char		text_[256];

		uint8_t dis_op8_() const {
			return (getbyte_(pc_reg_ + 1));
		}

		uint16_t dis_op16_() const {
			return (getbyte_(pc_reg_ + 1) + (getbyte_(pc_reg_ + 2) << 8));
		}

		int dis_show_ind_(char* buf) const {
			return sprintf(buf, "(%04X)  ", dis_op16_());
		}

		int dis_show_ind_x_(char* buf) const {
			return sprintf(buf, "(%02X,x)  ", dis_op8_());
		}

		int dis_show_ind_y_(char* buf) const {
			return sprintf(buf, "(%02X),y  ", dis_op8_());
		}

		int dis_show_zero_x_(char* buf) const {
			return sprintf(buf, " %02X,x   ", dis_op8_());
		}

		int dis_show_zero_y_(char* buf) const {
			return sprintf(buf, " %02X,y   ", dis_op8_());
		}

		int dis_show_abs_y_(char* buf) const {
			return sprintf(buf, " %04X,y ", dis_op16_());
		}

		int dis_show_abs_x_(char* buf) const {
			return sprintf(buf, " %04X,x ", dis_op16_());
		}

		int dis_show_zero_(char* buf) const {
			return sprintf(buf, " %02X     ", dis_op8_());
		}

		int dis_show_abs_(char* buf) const {
			return sprintf(buf, " %04X   ", dis_op16_());
		}

		int dis_show_immediate_(char* buf) const {
			return sprintf(buf, "#%02X     ", dis_op8_());
		}

		int dis_show_acc_(char* buf) const {
			return sprintf(buf, " a      ");
		}

		int dis_show_relative_(char* buf) const {
			int target;
			target = (int8_t) dis_op8_();
			target += (pc_reg_ + 2);
			return sprintf(buf, " %04X   ", target);
		}

		int dis_show_code_(char* buf, adrmode optype) const {
			char *dest = buf + sprintf(buf, "%02X ", getbyte_(pc_reg_));

			switch(optype) {
			case adrmode::imp:
			case adrmode::acc:
				dest += sprintf(dest, "      ");
				break;

			case adrmode::rel:
			case adrmode::imm:
			case adrmode::zero:
			case adrmode::zero_x:
			case adrmode::zero_y:
			case adrmode::ind_y:
			case adrmode::ind_x:
				dest += sprintf(dest, "%02X    ", getbyte_(pc_reg_ + 1));
				break;

			case adrmode::abs:
			case adrmode::abs_x:
			case adrmode::abs_y:
			case adrmode::ind:
				dest += sprintf(dest, "%02X %02X ", getbyte_(pc_reg_ + 1), getbyte_(pc_reg_ + 2));
				break;
			}
			return dest - buf;
		}

		int dis_show_op_(char* buf, const char* opstr, adrmode optype) const {
			char *dest = buf;
   
			dest += dis_show_code_(dest, optype);
			dest += sprintf(dest, "%s ", opstr);

			switch(optype) {
			case adrmode::imp:     dest += sprintf(dest, "        ");   break;
			case adrmode::acc:     dest += dis_show_acc_(dest);         break;
			case adrmode::rel:     dest += dis_show_relative_(dest);    break;
			case adrmode::imm:     dest += dis_show_immediate_(dest);   break;
			case adrmode::abs:     dest += dis_show_abs_(dest);         break;
			case adrmode::abs_x:   dest += dis_show_abs_x_(dest);       break;
			case adrmode::abs_y:   dest += dis_show_abs_y_(dest);       break;
			case adrmode::zero:    dest += dis_show_zero_(dest);        break;
			case adrmode::zero_x:  dest += dis_show_zero_x_(dest);      break;
			case adrmode::zero_y:  dest += dis_show_zero_y_(dest);      break;
			case adrmode::ind:     dest += dis_show_ind_(dest);         break;
			case adrmode::ind_x:   dest += dis_show_ind_x_(dest);       break;
			case adrmode::ind_y:   dest += dis_show_ind_y_(dest);       break;
			}
			return dest - buf;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		dis6502() : pc_reg_(0) { }


		//-------------------------------------------------------------//
		/*!
			@brief	バイト読み込み関数への参照
			@return	バイト読み込み関数
		*/
		//-------------------------------------------------------------//
		getbyte_type& at_getbyte() { return getbyte_; }


		//-------------------------------------------------------------//
		/*!
			@brief	バイト書き込み関数への参照
			@return	バイト書き込み関数
		*/
		//-------------------------------------------------------------//
		putbyte_type& at_putbyte() { return putbyte_; }


		//-------------------------------------------------------------//
		/*!
			@brief	逆アセンブル
			@param[in]	PC	開始アドレス
		*/
		//-------------------------------------------------------------//
		const char* disasm(uint32_t PC)
		{
			char* buf = text_;
			const char* op;
			adrmode type;

			pc_reg_ = PC;

			buf += sprintf(buf, "%04X- ", pc_reg_);

			switch (getbyte_(pc_reg_)) {
			case 0x00: op = "brk"; type = adrmode::imp;    break;
			case 0x01: op = "ora"; type = adrmode::ind_x;  break;
			case 0x02: op = "jam"; type = adrmode::imp;    break;
			case 0x03: op = "slo"; type = adrmode::ind_x;  break;
			case 0x04: op = "nop"; type = adrmode::zero;   break;
			case 0x05: op = "ora"; type = adrmode::zero;   break;
			case 0x06: op = "asl"; type = adrmode::zero;   break;
			case 0x07: op = "slo"; type = adrmode::zero;   break;
			case 0x08: op = "php"; type = adrmode::imp;    break;
			case 0x09: op = "ora"; type = adrmode::imm;    break;
			case 0x0a: op = "asl"; type = adrmode::acc;    break;
			case 0x0b: op = "anc"; type = adrmode::imm;    break;
			case 0x0c: op = "nop"; type = adrmode::abs;    break;
			case 0x0d: op = "ora"; type = adrmode::abs;    break;
			case 0x0e: op = "asl"; type = adrmode::abs;    break;
			case 0x0f: op = "slo"; type = adrmode::abs;    break;

			case 0x10: op = "bpl"; type = adrmode::rel;    break;
			case 0x11: op = "ora"; type = adrmode::ind_y;  break;
			case 0x12: op = "jam"; type = adrmode::imp;    break;
			case 0x13: op = "slo"; type = adrmode::ind_y;  break;
			case 0x14: op = "nop"; type = adrmode::zero_x; break;
			case 0x15: op = "ora"; type = adrmode::zero_x; break;
			case 0x16: op = "asl"; type = adrmode::zero_x; break;
			case 0x17: op = "slo"; type = adrmode::zero_x; break;
			case 0x18: op = "clc"; type = adrmode::imp;    break;
			case 0x19: op = "ora"; type = adrmode::abs_y;  break;
			case 0x1a: op = "nop"; type = adrmode::imp;    break;
			case 0x1b: op = "slo"; type = adrmode::abs_y;  break;
			case 0x1c: op = "nop"; type = adrmode::abs_x;  break;
			case 0x1d: op = "ora"; type = adrmode::abs_x;  break;
			case 0x1e: op = "asl"; type = adrmode::abs_x;  break;
			case 0x1f: op = "slo"; type = adrmode::abs_x;  break;

			case 0x20: op = "jsr"; type = adrmode::abs;    break;
			case 0x21: op = "and"; type = adrmode::ind_x;  break;
			case 0x22: op = "jam"; type = adrmode::imp;    break;
			case 0x23: op = "rla"; type = adrmode::ind_x;  break;
			case 0x24: op = "bit"; type = adrmode::zero;   break;
			case 0x25: op = "and"; type = adrmode::zero;   break;
			case 0x26: op = "rol"; type = adrmode::zero;   break;
			case 0x27: op = "rla"; type = adrmode::zero;   break;
			case 0x28: op = "plp"; type = adrmode::imp;    break;
			case 0x29: op = "and"; type = adrmode::imm;    break;
			case 0x2a: op = "rol"; type = adrmode::acc;    break;
			case 0x2b: op = "anc"; type = adrmode::imm;    break;
			case 0x2c: op = "bit"; type = adrmode::abs;    break;
			case 0x2d: op = "and"; type = adrmode::abs;    break;
			case 0x2e: op = "rol"; type = adrmode::abs;    break;
			case 0x2f: op = "rla"; type = adrmode::abs;    break;

			case 0x30: op = "bmi"; type = adrmode::rel;    break;
			case 0x31: op = "and"; type = adrmode::ind_y;  break;
			case 0x32: op = "jam"; type = adrmode::imp;    break;
			case 0x33: op = "rla"; type = adrmode::ind_y;  break;
			case 0x34: op = "nop"; type = adrmode::imp;    break;
			case 0x35: op = "and"; type = adrmode::zero_x; break;
			case 0x36: op = "rol"; type = adrmode::zero_x; break;
			case 0x37: op = "rla"; type = adrmode::zero_x; break;
			case 0x38: op = "sec"; type = adrmode::imp;    break;
			case 0x39: op = "and"; type = adrmode::abs_y;  break;
			case 0x3a: op = "nop"; type = adrmode::imp;    break;
			case 0x3b: op = "rla"; type = adrmode::abs_y;  break;
			case 0x3c: op = "nop"; type = adrmode::abs_x;  break;
			case 0x3d: op = "and"; type = adrmode::abs_x;  break;
			case 0x3e: op = "rol"; type = adrmode::abs_x;  break;
			case 0x3f: op = "rla"; type = adrmode::abs_x;  break;

			case 0x40: op = "rti"; type = adrmode::imp;    break;
			case 0x41: op = "eor"; type = adrmode::ind_x;  break;
			case 0x42: op = "jam"; type = adrmode::imp;    break;
			case 0x43: op = "sre"; type = adrmode::ind_x;  break;
			case 0x44: op = "nop"; type = adrmode::zero;   break;
			case 0x45: op = "eor"; type = adrmode::zero;   break;
			case 0x46: op = "lsr"; type = adrmode::zero;   break;
			case 0x47: op = "sre"; type = adrmode::zero;   break;
			case 0x48: op = "pha"; type = adrmode::imp;    break;
			case 0x49: op = "eor"; type = adrmode::imm;    break;
			case 0x4a: op = "lsr"; type = adrmode::acc;    break;
			case 0x4b: op = "asr"; type = adrmode::imm;    break;
			case 0x4c: op = "jmp"; type = adrmode::abs;    break;
			case 0x4d: op = "eor"; type = adrmode::abs;    break;
			case 0x4e: op = "lsr"; type = adrmode::abs;    break;
			case 0x4f: op = "sre"; type = adrmode::abs;    break;

			case 0x50: op = "bvc"; type = adrmode::rel;    break;
			case 0x51: op = "eor"; type = adrmode::ind_y;  break;
			case 0x52: op = "jam"; type = adrmode::imp;    break;
			case 0x53: op = "sre"; type = adrmode::ind_y;  break;
			case 0x54: op = "nop"; type = adrmode::zero_x; break;
			case 0x55: op = "eor"; type = adrmode::zero_x; break;
			case 0x56: op = "lsr"; type = adrmode::zero_x; break;
			case 0x57: op = "sre"; type = adrmode::zero_x; break;
			case 0x58: op = "cli"; type = adrmode::imp;    break;
			case 0x59: op = "eor"; type = adrmode::abs_y;  break;
			case 0x5a: op = "nop"; type = adrmode::imp;    break;
			case 0x5b: op = "sre"; type = adrmode::abs_y;  break;
			case 0x5c: op = "nop"; type = adrmode::abs_x;  break;
			case 0x5d: op = "eor"; type = adrmode::abs_x;  break;
			case 0x5e: op = "lsr"; type = adrmode::abs_x;  break;
			case 0x5f: op = "sre"; type = adrmode::abs_x;  break;
 
			case 0x60: op = "rts"; type = adrmode::imp;    break;
			case 0x61: op = "adc"; type = adrmode::ind_x;  break;
			case 0x62: op = "jam"; type = adrmode::imp;    break;
			case 0x63: op = "rra"; type = adrmode::ind_x;  break;
			case 0x64: op = "nop"; type = adrmode::zero;   break;
			case 0x65: op = "adc"; type = adrmode::zero;   break;
			case 0x66: op = "ror"; type = adrmode::zero;   break;
			case 0x67: op = "rra"; type = adrmode::zero;   break;
			case 0x68: op = "pla"; type = adrmode::imp;    break;
			case 0x69: op = "adc"; type = adrmode::imm;    break;
			case 0x6a: op = "ror"; type = adrmode::acc;    break;
			case 0x6b: op = "arr"; type = adrmode::imm;    break;
			case 0x6c: op = "jmp"; type = adrmode::ind;    break;
			case 0x6d: op = "adc"; type = adrmode::abs;    break;
			case 0x6e: op = "ror"; type = adrmode::abs;    break;
			case 0x6f: op = "rra"; type = adrmode::abs;    break;

			case 0x70: op = "bvs"; type = adrmode::rel;    break;
			case 0x71: op = "adc"; type = adrmode::ind_y;  break;
			case 0x72: op = "jam"; type = adrmode::imp;    break;
			case 0x73: op = "rra"; type = adrmode::ind_y;  break;
			case 0x74: op = "nop"; type = adrmode::zero_x; break;
			case 0x75: op = "adc"; type = adrmode::zero_x; break;
			case 0x76: op = "ror"; type = adrmode::zero_x; break;
			case 0x77: op = "rra"; type = adrmode::zero_x; break;
			case 0x78: op = "sei"; type = adrmode::imp;    break;
			case 0x79: op = "adc"; type = adrmode::abs_y;  break;
			case 0x7a: op = "nop"; type = adrmode::imp;    break;
			case 0x7b: op = "rra"; type = adrmode::abs_y;  break;
			case 0x7c: op = "nop"; type = adrmode::abs_x;  break;
			case 0x7d: op = "adc"; type = adrmode::abs_x;  break;
			case 0x7e: op = "ror"; type = adrmode::abs_x;  break;
			case 0x7f: op = "rra"; type = adrmode::abs_x;  break;

			case 0x80: op = "nop"; type = adrmode::imm;    break;
			case 0x81: op = "sta"; type = adrmode::ind_x;  break;
			case 0x82: op = "nop"; type = adrmode::imm;    break;
			case 0x83: op = "sax"; type = adrmode::ind_x;  break;
			case 0x84: op = "sty"; type = adrmode::zero;   break;
			case 0x85: op = "sta"; type = adrmode::zero;   break;
			case 0x86: op = "stx"; type = adrmode::zero;   break;
			case 0x87: op = "sax"; type = adrmode::zero;   break;
			case 0x88: op = "dey"; type = adrmode::imp;    break;
			case 0x89: op = "nop"; type = adrmode::imm;    break;
			case 0x8a: op = "txa"; type = adrmode::imp;    break;
			case 0x8b: op = "ane"; type = adrmode::imm;    break;
			case 0x8c: op = "sty"; type = adrmode::abs;    break;
			case 0x8d: op = "sta"; type = adrmode::abs;    break;
			case 0x8e: op = "stx"; type = adrmode::abs;    break;
			case 0x8f: op = "sax"; type = adrmode::abs;    break;

			case 0x90: op = "bcc"; type = adrmode::rel;    break;
			case 0x91: op = "sta"; type = adrmode::ind_y;  break;
			case 0x92: op = "jam"; type = adrmode::imp;    break;
			case 0x93: op = "sha"; type = adrmode::ind_y;  break;
			case 0x94: op = "sty"; type = adrmode::zero_x; break;
			case 0x95: op = "sta"; type = adrmode::zero_x; break;
			case 0x96: op = "stx"; type = adrmode::zero_y; break;
			case 0x97: op = "sax"; type = adrmode::zero_y; break;
			case 0x98: op = "tya"; type = adrmode::imp;    break;
			case 0x99: op = "sta"; type = adrmode::abs_y;  break;
			case 0x9a: op = "txs"; type = adrmode::imp;    break;
			case 0x9b: op = "shs"; type = adrmode::abs_y;  break;
			case 0x9c: op = "shy"; type = adrmode::abs_x;  break;
			case 0x9d: op = "sta"; type = adrmode::abs_x;  break;
			case 0x9e: op = "shx"; type = adrmode::abs_y;  break;
			case 0x9f: op = "sha"; type = adrmode::abs_y;  break;

			case 0xa0: op = "ldy"; type = adrmode::imm;    break;
			case 0xa1: op = "lda"; type = adrmode::ind_x;  break;
			case 0xa2: op = "ldx"; type = adrmode::imm;    break;
			case 0xa3: op = "lax"; type = adrmode::ind_x;  break;
			case 0xa4: op = "ldy"; type = adrmode::zero;   break;
			case 0xa5: op = "lda"; type = adrmode::zero;   break;
			case 0xa6: op = "ldx"; type = adrmode::zero;   break;
			case 0xa7: op = "lax"; type = adrmode::zero;   break;
			case 0xa8: op = "tay"; type = adrmode::imp;    break;
			case 0xa9: op = "lda"; type = adrmode::imm;    break;
			case 0xaa: op = "tax"; type = adrmode::imp;    break;
			case 0xab: op = "lxa"; type = adrmode::imm;    break;
			case 0xac: op = "ldy"; type = adrmode::abs;    break;
			case 0xad: op = "lda"; type = adrmode::abs;    break;
			case 0xae: op = "ldx"; type = adrmode::abs;    break;
			case 0xaf: op = "lax"; type = adrmode::abs;    break;

			case 0xb0: op = "bcs"; type = adrmode::rel;    break;
			case 0xb1: op = "lda"; type = adrmode::ind_y;  break;
			case 0xb2: op = "jam"; type = adrmode::imp;    break;
			case 0xb3: op = "lax"; type = adrmode::ind_y;  break;
			case 0xb4: op = "ldy"; type = adrmode::zero_x; break;
			case 0xb5: op = "lda"; type = adrmode::zero_x; break;
			case 0xb6: op = "ldx"; type = adrmode::zero_y; break;
			case 0xb7: op = "lax"; type = adrmode::zero_y; break;
			case 0xb8: op = "clv"; type = adrmode::imp;    break;
			case 0xb9: op = "lda"; type = adrmode::abs_y;  break;
			case 0xba: op = "tsx"; type = adrmode::imp;    break;
			case 0xbb: op = "las"; type = adrmode::abs_y;  break;
			case 0xbc: op = "ldy"; type = adrmode::abs_x;  break;
			case 0xbd: op = "lda"; type = adrmode::abs_x;  break;
			case 0xbe: op = "ldx"; type = adrmode::abs_y;  break;
			case 0xbf: op = "lax"; type = adrmode::abs_y;  break;

			case 0xc0: op = "cpy"; type = adrmode::imm;    break;
			case 0xc1: op = "cmp"; type = adrmode::ind_x;  break;
			case 0xc2: op = "nop"; type = adrmode::imm;    break;
			case 0xc3: op = "dcp"; type = adrmode::ind_x;  break;
			case 0xc4: op = "cpy"; type = adrmode::zero;   break;
			case 0xc5: op = "cmp"; type = adrmode::zero;   break;
			case 0xc6: op = "dec"; type = adrmode::zero;   break;
			case 0xc7: op = "dcp"; type = adrmode::zero;   break;
			case 0xc8: op = "iny"; type = adrmode::imp;    break;
			case 0xc9: op = "cmp"; type = adrmode::imm;    break;
			case 0xca: op = "dex"; type = adrmode::imp;    break;
			case 0xcb: op = "sbx"; type = adrmode::imm;    break;
			case 0xcc: op = "cpy"; type = adrmode::abs;    break;
			case 0xcd: op = "cmp"; type = adrmode::abs;    break;
			case 0xce: op = "dec"; type = adrmode::abs;    break;
			case 0xcf: op = "dcp"; type = adrmode::abs;    break;

			case 0xd0: op = "bne"; type = adrmode::rel;    break;
			case 0xd1: op = "cmp"; type = adrmode::ind_y;  break;
			case 0xd2: op = "jam"; type = adrmode::imp;    break;
			case 0xd3: op = "dcp"; type = adrmode::ind_y;  break;
			case 0xd4: op = "nop"; type = adrmode::zero_x; break;
			case 0xd5: op = "cmp"; type = adrmode::zero_x; break;
			case 0xd6: op = "dec"; type = adrmode::zero_x; break;
			case 0xd7: op = "dcp"; type = adrmode::zero_x; break;
			case 0xd8: op = "cld"; type = adrmode::imp;    break;
			case 0xd9: op = "cmp"; type = adrmode::abs_y;  break;
			case 0xda: op = "nop"; type = adrmode::imp;    break;
			case 0xdb: op = "dcp"; type = adrmode::abs_y;  break;
			case 0xdc: op = "nop"; type = adrmode::abs_x;  break;
			case 0xdd: op = "cmp"; type = adrmode::abs_x;  break;
			case 0xde: op = "dec"; type = adrmode::abs_x;  break;
			case 0xdf: op = "dcp"; type = adrmode::abs_x;  break;

			case 0xe0: op = "cpx"; type = adrmode::imm;    break;
			case 0xe1: op = "sbc"; type = adrmode::ind_x;  break;
			case 0xe2: op = "nop"; type = adrmode::imm;    break;
			case 0xe3: op = "isb"; type = adrmode::ind_x;  break;
			case 0xe4: op = "cpx"; type = adrmode::zero;   break;
			case 0xe5: op = "sbc"; type = adrmode::zero;   break;
			case 0xe6: op = "inc"; type = adrmode::zero;   break;
			case 0xe7: op = "isb"; type = adrmode::zero;   break;
			case 0xe8: op = "inx"; type = adrmode::imp;    break;
			case 0xe9: op = "sbc"; type = adrmode::imm;    break;
			case 0xea: op = "nop"; type = adrmode::imp;    break;
			case 0xeb: op = "sbc"; type = adrmode::imm;    break;
			case 0xec: op = "cpx"; type = adrmode::abs;    break;
			case 0xed: op = "sbc"; type = adrmode::abs;    break;
			case 0xee: op = "inc"; type = adrmode::abs;    break;
			case 0xef: op = "isb"; type = adrmode::abs;    break;

			case 0xf0: op = "beq"; type = adrmode::rel;    break;
			case 0xf1: op = "sbc"; type = adrmode::ind_y;  break;
			case 0xf2: op = "jam"; type = adrmode::imp;    break;
			case 0xf3: op = "isb"; type = adrmode::ind_y;  break;
			case 0xf4: op = "nop"; type = adrmode::zero_x; break;
			case 0xf5: op = "sbc"; type = adrmode::zero_x; break;
			case 0xf6: op = "inc"; type = adrmode::zero_x; break;
			case 0xf7: op = "isb"; type = adrmode::zero_x; break;
			case 0xf8: op = "sed"; type = adrmode::imp;    break;
			case 0xf9: op = "sbc"; type = adrmode::abs_y;  break;
			case 0xfa: op = "nop"; type = adrmode::imp;    break;
			case 0xfb: op = "isb"; type = adrmode::abs_y;  break;
			case 0xfc: op = "nop"; type = adrmode::abs_x;  break;
			case 0xfd: op = "sbc"; type = adrmode::abs_x;  break;
			case 0xfe: op = "inc"; type = adrmode::abs_x;  break;
			case 0xff: op = "isb"; type = adrmode::abs_x;  break;
			}

			buf += dis_show_op_(buf, op, type);

#if 0
			buf += sprintf(buf, "%c%c1%c%c%c%c%c %02X %02X %02X %02X\n",
				(P & flags::N) ? 'N' : '.',
				(P & flags::V) ? 'V' : '.',
				(P & flags::B) ? 'B' : '.',
				(P & flags::D) ? 'D' : '.',
				(P & flags::I) ? 'I' : '.',
				(P & flags::Z) ? 'Z' : '.',
				(P & flags::C) ? 'C' : '.',
				A, X, Y, S);
#endif

			uint32_t step = 0;
			switch(type) {
			case adrmode::imp:    step = 1; break;
			case adrmode::acc:    step = 1; break;
			case adrmode::rel:    step = 2; break;
			case adrmode::imm:    step = 2; break;
			case adrmode::abs:    step = 3; break;
			case adrmode::abs_x:  step = 3; break;
			case adrmode::abs_y:  step = 3; break;
			case adrmode::zero:   step = 2; break;
			case adrmode::zero_x: step = 2; break;
			case adrmode::zero_y: step = 2; break;
			case adrmode::ind:    step = 3; break;
			case adrmode::ind_x:  step = 2; break;
			case adrmode::ind_y:  step = 2; break;
			}
			pc_reg_ += step;

			return text_;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	リード・バイト
			@param[in]	adr	アドレス
			@return リード・バイト
		*/
		//-------------------------------------------------------------//
		uint8_t read_byte(uint32_t adr) {
			return getbyte_(adr);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ライト・バイト
			@param[in]	adr	アドレス
			@param[in]	dat	データ
		*/
		//-------------------------------------------------------------//
		void write_byte(uint32_t adr, uint8_t dat) {
			putbyte_(adr, dat);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	PC の取得
			@return PC
		*/
		//-------------------------------------------------------------//
		uint32_t get_pc() const { return pc_reg_ & 0xffff; }


		//-------------------------------------------------------------//
		/*!
			@brief	アセンブルリスト取得
			@return アセンブルリスト
		*/
		//-------------------------------------------------------------//
		const char* get_list() const { return text_; }
	};
}
