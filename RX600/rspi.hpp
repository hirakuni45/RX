#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・RSPI[abc] 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/renesas.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxv		受信ベクター
		@param[in]	txv		送信ベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv>
	struct rspi_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 制御レジスタ（SPCR）
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

			bit_rw_t<io_, bitpos::B0> SPMS;
			bit_rw_t<io_, bitpos::B1> TXMD;
			bit_rw_t<io_, bitpos::B2> MODFEN;
			bit_rw_t<io_, bitpos::B3> MSTR;
			bit_rw_t<io_, bitpos::B4> SPEIE;
			bit_rw_t<io_, bitpos::B5> SPTIE;
			bit_rw_t<io_, bitpos::B6> SPE;
			bit_rw_t<io_, bitpos::B7> SPRIE;
		};
		typedef spcr_t_<base + 0x00> spcr_t;
		static spcr_t SPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI スレーブセレクト極性レジスタ（SSLP）
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

			bit_rw_t<io_, bitpos::B0> SSLP0;
			bit_rw_t<io_, bitpos::B1> SSLP1;
			bit_rw_t<io_, bitpos::B2> SSLP2;
			bit_rw_t<io_, bitpos::B3> SSLP3;
		};
		typedef sslp_t_<base + 0x01> sslp_t;
		static sslp_t SSLP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 端子制御レジスタ（SPPCR）
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
			bit_rw_t<io_, bitpos::B1>	SPLP2;
			bit_rw_t<io_, bitpos::B4>	MOIFV;
			bit_rw_t<io_, bitpos::B5>	MOIFE;
		};
		typedef sppcr_t_<base + 0x02> sppcr_t;
		static sppcr_t SPPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ステータスレジスタ（SPSR）
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

			bit_rw_t<io_, bitpos::B0> OVRF;
			bit_rw_t<io_, bitpos::B1> IDLNF;
			bit_rw_t<io_, bitpos::B2> MODF;
			bit_rw_t<io_, bitpos::B3> PERF;
			bit_rw_t<io_, bitpos::B5> SPTEF;
			bit_rw_t<io_, bitpos::B7> SPRF;
		};
		typedef spsr_t_<base + 0x03> spsr_t;
		static spsr_t SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データレジスタ（SPDR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			rw16_t<ofs> H;
		};
		typedef spdr_t_<base + 0x04> spdr_t;
		static spdr_t SPDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI シーケンス制御レジスタ（SPSCR）
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

			bits_rw_t<io_, bitpos::B0, 3> SPSLN;
		};
		typedef spscr_t_<base + 0x08> spscr_t;
		static spscr_t SPSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI シーケンスステータスレジスタ（SPSSR）
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

			bits_rw_t<io_, bitpos::B0, 3> SPCP;
			bits_rw_t<io_, bitpos::B4, 3> SPECM;
		};
		typedef spssr_t_<base + 0x09> spssr_t;
		static spssr_t SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ビットレートレジスタ（SPBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x0A> spbr_t;
		static spbr_t SPBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データコントロールレジスタ（SPDCR）
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

			bits_rw_t<io_, bitpos::B0, 2> SPFC;
			bit_rw_t <io_, bitpos::B4>    SPRDTD;
			bit_rw_t <io_, bitpos::B5>    SPLW;
		};
		typedef spdcr_t_<base + 0x0B> spdcr_t;
		static spdcr_t SPDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI クロック遅延レジスタ（SPCKD）
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
			@brief  RSPI スレーブセレクトネゲート遅延レジスタ（SSLND）
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
			@brief  RSPI 次アクセス遅延レジスタ（SPND）
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
			@brief  RSPI 制御レジスタ 2（SPCR2）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcr2_t_ : public rw8_t<ofs> {
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
		typedef spcr2_t_<base + 0x0F> spcr2_t;
		static spcr2_t SPCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI コマンドレジスタ 0 ～ 7（SPCMD0 ～ SPCMD7）
			@param[in]	ofs	オフセット
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
			bits_rw_t<io_, bitpos::B4, 3> SSLA;
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
		typedef spcmd_t_<base + 0x18> spcmd4_t;
		static spcmd4_t SPCMD4;
		typedef spcmd_t_<base + 0x1A> spcmd5_t;
		static spcmd5_t SPCMD5;
		typedef spcmd_t_<base + 0x1C> spcmd6_t;
		static spcmd6_t SPCMD6;
		typedef spcmd_t_<base + 0x1E> spcmd7_t;
		static spcmd7_t SPCMD7;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャンネルを返す
			@return チャネル
		*/
		//-----------------------------------------------------------------//
		int get_chanel() const {
			return (base >> 5) & 3;
		}


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

#if defined(SIG_RX24T)
	typedef rspi_t<0x00088380, peripheral::RSPI0, ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0>  RSPI0;
#elif defined(SIG_RX64M)
	typedef rspi_t<0x000D0100, peripheral::RSPI,  ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0>  RSPI;
#elif defined(SIG_RX71M)
	typedef rspi_t<0x000D0100, peripheral::RSPI,  ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0>  RSPI;
	typedef rspi_t<0x000D0120, peripheral::RSPI2, ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0>  RSPI2;
#elif defined(SIG_RX65N)
	typedef rspi_t<0x000D0100, peripheral::RSPI0, ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0>  RSPI0;
	typedef rspi_t<0x000D0140, peripheral::RSPI1, ICU::VECTOR::SPRI1, ICU::VECTOR::SPTI1>  RSPI1;
	typedef rspi_t<0x000D0300, peripheral::RSPI1, ICU::VECTOR::SPRI2, ICU::VECTOR::SPTI2>  RSPI2;
#elif defined(SIG_RX66T) || defined(SIG_RX72M)

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス (c)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxv		受信ベクター
		@param[in]	txv		送信ベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv>
	struct rspi_c_t : public rspi_t<base, per, rxv, txv> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データコントロールレジスタ 2 (SPDCR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdcr2_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BYSW;
		};
		typedef spdcr2_t_<base + 0x20> spdcr2_t;
		static spdcr2_t SPDCR2;
	};
