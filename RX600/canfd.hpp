#pragma once
//=========================================================================//
/*!	@file
	@brief	CAN FD Module / CAN FD モジュール @n
			※新型 CAN コントローラー @n
			・RX660 (CANFD-Lite) @n
			・RX261 @n
			・RX26T
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
		@brief	CANFD base class
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct canfd_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  公称ビットレート設定レジスタ (NBCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct nbcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  BRP;
			bits_rw_t<io_, bitpos::B10, 7>  SJW;
			bits_rw_t<io_, bitpos::B17, 8>  TSEG1;
			bits_rw_t<io_, bitpos::B25, 7>  TSEG2;
		};
		static inline nbcr_t<base + 0x00> NBCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネル制御レジスタ (CHCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct chcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  MDC;
			bit_rw_t <io_, bitpos::B2>      SLPRQ;
			bit_rw_t <io_, bitpos::B3>      RTBO;

			bit_rw_t <io_, bitpos::B8>      BEIE;
			bit_rw_t <io_, bitpos::B9>      EWIE;
			bit_rw_t <io_, bitpos::B10>     EPIE;
			bit_rw_t <io_, bitpos::B11>     BOEIE;
			bit_rw_t <io_, bitpos::B12>     BORIE;
			bit_rw_t <io_, bitpos::B13>     OLIE;
			bit_rw_t <io_, bitpos::B14>     BLIE;
			bit_rw_t <io_, bitpos::B15>     ALIE;
			bit_rw_t <io_, bitpos::B16>     TAIE;
			bit_rw_t <io_, bitpos::B17>     ECOVIE;
			bit_rw_t <io_, bitpos::B18>     SCOVIE;
			bit_rw_t <io_, bitpos::B19>     TDCVIE;

			bits_rw_t<io_, bitpos::B21, 2>  BOM;
			bit_rw_t <io_, bitpos::B23>     EDM;
			bit_rw_t <io_, bitpos::B24>     CTME;
			bits_rw_t<io_, bitpos::B25, 2>  CTMS;

			bit_rw_t <io_, bitpos::B30>     BFT;
			bit_rw_t <io_, bitpos::B31>     ROME;
		};
		static inline chcr_t<base + 0x04> CHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルステータスレジスタ (CHSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct chsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <in_, bitpos::B0>      RSTST;
			bit_ro_t <in_, bitpos::B1>      HLTST;
			bit_ro_t <in_, bitpos::B2>      SLPST;
			bit_ro_t <in_, bitpos::B3>      EPST;
			bit_ro_t <in_, bitpos::B4>      BOST;
			bit_ro_t <in_, bitpos::B5>      TRMST;
			bit_ro_t <in_, bitpos::B6>      RECST;
			bit_ro_t <in_, bitpos::B7>      CRDY;
			bit_ro_t <io_, bitpos::B8>      RESI;

			bits_ro_t<in_, bitpos::B16, 8>  REC;
			bits_ro_t<in_, bitpos::B24, 8>  TEC;
		};
		static inline chsr_t<base + 0x08> CHSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルエラーステータスレジスタ (CHESR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct chesr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      BEDF;
			bit_rw_t <io_, bitpos::B1>      EWDF;
			bit_rw_t <io_, bitpos::B2>      EPDF;
			bit_rw_t <io_, bitpos::B3>      BOEDF;
			bit_rw_t <io_, bitpos::B4>      BORDF;
			bit_rw_t <io_, bitpos::B5>      OLDF;
			bit_rw_t <io_, bitpos::B6>      BLDF;
			bit_rw_t <io_, bitpos::B7>      ALDF;
			bit_rw_t <io_, bitpos::B8>      SEDF;
			bit_rw_t <io_, bitpos::B9>      FEDF;
			bit_rw_t <io_, bitpos::B10>     AEDF;
			bit_rw_t <io_, bitpos::B11>     CEDF;
			bit_rw_t <io_, bitpos::B12>     B1BDF;
			bit_rw_t <io_, bitpos::B13>     B0EDF;
			bit_rw_t <io_, bitpos::B14>     ADEDF;

			bits_ro_t<in_, bitpos::B16, 15> CRC;
		};
		static inline chesr_t<base + 0x0C> CHESR;


		//-----------------------------------------------------------------//
		/*!
			@brief  データビットレート設定レジスタ (DBCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dbcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  BRP;
			bits_rw_t<io_, bitpos::B8,  5>  TSEG1;

			bits_rw_t<io_, bitpos::B16, 4>  TSEG2;
			bits_rw_t<io_, bitpos::B24, 4>  SJW;
		};
		static inline dbcr_t<base + 0x100> DBCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN FD 設定レジスタ (FDCFG)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fdcfg_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3>  ECC;

			bit_rw_t <io_, bitpos::B8>      SSPC;
			bit_rw_t <io_, bitpos::B9>      TDCE;
			bit_rw_t <io_, bitpos::B10>     TESI;

			bits_rw_t<io_, bitpos::B16, 8>  TDCO;

			bit_rw_t <io_, bitpos::B28>     FDOE;
			bit_rw_t <io_, bitpos::B29>     REFE;
			bit_rw_t <io_, bitpos::B30>     CLOE;
		};
		static inline fdcfg_t<base + 0x104> FDCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN FD 制御レジスタ (FDCTR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fdctr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      ECCL;
			bit_rw_t <io_, bitpos::B1>      SCCL;
		};
		static inline fdctr_t<base + 0x108> FDCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN FD ステータスレジスタ (FDSTS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fdsts_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<in_, bitpos::B0,  8>  TDCR;
			bit_rw_t <io_, bitpos::B8>      ECOV;
			bit_rw_t <io_, bitpos::B9>      SCOV;

			bit_rw_t <io_, bitpos::B15>     TDCV;

			bits_ro_t<in_, bitpos::B16, 8>  EC;
			bits_ro_t<in_, bitpos::B24, 8>  SC;
		};
		static inline fdsts_t<base + 0x10C> FDSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN FD CRC レジスタ (FDCRC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fdcrc_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 21>  CRC21;

			bits_ro_t<in_, bitpos::B24, 4>  SBC;
		};
		static inline fdcrc_t<base + 0x110> FDCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバル設定レジスタ (GCFG)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gcfg_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      TPRI;
			bit_rw_t <io_, bitpos::B1>      DCE;
			bit_rw_t <io_, bitpos::B2>      DRE;
			bit_rw_t <io_, bitpos::B3>      MME;
			bit_rw_t <io_, bitpos::B4>      DLLCS;
			bit_rw_t <io_, bitpos::B5>      OMRC;

			bits_rw_t<io_, bitpos::B8, 4>   TSP;
			bit_rw_t <io_, bitpos::B12>     TSCS;

			bits_rw_t<io_, bitpos::B16, 16> ITP;
		};
		static inline gcfg_t<base + 0x14> GCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバル制御レジスタ (GCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   MDC;
			bit_rw_t <io_, bitpos::B2>      SLPRQ;

			bit_rw_t <io_, bitpos::B8>      DEIE;
			bit_rw_t <io_, bitpos::B9>      MLIE;
			bit_rw_t <io_, bitpos::B10>     THLIE;
			bit_rw_t <io_, bitpos::B11>     POIE;

			bit_rw_t <io_, bitpos::B16>     TSCR;
		};
		static inline gcr_t<base + 0x18> GCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバルステータスレジスタ (GSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>  RSTST;
			bit_ro_t <in_, bitpos::B1>  HLTST;
			bit_ro_t <in_, bitpos::B2>  SLPST;
			bit_ro_t <in_, bitpos::B3>  RAMST;
		};
		static inline gsr_t<base + 0x1C> GSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバルエラーステータスレジスタ (GESR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gesr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    DEDF;
			bit_rw_t <in_, bitpos::B1>    MLDF;
			bit_rw_t <in_, bitpos::B2>    THLDF;
			bit_rw_t <io_, bitpos::B3>    PODF;

			bit_rw_t <io_, bitpos::B16>   EEDF0;
		};
		static inline gesr_t<base + 0x20> GESR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信割り込みステータスレジスタ (TISR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tisr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>  TSIF0;
			bit_ro_t <in_, bitpos::B1>  TAIF0;
			bit_ro_t <in_, bitpos::B2>  TQIF0;
			bit_ro_t <in_, bitpos::B3>  CFTIF0;
			bit_ro_t <in_, bitpos::B4>  THIF0;
		};
		static inline tisr_t<base + 0xA4> TISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイムスタンプカウンタレジスタ (TSCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  VAL;
		};
		static inline tscr_t<base + 0x24> TSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタリスト制御レジスタ (AFCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct afcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      PAGE;

			bit_rw_t <io_, bitpos::B8>      AFLWE;
		};
		static inline afcr_t<base + 0x28> AFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタリスト設定レジスタ (AFCFG)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct afcfg_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 6>  RN0;
		};
		static inline afcfg_t<base + 0x2C> AFCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタリスト n ID レジスタ (AFLIDR[n]) (n = 0 ～ 15) @n
					※ AFLn.IDR
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct aflidr_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 15) { io_::index = j * 16; } }

			bits_rw_t<io_, bitpos::B0,  29>  ID;
			bit_rw_t <io_, bitpos::B29>      LPC;
			bit_rw_t <io_, bitpos::B30>      RTR;
			bit_rw_t <io_, bitpos::B31>      IDE;

			aflidr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline aflidr_t<base + 0x0120> AFLIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタリスト n マスクレジスタ (AFLMASK[n]) (n = 0 ～ 15) @n
					※ AFLn.MASK
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct aflmask_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 15) { io_::index = j * 16; } }

			bits_rw_t<io_, bitpos::B0,  29>  IDM;
			bit_rw_t <io_, bitpos::B29>      IFL1;
			bit_rw_t <io_, bitpos::B30>      RTRM;
			bit_rw_t <io_, bitpos::B31>      IDEM;

			aflmask_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline aflmask_t<base + 0x0124> AFLMASK;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタリスト n ポインタレジスタ 0 (AFLPTR0[n]) (n = 0 ～ 15) @n
					※ AFLn.PTR0
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct aflptr0_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 15) { io_::index = j * 16; } }

			bits_rw_t<io_, bitpos::B0,  4>   DLC;

			bit_rw_t <io_, bitpos::B7>       IFL0;
			bits_rw_t<io_, bitpos::B8,  5>   DMB;

			bit_rw_t <io_, bitpos::B15>      DMBE;
			bits_rw_t<io_, bitpos::B16, 16>  PTR;

			aflptr0_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline aflptr0_t<base + 0x0128> AFLPTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタリスト n ポインタレジスタ 1 (AFLPTR1[n]) (n = 0 ～ 15) @n
					※ AFLn.PTR1
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct aflptr1_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 15) { io_::index = j * 16; } }

			bit_rw_t <io_, bitpos::B0>       RF0E;
			bit_rw_t <io_, bitpos::B1>       RF1E;

			bit_rw_t <io_, bitpos::B8>       CF0E;

			aflptr1_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline aflptr1_t<base + 0x012C> AFLPTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信メッセージバッファ設定レジスタ (RMCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   MNB;

			bits_rw_t<io_, bitpos::B8, 3>   PLS;
		};
		static inline rmcr_t<base + 0x30> RMCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信メッセージバッファ新データレジスタ (RMNDR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmndr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 32>  NDF;
		};
		static inline rmndr_t<base + 0x34> RMNDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO n 設定レジスタ (RFCRn) (n = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfcrn_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      RFE;
			bit_rw_t <io_, bitpos::B1>      RFIE;

			bits_rw_t<io_, bitpos::B4, 3>   PLS;

			bits_rw_t<io_, bitpos::B8, 3>   FDS;

			bit_rw_t <io_, bitpos::B12>     RFIM;
			bits_rw_t<io_, bitpos::B13, 3>  RFITH;
		};
		static inline rfcrn_t<base + 0x3C> RFCR0;
		static inline rfcrn_t<base + 0x40> RFCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO n ステータスレジスタ (RFSRn) (n = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfsrn_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <in_, bitpos::B0>      EMPTY;
			bit_ro_t <in_, bitpos::B1>      FULL;
			bit_rw_t <io_, bitpos::B2>      LOST;
			bit_rw_t <io_, bitpos::B3>      RFIF;

			bits_rw_t<in_, bitpos::B8, 6>   FLVL;
		};
		static inline rfsrn_t<base + 0x44> RFSR0;
		static inline rfsrn_t<base + 0x48> RFSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO n ポインタ制御レジスタ (RFPCRn) (n = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfpcrn_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   VAL;
		};
		static inline rfpcrn_t<base + 0x4C> RFPCR0;
		static inline rfpcrn_t<base + 0x50> RFPCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  共通 FIFO 0 設定レジスタ (CFCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfcr0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CFE;
			bit_rw_t <io_, bitpos::B1>      CFRIE;
			bit_rw_t <io_, bitpos::B2>      CFTIE;

			bits_rw_t<io_, bitpos::B4, 3>   PLS;

			bit_rw_t <io_, bitpos::B8>      MODE;

			bit_rw_t <io_, bitpos::B10>     ITCS;
			bit_rw_t <io_, bitpos::B11>     ITR;
			bit_rw_t <io_, bitpos::B12>     CFIM;
			bits_rw_t<io_, bitpos::B13, 3>  CFITH;
			bits_rw_t<io_, bitpos::B16, 2>  LTM;

			bits_rw_t<io_, bitpos::B21, 3>  FDS;
			bits_rw_t<io_, bitpos::B24, 8>  TINT;
		};
		static inline cfcr0_t<base + 0x54> CFCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  共通 FIFO 0 ステータスレジスタ (CFSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfsr0_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <in_, bitpos::B0>      EMPTY;
			bit_ro_t <in_, bitpos::B1>      FULL;
			bit_rw_t <io_, bitpos::B2>      LOST;
			bit_rw_t <io_, bitpos::B3>      CFRIF;
			bit_rw_t <io_, bitpos::B4>      CFTIF;

			bits_rw_t<in_, bitpos::B8, 6>   FLVL;
		};
		static inline cfsr0_t<base + 0x58> CFSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  共通 FIFO 0 ポインタ制御レジスタ (CFPCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfpcr0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   VAL;
		};
		static inline cfpcr0_t<base + 0x5C> CFPCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO エンプティステータスレジスタ (FESR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fesr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      RFEMP0;
			bit_ro_t <in_, bitpos::B1>      RFEMP1;

			bit_rw_t <in_, bitpos::B8>      CFEMP0;
		};
		static inline fesr_t<base + 0x60> FESR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO フルステータスレジスタ (FFSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ffsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      RFFUL0;
			bit_ro_t <in_, bitpos::B1>      RFFUL1;

			bit_rw_t <in_, bitpos::B8>      CFFUL0;
		};
		static inline ffsr_t<base + 0x64> FFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO メッセージロストステータスレジスタ (FMLSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fmlsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      RFML0;
			bit_ro_t <in_, bitpos::B1>      RFML1;

			bit_rw_t <in_, bitpos::B8>      CFML0;
		};
		static inline fmlsr_t<base + 0x68> FMLSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO 割り込みステータスレジスタ (RFISR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfisr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      RFIF0;
			bit_ro_t <in_, bitpos::B1>      RFIF1;
		};
		static inline rfisr_t<base + 0x6C> RFISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DMA 転送制御レジスタ (DTCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dtcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      RFDTE0;
			bit_rw_t <io_, bitpos::B1>      RFDTE1;

			bit_rw_t <io_, bitpos::B8>      CFDTE0;
		};
		static inline dtcr_t<base + 0xC8> DTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DMA 転送ステータスレジスタ (DTSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dtsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      RFDTS0;
			bit_ro_t <in_, bitpos::B1>      RFDTS1;

			bit_ro_t <in_, bitpos::B8>      CFDTS0;
		};
		static inline dtsr_t<base + 0xCC> DTSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信メッセージバッファ n 制御レジスタ (TMCR[n]) (n = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmcr_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 3) { io_::index = j; } }

			bit_rw_t <io_, bitpos::B0>       TXRQ;
			bit_rw_t <io_, bitpos::B1>       TARQ;
			bit_rw_t <io_, bitpos::B2>       ONESHOT;

			tmcr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmcr_t<base + 0x70> TMCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信メッセージバッファ n ステータスレジスタ (TMSR[n]) (n = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmsr_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 3) { io_::index = j; } }

			bit_rw_t <io_, bitpos::B0>       TXSF;
			bits_rw_t<io_, bitpos::B1, 2>    TXRF;
			bit_rw_t <io_, bitpos::B3>       TXRQS;
			bit_rw_t <io_, bitpos::B4>       TARQS;

			tmsr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline tmsr_t<base + 0x74> TMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信メッセージバッファ送信要求ステータスレジスタ 0 (TMTRSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmtrsr0_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      TXRQS0;
			bit_ro_t <in_, bitpos::B1>      TXRQS1;
			bit_ro_t <in_, bitpos::B2>      TXRQS2;
			bit_ro_t <in_, bitpos::B3>      TXRQS3;
		};
		static inline tmtrsr0_t<base + 0x78> TMTRSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信メッセージバッファ送信アボート要求ステータスレジスタ 0 (TMARSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmarsr0_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      TARQS0;
			bit_ro_t <in_, bitpos::B1>      TARQS1;
			bit_ro_t <in_, bitpos::B2>      TARQS2;
			bit_ro_t <in_, bitpos::B3>      TARQS3;
		};
		static inline tmarsr0_t<base + 0x7C> TMARSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信メッセージバッファ送信完了ステータスレジスタ 0 (TMTCSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmtcsr0_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      TXCF0;
			bit_ro_t <in_, bitpos::B1>      TXCF1;
			bit_ro_t <in_, bitpos::B2>      TXCF2;
			bit_ro_t <in_, bitpos::B3>      TXCF3;
		};
		static inline tmtcsr0_t<base + 0x80> TMTCSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信メッセージバッファ送信アボートステータスレジスタ 0 (TMTASR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmtasr0_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>      TAF0;
			bit_ro_t <in_, bitpos::B1>      TAF1;
			bit_ro_t <in_, bitpos::B2>      TAF2;
			bit_ro_t <in_, bitpos::B3>      TAF3;
		};
		static inline tmtasr0_t<base + 0x84> TMTASR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信メッセージバッファ割り込み許可レジスタ 0 (TMIER0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmier0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      TMIE0;
			bit_rw_t <io_, bitpos::B1>      TMIE1;
			bit_rw_t <io_, bitpos::B2>      TMIE2;
			bit_rw_t <io_, bitpos::B3>      TMIE3;
		};
		static inline tmier0_t<base + 0x88> TMIER0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信キュー 0 設定レジスタ (TQCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tqcr0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      TQE;

			bit_rw_t <io_, bitpos::B5>      TQIE;

			bit_rw_t <io_, bitpos::B7>      TQIM;
			bits_rw_t<io_, bitpos::B8, 2>   QDS;
		};
		static inline tqcr0_t<base + 0x8C> TQCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信キュー 0 ステータスレジスタ (TQSR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tqsr0_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <in_, bitpos::B0>      EMPTY;
			bit_ro_t <in_, bitpos::B1>      FULL;
			bit_rw_t <io_, bitpos::B2>      TQIF;

			bits_ro_t<in_, bitpos::B8, 3>   FLVL;
		};
		static inline tqsr0_t<base + 0x90> TQSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信キュー 0 ポインタ制御レジスタ (TQPCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tqpcr0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   VAL;
		};
		static inline tqpcr0_t<base + 0x94> TQPCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信履歴設定レジスタ (THCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      THE;

			bit_rw_t <io_, bitpos::B8>      THIE;
			bit_rw_t <io_, bitpos::B9>      THIM;
			bit_rw_t <io_, bitpos::B10>     THRC;
		};
		static inline thcr_t<base + 0x98> THCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信履歴ステータスレジスタ (THSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <in_, bitpos::B0>      EMPTY;
			bit_ro_t <in_, bitpos::B1>      FULL;
			bit_rw_t <io_, bitpos::B2>      LOST;
			bit_rw_t <io_, bitpos::B3>      THIF;

			bits_ro_t<in_, bitpos::B8, 4>   FLVL;
		};
		static inline thsr_t<base + 0x9C> THSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信履歴アクセスレジスタ 0 (THACR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thacr0_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 3>   BT;
			bits_ro_t<in_, bitpos::B3, 2>   BN;

			bits_ro_t<in_, bitpos::B16, 16> TS;
		};
		static inline thacr0_t<base + 0x740> THACR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信履歴アクセスレジスタ 1 (THACR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thacr1_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0,  16> PTR;
			bits_ro_t<in_, bitpos::B16, 2>  IFL;
		};
		static inline thacr1_t<base + 0x744> THACR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信履歴ポインタ制御レジスタ (THPCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct thpcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   VAL;
		};
		static inline thpcr_t<base + 0xA0> THPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバルリセット制御レジスタ (GRCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct grcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      SRST;

			bits_rw_t<io_, bitpos::B8, 8>   KEY;
		};
		static inline grcr_t<base + 0xD8> GRCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバルテストモード設定レジスタ (GTMCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtmcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 4>  RTPS;
		};
		static inline gtmcr_t<base + 0xA8> GTMCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバルテストモード許可レジスタ (GTMER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtmer_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B2>      RTME;
		};
		static inline gtmer_t<base + 0xAC> GTMER;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバル CAN FD 設定レジスタ (GFDCFG)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gfdcfg_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      PXEDIS;

			bits_rw_t<io_, bitpos::B8, 2>   TSCPS;
		};
		static inline gfdcfg_t<base + 0xB0> GFDCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  グローバルテストモードロックキーレジスタ (GTMLKR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtmlkr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  VAL;
		};
		static inline gtmlkr_t<base + 0xB8> GTMLKR;


		//-----------------------------------------------------------------//
		/*!
			@brief  RAM テストページアクセスレジスタ (RTPAR[k]) (k = 0 ～ 63)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rtpar_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 63) { io_::index = j * 4; } }

			rtpar_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline rtpar_t<base + 0x280> RTPAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタ無効エントリ設定レジスタ (AFIGSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct afigsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>   IGES;
		};
		static inline afigsr_t<base + 0xC0> AFIGSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタ無効エントリ許可レジスタ (AFIGER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct afiger_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      IGEE;

			bits_rw_t<io_, bitpos::B8, 8>   KEY;
		};
		static inline afiger_t<base + 0xC4> AFIGER;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信メッセージバッファ割り込み許可レジスタ (RMIER)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rmier_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      RMIE0;
			bit_rw_t <io_, bitpos::B1>      RMIE1;
			bit_rw_t <io_, bitpos::B2>      RMIE2;
			bit_rw_t <io_, bitpos::B3>      RMIE3;
			bit_rw_t <io_, bitpos::B4>      RMIE4;
			bit_rw_t <io_, bitpos::B5>      RMIE5;
			bit_rw_t <io_, bitpos::B6>      RMIE6;
			bit_rw_t <io_, bitpos::B7>      RMIE7;
			bit_rw_t <io_, bitpos::B8>      RMIE8;
			bit_rw_t <io_, bitpos::B9>      RMIE9;
			bit_rw_t <io_, bitpos::B10>     RMIE10;
			bit_rw_t <io_, bitpos::B11>     RMIE11;
			bit_rw_t <io_, bitpos::B12>     RMIE12;
			bit_rw_t <io_, bitpos::B13>     RMIE13;
			bit_rw_t <io_, bitpos::B14>     RMIE14;
			bit_rw_t <io_, bitpos::B15>     RMIE15;
			bit_rw_t <io_, bitpos::B16>     RMIE16;
			bit_rw_t <io_, bitpos::B17>     RMIE17;
			bit_rw_t <io_, bitpos::B18>     RMIE18;
			bit_rw_t <io_, bitpos::B19>     RMIE19;
			bit_rw_t <io_, bitpos::B20>     RMIE20;
			bit_rw_t <io_, bitpos::B21>     RMIE21;
			bit_rw_t <io_, bitpos::B22>     RMIE22;
			bit_rw_t <io_, bitpos::B23>     RMIE23;
			bit_rw_t <io_, bitpos::B24>     RMIE24;
			bit_rw_t <io_, bitpos::B25>     RMIE25;
			bit_rw_t <io_, bitpos::B26>     RMIE26;
			bit_rw_t <io_, bitpos::B27>     RMIE27;
			bit_rw_t <io_, bitpos::B28>     RMIE28;
			bit_rw_t <io_, bitpos::B29>     RMIE29;
			bit_rw_t <io_, bitpos::B30>     RMIE30;
			bit_rw_t <io_, bitpos::B31>     RMIE31;
		};
		static inline rmier_t<base + 0x38> RMIER;


	// -------------------- メッセージ・バッファ関係定義 ---------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メッセージバッファフィールド（読出し専用データフィールド）
			@param[in]	BN		バッファ数
			@param[in]	ofs		オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t BN, uint32_t ofs>
		struct msgbuf_rod_t {

			typedef rw32_index_t<base + ofs + 0> hf0_;
			rw32_t<hf0_::address> HF0;
			bits_rw_t<hf0_, bitpos::B0,  29>  ID;
			bit_rw_t <hf0_, bitpos::B29>      THENT;
			bit_rw_t <hf0_, bitpos::B30>      RTR;
			bit_rw_t <hf0_, bitpos::B31>      IDE;

			typedef rw32_index_t<base + ofs + 4> hf1_;
			rw32_t<hf1_::address> HF1;
			bits_rw_t<hf1_, bitpos::B0,  16>  TS;
			bits_rw_t<hf1_, bitpos::B28,  4>  DLC;

			typedef rw32_index_t<base + ofs + 8> hf2_;
			rw32_t<hf2_::address> HF2;
			bit_rw_t <hf2_, bitpos::B0>       ESI;
			bit_rw_t <hf2_, bitpos::B1>       BRS;
			bit_rw_t <hf2_, bitpos::B2>       FDF;

			bits_rw_t<hf2_, bitpos::B8,  2>   IFL;

			bits_rw_t<hf2_, bitpos::B16, 16>  PTR;

			typedef rw32_index_t<base + ofs + 12> df0_;
			struct df_t {
				// 32ビット単位、読出し専用
				uint32_t operator() (uint32_t n) noexcept {
					if(n >= 16) n = 15;
					return rd32_(df0_::address + n * 4);
				}

				volatile const uint32_t& operator [] (uint32_t n) const noexcept {
					if(n >= 16) n = 15;
					return *reinterpret_cast<volatile uint32_t*>(df0_::address + n * 4);
				}
			};
			df_t	DF;

			struct data_t {
				// バイト単位、読出し専用
				uint8_t operator() (uint32_t n) noexcept {
					if(n >= 64) n = 63;
					return rd8_(df0_::address + n);
				}


				volatile const uint8_t& operator [] (uint32_t n) const noexcept {
					if(n >= 64) n = 63;
					return *reinterpret_cast<volatile uint8_t*>(df0_::address + n);
				}
			};
			data_t	DATA;


			void set_index(uint32_t idx) noexcept
			{
				if(idx < BN) {
					hf0_::index = idx * 0x4C;
					hf1_::index = idx * 0x4C;
					hf2_::index = idx * 0x4C;
					df0_::index = idx * 0x4C;
				}
			}


			msgbuf_rod_t& operator [] (uint32_t idx) noexcept {
				set_index(idx);
				return *this;
			}

		private:
			void operator = (const msgbuf_rod_t& t) { };  // 代入は禁止
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メッセージバッファフィールド（読み書きデータフィールド）
			@param[in]	BN		バッファ数
			@param[in]	ofs		オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t BN, uint32_t ofs>
		struct msgbuf_rwd_t {

			typedef rw32_index_t<base + ofs + 0> hf0_;
			rw32_t<hf0_::address> HF0;
			bits_rw_t<hf0_, bitpos::B0,  29>  ID;
			bit_rw_t <hf0_, bitpos::B29>      THENT;
			bit_rw_t <hf0_, bitpos::B30>      RTR;
			bit_rw_t <hf0_, bitpos::B31>      IDE;

			typedef rw32_index_t<base + ofs + 4> hf1_;
			rw32_t<hf1_::address> HF1;
			bits_rw_t<hf1_, bitpos::B0,  16>  TS;
			bits_rw_t<hf1_, bitpos::B28,  4>  DLC;

			typedef rw32_index_t<base + ofs + 8> hf2_;
			rw32_t<hf2_::address> HF2;
			bit_rw_t <hf2_, bitpos::B0>       ESI;
			bit_rw_t <hf2_, bitpos::B1>       BRS;
			bit_rw_t <hf2_, bitpos::B2>       FDF;

			bits_rw_t<hf2_, bitpos::B8,  2>   IFL;

			bits_rw_t<hf2_, bitpos::B16, 16>  PTR;

			typedef rw32_index_t<base + ofs + 12> df0_;
			struct df_t {
				// 32ビット単位、読出し専用
				uint32_t operator() (uint32_t n) noexcept {
					if(n >= 16) n = 15;
					return rd32_(df0_::address + n * 4);
				}

				void set(uint32_t n, uint32_t d) noexcept {
					if(n >= 16) n = 15;
					return wr32_(df0_::address + n * 4, d);
				}

				volatile uint32_t& operator [] (uint32_t n) noexcept {
					if(n >= 16) n = 15;
					return *reinterpret_cast<volatile uint32_t*>(df0_::address + n * 4);
				}
			};
			df_t	DF;

			struct data_t {
				// バイト単位、読出し専用
				uint8_t operator() (uint32_t n) noexcept {
					if(n >= 64) n = 63;
					return rd8_(df0_::address + n);
				}

				void set(uint32_t n, uint32_t d) noexcept {
					if(n >= 64) n = 64;
					return wr8_(df0_::address + n, d);
				}

				volatile uint8_t& operator [] (uint32_t n) noexcept {
					if(n >= 64) n = 63;
					return *reinterpret_cast<volatile uint8_t*>(df0_::address + n);
				}
			};
			data_t	DATA;


			void set_index(uint32_t idx) noexcept
			{
				if(idx < BN) {
					hf0_::index = idx * 0x4C;
					hf1_::index = idx * 0x4C;
					hf2_::index = idx * 0x4C;
					df0_::index = idx * 0x4C;
				}
			}


			msgbuf_rwd_t& operator [] (uint32_t idx) noexcept {
				set_index(idx);
				return *this;
			}

		private:
			void operator = (const msgbuf_rwd_t& t) { };  // 代入は禁止
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  受信メッセージバッファ n (RMB[n]) (n = 0 ～ 31) 
		*/
		//-----------------------------------------------------------------//
		static inline msgbuf_rod_t<32, 0x920> RMB;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO n (RFB[n]) (n = 0, 1) 
		*/
		//-----------------------------------------------------------------//
		static inline msgbuf_rod_t<2, 0x520> RFB;


		//-----------------------------------------------------------------//
		/*!
			@brief  共通 FIFO 0 (CFB)
		*/
		//-----------------------------------------------------------------//
		static inline msgbuf_rod_t<1, 0x5B8> CFB;


		//-----------------------------------------------------------------//
		/*!
			@brief  共通 送信メッセージバッファ n (TMB[n]) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		static inline msgbuf_rwd_t<4, 0x604> TMB;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CANFD ECC 制御モジュール（CANFD_ecc）
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct canfd_ecc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  ECC 制御 / ステータスレジスタ (ECCSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct eccsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <in_, bitpos::B0>      ECCEF;
			bit_ro_t <in_, bitpos::B1>      EC1EF;
			bit_ro_t <in_, bitpos::B2>      EC2EF;
			bit_rw_t <io_, bitpos::B3>      EC1EIE;
			bit_rw_t <io_, bitpos::B4>      EC2EIE;
			bit_rw_t <io_, bitpos::B5>      EC1ECD;
			bit_rw_t <io_, bitpos::B6>      ECEDE;

			bit_rw_t <io_, bitpos::B9>      EC1EC;
			bit_rw_t <io_, bitpos::B10>     EC2EC;
			bit_ro_t <in_, bitpos::B11>     ECOVF;

			bits_rw_t<io_, bitpos::B14, 2>  ECEDWC;
			bit_ro_t <in_, bitpos::B16>     EC1EAS;
			bit_ro_t <in_, bitpos::B17>     EC2EAS;
		};
		static inline eccsr_t<base + 0x00> ECCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ECC テストモードレジスタ (ECTMR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ectmr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B1>      ECDIS;

			bit_rw_t <io_, bitpos::B7>      ECTME;

			bits_rw_t<io_, bitpos::B14, 2>  ECTMWC;
		};
		static inline ectmr_t<base + 0x04> ECTMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ECC デコーダテストデータレジスタ (ECTDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x0C> ECTDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ECC エラーアドレスレジスタ (ECEAR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ecear_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11>  ADR;
		};
		static inline ecear_t<base + 0x10> ECEAR;
	};

#if defined(SIG_RX261)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CANFD モジュール (CANFD, ECC コア) for RX261
		@param[in]	base	ベースアドレス
		@param[in]	ecc		ECC 制御アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, uint32_t ecc>
	struct canfd_t : canfd_base_t<base>, canfd_ecc_t<ecc> {

		static constexpr auto PERIPHERAL = peripheral::CANFD0;	///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::CANFDCLK;	///< クロック周波数

		static constexpr auto GB0V = ICU::VECTOR::RFDREQ0;	///< グローバル０・割り込みベクター
		static constexpr auto GB1V = ICU::VECTOR::RFDREQ1;	///< グローバル１・割り込みベクター
		static constexpr auto CH0V = ICU::VECTOR::CFDREQ0;	///< チャネル０・割り込みベクター

		static constexpr auto CHEV = ICU::VECTOR::CHEI;		///< チャネルエラー・割り込みベクター
		static constexpr auto CFRV = ICU::VECTOR::CFRI;		///< 共通 FIFO 受信・割り込みベクター
		static constexpr auto GLEV = ICU::VECTOR::GLEI;		///< グローバルエラー・割り込みベクター
		static constexpr auto RFRV = ICU::VECTOR::RFRI;		///< 受信 FIFO 割り込みベクター
		static constexpr auto CHTV = ICU::VECTOR::CHTI;		///< チャネル送信・割り込みベクター
		static constexpr auto RMRV = ICU::VECTOR::RMRI;		///< 受信メッセージバッファ・割り込みベクター

		static constexpr auto EC1V = ICU::VECTOR::EC1EI;	///< １ビット ECC エラー・割り込みベクター
		static constexpr auto EC2V = ICU::VECTOR::EC2EI;	///< ２ビット ECC エラー・割り込みベクター
		static constexpr auto ECOV = ICU::VECTOR::ECOVI;	///< ECC オーバーフロー・割り込みベクター
	};
	typedef canfd_t<0x000A'8000, 0x000E'D000> CANFD0;
#elif defined(SIG_RX26T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CANFD モジュール (CANFD, ECC コア) for RX26T
		@param[in]	base	ベースアドレス
		@param[in]	ecc		ECC 制御アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, uint32_t ecc>
	struct canfd_t : canfd_base_t<base>, canfd_ecc_t<ecc> {

		static constexpr auto PERIPHERAL = peripheral::CANFD0;	///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::CANFDCLK;	///< クロック周波数

		static constexpr auto GB0V = ICU::VECTOR::RFDREQ0;	///< グローバル０・割り込みベクター
		static constexpr auto GB1V = ICU::VECTOR::RFDREQ1;	///< グローバル１・割り込みベクター
		static constexpr auto CH0V = ICU::VECTOR::CFDREQ0;	///< チャネル０・割り込みベクター

		static constexpr auto CHEV = ICU::GROUPBL2::CHEI;	///< チャネルエラー・割り込みベクター
		static constexpr auto CFRV = ICU::GROUPBL2::CFRI;	///< 共通 FIFO 受信・割り込みベクター
		static constexpr auto GLEV = ICU::GROUPBL2::GLEI;	///< グローバルエラー・割り込みベクター
		static constexpr auto RFRV = ICU::GROUPBL2::RFRI;	///< 受信 FIFO 割り込みベクター
		static constexpr auto CHTV = ICU::GROUPBL2::CHTI;	///< チャネル送信・割り込みベクター
		static constexpr auto RMRV = ICU::GROUPBL2::RMRI;	///< 受信メッセージバッファ・割り込みベクター

		static constexpr auto EC1V = ICU::SELECTA::EC1EI;	///< １ビット ECC エラー・割り込みベクター
		static constexpr auto EC2V = ICU::SELECTA::EC2EI;	///< ２ビット ECC エラー・割り込みベクター
		static constexpr auto ECOV = ICU::SELECTA::ECOVI;	///< ECC オーバーフロー・割り込みベクター
	};
	typedef canfd_t<0x000A'8000, 0x000E'D000> CANFD0;
#elif defined(SIG_RX660)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CANFD-Lite モジュール (CANFD, ECC コア) for RX660
		@param[in]	base	ベースアドレス
		@param[in]	ecc		ECC 制御アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, uint32_t ecc>
	struct canfd_t : canfd_base_t<base>, canfd_ecc_t<ecc> {

		static constexpr auto PERIPHERAL = peripheral::CANFD0;	///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::CANFDCLK;	///< クロック周波数

		static constexpr auto GB0V = ICU::SELECTB::RFDREQ0;	///< グローバル０・割り込みベクター
		static constexpr auto GB1V = ICU::SELECTB::RFDREQ1;	///< グローバル１・割り込みベクター
		static constexpr auto CH0V = ICU::SELECTB::CFDREQ0;	///< チャネル０・割り込みベクター

		static constexpr auto CHEV = ICU::GROUPBL2::CHEI;	///< チャネルエラー・割り込みベクター
		static constexpr auto CFRV = ICU::GROUPBL2::CFRI;	///< 共通 FIFO 受信・割り込みベクター
		static constexpr auto GLEV = ICU::GROUPBL2::GLEI;	///< グローバルエラー・割り込みベクター
		static constexpr auto RFRV = ICU::GROUPBL2::RFRI;	///< 受信 FIFO 割り込みベクター
		static constexpr auto CHTV = ICU::GROUPBL2::CHTI;	///< チャネル送信・割り込みベクター
		static constexpr auto RMRV = ICU::GROUPBL2::RMRI;	///< 受信メッセージバッファ・割り込みベクター

		static constexpr auto EC1V = ICU::SELECTA::EC1EI;	///< １ビット ECC エラー・割り込みベクター
		static constexpr auto EC2V = ICU::SELECTA::EC2EI;	///< ２ビット ECC エラー・割り込みベクター
		static constexpr auto ECOV = ICU::SELECTA::ECOVI;	///< ECC オーバーフロー・割り込みベクター
	};
	typedef canfd_t<0x000A'8000, 0x000E'D000> CANFD;
#endif
}
