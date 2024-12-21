#pragma once
//=========================================================================//
/*!	@file
	@brief	Sampling Rate Converter / サンプリングレートコンバータ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	SRC class
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct src_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  入力データレジスタ（ SRCID ）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0009'DFF0> SRCID;


		//-----------------------------------------------------------------//
		/*!
			@brief  出力データレジスタ（ SRCOD ）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0009'DFF4> SRCOD;


		//-----------------------------------------------------------------//
		/*!
			@brief  入力データ制御レジスタ（ SRCIDCTRL ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct srcidctrl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  IFTRG;
			bit_rw_t< io_, bitpos::B8>     IEN;
			bit_rw_t< io_, bitpos::B9>     IED;
		};
		static inline srcidctrl_t<0x0009'DFF8> SRCIDCTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  出力データ制御レジスタ（ SRCODCTRL ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct srcodctrl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OFTRG;
			bit_rw_t< io_, bitpos::B8>     OEN;
			bit_rw_t< io_, bitpos::B9>     OED;
			bit_rw_t< io_, bitpos::B10>    OCH;
		};
		static inline srcodctrl_t<0x0009'DFFA> SRCODCTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ（ SRCCTRL ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct srcctrl_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OFS;
			bits_rw_t<io_, bitpos::B4, 4>  IFS;
			bit_rw_t< io_, bitpos::B8>     CL;
			bit_rw_t< io_, bitpos::B9>     FL;
			bit_rw_t< io_, bitpos::B10>    OVEN;
			bit_rw_t< io_, bitpos::B11>    UDEN;
			bit_rw_t< io_, bitpos::B12>    SRCEN;
			bit_rw_t< io_, bitpos::B13>    CEEN;

			bit_rw_t< io_, bitpos::B15>    FICRAE;
		};
		static inline srcctrl_t<0x0009'DFFC> SRCCTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ（ SRCSTAT ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct srcstat_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			typedef ro16_t<ofs> ro_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     OINT;
			bit_rw_t< io_, bitpos::B1>     IINT;
			bit_rw_t< io_, bitpos::B2>     OVF;
			bit_rw_t< io_, bitpos::B3>     UDF;
			bit_rw_t< ro_, bitpos::B4>     ELF;
			bit_rw_t< io_, bitpos::B5>     CEF;

			bits_rw_t<ro_, bitpos::B7,  4> OIFDN;
			bits_rw_t<ro_, bitpos::B11, 5> OFDN;

		};
		static inline srcstat_t<0x0009'DFFE> SRCSTAT;


		//-----------------------------------------------------------------//
		/*!
			@brief  フィルタ係数テーブル n （ SRCFCTRn ）（ n = 0 ～ 5551 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct srcfctr_t {
			uint32_t get(uint16_t idx) const { return rd32_(ofs + idx); }

			void put(uint16_t idx, uint32_t val) { wr32_(ofs + idx, val); }

			uint32_t operator() (uint16_t idx) const { return get(idx); }

//			void operator[] (uint16_t idx) { put(idx, val); }
		};
		static inline srcfctr_t<0x0009'8000> SRCFCTR;
	};
	typedef src_t<peripheral::SRC> SRC;
}
