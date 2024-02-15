#pragma once
//=========================================================================//
/*!	@file
	@brief	リモコン信号受信機能 (REMCa)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  リモコン信号受信機能 (REMCa) クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct remc_t {

		static constexpr auto PERIPHERAL = peripheral::REMC0;	///< ペリフェラル型
		static constexpr auto REMCI      = ICU::VECTOR::REMCI0;	///< 割り込みベクター

		//-----------------------------------------------------------------//
		/*!
			@brief  機能選択レジスタ 0 (REMCON0)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remcon0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CFME;
		};
		static inline remcon0_t<0x000A'0B00> REMCON0;


		//-----------------------------------------------------------------//
		/*!
			@brief  機能選択レジスタ 1 (REMCON1)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remcon1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TYP;
			bit_rw_t <io_, bitpos::B2>     EN;
			bits_rw_t<io_, bitpos::B3, 4>  CSRC;
			bit_rw_t <io_, bitpos::B7>     INTMD;
		};
		static inline remcon1_t<0x000A'0B01> REMCON1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ (REMSTS)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remsts_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>     CPFLG;
			bit_ro_t <io_, bitpos::B1>     REFLG;
			bit_ro_t <io_, bitpos::B2>     DRFLG;
			bit_rw_t <io_, bitpos::B3>     BFULFLG;
			bit_ro_t <io_, bitpos::B4>     HDFLG;
			bit_ro_t <io_, bitpos::B5>     D0FLG;
			bit_ro_t <io_, bitpos::B6>     D1FLG;
			bit_ro_t <io_, bitpos::B7>     D2FLG;
		};
		static inline remsts_t<0x000A'0B02> REMSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み制御レジスタ (REMINT)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remint_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPINT;
			bit_rw_t <io_, bitpos::B1>     REINT;
			bit_rw_t <io_, bitpos::B2>     DRINT;
			bit_rw_t <io_, bitpos::B3>     BFULINT;
			bit_rw_t <io_, bitpos::B4>     HDINT;
			bit_rw_t <io_, bitpos::B5>     DINT;

			bit_rw_t <io_, bitpos::B7>     SDINT;
		};
		static inline remint_t<0x000A'0B03> REMINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペア制御レジスタ (REMCPC)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remcpc_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CPN;
		};
		static inline remcpc_t<0x000A'0B05> REMCPC;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペア値設定レジスタ (REMCPD)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remcpd_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> CPD;
		};
		static inline remcpd_t<0x000A'0B06> REMCPD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ヘッダパターン最小幅設定レジスタ (HDPMIN)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hdpmin_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> HDPMIN;
		};
		static inline hdpmin_t<0x000A'0B08> HDPMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  ヘッダパターン最大幅設定レジスタ (HDPMAX)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hdpmax_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> HDPMAX;
		};
		static inline hdpmax_t<0x000A'0B0A> HDPMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “0” パターン最小幅設定レジスタ (D0PMIN)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct d0pmin_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D0PMIN;
		};
		static inline d0pmin_t<0x000A'0B0C> D0PMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “0” パターン最大幅設定レジスタ (D0PMAX)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct d0pmax_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D0PMAX;
		};
		static inline d0pmax_t<0x000A'0B0D> D0PMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “1” パターン最小幅設定レジスタ (D1PMIN)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct d1pmin_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D1PMIN;
		};
		static inline d1pmin_t<0x000A'0B0E> D1PMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “1” パターン最大幅設定レジスタ (D1PMAX)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct d1pmax_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D1PMAX;
		};
		static inline d1pmax_t<0x000A'0B0F> D1PMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  特殊データパターン最小幅設定レジスタ (SDPMIN)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sdpmin_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> SDPMIN;
		};
		static inline sdpmin_t<0x000A'0B10> SDPMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  特殊データパターン最大幅設定レジスタ (SDPMAX)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sdpmax_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> SDPMAX;
		};
		static inline sdpmax_t<0x000A'0B12> SDPMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  パターンエンド設定レジスタ (REMPE)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rempe_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> PE;
		};
		static inline rempe_t<0x000A'0B14> REMPE;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ビット数レジスタ (REMRBIT)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remrbit_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    RBIT0;
			bits_rw_t<io_, bitpos::B1, 6> RBIT;
		};
		static inline remrbit_t<0x000A'0B17> REMRBIT;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信データ 0 レジスタ (REMDAT0)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remdat0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    DAT00;
			bits_rw_t<io_, bitpos::B1, 6> DAT0;
		};
		static inline remdat0_t<0x000A'0B18> REMDAT0;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信データ j レジスタ (REMDATj) (j = 1 ～ 7)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remdatn_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> DAT;
		};
		static inline remdatn_t<0x000A'0B19> REMDAT1;
		static inline remdatn_t<0x000A'0B1A> REMDAT2;
		static inline remdatn_t<0x000A'0B1B> REMDAT3;
		static inline remdatn_t<0x000A'0B1C> REMDAT4;
		static inline remdatn_t<0x000A'0B1D> REMDAT5;
		static inline remdatn_t<0x000A'0B1E> REMDAT6;
		static inline remdatn_t<0x000A'0B1F> REMDAT7;


		//-----------------------------------------------------------------//
		/*!
			@brief  測定結果レジスタ (REMTIM)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct remtim_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> TIM;
		};
		static inline remtim_t<0x000A'0B20> REMTIM;


		//-----------------------------------------------------------------//
		/*!
			@brief  リモコン信号受信端子制御レジスタ (REMPC)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rempc_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> PMC0S;
		};
		static inline rempc_t<0x000A'C29C> REMPC;
	};
	typedef remc_t REMC0;
}
