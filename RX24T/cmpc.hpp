#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・CMPC 定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ C（CMPC）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct cmpc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ制御レジスタ（CMPCTL）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpctl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CINV;
			bit_rw_t <io_, bitpos::B1>     COE;
			bits_rw_t<io_, bitpos::B3, 2>  CEG;
			bits_rw_t<io_, bitpos::B5, 2>  CDFS;
			bit_rw_t <io_, bitpos::B7>     HCMPON;
		};
		static cmpctl_t<base + 0x00> CMPCTL;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ入力切り替えレジスタ（CMPSEL0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpsel0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CMPSEL;
		};
		static cmpsel0_t<base + 0x04> CMPSEL0;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ入力切り替えレジスタ（CMPSEL1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpsel1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CVRS;
		};
		static cmpsel1_t<base + 0x08> CMPSEL1;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ出力モニタレジスタ（CMPMON）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpmon_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPMON0;
		};
		static cmpmon_t<base + 0x0C> CMPMON;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ外部出力許可レジスタ（CMPIOC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpioc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CPOE;
		};
		static cmpioc_t<base + 0x10> CMPIOC;

	};
	typedef cmpc_t<0x000A0C80> CMPC0;
	typedef cmpc_t<0x000A0CA0> CMPC1;
	typedef cmpc_t<0x000A0CC0> CMPC2;
	typedef cmpc_t<0x000A0CE0> CMPC3;

}
