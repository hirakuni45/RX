#pragma once
//=============================================================================//
/*!	@file
	@brief	RX621/RX62N 10 ビット A/D コンバータ（ADa）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
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
		static inline ADDRA_ ADDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ B（ADDRB）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x02> ADDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ C（ADDRC）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x04> ADDRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ D（ADDRD）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x06> ADDRD;


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
		static inline adcsr_t<base + 0x10> ADCSR;


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
		static inline adcr_t<base + 0x11> ADCR;


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
		static inline addpr_t<base + 0x12> ADDPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x13> ADSSTR;


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
		static inline addiagr_t<base + 0x1F> ADDIAGR;
	};


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
			@brief  アナログ入力型 (AD0)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN0,		///< P40 (LFQFP100:  95) (LFQFP144: 141)
			AN1,		///< P41 (LFQFP100:  93) (LFQFP144: 139)
			AN2,		///< P42 (LFQFP100:  92) (LFQFP144: 138)
			AN3,		///< P43 (LFQFP100:  91) (LFQFP144: 137)
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
		static inline ad_utils::addr_t<ANALOG, BASE::ADDRA_::address> ADDR;
	};


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
			@brief  アナログ入力型 (AD1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN4,		///< P44 (LFQFP100:  90) (LFQFP144: 136)
			AN5,		///< P45 (LFQFP100:  89) (LFQFP144: 135)
			AN6,		///< P46 (LFQFP100:  88) (LFQFP144: 134)
			AN7,		///< P47 (LFQFP100:  87) (LFQFP144: 133)
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
		static inline ad_utils::addr_t<ANALOG, BASE::ADDRA_::address> ADDR;
	};

	typedef ad0_t<0x0008'8040> AD0;
	typedef ad1_t<0x0008'8060> AD1;
}
