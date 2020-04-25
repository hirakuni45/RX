#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・RTC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2020 Kunihito Hiramatsu @n
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

		static const auto PERIPHERAL = per;	///< ペリフェラル型

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
		typedef r64cnt_t<0x0008C400> R64CNT_;
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
		typedef rseccnt_t<0x0008C402> RSECCNT_;
		static  RSECCNT_ RSECCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0（BCNT0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C402> BCNT0_;
		static  BCNT0_ BCNT0;


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
		typedef rmincnt_t<0x0008C404> RMINCNT_;
		static  RMINCNT_ RMINCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1（BCNT1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C404> BCNT1_;
		static  BCNT1_ BCNT1;


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
			bit_rw_t <io_, bitpos::B6>     PM;
		};
		typedef rhrcnt_t<0x0008C406> RHRCNT_;
		static  RHRCNT_ RHRCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2（BCNT2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C406> BCNT2_;
		static  BCNT2_ BCNT2;


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

			bits_rw_t<io_, bitpos::B0, 2>  DAYW;
		};
		typedef rwkcnt_t<0x0008C408> RWKCNT_;
		static  RWKCNT_ RWKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3（BCNT3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C408> BCNT3_;
		static  BCNT3_ BCNT3;


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
		typedef rdaycnt_t<0x0008C40A> RDAYCNT_;
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
		typedef rmoncnt_t<0x0008C40C> RMONCNT_;
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

			bits_rw_t<io_, bitpos::B0, 4> YR1;
			bits_rw_t<io_, bitpos::B4, 4> YR10;
		};
		typedef ryrcnt_t<0x0008C40E> RYRCNT_;
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
		typedef rsecar_t<0x0008C410> RSECAR_;
		static  RSECAR_ RSECAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラームレジスタ（BCNT0AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C410> BCNT0AR_;
		static  BCNT0AR_ BCNT0AR;


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
		typedef rminar_t<0x0008C412> RMINAR_;
		static  RMINAR_ RMINAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラームレジスタ（BCNT1AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C412> BCNT1AR_;
		static  BCNT1AR_ BCNT1AR;


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
			bit_rw_t <io_, bitpos::B6>    PM;
			bit_rw_t <io_, bitpos::B7>    ENB;
		};
		typedef rhrar_t<0x0008C414> RHRAR_;
		static  RHRAR_ RHRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラームレジスタ（BCNT2AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C414> BCNT2AR_;
		static  BCNT2AR_ BCNT2AR;


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
		typedef rwkar_t<0x0008C416> RWKAR_;
		static  RWKAR_ RWKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラームレジスタ（BCNT3AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C416> BCNT3AR_;
		static  BCNT3AR_ BCNT3AR;


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
		typedef rdayar_t<0x0008C418> RDAYAR_;
		static  RDAYAR_ RDAYAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラーム許可レジスタ（BCNT0AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C418> BCNT0AER_;
		static  BCNT0AER_ BCNT0AER;


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
		typedef rmonar_t<0x0008C41A> RMONAR_;
		static  RMONAR_ RMONAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラーム許可レジスタ（BCNT1AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C41A> BCNT1AER_;
		static  BCNT1AER_ BCNT1AER;


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

			bits_rw_t<io_, bitpos::B0, 4> YR1;
			bits_rw_t<io_, bitpos::B4, 4> YR10;
		};
		typedef ryrar_t<0x0008C41C> RYRAR_;
		static  RYRAR_ RYRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラーム許可レジスタ（BCNT2AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C41C> BCNT2AER_;
		static  BCNT2AER_ BCNT2AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  年アラーム許可レジスタ（RYRAREN）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ryraren_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  ENB;
		};
		typedef ryraren_t<0x0008C41E> RYRAREN_;
		static  RYRAREN_ RYRAREN;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラーム許可レジスタ（BCNT3AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C41E> BCNT3AER_;
		static  BCNT3AER_ BCNT3AER;


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
			bit_rw_t <io_, bitpos::B3>	  RTCOS;
			bits_rw_t<io_, bitpos::B4, 4> PES;
		};
		typedef rcr1_t<0x0008C422> RCR1_;
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
			bit_rw_t<io_, bitpos::B2>  ADJ30;
			bit_rw_t<io_, bitpos::B3>  RTCOE;
			bit_rw_t<io_, bitpos::B4>  AADJE;
			bit_rw_t<io_, bitpos::B5>  AADJP;
			bit_rw_t<io_, bitpos::B6>  HR24;
			bit_rw_t<io_, bitpos::B7>  CNTMD;
		};
		typedef rcr2_t<0x0008C424> RCR2_;
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

			bit_rw_t <io_, bitpos::B0>	  RTCEN;
			bits_rw_t<io_, bitpos::B1, 3> RTCDV;
		};
		typedef rcr3_t<0x0008C426> RCR3_;
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

			bit_rw_t <io_, bitpos::B0>	  RCKSEL;
		};
		typedef rcr4_t<0x0008C428> RCR4_;
		static  RCR4_ RCR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ H（RFRH）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008C42A> RFRH_;
		static  RFRH_ RFRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ L（RFRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008C42C> RFRL_;
		static  RFRL_ RFRL;


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

			bits_rw_t<io_, bitpos::B0, 5> ADJ;
			bits_rw_t<io_, bitpos::B6, 2> PMADJ;
		};
		typedef radj_t<0x0008C42E> RADJ_;
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

			bits_rw_t<io_, bitpos::B0, 2> TCCT;
			bit_rw_t <io_, bitpos::B2>    TCST;
			bits_rw_t<io_, bitpos::B4, 2> TCNF;
			bit_rw_t <io_, bitpos::B7>    TCEN;
		};
		typedef rtccr_t<0x0008C440> RTCCR0_;
		static  RTCCR0_ RTCCR0;
		typedef rtccr_t<0x0008C442> RTCCR1_;
		static  RTCCR1_ RTCCR1;
		typedef rtccr_t<0x0008C444> RTCCR2_;
		static  RTCCR2_ RTCCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  秒キャプチャレジスタ y（RSECCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rseccpy_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> SEC1;
			bits_rw_t<io_, bitpos::B4, 3> SEC10;
		};
		typedef rseccpy_t<0x0008C452> RSECCPY0_;
		static  RSECCPY0_ RSECCPY0;
		typedef rseccpy_t<0x0008C462> RSECCPY1_;
		static  RSECCPY1_ RSECCPY1;
		typedef rseccpy_t<0x0008C472> RSECCPY2_;
		static  RSECCPY2_ RSECCPY2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 0（BCNT0CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C452> BCNT0CP0_;
		static  BCNT0CP0_ BCNT0CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 1（BCNT0CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C462> BCNT0CP1_;
		static  BCNT0CP1_ BCNT0CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 2（BCNT0CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C472> BCNT0CP2_;
		static  BCNT0CP2_ BCNT0CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  分キャプチャレジスタ y（RMINCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmincpy_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MIN1;
			bits_rw_t<io_, bitpos::B4, 3> MIN10;
		};
		typedef rmincpy_t<0x0008C454> RMINCP0_;
		static  RMINCP0_ RMINCP0;
		typedef rmincpy_t<0x0008C464> RMINCP1_;
		static  RMINCP1_ RMINCP1;
		typedef rmincpy_t<0x0008C474> RMINCP2_;
		static  RMINCP2_ RMINCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 0（BCNT1CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C454> BCNT1CP0_;
		static  BCNT1CP0_ BCNT1CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 1（BCNT1CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C464> BCNT1CP1_;
		static  BCNT1CP1_ BCNT1CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 2（BCNT1CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C474> BCNT1CP2_;
		static  BCNT1CP2_ BCNT1CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  時キャプチャレジスタ y（RHRCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rhrcpy_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> HR1;
			bits_rw_t<io_, bitpos::B4, 2> HR10;
			bit_rw_t <io_, bitpos::B6>    PM;
		};
		typedef rhrcpy_t<0x0008C456> RHRCP0_;
		static  RHRCP0_ RHRCP0;
		typedef rhrcpy_t<0x0008C466> RHRCP1_;
		static  RHRCP1_ RHRCP1;
		typedef rhrcpy_t<0x0008C476> RHRCP2_;
		static  RHRCP2_ RHRCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 0（BCNT2CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C456> BCNT2CP0_;
		static  BCNT2CP0_ BCNT2CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 1（BCNT2CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C466> BCNT2CP1_;
		static  BCNT2CP1_ BCNT2CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 2（BCNT2CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C476> BCNT2CP2_;
		static  BCNT2CP2_ BCNT2CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  日キャプチャレジスタ y（RDAYCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rdaycpy_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> DATE1;
			bits_rw_t<io_, bitpos::B4, 2> DATE10;
		};
		typedef rdaycpy_t<0x0008C45A> RDAYCP0_;
		static  RDAYCP0_ RDAYCP0;
		typedef rdaycpy_t<0x0008C46A> RDAYCP1_;
		static  RDAYCP1_ RDAYCP1;
		typedef rdaycpy_t<0x0008C47A> RDAYCP2_;
		static  RDAYCP2_ RDAYCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 0（BCNT3CP0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C45A> BCNT3CP0_;
		static  BCNT3CP0_ BCNT3CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 1（BCNT3CP1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C46A> BCNT3CP1_;
		static  BCNT3CP1_ BCNT3CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 2（BCNT3CP2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008C47A> BCNT3CP2_;
		static  BCNT3CP2_ BCNT3CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  月キャプチャレジスタ y（RMONCPy）（y=0 ～ 2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rmoncpy_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MON1;
			bit_rw_t <io_, bitpos::B4>    MON10;
		};
		typedef rmoncpy_t<0x0008C45C> RMONCP0_;
		static  RMONCP0_ RMONCP0;
		typedef rmoncpy_t<0x0008C46C> RMONCP1_;
		static  RMONCP1_ RMONCP1;
		typedef rmoncpy_t<0x0008C47C> RMONCP2_;
		static  RMONCP2_ RMONCP2;
	};
	template <peripheral per> typename rtc_t<per>::R64CNT_ rtc_t<per>::R64CNT;
	template <peripheral per> typename rtc_t<per>::RSECCNT_ rtc_t<per>::RSECCNT;
	template <peripheral per> typename rtc_t<per>::BCNT0_ rtc_t<per>::BCNT0;
	template <peripheral per> typename rtc_t<per>::RMINCNT_ rtc_t<per>::RMINCNT;
	template <peripheral per> typename rtc_t<per>::BCNT1_ rtc_t<per>::BCNT1;
	template <peripheral per> typename rtc_t<per>::RHRCNT_ rtc_t<per>::RHRCNT;
	template <peripheral per> typename rtc_t<per>::BCNT2_ rtc_t<per>::BCNT2;
	template <peripheral per> typename rtc_t<per>::RWKCNT_ rtc_t<per>::RWKCNT;
	template <peripheral per> typename rtc_t<per>::BCNT3_ rtc_t<per>::BCNT3;
	template <peripheral per> typename rtc_t<per>::RDAYCNT_ rtc_t<per>::RDAYCNT;
	template <peripheral per> typename rtc_t<per>::RMONCNT_ rtc_t<per>::RMONCNT;
	template <peripheral per> typename rtc_t<per>::RYRCNT_ rtc_t<per>::RYRCNT;
	template <peripheral per> typename rtc_t<per>::RSECAR_ rtc_t<per>::RSECAR;
	template <peripheral per> typename rtc_t<per>::BCNT0AR_ rtc_t<per>::BCNT0AR;
	template <peripheral per> typename rtc_t<per>::RMINAR_ rtc_t<per>::RMINAR;
	template <peripheral per> typename rtc_t<per>::BCNT1AR_ rtc_t<per>::BCNT1AR;
	template <peripheral per> typename rtc_t<per>::RHRAR_ rtc_t<per>::RHRAR;
	template <peripheral per> typename rtc_t<per>::BCNT2AR_ rtc_t<per>::BCNT2AR;
	template <peripheral per> typename rtc_t<per>::RWKAR_ rtc_t<per>::RWKAR;
	template <peripheral per> typename rtc_t<per>::BCNT3AR_ rtc_t<per>::BCNT3AR;
	template <peripheral per> typename rtc_t<per>::RDAYAR_ rtc_t<per>::RDAYAR;
	template <peripheral per> typename rtc_t<per>::BCNT0AER_ rtc_t<per>::BCNT0AER;
	template <peripheral per> typename rtc_t<per>::RMONAR_ rtc_t<per>::RMONAR;
	template <peripheral per> typename rtc_t<per>::BCNT1AER_ rtc_t<per>::BCNT1AER;
	template <peripheral per> typename rtc_t<per>::RYRAR_ rtc_t<per>::RYRAR;
	template <peripheral per> typename rtc_t<per>::BCNT2AER_ rtc_t<per>::BCNT2AER;
	template <peripheral per> typename rtc_t<per>::RYRAREN_ rtc_t<per>::RYRAREN;
	template <peripheral per> typename rtc_t<per>::BCNT3AER_ rtc_t<per>::BCNT3AER;
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
	template <peripheral per> typename rtc_t<per>::RSECCPY0_ rtc_t<per>::RSECCPY0;
	template <peripheral per> typename rtc_t<per>::RSECCPY1_ rtc_t<per>::RSECCPY1;
	template <peripheral per> typename rtc_t<per>::RSECCPY2_ rtc_t<per>::RSECCPY2;
	template <peripheral per> typename rtc_t<per>::BCNT0CP0_ rtc_t<per>::BCNT0CP0;
	template <peripheral per> typename rtc_t<per>::BCNT0CP1_ rtc_t<per>::BCNT0CP1;
	template <peripheral per> typename rtc_t<per>::BCNT0CP2_ rtc_t<per>::BCNT0CP2;
	template <peripheral per> typename rtc_t<per>::RMINCP0_ rtc_t<per>::RMINCP0;
	template <peripheral per> typename rtc_t<per>::RMINCP1_ rtc_t<per>::RMINCP1;
	template <peripheral per> typename rtc_t<per>::RMINCP2_ rtc_t<per>::RMINCP2;
	template <peripheral per> typename rtc_t<per>::BCNT1CP0_ rtc_t<per>::BCNT1CP0;
	template <peripheral per> typename rtc_t<per>::BCNT1CP1_ rtc_t<per>::BCNT1CP1;
	template <peripheral per> typename rtc_t<per>::BCNT1CP2_ rtc_t<per>::BCNT1CP2;
	template <peripheral per> typename rtc_t<per>::RHRCP0_ rtc_t<per>::RHRCP0;
	template <peripheral per> typename rtc_t<per>::RHRCP1_ rtc_t<per>::RHRCP1;
	template <peripheral per> typename rtc_t<per>::RHRCP2_ rtc_t<per>::RHRCP2;
	template <peripheral per> typename rtc_t<per>::BCNT2CP0_ rtc_t<per>::BCNT2CP0;
	template <peripheral per> typename rtc_t<per>::BCNT2CP1_ rtc_t<per>::BCNT2CP1;
	template <peripheral per> typename rtc_t<per>::BCNT2CP2_ rtc_t<per>::BCNT2CP2;
	template <peripheral per> typename rtc_t<per>::RDAYCP0_ rtc_t<per>::RDAYCP0;
	template <peripheral per> typename rtc_t<per>::RDAYCP1_ rtc_t<per>::RDAYCP1;
	template <peripheral per> typename rtc_t<per>::RDAYCP2_ rtc_t<per>::RDAYCP2;
	template <peripheral per> typename rtc_t<per>::BCNT3CP0_ rtc_t<per>::BCNT3CP0;
	template <peripheral per> typename rtc_t<per>::BCNT3CP1_ rtc_t<per>::BCNT3CP1;
	template <peripheral per> typename rtc_t<per>::BCNT3CP2_ rtc_t<per>::BCNT3CP2;
	template <peripheral per> typename rtc_t<per>::RMONCP0_ rtc_t<per>::RMONCP0;
	template <peripheral per> typename rtc_t<per>::RMONCP1_ rtc_t<per>::RMONCP1;
	template <peripheral per> typename rtc_t<per>::RMONCP2_ rtc_t<per>::RMONCP2;


	typedef rtc_t<peripheral::RTC> RTC;
}
