#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ SCI 定義 SCI[acijgh]
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2015, 2022 Kunihito Hiramatsu @n
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
			bit_rw_t<io_, bitpos::B5> NFEN;		// sci[cg]
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
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR tei, ICU::VECTOR eri, uint32_t pclk>
	struct scia_t : public sci_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = false;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = false;	///< BGDM（ボーレート倍速）
		static constexpr bool SEMR_NFEN = false;	///< NFEN（ノイズフィルタ）


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
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, ICU::VECTOR eri, uint32_t pclk>
		typename scia_t<base, per, txv, rxv, tev, eri, pclk>::SCMR_ scia_t<base, per, txv, rxv, tev, eri, pclk>::SCMR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIc 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	INT		割り込みベクター型
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR tei, typename INT, INT eri, uint32_t pclk>
	struct scic_t : public sci_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = false;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = false;	///< BGDM（ボーレート倍速）
		static constexpr bool SEMR_NFEN = true;		///< NFEN（ノイズフィルタ）


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
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scic_t<base, per, txv, rxv, tev, INT, eri, pclk>::SCMR_ scic_t<base, per, txv, rxv, tev, INT, eri, pclk>::SCMR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scic_t<base, per, txv, rxv, tev, INT, eri, pclk>::SNFR_ scic_t<base, per, txv, rxv, tev, INT, eri, pclk>::SNFR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCId 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	INT		割り込みベクター型
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR tei, typename INT, INT eri, uint32_t pclk>
	struct scid_t : public sci_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = false;	///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = false;	///< BGDM（ボーレート倍速）
		static constexpr bool SEMR_NFEN = true;		///< NFEN（ノイズフィルタ）


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
			@brief  拡張シリアルモード有効レジスタ（ESMER）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct esmer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ESME;
		};
		typedef esmer_t<base + 0x20> ESMER_;
		static ESMER_ ESMER;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 0（CR0）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  SFSF;
			bit_rw_t<io_, bitpos::B2>  RXDSF;
			bit_rw_t<io_, bitpos::B3>  BRME;
		};
		typedef cr0_t<base + 0x21> CR0_;
		static CR0_ CR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 1（CR1）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     BFE;
			bit_rw_t <io_, bitpos::B1>     CF0RE;
			bits_rw_t<io_, bitpos::B2, 2>  CF1DS;
			bit_rw_t <io_, bitpos::B4>     PIBE;
			bits_rw_t<io_, bitpos::B5, 3>  PIBS;
		};
		typedef cr1_t<base + 0x22> CR1_;
		static CR1_ CR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 2（CR2）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  DFCS;
			bits_rw_t<io_, bitpos::B4, 2>  BCCS;
			bits_rw_t<io_, bitpos::B6, 2>  RTS;
		};
		typedef cr2_t<base + 0x23> CR2_;
		static CR2_ CR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 3（CR3）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  SDST;
		};
		typedef cr3_t<base + 0x24> CR3_;
		static CR3_ CR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートコントロールレジスタ（PCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  TXDXPS;
			bit_rw_t<io_, bitpos::B1>  RXDXPS;

			bit_rw_t<io_, bitpos::B4>  SHARPS;
		};
		typedef pcr_t<base + 0x25> PCR_;
		static PCR_ PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みコントロールレジスタ（ICR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BFDIE;
			bit_rw_t<io_, bitpos::B1>  CF0MIE;
			bit_rw_t<io_, bitpos::B2>  CF1MIE;
			bit_rw_t<io_, bitpos::B3>  PIBDIE;
			bit_rw_t<io_, bitpos::B4>  BCDIE;
			bit_rw_t<io_, bitpos::B5>  AEDIE;
		};
		typedef icr_t<base + 0x26> ICR_;
		static ICR_ ICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ（STR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct str_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  BFDF;
			bit_ro_t<io_, bitpos::B1>  CF0MF;
			bit_ro_t<io_, bitpos::B2>  CF1MF;
			bit_ro_t<io_, bitpos::B3>  PIBDF;
			bit_ro_t<io_, bitpos::B4>  BCDF;
			bit_ro_t<io_, bitpos::B5>  AEDF;
		};
		typedef str_t<base + 0x27> STR_;
		static STR_ STR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスクリアレジスタ（STCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct stcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BFDCL;
			bit_rw_t<io_, bitpos::B1>  CF0MCL;
			bit_rw_t<io_, bitpos::B2>  CF1MCL;
			bit_rw_t<io_, bitpos::B3>  PIBDCL;
			bit_rw_t<io_, bitpos::B4>  BCDCL;
			bit_rw_t<io_, bitpos::B5>  AEDCL;
		};
		typedef stcr_t<base + 0x28> STCR_;
		static STCR_ STCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 データレジスタ（CF0DR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x29> CF0DR_;
		static CF0DR_ CF0DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 コンペアイネーブルレジスタ（CF0CR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cf0cr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CF0CE0;
			bit_rw_t<io_, bitpos::B1>  CF0CE1;
			bit_rw_t<io_, bitpos::B2>  CF0CE2;
			bit_rw_t<io_, bitpos::B3>  CF0CE3;
			bit_rw_t<io_, bitpos::B4>  CF0CE4;
			bit_rw_t<io_, bitpos::B5>  CF0CE5;
			bit_rw_t<io_, bitpos::B6>  CF0CE6;
			bit_rw_t<io_, bitpos::B7>  CF0CE7;
		};
		typedef cf0cr_t<base + 0x2A> CF0CR_;
		static CF0CR_ CF0CR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 受信データレジスタ（CF0RR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2B> CF0RR_;
		static CF0RR_ CF0RR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プライマリ Control Field 1 データレジスタ（PCF1DR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2C> PCF1DR_;
		static PCF1DR_ PCF1DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  セカンダリ Control Field 1 データレジスタ（SCF1DR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2D> SCF1DR_;
		static SCF1DR_ SCF1DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 1 コンペアイネーブルレジスタ（CF1CR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cf1cr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CF1CE0;
			bit_rw_t<io_, bitpos::B1>  CF1CE1;
			bit_rw_t<io_, bitpos::B2>  CF1CE2;
			bit_rw_t<io_, bitpos::B3>  CF1CE3;
			bit_rw_t<io_, bitpos::B4>  CF1CE4;
			bit_rw_t<io_, bitpos::B5>  CF1CE5;
			bit_rw_t<io_, bitpos::B6>  CF1CE6;
			bit_rw_t<io_, bitpos::B7>  CF1CE7;
		};
		typedef cf1cr_t<base + 0x2E> CF1CR_;
		static CF1CR_ CF1CR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 1 受信データレジスタ（CF1RR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2F> CF1RR_;
		static CF1RR_ CF1RR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  TCST;
		};
		typedef tcr_t<base + 0x30> TCR_;
		static TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TDMS;

			bit_rw_t <io_, bitpos::B3>     TCST;
			bits_rw_t<io_, bitpos::B4, 3>  TCSS;
		};
		typedef tmr_t<base + 0x31> TMR_;
		static TMR_ TMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマプリスケーラレジスタ（TPRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x32> TPRE_;
		static TPRE_ TPRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウントレジスタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x33> TCNT_;
		static TCNT_ TCNT;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::SCMR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::SCMR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::SNFR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::SNFR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::ESMER_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::ESMER;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR0_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR0;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR1_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR1;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR2_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR2;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR3_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CR3;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::PCR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::PCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::ICR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::ICR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::STR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::STR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::STCR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::STCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF0DR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF0DR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF0CR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF0CR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF0RR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF0RR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::PCF1DR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::PCF1DR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::SCF1DR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::SCF1DR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF1CR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF1CR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF1RR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::CF1RR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TCR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TMR_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TMR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TPRE_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TPRE;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, ICU::VECTOR tev, typename INT, INT eri, uint32_t pclk>
		typename scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TCNT_ scid_t<base, per, txv, rxv, tev, INT, eri, pclk>::TCNT;


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
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		typename INT, INT tei, INT eri, uint32_t pclk>
	struct scih_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;		///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;		///< BGDM（ボーレート倍速）
		static constexpr bool SEMR_NFEN = true;		///< NFEN（ノイズフィルタ）

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
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, INT eri, uint32_t pclk>
		typename scih_t<base, per, txv, rxv, INT, tev, eri, pclk>::ESMER_ scih_t<base, per, txv, rxv, INT, tev, eri, pclk>::ESMER;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, INT eri, uint32_t pclk>
		typename scih_t<base, per, txv, rxv, INT, tev, eri, pclk>::CR0_ scih_t<base, per, txv, rxv, INT, tev, eri, pclk>::CR0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIi クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		typename INT, INT tei, INT eri, uint32_t pclk>
	struct scii_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;		///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;		///< BGDM（ボーレート倍速）
		static constexpr bool SEMR_NFEN = true;		///< NFEN（ノイズフィルタ）


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
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, INT eri, uint32_t pclk>
		typename scii_t<base, per, txv, rxv, INT, tev, eri, pclk>::FRDR_ scii_t<base, per, txv, rxv, INT, tev, eri, pclk>::FRDR;
	template <uint32_t base, peripheral per, ICU::VECTOR txv, ICU::VECTOR rxv, typename INT, INT tev, INT eri, uint32_t pclk>
		typename scii_t<base, per, txv, rxv, INT, tev, eri, pclk>::FTDR_ scii_t<base, per, txv, rxv, INT, tev, eri, pclk>::FTDR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIg クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		typename INT, INT tei, INT eri, uint32_t pclk>
	struct scig_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;		///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;		///< BGDM（ボーレート倍速）
		static constexpr bool SEMR_NFEN = true;		///< NFEN（ノイズフィルタ）
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIj クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		typename INT, INT tei, INT eri, uint32_t pclk>
	struct scij_t : public sci_core_t<base>, sci_core2_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = pclk;	///< PCLK 周波数

		static constexpr bool SEMR_BRME = true;		///< BRME（ボーレート微調整）
		static constexpr bool SEMR_BGDM = true;		///< BGDM（ボーレート倍速）
		static constexpr bool SEMR_NFEN = true;		///< NFEN（ノイズフィルタ）
	};

