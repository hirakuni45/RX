#pragma once
//=============================================================================//
/*!	@file
	@brief	Serial Peripheral Interface A / シリアルペリフェラルインタフェース
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSPIA base class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct rspia_base_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データレジスタ (SPDR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x00> SPDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI クロック遅延レジスタ (SPCKD)
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

			bits_rw_t<io_, bitpos::B0, 3>   SCKDL;
		};
		static inline spckd_t<base + 0x04> SPCKD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI スレーブセレクトネゲート遅延レジスタ (SSLND)
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

			bits_rw_t<io_, bitpos::B0, 3>   SLNDL;
		};
		static inline sslnd_t<base + 0x05> SSLND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 次アクセス遅延レジスタ (SPND)
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

			bits_rw_t<io_, bitpos::B0, 3>   SPNDL;
		};
		static inline spnd_t<base + 0x06> SPND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 制御レジスタ (SPCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      SPE;

			bit_rw_t <io_, bitpos::B7>      MRCKS;
			bit_rw_t <io_, bitpos::B8>      SPPE;
			bit_rw_t <io_, bitpos::B9>      SPOE;

			bit_rw_t <io_, bitpos::B11>     PTE;
			bit_rw_t <io_, bitpos::B12>     SCKASE;
			bit_rw_t <io_, bitpos::B13>     SCKDDIS;
			bit_rw_t <io_, bitpos::B14>     MODFEN;

			bit_rw_t <io_, bitpos::B16>     SPEIE;
			bit_rw_t <io_, bitpos::B17>     SPRIE;
			bit_rw_t <io_, bitpos::B18>     SPIIE;
			bit_rw_t <io_, bitpos::B19>     RDRIS;
			bit_rw_t <io_, bitpos::B20>     SPTIE;
			bit_rw_t <io_, bitpos::B21>     SPCIE;

			bit_rw_t <io_, bitpos::B24>     SPMS;
			bit_rw_t <io_, bitpos::B25>     FRFS;

			bits_rw_t<io_, bitpos::B28, 2>  CMMD;
			bit_rw_t <io_, bitpos::B30>     MSTR;
			bit_rw_t <io_, bitpos::B31>     SYNDIS;
		};
		static inline spcr_t<base + 0x08> SPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 受信専用モード制御レジスタ (SPRMCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sprmcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>   RFC;

			bit_rw_t <io_, bitpos::B6>      TERM;
			bit_rw_t <io_, bitpos::B7>      START;
		};
		static inline sprmcr_t<base + 0x0C> SPRMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 受信データレディ検出条件設定レジスタ (SPDRCSR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base + 0x0D> SPDRCSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 端子制御レジスタ (SPPCR)
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

			bit_rw_t <io_, bitpos::B0>      SPLP;
			bit_rw_t <io_, bitpos::B1>      SPLP2;

			bit_rw_t <io_, bitpos::B4>      MOIFV;
			bit_rw_t <io_, bitpos::B5>      MOIFE;
		};
		static inline sppcr_t<base + 0x0E> SPPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI スレーブセレクト極性レジスタ (SSLP)
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

			bit_rw_t <io_, bitpos::B0>      SSL0P;
			bit_rw_t <io_, bitpos::B1>      SSL1P;
			bit_rw_t <io_, bitpos::B2>      SSL2P;
			bit_rw_t <io_, bitpos::B3>      SSL3P;
		};
		static inline sslp_t<base + 0x10> SSLP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ビットレートレジスタ (SPBR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base + 0x11> SPBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI シーケンス制御レジスタ (SPSCR)
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

			bits_rw_t<io_, bitpos::B0, 3>   SPSLN;
		};
		static inline spscr_t<base + 0x13> SPSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  RSPI コマンドレジスタ (SPCMD[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spcmd_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 7) { io_::index = j * 4; } }

			bit_rw_t <io_, bitpos::B0>      CPHA;
			bit_rw_t <io_, bitpos::B1>      CPOL;
			bits_rw_t<io_, bitpos::B2, 2>   BRDV;

			bit_rw_t <io_, bitpos::B7>      SSLKP;

			bit_rw_t <io_, bitpos::B12>     LSBF;
			bit_rw_t <io_, bitpos::B13>     SPNDEN;
			bit_rw_t <io_, bitpos::B14>     SLNDEN;
			bit_rw_t <io_, bitpos::B15>     SCKDEN;
			bits_rw_t<io_, bitpos::B16, 5>  SPB;

			bits_rw_t<io_, bitpos::B24, 3>  SSLA;

			spcmd_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline spcmd_t<base + 0x14> SPCMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI データコントロールレジスタ (SPDCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      BYSW;

			bit_rw_t <io_, bitpos::B3>      SPRDTD;
			bit_rw_t <io_, bitpos::B4>      DINV;

			bits_rw_t<io_, bitpos::B8, 2>   SPFC;
		};
		static inline spdcr_t<base + 0x40> SPDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI FIFO コントロールレジスタ (SPFCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spfcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   RTRG;

			bits_rw_t<io_, bitpos::B8, 2>   TTRG;
		};
		static inline spfcr_t<base + 0x44> SPFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI シーケンスステータスレジスタ (SPSSR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spssr_t : public rw8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 3>   SPCP;

			bits_ro_t<in_, bitpos::B4, 3>   SPECM;
		};
		static inline spssr_t<base + 0x51> SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ステータスレジスタ (SPSR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spsr_t : public rw16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B7>      RRDYF;
			bit_ro_t <in_, bitpos::B8>      OVRF;
			bit_ro_t <in_, bitpos::B9>      IDLNF;
			bit_ro_t <in_, bitpos::B10>     MODF;
			bit_ro_t <in_, bitpos::B11>     PERF;
			bit_ro_t <in_, bitpos::B12>     UDRF;
			bit_ro_t <in_, bitpos::B13>     SPTEF;
			bit_ro_t <in_, bitpos::B14>     SPCF;
			bit_ro_t <in_, bitpos::B15>     SPRF;
		};
		static inline spsr_t<base + 0x52> SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 送信 FIFO ステータスレジスタ (SPTFSR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sptfsr_t : public rw8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 3>   FREE;
		};
		static inline sptfsr_t<base + 0x58> SPTFSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 受信 FIFO ステータスレジスタ (SPRFSR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sprfsr_t : public rw8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 3>   FILL;
		};
		static inline sprfsr_t<base + 0x5C> SPRFSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ステータスクリアレジスタ (SPSCLR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spsclr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>      RRDYFC;
			bit_rw_t <io_, bitpos::B8>      OVRFC;

			bit_rw_t <io_, bitpos::B10>     MODFC;
			bit_rw_t <io_, bitpos::B11>     PERFC;
			bit_rw_t <io_, bitpos::B12>     UDRFC;
			bit_rw_t <io_, bitpos::B13>     SPTEFC;
			bit_rw_t <io_, bitpos::B14>     SPCFC;
			bit_rw_t <io_, bitpos::B15>     SPRFC;
		};
		static inline spsclr_t<base + 0x6A> SPSCLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI FIFO クリアレジスタ (SPFCLR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spfclr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      FCLR;
		};
		static inline spfclr_t<base + 0x6C> SPFCLR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースＡ クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	spri	受信割り込みベクター
		@param[in]	spti	送信割り込みベクター
		@param[in]	spii	アイドル割り込み
		@param[in]	spei	エラー割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR spri, ICU::VECTOR spti, ICU::GROUPAL0 spii, ICU::GROUPAL0 spei>
	struct rspia_t : public rspia_base_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto SPRI = spri;		///< 受信割り込みベクター
		static constexpr auto SPTI = spti;		///< 送信割り込みベクター
		static constexpr auto SPII = spii;		///< アイドル割り込み
		static constexpr auto SPEI = spei;		///< エラー割り込み
		static constexpr auto PCLK = clock_profile::PCLKA;	///< PCLK 周波数
	};

#if defined(SIG_RX26T)
	typedef rspia_t<0x000E'2800, peripheral::RSPIA0,
		ICU::VECTOR::SPRI, ICU::VECTOR::SPTI, ICU::GROUPAL0::SPII, ICU::GROUPAL0::SPEI> RSPIA0;
#elif defined(SIG_RX671)
	typedef rspia_t<0x000E'2800, peripheral::RSPIA0,
		ICU::VECTOR::SPARI0, ICU::VECTOR::SPATI0, ICU::GROUPAL0::SPII, ICU::GROUPAL0::SPEI> RSPIA0;
#endif
}
