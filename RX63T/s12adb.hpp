#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T S12ADB 定義 @n
			48/64 ピン版、144/120/112/100 ピン版で構成が異なる @n
			S12ADB: 48/64 ピン版、アナログ入力８チャネル @n
			S12ADB0, S12ADB1: 144/120/112/100 ピン版、各アナログ入力４チャネル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADB ベース定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 自己診断データレジスタ（ADRD）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adrd_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12> AD;

			bits_rw_t<io_, bitpos::B14, 2> DIAGST;
		};
		typedef adrd_t<base + 0x1E>  ADRD_;
		static ADRD_ ADRD;


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
		static ADCSR_ ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ A（ADANSA）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> ANSA;

			bit_rw_t <io_, bitpos::B8>    PG000EN;
			bit_rw_t <io_, bitpos::B9>    PG001EN;
			bit_rw_t <io_, bitpos::B10>   PG002EN;

			bit_rw_t <io_, bitpos::B12>   PG000SEL;
			bit_rw_t <io_, bitpos::B13>   PG001SEL;
			bit_rw_t <io_, bitpos::B14>   PG002SEL;
		};
		typedef adansa_t<base + 0x04>  ADANSA_;
		static ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ B（ADANSB）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> ANSB;
		};
		typedef adansb_t<base + 0x14>  ADANSB_;
		static ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算モード選択レジスタ（ADADS）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  ADS;
		};
		typedef adads_t<base + 0x08>  ADADS_;
		static ADADS_ ADADS;


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
		};
		typedef adadc_t<base + 0x0C>  ADADC_;
		static ADADC_ ADADC;


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

			bit_rw_t <io_, bitpos::B4>     DCE;
			bit_rw_t <io_, bitpos::B5>     ACE;

			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;

			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		typedef adcer_t<base + 0x0E>  ADCER_;
		static ADCER_ ADCER;


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
//			bits_rw_t<io_, bitpos::B0, 5>  TRSB;

			bits_rw_t<io_, bitpos::B8, 6>  TRSA;
