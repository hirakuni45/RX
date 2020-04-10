#pragma once
//=====================================================================//
/*!	@file
	@brief	RX65X グループ・S12ADFa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADC 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adf_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 0（ADDR0）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x20> addr0_t;
		static addr0_t ADDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 1（ADDR1）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x22> addr1_t;
		static addr1_t ADDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 2（ADDR2）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x24> addr2_t;
		static addr2_t ADDR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 3（ADDR3）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x26> addr3_t;
		static addr3_t ADDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 4（ADDR4）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x28> addr4_t;
		static addr4_t ADDR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 5（ADDR5）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2A> addr5_t;
		static addr5_t ADDR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 6（ADDR6）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2C> addr6_t;
		static addr6_t ADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 7（ADDR7）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2E> addr7_t;
		static addr7_t ADDR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x18> addbldr_t;
		static addbldr_t ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ A（ADDBLDRA）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x84> addbldra_t;
		static addbldra_t ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ B（ADDBLDRB）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x86> addbldrb_t;
		static addbldrb_t ADDBLDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 自己診断データレジスタ（ ADRD ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adrd_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12>  AD;
			bits_rw_t<io_, bitpos::B14, 2>  DIAGST;
		};
		typedef adrd_t_<base + 0x1E> adrd_t;
		static adrd_t ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロールレジスタ（ADCSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcsr_t_ : public rw16_t<ofs> {
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
		typedef adcsr_t_<base + 0x00> adcsr_t;
		static adcsr_t ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均回数選択レジスタ（ADADC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adadc_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  ADC;
			bit_rw_t <io_, bitpos::B7>     AVEE;
		};
		typedef adadc_t_<base + 0x0C> adadc_t;
		static adadc_t ADADC;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロール拡張レジスタ（ADCER）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcer_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B1, 2>  ADPRC;
			bit_rw_t <io_, bitpos::B5>     ACE;
			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;
			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		typedef adcer_t_<base + 0x0E> adcer_t;
		static adcer_t ADCER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始トリガ選択レジスタ（ADSTRGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adstrgr_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  TRSB;
			bits_rw_t<io_, bitpos::B8, 6>  TRSA;
		};
		typedef adstrgr_t_<base + 0x10> adstrgr_t;
		static adstrgr_t ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C トリガ選択レジスタ（ ADGCTRGR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgctrgr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  TRSC;
			bit_rw_t <io_, bitpos::B6>     GCADIE;
			bit_rw_t <io_, bitpos::B7>     GRCE;
		};
		typedef adgctrgr_t_<base + 0xD9> adgctrgr_t;
		static adgctrgr_t ADGCTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> adsstr0_t;
		static adsstr0_t ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE1> adsstr1_t;
		static adsstr1_t ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE2> adsstr2_t;
		static adsstr2_t ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE3> adsstr3_t;
		static adsstr3_t ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE4> adsstr4_t;
		static adsstr4_t ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE5> adsstr5_t;
		static adsstr5_t ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE6> adsstr6_t;
		static adsstr6_t ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE7> adsstr7_t;
		static adsstr7_t ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 断線検出コントロールレジスタ（ADDISCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiscr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ADNDIS;
		};
		typedef addiscr_t_<base + 0x7A> addiscr_t;
		static addiscr_t ADDISCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループスキャン優先コントロールレジスタ（ADGSPCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgspcr_t_ : public rw16_t<ofs> {
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
		typedef adgspcr_t_<base + 0x80> adgspcr_t;
		static adgspcr_t ADGSPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアコントロールレジスタ（ ADCMPCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpcr_t_ : public rw16_t<ofs> {
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
		typedef adcmpcr_t_<base + 0x90> adcmpcr_t;
		static adcmpcr_t ADCMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 0 （ ADCMPDR0 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9C> adcmpdr0_t;
		static adcmpdr0_t ADCMPDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 1 （ ADCMPDR1 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9E> adcmpdr1_t;
		static adcmpdr1_t ADCMPDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A/B ステータスモニタレジスタ（ ADWINMON ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adwinmon_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   MONCOMB;

			bit_rw_t<io_, bitpos::B4>   MONCMPA;
			bit_rw_t<io_, bitpos::B5>   MONCMPB;
		};
		typedef adwinmon_t_<base + 0x8C> adwinmon_t;
		static adwinmon_t ADWINMON;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 下位側レベル設定レジスタ（ ADWINLLB ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xA8> adwinllb_t;
		static adwinllb_t ADWINLLB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 上位側レベル設定レジスタ（ ADWINULB ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xAA> adwinulb_t;
		static adwinulb_t ADWINULB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 逐次変換時間設定レジスタ（ ADSAM ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adsam_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B5>   SAM;
		};
		typedef adsam_t_<base + 0x6E> adsam_t;
		static adsam_t ADSAM;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 逐次変換時間設定プロテクト解除レジスタ（ ADSAMPR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adsampr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   PRO;
		};
		typedef adsampr_t_<base + 0x63> adsampr_t;
		static adsampr_t ADSAMPR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD0 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	avec	CMPA 割り込みベクター
		@param[in]	bvec	CMPB 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec>
	struct s12adf0_t_ : public s12adf_t<base> {

		typedef s12adf_t<base> base_class;


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

			uint32_t get_address(analog an) {
				return base + 0x20 + static_cast<uint32_t>(an) * 2;
			}

			uint16_t operator() (analog an) {
				return rd16_(get_address(an));
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
		struct adansa0_t_ : public rw16_t<ofs> {
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
		typedef adansa0_t_<base + 0x04> adansa0_t;
		static adansa0_t ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0（ADANSB0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t_ : public rw16_t<ofs> {
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
		};
		typedef adansb0_t_<base + 0x14> adansb0_t;
		static adansb0_t ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 （ ADANSC0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
			bit_rw_t<io_, bitpos::B4>  ANSC004;
			bit_rw_t<io_, bitpos::B5>  ANSC005;
			bit_rw_t<io_, bitpos::B6>  ANSC006;
			bit_rw_t<io_, bitpos::B7>  ANSC007;
		};
		typedef adansc0_t_<base + 0xD4> adansc0_t;
		static adansc0_t ADANSC0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS) unit0
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t_ {

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
			@brief  A/D チャネル選択レジスタ A0
		*/
		//-----------------------------------------------------------------//
		typedef adans_t_<base + 0x04> adansa_t;
		static adansa_t ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0
		*/
		//-----------------------------------------------------------------//
		typedef adans_t_<base + 0x14> adansb_t;
		static adansb_t ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0
		*/
		//-----------------------------------------------------------------//
		typedef adans_t_<base + 0xD4> adansc_t;
		static adansc_t ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ADS000;
			bit_rw_t<io_, bitpos::B1>  ADS001;
			bit_rw_t<io_, bitpos::B2>  ADS002;
			bit_rw_t<io_, bitpos::B3>  ADS003;
			bit_rw_t<io_, bitpos::B4>  ADS004;
			bit_rw_t<io_, bitpos::B5>  ADS005;
			bit_rw_t<io_, bitpos::B6>  ADS006;
			bit_rw_t<io_, bitpos::B7>  ADS007;
		};
		typedef adads0_t_<base + 0x08> adads0_t;
		static adads0_t ADADS0;


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
			@brief  A/D サンプル & ホールド回路コントロールレジスタ（ADSHCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshcr_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SSTSH;
			bits_rw_t<io_, bitpos::B8, 3>  SHANS;
		};
		typedef adshcr_t_<base + 0x66> adshcr_t;
		static adshcr_t ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプル＆ホールド動作モード選択レジスタ（ ADSHMSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshmsr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SHMD;
		};
		typedef adshmsr_t_<base + 0x7C> adshmsr_t;
		static adshmsr_t ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 0 （ ADCMPANSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPCHA000;
			bit_rw_t<io_, bitpos::B1>  CMPCHA001;
			bit_rw_t<io_, bitpos::B2>  CMPCHA002;
			bit_rw_t<io_, bitpos::B3>  CMPCHA003;
			bit_rw_t<io_, bitpos::B4>  CMPCHA004;
			bit_rw_t<io_, bitpos::B5>  CMPCHA005;
			bit_rw_t<io_, bitpos::B6>  CMPCHA006;
			bit_rw_t<io_, bitpos::B7>  CMPCHA007;
		};
		typedef adcmpansr0_t_<base + 0x94> adcmpansr0_t;
		static adcmpansr0_t ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0 （ ADCMPLR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>  CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>  CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>  CMPLCHA003;
			bit_rw_t<io_, bitpos::B4>  CMPLCHA004;
			bit_rw_t<io_, bitpos::B5>  CMPLCHA005;
			bit_rw_t<io_, bitpos::B6>  CMPLCHA006;
			bit_rw_t<io_, bitpos::B7>  CMPLCHA007;
		};
		typedef adcmplr0_t_<base + 0x98> adcmplr0_t;
		static adcmplr0_t ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0 （ ADCMPSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>  CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>  CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>  CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>  CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>  CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>  CMPSTCHA006;
			bit_rw_t<io_, bitpos::B7>  CMPSTCHA007;
		};
		typedef adcmpsr0_t_<base + 0xA0> adcmpsr0_t;
		static adcmpsr0_t ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ B チャネル選択レジスタ（ ADCMPBNSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbnsr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  CMPCHB;
			bit_rw_t <io_, bitpos::B7>     CMPLB;
		};
		typedef adcmpbnsr_t_<base + 0xA6> adcmpbnsr_t;
		static adcmpbnsr_t ADCMPBNSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ B チャネルステータスレジスタ（ ADCMPBSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbsr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CMPSTB;
		};
		typedef adcmpbsr_t_<base + 0xAC> adcmpbsr_t;
		static adcmpbsr_t ADCMPBSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みベクターＡを返す
			@return スキャン終了割り込みベクターＡ
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BL1 get_cmpa_vec() { return avec; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みベクターＡを返す
			@return スキャン終了割り込みベクターＡ
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BL1 get_cmpb_vec() { return bvec; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	avec	CMPA 割り込みベクター
		@param[in]	bvec	CMPB 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec>
	struct s12adf1_t_ : public s12adf_t<base> {

		typedef s12adf_t<base> base_class;

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
			AINT,		///< 温度センサ
			AINO,		///< 内部基準電圧
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
		typedef ro16_t<base + 0x30> addr8_t;
		static addr8_t ADDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 9（ADDR9）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x32> addr9_t;
		static addr9_t ADDR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 10（ADDR10）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x34> addr10_t;
		static addr10_t ADDR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 11（ADDR11）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x36> addr11_t;
		static addr11_t ADDR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 12（ADDR12）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x38> addr12_t;
		static addr12_t ADDR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 13（ADDR13）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3A> addr13_t;
		static addr13_t ADDR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 14（ADDR14）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3C> addr14_t;
		static addr14_t ADDR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 15（ADDR15）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3E> addr15_t;
		static addr15_t ADDR15;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> addr16_t;
		static addr16_t ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 17（ADDR17）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x42> addr17_t;
		static addr17_t ADDR17;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 18（ADDR18）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x44> addr18_t;
		static addr18_t ADDR18;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 19（ADDR19）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x46> addr19_t;
		static addr19_t ADDR19;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 20（ADDR20）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x48> addr20_t;
		static addr20_t ADDR20;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ（ ADTSDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1A> adtsdr_t;
		static adtsdr_t ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief   A/D 内部基準電圧データレジスタ（ ADOCDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1C> adocdr_t;
		static adocdr_t ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator() (analog an) {
				if(an <= analog::AIN120) {
					return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
				} else {
					uint32_t n = static_cast<uint32_t>(an) - static_cast<uint32_t>(analog::AINT);
					return rd16_(base + 0x1A + n * 2);
				}
			}
		};
		static addr_t ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0 （ ADANSA0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSA000;  ///< AN100
			bit_rw_t<io_, bitpos::B1>   ANSA001;  ///< AN101
			bit_rw_t<io_, bitpos::B2>   ANSA002;  ///< AN102
			bit_rw_t<io_, bitpos::B3>   ANSA003;  ///< AN103
			bit_rw_t<io_, bitpos::B4>   ANSA004;  ///< AN104
			bit_rw_t<io_, bitpos::B5>   ANSA005;  ///< AN105
			bit_rw_t<io_, bitpos::B6>   ANSA006;  ///< AN106
			bit_rw_t<io_, bitpos::B7>   ANSA007;  ///< AN107
			bit_rw_t<io_, bitpos::B8>   ANSA008;  ///< AN108
			bit_rw_t<io_, bitpos::B9>   ANSA009;  ///< AN109
			bit_rw_t<io_, bitpos::B10>  ANSA010;  ///< AN110
			bit_rw_t<io_, bitpos::B11>  ANSA011;  ///< AN111
			bit_rw_t<io_, bitpos::B12>  ANSA012;  ///< AN112
			bit_rw_t<io_, bitpos::B13>  ANSA013;  ///< AN113
			bit_rw_t<io_, bitpos::B14>  ANSA014;  ///< AN114
			bit_rw_t<io_, bitpos::B15>  ANSA015;  ///< AN115
		};
		typedef adansa0_t_<base + 0x04> adansa0_t;
		static adansa0_t ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A1 （ ADANSA1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa1_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSA100;  ///< AN116
			bit_rw_t<io_, bitpos::B1>  ANSA101;  ///< AN117
			bit_rw_t<io_, bitpos::B2>  ANSA102;  ///< AN118
			bit_rw_t<io_, bitpos::B3>  ANSA103;  ///< AN119
			bit_rw_t<io_, bitpos::B4>  ANSA104;  ///< AN120
		};
		typedef adansa1_t_<base + 0x06> adansa1_t;
		static adansa1_t ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0 （ ADANSB0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSB000;  ///< AN100
			bit_rw_t<io_, bitpos::B1>   ANSB001;  ///< AN101
			bit_rw_t<io_, bitpos::B2>   ANSB002;  ///< AN102
			bit_rw_t<io_, bitpos::B3>   ANSB003;  ///< AN103
			bit_rw_t<io_, bitpos::B4>   ANSB004;  ///< AN104
			bit_rw_t<io_, bitpos::B5>   ANSB005;  ///< AN105
			bit_rw_t<io_, bitpos::B6>   ANSB006;  ///< AN106
			bit_rw_t<io_, bitpos::B7>   ANSB007;  ///< AN107
			bit_rw_t<io_, bitpos::B8>   ANSB008;  ///< AN108
			bit_rw_t<io_, bitpos::B9>   ANSB009;  ///< AN109
			bit_rw_t<io_, bitpos::B10>  ANSB010;  ///< AN110
			bit_rw_t<io_, bitpos::B11>  ANSB011;  ///< AN111
			bit_rw_t<io_, bitpos::B12>  ANSB012;  ///< AN112
			bit_rw_t<io_, bitpos::B13>  ANSB013;  ///< AN113
			bit_rw_t<io_, bitpos::B14>  ANSB014;  ///< AN114
			bit_rw_t<io_, bitpos::B15>  ANSB015;  ///< AN115
		};
		typedef adansb0_t_<base + 0x14> adansb0_t;
		static adansb0_t ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1 （ ADANSB1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb1_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSA100;  ///< AN116
			bit_rw_t<io_, bitpos::B1>  ANSA101;  ///< AN117
			bit_rw_t<io_, bitpos::B2>  ANSA102;  ///< AN118
			bit_rw_t<io_, bitpos::B3>  ANSA103;  ///< AN119
			bit_rw_t<io_, bitpos::B4>  ANSA104;  ///< AN120
		};
		typedef adansb1_t_<base + 0x16> adansb1_t;
		static adansb1_t ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 （ ADANSC0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANSC000;  ///< AN100
			bit_rw_t<io_, bitpos::B1>   ANSC001;  ///< AN101
			bit_rw_t<io_, bitpos::B2>   ANSC002;  ///< AN102
			bit_rw_t<io_, bitpos::B3>   ANSC003;  ///< AN103
			bit_rw_t<io_, bitpos::B4>   ANSC004;  ///< AN104
			bit_rw_t<io_, bitpos::B5>   ANSC005;  ///< AN105
			bit_rw_t<io_, bitpos::B6>   ANSC006;  ///< AN106
			bit_rw_t<io_, bitpos::B7>   ANSC007;  ///< AN107
			bit_rw_t<io_, bitpos::B8>   ANSC008;  ///< AN108
			bit_rw_t<io_, bitpos::B9>   ANSC009;  ///< AN109
			bit_rw_t<io_, bitpos::B10>  ANSC010;  ///< AN110
			bit_rw_t<io_, bitpos::B11>  ANSC011;  ///< AN111
			bit_rw_t<io_, bitpos::B12>  ANSC012;  ///< AN112
			bit_rw_t<io_, bitpos::B13>  ANSC013;  ///< AN113
			bit_rw_t<io_, bitpos::B14>  ANSC014;  ///< AN114
			bit_rw_t<io_, bitpos::B15>  ANSC015;  ///< AN115
		};
		typedef adansc0_t_<base + 0xD4> adansc0_t;
		static adansc0_t ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1 （ ADANSC1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC100;  ///< AN116
			bit_rw_t<io_, bitpos::B1>  ANSC101;  ///< AN117
			bit_rw_t<io_, bitpos::B2>  ANSC102;  ///< AN118
			bit_rw_t<io_, bitpos::B3>  ANSC103;  ///< AN119
			bit_rw_t<io_, bitpos::B4>  ANSC104;  ///< AN120
		};
		typedef adansc1_t_<base + 0xD6> adansc1_t;
		static adansc1_t ADANSC1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t_ {
			void set(analog an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t ros = ofs;
				if(n >= 16) {
					n &= 15;
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
				if(n >= 16) {
					n &= 15;
					ros += 2;
				}
				return (rd16_(ros) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ（ADANSA）
		*/
		//-----------------------------------------------------------------//
		typedef adans_t_<base + 0x04> adansa_t;
		static adansa_t ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		typedef adans_t_<base + 0x14> adansb_t;
		static adansb_t ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		typedef adans_t_<base + 0xD4> adansc_t;
		static adansc_t ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS000;  ///< AN100
			bit_rw_t<io_, bitpos::B1>   ADS001;  ///< AN101
			bit_rw_t<io_, bitpos::B2>   ADS002;  ///< AN102
			bit_rw_t<io_, bitpos::B3>   ADS003;  ///< AN103
			bit_rw_t<io_, bitpos::B4>   ADS004;  ///< AN104
			bit_rw_t<io_, bitpos::B5>   ADS005;  ///< AN105
			bit_rw_t<io_, bitpos::B6>   ADS006;  ///< AN106
			bit_rw_t<io_, bitpos::B7>   ADS007;  ///< AN107
			bit_rw_t<io_, bitpos::B8>   ADS008;  ///< AN108
			bit_rw_t<io_, bitpos::B9>   ADS009;  ///< AN109
			bit_rw_t<io_, bitpos::B10>  ADS010;  ///< AN110
			bit_rw_t<io_, bitpos::B11>  ADS011;  ///< AN111
			bit_rw_t<io_, bitpos::B12>  ADS012;  ///< AN112
			bit_rw_t<io_, bitpos::B13>  ADS013;  ///< AN113
			bit_rw_t<io_, bitpos::B14>  ADS014;  ///< AN114
			bit_rw_t<io_, bitpos::B15>  ADS015;  ///< AN115
		};
		typedef adads0_t_<base + 0x08> adads0_t;
		static adads0_t ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均モード選択レジスタ 1 （ ADADS1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads1_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS100;  ///< AN116
			bit_rw_t<io_, bitpos::B1>   ADS101;  ///< AN117
			bit_rw_t<io_, bitpos::B2>   ADS102;  ///< AN118
			bit_rw_t<io_, bitpos::B3>   ADS103;  ///< AN119
			bit_rw_t<io_, bitpos::B4>   ADS104;  ///< AN120
		};
		typedef adads1_t_<base + 0x0A> adads1_t;
		static adads1_t ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換拡張入力コントロールレジスタ（ ADEXICR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adexicr_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      TSSAD;
			bit_rw_t <io_, bitpos::B1>      OCSAD;

			bit_rw_t <io_, bitpos::B8>      TSSA;
			bit_rw_t <io_, bitpos::B9>      OCSA;
			bit_rw_t <io_, bitpos::B10>     TSSB;
			bit_rw_t <io_, bitpos::B11>     OCSB;

			bits_rw_t<io_, bitpos::B13, 2>  EXSEL;
			bit_rw_t <io_, bitpos::B15>     EXOEN;
		};
		typedef adexicr_t_<base + 0x12> adexicr_t;
		static adexicr_t ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D グループ C 拡張入力コントロールレジスタ（ ADGCEXCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgcexcr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      TSSC;
			bit_rw_t <io_, bitpos::B1>      OCSC;
		};
		typedef adgcexcr_t_<base + 0xD8> adgcexcr_t;
		static adgcexcr_t ADGCEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> adsstrl_t;
		static adsstrl_t ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ T（ADSSTRT）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDE> adsstrt_t;
		static adsstrt_t ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDF> adsstro_t;
		static adsstro_t ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 8 （ ADSSTR8 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE8> adsstr8_t;
		static adsstr8_t ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 9 （ ADSSTR9 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE9> adsstr9_t;
		static adsstr9_t ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 10 （ ADSSTR10 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEA> adsstr10_t;
		static adsstr10_t ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 11 （ ADSSTR11 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEB> adsstr11_t;
		static adsstr11_t ADSSTR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 12 （ ADSSTR12 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEC> adsstr12_t;
		static adsstr12_t ADSSTR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 13 （ ADSSTR13 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xED> adsstr13_t;
		static adsstr13_t ADSSTR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 14 （ ADSSTR14 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEE> adsstr14_t;
		static adsstr14_t ADSSTR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 15 （ ADSSTR15 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEF> adsstr15_t;
		static adsstr15_t ADSSTR15;


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
			@brief	A/D コンペアチャネル選択レジスタ 0 （ ADCMPANSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t_ : public rw16_t<ofs> {
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
			bit_rw_t<io_, bitpos::B12>  CMPCHA012;
			bit_rw_t<io_, bitpos::B13>  CMPCHA013;
			bit_rw_t<io_, bitpos::B14>  CMPCHA014;
			bit_rw_t<io_, bitpos::B15>  CMPCHA015;
		};
		typedef adcmpansr0_t_<base + 0x94> adcmpansr0_t;
		static adcmpansr0_t ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 1 （ ADCMPANSR1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr1_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPCHA100;
			bit_rw_t<io_, bitpos::B1>   CMPCHA101;
			bit_rw_t<io_, bitpos::B2>   CMPCHA102;
			bit_rw_t<io_, bitpos::B3>   CMPCHA103;
			bit_rw_t<io_, bitpos::B4>   CMPCHA104;
		};
		typedef adcmpansr1_t_<base + 0x96> adcmpansr1_t;
		static adcmpansr1_t ADCMPANSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択拡張レジスタ（ ADCMPANSER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpanser_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CMPSTS;
			bit_rw_t <io_, bitpos::B1>  CMPSOC;
		};
		typedef adcmpanser_t_<base + 0x92> adcmpanser_t;
		static adcmpanser_t ADCMPANSER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0 （ ADCMPLR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t_ : public rw16_t<ofs> {
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
			bit_rw_t<io_, bitpos::B12>  CMPLCHA012;
			bit_rw_t<io_, bitpos::B13>  CMPLCHA013;
			bit_rw_t<io_, bitpos::B14>  CMPLCHA014;
			bit_rw_t<io_, bitpos::B15>  CMPLCHA015;
		};
		typedef adcmplr0_t_<base + 0x98> adcmplr0_t;
		static adcmplr0_t ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 1 （ ADCMPLR1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr1_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPLCHA100;
			bit_rw_t<io_, bitpos::B1>   CMPLCHA101;
			bit_rw_t<io_, bitpos::B2>   CMPLCHA102;
			bit_rw_t<io_, bitpos::B3>   CMPLCHA103;
			bit_rw_t<io_, bitpos::B4>   CMPLCHA104;
		};
		typedef adcmplr1_t_<base + 0x9A> adcmplr1_t;
		static adcmplr1_t ADCMPLR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベル拡張レジスタ（ ADCMPLER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpler_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPLTS;
			bit_rw_t<io_, bitpos::B0>  CMPLOC;
		};
		typedef adcmpler_t_<base + 0x93> adcmpler_t;
		static adcmpler_t ADCMPLER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0 （ ADCMPSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t_ : public rw16_t<ofs> {
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
			bit_rw_t<io_, bitpos::B12>  CMPSTCHA012;
			bit_rw_t<io_, bitpos::B13>  CMPSTCHA013;
			bit_rw_t<io_, bitpos::B14>  CMPSTCHA014;
			bit_rw_t<io_, bitpos::B15>  CMPSTCHA015;
		};
		typedef adcmpsr0_t_<base + 0xA0> adcmpsr0_t;
		static adcmpsr0_t ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 1 （ ADCMPSR1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr1_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA100;
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA101;
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA102;
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA103;
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA104;
		};
		typedef adcmpsr1_t_<base + 0xA2> adcmpsr1_t;
		static adcmpsr1_t ADCMPSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータス拡張レジスタ（ ADCMPSER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpser_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPFTS;
			bit_rw_t<io_, bitpos::B1>  CMPFOC;
		};
		typedef adcmpser_t_<base + 0xA4> adcmpser_t;
		static adcmpser_t ADCMPSER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ B チャネル選択レジスタ（ ADCMPBNSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbnsr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  CMPCHB;
			bit_rw_t <io_, bitpos::B7>     CMPLB;
		};
		typedef adcmpbnsr_t_<base + 0xA6> adcmpbnsr_t;
		static adcmpbnsr_t ADCMPBNSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ B チャネルステータスレジスタ（ ADCMPBSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpbsr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>    CMPSTB;
		};
		typedef adcmpbsr_t_<base + 0xAC> adcmpbsr_t;
		static adcmpbsr_t ADCMPBSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みベクターＡを返す
			@return スキャン終了割り込みベクターＡ
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BL1 get_cmpa_vec() { return avec; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みベクターＡを返す
			@return スキャン終了割り込みベクターＡ
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BL1 get_cmpb_vec() { return bvec; }
	};

	typedef s12adf0_t_<0x00089000, peripheral::S12AD,
		ICU::VECTOR_BL1::S12CMPAI,  ICU::VECTOR_BL1::S12CMPBI>   S12AD;
	typedef s12adf1_t_<0x00089100, peripheral::S12AD1,
		ICU::VECTOR_BL1::S12CMPAI1, ICU::VECTOR_BL1::S12CMPBI1>  S12AD1;
 
	template <uint32_t base> typename s12adf_t<base>::addr0_t s12adf_t<base>::ADDR0;
	template <uint32_t base> typename s12adf_t<base>::addr1_t s12adf_t<base>::ADDR1;
	template <uint32_t base> typename s12adf_t<base>::addr2_t s12adf_t<base>::ADDR2;
	template <uint32_t base> typename s12adf_t<base>::addr3_t s12adf_t<base>::ADDR3;
	template <uint32_t base> typename s12adf_t<base>::addr4_t s12adf_t<base>::ADDR4;
	template <uint32_t base> typename s12adf_t<base>::addr5_t s12adf_t<base>::ADDR5;
	template <uint32_t base> typename s12adf_t<base>::addr6_t s12adf_t<base>::ADDR6;
	template <uint32_t base> typename s12adf_t<base>::addr7_t s12adf_t<base>::ADDR7;
	template <uint32_t base> typename s12adf_t<base>::addbldr_t s12adf_t<base>::ADDBLDR;
	template <uint32_t base> typename s12adf_t<base>::addbldra_t s12adf_t<base>::ADDBLDRA;
	template <uint32_t base> typename s12adf_t<base>::addbldrb_t s12adf_t<base>::ADDBLDRB;
	template <uint32_t base> typename s12adf_t<base>::adrd_t s12adf_t<base>::ADRD;
	template <uint32_t base> typename s12adf_t<base>::adcsr_t s12adf_t<base>::ADCSR;
	template <uint32_t base> typename s12adf_t<base>::adadc_t s12adf_t<base>::ADADC;
	template <uint32_t base> typename s12adf_t<base>::adcer_t s12adf_t<base>::ADCER;
	template <uint32_t base> typename s12adf_t<base>::adstrgr_t s12adf_t<base>::ADSTRGR;
	template <uint32_t base> typename s12adf_t<base>::adgctrgr_t s12adf_t<base>::ADGCTRGR;
	template <uint32_t base> typename s12adf_t<base>::adsstr0_t s12adf_t<base>::ADSSTR0;
	template <uint32_t base> typename s12adf_t<base>::adsstr1_t s12adf_t<base>::ADSSTR1;
	template <uint32_t base> typename s12adf_t<base>::adsstr2_t s12adf_t<base>::ADSSTR2;
	template <uint32_t base> typename s12adf_t<base>::adsstr3_t s12adf_t<base>::ADSSTR3;
	template <uint32_t base> typename s12adf_t<base>::adsstr4_t s12adf_t<base>::ADSSTR4;
	template <uint32_t base> typename s12adf_t<base>::adsstr5_t s12adf_t<base>::ADSSTR5;
	template <uint32_t base> typename s12adf_t<base>::adsstr6_t s12adf_t<base>::ADSSTR6;
	template <uint32_t base> typename s12adf_t<base>::adsstr7_t s12adf_t<base>::ADSSTR7;
	template <uint32_t base> typename s12adf_t<base>::addiscr_t s12adf_t<base>::ADDISCR;
	template <uint32_t base> typename s12adf_t<base>::adgspcr_t s12adf_t<base>::ADGSPCR;
	template <uint32_t base> typename s12adf_t<base>::adcmpcr_t s12adf_t<base>::ADCMPCR;
	template <uint32_t base> typename s12adf_t<base>::adcmpdr0_t s12adf_t<base>::ADCMPDR0;
	template <uint32_t base> typename s12adf_t<base>::adcmpdr1_t s12adf_t<base>::ADCMPDR1;
	template <uint32_t base> typename s12adf_t<base>::adwinmon_t s12adf_t<base>::ADWINMON;
	template <uint32_t base> typename s12adf_t<base>::adwinllb_t s12adf_t<base>::ADWINLLB;
	template <uint32_t base> typename s12adf_t<base>::adwinulb_t s12adf_t<base>::ADWINULB;
	template <uint32_t base> typename s12adf_t<base>::adsam_t s12adf_t<base>::ADSAM;
	template <uint32_t base> typename s12adf_t<base>::adsampr_t s12adf_t<base>::ADSAMPR;

	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::addr_t s12adf0_t_<base, per, avec, bvec>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adansa0_t s12adf0_t_<base, per, avec, bvec>::ADANSA0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adansb0_t s12adf0_t_<base, per, avec, bvec>::ADANSB0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adansc0_t s12adf0_t_<base, per, avec, bvec>::ADANSC0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adansa_t s12adf0_t_<base, per, avec, bvec>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adansb_t s12adf0_t_<base, per, avec, bvec>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adansc_t s12adf0_t_<base, per, avec, bvec>::ADANSC;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adads0_t s12adf0_t_<base, per, avec, bvec>::ADADS0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adsstr_t s12adf0_t_<base, per, avec, bvec>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adshcr_t s12adf0_t_<base, per, avec, bvec>::ADSHCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adshmsr_t s12adf0_t_<base, per, avec, bvec>::ADSHMSR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adcmpansr0_t s12adf0_t_<base, per, avec, bvec>::ADCMPANSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adcmplr0_t s12adf0_t_<base, per, avec, bvec>::ADCMPLR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adcmpsr0_t s12adf0_t_<base, per, avec, bvec>::ADCMPSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adcmpbnsr_t s12adf0_t_<base, per, avec, bvec>::ADCMPBNSR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf0_t_<base, per, avec, bvec> ::adcmpbsr_t s12adf0_t_<base, per, avec, bvec>::ADCMPBSR;

	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr8_t s12adf1_t_<base, per, avec, bvec>::ADDR8;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr9_t s12adf1_t_<base, per, avec, bvec>::ADDR9;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr10_t s12adf1_t_<base, per, avec, bvec>::ADDR10;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr11_t s12adf1_t_<base, per, avec, bvec>::ADDR11;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr12_t s12adf1_t_<base, per, avec, bvec>::ADDR12;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr13_t s12adf1_t_<base, per, avec, bvec>::ADDR13;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr14_t s12adf1_t_<base, per, avec, bvec>::ADDR14;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr15_t s12adf1_t_<base, per, avec, bvec>::ADDR15;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr16_t s12adf1_t_<base, per, avec, bvec>::ADDR16;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr17_t s12adf1_t_<base, per, avec, bvec>::ADDR17;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr18_t s12adf1_t_<base, per, avec, bvec>::ADDR18;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr19_t s12adf1_t_<base, per, avec, bvec>::ADDR19;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr20_t s12adf1_t_<base, per, avec, bvec>::ADDR20;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adtsdr_t s12adf1_t_<base, per, avec, bvec>::ADTSDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adocdr_t s12adf1_t_<base, per, avec, bvec>::ADOCDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::addr_t s12adf1_t_<base, per, avec, bvec>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansa0_t s12adf1_t_<base, per, avec, bvec>::ADANSA0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansa1_t s12adf1_t_<base, per, avec, bvec>::ADANSA1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansb0_t s12adf1_t_<base, per, avec, bvec>::ADANSB0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansb1_t s12adf1_t_<base, per, avec, bvec>::ADANSB1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansc0_t s12adf1_t_<base, per, avec, bvec>::ADANSC0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansc1_t s12adf1_t_<base, per, avec, bvec>::ADANSC1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansa_t s12adf1_t_<base, per, avec, bvec>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansb_t s12adf1_t_<base, per, avec, bvec>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adansc_t s12adf1_t_<base, per, avec, bvec>::ADANSC;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adads0_t s12adf1_t_<base, per, avec, bvec>::ADADS0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adads1_t s12adf1_t_<base, per, avec, bvec>::ADADS1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adexicr_t s12adf1_t_<base, per, avec, bvec>::ADEXICR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adgcexcr_t s12adf1_t_<base, per, avec, bvec>::ADGCEXCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstrl_t s12adf1_t_<base, per, avec, bvec>::ADSSTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstrt_t s12adf1_t_<base, per, avec, bvec>::ADSSTRT;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstro_t s12adf1_t_<base, per, avec, bvec>::ADSSTRO;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr8_t s12adf1_t_<base, per, avec, bvec>::ADSSTR8;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr9_t s12adf1_t_<base, per, avec, bvec>::ADSSTR9;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr10_t s12adf1_t_<base, per, avec, bvec>::ADSSTR10;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr11_t s12adf1_t_<base, per, avec, bvec>::ADSSTR11;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr12_t s12adf1_t_<base, per, avec, bvec>::ADSSTR12;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr13_t s12adf1_t_<base, per, avec, bvec>::ADSSTR13;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr14_t s12adf1_t_<base, per, avec, bvec>::ADSSTR14;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr15_t s12adf1_t_<base, per, avec, bvec>::ADSSTR15;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adsstr_t s12adf1_t_<base, per, avec, bvec>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpansr0_t s12adf1_t_<base, per, avec, bvec>::ADCMPANSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpansr1_t s12adf1_t_<base, per, avec, bvec>::ADCMPANSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpanser_t s12adf1_t_<base, per, avec, bvec>::ADCMPANSER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmplr0_t s12adf1_t_<base, per, avec, bvec>::ADCMPLR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmplr1_t s12adf1_t_<base, per, avec, bvec>::ADCMPLR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpler_t s12adf1_t_<base, per, avec, bvec>::ADCMPLER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpsr0_t s12adf1_t_<base, per, avec, bvec>::ADCMPSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpsr1_t s12adf1_t_<base, per, avec, bvec>::ADCMPSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpser_t s12adf1_t_<base, per, avec, bvec>::ADCMPSER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpbnsr_t s12adf1_t_<base, per, avec, bvec>::ADCMPBNSR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 avec, ICU::VECTOR_BL1 bvec> typename s12adf1_t_<base, per, avec, bvec> ::adcmpbsr_t s12adf1_t_<base, per, avec, bvec>::ADCMPBSR;
}
