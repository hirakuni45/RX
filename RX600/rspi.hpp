#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・RSPI[abc] 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信割り込みベクター
		@param[in]	rxv		受信割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
	struct rspi_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
		static const auto TX_VEC = txv;		///< 受信割り込みベクター
		static const auto RX_VEC = rxv;		///< 送信割り込みベクター
		static const uint32_t PCLK = pclk;	///< PCLK 周波数


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 制御レジスタ（SPCR）
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

			bit_rw_t<io_, bitpos::B0> SPMS;
			bit_rw_t<io_, bitpos::B1> TXMD;
			bit_rw_t<io_, bitpos::B2> MODFEN;
			bit_rw_t<io_, bitpos::B3> MSTR;
			bit_rw_t<io_, bitpos::B4> SPEIE;
			bit_rw_t<io_, bitpos::B5> SPTIE;
			bit_rw_t<io_, bitpos::B6> SPE;
			bit_rw_t<io_, bitpos::B7> SPRIE;
		};
		typedef spcr_t<base + 0x00> SPCR_;
		static SPCR_ SPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI スレーブセレクト極性レジスタ（SSLP）
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

			bit_rw_t<io_, bitpos::B0> SSLP0;
			bit_rw_t<io_, bitpos::B1> SSLP1;
			bit_rw_t<io_, bitpos::B2> SSLP2;
			bit_rw_t<io_, bitpos::B3> SSLP3;
		};
		typedef sslp_t<base + 0x01> SSLP_;
		static SSLP_ SSLP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 端子制御レジスタ（SPPCR）
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
			bit_rw_t<io_, bitpos::B1>	SPLP2;
			bit_rw_t<io_, bitpos::B4>	MOIFV;
			bit_rw_t<io_, bitpos::B5>	MOIFE;
		};
		typedef sppcr_t<base + 0x02> SPPCR_;
		static SPPCR_ SPPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ステータスレジスタ（SPSR）
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

			bit_rw_t<io_, bitpos::B0> OVRF;
			bit_rw_t<io_, bitpos::B1> IDLNF;
			bit_rw_t<io_, bitpos::B2> MODF;
			bit_rw_t<io_, bitpos::B3> PERF;
			bit_rw_t<io_, bitpos::B5> SPTEF;
			bit_rw_t<io_, bitpos::B7> SPRF;
		};
		typedef spsr_t<base + 0x03> SPSR_;
		static SPSR_ SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データレジスタ（SPDR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			rw16_t<ofs> H;
		};
		typedef spdr_t<base + 0x04> SPDR_;
		static SPDR_ SPDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI シーケンス制御レジスタ（SPSCR）
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

			bits_rw_t<io_, bitpos::B0, 3> SPSLN;
		};
		typedef spscr_t<base + 0x08> SPSCR_;
		static SPSCR_ SPSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI シーケンスステータスレジスタ（SPSSR）
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

			bits_rw_t<io_, bitpos::B0, 3> SPCP;
			bits_rw_t<io_, bitpos::B4, 3> SPECM;
		};
		typedef spssr_t<base + 0x09> SPSSR_;
		static SPSSR_ SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ビットレートレジスタ（SPBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x0A> SPBR_;
		static SPBR_ SPBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データコントロールレジスタ（SPDCR）
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

			bits_rw_t<io_, bitpos::B0, 2> SPFC;
			bit_rw_t <io_, bitpos::B4>    SPRDTD;
			bit_rw_t <io_, bitpos::B5>    SPLW;
		};
		typedef spdcr_t<base + 0x0B> SPDCR_;
		static SPDCR_ SPDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI クロック遅延レジスタ（SPCKD）
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
		static SPCKD_ SPCKD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI スレーブセレクトネゲート遅延レジスタ（SSLND）
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
		static SSLND_ SSLND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 次アクセス遅延レジスタ（SPND）
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
		static SPND_ SPND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 制御レジスタ 2（SPCR2）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SPPE;
			bit_rw_t<io_, bitpos::B1> SPOE;
			bit_rw_t<io_, bitpos::B2> SPIIE;
			bit_rw_t<io_, bitpos::B3> PTE;
			bit_rw_t<io_, bitpos::B4> SCKASE;
		};
		typedef spcr2_t<base + 0x0F> SPCR2_;
		static SPCR2_ SPCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI コマンドレジスタ 0 ～ 7（SPCMD0 ～ SPCMD7）
			@param[in]	ofs	オフセット
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
			bits_rw_t<io_, bitpos::B4, 3> SSLA;
			bit_rw_t <io_, bitpos::B7>    SSLKP;
			bits_rw_t<io_, bitpos::B8, 4> SPB;
			bit_rw_t <io_, bitpos::B12>   LSBF;
			bit_rw_t <io_, bitpos::B13>   SPNDEN;
			bit_rw_t <io_, bitpos::B14>   SLNDEN;
			bit_rw_t <io_, bitpos::B15>   SCKDEN;
		};
		typedef spcmd_t<base + 0x10> SPCMD0_;
		typedef spcmd_t<base + 0x12> SPCMD1_;
		typedef spcmd_t<base + 0x14> SPCMD2_;
		typedef spcmd_t<base + 0x16> SPCMD3_;
		typedef spcmd_t<base + 0x18> SPCMD4_;
		typedef spcmd_t<base + 0x1A> SPCMD5_;
		typedef spcmd_t<base + 0x1C> SPCMD6_;
		typedef spcmd_t<base + 0x1E> SPCMD7_;
		static SPCMD0_ SPCMD0;
		static SPCMD1_ SPCMD1;
		static SPCMD2_ SPCMD2;
		static SPCMD3_ SPCMD3;
		static SPCMD4_ SPCMD4;
		static SPCMD5_ SPCMD5;
		static SPCMD6_ SPCMD6;
		static SPCMD7_ SPCMD7;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャンネルを返す
			@return チャネル
		*/
		//-----------------------------------------------------------------//
		int get_chanel() const {
			return (base >> 5) & 3;
		}
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCR_ rspi_t<base, per, txv, rxv, pclk>::SPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SSLP_ rspi_t<base, per, txv, rxv, pclk>::SSLP;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPPCR_ rspi_t<base, per, txv, rxv, pclk>::SPPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPSR_ rspi_t<base, per, txv, rxv, pclk>::SPSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPDR_ rspi_t<base, per, txv, rxv, pclk>::SPDR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPSCR_ rspi_t<base, per, txv, rxv, pclk>::SPSCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPSSR_ rspi_t<base, per, txv, rxv, pclk>::SPSSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPBR_ rspi_t<base, per, txv, rxv, pclk>::SPBR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPDCR_ rspi_t<base, per, txv, rxv, pclk>::SPDCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCKD_ rspi_t<base, per, txv, rxv, pclk>::SPCKD;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SSLND_ rspi_t<base, per, txv, rxv, pclk>::SSLND;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPND_ rspi_t<base, per, txv, rxv, pclk>::SPND;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCR2_ rspi_t<base, per, txv, rxv, pclk>::SPCR2;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD0_ rspi_t<base, per, txv, rxv, pclk>::SPCMD0;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD1_ rspi_t<base, per, txv, rxv, pclk>::SPCMD1;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD2_ rspi_t<base, per, txv, rxv, pclk>::SPCMD2;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD3_ rspi_t<base, per, txv, rxv, pclk>::SPCMD3;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD4_ rspi_t<base, per, txv, rxv, pclk>::SPCMD4;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD5_ rspi_t<base, per, txv, rxv, pclk>::SPCMD5;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD6_ rspi_t<base, per, txv, rxv, pclk>::SPCMD6;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
		typename rspi_t<base, per, txv, rxv, pclk>::SPCMD7_ rspi_t<base, per, txv, rxv, pclk>::SPCMD7;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス (c)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxv		受信割り込みベクター
		@param[in]	txv		送信割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, uint32_t pclk>
	struct rspi_c_t : public rspi_t<base, per, txv, rxv, pclk> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データコントロールレジスタ 2 (SPDCR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdcr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BYSW;
		};
		static spdcr2_t<base + 0x20> SPDCR2;
	};


