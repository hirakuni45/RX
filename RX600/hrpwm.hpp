#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T/RX66T/RX72T グループ・HRPWM 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief   高分解能 PWM 波形生成回路 クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct hrpwm_t {

		static constexpr auto PERIPHERAL = peripheral::HRPWM;	///< ペリフェラル型

		//=================================================================//
		/*!
			@brief  HRPWM 動作制御レジスタ (HROCR)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrocr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DLLEN;
			bit_rw_t<io_, bitpos::B1>  HRRST;
		};
		static inline hrocr_t<0x000C'2A00> HROCR;


		//=================================================================//
		/*!
			@brief  HRPWM 動作制御レジスタ 2 (HROCR2)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrocr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   HRSEL0;
			bit_rw_t<io_, bitpos::B1>   HRSEL1;
			bit_rw_t<io_, bitpos::B2>   HRSEL2;
			bit_rw_t<io_, bitpos::B3>   HRSEL3;

			bit_rw_t<io_, bitpos::B8>   HRDIS0;
			bit_rw_t<io_, bitpos::B9>   HRDIS1;
			bit_rw_t<io_, bitpos::B10>  HRDIS2;
			bit_rw_t<io_, bitpos::B11>  HRDIS3;
		};
		static inline hrocr2_t<0x000C'2A02> HROCR2;


		//=================================================================//
		/*!
			@brief  GTIOCnA 端子立ち上がりエッジ調整レジスタ (HRREARnA) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrrearna_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		static inline hrrearna_t<0x000C'2A18> HRREAR0A;
		static inline hrrearna_t<0x000C'2A1C> HRREAR1A;
		static inline hrrearna_t<0x000C'2A20> HRREAR2A;
		static inline hrrearna_t<0x000C'2A24> HRREAR3A;


		//=================================================================//
		/*!
			@brief  GTIOCnA 端子立ち下がりエッジ調整レジスタ (HRFEARnA) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrfearna_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		static inline hrfearna_t<0x000C'2A28> HRFEAR0A;
		static inline hrfearna_t<0x000C'2A2C> HRFEAR1A;
		static inline hrfearna_t<0x000C'2A30> HRFEAR2A;
		static inline hrfearna_t<0x000C'2A34> HRFEAR3A;


		//=================================================================//
		/*!
			@brief  GTIOCnB 端子立ち上がりエッジ調整レジスタ (HRREARnB) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrrearnb_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		static inline hrrearnb_t<0x000C'2A1A> HRREAR0B;
		static inline hrrearnb_t<0x000C'2A1E> HRREAR1B;
		static inline hrrearnb_t<0x000C'2A22> HRREAR2B;
		static inline hrrearnb_t<0x000C'2A26> HRREAR3B;


		//=================================================================//
		/*!
			@brief  GTIOCnB 端子立ち下がりエッジ調整レジスタ (HRFEARnB) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrfearnb_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		static inline hrfearnb_t<0x000C'2A1A> HRFEAR0B;
		static inline hrfearnb_t<0x000C'2A1E> HRFEAR1B;
		static inline hrfearnb_t<0x000C'2A22> HRFEAR2B;
		static inline hrfearnb_t<0x000C'2A26> HRFEAR3B;

#if defined(SIG_RX72T)
		//=================================================================//
		/*!
			@brief  HRPWM 動作クロック選択レジスタ (HRCKSR)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrcksr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  HRCKSEL;
		};
		static inline hrcksr_t<0x000C'2A70> HRCKSR;
#endif
	};
	typedef hrpwm_t HRPWM;
}
