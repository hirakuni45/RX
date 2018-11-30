#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・WDTA 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  独立ウォッチドッグタイマクラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct iwdt_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  IWDT リフレッシュレジスタ（IWDTRR）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x00> IWDTRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT コントロールレジスタ（IWDTCR）
		*/
		//-----------------------------------------------------------------//
		struct iwdtcr_t : public rw16_t<base + 0x02> {
			typedef rw16_t<base + 0x02> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> TOPS;

			bits_rw_t<io_, bitpos::B4,  4> CKS;
			bits_rw_t<io_, bitpos::B8,  2> RPES;

			bits_rw_t<io_, bitpos::B12, 2> RPSS;
		};
		static iwdtcr_t IWDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT ステータスレジスタ（IWDTSR）
		*/
		//-----------------------------------------------------------------//
		struct iwdtsr_t : public rw16_t<base + 0x04> {
			typedef rw16_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 14> CNTVAL;

			bit_rw_t <io_, bitpos::B14>    UNDFF;
			bit_rw_t <io_, bitpos::B15>    REFEF;
		};
		static iwdtsr_t IWDTSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT リセットコントロールレジスタ（IWDTRCR）
		*/
		//-----------------------------------------------------------------//
		struct iwdtrcr_t : public rw8_t<base + 0x06> {
			typedef rw8_t<base + 0x06> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  RSTIRQS;
		};
		static iwdtrcr_t IWDTRCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT カウント停止コントロールレジスタ（IWDTCSTPR）
		*/
		//-----------------------------------------------------------------//
		struct iwdtcstpr_t : public rw8_t<base + 0x08> {
			typedef rw8_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  SLCSTP;
		};
		static iwdtcstpr_t IWDTCSTPR;
	};
	typedef iwdt_t<0x00088030> IWDT;
}
