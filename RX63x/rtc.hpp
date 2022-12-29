#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N グループ RTCa 定義
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
		@brief  RTC 定義基底クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct rtc_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto ALM = ICU::VECTOR::ALM;	///< アラーム割り込みベクタ
		static constexpr auto PRD = ICU::VECTOR::PRD;	///< 周期割り込みベクタ
		static constexpr auto CUP = ICU::VECTOR::CUP;	///< 桁上げ割り込みベクタ
		static constexpr bool BINARY = false;			///< バイナリーカウントモード


		//-----------------------------------------------------------------//
		/*!
			@brief  64Hz カウンタ（R64CNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct r64cnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	F64HZ;
			bit_rw_t<io_, bitpos::B1>	F32HZ;
			bit_rw_t<io_, bitpos::B2>	F16HZ;
			bit_rw_t<io_, bitpos::B3>	F8HZ;
			bit_rw_t<io_, bitpos::B4>	F4HZ;
			bit_rw_t<io_, bitpos::B5>	F2HZ;
			bit_rw_t<io_, bitpos::B6>	F1HZ;
		};
		typedef r64cnt_t<0x0008'C400> R64CNT_;
		static  R64CNT_ R64CNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  秒カウンタ（RSECCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rseccnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  SEC1;
			bits_rw_t<io_, bitpos::B4, 3>  SEC10;
		};
		typedef rseccnt_t<0x0008'C402> RSECCNT_;
		static  RSECCNT_ RSECCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  分カウンタ（RMINCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmincnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  MIN1;
			bits_rw_t<io_, bitpos::B4, 3>  MIN10;
		};
		typedef rmincnt_t<0x0008'C404> RMINCNT_;
		static  RMINCNT_ RMINCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  時カウンタ（RHRCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rhrcnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  HR1;
			bits_rw_t<io_, bitpos::B4, 2>  HR10;
		};
		typedef rhrcnt_t<0x0008'C406> RHRCNT_;
		static  RHRCNT_ RHRCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  曜日カウンタ（RWKCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rwkcnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  DAYW;
		};
		typedef rwkcnt_t<0x0008'C408> RWKCNT_;
		static  RWKCNT_ RWKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  日カウンタ（RDAYCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rdaycnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> DATE1;
			bits_rw_t<io_, bitpos::B4, 2> DATE10;
		};
		typedef rdaycnt_t<0x0008'C40A> RDAYCNT_;
		static  RDAYCNT_ RDAYCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  月カウンタ（RMONCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmoncnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MON1;
			bit_rw_t <io_, bitpos::B4>    MON10;
		};
		typedef rmoncnt_t<0x0008'C40C> RMONCNT_;
		static  RMONCNT_ RMONCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  年カウンタ（RYRCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ryrcnt_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4> YEAR;
			bits_rw_t<io_, bitpos::B4,  4> YEAR10;
			bits_rw_t<io_, bitpos::B8,  4> YEAR100;
			bits_rw_t<io_, bitpos::B12, 4> YEAR1000;
		};
		typedef ryrcnt_t<0x0008'C40E> RYRCNT_;
		static  RYRCNT_ RYRCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  秒アラームレジスタ（RSECAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rsecar_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> SEC1;
			bits_rw_t<io_, bitpos::B4, 3> SEC10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rsecar_t<0x0008'C410> RSECAR_;
		static  RSECAR_ RSECAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  分アラームレジスタ（RMINAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rminar_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MIN1;
			bits_rw_t<io_, bitpos::B4, 3> MIN10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rminar_t<0x0008'C412> RMINAR_;
		static  RMINAR_ RMINAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  時アラームレジスタ（RHRAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rhrar_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> HR1;
			bits_rw_t<io_, bitpos::B4, 2> HR10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rhrar_t<0x0008'C414> RHRAR_;
		static  RHRAR_ RHRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  曜日アラームレジスタ（RWKAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rwkar_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> DAYW;

			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rwkar_t<0x0008'C416> RWKAR_;
		static  RWKAR_ RWKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  日アラームレジスタ（RDAYAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rdayar_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> DATE1;
			bits_rw_t<io_, bitpos::B4, 2> DATE10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rdayar_t<0x0008'C418> RDAYAR_;
		static  RDAYAR_ RDAYAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  月アラームレジスタ（RMONAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmonar_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MON1;
			bit_rw_t <io_, bitpos::B4>    MON10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rmonar_t<0x0008'C41A> RMONAR_;
		static  RMONAR_ RMONAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  年アラームレジスタ（RYRAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ryrar_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4> YEAR;
			bits_rw_t<io_, bitpos::B4,  4> YEAR10;
			bits_rw_t<io_, bitpos::B8,  4> YEAR100;
			bits_rw_t<io_, bitpos::B12, 4> YEAR1000;
		};
		typedef ryrar_t<0x0008'C41C> RYRAR_;
		static  RYRAR_ RYRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  年アラーム許可レジスタ（RYRAREN）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ryraren_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  ENB;
		};
		typedef ryraren_t<0x0008'C41E> RYRAREN_;
		static  RYRAREN_ RYRAREN;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 1（RCR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>	  AIE;
			bit_rw_t <io_, bitpos::B1>	  CIE;
			bit_rw_t <io_, bitpos::B2>	  PIE;

			bits_rw_t<io_, bitpos::B4, 3> PES;
		};
		typedef rcr1_t<0x0008'C422> RCR1_;
		static  RCR1_ RCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 2（RCR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  START;
			bit_rw_t<io_, bitpos::B1>  RESET;
			bit_rw_t<io_, bitpos::B2>  ADJ;
			bit_rw_t<io_, bitpos::B3>  RTCOE;
			bit_rw_t<io_, bitpos::B4>  AADJE;
			bit_rw_t<io_, bitpos::B5>  AADJP;
			bit_rw_t<io_, bitpos::B6>  HR24;
		};
		typedef rcr2_t<0x0008'C424> RCR2_;
		static  RCR2_ RCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 3（RCR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     RTCEN;
			bits_rw_t<io_, bitpos::B1, 3>  RTCDV;
		};
		typedef rcr3_t<0x0008'C426> RCR3_;
		static  RCR3_ RCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 4（RCR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr4_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     RCKSEL;
		};
		typedef rcr4_t<0x0008'C428> RCR4_;
		static  RCR4_ RCR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ H/L（RFRH）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rfrh_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     RFC;
		};
		typedef rfrh_t<0x0008'C42A> RFRH_;
		static RFRH_ RFRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ H/L（RFRL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rfrl_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 16> RFC;
		};
		typedef rfrl_t<0x0008'C42C> RFRL_;
		static RFRL_ RFRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  時間誤差補正レジスタ（RADJ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct radj_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  ADJ;
			bits_rw_t<io_, bitpos::B6, 2>  PMAD;
		};
		typedef radj_t<0x0008'C428> RADJ_;
		static  RADJ_ RADJ;


		//-----------------------------------------------------------------//
		/*!
			@brief  時間キャプチャ制御レジスタ y（RTCCRy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rtccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TCCT;
			bit_rw_t <io_, bitpos::B2>     TCST;

			bits_rw_t<io_, bitpos::B4, 2>  TCNF;

			bit_rw_t <io_, bitpos::B7>     TCEN;
		};
		typedef rtccr_t<0x0008'C440> RTCCR0_;
		static  RTCCR0_ RTCCR0;
		typedef rtccr_t<0x0008'C442> RTCCR1_;
		static  RTCCR1_ RTCCR1;
		typedef rtccr_t<0x0008'C444> RTCCR2_;
		static  RTCCR2_ RTCCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  秒キャプチャレジスタ y（RSECCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rseccp_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  SEC1;

			bits_rw_t<io_, bitpos::B4, 3>  SEC10;
		};
		typedef rseccp_t<0x0008'C452> RSECCP0_;
		static  RSECCP0_ RSECCP0;
		typedef rseccp_t<0x0008'C462> RSECCP1_;
		static  RSECCP1_ RSECCP1;
		typedef rseccp_t<0x0008'C472> RSECCP2_;
		static  RSECCP2_ RSECCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  分キャプチャレジスタ y（RMINCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmincp_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  MIN1;

			bits_rw_t<io_, bitpos::B4, 3>  MIN10;
		};
		typedef rmincp_t<0x0008'C454> RMINCP0_;
		static  RMINCP0_ RMINCP0;
		typedef rmincp_t<0x0008'C464> RMINCP1_;
		static  RMINCP1_ RMINCP1;
		typedef rmincp_t<0x0008'C474> RMINCP2_;
		static  RMINCP2_ RMINCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  時キャプチャレジスタ y（RHRCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rhrcp_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  HR1;
			bits_rw_t<io_, bitpos::B4, 2>  HR10;
			bit_rw_t <io_, bitpos::B6>     PM;
		};
		typedef rhrcp_t<0x0008'C456> RHRCP0_;
		static  RHRCP0_ RHRCP0;
		typedef rhrcp_t<0x0008'C466> RHRCP1_;
		static  RHRCP1_ RHRCP1;
		typedef rhrcp_t<0x0008'C476> RHRCP2_;
		static  RHRCP2_ RHRCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  日キャプチャレジスタ y（RDAYCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rdaycp_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DATE1;
			bits_rw_t<io_, bitpos::B4, 2>  DATE10;
		};
		typedef rdaycp_t<0x0008'C45A> RDAYCP0_;
		static  RDAYCP0_ RDAYCP0;
		typedef rdaycp_t<0x0008'C46A> RDAYCP1_;
		static  RDAYCP1_ RDAYCP1;
		typedef rdaycp_t<0x0008'C47A> RDAYCP2_;
		static  RDAYCP2_ RDAYCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  月キャプチャレジスタ y（RMONCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmoncp_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  MON1;
			bit_rw_t <io_, bitpos::B4>     MON10;
		};
		typedef rmoncp_t<0x0008'C45C> RMONCP0_;
		static  RMONCP0_ RMONCP0;
		typedef rmoncp_t<0x0008'C46C> RMONCP1_;
		static  RMONCP1_ RMONCP1;
		typedef rmoncp_t<0x0008'C47C> RMONCP2_;
		static  RMONCP2_ RMONCP2;
	};
	template <peripheral per> typename rtc_t<per>::R64CNT_ rtc_t<per>::R64CNT;
	template <peripheral per> typename rtc_t<per>::RSECCNT_ rtc_t<per>::RSECCNT;
	template <peripheral per> typename rtc_t<per>::RMINCNT_ rtc_t<per>::RMINCNT;
	template <peripheral per> typename rtc_t<per>::RHRCNT_ rtc_t<per>::RHRCNT;
	template <peripheral per> typename rtc_t<per>::RWKCNT_ rtc_t<per>::RWKCNT;
	template <peripheral per> typename rtc_t<per>::RDAYCNT_ rtc_t<per>::RDAYCNT;
	template <peripheral per> typename rtc_t<per>::RMONCNT_ rtc_t<per>::RMONCNT;
	template <peripheral per> typename rtc_t<per>::RYRCNT_ rtc_t<per>::RYRCNT;
	template <peripheral per> typename rtc_t<per>::RSECAR_ rtc_t<per>::RSECAR;
	template <peripheral per> typename rtc_t<per>::RMINAR_ rtc_t<per>::RMINAR;
	template <peripheral per> typename rtc_t<per>::RHRAR_ rtc_t<per>::RHRAR;
	template <peripheral per> typename rtc_t<per>::RWKAR_ rtc_t<per>::RWKAR;
	template <peripheral per> typename rtc_t<per>::RDAYAR_ rtc_t<per>::RDAYAR;
	template <peripheral per> typename rtc_t<per>::RMONAR_ rtc_t<per>::RMONAR;
	template <peripheral per> typename rtc_t<per>::RYRAR_ rtc_t<per>::RYRAR;
	template <peripheral per> typename rtc_t<per>::RYRAREN_ rtc_t<per>::RYRAREN;
	template <peripheral per> typename rtc_t<per>::RCR1_ rtc_t<per>::RCR1;
	template <peripheral per> typename rtc_t<per>::RCR2_ rtc_t<per>::RCR2;
	template <peripheral per> typename rtc_t<per>::RCR3_ rtc_t<per>::RCR3;
	template <peripheral per> typename rtc_t<per>::RCR4_ rtc_t<per>::RCR4;
	template <peripheral per> typename rtc_t<per>::RFRH_ rtc_t<per>::RFRH;
	template <peripheral per> typename rtc_t<per>::RFRL_ rtc_t<per>::RFRL;
	template <peripheral per> typename rtc_t<per>::RADJ_ rtc_t<per>::RADJ;
	template <peripheral per> typename rtc_t<per>::RTCCR0_ rtc_t<per>::RTCCR0;
	template <peripheral per> typename rtc_t<per>::RTCCR1_ rtc_t<per>::RTCCR1;
	template <peripheral per> typename rtc_t<per>::RTCCR2_ rtc_t<per>::RTCCR2;
	template <peripheral per> typename rtc_t<per>::RSECCP0_ rtc_t<per>::RSECCP0;
	template <peripheral per> typename rtc_t<per>::RSECCP1_ rtc_t<per>::RSECCP1;
	template <peripheral per> typename rtc_t<per>::RSECCP2_ rtc_t<per>::RSECCP2;
	template <peripheral per> typename rtc_t<per>::RMINCP0_ rtc_t<per>::RMINCP0;
	template <peripheral per> typename rtc_t<per>::RMINCP1_ rtc_t<per>::RMINCP1;
	template <peripheral per> typename rtc_t<per>::RMINCP2_ rtc_t<per>::RMINCP2;
	template <peripheral per> typename rtc_t<per>::RHRCP0_ rtc_t<per>::RHRCP0;
	template <peripheral per> typename rtc_t<per>::RHRCP1_ rtc_t<per>::RHRCP1;
	template <peripheral per> typename rtc_t<per>::RHRCP2_ rtc_t<per>::RHRCP2;
	template <peripheral per> typename rtc_t<per>::RDAYCP0_ rtc_t<per>::RDAYCP0;
	template <peripheral per> typename rtc_t<per>::RDAYCP1_ rtc_t<per>::RDAYCP1;
	template <peripheral per> typename rtc_t<per>::RDAYCP2_ rtc_t<per>::RDAYCP2;
	template <peripheral per> typename rtc_t<per>::RMONCP0_ rtc_t<per>::RMONCP0;
	template <peripheral per> typename rtc_t<per>::RMONCP1_ rtc_t<per>::RMONCP1;
	template <peripheral per> typename rtc_t<per>::RMONCP2_ rtc_t<per>::RMONCP2;

	typedef rtc_t<peripheral::RTC> RTC;
}
