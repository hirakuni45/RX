#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63 グループ・AD 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  AD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ad_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDRA レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x00>	ADDRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDRB レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x02>	ADDRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDRC レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x04>	ADDRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDRD レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x06>	ADDRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADCSR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x10> adcsr_io;
		struct adcsr_t : public adcsr_io {
			using adcsr_io::operator =;
			using adcsr_io::operator ();
			using adcsr_io::operator |=;
			using adcsr_io::operator &=;

			bits_t<adcsr_io, 0, 4>	CH;
			bit_t<adcsr_io, 5>	ADST;
			bit_t<adcsr_io, 6>	ADIE;
		};
		static adcsr_t	ADCSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x11> adcr_io;
		struct adcr_t : public adcr_io {
			using adcr_io::operator =;
			using adcr_io::operator ();
			using adcr_io::operator |=;
			using adcr_io::operator &=;

			bits_t<adcr_io, 0, 2>	MODE;
			bits_t<adcr_io, 2, 2>	CKS;
			bits_t<adcr_io, 5, 3>	TRGS;
		};
		static adcr_t	ADCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDPRA レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x12> addpra_io;
		struct addpra_t : public addpra_io {
			using addpra_io::operator =;
			using addpra_io::operator ();
			using addpra_io::operator |=;
			using addpra_io::operator &=;

			bit_t<addpra_io, 7>	DPSEL;
		};
		static addpra_t	ADDPRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADSSTR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static io8<base + 0x13> ADSSTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDIAGR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x15> addiagr_io;
		struct addiagr_t : public addiagr_io {
			using addiagr_io::operator =;
			using addiagr_io::operator ();
			using addiagr_io::operator |=;
			using addiagr_io::operator &=;

			bits_t<addiagr_io, 0, 2>	DIAG;
		};
		static addiagr_t	ADDIAGR;

	};
	typedef ad_t<0x00088040>	AD0;
	typedef ad_t<0x00088060>	AD1;
}
