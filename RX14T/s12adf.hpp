#pragma once
//=========================================================================//
/*!	@file
	@brief	12-Bit A/D Converter / 12 ビット A/D コンバータ (RX14T)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADHF base class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adf_base_t {

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
		};
		static inline adhvrefcnt_t<base + 0x8A>  ADHVREFCNT;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12adf_base_t<base> {

		typedef s12adf_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;	///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::GCADI;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 500;				///< A/D 入力 0.5uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型 (S12AD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,		///< P40 (LFQFP48: 44) (LQFP52: 47) (LFQFP64: 56)
			AN001,		///< P41 (LFQFP48: 43) (LQFP52: 46) (LFQFP64: 55)
			AN002,		///< P42 (LFQFP48: 42) (LQFP52: 45) (LFQFP64: 54)
			AN003,		///< P43 (LFQFP48: 41) (LQFP52: 44) (LFQFP64: 53)
			AN004,		///< P44 (LFQFP48: 40) (LQFP52: 43) (LFQFP64: 52)
			AN005,		///< P45 (LFQFP48: 39) (LQFP52: 42) (LFQFP64: 51)
			AN006,		///< P46 (LFQFP48: 38) (LQFP52: 41) (LFQFP64: 50)
			AN007,		///< P47 (LFQFP48: 37) (LQFP52: 40) (LFQFP64: 49)
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
			@brief  A/D データレジスタ (ADDR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


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
		static inline ADANSA0_ ADANSA0;


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
		static inline ADANSB0_ ADANSB0;


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
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSA0_::address>  ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSB0_::address>  ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSC0_::address>  ADANSC;


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
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADADS0_::address>  ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1_t<ANALOG, BASE::ADSSTR0_::address> ADSSTR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad1_t : public s12adf_base_t<base> {

		typedef s12adf_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI1;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI1;		///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::GCADI1;		///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 500;				///< A/D 入力 0.9uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型 (S12AD1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN102,		///< P11 (LFQFP48: 47) (LQFP52: 50) (LFQFP64: 61)
			AN103,		///< P10 (LFQFP48: 48) (LQFP52: 51) (LFQFP64: 62)
			AN104,		///< P12 (LFQFP48: --) (LQFP52: --) (LFQFP64: 60)
			AN105,		///< P13 (LFQFP48: 46) (LQFP52: 49) (LFQFP64: 59)
			AN106,		///< P14 (LFQFP48: 45) (LQFP52: 48) (LFQFP64: 58)
			AN107,		///< P15 (LFQFP48: --) (LQFP52: --) (LFQFP64: 57)
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
			case ANALOG::AN102:
				if(ena) {
					PORT1::PDR.B1 = 0;
					PORT1::PMR.B1 = 0;
				}
				MPC::P11PFS.ASEL = ena;
				break;
			case ANALOG::AN103:
				if(ena) {
					PORT1::PDR.B0 = 0;
					PORT1::PMR.B0 = 0;
				}
				MPC::P10PFS.ASEL = ena;
				break;
			case ANALOG::AN104:
				if(ena) {
					PORT1::PDR.B2 = 0;
					PORT1::PMR.B2 = 0;
				}
				MPC::P12PFS.ASEL = ena;
				break;
			case ANALOG::AN105:
				if(ena) {
					PORT1::PDR.B3 = 0;
					PORT1::PMR.B3 = 0;
				}
				MPC::P13PFS.ASEL = ena;
				break;
			case ANALOG::AN106:
				if(ena) {
					PORT1::PDR.B4 = 0;
					PORT1::PMR.B4 = 0;
				}
				MPC::P14PFS.ASEL = ena;
				break;
			case ANALOG::AN107:
				if(ena) {
					PORT1::PDR.B5 = 0;
					PORT1::PMR.B5 = 0;
				}
				MPC::P15PFS.ASEL = ena;
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
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


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
		static inline ADANSA0_ ADANSA0;


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
		static inline ADANSB0_ ADANSB0;


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
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSA0_::address>  ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSB0_::address>  ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSC0_::address>  ADANSC;


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
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADADS0_::address>  ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換拡張入力コントロールレジスタ (ADEXICR)
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
		};
		static inline adexicr_t<base + 0x12>  ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1_t<ANALOG, BASE::ADSSTR0_::address> ADSSTR;
	};

	typedef s12ad_t <0x0008'9000> S12AD;
	typedef s12ad1_t<0x0008'9200> S12AD1;
}
