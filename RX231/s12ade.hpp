#pragma once
//=========================================================================//
/*!	@file
	@brief	S12ADE 定義 @n
			ユニット構成は同等だが、RX140, RX231 でチャネル構成が異なる @n
			RX140:       8+9  input single A/D @n
			RX230/RX231: 8+16 input single A/D
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADE ベース定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ade_base_t {

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
			@brief  A/D データレジスタ 24（ADDR24）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x50> ADDR24;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 25（ADDR25）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x52> ADDR25;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 26（ADDR26）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x54> ADDR26;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 27（ADDR27）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x56> ADDR27;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 28（ADDR28）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x58> ADDR28;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 29（ADDR29）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x5A> ADDR29;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 30（ADDR30）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x5C> ADDR30;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 31（ADDR31）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x5E> ADDR31;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x18> ADDBLDR;


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
			bit_rw_t <io_, bitpos::B8>     ANSA108;
			bit_rw_t <io_, bitpos::B9>     ANSA109;
			bit_rw_t <io_, bitpos::B10>    ANSA110;
			bit_rw_t <io_, bitpos::B11>    ANSA111;
			bit_rw_t <io_, bitpos::B12>    ANSA112;
			bit_rw_t <io_, bitpos::B13>    ANSA113;
			bit_rw_t <io_, bitpos::B14>    ANSA114;
			bit_rw_t <io_, bitpos::B15>    ANSA115;
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
			bit_rw_t <io_, bitpos::B8>     ANSB108;
			bit_rw_t <io_, bitpos::B9>     ANSB109;
			bit_rw_t <io_, bitpos::B10>    ANSB110;
			bit_rw_t <io_, bitpos::B11>    ANSB111;
			bit_rw_t <io_, bitpos::B12>    ANSB112;
			bit_rw_t <io_, bitpos::B13>    ANSB113;
			bit_rw_t <io_, bitpos::B14>    ANSB114;
			bit_rw_t <io_, bitpos::B15>    ANSB115;
		};
		typedef adansb1_t<base + 0x16> ADANSB1_;
		static inline ADANSB1_ ADANSB1;


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
			bit_rw_t <io_, bitpos::B8>     ADS108;
			bit_rw_t <io_, bitpos::B9>     ADS109;
			bit_rw_t <io_, bitpos::B10>    ADS110;
			bit_rw_t <io_, bitpos::B11>    ADS111;
			bit_rw_t <io_, bitpos::B12>    ADS112;
			bit_rw_t <io_, bitpos::B13>    ADS113;
			bit_rw_t <io_, bitpos::B14>    ADS114;
			bit_rw_t <io_, bitpos::B15>    ADS115;
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
			bit_rw_t<io_, bitpos::B9>      OCS;
		};
		static inline adexicr_t<base + 0x12>  ADEXICR;


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

			bits_rw_t<io_, bitpos::B0, 2>  ELCC;
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

			bit_rw_t <io_, bitpos::B14>    WCMPE;
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
			bit_rw_t <io_, bitpos::B8>     CMPCHA108;
			bit_rw_t <io_, bitpos::B9>     CMPCHA109;
			bit_rw_t <io_, bitpos::B10>    CMPCHA110;
			bit_rw_t <io_, bitpos::B11>    CMPCHA111;
			bit_rw_t <io_, bitpos::B12>    CMPCHA112;
			bit_rw_t <io_, bitpos::B13>    CMPCHA113;
			bit_rw_t <io_, bitpos::B14>    CMPCHA114;
			bit_rw_t <io_, bitpos::B15>    CMPCHA115;
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
			bit_rw_t <io_, bitpos::B8>     CMPLCHA108;
			bit_rw_t <io_, bitpos::B9>     CMPLCHA109;
			bit_rw_t <io_, bitpos::B10>    CMPLCHA110;
			bit_rw_t <io_, bitpos::B11>    CMPLCHA111;
			bit_rw_t <io_, bitpos::B12>    CMPLCHA112;
			bit_rw_t <io_, bitpos::B13>    CMPLCHA113;
			bit_rw_t <io_, bitpos::B14>    CMPLCHA114;
			bit_rw_t <io_, bitpos::B15>    CMPLCHA115;
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
			bit_rw_t <io_, bitpos::B8>     CMPSTCHA108;
			bit_rw_t <io_, bitpos::B9>     CMPSTCHA109;
			bit_rw_t <io_, bitpos::B10>    CMPSTCHA110;
			bit_rw_t <io_, bitpos::B11>    CMPSTCHA111;
			bit_rw_t <io_, bitpos::B12>    CMPSTCHA112;
			bit_rw_t <io_, bitpos::B13>    CMPSTCHA113;
			bit_rw_t <io_, bitpos::B14>    CMPSTCHA114;
			bit_rw_t <io_, bitpos::B15>    CMPSTCHA115;
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

			bit_rw_t <io_, bitpos::B0>     CMPSTTSA;
			bit_rw_t <io_, bitpos::B1>     CMPSTOCA;
		};
		static inline adcmpser_t<base + 0xA4>  ADCMPSER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 高電位 / 低電位基準電圧コントロールレジスタ (ADHVREFCNT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adhvrefcnt_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  HVSEL;

			bit_rw_t <io_, bitpos::B4>     LVSEL;

			bit_rw_t <io_, bitpos::B7>     ADSLP;
		};
		static inline adhvrefcnt_t<base + 0x8A>  ADHVREFCNT;


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
			@brief	A/D データ格納バッファレジスタ 0 (ADBUF0)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xB0> ADBUF0_;
		static inline ADBUF0_ ADBUF0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 1 (ADBUF1)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xB2> ADBUF1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 2 (ADBUF2)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xB4> ADBUF2;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 3 (ADBUF3)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xB6> ADBUF3;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 4 (ADBUF4)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xB8> ADBUF4;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 5 (ADBUF5)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xBA> ADBUF5;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 6 (ADBUF6)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xBC> ADBUF6;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 7 (ADBUF7)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xBE> ADBUF7;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 8 (ADBUF8)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xC0> ADBUF8;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 9 (ADBUF9)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xC2> ADBUF9;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 10 (ADBUF10)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xC4> ADBUF10;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 11 (ADBUF11)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xC6> ADBUF11;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 12 (ADBUF12)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xC8> ADBUF12;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 13 (ADBUF13)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xCA> ADBUF13;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 14 (ADBUF14)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xCC> ADBUF14;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファレジスタ 15 (ADBUF15)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xCE> ADBUF15;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファイネーブルレジスタ (ADBUFEN)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adbufen_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     BUFEN;
		};
		static inline adbufen_t<base + 0xD0>  ADBUFEN;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データ格納バッファポインタレジスタ (ADBUFPTR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adbufptr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  BUFPTR;
			bit_rw_t <io_, bitpos::B4>     PTROVF;
		};
		static inline adbufptr_t<base + 0xD2>  ADBUFPTR;
	};


#if defined(SIG_RX231)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADE 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ade_t : public s12ade_base_t<base> {

		typedef s12ade_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI0;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI;		///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 830;				///< A/D 変換時間 0.83uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 24;	///< アナログ入力数


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,	///< AN000 入力
			AN001,
			AN002,
			AN003,
			AN004,
			AN005,
			AN006,
			AN007,

			AN016 = 16,
			AN017,
			AN018,
			AN019,
			AN020,
			AN021,
			AN022,
			AN023,
			AN024,
			AN025,
			AN026,
			AN027,
			AN028,
			AN029,
			AN030,
			AN031,

			TEMP,	///< 温度センサ
			REF,	///< 内部基準電圧
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
			case ANALOG::AN016:
				if(ena) {
					PORTE::PDR.B0 = 0;
					PORTE::PMR.B0 = 0;
				}
				MPC::PE0PFS.ASEL = ena;
				break;
			case ANALOG::AN017:
				if(ena) {
					PORTE::PDR.B1 = 0;
					PORTE::PMR.B1 = 0;
				}
				MPC::PE1PFS.ASEL = ena;
				break;
			case ANALOG::AN018:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::AN019:
				if(ena) {
					PORTE::PDR.B3 = 0;
					PORTE::PMR.B3 = 0;
				}
				MPC::PE3PFS.ASEL = ena;
				break;
			case ANALOG::AN020:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::AN021:
				if(ena) {
					PORTE::PDR.B5 = 0;
					PORTE::PMR.B5 = 0;
				}
				MPC::PE5PFS.ASEL = ena;
				break;
			case ANALOG::AN022:
				if(ena) {
					PORTE::PDR.B6 = 0;
					PORTE::PMR.B6 = 0;
				}
				MPC::PE6PFS.ASEL = ena;
				break;
			case ANALOG::AN023:
				if(ena) {
					PORTE::PDR.B7 = 0;
					PORTE::PMR.B7 = 0;
				}
				MPC::PE7PFS.ASEL = ena;
				break;
			case ANALOG::AN024:
				if(ena) {
					PORTD::PDR.B0 = 0;
					PORTD::PMR.B0 = 0;
				}
				MPC::PD0PFS.ASEL = ena;
				break;
			case ANALOG::AN025:
				if(ena) {
					PORTD::PDR.B1 = 0;
					PORTD::PMR.B1 = 0;
				}
				MPC::PD1PFS.ASEL = ena;
				break;
			case ANALOG::AN026:
				if(ena) {
					PORTD::PDR.B2 = 0;
					PORTD::PMR.B2 = 0;
				}
				MPC::PD2PFS.ASEL = ena;
				break;
			case ANALOG::AN027:
				if(ena) {
					PORTD::PDR.B3 = 0;
					PORTD::PMR.B3 = 0;
				}
				MPC::PD3PFS.ASEL = ena;
				break;
			case ANALOG::AN028:
				if(ena) {
					PORTD::PDR.B4 = 0;
					PORTD::PMR.B4 = 0;
				}
				MPC::PD4PFS.ASEL = ena;
				break;
			case ANALOG::AN029:
				if(ena) {
					PORTD::PDR.B5 = 0;
					PORTD::PMR.B5 = 0;
				}
				MPC::PD5PFS.ASEL = ena;
				break;
			case ANALOG::AN030:
				if(ena) {
					PORTD::PDR.B6 = 0;
					PORTD::PMR.B6 = 0;
				}
				MPC::PD6PFS.ASEL = ena;
				break;
			case ANALOG::AN031:
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
			@brief  A/D チャネル選択レジスタ（ADANS）
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adans_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 8>  ANSA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> ANSA1;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A (ADANSA)
		*/
		//-----------------------------------------------------------------//
		static inline adans_t<BASE::ADANSA0_::address, BASE::ADANSA1_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B (ADANSB)
		*/
		//-----------------------------------------------------------------//
		static inline adans_t<BASE::ADANSB0_::address, BASE::ADANSB1_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adads_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 8>  ADS0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> ADS1;
		};
		static inline adads_t<BASE::ADADS0_::address, BASE::ADADS1_::address> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
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
			bits_rw_t<io0_, bitpos::B0, 8>  CMPCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> CMPCHA1;
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
			bits_rw_t<io0_, bitpos::B0, 8>  CMPLCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> CMPLCHA1;
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
			bits_rw_t<io0_, bitpos::B0, 8>  CMPSTCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> CMPSTCHA1;
		};
		static inline adcmpsr_t<BASE::ADCMPSR0_::address, BASE::ADCMPSR1_::address> ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ格納バッファレジスタ (ADBUF) (idx = 0 ～ 15)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adbuf_t<BASE::ADBUF_::address, 15> ADBUF;
	};


