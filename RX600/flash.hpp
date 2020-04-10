#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX72M/RX65N/RX66T/RX72T グループ・フラッシュ 定義
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
	template<class _>
	struct flash_t_ {

		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E プロテクトレジスタ（FWEPROR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fwepror_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> FLWE;
		};
		typedef fwepror_t_<0x0008C296> fwepror_t;
		static fwepror_t FWEPROR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスステータスレジスタ（FASTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fastat_t_ : public rw8_t<base> {
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
		typedef fastat_t_<0x007FE010> fastat_t;
		static fastat_t FASTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスエラー割り込み許可レジスタ（FAEINT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct faeint_t_ : public rw8_t<base> {
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
		typedef faeint_t_<0x007FE014> faeint_t;
		static faeint_t FAEINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュレディ割り込み許可レジスタ（FRDYIE）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct frdyie_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  FRDYIE;
		};
		typedef frdyie_t_<0x007FE018> frdyie_t;
		static frdyie_t FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理開始アドレスレジスタ（FSADDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007FE030> fsaddr_t;
		static fsaddr_t FSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理終了アドレスレジスタ（FEADDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007FE034> feaddr_t;
		static feaddr_t FEADDR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		//-----------------------------------------------------------------//
		/*!
			@brief  FCURAM イネーブルレジスタ（FCURAME）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcurame_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     FCRME;
			bit_rw_t <io_, bitpos::B1>     FRAMTRAN;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fcurame_t_<0x007FE054> fcurame_t;
		static fcurame_t FCURAME;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ（FSTATR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr_t_ : public ro32_t<base> {
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
#if defined(SIG_RX72M)
			bit_ro_t <io_, bitpos::B20>  OTERR;
			bit_ro_t <io_, bitpos::B21>  SECERR;
			bit_ro_t <io_, bitpos::B22>  FESETERR;
			bit_ro_t <io_, bitpos::B23>  ILGCOMERR;
#endif
		};
		typedef fstatr_t_<0x007FE080> fstatr_t;
		static fstatr_t FSTATR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E モードエントリレジスタ（FENTRYR）
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

			bit_rw_t <io_, bitpos::B0>     FENTRYC;
			bit_rw_t <io_, bitpos::B7>     FENTRYD;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fentryr_t_<0x007FE084> fentryr_t;
		static fentryr_t FENTRYR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) 
		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュプロテクトレジスタ（FPROTR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fprotr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     FPROTCN;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fprotr_t_<0x007FE088> fprotr_t;
		static fprotr_t FPROTR;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ設定初期化レジスタ（FSUINITR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fsuinitr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     SUINIT;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fsuinitr_t_<0x007FE08C> fsuinitr_t;
		static fsuinitr_t FSUINITR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) 
		//-----------------------------------------------------------------//
		/*!
			@brief  ロックビットステータスレジスタ（FLKSTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct flkstat_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  FLOCKST;
		};
		typedef flkstat_t_<0x007FE090> flkstat_t;
		static flkstat_t FLKSTAT;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンドレジスタ（FCMDR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcmdr_t_ : public ro16_t<base> {
			typedef ro16_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  PCMDR;
			bits_ro_t<io_, bitpos::B8, 8>  CMDDR;
		};
		typedef fcmdr_t_<0x007FE0A0> fcmdr_t;
		static fcmdr_t FCMDR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) 
		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E ステータスレジスタ（FPESTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpestat_t_ : public ro16_t<base> {
			typedef ro16_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  PEERRST;
		};
		typedef fpestat_t_<0x007FE0C0> fpestat_t;
		static fpestat_t FPESTAT;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェック制御レジスタ（FBCCNT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fbccnt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BCDIR;
		};
		typedef fbccnt_t_<0x007FE0D0> fbccnt_t;
		static fbccnt_t FBCCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェックステータスレジスタ（FBCSTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fbcstat_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BCST;
		};
		typedef fbcstat_t_<0x007FE0D4> fbcstat_t;
		static fbcstat_t FBCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ書き込み開始アドレスレジスタ（FPSADDR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpsaddr_t_ : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 19>  PSADR;
		};
		typedef fpsaddr_t_<0x007FE0D8> fpsaddr_t;
		static fpsaddr_t FPSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ処理切り替えレジスタ（FCPSR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcpsr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ESUSPMD;
		};
		typedef fcpsr_t_<0x007FE0E0> fcpsr_t;
		static fcpsr_t FCPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ処理クロック通知レジスタ（FPCKAR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpckar_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  PCKA;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fpckar_t_<0x007FE0E4> fpckar_t;
		static fpckar_t FPCKAR;


#if defined(SIG_RX72M)
		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウモニタレジスタ (FAWMON)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fawmon_t_ : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0,  12>  FAWS;
			bit_ro_t <io_, bitpos::B15>      FSPR;
			bits_ro_t<io_, bitpos::B16, 12>  FAWE;
			bit_ro_t <io_, bitpos::B31>      BTFLG;
		};
		typedef fawmon_t_<0x007FE0DC> fawmon_t;
		static fawmon_t FAWMON;


		//-----------------------------------------------------------------//
		/*!
			@brief  スタートアップ領域コントロールレジスタ (FSUACR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fsuacr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  SAS;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fsuacr_t_<0x007FE0E8> fsuacr_t;
		static fsuacr_t FSUACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュメモリアクセス周波数設定レジスタ (EEPFCLK)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x007FC040> eepfclk_t;
		static eepfclk_t EEPFCLK;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					※RX64M、RX71M には無い
		*/
		//-----------------------------------------------------------------//
#if defined(SIG_RX24T)
		typedef ro32_t<0x007FC350> uidr0_t;
		static uidr0_t UIDR0;
		typedef ro32_t<0x007FC354> uidr1_t;
		static uidr1_t UIDR1;
		typedef ro32_t<0x007FC358> uidr2_t;
		static uidr2_t UIDR2;
		typedef ro32_t<0x007FC35C> uidr3_t;
		static uidr3_t UIDR3;
#elif defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef ro32_t<0xFE7F7D90> uidr0_t;
		static uidr0_t UIDR0;
		typedef ro32_t<0xFE7F7D94> uidr1_t;
		static uidr1_t UIDR1;
		typedef ro32_t<0xFE7F7D98> uidr2_t;
		static uidr2_t UIDR2;
		typedef ro32_t<0xFE7F7D9C> uidr3_t;
		static uidr3_t UIDR3;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
		typedef ro32_t<0x007FB174> uidr0_t;
		static uidr0_t UIDR0;
		typedef ro32_t<0x007FB1E4> uidr1_t;
		static uidr1_t UIDR1;
		typedef ro32_t<0x007FB1E8> uidr2_t;
		static uidr2_t UIDR2;
#endif
	};
	typedef flash_t_<void> FLASH;
	template<class _> typename flash_t_<_>::fwepror_t flash_t_<_>::FWEPROR;
	template<class _> typename flash_t_<_>::fastat_t flash_t_<_>::FASTAT;
	template<class _> typename flash_t_<_>::faeint_t flash_t_<_>::FAEINT;
	template<class _> typename flash_t_<_>::frdyie_t flash_t_<_>::FRDYIE;
	template<class _> typename flash_t_<_>::fsaddr_t flash_t_<_>::FSADDR;
	template<class _> typename flash_t_<_>::feaddr_t flash_t_<_>::FEADDR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	template<class _> typename flash_t_<_>::fcurame_t flash_t_<_>::FCURAME;
