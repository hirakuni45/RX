#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T S12ADB 定義 @n
			48/64 ピン版、144/120/112/100 ピン版で構成が異なる @n
			S12ADB: 48/64 ピン版、アナログ入力８チャネル @n
			S12ADB0, S12ADB1: 144/120/112/100 ピン版、各アナログ入力４チャネル @n
			定義が同居しているので、ピン数により、使い分ける。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

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
	template <uint32_t base> typename s12ad_base_t<base>::ADDR0_ s12ad_base_t<base>::ADDR0;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR1_ s12ad_base_t<base>::ADDR1;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR2_ s12ad_base_t<base>::ADDR2;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR3_ s12ad_base_t<base>::ADDR3;
	template <uint32_t base> typename s12ad_base_t<base>::ADRD_ s12ad_base_t<base>::ADRD;
	template <uint32_t base> typename s12ad_base_t<base>::ADCSR_ s12ad_base_t<base>::ADCSR;
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
		@brief  S12AD(B) 定義（８チャネル、１ユニット、64/48 ピン版）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI;		///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKD;			///< A/D 変換クロック元

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

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
			MPC::PWPR.B0WI  = 0;
			MPC::PWPR.PFSWE = 1;

			switch(an) {
			case ANALOG::AN000:  // P40
				if(ena) {
					PORT4::PDR.B0 = 0;
					PORT4::PMR.B0 = 0;
				}
				MPC::P40PFS.ASEL = ena;
				break;
			case ANALOG::AN001:  // P41
				if(ena) {
					PORT4::PDR.B1 = 0;
					PORT4::PMR.B1 = 0;
				}
				MPC::P41PFS.ASEL = ena;
				break;
			case ANALOG::AN002:  // P42
				if(ena) {
					PORT4::PDR.B2 = 0;
					PORT4::PMR.B2 = 0;
				}
				MPC::P42PFS.ASEL = ena;
				break;
			case ANALOG::AN003:  // P43
				if(ena) {
					PORT4::PDR.B3 = 0;
					PORT4::PMR.B3 = 0;
				}
				MPC::P43PFS.ASEL = ena;
				break;
			case ANALOG::AN004:  // P44
				if(ena) {
					PORT4::PDR.B4 = 0;
					PORT4::PMR.B4 = 0;
				}
				MPC::P44PFS.ASEL = ena;
				break;
			case ANALOG::AN005:  // P45
				if(ena) {
					PORT4::PDR.B5 = 0;
					PORT4::PMR.B5 = 0;
				}
				MPC::P45PFS.ASEL = ena;
				break;
			case ANALOG::AN006:  // P46
				if(ena) {
					PORT4::PDR.B6 = 0;
					PORT4::PMR.B6 = 0;
				}
				MPC::P46PFS.ASEL = ena;
				break;
			case ANALOG::AN007:  // P47
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
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
			@param[in] regadr	レジスタアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adansa_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 8> ANSA;
		};
		typedef adansa_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B (ADANSB)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adansb_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 8> ANSB;
		};
		typedef adansb_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
			@param[in] regadr	レジスタアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adads_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 8> ADS;
		};
		typedef adads_t<base + 0x08> ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1i_t<ANALOG, BASE::ADSSTR0_::address, BASE::ADSSTR1_::address> ADSSTR_;
		static ADSSTR_ ADSSTR;
	};
	template <uint32_t base> typename s12ad_t<base>::ADDR_  s12ad_t<base>::ADDR;
	template <uint32_t base> typename s12ad_t<base>::ADANSA_ s12ad_t<base>::ADANSA;
	template <uint32_t base> typename s12ad_t<base>::ADANSB_ s12ad_t<base>::ADANSB;
	template <uint32_t base> typename s12ad_t<base>::ADADS_ s12ad_t<base>::ADADS;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR_ s12ad_t<base>::ADSSTR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD(B)0 定義（４チャネル、100 ピン以上２ユニット版）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad0_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI;		///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKD;			///< A/D 変換クロック元

		static constexpr uint32_t ANALOG_NUM = 4;	///< アナログ入力数

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
			case ANALOG::AN000:  // P40
				if(ena) {
					PORT4::PDR.B0 = 0;
					PORT4::PMR.B0 = 0;
				}
				MPC::P40PFS.ASEL = ena;
				break;
			case ANALOG::AN001:  // P41
				if(ena) {
					PORT4::PDR.B1 = 0;
					PORT4::PMR.B1 = 0;
				}
				MPC::P41PFS.ASEL = ena;
				break;
			case ANALOG::AN002:  // P42
				if(ena) {
					PORT4::PDR.B2 = 0;
					PORT4::PMR.B2 = 0;
				}
				MPC::P42PFS.ASEL = ena;
				break;
			case ANALOG::AN003:  // P43
				if(ena) {
					PORT4::PDR.B3 = 0;
					PORT4::PMR.B3 = 0;
				}
				MPC::P43PFS.ASEL = ena;
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
		typedef ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
			@param[in] regadr	レジスタアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adansa_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 4> ANSA;

			bit_rw_t<io_, bitpos::B8>   PG000EN;
			bit_rw_t<io_, bitpos::B9>   PG001EN;
			bit_rw_t<io_, bitpos::B10>  PG002EN;

			bit_rw_t<io_, bitpos::B12>  PG000SEL;
			bit_rw_t<io_, bitpos::B13>  PG001SEL;
			bit_rw_t<io_, bitpos::B14>  PG002SEL;
		};
		typedef adansa_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B (ADANSB)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adansb_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 4> ANSB;
		};
		typedef adansb_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
			@param[in] regadr	レジスタアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adads_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 4> ADS;
		};
		typedef adads_t<base + 0x08> ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1i_t<ANALOG, BASE::ADSSTR0::address, BASE::ADSSTR1::address> ADSSTR_;
		static ADSSTR_ ADSSTR;


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
	template <uint32_t base> typename s12ad0_t<base>::ADDR_  s12ad0_t<base>::ADDR;
	template <uint32_t base> typename s12ad0_t<base>::ADANSA_ s12ad0_t<base>::ADANSA;
	template <uint32_t base> typename s12ad0_t<base>::ADANSB_ s12ad0_t<base>::ADANSB;
	template <uint32_t base> typename s12ad0_t<base>::ADADS_ s12ad0_t<base>::ADADS;
	template <uint32_t base> typename s12ad0_t<base>::ADSSTR_ s12ad0_t<base>::ADSSTR;
	template <uint32_t base> typename s12ad0_t<base>::ADPG_ s12ad0_t<base>::ADPG;
	template <uint32_t base> typename s12ad0_t<base>::ADGSPMR_ s12ad0_t<base>::ADGSPMR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD(B)1 定義（４チャネル、100 ピン以上２ユニット版）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad1_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI1;		///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI1;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKD;			///< A/D 変換クロック元

		static constexpr uint32_t ANALOG_NUM = 4;			///< アナログ入力数

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


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
			@param[in] regadr	レジスタアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adansa_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 4> ANSA;

			bit_rw_t<io_, bitpos::B8>   PG000EN;
			bit_rw_t<io_, bitpos::B9>   PG001EN;
			bit_rw_t<io_, bitpos::B10>  PG002EN;

			bit_rw_t<io_, bitpos::B12>  PG000SEL;
			bit_rw_t<io_, bitpos::B13>  PG001SEL;
			bit_rw_t<io_, bitpos::B14>  PG002SEL;
		};
		typedef adansa_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B (ADANSB)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adansb_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 4> ANSB;
		};
		typedef adansb_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
			@param[in] regadr	レジスタアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t regadr>
		struct adads_t : public ad_utils::adans1_t<ANALOG, regadr> {
			typedef ad_utils::adans1_t<ANALOG, regadr> adans1_;
			using adans1_::operator ();

			typedef rw16_t<regadr> io_;
			bits_rw_t<io_, bitpos::B0, 4> ADS;
		};
		typedef adads_t<base + 0x08> ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1i_t<ANALOG, BASE::ADSSTR0::address, BASE::ADSSTR1::address> ADSSTR_;
		static ADSSTR_ ADSSTR;


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
	template <uint32_t base> typename s12ad1_t<base>::ADDR_  s12ad1_t<base>::ADDR;
	template <uint32_t base> typename s12ad1_t<base>::ADANSA_ s12ad1_t<base>::ADANSA;
	template <uint32_t base> typename s12ad1_t<base>::ADANSB_ s12ad1_t<base>::ADANSB;
	template <uint32_t base> typename s12ad1_t<base>::ADADS_ s12ad1_t<base>::ADADS;
	template <uint32_t base> typename s12ad1_t<base>::ADSSTR_ s12ad1_t<base>::ADSSTR;
	template <uint32_t base> typename s12ad1_t<base>::ADPG_ s12ad1_t<base>::ADPG;

	typedef s12ad_t<0x0008'9000> S12AD;
	typedef s12ad0_t<0x0008'9000> S12AD0;
	typedef s12ad1_t<0x0008'9100> S12AD1;
}
