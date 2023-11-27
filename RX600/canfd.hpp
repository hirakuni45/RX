#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・CANFD 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/can_frame.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CANFD ベース・モジュール（CANFD_base）
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
			bits_rw_t<io_, bitpos::B17, 8>  TSEG;
			bits_rw_t<io_, bitpos::B25, 7>  TSEG2;
		};
		typedef nbcr_t<base + 0x00> NBCR_;
		static  NBCR_ NBCR;


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
		typedef chcr_t<base + 0x04> CHCR_;
		static  CHCR_ CHCR;


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
		typedef chsr_t<base + 0x08> CHSR_;
		static  CHSR_ CHSR;


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
		typedef chesr_t<base + 0x0C> CHESR_;
		static  CHESR_ CHESR;


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
		typedef dbcr_t<base + 0x100> DBCR_;
		static  DBCR_ DBCR;


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
		typedef fdcfg_t<base + 0x104> FDCFG_;
		static  FDCFG_ FDCFG;


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
		typedef fdctr_t<base + 0x108> FDCTR_;
		static  FDCTR_ FDCTR;


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
		typedef fdsts_t<base + 0x10C> FDSTS_;
		static  FDSTS_ FDSTS;


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
		typedef fdcrc_t<base + 0x110> FDCRC_;
		static  FDCRC_ FDCRC;


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
		typedef gcfg_t<base + 0x14> GCFG_;
		static  GCFG_ GCFG;


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
		typedef gcr_t<base + 0x18> GCR_;
		static  GCR_ GCR;


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
		typedef gsr_t<base + 0x1C> GSR_;
		static  GSR_ GSR;


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

			bit_rw_t <io_, bitpos::B0>      DEDF;
			bit_rw_t <in_, bitpos::B1>      MLDF;
			bit_rw_t <in_, bitpos::B2>      THLDF;
			bit_rw_t <io_, bitpos::B3>      PODF;

			bit_rw_t <io_, bitpos::B16>     EEDF0;
		};
		typedef gesr_t<base + 0x20> GESR_;
		static  GESR_ GESR;


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
		typedef tisr_t<base + 0xA4> TISR_;
		static  TISR_ TISR;


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
		typedef tscr_t<base + 0x24> TSCR_;
		static  TSCR_ TSCR;


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
		typedef afcr_t<base + 0x28> AFCR_;
		static  AFCR_ AFCR;


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
		typedef afcfg_t<base + 0x2C> AFCFG_;
		static  AFCFG_ AFCFG;


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
		typedef aflidr_t<base + 0x0120> AFLIDR_;
		static  AFLIDR_ AFLIDR;


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
		typedef aflmask_t<base + 0x0124> AFLMASK_;
		static  AFLMASK_ AFLMASK;


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
		typedef aflptr0_t<base + 0x0128> AFLPTR0_;
		static  AFLPTR0_ AFLPTR0;


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
		typedef aflptr1_t<base + 0x012C> AFLPTR1_;
		static  AFLPTR1_ AFLPTR1;


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
		typedef rmcr_t<base + 0x30> RMCR_;
		static  RMCR_ RMCR;


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
		typedef rmndr_t<base + 0x34> RMNDR_;
		static  RMNDR_ RMNDR;


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
		typedef rfcrn_t<base + 0x3C> RFCR0_;
		static  RFCR0_ RFCR0;
		typedef rfcrn_t<base + 0x40> RFCR1_;
		static  RFCR1_ RFCR1;


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
		typedef rfsrn_t<base + 0x44> RFSR0_;
		static  RFSR0_ RFSR0;
		typedef rfsrn_t<base + 0x48> RFSR1_;
		static  RFSR1_ RFSR1;


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
		typedef rfpcrn_t<base + 0x4C> RFPCR0_;
		static  RFPCR0_ RFPCR0;
		typedef rfpcrn_t<base + 0x50> RFPCR1_;
		static  RFPCR1_ RFPCR1;


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
		typedef cfcr0_t<base + 0x54> CFCR0_;
		static  CFCR0_ CFCR0;


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
		typedef cfsr0_t<base + 0x58> CFSR0_;
		static  CFSR0_ CFSR0;


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
		typedef cfpcr0_t<base + 0x5C> CFPCR0_;
		static  CFPCR0_ CFPCR0;


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
		typedef fesr_t<base + 0x60> FESR_;
		static  FESR_ FESR;


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
		typedef ffsr_t<base + 0x64> FFSR_;
		static  FFSR_ FFSR;


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
		typedef fmlsr_t<base + 0x68> FMLSR_;
		static  FMLSR_ FMLSR;


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
		typedef rfisr_t<base + 0x6C> RFISR_;
		static  RFISR_ RFISR;


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
		typedef dtcr_t<base + 0xC8> DTCR_;
		static  DTCR_ DTCR;


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
		typedef dtsr_t<base + 0xCC> DTSR_;
		static  DTSR_ DTSR;


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
		typedef tmcr_t<base + 0x70> TMCR_;
		static  TMCR_ TMCR;


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
		typedef tmsr_t<base + 0x74> TMSR_;
		static  TMSR_ TMSR;


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
		typedef tmtrsr0_t<base + 0x78> TMTRSR0_;
		static  TMTRSR0_ TMTRSR0;


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
		typedef tmarsr0_t<base + 0x7C> TMARSR0_;
		static  TMARSR0_ TMARSR0;


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
		typedef tmtcsr0_t<base + 0x80> TMTCSR0_;
		static  TMTCSR0_ TMTCSR0;


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
		typedef tmtasr0_t<base + 0x84> TMTASR0_;
		static  TMTASR0_ TMTASR0;


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
		typedef tmier0_t<base + 0x88> TMIER0_;
		static  TMIER0_ TMIER0;


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
		typedef tqcr0_t<base + 0x8C> TQCR0_;
		static  TQCR0_ TQCR0;


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
		typedef tqsr0_t<base + 0x90> TQSR0_;
		static  TQSR0_ TQSR0;


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
		typedef tqpcr0_t<base + 0x94> TQPCR0_;
		static  TQPCR0_ TQPCR0;


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
		typedef thcr_t<base + 0x98> THCR_;
		static  THCR_ THCR;


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
		typedef thsr_t<base + 0x9C> THSR_;
		static  THSR_ THSR;


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
		typedef thacr0_t<base + 0x740> THACR0_;
		static  THACR0_ THACR0;


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
		typedef thacr1_t<base + 0x744> THACR1_;
		static  THACR1_ THACR1;


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
		typedef thpcr_t<base + 0xA0> THPCR_;
		static  THPCR_ THPCR;


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
		typedef grcr_t<base + 0xD8> GRCR_;
		static  GRCR_ GRCR;


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
		typedef gtmcr_t<base + 0xA8> GTMCR_;
		static  GTMCR_ GTMCR;


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
		typedef gtmer_t<base + 0xAC> GTMER_;
		static  GTMER_ GTMER;


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
		typedef gfdcfg_t<base + 0xB0> GFDCFG_;
		static  GFDCFG_ GFDCFG;


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
		typedef gtmlkr_t<base + 0xB8> GTMLKR_;
		static  GTMLKR_ GTMLKR;


		//-----------------------------------------------------------------//
		/*!
			@brief  RAM テストページアクセスレジスタ (RTPAR[k]) (k = 0 ～ 63)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rtpar_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
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
		typedef rtpar_t<base + 0x280> RTPAR_;
		static  RTPAR_ RTPAR;


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
		typedef afigsr_t<base + 0xC0> AFIGSR_;
		static  AFIGSR_ AFIGSR;


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
		typedef afiger_t<base + 0xC4> AFIGER_;
		static  AFIGER_ AFIGER;


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
		typedef rmier_t<base + 0x38> RMIER_;
		static  RMIER_ RMIER;

#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスレジスタ j （ MB[j] ）（ j = 0 ～ 31 ） @n
					※MB0 ～ MB31 の定義は冗長なので割愛してある、MB[n] でアクセスの事
		*/
		//-----------------------------------------------------------------//
		struct mb_t {
			typedef rw32_index_t<base +  0> io0_;
			typedef rw8_index_t <base +  4 + 1> io1_;
			typedef rw16_index_t<base + 12 + 2> io3_;

			bits_rw_t<io0_, bitpos::B0,  18>  EID;
			bits_rw_t<io0_, bitpos::B18, 11>  SID;
			bit_rw_t <io0_, bitpos::B30>      RTR;
			bit_rw_t <io0_, bitpos::B31>      IDE;

			bits_rw_t<io1_, bitpos::B0, 4>    DLC;

			struct data_t {
				volatile uint8_t& operator [] (uint32_t n) {
					return *reinterpret_cast<volatile uint8_t*>(io0_::address + 6 + n);
				}
			};
			data_t	DATA;

			io3_	TS;

			void set_index(uint32_t j) noexcept
			{
				if(j < 32) {
					io0_::index = j * 16;
					io1_::index = j * 16;
					io3_::index = j * 16;
				}
			}

			void clear(uint32_t d = 0) noexcept
			{
				auto a = io0_::address;
				wr32_(a,      d);
				wr32_(a +  4, d);
				wr32_(a +  8, d);
				wr32_(a + 12, d);
			}

			uint32_t get_id() noexcept {
				return SID() | (EID() << 11);
			}

			void set_id(uint32_t id) noexcept {
				SID = id & 0x7ff;
				EID = id >> 11;
			}

			void copy(uint32_t idx) noexcept {
				wr32_(io0_::address + io0_::index +  0, rd32_(base + idx * 16 +  0));
				wr32_(io0_::address + io0_::index +  4, rd32_(base + idx * 16 +  4));
				wr32_(io0_::address + io0_::index +  8, rd32_(base + idx * 16 +  8));
				wr32_(io0_::address + io0_::index + 12, rd32_(base + idx * 16 + 12));
			}

			void set(const can_frame& src) noexcept {
				wr32_(io0_::address + io0_::index +  0, src[0]);
				wr32_(io0_::address + io0_::index +  4, src[1]);
				wr32_(io0_::address + io0_::index +  8, src[2]);
				wr32_(io0_::address + io0_::index + 12, src[3]);
			}

			void get(can_frame& dst) noexcept {
				dst[0] = rd32_(io0_::address + io0_::index +  0);
				dst[1] = rd32_(io0_::address + io0_::index +  4);
				dst[2] = rd32_(io0_::address + io0_::index +  8);
				dst[3] = rd32_(io0_::address + io0_::index + 12);
			}

			mb_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}

		private:
			void operator = (const mb_t& t) { };  // 代入は禁止
		};
		typedef mb_t MB_;
		static  MB_ MB;
