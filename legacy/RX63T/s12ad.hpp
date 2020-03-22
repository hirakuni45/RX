#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63 グループ・S12AD 定義
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
		@brief  S12AD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D データレジスタ y（ADDRy）（y = ０～７）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct addrx_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B12, 0>    AD;
		};
		static addrx_t<0x20> ADDR0;
		static addrx_t<0x22> ADDR1;
		static addrx_t<0x24> ADDR2;
		static addrx_t<0x26> ADDR3;
		static addrx_t<0x28> ADDR4;
		static addrx_t<0x2a> ADDR5;
		static addrx_t<0x2c> ADDR6;
		static addrx_t<0x2e> ADDR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D コントロールレジスタ（ADCSR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x00> adcsr_io;
		struct adcsr_t : public adcsr_io {
			using adcsr_io::operator =;
			using adcsr_io::operator ();
			using adcsr_io::operator |=;
			using adcsr_io::operator &=;

			bits_rw_t<adcsr_io, bitpos::B0, 5>  DBLANS;
			bit_rw_t <adcsr_io, bitpos::B6>     GBADIE;
			bit_rw_t <adcsr_io, bitpos::B7>     DBLE;
			bit_rw_t <adcsr_io, bitpos::B8>     EXTRG;
			bit_rw_t <adcsr_io, bitpos::B9>     TRGE;
			bit_rw_t <adcsr_io, bitpos::B12>    ADIE;
			bits_rw_t<adcsr_io, bitpos::B13, 2> ADCS;
			bit_rw_t <adcsr_io, bitpos::B15>    ADST;
		};
		static adcsr_t	ADCSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタＡ（ADANSA）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x04> adansa_io;
		struct adansa_t : public adansa_io {
			using adansa_io::operator =;
			using adansa_io::operator ();
			using adansa_io::operator |=;
			using adansa_io::operator &=;

			bits_rw_t<adansa_io, bitpos::B0, 8>	ANSA;
		};
		static adansa_t  ADANSA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタＢ（ADANSB）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x14> adansb_io;
		struct adansb_t : public adansb_io {
			using adansb_io::operator =;
			using adansb_io::operator ();
			using adansb_io::operator |=;
			using adansb_io::operator &=;

			bits_rw_t<adansb_io, bitpos::B0, 8>	ANSB;
		};
		static adansb_t  ADANSB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x08> adads_io;
		struct adads_t : public adads_io {
			using adads_io::operator =;
			using adads_io::operator ();
			using adads_io::operator |=;
			using adads_io::operator &=;

			bits_rw_t<adads_io, bitpos::B0, 8>	ADS;
		};
		static adads_t	ADADS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換値加算回数選択レジスタ（ADADC）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x0c> adadc_io;
		struct adadc_t : public adadc_io {
			using adadc_io::operator =;
			using adadc_io::operator ();
			using adadc_io::operator |=;
			using adadc_io::operator &=;

			bits_rw_t<adadc_io, bitpos::B0, 2>	ADC;
		};
		static adadc_t	ADADC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D コントロール拡張レジスタ（ADCER）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x0e> adcer_io;
		struct adcer_t : public adcer_io {
			using adcer_io::operator =;
			using adcer_io::operator ();
			using adcer_io::operator |=;
			using adcer_io::operator &=;

			bits_rw_t<adcer_io, bitpos::B1, 2> ADPRC;
			bit_rw_t< adcer_io, bitpos::B4>    DCE;
			bit_rw_t< adcer_io, bitpos::B5>    ACE;
			bits_rw_t<adcer_io, bitpos::B8, 2> DIAGVAL;
			bit_rw_t< adcer_io, bitpos::B10>   DIAGLD;
			bit_rw_t< adcer_io, bitpos::B11>   DIAGM;
			bit_rw_t< adcer_io, bitpos::B15>   ADRFMT;
		};
		static adcer_t	ADCER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 開始トリガ選択レジスタ（ADSTRGR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x10> adstrgr_io;
		struct adstrgr_t : public adstrgr_io {
			using adstrgr_io::operator =;
			using adstrgr_io::operator ();
			using adstrgr_io::operator |=;
			using adstrgr_io::operator &=;

			bits_rw_t<adstrgr_io, bitpos::B0, 5>  TRSB;
			bits_rw_t<adstrgr_io, bitpos::B8, 5>  TRSA;
		};
		static adstrgr_t	ADSTRGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTRn）（n=0..7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<base + 0x60> ADSSTR0;
		static rw8_t<base + 0x73> ADSSTR1;
		static rw8_t<base + 0x74> ADSSTR2;
		static rw8_t<base + 0x75> ADSSTR3;
		static rw8_t<base + 0x76> ADSSTR4;
		static rw8_t<base + 0x77> ADSSTR5;
		static rw8_t<base + 0x78> ADSSTR6;
		static rw8_t<base + 0x79> ADSSTR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サンプル＆ホールド回路コントロールレジスタ（ADSHCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x66> adshcr_io;
		struct adshcr_t : public adshcr_io {
			using adshcr_io::operator =;
			using adshcr_io::operator ();
			using adshcr_io::operator |=;
			using adshcr_io::operator &=;

			bits_rw_t<adshcr_io, bitpos::B0, 8>  SSTSH;
			bits_rw_t<adshcr_io, bitpos::B8, 3>  SHANS;
		};
		static adshcr_t	ADSHCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D グループスキャン優先コントロールレジスタ（ADGSPCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x80> adgspcr_io;
		struct adgspcr_t : public adgspcr_io {
			using adgspcr_io::operator =;
			using adgspcr_io::operator ();
			using adgspcr_io::operator |=;
			using adgspcr_io::operator &=;

			bit_rw_t<adgspcr_io, bitpos::B0>  PGS;
			bit_rw_t<adgspcr_io, bitpos::B1>  GBRSCN;
			bit_rw_t<adgspcr_io, bitpos::B15>  GBRP;
		};
		static adgspcr_t	ADGSPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  最大チャネル数を返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_max_chanel() { return 1; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADx 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adx_t {


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  最大チャネル数を返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_max_chanel() { return 2; }
	};

	// [64/48ピン版]
	typedef s12ad_t <0x00089000> S12AD;

	// [144/120/112/100ピン版]
	typedef s12adx_t<0x00089000> S12ADA;
	typedef s12adx_t<0x00089100> S12ADB;
}
