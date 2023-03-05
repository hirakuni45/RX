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
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>		GRSTSTS;
			bit_ro_t <in_, bitpos::B1>		GHLTSTS;
			bit_ro_t <in_, bitpos::B2>		GSLPSTS;
			bit_ro_t <in_, bitpos::B3>		GRAMINT;
		};
		typedef gsts_t<base + 0x2A>  GSTS_;
		static GSTS_ GSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバルエラーフラグレジスタ (GERFLL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gerfll_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator ();

			bit_rw_t <io_, bitpos::B0>		DEF;
			bit_ro_t <io_, bitpos::B1>		MES;
			bit_ro_t <io_, bitpos::B2>		THLES;
		};
		typedef gerfll_t<base + 0x2C>  GERFLL_;
		static GERFLL_ GERFLL;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバル送信割り込みステータスレジスタ (GTINTSTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtintsts_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>		TSIF0;
			bit_ro_t <in_, bitpos::B1>		TAIF0;
			bit_ro_t <in_, bitpos::B2>		CFTIF0;
			bit_ro_t <in_, bitpos::B3>		THIF0;
		};
		typedef gtintsts_t<base + 0x88>  GTINTSTS_;
		static GTINTSTS_ GTINTSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイムスタンプレジスタ (GTSC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtsc_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bits_ro_t <in_, bitpos::B0, 16> TS;
		};
		typedef gtsc_t<base + 0x2E>  GTSC_;
		static GTSC_ GTSC;


		//-----------------------------------------------------------------//
		/*!
			@brief	受信ルール数設定レジスタ (GAFLCFG)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gaflcfg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>	TSRST;
		};
		typedef gaflcfg_t<base + 0x30>  GAFLCFG_;
		static GAFLCFG_ GAFLCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jAL (GAFLIDLj) (j = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gaflidl_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 12; }
			}

			bits_rw_t<io_, bitpos::B0, 16>	GAFLID;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef gaflidl_t<base + 0xA0> GAFLIDL_;
		static GAFLIDL_ GAFLIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jAH (GAFLIDHj) (j = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gaflidh_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 12; }
			}

			bits_rw_t<io_, bitpos::B0, 13>	GAFLID;
			bit_rw_t <io_, bitpos::B13>		GAFLLB;
			bit_rw_t <io_, bitpos::B14>		GAFLRTR;
			bit_rw_t <io_, bitpos::B15>		GAFLIDE;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef gaflidh_t<base + 0xA2> GAFLIDH_;
		static GAFLIDH_ GAFLIDH;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jBL (GAFLMLj) (j = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gaflml_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 12; }
			}

			bits_rw_t<io_, bitpos::B0, 16>	GAFLIDM;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef gaflml_t<base + 0xA4> GAFLML_;
		static GAFLML_ GAFLML;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jBH (GAFLMHj) (j = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gaflmh_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 12; }
			}

			bits_rw_t<io_, bitpos::B0, 13>	GAFLIDM;

			bit_rw_t <io_, bitpos::B14>		GAFLRTRM;
			bit_rw_t <io_, bitpos::B15>		GAFLIDEM;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef gaflmh_t<base + 0xA6> GAFLMH_;
		static GAFLMH_ GAFLMH;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jCL (GAFLPLj) (j = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gaflpl_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 12; }
			}

			bit_rw_t <io_, bitpos::B0>		GAFLFDP0;
			bit_rw_t <io_, bitpos::B1>		GAFLFDP1;

			bit_rw_t <io_, bitpos::B4>		GAFLFDP4;

			bits_rw_t<io_, bitpos::B8, 7>	GAFLRMDP;
			bit_rw_t <io_, bitpos::B15>		GAFLRMV;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef gaflpl_t<base + 0xA8> GAFLPL_;
		static GAFLPL_ GAFLPL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jCH (GAFLPHj) (j = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gaflph_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 12; }
			}

			bits_rw_t<io_, bitpos::B0, 12>	GAFLPTR;
			bits_rw_t<io_, bitpos::B12, 4>	GAFLDLC;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef gaflph_t<base + 0xAA> GAFLPH_;
		static GAFLPH_ GAFLPH;


		//-----------------------------------------------------------------//
		/*!
			@brief	受信バッファ数設定レジスタ (RMNB)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmnb_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>	NRXMB;
		};
		typedef rmnb_t<base + 0x32>  RMNB_;
		static RMNB_ RMNB;


		//-----------------------------------------------------------------//
		/*!
			@brief	受信バッファ受信完了フラグレジスタ (RMND0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmnd0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>	RMNS;
		};
		typedef rmnd0_t<base + 0x34>  RMND0_;
		static RMND0_ RMND0;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nAL (RMIDLn) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmidl_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 16>	RMID;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmidl_t<base + 0xA0> RMIDL_;
		static RMIDL_ RMIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nAH (RMIDHn) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmidh_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 13>	RMID;

			bit_rw_t <io_, bitpos::B14>		RMRTR;
			bit_rw_t <io_, bitpos::B15>		RMIDE;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmidh_t<base + 0xA2> RMIDH_;
		static RMIDH_ RMIDH;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nBL (RMTSn) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmts_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 16>	RMTS;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmts_t<base + 0xA4> RMTS_;
		static RMTS_ RMTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nBH (RMPTRn) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmptr_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 12>	RMPTR;
			bits_rw_t<io_, bitpos::B12, 4>	RMDLC;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmptr_t<base + 0xA6> RMPTR_;
		static RMPTR_ RMPTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nCL (RMDF0n) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmdf0_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 8>	RMDB0;
			bits_rw_t<io_, bitpos::B8, 8>	RMDB1;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmdf0_t<base + 0xA8> RMDF0_;
		static RMDF0_ RMDF0;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nCH (RMDF1n) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmdf1_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 8>	RMDB2;
			bits_rw_t<io_, bitpos::B8, 8>	RMDB3;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmdf1_t<base + 0xAA> RMDF1_;
		static RMDF1_ RMDF1;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nDL (RMDF2n) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmdf2_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 8>	RMDB4;
			bits_rw_t<io_, bitpos::B8, 8>	RMDB5;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmdf2_t<base + 0xAC> RMDF2_;
		static RMDF2_ RMDF2;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nDH (RMDF3n) (n = 0 ～ 15)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmdf3_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 16) { io_::index = j * 16; }
			}

			bits_rw_t<io_, bitpos::B0, 8>	RMDB6;
			bits_rw_t<io_, bitpos::B8, 8>	RMDB7;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rmdf3_t<base + 0xAE> RMDF3_;
		static RMDF3_ RMDF3;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO 制御レジスタ m (RFCCm) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfcc_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 2; }
			}

			bit_rw_t <io_, bitpos::B0>		RFE;
			bit_rw_t <io_, bitpos::B1>		RFIE;

			bits_rw_t<io_, bitpos::B8, 3>	RFDC;

			bit_rw_t <io_, bitpos::B12>		RFIM;
			bits_rw_t<io_, bitpos::B13, 3>	RFIGCV;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rfcc_t<base + 0x38> RFCC_;
		static RFCC_ RFCC;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ステータスレジスタ m (RFSTSm) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfsts_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 2; }
			}

			bit_ro_t <io_, bitpos::B0>		RFEMP;
			bit_ro_t <io_, bitpos::B1>		RFFLL;
			bit_rw_t <io_, bitpos::B2>		RFMLT;
			bit_rw_t <io_, bitpos::B3>		RFIF;

			bits_ro_t<io_, bitpos::B8, 6>	RFMC;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rfsts_t<base + 0x40> RFSTS_;
		static RFSTS_ RFSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ポインタ制御レジスタ m (RFPCTRm) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfpctr_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 2; }
			}

			bits_rw_t<io_, bitpos::B0, 8>	RFPC;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rfpctr_t<base + 0x48> RFPCTR_;
		static RFPCTR_ RFPCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mAL (RFIDLm) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfidl_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 16>	RFID;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rfidl_t<base + 0xA0> RFIDL_;
		static RFIDL_ RFIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mAH (RFIDHm) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfidh_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 13>	RFID;

			bit_ro_t <io_, bitpos::B14>		RFRTR;
			bit_ro_t <io_, bitpos::B15>		RFIDE;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef rfidh_t<base + 0xA2> RFIDH_;
		static RFIDH_ RFIDH;







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
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GERFLL_ rscan_t<base, per>::GERFLL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GTINTSTS_ rscan_t<base, per>::GTINTSTS;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GTSC_ rscan_t<base, per>::GTSC;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GAFLCFG_ rscan_t<base, per>::GAFLCFG;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GAFLIDL_ rscan_t<base, per>::GAFLIDL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GAFLIDH_ rscan_t<base, per>::GAFLIDH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GAFLML_ rscan_t<base, per>::GAFLML;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GAFLMH_ rscan_t<base, per>::GAFLMH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GAFLPL_ rscan_t<base, per>::GAFLPL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::GAFLPH_ rscan_t<base, per>::GAFLPH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMNB_ rscan_t<base, per>::RMNB;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMND0_ rscan_t<base, per>::RMND0;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMIDL_ rscan_t<base, per>::RMIDL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMIDH_ rscan_t<base, per>::RMIDH;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMTS_ rscan_t<base, per>::RMTS;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMPTR_ rscan_t<base, per>::RMPTR;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMDF0_ rscan_t<base, per>::RMDF0;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMDF1_ rscan_t<base, per>::RMDF1;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMDF2_ rscan_t<base, per>::RMDF2;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RMDF3_ rscan_t<base, per>::RMDF3;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RFCC_ rscan_t<base, per>::RFCC;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RFSTS_ rscan_t<base, per>::RFSTS;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RFPCTR_ rscan_t<base, per>::RFPCTR;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RFIDL_ rscan_t<base, per>::RFIDL;
	template <uint32_t base, peripheral per> typename rscan_t<base, per>::RFIDH_ rscan_t<base, per>::RFIDH;




	typedef rscan_t<0x000A'8300, peripheral::RSCAN>  RSCAN;
}
