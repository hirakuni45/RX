#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
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
	struct flash_t {

		static constexpr uint32_t DATA_FLASH_ORG = 0x0010'0000;	///< データ・フラッシュ開始アドレス 
		static constexpr uint32_t DATA_FLASH_SIZE = 8192;		///< データ・フラッシュ、サイズ
		static constexpr uint32_t DATA_FLASH_BLOCK = 64;		///< データ・フラッシュ、ブロックサイズ(128)
		static constexpr uint32_t DATA_WORD_SIZE = 2;			///< データ・フラッシュ最小書き込みサイズ

		static constexpr auto ID_NUM = 0;						///< 個別識別子数

		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトイレーズプロテクトレジスタ（FWEPROR）
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
			@brief  フラッシュステータスレジスタ 0（FSTATR0）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fstatr0_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_rw_t<io_, bitpos::B0>  PRGSPD;
			bit_rw_t<io_, bitpos::B1>  ERSSPD;

			bit_rw_t<io_, bitpos::B3>  SUSRDY;
			bit_rw_t<io_, bitpos::B4>  PRGERR;
			bit_rw_t<io_, bitpos::B5>  ERSERR;
			bit_rw_t<io_, bitpos::B6>  ILGERR;
			bit_rw_t<io_, bitpos::B7>  FRDY;
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
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_rw_t<io_, bitpos::B4>  FLOCKST;

			bit_rw_t<io_, bitpos::B7>  FCUERR;
		};
		static inline fstatr1_t<0x007F'FFB1> FSTATR1;


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
			bits_rw_t<io_, bitpos::B8, 8> FEKEY;
		};
		static inline fentryr_t<0x007F'C4B2> FENTRYR;


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

			bits_rw_t<io_, bitpos::B8, 8> KEY;
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

			bits_rw_t<io_, bitpos::B8, 8> KEY;
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
			typedef ro16_t<base> io_;
			using io_::operator ();

			bits_rw_t<io_, bitpos::B0, 8> PCMDR;

			bits_rw_t<io_, bitpos::B8, 8> CMDR;
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
			@brief  フラッシュ P/E ステータスレジスタ（FPESTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fpestat_t : public ro16_t<base> {
			typedef ro16_t<base> io_;
			using io_::operator ();

			bits_rw_t<io_, bitpos::B0, 8> PEERRST;
		};
		static inline fpestat_t<0x007F'FFCC> FPESTAT;


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

			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef dflre0_t<0x007F'C440> DFLRE0_;
		static inline DFLRE0_ DFLRE0;


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

			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef dflwe0_t<0x007F'C450> DFLWE0_;
		static inline DFLWE0_ DFLWE0;


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
			@brief  データフラッシュブランクチェックステータスレジスタ（DFLBCSTAT）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dflbcstat_t : public ro16_t<base> {
			typedef ro16_t<base> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>    BCST;
		};
		static inline dflbcstat_t<0x007F'FFCE> DFLBCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					UID が無いので、ROM 内のダミーデータを返す @n
					ROM 0xFFFF'FFE8 to 0xFFFF'FFF7 互換性ダミー
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<0xFFFF'FFE8> UIDR0;
		static inline ro32_t<0xFFFF'FFEC> UIDR1;
		static inline ro32_t<0xFFFF'FFF0> UIDR2;
		static inline ro32_t<0xFFFF'FFF4> UIDR3;
	};
	typedef flash_t FLASH;
}
