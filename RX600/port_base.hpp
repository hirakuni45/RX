#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコン・ポート・ベース定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
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
	struct portx_t : public option {

		static constexpr uint32_t base_address_ = base;	///< ベースアドレス

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
	template <uint32_t base, class option>
		typename portx_t<base, option>::PDR_  portx_t<base, option>::PDR;
	template <uint32_t base, class option>
		typename portx_t<base, option>::PODR_ portx_t<base, option>::PODR;
	template <uint32_t base, class option>
		typename portx_t<base, option>::PIDR_ portx_t<base, option>::PIDR;
	template <uint32_t base, class option>
		typename portx_t<base, option>::PMR_  portx_t<base, option>::PMR;
	template <uint32_t base, class option>
		typename portx_t<base, option>::PCR_  portx_t<base, option>::PCR;
	template <uint32_t base, class option>
		typename portx_t<base, option>::DSCR_ portx_t<base, option>::DSCR;


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
		typedef pidr_t PIDR_;
		static PIDR_ PIDR;
	};
	template <uint32_t base> typename porti_t<base>::PIDR_ porti_t<base>::PIDR;


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
		typedef odr0_t<base + 0x00> ODR0_;
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
			bit_rw_t<io_, bitpos::B6> B6;
		};
		typedef odr1_t<base + 0x01> ODR1_;
		static ODR1_ ODR1;
	};
	template <uint32_t base> typename odr_oo_t<base>::ODR0_ odr_oo_t<base>::ODR0;
	template <uint32_t base> typename odr_oo_t<base>::ODR1_ odr_oo_t<base>::ODR1;


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


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・オープンドレイン・タイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct PORT_BASE {
		enum class OD_TYPE : uint8_t {
			NONE,	///< 無し
			N_CH,	///< N-Channel
			P_CH,	///< P-Channel
		};
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
		typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0x00>, BPOS> DIR_;
		static DIR_ DIR;


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
		typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0xC0>, BPOS> PU_;
		static PU_ PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		struct od_t {
			typedef rw8_t<PORTX::base_address_ + 0x80> ODR0_;
			static ODR0_ ODR0;
			typedef rw8_t<PORTX::base_address_ + 0x81> ODR1_;
			static ODR1_ ODR1;

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
				uint8_t pos = static_cast<uint8_t>(BPOS);
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

			void operator = (bool val) noexcept {
				if(ASSERT_) { PO = val; } else { PO = !val; }
			}
			bool operator () () noexcept {
				if(ASSERT_) { return PI(); } 
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
		static void FLIP() noexcept { P = !P(); }
	};
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::DIR_ PORT<PORTX, BPOS, ASSERT>::DIR;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::PU_ PORT<PORTX, BPOS, ASSERT>::PU;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::od_t::ODR0_ PORT<PORTX, BPOS, ASSERT>::od_t::ODR0;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::od_t::ODR1_ PORT<PORTX, BPOS, ASSERT>::od_t::ODR1;
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

//		static constexpr uint8_t PNO     = static_cast<uint8_t>(PORTx::base_address_ & 0x1f);
//		static constexpr uint8_t BIT_POS = static_cast<uint8_t>(bpos);

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<PORTx::base_address_ + 0x00> DIR_;
		static DIR_ DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<PORTx::base_address_ + 0xC0> PU_;
		static PU_ PU;


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
			typedef rw8_t<PORTx::base_address_ + 0x20> PO_;
			static PO_ PO;	// ポート出力用
			typedef ro8_t<PORTx::base_address_ + 0x40> PI_;
			static PI_ PI;  // ポート入力用

			void operator = (uint8_t val) { PO = val; }
			uint8_t operator () () { return PI(); }
		};
		typedef port_t P_;
		static P_ P;
	};
	template <class PORTx> typename PORT_BYTE<PORTx>::DIR_ PORT_BYTE<PORTx>::DIR;
	template <class PORTx> typename PORT_BYTE<PORTx>::PU_  PORT_BYTE<PORTx>::PU;
	template <class PORTx> typename PORT_BYTE<PORTx>::P_::PO_  PORT_BYTE<PORTx>::P_::PO;
	template <class PORTx> typename PORT_BYTE<PORTx>::P_::PI_  PORT_BYTE<PORTx>::P_::PI;
	template <class PORTx> typename PORT_BYTE<PORTx>::P_   PORT_BYTE<PORTx>::P;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  無効ポート定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct NULL_PORT_t {

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
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::DIR;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::PU;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::OD;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::P;


	typedef NULL_PORT_t<void> NULL_PORT;


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
