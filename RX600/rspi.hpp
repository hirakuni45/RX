#pragma once
//=============================================================================//
/*!	@file
	@brief	Serial Peripheral Interface / シリアルペリフェラルインタフェース @n
			RX110/RX111/RX113/RX130/RX140 @n
			RX220 @n
			RX231 @n
			RX23T @n
			RX24T/RX24U @n
			RX260/RX261 @n
			RX621/RX62N @n
			RX63T @n
			RX631/RX63N @n
			RX64M @n
			RX71M @n
			RX65N @n
			RX671 @n
			RX66T/RX72T @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSPI base class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct rspi_base_t {

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
		static inline spcr_t<base + 0x00> SPCR;


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
		static inline sslp_t<base + 0x01> SSLP;


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
		static inline sppcr_t<base + 0x02> SPPCR;


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
			bit_rw_t<io_, bitpos::B4> UDRF;
			bit_rw_t<io_, bitpos::B5> SPTEF;
			bit_rw_t<io_, bitpos::B6> SPCF;		///< d version only
			bit_rw_t<io_, bitpos::B7> SPRF;
		};
		static inline spsr_t<base + 0x03> SPSR;


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

			rw16_t<ofs>	H;
			rw8_t<ofs>	HH;
		};
		static inline spdr_t<base + 0x04> SPDR;


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
		static inline spscr_t<base + 0x08> SPSCR;


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
		static inline spssr_t<base + 0x09> SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ビットレートレジスタ（SPBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base + 0x0A> SPBR;


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
			bit_rw_t <io_, bitpos::B6>    SPBYT;	// RSPI[cd]
		};
		static inline spdcr_t<base + 0x0B> SPDCR;


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
		static inline spckd_t<base + 0x0C> SPCKD;


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
		static inline sslnd_t<base + 0x0D> SSLND;


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
		static inline spnd_t<base + 0x0E> SPND;


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
		static inline spcr2_t<base + 0x0F> SPCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI コマンドレジスタ（SPCMD[0] ～ SPCMD[7]）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcmd_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 2; } }

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

			spcmd_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline spcmd_t<base + 0x10> SPCMD;
//		static inline spcmd_t<base + 0x12> SPCMD1;
//		static inline spcmd_t<base + 0x14> SPCMD2;
//		static inline spcmd_t<base + 0x16> SPCMD3;
//		static inline spcmd_t<base + 0x18> SPCMD4;
//		static inline spcmd_t<base + 0x1A> SPCMD5;
//		static inline spcmd_t<base + 0x1C> SPCMD6;
//		static inline spcmd_t<base + 0x1E> SPCMD7;


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
			bit_rw_t<io_, bitpos::B1>  DINV;
		};
		static inline spdcr2_t<base + 0x20> SPDCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 制御レジスタ 3 (SPCR3)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RXMD;
			bit_rw_t<io_, bitpos::B1>  SCKDDIS;

			bit_rw_t<io_, bitpos::B4>  SPCIE;
		};
		static inline spcr3_t<base + 0x21> SPCR3;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス (RSPI)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	pclk	PCLK 周波数
		@param[in]	EIT		エラー割り込み型
		@param[in]	spri	受信バッファフル割り込みベクター
		@param[in]	spti	送信バッファエンプティ割り込みベクター
		@param[in]	spei	エラー割り込みベクター
		@param[in]	spii	アイドル割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, uint32_t pclk, typename EIT,
		ICU::VECTOR spri, ICU::VECTOR spti, EIT spei, ICU::VECTOR spii>
	struct rspi_t : public rspi_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr uint32_t PCLK = pclk;		///< PCLK 周波数
		static constexpr auto SPRI = spri;			///< 受信バッファフル割り込みベクター
		static constexpr auto SPTI = spti;			///< 送信バッファエンプティ割り込みベクター
		static constexpr auto SPEI = spei;			///< エラー割り込みベクター
		static constexpr auto SPII = spii;			///< アイドル割り込みベクター

		static constexpr bool BYTE_ACCESS = false;	///< バイトアクセス機能
		static constexpr bool SPSR_UDRF   = false;	///< SPSR.UDRF 機能
		static constexpr bool SPSR_SPTEF  = false;	///< SPSR.SPTEF 機能
		static constexpr bool SPSR_SPCF   = false;	///< SPSR.SPCF 機能
		static constexpr bool SPSR_SPRF   = false;	///< SPSR.SPRF 機能
		static constexpr bool SPDCR2_BYSW = false;	///< SPDCR2.BYSW 機能
		static constexpr bool SPDCR2_DINV = false;	///< SPDCR2.DINV 機能
		static constexpr bool SPCR3_reg   = false;	///< SPCR3 機能
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス (RSPIa)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	pclk	PCLK 周波数
		@param[in]	EIT		エラー割り込み型
		@param[in]	IIT		アイドル割り込み型
		@param[in]	spri	受信バッファフル割り込みベクター
		@param[in]	spti	送信バッファエンプティ割り込みベクター
		@param[in]	spei	エラー割り込みベクター
		@param[in]	spii	アイドル割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, uint32_t pclk, typename EIT, typename IIT,
		ICU::VECTOR spri, ICU::VECTOR spti, EIT spei, IIT spii>
	struct rspi_a_t : public rspi_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr uint32_t PCLK = pclk;		///< PCLK 周波数
		static constexpr auto SPRI = spri;			///< 受信バッファフル割り込みベクター
		static constexpr auto SPTI = spti;			///< 送信バッファエンプティ割り込みベクター
		static constexpr auto SPEI = spei;			///< エラー割り込みベクター
		static constexpr auto SPII = spii;			///< アイドル割り込みベクター

		static constexpr bool BYTE_ACCESS = false;	///< バイトアクセス機能
		static constexpr bool SPSR_UDRF   = false;	///< SPSR.UDRF 機能
		static constexpr bool SPSR_SPTEF  = true;	///< SPSR.SPTEF 機能
		static constexpr bool SPSR_SPCF   = false;	///< SPSR.SPCF 機能
		static constexpr bool SPSR_SPRF   = true;	///< SPSR.SPRF 機能
		static constexpr bool SPDCR2_BYSW = false;	///< SPDCR2.BYSW 機能
		static constexpr bool SPDCR2_DINV = false;	///< SPDCR2.DINV 機能
		static constexpr bool SPCR3_reg   = false;	///< SPCR3 機能
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス (RSPIb)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	pclk	PCLK 周波数
		@param[in]	spri	受信バッファフル割り込みベクター
		@param[in]	spti	送信バッファエンプティ割り込みベクター
		@param[in]	spei	エラー割り込みベクター
		@param[in]	spii	アイドル割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, uint32_t pclk,
		ICU::VECTOR spri, ICU::VECTOR spti, ICU::VECTOR spei, ICU::VECTOR spii>
	struct rspi_b_t : public rspi_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr uint32_t PCLK = pclk;		///< PCLK 周波数
		static constexpr auto SPRI = spri;			///< 受信バッファフル割り込みベクター
		static constexpr auto SPTI = spti;			///< 送信バッファエンプティ割り込みベクター
		static constexpr auto SPEI = spei;			///< エラー割り込みベクター
		static constexpr auto SPII = spii;			///< アイドル割り込みベクター

		static constexpr bool BYTE_ACCESS = false;	///< バイトアクセス機能
		static constexpr bool SPSR_UDRF   = true;	///< SPSR.UDRF 機能
		static constexpr bool SPSR_SPTEF  = true;	///< SPSR.SPTEF 機能
		static constexpr bool SPSR_SPCF   = false;	///< SPSR.SPCF 機能
		static constexpr bool SPSR_SPRF   = true;	///< SPSR.SPRF 機能
		static constexpr bool SPDCR2_BYSW = false;	///< SPDCR2.BYSW 機能
		static constexpr bool SPCR3_reg   = false;	///< SPCR3 機能
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス (RSPIc)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	pclk	PCLK 周波数
		@param[in]	EIT		エラー割り込み型
		@param[in]	IIT		アイドル割り込み型
		@param[in]	spri	受信バッファフル割り込みベクター
		@param[in]	spti	送信バッファエンプティ割り込みベクター
		@param[in]	spei	エラー割り込みベクター
		@param[in]	spii	アイドル割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, uint32_t pclk, typename EIT, typename IIT,
		ICU::VECTOR spri, ICU::VECTOR spti, EIT spei, IIT spii>
	struct rspi_c_t : public rspi_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr uint32_t PCLK = pclk;		///< PCLK 周波数
		static constexpr auto SPRI = spri;			///< 受信バッファフル割り込みベクター
		static constexpr auto SPTI = spti;			///< 送信バッファエンプティ割り込みベクター
		static constexpr auto SPEI = spei;			///< エラー割り込みベクター
		static constexpr auto SPII = spii;			///< アイドル割り込みベクター

		static constexpr bool BYTE_ACCESS = true;	///< バイトアクセス機能
		static constexpr bool SPSR_UDRF   = true;	///< SPSR.UDRF 機能
		static constexpr bool SPSR_SPTEF  = true;	///< SPSR.SPTEF 機能
		static constexpr bool SPSR_SPCF   = false;	///< SPSR.SPCF 機能
		static constexpr bool SPSR_SPRF   = true;	///< SPSR.SPRF 機能
		static constexpr bool SPDCR2_BYSW = true;	///< SPDCR2.BYSW 機能
		static constexpr bool SPDCR2_DINV = false;	///< SPDCR2.DINV 機能
		static constexpr bool SPCR3_reg   = false;	///< SPCR3 機能
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  シリアルペリフェラルインタフェースクラス (RSPId)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	pclk	PCLK 周波数
		@param[in]	EIT		エラー割り込み型
		@param[in]	IIT		アイドル割り込み型
		@param[in]	spri	受信バッファフル割り込みベクター
		@param[in]	spti	送信バッファエンプティ割り込みベクター
		@param[in]	spei	エラー割り込みベクター
		@param[in]	spii	アイドル割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, uint32_t pclk, typename EIT, typename IIT,
		ICU::VECTOR spri, ICU::VECTOR spti, EIT spei, IIT spii>
	struct rspi_d_t : public rspi_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr uint32_t PCLK = pclk;		///< PCLK 周波数
		static constexpr auto SPRI = spri;			///< 受信バッファフル割り込みベクター
		static constexpr auto SPTI = spti;			///< 送信バッファエンプティ割り込みベクター
		static constexpr auto SPEI = spei;			///< エラー割り込みベクター
		static constexpr auto SPII = spii;			///< アイドル割り込みベクター

		static constexpr bool BYTE_ACCESS = true;	///< バイトアクセス機能
		static constexpr bool SPSR_UDRF   = true;	///< SPSR.UDRF 機能
		static constexpr bool SPSR_SPTEF  = true;	///< SPSR.SPTEF 機能
		static constexpr bool SPSR_SPCF   = true;	///< SPSR.SPCF 機能
		static constexpr bool SPSR_SPRF   = true;	///< SPSR.SPRF 機能
		static constexpr bool SPDCR2_BYSW = true;	///< SPDCR2.BYSW 機能
		static constexpr bool SPDCR2_DINV = true;	///< SPDCR2.DINV 機能
		static constexpr bool SPCR3_reg   = true;	///< SPCR3 機能
	};

#if defined(SIG_RX110) || defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130) || defined(SIG_RX140)
	typedef rspi_c_t<0x0008'8380, peripheral::RSPI0, clock_profile::PCLKB, ICU::VECTOR, ICU::VECTOR,
		ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPEI0, ICU::VECTOR::SPII0> RSPI0;
#elif defined(SIG_RX220)
	typedef rspi_t  <0x0008'8380, peripheral::RSPI0, clock_profile::PCLKB, ICU::VECTOR,
		ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPEI0, ICU::VECTOR::SPII0> RSPI0;
#elif defined(SIG_RX231) || defined(SIG_RX23T)
	typedef rspi_a_t<0x0008'8380, peripheral::RSPI0, clock_profile::PCLKB, ICU::VECTOR, ICU::VECTOR,
		ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPEI0, ICU::VECTOR::SPII0> RSPI0;
#elif defined(SIG_RX24T) || defined(SIG_RX24U)
	typedef rspi_b_t<0x0008'8380, peripheral::RSPI0, clock_profile::PCLKB,
		ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPEI0, ICU::VECTOR::SPII0> RSPI0;
#elif defined(SIG_RX260) || defined(SIG_RX261)
	typedef rspi_c_t<0x0008'8300, peripheral::RSPI0, clock_profile::PCLKB, ICU::VECTOR, ICU::VECTOR,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::VECTOR::SPEI0, ICU::VECTOR::SPII0> RSPI0;
#elif defined(SIG_RX621) || defined(SIG_RX62N)
	typedef rspi_a_t<0x0008'8380, peripheral::RSPI0, clock_profile::PCLK, ICU::VECTOR, ICU::VECTOR,
		ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0, ICU::VECTOR::SPEI0, ICU::VECTOR::SPII0> RSPI0;
	typedef rspi_a_t<0x0008'83A0, peripheral::RSPI1, clock_profile::PCLK, ICU::VECTOR, ICU::VECTOR,
		ICU::VECTOR::SPRI1, ICU::VECTOR::SPTI1, ICU::VECTOR::SPEI1, ICU::VECTOR::SPII1> RSPI1;
#elif defined(SIG_RX63T) || defined(SIG_RX63T_S)
	typedef rspi_a_t<0x0008'8380, peripheral::RSPI0, clock_profile::PCLKB, ICU::GROUP12, ICU::VECTOR,
		ICU::VECTOR::SPRI0, ICU::VECTOR::SPTI0, ICU::GROUP12::SPEI0, ICU::VECTOR::SPII0> RSPI0;
	typedef rspi_a_t<0x0008'83A0, peripheral::RSPI1, clock_profile::PCLKB, ICU::GROUP12, ICU::VECTOR,
		ICU::VECTOR::SPRI1, ICU::VECTOR::SPTI1, ICU::GROUP12::SPEI1, ICU::VECTOR::SPII1> RSPI1;
#elif defined(SIG_RX631) || defined(SIG_RX63N)
	typedef rspi_t<0x0008'8380, peripheral::RSPI0, clock_profile::PCLKB, ICU::GROUP12,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::GROUP12::SPEI0, ICU::VECTOR::SPII0> RSPI0;
	typedef rspi_t<0x0008'83A0, peripheral::RSPI1, clock_profile::PCLKB, ICU::GROUP12,
		ICU::VECTOR::SPTI1, ICU::VECTOR::SPRI1, ICU::GROUP12::SPEI1, ICU::VECTOR::SPII1> RSPI1;
	typedef rspi_t<0x0008'83C0, peripheral::RSPI2, clock_profile::PCLKB, ICU::GROUP12,
		ICU::VECTOR::SPTI2, ICU::VECTOR::SPRI2, ICU::GROUP12::SPEI2, ICU::VECTOR::SPII2> RSPI2;
#elif defined(SIG_RX64M)
	typedef rspi_a_t<0x000D'0100, peripheral::RSPI0, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::GROUPAL0::SPEI0, ICU::GROUPAL0::SPII0> RSPI0;
#elif defined(SIG_RX71M)
	typedef rspi_a_t<0x000D'0100, peripheral::RSPI0, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::GROUPAL0::SPEI0, ICU::GROUPAL0::SPII0> RSPI0;
	typedef rspi_a_t<0x000D'0120, peripheral::RSPI1, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI1, ICU::VECTOR::SPRI1, ICU::GROUPAL0::SPEI1, ICU::GROUPAL0::SPII1> RSPI1;
#elif defined(SIG_RX65N) || defined(SIG_RX72N) || defined(SIG_RX72M) || defined(SIG_RX66N)
	typedef rspi_c_t<0x000D'0100, peripheral::RSPI0, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::GROUPAL0::SPEI0, ICU::GROUPAL0::SPII0> RSPI0;
	typedef rspi_c_t<0x000D'0140, peripheral::RSPI1, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI1, ICU::VECTOR::SPRI1, ICU::GROUPAL0::SPEI1, ICU::GROUPAL0::SPII1> RSPI1;
	typedef rspi_c_t<0x000D'0300, peripheral::RSPI2, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI2, ICU::VECTOR::SPRI2, ICU::GROUPAL0::SPEI2, ICU::GROUPAL0::SPII2> RSPI2;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef rspi_c_t<0x000D'0100, peripheral::RSPI0, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::GROUPAL0::SPEI0, ICU::GROUPAL0::SPII0> RSPI0;
#elif defined(SIG_RX660)
	typedef rspi_d_t<0x000D'0100, peripheral::RSPI0, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::GROUPAL0::SPEI0, ICU::GROUPAL0::SPII0> RSPI0;
#elif defined(SIG_RX671)
	typedef rspi_d_t<0x000D'0100, peripheral::RSPI0, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI0, ICU::VECTOR::SPRI0, ICU::GROUPAL0::SPEI0, ICU::GROUPAL0::SPII0> RSPI0;
	typedef rspi_d_t<0x000D'0140, peripheral::RSPI1, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI1, ICU::VECTOR::SPRI1, ICU::GROUPAL0::SPEI1, ICU::GROUPAL0::SPII1> RSPI1;
	typedef rspi_d_t<0x000D'0300, peripheral::RSPI2, clock_profile::PCLKA, ICU::GROUPAL0, ICU::GROUPAL0,
		ICU::VECTOR::SPTI2, ICU::VECTOR::SPRI2, ICU::GROUPAL0::SPEI2, ICU::GROUPAL0::SPII2> RSPI2;
#endif
}
