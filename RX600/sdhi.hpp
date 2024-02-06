#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・SDHI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDHI 定義基底クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sdhi_base_t {

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
		static inline sdcmd_t<base + 0x00> SDCMD;


		//-----------------------------------------------------------------//
		/*!
			@brief  アーギュメントレジスタ（ SDARG ）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x08> SDARG;


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
		static inline sdstop_t<base + 0x10> SDSTOP;


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロックカウントレジスタ（ SDBLKCNT ）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x14> SDBLKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 10 （ SDRSP10 ）
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<base + 0x18> SDRSP10;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 32 （ SDRSP32 ）
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<base + 0x20> SDRSP32;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 54 （ SDRSP54 ）
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<base + 0x28> SDRSP54;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 76 （ SDRSP76 ）
		*/
		//-----------------------------------------------------------------//
		static inline ro32_t<base + 0x30> SDRSP76;


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
		static inline sdsts1_t<base + 0x38> SDSTS1;


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
		static inline sdsts2_t<base + 0x3C> SDSTS2;


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
		static inline sdimsk1_t<base + 0x40> SDIMSK1;


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
		static inline sdimsk2_t<base + 0x44> SDIMSK2;


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
		static inline sdclkcr_t<base + 0x48> SDCLKCR;


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
		static inline sdsize_t<base + 0x4C> SDSIZE;


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
		static inline sdopt_t<base + 0x50> SDOPT;


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
		static inline sdersts1_t<base + 0x58> SDERSTS1;


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
		static inline sdersts2_t<base + 0x5C> SDERSTS2;


		//-----------------------------------------------------------------//
		/*!
			@brief  SD バッファレジスタ（ SDBUFR ）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x60> SDBUFR;


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
		static inline sdiomd_t SDIOMD;


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
		static inline sdiosts_t SDIOSTS;


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
		static inline sdioimsk_t SDIOIMSK;


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
		static inline sddmaen_t SDDMAEN;


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
		static inline sdrst_t SDRST;


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
		static inline sdver_t SDVER;


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
		static inline sdswap_t SDSWAP;
	};

#if defined(SIG_RX231)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDHI 通常割り込み・クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sdhi_t : public sdhi_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::SDHI;	///< ペリフェラル型
		static constexpr auto CDET_VEC   = ICU::VECTOR::CDETI;	///< CDET 割り込みベクター
		static constexpr auto CAC_VEC    = ICU::VECTOR::CACI;	///< CAC 割り込みベクター
		static constexpr auto SDAC_VEC   = ICU::VECTOR::SDACI;	///< SDAC 割り込みベクター
		static constexpr auto SBFA_VEC   = ICU::VECTOR::SBFAI;	///< SBFA 割り込みベクター
	};
#else
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDHI グループ割り込み・クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sdhi_t : public sdhi_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::SDHI;		///< ペリフェラル型
		static constexpr auto CDET_VEC   = ICU::GROUPBL1::CDETI;	///< CDET 割り込みベクター
		static constexpr auto CAC_VEC    = ICU::GROUPBL1::CACI;		///< CAC 割り込みベクター
		static constexpr auto SDAC_VEC   = ICU::GROUPBL1::SDACI;	///< SDAC 割り込みベクター
		static constexpr auto SBFA_VEC   = ICU::VECTOR::SBFAI;		///< SBFA 割り込みベクター
	};
#endif

	typedef sdhi_t<0x0008'AC00> SDHI;
}