#if defined(SIG_RX24T)
	typedef rspi_t<0x00088380, peripheral::RSPI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0,
		F_PCLKB>  RSPI0;
#elif defined(SIG_RX64M)
	typedef rspi_t<0x000D0100, peripheral::RSPI,  ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0,
		F_PCLKA>  RSPI;
#elif defined(SIG_RX71M)
	typedef rspi_t<0x000D0100, peripheral::RSPI,  ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0,
		F_PCLKA>  RSPI;
	typedef rspi_t<0x000D0120, peripheral::RSPI2, ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0,
		F_PCLKA>  RSPI2;
#elif defined(SIG_RX65N)
	typedef rspi_t<0x000D0100, peripheral::RSPI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0,
		F_PCLKA>  RSPI0;
	typedef rspi_t<0x000D0140, peripheral::RSPI1, ICU::VECTOR::SPTI1, ICU::VECTOR::SPRI1,
		F_PCLKA>  RSPI1;
	typedef rspi_t<0x000D0300, peripheral::RSPI1, ICU::VECTOR::SPTI2, ICU::VECTOR::SPRI2,
		F_PCLKA>  RSPI2;
#elif defined(SIG_RX66T)
	typedef rspi_c_t<0x000D0100, peripheral::RSPI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0,
		F_PCLKA>  RSPI0;
#elif defined(SIG_RX72M) || defined(SIG_RX72N) || defined(SIG_RX66N)
	typedef rspi_t<0x000D0100, peripheral::RSPI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0,
		F_PCLKA>  RSPI0;
	typedef rspi_t<0x000D0140, peripheral::RSPI1, ICU::VECTOR::SPTI1, ICU::VECTOR::SPRI1,
		F_PCLKA>  RSPI1;
	typedef rspi_t<0x000D0300, peripheral::RSPI1, ICU::VECTOR::SPTI2, ICU::VECTOR::SPRI2,
		F_PCLKA>  RSPI2;
#endif
}
