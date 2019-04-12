#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65N/RX66T グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2019 Kunihito Hiramatsu @n
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
	struct flash_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E プロテクトレジスタ（FWEPROR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fwepror_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> FLWE;
		};
		static fwepror_t<0x0008C296> FWEPROR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスステータスレジスタ（FASTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fastat_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_rw_t<io_, bitpos::B0>  ECRCT;
#endif
			bit_rw_t<io_, bitpos::B3>  DFAE;
			bit_rw_t<io_, bitpos::B4>  CMDLK;

			bit_rw_t<io_, bitpos::B7>  CFAE;

		};
		static fastat_t<0x007FE010> FASTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスエラー割り込み許可レジスタ（FAEINT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct faeint_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_rw_t<io_, bitpos::B0>  ECRCTIE;
#endif
			bit_rw_t<io_, bitpos::B3>  DFAEIE;
			bit_rw_t<io_, bitpos::B4>  CMDLKIE;

			bit_rw_t<io_, bitpos::B7>  CFAEIE;

		};
		static faeint_t<0x007FE014> FAEINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュレディ割り込み許可レジスタ（FRDYIE）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct frdyie_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  FRDYIE;
		};
		static frdyie_t<0x007FE018> FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理開始アドレスレジスタ（FSADDR）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x007FE030> FSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理終了アドレスレジスタ（FEADDR）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x007FE034> FEADDR;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		//-----------------------------------------------------------------//
		/*!
			@brief  FCURAM イネーブルレジスタ（FCURAME）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcurame_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     FCRME;
			bit_rw_t <io_, bitpos::B1>     FRAMTRAN;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static fcurame_t<0x007FE054> FCURAME;
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ（FSTATR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_ro_t <io_, bitpos::B0>   FRCRCT;
			bit_ro_t <io_, bitpos::B1>   FRDTCT;
#endif
			bit_ro_t <io_, bitpos::B6>   FLWEERR;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_ro_t <io_, bitpos::B7>   FCUERR;
#endif
			bit_ro_t <io_, bitpos::B8>   PRGSPD;
			bit_ro_t <io_, bitpos::B9>   ERSSPD;
			bit_ro_t <io_, bitpos::B10>  DBFULL;
			bit_ro_t <io_, bitpos::B11>  SUSRDY;
			bit_ro_t <io_, bitpos::B12>  PRGERR;
			bit_ro_t <io_, bitpos::B13>  ERSERR;
			bit_ro_t <io_, bitpos::B14>  ILGERR;
			bit_ro_t <io_, bitpos::B15>  FRDY;
		};
		static fstatr_t<0x007FE080> FSTATR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E モードエントリレジスタ（FENTRYR）
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

			bit_rw_t <io_, bitpos::B0>     FENTRYC;
			bit_rw_t <io_, bitpos::B7>     FENTRYD;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static fentryr_t<0x007FE084> FENTRYR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュプロテクトレジスタ（FPROTR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fprotr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     FPROTCN;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static fprotr_t<0x007FE088> FPROTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ設定初期化レジスタ（FSUINITR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fsuinitr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     SUINIT;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static fsuinitr_t<0x007FE08C> FSUINITR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ロックビットステータスレジスタ（FLKSTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct flkstat_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  FLOCKST;
		};
		static flkstat_t<0x007FE090> FLKSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンドレジスタ（FCMDR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcmdr_t : public ro16_t<base> {
			typedef ro16_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  PCMDR;
			bits_ro_t<io_, bitpos::B8, 8>  CMDDR;
		};
		static fcmdr_t<0x007FE0A0> FCMDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E ステータスレジスタ（FPESTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpestat_t : public ro16_t<base> {
			typedef ro16_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  PEERRST;
		};
		static fpestat_t<0x007FE0C0> FPESTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェック制御レジスタ（FBCCNT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fbccnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BCDIR;
		};
		static fbccnt_t<0x007FE0D0> FBCCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェックステータスレジスタ（FBCSTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fbcstat_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BCST;
		};
		static fbcstat_t<0x007FE0D4> FBCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ書き込み開始アドレスレジスタ（FPSADDR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpsaddr_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 19>  PSADR;
		};
		static fpsaddr_t<0x007FE0D8> FPSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ処理切り替えレジスタ（FCPSR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcpsr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ESUSPMD;
		};
		static fcpsr_t<0x007FE0E0> FCPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ処理クロック通知レジスタ（FPCKAR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpckar_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  PCKA;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static fpckar_t<0x007FE0E4> FPCKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					※RX64M、RX71M には無い
		*/
		//-----------------------------------------------------------------//
#if defined(SIG_RX24T)
		static ro32_t<0x007FC350> UIDR0;
		static ro32_t<0x007FC354> UIDR1;
		static ro32_t<0x007FC358> UIDR2;
		static ro32_t<0x007FC35C> UIDR3;
#elif defined(SIG_RX65N)
		static ro32_t<0xFE7F7D90> UIDR0;
		static ro32_t<0xFE7F7D94> UIDR1;
		static ro32_t<0xFE7F7D98> UIDR2;
		static ro32_t<0xFE7F7D9C> UIDR3;
#elif defined(SIG_RX66T)
		static ro32_t<0x007FB174> UIDR0;
		static ro32_t<0x007FB1E4> UIDR1;
		static ro32_t<0x007FB1E8> UIDR2;
#endif
	};
	typedef flash_t FLASH;
}
