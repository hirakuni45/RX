#pragma once
//=========================================================================//
/*!	@file
	@brief	Independent Watchdog Timer / 独立ウォッチドッグタイマ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IWDT class
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込み要因
		@param[in]	pclk	マスタークロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec, uint32_t pclk>
	struct iwdt_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto IVEC = ivec;		///< 割り込みベクター
		static constexpr auto PCLK = pclk;		///< マスタークロック周波数

		//-----------------------------------------------------------------//
		/*!
			@brief  IWDT リフレッシュレジスタ（IWDTRR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x00> IWDTRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT コントロールレジスタ（IWDTCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iwdtcr_t : public rw16_t<ofs> {
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
		static inline iwdtcr_t<base + 0x02> IWDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT ステータスレジスタ（IWDTSR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iwdtsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 14> CNTVAL;

			bit_rw_t <io_, bitpos::B14>    UNDFF;
			bit_rw_t <io_, bitpos::B15>    REFEF;
		};
		static inline iwdtsr_t<base + 0x04> IWDTSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT リセットコントロールレジスタ（IWDTRCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iwdtrcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  RSTIRQS;
		};
		static inline iwdtrcr_t<base + 0x06> IWDTRCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IWDT カウント停止コントロールレジスタ（IWDTCSTPR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iwdtcstpr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  SLCSTP;
		};
		static inline iwdtcstpr_t<base + 0x08> IWDTCSTPR;
	};

#if defined(SIG_RX220) || defined(SIG_RX63T) || defined(SIG_RX63T_S) || defined(SIG_RX621) || defined(SIG_RX62N) || defined(SIG_RX631) || defined(SIG_RX63N)
	typedef iwdt_t<0x0008'8030, peripheral::IWDT, ICU::VECTOR::NONE, 125'000> IWDT;
#elif defined(SIG_RX110) || defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130) || defined(SIG_RX140) || defined(SIG_RX231) || defined(SIG_RX13T) || defined(SIG_RX23T) || defined(SIG_RX24T) || defined(SIG_RX24U) || defined(SIG_RX260) || defined(SIG_RX261)
	// interrupt vector: for NMI vector
	typedef iwdt_t<0x0008'8030, peripheral::IWDT, ICU::VECTOR::NONE,  15'000> IWDT;
#else
	typedef iwdt_t<0x0008'8030, peripheral::IWDT, ICU::VECTOR::IWUNI, 120'000> IWDT;
#endif
}
