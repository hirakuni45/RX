#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  フラッシュ・メモリー制御クラス
		@param[in]	dsize	データフラッシュ容量
		@param[in]	idnum	ユニーク ID 数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t dsize, uint32_t idnum>
	struct flash_t {

		static constexpr auto DATA_SIZE = dsize;		///< データ領域のサイズ
		static constexpr uint32_t DATA_BLOCK_SIZE = 64;	///< データブロックのサイズ
		static constexpr uint32_t DATA_WORD_SIZE = 4;	///< 書き込み時のワードサイズ
		static constexpr auto ID_NUM = idnum;			///< ユニーク ID 数

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
		typedef fwepror_t<0x0008'C296> FWEPROR_;
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

			bit_rw_t<io_, bitpos::B0>  ECRCT;

			bit_rw_t<io_, bitpos::B3>  DFAE;
			bit_rw_t<io_, bitpos::B4>  CMDLK;

			bit_rw_t<io_, bitpos::B7>  CFAE;

		};
		typedef fastat_t<0x007F'E010> FASTAT_;
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

			bit_rw_t<io_, bitpos::B0>  ECRCTIE;

			bit_rw_t<io_, bitpos::B3>  DFAEIE;
			bit_rw_t<io_, bitpos::B4>  CMDLKIE;

			bit_rw_t<io_, bitpos::B7>  CFAEIE;

		};
		typedef faeint_t<0x007F'E014> FAEINT_;
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
		typedef frdyie_t<0x007F'E018> FRDYIE_;
		static FRDYIE_ FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理開始アドレスレジスタ（FSADDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007F'E030> FSADDR_;
		static FSADDR_ FSADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACI コマンド処理終了アドレスレジスタ（FEADDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x007F'E034> FEADDR_;
		static FEADDR_ FEADDR;


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
		typedef fcurame_t<0x007F'E054> FCURAME_;
		static FCURAME_ FCURAME;


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

			bit_ro_t <io_, bitpos::B0>   FRCRCT;
			bit_ro_t <io_, bitpos::B1>   FRDTCT;

			bit_ro_t <io_, bitpos::B6>   FLWEERR;
			bit_ro_t <io_, bitpos::B7>   FCUERR;

			bit_ro_t <io_, bitpos::B8>   PRGSPD;
			bit_ro_t <io_, bitpos::B9>   ERSSPD;
			bit_ro_t <io_, bitpos::B10>  DBFULL;
			bit_ro_t <io_, bitpos::B11>  SUSRDY;
			bit_ro_t <io_, bitpos::B12>  PRGERR;
			bit_ro_t <io_, bitpos::B13>  ERSERR;
			bit_ro_t <io_, bitpos::B14>  ILGERR;
			bit_ro_t <io_, bitpos::B15>  FRDY;
		};
		typedef fstatr_t<0x007F'E080> FSTATR_;
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
		typedef fentryr_t<0x007F'E084> FENTRYR_;
		static FENTRYR_ FENTRYR;


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
		typedef fprotr_t<0x007F'E088> FPROTR_;
		static FPROTR_ FPROTR;


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
		typedef fsuinitr_t<0x007F'E08C> FSUINITR_;
		static FSUINITR_ FSUINITR;


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
		typedef flkstat_t<0x007F'E090> FLKSTAT_;
		static FLKSTAT_ FLKSTAT;


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
		typedef fcmdr_t<0x007F'E0A0> FCMDR_;
		static FCMDR_ FCMDR;


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
		typedef fpestat_t<0x007F'E0C0> FPESTAT_;
		static FPESTAT_ FPESTAT;


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
		typedef fbccnt_t<0x007F'E0D0> FBCCNT_;
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
		typedef fbcstat_t<0x007F'E0D4> FBCSTAT_;
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

			bits_ro_t<io_, bitpos::B0, 19>  PSADR;  // RX72N: 17 bits
		};
		typedef fpsaddr_t<0x007F'E0D8> FPSADDR_;
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
		typedef fcpsr_t<0x007F'E0E0> FCPSR_;
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
		typedef fpckar_t<0x007F'E0E4> FPCKAR_;
		static FPCKAR_ FPCKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FACIコマンド発行領域 007E 0000h 4バイト
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x007E'0000> FACI_CMD_AREA_;
		static FACI_CMD_AREA_ FACI_CMD_AREA;		///< byte 書き込み
		typedef rw16_t<0x007E'0000> FACI_CMD_AREA16_;
		static FACI_CMD_AREA16_ FACI_CMD_AREA16;	///< word(16) 書き込み


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) 
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<0x007F'B174> UIDR0_;
		typedef ro32_t<0x007F'B1E4> UIDR1_;
		typedef ro32_t<0x007F'B1E8> UIDR2_;
		typedef ro32_t<0xFFFF'FFF4> UIDR3_;  ///< in VECTOR 

		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  EEPFCLK レジスタの設定 @n
					RX72N, RX72M にあるレジスタで、クロックジェネレーターの @n
					FCLK を変更する前に設定する必要がある。 @n
					この API は、system_io クラス、boost_master_clock から呼び出される。
			@param[in]	fclk	FCLK 周波数
		*/
		//-----------------------------------------------------------------//
		static void set_eepfclk(uint32_t fclk)
		{
		}
	};
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FWEPROR_  flash_t<dsize, idnum>::FWEPROR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FASTAT_   flash_t<dsize, idnum>::FASTAT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FAEINT_   flash_t<dsize, idnum>::FAEINT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FRDYIE_   flash_t<dsize, idnum>::FRDYIE;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FSADDR_   flash_t<dsize, idnum>::FSADDR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FEADDR_   flash_t<dsize, idnum>::FEADDR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FCURAME_  flash_t<dsize, idnum>::FCURAME;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FSTATR_   flash_t<dsize, idnum>::FSTATR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FENTRYR_  flash_t<dsize, idnum>::FENTRYR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPROTR_   flash_t<dsize, idnum>::FPROTR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FSUINITR_ flash_t<dsize, idnum>::FSUINITR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FLKSTAT_  flash_t<dsize, idnum>::FLKSTAT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FCMDR_    flash_t<dsize, idnum>::FCMDR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPESTAT_  flash_t<dsize, idnum>::FPESTAT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FBCCNT_   flash_t<dsize, idnum>::FBCCNT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FBCSTAT_  flash_t<dsize, idnum>::FBCSTAT;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPSADDR_  flash_t<dsize, idnum>::FPSADDR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FCPSR_    flash_t<dsize, idnum>::FCPSR;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FPCKAR_   flash_t<dsize, idnum>::FPCKAR;

	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FACI_CMD_AREA_ flash_t<dsize, idnum>::FACI_CMD_AREA;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::FACI_CMD_AREA16_ flash_t<dsize, idnum>::FACI_CMD_AREA16;

	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR0_  flash_t<dsize, idnum>::UIDR0;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR1_  flash_t<dsize, idnum>::UIDR1;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR2_  flash_t<dsize, idnum>::UIDR2;
	template <uint32_t dsize, uint32_t idnum> typename flash_t<dsize, idnum>::UIDR3_  flash_t<dsize, idnum>::UIDR3;

	typedef flash_t<65536, 3> FLASH;
}
