#pragma once
//=========================================================================//
/*!	@file
	@brief	RX113/RX130/RX140/RX230/RX231/RX23W グループ・CMPBa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ B_01
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb01_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B 制御レジスタ 1（CPBCNT1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbcnt1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0INI;

			bit_rw_t <io_, bitpos::B4>     CPB1INI;
		};
		static inline cpbcnt1_t<0x0008'C580> CPBCNT1;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B 制御レジスタ 2（CPBCNT2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbcnt2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0WCP;

			bit_rw_t <io_, bitpos::B4>     CPB1WCP;
		};
		static inline cpbcnt2_t<0x0008'C581> CPBCNT2;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B フラグレジスタ（CPBFLG）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbflg_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0OUT;

			bit_rw_t <io_, bitpos::B4>     CPB1OUT;
		};
		static inline cpbflg_t<0x0008'C582> CPBFLG;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B 割り込み制御レジスタ（CPBINT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbint_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0INTEN;
			bit_rw_t <io_, bitpos::B1>     CPB0INTEG;
			bit_rw_t <io_, bitpos::B2>     CPB0INTPL;

			bit_rw_t <io_, bitpos::B4>     CPB1INTEN;
			bit_rw_t <io_, bitpos::B5>     CPB1INTEG;
			bit_rw_t <io_, bitpos::B6>     CPB1INTPL;
		};
		static inline cpbint_t<0x0008'C583> CPBINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B フィルタ選択レジスタ（CPBF）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbf_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0FEN;

			bits_rw_t<io_, bitpos::B2, 2>  CPB0F;
			bit_rw_t <io_, bitpos::B4>     CPB1FEN;

			bits_rw_t<io_, bitpos::B6, 2>  CPB1F;
		};
		static inline cpbf_t<0x0008'C584> CPBF;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B モード選択レジスタ（CPBMD）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbmd_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPBSPDMD;
		};
		static inline cpbmd_t<0x0008'C585> CPBMD;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B リファレンス入力電圧選択レジスタ（CPBREF）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbref_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0VRF;

			bit_rw_t <io_, bitpos::B4>     CPB1VRF;
		};
		static inline cpbref_t<0x0008'C586> CPBREF;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B 出力制御レジスタ（CPBOCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbocr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0OE;
			bit_rw_t <io_, bitpos::B1>     CPB0OP;

			bit_rw_t <io_, bitpos::B4>     CPB1OE;
			bit_rw_t <io_, bitpos::B5>     CPB1OP;
		};
		static inline cpbocr_t<0x0008'C587> CPBOCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ B_23
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb23_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 制御レジスタ 1（CPB1CNT1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1cnt1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB2INI;

			bit_rw_t <io_, bitpos::B4>     CPB3INI;
		};
		static inline cpb1cnt1_t<0x0008'C5A0> CPB1CNT1;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 制御レジスタ 2（CPB1CNT2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1cnt2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB2WCP;

			bit_rw_t <io_, bitpos::B4>     CPB3WCP;
		};
		static inline cpb1cnt2_t<0x0008'C5A1> CPB1CNT2;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 フラグレジスタ（CPB1FLG）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1flg_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B3>     CPB2OUT;

			bit_rw_t <io_, bitpos::B7>     CPB3OUT;
		};
		static inline cpb1flg_t<0x0008'C5A2> CPB1FLG;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 割り込み制御レジスタ（CPB1INT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1int_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB2INTEN;
			bit_rw_t <io_, bitpos::B1>     CPB2INTEG;
			bit_rw_t <io_, bitpos::B2>     CPB2INTPL;

			bit_rw_t <io_, bitpos::B4>     CPB3INTEN;
			bit_rw_t <io_, bitpos::B5>     CPB3INTEG;
			bit_rw_t <io_, bitpos::B6>     CPB3INTPL;
		};
		static inline cpb1int_t<0x0008'C5A3> CPB1INT;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 フィルタ選択レジスタ（CPB1F）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1f_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB2FEN;

			bits_rw_t<io_, bitpos::B2, 2>  CPB2F;
			bit_rw_t <io_, bitpos::B4>     CPB3FEN;

			bits_rw_t<io_, bitpos::B6, 2>  CPB3F;
		};
		static inline cpb1f_t<0x0008'C5A4> CPB1F;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 モード選択レジスタ（CPB1MD）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1md_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB1SPDMD;
		};
		static inline cpb1md_t<0x0008'C5A5> CPB1MD;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 リファレンス入力電圧選択レジスタ（CPB1REF）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1ref_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB2VRF;

			bit_rw_t <io_, bitpos::B4>     CPB3VRF;
		};
		static inline cpb1ref_t<0x0008'C5A6> CPB1REF;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B1 出力制御レジスタ（CPB1OCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpb1ocr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB2OE;
			bit_rw_t <io_, bitpos::B1>     CPB2OP;

			bit_rw_t <io_, bitpos::B4>     CPB3OE;
			bit_rw_t <io_, bitpos::B5>     CPB3OP;
		};
		static inline cpb1ocr_t<0x0008'C5A7> CPB1OCR;
	};

#if defined(SIG_RX113)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX113 コンパレータ B（CMPBa）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb_t : public cmpb01_t {

		static constexpr auto PERIPHERAL = peripheral::CMPB;	///< ペリフェラル型
		static constexpr uint32_t CH_NUM = 2;					///< CMP channel num
		static constexpr auto LVD1  = ICU::VECTOR::LVD1;		///< LVD1 割り込みベクター
		static constexpr auto LVD2  = ICU::VECTOR::LVD2;		///< LVD2 割り込みベクター
		static constexpr auto CMPB0 = ICU::VECTOR::CMPB0;		///< CMPB0 割り込みベクター
		static constexpr auto CMPB1 = ICU::VECTOR::CMPB1;		///< CMPB1 割り込みベクター
		static constexpr auto CMPB2 = ICU::VECTOR::NONE;		///< CMPB2 割り込みベクター
		static constexpr auto CMPB3 = ICU::VECTOR::NONE;		///< CMPB3 割り込みベクター

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			CMPA2,		///< P27/CMPA2 入力
			CMPB0,		///< PE1/CMPB0 入力
			CVREFB0,	///< PE2/CVREFB0 入力
			CMPB1,		///< PA3/CMPB1 入力
			CVREFB1,	///< PA4/CVREFB1 入力
			CMPOB0,		///< PE7/CMPOB1 出力
			CMPOB1,		///< PE5/CMPOB1 出力
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ型
			@param[in]	ena	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true)
		{
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::CMPA2:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::CMPB0:
				if(ena) {
					PORTE::PDR.B1 = 0;
					PORTE::PMR.B1 = 0;
				}
				MPC::PE1PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB0:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::CMPB1:
				if(ena) {
					PORTA::PDR.B3 = 0;
					PORTA::PMR.B3 = 0;
				}
				MPC::PA3PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB1:
				if(ena) {
					PORTA::PDR.B4 = 0;
					PORTA::PMR.B4 = 0;
				}
				MPC::PA4PFS.ASEL = ena;
				break;
			case ANALOG::CMPOB0:
				if(ena) {
					PORTE::PDR.B7 = ena;
					PORTE::PMR.B7 = 0;
				}
				break;
			case ANALOG::CMPOB1:
				if(ena) {
					PORTE::PDR.B5 = ena;
					PORTE::PMR.B5 = 0;
				}
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
#elif defined(SIG_RX130) || defined(SIG_RX140) || defined(SIG_RX260) || defined(SIG_RX261)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ B（CMPBa）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb_t : public cmpb01_t {

		static constexpr auto PERIPHERAL = peripheral::CMPB;	///< ペリフェラル型
		static constexpr uint32_t CH_NUM = 2;					///< CMP channel num
		static constexpr auto LVD1  = ICU::VECTOR::LVD1;		///< LVD1 割り込みベクター
		static constexpr auto LVD2  = ICU::VECTOR::LVD2;		///< LVD2 割り込みベクター
		static constexpr auto CMPB0 = ICU::VECTOR::CMPB0;		///< CMPB0 割り込みベクター
		static constexpr auto CMPB1 = ICU::VECTOR::CMPB1;		///< CMPB1 割り込みベクター
		static constexpr auto CMPB2 = ICU::VECTOR::NONE;		///< CMPB2 割り込みベクター
		static constexpr auto CMPB3 = ICU::VECTOR::NONE;		///< CMPB3 割り込みベクター

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			CMPA2,		///< PE4/CMPA2 入力
			CMPB0,		///< PE1/CMPB0 入力
			CVREFB0,	///< PE2/CVREFB0 入力
			CMPB1,		///< PA3/CMPB1 入力
			CVREFB1,	///< PA4/CVREFB1 入力
			CMPOB0,		///< PE5/CMPOB1 出力
			CMPOB1,		///< PB1/CMPOB1 出力
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ型
			@param[in]	ena	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true)
		{
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::CMPA2:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::CMPB0:
				if(ena) {
					PORTE::PDR.B1 = 0;
					PORTE::PMR.B1 = 0;
				}
				MPC::PE1PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB0:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::CMPB1:
				if(ena) {
					PORTA::PDR.B3 = 0;
					PORTA::PMR.B3 = 0;
				}
				MPC::PA3PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB1:
				if(ena) {
					PORTA::PDR.B4 = 0;
					PORTA::PMR.B4 = 0;
				}
				MPC::PA4PFS.ASEL = ena;
				break;
			case ANALOG::CMPOB0:
				if(ena) {
					PORTE::PDR.B5 = ena;
					PORTE::PMR.B5 = 0;
				}
				break;
			case ANALOG::CMPOB1:
				if(ena) {
					PORTB::PDR.B1 = ena;
					PORTB::PMR.B1 = 0;
				}
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
#elif defined(SIG_RX230) || defined(SIG_RX231)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX230/RX231 コンパレータ B（CMPBa）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb_t : public cmpb01_t, cmpb23_t {

		static constexpr auto PERIPHERAL = peripheral::CMPB;	///< ペリフェラル型
		static constexpr uint32_t CH_NUM = 4;					///< CMP channel num
		static constexpr auto LVD1  = ICU::VECTOR::LVD1;		///< LVD1 割り込みベクター
		static constexpr auto LVD2  = ICU::VECTOR::LVD2;		///< LVD2 割り込みベクター
		static constexpr auto CMPB0 = ICU::VECTOR::CMPB0;		///< CMPB0 割り込みベクター
		static constexpr auto CMPB1 = ICU::VECTOR::CMPB1;		///< CMPB1 割り込みベクター
		static constexpr auto CMPB2 = ICU::VECTOR::CMPB2;		///< CMPB2 割り込みベクター
		static constexpr auto CMPB3 = ICU::VECTOR::CMPB3;		///< CMPB3 割り込みベクター


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			CMPA2,		///< PE4/CMPA2 入力
			CMPB0,		///< PE1/CMPB0 入力
			CVREFB0,	///< PE2/CVREFB0 入力
			CMPB1,		///< PA3/CMPB1 入力
			CVREFB1,	///< PA4/CVREFB1 入力
			CMPB2,		///< P15/CMPB2 入力
			CVREFB2,	///< P14/CVREFB2 入力
			CMPB3,		///< P26/CMPB3 入力
			CVREFB3,	///< P27/CVREFB3 入力
			CMPOB0,		///< PE5/CMPOB0 出力
			CMPOB1,		///< PB1/CMPOB1 出力
			CMPOB2,		///< P17/CMPOB2 出力
			CMPOB3,		///< P30/CMPOB3 出力
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ型
			@param[in]	ena	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true)
		{
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::CMPA2:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::CMPB0:
				if(ena) {
					PORTE::PDR.B1 = 0;
					PORTE::PMR.B1 = 0;
				}
				MPC::PE1PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB0:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::CMPB1:
				if(ena) {
					PORTA::PDR.B3 = 0;
					PORTA::PMR.B3 = 0;
				}
				MPC::PA3PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB1:
				if(ena) {
					PORTA::PDR.B4 = 0;
					PORTA::PMR.B4 = 0;
				}
				MPC::PA4PFS.ASEL = ena;
				break;
			case ANALOG::CMPB2:
				if(ena) {
					PORT1::PDR.B5 = 0;
					PORT1::PMR.B5 = 0;
				}
				MPC::P15PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB2:
				if(ena) {
					PORT1::PDR.B4 = 0;
					PORT1::PMR.B4 = 0;
				}
				MPC::P14PFS.ASEL = ena;
				break;
			case ANALOG::CMPB3:
				if(ena) {
					PORT2::PDR.B6 = 0;
					PORT2::PMR.B6 = 0;
				}
				MPC::P26PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB3:
				if(ena) {
					PORT2::PDR.B7 = 0;
					PORT2::PMR.B7 = 0;
				}
				MPC::P27PFS.ASEL = ena;
				break;
			case ANALOG::CMPOB0:
				if(ena) {
					PORTE::PDR.B5 = ena;
					PORTE::PMR.B5 = 0;
				}
				break;
			case ANALOG::CMPOB1:
				if(ena) {
					PORTB::PDR.B1 = ena;
					PORTB::PMR.B1 = 0;
				}
				break;
			case ANALOG::CMPOB2:
				if(ena) {
					PORT1::PDR.B7 = ena;
					PORT1::PMR.B7 = 0;
				}
				break;
			case ANALOG::CMPOB3:
				if(ena) {
					PORT3::PDR.B0 = ena;
					PORT3::PMR.B0 = 0;
				}
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
#elif defined(SIG_RX23W)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX23W コンパレータ B（CMPBa）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb_t : public cmpb01_t, cmpb23_t {

		static constexpr auto PERIPHERAL = peripheral::CMPB;	///< ペリフェラル型
		static constexpr uint32_t CH_NUM = 2;					///< CMP channel num
		static constexpr auto LVD1  = ICU::VECTOR::LVD1;		///< LVD1 割り込みベクター
		static constexpr auto LVD2  = ICU::VECTOR::NONE;		///< LVD2 割り込みベクター
		static constexpr auto CMPB0 = ICU::VECTOR::NONE;		///< CMPB0 割り込みベクター
		static constexpr auto CMPB1 = ICU::VECTOR::NONE;		///< CMPB1 割り込みベクター
		static constexpr auto CMPB2 = ICU::VECTOR::CMPB2;		///< CMPB2 割り込みベクター
		static constexpr auto CMPB3 = ICU::VECTOR::CMPB3;		///< CMPB3 割り込みベクター


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			CMPB2,		///< P15/CMPB2 入力
			CVREFB2,	///< P14/CVREFB2 入力
			CMPB3,		///< P26/CMPB3 入力
			CVREFB3,	///< P27/CVREFB3 入力
			CMPOB2,		///< P17/CMPOB2 出力
			CMPOB3,		///< P30/CMPOB3 出力
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ型
			@param[in]	ena	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true)
		{
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::CMPB2:
				if(ena) {
					PORT1::PDR.B5 = 0;
					PORT1::PMR.B5 = 0;
				}
				MPC::P15PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB2:
				if(ena) {
					PORT1::PDR.B4 = 0;
					PORT1::PMR.B4 = 0;
				}
				MPC::P14PFS.ASEL = ena;
				break;
			case ANALOG::CMPB3:
				if(ena) {
					PORT2::PDR.B6 = 0;
					PORT2::PMR.B6 = 0;
				}
				MPC::P26PFS.ASEL = ena;
				break;
			case ANALOG::CVREFB3:
				if(ena) {
					PORT2::PDR.B7 = 0;
					PORT2::PMR.B7 = 0;
				}
				MPC::P27PFS.ASEL = ena;
				break;
			case ANALOG::CMPOB2:
				if(ena) {
					PORT1::PDR.B7 = ena;
					PORT1::PMR.B7 = 0;
				}
				break;
			case ANALOG::CMPOB3:
				if(ena) {
					PORT3::PDR.B0 = ena;
					PORT3::PMR.B0 = 0;
				}
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
#endif
	typedef cmpb_t CMPB;
}
