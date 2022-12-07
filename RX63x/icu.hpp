#pragma once
//=============================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・ICUb 定義 @n
			・RIIC の割り込み名は、SCI の割り込み名と重複する為、変更している。 @n
			・Ex: RIIC0 (RXI0  --->  ICRXI0) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "RX600/icu_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX64M/RX71M 割り込みコントローラ・テンプレート・クラス（ICUA）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct icu_t : public ICU_BASE, ICU_IRQ16, ICU_GROUP, ICU_SELECT {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常割り込みベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {

			NONE		= 0,   ///< ベクター０

			BUSERR		= 16,  ///< BSC

			FIFERR		= 21,  ///< FCU

			FRDYI		= 23,  ///< FCU

			SWINT		= 27,  ///< ICU

			CMI0		= 28,  ///< CMT0
			CMI1		= 29,  ///< CMT1
			CMI2		= 30,  ///< CMT2
			CMI3		= 31,  ///< CMT3

			EINT		= 32,	///< Ether

			D0FIFO0		= 33,  ///< USB0
			D1FIFO0		= 34,
			USBI0		= 35,
			D0FIFO1		= 36,  ///< USB1
			D1FIFO1		= 37,
			USBI1		= 38,

			SPRI0		= 39,  ///< RSPI0
			SPTI0		= 40,
			SPII0		= 41,
			SPRI1		= 42,  ///< RSPI1
			SPTI1		= 43,
			SPII1		= 44,
			SPRI2		= 45,  ///< RSPI2
			SPTI2		= 46,
			SPII2		= 47,

			RXF0		= 43,  ///< CAN0
			TXF0		= 44,
			RXM0		= 45,
			TXM0		= 46,
			RXF1		= 47,  ///< CAN1
			TXF1		= 48,
			RXM1		= 49,
			TXM1		= 50,
			RXF2		= 51,  ///< CAN2
			TXF2		= 52,
			RXM2		= 53,
			TXM2		= 54,

			CUP			= 62,	///< RTC

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
			IRQ14		= 78,
			IRQ15		= 79,

			USBR0		= 90,	///< USB
			USBR1		= 91,

			ALM			= 92,	///< RTC
			PRD			= 93,

			ADI0		= 98,	///< AD

			GROUP0		= 106,  ///< ICU
			GROUP1		= 107,
			GROUP2		= 108,
			GROUP3		= 109,
			GROUP4		= 110,
			GROUP5		= 111,
			GROUP6		= 112,

			GROUP12		= 114,	///< ICU

			SCIX0		= 122,  ///< SCI12
			SCIX1		= 123,
			SCIX2		= 124,
			SCIX3		= 125,

			TGI0A		= 126,	///< TPU0
			TGI0B		= 127,
			TGI0C		= 128,
			TGI0D		= 129,
			TGI1A		= 130,	///< TPU1
			TGI1B		= 131,
			TGI2A		= 132,	///< TPU2
			TGI2B		= 133,
			TGI3A		= 134,	///< TPU3
			TGI3B		= 135,
			TGI3C		= 136,
			TGI3D		= 137,
			TGI4A		= 138,	///< TPU4
			TGI4B		= 139,
			TGI5A		= 140,	///< TPU5
			TGI5B		= 141,

			TGI6A		= 142,	///< TPU6
			TGI6B		= 143,
			TGI6C		= 144,
			TGI6D		= 145,
			TGIA0		= 142,  ///< MTU0
			TGIB0		= 143,
			TGIC0		= 144,
			TGID0		= 145,
			TGIE0		= 146,
			TGIF0		= 147,

			TGI7A		= 148,	///< TPU7
			TGI7B		= 149,
			TGIA1		= 148,  ///< MTU1
			TGIB1		= 149,

			TGI8A		= 150,	///< TPU8
			TGI8B		= 151,
			TGIA2		= 150,  ///< MTU2
			TGIB2		= 151,

			TGI9A		= 152,	///< TPU9
			TGI9B		= 153,
			TGI9C		= 154,
			TGI9D		= 155,
			TGIA3		= 152,  ///< MTU3
			TGIB3		= 153,
			TGIC3		= 154,
			TGID3		= 155,

			TGI10A		= 156,	///< TPU10
			TGI10B		= 157,
			TGIA4		= 156,  ///< MTU4
			TGIB4		= 157,
			TGIC4		= 158,
			TGID4		= 159,
			TGIV4		= 160,

			TGIU5		= 161,  ///< MTU5
			TGIV5		= 162,
			TGIW5		= 163,

			TGI11A		= 164,	///< TPU11
			TGI11B		= 165,

			OEI1		= 166,	///< POE
			OEI2		= 167,

			CMIA0		= 170,	///< TMR0
			CMIB0		= 171,
			OVI0		= 172,
			CMIA1		= 173,	///< TMR1
			CMIB1		= 174,
			OVI1		= 175,
			CMIA2		= 176,	///< TMR2
			CMIB2		= 177,
			OVI2		= 178,
			CMIA3		= 179,	///< TMR3
			CMIB3		= 180,
			OVI3		= 181,

			ICEEI0		= 182,  ///< RIIC0
			ICRXI0		= 183,
			ICTXI0		= 184,
			ICTEI0		= 185,
			ICEEI1		= 186,  ///< RIIC1
			ICRXI1		= 187,
			ICTXI1		= 188,
			ICTEI1		= 189,
			ICEEI2		= 190,  ///< RIIC2
			ICRXI2		= 191,
			ICTXI2		= 192,
			ICTEI2		= 193,
			ICEEI3		= 194,  ///< RIIC3
			ICRXI3		= 195,
			ICTXI3		= 196,
			ICTEI3		= 197,

			DMAC0I		= 198,	///< DMAC
			DMAC1I		= 199,
			DMAC2I		= 200,
			DMAC3I		= 201,

			EXDMAC0I	= 202,	///< EXDMAC 0
			EXDMAC1I	= 203,	///< EXDMAC 1

			DEU0		= 206,	///< DEU
			DEU1		= 207,

			PCDFI		= 208,	///< PDC
			PCFEI		= 209,
			PCERI		= 210,

			RXI0		= 214,	///< SCI0
			TXI0		= 215,
			TEI0		= 216,
			RXI1		= 217,	///< SCI1
			TXI1		= 218,
			TEI1		= 219,
			RXI2		= 220,	///< SCI2
			TXI2		= 221,
			TEI2		= 222,
			RXI3		= 223,	///< SCI3
			TXI3		= 224,
			TEI3		= 225,
			RXI4		= 226,	///< SCI4
			TXI4		= 227,
			TEI4		= 228,
			RXI5		= 229,	///< SCI5
			TXI5		= 230,
			TEI5		= 231,
			RXI6		= 232,	///< SCI6
			TXI6		= 233,
			TEI6		= 234,
			RXI7		= 235,	///< SCI7
			TXI7		= 236,
			TEI7		= 237,
			RXI8		= 238,	///< SCI8
			TXI8		= 239,
			TEI8		= 240,
			RXI9		= 241,	///< SCI9
			TXI9		= 242,
			TEI9		= 243,
			RXI10		= 244,	///< SCI10
			TXI10		= 245,
			TEI10		= 246,
			RXI11		= 247,	///< SCI11
			TXI11		= 248,
			TEI11		= 249,
			RXI12		= 250,	///< SCI12
			TXI12		= 251,
			TEI12		= 252,

			IEBINT		= 253,	///< IEB
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP0 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP0 : uint8_t {
			ERS0 = 0,		///< CAN0
			ERS1 = 1,		///< CAN1
			ERS2 = 2,		///< CAN2
			NUM_ = 3
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP1 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP1 : uint8_t {
			TCIV0 = 0,		///< MTU0
			TCIV1 = 1,		///< MTU1
			TCIU1 = 2,
			NUM_ = 3
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP2 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP2 : uint8_t {
			TCIV2 = 0,		///< MTU2
			TCIU2 = 1,
			TCIV3 = 2,		///< MTU3
			NUM_ = 3
		};








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
			volatile uint8_t& operator [] (VECTOR vec) noexcept {
				return *reinterpret_cast<volatile uint8_t*>(base + static_cast<uint8_t>(vec));
			}
		};
		typedef ir_t<0x0008'7000> IR_;
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
		typedef ier_t<0x0008'7200> IER_;
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
				case VECTOR::CMWI0:  idx = 6; break;
				case VECTOR::CMWI1:  idx = 7; break;
				default: idx = static_cast<uint32_t>(vec); break;
				}
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		typedef ipr_t<0x0008'7300> IPR_;
		static IPR_ IPR;

		/// @brief DTC 転送要求許可レジスタ  (DTCER)
		typedef dtcer_t<0x0008'7100, VECTOR> DTCER_;
		static DTCER_ DTCER;

		/// @brief DMAC 起動要因選択レジスタ m (DMRSRm) (m = DMAC チャネル番号 )
		static DMRSR8N_ DMRSR;
		static DMRSR0_ DMRSR0;
		static DMRSR1_ DMRSR1;
		static DMRSR2_ DMRSR2;
		static DMRSR3_ DMRSR3;
		static DMRSR4_ DMRSR4;
		static DMRSR5_ DMRSR5;
		static DMRSR6_ DMRSR6;
		static DMRSR7_ DMRSR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求レジスタ（GRPBE0） @n
					グループ BL0/1 割り込み要求レジスタ（GRPBL0/GRPBL1） @n
					グループ AL0/1 割り込み要求レジスタ（GRPAL0/GRPAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef grp_t<0x0008'7600, VECTOR_BE0> GRPBE0_;
		typedef grp_t<0x0008'7630, VECTOR_BL0> GRPBL0_;
		typedef grp_t<0x0008'7634, VECTOR_BL1> GRPBL1_;
		typedef grp_t<0x0008'7830, VECTOR_AL0> GRPAL0_;
		typedef grp_t<0x0008'7834, VECTOR_AL1> GRPAL1_;
		static GRPBE0_ GRPBE0;
		static GRPBL0_ GRPBL0;
		static GRPBL1_ GRPBL1;
		static GRPAL0_ GRPAL0;
		static GRPAL1_ GRPAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求許可レジスタ（GENBE0） @n
					グループ BL0/1 割り込み要求許可レジスタ（GENBL0/GENBL1/GENBL2） @n
					グループ AL0/1 割り込み要求許可レジスタ（GENAL0/GENAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gen_t<0x0008'7640, VECTOR_BE0> GENBE0_;
		typedef gen_t<0x0008'7670, VECTOR_BL0> GENBL0_;
		typedef gen_t<0x0008'7674, VECTOR_BL1> GENBL1_;
		typedef gen_t<0x0008'7870, VECTOR_AL0> GENAL0_;
		typedef gen_t<0x0008'7874, VECTOR_AL1> GENAL1_;
		static GENBE0_ GENBE0;
		static GENBL0_ GENBL0;
		static GENBL1_ GENBL1;
		static GENAL0_ GENAL0;
		static GENAL1_ GENAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込みクリアレジスタ（GCRBE0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gcr_t<0x0008'7680, VECTOR_BE0> GCRBE0_;
		static GCRBE0_ GCRBE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み B 要因選択レジスタ Xn（SLIBXRn）（n = 128 ～ 143）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef icu_utils::slixr_t<0x0008'7700, VECTOR, VECTOR_SELB> SLIBR_;
		static SLIBR_ SLIBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要因選択レジスタ n（SLIARn）（n = 208 ～ 255）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef icu_utils::slixr_t<0x0008'7900, VECTOR, VECTOR_SELA> SLIAR_;
		static SLIAR_ SLIAR;
	};
	template<class _> typename icu_t<_>::IR_  icu_t<_>::IR;
	template<class _> typename icu_t<_>::IER_ icu_t<_>::IER;
	template<class _> typename icu_t<_>::IPR_ icu_t<_>::IPR;
	template<class _> typename icu_t<_>::DTCER_ icu_t<_>::DTCER;
	template<class _> typename icu_t<_>::DMRSR8N_ icu_t<_>::DMRSR;
	template<class _> typename icu_t<_>::DMRSR0_ icu_t<_>::DMRSR0;
	template<class _> typename icu_t<_>::DMRSR1_ icu_t<_>::DMRSR1;
	template<class _> typename icu_t<_>::DMRSR2_ icu_t<_>::DMRSR2;
	template<class _> typename icu_t<_>::DMRSR3_ icu_t<_>::DMRSR3;
	template<class _> typename icu_t<_>::DMRSR4_ icu_t<_>::DMRSR4;
	template<class _> typename icu_t<_>::DMRSR5_ icu_t<_>::DMRSR5;
	template<class _> typename icu_t<_>::DMRSR6_ icu_t<_>::DMRSR6;
	template<class _> typename icu_t<_>::DMRSR7_ icu_t<_>::DMRSR7;
	template<class _> typename icu_t<_>::GRPBE0_ icu_t<_>::GRPBE0;
	template<class _> typename icu_t<_>::GRPBL0_ icu_t<_>::GRPBL0;
	template<class _> typename icu_t<_>::GRPBL1_ icu_t<_>::GRPBL1;
	template<class _> typename icu_t<_>::GRPAL0_ icu_t<_>::GRPAL0;
	template<class _> typename icu_t<_>::GRPAL1_ icu_t<_>::GRPAL1;
	template<class _> typename icu_t<_>::GENBE0_ icu_t<_>::GENBE0;
	template<class _> typename icu_t<_>::GENBL0_ icu_t<_>::GENBL0;
	template<class _> typename icu_t<_>::GENBL1_ icu_t<_>::GENBL1;
	template<class _> typename icu_t<_>::GENAL0_ icu_t<_>::GENAL0;
	template<class _> typename icu_t<_>::GENAL1_ icu_t<_>::GENAL1;
	template<class _> typename icu_t<_>::GCRBE0_ icu_t<_>::GCRBE0;
	template<class _> typename icu_t<_>::SLIBR_ icu_t<_>::SLIBR;
	template<class _> typename icu_t<_>::SLIAR_ icu_t<_>::SLIAR;

	typedef icu_t<void> ICU;
}
