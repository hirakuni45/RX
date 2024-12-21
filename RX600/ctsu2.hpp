#pragma once
//=========================================================================//
/*!	@file
	@brief	Capacitive Touch Sensing Unit 2 / 静電容量式タッチセンサ 2 @n
			・RX140 @n
			・RX260/RX261 (CTSU2SL)
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
		@brief	CTSU2L class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu2l_t {

		static constexpr auto PERIPHERAL = peripheral::CTSU;	///< ペリフェラル型
		static constexpr auto WRI = ICU::VECTOR::CTSUWR;		///< チャネル毎の設定レジスタ書き込み要求割り込み
		static constexpr auto RDI = ICU::VECTOR::CTSURD;		///< 測定データ転送要求割り込み
		static constexpr auto FNI = ICU::VECTOR::CTSUFN;		///< 測定終了割り込み

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CTSU2 ポート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PORT : uint8_t {
			TS0,		///< P32
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

			TSCAP = 36,	///< PC4
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
			case PORT::TS0:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = ena;
				break;
			case PORT::TS1:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = sel;  // ok
				PORT3::PMR.B1 = ena;
				break;
			case PORT::TS2:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = ena;
				break;
			case PORT::TS3:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;  // ok
				PORT2::PMR.B7 = ena;
				break;
			case PORT::TS4:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = ena;
				break;
			case PORT::TS5:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case PORT::TS6:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = ena;
				break;
			case PORT::TS7:
				PORTH::PMR.B3 = 0;
				MPC::PH3PFS.PSEL = sel;  // ok
				PORTH::PMR.B3 = ena;
				break;
			case PORT::TS8:
				PORTH::PMR.B2 = 0;
				MPC::PH2PFS.PSEL = sel;  // ok
				PORTH::PMR.B2 = ena;
				break;
			case PORT::TS9:
				PORTH::PMR.B1 = 0;
				MPC::PH1PFS.PSEL = sel;  // ok
				PORTH::PMR.B1 = ena;
				break;
			case PORT::TS10:
				PORTH::PMR.B0 = 0;
				MPC::PH0PFS.PSEL = sel;  // ok
				PORTH::PMR.B0 = ena;
				break;
			case PORT::TS11:
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = sel;  // ok
				PORT5::PMR.B5 = ena;
				break;
			case PORT::TS12:
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = sel;  // ok
				PORT5::PMR.B4 = ena;
				break;
			case PORT::TS13:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel; // ok
				PORTC::PMR.B7 = ena;
				break;
			case PORT::TS14:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = ena;
				break;
			case PORT::TS15:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;  // ok
				PORTC::PMR.B5 = ena;
				break;
			case PORT::TS16:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;  // ok
				PORTC::PMR.B3 = ena;
				break;
			case PORT::TS17:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = sel;  // ok
				PORTC::PMR.B2 = ena;
				break;
			case PORT::TS18:
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = sel;  // ok
				PORTB::PMR.B7 = ena;
				break;
			case PORT::TS19:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = ena;
				break;
			case PORT::TS20:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;  // ok
				PORTB::PMR.B5 = ena;
				break;
			case PORT::TS21:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = sel;  // ok
				PORTB::PMR.B4 = ena;
				break;
			case PORT::TS22:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;  // ok
				PORTB::PMR.B3 = ena;
				break;
			case PORT::TS23:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = ena;
				break;
			case PORT::TS24:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = ena;
				break;
			case PORT::TS25:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = ena;
				break;
			case PORT::TS26:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case PORT::TS27:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = ena;
				break;
			case PORT::TS28:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = ena;
				break;
			case PORT::TS29:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case PORT::TS30:
				PORTA::PMR.B2 = 0;
				MPC::PA2PFS.PSEL = sel;  // ok
				PORTA::PMR.B2 = ena;
				break;
			case PORT::TS31:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;  // ok
				PORTA::PMR.B1 = ena;
				break;
			case PORT::TS32:
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = sel;  // ok
				PORTA::PMR.B0 = ena;
				break;
			case PORT::TS33:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = sel;  // ok
				PORTE::PMR.B4 = ena;
				break;
			case PORT::TS34:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = sel;  // ok
				PORTE::PMR.B3 = ena;
				break;
			case PORT::TS35:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = sel;  // ok
				PORTE::PMR.B2 = ena;
				break;
			case PORT::TSCAP:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;  // ok
				PORTC::PMR.B4 = ena;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 制御レジスタ A (CTSUCRA)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsucra_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     STRT;
			bit_rw_t <io_, bitpos::B1>     CAP;
			bit_rw_t <io_, bitpos::B2>     SNZ;

			bit_rw_t <io_, bitpos::B4>     INIT;
			bit_rw_t <io_, bitpos::B5>     PUMPON;
			bits_rw_t<io_, bitpos::B6, 2>  TXVSEL;

			bit_rw_t <io_, bitpos::B8>     PON;
			bit_rw_t <io_, bitpos::B9>     CSW;
			bit_rw_t <io_, bitpos::B10>    ATUNE0;
			bit_rw_t <io_, bitpos::B11>    ATUNE1;
			bits_rw_t<io_, bitpos::B12, 2> CLK;

			bit_rw_t <io_, bitpos::B14>    MD0;
			bit_rw_t <io_, bitpos::B15>    MD1;

			bit_rw_t <io_, bitpos::B17>    ATUNE2;
			bits_rw_t<io_, bitpos::B18, 2> LOAD;
			bits_rw_t<io_, bitpos::B20, 2> POSEL;
			bit_rw_t <io_, bitpos::B22>    SDPSEL;
			bit_rw_t <io_, bitpos::B23>    PCSEL;
			bits_rw_t<io_, bitpos::B24, 6> STCLK;
			bit_rw_t <io_, bitpos::B30>    DCMODE;
			bit_rw_t <io_, bitpos::B31>    DCBACK;
		};
		static inline ctsucra_t<base + 0x00> CTSUCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 制御レジスタ B (CTSUCRB)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsucrb_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  PRRATIO;
			bits_rw_t<io_, bitpos::B4, 2>  PRMODE;
			bit_rw_t <io_, bitpos::B6>     SOFF;
			bit_rw_t <io_, bitpos::B7>     PROFF;
			bits_rw_t<io_, bitpos::B8, 8>  SST;

			bits_rw_t<io_, bitpos::B24, 3> SSMOD;

			bits_rw_t<io_, bitpos::B28, 2> SSCNT;
		};
		static inline ctsucrb_t<base + 0x04> CTSUCRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 計測チャネルレジスタ (CTSUMCH)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsumch_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  MCH0;

			bits_rw_t<io_, bitpos::B8, 6>  MCH1;

			bit_rw_t <io_, bitpos::B16>    MCA0;
			bit_rw_t <io_, bitpos::B17>    MCA1;
			bit_rw_t <io_, bitpos::B18>    MCA2;
			bit_rw_t <io_, bitpos::B19>    MCA3;
		};
		static inline ctsumch_t<base + 0x08> CTSUMCH;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ A (CTSUCHACA)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchaca_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CHAC0;
			bit_rw_t <io_, bitpos::B1>     CHAC1;
			bit_rw_t <io_, bitpos::B2>     CHAC2;
			bit_rw_t <io_, bitpos::B3>     CHAC3;
			bit_rw_t <io_, bitpos::B4>     CHAC4;
			bit_rw_t <io_, bitpos::B5>     CHAC5;
			bit_rw_t <io_, bitpos::B6>     CHAC6;
			bit_rw_t <io_, bitpos::B7>     CHAC7;
			bit_rw_t <io_, bitpos::B8>     CHAC8;
			bit_rw_t <io_, bitpos::B9>     CHAC9;
			bit_rw_t <io_, bitpos::B10>    CHAC10;
			bit_rw_t <io_, bitpos::B11>    CHAC11;
			bit_rw_t <io_, bitpos::B12>    CHAC12;
			bit_rw_t <io_, bitpos::B13>    CHAC13;
			bit_rw_t <io_, bitpos::B14>    CHAC14;
			bit_rw_t <io_, bitpos::B15>    CHAC15;
			bit_rw_t <io_, bitpos::B16>    CHAC16;
			bit_rw_t <io_, bitpos::B17>    CHAC17;
			bit_rw_t <io_, bitpos::B18>    CHAC18;
			bit_rw_t <io_, bitpos::B19>    CHAC19;
			bit_rw_t <io_, bitpos::B20>    CHAC20;
			bit_rw_t <io_, bitpos::B21>    CHAC21;
			bit_rw_t <io_, bitpos::B22>    CHAC22;
			bit_rw_t <io_, bitpos::B23>    CHAC23;
			bit_rw_t <io_, bitpos::B24>    CHAC24;
			bit_rw_t <io_, bitpos::B25>    CHAC25;
			bit_rw_t <io_, bitpos::B26>    CHAC26;
			bit_rw_t <io_, bitpos::B27>    CHAC27;
			bit_rw_t <io_, bitpos::B28>    CHAC28;
			bit_rw_t <io_, bitpos::B29>    CHAC29;
			bit_rw_t <io_, bitpos::B30>    CHAC30;
			bit_rw_t <io_, bitpos::B31>    CHAC31;
		};
		static inline ctsuchaca_t<base + 0x0C> CTSUCHACA;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ B (CTSUCHACB)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchacb_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CHAC32;
			bit_rw_t <io_, bitpos::B1>     CHAC33;
			bit_rw_t <io_, bitpos::B2>     CHAC34;
			bit_rw_t <io_, bitpos::B3>     CHAC35;
		};
		static inline ctsuchacb_t<base + 0x10> CTSUCHACB;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ A (CTSUCHTRCA)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchtrca_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CHTRC0;
			bit_rw_t <io_, bitpos::B1>     CHTRC1;
			bit_rw_t <io_, bitpos::B2>     CHTRC2;
			bit_rw_t <io_, bitpos::B3>     CHTRC3;
			bit_rw_t <io_, bitpos::B4>     CHTRC4;
			bit_rw_t <io_, bitpos::B5>     CHTRC5;
			bit_rw_t <io_, bitpos::B6>     CHTRC6;
			bit_rw_t <io_, bitpos::B7>     CHTRC7;
			bit_rw_t <io_, bitpos::B8>     CHTRC8;
			bit_rw_t <io_, bitpos::B9>     CHTRC9;
			bit_rw_t <io_, bitpos::B10>    CHTRC10;
			bit_rw_t <io_, bitpos::B11>    CHTRC11;
			bit_rw_t <io_, bitpos::B12>    CHTRC12;
			bit_rw_t <io_, bitpos::B13>    CHTRC13;
			bit_rw_t <io_, bitpos::B14>    CHTRC14;
			bit_rw_t <io_, bitpos::B15>    CHTRC15;
			bit_rw_t <io_, bitpos::B16>    CHTRC16;
			bit_rw_t <io_, bitpos::B17>    CHTRC17;
			bit_rw_t <io_, bitpos::B18>    CHTRC18;
			bit_rw_t <io_, bitpos::B19>    CHTRC19;
			bit_rw_t <io_, bitpos::B20>    CHTRC20;
			bit_rw_t <io_, bitpos::B21>    CHTRC21;
			bit_rw_t <io_, bitpos::B22>    CHTRC22;
			bit_rw_t <io_, bitpos::B23>    CHTRC23;
			bit_rw_t <io_, bitpos::B24>    CHTRC24;
			bit_rw_t <io_, bitpos::B25>    CHTRC25;
			bit_rw_t <io_, bitpos::B26>    CHTRC26;
			bit_rw_t <io_, bitpos::B27>    CHTRC27;
			bit_rw_t <io_, bitpos::B28>    CHTRC28;
			bit_rw_t <io_, bitpos::B29>    CHTRC29;
			bit_rw_t <io_, bitpos::B30>    CHTRC30;
			bit_rw_t <io_, bitpos::B31>    CHTRC31;
		};
		static inline ctsuchtrca_t<base + 0x14> CTSUCHTRCA;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ B (CTSUCHTRCB)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchtrcb_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CHTRC32;
			bit_rw_t <io_, bitpos::B1>     CHTRC33;
			bit_rw_t <io_, bitpos::B2>     CHTRC34;
			bit_rw_t <io_, bitpos::B3>     CHTRC35;
		};
		static inline ctsuchtrcb_t<base + 0x18> CTSUCHTRCB;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ステータスレジスタ (CTSUSR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsusr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  MFC;

			bit_rw_t <io_, bitpos::B5>     ICOMPRST;
			bit_ro_t <io_, bitpos::B6>     ICOMP1;
			bit_ro_t <io_, bitpos::B7>     ICOMP0;
			bits_ro_t<io_, bitpos::B8, 3>  STC;

			bit_ro_t <io_, bitpos::B12>    DTSR;
			bit_rw_t <io_, bitpos::B13>    SCOVF;
			bit_rw_t <io_, bitpos::B14>    UCOVF;
			bit_ro_t <io_, bitpos::B15>    PS;
		};
		static inline ctsusr_t<base + 0x1C> CTSUSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサオフセットレジスタ (CTSUSO)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuso_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10> SO;
			bits_rw_t<io_, bitpos::B11, 8> SNUM;

			bits_rw_t<io_, bitpos::B20, 4> SSDIV;
			bits_rw_t<io_, bitpos::B24, 8> SDPA;
		};
		static inline ctsuso_t<base + 0x20> CTSUSO;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサカウンタ (CTSUSCNT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuscnt_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16> SC;
			bits_rw_t<io_, bitpos::B16, 16> UC;
		};
		static inline ctsuscnt_t<base + 0x24> CTSUSCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU キャリブレーションレジスタ (CTSUCALIB)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsucalib_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B2>     TSOD;
			bit_rw_t <io_, bitpos::B3>     DRV;
			bits_rw_t<io_, bitpos::B4, 2>  CLKSEL;
			bit_rw_t <io_, bitpos::B6>     SUCLKEN;
			bit_rw_t <io_, bitpos::B7>     TSOC;
			bit_rw_t <io_, bitpos::B8>     CNTRDSEL;
			bit_rw_t <io_, bitpos::B9>     IOC;

			bit_rw_t <io_, bitpos::B11>    DCOFF;
			bit_rw_t <io_, bitpos::B12>    ICCSEL;

			bit_rw_t <io_, bitpos::B24>    DACMSEL;
			bit_rw_t <io_, bitpos::B25>    DACCARRY;
			bit_rw_t <io_, bitpos::B26>    SUMSEL;
			bit_rw_t <io_, bitpos::B27>    SUCARRY;
			bit_rw_t <io_, bitpos::B28>    DACCLK;
			bit_rw_t <io_, bitpos::B29>    CCOCLK;
			bit_rw_t <io_, bitpos::B30>    CCOCALIB;
			bit_rw_t <io_, bitpos::B31>    TXREV;
		};
		static inline ctsucalib_t<base + 0x28> CTSUCALIB;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサユニットクロック制御レジスタ A (CTSUSUCLKA)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsusuclka_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  SUADJ0;
			bits_rw_t<io_, bitpos::B8,  8>  SUMULTI0;
			bits_rw_t<io_, bitpos::B16, 8>  SUADJ1;
			bits_rw_t<io_, bitpos::B24, 8>  SUMULTI1;
		};
		static inline ctsusuclka_t<base + 0x2C> CTSUSUCLKA;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサユニットクロック制御レジスタ B (CTSUSUCLKB)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsusuclkb_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  SUADJ2;
			bits_rw_t<io_, bitpos::B8,  8>  SUMULTI2;
			bits_rw_t<io_, bitpos::B16, 8>  SUADJ3;
			bits_rw_t<io_, bitpos::B24, 8>  SUMULTI3;
		};
		static inline ctsusuclkb_t<base + 0x30> CTSUSUCLKB;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU トリミングレジスタ A (CTSUTRIMA)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsutrima_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  RTRIM;
			bits_rw_t<io_, bitpos::B8,  8>  DACTRIM;
			bits_rw_t<io_, bitpos::B16, 8>  SUADJD;
			bits_rw_t<io_, bitpos::B24, 8>  TRESULT4;
		};
		static inline ctsutrima_t<0x007F'C3A4> CTSUTRIMA;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU トリミングレジスタ B (CTSUTRIMB)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsutrimb_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  TRESULT0;
			bits_rw_t<io_, bitpos::B8,  8>  TRESULT1;
			bits_rw_t<io_, bitpos::B16, 8>  TRESULT2;
			bits_rw_t<io_, bitpos::B24, 8>  TRESULT3;
		};
		static inline ctsutrimb_t<0x007F'C3A8> CTSUTRIMB;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  静電容量式タッチセンサ CTSU2SL クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu2sl_t : public ctsu2l_t<base> {

		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU オプション設定レジスタ (CTSUOPT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuopt_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CCOCFEN;

			bit_rw_t <io_, bitpos::B4>      DTCLESS;
			bit_rw_t <io_, bitpos::B5>      MTUCFEN;

			bit_rw_t <io_, bitpos::B8>      AJFEN;

			bits_rw_t<io_, bitpos::B16, 4>  SCACTB;
		};
		static inline ctsuopt_t<base + 0x40> CTSUOPT;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU センサカウンタ自動補正テーブルアクセスレジスタ (CTSUSCNTACT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuscntact_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  SCNTACCOEFF;
			bits_rw_t<io_, bitpos::B16, 16>  SCNTACCOUNT;
		};
		static inline ctsuscntact_t<base + 0x44> CTSUSCNTACT;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 自動判定制御レジスタ (CTSUAJCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuajcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>   TLOT;
			bits_rw_t<io_, bitpos::B8,  8>   THOT;
			bit_rw_t <io_, bitpos::B16>      BLINI;

			bits_rw_t<io_, bitpos::B20, 2>   JC;

			bits_rw_t<io_, bitpos::B24, 4>   AJMMAT;
			bits_rw_t<io_, bitpos::B28, 4>   AJBMAT;
		};
		static inline ctsuajcr_t<base + 0x58> CTSUAJCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU しきい値レジスタ (CTSUAJTHR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuajthr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  AJTHL;
			bits_rw_t<io_, bitpos::B16, 16>  AJTHH;
		};
		static inline ctsuajthr_t<base + 0x5C> CTSUAJTHR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 移動平均結果レジスタ (CTSUAJMMAR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuajmmar_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>   AJMMAT;

			bits_rw_t<io_, bitpos::B5, 27>   AJMMR;
		};
		static inline ctsuajmmar_t<base + 0x60> CTSUAJMMAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ベースライン平均中間結果レジスタ (CTSUAJBLACT)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<base + 0x64> CTSUAJBLACT;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ベースライン平均結果レジスタ (CTSUAJBLAR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuajblar_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  AJBLAC;
			bits_rw_t<io_, bitpos::B16, 16>  AJBLAR;
		};
		static inline ctsuajblar_t<base + 0x68> CTSUAJBLAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU 自動判定結果レジスタ (CTSUAJRR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuajrr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>       TJR0;
			bit_rw_t <io_, bitpos::B1>       TJR1;
			bit_rw_t <io_, bitpos::B2>       TJR2;
			bit_rw_t <io_, bitpos::B3>       TJR3;
			bit_rw_t <io_, bitpos::B4>       FJR;

			bits_rw_t<io_, bitpos::B8, 8>    SJCCR;
		};
		static inline ctsuajrr_t<base + 0x6C> CTSUAJRR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU A/D コンバータ接続制御レジスタ (CTSUADCC)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuadcc_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>       CTADCS;
		};
		static inline ctsuadcc_t<0x00A'0700> CTSUADCC;
	};

#if defined(SIG_RX140)
	// RX140 ROM 容量 64K CTSU2L
//	static inline ctsu2l_t<0x000A'0900> CTSU;
	// RX140 ROM 容量 128K 以上 CTSU2SL
	static inline ctsu2sl_t<0x000A'0900> CTSU;
#elif defined(SIG_RX260) || defined(SIG_RX261)
	static inline ctsu2sl_t<0x000A'0900> CTSU;
#endif
}
