#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・ポート・レジスター定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include <tuple>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PDR, PODR, PIDR, PMR, PCR, DSCR）
		@param[in]	base	ベースアドレス
		@param[in]	option	オプション
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, class option>
	struct port_t : public option {

		static const uint32_t base_address_ = base;	///< ベースアドレス


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ（PDR）
		*/
		//-----------------------------------------------------------------//
		typedef basic_rw_t<rw8_t<base + 0x00> > PDR_;
		static PDR_ PDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート出力データレジスタ（PODR）
		*/
		//-----------------------------------------------------------------//
		typedef basic_rw_t<rw8_t<base + 0x20> > PODR_;
		static PODR_ PODR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート入力データレジスタ（PIDR）
		*/
		//-----------------------------------------------------------------//
		typedef basic_ro_t<ro8_t<base + 0x40> > PIDR_;
		static PIDR_ PIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートモードレジスタ（PMR）
		*/
		//-----------------------------------------------------------------//
		typedef basic_rw_t<rw8_t<base + 0x60> > PMR_;
		static PMR_ PMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御レジスタ（PCR）
		*/
		//-----------------------------------------------------------------//
		typedef basic_rw_t<rw8_t<base + 0xC0> > PCR_;
		static PCR_ PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  駆動能力制御レジスタ（DSCR）
		*/
		//-----------------------------------------------------------------//
		typedef basic_rw_t<rw8_t<base + 0xE0> > DSCR_;
		static DSCR_ DSCR;
	};
	template <uint32_t base, class option> const uint32_t port_t<base, option>::base_address_;
	template <uint32_t base, class option>
		typename port_t<base, option>::PDR_  port_t<base, option>::PDR;
	template <uint32_t base, class option>
		typename port_t<base, option>::PODR_ port_t<base, option>::PODR;
	template <uint32_t base, class option>
		typename port_t<base, option>::PIDR_ port_t<base, option>::PIDR;
	template <uint32_t base, class option>
		typename port_t<base, option>::PMR_  port_t<base, option>::PMR;
	template <uint32_t base, class option>
		typename port_t<base, option>::PCR_  port_t<base, option>::PCR;
	template <uint32_t base, class option>
		typename port_t<base, option>::DSCR_ port_t<base, option>::DSCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ODR 無し
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base> struct odr_xx_t { };


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ODR 全体定義 (ODR0, ODR1) @n
				※RX64M, RX71M
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct odr_oo_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御レジスタ 0（ODR0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct odr0_t : public rw8_t<ofs> {

			typedef rw8_t<ofs>  io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> B0;
			bit_rw_t<io_, bitpos::B2> B2;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B3> B3;
#endif
			bit_rw_t<io_, bitpos::B4> B4;
			bit_rw_t<io_, bitpos::B6> B6;
		};
		typedef odr0_t<base + 0> ODR0_;
		static ODR0_ ODR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御レジスタ 1（ODR1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct odr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs>  io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> B0;
			bit_rw_t<io_, bitpos::B2> B2;
			bit_rw_t<io_, bitpos::B4> B4;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B6> B6;
