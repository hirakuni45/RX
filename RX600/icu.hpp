#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/icu_utils.hpp"

#if defined(SIG_RX64M) || defined(SIG_RX71M)
#else  
#  error "icu.hpp requires SIG_RX64M or SIG_RX71M to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みコントローラ（ICUA）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {

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
#if defined(SIG_RX71M)
			SPRI1        = 40,  // RSPI1
			SPTI1        = 41,  // RSPI1
#endif
			SPRI         = 42,  // QSPI
			SPTI         = 43,  // QSPI

			SBFAI        = 44,  // SDHI

			MBFAI        = 45,  // MMCIF
			SSITXI0      = 46,  // SSI0 シリアルサウンドインタフェース
			SSIRXI0      = 47,  // SSI0 シリアルサウンドインタフェース
			SSIRTI1      = 48,  // SSI1 シリアルサウンドインタフェース

			IDEI         = 50,  // SRC
			ODFI         = 51,  // SRC
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
			USBAR        = 94,  // USBA

			IWUNI        = 95,  // IWDT

			WUNI         = 96,  // WDT

			PCDFI        = 97,  // PDC

			RXI7         = 98,  // SCI7
			TXI7         = 99,
			RXIF8        = 100, // SCIFA8
			TXIF8        = 101,
			RXIF9        = 102, // SCIFA9
			TXIF9        = 103,
			RXIF10       = 104, // SCIFA10
			TXIF10       = 105,

			GROUPBE0     = 106,  // ICU

			GROUPBL0	 = 110,  // ICU
			GROUPBL1	 = 111,  // ICU
			GROUPAL0	 = 112,  // ICU
			GROUPAL1	 = 113,  // ICU
			RXIF11  	 = 114,  // SCIFA11
			TXIF11   	 = 115,
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
			NONE = 0,	///< なし

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
			ERS2	///< CAN2 / ERS2
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
			OVFI = 0,		///< SRC / OVFI
			UDFI,			///< SRC / UDFI
			CEFI,			///< SRC / CEFI
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
			SSIF0,			///< SSI0 / SSIF0
			SSIF1,			///< SSI1 / SSIF1

			S12CMPAI = 20,	///< S12AD / S12CMPAI
			S12CMPAI1 = 22,	///< S12AD1 / S12CMPAI1
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_AL0 {
			TEIF8 = 0,		///< SCIFA8 / TEIF8
			ERIF8,			///< SCIFA8 / ERIF8
			BRIF8,			///< SCIFA8 / BRIF8
			DRIF8,			///< SCIFA8 / DRIF8
			TEIF9,			///< SCIFA9 / TEIF9
			ERIF9,			///< SCIFA9 / ERIF9
			BRIF9,			///< SCIFA9 / BRIF9
			DRIF9,			///< SCIFA9 / DRIF9

			TEIF10 = 8,		///< SCIFA10 / TEIF10
			ERIF10,			///< SCIFA10 / ERIF10
			BRIF10,			///< SCIFA10 / BRIF10
			DRIF10,			///< SCIFA10 / DRIF10
			TEIF11,			///< SCIFA11 / TEIF11
			ERIF11,			///< SCIFA11 / ERIF11
			BRIF11,			///< SCIFA11 / BRIF11
			DRIF11,			///< SCIFA11 / DRIF11

			SPII0 = 16,		///< RSPI0 / SPII0
			SPEI0,			///< RSPI0 / SPEI0
			SPII1,			///< RSPI1 / SPII1
			SPEI1,			///< RSPI1 / SPEI1
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL1・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_AL1 {
			MINT = 0,		///< EPTPC / MINT
			PINT,			///< PTPEDMAC / PINT

			EINT0 = 4,		///< EDMAC0/EINT0
			EINT1 = 5,		///< EDMAC1/EINT1
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
		struct ir_t {
			rw8_t<base + 26> SWINT2;
			rw8_t<base + 27> SWINT;

			rw8_t<base + 28> CMI0;
			rw8_t<base + 29> CMI1;
			rw8_t<base + 30> CMWI0;
			rw8_t<base + 31> CMWI1;

			rw8_t<base + 44> SDHI;

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
			rw8_t<base + 100> RXIF8;
			rw8_t<base + 101> TXIF8;
			rw8_t<base + 102> RXIF9;
			rw8_t<base + 103> TXIF9;
			rw8_t<base + 104> RXIF10;
			rw8_t<base + 105> TXIF10;

			rw8_t<base + 106> GROUPBE0;
			rw8_t<base + 110> GROUPBL0;
			rw8_t<base + 111> GROUPBL1;
			rw8_t<base + 112> GROUPAL0;
			rw8_t<base + 113> GROUPAL1;
			rw8_t<base + 114> RXIF11;
			rw8_t<base + 115> TXIF11;

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
			rw8_t<base + 151> INTB151;
			rw8_t<base + 152> INTB152;
			rw8_t<base + 153> INTB153;
			rw8_t<base + 154> INTB154;
			rw8_t<base + 155> INTB155;
			rw8_t<base + 156> INTB156;
			rw8_t<base + 157> INTB157;
			rw8_t<base + 158> INTB158;
			rw8_t<base + 159> INTB159;
			rw8_t<base + 160> INTB160;
			rw8_t<base + 161> INTB161;
			rw8_t<base + 162> INTB162;
			rw8_t<base + 163> INTB163;
			rw8_t<base + 164> INTB164;
			rw8_t<base + 165> INTB165;
			rw8_t<base + 166> INTB166;
			rw8_t<base + 167> INTB167;
			rw8_t<base + 168> INTB168;
			rw8_t<base + 169> INTB169;
			rw8_t<base + 170> INTB170;
			rw8_t<base + 171> INTB171;
			rw8_t<base + 172> INTB172;
			rw8_t<base + 173> INTB173;
			rw8_t<base + 174> INTB174;
			rw8_t<base + 175> INTB175;
			rw8_t<base + 176> INTB176;
			rw8_t<base + 177> INTB177;
			rw8_t<base + 178> INTB178;
			rw8_t<base + 179> INTB179;
			rw8_t<base + 180> INTB180;
			rw8_t<base + 181> INTB181;
			rw8_t<base + 182> INTB182;
			rw8_t<base + 183> INTB183;
			rw8_t<base + 184> INTB184;
			rw8_t<base + 185> INTB185;
			rw8_t<base + 186> INTB186;
			rw8_t<base + 187> INTB187;
			rw8_t<base + 188> INTB188;
			rw8_t<base + 189> INTB189;
			rw8_t<base + 190> INTB190;
			rw8_t<base + 191> INTB191;
			rw8_t<base + 192> INTB192;
			rw8_t<base + 193> INTB193;
			rw8_t<base + 194> INTB194;
			rw8_t<base + 195> INTB195;
			rw8_t<base + 196> INTB196;
			rw8_t<base + 197> INTB197;
			rw8_t<base + 198> INTB198;
			rw8_t<base + 199> INTB199;
			rw8_t<base + 200> INTB200;
			rw8_t<base + 201> INTB201;
			rw8_t<base + 202> INTB202;
			rw8_t<base + 203> INTB203;
			rw8_t<base + 204> INTB204;
			rw8_t<base + 205> INTB205;
			rw8_t<base + 206> INTB206;
			rw8_t<base + 207> INTB207;

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
			bit_rw_t<ier03, bitpos::B2>	SWINT2;
			bit_rw_t<ier03, bitpos::B3>	SWINT;
			bit_rw_t<ier03, bitpos::B4>	CMI0;
			bit_rw_t<ier03, bitpos::B5>	CMI1;
			bit_rw_t<ier03, bitpos::B6>	CMWI0;
			bit_rw_t<ier03, bitpos::B7>	CMWI1;

			typedef rw8_t<base + 0x05> ier05;
			bit_rw_t<ier05, bitpos::B4>	SDHI;

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
			bit_rw_t<ier0C, bitpos::B4>	RXIF8;
			bit_rw_t<ier0C, bitpos::B5>	TXIF8;
			bit_rw_t<ier0C, bitpos::B6>	RXIF9;
			bit_rw_t<ier0C, bitpos::B7>	TXIF9;

			typedef rw8_t<base + 0x0D> ier0D;
			bit_rw_t<ier0D, bitpos::B0>	RXIF10;
			bit_rw_t<ier0D, bitpos::B1>	TXIF10;
			bit_rw_t<ier0D, bitpos::B2>	GROUPBE0;

			bit_rw_t<ier0D, bitpos::B6>	GROUPBL0;
			bit_rw_t<ier0D, bitpos::B7>	GROUPBL1;

			typedef rw8_t<base + 0x0E> ier0E;
			bit_rw_t<ier0E, bitpos::B0>	GROUPAL0;
			bit_rw_t<ier0E, bitpos::B1> GROUPAL1;
			bit_rw_t<ier0E, bitpos::B2>	RXIF11;
			bit_rw_t<ier0E, bitpos::B3>	TXIF11;

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

			rw8_t<base + 3> SWINT2;
			rw8_t<base + 3> SWINT;

			rw8_t<base + 4> CMI0;
			rw8_t<base + 5> CMI1;
			rw8_t<base + 6> CMWI0;
			rw8_t<base + 7> CMWI1;

			rw8_t<base + 44> SDHI;

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
			rw8_t<base + 100> RXIF8;
			rw8_t<base + 101> TXIF8;
			rw8_t<base + 102> RXIF9;
			rw8_t<base + 103> TXIF9;
			rw8_t<base + 104> RXIF10;
			rw8_t<base + 105> TXIF10;
			rw8_t<base + 106> GROUPBE0;

			rw8_t<base + 110> GROUPBL0;
			rw8_t<base + 111> GROUPBL1;
			rw8_t<base + 112> GROUPAL0;
			rw8_t<base + 113> GROUPAL1;
			rw8_t<base + 114> RXIF11;
			rw8_t<base + 115> TXIF11;
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
		static ipr_t<0x00087300> IPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因選択レジスタ m（DMRSRm）（m = DMAC チャネル番号）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x00087400> DMRSR0;
		static rw8_t<0x00087404> DMRSR1;
		static rw8_t<0x00087408> DMRSR2;
		static rw8_t<0x0008740C> DMRSR3;
		static rw8_t<0x00087410> DMRSR4;
		static rw8_t<0x00087414> DMRSR5;
		static rw8_t<0x00087418> DMRSR6;
		static rw8_t<0x0008741C> DMRSR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ コントロールレジスタ i（IRQCRi）（i = 0 ～ 15）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B2, 2>  IRQMD;
		};
		static irqcr_t<0x00087500>  IRQCR0;
		static irqcr_t<0x00087501>  IRQCR1;
		static irqcr_t<0x00087502>  IRQCR2;
		static irqcr_t<0x00087503>  IRQCR3;
		static irqcr_t<0x00087504>  IRQCR4;
		static irqcr_t<0x00087505>  IRQCR5;
		static irqcr_t<0x00087506>  IRQCR6;
		static irqcr_t<0x00087507>  IRQCR7;
		static irqcr_t<0x00087508>  IRQCR8;
		static irqcr_t<0x00087509>  IRQCR9;
		static irqcr_t<0x0008750A>  IRQCR10;
		static irqcr_t<0x0008750B>  IRQCR11;
		static irqcr_t<0x0008750C>  IRQCR12;
		static irqcr_t<0x0008750D>  IRQCR13;
		static irqcr_t<0x0008750E>  IRQCR14;
		static irqcr_t<0x0008750F>  IRQCR15;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 0（IRQFLTE0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte0_t : public rw8_t<base> {
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
		static irqflte0_t<0x00087520> IRQFLTE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 1（IRQFLTE1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte1_t : public rw8_t<base> {
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
		static irqflte1_t<0x00087521> IRQFLTE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 0（IRQFLTC0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc0_t : public rw16_t<base> {
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
		static irqfltc0_t<0x00087528> IRQFLTC0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 1（IRQFLTC1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc1_t : public rw16_t<base> {
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
		static irqfltc1_t<0x0008752A> IRQFLTC1;


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
		static rw8_t<0x00087780> SLIBXR128;
		static rw8_t<0x00087781> SLIBXR129;
		static rw8_t<0x00087782> SLIBXR130;
		static rw8_t<0x00087783> SLIBXR131;
		static rw8_t<0x00087784> SLIBXR132;
		static rw8_t<0x00087785> SLIBXR133;
		static rw8_t<0x00087786> SLIBXR134;
		static rw8_t<0x00087787> SLIBXR135;
		static rw8_t<0x00087788> SLIBXR136;
		static rw8_t<0x00087789> SLIBXR137;
		static rw8_t<0x0008778A> SLIBXR138;
		static rw8_t<0x0008778B> SLIBXR139;
		static rw8_t<0x0008778C> SLIBXR140;
		static rw8_t<0x0008778D> SLIBXR141;
		static rw8_t<0x0008778E> SLIBXR142;
		static rw8_t<0x0008778F> SLIBXR143;


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

		static icu_utils::slixr_t<0x00087700> SLIXR;
	};
	typedef icu_t ICU;
}
