#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・CAN 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
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

		static const auto PERIPHERAL = per;		///< ペリフェラル型

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
		typedef ctlr_t<base + 0x0640> CTLR_;
		static  CTLR_ CTLR;


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
		typedef bcr_t<base + 0x0644> BCR_;
		static  BCR_ BCR;


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
		typedef mkrk_t<base + 0x0200> MKR0_;
		static  MKR0_ MKR0;
		typedef mkrk_t<base + 0x0204> MKR1_;
		static  MKR1_ MKR1;
		typedef mkrk_t<base + 0x0208> MKR2_;
		static  MKR2_ MKR2;
		typedef mkrk_t<base + 0x020C> MKR3_;
		static  MKR3_ MKR3;
		typedef mkrk_t<base + 0x0210> MKR4_;
		static  MKR4_ MKR4;
		typedef mkrk_t<base + 0x0214> MKR5_;
		static  MKR5_ MKR5;
		typedef mkrk_t<base + 0x0218> MKR6_;
		static  MKR6_ MKR6;
		typedef mkrk_t<base + 0x021C> MKR7_;
		static  MKR7_ MKR7;


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
		typedef fidcrx_t<base + 0x0220> FIDCR0_;
		static  FIDCR0_ FIDCR0;
		typedef fidcrx_t<base + 0x0224> FIDCR1_;
		static  FIDCR1_ FIDCR1;


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
		typedef mbn_t<base + 0x0228> MKIVLR_;
		static  MKIVLR_ MKIVLR;

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
///		typedef mbx_t<base + 0x0000> MB0_;
///		static  MB0_ MB0;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス割り込み許可レジスタ（ MIER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		typedef mbn_t<base + 0x022C> MIER_;
		static  MIER_ MIER;

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
		typedef mctln_t<base + 0x0620> MCTL0_;
		static  MCTL0_ MCTL0;
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
		typedef rfcr_t<base + 0x0648> RFCR_;
		static  RFCR_ RFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ポインタ制御レジスタ（ RFPCR ）
		*/
		//-----------------------------------------------------------------//
		typedef wo8_t<base + 0x0649>  RFPCR_;
		static  RFPCR_ RFPCR;


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
		typedef tfcr_t<base + 0x064A> TFCR_;
		static  TFCR_ TFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO ポインタ制御レジスタ（ TFPCR ）
		*/
		//-----------------------------------------------------------------//
		typedef wo8_t<base + 0x064B>  TFPCR_;
		static  TFPCR_ TFPCR;


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
		typedef str_t<base + 0x0642> STR_;
		static  STR_ STR;


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
		typedef msmr_t<base + 0x0654> MSMR_;
		static  MSMR_ MSMR;


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
		typedef mssr_t<base + 0x0652> MSSR_;
		static  MSSR_ MSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルサーチサポートレジスタ（ CSSR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x0651>  CSSR_;
		static  CSSR_ CSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタサポートレジスタ（ AFSR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0656>  AFSR_;
		static  AFSR_ AFSR;


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
		typedef eier_t<base + 0x064C> EIER_;
		static  EIER_ EIER;


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
		typedef eifr_t<base + 0x064D> EIFR_;
		static  EIFR_ EIFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信エラーカウントレジスタ（ RECR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x064E>  RECR_;
		static  RECR_ RECR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信エラーカウントレジスタ（ TECR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x064F>  TECR_;
		static  TECR_ TECR;


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
		typedef ecsr_t<base + 0x0650> ECSR_;
		static  ECSR_ ECSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイムスタンプレジスタ（ TSR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0654>  TSR_;
		static  TSR_ TSR;


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
		typedef tcr_t<base + 0x0658> TCR_;
		static  TCR_ TCR;
	};
	template <uint32_t base, peripheral per> typename can_t<base, per>::CTLR_ can_t<base, per>::CTLR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::BCR_ can_t<base, per>::BCR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR0_ can_t<base, per>::MKR0;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR1_ can_t<base, per>::MKR1;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR2_ can_t<base, per>::MKR2;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR3_ can_t<base, per>::MKR3;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR4_ can_t<base, per>::MKR4;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR5_ can_t<base, per>::MKR5;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR6_ can_t<base, per>::MKR6;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKR7_ can_t<base, per>::MKR7;
	template <uint32_t base, peripheral per> typename can_t<base, per>::FIDCR0_ can_t<base, per>::FIDCR0;
	template <uint32_t base, peripheral per> typename can_t<base, per>::FIDCR1_ can_t<base, per>::FIDCR1;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MKIVLR_ can_t<base, per>::MKIVLR;
