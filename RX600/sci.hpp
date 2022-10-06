#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SCI 定義 SCI[ijgh]
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2015, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI core クラス（初期の RX マイコンに備わっていた SCI）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_core_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ (RDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro8_t<base + 0x05> RDR_;
		static RDR_ RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x03> TDR_;
		static TDR_ TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct smr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			// 非スマートカードインタフェースモード
			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B2>	  MP;
			bit_rw_t <io_, bitpos::B3>	  STOP;
			bit_rw_t <io_, bitpos::B4>	  PM;
			bit_rw_t <io_, bitpos::B5>	  PE;
			bit_rw_t <io_, bitpos::B6>	  CHR;
			bit_rw_t <io_, bitpos::B7>	  CM;

			// スマートカードインタフェースモード
			bits_rw_t<io_, bitpos::B2, 2> BCP;
			bit_rw_t <io_, bitpos::B6>	  BLK;
			bit_rw_t <io_, bitpos::B7>	  GM;
		};
		typedef smr_t<base + 0x00> SMR_;
		static SMR_ SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKE;
			bit_rw_t <io_, bitpos::B2>	  TEIE;
			bit_rw_t <io_, bitpos::B3>	  MPIE;
			bit_rw_t <io_, bitpos::B4>	  RE;
			bit_rw_t <io_, bitpos::B5>	  TE;
			bit_rw_t <io_, bitpos::B6>	  RIE;
			bit_rw_t <io_, bitpos::B7>	  TIE;
		};
		typedef scr_t<base + 0x02> SCR_;
		static SCR_ SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (SSR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MPBT;
			bit_rw_t<io_, bitpos::B1> MPB;
			bit_rw_t<io_, bitpos::B2> TEND;
			bit_rw_t<io_, bitpos::B3> PER;
			bit_rw_t<io_, bitpos::B4> FER;
			bit_rw_t<io_, bitpos::B5> ORER;
			bit_rw_t<io_, bitpos::B6> RDRF;
			bit_rw_t<io_, bitpos::B7> TDRE;
		};
		typedef ssr_t<base + 0x04> SSR_;
		static SSR_ SSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x01> BRR_;
		static BRR_ BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル拡張レジスタ (SEMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct semr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ACS0;
			bit_rw_t<io_, bitpos::B2> BRME;		// sci[g]

			bit_rw_t<io_, bitpos::B4> ABCS;
			bit_rw_t<io_, bitpos::B5> NFEN;		// sci[g]
			bit_rw_t<io_, bitpos::B6> BGDM;		// sci[g]
			bit_rw_t<io_, bitpos::B7> RXDESEL;	// sci[g]
		};
		typedef semr_t<base + 0x07> SEMR_;
		static SEMR_ SEMR;
	};
	template <uint32_t base> typename sci_core_t<base>::RDR_ sci_core_t<base>::RDR;
	template <uint32_t base> typename sci_core_t<base>::TDR_ sci_core_t<base>::TDR;
	template <uint32_t base> typename sci_core_t<base>::SMR_ sci_core_t<base>::SMR;
	template <uint32_t base> typename sci_core_t<base>::SCR_ sci_core_t<base>::SCR;
	template <uint32_t base> typename sci_core_t<base>::SSR_ sci_core_t<base>::SSR;
	template <uint32_t base> typename sci_core_t<base>::BRR_ sci_core_t<base>::BRR;
	template <uint32_t base> typename sci_core_t<base>::SEMR_ sci_core_t<base>::SEMR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIa 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信ベクター
		@param[in]	rxv		受信ベクター
		@param[in]	tev		送信終了ベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv,
		typename INT, INT tev, uint32_t pclk>
	struct scia_t : public sci_core_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TX_VEC = txv;		///< 受信割り込みベクター
		static constexpr auto RX_VEC = rxv;		///< 送信割り込みベクター
		static constexpr auto TE_VEC = tev;		///< 送信終了割り込みベクター
		static constexpr auto PCLK = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = false;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = false;	///< BGDM（ボーレート倍速）


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）ダミー
		*/
		//-----------------------------------------------------------------//
		typedef rw8_null_t<0x00000000> MDDR_;
		static MDDR_ MDDR;


 		//-----------------------------------------------------------------//
		/*!
			@brief  スマートカードモードレジスタ (SCMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SMIF;

			bit_rw_t<io_, bitpos::B2> SINV;
			bit_rw_t<io_, bitpos::B3> SDIR;

			bit_rw_t<io_, bitpos::B7> BCP2;
		};
		typedef scmr_t<base + 0x06> SCMR_;
		static SCMR_ SCMR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI core2 クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_core2_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ H 、 L 、 HL (RDRH 、 RDRL 、 RDRHL)
		*/
		//-----------------------------------------------------------------//
		typedef ro8_t<base + 0x10> RDRH_;
		static RDRH_ RDRH;
		typedef ro8_t<base + 0x11> RDRL_;
		static RDRL_ RDRL;
		typedef ro16_t<base + 0x10> RDRHL_;
		static RDRHL_ RDRHL;


 		//-----------------------------------------------------------------//
		/*!
			@brief  スマートカードモードレジスタ (SCMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SMIF;

			bit_rw_t<io_, bitpos::B2> SINV;
			bit_rw_t<io_, bitpos::B3> SDIR;
			bit_rw_t<io_, bitpos::B4> CHR1;

			bit_rw_t<io_, bitpos::B7> BCP2;
		};
		typedef scmr_t<base + 0x06> SCMR_;
		static SCMR_ SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x12> MDDR_;
		static MDDR_ MDDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタ設定レジスタ (SNFR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct snfr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> NFCS;
		};
		typedef snfr_t<base + 0x08> SNFR_;
		static SNFR_ SNFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ１ (SIMR1)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct simr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IICM;
			bits_rw_t<io_, bitpos::B3, 5> IICDL;
		};
		typedef simr1_t<base + 0x09> SIMR1_;
		static SIMR1_ SIMR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ２ (SIMR2)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template < uint32_t ofs>
		struct simr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IICINTM;
			bit_rw_t<io_, bitpos::B1> IICCSC;
			bit_rw_t<io_, bitpos::B5> IICACKT;
		};
		typedef simr2_t<base + 0x0A> SIMR2_;
		static SIMR2_ SIMR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ３ (SIMR3)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct simr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IICSTAREQ;
			bit_rw_t <io_, bitpos::B1>    IICRSTAREQ;
			bit_rw_t <io_, bitpos::B2>    IICSTPREQ;
			bit_rw_t <io_, bitpos::B3>    IICSTIF;
			bits_rw_t<io_, bitpos::B4, 2> IICSDAS;
			bits_rw_t<io_, bitpos::B6, 2> IICSCLS;
		};
		typedef simr3_t<base + 0x0B> SIMR3_;
		static SIMR3_ SIMR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C ステータスレジスタ (SISR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sisr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IICACKR;
		};
		typedef sisr_t<base + 0x0C> SISR_;
		static SISR_ SISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SPI モードレジスタ (SPMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SSE;
			bit_rw_t<io_, bitpos::B1> CTSE;
			bit_rw_t<io_, bitpos::B2> MSS;
			bit_rw_t<io_, bitpos::B4> MFF;
			bit_rw_t<io_, bitpos::B6> CKPOL;
			bit_rw_t<io_, bitpos::B7> CKPH;
		};
		typedef spmr_t<base + 0x0D> SPMR_;
		static SPMR_ SPMR;
	};
	template <uint32_t base> typename sci_core2_t<base>::RDRH_ sci_core2_t<base>::RDRH;
	template <uint32_t base> typename sci_core2_t<base>::RDRL_ sci_core2_t<base>::RDRL;
	template <uint32_t base> typename sci_core2_t<base>::RDRHL_ sci_core2_t<base>::RDRHL;
	template <uint32_t base> typename sci_core2_t<base>::SCMR_ sci_core2_t<base>::SCMR;
	template <uint32_t base> typename sci_core2_t<base>::MDDR_ sci_core2_t<base>::MDDR;
	template <uint32_t base> typename sci_core2_t<base>::SNFR_ sci_core2_t<base>::SNFR;
	template <uint32_t base> typename sci_core2_t<base>::SIMR1_ sci_core2_t<base>::SIMR1;
	template <uint32_t base> typename sci_core2_t<base>::SIMR2_ sci_core2_t<base>::SIMR2;
	template <uint32_t base> typename sci_core2_t<base>::SIMR3_ sci_core2_t<base>::SIMR3;
	template <uint32_t base> typename sci_core2_t<base>::SISR_ sci_core2_t<base>::SISR;
	template <uint32_t base> typename sci_core2_t<base>::SPMR_ sci_core2_t<base>::SPMR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIh 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信ベクター
		@param[in]	rxv		受信ベクター
		@param[in]	tev		送信終了ベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv,
		typename INT, INT tev, uint32_t pclk>
	struct scih_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TX_VEC = txv;		///< 受信割り込みベクター
		static constexpr auto RX_VEC = rxv;		///< 送信割り込みベクター
		static constexpr auto TE_VEC = tev;		///< 送信終了割り込みベクター
		static constexpr uint32_t PCLK = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;	///< BGDM（ボーレート倍速）

		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモード有効レジスタ (ESMER) @n
					※SIC12 にのみ有効なレジスタ
		*/
		//-----------------------------------------------------------------//
		struct esmer_t : public rw8_t<base + 0x20> {
			typedef rw8_t<base + 0x20> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ESME;
		};
		typedef esmer_t ESMER_;
		static ESMER_ ESMER;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 0（CR0） @n
					※SIC12 にのみ有効なレジスタ
		*/
		//-----------------------------------------------------------------//
		struct cr0_t : public rw8_t<base + 0x21> {
			typedef rw8_t<base + 0x21> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t<io_, bitpos::B1> SCSF;
			bit_ro_t<io_, bitpos::B2> RXDSF;
			bit_rw_t<io_, bitpos::B3> BRME;
		};
		typedef cr0_t CR0_;
		static CR0_ CR0;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, uint32_t pclk>
		typename scih_t<base, per, txv, rxv, INT, tev, pclk>::ESMER_ scih_t<base, per, txv, rxv, INT, tev, pclk>::ESMER;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, uint32_t pclk>
		typename scih_t<base, per, txv, rxv, INT, tev, pclk>::CR0_ scih_t<base, per, txv, rxv, INT, tev, pclk>::CR0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIi クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信ベクター
		@param[in]	rxv		受信ベクター
		@param[in]	tev		送信終了ベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv,
		typename INT, INT tev, uint32_t pclk>
	struct scii_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TX_VEC = txv;		///< 受信割り込みベクター
		static constexpr auto RX_VEC = rxv;		///< 送信割り込みベクター
		static constexpr auto TE_VEC = tev;		///< 送信終了割り込みベクター
		static constexpr uint32_t PCLK = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;	///< BGDM（ボーレート倍速）

		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO データレジスタ (FRDR)
		*/
		//-----------------------------------------------------------------//
		struct frdr_t : public ro16_t<base + 0x10> {
			typedef ro16_t<base + 0x10> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 9> RDAT;
			bit_ro_t <io_, bitpos::B9>	  MPB;
			bit_ro_t <io_, bitpos::B10>	  DR;
			bit_ro_t <io_, bitpos::B11>	  PER;
			bit_ro_t <io_, bitpos::B12>	  FER;
			bit_ro_t <io_, bitpos::B13>	  ORER;
			bit_ro_t <io_, bitpos::B14>	  RDF;
		};
		typedef frdr_t FRDR_;
		static FRDR_ FRDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO データレジスタ (FTDR)
		*/
		//-----------------------------------------------------------------//
		struct ftdr_t : public wo16_t<base + 0x0E> {
			typedef wo16_t<base + 0x0E> io_;
			using io_::operator =;

			bits_rw_t<io_, bitpos::B0, 9> TDAT;
			bit_rw_t <io_, bitpos::B9>	  MPBT;
		};
		typedef ftdr_t FTDR_;
		static FTDR_ FTDR;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, uint32_t pclk>
		typename scii_t<base, per, txv, rxv, INT, tev, pclk>::FRDR_ scii_t<base, per, txv, rxv, INT, tev, pclk>::FRDR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, uint32_t pclk>
		typename scii_t<base, per, txv, rxv, INT, tev, pclk>::FTDR_ scii_t<base, per, txv, rxv, INT, tev, pclk>::FTDR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIg クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信ベクター
		@param[in]	rxv		受信ベクター
		@param[in]	tev		送信終了ベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv,
		typename INT, INT tev, uint32_t pclk>
	struct scig_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TX_VEC = txv;		///< 受信割り込みベクター
		static constexpr auto RX_VEC = rxv;		///< 送信割り込みベクター
		static constexpr auto TE_VEC = tev;		///< 送信終了割り込みベクター
		static constexpr uint32_t PCLK = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;	///< BGDM（ボーレート倍速）
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIj クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txv		送信ベクター
		@param[in]	rxv		受信ベクター
		@param[in]	tev		送信終了ベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv,
		typename INT, INT tev, uint32_t pclk>
	struct scij_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TX_VEC = txv;		///< 受信割り込みベクター
		static constexpr auto RX_VEC = rxv;		///< 送信割り込みベクター
		static constexpr auto TE_VEC = tev;		///< 送信終了割り込みベクター
		static constexpr uint32_t PCLK = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;	///< BGDM（ボーレート倍速）
	};


