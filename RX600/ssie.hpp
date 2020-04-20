#pragma once
//=====================================================================//
/*!	@file
	@brief	RX700 グループ・SSIE 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シリアルサウンドインタフェース（SSIE）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信データエンプティ割り込みベクタ
		@param[in]	rxi		受信データフル割り込みベクタ
		@param[in]	ssie	ステータス割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
	struct ssie_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
		static const auto TX_VEC = txi;		///< 送信データエンプティ割り込みベクタ
		static const auto RX_VEC = rxi;		///< 受信データフル割り込みベクタ
		static const auto SS_VEC = ssie;	///< ステータス割り込みベクタ


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御レジスタ（ SSICR ）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ssicr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     REN;
			bit_rw_t< io_, bitpos::B1>     TEN;

			bit_rw_t< io_, bitpos::B3>     MUEN;
			bits_rw_t<io_, bitpos::B4, 4>  CKDV;
			bit_rw_t< io_, bitpos::B8>     DEL;
			bit_rw_t< io_, bitpos::B9>     PDTA;
			bit_rw_t< io_, bitpos::B10>    SDTA;
			bit_rw_t< io_, bitpos::B11>    SPDP;
			bit_rw_t< io_, bitpos::B12>    LRCKP;
			bit_rw_t< io_, bitpos::B13>    BCKP;
			bit_rw_t< io_, bitpos::B14>    MST;

			bits_rw_t<io_, bitpos::B16, 3> SWL;
			bits_rw_t<io_, bitpos::B19, 3> DWL;
			bits_rw_t<io_, bitpos::B22, 2> FRM;

			bit_rw_t< io_, bitpos::B25>    IIEN;
			bit_rw_t< io_, bitpos::B26>    ROIEN;
			bit_rw_t< io_, bitpos::B27>    RUIEN;
			bit_rw_t< io_, bitpos::B28>    TOIEN;
			bit_rw_t< io_, bitpos::B29>    TUIEN;
		};
		typedef ssicr_t<base + 0x00> SSICR_;
		static SSICR_ SSICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ（ SSISR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssisr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> rw_;
			typedef ro32_t<ofs> ro_;
			using rw_::operator =;
			using rw_::operator ();
			using rw_::operator |=;
			using rw_::operator &=;

			bit_ro_t< ro_, bitpos::B25>    IIRQ;
			bit_rw_t< rw_, bitpos::B26>    ROIRQ;
			bit_rw_t< rw_, bitpos::B27>    RUIRQ;
			bit_rw_t< rw_, bitpos::B28>    TOIRQ;
			bit_rw_t< rw_, bitpos::B29>    TUIRQ;
		};
		typedef ssisr_t<base + 0x04> SSISR_;
		static SSISR_ SSISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO 制御レジスタ（ SSIFCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssifcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     RFRST;
			bit_rw_t< io_, bitpos::B1>     TFRST;
			bit_rw_t< io_, bitpos::B2>     RIE;
			bit_rw_t< io_, bitpos::B3>     TIE;

			bit_rw_t< io_, bitpos::B11>    BSW;

			bit_rw_t< io_, bitpos::B16>    SSIRST;

			bit_rw_t< io_, bitpos::B31>    AUCKE;
		};
		typedef ssifcr_t<base + 0x10> SSIFCR_;
		static SSIFCR_ SSIFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO ステータスレジスタ（ SSIFSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssifsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     RDF;

			bits_rw_t<io_, bitpos::B8, 6>  RDC;

			bit_rw_t< io_, bitpos::B16>    TDE;

			bits_rw_t<io_, bitpos::B24, 6> TDC;
		};
		typedef ssifsr_t<base + 0x14> SSIFSR_;
		static SSIFSR_ SSIFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO データレジスタ（ SSIFTDR ）
		*/
		//-----------------------------------------------------------------//
		typedef wo32_t<base + 0x18> SSIFTDR32_;
		static SSIFTDR32_ SSIFTDR32;
		typedef wo16_t<base + 0x18> SSIFTDR16_;
		static SSIFTDR16_ SSIFTDR16;
		typedef wo8_t<base + 0x18> SSIFTDR8_;
		static SSIFTDR8_ SSIFTDR8;

		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO データレジスタ（ SSIFRDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x1C> SSIFRDR32_;
		static SSIFRDR32_ SSIFRDR32;
		typedef ro16_t<base + 0x1C> SSIFRDR16_;
		static SSIFRDR16_ SSIFRDR16;
		typedef ro8_t<base + 0x1C> SSIFRDR8_;
		static SSIFRDR8_ SSIFRDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  オーディオフォーマットレジスタ (SSIOFR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssiofr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   OMOD;

			bit_rw_t <io_, bitpos::B8>      LRCONT;
			bit_rw_t <io_, bitpos::B9>      BCKASTP;
		};
		typedef ssiofr_t<base + 0x20> SSIOFR_;
		static SSIOFR_ SSIOFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO ステータスコントロールレジスタ (SSISCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssiscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>   RDFS;

			bits_rw_t<io_, bitpos::B8, 5>   TDES;
		};
		typedef ssiscr_t<base + 0x24> SSISCR_;
		static SSISCR_ SSISCR;
	};

	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSICR_ ssie_t<base, per, txi, rxi, ssie>::SSICR;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSISR_ ssie_t<base, per, txi, rxi, ssie>::SSISR;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFCR_ ssie_t<base, per, txi, rxi, ssie>::SSIFCR;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFSR_ ssie_t<base, per, txi, rxi, ssie>::SSIFSR;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFTDR32_ ssie_t<base, per, txi, rxi, ssie>::SSIFTDR32;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFTDR16_ ssie_t<base, per, txi, rxi, ssie>::SSIFTDR16;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFTDR8_ ssie_t<base, per, txi, rxi, ssie>::SSIFTDR8;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFRDR32_ ssie_t<base, per, txi, rxi, ssie>::SSIFRDR32;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFRDR16_ ssie_t<base, per, txi, rxi, ssie>::SSIFRDR16;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIFRDR8_ ssie_t<base, per, txi, rxi, ssie>::SSIFRDR8;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSIOFR_ ssie_t<base, per, txi, rxi, ssie>::SSIOFR;
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR_BL1 ssie>
		typename ssie_t<base, per, txi, rxi, ssie>::SSISCR_ ssie_t<base, per, txi, rxi, ssie>::SSISCR;


#if defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef ssie_t<0x0008A500, peripheral::SSIE0,
		ICU::VECTOR::SSITXI0, ICU::VECTOR::SSIRXI0, ICU::VECTOR_BL1::SSIF0> SSIE0;
	typedef ssie_t<0x0008A540, peripheral::SSIE1,
		ICU::VECTOR::SSIRTI1, ICU::VECTOR::SSIRTI1, ICU::VECTOR_BL1::SSIF1> SSIE1;
#endif
}
