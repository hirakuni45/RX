#pragma once
//=========================================================================//
/*!	@file
	@brief	I/O Ports / I/O ポート (RX621/RX62N)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（DDR, DR, PORT, ICR, ODR）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct portx_t {

		static constexpr uint32_t base_address_ = base;	///< ベースアドレス

		typedef rw8_t<base + 0x00>  ddr_io;
		typedef rw8_t<base + 0x20>  dr_io;
		typedef rw8_t<base + 0x40>  port_io;
		typedef rw8_t<base + 0x60>  icr_io;
		typedef rw8_t<base + 0x80>  odr_io;

		//-----------------------------------------------------------------//
		/*!
			@brief  DDR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct ddr_t : public ddr_io {
			using ddr_io::operator =;
			using ddr_io::operator ();
			using ddr_io::operator |=;
			using ddr_io::operator &=;

			bit_rw_t<ddr_io, bitpos::B0> B0;
			bit_rw_t<ddr_io, bitpos::B1> B1;
			bit_rw_t<ddr_io, bitpos::B2> B2;
			bit_rw_t<ddr_io, bitpos::B3> B3;
			bit_rw_t<ddr_io, bitpos::B4> B4;
			bit_rw_t<ddr_io, bitpos::B5> B5;
			bit_rw_t<ddr_io, bitpos::B6> B6;
			bit_rw_t<ddr_io, bitpos::B7> B7;
		};
		static inline ddr_t DDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct dr_t : public dr_io {
			using dr_io::operator =;
			using dr_io::operator ();
			using dr_io::operator |=;
			using dr_io::operator &=;

			bit_rw_t<dr_io, bitpos::B0> B0;
			bit_rw_t<dr_io, bitpos::B1> B1;
			bit_rw_t<dr_io, bitpos::B2> B2;
			bit_rw_t<dr_io, bitpos::B3> B3;
			bit_rw_t<dr_io, bitpos::B4> B4;
			bit_rw_t<dr_io, bitpos::B5> B5;
			bit_rw_t<dr_io, bitpos::B6> B6;
			bit_rw_t<dr_io, bitpos::B7> B7;

		};
		static inline dr_t DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PORT
		*/
		//-----------------------------------------------------------------//
		struct port_t : public port_io {
			using port_io::operator ();

			bit_ro_t<port_io, bitpos::B0> B0;
			bit_ro_t<port_io, bitpos::B1> B1;
			bit_ro_t<port_io, bitpos::B2> B2;
			bit_ro_t<port_io, bitpos::B3> B3;
			bit_ro_t<port_io, bitpos::B4> B4;
			bit_ro_t<port_io, bitpos::B5> B5;
			bit_ro_t<port_io, bitpos::B6> B6;
			bit_ro_t<port_io, bitpos::B7> B7;
		};
		static inline port_t PORT;


		//-----------------------------------------------------------------//
		/*!
			@brief  ICR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct icr_t : public icr_io {
			using icr_io::operator =;
			using icr_io::operator ();
			using icr_io::operator |=;
			using icr_io::operator &=;

			bit_rw_t<icr_io, bitpos::B0> B0;
			bit_rw_t<icr_io, bitpos::B1> B1;
			bit_rw_t<icr_io, bitpos::B2> B2;
			bit_rw_t<icr_io, bitpos::B3> B3;
			bit_rw_t<icr_io, bitpos::B4> B4;
			bit_rw_t<icr_io, bitpos::B5> B5;
			bit_rw_t<icr_io, bitpos::B6> B6;
			bit_rw_t<icr_io, bitpos::B7> B7;
		};
		static inline icr_t ICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct odr_t : public odr_io {
			using odr_io::operator =;
			using odr_io::operator ();
			using odr_io::operator |=;
			using odr_io::operator &=;

			bit_rw_t<odr_io, bitpos::B0> B0;
			bit_rw_t<odr_io, bitpos::B1> B1;
			bit_rw_t<odr_io, bitpos::B2> B2;
			bit_rw_t<odr_io, bitpos::B3> B3;
			bit_rw_t<odr_io, bitpos::B4> B4;
			bit_rw_t<odr_io, bitpos::B5> B5;
			bit_rw_t<odr_io, bitpos::B6> B6;
			bit_rw_t<odr_io, bitpos::B7> B7;
		};
		static inline odr_t ODR;
	};
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
	typedef portx_t<0x0008'C00C> PORTC;
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
//			P_CH,	///< P-Channel
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
		static inline bit_rw_t<rw8_t<PORTX::base_address_ + 0x00>, BPOS> DIR;


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
		static inline bit_rw_t<rw8_t<PORTX::base_address_ + 0xC0>, BPOS> PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		struct od_t {
			static rw8_t<PORTX::base_address_ + 0x80> ODR;

			void operator = (OD_TYPE val) {
				uint8_t pos = static_cast<uint8_t>(BPOS);
				ODR = (ODR() & ~(3 << pos)) | (static_cast<uint8_t>(val) << pos);
			}

			OD_TYPE operator () () {
				uint8_t pos = static_cast<uint8_t>(BPOS);
				return static_cast<OD_TYPE>(ODR() & (3 << pos));
			}
		};
		static inline od_t OD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ @n
					※ポート出力と、ポート入力が異なる
		*/
		//-----------------------------------------------------------------//
		struct port_t {

			static inline bit_rw_t<rw8_t<PORTX::base_address_ + 0x20>, BPOS> PO;  // ポート出力用

			static inline bit_ro_t<ro8_t<PORTX::base_address_ + 0x40>, BPOS> PI;  // ポート入力用

			void operator = (bool val) {
				if(ASSERT) { PO = val; } else { PO = !val; }
			}
			bool operator () () {
				if(ASSERT) { return PI(); } 
				else { return !PI(); }
			}
		};
		static inline port_t P;


		//-----------------------------------------------------------------//
		/*!
			@brief  反転
		*/
		//-----------------------------------------------------------------//
		static void FLIP() { P = !P(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ８ビット・ポート定義
		@param[in]	PORTx	ポート・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTx>
	struct PORT_BYTE {

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<PORTx::base_address_ + 0x00> DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<PORTx::base_address_ + 0xC0> PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ @n
					※ポート出力と、ポート入力が異なる
		*/
		//-----------------------------------------------------------------//
		struct port_t {

			static inline rw8_t<PORTx::base_address_ + 0x20> PO;  // ポート出力用

			static inline ro8_t<PORTx::base_address_ + 0x40> PI;  // ポート入力用

			void operator = (uint8_t val) { PO = val; }
			uint8_t operator () () { return PI(); }
		};
		static inline port_t P;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  無効ポート定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct NULL_PORT {

		static constexpr uint8_t PNO     = 0xff;
		static constexpr uint8_t BIT_POS = 0xff;

		struct null_t {
			void operator = (bool f) { }
			bool operator () () const { return 0; } 
		};

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		static inline null_t DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static inline null_t PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static inline null_t OD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ
		*/
		//-----------------------------------------------------------------//
		static inline null_t P;
	};
}

