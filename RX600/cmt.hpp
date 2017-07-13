#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621, RX63T, RX64M グループ・CMT 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#if defined(SIG_RX63T)
#include "RX63T/peripheral.hpp"
#elif defined(SIG_RX64M)
#include "RX64M/peripheral.hpp"
#elif defined(SIG_RX24T)
#include "RX24T/peripheral.hpp"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct cmt_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR0 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmstr0_t : public rw16_t<0x00088000> {
			typedef rw16_t<0x00088000> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STR0;
			bit_rw_t<io_, bitpos::B1> STR1;
		};
		static cmstr0_t	CMSTR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR1 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmstr1_t : public rw16_t<0x00088010> {
			typedef rw16_t<0x00088010> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STR2;
			bit_rw_t<io_, bitpos::B1> STR3;
		};
		static cmstr1_t	CMSTR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmcr_t : public rw16_t<base + 0x00> {
			typedef rw16_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B6>    CMIE;
		};
		static cmcr_t CMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCNT レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw16_t<base + 0x02> CMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCOR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw16_t<base + 0x04> CMCOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネルを返す
			@return チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_chanel() {
			return (base >> 3) & 3;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }
	};

	typedef cmt_t<0x00088002, peripheral::CMT0> CMT0;
	typedef cmt_t<0x00088008, peripheral::CMT1> CMT1;
	typedef cmt_t<0x00088012, peripheral::CMT2> CMT2;
	typedef cmt_t<0x00088018, peripheral::CMT3> CMT3;
}
