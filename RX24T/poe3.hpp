#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ポートアウトプットイネーブル 3（POE3b）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX24T/peripheral.hpp"
#include "RX24T/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  POE3 全体定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct poe3_t {

		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 1（ICSR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE0M;
			bit_rw_t <io_, bitpos::B8>     PIE1;
			bit_rw_t <io_, bitpos::B12>    POE0F;
		};
		static icsr1_t<0x0008C4C0> ICSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 2（ICSR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE4M;
			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		static icsr2_t<0x0008C4C4> ICSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 3（ICSR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE8M;
			bit_rw_t <io_, bitpos::B8>     PIE3;
			bit_rw_t <io_, bitpos::B9>     POE8E;
			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		static icsr3_t<0x0008C4C8> ICSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 4（ICSR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr4_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE10M;
			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B9>     POE10E;
			bit_rw_t <io_, bitpos::B12>    POE10F;
		};
		static icsr4_t<0x0008C4D6> ICSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 5（ICSR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr5_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE11M;
			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;
			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		static icsr5_t<0x0008C4D8> ICSR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 6（ICSR6）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr6_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B9>     OSTSTE;
			bit_rw_t <io_, bitpos::B12>    OSTSTF;
		};
		static icsr6_t<0x0008C4DC> ICSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 7（ICSR7）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr7_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE12M;
			bit_rw_t <io_, bitpos::B8>     PIE7;
			bit_rw_t <io_, bitpos::B9>     POE12E;
			bit_rw_t <io_, bitpos::B12>    POE12F;
		};
		static icsr7_t<0x0008C4E0> ICSR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 1（OCSR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>     OIE1;
			bit_rw_t <io_, bitpos::B9>     OCE1;
			bit_rw_t <io_, bitpos::B15>    OSF1;
		};
		static ocsr1_t<0x0008C4C2> OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 1（OCSR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>     OIE2;
			bit_rw_t <io_, bitpos::B9>     OCE2;
			bit_rw_t <io_, bitpos::B15>    OSF2;
		};
		static ocsr2_t<0x0008C4C6> OCSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 1（ALR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  OLSG0A;
			bit_rw_t<io_, bitpos::B1>  OLSG0B;
			bit_rw_t<io_, bitpos::B2>  OLSG1A;
			bit_rw_t<io_, bitpos::B3>  OLSG1B;
			bit_rw_t<io_, bitpos::B4>  OLSG2A;
			bit_rw_t<io_, bitpos::B5>  OLSG2B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		static alr1_t<0x0008C4DA> ALR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 2（ALR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  OLSG4A;
			bit_rw_t<io_, bitpos::B1>  OLSG4B;
			bit_rw_t<io_, bitpos::B2>  OLSG5A;
			bit_rw_t<io_, bitpos::B3>  OLSG5B;
			bit_rw_t<io_, bitpos::B4>  OLSG6A;
			bit_rw_t<io_, bitpos::B5>  OLSG6B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		static alr2_t<0x0008C4DE> ALR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ（SPOER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct spoer_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTUCH34HIZ;
			bit_rw_t<io_, bitpos::B1>  MTUCH67HIZ;
			bit_rw_t<io_, bitpos::B2>  MTUCH0HIZ;

			bit_rw_t<io_, bitpos::B6>  MTUCH9HIZ;
		};
		static spoer_t<0x0008C4CA> SPOER;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 1（POECR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AZE;
			bit_rw_t<io_, bitpos::B1>  MTU0BZE;
			bit_rw_t<io_, bitpos::B2>  MTU0CZE;
			bit_rw_t<io_, bitpos::B3>  MTU0DZE;
			bit_rw_t<io_, bitpos::B4>  MTU0A1ZE;
			bit_rw_t<io_, bitpos::B5>  MTU0B1ZE;
		};
		static poecr1_t<0x0008C4CB> POECR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 2（POECR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU7BDZE;
			bit_rw_t<io_, bitpos::B1>  MTU7ACZE;
			bit_rw_t<io_, bitpos::B2>  MTU6BDZE;

			bit_rw_t<io_, bitpos::B8>  MTU4BDZE;
			bit_rw_t<io_, bitpos::B9>  MTU4ACZE;
			bit_rw_t<io_, bitpos::B10> MTU3BDZE;
		};
		static poecr2_t<0x0008C4CC> POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4（POECR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr4_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDMT34ZE;

			bit_rw_t<io_, bitpos::B1>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B2>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC5ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC6ADDMT34ZE;

			bit_rw_t<io_, bitpos::B8>  CMADDMT67ZE;
			bit_rw_t<io_, bitpos::B9>  IC1ADDMT67ZE;

			bit_rw_t<io_, bitpos::B11> IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B13> IC5ADDMT67ZE;
			bit_rw_t<io_, bitpos::B14> IC6ADDMT67ZE;
		};
		static poecr4_t<0x0008C4D0> POECR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 5（POECR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr5_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDMT0ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT0ZE;
		};
		static poecr5_t<0x0008C4D2> POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 7（POECR7）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr7_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU9AZE;
			bit_rw_t<io_, bitpos::B1>  MTU9BZE;
			bit_rw_t<io_, bitpos::B2>  MTU9CZE;
			bit_rw_t<io_, bitpos::B3>  MTU9DZE;
			bit_rw_t<io_, bitpos::B4>  MTU9A1ZE;
			bit_rw_t<io_, bitpos::B5>  MTU9B1ZE;
			bit_rw_t<io_, bitpos::B6>  MTU9C1ZE;
			bit_rw_t<io_, bitpos::B7>  MTU9D1ZE;
		};
		static poecr7_t<0x0008C4E2> POECR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 8（POECR8）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr8_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDMT9ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT9ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT9ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT9ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT9ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT9ZE;
		};
		static poecr8_t<0x0008C4E4> POECR8;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ検出フラグレジスタ（POECMPFR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpfr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  C0FLAG;
			bit_rw_t<io_, bitpos::B1>  C1FLAG;
			bit_rw_t<io_, bitpos::B2>  C2FLAG;
			bit_rw_t<io_, bitpos::B3>  C3FLAG;
		};
		static poecmpfr_t<0x0008C4E6> POECMPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求選択レジスタ（POECMPSEL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpsel_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
		};
		static poecmpsel_t<0x0008C4E8> POECMPSEL;

	};
	typedef poe3_t POE3;
}
