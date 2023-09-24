#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct flash_t {

		static constexpr uint32_t DATA_SIZE = 16384;
		static constexpr uint32_t DATA_BLOCK_SIZE = 64;
		static constexpr uint32_t DATA_WORD_SIZE = 4;
		static constexpr uint32_t ID_NUM = 3;

		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E プロテクトレジスタ (FWEPROR)
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
		typedef fwepror_t<0x0008'C296> FWEPROR_;
		static FWEPROR_ FWEPROR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスステータスレジスタ (FASTAT)
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

			bits_rw_t<io_, bitpos::B0, 2> FLWE;
		};
		typedef fastat_t<0x007F'E010> FASTAT_;
		static FASTAT_ FASTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスエラー割り込み許可レジスタ (FAEINT)
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

			bit_rw_t<io_, bitpos::B3>  DFAEIE;
			bit_rw_t<io_, bitpos::B4>  CMDLKIE;

			bit_rw_t<io_, bitpos::B7>  CFAEIE;
		};
		typedef faeint_t<0x007F'E014> FAEINT_;
		static FAEINT_ FAEINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュレディ割り込み許可レジスタ (FRDYIE)
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
		typedef frdyie_t<0x007F'E018> FRDYIE_;
		static FRDYIE_ FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理開始アドレスレジスタ (FSADDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007F'E030> FSADDR_;
		static FSADDR_ FSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理終了アドレスレジスタ (FEADDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007F'E034> FEADDR_;
		static FEADDR_ FEADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ (FSTATR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B6>  FLWERR;

			bit_ro_t<io_, bitpos::B8>  PRGSPD;
			bit_ro_t<io_, bitpos::B9>  ERSSPD;
			bit_ro_t<io_, bitpos::B10> DBFULL;
			bit_ro_t<io_, bitpos::B11> SUSRDY;
			bit_ro_t<io_, bitpos::B12> PRGERR;
			bit_ro_t<io_, bitpos::B13> ERSERR;
			bit_ro_t<io_, bitpos::B14> ILGLERR;
			bit_ro_t<io_, bitpos::B15> FRDY;
		};
		typedef fstatr_t<0x007F'E080> FSTATR_;
		static FSTATR_ FSTATR;


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

			bit_rw_t <io_, bitpos::B0>     FENTRYC;

			bit_rw_t <io_, bitpos::B7>     FENTRYD;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef fentryr_t<0x007F'E084> FENTRYR_;
		static FENTRYR_ FENTRYR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ設定初期化レジスタ (FSUINITR)
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
		typedef fsuinitr_t<0x007F'E08C> FSUINITR_;
		static FSUINITR_ FSUINITR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンドレジスタ (FCMDR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcmdr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  PCMDR;
			bits_rw_t<io_, bitpos::B8, 8>  CMDR;
		};
		typedef fcmdr_t<0x007F'E0A0> FCMDR_;
		static FCMDR_ FCMDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E ステータスレジスタ (FPESTAT)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpestat_t : public ro16_t<base> {
			typedef ro16_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  PEERRST;
		};
		typedef fpestat_t<0x007F'E0C0> FPESTAT_;
		static FPESTAT_ FPESTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェック制御レジスタ (FBCCNT)
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
		typedef fbccnt_t<0x007F'E0D0> FBCCNT_;
		static FBCCNT_ FBCCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェックステータスレジスタ (FBCSTAT)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fbcstat_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  BCST;
		};
		typedef fbcstat_t<0x007F'E0D4> FBCSTAT_;
		static FBCSTAT_ FBCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ書き込み開始アドレスレジスタ (FPSADDR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpsaddr_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 19> PSADR;
		};
		typedef fpsaddr_t<0x007F'E0D8> FPSADDR_;
		static FPSADDR_ FPSADDR;


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

			bits_ro_t<io_, bitpos::B0,  13> FAWS;

			bit_ro_t <io_, bitpos::B15>     FSPR;
			bits_ro_t<io_, bitpos::B16, 13> FAWE;

			bit_ro_t <io_, bitpos::B31>     BTFLG;
		};
		typedef fawmon_t<0x007F'E0DC> FAWMON_;
		static FAWMON_ FAWMON;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ処理切り替えレジスタ (FCPSR)
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
		typedef fcpsr_t<0x007F'E0E0> FCPSR_;
		static FCPSR_ FCPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュシーケンサ処理クロック周波数通知レジスタ (FPCKAR)
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

			bits_rw_t<io_, bitpos::B0, 8> PCKA;
			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef fpckar_t<0x007F'E0E4> FPCKAR_;
		static FPCKAR_ FPCKAR;


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

			bits_rw_t<io_, bitpos::B0, 2> SAS;

			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef fsuacr_t<0x007F'E0E8> FSUACR_;
		static FSUACR_ FSUACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					UIDR3 はダミー（ROM エリアから読み込む）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<0x007F'B174> UIDR0_;
		typedef ro32_t<0x007F'B1E4> UIDR1_;
		typedef ro32_t<0x007F'B1E8> UIDR2_;
		typedef ro32_t<0xFFFF'FFF4> UIDR3_;
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;
	};
	typedef flash_t<void> FLASH;

	template<class _> typename flash_t<_>::FWEPROR_  flash_t<_>::FWEPROR;
	template<class _> typename flash_t<_>::FASTAT_   flash_t<_>::FASTAT;
	template<class _> typename flash_t<_>::FAEINT_   flash_t<_>::FAEINT;
	template<class _> typename flash_t<_>::FRDYIE_   flash_t<_>::FRDYIE;
	template<class _> typename flash_t<_>::FSADDR_   flash_t<_>::FSADDR;
	template<class _> typename flash_t<_>::FEADDR_   flash_t<_>::FEADDR;
	template<class _> typename flash_t<_>::FSTATR_   flash_t<_>::FSTATR;
	template<class _> typename flash_t<_>::FENTRYR_  flash_t<_>::FENTRYR;
	template<class _> typename flash_t<_>::FSUINITR_ flash_t<_>::FSUINITR;
	template<class _> typename flash_t<_>::FCMDR_    flash_t<_>::FCMDR;
	template<class _> typename flash_t<_>::FPESTAT_  flash_t<_>::FPESTAT;
	template<class _> typename flash_t<_>::FBCCNT_   flash_t<_>::FBCCNT;
	template<class _> typename flash_t<_>::FPSADDR_  flash_t<_>::FPSADDR;
	template<class _> typename flash_t<_>::FAWMON_   flash_t<_>::FAWMON;
	template<class _> typename flash_t<_>::FCPSR_    flash_t<_>::FCPSR;
	template<class _> typename flash_t<_>::FPCKAR_   flash_t<_>::FPCKAR;
	template<class _> typename flash_t<_>::FSUACR_   flash_t<_>::FSUACR;
	template<class _> typename flash_t<_>::UIDR0_    flash_t<_>::UIDR0;
	template<class _> typename flash_t<_>::UIDR1_    flash_t<_>::UIDR1;
	template<class _> typename flash_t<_>::UIDR2_    flash_t<_>::UIDR2;
	template<class _> typename flash_t<_>::UIDR3_    flash_t<_>::UIDR3;
}
