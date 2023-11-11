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

			bit_ro_t <io_, bitpos::B0>      BEDF;
			bit_ro_t <io_, bitpos::B1>      EWDF;
			bit_ro_t <io_, bitpos::B2>      EPDF;
			bit_ro_t <io_, bitpos::B3>      BOEDF;
			bit_ro_t <io_, bitpos::B4>      BORDF;
			bit_ro_t <io_, bitpos::B5>      OLDF;
			bit_ro_t <io_, bitpos::B6>      BLDF;
			bit_ro_t <io_, bitpos::B7>      ALDF;
			bit_ro_t <io_, bitpos::B8>      SEDF;
			bit_ro_t <io_, bitpos::B9>      FEDF;
			bit_ro_t <io_, bitpos::B10>     AEDF;
			bit_ro_t <io_, bitpos::B11>     CEDF;
			bit_ro_t <io_, bitpos::B12>     B1BDF;
			bit_ro_t <io_, bitpos::B13>     B0EDF;
			bit_ro_t <io_, bitpos::B14>     ADEDF;

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








#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  マスクレジスタ k （ MKR[k] ）（ k = 0 ～ 7 ）@n
					※MKR0 ～ 7 は廃止
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mkr_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 4; } }

			bits_rw_t<io_, bitpos::B0,  18>  EID;
			bits_rw_t<io_, bitpos::B18, 11>  SID;

			mkr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef mkr_t<base + 0x0200> MKR_;
		static  MKR_ MKR;


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
	template <uint32_t base> typename canfd_base_t<base>::NBCR_  canfd_base_t<base>::NBCR;
	template <uint32_t base> typename canfd_base_t<base>::CHCR_  canfd_base_t<base>::CHCR;
	template <uint32_t base> typename canfd_base_t<base>::CHSR_  canfd_base_t<base>::CHSR;
	template <uint32_t base> typename canfd_base_t<base>::CHESR_ canfd_base_t<base>::CHESR;
	template <uint32_t base> typename canfd_base_t<base>::DBCR_  canfd_base_t<base>::DBCR;






#if 0
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN モジュール（CAN 通常割り込み型 + グループ割り込み BE0）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxf		受信 FIFO 割り込み
		@param[in]	txf		送信 FIFO 割り込み
		@param[in]	rxm		メールボックス受信割り込み
		@param[in]	txm		メールボックス送信割り込み
		@param[in]	ers		エラー割り込み（BE0 グループ割り込み）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR rxf, ICU::VECTOR txf, ICU::VECTOR rxm, ICU::VECTOR txm, ICU::GROUPBE0 ers>
	struct canfd_t : canfd_base_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::PCLKB;	///< クロック周波数
		static constexpr auto RXF = rxf;	///< RXF 割り込みベクター
		static constexpr auto TXF = txf;	///< TXF 割り込みベクター
		static constexpr auto RXM = rxm;	///< RXM 割り込みベクター
		static constexpr auto TXM = txm;	///< TXM 割り込みベクター
		static constexpr auto ERS = ers;	///< ERS 割り込みベクター
	};
	typedef canfd_t<0x000A'0800, peripheral::CANFD0,
		ICU::VECTOR::RXF0, ICU::VECTOR::TXF0,
		ICU::VECTOR::RXM0, ICU::VECTOR::TXM0, ICU::GROUPBE0::ERS0> CAN0;
#endif
}
