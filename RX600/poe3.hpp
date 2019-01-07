#pragma once
//=====================================================================//
/*!	@file
	@brief	ポートアウトプットイネーブル 3（POE3）定義 @n
			・RX64M, RX71M, RX65N, RX651, RX66T, RX24T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 クラス
		@param[in]	org		POE3 モジュール先頭アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t org, peripheral per>
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

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE0M;
			bits_rw_t<io_, bitpos::B4, 4>  POE0M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE0M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE1;
			bit_rw_t <io_, bitpos::B12>    POE0F;
		};
		static icsr1_t<org + 0x00> ICSR1;


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

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE4M;
			bits_rw_t<io_, bitpos::B4, 4>  POE4M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE4M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE2;
			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		static icsr2_t<org + 0x04> ICSR2;


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

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE8M;
			bits_rw_t<io_, bitpos::B4, 4>  POE8M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE8M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE3;
			bit_rw_t <io_, bitpos::B9>     POE8E;
			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		static icsr3_t<org + 0x08> ICSR3;


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

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE10M;
			bits_rw_t<io_, bitpos::B4, 4>  POE10M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE10M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B9>     POE10E;
			bit_rw_t <io_, bitpos::B12>    POE10F;
		};
		static icsr4_t<org + 0x16> ICSR4;


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

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE11M;
			bits_rw_t<io_, bitpos::B4, 4>  POE11M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE11M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;
			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		static icsr5_t<org + 0x18> ICSR5;


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
		static icsr6_t<org + 0x1C> ICSR6;

#if defined(SIG_RX24T) || defined(SIG_RX66T)
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

#if defined(SIG_RX24T)
			bits_rw_t<io_, bitpos::B0, 2>  POE12M;
#elif defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE12M;
			bits_rw_t<io_, bitpos::B4, 4>  POE12M2;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE7;
			bit_rw_t <io_, bitpos::B9>     POE12E;
			bit_rw_t <io_, bitpos::B12>    POE12F;
		};
		static icsr7_t<org + 0x20> ICSR7;
#endif

#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 8（ICSR8）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr8_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  POE9M;
			bits_rw_t<io_, bitpos::B4, 4>  POE9M2;
			bit_rw_t <io_, bitpos::B8>     PIE8;
			bit_rw_t <io_, bitpos::B9>     POE9E;
			bit_rw_t <io_, bitpos::B12>    POE9F;
		};
		static icsr8_t<org + 0x40> ICSR8;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 9（ICSR9）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr9_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  POE13M;
			bits_rw_t<io_, bitpos::B4, 4>  POE13M2;
			bit_rw_t <io_, bitpos::B8>     PIE9;
			bit_rw_t <io_, bitpos::B9>     POE13E;
			bit_rw_t <io_, bitpos::B12>    POE13F;
		};
		static icsr9_t<org + 0x42> ICSR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 10（ICSR10）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr10_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  POE14M;
			bits_rw_t<io_, bitpos::B4, 4>  POE14M2;
			bit_rw_t <io_, bitpos::B8>     PIE10;
			bit_rw_t <io_, bitpos::B9>     POE14E;
			bit_rw_t <io_, bitpos::B12>    POE14F;
		};
		static icsr10_t<org + 0x44> ICSR10;
#endif


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

			bit_rw_t<io_, bitpos::B8>   OIE1;
			bit_rw_t<io_, bitpos::B9>   OCE1;
			bit_rw_t<io_, bitpos::B15>  OSF1;
		};
		static ocsr1_t<org + 0x02> OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 2（OCSR2）
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

			bit_rw_t<io_, bitpos::B8>   OIE2;
			bit_rw_t<io_, bitpos::B9>   OCE2;
			bit_rw_t<io_, bitpos::B15>  OSF2;
		};
		static ocsr2_t<org + 0x06> OCSR2;


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 3（OCSR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE3;
			bit_rw_t<io_, bitpos::B9>   OCE3;
			bit_rw_t<io_, bitpos::B15>  OSF3;
		};
		static ocsr3_t<org + 0x2A> OCSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 4（OCSR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr4_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE4;
			bit_rw_t<io_, bitpos::B9>   OCE4;
			bit_rw_t<io_, bitpos::B15>  OSF4;
		};
		static ocsr4_t<org + 0x46> OCSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 5（OCSR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr5_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE5;
			bit_rw_t<io_, bitpos::B9>   OCE5;
			bit_rw_t<io_, bitpos::B15>  OSF5;
		};
		static ocsr5_t<org + 0x48> OCSR5;
#endif


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
		static alr1_t<org + 0x1A> ALR1;


#if defined(SIG_RX24T) || defined(SIG_RX66T)
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
		static alr2_t<org + 0x1E> ALR2;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 3（ALR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr3_t : public rw16_t<base> {
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
		static alr3_t<org + 0x2C> ALR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 4（ALR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr4_t : public rw16_t<base> {
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
		static alr4_t<org + 0x4A> ALR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 5（ALR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr5_t : public rw16_t<base> {
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
		static alr5_t<org + 0x4C> ALR5;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ（SPOER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
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
			bit_rw_t<io_, bitpos::B3>  GPT01HIZ;
			bit_rw_t<io_, bitpos::B4>  GPT23HIZ;
		};
		static spoer_t<org + 0x0A> SPOER;
#elif defined(SIG_RX24T)
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

			bit_rw_t<io_, bitpos::B4>  GPT03HIZ;

			bit_rw_t<io_, bitpos::B6>  MTUCH9HIZ;
		};
		static spoer_t<org + 0x0A> SPOER;
#elif defined(SIG_RX66T)
		template <uint32_t base>
		struct spoer_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTUCH34HIZ;
			bit_rw_t<io_, bitpos::B1>  MTUCH67HIZ;
			bit_rw_t<io_, bitpos::B2>  MTUCH0HIZ;
			bit_rw_t<io_, bitpos::B3>  GPT01HIZ;
			bit_rw_t<io_, bitpos::B4>  GPT03HIZ;

			bit_rw_t<io_, bitpos::B6>  MTUCH9HIZ;

			bit_rw_t<io_, bitpos::B8>  GPT02HIZ;
			bit_rw_t<io_, bitpos::B9>  GPT46HIZ;
			bit_rw_t<io_, bitpos::B10> GPT79HIZ;
		};
		static spoer_t<org + 0x2E> SPOER;
#endif


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
#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B4>  MTU0A1ZE;
			bit_rw_t<io_, bitpos::B5>  MTU0B1ZE;
#endif
		};
		static poecr1_t<org + 0x0B> POECR1;


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
		static poecr2_t<org + 0x0C> POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 3（POECR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B8>   GPT0A1ZE;
			bit_rw_t<io_, bitpos::B9>   GPT0B1ZE;
			bit_rw_t<io_, bitpos::B10>  GPT1A1ZE;
			bit_rw_t<io_, bitpos::B11>  GPT1B1ZE;
			bit_rw_t<io_, bitpos::B12>  GPT2A1ZE;
			bit_rw_t<io_, bitpos::B13>  GPT2B1ZE;
			bit_rw_t<io_, bitpos::B14>  GPT3A1ZE;
			bit_rw_t<io_, bitpos::B15>  GPT3B1ZE;
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_rw_t<io_, bitpos::B0>   GPT0ABZE;
			bit_rw_t<io_, bitpos::B1>   GPT1ABZE;
			bit_rw_t<io_, bitpos::B8>   GPT2ABZE;
			bit_rw_t<io_, bitpos::B9>   GPT3ABZE;
#elif defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B0>   GPT0ABZE;
			bit_rw_t<io_, bitpos::B1>   GPT1ABZE;
			bit_rw_t<io_, bitpos::B2>   GPT2ABZE;
			bit_rw_t<io_, bitpos::B3>   GPT3ABZE;
			bit_rw_t<io_, bitpos::B4>   GPT4ABZE;
			bit_rw_t<io_, bitpos::B5>   GPT5ABZE;
			bit_rw_t<io_, bitpos::B6>   GPT6ABZE;
			bit_rw_t<io_, bitpos::B7>   GPT7ABZE;
			bit_rw_t<io_, bitpos::B8>   GPT8ABZE;
			bit_rw_t<io_, bitpos::B9>   GPT9ABZE;
#endif
		};
		static poecr3_t<org + 0x0E> POECR3;


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

#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B0>  CMADDMT34ZE;

			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT34ZE;

			bit_rw_t<io_, bitpos::B8>  CMADDMT67ZE;
			bit_rw_t<io_, bitpos::B9>  IC1ADDMT67ZE;

			bit_rw_t<io_, bitpos::B11> IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B13> IC5ADDMT67ZE;
			bit_rw_t<io_, bitpos::B14> IC6ADDMT67ZE;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;

			bit_rw_t<io_, bitpos::B9>  IC1ADDMT67ZE;

			bit_rw_t<io_, bitpos::B3>  IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT67ZE;
#elif defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B0>  CMADDMT34ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT34ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT34ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT34ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT34ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT34ZE;
#endif
		};
		static poecr4_t<org + 0x10> POECR4;


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4B（POECR4B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr4b_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDMT67ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT67ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT67ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT67ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT67ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT67ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT67ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT67ZE;
		};
		static poecr4b_t<org + 0x4E> POECR4B;
#endif


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

#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B0>  CMADDMT0ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT0ZE;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
#elif defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B0>  CMADDMT0ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT0ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT0ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT0ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT0ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT0ZE;
#endif 
		};
		static poecr5_t<org + 0x12> POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6（POECR6）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr6_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B8>  CMADDGPT03ZE;
			bit_rw_t<io_, bitpos::B9>  IC1ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B10> IC2ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B11> IC3ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDGPT03ZE;

			bit_rw_t<io_, bitpos::B14> IC6ADDGPT03ZE;
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B9>  IC1ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B10> IC2ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B11> IC3ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDGPT23ZE;
#elif defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B0>  CMADDGPT01ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT01ZE;
#endif 
		};
#if defined(SIG_RX24T) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T)
		static poecr6_t<org + 0x14> POECR6;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6B（POECR6B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr6B_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDGPT23ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT23ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT23ZE;
		};
		static poecr6B_t<org + 0x50> POECR6B;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
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
#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B4>  MTU9A1ZE;
			bit_rw_t<io_, bitpos::B5>  MTU9B1ZE;
			bit_rw_t<io_, bitpos::B6>  MTU9C1ZE;
			bit_rw_t<io_, bitpos::B7>  MTU9D1ZE;
#endif
		};
		static poecr7_t<org + 0x22> POECR7;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
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
#if defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT9ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT9ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT9ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT9ZE;
#endif
		};
		static poecr8_t<org + 0x24> POECR8;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 9（POECR9）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr9_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDGPT02ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT02ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT02ZE;
		};
		static poecr9_t<org + 0x52> POECR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 10（POECR10）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr10_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDGPT46ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT46ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT46ZE;
		};
		static poecr10_t<org + 0x54> POECR10;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 11（POECR11）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr11_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDGPT79ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT79ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT79ZE;
		};
		static poecr11_t<org + 0x56> POECR11;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 0 (PMMCR0)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AME;
			bit_rw_t<io_, bitpos::B1>  MTU0BME;
			bit_rw_t<io_, bitpos::B2>  MTU0CME;
			bit_rw_t<io_, bitpos::B3>  MTU0DME;
			bit_rw_t<io_, bitpos::B4>  MTU0A1ME;
			bit_rw_t<io_, bitpos::B5>  MTU0B1ME;
		};
		static pmmcr0_t<org + 0x30> PMMCR0;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 0 (PMMCR0)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AME;
			bit_rw_t<io_, bitpos::B1>  MTU0BME;
			bit_rw_t<io_, bitpos::B2>  MTU0CME;
			bit_rw_t<io_, bitpos::B3>  MTU0DME;

			bit_rw_t<io_, bitpos::B8>  MTU9AME;
			bit_rw_t<io_, bitpos::B9>  MTU9BME;
			bit_rw_t<io_, bitpos::B10> MTU9CME;
			bit_rw_t<io_, bitpos::B11> MTU9DME;
		};
		static pmmcr0_t<org + 0x30> PMMCR0;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 1 (PMMCR1)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU7BME;
			bit_rw_t<io_, bitpos::B1>  MTU7AME;
			bit_rw_t<io_, bitpos::B2>  MTU6BME;
			bit_rw_t<io_, bitpos::B3>  MTU7DME;
			bit_rw_t<io_, bitpos::B4>  MTU7CME;
			bit_rw_t<io_, bitpos::B5>  MTU6DME;

			bit_rw_t<io_, bitpos::B8>  MTU4BME;
			bit_rw_t<io_, bitpos::B9>  MTU4AME;
			bit_rw_t<io_, bitpos::B10> MTU3BME;
			bit_rw_t<io_, bitpos::B11> MTU4DME;
			bit_rw_t<io_, bitpos::B12> MTU4CME;
			bit_rw_t<io_, bitpos::B13> MTU3DME;
		};
		static pmmcr1_t<org + 0x32> PMMCR1;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 2 (PMMCR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>  GPT0A1ME;
			bit_rw_t<io_, bitpos::B9>  GPT0B1ME;
			bit_rw_t<io_, bitpos::B10> GPT1A1ME;
			bit_rw_t<io_, bitpos::B11> GPT1B1ME;
			bit_rw_t<io_, bitpos::B12> GPT2A1ME;
			bit_rw_t<io_, bitpos::B13> GPT2B1ME;
			bit_rw_t<io_, bitpos::B14> GPT3A1ME;
			bit_rw_t<io_, bitpos::B15> GPT3B1ME;
		};
		static pmmcr2_t<org + 0x34> PMMCR2;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 2 (PMMCR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GPT0AME;
			bit_rw_t<io_, bitpos::B1>  GPT0BME;
			bit_rw_t<io_, bitpos::B2>  GPT1AME;
			bit_rw_t<io_, bitpos::B3>  GPT1BME;
			bit_rw_t<io_, bitpos::B4>  GPT2AME;
			bit_rw_t<io_, bitpos::B5>  GPT2BME;
			bit_rw_t<io_, bitpos::B6>  GPT3AME;
			bit_rw_t<io_, bitpos::B7>  GPT3BME;
			bit_rw_t<io_, bitpos::B8>  GPT4AME;
			bit_rw_t<io_, bitpos::B9>  GPT4BME;
			bit_rw_t<io_, bitpos::B10> GPT5AME;
			bit_rw_t<io_, bitpos::B11> GPT5BME;
			bit_rw_t<io_, bitpos::B12> GPT6AME;
			bit_rw_t<io_, bitpos::B13> GPT6BME;
			bit_rw_t<io_, bitpos::B14> GPT7AME;
			bit_rw_t<io_, bitpos::B15> GPT7BME;
		};
		static pmmcr2_t<org + 0x34> PMMCR2;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 3 (PMMCR3)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU9AME;
			bit_rw_t<io_, bitpos::B1>  MTU9BME;
			bit_rw_t<io_, bitpos::B2>  MTU9CME;
			bit_rw_t<io_, bitpos::B3>  MTU9DME;
			bit_rw_t<io_, bitpos::B4>  MTU9A1ME;
			bit_rw_t<io_, bitpos::B5>  MTU9B1ME;
			bit_rw_t<io_, bitpos::B6>  MTU9C1ME;
			bit_rw_t<io_, bitpos::B7>  MTU9D1ME;
		};
		static pmmcr3_t<org + 0x36> PMMCR3;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 3 (PMMCR3)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GPT8AME;
			bit_rw_t<io_, bitpos::B1>  GPT8BME;
			bit_rw_t<io_, bitpos::B2>  GPT9AME;
			bit_rw_t<io_, bitpos::B3>  GPT9BME;
		};
		static pmmcr3_t<org + 0x36> PMMCR3;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
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
#if defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B4>  C4FLAG;
			bit_rw_t<io_, bitpos::B5>  C5FLAG;
#endif
		};
		static poecmpfr_t<org + 0x26> POECMPFR;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
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
#if defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B4>  POEREQ4;
			bit_rw_t<io_, bitpos::B5>  POEREQ5;
#endif
		};
		static poecmpsel_t<org + 0x28> POECMPSEL;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求拡張選択レジスタ m @n
					(POECMPEXm) (m = 0 ～ 2, 4, 5)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpex_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
		};
		static poecmpex_t<org + 0x38> POECMPEX0;
		static poecmpex_t<org + 0x39> POECMPEX1;
		static poecmpex_t<org + 0x3A> POECMPEX2;
		static poecmpex_t<org + 0x3C> POECMPEX4;
		static poecmpex_t<org + 0x3D> POECMPEX5;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求拡張選択レジスタ m @n
					(POECMPEXm) (m = 0 ～ 2, 4, 5)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpex_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
			bit_rw_t<io_, bitpos::B4>  POEREQ4;
			bit_rw_t<io_, bitpos::B5>  POEREQ5;
		};
		static poecmpex_t<org + 0x38> POECMPEX0;
		static poecmpex_t<org + 0x39> POECMPEX1;
		static poecmpex_t<org + 0x3A> POECMPEX2;
		static poecmpex_t<org + 0x3B> POECMPEX3;
		static poecmpex_t<org + 0x3C> POECMPEX4;
		static poecmpex_t<org + 0x3D> POECMPEX5;
		static poecmpex_t<org + 0x58> POECMPEX6;
		static poecmpex_t<org + 0x59> POECMPEX7;
		static poecmpex_t<org + 0x5A> POECMPEX8;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M)
		//-----------------------------------------------------------------//
		/*!
			@brief	GPT0 端子選択レジスタ（G0SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g0selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G0BSEL;
		};
		static g0selr_t<org + 0x20> G0SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT1 端子選択レジスタ（G1SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g1selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G1ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G1BSEL;
		};
		static g1selr_t<org + 0x21> G1SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT2 端子選択レジスタ（G2SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g2selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G2ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G2BSEL;
		};
		static g2selr_t<org + 0x22> G2SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT3 端子選択レジスタ（G3SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g3selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G3ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G3BSEL;
		};
		static g3selr_t<org + 0x23> G3SELR;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ（M0SELR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m0selr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0BSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 2（M0SELR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m0selr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0CSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0DSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU3 端子選択レジスタ（M3SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m3selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M3BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M3DSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 1（M4SELR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m4selr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4CSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 2（M4SELR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m4selr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4DSEL;
		};
#endif

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		static m0selr1_t<org + 0x24> M0SELR1;
		static m0selr2_t<org + 0x25> M0SELR2;
		static m3selr_t<org + 0x26>  M3SELR;
		static m4selr1_t<org + 0x27> M4SELR1;
		static m4selr2_t<org + 0x28> M4SELR2;
#elif defined(SIG_RX66T)
		static m0selr1_t<org + 0x60> M0SELR1;
		static m0selr2_t<org + 0x61> M0SELR2;
		static m3selr_t<org + 0x62>  M3SELR;
		static m4selr1_t<org + 0x63> M4SELR1;
		static m4selr2_t<org + 0x64> M4SELR2;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M)
		//-----------------------------------------------------------------//
		/*!
			@brief	MTU/GPT 端子機能選択レジスタ（MGSELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mgselr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  M3G0SEL;
			bit_rw_t<io_, bitpos::B1>  M4G1SEL;
			bit_rw_t<io_, bitpos::B2>  M4G2SEL;
		};
		static mgselr_t<org + 0x29> MGSELR;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	MTU6 端子選択レジスタ (M6SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m6selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M6BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M6DSEL;
		};
		static m6selr_t<org + 0x65> M6SELR;



#endif





		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};
#if defined(SIG_RX24T) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	typedef poe3_t<0x0008C4C0, peripheral::POE> POE3;
#elif defined(SIG_RX66T)
	typedef poe3_t<0x0009E400, peripheral::POE> POE3;
#endif
}
