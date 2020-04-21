#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　DTCa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データトランスファコントローラ・クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct dtc_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC コントロールレジスタ（DTCCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4> RRS;
		};
		typedef dtccr_t<0x00082400> DTCCR_;
		static  DTCCR_ DTCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC ベクタベースレジスタ（DTCVBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00082404> DTCVBR_;
		static  DTCVBR_ DTCVBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC アドレスモードレジスタ（DTCADMOD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcadmod_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SHORT;
		};
		typedef dtcadmod_t<0x00082408> DTCADMOD_;
		static  DTCADMOD_ DTCADMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC モジュール起動レジスタ（DTCST）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcst_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DTCST;
		};
		typedef dtcst_t<0x0008240C> DTCST_;
		static  DTCST_ DTCST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC ステータスレジスタ（DTCSTS）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcsts_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> VECN;
			bit_rw_t <io_, bitpos::B15>   ACT;
		};
		typedef dtcsts_t<0x0008240E> DTCSTS_;
		static  DTCSTS_ DTCSTS;
	};
	template <peripheral per> typename dtc_t<per>::DTCCR_ dtc_t<per>::DTCCR;
	template <peripheral per> typename dtc_t<per>::DTCVBR_ dtc_t<per>::DTCVBR;
	template <peripheral per> typename dtc_t<per>::DTCADMOD_ dtc_t<per>::DTCADMOD;
	template <peripheral per> typename dtc_t<per>::DTCST_ dtc_t<per>::DTCST;
	template <peripheral per> typename dtc_t<per>::DTCSTS_ dtc_t<per>::DTCSTS;


	typedef dtc_t<peripheral::DTC>  DTC;
}
