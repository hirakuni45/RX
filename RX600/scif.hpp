#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SCIF(SCIFA) 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIF 定義基底クラス (SCIF)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信ベクター
		@param[in]	rxv		受信ベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv>
	struct scif_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
		static const auto TX_VEC = txv;		///< 受信割り込みベクター
		static const auto RX_VEC = rxv;		///< 送信割り込みベクター

		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブ FIFO データレジスタ (FRDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x0A> FRDR_;
		static  FRDR_ FRDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミット FIFO データレジスタ (FTDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x06> FTDR_;
		static  FTDR_ FTDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
		*/
		//-----------------------------------------------------------------//
		struct smr_t : public rw16_t<base + 0x00> {
			typedef rw16_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B3>	  STOP;
			bit_rw_t <io_, bitpos::B4>	  PM;
			bit_rw_t <io_, bitpos::B5>	  PE;
			bit_rw_t <io_, bitpos::B6>	  CHR;
			bit_rw_t <io_, bitpos::B7>	  CM;
		};
		typedef smr_t SMR_;
		static  SMR_ SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
		*/
		//-----------------------------------------------------------------//
		struct scr_t : public rw16_t<base + 0x04> {
			typedef rw16_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKE;
			bit_rw_t <io_, bitpos::B2>	  TEIE;
			bit_rw_t <io_, bitpos::B3>	  REIE;
			bit_rw_t <io_, bitpos::B4>	  RE;
			bit_rw_t <io_, bitpos::B5>	  TE;
			bit_rw_t <io_, bitpos::B6>	  RIE;
			bit_rw_t <io_, bitpos::B7>	  TIE;
		};
		typedef scr_t SCR_;
		static  SCR_ SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (FSR)
		*/
		//-----------------------------------------------------------------//
		struct fsr_t : public rw16_t<base + 0x08> {
			typedef rw16_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DR;
			bit_rw_t<io_, bitpos::B1> RDF;
			bit_rw_t<io_, bitpos::B2> PER;
			bit_rw_t<io_, bitpos::B3> FER;
			bit_rw_t<io_, bitpos::B4> BRK;
			bit_rw_t<io_, bitpos::B5> TDFE;
			bit_rw_t<io_, bitpos::B6> TEND;
			bit_rw_t<io_, bitpos::B7> ER;
		};
		typedef fsr_t FSR_;
		static  FSR_ FSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x02> BRR_;
		static  BRR_ BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ (MDDR) @n
					※BRRと同一アドレス
					※SEMR.MDDRS = 1 の場合に有効
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x02> MDDR_;
		static  MDDR_ MDDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO コントロールレジスタ (FCR)
		*/
		//-----------------------------------------------------------------//
		struct fcr_t : public rw16_t<base + 0x0C> {
			typedef rw16_t<base + 0x0C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     LOOP;
			bit_rw_t <io_, bitpos::B1>     RFRST;
			bit_rw_t <io_, bitpos::B2>     TFRST;
			bit_rw_t <io_, bitpos::B3>     MCE;
			bits_rw_t<io_, bitpos::B4, 2>  TTRG;
			bits_rw_t<io_, bitpos::B6, 2>  RTRG;
			bits_rw_t<io_, bitpos::B8, 3>  RSTRG;
		};
		typedef fcr_t FCR_;
		static  FCR_ FCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO データ数レジスタ (FDR)
		*/
		//-----------------------------------------------------------------//
		struct fdr_t : public ro16_t<base + 0x0E> {
			typedef ro16_t<base + 0x0E> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 5>  R;
			bits_ro_t<io_, bitpos::B8, 5>  T;
		};
		typedef fdr_t FDR_;
		static  FDR_ FDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルポートレジスタ (SPTR)
		*/
		//-----------------------------------------------------------------//
		struct sptr_t : public rw16_t<base + 0x10> {
			typedef rw16_t<base + 0x10> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SPB2DT;
			bit_rw_t<io_, bitpos::B1>  SPB2IO;
			bit_rw_t<io_, bitpos::B2>  SCKDT;
			bit_rw_t<io_, bitpos::B3>  SCKIO;
			bit_rw_t<io_, bitpos::B4>  CTS2DT;
			bit_rw_t<io_, bitpos::B5>  CTS2IO;
			bit_rw_t<io_, bitpos::B6>  RTS2DT;
			bit_rw_t<io_, bitpos::B7>  RTS2IO;
		};
		typedef sptr_t SPTR_;
		static  SPTR_ SPTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ラインステータスレジスタ (LSR)
		*/
		//-----------------------------------------------------------------//
		struct lsr_t : public rw16_t<base + 0x12> {
			typedef rw16_t<base + 0x12> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ORER;
			bits_rw_t<io_, bitpos::B2, 4>  FER;
			bits_rw_t<io_, bitpos::B8, 4>  PER;
		};
		typedef lsr_t LSR_;
		static  LSR_ LSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO トリガコントロールレジスタ (FTCR)
		*/
		//-----------------------------------------------------------------//
		struct ftcr_t : public rw16_t<base + 0x16> {
			typedef rw16_t<base + 0x16> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  5>  TFTC;
			bit_rw_t <io_, bitpos::B7>      TTRGS;
			bits_rw_t<io_, bitpos::B8,  5>  RFTC;
			bit_rw_t <io_, bitpos::B15>     RTRGS;
		};
		typedef ftcr_t FTCR_;
		static  FTCR_ FTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	シリアル拡張モードレジスタ (SEMR)
		*/
		//-----------------------------------------------------------------//
		struct semr_t : public rw16_t<base + 0x14> {
			typedef rw16_t<base + 0x14> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ABCS0;
			bit_rw_t <io_, bitpos::B2>  NFEN;
			bit_rw_t <io_, bitpos::B3>  DIR;
			bit_rw_t <io_, bitpos::B4>  MDDRS;
			bit_rw_t <io_, bitpos::B5>  BRME;
			bit_rw_t <io_, bitpos::B7>  BGDM;
		};
		typedef semr_t SEMR_;
		static  SEMR_ SEMR;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::FRDR_ scif_t<base, per, txv, rxv>::FRDR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::FTDR_ scif_t<base, per, txv, rxv>::FTDR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::SMR_ scif_t<base, per, txv, rxv>::SMR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::SCR_ scif_t<base, per, txv, rxv>::SCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::FSR_ scif_t<base, per, txv, rxv>::FSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::BRR_ scif_t<base, per, txv, rxv>::BRR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::MDDR_ scif_t<base, per, txv, rxv>::MDDR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::FCR_ scif_t<base, per, txv, rxv>::FCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::FDR_ scif_t<base, per, txv, rxv>::FDR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::SPTR_ scif_t<base, per, txv, rxv>::SPTR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::LSR_ scif_t<base, per, txv, rxv>::LSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::FTCR_ scif_t<base, per, txv, rxv>::FTCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv> typename scif_t<base, per, txv, rxv>::SEMR_ scif_t<base, per, txv, rxv>::SEMR;


#if defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef scif_t<0x000D0000, peripheral::SCIF8,  ICU::VECTOR::TXIF8,  ICU::VECTOR::RXIF8>  SCIF8;
	typedef scif_t<0x000D0020, peripheral::SCIF9,  ICU::VECTOR::TXIF9,  ICU::VECTOR::RXIF9>  SCIF9;
	typedef scif_t<0x000D0040, peripheral::SCIF10, ICU::VECTOR::TXIF10, ICU::VECTOR::RXIF10> SCIF10;
	typedef scif_t<0x000D0060, peripheral::SCIF11, ICU::VECTOR::TXIF11, ICU::VECTOR::RXIF11> SCIF11;
#endif
}
