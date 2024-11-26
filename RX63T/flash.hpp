#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・フラッシュ 定義 @n
			R5F563T[ECB]: 32K @n
			R5F563T[654]:  8K
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
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
		static constexpr uint32_t DATA_SIZE  = 8192;		///< データ・フラッシュ、サイズ
		static constexpr uint32_t DATA_BLOCK_SIZE = 32;		///< データ・フラッシュ、ブロックサイズ
		static constexpr uint32_t DATA_WORD_SIZE = 2;		///< データ・フラッシュ最小書き込みサイズ

		static constexpr auto ID_NUM = 0;					///< 個別識別子数

		static constexpr uint8_t DATA_PROG_CMD_2ND = 0x01;

		static inline rw8_t<DATA_ORG> FCU_DATA_CMD8;
		static inline rw16_t<DATA_ORG> FCU_DATA_CMD16;

		static constexpr uint32_t WRITE_WORD_TIME  = 2000;		///< 2mS (DATA_WORD_SIZE)
		static constexpr uint32_t ERASE_BLOCK_TIME = 20000;		///< 20mS (DATA_BLOCK_SIZE)
		static constexpr uint32_t CHECK_WORD_TIME  = 30;		///< 30uS (DATA_WORD_SIZE)
		static constexpr uint32_t CHECK_BLOCK_TIME = 700;		///< 0.7mS (DATA_BLOCK_SIZE)


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトイレースプロテクトレジスタ（FWEPROR）
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
			@brief  フラッシュモードレジスタ（FMODR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fmodr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4> FRDMD;
		};
		static inline fmodr_t<0x007F'C402> FMODR;


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

			bit_rw_t <io_, bitpos::B0> DFLWPE;
			bit_rw_t <io_, bitpos::B1> DFLRPE;

			bit_rw_t <io_, bitpos::B3> DFLAE;
			bit_rw_t <io_, bitpos::B4> CMDLK;

			bit_rw_t <io_, bitpos::B7> ROMAE;
		};
		static inline fastat_t<0x007F'C410> FASTAT;


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

			bit_rw_t <io_, bitpos::B0> DFLWPEIE;
			bit_rw_t <io_, bitpos::B1> DFLRPEIE;

			bit_rw_t <io_, bitpos::B3> DFLAEIE;
			bit_rw_t <io_, bitpos::B4> CMDLKIE;

			bit_rw_t <io_, bitpos::B7> ROMAEIE;
		};
		static inline faeint_t<0x007F'C411> FAEINT;


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

			bit_rw_t <io_, bitpos::B0>  FRDYIE;
		};
		static inline frdyie_t<0x007F'C412> FRDYIE;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ読み出し許可レジスタ 0（DFLRE0）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflre0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    DBRE00;
			bit_rw_t <io_, bitpos::B1>    DBRE01;
			bit_rw_t <io_, bitpos::B2>    DBRE02;
			bit_rw_t <io_, bitpos::B3>    DBRE03;
			bit_rw_t <io_, bitpos::B4>    DBRE04;
			bit_rw_t <io_, bitpos::B5>    DBRE05;
			bit_rw_t <io_, bitpos::B6>    DBRE06;
			bit_rw_t <io_, bitpos::B7>    DBRE07;
			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef dflre0_t<0x007F'C440> DFLRE0_;
		static inline DFLRE0_ DFLRE0;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ読み出し許可レジスタ 1（DFLRE1）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflre1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    DBRE08;
			bit_rw_t <io_, bitpos::B1>    DBRE09;
			bit_rw_t <io_, bitpos::B2>    DBRE10;
			bit_rw_t <io_, bitpos::B3>    DBRE11;
			bit_rw_t <io_, bitpos::B4>    DBRE12;
			bit_rw_t <io_, bitpos::B5>    DBRE13;
			bit_rw_t <io_, bitpos::B6>    DBRE14;
			bit_rw_t <io_, bitpos::B7>    DBRE15;
			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef dflre1_t<0x007F'C442> DFLRE1_;
		static inline DFLRE1_ DFLRE1;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ書き込み／消去許可レジスタ 0（DFLWE0）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflwe0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    DBWE00;
			bit_rw_t <io_, bitpos::B1>    DBWE01;
			bit_rw_t <io_, bitpos::B2>    DBWE02;
			bit_rw_t <io_, bitpos::B3>    DBWE03;
			bit_rw_t <io_, bitpos::B4>    DBWE04;
			bit_rw_t <io_, bitpos::B5>    DBWE05;
			bit_rw_t <io_, bitpos::B6>    DBWE06;
			bit_rw_t <io_, bitpos::B7>    DBWE07;
			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef dflwe0_t<0x007F'C450> DFLWE0_;
		static inline DFLWE0_ DFLWE0;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュ書き込み／消去許可レジスタ 1（DFLWE1）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflwe1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    DBWE08;
			bit_rw_t <io_, bitpos::B1>    DBWE09;
			bit_rw_t <io_, bitpos::B2>    DBWE10;
			bit_rw_t <io_, bitpos::B3>    DBWE11;
			bit_rw_t <io_, bitpos::B4>    DBWE12;
			bit_rw_t <io_, bitpos::B5>    DBWE13;
			bit_rw_t <io_, bitpos::B6>    DBWE14;
			bit_rw_t <io_, bitpos::B7>    DBWE15;
			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef dflwe1_t<0x007F'C452> DFLWE1_;
		static inline DFLWE1_ DFLWE1;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 0（FSTATR0）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr0_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  PRGSPD;
			bit_ro_t<in_, bitpos::B1>  ERSSPD;

			bit_ro_t<in_, bitpos::B3>  SUSRDY;
			bit_ro_t<in_, bitpos::B4>  PRGERR;
			bit_ro_t<in_, bitpos::B5>  ERSERR;
			bit_ro_t<in_, bitpos::B6>  ILGLERR;
			bit_ro_t<in_, bitpos::B7>  FRDY;
		};
		static inline fstatr0_t<0x007F'FFB0> FSTATR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュステータスレジスタ 1（FSTATR1）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr1_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B4>  FLOCKST;

			bit_ro_t<in_, bitpos::B7>  FCUERR;
		};
		static inline fstatr1_t<0x007F'FFB1> FSTATR1;


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

			bit_rw_t <io_, bitpos::B0>    FENTRY0;

			bit_rw_t <io_, bitpos::B7>    FENTRYD;
			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		static inline fentryr_t<0x007F'FFB2> FENTRYR;


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

			bit_rw_t <io_, bitpos::B0>    FPROTCN;

			bits_rw_t<io_, bitpos::B8, 8> FPKEY;
		};
		static inline fprotr_t<0x007F'FFB4> FPROTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュリセットレジスタ（FRESETR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fresetr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    FRESET;

			bits_rw_t<io_, bitpos::B8, 8> FRKEY;
		};
		static inline fresetr_t<0x007F'FFB6> FRESETR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FCU コマンドレジスタ（FCMDR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fcmdr_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 8> PCMDR;
			bits_ro_t<in_, bitpos::B8, 8> CMDR;
		};
		static inline fcmdr_t<0x007F'FFBA> FCMDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FCU 処理切り替えレジスタ（FCPSR）
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

			bit_rw_t <io_, bitpos::B0>    ESUSPMD;
		};
		static inline fcpsr_t<0x007F'FFC8> FCPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェック制御レジスタ（DFLBCCNT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflbccnt_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> BCADR;

			bit_rw_t <io_, bitpos::B15>    BCSIZE;
		};
		static inline dflbccnt_t<0x007F'FFCA> DFLBCCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ P/E ステータスレジスタ（FPESTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpestat_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 8> PEERRST;
		};
		static inline fpestat_t<0x007F'FFCC> FPESTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  データフラッシュブランクチェックステータスレジスタ（DFLBCSTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflbcstat_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>    BCST;
		};
		static inline dflbcstat_t<0x007F'FFCE> DFLBCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺クロック通知レジスタ（PCKAR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pckar_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> PCKA;
		};
		static inline pckar_t<0x007F'FFE8> PCKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ファームの転送
		*/
		//-----------------------------------------------------------------//
		static void transfer_farm() noexcept
		{
		}


		static bool FSTATR_FRDY() noexcept { return FSTATR0.FRDY(); }
		static bool FSTATR_ILGLERR() noexcept { return FSTATR0.ILGLERR(); }
		static bool FSTATR_ERSERR() noexcept { return FSTATR0.ERSERR(); }
		static bool FSTATR_PRGERR() noexcept { return FSTATR0.PRGERR(); }
		static bool ERASE_STATE() noexcept { return DFLBCSTAT.BCST() == 0; }


		static void enable_read(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			uint16_t mask = ena ? 0x00ff : 0x0000;
			DFLRE0 = DFLRE0.KEY.b(0x2D) | mask;
			DFLRE1 = DFLRE0.KEY.b(0xD2) | mask;
		}


		static void enable_write(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			uint16_t mask = ena ? 0x00ff : 0x0000;
			DFLWE0 = DFLWE0.KEY.b(0x1E) | mask;
			DFLWE1 = DFLWE0.KEY.b(0xE1) | mask;
		}


		static void reset_fcu() noexcept
		{
			// FCU 初期化
			FRESETR = FRESETR.FRKEY.b(0xCC) | FRESETR.FRESET.b(1);
			utils::delay::micro_second(35 * 2);  // Min: 35uS
			FRESETR = FRESETR.FRKEY.b(0xCC) | FRESETR.FRESET.b(0);
		}


		static void set_clock(uint32_t fclk) noexcept
		{
			PCKAR = fclk;
			FCU_DATA_CMD8  = 0xE9;
			FCU_DATA_CMD8  = 0x03;
			FCU_DATA_CMD16 = 0x0F0F;
			FCU_DATA_CMD16 = 0x0F0F;
			FCU_DATA_CMD16 = 0x0F0F;
			FCU_DATA_CMD8  = 0xD0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					ユニークレジスタは無いので、ROM 領域を読み出す @n
					ROM 0xFFFF'FFC0 to 0xFFFF'FFCF
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<0xFFFF'FFC0> UIDR0_;
		typedef ro32_t<0xFFFF'FFC4> UIDR1_;
		typedef ro32_t<0xFFFF'FFC8> UIDR2_;
		typedef ro32_t<0xFFFF'FFCC> UIDR3_;
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;
	};
	typedef flash_t FLASH;
}