#endif
	template<class _> typename flash_t_<_>::fstatr_t flash_t_<_>::FSTATR;
	template<class _> typename flash_t_<_>::fentryr_t flash_t_<_>::FENTRYR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) 
	template<class _> typename flash_t_<_>::fprotr_t flash_t_<_>::FPROTR;
#endif
	template<class _> typename flash_t_<_>::fsuinitr_t flash_t_<_>::FSUINITR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) 
	template<class _> typename flash_t_<_>::flkstat_t flash_t_<_>::FLKSTAT;
#endif
	template<class _> typename flash_t_<_>::fcmdr_t flash_t_<_>::FCMDR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) 
	template<class _> typename flash_t_<_>::fpestat_t flash_t_<_>::FPESTAT;
#endif
	template<class _> typename flash_t_<_>::fbccnt_t flash_t_<_>::FBCCNT;
	template<class _> typename flash_t_<_>::fbcstat_t flash_t_<_>::FBCSTAT;
	template<class _> typename flash_t_<_>::fpsaddr_t flash_t_<_>::FPSADDR;
	template<class _> typename flash_t_<_>::fcpsr_t flash_t_<_>::FCPSR;
	template<class _> typename flash_t_<_>::fpckar_t flash_t_<_>::FPCKAR;
#if defined(SIG_RX72M)
	template<class _> typename flash_t_<_>::fawmon_t flash_t_<_>::FAWMON;
	template<class _> typename flash_t_<_>::fsuacr_t flash_t_<_>::FSUACR;
	template<class _> typename flash_t_<_>::eepfclk_t flash_t_<_>::EEPFCLK;
#endif
#if defined(SIG_RX24T)
	template<class _> typename flash_t_<_>::uidr0_t flash_t_<_>::UIDR0;
	template<class _> typename flash_t_<_>::uidr1_t flash_t_<_>::UIDR1;
	template<class _> typename flash_t_<_>::uidr2_t flash_t_<_>::UIDR2;
	template<class _> typename flash_t_<_>::uidr3_t flash_t_<_>::UIDR3;
#elif defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template<class _> typename flash_t_<_>::uidr0_t flash_t_<_>::UIDR0;
	template<class _> typename flash_t_<_>::uidr1_t flash_t_<_>::UIDR1;
	template<class _> typename flash_t_<_>::uidr2_t flash_t_<_>::UIDR2;
	template<class _> typename flash_t_<_>::uidr3_t flash_t_<_>::UIDR3;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	template<class _> typename flash_t_<_>::uidr0_t flash_t_<_>::UIDR0;
	template<class _> typename flash_t_<_>::uidr1_t flash_t_<_>::UIDR1;
	template<class _> typename flash_t_<_>::uidr2_t flash_t_<_>::UIDR2;
#endif
}
