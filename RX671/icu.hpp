#pragma once
//=========================================================================//
/*!	@file
	@brief	RX671 グループ・ICUE 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/icu_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX671 割り込みコントローラ・テンプレート・クラス（ICUE）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t : public ICU_BASE, ICU_IRQ16, ICU_GROUP, ICU_SELECT {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常割り込みベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {
			NONE		= 0,		///< ベクター０

			BUSERR		= 16,		///< BSC
			GROUPIE0	= 17,		///< ICU
			RAMERR		= 18,		///< RAM

			FIFERR		= 21,		///< FCU

			FRDYI		= 23,		///< FCU

			SWINT2		= 26,		///< ICU
			SWINT		= 27,		///< ICU

			CMI0		= 28,		///< CMT0
			CMI1		= 29,		///< CMT1
			CMWI0		= 30,		///< CMTW0
			CMWI1		= 31,		///< CMTW1

			RRXI10		= 32,		///< RSCI10
			RTXI10		= 33,		///< RSCI10

			D0FIFO0		= 34,		///< USB0
			D1FIFO0		= 35,		///< USB0
			D0FIFO1		= 36,		///< USB1
			D1FIFO1		= 37,		///< USB1

			SPRI0		= 38,		///< RSPI0
			SPTI0		= 39,		///< RSPI0
			SPRI1		= 40,		///< RSPI1
			SPTI1		= 41,		///< RSPI1

			RRXI11		= 42,		///< RSCI11
			RTXI11		= 43,		///< RSCI11

			SBFAI		= 44,		///< SDHI

			SSITXI0		= 46,		///< SSIE0
			SSIRXI0		= 47,		///< SSIE0

			SPARI0		= 48,		///< RSPIA0 RX 
			SPATI0		= 49,		///< RSPIA0 TX

			ICRXI1		= 50,		///< RIIC1 RXI
			ICTXI1		= 51,		///< RIIC1 TXI
			ICRXI0		= 52,		///< RIIC0 RXI
			ICTXI0		= 53,		///< RIIC0 TXI
			ICRXI2		= 54,		///< RIIC2 RXI
			ICTXI2		= 55,		///< RIIC2 TXI

			RXI0		= 58,		///< SCI0
			TXI0		= 59,
			RXI1		= 60,		///< SCI1
			TXI1		= 61,
			RXI2		= 62,		///< SCI2
			TXI2		= 63, 

			IRQ0        = 64,		///< ICU
			IRQ1        = 65,
			IRQ2        = 66,
			IRQ3        = 67,
			IRQ4        = 68,
			IRQ5        = 69,
			IRQ6        = 70,
			IRQ7        = 71,
			IRQ8        = 72,
			IRQ9        = 73,
			IRQ10       = 74,
			IRQ11       = 75,
			IRQ12       = 76,
			IRQ13       = 77,
			IRQ14       = 78,
			IRQ15       = 79,

			RXI3        = 80,		///< SCI3
			TXI3        = 81,
			RXI4        = 82,		///< SCI4
			TXI4        = 83,
			RXI5        = 84,		///< SCI5
			TXI5        = 85,
			RXI6        = 86,		///< SCI6
			TXI6        = 87,

			LVD1        = 88,		///< LVD1
			LVD2        = 89,		///< LVD2

			USBR0       = 90,		///< USB0

			TAMPDI		= 91,		///< VBATT

			ALM         = 92,		///< RTC
			PRD         = 93,

			IWUNI       = 95,		///< IWDT

			WUNI        = 96,		///< WDT

			RXI7        = 98,		///< SCI7 RX
			TXI7        = 99,		///< SCI7 TX
			RXI8        = 100,		///< SCI8 RX
			TXI8        = 101,		///< SCI8 TX
			RXI9        = 102,		///< SCI9 RX
			TXI9        = 103,		///< SCI9 TX
			RXI10       = 104,		///< SCI10 RX
			TXI10       = 105,		///< SCI10 TX

			GROUPBE0    = 106,		///< ICU
			GROUPBL2    = 107,

			SPRI2       = 108,		///< RSPI2 R
			SPTI2       = 109,		///< RSPI2 T

			GROUPBL0	= 110,		///< ICU
			GROUPBL1	= 111,		///< ICU
			GROUPAL0	= 112,		///< ICU
			GROUPAL1	= 113,		///< ICU

			RXI11   	= 114,		///< SCI11 RX
			TXI11   	= 115,		///< SCI11 TX
			RXI12   	= 116,		///< SCI12 RX
			TXI12   	= 117,		///< SCI12 TX

			ICHSRXI		= 118,		///< RIICHS0 RX
			ICHSTXI		= 119,		///< RIICHS0 TX

			DMAC0I  	= 120,		///< DMAC 0
			DMAC1I  	= 121,		///< DMAC 1
			DMAC2I  	= 122,		///< DMAC 2
			DMAC3I  	= 123,		///< DMAC 3
			DMAC74I 	= 124,		///< DMAC 4,5,6,7

			OSTDI    	= 125,		///< OST

			EXDMAC0I 	= 126,		///< EXDMAC 0
			EXDMAC1I 	= 127,		///< EXDMAC 1

			INTB128  	= 128,
			INTB129,
			INTB130,
			INTB131,
			INTB132,
			INTB133,
			INTB134,
			INTB135,
			INTB136,
			INTB137,
			INTB138,
			INTB139,
			INTB140,
			INTB141,
			INTB142,
			INTB143,
			INTB144,
			INTB145,
			INTB146,
			INTB147,
			INTB148,
			INTB149,
			INTB150,
			INTB151,
			INTB152,
			INTB153,
			INTB154,
			INTB155,
			INTB156,
			INTB157,
			INTB158,
			INTB159,
			INTB160,
			INTB161,
			INTB162,
			INTB163,
			INTB164,
			INTB165,
			INTB166,
			INTB167,
			INTB168,
			INTB169,
			INTB170,
			INTB171,
			INTB172,
			INTB173,
			INTB174,
			INTB175,
			INTB176,
			INTB177,
			INTB178,
			INTB179,
			INTB180,
			INTB181,
			INTB182,
			INTB183,
			INTB184,
			INTB185,
			INTB186,
			INTB187,
			INTB188,
			INTB189,
			INTB190,
			INTB191,
			INTB192,
			INTB193,
			INTB194,
			INTB195,
			INTB196,
			INTB197,
			INTB198,
			INTB199,
			INTB200,
			INTB201,
			INTB202,
			INTB203,
			INTB204,
			INTB205,
			INTB206,
			INTB207,

			INTA208		= 208,
			INTA209,
			INTA210,
			INTA211,
			INTA212,
			INTA213,
			INTA214,
			INTA215,
			INTA216,
			INTA217,
			INTA218,
			INTA219,
			INTA220,
			INTA221,
			INTA222,
			INTA223,
			INTA224,
			INTA225,
			INTA226,
			INTA227,
			INTA228,
			INTA229,
			INTA230,
			INTA231,
			INTA232,
			INTA233,
			INTA234,
			INTA235,
			INTA236,
			INTA237,
			INTA238,
			INTA239,
			INTA240,
			INTA241,
			INTA242,
			INTA243,
			INTA244,
			INTA245,
			INTA246,
			INTA247,
			INTA248,
			INTA249,
			INTA250,
			INTA251,
			INTA252,
			INTA253,
			INTA254,
			INTA255,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込みＢ要因・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SELECTB : uint8_t {
			NONE = 0,	///< 要因無し

			CMI2 = 1,	///< CMT2
			CMI3 = 2,	///< CMT3

			CMIA0 = 3,	///< TMR0 (TCORA のコンペアマッチ)
			CMIB0,		///< TMR0 (TCORB のコンペアマッチ)
			OVI0,		///< TMR0 (TCNT のオーバフロー)
			CMIA1,		///< TMR1 (TCORA のコンペアマッチ)
			CMIB1,		///< TMR1 (TCORB のコンペアマッチ)
			OVI1,		///< TMR1 (TCNT のオーバフロー)
			CMIA2,		///< TMR2 (TCORA のコンペアマッチ)
			CMIB2,		///< TMR2 (TCORB のコンペアマッチ)
			OVI2,		///< TMR2 (TCNT のオーバフロー)
			CMIA3,		///< TMR3 (TCORA のコンペアマッチ)
			CMIB3,		///< TMR3 (TCORB のコンペアマッチ)
			OVI3,		///< TMR3 (TCNT のオーバフロー)

			TGI0A = 15,	///< TPU0 (TGRA のインプットキャプチャ / コンペアマッチ)
			TGI0B,		///< TPU0 (TGRB のインプットキャプチャ / コンペアマッチ)
			TGI0C,		///< TPU0 (TGRC のインプットキャプチャ / コンペアマッチ)
			TGI0D,		///< TPU0 (TGRD のインプットキャプチャ / コンペアマッチ)
			TGI0V,		///< TPU0 (TCNT のオーバフロー)

			TGI1A,		///< TPU1 (TGRA のインプットキャプチャ / コンペアマッチ)
			TGI1B,		///< TPU1 (TGRB のインプットキャプチャ / コンペアマッチ)
			TGI1V,		///< TPU1 (TCNT のオーバフロー)
			TGI1U,		///< TPU1 (TCNT のアンダーフロー)

			TGI2A,		///< TPU2 (TGRA のインプットキャプチャ / コンペアマッチ)
			TGI2B,		///< TPU2 (TGRB のインプットキャプチャ / コンペアマッチ)
			TGI2V,		///< TPU2 (TCNT のオーバフロー)
			TGI2U,		///< TPU2 (TCNT のアンダーフロー)

			TGI3A,		///< TPU3 (TGRA のインプットキャプチャ / コンペアマッチ)
			TGI3B,		///< TPU3 (TGRB のインプットキャプチャ / コンペアマッチ)
			TGI3C,		///< TPU3 (TGRC のインプットキャプチャ / コンペアマッチ)
			TGI3D,		///< TPU3 (TGRD のインプットキャプチャ / コンペアマッチ)
			TGI3V,		///< TPU3 (TCNT のオーバフロー)

			TGI4A,		///< TPU4 (TGRA のインプットキャプチャ / コンペアマッチ)
			TGI4B,		///< TPU4 (TGRB のインプットキャプチャ / コンペアマッチ)
			TGI4V,		///< TPU4 (TCNT のオーバフロー)
			TGI4U,		///< TPU4 (TCNT のアンダーフロー)

			TGI5A,		///< TPU5 (TGRA のインプットキャプチャ / コンペアマッチ)
			TGI5B,		///< TPU5 (TGRB のインプットキャプチャ / コンペアマッチ)
			TGI5V,		///< TPU5 (TCNT のオーバフロー)
			TGI5U,		///< TPU5 (TCNT のアンダーフロー)

			IC0I0,		///< CMTW0 (CMWICR0 レジスタのインプットキャプチャ入力)
			IC1I0,		///< CMTW0 (CMWICR1 レジスタのインプットキャプチャ入力)
			OC0I0,		///< CMTW0 (CMWOCR0 レジスタのアウトプットコンペア出力)
			OC1I0,		///< CMTW0 (CMWOCR1 レジスタのアウトプットコンペア出力)
			IC0I1,		///< CMTW1 (CMWICR0 レジスタのインプットキャプチャ入力)
			IC1I1,		///< CMTW1 (CMWICR1 レジスタのインプットキャプチャ入力)
			OC0I1,		///< CMTW1 (CMWOCR0 レジスタのアウトプットコンペア出力)
			OC1I1,		///< CMTW1 (CMWOCR1 レジスタのアウトプットコンペア出力)

			CUP			= 49,	///< RTC (桁上げ割り込み)

			RXF0		= 50,	///< CAN0（受信 FIFO 割り込み）
			TXF0		= 51,	///< CAN0（送信 FIFO 割り込み）
			RXM0		= 52,	///< CAN0（メールボックス０～３１メッセージ受信完了）
			TXM0		= 53,	///< CAN0（メールボックス０～３１メッセージ送信完了）
			RXF1		= 54,	///< CAN1（受信 FIFO 割り込み）
			TXF1		= 55,	///< CAN1（送信 FIFO 割り込み）
			RXM1		= 56,	///< CAN1（メールボックス０～３１メッセージ受信完了）
			TXM1		= 57,	///< CAN1（メールボックス０～３１メッセージ送信完了）
			RXF2		= 58,	///< CAN2（受信 FIFO 割り込み）
			TXF2		= 59,	///< CAN2（送信 FIFO 割り込み）
			RXM2		= 60,	///< CAN2（メールボックス０～３１メッセージ受信完了）
			TXM2		= 61,	///< CAN2（メールボックス０～３１メッセージ送信完了）

			USBI0		= 62,	///< USB0（１５要因のステータス割り込み）
			USBI1		= 63,	///< USB1（１５要因のステータス割り込み）

			S12ADI		= 64,	///< S12AD (A/D変換終了)
			S12GBADI	= 65,	///< S12AD (グループ B A/D変換終了割り込み)
			S12GCADI	= 66,	///< S12AD (グループ C A/D変換終了割り込み)
			S12ADI1		= 68,	///< S12AD1 (A/D変換終了)
			S12GBADI1	= 69,	///< S12AD1 (グループ B A/D変換終了割り込み)
			S12GCADI1	= 70,	///< S12AD1 (グループ C A/D変換終了割り込み)

			RNGEND = 76,	///< RNG (完了割り込み)

			ELSR18I = 79,	///< ELC (ELC割り込み)
			ELSR19I,		///< ELC (ELC割り込み)

			PROC_BUSY = 85,	///< TSIP (手順完了割り込み)
			ROMOK,			///< TSIP (改ざん検出割り込み)
			LONG_PLG,		///< TSIP (演算完了割り込み)
			TEST_BUSY,		///< TSIP (テストビジー )
			WRRDY0,			///< TSIP (ライトレディ 0)
			WRRDY1,			///< TSIP (ライトレディ 1)
			WRRDY4,			///< TSIP (ライトレディ 4)
			RDRDY0,			///< TSIP (リードレディ 0)
			RDRDY1,			///< TSIP (リードレディ 1)
			INTEGRATE_WRRDY,	///< TSIP (インテグレートライトレディ )
			INTEGRATE_RDRDY,	///< TSIP (インテグレートリードレディ )
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込みＡ要因・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SELECTA : uint8_t {
			NONE = 0,	///< 要因無し

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
			TCIV7,		///< MTU7（TCNTのオーバフロー /アンダフロー（相補PWMモード時のみ））

			TGIA8 = 41,	///< MTU8（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB8,		///< MTU8（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC8,		///< MTU8（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID8,		///< MTU8（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV8,		///< MTU8（TCNTのオーバフロー）

			AESRDY = 88,	///< AES (暗号/復号準備完了)
			AESEND,			///< AES (暗号/復号準備完了)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBE0・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUPBE0 : uint8_t {
			ERS0 = 0,	///< CAN0 (エラー割り込み)
			ERS1,		///< CAN1 (エラー割り込み)
			NUM_ = 2
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL0・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUPBL0 : uint8_t {
			TEI0 = 0,	///< SCI0 （送信完了）
			ERI0,		///< SCI0 （受信エラー）
			TEI1,		///< SCI1 （送信完了）
			ERI1,		///< SCI1 （受信エラー）
			TEI2,		///< SCI2 （送信完了）
			ERI2,		///< SCI2 （受信エラー）
			TEI3,		///< SCI3 （送信完了）
			ERI3,		///< SCI3 （受信エラー）
			TEI4,		///< SCI4 （送信完了）
			ERI4,		///< SCI4 （受信エラー）
			TEI5,		///< SCI5 （送信完了）
			ERI5,		///< SCI5 （受信エラー）
			TEI6,		///< SCI6 （送信完了）
			ERI6,		///< SCI6 （受信エラー）
			TEI7,		///< SCI7 （送信完了）
			ERI7,		///< SCI7 （受信エラー）
			TEI12,		///< SCI12（送信完了）
			ERI12,		///< SCI12（受信エラー）
			SCIX0,		///< SCI12 (Break Field Low width検出)
			SCIX1,		///< SCI12 (Control Field 0一致),(Control Field 1一致),(プライオリティインタラプトビット検出)
			SCIX2,		///< SCI12 (バス衝突検出)
			SCIX3,		///< SCI12 (有効エッジ検出)

			FERRI = 26,	///< CAC (周波数エラー )
			MENDI,		///< CAC (測定終了)
			OVFI,		///< CAC (オーバフロー割り込み)

			DOPCI = 29,	///< DOC (データ演算回路割り込み)

			NUM_ = 26
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL1・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUPBL1 : uint8_t {
			CDETI = 3,		///< SDHI (カード検出割り込み)
			CACI,			///< SDHI (カードアクセス割り込み)
			SDACI,			///< SDHI (SDIOアクセス割り込み)

			OEI1 = 9,		///< POE3 (アウトプットイネーブル割り込み1)
			OEI2,			///< POE3 (アウトプットイネーブル割り込み2)
			OEI3,			///< POE3 (アウトプットイネーブル割り込み3)
			OEI4,			///< POE3 (アウトプットイネーブル割り込み4)

			TEI0 = 13,		///< RIIC0 (送信完了)
			EEI0,			///< RIIC0 (通信エラー /通信イベント)
			TEI2,			///< RIIC2 (送信完了)
			EEI2,			///< RIIC2 (通信エラー /通信イベント)

			SSIF0 = 17,		///< SSIE0 (ステータス割り込み)

			S12CMPAI = 20,	///< S12AD (コンペア割り込み)
			S12CMPBI,		///< S12AD (コンペア割り込み)
			S12CMPAI1 = 22,	///< S12AD1 (コンペア割り込み)
			S12CMPBI1,		///< S12AD1 (コンペア割り込み)

			TEI8 = 24,		///< SCI8 (送信完了)
			ERI8,			///< SCI8 (受信エラー)
			TEI9,			///< SCI9 (送信完了)
			ERI9,			///< SCI9 (受信エラー)

			TEI1 = 28,		///< RIIC1 (送信完了)
			EEI1,			///< RIIC1 (通信エラー /通信イベント)

			NUM_ = 22
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL2・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUPBL2 : uint8_t {
			NUM_ = 0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL0・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUPAL0 : uint8_t {
			TEI10 = 8,		///< SCI10 (送信完了)
			ERI10,			///< SCI10 (受信エラー )

			TEI11 = 12,		///< SCI11 (送信完了)
			ERI11,			///< SCI11 (受信エラー )

			SPII0 = 16,		///< RSPI0 (アイドル割り込み)
			SPEI0,			///< RSPI0 (エラー割り込み)
			SPII1,			///< RSPI1 (アイドル割り込み)
			SPEI1,			///< RSPI1 (エラー割り込み)
			SPII2,			///< RSPI2 (アイドル割り込み)
			SPEI2,			///< RSPI2 (エラー割り込み)

			SPII = 22,		///< RSPIA0 (アイドル割り込み)
			SPEI,			///< RSPIA0 (エラー割り込み)

			RTEI10 = 24,	///< RSCI10 (送信完了/コンディション生成完了)
			RERI10,			///< RSCI10 (受信エラー )
			RBFD10,			///< RSCI10 (Breakフィールド検出)

			RTEI11 = 27,	///< RSCI11 (送信完了/コンディション生成完了)
			RERI11,			///< RSCI11 (受信エラー )
			RBFD11,			///< RSCI11 (Breakフィールド検出)

			QERI = 30,		///< QSPIX (ROMアクセスエラー )

			NUM_ = 19
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL1・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUPAL1 : uint8_t {
			TEI = 12,		///< RIICHS0 (送信完了)
			EEI,			///< RIICHS0 (通信エラー /通信イベント)

			NUM_ = 2
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {

			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		割り込みベクター
				@return IR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) {
				auto idx = static_cast<uint8_t>(vec);
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		static inline ir_t<0x0008'7000> IR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ier_t {

			//-------------------------------------------------------------//
			/*!
				@brief  許可、不許可
				@param[in]	vec		割り込みベクター
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
				@param[in]	vec		割り込みベクター
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
		static inline ier_t<0x0008'7200> IER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IPR レジスタ @n
					全て、下位４ビットが有効
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
			volatile uint8_t& operator [] (VECTOR vec) noexcept {
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
				case VECTOR::CMWI0:  idx = 6; break;
				case VECTOR::CMWI1:  idx = 7; break;

				default: idx = static_cast<uint32_t>(vec); break;
				}
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		static inline ipr_t<0x0008'7300> IPR;

		/// @brief ソフトウェア割り込み 2 起動レジスタ (SWINT2R)
		static inline SWINT2R_ SWINT2R;

		/// @brief DTC 転送要求許可レジスタ  (DTCER)
		static inline dtcer_t<0x0008'7100, VECTOR> DTCER;

		/// @brief DMAC 起動要因選択レジスタ m (DMRSRm) (m = DMAC チャネル番号 )
		static inline DMRSR8N_ DMRSR;
		static inline DMRSR0_ DMRSR0;
		static inline DMRSR1_ DMRSR1;
		static inline DMRSR2_ DMRSR2;
		static inline DMRSR3_ DMRSR3;
		static inline DMRSR4_ DMRSR4;
		static inline DMRSR5_ DMRSR5;
		static inline DMRSR6_ DMRSR6;
		static inline DMRSR7_ DMRSR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求レジスタ（GRPBE0）@n
					グループ BL0/1 割り込み要求レジスタ（GRPBL0/GRPBL1）@n
					グループ AL0/1 割り込み要求レジスタ（GRPAL0/GRPAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline grp_t<0x0008'7600, GROUPBE0> GRPBE0;
		static inline grp_t<0x0008'7630, GROUPBL0> GRPBL0;
		static inline grp_t<0x0008'7634, GROUPBL1> GRPBL1;
		static inline grp_t<0x0008'7638, GROUPBL2> GRPBL2;
		static inline grp_t<0x0008'7830, GROUPAL0> GRPAL0;
		static inline grp_t<0x0008'7834, GROUPAL1> GRPAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求許可レジスタ（GENBE0）@n
					グループ BL0/1 割り込み要求許可レジスタ（GENBL0/GENBL1/GENBL2）@n
					グループ AL0/1 割り込み要求許可レジスタ（GENAL0/GENAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline gen_t<0x0008'7640, GROUPBE0> GENBE0;
		static inline gen_t<0x0008'7670, GROUPBL0> GENBL0;
		static inline gen_t<0x0008'7674, GROUPBL1> GENBL1;
		static inline gen_t<0x0008'7678, GROUPBL2> GENBL2;
		static inline gen_t<0x0008'7870, GROUPAL0> GENAL0;
		static inline gen_t<0x0008'7874, GROUPAL1> GENAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込みクリアレジスタ（GCRBE0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gcr_t<0x0008'7680, GROUPBE0> GCRBE0_;
		static inline GCRBE0_ GCRBE0;


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
			@brief	選択型割り込み B 要因選択レジスタ（SLIBXR）（n = 128 ～ 143）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline icu_utils::slixr_t<0x00087700, VECTOR, SELECTB> SLIBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要因選択レジスタ n（SLIARn）（n = 208 ～ 255）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline icu_utils::slixr_t<0x00087900, VECTOR, SELECTA> SLIAR;
	};
	typedef icu_t ICU;
}
