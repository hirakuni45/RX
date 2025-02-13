#pragma once
//=========================================================================//
/*!	@file
	@brief	RX210 グループ・RTCb 定義 @n
			RX220 グループ・RTCc 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RTCb/RTCc 定義基底クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct rtc_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr bool BINARY = true;	///< バイナリーカウントモード

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0（BCNT0）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C402> BCNT0;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1（BCNT1）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C404> BCNT1;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2（BCNT2）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C406> BCNT2;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3（BCNT3）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C408> BCNT3;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラームレジスタ（BCNT0AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C410> BCNT0AR;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラームレジスタ（BCNT1AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C412> BCNT1AR;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラームレジスタ（BCNT2AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C414> BCNT2AR;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラームレジスタ（BCNT3AR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C416> BCNT3AR;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラーム許可レジスタ（BCNT0AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C418> BCNT0AER;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラーム許可レジスタ（BCNT1AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C41A> BCNT1AER;
#endif

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

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラーム許可レジスタ（BCNT2AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'C41C> BCNT2AER;
#endif

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
		static inline ryraren_t<0x0008'C41E> RYRAREN;

#if defined(SIG_RX220)
		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラーム許可レジスタ（BCNT3AER）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C41E> BCNT3AER;
#endif

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
#if defined(SIG_RX220)
			bit_rw_t<io_, bitpos::B7>  CNTMD;
#endif
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

			bits_rw_t<io_, bitpos::B0, 6> ADJ;
			bits_rw_t<io_, bitpos::B6, 2> PMADJ;
		};
		static inline radj_t<0x0008'C42E> RADJ;

#if defined(SIG_RX210)
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
		struct rseccp_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> SEC1;
			bits_rw_t<io_, bitpos::B4, 3> SEC10;
		};
		static inline rseccp_t<0x0008'C452> RSECCP0;
		static inline rseccp_t<0x0008'C462> RSECCP1;
		static inline rseccp_t<0x0008'C472> RSECCP2;


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

			bits_rw_t<io_, bitpos::B0, 4> MIN1;
			bits_rw_t<io_, bitpos::B4, 3> MIN10;
		};
		static inline rmincp_t<0x0008'C454> RMINCP0;
		static inline rmincp_t<0x0008'C464> RMINCP1;
		static inline rmincp_t<0x0008'C474> RMINCP2;


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

			bits_rw_t<io_, bitpos::B0, 4> HR1;
			bits_rw_t<io_, bitpos::B4, 2> HR10;
			bit_rw_t <io_, bitpos::B6>    PM;
		};
		static inline rhrcp_t<0x0008'C456> RHRCP0;
		static inline rhrcp_t<0x0008'C466> RHRCP1;
		static inline rhrcp_t<0x0008'C476> RHRCP2;


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

			bits_rw_t<io_, bitpos::B0, 4> DATE1;
			bits_rw_t<io_, bitpos::B4, 2> DATE10;
		};
		static inline rdaycp_t<0x0008'C45A> RDAYCP0;
		static inline rdaycp_t<0x0008'C46A> RDAYCP1;
		static inline rdaycp_t<0x0008'C47A> RDAYCP2;


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

			bits_rw_t<io_, bitpos::B0, 4> MON1;
			bit_rw_t <io_, bitpos::B4>    MON10;
		};
		static inline rmoncp_t<0x0008'C45C> RMONCP0;
		static inline rmoncp_t<0x0008'C46C> RMONCP1;
		static inline rmoncp_t<0x0008'C47C> RMONCP2;
#endif
	};
	typedef rtc_t<peripheral::RTC> RTC;
}
