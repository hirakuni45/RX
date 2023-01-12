#pragma once
//=========================================================================//
/*!	@file
	@brief	RX651/RX65N/RX72N/RX72M グループ・S12ADFa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADF 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adf_base_t {

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
			@brief  A/D データ 2 重化レジスタ（ADDBLDR）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x18> ADDBLDR_;
		static  ADDBLDR_ ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ A（ADDBLDRA）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x84> ADDBLDRA_;
		static  ADDBLDRA_ ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ B（ADDBLDRB）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x86> ADDBLDRB_;
		static  ADDBLDRB_ ADDBLDRB;


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
		typedef adrd_t<base + 0x1E>  ADRD_;
		static  ADRD_ ADRD;


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

			bits_rw_t<io_, bitpos::B0, 3>  ADC;

			bit_rw_t <io_, bitpos::B7>     AVEE;
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

			bits_rw_t<io_, bitpos::B1, 2>  ADPRC;

			bit_rw_t <io_, bitpos::B5>     ACE;

			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;

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

			bits_rw_t<io_, bitpos::B0, 6>  TRSB;

			bits_rw_t<io_, bitpos::B8, 6>  TRSA;
		};
		typedef adstrgr_t<base + 0x10>  ADSTRGR_;
		static  ADSTRGR_ ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C トリガ選択レジスタ（ ADGCTRGR ）
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
		typedef adgctrgr_t<base + 0xD9>  ADGCTRGR_;
		static  ADGCTRGR_ ADGCTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE1> ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE2> ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE3> ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE4> ADSSTR4_;
		static  ADSSTR4_ ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE5> ADSSTR5_;
		static  ADSSTR5_ ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE6> ADSSTR6_;
		static  ADSSTR6_ ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE7> ADSSTR7_;
		static  ADSSTR7_ ADSSTR7;


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
		typedef addiscr_t<base + 0x7A>  ADDISCR_;
		static  ADDISCR_ ADDISCR;


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
		typedef adgspcr_t<base + 0x80>  ADGSPCR_;
		static  ADGSPCR_ ADGSPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアコントロールレジスタ（ADCMPCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CMPAB;

			bit_rw_t <io_, bitpos::B9>    CMPBE;

			bit_rw_t <io_, bitpos::B11>   CMPAE;

			bit_rw_t <io_, bitpos::B13>   CMPBIE;
			bit_rw_t <io_, bitpos::B14>   WCMPE;
			bit_rw_t <io_, bitpos::B15>   CMPAIE;
		};
		typedef adcmpcr_t<base + 0x90>  ADCMPCR_;
		static  ADCMPCR_ ADCMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 0 （ADCMPDR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9C> ADCMPDR0_;
		static  ADCMPDR0_ ADCMPDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 1 （ADCMPDR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9E> ADCMPDR1_;
		static  ADCMPDR1_ ADCMPDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ A/B ステータスモニタレジスタ（ADWINMON）
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
		typedef adwinmon_t<base + 0x8C>  ADWINMON_;
		static  ADWINMON_ ADWINMON;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B チャネル選択レジスタ（ADCMPBNSR）
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

			bits_rw_t<io_, bitpos::B0, 6> CMPCHB;

			bit_rw_t <io_, bitpos::B7>    CMPLB;
		};
		typedef adcmpbnsr_t<base + 0xA6>  ADCMPBNSR_;
		static  ADCMPBNSR_ ADCMPBNSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 下位側レベル設定レジスタ（ ADWINLLB ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xA8> ADWINLLB_;
		static  ADWINLLB_ ADWINLLB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B 上位側レベル設定レジスタ（ ADWINULB ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xAA> ADWINULB_;
		static  ADWINULB_ ADWINULB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペア機能ウィンドウ B チャネルステータスレジスタ（ADCMPBSR）
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
		typedef adcmpbsr_t<base + 0xAC>  ADCMPBSR_;
		static  ADCMPBSR_ ADCMPBSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 逐次変換時間設定レジスタ（ ADSAM ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adsam_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B5>   SAM;
		};
		typedef adsam_t<base + 0x6E>  ADSAM_;
		static  ADSAM_ ADSAM;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 逐次変換時間設定プロテクト解除レジスタ（ ADSAMPR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adsampr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   PRO;
		};
		typedef adsampr_t<base + 0x63>  ADSAMPR_;
		static  ADSAMPR_ ADSAMPR;
	};
	template <uint32_t base> typename s12adf_base_t<base>::ADDR0_ s12adf_base_t<base>::ADDR0;
	template <uint32_t base> typename s12adf_base_t<base>::ADDR1_ s12adf_base_t<base>::ADDR1;
	template <uint32_t base> typename s12adf_base_t<base>::ADDR2_ s12adf_base_t<base>::ADDR2;
	template <uint32_t base> typename s12adf_base_t<base>::ADDR3_ s12adf_base_t<base>::ADDR3;
	template <uint32_t base> typename s12adf_base_t<base>::ADDR4_ s12adf_base_t<base>::ADDR4;
	template <uint32_t base> typename s12adf_base_t<base>::ADDR5_ s12adf_base_t<base>::ADDR5;
	template <uint32_t base> typename s12adf_base_t<base>::ADDR6_ s12adf_base_t<base>::ADDR6;
	template <uint32_t base> typename s12adf_base_t<base>::ADDR7_ s12adf_base_t<base>::ADDR7;
	template <uint32_t base> typename s12adf_base_t<base>::ADDBLDR_ s12adf_base_t<base>::ADDBLDR;
	template <uint32_t base> typename s12adf_base_t<base>::ADDBLDRA_ s12adf_base_t<base>::ADDBLDRA;
	template <uint32_t base> typename s12adf_base_t<base>::ADDBLDRB_ s12adf_base_t<base>::ADDBLDRB;
	template <uint32_t base> typename s12adf_base_t<base>::ADRD_ s12adf_base_t<base>::ADRD;
	template <uint32_t base> typename s12adf_base_t<base>::ADCSR_ s12adf_base_t<base>::ADCSR;
	template <uint32_t base> typename s12adf_base_t<base>::ADADC_ s12adf_base_t<base>::ADADC;
	template <uint32_t base> typename s12adf_base_t<base>::ADCER_ s12adf_base_t<base>::ADCER;
	template <uint32_t base> typename s12adf_base_t<base>::ADSTRGR_ s12adf_base_t<base>::ADSTRGR;
	template <uint32_t base> typename s12adf_base_t<base>::ADGCTRGR_ s12adf_base_t<base>::ADGCTRGR;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR0_ s12adf_base_t<base>::ADSSTR0;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR1_ s12adf_base_t<base>::ADSSTR1;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR2_ s12adf_base_t<base>::ADSSTR2;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR3_ s12adf_base_t<base>::ADSSTR3;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR4_ s12adf_base_t<base>::ADSSTR4;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR5_ s12adf_base_t<base>::ADSSTR5;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR6_ s12adf_base_t<base>::ADSSTR6;
	template <uint32_t base> typename s12adf_base_t<base>::ADSSTR7_ s12adf_base_t<base>::ADSSTR7;
	template <uint32_t base> typename s12adf_base_t<base>::ADDISCR_ s12adf_base_t<base>::ADDISCR;
	template <uint32_t base> typename s12adf_base_t<base>::ADGSPCR_ s12adf_base_t<base>::ADGSPCR;
	template <uint32_t base> typename s12adf_base_t<base>::ADCMPCR_ s12adf_base_t<base>::ADCMPCR;
	template <uint32_t base> typename s12adf_base_t<base>::ADCMPDR0_ s12adf_base_t<base>::ADCMPDR0;
	template <uint32_t base> typename s12adf_base_t<base>::ADCMPDR1_ s12adf_base_t<base>::ADCMPDR1;
	template <uint32_t base> typename s12adf_base_t<base>::ADWINMON_ s12adf_base_t<base>::ADWINMON;
	template <uint32_t base> typename s12adf_base_t<base>::ADCMPBNSR_ s12adf_base_t<base>::ADCMPBNSR;
	template <uint32_t base> typename s12adf_base_t<base>::ADWINLLB_ s12adf_base_t<base>::ADWINLLB;
	template <uint32_t base> typename s12adf_base_t<base>::ADWINULB_ s12adf_base_t<base>::ADWINULB;
	template <uint32_t base> typename s12adf_base_t<base>::ADCMPBSR_ s12adf_base_t<base>::ADCMPBSR;
	template <uint32_t base> typename s12adf_base_t<base>::ADSAM_ s12adf_base_t<base>::ADSAM;
	template <uint32_t base> typename s12adf_base_t<base>::ADSAMPR_ s12adf_base_t<base>::ADSAMPR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD0 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adf0_t : public s12adf_base_t<base> {

		typedef s12adf_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::SELECTB::S12ADI;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::SELECTB::S12GBADI;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::SELECTB::S12GCADI;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI1;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 480;				///< A/D 入力 0.48uS、単位「ns」

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
			case ANALOG::AN007:
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
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR_;
		static  ADDR_ ADDR;


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
		typedef adansa0_t<base + 0x04>   ADANSA0_;
		static  ADANSA0_ ADANSA0;


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
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static  ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0 （ ADANSC0 ）
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
			bit_rw_t<io_, bitpos::B4>  ANSC004;
			bit_rw_t<io_, bitpos::B5>  ANSC005;
			bit_rw_t<io_, bitpos::B6>  ANSC006;
			bit_rw_t<io_, bitpos::B7>  ANSC007;
		};
		typedef adansc0_t<base + 0xD4>   ADANSC0_;
		static  ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSA0_::address>  ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSB0_::address>  ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADANSC0_::address>  ADANSC_;
		static  ADANSC_ ADANSC;


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
			bit_rw_t<io_, bitpos::B4>  ADS004;
			bit_rw_t<io_, bitpos::B5>  ADS005;
			bit_rw_t<io_, bitpos::B6>  ADS006;
			bit_rw_t<io_, bitpos::B7>  ADS007;
		};
		typedef adads0_t<base + 0x08>   ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ（ADADS）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADADS0_::address> ADADS_;
		static ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1_t<ANALOG, BASE::ADSSTR0_::address> ADSSTR_;
		static  ADSSTR_ ADSSTR;


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
		typedef adshcr_t<base + 0x66>   ADSHCR_;
		static  ADSHCR_ ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプル＆ホールド動作モード選択レジスタ（ ADSHMSR ）
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
		typedef adshmsr_t<base + 0x7C>  ADSHMSR_;
		static  ADSHMSR_ ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 0（ADCMPANSR0）
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

			bit_rw_t <io_, bitpos::B0>  CMPCHA000;
			bit_rw_t <io_, bitpos::B1>  CMPCHA001;
			bit_rw_t <io_, bitpos::B2>  CMPCHA002;
			bit_rw_t <io_, bitpos::B3>  CMPCHA003;
			bit_rw_t <io_, bitpos::B4>  CMPCHA004;
			bit_rw_t <io_, bitpos::B5>  CMPCHA005;
			bit_rw_t <io_, bitpos::B6>  CMPCHA006;
			bit_rw_t <io_, bitpos::B7>  CMPCHA007;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static  ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ（ADCMPANSR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPANSR0_::address> ADCMPANSR_;
		static ADCMPANSR_ ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0（ADCMPLR0）
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

			bit_rw_t<io_, bitpos::B0>  CMPLCHA000;
			bit_rw_t<io_, bitpos::B1>  CMPLCHA001;
			bit_rw_t<io_, bitpos::B2>  CMPLCHA002;
			bit_rw_t<io_, bitpos::B3>  CMPLCHA003;
			bit_rw_t<io_, bitpos::B4>  CMPLCHA004;
			bit_rw_t<io_, bitpos::B5>  CMPLCHA005;
			bit_rw_t<io_, bitpos::B6>  CMPLCHA006;
			bit_rw_t<io_, bitpos::B7>  CMPLCHA007;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static  ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	@brief  A/D コンペアレベルレジスタ（ADCMPLR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPLR0_::address> ADCMPLR_;
		static ADCMPLR_ ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネルステータスレジスタ 0（ADCMPSR0）
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

			bit_rw_t<io_, bitpos::B0>  CMPSTCHA000;
			bit_rw_t<io_, bitpos::B1>  CMPSTCHA001;
			bit_rw_t<io_, bitpos::B2>  CMPSTCHA002;
			bit_rw_t<io_, bitpos::B3>  CMPSTCHA003;
			bit_rw_t<io_, bitpos::B4>  CMPSTCHA004;
			bit_rw_t<io_, bitpos::B5>  CMPSTCHA005;
			bit_rw_t<io_, bitpos::B6>  CMPSTCHA006;
			bit_rw_t<io_, bitpos::B7>  CMPSTCHA007;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペア機能ウィンドウ A チャネルステータスレジスタ（ADCMPSR0）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans1_t<ANALOG, ADCMPSR0_::address> ADCMPSR_;
		static ADCMPSR_ ADCMPSR;
	};
	template <uint32_t base> typename s12adf0_t<base>::ADDR_ s12adf0_t<base>::ADDR;
	template <uint32_t base> typename s12adf0_t<base>::ADANSA0_ s12adf0_t<base>::ADANSA0;
	template <uint32_t base> typename s12adf0_t<base>::ADANSB0_ s12adf0_t<base>::ADANSB0;
	template <uint32_t base> typename s12adf0_t<base>::ADANSC0_ s12adf0_t<base>::ADANSC0;
	template <uint32_t base> typename s12adf0_t<base>::ADANSA_ s12adf0_t<base>::ADANSA;
	template <uint32_t base> typename s12adf0_t<base>::ADANSB_ s12adf0_t<base>::ADANSB;
	template <uint32_t base> typename s12adf0_t<base>::ADANSC_ s12adf0_t<base>::ADANSC;
	template <uint32_t base> typename s12adf0_t<base>::ADADS0_ s12adf0_t<base>::ADADS0;
	template <uint32_t base> typename s12adf0_t<base>::ADSSTR_ s12adf0_t<base>::ADSSTR;
	template <uint32_t base> typename s12adf0_t<base>::ADSHCR_ s12adf0_t<base>::ADSHCR;
	template <uint32_t base> typename s12adf0_t<base>::ADSHMSR_ s12adf0_t<base>::ADSHMSR;
	template <uint32_t base> typename s12adf0_t<base>::ADCMPANSR0_ s12adf0_t<base>::ADCMPANSR0;
	template <uint32_t base> typename s12adf0_t<base>::ADCMPANSR_ s12adf0_t<base>::ADCMPANSR;
	template <uint32_t base> typename s12adf0_t<base>::ADCMPLR0_ s12adf0_t<base>::ADCMPLR0;
	template <uint32_t base> typename s12adf0_t<base>::ADCMPLR_ s12adf0_t<base>::ADCMPLR;
	template <uint32_t base> typename s12adf0_t<base>::ADCMPSR0_ s12adf0_t<base>::ADCMPSR0;
	template <uint32_t base> typename s12adf0_t<base>::ADCMPSR_ s12adf0_t<base>::ADCMPSR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12adf1_t : public s12adf_base_t<base> {

		typedef s12adf_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::S12AD1;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::SELECTB::S12ADI1;	///< 変換終了割り込みベクター
		static constexpr auto GBADI		 = ICU::SELECTB::S12GBADI1;	///< グループＢ変換終了割り込みベクター
		static constexpr auto GCADI		 = ICU::SELECTB::S12GCADI1;	///< グループＣ変換終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::GROUPBL1::S12CMPAI1;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;		///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 480;				///< A/D 入力 0.48uS、単位「ns」

		static constexpr uint32_t ANALOG_NUM = 21;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN100,
			AN101,
			AN102,
			AN103,
			AN104,
			AN105,
			AN106,
			AN107,
			AN108,
			AN109,
			AN110,
			AN111,
			AN112,
			AN113,
			AN114,
			AN115,
			AN116,
			AN117,
			AN118,
			AN119,
			AN120,
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
			case ANALOG::AN100:
				if(ena) {
					PORTE::PDR.B2 = 0;
					PORTE::PMR.B2 = 0;
				}
				MPC::PE2PFS.ASEL = ena;
				break;
			case ANALOG::AN101:
				if(ena) {
					PORTE::PDR.B3 = 0;
					PORTE::PMR.B3 = 0;
				}
				MPC::PE3PFS.ASEL = ena;
				break;
			case ANALOG::AN102:
				if(ena) {
					PORTE::PDR.B4 = 0;
					PORTE::PMR.B4 = 0;
				}
				MPC::PE4PFS.ASEL = ena;
				break;
			case ANALOG::AN103:
				if(ena) {
					PORTE::PDR.B5 = 0;
					PORTE::PMR.B5 = 0;
				}
				MPC::PE5PFS.ASEL = ena;
				break;
			case ANALOG::AN104:
				if(ena) {
					PORTE::PDR.B6 = 0;
					PORTE::PMR.B6 = 0;
				}
				MPC::PE6PFS.ASEL = ena;
				break;
			case ANALOG::AN105:
				if(ena) {
					PORTE::PDR.B7 = 0;
					PORTE::PMR.B7 = 0;
				}
				MPC::PE7PFS.ASEL = ena;
				break;
			case ANALOG::AN106:
				if(ena) {
					PORTD::PDR.B6 = 0;
					PORTD::PMR.B6 = 0;
				}
				MPC::PD6PFS.ASEL = ena;
				break;
			case ANALOG::AN107:
				if(ena) {
					PORTD::PDR.B7 = 0;
					PORTD::PMR.B7 = 0;
				}
				MPC::PD7PFS.ASEL = ena;
				break;
			case ANALOG::AN108:
				if(ena) {
					PORTD::PDR.B0 = 0;
					PORTD::PMR.B0 = 0;
				}
				MPC::PD0PFS.ASEL = ena;
				break;
			case ANALOG::AN109:
				if(ena) {
					PORTD::PDR.B1 = 0;
					PORTD::PMR.B1 = 0;
				}
				MPC::PD1PFS.ASEL = ena;
				break;
			case ANALOG::AN110:
				if(ena) {
					PORTD::PDR.B2 = 0;
					PORTD::PMR.B2 = 0;
				}
				MPC::PD2PFS.ASEL = ena;
				break;
			case ANALOG::AN111:
				if(ena) {
					PORTD::PDR.B3 = 0;
					PORTD::PMR.B3 = 0;
				}
				MPC::PD3PFS.ASEL = ena;
				break;
			case ANALOG::AN112:
				if(ena) {
					PORTD::PDR.B4 = 0;
					PORTD::PMR.B4 = 0;
				}
				MPC::PD4PFS.ASEL = ena;
				break;
			case ANALOG::AN113:
				if(ena) {
					PORTD::PDR.B5 = 0;
					PORTD::PMR.B5 = 0;
				}
				MPC::PD5PFS.ASEL = ena;
				break;
			case ANALOG::AN114:
				if(ena) {
					PORT9::PDR.B0 = 0;
					PORT9::PMR.B0 = 0;
				}
				MPC::P90PFS.ASEL = ena;
				break;
			case ANALOG::AN115:
				if(ena) {
					PORT9::PDR.B1 = 0;
					PORT9::PMR.B1 = 0;
				}
				MPC::P91PFS.ASEL = ena;
				break;
			case ANALOG::AN116:
				if(ena) {
					PORT9::PDR.B2 = 0;
					PORT9::PMR.B2 = 0;
				}
				MPC::P92PFS.ASEL = ena;
				break;
			case ANALOG::AN117:
				if(ena) {
					PORT9::PDR.B3 = 0;
					PORT9::PMR.B3 = 0;
				}
				MPC::P93PFS.ASEL = ena;
				break;
			case ANALOG::AN118:
				if(ena) {
					PORT0::PDR.B0 = 0;
					PORT0::PMR.B0 = 0;
				}
				MPC::P00PFS.ASEL = ena;
				break;
			case ANALOG::AN119:
				if(ena) {
					PORT0::PDR.B1 = 0;
					PORT0::PMR.B1 = 0;
				}
				MPC::P01PFS.ASEL = ena;
				break;
			case ANALOG::AN120:
				if(ena) {
					PORT0::PDR.B2 = 0;
					PORT0::PMR.B2 = 0;
				}
				MPC::P02PFS.ASEL = ena;
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
		static  ADDR8_ ADDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 9（ADDR9）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x32> ADDR9_;
		static  ADDR9_ ADDR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 10（ADDR10）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x34> ADDR10_;
		static  ADDR10_ ADDR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 11（ADDR11）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x36> ADDR11_;
		static  ADDR11_ ADDR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 12（ADDR12）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x38> ADDR12_;
		static  ADDR12_ ADDR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 13（ADDR13）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3A> ADDR13_;
		static  ADDR13_ ADDR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 14（ADDR14）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3C> ADDR14_;
		static  ADDR14_ ADDR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 15（ADDR15）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3E> ADDR15_;
		static  ADDR15_ ADDR15;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> ADDR16_;
		static  ADDR16_ ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 17（ADDR17）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x42> ADDR17_;
		static  ADDR17_ ADDR17;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 18（ADDR18）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x44> ADDR18_;
		static  ADDR18_ ADDR18;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 19（ADDR19）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x46> ADDR19_;
		static  ADDR19_ ADDR19;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 20（ADDR20）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x48> ADDR20_;
		static  ADDR20_ ADDR20;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ（ ADTSDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1A> ADTSDR_;
		static  ADTSDR_ ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief   A/D 内部基準電圧データレジスタ（ ADOCDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1C> ADOCDR_;
		static  ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::addr_tr_t<ANALOG, BASE::ADDR0_::address,
			ANALOG::TEMP, ADTSDR_::address, ANALOG::REF, ADOCDR_::address> ADDR_;
		static  ADDR_ ADDR;


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

			bit_rw_t<io_, bitpos::B0>   ANSA000;	///< AN100
			bit_rw_t<io_, bitpos::B1>   ANSA001;	///< AN101
			bit_rw_t<io_, bitpos::B2>   ANSA002;	///< AN102
			bit_rw_t<io_, bitpos::B3>   ANSA003;	///< AN103
			bit_rw_t<io_, bitpos::B4>   ANSA004;	///< AN104
			bit_rw_t<io_, bitpos::B5>   ANSA005;	///< AN105
			bit_rw_t<io_, bitpos::B6>   ANSA006;	///< AN106
			bit_rw_t<io_, bitpos::B7>   ANSA007;	///< AN107
			bit_rw_t<io_, bitpos::B8>   ANSA008;	///< AN108
			bit_rw_t<io_, bitpos::B9>   ANSA009;	///< AN109
			bit_rw_t<io_, bitpos::B10>  ANSA010;	///< AN110
			bit_rw_t<io_, bitpos::B11>  ANSA011;	///< AN111
			bit_rw_t<io_, bitpos::B12>  ANSA012;	///< AN112
			bit_rw_t<io_, bitpos::B13>  ANSA013;	///< AN113
			bit_rw_t<io_, bitpos::B14>  ANSA014;	///< AN114
			bit_rw_t<io_, bitpos::B15>  ANSA015;	///< AN115
		};
		typedef adansa0_t<base + 0x04>   ADANSA0_;
		static  ADANSA0_ ADANSA0;


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

			bit_rw_t<io_, bitpos::B0>  ANSA100;		///< AN116
			bit_rw_t<io_, bitpos::B1>  ANSA101;		///< AN117
			bit_rw_t<io_, bitpos::B2>  ANSA102;		///< AN118
			bit_rw_t<io_, bitpos::B3>  ANSA103;		///< AN119
			bit_rw_t<io_, bitpos::B4>  ANSA104;		///< AN120
		};
		typedef adansa1_t<base + 0x06>   ADANSA1_;
		static  ADANSA1_ ADANSA1;


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

			bit_rw_t<io_, bitpos::B0>   ANSB000;	///< AN100
			bit_rw_t<io_, bitpos::B1>   ANSB001;	///< AN101
			bit_rw_t<io_, bitpos::B2>   ANSB002;	///< AN102
			bit_rw_t<io_, bitpos::B3>   ANSB003;	///< AN103
			bit_rw_t<io_, bitpos::B4>   ANSB004;	///< AN104
			bit_rw_t<io_, bitpos::B5>   ANSB005;	///< AN105
			bit_rw_t<io_, bitpos::B6>   ANSB006;	///< AN106
			bit_rw_t<io_, bitpos::B7>   ANSB007;	///< AN107
			bit_rw_t<io_, bitpos::B8>   ANSB008;	///< AN108
			bit_rw_t<io_, bitpos::B9>   ANSB009;	///< AN109
			bit_rw_t<io_, bitpos::B10>  ANSB010;	///< AN110
			bit_rw_t<io_, bitpos::B11>  ANSB011;	///< AN111
			bit_rw_t<io_, bitpos::B12>  ANSB012;	///< AN112
			bit_rw_t<io_, bitpos::B13>  ANSB013;	///< AN113
			bit_rw_t<io_, bitpos::B14>  ANSB014;	///< AN114
			bit_rw_t<io_, bitpos::B15>  ANSB015;	///< AN115
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static  ADANSB0_ ADANSB0;


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

			bit_rw_t<io_, bitpos::B0>  ANSB100;		///< AN116
			bit_rw_t<io_, bitpos::B1>  ANSB101;		///< AN117
			bit_rw_t<io_, bitpos::B2>  ANSB102;		///< AN118
			bit_rw_t<io_, bitpos::B3>  ANSB103;		///< AN119
			bit_rw_t<io_, bitpos::B4>  ANSB104;		///< AN120
		};
		typedef adansb1_t<base + 0x16>   ADANSB1_;
		static  ADANSB1_ ADANSB1;


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

			bit_rw_t<io_, bitpos::B0>   ANSC000;	///< AN100
			bit_rw_t<io_, bitpos::B1>   ANSC001;	///< AN101
			bit_rw_t<io_, bitpos::B2>   ANSC002;	///< AN102
			bit_rw_t<io_, bitpos::B3>   ANSC003;	///< AN103
			bit_rw_t<io_, bitpos::B4>   ANSC004;	///< AN104
			bit_rw_t<io_, bitpos::B5>   ANSC005;	///< AN105
			bit_rw_t<io_, bitpos::B6>   ANSC006;	///< AN106
			bit_rw_t<io_, bitpos::B7>   ANSC007;	///< AN107
			bit_rw_t<io_, bitpos::B8>   ANSC008;	///< AN108
			bit_rw_t<io_, bitpos::B9>   ANSC009;	///< AN109
			bit_rw_t<io_, bitpos::B10>  ANSC010;	///< AN110
			bit_rw_t<io_, bitpos::B11>  ANSC011;	///< AN111
			bit_rw_t<io_, bitpos::B12>  ANSC012;	///< AN112
			bit_rw_t<io_, bitpos::B13>  ANSC013;	///< AN113
			bit_rw_t<io_, bitpos::B14>  ANSC014;	///< AN114
			bit_rw_t<io_, bitpos::B15>  ANSC015;	///< AN115
		};
		typedef adansc0_t<base + 0xD4>   ADANSC0_;
		static  ADANSC0_ ADANSC0;


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

			bit_rw_t<io_, bitpos::B0>  ANSC100;		///< AN116
			bit_rw_t<io_, bitpos::B1>  ANSC101;		///< AN117
			bit_rw_t<io_, bitpos::B2>  ANSC102;		///< AN118
			bit_rw_t<io_, bitpos::B3>  ANSC103;		///< AN119
			bit_rw_t<io_, bitpos::B4>  ANSC104;		///< AN120
		};
		typedef adansc1_t<base + 0xD6>   ADANSC1_;
		static  ADANSC1_ ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ（ADANSA）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADANSA0_::address, ADANSA1_::address> ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADANSB0_::address, ADANSB1_::address> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADANSC0_::address, ADANSC1_::address> ADANSC_;
		static  ADANSC_ ADANSC;


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

			bit_rw_t<io_, bitpos::B0>   ADS000;		///< AN100
			bit_rw_t<io_, bitpos::B1>   ADS001;		///< AN101
			bit_rw_t<io_, bitpos::B2>   ADS002;		///< AN102
			bit_rw_t<io_, bitpos::B3>   ADS003;		///< AN103
			bit_rw_t<io_, bitpos::B4>   ADS004;		///< AN104
			bit_rw_t<io_, bitpos::B5>   ADS005;		///< AN105
			bit_rw_t<io_, bitpos::B6>   ADS006;		///< AN106
			bit_rw_t<io_, bitpos::B7>   ADS007;		///< AN107
			bit_rw_t<io_, bitpos::B8>   ADS008;		///< AN108
			bit_rw_t<io_, bitpos::B9>   ADS009;		///< AN109
			bit_rw_t<io_, bitpos::B10>  ADS010;		///< AN110
			bit_rw_t<io_, bitpos::B11>  ADS011;		///< AN111
			bit_rw_t<io_, bitpos::B12>  ADS012;		///< AN112
			bit_rw_t<io_, bitpos::B13>  ADS013;		///< AN113
			bit_rw_t<io_, bitpos::B14>  ADS014;		///< AN114
			bit_rw_t<io_, bitpos::B15>  ADS015;		///< AN115
		};
		typedef adads0_t<base + 0x08>   ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均モード選択レジスタ 1（ADADS1）
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

			bit_rw_t<io_, bitpos::B0>   ADS100;		///< AN116
			bit_rw_t<io_, bitpos::B1>   ADS101;		///< AN117
			bit_rw_t<io_, bitpos::B2>   ADS102;		///< AN118
			bit_rw_t<io_, bitpos::B3>   ADS103;		///< AN119
			bit_rw_t<io_, bitpos::B4>   ADS104;		///< AN120
		};
		typedef adads1_t<base + 0x0A>   ADADS1_;
		static  ADADS1_ ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均モード選択レジスタ（ADADS）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADADS0_::address, ADADS1_::address> ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換拡張入力コントロールレジスタ（ ADEXICR ）
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

			bit_rw_t <io_, bitpos::B0>      TSSAD;
			bit_rw_t <io_, bitpos::B1>      OCSAD;

			bit_rw_t <io_, bitpos::B8>      TSSA;
			bit_rw_t <io_, bitpos::B9>      OCSA;
			bit_rw_t <io_, bitpos::B10>     TSSB;
			bit_rw_t <io_, bitpos::B11>     OCSB;

			bits_rw_t<io_, bitpos::B13, 2>  EXSEL;
			bit_rw_t <io_, bitpos::B15>     EXOEN;
		};
		typedef adexicr_t<base + 0x12>   ADEXICR_;
		static  ADEXICR_ ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D グループ C 拡張入力コントロールレジスタ（ ADGCEXCR ）
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

			bit_rw_t <io_, bitpos::B0>      TSSC;
			bit_rw_t <io_, bitpos::B1>      OCSC;
		};
		typedef adgcexcr_t<base + 0xD8>   ADGCEXCR_;
		static  ADGCEXCR_ ADGCEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> ADSSTRL_;
		static  ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ T（ADSSTRT）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDE> ADSSTRT_;
		static  ADSSTRT_ ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDF> ADSSTRO_;
		static  ADSSTRO_ ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 8 （ ADSSTR8 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE8> ADSSTR8_;
		static  ADSSTR8_ ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 9 （ ADSSTR9 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE9> ADSSTR9_;
		static  ADSSTR9_ ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 10 （ ADSSTR10 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEA> ADSSTR10_;
		static  ADSSTR10_ ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 11 （ ADSSTR11 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEB> ADSSTR11_;
		static  ADSSTR11_ ADSSTR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 12 （ ADSSTR12 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEC> ADSSTR12_;
		static  ADSSTR12_ ADSSTR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 13 （ ADSSTR13 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xED> ADSSTR13_;
		static  ADSSTR13_ ADSSTR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 14 （ ADSSTR14 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEE> ADSSTR14_;
		static  ADSSTR14_ ADSSTR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 15 （ ADSSTR15 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEF> ADSSTR15_;
		static  ADSSTR15_ ADSSTR15;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adsstr1l_tr_t<ANALOG, BASE::ADSSTR0_::address, ADSSTRL_::address,
			ANALOG::TEMP, ADSSTRT_::address, ANALOG::REF, ADSSTRO_::address> ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 0（ADCMPANSR0）
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

			bit_rw_t<io_, bitpos::B0>   CMPCHA000;		///< AN100
			bit_rw_t<io_, bitpos::B1>   CMPCHA001;		///< AN101
			bit_rw_t<io_, bitpos::B2>   CMPCHA002;		///< AN102
			bit_rw_t<io_, bitpos::B3>   CMPCHA003;		///< AN103
			bit_rw_t<io_, bitpos::B4>   CMPCHA004;		///< AN104
			bit_rw_t<io_, bitpos::B5>   CMPCHA005;		///< AN105
			bit_rw_t<io_, bitpos::B6>   CMPCHA006;		///< AN106
			bit_rw_t<io_, bitpos::B7>   CMPCHA007;		///< AN107
			bit_rw_t<io_, bitpos::B8>   CMPCHA008;		///< AN108
			bit_rw_t<io_, bitpos::B9>   CMPCHA009;		///< AN109
			bit_rw_t<io_, bitpos::B10>  CMPCHA010;		///< AN110
			bit_rw_t<io_, bitpos::B11>  CMPCHA011;		///< AN111
			bit_rw_t<io_, bitpos::B12>  CMPCHA012;		///< AN112
			bit_rw_t<io_, bitpos::B13>  CMPCHA013;		///< AN113
			bit_rw_t<io_, bitpos::B14>  CMPCHA014;		///< AN114
			bit_rw_t<io_, bitpos::B15>  CMPCHA015;		///< AN115
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static  ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 1（ADCMPANSR1）
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

			bit_rw_t<io_, bitpos::B0>   CMPCHA100;		///< AN116
			bit_rw_t<io_, bitpos::B1>   CMPCHA101;		///< AN117
			bit_rw_t<io_, bitpos::B2>   CMPCHA102;		///< AN118
			bit_rw_t<io_, bitpos::B3>   CMPCHA103;		///< AN119
			bit_rw_t<io_, bitpos::B4>   CMPCHA104;		///< AN120
		};
		typedef adcmpansr1_t<base + 0x96>  ADCMPANSR1_;
		static  ADCMPANSR1_ ADCMPANSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ（ADCMPANSR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADCMPANSR0_::address, ADCMPANSR1_::address> ADCMPANSR_;
		static ADCMPANSR_ ADCMPANSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択拡張レジスタ（ADCMPANSER）
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

			bit_rw_t <io_, bitpos::B0>  CMPSTS;
			bit_rw_t <io_, bitpos::B1>  CMPSOC;
		};
		typedef adcmpanser_t<base + 0x92>  ADCMPANSER_;
		static  ADCMPANSER_ ADCMPANSER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0（ADCMPLR0）
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

			bit_rw_t<io_, bitpos::B0>   CMPLCHA000;		///< AN100
			bit_rw_t<io_, bitpos::B1>   CMPLCHA001;		///< AN101
			bit_rw_t<io_, bitpos::B2>   CMPLCHA002;		///< AN102
			bit_rw_t<io_, bitpos::B3>   CMPLCHA003;		///< AN103
			bit_rw_t<io_, bitpos::B4>   CMPLCHA004;		///< AN104
			bit_rw_t<io_, bitpos::B5>   CMPLCHA005;		///< AN105
			bit_rw_t<io_, bitpos::B6>   CMPLCHA006;		///< AN106
			bit_rw_t<io_, bitpos::B7>   CMPLCHA007;		///< AN107
			bit_rw_t<io_, bitpos::B8>   CMPLCHA008;		///< AN108
			bit_rw_t<io_, bitpos::B9>   CMPLCHA009;		///< AN109
			bit_rw_t<io_, bitpos::B10>  CMPLCHA010;		///< AN110
			bit_rw_t<io_, bitpos::B11>  CMPLCHA011;		///< AN111
			bit_rw_t<io_, bitpos::B12>  CMPLCHA012;		///< AN112
			bit_rw_t<io_, bitpos::B13>  CMPLCHA013;		///< AN113
			bit_rw_t<io_, bitpos::B14>  CMPLCHA014;		///< AN114
			bit_rw_t<io_, bitpos::B15>  CMPLCHA015;		///< AN115
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static  ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 1（ADCMPLR1）
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

			bit_rw_t<io_, bitpos::B0>   CMPLCHA100;		///< AN116
			bit_rw_t<io_, bitpos::B1>   CMPLCHA101;		///< AN117
			bit_rw_t<io_, bitpos::B2>   CMPLCHA102;		///< AN118
			bit_rw_t<io_, bitpos::B3>   CMPLCHA103;		///< AN119
			bit_rw_t<io_, bitpos::B4>   CMPLCHA104;		///< AN120
		};
		typedef adcmplr1_t<base + 0x9A>  ADCMPLR1_;
		static  ADCMPLR1_ ADCMPLR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ（ADCMPLR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADCMPLR0_::address, ADCMPLR1_::address> ADCMPLR_;
		static ADCMPLR_ ADCMPLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベル拡張レジスタ（ADCMPLER）
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

			bit_rw_t<io_, bitpos::B0>  CMPLTS;
			bit_rw_t<io_, bitpos::B1>  CMPLOC;
		};
		typedef adcmpler_t<base + 0x93>  ADCMPLER_;
		static  ADCMPLER_ ADCMPLER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0（ADCMPSR0）
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

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA000;	///< AN100
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA001;	///< AN101
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA002;	///< AN102
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA003;	///< AN103
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA004;	///< AN104
			bit_rw_t<io_, bitpos::B5>   CMPSTCHA005;	///< AN105
			bit_rw_t<io_, bitpos::B6>   CMPSTCHA006;	///< AN106
			bit_rw_t<io_, bitpos::B7>   CMPSTCHA007;	///< AN107
			bit_rw_t<io_, bitpos::B8>   CMPSTCHA008;	///< AN108
			bit_rw_t<io_, bitpos::B9>   CMPSTCHA009;	///< AN109
			bit_rw_t<io_, bitpos::B10>  CMPSTCHA010;	///< AN110
			bit_rw_t<io_, bitpos::B11>  CMPSTCHA011;	///< AN111
			bit_rw_t<io_, bitpos::B12>  CMPSTCHA012;	///< AN112
			bit_rw_t<io_, bitpos::B13>  CMPSTCHA013;	///< AN113
			bit_rw_t<io_, bitpos::B14>  CMPSTCHA014;	///< AN114
			bit_rw_t<io_, bitpos::B15>  CMPSTCHA015;	///< AN115
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 1（ADCMPSR1）
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

			bit_rw_t<io_, bitpos::B0>   CMPSTCHA100;	///< AN116
			bit_rw_t<io_, bitpos::B1>   CMPSTCHA101;	///< AN117
			bit_rw_t<io_, bitpos::B2>   CMPSTCHA102;	///< AN118
			bit_rw_t<io_, bitpos::B3>   CMPSTCHA103;	///< AN119
			bit_rw_t<io_, bitpos::B4>   CMPSTCHA104;	///< AN120
		};
		typedef adcmpsr1_t<base + 0xA2>  ADCMPSR1_;
		static  ADCMPSR1_ ADCMPSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ（ADCMPSR）
		*/
		//-----------------------------------------------------------------//
		typedef ad_utils::adans2_t<ANALOG, ADCMPSR0_::address, ADCMPSR1_::address> ADCMPSR_;
		static ADCMPSR_ ADCMPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータス拡張レジスタ（ADCMPSER）
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

			bit_rw_t<io_, bitpos::B0>  CMPFTS;
			bit_rw_t<io_, bitpos::B1>  CMPFOC;
		};
		typedef adcmpser_t<base + 0xA4>  ADCMPSER_;
		static  ADCMPSER_ ADCMPSER;
	};
	template <uint32_t base> typename s12adf1_t<base>::ADDR8_  s12adf1_t<base>::ADDR8;
	template <uint32_t base> typename s12adf1_t<base>::ADDR9_  s12adf1_t<base>::ADDR9;
	template <uint32_t base> typename s12adf1_t<base>::ADDR10_ s12adf1_t<base>::ADDR10;
	template <uint32_t base> typename s12adf1_t<base>::ADDR11_ s12adf1_t<base>::ADDR11;
	template <uint32_t base> typename s12adf1_t<base>::ADDR12_ s12adf1_t<base>::ADDR12;
	template <uint32_t base> typename s12adf1_t<base>::ADDR13_ s12adf1_t<base>::ADDR13;
	template <uint32_t base> typename s12adf1_t<base>::ADDR14_ s12adf1_t<base>::ADDR14;
	template <uint32_t base> typename s12adf1_t<base>::ADDR15_ s12adf1_t<base>::ADDR15;
	template <uint32_t base> typename s12adf1_t<base>::ADDR16_ s12adf1_t<base>::ADDR16;
	template <uint32_t base> typename s12adf1_t<base>::ADDR17_ s12adf1_t<base>::ADDR17;
	template <uint32_t base> typename s12adf1_t<base>::ADDR18_ s12adf1_t<base>::ADDR18;
	template <uint32_t base> typename s12adf1_t<base>::ADDR19_ s12adf1_t<base>::ADDR19;
	template <uint32_t base> typename s12adf1_t<base>::ADDR20_ s12adf1_t<base>::ADDR20;
	template <uint32_t base> typename s12adf1_t<base>::ADTSDR_ s12adf1_t<base>::ADTSDR;
	template <uint32_t base> typename s12adf1_t<base>::ADOCDR_ s12adf1_t<base>::ADOCDR;
	template <uint32_t base> typename s12adf1_t<base>::ADDR_   s12adf1_t<base>::ADDR;
	template <uint32_t base> typename s12adf1_t<base>::ADANSA0_ s12adf1_t<base>::ADANSA0;
	template <uint32_t base> typename s12adf1_t<base>::ADANSA1_ s12adf1_t<base>::ADANSA1;
	template <uint32_t base> typename s12adf1_t<base>::ADANSB0_ s12adf1_t<base>::ADANSB0;
	template <uint32_t base> typename s12adf1_t<base>::ADANSB1_ s12adf1_t<base>::ADANSB1;
	template <uint32_t base> typename s12adf1_t<base>::ADANSC0_ s12adf1_t<base>::ADANSC0;
	template <uint32_t base> typename s12adf1_t<base>::ADANSC1_ s12adf1_t<base>::ADANSC1;
	template <uint32_t base> typename s12adf1_t<base>::ADANSA_  s12adf1_t<base>::ADANSA;
	template <uint32_t base> typename s12adf1_t<base>::ADANSB_  s12adf1_t<base>::ADANSB;
	template <uint32_t base> typename s12adf1_t<base>::ADANSC_  s12adf1_t<base>::ADANSC;
	template <uint32_t base> typename s12adf1_t<base>::ADADS0_  s12adf1_t<base>::ADADS0;
	template <uint32_t base> typename s12adf1_t<base>::ADADS1_  s12adf1_t<base>::ADADS1;
	template <uint32_t base> typename s12adf1_t<base>::ADEXICR_ s12adf1_t<base>::ADEXICR;
	template <uint32_t base> typename s12adf1_t<base>::ADGCEXCR_ s12adf1_t<base>::ADGCEXCR;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTRL_  s12adf1_t<base>::ADSSTRL;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTRT_  s12adf1_t<base>::ADSSTRT;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTRO_  s12adf1_t<base>::ADSSTRO;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR8_  s12adf1_t<base>::ADSSTR8;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR9_  s12adf1_t<base>::ADSSTR9;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR10_ s12adf1_t<base>::ADSSTR10;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR11_ s12adf1_t<base>::ADSSTR11;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR12_ s12adf1_t<base>::ADSSTR12;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR13_ s12adf1_t<base>::ADSSTR13;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR14_ s12adf1_t<base>::ADSSTR14;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR15_ s12adf1_t<base>::ADSSTR15;
	template <uint32_t base> typename s12adf1_t<base>::ADSSTR_   s12adf1_t<base>::ADSSTR;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPANSR0_ s12adf1_t<base>::ADCMPANSR0;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPANSR1_ s12adf1_t<base>::ADCMPANSR1;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPANSR_ s12adf1_t<base>::ADCMPANSR;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPANSER_ s12adf1_t<base>::ADCMPANSER;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPLR0_ s12adf1_t<base>::ADCMPLR0;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPLR1_ s12adf1_t<base>::ADCMPLR1;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPLR_ s12adf1_t<base>::ADCMPLR;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPLER_ s12adf1_t<base>::ADCMPLER;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPSR0_ s12adf1_t<base>::ADCMPSR0;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPSR1_ s12adf1_t<base>::ADCMPSR1;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPSR_ s12adf1_t<base>::ADCMPSR;
	template <uint32_t base> typename s12adf1_t<base>::ADCMPSER_ s12adf1_t<base>::ADCMPSER;

	typedef s12adf0_t<0x0008'9000> S12AD;
	typedef s12adf1_t<0x0008'9100> S12AD1;
}
