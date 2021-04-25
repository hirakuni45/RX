#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX72M/RX65N/RX66T/RX72T/RX72N グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
		@param[in]	dsize	データフラッシュ容量
		@param[in]	idnum	ID 数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t dsize, uint32_t idnum>
	struct flash_t {

		static const auto DATA_SIZE = dsize;
		static const uint32_t DATA_BLOCK_SIZE = 64;
		static const auto ID_NUM = idnum;

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


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72T) 
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


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72T)
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


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72T)
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

			bits_ro_t<io_, bitpos::B0, 19>  PSADR;
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


#if defined(SIG_RX72M) || defined(SIG_RX72N)
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
					※RX64M、RX71M には無いので仮想レジスタとしてダミーを定義
		*/
		//-----------------------------------------------------------------//
#if defined(SIG_RX64M) || defined(SIG_RX71M)
		typedef ro32_t<0xFFFFFFE8> UIDR0_;  ///< in VECTOR 
		typedef ro32_t<0xFFFFFFEC> UIDR1_;  ///< in VECTOR 
		typedef ro32_t<0xFFFFFFF0> UIDR2_;  ///< in VECTOR 
		typedef ro32_t<0xFFFFFFF4> UIDR3_;  ///< in VECTOR 
#elif defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef ro32_t<0xFE7F7D90> UIDR0_;
		typedef ro32_t<0xFE7F7D94> UIDR1_;
		typedef ro32_t<0xFE7F7D98> UIDR2_;
		typedef ro32_t<0xFE7F7D9C> UIDR3_;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
		typedef ro32_t<0x007FB174> UIDR0_;
		typedef ro32_t<0x007FB1E4> UIDR1_;
		typedef ro32_t<0x007FB1E8> UIDR2_;
		typedef ro32_t<0xFFFFFFF4> UIDR3_;  ///< in VECTOR 
#endif
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;
	};
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FWEPROR_  flash_t<dsize, idnum>::FWEPROR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FASTAT_   flash_t<dsize, idnum>::FASTAT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FAEINT_   flash_t<dsize, idnum>::FAEINT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FRDYIE_   flash_t<dsize, idnum>::FRDYIE;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FSADDR_   flash_t<dsize, idnum>::FSADDR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FEADDR_   flash_t<dsize, idnum>::FEADDR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FCURAME_  flash_t<dsize, idnum>::FCURAME;
#endif
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FSTATR_   flash_t<dsize, idnum>::FSTATR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FENTRYR_  flash_t<dsize, idnum>::FENTRYR;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPROTR_   flash_t<dsize, idnum>::FPROTR;
#endif
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FSUINITR_ flash_t<dsize, idnum>::FSUINITR;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FLKSTAT_  flash_t<dsize, idnum>::FLKSTAT;
#endif
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FCMDR_    flash_t<dsize, idnum>::FCMDR;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPESTAT_  flash_t<dsize, idnum>::FPESTAT;
#endif
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FBCCNT_   flash_t<dsize, idnum>::FBCCNT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FBCSTAT_  flash_t<dsize, idnum>::FBCSTAT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPSADDR_  flash_t<dsize, idnum>::FPSADDR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FCPSR_    flash_t<dsize, idnum>::FCPSR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPCKAR_   flash_t<dsize, idnum>::FPCKAR;
#if defined(SIG_RX72M) || defined(SIG_RX72N)
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FAWMON_   flash_t<dsize, idnum>::FAWMON;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FSUACR_   flash_t<dsize, idnum>::FSUACR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::EEPFCLK_  flash_t<dsize, idnum>::EEPFCLK;
#endif
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR0_  flash_t<dsize, idnum>::UIDR0;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR1_  flash_t<dsize, idnum>::UIDR1;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR2_  flash_t<dsize, idnum>::UIDR2;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR3_  flash_t<dsize, idnum>::UIDR3;

#if defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef flash_t<65536, 0> FLASH;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef flash_t<32768, 3> FLASH;
#else
	typedef flash_t<32768, 4> FLASH;
#endif
}
