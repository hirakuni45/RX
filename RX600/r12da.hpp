#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65x/RX66T グループ・R12DA 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

/// R12DA モジュールが無いデバイスでエラーとする
#if defined(SIG_RX24T)
#  error "r12da.hpp: This module does not exist"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	12 ビット D/A コンバータ（R12DA）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct r12da_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 0（DADR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x00088040> DADR0_;
		static DADR0_ DADR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 1（DADR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x00088042> DADR1_;
		static DADR1_ DADR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A 制御レジスタ（DACR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dacr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B5> DAE;
			bit_rw_t<io_, bitpos::B6> DAOE0;
			bit_rw_t<io_, bitpos::B7> DAOE1;
		};
		typedef dacr_t<0x00088044> DACR_;
		static DACR_ DACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DADR0 フォーマット選択レジスタ（DADPR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dadpr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7> DPSEL;
		};
		typedef dadpr_t<0x00088045> DADPR_;
		static DADPR_ DADPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A A/D 同期スタート制御レジスタ（DAADSCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct daadscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7> DAADST;
		};
		typedef daadscr_t<0x00088046> DAADSCR_;
		static DAADSCR_ DAADSCR;
	};
	template <peripheral per> typename r12da_t<per>::DADR0_ r12da_t<per>::DADR0;
	template <peripheral per> typename r12da_t<per>::DADR1_ r12da_t<per>::DADR1;
	template <peripheral per> typename r12da_t<per>::DACR_ r12da_t<per>::DACR;
	template <peripheral per> typename r12da_t<per>::DADPR_ r12da_t<per>::DADPR;
	template <peripheral per> typename r12da_t<per>::DAADSCR_ r12da_t<per>::DAADSCR;


#if defined(SIG_RX64M) || defined(SIG_RX65N) || defined(SIG_RX71M) || defined(SIG_RX72T) || defined(SIG_RX72M) || defined(SIG_RX72N) 
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	12 ビット D/A コンバータ（R12DA）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct r12da_a_t : public r12da_t<per> {

		typedef r12da_t<per> base_type;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入出力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class analog : uint8_t {
			DA0,
			DA1,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A 出力アンプ制御レジスタ（DAAMPCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct daampcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> DAAMP0;
			bit_rw_t<io_, bitpos::B7> DAAMP1;
		};
		typedef daampcr_t<0x00088048> DAAMPCR_;
		static DAAMPCR_ DAAMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A A/D 同期ユニット選択レジスタ（DAADUSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct daadusr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1> AMADSEL1;
		};
		typedef daadusr_t<0x0008C5C0> DAADUSR_;
		static DAADUSR_ DAADUSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(analog an, bool f = true)
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			switch(an) {
			case analog::DA0:
				MPC::P03PFS.ASEL = f;
				PORT0::PMR.B3 = 1;
				break;
			case analog::DA1:
				MPC::P05PFS.ASEL = f;
				PORT0::PMR.B5 = 1;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
	typedef r12da_a_t<peripheral::R12DA> R12DA;

	template <peripheral per> typename r12da_a_t<per>::DAAMPCR_ r12da_a_t<per>::DAAMPCR;
	template <peripheral per> typename r12da_a_t<per>::DAADUSR_ r12da_a_t<per>::DAADUSR;


#elif defined(SIG_RX66T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	12 ビット D/A コンバータ（R12DA）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct r12da_b_t : public r12da_t<per> {

		typedef r12da_t<per> base_type;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入出力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class analog : uint8_t {
			DA0,
			DA1,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A 出力先選択レジスタ（ DADSELR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dadselr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  OUTDA0;
			bit_rw_t<io_, bitpos::B1>  OUTDA1;
			bit_rw_t<io_, bitpos::B2>  OUTREF0;
			bit_rw_t<io_, bitpos::B3>  OUTREF1;
		};
		static dadselr_t<0x00088049> DADSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(analog an, bool f = true)
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			switch(an) {
			case analog::DA0:
				MPC::P64PFS.ASEL = 1;
				PORT6::PMR.B4 = 1;
				break;
			case analog::DA1:
				MPC::P65PFS.ASEL = 1;
				PORT6::PMR.B5 = 1;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
	typedef r12da_b_t<peripheral::R12DA> R12DA;
#endif
}
