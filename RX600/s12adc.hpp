#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・S12ADC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"

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

			bits_rw_t<io_, bitpos::B0, 2>  ADC;
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ x（ADSSTRx）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adsstrx_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SST;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x60> adsstr0_t;
		static adsstr0_t ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x73> adsstr1_t;
		static adsstr1_t ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x74> adsstr2_t;
		static adsstr2_t ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x75> adsstr3_t;
		static adsstr3_t ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x76> adsstr4_t;
		static adsstr4_t ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x77> adsstr5_t;
		static adsstr5_t ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x78> adsstr6_t;
		static adsstr6_t ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t_<base + 0x79> adsstr7_t;
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
		struct adcmpcr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B6>   WCMPE;
			bit_rw_t <io_, bitpos::B7>   CMPIE;
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
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD0 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec>
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
			@brief  A/D チャネル選択レジスタ設定 A
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

			bits_rw_t <io_, bitpos::B0, 8>  CMPS0;
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

			bits_rw_t<io_, bitpos::B0, 8>  CMPL0;
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

			bits_rw_t<io_, bitpos::B0, 8>  CMPF0;
		};
		typedef adcmpsr0_t_<base + 0xA0> adcmpsr0_t;
		static adcmpsr0_t ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みＡベクターを返す
			@return スキャン終了割り込みＡベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BL1 get_cmpa_vec() { return ivec; }

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec>
	struct s12ad1_t : public s12adc_t<base> {

		typedef s12adc_t<base> base_class;

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
		typedef ro16_t<base + 0x01C> adocdr_t;
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
		struct adansa0_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSA100;
			bit_rw_t<io_, bitpos::B1>  ANSA101;
			bit_rw_t<io_, bitpos::B2>  ANSA102;
			bit_rw_t<io_, bitpos::B3>  ANSA103;
			bit_rw_t<io_, bitpos::B4>  ANSA104;
			bit_rw_t<io_, bitpos::B5>  ANSA105;
			bit_rw_t<io_, bitpos::B6>  ANSA106;
			bit_rw_t<io_, bitpos::B7>  ANSA107;
			bit_rw_t<io_, bitpos::B8>  ANSA108;
			bit_rw_t<io_, bitpos::B9>  ANSA109;
			bit_rw_t<io_, bitpos::B10> ANSA110;
			bit_rw_t<io_, bitpos::B11> ANSA111;
			bit_rw_t<io_, bitpos::B12> ANSA112;
			bit_rw_t<io_, bitpos::B13> ANSA113;
			bit_rw_t<io_, bitpos::B14> ANSA114;
			bit_rw_t<io_, bitpos::B15> ANSA115;
		};
		typedef adansa0_t_<base + 0x04> adansa0_t;
		static adansa0_t ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A1（ADANSA1）
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

			bit_rw_t<io_, bitpos::B0>  ANSA116;
			bit_rw_t<io_, bitpos::B1>  ANSA117;
			bit_rw_t<io_, bitpos::B2>  ANSA118;
			bit_rw_t<io_, bitpos::B3>  ANSA119;
			bit_rw_t<io_, bitpos::B4>  ANSA120;
		};
		typedef adansa1_t_<base + 0x06> adansa1_t;
		static adansa1_t ADANSA1;


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

			bit_rw_t<io_, bitpos::B0>  ANSB100;
			bit_rw_t<io_, bitpos::B1>  ANSB101;
			bit_rw_t<io_, bitpos::B2>  ANSB102;
			bit_rw_t<io_, bitpos::B3>  ANSB103;
			bit_rw_t<io_, bitpos::B4>  ANSB104;
			bit_rw_t<io_, bitpos::B5>  ANSB105;
			bit_rw_t<io_, bitpos::B6>  ANSB106;
			bit_rw_t<io_, bitpos::B7>  ANSB107;
			bit_rw_t<io_, bitpos::B8>  ANSB108;
			bit_rw_t<io_, bitpos::B9>  ANSB109;
			bit_rw_t<io_, bitpos::B10> ANSB110;
			bit_rw_t<io_, bitpos::B11> ANSB111;
			bit_rw_t<io_, bitpos::B12> ANSB112;
			bit_rw_t<io_, bitpos::B13> ANSB113;
			bit_rw_t<io_, bitpos::B14> ANSB114;
			bit_rw_t<io_, bitpos::B15> ANSB115;
		};
		typedef adansb0_t_<base + 0x14> adansb0_t;
		static adansb0_t ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		typedef adans_t_<base + 0x14> adansb_t;
		static adansb_t ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1（ADANSB1）
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

			bit_rw_t<io_, bitpos::B0>  ANSB116;
			bit_rw_t<io_, bitpos::B1>  ANSB117;
			bit_rw_t<io_, bitpos::B2>  ANSB118;
			bit_rw_t<io_, bitpos::B3>  ANSB119;
			bit_rw_t<io_, bitpos::B4>  ANSB120;
		};
		typedef adansb1_t_<base + 0x16> adansb1_t;
		static adansb1_t ADANSB1;


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

			bit_rw_t<io_, bitpos::B0>   ADS100;
			bit_rw_t<io_, bitpos::B1>   ADS101;
			bit_rw_t<io_, bitpos::B2>   ADS102;
			bit_rw_t<io_, bitpos::B3>   ADS103;
			bit_rw_t<io_, bitpos::B4>   ADS104;
			bit_rw_t<io_, bitpos::B5>   ADS105;
			bit_rw_t<io_, bitpos::B6>   ADS106;
			bit_rw_t<io_, bitpos::B7>   ADS107;
			bit_rw_t<io_, bitpos::B8>   ADS108;
			bit_rw_t<io_, bitpos::B9>   ADS109;
			bit_rw_t<io_, bitpos::B10>  ADS110;
			bit_rw_t<io_, bitpos::B11>  ADS111;
			bit_rw_t<io_, bitpos::B12>  ADS112;
			bit_rw_t<io_, bitpos::B13>  ADS113;
			bit_rw_t<io_, bitpos::B14>  ADS114;
			bit_rw_t<io_, bitpos::B15>  ADS115;
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

			bit_rw_t<io_, bitpos::B0>   ADS116;
			bit_rw_t<io_, bitpos::B1>   ADS117;
			bit_rw_t<io_, bitpos::B2>   ADS118;
			bit_rw_t<io_, bitpos::B3>   ADS119;
			bit_rw_t<io_, bitpos::B4>   ADS120;
		};
		typedef adads1_t_<base + 0x10> adads1_t;
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

			bit_rw_t<io_, bitpos::B0>      TSSAD;
			bit_rw_t<io_, bitpos::B1>      OCSAD;

			bit_rw_t<io_, bitpos::B8>      TSSA;
			bit_rw_t<io_, bitpos::B9>      OCSA;
			bit_rw_t<io_, bitpos::B10>     TSSB;
			bit_rw_t<io_, bitpos::B11>     OCSB;

			bits_rw_t<io_, bitpos::B13, 2> EXSEL;
			bit_rw_t<io_, bitpos::B15>     EXOEN;
		};
		typedef adexicr_t_<base + 0x12> adexicr_t;
		static adexicr_t ADEXICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ x（ADSSTRx）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adsstrx_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SST;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x61> adsstrl_t;
		static adsstrl_t ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ T（ADSSTRT）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x70> adsstrt_t;
		static adsstrt_t ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x71> adsstro_t;
		static adsstro_t ADSSTRO;


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

			bits_rw_t <io_, bitpos::B0, 16>  CMPS0;
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

			bits_rw_t <io_, bitpos::B0, 5>  CMPS1;
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

			bits_rw_t<io_, bitpos::B0, 16>  CMPL0;
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

			bits_rw_t<io_, bitpos::B0, 5>  CMPL1;
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

			bits_rw_t<io_, bitpos::B0, 16>  CMPF0;
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

			bits_rw_t<io_, bitpos::B0, 5>  CMPF1;
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
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スキャン終了割り込みＡベクターを返す
			@return スキャン終了割り込みＡベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BL1 get_cmpa_vec() { return ivec; }
	};

	typedef s12ad0_t<0x00089000, peripheral::S12AD,  ICU::VECTOR_BL1::S12CMPAI>   S12AD;
	typedef s12ad1_t<0x00089100, peripheral::S12AD1, ICU::VECTOR_BL1::S12CMPAI1>  S12AD1;

	template<uint32_t base> typename s12adc_t<base>::addr0_t s12adc_t<base>::ADDR0;
	template<uint32_t base> typename s12adc_t<base>::addr1_t s12adc_t<base>::ADDR1;
	template<uint32_t base> typename s12adc_t<base>::addr2_t s12adc_t<base>::ADDR2;
	template<uint32_t base> typename s12adc_t<base>::addr3_t s12adc_t<base>::ADDR3;
	template<uint32_t base> typename s12adc_t<base>::addr4_t s12adc_t<base>::ADDR4;
	template<uint32_t base> typename s12adc_t<base>::addr5_t s12adc_t<base>::ADDR5;
	template<uint32_t base> typename s12adc_t<base>::addr6_t s12adc_t<base>::ADDR6;
	template<uint32_t base> typename s12adc_t<base>::addr7_t s12adc_t<base>::ADDR7;
	template<uint32_t base> typename s12adc_t<base>::addbldr_t s12adc_t<base>::ADDBLDR;
	template<uint32_t base> typename s12adc_t<base>::addbldra_t s12adc_t<base>::ADDBLDRA;
	template<uint32_t base> typename s12adc_t<base>::addbldrb_t s12adc_t<base>::ADDBLDRB;
	template<uint32_t base> typename s12adc_t<base>::adrd_t s12adc_t<base>::ADRD;
	template<uint32_t base> typename s12adc_t<base>::adcsr_t s12adc_t<base>::ADCSR;
	template<uint32_t base> typename s12adc_t<base>::adadc_t s12adc_t<base>::ADADC;
	template<uint32_t base> typename s12adc_t<base>::adcer_t s12adc_t<base>::ADCER;
	template<uint32_t base> typename s12adc_t<base>::adstrgr_t s12adc_t<base>::ADSTRGR;
	template<uint32_t base> typename s12adc_t<base>::adsstr0_t s12adc_t<base>::ADSSTR0;
	template<uint32_t base> typename s12adc_t<base>::adsstr1_t s12adc_t<base>::ADSSTR1;
	template<uint32_t base> typename s12adc_t<base>::adsstr2_t s12adc_t<base>::ADSSTR2;
	template<uint32_t base> typename s12adc_t<base>::adsstr3_t s12adc_t<base>::ADSSTR3;
	template<uint32_t base> typename s12adc_t<base>::adsstr4_t s12adc_t<base>::ADSSTR4;
	template<uint32_t base> typename s12adc_t<base>::adsstr5_t s12adc_t<base>::ADSSTR5;
	template<uint32_t base> typename s12adc_t<base>::adsstr6_t s12adc_t<base>::ADSSTR6;
	template<uint32_t base> typename s12adc_t<base>::adsstr7_t s12adc_t<base>::ADSSTR7;
	template<uint32_t base> typename s12adc_t<base>::addiscr_t s12adc_t<base>::ADDISCR;
	template<uint32_t base> typename s12adc_t<base>::adgspcr_t s12adc_t<base>::ADGSPCR;
	template<uint32_t base> typename s12adc_t<base>::adcmpcr_t s12adc_t<base>::ADCMPCR;
	template<uint32_t base> typename s12adc_t<base>::adcmpdr0_t s12adc_t<base>::ADCMPDR0;
	template<uint32_t base> typename s12adc_t<base>::adcmpdr1_t s12adc_t<base>::ADCMPDR1;

	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::addr_t s12ad0_t<base, per, ivec>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adansa0_t s12ad0_t<base, per, ivec>::ADANSA0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adansa_t s12ad0_t<base, per, ivec>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adansb_t s12ad0_t<base, per, ivec>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adansb0_t s12ad0_t<base, per, ivec>::ADANSB0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adads0_t s12ad0_t<base, per, ivec>::ADADS0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adsstr_t s12ad0_t<base, per, ivec>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adshcr_t s12ad0_t<base, per, ivec>::ADSHCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adshmsr_t s12ad0_t<base, per, ivec>::ADSHMSR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adcmpansr0_t s12ad0_t<base, per, ivec>::ADCMPANSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adcmplr0_t s12ad0_t<base, per, ivec>::ADCMPLR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad0_t<base, per, ivec>::adcmpsr0_t s12ad0_t<base, per, ivec>::ADCMPSR0;

	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr8_t s12ad1_t<base, per, ivec>::ADDR8;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr9_t s12ad1_t<base, per, ivec>::ADDR9;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr10_t s12ad1_t<base, per, ivec>::ADDR10;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr11_t s12ad1_t<base, per, ivec>::ADDR11;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr12_t s12ad1_t<base, per, ivec>::ADDR12;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr13_t s12ad1_t<base, per, ivec>::ADDR13;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr14_t s12ad1_t<base, per, ivec>::ADDR14;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr15_t s12ad1_t<base, per, ivec>::ADDR15;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr16_t s12ad1_t<base, per, ivec>::ADDR16;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr17_t s12ad1_t<base, per, ivec>::ADDR17;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr18_t s12ad1_t<base, per, ivec>::ADDR18;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr19_t s12ad1_t<base, per, ivec>::ADDR19;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr20_t s12ad1_t<base, per, ivec>::ADDR20;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adtsdr_t s12ad1_t<base, per, ivec>::ADTSDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adocdr_t s12ad1_t<base, per, ivec>::ADOCDR;

	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::addr_t s12ad1_t<base, per, ivec>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adansa0_t s12ad1_t<base, per, ivec>::ADANSA0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adansa1_t s12ad1_t<base, per, ivec>::ADANSA1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adansa_t s12ad1_t<base, per, ivec>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adansb0_t s12ad1_t<base, per, ivec>::ADANSB0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adansb_t s12ad1_t<base, per, ivec>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adansb1_t s12ad1_t<base, per, ivec>::ADANSB1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adads0_t s12ad1_t<base, per, ivec>::ADADS0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adads1_t s12ad1_t<base, per, ivec>::ADADS1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adexicr_t s12ad1_t<base, per, ivec>::ADEXICR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adsstrl_t s12ad1_t<base, per, ivec>::ADSSTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adsstrt_t s12ad1_t<base, per, ivec>::ADSSTRT;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adsstro_t s12ad1_t<base, per, ivec>::ADSSTRO;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adsstr_t s12ad1_t<base, per, ivec>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmpansr0_t s12ad1_t<base, per, ivec>::ADCMPANSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmpansr1_t s12ad1_t<base, per, ivec>::ADCMPANSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmpanser_t s12ad1_t<base, per, ivec>::ADCMPANSER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmplr0_t s12ad1_t<base, per, ivec>::ADCMPLR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmplr1_t s12ad1_t<base, per, ivec>::ADCMPLR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmpler_t s12ad1_t<base, per, ivec>::ADCMPLER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmpsr0_t s12ad1_t<base, per, ivec>::ADCMPSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmpsr1_t s12ad1_t<base, per, ivec>::ADCMPSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 ivec> typename s12ad1_t<base, per, ivec>::adcmpser_t s12ad1_t<base, per, ivec>::ADCMPSER;
}
