#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T S12ADB 定義 @n
			48/64 ピン版、144/120/112/100 ピン版で構成が異なる @n
			S12ADB: 48/64 ピン版、アナログ入力８チャネル @n
			S12ADB0, S12ADB1: 144/120/112/100 ピン版、各アナログ入力４チャネル @n
			定義が同居しているので、ピン数により、使い分ける。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
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
		static inline adrd_t<base + 0x1E>  ADRD;


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

			bit_rw_t <io_, bitpos::B4>     DCE;
			bit_rw_t <io_, bitpos::B5>     ACE;

			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGD;
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
//			bits_rw_t<io_, bitpos::B0, 5>  TRSB;

			bits_rw_t<io_, bitpos::B8, 6>  TRSA;
//			bits_rw_t<io_, bitpos::B8, 5>  TRSA;
		};
		static inline adstrgr_t<base + 0x10>  ADSTRGR;


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
		static inline ADSSTR0_ ADSSTR0;
		typedef adsstr_t<base + 0x73>  ADSSTR1_;
		static inline ADSSTR1_ ADSSTR1;
		static inline adsstr_t<base + 0x74>  ADSSTR2;
		static inline adsstr_t<base + 0x75>  ADSSTR3;
		static inline adsstr_t<base + 0x76>  ADSSTR4;
		static inline adsstr_t<base + 0x77>  ADSSTR5;
		static inline adsstr_t<base + 0x78>  ADSSTR6;
		static inline adsstr_t<base + 0x79>  ADSSTR7;


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
		static inline adshcr_t<base + 0x66>  ADSHCR;


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
		static inline adgspcr_t<base + 0x80>  ADGSPCR;


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
		static inline adcmpmd0_t<base + 0xE0>  ADCMPMD0;


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
		static inline adcmpmd1_t<base + 0xE2>  ADCMPMD1;


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
		static inline adcmpnr0_t<base + 0xE4>  ADCMPNR0;


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
		static inline adcmpfr_t<base + 0xE8>  ADCMPFR;


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
		static inline adcmpsel_t<base + 0xEA>  ADCMPSEL;
	};


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
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

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
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


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
		static inline adansa_t<base + 0x04> ADANSA;


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
		static inline adansb_t<base + 0x14> ADANSB;


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
		static inline adads_t<base + 0x08> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1i_t<ANALOG, BASE::ADSSTR0_::address, BASE::ADSSTR1_::address> ADSSTR;
	};


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
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

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
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


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
		static inline adansa_t<base + 0x04> ADANSA;


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
		static inline adansb_t<base + 0x14> ADANSB;


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
		static inline adads_t<base + 0x08> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1i_t<ANALOG, BASE::ADSSTR0::address, BASE::ADSSTR1::address> ADSSTR;


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
		static inline adpg_t<base + 0x8A>  ADPG;


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
		static inline adgspmr_t<base + 0xFC>  ADGSPMR;
	};


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
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 4;			///< アナログ入力数

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
		static inline addr_t ADDR;


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
		static inline adansa_t<base + 0x04> ADANSA;


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
		static inline adansb_t<base + 0x14> ADANSB;


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
		static inline adads_t<base + 0x08> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1i_t<ANALOG, BASE::ADSSTR0::address, BASE::ADSSTR1::address> ADSSTR;


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
		static inline adpg_t<base + 0x8A>  ADPG;
	};

// 64/48 ピン版
#if defined(SIG_RX63T_S)
	typedef s12ad_t<0x0008'9000> S12AD;
#else
	typedef s12ad0_t<0x0008'9000> S12AD0;
	typedef s12ad1_t<0x0008'9100> S12AD1;
#endif
}