#if defined(SIG_RX220)
	typedef scia_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR::TEI1, ICU::VECTOR::ERI1, clock_profile::PCLKB> SCI1;

#elif defined(SIG_RX621) || defined(SIG_RX62N)
	typedef scia_t<0x0008'8240, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR::TEI0, ICU::VECTOR::ERI0, clock_profile::PCLK> SCI0;
	typedef scia_t<0x0008'8248, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR::TEI1, ICU::VECTOR::ERI1, clock_profile::PCLK> SCI1;
	typedef scia_t<0x0008'8250, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::VECTOR::TEI2, ICU::VECTOR::ERI2, clock_profile::PCLK> SCI2;
	typedef scia_t<0x0008'8258, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::VECTOR::TEI3, ICU::VECTOR::ERI3, clock_profile::PCLK> SCI3;
	typedef scia_t<0x0008'8268, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR::TEI5, ICU::VECTOR::ERI5, clock_profile::PCLK> SCI5;
	typedef scia_t<0x0008'8270, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR::TEI6, ICU::VECTOR::ERI6, clock_profile::PCLK> SCI6;
#elif defined(SIG_RX63T)
	typedef scic_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0, ICU::VECTOR::TEI0,
		ICU::GROUP12, ICU::GROUP12::ERI0, clock_profile::PCLKB> SCI0;
	typedef scic_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1, ICU::VECTOR::TEI1, 
		ICU::GROUP12, ICU::GROUP12::ERI1, clock_profile::PCLKB> SCI1;
	typedef scic_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2, ICU::VECTOR::TEI2,
		ICU::GROUP12, ICU::GROUP12::ERI2, clock_profile::PCLKB> SCI2;
	typedef scic_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3, ICU::VECTOR::TEI3,
		ICU::GROUP12, ICU::GROUP12::ERI3, clock_profile::PCLKB> SCI3;
	typedef scid_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12, ICU::VECTOR::TEI12,
		ICU::GROUP12, ICU::GROUP12::ERI12, clock_profile::PCLKB> SCI12;
