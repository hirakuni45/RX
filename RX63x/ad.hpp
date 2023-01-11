#pragma once
//=============================================================================//
/*!	@file
	@brief	RX631/RX63N 10 ビット A/D コンバータ（ADb）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t base>
	struct ad_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ n（ADDRn）（n = A ～ H）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20> ADDRA_;
		static ADDRA_ ADDRA;
		typedef rw16_t<base + 0x22> ADDRB_;
		static ADDRB_ ADDRB;
		typedef rw16_t<base + 0x24> ADDRC_;
		static ADDRC_ ADDRC;
		typedef rw16_t<base + 0x26> ADDRD_;
		static ADDRD_ ADDRD;
		typedef rw16_t<base + 0x28> ADDRE_;
		static ADDRE_ ADDRE;
		typedef rw16_t<base + 0x2A> ADDRF_;
		static ADDRF_ ADDRF;
		typedef rw16_t<base + 0x2C> ADDRG_;
		static ADDRG_ ADDRG;
		typedef rw16_t<base + 0x2E> ADDRH_;
		static ADDRH_ ADDRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロール／ステータスレジスタ（ADCSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CH;

			bit_rw_t <io_, bitpos::B5>     ADST;
			bit_rw_t <io_, bitpos::B6>     ADIE;
		};
		typedef adcsr_t<base + 0x10> ADCSR_;
		static ADCSR_ ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロールレジスタ（ADCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> MODE;
			bits_rw_t<io_, bitpos::B2, 2> CKS;

			bits_rw_t<io_, bitpos::B5, 3> TRGS;
		};
		typedef adcr_t<base + 0x11> ADCR_;
		static ADCR_ ADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロールレジスタ 2（ADCR2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 2> EXSEL;
			bit_rw_t <io_, bitpos::B6>    EXOEN;
			bit_rw_t <io_, bitpos::B7>    DPSEL;
		};
		typedef adcr2_t<base + 0x12> ADCR2_;
		static ADCR2_ ADCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x13> ADSSTR_;
		static ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断レジスタ（ADDIAGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiagr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> DIAG;
		};
		typedef addiagr_t<base + 0x1F> ADDIAGR_;
		static ADDIAGR_ ADDIAGR;
	};
	template <uint32_t base> typename ad_base_t<base>::ADDRA_  ad_base_t<base>::ADDRA;
	template <uint32_t base> typename ad_base_t<base>::ADDRB_  ad_base_t<base>::ADDRB;
	template <uint32_t base> typename ad_base_t<base>::ADDRC_  ad_base_t<base>::ADDRC;
	template <uint32_t base> typename ad_base_t<base>::ADDRD_  ad_base_t<base>::ADDRD;
	template <uint32_t base> typename ad_base_t<base>::ADDRE_  ad_base_t<base>::ADDRE;
	template <uint32_t base> typename ad_base_t<base>::ADDRF_  ad_base_t<base>::ADDRF;
	template <uint32_t base> typename ad_base_t<base>::ADDRG_  ad_base_t<base>::ADDRG;
	template <uint32_t base> typename ad_base_t<base>::ADDRH_  ad_base_t<base>::ADDRH;
	template <uint32_t base> typename ad_base_t<base>::ADCSR_  ad_base_t<base>::ADCSR;
	template <uint32_t base> typename ad_base_t<base>::ADCR_  ad_base_t<base>::ADCR;
	template <uint32_t base> typename ad_base_t<base>::ADCR2_  ad_base_t<base>::ADCR2;
	template <uint32_t base> typename ad_base_t<base>::ADDIAGR_  ad_base_t<base>::ADDIAGR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス (ADb)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ad_t : public ad_base_t<base> {

		typedef ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::ADI0;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::NONE;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;	///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;	///< A/D 変換クロック元

		static constexpr uint32_t ANALOG_NUM = 8;			///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN0,
			AN1,
			AN2,
			AN3,
			AN4,
			AN5,
			AN6,
			AN7,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	ena	ポート無効の場合「false」
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//		
		static bool enable(ANALOG an, bool ena = true)
		{
			bool ret = true;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN0:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::AN1:
				if(ena) {
					PORTE::PDR.B3 = 0;
					PORTE::PMR.B3 = 0;
				}
				MPC::PE3PFS.ASEL = ena;
				break;
			case ANALOG::AN2:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::AN3:
				if(ena) {
					PORTE::PDR.B5 = 0;
					PORTE::PMR.B5 = 0;
				}
				MPC::PE5PFS.ASEL = ena;
				break;
			case ANALOG::AN4:
				if(ena) {
					PORTE::PDR.B6 = 0;
					PORTE::PMR.B6 = 0;
				}
				MPC::PE6PFS.ASEL = ena;
				break;
			case ANALOG::AN5:
				if(ena) {
					PORTE::PDR.B7 = 0;
					PORTE::PMR.B7 = 0;
				}
				MPC::PE7PFS.ASEL = ena;
				break;
			case ANALOG::AN6:
				if(ena) {
					PORTD::PDR.B6 = 0;
					PORTD::PMR.B6 = 0;
				}
				MPC::PD6PFS.ASEL = ena;
				break;
			case ANALOG::AN7:
				if(ena) {
					PORTD::PDR.B7 = 0;
					PORTD::PMR.B7 = 0;
				}
				MPC::PD7PFS.ASEL = ena;
				break;
			case ANALOG::ANEX0:
				if(ena) {
					PORTE::PDR.B0 = 0;
					PORTE::PMR.B0 = 0;
				}
				MPC::PE0PFS.ASEL = ena;
				break;
			case ANALOG::ANEX1:
				if(ena) {
					PORTE::PDR.B1 = 0;
					PORTE::PMR.B1 = 0;
				}
				MPC::PE1PFS.ASEL = ena;
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_t<ANALOG, BASE::ADDRA_::address> ADDR_;
		static ADDR_ ADDR;
	};
	template <uint32_t base> typename ad_t<base>::ADDR_ ad_t<base>::ADDR;

	typedef ad_t<0x0008'9800> AD;
}
