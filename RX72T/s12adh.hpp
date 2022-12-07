#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72T グループ・S12ADH 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADH 共通定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	vec		割り込みベクター
		@param[in]	gbi		GB 割り込みベクター
		@param[in]	gci		GC 割り込みベクター
		@param[in]	cmpai	CMPA 割り込みベクター
		@param[in]	cmpbi	CMPB 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
	struct s12adh_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto VEC   	 = vec;		///< 割り込みベクター
		static constexpr auto GB_VEC	 = gbi;		///< GB 割り込みベクター
		static constexpr auto GC_VEC	 = gci;		///< GC 割り込みベクター
		static constexpr auto CMPA_VEC	 = cmpai;	///< CMPA 割り込みベクター
		static constexpr auto CMPB_VEC	 = cmpbi;	///< CMPB 割り込みベクター

		static constexpr uint32_t UNIT_NUM = 3;		///< 変換ユニット数
		static constexpr auto BASE_CLOCK = clock_profile::PCLKB;	///< A/D 変換クロック
		static constexpr uint32_t IN_CONV_TIME_NS = 900;	///< A/D 入力 0.9uS、単位「ns」
		static constexpr uint32_t TO_CONV_TIME_NS = 4000;	///< 温度、基準電圧 4uS、単位「ns」


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

			bits_rw_t<io_, bitpos::B1, 2>  ADPRC;
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
			@brief	A/D グループ C トリガ選択レジスタ（ ADGCTRGR ）
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
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA001;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA002;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA003;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA004;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA005;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA006;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA007;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA008;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA009;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA010;
			bit_rw_t<io_, bitpos::B0>   CMPSTCHA011;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;


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
	};
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR1_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR2_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR2;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR3_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR3;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR4_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR4;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR5_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR5;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR6_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR6;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR7_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR7;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDBLDR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDBLDR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDBLDRA_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDBLDRA;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDBLDRB_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDBLDRB;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADRD_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADRD;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCSR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCSR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADANSA0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADANSB0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADANSC0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS1_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS2_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS2;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS3_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS3;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS4_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS4;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS5_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS5;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS6_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS6;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS7_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS7;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADADS0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADADS0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADADC_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADADC;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCER_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCER;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSTRGR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSTRGR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADGCTRGR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADGCTRGR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR1_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR2_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR2;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR3_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR3;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR4_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR4;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR5_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR5;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR6_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR6;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR7_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR7;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDISCR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDISCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADELCCR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADELCCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADGSPCR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADGSPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPCR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPDR0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPDR1_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPDR1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPANSR0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPANSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPLR0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPLR0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPSR0_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADWINMON_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADWINMON;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPBNSR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPBNSR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPBSR_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPBSR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADWINLLB_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADWINLLB;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12adh_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADWINULB_ s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADWINULB;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	vec		割り込みベクター
		@param[in]	gbi		GB 割り込みベクター
		@param[in]	gci		GC 割り込みベクター
		@param[in]	cmpai	CMPA 割り込みベクター
		@param[in]	cmpbi	CMPB 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
	struct s12ad_t : public s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi> {

		static constexpr uint32_t UNIT_NO = 0;		///< 変換ユニット番号
		static constexpr uint32_t ANALOG_NUM = 8;	///< アナログ入力数

		typedef s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi> base_class;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AIN000,
			AIN001,
			AIN002,
			AIN003,
			AIN004,
			AIN005,
			AIN006,
			AIN007,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AIN000:
				PORT4::PDR.B0 = 0;
				MPC::P40PFS.ASEL = f;
				break;
			case ANALOG::AIN001:
				PORT4::PDR.B1 = 0;
				MPC::P41PFS.ASEL = f;
				break;
			case ANALOG::AIN002:
				PORT4::PDR.B2 = 0;
				MPC::P42PFS.ASEL = f;
				break;
			case ANALOG::AIN003:
				PORT4::PDR.B3 = 0;
				MPC::P43PFS.ASEL = f;
				break;
			case ANALOG::AIN004:
				PORTH::PDR.B1 = 0;
				MPC::PH1PFS.ASEL = f;
				break;
			case ANALOG::AIN005:
				PORTH::PDR.B2 = 0;
				MPC::PH2PFS.ASEL = f;
				break;
			case ANALOG::AIN006:
				PORTH::PDR.B3 = 0;
				MPC::PH3PFS.ASEL = f;
				break;
			case ANALOG::AIN007:
				PORTH::PDR.B0 = 0;
				MPC::PH0PFS.ASEL = f;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み (ADDR) unit0
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator() (ANALOG an) {
				return rd16_(base_class::ADDR0.address + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS) unit0
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {

			void set(ANALOG an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t a = ofs;
				if(f) {
					wr16_(a, rd16_(a) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(a, rd16_(a) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			bool operator() (ANALOG an) const {
				uint32_t n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x04>   ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x14>   ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0xD4> ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(ANALOG an, uint8_t v) {
				wr8_(base_class::ADSSTR0.address + static_cast<uint32_t>(an), v);
			}
		};
		typedef adsstr_t ADSSTR_;
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

			bits_rw_t<io_, bitpos::B0, 4>  Px00CR;
			bits_rw_t<io_, bitpos::B4, 4>  Px01CR;
			bits_rw_t<io_, bitpos::B8, 4>  Px02CR;
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

			bits_rw_t<io_, bitpos::B0, 4>  Px00GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  Px01GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  Px02GAIN;
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
			bits_rw_t<io_, bitpos::B0, 2>  Px00DG;

			bit_rw_t <io_, bitpos::B3>     P000DEN;
			bit_rw_t <io_, bitpos::B3>     Px00DEN;
			bits_rw_t<io_, bitpos::B4, 2>  P001DG;
			bits_rw_t<io_, bitpos::B4, 2>  Px01DG;

			bit_rw_t <io_, bitpos::B7>     P001DEN;
			bit_rw_t <io_, bitpos::B7>     Px01DEN;
			bits_rw_t<io_, bitpos::B8, 2>  P002DG;
			bits_rw_t<io_, bitpos::B8, 2>  Px02DG;

			bit_rw_t <io_, bitpos::B11>    P002DEN;
			bit_rw_t <io_, bitpos::B11>    Px02DEN;
		};
		typedef adpgadcr0_t<base + 0x1B0>  ADPGADCR0_;
		static  ADPGADCR0_ ADPGADCR0;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHCR_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHMSR_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHMSR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGACR_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGACR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGAGS0_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGAGS0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGADCR0_ s12ad_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGADCR0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	vec		割り込みベクター
		@param[in]	gbi		GB 割り込みベクター
		@param[in]	gci		GC 割り込みベクター
		@param[in]	cmpai	CMPA 割り込みベクター
		@param[in]	cmpbi	CMPB 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
	struct s12ad1_t : public s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi> {

		static constexpr uint32_t UNIT_NO = 1;		///< 変換ユニット番号

		typedef s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi> base_class;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AIN100,
			AIN101,
			AIN102,
			AIN103,
			AIN104,
			AIN105,
			AIN106,
			AIN107,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	アナログ入力数
		*/
		//-----------------------------------------------------------------//		
		static constexpr uint32_t analog_num = 8;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AIN100:
				PORT4::PDR.B4 = 0;
				MPC::P44PFS.ASEL = f;
				break;
			case ANALOG::AIN101:
				PORT4::PDR.B5 = 0;
				MPC::P45PFS.ASEL = f;
				break;
			case ANALOG::AIN102:
				PORT4::PDR.B6 = 0;
				MPC::P46PFS.ASEL = f;
				break;
			case ANALOG::AIN103:
				PORT4::PDR.B7 = 0;
				MPC::P47PFS.ASEL = f;
				break;
			case ANALOG::AIN104:
				PORTH::PDR.B5 = 0;
				MPC::PH5PFS.ASEL = f;
				break;
			case ANALOG::AIN105:
				PORTH::PDR.B6 = 0;
				MPC::PH6PFS.ASEL = f;
				break;
			case ANALOG::AIN106:
				PORTH::PDR.B7 = 0;
				MPC::PH7PFS.ASEL = f;
				break;
			case ANALOG::AIN107:
				PORTH::PDR.B4 = 0;
				MPC::PH4PFS.ASEL = f;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator() (ANALOG an) {
				return ro16_(base_class::ADDR0.address + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS) unit1
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {

			void set(ANALOG an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t a = ofs;
				if(f) {
					wr16_(a, rd16_(a) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(a, rd16_(a) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			bool operator() (ANALOG an) const {
				uint32_t n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x04>   ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x14>   ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0xD4> ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(ANALOG an, uint8_t v) {
				wr8_(base_class::ADSSTR0.address + static_cast<uint32_t>(an), v);
			}
		};
		typedef adsstr_t ADSSTR_;
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

			bits_rw_t<io_, bitpos::B0, 4>  Px00CR;
			bits_rw_t<io_, bitpos::B4, 4>  Px01CR;
			bits_rw_t<io_, bitpos::B8, 4>  Px02CR;
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

			bits_rw_t<io_, bitpos::B0, 4>  Px00GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  Px01GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  Px02GAIN;
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
			bits_rw_t<io_, bitpos::B0, 2>  Px00DG;

			bit_rw_t <io_, bitpos::B3>     P100DEN;
			bit_rw_t <io_, bitpos::B3>     Px00DEN;
			bits_rw_t<io_, bitpos::B4, 2>  P101DG;
			bits_rw_t<io_, bitpos::B4, 2>  Px01DG;

			bit_rw_t <io_, bitpos::B7>     P101DEN;
			bit_rw_t <io_, bitpos::B7>     Px01DEN;
			bits_rw_t<io_, bitpos::B8, 2>  P102DG;
			bits_rw_t<io_, bitpos::B8, 2>  Px02DG;

			bit_rw_t <io_, bitpos::B11>    P102DEN;
			bit_rw_t <io_, bitpos::B11>    Px02DEN;
		};
		typedef adpgadcr0_t<base + 0x1B0>  ADPGADCR0_;
		static  ADPGADCR0_ ADPGADCR0;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHCR_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHMSR_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSHMSR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGACR_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGACR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGAGS0_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGAGS0;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGADCR0_ s12ad1_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADPGADCR0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD2 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	vec		割り込みベクター
		@param[in]	gbi		GB 割り込みベクター
		@param[in]	gci		GC 割り込みベクター
		@param[in]	cmpai	CMPA 割り込みベクター
		@param[in]	cmpbi	CMPB 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
	struct s12ad2_t : public s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi> {

		static constexpr uint32_t UNIT_NO = 2;		///< 変換ユニット番号

		typedef s12adh_t<base, per, vec, gbi, gci, cmpai, cmpbi> base_class;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AIN200,
			AIN201,
			AIN202,
			AIN203,
			AIN204,
			AIN205,
			AIN206,
			AIN207,
			AIN208,
			AIN209,
			AIN210,
			AIN211,

			AIN216 = 16,
			AIN217,

			AINT,		///< 温度センサ
			AINO,		///< 内部基準電圧
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	アナログ入力数
		*/
		//-----------------------------------------------------------------//		
		static constexpr uint32_t analog_num = 12;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true) {
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AIN200:
				PORT5::PDR.B2 = 0;
				MPC::P52PFS.ASEL = f;
				break;
			case ANALOG::AIN201:
				PORT5::PDR.B3 = 0;
				MPC::P53PFS.ASEL = f;
				break;
			case ANALOG::AIN202:
				PORT5::PDR.B4 = 0;
				MPC::P54PFS.ASEL = f;
				break;
			case ANALOG::AIN203:
				PORT5::PDR.B5 = 0;
				MPC::P55PFS.ASEL = f;
				break;
			case ANALOG::AIN204:
				PORT5::PDR.B0 = 0;
				MPC::P50PFS.ASEL = f;
				break;
			case ANALOG::AIN205:
				PORT5::PDR.B1 = 0;
				MPC::P51PFS.ASEL = f;
				break;
			case ANALOG::AIN206:
				PORT6::PDR.B0 = 0;
				MPC::P60PFS.ASEL = f;
				break;
			case ANALOG::AIN207:
				PORT6::PDR.B1 = 0;
				MPC::P61PFS.ASEL = f;
				break;
			case ANALOG::AIN208:
				PORT6::PDR.B2 = 0;
				MPC::P62PFS.ASEL = f;
				break;
			case ANALOG::AIN209:
				PORT6::PDR.B3 = 0;
				MPC::P63PFS.ASEL = f;
				break;
			case ANALOG::AIN210:
				PORT6::PDR.B4 = 0;
				MPC::P64PFS.ASEL = f;
				break;
			case ANALOG::AIN211:
				PORT6::PDR.B5 = 0;
				MPC::P65PFS.ASEL = f;
				break;

			case ANALOG::AIN216:
				PORT2::PDR.B0 = 0;
				MPC::P20PFS.ASEL = f;
				break;
			case ANALOG::AIN217:
				PORT2::PDR.B1 = 0;
				MPC::P21PFS.ASEL = f;
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
			@brief  A/D データレジスタ読み込み
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator() (ANALOG an) {
				if(an <= ANALOG::AIN217) {
					return ro16_(base_class::ADDR0.address + static_cast<uint32_t>(an) * 2);
				} else if(an == ANALOG::AINT) {
					return ADTSDR();
				} else if(an == ANALOG::AINO) {
					return ADOCDR();
				} else {
					return 0x0000;
				}
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {

			void set(ANALOG an, bool f = true) {
				if(an == ANALOG::AINT || an == ANALOG::AINO) return;
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t a = ofs;
				if(n >= 16) {
					n &= 15;
					a += 2;
				}
				if(f) {
					wr16_(a, rd16_(a) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(a, rd16_(a) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			bool operator() (ANALOG an) const {
				if(an == ANALOG::AINT || an == ANALOG::AINO) return 0;
				uint32_t n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x04>   ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x14>   ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0xD4> ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS8)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C8> ADSCS8_;
		static  ADSCS8_ ADSCS8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS9)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C9> ADSCS9_;
		static  ADSCS9_ ADSCS9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS10)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1CA> ADSCS10_;
		static  ADSCS10_ ADSCS10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS11)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1CB> ADSCS11_;
		static  ADSCS11_ ADSCS11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS12)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1D0> ADSCS12_;
		static  ADSCS12_ ADSCS12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS13)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1D1> ADSCS13_;
		static  ADSCS13_ ADSCS13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ
		*/
		//-----------------------------------------------------------------//
		struct adscs_t {
			void set(ANALOG an, uint8_t v) {
				if(an == ANALOG::AINT || an == ANALOG::AINO) return;
				wr8_(base_class::ADSCS0.address + static_cast<uint32_t>(an), v);
			}

			uint8_t get(ANALOG an) {
				if(an == ANALOG::AINT || an == ANALOG::AINO) return 0x00;
				return rd8_(base_class::ADSCS0.address + static_cast<uint32_t>(an));
			}

			uint8_t operator () (ANALOG an) {
				return get(an);
			}
		};
		typedef adscs_t ADSCS_;
		static  ADSCS_ ADSCS;


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
		struct adsstr_t {
			void set(ANALOG an, uint8_t v) {
				if(an == ANALOG::AIN216 || an == ANALOG::AIN217) {
					ADSSTRL = v;
				} else if(an == ANALOG::AINT) {
					ADSSTRT = v;
				} else if(an == ANALOG::AINO) {
					ADSSTRO = v;
				} else {
					wr8_(base_class::ADSSTR0.address + static_cast<uint32_t>(an), v);
				}
			}
		};
		typedef adsstr_t ADSSTR_;
		static  ADSSTR_ ADSSTR;


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
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR8_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR8;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR9_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR9;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR10_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR10;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR11_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR11;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR16_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR16;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR17_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR17;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADTSDR_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADTSDR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADOCDR_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADOCDR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADDR_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADANSA1_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADANSB1_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADANSC1_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADANSC;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS8_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS8;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS9_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS9;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS10_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS10;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS11_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS11;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS12_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS12;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSCS13_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSCS13;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADADS1_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADADS1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADEXICR_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADEXICR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADGCEXCR_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADGCEXCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR8_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR8;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR9_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR9;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR10_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR10;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR11_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR11;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTRL_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTRT_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTRT;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTRO_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTRO;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPANSR1_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPANSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPANSER_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPANSER;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPLR1_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPLR1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPLER_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPLER;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPSR1_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADCMPSER_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADCMPSER;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADVMONCR_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADVMONCR;
	template <uint32_t base, peripheral per, ICU::VECTOR vec, ICU::VECTOR gbi, ICU::VECTOR gci, ICU::GROUPBL1 cmpai, ICU::GROUPBL1 cmpbi>
		typename s12ad2_t<base,per, vec, gbi, gci, cmpai, cmpbi>::ADVMONO_ s12ad2_t<base, per, vec, gbi, gci, cmpai, cmpbi>::ADVMONO;


	typedef s12ad_t<0x00089000, peripheral::S12AD,
		ICU::VECTOR::S12ADI,  ICU::VECTOR::S12GBADI,  ICU::VECTOR::S12GCADI,  ICU::GROUPBL1::S12CMPAI,  ICU::GROUPBL1::S12CMPBI>  S12AD;
	typedef s12ad1_t<0x00089200, peripheral::S12AD1,
		ICU::VECTOR::S12ADI1, ICU::VECTOR::S12GBADI1, ICU::VECTOR::S12GCADI1, ICU::GROUPBL1::S12CMPAI1, ICU::GROUPBL1::S12CMPBI1> S12AD1;
	typedef s12ad2_t<0x00089400, peripheral::S12AD2,
		ICU::VECTOR::S12ADI2, ICU::VECTOR::S12GBADI2, ICU::VECTOR::S12GCADI2, ICU::GROUPBL1::S12CMPAI2, ICU::GROUPBL1::S12CMPBI2> S12AD2;
}
