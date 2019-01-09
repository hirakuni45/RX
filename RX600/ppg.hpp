#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65N グループ・PPG 定義
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
		@brief	プログラマブルパルスジェネレータ（PPG）
		@param[in]	ch		チャネル
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ch, peripheral per>
	struct ppg_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  PPG トリガセレクトレジスタ（PTRSLR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ptrslr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PTRSL;
		};
		static ptrslr_t<0x000881F0> PTRSLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータレジスタ H（NDRH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ndrh_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  NDR8;
			bit_rw_t<io_, bitpos::B1>  NDR9;
			bit_rw_t<io_, bitpos::B2>  NDR10;
			bit_rw_t<io_, bitpos::B3>  NDR11;
			bit_rw_t<io_, bitpos::B4>  NDR12;
			bit_rw_t<io_, bitpos::B5>  NDR13;
			bit_rw_t<io_, bitpos::B6>  NDR14;
			bit_rw_t<io_, bitpos::B7>  NDR15;
		};
		static ndrh_t<0x000881EC + ch * 2> NDRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータレジスタ L（NDRL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ndrl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  NDR0;
			bit_rw_t<io_, bitpos::B1>  NDR1;
			bit_rw_t<io_, bitpos::B2>  NDR2;
			bit_rw_t<io_, bitpos::B3>  NDR3;
			bit_rw_t<io_, bitpos::B4>  NDR4;
			bit_rw_t<io_, bitpos::B5>  NDR5;
			bit_rw_t<io_, bitpos::B6>  NDR6;
			bit_rw_t<io_, bitpos::B7>  NDR7;
		};
		static ndrl_t<0x000881ED + ch * 2> NDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  PPG 出力コントロールレジスタ（PCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  G0CMS;
			bits_rw_t<io_, bitpos::B2, 2>  G1CMS;
			bits_rw_t<io_, bitpos::B4, 2>  G2CMS;
			bits_rw_t<io_, bitpos::B6, 2>  G3CMS;
		};
		static pcr_t<0x000881E6 + ch * 0x10> PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PPG 出力モードレジスタ（PMR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  G0NOV;
			bit_rw_t<io_, bitpos::B1>  G1NOV;
			bit_rw_t<io_, bitpos::B2>  G2NOV;
			bit_rw_t<io_, bitpos::B3>  G3NOV;
			bit_rw_t<io_, bitpos::B4>  G0INV;
			bit_rw_t<io_, bitpos::B5>  G1INV;
			bit_rw_t<io_, bitpos::B6>  G2INV;
			bit_rw_t<io_, bitpos::B7>  G3INV;
		};
		static pmr_t<0x000881E7 + ch * 0x10> PMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	プログラマブルパルスジェネレータ（PPG0）
		@param[in]	ch		チャネル
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ch, peripheral per>
	struct ppg0_t : public ppg_t<ch, per> {

		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータイネーブルレジスタ H（NDERH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nderh_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  NDER8;
			bit_rw_t<io_, bitpos::B1>  NDER9;
			bit_rw_t<io_, bitpos::B2>  NDER10;
			bit_rw_t<io_, bitpos::B3>  NDER11;
			bit_rw_t<io_, bitpos::B4>  NDER12;
			bit_rw_t<io_, bitpos::B5>  NDER13;
			bit_rw_t<io_, bitpos::B6>  NDER14;
			bit_rw_t<io_, bitpos::B7>  NDER15;
		};
		static nderh_t<0x000881E8> NDERH;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータイネーブルレジスタ L（NDERL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nderl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  NDER0;
			bit_rw_t<io_, bitpos::B1>  NDER1;
			bit_rw_t<io_, bitpos::B2>  NDER2;
			bit_rw_t<io_, bitpos::B3>  NDER3;
			bit_rw_t<io_, bitpos::B4>  NDER4;
			bit_rw_t<io_, bitpos::B5>  NDER5;
			bit_rw_t<io_, bitpos::B6>  NDER6;
			bit_rw_t<io_, bitpos::B7>  NDER7;
		};
		static nderl_t<0x000881E9> NDERL;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ H（PODRH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrh_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POD8;
			bit_rw_t<io_, bitpos::B1>  POD9;
			bit_rw_t<io_, bitpos::B2>  POD10;
			bit_rw_t<io_, bitpos::B3>  POD11;
			bit_rw_t<io_, bitpos::B4>  POD12;
			bit_rw_t<io_, bitpos::B5>  POD13;
			bit_rw_t<io_, bitpos::B6>  POD14;
			bit_rw_t<io_, bitpos::B7>  POD15;
		};
		static podrh_t<0x000881EA> PODRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ L（PODRL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POD0;
			bit_rw_t<io_, bitpos::B1>  POD1;
			bit_rw_t<io_, bitpos::B2>  POD2;
			bit_rw_t<io_, bitpos::B3>  POD3;
			bit_rw_t<io_, bitpos::B4>  POD4;
			bit_rw_t<io_, bitpos::B5>  POD5;
			bit_rw_t<io_, bitpos::B6>  POD6;
			bit_rw_t<io_, bitpos::B7>  POD7;
		};
		static podrl_t<0x000881EB> PODRL;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	プログラマブルパルスジェネレータ（PPG1）
		@param[in]	ch		チャネル
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ch, peripheral per>
	struct ppg1_t : public ppg_t<ch, per> {

		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータイネーブルレジスタ H（NDERH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nderh_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  NDER24;
			bit_rw_t<io_, bitpos::B1>  NDER25;
			bit_rw_t<io_, bitpos::B2>  NDER26;
			bit_rw_t<io_, bitpos::B3>  NDER27;
			bit_rw_t<io_, bitpos::B4>  NDER28;
			bit_rw_t<io_, bitpos::B5>  NDER29;
			bit_rw_t<io_, bitpos::B6>  NDER30;
			bit_rw_t<io_, bitpos::B7>  NDER31;
		};
		static nderh_t<0x000881F8> NDERH;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータイネーブルレジスタ L（NDERL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nderl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  NDER16;
			bit_rw_t<io_, bitpos::B1>  NDER17;
			bit_rw_t<io_, bitpos::B2>  NDER18;
			bit_rw_t<io_, bitpos::B3>  NDER19;
			bit_rw_t<io_, bitpos::B4>  NDER20;
			bit_rw_t<io_, bitpos::B5>  NDER21;
			bit_rw_t<io_, bitpos::B6>  NDER22;
			bit_rw_t<io_, bitpos::B7>  NDER23;
		};
		static nderl_t<0x000881F9> NDERL;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ H（PODRH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrh_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POD24;
			bit_rw_t<io_, bitpos::B1>  POD25;
			bit_rw_t<io_, bitpos::B2>  POD26;
			bit_rw_t<io_, bitpos::B3>  POD27;
			bit_rw_t<io_, bitpos::B4>  POD28;
			bit_rw_t<io_, bitpos::B5>  POD29;
			bit_rw_t<io_, bitpos::B6>  POD30;
			bit_rw_t<io_, bitpos::B7>  POD31;
		};
		static podrh_t<0x000881FA> PODRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ L（PODRL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POD16;
			bit_rw_t<io_, bitpos::B1>  POD17;
			bit_rw_t<io_, bitpos::B2>  POD18;
			bit_rw_t<io_, bitpos::B3>  POD19;
			bit_rw_t<io_, bitpos::B4>  POD20;
			bit_rw_t<io_, bitpos::B5>  POD21;
			bit_rw_t<io_, bitpos::B6>  POD22;
			bit_rw_t<io_, bitpos::B7>  POD23;
		};
		static podrl_t<0x000881FB> PODRL;
	};


	typedef ppg0_t<0, peripheral::PPG0> PPG0;
	typedef ppg1_t<1, peripheral::PPG1> PPG1;
}
