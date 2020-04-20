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
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	DMA コントローラ（DMACa）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
	struct dmac_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型
		static const auto IVEC = ivec;			///< 割り込みベクター

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送元アドレスレジスタ (DMSAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x00> DMSAR_;
		static DMSAR_ DMSAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送先アドレスレジスタ (DMDAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x04> DMDAR_;
		static DMDAR_ DMDAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送カウントレジスタ (DMCRA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x08> DMCRA_;
		static DMCRA_ DMCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ブロック転送カウントレジスタ (DMCRB)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x0C> DMCRB_;
		static DMCRB_ DMCRB;


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
		typedef dmtmd_t<base + 0x10> DMTMD_;
		static DMTMD_ DMTMD;


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
		typedef dmint_t<base + 0x13> DMINT_;
		static DMINT_ DMINT;


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
		typedef dmamd_t<base + 0x14> DMAMD_;
		static DMAMD_ DMAMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA オフセットレジスタ (DMOFR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> DMOFR_;
		static DMOFR_ DMOFR;


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
		typedef dmcnt_t<base + 0x1C> DMCNT_;
		static DMCNT_ DMCNT;


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
		typedef dmreq_t<base + 0x1D> DMREQ_;
		static DMREQ_ DMREQ;


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
		typedef dmsts_t<base + 0x1E> DMSTS_;
		static DMSTS_ DMSTS;


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
		typedef dmcsl_t<base + 0x1F> DMCSL_;
		static DMCSL_ DMCSL;
	};

	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMSAR_ dmac_t<base, per, ivec>::DMSAR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMDAR_ dmac_t<base, per, ivec>::DMDAR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMCRA_ dmac_t<base, per, ivec>::DMCRA;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMCRB_ dmac_t<base, per, ivec>::DMCRB;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMTMD_ dmac_t<base, per, ivec>::DMTMD;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMINT_ dmac_t<base, per, ivec>::DMINT;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMAMD_ dmac_t<base, per, ivec>::DMAMD;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMOFR_ dmac_t<base, per, ivec>::DMOFR;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMCNT_ dmac_t<base, per, ivec>::DMCNT;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMREQ_ dmac_t<base, per, ivec>::DMREQ;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMSTS_ dmac_t<base, per, ivec>::DMSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
		typename dmac_t<base, per, ivec>::DMCSL_ dmac_t<base, per, ivec>::DMCSL;


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


	typedef dmac_t<0x00082000, peripheral::DMAC0, ICU::VECTOR::DMAC0I>    DMAC0;
	typedef dmac_t<0x00082040, peripheral::DMAC1, ICU::VECTOR::DMAC1I>    DMAC1;
	typedef dmac_t<0x00082080, peripheral::DMAC2, ICU::VECTOR::DMAC2I>    DMAC2;
	typedef dmac_t<0x000820C0, peripheral::DMAC3, ICU::VECTOR::DMAC3I>    DMAC3;
	typedef dmac_t<0x00082100, peripheral::DMAC4, ICU::VECTOR::DMAC74I>   DMAC4;
	typedef dmac_t<0x00082140, peripheral::DMAC5, ICU::VECTOR::DMAC74I>   DMAC5;
	typedef dmac_t<0x00082180, peripheral::DMAC6, ICU::VECTOR::DMAC74I>   DMAC6;
	typedef dmac_t<0x000821C0, peripheral::DMAC7, ICU::VECTOR::DMAC74I>   DMAC7;
}
