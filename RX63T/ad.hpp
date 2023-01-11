#pragma once
//=============================================================================//
/*!	@file
	@brief	RX63T 10 ビット A/D コンバータ（ADa）
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
			@brief  A/D データレジスタ n（ADDRn）（n = A ～ T）
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
		typedef rw16_t<base + 0x30> ADDRI_;
		static ADDRI_ ADDRI;
		typedef rw16_t<base + 0x32> ADDRJ_;
		static ADDRJ_ ADDRJ;
		typedef rw16_t<base + 0x34> ADDRK_;
		static ADDRK_ ADDRK;
		typedef rw16_t<base + 0x36> ADDRL_;
		static ADDRL_ ADDRL;
		typedef rw16_t<base + 0x38> ADDRM_;
		static ADDRM_ ADDRM;
		typedef rw16_t<base + 0x3A> ADDRN_;
		static ADDRN_ ADDRN;
		typedef rw16_t<base + 0x3C> ADDRO_;
		static ADDRO_ ADDRO;
		typedef rw16_t<base + 0x3E> ADDRP_;
		static ADDRP_ ADDRP;
		typedef rw16_t<base + 0x40> ADDRQ_;
		static ADDRQ_ ADDRQ;
		typedef rw16_t<base + 0x42> ADDRR_;
		static ADDRR_ ADDRR;
		typedef rw16_t<base + 0x44> ADDRS_;
		static ADDRS_ ADDRS;
		typedef rw16_t<base + 0x46> ADDRT_;
		static ADDRT_ ADDRT;


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
		typedef adrd_t<base + 0x1E> ADRD_;
		static ADRD_ ADRD;


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
		typedef adcsr_t<base + 0x00> ADCSR_;
		static ADCSR_ ADCSR;


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
		static ADANSA0_ ADANSA0;


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
		static ADANSA1_ ADANSA1;


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
		typedef adads0_t<base + 0x08> ADADS0_;
		static ADADS0_ ADADS0;


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
		typedef adads1_t<base + 0x0A> ADADS1_;
		static ADADS1_ ADADS1;


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
		typedef adadc_t<base + 0x0C> ADADC_;
		static ADADC_ ADADC;


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
		typedef adcer_t<base + 0x0E> ADCER_;
		static ADCER_ ADCER;


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
		typedef adstrgr_t<base + 0x10> ADSTRGR_;
		static ADSTRGR_ ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 7）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x60> ADSSTR0_;
		static ADSSTR0_ ADSSTR0;
		typedef rw8_t<base + 0x73> ADSSTR1_;
		static ADSSTR1_ ADSSTR1;
		typedef rw8_t<base + 0x74> ADSSTR2_;
		static ADSSTR2_ ADSSTR2;
		typedef rw8_t<base + 0x75> ADSSTR3_;
		static ADSSTR3_ ADSSTR3;
		typedef rw8_t<base + 0x76> ADSSTR4_;
		static ADSSTR4_ ADSSTR4;
		typedef rw8_t<base + 0x77> ADSSTR5_;
		static ADSSTR5_ ADSSTR5;
		typedef rw8_t<base + 0x78> ADSSTR6_;
		static ADSSTR6_ ADSSTR6;
		typedef rw8_t<base + 0x79> ADSSTR7_;
		static ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x61> ADSSTRL_;
		static ADSSTRL_ ADSSTRL;


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
		typedef addpconr_t<base + 0x7D> ADDPCONR_;
		static ADDPCONR_ ADDPCONR;
	};
	template <uint32_t base> typename ad_base_t<base>::ADDRA_ ad_base_t<base>::ADDRA;
	template <uint32_t base> typename ad_base_t<base>::ADDRB_ ad_base_t<base>::ADDRB;
	template <uint32_t base> typename ad_base_t<base>::ADDRC_ ad_base_t<base>::ADDRC;
	template <uint32_t base> typename ad_base_t<base>::ADDRD_ ad_base_t<base>::ADDRD;
	template <uint32_t base> typename ad_base_t<base>::ADDRE_ ad_base_t<base>::ADDRE;
	template <uint32_t base> typename ad_base_t<base>::ADDRF_ ad_base_t<base>::ADDRF;
	template <uint32_t base> typename ad_base_t<base>::ADDRG_ ad_base_t<base>::ADDRG;
	template <uint32_t base> typename ad_base_t<base>::ADDRH_ ad_base_t<base>::ADDRH;
	template <uint32_t base> typename ad_base_t<base>::ADDRI_ ad_base_t<base>::ADDRI;
	template <uint32_t base> typename ad_base_t<base>::ADDRJ_ ad_base_t<base>::ADDRJ;
	template <uint32_t base> typename ad_base_t<base>::ADDRK_ ad_base_t<base>::ADDRK;
	template <uint32_t base> typename ad_base_t<base>::ADDRL_ ad_base_t<base>::ADDRL;
	template <uint32_t base> typename ad_base_t<base>::ADDRM_ ad_base_t<base>::ADDRM;
	template <uint32_t base> typename ad_base_t<base>::ADDRN_ ad_base_t<base>::ADDRN;
	template <uint32_t base> typename ad_base_t<base>::ADDRO_ ad_base_t<base>::ADDRO;
	template <uint32_t base> typename ad_base_t<base>::ADDRP_ ad_base_t<base>::ADDRP;
	template <uint32_t base> typename ad_base_t<base>::ADDRQ_ ad_base_t<base>::ADDRQ;
	template <uint32_t base> typename ad_base_t<base>::ADDRR_ ad_base_t<base>::ADDRR;
	template <uint32_t base> typename ad_base_t<base>::ADDRS_ ad_base_t<base>::ADDRS;
	template <uint32_t base> typename ad_base_t<base>::ADDRT_ ad_base_t<base>::ADDRT;
	template <uint32_t base> typename ad_base_t<base>::ADRD_ ad_base_t<base>::ADRD;
	template <uint32_t base> typename ad_base_t<base>::ADCSR_ ad_base_t<base>::ADCSR;
	template <uint32_t base> typename ad_base_t<base>::ADANSA0_ ad_base_t<base>::ADANSA0;
	template <uint32_t base> typename ad_base_t<base>::ADANSA1_ ad_base_t<base>::ADANSA1;
	template <uint32_t base> typename ad_base_t<base>::ADADS0_ ad_base_t<base>::ADADS0;
	template <uint32_t base> typename ad_base_t<base>::ADADS1_ ad_base_t<base>::ADADS1;
	template <uint32_t base> typename ad_base_t<base>::ADADC_ ad_base_t<base>::ADADC;
	template <uint32_t base> typename ad_base_t<base>::ADCER_ ad_base_t<base>::ADCER;
	template <uint32_t base> typename ad_base_t<base>::ADSTRGR_ ad_base_t<base>::ADSTRGR;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR0_ ad_base_t<base>::ADSSTR0;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR1_ ad_base_t<base>::ADSSTR1;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR2_ ad_base_t<base>::ADSSTR2;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR3_ ad_base_t<base>::ADSSTR3;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR4_ ad_base_t<base>::ADSSTR4;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR5_ ad_base_t<base>::ADSSTR5;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR6_ ad_base_t<base>::ADSSTR6;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR7_ ad_base_t<base>::ADSSTR7;
	template <uint32_t base> typename ad_base_t<base>::ADSSTRL_ ad_base_t<base>::ADSSTRL;
	template <uint32_t base> typename ad_base_t<base>::ADDPCONR_ ad_base_t<base>::ADDPCONR;


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
		typedef ad_utils::addr_t<ANALOG, BASE::ADDRA_::address> ADDR_;
		static ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, BASE::ADANSA0_::address, BASE::ADANSA1_::address> ADANSA_;
		static  ADANSA_ ADANSA;


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
		typedef adsstr_t ADSSTR_;
		static ADSSTR_ ADSSTR;
	};
	template <uint32_t base> typename ad_t<base>::ADDR_ ad_t<base>::ADDR;
	template <uint32_t base> typename ad_t<base>::ADSSTR_ ad_t<base>::ADSSTR;

	typedef ad_t<0x0008'9800> AD;
}
