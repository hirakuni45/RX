#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ICUb 定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ICUA 定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR {
			BUSERR = 16,  // BSC

			FRDYI  = 23,  // FCU

			SWINT  = 27,  // ICU

			CMI0   = 28,  // CMT0
			CMI1   = 29,  // CMT1
			CMI2   = 30,  // CMT2
			CMI3   = 31,  // CMT3

			FEPRF  = 32,  // CAC
			MENDF  = 33,  // CAC
			OVFF   = 34,  // CAC

			SPEI0  = 44,  // RSPI0
			SPRI0  = 45,  // RSPI0
			SPTI0  = 46,  // RSPI0
			SPII0  = 47,  // RSPI0

			DOPCF  = 57,  // DOC

			IRQ0   = 64,  // ICU
			IRQ1   = 65,
			IRQ2   = 66,
			IRQ3   = 67,
			IRQ4   = 68,
			IRQ5   = 69,
			IRQ6   = 70,
			IRQ7   = 71,

			LVD1   = 88,   // LVD
			LVD2   = 89,   // LVD

			ERI1   = 218,  // SCI1
			RXI1   = 219,  // SCI1
			TXI1   = 220,  // SCI1
			TEI1   = 221,  // SCI1
			ERI5   = 222,  // SCI5
			RXI5   = 223,  // SCI5
			TXI5   = 224,  // SCI5
			TEI5   = 225,  // SCI5
			ERI6   = 226,  // SCI6
			RXI6   = 227,  // SCI6
			TXI6   = 228,  // SCI6
			TEI6   = 229,  // SCI6

			EEI0   = 246,  // RIIC0
			RXI0   = 247,  // RIIC0
			TXI0   = 248,  // RIIC0
			TEI0   = 249,  // RIIC0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {
			rw8_t<base + 28> CMI0;
			rw8_t<base + 29> CMI1;
			rw8_t<base + 30> CMI2;
			rw8_t<base + 31> CMI3;

			rw8_t<base + 44> SPEI0;
			rw8_t<base + 45> SPRI0;
			rw8_t<base + 46> SPTI0;
			rw8_t<base + 47> SPII0;

			rw8_t<base + 218> ERI1;
			rw8_t<base + 219> RXI1;
			rw8_t<base + 220> TXI1;
			rw8_t<base + 221> TEI1;

			rw8_t<base + 222> ERI5;
			rw8_t<base + 223> RXI5;
			rw8_t<base + 224> TXI5;
			rw8_t<base + 225> TEI5;

			rw8_t<base + 226> ERI6;
			rw8_t<base + 227> RXI6;
			rw8_t<base + 228> TXI6;
			rw8_t<base + 229> TEI6;

			rw8_t<base + 246> ERI0;
			rw8_t<base + 247> RXI0;
			rw8_t<base + 248> TXI0;
			rw8_t<base + 249> TEI0;
		};
		static ir_t<0x00087010> IR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ier_t {
			typedef rw8_t<base + 0x02> ier02;
			bit_rw_t<ier02, bitpos::B0>	BUSERR;
			bit_rw_t<ier02, bitpos::B7>	FRDYI;

			typedef rw8_t<base + 0x03> ier03;
			bit_rw_t<ier03, bitpos::B3>	SWINT;
			bit_rw_t<ier03, bitpos::B4>	CMI0;
			bit_rw_t<ier03, bitpos::B5>	CMI1;
			bit_rw_t<ier03, bitpos::B6>	CMI2;
			bit_rw_t<ier03, bitpos::B7>	CMI3;

			typedef rw8_t<base + 0x05> ier05;
			bit_rw_t<ier03, bitpos::B4>	SPEI0;
			bit_rw_t<ier03, bitpos::B5>	SPRI0;
			bit_rw_t<ier03, bitpos::B6>	SPTI0;
			bit_rw_t<ier03, bitpos::B7>	SPII0;

			typedef rw8_t<base + 0x08> ier08;
			bit_rw_t<ier08, bitpos::B0>	IRQ0;
			bit_rw_t<ier08, bitpos::B1>	IRQ1;
			bit_rw_t<ier08, bitpos::B2>	IRQ2;
			bit_rw_t<ier08, bitpos::B3>	IRQ3;
			bit_rw_t<ier08, bitpos::B4>	IRQ4;
			bit_rw_t<ier08, bitpos::B5>	IRQ5;
			bit_rw_t<ier08, bitpos::B6>	IRQ6;
			bit_rw_t<ier08, bitpos::B7>	IRQ7;

			typedef rw8_t<base + 0x1B> ier1b;
			bit_rw_t<ier1b, bitpos::B2>	ERI1;
			bit_rw_t<ier1b, bitpos::B3>	RXI1;
			bit_rw_t<ier1b, bitpos::B4>	TXI1;
			bit_rw_t<ier1b, bitpos::B5>	TEI1;
			bit_rw_t<ier1b, bitpos::B6>	ERI5;
			bit_rw_t<ier1b, bitpos::B7>	RXI5;
			typedef rw8_t<base + 0x1C> ier1c;
			bit_rw_t<ier1c, bitpos::B0>	TXI5;
			bit_rw_t<ier1c, bitpos::B1>	TEI5;
			bit_rw_t<ier1c, bitpos::B2>	ERI6;
			bit_rw_t<ier1c, bitpos::B3>	RXI6;
			bit_rw_t<ier1c, bitpos::B4>	TXI6;
			bit_rw_t<ier1c, bitpos::B5>	TEI6;

			typedef rw8_t<base + 0x1E> ier1e;
			bit_rw_t<ier1e, bitpos::B6>	EEI0;
			bit_rw_t<ier1e, bitpos::B7>	RXI0;
			typedef rw8_t<base + 0x1F> ier1f;
			bit_rw_t<ier1f, bitpos::B0>	TXI0;
			bit_rw_t<ier1f, bitpos::B1>	TEI0;
		};
		static ier_t<0x00087200> IER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IPR レジスタ @n
					全て、下位４ビットが有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ipr_t {

			rw8_t<base + 4> CMI0;
			rw8_t<base + 5> CMI1;
			rw8_t<base + 6> CMI2;
			rw8_t<base + 7> CMI3;

			rw8_t<base + 44> RSPI0;

			rw8_t<base + 218> SCI1;
			rw8_t<base + 222> SCI5;
			rw8_t<base + 226> SCI6;

			rw8_t<base + 246> EEI0;
			rw8_t<base + 247> RXI0;
			rw8_t<base + 248> TXI0;
			rw8_t<base + 249> TEI0;
		};
		static ipr_t<0x00087300> IPR;

	};
	typedef icu_t ICU;
}
