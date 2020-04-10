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
	struct flash_t_ {

		//-----------------------------------------------------------------//
		/*!
			@brief  E2 データフラッシュ制御レジスタ (DFLCTL)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflctl_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DFLEN;
		};
		typedef dflctl_t_<0x007FC090> dflctl_t;
		static dflctl_t DFLCTL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E モードエントリレジスタ (FENTRYR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fentryr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     FENTRY0;
			bit_rw_t <io_, bitpos::B7>     FENTRYD;
			bits_rw_t<io_, bitpos::B8, 8>  FEKEY;
		};
		typedef fentryr_t_<0x007FFFB2> fentryr_t;
		static fentryr_t FENTRYR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクト解除レジスタ (FPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x007FC180> fpr_t;
		static fpr_t FPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクト解除ステータスレジスタ (FPSR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpsr_t_ : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0> PERR;
		};
		typedef fpsr_t_<0x007FC184> fpsr_t;
		static fpsr_t FPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E モード制御レジスタ (FPMCR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpmcr_t_ : public rw8_t<base> {
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
		typedef fpmcr_t_<0x007FC100> fpmcr_t;
		static fpmcr_t FPMCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ初期設定レジスタ (FISR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fisr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  PCKA;
			bits_rw_t<io_, bitpos::B6, 2>  SAS;
		};
		typedef fisr_t_<0x007FC1D8> fisr_t;
		static fisr_t FISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュリセットレジスタ (FRESETR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fresetr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  FRESET;
		};
		typedef fresetr_t_<0x007FC124> fresetr_t;
		static fresetr_t FRESETR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ領域選択レジスタ (FASR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fasr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  EXS;
		};
		typedef fasr_t_<0x007FC104> fasr_t;
		static fasr_t FASR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ制御レジスタ (FCR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CMD;
			bit_rw_t <io_, bitpos::B6>     STOP;
			bit_rw_t <io_, bitpos::B7>     OPST;
		};
		typedef fcr_t_<0x007FC114> fcr_t;
		static fcr_t FCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエクストラ領域制御レジスタ (FEXCR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fexcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CMD;
			bit_rw_t <io_, bitpos::B7>     OPST;
		};
		typedef fexcr_t_<0x007FC1DC> fexcr_t;
		static fexcr_t FEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ H (FSARH)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC110> fsarh_t;
		static fsarh_t FSARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ L (FSARL)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC108> fsarl_t;
		static fsarl_t FSARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ H (FEARH)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC120> fearh_t;
		static fearh_t FEARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ L (FEARL)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC118> fearl_t;
		static fearl_t FEARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトバッファ n レジスタ (FWBn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC130> fwb0_t;
		static fwb0_t FWB0;
		typedef rw16_t<0x007FC138> fwb1_t;
		static fwb1_t FWB1;
		typedef rw16_t<0x007FC140> fwb2_t;
		static fwb2_t FWB2;
		typedef rw16_t<0x007FC144> fwb3_t;
		static fwb3_t FWB3;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 0 (FSTATR0)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr0_t_ : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  ERERR;
			bit_ro_t<io_, bitpos::B1>  PRGERR;
			bit_ro_t<io_, bitpos::B3>  BCERR;
			bit_ro_t<io_, bitpos::B4>  ILGLERR;
			bit_ro_t<io_, bitpos::B5>  EILGLERR;
		};
		typedef fstatr0_t_<0x007FC1F0> fstatr0_t;
		static fstatr0_t FSTATR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 1 (FSTATR1)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr1_t_ : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B6>  FRDY;
			bit_ro_t<io_, bitpos::B7>  EXRDY;
		};
		typedef fstatr1_t_<0x007FC12C> fstatr1_t;
		static fstatr1_t FSTATR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ H (FEAMH)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1E8> feamh_t;
		static feamh_t FEAMH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ L (FEAML)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1E0> feaml_t;
		static feaml_t FEAML;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュスタートアップ設定モニタレジスタ (FSCMR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fscmr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>  SASMF;
		};
		typedef fscmr_t_<0x007FC1C0> fscmr_t;
		static fscmr_t FSCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ開始アドレスモニタレジスタ (FAWSMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1C8> fawsmr_t;
		static fawsmr_t FAWSMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ終了アドレスモニタレジスタ (FAWEMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x007FC1D0> fawemr_t;
		static fawemr_t FAWEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007FC350> uidr0_t;
		static uidr0_t UIDR0;
		typedef rw32_t<0x007FC354> uidr1_t;
		static uidr1_t UIDR1;
		typedef rw32_t<0x007FC358> uidr2_t;
		static uidr2_t UIDR2;
		typedef rw32_t<0x007FC35C> uidr3_t;
		static uidr3_t UIDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ROM キャッシュ許可レジスタ (ROMCE)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct romce_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ROMCEN;
		};
		typedef romce_t_<0x00081000> romce_t;
		static romce_t ROMCE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ROM キャッシュ無効化レジスタ (ROMCIV)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct romciv_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ROMCIV;
		};
		typedef romciv_t_<0x00081004> romciv_t;
		static romciv_t ROMCIV;


	};
	typedef flash_t_<void> FLASH;
	template<class _> typename flash_t_<_>::dflctl_t flash_t_<_>::DFLCTL;
	template<class _> typename flash_t_<_>::fentryr_t flash_t_<_>::FENTRYR;
	template<class _> typename flash_t_<_>::fpr_t flash_t_<_>::FPR;
	template<class _> typename flash_t_<_>::fpsr_t flash_t_<_>::FPSR;
	template<class _> typename flash_t_<_>::fpmcr_t flash_t_<_>::FPMCR;
	template<class _> typename flash_t_<_>::fisr_t flash_t_<_>::FISR;
	template<class _> typename flash_t_<_>::fresetr_t flash_t_<_>::FRESETR;
	template<class _> typename flash_t_<_>::fasr_t flash_t_<_>::FASR;
	template<class _> typename flash_t_<_>::fcr_t flash_t_<_>::FCR;
	template<class _> typename flash_t_<_>::fexcr_t flash_t_<_>::FEXCR;
	template<class _> typename flash_t_<_>::fsarh_t flash_t_<_>::FSARH;
	template<class _> typename flash_t_<_>::fsarl_t flash_t_<_>::FSARL;
	template<class _> typename flash_t_<_>::fearh_t flash_t_<_>::FEARH;
	template<class _> typename flash_t_<_>::fearl_t flash_t_<_>::FEARL;
	template<class _> typename flash_t_<_>::fwb0_t flash_t_<_>::FWB0;
	template<class _> typename flash_t_<_>::fwb1_t flash_t_<_>::FWB1;
	template<class _> typename flash_t_<_>::fwb2_t flash_t_<_>::FWB2;
	template<class _> typename flash_t_<_>::fwb3_t flash_t_<_>::FWB3;
	template<class _> typename flash_t_<_>::fstatr0_t flash_t_<_>::FSTATR0;
	template<class _> typename flash_t_<_>::fstatr1_t flash_t_<_>::FSTATR1;
	template<class _> typename flash_t_<_>::feamh_t flash_t_<_>::FEAMH;
	template<class _> typename flash_t_<_>::feaml_t flash_t_<_>::FEAML;
	template<class _> typename flash_t_<_>::fscmr_t flash_t_<_>::FSCMR;
	template<class _> typename flash_t_<_>::fawsmr_t flash_t_<_>::FAWSMR;
	template<class _> typename flash_t_<_>::fawemr_t flash_t_<_>::FAWEMR;
	template<class _> typename flash_t_<_>::uidr0_t flash_t_<_>::UIDR0;
	template<class _> typename flash_t_<_>::uidr1_t flash_t_<_>::UIDR1;
	template<class _> typename flash_t_<_>::uidr2_t flash_t_<_>::UIDR2;
	template<class _> typename flash_t_<_>::uidr3_t flash_t_<_>::UIDR3;
	template<class _> typename flash_t_<_>::romce_t flash_t_<_>::ROMCE;
	template<class _> typename flash_t_<_>::romciv_t flash_t_<_>::ROMCIV;
}
