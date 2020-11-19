#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・QSPI 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信バッファ・エンプティ割り込みベクター
		@param[in]	rxv		受信バッファ・フル割り込みベクター
		@param[in]	sslv	QSSL ネゲート割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv,
		ICU::VECTOR_BL0 sslv>
	struct qspi_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型
		static const auto TX_VEC = txv;			///< 受信割り込みベクター
		static const auto RX_VEC = rxv;			///< 送信割り込みベクター
		static const auto SSL_VEC = sslv;		///< 送信終了割り込みベクター
		static const uint32_t PCLK = F_PCLKB;	///< PCLK 周波数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 制御レジスタ（SPCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1> SPSSLIE;

			bit_rw_t<io_, bitpos::B3> MSTR;

			bit_rw_t<io_, bitpos::B5> SPTIE;
			bit_rw_t<io_, bitpos::B6> SPE;
			bit_rw_t<io_, bitpos::B7> SPRIE;
		};
		typedef spcr_t<base + 0x00> SPCR_;
		static  SPCR_ SPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI スレーブセレクト極性レジスタ（SSLP）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sslp_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SSLP;
		};
		typedef sslp_t<base + 0x01> SSLP_;
		static  SSLP_ SSLP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 端子制御レジスタ（SPPCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sppcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	SPLP;
			bit_rw_t<io_, bitpos::B1>	IO2FV;
			bit_rw_t<io_, bitpos::B2>	IO3FV;

			bit_rw_t<io_, bitpos::B4>	MOIFV;
			bit_rw_t<io_, bitpos::B5>	MOIFE;
		};
		typedef sppcr_t<base + 0x02> SPPCR_;
		static  SPPCR_ SPPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ステータスレジスタ（SPSR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4> SPSSLF;
			bit_rw_t<io_, bitpos::B5> SPTEF;
			bit_rw_t<io_, bitpos::B6> TREND;
			bit_rw_t<io_, bitpos::B7> SPRFF;
		};
		typedef spsr_t<base + 0x03> SPSR_;
		static  SPSR_ SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI データレジスタ（SPDR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x04> SPDR32_;
		static  SPDR32_ SPDR32;
		typedef rw16_t<base + 0x04> SPDR16_;
		static  SPDR16_ SPDR16;
		typedef rw8_t<base + 0x04> SPDR8_;
		static  SPDR8_ SPDR8;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI シーケンス制御レジスタ（SPSCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> SPSC;
		};
		typedef spscr_t<base + 0x08> SPSCR_;
		static  SPSCR_ SPSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI シーケンスステータスレジスタ（SPSSR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spssr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> SPSS;
		};
		typedef spssr_t<base + 0x09> SPSSR_;
		static  SPSSR_ SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ビットレートレジスタ（SPBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x0A> SPBR_;
		static  SPBR_ SPBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI データ制御レジスタ（SPDCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  TXDMY;
		};
		typedef spdcr_t<base + 0x0B> SPDCR_;
		static  SPDCR_ SPDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI クロック遅延レジスタ（SPCKD）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spckd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SCKDL;
		};
		typedef spckd_t<base + 0x0C> SPCKD_;
		static  SPCKD_ SPCKD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI スレーブセレクトネゲート遅延レジスタ（SSLND）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sslnd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SLNDL;
		};
		typedef sslnd_t<base + 0x0D> SSLND_;
		static  SSLND_ SSLND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 次アクセス遅延レジスタ（SPND）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spnd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SPNDL;
		};
		typedef spnd_t<base + 0x0E> SPND_;
		static  SPND_ SPND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI コマンドレジスタ n（SPCMD[n]）（n = 0 ～ 3）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcmd_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 4) { io_::index = j * 2; } }

			bit_rw_t <io_, bitpos::B0>    CPHA;
			bit_rw_t <io_, bitpos::B1>    CPOL;
			bits_rw_t<io_, bitpos::B2, 2> BRDV;
			bit_rw_t <io_, bitpos::B4>    SPRW;
			bits_rw_t<io_, bitpos::B5, 2> SPIMOD;
			bit_rw_t <io_, bitpos::B7>    SSLKP;
			bits_rw_t<io_, bitpos::B8, 4> SPB;
			bit_rw_t <io_, bitpos::B12>   LSBF;
			bit_rw_t <io_, bitpos::B13>   SPNDEN;
			bit_rw_t <io_, bitpos::B14>   SLNDEN;
			bit_rw_t <io_, bitpos::B15>   SCKDEN;

			spcmd_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef spcmd_t<base + 0x10> SPCMD_;
		static  SPCMD_ SPCMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI バッファ制御レジスタ (SPBFCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spbfcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> RXTRG;
			bit_rw_t <io_, bitpos::B3>    TXTRGEX;
			bits_rw_t<io_, bitpos::B4, 2> TXTRG;
			bit_rw_t <io_, bitpos::B6>    RXRST;
			bit_rw_t <io_, bitpos::B7>    TXRST;
		};
		typedef spbfcr_t<base + 0x18> SPBFCR_;
		static  SPBFCR_ SPBFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI バッファデータカウントセットレジスタ (SPBDCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spbdcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6> RXBC;

			bits_rw_t<io_, bitpos::B8, 6> TXBC;
		};
		typedef spbdcr_t<base + 0x1A> SPBDCR_;
		static  SPBDCR_ SPBDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 転送データ長倍数設定レジスタ n (SPBMULn) (n = 0 ～ 3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x1C> SPBMUL0_;
		static  SPBMUL0_ SPBMUL0;
		typedef rw32_t<base + 0x20> SPBMUL1_;
		static  SPBMUL1_ SPBMUL1;
		typedef rw32_t<base + 0x24> SPBMUL2_;
		static  SPBMUL2_ SPBMUL2;
		typedef rw32_t<base + 0x28> SPBMUL3_;
		static  SPBMUL3_ SPBMUL3;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPCR_ qspi_t<base, per, txv, rxv, sslv>::SPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SSLP_ qspi_t<base, per, txv, rxv, sslv>::SSLP;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPPCR_ qspi_t<base, per, txv, rxv, sslv>::SPPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPSR_ qspi_t<base, per, txv, rxv, sslv>::SPSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPDR32_ qspi_t<base, per, txv, rxv, sslv>::SPDR32;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPDR16_ qspi_t<base, per, txv, rxv, sslv>::SPDR16;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPDR8_ qspi_t<base, per, txv, rxv, sslv>::SPDR8;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPSCR_ qspi_t<base, per, txv, rxv, sslv>::SPSCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPSSR_ qspi_t<base, per, txv, rxv, sslv>::SPSSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPBR_ qspi_t<base, per, txv, rxv, sslv>::SPBR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPDCR_ qspi_t<base, per, txv, rxv, sslv>::SPDCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPCKD_ qspi_t<base, per, txv, rxv, sslv>::SPCKD;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SSLND_ qspi_t<base, per, txv, rxv, sslv>::SSLND;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPND_ qspi_t<base, per, txv, rxv, sslv>::SPND;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv
> typename qspi_t<base, per, txv, rxv, sslv>::SPCMD_ qspi_t<base, per, txv, rxv, sslv>::SPCMD;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPBFCR_ qspi_t<base, per, txv, rxv, sslv>::SPBFCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPBDCR_ qspi_t<base, per, txv, rxv, sslv>::SPBDCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPBMUL0_ qspi_t<base, per, txv, rxv, sslv>::SPBMUL0;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPBMUL1_ qspi_t<base, per, txv, rxv, sslv>::SPBMUL1;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPBMUL2_ qspi_t<base, per, txv, rxv, sslv>::SPBMUL2;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR_BL0 sslv> typename qspi_t<base, per, txv, rxv, sslv>::SPBMUL3_ qspi_t<base, per, txv, rxv, sslv>::SPBMUL3;


	typedef qspi_t<0x00089E00, peripheral::QSPI, ICU::VECTOR::SPTI, ICU::VECTOR::SPRI,
		ICU::VECTOR_BL0::QSPSSLI>  QSPI;
}
