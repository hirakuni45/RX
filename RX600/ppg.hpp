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
		struct ptrslr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PTRSL;
		};
		typedef ptrslr_t_<0x000881F0> ptrslr_t;
		static ptrslr_t PTRSLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータレジスタ H（NDRH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ndrh_t_ : public rw8_t<base> {
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
		typedef ndrh_t_<0x000881EC + ch * 2> ndrh_t;
		static ndrh_t NDRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータレジスタ L（NDRL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ndrl_t_ : public rw8_t<base> {
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
		typedef ndrl_t_<0x000881ED + ch * 2> ndrl_t;
		static ndrl_t NDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  PPG 出力コントロールレジスタ（PCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pcr_t_ : public rw8_t<base> {
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
		typedef pcr_t_<0x000881E6 + ch * 0x10> pcr_t;
		static pcr_t PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PPG 出力モードレジスタ（PMR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmr_t_ : public rw8_t<base> {
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
		typedef pmr_t_<0x000881E7 + ch * 0x10> pmr_t;
		static pmr_t PMR;


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
		struct nderh_t_ : public rw8_t<base> {
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
		typedef nderh_t_<0x000881E8> nderh_t;
		static nderh_t NDERH;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータイネーブルレジスタ L（NDERL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nderl_t_ : public rw8_t<base> {
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
		typedef nderl_t_<0x000881E9> nderl_t;
		static nderl_t NDERL;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ H（PODRH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrh_t_ : public rw8_t<base> {
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
		typedef podrh_t_<0x000881EA> podrh_t;
		static podrh_t PODRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ L（PODRL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrl_t_ : public rw8_t<base> {
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
		typedef podrl_t_<0x000881EB> podrl_t;
		static podrl_t PODRL;
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
		struct nderh_t_ : public rw8_t<base> {
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
		typedef nderh_t_<0x000881F8> nderh_t;
		static nderh_t NDERH;


		//-----------------------------------------------------------------//
		/*!
			@brief  ネクストデータイネーブルレジスタ L（NDERL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nderl_t_ : public rw8_t<base> {
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
		typedef nderl_t_<0x000881F9> nderl_t;
		static nderl_t NDERL;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ H（PODRH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrh_t_ : public rw8_t<base> {
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
		typedef podrh_t_<0x000881FA> podrh_t;
		static podrh_t PODRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  アウトプットデータレジスタ L（PODRL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct podrl_t_ : public rw8_t<base> {
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
		typedef podrl_t_<0x000881FB> podrl_t;
		static podrl_t PODRL;
	};


	typedef ppg0_t<0, peripheral::PPG0> PPG0;
	typedef ppg1_t<1, peripheral::PPG1> PPG1;

	template <uint32_t ch, peripheral per> typename ppg_t<ch, per>::ptrslr_t ppg_t<ch, per>::PTRSLR;
	template <uint32_t ch, peripheral per> typename ppg_t<ch, per>::ndrh_t ppg_t<ch, per>::NDRH;
	template <uint32_t ch, peripheral per> typename ppg_t<ch, per>::ndrl_t ppg_t<ch, per>::NDRL;
	template <uint32_t ch, peripheral per> typename ppg_t<ch, per>::pcr_t ppg_t<ch, per>::PCR;
	template <uint32_t ch, peripheral per> typename ppg_t<ch, per>::pmr_t ppg_t<ch, per>::PMR;

	template <uint32_t ch, peripheral per> typename ppg0_t<ch, per>::nderh_t ppg0_t<ch, per>::NDERH;
	template <uint32_t ch, peripheral per> typename ppg0_t<ch, per>::nderl_t ppg0_t<ch, per>::NDERL;
	template <uint32_t ch, peripheral per> typename ppg0_t<ch, per>::podrh_t ppg0_t<ch, per>::PODRH;
	template <uint32_t ch, peripheral per> typename ppg0_t<ch, per>::podrl_t ppg0_t<ch, per>::PODRL;

	template <uint32_t ch, peripheral per> typename ppg1_t<ch, per>::nderh_t ppg1_t<ch, per>::NDERH;
	template <uint32_t ch, peripheral per> typename ppg1_t<ch, per>::nderl_t ppg1_t<ch, per>::NDERL;
	template <uint32_t ch, peripheral per> typename ppg1_t<ch, per>::podrh_t ppg1_t<ch, per>::PODRH;
	template <uint32_t ch, peripheral per> typename ppg1_t<ch, per>::podrl_t ppg1_t<ch, per>::PODRL;
}
