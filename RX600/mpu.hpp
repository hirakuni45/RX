#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ メモリプロテクションユニット（MPU）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
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
	template <class _>
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
		typedef rspage_t<0x0008'6400> RSPAGE0_;
		static  RSPAGE0_ RSPAGE0;
		typedef rspage_t<0x0008'6408> RSPAGE1_;
		static  RSPAGE1_ RSPAGE1;
		typedef rspage_t<0x0008'6410> RSPAGE2_;
		static  RSPAGE2_ RSPAGE2;
		typedef rspage_t<0x0008'6418> RSPAGE3_;
		static  RSPAGE3_ RSPAGE3;
		typedef rspage_t<0x0008'6420> RSPAGE4_;
		static  RSPAGE4_ RSPAGE4;
		typedef rspage_t<0x0008'6428> RSPAGE5_;
		static  RSPAGE5_ RSPAGE5;
		typedef rspage_t<0x0008'6430> RSPAGE6_;
		static  RSPAGE6_ RSPAGE6;
		typedef rspage_t<0x0008'6438> RSPAGE7_;
		static  RSPAGE7_ RSPAGE7;


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
		typedef repage_t<0x0008'6404> REPAGE0_;
		static  REPAGE0_ REPAGE0;
		typedef repage_t<0x0008'640C> REPAGE1_;
		static  REPAGE1_ REPAGE1;
		typedef repage_t<0x0008'6414> REPAGE2_;
		static  REPAGE2_ REPAGE2;
		typedef repage_t<0x0008'641C> REPAGE3_;
		static  REPAGE3_ REPAGE3;
		typedef repage_t<0x0008'6424> REPAGE4_;
		static  REPAGE4_ REPAGE4;
		typedef repage_t<0x0008'642C> REPAGE5_;
		static  REPAGE5_ REPAGE5;
		typedef repage_t<0x0008'6434> REPAGE6_;
		static  REPAGE6_ REPAGE6;
		typedef repage_t<0x0008'643C> REPAGE7_;
		static  REPAGE7_ REPAGE7;


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
		typedef mpen_t<0x0008'6500> MPEN_;
		static  MPEN_ MPEN;


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
		typedef mpbac_t<0x0008'6504> MPBAC_;
		static  MPBAC_ MPBAC;


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
		typedef mpeclr_t<0x0008'6508> MPECLR_;
		static  MPECLR_ MPECLR;


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
		typedef mpests_t<0x0008'650C> MPESTS_;
		static  MPESTS_ MPESTS;


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
		typedef mpdea_t<0x0008'6514> MPEDEA_;
		static  MPEDEA_ MPEDEA;


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
		typedef mpsa_t<0x0008'6520> MPSA_;
		static  MPSA_ MPSA;


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
		typedef mpops_t<0x0008'6524> MPOPS_;
		static  MPOPS_ MPOPS;


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
		typedef mpopi_t<0x0008'6526> MPOPI_;
		static  MPOPI_ MPOPI;


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
		typedef mhiti_t<0x0008'6528> MHIHI_;
		static  MHIHI_ MHIHI;


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
		typedef mhitd_t<0x0008'6528> MHITD_;
		static  MHITD_ MHITD;
	};
	template <class _> typename mpu_t<_>::RSPAGE0_ mpu_t<_>::RSPAGE0;
	template <class _> typename mpu_t<_>::RSPAGE1_ mpu_t<_>::RSPAGE1;
	template <class _> typename mpu_t<_>::RSPAGE2_ mpu_t<_>::RSPAGE2;
	template <class _> typename mpu_t<_>::RSPAGE3_ mpu_t<_>::RSPAGE3;
	template <class _> typename mpu_t<_>::RSPAGE4_ mpu_t<_>::RSPAGE4;
	template <class _> typename mpu_t<_>::RSPAGE5_ mpu_t<_>::RSPAGE5;
	template <class _> typename mpu_t<_>::RSPAGE6_ mpu_t<_>::RSPAGE6;
	template <class _> typename mpu_t<_>::RSPAGE7_ mpu_t<_>::RSPAGE7;
	template <class _> typename mpu_t<_>::REPAGE0_ mpu_t<_>::REPAGE0;
	template <class _> typename mpu_t<_>::REPAGE1_ mpu_t<_>::REPAGE1;
	template <class _> typename mpu_t<_>::REPAGE2_ mpu_t<_>::REPAGE2;
	template <class _> typename mpu_t<_>::REPAGE3_ mpu_t<_>::REPAGE3;
	template <class _> typename mpu_t<_>::REPAGE4_ mpu_t<_>::REPAGE4;
	template <class _> typename mpu_t<_>::REPAGE5_ mpu_t<_>::REPAGE5;
	template <class _> typename mpu_t<_>::REPAGE6_ mpu_t<_>::REPAGE6;
	template <class _> typename mpu_t<_>::REPAGE7_ mpu_t<_>::REPAGE7;
	template <class _> typename mpu_t<_>::MPEN_ mpu_t<_>::MPEN;
	template <class _> typename mpu_t<_>::MPBAC_ mpu_t<_>::MPBAC;
	template <class _> typename mpu_t<_>::MPECLR_ mpu_t<_>::MPECLR;
	template <class _> typename mpu_t<_>::MPESTS_ mpu_t<_>::MPESTS;
	template <class _> typename mpu_t<_>::MPEDEA_ mpu_t<_>::MPEDEA;
	template <class _> typename mpu_t<_>::MPSA_ mpu_t<_>::MPSA;
	template <class _> typename mpu_t<_>::MPOPS_ mpu_t<_>::MPOPS;
	template <class _> typename mpu_t<_>::MPOPI_ mpu_t<_>::MPOPI;
	template <class _> typename mpu_t<_>::MHIHI_ mpu_t<_>::MHIHI;
	template <class _> typename mpu_t<_>::MHITD_ mpu_t<_>::MHITD;

	typedef mpu_t<void> MPU;
}
