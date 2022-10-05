#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ・ICUC 定義 @n
			RX66T、RX72T 共通
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/icu_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX66T/RX72T 割り込みコントローラ・テンプレート・クラス（ICUC）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icuc_t : public icu_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常割り込みベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {
			NONE		= 0,	///< none 

			BUSERR		= 16,	///< BSC

			RAMERR		= 18,	///< RAM

			FIFERR		= 21,	///< FCU

			FRDYI		= 23,	///< FCU

			SWINT2		= 26,	///< ICU
			SWINT		= 27,	///< ICU

			CMI0		= 28,	///< CMT0
			CMI1		= 29,	///< CMT1
			CMI2		= 30,	///< CMT2
			CMI3		= 31,	///< CMT3

			D0FIFO0		= 34,	///< USB0 0
 			D1FIFO0		= 35,	///< USB0 1

			SPRI0		= 38,	///< RSPI0 R
			SPTI0		= 39,	///< RSPI0 T

			ICRXI0		= 52,	///< RIIC0 RX
			ICTXI0		= 53,	///< RIIC0 TX

			RXI1		= 60,	///< SCI1 RX
			TXI1		= 61,	///< SCI1 TX

			IRQ0		= 64,	///< ICU
			IRQ1		= 65,
			IRQ2		= 66,
			IRQ3		= 67,
			IRQ4		= 68,
			IRQ5		= 69,
			IRQ6		= 70,
			IRQ7		= 71,
			IRQ8		= 72,
			IRQ9		= 73,
			IRQ10		= 74,
			IRQ11		= 75,
			IRQ12		= 76,
			IRQ13		= 77,
			IRQ14     	= 78,
			IRQ15    	= 79,

			RXI5      	= 84,	///< SCI5 RX
			TXI5      	= 85,	///< SCI5 TX
			RXI6	  	= 86,	///< SCI6 RX
			TXI6	  	= 87,	///< SCI6 TX

			LVD1      	= 88,	///< LVD1
			LVD2      	= 89,	///< LVD2

			USBR0	  	= 90,	///< USB0

			IWUNI     	= 95,	///< IWDT
			WUNI	  	= 96,	///< WDT

			RXI8	  	= 100,	///< SCI8 RX
			TXI8	  	= 101,	///< SCI8 TX
			RXI9	  	= 102,	///< SCI9 RX
			TXI9	  	= 103,	///< SCI9 TX

			GROUPBE0	= 106,	///< ICU

			GROUPBL0	= 110,	///< ICU
			GROUPBL1	= 111,	///< ICU
			GROUPAL0	= 112,	///< ICU

			RXI11		= 114,	///< SCI11 RX
			TXI11		= 115,	///< SCI11 TX
			RXI12		= 116,	///< SCI12 RX
			TXI12		= 117,	///< SCI12 TX

			DMAC0I		= 120,	///< DMAC 0
			DMAC1I		= 121,	///< DMAC 1
			DMAC2I		= 122,	///< DMAC 2
			DMAC3I		= 123,	///< DMAC 3
			DMAC74I		= 124,	///< DMAC 4,5,6,7

			OSTDI		= 125,	///< OST

			S12ADI		= 128,	///< S12AD
			S12GBADI	= 129,	///< S12AD
			S12GCADI	= 130,	///< S12AD

			S12ADI1		= 132,	///< S12AD1
			S12GBADI1	= 133,	///< S12AD1
			S12GCADI1	= 134,	///< S12AD1

			S12ADI2		= 136,	///< S12AD2
			S12GBADI2	= 137,	///< S12AD2
			S12GCADI2	= 138,	///< S12AD2

			CMIA0		= 146,	///< TMR0: CMIA0
			CMIB0		= 147,	///< TMR0: CMIB0
			OVI0		= 148,	///< TMR0: OVI0
			CMIA1		= 149,	///< TMR1: CMIA1
			CMIB1		= 150,	///< TMR1: CMIB1
			OVI1		= 151,	///< TMR1: OVI1
			CMIA2		= 152,	///< TMR2: CMIA2
			CMIB2		= 153,	///< TMR2: CMIB2
			OVI2		= 154,	///< TMR2: OVI2
			CMIA3		= 155,	///< TMR3: CMIA3
			CMIB3		= 156,	///< TMR3: CMIB3
			OVI3		= 157,	///< TMR3: OVI3
			CMIA4		= 158,	///< TMR4: CMIA4
			CMIB4		= 159,	///< TMR4: CMIB4
			OVI4		= 160,	///< TMR4: OVI4
			CMIA5		= 161,	///< TMR5: CMIA5
			CMIB5		= 162,	///< TMR5: CMIB5
			OVI5		= 163,	///< TMR5: OVI5
			CMIA6		= 164,	///< TMR6: CMIA6
			CMIB6		= 165,	///< TMR6: CMIB6
			OVI6		= 166,	///< TMR6: OVI6
			CMIA7		= 167,	///< TMR7: CMIA7
			CMIB7		= 168,	///< TMR7: CMIB7
			OVI7		= 169,	///< TMR7: OVI7

			RXF0		= 170,	///< CAN0 RXF
			TXF0		= 171,	///< CAN0 TXF
			RXM0		= 172,	///< CAN0 RXM
			TXM0		= 173,	///< CAN0 TXM

			USBI0		= 174,	///< USB0

			ELSR18I		= 175,	///< ELC
			ELSR19I		= 176,	///< ELC

			RD			= 177,	///< TSIP-Lite
			WR			= 178,	///< TSIP-Lite
			ERR			= 179,	///< TSIP-Lite

			CMPC0	  = 180,	///< CMPC0
			CMPC1	  = 181,	///< CMPC1
			CMPC2	  = 182,	///< CMPC2
			CMPC3	  = 183,	///< CMPC3
			CMPC4	  = 184,	///< CMPC4
			CMPC5	  = 185,	///< CMPC5

			INTA208   = 208,	///< PERIA
			INTA209   = 209,	///< PERIA
			INTA210   = 210,	///< PERIA
			INTA211   = 211,	///< PERIA
			INTA212   = 212,	///< PERIA
			INTA213   = 213,	///< PERIA
			INTA214   = 214,	///< PERIA
			INTA215   = 215,	///< PERIA
			INTA216   = 216,	///< PERIA
			INTA217   = 217,	///< PERIA
			INTA218   = 218,	///< PERIA
			INTA219   = 219,	///< PERIA
			INTA220   = 220,	///< PERIA
			INTA221   = 221,	///< PERIA
			INTA222   = 222,	///< PERIA
			INTA223   = 223,	///< PERIA
			INTA224   = 224,	///< PERIA
			INTA225   = 225,	///< PERIA
			INTA226   = 226,	///< PERIA
			INTA227   = 227,	///< PERIA
			INTA228   = 228,	///< PERIA
			INTA229   = 229,	///< PERIA
			INTA230   = 230,	///< PERIA
			INTA231   = 231,	///< PERIA
			INTA232   = 232,	///< PERIA
			INTA233   = 233,	///< PERIA
			INTA234   = 234,	///< PERIA
			INTA235   = 235,	///< PERIA
			INTA236   = 236,	///< PERIA
			INTA237   = 237,	///< PERIA
			INTA238   = 238,	///< PERIA
			INTA239   = 239,	///< PERIA
			INTA240   = 240,	///< PERIA
			INTA241   = 241,	///< PERIA
			INTA242   = 242,	///< PERIA
			INTA243   = 243,	///< PERIA
			INTA244   = 244,	///< PERIA
			INTA245   = 245,	///< PERIA
			INTA246   = 246,	///< PERIA
			INTA247   = 247,	///< PERIA
			INTA248   = 248,	///< PERIA
			INTA249   = 249,	///< PERIA
			INTA250   = 250,	///< PERIA
			INTA251   = 251,	///< PERIA
			INTA252   = 252,	///< PERIA
			INTA253   = 253,	///< PERIA
			INTA254   = 254,	///< PERIA
			INTA255   = 255		///< PERIA
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPIE0・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_IE0 : uint8_t {
			DPFPUEX,		///< 倍精度浮動少数点例外
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBE0・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BE0 : uint8_t {
			ERS0,			///< CAN0 / ERS0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL0・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BL0 : uint8_t {
			TEI1 = 2,		///< SCI1 / TEI1（送信完了）
			ERI1,			///< SCI1 / ERI1（受信エラー）

			TEI5 = 10,		///< SCI5 / TEI5（送信完了）
			ERI5,			///< SCI5 / ERI5（受信エラー）
			TEI6,			///< SCI6 / TEI6（送信完了）
			ERI6,			///< SCI6 / ERI6（受信エラー）

			TEI12 = 16,		///< SCI12 / TEI12（送信完了）
			ERI12,			///< SCI12 / ERI12（受信エラー）
			SCIX0,			///< SCI12 / SCIX0
			SCIX1,			///< SCI12 / SCIX1
			SCIX2,			///< SCI12 / SCIX2
			SCIX3,			///< SCI12 / SCIX3

			FERRI = 26,		///< CAC / FERRI
			MENDI,			///< CAC / MENDI
			OVFI,			///< CAC / OVFI
			DOPCI,			///< DOC / DOPCI
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL1・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BL1 : uint8_t {
			POEGGAI,		///< POEG (group A)
			POEGGBI,		///< POEG (group B)
			POEGGCI,		///< POEG (group C)
			POEGGDI,		///< POEG (group C)

			OEI5 = 8,		///< POE / OEI5
			OEI1,			///< POE / OEI1
			OEI2,			///< POE / OEI2
			OEI3,			///< POE / OEI3
			OEI4,			///< POE / OEI4
			TEI0,			///< RIIC0 / TEI0
			EEI0,			///< RIIC0 / EEI0

			S12CMPAI2 = 18,	///< S12AD2 / S12CMPAI2
			S12CMPBI2,		///< S12AD2 / S12CMPBI2
			S12CMPAI,		///< S12AD / S12CMPAI
			S12CMPBI,		///< S12AD / S12CMPBI
			S12CMPAI1,		///< S12AD1 / S12CMPAI1
			S12CMPBI1,		///< S12AD1 / S12CMPBI1
			TEI8,			///< SCI8 / TEI8
			ERI8,			///< SCI8 / ERI8
			TEI9,			///< SCI9 / TEI9
			ERI9,			///< SCI9 / ERI9
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL0・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_AL0 : uint8_t {
			TEI11 = 12,		///< SCI11 / TEI11
			ERI11,			///< SCI11 / ERI11

			SPII0 = 16,		///< RSPI0 / SPII0
			SPEI0,			///< RSPI0 / SPEI0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込みＡ要因・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_SELA : uint8_t {
			NONE = 0,	///< なし

			TGIA0 = 1,	///< MTU0（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB0,		///< MTU0（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC0,		///< MTU0（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID0,		///< MTU0（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV0,		///< MTU0（TCNTのオーバフロー）
			TGIE0,		///< MTU0（TGREのインプットキャプチャ /コンペアマッチ）
			TGIF0,		///< MTU0（TGRFのインプットキャプチャ /コンペアマッチ）

			TGIA1 = 8,	///< MTU1（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB1,		///< MTU1（TGRBのインプットキャプチャ /コンペアマッチ）
			TCIV1,		///< MTU1（TCNTのオーバフロー）
			TCIU1,		///< MTU1（TCNTのアンダフロー）

			TGIA2 = 12,	///< MTU2（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB2,		///< MTU2（TGRBのインプットキャプチャ /コンペアマッチ）
			TCIV2,		///< MTU2（TCNTのオーバフロー）
			TCIU2,		///< MTU2（TCNTのアンダフロー）

			TGIA3 = 16,	///< MTU3（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB3,		///< MTU3（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC3,		///< MTU3（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID3,		///< MTU3（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV3,		///< MTU3（TCNTのオーバフロー）

			TGIA4 = 21,	///< MTU4（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB4,		///< MTU4（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC4,		///< MTU4（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID4,		///< MTU4（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV4,		///< MTU4（TCNTのオーバフロー /アンダフロー（相補PWMモード時のみ））

			TGIU5 = 27,	///< MTU5（TGRUのインプットキャプチャ /コンペアマッチ）
			TGIV5,		///< MTU5（TGRVのインプットキャプチャ /コンペアマッチ）
			TGIW5,		///< MTU5（TGRWのインプットキャプチャ /コンペアマッチ）

			TGIA6 = 30,	///< MTU6（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB6,		///< MTU6（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC6,		///< MTU6（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID6,		///< MTU6（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV6,		///< MTU6（TCNTのオーバフロー）

			TGIA7 = 35,	///< MTU7（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB7,		///< MTU7（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC7,		///< MTU7（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID7,		///< MTU7（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV7,		///< MTU7（TCNTのオーバフロー /アンダフロー (相補PWMモード時のみ))

			TGIA8 = 41,	///< MTU8（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB8,		///< MTU8（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC8,		///< MTU8（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID8,		///< MTU8（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV8,		///< MTU8（TCNTのオーバフロー）

			TGIA9 = 47,	///< MTU9（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB9,		///< MTU9（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC9,		///< MTU9（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID9,		///< MTU9（TGRDのインプットキャプチャ /コンペアマッチ）
			TGIV9,		///< MTU9（TCNTのオーバフロー）
			TGIE9,		///< MTU9 (TGREのコンペアマッチ)
			TGIF9,		///< MTU9 (TGRFのコンペアマッチ)

			GTCIA0 = 56,///< GPTW0 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB0,		///< GPTW0 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC0,		///< GPTW0 (GTCCRC レジスタのコンペアマッチ)
			GTCID0,		///< GPTW0 (GTCCRD レジスタのコンペアマッチ)
			GDTE0,		///< GPTW0 (デッドタイムエラー)
			GTCIE0,		///< GPTW0 (GTCCRE レジスタのコンペアマッチ)
			GTCIF0,		///< GPTW0 (GTCCRF レジスタのコンペアマッチ)
			GTCIV0,		///< GPTW0 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU0,		///< GPTW0 (GTCNT カウンタのアンダフロー)

			GTCIA1 = 65,///< GPTW1 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB1,		///< GPTW1 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC1,		///< GPTW1 (GTCCRC レジスタのコンペアマッチ)
			GTCID1,		///< GPTW1 (GTCCRD レジスタのコンペアマッチ)
			GDTE1,		///< GPTW1 (デッドタイムエラー)
			GTCIE1,		///< GPTW1 (GTCCRE レジスタのコンペアマッチ)
			GTCIF1,		///< GPTW1 (GTCCRF レジスタのコンペアマッチ)
			GTCIV1,		///< GPTW1 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU1,		///< GPTW1 (GTCNT カウンタのアンダフロー)

			GTCIA2 = 74,///< GPTW2 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB2,		///< GPTW2 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC2,		///< GPTW2 (GTCCRC レジスタのコンペアマッチ)
			GTCID2,		///< GPTW2 (GTCCRD レジスタのコンペアマッチ)
			GDTE2,		///< GPTW2 (デッドタイムエラー)
			GTCIE2,		///< GPTW2 (GTCCRE レジスタのコンペアマッチ)
			GTCIF2,		///< GPTW2 (GTCCRF レジスタのコンペアマッチ)
			GTCIV2,		///< GPTW2 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU2,		///< GPTW2 (GTCNT カウンタのアンダフロー)

			GTCIA3 = 83,///< GPTW3 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB3,		///< GPTW3 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC3,		///< GPTW3 (GTCCRC レジスタのコンペアマッチ)
			GTCID3,		///< GPTW3 (GTCCRD レジスタのコンペアマッチ)
			GDTE3,		///< GPTW3 (デッドタイムエラー)
			GTCIE3,		///< GPTW3 (GTCCRE レジスタのコンペアマッチ)
			GTCIF3,		///< GPTW3 (GTCCRF レジスタのコンペアマッチ)
			GTCIV3,		///< GPTW3 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU3,		///< GPTW3 (GTCNT カウンタのアンダフロー)

			GTCIA4 = 92,///< GPTW4 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB4,		///< GPTW4 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC4,		///< GPTW4 (GTCCRC レジスタのコンペアマッチ)
			GTCID4,		///< GPTW4 (GTCCRD レジスタのコンペアマッチ)
			GDTE4,		///< GPTW4 (デッドタイムエラー)
			GTCIE4,		///< GPTW4 (GTCCRE レジスタのコンペアマッチ)
			GTCIF4,		///< GPTW4 (GTCCRF レジスタのコンペアマッチ)
			GTCIV4,		///< GPTW4 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU4,		///< GPTW4 (GTCNT カウンタのアンダフロー)

			GTCIA5 =101,///< GPTW5 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB5,		///< GPTW5 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC5,		///< GPTW5 (GTCCRC レジスタのコンペアマッチ)
			GTCID5,		///< GPTW5 (GTCCRD レジスタのコンペアマッチ)
			GDTE5,		///< GPTW5 (デッドタイムエラー)
			GTCIE5,		///< GPTW5 (GTCCRE レジスタのコンペアマッチ)
			GTCIF5,		///< GPTW5 (GTCCRF レジスタのコンペアマッチ)
			GTCIV5,		///< GPTW5 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU5,		///< GPTW5 (GTCNT カウンタのアンダフロー)

			GTCIA6 =110,///< GPTW6 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB6,		///< GPTW6 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC6,		///< GPTW6 (GTCCRC レジスタのコンペアマッチ)
			GTCID6,		///< GPTW6 (GTCCRD レジスタのコンペアマッチ)
			GDTE6,		///< GPTW6 (デッドタイムエラー)
			GTCIE6,		///< GPTW6 (GTCCRE レジスタのコンペアマッチ)
			GTCIF6,		///< GPTW6 (GTCCRF レジスタのコンペアマッチ)
			GTCIV6,		///< GPTW6 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU6,		///< GPTW6 (GTCNT カウンタのアンダフロー)

			GTCIA7 =119,///< GPTW7 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB7,		///< GPTW7 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC7,		///< GPTW7 (GTCCRC レジスタのコンペアマッチ)
			GTCID7,		///< GPTW7 (GTCCRD レジスタのコンペアマッチ)
			GDTE7,		///< GPTW7 (デッドタイムエラー)
			GTCIE7,		///< GPTW7 (GTCCRE レジスタのコンペアマッチ)
			GTCIF7,		///< GPTW7 (GTCCRF レジスタのコンペアマッチ)
			GTCIV7,		///< GPTW7 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU7,		///< GPTW7 (GTCNT カウンタのアンダフロー)

			GTCIA8 =128,///< GPTW8 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB8,		///< GPTW8 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC8,		///< GPTW8 (GTCCRC レジスタのコンペアマッチ)
			GTCID8,		///< GPTW8 (GTCCRD レジスタのコンペアマッチ)
			GDTE8,		///< GPTW8 (デッドタイムエラー)
			GTCIE8,		///< GPTW8 (GTCCRE レジスタのコンペアマッチ)
			GTCIF8,		///< GPTW8 (GTCCRF レジスタのコンペアマッチ)
			GTCIV8,		///< GPTW8 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU8,		///< GPTW8 (GTCNT カウンタのアンダフロー)

			GTCIA9 =137,///< GPTW9 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB9,		///< GPTW9 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC9,		///< GPTW9 (GTCCRC レジスタのコンペアマッチ)
			GTCID9,		///< GPTW9 (GTCCRD レジスタのコンペアマッチ)
			GDTE9,		///< GPTW9 (デッドタイムエラー)
			GTCIE9,		///< GPTW9 (GTCCRE レジスタのコンペアマッチ)
			GTCIF9,		///< GPTW9 (GTCCRF レジスタのコンペアマッチ)
			GTCIV9,		///< GPTW9 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU9,		///< GPTW9 (GTCNT カウンタのアンダフロー)

			NONE2 = 255,///< 割り込み選択なし
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター IE0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_IE0 ivec) noexcept {
			return VECTOR::GROUPIE0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター BL0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BL0 ivec) noexcept {
			return VECTOR::GROUPBL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター BL1 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BL1 ivec) noexcept {
			return VECTOR::GROUPBL1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター BE0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BE0 ivec) noexcept {
			return VECTOR::GROUPBE0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター AL0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_AL0 ivec) noexcept {
			return VECTOR::GROUPAL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ・クラス
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {

			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		割り込みベクター型
				@return IR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) {
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

			//-------------------------------------------------------------//
			/*!
				@brief  許可、不許可
				@param[in]	vec		割り込みベクター型
				@param[in]	ena		不許可の場合「false」
			*/
			//-------------------------------------------------------------//
			void enable(VECTOR vec, bool ena = true) noexcept
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
			@brief  IPR レジスタ @n
					全て、下位４ビットが有効
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ipr_t {

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
				case VECTOR::RAMERR: idx = 0; break;
				case VECTOR::FIFERR: idx = 1; break;
				case VECTOR::FRDYI:  idx = 2; break;
				case VECTOR::SWINT2: idx = 3; break;
				case VECTOR::SWINT:  idx = 3; break;
				case VECTOR::CMI0:   idx = 4; break;
				case VECTOR::CMI1:   idx = 5; break;
				case VECTOR::CMI2:   idx = 6; break;
				case VECTOR::CMI3:   idx = 7; break;

				case VECTOR::CMIA0:
				case VECTOR::CMIB0:
				case VECTOR::OVI0:
					idx = static_cast<uint32_t>(VECTOR::CMIA0);
					break;
				case VECTOR::CMIA1:
				case VECTOR::CMIB1:
				case VECTOR::OVI1:
					idx = static_cast<uint32_t>(VECTOR::CMIA1);
					break;
				case VECTOR::CMIA2:
				case VECTOR::CMIB2:
				case VECTOR::OVI2:
					idx = static_cast<uint32_t>(VECTOR::CMIA2);
					break;
				case VECTOR::CMIA3:
				case VECTOR::CMIB3:
				case VECTOR::OVI3:
					idx = static_cast<uint32_t>(VECTOR::CMIA3);
					break;
				case VECTOR::CMIA4:
				case VECTOR::CMIB4:
				case VECTOR::OVI4:
					idx = static_cast<uint32_t>(VECTOR::CMIA4);
					break;
				case VECTOR::CMIA5:
				case VECTOR::CMIB5:
				case VECTOR::OVI5:
					idx = static_cast<uint32_t>(VECTOR::CMIA5);
					break;
				case VECTOR::CMIA6:
				case VECTOR::CMIB6:
				case VECTOR::OVI6:
					idx = static_cast<uint32_t>(VECTOR::CMIA6);
					break;
				case VECTOR::CMIA7:
				case VECTOR::CMIB7:
				case VECTOR::OVI7:
					idx = static_cast<uint32_t>(VECTOR::CMIA7);
					break;
				case VECTOR::RXF0:
				case VECTOR::TXF0:
				case VECTOR::RXM0:
				case VECTOR::TXM0:
					idx = static_cast<uint32_t>(VECTOR::RXF0);
					break;
				default: idx = static_cast<uint32_t>(vec); break;
				}
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		typedef ipr_t<0x00087300> IPR_;
		static IPR_ IPR;


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
		typedef grp_t<0x00087600> GRPBE0_;
		static GRPBE0_ GRPBE0;
		typedef grp_t<0x00087630> GRPBL0_;
		static GRPBL0_ GRPBL0;
		typedef grp_t<0x00087634> GRPBL1_;
		static GRPBL1_ GRPBL1;
		typedef grp_t<0x00087830> GRPAL0_;
		static GRPAL0_ GRPAL0;
		typedef grp_t<0x00087834> GRPAL1_;
		static GRPAL1_ GRPAL1;


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

			bit_rw_t<io_, bitpos::B0>  EN0;
			bit_rw_t<io_, bitpos::B1>  EN1;
			bit_rw_t<io_, bitpos::B2>  EN2;
			bit_rw_t<io_, bitpos::B3>  EN3;
			bit_rw_t<io_, bitpos::B4>  EN4;
			bit_rw_t<io_, bitpos::B5>  EN5;
			bit_rw_t<io_, bitpos::B6>  EN6;
			bit_rw_t<io_, bitpos::B7>  EN7;

			bit_rw_t<io_, bitpos::B8>  EN8;
			bit_rw_t<io_, bitpos::B9>  EN9;
			bit_rw_t<io_, bitpos::B10> EN10;
			bit_rw_t<io_, bitpos::B11> EN11;
			bit_rw_t<io_, bitpos::B12> EN12;
			bit_rw_t<io_, bitpos::B13> EN13;
			bit_rw_t<io_, bitpos::B14> EN14;
			bit_rw_t<io_, bitpos::B15> EN15;

			bit_rw_t<io_, bitpos::B16> EN16;
			bit_rw_t<io_, bitpos::B17> EN17;
			bit_rw_t<io_, bitpos::B18> EN18;
			bit_rw_t<io_, bitpos::B19> EN19;
			bit_rw_t<io_, bitpos::B20> EN20;
			bit_rw_t<io_, bitpos::B21> EN21;
			bit_rw_t<io_, bitpos::B22> EN22;
			bit_rw_t<io_, bitpos::B23> EN23;

			bit_rw_t<io_, bitpos::B24> EN24;
			bit_rw_t<io_, bitpos::B25> EN25;
			bit_rw_t<io_, bitpos::B26> EN26;
			bit_rw_t<io_, bitpos::B27> EN27;
			bit_rw_t<io_, bitpos::B28> EN28;
			bit_rw_t<io_, bitpos::B29> EN29;
			bit_rw_t<io_, bitpos::B30> EN30;
			bit_rw_t<io_, bitpos::B31> EN31;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求許可レジスタ（GENBE0）@n
					グループ BL0/1 割り込み要求許可レジスタ（GENBL0/GENBL1/GENBL2）@n
					グループ AL0/1 割り込み要求許可レジスタ（GENAL0/GENAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gen_t<0x00087640> GENBE0_;
		static GENBE0_ GENBE0;
		typedef gen_t<0x00087670> GENBL0_;
		static GENBL0_ GENBL0;
		typedef gen_t<0x00087674> GENBL1_;
		static GENBL1_ GENBL1;
		typedef gen_t<0x00087870> GENAL0_;
		static GENAL0_ GENAL0;
		typedef gen_t<0x00087874> GENAL1_;
		static GENAL1_ GENAL1;


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
		typedef gcrbe0_t<0x00087680> GCRBE0_;
		static GCRBE0_ GCRBE0;


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
			@brief  選択型割り込み A 要求レジスタ k（PIARk）（k = 0h ～ Bh）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pixr_t<0x00087900> PIAR0_;
		static PIAR0_ PIAR0;
		typedef pixr_t<0x00087901> PIAR1_;
		static PIAR1_ PIAR1;
		typedef pixr_t<0x00087902> PIAR2_;
		static PIAR2_ PIAR2;
		typedef pixr_t<0x00087903> PIAR3_;
		static PIAR3_ PIAR3;
		typedef pixr_t<0x00087904> PIAR4_;
		static PIAR4_ PIAR4;
		typedef pixr_t<0x00087905> PIAR5_;
		static PIAR5_ PIAR5;
		typedef pixr_t<0x00087906> PIAR6_;
		static PIAR6_ PIAR6;
		typedef pixr_t<0x00087907> PIAR7_;
		static PIAR7_ PIAR7;
		typedef pixr_t<0x00087908> PIAR8_;
		static PIAR8_ PIAR8;
		typedef pixr_t<0x00087909> PIAR9_;
		static PIAR9_ PIAR9;
		typedef pixr_t<0x0008790A> PIARA_;
		static PIARA_ PIARA;
		typedef pixr_t<0x0008790B> PIARB_;
		static PIARB_ PIARB;
		typedef pixr_t<0x0008790C> PIARC_;
		static PIARC_ PIARC;
		typedef pixr_t<0x0008790D> PIARD_;
		static PIARD_ PIARD;
		typedef pixr_t<0x0008790E> PIARE_;
		static PIARE_ PIARE;
		typedef pixr_t<0x0008790F> PIARF_;
		static PIARF_ PIARF;
		typedef pixr_t<0x00087910> PIAR10_;
		static PIAR10_ PIAR10;
		typedef pixr_t<0x00087911> PIAR11_;
		static PIAR11_ PIAR11;
		typedef pixr_t<0x00087912> PIAR12_;
		static PIAR12_ PIAR12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要因選択レジスタ n（SLIARn）（n = 208 ～ 255）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef icu_utils::slixr_t<0x00087900, VECTOR, VECTOR_SELA> SLIAR_;
		static SLIAR_ SLIAR;
	};
	typedef icuc_t<void> ICU;

	template<class _> typename icuc_t<_>::IR_ icuc_t<_>::IR;
	template<class _> typename icuc_t<_>::IER_ icuc_t<_>::IER;
	template<class _> typename icuc_t<_>::IPR_ icuc_t<_>::IPR;

	template<class _> typename icuc_t<_>::GRPBE0_ icuc_t<_>::GRPBE0;
	template<class _> typename icuc_t<_>::GRPBL0_ icuc_t<_>::GRPBL0;
	template<class _> typename icuc_t<_>::GRPBL1_ icuc_t<_>::GRPBL1;
	template<class _> typename icuc_t<_>::GRPAL0_ icuc_t<_>::GRPAL0;
	template<class _> typename icuc_t<_>::GRPAL1_ icuc_t<_>::GRPAL1;

	template<class _> typename icuc_t<_>::GENBE0_ icuc_t<_>::GENBE0;
	template<class _> typename icuc_t<_>::GENBL0_ icuc_t<_>::GENBL0;
	template<class _> typename icuc_t<_>::GENBL1_ icuc_t<_>::GENBL1;
	template<class _> typename icuc_t<_>::GENAL0_ icuc_t<_>::GENAL0;
	template<class _> typename icuc_t<_>::GENAL1_ icuc_t<_>::GENAL1;

	template<class _> typename icuc_t<_>::GCRBE0_ icuc_t<_>::GCRBE0;

	template<class _> typename icuc_t<_>::PIAR0_ icuc_t<_>::PIAR0;
	template<class _> typename icuc_t<_>::PIAR1_ icuc_t<_>::PIAR1;
	template<class _> typename icuc_t<_>::PIAR2_ icuc_t<_>::PIAR2;
	template<class _> typename icuc_t<_>::PIAR3_ icuc_t<_>::PIAR3;
	template<class _> typename icuc_t<_>::PIAR4_ icuc_t<_>::PIAR4;
	template<class _> typename icuc_t<_>::PIAR5_ icuc_t<_>::PIAR5;
	template<class _> typename icuc_t<_>::PIAR6_ icuc_t<_>::PIAR6;
	template<class _> typename icuc_t<_>::PIAR7_ icuc_t<_>::PIAR7;
	template<class _> typename icuc_t<_>::PIAR8_ icuc_t<_>::PIAR8;
	template<class _> typename icuc_t<_>::PIAR9_ icuc_t<_>::PIAR9;
	template<class _> typename icuc_t<_>::PIARA_ icuc_t<_>::PIARA;
	template<class _> typename icuc_t<_>::PIARB_ icuc_t<_>::PIARB;
	template<class _> typename icuc_t<_>::PIARC_ icuc_t<_>::PIARC;
	template<class _> typename icuc_t<_>::PIARD_ icuc_t<_>::PIARD;
	template<class _> typename icuc_t<_>::PIARE_ icuc_t<_>::PIARE;
	template<class _> typename icuc_t<_>::PIARF_ icuc_t<_>::PIARF;
	template<class _> typename icuc_t<_>::PIAR10_ icuc_t<_>::PIAR10;
	template<class _> typename icuc_t<_>::PIAR11_ icuc_t<_>::PIAR11;
	template<class _> typename icuc_t<_>::PIAR12_ icuc_t<_>::PIAR12;

	template<class _> typename icuc_t<_>::SLIAR_ icuc_t<_>::SLIAR;
}
