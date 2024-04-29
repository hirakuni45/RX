#pragma once
//=========================================================================//
/*!	@file
	@brief	RX13T/RX23T/RX24T/RX24U グループ・フラッシュ 定義 @n
			RX23T はデータフラッシュが無
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
		@param[in]	DSZ		データサイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t DSZ>
	struct flash_t {

		static constexpr auto DATA_SIZE = DSZ;
		static constexpr auto DATA_BLOCK_SIZE = 1024;
		static constexpr uint32_t DATA_WORD_SIZE = 1;
		static constexpr auto ID_NUM = 4;

#if defined(SIG_RX23T)
#else
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
		static inline dflctl_t<0x007F'C090> DFLCTL;
#endif

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
		static inline fentryr_t<0x007F'FFB2> FENTRYR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクト解除レジスタ (FPR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007F'C180> FPR;


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
		static inline fpsr_t<0x007F'C184> FPSR;


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
		static inline fpmcr_t<0x007F'C100> FPMCR;


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
		static inline fisr_t<0x007F'C1D8> FISR;


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
		static inline fresetr_t<0x007F'C124> FRESETR;


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
		static inline fasr_t<0x007F'C104> FASR;


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
		static inline fcr_t<0x007F'C114> FCR;


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
		static inline fexcr_t<0x007F'C1DC> FEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ H (FSARH)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C110> FSARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ L (FSARL)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C108> FSARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ H (FEARH)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007FC120> FEARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ L (FEARL)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C118> FEARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトバッファ n レジスタ (FWBn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C130> FWB0;
		static inline rw16_t<0x007F'C138> FWB1;
		static inline rw16_t<0x007F'C140> FWB2;
		static inline rw16_t<0x007F'C144> FWB3;


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
		static inline fstatr0_t<0x007F'C1F0> FSTATR0;


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
		static inline fstatr1_t<0x007F'C12C> FSTATR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ H (FEAMH)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C1E8> FEAMH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ L (FEAML)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C1E0> FEAML;


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
		static inline fscmr_t<0x007F'C1C0> FSCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ開始アドレスモニタレジスタ (FAWSMR)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C1C8> FAWSMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ終了アドレスモニタレジスタ (FAWEMR)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C1D0> FAWEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<0x007F'C350> UIDR0;
		static inline ro32_t<0x007F'C354> UIDR1;
		static inline ro32_t<0x007F'C358> UIDR2;
		static inline ro32_t<0x007F'C35C> UIDR3;


#if defined (SIG_RX24T) || defined(SIG_RX24U)
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
		static inline romce_t<0x0008'1000> ROMCE;


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
		static inline romciv_t<0x0008'1004> ROMCIV;
#endif
	};

#if defined(SIG_RX13T)
	typedef flash_t<4096> FLASH;
#elif defined(SIG_RX23T)
	typedef flash_t<0> FLASH;
#elif defined(SIG_RX24T) || defined(SIG_RX24U)
	typedef flash_t<8192> FLASH;
#endif
}