#elif defined(SIG_RX24T)
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, ICU::VECTOR::ERI1, clock_profile::PCLKB> SCI1;
	typedef scig_t<0x0008'A020, peripheral::SCI1C, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, ICU::VECTOR::ERI1, clock_profile::PCLKB> SCI1C;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, ICU::VECTOR::ERI5, clock_profile::PCLKB> SCI5;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5C, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, ICU::VECTOR::ERI5, clock_profile::PCLKB> SCI5C;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, ICU::VECTOR::ERI6, clock_profile::PCLKB> SCI6;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6C, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, ICU::VECTOR::ERI6, clock_profile::PCLKB> SCI6C;

#elif defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef scig_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI0, ICU::GROUPBL0::ERI0, clock_profile::PCLKB> SCI0;
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1, clock_profile::PCLKB> SCI1;
	typedef scig_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI2, ICU::GROUPBL0::ERI2, clock_profile::PCLKB> SCI2;
	typedef scig_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI3, ICU::GROUPBL0::ERI3, clock_profile::PCLKB> SCI3;
	typedef scig_t<0x0008'A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI4, ICU::GROUPBL0::ERI4, clock_profile::PCLKB> SCI4;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5, clock_profile::PCLKB> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6, clock_profile::PCLKB> SCI6;
	typedef scig_t<0x0008'A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI7, ICU::GROUPBL0::ERI7, clock_profile::PCLKB> SCI7;

	typedef scih_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI12, ICU::GROUPBL0::ERI12, clock_profile::PCLKB> SCI12;

