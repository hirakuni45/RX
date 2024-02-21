#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ　DMACAa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	DMA コントローラ（DMACAa/DMACAb）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
	struct dmac_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto IVEC = ivec;			///< 割り込みベクター

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送元アドレスレジスタ (DMSAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x00> DMSAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送先アドレスレジスタ (DMDAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x04> DMDAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送カウントレジスタ (DMCRA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmcra_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  DMCRAL;
			bits_rw_t<io_, bitpos::B16, 10>  DMCRAH;
		};
		static inline dmcra_t<base + 0x08> DMCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ブロック転送カウントレジスタ (DMCRB)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base + 0x0C> DMCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送モードレジスタ (DMTMD)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dmtmd_t<base + 0x10> DMTMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 割り込み設定レジスタ (DMINT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dmint_t<base + 0x13> DMINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA アドレスモードレジスタ (DMAMD)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dmamd_t<base + 0x14> DMAMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA オフセットレジスタ (DMOFR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x18> DMOFR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA 転送許可レジスタ (DMCNT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmcnt_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DTE;
		};
		static inline dmcnt_t<base + 0x1C> DMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ソフトウェア起動レジスタ (DMREQ)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dmreq_t<base + 0x1D> DMREQ;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMA ステータスレジスタ (DMSTS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmsts_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ESIF;

			bit_rw_t<io_, bitpos::B4>   DTIF;

			bit_ro_t<io_, bitpos::B7>   ACT;
		};
		static inline dmsts_t<base + 0x1E> DMSTS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因フラグ制御レジスタ (DMCSL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dmcsl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DISEL;
		};
		static inline dmcsl_t<base + 0x1F> DMCSL;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC モジュール起動レジスタ (DMAST)
		@param[in]	ofs	オフセット
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs>
	struct dmast_t : public rw8_t<ofs> {
		typedef rw8_t<ofs> io_;
		using io_::operator =;
		using io_::operator ();
		using io_::operator |=;
		using io_::operator &=;

		bit_rw_t<io_, bitpos::B0>   DMST;
	};
	static inline dmast_t<0x0008'2200> DMAST;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC74 割り込みステータスモニタレジスタ (DMIST)
		@param[in]	ofs	オフセット
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs>
	struct dmist_t : public ro8_t<ofs> {
		typedef ro8_t<ofs> in_;
		using in_::operator ();

		bit_ro_t<in_, bitpos::B4>   DMIS4;
		bit_ro_t<in_, bitpos::B5>   DMIS5;
		bit_ro_t<in_, bitpos::B6>   DMIS6;
		bit_ro_t<in_, bitpos::B7>   DMIS7;
	};
	static inline dmist_t<0x0008'2204> DMIST;

#if defined(SIG_RX220) || defined(SIG_RX231) || defined(SIG_RX63T) || defined(SIG_RX63T_S) || defined(SIG_RX621) || defined(SIG_RX62N) || defined(SIG_RX631) || defined(SIG_RX63N)
	typedef dmac_t<0x0008'2000, peripheral::DMAC0, ICU::VECTOR::DMACI0>   DMAC0;
	typedef dmac_t<0x0008'2040, peripheral::DMAC1, ICU::VECTOR::DMACI1>   DMAC1;
	typedef dmac_t<0x0008'2080, peripheral::DMAC2, ICU::VECTOR::DMACI2>   DMAC2;
	typedef dmac_t<0x0008'20C0, peripheral::DMAC3, ICU::VECTOR::DMACI3>   DMAC3;
#else
	typedef dmac_t<0x0008'2000, peripheral::DMAC0, ICU::VECTOR::DMAC0I>   DMAC0;
	typedef dmac_t<0x0008'2040, peripheral::DMAC1, ICU::VECTOR::DMAC1I>   DMAC1;
	typedef dmac_t<0x0008'2080, peripheral::DMAC2, ICU::VECTOR::DMAC2I>   DMAC2;
	typedef dmac_t<0x0008'20C0, peripheral::DMAC3, ICU::VECTOR::DMAC3I>   DMAC3;
	typedef dmac_t<0x0008'2100, peripheral::DMAC4, ICU::VECTOR::DMAC74I>  DMAC4;
	typedef dmac_t<0x0008'2140, peripheral::DMAC5, ICU::VECTOR::DMAC74I>  DMAC5;
	typedef dmac_t<0x0008'2180, peripheral::DMAC6, ICU::VECTOR::DMAC74I>  DMAC6;
	typedef dmac_t<0x0008'21C0, peripheral::DMAC7, ICU::VECTOR::DMAC74I>  DMAC7;
#endif
}
