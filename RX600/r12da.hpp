#pragma once
//=========================================================================//
/*!	@file
	@brief	R12DA 定義 @n
			RX231/RX64M/RX71M/RX65x/RX72N/RX72M @n
			RX26T/RX66T/RX72T
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
		@brief	12 ビット D/A コンバータ（R12DA）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct r12da_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 0（DADR0）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8040> DADR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 1（DADR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8042> DADR1;


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

			bits_rw_t<io_, bitpos::B0, 5> RESERVE;
			bit_rw_t <io_, bitpos::B5>    DAE;
			bit_rw_t <io_, bitpos::B6>    DAOE0;
			bit_rw_t <io_, bitpos::B7>    DAOE1;
		};
		static inline dacr_t<0x0008'8044> DACR;


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
		static inline dadpr_t<0x0008'8045> DADPR;


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
		static inline daadscr_t<0x0008'8046> DAADSCR;
	};


#if defined(SIG_RX64M) || defined(SIG_RX65N) || defined(SIG_RX71M) || defined(SIG_RX72N) || defined(SIG_RX72M) 
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	12 ビット D/A コンバータ（R12DA）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct r12da_a_t : public r12da_t<per> {

		typedef r12da_t<per> base_type;

		static constexpr bool DACR_DAE = true;	///< DAE フラグの有無

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ出力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
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
		static inline daampcr_t<0x0008'8048> DAAMPCR;


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
		static inline daadusr_t<0x0008'C5C0> DAADUSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true)
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			switch(an) {
			case ANALOG::DA0:
				PORT0::PCR.B3 = 0;
				PORT0::PMR.B3 = 0;
				MPC::P03PFS.ASEL = f;
				break;
			case ANALOG::DA1:
				PORT0::PCR.B5 = 0;
				PORT0::PMR.B5 = 0;
				MPC::P05PFS.ASEL = f;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
	typedef r12da_a_t<peripheral::R12DA> R12DA;

#elif defined(SIG_RX231)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	12 ビット D/A コンバータ（R12DAA）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct r12da_A_t : public r12da_t<per> {

		typedef r12da_t<per> base_type;

		static constexpr bool DACR_DAE = false;	///< DAE フラグの有無

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ出力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			DA0,
			DA1,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A VREF 制御レジスタ（DAVREFCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct davrefcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> REF;
		};
		static inline davrefcr_t<0x0008'8047> DAVREFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true)
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			switch(an) {
			case ANALOG::DA0:
				PORT0::PCR.B3 = 0;
				PORT0::PDR.B3 = 0;
				PORT0::PMR.B3 = 0;
				MPC::P03PFS.ASEL = f;
				break;
			case ANALOG::DA1:
				PORT0::PCR.B5 = 0;
				PORT0::PDR.B5 = 0;
				PORT0::PMR.B5 = 0;
				MPC::P05PFS.ASEL = f;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
	typedef r12da_A_t<peripheral::R12DA> R12DA;

#elif defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	12 ビット D/A コンバータ（R12DAb）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct r12da_b_t : public r12da_t<per> {

		typedef r12da_t<per> base_type;

		static constexpr bool DACR_DAE = true;	///< DAE フラグの有無

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ出力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
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
		static inline dadselr_t<0x0008'8049> DADSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true)
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
			switch(an) {
			case ANALOG::DA0:
				PORT6::PCR.B4 = 0;
				PORT6::PMR.B4 = 0;
				MPC::P64PFS.ASEL = f;
				break;
			case ANALOG::DA1:
				PORT6::PCR.B5 = 0;
				PORT6::PMR.B5 = 0;
				MPC::P65PFS.ASEL = f;
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
