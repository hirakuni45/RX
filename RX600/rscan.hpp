#pragma once
//=========================================================================//
/*!	@file
	@brief	RX231/RX24T グループ・RSCAN 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RSCAN モジュール（RSCAN）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct rscan_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief	ビットコンフィギュレーションレジスタ L (CFGL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfgl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  BRP;
		};
		typedef cfgl_t<base + 0x00>  CFGL_;
		static CFGL_ CFGL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ビットコンフィギュレーションレジスタ H (CFGH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfgh_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  TSEG1;
			bits_rw_t<io_, bitpos::B4, 4>  TSEG2;

			bits_rw_t<io_, bitpos::B8, 2>  SJW;
		};
		typedef cfgh_t<base + 0x02>  CFGH_;
		static CFGH_ CFGH;


		//-----------------------------------------------------------------//
		/*!
			@brief	制御レジスタ L (CTRL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctrl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>	CHMDC;
			bit_rw_t <io_, bitpos::B2>		CSLPR;
			bit_rw_t <io_, bitpos::B3>		RTBO;

			bit_rw_t <io_, bitpos::B8>		BEIE;
			bit_rw_t <io_, bitpos::B9>		EWIE;
			bit_rw_t <io_, bitpos::B10>		EPIE;
			bit_rw_t <io_, bitpos::B11>		BOEIE;
			bit_rw_t <io_, bitpos::B12>		BORIE;
			bit_rw_t <io_, bitpos::B13>		OLIE;
			bit_rw_t <io_, bitpos::B14>		BLIE;
			bit_rw_t <io_, bitpos::B15>		ALIE;
		};
		typedef ctrl_t<base + 0x04>  CTRL_;
		static CTRL_ CTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	制御レジスタ H (CTRH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctrh_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		TAIE;

			bits_rw_t<io_, bitpos::B5, 2>	BOM;
			bit_rw_t <io_, bitpos::B7>		ERRD;
			bit_rw_t <io_, bitpos::B8>		CTME;
			bits_rw_t<io_, bitpos::B9, 2>	CTMS;
		};
		typedef ctrh_t<base + 0x06>  CTRH_;
		static CTRH_ CTRH;


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータスレジスタ L (STSL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct stsl_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>		CRSTSTS;
			bit_ro_t <io_, bitpos::B1>		CHLTSTS;
			bit_ro_t <io_, bitpos::B2>		CSLPSTS;
			bit_ro_t <io_, bitpos::B3>		EPSTS;
			bit_ro_t <io_, bitpos::B4>		BOSTS;
			bit_ro_t <io_, bitpos::B5>		TRMSTS;
			bit_ro_t <io_, bitpos::B6>		RECSTS;
			bit_ro_t <io_, bitpos::B7>		COMSTS;
		};
		typedef stsl_t<base + 0x08>  STSL_;
		static STSL_ STSL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータスレジスタ H (STSH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct stsh_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8>	REC;
			bits_ro_t<io_, bitpos::B8, 8>	TEC;
		};
		typedef stsh_t<base + 0x0A>  STSH_;
		static STSH_ STSH;


		//-----------------------------------------------------------------//
		/*!
			@brief	エラーフラグレジスタ L (ERFLL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct erfll_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		BEF;
			bit_rw_t <io_, bitpos::B1>		EWF;
			bit_rw_t <io_, bitpos::B2>		EPF;
			bit_rw_t <io_, bitpos::B3>		BOEF;
			bit_rw_t <io_, bitpos::B4>		BORF;
			bit_rw_t <io_, bitpos::B5>		OVLF;
			bit_rw_t <io_, bitpos::B6>		BLF;
			bit_rw_t <io_, bitpos::B7>		ALF;
			bit_rw_t <io_, bitpos::B8>		SERR;
			bit_rw_t <io_, bitpos::B9>		FERR;
			bit_rw_t <io_, bitpos::B10>		AERR;
			bit_rw_t <io_, bitpos::B11>		CERR;
			bit_rw_t <io_, bitpos::B12>		B1ERR;
			bit_rw_t <io_, bitpos::B13>		B0ERR;
			bit_rw_t <io_, bitpos::B14>		ADERR;
		};
		typedef erfll_t<base + 0x0C>  ERFLL_;
		static ERFLL_ ERFLL;


		//-----------------------------------------------------------------//
		/*!
			@brief	エラーフラグレジスタ H (ERFLH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct erflh_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 15>	CRCREG;
		};
		typedef erflh_t<base + 0x0E>  ERFLH_;
		static ERFLH_ ERFLH;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバル設定レジスタ L (GCFGL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gcfgl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		TPRI;
			bit_rw_t <io_, bitpos::B1>		DCE;
			bit_rw_t <io_, bitpos::B2>		DRE;
			bit_rw_t <io_, bitpos::B3>		MIME;
			bit_rw_t <io_, bitpos::B4>		DCS;

			bits_rw_t<io_, bitpos::B8, 4>	TSP;
			bit_rw_t <io_, bitpos::B12>		TSSS;
		};
		typedef gcfgl_t<base + 0x22>  GCFGL_;
		static GCFGL_ GCFGL;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバル設定レジスタ H (GCFGH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gcfgh_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>	ITRCP;
		};
		typedef gcfgh_t<base + 0x24>  GCFGH_;
		static GCFGH_ GCFGH;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバル制御レジスタ L (GCTRL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gctrl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>	GMDC;
			bit_rw_t <io_, bitpos::B2>		GSLPR;

			bit_rw_t <io_, bitpos::B8>		DEIE;
			bit_rw_t <io_, bitpos::B9>		MEIE;
			bit_rw_t <io_, bitpos::B10>		THLEIE;
		};
		typedef gctrl_t<base + 0x26>  GCTRL_;
		static GCTRL_ GCTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバル制御レジスタ H (GCTRH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gctrh_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		TSRST;
		};
		typedef gctrh_t<base + 0x28>  GCTRH_;
		static GCTRH_ GCTRH;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバルステータスレジスタ (GSTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gsts_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>		GRSTSTS;
			bit_ro_t <io_, bitpos::B1>		GHLTSTS;
			bit_ro_t <io_, bitpos::B2>		GSLPSTS;
			bit_ro_t <io_, bitpos::B3>		GRAMINT;
		};
		typedef gsts_t<base + 0x2A>  GSTS_;
		static GSTS_ GSTS;







	};
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::CFGL_ rscan_t<base, per>::CFGL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::CFGH_ rscan_t<base, per>::CFGH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::CTRL_ rscan_t<base, per>::CTRL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::CTRH_ rscan_t<base, per>::CTRH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::STSL_ rscan_t<base, per>::STSL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::STSH_ rscan_t<base, per>::STSH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::ERFLL_ rscan_t<base, per>::ERFLL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::ERFLH_ rscan_t<base, per>::ERFLH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GCFGL_ rscan_t<base, per>::GCFGL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GCFGH_ rscan_t<base, per>::GCFGH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GCTRL_ rscan_t<base, per>::GCTRL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GCTRH_ rscan_t<base, per>::GCTRH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GSTS_ rscan_t<base, per>::GSTS;


	typedef rscan_t<0x000A'8300, peripheral::RSCAN>  RSCAN;
}
