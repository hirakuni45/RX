#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・フラッシュ 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
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

		static constexpr uint32_t DATA_FLASH_ORG = 0x0010'0000;	///< データ・フラッシュ開始アドレス 
		static constexpr uint32_t DATA_FLASH_SIZE = 32768;		///< データ・フラッシュ、サイズ
		static constexpr uint32_t DATA_FLASH_BLOCK = 2048;		///< データ・フラッシュ、ブロックサイズ
		static constexpr uint32_t DATA_WORD_SIZE = 2;			///< データ・フラッシュ最小書き込みサイズ

		static constexpr auto ID_NUM = 0;						///< 個別識別子数

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
		typedef fmodr_t<0x007F'C402> FMODR_;
		static FMODR_ FMODR;


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
		typedef fastat_t<0x007F'C410> FASTAT_;
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

			bit_rw_t <io_, bitpos::B0> DFLWPEIE;
			bit_rw_t <io_, bitpos::B1> DFLRPEIE;

			bit_rw_t <io_, bitpos::B3> DFLAEIE;
			bit_rw_t <io_, bitpos::B4> CMDLKIE;

			bit_rw_t <io_, bitpos::B7> ROMAEIE;
		};
		typedef faeint_t<0x007F'C411> FAEINT_;
		static FAEINT_ FAEINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  FCU RAM イネーブルレジスタ（FCURAME）
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

			bit_rw_t <io_, bitpos::B0>    FCRME;

			bits_rw_t<io_, bitpos::B8, 8> KEY;
		};
		typedef fcurame_t<0x007F'C454> FCURAME_;
		static FCURAME_ FCURAME;


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
		typedef fstatr0_t<0x007F'FFB0> FSTATR0_;
		static FSTATR0_ FSTATR0;


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
		typedef fstatr1_t<0x007F'FFB1> FSTATR1_;
		static FSTATR1_ FSTATR1;


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
		typedef frdyie_t<0x007F'C412> FRDYIE_;
		static FRDYIE_ FRDYIE;


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
		typedef fprotr_t<0x007F'FFB4> FPROTR_;
		static FPROTR_ FPROTR;


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
		typedef fresetr_t<0x007F'FFB6> FRESETR_;
		static FRESETR_ FRESETR;


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
		typedef fcmdr_t<0x007F'FFBA> FCMDR_;
		static FCMDR_ FCMDR;


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
		typedef fcpsr_t<0x007F'FFC8> FCPSR_;
		static FCPSR_ FCPSR;


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
		typedef fpestat_t<0x007F'FFCC> FPESTAT_;
		static FPESTAT_ FPESTAT;


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
		typedef pckar_t<0x007F'FFE8> PCKAR_;
		static PCKAR_ PCKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュライトイレースプロテクトレジスタ（FWEPROR）
			@param[in]	base	ベース
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fweprcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> FLWE;
		};
		typedef fweprcr_t<0x0008'C289> FWEPROR_;
		static FWEPROR_ FWEPROR;


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
		static DFLRE0_ DFLRE0;


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
		static DFLRE1_ DFLRE1;


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
		static DFLWE0_ DFLWE0;


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
		static DFLWE1_ DFLWE1;


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
		typedef fentryr_t<0x007F'FFB2> FENTRYR_;
		static FENTRYR_ FENTRYR;


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

			bit_rw_t <io_, bitpos::B0>    BCSIZE;

			bits_rw_t<io_, bitpos::B3, 8> BCADR;
		};
		typedef dflbccnt_t<0x007F'FFCA> DFLBCCNT_;
		static DFLBCCNT_ DFLBCCNT;


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
		typedef dflbcstat_t<0x007F'FFCE> DFLBCSTAT_;
		static DFLBCSTAT_ DFLBCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  FCU E2 データフラッシュコマンドレジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<DATA_FLASH_ORG> FCU_DATA_CMD8_;
		static FCU_DATA_CMD8_ FCU_DATA_CMD8;
		typedef rw16_t<DATA_FLASH_ORG> FCU_DATA_CMD16_;
		static FCU_DATA_CMD16_ FCU_DATA_CMD16;


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニーク ID レジスタ n (UIDRn) (n = 0 ～ 3) @n
					ROM 0xFFFF'FFE8 to 0xFFFF'FFF7 互換性ダミー
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<0xFFFF'FFE8> UIDR0_;
		typedef ro32_t<0xFFFF'FFEC> UIDR1_;
		typedef ro32_t<0xFFFF'FFF0> UIDR2_;
		typedef ro32_t<0xFFFF'FFF4> UIDR3_;
		static UIDR0_ UIDR0;
		static UIDR1_ UIDR1;
		static UIDR2_ UIDR2;
		static UIDR3_ UIDR3;
	};
	typedef flash_t<void> FLASH;

	template<class _> typename flash_t<_>::FMODR_ flash_t<_>::FMODR;
	template<class _> typename flash_t<_>::FASTAT_ flash_t<_>::FASTAT;
	template<class _> typename flash_t<_>::FAEINT_ flash_t<_>::FAEINT;
	template<class _> typename flash_t<_>::FCURAME_ flash_t<_>::FCURAME;
	template<class _> typename flash_t<_>::FSTATR0_ flash_t<_>::FSTATR0;
	template<class _> typename flash_t<_>::FSTATR1_ flash_t<_>::FSTATR1;
	template<class _> typename flash_t<_>::FRDYIE_ flash_t<_>::FRDYIE;
	template<class _> typename flash_t<_>::FPROTR_ flash_t<_>::FPROTR;
	template<class _> typename flash_t<_>::FRESETR_ flash_t<_>::FRESETR;
	template<class _> typename flash_t<_>::FCMDR_ flash_t<_>::FCMDR;
	template<class _> typename flash_t<_>::FCPSR_ flash_t<_>::FCPSR;
	template<class _> typename flash_t<_>::FPESTAT_ flash_t<_>::FPESTAT;
	template<class _> typename flash_t<_>::PCKAR_ flash_t<_>::PCKAR;
	template<class _> typename flash_t<_>::FWEPROR_ flash_t<_>::FWEPROR;
	template<class _> typename flash_t<_>::DFLRE0_ flash_t<_>::DFLRE0;
	template<class _> typename flash_t<_>::DFLRE1_ flash_t<_>::DFLRE1;
	template<class _> typename flash_t<_>::DFLWE0_ flash_t<_>::DFLWE0;
	template<class _> typename flash_t<_>::DFLWE1_ flash_t<_>::DFLWE1;
	template<class _> typename flash_t<_>::FENTRYR_ flash_t<_>::FENTRYR;
	template<class _> typename flash_t<_>::DFLBCCNT_ flash_t<_>::DFLBCCNT;
	template<class _> typename flash_t<_>::DFLBCSTAT_ flash_t<_>::DFLBCSTAT;
	template<class _> typename flash_t<_>::FCU_DATA_CMD8_ flash_t<_>::FCU_DATA_CMD8;
	template<class _> typename flash_t<_>::FCU_DATA_CMD16_ flash_t<_>::FCU_DATA_CMD16;
	template<class _> typename flash_t<_>::UIDR0_ flash_t<_>::UIDR0;
	template<class _> typename flash_t<_>::UIDR1_ flash_t<_>::UIDR1;
	template<class _> typename flash_t<_>::UIDR2_ flash_t<_>::UIDR2;
	template<class _> typename flash_t<_>::UIDR3_ flash_t<_>::UIDR3;
}
