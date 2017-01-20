#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・フラッシュ 定義 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  E2 データフラッシュ制御レジスタ (DFLCTL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dflctl_t : public rw8_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DFLEN;
		};
		static dflctl_t<0x007FC090> DFLCTL;




	};
	typedef flash_t FLASH;
}
