#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・RTCc 定義
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
		@brief  RTCc 定義基底クラス
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
			@brief  バイナリカウンタ 0（BCNT0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C402> BCNT0_;
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
		typedef rmincnt_t<0x0008'C404> RMINCNT_;
		static  RMINCNT_ RMINCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1（BCNT1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C404> BCNT1_;
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
		typedef rhrcnt_t<0x0008'C406> RHRCNT_;
		static  RHRCNT_ RHRCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2（BCNT2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C406> BCNT2_;
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
		typedef rwkcnt_t<0x0008'C408> RWKCNT_;
		static  RWKCNT_ RWKCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3（BCNT3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C408> BCNT3_;
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

			bits_rw_t<io_, bitpos::B0, 4> YR1;
			bits_rw_t<io_, bitpos::B4, 4> YR10;
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
			@brief  バイナリカウンタ 0 アラームレジスタ（BCNT0AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C410> BCNT0AR_;
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
		typedef rminar_t<0x0008'C412> RMINAR_;
		static  RMINAR_ RMINAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラームレジスタ（BCNT1AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C412> BCNT1AR_;
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
		typedef rhrar_t<0x0008'C414> RHRAR_;
		static  RHRAR_ RHRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラームレジスタ（BCNT2AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C414> BCNT2AR_;
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
		typedef rwkar_t<0x0008'C416> RWKAR_;
		static  RWKAR_ RWKAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 3 アラームレジスタ（BCNT3AR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C416> BCNT3AR_;
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
		typedef rdayar_t<0x0008'C418> RDAYAR_;
		static  RDAYAR_ RDAYAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 0 アラーム許可レジスタ（BCNT0AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C418> BCNT0AER_;
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
		typedef rmonar_t<0x0008'C41A> RMONAR_;
		static  RMONAR_ RMONAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 1 アラーム許可レジスタ（BCNT1AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C41A> BCNT1AER_;
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
		typedef ryrar_t<0x0008'C41C> RYRAR_;
		static  RYRAR_ RYRAR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バイナリカウンタ 2 アラーム許可レジスタ（BCNT2AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'C41C> BCNT2AER_;
		static  BCNT2AER_ BCNT2AER;


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
			@brief  バイナリカウンタ 3 アラーム許可レジスタ（BCNT3AER）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x0008'C41E> BCNT3AER_;
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
			bit_rw_t<io_, bitpos::B2>  ADJ30;
			bit_rw_t<io_, bitpos::B3>  RTCOE;
			bit_rw_t<io_, bitpos::B4>  AADJE;
			bit_rw_t<io_, bitpos::B5>  AADJP;
			bit_rw_t<io_, bitpos::B6>  HR24;
			bit_rw_t<io_, bitpos::B7>  CNTMD;
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

			bit_rw_t <io_, bitpos::B0>	  RTCEN;
			bits_rw_t<io_, bitpos::B1, 3> RTCDV;
		};
		typedef rcr3_t<0x0008'C426> RCR3_;
		static  RCR3_ RCR3;


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
		typedef radj_t<0x0008'C42E> RADJ_;
		static  RADJ_ RADJ;
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
	template <peripheral per> typename rtc_t<per>::RADJ_ rtc_t<per>::RADJ;

	typedef rtc_t<peripheral::RTC> RTC;
}
