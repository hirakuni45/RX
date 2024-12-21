#pragma once
//=============================================================================//
/*!	@file
	@brief	Compare Match Timer W / コンペアマッチタイマ W @n
			RX26T @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX660/RX671 @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMPW class
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
		@param[in]	cmwi	コンペア・マッチ割り込みベクタ
		@param[in]	CIVT	キャプチャ系・割り込み型
		@param[in]	ic0i	インプット・キャプチャ 0 割り込みベクタ
		@param[in]	ic1i	インプット・キャプチャ 1 割り込みベクタ
		@param[in]	oc0i	アウトプット・キャプチャ 0 割り込みベクタ
		@param[in]	oc1i	アウトプット・キャプチャ 1 割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR cmwi, typename CIVT,
		CIVT ic0i, CIVT ic1i, CIVT oc0i, CIVT oc1i>
	struct cmtw_t {

		static constexpr auto PERIPHERAL = per;				///< ペリフェラル型
		static constexpr auto CMWI = cmwi;					///< コンペア・マッチ割り込みベクタ
		static constexpr auto IC0I = ic0i;					///< インプット・キャプチャ 0 割り込みベクタ
		static constexpr auto IC1I = ic1i;					///< インプット・キャプチャ 1 割り込みベクタ
		static constexpr auto OC0I = oc0i;					///< アウトプット・キャプチャ 0 割り込みベクタ
		static constexpr auto OC1I = oc1i;					///< アウトプット・キャプチャ 1 割り込みベクタ
		static constexpr auto PCLK = clock_profile::PCLKB;	///< PCLK 周波数


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
		static inline cmwstr_t<base + 0x00> CMWSTR;


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
		static inline cmwcr_t<base + 0x04> CMWCR;


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
		static inline cmwior_t<base + 0x08> CMWIOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマカウンタ（CMWCNT）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x10> CMWCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コンペアマッチコンスタントレジスタ（CMWCOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x14> CMWCOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  インプットキャプチャレジスタ 0（CMWICR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x18> CMWICR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  インプットキャプチャレジスタ 1（CMWICR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x1C> CMWICR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプットコンペアレジスタ 0（CMWOCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x20> CMWOCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプットコンペアレジスタ 1（CMWOCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x24> CMWOCR1;
	};
#if defined (SIG_RX26T)
	typedef cmtw_t<0x0009'4200, peripheral::CMTW0, ICU::VECTOR::CMWI0, ICU::VECTOR,
		ICU::VECTOR::IC0I0, ICU::VECTOR::IC1I0, ICU::VECTOR::OC0I0, ICU::VECTOR::OC1I0> CMTW0;
	typedef cmtw_t<0x0009'4280, peripheral::CMTW1, ICU::VECTOR::CMWI1, ICU::VECTOR,
		ICU::VECTOR::IC0I1, ICU::VECTOR::IC1I1, ICU::VECTOR::OC0I1, ICU::VECTOR::OC1I1> CMTW1;
#else
	typedef cmtw_t<0x0009'4200, peripheral::CMTW0, ICU::VECTOR::CMWI0, ICU::SELECTB,
		ICU::SELECTB::IC0I0, ICU::SELECTB::IC1I0, ICU::SELECTB::OC0I0, ICU::SELECTB::OC1I0> CMTW0;
	typedef cmtw_t<0x0009'4280, peripheral::CMTW1, ICU::VECTOR::CMWI1, ICU::SELECTB,
		ICU::SELECTB::IC0I1, ICU::SELECTB::IC1I1, ICU::SELECTB::OC0I1, ICU::SELECTB::OC1I1> CMTW1;
#endif
}
