#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ICUb 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX600/icu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX24T 割り込みコントローラ・テンプレート・クラス（ICUb）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_t : public ICU_BASE, ICU_IRQ8 {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常割り込みベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {
			NONE    = 0,	///< none

			BUSERR  = 16,   ///< BSC

			FRDYI   = 23,   ///< FCU

			SWINT   = 27,   ///< ICU
			CMI0    = 28,   ///< CMT0
			CMI1    = 29,   ///< CMT1
			CMI2    = 30,   ///< CMT2
			CMI3    = 31,   ///< CMT3

			FERRF   = 32,	///< CAC
			MENDF   = 33,	///< CAC
			OVFF    = 34,	///< CAC

			ETGIN   = 40,	///< GPT
			ETGIP   = 41,	///< GPT

			SPEI0   = 44,	///< RSPI0
			SPRI0   = 45,	///< RSPI0
			SPTI0   = 46,	///< RSPI0
			SPII0   = 47,	///< RSPI0

			GTCIA0  = 48,	///< GPT0
			GTCIB0  = 49,
			GTCIC0  = 50,
			GTCID0  = 51,
			GDTE0   = 52,
			GTCIE0  = 53,
			GTCIF0  = 54,
			GTCIV0  = 55,
			GTCIU0  = 56,

			DOPCF   = 57,	///< DOC

			COMFRXINT = 59,	///< RSCAN
			RXFINT    = 60,
			TXINT     = 61,
			CHERRINT  = 62,
			GLERRINT  = 63,

			IRQ0    = 64,	///< ICU
			IRQ1    = 65,
			IRQ2    = 66,
			IRQ3    = 67,
			IRQ4    = 68,
			IRQ5    = 69,
			IRQ6    = 70,
			IRQ7    = 71,

			LVD1    = 88,   ///< LVD
			LVD2    = 89,   ///< LVD

			GTCIA1  = 98,	///< GPT1
			GTCIB1  = 99,
			GTCIC1  = 100,
			GTCID1  = 101,

			S12ADI  = 102,  ///< S12AD
			GBADI   = 103,
			GCADI   = 104,
			S12ADI1 = 105,  ///< S12ADI1
			GBADI1  = 106,
			GCADI1  = 107,
			CMPC0   = 108,  ///< CMPC0
			CMPC1   = 109,  ///< CMPC1
			CMPC2   = 110,  ///< CMPC2
			S12ADI2 = 111,  ///< S12AD2
			GBADI2  = 112,
			GCADI2  = 113,

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

			TGIA6   = 142,  ///< MTU6
			TGIB6   = 143,  ///< MTU6
			TGIC6   = 144,  ///< MTU6
			TGID6   = 145,  ///< MTU6
			TCIV6   = 146,  ///< MTU6

			TGIA7   = 149,  ///< MTU7
			TGIB7   = 150,  ///< MTU7
			TGIC7   = 151,  ///< MTU7
			TGID7   = 152,  ///< MTU7
			TCIV7   = 153,  ///< MTU7

			TGIA9   = 159,  ///< MTU9
			TGIB9   = 160,  ///< MTU9
			TGIC9   = 161,  ///< MTU9
			TGID9   = 162,  ///< MTU9
			TCIV9   = 163,  ///< MTU9
			TGIE9   = 164,  ///< MTU9
			TGIF9   = 165,  ///< MTU9

			OEI1	= 168,	///< POE
			OEI2	= 169,	///< POE
			OEI3	= 170,	///< POE
			OEI4	= 171,	///< POE
			OEI5	= 172,	///< POE

			CMPC3   = 173,  ///< CMPC3

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
			CMIA4   = 186,	///< TMR4: CMIA4
			CMIB4   = 187,	///< TMR4: CMIB4
			OVI4    = 188,	///< TMR4: OVI4
			CMIA5   = 189,	///< TMR5: CMIA5
			CMIB5   = 190,	///< TMR5: CMIB5
			OVI5    = 191,	///< TMR5: OVI5
			CMIA6   = 192,	///< TMR6: CMIA6
			CMIB6   = 193,	///< TMR6: CMIB6
			OVI6    = 194,	///< TMR6: OVI6
			CMIA7   = 195,	///< TMR7: CMIA7
			CMIB7   = 196,	///< TMR7: CMIB7
			OVI7    = 197,	///< TMR7: OVI7

			GDTE1   = 202,	///< GPT1
			GTCIE1  = 203,
			GTCIF1  = 204,
			GTCIV1  = 205,
			GTCIU1  = 206,
			GTCIA2  = 207,	///< GPT2
			GTCIB2  = 208,
			GTCIC2  = 209,
			GTCID2  = 210,
			GDTE2   = 211,
			GTCIE2  = 212,
			GTCIF2  = 213,
			GTCIV2  = 214,
			GTCIU2  = 215,
			GTCIA3  = 216,  ///< GPT3
			GTCIB3  = 217,

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

			GTCIC3  = 238, 	///< GPT3
			GTCID3  = 239,
			GDTE3   = 240,
			GTCIE3  = 241,
			GTCIF3  = 242,
			GTCIV3  = 243,
			GTCIU3  = 244,

			ICEEI0  = 246,  ///< RIIC0
			ICRXI0  = 247,  ///< RIIC0
			ICTXI0  = 248,  ///< RIIC0
			ICTEI0  = 249,  ///< RIIC0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ・クラス
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
			@brief  IPR レジスタ・クラス @n
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
				case VECTOR::BUSERR: idx = 0; break;
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
					idx = 44;
					break;
				case VECTOR::TGIA0:
				case VECTOR::TGIB0:
				case VECTOR::TGIC0:
				case VECTOR::TGID0:
					idx = 114;
					break;
				case VECTOR::TCIV0:
				case VECTOR::TGIE0:
				case VECTOR::TGIF0:
					idx = 118;
					break;
				case VECTOR::TGIA1:
				case VECTOR::TGIB1:
					idx = 121;
					break;
				case VECTOR::TCIV1:
				case VECTOR::TCIU1:
					idx = 123;
					break;
				case VECTOR::TGIA2:
				case VECTOR::TGIB2:
					idx = 125;
					break;
				case VECTOR::TCIV2:
				case VECTOR::TCIU2:
					idx = 127;
					break;
				case VECTOR::TGIA3:
				case VECTOR::TGIB3:
				case VECTOR::TGIC3:
				case VECTOR::TGID3:
					idx = 129;
					break;
				case VECTOR::TCIV3:
					idx = 133;
					break;
				case VECTOR::TGIA4:
				case VECTOR::TGIB4:
				case VECTOR::TGIC4:
				case VECTOR::TGID4:
					idx = 134;
					break;
				case VECTOR::TCIV4:
					idx = 138;
					break;
				case VECTOR::TGIU5:
				case VECTOR::TGIV5:
				case VECTOR::TGIW5:
					idx = 139;
					break;
				case VECTOR::TGIA6:
				case VECTOR::TGIB6:
				case VECTOR::TGIC6:
				case VECTOR::TGID6:
					idx = 142;
					break;
				case VECTOR::TCIV6:
					idx = 146;
					break;
				case VECTOR::TGIA7:
				case VECTOR::TGIB7:
					idx = 149;
					break;
				case VECTOR::TGIC7:
				case VECTOR::TGID7:
					idx = 151;
					break;
				case VECTOR::TCIV7:
					idx = 153;
					break;
				case VECTOR::TGIA9:
				case VECTOR::TGIB9:
				case VECTOR::TGIC9:
				case VECTOR::TGID9:
					idx = 159;
					break;
				case VECTOR::TCIV9:
				case VECTOR::TGIE9:
				case VECTOR::TGIF9:
					idx = 163;
					break;
				case VECTOR::CMIA0:
				case VECTOR::CMIB0:
				case VECTOR::OVI0:
					idx = 174;
					break;
				case VECTOR::CMIA1:
				case VECTOR::CMIB1:
				case VECTOR::OVI1:
					idx = 177;
					break;
				case VECTOR::CMIA2:
				case VECTOR::CMIB2:
				case VECTOR::OVI2:
					idx = 180;
					break;
				case VECTOR::CMIA3:
				case VECTOR::CMIB3:
				case VECTOR::OVI3:
					idx = 183;
					break;
				case VECTOR::CMIA4:
				case VECTOR::CMIB4:
				case VECTOR::OVI4:
					idx = 186;
					break;
				case VECTOR::CMIA5:
				case VECTOR::CMIB5:
				case VECTOR::OVI5:
					idx = 189;
					break;
				case VECTOR::CMIA6:
				case VECTOR::CMIB6:
				case VECTOR::OVI6:
					idx = 192;
					break;
				case VECTOR::CMIA7:
				case VECTOR::CMIB7:
				case VECTOR::OVI7:
					idx = 195;
					break;
				case VECTOR::ERI1:
				case VECTOR::RXI1:
				case VECTOR::TXI1:
				case VECTOR::TEI1:
					idx = 218;
					break;
				case VECTOR::ERI5:
				case VECTOR::RXI5:
				case VECTOR::TXI5:
				case VECTOR::TEI5:
					idx = 222;
					break;
				case VECTOR::ERI6:
				case VECTOR::RXI6:
				case VECTOR::TXI6:
				case VECTOR::TEI6:
					idx = 226;
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
	};
	typedef icu_t<void> ICU;

	template<class _> typename icu_t<_>::IR_ icu_t<_>::IR;
	template<class _> typename icu_t<_>::IER_ icu_t<_>::IER;
	template<class _> typename icu_t<_>::IPR_ icu_t<_>::IPR;
	template<class _> typename icu_t<_>::DTCER_ icu_t<_>::DTCER;
}
