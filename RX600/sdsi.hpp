#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・SDSI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
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
	template <uint32_t base, peripheral per, ICU::GROUPBL2 sdioi>
	struct sdsi_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
//		static constexpr auto CDET_VEC = cdeti;	///< カード検出割り込み・ベクタ
//		static constexpr auto CAC_VEC  = caci;	///< カードアクセス割り込み・ベクタ
//		static constexpr auto SDAC_VEC = sdaci;	///< SDIO アクセス割り込み・ベクタ
//		static constexpr auto SBFA_VEC = sdfai;	///< バッファアクセス割り込み・ベクタ


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FN1 アクセス制御レジスタ (FN1ACCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fn1accr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B11>  FN1ACC;
		};
		static inline fn1accr_t<base + 0x00> FN1ACCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みイネーブル制御レジスタ 1 (INTENCR1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct intencr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMD52WIREN;
			bit_rw_t<io_, bitpos::B1>  CMD53WIREN;
			bit_rw_t<io_, bitpos::B2>  CMD53RIREN;
		};
		static inline intencr1_t<base + 0x04> INTENCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みステータスレジスタ 1 (INTSR1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct intsr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMD52W;
			bit_rw_t<io_, bitpos::B1>  CMD53W;
			bit_rw_t<io_, bitpos::B2>  CMD53R;
		};
		static inline intsr1_t<base + 0x05> INTSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SD コマンド制御レジスタ (SDCMDCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sdcmdcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline sdcmdcr_t<base + 0x06> SDCMDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SD コマンドアクセスアドレス 0 レジスタ (SDCADD0R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sdcadd0r_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		static inline sdcadd0r_t<base + 0x07> SDCADD0R;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SD コマンドアクセスアドレス 1 レジスタ (SDCADD1R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sdcadd1r_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		static inline sdcadd1r_t<base + 0x08> SDCADD1R;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SD コマンドアクセスアドレス 2 レジスタ (SDCADD2R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sdcadd2r_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		static inline sdcadd2r_t<base + 0x09> SDCADD2R;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDSI 制御レジスタ 1 (SDSICR1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sdsicr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  IOE1IOR1;
			bit_ro_t<io_, bitpos::B1>  EPS;
			bit_ro_t<io_, bitpos::B2>  EMPC;
		};
		static inline sdsicr1_t<base + 0x0A> SDSICR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 制御レジスタ 1 (DMACR1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmacr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DMAEN;
			bit_rw_t<io_, bitpos::B1>  DMALOCKEN;
		};
		static inline dmacr1_t<base + 0x0B> DMACR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ブロックカウンタ (BLKCNT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct blkcnt_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>  CMD53BLK;
		};
		static inline blkcnt_t<base + 0x0C> BLKCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バイトカウンタ (BYTCNT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bytcnt_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12>  CMD53BYT;
		};
		static inline bytcnt_t<base + 0x0E> BYTCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送アドレスレジスタ (DMATRADDR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmatraddr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 32>  DMAADD;
		};
		static inline dmatraddr_t<base + 0x10> DMATRADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDSI 制御レジスタ 2 (SDSICR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sdsicr2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      RSWAP;

			bit_rw_t <io_, bitpos::B2>      WSWAP;

			bit_rw_t <io_, bitpos::B4>      REG5EN;
		};
		static inline sdsicr2_t<base + 0x100> SDSICR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDSI 制御レジスタ 3 (SDSICR3)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sdsicr3_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      SRST;

			bit_rw_t <io_, bitpos::B2>      IOR0;
			bit_rw_t <io_, bitpos::B3>      CEN;

			bit_rw_t <io_, bitpos::B18>     SPS;
			bit_rw_t <io_, bitpos::B19>     SMPC;
		};
		static inline sdsicr3_t<base + 0x104> SDSICR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みイネーブル制御レジスタ 2 (INTENCR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct intencr2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CDFEN;
			bit_rw_t <io_, bitpos::B1>      CDREN;
			bit_rw_t <io_, bitpos::B2>      DTEEN;
		};
		static inline intencr2_t<base + 0x108> INTENCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みステータスレジスタ 2 (INTSR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct intsr2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CDF;
			bit_rw_t <io_, bitpos::B1>      CDR;
			bit_rw_t <io_, bitpos::B2>      DTE;
		};
		static inline intsr2_t<base + 0x10C> INTSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 制御レジスタ 2 (DMACR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmacr2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   DMARSWAP;
			bits_rw_t<io_, bitpos::B2, 2>   DMAWSWAP;

			bit_rw_t <io_, bitpos::B8>      DMASDSEL;
		};
		static inline dmacr2_t<base + 0x110> DMACR2;






// under constructions...
	};

	typedef sdsi_t<0x0009'5000, peripheral::SDSI, ICU::GROUPBL2::SDIOI> SDSI;
}
