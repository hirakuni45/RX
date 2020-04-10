#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SDHI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2019 Kunihito Hiramatsu @n
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

		//-----------------------------------------------------------------//
		/*!
			@brief  コマンドレジスタ（ SDCMD ）
		*/
		//-----------------------------------------------------------------//
		struct sdcmd_t : public rw32_t<base + 0x00> {
			typedef rw32_t<base + 0x00> io_;
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
		static sdcmd_t SDCMD;


		//-----------------------------------------------------------------//
		/*!
			@brief  アーギュメントレジスタ（ SDARG ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x08> sdarg_t;
		static sdarg_t SDARG;


		//-----------------------------------------------------------------//
		/*!
			@brief  データストップレジスタ（ SDSTOP ）
		*/
		//-----------------------------------------------------------------//
		struct sdstop_t : public rw32_t<base + 0x10> {
			typedef rw32_t<base + 0x10> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  STP;
			bit_rw_t<io_, bitpos::B8>  SDBLKCNTEN;
		};
		static sdstop_t SDSTOP;


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロックカウントレジスタ（ SDBLKCNT ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x14> sdblkcnt_t;
		static sdblkcnt_t SDBLKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 10 （ SDRSP10 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x18> sdrsp10_t;
		static sdrsp10_t SDRSP10;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 32 （ SDRSP32 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x20> sdrsp32_t;
		static sdrsp32_t SDRSP32;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 54 （ SDRSP54 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x28> sdrsp54_t;
		static sdrsp54_t SDRSP54;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 76 （ SDRSP76 ）
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x30> sdrsp76_t;
		static sdrsp76_t SDRSP76;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD ステータスレジスタ 1 （ SDSTS1 ）
		*/
		//-----------------------------------------------------------------//
		struct sdsts1_t : public rw32_t<base + 0x38> {
			typedef rw32_t<base + 0x38> io_;
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
		static sdsts1_t SDSTS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD ステータスレジスタ 2 （ SDSTS2 ）
		*/
		//-----------------------------------------------------------------//
		struct sdsts2_t : public rw32_t<base + 0x3C> {
			typedef rw32_t<base + 0x3C> io_;
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
		static sdsts2_t SDSTS2;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD 割り込みマスクレジスタ 1 （ SDIMSK1 ）
		*/
		//-----------------------------------------------------------------//
		struct sdimsk1_t : public rw32_t<base + 0x40> {
			typedef rw32_t<base + 0x40> io_;
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
		static sdimsk1_t SDIMSK1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD 割り込みマスクレジスタ 2 （ SDIMSK2 ）
		*/
		//-----------------------------------------------------------------//
		struct sdimsk2_t : public rw32_t<base + 0x44> {
			typedef rw32_t<base + 0x44> io_;
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
		static sdimsk2_t SDIMSK2;


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI クロックコントロールレジスタ（ SDCLKCR ）
		*/
		//-----------------------------------------------------------------//
		struct sdclkcr_t : public rw32_t<base + 0x48> {
			typedef rw32_t<base + 0x48> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  CLKSEL;
			bit_rw_t <io_, bitpos::B8>     CLKEN;
			bit_rw_t <io_, bitpos::B9>     CLKCTRLEN;
		};
		static sdclkcr_t SDCLKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  転送データサイズレジスタ（ SDSIZE ）
		*/
		//-----------------------------------------------------------------//
		struct sdsize_t : public rw32_t<base + 0x4C> {
			typedef rw32_t<base + 0x4C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  LEN;
		};
		static sdsize_t SDSIZE;


		//-----------------------------------------------------------------//
		/*!
			@brief  カードアクセスオプションレジスタ（ SDOPT ）
		*/
		//-----------------------------------------------------------------//
		struct sdopt_t : public rw32_t<base + 0x50> {
			typedef rw32_t<base + 0x50> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CTOP;
			bits_rw_t<io_, bitpos::B4, 4>  TOP;

			bit_rw_t <io_, bitpos::B15>    WIDTH;
		};
		static sdopt_t SDOPT;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD エラーステータスレジスタ 1 （ SDERSTS1 ）
		*/
		//-----------------------------------------------------------------//
		struct sdersts1_t : public ro32_t<base + 0x58> {
			typedef ro32_t<base + 0x58> io_;
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
		static sdersts1_t SDERSTS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD エラーステータスレジスタ 2 （ SDERSTS2 ）
		*/
		//-----------------------------------------------------------------//
		struct sdersts2_t : public ro32_t<base + 0x5C> {
			typedef ro32_t<base + 0x5C> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  RSPTO0;
			bit_ro_t<io_, bitpos::B1>  RSPTO1;
			bit_ro_t<io_, bitpos::B2>  BSYTO0;
			bit_ro_t<io_, bitpos::B3>  BSYTO1;
			bit_ro_t<io_, bitpos::B4>  RDTO;
			bit_ro_t<io_, bitpos::B5>  CRCTO;
			bit_ro_t<io_, bitpos::B6>  CRCBSYTO;
		};
		static sdersts2_t SDERSTS2;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD バッファレジスタ（ SDBUFR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x60> sdbufr_t;
		static sdbufr_t SDBUFR;


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
		static sdiomd_t SDIOMD;


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
		static sdiosts_t SDIOSTS;


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
		static sdioimsk_t SDIOIMSK;


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
		static sddmaen_t SDDMAEN;


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
		static sdrst_t SDRST;


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
		static sdver_t SDVER;


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
		static sdswap_t SDSWAP;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  カード検出割り込み・ベクタ
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static auto get_cdeti() { return cdeti; }


		//-----------------------------------------------------------------//
		/*!
			@brief  カードアクセス割り込み・ベクタ
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static auto get_caci() { return caci; }


		//-----------------------------------------------------------------//
		/*!
			@brief  SDIO アクセス割り込み・ベクタ
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static auto get_sdaci() { return sdaci; }


		//-----------------------------------------------------------------//
		/*!
			@brief  バッファアクセス割り込み・ベクタ
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static auto get_sbfai() { return sbfai; }
	};

	typedef sdhi_t<0x0008AC00, peripheral::SDHI,
				   ICU::VECTOR_BL1::CDETI, ICU::VECTOR_BL1::CACI, ICU::VECTOR_BL1::SDACI,
				   ICU::VECTOR::SBFAI> SDHI;

	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdcmd_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDCMD;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdarg_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDARG;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdstop_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTOP;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdblkcnt_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDBLKCNT;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdrsp10_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP10;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdrsp32_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP32;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdrsp54_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP54;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdrsp76_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRSP76;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdsts1_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTS1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdsts2_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSTS2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdimsk1_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIMSK1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdimsk2_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIMSK2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdclkcr_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDCLKCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdsize_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSIZE;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdopt_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDOPT;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdersts1_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDERSTS1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdersts2_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDERSTS2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdbufr_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDBUFR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdiomd_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOMD;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdiosts_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdioimsk_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDIOIMSK;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sddmaen_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDDMAEN;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdrst_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDRST;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdver_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDVER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cdeti, ICU::VECTOR_BL1 caci, ICU::VECTOR_BL1 sdaci, ICU::VECTOR sbfai> typename sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::sdswap_t sdhi_t<base, per, cdeti, caci, sdaci, sbfai>::SDSWAP;
}
