#pragma once
//=========================================================================//
/*!	@file
	@brief	RSCAN Module / RSCAN モジュール @n
			RX140 @n
			RX231 @n
			RX24T/RX24U
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RSCAN base class
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct rscan_base_t {

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
		static inline cfgl_t<base + 0x00>  CFGL;


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
		static inline cfgh_t<base + 0x02>  CFGH;


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
		static inline ctrl_t<base + 0x04>  CTRL;


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
		static inline ctrh_t<base + 0x06>  CTRH;


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
		static inline stsl_t<base + 0x08>  STSL;


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
		static inline stsh_t<base + 0x0A>  STSH;


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
		static inline erfll_t<base + 0x0C>  ERFLL;


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
		static inline erflh_t<base + 0x0E>  ERFLH;


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
		static inline gcfgl_t<base + 0x22>  GCFGL;


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
		static inline gcfgh_t<base + 0x24>  GCFGH;


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
		static inline gctrl_t<base + 0x26>  GCTRL;


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
		static inline gctrh_t<base + 0x28>  GCTRH;


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
		static inline gsts_t<base + 0x2A>  GSTS;


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
		static inline gerfll_t<base + 0x2C>  GERFLL;


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
		static inline gtintsts_t<base + 0x88>  GTINTSTS;


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
		static inline gtsc_t<base + 0x2E>  GTSC;


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
		static inline gaflcfg_t<base + 0x30>  GAFLCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jAL (GAFLIDL[j]) (j = 0 ～ 15)
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
		static inline gaflidl_t<base + 0xA0> GAFLIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jAH (GAFLIDH[j]) (j = 0 ～ 15)
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
		static inline gaflidh_t<base + 0xA2> GAFLIDH;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jBL (GAFLML[j]) (j = 0 ～ 15)
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
		static inline gaflml_t<base + 0xA4> GAFLML;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jBH (GAFLMH[j]) (j = 0 ～ 15)
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
		static inline gaflmh_t<base + 0xA6> GAFLMH;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jCL (GAFLPL[j]) (j = 0 ～ 15)
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
		static inline gaflpl_t<base + 0xA8> GAFLPL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ルール登録レジスタ jCH (GAFLPH[j]) (j = 0 ～ 15)
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
		static inline gaflph_t<base + 0xAA> GAFLPH;


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
		static inline rmnb_t<base + 0x32>  RMNB;


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
		static inline rmnd0_t<base + 0x34>  RMND0;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nAL (RMIDL[n]) (n = 0 ～ 15)
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
		static inline rmidl_t<base + 0xA0> RMIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nAH (RMIDH[n]) (n = 0 ～ 15)
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
		static inline rmidh_t<base + 0xA2> RMIDH;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nBL (RMTS[n]) (n = 0 ～ 15)
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
		static inline rmts_t<base + 0xA4> RMTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nBH (RMPTR[n]) (n = 0 ～ 15)
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
		static inline rmptr_t<base + 0xA6> RMPTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nCL (RMDF0[n]) (n = 0 ～ 15)
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
		static inline rmdf0_t<base + 0xA8> RMDF0;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nCH (RMDF1[n]) (n = 0 ～ 15)
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
		static inline rmdf1_t<base + 0xAA> RMDF1;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nDL (RMDF2[n]) (n = 0 ～ 15)
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
		static inline rmdf2_t<base + 0xAC> RMDF2;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファレジスタ nDH (RMDF3[n]) (n = 0 ～ 15)
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
		static inline rmdf3_t<base + 0xAE> RMDF3;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO 制御レジスタ m (RFCC[m]) (m = 0, 1)
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
		static inline rfcc_t<base + 0x38> RFCC;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ステータスレジスタ m (RFSTS[m]) (m = 0, 1)
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
		static inline rfsts_t<base + 0x40> RFSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ポインタ制御レジスタ m (RFPCTR[m]) (m = 0, 1)
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
		static inline rfpctr_t<base + 0x48> RFPCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mAL (RFIDL[m]) (m = 0, 1)
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
		static inline rfidl_t<base + 0x2A0> RFIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mAH (RFIDH[m]) (m = 0, 1)
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
		static inline rfidh_t<base + 0x2A2> RFIDH;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mBL (RFTS[m]) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfts_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 16>	RFTS;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rfts_t<base + 0x2A4> RFTS;
	

		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mBH (RFPTR[m]) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfptr_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 12>	RFPTR;
			bits_ro_t<io_, bitpos::B12, 4>	RFDLC;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rfptr_t<base + 0x2A6> RFPTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mCL (RFDF0[m]) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfdf0_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 8>	RFDB0;
			bits_ro_t<io_, bitpos::B8, 8>	RFDB1;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rfdf0_t<base + 0x2A8> RFDF0;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mCH (RFDF1[m]) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfdf1_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 8>	RFDB2;
			bits_ro_t<io_, bitpos::B8, 8>	RFDB3;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rfdf1_t<base + 0x2AA> RFDF1;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mDL (RFDF2[m]) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfdf2_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 8>	RFDB4;
			bits_ro_t<io_, bitpos::B8, 8>	RFDB5;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rfdf2_t<base + 0x2AC> RFDF2;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO アクセスレジスタ mDH (RFDF3[m]) (m = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfdf3_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) {
				if(j < 2) { io_::index = j * 0x10; }
			}

			bits_ro_t<io_, bitpos::B0, 8>	RFDB6;
			bits_ro_t<io_, bitpos::B8, 8>	RFDB7;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rfdf3_t<base + 0x2AE> RFDF3;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO 制御レジスタ 0L (CFCCL0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfccl0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		CFE;
			bit_rw_t <io_, bitpos::B1>		CFRXIE;
			bit_rw_t <io_, bitpos::B2>		CFTXIE;

			bits_rw_t<io_, bitpos::B8, 3>	CFDC;

			bit_rw_t <io_, bitpos::B12>		CFIM;
			bits_rw_t<io_, bitpos::B13, 3>	CFIGCV;
		};
		static inline cfccl0_t<base + 0x50>  CFCCL0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO 制御レジスタ 0H (CFCCH0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfcch0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>	CFM;
			bit_rw_t <io_, bitpos::B2>		CFITSS;
			bit_rw_t <io_, bitpos::B3>		CFITR;
			bits_rw_t<io_, bitpos::B4, 2>	CFTML;

			bits_rw_t<io_, bitpos::B8, 8>	CFITT;
		};
		static inline cfcch0_t<base + 0x52>  CFCCH0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO ステータスレジスタ 0 (CFSTS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfsts0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		CFEMP;
			bit_rw_t <io_, bitpos::B1>		CFFLL;
			bit_rw_t <io_, bitpos::B2>		CFMLT;
			bit_rw_t <io_, bitpos::B3>		CFRXIF;
			bit_rw_t <io_, bitpos::B4>		CFTXIF;

			bits_rw_t<io_, bitpos::B8, 6>	CFMC;
		};
		static inline cfsts0_t<base + 0x58>  CFSTS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO ポインタ制御レジスタ 0 (CFPCTR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfpctr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>	CFPC;
		};
		static inline cfpctr0_t<base + 0x5C>  CFPCTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0AL (CFIDL0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfidl0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>	CFID;
		};
		static inline cfidl0_t<base + 0x2E0>  CFIDL0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0AH (CFIDH0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfidh0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 13>	CFID;
			bit_rw_t <io_, bitpos::B13>		THLEN;
			bit_rw_t <io_, bitpos::B14>		CFRTR;
			bit_rw_t <io_, bitpos::B15>		CFIDE;
		};
		static inline cfidh0_t<base + 0x2E2>  CFIDH0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0BL (CFTS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfts0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>	CFTS;
		};
		static inline cfts0_t<base + 0x2E4>  CFTS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0BH (CFPTR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfptr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12>	CFPTR;
			bits_rw_t<io_, bitpos::B12, 4>	CFDLC;
		};
		static inline cfptr0_t<base + 0x2E6>  CFPTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0CL (CFDF00)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfdf00_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>	CFDB0;
			bits_rw_t<io_, bitpos::B8, 8>	CFDB1;
		};
		static inline cfdf00_t<base + 0x2E8>  CFDF00;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0CH (CFDF10)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfdf10_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>	CFDB2;
			bits_rw_t<io_, bitpos::B8, 8>	CFDB3;
		};
		static inline cfdf10_t<base + 0x2EA>  CFDF10;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0DL (CFDF20)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfdf20_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>	CFDB4;
			bits_rw_t<io_, bitpos::B8, 8>	CFDB5;
		};
		static inline cfdf20_t<base + 0x2EC>  CFDF20;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO アクセスレジスタ 0DH (CFDF30)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfdf30_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>	CFDB6;
			bits_rw_t<io_, bitpos::B8, 8>	CFDB7;
		};
		static inline cfdf30_t<base + 0x2EE>  CFDF30;


		//-----------------------------------------------------------------//
		/*!
			@brief	受信 FIFO メッセージロストステータスレジスタ (RFMSTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfmsts_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_rw_t <in_, bitpos::B0>		RF0MLT;
			bit_rw_t <in_, bitpos::B1>		RF1MLT;
		};
		static inline rfmsts_t<base + 0x60>  RFMSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO メッセージロストステータスレジスタ (CFMSTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfmsts_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_rw_t <in_, bitpos::B0>		CF0MLT;
		};
		static inline cfmsts_t<base + 0x61>  CFMSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	受信 FIFO 割り込みステータスレジスタ (RFISTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfists_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_rw_t <in_, bitpos::B0>		RF0IF;
			bit_rw_t <in_, bitpos::B1>		RF1IF;
		};
		static inline rfists_t<base + 0x62>  RFISTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	送受信 FIFO 受信割り込みステータスレジスタ (CFISTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfists_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_rw_t <in_, bitpos::B0>		CF0IF;
		};
		static inline cfists_t<base + 0x63>  CFISTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信バッファ制御レジスタ p (TMC[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmc_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j; }
			}

			bit_rw_t <io_, bitpos::B0>		TMTR;
			bit_rw_t <io_, bitpos::B1>		TMTAR;
			bit_rw_t <io_, bitpos::B2>		TMOM;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmc_t<base + 0x64> TMC;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファステータスレジスタ p (TMSTS[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmsts_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j; }
			}

			bit_rw_t <io_, bitpos::B0>		TMTSTS;
			bits_rw_t<io_, bitpos::B1, 2>	TMTRF;
			bit_rw_t <io_, bitpos::B3>		TMTRM;
			bit_rw_t <io_, bitpos::B4>		TMTARM;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmsts_t<base + 0x6C> TMSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファ送信要求ステータスレジスタ (TMTRSTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmtrsts_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>		TMTRSTS0;
			bit_ro_t <in_, bitpos::B1>		TMTRSTS1;
			bit_ro_t <in_, bitpos::B2>		TMTRSTS2;
			bit_ro_t <in_, bitpos::B3>		TMTRSTS3;
		};
		static inline tmtrsts_t<base + 0x74>  TMTRSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファ送信完了ステータスレジスタ (TMTCSTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmtcsts_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>		TMTCSTS0;
			bit_ro_t <in_, bitpos::B1>		TMTCSTS1;
			bit_ro_t <in_, bitpos::B2>		TMTCSTS2;
			bit_ro_t <in_, bitpos::B3>		TMTCSTS3;
		};
		static inline tmtcsts_t<base + 0x76>  TMTCSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファ送信アボートステータスレジスタ (TMTASTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmtasts_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>		TMTASTS0;
			bit_ro_t <in_, bitpos::B1>		TMTASTS1;
			bit_ro_t <in_, bitpos::B2>		TMTASTS2;
			bit_ro_t <in_, bitpos::B3>		TMTASTS3;
		};
		static inline tmtasts_t<base + 0x78>  TMTASTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファ割り込み許可レジスタ (TMIEC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmiec_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		TMIE0;
			bit_rw_t <io_, bitpos::B1>		TMIE1;
			bit_rw_t <io_, bitpos::B2>		TMIE2;
			bit_rw_t <io_, bitpos::B3>		TMIE3;
		};
		static inline tmiec_t<base + 0x7A>  TMIEC;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファレジスタ pAL (TMIDLp) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmidl_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j * 0x10; }
			}

			bits_rw_t<io_, bitpos::B0, 16>	TMID;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmidl_t<base + 0x300> TMIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファレジスタ pAH (TMIDH[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmidh_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j * 0x10; }
			}

			bits_rw_t<io_, bitpos::B0, 13>	TMID;
			bit_rw_t <io_, bitpos::B13>		THLEN;
			bit_rw_t <io_, bitpos::B14>		TMRTR;
			bit_rw_t <io_, bitpos::B15>		TMIDE;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmidh_t<base + 0x302> TMIDH;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファレジスタ pBH (TMPTR[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmptr_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j * 0x10; }
			}

			bits_rw_t<io_, bitpos::B0,  8>	TMPTR;
			bits_rw_t<io_, bitpos::B12, 4>	TMDLC;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmptr_t<base + 0x306> TMPTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファレジスタ pCL (TMDF0[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmdf0_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j * 0x10; }
			}

			bits_rw_t<io_, bitpos::B0,  8>	TMDB0;
			bits_rw_t<io_, bitpos::B8,  8>	TMDB1;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmdf0_t<base + 0x308> TMDF0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファレジスタ pCH (TMDF1[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmdf1_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j * 0x10; }
			}

			bits_rw_t<io_, bitpos::B0,  8>	TMDB2;
			bits_rw_t<io_, bitpos::B8,  8>	TMDB3;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmdf1_t<base + 0x30A> TMDF1;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファレジスタ pDL (TMDF2[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmdf2_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j * 0x10; }
			}

			bits_rw_t<io_, bitpos::B0,  8>	TMDB4;
			bits_rw_t<io_, bitpos::B8,  8>	TMDB5;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmdf2_t<base + 0x30C> TMDF2;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信バッファレジスタ pDH (TMDF3[p]) (p = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmdf3_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 4) { io_::index = j * 0x10; }
			}

			bits_rw_t<io_, bitpos::B0,  8>	TMDB6;
			bits_rw_t<io_, bitpos::B8,  8>	TMDB7;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmdf3_t<base + 0x30E> TMDF3;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信履歴バッファ制御レジスタ (THLCC0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thlcc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		THLE;

			bit_rw_t <io_, bitpos::B8>		THLIE;
			bit_rw_t <io_, bitpos::B9>		THLIM;
			bit_rw_t <io_, bitpos::B10>		THLDTE;
		};
		static inline thlcc0_t<base + 0x7C>  THLCC0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信履歴バッファステータスレジスタ (THLSTS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thlsts0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>		THLEMP;
			bit_ro_t <in_, bitpos::B1>		THLFLL;
			bit_rw_t <io_, bitpos::B2>		THLELT;
			bit_rw_t <io_, bitpos::B3>		THLIF;

			bits_ro_t<in_, bitpos::B8, 4>	THLMC;
		};
		static inline thlsts0_t<base + 0x80>  THLSTS0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信履歴バッファアクセスレジスタ (THLACC0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thlacc0_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 2>	BT;
			bits_ro_t<in_, bitpos::B3, 2>	BN;

			bits_ro_t<in_, bitpos::B8, 8>	TID;
		};
		static inline thlacc0_t<base + 0x380>  THLACC0;


		//-----------------------------------------------------------------//
		/*!
			@brief	送信履歴バッファポインタ制御レジスタ (THLPCTR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thlpctr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> o_;
			using o_::operator =;

			bits_rw_t<o_, bitpos::B0, 8>	THLPC;
		};
		static inline thlpctr0_t<base + 0x384>  THLPCTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバル RAM ウィンドウ制御レジスタ (GRWCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct grwcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		RPAGE;
		};
		static inline grwcr_t<base + 0x8A>  GRWCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバルテスト設定レジスタ (GTSTCFG)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtstcfg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 3>	RTMPS;
		};
		static inline gtstcfg_t<base + 0x8C>  GTSTCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバルテスト制御レジスタ (GTSTCTRL)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtstctrl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B2>		RTIME;
		};
		static inline gtstctrl_t<base + 0x8E>  GTSTCTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	グローバルテストプロテクト解除レジスタ (GLOCKK)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct glockk_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>	LOCK;
		};
		static inline glockk_t<base + 0x94>  GLOCKK;


		//-----------------------------------------------------------------//
		/*!
			@brief	RAM テストレジスタ r (RPGACCr) (r = 0 ～ 127)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rpgacc_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) {
				if(j < 128) { io_::index = j * 2; }
			}

			bits_rw_t<io_, bitpos::B0, 16>	RDTA;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rpgacc_t<base + 0x280> RPGACC;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RSCAN モジュール（RX140/RX231/RX24T）
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct rscan_t : rscan_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::RSCAN;		///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::PCLKB / 2;		///< 周辺クロック周波数（1/2）
		static constexpr auto MCLK = clock_profile::BASE;			///< CANMCLK

		static constexpr auto RXINT = ICU::VECTOR::RXFINT;			///< グローバル受信 FIFO 割り込み
		static constexpr auto GLERRINT = ICU::VECTOR::GLERRINT;		///< グローバルエラー割り込み
		static constexpr auto TXINT = ICU::VECTOR::TXINT;			///< チャネル送信割り込み
		static constexpr auto COMFRXINT = ICU::VECTOR::COMFRXINT;	///< 送受信 FIFO 受信割り込み
		static constexpr auto CHERRIN = ICU::VECTOR::CHERRINT;		///< チャネルエラー割り込み
	};
	typedef rscan_t<0x000A'8300> RSCAN;
}
