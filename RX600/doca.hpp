#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・DOCA 定義 @n
			RX26T @n
			RX671
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOCA）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct doca_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  DOC コントロールレジスタ（DOCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct docr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OMS;

			bit_rw_t <io_, bitpos::B3>     DOPSZ;
			bits_rw_t<io_, bitpos::B4, 3>  DCSEL;
			bit_rw_t <io_, bitpos::B7>     DOPCIE;
		};
		static inline docr_t<base + 0x00> DOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC ステータスレジスタ (DOSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dosr_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>     DOPCF;
		};
		static inline dosr_t<base + 0x04> DOSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC ステータスクリアレジスタ (DOSCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct doscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     DOPCFCL;
		};
		static inline doscr_t<base + 0x08> DOSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC データインプットレジスタ（DODIR）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x0C> DODIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC データセッティングレジスタ 0（DODSR0）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x10> DODSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC データセッティングレジスタ 1（DODSR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x14> DODSR1;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOCA）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	vec		割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::GROUPBL0 vec>
	struct doca_bl0_t : public doca_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto INTRV = vec;			///< 割り込みベクター

	};
	typedef doca_bl0_t<0x000A'0580, peripheral::DOC, ICU::GROUPBL0::DOPCI> DOC;
}
