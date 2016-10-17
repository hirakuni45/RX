#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・ICUb 定義 @n
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

			RAMERR = 18,  // RAM

			FIFERR = 21,  // FCU

			FRDYI  = 23,  // FCU

			SWINT2 = 26,  // ICU
			SWINT  = 27,  // ICU

			CMI0   = 28,  // CMT0
			CMI1   = 29,  // CMT1
			CMWI0  = 30,  // CMTW0
			CMWI1  = 31,  // CMTW1

			D0FIFO2 = 32,  // USBA
			D1FIFO2 = 33,  // USBA
			D0FIFO0 = 34,  // USB0
			D1FIFO0 = 35,  // USB0

			RPRI0   = 38,  // RSPI0
			SPTI0   = 39,  // RSPI0

			SPRI    = 42,  // QSPI
			SPTI    = 43,  // QSPI

			SBFAI   = 44,  // SDHI

			MBFAI   = 45,  // MMCIF

			SSITXI0 = 46,  // SSI0
			SSIRXI0 = 47,  // SSI0

			SSIRTI1 = 48,  // SSI1

			IDEI    = 50,  // SRC
			ODFI    = 51,  // SRC

//			RXI0    = 52,  // RIIC0
//			TXI0    = 53,
//			RXI2    = 54,  // RIIC2
//			TXI2    = 55,

			RXI0    = 58,  // SCI0
			TXI0    = 59,
			RXI1    = 60,  // SCI1
			TXI1    = 61,
			RXI2    = 62,  // SCI2
			TXI2    = 63, 

			IRQ0    = 64,  // ICU
			IRQ1    = 65,
			IRQ2    = 66,
			IRQ3    = 67,
			IRQ4    = 68,
			IRQ5    = 69,
			IRQ6    = 70,
			IRQ7    = 71,
			IRQ8    = 72,
			IRQ9    = 73,
			IRQ10   = 74,
			IRQ11   = 75,
			IRQ12   = 76,
			IRQ13   = 77,
			IRQ14   = 78,
			IRQ15   = 79,

			RXI3    = 80,  // SCI3
			TXI3    = 81,
			RXI4    = 82,  // SCI4
			TXI4    = 83,
			RXI5    = 84,  // SCI5
			TXI5    = 85,
			RXI6    = 86,  // SCI6
			TXI6    = 87,

			LVD1    = 88,  // LVD1
			LVD2    = 89,  // LVD2

			USBR0   = 90,  // USB0

			ALM     = 92,  // RTC
			PRD     = 93,

			USBAR   = 94,  // USBA

			IWUNI   = 95,  // IWDT

			WUNI    = 96,  // WDT

			PCDFI   = 97,  // PDC

			RXI7    = 98,  // SCI7
			TXI7    = 99,

			RXIF8   = 100, // SCIFA8
			TXIF8   = 101,

			RXIF9   = 102, // SCIFA9
			TXIF9   = 103,

			RXIF10  = 104, // SCIFA10
			TXIF10  = 105,

			GROUPBE0 = 106,  // ICU
			GROUPBL0 = 110,
			GROUPBL1 = 111,
			GROUPAL0 = 112,
			GROUPAL1 = 113,

			RXIF11   = 114,  // SCIFA11
			TXIF11   = 115,

			RXI12    = 116,  // SCI12
			TXI12    = 117,

			DMAC0I   = 120,  // DMAC
			DMAC1I   = 121,
			DMAC2I   = 122,
			DMAC3I   = 123,
			DMAC74I  = 124,

			OSTDI    = 125,  // OST

			EXDMAC0I = 126,  // EXDMAC
			EXDMAC1I = 127,

			INTB128  = 128,
			INTA208  = 208,
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

			rw8_t<base + 58> RXI0;
			rw8_t<base + 59> TXI0;
			rw8_t<base + 60> RXI1;
			rw8_t<base + 61> TXI1;
			rw8_t<base + 62> RXI2;
			rw8_t<base + 63> TXI2;

			rw8_t<base + 64> IRQ0;
			rw8_t<base + 65> IRQ1;
			rw8_t<base + 66> IRQ2;
			rw8_t<base + 67> IRQ3;
			rw8_t<base + 68> IRQ4;
			rw8_t<base + 69> IRQ5;
			rw8_t<base + 70> IRQ6;
			rw8_t<base + 71> IRQ7;
			rw8_t<base + 72> IRQ8;
			rw8_t<base + 73> IRQ9;
			rw8_t<base + 74> IRQ10;
			rw8_t<base + 75> IRQ11;
			rw8_t<base + 76> IRQ12;
			rw8_t<base + 77> IRQ13;
			rw8_t<base + 78> IRQ14;
			rw8_t<base + 79> IRQ15;

			rw8_t<base + 80> RXI3;
			rw8_t<base + 81> TXI3;

			rw8_t<base + 82> RXI4;
			rw8_t<base + 83> TXI4;
			rw8_t<base + 84> RXI5;
			rw8_t<base + 85> TXI5;
			rw8_t<base + 86> RXI6;
			rw8_t<base + 87> TXI6;


			rw8_t<base + 98> RXI7;
			rw8_t<base + 99> TXI7;
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
			bit_rw_t<ier02, bitpos::B5>	FIFERR;
			bit_rw_t<ier02, bitpos::B7>	FRDYI;

			typedef rw8_t<base + 0x03> ier03;
			bit_rw_t<ier03, bitpos::B3>	SWINT;
			bit_rw_t<ier03, bitpos::B4>	CMI0;
			bit_rw_t<ier03, bitpos::B5>	CMI1;

			typedef rw8_t<base + 0x07> ier07;
			bit_rw_t<ier07, bitpos::B2>	RXI0;
			bit_rw_t<ier07, bitpos::B3>	TXI0;
			bit_rw_t<ier07, bitpos::B4>	RXI1;
			bit_rw_t<ier07, bitpos::B5>	TXI1;
			bit_rw_t<ier07, bitpos::B6>	RXI2;
			bit_rw_t<ier07, bitpos::B7>	TXI2;

			typedef rw8_t<base + 0x08> ier08;
			bit_rw_t<ier08, bitpos::B0>	IRQ0;
			bit_rw_t<ier08, bitpos::B1>	IRQ1;
			bit_rw_t<ier08, bitpos::B2>	IRQ2;
			bit_rw_t<ier08, bitpos::B3>	IRQ3;
			bit_rw_t<ier08, bitpos::B4>	IRQ4;
			bit_rw_t<ier08, bitpos::B5>	IRQ5;
			bit_rw_t<ier08, bitpos::B6>	IRQ6;
			bit_rw_t<ier08, bitpos::B7>	IRQ7;

			typedef rw8_t<base + 0x09> ier09;
			bit_rw_t<ier09, bitpos::B0>	IRQ8;
			bit_rw_t<ier09, bitpos::B1>	IRQ9;
			bit_rw_t<ier09, bitpos::B2>	IRQ10;
			bit_rw_t<ier09, bitpos::B3>	IRQ11;
			bit_rw_t<ier09, bitpos::B4>	IRQ12;
			bit_rw_t<ier09, bitpos::B5>	IRQ13;
			bit_rw_t<ier09, bitpos::B6>	IRQ14;
			bit_rw_t<ier09, bitpos::B7>	IRQ15;

			typedef rw8_t<base + 0x0A> ier0A;
			bit_rw_t<ier0A, bitpos::B0>	RXI3;
			bit_rw_t<ier0A, bitpos::B1>	TXI3;
			bit_rw_t<ier0A, bitpos::B2>	RXI4;
			bit_rw_t<ier0A, bitpos::B3>	TXI4;
			bit_rw_t<ier0A, bitpos::B4>	RXI5;
			bit_rw_t<ier0A, bitpos::B5>	TXI5;
			bit_rw_t<ier0A, bitpos::B6>	RXI6;
			bit_rw_t<ier0A, bitpos::B7>	TXI6;

			typedef rw8_t<base + 0x0C> ier0C;
			bit_rw_t<ier0C, bitpos::B2>	RXI7;
			bit_rw_t<ier0C, bitpos::B3>	TXI7;
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
			rw8_t<base + 0> BUSERR;

			rw8_t<base + 4> CMI0;
			rw8_t<base + 5> CMI1;

			rw8_t<base + 58> RXI0;
			rw8_t<base + 59> TXI0;
			rw8_t<base + 60> RXI1;
			rw8_t<base + 61> TXI1;
			rw8_t<base + 62> RXI2;
			rw8_t<base + 63> TXI2;

			rw8_t<base + 64> IRQ0;
			rw8_t<base + 65> IRQ1;
			rw8_t<base + 66> IRQ2;
			rw8_t<base + 67> IRQ3;
			rw8_t<base + 68> IRQ4;
			rw8_t<base + 69> IRQ5;
			rw8_t<base + 70> IRQ6;
			rw8_t<base + 71> IRQ7;

			rw8_t<base + 72> IRQ8;
			rw8_t<base + 73> IRQ9;
			rw8_t<base + 74> IRQ10;
			rw8_t<base + 75> IRQ11;
			rw8_t<base + 76> IRQ12;
			rw8_t<base + 77> IRQ13;
			rw8_t<base + 78> IRQ14;
			rw8_t<base + 79> IRQ15;

			rw8_t<base + 80> RXI3;
			rw8_t<base + 81> TXI3;

			rw8_t<base + 82> RXI4;
			rw8_t<base + 83> TXI4;
			rw8_t<base + 84> RXI5;
			rw8_t<base + 85> TXI5;
			rw8_t<base + 86> RXI6;
			rw8_t<base + 87> TXI6;


			rw8_t<base + 98> RXI7;
			rw8_t<base + 99> TXI7;
		};
		static ipr_t<0x00087300> IPR;

	};
	typedef icu_t ICU;
}
