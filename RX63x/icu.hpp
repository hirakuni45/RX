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
		@brief  RX631/RX63N 割り込みコントローラ・テンプレート・クラス（ICUb）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t : public ICU_BASE, ICU_IRQ16, ICU_GROUP {

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

			RXF0		= 48,  ///< CAN0
			TXF0		= 49,
			RXM0		= 50,
			TXM0		= 51,
			RXF1		= 52,  ///< CAN1
			TXF1		= 53,
			RXM1		= 54,
			TXM1		= 55,
			RXF2		= 56,  ///< CAN2
			TXF2		= 57,
			RXM2		= 58,
			TXM2		= 59,

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

			S12ADI0		= 102,	///< S12AD

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

			DMACI0		= 198,	///< DMAC
			DMACI1		= 199,
			DMACI2		= 200,
			DMACI3		= 201,

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
			@brief  GROUP0 型（レベル割り込み）
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
			@brief  GROUP1 型（レベル割り込み）
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
			@brief  GROUP2 型（レベル割り込み）
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
			@brief  GROUP3 型（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP3 : uint8_t {
			TCI0V = 0,		///< TPU0
			TCI1V = 1,		///< TPU1
			TCI1U,
			TCI5V = 3,		///< TPU5
			TCI5U,
			NUM_ = 5
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP4 型（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP4 : uint8_t {
			TCI2V = 0,		///< TPU2
			TCI2U,
			TCI3V = 2,		///< TPU3
			TCI4V = 3,		///< TPU4
			TCI4U,
			NUM_ = 5
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP5 型（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP5 : uint8_t {
			TCI6V  = 0,		///< TPU6
			TCI7V  = 1,		///< TPU7
			TCI7U,
			TCI11V = 3,		///< TPU11
			TCI11U,
			NUM_ = 5
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP6 型（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP6 : uint8_t {
			TCI8V  = 0,		///< TPU8
			TCI8U,
			TCI9V  = 2,		///< TPU9
			TCI10V = 3,		///< TPU10
			TCI10U,
			NUM_ = 5
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP12 型（エッジ割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP12 : uint8_t {
			ERI0  = 0,	///< SCI0
			ERI1  = 1,	///< SCI1
			ERI2  = 2,	///< SCI2
			ERI3  = 3,	///< SCI3
			ERI4  = 4,	///< SCI4
			ERI5  = 5,	///< SCI5
			ERI6  = 6,	///< SCI6
			ERI7  = 7,	///< SCI7
			ERI8  = 8,	///< SCI8
			ERI9  = 9,	///< SCI9
			ERI10 = 10,	///< SCI10
			ERI11 = 11,	///< SCI11
			ERI12 = 12,	///< SCI12
			SPEI0 = 13,	///< RSPI0
			SPEI1 = 14,	///< RSPI1
			SPEI2 = 15,	///< RSPI2
			NUM_ = 16
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
				case VECTOR::FIFERR: idx = 1; break;
				case VECTOR::FRDYI:  idx = 2; break;
				case VECTOR::SWINT:  idx = 3; break;
				case VECTOR::CMI0:   idx = 4; break;
				case VECTOR::CMI1:   idx = 5; break;
				case VECTOR::CMI2:   idx = 6; break;
				case VECTOR::CMI3:   idx = 7; break;
				case VECTOR::SPRI0:
				case VECTOR::SPTI0:
				case VECTOR::SPII0:
					idx = static_cast<uint32_t>(VECTOR::SPRI0);
					break;
				case VECTOR::SPRI1:
				case VECTOR::SPTI1:
				case VECTOR::SPII1:
					idx = static_cast<uint32_t>(VECTOR::SPRI1);
					break;
				case VECTOR::SPRI2:
				case VECTOR::SPTI2:
				case VECTOR::SPII2:
					idx = static_cast<uint32_t>(VECTOR::SPRI2);
					break;
				case VECTOR::RXF0:
				case VECTOR::TXF0:
				case VECTOR::RXM0:
				case VECTOR::TXM0:
					idx = static_cast<uint32_t>(VECTOR::RXF0);
					break;
				case VECTOR::RXF1:
				case VECTOR::TXF1:
				case VECTOR::RXM1:
				case VECTOR::TXM1:
					idx = static_cast<uint32_t>(VECTOR::RXF1);
					break;
				case VECTOR::RXF2:
				case VECTOR::TXF2:
				case VECTOR::RXM2:
				case VECTOR::TXM2:
					idx = static_cast<uint32_t>(VECTOR::RXF2);
					break;
				case VECTOR::SCIX0:
				case VECTOR::SCIX1:
				case VECTOR::SCIX2:
				case VECTOR::SCIX3:
					idx = static_cast<uint32_t>(VECTOR::SCIX0);
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
				case VECTOR::TGI2A:
				case VECTOR::TGI2B:
					idx = static_cast<uint32_t>(VECTOR::TGI2A);
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
				case VECTOR::TGI5A:
				case VECTOR::TGI5B:
					idx = static_cast<uint32_t>(VECTOR::TGI5A);
					break;
				case VECTOR::TGI6A:  // TGIA0
				case VECTOR::TGI6B:  // TGIB0
				case VECTOR::TGI6C:  // TGIC0
				case VECTOR::TGI6D:  // TGID0
					idx = static_cast<uint32_t>(VECTOR::TGI6A);
					break;
				case VECTOR::TGIE0:
				case VECTOR::TGIF0:
					idx = static_cast<uint32_t>(VECTOR::TGIE0);
					break;
				case VECTOR::TGI7A:  // TGIA1
				case VECTOR::TGI7B:  // TGIB1
					idx = static_cast<uint32_t>(VECTOR::TGI7A);
					break;
				case VECTOR::TGI8A:  // TGIA2
				case VECTOR::TGI8B:  // TGIB2
					idx = static_cast<uint32_t>(VECTOR::TGI8A);
					break;
				case VECTOR::TGI9A:  // TGIA3
				case VECTOR::TGI9B:  // TGIB3
				case VECTOR::TGI9C:  // TGIC3
				case VECTOR::TGI9D:  // TGID3
					idx = static_cast<uint32_t>(VECTOR::TGI9A);
					break;
				case VECTOR::TGI10A:  // TGIA4
				case VECTOR::TGI10B:  // TGIB4
				case VECTOR::TGIC4:
				case VECTOR::TGID4:
					idx = static_cast<uint32_t>(VECTOR::TGI10A);
					break;
				case VECTOR::TGIU5:
				case VECTOR::TGIV5:
				case VECTOR::TGIW5:
					idx = static_cast<uint32_t>(VECTOR::TGIU5);
					break;
				case VECTOR::TGI11A:
				case VECTOR::TGI11B:
					idx = static_cast<uint32_t>(VECTOR::TGI11A);
					break;
				case VECTOR::OEI1:
				case VECTOR::OEI2:
					idx = static_cast<uint32_t>(VECTOR::OEI1);
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
				case VECTOR::RXI4:
				case VECTOR::TXI4:
				case VECTOR::TEI4:
					idx = static_cast<uint32_t>(VECTOR::RXI4);
					break;
				case VECTOR::RXI5:
				case VECTOR::TXI5:
				case VECTOR::TEI5:
					idx = static_cast<uint32_t>(VECTOR::RXI5);
					break;
				case VECTOR::RXI6:
				case VECTOR::TXI6:
				case VECTOR::TEI6:
					idx = static_cast<uint32_t>(VECTOR::RXI6);
					break;
				case VECTOR::RXI7:
				case VECTOR::TXI7:
				case VECTOR::TEI7:
					idx = static_cast<uint32_t>(VECTOR::RXI7);
					break;
				case VECTOR::RXI8:
				case VECTOR::TXI8:
				case VECTOR::TEI8:
					idx = static_cast<uint32_t>(VECTOR::RXI8);
					break;
				case VECTOR::RXI9:
				case VECTOR::TXI9:
				case VECTOR::TEI9:
					idx = static_cast<uint32_t>(VECTOR::RXI9);
					break;
				case VECTOR::RXI10:
				case VECTOR::TXI10:
				case VECTOR::TEI10:
					idx = static_cast<uint32_t>(VECTOR::RXI10);
					break;
				case VECTOR::RXI11:
				case VECTOR::TXI11:
				case VECTOR::TEI11:
					idx = static_cast<uint32_t>(VECTOR::RXI11);
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
		static inline ipr_t<0x0008'7300> IPR;

		/// @brief DTC 転送要求許可レジスタ  (DTCER)
		static inline dtcer_t<0x0008'7100, VECTOR> DTCER;

		/// @brief DMAC 起動要因選択レジスタ m (DMRSRm) (m = DMAC チャネル番号 )
		static inline DMRSR8N_ DMRSR;
		static inline DMRSR0_ DMRSR0;
		static inline DMRSR1_ DMRSR1;
		static inline DMRSR2_ DMRSR2;
		static inline DMRSR3_ DMRSR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ m 割り込み要因レジスタ（GRPm）(m= グループ番号 ) @n
					GROUP0 ～ GROUP6, GROUP12
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline grp_t<0x0008'C300, GROUP0> GRP00;
		static inline grp_t<0x0008'C304, GROUP1> GRP01;
		static inline grp_t<0x0008'C308, GROUP2> GRP02;
		static inline grp_t<0x0008'C30C, GROUP3> GRP03;
		static inline grp_t<0x0008'C310, GROUP4> GRP04;
		static inline grp_t<0x0008'C314, GROUP5> GRP05;
		static inline grp_t<0x0008'C318, GROUP6> GRP06;
		static inline grp_t<0x0008'C330, GROUP12> GRP12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ m 割り込み許可レジスタ（GENm）(m= グループ番号 ) @n
					GROUP0 ～ GROUP6, GROUP12
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline gen_t<0x0008'C340, GROUP0> GEN00;
		static inline gen_t<0x0008'C344, GROUP1> GEN01;
		static inline gen_t<0x0008'C348, GROUP2> GEN02;
		static inline gen_t<0x0008'C34C, GROUP3> GEN03;
		static inline gen_t<0x0008'C350, GROUP4> GEN04;
		static inline gen_t<0x0008'C354, GROUP5> GEN05;
		static inline gen_t<0x0008'C358, GROUP6> GEN06;
		static inline gen_t<0x0008'C370, GROUP12> GEN12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ m 割り込みクリアレジスタ（GCRm）(m= グループ番号 )
					GROUP0 ～ GROUP6
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gcr_t<0x0008'C380, GROUP0> GCR00_;
		typedef gcr_t<0x0008'C384, GROUP1> GCR01_;
		typedef gcr_t<0x0008'C388, GROUP2> GCR02_;
		typedef gcr_t<0x0008'C38C, GROUP3> GCR03_;
		typedef gcr_t<0x0008'C390, GROUP4> GCR04_;
		typedef gcr_t<0x0008'C394, GROUP5> GCR05_;
		typedef gcr_t<0x0008'C398, GROUP6> GCR06_;
		static inline GCR00_ GCR00;
		static inline GCR01_ GCR01;
		static inline GCR02_ GCR02;
		static inline GCR03_ GCR03;
		static inline GCR04_ GCR04;
		static inline GCR05_ GCR05;
		static inline GCR06_ GCR06;
	};
	typedef icu_t ICU;
}
