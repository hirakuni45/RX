#pragma once
//=====================================================================//
/*!	@file
	@brief	RX220 S12ADb 定義 @n
			  16 channel A/D input 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADb ベース定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロールレジスタ（ADCSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  DBLANS;

			bit_rw_t <io_, bitpos::B6>     GBADIE;
			bit_rw_t <io_, bitpos::B7>     DBLE;
			bit_rw_t <io_, bitpos::B8>     EXTRG;
			bit_rw_t <io_, bitpos::B9>     TRGE;

			bit_rw_t <io_, bitpos::B12>    ADIE;
			bits_rw_t<io_, bitpos::B13, 2> ADCS;
			bit_rw_t <io_, bitpos::B15>    ADST;
		};
		typedef adcsr_t<base + 0x00>  ADCSR_;
		static  ADCSR_ ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均回数選択レジスタ（ADADC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adadc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  ADC;
		};
		typedef adadc_t<base + 0x0C>  ADADC_;
		static  ADADC_ ADADC;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロール拡張レジスタ（ADCER）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcer_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B5>     ACE;

			bits_rw_t<io_, bitpos::B8, 2>  DIAGAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;

			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		typedef adcer_t<base + 0x0E>  ADCER_;
		static  ADCER_ ADCER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始トリガ選択レジスタ（ADSTRGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adstrgr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  TRSB;

			bits_rw_t<io_, bitpos::B8, 4>  TRSA;
		};
		typedef adstrgr_t<base + 0x10>  ADSTRGR_;
		static  ADSTRGR_ ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換拡張入力コントロールレジスタ（ADEXICR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adexicr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>      OCSAD;

			bit_rw_t<io_, bitpos::B9>      OCS;
		};
		typedef adexicr_t<base + 0x12>  ADEXICR_;
		static  ADEXICR_ ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 断線検出コントロールレジスタ（ADDISCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiscr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ADNDIS;
		};
		typedef addiscr_t<base + 0x7A>  ADDISCR_;
		static  ADDISCR_ ADDISCR;
	};
	template <uint32_t base> typename s12ad_base_t<base>::ADCSR_ s12ad_base_t<base>::ADCSR;
	template <uint32_t base> typename s12ad_base_t<base>::ADADC_ s12ad_base_t<base>::ADADC;
	template <uint32_t base> typename s12ad_base_t<base>::ADCER_ s12ad_base_t<base>::ADCER;
	template <uint32_t base> typename s12ad_base_t<base>::ADSTRGR_ s12ad_base_t<base>::ADSTRGR;
	template <uint32_t base> typename s12ad_base_t<base>::ADEXICR_ s12ad_base_t<base>::ADEXICR;
	template <uint32_t base> typename s12ad_base_t<base>::ADDISCR_ s12ad_base_t<base>::ADDISCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADb 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12ad_t : public s12ad_base_t<base> {

		static constexpr auto PERIPHERAL = per;  				///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI0;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI  = ICU::VECTOR::GBADI;		///< 割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 16;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,	///< AN000 入力
			AN001,
			AN002,
			AN003,
			AN004,
			AN005,
			AN006,
			AN007,
			AN008,
			AN009,
			AN010,
			AN011,
			AN012,
			AN013,
			AN014,
			AN015,
			REF,	///< 内部基準電圧
		};

	
		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true)
		{
			switch(an) {
			case ANALOG::AN000:
				PORT4::PDR.B0 = 0;
				MPC::P40PFS.ASEL = f;
				break;
			case ANALOG::AN001:
				PORT4::PDR.B1 = 0;
				MPC::P41PFS.ASEL = f;
				break;
			case ANALOG::AN002:
				PORT4::PDR.B2 = 0;
				MPC::P42PFS.ASEL = f;
				break;
			case ANALOG::AN003:
				PORT4::PDR.B3 = 0;
				MPC::P43PFS.ASEL = f;
				break;
			case ANALOG::AN004:
				PORT4::PDR.B4 = 0;
				MPC::P44PFS.ASEL = f;
				break;
			case ANALOG::AN005:
				PORT4::PDR.B5 = 0;
				MPC::P45PFS.ASEL = f;
				break;
			case ANALOG::AN006:
				PORT4::PDR.B6 = 0;
				MPC::P46PFS.ASEL = f;
				break;
			case ANALOG::AN007:
				PORT4::PDR.B7 = 0;
				MPC::P47PFS.ASEL = f;
				break;
			case ANALOG::AN008:
				PORTE::PDR.B0 = 0;
				MPC::PE0PFS.ASEL = f;
				break;
			case ANALOG::AN009:
				PORTE::PDR.B1 = 0;
				MPC::PE1PFS.ASEL = f;
				break;
			case ANALOG::AN010:
				PORTE::PDR.B2 = 0;
				MPC::PE2PFS.ASEL = f;
				break;
			case ANALOG::AN011:
				PORTE::PDR.B3 = 0;
				MPC::PE3PFS.ASEL = f;
				break;
			case ANALOG::AN012:
				PORTE::PDR.B4 = 0;
				MPC::PE4PFS.ASEL = f;
				break;
			case ANALOG::AN013:
				PORTE::PDR.B5 = 0;
				MPC::PE5PFS.ASEL = f;
				break;
			case ANALOG::AN014:
				PORTE::PDR.B6 = 0;
				MPC::PE6PFS.ASEL = f;
				break;
			case ANALOG::AN015:
				PORTE::PDR.B7 = 0;
				MPC::PE7PFS.ASEL = f;
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x18> ADDBLDR_;
		static ADDBLDR_ ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ（ADOCDR） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1C> ADOCDR_;
		static ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ（ADRD） @n
					右詰め、左詰めで有効ビット位置が異なる。
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1E> ADRD_;
		static ADRD_ ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）（AIN000 ～ AIN015）
		*/
		//-----------------------------------------------------------------//
		struct addr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (ANALOG an) noexcept {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ (ADANS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) noexcept {
				auto n = static_cast<uint32_t>(an);
				if(f) {
					wr16_(ofs, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			// チャネルビット取得
			bool operator() (ANALOG an) const noexcept {
				auto n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;
		typedef adans_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef adans_t<base + 0x08> ADADS_;
		static  ADADS_ ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 7、L、O）
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {

			uint32_t get_adr_offset(ANALOG an) const noexcept
			{
				uint32_t ofs;
				switch(an) {
				case ANALOG::AN000: ofs = 0x00; break;
				case ANALOG::AN001: ofs = 0x13; break;
				case ANALOG::AN002: ofs = 0x14; break;
				case ANALOG::AN003: ofs = 0x15; break;
				case ANALOG::AN004: ofs = 0x16; break;
				case ANALOG::AN005: ofs = 0x17; break;
				case ANALOG::AN006: ofs = 0x18; break;
				case ANALOG::AN007: ofs = 0x19; break;
				case ANALOG::REF:   ofs = 0x11; break;
				default:
					ofs = 0x01;
				}
				return ofs;
			}

			void set(ANALOG an, uint8_t val) noexcept
			{
				wr8_(base + 0x60 + get_adr_offset(an), val);
			}


			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (ANALOG an) const noexcept {
				return rd8_(base + 0x60 + get_adr_offset(an));
			}
		};
		typedef adsstr_t ADSSTR_;
		static  ADSSTR_ ADSSTR;
	};
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADDR_  s12ad_t<base, per>::ADDR;
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADANSA_ s12ad_t<base, per>::ADANSA;
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADANSB_ s12ad_t<base, per>::ADANSB;
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADADS_ s12ad_t<base, per>::ADADS;
	template <uint32_t base, peripheral per> typename s12ad_t<base, per>::ADSSTR_ s12ad_t<base, per>::ADSSTR;


	typedef s12ad_t<0x0008'9000, peripheral::S12AD>  S12AD;
}