#endif

	};
	template <uint32_t base> typename canfd_base_t<base>::NBCR_    canfd_base_t<base>::NBCR;
	template <uint32_t base> typename canfd_base_t<base>::CHCR_    canfd_base_t<base>::CHCR;
	template <uint32_t base> typename canfd_base_t<base>::CHSR_    canfd_base_t<base>::CHSR;
	template <uint32_t base> typename canfd_base_t<base>::CHESR_   canfd_base_t<base>::CHESR;
	template <uint32_t base> typename canfd_base_t<base>::DBCR_    canfd_base_t<base>::DBCR;
	template <uint32_t base> typename canfd_base_t<base>::FDCFG_   canfd_base_t<base>::FDCFG;
	template <uint32_t base> typename canfd_base_t<base>::FDCTR_   canfd_base_t<base>::FDCTR;
	template <uint32_t base> typename canfd_base_t<base>::FDSTS_   canfd_base_t<base>::FDSTS;
	template <uint32_t base> typename canfd_base_t<base>::FDCRC_   canfd_base_t<base>::FDCRC;
	template <uint32_t base> typename canfd_base_t<base>::GCFG_    canfd_base_t<base>::GCFG;
	template <uint32_t base> typename canfd_base_t<base>::GCR_     canfd_base_t<base>::GCR;
	template <uint32_t base> typename canfd_base_t<base>::GSR_     canfd_base_t<base>::GSR;
	template <uint32_t base> typename canfd_base_t<base>::GESR_    canfd_base_t<base>::GESR;
	template <uint32_t base> typename canfd_base_t<base>::TISR_    canfd_base_t<base>::TISR;
	template <uint32_t base> typename canfd_base_t<base>::TSCR_    canfd_base_t<base>::TSCR;
	template <uint32_t base> typename canfd_base_t<base>::AFCR_    canfd_base_t<base>::AFCR;
	template <uint32_t base> typename canfd_base_t<base>::AFCFG_   canfd_base_t<base>::AFCFG;
	template <uint32_t base> typename canfd_base_t<base>::AFLIDR_  canfd_base_t<base>::AFLIDR;
	template <uint32_t base> typename canfd_base_t<base>::AFLMASK_ canfd_base_t<base>::AFLMASK;
	template <uint32_t base> typename canfd_base_t<base>::AFLPTR0_ canfd_base_t<base>::AFLPTR0;
	template <uint32_t base> typename canfd_base_t<base>::AFLPTR1_ canfd_base_t<base>::AFLPTR1;
	template <uint32_t base> typename canfd_base_t<base>::RMCR_    canfd_base_t<base>::RMCR;
	template <uint32_t base> typename canfd_base_t<base>::RMNDR_   canfd_base_t<base>::RMNDR;
	template <uint32_t base> typename canfd_base_t<base>::RFCR0_   canfd_base_t<base>::RFCR0;
	template <uint32_t base> typename canfd_base_t<base>::RFCR1_   canfd_base_t<base>::RFCR1;
	template <uint32_t base> typename canfd_base_t<base>::RFSR0_   canfd_base_t<base>::RFSR0;
	template <uint32_t base> typename canfd_base_t<base>::RFSR1_   canfd_base_t<base>::RFSR1;
	template <uint32_t base> typename canfd_base_t<base>::RFPCR0_  canfd_base_t<base>::RFPCR0;
	template <uint32_t base> typename canfd_base_t<base>::RFPCR1_  canfd_base_t<base>::RFPCR1;
	template <uint32_t base> typename canfd_base_t<base>::CFCR0_   canfd_base_t<base>::CFCR0;
	template <uint32_t base> typename canfd_base_t<base>::CFSR0_   canfd_base_t<base>::CFSR0;
	template <uint32_t base> typename canfd_base_t<base>::CFPCR0_  canfd_base_t<base>::CFPCR0;
	template <uint32_t base> typename canfd_base_t<base>::FESR_    canfd_base_t<base>::FESR;
	template <uint32_t base> typename canfd_base_t<base>::FFSR_    canfd_base_t<base>::FFSR;
	template <uint32_t base> typename canfd_base_t<base>::FMLSR_   canfd_base_t<base>::FMLSR;
	template <uint32_t base> typename canfd_base_t<base>::RFISR_   canfd_base_t<base>::RFISR;
	template <uint32_t base> typename canfd_base_t<base>::DTCR_    canfd_base_t<base>::DTCR;
	template <uint32_t base> typename canfd_base_t<base>::DTSR_    canfd_base_t<base>::DTSR;
	template <uint32_t base> typename canfd_base_t<base>::TMCR_    canfd_base_t<base>::TMCR;
	template <uint32_t base> typename canfd_base_t<base>::TMSR_    canfd_base_t<base>::TMSR;
	template <uint32_t base> typename canfd_base_t<base>::TMTRSR0_ canfd_base_t<base>::TMTRSR0;
	template <uint32_t base> typename canfd_base_t<base>::TMARSR0_ canfd_base_t<base>::TMARSR0;
	template <uint32_t base> typename canfd_base_t<base>::TMTCSR0_ canfd_base_t<base>::TMTCSR0;
	template <uint32_t base> typename canfd_base_t<base>::TMTASR0_ canfd_base_t<base>::TMTASR0;
	template <uint32_t base> typename canfd_base_t<base>::TMIER0_  canfd_base_t<base>::TMIER0;
	template <uint32_t base> typename canfd_base_t<base>::TQCR0_   canfd_base_t<base>::TQCR0;
	template <uint32_t base> typename canfd_base_t<base>::TQSR0_   canfd_base_t<base>::TQSR0;
	template <uint32_t base> typename canfd_base_t<base>::TQPCR0_  canfd_base_t<base>::TQPCR0;
	template <uint32_t base> typename canfd_base_t<base>::THCR_    canfd_base_t<base>::THCR;
	template <uint32_t base> typename canfd_base_t<base>::THSR_    canfd_base_t<base>::THSR;
	template <uint32_t base> typename canfd_base_t<base>::THACR0_  canfd_base_t<base>::THACR0;
	template <uint32_t base> typename canfd_base_t<base>::THACR1_  canfd_base_t<base>::THACR1;
	template <uint32_t base> typename canfd_base_t<base>::THPCR_   canfd_base_t<base>::THPCR;
	template <uint32_t base> typename canfd_base_t<base>::GRCR_    canfd_base_t<base>::GRCR;
	template <uint32_t base> typename canfd_base_t<base>::GTMCR_   canfd_base_t<base>::GTMCR;
	template <uint32_t base> typename canfd_base_t<base>::GTMER_   canfd_base_t<base>::GTMER;
	template <uint32_t base> typename canfd_base_t<base>::GFDCFG_  canfd_base_t<base>::GFDCFG;
	template <uint32_t base> typename canfd_base_t<base>::GTMLKR_  canfd_base_t<base>::GTMLKR;
	template <uint32_t base> typename canfd_base_t<base>::RTPAR_   canfd_base_t<base>::RTPAR;
	template <uint32_t base> typename canfd_base_t<base>::AFIGSR_  canfd_base_t<base>::AFIGSR;
	template <uint32_t base> typename canfd_base_t<base>::AFIGER_  canfd_base_t<base>::AFIGER;
	template <uint32_t base> typename canfd_base_t<base>::RMIER_   canfd_base_t<base>::RMIER;


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
		typedef eccsr_t<base + 0x00> ECCSR_;
		static  ECCSR_ ECCSR;


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
		typedef ectmr_t<base + 0x04> ECTMR_;
		static  ECTMR_ ECTMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ECC デコーダテストデータレジスタ (ECTDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x0C> ECTDR_;
		static  ECTDR_ ECTDR;


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
		typedef ecear_t<base + 0x10> ECEAR_;
		static  ECEAR_ ECEAR;
	};
	template <uint32_t base> typename canfd_ecc_t<base>::ECCSR_ canfd_ecc_t<base>::ECCSR;
	template <uint32_t base> typename canfd_ecc_t<base>::ECTMR_ canfd_ecc_t<base>::ECTMR;
	template <uint32_t base> typename canfd_ecc_t<base>::ECTDR_ canfd_ecc_t<base>::ECTDR;
	template <uint32_t base> typename canfd_ecc_t<base>::ECEAR_ canfd_ecc_t<base>::ECEAR;


#if defined(SIG_RX26T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CANFD モジュール (CANFD ECC コア) for RX26T
		@param[in]	base	ベースアドレス
		@param[in]	ecc		ECC 制御アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, uint32_t ecc>
	struct canfd_t : canfd_base_t<base>, canfd_ecc_t<ecc> {

		static constexpr auto PERIPHERAL = peripheral::CANFD;	///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::PCLKB;	///< クロック周波数

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
	typedef canfd_t<0x000A'8000, 0x000E'D000> CANFD;
#endif
}
