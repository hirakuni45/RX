#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M, RX65x, RX71M, RX72M グループ・CMTW 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

/// cmtw モジュールが無いデバイスでエラーとする
#if defined(SIG_RX24T) || defined(SIG_RX66T) || defined(SIG_RX72T)
#  error "cmtw.hpp: This module does not exist"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンペアマッチタイマ W クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
	struct cmtw_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマスタートレジスタ（CMWSTR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmwstr_t : public rw16_t<base + 0x00> {
			typedef rw16_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   STR;
		};
		static cmwstr_t CMWSTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ（CMWCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmwcr_t : public rw16_t<base + 0x04> {
			typedef rw16_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   CKS;

			bit_rw_t <io_, bitpos::B3>      CMWIE;
			bit_rw_t <io_, bitpos::B4>      IC0IE;
			bit_rw_t <io_, bitpos::B5>      IC1IE;
			bit_rw_t <io_, bitpos::B6>      OC0IE;
			bit_rw_t <io_, bitpos::B7>      OC1IE;

			bit_rw_t <io_, bitpos::B9>      CMS;

			bits_rw_t<io_, bitpos::B13, 3>  CCLR;
		};
		static cmwcr_t CMWCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマ I/O コントロールレジスタ（CMWIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmwior_t : public rw16_t<base + 0x08> {
			typedef rw16_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   IC0;
			bits_rw_t<io_, bitpos::B2, 2>   IC1;

			bit_rw_t <io_, bitpos::B4>      IC0E;
			bit_rw_t <io_, bitpos::B5>      IC1E;

			bits_rw_t<io_, bitpos::B8,  2>  OC0;
			bits_rw_t<io_, bitpos::B10, 2>  OC1;

			bit_rw_t <io_, bitpos::B12>     OC0E;
			bit_rw_t <io_, bitpos::B13>     OC1E;

			bit_rw_t <io_, bitpos::B15>     CMWE;
		};
		static cmwior_t CMWIOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマカウンタ（CMWCNT）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x10> cmwcnt_t;
		static cmwcnt_t CMWCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コンペアマッチコンスタントレジスタ（CMWCOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x14> cmwcor_t;
		static cmwcor_t CMWCOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  インプットキャプチャレジスタ 0（CMWICR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> cmwicr0_t;
		static cmwicr0_t CMWICR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  インプットキャプチャレジスタ 1（CMWICR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x1C> cmwicr1_t;
		static cmwicr1_t CMWICR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプットコンペアレジスタ 0（CMWOCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x20> cmwocr0_t;
		static cmwocr0_t CMWOCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプットコンペアレジスタ 1（CMWOCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x24> cmwocr1_t;
		static cmwocr1_t CMWOCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() noexcept { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_ivec() noexcept { return ivec; }
	};

	typedef cmtw_t<0x00094200, peripheral::CMTW0, ICU::VECTOR::CMWI0> CMTW0;
	typedef cmtw_t<0x00094280, peripheral::CMTW1, ICU::VECTOR::CMWI1> CMTW1;

	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwstr_t cmtw_t<base, per, ivec>::CMWSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwcr_t cmtw_t<base, per, ivec>::CMWCR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwior_t cmtw_t<base, per, ivec>::CMWIOR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwcnt_t cmtw_t<base, per, ivec>::CMWCNT;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwcor_t cmtw_t<base, per, ivec>::CMWCOR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwicr0_t cmtw_t<base, per, ivec>::CMWICR0;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwicr1_t cmtw_t<base, per, ivec>::CMWICR1;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwocr0_t cmtw_t<base, per, ivec>::CMWOCR0;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::cmwocr1_t cmtw_t<base, per, ivec>::CMWOCR1;
}
