#pragma once
//=============================================================================//
/*!	@file
	@brief	RX700 グループ　PMGI 定義 @n
			RX66N (1 channel) @n
			RX72N @n
			RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PMGI 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	pmgii	アクセス終了割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::SELECTA pmgii>
	struct pmgi_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto PMGII = pmgii;	///< アクセス終了割り込みベクタ

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PMGI コンフィギュレーションレジスタ (PMGCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pmgcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8,  6>  PSMCS;

			bit_rw_t <io_, bitpos::B15>     PSMDP;
			bits_rw_t<io_, bitpos::B16, 3>  PSMHT;

			bits_rw_t<io_, bitpos::B20, 3>  PSMCT;
		};
		static inline pmgcr_t<base + 0x00> PMGCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY ステーションマネジメントレジスタ (PSMR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct psmr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      PSME;
			bit_rw_t <io_, bitpos::B1>      PSMAD;

			bits_rw_t<io_, bitpos::B3,  5>  PDA;
			bits_rw_t<io_, bitpos::B8,  5>  PRA;

			bits_rw_t<io_, bitpos::B16, 16> PRD;
		};
		static inline psmr_t<base + 0x04> PSMR;
	};
#if defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef pmgi_t<0x000C'5880, peripheral::PMGI0, ICU::SELECTA::PMGI0I> PMGI0;
#endif
#if defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef pmgi_t<0x000C'5890, peripheral::PMGI1, ICU::SELECTA::PMGI1I> PMGI1;
#endif
}
