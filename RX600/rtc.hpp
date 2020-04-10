#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65x グループ・RTC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

/// RTC モジュールが無いデバイスでエラーとする
#if defined(SIG_RX24T) || defined(SIG_RX66T)
#  error "rtc.hpp: This module does not exist"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RTC 定義基底クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct rtc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  64Hz カウンタ（R64CNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct r64cnt_t_ : public rw8_t<base> {
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
		typedef r64cnt_t_<0x0008C400> r64cnt_t;
		static r64cnt_t R64CNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  秒カウンタ（RSECCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rseccnt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  SEC1;
			bits_rw_t<io_, bitpos::B4, 3>  SEC10;
		};
		typedef rseccnt_t_<0x0008C402> rseccnt_t;
		static rseccnt_t RSECCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0（BCNT0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C402> bcnt0_t;
		static bcnt0_t BCNT0;


		//-----------------------------------------------------------------//
		/*!
			@brief  分カウンタ（RMINCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmincnt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  MIN1;
			bits_rw_t<io_, bitpos::B4, 3>  MIN10;
		};
		typedef rmincnt_t_<0x0008C404> rmincnt_t;
		static rmincnt_t RMINCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1（BCNT1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C404> bcnt1_t;
		static bcnt1_t BCNT1;


		//-----------------------------------------------------------------//
		/*!
			@brief  時カウンタ（RHRCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rhrcnt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  HR1;
			bits_rw_t<io_, bitpos::B4, 2>  HR10;
			bit_rw_t <io_, bitpos::B6>     PM;
		};
		typedef rhrcnt_t_<0x0008C406> rhrcnt_t;
		static rhrcnt_t RHRCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2（BCNT2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C406> bcnt2_t;
		static bcnt2_t BCNT2;


		//-----------------------------------------------------------------//
		/*!
			@brief  曜日カウンタ（RWKCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rwkcnt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  DAYW;
		};
		typedef rwkcnt_t_<0x0008C408> rwkcnt_t;
		static rwkcnt_t RWKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3（BCNT3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C408> bcnt3_t;
		static bcnt3_t BCNT3;


		//-----------------------------------------------------------------//
		/*!
			@brief  日カウンタ（RDAYCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rdaycnt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> DATE1;
			bits_rw_t<io_, bitpos::B4, 2> DATE10;
		};
		typedef rdaycnt_t_<0x0008C40A> rdaycnt_t;
		static rdaycnt_t RDAYCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  月カウンタ（RMONCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmoncnt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MON1;
			bit_rw_t <io_, bitpos::B4>    MON10;
		};
		typedef rmoncnt_t_<0x0008C40C> rmoncnt_t;
		static rmoncnt_t RMONCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  年カウンタ（RYRCNT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ryrcnt_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> YR1;
			bits_rw_t<io_, bitpos::B4, 4> YR10;
		};
		typedef ryrcnt_t_<0x0008C40E> ryrcnt_t;
		static ryrcnt_t RYRCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  秒アラームレジスタ（RSECAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rsecar_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> SEC1;
			bits_rw_t<io_, bitpos::B4, 3> SEC10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rsecar_t_<0x0008C410> rsecar_t;
		static rsecar_t RSECAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラームレジスタ（BCNT0AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C410> bcnt0ar_t;
		static bcnt0ar_t BCNT0AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  分アラームレジスタ（RMINAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rminar_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MIN1;
			bits_rw_t<io_, bitpos::B4, 3> MIN10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rminar_t_<0x0008C412> rminar_t;
		static rminar_t RMINAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラームレジスタ（BCNT1AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C412> bcnt1ar_t;
		static bcnt1ar_t BCNT1AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  時アラームレジスタ（RHRAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rhrar_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> HR1;
			bits_rw_t<io_, bitpos::B4, 2> HR10;
			bit_rw_t <io_, bitpos::B6>    PM;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rhrar_t_<0x0008C414> rhrar_t;
		static rhrar_t RHRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラームレジスタ（BCNT2AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C414> bcnt2ar_t;
		static bcnt2ar_t BCNT2AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  曜日アラームレジスタ（RWKAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rwkar_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> DAYW;

			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rwkar_t_<0x0008C416> rwkar_t;
		static rwkar_t RWKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラームレジスタ（BCNT3AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C416> bcnt3ar_t;
		static bcnt3ar_t BCNT3AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  日アラームレジスタ（RDAYAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rdayar_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> DATE1;
			bits_rw_t<io_, bitpos::B4, 2> DATE10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rdayar_t_<0x0008C418> rdayar_t;
		static rdayar_t RDAYAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラーム許可レジスタ（BCNT0AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C418> bcnt0aer_t;
		static bcnt0aer_t BCNT0AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  月アラームレジスタ（RMONAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmonar_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MON1;
			bit_rw_t <io_, bitpos::B4>    MON10;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rmonar_t_<0x0008C41A> rmonar_t;
		static rmonar_t RMONAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラーム許可レジスタ（BCNT1AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C41A> bcnt1aer_t;
		static bcnt1aer_t BCNT1AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  年アラームレジスタ（RYRAR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ryrar_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> YR1;
			bits_rw_t<io_, bitpos::B4, 4> YR10;
		};
		typedef ryrar_t_<0x0008C41C> ryrar_t;
		static ryrar_t RYRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラーム許可レジスタ（BCNT2AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C41C> bcnt2aer_t;
		static bcnt2aer_t BCNT2AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  年アラーム許可レジスタ（RYRAREN）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ryraren_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  ENB;
		};
		typedef ryraren_t_<0x0008C41E> ryraren_t;
		static ryraren_t RYRAREN;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラーム許可レジスタ（BCNT3AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C41E> bcnt3aer_t;
		static bcnt3aer_t BCNT3AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 1（RCR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr1_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>	  AIE;
			bit_rw_t <io_, bitpos::B1>	  CIE;
			bit_rw_t <io_, bitpos::B2>	  PIE;
			bit_rw_t <io_, bitpos::B3>	  RTCOS;
			bits_rw_t<io_, bitpos::B4, 4> PES;
		};
		typedef rcr1_t_<0x0008C422> rcr1_t;
		static rcr1_t RCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 2（RCR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr2_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  START;
			bit_rw_t<io_, bitpos::B1>  RESET;
			bit_rw_t<io_, bitpos::B2>  ADJ30;
			bit_rw_t<io_, bitpos::B3>  RTCOE;
			bit_rw_t<io_, bitpos::B4>  AADJE;
			bit_rw_t<io_, bitpos::B5>  AADJP;
			bit_rw_t<io_, bitpos::B6>  HR24;
			bit_rw_t<io_, bitpos::B7>  CNTMD;
		};
		typedef rcr2_t_<0x0008C424> rcr2_t;
		static rcr2_t RCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 3（RCR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr3_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>	  RTCEN;
			bits_rw_t<io_, bitpos::B1, 3> RTCDV;
		};
		typedef rcr3_t_<0x0008C426> rcr3_t;
		static rcr3_t RCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  RTC コントロールレジスタ 4（RCR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rcr4_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>	  RCKSEL;
		};
		typedef rcr4_t_<0x0008C428> rcr4_t;
		static rcr4_t RCR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ H（RFRH）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008C42A> rfrh_t;
		static rfrh_t RFRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ L（RFRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008C42C> rfrl_t;
		static rfrl_t RFRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  時間誤差補正レジスタ（RADJ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct radj_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> ADJ;
			bits_rw_t<io_, bitpos::B6, 2> PMADJ;
		};
		typedef radj_t_<0x0008C42E> radj_t;
		static radj_t RADJ;


		//-----------------------------------------------------------------//
		/*!
			@brief  時間キャプチャ制御レジスタ y（RTCCRy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rtccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> TCCT;
			bit_rw_t <io_, bitpos::B2>    TCST;
			bits_rw_t<io_, bitpos::B4, 2> TCNF;
			bit_rw_t <io_, bitpos::B7>    TCEN;
		};
		typedef rtccr_t_<0x0008C440> rtccr0_t;
		static rtccr0_t RTCCR0;
		typedef rtccr_t_<0x0008C442> rtccr1_t;
		static rtccr1_t RTCCR1;
		typedef rtccr_t_<0x0008C444> rtccr2_t;
		static rtccr2_t RTCCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  秒キャプチャレジスタ y（RSECCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rseccpy_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> SEC1;
			bits_rw_t<io_, bitpos::B4, 3> SEC10;
		};
		typedef rseccpy_t_<0x0008C452> rseccpy0_t;
		static rseccpy0_t RSECCPY0;
		typedef rseccpy_t_<0x0008C462> rseccpy1_t;
		static rseccpy1_t RSECCPY1;
		typedef rseccpy_t_<0x0008C472> rseccpy2_t;
		static rseccpy2_t RSECCPY2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 0（BCNT0CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C452> bcnt0cp0_t;
		static bcnt0cp0_t BCNT0CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 1（BCNT0CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C462> bcnt0cp1_t;
		static bcnt0cp1_t BCNT0CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 2（BCNT0CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C472> bcnt0cp2_t;
		static bcnt0cp2_t BCNT0CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  分キャプチャレジスタ y（RMINCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmincpy_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MIN1;
			bits_rw_t<io_, bitpos::B4, 3> MIN10;
		};
		typedef rmincpy_t_<0x0008C454> rmincp0_t;
		static rmincp0_t RMINCP0;
		typedef rmincpy_t_<0x0008C464> rmincp1_t;
		static rmincp1_t RMINCP1;
		typedef rmincpy_t_<0x0008C474> rmincp2_t;
		static rmincp2_t RMINCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 0（BCNT1CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C454> bcnt1cp0_t;
		static bcnt1cp0_t BCNT1CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 1（BCNT1CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C464> bcnt1cp1_t;
		static bcnt1cp1_t BCNT1CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 2（BCNT1CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C474> bcnt1cp2_t;
		static bcnt1cp2_t BCNT1CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  時キャプチャレジスタ y（RHRCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rhrcpy_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> HR1;
			bits_rw_t<io_, bitpos::B4, 2> HR10;
			bit_rw_t <io_, bitpos::B6>    PM;
		};
		typedef rhrcpy_t_<0x0008C456> rhrcp0_t;
		static rhrcp0_t RHRCP0;
		typedef rhrcpy_t_<0x0008C466> rhrcp1_t;
		static rhrcp1_t RHRCP1;
		typedef rhrcpy_t_<0x0008C476> rhrcp2_t;
		static rhrcp2_t RHRCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 0（BCNT2CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C456> bcnt2cp0_t;
		static bcnt2cp0_t BCNT2CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 1（BCNT2CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C466> bcnt2cp1_t;
		static bcnt2cp1_t BCNT2CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 2（BCNT2CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C476> bcnt2cp2_t;
		static bcnt2cp2_t BCNT2CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  日キャプチャレジスタ y（RDAYCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rdaycpy_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> DATE1;
			bits_rw_t<io_, bitpos::B4, 2> DATE10;
		};
		typedef rdaycpy_t_<0x0008C45A> rdaycp0_t;
		static rdaycp0_t RDAYCP0;
		typedef rdaycpy_t_<0x0008C46A> rdaycp1_t;
		static rdaycp1_t RDAYCP1;
		typedef rdaycpy_t_<0x0008C47A> rdaycp2_t;
		static rdaycp2_t RDAYCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 0（BCNT3CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C45A> bcnt3cp0_t;
		static bcnt3cp0_t BCNT3CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 1（BCNT3CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C46A> bcnt3cp1_t;
		static bcnt3cp1_t BCNT3CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 2（BCNT3CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C47A> bcnt3cp2_t;
		static bcnt3cp2_t BCNT3CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  月キャプチャレジスタ y（RMONCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmoncpy_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MON1;
			bit_rw_t <io_, bitpos::B4>    MON10;
		};
		typedef rmoncpy_t_<0x0008C45C> rmoncp0_t;
		static rmoncp0_t RMONCP0;
		typedef rmoncpy_t_<0x0008C46C> rmoncp1_t;
		static rmoncp1_t RMONCP1;
		typedef rmoncpy_t_<0x0008C47C> rmoncp2_t;
		static rmoncp2_t RMONCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};
	typedef rtc_t<peripheral::RTC> RTC;

	template <peripheral per> typename rtc_t<per>::r64cnt_t rtc_t<per>::R64CNT;
	template <peripheral per> typename rtc_t<per>::rseccnt_t rtc_t<per>::RSECCNT;
	template <peripheral per> typename rtc_t<per>::bcnt0_t rtc_t<per>::BCNT0;
	template <peripheral per> typename rtc_t<per>::rmincnt_t rtc_t<per>::RMINCNT;
	template <peripheral per> typename rtc_t<per>::bcnt1_t rtc_t<per>::BCNT1;
	template <peripheral per> typename rtc_t<per>::rhrcnt_t rtc_t<per>::RHRCNT;
	template <peripheral per> typename rtc_t<per>::bcnt2_t rtc_t<per>::BCNT2;
	template <peripheral per> typename rtc_t<per>::rwkcnt_t rtc_t<per>::RWKCNT;
	template <peripheral per> typename rtc_t<per>::bcnt3_t rtc_t<per>::BCNT3;
	template <peripheral per> typename rtc_t<per>::rdaycnt_t rtc_t<per>::RDAYCNT;
	template <peripheral per> typename rtc_t<per>::rmoncnt_t rtc_t<per>::RMONCNT;
	template <peripheral per> typename rtc_t<per>::ryrcnt_t rtc_t<per>::RYRCNT;
	template <peripheral per> typename rtc_t<per>::rsecar_t rtc_t<per>::RSECAR;
	template <peripheral per> typename rtc_t<per>::bcnt0ar_t rtc_t<per>::BCNT0AR;
	template <peripheral per> typename rtc_t<per>::rminar_t rtc_t<per>::RMINAR;
	template <peripheral per> typename rtc_t<per>::bcnt1ar_t rtc_t<per>::BCNT1AR;
	template <peripheral per> typename rtc_t<per>::rhrar_t rtc_t<per>::RHRAR;
	template <peripheral per> typename rtc_t<per>::bcnt2ar_t rtc_t<per>::BCNT2AR;
	template <peripheral per> typename rtc_t<per>::rwkar_t rtc_t<per>::RWKAR;
	template <peripheral per> typename rtc_t<per>::bcnt3ar_t rtc_t<per>::BCNT3AR;
	template <peripheral per> typename rtc_t<per>::rdayar_t rtc_t<per>::RDAYAR;
	template <peripheral per> typename rtc_t<per>::bcnt0aer_t rtc_t<per>::BCNT0AER;
	template <peripheral per> typename rtc_t<per>::rmonar_t rtc_t<per>::RMONAR;
	template <peripheral per> typename rtc_t<per>::bcnt1aer_t rtc_t<per>::BCNT1AER;
	template <peripheral per> typename rtc_t<per>::ryrar_t rtc_t<per>::RYRAR;
	template <peripheral per> typename rtc_t<per>::bcnt2aer_t rtc_t<per>::BCNT2AER;
	template <peripheral per> typename rtc_t<per>::ryraren_t rtc_t<per>::RYRAREN;
	template <peripheral per> typename rtc_t<per>::bcnt3aer_t rtc_t<per>::BCNT3AER;
	template <peripheral per> typename rtc_t<per>::rcr1_t rtc_t<per>::RCR1;
	template <peripheral per> typename rtc_t<per>::rcr2_t rtc_t<per>::RCR2;
	template <peripheral per> typename rtc_t<per>::rcr3_t rtc_t<per>::RCR3;
	template <peripheral per> typename rtc_t<per>::rcr4_t rtc_t<per>::RCR4;
	template <peripheral per> typename rtc_t<per>::rfrh_t rtc_t<per>::RFRH;
	template <peripheral per> typename rtc_t<per>::rfrl_t rtc_t<per>::RFRL;
	template <peripheral per> typename rtc_t<per>::radj_t rtc_t<per>::RADJ;
	template <peripheral per> typename rtc_t<per>::rtccr0_t rtc_t<per>::RTCCR0;
	template <peripheral per> typename rtc_t<per>::rtccr1_t rtc_t<per>::RTCCR1;
	template <peripheral per> typename rtc_t<per>::rtccr2_t rtc_t<per>::RTCCR2;
	template <peripheral per> typename rtc_t<per>::rseccpy0_t rtc_t<per>::RSECCPY0;
	template <peripheral per> typename rtc_t<per>::rseccpy1_t rtc_t<per>::RSECCPY1;
	template <peripheral per> typename rtc_t<per>::rseccpy2_t rtc_t<per>::RSECCPY2;
	template <peripheral per> typename rtc_t<per>::bcnt0cp0_t rtc_t<per>::BCNT0CP0;
	template <peripheral per> typename rtc_t<per>::bcnt0cp1_t rtc_t<per>::BCNT0CP1;
	template <peripheral per> typename rtc_t<per>::bcnt0cp2_t rtc_t<per>::BCNT0CP2;
	template <peripheral per> typename rtc_t<per>::rmincp0_t rtc_t<per>::RMINCP0;
	template <peripheral per> typename rtc_t<per>::rmincp1_t rtc_t<per>::RMINCP1;
	template <peripheral per> typename rtc_t<per>::rmincp2_t rtc_t<per>::RMINCP2;
	template <peripheral per> typename rtc_t<per>::bcnt1cp0_t rtc_t<per>::BCNT1CP0;
	template <peripheral per> typename rtc_t<per>::bcnt1cp1_t rtc_t<per>::BCNT1CP1;
	template <peripheral per> typename rtc_t<per>::bcnt1cp2_t rtc_t<per>::BCNT1CP2;
	template <peripheral per> typename rtc_t<per>::rhrcp0_t rtc_t<per>::RHRCP0;
	template <peripheral per> typename rtc_t<per>::rhrcp1_t rtc_t<per>::RHRCP1;
	template <peripheral per> typename rtc_t<per>::rhrcp2_t rtc_t<per>::RHRCP2;
	template <peripheral per> typename rtc_t<per>::bcnt2cp0_t rtc_t<per>::BCNT2CP0;
	template <peripheral per> typename rtc_t<per>::bcnt2cp1_t rtc_t<per>::BCNT2CP1;
	template <peripheral per> typename rtc_t<per>::bcnt2cp2_t rtc_t<per>::BCNT2CP2;
	template <peripheral per> typename rtc_t<per>::rdaycp0_t rtc_t<per>::RDAYCP0;
	template <peripheral per> typename rtc_t<per>::rdaycp1_t rtc_t<per>::RDAYCP1;
	template <peripheral per> typename rtc_t<per>::rdaycp2_t rtc_t<per>::RDAYCP2;
	template <peripheral per> typename rtc_t<per>::bcnt3cp0_t rtc_t<per>::BCNT3CP0;
	template <peripheral per> typename rtc_t<per>::bcnt3cp1_t rtc_t<per>::BCNT3CP1;
	template <peripheral per> typename rtc_t<per>::bcnt3cp2_t rtc_t<per>::BCNT3CP2;
	template <peripheral per> typename rtc_t<per>::rmoncp0_t rtc_t<per>::RMONCP0;
	template <peripheral per> typename rtc_t<per>::rmoncp1_t rtc_t<per>::RMONCP1;
	template <peripheral per> typename rtc_t<per>::rmoncp2_t rtc_t<per>::RMONCP2;
}
