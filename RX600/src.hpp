#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SRC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	サンプリングレートコンバータ（SRC）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct src_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  入力データレジスタ（ SRCID ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0009DFF0> SRCID_;
		static  SRCID_ SRCID;


		//-----------------------------------------------------------------//
		/*!
			@brief  出力データレジスタ（ SRCOD ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0009DFF4> SRCOD_;
		static  SRCOD_ SRCOD;


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
		typedef srcidctrl_t<0x0009DFF8> SRCIDCTRL_;
		static  SRCIDCTRL_ SRCIDCTRL;


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
		typedef srcodctrl_t<0x0009DFFA> SRCODCTRL_;
		static  SRCODCTRL_ SRCODCTRL;


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
		typedef srcctrl_t<0x0009DFFC> SRCCTRL_;
		static  SRCCTRL_ SRCCTRL;


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
		typedef srcstat_t<0x0009DFFE> SRCSTAT_;
		static  SRCSTAT_ SRCSTAT;


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
		typedef srcfctr_t<0x00098000> SRCFCTR_;
		static  SRCFCTR_ SRCFCTR;
	};
	template <peripheral per> typename src_t<per>::SRCID_ src_t<per>::SRCID;
	template <peripheral per> typename src_t<per>::SRCOD_ src_t<per>::SRCOD;
	template <peripheral per> typename src_t<per>::SRCIDCTRL_ src_t<per>::SRCIDCTRL;
	template <peripheral per> typename src_t<per>::SRCODCTRL_ src_t<per>::SRCODCTRL;
	template <peripheral per> typename src_t<per>::SRCCTRL_ src_t<per>::SRCCTRL;
	template <peripheral per> typename src_t<per>::SRCSTAT_ src_t<per>::SRCSTAT;
	template <peripheral per> typename src_t<per>::SRCFCTR_ src_t<per>::SRCFCTR;


	typedef src_t<peripheral::SRC> SRC;
}