#endif
		};
		typedef odr1_t<base + 1> ODR1_;
		static ODR1_ ODR1;
	};
	template <uint32_t base> typename odr_oo_t<base>::ODR0_ odr_oo_t<base>::ODR0;
	template <uint32_t base> typename odr_oo_t<base>::ODR1_ odr_oo_t<base>::ODR1;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ODR 全体定義 (ODR0)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct odr_ox_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御レジスタ 0（ODR0）@n
					※RX24T
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct odr0_t : public rw8_t<ofs> {

			typedef rw8_t<ofs>  io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> B0;
			bit_rw_t<io_, bitpos::B2> B2;
			bit_rw_t<io_, bitpos::B4> B4;
			bit_rw_t<io_, bitpos::B6> B6;
		};
		typedef odr0_t<base> ODR0_;
		static ODR0_ ODR0;
	};
	template <uint32_t base> typename odr_ox_t<base>::ODR0_ ODR0;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef port_t<0x0008C000, odr_oo_t<0x0008C080> > PORT0;
	typedef port_t<0x0008C001, odr_oo_t<0x0008C082> > PORT1;
	typedef port_t<0x0008C002, odr_oo_t<0x0008C084> > PORT2;
	typedef port_t<0x0008C003, odr_oo_t<0x0008C086> > PORT3;
	typedef port_t<0x0008C004, odr_oo_t<0x0008C088> > PORT4;
	typedef port_t<0x0008C005, odr_oo_t<0x0008C08A> > PORT5;
	typedef port_t<0x0008C006, odr_oo_t<0x0008C08C> > PORT6;
	typedef port_t<0x0008C007, odr_oo_t<0x0008C08E> > PORT7;
	typedef port_t<0x0008C008, odr_oo_t<0x0008C090> > PORT8;
	typedef port_t<0x0008C009, odr_oo_t<0x0008C092> > PORT9;
	typedef port_t<0x0008C00A, odr_oo_t<0x0008C094> > PORTA;
	typedef port_t<0x0008C00B, odr_oo_t<0x0008C096> > PORTB;
	typedef port_t<0x0008C00C, odr_oo_t<0x0008C098> > PORTC;
	typedef port_t<0x0008C00D, odr_oo_t<0x0008C09A> > PORTD;
	typedef port_t<0x0008C00E, odr_oo_t<0x0008C09C> > PORTE;
	typedef port_t<0x0008C00F, odr_oo_t<0x0008C09E> > PORTF;
	typedef port_t<0x0008C010, odr_oo_t<0x0008C0A0> > PORTG;
	typedef port_t<0x0008C012, odr_oo_t<0x0008C0A4> > PORTJ;
#elif defined(SIG_RX63T)
	typedef port_t<0x0008C000, odr_oo_t<0x0008C080> > PORT0;
	typedef port_t<0x0008C001, odr_oo_t<0x0008C082> > PORT1;
	typedef port_t<0x0008C002, odr_oo_t<0x0008C084> > PORT2;
	typedef port_t<0x0008C003, odr_oo_t<0x0008C086> > PORT3;
	typedef port_t<0x0008C004, odr_oo_t<0x0008C088> > PORT4;
	typedef port_t<0x0008C005, odr_oo_t<0x0008C08A> > PORT5;
	typedef port_t<0x0008C006, odr_oo_t<0x0008C08C> > PORT6;
	typedef port_t<0x0008C007, odr_oo_t<0x0008C08E> > PORT7;
	typedef port_t<0x0008C008, odr_oo_t<0x0008C090> > PORT8;
	typedef port_t<0x0008C009, odr_oo_t<0x0008C092> > PORT9;
	typedef port_t<0x0008C00A, odr_oo_t<0x0008C094> > PORTA;
	typedef port_t<0x0008C00B, odr_oo_t<0x0008C096> > PORTB;
	typedef port_t<0x0008C00C, odr_oo_t<0x0008C098> > PORTC;
	typedef port_t<0x0008C00D, odr_oo_t<0x0008C09A> > PORTD;
	typedef port_t<0x0008C00E, odr_oo_t<0x0008C09C> > PORTE;
	typedef port_t<0x0008C00F, odr_oo_t<0x0008C09E> > PORTF;
	typedef port_t<0x0008C010, odr_oo_t<0x0008C0A0> > PORTG;
