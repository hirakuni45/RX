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
		static spcr_t<base + 0x00> SPCR;


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
		static sslp_t<base + 0x01> SSLP;


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
		static sppcr_t<base + 0x02> SPPCR;


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
		static spsr_t<base + 0x03> SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI データレジスタ（SPDR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw32_t<base + 0x04> SPDR;
		static rw16_t<base + 0x04> SPDR16;
		static rw8_t<base + 0x04> SPDR8;


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
		static spscr_t<base + 0x08> SPSCR;


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
		static spssr_t<base + 0x09> SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ビットレートレジスタ（SPBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<base + 0x0A> SPBR;


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
		static spdcr_t<base + 0x0B> SPDCR;


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
		static spckd_t<base + 0x0C> SPCKD;


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
		static sslnd_t<base + 0x0D> SSLND;


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
		static spnd_t<base + 0x0E> SPND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI コマンドレジスタ n（SPCMDn）（n = 0 ～ 3）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcmd_t : public rw16_t<ofs> {
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
		static spcmd_t<base + 0x10> SPCMD0;
		static spcmd_t<base + 0x12> SPCMD1;
		static spcmd_t<base + 0x14> SPCMD2;
		static spcmd_t<base + 0x16> SPCMD3;


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
}
