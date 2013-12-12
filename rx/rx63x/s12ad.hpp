#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63 グループ・S12AD 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "../io_utils.hpp"

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
			@brief  A/D コントロールレジスタ（ADCSR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x00> adcsr_io;
		struct adcsr_t : public adcsr_io {
			using adcsr_io::operator =;
			using adcsr_io::operator ();
			using adcsr_io::operator |=;
			using adcsr_io::operator &=;

			bits_t<adcsr_io,  0, 5> DBLANS;
			bit_t< adcsr_io,  6>    GBADIE;
			bit_t< adcsr_io,  7>    DBLE;
			bit_t< adcsr_io,  8>    EXTRG;
			bit_t< adcsr_io,  9>    TRGE;
			bit_t< adcsr_io, 12>    ADIE;
			bits_t<adcsr_io, 13, 2> ADCS;
			bit_t< adcsr_io, 15>    ADST;
		};
		static adcsr_t	ADCSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタＡ（ADANSA）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x04> adansa_io;
		struct adansa_t : public adansa_io {
			using adansa_io::operator =;
			using adansa_io::operator ();
			using adansa_io::operator |=;
			using adansa_io::operator &=;

			bits<adansa_io, 0, 8>	ANSA;
		};
		static adansa_t  ADANSA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタＢ（ADANSB）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x14> adansb_io;
		struct adansb_t : public adansb_io {
			using adansb_io::operator =;
			using adansb_io::operator ();
			using adansb_io::operator |=;
			using adansb_io::operator &=;

			bits<adansb_io, 0, 8>	ANSB;
		};
		static adansb_t  ADANSB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x08> adads_io;
		struct adads_t : public adads_io {
			using adads_io::operator =;
			using adads_io::operator ();
			using adads_io::operator |=;
			using adads_io::operator &=;

			bits<adads_io, 0, 8>	ADS;
		};
		static adads_t	ADADS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換値加算回数選択レジスタ（ADADC）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x0c> adadc_io;
		struct adadc_t : public adadc_io {
			using adads_io::operator =;
			using adads_io::operator ();
			using adads_io::operator |=;
			using adads_io::operator &=;

			bits<adads_io, 0, 2>	ADC;
		};
		static adadc_t	ADADC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D コントロール拡張レジスタ（ADCER）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x0e> adcer_io;
		struct adcer_t : public adcer_io {
			using adcer_io::operator =;
			using adcer_io::operator ();
			using adcer_io::operator |=;
			using adcer_io::operator &=;

			bits_t<adcer_io,  1, 2>	ADPRC;
			bit_t< adcer_io,  4>    DCE;
			bit_t< adcer_io,  5>    ACE;
			bits_t<adcer_io,  8, 2>	DIAGVAL;
			bit_t< adcer_io, 10>    DIAGLD;
			bit_t< adcer_io, 11>    DIAGM;
			bit_t< adcer_io, 15>    ADRFMT;
		};
		static adcer_t	ADCER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 開始トリガ選択レジスタ（ADSTRGR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x10> adstrgr_io;
		struct adstrgr_t : public adstrgr_io {
			using adstrgr_io::operator =;
			using adstrgr_io::operator ();
			using adstrgr_io::operator |=;
			using adstrgr_io::operator &=;

			bits_t<adstrgr_io, 0, 5>  TRSB;
			bits_t<adstrgr_io, 8, 5>  TRSA;
		};
		static adstrgr_t	ADSTRGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTRn）（n=0..7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static io8<base + 0x60> ADSSTR0;
		static io8<base + 0x73> ADSSTR1;
		static io8<base + 0x74> ADSSTR2;
		static io8<base + 0x75> ADSSTR3;
		static io8<base + 0x76> ADSSTR4;
		static io8<base + 0x77> ADSSTR5;
		static io8<base + 0x78> ADSSTR6;
		static io8<base + 0x79> ADSSTR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サンプル＆ホールド回路コントロールレジスタ（ADSHCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x66> adshcr_io;
		struct adshcr_t : public adshcr_io {
			using adshcr_io::operator =;
			using adshcr_io::operator ();
			using adshcr_io::operator |=;
			using adshcr_io::operator &=;

			bits_t<adshcr_io, 0, 8>  SSTSH;
			bits_t<adshcr_io, 8, 3>  SHANS;
		};
		static adshcr_t	ADSHCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D グループスキャン優先コントロールレジスタ（ADGSPCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<base + 0x80> adgspcr_io;
		struct adgspcr_t : public adgspcr_io {
			using adgspcr_io::operator =;
			using adgspcr_io::operator ();
			using adgspcr_io::operator |=;
			using adgspcr_io::operator &=;

			bit_t<adgspcr_io,  0>  PGS;
			bit_t<adgspcr_io,  1>  GBRSCN;
			bit_t<adgspcr_io, 15>  GBRP;
		};
		static adgspcr_t	ADGSPCR;






	};
	typedef s12ad_t<0x00089000> S12AD;
}
