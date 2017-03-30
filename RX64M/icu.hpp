#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・ICUb 定義 @n
			Copyright 2016,2017 Kunihito Hiramatsu
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

			RIIC_RXI0    = 52,  // RIIC0
			RIIC_TXI0    = 53,
			RIIC_RXI2    = 54,  // RIIC2
			RIIC_TXI2    = 55,

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

			CMI2     = 256,  // CMT2 (group)
			CMI3     = 257,  // CMT3 (group)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {
			rw8_t<base + 28> CMI0;
			rw8_t<base + 29> CMI1;

			rw8_t<base + 52> RIIC_RXI0;
			rw8_t<base + 53> RIIC_TXI0;
			rw8_t<base + 64> RIIC_RXI2;
			rw8_t<base + 65> RIIC_TXI2;

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

			rw8_t<base + 106> GROUPBE0;
			rw8_t<base + 110> GROUPBL0;
			rw8_t<base + 111> GROUPBL1;
			rw8_t<base + 112> GROUPAL0;
			rw8_t<base + 113> GROUPAL1;
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

			typedef rw8_t<base + 0x06> ier06;
			bit_rw_t<ier06, bitpos::B4>	RIIC_RXI0;
			bit_rw_t<ier06, bitpos::B5>	RIIC_TXI0;
			bit_rw_t<ier06, bitpos::B6>	RIIC_RXI2;
			bit_rw_t<ier06, bitpos::B7>	RIIC_TXI2;

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

			typedef rw8_t<base + 0x0D> ier0D;
			bit_rw_t<ier0D, bitpos::B2>	GROUPBE0;
			bit_rw_t<ier0D, bitpos::B6>	GROUPBL0;
			bit_rw_t<ier0D, bitpos::B7>	GROUPBL1;
			typedef rw8_t<base + 0x0E> ier0E;
			bit_rw_t<ier0E, bitpos::B0>	GROUPAL0;
			bit_rw_t<ier0E, bitpos::B1> GROUPAL1;
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

			rw8_t<base + 52> RIIC_RXI0;
			rw8_t<base + 53> RIIC_TXI0;
			rw8_t<base + 54> RIIC_RXI2;
			rw8_t<base + 55> RIIC_TXI2;

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

			rw8_t<base + 106> GROUPBE0;
			rw8_t<base + 110> GROUPBL0;
			rw8_t<base + 111> GROUPBL1;
			rw8_t<base + 112> GROUPAL0;
			rw8_t<base + 113> GROUPAL1;
		};
		static ipr_t<0x00087300> IPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み要求レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct grp_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>  IS0;
			bit_ro_t <io_, bitpos::B1>  IS1;
			bit_ro_t <io_, bitpos::B2>  IS2;
			bit_ro_t <io_, bitpos::B3>  IS3;
			bit_ro_t <io_, bitpos::B4>  IS4;
			bit_ro_t <io_, bitpos::B5>  IS5;
			bit_ro_t <io_, bitpos::B6>  IS6;
			bit_ro_t <io_, bitpos::B7>  IS7;

			bit_ro_t <io_, bitpos::B8>  IS8;
			bit_ro_t <io_, bitpos::B9>  IS9;
			bit_ro_t <io_, bitpos::B10> IS10;
			bit_ro_t <io_, bitpos::B11> IS11;
			bit_ro_t <io_, bitpos::B12> IS12;
			bit_ro_t <io_, bitpos::B13> IS13;
			bit_ro_t <io_, bitpos::B14> IS14;
			bit_ro_t <io_, bitpos::B15> IS15;

			bit_ro_t <io_, bitpos::B16> IS16;
			bit_ro_t <io_, bitpos::B17> IS17;
			bit_ro_t <io_, bitpos::B18> IS18;
			bit_ro_t <io_, bitpos::B19> IS19;
			bit_ro_t <io_, bitpos::B20> IS20;
			bit_ro_t <io_, bitpos::B21> IS21;
			bit_ro_t <io_, bitpos::B22> IS22;
			bit_ro_t <io_, bitpos::B23> IS23;

			bit_ro_t <io_, bitpos::B24> IS24;
			bit_ro_t <io_, bitpos::B25> IS25;
			bit_ro_t <io_, bitpos::B26> IS26;
			bit_ro_t <io_, bitpos::B27> IS27;
			bit_ro_t <io_, bitpos::B28> IS28;
			bit_ro_t <io_, bitpos::B29> IS29;
			bit_ro_t <io_, bitpos::B30> IS30;
			bit_ro_t <io_, bitpos::B31> IS31;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求レジスタ（GRPBE0）@n
					グループ BL0/1 割り込み要求レジスタ（GRPBL0/GRPBL1）@n
					グループ AL0/1 割り込み要求レジスタ（GRPAL0/GRPAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static grp_t<0x00087600> GRPBE0;
		static grp_t<0x00087630> GRPBL0;
		static grp_t<0x00087634> GRPBL1;
		static grp_t<0x00087830> GRPAL0;
		static grp_t<0x00087834> GRPAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み要求許可レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct gen_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  EN0;
			bit_rw_t <io_, bitpos::B1>  EN1;
			bit_rw_t <io_, bitpos::B2>  EN2;
			bit_rw_t <io_, bitpos::B3>  EN3;
			bit_rw_t <io_, bitpos::B4>  EN4;
			bit_rw_t <io_, bitpos::B5>  EN5;
			bit_rw_t <io_, bitpos::B6>  EN6;
			bit_rw_t <io_, bitpos::B7>  EN7;

			bit_rw_t <io_, bitpos::B8>  EN8;
			bit_rw_t <io_, bitpos::B9>  EN9;
			bit_rw_t <io_, bitpos::B10> EN10;
			bit_rw_t <io_, bitpos::B11> EN11;
			bit_rw_t <io_, bitpos::B12> EN12;
			bit_rw_t <io_, bitpos::B13> EN13;
			bit_rw_t <io_, bitpos::B14> EN14;
			bit_rw_t <io_, bitpos::B15> EN15;

			bit_rw_t <io_, bitpos::B16> EN16;
			bit_rw_t <io_, bitpos::B17> EN17;
			bit_rw_t <io_, bitpos::B18> EN18;
			bit_rw_t <io_, bitpos::B19> EN19;
			bit_rw_t <io_, bitpos::B20> EN20;
			bit_rw_t <io_, bitpos::B21> EN21;
			bit_rw_t <io_, bitpos::B22> EN22;
			bit_rw_t <io_, bitpos::B23> EN23;

			bit_rw_t <io_, bitpos::B24> EN24;
			bit_rw_t <io_, bitpos::B25> EN25;
			bit_rw_t <io_, bitpos::B26> EN26;
			bit_rw_t <io_, bitpos::B27> EN27;
			bit_rw_t <io_, bitpos::B28> EN28;
			bit_rw_t <io_, bitpos::B29> EN29;
			bit_rw_t <io_, bitpos::B30> EN30;
			bit_rw_t <io_, bitpos::B31> EN31;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求許可レジスタ（GENBE0）@n
					グループ BL0/1 割り込み要求許可レジスタ（GENBL0/GENBL1）@n
					グループ AL0/1 割り込み要求許可レジスタ（GENAL0/GENAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static gen_t<0x00087640> GENBE0;
		static gen_t<0x00087670> GENBL0;
		static gen_t<0x00087674> GENBL1;
		static gen_t<0x00087870> GENAL0;
		static gen_t<0x00087874> GENAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込みクリアレジスタ（GCRBE0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct gcrbe0_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CLR0;
			bit_rw_t <io_, bitpos::B1>  CLR1;
			bit_rw_t <io_, bitpos::B2>  CLR2;
			bit_rw_t <io_, bitpos::B3>  CLR3;
			bit_rw_t <io_, bitpos::B4>  CLR4;
			bit_rw_t <io_, bitpos::B5>  CLR5;
			bit_rw_t <io_, bitpos::B6>  CLR6;
			bit_rw_t <io_, bitpos::B7>  CLR7;

			bit_rw_t <io_, bitpos::B8>  CLR8;
			bit_rw_t <io_, bitpos::B9>  CLR9;
			bit_rw_t <io_, bitpos::B10> CLR10;
			bit_rw_t <io_, bitpos::B11> CLR11;
			bit_rw_t <io_, bitpos::B12> CLR12;
			bit_rw_t <io_, bitpos::B13> CLR13;
			bit_rw_t <io_, bitpos::B14> CLR14;
			bit_rw_t <io_, bitpos::B15> CLR15;

			bit_rw_t <io_, bitpos::B16> CLR16;
			bit_rw_t <io_, bitpos::B17> CLR17;
			bit_rw_t <io_, bitpos::B18> CLR18;
			bit_rw_t <io_, bitpos::B19> CLR19;
			bit_rw_t <io_, bitpos::B20> CLR20;
			bit_rw_t <io_, bitpos::B21> CLR21;
			bit_rw_t <io_, bitpos::B22> CLR22;
			bit_rw_t <io_, bitpos::B23> CLR23;

			bit_rw_t <io_, bitpos::B24> CLR24;
			bit_rw_t <io_, bitpos::B25> CLR25;
			bit_rw_t <io_, bitpos::B26> CLR26;
			bit_rw_t <io_, bitpos::B27> CLR27;
			bit_rw_t <io_, bitpos::B28> CLR28;
			bit_rw_t <io_, bitpos::B29> CLR29;
			bit_rw_t <io_, bitpos::B30> CLR30;
			bit_rw_t <io_, bitpos::B31> CLR31;
		};
		static gcrbe0_t<0x00087680> GCRBE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み要求レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pixr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  PIR0;
			bit_rw_t <io_, bitpos::B1>  PIR1;
			bit_rw_t <io_, bitpos::B2>  PIR2;
			bit_rw_t <io_, bitpos::B3>  PIR3;
			bit_rw_t <io_, bitpos::B4>  PIR4;
			bit_rw_t <io_, bitpos::B5>  PIR5;
			bit_rw_t <io_, bitpos::B6>  PIR6;
			bit_rw_t <io_, bitpos::B7>  PIR7;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み B 要求レジスタ k（PIBRk）（k = 0h ～ Ah）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pixr_t<0x00087700> PIBR0;
		static pixr_t<0x00087701> PIBR1;
		static pixr_t<0x00087702> PIBR2;
		static pixr_t<0x00087703> PIBR3;
		static pixr_t<0x00087704> PIBR4;
		static pixr_t<0x00087705> PIBR5;
		static pixr_t<0x00087706> PIBR6;
		static pixr_t<0x00087707> PIBR7;
		static pixr_t<0x00087708> PIBR8;
		static pixr_t<0x00087709> PIBR9;
		static pixr_t<0x0008770A> PIBRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要求レジスタ k（PIARk）（k = 0h ～ Bh）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pixr_t<0x00087900> PIAR0;
		static pixr_t<0x00087901> PIAR1;
		static pixr_t<0x00087902> PIAR2;
		static pixr_t<0x00087903> PIAR3;
		static pixr_t<0x00087904> PIAR4;
		static pixr_t<0x00087905> PIAR5;
		static pixr_t<0x00087906> PIAR6;
		static pixr_t<0x00087907> PIAR7;
		static pixr_t<0x00087908> PIAR8;
		static pixr_t<0x00087909> PIAR9;
		static pixr_t<0x0008790A> PIARA;
		static pixr_t<0x0008790B> PIARB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み B 要因選択レジスタ Xn（SLIBXRn）（n = 128 ～ 143）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x00087780> SLIBX128;
		static rw8_t<0x00087781> SLIBX129;
		static rw8_t<0x00087782> SLIBX130;
		static rw8_t<0x00087783> SLIBX131;
		static rw8_t<0x00087784> SLIBX132;
		static rw8_t<0x00087785> SLIBX133;
		static rw8_t<0x00087786> SLIBX134;
		static rw8_t<0x00087787> SLIBX135;
		static rw8_t<0x00087788> SLIBX136;
		static rw8_t<0x00087789> SLIBX137;
		static rw8_t<0x0008778A> SLIBX138;
		static rw8_t<0x0008778B> SLIBX139;
		static rw8_t<0x0008778C> SLIBX140;
		static rw8_t<0x0008778D> SLIBX141;
		static rw8_t<0x0008778E> SLIBX142;
		static rw8_t<0x0008778F> SLIBX143;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み B 要因選択レジスタ n（SLIBRn）（n = 144 ～ 207）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x00087790> SLIBR144;
		static rw8_t<0x00087791> SLIBR145;
		static rw8_t<0x00087792> SLIBR146;
		static rw8_t<0x00087793> SLIBR147;
		static rw8_t<0x00087794> SLIBR148;
		static rw8_t<0x00087795> SLIBR149;
		static rw8_t<0x00087796> SLIBR150;
		static rw8_t<0x00087797> SLIBR151;
		static rw8_t<0x00087798> SLIBR152;
		static rw8_t<0x00087799> SLIBR153;
		static rw8_t<0x0008779A> SLIBR154;
		static rw8_t<0x0008779B> SLIBR155;
		static rw8_t<0x0008779C> SLIBR156;
		static rw8_t<0x0008779D> SLIBR157;
		static rw8_t<0x0008779E> SLIBR158;
		static rw8_t<0x0008779F> SLIBR159;

		static rw8_t<0x000877A0> SLIBR160;
		static rw8_t<0x000877A1> SLIBR161;
		static rw8_t<0x000877A2> SLIBR162;
		static rw8_t<0x000877A3> SLIBR163;
		static rw8_t<0x000877A4> SLIBR164;
		static rw8_t<0x000877A5> SLIBR165;
		static rw8_t<0x000877A6> SLIBR166;
		static rw8_t<0x000877A7> SLIBR167;
		static rw8_t<0x000877A8> SLIBR168;
		static rw8_t<0x000877A9> SLIBR169;
		static rw8_t<0x000877AA> SLIBR170;
		static rw8_t<0x000877AB> SLIBR171;
		static rw8_t<0x000877AC> SLIBR172;
		static rw8_t<0x000877AD> SLIBR173;
		static rw8_t<0x000877AE> SLIBR174;
		static rw8_t<0x000877AF> SLIBR175;

		static rw8_t<0x000877B0> SLIBR176;
		static rw8_t<0x000877B1> SLIBR177;
		static rw8_t<0x000877B2> SLIBR178;
		static rw8_t<0x000877B3> SLIBR179;
		static rw8_t<0x000877B4> SLIBR180;
		static rw8_t<0x000877B5> SLIBR181;
		static rw8_t<0x000877B6> SLIBR182;
		static rw8_t<0x000877B7> SLIBR183;
		static rw8_t<0x000877B8> SLIBR184;
		static rw8_t<0x000877B9> SLIBR185;
		static rw8_t<0x000877BA> SLIBR186;
		static rw8_t<0x000877BB> SLIBR187;
		static rw8_t<0x000877BC> SLIBR188;
		static rw8_t<0x000877BD> SLIBR189;
		static rw8_t<0x000877BE> SLIBR190;
		static rw8_t<0x000877BF> SLIBR191;

		static rw8_t<0x000877C0> SLIBR192;
		static rw8_t<0x000877C1> SLIBR193;
		static rw8_t<0x000877C2> SLIBR194;
		static rw8_t<0x000877C3> SLIBR195;
		static rw8_t<0x000877C4> SLIBR196;
		static rw8_t<0x000877C5> SLIBR197;
		static rw8_t<0x000877C6> SLIBR198;
		static rw8_t<0x000877C7> SLIBR199;
		static rw8_t<0x000877C8> SLIBR200;
		static rw8_t<0x000877C9> SLIBR201;
		static rw8_t<0x000877CA> SLIBR202;
		static rw8_t<0x000877CB> SLIBR203;
		static rw8_t<0x000877CC> SLIBR204;
		static rw8_t<0x000877CD> SLIBR205;
		static rw8_t<0x000877CE> SLIBR206;
		static rw8_t<0x000877CF> SLIBR207;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要因選択レジスタ n（SLIARn）（n = 208 ～ 255）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x000879D0> SLIAR208;
		static rw8_t<0x000879D1> SLIAR209;
		static rw8_t<0x000879D2> SLIAR210;
		static rw8_t<0x000879D3> SLIAR211;
		static rw8_t<0x000879D4> SLIAR212;
		static rw8_t<0x000879D5> SLIAR213;
		static rw8_t<0x000879D6> SLIAR214;
		static rw8_t<0x000879D7> SLIAR215;
		static rw8_t<0x000879D8> SLIAR216;
		static rw8_t<0x000879D9> SLIAR217;
		static rw8_t<0x000879DA> SLIAR218;
		static rw8_t<0x000879DB> SLIAR219;
		static rw8_t<0x000879DC> SLIAR220;
		static rw8_t<0x000879DD> SLIAR221;
		static rw8_t<0x000879DE> SLIAR222;
		static rw8_t<0x000879DF> SLIAR223;

		static rw8_t<0x000879E0> SLIAR224;
		static rw8_t<0x000879E1> SLIAR225;
		static rw8_t<0x000879E2> SLIAR226;
		static rw8_t<0x000879E3> SLIAR227;
		static rw8_t<0x000879E4> SLIAR228;
		static rw8_t<0x000879E5> SLIAR229;
		static rw8_t<0x000879E6> SLIAR230;
		static rw8_t<0x000879E7> SLIAR231;
		static rw8_t<0x000879E8> SLIAR232;
		static rw8_t<0x000879E9> SLIAR233;
		static rw8_t<0x000879EA> SLIAR234;
		static rw8_t<0x000879EB> SLIAR235;
		static rw8_t<0x000879EC> SLIAR236;
		static rw8_t<0x000879ED> SLIAR237;
		static rw8_t<0x000879EE> SLIAR238;
		static rw8_t<0x000879EF> SLIAR239;

		static rw8_t<0x000879F0> SLIAR240;
		static rw8_t<0x000879F1> SLIAR241;
		static rw8_t<0x000879F2> SLIAR242;
		static rw8_t<0x000879F3> SLIAR243;
		static rw8_t<0x000879F4> SLIAR244;
		static rw8_t<0x000879F5> SLIAR245;
		static rw8_t<0x000879F6> SLIAR246;
		static rw8_t<0x000879F7> SLIAR247;
		static rw8_t<0x000879F8> SLIAR248;
		static rw8_t<0x000879F9> SLIAR249;
		static rw8_t<0x000879FA> SLIAR250;
		static rw8_t<0x000879FB> SLIAR251;
		static rw8_t<0x000879FC> SLIAR252;
		static rw8_t<0x000879FD> SLIAR253;
		static rw8_t<0x000879FE> SLIAR254;
		static rw8_t<0x000879FF> SLIAR255;
	};
	typedef icu_t ICU;
}
