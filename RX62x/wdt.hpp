#pragma once
//=====================================================================//
/*!	@file
	@brief	RX621/RX62N WDT 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  wdt 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込み要因
		@param[in]	pclk	マスタークロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec, uint32_t pclk>
	struct wdt_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto IVEC = ivec;		///< 割り込みベクター
		static constexpr auto PCLK = pclk;	///< マスタークロック周波数

		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x09> TCNT_;
		static TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロール／ステータスレジスタ（TCSR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> CKS;

			bit_rw_t <io_, bitpos::B5>    TME;
			bit_rw_t <io_, bitpos::B6>    TMS;
		};
		typedef tcsr_t<base + 0x08> TCSR_;
		static TCSR_ TCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	リセットコントロール／ステータスレジスタ（RSTCSR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rstcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B6>   RSTE;
			bit_rw_t <io_, bitpos::B7>   WOVF;
		};
		typedef rstcsr_t<base + 0x0B> RSTCSR_;
		static RSTCSR_ RSTCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ライトウィンドウ A レジスタ（WINA）
		*/
		//-----------------------------------------------------------------//
		typedef wo16_t<base + 0x08> WINA_;
		static WINA_ WINA;


		//-----------------------------------------------------------------//
		/*!
			@brief  ライトウィンドウ B レジスタ（WINB）
		*/
		//-----------------------------------------------------------------//
		typedef wo16_t<base + 0x0A> WINB_;
		static WINB_ WINB;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR ivec, uint32_t pclk>
		typename wdt_t<base, per, ivec, pclk>::TCNT_ wdt_t<base, per, ivec, pclk>::TCNT;
	
	typedef wdt_t<0x0008'8020, peripheral::WDT, ICU::VECTOR::WOVI, clock_profile::PCLK> WDT;
}
