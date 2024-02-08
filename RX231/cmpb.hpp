#pragma once
//=========================================================================//
/*!	@file
	@brief	RX140/RX231 グループ・CMPBa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
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

#if defined(SIG_RX140)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ B（CMPBa）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb_t : public cmpb01_t {

		static constexpr auto PERIPHERAL = peripheral::CMPB;	///< ペリフェラル型
		static constexpr auto LVD1 = ICU::VECTOR::LVD1;			///< 割り込みベクター
		static constexpr auto LVD2 = ICU::VECTOR::LVD2;			///< 割り込みベクター
	};
#elif defined(SIG_RX231)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ B（CMPBa）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb_t : public cmpb01_t, cmpb23_t {

		static constexpr auto PERIPHERAL = peripheral::CMPB;	///< ペリフェラル型
		static constexpr auto LVD1 = ICU::VECTOR::LVD1;			///< 割り込みベクター
		static constexpr auto LVD2 = ICU::VECTOR::LVD2;			///< 割り込みベクター
	};
#endif
	typedef cmpb_t CMPB;
}
