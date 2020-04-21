#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・IWDT 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
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
		@param[in]	ivec	割り込み要因
		@param[in]	pclk	マスタークロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
	struct iwdt_t {

		static const auto IVEC = ivec;	///< 割り込みベクター
		static const auto PCLK = pclk;	///< マスタークロック周波数

		//-----------------------------------------------------------------//
		/*!
			@brief  IWDT リフレッシュレジスタ（IWDTRR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x00> IWDTRR_;
		static IWDTRR_ IWDTRR;


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
		typedef iwdtcr_t<base + 0x02> IWDTCR_;
		static IWDTCR_ IWDTCR;


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
		typedef iwdtsr_t<base + 0x04> IWDTSR_;
		static IWDTSR_ IWDTSR;


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
		typedef iwdtrcr_t<base + 0x06> IWDTRCR_;
		static IWDTRCR_ IWDTRCR;


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
		typedef iwdtcstpr_t<base + 0x08> IWDTCSTPR_;
		static IWDTCSTPR_ IWDTCSTPR;
	};
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename iwdt_t<base, ivec, pclk>::IWDTRR_ iwdt_t<base, ivec, pclk>::IWDTRR;
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename iwdt_t<base, ivec, pclk>::IWDTCR_ iwdt_t<base, ivec, pclk>::IWDTCR;
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename iwdt_t<base, ivec, pclk>::IWDTSR_ iwdt_t<base, ivec, pclk>::IWDTSR;
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename iwdt_t<base, ivec, pclk>::IWDTRCR_ iwdt_t<base, ivec, pclk>::IWDTRCR;
	template <uint32_t base, ICU::VECTOR ivec, uint32_t pclk>
		typename iwdt_t<base, ivec, pclk>::IWDTCSTPR_ iwdt_t<base, ivec, pclk>::IWDTCSTPR;


#if defined(SIG_RX24T)
	typedef iwdt_t<0x00088030, ICU::VECTOR::IWUNI,  15'000> IWDT;
#else
	typedef iwdt_t<0x00088030, ICU::VECTOR::IWUNI, 120'000> IWDT;
#endif
}
