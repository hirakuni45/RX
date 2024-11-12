#pragma once
//=========================================================================//
/*!	@file
	@brief	リモコン信号受信機能 (REMC/REMCa) @n
			RX130 @n
			RX260/RX261 @n
			RX660 @n
			RX671
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
		@brief  リモコン信号受信機能ベース・クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct remc_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  機能選択レジスタ 0 (REMCON0)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remcon0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CFME;
		};
		static inline remcon0_t<base + 0x00> REMCON0;


		//-----------------------------------------------------------------//
		/*!
			@brief  機能選択レジスタ 1 (REMCON1)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remcon1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TYP;
			bit_rw_t <io_, bitpos::B2>     EN;
			bits_rw_t<io_, bitpos::B3, 4>  CSRC;
			bit_rw_t <io_, bitpos::B7>     INTMD;
		};
		static inline remcon1_t<base + 0x01> REMCON1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ (REMSTS)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remsts_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline remsts_t<base + 0x02> REMSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み制御レジスタ (REMINT)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remint_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline remint_t<base + 0x03> REMINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペア制御レジスタ (REMCPC)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remcpc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CPN;
		};
		static inline remcpc_t<base + 0x05> REMCPC;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペア値設定レジスタ (REMCPD)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remcpd_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> CPD;
		};
		static inline remcpd_t<base + 0x06> REMCPD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ヘッダパターン最小幅設定レジスタ (HDPMIN)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct hdpmin_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> HDPMIN;
		};
		static inline hdpmin_t<base + 0x08> HDPMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  ヘッダパターン最大幅設定レジスタ (HDPMAX)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct hdpmax_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> HDPMAX;
		};
		static inline hdpmax_t<base + 0x0A> HDPMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “0” パターン最小幅設定レジスタ (D0PMIN)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct d0pmin_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D0PMIN;
		};
		static inline d0pmin_t<base + 0x0C> D0PMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “0” パターン最大幅設定レジスタ (D0PMAX)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct d0pmax_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D0PMAX;
		};
		static inline d0pmax_t<base + 0x0D> D0PMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “1” パターン最小幅設定レジスタ (D1PMIN)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct d1pmin_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D1PMIN;
		};
		static inline d1pmin_t<base + 0x0E> D1PMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ “1” パターン最大幅設定レジスタ (D1PMAX)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct d1pmax_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> D1PMAX;
		};
		static inline d1pmax_t<base + 0x0F> D1PMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  特殊データパターン最小幅設定レジスタ (SDPMIN)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdpmin_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> SDPMIN;
		};
		static inline sdpmin_t<base + 0x10> SDPMIN;


		//-----------------------------------------------------------------//
		/*!
			@brief  特殊データパターン最大幅設定レジスタ (SDPMAX)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sdpmax_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> SDPMAX;
		};
		static inline sdpmax_t<base + 0x12> SDPMAX;


		//-----------------------------------------------------------------//
		/*!
			@brief  パターンエンド設定レジスタ (REMPE)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rempe_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> PE;
		};
		static inline rempe_t<base + 0x14> REMPE;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信ビット数レジスタ (REMRBIT)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remrbit_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    RBIT0;
			bits_rw_t<io_, bitpos::B1, 6> RBIT;
		};
		static inline remrbit_t<base + 0x17> REMRBIT;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信データ 0 レジスタ (REMDAT0)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remdat0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    DAT00;
			bits_rw_t<io_, bitpos::B1, 6> DAT0;
		};
		static inline remdat0_t<base + 0x18> REMDAT0;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信データ j レジスタ (REMDATj) (j = 1 ～ 7)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remdatn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> DAT;
		};
		static inline remdatn_t<base + 0x19> REMDAT1;
		static inline remdatn_t<base + 0x1A> REMDAT2;
		static inline remdatn_t<base + 0x1B> REMDAT3;
		static inline remdatn_t<base + 0x1C> REMDAT4;
		static inline remdatn_t<base + 0x1D> REMDAT5;
		static inline remdatn_t<base + 0x1E> REMDAT6;
		static inline remdatn_t<base + 0x1F> REMDAT7;


		//-----------------------------------------------------------------//
		/*!
			@brief  測定結果レジスタ (REMTIM)
			@param[in]	ofs	オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct remtim_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> TIM;
		};
		static inline remtim_t<base + 0x20> REMTIM;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  リモコン信号受信機能 (REMC) クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	remci	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR remci>
	struct remc_t : public remc_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto REMCI      = remci;	///< 割り込みベクター

		//-----------------------------------------------------------------//
		/*!
			@brief  HOCO クロック供給制御レジスタ（HOSCR）
			@param[in]	adrs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t adrs>
		struct hoscr_t : public rw8_t<adrs> {
			typedef rw8_t<adrs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  HOSE;
		};
		static inline hoscr_t<0x000A'0C00> HOSCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  リモコン信号受信機能 (REMCa) クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	remci	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR remci>
	struct remca_t : public remc_base_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto REMCI      = remci;	///< 割り込みベクター

		//-----------------------------------------------------------------//
		/*!
			@brief  リモコン信号受信端子制御レジスタ (REMPC)
			@param[in]	adrs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t adrs>
		struct rempc_t : public rw8_t<adrs> {
			typedef rw8_t<adrs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> PMC0S;
		};
		static inline rempc_t<0x000A'C29C> REMPC;
	};

#if defined(SIG_RX130)
	typedef remc_t<0x000A'0B00, peripheral::REMC0, ICU::VECTOR::REMCI1> REMC0;
	typedef remc_t<0x000A'0B80, peripheral::REMC1, ICU::VECTOR::REMCI1> REMC1;
#elif defined(SIG_RX260) || defined(SIG_RX261) || defined(SIG_RX660) || defined(SIG_RX671)
	typedef remca_t<0x000A'0B00, peripheral::REMC0, ICU::VECTOR::REMCI0> REMC0;
#endif
}
