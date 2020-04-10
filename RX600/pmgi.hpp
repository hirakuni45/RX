#pragma once
//=====================================================================//
/*!	@file
	@brief	RX700 グループ　PMGI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PMGI 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct pmgi_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PMGI コンフィギュレーションレジスタ (PMGCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pmgcr_t_ : public rw32_t<ofs> {
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
		typedef pmgcr_t_<base + 0x00> pmgcr_t;
		static pmgcr_t PMGCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY ステーションマネジメントレジスタ (PSMR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct psmr_t_ : public rw32_t<ofs> {
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
		typedef psmr_t_<base + 0x04> psmr_t;
		static psmr_t PSMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};

	typedef pmgi_t<0x000C5880, peripheral::PMGI0> PMGI0;
	typedef pmgi_t<0x000C5890, peripheral::PMGI1> PMGI1;

	template<uint32_t base, peripheral per> typename pmgi_t<base, per>::pmgcr_t pmgi_t<base, per>::PMGCR;
	template<uint32_t base, peripheral per> typename pmgi_t<base, per>::psmr_t pmgi_t<base, per>::PSMR;
}
