#pragma once
//=========================================================================//
/*!	@file
	@brief	Trigonometrical function calculator / 三角関数演算器
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TFUv2 class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct tfu_t {

		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 sincos 入出力設定レジスタ (FXSCIOC)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fxscioc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     IUF;

			bits_rw_t<io_, bitpos::B3, 2>  OF;
		};
		static inline fxscioc_t<0x0008'1404> FXSCIOC;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 atanhypot_k 入出力設定レジスタ (FXATIOC)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fxatioc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B4>     OUF;
		};
		static inline fxatioc_t<0x0008'1405> FXATIOC;


		//-----------------------------------------------------------------//
		/*!
			@brief	三角関数演算器ステータスレジスタ (TRGSTS)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct trgsts_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     BSYF;
			bit_rw_t <io_, bitpos::B1>     ERRF;
		};
		static inline trgsts_t<0x0008'1408> TRGSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 sincos 処理用データレジスタ 0 (FPSCDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1410> FPSCDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 sincos 処理用データレジスタ 1 (FPSCDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1414> FPSCDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 atanhypot_k 処理用データレジスタ 0 (FPATDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1418> FPATDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 atanhypot_k 処理用データレジスタ 1 (FPATDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'141C> FPATDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 sincos 処理用データレジスタ 0 (FXSCDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1420> FXSCDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 sincos 処理用データレジスタ 1 (FXSCDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1424> FXSCDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 atanhypot_k 処理用データレジスタ 0 (FXATDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1428> FXATDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 atanhypot_k 処理用データレジスタ 1 (FXATDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'142C> FXATDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	データ退避復帰用レジスタ 0 (DTSR0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1430> DTSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	データ退避復帰用レジスタ 1 (DTSR1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'1434> DTSR1;
	};
	typedef tfu_t TFU;
}