///	template <uint32_t base, peripheral per> typename can_t<base, per>::MB0_ can_t<base, per>::MB0;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MIER_ can_t<base, per>::MIER;
///	template <uint32_t base, peripheral per> typename can_t<base, per>::MCTL0_ can_t<base, per>::MCTL0;
	template <uint32_t base, peripheral per> typename can_t<base, per>::RFCR_ can_t<base, per>::RFCR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::RFPCR_ can_t<base, per>::RFPCR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::TFCR_ can_t<base, per>::TFCR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::TFPCR_ can_t<base, per>::TFPCR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::STR_ can_t<base, per>::STR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MSMR_ can_t<base, per>::MSMR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::MSSR_ can_t<base, per>::MSSR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::CSSR_ can_t<base, per>::CSSR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::AFSR_ can_t<base, per>::AFSR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::EIER_ can_t<base, per>::EIER;
	template <uint32_t base, peripheral per> typename can_t<base, per>::EIFR_ can_t<base, per>::EIFR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::RECR_ can_t<base, per>::RECR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::TECR_ can_t<base, per>::TECR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::ECSR_ can_t<base, per>::ECSR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::TSR_ can_t<base, per>::TSR;
	template <uint32_t base, peripheral per> typename can_t<base, per>::TCR_ can_t<base, per>::TCR;


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

		static const auto RXF_VEC = rxf;	///< RXF 割り込みベクター
		static const auto TXF_VEC = txf;	///< TXF 割り込みベクター
		static const auto RXM_VEC = rxm;	///< RXM 割り込みベクター
		static const auto TXM_VEC = txm;	///< TXM 割り込みベクター
	};
	typedef can_norm_t<0x00090200, peripheral::CAN0,
		ICU::VECTOR::RXF0, ICU::VECTOR::TXF0,
		ICU::VECTOR::RXM0, ICU::VECTOR::TXM0> CAN0;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72N)
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

		static const auto VEC_RXF = rxf;	///< RXF 割り込みベクター
		static const auto TXF_VEC = txf;	///< TXF 割り込みベクター
		static const auto RXM_VEC = rxm;	///< RXM 割り込みベクター
		static const auto TXM_VEC = txm;	///< TXM 割り込みベクター
		static const auto ERS_VEC = ers;	///< ERS 割り込みベクター
	};

	typedef can_seli_t<0x00090200, peripheral::CAN0,
		ICU::VECTOR_SELB::RXF0, ICU::VECTOR_SELB::TXF0,
		ICU::VECTOR_SELB::RXM0, ICU::VECTOR_SELB::TXM0, ICU::VECTOR_BE0::ERS0> CAN0;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72N)
	typedef can_seli_t<0x00091200, peripheral::CAN1,
		ICU::VECTOR_SELB::RXF1, ICU::VECTOR_SELB::TXF1,
		ICU::VECTOR_SELB::RXM1, ICU::VECTOR_SELB::TXM1, ICU::VECTOR_BE0::ERS1> CAN1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72N)
	typedef can_seli_t<0x00092200, peripheral::CAN2,
		ICU::VECTOR_SELB::RXF2, ICU::VECTOR_SELB::TXF2,
		ICU::VECTOR_SELB::RXM2, ICU::VECTOR_SELB::TXM2, ICU::VECTOR_BE0::ERS2> CAN2;
#endif
#endif
// note: RX65x CAN0, CAN1
}
