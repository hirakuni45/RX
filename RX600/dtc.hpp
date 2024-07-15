#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ　DTCa, DTCb 定義 @n
			・RX13T @n
			・RX140 @n
			・RX220 @n
			・RX231 @n
			・RX23T @n
			・RX24T/RX24U @n
			・RX26T @n
			・RX62N/RX621 @n
			・RX63N/RX631 @n
			・RX63T @n
			・RX64M/RX71M @n
			・RX65N/RX651 @n
			・RX66T/RX72T @n
			・RX660/RX671 @n
			・RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DTCa データトランスファコントローラ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct dtca_t {

		static constexpr auto PERIPHERAL = peripheral::DTC;	///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC コントロールレジスタ（DTCCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4> RRS;
		};
		static inline dtccr_t<0x0008'2400> DTCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC ベクタベースレジスタ（DTCVBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<0x0008'2404> DTCVBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC アドレスモードレジスタ（DTCADMOD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcadmod_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SHORT;
		};
		static inline dtcadmod_t<0x0008'2408> DTCADMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC モジュール起動レジスタ（DTCST）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcst_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DTCST;
		};
		static inline dtcst_t<0x0008'240C> DTCST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC ステータスレジスタ（DTCSTS）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcsts_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 8> VECN;

			bit_ro_t <in_, bitpos::B15>   ACT;
		};
		static inline dtcsts_t<0x0008'240E> DTCSTS;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DTCb データトランスファコントローラ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct dtcb_t : public dtca_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  DTC インデックステーブルベースレジスタ (DTCIBR)
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'2410> DTCIBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC オペレーションレジスタ (DTCOR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcor_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SQTFRL;
		};
		static inline dtcor_t<0x0008'2414> DTCOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC シーケンス転送許可レジスタ (DTCSQE)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dtcsqe_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  VECN;

			bit_rw_t <io_, bitpos::B0>     ESPSEL;
		};
		static inline dtcsqe_t<0x0008'2416> DTCSQE;


		//-----------------------------------------------------------------//
		/*!
			@brief  DTC アドレスディスプレースメントレジスタ (DTCDISP)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x0008'2418> DTCDISP;
	};

#if defined(SIG_RX140) || defined(SIG_RX660) || defined(SIG_RX671)
	typedef dtcb_t DTC;
#else
	typedef dtca_t DTC;
#endif
}
