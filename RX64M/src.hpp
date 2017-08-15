#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・SRC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX64M/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	サンプリングレートコンバータ（SRC）
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct src_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  入力データレジスタ（ SRCID ）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x0009DFF0> SRCID;


		//-----------------------------------------------------------------//
		/*!
			@brief  出力データレジスタ（ SRCOD ）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x0009DFF4> SRCOD;


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
		static srcidctrl_t<0x0009DFF8> SRCIDCTRL;


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
		static srcodctrl_t<0x0009DFFA> SRCODCTRL;


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
		static srcctrl_t<0x0009DFFC> SRCCTRL;


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
		static srcstat_t<0x0009DFFE> SRCSTAT;


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
		static srcfctr_t<0x00098000> SRCFCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }

	};
	typedef src_t<peripheral::SRC> SRC;
}
