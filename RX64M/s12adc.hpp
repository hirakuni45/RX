#pragma once
//=========================================================================//
/*!	@file
	@brief	12-Bit A/D Converter / 12 ビット A/D コンバータ (RX64M/RX71M)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADC base class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adc_base_t {

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
			@brief  A/D データ 2 重化レジスタ（ADDBLDR）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x18> ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ A（ADDBLDRA）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x84> ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ B（ADDBLDRB）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x86> ADDBLDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 自己診断データレジスタ（ ADRD ）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x1E>  ADRD;


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
		static inline adcsr_t<base + 0x00>  ADCSR;


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

			bits_rw_t<io_, bitpos::B0, 2>  ADC;

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

			bits_rw_t<io_, bitpos::B1, 2>  ADPRC;

			bit_rw_t <io_, bitpos::B5>     ACE;

			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ n（ADSSTRn）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adsstrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SST;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x60> ADSSTR0_;
		static inline ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x73> ADSSTR1_;
		static inline ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static inline adsstrn_t<base + 0x74> ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static inline adsstrn_t<base + 0x75> ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		static inline adsstrn_t<base + 0x76> ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		static inline adsstrn_t<base + 0x77> ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		static inline adsstrn_t<base + 0x78> ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		static inline adsstrn_t<base + 0x79> ADSSTR7;


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

			bit_rw_t<io_, bitpos::B15>  GBRP;
		};
		static inline adgspcr_t<base + 0x80>  ADGSPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアコントロールレジスタ（ ADCMPCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B6>   WCMPE;
			bit_rw_t <io_, bitpos::B7>   CMPIE;
		};
		static inline adcmpcr_t<base + 0x90>  ADCMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 0 （ ADCMPDR0 ）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x9C> ADCMPDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 1 （ ADCMPDR1 ）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x9E> ADCMPDR1;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12adc_base_t<base> {

		typedef s12adc_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::SELECTB::S12ADI;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::SELECTB::S12GBADI;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 480;				///< 変換時間（ns）12 bits 変換モード

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型 (S12AD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,		///< P40 (LFQFP100:  95) (LFQFP144: 141) (LFQFP176: 173)
			AN001,		///< P41 (LFQFP100:  93) (LFQFP144: 139) (LFQFP176: 171)
			AN002,		///< P42 (LFQFP100:  92) (LFQFP144: 138) (LFQFP176: 170)
			AN003,		///< P43 (LFQFP100:  91) (LFQFP144: 137) (LFQFP176: 169)
			AN004,		///< P44 (LFQFP100:  90) (LFQFP144: 136) (LFQFP176: 168)
			AN005,		///< P45 (LFQFP100:  89) (LFQFP144: 135) (LFQFP176: 167)
			AN006,		///< P46 (LFQFP100:  88) (LFQFP144: 134) (LFQFP176: 166)
			AN007,		///< P47 (LFQFP100:  87) (LFQFP144: 133) (LFQFP176: 165)
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
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0（ADANSA0）
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

			bit_rw_t<io_, bitpos::B0>  ANSA000;
			bit_rw_t<io_, bitpos::B1>  ANSA001;
			bit_rw_t<io_, bitpos::B2>  ANSA002;
			bit_rw_t<io_, bitpos::B3>  ANSA003;
			bit_rw_t<io_, bitpos::B4>  ANSA004;
			bit_rw_t<io_, bitpos::B5>  ANSA005;
			bit_rw_t<io_, bitpos::B6>  ANSA006;
			bit_rw_t<io_, bitpos::B7>  ANSA007;
		};
		typedef adansa0_t<base + 0x04>  ADANSA0_;
		static inline ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0（ADANSB0）
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

			bit_rw_t<io_, bitpos::B0>  ANSB000;
			bit_rw_t<io_, bitpos::B1>  ANSB001;
			bit_rw_t<io_, bitpos::B2>  ANSB002;
			bit_rw_t<io_, bitpos::B3>  ANSB003;
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
		};
		typedef adansb0_t<base + 0x14>  ADANSB0_;
		static inline ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A (ADANSA)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSA0_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B (ADANSB)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSB0_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
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

			bit_rw_t<io_, bitpos::B0>  ADS000;
			bit_rw_t<io_, bitpos::B1>  ADS001;
			bit_rw_t<io_, bitpos::B2>  ADS002;
			bit_rw_t<io_, bitpos::B3>  ADS003;
			bit_rw_t<io_, bitpos::B4>  ADS004;
			bit_rw_t<io_, bitpos::B5>  ADS005;
			bit_rw_t<io_, bitpos::B6>  ADS006;
			bit_rw_t<io_, bitpos::B7>  ADS007;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ（ADADS）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADADS0_::address> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1i_t<ANALOG, BASE::ADSSTR0_::address, BASE::ADSSTR1_::address> ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプル & ホールド回路コントロールレジスタ（ADSHCR）
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
		static inline adshcr_t<base + 0x66>   ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプル＆ホールド動作モード選択レジスタ（ ADSHMSR ）
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
		static inline adshmsr_t<base + 0x7C>  ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 0 （ADCMPANSR0）
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

			bits_rw_t <io_, bitpos::B0, 8>  CMPS0;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static inline ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ （ADCMPANSR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPANSR0_::address> ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0 （ ADCMPLR0 ）
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

			bits_rw_t<io_, bitpos::B0, 8>  CMPL0;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static inline ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ （ADCMPLR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPLR0_::address> ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0 （ADCMPSR0）
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

			bits_rw_t<io_, bitpos::B0, 8>  CMPF0;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static inline ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0 （ADCMPSR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPSR0_::address> ADCMPSR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad1_t : public s12adc_base_t<base> {

		typedef s12adc_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::SELECTB::S12ADI1;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::SELECTB::S12GBADI1;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI1;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 480;				///< 変換時間（ns）12 bits 変換モード

		static constexpr uint32_t ANALOG_NUM = 21;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型 (S12AD1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN100,		///< PE2 (LFQFP100:  76) (LFQFP144: 109) (LFQFP176: 133)
			AN101,		///< PE3 (LFQFP100:  75) (LFQFP144: 108) (LFQFP176: 132)
			AN102,		///< PE4 (LFQFP100:  74) (LFQFP144: 107) (LFQFP176: 131)
			AN103,		///< PE5 (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
			AN104,		///< PE6 (LFQFP100:  72) (LFQFP144: 102) (LFQFP176: 126)
			AN105,		///< PE7 (LFQFP100:  71) (LFQFP144: 101) (LFQFP176: 125)
			AN106,		///< PD6 (LFQFP100:  80) (LFQFP144: 120) (LFQFP176: 145)
			AN107,		///< PD7 (LFQFP100:  79) (LFQFP144: 119) (LFQFP176: 143)
			AN108,		///< PD0 (LFQFP100:  86) (LFQFP144: 126) (LFQFP176: 158)
			AN109,		///< PD1 (LFQFP100:  85) (LFQFP144: 125) (LFQFP176: 156)
			AN110,		///< PD2 (LFQFP100:  84) (LFQFP144: 124) (LFQFP176: 154)
			AN111,		///< PD3 (LFQFP100:  83) (LFQFP144: 123) (LFQFP176: 150)
			AN112,		///< PD4 (LFQFP100:  82) (LFQFP144: 122) (LFQFP176: 148)
			AN113,		///< PD5 (LFQFP100:  81) (LFQFP144: 121) (LFQFP176: 147)
			AN114,		///< P90 (LFQFP100: ---) (LFQFP144: 131) (LFQFP176: 163)
			AN115,		///< P91 (LFQFP100: ---) (LFQFP144: 129) (LFQFP176: 161)
			AN116,		///< P92 (LFQFP100: ---) (LFQFP144: 128) (LFQFP176: 160)
			AN117,		///< P93 (LFQFP100: ---) (LFQFP144: 127) (LFQFP176: 159)
			AN118,		///< P00 (LFQFP100: ---) (LFQFP144:   8) (LFQFP176:   8)
			AN119,		///< P01 (LFQFP100: ---) (LFQFP144:   7) (LFQFP176:   7)
			AN120,		///< P02 (LFQFP100: ---) (LFQFP144:   6) (LFQFP176:   6)

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
			case ANALOG::AN100:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::AN101:
				if(ena) {
					PORTE::PDR.B3 = 0;
					PORTE::PMR.B3 = 0;
				}
				MPC::PE3PFS.ASEL = ena;
				break;
			case ANALOG::AN102:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::AN103:
				if(ena) {
					PORTE::PDR.B5 = 0;
					PORTE::PMR.B5 = 0;
				}
				MPC::PE5PFS.ASEL = ena;
				break;
			case ANALOG::AN104:
				if(ena) {
					PORTE::PDR.B6 = 0;
					PORTE::PMR.B6 = 0;
				}
				MPC::PE6PFS.ASEL = ena;
				break;
			case ANALOG::AN105:
				if(ena) {
					PORTE::PDR.B7 = 0;
					PORTE::PMR.B7 = 0;
				}
				MPC::PE7PFS.ASEL = ena;
				break;
			case ANALOG::AN106:
				if(ena) {
					PORTD::PDR.B6 = 0;
					PORTD::PMR.B6 = 0;
				}
				MPC::PD6PFS.ASEL = ena;
				break;
			case ANALOG::AN107:
				if(ena) {
					PORTD::PDR.B7 = 0;
					PORTD::PMR.B7 = 0;
				}
				MPC::PD7PFS.ASEL = ena;
				break;
			case ANALOG::AN108:
				if(ena) {
					PORTD::PDR.B0 = 0;
					PORTD::PMR.B0 = 0;
				}
				MPC::PD0PFS.ASEL = ena;
				break;
			case ANALOG::AN109:
				if(ena) {
					PORTD::PDR.B1 = 0;
					PORTD::PMR.B1 = 0;
				}
				MPC::PD1PFS.ASEL = ena;
				break;
			case ANALOG::AN110:
				if(ena) {
					PORTD::PDR.B2 = 0;
					PORTD::PMR.B2 = 0;
				}
				MPC::PD2PFS.ASEL = ena;
				break;
			case ANALOG::AN111:
				if(ena) {
					PORTD::PDR.B3 = 0;
					PORTD::PMR.B3 = 0;
				}
				MPC::PD3PFS.ASEL = ena;
				break;
			case ANALOG::AN112:
				if(ena) {
					PORTD::PDR.B4 = 0;
					PORTD::PMR.B4 = 0;
				}
				MPC::PD4PFS.ASEL = ena;
				break;
			case ANALOG::AN113:
				if(ena) {
					PORTD::PDR.B5 = 0;
					PORTD::PMR.B5 = 0;
				}
				MPC::PD5PFS.ASEL = ena;
				break;
			case ANALOG::AN114:
				if(ena) {
					PORT9::PDR.B0 = 0;
					PORT9::PMR.B0 = 0;
				}
				MPC::P90PFS.ASEL = ena;
				break;
			case ANALOG::AN115:
				if(ena) {
					PORT9::PDR.B1 = 0;
					PORT9::PMR.B1 = 0;
				}
				MPC::P91PFS.ASEL = ena;
				break;
			case ANALOG::AN116:
				if(ena) {
					PORT9::PDR.B2 = 0;
					PORT9::PMR.B2 = 0;
				}
				MPC::P92PFS.ASEL = ena;
				break;
			case ANALOG::AN117:
				if(ena) {
					PORT9::PDR.B3 = 0;
					PORT9::PMR.B3 = 0;
				}
				MPC::P93PFS.ASEL = ena;
				break;
			case ANALOG::AN118:
				if(ena) {
					PORT0::PDR.B0 = 0;
					PORT0::PMR.B0 = 0;
				}
				MPC::P00PFS.ASEL = ena;
				break;
			case ANALOG::AN119:
				if(ena) {
					PORT0::PDR.B1 = 0;
					PORT0::PMR.B1 = 0;
				}
				MPC::P01PFS.ASEL = ena;
				break;
			case ANALOG::AN120:
				if(ena) {
					PORT0::PDR.B2 = 0;
					PORT0::PMR.B2 = 0;
				}
				MPC::P02PFS.ASEL = ena;
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
		static inline ro16_t<base + 0x40> ADDR16;


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
			@brief  A/D 温度センサデータレジスタ（ ADTSDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1A> ADTSDR_;
		static inline ADTSDR_ ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief   A/D 内部基準電圧データレジスタ（ ADOCDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x01C> ADOCDR_;
		static inline ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_tr_t<ANALOG, BASE::ADDR0_::address,
			ANALOG::TEMP, ADTSDR_::address, ANALOG::REF, ADOCDR_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0（ADANSA0）
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

			bit_rw_t<io_, bitpos::B0>  ANSA100;
			bit_rw_t<io_, bitpos::B1>  ANSA101;
			bit_rw_t<io_, bitpos::B2>  ANSA102;
			bit_rw_t<io_, bitpos::B3>  ANSA103;
			bit_rw_t<io_, bitpos::B4>  ANSA104;
			bit_rw_t<io_, bitpos::B5>  ANSA105;
			bit_rw_t<io_, bitpos::B6>  ANSA106;
			bit_rw_t<io_, bitpos::B7>  ANSA107;
			bit_rw_t<io_, bitpos::B8>  ANSA108;
			bit_rw_t<io_, bitpos::B9>  ANSA109;
			bit_rw_t<io_, bitpos::B10> ANSA110;
			bit_rw_t<io_, bitpos::B11> ANSA111;
			bit_rw_t<io_, bitpos::B12> ANSA112;
			bit_rw_t<io_, bitpos::B13> ANSA113;
			bit_rw_t<io_, bitpos::B14> ANSA114;
			bit_rw_t<io_, bitpos::B15> ANSA115;
		};
		typedef adansa0_t<base + 0x04>   ADANSA0_;
		static inline ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A1（ADANSA1）
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

			bit_rw_t<io_, bitpos::B0>  ANSA116;
			bit_rw_t<io_, bitpos::B1>  ANSA117;
			bit_rw_t<io_, bitpos::B2>  ANSA118;
			bit_rw_t<io_, bitpos::B3>  ANSA119;
			bit_rw_t<io_, bitpos::B4>  ANSA120;
		};
		typedef adansa1_t<base + 0x06>   ADANSA1_;
		static inline ADANSA1_ ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSA0_::address, ADANSA1_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0（ADANSB0）
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

			bit_rw_t<io_, bitpos::B0>  ANSB100;
			bit_rw_t<io_, bitpos::B1>  ANSB101;
			bit_rw_t<io_, bitpos::B2>  ANSB102;
			bit_rw_t<io_, bitpos::B3>  ANSB103;
			bit_rw_t<io_, bitpos::B4>  ANSB104;
			bit_rw_t<io_, bitpos::B5>  ANSB105;
			bit_rw_t<io_, bitpos::B6>  ANSB106;
			bit_rw_t<io_, bitpos::B7>  ANSB107;
			bit_rw_t<io_, bitpos::B8>  ANSB108;
			bit_rw_t<io_, bitpos::B9>  ANSB109;
			bit_rw_t<io_, bitpos::B10> ANSB110;
			bit_rw_t<io_, bitpos::B11> ANSB111;
			bit_rw_t<io_, bitpos::B12> ANSB112;
			bit_rw_t<io_, bitpos::B13> ANSB113;
			bit_rw_t<io_, bitpos::B14> ANSB114;
			bit_rw_t<io_, bitpos::B15> ANSB115;
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static inline ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1（ADANSB1）
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

			bit_rw_t<io_, bitpos::B0>  ANSB116;
			bit_rw_t<io_, bitpos::B1>  ANSB117;
			bit_rw_t<io_, bitpos::B2>  ANSB118;
			bit_rw_t<io_, bitpos::B3>  ANSB119;
			bit_rw_t<io_, bitpos::B4>  ANSB120;
		};
		typedef adansb1_t<base + 0x16>   ADANSB1_;
		static inline ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSB0_::address, ADANSB1_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
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

			bit_rw_t<io_, bitpos::B0>   ADS100;
			bit_rw_t<io_, bitpos::B1>   ADS101;
			bit_rw_t<io_, bitpos::B2>   ADS102;
			bit_rw_t<io_, bitpos::B3>   ADS103;
			bit_rw_t<io_, bitpos::B4>   ADS104;
			bit_rw_t<io_, bitpos::B5>   ADS105;
			bit_rw_t<io_, bitpos::B6>   ADS106;
			bit_rw_t<io_, bitpos::B7>   ADS107;
			bit_rw_t<io_, bitpos::B8>   ADS108;
			bit_rw_t<io_, bitpos::B9>   ADS109;
			bit_rw_t<io_, bitpos::B10>  ADS110;
			bit_rw_t<io_, bitpos::B11>  ADS111;
			bit_rw_t<io_, bitpos::B12>  ADS112;
			bit_rw_t<io_, bitpos::B13>  ADS113;
			bit_rw_t<io_, bitpos::B14>  ADS114;
			bit_rw_t<io_, bitpos::B15>  ADS115;
		};
		typedef adads0_t<base + 0x08>   ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均モード選択レジスタ 1 （ ADADS1 ）
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

			bit_rw_t<io_, bitpos::B0>   ADS116;
			bit_rw_t<io_, bitpos::B1>   ADS117;
			bit_rw_t<io_, bitpos::B2>   ADS118;
			bit_rw_t<io_, bitpos::B3>   ADS119;
			bit_rw_t<io_, bitpos::B4>   ADS120;
		};
		typedef adads1_t<base + 0x10>   ADADS1_;
		static inline ADADS1_ ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均モード選択レジスタ （ ADADS ）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADADS0_::address, ADADS1_::address> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換拡張入力コントロールレジスタ（ ADEXICR ）
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

			bits_rw_t<io_, bitpos::B13, 2> EXSEL;
			bit_rw_t<io_, bitpos::B15>     EXOEN;
		};
		static inline adexicr_t<base + 0x12>   ADEXICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ n（ADSSTRn）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adsstrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SST;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x61> ADSSTRL_;
		static inline ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ T（ADSSTRT）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x70> ADSSTRT_;
		static inline ADSSTRT_ ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x71> ADSSTRO_;
		static inline ADSSTRO_ ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1il_tr_t<ANALOG, BASE::ADSSTR0_::address, BASE::ADSSTR1_::address, ADSSTRL_::address,
			ANALOG::TEMP, ADSSTRT_::address, ANALOG::REF, ADSSTRO_::address> ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 0 （ADCMPANSR0）
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

			bits_rw_t <io_, bitpos::B0, 8>  CMPS0;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static inline ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 1 （ ADCMPANSR1 ）
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

			bits_rw_t <io_, bitpos::B0, 5>  CMPS1;
		};
		typedef adcmpansr1_t<base + 0x96>  ADCMPANSR1_;
		static inline ADCMPANSR1_ ADCMPANSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ （ADCMPANSR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADCMPANSR0_::address, ADCMPANSR1_::address> ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択拡張レジスタ（ADCMPANSER）
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

			bit_rw_t <io_, bitpos::B0>  CMPSTS;
			bit_rw_t <io_, bitpos::B1>  CMPSOC;
		};
		static inline adcmpanser_t<base + 0x92>  ADCMPANSER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0 （ADCMPLR0）
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

			bits_rw_t<io_, bitpos::B0, 8>  CMPL0;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static inline ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 1 （ADCMPLR1）
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

			bits_rw_t<io_, bitpos::B0, 5>  CMPL1;
		};
		typedef adcmplr1_t<base + 0x9A>  ADCMPLR1_;
		static inline ADCMPLR1_ ADCMPLR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ（ADCMPLR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADCMPLR0_::address, ADCMPLR1_::address> ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベル拡張レジスタ（ADCMPLER）
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

			bit_rw_t<io_, bitpos::B0>  CMPLTS;
			bit_rw_t<io_, bitpos::B0>  CMPLOC;
		};
		static inline adcmpler_t<base + 0x93>  ADCMPLER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0（ADCMPSR0）
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

			bits_rw_t<io_, bitpos::B0, 8>  CMPF0;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static inline ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 1（ ADCMPSR1 ）
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

			bits_rw_t<io_, bitpos::B0, 5>  CMPF1;
		};
		typedef adcmpsr1_t<base + 0xA2>  ADCMPSR1_;
		static inline ADCMPSR1_ ADCMPSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ（ADCMPSR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADCMPSR0_::address, ADCMPSR1_::address> ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータス拡張レジスタ（ADCMPSER）
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

			bit_rw_t<io_, bitpos::B0>  CMPFTS;
			bit_rw_t<io_, bitpos::B1>  CMPFOC;
		};
		static inline adcmpser_t<base + 0xA4>  ADCMPSER;
	};

	typedef s12ad_t <0x00089000> S12AD;
	typedef s12ad1_t<0x00089100> S12AD1;
}
