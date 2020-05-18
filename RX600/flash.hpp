#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX72M/RX65N/RX66T/RX72N グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
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
	template <class _>
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
		typedef fwepror_t<0x0008C296> FWEPROR_;
		static FWEPROR_ FWEPROR;


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
		typedef fastat_t<0x007FE010> FASTAT_;
		static FASTAT_ FASTAT;


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
		typedef faeint_t<0x007FE014> FAEINT_;
		static FAEINT_ FAEINT;


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
		typedef frdyie_t<0x007FE018> FRDYIE_;
		static FRDYIE_ FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理開始アドレスレジスタ（FSADDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007FE030> FSADDR_;
		static FSADDR_ FSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理終了アドレスレジスタ（FEADDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007FE034> FEADDR_;
		static FEADDR_ FEADDR;


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
		typedef fcurame_t<0x007FE054> FCURAME_;
		static FCURAME_ FCURAME;
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
#if defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_ro_t <io_, bitpos::B20>  OTERR;
			bit_ro_t <io_, bitpos::B21>  SECERR;
			bit_ro_t <io_, bitpos::B22>  FESETERR;
			bit_ro_t <io_, bitpos::B23>  ILGCOMERR;
#endif
		};
		typedef fstatr_t<0x007FE080> FSTATR_;
		static FSTATR_ FSTATR;


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
		typedef fentryr_t<0x007FE084> FENTRYR_;
		static FENTRYR_ FENTRYR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) 
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
		typedef fprotr_t<0x007FE088> FPROTR_;
		static FPROTR_ FPROTR;
#endif


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
		typedef fsuinitr_t<0x007FE08C> FSUINITR_;
		static FSUINITR_ FSUINITR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) 
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
		typedef flkstat_t<0x007FE090> FLKSTAT_;
		static FLKSTAT_ FLKSTAT;
#endif


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
		typedef fcmdr_t<0x007FE0A0> FCMDR_;
		static FCMDR_ FCMDR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) 
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
		typedef fpestat_t<0x007FE0C0> FPESTAT_;
		static FPESTAT_ FPESTAT;
#endif


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
		typedef fbccnt_t<0x007FE0D0> FBCCNT_;
		static FBCCNT_ FBCCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェックステータスレジスタ（FBCSTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fbcstat_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  BCST;
		};
		typedef fbcstat_t<0x007FE0D4> FBCSTAT_;
		static FBCSTAT_ FBCSTAT;


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

			bits_ro_t<io_, bitpos::B0, 17>  PSADR;
		};
		typedef fpsaddr_t<0x007FE0D8> FPSADDR_;
		static FPSADDR_ FPSADDR;


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
		typedef fcpsr_t<0x007FE0E0> FCPSR_;
		static FCPSR_ FCPSR;


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
		typedef fpckar_t<0x007FE0E4> FPCKAR_;
		static FPCKAR_ FPCKAR;


#if defined(SIG_RX72M) || defined(SIG_RX72N) || defined(SIG_RX72T)
		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウモニタレジスタ (FAWMON)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fawmon_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0,  12>  FAWS;

			bit_ro_t <io_, bitpos::B15>      FSPR;
			bits_ro_t<io_, bitpos::B16, 12>  FAWE;

			bit_ro_t <io_, bitpos::B31>      BTFLG;
		};
		typedef fawmon_t<0x007FE0DC> FAWMON_;
		static FAWMON_ FAWMON;


		//-----------------------------------------------------------------//
		/*!
			@brief  スタートアップ領域コントロールレジスタ (FSUACR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fsuacr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  SAS;

			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fsuacr_t<0x007FE0E8> FSUACR_;
		static FSUACR_ FSUACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュメモリアクセス周波数設定レジスタ (EEPFCLK)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x007FC040> EEPFCLK_;
		static EEPFCLK_ EEPFCLK;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					※RX64M、RX71M には無い
		*/
		//-----------------------------------------------------------------//
#if defined(SIG_RX24T)
		typedef ro32_t<0x007FC350> UIDR0_;
		typedef ro32_t<0x007FC354> UIDR1_;
		typedef ro32_t<0x007FC358> UIDR2_;
		typedef ro32_t<0x007FC35C> UIDR3_;
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;
#elif defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef ro32_t<0xFE7F7D90> UIDR0_;
		typedef ro32_t<0xFE7F7D94> UIDR1_;
		typedef ro32_t<0xFE7F7D98> UIDR2_;
		typedef ro32_t<0xFE7F7D9C> UIDR3_;
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
		typedef ro32_t<0x007FB174> UIDR0_;
		typedef ro32_t<0x007FB1E4> UIDR1_;
		typedef ro32_t<0x007FB1E8> UIDR2_;
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
#endif
	};
	typedef flash_t<void> FLASH;

	template <class _> typename flash_t<_>::FWEPROR_  flash_t<_>::FWEPROR;
	template <class _> typename flash_t<_>::FASTAT_   flash_t<_>::FASTAT;
	template <class _> typename flash_t<_>::FAEINT_   flash_t<_>::FAEINT;
	template <class _> typename flash_t<_>::FRDYIE_   flash_t<_>::FRDYIE;
	template <class _> typename flash_t<_>::FSADDR_   flash_t<_>::FSADDR;
	template <class _> typename flash_t<_>::FEADDR_   flash_t<_>::FEADDR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	template <class _> typename flash_t<_>::FCURAME_  flash_t<_>::FCURAME;
#endif
	template <class _> typename flash_t<_>::FSTATR_   flash_t<_>::FSTATR;
	template <class _> typename flash_t<_>::FENTRYR_  flash_t<_>::FENTRYR;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <class _> typename flash_t<_>::FPROTR_   flash_t<_>::FPROTR;
#endif
	template <class _> typename flash_t<_>::FSUINITR_ flash_t<_>::FSUINITR;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <class _> typename flash_t<_>::FLKSTAT_  flash_t<_>::FLKSTAT;
#endif
	template <class _> typename flash_t<_>::FCMDR_    flash_t<_>::FCMDR;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <class _> typename flash_t<_>::FPESTAT_  flash_t<_>::FPESTAT;
#endif
	template <class _> typename flash_t<_>::FBCCNT_   flash_t<_>::FBCCNT;
	template <class _> typename flash_t<_>::FBCSTAT_  flash_t<_>::FBCSTAT;
	template <class _> typename flash_t<_>::FPSADDR_  flash_t<_>::FPSADDR;
	template <class _> typename flash_t<_>::FCPSR_    flash_t<_>::FCPSR;
	template <class _> typename flash_t<_>::FPCKAR_   flash_t<_>::FPCKAR;
#if defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename flash_t<_>::FAWMON_   flash_t<_>::FAWMON;
	template <class _> typename flash_t<_>::FSUACR_   flash_t<_>::FSUACR;
	template <class _> typename flash_t<_>::EEPFCLK_  flash_t<_>::EEPFCLK;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M)
#else
	template <class _> typename flash_t<_>::UIDR0_  flash_t<_>::UIDR0;
	template <class _> typename flash_t<_>::UIDR1_  flash_t<_>::UIDR1;
	template <class _> typename flash_t<_>::UIDR2_  flash_t<_>::UIDR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T) || defined(SIG_RX72T)
#else
	template <class _> typename flash_t<_>::UIDR3_  flash_t<_>::UIDR3;
#endif
}
