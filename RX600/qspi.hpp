#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・QSPI 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	rxv		受信ベクター
		@param[in]	txv		送信ベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv>
	struct qspi_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 制御レジスタ（SPCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcr_t_ : public rw8_t<ofs> {
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
		typedef spcr_t_<base + 0x00> spcr_t;
		static spcr_t SPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI スレーブセレクト極性レジスタ（SSLP）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sslp_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SSLP;
		};
		typedef sslp_t_<base + 0x01> sslp_t;
		static sslp_t SSLP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 端子制御レジスタ（SPPCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sppcr_t_ : public rw8_t<ofs> {
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
		typedef sppcr_t_<base + 0x02> sppcr_t;
		static sppcr_t SPPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ステータスレジスタ（SPSR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spsr_t_ : public rw8_t<ofs> {
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
		typedef spsr_t_<base + 0x03> spsr_t;
		static spsr_t SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI データレジスタ（SPDR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x04> spdr_t;
		static spdr_t SPDR;
		typedef rw16_t<base + 0x04> spdr16_t;
		static spdr16_t SPDR16;
		typedef rw8_t<base + 0x04> spdr8_t;
		static spdr8_t SPDR8;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI シーケンス制御レジスタ（SPSCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spscr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> SPSC;
		};
		typedef spscr_t_<base + 0x08> spscr_t;
		static spscr_t SPSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI シーケンスステータスレジスタ（SPSSR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spssr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> SPSS;
		};
		typedef spssr_t_<base + 0x09> spssr_t;
		static spssr_t SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ビットレートレジスタ（SPBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x0A> spbr_t;
		static spbr_t SPBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI データ制御レジスタ（SPDCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdcr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  TXDMY;
		};
		typedef spdcr_t_<base + 0x0B> spdcr_t;
		static spdcr_t SPDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI クロック遅延レジスタ（SPCKD）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spckd_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SCKDL;
		};
		typedef spckd_t_<base + 0x0C> spckd_t;
		static spckd_t SPCKD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI スレーブセレクトネゲート遅延レジスタ（SSLND）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sslnd_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SLNDL;
		};
		typedef sslnd_t_<base + 0x0D> sslnd_t;
		static sslnd_t SSLND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 次アクセス遅延レジスタ（SPND）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spnd_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SPNDL;
		};
		typedef spnd_t_<base + 0x0E> spnd_t;
		static spnd_t SPND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI コマンドレジスタ n（SPCMDn）（n = 0 ～ 3）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcmd_t_ : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

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
		};
		typedef spcmd_t_<base + 0x10> spcmd0_t;
		static spcmd0_t SPCMD0;
		typedef spcmd_t_<base + 0x12> spcmd1_t;
		static spcmd1_t SPCMD1;
		typedef spcmd_t_<base + 0x14> spcmd2_t;
		static spcmd2_t SPCMD2;
		typedef spcmd_t_<base + 0x16> spcmd3_t;
		static spcmd3_t SPCMD3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_rx_vec() { return rxv; }


		//-----------------------------------------------------------------//
		/*!
			@brief  送信割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_tx_vec() { return txv; }
	};

	typedef qspi_t<0x00089E00, peripheral::QSPI, ICU::VECTOR::SPRI, ICU::VECTOR::SPTI>  QSPI;

	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spcr_t qspi_t<base, per, rxv, txv>::SPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::sslp_t qspi_t<base, per, rxv, txv>::SSLP;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::sppcr_t qspi_t<base, per, rxv, txv>::SPPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spsr_t qspi_t<base, per, rxv, txv>::SPSR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spdr_t qspi_t<base, per, rxv, txv>::SPDR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spdr16_t qspi_t<base, per, rxv, txv>::SPDR16;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spdr8_t qspi_t<base, per, rxv, txv>::SPDR8;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spscr_t qspi_t<base, per, rxv, txv>::SPSCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spssr_t qspi_t<base, per, rxv, txv>::SPSSR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spbr_t qspi_t<base, per, rxv, txv>::SPBR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spdcr_t qspi_t<base, per, rxv, txv>::SPDCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spckd_t qspi_t<base, per, rxv, txv>::SPCKD;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::sslnd_t qspi_t<base, per, rxv, txv>::SSLND;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spnd_t qspi_t<base, per, rxv, txv>::SPND;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spcmd0_t qspi_t<base, per, rxv, txv>::SPCMD0;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spcmd1_t qspi_t<base, per, rxv, txv>::SPCMD1;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spcmd2_t qspi_t<base, per, rxv, txv>::SPCMD2;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename qspi_t<base, per, rxv, txv>::spcmd3_t qspi_t<base, per, rxv, txv>::SPCMD3;
}
