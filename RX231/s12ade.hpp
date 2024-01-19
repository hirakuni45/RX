#pragma once
//=========================================================================//
/*!	@file
	@brief	RX231 S12ADE 定義 @n
			  8+16 channel A/D input 
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
			@brief  A/D データレジスタ 18（ADDR18）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x44> ADDR18_;
		static  ADDR18_ ADDR18;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 19（ADDR19）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x46> ADDR19_;
		static  ADDR19_ ADDR19;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 20（ADDR20）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x48> ADDR20_;
		static  ADDR20_ ADDR20;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 21（ADDR21）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x4A> ADDR21_;
		static  ADDR21_ ADDR21;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 22（ADDR22）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x4C> ADDR22_;
		static  ADDR22_ ADDR22;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 23（ADDR23）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x4E> ADDR23_;
		static  ADDR23_ ADDR23;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 24（ADDR24）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x50> ADDR24_;
		static  ADDR24_ ADDR24;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 25（ADDR25）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x52> ADDR25_;
		static  ADDR25_ ADDR25;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 26（ADDR26）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x54> ADDR26_;
		static  ADDR26_ ADDR26;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 27（ADDR27）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x56> ADDR27_;
		static  ADDR27_ ADDR27;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 28（ADDR28）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x58> ADDR28_;
		static  ADDR28_ ADDR28;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 29（ADDR29）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x5A> ADDR29_;
		static  ADDR29_ ADDR29;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 30（ADDR30）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x5C> ADDR30_;
		static  ADDR30_ ADDR30;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 31（ADDR31）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x5E> ADDR31_;
		static  ADDR31_ ADDR31;


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

			bits_rw_t<io_, bitpos::B0, 6>  TRSB;

			bits_rw_t<io_, bitpos::B8, 6>  TRSA;
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

			bit_rw_t<io_, bitpos::B0>      TSSAD;
			bit_rw_t<io_, bitpos::B1>      OCSAD;

			bit_rw_t<io_, bitpos::B8>      TSSA;
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
	template <uint32_t base> typename s12ad_base_t<base>::ADDR16_ s12ad_base_t<base>::ADDR16;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR17_ s12ad_base_t<base>::ADDR17;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR18_ s12ad_base_t<base>::ADDR18;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR19_ s12ad_base_t<base>::ADDR19;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR20_ s12ad_base_t<base>::ADDR20;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR21_ s12ad_base_t<base>::ADDR21;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR22_ s12ad_base_t<base>::ADDR22;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR23_ s12ad_base_t<base>::ADDR23;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR24_ s12ad_base_t<base>::ADDR24;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR25_ s12ad_base_t<base>::ADDR25;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR26_ s12ad_base_t<base>::ADDR26;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR27_ s12ad_base_t<base>::ADDR27;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR28_ s12ad_base_t<base>::ADDR28;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR29_ s12ad_base_t<base>::ADDR29;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR30_ s12ad_base_t<base>::ADDR30;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR31_ s12ad_base_t<base>::ADDR31;
	template <uint32_t base> typename s12ad_base_t<base>::ADCSR_ s12ad_base_t<base>::ADCSR;
	template <uint32_t base> typename s12ad_base_t<base>::ADADC_ s12ad_base_t<base>::ADADC;
	template <uint32_t base> typename s12ad_base_t<base>::ADCER_ s12ad_base_t<base>::ADCER;
	template <uint32_t base> typename s12ad_base_t<base>::ADSTRGR_ s12ad_base_t<base>::ADSTRGR;
	template <uint32_t base> typename s12ad_base_t<base>::ADEXICR_ s12ad_base_t<base>::ADEXICR;
	template <uint32_t base> typename s12ad_base_t<base>::ADDISCR_ s12ad_base_t<base>::ADDISCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADE 定義
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
			@brief  A/D データ 2 重化レジスタ（ADDBLDR） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x18> ADDBLDR_;
		static ADDBLDR_ ADDBLDR;


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
			@brief  A/D 自己診断データレジスタ (ADRD)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1E> ADRD_;
		static  ADRD_ ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_tr_t<ANALOG, BASE::ADDR0_::address, ANALOG::TEMP, ADTSDR_::address, ANALOG::REF, ADOCDR_::address> ADDR_;
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
			@brief	A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 7、L、T, O）
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
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL） @n
					AN016 ～AN031
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xDD>  ADSSTRL_;
		static  ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ T（ADSSTRT） @n
					温度センサ出力（TEMP）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xDE>  ADSSTRT_;
		static  ADSSTRT_ ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO） @n
					内部基準電圧（VREF）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xDF>  ADSSTRO_;
		static  ADSSTRO_ ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE0>  ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE1>  ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE2>  ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE3>  ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE4>  ADSSTR4_;
		static  ADSSTR4_ ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE5>  ADSSTR5_;
		static  ADSSTR5_ ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE6>  ADSSTR6_;
		static  ADSSTR6_ ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrn_t<base + 0xE7>  ADSSTR7_;
		static  ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1il_tr_t<ANALOG, ADSSTR0_::address, ADSSTR1_::address, ADSSTRL_::address,
			ANALOG::TEMP, ADSSTRT_::address, ANALOG::REF, ADSSTRO_::address> ADSSTR_;
		static  ADSSTR_ ADSSTR;
	};
	template <uint32_t base> typename s12ad_t<base>::ADDR_  s12ad_t<base>::ADDR;
	template <uint32_t base> typename s12ad_t<base>::ADANSA_ s12ad_t<base>::ADANSA;
	template <uint32_t base> typename s12ad_t<base>::ADANSB_ s12ad_t<base>::ADANSB;
	template <uint32_t base> typename s12ad_t<base>::ADADS_ s12ad_t<base>::ADADS;
	template <uint32_t base> typename s12ad_t<base>::ADSSTRL_ s12ad_t<base>::ADSSTRL;
	template <uint32_t base> typename s12ad_t<base>::ADSSTRT_ s12ad_t<base>::ADSSTRT;
	template <uint32_t base> typename s12ad_t<base>::ADSSTRO_ s12ad_t<base>::ADSSTRO;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR0_ s12ad_t<base>::ADSSTR0;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR1_ s12ad_t<base>::ADSSTR1;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR2_ s12ad_t<base>::ADSSTR2;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR3_ s12ad_t<base>::ADSSTR3;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR4_ s12ad_t<base>::ADSSTR4;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR5_ s12ad_t<base>::ADSSTR5;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR6_ s12ad_t<base>::ADSSTR6;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR7_ s12ad_t<base>::ADSSTR7;
	template <uint32_t base> typename s12ad_t<base>::ADSSTR_ s12ad_t<base>::ADSSTR;

	typedef s12ad_t<0x0008'9000>  S12AD;
}
