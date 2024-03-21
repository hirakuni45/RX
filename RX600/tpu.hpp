#pragma once
//=========================================================================//
/*!	@file
	@brief	16 ビットタイマパルスユニット定義 @n
			RX231 @n
			RX631/RX63N @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX671 @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  16 ビットタイマパルスユニット・ベース（TPUa）
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct tpu_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		struct tcr_t : public rw8_t<base + 0x00> {
			typedef rw8_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC;
			bits_rw_t<io_, bitpos::B3, 2> CKEG;
			bits_rw_t<io_, bitpos::B5, 3> CCLR;
		};
		static inline tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		struct tmdr_t : public rw8_t<base + 0x01> {
			typedef rw8_t<base + 0x01> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  MD;
			bit_rw_t <io_, bitpos::B4>     BFA;
			bit_rw_t <io_, bitpos::B5>     BFB;
			bit_rw_t <io_, bitpos::B6>     ICSELB;
			bit_rw_t <io_, bitpos::B7>     ICSELD;
		};
		static inline tmdr_t TMDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		struct tiorh_t : public rw8_t<base + 0x02> {
			typedef rw8_t<base + 0x02> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IOA;
			bits_rw_t<io_, bitpos::B4, 4> IOB;
		};
		static inline tiorh_t TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ割り込み許可レジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		struct tier_t : public rw8_t<base + 0x04> {
			typedef rw8_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  TGIEA;
			bit_rw_t<io_, bitpos::B1>  TGIEB;
			bit_rw_t<io_, bitpos::B2>  TGIEC;
			bit_rw_t<io_, bitpos::B3>  TGIED;
			bit_rw_t<io_, bitpos::B4>  TCIEV;
			bit_rw_t<io_, bitpos::B5>  TCIEU;

			bit_rw_t<io_, bitpos::B7>  TTGE;
		};
		static inline tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		struct tsr_t : public rw8_t<base + 0x05> {
			typedef rw8_t<base + 0x05> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  TGFA;
			bit_rw_t<io_, bitpos::B1>  TGFB;
			bit_rw_t<io_, bitpos::B2>  TGFC;
			bit_rw_t<io_, bitpos::B3>  TGFD;
			bit_rw_t<io_, bitpos::B4>  TCFV;
			bit_rw_t<io_, bitpos::B5>  TCFU;

			bit_rw_t<io_, bitpos::B7>  TCFD;
		};
		static inline tsr_t TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x06> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ A（TGRA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x08> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ B（TGRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x0A> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマスタートレジスタ（TSTR）
		*/
		//-----------------------------------------------------------------//
		struct tstr_t : public rw8_t<0x00088100> {
			typedef rw8_t<0x00088100> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CST0;
			bit_rw_t <io_, bitpos::B1>  CST1;
			bit_rw_t <io_, bitpos::B2>  CST2;
			bit_rw_t <io_, bitpos::B3>  CST3;
			bit_rw_t <io_, bitpos::B4>  CST4;
			bit_rw_t <io_, bitpos::B5>  CST5;
		};
		static inline tstr_t TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマシンクロレジスタ（TSYR）
		*/
		//-----------------------------------------------------------------//
		struct tsyr_t : public rw8_t<0x00088101> {
			typedef rw8_t<0x00088101> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  SYNC0;
			bit_rw_t <io_, bitpos::B1>  SYNC1;
			bit_rw_t <io_, bitpos::B2>  SYNC2;
			bit_rw_t <io_, bitpos::B3>  SYNC3;
			bit_rw_t <io_, bitpos::B4>  SYNC4;
			bit_rw_t <io_, bitpos::B5>  SYNC5;
		};
		static inline tsyr_t TSYR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		struct nfcr_t : public rw8_t<base + 0x08> {
			typedef rw8_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     NFAEN;
			bit_rw_t <io_, bitpos::B1>     NFBEN;
			bit_rw_t <io_, bitpos::B2>     NFCEN;
			bit_rw_t <io_, bitpos::B3>     NFDEN;

			bits_rw_t<io_, bitpos::B4, 2>  NFCS;
		};
		static inline nfcr_t NFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  16 ビットタイマパルスユニット・ベース（TPUa）TPU0, TPU3
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	TGI		TGI[ABCD] 割り込み型
		@param[in]	tgia	割り込み要因Ａ
		@param[in]	tgib	割り込み要因Ｂ
		@param[in]	tgic	割り込み要因Ｃ
		@param[in]	tgid	割り込み要因Ｄ
		@param[in]	TCI		TCI[VU] 割り込み型
		@param[in]	tciv	割り込み要因Ｖ
		@param[in]	tciu	割り込み要因Ｕ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		typename TGI, TGI tgia, TGI tgib, TGI tgic, TGI tgid, typename TCI, TCI tciv, TCI tciu>
	struct tpu_x_t : public tpu_base_t<base> {

		typedef tpu_base_t<base> BASE;

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TGIA = tgia;	///< 割り込み要因Ａ
		static constexpr auto TGIB = tgib;	///< 割り込み要因Ｂ
		static constexpr auto TGIC = tgic;	///< 割り込み要因Ｃ
		static constexpr auto TGID = tgid;	///< 割り込み要因Ｄ
		static constexpr auto TCIV = tciv;	///< 割り込み要因Ｖ
		static constexpr auto TCIU = tciu;	///< 割り込み要因Ｕ


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		struct tiorl_t : public rw8_t<base + 0x03> {
			typedef rw8_t<base + 0x03> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IOC;
			bits_rw_t<io_, bitpos::B4, 4> IOD;
		};
		static inline tiorl_t TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ C（TGRC）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x0C> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ D（TGRD）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x0E> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマスタートレジスタ（TSTR）のエイリアス
			@param[in]	f	動作停止にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool f = true)
		{
			if(f) {
				BASE::TSTR |=  (1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			} else {
				BASE::TSTR &= ~(1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYR）のエイリアス
			@param[in]	f	同期解除にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void sync(bool f = true)
		{
			if(f) {
				BASE::TSYR |=  (1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			} else {
				BASE::TSYR &= ~(1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			}
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  16 ビットタイマパルスユニット・ベース（TPUa）TPU1, TPU2, TPU4, TPU5
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	TGI		TGI[ABCD] 割り込み型
		@param[in]	tgia	割り込み要因Ａ
		@param[in]	tgib	割り込み要因Ｂ
		@param[in]	tgic	割り込み要因Ｃ
		@param[in]	tgid	割り込み要因Ｄ
		@param[in]	TGI		TCI[VU] 割り込み型
		@param[in]	tciv	割り込み要因Ｖ
		@param[in]	tciu	割り込み要因Ｕ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		typename TGI, TGI tgia, TGI tgib, TGI tgic, TGI tgid, typename TCI, TCI tciv, TCI tciu>
	struct tpu_y_t : public tpu_base_t<base> {

		typedef tpu_base_t<base> BASE;

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TGIA = tgia;	///< 割り込み要因Ａ
		static constexpr auto TGIB = tgib;	///< 割り込み要因Ｂ
		static constexpr auto TGIC = tgic;	///< 割り込み要因Ｃ
		static constexpr auto TGID = tgid;	///< 割り込み要因Ｄ
		static constexpr auto TCIV = tciv;	///< 割り込み要因Ｖ
		static constexpr auto TCIU = tciu;	///< 割り込み要因Ｕ


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORL） @n
					※ダミーアクセス
		*/
		//-----------------------------------------------------------------//
		struct tiorl_t : public rw8_null_t<base + 0x03> {
			typedef rw8_null_t<base + 0x03> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IOC;
			bits_rw_t<io_, bitpos::B4, 4> IOD;
		};
		static inline tiorl_t TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ C（TGRC） @n
					※ダミーアクセス
		*/
		//-----------------------------------------------------------------//
		static inline rw16_null_t<base + 0x0C> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ D（TGRD） @n
					※ダミーアクセス
		*/
		//-----------------------------------------------------------------//
		static inline rw16_null_t<base + 0x0E> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマスタートレジスタ（TSTR）のエイリアス
			@param[in]	f	動作停止にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool f = true)
		{
			if(f) {
				BASE::TSTR |=  (1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			} else {
				BASE::TSTR &= ~(1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYR）のエイリアス
			@param[in]	f	同期解除にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void sync(bool f = true)
		{
			if(f) {
				BASE::TSYR |=  (1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			} else {
				BASE::TSYR &= ~(1 << (static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::TPU0)));
			}
		}
	};


#if defined(SIG_RX231)
	// グループベクターには無効表現が無い為、割り込みが無い場合「NUM_」としている。（I/O ドライバーのケアが必要）
	typedef tpu_x_t<0x0008'8110, peripheral::TPU0,
		ICU::VECTOR, ICU::VECTOR::TGI0A, ICU::VECTOR::TGI0B, ICU::VECTOR::TGI0C, ICU::VECTOR::TGI0D,
		ICU::VECTOR, ICU::VECTOR::TCI0V, ICU::VECTOR::NONE>  TPU0;
	typedef tpu_y_t<0x0008'8120, peripheral::TPU1,
		ICU::VECTOR, ICU::VECTOR::TGI1A, ICU::VECTOR::TGI1B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::VECTOR, ICU::VECTOR::TCI1V, ICU::VECTOR::TCI1U> TPU1;
	typedef tpu_y_t<0x0008'8130, peripheral::TPU2,
		ICU::VECTOR, ICU::VECTOR::TGI2A, ICU::VECTOR::TGI2B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::VECTOR, ICU::VECTOR::TCI2V, ICU::VECTOR::TCI2U> TPU2;
	typedef tpu_x_t<0x0008'8140, peripheral::TPU3,
		ICU::VECTOR, ICU::VECTOR::TGI3A, ICU::VECTOR::TGI3B, ICU::VECTOR::TGI3C, ICU::VECTOR::TGI3D,
		ICU::VECTOR, ICU::VECTOR::TCI3V, ICU::VECTOR::NONE>  TPU3;
	typedef tpu_y_t<0x0008'8150, peripheral::TPU4,
		ICU::VECTOR, ICU::VECTOR::TGI4A, ICU::VECTOR::TGI4B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::VECTOR, ICU::VECTOR::TCI4V, ICU::VECTOR::TCI4U> TPU4;
	typedef tpu_y_t<0x0008'8160, peripheral::TPU5,
		ICU::VECTOR, ICU::VECTOR::TGI5A, ICU::VECTOR::TGI5B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::VECTOR, ICU::VECTOR::TCI5V, ICU::VECTOR::TCI5U> TPU5;

#elif defined(SIG_RX631) || defined(SIG_RX63N)
	// グループベクターには無効表現が無い為、割り込みが無い場合「NUM_」としている。（I/O ドライバーのケアが必要）
	typedef tpu_x_t<0x0008'8110, peripheral::TPU0,
		ICU::VECTOR, ICU::VECTOR::TGI0A, ICU::VECTOR::TGI0B, ICU::VECTOR::TGI0C, ICU::VECTOR::TGI0D,
		ICU::GROUP3, ICU::GROUP3::TCI0V, ICU::GROUP3::NUM_>  TPU0;
	typedef tpu_y_t<0x0008'8120, peripheral::TPU1,
		ICU::VECTOR, ICU::VECTOR::TGI1A, ICU::VECTOR::TGI1B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::GROUP3, ICU::GROUP3::TCI1V, ICU::GROUP3::TCI1U> TPU1;
	typedef tpu_y_t<0x0008'8130, peripheral::TPU2,
		ICU::VECTOR, ICU::VECTOR::TGI2A, ICU::VECTOR::TGI2B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::GROUP4, ICU::GROUP4::TCI2V, ICU::GROUP4::TCI2U> TPU2;
	typedef tpu_x_t<0x0008'8140, peripheral::TPU3,
		ICU::VECTOR, ICU::VECTOR::TGI3A, ICU::VECTOR::TGI3B, ICU::VECTOR::TGI3C, ICU::VECTOR::TGI3D,
		ICU::GROUP4, ICU::GROUP4::TCI3V, ICU::GROUP4::NUM_>  TPU3;
	typedef tpu_y_t<0x0008'8150, peripheral::TPU4,
		ICU::VECTOR, ICU::VECTOR::TGI4A, ICU::VECTOR::TGI4B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::GROUP4, ICU::GROUP4::TCI4V, ICU::GROUP4::TCI4U> TPU4;
	typedef tpu_y_t<0x0008'8160, peripheral::TPU5,
		ICU::VECTOR, ICU::VECTOR::TGI5A, ICU::VECTOR::TGI5B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::GROUP3, ICU::GROUP3::TCI5V, ICU::GROUP3::TCI5U> TPU5;
	typedef tpu_x_t<0x0008'8180, peripheral::TPU6,
		ICU::VECTOR, ICU::VECTOR::TGI6A, ICU::VECTOR::TGI6B, ICU::VECTOR::TGI6C, ICU::VECTOR::TGI6D,
		ICU::GROUP5, ICU::GROUP5::TCI6V, ICU::GROUP5::NUM_>  TPU6;
	typedef tpu_y_t<0x0008'8190, peripheral::TPU7,
		ICU::VECTOR, ICU::VECTOR::TGI7A, ICU::VECTOR::TGI7B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::GROUP5, ICU::GROUP5::TCI7V, ICU::GROUP5::TCI7U> TPU7;
	typedef tpu_y_t<0x0008'81A0, peripheral::TPU8,
		ICU::VECTOR, ICU::VECTOR::TGI8A, ICU::VECTOR::TGI8B, ICU::VECTOR::NONE,  ICU::VECTOR::NONE,
		ICU::GROUP6, ICU::GROUP6::TCI8V, ICU::GROUP6::TCI8U> TPU8;
	typedef tpu_x_t<0x0008'81B0, peripheral::TPU9,
		ICU::VECTOR, ICU::VECTOR::TGI9A, ICU::VECTOR::TGI9B, ICU::VECTOR::TGI9C, ICU::VECTOR::TGI9D,
		ICU::GROUP6, ICU::GROUP6::TCI9V, ICU::GROUP6::NUM_>  TPU9;
	typedef tpu_y_t<0x0008'81C0, peripheral::TPU10,
		ICU::VECTOR, ICU::VECTOR::TGI10A, ICU::VECTOR::TGI10B, ICU::VECTOR::NONE, ICU::VECTOR::NONE,
		ICU::GROUP6, ICU::GROUP6::TCI10V, ICU::GROUP6::TCI10U> TPU10;
	typedef tpu_y_t<0x0008'81D0, peripheral::TPU11,
		ICU::VECTOR, ICU::VECTOR::TGI11A, ICU::VECTOR::TGI11B, ICU::VECTOR::NONE, ICU::VECTOR::NONE,
		ICU::GROUP5, ICU::GROUP5::TCI11V, ICU::GROUP5::TCI11U> TPU11;

#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef tpu_x_t<0x0008'8110, peripheral::TPU0,
		ICU::SELECTB, ICU::SELECTB::TGI0A, ICU::SELECTB::TGI0B, ICU::SELECTB::TGI0C, ICU::SELECTB::TGI0D,
		ICU::SELECTB, ICU::SELECTB::TGI0V, ICU::SELECTB::NONE>  TPU0;
	typedef tpu_y_t<0x0008'8120, peripheral::TPU1,
		ICU::SELECTB, ICU::SELECTB::TGI1A, ICU::SELECTB::TGI1B, ICU::SELECTB::NONE,  ICU::SELECTB::NONE,
		ICU::SELECTB, ICU::SELECTB::TGI1V, ICU::SELECTB::TGI1U> TPU1;
	typedef tpu_y_t<0x0008'8130, peripheral::TPU2,
		ICU::SELECTB, ICU::SELECTB::TGI2A, ICU::SELECTB::TGI2B, ICU::SELECTB::NONE,  ICU::SELECTB::NONE,
		ICU::SELECTB, ICU::SELECTB::TGI2V, ICU::SELECTB::TGI2U> TPU2;
	typedef tpu_x_t<0x0008'8140, peripheral::TPU3,
		ICU::SELECTB, ICU::SELECTB::TGI3A, ICU::SELECTB::TGI3B, ICU::SELECTB::TGI3C, ICU::SELECTB::TGI3D,
		ICU::SELECTB, ICU::SELECTB::TGI3V, ICU::SELECTB::NONE>  TPU3;
	typedef tpu_y_t<0x0008'8150, peripheral::TPU4,
		ICU::SELECTB, ICU::SELECTB::TGI4A, ICU::SELECTB::TGI4B, ICU::SELECTB::NONE,  ICU::SELECTB::NONE,
		ICU::SELECTB, ICU::SELECTB::TGI4V, ICU::SELECTB::TGI4U> TPU4;
	typedef tpu_y_t<0x0008'8160, peripheral::TPU5,
		ICU::SELECTB, ICU::SELECTB::TGI5A, ICU::SELECTB::TGI5B, ICU::SELECTB::NONE,  ICU::SELECTB::NONE,
		ICU::SELECTB, ICU::SELECTB::TGI5V, ICU::SELECTB::TGI5U> TPU5;
#endif
}
