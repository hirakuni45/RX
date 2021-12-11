#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX24T 割り込みコントローラ・テンプレート・クラス（ICUb）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_t : public icu_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常割り込みベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {
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

			GTCIA0  = 48,	///< GPT0
			GTCIB0  = 49,
			GTCIC0  = 50,
			GTCID0  = 51,
			GDTE0   = 52,
			GTCIE0  = 53,
			GTCIF0  = 54,
			GTCIV0  = 55,
			GTCIU0  = 56,

			DOPCF   = 57,	///< DOC

			COMFRXINT = 59,	///< RSCAN
			RXFINT    = 60,
			TXINT     = 61,
			CHERRINT  = 62,
			GLERRINT  = 63,

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

			GTCIA1  = 98,	///< GPT1
			GTCIB1  = 99,
			GTCIC1  = 100,
			GTCID1  = 101,

			S12ADI  = 102,  ///< S12AD
			GBADI   = 103,
			GCADI   = 104,
			S12ADI1 = 105,  ///< S12ADI1
			GBADI1  = 106,
			GCADI1  = 107,
			CMPC0   = 108,  ///< CMPC0
			CMPC1   = 109,  ///< CMPC1
			CMPC2   = 110,  ///< CMPC2
			S12ADI2 = 111,  ///< S12AD2
			GBADI2  = 112,
			GCADI2  = 113,

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

			OEI1	= 168,	///< POE
			OEI2	= 169,	///< POE
			OEI3	= 170,	///< POE
			OEI4	= 171,	///< POE
			OEI5	= 172,	///< POE

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

			GDTE1   = 202,	///< GPT1
			GTCIE1  = 203,
			GTCIF1  = 204,
			GTCIV1  = 205,
			GTCIU1  = 206,
			GTCIA2  = 207,	///< GPT2
			GTCIB2  = 208,
			GTCIC2  = 209,
			GTCID2  = 210,
			GDTE2   = 211,
			GTCIE2  = 212,
			GTCIF2  = 213,
			GTCIV2  = 214,
			GTCIU2  = 215,
			GTCIA3  = 216,  ///< GPT3
			GTCIB3  = 217,

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

			GTCIC3  = 238, 	///< GPT3
			GTCID3  = 239,
			GDTE3   = 240,
			GTCIE3  = 241,
			GTCIF3  = 242,
			GTCIV3  = 243,
			GTCIU3  = 244,

			RIIC_EEI0 = 246,  ///< RIIC0
			RIIC_RXI0 = 247,  ///< RIIC0
			RIIC_TXI0 = 248,  ///< RIIC0
			RIIC_TEI0 = 249,  ///< RIIC0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクターの取得 @n
					RX24T はグループベクターをサポートしない為「NONE」を返す
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR ivec) noexcept {
			return VECTOR::NONE;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ・クラス
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {
			rw8_t<base + 16> BUSERR;

			rw8_t<base + 23> FRDYI;

			rw8_t<base + 27> SWINT;
			rw8_t<base + 28> CMI0;
			rw8_t<base + 29> CMI1;
			rw8_t<base + 30> CMI2;
			rw8_t<base + 31> CMI3;
			rw8_t<base + 32> FERRF;
			rw8_t<base + 33> MENDF;
			rw8_t<base + 34> OVFF;

			rw8_t<base + 40> ETGIN;
			rw8_t<base + 41> ETGIP;

			rw8_t<base + 44> SPEI0;
			rw8_t<base + 45> SPRI0;
			rw8_t<base + 46> SPTI0;
			rw8_t<base + 47> SPII0;

			rw8_t<base + 48> GTCIA0;
			rw8_t<base + 49> GTCIB0;
			rw8_t<base + 50> GTCIC0;
			rw8_t<base + 51> GTCID0;
			rw8_t<base + 52> GDTE0;
			rw8_t<base + 53> GTCIE0;
			rw8_t<base + 54> GTCIF0;
			rw8_t<base + 55> GTCIV0;
			rw8_t<base + 56> GTCIU0;

			rw8_t<base + 57> DOPCF;

			rw8_t<base + 59> COMFRXINT;
			rw8_t<base + 60> RXFINT;
			rw8_t<base + 61> TXINT;
			rw8_t<base + 62> CHERRINT;
			rw8_t<base + 63> GLERRINT;

			rw8_t<base + 64> IRQ0;
			rw8_t<base + 65> IRQ1;
			rw8_t<base + 66> IRQ2;
			rw8_t<base + 67> IRQ3;
			rw8_t<base + 68> IRQ4;
			rw8_t<base + 69> IRQ5;
			rw8_t<base + 70> IRQ6;
			rw8_t<base + 71> IRQ7;

			rw8_t<base + 88> LVD1;
			rw8_t<base + 89> LVD2;

			rw8_t<base + 98>  GTCIA1;
			rw8_t<base + 99>  GTCIB1;
			rw8_t<base + 100> GTCIC1;
			rw8_t<base + 101> GTCID1;

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

			rw8_t<base + 168> OEI1;
			rw8_t<base + 169> OEI2;
			rw8_t<base + 170> OEI3;
			rw8_t<base + 171> OEI4;
			rw8_t<base + 172> OEI5;

			rw8_t<base + 173> CMPC3;

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

			rw8_t<base + 202> GDTE1;
			rw8_t<base + 203> GTCIE1;
			rw8_t<base + 204> GTCIF1;
			rw8_t<base + 205> GTCIV1;
			rw8_t<base + 206> GTCIU1;

			rw8_t<base + 207> GTCIA2;
			rw8_t<base + 208> GTCIB2;
			rw8_t<base + 209> GTCIC2;
			rw8_t<base + 210> GTCID2;
			rw8_t<base + 211> GDTE2;
			rw8_t<base + 212> GTCIE2;
			rw8_t<base + 213> GTCIF2;
			rw8_t<base + 214> GTCIV2;
			rw8_t<base + 215> GTCIU2;

			rw8_t<base + 216> GTCIA3;
			rw8_t<base + 217> GTCIB3;

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

			rw8_t<base + 238> GTCIC3;
			rw8_t<base + 239> GTCID3;
			rw8_t<base + 240> GDTE3;
			rw8_t<base + 241> GTCIE3;
			rw8_t<base + 242> GTCIF3;
			rw8_t<base + 243> GTCIV3;
			rw8_t<base + 244> GTCIU3;

			rw8_t<base + 246> RIIC_EEI0;
			rw8_t<base + 247> RIIC_RXI0;
			rw8_t<base + 248> RIIC_TXI0;
			rw8_t<base + 249> RIIC_TEI0;


			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		割り込みベクター型
				@return IR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) noexcept {
				return *reinterpret_cast<volatile uint8_t*>(base + static_cast<uint8_t>(vec));
			}
		};
		typedef ir_t<0x00087000> IR_;
		static IR_ IR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ・クラス
			@param[in]	base	ベースアドレス
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

			typedef rw8_t<base + 0x04> ier04;
			bit_rw_t<ier04, bitpos::B0>	FERRF;
			bit_rw_t<ier04, bitpos::B1>	MENDF;
			bit_rw_t<ier04, bitpos::B3>	OVFF;

			typedef rw8_t<base + 0x05> ier05;
			bit_rw_t<ier05, bitpos::B0>	ETGIN;
			bit_rw_t<ier05, bitpos::B1>	ETGIP;

			bit_rw_t<ier05, bitpos::B4>	SPEI0;
			bit_rw_t<ier05, bitpos::B5>	SPRI0;
			bit_rw_t<ier05, bitpos::B6>	SPTI0;
			bit_rw_t<ier05, bitpos::B7>	SPII0;

			typedef rw8_t<base + 0x06> ier06;
			bit_rw_t<ier06, bitpos::B0>	GTCIA0;
			bit_rw_t<ier06, bitpos::B1>	GTCIB0;
			bit_rw_t<ier06, bitpos::B2>	GTCIC0;
			bit_rw_t<ier06, bitpos::B3>	GTCID0;
			bit_rw_t<ier06, bitpos::B4>	GDTE0;
			bit_rw_t<ier06, bitpos::B5>	GTCIE0;
			bit_rw_t<ier06, bitpos::B6>	GTCIF0;
			bit_rw_t<ier06, bitpos::B7>	GTCIV0;
			typedef rw8_t<base + 0x06> ier07;
			bit_rw_t<ier07, bitpos::B0>	GTCIU0;

			bit_rw_t<ier07, bitpos::B1>	DOPCF;

			bit_rw_t<ier07, bitpos::B3>	COMFRXINT;
			bit_rw_t<ier07, bitpos::B4>	RXFINT;
			bit_rw_t<ier07, bitpos::B5>	TXINT;
			bit_rw_t<ier07, bitpos::B6>	CHERRINT;
			bit_rw_t<ier07, bitpos::B7>	GLERRINT;

			typedef rw8_t<base + 0x08> ier08;
			bit_rw_t<ier08, bitpos::B0>	IRQ0;
			bit_rw_t<ier08, bitpos::B1>	IRQ1;
			bit_rw_t<ier08, bitpos::B2>	IRQ2;
			bit_rw_t<ier08, bitpos::B3>	IRQ3;
			bit_rw_t<ier08, bitpos::B4>	IRQ4;
			bit_rw_t<ier08, bitpos::B5>	IRQ5;
			bit_rw_t<ier08, bitpos::B6>	IRQ6;
			bit_rw_t<ier08, bitpos::B7>	IRQ7;

			typedef rw8_t<base + 0x0B> ier0B;
			bit_rw_t<ier0B, bitpos::B0>	LVD1;
			bit_rw_t<ier0B, bitpos::B1>	LVD2;

			typedef rw8_t<base + 0x0C> ier0C;
			bit_rw_t<ier0C, bitpos::B2>	GTCIA1;
			bit_rw_t<ier0C, bitpos::B3>	GTCIB1;
			bit_rw_t<ier0C, bitpos::B4>	GTCIC1;
			bit_rw_t<ier0C, bitpos::B5>	GTCID1;

			bit_rw_t<ier0C, bitpos::B6>	S12ADI;
			bit_rw_t<ier0C, bitpos::B7>	GBADI;
			typedef rw8_t<base + 0x0D> ier0D;
			bit_rw_t<ier0D, bitpos::B0>	GCADI;
			bit_rw_t<ier0D, bitpos::B1>	S12ADI1;
			bit_rw_t<ier0D, bitpos::B2>	GBADI1;
			bit_rw_t<ier0D, bitpos::B3>	GCADI1;
			bit_rw_t<ier0D, bitpos::B4>	CMPC0;
			bit_rw_t<ier0D, bitpos::B5>	CMPC1;
			bit_rw_t<ier0D, bitpos::B6>	CMPC2;
			bit_rw_t<ier0D, bitpos::B7>	S12ADI2;
			typedef rw8_t<base + 0x0E> ier0E;
			bit_rw_t<ier0E, bitpos::B0>	GBADI2;
			bit_rw_t<ier0E, bitpos::B1>	GCADI2;

			bit_rw_t<ier0E, bitpos::B2>	TGIA0;
			bit_rw_t<ier0E, bitpos::B3>	TGIB0;
			bit_rw_t<ier0E, bitpos::B4>	TGIC0;
			bit_rw_t<ier0E, bitpos::B5>	TGID0;
			bit_rw_t<ier0E, bitpos::B6>	TCIV0;
			bit_rw_t<ier0E, bitpos::B7>	TGIE0;
			typedef rw8_t<base + 0x0F> ier0F;
			bit_rw_t<ier0F, bitpos::B0>	TGIF0;
			bit_rw_t<ier0F, bitpos::B1>	TGIA1;
			bit_rw_t<ier0F, bitpos::B2>	TGIB1;
			bit_rw_t<ier0F, bitpos::B3>	TCIV1;
			bit_rw_t<ier0F, bitpos::B4>	TCIU1;

			bit_rw_t<ier0F, bitpos::B5>	TGIA2;
			bit_rw_t<ier0F, bitpos::B6>	TGIB2;
			bit_rw_t<ier0F, bitpos::B7>	TCIV2;
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
			bit_rw_t<ier15, bitpos::B0>	OEI1;
			bit_rw_t<ier15, bitpos::B1>	OEI2;
			bit_rw_t<ier15, bitpos::B2>	OEI3;
			bit_rw_t<ier15, bitpos::B3>	OEI4;
			bit_rw_t<ier15, bitpos::B4>	OEI5;

			bit_rw_t<ier15, bitpos::B5>	CMPC3;

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

			typedef rw8_t<base + 0x19> ier19;
			bit_rw_t<ier19, bitpos::B2>	GDTE1;
			bit_rw_t<ier19, bitpos::B3>	GTCIE1;
			bit_rw_t<ier19, bitpos::B4>	GTCIF1;
			bit_rw_t<ier19, bitpos::B5>	GTCIV1;
			bit_rw_t<ier19, bitpos::B6>	GTCIU1;

			bit_rw_t<ier19, bitpos::B7>	GTCIA2;
			typedef rw8_t<base + 0x1A> ier1A;
			bit_rw_t<ier1A, bitpos::B0>	GTCIB2;
			bit_rw_t<ier1A, bitpos::B1>	GTCIC2;
			bit_rw_t<ier1A, bitpos::B2>	GTCID2;
			bit_rw_t<ier1A, bitpos::B3>	GDTE2;
			bit_rw_t<ier1A, bitpos::B4>	GTCIE2;
			bit_rw_t<ier1A, bitpos::B5>	GTCIF2;
			bit_rw_t<ier1A, bitpos::B6>	GTCIV2;
			bit_rw_t<ier1A, bitpos::B7>	GTCIU2;

			typedef rw8_t<base + 0x1B> ier1B;
			bit_rw_t<ier1B, bitpos::B0>	GTCIA3;
			bit_rw_t<ier1B, bitpos::B1>	GTCIB3;

			bit_rw_t<ier1B, bitpos::B2>	ERI1;
			bit_rw_t<ier1B, bitpos::B3>	RXI1;
			bit_rw_t<ier1B, bitpos::B4>	TXI1;
			bit_rw_t<ier1B, bitpos::B5>	TEI1;
			bit_rw_t<ier1B, bitpos::B6>	ERI5;
			bit_rw_t<ier1B, bitpos::B7>	RXI5;
			typedef rw8_t<base + 0x1C> ier1C;
			bit_rw_t<ier1C, bitpos::B0>	TXI5;
			bit_rw_t<ier1C, bitpos::B1>	TEI5;
			bit_rw_t<ier1C, bitpos::B2>	ERI6;
			bit_rw_t<ier1C, bitpos::B3>	RXI6;
			bit_rw_t<ier1C, bitpos::B4>	TXI6;
			bit_rw_t<ier1C, bitpos::B5>	TEI6;

			typedef rw8_t<base + 0x1D> ier1D;
			bit_rw_t<ier1D, bitpos::B6>	GTCIC3;
			bit_rw_t<ier1D, bitpos::B7>	GTCID3;
			typedef rw8_t<base + 0x1E> ier1E;
			bit_rw_t<ier1E, bitpos::B0>	GDTE3;
			bit_rw_t<ier1E, bitpos::B1>	GTCIE3;
			bit_rw_t<ier1E, bitpos::B2>	GTCIF3;
			bit_rw_t<ier1E, bitpos::B3>	GTCIV3;
			bit_rw_t<ier1E, bitpos::B4>	GTCIU3;

			bit_rw_t<ier1E, bitpos::B6>	RIIC_EEI0;
			bit_rw_t<ier1E, bitpos::B7>	RIIC_RXI0;
			typedef rw8_t<base + 0x1F> ier1F;
			bit_rw_t<ier1F, bitpos::B0>	RIIC_TXI0;
			bit_rw_t<ier1F, bitpos::B1>	RIIC_TEI0;


			//-------------------------------------------------------------//
			/*!
				@brief  許可、不許可
				@param[in]	vec		割り込みベクター型
				@param[in]	ena		許可／不許可
			*/
			//-------------------------------------------------------------//
			void enable(VECTOR vec, bool ena) noexcept
			{
				auto idx = static_cast<uint8_t>(vec);
				auto tmp = rd8_(base + (idx >> 3));
				if(ena) {
					tmp |=   1 << (idx & 7);
				} else {
					tmp &= ~(1 << (idx & 7));
				}
				wr8_(base + (idx >> 3), tmp);
			}


			//-------------------------------------------------------------//
			/*!
				@brief  許可状態を取得
				@param[in]	vec		割り込みベクター型
				@return 許可状態（許可の場合「true」）
			*/
			//-------------------------------------------------------------//
			bool get(VECTOR vec) const noexcept
			{
				auto idx = static_cast<uint8_t>(vec);
				auto tmp = rd8_(base + (idx >> 3));
				return tmp & (1 << (idx & 7));
			}
		};
		typedef ier_t<0x00087200> IER_;
		static IER_ IER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IPR レジスタ・クラス @n
					全て、下位４ビットが有効
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ipr_t {

			rw8_t<base + 0  > BUSERR;

			rw8_t<base + 2  > FRDYI;

			rw8_t<base + 3  > SWINT;

			rw8_t<base + 4  > CMI0;
			rw8_t<base + 5  > CMI1;
			rw8_t<base + 6  > CMI2;
			rw8_t<base + 7  > CMI3;

			rw8_t<base + 32 > FERRF;
			rw8_t<base + 33 > MENDF;
			rw8_t<base + 34 > OVFF;

			rw8_t<base + 40 > ETGIN;
			rw8_t<base + 41 > ETGIP;

			rw8_t<base + 44 > SPEI0;
			rw8_t<base + 44 > SPRI0;
			rw8_t<base + 44 > SPTI0;
			rw8_t<base + 44 > SPII0;

			rw8_t<base + 48 > GTCIA0;
			rw8_t<base + 49 > GTCIB0;
			rw8_t<base + 50 > GTCIC0;
			rw8_t<base + 51 > GTCID0;
			rw8_t<base + 52 > GDTE0;
			rw8_t<base + 53 > GTCIE0;
			rw8_t<base + 54 > GTCIF0;
			rw8_t<base + 55 > GTCIV0;
			rw8_t<base + 56 > GTCIU0;

			rw8_t<base + 57 > DOPCF;

			rw8_t<base + 59 > COMFRXINT;
			rw8_t<base + 60 > RXFINT;
			rw8_t<base + 61 > TXINT;
			rw8_t<base + 62 > CHERRINT;
			rw8_t<base + 63 > GLERRINT;

			rw8_t<base + 64 > IRQ0;
			rw8_t<base + 65 > IRQ1;
			rw8_t<base + 66 > IRQ2;
			rw8_t<base + 67 > IRQ3;
			rw8_t<base + 68 > IRQ4;
			rw8_t<base + 69 > IRQ5;
			rw8_t<base + 70 > IRQ6;
			rw8_t<base + 71 > IRQ7;

			rw8_t<base + 88 > LVD1;
			rw8_t<base + 89 > LVD2;

			rw8_t<base + 98 > GTCIA1;
			rw8_t<base + 99 > GTCIB1;
			rw8_t<base + 100> GTCIC1;
			rw8_t<base + 101> GTCID1;

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

			rw8_t<base + 114> TGIA0;	///< MTU0
			rw8_t<base + 114> TGIB0;	///< MTU0
			rw8_t<base + 114> TGIC0;	///< MTU0
			rw8_t<base + 114> TGID0;	///< MTU0
			rw8_t<base + 118> TCIV0;	///< MTU0
			rw8_t<base + 118> TGIE0;	///< MTU0
			rw8_t<base + 118> TGIF0;	///< MTU0

			rw8_t<base + 121> TGIA1;	///< MTU1
			rw8_t<base + 121> TGIB1;	///< MTU1
			rw8_t<base + 123> TCIV1;	///< MTU1
			rw8_t<base + 123> TCIU1;	///< MTU1

			rw8_t<base + 125> TGIA2;	///< MTU2
			rw8_t<base + 125> TGIB2;	///< MTU2
			rw8_t<base + 127> TCIV2;	///< MTU2
			rw8_t<base + 127> TCIU2;	///< MTU2

			rw8_t<base + 129> TGIA3;	///< MTU3
			rw8_t<base + 129> TGIB3;	///< MTU3
			rw8_t<base + 129> TGIC3;	///< MTU3
			rw8_t<base + 129> TGID3;	///< MTU3
			rw8_t<base + 133> TCIV3;	///< MTU3

			rw8_t<base + 134> TGIA4;	///< MTU4
			rw8_t<base + 134> TGIB4;	///< MTU4
			rw8_t<base + 134> TGIC4;	///< MTU4
			rw8_t<base + 134> TGID4;	///< MTU4
			rw8_t<base + 138> TCIV4;	///< MTU4

			rw8_t<base + 139> TGIU5;	///< MTU5
			rw8_t<base + 139> TGIV5;	///< MTU5
			rw8_t<base + 139> TGIW5;	///< MTU5

			rw8_t<base + 142> TGIA6;	///< MTU6
			rw8_t<base + 142> TGIB6;	///< MTU6
			rw8_t<base + 142> TGIC6;	///< MTU6
			rw8_t<base + 142> TGID6;	///< MTU6
			rw8_t<base + 146> TCIV6;	///< MTU6

			rw8_t<base + 149> TGIA7;	///< MTU7
			rw8_t<base + 149> TGIB7;	///< MTU7
			rw8_t<base + 151> TGIC7;	///< MTU7
			rw8_t<base + 151> TGID7;	///< MTU7
			rw8_t<base + 153> TCIV7;	///< MTU7

			rw8_t<base + 159> TGIA9;	///< MTU9
			rw8_t<base + 159> TGIB9;	///< MTU9
			rw8_t<base + 159> TGIC9;	///< MTU9
			rw8_t<base + 159> TGID9;	///< MTU9
			rw8_t<base + 163> TCIV9;	///< MTU9
			rw8_t<base + 163> TGIE9;	///< MTU9
			rw8_t<base + 163> TGIF9;	///< MTU9

			rw8_t<base + 168> OEI1;		///< POE
			rw8_t<base + 169> OEI2;		///< POE
			rw8_t<base + 170> OEI3;		///< POE
			rw8_t<base + 171> OEI4;		///< POE
			rw8_t<base + 172> OEI5;		///< POE

			rw8_t<base + 173> CMPC3;	///< CMPC3

			rw8_t<base + 174> CMIA0;	///< TMR0
			rw8_t<base + 174> CMIB0;	///< TMR0
			rw8_t<base + 174> OVI0;		///< TMR0
			rw8_t<base + 177> CMIA1;	///< TMR1
			rw8_t<base + 177> CMIB1;	///< TMR1
			rw8_t<base + 177> OVI1;		///< TMR1
			rw8_t<base + 180> CMIA2;	///< TMR2
			rw8_t<base + 180> CMIB2;	///< TMR2
			rw8_t<base + 180> OVI2;		///< TMR2
			rw8_t<base + 183> CMIA3;	///< TMR3
			rw8_t<base + 183> CMIB3;	///< TMR3
			rw8_t<base + 183> OVI3;		///< TMR3
			rw8_t<base + 186> CMIA4;	///< TMR4
			rw8_t<base + 186> CMIB4;	///< TMR4
			rw8_t<base + 186> OVI4;		///< TMR4
			rw8_t<base + 189> CMIA5;	///< TMR5
			rw8_t<base + 189> CMIB5;	///< TMR5
			rw8_t<base + 189> OVI5;		///< TMR5
			rw8_t<base + 192> CMIA6;	///< TMR6
			rw8_t<base + 192> CMIB6;	///< TMR6
			rw8_t<base + 192> OVI6;		///< TMR6
			rw8_t<base + 195> CMIA7;	///< TMR7
			rw8_t<base + 195> CMIB7;	///< TMR7
			rw8_t<base + 195> OVI7;		///< TMR7

			rw8_t<base + 202> GDTE1;	///< GPT1
			rw8_t<base + 203> GTCIE1;	///< GPT1
			rw8_t<base + 204> GTCIF1;	///< GPT1
			rw8_t<base + 205> GTCIV1;	///< GPT1
			rw8_t<base + 206> GTCIU1;	///< GPT1

			rw8_t<base + 207> GTCIA2;	///< GPT2
			rw8_t<base + 208> GTCIB2;	///< GPT2
			rw8_t<base + 209> GTCIC2;	///< GPT2
			rw8_t<base + 210> GTCID2;	///< GPT2
			rw8_t<base + 211> GDTE2;	///< GPT2
			rw8_t<base + 212> GTCIE2;	///< GPT2
			rw8_t<base + 213> GTCIF2;	///< GPT2
			rw8_t<base + 214> GTCIV2;	///< GPT2
			rw8_t<base + 215> GTCIU2;	///< GPT2

			rw8_t<base + 216> GTCIA3;	///< GPT3
			rw8_t<base + 217> GTCIB3;	///< GPT3

			rw8_t<base + 218> ERI1;		///< SCI1
			rw8_t<base + 218> RXI1;		///< SCI1
			rw8_t<base + 218> TXI1;		///< SCI1
			rw8_t<base + 218> TEI1;		///< SCI1

			rw8_t<base + 222> ERI5;		///< SCI5
			rw8_t<base + 222> RXI5;		///< SCI5
			rw8_t<base + 222> TXI5;		///< SCI5
			rw8_t<base + 222> TEI5;		///< SCI5

			rw8_t<base + 226> ERI6;		///< SCI6
			rw8_t<base + 226> RXI6;		///< SCI6
			rw8_t<base + 226> TXI6;		///< SCI6
			rw8_t<base + 226> TEI6;		///< SCI6

			rw8_t<base + 238> GTCIC3;	///< GPT3
			rw8_t<base + 239> GTCID3;	///< GPT3
			rw8_t<base + 240> GDTE3;	///< GPT3
			rw8_t<base + 241> GTCIE3;	///< GPT3
			rw8_t<base + 242> GTCIF3;	///< GPT3
			rw8_t<base + 243> GTCIV3;	///< GPT3
			rw8_t<base + 244> GTCIU3;	///< GPT3

			rw8_t<base + 246> RIIC_EEI0;  	///< RIIC0
			rw8_t<base + 247> RIIC_RXI0;
			rw8_t<base + 248> RIIC_TXI0;
			rw8_t<base + 249> RIIC_TEI0;


			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		標準割り込みベクター型
				@return IPR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) {
				uint32_t idx = 0;
				switch(vec) {
				case VECTOR::BUSERR: idx = 0; break;
				case VECTOR::FRDYI:  idx = 2; break;
				case VECTOR::SWINT:  idx = 3; break;
				case VECTOR::CMI0:   idx = 4; break;
				case VECTOR::CMI1:   idx = 5; break;
				case VECTOR::CMI2:   idx = 6; break;
				case VECTOR::CMI3:   idx = 7; break;
				case VECTOR::SPEI0:
				case VECTOR::SPRI0:
				case VECTOR::SPTI0:
				case VECTOR::SPII0:
					idx = 44;
					break;
				case VECTOR::TGIA0:
				case VECTOR::TGIB0:
				case VECTOR::TGIC0:
				case VECTOR::TGID0:
					idx = 114;
					break;
				case VECTOR::TCIV0:
				case VECTOR::TGIE0:
				case VECTOR::TGIF0:
					idx = 118;
					break;
				case VECTOR::TGIA1:
				case VECTOR::TGIB1:
					idx = 121;
					break;
				case VECTOR::TCIV1:
				case VECTOR::TCIU1:
					idx = 123;
					break;
				case VECTOR::TGIA2:
				case VECTOR::TGIB2:
					idx = 125;
					break;
				case VECTOR::TCIV2:
				case VECTOR::TCIU2:
					idx = 127;
					break;
				case VECTOR::TGIA3:
				case VECTOR::TGIB3:
				case VECTOR::TGIC3:
				case VECTOR::TGID3:
					idx = 129;
					break;
				case VECTOR::TCIV3:
					idx = 133;
					break;
				case VECTOR::TGIA4:
				case VECTOR::TGIB4:
				case VECTOR::TGIC4:
				case VECTOR::TGID4:
					idx = 134;
					break;
				case VECTOR::TCIV4:
					idx = 138;
					break;
				case VECTOR::TGIU5:
				case VECTOR::TGIV5:
				case VECTOR::TGIW5:
					idx = 139;
					break;
				case VECTOR::TGIA6:
				case VECTOR::TGIB6:
				case VECTOR::TGIC6:
				case VECTOR::TGID6:
					idx = 142;
					break;
				case VECTOR::TCIV6:
					idx = 146;
					break;
				case VECTOR::TGIA7:
				case VECTOR::TGIB7:
					idx = 149;
					break;
				case VECTOR::TGIC7:
				case VECTOR::TGID7:
					idx = 151;
					break;
				case VECTOR::TCIV7:
					idx = 153;
					break;
				case VECTOR::TGIA9:
				case VECTOR::TGIB9:
				case VECTOR::TGIC9:
				case VECTOR::TGID9:
					idx = 159;
					break;
				case VECTOR::TCIV9:
				case VECTOR::TGIE9:
				case VECTOR::TGIF9:
					idx = 163;
					break;
				case VECTOR::CMIA0:
				case VECTOR::CMIB0:
				case VECTOR::OVI0:
					idx = 174;
					break;
				case VECTOR::CMIA1:
				case VECTOR::CMIB1:
				case VECTOR::OVI1:
					idx = 177;
					break;
				case VECTOR::CMIA2:
				case VECTOR::CMIB2:
				case VECTOR::OVI2:
					idx = 180;
					break;
				case VECTOR::CMIA3:
				case VECTOR::CMIB3:
				case VECTOR::OVI3:
					idx = 183;
					break;
				case VECTOR::CMIA4:
				case VECTOR::CMIB4:
				case VECTOR::OVI4:
					idx = 186;
					break;
				case VECTOR::CMIA5:
				case VECTOR::CMIB5:
				case VECTOR::OVI5:
					idx = 189;
					break;
				case VECTOR::CMIA6:
				case VECTOR::CMIB6:
				case VECTOR::OVI6:
					idx = 192;
					break;
				case VECTOR::CMIA7:
				case VECTOR::CMIB7:
				case VECTOR::OVI7:
					idx = 195;
					break;
				case VECTOR::ERI1:
				case VECTOR::RXI1:
				case VECTOR::TXI1:
				case VECTOR::TEI1:
					idx = 218;
					break;
				case VECTOR::ERI5:
				case VECTOR::RXI5:
				case VECTOR::TXI5:
				case VECTOR::TEI5:
					idx = 222;
					break;
				case VECTOR::ERI6:
				case VECTOR::RXI6:
				case VECTOR::TXI6:
				case VECTOR::TEI6:
					idx = 226;
					break;

				default: idx = static_cast<uint32_t>(vec); break;
				}
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		typedef ipr_t<0x00087300> IPR_;
		static IPR_ IPR;
	};
	typedef icu_t<void> ICU;

	template<class _> typename icu_t<_>::IR_ icu_t<_>::IR;
	template<class _> typename icu_t<_>::IER_ icu_t<_>::IER;
	template<class _> typename icu_t<_>::IPR_ icu_t<_>::IPR;
}