#elif defined(SIG_RX65N)
	typedef scig_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI0, ICU::GROUPBL0::ERI0, clock_profile::PCLKB> SCI0;
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1, clock_profile::PCLKB> SCI1;
	typedef scig_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI2, ICU::GROUPBL0::ERI2, clock_profile::PCLKB> SCI2;
	typedef scig_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI3, ICU::GROUPBL0::ERI3, clock_profile::PCLKB> SCI3;
	typedef scig_t<0x0008'A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI4, ICU::GROUPBL0::ERI4, clock_profile::PCLKB> SCI4;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5, clock_profile::PCLKB> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6, clock_profile::PCLKB> SCI6;
	typedef scig_t<0x0008'A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI7, ICU::GROUPBL0::ERI7, clock_profile::PCLKB> SCI7;
	typedef scig_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI8, ICU::GROUPBL1::ERI8, clock_profile::PCLKB> SCI8;
	typedef scig_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI9, ICU::GROUPBL1::ERI9, clock_profile::PCLKB> SCI9;

	typedef scii_t<0x000D'0040, peripheral::SCI10, ICU::VECTOR::TXI10, ICU::VECTOR::RXI10,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI10, ICU::GROUPAL0::ERI10, clock_profile::PCLKA> SCI10;
	typedef scii_t<0x000D'0060, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI11, ICU::GROUPAL0::ERI11, clock_profile::PCLKA> SCI11;

	typedef scih_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI12, ICU::GROUPBL0::ERI12, clock_profile::PCLKB> SCI12;

#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef scij_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1, clock_profile::PCLKB> SCI1;

	typedef scij_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5, clock_profile::PCLKB> SCI5;
	typedef scij_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6, clock_profile::PCLKB> SCI6;

	typedef scij_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI8, ICU::GROUPBL1::ERI8, clock_profile::PCLKB> SCI8;
	typedef scij_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI9, ICU::GROUPBL1::ERI9, clock_profile::PCLKB> SCI9;

	typedef scii_t<0x000D'0000, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI11, ICU::GROUPAL0::ERI11, clock_profile::PCLKA> SCI11;

	typedef scih_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI12, ICU::GROUPBL0::ERI12, clock_profile::PCLKB> SCI12;

#elif defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef scij_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI0, ICU::GROUPBL0::ERI0, clock_profile::PCLKB> SCI0;
	typedef scij_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1, clock_profile::PCLKB> SCI1;
	typedef scij_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI2, ICU::GROUPBL0::ERI2, clock_profile::PCLKB> SCI2;
	typedef scij_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI3, ICU::GROUPBL0::ERI3, clock_profile::PCLKB> SCI3;
	typedef scij_t<0x0008'A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI4, ICU::GROUPBL0::ERI4, clock_profile::PCLKB> SCI4;
	typedef scij_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5, clock_profile::PCLKB> SCI5;
	typedef scij_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6, clock_profile::PCLKB> SCI6;

	typedef scii_t<0x0008'A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI7, ICU::GROUPAL0::ERI7, clock_profile::PCLKA> SCI7;
	typedef scii_t<0x000D'0000, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI8, ICU::GROUPAL0::ERI8, clock_profile::PCLKA> SCI8;
	typedef scii_t<0x000D'0020, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI9, ICU::GROUPAL0::ERI9, clock_profile::PCLKA> SCI9;
	typedef scii_t<0x000D'0040, peripheral::SCI10, ICU::VECTOR::TXI10, ICU::VECTOR::RXI10,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI10, ICU::GROUPAL0::ERI10, clock_profile::PCLKA> SCI10;
	typedef scii_t<0x000D'0060, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI11, ICU::GROUPAL0::ERI11, clock_profile::PCLKA> SCI11;

	typedef scih_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI12, ICU::GROUPBL0::ERI12, clock_profile::PCLKB> SCI12;
#endif
}
