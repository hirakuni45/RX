#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・ポート・レジスター定義 @n
                P0 P1 P2 P3 P4 P5 P6 P7 P8 P9 PA PB PC PD PE PF PG PJ @n
    RX24T ODR0  o  o  o  o  x  x  x  o  o  o  o  o  x  o  o  -  -  -  @n
          ODR1  x  x  o  x  x  x  x  o  x  o  o  o  x  o  o  -  -  -  @n
    RX64M ODR0  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o  @n
          ODR1  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o  o
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

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
		static basic_rw_t<rw8_t<base + 0x00> > PDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート出力データレジスタ（PODR）
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0x20> > PODR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート入力データレジスタ（PIDR）
		*/
		//-----------------------------------------------------------------//
		static basic_ro_t<ro8_t<base + 0x40> > PIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートモードレジスタ（PMR）
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0x60> > PMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御レジスタ（PCR）
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0xC0> > PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  駆動能力制御レジスタ（DSCR）
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0xE0> > DSCR;
	};


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
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_rw_t<io_, bitpos::B3> B3;
#endif
			bit_rw_t<io_, bitpos::B4> B4;
			bit_rw_t<io_, bitpos::B6> B6;
		};
		static odr0_t<base + 0> ODR0;


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
			bit_rw_t<io_, bitpos::B6> B6;
		};
		static odr1_t<base + 1> ODR1;
	};


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
		static odr0_t<base> ODR0;
	};


#if defined(SIG_RX64M) || defined(SIG_RX71M)
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
#elif defined(SIG_RX24T) || defined(SIG_RX63T)
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
	typedef port_t<0x0008C00C, odr_xx_t<0x0008C098> > PORTC;
	typedef port_t<0x0008C00D, odr_oo_t<0x0008C09A> > PORTD;
	typedef port_t<0x0008C00E, odr_oo_t<0x0008C09C> > PORTE;
#endif


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単ポート定義テンプレート
		@param[in]	PORTx	ポート・クラス
		@param[in]	bpos	ビット位置	
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTx, bitpos bpos>
	struct PORT {

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		static bit_rw_t<rw8_t<PORTx::base_address_ + 0x00>, bpos> DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static bit_rw_t<rw8_t<PORTx::base_address_ + 0xC0>, bpos> PU;


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


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ @n
					※ポート出力と、ポート入力が異なる
		*/
		//-----------------------------------------------------------------//
		struct port_t {
			static bit_rw_t<rw8_t<PORTx::base_address_ + 0x20>, bpos> PO;  // ポート出力用
			static bit_ro_t<ro8_t<PORTx::base_address_ + 0x40>, bpos> PI;  // ポート入力用

			void operator = (bool val) { PO = val; }
			bool operator () () { return PI(); }
		};
		static port_t P;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  無効ポート定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct NULL_PORT {

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
}
