#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・WDTA 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  wdta 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	ivec	割り込み要因
		@param[in]	pclk	マスタークロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
	struct wdta_t {

		static const auto IVEC = ivec;	///< 割り込みベクター
		static const auto PCLK = pclk;	///< マスタークロック周波数

		//-----------------------------------------------------------------//
		/*!
			@brief  WDT リフレッシュレジスタ（WDTRR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x00> WDTRR_;
		static WDTRR_ WDTRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	WDT コントロールレジスタ（WDTCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct wdtcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> TOPS;

			bits_rw_t<io_, bitpos::B4,  4> CKS;
			bits_rw_t<io_, bitpos::B8,  2> RPES;

			bits_rw_t<io_, bitpos::B12, 2> RPSS;
		};
		typedef wdtcr_t<base + 0x02> WDTCR_;
		static WDTCR_ WDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	WDT ステータスレジスタ（WDTSR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct wdtsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 14> CNTVAL;

			bit_rw_t <io_, bitpos::B14>    UNDFF;
			bit_rw_t <io_, bitpos::B15>    REFEF;
		};
		typedef wdtsr_t<base + 0x04> WDTSR_;
		static WDTSR_ WDTSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	WDT リセットコントロールレジスタ（WDTRCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct wdtrcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  RSTIRQS;
		};
		typedef wdtrcr_t<base + 0x06> WDTRCR_;
		static WDTRCR_ WDTRCR;
	};
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename wdta_t<base, ivec, pclk>::WDTRR_ wdta_t<base, ivec, pclk>::WDTRR;
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename wdta_t<base, ivec, pclk>::WDTCR_ wdta_t<base, ivec, pclk>::WDTCR;
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename wdta_t<base, ivec, pclk>::WDTSR_ wdta_t<base, ivec, pclk>::WDTSR;
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename wdta_t<base, ivec, pclk>::WDTRCR_ wdta_t<base, ivec, pclk>::WDTRCR;


	typedef wdta_t<0x00088020, ICU::VECTOR::WUNI, F_PCLKB> WDT;
}
