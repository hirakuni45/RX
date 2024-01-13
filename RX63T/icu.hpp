#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX63T 割り込みコントローラ・テンプレート・クラス（ICUb）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_t : public ICU_BASE, ICU_IRQ8, ICU_GROUP {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR {
			NONE	  = 0,		///< none

			BUSERR	  = 16,		///< BSC

			FIFERR	  = 21,		///< FCU

			FRDYI	  = 23,		///< FCU

			SWINT	  = 27,		///< ICU
			CMI0	  = 28,		///< CMT0
			CMI1	  = 29,		///< CMT1
			CMI2	  = 30,		///< CMT2
			CMI3	  = 31,		///< CMT3

			D0FIFO0	  = 33,		///< USB0
			D1FIFO0	  = 34,		///< USB0
			USBI0	  = 35,		///< USB0

			FERRF	  = 36,		///< CAC
			MENDF	  = 37, 	///< CAC
			OVFF	  = 38,  	///< CAC

			SPRI0	  = 39,		///< RSPI0
			SPTI0	  = 40,		///< RSPI0
			SPII0	  = 41,		///< RSPI0

			SPRI1	  = 42,		///< RSPI1
			SPTI1	  = 43,		///< RSPI1
			SPII1	  = 44,		///< RSPI1

			RXF1	  = 45,		///< CAN1
			TXF1	  = 46,		///< CAN1
			RXM1	  = 47,		///< CAN1
			TXM1	  = 48,		///< CAN1			

			GTCIA7	  = 49,  	///< GPT7
			GTCIB7	  = 50,  	///< GPT7
			GTCIC7	  = 51,  	///< GPT7
			GTCIE7	  = 52,  	///< GPT7
			GTCIV7	  = 53,  	///< GPT7

			CMP4	  = 54, 	///< コンパレータ
			CMP5	  = 55, 	///< コンパレータ
			CMP6	  = 56, 	///< コンパレータ

			DOPCF	  = 57, 	///< DOC

			RBI0	  = 58, 	///< DPC
			RBI1	  = 59, 	///< DPC
			RBI2	  = 60, 	///< DPC
			RBI3	  = 61, 	///< DPC
			RBI4	  = 62, 	///< DPC

			IRQ0	  = 64,		///< ICU
			IRQ1	  = 65,
			IRQ2	  = 66,
			IRQ3	  = 67,
			IRQ4	  = 68,
			IRQ5	  = 69,
			IRQ6	  = 70,
			IRQ7	  = 71,

			USBR0	  = 90,		///< USB

			ADI0	  = 98,		///< AD

			S12ADI	  = 102,	///< S12AD
			S12GBADI  = 103,	///< S12AD

			S12ADI1	  = 104,	///< S12AD1
			S12GBADI1 = 105,	///< S12AD1

			GROUP0    = 106,	///< ICU

			GROUP12   = 114,	///< ICU

			SCIX0	  = 122,	///< SCI12
			SCIX1	  = 123,
			SCIX2     = 124,
			SCIX3     = 125,

			TGIA0	  = 126,	///< MTU0
			TGIB0	  = 127,	///< MTU0
			TGIC0	  = 128,	///< MTU0
			TGID0	  = 129,	///< MTU0
			TCIV0	  = 130,	///< MTU0
			TGIE0	  = 131,	///< MTU0
			TGIF0	  = 132,	///< MTU0

			TGIA1	  = 133,	///< MTU1
			TGIB1	  = 134,	///< MTU1
			TCIV1	  = 135,	///< MTU1
			TCIU1	  = 136,	///< MTU1

			TGIA2	  = 137,	///< MTU2
			TGIB2	  = 138,	///< MTU2
			TCIV2	  = 139,	///< MTU2
			TCIU2	  = 140,	///< MTU2

			TGIA3	  = 141,	///< MTU3
			TGIB3	  = 142,	///< MTU3
			TGIC3	  = 143,	///< MTU3
			TGID3	  = 144,	///< MTU3
			TCIV3	  = 145,	///< MTU3

			TGIA4	  = 146,	///< MTU4
			TGIB4	  = 147,	///< MTU4
			TGIC4	  = 148,	///< MTU4
			TGID4	  = 149,	///< MTU4
			TCIV4	  = 150,	///< MTU4

			TGIU5	  = 151,	///< MTU5
			TGIV5	  = 152,	///< MTU5
			TGIW5	  = 153,	///< MTU5

			TGIA6	  = 154,	///< MTU6
			TGIB6	  = 155,	///< MTU6
			TGIC6	  = 156,	///< MTU6
			TGID6	  = 157,	///< MTU6
			TCIV6	  = 158,	///< MTU6

			TGIA7	  = 161,	///< MTU7
			TGIB7	  = 162,	///< MTU7
			TGIC7	  = 163,	///< MTU7
			TGID7	  = 164,	///< MTU7
			TCIV7	  = 165,	///< MTU7

			OEI1	  = 166,	///< POE
			OEI2	  = 167,	///< POE
			OEI3	  = 168,	///< POE
			OEI4	  = 169,	///< POE
			OEI5	  = 170,	///< POE

			CMP0	  = 171,	///< コンパレータ
			CMP1	  = 172,	///< コンパレータ
			CMP2	  = 173,	///< コンパレータ

			GTCIA4	  = 174,  	///< GPT4
			GTCIB4	  = 175,  	///< GPT4
			GTCIC4	  = 176,  	///< GPT4
			GTCIE4	  = 177,  	///< GPT4
			GTCIV4	  = 178,  	///< GPT4
			LOCOI4	  = 179,	///< GPT4

			GTCIA5	  = 180,  	///< GPT5
			GTCIB5	  = 181,  	///< GPT5
			GTCIC5	  = 182,  	///< GPT5
			GTCIE5	  = 183,  	///< GPT5
			GTCIV5	  = 184,  	///< GPT5

			GTCIA6	  = 185,  	///< GPT6
			GTCIB6	  = 186,  	///< GPT6
			GTCIC6	  = 187,  	///< GPT6
			GTCIE6	  = 188,  	///< GPT6
			GTCIV6	  = 189,  	///< GPT6

			ICEEI1	  = 190,	///< RIIC1
			ICRXI1	  = 191,	///< RIIC1
			ICTXI1	  = 192,	///< RIIC1
			ICTEI1	  = 193,	///< RIIC1

			ICEEI0	  = 194,	///< RIIC0
			ICRXI0	  = 195,	///< RIIC0
			ICTXI0	  = 196,	///< RIIC0
			ICTEI0	  = 197,	///< RIIC0

			DMACI0	  = 198,	///< DMACA
			DMACI1	  = 199,	///< DMACA
			DMACI2	  = 200,	///< DMACA
			DMACI3	  = 201,	///< DMACA

			RXI0	  = 214,	///< SCI0
			TXI0	  = 215,	///< SCI0
			TEI0	  = 216,	///< SCI0

			RXI1	  = 217,	///< SCI1
			TXI1	  = 218,	///< SCI1
			TEI1	  = 219,	///< SCI1

			RXI2	  = 220,	///< SCI2
			TXI2	  = 221,	///< SCI2
			TEI2	  = 222,	///< SCI2

			RXI3	  = 223,	///< SCI3
			TXI3	  = 224,	///< SCI3
			TEI3	  = 225,	///< SCI3

			GTCIA0	  = 226,  	///< GPT0
			GTCIB0	  = 227,  	///< GPT0
			GTCIC0	  = 228,  	///< GPT0
			GTCIE0	  = 229,  	///< GPT0
			GTCIV0	  = 230,  	///< GPT0
			LOCOI0	  = 231,	///< GPT0

			GTCIA1	  = 232,  	///< GPT1
			GTCIB1	  = 233,  	///< GPT1
			GTCIC1	  = 234,  	///< GPT1
			GTCIE1	  = 235,  	///< GPT1
			GTCIV1	  = 236,  	///< GPT1

			GTCIA2	  = 238,  	///< GPT2
			GTCIB2	  = 239,  	///< GPT2
			GTCIC2	  = 240,  	///< GPT2
			GTCIE2	  = 241,  	///< GPT2
			GTCIV2	  = 242,  	///< GPT2

			GTCIA3	  = 244,  	///< GPT3
			GTCIB3	  = 245,  	///< GPT3
			GTCIC3	  = 246,  	///< GPT3
			GTCIE3	  = 247,  	///< GPT3
			GTCIV3	  = 248,  	///< GPT3

			RXI12	  = 250,	///< SCI12
			TXI12	  = 251,	///< SCI12
			TEI12	  = 252,	///< SCI12
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP0 ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP0 : uint8_t {
			ERS1 = 1,	///< CAN1
			NUM_ = 1
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP12 ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP12 : uint8_t {
			ERI0 = 0,	///< SCI0
			ERI1,		///< SCI1
			ERI2,		///< SCI2
			ERI3,		///< SCI3
			ERI12,		///< SCI12
			SPEI0,		///< RSPI0
			SPEI1,		///< RSPI1
			NUM_
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
				case VECTOR::FERRF:
				case VECTOR::MENDF:
				case VECTOR::OVFF:
					idx = static_cast<uint32_t>(VECTOR::FERRF);
					break;
				case VECTOR::RXF1:
				case VECTOR::TXF1:
				case VECTOR::RXM1:
				case VECTOR::TXM1:
					idx = static_cast<uint32_t>(VECTOR::RXF1);
					break;
				case VECTOR::GTCIA7:
				case VECTOR::GTCIB7:
				case VECTOR::GTCIC7:
					idx = static_cast<uint32_t>(VECTOR::GTCIA7);
					break;
				case VECTOR::GTCIE7:
				case VECTOR::GTCIV7:
					idx = static_cast<uint32_t>(VECTOR::GTCIE7);
					break;
				case VECTOR::SCIX0:
				case VECTOR::SCIX1:
				case VECTOR::SCIX2:
				case VECTOR::SCIX3:
					idx = static_cast<uint32_t>(VECTOR::SCIX0);
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
				case VECTOR::TGIA4:
				case VECTOR::TGIB4:
				case VECTOR::TGIC4:
				case VECTOR::TGID4:
					idx = static_cast<uint32_t>(VECTOR::TGIA4);
					break;
				case VECTOR::TGIU5:
				case VECTOR::TGIV5:
				case VECTOR::TGIW5:
					idx = static_cast<uint32_t>(VECTOR::TGIU5);
					break;
				case VECTOR::TGIA6:
				case VECTOR::TGIB6:
				case VECTOR::TGIC6:
				case VECTOR::TGID6:
					idx = static_cast<uint32_t>(VECTOR::TGIA6);
					break;
				case VECTOR::TGIA7:
				case VECTOR::TGIB7:
					idx = static_cast<uint32_t>(VECTOR::TGIA7);
					break;
				case VECTOR::TGIC7:
				case VECTOR::TGID7:
					idx = static_cast<uint32_t>(VECTOR::TGIC7);
					break;
				case VECTOR::OEI1:
				case VECTOR::OEI2:
				case VECTOR::OEI3:
				case VECTOR::OEI4:
				case VECTOR::OEI5:
					idx = static_cast<uint32_t>(VECTOR::OEI1);
					break;
				case VECTOR::GTCIA4:
				case VECTOR::GTCIB4:
				case VECTOR::GTCIC4:
					idx = static_cast<uint32_t>(VECTOR::GTCIA4);
					break;
				case VECTOR::GTCIE4:
				case VECTOR::GTCIV4:
				case VECTOR::LOCOI4:
					idx = static_cast<uint32_t>(VECTOR::GTCIE4);
					break;
				case VECTOR::GTCIA5:
				case VECTOR::GTCIB5:
				case VECTOR::GTCIC5:
					idx = static_cast<uint32_t>(VECTOR::GTCIA5);
					break;
				case VECTOR::GTCIE5:
				case VECTOR::GTCIV5:
					idx = static_cast<uint32_t>(VECTOR::GTCIE5);
					break;
				case VECTOR::GTCIA6:
				case VECTOR::GTCIB6:
				case VECTOR::GTCIC6:
					idx = static_cast<uint32_t>(VECTOR::GTCIA6);
					break;
				case VECTOR::GTCIE6:
				case VECTOR::GTCIV6:
					idx = static_cast<uint32_t>(VECTOR::GTCIE6);
					break;
				case VECTOR::ICEEI1:
				case VECTOR::ICRXI1:
				case VECTOR::ICTXI1:
				case VECTOR::ICTEI1:
					idx = static_cast<uint32_t>(VECTOR::ICEEI1);
					break;
				case VECTOR::ICEEI0:
				case VECTOR::ICRXI0:
				case VECTOR::ICTXI0:
				case VECTOR::ICTEI0:
					idx = static_cast<uint32_t>(VECTOR::ICEEI0);
					break;
				case VECTOR::RXI0:
				case VECTOR::TXI0:
				case VECTOR::TEI0:
					idx = static_cast<uint32_t>(VECTOR::RXI0);
					break;
				case VECTOR::RXI1:
				case VECTOR::TXI1:
				case VECTOR::TEI1:
					idx = static_cast<uint32_t>(VECTOR::RXI1);
					break;
				case VECTOR::RXI2:
				case VECTOR::TXI2:
				case VECTOR::TEI2:
					idx = static_cast<uint32_t>(VECTOR::RXI2);
					break;
				case VECTOR::RXI3:
				case VECTOR::TXI3:
				case VECTOR::TEI3:
					idx = static_cast<uint32_t>(VECTOR::RXI3);
					break;
				case VECTOR::GTCIA0:
				case VECTOR::GTCIB0:
				case VECTOR::GTCIC0:
					idx = static_cast<uint32_t>(VECTOR::GTCIA0);
					break;
				case VECTOR::GTCIE0:
				case VECTOR::GTCIV0:
				case VECTOR::LOCOI0:
					idx = static_cast<uint32_t>(VECTOR::GTCIE0);
					break;
				case VECTOR::GTCIA1:
				case VECTOR::GTCIB1:
				case VECTOR::GTCIC1:
					idx = static_cast<uint32_t>(VECTOR::GTCIA1);
					break;
				case VECTOR::GTCIE1:
				case VECTOR::GTCIV1:
					idx = static_cast<uint32_t>(VECTOR::GTCIE1);
					break;
				case VECTOR::GTCIA2:
				case VECTOR::GTCIB2:
				case VECTOR::GTCIC2:
					idx = static_cast<uint32_t>(VECTOR::GTCIA2);
					break;
				case VECTOR::GTCIE2:
				case VECTOR::GTCIV2:
					idx = static_cast<uint32_t>(VECTOR::GTCIE2);
					break;
				case VECTOR::GTCIA3:
				case VECTOR::GTCIB3:
				case VECTOR::GTCIC3:
					idx = static_cast<uint32_t>(VECTOR::GTCIA3);
					break;
				case VECTOR::GTCIE3:
				case VECTOR::GTCIV3:
					idx = static_cast<uint32_t>(VECTOR::GTCIE3);
					break;
				case VECTOR::RXI12:
				case VECTOR::TXI12:
				case VECTOR::TEI12:
					idx = static_cast<uint32_t>(VECTOR::RXI12);
					break;
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
		static DMRSR4N_ DMRSR;
		static DMRSR0_ DMRSR0;
		static DMRSR1_ DMRSR1;
		static DMRSR2_ DMRSR2;
		static DMRSR3_ DMRSR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ 0 割り込み要因レジスタ（GRP00）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef grp_t<0x0008'C300, GROUP0> GRP00_;
		static GRP00_ GRP00;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ 12 割り込み要因レジスタ（GRP12）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef grp_t<0x0008'C330, GROUP12> GRP12_;
		static GRP12_ GRP12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ 0 割り込み許可レジスタ（GEN00）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gen_t<0x0008'C340, GROUP0> GEN00_;
		static GEN00_ GEN00;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ 12 割り込み許可レジスタ（GEN12）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gen_t<0x0008'C370, GROUP12> GEN12_;
		static GEN12_ GEN12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ 0 割り込みクリアレジスタ（GCR00）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gcr_t<0x0008'C380, GROUP0> GCR00_;
		static GCR00_ GCR00;
	};
	template<class _> typename icu_t<_>::IR_ icu_t<_>::IR;
	template<class _> typename icu_t<_>::IER_ icu_t<_>::IER;
	template<class _> typename icu_t<_>::IPR_ icu_t<_>::IPR;
	template<class _> typename icu_t<_>::DTCER_ icu_t<_>::DTCER;
	template<class _> typename icu_t<_>::DMRSR4N_ icu_t<_>::DMRSR;
	template<class _> typename icu_t<_>::DMRSR0_ icu_t<_>::DMRSR0;
	template<class _> typename icu_t<_>::DMRSR1_ icu_t<_>::DMRSR1;
	template<class _> typename icu_t<_>::DMRSR2_ icu_t<_>::DMRSR2;
	template<class _> typename icu_t<_>::DMRSR3_ icu_t<_>::DMRSR3;
	template<class _> typename icu_t<_>::GRP00_ icu_t<_>::GRP00;
	template<class _> typename icu_t<_>::GRP12_ icu_t<_>::GRP12;
	template<class _> typename icu_t<_>::GEN00_ icu_t<_>::GEN00;
	template<class _> typename icu_t<_>::GEN12_ icu_t<_>::GEN12;
	template<class _> typename icu_t<_>::GCR00_ icu_t<_>::GCR00;

	typedef icu_t<void> ICU;
}
