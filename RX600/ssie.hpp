#pragma once
//=========================================================================//
/*!	@file
	@brief	RX700 グループ・SSIE 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
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
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPBL1 ssie>
	struct ssie_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TX_VEC = txi;		///< 送信データエンプティ割り込みベクタ
		static constexpr auto RX_VEC = rxi;		///< 受信データフル割り込みベクタ
		static constexpr auto SS_VEC = ssie;	///< ステータス割り込みベクタ


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
		static inline ssicr_t<base + 0x00> SSICR;


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
		static inline ssisr_t<base + 0x04> SSISR;


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
		static inline ssifcr_t<base + 0x10> SSIFCR;


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
		static inline ssifsr_t<base + 0x14> SSIFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO データレジスタ（ SSIFTDR ）
		*/
		//-----------------------------------------------------------------//
		static inline wo32_t<base + 0x18> SSIFTDR32;
		static inline wo16_t<base + 0x18> SSIFTDR16;
		static inline wo8_t<base + 0x18> SSIFTDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO データレジスタ（ SSIFRDR ）
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<base + 0x1C> SSIFRDR32;
		static inline ro16_t<base + 0x1C> SSIFRDR16;
		static inline ro8_t<base + 0x1C> SSIFRDR8;


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
		static inline ssiofr_t<base + 0x20> SSIOFR;


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
		static inline ssiscr_t<base + 0x24> SSISCR;
	};


#if defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef ssie_t<0x0008'A500, peripheral::SSIE0,
		ICU::VECTOR::SSITXI0, ICU::VECTOR::SSIRXI0, ICU::GROUPBL1::SSIF0> SSIE0;
	typedef ssie_t<0x0008'A540, peripheral::SSIE1,
		ICU::VECTOR::SSIRTI1, ICU::VECTOR::SSIRTI1, ICU::GROUPBL1::SSIF1> SSIE1;
#endif
}
