#pragma once
//=========================================================================//
/*!	@file
	@brief	Memory-Protection Unit / メモリプロテクションユニット
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MPU class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mpu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域 n 開始ページ番号レジスタ（RSPAGEn）（n = 0 ～ 7）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct rspage_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 28> RSPN;
		};
		static inline rspage_t<0x0008'6400> RSPAGE0;
		static inline rspage_t<0x0008'6408> RSPAGE1;
		static inline rspage_t<0x0008'6410> RSPAGE2;
		static inline rspage_t<0x0008'6418> RSPAGE3;
		static inline rspage_t<0x0008'6420> RSPAGE4;
		static inline rspage_t<0x0008'6428> RSPAGE5;
		static inline rspage_t<0x0008'6430> RSPAGE6;
		static inline rspage_t<0x0008'6438> RSPAGE7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域 n 終了ページ番号レジスタ（REPAGEn）（n = 0 ～ 7）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct repage_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      V;
			bits_rw_t<io_, bitpos::B1, 3>   UAC;
			bits_rw_t<io_, bitpos::B4, 28>  REPN;
		};
		static inline repage_t<0x0008'6404> REPAGE0;
		static inline repage_t<0x0008'640C> REPAGE1;
		static inline repage_t<0x0008'6414> REPAGE2;
		static inline repage_t<0x0008'641C> REPAGE3;
		static inline repage_t<0x0008'6424> REPAGE4;
		static inline repage_t<0x0008'642C> REPAGE5;
		static inline repage_t<0x0008'6434> REPAGE6;
		static inline repage_t<0x0008'643C> REPAGE7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリプロテクション機能有効化レジスタ（MPEN）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpen_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MPEN;
		};
		static inline mpen_t<0x0008'6500> MPEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックグラウンドアクセス制御レジスタ（MPBAC）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpbac_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B1, 3>  UBAC;
		};
		static inline mpbac_t<0x0008'6504> MPBAC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリプロテクションエラーステータスクリアレジスタ（MPECLR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpeclr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CLR;
		};
		static inline mpeclr_t<0x0008'6508> MPECLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリプロテクションエラーステータスレジスタ（MPESTS）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpests_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_rw_t<io_, bitpos::B0>  IMPER;
			bit_rw_t<io_, bitpos::B1>  DMPER;
			bit_rw_t<io_, bitpos::B2>  DRW;
		};
		static inline mpests_t<0x0008'650C> MPESTS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データメモリプロテクションエラーアドレスレジスタ（MPDEA）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpdea_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_rw_t<io_, bitpos::B0, 32>  DEA;
		};
		static inline mpdea_t<0x0008'6514> MPEDEA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域サーチアドレスレジスタ（MPSA）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpsa_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 32>  SA;
		};
		static inline mpsa_t<0x0008'6520> MPSA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域サーチオペレーションレジスタ（MPOPS）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpops_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  S;
		};
		static inline mpops_t<0x0008'6524> MPOPS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域インバリデートオペレーションレジスタ（MPOPI）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpopi_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  INV;
		};
		static inline mpopi_t<0x0008'6526> MPOPI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  命令ヒット領域レジスタ（MHITI）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mhiti_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B1,  3>  UHACI;

			bits_rw_t<io_, bitpos::B16, 8>  HITI;
		};
		static inline mhiti_t<0x0008'6528> MHIHI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データヒット領域レジスタ（MHITD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mhitd_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B1,  3>  UHACD;

			bits_rw_t<io_, bitpos::B16, 8>  HITD;
		};
		static inline mhitd_t<0x0008'6528> MHITD;
	};
	static inline mpu_t MPU;
}
