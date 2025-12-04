#pragma once
//=========================================================================//
/*!	@file
	@brief	12-Bit A/D Converter / 12 ビット A/D コンバータ (RX660)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADH base class
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
		static inline ADDR0_ ADDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 1（ADDR1）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x22> ADDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 2（ADDR2）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x24> ADDR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 3（ADDR3）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x26> ADDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 4（ADDR4）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x28> ADDR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 5（ADDR5）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x2A> ADDR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 6（ADDR6）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x2C> ADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 7（ADDR7）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x2E> ADDR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 8（ADDR8）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x30> ADDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 9（ADDR9）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x32> ADDR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 10（ADDR10）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x34> ADDR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 11（ADDR11）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x36> ADDR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 12（ADDR12）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x38> ADDR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 13（ADDR13）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x3A> ADDR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 14（ADDR14）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x3C> ADDR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 15（ADDR15）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x3E> ADDR15;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> ADDR16_;
		static inline ADDR16_ ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 17（ADDR17）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x42> ADDR17;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 18（ADDR18）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x44> ADDR18;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 19（ADDR19）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x46> ADDR19;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 20（ADDR20）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x48> ADDR20;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 21（ADDR21）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x4A> ADDR21;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 22（ADDR22）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x4C> ADDR22;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 23（ADDR23）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x4E> ADDR23;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x18> ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ二重化レジスタ A (ADDBLDRA)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x84> ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ二重化レジスタ B (ADDBLDRB)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x86> ADDBLDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ (ADTSDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1A> ADTSDR_;
		static inline ADTSDR_ ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ (ADOCDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1C> ADOCDR_;
		static inline ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ (ADRD)
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x1E> ADRD;


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
			bit_rw_t <io_, bitpos::B10>    ADHSC;

			bit_rw_t <io_, bitpos::B12>    ADIE;
			bits_rw_t<io_, bitpos::B13, 2> ADCS;
			bit_rw_t <io_, bitpos::B15>    ADST;
		};
		static inline adcsr_t<base + 0x00>  ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ A0 (ADANSA0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ANSA000;
			bit_rw_t <io_, bitpos::B1>     ANSA001;
			bit_rw_t <io_, bitpos::B2>     ANSA002;
			bit_rw_t <io_, bitpos::B3>     ANSA003;
			bit_rw_t <io_, bitpos::B4>     ANSA004;
			bit_rw_t <io_, bitpos::B5>     ANSA005;
			bit_rw_t <io_, bitpos::B6>     ANSA006;
			bit_rw_t <io_, bitpos::B7>     ANSA007;
			bit_rw_t <io_, bitpos::B8>     ANSA008;
			bit_rw_t <io_, bitpos::B9>     ANSA009;
			bit_rw_t <io_, bitpos::B10>    ANSA010;
			bit_rw_t <io_, bitpos::B11>    ANSA011;
			bit_rw_t <io_, bitpos::B12>    ANSA012;
			bit_rw_t <io_, bitpos::B13>    ANSA013;
			bit_rw_t <io_, bitpos::B14>    ANSA014;
			bit_rw_t <io_, bitpos::B15>    ANSA015;
		};
		typedef adansa0_t<base + 0x04> ADANSA0_;
		static inline ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ A1 (ADANSA1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ANSA100;
			bit_rw_t <io_, bitpos::B1>     ANSA101;
			bit_rw_t <io_, bitpos::B2>     ANSA102;
			bit_rw_t <io_, bitpos::B3>     ANSA103;
			bit_rw_t <io_, bitpos::B4>     ANSA104;
			bit_rw_t <io_, bitpos::B5>     ANSA105;
			bit_rw_t <io_, bitpos::B6>     ANSA106;
			bit_rw_t <io_, bitpos::B7>     ANSA107;
		};
		typedef adansa1_t<base + 0x06> ADANSA1_;
		static inline ADANSA1_ ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ B0 (ADANSB0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ANSB000;
			bit_rw_t <io_, bitpos::B1>     ANSB001;
			bit_rw_t <io_, bitpos::B2>     ANSB002;
			bit_rw_t <io_, bitpos::B3>     ANSB003;
			bit_rw_t <io_, bitpos::B4>     ANSB004;
			bit_rw_t <io_, bitpos::B5>     ANSB005;
			bit_rw_t <io_, bitpos::B6>     ANSB006;
			bit_rw_t <io_, bitpos::B7>     ANSB007;
			bit_rw_t <io_, bitpos::B8>     ANSB008;
			bit_rw_t <io_, bitpos::B9>     ANSB009;
			bit_rw_t <io_, bitpos::B10>    ANSB010;
			bit_rw_t <io_, bitpos::B11>    ANSB011;
			bit_rw_t <io_, bitpos::B12>    ANSB012;
			bit_rw_t <io_, bitpos::B13>    ANSB013;
			bit_rw_t <io_, bitpos::B14>    ANSB014;
			bit_rw_t <io_, bitpos::B15>    ANSB015;
		};
		typedef adansb0_t<base + 0x14> ADANSB0_;
		static inline ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ B1 (ADANSB1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ANSB100;
			bit_rw_t <io_, bitpos::B1>     ANSB101;
			bit_rw_t <io_, bitpos::B2>     ANSB102;
			bit_rw_t <io_, bitpos::B3>     ANSB103;
			bit_rw_t <io_, bitpos::B4>     ANSB104;
			bit_rw_t <io_, bitpos::B5>     ANSB105;
			bit_rw_t <io_, bitpos::B6>     ANSB106;
			bit_rw_t <io_, bitpos::B7>     ANSB107;
		};
		typedef adansb1_t<base + 0x16> ADANSB1_;
		static inline ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ C0 (ADANSC0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ANSC000;
			bit_rw_t <io_, bitpos::B1>     ANSC001;
			bit_rw_t <io_, bitpos::B2>     ANSC002;
			bit_rw_t <io_, bitpos::B3>     ANSC003;
			bit_rw_t <io_, bitpos::B4>     ANSC004;
			bit_rw_t <io_, bitpos::B5>     ANSC005;
			bit_rw_t <io_, bitpos::B6>     ANSC006;
			bit_rw_t <io_, bitpos::B7>     ANSC007;
			bit_rw_t <io_, bitpos::B8>     ANSC008;
			bit_rw_t <io_, bitpos::B9>     ANSC009;
			bit_rw_t <io_, bitpos::B10>    ANSC010;
			bit_rw_t <io_, bitpos::B11>    ANSC011;
			bit_rw_t <io_, bitpos::B12>    ANSC012;
			bit_rw_t <io_, bitpos::B13>    ANSC013;
			bit_rw_t <io_, bitpos::B14>    ANSC014;
			bit_rw_t <io_, bitpos::B15>    ANSC015;
		};
		typedef adansc0_t<base + 0xD4> ADANSC0_;
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ C1 (ADANSC1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ANSC100;
			bit_rw_t <io_, bitpos::B1>     ANSC101;
			bit_rw_t <io_, bitpos::B2>     ANSC102;
			bit_rw_t <io_, bitpos::B3>     ANSC103;
			bit_rw_t <io_, bitpos::B4>     ANSC104;
			bit_rw_t <io_, bitpos::B5>     ANSC105;
			bit_rw_t <io_, bitpos::B6>     ANSC106;
			bit_rw_t <io_, bitpos::B7>     ANSC107;
		};
		typedef adansc1_t<base + 0xD6> ADANSC1_;
		static inline ADANSC1_ ADANSC1;


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

			bit_rw_t <io_, bitpos::B0>     ADS000;
			bit_rw_t <io_, bitpos::B1>     ADS001;
			bit_rw_t <io_, bitpos::B2>     ADS002;
			bit_rw_t <io_, bitpos::B3>     ADS003;
			bit_rw_t <io_, bitpos::B4>     ADS004;
			bit_rw_t <io_, bitpos::B5>     ADS005;
			bit_rw_t <io_, bitpos::B6>     ADS006;
			bit_rw_t <io_, bitpos::B7>     ADS007;
			bit_rw_t <io_, bitpos::B8>     ADS008;
			bit_rw_t <io_, bitpos::B9>     ADS009;
			bit_rw_t <io_, bitpos::B10>    ADS010;
			bit_rw_t <io_, bitpos::B11>    ADS011;
			bit_rw_t <io_, bitpos::B12>    ADS012;
			bit_rw_t <io_, bitpos::B13>    ADS013;
			bit_rw_t <io_, bitpos::B14>    ADS014;
			bit_rw_t <io_, bitpos::B15>    ADS015;
		};
		typedef adads0_t<base + 0x08> ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均機能チャネル選択レジスタ 1 (ADADS1)
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

			bit_rw_t <io_, bitpos::B0>     ADS100;
			bit_rw_t <io_, bitpos::B1>     ADS101;
			bit_rw_t <io_, bitpos::B2>     ADS102;
			bit_rw_t <io_, bitpos::B3>     ADS103;
			bit_rw_t <io_, bitpos::B4>     ADS104;
			bit_rw_t <io_, bitpos::B5>     ADS105;
			bit_rw_t <io_, bitpos::B6>     ADS106;
			bit_rw_t <io_, bitpos::B7>     ADS107;
		};
		typedef adads1_t<base + 0x0A> ADADS1_;
		static inline ADADS1_ ADADS1;


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
		static inline adadc_t<base + 0x0C>  ADADC;


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

			bits_rw_t<io_, bitpos::B8, 2>  DIAGAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;

			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		static inline adcer_t<base + 0x0E>  ADCER;


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
		static inline adstrgr_t<base + 0x10>  ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換拡張入力コントロールレジスタ（ADEXICR）
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

			bit_rw_t<io_, bitpos::B0>      TSSAD;
			bit_rw_t<io_, bitpos::B1>      OCSAD;

			bit_rw_t<io_, bitpos::B8>      TSSA;
			bit_rw_t<io_, bitpos::B9>      OCSA;
			bit_rw_t<io_, bitpos::B10>     TSSB;
			bit_rw_t<io_, bitpos::B11>     OCSB;
		};
		static inline adexicr_t<base + 0x12>  ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C 拡張入力コントロールレジスタ (ADGCEXCR)
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

			bit_rw_t<io_, bitpos::B0>      TSSC;
			bit_rw_t<io_, bitpos::B1>      OCSC;
		};
		static inline adgcexcr_t<base + 0xD8>  ADGCEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C トリガ選択レジスタ (ADGCTRGR)
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
		static inline adgctrgr_t<base + 0xD9>  ADGCTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0>  ADSSTR0_;
		static inline ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE1>  ADSSTR1_;
		static inline ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE2>  ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE3>  ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE4>  ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE5>  ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE6>  ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE7>  ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 8（ADSSTR8）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE8>  ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 9（ADSSTR9）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE9>  ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 10（ADSSTR10）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEA>  ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 11（ADSSTR11）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEB>  ADSSTR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 12（ADSSTR12）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEC>  ADSSTR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 13（ADSSTR13）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xED>  ADSSTR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 14（ADSSTR14）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEE>  ADSSTR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 15（ADSSTR15）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEF>  ADSSTR15;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL） @n
					AN016 ～AN031
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD>  ADSSTRL_;
		static inline ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ T（ADSSTRT） @n
					温度センサ出力（TEMP）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDE>  ADSSTRT_;
		static inline ADSSTRT_ ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO） @n
					内部基準電圧（VREF）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDF>  ADSSTRO_;
		static inline ADSSTRO_ ADSSTRO;


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
		static inline addiscr_t<base + 0x7A>  ADDISCR;


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
		static inline adelccr_t<base + 0x7D>  ADELCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループスキャン優先コントロールレジスタ (ADGSPCR)
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

			bit_rw_t <io_, bitpos::B0>     PGS;
			bit_rw_t <io_, bitpos::B1>     GBRSCN;

			bit_rw_t <io_, bitpos::B14>    LGRRS;
			bit_rw_t <io_, bitpos::B15>    GBRP;
		};
		static inline adgspcr_t<base + 0x80>  ADGSPCR;


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
			bit_rw_t <io_, bitpos::B14>    WCMPE;
			bit_rw_t <io_, bitpos::B15>    CMPAIE;
		};
		static inline adcmpcr_t<base + 0x90>  ADCMPCR;


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

			bit_rw_t <io_, bitpos::B0>     CMPCHA000;
			bit_rw_t <io_, bitpos::B1>     CMPCHA001;
			bit_rw_t <io_, bitpos::B2>     CMPCHA002;
			bit_rw_t <io_, bitpos::B3>     CMPCHA003;
			bit_rw_t <io_, bitpos::B4>     CMPCHA004;
			bit_rw_t <io_, bitpos::B5>     CMPCHA005;
			bit_rw_t <io_, bitpos::B6>     CMPCHA006;
			bit_rw_t <io_, bitpos::B7>     CMPCHA007;
			bit_rw_t <io_, bitpos::B8>     CMPCHA008;
			bit_rw_t <io_, bitpos::B9>     CMPCHA009;
			bit_rw_t <io_, bitpos::B10>    CMPCHA010;
			bit_rw_t <io_, bitpos::B11>    CMPCHA011;
			bit_rw_t <io_, bitpos::B12>    CMPCHA012;
			bit_rw_t <io_, bitpos::B13>    CMPCHA013;
			bit_rw_t <io_, bitpos::B14>    CMPCHA014;
			bit_rw_t <io_, bitpos::B15>    CMPCHA015;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static inline ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ 1 (ADCMPANSR1)
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

			bit_rw_t <io_, bitpos::B0>     CMPCHA100;
			bit_rw_t <io_, bitpos::B1>     CMPCHA101;
			bit_rw_t <io_, bitpos::B2>     CMPCHA102;
			bit_rw_t <io_, bitpos::B3>     CMPCHA103;
			bit_rw_t <io_, bitpos::B4>     CMPCHA104;
			bit_rw_t <io_, bitpos::B5>     CMPCHA105;
			bit_rw_t <io_, bitpos::B6>     CMPCHA106;
			bit_rw_t <io_, bitpos::B7>     CMPCHA107;
		};
		typedef adcmpansr1_t<base + 0x96>  ADCMPANSR1_;
		static inline ADCMPANSR1_ ADCMPANSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 拡張入力選択レジスタ (ADCMPANSER)
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

			bit_rw_t <io_, bitpos::B0>     CMPSTS;
			bit_rw_t <io_, bitpos::B1>     CMPSOC;
		};
		static inline adcmpanser_t<base + 0x92>  ADCMPANSER;


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

			bit_rw_t <io_, bitpos::B0>     CMPLCHA000;
			bit_rw_t <io_, bitpos::B1>     CMPLCHA001;
			bit_rw_t <io_, bitpos::B2>     CMPLCHA002;
			bit_rw_t <io_, bitpos::B3>     CMPLCHA003;
			bit_rw_t <io_, bitpos::B4>     CMPLCHA004;
			bit_rw_t <io_, bitpos::B5>     CMPLCHA005;
			bit_rw_t <io_, bitpos::B6>     CMPLCHA006;
			bit_rw_t <io_, bitpos::B7>     CMPLCHA007;
			bit_rw_t <io_, bitpos::B8>     CMPLCHA008;
			bit_rw_t <io_, bitpos::B9>     CMPLCHA009;
			bit_rw_t <io_, bitpos::B10>    CMPLCHA010;
			bit_rw_t <io_, bitpos::B11>    CMPLCHA011;
			bit_rw_t <io_, bitpos::B12>    CMPLCHA012;
			bit_rw_t <io_, bitpos::B13>    CMPLCHA013;
			bit_rw_t <io_, bitpos::B14>    CMPLCHA014;
			bit_rw_t <io_, bitpos::B15>    CMPLCHA015;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static inline ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 1 (ADCMPLR1)
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

			bit_rw_t <io_, bitpos::B0>     CMPLCHA100;
			bit_rw_t <io_, bitpos::B1>     CMPLCHA101;
			bit_rw_t <io_, bitpos::B2>     CMPLCHA102;
			bit_rw_t <io_, bitpos::B3>     CMPLCHA103;
			bit_rw_t <io_, bitpos::B4>     CMPLCHA104;
			bit_rw_t <io_, bitpos::B5>     CMPLCHA105;
			bit_rw_t <io_, bitpos::B6>     CMPLCHA106;
			bit_rw_t <io_, bitpos::B7>     CMPLCHA107;
		};
		typedef adcmplr1_t<base + 0x9A>  ADCMPLR1_;
		static inline ADCMPLR1_ ADCMPLR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 拡張入力比較条件設定レジスタ (ADCMPLER)
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

			bit_rw_t <io_, bitpos::B0>     CMPLTS;
			bit_rw_t <io_, bitpos::B1>     CMPLOC;
		};
		static inline adcmpler_t<base + 0x93>  ADCMPLER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 下位側レベル設定レジスタ (ADCMPDR0)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x9C> ADCMPDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 上位側レベル設定レジスタ (ADCMPDR1)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x9E> ADCMPDR1;


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

			bit_rw_t <io_, bitpos::B0>     CMPSTCHA000;
			bit_rw_t <io_, bitpos::B1>     CMPSTCHA001;
			bit_rw_t <io_, bitpos::B2>     CMPSTCHA002;
			bit_rw_t <io_, bitpos::B3>     CMPSTCHA003;
			bit_rw_t <io_, bitpos::B4>     CMPSTCHA004;
			bit_rw_t <io_, bitpos::B5>     CMPSTCHA005;
			bit_rw_t <io_, bitpos::B6>     CMPSTCHA006;
			bit_rw_t <io_, bitpos::B7>     CMPSTCHA007;
			bit_rw_t <io_, bitpos::B8>     CMPSTCHA008;
			bit_rw_t <io_, bitpos::B9>     CMPSTCHA009;
			bit_rw_t <io_, bitpos::B10>    CMPSTCHA010;
			bit_rw_t <io_, bitpos::B11>    CMPSTCHA011;
			bit_rw_t <io_, bitpos::B12>    CMPSTCHA012;
			bit_rw_t <io_, bitpos::B13>    CMPSTCHA013;
			bit_rw_t <io_, bitpos::B14>    CMPSTCHA014;
			bit_rw_t <io_, bitpos::B15>    CMPSTCHA015;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static inline ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 1 (ADCMPSR1)
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

			bit_rw_t <io_, bitpos::B0>     CMPSTCHA100;
			bit_rw_t <io_, bitpos::B1>     CMPSTCHA101;
			bit_rw_t <io_, bitpos::B2>     CMPSTCHA102;
			bit_rw_t <io_, bitpos::B3>     CMPSTCHA103;
			bit_rw_t <io_, bitpos::B4>     CMPSTCHA104;
			bit_rw_t <io_, bitpos::B5>     CMPSTCHA105;
			bit_rw_t <io_, bitpos::B6>     CMPSTCHA106;
			bit_rw_t <io_, bitpos::B7>     CMPSTCHA107;
		};
		typedef adcmpsr1_t<base + 0xA2>  ADCMPSR1_;
		static inline ADCMPSR1_ ADCMPSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 拡張入力チャネルステータスレジスタ (ADCMPSER)
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

			bit_rw_t <io_, bitpos::B0>     CMPFTS;
			bit_rw_t <io_, bitpos::B1>     CMPFOC;
		};
		static inline adcmpser_t<base + 0xA4>  ADCMPSER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A/B ステータスモニタレジスタ (ADWINMON)
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

			bit_rw_t <io_, bitpos::B0>     MONCOMB;

			bit_rw_t <io_, bitpos::B4>     MONCMPA;
			bit_rw_t <io_, bitpos::B5>     MONCMPB;
		};
		static inline adwinmon_t<base + 0x8C>  ADWINMON;


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

			bits_rw_t<io_, bitpos::B0, 6>  CMPCHB;

			bit_rw_t <io_, bitpos::B7>     CMPLB;
		};
		static inline adcmpbnsr_t<base + 0xA6>  ADCMPBNSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 下位側レベル設定レジスタ (ADWINLLB)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xA8> ADWINLLB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 上位側レベル設定レジスタ (ADWINULB)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xAA> ADWINULB;


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

			bit_rw_t <io_, bitpos::B0>     CMPSTB;
		};
		static inline adcmpbsr_t<base + 0xAC>  ADCMPBSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 内部基準電圧モニタ回路許可レジスタ (ADVMONCR)
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

			bit_rw_t <io_, bitpos::B0>     VDE;
		};
		static inline advmoncr_t<base + 0x1E2> ADVMONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 内部基準電圧モニタ回路出力許可レジスタ (ADVMONO)
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

			bit_rw_t <io_, bitpos::B0>     VDO;
		};
		static inline advmono_t<base + 0x1E4> ADVMONO;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 基準電圧コントロールレジスタ (ADVREFCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct advrefcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CREFSEL;
		};
		static inline advrefcr_t<0x0008'8084> ADVREFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADE 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adh_t : public s12adh_base_t<base> {

		typedef s12adh_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::SELECTB::S12ADI;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::SELECTB::S12GBADI;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::SELECTB::S12GCADI;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 900;				///< A/D 変換時間 0.9uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 24;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型 (S12AD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,		///< P40 (LFQFP100:  95) (LFQFP144: 141)
			AN001,		///< P41 (LFQFP100:  93) (LFQFP144: 139)
			AN002,		///< P42 (LFQFP100:  92) (LFQFP144: 138)
			AN003,		///< P43 (LFQFP100:  91) (LFQFP144: 137)
			AN004,		///< P44 (LFQFP100:  90) (LFQFP144: 136)
			AN005,		///< P45 (LFQFP100:  89) (LFQFP144: 135)
			AN006,		///< P46 (LFQFP100:  88) (LFQFP144: 134)
			AN007,		///< P47 (LFQFP100:  87) (LFQFP144: 133)
			AN008,		///< PE0 (LFQFP100:  78) (LFQFP144: 111)
			AN009,		///< PE1 (LFQFP100:  77) (LFQFP144: 110)
			AN010,		///< PE2 (LFQFP100:  76) (LFQFP144: 109)
			AN011,		///< PE3 (LFQFP100:  75) (LFQFP144: 108)
			AN012,		///< PE4 (LFQFP100:  74) (LFQFP144: 107)
			AN013,		///< PE5 (LFQFP100:  73) (LFQFP144: 106)
			AN014,		///< PE6 (LFQFP100:  72) (LFQFP144: 102)
			AN015,		///< PE7 (LFQFP100:  71) (LFQFP144: 101)
			AN016,		///< PD0 (LFQFP100:  86) (LFQFP144: 126)
			AN017,		///< PD1 (LFQFP100:  85) (LFQFP144: 125)
			AN018,		///< PD2 (LFQFP100:  84) (LFQFP144: 124)
			AN019,		///< PD3 (LFQFP100:  83) (LFQFP144: 123)
			AN020,		///< PD4 (LFQFP100:  82) (LFQFP144: 122)
			AN021,		///< PD5 (LFQFP100:  81) (LFQFP144: 121)
			AN022,		///< PD6 (LFQFP100:  80) (LFQFP144: 120)
			AN023,		///< PD7 (LFQFP100:  79) (LFQFP144: 119)

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
		static void enable(ANALOG an, bool ena = true)
		{
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

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
					PORT4::PDR.B4 = 0;
					PORT4::PMR.B4 = 0;
				}
				MPC::P44PFS.ASEL = ena;
				break;
			case ANALOG::AN005:
				if(ena) {
					PORT4::PDR.B5 = 0;
					PORT4::PMR.B5 = 0;
				}
				MPC::P45PFS.ASEL = ena;
				break;
			case ANALOG::AN006:
				if(ena) {
					PORT4::PDR.B6 = 0;
					PORT4::PMR.B6 = 0;
				}
				MPC::P46PFS.ASEL = ena;
				break;
			case ANALOG::AN007:
				if(ena) {
					PORT4::PDR.B7 = 0;
					PORT4::PMR.B7 = 0;
				}
				MPC::P47PFS.ASEL = ena;
				break;
			case ANALOG::AN008:
				if(ena) {
					PORTE::PDR.B0 = 0;
					PORTE::PMR.B0 = 0;
				}
				MPC::PE0PFS.ASEL = ena;
				break;
			case ANALOG::AN009:
				if(ena) {
					PORTE::PDR.B1 = 0;
					PORTE::PMR.B1 = 0;
				}
				MPC::PE1PFS.ASEL = ena;
				break;
			case ANALOG::AN010:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::AN011:
				if(ena) {
					PORTE::PDR.B3 = 0;
					PORTE::PMR.B3 = 0;
				}
				MPC::PE3PFS.ASEL = ena;
				break;
			case ANALOG::AN012:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::AN013:
				if(ena) {
					PORTE::PDR.B5 = 0;
					PORTE::PMR.B5 = 0;
				}
				MPC::PE5PFS.ASEL = ena;
				break;
			case ANALOG::AN014:
				if(ena) {
					PORTE::PDR.B6 = 0;
					PORTE::PMR.B6 = 0;
				}
				MPC::PE6PFS.ASEL = ena;
				break;
			case ANALOG::AN015:
				if(ena) {
					PORTE::PDR.B7 = 0;
					PORTE::PMR.B7 = 0;
				}
				MPC::PE7PFS.ASEL = ena;
				break;
			case ANALOG::AN016:
				if(ena) {
					PORTD::PDR.B0 = 0;
					PORTD::PMR.B0 = 0;
				}
				MPC::PD0PFS.ASEL = ena;
				break;
			case ANALOG::AN017:
				if(ena) {
					PORTD::PDR.B1 = 0;
					PORTD::PMR.B1 = 0;
				}
				MPC::PD1PFS.ASEL = ena;
				break;
			case ANALOG::AN018:
				if(ena) {
					PORTD::PDR.B2 = 0;
					PORTD::PMR.B2 = 0;
				}
				MPC::PD2PFS.ASEL = ena;
				break;
			case ANALOG::AN019:
				if(ena) {
					PORTD::PDR.B3 = 0;
					PORTD::PMR.B3 = 0;
				}
				MPC::PD3PFS.ASEL = ena;
				break;
			case ANALOG::AN020:
				if(ena) {
					PORTD::PDR.B4 = 0;
					PORTD::PMR.B4 = 0;
				}
				MPC::PD4PFS.ASEL = ena;
				break;
			case ANALOG::AN021:
				if(ena) {
					PORTD::PDR.B5 = 0;
					PORTD::PMR.B5 = 0;
				}
				MPC::PD5PFS.ASEL = ena;
				break;
			case ANALOG::AN022:
				if(ena) {
					PORTD::PDR.B6 = 0;
					PORTD::PMR.B6 = 0;
				}
				MPC::PD6PFS.ASEL = ena;
				break;
			case ANALOG::AN023:
				if(ena) {
					PORTD::PDR.B7 = 0;
					PORTD::PMR.B7 = 0;
				}
				MPC::PD7PFS.ASEL = ena;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_tr_t<ANALOG, BASE::ADDR0_::address, ANALOG::TEMP, BASE::ADTSDR_::address,
			ANALOG::REF, BASE::ADOCDR_::address> ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ、０、１
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adans01_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 16> ANS0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 8>  ANS1;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		static inline adans01_t<BASE::ADANSA0_::address, BASE::ADANSA1_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B（ADANSB）
		*/
		//-----------------------------------------------------------------//
		static inline adans01_t<BASE::ADANSB0_::address, BASE::ADANSB1_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C（ADANSC）
		*/
		//-----------------------------------------------------------------//
		static inline adans01_t<BASE::ADANSC0_::address, BASE::ADANSC1_::address> ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ n (ADSCSn) (n = 0 ～ 23)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adscs_t<ANALOG, ANALOG::AN023, base + 0xC0> ADSCS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adads_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 16> ADS0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 8>  ADS1;
		};
		static inline adads_t<BASE::ADADS0_::address, BASE::ADADS1_::address> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR） @n
					0 ～ 15, L, T, O
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1il_tr_t<ANALOG, BASE::ADSSTR0_::address, BASE::ADSSTR1_::address,
			BASE::ADSSTRL_::address, ANALOG::TEMP, BASE::ADSSTRT_::address, ANALOG::REF, BASE::ADSSTRO_::address> ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネル選択レジスタ (ADCMPANSR)
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adcmpansr_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 16> CMPCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 8>  CMPCHA1;
		};
		static inline adcmpansr_t<BASE::ADCMPANSR0_::address, BASE::ADCMPANSR1_::address> ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 比較条件設定レジスタ (ADCMPLR)
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adcmplr_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 16> CMPLCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 8>  CMPLCHA1;
		};
		static inline adcmplr_t<BASE::ADCMPLR0_::address, BASE::ADCMPLR1_::address> ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネルステータスレジスタ (ADCMPSR)
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adcmpsr_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 16> CMPSTCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 8>  CMPSTCHA1;
		};
		static inline adcmpsr_t<BASE::ADCMPSR0_::address, BASE::ADCMPSR1_::address> ADCMPSR;
	};

	typedef s12adh_t<0x0008'9000>  S12AD;
}
