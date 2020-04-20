#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SDHI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDHI 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	cdeti	カード検出割り込み・ベクタ
		@param[in]	caci	カードアクセス割り込み・ベクタ
		@param[in]	sdaci	SDIO アクセス割り込み・ベクタ
		@param[in]	sbfai	バッファアクセス割り込み・ベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	struct sdhi_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型
		static const auto CDET_VEC = cdeti;		///< CDET 割り込みベクター
		static const auto CAC_VEC = caci;		///< CAC 割り込みベクター
		static const auto SDAC_VEC = sdaci;		///< SDAC 割り込みベクター
		static const auto SBFA_VEC = sbfai;		///< SBFA 割り込みベクター

		//-----------------------------------------------------------------//
		/*!
			@brief  コマンドレジスタ（ SDCMD ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdcmd_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  CMDIDX;
			bits_rw_t<io_, bitpos::B6, 2>  ACMD;
			bits_rw_t<io_, bitpos::B8, 3>  RSPTP;
			bit_rw_t <io_, bitpos::B11>    CMDTP;
			bit_rw_t <io_, bitpos::B12>    CMDRW;
			bit_rw_t <io_, bitpos::B13>    TRSTP;
			bits_rw_t<io_, bitpos::B14, 2> CMD12AT;
		};
		typedef sdcmd_t<base + 0x00> SDCMD_;
		static SDCMD_ SDCMD;


		//-----------------------------------------------------------------//
		/*!
			@brief  アーギュメントレジスタ（ SDARG ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x08> SDARG_;
		static SDARG_ SDARG;


		//-----------------------------------------------------------------//
		/*!
			@brief  データストップレジスタ（ SDSTOP ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdstop_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  STP;
			bit_rw_t<io_, bitpos::B8>  SDBLKCNTEN;
		};
		typedef sdstop_t<base + 0x10> SDSTOP_;
		static SDSTOP_ SDSTOP;


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロックカウントレジスタ（ SDBLKCNT ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x14> SDBLKCNT_;
		static SDBLKCNT_ SDBLKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 10 （ SDRSP10 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x18> SDRSP10_;
		static SDRSP10_ SDRSP10;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 32 （ SDRSP32 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x20> SDRSP32_;
		static SDRSP32_ SDRSP32;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 54 （ SDRSP54 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x28> SDRSP54_;
		static SDRSP54_ SDRSP54;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 76 （ SDRSP76 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x30> SDRSP76_;
		static SDRSP76_ SDRSP76;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD ステータスレジスタ 1 （ SDSTS1 ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdsts1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RSPEND;

			bit_rw_t<io_, bitpos::B2>  ACEND;
			bit_rw_t<io_, bitpos::B3>  SDCDRM;
			bit_rw_t<io_, bitpos::B4>  SDCDIN;
			bit_ro_t<io_, bitpos::B5>  SDCDMON;

			bit_ro_t<io_, bitpos::B7>  SDWPMON;
			bit_rw_t<io_, bitpos::B8>  SDD3RM;
			bit_rw_t<io_, bitpos::B9>  SDD3IN;
			bit_ro_t<io_, bitpos::B10> SDD3MON;
		};
		typedef sdsts1_t<base + 0x38> SDSTS1_;
		static SDSTS1_ SDSTS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD ステータスレジスタ 2 （ SDSTS2 ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdsts2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMDE;
			bit_rw_t<io_, bitpos::B1>  CRCE;
			bit_rw_t<io_, bitpos::B2>  ENDE;
			bit_rw_t<io_, bitpos::B3>  DTO;
			bit_rw_t<io_, bitpos::B4>  ILW;
			bit_rw_t<io_, bitpos::B5>  ILR;
			bit_rw_t<io_, bitpos::B6>  RSPTO;
			bit_ro_t<io_, bitpos::B7>  SDD0MON;
			bit_rw_t<io_, bitpos::B8>  BRE;
			bit_rw_t<io_, bitpos::B9>  BWE;

			bit_ro_t<io_, bitpos::B13> SDCLKCREN;
			bit_ro_t<io_, bitpos::B14> CBSY;
			bit_rw_t<io_, bitpos::B15> ILA;
		};
		typedef sdsts2_t<base + 0x3C> SDSTS2_;
		static SDSTS2_ SDSTS2;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD 割り込みマスクレジスタ 1 （ SDIMSK1 ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdimsk1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RSPENDM;

			bit_rw_t<io_, bitpos::B2>  ACENDM;
			bit_rw_t<io_, bitpos::B3>  SDCDRMM;
			bit_rw_t<io_, bitpos::B4>  SDCDINM;

			bit_rw_t<io_, bitpos::B8>  SDD3RMM;
			bit_rw_t<io_, bitpos::B9>  SDD3INM;
		};
		typedef sdimsk1_t<base + 0x40> SDIMSK1_;
		static SDIMSK1_ SDIMSK1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD 割り込みマスクレジスタ 2 （ SDIMSK2 ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdimsk2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMDEM;
			bit_rw_t<io_, bitpos::B1>  CRCEM;
			bit_rw_t<io_, bitpos::B2>  ENDEM;
			bit_rw_t<io_, bitpos::B3>  DTTOM;
			bit_rw_t<io_, bitpos::B4>  ILWM;
			bit_rw_t<io_, bitpos::B5>  ILRM;
			bit_rw_t<io_, bitpos::B6>  RSPTOM;

			bit_rw_t<io_, bitpos::B8>  BREM;
			bit_rw_t<io_, bitpos::B9>  BWEM;

			bit_rw_t<io_, bitpos::B15> ILAM;
		};
		typedef sdimsk2_t<base + 0x44> SDIMSK2_;
		static SDIMSK2_ SDIMSK2;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI クロックコントロールレジスタ（ SDCLKCR ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdclkcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  CLKSEL;
			bit_rw_t <io_, bitpos::B8>     CLKEN;
			bit_rw_t <io_, bitpos::B9>     CLKCTRLEN;
		};
		typedef sdclkcr_t<base + 0x48> SDCLKCR_;
		static SDCLKCR_ SDCLKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  転送データサイズレジスタ（ SDSIZE ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdsize_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  LEN;
		};
		typedef sdsize_t<base + 0x4C> SDSIZE_;
		static SDSIZE_ SDSIZE;


		//-----------------------------------------------------------------//
		/*!
			@brief  カードアクセスオプションレジスタ（ SDOPT ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdopt_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CTOP;
			bits_rw_t<io_, bitpos::B4, 4>  TOP;

			bit_rw_t <io_, bitpos::B15>    WIDTH;
		};
		typedef sdopt_t<base + 0x50> SDOPT_;
		static SDOPT_ SDOPT;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD エラーステータスレジスタ 1 （ SDERSTS1 ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdersts1_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>      CMDE0;
			bit_ro_t <io_, bitpos::B1>      CMDE1;
			bit_ro_t <io_, bitpos::B2>      RSPLENE0;
			bit_ro_t <io_, bitpos::B3>      RSPLENE1;
			bit_ro_t <io_, bitpos::B4>      RDLENE;
			bit_ro_t <io_, bitpos::B5>      CRCLENE;

			bit_ro_t <io_, bitpos::B8>      RSPCRCE0;
			bit_ro_t <io_, bitpos::B9>      RSPCRCE1;
			bit_ro_t <io_, bitpos::B10>     RDCRCE;
			bit_ro_t <io_, bitpos::B11>     CRCTKE;
			bits_ro_t<io_, bitpos::B12, 3>  CRCTK;
		};
		typedef sdersts1_t<base + 0x58> SDERSTS1_;
		static SDERSTS1_ SDERSTS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD エラーステータスレジスタ 2 （ SDERSTS2 ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdersts2_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  RSPTO0;
			bit_ro_t<io_, bitpos::B1>  RSPTO1;
			bit_ro_t<io_, bitpos::B2>  BSYTO0;
			bit_ro_t<io_, bitpos::B3>  BSYTO1;
			bit_ro_t<io_, bitpos::B4>  RDTO;
			bit_ro_t<io_, bitpos::B5>  CRCTO;
			bit_ro_t<io_, bitpos::B6>  CRCBSYTO;
		};
		typedef sdersts2_t<base + 0x5C> SDERSTS2_;
		static SDERSTS2_ SDERSTS2;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD バッファレジスタ（ SDBUFR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x60> SDBUFR_;
		static SDBUFR_ SDBUFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDIO モードコントロールレジスタ（ SDIOMD ）
		*/
		//-----------------------------------------------------------------//
		struct sdiomd_t : public rw32_t<base + 0x68> {
			typedef rw32_t<base + 0x68> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  INTEN;

			bit_rw_t<io_, bitpos::B2>  RWREQ;

			bit_rw_t<io_, bitpos::B8>  IOABT;
			bit_rw_t<io_, bitpos::B9>  C52PUB;
		};
		typedef sdiomd_t SDIOMD_;
		static SDIOMD_ SDIOMD;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDIO ステータスレジスタ（ SDIOSTS ）
		*/
		//-----------------------------------------------------------------//
		struct sdiosts_t : public rw32_t<base + 0x6C> {
			typedef rw32_t<base + 0x6C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  IOIRQ;

			bit_rw_t<io_, bitpos::B14> EXPUB52;
			bit_rw_t<io_, bitpos::B15> EXWT;
		};
		typedef sdiosts_t SDIOSTS_;
		static SDIOSTS_ SDIOSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDIO 割り込みマスクレジスタ（ SDIOIMSK ）
		*/
		//-----------------------------------------------------------------//
		struct sdioimsk_t : public rw32_t<base + 0x70> {
			typedef rw32_t<base + 0x70> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  IOIRQM;

			bit_rw_t<io_, bitpos::B14> EXPUB52M;
			bit_rw_t<io_, bitpos::B15> EXWTM;
		};
		typedef sdioimsk_t SDIOIMSK_;
		static SDIOIMSK_ SDIOIMSK;


		//-----------------------------------------------------------------//
		/*!
			@brief  DMA 転送許可レジスタ（ SDDMAEN ）
		*/
		//-----------------------------------------------------------------//
		struct sddmaen_t : public rw32_t<base + 0x1B0> {
			typedef rw32_t<base + 0x1B0> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  DMAEN;
		};
		typedef sddmaen_t SDDMAEN_;
		static SDDMAEN_ SDDMAEN;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI ソフトウェアリセットレジスタ（ SDRST ）
		*/
		//-----------------------------------------------------------------//
		struct sdrst_t : public rw32_t<base + 0x1C0> {
			typedef rw32_t<base + 0x1C0> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SDRST;
		};
		typedef sdrst_t SDRST_;
		static SDRST_ SDRST;


		//-----------------------------------------------------------------//
		/*!
			@brief  バージョンレジスタ（ SDVER ）
		*/
		//-----------------------------------------------------------------//
		struct sdver_t : public ro32_t<base + 0x1C4> {
			typedef ro32_t<base + 0x1C4> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>  IP1;
			bits_ro_t<io_, bitpos::B8, 4>  IP2;

			bit_ro_t <io_, bitpos::B14>    CLKRAT;
			bit_ro_t <io_, bitpos::B15>    CPRM;
		};
		typedef sdver_t SDVER_;
		static SDVER_ SDVER;


		//-----------------------------------------------------------------//
		/*!
			@brief  スワップコントロールレジスタ（ SDSWAP ）
		*/
		//-----------------------------------------------------------------//
		struct sdswap_t : public rw32_t<base + 0x1E0> {
			typedef rw32_t<base + 0x1E0> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  BWSWP;
			bit_rw_t<io_, bitpos::B7>  BRSWP;
		};
		typedef sdswap_t SDSWAP_;
		static SDSWAP_ SDSWAP;
	};
	typedef sdhi_t<0x0008AC00, peripheral::SDHI,
		ICU::VECTOR_BL1::CDETI, ICU::VECTOR_BL1::CACI, ICU::VECTOR_BL1::SDACI,
		ICU::VECTOR::SBFAI> SDHI;

	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDCMD_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDCMD;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDARG_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDARG;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTOP_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTOP;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDBLKCNT_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDBLKCNT;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP10_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP10;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP32_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP32;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP54_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP54;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP76_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP76;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTS1_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTS1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTS2_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTS2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIMSK1_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIMSK1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIMSK2_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIMSK2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDCLKCR_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDCLKCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSIZE_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSIZE;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDOPT_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDOPT;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDERSTS1_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDERSTS1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDERSTS2_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDERSTS2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDBUFR_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDBUFR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOMD_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOMD;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOSTS_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOIMSK_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOIMSK;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDDMAEN_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDDMAEN;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRST_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRST;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDVER_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDVER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai>
	typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSWAP_
	sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSWAP;
}
