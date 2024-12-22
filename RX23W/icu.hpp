#pragma once
//=============================================================================//
/*!	@file
	@brief	Interrupt Controller / 割り込みコントローラ (RX23W)
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
		@brief  RICU class (ICUb)
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
			CMI2		= 30,   ///< CMT2
			CMI3		= 31,   ///< CMT3
			FERRF		= 32,	///< CAC
			MENDF		= 33,	///< CAC
			OVFF		= 34,	///< CAC

			D0FIFO0		= 36,	///< USB0
			D1FIFO0		= 37,
			USBI0		= 38,

			SBFAI		= 40,	///< SDHI
			CDETI		= 41,
			CACI		= 42,
			SDACI		= 43,

			SPEI0		= 44,	///< RSPI0
			SPRI0		= 45,
			SPTI0		= 46,
			SPII0		= 47,

			COMFRXINT	= 52,	///< RSCAN
			RXFINT		= 53,
			TXINT		= 54,
			CHERRINT	= 55,
			GLERRINT	= 56,

			DOPCF		= 57,	///< DOC

			CTSUWR		= 60,	///< CTSU
			CTSURD		= 61,
			CTSUFN		= 62,

			CUP			= 63,	///< RTC

			IRQ0		= 64,	///< ICU
			IRQ1		= 65,

			BLEIRQ		= 67,
			IRQ4		= 68,
			IRQ5		= 69,
			IRQ6		= 70,
			IRQ7		= 71,

			ELSR8I		= 80,	///< ELC

			LVD1		= 88,   ///< LVD1/CMPA1

			USBR0		= 90,	///< USB0

			VBTLVDI		= 91,	///< VBATT

			ALM			= 92,	///< RTC
			PRD			= 93,	///< RTC

			S12ADI0		= 102,	///< S12AD
			GBADI		= 103,	///< S12AD

			CMPB2		= 104,	///< CMPB1
			CMPB3		= 105,

			ELSR18I		= 106,	///< ELC
			ELSR19I		= 107,

			SSIF0		= 108,	///< SSI0
			SSIRXI0		= 109,
			SSITXI0		= 110,

			RD			= 111,	///< TSIP
			WR			= 112,
			ERR			= 113,

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

			TGI0A		= 142,	///< TPU0
			TGI0B		= 143,
			TGI0C		= 144,
			TGI0D		= 145,
			TCI0V		= 146,

			TGI1A		= 147,	///< TPU1
			TGI1B		= 148,
			TCI1V		= 149,
			TCI1U		= 150,

			TGI2A		= 151,	///< TPU2
			TGI2B		= 152,
			TCI2V		= 153,
			TCI2U		= 154,

			TGI3A		= 155,	///< TPU3
			TGI3B		= 156,
			TGI3C		= 157,
			TGI3D		= 158,
			TCI3V		= 159,

			TGI4A		= 160,	///< TPU4
			TGI4B		= 161,
			TCI4V		= 162,
			TCI4U		= 163,

			TGI5A		= 164,	///< TPU5
			TGI5B		= 165,
			TCI5V		= 166,
			TCI5U		= 167,

			OEI1		= 170,	///< POE
			OEI2		= 171,

			CMIA0		= 174,	///< TMR0: CMIA0
			CMIB0		= 175,	///< TMR0: CMIB0
			OVI0		= 176,	///< TMR0: OVI0

			CMIA1		= 177,	///< TMR1: CMIA1
			CMIB1		= 178,	///< TMR1: CMIB1
			OVI1		= 179,	///< TMR1: OVI1

			CMIA2		= 180,	///< TMR2: CMIA2
			CMIB2		= 181,	///< TMR2: CMIB2
			OVI2		= 182,	///< TMR2: OVI2

			CMIA3		= 183,	///< TMR3: CMIA3
			CMIB3		= 184,	///< TMR3: CMIB3
			OVI3		= 185,	///< TMR3: OVI3

			DMACI0		= 198,  ///< DMACA
			DMACI1		= 199,
			DMACI2		= 200,
			DMACI3		= 201,

			ERI1		= 218,  ///< SCI1
			RXI1		= 219,  ///< SCI1
			TXI1		= 220,  ///< SCI1
			TEI1		= 221,  ///< SCI1

			ERI5		= 222,  ///< SCI5
			RXI5		= 223,  ///< SCI5
			TXI5		= 224,  ///< SCI5
			TEI5		= 225,  ///< SCI5

			ERI			= 226,  ///< BLE
			RXI			= 227,  ///< BLE
			TXI			= 228,  ///< BLE
			TEI			= 229,  ///< BLE

			ERI8		= 230,  ///< SCI8
			RXI8		= 231,  ///< SCI8
			TXI8		= 232,  ///< SCI8
			TEI8		= 233,  ///< SCI8

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
				case VECTOR::CMI2:    idx = 0x06; break;
				case VECTOR::CMI3:    idx = 0x07; break;

				case VECTOR::SPEI0:
				case VECTOR::SPRI0:
				case VECTOR::SPTI0:
				case VECTOR::SPII0:
					idx = static_cast<uint32_t>(VECTOR::SPEI0);
					break;
				case VECTOR::CTSUWR:
				case VECTOR::CTSURD:
				case VECTOR::CTSUFN:
					idx = static_cast<uint32_t>(VECTOR::CTSUWR);
					break;
				case VECTOR::SSIF0:
				case VECTOR::SSIRXI0:
				case VECTOR::SSITXI0:
					idx = static_cast<uint32_t>(VECTOR::SSIF0);
					break;
				case VECTOR::RD:
				case VECTOR::WR:
					idx = static_cast<uint32_t>(VECTOR::RD);
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
				case VECTOR::TGI0A:
				case VECTOR::TGI0B:
				case VECTOR::TGI0C:
				case VECTOR::TGI0D:
					idx = static_cast<uint32_t>(VECTOR::TGI0A);
					break;
				case VECTOR::TCI0V:
					idx = static_cast<uint32_t>(VECTOR::TCI0V);
					break;
				case VECTOR::TGI1A:
				case VECTOR::TGI1B:
					idx = static_cast<uint32_t>(VECTOR::TGI1A);
					break;
				case VECTOR::TCI1V:
				case VECTOR::TCI1U:
					idx = static_cast<uint32_t>(VECTOR::TCI1V);
					break;
				case VECTOR::TGI2A:
				case VECTOR::TGI2B:
					idx = static_cast<uint32_t>(VECTOR::TGI2A);
					break;
				case VECTOR::TCI2V:
				case VECTOR::TCI2U:
					idx = static_cast<uint32_t>(VECTOR::TCI2V);
					break;
				case VECTOR::TGI3A:
				case VECTOR::TGI3B:
				case VECTOR::TGI3C:
				case VECTOR::TGI3D:
					idx = static_cast<uint32_t>(VECTOR::TGI3A);
					break;
				case VECTOR::TCI3V:
					idx = static_cast<uint32_t>(VECTOR::TCI3V);
					break;
				case VECTOR::TGI4A:
				case VECTOR::TGI4B:
					idx = static_cast<uint32_t>(VECTOR::TGI4A);
					break;
				case VECTOR::TCI4V:
				case VECTOR::TCI4U:
					idx = static_cast<uint32_t>(VECTOR::TCI4V);
					break;
				case VECTOR::TGI5A:
				case VECTOR::TGI5B:
					idx = static_cast<uint32_t>(VECTOR::TGI5A);
					break;
				case VECTOR::TCI5V:
				case VECTOR::TCI5U:
					idx = static_cast<uint32_t>(VECTOR::TCI5V);
					break;
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
				case VECTOR::ERI:
				case VECTOR::RXI:
				case VECTOR::TXI:
				case VECTOR::TEI:
					idx = static_cast<uint32_t>(VECTOR::ERI);
					break;
				case VECTOR::ERI8:
				case VECTOR::RXI8:
				case VECTOR::TXI8:
				case VECTOR::TEI8:
					idx = static_cast<uint32_t>(VECTOR::ERI8);
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

		/// @brief DMAC 起動要因選択レジスタ m (DMRSRm) (m = DMAC チャネル番号 )
		static inline rw8_t<0x0008'7400> DMRSR0;
		static inline rw8_t<0x0008'7404> DMRSR1;
		static inline rw8_t<0x0008'7408> DMRSR2;
		static inline rw8_t<0x0008'740C> DMRSR3;
	};
	typedef icu_t ICU;
}
