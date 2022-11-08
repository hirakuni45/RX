#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・デジタル電源制御演算器（DPC）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  デジタル電源制御演算器共通クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct dpc_t {

		static constexpr auto RBI4 = ICU::VECTOR::RBI4;	///< 制御チャネル４割り込み

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  基準値参照設定レジスタ（REFSEL）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct refsel_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>      RSEL;
		};
		typedef refsel_t<0x000C'3020> REFSEL_;
		static REFSEL_ REFSEL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御チャネル設定レジスタ（CHLSEL）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct chlsel_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CSEL;
		};
		typedef chlsel_t<0x000C'3024> CHLSEL_;
		static CHLSEL_ CHLSEL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御イネーブル設定レジスタ（ENABLE）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct enable_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>      EN0;
			bit_rw_t<io_, bitpos::B1>      EN1;
			bit_rw_t<io_, bitpos::B2>      EN2;
			bit_rw_t<io_, bitpos::B3>      EN3;
		};
		typedef enable_t<0x000C'3028> ENABLE_;
		static ENABLE_ ENABLE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入力コードモニタイネーブル設定レジスタ（TMONEN）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmonen_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>      TMEN;
		};
		typedef tmonen_t<0x000C'307C> TMONEN_;
		static TMONEN_ TMONEN;



	};
	template<class _> typename dpc_t<_>::REFSEL_ dpc_t<_>::REFSEL;
	template<class _> typename dpc_t<_>::CHLSEL_ dpc_t<_>::CHLSEL;
	template<class _> typename dpc_t<_>::ENABLE_ dpc_t<_>::ENABLE;
	template<class _> typename dpc_t<_>::TMONEN_ dpc_t<_>::TMONEN;

	typedef dpc_t<void> DPC;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  デジタル電源制御演算器（DPC）クラス
		@param[in]	ofs		オフセットアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rbi		割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi>
	struct dpcn_t : public DPC {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto RBI		 = rbi;		///< 制御チャネル割り込み


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトスタート設定レジスタ（SOFTSTARTn）（n = 0 ～ 3）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct softstart_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SSTM;
			bit_rw_t <io_, bitpos::B8>     SSEN;
		};
		typedef softstart_t<0x000C'3000 + ofs> SOFTSTART_;
		static SOFTSTART_ SOFTSTART;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  基準値設定レジスタ（VOTARGETn）（n=0 ～ 3）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct votarget_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  TGVO;
		};
		typedef votarget_t<0x000C'3010 + ofs> VOTARGET_;
		static VOTARGET_ VOTARGET;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御演算パラメータ Km 設定レジスタ（PARAMKmn）（m=P,I,Q,F、n=0 ～ 3）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x000C'302C + (ofs * 4)> PARAMKP_;
		static PARAMKP_ PARAMKP;
		typedef rw16_t<0x000C'3030 + (ofs * 4)> PARAMKI_;
		static PARAMKI_ PARAMKI;
		typedef rw16_t<0x000C'3034 + (ofs * 4)> PARAMKQ_;
		static PARAMKQ_ PARAMKQ;
		typedef rw16_t<0x000C'3038 + (ofs * 4)> PARAMKF_;
		static PARAMKF_ PARAMKF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御演算結果上位 / 下位ビット格納レジスタ（RESULTmn）（m=U、L）（n=0 ～ 3）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x000C'306C + ofs> RESULTU_;
		static RESULTU_ RESULTU;
		typedef rw16_t<0x000C'306E + ofs> RESULTL_;
		static RESULTL_ RESULTL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  最大入力コードモニタレジスタ（TMONMAXn）（n=0 ～ 3）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmonmax_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  VMAX;
		};
		typedef tmonmax_t<0x000C'3080 + (ofs * 2)> TMONMAX_;
		static TMONMAX_ TMONMAX;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  最小入力コードモニタレジスタ（TMONMINn）（n=0 ～ 3）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmonmin_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  VMIN;
		};
		typedef tmonmin_t<0x000C'3084 + (ofs * 2)> TMONMIN_;
		static TMONMIN_ TMONMIN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力過電圧異常判定閾値設定レジスタ（ERRVTHn）（n=0 ～ 3）
			@param[in]	base	ベース
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct errvth_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  ERVH;
		};
		typedef errvth_t<0x000C'30A0 + ofs> ERRVTH_;
		static ERRVTH_ ERRVTH;
	};
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::SOFTSTART_ dpcn_t<ofs, per, rbi>::SOFTSTART;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::VOTARGET_ dpcn_t<ofs, per, rbi>::VOTARGET;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::PARAMKP_ dpcn_t<ofs, per, rbi>::PARAMKP;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::PARAMKI_ dpcn_t<ofs, per, rbi>::PARAMKI;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::PARAMKQ_ dpcn_t<ofs, per, rbi>::PARAMKQ;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::PARAMKF_ dpcn_t<ofs, per, rbi>::PARAMKF;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::RESULTU_ dpcn_t<ofs, per, rbi>::RESULTU;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::RESULTL_ dpcn_t<ofs, per, rbi>::RESULTL;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::TMONMAX_ dpcn_t<ofs, per, rbi>::TMONMAX;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::TMONMIN_ dpcn_t<ofs, per, rbi>::TMONMIN;
	template <uint32_t ofs, peripheral per, ICU::VECTOR rbi> typename dpcn_t<ofs, per, rbi>::ERRVTH_ dpcn_t<ofs, per, rbi>::ERRVTH;

	typedef dpcn_t<0x0, peripheral::DPC0, ICU::VECTOR::RBI0> DPC0;
	typedef dpcn_t<0x4, peripheral::DPC1, ICU::VECTOR::RBI1> DPC1;
	typedef dpcn_t<0x8, peripheral::DPC2, ICU::VECTOR::RBI2> DPC2;
	typedef dpcn_t<0xC, peripheral::DPC3, ICU::VECTOR::RBI3> DPC3;
}
