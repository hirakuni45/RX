#pragma once
//=====================================================================//
/*!	@file
	@brief	RX220 グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX220 割り込みコントローラ・テンプレート・クラス（ICUb）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_t : public ICU_BASE {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR {
			NONE    = 0,	///< none

			BUSERR  = 16,   ///< BSC

			FIFERR  = 21,	///< FCU

			FRDYI   = 23,   ///< FCU

			SWINT   = 27,   ///< ICU
			CMI0    = 28,   ///< CMT0
			CMI1    = 29,   ///< CMT1
			CMI2    = 30,   ///< CMT2
			CMI3    = 31,   ///< CMT3
			FERRF   = 32,	///< CAC
			MENDF   = 33,	///< CAC
			OVFF    = 34,	///< CAC

			SPEI0   = 44,	///< RSPI0
			SPRI0   = 45,	///< RSPI0
			SPTI0   = 46,	///< RSPI0
			SPII0   = 47,	///< RSPI0

			DCPCF	= 57,	///< DOC

			CUP		= 63,	///< RTC
			IRQ0    = 64,	///< ICU
			IRQ1    = 65,
			IRQ2    = 66,
			IRQ3    = 67,
			IRQ4    = 68,
			IRQ5    = 69,
			IRQ6    = 70,
			IRQ7    = 71,

			LVD1	= 88,   ///< LVD/CMPA
			LVD2    = 89,	///< LVD/CMPA

			ALM		= 92,	///< RTC
			PRD		= 93,	///< RTC

			S12ADI0	= 102,	///< S12AD
			GBADI	= 103,	///< S12AD

			ELSR18I	= 106,	///< ELC

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

			OEI1	= 170,	///< POE
			OEI2	= 171,	///< POE

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

			DMACI0  = 198,  ///< DMACA
			DMACI1  = 199,  ///< DMACA
			DMACI2  = 200,  ///< DMACA
			DMACI3  = 201,  ///< DMACA

			EXDMACI0 = 202,  ///< EXDMACA
			EXDMACI1 = 203,  ///< EXDMACA

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

			ERI9    = 234,  ///< SCI9
			RXI9    = 235,  ///< SCI9
			TXI9    = 236,  ///< SCI9
			TEI9    = 237,  ///< SCI9

			ERI12   = 238,  ///< SCI12
			RXI12   = 239,  ///< SCI12
			TXI12   = 240,  ///< SCI12
			TEI12   = 241,  ///< SCI12
			SCIX0	= 242,	///< SCI12
			SCIX1	= 243,	///< SCI12
			SCIX2	= 244,	///< SCI12
			SCIX3	= 245,	///< SCI12

			ICEEI0  = 246,  ///< RIIC0 (EEI0)
			ICRXI0  = 247,  ///< RIIC0 (RXI0)
			ICTXI0  = 248,  ///< RIIC0 (TXI0)
			ICTEI0  = 249,  ///< RIIC0 (TEI0)
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
		typedef ier_t<0x0008'7200> IER_;
		static IER_ IER;

#if 0
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
				case VECTOR::FIFERR:  idx = 0x01; break;
				case VECTOR::FRDYI:   idx = 0x02; break;
				case VECTOR::SWINT:   idx = 0x03; break;
				case VECTOR::CMI0:    idx = 0x04; break;
				case VECTOR::CMI1:    idx = 0x05; break;
				case VECTOR::CMI2:    idx = 0x06; break;
				case VECTOR::CMI3:    idx = 0x07; break;
				case VECTOR::EINT:    idx = 0x08; break;

				case VECTOR::D0FIFO0: idx = 0x0C; break;
				case VECTOR::D1FIFO0: idx = 0x0D; break;
				case VECTOR::USBI0:   idx = 0x0E; break;

				case VECTOR::D0FIFO1: idx = 0x10; break;
				case VECTOR::D1FIFO1: idx = 0x11; break;
				case VECTOR::USBI1:   idx = 0x12; break;

				case VECTOR::SPEI0:
				case VECTOR::SPRI0:
				case VECTOR::SPTI0:
				case VECTOR::SPII0:   idx = 0x14; break;
				case VECTOR::SPEI1:
				case VECTOR::SPRI1:
				case VECTOR::SPTI1:
				case VECTOR::SPII1:   idx = 0x15; break;

				case VECTOR::ERS0:
				case VECTOR::RXF0:
				case VECTOR::TXF0:
				case VECTOR::RXM0:
				case VECTOR::TXM0:    idx = 0x18; break;

				case VECTOR::PRD:     idx = 0x1E; break;
				case VECTOR::CUP:     idx = 0x1F; break;

				case VECTOR::IRQ0:    idx = 0x20; break;
				case VECTOR::IRQ1:    idx = 0x21; break;
				case VECTOR::IRQ2:    idx = 0x22; break;
				case VECTOR::IRQ3:    idx = 0x23; break;
				case VECTOR::IRQ4:    idx = 0x24; break;
				case VECTOR::IRQ5:    idx = 0x25; break;
				case VECTOR::IRQ6:    idx = 0x26; break;
				case VECTOR::IRQ7:    idx = 0x27; break;
				case VECTOR::IRQ8:    idx = 0x28; break;
				case VECTOR::IRQ9:    idx = 0x29; break;
				case VECTOR::IRQ10:   idx = 0x2A; break;
				case VECTOR::IRQ11:   idx = 0x2B; break;
				case VECTOR::IRQ12:   idx = 0x2C; break;
				case VECTOR::IRQ13:   idx = 0x2D; break;
				case VECTOR::IRQ14:   idx = 0x2E; break;
				case VECTOR::IRQ15:   idx = 0x2F; break;

				case VECTOR::USBR0:   idx = 0x3A; break;
				case VECTOR::USBR1:   idx = 0x3B; break;

				case VECTOR::ALM:     idx = 0x3C; break;

				case VECTOR::WOVI:    idx = 0x40; break;

				case VECTOR::ADI0:    idx = 0x44; break;
				case VECTOR::ADI1:    idx = 0x45; break;

				case VECTOR::S12ADI0: idx = 0x48; break;

				case VECTOR::TGIA0:
				case VECTOR::TGIB0:
				case VECTOR::TGIC0:
				case VECTOR::TGID0:   idx = 0x51; break;
				case VECTOR::TCIV0:
				case VECTOR::TGIE0:
				case VECTOR::TGIF0:   idx = 0x52; break;

				case VECTOR::TGIA1:
				case VECTOR::TGIB1:   idx = 0x53; break;
				case VECTOR::TCIV1:
				case VECTOR::TCIU1:   idx = 0x54; break;

				case VECTOR::TGIA2:
				case VECTOR::TGIB2:   idx = 0x55; break;
				case VECTOR::TCIV2:
				case VECTOR::TCIU2:   idx = 0x56; break;

				case VECTOR::TGIA3:
				case VECTOR::TGIB3:
				case VECTOR::TGIC3:
				case VECTOR::TGID3:   idx = 0x57; break;
				case VECTOR::TCIV3:   idx = 0x58; break;

				case VECTOR::TGIA4:
				case VECTOR::TGIB4:
				case VECTOR::TGIC4:
				case VECTOR::TGID4:   idx = 0x59; break;
				case VECTOR::TCIV4:   idx = 0x5A; break;

				case VECTOR::TGIU5:
				case VECTOR::TGIV5:
				case VECTOR::TGIW5:   idx = 0x5B; break;

				case VECTOR::TGIA6:
				case VECTOR::TGIB6:
				case VECTOR::TGIC6:
				case VECTOR::TGID6:   idx = 0x5C; break;
				case VECTOR::TCIV6:
				case VECTOR::TGIE6:
				case VECTOR::TGIF6:   idx = 0x5D; break;

				case VECTOR::TGIA7:
				case VECTOR::TGIB7:   idx = 0x5E; break;
				case VECTOR::TCIV7:
				case VECTOR::TCIU7:   idx = 0x5F; break;

				case VECTOR::TGIA8:
				case VECTOR::TGIB8:   idx = 0x60; break;
				case VECTOR::TCIV8:
				case VECTOR::TCIU8:   idx = 0x61; break;

				case VECTOR::TGIA9:
				case VECTOR::TGIB9:
				case VECTOR::TGIC9:
				case VECTOR::TGID9:   idx = 0x62; break;
				case VECTOR::TCIV9:   idx = 0x63; break;

				case VECTOR::TGIA10:
				case VECTOR::TGIB10:
				case VECTOR::TGIC10:
				case VECTOR::TGID10:  idx = 0x64; break;
				case VECTOR::TCIV10:  idx = 0x65; break;

				case VECTOR::TGIU11:
				case VECTOR::TGIV11:
				case VECTOR::TGIW11:  idx = 0x66; break;

				case VECTOR::OEI1:
				case VECTOR::OEI2:
				case VECTOR::OEI3:
				case VECTOR::OEI4:    idx = 0x67; break;

				case VECTOR::CMIA0:
				case VECTOR::CMIB0:
				case VECTOR::OVI0:    idx = 0x68; break;

				case VECTOR::CMIA1:
				case VECTOR::CMIB1:
				case VECTOR::OVI1:    idx = 0x69; break;

				case VECTOR::CMIA2:
				case VECTOR::CMIB2:
				case VECTOR::OVI2:    idx = 0x6A; break;

				case VECTOR::CMIA3:
				case VECTOR::CMIB3:
				case VECTOR::OVI3:    idx = 0x6B; break;

				case VECTOR::DMACI0:  idx = 0x70; break;
				case VECTOR::DMACI1:  idx = 0x71; break;
				case VECTOR::DMACI2:  idx = 0x72; break;
				case VECTOR::DMACI3:  idx = 0x73; break;

				case VECTOR::EXDMACI0: idx = 0x74; break;
				case VECTOR::EXDMACI1: idx = 0x75; break;

				case VECTOR::ERI0:
				case VECTOR::RXI0:
				case VECTOR::TXI0:
				case VECTOR::TEI0:     idx = 0x80; break;

				case VECTOR::ERI1:
				case VECTOR::RXI1:
				case VECTOR::TXI1:
				case VECTOR::TEI1:     idx = 0x81; break;

				case VECTOR::ERI2:
				case VECTOR::RXI2:
				case VECTOR::TXI2:
				case VECTOR::TEI2:     idx = 0x82; break;

				case VECTOR::ERI3:
				case VECTOR::RXI3:
				case VECTOR::TXI3:
				case VECTOR::TEI3:     idx = 0x83; break;

				case VECTOR::ERI5:
				case VECTOR::RXI5:
				case VECTOR::TXI5:
				case VECTOR::TEI5:     idx = 0x85; break;

				case VECTOR::ERI6:
				case VECTOR::RXI6:
				case VECTOR::TXI6:
				case VECTOR::TEI6:     idx = 0x86; break;

				case VECTOR::ICEEI0:   idx = 0x88; break;
				case VECTOR::ICRXI0:   idx = 0x89; break;
				case VECTOR::ICTXI0:   idx = 0x8A; break;
				case VECTOR::ICTEI0:   idx = 0x8B; break;

				case VECTOR::ICEEI1:   idx = 0x8C; break;
				case VECTOR::ICRXI1:   idx = 0x8D; break;
				case VECTOR::ICTXI1:   idx = 0x8E; break;
				case VECTOR::ICTEI1:   idx = 0x8F; break;

				default: idx = static_cast<uint32_t>(vec); break;
				}
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}

		};
		typedef ipr_t<0x0008'7300> IPR_;
		static IPR_ IPR;
#endif





		/// @brief DTC 転送要求許可レジスタ  (DTCER)
		typedef dtcer_t<0x0008'7100, VECTOR> DTCER_;
		static DTCER_ DTCER;


		/// @brief DMAC 起動要因選択レジスタ m (DMRSRm) (m = DMAC チャネル番号 )
		typedef rw8_t<0x0008'7400> DMRSR0_;
		static DMRSR0_ DMRSR0;
		typedef rw8_t<0x0008'7404> DMRSR1_;
		static DMRSR1_ DMRSR1;
		typedef rw8_t<0x0008'7408> DMRSR2_;
		static DMRSR2_ DMRSR2;
		typedef rw8_t<0x0008'740C> DMRSR3_;
		static DMRSR3_ DMRSR3;
	};
	typedef icu_t<void> ICU;

	template<class _> typename icu_t<_>::IR_ icu_t<_>::IR;
	template<class _> typename icu_t<_>::IER_ icu_t<_>::IER;
//	template<class _> typename icu_t<_>::IPR_ icu_t<_>::IPR;
	template<class _> typename icu_t<_>::DTCER_ icu_t<_>::DTCER;
	template<class _> typename icu_t<_>::DMRSR0_ icu_t<_>::DMRSR0;
	template<class _> typename icu_t<_>::DMRSR1_ icu_t<_>::DMRSR1;
	template<class _> typename icu_t<_>::DMRSR2_ icu_t<_>::DMRSR2;
	template<class _> typename icu_t<_>::DMRSR3_ icu_t<_>::DMRSR3;
}
