#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・CRC 定義 @n
			・RX220 @n
			・RX231 @n
			・RX23T @n
			・RX24T/RX24U @n
			・RX260/RX261 @n
			・RX26T @n
			・RX62N/RX621 @n
			・RX63N/RX631 @n
			・RX63T @n
			・RX64M/RX71M @n
			・RX65N/RX651 @n
			・RX66T/RX72T @n
			・RX671 @n
			・RX72N/RX72M
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
		@brief  CRC 演算器クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct crc_t {

		static constexpr auto PERIPHERAL = peripheral::CRC;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  CRC コントロールレジスタ（CRCCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct crccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  GPS;
			bit_rw_t <io_, bitpos::B2>     LMS;

			bit_rw_t <io_, bitpos::B7>     DORCLR;
		};
		static inline crccr_t<base + 0x00> CRCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ入力レジスタ（CRCDIR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x01> CRCDIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ出力レジスタ（CRCDOR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x02> CRCDOR;
	};
	typedef crc_t<0x0008'8280> CRC;
}
