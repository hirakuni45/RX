#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ MPU 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  メモリプロテクションユニットクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mpu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域 n 開始ページ番号レジスタ（RSPAGEn）（n = 0 ～ 7）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct rspage_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 28> RSPN;
		};
		static rspage_t<0x00086400> RSPAGE0;
		static rspage_t<0x00086408> RSPAGE1;
		static rspage_t<0x00086410> RSPAGE2;
		static rspage_t<0x00086418> RSPAGE3;
		static rspage_t<0x00086420> RSPAGE4;
		static rspage_t<0x00086428> RSPAGE5;
		static rspage_t<0x00086430> RSPAGE6;
		static rspage_t<0x00086438> RSPAGE7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域 n 終了ページ番号レジスタ（REPAGEn）（n = 0 ～ 7）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static repage_t<0x00086404> REPAGE0;
		static repage_t<0x0008640C> REPAGE1;
		static repage_t<0x00086414> REPAGE2;
		static repage_t<0x0008641C> REPAGE3;
		static repage_t<0x00086424> REPAGE4;
		static repage_t<0x0008642C> REPAGE5;
		static repage_t<0x00086434> REPAGE6;
		static repage_t<0x0008643C> REPAGE7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリプロテクション機能有効化レジスタ（MPEN）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpen_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MPEN;
		};
		static mpen_t<0x00086500> MPEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックグラウンドアクセス制御レジスタ（MPBAC）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpbac_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B1, 3>  UBAC;
		};
		static mpbac_t<0x00086504> MPBAC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリプロテクションエラーステータスクリアレジスタ（MPECLR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpeclr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CLR;
		};
		static mpeclr_t<0x00086508> MPECLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリプロテクションエラーステータスレジスタ（MPESTS）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpests_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_rw_t<io_, bitpos::B0>  IMPER;
			bit_rw_t<io_, bitpos::B1>  DMPER;
			bit_rw_t<io_, bitpos::B2>  DRW;
		};
		static mpests_t<0x0008650C> MPESTS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データメモリプロテクションエラーアドレスレジスタ（MPDEA）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpdea_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_rw_t<io_, bitpos::B0, 32>  DEA;
		};
		static mpdea_t<0x00086514> MPEDEA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域サーチアドレスレジスタ（MPSA）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpsa_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 32>  SA;
		};
		static mpsa_t<0x00086520> MPSA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域サーチオペレーションレジスタ（MPOPS）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpops_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  S;
		};
		static mpops_t<0x00086524> MPOPS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  領域インバリデートオペレーションレジスタ（MPOPI）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mpopi_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  INV;
		};
		static mpopi_t<0x00086526> MPOPI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  命令ヒット領域レジスタ（MHITI）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static mhiti_t<0x00086528> MHIHI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データヒット領域レジスタ（MHITD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static mhitd_t<0x00086528> MHITD;
	};
	typedef mpu_t MPU;
}
