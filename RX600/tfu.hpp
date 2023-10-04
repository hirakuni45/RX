#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・三角関数演算器 (TFUv2) 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  三角関数演算器 (TFUv2) クラス
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
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
		typedef fxscioc_t<0x0008'1404> FXSCIOC_;
		static  FXSCIOC_ FXSCIOC;


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
		typedef fxatioc_t<0x0008'1405> FXATIOC_;
		static  FXATIOC_ FXATIOC;


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
		typedef trgsts_t<0x0008'1408> TRGSTS_;
		static  TRGSTS_ TRGSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 sincos 処理用データレジスタ 0 (FPSCDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1410> FPSCDT0_;
		static  FPSCDT0_ FPSCDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 sincos 処理用データレジスタ 1 (FPSCDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1414> FPSCDT1_;
		static  FPSCDT1_ FPSCDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 atanhypot_k 処理用データレジスタ 0 (FPATDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1418> FPATDT0_;
		static  FPATDT0_ FPATDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	浮動小数 atanhypot_k 処理用データレジスタ 1 (FPATDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'141C> FPATDT1_;
		static  FPATDT1_ FPATDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 sincos 処理用データレジスタ 0 (FXSCDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1420> FXSCDT0_;
		static  FXSCDT0_ FXSCDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 sincos 処理用データレジスタ 1 (FXSCDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1424> FXSCDT1_;
		static  FXSCDT1_ FXSCDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 atanhypot_k 処理用データレジスタ 0 (FXATDT0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1428> FXATDT0_;
		static  FXATDT0_ FXATDT0;


		//-----------------------------------------------------------------//
		/*!
			@brief	固定小数 atanhypot_k 処理用データレジスタ 1 (FXATDT1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'142C> FXATDT1_;
		static  FXATDT1_ FXATDT1;


		//-----------------------------------------------------------------//
		/*!
			@brief	データ退避復帰用レジスタ 0 (DTSR0)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1430> DTSR0_;
		static  DTSR0_ DTSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	データ退避復帰用レジスタ 1 (DTSR1)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'1434> DTSR1_;
		static  DTSR1_ DTSR1;
	};
	template<class _> typename tfu_t<_>::FXSCIOC_ tfu_t<_>::FXSCIOC;
	template<class _> typename tfu_t<_>::FXATIOC_ tfu_t<_>::FXATIOC;
	template<class _> typename tfu_t<_>::TRGSTS_  tfu_t<_>::TRGSTS;
	template<class _> typename tfu_t<_>::FPSCDT0_ tfu_t<_>::FPSCDT0;
	template<class _> typename tfu_t<_>::FPSCDT1_ tfu_t<_>::FPSCDT1;
	template<class _> typename tfu_t<_>::FPATDT0_ tfu_t<_>::FPATDT0;
	template<class _> typename tfu_t<_>::FPATDT1_ tfu_t<_>::FPATDT1;
	template<class _> typename tfu_t<_>::FXSCDT0_ tfu_t<_>::FXSCDT0;
	template<class _> typename tfu_t<_>::FXSCDT1_ tfu_t<_>::FXSCDT1;
	template<class _> typename tfu_t<_>::FXATDT0_ tfu_t<_>::FXATDT0;
	template<class _> typename tfu_t<_>::FXATDT1_ tfu_t<_>::FXATDT1;
	template<class _> typename tfu_t<_>::DTSR0_   tfu_t<_>::DTSR0;
	template<class _> typename tfu_t<_>::DTSR1_   tfu_t<_>::DTSR1;

	typedef tfu_t<void> TFU;
}