#if defined(SIG_RX66T)
	typedef rspi_c_t<0x000D0100, peripheral::RSPI0, ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0>  RSPI0;
#elif defined(SIG_RX72M)
	typedef rspi_t<0x000D0100, peripheral::RSPI0, ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0>  RSPI0;
	typedef rspi_t<0x000D0140, peripheral::RSPI1, ICU::VECTOR::SPRI1, ICU::VECTOR::SPTI1>  RSPI1;
	typedef rspi_t<0x000D0300, peripheral::RSPI1, ICU::VECTOR::SPRI2, ICU::VECTOR::SPTI2>  RSPI2;
#endif
#endif

	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcr_t rspi_t<base, per, rxv, txv>::SPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::sslp_t rspi_t<base, per, rxv, txv>::SSLP;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::sppcr_t rspi_t<base, per, rxv, txv>::SPPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spsr_t rspi_t<base, per, rxv, txv>::SPSR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spdr_t rspi_t<base, per, rxv, txv>::SPDR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spscr_t rspi_t<base, per, rxv, txv>::SPSCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spssr_t rspi_t<base, per, rxv, txv>::SPSSR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spbr_t rspi_t<base, per, rxv, txv>::SPBR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spdcr_t rspi_t<base, per, rxv, txv>::SPDCR;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spckd_t rspi_t<base, per, rxv, txv>::SPCKD;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::sslnd_t rspi_t<base, per, rxv, txv>::SSLND;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spnd_t rspi_t<base, per, rxv, txv>::SPND;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcr2_t rspi_t<base, per, rxv, txv>::SPCR2;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd0_t rspi_t<base, per, rxv, txv>::SPCMD0;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd1_t rspi_t<base, per, rxv, txv>::SPCMD1;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd2_t rspi_t<base, per, rxv, txv>::SPCMD2;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd3_t rspi_t<base, per, rxv, txv>::SPCMD3;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd4_t rspi_t<base, per, rxv, txv>::SPCMD4;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd5_t rspi_t<base, per, rxv, txv>::SPCMD5;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd6_t rspi_t<base, per, rxv, txv>::SPCMD6;
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_t<base, per, rxv, txv>::spcmd7_t rspi_t<base, per, rxv, txv>::SPCMD7;

#if defined(SIG_RX66T) || defined(SIG_RX72M)
	template <uint32_t base, peripheral per, ICU::VECTOR rxv, ICU::VECTOR txv> typename rspi_c_t<base, per, rxv, txv>::spdcr2_t rspi_c_t<base, per, rxv, txv>::SPDCR2;
#endif
}
