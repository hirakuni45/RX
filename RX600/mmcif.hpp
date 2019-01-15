#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65N/RX651 マルチメディアカードインタフェース（MMCIF）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  マルチメディアカードインタフェースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mmcif_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コマンド設定レジスタ（ CECMDSET ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct cecmdset_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   DATW;

			bit_rw_t <io_, bitpos::B3>      SBIT;

			bit_rw_t <io_, bitpos::B6>      CPDM;
			bit_rw_t <io_, bitpos::B7>      TBIT;
			bit_rw_t <io_, bitpos::B8>      CRCSTE;
			bit_rw_t <io_, bitpos::B9>      BOOTACK;
			bit_rw_t <io_, bitpos::B10>     CRC16C;

			bits_rw_t<io_, bitpos::B12, 2>  RCRC7C;
			bits_rw_t<io_, bitpos::B14, 2>  RIDXC;
			bit_rw_t <io_, bitpos::B16>     CMD12EN;
			bit_rw_t <io_, bitpos::B17>     CMLTE;
			bit_rw_t <io_, bitpos::B18>     DWEN;
			bit_rw_t <io_, bitpos::B19>     WDAT;

			bit_rw_t <io_, bitpos::B21>     RBSY;
			bits_rw_t<io_, bitpos::B22, 2>  RTYP;
			bits_rw_t<io_, bitpos::B24, 6>  CMD;
			bit_rw_t <io_, bitpos::B30>     BOOT;
		};
		static cecmdset_t<0x00088500> CECMDSET;


		//-----------------------------------------------------------------//
		/*!
			@brief  アーギュメントレジスタ（ CEARG ）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x00088508>  CEARG;


		//-----------------------------------------------------------------//
		/*!
			@brief  自動 CMD12 アーギュメントレジスタ（ CEARGCMD12 ）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x0008850C>  CEARGCMD12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コマンド制御レジスタ（ CECMDCTRL ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct cecmdctrl_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B3>  BREAK;
		};
		static cecmdctrl_t<0x00088510> CECMDCTRL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  転送ブロック設定レジスタ（ CEBLOCKSET ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ceblockset_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  BLKSIZ;
			bits_rw_t<io_, bitpos::B16, 16>  BLKCNT;
		};
		static ceblockset_t<0x00088514> CEBLOCKSET;









		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return peripheral::MMCIF; }
	};

	typedef mmcif_t MMCIF;
}
