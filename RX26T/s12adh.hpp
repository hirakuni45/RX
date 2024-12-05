#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・S12ADHa 定義 @n
			※RAM 容量 48K バイト品には対応していない。（ポート選択などが異なる）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADHa 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adh_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 0（ADDR0）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x20> ADDR0_;
		static inline ADDR0_ ADDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 1（ADDR1）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x22> ADDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 2（ADDR2）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x24> ADDR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 3（ADDR3）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x26> ADDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 4（ADDR4）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x28> ADDR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 5（ADDR5）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x2A> ADDR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 6（ADDR6）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x2C> ADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 7（ADDR7）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x2E> ADDR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x18> ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ A（ADDBLDRA）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x84> ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ B（ADDBLDRB）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x86> ADDBLDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ (ADRD)
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x1E> ADRD;


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
		static inline adcsr_t<base + 0x00>  ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS0)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C0> ADSCS0_;
		static inline ADSCS0_ ADSCS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS1)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1C1> ADSCS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS2)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1C2> ADSCS2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS3)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1C3> ADSCS3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS4)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1C4> ADSCS4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS5)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1C5> ADSCS5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS6)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1C6> ADSCS6;


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

			bits_rw_t<io_, bitpos::B0, 3>  ADC;

			bit_rw_t <io_, bitpos::B7>     AVEE;
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
			bit_rw_t <io_, bitpos::B6>     ASE;

			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;

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
		struct adstrgr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 7>  TRSB;

			bits_rw_t<io_, bitpos::B8, 7>  TRSA;
		};
		static inline adstrgr_t<base + 0x10>  ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C トリガ選択レジスタ（ADGCTRGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgctrgr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  TRSC;
			bit_rw_t <io_, bitpos::B6>     GCADIE;
			bit_rw_t <io_, bitpos::B7>     GRCE;
		};
		static inline adgctrgr_t<base + 0xD9>  ADGCTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C トリガ選択レジスタ 2 (ADGCTRGR2)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgctrgr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     TRSC6;
		};
		static inline adgctrgr2_t<base + 0xDC>  ADGCTRGR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static inline ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE1> ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE2> ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE3> ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE4> ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE5> ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE6> ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE7> ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 断線検出コントロールレジスタ（ADDISCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ADNDIS;
		};
		static inline addiscr_t<base + 0x7A>  ADDISCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D イベントリンクコントロールレジスタ (ADELCCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adelccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  ELCC;
		};
		static inline adelccr_t<base + 0x7D>  ADELCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループスキャン優先コントロールレジスタ（ADGSPCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgspcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   PGS;
			bit_rw_t<io_, bitpos::B1>   GBRSCN;

			bit_rw_t<io_, bitpos::B14>  LGRRS;
			bit_rw_t<io_, bitpos::B15>  GBRP;
		};
		static inline adgspcr_t<base + 0x80>  ADGSPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能コントロールレジスタ (ADCMPCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CMPAB;

			bit_rw_t <io_, bitpos::B9>     CMPBE;

			bit_rw_t <io_, bitpos::B11>    CMPAE;

			bit_rw_t <io_, bitpos::B13>    CMPBIE;
			bit_rw_t <io_, bitpos::B14>    WCMPBE;
			bit_rw_t <io_, bitpos::B15>    CMPAIE;
		};
		static inline adcmpcr_t<base + 0x90>  ADCMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 下位側レベル設定レジスタ (ADCMPDR0)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x9C> ADCMPDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 上位側レベル設定レジスタ (ADCMPDR1)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x9E> ADCMPDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A/B ステータスモニタレジスタ（ ADWINMON ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adwinmon_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   MONCOMB;

			bit_rw_t<io_, bitpos::B4>   MONCMPA;
			bit_rw_t<io_, bitpos::B5>   MONCMPB;
		};
		static inline adwinmon_t<base + 0x8C>  ADWINMON;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B チャネル選択レジスタ (ADCMPBNSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbnsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   CMPCHB;

			bit_rw_t <io_, bitpos::B7>      CMPLB;
		};
		static inline adcmpbnsr_t<base + 0xA6>  ADCMPBNSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 下位側レベル設定レジスタ（ ADWINLLB ）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xA8> ADWINLLB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 上位側レベル設定レジスタ（ ADWINULB ）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0xAA> ADWINULB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B チャネルステータスレジスタ (ADCMPBSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTB;
		};
		static inline adcmpbsr_t<base + 0xAC>  ADCMPBSR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADa 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t : public s12adh_base_t<base> {

		typedef s12adh_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI;		///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::S12GCADI;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::GROUPBL1::S12CMPBI;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 900;				///< A/D 入力 0.9uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,		///< AN000 入力
			AN001,		///< AN001 入力
			AN002,		///< AN002 入力
			AN003,		///< AN003 入力
			AN004,		///< AN004 入力
			AN005,		///< AN005 入力
			AN006,		///< AN006 入力
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
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ (ADDR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0 (ADANSA0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA000;
			bit_rw_t<io_, bitpos::B1>   ANSA001;
			bit_rw_t<io_, bitpos::B2>   ANSA002;
			bit_rw_t<io_, bitpos::B3>   ANSA003;
			bit_rw_t<io_, bitpos::B4>   ANSA004;
			bit_rw_t<io_, bitpos::B5>   ANSA005;
			bit_rw_t<io_, bitpos::B6>   ANSA006;
		};
		typedef adansa0_t<base + 0x04>  ADANSA0_;
		static inline ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0 (ADANSB0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB000;
			bit_rw_t<io_, bitpos::B1>   ANSB001;
			bit_rw_t<io_, bitpos::B2>   ANSB002;
			bit_rw_t<io_, bitpos::B3>   ANSB003;
			bit_rw_t<io_, bitpos::B4>   ANSB004;
			bit_rw_t<io_, bitpos::B5>   ANSB005;
			bit_rw_t<io_, bitpos::B6>   ANSB006;
		};
		typedef adansb0_t<base + 0x14>  ADANSB0_;
		static inline ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 (ADANSC0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC000;
			bit_rw_t<io_, bitpos::B1>   ANSC001;
			bit_rw_t<io_, bitpos::B2>   ANSC002;
			bit_rw_t<io_, bitpos::B3>   ANSC003;
			bit_rw_t<io_, bitpos::B4>   ANSC004;
			bit_rw_t<io_, bitpos::B5>   ANSC005;
			bit_rw_t<io_, bitpos::B6>   ANSC006;
		};
		typedef adansc0_t<base + 0xD4>  ADANSC0_;
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSA0_::address>  ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSB0_::address>  ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSC0_::address>  ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adscs_t<ANALOG, ANALOG::AN006, BASE::ADSCS0_::address> ADSCS;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均機能チャネル選択レジスタ 0 (ADADS0)
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

			bit_rw_t<io_, bitpos::B0>   ADS000;
			bit_rw_t<io_, bitpos::B1>   ADS001;
			bit_rw_t<io_, bitpos::B2>   ADS002;
			bit_rw_t<io_, bitpos::B3>   ADS003;
			bit_rw_t<io_, bitpos::B4>   ADS004;
			bit_rw_t<io_, bitpos::B5>   ADS005;
			bit_rw_t<io_, bitpos::B6>   ADS006;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADADS0_::address>  ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1_t<ANALOG, BASE::ADSSTR0_::address> ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド動作モード選択レジスタ (ADSHMSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshmsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SHMD;
		};
		static inline adshmsr_t<base + 0x7C>  ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ 0 (ADCMPANSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPCHA006;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static inline ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ (ADCMPANSR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPANSR0_::address>  ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 0 (ADCMPLR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPLCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPLCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPLCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPLCHA006;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static inline ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ (ADCMPLR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPLR0_::address>  ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 0 (ADCMPSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPSTCHA006;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static inline ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ (ADCMPSR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPSR0_::address>  ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプコントロールレジスタ (ADPGACR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgacr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P000CR;
			bits_rw_t<io_, bitpos::B4, 4>  P001CR;
			bits_rw_t<io_, bitpos::B8, 4>  P002CR;
		};
		static inline adpgacr_t<base + 0x1A0>  ADPGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプゲイン設定レジスタ 0 (ADPGAGS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgags0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P000GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  P001GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  P002GAIN;
		};
		static inline adpgags0_t<base + 0x1A2>  ADPGAGS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプ差動入力コントロールレジスタ (ADPGADCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgadcr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  P000DG;

			bit_rw_t <io_, bitpos::B3>     P000DEN;
			bits_rw_t<io_, bitpos::B4, 2>  P001DG;

			bit_rw_t <io_, bitpos::B7>     P001DEN;
			bits_rw_t<io_, bitpos::B8, 2>  P002DG;

			bit_rw_t <io_, bitpos::B11>    P002DEN;
		};
		static inline adpgadcr0_t<base + 0x1B0>  ADPGADCR0;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad1_t : public s12adh_base_t<base> {

		typedef s12adh_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI1;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI1;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::S12GCADI1;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI1;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::GROUPBL1::S12CMPBI1;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 900;				///< A/D 入力 0.9uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 8;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN100,		///< AN100 入力
			AN101,		///< AN101 入力
			AN102,		///< AN102 入力
			AN103,		///< AN103 入力
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
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN100:
				if(ena) {
					PORT4::PDR.B4 = 0;
					PORT4::PMR.B4 = 0;
				}
				MPC::P44PFS.ASEL = ena;
				break;
			case ANALOG::AN101:
				if(ena) {
					PORT4::PDR.B5 = 0;
					PORT4::PMR.B5 = 0;
				}
				MPC::P45PFS.ASEL = ena;
				break;
			case ANALOG::AN102:
				if(ena) {
					PORT4::PDR.B6 = 0;
					PORT4::PMR.B6 = 0;
				}
				MPC::P46PFS.ASEL = ena;
				break;
			case ANALOG::AN103:
				if(ena) {
					PORT4::PDR.B7 = 0;
					PORT4::PMR.B7 = 0;
				}
				MPC::P47PFS.ASEL = ena;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ (ADDR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0 (ADANSA0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA000;
			bit_rw_t<io_, bitpos::B1>   ANSA001;
			bit_rw_t<io_, bitpos::B2>   ANSA002;
			bit_rw_t<io_, bitpos::B3>   ANSA003;
		};
		typedef adansa0_t<base + 0x04>  ADANSA0_;
		static inline ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0 (ADANSB0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB000;
			bit_rw_t<io_, bitpos::B1>   ANSB001;
			bit_rw_t<io_, bitpos::B2>   ANSB002;
			bit_rw_t<io_, bitpos::B3>   ANSB003;
		};
		typedef adansb0_t<base + 0x14>  ADANSB0_;
		static inline ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 (ADANSC0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC000;
			bit_rw_t<io_, bitpos::B1>   ANSC001;
			bit_rw_t<io_, bitpos::B2>   ANSC002;
			bit_rw_t<io_, bitpos::B3>   ANSC003;
		};
		typedef adansc0_t<base + 0xD4>  ADANSC0_;
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSA0_::address>  ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSB0_::address>  ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADANSC0_::address>  ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adscs_t<ANALOG, ANALOG::AN107, BASE::ADSCS0_::address> ADSCS;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均機能チャネル選択レジスタ 0 (ADADS0)
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

			bit_rw_t<io_, bitpos::B0>   ADS000;
			bit_rw_t<io_, bitpos::B1>   ADS001;
			bit_rw_t<io_, bitpos::B2>   ADS002;
			bit_rw_t<io_, bitpos::B3>   ADS003;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADADS0_::address>  ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1_t<ANALOG, BASE::ADSSTR0_::address> ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド回路コントロールレジスタ (ADSHCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SSTSH;
			bits_rw_t<io_, bitpos::B8, 3>  SHANS;
		};
		static inline adshcr_t<base + 0x66>  ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド動作モード選択レジスタ (ADSHMSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshmsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SHMD;
		};
		static inline adshmsr_t<base + 0x7C>  ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ 0 (ADCMPANSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPCHA003;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static inline ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ (ADCMPANSR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPANSR0_::address>  ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 0 (ADCMPLR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPLCHA003;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static inline ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ (ADCMPLR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPLR0_::address>  ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 0 (ADCMPSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPSTCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPSTCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPSTCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPSTCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPSTCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPSTCHA011;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static inline ADCMPSR0_ ADCMPSR0;
	

		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ (ADCMPSR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, ADCMPSR0_::address>  ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプコントロールレジスタ (ADPGACR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgacr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P100CR;
			bits_rw_t<io_, bitpos::B4, 4>  P101CR;
			bits_rw_t<io_, bitpos::B8, 4>  P102CR;
		};
		static inline adpgacr_t<base + 0x1A0>  ADPGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプゲイン設定レジスタ 0 (ADPGAGS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgags0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  P100GAIN;
			bits_rw_t<io_, bitpos::B4, 4>  P101GAIN;
			bits_rw_t<io_, bitpos::B8, 4>  P102GAIN;
		};
		static inline adpgags0_t<base + 0x1A2>  ADPGAGS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D プログラマブルゲインアンプ差動入力コントロールレジスタ (ADPGADCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgadcr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  P100DG;

			bit_rw_t <io_, bitpos::B3>     P100DEN;
			bits_rw_t<io_, bitpos::B4, 2>  P101DG;

			bit_rw_t <io_, bitpos::B7>     P101DEN;
			bits_rw_t<io_, bitpos::B8, 2>  P102DG;

			bit_rw_t <io_, bitpos::B11>    P102DEN;
		};
		static inline adpgadcr0_t<base + 0x1B0>  ADPGADCR0;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD2 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad2_t : public s12adh_base_t<base> {

		typedef s12adh_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD2;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::S12ADI2;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::S12GBADI2;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::S12GCADI2;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI2;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::GROUPBL1::S12CMPBI2;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 900;				///< A/D 入力 0.9uS、単位「ns」
		static constexpr uint32_t TO_CONV_TIME_NS = 4000;			///< 温度、基準電圧 4uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 14;					///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN200,		///< AN200 入力
			AN201,		///< AN201 入力
			AN202,		///< AN202 入力
			AN203,		///< AN203 入力
			AN204,		///< AN204 入力
			AN205,		///< AN205 入力
			AN206,		///< AN206 入力
			AN207,		///< AN207 入力
			AN208,		///< AN208 入力
			AN209,		///< AN209 入力
			AN210,		///< AN210 入力
			AN211,		///< AN211 入力

			AN216 = 16,	///< AN216 入力
			AN217,		///< AN217 入力

			TEMP,		///< 温度センサ
			REF,		///< 内部基準電圧
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
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN200:
				if(ena) {
					PORT5::PDR.B2 = 0;
					PORT5::PMR.B2 = 0;
				}
				MPC::P52PFS.ASEL = ena;
				break;
			case ANALOG::AN201:
				if(ena) {
					PORT5::PDR.B3 = 0;
					PORT5::PMR.B3 = 0;
				}
				MPC::P53PFS.ASEL = ena;
				break;
			case ANALOG::AN202:
				if(ena) {
					PORT5::PDR.B4 = 0;
					PORT5::PMR.B4 = 0;
				}
				MPC::P54PFS.ASEL = ena;
				break;
			case ANALOG::AN203:
				if(ena) {
					PORT5::PDR.B5 = 0;
					PORT5::PMR.B5 = 0;
				}
				MPC::P55PFS.ASEL = ena;
				break;
			case ANALOG::AN204:
				if(ena) {
					PORT5::PDR.B0 = 0;
					PORT5::PMR.B0 = 0;
				}
				MPC::P50PFS.ASEL = ena;
				break;
			case ANALOG::AN205:
				if(ena) {
					PORT5::PDR.B1 = 0;
					PORT5::PMR.B1 = 0;
				}
				MPC::P51PFS.ASEL = ena;
				break;
			case ANALOG::AN206:
				if(ena) {
					PORT6::PDR.B0 = 0;
					PORT6::PMR.B0 = 0;
				}
				MPC::P60PFS.ASEL = ena;
				break;
			case ANALOG::AN207:
				if(ena) {
					PORT6::PDR.B1 = 0;
					PORT6::PMR.B1 = 0;
				}
				MPC::P61PFS.ASEL = ena;
				break;
			case ANALOG::AN208:
				if(ena) {
					PORT6::PDR.B2 = 0;
					PORT6::PMR.B2 = 0;
				}
				MPC::P62PFS.ASEL = ena;
				break;
			case ANALOG::AN209:
				if(ena) {
					PORT6::PDR.B3 = 0;
					PORT6::PMR.B3 = 0;
				}
				MPC::P63PFS.ASEL = ena;
				break;
			case ANALOG::AN210:
				if(ena) {
					PORT6::PDR.B4 = 0;
					PORT6::PMR.B4 = 0;
				}
				MPC::P64PFS.ASEL = ena;
				break;
			case ANALOG::AN211:
				if(ena) {
					PORT6::PDR.B5 = 0;
					PORT6::PMR.B5 = 0;
				}
				MPC::P65PFS.ASEL = ena;
				break;

			case ANALOG::AN216:
				if(ena) {
					PORT2::PDR.B0 = 0;
					PORT2::PMR.B0 = 0;
				}
				MPC::P20PFS.ASEL = ena;
				break;
			case ANALOG::AN217:
				if(ena) {
					PORT2::PDR.B1 = 0;
					PORT2::PMR.B1 = 0;
				}
				MPC::P21PFS.ASEL = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 8（ADDR8）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x30> ADDR8_;
		static inline ADDR8_ ADDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 9（ADDR9）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x32> ADDR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 10（ADDR10）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x34> ADDR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 11（ADDR11）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x36> ADDR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> ADDR16_;
		static inline ADDR16_ ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 17（ADDR17）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x42> ADDR17;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ (ADTSDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1A> ADTSDR_;
		static inline ADTSDR_ ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ (ADOCDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1C> ADOCDR_;
		static inline ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ (ADDR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_tr_t<ANALOG, BASE::ADDR0_::address,
			ANALOG::TEMP, ADTSDR_::address, ANALOG::REF, ADOCDR_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0 (ADANSA0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA000;
			bit_rw_t<io_, bitpos::B1>   ANSA001;
			bit_rw_t<io_, bitpos::B2>   ANSA002;
			bit_rw_t<io_, bitpos::B3>   ANSA003;
			bit_rw_t<io_, bitpos::B4>   ANSA004;
			bit_rw_t<io_, bitpos::B5>   ANSA005;
			bit_rw_t<io_, bitpos::B6>   ANSA006;
			bit_rw_t<io_, bitpos::B7>   ANSA007;
			bit_rw_t<io_, bitpos::B8>   ANSA008;
			bit_rw_t<io_, bitpos::B9>   ANSA009;
			bit_rw_t<io_, bitpos::B10>  ANSA010;
			bit_rw_t<io_, bitpos::B11>  ANSA011;
		};
		typedef adansa0_t<base + 0x04>  ADANSA0_;
		static inline ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A1 (ADANSA1)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA100;
			bit_rw_t<io_, bitpos::B1>   ANSA101;
		};
		typedef adansa1_t<base + 0x06>  ADANSA1_;
		static inline ADANSA1_ ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0 (ADANSB0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB000;
			bit_rw_t<io_, bitpos::B1>   ANSB001;
			bit_rw_t<io_, bitpos::B2>   ANSB002;
			bit_rw_t<io_, bitpos::B3>   ANSB003;
			bit_rw_t<io_, bitpos::B4>   ANSB004;
			bit_rw_t<io_, bitpos::B5>   ANSB005;
			bit_rw_t<io_, bitpos::B6>   ANSB006;
			bit_rw_t<io_, bitpos::B7>   ANSB007;
			bit_rw_t<io_, bitpos::B8>   ANSB008;
			bit_rw_t<io_, bitpos::B9>   ANSB009;
			bit_rw_t<io_, bitpos::B10>  ANSB010;
			bit_rw_t<io_, bitpos::B11>  ANSB011;
		};
		typedef adansb0_t<base + 0x14>  ADANSB0_;
		static inline ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1 (ADANSB1)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB100;
			bit_rw_t<io_, bitpos::B1>   ANSB101;
		};
		typedef adansb1_t<base + 0x16>  ADANSB1_;
		static inline ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 (ADANSC0)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC000;
			bit_rw_t<io_, bitpos::B1>   ANSC001;
			bit_rw_t<io_, bitpos::B2>   ANSC002;
			bit_rw_t<io_, bitpos::B3>   ANSC003;
			bit_rw_t<io_, bitpos::B4>   ANSC004;
			bit_rw_t<io_, bitpos::B5>   ANSC005;
			bit_rw_t<io_, bitpos::B6>   ANSC006;
			bit_rw_t<io_, bitpos::B7>   ANSC007;
			bit_rw_t<io_, bitpos::B8>   ANSC008;
			bit_rw_t<io_, bitpos::B9>   ANSC009;
			bit_rw_t<io_, bitpos::B10>  ANSC010;
			bit_rw_t<io_, bitpos::B11>  ANSC011;
		};
		typedef adansc0_t<base + 0xD4>  ADANSC0_;
		static inline ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1 (ADANSC1)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC100;
			bit_rw_t<io_, bitpos::B1>   ANSC101;
		};
		typedef adansc1_t<base + 0xD6>  ADANSC1_;
		static inline ADANSC1_ ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSA0_::address, ADANSA1_::address>  ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSB0_::address, ADANSB1_::address>  ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADANSC0_::address, ADANSC1_::address>  ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 8 (ADSCS8)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x1C8> ADSCS8_;
		static inline ADSCS8_ ADSCS8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 9 (ADSCS9)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1C9> ADSCS9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 10 (ADSCS10)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1CA> ADSCS10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 11 (ADSCS11)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1CB> ADSCS11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 12 (ADSCS12)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1D0> ADSCS12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ 13 (ADSCS13)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x1D1> ADSCS13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ (ADSCS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adscs_t<ANALOG, ANALOG::AN217, BASE::ADSCS0_::address> ADSCS;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均機能チャネル選択レジスタ 0 (ADADS0)
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

			bit_rw_t<io_, bitpos::B0>   ADS000;
			bit_rw_t<io_, bitpos::B1>   ADS001;
			bit_rw_t<io_, bitpos::B2>   ADS002;
			bit_rw_t<io_, bitpos::B3>   ADS003;
			bit_rw_t<io_, bitpos::B4>   ADS004;
			bit_rw_t<io_, bitpos::B5>   ADS005;
			bit_rw_t<io_, bitpos::B6>   ADS006;
			bit_rw_t<io_, bitpos::B7>   ADS007;
			bit_rw_t<io_, bitpos::B8>   ADS008;
			bit_rw_t<io_, bitpos::B9>   ADS009;
			bit_rw_t<io_, bitpos::B10>  ADS010;
			bit_rw_t<io_, bitpos::B11>  ADS011;
		};
		typedef adads0_t<base + 0x08>  ADADS0_;
		static inline ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 1 (ADADS1)
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

			bit_rw_t<io_, bitpos::B0>   ADS100;
			bit_rw_t<io_, bitpos::B1>   ADS101;
		};
		typedef adads1_t<base + 0x0A>  ADADS1_;
		static inline ADADS1_ ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ (ADADS)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADADS0_::address, ADADS1_::address>  ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換拡張入力コントロールレジスタ (ADEXICR)
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

			bit_rw_t<io_, bitpos::B0>   TSSAD;
			bit_rw_t<io_, bitpos::B1>   OCSAD;

			bit_rw_t<io_, bitpos::B8>   TSSA;
			bit_rw_t<io_, bitpos::B9>   OCSA;
			bit_rw_t<io_, bitpos::B10>  TSSB;
			bit_rw_t<io_, bitpos::B11>  OCSB;
		};
		static inline adexicr_t<base + 0x12>  ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D グループ C 拡張入力コントロールレジスタ (ADGCEXCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgcexcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TSSC;
			bit_rw_t<io_, bitpos::B1> OCSC;
		};
		static inline adgcexcr_t<base + 0xD8>  ADGCEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR8)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE8> ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR9)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xE9> ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR10)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEA> ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTR11)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0xEB> ADSSTR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> ADSSTRL_;
		static inline ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTRT)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDE> ADSSTRT_;
		static inline ADSSTRT_ ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ (ADSSTRO)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDF> ADSSTRO_;
		static inline ADSSTRO_ ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adsstr1l_tr_t<ANALOG, BASE::ADSSTR0_::address, ADSSTRL_::address,
			ANALOG::TEMP, ADSSTRT_::address, ANALOG::REF, ADSSTRO_::address> ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D サンプル & ホールド回路コントロールレジスタ (ADSHCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SSTSH;
			bits_rw_t<io_, bitpos::B8, 3>  SHANS;
		};
		static inline adshcr_t<base + 0x66>  ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ 0 (ADCMPANSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPCHA011;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static inline ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネル選択レジスタ 1 (ADCMPANSR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPCHA100;
			bit_rw_t<io_, bitpos::B1> CMPCHA101;
		};
		typedef adcmpansr1_t<base + 0x96>  ADCMPANSR1_;
		static inline ADCMPANSR1_ ADCMPANSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネル選択レジスタ (ADCMPANSR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADCMPANSR0_::address, ADCMPANSR1_::address>  ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 拡張入力選択レジスタ (ADCMPANSER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpanser_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPSTS;
			bit_rw_t<io_, bitpos::B1> CMPSOC;
		};
		static inline adcmpanser_t<base + 0x92>  ADCMPANSER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 0 (ADCMPLR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPLCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPLCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPLCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPLCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPLCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPLCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPLCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPLCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPLCHA011;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static inline ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 比較条件設定レジスタ 1 (ADCMPLR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPLCHA100;
			bit_rw_t<io_, bitpos::B1> CMPLCHA101;
		};
		typedef adcmplr1_t<base + 0x9A>  ADCMPLR1_;
		static inline ADCMPLR1_ ADCMPLR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A 比較条件設定レジスタ (ADCMPLR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADCMPLR0_::address, ADCMPLR1_::address>  ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 拡張入力比較条件設定レジスタ (ADCMPLER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpler_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPLTS;
			bit_rw_t<io_, bitpos::B1> CMPLOC;
		};
		static inline adcmpler_t<base + 0x93>  ADCMPLER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 0 (ADCMPSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>   CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>   CMPSTCHA006;
			bit_rw_t<io_, bitpos::B7>   CMPSTCHA007;
			bit_rw_t<io_, bitpos::B8>   CMPSTCHA008;
			bit_rw_t<io_, bitpos::B9>   CMPSTCHA009;
			bit_rw_t<io_, bitpos::B10>  CMPSTCHA010;
			bit_rw_t<io_, bitpos::B11>  CMPSTCHA011;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static inline ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 1 (ADCMPSR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPFTCHA100;
			bit_rw_t<io_, bitpos::B1> CMPFTCHA101;
		};
		typedef adcmpsr1_t<base + 0xA2>  ADCMPSR1_;
		static inline ADCMPSR1_ ADCMPSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネルステータスレジスタ (ADCMPSR)
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans2_t<ANALOG, ADCMPSR0_::address, ADCMPSR1_::address>  ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A 拡張入力チャネルステータスレジスタ (ADCMPSER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpser_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPFTS;
			bit_rw_t<io_, bitpos::B1> CMPFOC;
		};
		static inline adcmpser_t<base + 0xA4>  ADCMPSER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧モニタ回路許可レジスタ (ADVMONCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct advmoncr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> VDE;
		};
		static inline advmoncr_t<base + 0x1E2>  ADVMONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧モニタ回路出力許可レジスタ (ADVMONO)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct advmono_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> VDO;
		};
		static inline advmono_t<base + 0x1E4>  ADVMONO;
	};

	typedef s12ad_t <0x0008'9000> S12AD;
	typedef s12ad1_t<0x0008'9200> S12AD1;
	typedef s12ad2_t<0x0008'9400> S12AD2;
}
