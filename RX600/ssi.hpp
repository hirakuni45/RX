#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SSI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シリアルサウンドインタフェース（SSI）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ssif	ステータス割り込み
		@param[in]	rxi		受信データフル割り込みベクタ
		@param[in]	txi		送信データエンプティ割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi>
	struct ssi_t {

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
			bit_rw_t< io_, bitpos::B12>    SWSP;
			bit_rw_t< io_, bitpos::B13>    SCKP;
			bit_rw_t< io_, bitpos::B14>    SWSD;
			bit_rw_t< io_, bitpos::B15>    SCKD;
			bits_rw_t<io_, bitpos::B16, 3> SWL;
			bits_rw_t<io_, bitpos::B19, 3> DWL;
			bits_rw_t<io_, bitpos::B22, 3> CHNL;

			bit_rw_t< io_, bitpos::B25>    IIEN;
			bit_rw_t< io_, bitpos::B26>    ROIEN;
			bit_rw_t< io_, bitpos::B27>    RUIEN;
			bit_rw_t< io_, bitpos::B28>    TOIEN;
			bit_rw_t< io_, bitpos::B29>    TUIEN;
			bit_rw_t< io_, bitpos::B30>    CKS;
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

			bit_ro_t< ro_, bitpos::B0>     IDST;
			bit_ro_t< ro_, bitpos::B1>     RSWNO;
			bits_ro_t<ro_, bitpos::B2, 2>  RCHNO;
			bit_ro_t< ro_, bitpos::B4>     TSWNO;
			bits_ro_t<ro_, bitpos::B5, 2>  TCHNO;

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
			bits_rw_t<io_, bitpos::B4, 2>  RTRG;
			bits_rw_t<io_, bitpos::B6, 2>  TTRG;

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
		typedef rw32_t<base + 0x18> ssiftdr_t;
		static ssiftdr_t SSIFTDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO データレジスタ（ SSIFRDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x1C> ssifrdr_t;
		static ssifrdr_t SSIFRDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  TDM モードレジスタ（ SSITDMR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssitdmr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B8>     CONT;
		};
		typedef ssitdmr_t_<base + 0x20> ssitdmr_t;
		static ssitdmr_t SSITDMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


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

#if defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef ssi_t<0x0008A500, peripheral::SSI0,
		ICU::VECTOR_BL1::SSIF0, ICU::VECTOR::SSIRXI0, ICU::VECTOR::SSITXI0> SSI0;
	typedef ssi_t<0x0008A540, peripheral::SSI1,
		ICU::VECTOR_BL1::SSIF0, ICU::VECTOR::SSIRTI1, ICU::VECTOR::SSIRTI1> SSI1;
#endif

	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssi_t<base, per, ssif, rxi, txi>::ssicr_t ssi_t<base, per, ssif, rxi, txi>::SSICR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssi_t<base, per, ssif, rxi, txi>::ssisr_t ssi_t<base, per, ssif, rxi, txi>::SSISR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssi_t<base, per, ssif, rxi, txi>::ssifcr_t ssi_t<base, per, ssif, rxi, txi>::SSIFCR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssi_t<base, per, ssif, rxi, txi>::ssifsr_t ssi_t<base, per, ssif, rxi, txi>::SSIFSR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssi_t<base, per, ssif, rxi, txi>::ssiftdr_t ssi_t<base, per, ssif, rxi, txi>::SSIFTDR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssi_t<base, per, ssif, rxi, txi>::ssifrdr_t ssi_t<base, per, ssif, rxi, txi>::SSIFRDR;
	template<uint32_t base, peripheral per, ICU::VECTOR_BL1 ssif, ICU::VECTOR rxi, ICU::VECTOR txi> typename ssi_t<base, per, ssif, rxi, txi>::ssitdmr_t ssi_t<base, per, ssif, rxi, txi>::SSITDMR;
}
