#pragma once
//=====================================================================//
/*!	@file
	@brief	RX631/RX63N S12ADa 定義 @n
			  21 channel A/D input 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADa ベース定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_base_t {

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
		struct adstrgr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  ADSTRS;
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

			bit_rw_t<io_, bitpos::B8>      TSS;
			bit_rw_t<io_, bitpos::B9>      OCS;
		};
		typedef adexicr_t<base + 0x12>  ADEXICR_;
		static  ADEXICR_ ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプリングステートレジスタ 01（ADSSTR01）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adsstr01_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   SST1;
		};
		typedef adsstr01_t<base + 0x60>  ADSSTR01_;
		static  ADSSTR01_ ADSSTR01;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプリングステートレジスタ 23（ADSSTR23）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adsstr23_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 8>   SST2;
		};
		typedef adsstr23_t<base + 0x70>  ADSSTR23_;
		static  ADSSTR23_ ADSSTR23;
	};
	template <uint32_t base> typename s12ad_base_t<base>::ADCSR_ s12ad_base_t<base>::ADCSR;
	template <uint32_t base> typename s12ad_base_t<base>::ADADC_ s12ad_base_t<base>::ADADC;
	template <uint32_t base> typename s12ad_base_t<base>::ADCER_ s12ad_base_t<base>::ADCER;
	template <uint32_t base> typename s12ad_base_t<base>::ADSTRGR_ s12ad_base_t<base>::ADSTRGR;
	template <uint32_t base> typename s12ad_base_t<base>::ADEXICR_ s12ad_base_t<base>::ADEXICR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADb 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12ad_t : public s12ad_base_t<base> {

		static constexpr auto PERIPHERAL = per;  				///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI0;	///< スキャン終了割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 21;				///< アナログ入力数
		static constexpr auto PCLK = clock_profile::PCLKB;	///< A/D 変換クロック元


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
			AN016,
			AN017,
			AN018,
			AN019,
			AN020,
			TEMP,	///< 温度センサ
			REF,	///< 内部基準電圧
		};

	
		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
			@param[in]	odr	オーダー型（選択肢）
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//		
		static bool enable(ANALOG an, bool f = true, port_map_order::ORDER odr = port_map_order::ORDER::FIRST)
		{
			bool ret = true;
			if(an >= ANALOG::AN000 && an <= ANALOG::AN007) {
				if(odr != port_map_order::ORDER::FIRST) {
					return false;
				}
			} else if(an >= ANALOG::AN014 && an <= ANALOG::AN020) {
				if(odr != port_map_order::ORDER::FIRST) {
					return false;
				}
			}

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN000:
				if(f) {
					PORT4::PDR.B0 = 0;
					PORT4::PMR.B0 = 0;
				}
				MPC::P40PFS.ASEL = f;
				break;
			case ANALOG::AN001:
				if(f) {
					PORT4::PDR.B1 = 0;
					PORT4::PMR.B1 = 0;
				}
				MPC::P41PFS.ASEL = f;
				break;
			case ANALOG::AN002:
				if(f) {
					PORT4::PDR.B2 = 0;
					PORT4::PMR.B2 = 0;
				}
				MPC::P42PFS.ASEL = f;
				break;
			case ANALOG::AN003:
				if(f) {
					PORT4::PDR.B3 = 0;
					PORT4::PMR.B3 = 0;
				}
				MPC::P43PFS.ASEL = f;
				break;
			case ANALOG::AN004:
				if(f) {
					PORT4::PDR.B4 = 0;
					PORT4::PMR.B4 = 0;
				}
				MPC::P44PFS.ASEL = f;
				break;
			case ANALOG::AN005:
				if(f) {
					PORT4::PDR.B5 = 0;
					PORT4::PMR.B5 = 0;
				}
				MPC::P45PFS.ASEL = f;
				break;
			case ANALOG::AN006:
				if(f) {
					PORT4::PDR.B6 = 0;
					PORT4::PMR.B6 = 0;
				}
				MPC::P46PFS.ASEL = f;
				break;
			case ANALOG::AN007:
				if(f) {
					PORT4::PDR.B7 = 0;
					PORT4::PMR.B7 = 0;
				}
				MPC::P47PFS.ASEL = f;
				break;
			case ANALOG::AN008:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(f) {
						PORTD::PDR.B0 = 0;
						PORTD::PMR.B0 = 0;
					}
					MPC::PD0PFS.ASEL = f;
					break;
				case port_map_order::ORDER::SECOND:
					if(f) {
						PORTE::PDR.B0 = 0;
						PORTE::PMR.B0 = 0;
					}
					MPC::PE0PFS.ASEL = f;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN009:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(f) {
						PORTD::PDR.B1 = 0;
						PORTD::PMR.B1 = 0;
					}
					MPC::PD2PFS.ASEL = f;
					break;
				case port_map_order::ORDER::SECOND:
					if(f) {
						PORTE::PDR.B1 = 0;
						PORTE::PMR.B1 = 0;
					}
					MPC::PE2PFS.ASEL = f;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN010:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(f) {
						PORTD::PDR.B2 = 0;
						PORTD::PMR.B2 = 0;
					}
					MPC::PD2PFS.ASEL = f;
					break;
				case port_map_order::ORDER::SECOND:
					if(f) {
						PORTE::PDR.B2 = 0;
						PORTE::PMR.B2 = 0;
					}
					MPC::PE2PFS.ASEL = f;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN011:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(f) {
						PORTD::PDR.B3 = 0;
						PORTD::PMR.B3 = 0;
					}
					MPC::PD3PFS.ASEL = f;
					break;
				case port_map_order::ORDER::SECOND:
					if(f) {
						PORTE::PDR.B3 = 0;
						PORTE::PMR.B3 = 0;
					}
					MPC::PE3PFS.ASEL = f;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN012:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(f) {
						PORTD::PDR.B4 = 0;
						PORTD::PMR.B4 = 0;
					}
					MPC::PD4PFS.ASEL = f;
					break;
				case port_map_order::ORDER::SECOND:
					if(f) {
						PORTE::PDR.B4 = 0;
						PORTE::PMR.B4 = 0;
					}
					MPC::PE4PFS.ASEL = f;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN013:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(f) {
						PORTD::PDR.B5 = 0;
						PORTD::PMR.B5 = 0;
					}
					MPC::PD5PFS.ASEL = f;
					break;
				case port_map_order::ORDER::SECOND:
					if(f) {
						PORTE::PDR.B5 = 0;
						PORTE::PMR.B5 = 0;
					}
					MPC::PE5PFS.ASEL = f;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN014:
				if(f) {
					PORT9::PDR.B0 = 0;
					PORT9::PMR.B0 = 0;
				}
				MPC::P90PFS.ASEL = f;
				break;
			case ANALOG::AN015:
				if(f) {
					PORT9::PDR.B1 = 0;
					PORT9::PMR.B1 = 0;
				}
				MPC::P91PFS.ASEL = f;
				break;
			case ANALOG::AN016:
				if(f) {
					PORT9::PDR.B2 = 0;
					PORT9::PMR.B2 = 0;
				}
				MPC::P92PFS.ASEL = f;
				break;
			case ANALOG::AN017:
				if(f) {
					PORT9::PDR.B3 = 0;
					PORT9::PMR.B3 = 0;
				}
				MPC::P93PFS.ASEL = f;
				break;
			case ANALOG::AN018:
				if(f) {
					PORT0::PDR.B0 = 0;
					PORT0::PMR.B0 = 0;
				}
				MPC::P00PFS.ASEL = f;
				break;
			case ANALOG::AN019:
				if(f) {
					PORT0::PDR.B1 = 0;
					PORT0::PMR.B1 = 0;
				}
				MPC::P01PFS.ASEL = f;
				break;
			case ANALOG::AN020:
				if(f) {
					PORT0::PDR.B2 = 0;
					PORT0::PMR.B2 = 0;
				}
				MPC::P02PFS.ASEL = f;
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
			@brief  A/D 自己診断データレジスタ（ADRD） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1E> ADRD_;
		static ADRD_ ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）（AIN000 ～ AIN020）
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
			uint16_t operator() (ANALOG an) noexcept {
				if(an == ANALOG::TEMP) {
					return rd16_(base + 0x1A);
				} else if(an == ANALOG::REF) {
					return rd16_(base + 0x1C);
				}
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ (ADANS)(ADANS0, ADANS1)
			@param[in]	ofs		ADANS0 のアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {

			void set(ANALOG an, bool f = true) noexcept {
				auto n = static_cast<uint32_t>(an);
				uint32_t d = 0;
				if(n > 20) {
					return;
				} else if(n >= 16) {
					d = 2;
					n &= 15;
				}
				if(f) {
					wr16_(ofs + d, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs + d, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			// チャネルビット取得
			bool operator() (ANALOG an) const noexcept {
				auto n = static_cast<uint32_t>(an);
				uint32_t d = 0;
				if(n > 20) {
					return 0;
				} else if(n >= 16) {
					d = 2;
					n &= 15;
				}
				return (rd16_(ofs + d) >> n) & 1;
			}
		};
		typedef adans_t<base + 0x04> ADANS_;
		static  ADANS_ ADANS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef adans_t<base + 0x08> ADADS_;
		static  ADADS_ ADADS;
	};
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADDR_  s12ad_t<base, per>::ADDR;
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADANS_ s12ad_t<base, per>::ADANS;
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADADS_ s12ad_t<base, per>::ADADS;

	typedef s12ad_t<0x0008'9000, peripheral::S12AD>  S12AD;
}
