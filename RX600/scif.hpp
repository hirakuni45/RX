#pragma once
//=========================================================================//
/*!	@file
	@brief	Serial Communications Interface with FIFO / FIFO 内蔵シリアルコミュニケーションインタフェース @n
			RX64M/RX71M
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
		@brief  SCIF base class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct scif_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブ FIFO データレジスタ (FRDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x0A> FRDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミット FIFO データレジスタ (FTDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x06> FTDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct smr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline smr_t<base + 0x00> SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline scr_t<base + 0x04> SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (FSR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline fsr_t<base + 0x08> FSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x02> BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ (MDDR) @n
					※BRRと同一アドレス
					※SEMR.MDDRS = 1 の場合に有効
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x02> MDDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO コントロールレジスタ (FCR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline fcr_t<base + 0x0C> FCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO データ数レジスタ (FDR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fdr_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 5>  R;
			bits_ro_t<io_, bitpos::B8, 5>  T;
		};
		static inline fdr_t<base + 0x0E> FDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルポートレジスタ (SPTR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sptr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline sptr_t<base + 0x10> SPTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ラインステータスレジスタ (LSR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct lsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ORER;
			bits_rw_t<io_, bitpos::B2, 4>  FER;
			bits_rw_t<io_, bitpos::B8, 4>  PER;
		};
		static inline lsr_t<base + 0x12> LSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO トリガコントロールレジスタ (FTCR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ftcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  5>  TFTC;
			bit_rw_t <io_, bitpos::B7>      TTRGS;
			bits_rw_t<io_, bitpos::B8,  5>  RFTC;
			bit_rw_t <io_, bitpos::B15>     RTRGS;
		};
		static inline ftcr_t<base + 0x16> FTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	シリアル拡張モードレジスタ (SEMR)
			@param[in]	ofs		アドレス・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct semr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline semr_t<base + 0x14> SEMR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIF 定義基底クラス (SCIF)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込み
		@param[in]	rxi		受信割り込み
		@param[in]	tei		送信終了割り込み
		@param[in]	eri		エラー割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPAL0 tei, ICU::GROUPAL0 eri>
	struct scif_t : public scif_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKA;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME  = true;	///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM  = true;	///< SEMR.BGDM が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN  = true;	///< SEMR.NFEN が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = true;	///< SEMR.ABCSE が利用可能な場合「true」
	};

	typedef scif_t<0x000D'0000, peripheral::SCIF8,  ICU::VECTOR::TXIF8, ICU::VECTOR::RXIF8,
		ICU::GROUPAL0::TEIF8, ICU::GROUPAL0::ERIF8>  SCIF8;
	typedef scif_t<0x000D'0020, peripheral::SCIF9,  ICU::VECTOR::TXIF9, ICU::VECTOR::RXIF9,
		ICU::GROUPAL0::TEIF9, ICU::GROUPAL0::ERIF9>  SCIF9;
	typedef scif_t<0x000D'0040, peripheral::SCIF10, ICU::VECTOR::TXIF10, ICU::VECTOR::RXIF10,
		ICU::GROUPAL0::TEIF10, ICU::GROUPAL0::ERIF10>  SCIF10;
	typedef scif_t<0x000D'0060, peripheral::SCIF11, ICU::VECTOR::TXIF11, ICU::VECTOR::RXIF11,
		ICU::GROUPAL0::TEIF11, ICU::GROUPAL0::ERIF11>  SCIF11;
}
