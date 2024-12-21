#pragma once
//=========================================================================//
/*!	@file
	@brief	Capacitive Touch Sensing Unit / 静電容量式タッチセンサ @n
			・RX113 @n
			・RX130 @n
			・RX231 @n
			・RX671
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CTSU base class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 制御レジスタ 0 (CTSUCR0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsucr0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CTSUSTRT;
			bit_rw_t <io_, bitpos::B1>     CTSUCAP;
			bit_rw_t <io_, bitpos::B2>     CTSUSNZ;
			bit_rw_t <io_, bitpos::B3>     CTSUIOC;
			bit_rw_t <io_, bitpos::B4>     CTSUINIT;
		};
		static inline ctsucr0_t<base + 0x00> CTSUCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 制御レジスタ 1 (CTSUCR1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsucr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CTSUPON;
			bit_rw_t <io_, bitpos::B1>     CTSUCSW;
			bit_rw_t <io_, bitpos::B2>     CTSUATUNE0;
			bit_rw_t <io_, bitpos::B3>     CTSUATUNE1;
			bits_rw_t<io_, bitpos::B4, 2>  CTSUCLK;
			bits_rw_t<io_, bitpos::B6, 2>  CTSUMD;
		};
		static inline ctsucr1_t<base + 0x01> CTSUCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 同期ノイズ低減設定レジスタ (CTSUSDPRS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsusdprs_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			
			bits_rw_t<io_, bitpos::B0, 4>  CTSUPRRATIO;
			bits_rw_t<io_, bitpos::B4, 2>  CTSUPRMODE;
			bit_rw_t <io_, bitpos::B6>     CTSUSOFF;
		};
		static inline ctsusdprs_t<base + 0x02> CTSUSDPRS;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサ安定待ち時間レジスタ (CTSUSST)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsusst_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			
			bits_rw_t<io_, bitpos::B0, 8>  CTSUSST;
		};
		static inline ctsusst_t<base + 0x03> CTSUSST;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 計測チャネルレジスタ 0 (CTSUMCH0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsumch0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			
			bits_rw_t<io_, bitpos::B0, 6>  CTSUMCH0;
		};
		static inline ctsumch0_t<base + 0x04> CTSUMCH0;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 計測チャネルレジスタ 1 (CTSUMCH1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsumch1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			
			bits_rw_t<io_, bitpos::B0, 6>  CTSUMCH1;
		};
		static inline ctsumch1_t<base + 0x05> CTSUMCH1;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 高域ノイズ低減制御レジスタ (CTSUDCLKC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsudclkc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			
			bits_rw_t<io_, bitpos::B0, 2>  CTSUSSMOD;

			bits_rw_t<io_, bitpos::B4, 2>  CTSUSSCNT;
		};
		static inline ctsudclkc_t<base + 0x10> CTSUDCLKC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ステータスレジスタ (CTSUST)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsust_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			
			bits_ro_t<io_, bitpos::B0, 3>  CTSUSTC;

			bit_ro_t <io_, bitpos::B4>     CTSUDTSR;
			bit_rw_t <io_, bitpos::B5>     CTSUSOVF;
			bit_rw_t <io_, bitpos::B6>     CTSUROVF;
			bit_ro_t <io_, bitpos::B7>     CTSUPS;
		};
		static inline ctsust_t<base + 0x11> CTSUST;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 高域ノイズ低減スペクトラム拡散制御レジスタ (CTSUSSC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsussc_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 4>  CTSUSSDIV;
		};
		static inline ctsussc_t<base + 0x12> CTSUSSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサオフセットレジスタ 0 (CTSUSO0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuso0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10> CTSUSO;
			bits_rw_t<io_, bitpos::B10, 6> CTSUSNUM;
		};
		static inline ctsuso0_t<base + 0x14> CTSUSO0;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサオフセットレジスタ 1 (CTSUSO1)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuso1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8> CTSURICOA;
			bits_rw_t<io_, bitpos::B8,  5> CTSUSDPA;
			bits_rw_t<io_, bitpos::B13, 2> CTSUICOG;
		};
		static inline ctsuso1_t<base + 0x16> CTSUSO1;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサカウンタ (CTSUSC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsusc_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> CTSUSC;
		};
		static inline ctsusc_t<base + 0x18> CTSUSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU リファレンスカウンタ (CTSURC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsurc_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> CTSURC;
		};
		static inline ctsurc_t<base + 0x1A> CTSURC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU エラーステータスレジスタ (CTSUERRS)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuerrs_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CTSUSPMD;
			bit_rw_t <io_, bitpos::B2>     CTSUTSOD;
			bit_rw_t <io_, bitpos::B3>     CTSUDRV;

			bit_rw_t <io_, bitpos::B7>     CTSUTSOC;

			bit_rw_t <io_, bitpos::B15>    CTSUICOMP;
		};
		static inline ctsuerrs_t<base + 0x1C> CTSUERRS;
	};


	struct ctsu_utils {

		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ n (CTSUCHACn) (n = 0 ～ 4)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchacn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CTSUCHAC0;
			bit_rw_t <io_, bitpos::B1>     CTSUCHAC1;
			bit_rw_t <io_, bitpos::B2>     CTSUCHAC2;
			bit_rw_t <io_, bitpos::B3>     CTSUCHAC3;
			bit_rw_t <io_, bitpos::B4>     CTSUCHAC4;
			bit_rw_t <io_, bitpos::B5>     CTSUCHAC5;
			bit_rw_t <io_, bitpos::B6>     CTSUCHAC6;
			bit_rw_t <io_, bitpos::B7>     CTSUCHAC7;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ n (CTSUCHTRCn) (n = 0 ～ 4)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchtrcn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CTSUCHTRC0;
			bit_rw_t <io_, bitpos::B1>     CTSUCHTRC1;
			bit_rw_t <io_, bitpos::B2>     CTSUCHTRC2;
			bit_rw_t <io_, bitpos::B3>     CTSUCHTRC3;
			bit_rw_t <io_, bitpos::B4>     CTSUCHTRC4;
			bit_rw_t <io_, bitpos::B5>     CTSUCHTRC5;
			bit_rw_t <io_, bitpos::B6>     CTSUCHTRC6;
			bit_rw_t <io_, bitpos::B7>     CTSUCHTRC7;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル制御クラス
			@param[in]	base	ベース・アドレス
			@param[in]	PORT	ポート型
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base, typename PORT>
		struct ctsuchctrl_t {

			bool get(PORT port) noexcept
			{
				if(port != PORT::TSCAP) {
					auto n = static_cast<uint8_t>(port);
					auto adr = base + (n >> 3);
					auto tmp = rd8_(adr);
					return tmp & (1 << (n & 7));
				} else {
					return 0;
				}
			}

			void set(PORT port, bool val = true) noexcept
			{
				if(port != PORT::TSCAP) {
					auto n = static_cast<uint8_t>(port);
					auto adr = base + (n >> 3);
					auto tmp = rd8_(adr);
					if(val) {
						tmp |= 1 << (n & 7);
					} else {
						tmp &= ~(1 << (n & 7));
					}
					wr8_(adr, tmp);
				}
			}

			bool operator () (PORT port) {
				return get(port);
			}
		};
	};

#if defined(SIG_RX113)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX113 静電容量式タッチセンサ CTSU クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu_t : public ctsu_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::CTSU;	///< ペリフェラル型
		static constexpr auto WRI = ICU::VECTOR::CTSUWR;		///< チャネル毎の設定レジスタ書き込み要求割り込み
		static constexpr auto RDI = ICU::VECTOR::CTSURD;		///< 測定データ転送要求割り込み
		static constexpr auto FNI = ICU::VECTOR::CTSUFN;		///< 測定終了割り込み

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CTSU ポート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PORT : uint8_t {
			TSCAP = 12,	///< P26
			TS0 = 0,	///< P07
			TS1,		///< P04
			TS2,		///< P02
			TS3,		///< PJ3
			TS4,		///< P25
			TS5,		///< P24
			TS6,		///< P23
			TS7,		///< P22
			TS8,		///< P21
			TS9,		///< P20
			TS10,		///< P27
			TS11,		///< P26
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ポートを有効にする
			@param[in]	port	CTSU ポート
			@param[in]	ena		無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(PORT port, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			uint8_t sel = ena ? 0b1'1001 : 0;
			switch(port) {
			case PORT::TSCAP:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;
				PORT2::PMR.B6 = ena;
				break;
			case PORT::TS0:
				PORT0::PMR.B7 = 0;
				MPC::P07PFS.PSEL = sel;
				PORT0::PMR.B7 = ena;
				break;
			case PORT::TS1:
				PORT0::PMR.B4 = 0;
				MPC::P04PFS.PSEL = sel;
				PORT0::PMR.B4 = ena;
				break;
			case PORT::TS2:
				PORT0::PMR.B2 = 0;
				MPC::P02PFS.PSEL = sel;
				PORT0::PMR.B2 = ena;
				break;
			case PORT::TS3:
				PORTJ::PMR.B3 = 0;
				MPC::PJ3PFS.PSEL = sel;
				PORTJ::PMR.B3 = ena;
				break;
			case PORT::TS4:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;
				PORT2::PMR.B5 = ena;
				break;
			case PORT::TS5:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;
				PORT2::PMR.B4 = ena;
				break;
			case PORT::TS6:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = ena;
				break;
			case PORT::TS7:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B2 = ena;
				break;
			case PORT::TS8:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;
				PORT2::PMR.B1 = ena;
				break;
			case PORT::TS9:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;
				PORT2::PMR.B0 = ena;
				break;
			case PORT::TS10:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;
				PORT2::PMR.B7 = ena;
				break;
			case PORT::TS11:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;
				PORT2::PMR.B6 = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ n (CTSUCHACn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchacn_t<base + 0x06> CTSUCHAC0_;
		static inline CTSUCHAC0_ CTSUCHAC0;
		static inline ctsu_utils::ctsuchacn_t<base + 0x07> CTSUCHAC1;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x06, PORT> CTSUCHAC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ n (CTSUCHTRCn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0B> CTSUCHTRC0_;
		static inline CTSUCHTRC0_ CTSUCHTRC0;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0C> CTSUCHTRC1;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x08, PORT> CTSUCHTRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 基準電流調整レジスタ (CTSUTRMR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007F'FFBE> CTSUTRMR;
	};

#elif defined(SIG_RX130)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX130 静電容量式タッチセンサ CTSUa クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu_t : public ctsu_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::CTSU;	///< ペリフェラル型
		static constexpr auto WRI = ICU::VECTOR::CTSUWR;		///< チャネル毎の設定レジスタ書き込み要求割り込み
		static constexpr auto RDI = ICU::VECTOR::CTSURD;		///< 測定データ転送要求割り込み
		static constexpr auto FNI = ICU::VECTOR::CTSUFN;		///< 測定終了割り込み

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CTSU ポート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PORT : uint8_t {
			TSCAP = 36,	///< PC4
			TS0 = 0,	///< P32
			TS1,		///< P31
			TS2,		///< P30
			TS3,		///< P27
			TS4,		///< P26
			TS5,		///< P15
			TS6,		///< P14
			TS7,		///< PH3
			TS8,		///< PH2
			TS9,		///< PH1
			TS10,		///< PH0
			TS11,		///< P55
			TS12,		///< P54
			TS13,		///< PC7
			TS14,		///< PC6
			TS15,		///< PC5
			TS16,		///< PC3
			TS17,		///< PC2
			TS18,		///< PB7
			TS19,		///< PB6
			TS20,		///< PB5
			TS21,		///< PB4
			TS22,		///< PB3
			TS23,		///< PB2
			TS24,		///< PB1
			TS25,		///< PB0
			TS26,		///< PA6
			TS27,		///< PA5
			TS28,		///< PA4
			TS29,		///< PA3
			TS30,		///< PA2
			TS31,		///< PA1
			TS32,		///< PA0
			TS33,		///< PE4
			TS34,		///< PE3
			TS35,		///< PE2
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ポートを有効にする
			@param[in]	port	CTSU ポート
			@param[in]	ena		無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(PORT port, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			uint8_t sel = ena ? 0b1'1001 : 0;
			switch(port) {
			case PORT::TSCAP:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;
				PORTC::PMR.B4 = ena;
				break;
			case PORT::TS0:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;
				PORT3::PMR.B2 = ena;
				break;
			case PORT::TS1:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = sel;
				PORT3::PMR.B1 = ena;
				break;
			case PORT::TS2:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = sel;
				PORT3::PMR.B0 = ena;
				break;
			case PORT::TS3:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;
				PORT2::PMR.B7 = ena;
				break;
			case PORT::TS4:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;
				PORT2::PMR.B6 = ena;
				break;
			case PORT::TS5:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;
				PORT1::PMR.B5 = ena;
				break;
			case PORT::TS6:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;
				PORT1::PMR.B4 = ena;
				break;
			case PORT::TS7:
				PORTH::PMR.B3 = 0;
				MPC::PH3PFS.PSEL = sel;
				PORTH::PMR.B3 = ena;
				break;
			case PORT::TS8:
				PORTH::PMR.B2 = 0;
				MPC::PH2PFS.PSEL = sel;
				PORTH::PMR.B2 = ena;
				break;
			case PORT::TS9:
				PORTH::PMR.B1 = 0;
				MPC::PH1PFS.PSEL = sel;
				PORTH::PMR.B1 = ena;
				break;
			case PORT::TS10:
				PORTH::PMR.B0 = 0;
				MPC::PH0PFS.PSEL = sel;
				PORTH::PMR.B0 = ena;
				break;
			case PORT::TS11:
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = sel;
				PORT5::PMR.B5 = ena;
				break;
			case PORT::TS12:
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = sel;
				PORT5::PMR.B4 = ena;
				break;
			case PORT::TS13:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;
				PORTC::PMR.B7 = ena;
				break;
			case PORT::TS14:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = ena;
				break;
			case PORT::TS15:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B5 = ena;
				break;
			case PORT::TS16:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;
				PORTC::PMR.B3 = ena;
				break;
			case PORT::TS17:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = sel;
				PORTC::PMR.B2 = ena;
				break;
			case PORT::TS18:
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = sel;
				PORTB::PMR.B7 = ena;
				break;
			case PORT::TS19:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = ena;
				break;
			case PORT::TS20:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = ena;
				break;
			case PORT::TS21:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = sel;
				PORTB::PMR.B4 = ena;
				break;
			case PORT::TS22:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;
				PORTB::PMR.B3 = ena;
				break;
			case PORT::TS23:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = ena;
				break;
			case PORT::TS24:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = ena;
				break;
			case PORT::TS25:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = ena;
				break;
			case PORT::TS26:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;
				PORTA::PMR.B6 = ena;
				break;
			case PORT::TS27:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;
				PORTA::PMR.B5 = ena;
				break;
			case PORT::TS28:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;
				PORTA::PMR.B4 = ena;
				break;
			case PORT::TS29:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = sel;
				PORTA::PMR.B3 = ena;
				break;
			case PORT::TS30:
				PORTA::PMR.B2 = 0;
				MPC::PA2PFS.PSEL = sel;
				PORTA::PMR.B2 = ena;
				break;
			case PORT::TS31:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;
				PORTA::PMR.B1 = ena;
				break;
			case PORT::TS32:
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = sel;
				PORTA::PMR.B0 = ena;
				break;
			case PORT::TS33:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = sel;
				PORTE::PMR.B4 = ena;
				break;
			case PORT::TS34:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = sel;
				PORTE::PMR.B3 = ena;
				break;
			case PORT::TS35:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = sel;
				PORTE::PMR.B2 = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ n (CTSUCHACn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchacn_t<base + 0x06> CTSUCHAC0_;
		static inline CTSUCHAC0_ CTSUCHAC0;
		static inline ctsu_utils::ctsuchacn_t<base + 0x07> CTSUCHAC1;
		static inline ctsu_utils::ctsuchacn_t<base + 0x08> CTSUCHAC2;
		static inline ctsu_utils::ctsuchacn_t<base + 0x09> CTSUCHAC3;
		static inline ctsu_utils::ctsuchacn_t<base + 0x0A> CTSUCHAC4;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x06, PORT> CTSUCHAC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ n (CTSUCHTRCn) (n = 0 ～ 3)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0B> CTSUCHTRC0_;
		static inline CTSUCHTRC0_ CTSUCHTRC0;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0C> CTSUCHTRC1;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0D> CTSUCHTRC2;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0E> CTSUCHTRC3;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0F> CTSUCHTRC4;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x08, PORT> CTSUCHTRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 基準電流調整レジスタ (CTSUTRMR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x007F'FFBE> CTSUTRMR;
	};

#elif defined(SIG_RX231)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX231 静電容量式タッチセンサ CTSU クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu_t : public ctsu_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::CTSU;	///< ペリフェラル型
		static constexpr auto WRI = ICU::VECTOR::CTSUWR;		///< チャネル毎の設定レジスタ書き込み要求割り込み
		static constexpr auto RDI = ICU::VECTOR::CTSURD;		///< 測定データ転送要求割り込み
		static constexpr auto FNI = ICU::VECTOR::CTSUFN;		///< 測定終了割り込み

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CTSU ポート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PORT : uint8_t {
			TSCAP = 36,	///< PC4
			TS0 = 0,	///< P34
			TS1,		///< P33
			TS2,		///< P27
			TS3,		///< P26
			TS4,		///< P25
			TS5,		///< P24
			TS6,		///< P23
			TS7,		///< P22
			TS8,		///< P21
			TS9,		///< P20
			TS12 = 12,	///< P15
			TS13,		///< P14
			TS15 = 15,	///< P55
			TS16,		///< P54
			TS17,		///< P53
			TS18,		///< P52
			TS19,		///< P51
			TS20,		///< P50
			TS22 = 22,	///< PC6
			TS23,		///< PC5
			TS27 = 27,	///< PC3
			TS30 = 30,	///< PC2
			TS33 = 33,	///< PC1
			TS35 = 35,	///< PC0
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ポートを有効にする
			@param[in]	port	CTSU ポート
			@param[in]	ena		無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(PORT port, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			uint8_t sel = ena ? 0b1'1001 : 0;
			switch(port) {
			case PORT::TSCAP:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;
				PORTC::PMR.B4 = ena;
				break;
			case PORT::TS0:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = sel;
				PORT3::PMR.B4 = ena;
				break;
			case PORT::TS1:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;
				PORT3::PMR.B3 = ena;
				break;
			case PORT::TS2:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;
				PORT2::PMR.B7 = ena;
				break;
			case PORT::TS3:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;
				PORT2::PMR.B6 = ena;
				break;
			case PORT::TS4:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;
				PORT2::PMR.B5 = ena;
				break;
			case PORT::TS5:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;
				PORT2::PMR.B4 = ena;
				break;
			case PORT::TS6:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = ena;
				break;
			case PORT::TS7:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B2 = ena;
				break;
			case PORT::TS8:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;
				PORT2::PMR.B1 = ena;
				break;
			case PORT::TS9:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;
				PORT2::PMR.B0 = ena;
				break;
			case PORT::TS12:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;
				PORT1::PMR.B5 = ena;
				break;
			case PORT::TS13:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;
				PORT1::PMR.B4 = ena;
				break;
			case PORT::TS15:
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = sel;
				PORT5::PMR.B5 = ena;
				break;
			case PORT::TS16:
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = sel;
				PORT5::PMR.B4 = ena;
				break;
			case PORT::TS17:
				PORT5::PMR.B3 = 0;
				MPC::P53PFS.PSEL = sel;
				PORT5::PMR.B3 = ena;
				break;
			case PORT::TS18:
				PORT5::PMR.B2 = 0;
				MPC::P52PFS.PSEL = sel;
				PORT5::PMR.B2 = ena;
				break;
			case PORT::TS19:
				PORT5::PMR.B1 = 0;
				MPC::P51PFS.PSEL = sel;
				PORT5::PMR.B1 = ena;
				break;
			case PORT::TS20:
				PORT5::PMR.B0 = 0;
				MPC::P50PFS.PSEL = sel;
				PORT5::PMR.B0 = ena;
				break;
			case PORT::TS22:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = ena;
				break;
			case PORT::TS23:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B5 = ena;
				break;
			case PORT::TS27:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;
				PORTC::PMR.B3 = ena;
				break;
			case PORT::TS30:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = sel;
				PORTC::PMR.B2 = ena;
				break;
			case PORT::TS33:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = sel;
				PORTC::PMR.B1 = ena;
				break;
			case PORT::TS35:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = sel;
				PORTC::PMR.B0 = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ n (CTSUCHACn) (n = 0 ～ 4)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchacn_t<base + 0x06> CTSUCHAC0_;
		static inline CTSUCHAC0_ CTSUCHAC0;
		static inline ctsu_utils::ctsuchacn_t<base + 0x07> CTSUCHAC1;
		static inline ctsu_utils::ctsuchacn_t<base + 0x08> CTSUCHAC2;
		static inline ctsu_utils::ctsuchacn_t<base + 0x09> CTSUCHAC3;
		static inline ctsu_utils::ctsuchacn_t<base + 0x0A> CTSUCHAC4;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x06, PORT> CTSUCHAC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ n (CTSUCHTRCn) (n = 0 ～ 4)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0B> CTSUCHTRC0_;
		static inline CTSUCHTRC0_ CTSUCHTRC0;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0C> CTSUCHTRC1;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0D> CTSUCHTRC2;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0E> CTSUCHTRC3;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0F> CTSUCHTRC4;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x08, PORT> CTSUCHTRC;
	};

#elif defined(SIG_RX671)

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX671 静電容量式タッチセンサ CTSUa クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu_t : public ctsu_base_t<base> {

		typedef ctsu_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::CTSU;	///< ペリフェラル型
		static constexpr auto WRI = ICU::SELECTB::CTSUWR;		///< チャネル毎の設定レジスタ書き込み要求割り込み
		static constexpr auto RDI = ICU::SELECTB::CTSURD;		///< 測定データ転送要求割り込み
		static constexpr auto FNI = ICU::SELECTB::CTSUFN;		///< 測定終了割り込み

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CTSU ポート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PORT : uint8_t {
			TSCAP = 17,	///< PC4
			TS0 = 0,	///< P34
			TS1,		///< P33
			TS2,		///< P27
			TS3,		///< P26
			TS4,		///< P25
			TS5,		///< P24
			TS6,		///< P23
			TS7,		///< P22
			TS8,		///< P21
			TS9,		///< P20
			TS10,		///< P15
			TS11,		///< P14
			TS12,		///< P53
			TS13,		///< PC6
			TS14,		///< PC5
			TS15,		///< PC1
			TS16,		///< PC0
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ポートを有効にする
			@param[in]	port	CTSU ポート
			@param[in]	ena		無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(PORT port, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			uint8_t sel = ena ? 0b1'1001 : 0;
			switch(port) {
			case PORT::TSCAP:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;
				PORTC::PMR.B4 = ena;
				break;
			case PORT::TS0:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = sel;
				PORT3::PMR.B4 = ena;
				break;
			case PORT::TS1:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;
				PORT3::PMR.B3 = ena;
				break;
			case PORT::TS2:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;
				PORT2::PMR.B7 = ena;
				break;
			case PORT::TS3:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;
				PORT2::PMR.B6 = ena;
				break;
			case PORT::TS4:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;
				PORT2::PMR.B5 = ena;
				break;
			case PORT::TS5:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;
				PORT2::PMR.B4 = ena;
				break;
			case PORT::TS6:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = ena;
				break;
			case PORT::TS7:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B2 = ena;
				break;
			case PORT::TS8:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;
				PORT2::PMR.B1 = ena;
				break;
			case PORT::TS9:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;
				PORT2::PMR.B0 = ena;
				break;
			case PORT::TS10:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;
				PORT1::PMR.B5 = ena;
				break;
			case PORT::TS11:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;
				PORT1::PMR.B4 = ena;
				break;
			case PORT::TS12:
				PORT5::PMR.B3 = 0;
				MPC::P53PFS.PSEL = sel;
				PORT5::PMR.B3 = ena;
				break;
			case PORT::TS13:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = ena;
				break;
			case PORT::TS14:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B5 = ena;
				break;
			case PORT::TS15:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = sel;
				PORTC::PMR.B1 = ena;
				break;
			case PORT::TS16:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = sel;
				PORTC::PMR.B0 = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ n (CTSUCHACn) (n = 0 ～ 2)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchacn_t<base + 0x06> CTSUCHAC0_;
		static inline CTSUCHAC0_ CTSUCHAC0;
		static inline ctsu_utils::ctsuchacn_t<base + 0x07> CTSUCHAC1;
		static inline ctsu_utils::ctsuchacn_t<base + 0x08> CTSUCHAC2;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x06, PORT> CTSUCHAC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ n (CTSUCHTRCn) (n = 0 ～ 2)
		*/
		//-----------------------------------------------------------------//
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0B> CTSUCHTRC0_;
		static inline CTSUCHTRC0_ CTSUCHTRC0;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0C> CTSUCHTRC1;
		typedef ctsu_utils::ctsuchtrcn_t<base + 0x0D> CTSUCHTRC2;
		static inline ctsu_utils::ctsuchctrl_t<base + 0x08, PORT> CTSUCHTRC;
	};
#endif
	typedef ctsu_t<0x000A'0900> CTSU;
}
