#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N S12AD 定義
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
		@brief  S12AD ベース定義
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
			@brief	A/D コントロールレジスタ（ADCSR）
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

			bit_rw_t <io_, bitpos::B0>     EXTRG;
			bit_rw_t <io_, bitpos::B1>     TRGE;
			bits_rw_t<io_, bitpos::B2, 2>  CKS;
			bit_rw_t <io_, bitpos::B4>     ADIE;

			bit_rw_t <io_, bitpos::B6>     ADCS;
			bit_rw_t <io_, bitpos::B7>     ADST;
		};
		typedef adcsr_t<base + 0x00>  ADCSR_;
		static  ADCSR_ ADCSR;


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

			bits_rw_t<io_, bitpos::B0, 8>  ADS;
		};
		typedef adads_t<base + 0x08>  ADADS_;
		static  ADADS_ ADADS;


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

			bits_rw_t<io_, bitpos::B0, 4>  ADSTRS;
		};
		typedef adstrgr_t<base + 0x10>  ADSTRGR_;
		static  ADSTRGR_ ADSTRGR;
	};
	template <uint32_t base> typename s12ad_base_t<base>::ADDR0_ s12ad_base_t<base>::ADDR0;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR1_ s12ad_base_t<base>::ADDR1;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR2_ s12ad_base_t<base>::ADDR2;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR3_ s12ad_base_t<base>::ADDR3;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR4_ s12ad_base_t<base>::ADDR4;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR5_ s12ad_base_t<base>::ADDR5;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR6_ s12ad_base_t<base>::ADDR6;
	template <uint32_t base> typename s12ad_base_t<base>::ADDR7_ s12ad_base_t<base>::ADDR7;
	template <uint32_t base> typename s12ad_base_t<base>::ADCSR_ s12ad_base_t<base>::ADCSR;
	template <uint32_t base> typename s12ad_base_t<base>::ADADS_ s12ad_base_t<base>::ADADS;
	template <uint32_t base> typename s12ad_base_t<base>::ADADC_ s12ad_base_t<base>::ADADC;
	template <uint32_t base> typename s12ad_base_t<base>::ADCER_ s12ad_base_t<base>::ADCER;
	template <uint32_t base> typename s12ad_base_t<base>::ADSTRGR_ s12ad_base_t<base>::ADSTRGR;


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
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI0;	///< A/D 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::NONE;		///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLK;			///< A/D 変換クロック元

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
		static void enable(ANALOG an, bool ena = true)
		{
			switch(an) {
			case ANALOG::AN000:
				if(ena) {
					PORT4::DDR.B0 = 0;
				}
				PORT4::ICR.B0 = ena;
				break;
			case ANALOG::AN001:
				if(ena) {
					PORT4::DDR.B1 = 0;
				}
				PORT4::ICR.B1 = ena;
				break;
			case ANALOG::AN002:
				if(ena) {
					PORT4::DDR.B2 = 0;
				}
				PORT4::ICR.B2 = ena;
				break;
			case ANALOG::AN003:
				if(ena) {
					PORT4::DDR.B3 = 0;
				}
				PORT4::ICR.B3 = ena;
				break;
			case ANALOG::AN004:
				if(ena) {
					PORT4::DDR.B4 = 0;
				}
				PORT4::ICR.B4 = ena;
				break;
			case ANALOG::AN005:
				if(ena) {
					PORT4::DDR.B5 = 0;
				}
				PORT4::ICR.B5 = ena;
				break;
			case ANALOG::AN006:
				if(ena) {
					PORT4::DDR.B6 = 0;
				}
				PORT4::ICR.B6 = ena;
				break;
			case ANALOG::AN007:
				if(ena) {
					PORT4::DDR.B7 = 0;
				}
				PORT4::ICR.B7 = ena;
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
		typedef ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
			@param[in]	ofs		オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  ANS;


			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル選択
				@param[in]	an	アナログ入力型
				@param[in]	ena	チャネルを無効にする場合「false」
			*/
			//-------------------------------------------------------------//
			void set(ANALOG an, bool ena = true) noexcept
			{
				auto n = static_cast<uint32_t>(an);
				if(ena) {
					wr16_(ofs, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル選択オペレーター
				@param[in]	an	アナログ入力型
				@return A/D チャネル選択
			*/
			//-------------------------------------------------------------//
			bool operator() (ANALOG an) const noexcept
			{
				auto n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};
		typedef adans_t<base + 0x04> ADANS_;
		static  ADANS_ ADANS;
	};
	template <uint32_t base> typename s12ad_t<base>::ADDR_  s12ad_t<base>::ADDR;
	template <uint32_t base> typename s12ad_t<base>::ADANS_ s12ad_t<base>::ADANS;

	typedef s12ad_t<0x0008'9000> S12AD;
}
