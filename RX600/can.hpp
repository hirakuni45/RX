#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・CAN 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/can_frame.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN ベース・モジュール（CAN）
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct can_t {

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
		static inline ctlr_t<base + 0x0640> CTLR;


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
		static inline bcr_t<base + 0x0644> BCR;


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
		static inline mkr_t<base + 0x0200> MKR;


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
		static inline fidcrx_t<base + 0x0220> FIDCR0;
		static inline fidcrx_t<base + 0x0224> FIDCR1;


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

			void set(uint32_t idx) {
				auto v = rd32_(io_::address);
				v |= 1 << idx;
				wr32_(io_::address, v);
			}

			bool get(uint32_t idx) {
				auto v = rd32_(io_::address);
				return (v & (1 << idx)) != 0;
			}
		};
		static inline mbn_t<base + 0x0228> MKIVLR;


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
		static inline mb_t MB;


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス割り込み許可レジスタ（ MIER ）
		*/
		//-----------------------------------------------------------------//
		static inline mbn_t<base + 0x022C> MIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  メッセージ制御レジスタ j（ MCTL[j] ）（ j ＝ 0 ～ 31 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mctl_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 32) { io_::index = j; } }

			bit_rw_t <io_, bitpos::B0>  SENTDATA;  // Send mode
			bit_rw_t <io_, bitpos::B0>  NEWDATA;   // Recv mode
			bit_rw_t <io_, bitpos::B1>  TRMACTIVE; // Send mode
			bit_rw_t <io_, bitpos::B1>  INVALDATA; // Recv mode
			bit_rw_t <io_, bitpos::B2>  TRMABT;    // Send mode
			bit_rw_t <io_, bitpos::B2>  TMSGLOST;  // Recv mode

			bit_rw_t <io_, bitpos::B4>  ONESHOT;

			bit_rw_t <io_, bitpos::B6>  RECREQ;
			bit_rw_t <io_, bitpos::B7>  TRMREQ;

			mctl_t& operator [] (uint32_t idx)
			{
				set_index(idx);
				return *this;
			}
		};
		static inline mctl_t<base + 0x0620> MCTL;


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
		static inline rfcr_t<base + 0x0648> RFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ポインタ制御レジスタ（ RFPCR ）
		*/
		//-----------------------------------------------------------------//
		static inline wo8_t<base + 0x0649>  RFPCR;


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
		static inline tfcr_t<base + 0x064A> TFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO ポインタ制御レジスタ（ TFPCR ）
		*/
		//-----------------------------------------------------------------//
		static inline wo8_t<base + 0x064B>  TFPCR;


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
		static inline str_t<base + 0x0642> STR;


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
		static inline msmr_t<base + 0x0654> MSMR;


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
		static inline mssr_t<base + 0x0652> MSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルサーチサポートレジスタ（ CSSR ）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x0651>  CSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  アクセプタンスフィルタサポートレジスタ（ AFSR ）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x0656>  AFSR;


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
		static inline eier_t<base + 0x064C> EIER;


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
		static inline eifr_t<base + 0x064D> EIFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信エラーカウントレジスタ（ RECR ）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x064E>  RECR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信エラーカウントレジスタ（ TECR ）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x064F>  TECR;


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
		static inline ecsr_t<base + 0x0650> ECSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイムスタンプレジスタ（ TSR ）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x0654>  TSR;


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
		static inline tcr_t<base + 0x0658> TCR;
	};


#if defined(SIG_RX631) || defined(SIG_RX63N) || defined(SIG_RX63T) || defined(SIG_RX63T_S)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN モジュール（CAN 通常割り込み、GROUP0 型）
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
		ICU::VECTOR rxf, ICU::VECTOR txf, ICU::VECTOR rxm, ICU::VECTOR txm, ICU::GROUP0 ers>
	struct can_norm_t : can_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::PCLKB;	///< クロック周波数
		static constexpr auto RXF = rxf;	///< RXF 割り込みベクター
		static constexpr auto TXF = txf;	///< TXF 割り込みベクター
		static constexpr auto RXM = rxm;	///< RXM 割り込みベクター
		static constexpr auto TXM = txm;	///< TXM 割り込みベクター
		static constexpr auto ERS = ers;	///< ERS 割り込みベクター
	};
	typedef can_norm_t<0x0009'1200, peripheral::CAN1,
		ICU::VECTOR::RXF1, ICU::VECTOR::TXF1,
		ICU::VECTOR::RXM1, ICU::VECTOR::TXM1, ICU::GROUP0::ERS1> CAN1;
