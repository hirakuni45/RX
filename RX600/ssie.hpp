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
		@param[in]	ssie	ステータス割り込みベクタ
		@param[in]	rxi		受信データフル割り込みベクタ
		@param[in]	txi		送信データエンプティ割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi>
	struct ssie_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御レジスタ（ SSICR ）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ssicr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     REN;
			bit_rw_t< io_, bitpos::B1>     TEN;

			bit_rw_t< io_, bitpos::B2>     MUEN;
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
			bits_rw_t<io_, bitpos::B22, 3> FRM;

			bit_rw_t< io_, bitpos::B25>    IIEN;
			bit_rw_t< io_, bitpos::B26>    ROIEN;
			bit_rw_t< io_, bitpos::B27>    RUIEN;
			bit_rw_t< io_, bitpos::B28>    TOIEN;
			bit_rw_t< io_, bitpos::B29>    TUIEN;
		};
		typedef ssicr_t_<base + 0x00> ssicr_t;
		static ssicr_t SSICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ（ SSISR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssisr_t_ : public rw32_t<ofs> {
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
		typedef ssisr_t_<base + 0x04> ssisr_t;
		static ssisr_t SSISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO 制御レジスタ（ SSIFCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssifcr_t_ : public rw32_t<ofs> {
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
		typedef ssifcr_t_<base + 0x10> ssifcr_t;
		static ssifcr_t SSIFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO ステータスレジスタ（ SSIFSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssifsr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			typedef ro32_t<ofs> ro_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     RDF;

			bits_ro_t<ro_, bitpos::B8, 4>  RDC;

			bit_rw_t< io_, bitpos::B16>    TDE;

			bits_ro_t<ro_, bitpos::B24, 4> TDC;
		};
		typedef ssifsr_t_<base + 0x14> ssifsr_t;
		static ssifsr_t SSIFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO データレジスタ（ SSIFTDR ）
		*/
		//-----------------------------------------------------------------//
		typedef wo32_t<base + 0x18> ssiftdr32_t;
		static ssiftdr32_t SSIFTDR32;
		typedef wo16_t<base + 0x18> ssiftdr16_t;
		static ssiftdr16_t SSIFTDR16;
		typedef wo8_t<base + 0x18> ssiftdr8_t;
		static ssiftdr8_t SSIFTDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO データレジスタ（ SSIFRDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x1C> ssifrdr32_t;
		static ssifrdr32_t SSIFRDR32;
		typedef ro16_t<base + 0x1C> ssifrdr16_t;
		static ssifrdr16_t SSIFRDR16;
		typedef ro8_t<base + 0x1C> ssifrdr8_t;
		static ssifrdr8_t SSIFRDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  オーディオフォーマットレジスタ (SSIOFR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssiofr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   OMOD;

			bit_rw_t <io_, bitpos::B8>      LRCONT;
			bit_rw_t <io_, bitpos::B9>      BCKASTP;
		};
		typedef ssiofr_t_<base + 0x20> ssiofr_t;
		static ssiofr_t SSIOFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO ステータスコントロールレジスタ (SSISCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssiscr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>   RDFS;

			bits_rw_t<io_, bitpos::B8, 5>   TDES;
		};
		typedef ssiscr_t_<base + 0x24> ssiscr_t;
		static ssiscr_t SSISCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータス割り込みベクターの取得
			@return ステータス割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BL1 get_ssie_vec() { return ssie; }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信データフル割り込みベクタを取得
			@return 受信データフル割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_rxi_vec() { return rxi; }


		//-----------------------------------------------------------------//
		/*!
			@brief  送信データエンプティ割り込みベクタを取得
			@return 送信データエンプティ割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_txi_vec() { return txi; }
	};

#if defined(SIG_RX72M)
	typedef ssie_t<0x0008A500, peripheral::SSIE0, ICU::VECTOR_BL1::SSIF0, ICU::VECTOR::SSIRXI0, ICU::VECTOR::SSITXI0> SSI0;
	typedef ssie_t<0x0008A540, peripheral::SSIE1, ICU::VECTOR_BL1::SSIF1, ICU::VECTOR::SSIRTI1, ICU::VECTOR::SSIRTI1> SSI1;
#endif

	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssicr_t ssie_t<base, per, ssie, rxi, txi>::SSICR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssisr_t ssie_t<base, per, ssie, rxi, txi>::SSISR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssifcr_t ssie_t<base, per, ssie, rxi, txi>::SSIFCR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssifsr_t ssie_t<base, per, ssie, rxi, txi>::SSIFSR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssiftdr32_t ssie_t<base, per, ssie, rxi, txi>::SSIFTDR32;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssiftdr16_t ssie_t<base, per, ssie, rxi, txi>::SSIFTDR16;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssiftdr8_t ssie_t<base, per, ssie, rxi, txi>::SSIFTDR8;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssifrdr32_t ssie_t<base, per, ssie, rxi, txi>::SSIFRDR32;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssifrdr16_t ssie_t<base, per, ssie, rxi, txi>::SSIFRDR16;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssifrdr8_t ssie_t<base, per, ssie, rxi, txi>::SSIFRDR8;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssiofr_t ssie_t<base, per, ssie, rxi, txi>::SSIOFR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssie, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssie_t<base, per, ssie, rxi, txi>::ssiscr_t ssie_t<base, per, ssie, rxi, txi>::SSISCR;
}
