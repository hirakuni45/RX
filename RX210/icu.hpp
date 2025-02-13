#pragma once
//=========================================================================//
/*!	@file
	@brief	Interrupt Controller / 割り込みコントローラ (RX210)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ICU class (ICUb)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t : public ICU_BASE, ICU_IRQ8 {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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

			DOPCF	= 57,	///< DOC

			CMPB0   = 58,	///< CMPB
			CMPB1   = 59,	///< CMPB

			CUP		= 63,	///< RTC

			IRQ0    = 64,	///< ICU
			IRQ1    = 65,
			IRQ2    = 66,
			IRQ3    = 67,
			IRQ4    = 68,
			IRQ5    = 69,
			IRQ6    = 70,
			IRQ7    = 71,

			LVD1	= 88,   ///< LVD
			LVD2    = 89,	///< LVD
			CMPA1   = 88,	///< CMPA
			CMPA2   = 89,	///< CMPA

			ALM		= 92,	///< RTC
			PRD		= 93,	///< RTC

			S12ADI0	= 102,	///< S12AD
			GBADI	= 103,	///< S12AD

			ELSR18I	= 106,	///< ELC
			ELSRI9I = 107,	///< ELC

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

			TGI0A   = 142,	///< TPU0
			TGI0B   = 143,	///< TPU0 
			TGI0C   = 144,	///< TPU0 
			TGI0D   = 145,	///< TPU0 
			TCI0V   = 146,	///< TPU0 

			TGI1A   = 147,	///< TPU1
			TGI1B   = 148,	///< TPU1 
			TCI1V   = 149,	///< TPU1 
			TCI1U   = 150,	///< TPU1

			TGI2A   = 151,	///< TPU2
			TGI2B   = 152,	///< TPU2 
			TCI2V   = 153,	///< TPU2 
			TCI2U   = 154,	///< TPU2

			TGI3A   = 155,	///< TPU3
			TGI3B   = 156,	///< TPU3
			TGI3C   = 157,	///< TPU3
			TGI3D   = 158,	///< TPU3
			TCI3V   = 159,	///< TPU3

			TGI4A   = 160,	///< TPU4
			TGI4B   = 161,	///< TPU4 
			TCI4V   = 162,	///< TPU4 
			TCI4U   = 163,	///< TPU4

			TGI5A   = 164,	///< TPU5
			TGI5B   = 165,	///< TPU5 
			TCI5V   = 166,	///< TPU5 
			TCI5U   = 167,	///< TPU5

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

			ERI2    = 186,  ///< SCI2
			RXI2    = 187,  ///< SCI2
			TXI2    = 188,  ///< SCI2
			TEI2    = 189,  ///< SCI2

			ERI3    = 190,  ///< SCI3
			RXI3    = 191,  ///< SCI3
			TXI3    = 192,  ///< SCI3
			TEI3    = 193,  ///< SCI3

			ERI4    = 194,  ///< SCI4
			RXI4    = 195,  ///< SCI4
			TXI4    = 196,  ///< SCI4
			TEI4    = 197,  ///< SCI4

			DMACI0  = 198,  ///< DMACA
			DMACI1  = 199,  ///< DMACA
			DMACI2  = 200,  ///< DMACA
			DMACI3  = 201,  ///< DMACA

			ERI7    = 206,  ///< SCI7
			RXI7    = 207,  ///< SCI7
			TXI7    = 208,  ///< SCI7
			TEI7    = 209,  ///< SCI7

			ERI10   = 210,  ///< SCI10
			RXI10   = 211,  ///< SCI10
			TXI10   = 212,  ///< SCI10
			TEI10   = 213,  ///< SCI10

			ERI0    = 214,  ///< SCI0
			RXI0    = 215,  ///< SCI0
			TXI0    = 216,  ///< SCI0
			TEI0    = 217,  ///< SCI0

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

			ERI8    = 230,  ///< SCI8
			RXI8    = 231,  ///< SCI8
			TXI8    = 232,  ///< SCI8
			TEI8    = 233,  ///< SCI8

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

			ERI11   = 250,  ///< SCI11
			RXI11   = 251,  ///< SCI11
			TXI11   = 252,  ///< SCI11
			TEI11   = 253,  ///< SCI11
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
				case VECTOR::FIFERR:  idx = 0x01; break;
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

				case VECTOR::ERI2:
				case VECTOR::RXI2:
				case VECTOR::TXI2:
				case VECTOR::TEI2:
					idx = static_cast<uint32_t>(VECTOR::ERI2);
					break;
				case VECTOR::ERI3:
				case VECTOR::RXI3:
				case VECTOR::TXI3:
				case VECTOR::TEI3:
					idx = static_cast<uint32_t>(VECTOR::ERI3);
					break;
				case VECTOR::ERI4:
				case VECTOR::RXI4:
				case VECTOR::TXI4:
				case VECTOR::TEI4:
					idx = static_cast<uint32_t>(VECTOR::ERI4);
					break;

				case VECTOR::ERI7:
				case VECTOR::RXI7:
				case VECTOR::TXI7:
				case VECTOR::TEI7:
					idx = static_cast<uint32_t>(VECTOR::ERI7);
					break;
				case VECTOR::ERI10:
				case VECTOR::RXI10:
				case VECTOR::TXI10:
				case VECTOR::TEI10:
					idx = static_cast<uint32_t>(VECTOR::ERI10);
					break;
				case VECTOR::ERI0:
				case VECTOR::RXI0:
				case VECTOR::TXI0:
				case VECTOR::TEI0:
					idx = static_cast<uint32_t>(VECTOR::ERI0);
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
				case VECTOR::ERI6:
				case VECTOR::RXI6:
				case VECTOR::TXI6:
				case VECTOR::TEI6:
					idx = static_cast<uint32_t>(VECTOR::ERI6);
					break;
				case VECTOR::ERI8:
				case VECTOR::RXI8:
				case VECTOR::TXI8:
				case VECTOR::TEI8:
					idx = static_cast<uint32_t>(VECTOR::ERI8);
					break;
				case VECTOR::ERI9:
				case VECTOR::RXI9:
				case VECTOR::TXI9:
				case VECTOR::TEI9:
					idx = static_cast<uint32_t>(VECTOR::ERI9);
					break;
				case VECTOR::ERI12:
				case VECTOR::RXI12:
				case VECTOR::TXI12:
				case VECTOR::TEI12:
					idx = static_cast<uint32_t>(VECTOR::ERI12);
					break;
				case VECTOR::ERI11:
				case VECTOR::RXI11:
				case VECTOR::TXI11:
				case VECTOR::TEI11:
					idx = static_cast<uint32_t>(VECTOR::ERI11);
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
