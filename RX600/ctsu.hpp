#pragma once
//=========================================================================//
/*!	@file
	@brief	静電容量式タッチセンサ (CTSU) 定義
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
		@brief  静電容量式タッチセンサ CTSU クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ctsu_t {

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

		static constexpr auto PERIPHERAL = peripheral::CTSU;	///< ペリフェラル型
		static constexpr auto WRI = ICU::VECTOR::CTSUWR;		///< チャネル毎の設定レジスタ書き込み要求割り込み
		static constexpr auto RDI = ICU::VECTOR::CTSURD;		///< 測定データ転送要求割り込み
		static constexpr auto FNI = ICU::VECTOR::CTSUFN;		///< 測定終了割り込み


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
		typedef ctsucr0_t<base + 0x00> CTSUCR0_;
		static CTSUCR0_ CTSUCR0;


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
		typedef ctsucr1_t<base + 0x01> CTSUCR1_;
		static CTSUCR1_ CTSUCR1;


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
		typedef ctsusdprs_t<base + 0x02> CTSUSDPRS_;
		static CTSUSDPRS_ CTSUSDPRS;


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
		typedef ctsusst_t<base + 0x03> CTSUSST_;
		static CTSUSST_ CTSUSST;


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
		typedef ctsumch0_t<base + 0x04> CTSUMCH0_;
		static CTSUMCH0_ CTSUMCH0;


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
		typedef ctsumch1_t<base + 0x05> CTSUMCH1_;
		static CTSUMCH1_ CTSUMCH1;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル有効制御レジスタ n (CTSUCHAC[n]) (n = 0 ～ 4) @n
					※冗長なので、[]オペレーターで対応
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchac_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) noexcept { if(j <= 4) { io_::index = j; } }

			void enable(PORT port, bool ena = true) noexcept
			{
				if(port != PORT::TSCAP) {
					auto n = static_cast<uint8_t>(port);
					set_index(n >> 3);
					auto tmp = io_::read();
					if(ena) {
						tmp |= 1 << (n & 7);
					} else {
						tmp &= ~(1 << (n & 7));
					}
					io_::write(tmp);
				}
			}

			bit_rw_t <io_, bitpos::B0>     CTSUCHAC0;
			bit_rw_t <io_, bitpos::B1>     CTSUCHAC1;
			bit_rw_t <io_, bitpos::B2>     CTSUCHAC2;
			bit_rw_t <io_, bitpos::B3>     CTSUCHAC3;
			bit_rw_t <io_, bitpos::B4>     CTSUCHAC4;
			bit_rw_t <io_, bitpos::B5>     CTSUCHAC5;
			bit_rw_t <io_, bitpos::B6>     CTSUCHAC6;
			bit_rw_t <io_, bitpos::B7>     CTSUCHAC7;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef ctsuchac_t<base + 0x06> CTSUCHAC_;
		static CTSUCHAC_ CTSUCHAC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU チャネル送受信制御レジスタ n (CTSUCHTRC[n]) (n = 0 ～ 4) @n
					※冗長なので、[]オペレーターで対応
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsuchtrc_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) noexcept { if(j <= 4) { io_::index = j; } }

			void enable(PORT port, bool ena = true) noexcept
			{
				if(port != PORT::TSCAP) {
					auto n = static_cast<uint8_t>(port);
					set_index(n >> 3);
					auto tmp = io_::read();
					if(ena) {
						tmp |= 1 << (n & 7);
					} else {
						tmp &= ~(1 << (n & 7));
					}
					io_::write(tmp);
				}
			}

			bit_rw_t <io_, bitpos::B0>     CTSUCHTRC0;
			bit_rw_t <io_, bitpos::B1>     CTSUCHTRC1;
			bit_rw_t <io_, bitpos::B2>     CTSUCHTRC2;
			bit_rw_t <io_, bitpos::B3>     CTSUCHTRC3;
			bit_rw_t <io_, bitpos::B4>     CTSUCHTRC4;
			bit_rw_t <io_, bitpos::B5>     CTSUCHTRC5;
			bit_rw_t <io_, bitpos::B6>     CTSUCHTRC6;
			bit_rw_t <io_, bitpos::B7>     CTSUCHTRC7;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef ctsuchtrc_t<base + 0x0B> CTSUCHTRC_;
		static CTSUCHTRC_ CTSUCHTRC;


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
		typedef ctsudclkc_t<base + 0x10> CTSUDCLKC_;
		static CTSUDCLKC_ CTSUDCLKC;


		//-----------------------------------------------------------------//
		/*!
			@brief  CTSU ステータスレジスタ (CTSUST)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ctsust_t : public rw8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
			
			bits_ro_t<in_, bitpos::B0, 3>  CTSUSTC;

			bit_ro_t <in_, bitpos::B4>     CTSUDTSR;
			bit_rw_t <io_, bitpos::B5>     CTSUSOVF;
			bit_rw_t <io_, bitpos::B6>     CTSUROVF;
			bit_ro_t <in_, bitpos::B7>     CTSUPS;
		};
		typedef ctsust_t<base + 0x11> CTSUST_;
		static CTSUST_ CTSUST;


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
		typedef ctsussc_t<base + 0x12> CTSUSSC_;
		static CTSUSSC_ CTSUSSC;


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
		typedef ctsuso0_t<base + 0x14> CTSUSO0_;
		static CTSUSO0_ CTSUSO0;


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
		typedef ctsuso1_t<base + 0x16> CTSUSO1_;
		static CTSUSO1_ CTSUSO1;


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
		typedef ctsusc_t<base + 0x18> CTSUSC_;
		static CTSUSC_ CTSUSC;


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
		typedef ctsurc_t<base + 0x1A> CTSURC_;
		static CTSURC_ CTSURC;


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
		typedef ctsuerrs_t<base + 0x1C> CTSUERRS_;
		static CTSUERRS_ CTSUERRS;
	};
	template <uint32_t base> typename ctsu_t<base>::CTSUCR0_   ctsu_t<base>::CTSUCR0;
	template <uint32_t base> typename ctsu_t<base>::CTSUCR1_   ctsu_t<base>::CTSUCR1;
	template <uint32_t base> typename ctsu_t<base>::CTSUSDPRS_ ctsu_t<base>::CTSUSDPRS;
	template <uint32_t base> typename ctsu_t<base>::CTSUSST_   ctsu_t<base>::CTSUSST;
	template <uint32_t base> typename ctsu_t<base>::CTSUMCH0_  ctsu_t<base>::CTSUMCH0;
	template <uint32_t base> typename ctsu_t<base>::CTSUMCH1_  ctsu_t<base>::CTSUMCH1;
	template <uint32_t base> typename ctsu_t<base>::CTSUCHAC_  ctsu_t<base>::CTSUCHAC;
	template <uint32_t base> typename ctsu_t<base>::CTSUCHTRC_ ctsu_t<base>::CTSUCHTRC;
	template <uint32_t base> typename ctsu_t<base>::CTSUDCLKC_ ctsu_t<base>::CTSUDCLKC;
	template <uint32_t base> typename ctsu_t<base>::CTSUST_    ctsu_t<base>::CTSUST;
	template <uint32_t base> typename ctsu_t<base>::CTSUSSC_   ctsu_t<base>::CTSUSSC;
	template <uint32_t base> typename ctsu_t<base>::CTSUSO0_   ctsu_t<base>::CTSUSO0;
	template <uint32_t base> typename ctsu_t<base>::CTSUSO1_   ctsu_t<base>::CTSUSO1;
	template <uint32_t base> typename ctsu_t<base>::CTSUSC_    ctsu_t<base>::CTSUSC;
	template <uint32_t base> typename ctsu_t<base>::CTSURC_    ctsu_t<base>::CTSURC;
	template <uint32_t base> typename ctsu_t<base>::CTSUERRS_  ctsu_t<base>::CTSUERRS;

	typedef ctsu_t<0x0008'0980> CTSU;
}
