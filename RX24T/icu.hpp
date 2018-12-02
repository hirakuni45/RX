#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ICU 定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR {
			NONE    = 0,	///< none 
			BUSERR  = 16,   ///< BSC

			FRDYI   = 23,   ///< FCU

			SWINT   = 27,   ///< ICU
			CMI0    = 28,   ///< CMT0
			CMI1    = 29,   ///< CMT1
			CMI2    = 30,   ///< CMT2
			CMI3    = 31,   ///< CMT3
			FERRF   = 32,	///< CAC
			MENDF   = 33,	///< CAC
			OVFF    = 34,	///< CAC

			ETGIN   = 40,	///< GPT
			ETGIP   = 41,	///< GPT

			SPEI0   = 44,	///< RSPI0
			SPRI0   = 45,	///< RSPI0
			SPTI0   = 46,	///< RSPI0
			SPII0   = 47,	///< RSPI0

			DOPCF   = 57,	///< DOC

			IRQ0    = 64,	///< ICU
			IRQ1    = 65,
			IRQ2    = 66,
			IRQ3    = 67,
			IRQ4    = 68,
			IRQ5    = 69,
			IRQ6    = 70,
			IRQ7    = 71,

			LVD1    = 88,   ///< LVD
			LVD2    = 89,   ///< LVD

			S12ADI  = 102,  ///< S12ADI
			GBADI   = 103,  ///< S12AD
			GCADI   = 104,  ///< S12AD
			S12ADI1 = 105,  ///< S12ADI1
			GBADI1  = 106,  ///< S12AD1
			GCADI1  = 107,  ///< S12AD1
			CMPC0   = 108,  ///< CMPC0
			CMPC1   = 109,  ///< CMPC1
			CMPC2   = 110,  ///< CMPC2
			S12ADI2 = 111,  ///< S12AD2
			GBADI2  = 112,  ///< S12AD2
			GCADI2  = 113,  ///< S12AD2

			TGIA0   = 114,  ///< MTU0
			TGIB0   = 115,  ///< MTU0
			TGIC0   = 116,  ///< MTU0
			TGID0   = 117,  ///< MTU0
			TCIV0   = 118,  ///< MTU0
			TGIE0   = 119,  ///< MTU0
			TGIF0   = 120,  ///< MTU0

			TGIA1   = 121,  ///< MTU1
			TGIB1   = 122,  ///< MTU1
			TCIV1   = 123,  ///< MTU1
			TCIU1   = 124,  ///< MTU1

			TGIA2   = 125,  ///< MTU2
			TGIB2   = 126,  ///< MTU2
			TCIV2   = 127,  ///< MTU2
			TCIU2   = 128,  ///< MTU2

			TGIA3   = 129,  ///< MTU3
			TGIB3   = 130,  ///< MTU3
			TGIC3   = 131,  ///< MTU3
			TGID3   = 132,  ///< MTU3
			TCIV3   = 133,  ///< MTU3

			TGIA4   = 134,  ///< MTU4
			TGIB4   = 135,  ///< MTU4
			TGIC4   = 136,  ///< MTU4
			TGID4   = 137,  ///< MTU4
			TCIV4   = 138,  ///< MTU4

			TGIU5   = 139,  ///< MTU5
			TGIV5   = 140,  ///< MTU5
			TGIW5   = 141,  ///< MTU5

			TGIA6   = 142,  ///< MTU6
			TGIB6   = 143,  ///< MTU6
			TGIC6   = 144,  ///< MTU6
			TGID6   = 145,  ///< MTU6
			TCIV6   = 146,  ///< MTU6

			TGIA7   = 149,  ///< MTU7
			TGIB7   = 150,  ///< MTU7
			TGIC7   = 151,  ///< MTU7
			TGID7   = 152,  ///< MTU7
			TCIV7   = 153,  ///< MTU7

			TGIA9   = 159,  ///< MTU9
			TGIB9   = 160,  ///< MTU9
			TGIC9   = 161,  ///< MTU9
			TGID9   = 162,  ///< MTU9
			TCIV9   = 163,  ///< MTU9
			TGIE9   = 164,  ///< MTU9
			TGIF9   = 165,  ///< MTU9

			CMPC3   = 173,  ///< CMPC3

			CMIA0   = 174,	///< TMR0: CMIA0
			CMIB0   = 175,	///< TMR0: CMIB0
			OVI0    = 176,	///< TMR0: OVI0
			CMIA1   = 177,	///< TMR1: CMIA1
			CMIB1   = 178,	///< TMR1: CMIB1
			OVI1    = 179,	///< TMR1: OVI1
			CMIA2   = 180,	///< TMR2: CMIA2
			CMIB2   = 181,	///< TMR2: CMIB2
			OVI2    = 182,	///< TMR2: OVI2
			CMIA3   = 183,	///< TMR3: CMIA3
			CMIB3   = 184,	///< TMR3: CMIB3
			OVI3    = 185,	///< TMR3: OVI3
			CMIA4   = 186,	///< TMR4: CMIA4
			CMIB4   = 187,	///< TMR4: CMIB4
			OVI4    = 188,	///< TMR4: OVI4
			CMIA5   = 189,	///< TMR5: CMIA5
			CMIB5   = 190,	///< TMR5: CMIB5
			OVI5    = 191,	///< TMR5: OVI5
			CMIA6   = 192,	///< TMR6: CMIA6
			CMIB6   = 193,	///< TMR6: CMIB6
			OVI6    = 194,	///< TMR6: OVI6
			CMIA7   = 195,	///< TMR7: CMIA7
			CMIB7   = 196,	///< TMR7: CMIB7
			OVI7    = 197,	///< TMR7: OVI7

			ERI1    = 218,  ///< SCI1
			RXI1    = 219,  ///< SCI1
			TXI1    = 220,  ///< SCI1
			TEI1    = 221,  ///< SCI1
			ERI5    = 222,  ///< SCI5
			RXI5    = 223,  ///< SCI5
			TXI5    = 224,  ///< SCI5
			TEI5    = 225,  ///< SCI5
			ERI6    = 226,  ///< SCI6
			RXI6    = 227,  ///< SCI6
			TXI6    = 228,  ///< SCI6
			TEI6    = 229,  ///< SCI6

			RIIC_EEI0 = 246,  ///< RIIC0
			RIIC_RXI0 = 247,  ///< RIIC0
			RIIC_TXI0 = 248,  ///< RIIC0
			RIIC_TEI0 = 249,  ///< RIIC0
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

			rw8_t<base + 102> S12ADI;
			rw8_t<base + 103> GBADI;
			rw8_t<base + 104> GCADI;
			rw8_t<base + 105> S12ADI1;
			rw8_t<base + 106> GBADI1;
			rw8_t<base + 107> GCADI1;
			rw8_t<base + 108> CMPC0;
			rw8_t<base + 109> CMPC1;
			rw8_t<base + 110> CMPC2;
			rw8_t<base + 111> S12ADI2;
			rw8_t<base + 112> GBADI2;
			rw8_t<base + 113> GCADI2;

			rw8_t<base + 114> TGIA0;
			rw8_t<base + 115> TGIB0;
			rw8_t<base + 116> TGIC0;
			rw8_t<base + 117> TGID0;
			rw8_t<base + 118> TCIV0;
			rw8_t<base + 119> TGIE0;
			rw8_t<base + 120> TGIF0;

			rw8_t<base + 121> TGIA1;
			rw8_t<base + 122> TGIB1;
			rw8_t<base + 123> TCIV1;
			rw8_t<base + 124> TCIU1;

			rw8_t<base + 125> TGIA2;
			rw8_t<base + 126> TGIB2;
			rw8_t<base + 127> TCIV2;
			rw8_t<base + 128> TCIU2;

			rw8_t<base + 129> TGIA3;
			rw8_t<base + 130> TGIB3;
			rw8_t<base + 131> TGIC3;
			rw8_t<base + 132> TGID3;
			rw8_t<base + 133> TCIV3;

			rw8_t<base + 134> TGIA4;
			rw8_t<base + 135> TGIB4;
			rw8_t<base + 136> TGIC4;
			rw8_t<base + 137> TGID4;
			rw8_t<base + 138> TCIV4;

			rw8_t<base + 139> TGIU5;
			rw8_t<base + 140> TGIV5;
			rw8_t<base + 141> TGIW5;

			rw8_t<base + 142> TGIA6;
			rw8_t<base + 143> TGIB6;
			rw8_t<base + 144> TGIC6;
			rw8_t<base + 145> TGID6;
			rw8_t<base + 146> TCIV6;

			rw8_t<base + 149> TGIA7;
			rw8_t<base + 150> TGIB7;
			rw8_t<base + 151> TGIC7;
			rw8_t<base + 152> TGID7;
			rw8_t<base + 153> TCIV7;

			rw8_t<base + 159> TGIA9;
			rw8_t<base + 160> TGIB9;
			rw8_t<base + 161> TGIC9;
			rw8_t<base + 162> TGID9;
			rw8_t<base + 163> TCIV9;
			rw8_t<base + 164> TGIE9;
			rw8_t<base + 165> TGIF9;

			rw8_t<base + 174> CMIA0;
			rw8_t<base + 175> CMIB0;
			rw8_t<base + 176> OVI0;
			rw8_t<base + 177> CMIA1;
			rw8_t<base + 178> CMIB1;
			rw8_t<base + 179> OVI1;
			rw8_t<base + 180> CMIA2;
			rw8_t<base + 181> CMIB2;
			rw8_t<base + 182> OVI2;
			rw8_t<base + 183> CMIA3;
			rw8_t<base + 184> CMIB3;
			rw8_t<base + 185> OVI3;
			rw8_t<base + 186> CMIA4;
			rw8_t<base + 187> CMIB4;
			rw8_t<base + 188> OVI4;
			rw8_t<base + 189> CMIA5;
			rw8_t<base + 190> CMIB5;
			rw8_t<base + 191> OVI5;
			rw8_t<base + 192> CMIA6;
			rw8_t<base + 193> CMIB6;
			rw8_t<base + 194> OVI6;
			rw8_t<base + 195> CMIA7;
			rw8_t<base + 196> CMIB7;
			rw8_t<base + 197> OVI7;

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

			rw8_t<base + 246> RIIC_EEI0;
			rw8_t<base + 247> RIIC_RXI0;
			rw8_t<base + 248> RIIC_TXI0;
			rw8_t<base + 249> RIIC_TEI0;
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

			typedef rw8_t<base + 0x0C> ier0c;
			bit_rw_t<ier0c, bitpos::B6>	S12ADI;
			bit_rw_t<ier0c, bitpos::B7>	GBADI;
			typedef rw8_t<base + 0x0D> ier0d;
			bit_rw_t<ier0d, bitpos::B0>	GCADI;
			bit_rw_t<ier0d, bitpos::B1>	S12ADI1;
			bit_rw_t<ier0d, bitpos::B2>	GBADI1;
			bit_rw_t<ier0d, bitpos::B3>	GCADI1;
			bit_rw_t<ier0d, bitpos::B4>	CMPC0;
			bit_rw_t<ier0d, bitpos::B5>	CMPC1;
			bit_rw_t<ier0d, bitpos::B6>	CMPC2;
			bit_rw_t<ier0d, bitpos::B7>	S12ADI2;
			typedef rw8_t<base + 0x0E> ier0e;
			bit_rw_t<ier0e, bitpos::B0>	GBADI2;
			bit_rw_t<ier0e, bitpos::B1>	GCADI2;

			bit_rw_t<ier0e, bitpos::B2>	TGIA0;
			bit_rw_t<ier0e, bitpos::B3>	TGIB0;
			bit_rw_t<ier0e, bitpos::B4>	TGIC0;
			bit_rw_t<ier0e, bitpos::B5>	TGID0;
			bit_rw_t<ier0e, bitpos::B6>	TCIV0;
			bit_rw_t<ier0e, bitpos::B7>	TGIE0;
			typedef rw8_t<base + 0x0F> ier0f;
			bit_rw_t<ier0f, bitpos::B0>	TGIF0;
			bit_rw_t<ier0f, bitpos::B1>	TGIA1;
			bit_rw_t<ier0f, bitpos::B2>	TGIB1;
			bit_rw_t<ier0f, bitpos::B3>	TCIV1;
			bit_rw_t<ier0f, bitpos::B4>	TCIU1;

			bit_rw_t<ier0f, bitpos::B5>	TGIA2;
			bit_rw_t<ier0f, bitpos::B6>	TGIB2;
			bit_rw_t<ier0f, bitpos::B7>	TCIV2;
			typedef rw8_t<base + 0x10> ier10;
			bit_rw_t<ier10, bitpos::B0>	TCIU2;
			bit_rw_t<ier10, bitpos::B1>	TGIA3;
			bit_rw_t<ier10, bitpos::B2>	TGIB3;
			bit_rw_t<ier10, bitpos::B3>	TGIC3;
			bit_rw_t<ier10, bitpos::B4>	TGID3;
			bit_rw_t<ier10, bitpos::B5>	TCIV3;
			bit_rw_t<ier10, bitpos::B6>	TGIA4;
			bit_rw_t<ier10, bitpos::B7>	TGIB4;
			typedef rw8_t<base + 0x11> ier11;
			bit_rw_t<ier11, bitpos::B0>	TGIC4;
			bit_rw_t<ier11, bitpos::B1>	TGID4;
			bit_rw_t<ier11, bitpos::B2>	TCIV4;
			bit_rw_t<ier11, bitpos::B3>	TGIU5;
			bit_rw_t<ier11, bitpos::B4>	TGIV5;
			bit_rw_t<ier11, bitpos::B5>	TGIW5;
			typedef rw8_t<base + 0x12> ier12;
			bit_rw_t<ier11, bitpos::B6>	TGIA6;
			bit_rw_t<ier11, bitpos::B7>	TGIB6;
			bit_rw_t<ier12, bitpos::B0>	TGIC6;
			bit_rw_t<ier12, bitpos::B1>	TGID6;
			bit_rw_t<ier12, bitpos::B2>	TCIV6;
			bit_rw_t<ier12, bitpos::B5>	TGIA7;
			bit_rw_t<ier12, bitpos::B6>	TGIB7;
			bit_rw_t<ier12, bitpos::B7>	TGIC7;
			typedef rw8_t<base + 0x13> ier13;
			bit_rw_t<ier13, bitpos::B0>	TGID7;
			bit_rw_t<ier13, bitpos::B1>	TCIV7;
			bit_rw_t<ier13, bitpos::B7>	TGIA9;
			typedef rw8_t<base + 0x14> ier14;
			bit_rw_t<ier14, bitpos::B0>	TGIB9;
			bit_rw_t<ier14, bitpos::B1>	TGIC9;
			bit_rw_t<ier14, bitpos::B2>	TGID9;
			bit_rw_t<ier14, bitpos::B3>	TCIV9;
			bit_rw_t<ier14, bitpos::B4>	TGIE9;
			bit_rw_t<ier14, bitpos::B5>	TGIF9;

			typedef rw8_t<base + 0x15> ier15;
			bit_rw_t<ier15, bitpos::B6>	CMIA0;
			bit_rw_t<ier15, bitpos::B7>	CMIB0;
			typedef rw8_t<base + 0x16> ier16;
			bit_rw_t<ier16, bitpos::B0>	OVI0;
			bit_rw_t<ier16, bitpos::B1>	CMIA1;
			bit_rw_t<ier16, bitpos::B2>	CMIB1;
			bit_rw_t<ier16, bitpos::B3>	OVI1;
			bit_rw_t<ier16, bitpos::B4>	CMIA2;
			bit_rw_t<ier16, bitpos::B5>	CMIB2;
			bit_rw_t<ier16, bitpos::B6>	OVI2;
			bit_rw_t<ier16, bitpos::B7>	CMIA3;
			typedef rw8_t<base + 0x17> ier17;
			bit_rw_t<ier17, bitpos::B0>	CMIB3;
			bit_rw_t<ier17, bitpos::B1>	OVI3;
			bit_rw_t<ier17, bitpos::B2>	CMIA4;
			bit_rw_t<ier17, bitpos::B3>	CMIB4;
			bit_rw_t<ier17, bitpos::B4>	OVI4;
			bit_rw_t<ier17, bitpos::B5>	CMIA5;
			bit_rw_t<ier17, bitpos::B6>	CMIB5;
			bit_rw_t<ier17, bitpos::B7>	OVI5;
			typedef rw8_t<base + 0x18> ier18;
			bit_rw_t<ier18, bitpos::B0>	CMIA6;
			bit_rw_t<ier18, bitpos::B1>	CMIB6;
			bit_rw_t<ier18, bitpos::B2>	OVI6;
			bit_rw_t<ier18, bitpos::B3>	CMIA7;
			bit_rw_t<ier18, bitpos::B4>	CMIB7;
			bit_rw_t<ier18, bitpos::B5>	OVI7;

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
			bit_rw_t<ier1e, bitpos::B6>	RIIC_EEI0;
			bit_rw_t<ier1e, bitpos::B7>	RIIC_RXI0;
			typedef rw8_t<base + 0x1F> ier1f;
			bit_rw_t<ier1f, bitpos::B0>	RIIC_TXI0;
			bit_rw_t<ier1f, bitpos::B1>	RIIC_TEI0;
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

			rw8_t<base + 4  > CMI0;
			rw8_t<base + 5  > CMI1;
			rw8_t<base + 6  > CMI2;
			rw8_t<base + 7  > CMI3;

			rw8_t<base + 44 > RSPI0;

			rw8_t<base + 102> S12ADI;   ///< S12AD
			rw8_t<base + 103> GBADI;
			rw8_t<base + 104> GCADI;
			rw8_t<base + 105> S12ADI1;  ///< S12AD1
			rw8_t<base + 106> GBADI1;
			rw8_t<base + 107> GCADI1;
			rw8_t<base + 108> CMPC0;
			rw8_t<base + 109> CMPC1;
			rw8_t<base + 110> CMPC2;
			rw8_t<base + 111> S12ADI2;  ///< S12AD2
			rw8_t<base + 112> GBADI2;
			rw8_t<base + 113> GCADI2;

			rw8_t<base + 114> MTU0_ABCD;	///< MTU0
			rw8_t<base + 118> MTU0_VEF;		///< MTU0

			rw8_t<base + 121> MTU1_AB;		///< MTU1
			rw8_t<base + 123> MTU1_VU;		///< MTU1

			rw8_t<base + 125> MTU2_AB;		///< MTU2
			rw8_t<base + 127> MTU2_VU;		///< MTU2

			rw8_t<base + 129> MTU3_ABCD;	///< MTU3
			rw8_t<base + 133> MTU3_V;		///< MTU3

			rw8_t<base + 134> MTU4_ABCD;	///< MTU4
			rw8_t<base + 138> MTU4_V;		///< MTU4

			rw8_t<base + 139> MTU5_UVW;		///< MTU5

			rw8_t<base + 142> MTU6_ABCD;	///< MTU6
			rw8_t<base + 146> MTU6_V;		///< MTU6

			rw8_t<base + 149> MTU7_AB;		///< MTU7
			rw8_t<base + 151> MTU7_CD;		///< MTU7
			rw8_t<base + 153> MTU7_V;		///< MTU7

			rw8_t<base + 159> MTU9_ABCD;	///< MTU9
			rw8_t<base + 163> MTU9_VEF;		///< MTU9

			rw8_t<base + 174> TMR0;		///< TMR0
			rw8_t<base + 177> TMR1;		///< TMR1
			rw8_t<base + 180> TMR2;		///< TMR2
			rw8_t<base + 183> TMR3;		///< TMR3
			rw8_t<base + 186> TMR4;		///< TMR4
			rw8_t<base + 189> TMR5;		///< TMR5
			rw8_t<base + 192> TMR6;		///< TMR6
			rw8_t<base + 195> TMR7;		///< TMR7

			rw8_t<base + 218> SCI1;		///< SCI1
			rw8_t<base + 222> SCI5;		///< SCI5
			rw8_t<base + 226> SCI6;		///< SCI6

			rw8_t<base + 246> RIIC_EEI0;  	///< RIIC0
			rw8_t<base + 247> RIIC_RXI0;
			rw8_t<base + 248> RIIC_TXI0;
			rw8_t<base + 249> RIIC_TEI0;
		};
		static ipr_t<0x00087300> IPR;

	};
	typedef icu_t ICU;
}
