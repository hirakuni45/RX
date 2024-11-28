#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・フラッシュ 定義 @n
			RX110 @n
			RX111 @n
			RX113 @n
			RX130 @n
			RX13T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー・ベース制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_base_t {

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
		typedef rw8_t<0x007F'C0C0> FPR_;
		static inline FPR_ FPR;


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
		static inline fpsr_t<0x007F'C0C1> FPSR;

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
		static inline fpmcr_t<0x007F'FF80> FPMCR;


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
		static inline fisr_t<0x007F'C0B6> FISR;


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
		static inline fresetr_t<0x007F'FF89> FRESETR;


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
		static inline fasr_t<0x007F'FF81> FASR;


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
			bit_rw_t <io_, bitpos::B4>     DRC;

			bit_rw_t <io_, bitpos::B6>     STOP;
			bit_rw_t <io_, bitpos::B7>     OPST;
		};
		static inline fcr_t<0x007F'FF85> FCR;


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
		static inline fexcr_t<0x007F'C0B7> FEXCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ H (FSARH)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007F'FF84> FSARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理開始アドレスレジスタ L (FSARL)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'FF82> FSARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ H (FEARH)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007F'FF88> FEARH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ処理終了アドレスレジスタ L (FEARL)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'FF86> FEARL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュリードバッファレジスタ H (FRBH)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C0C4> FRBH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュリードバッファレジスタ L (FRBL)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C0C2> FRBL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトバッファレジスタ H  (FWBH)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'FF8E> FWBH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトバッファレジスタ L  (FWBL)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'FF8C> FWBL;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 0 (FSTATR0)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr0_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  ERERR;
			bit_ro_t<in_, bitpos::B1>  PRGERR;

			bit_ro_t<in_, bitpos::B3>  BCERR;
			bit_ro_t<in_, bitpos::B4>  ILGLERR;
			bit_ro_t<in_, bitpos::B5>  EILGLERR;
		};
		static inline fstatr0_t<0x007F'FF8A> FSTATR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 1 (FSTATR1)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr1_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B1>  DRRDY;

			bit_ro_t<in_, bitpos::B6>  FRDY;
			bit_ro_t<in_, bitpos::B7>  EXRDY;
		};
		static inline fstatr1_t<0x007F'FF8B> FSTATR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ H (FEAMH)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007F'C0BA> FEAMH;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュエラーアドレスモニタレジスタ L (FEAML)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C0B8> FEAML;


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
		static inline fscmr_t<0x007F'C0B0> FSCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ開始アドレスモニタレジスタ (FAWSMR)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C0B2> FAWSMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウ終了アドレスモニタレジスタ (FAWEMR)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x007F'C0B4> FAWEMR;
	};

#if defined(SIG_RX110)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX110 フラッシュ・メモリー制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_t : public flash_base_t {

		static constexpr auto DATA_SIZE = 0;
		static constexpr uint32_t DATA_BLOCK_SIZE = 1;
		static constexpr uint32_t DATA_WORD_SIZE = 0;
		static constexpr auto ID_NUM = 4;

		static constexpr uint8_t  DF_VA_H = 0x0F;  ///< E2 データフラッシュアドレス（0x0F'1000）
		static constexpr uint16_t DF_VA_L = 0x1000;
	};

#elif defined(SIG_RX13T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX13T フラッシュ・メモリー制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_t : public flash_base_t {

		static constexpr auto DATA_SIZE = 0;
		static constexpr uint32_t DATA_BLOCK_SIZE = 1;
		static constexpr uint32_t DATA_WORD_SIZE = 0;
		static constexpr auto ID_NUM = 4;

		static constexpr uint8_t  DF_VA_H = 0x0F;  ///< E2 データフラッシュアドレス（0x0F'1000）
		static constexpr uint16_t DF_VA_L = 0x1000;

		//-----------------------------------------------------------------//
		/*!
			@brief  E2 データフラッシュ制御レジスタ (DFLCTL) @n
					RX111/RX113/RX130
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
	};

#else
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_t : public flash_base_t {

		static constexpr auto DATA_SIZE = 8192;
		static constexpr uint32_t DATA_BLOCK_SIZE = 1024;
		static constexpr uint32_t DATA_WORD_SIZE = 1;
		static constexpr auto ID_NUM = 4;

		static constexpr uint8_t  DF_VA_H = 0x0F;  ///< E2 データフラッシュアドレス（0x0F'1000）
		static constexpr uint16_t DF_VA_L = 0x1000;

		//-----------------------------------------------------------------//
		/*!
			@brief  E2 データフラッシュ制御レジスタ (DFLCTL) @n
					RX111/RX113/RX130
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
	};
#endif
	typedef flash_t FLASH;
}
