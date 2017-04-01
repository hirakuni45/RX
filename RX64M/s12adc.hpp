#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・S12ADC 定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX64M/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX64M/mpc.hpp"
#include "RX64M/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADC 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 0（ADDR0）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x20> ADDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 1（ADDR1）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x22> ADDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 2（ADDR2）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x24> ADDR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 3（ADDR3）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x26> ADDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 4（ADDR4）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x28> ADDR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 5（ADDR5）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x2A> ADDR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 6（ADDR6）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x2C> ADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 7（ADDR7）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x2E> ADDR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x18> ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ A（ADDBLDRA）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x84> ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ B（ADDBLDRB）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x86> ADDBLDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 自己診断データレジスタ（ ADRD ）
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

			bits_rw_t<io_, bitpos::B0, 12>  AD;
			bits_rw_t<io_, bitpos::B14, 2>  DIAGST;
		};
		static adrd_t<base + 0x1E>  ADRD;


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
		static adcsr_t<base + 0x00>  ADCSR;


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
		static adadc_t<base + 0x0C>  ADADC;


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
			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;
			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		static adcer_t<base + 0x0E>  ADCER;


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
		static adstrgr_t<base + 0x10>  ADSTRGR;


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
		static adgctrgr_t<base + 0xD9>  ADGCTRGR;


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
		static addiscr_t<base + 0x7A>  ADDISCR;


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
		static adgspcr_t<base + 0x80>  ADGSPCR;

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD0 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct s12ad0_t : public s12adc_t<base> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class analog : uint8_t {
			AIN000,
			AIN001,
			AIN002,
			AIN003,
			AIN004,
			AIN005,
			AIN006,
			AIN007,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	アナログ入力数
		*/
		//-----------------------------------------------------------------//		
		static const uint32_t analog_num_ = 8;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(analog an, bool f = true) {
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case analog::AIN000:
				PORT4::PDR.B0 = 0;
				MPC::P40PFS.ASEL = f;
				break;
			case analog::AIN001:
				PORT4::PDR.B1 = 0;
				MPC::P41PFS.ASEL = f;
				break;
			case analog::AIN002:
				PORT4::PDR.B2 = 0;
				MPC::P42PFS.ASEL = f;
				break;
			case analog::AIN003:
				PORT4::PDR.B3 = 0;
				MPC::P43PFS.ASEL = f;
				break;
			case analog::AIN004:
				PORT4::PDR.B4 = 0;
				MPC::P44PFS.ASEL = f;
				break;
			case analog::AIN005:
				PORT4::PDR.B5 = 0;
				MPC::P45PFS.ASEL = f;
				break;
			case analog::AIN006:
				PORT4::PDR.B6 = 0;
				MPC::P46PFS.ASEL = f;
				break;
			case analog::AIN007:
				PORT4::PDR.B7 = 0;
				MPC::P47PFS.ASEL = f;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator() (analog an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		static addr_t ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0（ADANSA0）
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

			bit_rw_t<io_, bitpos::B0>  ANSA000;
			bit_rw_t<io_, bitpos::B1>  ANSA001;
			bit_rw_t<io_, bitpos::B2>  ANSA002;
			bit_rw_t<io_, bitpos::B3>  ANSA003;
			bit_rw_t<io_, bitpos::B4>  ANSA004;
			bit_rw_t<io_, bitpos::B5>  ANSA005;
			bit_rw_t<io_, bitpos::B6>  ANSA006;
			bit_rw_t<io_, bitpos::B7>  ANSA007;
		};
		static adansa0_t<base + 0x04>   ADANSA0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS) unit0
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(analog an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				if(f) {
					wr16_(ofs, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			bool operator() (analog an) const {
				uint32_t n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};
		static adans_t<base + 0x04>   ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		static adans_t<base + 0x14> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0（ADANSB0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSB000;
			bit_rw_t<io_, bitpos::B1>  ANSB001;
			bit_rw_t<io_, bitpos::B2>  ANSB002;
			bit_rw_t<io_, bitpos::B3>  ANSB003;
		};
		static adansb0_t<base + 0x14>   ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1（ADANSB1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSB100;
		};
		static adansb1_t<base + 0x16>   ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		static adans_t<base + 0xD4> ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
		};
		static adansc0_t<base + 0xD4>   ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1（ADANSC1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC100;
		};
		static adansc1_t<base + 0xD6>   ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
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

			bit_rw_t<io_, bitpos::B0>  ADS000;
			bit_rw_t<io_, bitpos::B1>  ADS001;
			bit_rw_t<io_, bitpos::B2>  ADS002;
			bit_rw_t<io_, bitpos::B3>  ADS003;
			bit_rw_t<io_, bitpos::B3>  ADS004;
			bit_rw_t<io_, bitpos::B3>  ADS005;
			bit_rw_t<io_, bitpos::B3>  ADS006;
			bit_rw_t<io_, bitpos::B3>  ADS007;
		};
		static adads0_t<base + 0x08>   ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(analog an, uint8_t v) {
				if(an == analog::AIN016) {
					wr8_(base + 0xDD + static_cast<uint32_t>(an), v);
				} else {
					wr8_(base + 0xE0 + static_cast<uint32_t>(an), v);
				}
			}
		};
		static adsstr_t ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xDD> ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE0> ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE1> ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE2> ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE3> ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D プログラマブルゲインアンプコントロールレジスタ（ADPGACR）
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

			bit_rw_t<io_, bitpos::B1>  P000SEL1;
			bit_rw_t<io_, bitpos::B2>  P000ENAMP;
		};
		static adpgacr_t<base + 0x1A0>  ADPGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D プログラマブルゲインアンプゲイン設定レジスタ 0（ADPGAGS0）
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

			bits_rw_t<io_, bitpos::B0, 3>  P000GAIN;
		};
		static adpgags0_t<base + 0x1A2>  ADPGAGS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
