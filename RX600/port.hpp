#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・ポート・レジスター定義
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
		@brief  ポート定義基底クラス（PDR, PODR, PIDR, PMR, ODR0, ODR1, PCR, DSCR）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct port_t {

		static const uint32_t base_address_ = base;


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
			bit_rw_t<io_, bitpos::B3> B3;
			bit_rw_t<io_, bitpos::B4> B4;
			bit_rw_t<io_, bitpos::B6> B6;
		};
		static odr0_t<base + 0x80> ODR0;


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
		static odr1_t<base + 0x81> ODR1;


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

	typedef port_t<0x0008C000> PORT0;
	typedef port_t<0x0008C001> PORT1;
	typedef port_t<0x0008C002> PORT2;
	typedef port_t<0x0008C003> PORT3;
	typedef port_t<0x0008C004> PORT4;
	typedef port_t<0x0008C005> PORT5;
	typedef port_t<0x0008C006> PORT6;
	typedef port_t<0x0008C007> PORT7;
	typedef port_t<0x0008C008> PORT8;
	typedef port_t<0x0008C009> PORT9;
	typedef port_t<0x0008C00A> PORTA;
	typedef port_t<0x0008C00B> PORTB;
	typedef port_t<0x0008C00C> PORTC;
	typedef port_t<0x0008C00D> PORTD;
	typedef port_t<0x0008C00E> PORTE;
	typedef port_t<0x0008C00F> PORTF;
	typedef port_t<0x0008C010> PORTG;
	typedef port_t<0x0008C012> PORTJ;


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
