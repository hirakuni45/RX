#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・フラッシュ・メモリ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"
#include "common/delay.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_t {

		static constexpr uint32_t CODE_ORG = 0xFFFF'FFF0;	///< コード領域コマンド開始アドレス
		static constexpr uint32_t DATA_ORG = 0x0010'0000;	///< データ・フラッシュ開始アドレス
		static constexpr uint32_t DATA_SIZE = 16384;		///< データ・フラッシュ、サイズ
		static constexpr uint32_t DATA_BLOCK_SIZE = 64;		///< データ・フラッシュ、ブロックサイズ
		static constexpr uint32_t DATA_WORD_SIZE = 4;		///< データ・フラッシュ最小書き込みサイズ
		static constexpr uint32_t ID_NUM = 3;				///< 個別識別子数

		static constexpr uint8_t DATA_PROG_CMD_2ND = 0x02;

		static constexpr uint32_t FACI_CMD_ORG = 0x007E'0000;	///< FACI コマンド発行領域
		static inline rw8_t<FACI_CMD_ORG> FCU_DATA_CMD8;
		static inline rw16_t<FACI_CMD_ORG> FCU_DATA_CMD16;

		static constexpr uint32_t WRITE_WORD_TIME  = 1700;	///< 1.7mS (DATA_WORD_SIZE)
		static constexpr uint32_t ERASE_BLOCK_TIME = 10000;	///< 10mS(64) (DATA_BLOCK_SIZE)
		static constexpr uint32_t CHECK_WORD_TIME  = 30;	///< 30 uS (DATA_WORD_SIZE)
		static constexpr uint32_t CHECK_BLOCK_TIME = 100;	///< 100 uS (DATA_BLOCK_SIZE)


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
		static inline fwepror_t<0x0008'C296> FWEPROR;


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

			bit_rw_t<io_, bitpos::B3> DFAE;
			bit_rw_t<io_, bitpos::B4> CMDLK;

			bit_rw_t<io_, bitpos::B7> CFAE;
		};
		static inline fastat_t<0x007F'E010> FASTAT;


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
		static inline faeint_t<0x007F'E014> FAEINT;


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
		static inline frdyie_t<0x007F'E018> FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理開始アドレスレジスタ (FSADDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x007F'E030> FSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理終了アドレスレジスタ (FEADDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x007F'E034> FEADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ (FSTATR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr_t : public ro32_t<base> {
			typedef ro32_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B6>  FLWERR;

			bit_ro_t<in_, bitpos::B8>  PRGSPD;
			bit_ro_t<in_, bitpos::B9>  ERSSPD;
			bit_ro_t<in_, bitpos::B10> DBFULL;
			bit_ro_t<in_, bitpos::B11> SUSRDY;
			bit_ro_t<in_, bitpos::B12> PRGERR;
			bit_ro_t<in_, bitpos::B13> ERSERR;
			bit_ro_t<in_, bitpos::B14> ILGLERR;
			bit_ro_t<in_, bitpos::B15> FRDY;
		};
		static inline fstatr_t<0x007F'E080> FSTATR;


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
		static inline fentryr_t<0x007F'E084> FENTRYR;


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
		static inline fsuinitr_t<0x007F'E08C> FSUINITR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンドレジスタ (FCMDR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcmdr_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 8>  PCMDR;
			bits_ro_t<in_, bitpos::B8, 8>  CMDR;
		};
		static inline fcmdr_t<0x007F'E0A0> FCMDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E ステータスレジスタ (FPESTAT)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpestat_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 8>  PEERRST;
		};
		static inline fpestat_t<0x007F'E0C0> FPESTAT;


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
		static inline fbccnt_t<0x007F'E0D0> FBCCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェックステータスレジスタ (FBCSTAT)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fbcstat_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  BCST;
		};
		static inline fbcstat_t<0x007F'E0D4> FBCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ書き込み開始アドレスレジスタ (FPSADDR)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpsaddr_t : public ro32_t<base> {
			typedef ro32_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 19> PSADR;
		};
		static inline fpsaddr_t<0x007F'E0D8> FPSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュアクセスウィンドウモニタレジスタ (FAWMON)
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fawmon_t : public ro32_t<base> {
			typedef ro32_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0,  13> FAWS;

			bit_ro_t <in_, bitpos::B15>     FSPR;
			bits_ro_t<in_, bitpos::B16, 13> FAWE;

			bit_ro_t <in_, bitpos::B31>     BTFLG;
		};
		static inline fawmon_t<0x007F'E0DC> FAWMON;


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
		static inline fcpsr_t<0x007F'E0E0> FCPSR;


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
		static inline fpckar_t<0x007F'E0E4> FPCKAR;


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
		static inline fsuacr_t<0x007F'E0E8> FSUACR;


		static bool FSTATR_FRDY() noexcept { return FSTATR.FRDY(); }
		static bool FSTATR_ILGLERR() noexcept { return FSTATR.ILGLERR(); }
		static bool FSTATR_ERSERR() noexcept { return FSTATR.ERSERR(); }
		static bool FSTATR_PRGERR() noexcept { return FSTATR.PRGERR(); }
		static bool ERASE_STATE() noexcept { return FBCSTAT.BCST() == 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ファームの転送 @n
					※RX26T ではファームの転送は必要無い
		*/
		//-----------------------------------------------------------------//
		static void transfer_farm() noexcept
		{
		}


		static void enable_read(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
		}


		static void enable_write(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			if(ena) {
				FSADDR = org;
				FEADDR = org + len;
			}
		}


		static bool set_clock(uint32_t fclk) noexcept
		{
			FPCKAR = FPCKAR.KEY.b(0x1E) | FPCKAR.PCKA.b(fclk);
			return true;
		}


		static void reset_fcu() noexcept
		{
			FSUINITR = FSUINITR.KEY.b(0x2D) | FSUINITR.SUINIT.b(1);
			utils::delay::micro_second(20 * 2);  // 20uS 以上 (32MHz)
			FSUINITR = FSUINITR.KEY.b(0x2D);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					UIDR3 はダミー（ROM エリアから読み込む）
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<0x007F'B174> UIDR0;
		static inline ro32_t<0x007F'B1E4> UIDR1;
		static inline ro32_t<0x007F'B1E8> UIDR2;
		static inline ro32_t<0xFFFF'FFF4> UIDR3;  // ダミー
	};
	typedef flash_t FLASH;
}