//		static ICU::VECTOR get_vec() { return ICU::VECTOR::S12ADI; }


		//-----------------------------------------------------------------//
		/*!
			@brief  グループＢスキャン終了割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
//		static ICU::VECTOR get_gb_vec() { return ICU::VECTOR::GBADI; }


		//-----------------------------------------------------------------//
		/*!
			@brief  グループＣスキャン終了割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
//		static ICU::VECTOR get_gc_vec() { return ICU::VECTOR::GCADI; }

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct s12ad1_t : public s12adc_t<base> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class analog : uint8_t {
			AIN100,
			AIN101,
			AIN102,
			AIN103,
			AIN104,
			AIN105,
			AIN106,
			AIN107,
			AIN108,
			AIN109,
			AIN110,
			AIN111,
			AIN112,
			AIN113,
			AIN114,
			AIN115,
			AIN116,
			AIN117,
			AIN118,
			AIN119,
			AIN120,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	アナログ入力数
		*/
		//-----------------------------------------------------------------//		
		static const uint32_t analog_num_ = 20;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(analog an, bool f = true) {
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case analog::AIN100:
				PORTE::PDR.B2 = 0;
				MPC::PE2PFS.ASEL = f;
				break;
			case analog::AIN101:
				PORTE::PDR.B3 = 0;
				MPC::PE3PFS.ASEL = f;
				break;
			case analog::AIN102:
				PORTE::PDR.B4 = 0;
				MPC::PE4PFS.ASEL = f;
				break;
			case analog::AIN103:
				PORTE::PDR.B5 = 0;
				MPC::PE5PFS.ASEL = f;
				break;
			case analog::AIN104:
				PORTE::PDR.B6 = 0;
				MPC::PE6PFS.ASEL = f;
				break;
			case analog::AIN105:
				PORTE::PDR.B7 = 0;
				MPC::PE7PFS.ASEL = f;
				break;
			case analog::AIN106:
				PORTD::PDR.B6 = 0;
				MPC::PD6PFS.ASEL = f;
				break;
			case analog::AIN107:
				PORTD::PDR.B7 = 0;
				MPC::PD7PFS.ASEL = f;
				break;
			case analog::AIN108:
				PORTD::PDR.B0 = 0;
				MPC::PD0PFS.ASEL = f;
				break;
			case analog::AIN109:
				PORTD::PDR.B1 = 0;
				MPC::PD1PFS.ASEL = f;
				break;
			case analog::AIN110:
				PORTD::PDR.B2 = 0;
				MPC::PD2PFS.ASEL = f;
				break;
			case analog::AIN111:
				PORTD::PDR.B3 = 0;
				MPC::PD3PFS.ASEL = f;
				break;
			case analog::AIN112:
				PORTD::PDR.B4 = 0;
				MPC::PD4PFS.ASEL = f;
				break;
			case analog::AIN113:
				PORTD::PDR.B5 = 0;
				MPC::PD5PFS.ASEL = f;
				break;
			case analog::AIN114:
				PORT9::PDR.B0 = 0;
				MPC::P90PFS.ASEL = f;
				break;
			case analog::AIN115:
				PORT9::PDR.B1 = 0;
				MPC::P91PFS.ASEL = f;
				break;
			case analog::AIN116:
				PORT9::PDR.B2 = 0;
				MPC::P92PFS.ASEL = f;
				break;
			case analog::AIN117:
				PORT9::PDR.B3 = 0;
				MPC::P93PFS.ASEL = f;
				break;
			case analog::AIN118:
				PORT0::PDR.B0 = 0;
				MPC::P00PFS.ASEL = f;
				break;
			case analog::AIN119:
				PORT0::PDR.B1 = 0;
				MPC::P01PFS.ASEL = f;
				break;
			case analog::AIN120:
				PORT0::PDR.B2 = 0;
				MPC::P02PFS.ASEL = f;
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
		static ro16_t<base + 0x30> ADDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 9（ADDR9）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x32> ADDR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 10（ADDR10）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x34> ADDR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 11（ADDR11）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x36> ADDR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 12（ADDR12）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x38> ADDR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 13（ADDR13）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x3A> ADDR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 14（ADDR14）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x3C> ADDR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 15（ADDR15）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x3E> ADDR15;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x40> ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 17（ADDR17）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x42> ADDR17;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 18（ADDR18）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x44> ADDR18;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 19（ADDR19）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x46> ADDR19;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 20（ADDR20）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x48> ADDR20;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ（ ADTSDR ）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x1A> ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief   A/D 内部基準電圧データレジスタ（ ADOCDR ）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x01C> ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator() (analog an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		static addr_t ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(analog an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t ros = ofs;
				if(n >= 4) {
					n -= 4;
					ros += 2;
				}
				if(f) {
					wr16_(ros, rd16_(ros) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ros, rd16_(ros) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			bool operator() (analog an) const {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t ros = ofs;
				if(n >= 4) {
					n -= 4;
					ros += 2;
				}
				return (rd16_(ros) >> n) & 1;
			}
		};
		static adans_t<base + 0x04> ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0（ADANSA0）
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

			bit_rw_t<io_, bitpos::B0>  ANSA000;
			bit_rw_t<io_, bitpos::B1>  ANSA001;
			bit_rw_t<io_, bitpos::B2>  ANSA002;
			bit_rw_t<io_, bitpos::B3>  ANSA003;
		};
		static adansa0_t<base + 0x04>   ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A1（ADANSA1）
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

			bit_rw_t<io_, bitpos::B0>  ANSA100;
		};
		static adansa1_t<base + 0x06>   ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		static adans_t<base + 0x14> ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0（ADANSB0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSB000;
			bit_rw_t<io_, bitpos::B1>  ANSB001;
			bit_rw_t<io_, bitpos::B2>  ANSB002;
			bit_rw_t<io_, bitpos::B3>  ANSB003;
		};
		static adansb0_t<base + 0x14>   ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1（ADANSB1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSB100;
		};
		static adansb1_t<base + 0x16>   ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
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
			bit_rw_t<io_, bitpos::B12>  ADS012;
			bit_rw_t<io_, bitpos::B13>  ADS013;
			bit_rw_t<io_, bitpos::B14>  ADS014;
			bit_rw_t<io_, bitpos::B15>  ADS015;
		};
		static adads0_t<base + 0x08>   ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		static adans_t<base + 0xD4> ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
		};
		static adansc0_t<base + 0xD4>   ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1（ADANSC1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC100;
		};
		static adansc1_t<base + 0xD6>   ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(analog an, uint8_t v) {
				if(an == analog::AIN016) {
					wr8_(base + 0xDD + static_cast<uint32_t>(an), v);
				} else {
					wr8_(base + 0xE0 + static_cast<uint32_t>(an), v);
				}
			}
		};
		static adsstr_t ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xDD> ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE0> ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE1> ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE2> ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE3> ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプル & ホールド回路コントロールレジスタ（ADSHCR）
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
		static adshcr_t<base + 0x66>   ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
//		static ICU::VECTOR get_vec() { return ICU::VECTOR::S12ADI1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  グループＢスキャン終了割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
//		static ICU::VECTOR get_gb_vec() { return ICU::VECTOR::GBADI1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  グループＣスキャン終了割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
//		static ICU::VECTOR get_gc_vec() { return ICU::VECTOR::GCADI1; }

	};

	typedef s12ad0_t<0x00089000, peripheral::S12AD>   S12AD;
	typedef s12ad1_t<0x00089100, peripheral::S12AD1>  S12AD1;
}