//			bits_rw_t<io_, bitpos::B8, 5>  TRSA;
		};
		typedef adstrgr_t<base + 0x10>  ADSTRGR_;
		static ADSTRGR_ ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 7）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adsstr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SST;
		};
		typedef adsstr_t<base + 0x60>  ADSSTR0_;
		static ADSSTR0_ ADSSTR0;
		typedef adsstr_t<base + 0x73>  ADSSTR1_;
		static ADSSTR1_ ADSSTR1;
		typedef adsstr_t<base + 0x74>  ADSSTR2_;
		static ADSSTR2_ ADSSTR2;
		typedef adsstr_t<base + 0x75>  ADSSTR3_;
		static ADSSTR3_ ADSSTR3;
		typedef adsstr_t<base + 0x76>  ADSSTR4_;
		static ADSSTR4_ ADSSTR4;
		typedef adsstr_t<base + 0x77>  ADSSTR5_;
		static ADSSTR5_ ADSSTR5;
		typedef adsstr_t<base + 0x78>  ADSSTR6_;
		static ADSSTR6_ ADSSTR6;
		typedef adsstr_t<base + 0x79>  ADSSTR7_;
		static ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	サンプル & ホールド回路コントロールレジスタ（ADSHCR）
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
		static ADSHCR_ ADSHCR;


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

			bit_rw_t<io_, bitpos::B0>  PGS;
			bit_rw_t<io_, bitpos::B1>  GBRSCN;

			bit_rw_t<io_, bitpos::B15> GBRP;
		};
		typedef adgspcr_t<base + 0x80>  ADGSPCR_;
		static ADGSPCR_ ADGSPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	コンパレータ動作モード選択レジスタ 0（ADCMPMD0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpmd0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CEN000;
			bits_rw_t<io_, bitpos::B2, 2>  CEN001;
			bits_rw_t<io_, bitpos::B4, 2>  CEN002;
		};
		typedef adcmpmd0_t<base + 0xE0>  ADCMPMD0_;
		static ADCMPMD0_ ADCMPMD0;


		//-----------------------------------------------------------------//
		/*!
			@brief	コンパレータ動作モード選択レジスタ 1（ADCMPMD1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpmd1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  REFL;

			bits_rw_t<io_, bitpos::B4, 3>  REFH;

			bit_rw_t <io_, bitpos::B8>     CSEL0;
			bit_rw_t <io_, bitpos::B9>     VSELH0;
			bit_rw_t <io_, bitpos::B10>    VSELL0;
		};
		typedef adcmpmd1_t<base + 0xE2>  ADCMPMD1_;
		static ADCMPMD1_ ADCMPMD1;


		//-----------------------------------------------------------------//
		/*!
			@brief	コンパレータフィルタモードレジスタ 0（ADCMPNR0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpnr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  C000NR;
			bits_rw_t<io_, bitpos::B4, 4>  C001NR;
			bits_rw_t<io_, bitpos::B8, 4>  C002NR;
		};
		typedef adcmpnr0_t<base + 0xE4>  ADCMPNR0_;
		static ADCMPNR0_ ADCMPNR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	コンパレータ検出フラグレジスタ（ADCMPFR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpfr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  C000FLAG;
			bit_rw_t<io_, bitpos::B1>  C001FLAG;
			bit_rw_t<io_, bitpos::B2>  C002FLAG;
		};
		typedef adcmpfr_t<base + 0xE8>  ADCMPFR_;
		static ADCMPFR_ ADCMPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	コンパレータ割り込み選択レジスタ（ADCMPSEL）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsel_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  IE000;
			bit_rw_t<io_, bitpos::B1>  IE001;
			bit_rw_t<io_, bitpos::B2>  IE002;

			bit_rw_t<io_, bitpos::B8>  POERQ000;
			bit_rw_t<io_, bitpos::B9>  POERQ001;
			bit_rw_t<io_, bitpos::B10> POERQ002;
		};
		typedef adcmpsel_t<base + 0xEA>  ADCMPSEL_;
		static ADCMPSEL_ ADCMPSEL;
	};
	template <uint32_t base> typename s12ad_base_t<base>::ADRD_ s12ad_base_t<base>::ADRD;
	template <uint32_t base> typename s12ad_base_t<base>::ADCSR_ s12ad_base_t<base>::ADCSR;
	template <uint32_t base> typename s12ad_base_t<base>::ADANSA_ s12ad_base_t<base>::ADANSA;
	template <uint32_t base> typename s12ad_base_t<base>::ADANSB_ s12ad_base_t<base>::ADANSB;
	template <uint32_t base> typename s12ad_base_t<base>::ADADS_ s12ad_base_t<base>::ADADS;
	template <uint32_t base> typename s12ad_base_t<base>::ADADC_ s12ad_base_t<base>::ADADC;
	template <uint32_t base> typename s12ad_base_t<base>::ADCER_ s12ad_base_t<base>::ADCER;
	template <uint32_t base> typename s12ad_base_t<base>::ADSTRGR_ s12ad_base_t<base>::ADSTRGR;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR0_ s12ad_base_t<base>::ADSSTR0;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR1_ s12ad_base_t<base>::ADSSTR1;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR2_ s12ad_base_t<base>::ADSSTR2;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR3_ s12ad_base_t<base>::ADSSTR3;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR4_ s12ad_base_t<base>::ADSSTR4;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR5_ s12ad_base_t<base>::ADSSTR5;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR6_ s12ad_base_t<base>::ADSSTR6;
	template <uint32_t base> typename s12ad_base_t<base>::ADSSTR7_ s12ad_base_t<base>::ADSSTR7;
	template <uint32_t base> typename s12ad_base_t<base>::ADSHCR_ s12ad_base_t<base>::ADSHCR;
	template <uint32_t base> typename s12ad_base_t<base>::ADGSPCR_ s12ad_base_t<base>::ADGSPCR;
	template <uint32_t base> typename s12ad_base_t<base>::ADCMPMD0_ s12ad_base_t<base>::ADCMPMD0;
	template <uint32_t base> typename s12ad_base_t<base>::ADCMPMD1_ s12ad_base_t<base>::ADCMPMD1;
	template <uint32_t base> typename s12ad_base_t<base>::ADCMPNR0_ s12ad_base_t<base>::ADCMPNR0;
	template <uint32_t base> typename s12ad_base_t<base>::ADCMPFR_ s12ad_base_t<base>::ADCMPFR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADB 定義（８チャネル）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12adb_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = per;  			///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI;	///< スキャン終了割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 8;			///< アナログ入力数
		static constexpr auto PCLK = clock_profile::PCLKC;	///< A/D 変換クロック元

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
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::AIN000:  // P40
				MPC::P40PFS.ASEL = f;
				break;
			case ANALOG::AIN001:  // P41
				MPC::P41PFS.ASEL = f;
				break;
			case ANALOG::AIN002:  // P42
				MPC::P42PFS.ASEL = f;
				break;
			case ANALOG::AIN003:  // P43
				MPC::P43PFS.ASEL = f;
				break;
			case ANALOG::AIN004:  // P44
				MPC::P44PFS.ASEL = f;
				break;
			case ANALOG::AIN005:  // P45
				MPC::P45PFS.ASEL = f;
				break;
			case ANALOG::AIN006:  // P46
				MPC::P46PFS.ASEL = f;
				break;
			case ANALOG::AIN007:  // P47
				MPC::P47PFS.ASEL = f;
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
		struct addr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (ANALOG an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ (ADANS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) {
				auto n = static_cast<uint32_t>(an);
				if(f) {
					wr16_(ofs, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			// チャネルビット取得
			bool operator() (ANALOG an) const {
				auto n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;
		typedef adans_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {

			void set(ANALOG an, uint8_t v) noexcept
			{
				switch(an) {
				case ANALOG::AIN000: BASE::ADSSTR0 = v; break;
				case ANALOG::AIN001: BASE::ADSSTR1 = v; break;
				case ANALOG::AIN002: BASE::ADSSTR2 = v; break;
				case ANALOG::AIN003: BASE::ADSSTR3 = v; break;
				case ANALOG::AIN004: BASE::ADSSTR4 = v; break;
				case ANALOG::AIN005: BASE::ADSSTR5 = v; break;
				case ANALOG::AIN006: BASE::ADSSTR6 = v; break;
				case ANALOG::AIN007: BASE::ADSSTR7 = v; break;
				default:
					break;
				}
			}

			uint8_t get(ANALOG an) noexcept
			{
				switch(an) {
				case ANALOG::AIN000: return BASE::ADSSTR0();
				case ANALOG::AIN001: return BASE::ADSSTR1();
				case ANALOG::AIN002: return BASE::ADSSTR2();
				case ANALOG::AIN003: return BASE::ADSSTR3();
				case ANALOG::AIN004: return BASE::ADSSTR4();
				case ANALOG::AIN005: return BASE::ADSSTR5();
				case ANALOG::AIN006: return BASE::ADSSTR6();
				case ANALOG::AIN007: return BASE::ADSSTR7();
				default:
					break;
				}
				return 0;
			}

			uint8_t operator () (ANALOG an) noexcept { return get(an); }
		};
		typedef adsstr_t ADSSTR_;
		static ADSSTR_ ADSSTR;
	};
	template <uint32_t base, peripheral per> typename s12adb_t<base, per>::ADDR_  s12adb_t<base, per>::ADDR;
	template <uint32_t base, peripheral per> typename s12adb_t<base, per>::ADANSA_ s12adb_t<base, per>::ADANSA;
	template <uint32_t base, peripheral per> typename s12adb_t<base, per>::ADANSB_ s12adb_t<base, per>::ADANSB;
	template <uint32_t base, peripheral per> typename s12adb_t<base, per>::ADSSTR_ s12adb_t<base, per>::ADSSTR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADB0 定義（４チャネル）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	adi		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12adb0_t : public s12ad_base_t<base> {

		static constexpr auto PERIPHERAL = per;  	///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI;	///< スキャン終了割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 4;	///< アナログ入力数
		static constexpr auto PCLK = clock_profile::PCLKC;	///< A/D 変換クロック元

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
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::AIN000:  // P40
				MPC::P40PFS.ASEL = f;
				break;
			case ANALOG::AIN001:  // P41
				MPC::P41PFS.ASEL = f;
				break;
			case ANALOG::AIN002:  // P42
				MPC::P42PFS.ASEL = f;
				break;
			case ANALOG::AIN003:  // P43
				MPC::P43PFS.ASEL = f;
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
		struct addr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (ANALOG an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ (ADANS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) {
				auto n = static_cast<uint32_t>(an);
				if(f) {
					wr16_(ofs, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			// チャネルビット取得
			bool operator() (ANALOG an) const {
				auto n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;
		typedef adans_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプレジスタ（ADPG）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  PG0GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  PG1GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  PG2GAIN;
		};
		typedef adpg_t<base + 0x8A>  ADPG_;
		static ADPG_ ADPG;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループスキャン優先モードレジスタ（ADGSPMR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgspmr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  PG0GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  PG1GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  PG2GAIN;
		};
		typedef adgspmr_t<base + 0xFC>  ADGSPMR_;
		static ADGSPMR_ ADGSPMR;
	};
	template <uint32_t base, peripheral per> typename s12adb0_t<base, per>::ADDR_  s12adb0_t<base, per>::ADDR;
	template <uint32_t base, peripheral per> typename s12adb0_t<base, per>::ADANSA_ s12adb0_t<base, per>::ADANSA;
	template <uint32_t base, peripheral per> typename s12adb0_t<base, per>::ADANSB_ s12adb0_t<base, per>::ADANSB;
	template <uint32_t base, peripheral per> typename s12adb0_t<base, per>::ADGSPMR_ s12adb0_t<base, per>::ADGSPMR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADB1 定義（４チャネル）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	adi		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12adb1_t : public s12ad_base_t<base> {

		static constexpr auto PERIPHERAL = per;  			///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI1;	///< スキャン終了割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 4;			///< アナログ入力数
		static constexpr auto PCLK = clock_profile::PCLKC;	///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 400;		///< 変換時間[ns]（0.4us）


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
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::AIN100:  // P44
				MPC::P44PFS.ASEL = f;
				break;
			case ANALOG::AIN101:  // P45
				MPC::P45PFS.ASEL = f;
				break;
			case ANALOG::AIN102:  // P46
				MPC::P46PFS.ASEL = f;
				break;
			case ANALOG::AIN103:  // P47
				MPC::P47PFS.ASEL = f;
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
		struct addr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (ANALOG an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ (ADANS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) {
				auto n = static_cast<uint32_t>(an);
				if(f) {
					wr16_(ofs, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			// チャネルビット取得
			bool operator() (ANALOG an) const {
				auto n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;
		typedef adans_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプレジスタ（ADPG）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  PG0GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  PG1GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  PG2GAIN;
		};
		typedef adpg_t<base + 0x8A>  ADPG_;
		static ADPG_ ADPG;
	};
	template <uint32_t base, peripheral per> typename s12adb1_t<base, per>::ADDR_  s12adb1_t<base, per>::ADDR;
	template <uint32_t base, peripheral per> typename s12adb1_t<base, per>::ADANSA_ s12adb1_t<base, per>::ADANSA;
	template <uint32_t base, peripheral per> typename s12adb1_t<base, per>::ADANSB_ s12adb1_t<base, per>::ADANSB;
	template <uint32_t base, peripheral per> typename s12adb1_t<base, per>::ADPG_ s12adb1_t<base, per>::ADPG;


	typedef s12adb_t<0x0008'9000, peripheral::S12ADB> S12ADB;
	typedef s12adb0_t<0x0008'9000, peripheral::S12ADB0> S12ADB0;
	typedef s12adb1_t<0x0008'9100, peripheral::S12ADB1> S12ADB1;
}