#if defined(SIG_RX621) || defined(SIG_RX62N)
	typedef scia_t<0x00088240, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR, ICU::VECTOR::TEI0, clock_profile::PCLK> SCI0;
	typedef scia_t<0x00088248, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, clock_profile::PCLK> SCI1;
	typedef scia_t<0x00088250, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::VECTOR, ICU::VECTOR::TEI2, clock_profile::PCLK> SCI2;
	typedef scia_t<0x00088258, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::VECTOR, ICU::VECTOR::TEI3, clock_profile::PCLK> SCI3;
	typedef scia_t<0x00088268, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, clock_profile::PCLK> SCI5;
	typedef scia_t<0x00088270, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, clock_profile::PCLK> SCI6;
#elif defined(SIG_RX24T)
	typedef scig_t<0x0008A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, clock_profile::PCLKB> SCI1;
	typedef scig_t<0x0008A020, peripheral::SCI1C, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, clock_profile::PCLKB> SCI1C;
	typedef scig_t<0x0008A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, clock_profile::PCLKB> SCI5;
	typedef scig_t<0x0008A0A0, peripheral::SCI5C, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, clock_profile::PCLKB> SCI5C;
	typedef scig_t<0x0008A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, clock_profile::PCLKB> SCI6;
	typedef scig_t<0x0008A0C0, peripheral::SCI6C, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, clock_profile::PCLKB> SCI6C;

