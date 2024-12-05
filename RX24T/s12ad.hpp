#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24T/RX24U グループ・S12AD 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX24T)
#include "RX24T/peripheral.hpp"
#include "RX24T/icu.hpp"
#elif defined(SIG_RX24U)
#include "RX24U/peripheral.hpp"
#include "RX24U/icu.hpp"
#endif
#include "RX24T/port.hpp"
#include "RX24T/mpc.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_base_t {

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
		static inline adgctrgr_t<base + 0xD9>  ADGCTRGR;


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
			bit_rw_t<io_, bitpos::B14>  LGRRS;
			bit_rw_t<io_, bitpos::B15>  GBRP;
		};
		static inline adgspcr_t<base + 0x80>  ADGSPCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI;		///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI;		///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::GCADI;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKD;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 5;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,			///< AN000 入力
			AN001,			///< AN001 入力
			AN002,			///< AN002 入力
			AN003,			///< AN003 入力
			AN016 = 0x10,	///< AN016 入力
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
			case ANALOG::AN016:
				if(ena) {
					PORT2::PDR.B0 = 0;
					PORT2::PMR.B0 = 0;
				}
				MPC::P20PFS.ASEL = ena;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x40> ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
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
		};
		typedef adansa0_t<base + 0x04> ADANSA0_;
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

			bit_rw_t<io_, bitpos::B0>  ANSA100;
		};
		typedef adansa1_t<base + 0x06> ADANSA1_;
		static inline ADANSA1_ ADANSA1;


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
		};
		typedef adansb0_t<base + 0x14> ADANSB0_;
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

			bit_rw_t<io_, bitpos::B0>  ANSB100;
		};
		typedef adansb1_t<base + 0x16> ADANSB1_;
		static inline ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
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

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
		};
		typedef adansc0_t<base + 0xD4> ADANSC0_;
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1（ADANSC1）
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

			bit_rw_t<io_, bitpos::B0>  ANSC100;
		};
		typedef adansc1_t<base + 0xD6> ADANSC1_;
		static inline ADANSC1_ ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSA0_::address, ADANSA1_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B（ADANSB）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSB0_::address, ADANSB1_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C（ADANSC）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSC0_::address, ADANSC1_::address> ADANSC;


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
		};
		typedef adads0_t<base + 0x08> ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 1（ADADS1）
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

			bit_rw_t<io_, bitpos::B0>  ADS100;
		};
		typedef adads1_t<base + 0x0A> ADADS1_;
		static ADADS1_ ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ（ADADS）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADADS0_::address, ADADS1_::address> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> ADSSTRL_;
		static inline ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static inline ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE1> ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE2> ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE3> ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr2_t<ANALOG, ADSSTR0_::address, ADSSTRL_::address> ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D プログラマブルゲインアンプコントロールレジスタ（ADPGACR）
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

			bit_rw_t<io_, bitpos::B1>  P000SEL1;
			bit_rw_t<io_, bitpos::B2>  P000ENAMP;
		};
		static inline adpgacr_t<base + 0x1A0>  ADPGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D プログラマブルゲインアンプゲイン設定レジスタ 0（ADPGAGS0）
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

			bits_rw_t<io_, bitpos::B0, 3>  P000GAIN;
		};
		static inline adpgags0_t<base + 0x1A2>  ADPGAGS0;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad1_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI1;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI1;		///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::GCADI1;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKD;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 5;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN100,			///< AN100 入力
			AN101,			///< AN101 入力
			AN102,			///< AN102 入力
			AN103,			///< AN103 入力
			AN116 = 0x10,	///< AN116 入力
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
			case ANALOG::AN116:
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
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x40> ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
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
		};
		typedef adansa0_t<base + 0x04> ADANSA0_;
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

			bit_rw_t<io_, bitpos::B0>  ANSA100;
		};
		typedef adansa1_t<base + 0x06> ADANSA1_;
		static inline ADANSA1_ ADANSA1;


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
		};
		typedef adansb0_t<base + 0x14> ADANSB0_;
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

			bit_rw_t<io_, bitpos::B0>  ANSB100;
		};
		typedef adansb1_t<base + 0x16> ADANSB1_;
		static inline ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
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

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
		};
		typedef adansc0_t<base + 0xD4> ADANSC0_;
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1（ADANSC1）
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

			bit_rw_t<io_, bitpos::B0>  ANSC100;
		};
		typedef adansc1_t<base + 0xD6> ADANSC1_;
		static inline ADANSC1_ ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSA0_::address, ADANSA1_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B（ADANSB）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSB0_::address, ADANSB1_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C（ADANSC）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSC0_::address, ADANSC1_::address> ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> ADSSTRL_;
		static inline ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static inline ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE1> ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE2> ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE3> ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr2_t<ANALOG, ADSSTR0_::address, ADSSTRL_::address> ADSSTR;


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
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD2 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad2_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD2;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI2;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI2;		///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::GCADI2;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKD;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 12;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN200,			///< AN200 入力
			AN201,			///< AN201 入力
			AN202,			///< AN202 入力
			AN203,			///< AN203 入力
			AN204,			///< AN204 入力
			AN205,			///< AN205 入力
			AN206,			///< AN206 入力
			AN207,			///< AN207 入力
			AN208,			///< AN208 入力
			AN209,			///< AN209 入力
			AN210,			///< AN210 入力
			AN211,			///< AN211 入力
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
					PORT6::PDR.B0 = 0;
					PORT6::PMR.B0 = 0;
				}
				MPC::P60PFS.ASEL = ena;
				break;
			case ANALOG::AN201:
				if(ena) {
					PORT6::PDR.B1 = 0;
					PORT6::PMR.B1 = 0;
				}
				MPC::P61PFS.ASEL = ena;
				break;
			case ANALOG::AN202:
				if(ena) {
					PORT6::PDR.B2 = 0;
					PORT6::PMR.B2 = 0;
				}
				MPC::P62PFS.ASEL = ena;
				break;
			case ANALOG::AN203:
				if(ena) {
					PORT6::PDR.B3 = 0;
					PORT6::PMR.B3 = 0;
				}
				MPC::P63PFS.ASEL = ena;
				break;
			case ANALOG::AN204:
				if(ena) {
					PORT6::PDR.B4 = 0;
					PORT6::PMR.B4 = 0;
				}
				MPC::P64PFS.ASEL = ena;
				break;
			case ANALOG::AN205:
				if(ena) {
					PORT6::PDR.B5 = 0;
					PORT6::PMR.B5 = 0;
				}
				MPC::P65PFS.ASEL = ena;
				break;
			case ANALOG::AN206:
				if(ena) {
					PORT5::PDR.B0 = 0;
					PORT5::PMR.B0 = 0;
				}
				MPC::P50PFS.ASEL = ena;
				break;
			case ANALOG::AN207:
				if(ena) {
					PORT5::PDR.B1 = 0;
					PORT5::PMR.B1 = 0;
				}
				MPC::P51PFS.ASEL = ena;
				break;
			case ANALOG::AN208:
				if(ena) {
					PORT5::PDR.B2 = 0;
					PORT5::PMR.B2 = 0;
				}
				MPC::P52PFS.ASEL = ena;
				break;
			case ANALOG::AN209:
				if(ena) {
					PORT5::PDR.B3 = 0;
					PORT5::PMR.B3 = 0;
				}
				MPC::P53PFS.ASEL = ena;
				break;
			case ANALOG::AN210:
				if(ena) {
					PORT5::PDR.B4 = 0;
					PORT5::PMR.B4 = 0;
				}
				MPC::P54PFS.ASEL = ena;
				break;
			case ANALOG::AN211:
				if(ena) {
					PORT5::PDR.B5 = 0;
					PORT5::PMR.B5 = 0;
				}
				MPC::P55PFS.ASEL = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


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
			@brief  A/D データレジスタ（ADDR）
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
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		typedef adansa0_t<base + 0x04> ADANSA0_;
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
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		typedef adansb0_t<base + 0x14> ADANSB0_;
		static inline ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
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

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		typedef adansc0_t<base + 0xD4> ADANSC0_;
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSA0_::address> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSB0_::address> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSC0_::address> ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ（ADOCDR）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x1C> ADOCDR;


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

			bit_rw_t<io_, bitpos::B1>  OCSAD;
			bit_rw_t<io_, bitpos::B9>  OCSA;
		};
		static inline adexicr_t<base + 0x12>  ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static inline ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE1> ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE2> ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE3> ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE4> ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE5> ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE6> ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE7> ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 8（ADSSTR8）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE8> ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 9（ADSSTR9）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE9> ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 10（ADSSTR10）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEA> ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 11（ADSSTR11）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEB> ADSSTR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1_t<ANALOG, ADSSTR0_::address> ADSSTR;
	};

	typedef s12ad_t <0x00089000> S12AD;
	typedef s12ad1_t<0x00089200> S12AD1;
	typedef s12ad2_t<0x00089400> S12AD2;
}
