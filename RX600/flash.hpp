#pragma once
//=============================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・フラッシュ 定義 @n
			・RX64M/RX71M @n
			・RX65N/RX651 @n
			・RX66N @n
			・RX660/RX671 @n
			・RX72N/RX72M @n
			・RX66T/RX72T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
		@param[in]	dsize	データフラッシュ容量
		@param[in]	idnum	ユニーク ID 数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t dsize, uint32_t idnum>
	struct flash_t {

		static constexpr auto DATA_SIZE = dsize;		///< データ領域のサイズ
		static constexpr uint32_t DATA_BLOCK_SIZE = 64;	///< データブロックのサイズ
		static constexpr uint32_t DATA_WORD_SIZE = 4;	///< 書き込み時のワードサイズ
		static constexpr auto ID_NUM = idnum;			///< ユニーク ID 数

#if defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72N) || defined(SIG_RX72M)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ許可レジスタ（ ROMCE ）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romce_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCEN;
		};
		static inline romce_t<0x0008'1000> ROMCE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ無効化レジスタ（ ROMCIV ）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romciv_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCIV;
		};
		static inline romciv_t<0x0008'1004> ROMCIV;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX660)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ許可レジスタ（ ROMCE ）ダミー
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romce_null_t : public rw16_null_t<base> {
			typedef rw16_null_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCEN;
		};
		static inline romce_null_t<0x0000'0000> ROMCE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ無効化レジスタ（ ROMCIV ）ダミー
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romciv_null_t : public rw16_null_t<base> {
			typedef rw16_null_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCIV;
		};
		static inline romciv_null_t<0x0000'0000> ROMCIV;
#endif


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
		static inline fwepror_t<0x0008'C296> FWEPROR;


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
		static inline fastat_t<0x007F'E010> FASTAT;


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
		static inline faeint_t<0x007F'E014> FAEINT;


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
		static inline frdyie_t<0x007F'E018> FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理開始アドレスレジスタ（FSADDR）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x007F'E030> FSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理終了アドレスレジスタ（FEADDR）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x007F'E034> FEADDR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651)
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
		static inline fcurame_t<0x007F'E054> FCURAME;
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
#if defined(SIG_RX72N) || defined(SIG_RX72M)
			bit_ro_t <io_, bitpos::B20>  OTERR;
			bit_ro_t <io_, bitpos::B21>  SECERR;
			bit_ro_t <io_, bitpos::B22>  FESETERR;
			bit_ro_t <io_, bitpos::B23>  ILGCOMERR;
#endif
		};
		static inline fstatr_t<0x007F'E080> FSTATR;


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
		static inline fentryr_t<0x007F'E084> FENTRYR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T) || defined(SIG_RX72T) 
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
		static inline fprotr_t<0x007F'E088> FPROTR;
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
		static inline fsuinitr_t<0x007F'E08C> FSUINITR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T) || defined(SIG_RX72T)
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
		static inline flkstat_t<0x007F'E090> FLKSTAT;
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
		static inline fcmdr_t<0x007F'E0A0> FCMDR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T) || defined(SIG_RX72T)
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
		static inline fpestat_t<0x007F'E0C0> FPESTAT;
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
		static inline fbccnt_t<0x007F'E0D0> FBCCNT;


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
		static inline fbcstat_t<0x007F'E0D4> FBCSTAT;


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

			bits_ro_t<io_, bitpos::B0, 19>  PSADR;  // RX72N: 17 bits
		};
		static inline fpsaddr_t<0x007F'E0D8> FPSADDR;


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
		static inline fcpsr_t<0x007F'E0E0> FCPSR;


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
		static inline fpckar_t<0x007F'E0E4> FPCKAR;


#if defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX72N) || defined(SIG_RX72M)
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
		static inline fawmon_t<0x007F'E0DC> FAWMON;


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
		static inline fsuacr_t<0x007F'E0E8> FSUACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュメモリアクセス周波数設定レジスタ (EEPFCLK)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007F'C040> EEPFCLK;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  FACIコマンド発行領域 007E 0000h 4バイト
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007E'0000> FACI_CMD_AREA;  ///< byte 書き込み
		static inline rw16_t<0x007E'0000> FACI_CMD_AREA16;  ///< word(16) 書き込み


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) 
		*/
		//-----------------------------------------------------------------//
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX660) || defined(SIG_RX66T) || defined(SIG_RX72T)
		static inline ro32_t<0x007F'B174> UIDR0;
		static inline ro32_t<0x007F'B1E4> UIDR1;
		static inline ro32_t<0x007F'B1E8> UIDR2;
		static inline ro32_t<0xFFFF'FFF4> UIDR3;  ///< in VECTOR 
#elif defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX72N) || defined(SIG_RX72M)
		static inline ro32_t<0xFE7F'7D90> UIDR0;
		static inline ro32_t<0xFE7F'7D94> UIDR1;
		static inline ro32_t<0xFE7F7'D98> UIDR2;
		static inline ro32_t<0xFE7F7'D9C> UIDR3;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  EEPFCLK レジスタの設定 @n
					RX671, RX72N, RX72M にあるレジスタで、クロックジェネレーターの @n
					FCLK を変更する前に設定する必要がある。 @n
					この API は、system_io クラス、boost_master_clock から呼び出される。
			@param[in]	fclk	FCLK 周波数
		*/
		//-----------------------------------------------------------------//
		static void set_eepfclk(uint32_t fclk)
		{
#if defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX72N) || defined(SIG_RX72M)
			// Set for DataFlash memory access clocks
			uint32_t clk = ((fclk / 500'000) + 1) >> 1;
			if(clk > 60) {
				clk = 60;
			}
			EEPFCLK = clk;
			while(EEPFCLK() != clk) { asm("nop"); }
#endif
		}
	};

#if defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef flash_t<65536, 3> FLASH;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef flash_t<32768, 3> FLASH;
#elif defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX66N) || defined(SIG_RX660) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef flash_t<32768, 4> FLASH;
#elif defined(SIG_RX671)
	typedef flash_t<8192, 4> FLASH;
#endif
}
