#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24T/RX24U ポートアウトプットイネーブル 3（POE3[bA]）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 クラス
		@param[in]	base	POE3 モジュール先頭アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct poe3_t {

		static constexpr auto PERIPHERAL = peripheral::POE3;	///< ペリフェラル型
		static constexpr auto OEI1 = ICU::VECTOR::OEI1;			///< アウトプットイネーブル割り込み1
		static constexpr auto OEI2 = ICU::VECTOR::OEI2;			///< アウトプットイネーブル割り込み2
		static constexpr auto OEI3 = ICU::VECTOR::OEI3;			///< アウトプットイネーブル割り込み3
		static constexpr auto OEI4 = ICU::VECTOR::OEI4;			///< アウトプットイネーブル割り込み4
		static constexpr auto OEI5 = ICU::VECTOR::OEI5;			///< アウトプットイネーブル割り込み5


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 1（ICSR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE0M;

			bit_rw_t <io_, bitpos::B8>     PIE1;
			bit_rw_t <io_, bitpos::B12>    POE0F;
		};
		static inline icsr1_t<base + 0x00> ICSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 2（ICSR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE4M;

			bit_rw_t <io_, bitpos::B8>     PIE2;

			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		static inline icsr2_t<base + 0x04> ICSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 3（ICSR3）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE8M;

			bit_rw_t <io_, bitpos::B8>     PIE3;
			bit_rw_t <io_, bitpos::B9>     POE8E;

			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		static inline icsr3_t<base + 0x08> ICSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 4（ICSR4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr4_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE10M;

			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B9>     POE10E;

			bit_rw_t <io_, bitpos::B12>    POE10F;
		};
		static inline icsr4_t<base + 0x16> ICSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 5（ICSR5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE11M;

			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;

			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		static inline icsr5_t<base + 0x18> ICSR5;
	

		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 6（ICSR6）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr6_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B9>     OSTSTE;

			bit_rw_t <io_, bitpos::B12>    OSTSTF;
		};
		static inline icsr6_t<base + 0x1C> ICSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 7（ICSR7）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr7_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE12M;

			bit_rw_t <io_, bitpos::B8>     PIE7;
			bit_rw_t <io_, bitpos::B9>     POE12E;

			bit_rw_t <io_, bitpos::B12>    POE12F;
		};
		static inline icsr7_t<base + 0x20> ICSR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 1（OCSR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE1;
			bit_rw_t<io_, bitpos::B9>   OCE1;

			bit_rw_t<io_, bitpos::B15>  OSF1;
		};
		static inline ocsr1_t<base + 0x02> OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 2（OCSR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE2;
			bit_rw_t<io_, bitpos::B9>   OCE2;

			bit_rw_t<io_, bitpos::B15>  OSF2;
		};
		static inline ocsr2_t<base + 0x06> OCSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 1（ALR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline alr1_t<base + 0x1A> ALR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 2（ALR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline alr2_t<base + 0x1E> ALR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ（SPOER）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spoer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline spoer_t<base + 0x0A> SPOER;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 1（POECR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline poecr1_t<base + 0x0B> POECR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 2（POECR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline poecr2_t<base + 0x0C> POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 3（POECR3）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   GPT0A1ZE;
			bit_rw_t<io_, bitpos::B9>   GPT0B1ZE;
			bit_rw_t<io_, bitpos::B10>  GPT1A1ZE;
			bit_rw_t<io_, bitpos::B11>  GPT1B1ZE;
			bit_rw_t<io_, bitpos::B12>  GPT2A1ZE;
			bit_rw_t<io_, bitpos::B13>  GPT2B1ZE;
			bit_rw_t<io_, bitpos::B14>  GPT3A1ZE;
			bit_rw_t<io_, bitpos::B15>  GPT3B1ZE;
		};
		static inline poecr3_t<base + 0x0E> POECR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4（POECR4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr4_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

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
		};
		static inline poecr4_t<base + 0x10> POECR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 5（POECR5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline poecr5_t<base + 0x12> POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6（POECR6）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr6_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>  CMADDGPT03ZE;
			bit_rw_t<io_, bitpos::B9>  IC1ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B10> IC2ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B11> IC3ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDGPT03ZE;

			bit_rw_t<io_, bitpos::B14> IC6ADDGPT03ZE;
		};
		static inline poecr6_t<base + 0x14> POECR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 7（POECR7）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr7_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline poecr7_t<base + 0x22> POECR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 8（POECR8）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr8_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDGPT9ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT9ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT9ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT9ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT9ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT9ZE;
		};
		static inline poecr8_t<base + 0x24> POECR8;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 0 (PMMCR0)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline pmmcr0_t<base + 0x30> PMMCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 1 (PMMCR1)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline pmmcr1_t<base + 0x32> PMMCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 2 (PMMCR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline pmmcr2_t<base + 0x34> PMMCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 3 (PMMCR3)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		static inline pmmcr3_t<base + 0x36> PMMCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ出力検出フラグレジスタ (POECMPFR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecmpfr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  C0FLAG;
			bit_rw_t<io_, bitpos::B1>  C1FLAG;
			bit_rw_t<io_, bitpos::B2>  C2FLAG;
			bit_rw_t<io_, bitpos::B3>  C3FLAG;
		};
		static inline poecmpfr_t<base + 0x26> POECMPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求選択レジスタ (POECMPSEL)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecmpsel_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
		};
		static inline poecmpsel_t<base + 0x28> POECMPSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求拡張選択レジスタ m (POECMPEXm) (m = 0 ～ 2, 4, 5)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecmpexm_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
		};
		static inline poecmpexm_t<base + 0x38> POECMPEX0;
		static inline poecmpexm_t<base + 0x39> POECMPEX1;
		static inline poecmpexm_t<base + 0x3A> POECMPEX2;
		static inline poecmpexm_t<base + 0x3C> POECMPEX4;
		static inline poecmpexm_t<base + 0x3D> POECMPEX5;
	};
	typedef poe3_t<0x0008'C4C0> POE3;
}