#elif defined(SIG_RX24T)
//  ODR0  o  o  o  o  x  x  x  o  o  o  o  o  x  o  o  -  -  -
//  ODR1  x  x  o  x  x  x  x  o  x  o  o  o  x  o  o  -  -  -
	typedef port_t<0x0008C000, odr_ox_t<0x0008C080> > PORT0;
	typedef port_t<0x0008C001, odr_ox_t<0x0008C082> > PORT1;
	typedef port_t<0x0008C002, odr_oo_t<0x0008C084> > PORT2;
	typedef port_t<0x0008C003, odr_ox_t<0x0008C086> > PORT3;
	typedef port_t<0x0008C004, odr_xx_t<0x0008C088> > PORT4;
	typedef port_t<0x0008C005, odr_xx_t<0x0008C08A> > PORT5;
	typedef port_t<0x0008C006, odr_xx_t<0x0008C08C> > PORT6;
	typedef port_t<0x0008C007, odr_oo_t<0x0008C08E> > PORT7;
	typedef port_t<0x0008C008, odr_ox_t<0x0008C090> > PORT8;
	typedef port_t<0x0008C009, odr_oo_t<0x0008C092> > PORT9;
	typedef port_t<0x0008C00A, odr_oo_t<0x0008C094> > PORTA;
	typedef port_t<0x0008C00B, odr_oo_t<0x0008C096> > PORTB;
	typedef port_t<0x0008C00D, odr_oo_t<0x0008C09A> > PORTD;
	typedef port_t<0x0008C00E, odr_oo_t<0x0008C09C> > PORTE;
#elif defined(SIG_RX66T)
	typedef port_t<0x0008C000, odr_oo_t<0x0008C080> > PORT0;
	typedef port_t<0x0008C001, odr_oo_t<0x0008C082> > PORT1;
	typedef port_t<0x0008C002, odr_oo_t<0x0008C084> > PORT2;
	typedef port_t<0x0008C003, odr_oo_t<0x0008C086> > PORT3;
	typedef port_t<0x0008C004, odr_oo_t<0x0008C088> > PORT4;
	typedef port_t<0x0008C005, odr_oo_t<0x0008C08A> > PORT5;
	typedef port_t<0x0008C006, odr_oo_t<0x0008C08C> > PORT6;
	typedef port_t<0x0008C007, odr_oo_t<0x0008C08E> > PORT7;
	typedef port_t<0x0008C008, odr_oo_t<0x0008C090> > PORT8;
	typedef port_t<0x0008C009, odr_oo_t<0x0008C092> > PORT9;
	typedef port_t<0x0008C00A, odr_oo_t<0x0008C094> > PORTA;
	typedef port_t<0x0008C00B, odr_oo_t<0x0008C096> > PORTB;
	typedef port_t<0x0008C00C, odr_oo_t<0x0008C098> > PORTC;
	typedef port_t<0x0008C00D, odr_oo_t<0x0008C09A> > PORTD;
	typedef port_t<0x0008C00E, odr_oo_t<0x0008C09C> > PORTE;
	typedef port_t<0x0008C00F, odr_oo_t<0x0008C09E> > PORTF;
	typedef port_t<0x0008C010, odr_oo_t<0x0008C0A0> > PORTG;
#elif defined(SIG_RX72T)
	typedef port_t<0x0008C000, odr_oo_t<0x0008C080> > PORT0;
	typedef port_t<0x0008C001, odr_oo_t<0x0008C082> > PORT1;
	typedef port_t<0x0008C002, odr_oo_t<0x0008C084> > PORT2;
	typedef port_t<0x0008C003, odr_oo_t<0x0008C086> > PORT3;
	typedef port_t<0x0008C004, odr_oo_t<0x0008C088> > PORT4;
	typedef port_t<0x0008C005, odr_oo_t<0x0008C08A> > PORT5;
	typedef port_t<0x0008C006, odr_oo_t<0x0008C08C> > PORT6;
	typedef port_t<0x0008C007, odr_oo_t<0x0008C08E> > PORT7;
	typedef port_t<0x0008C008, odr_oo_t<0x0008C090> > PORT8;
	typedef port_t<0x0008C009, odr_oo_t<0x0008C092> > PORT9;
	typedef port_t<0x0008C00A, odr_oo_t<0x0008C094> > PORTA;
	typedef port_t<0x0008C00B, odr_oo_t<0x0008C096> > PORTB;
	typedef port_t<0x0008C00C, odr_oo_t<0x0008C098> > PORTC;
	typedef port_t<0x0008C00D, odr_oo_t<0x0008C09A> > PORTD;
	typedef port_t<0x0008C00E, odr_oo_t<0x0008C09C> > PORTE;
	typedef port_t<0x0008C00F, odr_oo_t<0x0008C09E> > PORTF;
	typedef port_t<0x0008C010, odr_oo_t<0x0008C0A0> > PORTG;
	typedef port_t<0x0008C011, odr_oo_t<0x0008C0A2> > PORTH;

	typedef port_t<0x0008C013, odr_oo_t<0x0008C0A6> > PORTK;
