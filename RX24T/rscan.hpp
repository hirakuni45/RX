#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・RSCAN 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX24T/peripheral.hpp"
#include "RX24T/mpc.hpp"
#include "RX24T/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSCAN 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct rscan_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief	ビットコンフィギュレーションレジスタ L (CFGL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfgl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  BRP;
		};
		typedef cfgl_t<base + 0x00>  CFGL_;
		static CFGL_ CFGL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ビットコンフィギュレーションレジスタ H (CFGH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfgh_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  TSEG1;
			bits_rw_t<io_, bitpos::B4, 4>  TSEG2;

			bits_rw_t<io_, bitpos::B8, 2>  SJW;
		};
		typedef cfgh_t<base + 0x02>  CFGH_;
		static CFGH_ CFGH;





	};



	typedef rscan_t<0x000A8300, peripheral::RSCAN>  RSCAN;
}
