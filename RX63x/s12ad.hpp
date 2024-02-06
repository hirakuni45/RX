#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N S12ADa 定義 @n
			  21 channel A/D input 
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
		static inline adcsr_t<base + 0x00>  ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ 0（ADANS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adans0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  ANS0;
		};
		typedef adans0_t<base + 0x04>  ADANS0_;
		static inline ADANS0_ ADANS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D チャネル選択レジスタ 1（ADANS1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adans1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ANS1;
		};
		typedef adans1_t<base + 0x06>  ADANS1_;
		static inline ADANS1_ ADANS1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算モード選択レジスタ 0（ADADS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  ADS0;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算モード選択レジスタ 1（ADADS1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ADS1;
		};
		typedef adads1_t<base + 0x0A>  ADADS1_;
		static inline ADADS1_ ADADS1;


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

			bit_rw_t <io_, bitpos::B5>     ACE;

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
		struct adstrgr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  ADSTRS;
		};
		static inline adstrgr_t<base + 0x10>  ADSTRGR;


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
		static inline adexicr_t<base + 0x12>  ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 温度センサデータレジスタ（ADTSDR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x1A>  ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 内部基準電圧データレジスタ（ADOCDR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x1C>  ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D データレジスタ y（ADDRy）（y = 0 ～ 20）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20>  ADDR0_;
		static inline ADDR0_ ADDR0;
		static inline rw16_t<base + 0x22>  ADDR1;
		static inline rw16_t<base + 0x24>  ADDR2;
		static inline rw16_t<base + 0x26>  ADDR3;
		static inline rw16_t<base + 0x28>  ADDR4;
		static inline rw16_t<base + 0x2A>  ADDR5;
		static inline rw16_t<base + 0x2C>  ADDR6;
		static inline rw16_t<base + 0x2E>  ADDR7;
		static inline rw16_t<base + 0x30>  ADDR8;
		static inline rw16_t<base + 0x32>  ADDR9;
		static inline rw16_t<base + 0x34>  ADDR10;
		static inline rw16_t<base + 0x36>  ADDR11;
		static inline rw16_t<base + 0x38>  ADDR12;
		static inline rw16_t<base + 0x3A>  ADDR13;
		static inline rw16_t<base + 0x3C>  ADDR14;
		static inline rw16_t<base + 0x3E>  ADDR15;
		static inline rw16_t<base + 0x40>  ADDR16;
		static inline rw16_t<base + 0x42>  ADDR17;
		static inline rw16_t<base + 0x44>  ADDR18;
		static inline rw16_t<base + 0x46>  ADDR19;
		static inline rw16_t<base + 0x48>  ADDR20;


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
		static inline adsstr01_t<base + 0x60>  ADSSTR01;


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
		static inline adsstr23_t<base + 0x70>  ADSSTR23;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADa 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12ad_base_t<base> {

		typedef s12ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI0;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::NONE;		///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;		///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;		///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 21;					///< アナログ入力数

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
			@param[in]	ena	ポート無効の場合「false」
			@param[in]	odr	オーダー型（選択肢）
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//		
		static bool enable(ANALOG an, bool ena = true, port_map_order::ORDER odr = port_map_order::ORDER::FIRST)
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
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(ena) {
						PORTD::PDR.B0 = 0;
						PORTD::PMR.B0 = 0;
					}
					MPC::PD0PFS.ASEL = ena;
					break;
				case port_map_order::ORDER::SECOND:
					if(ena) {
						PORTE::PDR.B0 = 0;
						PORTE::PMR.B0 = 0;
					}
					MPC::PE0PFS.ASEL = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN009:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(ena) {
						PORTD::PDR.B1 = 0;
						PORTD::PMR.B1 = 0;
					}
					MPC::PD2PFS.ASEL = ena;
					break;
				case port_map_order::ORDER::SECOND:
					if(ena) {
						PORTE::PDR.B1 = 0;
						PORTE::PMR.B1 = 0;
					}
					MPC::PE2PFS.ASEL = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN010:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(ena) {
						PORTD::PDR.B2 = 0;
						PORTD::PMR.B2 = 0;
					}
					MPC::PD2PFS.ASEL = ena;
					break;
				case port_map_order::ORDER::SECOND:
					if(ena) {
						PORTE::PDR.B2 = 0;
						PORTE::PMR.B2 = 0;
					}
					MPC::PE2PFS.ASEL = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN011:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(ena) {
						PORTD::PDR.B3 = 0;
						PORTD::PMR.B3 = 0;
					}
					MPC::PD3PFS.ASEL = ena;
					break;
				case port_map_order::ORDER::SECOND:
					if(ena) {
						PORTE::PDR.B3 = 0;
						PORTE::PMR.B3 = 0;
					}
					MPC::PE3PFS.ASEL = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN012:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(ena) {
						PORTD::PDR.B4 = 0;
						PORTD::PMR.B4 = 0;
					}
					MPC::PD4PFS.ASEL = ena;
					break;
				case port_map_order::ORDER::SECOND:
					if(ena) {
						PORTE::PDR.B4 = 0;
						PORTE::PMR.B4 = 0;
					}
					MPC::PE4PFS.ASEL = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN013:
				switch(odr) {
				case port_map_order::ORDER::FIRST:
					if(ena) {
						PORTD::PDR.B5 = 0;
						PORTD::PMR.B5 = 0;
					}
					MPC::PD5PFS.ASEL = ena;
					break;
				case port_map_order::ORDER::SECOND:
					if(ena) {
						PORTE::PDR.B5 = 0;
						PORTE::PMR.B5 = 0;
					}
					MPC::PE5PFS.ASEL = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case ANALOG::AN014:
				if(ena) {
					PORT9::PDR.B0 = 0;
					PORT9::PMR.B0 = 0;
				}
				MPC::P90PFS.ASEL = ena;
				break;
			case ANALOG::AN015:
				if(ena) {
					PORT9::PDR.B1 = 0;
					PORT9::PMR.B1 = 0;
				}
				MPC::P91PFS.ASEL = ena;
				break;
			case ANALOG::AN016:
				if(ena) {
					PORT9::PDR.B2 = 0;
					PORT9::PMR.B2 = 0;
				}
				MPC::P92PFS.ASEL = ena;
				break;
			case ANALOG::AN017:
				if(ena) {
					PORT9::PDR.B3 = 0;
					PORT9::PMR.B3 = 0;
				}
				MPC::P93PFS.ASEL = ena;
				break;
			case ANALOG::AN018:
				if(ena) {
					PORT0::PDR.B0 = 0;
					PORT0::PMR.B0 = 0;
				}
				MPC::P00PFS.ASEL = ena;
				break;
			case ANALOG::AN019:
				if(ena) {
					PORT0::PDR.B1 = 0;
					PORT0::PMR.B1 = 0;
				}
				MPC::P01PFS.ASEL = ena;
				break;
			case ANALOG::AN020:
				if(ena) {
					PORT0::PDR.B2 = 0;
					PORT0::PMR.B2 = 0;
				}
				MPC::P02PFS.ASEL = ena;
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
			@brief  A/D データレジスタ（ADDR）（AN000 ～ AN020）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_tr_t<ANALOG, BASE::ADDR0_::address,
			ANALOG::TEMP, BASE::ADTSDR_::address, ANALOG::REF, BASE::ADOCDR_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ (ADANS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, BASE::ADANS0_::address, BASE::ADANS1_::address> ADANS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, BASE::ADADS0_::address, BASE::ADADS1_::address> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(ANALOG an, uint8_t v) noexcept
			{
				if(an == ANALOG::TEMP) {
					BASE::ADSSTR23.SST2 = v;
				} else {
					BASE::ADSSTR01.SST1 = v;
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (ANALOG an) const noexcept
			{
				if(an == ANALOG::TEMP) {
					return BASE::ADSSTR23.SST2();
				} else {
					return BASE::ADSSTR01.SST1();
				}
			}
		};
		static inline adsstr_t ADSSTR;
	};
	typedef s12ad_t<0x0008'9000>  S12AD;
}
