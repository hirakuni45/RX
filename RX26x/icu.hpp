#pragma once
//=========================================================================//
/*!	@file
	@brief	RX260/RX261 グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/icu_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みコントローラ・テンプレート・クラス（ICUb）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icub_t : public ICU_BASE, ICU_IRQ8, ICU_GROUP, ICU_SELECT {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常割り込みベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {
			NONE		= 0,	///< none 

			BUSERR		= 16,	///< BSC

			RAMERR		= 18,	///< RAM

			FIFERR		= 21,	///< FCU

			FRDYI		= 23,	///< FCU

			SWINT		= 27,	///< ICU

			CMI0		= 28,	///< CMT0
			CMI1		= 29,	///< CMT1
			CMI2		= 30,	///< CMT2
			CMI3		= 31,	///< CMT3
			FERRF		= 32,	///< CAC
			MENDF,
			OVFF,

			D0FIFO0		= 36,	///< USB0
			D1FIFO0,
			USBI0,

			POEGGAI		= 40,	///< POEG
			POEGGBI,
			POEGGCI,
			POEGGDI,

			SPEI0		= 44,	///< RSPI0
			SPRI0,
			SPTI0,
			SPII0,

			DOPCF		= 57,	///< DOC

			CMPB0		= 58,	///< CMPB
			CMPB1,

			CTSUWR		= 60,	///< CTSU
			CTSURD,
			CTSUFN,

			CUP			= 63,	///< RTC

			IRQ0		= 64,	///< ICU
			IRQ1,
			IRQ2,
			IRQ3,
			IRQ4,
			IRQ5,
			IRQ6,
			IRQ7,

			ELSR8I		= 80,	///< ELC

			SNZI		= 81,	///< SYSTEM

			LVD1		= 88,	///< LVD
			LVD2,
			CMPA2		= 89,	///< CMPA

			USBR0		= 90,	///< USB0

			ALM			= 92,	///< RTC
			PRD,

			REMCI0		= 94,	///< REMC0

			S12ADI0		= 102,	///< S12AD
			GBADI,

			ELSR18I		= 106,	///< ELC
			ELSR19I,

			GTCIA0		= 108,	///< GPTW0
			GTCIB0,
			GTCIC0,
			GTCID0,
			GTCIE0,
			GTCIF0,
			GTCIV0,
			GTCIU0,

			GTCIA1		= 116,	///< GPTW1
			GTCIB1,
			GTCIC1,
			GTCID1,
			GTCIE1,
			GTCIF1,
			GTCIV1,
			GTCIU1,

			GTCIA2		= 124,	///< GPTW2
			GTCIB2,
			GTCIC2,
			GTCID2,
			GTCIE2,
			GTCIF2,
			GTCIV2,
			GTCIU2,

			GTCIA3		= 132,	///< GPTW3
			GTCIB3,
			GTCIC3,
			GTCID3,
			GTCIE3,
			GTCIF3,
			GTCIV3,
			GTCIU3,

			GTCIA4		= 140,	///< GPTW4
			GTCIB4,
			GTCIC4,
			GTCID4,
			GTCIE4,
			GTCIF4,
			GTCIV4,
			GTCIU4,

			GTCIA5		= 148,	///< GPTW5
			GTCIB5,
			GTCIC5,
			GTCID5,
			GTCIE5,
			GTCIF5,
			GTCIV5,
			GTCIU5,

			GTCIA6		= 156,	///< GPTW6
			GTCIB6,
			GTCIC6,
			GTCID6,
			GTCIE6,
			GTCIF6,
			GTCIV6,
			GTCIU6,

			GTCIA7		= 164,	///< GPTW7
			GTCIB7,
			GTCIC7,
			GTCID7,
			GTCIE7,
			GTCIF7,
			GTCIV7,
			GTCIU7,

			CMIA0		= 174,	///< TMR0
			CMIB0,
			OVI0,
			CMIA1		= 177,	///< TMR1
			CMIB1,
			OVI1,
			CMIA2		= 180,	///< TMR2
			CMIB2,
			OVI2,
			CMIA3		= 183,	///< TMR3
			CMIB3,
			OVI3,

			RFRI		= 186,	///< CANFD
			GLEI,
			RMRI,
			RFDREQ0,
			RFDREQ1,
			EC1EI,
			EC2EI,
			ECOVI,

			CHTI		= 194,	///< CANFD0
			CHEI,
			CFRI,
			CFDREQ0,

			DMACI0		= 198,	///< DMAC
			DMACI1,
			DMACI2,
			DMACI3,

			PROC_BUSY	= 202,	///< RSIP
			ROMOK,
			LONG_PLG,
			TEST_BUSY,
			WRRDY0,
			WRRDY2,
			RDRDY0,
			INTEGRATE_RDRDY,
			INTEGRATE_WRRDY,
			ECCERR,

			BFD			= 212,	///< RSCI9
			AED,

			ERI0		= 214,	///< RSCI0
			RXI0,
			TXI0,
			TEI0,

			ERI1		= 218,	///< SCI1
			RXI1,
			TXI1,
			TEI1,

			ERI5      	= 222,	///< SCI5
			RXI5,
			TXI5,
			TEI5,

			ERI6      	= 226,	///< SCI6
			RXI6,
			TXI6,
			TEI6,

			ERI8		= 230,	///< RSCI8
			RXI8,
			TXI8,
			TEI8,

			ERI9		= 234,	///< RSCI9
			RXI9,
			TXI9,
			TEI9,

			ERI12		= 238,	///< SCI12
			RXI12,
			TXI12,
			TEI12,
			SCIX0,
			SCIX1,
			SCIX2,
			SCIX3,

			ICEEI0		= 246,	///< RIIC0
			ICRXI0,
			ICTXI0,
			ICTEI0,

			LPTCMI1		= 255	///< LPT
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
			volatile uint8_t& operator [] (VECTOR vec) {
				return *reinterpret_cast<volatile uint8_t*>(base + static_cast<uint8_t>(vec));
			}
		};
		static inline ir_t<0x0008'7000> IR;


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
				case VECTOR::SWINT:  idx = 3; break;
				case VECTOR::CMI0:   idx = 4; break;
				case VECTOR::CMI1:   idx = 5; break;
				case VECTOR::CMI2:   idx = 6; break;
				case VECTOR::CMI3:   idx = 7; break;

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

				case VECTOR::GTCIA0:
				case VECTOR::GTCIB0:
					idx = static_cast<uint32_t>(VECTOR::GTCIA0);
					break;
				case VECTOR::GTCIC0:
				case VECTOR::GTCID0:
				case VECTOR::GTCIE0:
				case VECTOR::GTCIF0:
					idx = static_cast<uint32_t>(VECTOR::GTCIC0);
					break;
				case VECTOR::GTCIV0:
				case VECTOR::GTCIU0:
					idx = static_cast<uint32_t>(VECTOR::GTCIV0);
					break;

				case VECTOR::GTCIA1:
				case VECTOR::GTCIB1:
					idx = static_cast<uint32_t>(VECTOR::GTCIA1);
					break;
				case VECTOR::GTCIC1:
				case VECTOR::GTCID1:
				case VECTOR::GTCIE1:
				case VECTOR::GTCIF1:
					idx = static_cast<uint32_t>(VECTOR::GTCIC1);
					break;
				case VECTOR::GTCIV1:
				case VECTOR::GTCIU1:
					idx = static_cast<uint32_t>(VECTOR::GTCIV1);
					break;

				case VECTOR::GTCIA2:
				case VECTOR::GTCIB2:
					idx = static_cast<uint32_t>(VECTOR::GTCIA2);
					break;
				case VECTOR::GTCIC2:
				case VECTOR::GTCID2:
				case VECTOR::GTCIE2:
				case VECTOR::GTCIF2:
					idx = static_cast<uint32_t>(VECTOR::GTCIC2);
					break;
				case VECTOR::GTCIV2:
				case VECTOR::GTCIU2:
					idx = static_cast<uint32_t>(VECTOR::GTCIV2);
					break;

				case VECTOR::GTCIA3:
				case VECTOR::GTCIB3:
					idx = static_cast<uint32_t>(VECTOR::GTCIA3);
					break;
				case VECTOR::GTCIC3:
				case VECTOR::GTCID3:
				case VECTOR::GTCIE3:
				case VECTOR::GTCIF3:
					idx = static_cast<uint32_t>(VECTOR::GTCIC3);
					break;
				case VECTOR::GTCIV3:
				case VECTOR::GTCIU3:
					idx = static_cast<uint32_t>(VECTOR::GTCIV3);
					break;

				case VECTOR::GTCIA4:
				case VECTOR::GTCIB4:
					idx = static_cast<uint32_t>(VECTOR::GTCIA4);
					break;
				case VECTOR::GTCIC4:
				case VECTOR::GTCID4:
				case VECTOR::GTCIE4:
				case VECTOR::GTCIF4:
					idx = static_cast<uint32_t>(VECTOR::GTCIC4);
					break;
				case VECTOR::GTCIV4:
				case VECTOR::GTCIU4:
					idx = static_cast<uint32_t>(VECTOR::GTCIV4);
					break;

				case VECTOR::GTCIA5:
				case VECTOR::GTCIB5:
					idx = static_cast<uint32_t>(VECTOR::GTCIA5);
					break;
				case VECTOR::GTCIC5:
				case VECTOR::GTCID5:
				case VECTOR::GTCIE5:
				case VECTOR::GTCIF5:
					idx = static_cast<uint32_t>(VECTOR::GTCIC5);
					break;
				case VECTOR::GTCIV5:
				case VECTOR::GTCIU5:
					idx = static_cast<uint32_t>(VECTOR::GTCIV5);
					break;

				case VECTOR::GTCIA6:
				case VECTOR::GTCIB6:
					idx = static_cast<uint32_t>(VECTOR::GTCIA6);
					break;
				case VECTOR::GTCIC6:
				case VECTOR::GTCID6:
				case VECTOR::GTCIE6:
				case VECTOR::GTCIF6:
					idx = static_cast<uint32_t>(VECTOR::GTCIC6);
					break;
				case VECTOR::GTCIV6:
				case VECTOR::GTCIU6:
					idx = static_cast<uint32_t>(VECTOR::GTCIV6);
					break;

				case VECTOR::GTCIA7:
				case VECTOR::GTCIB7:
					idx = static_cast<uint32_t>(VECTOR::GTCIA7);
					break;
				case VECTOR::GTCIC7:
				case VECTOR::GTCID7:
				case VECTOR::GTCIE7:
				case VECTOR::GTCIF7:
					idx = static_cast<uint32_t>(VECTOR::GTCIC7);
					break;
				case VECTOR::GTCIV7:
				case VECTOR::GTCIU7:
					idx = static_cast<uint32_t>(VECTOR::GTCIV7);
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

				default: idx = static_cast<uint32_t>(vec); break;
				}
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};
		static inline ipr_t<0x0008'7300> IPR;


		/// @brief DTC 転送要求許可レジスタ  (DTCER)
		static inline dtcer_t<0x0008'7100, VECTOR> DTCER;

		/// @brief DMAC 起動要因選択レジスタ m (DMRSRm) (m = DMAC チャネル番号 )
		static inline DMRSR8N_ DMRSR;
		static inline DMRSR0_ DMRSR0;
		static inline DMRSR1_ DMRSR1;
		static inline DMRSR2_ DMRSR2;
		static inline DMRSR3_ DMRSR3;
	};
	typedef icub_t ICU;
}
