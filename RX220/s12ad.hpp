#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 S12ADb 定義 @n
			  16 channel A/D input 
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
		@brief  S12ADb ベース定義
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
			@brief  A/D データレジスタ 12（ADDR12）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x38> ADDR12_;
		static  ADDR12_ ADDR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 13（ADDR13）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3A> ADDR13_;
		static  ADDR13_ ADDR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 14（ADDR14）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3C> ADDR14_;
		static  ADDR14_ ADDR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 15（ADDR15）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3E> ADDR15_;
		static  ADDR15_ ADDR15;


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

			bits_rw_t<io_, bitpos::B8, 2>  DIAGAL;
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

			bits_rw_t<io_, bitpos::B0, 4>  TRSB;

			bits_rw_t<io_, bitpos::B8, 4>  TRSA;
		};
		typedef adstrgr_t<base + 0x10>  ADSTRGR_;
		static  ADSTRGR_ ADSTRGR;


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

			bit_rw_t<io_, bitpos::B1>      OCSAD;

			bit_rw_t<io_, bitpos::B9>      OCS;
		};
		typedef adexicr_t<base + 0x12>  ADEXICR_;
		static  ADEXICR_ ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 断線検出コントロールレジスタ（ADDISCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiscr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ADNDIS;
		};
		typedef addiscr_t<base + 0x7A>  ADDISCR_;
		static  ADDISCR_ ADDISCR;
	};
	template <uint32_t base> typename s12ad_base_t<base>::ADDR0_ s12ad_base_t<base>::ADDR0;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR1_ s12ad_base_t<base>::ADDR1;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR2_ s12ad_base_t<base>::ADDR2;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR3_ s12ad_base_t<base>::ADDR3;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR4_ s12ad_base_t<base>::ADDR4;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR5_ s12ad_base_t<base>::ADDR5;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR6_ s12ad_base_t<base>::ADDR6;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR7_ s12ad_base_t<base>::ADDR7;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR8_ s12ad_base_t<base>::ADDR8;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR9_ s12ad_base_t<base>::ADDR9;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR10_ s12ad_base_t<base>::ADDR10;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR11_ s12ad_base_t<base>::ADDR11;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR12_ s12ad_base_t<base>::ADDR12;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR13_ s12ad_base_t<base>::ADDR13;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR14_ s12ad_base_t<base>::ADDR14;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR15_ s12ad_base_t<base>::ADDR15;
	template <uint32_t base> typename s12ad_base_t<base>::ADCSR_ s12ad_base_t<base>::ADCSR;
	template <uint32_t base> typename s12ad_base_t<base>::ADADC_ s12ad_base_t<base>::ADADC;
	template <uint32_t base> typename s12ad_base_t<base>::ADCER_ s12ad_base_t<base>::ADCER;
	template <uint32_t base> typename s12ad_base_t<base>::ADSTRGR_ s12ad_base_t<base>::ADSTRGR;
	template <uint32_t base> typename s12ad_base_t<base>::ADEXICR_ s12ad_base_t<base>::ADEXICR;
	template <uint32_t base> typename s12ad_base_t<base>::ADDISCR_ s12ad_base_t<base>::ADDISCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADb 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI0;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::GBADI;		///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1560;				///< A/D 入力 1.56uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 16;	///< アナログ入力数

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
			AN008,
			AN009,
			AN010,
			AN011,
			AN012,
			AN013,
			AN014,
			AN015,
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
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x18> ADDBLDR_;
		static ADDBLDR_ ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ（ADOCDR） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1C> ADOCDR_;
		static ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_r_t<ANALOG, BASE::ADDR0_::address, ANALOG::REF, ADOCDR_::address> ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ（ADRD） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1E> ADRD_;
		static ADRD_ ADRD;


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
			bits_rw_t<io_, bitpos::B0, 16> ANSA;
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
			bits_rw_t<io_, bitpos::B0, 16> ANSB;
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
			bits_rw_t<io_, bitpos::B0, 16> ADS;
		};
		typedef adads_t<base + 0x08> ADADS_;
		static  ADADS_ ADADS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 7、L、O）
			@param[in]	ofs	オフセット
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
		typedef adsstrn_t<base + 0x60>  ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x73>  ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x74>  ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x75>  ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x76>  ADSSTR4_;
		static  ADSSTR4_ ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x77>  ADSSTR5_;
		static  ADSSTR5_ ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x78>  ADSSTR6_;
		static  ADSSTR6_ ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x79>  ADSSTR7_;
		static  ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x61>  ADSSTRL_;
		static  ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0x71>  ADSSTRO_;
		static  ADSSTRO_ ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1il_r_t<ANALOG, ADSSTR0_::address, ADSSTR1_::address, ADSSTRL_::address,
			ANALOG::REF, ADSSTRO_::address> ADSSTR_;
		static  ADSSTR_ ADSSTR;
	};
	template <uint32_t base> typename s12ad_t<base>::ADDR_  s12ad_t<base>::ADDR;
	template <uint32_t base> typename s12ad_t<base>::ADANSA_ s12ad_t<base>::ADANSA;
	template <uint32_t base> typename s12ad_t<base>::ADANSB_ s12ad_t<base>::ADANSB;
	template <uint32_t base> typename s12ad_t<base>::ADADS_ s12ad_t<base>::ADADS;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR0_ s12ad_t<base>::ADSSTR0;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR1_ s12ad_t<base>::ADSSTR1;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR2_ s12ad_t<base>::ADSSTR2;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR3_ s12ad_t<base>::ADSSTR3;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR4_ s12ad_t<base>::ADSSTR4;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR5_ s12ad_t<base>::ADSSTR5;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR6_ s12ad_t<base>::ADSSTR6;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR7_ s12ad_t<base>::ADSSTR7;
	template <uint32_t base> typename s12ad_t<base>::ADSSTRL_ s12ad_t<base>::ADSSTRL;
	template <uint32_t base> typename s12ad_t<base>::ADSSTRO_ s12ad_t<base>::ADSSTRO;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR_ s12ad_t<base>::ADSSTR;

	typedef s12ad_t<0x0008'9000>  S12AD;
}
