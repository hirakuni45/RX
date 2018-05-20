#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　DMACa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX600/peripheral.hpp"
#include "RX600/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	DMA コントローラ（DMACa）
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct dmac_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送元アドレスレジスタ (DMSAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw32_t<base + 0x00> DMSAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送先アドレスレジスタ (DMDAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw32_t<base + 0x04> DMDAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送カウントレジスタ (DMCRA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw32_t<base + 0x08> DMCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ブロック転送カウントレジスタ (DMCRB)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw16_t<base + 0x0C> DMCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送モードレジスタ (DMTMD)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmtmd_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>   DCTG;
			bits_rw_t<io_, bitpos::B8,  2>   SZ;
			bits_rw_t<io_, bitpos::B12, 2>   DTS;
			bits_rw_t<io_, bitpos::B14, 2>   MD;
		};
		static dmtmd_t<base + 0x10> DMTMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 割り込み設定レジスタ (DMINT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmint_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DARIE;
			bit_rw_t<io_, bitpos::B1>   SARIE;
			bit_rw_t<io_, bitpos::B2>   RPTIE;
			bit_rw_t<io_, bitpos::B3>   ESIE;
			bit_rw_t<io_, bitpos::B4>   DTIE;
		};
		static dmint_t<base + 0x13> DMINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA アドレスモードレジスタ (DMAMD)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmamd_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  5>   DARA;
			bits_rw_t<io_, bitpos::B6,  2>   DM;
			bits_rw_t<io_, bitpos::B8,  5>   SARA;
			bits_rw_t<io_, bitpos::B14, 2>   SM;
		};
		static dmamd_t<base + 0x14> DMAMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA オフセットレジスタ (DMOFR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw32_t<base + 0x18> DMOFR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送許可レジスタ (DMCNT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmcnt_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DTE;
		};
		static dmcnt_t<base + 0x1C> DMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ソフトウェア起動レジスタ (DMREQ)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmreq_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   SWREQ;
			bit_rw_t<io_, bitpos::B4>   CLRS;
		};
		static dmreq_t<base + 0x1D> DMREQ;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ステータスレジスタ (DMSTS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmsts_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ESIF;
			bit_rw_t<io_, bitpos::B4>   DTIF;
			bit_rw_t<io_, bitpos::B7>   ACT;
		};
		static dmsts_t<base + 0x1E> DMSTS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因フラグ制御レジスタ (DMCSL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmcsl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DISEL;
		};
		static dmcsl_t<base + 0x1F> DMCSL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC モジュール起動レジスタ (DMAST)
		@param[in]	ofs	オフセット
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs>
	struct dmast_t : public rw8_t<ofs> {
		typedef rw8_t<ofs> io_;
		using io_::operator =;
		using io_::operator ();
		using io_::operator |=;
		using io_::operator &=;

		bit_rw_t<io_, bitpos::B0>   DMST;
	};
	static dmast_t<0x00082200> DMAST;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC74 割り込みステータスモニタレジスタ (DMIST)
		@param[in]	ofs	オフセット
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs>
	struct dmist_t : public ro8_t<ofs> {
		typedef ro8_t<ofs> in_;
		using in_::operator ();

		bit_ro_t<in_, bitpos::B4>   DMIS4;
		bit_ro_t<in_, bitpos::B5>   DMIS5;
		bit_ro_t<in_, bitpos::B6>   DMIS6;
		bit_ro_t<in_, bitpos::B7>   DMIS7;
	};
	static dmist_t<0x00082204> DMIST;


	typedef dmac_t<0x00820000, peripheral::DMAC0>    DMAC0;
	typedef dmac_t<0x00820040, peripheral::DMAC1>    DMAC1;
	typedef dmac_t<0x00820080, peripheral::DMAC2>    DMAC2;
	typedef dmac_t<0x008200C0, peripheral::DMAC3>    DMAC3;
	typedef dmac_t<0x00820100, peripheral::DMAC4>    DMAC4;
	typedef dmac_t<0x00820140, peripheral::DMAC5>    DMAC5;
	typedef dmac_t<0x00820180, peripheral::DMAC6>    DMAC6;
	typedef dmac_t<0x008201C0, peripheral::DMAC7>    DMAC7;
}
