#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T/RX66T グループ・CMPC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

/// CMPC モジュールが無いデバイスでエラーとする
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
#  error "cmpc.hpp: This module does not exist"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ C（CMPC）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	vec		割り込みベクタ型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR vec>
	struct cmpc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ制御レジスタ（CMPCTL）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpctl_t_ : public rw8_t<ofs> {
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
		typedef cmpctl_t_<base + 0x00> cmpctl_t;
		static cmpctl_t CMPCTL;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ入力切り替えレジスタ（CMPSEL0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpsel0_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CMPSEL;
		};
		typedef cmpsel0_t_<base + 0x04> cmpsel0_t;
		static cmpsel0_t CMPSEL0;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ入力切り替えレジスタ（CMPSEL1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpsel1_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CVRS;
		};
		typedef cmpsel1_t_<base + 0x08> cmpsel1_t;
		static cmpsel1_t CMPSEL1;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ出力モニタレジスタ（CMPMON）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpmon_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPMON0;
		};
		typedef cmpmon_t_<base + 0x0C> cmpmon_t;
		static cmpmon_t CMPMON;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ外部出力許可レジスタ（CMPIOC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cmpioc_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CPOE;
		};
		typedef cmpioc_t_<base + 0x10> cmpioc_t;
		static cmpioc_t CMPIOC;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec() { return vec; }
	};

#if defined(SIG_RX24T)
	typedef cmpc_t<0x000A0C80, peripheral::CMPC0, ICU::VECTOR::CMPC0> CMPC0;
	typedef cmpc_t<0x000A0CA0, peripheral::CMPC1, ICU::VECTOR::CMPC1> CMPC1;
	typedef cmpc_t<0x000A0CC0, peripheral::CMPC2, ICU::VECTOR::CMPC2> CMPC2;
	typedef cmpc_t<0x000A0CE0, peripheral::CMPC3, ICU::VECTOR::CMPC3> CMPC3;
#elif defined(SIG_RX66T)
	typedef cmpc_t<0x000A0C80, peripheral::CMPC0, ICU::VECTOR::CMPC0> CMPC0;
	typedef cmpc_t<0x000A0CA0, peripheral::CMPC1, ICU::VECTOR::CMPC1> CMPC1;
	typedef cmpc_t<0x000A0CC0, peripheral::CMPC2, ICU::VECTOR::CMPC2> CMPC2;
	typedef cmpc_t<0x000A0CE0, peripheral::CMPC3, ICU::VECTOR::CMPC3> CMPC3;
	typedef cmpc_t<0x000A0D00, peripheral::CMPC4, ICU::VECTOR::CMPC4> CMPC4;
	typedef cmpc_t<0x000A0D20, peripheral::CMPC5, ICU::VECTOR::CMPC5> CMPC5;
#endif

	template<uint32_t base, peripheral per, ICU::VECTOR vec> typename cmpc_t<base, per, vec>::cmpctl_t cmpc_t<base, per, vec>::CMPCTL;
	template<uint32_t base, peripheral per, ICU::VECTOR vec> typename cmpc_t<base, per, vec>::cmpsel0_t cmpc_t<base, per, vec>::CMPSEL0;
	template<uint32_t base, peripheral per, ICU::VECTOR vec> typename cmpc_t<base, per, vec>::cmpsel1_t cmpc_t<base, per, vec>::CMPSEL1;
	template<uint32_t base, peripheral per, ICU::VECTOR vec> typename cmpc_t<base, per, vec>::cmpmon_t cmpc_t<base, per, vec>::CMPMON;
	template<uint32_t base, peripheral per, ICU::VECTOR vec> typename cmpc_t<base, per, vec>::cmpioc_t cmpc_t<base, per, vec>::CMPIOC;
}
