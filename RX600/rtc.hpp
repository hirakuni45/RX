#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・RTC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RTC 定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct rtc_t {

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
		static inline r64cnt_t<0x0008'C400> R64CNT;


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
		static inline rseccnt_t<0x0008'C402> RSECCNT;


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
		static inline rmincnt_t<0x0008'C404> RMINCNT;


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
		static inline rhrcnt_t<0x0008'C406> RHRCNT;


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
		static inline rwkcnt_t<0x0008'C408> RWKCNT;


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
		static inline rdaycnt_t<0x0008'C40A> RDAYCNT;


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
		static inline rmoncnt_t<0x0008'C40C> RMONCNT;


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
		static inline ryrcnt_t<0x0008'C40E> RYRCNT;


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
		static inline rsecar_t<0x0008'C410> RSECAR;


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
		static inline rminar_t<0x0008'C412> RMINAR;


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
		static inline rhrar_t<0x0008'C414> RHRAR;


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
		static inline rwkar_t<0x0008'C416> RWKAR;


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
		static inline rdayar_t<0x0008'C418> RDAYAR;


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
		static inline rmonar_t<0x0008'C41A> RMONAR;


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
		static inline ryrar_t<0x0008'C41C> RYRAR;


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
		static inline ryraren_t<0x0008'C41E> RYRAREN;


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
		static inline rcr1_t<0x0008'C422> RCR1;


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
		static inline rcr2_t<0x0008'C424> RCR2;


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
		static inline rcr3_t<0x0008'C426> RCR3;


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
		static inline rcr4_t<0x0008'C428> RCR4;


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
		static inline radj_t<0x0008'C42E> RADJ;


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
		static inline rtccr_t<0x0008'C440> RTCCR0;
		static inline rtccr_t<0x0008'C442> RTCCR1;
		static inline rtccr_t<0x0008'C444> RTCCR2;


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
		static inline rseccpy_t<0x0008'C452> RSECCPY0;
		static inline rseccpy_t<0x0008'C462> RSECCPY1;
		static inline rseccpy_t<0x0008'C472> RSECCPY2;


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
		static inline rmincpy_t<0x0008'C454> RMINCP0;
		static inline rmincpy_t<0x0008'C464> RMINCP1;
		static inline rmincpy_t<0x0008'C474> RMINCP2;


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
		static inline rhrcpy_t<0x0008'C456> RHRCP0;
		static inline rhrcpy_t<0x0008'C466> RHRCP1;
		static inline rhrcpy_t<0x0008'C476> RHRCP2;


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
		static inline rdaycpy_t<0x0008'C45A> RDAYCP0;
		static inline rdaycpy_t<0x0008'C46A> RDAYCP1;
		static inline rdaycpy_t<0x0008'C47A> RDAYCP2;


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
		static inline rmoncpy_t<0x0008'C45C> RMONCP0;
		static inline rmoncpy_t<0x0008'C46C> RMONCP1;
		static inline rmoncpy_t<0x0008'C47C> RMONCP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0（BCNT0）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C402> BCNT0;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1（BCNT1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C404> BCNT1;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2（BCNT2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C406> BCNT2;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3（BCNT3）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C408> BCNT3;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラームレジスタ（BCNT0AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C410> BCNT0AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラームレジスタ（BCNT1AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C412> BCNT1AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラームレジスタ（BCNT2AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C414> BCNT2AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラームレジスタ（BCNT3AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C416> BCNT3AR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラーム許可レジスタ（BCNT0AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C418> BCNT0AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラーム許可レジスタ（BCNT1AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C41A> BCNT1AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラーム許可レジスタ（BCNT2AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C41C> BCNT2AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラーム許可レジスタ（BCNT3AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C41E> BCNT3AER;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 0（BCNT0CP0）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C452> BCNT0CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 1（BCNT0CP1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C462> BCNT0CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT0 キャプチャレジスタ 2（BCNT0CP2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C472> BCNT0CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 0（BCNT1CP0）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C454> BCNT1CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 1（BCNT1CP1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C464> BCNT1CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT1 キャプチャレジスタ 2（BCNT1CP2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C474> BCNT1CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 0（BCNT2CP0）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C456> BCNT2CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 1（BCNT2CP1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C466> BCNT2CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT2 キャプチャレジスタ 2（BCNT2CP2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C476> BCNT2CP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 0（BCNT3CP0）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C45A> BCNT3CP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 1（BCNT3CP1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C46A> BCNT3CP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BCNT3 キャプチャレジスタ 2（BCNT3CP2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C47A> BCNT3CP2;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RTCd 定義基底クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct rtcd_t : public rtc_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr bool BINARY = true;	///< バイナリーカウントモード

		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ H（RFRH）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'C42A> RFRH;


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数レジスタ L（RFRL）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'C42C> RFRL;

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RTCC 定義基底クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct rtcc_t : public rtc_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr bool BINARY = true;	///< バイナリーカウントモード

	};

#if defined(SIG_RX660)
	typedef rtcc_t<peripheral::RTC> RTC;
#else
	typedef rtcd_t<peripheral::RTC> RTC;
#endif
}
