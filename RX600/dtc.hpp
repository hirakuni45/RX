#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　DTCa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
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

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC コントロールレジスタ（DTCCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4> RRS;
		};
		typedef dtccr_t_<0x00082400> dtccr_t;
		static dtccr_t DTCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC ベクタベースレジスタ（DTCVBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00082404> dtcvbr_t;
		static dtcvbr_t DTCVBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC アドレスモードレジスタ（DTCADMOD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcadmod_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SHORT;
		};
		typedef dtcadmod_t_<0x00082408> dtcadmod_t;
		static dtcadmod_t DTCADMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC モジュール起動レジスタ（DTCST）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcst_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DTCST;
		};
		typedef dtcst_t_<0x0008240C> dtcst_t;
		static dtcst_t DTCST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC ステータスレジスタ（DTCSTS）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcsts_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> VECN;
			bit_rw_t <io_, bitpos::B15>   ACT;
		};
		typedef dtcsts_t_<0x0008240E> dtcsts_t;
		static dtcsts_t DTCSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};

	typedef dtc_t<peripheral::DTC>  DTC;

	template<peripheral per> typename dtc_t<per>::dtccr_t dtc_t<per>::DTCCR;
	template<peripheral per> typename dtc_t<per>::dtcvbr_t dtc_t<per>::DTCVBR;
	template<peripheral per> typename dtc_t<per>::dtcadmod_t dtc_t<per>::DTCADMOD;
	template<peripheral per> typename dtc_t<per>::dtcst_t dtc_t<per>::DTCST;
	template<peripheral per> typename dtc_t<per>::dtcsts_t dtc_t<per>::DTCSTS;
}
