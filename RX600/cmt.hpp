#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621, RX63T, RX64M グループ・CMT 定義 @n
			Copyright 2013, 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT 定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct cmt_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR0 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x00088000> cmstr0_io;
		struct cmstr0_t : public cmstr0_io {
			using cmstr0_io::operator =;
			using cmstr0_io::operator ();
			using cmstr0_io::operator |=;
			using cmstr0_io::operator &=;

			bit_rw_t<cmstr0_io, bitpos::B0>	STR0;
			bit_rw_t<cmstr0_io, bitpos::B1>	STR1;
		};
		static cmstr0_t	CMSTR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR1 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x00088010> cmstr1_io;
		struct cmstr1_t : public cmstr1_io {
			using cmstr1_io::operator =;
			using cmstr1_io::operator ();
			using cmstr1_io::operator |=;
			using cmstr1_io::operator &=;

			bit_rw_t<cmstr1_io, bitpos::B0>	STR2;
			bit_rw_t<cmstr1_io, bitpos::B1>	STR3;
		};
		static cmstr1_t	CMSTR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x00> cmcr_io;
		struct cmcr_t : public cmcr_io {
			using cmcr_io::operator =;
			using cmcr_io::operator ();
			using cmcr_io::operator |=;
			using cmcr_io::operator &=;

			bits_rw_t<cmcr_io, bitpos::B0, 2>	CKS;
			bit_rw_t <cmcr_io, bitpos::B6>	CMIE;
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
	};

	typedef cmt_t<0x00088002> CMT0;
	typedef cmt_t<0x00088008> CMT1;
	typedef cmt_t<0x00088012> CMT2;
	typedef cmt_t<0x00088018> CMT3;
}