#elif defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef scig_t<0x0008A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI0, clock_profile::PCLKB> SCI0;
	typedef scig_t<0x0008A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI1, clock_profile::PCLKB> SCI1;
	typedef scig_t<0x0008A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI2, clock_profile::PCLKB> SCI2;
	typedef scig_t<0x0008A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI3, clock_profile::PCLKB> SCI3;
	typedef scig_t<0x0008A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI4, clock_profile::PCLKB> SCI4;
	typedef scig_t<0x0008A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI5, clock_profile::PCLKB> SCI5;
	typedef scig_t<0x0008A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI6, clock_profile::PCLKB> SCI6;
	typedef scig_t<0x0008A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI7, clock_profile::PCLKB> SCI7;

	typedef scih_t<0x0008B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI12, clock_profile::PCLKB> SCI12;

#elif defined(SIG_RX65N)
	typedef scig_t<0x0008A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI0, clock_profile::PCLKB> SCI0;
	typedef scig_t<0x0008A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI1, clock_profile::PCLKB> SCI1;
	typedef scig_t<0x0008A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI2, clock_profile::PCLKB> SCI2;
	typedef scig_t<0x0008A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI3, clock_profile::PCLKB> SCI3;
	typedef scig_t<0x0008A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI4, clock_profile::PCLKB> SCI4;
	typedef scig_t<0x0008A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI5, clock_profile::PCLKB> SCI5;
	typedef scig_t<0x0008A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI6, clock_profile::PCLKB> SCI6;
	typedef scig_t<0x0008A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI7, clock_profile::PCLKB> SCI7;
	typedef scig_t<0x0008A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::VECTOR_BL1, ICU::VECTOR_BL1::TEI8, clock_profile::PCLKB> SCI8;
	typedef scig_t<0x0008A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR_BL1, ICU::VECTOR_BL1::TEI9, clock_profile::PCLKB> SCI9;

	typedef scii_t<0x000D0040, peripheral::SCI10, ICU::VECTOR::TXI10, ICU::VECTOR::RXI10,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI10, clock_profile::PCLKA> SCI10;
	typedef scii_t<0x000D0060, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI11, clock_profile::PCLKA> SCI11;

	typedef scih_t<0x0008B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI12, clock_profile::PCLKB> SCI12;

