#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・CAN 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN ベース・モジュール（CAN）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct can_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ（ CTLR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctlr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      MBM;
			bits_rw_t<io_, bitpos::B1, 2>   IDFM;
			bit_rw_t <io_, bitpos::B3>      MLM;
			bit_rw_t <io_, bitpos::B4>      TPM;
			bit_rw_t <io_, bitpos::B5>      TSRC;
			bits_rw_t<io_, bitpos::B6, 2>   TSPS;
			bits_rw_t<io_, bitpos::B8, 2>   CANM;
			bit_rw_t <io_, bitpos::B10>     SLPM;
			bits_rw_t<io_, bitpos::B11, 2>  BOM;
			bit_rw_t <io_, bitpos::B13>     RBOC;
		};
		static ctlr_t<base + 0x0640> CTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットコンフィグレーションレジスタ（ BCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct bcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CCLKS;
			bits_rw_t<io_, bitpos::B8,  3>  TSEG2;
			bits_rw_t<io_, bitpos::B12, 2>  SJW;
			bits_rw_t<io_, bitpos::B16, 10> BRP;
			bits_rw_t<io_, bitpos::B28, 4>  TSEG1;
		};
		static bcr_t<base + 0x0644> BCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  マスクレジスタ k （ MKRk ）（ k = 0 ～ 7 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mkrk_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  18>  EID;
			bits_rw_t<io_, bitpos::B18, 11>  SID;
		};
		static mkrk_t<base + 0x0200> MKR0;
		static mkrk_t<base + 0x0204> MKR1;
		static mkrk_t<base + 0x0208> MKR2;
		static mkrk_t<base + 0x020C> MKR3;
		static mkrk_t<base + 0x0210> MKR4;
		static mkrk_t<base + 0x0214> MKR5;
		static mkrk_t<base + 0x0218> MKR6;
		static mkrk_t<base + 0x021C> MKR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO 受信 ID 比較レジスタ 0 、 1 （ FIDCR0 、 FIDCR1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fidcrx_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  18>  EID;
			bits_rw_t<io_, bitpos::B18, 11>  SID;
			bit_rw_t <io_, bitpos::B30>      RTR;
			bit_rw_t <io_, bitpos::B31>      IDE;
		};
		static fidcrx_t<base + 0x0220> FIDCR0;
		static fidcrx_t<base + 0x0224> FIDCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  マスク無効レジスタ（ MKIVLR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mbn_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   MB0;
			bit_rw_t <io_, bitpos::B1>   MB1;
			bit_rw_t <io_, bitpos::B2>   MB2;
			bit_rw_t <io_, bitpos::B3>   MB3;
			bit_rw_t <io_, bitpos::B4>   MB4;
			bit_rw_t <io_, bitpos::B5>   MB5;
			bit_rw_t <io_, bitpos::B6>   MB6;
			bit_rw_t <io_, bitpos::B7>   MB7;
			bit_rw_t <io_, bitpos::B8>   MB8;
			bit_rw_t <io_, bitpos::B9>   MB9;
			bit_rw_t <io_, bitpos::B10>  MB10;
			bit_rw_t <io_, bitpos::B11>  MB11;
			bit_rw_t <io_, bitpos::B12>  MB12;
			bit_rw_t <io_, bitpos::B13>  MB13;
			bit_rw_t <io_, bitpos::B14>  MB14;
			bit_rw_t <io_, bitpos::B15>  MB15;
			bit_rw_t <io_, bitpos::B16>  MB16;
			bit_rw_t <io_, bitpos::B17>  MB17;
			bit_rw_t <io_, bitpos::B18>  MB18;
			bit_rw_t <io_, bitpos::B19>  MB19;
			bit_rw_t <io_, bitpos::B20>  MB20;
			bit_rw_t <io_, bitpos::B21>  MB21;
			bit_rw_t <io_, bitpos::B22>  MB22;
			bit_rw_t <io_, bitpos::B23>  MB23;
			bit_rw_t <io_, bitpos::B24>  MB24;
			bit_rw_t <io_, bitpos::B25>  MB25;
			bit_rw_t <io_, bitpos::B26>  MB26;
			bit_rw_t <io_, bitpos::B27>  MB27;
			bit_rw_t <io_, bitpos::B28>  MB28;
			bit_rw_t <io_, bitpos::B29>  MB29;
			bit_rw_t <io_, bitpos::B30>  MB30;
			bit_rw_t <io_, bitpos::B31>  MB31;
		};
		static mbn_t<base + 0x0228> MKIVLR;

