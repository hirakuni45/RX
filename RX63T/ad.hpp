#pragma once
//=============================================================================//
/*!	@file
	@brief	RX63T 10 ビット A/D コンバータ（ADa）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
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
			@brief  A/D データレジスタ n（ADDRn）（n = A ～ T）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20> ADDRA_;
		static inline ADDRA_ ADDRA;
		static inline rw16_t<base + 0x22> ADDRB;
		static inline rw16_t<base + 0x24> ADDRC;
		static inline rw16_t<base + 0x26> ADDRD;
		static inline rw16_t<base + 0x28> ADDRE;
		static inline rw16_t<base + 0x2A> ADDRF;
		static inline rw16_t<base + 0x2C> ADDRG;
		static inline rw16_t<base + 0x2E> ADDRH;
		static inline rw16_t<base + 0x30> ADDRI;
		static inline rw16_t<base + 0x32> ADDRJ;
		static inline rw16_t<base + 0x34> ADDRK;
		static inline rw16_t<base + 0x36> ADDRL;
		static inline rw16_t<base + 0x38> ADDRM;
		static inline rw16_t<base + 0x3A> ADDRN;
		static inline rw16_t<base + 0x3C> ADDRO;
		static inline rw16_t<base + 0x3E> ADDRP;
		static inline rw16_t<base + 0x40> ADDRQ;
		static inline rw16_t<base + 0x42> ADDRR;
		static inline rw16_t<base + 0x44> ADDRS;
		static inline rw16_t<base + 0x46> ADDRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ（ADRD）
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

			bits_rw_t<io_, bitpos::B0, 10>  AD;

			bits_rw_t<io_, bitpos::B14, 2>  DIAGST;
		};
		static inline adrd_t<base + 0x1E> ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロール／ステータスレジスタ（ADCSR）
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

			bit_rw_t <io_, bitpos::B8>     EXTRG;
			bit_rw_t <io_, bitpos::B9>     TRGE;

			bit_rw_t <io_, bitpos::B12>    ADIE;

			bit_rw_t <io_, bitpos::B14>    ADCS;
			bit_rw_t <io_, bitpos::B15>    ADST;
		};
		static inline adcsr_t<base + 0x00> ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ 0（ADANSA0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> ANSA0;
		};
		typedef adansa0_t<base + 0x04> ADANSA0_;
		static inline ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ 1（ADANSA1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  ANSA;
		};
		typedef adansa1_t<base + 0x06> ADANSA1_;
		static inline ADANSA1_ ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ 0（ADADS0）
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

			bits_rw_t<io_, bitpos::B0, 16> ADS0;
		};
		static inline adads0_t<base + 0x08> ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ 1（ADADS1）
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

			bits_rw_t<io_, bitpos::B0, 4> ADS;
		};
		static inline adads1_t<base + 0x0A> ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算回数選択レジスタ（ADADC）
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
		static inline adadc_t<base + 0x0C> ADADC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロール拡張レジスタ（ADCER）
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

			bit_rw_t <io_, bitpos::B2>    ADPRC;

			bit_rw_t <io_, bitpos::B5>    ACE;

			bits_rw_t<io_, bitpos::B8, 2> DIAGVAL;
			bit_rw_t <io_, bitpos::B10>   DIAGM;

			bit_rw_t <io_, bitpos::B15>   ADRFMT;
		};
		static inline adcer_t<base + 0x0E> ADCER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 開始トリガ選択レジスタ（ADSTRGR）
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

			bits_rw_t<io_, bitpos::B8, 6> TRSA;
		};
		static inline adstrgr_t<base + 0x10> ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 7）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x60> ADSSTR0;
		static inline rw8_t<base + 0x73> ADSSTR1;
		static inline rw8_t<base + 0x74> ADSSTR2;
		static inline rw8_t<base + 0x75> ADSSTR3;
		static inline rw8_t<base + 0x76> ADSSTR4;
		static inline rw8_t<base + 0x77> ADSSTR5;
		static inline rw8_t<base + 0x78> ADSSTR6;
		static inline rw8_t<base + 0x79> ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x61> ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  デジタル電源制御回路出力設定レジスタ（ADDPCONR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addpconr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DPCOE;
		};
		static inline addpconr_t<base + 0x7D> ADDPCONR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
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

		static constexpr auto PCLK = clock_profile::PCLKC;		///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 1000;				///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 20;	///< アナログ入力数


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
			AN8,
			AN9,
			AN10,
			AN11,
			AN12,
			AN13,
			AN14,
			AN15,
			AN16,
			AN17,
			AN18,
			AN19,
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
			case ANALOG::AN0:
				if(ena) {
					PORT6::PDR.B0 = 0;
					PORT6::PMR.B0 = 0;
				}
				MPC::P60PFS.ASEL = ena;
				break;
			case ANALOG::AN1:
				if(ena) {
					PORT6::PDR.B1 = 0;
					PORT6::PMR.B1 = 0;
				}
				MPC::P61PFS.ASEL = ena;
				break;
			case ANALOG::AN2:
				if(ena) {
					PORT6::PDR.B2 = 0;
					PORT6::PMR.B2 = 0;
				}
				MPC::P62PFS.ASEL = ena;
				break;
			case ANALOG::AN3:
				if(ena) {
					PORT6::PDR.B3 = 0;
					PORT6::PMR.B3 = 0;
				}
				MPC::P63PFS.ASEL = ena;
				break;
			case ANALOG::AN4:
				if(ena) {
					PORT6::PDR.B4 = 0;
					PORT6::PMR.B4 = 0;
				}
				MPC::P64PFS.ASEL = ena;
				break;
			case ANALOG::AN5:
				if(ena) {
					PORT6::PDR.B5 = 0;
					PORT6::PMR.B5 = 0;
				}
				MPC::P65PFS.ASEL = ena;
				break;
			case ANALOG::AN6:
				if(ena) {
					PORT5::PDR.B0 = 0;
					PORT5::PMR.B0 = 0;
				}
				MPC::P50PFS.ASEL = ena;
				break;
			case ANALOG::AN7:
				if(ena) {
					PORT5::PDR.B1 = 0;
					PORT5::PMR.B1 = 0;
				}
				MPC::P51PFS.ASEL = ena;
				break;
			case ANALOG::AN8:
				if(ena) {
					PORT5::PDR.B2 = 0;
					PORT5::PMR.B2 = 0;
				}
				MPC::P52PFS.ASEL = ena;
				break;
			case ANALOG::AN9:
				if(ena) {
					PORT5::PDR.B3 = 0;
					PORT5::PMR.B3 = 0;
				}
				MPC::P53PFS.ASEL = ena;
				break;
			case ANALOG::AN10:
				if(ena) {
					PORT5::PDR.B4 = 0;
					PORT5::PMR.B4 = 0;
				}
				MPC::P54PFS.ASEL = ena;
				break;
			case ANALOG::AN11:
				if(ena) {
					PORT5::PDR.B5 = 0;
					PORT5::PMR.B5 = 0;
				}
				MPC::P55PFS.ASEL = ena;
				break;
			case ANALOG::AN12:
				if(ena) {
					PORT5::PDR.B6 = 0;
					PORT5::PMR.B6 = 0;
				}
				MPC::P56PFS.ASEL = ena;
				break;
			case ANALOG::AN13:
				if(ena) {
					PORT5::PDR.B7 = 0;
					PORT5::PMR.B7 = 0;
				}
				MPC::P57PFS.ASEL = ena;
				break;
			case ANALOG::AN14:
				if(ena) {
					PORTC::PDR.B0 = 0;
					PORTC::PMR.B0 = 0;
				}
				MPC::PC0PFS.ASEL = ena;
				break;
			case ANALOG::AN15:
				if(ena) {
					PORTC::PDR.B1 = 0;
					PORTC::PMR.B1 = 0;
				}
				MPC::PC1PFS.ASEL = ena;
				break;
			case ANALOG::AN16:
				if(ena) {
					PORTC::PDR.B2 = 0;
					PORTC::PMR.B2 = 0;
				}
				MPC::PC2PFS.ASEL = ena;
				break;
			case ANALOG::AN17:
				if(ena) {
					PORTC::PDR.B3 = 0;
					PORTC::PMR.B3 = 0;
				}
				MPC::PC3PFS.ASEL = ena;
				break;
			case ANALOG::AN18:
				if(ena) {
					PORTC::PDR.B4 = 0;
					PORTC::PMR.B4 = 0;
				}
				MPC::PC4PFS.ASEL = ena;
				break;
			case ANALOG::AN19:
				if(ena) {
					PORTC::PDR.B5 = 0;
					PORTC::PMR.B5 = 0;
				}
				MPC::PC5PFS.ASEL = ena;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_t<ANALOG, BASE::ADDRA_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, BASE::ADANSA0_::address, BASE::ADANSA1_::address> ADANSA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct adsstr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(ANALOG an, uint8_t val) noexcept
			{
				switch(an) {
					// ADSSTRx レジスタアドレスは規則性が低いので・・
					case ANALOG::AN0: BASE::ADSSTR0 = val; break;
					case ANALOG::AN1: BASE::ADSSTR1 = val; break;
					case ANALOG::AN2: BASE::ADSSTR2 = val; break;
					case ANALOG::AN3: BASE::ADSSTR3 = val; break;
					case ANALOG::AN4: BASE::ADSSTR4 = val; break;
					case ANALOG::AN5: BASE::ADSSTR5 = val; break;
					case ANALOG::AN6: BASE::ADSSTR6 = val; break;
					case ANALOG::AN7: BASE::ADSSTR7 = val; break;
					default:
						BASE::ADSSTRL = val;
						break;
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint16_t operator () (ANALOG an) noexcept
			{
				uint16_t val;
				switch(an) {
					case ANALOG::AN0: val = BASE::ADSSTR0(); break;
					case ANALOG::AN1: val = BASE::ADSSTR1(); break;
					case ANALOG::AN2: val = BASE::ADSSTR2(); break;
					case ANALOG::AN3: val = BASE::ADSSTR3(); break;
					case ANALOG::AN4: val = BASE::ADSSTR4(); break;
					case ANALOG::AN5: val = BASE::ADSSTR5(); break;
					case ANALOG::AN6: val = BASE::ADSSTR6(); break;
					case ANALOG::AN7: val = BASE::ADSSTR7(); break;
					default:
						val = BASE::ADSSTRL();
						break;
				}
				return val;
			}
		};
		static inline adsstr_t ADSSTR;
	};
	typedef ad_t<0x0008'9800> AD;
}
