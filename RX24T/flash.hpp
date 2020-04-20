#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct flash_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  E2 データフラッシュ制御レジスタ (DFLCTL)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflctl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DFLEN;
		};
		typedef dflctl_t<0x007FC090> DFLCTL_;
		static DFLCTL_ DFLCTL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E モードエントリレジスタ (FENTRYR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fentryr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     FENTRY0;
			bit_rw_t <io_, bitpos::B7>     FENTRYD;
			bits_rw_t<io_, bitpos::B8, 8>  FEKEY;
		};
		typedef fentryr_t<0x007FFFB2> FENTRYR_;
		static FENTRYR_ FENTRYR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクト解除レジスタ (FPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x007FC180> FPR_;
		static FPR_ FPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクト解除ステータスレジスタ (FPSR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpsr_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0> PERR;
		};
		typedef fpsr_t<0x007FC184> FPSR_;
		static FPSR_ FPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E モード制御レジスタ (FPMCR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpmcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  FMS0;
			bit_rw_t<io_, bitpos::B3>  RPDIS;
			bit_rw_t<io_, bitpos::B4>  FMS1;
			bit_rw_t<io_, bitpos::B6>  LVPE;
			bit_rw_t<io_, bitpos::B7>  FMS2;
		};
		typedef fpmcr_t<0x007FC100> FPMCR_;
		static FPMCR_ FPMCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ初期設定レジスタ (FISR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fisr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  PCKA;
			bits_rw_t<io_, bitpos::B6, 2>  SAS;
		};
		typedef fisr_t<0x007FC1D8> FISR_;
		static FISR_ FISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュリセットレジスタ (FRESETR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fresetr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  FRESET;
		};
		typedef fresetr_t<0x007FC124> FRESETR_;
		static FRESETR_ FRESETR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ領域選択レジスタ (FASR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fasr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  EXS;
		};
		typedef fasr_t<0x007FC104> FASR_;
		static FASR_ FASR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ制御レジスタ (FCR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CMD;
			bit_rw_t <io_, bitpos::B6>     STOP;
			bit_rw_t <io_, bitpos::B7>     OPST;
		};
		typedef fcr_t<0x007FC114> FCR_;
		static FCR_ FCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエクストラ領域制御レジスタ (FEXCR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fexcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CMD;
			bit_rw_t <io_, bitpos::B7>     OPST;
		};
		typedef fexcr_t<0x007FC1DC> FEXCR_;
		static FEXCR_ FEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ H (FSARH)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC110> FSARH_;
		static FSARH_ FSARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ L (FSARL)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC108> FSARL_;
		static FSARL_ FSARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ H (FEARH)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC120> FEARH_;
		static FEARH_ FEARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ L (FEARL)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC118> FEARL_;
		static FEARL_ FEARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトバッファ n レジスタ (FWBn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC130> FWB0_;
		typedef rw16_t<0x007FC138> FWB1_;
		typedef rw16_t<0x007FC140> FWB2_;
		typedef rw16_t<0x007FC144> FWB3_;
		static FWB0_ FWB0;
		static FWB1_ FWB1;
		static FWB2_ FWB2;
		static FWB3_ FWB3;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 0 (FSTATR0)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr0_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  ERERR;
			bit_ro_t<io_, bitpos::B1>  PRGERR;
			bit_ro_t<io_, bitpos::B3>  BCERR;
			bit_ro_t<io_, bitpos::B4>  ILGLERR;
			bit_ro_t<io_, bitpos::B5>  EILGLERR;
		};
		typedef fstatr0_t<0x007FC1F0> FSTATR0_;
		static FSTATR0_ FSTATR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 1 (FSTATR1)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr1_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B6>  FRDY;
			bit_ro_t<io_, bitpos::B7>  EXRDY;
		};
		typedef fstatr1_t<0x007FC12C> FSTATR1_;
		static FSTATR1_ FSTATR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ H (FEAMH)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1E8> FEAMH_;
		static FEAMH_ FEAMH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ L (FEAML)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1E0> FEAML_;
		static FEAML_ FEAML;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュスタートアップ設定モニタレジスタ (FSCMR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fscmr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>  SASMF;
		};
		typedef fscmr_t<0x007FC1C0> FSCMR_;
		static FSCMR_ FSCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ開始アドレスモニタレジスタ (FAWSMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1C8> FAWSMR_;
		static FAWSMR_ FAWSMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ終了アドレスモニタレジスタ (FAWEMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1D0> FAWEMR_;
		static FAWEMR_ FAWEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007FC350> UIDR0_;
		typedef rw32_t<0x007FC354> UIDR1_;
		typedef rw32_t<0x007FC358> UIDR2_;
		typedef rw32_t<0x007FC35C> UIDR3_;
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ROM キャッシュ許可レジスタ (ROMCE)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct romce_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ROMCEN;
		};
		typedef romce_t<0x00081000> ROMCE_;
		static ROMCE_ ROMCE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ROM キャッシュ無効化レジスタ (ROMCIV)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct romciv_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ROMCIV;
		};
		typedef romciv_t<0x00081004> ROMCIV_;
		static ROMCIV_ ROMCIV;
	};
	typedef flash_t<void> FLASH;

	template<class _> typename flash_t<_>::DFLCTL_  flash_t<_>::DFLCTL;
	template<class _> typename flash_t<_>::FENTRYR_ flash_t<_>::FENTRYR;
	template<class _> typename flash_t<_>::FPR_     flash_t<_>::FPR;
	template<class _> typename flash_t<_>::FPSR_    flash_t<_>::FPSR;
	template<class _> typename flash_t<_>::FPMCR_   flash_t<_>::FPMCR;
	template<class _> typename flash_t<_>::FISR_    flash_t<_>::FISR;
	template<class _> typename flash_t<_>::FRESETR_ flash_t<_>::FRESETR;
	template<class _> typename flash_t<_>::FASR_    flash_t<_>::FASR;
	template<class _> typename flash_t<_>::FCR_     flash_t<_>::FCR;
	template<class _> typename flash_t<_>::FEXCR_   flash_t<_>::FEXCR;
	template<class _> typename flash_t<_>::FSARH_   flash_t<_>::FSARH;
	template<class _> typename flash_t<_>::FSARL_   flash_t<_>::FSARL;
	template<class _> typename flash_t<_>::FEARH_   flash_t<_>::FEARH;
	template<class _> typename flash_t<_>::FEARL_   flash_t<_>::FEARL;
	template<class _> typename flash_t<_>::FWB0_    flash_t<_>::FWB0;
	template<class _> typename flash_t<_>::FWB1_    flash_t<_>::FWB1;
	template<class _> typename flash_t<_>::FWB2_    flash_t<_>::FWB2;
	template<class _> typename flash_t<_>::FWB3_    flash_t<_>::FWB3;
	template<class _> typename flash_t<_>::FSTATR0_ flash_t<_>::FSTATR0;
	template<class _> typename flash_t<_>::FSTATR1_ flash_t<_>::FSTATR1;
	template<class _> typename flash_t<_>::FEAMH_   flash_t<_>::FEAMH;
	template<class _> typename flash_t<_>::FEAML_   flash_t<_>::FEAML;
	template<class _> typename flash_t<_>::FSCMR_   flash_t<_>::FSCMR;
	template<class _> typename flash_t<_>::FAWSMR_  flash_t<_>::FAWSMR;
	template<class _> typename flash_t<_>::FAWEMR_  flash_t<_>::FAWEMR;
	template<class _> typename flash_t<_>::UIDR0_   flash_t<_>::UIDR0;
	template<class _> typename flash_t<_>::UIDR1_   flash_t<_>::UIDR1;
	template<class _> typename flash_t<_>::UIDR2_   flash_t<_>::UIDR2;
	template<class _> typename flash_t<_>::UIDR3_   flash_t<_>::UIDR3;

	template<class _> typename flash_t<_>::ROMCE_   flash_t<_>::ROMCE;
	template<class _> typename flash_t<_>::ROMCIV_  flash_t<_>::ROMCIV;
}