/// 構成を検討中・・・
#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスレジスタ j （ MBj ）（ j = 0 ～ 31 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mbx_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  18>  EID;
			bits_rw_t<io_, bitpos::B18, 11>  SID;
			bit_rw_t <io_, bitpos::B30>      RTR;
			bit_rw_t <io_, bitpos::B31>      IDE;
		};
///		static mbx_t<base + 0x0000> MB0;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス割り込み許可レジスタ（ MIER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static mbn_t<base + 0x022C> MIER;

#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  メッセージ制御レジスタ j （ MCTLj ）（ j ＝ 0 ～ 31 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mctln_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  18>  EID;
			bits_rw_t<io_, bitpos::B18, 11>  SID;
			bit_rw_t <io_, bitpos::B30>      RTR;
			bit_rw_t <io_, bitpos::B31>      IDE;
		};
		static mctln_t<base + 0x0620> MCTL0;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO 制御レジスタ（ RFCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      RFE;
			bits_ro_t<io_, bitpos::B1, 3>   RFUST;
			bit_rw_t <io_, bitpos::B4>      RFMLF;
			bit_ro_t <io_, bitpos::B5>      RFFST;
			bit_ro_t <io_, bitpos::B6>      RFWST;
			bit_ro_t <io_, bitpos::B7>      RFEST;
		};
		static rfcr_t<base + 0x0648> RFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ポインタ制御レジスタ（ RFPCR ）
		*/
		//-----------------------------------------------------------------//
		static wo8_t<base + 0x0649>  RFPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO 制御レジスタ（ TFCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tfcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      TFE;
			bits_rw_t<io_, bitpos::B1, 3>   TFUST;
			bit_ro_t <io_, bitpos::B6>      TFFST;
			bit_ro_t <io_, bitpos::B7>      TFEST;
		};
		static tfcr_t<base + 0x064A> TFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO ポインタ制御レジスタ（ TFPCR ）
		*/
		//-----------------------------------------------------------------//
		static wo8_t<base + 0x064B>  TFPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ（ STR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct str_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>   NDST;
			bit_ro_t <in_, bitpos::B1>   SDST;
			bit_ro_t <in_, bitpos::B2>   RFST;
			bit_ro_t <in_, bitpos::B3>   TFST;
			bit_ro_t <in_, bitpos::B4>   NMLST;
			bit_ro_t <in_, bitpos::B5>   FMLST;
			bit_ro_t <in_, bitpos::B6>   TABST;
			bit_ro_t <in_, bitpos::B7>   EST;
			bit_ro_t <in_, bitpos::B8>   RSTST;
			bit_ro_t <in_, bitpos::B9>   HLTST;
			bit_ro_t <in_, bitpos::B10>  SLPST;
			bit_ro_t <in_, bitpos::B11>  EPST;
			bit_ro_t <in_, bitpos::B12>  BOST;
			bit_ro_t <in_, bitpos::B13>  TRMST;
			bit_ro_t <in_, bitpos::B14>  RECST;
		};
		static str_t<base + 0x0642> STR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスサーチモードレジスタ（ MSMR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct msmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  MBSM;
		};
		static msmr_t<base + 0x0654> MSMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスサーチステータスレジスタ（ MSSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mssr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  MBNST;
			bit_rw_t <io_, bitpos::B7>     SEST;
		};
		static mssr_t<base + 0x0652> MSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルサーチサポートレジスタ（ CSSR ）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x0651>  CSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタサポートレジスタ（ AFSR ）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x0656>  AFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  エラー割り込み許可レジスタ（ EIER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct eier_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BEIE;
			bit_rw_t<io_, bitpos::B1>  EWIE;
			bit_rw_t<io_, bitpos::B2>  EPIE;
			bit_rw_t<io_, bitpos::B3>  BOEIE;
			bit_rw_t<io_, bitpos::B4>  BORIE;
			bit_rw_t<io_, bitpos::B5>  ORIE;
			bit_rw_t<io_, bitpos::B6>  OLIE;
			bit_rw_t<io_, bitpos::B7>  BLIE;
		};
		static eier_t<base + 0x064C> EIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  エラー割り込み要因判定レジスタ（ EIFR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct eifr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  BEIF;
			bit_rw_t<io_, bitpos::B1>  EWIF;
			bit_rw_t<io_, bitpos::B2>  EPIF;
			bit_rw_t<io_, bitpos::B3>  BOEIF;
			bit_rw_t<io_, bitpos::B4>  BORIF;
			bit_rw_t<io_, bitpos::B5>  ORIF;
			bit_rw_t<io_, bitpos::B6>  OLIF;
			bit_rw_t<io_, bitpos::B7>  BLIF;
		};
		static eifr_t<base + 0x064D> EIFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信エラーカウントレジスタ（ RECR ）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x064E>  RECR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信エラーカウントレジスタ（ TECR ）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x064F>  TECR;


		//-----------------------------------------------------------------//
		/*!
			@brief	エラーコード格納レジスタ（ ECSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ecsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SEF;
			bit_rw_t<io_, bitpos::B1>  FEF;
			bit_rw_t<io_, bitpos::B2>  AEF;
			bit_rw_t<io_, bitpos::B3>  CEF;
			bit_rw_t<io_, bitpos::B4>  BE1F;
			bit_rw_t<io_, bitpos::B5>  BE0F;
			bit_rw_t<io_, bitpos::B6>  ADEF;
			bit_rw_t<io_, bitpos::B7>  EDPM;
		};
		static ecsr_t<base + 0x0650> ECSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイムスタンプレジスタ（ TSR ）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x0654>  TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	テスト制御レジスタ（ TCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     TSTE;
			bits_rw_t<io_, bitpos::B1, 2>  TSTM;
		};
		static tcr_t<base + 0x0658> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};


#if defined(SIG_RX66T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN モジュール（CAN 通常割り込み型）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxf		受信 FIFO 割り込み
		@param[in]	txf		送信 FIFO 割り込み
		@param[in]	rxm		メールボックス受信割り込み
		@param[in]	txm		メールボックス送信割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR rxf, ICU::VECTOR txf, ICU::VECTOR rxm, ICU::VECTOR txm>
	struct can_norm_t : can_t<base, per> {

		//-----------------------------------------------------------------//
		/*!
			@brief  RXF 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_rxf_vec() { return rxf; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TXF 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_txf_vec() { return txf; }


		//-----------------------------------------------------------------//
		/*!
			@brief  RXM 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_rxm_vec() { return rxm; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TXM 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_txm_vec() { return txm; }
	};
	typedef can_norm_t<0x00090200, peripheral::CAN0,
		ICU::VECTOR::RXF0, ICU::VECTOR::TXF0,
		ICU::VECTOR::RXM0, ICU::VECTOR::TXM0> CAN0;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN モジュール（CAN 選択割り込み型）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxf		受信 FIFO 割り込み
		@param[in]	txf		送信 FIFO 割り込み
		@param[in]	rxm		メールボックス受信割り込み
		@param[in]	txm		メールボックス送信割り込み
		@param[in]	ers		エラー割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB rxf, ICU::VECTOR_SELB txf, ICU::VECTOR_SELB rxm, ICU::VECTOR_SELB txm,
		ICU::VECTOR_BE0 ers>
	struct can_seli_t : can_t<base, per> {

		//-----------------------------------------------------------------//
		/*!
			@brief  RXF 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELB get_rxf_vec() { return rxf; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TXF 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELB get_txf_vec() { return txf; }


		//-----------------------------------------------------------------//
		/*!
			@brief  RXM 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELB get_rxm_vec() { return rxm; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TXM 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELB get_txm_vec() { return txm; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ERS 割り込みベクターを返す
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_BE0 get_ers_vec() { return ers; }
	};

	typedef can_seli_t<0x00090200, peripheral::CAN0,
		ICU::VECTOR_SELB::RXF0, ICU::VECTOR_SELB::TXF0,
		ICU::VECTOR_SELB::RXM0, ICU::VECTOR_SELB::TXM0, ICU::VECTOR_BE0::ERS0> CAN0;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	typedef can_seli_t<0x00091200, peripheral::CAN1,
		ICU::VECTOR_SELB::RXF1, ICU::VECTOR_SELB::TXF1,
		ICU::VECTOR_SELB::RXM1, ICU::VECTOR_SELB::TXM1, ICU::VECTOR_BE0::ERS1> CAN1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef can_seli_t<0x00092200, peripheral::CAN2,
		ICU::VECTOR_SELB::RXF2, ICU::VECTOR_SELB::TXF2,
		ICU::VECTOR_SELB::RXM2, ICU::VECTOR_SELB::TXM2, ICU::VECTOR_BE0::ERS2> CAN2;
#endif
#endif
// note: RX65x CAN0, CAN1
}
