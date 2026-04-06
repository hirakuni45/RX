#pragma once
//=========================================================================//
/*!	@file
	@brief	RX21A 10 ビット A/D コンバータ（AD）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t base>
	struct ad_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ n（ADDRn）（n = 0 ～ 6）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x20> ADDR0_;
		static inline ADDR0_ ADDR0;
		static inline ro16_t<base + 0x22> ADDR1;
		static inline ro16_t<base + 0x24> ADDR2;
		static inline ro16_t<base + 0x26> ADDR3;
		static inline ro16_t<base + 0x28> ADDR4;
		static inline ro16_t<base + 0x2A> ADDR5;
		static inline ro16_t<base + 0x2C> ADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ（ADTSDR）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x1A> ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ（ADOCDR）
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<base + 0x1C> ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ（ADRD）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adrd_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 10>  AD;

			bits_ro_t<in_, bitpos::B14, 2>  DIAGST;
		};
		static inline adrd_t<base + 0x1E> ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロール／ステータスレジスタ（ADCSR）
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

			bit_rw_t<io_, bitpos::B8>     EXTRG;
			bit_rw_t<io_, bitpos::B9>     TRGE;

			bit_rw_t<io_, bitpos::B12>    ADIE;

			bit_rw_t<io_, bitpos::B14>    ADCS;
			bit_rw_t<io_, bitpos::B15>    ADST;
		};
		static inline adcsr_t<base + 0x00> ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x04> ADANSA_;
		static inline ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ（ADADS）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 7>  ADS;
		};
		static inline adads_t<base + 0x08> ADADS;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算回数選択レジスタ（ADADC）
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
		static inline adadc_t<base + 0x0C> ADADC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロール拡張レジスタ（ADCER）
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

			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;

			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		static inline adcer_t<base + 0x0E> ADCER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 開始トリガ選択レジスタ（ADSTRGR）
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

			bits_rw_t<io_, bitpos::B8, 5>  TRSA;
		};
		static inline adstrgr_t<base + 0x10> ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 拡張入力コントロールレジスタ（ADEXICR）
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

			bit_rw_t <io_, bitpos::B1>     OCSAD;

			bit_rw_t <io_, bitpos::B8>     TSS;
			bit_rw_t <io_, bitpos::B9>     OCS;
		};
		static inline adexicr_t<base + 0x12> ADEXICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 6、T、O）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x60> ADSSTR0;
		static inline rw8_t<base + 0x73> ADSSTR1;
		static inline rw8_t<base + 0x74> ADSSTR2;
		static inline rw8_t<base + 0x75> ADSSTR3;
		static inline rw8_t<base + 0x76> ADSSTR4;
		static inline rw8_t<base + 0x77> ADSSTR5;
		static inline rw8_t<base + 0x78> ADSSTR6;
		static inline rw8_t<base + 0x70> ADSSTRT;
		static inline rw8_t<base + 0x71> ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 断線検出コントロールレジスタ（ADDISCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  ADNDIS;
		};
		static inline addiscr_t<base + 0x0C> ADDISCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス (ADb)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct ad_t : public ad_base_t<base> {

		typedef ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = peripheral::AD;		///< ペリフェラル型
		static constexpr auto ADI		 = ICU::VECTOR::ADI;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI		 = ICU::VECTOR::NONE;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI		 = ICU::VECTOR::NONE;	///< グループＣスキャン終了割り込みベクター
		static constexpr auto CMPAI		 = ICU::VECTOR::NONE;	///< コンペアＡ割り込みベクター
		static constexpr auto CMPBI		 = ICU::VECTOR::NONE;	///< コンペアＢ割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;		///< A/D 変換クロック元
		static constexpr uint32_t CONV_TIME_NS = 2000;			///< 変換時間（ns）

		static constexpr uint32_t ANALOG_NUM = 7;				///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN0,	///< アナログ入力０
			AN1,	///< アナログ入力１
			AN2,	///< アナログ入力２
			AN3,	///< アナログ入力３
			AN4,	///< アナログ入力４
			AN5,	///< アナログ入力５
			AN6,	///< アナログ入力６

			TEMP,
			REF
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	ena	ポート無効の場合「false」
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//		
		static bool enable(ANALOG an, bool ena = true)
		{
			bool ret = true;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AN0:
				if(ena) {
					PORT4::PDR.B0 = 0;
					PORT4::PMR.B0 = 0;
				}
				MPC::P40PFS.ASEL = ena;
				break;
			case ANALOG::AN1:
				if(ena) {
					PORT4::PDR.B1 = 0;
					PORT4::PMR.B1 = 0;
				}
				MPC::P41PFS.ASEL = ena;
				break;
			case ANALOG::AN2:
				if(ena) {
					PORT4::PDR.B2 = 0;
					PORT4::PMR.B2 = 0;
				}
				MPC::P42PFS.ASEL = ena;
				break;
			case ANALOG::AN3:
				if(ena) {
					PORT4::PDR.B3 = 0;
					PORT4::PMR.B3 = 0;
				}
				MPC::P43PFS.ASEL = ena;
				break;
			case ANALOG::AN4:
				if(ena) {
					PORT0::PDR.B3 = 0;
					PORT0::PMR.B3 = 0;
				}
				MPC::P03PFS.ASEL = ena;
				break;
			case ANALOG::AN5:
				if(ena) {
					PORT0::PDR.B5 = 0;
					PORT0::PMR.B5 = 0;
				}
				MPC::P05PFS.ASEL = ena;
				break;
			case ANALOG::AN6:
				if(ena) {
					PORT0::PDR.B7 = 0;
					PORT0::PMR.B7 = 0;
				}
				MPC::P07PFS.ASEL = ena;
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ（ADDR）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::addr_t<ANALOG, BASE::ADDR0_::address> ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A（ADANSA）
		*/
		//-----------------------------------------------------------------//
		static inline ad_utils::adans1_t<ANALOG, BASE::ADANSA0_::address> ADANSA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct adsstr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(ANALOG an, uint8_t val) noexcept
			{
				switch(an) {
					// ADSSTRx レジスタアドレスは規則性が低いので・・
					case ANALOG::AN0: BASE::ADSSTR0 = val; break;
					case ANALOG::AN1: BASE::ADSSTR1 = val; break;
					case ANALOG::AN2: BASE::ADSSTR2 = val; break;
					case ANALOG::AN3: BASE::ADSSTR3 = val; break;
					case ANALOG::AN4: BASE::ADSSTR4 = val; break;
					case ANALOG::AN5: BASE::ADSSTR5 = val; break;
					case ANALOG::AN6: BASE::ADSSTR6 = val; break;
					case ANALOG::TEMP: BASE::ADSSTRT = val; break;
					case ANALOG::REF: BASE::ADSSTRO = val; break;
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint16_t operator () (ANALOG an) noexcept
			{
				uint16_t val;
				switch(an) {
					case ANALOG::AN0: val = BASE::ADSSTR0(); break;
					case ANALOG::AN1: val = BASE::ADSSTR1(); break;
					case ANALOG::AN2: val = BASE::ADSSTR2(); break;
					case ANALOG::AN3: val = BASE::ADSSTR3(); break;
					case ANALOG::AN4: val = BASE::ADSSTR4(); break;
					case ANALOG::AN5: val = BASE::ADSSTR5(); break;
					case ANALOG::AN6: val = BASE::ADSSTR6(); break;
					case ANALOG::TEMP: val = BASE::ADSSTRT(); break;
					case ANALOG::REF: val = BASE::ADSSTRO(); break;
				}
				return val;
			}
		};
		static inline adsstr_t ADSSTR;
	};
	typedef ad_t<0x0008'9800> AD;
}
