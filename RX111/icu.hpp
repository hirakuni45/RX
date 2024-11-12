#pragma once
//=============================================================================//
/*!	@file
	@brief	RX111 グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/io_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX111 割り込みコントローラ・テンプレート・クラス（ICUb）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t : public ICU_BASE, ICU_IRQ8 {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR {
			NONE		= 0,	///< none

			BUSERR		= 16,   ///< BSC

			FRDYI		= 23,   ///< FCU

			SWINT		= 27,   ///< ICU
			CMI0		= 28,   ///< CMT0
			CMI1		= 29,   ///< CMT1

			FERRF		= 32,	///< CAC
			MENDF		= 33,	///< CAC
			OVFF		= 34,	///< CAC

			D0FIFO0		= 36,	///< USB0
			D1FIFO0		= 37,	///< USB0
			USBI0		= 38,	///< USB0

			SPEI0		= 44,	///< RSPI0
			SPRI0		= 45,
			SPTI0		= 46,
			SPII0		= 47,

			DOPCF		= 57,	///< DOC

			CMPB0		= 58,	///< CMPB0
			CMPB1		= 59,

			CTSUWR		= 60,	///< CTSU
			CTSURD		= 61,
			CTSUFN		= 62,

			CUP			= 63,	///< RTC

			IRQ0		= 64,	///< ICU
			IRQ1		= 65,
			IRQ2		= 66,
			IRQ3		= 67,
			IRQ4		= 68,
			IRQ5		= 69,
			IRQ6		= 70,
			IRQ7		= 71,

			LVD1		= 88,   ///< LVD/CMPA
			LVD2    	= 89,	///< LVD/CMPA

			USBR0		= 90,	///< USB0

			ALM			= 92,	///< RTC
			PRD			= 93,	///< RTC

			S12ADI0		= 102,	///< S12AD
			GBADI		= 103,	///< S12AD

			ELSR18I		= 106,	///< ELC

			TGIA0		= 114,  ///< MTU0
			TGIB0		= 115,
			TGIC0		= 116,
			TGID0		= 117,
			TCIV0		= 118,
			TGIE0		= 119,
			TGIF0		= 120,

			TGIA1		= 121,  ///< MTU1
			TGIB1		= 122,
			TCIV1		= 123,
			TCIU1		= 124,

			TGIA2		= 125,  ///< MTU2
			TGIB2		= 126,
			TCIV2		= 127,
			TCIU2		= 128,

			TGIA3		= 129,  ///< MTU3
			TGIB3		= 130,
			TGIC3		= 131,
			TGID3		= 132,
			TCIV3		= 133,

			TGIA4		= 134,  ///< MTU4
			TGIB4		= 135,
			TGIC4		= 136,
			TGID4		= 137,
			TCIV4		= 138,

			TGIU5		= 139,  ///< MTU5
			TGIV5		= 140,
			TGIW5		= 141,

			OEI1		= 170,	///< POE
			OEI2		= 171,

			ERI1		= 218,  ///< SCI1
			RXI1		= 219,  ///< SCI1
			TXI1		= 220,  ///< SCI1
			TEI1		= 221,  ///< SCI1

			ERI5		= 222,  ///< SCI5
			RXI5		= 223,  ///< SCI5
			TXI5		= 224,  ///< SCI5
			TEI5		= 225,  ///< SCI5

			ERI12		= 238,  ///< SCI12
			RXI12		= 239,  ///< SCI12
			TXI12		= 240,  ///< SCI12
			TEI12		= 241,  ///< SCI12
			SCIX0		= 242,	///< SCI12
			SCIX1		= 243,	///< SCI12
			SCIX2		= 244,	///< SCI12
			SCIX3		= 245,	///< SCI12

			ICEEI0		= 246,  ///< RIIC0 (EEI0)
			ICRXI0		= 247,  ///< RIIC0 (RXI0)
			ICTXI0		= 248,  ///< RIIC0 (TXI0)
			ICTEI0		= 249,  ///< RIIC0 (TEI0)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {

			//-----------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		割り込みベクター型
				@return IR レジスターの参照
			*/
			//-----------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) noexcept {
				return *reinterpret_cast<volatile uint8_t*>(base + static_cast<uint8_t>(vec));
			}
		};
		static inline ir_t<0x0008'7000> IR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ier_t {

			//-----------------------------------------------------------------//
			/*!
				@brief  許可、不許可
				@param[in]	vec		割り込みベクター型
				@param[in]	ena		不許可の場合「false」
			*/
			//-----------------------------------------------------------------//
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


			//-----------------------------------------------------------------//
			/*!
				@brief  許可状態を取得
				@param[in]	vec		割り込みベクター型
				@return 許可状態（許可の場合「true」）
			*/
			//-----------------------------------------------------------------//
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
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ipr_t {

			//-----------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		標準割り込みベクター型
				@return IPR レジスターの参照
			*/
			//-----------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) {
				uint32_t idx = 0;
				switch(vec) {
				case VECTOR::BUSERR:  idx = 0x00; break;
				case VECTOR::FRDYI:   idx = 0x02; break;
				case VECTOR::SWINT:   idx = 0x03; break;
				case VECTOR::CMI0:    idx = 0x04; break;
				case VECTOR::CMI1:    idx = 0x05; break;

				case VECTOR::SPEI0:
				case VECTOR::SPRI0:
				case VECTOR::SPTI0:
				case VECTOR::SPII0:
					idx = static_cast<uint32_t>(VECTOR::SPEI0);
					break;

				case VECTOR::TGIA0:
				case VECTOR::TGIB0:
				case VECTOR::TGIC0:
				case VECTOR::TGID0:
					idx = static_cast<uint32_t>(VECTOR::TGIA0);
					break;
				case VECTOR::TCIV0:
				case VECTOR::TGIE0:
				case VECTOR::TGIF0:
					idx = static_cast<uint32_t>(VECTOR::TCIV0);
					break;
				case VECTOR::TGIA1:
				case VECTOR::TGIB1:
					idx = static_cast<uint32_t>(VECTOR::TGIA1);
					break;
				case VECTOR::TCIV1:
				case VECTOR::TCIU1:
					idx = static_cast<uint32_t>(VECTOR::TCIV1);
					break;
				case VECTOR::TGIA2:
				case VECTOR::TGIB2:
					idx = static_cast<uint32_t>(VECTOR::TGIA2);
					break;
				case VECTOR::TCIV2:
				case VECTOR::TCIU2:
					idx = static_cast<uint32_t>(VECTOR::TCIV2);
					break;
				case VECTOR::TGIA3:
				case VECTOR::TGIB3:
				case VECTOR::TGIC3:
				case VECTOR::TGID3:
					idx = static_cast<uint32_t>(VECTOR::TGIA3);
					break;
				case VECTOR::TCIV3:
					idx = static_cast<uint32_t>(VECTOR::TCIV3);
					break;
				case VECTOR::TGIA4:
				case VECTOR::TGIB4:
				case VECTOR::TGIC4:
				case VECTOR::TGID4:
					idx = static_cast<uint32_t>(VECTOR::TGIA4);
					break;
				case VECTOR::TCIV4:
					idx = static_cast<uint32_t>(VECTOR::TCIV4);
					break;
				case VECTOR::TGIU5:
				case VECTOR::TGIV5:
				case VECTOR::TGIW5:
					idx = static_cast<uint32_t>(VECTOR::TGIU5);
					break;

				case VECTOR::ERI1:
				case VECTOR::RXI1:
				case VECTOR::TXI1:
				case VECTOR::TEI1:
					idx = static_cast<uint32_t>(VECTOR::ERI1);
					break;
				case VECTOR::ERI5:
				case VECTOR::RXI5:
				case VECTOR::TXI5:
				case VECTOR::TEI5:
					idx = static_cast<uint32_t>(VECTOR::ERI5);
					break;

				case VECTOR::ERI12:
				case VECTOR::RXI12:
				case VECTOR::TXI12:
				case VECTOR::TEI12:
					idx = static_cast<uint32_t>(VECTOR::ERI12);
					break;
				default: idx = static_cast<uint32_t>(vec); break;
				}
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}

		};
		static inline ipr_t<0x0008'7300> IPR;

		/// @brief DTC 転送要求許可レジスタ  (DTCER)
		static inline dtcer_t<0x0008'7100, VECTOR> DTCER;
	};
	typedef icu_t ICU;
}