#if defined(SIG_RX631) || defined(SIG_RX63N)
	typedef can_norm_t<0x0009'0200, peripheral::CAN0,
		ICU::VECTOR::RXF0, ICU::VECTOR::TXF0,
		ICU::VECTOR::RXM0, ICU::VECTOR::TXM0, ICU::GROUP0::ERS0> CAN0;
	typedef can_norm_t<0x0009'2200, peripheral::CAN2,
		ICU::VECTOR::RXF2, ICU::VECTOR::TXF2,
		ICU::VECTOR::RXM2, ICU::VECTOR::TXM2, ICU::GROUP0::ERS2> CAN2;
#endif

#elif defined(SIG_RX621) || defined(SIG_RX62N)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN モジュール（CAN 通常割り込み型）
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
		ICU::VECTOR rxf, ICU::VECTOR txf, ICU::VECTOR rxm, ICU::VECTOR txm, ICU::VECTOR ers>
	struct can_norm_t : can_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::PCLK;	///< クロック周波数
		static constexpr auto RXF = rxf;	///< RXF 割り込みベクター
		static constexpr auto TXF = txf;	///< TXF 割り込みベクター
		static constexpr auto RXM = rxm;	///< RXM 割り込みベクター
		static constexpr auto TXM = txm;	///< TXM 割り込みベクター
		static constexpr auto ERS = ers;	///< ERS 割り込みベクター
	};
	typedef can_norm_t<0x0009'0200, peripheral::CAN,
		ICU::VECTOR::RXF0, ICU::VECTOR::TXF0,
		ICU::VECTOR::RXM0, ICU::VECTOR::TXM0, ICU::VECTOR::ERS0> CAN;

#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR rxf, ICU::VECTOR txf, ICU::VECTOR rxm, ICU::VECTOR txm, ICU::GROUPBE0 ers>
	struct can_norm_t : can_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::PCLKB;	///< クロック周波数
		static constexpr auto RXF = rxf;	///< RXF 割り込みベクター
		static constexpr auto TXF = txf;	///< TXF 割り込みベクター
		static constexpr auto RXM = rxm;	///< RXM 割り込みベクター
		static constexpr auto TXM = txm;	///< TXM 割り込みベクター
		static constexpr auto ERS = ers;	///< ERS 割り込みベクター
	};
	typedef can_norm_t<0x0009'0200, peripheral::CAN0,
		ICU::VECTOR::RXF0, ICU::VECTOR::TXF0,
		ICU::VECTOR::RXM0, ICU::VECTOR::TXM0, ICU::GROUPBE0::ERS0> CAN0;

#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72N) || defined(SIG_RX72M)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CAN モジュール（CAN 選択割り込み型 + グループ割り込み BE0）
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxf		受信 FIFO 割り込み
		@param[in]	txf		送信 FIFO 割り込み
		@param[in]	rxm		メールボックス受信割り込み
		@param[in]	txm		メールボックス送信割り込み
		@param[in]	ers		エラー割り込み（BE0 グループ割り込み）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::SELECTB rxf, ICU::SELECTB txf, ICU::SELECTB rxm, ICU::SELECTB txm, ICU::GROUPBE0 ers>
	struct can_seli_t : can_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		static constexpr auto PCLK = clock_profile::PCLKB;	///< クロック周波数
		static constexpr auto RXF = rxf;	///< RXF 割り込みベクター
		static constexpr auto TXF = txf;	///< TXF 割り込みベクター
		static constexpr auto RXM = rxm;	///< RXM 割り込みベクター
		static constexpr auto TXM = txm;	///< TXM 割り込みベクター
		static constexpr auto ERS = ers;	///< ERS 割り込みベクター
	};

	typedef can_seli_t<0x0009'0200, peripheral::CAN0,
		ICU::SELECTB::RXF0, ICU::SELECTB::TXF0,
		ICU::SELECTB::RXM0, ICU::SELECTB::TXM0, ICU::GROUPBE0::ERS0> CAN0;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef can_seli_t<0x0009'1200, peripheral::CAN1,
		ICU::SELECTB::RXF1, ICU::SELECTB::TXF1,
		ICU::SELECTB::RXM1, ICU::SELECTB::TXM1, ICU::GROUPBE0::ERS1> CAN1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef can_seli_t<0x0009'2200, peripheral::CAN2,
		ICU::SELECTB::RXF2, ICU::SELECTB::TXF2,
		ICU::SELECTB::RXM2, ICU::SELECTB::TXM2, ICU::GROUPBE0::ERS2> CAN2;
#endif
#endif
// note: RX65x/RX72x CAN0, CAN1
}