#else
#  error "port.hpp requires SIG_XXX to be defined"
#endif


	//-------------------------------------------------------------//
	/*!
		@brief  ポートの初期設定
		@param[in]	dir	方向初期化
	*/
	//-------------------------------------------------------------//
	inline void init_port(uint8_t dir)
	{
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		// RX64M/LQFP:176(177)
		PORT0::PCR = dir;	// (6) P00,P01,P02,P05,P07
		PORT1::PCR = dir;	// (8) P10 to P17
		PORT2::PCR = dir;	// (8) P20 to P27
		PORT3::PCR = dir;	// (8) P30 to P37
		PORT4::PCR = dir;	// (8) P40 to P47
		PORT5::PCR = dir;	// (4) P50,P51,P52,P53
		PORT6::PCR = dir;	// (8) P60 to P67
		PORT7::PCR = dir;	// (8) P70 to P77
		PORT8::PCR = dir;	// (6) P80,P81,P82,P83,P86,P87
		PORT9::PCR = dir;	// (8) P90 to P97
		PORTA::PCR = dir;	// (8) PA0 to PA7
		PORTB::PCR = dir;	// (8) PB0 to PB7
		PORTC::PCR = dir;	// (8) PC0 to PC7
		PORTD::PCR = dir;	// (8) PD0 to PD7
		PORTE::PCR = dir;	// (8) PE0 to PE7
		PORTF::PCR = dir;	// (6) PF0,PF1,PF2,PF3,PF4,PF5
		PORTG::PCR = dir;	// (8) PG0 to PG7
		PORTJ::PCR = dir;	// (2) PJ3,PJ5
#elif defined(SIG_RX63T)
		// RX63T は PCR レジスターをサポートしていない
#elif defined(SIG_RX24T)
		// RX24T/LFQFP:100
		PORT0::PCR = dir;	// (3) P00,P01,P02
		PORT1::PCR = dir;	// (2) P10,P11
		PORT2::PCR = dir;	// (5) P20,P21,P22,P23,P24
		PORT3::PCR = dir;	// (6) P30,P31,P32,P33,P36,P37
		PORT4::PCR = dir;	// (8) P40,P41,P42,P43,P44,P45,P46,P47 (analog input)
		PORT5::PCR = dir;	// (6) P50,P51,P52,P53,P54,P55 (analog input)
		PORT6::PCR = dir;	// (6) P60,P61,P62,P63,P64,P65 (analog input)
		PORT7::PCR = dir;	// (7) P70,P71,P72,P73,P74,P75,P76
		PORT8::PCR = dir;	// (3) P80,P81,P82
		PORT9::PCR = dir;	// (7) P90,P91,P92,P93,P94,P95,P96
		PORTA::PCR = dir;	// (6) PA0,PA1,PA2,PA3,PA4,PA5
		PORTB::PCR = dir;	// (8) PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7
		PORTD::PCR = dir;	// (8) PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7
		PORTE::PCR = dir;	// (5) PE0,PE1,PE3,PE4,PE5
#elif defined(SIG_RX66T)

// UC

#elif defined(SIG_RX72T)

// UC

#else
#  error "port.hpp requires SIG_XXX to be defined"
#endif
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単ポート定義テンプレート
		@param[in]	PORT	ポート・クラス
		@param[in]	BPOS	ビット位置
		@param[in]	ASSERT	アサート論理（通常「１」）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTX, bitpos BPOS, bool ASSERT = 1>
	struct PORT {

		static const uint8_t PNO     = static_cast<uint8_t>(PORTX::base_address_ & 0x1f);
		static const uint8_t BIT_POS = static_cast<uint8_t>(BPOS);

		/// オープンドレインタイプ
		enum class OD_TYPE : uint8_t {
			NONE,	///< 無し
			N_CH,	///< N-Channel
			P_CH,	///< P-Channel
		};

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0x00>, BPOS> DIR_;
		static DIR_ DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートを出力にする
		*/
		//-----------------------------------------------------------------//
		static void OUTPUT() { DIR = 1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートを入力にする
		*/
		//-----------------------------------------------------------------//
		static void INPUT() { DIR = 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0xC0>, BPOS> PU_;
		static PU_ PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		struct od_t {
			static rw8_t<PORTX::base_address_ + 0x80> ODR0;
			static rw8_t<PORTX::base_address_ + 0x81> ODR1;

			void operator = (OD_TYPE val) {
				uint8_t pos = static_cast<uint8_t>(BPOS);
				if(pos < 4) {
					ODR0 = (ODR0() & ~(3 << (pos * 2))) | (static_cast<uint8_t>(val) << (pos * 2));
				} else {
					pos -= 4;
					if(val) ODR1 |= 1 << (pos * 2);
					else ODR1 &= ~(1 << (pos * 2));
				}
			}

			OD_TYPE operator () () {
				uint8_t pos = static_cast<uint8_t>(BPOS);
				if(pos < 4) {
					return static_cast<OD_TYPE>(ODR0() & (3 << (pos * 2)));
				} else {
					pos -= 4;
					return static_cast<OD_TYPE>(ODR1() & (3 << (pos * 2)));
				}
			}
		};
		typedef od_t OD_;
		static OD_ OD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ @n
					※ポート出力と、ポート入力が異なる
		*/
		//-----------------------------------------------------------------//
		struct port_t {
			typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0x20>, BPOS> PO_;
			static PO_ PO;  // ポート出力用
			typedef bit_ro_t<ro8_t<PORTX::base_address_ + 0x40>, BPOS> PI_;
			static PI_ PI;  // ポート入力用

			void operator = (bool val) {
				if(ASSERT) { PO = val; } else { PO = !val; }
			}
			bool operator () () {
				if(ASSERT) { return PI(); } 
				else { return !PI(); }
			}
		};
		typedef port_t P_;
		static P_ P;
	};
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::DIR_ PORT<PORTX, BPOS, ASSERT>::DIR;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::PU_ PORT<PORTX, BPOS, ASSERT>::PU;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::OD_ PORT<PORTX, BPOS, ASSERT>::OD;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::port_t::PO_ PORT<PORTX, BPOS, ASSERT>::port_t::PO;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::port_t::PI_ PORT<PORTX, BPOS, ASSERT>::port_t::PI;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::P_ PORT<PORTX, BPOS, ASSERT>::P;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ８ビット・ポート定義
		@param[in]	PORTx	ポート・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTx>
	struct PORT_BYTE {

//		static const uint8_t PNO     = static_cast<uint8_t>(PORTx::base_address_ & 0x1f);
//		static const uint8_t BIT_POS = static_cast<uint8_t>(bpos);

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		static rw8_t<PORTx::base_address_ + 0x00> DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static rw8_t<PORTx::base_address_ + 0xC0> PU;


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		struct od_t {
			static rw8_t<PORTx::base_address_ + 0x80> ODR0;
			static rw8_t<PORTx::base_address_ + 0x81> ODR1;

			void operator = (bool val) {
				uint8_t pos = static_cast<uint8_t>(bpos);
				if(pos < 4) { 
					if(val) ODR0 |= 1 << (pos * 2);
					else ODR0 &= ~(1 << (pos * 2));
				} else {
					pos -= 4;
					if(val) ODR1 |= 1 << (pos * 2);
					else ODR1 &= ~(1 << (pos * 2));
				}
			}
			bool operator () () {
				uint8_t pos = static_cast<uint8_t>(bpos);
				if(pos < 4) {
					return ODR0() & (1 << (pos * 2));
				} else {
					pos -= 4;
					return ODR1() & (1 << (pos * 2));
				}
			}
		};
		static od_t OD;
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ @n
					※ポート出力と、ポート入力が異なる
		*/
		//-----------------------------------------------------------------//
		struct port_t {
			static rw8_t<PORTx::base_address_ + 0x20> PO;  // ポート出力用
			static ro8_t<PORTx::base_address_ + 0x40> PI;  // ポート入力用

			void operator = (uint8_t val) { PO = val; }
			uint8_t operator () () { return PI(); }
		};
		static port_t P;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  無効ポート定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct NULL_PORT_t {

		static const uint8_t PNO     = 0xff;
		static const uint8_t BIT_POS = 0xff;

		struct null_t {
			void operator = (bool f) { }
			bool operator () () const { return 0; } 
		};

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t OD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t P;
	};
	typedef NULL_PORT_t<void> NULL_PORT;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::DIR;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::PU;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::OD;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::P;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  複数ポート定義テンプレート（最大８ビット）
		@param[in]	Args	ポート・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class... Args>
	class PORTS {
		static constexpr std::size_t pack_size = sizeof...(Args);
		static std::tuple<Args...> pack_; 
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  ポートの読み出し @n
					※個別のポート制御なので、遅延が発生する
			@return 値
		*/
		//-----------------------------------------------------------------//
		uint32_t operator () () {
			uint32_t bits = 0;
			if(pack_size > 7) {
				bits <<= 1;
				if(std::get<7>(pack_).P()) ++bits;
			}
			if(pack_size > 6) {
				bits <<= 1;
				if(std::get<6>(pack_).P()) ++bits;
			}
			if(pack_size > 5) {
				bits <<= 1;
				if(std::get<5>(pack_).P()) ++bits;
			}
			if(pack_size > 4) {
				bits <<= 1;
				if(std::get<4>(pack_).P()) ++bits;
			}
			if(pack_size > 3) {
				bits <<= 1;
				if(std::get<3>(pack_).P()) ++bits;
			}
			if(pack_size > 2) {
				bits <<= 1;
				if(std::get<2>(pack_).P()) ++bits;
			}
			if(pack_size > 1) {
				bits <<= 1;
				if(std::get<1>(pack_).P()) ++bits;
			}
			bits <<= 1;
			if(std::get<0>(pack_).P()) ++bits;

			return bits;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートへの書き込み @n
					※個別のポート制御なので、グリッチが発生する
			@param[in]	bits	値
		*/
		//-----------------------------------------------------------------//
		void operator = (uint32_t bits) {	
			std::get<0>(pack_).P = bits;
			if(pack_size > 1) {
				bits >>= 1;
				std::get<1>(pack_).P = bits;
			}
			if(pack_size > 2) {
				bits >>= 1;
				std::get<2>(pack_).P = bits;
			}
			if(pack_size > 3) {
				bits >>= 1;
				std::get<3>(pack_).P = bits;
			}
			if(pack_size > 4) {
				bits >>= 1;
				std::get<4>(pack_).P = bits;
			}
			if(pack_size > 5) {
				bits >>= 1;
				std::get<5>(pack_).P = bits;
			}
			if(pack_size > 6) {
				bits >>= 1;
				std::get<6>(pack_).P = bits;
			}
			if(pack_size > 7) {
				bits >>= 1;
				std::get<7>(pack_).P = bits;
			}
		}
	};
}
