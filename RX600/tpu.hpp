#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX651/RX65N/RX72N/RX72M 16 ビットタイマパルスユニット定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
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
		typedef tcr_t TCR_;
		static TCR_ TCR;


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
		typedef tmdr_t TMDR_;
		static TMDR_ TMDR;


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
		typedef tiorh_t TIORH_;
		static TIORH_ TIORH;


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
		typedef tier_t TIER_;
		static TIER_ TIER;


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
		typedef tsr_t TSR_;
		static TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x06> TCNT_;
		static TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ A（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x08> TGRA_;
		static TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ B（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0A> TGRB_;
		static TGRB_ TGRB;


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
		typedef tstr_t TSTR_;
		static TSTR_ TSTR;


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
		typedef tsyr_t TSYR_;
		static TSYR_ TSYR;


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
		typedef nfcr_t NFCR_;
		static NFCR_ NFCR;
	};
	template <uint32_t base> typename tpu_base_t<base>::TCR_   tpu_base_t<base>::TCR;
	template <uint32_t base> typename tpu_base_t<base>::TMDR_  tpu_base_t<base>::TMDR;
	template <uint32_t base> typename tpu_base_t<base>::TIORH_ tpu_base_t<base>::TIORH;
	template <uint32_t base> typename tpu_base_t<base>::TIER_  tpu_base_t<base>::TIER;
	template <uint32_t base> typename tpu_base_t<base>::TSR_   tpu_base_t<base>::TSR;
	template <uint32_t base> typename tpu_base_t<base>::TCNT_  tpu_base_t<base>::TCNT;
	template <uint32_t base> typename tpu_base_t<base>::TGRA_  tpu_base_t<base>::TGRA;
	template <uint32_t base> typename tpu_base_t<base>::TGRB_  tpu_base_t<base>::TGRB;
	template <uint32_t base> typename tpu_base_t<base>::TSTR_  tpu_base_t<base>::TSTR;
	template <uint32_t base> typename tpu_base_t<base>::TSYR_  tpu_base_t<base>::TSYR;
	template <uint32_t base> typename tpu_base_t<base>::NFCR_  tpu_base_t<base>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  16 ビットタイマパルスユニット・ベース（TPUa）TPU0, TPU3
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	intra	割り込み要因Ａ
		@param[in]	intrb	割り込み要因Ｂ
		@param[in]	intrc	割り込み要因Ｃ
		@param[in]	intrd	割り込み要因Ｄ
		@param[in]	intrv	割り込み要因Ｖ
		@param[in]	intru	割り込み要因Ｕ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb,
		ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd,
		ICU::VECTOR_SELB intrv, ICU::VECTOR_SELB intru>
	struct tpu_x_t : public tpu_base_t<base> {

		typedef tpu_base_t<base> BASE;

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto RA_INN = intra;	///< 割り込み要因Ａ
		static constexpr auto RB_INN = intrb;	///< 割り込み要因Ｂ
		static constexpr auto RC_INN = intrc;	///< 割り込み要因Ｃ
		static constexpr auto RD_INN = intrd;	///< 割り込み要因Ｄ
		static constexpr auto RV_INN = intrv;	///< 割り込み要因Ｖ
		static constexpr auto RU_INN = intru;	///< 割り込み要因Ｕ


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
		typedef tiorl_t TIORL_;
		static TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ C（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0C> TGRC_;
		static TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ D（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0E> TGRD_;
		static TGRD_ TGRD;


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
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb, ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd, ICU::VECTOR_SELB intru, ICU::VECTOR_SELB intrv>
		typename tpu_x_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TIORL_
		tpu_x_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TIORL;
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb, ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd, ICU::VECTOR_SELB intru, ICU::VECTOR_SELB intrv>
		typename tpu_x_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRC_
		tpu_x_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRC;
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb, ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd, ICU::VECTOR_SELB intru, ICU::VECTOR_SELB intrv>
		typename tpu_x_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRD_
		tpu_x_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRD;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  16 ビットタイマパルスユニット・ベース（TPUa）TPU1, TPU2, TPU4, TPU5
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	intra	割り込み要因Ａ
		@param[in]	intrb	割り込み要因Ｂ
		@param[in]	intrc	割り込み要因Ｃ
		@param[in]	intrd	割り込み要因Ｄ
		@param[in]	intrv	割り込み要因Ｖ
		@param[in]	intru	割り込み要因Ｕ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb,
		ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd,
		ICU::VECTOR_SELB intrv, ICU::VECTOR_SELB intru>
	struct tpu_y_t : public tpu_base_t<base> {

		typedef tpu_base_t<base> BASE;

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto RA_INN = intra;	///< 割り込み要因Ａ
		static constexpr auto RB_INN = intrb;	///< 割り込み要因Ｂ
		static constexpr auto RC_INN = intrc;	///< 割り込み要因Ｃ
		static constexpr auto RD_INN = intrd;	///< 割り込み要因Ｄ
		static constexpr auto RV_INN = intrv;	///< 割り込み要因Ｖ
		static constexpr auto RU_INN = intru;	///< 割り込み要因Ｕ


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
		typedef tiorl_t TIORL_;
		static TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ C（TGRC） @n
					※ダミーアクセス
		*/
		//-----------------------------------------------------------------//
		typedef rw16_null_t<base + 0x0C> TGRC_;
		static TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ D（TGRD） @n
					※ダミーアクセス
		*/
		//-----------------------------------------------------------------//
		typedef rw16_null_t<base + 0x0E> TGRD_;
		static TGRD_ TGRD;


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
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb, ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd, ICU::VECTOR_SELB intru, ICU::VECTOR_SELB intrv>
		typename tpu_y_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TIORL_
		tpu_y_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TIORL;
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb, ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd, ICU::VECTOR_SELB intru, ICU::VECTOR_SELB intrv>
		typename tpu_y_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRC_
		tpu_y_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRC;
	template <uint32_t base, peripheral per,
		ICU::VECTOR_SELB intra, ICU::VECTOR_SELB intrb, ICU::VECTOR_SELB intrc, ICU::VECTOR_SELB intrd, ICU::VECTOR_SELB intru, ICU::VECTOR_SELB intrv>
		typename tpu_y_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRD_
		tpu_y_t<base, per, intra, intrb, intrc, intrd, intru, intrv>::TGRD;


	typedef tpu_x_t<0x0008'8110, peripheral::TPU0,
		ICU::VECTOR_SELB::TGI0A, ICU::VECTOR_SELB::TGI0B,
		ICU::VECTOR_SELB::TGI0C, ICU::VECTOR_SELB::TGI0D,
		ICU::VECTOR_SELB::TGI0V, ICU::VECTOR_SELB::NONE>  TPU0;
	typedef tpu_y_t<0x0008'8120, peripheral::TPU1,
		ICU::VECTOR_SELB::TGI1A, ICU::VECTOR_SELB::TGI1B,
		ICU::VECTOR_SELB::NONE,  ICU::VECTOR_SELB::NONE,
		ICU::VECTOR_SELB::TGI1V, ICU::VECTOR_SELB::TGI1U> TPU1;
	typedef tpu_y_t<0x0008'8130, peripheral::TPU2,
		ICU::VECTOR_SELB::TGI2A, ICU::VECTOR_SELB::TGI2B,
		ICU::VECTOR_SELB::NONE,  ICU::VECTOR_SELB::NONE,
		ICU::VECTOR_SELB::TGI2V, ICU::VECTOR_SELB::TGI2U> TPU2;
	typedef tpu_x_t<0x0008'8140, peripheral::TPU3,
		ICU::VECTOR_SELB::TGI3A, ICU::VECTOR_SELB::TGI3B,
		ICU::VECTOR_SELB::TGI3C, ICU::VECTOR_SELB::TGI3D,
		ICU::VECTOR_SELB::TGI3V, ICU::VECTOR_SELB::NONE>  TPU3;
	typedef tpu_y_t<0x0008'8150, peripheral::TPU4,
		ICU::VECTOR_SELB::TGI4A, ICU::VECTOR_SELB::TGI4B,
		ICU::VECTOR_SELB::NONE,  ICU::VECTOR_SELB::NONE,
		ICU::VECTOR_SELB::TGI4V, ICU::VECTOR_SELB::TGI4U> TPU4;
	typedef tpu_y_t<0x0008'8160, peripheral::TPU5,
		ICU::VECTOR_SELB::TGI5A, ICU::VECTOR_SELB::TGI5B,
		ICU::VECTOR_SELB::NONE,  ICU::VECTOR_SELB::NONE,
		ICU::VECTOR_SELB::TGI5V, ICU::VECTOR_SELB::TGI5U> TPU5;
}
