#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコン・ポート・ベース定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"
#include <tuple>

namespace device {

	//=====================================================================//
	/*!
		@brief  ポート・ベース・クラス
	*/
	//=====================================================================//
	struct PORT_BASE {
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PORT : uint8_t {
			P0,		///< PORT0
			P1,		///< PORT1
			P2,		///< PORT2
			P3,		///< PORT3
			P4,		///< PORT4
			P5,		///< PORT5
			P6,		///< PORT6
			P7,		///< PORT7
			P8,		///< PORT8
			P9,		///< PORT9
			PA,		///< PORTA
			PB,		///< PORTB
			PC,		///< PORTC
			PD,		///< PORTD
			PE,		///< PORTE
			PF,		///< PORTF
			PG,		///< PORTG
			PH,		///< PORTH
			PJ,		///< PORTJ
			PK,		///< PORTK
			PL,		///< PORTL
			PM,		///< PORTM
			PN,		///< PORTN
			PQ,		///< PORTQ
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート・オープンドレイン・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OD_TYPE : uint8_t {
			NONE,	///< 無し
			N_CH,	///< N-Channel
			P_CH,	///< P-Channel
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PDR, PODR, PIDR, PMR, PCR, DSCR）
		@param[in]	base	ベースアドレス
		@param[in]	option	オプション
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, class option>
	struct portx_t : public option {

		static constexpr uint32_t base_address_ = base;	///< ベースアドレス
		static constexpr auto N = static_cast<PORT_BASE::PORT>(base & 0x1f);

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ（PDR）
		*/
		//-----------------------------------------------------------------//
		static inline basic_rw_t<rw8_t<base + 0x00> > PDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート出力データレジスタ（PODR）
		*/
		//-----------------------------------------------------------------//
		static inline basic_rw_t<rw8_t<base + 0x20> > PODR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート入力データレジスタ（PIDR）
		*/
		//-----------------------------------------------------------------//
		static inline basic_ro_t<ro8_t<base + 0x40> > PIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートモードレジスタ（PMR）
		*/
		//-----------------------------------------------------------------//
		static inline basic_rw_t<rw8_t<base + 0x60> > PMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御レジスタ（PCR）
		*/
		//-----------------------------------------------------------------//
		static inline basic_rw_t<rw8_t<base + 0xC0> > PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  駆動能力制御レジスタ（DSCR）
		*/
		//-----------------------------------------------------------------//
		static inline basic_rw_t<rw8_t<base + 0xE0> > DSCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PIDR）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct porti_t {

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
		static inline pidr_t PIDR;
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
		@brief  ODR 定義 (ODR0, ODR1) 
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
			bit_rw_t<io_, bitpos::B3> B3;
			bit_rw_t<io_, bitpos::B4> B4;
			bit_rw_t<io_, bitpos::B6> B6;
		};
		static inline odr0_t<base + 0x00> ODR0;


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
		static inline odr1_t<base + 0x01> ODR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御レジスタ（ODR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct odr_t {
			typedef rw8_t<ofs + 0>  io0_;
			typedef rw8_t<ofs + 1>  io1_;

			bits_rw_t<io0_, bitpos::B0, 2> B0;
			bits_rw_t<io0_, bitpos::B2, 2> B1;
			bits_rw_t<io0_, bitpos::B4, 2> B2;
			bits_rw_t<io0_, bitpos::B6, 2> B3;
			bits_rw_t<io1_, bitpos::B0, 2> B4;
			bits_rw_t<io1_, bitpos::B2, 2> B5;
			bits_rw_t<io1_, bitpos::B4, 2> B6;
			bits_rw_t<io1_, bitpos::B6, 2> B7;
		};
		static inline odr_t<base> ODR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ODR 定義 (ODR0)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct odr_ox_t {

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
			bit_rw_t<io_, bitpos::B4> B4;
			bit_rw_t<io_, bitpos::B6> B6;
		};
		static inline odr0_t<base + 0> ODR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御レジスタ（ODR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct odr_t {
			typedef rw8_t<ofs + 0>  io0_;

			bits_rw_t<io0_, bitpos::B0, 2> B0;
			bits_rw_t<io0_, bitpos::B2, 2> B1;
			bits_rw_t<io0_, bitpos::B4, 2> B2;
			bits_rw_t<io0_, bitpos::B6, 2> B3;
		};
		static inline odr_t<base> ODR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ODR 定義 (ODR1)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct odr_xo_t {

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
		static inline odr1_t<base + 1> ODR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御レジスタ（ODR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct odr_t {
			typedef rw8_t<ofs + 1>  io1_;

			bits_rw_t<io1_, bitpos::B0, 2> B4;
			bits_rw_t<io1_, bitpos::B2, 2> B5;
			bits_rw_t<io1_, bitpos::B4, 2> B6;
			bits_rw_t<io1_, bitpos::B6, 2> B7;
		};
		static inline odr_t<base> ODR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単ポート定義テンプレート
		@param[in]	PORT	ポート・クラス
		@param[in]	BPOS	ビット位置
		@param[in]	ASSERT_	アサート論理 @n
							※反転入力、反転出力として扱う場合「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTX, bitpos BPOS, bool ASSERT_ = true>
	struct PORT : public PORT_BASE {

		typedef PORTX value_type;

		static constexpr auto PNO     = static_cast<uint8_t>(PORTX::base_address_ & 0x1f);	///< ポート番号（０～３１）
		static constexpr auto BIT_POS = BPOS;		///< ポート、ビット位置
		static constexpr auto ASSERT  = ASSERT_;	///< アサート論理

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ @n
					0: 入力 @n
					1: 出力
		*/
		//-----------------------------------------------------------------//
		static inline bit_rw_t<rw8_t<PORTX::base_address_ + 0x00>, BPOS> DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートを出力にする
		*/
		//-----------------------------------------------------------------//
		static void OUTPUT() noexcept { DIR = 1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートを入力にする
		*/
		//-----------------------------------------------------------------//
		static void INPUT() noexcept { DIR = 0; }


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

			static inline rw8_t<PORTX::base_address_ + 0x80> ODR0;

			static inline rw8_t<PORTX::base_address_ + 0x81> ODR1;

			void operator = (OD_TYPE val) noexcept {
				uint8_t pos = static_cast<uint8_t>(BPOS);
				if(pos < 4) {
					ODR0 = (ODR0() & ~(3 << (pos * 2))) | (static_cast<uint8_t>(val) << (pos * 2));
				} else {
					pos -= 4;
					ODR1 = (ODR1() & ~(3 << (pos * 2))) | (static_cast<uint8_t>(val) << (pos * 2));
				}
			}

			OD_TYPE operator () () noexcept {

				auto pos = static_cast<uint8_t>(BPOS);
				switch(BPOS) {
				case bitpos::B0:
					return static_cast<OD_TYPE>(ODR0() & 0b0000'0011);
				case bitpos::B1:
					return static_cast<OD_TYPE>((ODR0() & 0b0000'1100) >> 2);
				case bitpos::B2:
					return static_cast<OD_TYPE>((ODR0() & 0b0011'0000) >> 4);
				case bitpos::B3:
					return static_cast<OD_TYPE>((ODR0() & 0b1100'0000) >> 6);
				case bitpos::B4:
					return static_cast<OD_TYPE>(ODR1() & 0b0000'0011);
				case bitpos::B5:
					return static_cast<OD_TYPE>((ODR1() & 0b0000'1100) >> 2);
				case bitpos::B6:
					return static_cast<OD_TYPE>((ODR1() & 0b0011'0000) >> 4);
				case bitpos::B7:
					return static_cast<OD_TYPE>((ODR1() & 0b1100'0000) >> 6);
				default:
					return OD_TYPE::NONE;
				}
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

			void operator = (bool val) noexcept {
				if(ASSERT_) { PO = val; } else { PO = !val; }
			}
			bool operator () () noexcept {
				if(ASSERT_) { return PI(); } 
				else { return !PI(); }
			}
		};
		static inline port_t P;


		//-----------------------------------------------------------------//
		/*!
			@brief  反転
		*/
		//-----------------------------------------------------------------//
		static void FLIP() noexcept { P = !P(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ８ビット・ポート定義
		@param[in]	PORTx	ポート・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTx>
	struct PORT_BYTE {

//		static constexpr uint8_t PNO     = static_cast<uint8_t>(PORTx::base_address_ & 0x1f);
//		static constexpr uint8_t BIT_POS = static_cast<uint8_t>(bpos);

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
	struct null_port_t {

		static constexpr uint8_t PNO  = 0xff;
		static constexpr auto BIT_POS = bitpos::NONE;  ///< 無効ビット 
		static constexpr bool ASSERT  = 0;

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
	typedef null_port_t NULL_PORT;


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
