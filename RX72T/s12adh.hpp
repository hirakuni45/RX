#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ・S12ADH 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADH 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adh_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 0（ADDR0）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x20> ADDR0_;
		static  ADDR0_ ADDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 1（ADDR1）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x22> ADDR1_;
		static  ADDR1_ ADDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 2（ADDR2）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x24> ADDR2_;
		static  ADDR2_ ADDR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 3（ADDR3）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x26> ADDR3_;
		static  ADDR3_ ADDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 4（ADDR4）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x28> ADDR4_;
		static  ADDR4_ ADDR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 5（ADDR5）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2A> ADDR5_;
		static  ADDR5_ ADDR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 6（ADDR6）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2C> ADDR6_;
		static  ADDR6_ ADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 7（ADDR7）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2E> ADDR7_;
		static  ADDR7_ ADDR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x18> ADDBLDR_;
		static  ADDBLDR_ ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ A（ADDBLDRA）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x84> ADDBLDRA_;
		static  ADDBLDRA_ ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ B（ADDBLDRB）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x86> ADDBLDRB_;
		static  ADDBLDRB_ ADDBLDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ (ADRD)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1E> ADRD_;
		static  ADRD_ ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロールレジスタ（ADCSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  DBLANS;

			bit_rw_t <io_, bitpos::B6>     GBADIE;
			bit_rw_t <io_, bitpos::B7>     DBLE;
			bit_rw_t <io_, bitpos::B8>     EXTRG;
			bit_rw_t <io_, bitpos::B9>     TRGE;

			bit_rw_t <io_, bitpos::B12>    ADIE;
			bits_rw_t<io_, bitpos::B13, 2> ADCS;
			bit_rw_t <io_, bitpos::B15>    ADST;
		};
		typedef adcsr_t<base + 0x00>  ADCSR_;
		static  ADCSR_ ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS0)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C0> ADSCS0_;
		static  ADSCS0_ ADSCS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS1)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C1> ADSCS1_;
		static  ADSCS1_ ADSCS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS2)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C2> ADSCS2_;
		static  ADSCS2_ ADSCS2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS3)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C3> ADSCS3_;
		static  ADSCS3_ ADSCS3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS4)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C4> ADSCS4_;
		static  ADSCS4_ ADSCS4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS5)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C5> ADSCS5_;
		static  ADSCS5_ ADSCS5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS6)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C6> ADSCS6_;
		static  ADSCS6_ ADSCS6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS7)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C7> ADSCS7_;
		static  ADSCS7_ ADSCS7;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均回数選択レジスタ（ADADC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adadc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  ADC;

			bit_rw_t <io_, bitpos::B7>     AVEE;
		};
		typedef adadc_t<base + 0x0C>  ADADC_;
		static  ADADC_ ADADC;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロール拡張レジスタ（ADCER）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcer_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B5>     ACE;

			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;

			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		typedef adcer_t<base + 0x0E>  ADCER_;
		static  ADCER_ ADCER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始トリガ選択レジスタ（ADSTRGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adstrgr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  TRSB;

			bits_rw_t<io_, bitpos::B8, 6>  TRSA;
		};
		typedef adstrgr_t<base + 0x10>  ADSTRGR_;
		static  ADSTRGR_ ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C トリガ選択レジスタ（ADGCTRGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgctrgr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  TRSC;
			bit_rw_t <io_, bitpos::B6>     GCADIE;
			bit_rw_t <io_, bitpos::B7>     GRCE;
		};
		typedef adgctrgr_t<base + 0xD9>  ADGCTRGR_;
		static  ADGCTRGR_ ADGCTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE1> ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE2> ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE3> ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE4> ADSSTR4_;
		static  ADSSTR4_ ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE5> ADSSTR5_;
		static  ADSSTR5_ ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE6> ADSSTR6_;
		static  ADSSTR6_ ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE7> ADSSTR7_;
		static  ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 断線検出コントロールレジスタ（ADDISCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ADNDIS;
		};
		typedef addiscr_t<base + 0x7A>  ADDISCR_;
		static  ADDISCR_ ADDISCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D イベントリンクコントロールレジスタ (ADELCCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adelccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  ELCC;
		};
		typedef adelccr_t<base + 0x7D>  ADELCCR_;
		static  ADELCCR_ ADELCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループスキャン優先コントロールレジスタ（ADGSPCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgspcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   PGS;
			bit_rw_t<io_, bitpos::B1>   GBRSCN;

			bit_rw_t<io_, bitpos::B14>  LGRRS;
			bit_rw_t<io_, bitpos::B15>  GBRP;
		};
		typedef adgspcr_t<base + 0x80>  ADGSPCR_;
		static  ADGSPCR_ ADGSPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能コントロールレジスタ (ADCMPCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CMPAB;

			bit_rw_t <io_, bitpos::B9>     CMPBE;

			bit_rw_t <io_, bitpos::B11>    CMPAE;

			bit_rw_t <io_, bitpos::B13>    CMPBIE;
			bit_rw_t <io_, bitpos::B14>    WCMPBE;
			bit_rw_t <io_, bitpos::B15>    CMPAIE;
		};
		typedef adcmpcr_t<base + 0x90>  ADCMPCR_;
		static  ADCMPCR_ ADCMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 下位側レベル設定レジスタ (ADCMPDR0)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9C> ADCMPDR0_;
		static  ADCMPDR0_ ADCMPDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 上位側レベル設定レジスタ (ADCMPDR1)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9E> ADCMPDR1_;
		static  ADCMPDR1_ ADCMPDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A/B ステータスモニタレジスタ（ ADWINMON ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adwinmon_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   MONCOMB;

			bit_rw_t<io_, bitpos::B4>   MONCMPA;
			bit_rw_t<io_, bitpos::B5>   MONCMPB;
		};
		typedef adwinmon_t<base + 0x8C>  ADWINMON_;
		static  ADWINMON_ ADWINMON;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B チャネル選択レジスタ (ADCMPBNSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbnsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   CMPCHB;

			bit_rw_t <io_, bitpos::B7>      CMPLB;
		};
		typedef adcmpbnsr_t<base + 0xA6>  ADCMPBNSR_;
		static  ADCMPBNSR_ ADCMPBNSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 下位側レベル設定レジスタ（ ADWINLLB ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xA8> ADWINLLB_;
		static  ADWINLLB_ ADWINLLB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 上位側レベル設定レジスタ（ ADWINULB ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xAA> ADWINULB_;
		static  ADWINULB_ ADWINULB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B チャネルステータスレジスタ (ADCMPBSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTB;
		};
		typedef adcmpbsr_t<base + 0xAC>  ADCMPBSR_;
		static  ADCMPBSR_ ADCMPBSR;
	};
	template <uint32_t base> typename s12adh_base_t<base>::ADDR0_ s12adh_base_t<base>::ADDR0;
	template <uint32_t base> typename s12adh_base_t<base>::ADDR1_ s12adh_base_t<base>::ADDR1;
	template <uint32_t base> typename s12adh_base_t<base>::ADDR2_ s12adh_base_t<base>::ADDR2;
	template <uint32_t base> typename s12adh_base_t<base>::ADDR3_ s12adh_base_t<base>::ADDR3;
	template <uint32_t base> typename s12adh_base_t<base>::ADDR4_ s12adh_base_t<base>::ADDR4;
	template <uint32_t base> typename s12adh_base_t<base>::ADDR5_ s12adh_base_t<base>::ADDR5;
	template <uint32_t base> typename s12adh_base_t<base>::ADDR6_ s12adh_base_t<base>::ADDR6;
	template <uint32_t base> typename s12adh_base_t<base>::ADDR7_ s12adh_base_t<base>::ADDR7;
	template <uint32_t base> typename s12adh_base_t<base>::ADDBLDR_ s12adh_base_t<base>::ADDBLDR;
	template <uint32_t base> typename s12adh_base_t<base>::ADDBLDRA_ s12adh_base_t<base>::ADDBLDRA;
	template <uint32_t base> typename s12adh_base_t<base>::ADDBLDRB_ s12adh_base_t<base>::ADDBLDRB;
	template <uint32_t base> typename s12adh_base_t<base>::ADRD_ s12adh_base_t<base>::ADRD;
	template <uint32_t base> typename s12adh_base_t<base>::ADCSR_ s12adh_base_t<base>::ADCSR;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS0_ s12adh_base_t<base>::ADSCS0;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS1_ s12adh_base_t<base>::ADSCS1;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS2_ s12adh_base_t<base>::ADSCS2;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS3_ s12adh_base_t<base>::ADSCS3;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS4_ s12adh_base_t<base>::ADSCS4;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS5_ s12adh_base_t<base>::ADSCS5;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS6_ s12adh_base_t<base>::ADSCS6;
	template <uint32_t base> typename s12adh_base_t<base>::ADSCS7_ s12adh_base_t<base>::ADSCS7;
	template <uint32_t base> typename s12adh_base_t<base>::ADADC_ s12adh_base_t<base>::ADADC;
	template <uint32_t base> typename s12adh_base_t<base>::ADCER_ s12adh_base_t<base>::ADCER;
	template <uint32_t base> typename s12adh_base_t<base>::ADSTRGR_ s12adh_base_t<base>::ADSTRGR;
	template <uint32_t base> typename s12adh_base_t<base>::ADGCTRGR_ s12adh_base_t<base>::ADGCTRGR;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR0_ s12adh_base_t<base>::ADSSTR0;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR1_ s12adh_base_t<base>::ADSSTR1;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR2_ s12adh_base_t<base>::ADSSTR2;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR3_ s12adh_base_t<base>::ADSSTR3;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR4_ s12adh_base_t<base>::ADSSTR4;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR5_ s12adh_base_t<base>::ADSSTR5;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR6_ s12adh_base_t<base>::ADSSTR6;
	template <uint32_t base> typename s12adh_base_t<base>::ADSSTR7_ s12adh_base_t<base>::ADSSTR7;
	template <uint32_t base> typename s12adh_base_t<base>::ADDISCR_ s12adh_base_t<base>::ADDISCR;
	template <uint32_t base> typename s12adh_base_t<base>::ADELCCR_ s12adh_base_t<base>::ADELCCR;
	template <uint32_t base> typename s12adh_base_t<base>::ADGSPCR_ s12adh_base_t<base>::ADGSPCR;
	template <uint32_t base> typename s12adh_base_t<base>::ADCMPCR_ s12adh_base_t<base>::ADCMPCR;
	template <uint32_t base> typename s12adh_base_t<base>::ADCMPDR0_ s12adh_base_t<base>::ADCMPDR0;
	template <uint32_t base> typename s12adh_base_t<base>::ADCMPDR1_ s12adh_base_t<base>::ADCMPDR1;
	template <uint32_t base> typename s12adh_base_t<base>::ADWINMON_ s12adh_base_t<base>::ADWINMON;
	template <uint32_t base> typename s12adh_base_t<base>::ADCMPBNSR_ s12adh_base_t<base>::ADCMPBNSR;
	template <uint32_t base> typename s12adh_base_t<base>::ADWINLLB_ s12adh_base_t<base>::ADWINLLB;
	template <uint32_t base> typename s12adh_base_t<base>::ADWINULB_ s12adh_base_t<base>::ADWINULB;
	template <uint32_t base> typename s12adh_base_t<base>::ADCMPBSR_ s12adh_base_t<base>::ADCMPBSR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12adh_base_t<base> {

		typedef s12adh_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI;		///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::S12GCADI;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::GROUPBL1::S12CMPBI;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

		static constexpr uint32_t IN_CONV_TIME_NS = 900;	///< A/D 入力 0.9uS、単位「ns」
		static constexpr uint32_t TO_CONV_TIME_NS = 4000;	///< 温度、基準電圧 4uS、単位「ns」

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,
			AN001,
			AN002,
			AN003,
			AN004,
			AN005,
			AN006,
			AN007,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	ena	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN000:
				if(ena) {
					PORT4::PDR.B0 = 0;
					PORT4::PMR.B0 = 0;
				}
				MPC::P40PFS.ASEL = ena;
				break;
			case ANALOG::AN001:
				if(ena) {
					PORT4::PDR.B1 = 0;
					PORT4::PMR.B1 = 0;
				}
				MPC::P41PFS.ASEL = ena;
				break;
			case ANALOG::AN002:
				if(ena) {
					PORT4::PDR.B2 = 0;
					PORT4::PMR.B2 = 0;
				}
				MPC::P42PFS.ASEL = ena;
				break;
			case ANALOG::AN003:
				if(ena) {
					PORT4::PDR.B3 = 0;
					PORT4::PMR.B3 = 0;
				}
				MPC::P43PFS.ASEL = ena;
				break;
			case ANALOG::AN004:
				if(ena) {
					PORTH::PDR.B1 = 0;
					PORTH::PMR.B1 = 0;
				}
				MPC::PH1PFS.ASEL = ena;
				break;
			case ANALOG::AN005:
				if(ena) {
					PORTH::PDR.B2 = 0;
					PORTH::PMR.B2 = 0;
				}
				MPC::PH2PFS.ASEL = ena;
				break;
			case ANALOG::AN006:
				if(ena) {
					PORTH::PDR.B3 = 0;
					PORTH::PMR.B3 = 0;
				}
				MPC::PH3PFS.ASEL = ena;
				break;
			case ANALOG::AN007:
				if(ena) {
					PORTH::PDR.B0 = 0;
					PORTH::PMR.B0 = 0;
				}
				MPC::PH0PFS.ASEL = ena;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ (ADDR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0 (ADANSA0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA000;
			bit_rw_t<io_, bitpos::B1>   ANSA001;
			bit_rw_t<io_, bitpos::B2>   ANSA002;
			bit_rw_t<io_, bitpos::B3>   ANSA003;
			bit_rw_t<io_, bitpos::B4>   ANSA004;
			bit_rw_t<io_, bitpos::B5>   ANSA005;
			bit_rw_t<io_, bitpos::B6>   ANSA006;
			bit_rw_t<io_, bitpos::B7>   ANSA007;
		};
		typedef adansa0_t<base + 0x04>  ADANSA0_;
		static  ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0 (ADANSB0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB000;
			bit_rw_t<io_, bitpos::B1>   ANSB001;
			bit_rw_t<io_, bitpos::B2>   ANSB002;
			bit_rw_t<io_, bitpos::B3>   ANSB003;
			bit_rw_t<io_, bitpos::B4>   ANSB004;
			bit_rw_t<io_, bitpos::B5>   ANSB005;
			bit_rw_t<io_, bitpos::B6>   ANSB006;
			bit_rw_t<io_, bitpos::B7>   ANSB007;
		};
		typedef adansb0_t<base + 0x14>  ADANSB0_;
		static  ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 (ADANSC0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC000;
			bit_rw_t<io_, bitpos::B1>   ANSC001;
			bit_rw_t<io_, bitpos::B2>   ANSC002;
			bit_rw_t<io_, bitpos::B3>   ANSC003;
			bit_rw_t<io_, bitpos::B4>   ANSC004;
			bit_rw_t<io_, bitpos::B5>   ANSC005;
			bit_rw_t<io_, bitpos::B6>   ANSC006;
			bit_rw_t<io_, bitpos::B7>   ANSC007;
		};
		typedef adansc0_t<base + 0xD4>  ADANSC0_;
		static  ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSA0_::address>  ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSB0_::address>  ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSC0_::address>  ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adscs_t<ANALOG, ANALOG::AN007, BASE::ADSCS0_::address> ADSCS_;
		static  ADSCS_ ADSCS;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均機能チャネル選択レジスタ 0 (ADADS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS000;
			bit_rw_t<io_, bitpos::B1>   ADS001;
			bit_rw_t<io_, bitpos::B2>   ADS002;
			bit_rw_t<io_, bitpos::B3>   ADS003;
			bit_rw_t<io_, bitpos::B4>   ADS004;
			bit_rw_t<io_, bitpos::B5>   ADS005;
			bit_rw_t<io_, bitpos::B6>   ADS006;
			bit_rw_t<io_, bitpos::B7>   ADS007;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADADS0_::address>  ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1_t<ANALOG, BASE::ADSSTR0_::address> ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド動作モード選択レジスタ (ADSHMSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshmsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SHMD;
		};
		typedef adshmsr_t<base + 0x7C>  ADSHMSR_;
		static  ADSHMSR_ ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ 0 (ADCMPANSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPCHA007;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static  ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ (ADCMPANSR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPANSR0_::address>  ADCMPANSR_;
		static  ADCMPANSR_ ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 0 (ADCMPLR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPLCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPLCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPLCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPLCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPLCHA007;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static  ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ (ADCMPLR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPLR0_::address>  ADCMPLR_;
		static ADCMPLR_ ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 0 (ADCMPSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPSTCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPSTCHA007;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ (ADCMPSR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPSR0_::address>  ADCMPSR_;
		static ADCMPSR_ ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプコントロールレジスタ (ADPGACR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgacr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P000CR;
			bits_rw_t<io_, bitpos::B4, 4>  P001CR;
			bits_rw_t<io_, bitpos::B8, 4>  P002CR;
		};
		typedef adpgacr_t<base + 0x1A0>  ADPGACR_;
		static  ADPGACR_ ADPGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプゲイン設定レジスタ 0 (ADPGAGS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgags0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P000GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  P001GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  P002GAIN;
		};
		typedef adpgags0_t<base + 0x1A2>  ADPGAGS0_;
		static  ADPGAGS0_ ADPGAGS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプ差動入力コントロールレジスタ (ADPGADCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgadcr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  P000DG;

			bit_rw_t <io_, bitpos::B3>     P000DEN;
			bits_rw_t<io_, bitpos::B4, 2>  P001DG;

			bit_rw_t <io_, bitpos::B7>     P001DEN;
			bits_rw_t<io_, bitpos::B8, 2>  P002DG;

			bit_rw_t <io_, bitpos::B11>    P002DEN;
		};
		typedef adpgadcr0_t<base + 0x1B0>  ADPGADCR0_;
		static  ADPGADCR0_ ADPGADCR0;
	};
	template <uint32_t base> typename s12ad_t<base>::ADDR_ s12ad_t<base>::ADDR;
	template <uint32_t base> typename s12ad_t<base>::ADANSA_ s12ad_t<base>::ADANSA;
	template <uint32_t base> typename s12ad_t<base>::ADANSB_ s12ad_t<base>::ADANSB;
	template <uint32_t base> typename s12ad_t<base>::ADANSC_ s12ad_t<base>::ADANSC;
	template <uint32_t base> typename s12ad_t<base>::ADSCS_ s12ad_t<base>::ADSCS;
	template <uint32_t base> typename s12ad_t<base>::ADADS0_ s12ad_t<base>::ADADS0;
	template <uint32_t base> typename s12ad_t<base>::ADADS_ s12ad_t<base>::ADADS;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR_ s12ad_t<base>::ADSSTR;
	template <uint32_t base> typename s12ad_t<base>::ADSHMSR_ s12ad_t<base>::ADSHMSR;
	template <uint32_t base> typename s12ad_t<base>::ADCMPANSR0_ s12ad_t<base>::ADCMPANSR0;
	template <uint32_t base> typename s12ad_t<base>::ADCMPANSR_ s12ad_t<base>::ADCMPANSR;
	template <uint32_t base> typename s12ad_t<base>::ADCMPLR0_ s12ad_t<base>::ADCMPLR0;
	template <uint32_t base> typename s12ad_t<base>::ADCMPLR_ s12ad_t<base>::ADCMPLR;
	template <uint32_t base> typename s12ad_t<base>::ADCMPSR0_ s12ad_t<base>::ADCMPSR0;
	template <uint32_t base> typename s12ad_t<base>::ADCMPSR_ s12ad_t<base>::ADCMPSR;
	template <uint32_t base> typename s12ad_t<base>::ADPGACR_ s12ad_t<base>::ADPGACR;
	template <uint32_t base> typename s12ad_t<base>::ADPGAGS0_ s12ad_t<base>::ADPGAGS0;
	template <uint32_t base> typename s12ad_t<base>::ADPGADCR0_ s12ad_t<base>::ADPGADCR0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad1_t : public s12adh_base_t<base> {

		typedef s12adh_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI1;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI1;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::S12GCADI1;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI1;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::GROUPBL1::S12CMPBI1;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN100,
			AN101,
			AN102,
			AN103,
			AN104,
			AN105,
			AN106,
			AN107,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	ena	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN100:
				if(ena) {
					PORT4::PDR.B4 = 0;
					PORT4::PMR.B4 = 0;
				}
				MPC::P44PFS.ASEL = ena;
				break;
			case ANALOG::AN101:
				if(ena) {
					PORT4::PDR.B5 = 0;
					PORT4::PMR.B5 = 0;
				}
				MPC::P45PFS.ASEL = ena;
				break;
			case ANALOG::AN102:
				if(ena) {
					PORT4::PDR.B6 = 0;
					PORT4::PMR.B6 = 0;
				}
				MPC::P46PFS.ASEL = ena;
				break;
			case ANALOG::AN103:
				if(ena) {
					PORT4::PDR.B7 = 0;
					PORT4::PMR.B7 = 0;
				}
				MPC::P47PFS.ASEL = ena;
				break;
			case ANALOG::AN104:
				if(ena) {
					PORTH::PDR.B5 = 0;
					PORTH::PMR.B5 = 0;
				}
				MPC::PH5PFS.ASEL = ena;
				break;
			case ANALOG::AN105:
				if(ena) {
					PORTH::PDR.B6 = 0;
					PORTH::PMR.B6 = 0;
				}
				MPC::PH6PFS.ASEL = ena;
				break;
			case ANALOG::AN106:
				if(ena) {
					PORTH::PDR.B7 = 0;
					PORTH::PMR.B7 = 0;
				}
				MPC::PH7PFS.ASEL = ena;
				break;
			case ANALOG::AN107:
				if(ena) {
					PORTH::PDR.B4 = 0;
					PORTH::PMR.B4 = 0;
				}
				MPC::PH4PFS.ASEL = ena;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ (ADDR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0 (ADANSA0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA000;
			bit_rw_t<io_, bitpos::B1>   ANSA001;
			bit_rw_t<io_, bitpos::B2>   ANSA002;
			bit_rw_t<io_, bitpos::B3>   ANSA003;
			bit_rw_t<io_, bitpos::B4>   ANSA004;
			bit_rw_t<io_, bitpos::B5>   ANSA005;
			bit_rw_t<io_, bitpos::B6>   ANSA006;
			bit_rw_t<io_, bitpos::B7>   ANSA007;
		};
		typedef adansa0_t<base + 0x04>  ADANSA0_;
		static  ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0 (ADANSB0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB000;
			bit_rw_t<io_, bitpos::B1>   ANSB001;
			bit_rw_t<io_, bitpos::B2>   ANSB002;
			bit_rw_t<io_, bitpos::B3>   ANSB003;
			bit_rw_t<io_, bitpos::B4>   ANSB004;
			bit_rw_t<io_, bitpos::B5>   ANSB005;
			bit_rw_t<io_, bitpos::B6>   ANSB006;
			bit_rw_t<io_, bitpos::B7>   ANSB007;
		};
		typedef adansb0_t<base + 0x14>  ADANSB0_;
		static  ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 (ADANSC0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC000;
			bit_rw_t<io_, bitpos::B1>   ANSC001;
			bit_rw_t<io_, bitpos::B2>   ANSC002;
			bit_rw_t<io_, bitpos::B3>   ANSC003;
			bit_rw_t<io_, bitpos::B4>   ANSC004;
			bit_rw_t<io_, bitpos::B5>   ANSC005;
			bit_rw_t<io_, bitpos::B6>   ANSC006;
			bit_rw_t<io_, bitpos::B7>   ANSC007;
		};
		typedef adansc0_t<base + 0xD4>  ADANSC0_;
		static  ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSA0_::address>  ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSB0_::address>  ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSC0_::address>  ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adscs_t<ANALOG, ANALOG::AN107, BASE::ADSCS0_::address> ADSCS_;
		static  ADSCS_ ADSCS;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均機能チャネル選択レジスタ 0 (ADADS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS000;
			bit_rw_t<io_, bitpos::B1>   ADS001;
			bit_rw_t<io_, bitpos::B2>   ADS002;
			bit_rw_t<io_, bitpos::B3>   ADS003;
			bit_rw_t<io_, bitpos::B4>   ADS004;
			bit_rw_t<io_, bitpos::B5>   ADS005;
			bit_rw_t<io_, bitpos::B6>   ADS006;
			bit_rw_t<io_, bitpos::B7>   ADS007;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADADS0_::address>  ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1_t<ANALOG, BASE::ADSSTR0_::address> ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド回路コントロールレジスタ (ADSHCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SSTSH;
			bits_rw_t<io_, bitpos::B8, 3>  SHANS;
		};
		typedef adshcr_t<base + 0x66>  ADSHCR_;
		static  ADSHCR_ ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド動作モード選択レジスタ (ADSHMSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshmsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SHMD;
		};
		typedef adshmsr_t<base + 0x7C>  ADSHMSR_;
		static  ADSHMSR_ ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ 0 (ADCMPANSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPCHA007;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static  ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ (ADCMPANSR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPANSR0_::address>  ADCMPANSR_;
		static  ADCMPANSR_ ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 0 (ADCMPLR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPLCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPLCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPLCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPLCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPLCHA007;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static  ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ (ADCMPLR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPLR0_::address>  ADCMPLR_;
		static ADCMPLR_ ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 0 (ADCMPSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPSTCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPSTCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPSTCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPSTCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPSTCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPSTCHA011;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;
	

		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ (ADCMPSR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPSR0_::address>  ADCMPSR_;
		static ADCMPSR_ ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプコントロールレジスタ (ADPGACR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgacr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P100CR;
			bits_rw_t<io_, bitpos::B4, 4>  P101CR;
			bits_rw_t<io_, bitpos::B8, 4>  P102CR;
		};
		typedef adpgacr_t<base + 0x1A0>  ADPGACR_;
		static  ADPGACR_ ADPGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプゲイン設定レジスタ 0 (ADPGAGS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgags0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P100GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  P101GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  P102GAIN;
		};
		typedef adpgags0_t<base + 0x1A2>  ADPGAGS0_;
		static  ADPGAGS0_ ADPGAGS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプ差動入力コントロールレジスタ (ADPGADCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgadcr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  P100DG;

			bit_rw_t <io_, bitpos::B3>     P100DEN;
			bits_rw_t<io_, bitpos::B4, 2>  P101DG;

			bit_rw_t <io_, bitpos::B7>     P101DEN;
			bits_rw_t<io_, bitpos::B8, 2>  P102DG;

			bit_rw_t <io_, bitpos::B11>    P102DEN;
		};
		typedef adpgadcr0_t<base + 0x1B0>  ADPGADCR0_;
		static  ADPGADCR0_ ADPGADCR0;
	};
	template <uint32_t base> typename s12ad1_t<base>::ADDR_ s12ad1_t<base>::ADDR;
	template <uint32_t base> typename s12ad1_t<base>::ADANSA_ s12ad1_t<base>::ADANSA;
	template <uint32_t base> typename s12ad1_t<base>::ADANSB_ s12ad1_t<base>::ADANSB;
	template <uint32_t base> typename s12ad1_t<base>::ADANSC_ s12ad1_t<base>::ADANSC;
	template <uint32_t base> typename s12ad1_t<base>::ADSCS_ s12ad1_t<base>::ADSCS;
	template <uint32_t base> typename s12ad1_t<base>::ADADS0_ s12ad1_t<base>::ADADS0;
	template <uint32_t base> typename s12ad1_t<base>::ADADS_ s12ad1_t<base>::ADADS;
	template <uint32_t base> typename s12ad1_t<base>::ADSSTR_ s12ad1_t<base>::ADSSTR;
	template <uint32_t base> typename s12ad1_t<base>::ADSHCR_ s12ad1_t<base>::ADSHCR;
	template <uint32_t base> typename s12ad1_t<base>::ADSHMSR_ s12ad1_t<base>::ADSHMSR;
	template <uint32_t base> typename s12ad1_t<base>::ADCMPANSR0_ s12ad1_t<base>::ADCMPANSR0;
	template <uint32_t base> typename s12ad1_t<base>::ADCMPANSR_ s12ad1_t<base>::ADCMPANSR;
	template <uint32_t base> typename s12ad1_t<base>::ADCMPLR0_ s12ad1_t<base>::ADCMPLR0;
	template <uint32_t base> typename s12ad1_t<base>::ADCMPLR_ s12ad1_t<base>::ADCMPLR;
	template <uint32_t base> typename s12ad1_t<base>::ADCMPSR0_ s12ad1_t<base>::ADCMPSR0;
	template <uint32_t base> typename s12ad1_t<base>::ADCMPSR_ s12ad1_t<base>::ADCMPSR;
	template <uint32_t base> typename s12ad1_t<base>::ADPGACR_ s12ad1_t<base>::ADPGACR;
	template <uint32_t base> typename s12ad1_t<base>::ADPGAGS0_ s12ad1_t<base>::ADPGAGS0;
	template <uint32_t base> typename s12ad1_t<base>::ADPGADCR0_ s12ad1_t<base>::ADPGADCR0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD2 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad2_t : public s12adh_base_t<base> {

		typedef s12adh_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD2;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI2;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI2;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::S12GCADI2;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI2;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::GROUPBL1::S12CMPBI2;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元

		static constexpr uint32_t ANALOG_NUM = 14;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN200,
			AN201,
			AN202,
			AN203,
			AN204,
			AN205,
			AN206,
			AN207,
			AN208,
			AN209,
			AN210,
			AN211,

			AN216 = 16,
			AN217,

			TEMP,		///< 温度センサ
			REF,		///< 内部基準電圧
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	ena	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN200:
				if(ena) {
					PORT5::PDR.B2 = 0;
					PORT5::PMR.B2 = 0;
				}
				MPC::P52PFS.ASEL = ena;
				break;
			case ANALOG::AN201:
				if(ena) {
					PORT5::PDR.B3 = 0;
					PORT5::PMR.B3 = 0;
				}
				MPC::P53PFS.ASEL = ena;
				break;
			case ANALOG::AN202:
				if(ena) {
					PORT5::PDR.B4 = 0;
					PORT5::PMR.B4 = 0;
				}
				MPC::P54PFS.ASEL = ena;
				break;
			case ANALOG::AN203:
				if(ena) {
					PORT5::PDR.B5 = 0;
					PORT5::PMR.B5 = 0;
				}
				MPC::P55PFS.ASEL = ena;
				break;
			case ANALOG::AN204:
				if(ena) {
					PORT5::PDR.B0 = 0;
					PORT5::PMR.B0 = 0;
				}
				MPC::P50PFS.ASEL = ena;
				break;
			case ANALOG::AN205:
				if(ena) {
					PORT5::PDR.B1 = 0;
					PORT5::PMR.B1 = 0;
				}
				MPC::P51PFS.ASEL = ena;
				break;
			case ANALOG::AN206:
				if(ena) {
					PORT6::PDR.B0 = 0;
					PORT6::PMR.B0 = 0;
				}
				MPC::P60PFS.ASEL = ena;
				break;
			case ANALOG::AN207:
				if(ena) {
					PORT6::PDR.B1 = 0;
					PORT6::PMR.B1 = 0;
				}
				MPC::P61PFS.ASEL = ena;
				break;
			case ANALOG::AN208:
				if(ena) {
					PORT6::PDR.B2 = 0;
					PORT6::PMR.B2 = 0;
				}
				MPC::P62PFS.ASEL = ena;
				break;
			case ANALOG::AN209:
				if(ena) {
					PORT6::PDR.B3 = 0;
					PORT6::PMR.B3 = 0;
				}
				MPC::P63PFS.ASEL = ena;
				break;
			case ANALOG::AN210:
				if(ena) {
					PORT6::PDR.B4 = 0;
					PORT6::PMR.B4 = 0;
				}
				MPC::P64PFS.ASEL = ena;
				break;
			case ANALOG::AN211:
				if(ena) {
					PORT6::PDR.B5 = 0;
					PORT6::PMR.B5 = 0;
				}
				MPC::P65PFS.ASEL = ena;
				break;

			case ANALOG::AN216:
				if(ena) {
					PORT2::PDR.B0 = 0;
					PORT2::PMR.B0 = 0;
				}
				MPC::P20PFS.ASEL = ena;
				break;
			case ANALOG::AN217:
				if(ena) {
					PORT2::PDR.B1 = 0;
					PORT2::PMR.B1 = 0;
				}
				MPC::P21PFS.ASEL = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 8（ADDR8）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x30> ADDR8_;
		static  ADDR8_ ADDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 9（ADDR9）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x32> ADDR9_;
		static  ADDR9_ ADDR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 10（ADDR10）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x34> ADDR10_;
		static  ADDR10_ ADDR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 11（ADDR11）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x36> ADDR11_;
		static  ADDR11_ ADDR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> ADDR16_;
		static  ADDR16_ ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 17（ADDR17）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x42> ADDR17_;
		static  ADDR17_ ADDR17;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ (ADTSDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1A> ADTSDR_;
		static  ADTSDR_ ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ (ADOCDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1C> ADOCDR_;
		static  ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ (ADDR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_tr_t<ANALOG, BASE::ADDR0_::address,
			ANALOG::TEMP, ADTSDR_::address, ANALOG::REF, ADOCDR_::address> ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0 (ADANSA0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA000;
			bit_rw_t<io_, bitpos::B1>   ANSA001;
			bit_rw_t<io_, bitpos::B2>   ANSA002;
			bit_rw_t<io_, bitpos::B3>   ANSA003;
			bit_rw_t<io_, bitpos::B4>   ANSA004;
			bit_rw_t<io_, bitpos::B5>   ANSA005;
			bit_rw_t<io_, bitpos::B6>   ANSA006;
			bit_rw_t<io_, bitpos::B7>   ANSA007;
			bit_rw_t<io_, bitpos::B8>   ANSA008;
			bit_rw_t<io_, bitpos::B9>   ANSA009;
			bit_rw_t<io_, bitpos::B10>  ANSA010;
			bit_rw_t<io_, bitpos::B11>  ANSA011;
		};
		typedef adansa0_t<base + 0x04>  ADANSA0_;
		static  ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A1 (ADANSA1)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA100;
			bit_rw_t<io_, bitpos::B1>   ANSA101;
		};
		typedef adansa1_t<base + 0x06>  ADANSA1_;
		static  ADANSA1_ ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0 (ADANSB0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB000;
			bit_rw_t<io_, bitpos::B1>   ANSB001;
			bit_rw_t<io_, bitpos::B2>   ANSB002;
			bit_rw_t<io_, bitpos::B3>   ANSB003;
			bit_rw_t<io_, bitpos::B4>   ANSB004;
			bit_rw_t<io_, bitpos::B5>   ANSB005;
			bit_rw_t<io_, bitpos::B6>   ANSB006;
			bit_rw_t<io_, bitpos::B7>   ANSB007;
			bit_rw_t<io_, bitpos::B8>   ANSB008;
			bit_rw_t<io_, bitpos::B9>   ANSB009;
			bit_rw_t<io_, bitpos::B10>  ANSB010;
			bit_rw_t<io_, bitpos::B11>  ANSB011;
		};
		typedef adansb0_t<base + 0x14>  ADANSB0_;
		static  ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1 (ADANSB1)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB100;
			bit_rw_t<io_, bitpos::B1>   ANSB101;
		};
		typedef adansb1_t<base + 0x16>  ADANSB1_;
		static  ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 (ADANSC0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC000;
			bit_rw_t<io_, bitpos::B1>   ANSC001;
			bit_rw_t<io_, bitpos::B2>   ANSC002;
			bit_rw_t<io_, bitpos::B3>   ANSC003;
			bit_rw_t<io_, bitpos::B4>   ANSC004;
			bit_rw_t<io_, bitpos::B5>   ANSC005;
			bit_rw_t<io_, bitpos::B6>   ANSC006;
			bit_rw_t<io_, bitpos::B7>   ANSC007;
			bit_rw_t<io_, bitpos::B8>   ANSC008;
			bit_rw_t<io_, bitpos::B9>   ANSC009;
			bit_rw_t<io_, bitpos::B10>  ANSC010;
			bit_rw_t<io_, bitpos::B11>  ANSC011;
		};
		typedef adansc0_t<base + 0xD4>  ADANSC0_;
		static  ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1 (ADANSC1)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC100;
			bit_rw_t<io_, bitpos::B1>   ANSC101;
		};
		typedef adansc1_t<base + 0xD6>  ADANSC1_;
		static  ADANSC1_ ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADANSA0_::address, ADANSA1_::address>  ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADANSB0_::address, ADANSB1_::address>  ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADANSC0_::address, ADANSC1_::address>  ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 8 (ADSCS8)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C8> ADSCS8_;
		static  ADSCS8_ ADSCS8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 9 (ADSCS9)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C9> ADSCS9_;
		static  ADSCS9_ ADSCS9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 10 (ADSCS10)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1CA> ADSCS10_;
		static  ADSCS10_ ADSCS10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 11 (ADSCS11)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1CB> ADSCS11_;
		static  ADSCS11_ ADSCS11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 12 (ADSCS12)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1D0> ADSCS12_;
		static  ADSCS12_ ADSCS12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 13 (ADSCS13)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1D1> ADSCS13_;
		static  ADSCS13_ ADSCS13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adscs_t<ANALOG, ANALOG::AN217, BASE::ADSCS0_::address> ADSCS_;
		static  ADSCS_ ADSCS;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均機能チャネル選択レジスタ 0 (ADADS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS000;
			bit_rw_t<io_, bitpos::B1>   ADS001;
			bit_rw_t<io_, bitpos::B2>   ADS002;
			bit_rw_t<io_, bitpos::B3>   ADS003;
			bit_rw_t<io_, bitpos::B4>   ADS004;
			bit_rw_t<io_, bitpos::B5>   ADS005;
			bit_rw_t<io_, bitpos::B6>   ADS006;
			bit_rw_t<io_, bitpos::B7>   ADS007;
			bit_rw_t<io_, bitpos::B8>   ADS008;
			bit_rw_t<io_, bitpos::B9>   ADS009;
			bit_rw_t<io_, bitpos::B10>  ADS010;
			bit_rw_t<io_, bitpos::B11>  ADS011;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 1 (ADADS1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS100;
			bit_rw_t<io_, bitpos::B1>   ADS101;
		};
		typedef adads1_t<base + 0x0A>  ADADS1_;
		static  ADADS1_ ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADADS0_::address, ADADS1_::address>  ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換拡張入力コントロールレジスタ (ADEXICR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adexicr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   TSSAD;
			bit_rw_t<io_, bitpos::B1>   OCSAD;

			bit_rw_t<io_, bitpos::B8>   TSSA;
			bit_rw_t<io_, bitpos::B9>   OCSA;
			bit_rw_t<io_, bitpos::B10>  TSSB;
			bit_rw_t<io_, bitpos::B11>  OCSB;
		};
		typedef adexicr_t<base + 0x12>  ADEXICR_;
		static  ADEXICR_ ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D グループ C 拡張入力コントロールレジスタ (ADGCEXCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgcexcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TSSC;
			bit_rw_t<io_, bitpos::B1> OCSC;
		};
		typedef adgcexcr_t<base + 0xD8>  ADGCEXCR_;
		static  ADGCEXCR_ ADGCEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR8)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE8> ADSSTR8_;
		static  ADSSTR8_ ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR9)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE9> ADSSTR9_;
		static  ADSSTR9_ ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR10)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEA> ADSSTR10_;
		static  ADSSTR10_ ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR11)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEB> ADSSTR11_;
		static  ADSSTR11_ ADSSTR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> ADSSTRL_;
		static  ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTRT)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDE> ADSSTRT_;
		static  ADSSTRT_ ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTRO)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDF> ADSSTRO_;
		static  ADSSTRO_ ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1l_tr_t<ANALOG, BASE::ADSSTR0_::address, ADSSTRL_::address,
			ANALOG::TEMP, ADSSTRT_::address, ANALOG::REF, ADSSTRO_::address> ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド回路コントロールレジスタ (ADSHCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SSTSH;
			bits_rw_t<io_, bitpos::B8, 3>  SHANS;
		};
		typedef adshcr_t<base + 0x66>  ADSHCR_;
		static  ADSHCR_ ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ 0 (ADCMPANSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPCHA011;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static  ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネル選択レジスタ 1 (ADCMPANSR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPCHA100;
			bit_rw_t<io_, bitpos::B1> CMPCHA101;
		};
		typedef adcmpansr1_t<base + 0x96>  ADCMPANSR1_;
		static  ADCMPANSR1_ ADCMPANSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ (ADCMPANSR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADCMPANSR0_::address, ADCMPANSR1_::address>  ADCMPANSR_;
		static  ADCMPANSR_ ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 拡張入力選択レジスタ (ADCMPANSER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpanser_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPSTS;
			bit_rw_t<io_, bitpos::B1> CMPSOC;
		};
		typedef adcmpanser_t<base + 0x92>  ADCMPANSER_;
		static  ADCMPANSER_ ADCMPANSER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 0 (ADCMPLR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPLCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPLCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPLCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPLCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPLCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPLCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPLCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPLCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPLCHA011;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static  ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 1 (ADCMPLR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPLCHA100;
			bit_rw_t<io_, bitpos::B1> CMPLCHA101;
		};
		typedef adcmplr1_t<base + 0x9A>  ADCMPLR1_;
		static  ADCMPLR1_ ADCMPLR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ (ADCMPLR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADCMPLR0_::address, ADCMPLR1_::address>  ADCMPLR_;
		static  ADCMPLR_ ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 拡張入力比較条件設定レジスタ (ADCMPLER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpler_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPLTS;
			bit_rw_t<io_, bitpos::B1> CMPLOC;
		};
		typedef adcmpler_t<base + 0x93>  ADCMPLER_;
		static  ADCMPLER_ ADCMPLER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 0 (ADCMPSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPSTCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPSTCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPSTCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPSTCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPSTCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPSTCHA011;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 1 (ADCMPSR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPFTCHA100;
			bit_rw_t<io_, bitpos::B1> CMPFTCHA101;
		};
		typedef adcmpsr1_t<base + 0xA2>  ADCMPSR1_;
		static  ADCMPSR1_ ADCMPSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネルステータスレジスタ (ADCMPSR)
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADCMPSR0_::address, ADCMPSR1_::address>  ADCMPSR_;
		static  ADCMPSR_ ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 拡張入力チャネルステータスレジスタ (ADCMPSER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpser_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPFTS;
			bit_rw_t<io_, bitpos::B1> CMPFOC;
		};
		typedef adcmpser_t<base + 0xA4>  ADCMPSER_;
		static  ADCMPSER_ ADCMPSER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧モニタ回路許可レジスタ (ADVMONCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct advmoncr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> VDE;
		};
		typedef advmoncr_t<base + 0x1E2>  ADVMONCR_;
		static  ADVMONCR_ ADVMONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧モニタ回路出力許可レジスタ (ADVMONO)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct advmono_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> VDO;
		};
		typedef advmono_t<base + 0x1E4>  ADVMONO_;
		static  ADVMONO_ ADVMONO;
	};
	template <uint32_t base> typename s12ad2_t<base>::ADDR8_ s12ad2_t<base>::ADDR8;
	template <uint32_t base> typename s12ad2_t<base>::ADDR9_ s12ad2_t<base>::ADDR9;
	template <uint32_t base> typename s12ad2_t<base>::ADDR10_ s12ad2_t<base>::ADDR10;
	template <uint32_t base> typename s12ad2_t<base>::ADDR11_ s12ad2_t<base>::ADDR11;
	template <uint32_t base> typename s12ad2_t<base>::ADDR16_ s12ad2_t<base>::ADDR16;
	template <uint32_t base> typename s12ad2_t<base>::ADDR17_ s12ad2_t<base>::ADDR17;
	template <uint32_t base> typename s12ad2_t<base>::ADTSDR_ s12ad2_t<base>::ADTSDR;
	template <uint32_t base> typename s12ad2_t<base>::ADOCDR_ s12ad2_t<base>::ADOCDR;
	template <uint32_t base> typename s12ad2_t<base>::ADDR_ s12ad2_t<base>::ADDR;
	template <uint32_t base> typename s12ad2_t<base>::ADANSA1_ s12ad2_t<base>::ADANSA1;
	template <uint32_t base> typename s12ad2_t<base>::ADANSB1_ s12ad2_t<base>::ADANSB1;
	template <uint32_t base> typename s12ad2_t<base>::ADANSC1_ s12ad2_t<base>::ADANSC1;
	template <uint32_t base> typename s12ad2_t<base>::ADANSA_ s12ad2_t<base>::ADANSA;
	template <uint32_t base> typename s12ad2_t<base>::ADANSB_ s12ad2_t<base>::ADANSB;
	template <uint32_t base> typename s12ad2_t<base>::ADANSC_ s12ad2_t<base>::ADANSC;
	template <uint32_t base> typename s12ad2_t<base>::ADSCS8_ s12ad2_t<base>::ADSCS8;
	template <uint32_t base> typename s12ad2_t<base>::ADSCS9_ s12ad2_t<base>::ADSCS9;
	template <uint32_t base> typename s12ad2_t<base>::ADSCS10_ s12ad2_t<base>::ADSCS10;
	template <uint32_t base> typename s12ad2_t<base>::ADSCS11_ s12ad2_t<base>::ADSCS11;
	template <uint32_t base> typename s12ad2_t<base>::ADSCS12_ s12ad2_t<base>::ADSCS12;
	template <uint32_t base> typename s12ad2_t<base>::ADSCS13_ s12ad2_t<base>::ADSCS13;
	template <uint32_t base> typename s12ad2_t<base>::ADSCS_ s12ad2_t<base>::ADSCS;
	template <uint32_t base> typename s12ad2_t<base>::ADADS0_ s12ad2_t<base>::ADADS0;
	template <uint32_t base> typename s12ad2_t<base>::ADADS1_ s12ad2_t<base>::ADADS1;
	template <uint32_t base> typename s12ad2_t<base>::ADADS_ s12ad2_t<base>::ADADS;
	template <uint32_t base> typename s12ad2_t<base>::ADEXICR_ s12ad2_t<base>::ADEXICR;
	template <uint32_t base> typename s12ad2_t<base>::ADGCEXCR_ s12ad2_t<base>::ADGCEXCR;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTR8_ s12ad2_t<base>::ADSSTR8;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTR9_ s12ad2_t<base>::ADSSTR9;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTR10_ s12ad2_t<base>::ADSSTR10;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTR11_ s12ad2_t<base>::ADSSTR11;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTRL_ s12ad2_t<base>::ADSSTRL;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTRT_ s12ad2_t<base>::ADSSTRT;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTRO_ s12ad2_t<base>::ADSSTRO;
	template <uint32_t base> typename s12ad2_t<base>::ADSSTR_ s12ad2_t<base>::ADSSTR;
	template <uint32_t base> typename s12ad2_t<base>::ADSHCR_ s12ad2_t<base>::ADSHCR;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPANSR0_ s12ad2_t<base>::ADCMPANSR0;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPANSR1_ s12ad2_t<base>::ADCMPANSR1;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPANSR_ s12ad2_t<base>::ADCMPANSR;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPANSER_ s12ad2_t<base>::ADCMPANSER;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPLR1_ s12ad2_t<base>::ADCMPLR1;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPLR_ s12ad2_t<base>::ADCMPLR;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPLER_ s12ad2_t<base>::ADCMPLER;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPSR0_ s12ad2_t<base>::ADCMPSR0;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPSR1_ s12ad2_t<base>::ADCMPSR1;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPSR_ s12ad2_t<base>::ADCMPSR;
	template <uint32_t base> typename s12ad2_t<base>::ADCMPSER_ s12ad2_t<base>::ADCMPSER;
	template <uint32_t base> typename s12ad2_t<base>::ADVMONCR_ s12ad2_t<base>::ADVMONCR;
	template <uint32_t base> typename s12ad2_t<base>::ADVMONO_ s12ad2_t<base>::ADVMONO;

	typedef s12ad_t <0x0008'9000>  S12AD;
	typedef s12ad1_t<0x0008'9200>  S12AD1;
	typedef s12ad2_t<0x0008'9400>  S12AD2;
}
