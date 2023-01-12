#pragma once
//=============================================================================//
/*!	@file
	@brief	RX621/RX62N 10 ビット A/D コンバータ（ADa）
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
			@brief  A/D データレジスタ A（ADDRA）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x00> ADDRA_;
		static  ADDRA_ ADDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ B（ADDRB）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x02> ADDRB_;
		static  ADDRB_ ADDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ C（ADDRC）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x04> ADDRC_;
		static  ADDRC_ ADDRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ D（ADDRD）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x06> ADDRD_;
		static  ADDRD_ ADDRD;


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

			bits_rw_t<io_, bitpos::B0, 4>  CH;

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

			bits_rw_t<io_, bitpos::B0, 2>  MODE;
			bits_rw_t<io_, bitpos::B2, 2>  CKS;

			bits_rw_t<io_, bitpos::B5, 3>  TRGS;
		};
		typedef adcr_t<base + 0x11> ADCR_;
		static ADCR_ ADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ADDRn フォーマット選択レジスタ（ADDPR）（n = A ～ D）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addpr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>     DPSEL;
		};
		typedef addpr_t<base + 0x12> ADDPR_;
		static ADDPR_ ADDPR;


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

			bits_rw_t<io_, bitpos::B0, 2>  DIAG;
		};
		typedef addiagr_t<base + 0x1F> ADDIAGR_;
		static ADDIAGR_ ADDIAGR;
	};
	template <uint32_t base> typename ad_base_t<base>::ADDRA_  ad_base_t<base>::ADDRA;
	template <uint32_t base> typename ad_base_t<base>::ADDRB_  ad_base_t<base>::ADDRB;
	template <uint32_t base> typename ad_base_t<base>::ADDRC_  ad_base_t<base>::ADDRC;
	template <uint32_t base> typename ad_base_t<base>::ADDRD_  ad_base_t<base>::ADDRD;
	template <uint32_t base> typename ad_base_t<base>::ADCSR_  ad_base_t<base>::ADCSR;
	template <uint32_t base> typename ad_base_t<base>::ADCR_   ad_base_t<base>::ADCR;
	template <uint32_t base> typename ad_base_t<base>::ADDPR_  ad_base_t<base>::ADDPR;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR_ ad_base_t<base>::ADSSTR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ad0_t : public ad_base_t<base> {

		typedef ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::AD0;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::ADI0;	///< A/D 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::NONE;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;	///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLK;		///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1000;			///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 4;				///< アナログ入力数


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
			switch(an) {
			case ANALOG::AN0:
				if(ena) {
					PORT4::DDR.B0 = 0;
				}
				PORT4::ICR.B0 = ena;
				break;
			case ANALOG::AN1:
				if(ena) {
					PORT4::DDR.B1 = 0;
				}
				PORT4::ICR.B1 = ena;
				break;
			case ANALOG::AN2:
				if(ena) {
					PORT4::DDR.B2 = 0;
				}
				PORT4::ICR.B2 = ena;
				break;
			case ANALOG::AN3:
				if(ena) {
					PORT4::DDR.B3 = 0;
				}
				PORT4::ICR.B3 = ena;
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_t<ANALOG, BASE::ADDRA_::address> ADDR_;
		static  ADDR_ ADDR;
	};
	template <uint32_t base> typename ad0_t<base>::ADDR_ ad0_t<base>::ADDR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ad1_t : public ad_base_t<base> {

		typedef ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::ADI1;	///< A/D 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::NONE;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;	///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLK;		///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1000;			///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 4;				///< アナログ入力数


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
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
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool ena = true) noexcept
		{
			switch(an) {
			case ANALOG::AN4:
				if(ena) {
					PORT4::DDR.B4 = 0;
				}
				PORT4::ICR.B4 = ena;
				break;
			case ANALOG::AN5:
				if(ena) {
					PORT4::DDR.B5 = 0;
				}
				PORT4::ICR.B5 = ena;
				break;
			case ANALOG::AN6:
				if(ena) {
					PORT4::DDR.B6 = 0;
				}
				PORT4::ICR.B6 = ena;
				break;
			case ANALOG::AN7:
				if(ena) {
					PORT4::DDR.B7 = 0;
				}
				PORT4::ICR.B7 = ena;
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_t<ANALOG, BASE::ADDRA_::address> ADDR_;
		static  ADDR_ ADDR;
	};
	template <uint32_t base> typename ad1_t<base>::ADDR_ ad1_t<base>::ADDR;

	typedef ad0_t<0x0008'8040> AD0;
	typedef ad1_t<0x0008'8060> AD1;
}
