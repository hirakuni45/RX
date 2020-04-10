#pragma once
//=====================================================================//
/*!	@file
	@brief	RX651/RX65N グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <typeinfo>
#include "RX600/icu_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ICUA 定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_t_ {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR {
			NONE         = 0,   ///< ベクター０

			BUSERR       = 16,  ///< BSC

			RAMERR       = 18,  ///< RAM

			FIFERR       = 21,  ///< FCU

			FRDYI        = 23,  ///< FCU

			SWINT2       = 26,  // ICU
			SWINT        = 27,  // ICU

			CMI0         = 28,  // CMT0
			CMI1         = 29,  // CMT1
			CMWI0        = 30,  // CMTW0
			CMWI1        = 31,  // CMTW1

			D0FIFO2      = 32,  // USBA
			D1FIFO2      = 33,  // USBA

			D0FIFO0      = 34,  // USB0
			D1FIFO0      = 35,  // USB0

			SPRI0        = 38,  // RSPI0
			SPTI0        = 39,  // RSPI0
			SPRI1        = 40,  // RSPI1
			SPTI1        = 41,  // RSPI1

			SPRI         = 42,  // QSPI
			SPTI         = 43,  // QSPI

			SBFAI        = 44,  // SDHI

			MBFAI        = 45,  // MMCIF

			RIIC_RXI1    = 50,	// RIIC1 RXI
			RIIC_TXI1    = 51,	// RIIC1 TXI
			RIIC_RXI0    = 52,  // RIIC0 RXI
			RIIC_TXI0    = 53,	// RIIC0 TXI
			RIIC_RXI2    = 54,  // RIIC2 RXI
			RIIC_TXI2    = 55,	// RIIC2 TXI

			RXI0         = 58,  // SCI0
			TXI0         = 59,
			RXI1         = 60,  // SCI1
			TXI1         = 61,
			RXI2         = 62,  // SCI2
			TXI2         = 63, 

			IRQ0         = 64,  // ICU
			IRQ1         = 65,
			IRQ2         = 66,
			IRQ3         = 67,
			IRQ4         = 68,
			IRQ5         = 69,
			IRQ6         = 70,
			IRQ7         = 71,
			IRQ8         = 72,
			IRQ9         = 73,
			IRQ10        = 74,
			IRQ11        = 75,
			IRQ12        = 76,
			IRQ13        = 77,
			IRQ14        = 78,
			IRQ15        = 79,

			RXI3         = 80,  // SCI3
			TXI3         = 81,
			RXI4         = 82,  // SCI4
			TXI4         = 83,
			RXI5         = 84,  // SCI5
			TXI5         = 85,
			RXI6         = 86,  // SCI6
			TXI6         = 87,

			LVD1         = 88,  // LVD1
			LVD2         = 89,  // LVD2

			USBR0        = 90,  // USB0

			ALM          = 92,  // RTC
			PRD          = 93,

			IWUNI        = 95,  // IWDT

			WUNI         = 96,  // WDT

			PCDFI        = 97,  // PDC

			RXI7         = 98,  // SCI7
			TXI7         = 99,
			RXI8         = 100, // SCI8
			TXI8         = 101,
			RXI9         = 102, // SCI9
			TXI9         = 103,
			RXI10        = 104, // SCI10
			TXI10        = 105,

			GROUPBE0     = 106,  // ICU
			GROUPBL2     = 107,

			SPRI2        = 108,
			SPTI2        = 109,

			GROUPBL0	 = 110,  // ICU
			GROUPBL1	 = 111,  // ICU
			GROUPAL0	 = 112,  // ICU
			GROUPAL1	 = 113,  // ICU
			RXI11   	 = 114,  // SCI11
			TXI11   	 = 115,

			RXI12   	 = 116,  // SCI12
			TXI12   	 = 117,

			DMAC0I  	 = 120,  // DMAC
			DMAC1I  	 = 121,
			DMAC2I  	 = 122,
			DMAC3I  	 = 123,
			DMAC74I 	 = 124,

			OSTDI    	 = 125,  // OST

			EXDMAC0I 	 = 126,  // EXDMAC
			EXDMAC1I 	 = 127,

			INTB128  	 = 128,
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

			INTA208  = 208,
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
			@brief  選択型割り込みＢ要因・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_SELB {
			CMI2 = 1,	///< CMT2
			CMI3 = 2,	///< CMT3

			RXF0 = 50,	///< CAN0（受信 FIFO 割り込み）
			TXF0 = 51,	///< CAN0（送信 FIFO 割り込み）
			RXM0 = 52,	///< CAN0（メールボックス０～３１メッセージ受信完了）
			TXM0 = 53,	///< CAN0（メールボックス０～３１メッセージ送信完了）
			RXF1 = 54,	///< CAN1（受信 FIFO 割り込み）
			TXF1 = 55,	///< CAN1（送信 FIFO 割り込み）
			RXM1 = 56,	///< CAN1（メールボックス０～３１メッセージ受信完了）
			TXM1 = 57,	///< CAN1（メールボックス０～３１メッセージ送信完了）
			RXF2 = 58,	///< CAN2（受信 FIFO 割り込み）
			TXF2 = 59,	///< CAN2（送信 FIFO 割り込み）
			RXM2 = 60,	///< CAN2（メールボックス０～３１メッセージ受信完了）
			TXM2 = 61,	///< CAN2（メールボックス０～３１メッセージ送信完了）

			USBI0 = 62,	///< USB0（１５要因のステータス割り込み）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込みＡ要因・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_SELA {
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
			TCIV7,		///< MTU7（TCNTのオーバフロー /アンダフロー（相補PWMモード時のみ））

			TGIA8 = 41,	///< MTU8（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB8,		///< MTU8（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC8,		///< MTU8（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID8,		///< MTU8（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV8,		///< MTU8（TCNTのオーバフロー）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBE0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BE0 {
			ERS0,	///< CAN0 / ERS0
			ERS1,	///< CAN1 / ERS1
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BL0 {
			TEI0,	///< SCI0 / TEI0（送信完了）
			ERI0,	///< SCI0 / ERI0（受信エラー）
			TEI1,	///< SCI1 / TEI1（送信完了）
			ERI1,	///< SCI1 / ERI1（受信エラー）
			TEI2,	///< SCI2 / TEI2（送信完了）
			ERI2,	///< SCI2 / ERI2（受信エラー）
			TEI3,	///< SCI3 / TEI3（送信完了）
			ERI3,	///< SCI3 / ERI3（受信エラー）
			TEI4,	///< SCI4 / TEI4（送信完了）
			ERI4,	///< SCI4 / ERI4（受信エラー）
			TEI5,	///< SCI5 / TEI5（送信完了）
			ERI5,	///< SCI5 / ERI5（受信エラー）
			TEI6,	///< SCI6 / TEI6（送信完了）
			ERI6,	///< SCI6 / ERI6（受信エラー）
			TEI7,	///< SCI7 / TEI7（送信完了）
			ERI7,	///< SCI7 / ERI7（受信エラー）
			TEI12,	///< SCI12 / TEI12（送信完了）
			ERI12,	///< SCI12 / ERI12（受信エラー）
			SCIX0,	///< SCI12 / SCIX0
			SCIX1,	///< SCI12 / SCIX1
			SCIX2,	///< SCI12 / SCIX2
			SCIX3,	///< SCI12 / SCIX3

			QSPSSLI = 24,	///< QSPI / QSPSSLI

			FERRI = 26,		///< CAC / FERRI
			MENDI,			///< CAC / MENDI
			OVFI,			///< CAC / OVFI
			DOPCI,			///< DOC / DOPCI
			PCFEI,			///< PDC / PCFEI
			PCERI			///< PDC / PCERI
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL1・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BL1 {
			CDETI = 3,		///< SDHI / CDETI
			CACI,			///< SDHI / CACI
			SDACI,			///< SDHI / SDACI
			CDETIO,			///< MMCIF / CDETIO
			ERRIO,			///< MMCIF / ERRIO
			ACCIO,			///< MMCIF / ACCIO
			OEI1,			///< POE3 / OEI1
			OEI2,			///< POE3 / OEI2
			OEI3,			///< POE3 / OEI3
			OEI4,			///< POE3 / OEI4
			TEI0,			///< RIIC0 / TEI0
			EEI0,			///< RIIC0 / EEI0
			TEI2,			///< RIIC2 / TEI2
			EEI2,			///< RIIC2 / EEI2

			S12CMPAI = 20,	///< S12AD / S12CMPAI
			S12CMPBI,		///< S12AD / S12CMPBI
			S12CMPAI1 = 22,	///< S12AD1 / S12CMPAI1
			S12CMPBI1,		///< S12AD1 / S12CMPBI1
			TEI8,			///< SCI8 / TEI8
			ERI8,			///< SCI8 / ERI8
			TEI9,			///< SCI9 / TEI9
			ERI9,			///< SCI9 / ERI9
			TEI1,			///< RIIC1 / TEI1
			EEI1,			///< RIIC1 / EEI1
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL2・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BL2 {
			SDIOI,			///< SDSI / SDIOI
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_AL0 {
			TEI10 = 8,		///< SCI10 / TEI10
			ERI10,			///< SCI10 / ERI10

			TEI11 = 12,		///< SCI11 / TEI11
			ERI11,			///< SCI11 / ERI11

			SPII0 = 16,		///< RSPI0 / SPII0
			SPEI0,			///< RSPI0 / SPEI0
			SPII2,			///< RSPI2 / SPII2
			SPEI2,			///< RSPI2 / SPEI2
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL1・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_AL1 {
			EINT0 = 4,		///< EDMAC0/EINT0
			EINT1 = 5,		///< EDMAC1/EINT1
			VPOS  = 8,		///< GLCDC/VPOS
			GR1UF,			///< GLCDC/GR1UF
			GR2UF,			///< GLCDC/GR2UF
			DRW_IRQ			///< DRW2D/DRW_IRQ
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクターの取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BL0 ivec) noexcept {
			return VECTOR::GROUPBL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクターの取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BL1 ivec) noexcept {
			return VECTOR::GROUPBL1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクターの取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BL2 ivec) noexcept {
			return VECTOR::GROUPBL2;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクターの取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BE0 ivec) noexcept {
			return VECTOR::GROUPBE0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクターの取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_AL0 ivec) noexcept {
			return VECTOR::GROUPAL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクターの取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_AL1 ivec) noexcept {
			return VECTOR::GROUPAL1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t_ {
			rw8_t<base + 26> SWINT2;
			rw8_t<base + 27> SWINT;

			rw8_t<base + 28> CMI0;
			rw8_t<base + 29> CMI1;
			rw8_t<base + 30> CMWI0;
			rw8_t<base + 31> CMWI1;

			rw8_t<base + 34> D0FIFO0;		///< USB0
			rw8_t<base + 35> D1FIFO0;		///< USB0

			rw8_t<base + 44> SBFAI;			///< SDHI

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

			rw8_t<base + 90> USBR0;

			rw8_t<base + 98> RXI7;
			rw8_t<base + 99> TXI7;
			rw8_t<base + 100> RXI8;
			rw8_t<base + 101> TXI8;
			rw8_t<base + 102> RXI9;
			rw8_t<base + 103> TXI9;
			rw8_t<base + 104> RXI10;
			rw8_t<base + 105> TXI10;

			rw8_t<base + 106> GROUPBE0;
			rw8_t<base + 110> GROUPBL0;
			rw8_t<base + 111> GROUPBL1;
			rw8_t<base + 112> GROUPAL0;
			rw8_t<base + 113> GROUPAL1;
			rw8_t<base + 114> RXI11;
			rw8_t<base + 115> TXI11;

			rw8_t<base + 116> RXI12;
			rw8_t<base + 117> TXI12;

			rw8_t<base + 120> DMAC0I;
			rw8_t<base + 121> DMAC1I;
			rw8_t<base + 122> DMAC2I;
			rw8_t<base + 123> DMAC3I;
			rw8_t<base + 124> DMAC74I;

			rw8_t<base + 128> INTB128;
			rw8_t<base + 129> INTB129;
			rw8_t<base + 130> INTB130;
			rw8_t<base + 131> INTB131;
			rw8_t<base + 132> INTB132;
			rw8_t<base + 133> INTB133;
			rw8_t<base + 134> INTB134;
			rw8_t<base + 135> INTB135;
			rw8_t<base + 136> INTB136;
			rw8_t<base + 137> INTB137;
			rw8_t<base + 138> INTB138;
			rw8_t<base + 139> INTB139;
			rw8_t<base + 140> INTB140;
			rw8_t<base + 141> INTB141;
			rw8_t<base + 142> INTB142;
			rw8_t<base + 143> INTB143;
			rw8_t<base + 144> INTB144;
			rw8_t<base + 145> INTB145;
			rw8_t<base + 146> INTB146;
			rw8_t<base + 147> INTB147;
			rw8_t<base + 148> INTB148;
			rw8_t<base + 149> INTB149;
			rw8_t<base + 150> INTB150;

			rw8_t<base + 208> INTA208;
			rw8_t<base + 209> INTA209;
			rw8_t<base + 210> INTA210;
			rw8_t<base + 211> INTA211;
			rw8_t<base + 212> INTA212;
			rw8_t<base + 213> INTA213;
			rw8_t<base + 214> INTA214;
			rw8_t<base + 215> INTA215;
			rw8_t<base + 216> INTA216;
			rw8_t<base + 217> INTA217;
			rw8_t<base + 218> INTA218;
			rw8_t<base + 219> INTA219;
			rw8_t<base + 220> INTA220;
			rw8_t<base + 221> INTA221;
			rw8_t<base + 222> INTA222;
			rw8_t<base + 223> INTA223;
			rw8_t<base + 224> INTA224;
			rw8_t<base + 225> INTA225;
			rw8_t<base + 226> INTA226;
			rw8_t<base + 227> INTA227;
			rw8_t<base + 228> INTA228;
			rw8_t<base + 229> INTA229;
			rw8_t<base + 230> INTA230;
			rw8_t<base + 231> INTA231;
			rw8_t<base + 232> INTA232;
			rw8_t<base + 233> INTA233;
			rw8_t<base + 234> INTA234;
			rw8_t<base + 235> INTA235;
			rw8_t<base + 236> INTA236;
			rw8_t<base + 237> INTA237;
			rw8_t<base + 238> INTA238;
			rw8_t<base + 239> INTA239;
			rw8_t<base + 240> INTA240;
			rw8_t<base + 241> INTA241;
			rw8_t<base + 242> INTA242;
			rw8_t<base + 243> INTA243;
			rw8_t<base + 244> INTA244;
			rw8_t<base + 245> INTA245;
			rw8_t<base + 246> INTA246;
			rw8_t<base + 247> INTA247;
			rw8_t<base + 248> INTA248;
			rw8_t<base + 249> INTA249;
			rw8_t<base + 250> INTA250;
			rw8_t<base + 251> INTA251;
			rw8_t<base + 252> INTA252;
			rw8_t<base + 253> INTA253;
			rw8_t<base + 254> INTA254;
			rw8_t<base + 255> INTA255;


			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	idx		インデックス（０～２５５）
				@return IR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (uint8_t idx) {
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		typedef ir_t_<0x00087010> ir_t;
		static ir_t IR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ier_t_ {
			typedef rw8_t<base + 0x02> ier02;
			bit_rw_t<ier02, bitpos::B0>	BUSERR;
			bit_rw_t<ier02, bitpos::B5>	FIFERR;
			bit_rw_t<ier02, bitpos::B7>	FRDYI;

			typedef rw8_t<base + 0x03> ier03;
			bit_rw_t<ier03, bitpos::B2>	SWINT2;
			bit_rw_t<ier03, bitpos::B3>	SWINT;
			bit_rw_t<ier03, bitpos::B4>	CMI0;
			bit_rw_t<ier03, bitpos::B5>	CMI1;
			bit_rw_t<ier03, bitpos::B6>	CMWI0;
			bit_rw_t<ier03, bitpos::B7>	CMWI1;

			typedef rw8_t<base + 0x04> ier04;
			bit_rw_t<ier04, bitpos::B2>	D0FIOFO0;
			bit_rw_t<ier04, bitpos::B3>	D1FIOFO0;

			typedef rw8_t<base + 0x05> ier05;
			bit_rw_t<ier05, bitpos::B4>	SBFAI;

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

			typedef rw8_t<base + 0x0B> ier0B;
			bit_rw_t<ier0B, bitpos::B2>	USBR0;

			typedef rw8_t<base + 0x0C> ier0C;
			bit_rw_t<ier0C, bitpos::B2>	RXI7;
			bit_rw_t<ier0C, bitpos::B3>	TXI7;
			bit_rw_t<ier0C, bitpos::B4>	RXI8;
			bit_rw_t<ier0C, bitpos::B5>	TXI8;
			bit_rw_t<ier0C, bitpos::B6>	RXI9;
			bit_rw_t<ier0C, bitpos::B7>	TXI9;

			typedef rw8_t<base + 0x0D> ier0D;
			bit_rw_t<ier0D, bitpos::B0>	RXI10;
			bit_rw_t<ier0D, bitpos::B1>	TXI10;

			bit_rw_t<ier0D, bitpos::B2>	GROUPBE0;
			bit_rw_t<ier0D, bitpos::B3>	GROUPBL2;
			bit_rw_t<ier0D, bitpos::B6>	GROUPBL0;
			bit_rw_t<ier0D, bitpos::B7>	GROUPBL1;

			typedef rw8_t<base + 0x0E> ier0E;
			bit_rw_t<ier0E, bitpos::B0>	GROUPAL0;
			bit_rw_t<ier0E, bitpos::B1> GROUPAL1;
			bit_rw_t<ier0E, bitpos::B2>	RXI11;
			bit_rw_t<ier0E, bitpos::B3>	TXI11;

			bit_rw_t<ier0E, bitpos::B4> RXI12;
			bit_rw_t<ier0E, bitpos::B5> TXI12;

			typedef rw8_t<base + 0x0F> ier0F;
			bit_rw_t<ier0F, bitpos::B0> DMAC0I;
			bit_rw_t<ier0F, bitpos::B1> DMAC1I;
			bit_rw_t<ier0F, bitpos::B2> DMAC2I;
			bit_rw_t<ier0F, bitpos::B3> DMAC3I;
			bit_rw_t<ier0F, bitpos::B4> DMAC74I;

			typedef rw8_t<base + 0x10> ier10;
			bit_rw_t<ier10, bitpos::B0> INTB128;
			bit_rw_t<ier10, bitpos::B1> INTB129;
			bit_rw_t<ier10, bitpos::B2> INTB130;
			bit_rw_t<ier10, bitpos::B3> INTB131;
			bit_rw_t<ier10, bitpos::B4> INTB132;
			bit_rw_t<ier10, bitpos::B5> INTB133;
			bit_rw_t<ier10, bitpos::B6> INTB134;
			bit_rw_t<ier10, bitpos::B7> INTB135;


			typedef rw8_t<base + 0x1A> ier1A;
			bit_rw_t<ier1A, bitpos::B0> INTA208;
			bit_rw_t<ier1A, bitpos::B1> INTA209;
			bit_rw_t<ier1A, bitpos::B2> INTA210;
			bit_rw_t<ier1A, bitpos::B3> INTA211;
			bit_rw_t<ier1A, bitpos::B4> INTA212;
			bit_rw_t<ier1A, bitpos::B5> INTA213;
			bit_rw_t<ier1A, bitpos::B6> INTA214;
			bit_rw_t<ier1A, bitpos::B7> INTA215;
			typedef rw8_t<base + 0x1B> ier1B;
			bit_rw_t<ier1B, bitpos::B0> INTA216;
			bit_rw_t<ier1B, bitpos::B1> INTA217;
			bit_rw_t<ier1B, bitpos::B2> INTA218;
			bit_rw_t<ier1B, bitpos::B3> INTA219;
			bit_rw_t<ier1B, bitpos::B4> INTA220;
			bit_rw_t<ier1B, bitpos::B5> INTA221;
			bit_rw_t<ier1B, bitpos::B6> INTA222;
			bit_rw_t<ier1B, bitpos::B7> INTA223;
			typedef rw8_t<base + 0x1C> ier1C;
			bit_rw_t<ier1C, bitpos::B0> INTA224;
			bit_rw_t<ier1C, bitpos::B1> INTA225;
			bit_rw_t<ier1C, bitpos::B2> INTA226;
			bit_rw_t<ier1C, bitpos::B3> INTA227;
			bit_rw_t<ier1C, bitpos::B4> INTA228;
			bit_rw_t<ier1C, bitpos::B5> INTA229;
			bit_rw_t<ier1C, bitpos::B6> INTA230;
			bit_rw_t<ier1C, bitpos::B7> INTA231;
			typedef rw8_t<base + 0x1D> ier1D;
			bit_rw_t<ier1D, bitpos::B0> INTA232;
			bit_rw_t<ier1D, bitpos::B1> INTA233;
			bit_rw_t<ier1D, bitpos::B2> INTA234;
			bit_rw_t<ier1D, bitpos::B3> INTA235;
			bit_rw_t<ier1D, bitpos::B4> INTA236;
			bit_rw_t<ier1D, bitpos::B5> INTA237;
			bit_rw_t<ier1D, bitpos::B6> INTA238;
			bit_rw_t<ier1D, bitpos::B7> INTA239;
			typedef rw8_t<base + 0x1E> ier1E;
			bit_rw_t<ier1E, bitpos::B0> INTA240;
			bit_rw_t<ier1E, bitpos::B1> INTA241;
			bit_rw_t<ier1E, bitpos::B2> INTA242;
			bit_rw_t<ier1E, bitpos::B3> INTA243;
			bit_rw_t<ier1E, bitpos::B4> INTA244;
			bit_rw_t<ier1E, bitpos::B5> INTA245;
			bit_rw_t<ier1E, bitpos::B6> INTA246;
			bit_rw_t<ier1E, bitpos::B7> INTA247;
			typedef rw8_t<base + 0x1F> ier1F;
			bit_rw_t<ier1F, bitpos::B0> INTA248;
			bit_rw_t<ier1F, bitpos::B1> INTA249;
			bit_rw_t<ier1F, bitpos::B2> INTA250;
			bit_rw_t<ier1F, bitpos::B3> INTA251;
			bit_rw_t<ier1F, bitpos::B4> INTA252;
			bit_rw_t<ier1F, bitpos::B5> INTA253;
			bit_rw_t<ier1F, bitpos::B6> INTA254;
			bit_rw_t<ier1F, bitpos::B7> INTA255;


			//-------------------------------------------------------------//
			/*!
				@brief  許可、不許可
				@param[in]	idx		インデックス（０～２５５）
				@param[in]	ena		許可／不許可
			*/
			//-------------------------------------------------------------//
			void enable(uint8_t idx, bool ena) noexcept
			{
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
				@param[in]	idx		インデックス（０～２５５）
				@return 許可状態（許可の場合「true」）
			*/
			//-------------------------------------------------------------//
			bool get(uint8_t idx) const noexcept
			{
				auto tmp = rd8_(base + (idx >> 3));
				return tmp & (1 << (idx & 7));
			}
		};
		typedef ier_t_<0x00087200> ier_t;
		static ier_t IER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IPR レジスタ @n
					全て、下位４ビットが有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ipr_t_ {
			rw8_t<base + 0> BUSERR;

			rw8_t<base + 3> SWINT2;
			rw8_t<base + 3> SWINT;

			rw8_t<base + 4> CMI0;
			rw8_t<base + 5> CMI1;
			rw8_t<base + 6> CMWI0;
			rw8_t<base + 7> CMWI1;

			rw8_t<base + 34> D0FIFO0;		///< USB0
			rw8_t<base + 35> D1FIFO0;		///< USB0

			rw8_t<base + 44> SBFAI;			///< SDHI

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
			rw8_t<base + 100> RXI8;
			rw8_t<base + 101> TXI8;
			rw8_t<base + 102> RXI9;
			rw8_t<base + 103> TXI9;
			rw8_t<base + 104> RXI10;
			rw8_t<base + 105> TXI10;

			rw8_t<base + 106> GROUPBE0;
			rw8_t<base + 107> GROUPBL2;

			rw8_t<base + 110> GROUPBL0;
			rw8_t<base + 111> GROUPBL1;
			rw8_t<base + 112> GROUPAL0;
			rw8_t<base + 113> GROUPAL1;
			rw8_t<base + 114> RXI11;
			rw8_t<base + 115> TXI11;
			rw8_t<base + 116> RXI12;
			rw8_t<base + 117> TXI12;

			rw8_t<base + 120> DMAC0I;
			rw8_t<base + 121> DMAC1I;
			rw8_t<base + 122> DMAC2I;
			rw8_t<base + 123> DMAC3I;
			rw8_t<base + 124> DMAC74I;

			rw8_t<base + 128> INTB128;
			rw8_t<base + 129> INTB129;
			rw8_t<base + 130> INTB130;
			rw8_t<base + 131> INTB131;
			rw8_t<base + 132> INTB132;
			rw8_t<base + 133> INTB133;
			rw8_t<base + 134> INTB134;
			rw8_t<base + 135> INTB135;
			rw8_t<base + 136> INTB136;
			rw8_t<base + 137> INTB137;
			rw8_t<base + 138> INTB138;
			rw8_t<base + 139> INTB139;
			rw8_t<base + 140> INTB140;
			rw8_t<base + 141> INTB141;
			rw8_t<base + 142> INTB142;
			rw8_t<base + 143> INTB143;
			rw8_t<base + 144> INTB144;
			rw8_t<base + 145> INTB145;
			rw8_t<base + 146> INTB146;
			rw8_t<base + 147> INTB147;
			rw8_t<base + 148> INTB148;
			rw8_t<base + 149> INTB149;
			rw8_t<base + 150> INTB150;

			rw8_t<base + 208> INTA208;
			rw8_t<base + 209> INTA209;
			rw8_t<base + 210> INTA210;
			rw8_t<base + 211> INTA211;
			rw8_t<base + 212> INTA212;
			rw8_t<base + 213> INTA213;
			rw8_t<base + 214> INTA214;
			rw8_t<base + 215> INTA215;
			rw8_t<base + 216> INTA216;
			rw8_t<base + 217> INTA217;
			rw8_t<base + 218> INTA218;
			rw8_t<base + 219> INTA219;
			rw8_t<base + 220> INTA220;
			rw8_t<base + 221> INTA221;
			rw8_t<base + 222> INTA222;
			rw8_t<base + 223> INTA223;
			rw8_t<base + 224> INTA224;
			rw8_t<base + 225> INTA225;
			rw8_t<base + 226> INTA226;
			rw8_t<base + 227> INTA227;
			rw8_t<base + 228> INTA228;
			rw8_t<base + 229> INTA229;
			rw8_t<base + 230> INTA230;
			rw8_t<base + 231> INTA231;
			rw8_t<base + 232> INTA232;
			rw8_t<base + 233> INTA233;
			rw8_t<base + 234> INTA234;
			rw8_t<base + 235> INTA235;
			rw8_t<base + 236> INTA236;
			rw8_t<base + 237> INTA237;
			rw8_t<base + 238> INTA238;
			rw8_t<base + 239> INTA239;
			rw8_t<base + 240> INTA240;
			rw8_t<base + 241> INTA241;
			rw8_t<base + 242> INTA242;
			rw8_t<base + 243> INTA243;
			rw8_t<base + 244> INTA244;
			rw8_t<base + 245> INTA245;
			rw8_t<base + 246> INTA246;
			rw8_t<base + 247> INTA247;
			rw8_t<base + 248> INTA248;
			rw8_t<base + 249> INTA249;
			rw8_t<base + 250> INTA250;
			rw8_t<base + 251> INTA251;
			rw8_t<base + 252> INTA252;
			rw8_t<base + 253> INTA253;
			rw8_t<base + 254> INTA254;
			rw8_t<base + 255> INTA255;


			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	idx		インデックス（０～２５５）
				@return IR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (uint8_t idx) {
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		typedef ipr_t_<0x00087300> ipr_t;
		static ipr_t IPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因選択レジスタ m（DMRSRm）（m = DMAC チャネル番号）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087400> dmrsr0_t;
		static dmrsr0_t DMRSR0;
		typedef rw8_t<0x00087404> dmrsr1_t;
		static dmrsr1_t DMRSR1;
		typedef rw8_t<0x00087408> dmrsr2_t;
		static dmrsr2_t DMRSR2;
		typedef rw8_t<0x0008740C> dmrsr3_t;
		static dmrsr3_t DMRSR3;
		typedef rw8_t<0x00087410> dmrsr4_t;
		static dmrsr4_t DMRSR4;
		typedef rw8_t<0x00087414> dmrsr5_t;
		static dmrsr5_t DMRSR5;
		typedef rw8_t<0x00087418> dmrsr6_t;
		static dmrsr6_t DMRSR6;
		typedef rw8_t<0x0008741C> dmrsr7_t;
		static dmrsr7_t DMRSR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ コントロールレジスタ i（IRQCRi）（i = 0 ～ 15）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B2, 2>  IRQMD;
		};
		typedef irqcr_t_<0x00087500> irqcr0_t;
		static irqcr0_t IRQCR0;
		typedef irqcr_t_<0x00087501> irqcr1_t;
		static irqcr1_t IRQCR1;
		typedef irqcr_t_<0x00087502> irqcr2_t;
		static irqcr2_t IRQCR2;
		typedef irqcr_t_<0x00087503> irqcr3_t;
		static irqcr3_t IRQCR3;
		typedef irqcr_t_<0x00087504> irqcr4_t;
		static irqcr4_t IRQCR4;
		typedef irqcr_t_<0x00087505> irqcr5_t;
		static irqcr5_t IRQCR5;
		typedef irqcr_t_<0x00087506> irqcr6_t;
		static irqcr6_t IRQCR6;
		typedef irqcr_t_<0x00087507> irqcr7_t;
		static irqcr7_t IRQCR7;
		typedef irqcr_t_<0x00087508> irqcr8_t;
		static irqcr8_t IRQCR8;
		typedef irqcr_t_<0x00087509> irqcr9_t;
		static irqcr9_t IRQCR9;
		typedef irqcr_t_<0x0008750A> irqcr10_t;
		static irqcr10_t IRQCR10;
		typedef irqcr_t_<0x0008750B> irqcr11_t;
		static irqcr11_t IRQCR11;
		typedef irqcr_t_<0x0008750C> irqcr12_t;
		static irqcr12_t IRQCR12;
		typedef irqcr_t_<0x0008750D> irqcr13_t;
		static irqcr13_t IRQCR13;
		typedef irqcr_t_<0x0008750E> irqcr14_t;
		static irqcr14_t IRQCR14;
		typedef irqcr_t_<0x0008750F> irqcr15_t;
		static irqcr15_t IRQCR15;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 0（IRQFLTE0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte0_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> FLTEN0;
			bit_rw_t<io_, bitpos::B1> FLTEN1;
			bit_rw_t<io_, bitpos::B2> FLTEN2;
			bit_rw_t<io_, bitpos::B3> FLTEN3;
			bit_rw_t<io_, bitpos::B4> FLTEN4;
			bit_rw_t<io_, bitpos::B5> FLTEN5;
			bit_rw_t<io_, bitpos::B6> FLTEN6;
			bit_rw_t<io_, bitpos::B7> FLTEN7;
		};
		typedef irqflte0_t_<0x00087520> irqflte0_t;
		static irqflte0_t IRQFLTE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 1（IRQFLTE1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte1_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> FLTEN8;
			bit_rw_t<io_, bitpos::B1> FLTEN9;
			bit_rw_t<io_, bitpos::B2> FLTEN10;
			bit_rw_t<io_, bitpos::B3> FLTEN11;
			bit_rw_t<io_, bitpos::B4> FLTEN12;
			bit_rw_t<io_, bitpos::B5> FLTEN13;
			bit_rw_t<io_, bitpos::B6> FLTEN14;
			bit_rw_t<io_, bitpos::B7> FLTEN15;
		};
		typedef irqflte1_t_<0x00087521> irqflte1_t;
		static irqflte1_t IRQFLTE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 0（IRQFLTC0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc0_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> FCLKSEL0;
			bits_rw_t<io_, bitpos::B2,  2> FCLKSEL1;
			bits_rw_t<io_, bitpos::B4,  2> FCLKSEL2;
			bits_rw_t<io_, bitpos::B6,  2> FCLKSEL3;
			bits_rw_t<io_, bitpos::B8,  2> FCLKSEL4;
			bits_rw_t<io_, bitpos::B10, 2> FCLKSEL5;
			bits_rw_t<io_, bitpos::B12, 2> FCLKSEL6;
			bits_rw_t<io_, bitpos::B14, 2> FCLKSEL7;
		};
		typedef irqfltc0_t_<0x00087528> irqfltc0_t;
		static irqfltc0_t IRQFLTC0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 1（IRQFLTC1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc1_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> FCLKSEL8;
			bits_rw_t<io_, bitpos::B2,  2> FCLKSEL9;
			bits_rw_t<io_, bitpos::B4,  2> FCLKSEL10;
			bits_rw_t<io_, bitpos::B6,  2> FCLKSEL11;
			bits_rw_t<io_, bitpos::B8,  2> FCLKSEL12;
			bits_rw_t<io_, bitpos::B10, 2> FCLKSEL13;
			bits_rw_t<io_, bitpos::B12, 2> FCLKSEL14;
			bits_rw_t<io_, bitpos::B14, 2> FCLKSEL15;
		};
		typedef irqfltc1_t_<0x0008752A> irqfltc1_t;
		static irqfltc1_t IRQFLTC1;


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
		typedef grp_t<0x00087600> grpbe0_t;
		static grpbe0_t GRPBE0;
		typedef grp_t<0x00087630> grpbl0_t;
		static grpbl0_t GRPBL0;
		typedef grp_t<0x00087634> grpbl1_t;
		static grpbl1_t GRPBL1;
		typedef grp_t<0x00087638> grpbl2_t;
		static grpbl2_t GRPBL2;
		typedef grp_t<0x00087830> grpal0_t;
		static grpal0_t GRPAL0;
		typedef grp_t<0x00087834> grpal1_t;
		static grpal1_t GRPAL1;


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
		typedef gen_t<0x00087640> genbe0_t;
		static genbe0_t GENBE0;
		typedef gen_t<0x00087670> genbl0_t;
		static genbl0_t GENBL0;
		typedef gen_t<0x00087674> genbl1_t;
		static genbl1_t GENBL1;
		typedef gen_t<0x00087678> genbl2_t;
		static genbl2_t GENBL2;
		typedef gen_t<0x00087870> genal0_t;
		static genal0_t GENAL0;
		typedef gen_t<0x00087874> genal1_t;
		static genal1_t GENAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込みクリアレジスタ（GCRBE0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct gcrbe0_t_ : public rw32_t<base> {
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
		typedef gcrbe0_t_<0x00087680> gcrbe0_t;
		static gcrbe0_t GCRBE0;


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
		typedef pixr_t<0x00087700> pibr0_t;
		static pibr0_t PIBR0;
		typedef pixr_t<0x00087701> pibr1_t;
		static pibr1_t PIBR1;
		typedef pixr_t<0x00087702> pibr2_t;
		static pibr2_t PIBR2;
		typedef pixr_t<0x00087703> pibr3_t;
		static pibr3_t PIBR3;
		typedef pixr_t<0x00087704> pibr4_t;
		static pibr4_t PIBR4;
		typedef pixr_t<0x00087705> pibr5_t;
		static pibr5_t PIBR5;
		typedef pixr_t<0x00087706> pibr6_t;
		static pibr6_t PIBR6;
		typedef pixr_t<0x00087707> pibr7_t;
		static pibr7_t PIBR7;
		typedef pixr_t<0x00087708> pibr8_t;
		static pibr8_t PIBR8;
		typedef pixr_t<0x00087709> pibr9_t;
		static pibr9_t PIBR9;
		typedef pixr_t<0x0008770A> pibra_t;
		static pibra_t PIBRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要求レジスタ k（PIARk）（k = 0h ～ Bh）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pixr_t<0x00087900> piar0_t;
		static piar0_t PIAR0;
		typedef pixr_t<0x00087901> piar1_t;
		static piar1_t PIAR1;
		typedef pixr_t<0x00087902> piar2_t;
		static piar2_t PIAR2;
		typedef pixr_t<0x00087903> piar3_t;
		static piar3_t PIAR3;
		typedef pixr_t<0x00087904> piar4_t;
		static piar4_t PIAR4;
		typedef pixr_t<0x00087905> piar5_t;
		static piar5_t PIAR5;
		typedef pixr_t<0x00087906> piar6_t;
		static piar6_t PIAR6;
		typedef pixr_t<0x00087907> piar7_t;
		static piar7_t PIAR7;
		typedef pixr_t<0x00087908> piar8_t;
		static piar8_t PIAR8;
		typedef pixr_t<0x00087909> piar9_t;
		static piar9_t PIAR9;
		typedef pixr_t<0x0008790A> piara_t;
		static piara_t PIARA;
		typedef pixr_t<0x0008790B> piarb_t;
		static piarb_t PIARB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み B 要因選択レジスタ Xn（SLIBXRn）（n = 128 ～ 143）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087780> slibxr128_t;
		static slibxr128_t SLIBXR128;
		typedef rw8_t<0x00087781> slibxr129_t;
		static slibxr129_t SLIBXR129;
		typedef rw8_t<0x00087782> slibxr130_t;
		static slibxr130_t SLIBXR130;
		typedef rw8_t<0x00087783> slibxr131_t;
		static slibxr131_t SLIBXR131;
		typedef rw8_t<0x00087784> slibxr132_t;
		static slibxr132_t SLIBXR132;
		typedef rw8_t<0x00087785> slibxr133_t;
		static slibxr133_t SLIBXR133;
		typedef rw8_t<0x00087786> slibxr134_t;
		static slibxr134_t SLIBXR134;
		typedef rw8_t<0x00087787> slibxr135_t;
		static slibxr135_t SLIBXR135;
		typedef rw8_t<0x00087788> slibxr136_t;
		static slibxr136_t SLIBXR136;
		typedef rw8_t<0x00087789> slibxr137_t;
		static slibxr137_t SLIBXR137;
		typedef rw8_t<0x0008778A> slibxr138_t;
		static slibxr138_t SLIBXR138;
		typedef rw8_t<0x0008778B> slibxr139_t;
		static slibxr139_t SLIBXR139;
		typedef rw8_t<0x0008778C> slibxr140_t;
		static slibxr140_t SLIBXR140;
		typedef rw8_t<0x0008778D> slibxr141_t;
		static slibxr141_t SLIBXR141;
		typedef rw8_t<0x0008778E> slibxr142_t;
		static slibxr142_t SLIBXR142;
		typedef rw8_t<0x0008778F> slibxr143_t;
		static slibxr143_t SLIBXR143;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み B 要因選択レジスタ n（SLIBRn）（n = 144 ～ 207）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087790> slibr144_t;
		static slibr144_t SLIBR144;
		typedef rw8_t<0x00087791> slibr145_t;
		static slibr145_t SLIBR145;
		typedef rw8_t<0x00087792> slibr146_t;
		static slibr146_t SLIBR146;
		typedef rw8_t<0x00087793> slibr147_t;
		static slibr147_t SLIBR147;
		typedef rw8_t<0x00087794> slibr148_t;
		static slibr148_t SLIBR148;
		typedef rw8_t<0x00087795> slibr149_t;
		static slibr149_t SLIBR149;
		typedef rw8_t<0x00087796> slibr150_t;
		static slibr150_t SLIBR150;
		typedef rw8_t<0x00087797> slibr151_t;
		static slibr151_t SLIBR151;
		typedef rw8_t<0x00087798> slibr152_t;
		static slibr152_t SLIBR152;
		typedef rw8_t<0x00087799> slibr153_t;
		static slibr153_t SLIBR153;
		typedef rw8_t<0x0008779A> slibr154_t;
		static slibr154_t SLIBR154;
		typedef rw8_t<0x0008779B> slibr155_t;
		static slibr155_t SLIBR155;
		typedef rw8_t<0x0008779C> slibr156_t;
		static slibr156_t SLIBR156;
		typedef rw8_t<0x0008779D> slibr157_t;
		static slibr157_t SLIBR157;
		typedef rw8_t<0x0008779E> slibr158_t;
		static slibr158_t SLIBR158;
		typedef rw8_t<0x0008779F> slibr159_t;
		static slibr159_t SLIBR159;

		typedef rw8_t<0x000877A0> slibr160_t;
		static slibr160_t SLIBR160;
		typedef rw8_t<0x000877A1> slibr161_t;
		static slibr161_t SLIBR161;
		typedef rw8_t<0x000877A2> slibr162_t;
		static slibr162_t SLIBR162;
		typedef rw8_t<0x000877A3> slibr163_t;
		static slibr163_t SLIBR163;
		typedef rw8_t<0x000877A4> slibr164_t;
		static slibr164_t SLIBR164;
		typedef rw8_t<0x000877A5> slibr165_t;
		static slibr165_t SLIBR165;
		typedef rw8_t<0x000877A6> slibr166_t;
		static slibr166_t SLIBR166;
		typedef rw8_t<0x000877A7> slibr167_t;
		static slibr167_t SLIBR167;
		typedef rw8_t<0x000877A8> slibr168_t;
		static slibr168_t SLIBR168;
		typedef rw8_t<0x000877A9> slibr169_t;
		static slibr169_t SLIBR169;
		typedef rw8_t<0x000877AA> slibr170_t;
		static slibr170_t SLIBR170;
		typedef rw8_t<0x000877AB> slibr171_t;
		static slibr171_t SLIBR171;
		typedef rw8_t<0x000877AC> slibr172_t;
		static slibr172_t SLIBR172;
		typedef rw8_t<0x000877AD> slibr173_t;
		static slibr173_t SLIBR173;
		typedef rw8_t<0x000877AE> slibr174_t;
		static slibr174_t SLIBR174;
		typedef rw8_t<0x000877AF> slibr175_t;
		static slibr175_t SLIBR175;

		typedef rw8_t<0x000877B0> slibr176_t;
		static slibr176_t SLIBR176;
		typedef rw8_t<0x000877B1> slibr177_t;
		static slibr177_t SLIBR177;
		typedef rw8_t<0x000877B2> slibr178_t;
		static slibr178_t SLIBR178;
		typedef rw8_t<0x000877B3> slibr179_t;
		static slibr179_t SLIBR179;
		typedef rw8_t<0x000877B4> slibr180_t;
		static slibr180_t SLIBR180;
		typedef rw8_t<0x000877B5> slibr181_t;
		static slibr181_t SLIBR181;
		typedef rw8_t<0x000877B6> slibr182_t;
		static slibr182_t SLIBR182;
		typedef rw8_t<0x000877B7> slibr183_t;
		static slibr183_t SLIBR183;
		typedef rw8_t<0x000877B8> slibr184_t;
		static slibr184_t SLIBR184;
		typedef rw8_t<0x000877B9> slibr185_t;
		static slibr185_t SLIBR185;
		typedef rw8_t<0x000877BA> slibr186_t;
		static slibr186_t SLIBR186;
		typedef rw8_t<0x000877BB> slibr187_t;
		static slibr187_t SLIBR187;
		typedef rw8_t<0x000877BC> slibr188_t;
		static slibr188_t SLIBR188;
		typedef rw8_t<0x000877BD> slibr189_t;
		static slibr189_t SLIBR189;
		typedef rw8_t<0x000877BE> slibr190_t;
		static slibr190_t SLIBR190;
		typedef rw8_t<0x000877BF> slibr191_t;
		static slibr191_t SLIBR191;

		typedef rw8_t<0x000877C0> slibr192_t;
		static slibr192_t SLIBR192;
		typedef rw8_t<0x000877C1> slibr193_t;
		static slibr193_t SLIBR193;
		typedef rw8_t<0x000877C2> slibr194_t;
		static slibr194_t SLIBR194;
		typedef rw8_t<0x000877C3> slibr195_t;
		static slibr195_t SLIBR195;
		typedef rw8_t<0x000877C4> slibr196_t;
		static slibr196_t SLIBR196;
		typedef rw8_t<0x000877C5> slibr197_t;
		static slibr197_t SLIBR197;
		typedef rw8_t<0x000877C6> slibr198_t;
		static slibr198_t SLIBR198;
		typedef rw8_t<0x000877C7> slibr199_t;
		static slibr199_t SLIBR199;
		typedef rw8_t<0x000877C8> slibr200_t;
		static slibr200_t SLIBR200;
		typedef rw8_t<0x000877C9> slibr201_t;
		static slibr201_t SLIBR201;
		typedef rw8_t<0x000877CA> slibr202_t;
		static slibr202_t SLIBR202;
		typedef rw8_t<0x000877CB> slibr203_t;
		static slibr203_t SLIBR203;
		typedef rw8_t<0x000877CC> slibr204_t;
		static slibr204_t SLIBR204;
		typedef rw8_t<0x000877CD> slibr205_t;
		static slibr205_t SLIBR205;
		typedef rw8_t<0x000877CE> slibr206_t;
		static slibr206_t SLIBR206;
		typedef rw8_t<0x000877CF> slibr207_t;
		static slibr207_t SLIBR207;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要因選択レジスタ n（SLIARn）（n = 208 ～ 255）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000879D0> sliar208_t;
		static sliar208_t SLIAR208;
		typedef rw8_t<0x000879D1> sliar209_t;
		static sliar209_t SLIAR209;
		typedef rw8_t<0x000879D2> sliar210_t;
		static sliar210_t SLIAR210;
		typedef rw8_t<0x000879D3> sliar211_t;
		static sliar211_t SLIAR211;
		typedef rw8_t<0x000879D4> sliar212_t;
		static sliar212_t SLIAR212;
		typedef rw8_t<0x000879D5> sliar213_t;
		static sliar213_t SLIAR213;
		typedef rw8_t<0x000879D6> sliar214_t;
		static sliar214_t SLIAR214;
		typedef rw8_t<0x000879D7> sliar215_t;
		static sliar215_t SLIAR215;
		typedef rw8_t<0x000879D8> sliar216_t;
		static sliar216_t SLIAR216;
		typedef rw8_t<0x000879D9> sliar217_t;
		static sliar217_t SLIAR217;
		typedef rw8_t<0x000879DA> sliar218_t;
		static sliar218_t SLIAR218;
		typedef rw8_t<0x000879DB> sliar219_t;
		static sliar219_t SLIAR219;
		typedef rw8_t<0x000879DC> sliar220_t;
		static sliar220_t SLIAR220;
		typedef rw8_t<0x000879DD> sliar221_t;
		static sliar221_t SLIAR221;
		typedef rw8_t<0x000879DE> sliar222_t;
		static sliar222_t SLIAR222;
		typedef rw8_t<0x000879DF> sliar223_t;
		static sliar223_t SLIAR223;

		typedef rw8_t<0x000879E0> sliar224_t;
		static sliar224_t SLIAR224;
		typedef rw8_t<0x000879E1> sliar225_t;
		static sliar225_t SLIAR225;
		typedef rw8_t<0x000879E2> sliar226_t;
		static sliar226_t SLIAR226;
		typedef rw8_t<0x000879E3> sliar227_t;
		static sliar227_t SLIAR227;
		typedef rw8_t<0x000879E4> sliar228_t;
		static sliar228_t SLIAR228;
		typedef rw8_t<0x000879E5> sliar229_t;
		static sliar229_t SLIAR229;
		typedef rw8_t<0x000879E6> sliar230_t;
		static sliar230_t SLIAR230;
		typedef rw8_t<0x000879E7> sliar231_t;
		static sliar231_t SLIAR231;
		typedef rw8_t<0x000879E8> sliar232_t;
		static sliar232_t SLIAR232;
		typedef rw8_t<0x000879E9> sliar233_t;
		static sliar233_t SLIAR233;
		typedef rw8_t<0x000879EA> sliar234_t;
		static sliar234_t SLIAR234;
		typedef rw8_t<0x000879EB> sliar235_t;
		static sliar235_t SLIAR235;
		typedef rw8_t<0x000879EC> sliar236_t;
		static sliar236_t SLIAR236;
		typedef rw8_t<0x000879ED> sliar237_t;
		static sliar237_t SLIAR237;
		typedef rw8_t<0x000879EE> sliar238_t;
		static sliar238_t SLIAR238;
		typedef rw8_t<0x000879EF> sliar239_t;
		static sliar239_t SLIAR239;

		typedef rw8_t<0x000879F0> sliar240_t;
		static sliar240_t SLIAR240;
		typedef rw8_t<0x000879F1> sliar241_t;
		static sliar241_t SLIAR241;
		typedef rw8_t<0x000879F2> sliar242_t;
		static sliar242_t SLIAR242;
		typedef rw8_t<0x000879F3> sliar243_t;
		static sliar243_t SLIAR243;
		typedef rw8_t<0x000879F4> sliar244_t;
		static sliar244_t SLIAR244;
		typedef rw8_t<0x000879F5> sliar245_t;
		static sliar245_t SLIAR245;
		typedef rw8_t<0x000879F6> sliar246_t;
		static sliar246_t SLIAR246;
		typedef rw8_t<0x000879F7> sliar247_t;
		static sliar247_t SLIAR247;
		typedef rw8_t<0x000879F8> sliar248_t;
		static sliar248_t SLIAR248;
		typedef rw8_t<0x000879F9> sliar249_t;
		static sliar249_t SLIAR249;
		typedef rw8_t<0x000879FA> sliar250_t;
		static sliar250_t SLIAR250;
		typedef rw8_t<0x000879FB> sliar251_t;
		static sliar251_t SLIAR251;
		typedef rw8_t<0x000879FC> sliar252_t;
		static sliar252_t SLIAR252;
		typedef rw8_t<0x000879FD> sliar253_t;
		static sliar253_t SLIAR253;
		typedef rw8_t<0x000879FE> sliar254_t;
		static sliar254_t SLIAR254;
		typedef rw8_t<0x000879FF> sliar255_t;
		static sliar255_t SLIAR255;

		typedef icu_utils::slixr_t<0x00087700> slixr_t;
		static slixr_t SLIXR;
	};
	typedef icu_t_<void> ICU;
	typedef icu_t_<void> icu_t;
	template<class _> typename icu_t_<_>::ir_t         icu_t_<_>::IR;
	template<class _> typename icu_t_<_>:: ier_t       icu_t_<_>::IER;
	template<class _> typename icu_t_<_>:: ipr_t       icu_t_<_>::IPR;
	template<class _> typename icu_t_<_>:: dmrsr0_t    icu_t_<_>::DMRSR0;
	template<class _> typename icu_t_<_>:: dmrsr1_t    icu_t_<_>::DMRSR1;
	template<class _> typename icu_t_<_>:: dmrsr2_t    icu_t_<_>::DMRSR2;
	template<class _> typename icu_t_<_>:: dmrsr3_t    icu_t_<_>::DMRSR3;
	template<class _> typename icu_t_<_>:: dmrsr4_t    icu_t_<_>::DMRSR4;
	template<class _> typename icu_t_<_>:: dmrsr5_t    icu_t_<_>::DMRSR5;
	template<class _> typename icu_t_<_>:: dmrsr6_t    icu_t_<_>::DMRSR6;
	template<class _> typename icu_t_<_>:: dmrsr7_t    icu_t_<_>::DMRSR7;
	template<class _> typename icu_t_<_>:: irqcr0_t  icu_t_<_>::IRQCR0;
	template<class _> typename icu_t_<_>:: irqcr1_t  icu_t_<_>::IRQCR1;
	template<class _> typename icu_t_<_>:: irqcr2_t  icu_t_<_>::IRQCR2;
	template<class _> typename icu_t_<_>:: irqcr3_t  icu_t_<_>::IRQCR3;
	template<class _> typename icu_t_<_>:: irqcr4_t  icu_t_<_>::IRQCR4;
	template<class _> typename icu_t_<_>:: irqcr5_t  icu_t_<_>::IRQCR5;
	template<class _> typename icu_t_<_>:: irqcr6_t  icu_t_<_>::IRQCR6;
	template<class _> typename icu_t_<_>:: irqcr7_t  icu_t_<_>::IRQCR7;
	template<class _> typename icu_t_<_>:: irqcr8_t  icu_t_<_>::IRQCR8;
	template<class _> typename icu_t_<_>:: irqcr9_t  icu_t_<_>::IRQCR9;
	template<class _> typename icu_t_<_>:: irqcr10_t icu_t_<_>::IRQCR10;
	template<class _> typename icu_t_<_>:: irqcr11_t icu_t_<_>::IRQCR11;
	template<class _> typename icu_t_<_>:: irqcr12_t icu_t_<_>::IRQCR12;
	template<class _> typename icu_t_<_>:: irqcr13_t icu_t_<_>::IRQCR13;
	template<class _> typename icu_t_<_>:: irqcr14_t icu_t_<_>::IRQCR14;
	template<class _> typename icu_t_<_>:: irqcr15_t icu_t_<_>::IRQCR15;
	template<class _> typename icu_t_<_>:: irqflte0_t  icu_t_<_>::IRQFLTE0;
	template<class _> typename icu_t_<_>:: irqflte1_t  icu_t_<_>::IRQFLTE1;
	template<class _> typename icu_t_<_>:: irqfltc0_t  icu_t_<_>::IRQFLTC0;
	template<class _> typename icu_t_<_>:: irqfltc1_t  icu_t_<_>::IRQFLTC1;
	template<class _> typename icu_t_<_>:: grpbe0_t    icu_t_<_>::GRPBE0;
	template<class _> typename icu_t_<_>:: grpbl0_t    icu_t_<_>::GRPBL0;
	template<class _> typename icu_t_<_>:: grpbl1_t    icu_t_<_>::GRPBL1;
	template<class _> typename icu_t_<_>:: grpbl2_t    icu_t_<_>::GRPBL2;
	template<class _> typename icu_t_<_>:: grpal0_t    icu_t_<_>::GRPAL0;
	template<class _> typename icu_t_<_>:: grpal1_t    icu_t_<_>::GRPAL1;
	template<class _> typename icu_t_<_>:: genbe0_t    icu_t_<_>::GENBE0;
	template<class _> typename icu_t_<_>:: genbl0_t    icu_t_<_>::GENBL0;
	template<class _> typename icu_t_<_>:: genbl1_t    icu_t_<_>::GENBL1;
	template<class _> typename icu_t_<_>:: genbl2_t    icu_t_<_>::GENBL2;
	template<class _> typename icu_t_<_>:: genal0_t    icu_t_<_>::GENAL0;
	template<class _> typename icu_t_<_>:: genal1_t    icu_t_<_>::GENAL1;
	template<class _> typename icu_t_<_>:: gcrbe0_t    icu_t_<_>::GCRBE0;
	template<class _> typename icu_t_<_>:: pibr0_t     icu_t_<_>::PIBR0;
	template<class _> typename icu_t_<_>:: pibr1_t     icu_t_<_>::PIBR1;
	template<class _> typename icu_t_<_>:: pibr2_t     icu_t_<_>::PIBR2;
	template<class _> typename icu_t_<_>:: pibr3_t     icu_t_<_>::PIBR3;
	template<class _> typename icu_t_<_>:: pibr4_t     icu_t_<_>::PIBR4;
	template<class _> typename icu_t_<_>:: pibr5_t     icu_t_<_>::PIBR5;
	template<class _> typename icu_t_<_>:: pibr6_t     icu_t_<_>::PIBR6;
	template<class _> typename icu_t_<_>:: pibr7_t     icu_t_<_>::PIBR7;
	template<class _> typename icu_t_<_>:: pibr8_t     icu_t_<_>::PIBR8;
	template<class _> typename icu_t_<_>:: pibr9_t     icu_t_<_>::PIBR9;
	template<class _> typename icu_t_<_>:: pibra_t     icu_t_<_>::PIBRA;
	template<class _> typename icu_t_<_>:: piar0_t     icu_t_<_>::PIAR0;
	template<class _> typename icu_t_<_>:: piar1_t     icu_t_<_>::PIAR1;
	template<class _> typename icu_t_<_>:: piar2_t     icu_t_<_>::PIAR2;
	template<class _> typename icu_t_<_>:: piar3_t     icu_t_<_>::PIAR3;
	template<class _> typename icu_t_<_>:: piar4_t     icu_t_<_>::PIAR4;
	template<class _> typename icu_t_<_>:: piar5_t     icu_t_<_>::PIAR5;
	template<class _> typename icu_t_<_>:: piar6_t     icu_t_<_>::PIAR6;
	template<class _> typename icu_t_<_>:: piar7_t     icu_t_<_>::PIAR7;
	template<class _> typename icu_t_<_>:: piar8_t     icu_t_<_>::PIAR8;
	template<class _> typename icu_t_<_>:: piar9_t     icu_t_<_>::PIAR9;
	template<class _> typename icu_t_<_>:: piara_t     icu_t_<_>::PIARA;
	template<class _> typename icu_t_<_>:: piarb_t     icu_t_<_>::PIARB;
	template<class _> typename icu_t_<_>:: slibxr128_t icu_t_<_>::SLIBXR128;
	template<class _> typename icu_t_<_>:: slibxr129_t icu_t_<_>::SLIBXR129;
	template<class _> typename icu_t_<_>:: slibxr130_t icu_t_<_>::SLIBXR130;
	template<class _> typename icu_t_<_>:: slibxr131_t icu_t_<_>::SLIBXR131;
	template<class _> typename icu_t_<_>:: slibxr132_t icu_t_<_>::SLIBXR132;
	template<class _> typename icu_t_<_>:: slibxr133_t icu_t_<_>::SLIBXR133;
	template<class _> typename icu_t_<_>:: slibxr134_t icu_t_<_>::SLIBXR134;
	template<class _> typename icu_t_<_>:: slibxr135_t icu_t_<_>::SLIBXR135;
	template<class _> typename icu_t_<_>:: slibxr136_t icu_t_<_>::SLIBXR136;
	template<class _> typename icu_t_<_>:: slibxr137_t icu_t_<_>::SLIBXR137;
	template<class _> typename icu_t_<_>:: slibxr138_t icu_t_<_>::SLIBXR138;
	template<class _> typename icu_t_<_>:: slibxr139_t icu_t_<_>::SLIBXR139;
	template<class _> typename icu_t_<_>:: slibxr140_t icu_t_<_>::SLIBXR140;
	template<class _> typename icu_t_<_>:: slibxr141_t icu_t_<_>::SLIBXR141;
	template<class _> typename icu_t_<_>:: slibxr142_t icu_t_<_>::SLIBXR142;
	template<class _> typename icu_t_<_>:: slibxr143_t icu_t_<_>::SLIBXR143;
	template<class _> typename icu_t_<_>:: slibr144_t  icu_t_<_>::SLIBR144;
	template<class _> typename icu_t_<_>:: slibr145_t  icu_t_<_>::SLIBR145;
	template<class _> typename icu_t_<_>:: slibr146_t  icu_t_<_>::SLIBR146;
	template<class _> typename icu_t_<_>:: slibr147_t  icu_t_<_>::SLIBR147;
	template<class _> typename icu_t_<_>:: slibr148_t  icu_t_<_>::SLIBR148;
	template<class _> typename icu_t_<_>:: slibr149_t  icu_t_<_>::SLIBR149;
	template<class _> typename icu_t_<_>:: slibr150_t  icu_t_<_>::SLIBR150;
	template<class _> typename icu_t_<_>:: slibr151_t  icu_t_<_>::SLIBR151;
	template<class _> typename icu_t_<_>:: slibr152_t  icu_t_<_>::SLIBR152;
	template<class _> typename icu_t_<_>:: slibr153_t  icu_t_<_>::SLIBR153;
	template<class _> typename icu_t_<_>:: slibr154_t  icu_t_<_>::SLIBR154;
	template<class _> typename icu_t_<_>:: slibr155_t  icu_t_<_>::SLIBR155;
	template<class _> typename icu_t_<_>:: slibr156_t  icu_t_<_>::SLIBR156;
	template<class _> typename icu_t_<_>:: slibr157_t  icu_t_<_>::SLIBR157;
	template<class _> typename icu_t_<_>:: slibr158_t  icu_t_<_>::SLIBR158;
	template<class _> typename icu_t_<_>:: slibr159_t  icu_t_<_>::SLIBR159;
	template<class _> typename icu_t_<_>:: slibr160_t  icu_t_<_>::SLIBR160;
	template<class _> typename icu_t_<_>:: slibr161_t  icu_t_<_>::SLIBR161;
	template<class _> typename icu_t_<_>:: slibr162_t  icu_t_<_>::SLIBR162;
	template<class _> typename icu_t_<_>:: slibr163_t  icu_t_<_>::SLIBR163;
	template<class _> typename icu_t_<_>:: slibr164_t  icu_t_<_>::SLIBR164;
	template<class _> typename icu_t_<_>:: slibr165_t  icu_t_<_>::SLIBR165;
	template<class _> typename icu_t_<_>:: slibr166_t  icu_t_<_>::SLIBR166;
	template<class _> typename icu_t_<_>:: slibr167_t  icu_t_<_>::SLIBR167;
	template<class _> typename icu_t_<_>:: slibr168_t  icu_t_<_>::SLIBR168;
	template<class _> typename icu_t_<_>:: slibr169_t  icu_t_<_>::SLIBR169;
	template<class _> typename icu_t_<_>:: slibr170_t  icu_t_<_>::SLIBR170;
	template<class _> typename icu_t_<_>:: slibr171_t  icu_t_<_>::SLIBR171;
	template<class _> typename icu_t_<_>:: slibr172_t  icu_t_<_>::SLIBR172;
	template<class _> typename icu_t_<_>:: slibr173_t  icu_t_<_>::SLIBR173;
	template<class _> typename icu_t_<_>:: slibr174_t  icu_t_<_>::SLIBR174;
	template<class _> typename icu_t_<_>:: slibr175_t  icu_t_<_>::SLIBR175;
	template<class _> typename icu_t_<_>:: slibr176_t  icu_t_<_>::SLIBR176;
	template<class _> typename icu_t_<_>:: slibr177_t  icu_t_<_>::SLIBR177;
	template<class _> typename icu_t_<_>:: slibr178_t  icu_t_<_>::SLIBR178;
	template<class _> typename icu_t_<_>:: slibr179_t  icu_t_<_>::SLIBR179;
	template<class _> typename icu_t_<_>:: slibr180_t  icu_t_<_>::SLIBR180;
	template<class _> typename icu_t_<_>:: slibr181_t  icu_t_<_>::SLIBR181;
	template<class _> typename icu_t_<_>:: slibr182_t  icu_t_<_>::SLIBR182;
	template<class _> typename icu_t_<_>:: slibr183_t  icu_t_<_>::SLIBR183;
	template<class _> typename icu_t_<_>:: slibr184_t  icu_t_<_>::SLIBR184;
	template<class _> typename icu_t_<_>:: slibr185_t  icu_t_<_>::SLIBR185;
	template<class _> typename icu_t_<_>:: slibr186_t  icu_t_<_>::SLIBR186;
	template<class _> typename icu_t_<_>:: slibr187_t  icu_t_<_>::SLIBR187;
	template<class _> typename icu_t_<_>:: slibr188_t  icu_t_<_>::SLIBR188;
	template<class _> typename icu_t_<_>:: slibr189_t  icu_t_<_>::SLIBR189;
	template<class _> typename icu_t_<_>:: slibr190_t  icu_t_<_>::SLIBR190;
	template<class _> typename icu_t_<_>:: slibr191_t  icu_t_<_>::SLIBR191;
	template<class _> typename icu_t_<_>:: slibr192_t  icu_t_<_>::SLIBR192;
	template<class _> typename icu_t_<_>:: slibr193_t  icu_t_<_>::SLIBR193;
	template<class _> typename icu_t_<_>:: slibr194_t  icu_t_<_>::SLIBR194;
	template<class _> typename icu_t_<_>:: slibr195_t  icu_t_<_>::SLIBR195;
	template<class _> typename icu_t_<_>:: slibr196_t  icu_t_<_>::SLIBR196;
	template<class _> typename icu_t_<_>:: slibr197_t  icu_t_<_>::SLIBR197;
	template<class _> typename icu_t_<_>:: slibr198_t  icu_t_<_>::SLIBR198;
	template<class _> typename icu_t_<_>:: slibr199_t  icu_t_<_>::SLIBR199;
	template<class _> typename icu_t_<_>:: slibr200_t  icu_t_<_>::SLIBR200;
	template<class _> typename icu_t_<_>:: slibr201_t  icu_t_<_>::SLIBR201;
	template<class _> typename icu_t_<_>:: slibr202_t  icu_t_<_>::SLIBR202;
	template<class _> typename icu_t_<_>:: slibr203_t  icu_t_<_>::SLIBR203;
	template<class _> typename icu_t_<_>:: slibr204_t  icu_t_<_>::SLIBR204;
	template<class _> typename icu_t_<_>:: slibr205_t  icu_t_<_>::SLIBR205;
	template<class _> typename icu_t_<_>:: slibr206_t  icu_t_<_>::SLIBR206;
	template<class _> typename icu_t_<_>:: slibr207_t  icu_t_<_>::SLIBR207;
	template<class _> typename icu_t_<_>:: sliar208_t  icu_t_<_>::SLIAR208;
	template<class _> typename icu_t_<_>:: sliar209_t  icu_t_<_>::SLIAR209;
	template<class _> typename icu_t_<_>:: sliar210_t  icu_t_<_>::SLIAR210;
	template<class _> typename icu_t_<_>:: sliar211_t  icu_t_<_>::SLIAR211;
	template<class _> typename icu_t_<_>:: sliar212_t  icu_t_<_>::SLIAR212;
	template<class _> typename icu_t_<_>:: sliar213_t  icu_t_<_>::SLIAR213;
	template<class _> typename icu_t_<_>:: sliar214_t  icu_t_<_>::SLIAR214;
	template<class _> typename icu_t_<_>:: sliar215_t  icu_t_<_>::SLIAR215;
	template<class _> typename icu_t_<_>:: sliar216_t  icu_t_<_>::SLIAR216;
	template<class _> typename icu_t_<_>:: sliar217_t  icu_t_<_>::SLIAR217;
	template<class _> typename icu_t_<_>:: sliar218_t  icu_t_<_>::SLIAR218;
	template<class _> typename icu_t_<_>:: sliar219_t  icu_t_<_>::SLIAR219;
	template<class _> typename icu_t_<_>:: sliar220_t  icu_t_<_>::SLIAR220;
	template<class _> typename icu_t_<_>:: sliar221_t  icu_t_<_>::SLIAR221;
	template<class _> typename icu_t_<_>:: sliar222_t  icu_t_<_>::SLIAR222;
	template<class _> typename icu_t_<_>:: sliar223_t  icu_t_<_>::SLIAR223;
	template<class _> typename icu_t_<_>:: sliar224_t  icu_t_<_>::SLIAR224;
	template<class _> typename icu_t_<_>:: sliar225_t  icu_t_<_>::SLIAR225;
	template<class _> typename icu_t_<_>:: sliar226_t  icu_t_<_>::SLIAR226;
	template<class _> typename icu_t_<_>:: sliar227_t  icu_t_<_>::SLIAR227;
	template<class _> typename icu_t_<_>:: sliar228_t  icu_t_<_>::SLIAR228;
	template<class _> typename icu_t_<_>:: sliar229_t  icu_t_<_>::SLIAR229;
	template<class _> typename icu_t_<_>:: sliar230_t  icu_t_<_>::SLIAR230;
	template<class _> typename icu_t_<_>:: sliar231_t  icu_t_<_>::SLIAR231;
	template<class _> typename icu_t_<_>:: sliar232_t  icu_t_<_>::SLIAR232;
	template<class _> typename icu_t_<_>:: sliar233_t  icu_t_<_>::SLIAR233;
	template<class _> typename icu_t_<_>:: sliar234_t  icu_t_<_>::SLIAR234;
	template<class _> typename icu_t_<_>:: sliar235_t  icu_t_<_>::SLIAR235;
	template<class _> typename icu_t_<_>:: sliar236_t  icu_t_<_>::SLIAR236;
	template<class _> typename icu_t_<_>:: sliar237_t  icu_t_<_>::SLIAR237;
	template<class _> typename icu_t_<_>:: sliar238_t  icu_t_<_>::SLIAR238;
	template<class _> typename icu_t_<_>:: sliar239_t  icu_t_<_>::SLIAR239;
	template<class _> typename icu_t_<_>:: sliar240_t  icu_t_<_>::SLIAR240;
	template<class _> typename icu_t_<_>:: sliar241_t  icu_t_<_>::SLIAR241;
	template<class _> typename icu_t_<_>:: sliar242_t  icu_t_<_>::SLIAR242;
	template<class _> typename icu_t_<_>:: sliar243_t  icu_t_<_>::SLIAR243;
	template<class _> typename icu_t_<_>:: sliar244_t  icu_t_<_>::SLIAR244;
	template<class _> typename icu_t_<_>:: sliar245_t  icu_t_<_>::SLIAR245;
	template<class _> typename icu_t_<_>:: sliar246_t  icu_t_<_>::SLIAR246;
	template<class _> typename icu_t_<_>:: sliar247_t  icu_t_<_>::SLIAR247;
	template<class _> typename icu_t_<_>:: sliar248_t  icu_t_<_>::SLIAR248;
	template<class _> typename icu_t_<_>:: sliar249_t  icu_t_<_>::SLIAR249;
	template<class _> typename icu_t_<_>:: sliar250_t  icu_t_<_>::SLIAR250;
	template<class _> typename icu_t_<_>:: sliar251_t  icu_t_<_>::SLIAR251;
	template<class _> typename icu_t_<_>:: sliar252_t  icu_t_<_>::SLIAR252;
	template<class _> typename icu_t_<_>:: sliar253_t  icu_t_<_>::SLIAR253;
	template<class _> typename icu_t_<_>:: sliar254_t  icu_t_<_>::SLIAR254;
	template<class _> typename icu_t_<_>:: sliar255_t  icu_t_<_>::SLIAR255;
	template<class _> typename icu_t_<_>:: slixr_t     icu_t_<_>::SLIXR;
}
