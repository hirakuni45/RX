#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M, RX65x, RX71M, RX72M, RX72N グループ・CMTW 定義
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

		static const auto PERIPHERAL = per;		///< ペリフェラル型
		static const auto IVEC = ivec;			///< 割り込みベクター
		static const uint32_t PCLK = F_PCLKB;	///< PCLK 周波数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマスタートレジスタ（CMWSTR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cmwstr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   STR;
		};
		typedef cmwstr_t<base + 0x00> CMWSTR_;
		static  CMWSTR_ CMWSTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ（CMWCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cmwcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef cmwcr_t<base + 0x04> CMWCR_;
		static  CMWCR_ CMWCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマ I/O コントロールレジスタ（CMWIOR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cmwior_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef cmwior_t<base + 0x08> CMWIOR_;
		static  CMWIOR_ CMWIOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマカウンタ（CMWCNT）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x10> CMWCNT_;
		static  CMWCNT_ CMWCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コンペアマッチコンスタントレジスタ（CMWCOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x14> CMWCOR_;
		static  CMWCOR_ CMWCOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  インプットキャプチャレジスタ 0（CMWICR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> CMWICR0_;
		static  CMWICR0_ CMWICR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  インプットキャプチャレジスタ 1（CMWICR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x1C> CMWICR1_;
		static  CMWICR1_ CMWICR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプットコンペアレジスタ 0（CMWOCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x20> CMWOCR0_;
		static  CMWOCR0_ CMWOCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプットコンペアレジスタ 1（CMWOCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x24> CMWOCR1_;
		static  CMWOCR1_ CMWOCR1;
	};

	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWSTR_ cmtw_t<base, per, ivec>::CMWSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWCR_ cmtw_t<base, per, ivec>::CMWCR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWIOR_ cmtw_t<base, per, ivec>::CMWIOR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWCNT_ cmtw_t<base, per, ivec>::CMWCNT;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWCOR_ cmtw_t<base, per, ivec>::CMWCOR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWICR0_ cmtw_t<base, per, ivec>::CMWICR0;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWICR1_ cmtw_t<base, per, ivec>::CMWICR1;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWOCR0_ cmtw_t<base, per, ivec>::CMWOCR0;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec> typename cmtw_t<base, per, ivec>::  CMWOCR1_ cmtw_t<base, per, ivec>::CMWOCR1;

	typedef cmtw_t<0x00094200, peripheral::CMTW0, ICU::VECTOR::CMWI0> CMTW0;
	typedef cmtw_t<0x00094280, peripheral::CMTW1, ICU::VECTOR::CMWI1> CMTW1;
}
