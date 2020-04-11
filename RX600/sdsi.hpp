#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SDSI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDSI 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	cdeti	カード検出割り込み・ベクタ
		@param[in]	caci	カードアクセス割り込み・ベクタ
		@param[in]	sdaci	SDIO アクセス割り込み・ベクタ
		@param[in]	sbfai	バッファアクセス割り込み・ベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi>
	struct sdsi_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
//		static const auto CDET_VEC = cdeti;	///< カード検出割り込み・ベクタ
//		static const auto CAC_VEC  = caci;	///< カードアクセス割り込み・ベクタ
//		static const auto SDAC_VEC = sdaci;	///< SDIO アクセス割り込み・ベクタ
//		static const auto SBFA_VEC = sdfai;	///< バッファアクセス割り込み・ベクタ


		//-----------------------------------------------------------------//
		/*!
			@brief  FN1 アクセス制御レジスタ (FN1ACCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fn1accr_t : public rw32_t<base + ofs> {
			typedef rw32_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B11>  FN1ACC;
		};
		static fn1accr_t<0x0000> FN1ACCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みイネーブル制御レジスタ 1 (INTENCR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intencr1_t : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMD52WIREN;
			bit_rw_t<io_, bitpos::B1>  CMD53WIREN;
			bit_rw_t<io_, bitpos::B2>  CMD53RIREN;
		};
		static intencr1_t<0x0004> INTENCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みステータスレジスタ 1 (INTSR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intsr1_t : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMD52W;
			bit_rw_t<io_, bitpos::B1>  CMD53W;
			bit_rw_t<io_, bitpos::B2>  CMD53R;
		};
		static intsr1_t<0x0005> INTSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンド制御レジスタ (SDCMDCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcmdcr_t : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SDCMDIDX;
			bit_rw_t<io_, bitpos::B1>  SDWNRFLG;
			bit_rw_t<io_, bitpos::B2>  SDRAWFLG;
			bit_rw_t<io_, bitpos::B3>  SDBMODE;
			bit_rw_t<io_, bitpos::B4>  SDOPCODE;
		};
		static sdcmdcr_t<0x0006> SDCMDCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンドアクセスアドレス 0 レジスタ (SDCADD0R)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcadd0r_t : public ro8_t<base + ofs> {
			typedef ro8_t<base + ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		static sdcadd0r_t<0x0007> SDCADD0R;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンドアクセスアドレス 1 レジスタ (SDCADD1R)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcadd1r_t : public ro8_t<base + ofs> {
			typedef ro8_t<base + ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		static sdcadd1r_t<0x0008> SDCADD1R;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンドアクセスアドレス 2 レジスタ (SDCADD2R)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcadd2r_t : public ro8_t<base + ofs> {
			typedef ro8_t<base + ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		static sdcadd2r_t<0x0009> SDCADD2R;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDSI 制御レジスタ 1 (SDSICR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdsicr1_t : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  IOE1IOR1;
			bit_ro_t<io_, bitpos::B1>  EPS;
			bit_ro_t<io_, bitpos::B2>  EMPC;
		};
		static sdsicr1_t<0x000A> SDSICR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  DMA 制御レジスタ 1 (DMACR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dmacr1_t : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DMAEN;
			bit_rw_t<io_, bitpos::B1>  DMALOCKEN;
		};
		static dmacr1_t<0x000B> DMACR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロックカウンタ (BLKCNT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct blkcnt_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>  CMD53BLK;
		};
		static blkcnt_t<0x000C> BLKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイトカウンタ (BYTCNT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct bytcnt_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12>  CMD53BYT;
		};
		static bytcnt_t<0x000E> BYTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  DMA 転送アドレスレジスタ (DMATRADDR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dmatraddr_t : public rw32_t<base + ofs> {
			typedef rw32_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 32>  DMAADD;
		};
		static dmatraddr_t<0x0010> DMATRADDR;



// under constructions...




	};

	typedef sdsi_t<0x00095000, peripheral::SDSI, ICU::VECTOR_BL2::SDIOI> SDSI;
}
