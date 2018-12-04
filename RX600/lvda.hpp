#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ LVDA 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  電圧検出回路（LVDA）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct lvda_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  電圧監視 1 回路制御レジスタ 1（LVD1CR1）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvd1cr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  LVD1IDTSEL;
			bit_rw_t <io_, bitpos::B2>     LVD1IRQSEL;
		};
		static lvd1cr1_t<0x000800E0>  LVD1CR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧監視 1 回路ステータスレジスタ（LVD1SR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvd1sr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   LVD1DET;
			bit_ro_t <io_, bitpos::B1>   LVD1MON;
		};
		static lvd1sr_t<0x000800E1>  LVD1SR;


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧監視 2 回路制御レジスタ 1（LVD2CR1）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvd2cr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  LVD2IDTSEL;
			bit_rw_t <io_, bitpos::B2>     LVD2IRQSEL;
		};
		static lvd2cr1_t<0x000800E2>  LVD2CR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧監視 2 回路ステータスレジスタ（LVD2SR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvd2sr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   LVD2DET;
			bit_ro_t <io_, bitpos::B1>   LVD2MON;
		};
		static lvd2sr_t<0x000800E3>  LVD2SR;


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧監視回路制御レジスタ（LVCMPCR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvcmpcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B5>   LVD1E;
			bit_rw_t<io_, bitpos::B6>   LVD2E;
		};
		static lvcmpcr_t<0x0008C297>  LVCMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧検出レベル選択レジスタ（LVDLVLR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvdlvlr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   LVD1LVL;
#if defined(SIG_RX24T)
			bits_rw_t<io_, bitpos::B4, 2>   LVD2LVL;
#else
			bits_rw_t<io_, bitpos::B4, 4>   LVD2LVL;
#endif
		};
		static lvdlvlr_t<0x0008C298>  LVDLVLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧監視 1 回路制御レジスタ 0（LVD1CR0）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvd1cr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     LVD1RIE;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
			bit_rw_t <io_, bitpos::B1>     LVD1DFDIS;
#endif
			bit_rw_t <io_, bitpos::B2>     LVD1CMPE;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B4, 2>  LVD1FSAMP;
#endif
			bit_rw_t <io_, bitpos::B6>     LVD1RI;
			bit_rw_t <io_, bitpos::B7>     LVD1RN;
		};
		static lvd1cr0_t<0x0008C29A>  LVD1CR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧監視 2 回路制御レジスタ 0（LVD2CR0）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvd2cr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     LVD2RIE;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
			bit_rw_t <io_, bitpos::B1>     LVD2DFDIS;
#endif
			bit_rw_t <io_, bitpos::B2>     LVD2CMPE;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B4, 2>  LVD2FSAMP;
#endif
			bit_rw_t <io_, bitpos::B6>     LVD2RI;
			bit_rw_t <io_, bitpos::B7>     LVD2RN;
		};
		static lvd2cr0_t<0x0008C29B>  LVD2CR0;
	};
	typedef lvda_t LVDA;
}
