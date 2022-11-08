#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・ポート・レジスター定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PDR, PODR, PIDR, PMR, ODR0, ODR1）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct portx_t {

		static constexpr uint32_t base_address_ = base;	///< ベースアドレス

		typedef rw8_t<base + 0x00>  pdr_io;
		typedef rw8_t<base + 0x20>  podr_io;
		typedef rw8_t<base + 0x40>  pidr_io;
		typedef rw8_t<base + 0x60>  pmr_io;
		typedef rw8_t<base + 0x80>  odr0_io;
		typedef rw8_t<base + 0x85>  odr1_io;

		//-----------------------------------------------------------------//
		/*!
			@brief  PDR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pdr_t : public pdr_io {
			using pdr_io::operator =;
			using pdr_io::operator ();
			using pdr_io::operator |=;
			using pdr_io::operator &=;

			bit_rw_t<pdr_io, bitpos::B0> B0;
			bit_rw_t<pdr_io, bitpos::B1> B1;
			bit_rw_t<pdr_io, bitpos::B2> B2;
			bit_rw_t<pdr_io, bitpos::B3> B3;
			bit_rw_t<pdr_io, bitpos::B4> B4;
			bit_rw_t<pdr_io, bitpos::B5> B5;
			bit_rw_t<pdr_io, bitpos::B6> B6;
			bit_rw_t<pdr_io, bitpos::B7> B7;
		};
		typedef pdr_t PDR_;
		static PDR_ PDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PODR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct podr_t : public podr_io {
			using podr_io::operator =;
			using podr_io::operator ();
			using podr_io::operator |=;
			using podr_io::operator &=;

			bit_rw_t<podr_io, bitpos::B0> B0;
			bit_rw_t<podr_io, bitpos::B1> B1;
			bit_rw_t<podr_io, bitpos::B2> B2;
			bit_rw_t<podr_io, bitpos::B3> B3;
			bit_rw_t<podr_io, bitpos::B4> B4;
			bit_rw_t<podr_io, bitpos::B5> B5;
			bit_rw_t<podr_io, bitpos::B6> B6;
			bit_rw_t<podr_io, bitpos::B7> B7;

		};
		typedef podr_t PODR_;
		static PODR_ PODR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PIDR
		*/
		//-----------------------------------------------------------------//
		struct pidr_t : public pidr_io {
			using pidr_io::operator ();

			bit_ro_t<pidr_io, bitpos::B0> B0;
			bit_ro_t<pidr_io, bitpos::B1> B1;
			bit_ro_t<pidr_io, bitpos::B2> B2;
			bit_ro_t<pidr_io, bitpos::B3> B3;
			bit_ro_t<pidr_io, bitpos::B4> B4;
			bit_ro_t<pidr_io, bitpos::B5> B5;
			bit_ro_t<pidr_io, bitpos::B6> B6;
			bit_ro_t<pidr_io, bitpos::B7> B7;
		};
		typedef pidr_t PIDR_;
		static PIDR_ PIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PMR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pmr_t : public pmr_io {
			using pmr_io::operator =;
			using pmr_io::operator ();
			using pmr_io::operator |=;
			using pmr_io::operator &=;

			bit_rw_t<pmr_io, bitpos::B0> B0;
			bit_rw_t<pmr_io, bitpos::B1> B1;
			bit_rw_t<pmr_io, bitpos::B2> B2;
			bit_rw_t<pmr_io, bitpos::B3> B3;
			bit_rw_t<pmr_io, bitpos::B4> B4;
			bit_rw_t<pmr_io, bitpos::B5> B5;
			bit_rw_t<pmr_io, bitpos::B6> B6;
			bit_rw_t<pmr_io, bitpos::B7> B7;
		};
		typedef pmr_t PMR_;
		static PMR_ PMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR0 レジスタ
		*/
		//-----------------------------------------------------------------//
		struct odr0_t : public odr0_io {
			using odr0_io::operator =;
			using odr0_io::operator ();
			using odr0_io::operator |=;
			using odr0_io::operator &=;

			bit_rw_t<odr0_io, bitpos::B0> B0;
			bit_rw_t<odr0_io, bitpos::B2> B2;
			bit_rw_t<odr0_io, bitpos::B4> B4;
			bit_rw_t<odr0_io, bitpos::B6> B6;
		};
		typedef odr0_t ODR0_;
		static ODR0_ ODR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR1 レジスタ
		*/
		//-----------------------------------------------------------------//
		struct odr1_t : public odr1_io {
			using odr1_io::operator =;
			using odr1_io::operator ();
			using odr1_io::operator |=;
			using odr1_io::operator &=;

			bit_rw_t<odr1_io, bitpos::B0> B0;
			bit_rw_t<odr1_io, bitpos::B2> B2;
			bit_rw_t<odr1_io, bitpos::B4> B4;
		};
		typedef odr1_t ODR1_;
		static ODR1_ ODR1;
	};
	template <uint32_t base> typename portx_t<base>::PDR_  portx_t<base>::PDR;
	template <uint32_t base> typename portx_t<base>::PODR_ portx_t<base>::PODR;
	template <uint32_t base> typename portx_t<base>::PIDR_ portx_t<base>::PIDR;
	template <uint32_t base> typename portx_t<base>::PMR_  portx_t<base>::PMR;
	template <uint32_t base> typename portx_t<base>::ODR0_ portx_t<base>::ODR0;
	template <uint32_t base> typename portx_t<base>::ODR1_ portx_t<base>::ODR1;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PIDR）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct porty_t {

		static constexpr uint32_t base_address_ = base;	///< ベースアドレス

		typedef rw8_t<base + 0x40>  pidr_io;

		//-----------------------------------------------------------------//
		/*!
			@brief  PIDR
		*/
		//-----------------------------------------------------------------//
		struct pidr_t : public pidr_io {
			using pidr_io::operator ();

			bit_ro_t<pidr_io, bitpos::B0> B0;
			bit_ro_t<pidr_io, bitpos::B1> B1;
			bit_ro_t<pidr_io, bitpos::B2> B2;
			bit_ro_t<pidr_io, bitpos::B3> B3;
			bit_ro_t<pidr_io, bitpos::B4> B4;
			bit_ro_t<pidr_io, bitpos::B5> B5;
			bit_ro_t<pidr_io, bitpos::B6> B6;
			bit_ro_t<pidr_io, bitpos::B7> B7;
		};
		typedef pidr_t PIDR_;
		static PIDR_ PIDR;
	};
	template <uint32_t base> typename porty_t<base>::PIDR_ porty_t<base>::PIDR;


	typedef portx_t<0x0008'C000> PORT0;
	typedef portx_t<0x0008'C001> PORT1;
	typedef portx_t<0x0008'C002> PORT2;
	typedef portx_t<0x0008'C003> PORT3;
	typedef portx_t<0x0008'C004> PORT4;
	typedef portx_t<0x0008'C005> PORT5;
	typedef portx_t<0x0008'C006> PORT6;
	typedef portx_t<0x0008'C007> PORT7;
	typedef portx_t<0x0008'C008> PORT8;
	typedef portx_t<0x0008'C009> PORT9;
	typedef portx_t<0x0008'C00A> PORTA;
	typedef portx_t<0x0008'C00B> PORTB;
	typedef portx_t<0x0008'C00D> PORTD;
	typedef portx_t<0x0008'C00E> PORTE;
	typedef portx_t<0x0008'C00F> PORTF;
	typedef portx_t<0x0008'C010> PORTG;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・オープンドレイン・タイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct PORT_BASE {
		enum class OD_TYPE : uint8_t {
			NONE,	///< 無し
			N_CH,	///< N-Channel
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単ポート定義テンプレート
		@param[in]	PORT	ポート・クラス
		@param[in]	BPOS	ビット位置
		@param[in]	ASSERT	アサート論理 @n
							※反転入力、反転出力として扱う場合「０」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTX, bitpos BPOS, bool ASSERT = 1>
	struct PORT : public PORT_BASE {

		static constexpr uint8_t PNO     = static_cast<uint8_t>(PORTX::base_address_ & 0x1f);
		static constexpr uint8_t BIT_POS = static_cast<uint8_t>(BPOS);

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
					ODR1 = (ODR1() & ~(3 << (pos * 2))) | (static_cast<uint8_t>(val) << (pos * 2));
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


		//-----------------------------------------------------------------//
		/*!
			@brief  反転
		*/
		//-----------------------------------------------------------------//
		static void FLIP() { P = !P(); }
	};
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::DIR_ PORT<PORTX, BPOS, ASSERT>::DIR;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::OD_ PORT<PORTX, BPOS, ASSERT>::OD;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::port_t::PO_ PORT<PORTX, BPOS, ASSERT>::port_t::PO;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::port_t::PI_ PORT<PORTX, BPOS, ASSERT>::port_t::PI;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::P_ PORT<PORTX, BPOS, ASSERT>::P;

}
