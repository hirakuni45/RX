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
		struct VECTOR {
		  enum type { 
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

			rw8_t<base + 1> FIFERR;
			rw8_t<base + 2> FRDIY;

			rw8_t<base + 3> SWINT;

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

#if 0
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FIR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<0x000872f0> fir_io;
		struct fir_t : public fir_io {
			using fir_io::operator =;
			using fir_io::operator ();
			using fir_io::operator |=;
			using fir_io::operator &=;
			
			bits_rw_t<fir_io, bitpos::B0, 8> FVCT;
			bit_rw_t<fir_io, bitpos::B15> FIEN;
		};
		static fir_t FIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SWINTR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000872e0> swintr_io;
		struct swintr_t : public swintr_io {
			using swintr_io::operator =;
			using swintr_io::operator ();
			using swintr_io::operator |=;
			using swintr_io::operator &=;
			
			bit_rw_t<swintr_io, bitpos::B0> SWINT;
		};
		static swintr_t SWINTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct dtc_t {

			template <uint32_t base>
			struct dtce_t : public rw8_t<base> {
				typedef rw8_t<base> rw8_t;				
				using rw8_t::operator =;
				using rw8_t::operator ();
				using rw8_t::operator |=;
				using rw8_t::operator &=;

				bit_rw_t<rw8_t, 0>	DTCE;
			};
			dtce_t<0x00087100 + 27> DTCER027;
			dtce_t<0x00087100 + 28> DTCER028;
			dtce_t<0x00087100 + 29> DTCER029;
			dtce_t<0x00087100 + 30> DTCER030;
			dtce_t<0x00087100 + 31> DTCER031;

			dtce_t<0x00087100 + 36> DTCER036;
			dtce_t<0x00087100 + 37> DTCER037;

			dtce_t<0x00087100 + 40> DTCER040;
			dtce_t<0x00087100 + 41> DTCER041;

			dtce_t<0x00087100 + 45> DTCER045;
			dtce_t<0x00087100 + 46> DTCER046;

			dtce_t<0x00087100 + 49> DTCER049;
			dtce_t<0x00087100 + 50> DTCER050;

			dtce_t<0x00087100 + 64> DTCER064;
			dtce_t<0x00087100 + 65> DTCER065;
			dtce_t<0x00087100 + 66> DTCER066;
			dtce_t<0x00087100 + 67> DTCER067;
			dtce_t<0x00087100 + 68> DTCER068;
			dtce_t<0x00087100 + 69> DTCER069;
			dtce_t<0x00087100 + 70> DTCER070;
			dtce_t<0x00087100 + 71> DTCER071;
			dtce_t<0x00087100 + 72> DTCER072;
			dtce_t<0x00087100 + 73> DTCER073;
			dtce_t<0x00087100 + 74> DTCER074;
			dtce_t<0x00087100 + 75> DTCER075;
			dtce_t<0x00087100 + 76> DTCER076;
			dtce_t<0x00087100 + 77> DTCER077;
			dtce_t<0x00087100 + 78> DTCER078;
			dtce_t<0x00087100 + 79> DTCER079;

			dtce_t<0x00087100 + 98> DTCER098;
			dtce_t<0x00087100 + 99> DTCER099;

			dtce_t<0x00087100 + 102> DTCER102;

			dtce_t<0x00087100 + 114> DTCER114;
			dtce_t<0x00087100 + 115> DTCER115;
			dtce_t<0x00087100 + 116> DTCER116;
			dtce_t<0x00087100 + 117> DTCER117;

			dtce_t<0x00087100 + 121> DTCER121;
			dtce_t<0x00087100 + 122> DTCER122;

			dtce_t<0x00087100 + 125> DTCER125;
			dtce_t<0x00087100 + 126> DTCER126;

			dtce_t<0x00087100 + 129> DTCER129;
			dtce_t<0x00087100 + 130> DTCER130;
			dtce_t<0x00087100 + 131> DTCER131;
			dtce_t<0x00087100 + 132> DTCER132;
			dtce_t<0x00087100 + 133> DTCER133;
			dtce_t<0x00087100 + 134> DTCER134;
			dtce_t<0x00087100 + 135> DTCER135;
			dtce_t<0x00087100 + 136> DTCER136;
			dtce_t<0x00087100 + 137> DTCER137;
			dtce_t<0x00087100 + 138> DTCER138;
			dtce_t<0x00087100 + 139> DTCER139;
			dtce_t<0x00087100 + 140> DTCER140;
			dtce_t<0x00087100 + 141> DTCER141;
			dtce_t<0x00087100 + 142> DTCER142;
			dtce_t<0x00087100 + 143> DTCER143;
			dtce_t<0x00087100 + 144> DTCER144;
			dtce_t<0x00087100 + 145> DTCER145;

			dtce_t<0x00087100 + 149> DTCER149;
			dtce_t<0x00087100 + 150> DTCER150;

			dtce_t<0x00087100 + 153> DTCER153;
			dtce_t<0x00087100 + 154> DTCER154;

			dtce_t<0x00087100 + 157> DTCER157;
			dtce_t<0x00087100 + 158> DTCER158;
			dtce_t<0x00087100 + 159> DTCER159;
			dtce_t<0x00087100 + 160> DTCER160;

			dtce_t<0x00087100 + 162> DTCER162;
			dtce_t<0x00087100 + 163> DTCER163;
			dtce_t<0x00087100 + 164> DTCER164;
			dtce_t<0x00087100 + 165> DTCER165;
			dtce_t<0x00087100 + 166> DTCER166;
			dtce_t<0x00087100 + 167> DTCER167;
			dtce_t<0x00087100 + 168> DTCER168;
			dtce_t<0x00087100 + 169> DTCER169;

			dtce_t<0x00087100 + 174> DTCER174;
			dtce_t<0x00087100 + 175> DTCER175;

			dtce_t<0x00087100 + 177> DTCER177;
			dtce_t<0x00087100 + 178> DTCER178;

			dtce_t<0x00087100 + 180> DTCER180;
			dtce_t<0x00087100 + 181> DTCER181;

			dtce_t<0x00087100 + 183> DTCER183;
			dtce_t<0x00087100 + 184> DTCER184;

			dtce_t<0x00087100 + 198> DTCER198;
			dtce_t<0x00087100 + 199> DTCER199;
			dtce_t<0x00087100 + 200> DTCER200;
			dtce_t<0x00087100 + 201> DTCER201;
			dtce_t<0x00087100 + 202> DTCER202;
			dtce_t<0x00087100 + 203> DTCER203;

			dtce_t<0x00087100 + 215> DTCER215;
			dtce_t<0x00087100 + 216> DTCER216;

			dtce_t<0x00087100 + 219> DTCER219;

			dtce_t<0x00087100 + 220> DTCER220;

			dtce_t<0x00087100 + 223> DTCER223;
			dtce_t<0x00087100 + 224> DTCER224;

			dtce_t<0x00087100 + 227> DTCER227;
			dtce_t<0x00087100 + 228> DTCER228;

			dtce_t<0x00087100 + 235> DTCER235;
			dtce_t<0x00087100 + 236> DTCER236;

			dtce_t<0x00087100 + 239> DTCER239;
			dtce_t<0x00087100 + 240> DTCER240;

			dtce_t<0x00087100 + 247> DTCER247;
			dtce_t<0x00087100 + 248> DTCER248;

			dtce_t<0x00087100 + 251> DTCER251;
			dtce_t<0x00087100 + 252> DTCER252;
		};
		static dtc_t DTC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMACA レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct dmaca_t {
			rw8_t<0x00087400 + 0x00> DMRSR0;
			rw8_t<0x00087400 + 0x04> DMRSR1;
			rw8_t<0x00087400 + 0x08> DMRSR2;
			rw8_t<0x00087400 + 0x0c> DMRSR3;
		};
		static dmaca_t DMACA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqcr_t : public rw8_t<base> {
			typedef rw8_t<base> rw8_t_;
			using rw8_t_::operator =;
			using rw8_t_::operator ();
			using rw8_t_::operator |=;
			using rw8_t_::operator &=;

			bits_rw_t<rw8_t_, B2, 2>	IRQMD;
		};
		static irqcr_t<0x00087500 + 0x00> IRQCR0;
		static irqcr_t<0x00087500 + 0x01> IRQCR1;
		static irqcr_t<0x00087500 + 0x02> IRQCR2;
		static irqcr_t<0x00087500 + 0x03> IRQCR3;
		static irqcr_t<0x00087500 + 0x04> IRQCR4;
		static irqcr_t<0x00087500 + 0x05> IRQCR5;
		static irqcr_t<0x00087500 + 0x06> IRQCR6;
		static irqcr_t<0x00087500 + 0x07> IRQCR7;
		static irqcr_t<0x00087500 + 0x08> IRQCR8;
		static irqcr_t<0x00087500 + 0x09> IRQCR9;
		static irqcr_t<0x00087500 + 0x0a> IRQCR10;
		static irqcr_t<0x00087500 + 0x0b> IRQCR11;
		static irqcr_t<0x00087500 + 0x0c> IRQCR12;
		static irqcr_t<0x00087500 + 0x0d> IRQCR13;
		static irqcr_t<0x00087500 + 0x0e> IRQCR14;
		static irqcr_t<0x00087500 + 0x0f> IRQCR15;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMISR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087580> nmisr_io;
		struct nmisr_t : public nmisr_io {
			using nmisr_io::operator =;
			using nmisr_io::operator ();
			using nmisr_io::operator |=;
			using nmisr_io::operator &=;

			bit_rw_t<nmisr_io, bitpos::B0>	NMIST;
			bit_rw_t<nmisr_io, bitpos::B1>	LVDST;
			bit_rw_t<nmisr_io, bitpos::B2>	OSTST;
		};
		static nmisr_t NMISR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMIER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087581> nmier_io;
		struct nmier_t : public nmier_io {
			using nmier_io::operator =;
			using nmier_io::operator ();
			using nmier_io::operator |=;
			using nmier_io::operator &=;

			bit_rw_t<nmier_io, bitpos::B0>	NMIEN;
			bit_rw_t<nmier_io, bitpos::B1>	LVDEN;
			bit_rw_t<nmier_io, bitpos::B2>	OSTEN;
		};
		static nmier_t NMIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMICLR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087582> nmiclr_io;
		struct nmiclr_t : public nmiclr_io {
			using nmiclr_io::operator =;
			using nmiclr_io::operator ();
			using nmiclr_io::operator |=;
			using nmiclr_io::operator &=;

			bit_rw_t<nmiclr_io, bitpos::B0>	NMICLR;
			bit_rw_t<nmiclr_io, bitpos::B2>	OSTCLR;
		};
		static nmiclr_t NMICLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMICR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087583> nmicr_io;
		struct nmicr_t : public nmicr_io {
			using nmicr_io::operator =;
			using nmicr_io::operator ();
			using nmicr_io::operator |=;
			using nmicr_io::operator &=;

			bit_rw_t<nmicr_io, bitpos::B3>	NMIMD;
		};
		static nmicr_t NMICR;
#endif
	};
	typedef icu_t ICU;
}
