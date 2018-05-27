#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・CAN 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX600/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN モジュール（CAN）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct can_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ（ CTLR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctlr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      MBM;
			bits_rw_t<io_, bitpos::B1, 2>   IDFM;
			bit_rw_t <io_, bitpos::B3>      MLM;
			bit_rw_t <io_, bitpos::B4>      TPM;
			bit_rw_t <io_, bitpos::B5>      TSRC;
			bits_rw_t<io_, bitpos::B6, 2>   TSPS;
			bits_rw_t<io_, bitpos::B9, 2>   CANM;
			bit_rw_t <io_, bitpos::B10>     SLPM;
			bits_rw_t<io_, bitpos::B11, 2>  BOM;
			bit_rw_t <io_, bitpos::B13>     RBOC;
		};
		static ctlr_t<base + 0x00> CTLR;









		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }

	};

	typedef can_t<0x00090840, peripheral::CAN0> CAN0;
	typedef can_t<0x00091840, peripheral::CAN1> CAN1;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef can_t<0x00092840, peripheral::CAN2> CAN2;
#endif
// note: RX65x CAN0, CAN1
}
