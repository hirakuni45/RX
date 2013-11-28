#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621 グループ・ICUa 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ICUa 定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct VECTOR {
			enum index {
				BUSERR = 16,

				FIFERR = 21,

				FRDYI = 23,

				SWINT = 27,

				CMI0 = 28,
				CMI1 = 29,
				CMI2 = 30,
				CMI3 = 31,

				EINT = 32,

				D0FIFO0 = 36,
				D1FIFO0 = 37,
				USBI0 = 38,

				D0FIFO1 = 40,
				D1FIFO1 = 41,
				USBI1 = 42,

				SPEI0 = 44,
				SPRI0 = 45,
				SPTI0 = 46,
				SPII0 = 47,

				SPEI1 = 48,
				SPRI1 = 49,
				SPTI1 = 50,
				SPII1 = 51,

				ERS0 = 56,
				RXF0 = 57,
				TXF0 = 58,
				RXM0 = 59,
				TXM0 = 60,

				PRD = 62,
				CUP = 63,

				IRQ0 = 64,
				IRQ1 = 65,
				IRQ2 = 66,
				IRQ3 = 67,
				IRQ4 = 68,
				IRQ5 = 69,
				IRQ6 = 70,
				IRQ7 = 71,
				IRQ8 = 72,
				IRQ9 = 73,
				IRQ10 = 74,
				IRQ11 = 75,
				IRQ12 = 76,
				IRQ13 = 77,
				IRQ14 = 78,
				IRQ15 = 79,

				USBR0 = 90,
				USBR1 = 91,

				ALM = 92,

				WOVI = 96,

				ADI0 = 98,
				ADI1 = 99,

				S12ADI0 = 102,

				TGIA0 = 114,
				TGIB0 = 115,
				TGIC0 = 116,
				TGID0 = 117,
				TCIV0 = 118,
				TGIE0 = 119,
				TGIF0 = 120,

				TGIA1 = 121,
				TGIB1 = 122,
				TCIV1 = 123,
				TCIU1 = 124,

				TGIA2 = 125,
				TGIB2 = 126,
				TCIV2 = 127,
				TCIU2 = 128,

				TGIA3 = 129,
				TGIB3 = 130,
				TGIC3 = 131,
				TGID3 = 132,
				TCIV3 = 133,

				TGIA4 = 134,
				TGIB4 = 135,
				TGIC4 = 136,
				TGID4 = 137,
				TCIV4 = 138,

				TGIU5 = 139,
				TGIV5 = 140,
				TGIW5 = 141,

				TGIA6 = 142,
				TGIB6 = 143,
				TGIC6 = 144,
				TGID6 = 145,
				TCIV6 = 146,
				TGIE6 = 147,
				TGIF6 = 148,

				TGIA7 = 149,
				TGIB7 = 150,
				TCIV7 = 151,
				TCIU7 = 152,

				TGIA8 = 153,
				TGIB8 = 154,
				TCIV8 = 155,
				TCIU8 = 156,

				TGIA9 = 157,
				TGIB9 = 158,
				TGIC9 = 159,
				TGID9 = 160,
				TCIV9 = 161,

				TGIA10 = 162,
				TGIB10 = 163,
				TGIC10 = 164,
				TGID10 = 165,
				TCIV10 = 166,

				TGIU11 = 167,
				TGIV11 = 168,
				TGIW11 = 169,

				OEI1 = 170,
				OEI2 = 171,
				OEI3 = 172,
				OEI4 = 173,

				CMIA0 = 174,
				CMIB0 = 175,
				OVI0 = 176,

				CMIA1 = 177,
				CMIB1 = 178,
				OVI1 = 179,

				CMIA2 = 180,
				CMIB2 = 181,
				OVI2 = 182,

				CMIA3 = 183,
				CMIB3 = 184,
				OVI3 = 185,

				DMACI0 = 198,
				DMACI1 = 199,
				DMACI2 = 200,
				DMACI3 = 201,

				EXDMACI0 = 202,
				EXDMACI1 = 203,

				ERI0 = 214,
				RXI0 = 215,
				TXI0 = 216,
				TEI0 = 217,

				ERI1 = 218,
				RXI1 = 219,
				TXI1 = 220,
				TEI1 = 221,

				ERI2 = 222,
				RXI2 = 223,
				TXI2 = 224,
				TEI2 = 225,

				ERI3 = 226,
				RXI3 = 227,
				TXI3 = 228,
				TEI3 = 229,

				ERI5 = 234,
				RXI5 = 235,
				TXI5 = 236,
				TEI5 = 237,

				ERI6 = 238,
				RXI6 = 239,
				TXI6 = 240,
				TEI6 = 241,

				ICEEI0 = 246,
				ICRXI0 = 247,
				ICTXI0 = 248,
				ICTEI0 = 249,

				ICEEI1 = 250,
				ICRXI1 = 251,
				ICTXI1 = 252,
				ICTEI1 = 253,
			};
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ier_t {
			typedef io8<base + 0x02> ier02;
			bit_t<ier02, 0>	BUSERR;
			bit_t<ier02, 5>	FIFERR;

			typedef io8<base + 0x03> ier03;
			bit_t<ier03, 3>	SWINT;
			bit_t<ier03, 4>	CMI0;
			bit_t<ier03, 5>	CMI1;
			bit_t<ier03, 6>	CMI2;
			bit_t<ier03, 7>	CMI3;

			typedef io8<base + 0x04> ier04;
			bit_t<ier04, 0>	EINT;

			bit_t<ier04, 4>	D0FIFO0;
			bit_t<ier04, 5>	D1FIFO0;
			bit_t<ier04, 6>	USBI0;

			typedef io8<base + 0x05> ier05;
			bit_t<ier05, 0>	D0FIFO1;
			bit_t<ier05, 1>	D1FIFO1;
			bit_t<ier05, 2>	USBI1;

			bit_t<ier05, 4>	SPEI0;
			bit_t<ier05, 5>	SPRI0;
			bit_t<ier05, 6>	SPTI0;
			bit_t<ier05, 7>	SPII0;

			typedef io8<base + 0x06> ier06;
			bit_t<ier06, 0>	SPEI1;
			bit_t<ier06, 1>	SPRI1;
			bit_t<ier06, 2>	SPTI1;
			bit_t<ier06, 3>	SPII1;

			typedef io8<base + 0x07> ier07;
			bit_t<ier07, 0>	ERS0;
			bit_t<ier07, 1>	RXF0;
			bit_t<ier07, 2>	TXF0;
			bit_t<ier07, 3>	RXM0;
			bit_t<ier07, 4>	TXM0;

			bit_t<ier07, 6>	PRD;
			bit_t<ier07, 7>	CUP;

			typedef io8<base + 0x08> ier08;
			bit_t<ier08, 0>	IRQ0;
			bit_t<ier08, 1>	IRQ1;
			bit_t<ier08, 2>	IRQ2;
			bit_t<ier08, 3>	IRQ3;
			bit_t<ier08, 4>	IRQ4;
			bit_t<ier08, 5>	IRQ5;
			bit_t<ier08, 6>	IRQ6;
			bit_t<ier08, 7>	IRQ7;

			typedef io8<base + 0x09> ier09;
			bit_t<ier09, 0>	IRQ8;
			bit_t<ier09, 1>	IRQ9;
			bit_t<ier09, 2>	IRQ10;
			bit_t<ier09, 3>	IRQ11;
			bit_t<ier09, 4>	IRQ12;
			bit_t<ier09, 5>	IRQ13;
			bit_t<ier09, 6>	IRQ14;
			bit_t<ier09, 7>	IRQ15;

			typedef io8<base + 0x0b> ier0b;
			bit_t<ier0b, 2>	USBR0;
			bit_t<ier0b, 3>	USBR1;

			bit_t<ier0b, 4>	ALM;

			typedef io8<base + 0x0c> ier0c;
			bit_t<ier0c, 0>	WOVI;

			bit_t<ier0c, 2>	ADI0;
			bit_t<ier0c, 3>	ADI1;

			bit_t<ier0c, 6>	S12ADI0;

			typedef io8<base + 0x0e> ier0e;
			bit_t<ier0e, 2>	TGIA0;
			bit_t<ier0e, 3>	TGIB0;
			bit_t<ier0e, 4>	TGIC0;
			bit_t<ier0e, 5>	TGID0;
			bit_t<ier0e, 6>	TCIV0;
			bit_t<ier0e, 7>	TGIE0;
			typedef io8<base + 0x0f> ier0f;
			bit_t<ier0f, 0>	TGIF0;

			bit_t<ier0f, 1>	TGIA1;
			bit_t<ier0f, 2>	TGIB1;
			bit_t<ier0f, 3>	TCIV1;
			bit_t<ier0f, 4>	TCIU1;

			bit_t<ier0f, 5>	TGIA2;
			bit_t<ier0f, 6>	TGIB2;
			bit_t<ier0f, 7>	TCIV2;
			typedef io8<base + 0x10> ier10;
			bit_t<ier10, 0>	TCIU2;

			bit_t<ier10, 1>	TGIA3;
			bit_t<ier10, 2>	TGIB3;
			bit_t<ier10, 3>	TGIC3;
			bit_t<ier10, 4>	TGID3;
			bit_t<ier10, 5>	TCIV3;

			bit_t<ier10, 6>	TGIA4;
			bit_t<ier10, 7>	TGIB4;
			typedef io8<base + 0x11> ier11;
			bit_t<ier11, 0>	TGIC4;
			bit_t<ier11, 1>	TGID4;
			bit_t<ier11, 2>	TCIV4;

			bit_t<ier11, 3>	TGIU5;
			bit_t<ier11, 4>	TGIV5;
			bit_t<ier11, 5>	TGIW5;

			bit_t<ier11, 6>	TGIA6;
			bit_t<ier11, 7>	TGIB6;
			typedef io8<base + 0x12> ier12;
			bit_t<ier12, 0>	TGIC6;
			bit_t<ier12, 1>	TGID6;
			bit_t<ier12, 2>	TCIV6;
			bit_t<ier12, 3>	TGIE6;
			bit_t<ier12, 4>	TGIF6;

			bit_t<ier12, 5>	TGIA7;
			bit_t<ier12, 6>	TGIB7;
			bit_t<ier12, 7>	TCIV7;
			typedef io8<base + 0x13> ier13;
			bit_t<ier13, 0>	TCIU7;

			bit_t<ier13, 1>	TGIA8;
			bit_t<ier13, 2>	TGIB8;
			bit_t<ier13, 3>	TCIV8;
			bit_t<ier13, 4>	TCIU8;

			bit_t<ier13, 5>	TGIA9;
			bit_t<ier13, 6>	TGIB9;
			bit_t<ier13, 7>	TGIC9;
			typedef io8<base + 0x14> ier14;
			bit_t<ier14, 0>	TGID9;
			bit_t<ier14, 1>	TCIV9;

			bit_t<ier14, 2>	TGIA10;
			bit_t<ier14, 3>	TGIB10;
			bit_t<ier14, 4>	TGIC10;
			bit_t<ier14, 5>	TGID10;
			bit_t<ier14, 6>	TCIV10;

			bit_t<ier14, 7>	TGIU11;
			typedef io8<base + 0x15> ier15;
			bit_t<ier15, 0>	TGIV11;
			bit_t<ier15, 1>	TGIW11;

			bit_t<ier15, 2>	OEI1;
			bit_t<ier15, 3>	OEI2;
			bit_t<ier15, 4>	OEI3;
			bit_t<ier15, 5>	OEI4;

			bit_t<ier15, 6>	CMIA0;
			bit_t<ier15, 7>	CMIB0;
			typedef io8<base + 0x16> ier16;
			bit_t<ier16, 0>	OVI0;

			bit_t<ier16, 1>	CMIA1;
			bit_t<ier16, 2>	CMIB1;
			bit_t<ier16, 3>	OVI1;

			bit_t<ier16, 4>	CMIA2;
			bit_t<ier16, 5>	CMIB2;
			bit_t<ier16, 6>	OVI2;

			bit_t<ier16, 7>	CMIA3;
			typedef io8<base + 0x17> ier17;
			bit_t<ier17, 0>	CMIB3;
			bit_t<ier17, 1>	OVI3;

			typedef io8<base + 0x18> ier18;
			bit_t<ier18, 6>	DMACI0;
			bit_t<ier18, 7>	DMACI1;
			typedef io8<base + 0x19> ier19;
			bit_t<ier19, 0>	DMACI2;
			bit_t<ier19, 1>	DMACI3;

			bit_t<ier19, 2>	EXDMACI0;
			bit_t<ier19, 3>	EXDMACI1;

			typedef io8<base + 0x1a> ier1a;
			bit_t<ier1a, 6>	ERI0;
			bit_t<ier1a, 7>	RXI0;
			typedef io8<base + 0x1b> ier1b;
			bit_t<ier1b, 0>	TXI0;
			bit_t<ier1b, 1>	TEI0;

			bit_t<ier1b, 2>	ERI1;
			bit_t<ier1b, 3>	RXI1;
			bit_t<ier1b, 4>	TXI1;
			bit_t<ier1b, 5>	TEI1;

			bit_t<ier1b, 6>	ERI2;
			bit_t<ier1b, 7>	RXI2;
			typedef io8<base + 0x1c> ier1c;
			bit_t<ier1c, 0>	TXI2;
			bit_t<ier1c, 1>	TEI2;

			bit_t<ier1c, 2>	ERI3;
			bit_t<ier1c, 3>	RXI3;
			bit_t<ier1c, 4>	TXI3;
			bit_t<ier1c, 5>	TEI3;

			typedef io8<base + 0x1d> ier1d;
			bit_t<ier1d, 2>	ERI5;
			bit_t<ier1d, 3>	RXI5;
			bit_t<ier1d, 4>	TXI5;
			bit_t<ier1d, 5>	TEI5;

			bit_t<ier1d, 6>	ERI6;
			bit_t<ier1d, 7>	RXI6;
			typedef io8<base + 0x1e> ier1e;
			bit_t<ier1e, 0>	TXI6;
			bit_t<ier1e, 1>	TEI6;

			bit_t<ier1e, 6>	ICEEI0;
			bit_t<ier1e, 7>	ICRXI0;
			typedef io8<base + 0x1f> ier1f;
			bit_t<ier1f, 0>	ICTXI0;
			bit_t<ier1f, 1>	ICTEI0;

			bit_t<ier1f, 2>	ICEEI1;
			bit_t<ier1f, 3>	ICRXI1;
			bit_t<ier1f, 4>	ICTXI1;
			bit_t<ier1f, 5>	ICTEI1;
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
			io8<base + 0x00> BUSERR;

			io8<base + 0x01> FIFERR;
			io8<base + 0x02> FRDIY;

			io8<base + 0x03> SWINT;

			io8<base + 0x04> CMI0;
			io8<base + 0x05> CMI1;
			io8<base + 0x06> CMI2;
			io8<base + 0x07> CMI3;

			io8<base + 0x08> EINT;

			io8<base + 0x0c> D0FIFO0;
			io8<base + 0x0d> D1FIFO0;
			io8<base + 0x0e> USBIO;

			io8<base + 0x10> D0FIFO1;
			io8<base + 0x11> D1FIFO1;
			io8<base + 0x12> USBI1;

			io8<base + 0x14> RSPI0;
			io8<base + 0x15> RSPI1;

			io8<base + 0x18> CAN0;

			io8<base + 0x1e> PRD;
			io8<base + 0x1f> CUP;

			io8<base + 0x20> IRQ0;
			io8<base + 0x21> IRQ1;
			io8<base + 0x22> IRQ2;
			io8<base + 0x23> IRQ3;
			io8<base + 0x24> IRQ4;
			io8<base + 0x25> IRQ5;
			io8<base + 0x26> IRQ6;
			io8<base + 0x27> IRQ7;
			io8<base + 0x28> IRQ8;
			io8<base + 0x29> IRQ9;
			io8<base + 0x2a> IRQ10;
			io8<base + 0x2b> IRQ11;
			io8<base + 0x2c> IRQ12;
			io8<base + 0x2d> IRQ13;
			io8<base + 0x2e> IRQ14;
			io8<base + 0x2f> IRQ15;

			io8<base + 0x3a> USBR0;
			io8<base + 0x3b> USBR1;

			io8<base + 0x3c> ALM;

			io8<base + 0x40> WOVI;

			io8<base + 0x44> ADI0;
			io8<base + 0x45> ADI1;

			io8<base + 0x48> S12ADI0;

			io8<base + 0x51> MTU0_ABCD;	///< TGIA0, TGIB0, TGIC0, TGID0
			io8<base + 0x52> MTU0_VEF;	///< TCIV0, TGIE0, TGIF0

			io8<base + 0x53> MTU1_AB;	///< TGIA1, TGIB1
			io8<base + 0x54> MTU1_VU;	///< TCIV1, TCIU1

			io8<base + 0x55> MTU2_AB;	///< TGIA2, TGIB2
			io8<base + 0x56> MTU2_VU;	///< TCIV2, TCIU2

			io8<base + 0x57> MTU3_ABCD;	///< TGIA3, TGIB3, TGIC3, TGID3
			io8<base + 0x58> MTU3_V;	///< TCIV3

			io8<base + 0x59> MTU4_ABCD;	///< TGIA4, TGIB4, TGIC4, TGID4
			io8<base + 0x5a> MTU4_V;	///< TCIV4

			io8<base + 0x5b> MTU5_UVW;	///< TGIU5, TGIV5, TGIW5

			io8<base + 0x5c> MTU6_ABCD;	///< TGIA6, TGIB6, TGIC6, TGID6
			io8<base + 0x5d> MTU6_VEF;	///< TCIV6, TGIE6, TGIF6

			io8<base + 0x5e> MTU7_AB;	///< TGIA7, TGIB7
			io8<base + 0x5f> MTU7_VU;	///< TCIV7, TCIU7

			io8<base + 0x60> MTU8_AB;	///< TGIA8, TGIB8
			io8<base + 0x61> MTU8_VU;	///< TCIV8, TCIU8

			io8<base + 0x62> MTU9_ABCD;	///< TGIA9, TGIB9, TGIC9, TGID9
			io8<base + 0x63> MTU9_V;	///< TCIV9

			io8<base + 0x64> MTU10_ABCD;	///< TGIA10, TGIB10, TGIC10, TGID10
			io8<base + 0x65> MTU10_V;		///< TCIV10

			io8<base + 0x66> MTU11_UVW;	///< TGIU11, TGIV11, TGIW11

			io8<base + 0x67> POE;

			io8<base + 0x68> TMR0;
			io8<base + 0x69> TMR1;
			io8<base + 0x6a> TMR2;
			io8<base + 0x6b> TMR3;

			io8<base + 0x70> DMACI0;
			io8<base + 0x71> DMACI1;
			io8<base + 0x72> DMACI2;
			io8<base + 0x73> DMACI3;

			io8<base + 0x74> EXDMACI0;
			io8<base + 0x75> EXDMACI1;

			io8<base + 0x80> SCI0;
			io8<base + 0x81> SCI1;
			io8<base + 0x82> SCI2;
			io8<base + 0x83> SCI3;

			io8<base + 0x85> SCI5;
			io8<base + 0x86> SCI6;

			io8<base + 0x88> ICEEI0;
			io8<base + 0x89> ICRXI0;
			io8<base + 0x8a> ICTXI0;
			io8<base + 0x8b> ICTEI0;
			io8<base + 0x8c> ICEEI1;
			io8<base + 0x8d> ICRXI1;
			io8<base + 0x8e> ICTXI1;
			io8<base + 0x8f> ICTEI1;
		};
		static ipr_t<0x00087300> IPR;


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
			
			bits_t<fir_io, 0, 8> FVCT;
			bit_t<fir_io, 15> FIEN;
		};
		static fir_t FIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SWINTR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x000872e0> swintr_io;
		struct swintr_t : public swintr_io {
			using swintr_io::operator =;
			using swintr_io::operator ();
			using swintr_io::operator |=;
			using swintr_io::operator &=;
			
			bit_t<swintr_io, 0> SWINT;
		};
		static swintr_t SWINTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct dtc_t {

			template <uint32_t base>
			struct dtce_t : public io8<base> {
				typedef io8<base> io8_;				
				using io8_::operator =;
				using io8_::operator ();
				using io8_::operator |=;
				using io8_::operator &=;

				bit_t<io8_, 0>	DTCE;
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
			io8<0x00087400 + 0x00> DMRSR0;
			io8<0x00087400 + 0x04> DMRSR1;
			io8<0x00087400 + 0x08> DMRSR2;
			io8<0x00087400 + 0x0c> DMRSR3;
		};
		static dmaca_t DMACA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqcr_t : public io8<base> {
			typedef io8<base> io8_;
			using io8_::operator =;
			using io8_::operator ();
			using io8_::operator |=;
			using io8_::operator &=;

			bits_t<io8_, 2, 2>	IRQMD;
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
		typedef io8<0x00087580> nmisr_io;
		struct nmisr_t : public nmisr_io {
			using nmisr_io::operator =;
			using nmisr_io::operator ();
			using nmisr_io::operator |=;
			using nmisr_io::operator &=;

			bit_t<nmisr_io, 0>	NMIST;
			bit_t<nmisr_io, 1>	LVDST;
			bit_t<nmisr_io, 2>	OSTST;
		};
		static nmisr_t NMISR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMIER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x00087581> nmier_io;
		struct nmier_t : public nmier_io {
			using nmier_io::operator =;
			using nmier_io::operator ();
			using nmier_io::operator |=;
			using nmier_io::operator &=;

			bit_t<nmier_io, 0>	NMIEN;
			bit_t<nmier_io, 1>	LVDEN;
			bit_t<nmier_io, 2>	OSTEN;
		};
		static nmier_t NMIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMICLR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x00087582> nmiclr_io;
		struct nmiclr_t : public nmiclr_io {
			using nmiclr_io::operator =;
			using nmiclr_io::operator ();
			using nmiclr_io::operator |=;
			using nmiclr_io::operator &=;

			bit_t<nmiclr_io, 0>	NMICLR;
			bit_t<nmiclr_io, 2>	OSTCLR;
		};
		static nmiclr_t NMICLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMICR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x00087583> nmicr_io;
		struct nmicr_t : public nmicr_io {
			using nmicr_io::operator =;
			using nmicr_io::operator ();
			using nmicr_io::operator |=;
			using nmicr_io::operator &=;

			bit_t<nmicr_io, 3>	NMIMD;
		};
		static nmicr_t NMICR;

	};
	typedef icu_t ICU;
}
