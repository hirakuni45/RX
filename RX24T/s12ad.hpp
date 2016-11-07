#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・S12AD 定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX24T/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX24T/mpc.hpp"
#include "RX24T/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t {

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
	struct s12ad0_t : public s12ad_t<base> {

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
			AIN016 = 0x10,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	アナログ入力数
		*/
		//-----------------------------------------------------------------//		
		static const uint32_t analog_num_ = 5;


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
			case analog::AIN016:
				PORT2::PDR.B0 = 0;
				MPC::P20PFS.ASEL = f;
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
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x40> ADDR16;


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


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A
		*/
		//-----------------------------------------------------------------//
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
		};
		static adads0_t<base + 0x08>   ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 1（ADADS1）
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

			bit_rw_t<io_, bitpos::B0>  ADS100;
		};
		static adads1_t<base + 0x0A>   ADADS1;


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

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct s12ad1_t : public s12ad_t<base> {

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
			AIN116 = 0x10,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	アナログ入力数
		*/
		//-----------------------------------------------------------------//		
		static const uint32_t analog_num_ = 5;


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
				PORT4::PDR.B4 = 0;
				MPC::P44PFS.ASEL = f;
				break;
			case analog::AIN101:
				PORT4::PDR.B5 = 0;
				MPC::P45PFS.ASEL = f;
				break;
			case analog::AIN102:
				PORT4::PDR.B6 = 0;
				MPC::P46PFS.ASEL = f;
				break;
			case analog::AIN103:
				PORT4::PDR.B7 = 0;
				MPC::P47PFS.ASEL = f;
				break;
			case analog::AIN116:
				PORT2::PDR.B1 = 0;
				MPC::P21PFS.ASEL = f;
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
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x40> ADDR16;


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


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A
		*/
		//-----------------------------------------------------------------//
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

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD2 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct s12ad2_t : public s12ad_t<base> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class analog : uint8_t {
			AIN200,
			AIN201,
			AIN202,
			AIN203,
			AIN204,
			AIN205,
			AIN206,
			AIN207,
			AIN208,
			AIN209,
			AIN210,
			AIN211,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	アナログ入力数
		*/
		//-----------------------------------------------------------------//		
		static const uint32_t analog_num_ = 12;


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
			case analog::AIN200:
				PORT6::PDR.B0 = 0;
				MPC::P60PFS.ASEL = f;
				break;
			case analog::AIN201:
				PORT6::PDR.B1 = 0;
				MPC::P61PFS.ASEL = f;
				break;
			case analog::AIN202:
				PORT6::PDR.B2 = 0;
				MPC::P62PFS.ASEL = f;
				break;
			case analog::AIN203:
				PORT6::PDR.B3 = 0;
				MPC::P63PFS.ASEL = f;
				break;
			case analog::AIN204:
				PORT6::PDR.B4 = 0;
				MPC::P64PFS.ASEL = f;
				break;
			case analog::AIN205:
				PORT6::PDR.B5 = 0;
				MPC::P65PFS.ASEL = f;
				break;
			case analog::AIN206:
				PORT5::PDR.B0 = 0;
				MPC::P50PFS.ASEL = f;
				break;
			case analog::AIN207:
				PORT5::PDR.B1 = 0;
				MPC::P51PFS.ASEL = f;
				break;
			case analog::AIN208:
				PORT5::PDR.B2 = 0;
				MPC::P52PFS.ASEL = f;
				break;
			case analog::AIN209:
				PORT5::PDR.B3 = 0;
				MPC::P53PFS.ASEL = f;
				break;
			case analog::AIN210:
				PORT5::PDR.B4 = 0;
				MPC::P54PFS.ASEL = f;
				break;
			case analog::AIN211:
				PORT5::PDR.B5 = 0;
				MPC::P55PFS.ASEL = f;
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
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


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A
		*/
		//-----------------------------------------------------------------//
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
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		static adansa0_t<base + 0x04>   ADANSA0;


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
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		static adansb0_t<base + 0x14>   ADANSB0;


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
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		static adansc0_t<base + 0xD4>   ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ（ADOCDR）
		*/
		//-----------------------------------------------------------------//
		static ro16_t<base + 0x1C> ADOCDR;


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

			bit_rw_t<io_, bitpos::B1>  OCSAD;
			bit_rw_t<io_, bitpos::B9>  OCSA;
		};
		static adexicr_t<base + 0x12>  ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(analog an, uint8_t v) {
				wr8_(base + 0xE0 + static_cast<uint32_t>(an), v);
			}
		};
		static adsstr_t ADSSTR;


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
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE4> ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE5> ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE6> ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE7> ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 8（ADSSTR8）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE8> ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 9（ADSSTR9）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xE9> ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 10（ADSSTR10）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xEA> ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 11（ADSSTR11）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0xEB> ADSSTR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }

	};

	typedef s12ad0_t<0x00089000, peripheral::S12AD>  S12AD;
	typedef s12ad1_t<0x00089200, peripheral::S12AD1> S12AD1;
	typedef s12ad2_t<0x00089400, peripheral::S12AD2> S12AD2;
}
