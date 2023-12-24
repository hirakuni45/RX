#pragma once
//=========================================================================//
/*!	@file
	@brief	IrDA 定義 @n
			RX220 @n
			RX231
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IrDA クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct irda_t {

		//-----------------------------------------------------------------//
		/*!
			@brief	IrDA 制御レジスタ（IRCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ircr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B2>     IRRXINV;
			bit_rw_t <io_, bitpos::B3>     IRTXINV;
			bits_rw_t<io_, bitpos::B4, 3>  IRCKS;
			bit_rw_t <io_, bitpos::B7>     IRE;
		};
		typedef ircr_t<0x0008'8410>  IRCR_;
		static  IRCR_ IRCR;

	};
	template<class _> typename irda_t<_>::IRCR_ irda_t<_>::IRCR;

	typedef irda_t<void> IrDA;
}
