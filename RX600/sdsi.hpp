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

		//-----------------------------------------------------------------//
		/*!
			@brief  FN1 アクセス制御レジスタ (FN1ACCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fn1accr_t_ : public rw32_t<base + ofs> {
			typedef rw32_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B11>  FN1ACC;
		};
		typedef fn1accr_t_<0x0000> fn1accr_t;
		static fn1accr_t FN1ACCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みイネーブル制御レジスタ 1 (INTENCR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intencr1_t_ : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMD52WIREN;
			bit_rw_t<io_, bitpos::B1>  CMD53WIREN;
			bit_rw_t<io_, bitpos::B2>  CMD53RIREN;
		};
		typedef intencr1_t_<0x0004> intencr1_t;
		static intencr1_t INTENCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みステータスレジスタ 1 (INTSR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intsr1_t_ : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMD52W;
			bit_rw_t<io_, bitpos::B1>  CMD53W;
			bit_rw_t<io_, bitpos::B2>  CMD53R;
		};
		typedef intsr1_t_<0x0005> intsr1_t;
		static intsr1_t INTSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンド制御レジスタ (SDCMDCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcmdcr_t_ : public rw8_t<base + ofs> {
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
		typedef sdcmdcr_t_<0x0006> sdcmdcr_t;
		static sdcmdcr_t SDCMDCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンドアクセスアドレス 0 レジスタ (SDCADD0R)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcadd0r_t_ : public ro8_t<base + ofs> {
			typedef ro8_t<base + ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		typedef sdcadd0r_t_<0x0007> sdcadd0r_t;
		static sdcadd0r_t SDCADD0R;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンドアクセスアドレス 1 レジスタ (SDCADD1R)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcadd1r_t_ : public ro8_t<base + ofs> {
			typedef ro8_t<base + ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		typedef sdcadd1r_t_<0x0008> sdcadd1r_t;
		static sdcadd1r_t SDCADD1R;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD コマンドアクセスアドレス 2 レジスタ (SDCADD2R)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcadd2r_t_ : public ro8_t<base + ofs> {
			typedef ro8_t<base + ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  SDCMDACCADD;
		};
		typedef sdcadd2r_t_<0x0009> sdcadd2r_t;
		static sdcadd2r_t SDCADD2R;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDSI 制御レジスタ 1 (SDSICR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdsicr1_t_ : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  IOE1IOR1;
			bit_ro_t<io_, bitpos::B1>  EPS;
			bit_ro_t<io_, bitpos::B2>  EMPC;
		};
		typedef sdsicr1_t_<0x000A> sdsicr1_t;
		static sdsicr1_t SDSICR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  DMA 制御レジスタ 1 (DMACR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dmacr1_t_ : public rw8_t<base + ofs> {
			typedef rw8_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DMAEN;
			bit_rw_t<io_, bitpos::B1>  DMALOCKEN;
		};
		typedef dmacr1_t_<0x000B> dmacr1_t;
		static dmacr1_t DMACR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロックカウンタ (BLKCNT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct blkcnt_t_ : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>  CMD53BLK;
		};
		typedef blkcnt_t_<0x000C> blkcnt_t;
		static blkcnt_t BLKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイトカウンタ (BYTCNT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct bytcnt_t_ : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12>  CMD53BYT;
		};
		typedef bytcnt_t_<0x000E> bytcnt_t;
		static bytcnt_t BYTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  DMA 転送アドレスレジスタ (DMATRADDR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dmatraddr_t_ : public rw32_t<base + ofs> {
			typedef rw32_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 32>  DMAADD;
		};
		typedef dmatraddr_t_<0x0010> dmatraddr_t;
		static dmatraddr_t DMATRADDR;



// under constructions...



		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  SDSI 割り込み・ベクタ
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static auto get_sdioi() { return sdioi; }
	};

	typedef sdsi_t<0x00095000, peripheral::SDSI, ICU::VECTOR_BL2::SDIOI> SDSI;

	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::fn1accr_t sdsi_t<base, per, sdioi>::FN1ACCR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::intencr1_t sdsi_t<base, per, sdioi>::INTENCR1;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::intsr1_t sdsi_t<base, per, sdioi>::INTSR1;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::sdcmdcr_t sdsi_t<base, per, sdioi>::SDCMDCR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::sdcadd0r_t sdsi_t<base, per, sdioi>::SDCADD0R;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::sdcadd1r_t sdsi_t<base, per, sdioi>::SDCADD1R;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::sdcadd2r_t sdsi_t<base, per, sdioi>::SDCADD2R;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::sdsicr1_t sdsi_t<base, per, sdioi>::SDSICR1;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::dmacr1_t sdsi_t<base, per, sdioi>::DMACR1;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::blkcnt_t sdsi_t<base, per, sdioi>::BLKCNT;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::bytcnt_t sdsi_t<base, per, sdioi>::BYTCNT;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL2 sdioi> typename sdsi_t<base, per, sdioi>::dmatraddr_t sdsi_t<base, per, sdioi>::DMATRADDR;
}