#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef scij_t<0x0008A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI1, clock_profile::PCLKB> SCI1;

	typedef scij_t<0x0008A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI5, clock_profile::PCLKB> SCI5;
	typedef scij_t<0x0008A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI6, clock_profile::PCLKB> SCI6;

	typedef scij_t<0x0008A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::VECTOR_BL1, ICU::VECTOR_BL1::TEI8, clock_profile::PCLKB> SCI8;
	typedef scij_t<0x0008A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR_BL1, ICU::VECTOR_BL1::TEI9, clock_profile::PCLKB> SCI9;

	typedef scii_t<0x000D0000, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI11, clock_profile::PCLKA> SCI11;

	typedef scih_t<0x0008B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI12, clock_profile::PCLKB> SCI12;

#elif defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef scij_t<0x0008A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI0, clock_profile::PCLKB> SCI0;
	typedef scij_t<0x0008A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI1, clock_profile::PCLKB> SCI1;
	typedef scij_t<0x0008A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI2, clock_profile::PCLKB> SCI2;
	typedef scij_t<0x0008A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI3, clock_profile::PCLKB> SCI3;
	typedef scij_t<0x0008A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI4, clock_profile::PCLKB> SCI4;
	typedef scij_t<0x0008A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI5, clock_profile::PCLKB> SCI5;
	typedef scij_t<0x0008A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI6, clock_profile::PCLKB> SCI6;

	typedef scii_t<0x0008A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI7, clock_profile::PCLKA> SCI7;
	typedef scii_t<0x000D0000, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI8, clock_profile::PCLKA> SCI8;
	typedef scii_t<0x000D0020, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI9, clock_profile::PCLKA> SCI9;
	typedef scii_t<0x000D0040, peripheral::SCI10, ICU::VECTOR::TXI10, ICU::VECTOR::RXI10,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI10, clock_profile::PCLKA> SCI10;
	typedef scii_t<0x000D0060, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::VECTOR_AL0, ICU::VECTOR_AL0::TEI11, clock_profile::PCLKA> SCI11;

	typedef scih_t<0x0008B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::VECTOR_BL0, ICU::VECTOR_BL0::TEI12, clock_profile::PCLKB> SCI12;
#endif
}
