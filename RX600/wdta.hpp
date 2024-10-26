#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・WDTA 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  wdta 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込み要因
		@param[in]	pclk	マスタークロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec, uint32_t pclk>
	struct wdta_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto IVEC = ivec;		///< 割り込みベクター
		static constexpr auto PCLK = pclk;		///< マスタークロック周波数

		//-----------------------------------------------------------------//
		/*!
			@brief  WDT リフレッシュレジスタ（WDTRR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x00> WDTRR;


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
		static inline wdtcr_t<base + 0x02> WDTCR;


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
		static inline wdtsr_t<base + 0x04> WDTSR;


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
		static inline wdtrcr_t<base + 0x06> WDTRCR;
	};

#if defined(SIG_RX231) || defined(SIG_RX260) || defined(SIG_RX261) || defined(SIG_RX631) || defined(SIG_RX63N)
	// WUNI for NMI
	typedef wdta_t<0x0008'8020, peripheral::WDTA, ICU::VECTOR::NONE, clock_profile::PCLKB> WDT;
#else
	typedef wdta_t<0x0008'8020, peripheral::WDTA, ICU::VECTOR::WUNI, clock_profile::PCLKB> WDT;
#endif
}
