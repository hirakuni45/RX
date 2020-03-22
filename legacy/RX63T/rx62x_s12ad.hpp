#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621 グループ・S12AD 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR0 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x20> ADDR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR1 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x22> ADDR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR2 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x24> ADDR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR3 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x26> ADDR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR4 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x28> ADDR4;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR5 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x2a> ADDR5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR6 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x2c> ADDR6;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADDR7 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x2e> ADDR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADCSR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x00> adcsr_io;
		struct adcsr_t : public adcsr_io {
			using adcsr_io::operator =;
			using adcsr_io::operator ();
			using adcsr_io::operator |=;
			using adcsr_io::operator &=;

			bit_t<adcsr_io, 0>	EXTRG;
			bit_t<adcsr_io, 1>	TRGE;
			bits_t<adcsr_io, 2, 2>	CKS;
			bit_t<adcsr_io, 4>	ADIE;
			bit_t<adcsr_io, 6>	ADCS;
			bit_t<adcsr_io, 7>	ADST;
		};
		static adcsr_t	ADCSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADANS レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x04> adans_io;
		struct adans_t : public adans_io {
			using adans_io::operator =;
			using adans_io::operator ();
			using adans_io::operator |=;
			using adans_io::operator &=;

			bits_t<adans_io, 0, 8>	ANS;
		};
		static adans_t	ADANS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADADS レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x08> adads_io;
		struct adads_t : public adads_io {
			using adads_io::operator =;
			using adads_io::operator ();
			using adads_io::operator |=;
			using adads_io::operator &=;

			bits_t<adads_io, 0, 8>	ADS;
		};
		static adads_t	ADADS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADADC レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x0c> adadc_io;
		struct adadc_t : public adadc_io {
			using adads_io::operator =;
			using adads_io::operator ();
			using adads_io::operator |=;
			using adads_io::operator &=;

			bits_t<adads_io, 0, 2>	ADC;
		};
		static adadc_t	ADADC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADCER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x0e> adcer_io;
		struct adcer_t : public adcer_io {
			using adcer_io::operator =;
			using adcer_io::operator ();
			using adcer_io::operator |=;
			using adcer_io::operator &=;

			bit_t<adcer_io,  5>	ACE;
			bit_t<adcer_io, 15>	ADRFMT;
		};
		static adcer_t	ADCER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ADSTRGR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x10> adstrgr_io;
		struct adstrgr_t : public adstrgr_io {
			using adstrgr_io::operator =;
			using adstrgr_io::operator ();
			using adstrgr_io::operator |=;
			using adstrgr_io::operator &=;

			bits_t<adstrgr_io, 0, 4>	ADSTRS;
		};
		static adstrgr_t	ADSTRGR;

	};
	typedef s12ad_t<0x00089000> S12AD;
}
