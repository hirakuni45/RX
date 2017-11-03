#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・WDTA 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
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
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct wdta_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  WDT リフレッシュレジスタ（WDTRR）
		*/
		//-----------------------------------------------------------------//
		rw8_t<base + 0x00> WDTRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	WDT コントロールレジスタ（WDTCR）
		*/
		//-----------------------------------------------------------------//
		struct wdtcr_t : public rw16_t<base + 0x02> {
			typedef rw16_t<base + 0x02> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> TOPS;

			bits_rw_t<io_, bitpos::B4,  2> CKS;
			bits_rw_t<io_, bitpos::B8,  2> RPES;

			bits_rw_t<io_, bitpos::B12, 2> RPSS;
		};
		wdtcr_t WDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	WDT ステータスレジスタ（WDTSR）
		*/
		//-----------------------------------------------------------------//
		struct wdtsr_t : public rw16_t<base + 0x04> {
			typedef rw16_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 14> CNTVAL;

			bit_rw_t <io_, bitpos::B14>    UNDFF;
			bit_rw_t <io_, bitpos::B15>    REFEF;
		};
		wdtsr_t WDTSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	WDT リセットコントロールレジスタ（WDTRCR）
		*/
		//-----------------------------------------------------------------//
		struct wdtrcr_t : public rw8_t<base + 0x06> {
			typedef rw8_t<base + 0x06> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  RSTIRQS;
		};
		wdtrcr_t WDTRCR;

	};
	static rtc_t<0x00088020> WDT;
}
