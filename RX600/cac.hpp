#pragma once
//=========================================================================//
/*!	@file
	@brief	CAC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  クロック周波数精度測定回路（CAC）クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込みベクタ型
		@param[in]	ferr	周波数エラー割り込みベクタ
		@param[in]	mend	測定終了割り込みベクタ
		@param[in]	ovff	オーバフロー割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<peripheral per, typename INT, INT ferr, INT mend, INT ovff>
	struct cac_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto FERR_VEC = ferr;		///< 周波数エラー割り込みベクター
		static constexpr auto MEND_VEC = mend;		///< 測定終了割り込みベクター
		static constexpr auto OVFF_VEC = ovff;		///< オーバーフロー割り込みベクター


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC コントロールレジスタ 0（CACR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cacr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CFME;
		};
		static inline cacr0_t<0x0008'B000> CACR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC コントロールレジスタ 1（CACR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cacr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CACREFE;
			bits_rw_t<io_, bitpos::B1, 3>  FMCS;
			bits_rw_t<io_, bitpos::B4, 2>  TCSS;
			bits_rw_t<io_, bitpos::B6, 2>  EDGES;
		};
		static inline cacr1_t<0x0008'B001> CACR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC コントロールレジスタ 2（CACR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cacr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     RPS;
			bits_rw_t<io_, bitpos::B1, 3>  RSCS;
			bits_rw_t<io_, bitpos::B4, 2>  RCDS;
			bits_rw_t<io_, bitpos::B6, 2>  DFS;
		};
		static inline cacr2_t<0x0008'B002> CACR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC 割り込み要求許可レジスタ（CAICR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct caicr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   FERRIE;
			bit_rw_t<io_, bitpos::B1>   MENDIE;
			bit_rw_t<io_, bitpos::B2>   OVFIE;

			bit_rw_t<io_, bitpos::B4>   FERRFCL;
			bit_rw_t<io_, bitpos::B5>   MENDFCL;
			bit_rw_t<io_, bitpos::B6>   OVFFCL;
		};
		static inline caicr_t<0x0008'B003> CAICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC ステータスレジスタ（CASTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct castr_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>   FERRF;
			bit_ro_t<io_, bitpos::B1>   MENDF;
			bit_ro_t<io_, bitpos::B2>   OVFF;
		};
		static inline castr_t<0x0008'B004> CASTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC 上限値設定レジスタ（CAULVR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'B006>  CAULVR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC 下限値設定レジスタ（CALLVR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'B008>  CALLVR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CAC カウンタバッファレジスタ（CACNTBR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'B00A>  CACNTBR;
	};

#if defined(SIG_RX140) || defined(SIG_RX220) || defined(SIG_RX231) || defined(SIG_RX24T)
	typedef cac_t<peripheral::CAC,
		ICU::VECTOR, ICU::VECTOR::FERRF, ICU::VECTOR::MENDF, ICU::VECTOR::OVFF> CAC;
#elif defined(SIG_RX26T) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef cac_t<peripheral::CAC,
		ICU::GROUPBL0, ICU::GROUPBL0::FERRI, ICU::GROUPBL0::MENDI, ICU::GROUPBL0::OVFI> CAC;
#endif
}