#elif defined(SIG_RX140)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADE 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ade_t : public s12ade_base_t<base> {

		typedef s12ade_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI0;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI;		///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 880;				///< A/D 変換時間 (ADCCR.CCS=0) 0.83uS、単位「ns」
		static constexpr uint32_t CONV_TIME2_NS = 670;				///< A/D 変換時間 (ADCCR.CCS=1) 0.67uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 17;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,	///< AN000 入力
			AN001,
			AN002,
			AN003,
			AN004,
			AN005,
			AN006,
			AN007,

			AN016 = 16,
			AN017,
			AN018,
			AN019,
			AN020,
			AN021,

			AN024 = 24,
			AN025,
			AN026,

			TEMP,	///< 温度センサ
			REF,	///< 内部基準電圧
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
			case ANALOG::AN016:
				if(ena) {
					PORTE::PDR.B0 = 0;
					PORTE::PMR.B0 = 0;
				}
				MPC::PE0PFS.ASEL = ena;
				break;
			case ANALOG::AN017:
				if(ena) {
					PORTE::PDR.B1 = 0;
					PORTE::PMR.B1 = 0;
				}
				MPC::PE1PFS.ASEL = ena;
				break;
			case ANALOG::AN018:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::AN019:
				if(ena) {
					PORTE::PDR.B3 = 0;
					PORTE::PMR.B3 = 0;
				}
				MPC::PE3PFS.ASEL = ena;
				break;
			case ANALOG::AN020:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::AN021:
				if(ena) {
					PORTE::PDR.B5 = 0;
					PORTE::PMR.B5 = 0;
				}
				MPC::PE5PFS.ASEL = ena;
				break;

			case ANALOG::AN024:
				if(ena) {
					PORTD::PDR.B0 = 0;
					PORTD::PMR.B0 = 0;
				}
				MPC::PD0PFS.ASEL = ena;
				break;
			case ANALOG::AN025:
				if(ena) {
					PORTD::PDR.B1 = 0;
					PORTD::PMR.B1 = 0;
				}
				MPC::PD1PFS.ASEL = ena;
				break;
			case ANALOG::AN026:
				if(ena) {
					PORTD::PDR.B2 = 0;
					PORTD::PMR.B2 = 0;
				}
				MPC::PD2PFS.ASEL = ena;
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
			@brief  A/D チャネル選択レジスタ（ADANS）
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adans_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 8>  ANSA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> ANSA1;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A (ADANSA)
		*/
		//-----------------------------------------------------------------//
		static inline adans_t<BASE::ADANSA0_::address, BASE::ADANSA1_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B (ADANSB)
		*/
		//-----------------------------------------------------------------//
		static inline adans_t<BASE::ADANSB0_::address, BASE::ADANSB1_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
			@param[in] regadr0	レジスタアドレス０
			@param[in] regadr1	レジスタアドレス１
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr0, uint32_t regadr1>
		struct adads_t : public ad_utils::adans2_t<ANALOG, regadr0, regadr1> {
			typedef ad_utils::adans2_t<ANALOG, regadr0, regadr1> base_;
			using base_::operator ();

			typedef rw16_t<regadr0> io0_;
			bits_rw_t<io0_, bitpos::B0, 8>  ADS0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> ADS1;
		};
		static inline adads_t<BASE::ADADS0_::address, BASE::ADADS1_::address> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
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
			bits_rw_t<io0_, bitpos::B0, 8>  CMPCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> CMPCHA1;
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
			bits_rw_t<io0_, bitpos::B0, 8>  CMPLCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> CMPLCHA1;
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
			bits_rw_t<io0_, bitpos::B0, 8>  CMPSTCHA0;
			typedef rw16_t<regadr1> io1_;
			bits_rw_t<io1_, bitpos::B0, 16> CMPSTCHA1;
		};
		static inline adcmpsr_t<BASE::ADCMPSR0_::address, BASE::ADCMPSR1_::address> ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ格納バッファレジスタ (ADBUF) (idx = 0 ～ 15)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adbuf_t<BASE::ADBUF_::address, 15> ADBUF;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換サイクル制御レジスタ (ADCCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B1>  CCS;
		};
		static inline adccr_t<base + 0x7E>  ADCCR;
	};
#endif

	typedef s12ade_t<0x0008'9000>  S12AD;
}
