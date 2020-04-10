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
		@param[in]	t		ペリフェラル型
		@param[in]	vec		割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t, ICU::VECTOR vec>
	struct dmac_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送元アドレスレジスタ (DMSAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x00> dmsar_t;
		static dmsar_t DMSAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送先アドレスレジスタ (DMDAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x04> dmdar_t;
		static dmdar_t DMDAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送カウントレジスタ (DMCRA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x08> dmcra_t;
		static dmcra_t DMCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ブロック転送カウントレジスタ (DMCRB)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x0C> dmcrb_t;
		static dmcrb_t DMCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送モードレジスタ (DMTMD)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmtmd_t_ : public rw16_t<ofs> {
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
		typedef dmtmd_t_<base + 0x10> dmtmd_t;
		static dmtmd_t DMTMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 割り込み設定レジスタ (DMINT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmint_t_ : public rw8_t<ofs> {
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
		typedef dmint_t_<base + 0x13> dmint_t;
		static dmint_t DMINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA アドレスモードレジスタ (DMAMD)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmamd_t_ : public rw16_t<ofs> {
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
		typedef dmamd_t_<base + 0x14> dmamd_t;
		static dmamd_t DMAMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA オフセットレジスタ (DMOFR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> dmofr_t;
		static dmofr_t DMOFR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送許可レジスタ (DMCNT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmcnt_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DTE;
		};
		typedef dmcnt_t_<base + 0x1C> dmcnt_t;
		static dmcnt_t DMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ソフトウェア起動レジスタ (DMREQ)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmreq_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   SWREQ;
			bit_rw_t<io_, bitpos::B4>   CLRS;
		};
		typedef dmreq_t_<base + 0x1D> dmreq_t;
		static dmreq_t DMREQ;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ステータスレジスタ (DMSTS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmsts_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ESIF;
			bit_rw_t<io_, bitpos::B4>   DTIF;
			bit_rw_t<io_, bitpos::B7>   ACT;
		};
		typedef dmsts_t_<base + 0x1E> dmsts_t;
		static dmsts_t DMSTS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因フラグ制御レジスタ (DMCSL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmcsl_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DISEL;
		};
		typedef dmcsl_t_<base + 0x1F> dmcsl_t;
		static dmcsl_t DMCSL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec() { return vec; }
	};

	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmsar_t dmac_t<base, t, vec>::DMSAR;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmdar_t dmac_t<base, t, vec>::DMDAR;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmcra_t dmac_t<base, t, vec>::DMCRA;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmcrb_t dmac_t<base, t, vec>::DMCRB;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmtmd_t dmac_t<base, t, vec>::DMTMD;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmint_t dmac_t<base, t, vec>::DMINT;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmamd_t dmac_t<base, t, vec>::DMAMD;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmofr_t dmac_t<base, t, vec>::DMOFR;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmcnt_t dmac_t<base, t, vec>::DMCNT;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmreq_t dmac_t<base, t, vec>::DMREQ;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmsts_t dmac_t<base, t, vec>::DMSTS;
	template <uint32_t base, peripheral t, ICU::VECTOR vec> typename dmac_t<base, t, vec>::dmcsl_t dmac_t<base, t, vec>::DMCSL;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC モジュール起動レジスタ (DMAST)
		@param[in]	ofs	オフセット
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs>
	struct dmast_t_ : public rw8_t<ofs> {
		typedef rw8_t<ofs> io_;
		using io_::operator =;
		using io_::operator ();
		using io_::operator |=;
		using io_::operator &=;

		bit_rw_t<io_, bitpos::B0>   DMST;
	};
	typedef dmast_t_<0x00082200> dmast_t;
	static dmast_t DMAST;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC74 割り込みステータスモニタレジスタ (DMIST)
		@param[in]	ofs	オフセット
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs>
	struct dmist_t_ : public ro8_t<ofs> {
		typedef ro8_t<ofs> in_;
		using in_::operator ();

		bit_ro_t<in_, bitpos::B4>   DMIS4;
		bit_ro_t<in_, bitpos::B5>   DMIS5;
		bit_ro_t<in_, bitpos::B6>   DMIS6;
		bit_ro_t<in_, bitpos::B7>   DMIS7;
	};
	typedef dmist_t_<0x00082204> dmist_t;
	static dmist_t DMIST;


	typedef dmac_t<0x00082000, peripheral::DMAC0, ICU::VECTOR::DMAC0I>    DMAC0;
	typedef dmac_t<0x00082040, peripheral::DMAC1, ICU::VECTOR::DMAC1I>    DMAC1;
	typedef dmac_t<0x00082080, peripheral::DMAC2, ICU::VECTOR::DMAC2I>    DMAC2;
	typedef dmac_t<0x000820C0, peripheral::DMAC3, ICU::VECTOR::DMAC3I>    DMAC3;
	typedef dmac_t<0x00082100, peripheral::DMAC4, ICU::VECTOR::DMAC74I>   DMAC4;
	typedef dmac_t<0x00082140, peripheral::DMAC5, ICU::VECTOR::DMAC74I>   DMAC5;
	typedef dmac_t<0x00082180, peripheral::DMAC6, ICU::VECTOR::DMAC74I>   DMAC6;
	typedef dmac_t<0x000821C0, peripheral::DMAC7, ICU::VECTOR::DMAC74I>   DMAC7;
}
