#pragma once
//=============================================================================//
/*!	@file
	@brief	RX63T 10 ビット A/D コンバータ（ADa）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t base>
	struct ad_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ n（ADDRn）（n = A ～ T）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20> ADDRA_;
		static ADDRA_ ADDRA;
		typedef rw16_t<base + 0x22> ADDRB_;
		static ADDRB_ ADDRB;
		typedef rw16_t<base + 0x24> ADDRC_;
		static ADDRC_ ADDRC;
		typedef rw16_t<base + 0x26> ADDRD_;
		static ADDRD_ ADDRD;
		typedef rw16_t<base + 0x28> ADDRE_;
		static ADDRE_ ADDRE;
		typedef rw16_t<base + 0x2A> ADDRF_;
		static ADDRF_ ADDRF;
		typedef rw16_t<base + 0x2C> ADDRG_;
		static ADDRG_ ADDRG;
		typedef rw16_t<base + 0x2E> ADDRH_;
		static ADDRH_ ADDRH;
		typedef rw16_t<base + 0x30> ADDRI_;
		static ADDRI_ ADDRI;
		typedef rw16_t<base + 0x32> ADDRJ_;
		static ADDRJ_ ADDRJ;
		typedef rw16_t<base + 0x34> ADDRK_;
		static ADDRK_ ADDRK;
		typedef rw16_t<base + 0x36> ADDRL_;
		static ADDRL_ ADDRL;
		typedef rw16_t<base + 0x38> ADDRM_;
		static ADDRM_ ADDRM;
		typedef rw16_t<base + 0x3A> ADDRN_;
		static ADDRN_ ADDRN;
		typedef rw16_t<base + 0x3C> ADDRO_;
		static ADDRO_ ADDRO;
		typedef rw16_t<base + 0x3E> ADDRP_;
		static ADDRP_ ADDRP;
		typedef rw16_t<base + 0x40> ADDRQ_;
		static ADDRQ_ ADDRQ;
		typedef rw16_t<base + 0x42> ADDRR_;
		static ADDRR_ ADDRR;
		typedef rw16_t<base + 0x44> ADDRS_;
		static ADDRS_ ADDRS;
		typedef rw16_t<base + 0x46> ADDRT_;
		static ADDRT_ ADDRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断データレジスタ（ADRD）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adrd_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  AD;

			bits_rw_t<io_, bitpos::B14, 2>  DIAGST;
		};
		typedef adrd_t<base + 0x1E> ADRD_;
		static ADRD_ ADRD;


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

			bit_rw_t <io_, bitpos::B8>     EXTRG;
			bit_rw_t <io_, bitpos::B9>     TRGE;

			bit_rw_t <io_, bitpos::B12>    ADIE;

			bit_rw_t <io_, bitpos::B14>    ADCS;
			bit_rw_t <io_, bitpos::B15>    ADST;
		};
		typedef adcsr_t<base + 0x00> ADCSR_;
		static ADCSR_ ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ 0（ADANSA0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> ANSA0;
		};
		typedef adansa0_t<base + 0x04> ADANSA0_;
		static ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ 1（ADANSA1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  ANSA;
		};
		typedef adansa1_t<base + 0x06> ADANSA1_;
		static ADANSA1_ ADANSA1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ 0（ADADS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> ADS0;
		};
		typedef adads0_t<base + 0x08> ADADS0_;
		static ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算モード選択レジスタ 1（ADADS1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> ADS;
		};
		typedef adads1_t<base + 0x0A> ADADS1_;
		static ADADS1_ ADADS1;


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
		typedef adadc_t<base + 0x0C> ADADC_;
		static ADADC_ ADADC;


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

			bit_rw_t <io_, bitpos::B2>    ADPRC;

			bit_rw_t <io_, bitpos::B5>    ACE;

			bits_rw_t<io_, bitpos::B8, 2> DIAGVAL;
			bit_rw_t <io_, bitpos::B10>   DIAGM;

			bit_rw_t <io_, bitpos::B15>   ADRFMT;
		};
		typedef adcer_t<base + 0x0E> ADCER_;
		static ADCER_ ADCER;


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

			bits_rw_t<io_, bitpos::B8, 6> TRSA;
		};
		typedef adstrgr_t<base + 0x10> ADSTRGR_;
		static ADSTRGR_ ADSTRGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ n（ADSSTRn）（n=0 ～ 7）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x60> ADSSTR0_;
		static ADSSTR0_ ADSSTR0;
		typedef rw8_t<base + 0x73> ADSSTR1_;
		static ADSSTR1_ ADSSTR1;
		typedef rw8_t<base + 0x74> ADSSTR2_;
		static ADSSTR2_ ADSSTR2;
		typedef rw8_t<base + 0x75> ADSSTR3_;
		static ADSSTR3_ ADSSTR3;
		typedef rw8_t<base + 0x76> ADSSTR4_;
		static ADSSTR4_ ADSSTR4;
		typedef rw8_t<base + 0x77> ADSSTR5_;
		static ADSSTR5_ ADSSTR5;
		typedef rw8_t<base + 0x78> ADSSTR6_;
		static ADSSTR6_ ADSSTR6;
		typedef rw8_t<base + 0x79> ADSSTR7_;
		static ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x61> ADSSTRL_;
		static ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  デジタル電源制御回路出力設定レジスタ（ADDPCONR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addpconr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DPCOE;
		};
		typedef addpconr_t<base + 0x7D> ADDPCONR_;
		static ADDPCONR_ ADDPCONR;
	};
	template <uint32_t base> typename ad_base_t<base>::ADDRA_  ad_base_t<base>::ADDRA;
	template <uint32_t base> typename ad_base_t<base>::ADDRB_  ad_base_t<base>::ADDRB;
	template <uint32_t base> typename ad_base_t<base>::ADDRC_  ad_base_t<base>::ADDRC;
	template <uint32_t base> typename ad_base_t<base>::ADDRD_  ad_base_t<base>::ADDRD;
	template <uint32_t base> typename ad_base_t<base>::ADDRE_  ad_base_t<base>::ADDRE;
	template <uint32_t base> typename ad_base_t<base>::ADDRF_  ad_base_t<base>::ADDRF;
	template <uint32_t base> typename ad_base_t<base>::ADDRG_  ad_base_t<base>::ADDRG;
	template <uint32_t base> typename ad_base_t<base>::ADDRH_  ad_base_t<base>::ADDRH;
	template <uint32_t base> typename ad_base_t<base>::ADDRI_  ad_base_t<base>::ADDRI;
	template <uint32_t base> typename ad_base_t<base>::ADDRJ_  ad_base_t<base>::ADDRJ;
	template <uint32_t base> typename ad_base_t<base>::ADDRK_  ad_base_t<base>::ADDRK;
	template <uint32_t base> typename ad_base_t<base>::ADDRL_  ad_base_t<base>::ADDRL;
	template <uint32_t base> typename ad_base_t<base>::ADDRM_  ad_base_t<base>::ADDRM;
	template <uint32_t base> typename ad_base_t<base>::ADDRN_  ad_base_t<base>::ADDRN;
	template <uint32_t base> typename ad_base_t<base>::ADDRO_  ad_base_t<base>::ADDRO;
	template <uint32_t base> typename ad_base_t<base>::ADDRP_  ad_base_t<base>::ADDRP;
	template <uint32_t base> typename ad_base_t<base>::ADDRQ_  ad_base_t<base>::ADDRQ;
	template <uint32_t base> typename ad_base_t<base>::ADDRR_  ad_base_t<base>::ADDRR;
	template <uint32_t base> typename ad_base_t<base>::ADDRS_  ad_base_t<base>::ADDRS;
	template <uint32_t base> typename ad_base_t<base>::ADDRT_  ad_base_t<base>::ADDRT;
	template <uint32_t base> typename ad_base_t<base>::ADRD_  ad_base_t<base>::ADRD;
	template <uint32_t base> typename ad_base_t<base>::ADCSR_  ad_base_t<base>::ADCSR;
	template <uint32_t base> typename ad_base_t<base>::ADANSA0_  ad_base_t<base>::ADANSA0;
	template <uint32_t base> typename ad_base_t<base>::ADANSA1_  ad_base_t<base>::ADANSA1;
	template <uint32_t base> typename ad_base_t<base>::ADADS0_  ad_base_t<base>::ADADS0;
	template <uint32_t base> typename ad_base_t<base>::ADADS1_  ad_base_t<base>::ADADS1;
	template <uint32_t base> typename ad_base_t<base>::ADADC_  ad_base_t<base>::ADADC;
	template <uint32_t base> typename ad_base_t<base>::ADCER_  ad_base_t<base>::ADCER;
	template <uint32_t base> typename ad_base_t<base>::ADSTRGR_  ad_base_t<base>::ADSTRGR;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR0_ ad_base_t<base>::ADSSTR0;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR1_ ad_base_t<base>::ADSSTR1;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR2_ ad_base_t<base>::ADSSTR2;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR3_ ad_base_t<base>::ADSSTR3;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR4_ ad_base_t<base>::ADSSTR4;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR5_ ad_base_t<base>::ADSSTR5;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR6_ ad_base_t<base>::ADSSTR6;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR7_ ad_base_t<base>::ADSSTR7;
	template <uint32_t base> typename ad_base_t<base>::ADSSTRL_ ad_base_t<base>::ADSSTRL;
	template <uint32_t base> typename ad_base_t<base>::ADDPCONR_ ad_base_t<base>::ADDPCONR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	adi		割り込み番号
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR adi>
	struct ada_t : public ad_base_t<base> {

		typedef ad_base_t<base> BASE;

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto ADI = adi;
		static constexpr uint32_t ANALOG_NUM = 20;	///< アナログ入力数
		static constexpr auto PCLK = clock_profile::PCLKC;	///< A/D 変換クロック元

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN0,
			AN1,
			AN2,
			AN3,
			AN4,
			AN5,
			AN6,
			AN7,
			AN8,
			AN9,
			AN10,
			AN11,
			AN12,
			AN13,
			AN14,
			AN15,
			AN16,
			AN17,
			AN18,
			AN19,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ n（ADDR）
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator () (ANALOG an) noexcept
			{
				return rd16_(BASE::ADDR0::addresss + (static_cast<uint32_t>(an) * 2));
			}
		};
		typedef addr_t ADDR_;
		static ADDR_ ADDR;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR adi>
		typename ada_t<base, per, adi>::ADDR_ ada_t<base, per, adi>::ADDR;


	typedef ada_t<0x0008'9800, peripheral::AD, ICU::VECTOR::ADI0> AD;
}
