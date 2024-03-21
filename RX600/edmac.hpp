#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・イーサネットコントローラ用 DMA コントローラ (EDMACa, PTPEDMAC) @n
			RX62N @n
			RX63N @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac core 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct edmac_core_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC モードレジスタ（EDMR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SWR;

			bits_rw_t<io_, bitpos::B4, 2> DL;
			bit_rw_t<io_, bitpos::B6> DE;

		};
		static inline edmr_t<base + 0x00> EDMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC 送信要求レジスタ（EDTRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edtrr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TR;

		};
		static inline edtrr_t<base + 0x08> EDTRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC 受信要求レジスタ（EDRRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edrrr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RR;
		};
		static inline edrrr_t<base + 0x10> EDRRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信ディスクリプタリスト先頭アドレスレジスタ（TDLAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x18> TDLAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信ディスクリプタリスト先頭アドレスレジスタ（RDLAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x20> RDLAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ミスドフレームカウンタレジスタ（RMFCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rmfcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> MFC;
		};
		static inline rmfcr_t<base + 0x40> RMFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信 FIFO しきい値指定レジスタ（TFTR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tftr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> TFT;
		};
		static inline tftr_t<base + 0x48> TFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FIFO 容量指定レジスタ（FDR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fdr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> RFD;
			bits_rw_t<io_, bitpos::B8, 5> TFD;
		};
		static inline fdr_t<base + 0x50> FDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信方式制御レジスタ（RMCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rmcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RNR;
		};
		static inline rmcr_t<base + 0x58> RMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信 FIFO アンダフローカウント（TFUCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tfucr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> UNDER;
		};
		static inline tfucr_t<base + 0x64> TFUCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信 FIFO オーバフローカウント（RFOCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rfocr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> OVER;
		};
		static inline rfocr_t<base + 0x68> RFOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フロー制御開始 FIFO しきい値設定レジスタ（FCFTR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fcftr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  RFDO;

			bits_rw_t<io_, bitpos::B16, 3> RFFO;
		};
		static inline fcftr_t<base + 0x70> FCFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信データパディング挿入設定レジスタ（RPADIR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rpadir_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  PADR;

			bits_rw_t<io_, bitpos::B16, 2> PADS;
		};
		static inline rpadir_t<base + 0x78> RPADIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信割り込み設定レジスタ（TRIMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct trimd_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TIS;

			bit_rw_t<io_, bitpos::B4> TIM;
		};
		static inline trimd_t<base + 0x7C> TRIMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信バッファライトアドレスレジスタ（RBWAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xC8> RBWAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信ディスクリプタフェッチアドレスレジスタ（RDFAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xCC> RDFAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信バッファリードアドレスレジスタ（TBRAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xD4> TBRAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信ディスクリプタフェッチアドレスレジスタ（TDFAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xD8> TDFAR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	IT		割り込み型
		@param[in]	eint	割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename IT, IT eint>
	struct edmac_t : public edmac_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto EINT = eint;			///< 割り込みベクタ

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC ステータスレジスタ（EDMACn.EESR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CERF;
			bit_rw_t<io_, bitpos::B1>  PRE;
			bit_rw_t<io_, bitpos::B2>  RTSF;
			bit_rw_t<io_, bitpos::B3>  RTLF;
			bit_rw_t<io_, bitpos::B4>  RRF;

			bit_rw_t<io_, bitpos::B7>  RMAF;
			bit_rw_t<io_, bitpos::B8>  TRO;
			bit_rw_t<io_, bitpos::B9>  CD;
			bit_rw_t<io_, bitpos::B10> DLC;
			bit_rw_t<io_, bitpos::B11> CND;

			bit_rw_t<io_, bitpos::B16> RFOF;
			bit_rw_t<io_, bitpos::B17> RDE;
			bit_rw_t<io_, bitpos::B18> FR;
			bit_rw_t<io_, bitpos::B19> TFUF;
			bit_rw_t<io_, bitpos::B20> TDE;
			bit_rw_t<io_, bitpos::B21> TC;
			bit_rw_t<io_, bitpos::B22> ECI;
			bit_rw_t<io_, bitpos::B23> ADE;
			bit_rw_t<io_, bitpos::B24> RFCOF;
			bit_rw_t<io_, bitpos::B25> RABT;
			bit_rw_t<io_, bitpos::B26> TABT;

			bit_rw_t<io_, bitpos::B30> TWB;
		};
		static inline eesr_t<base + 0x28> EESR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC ステータス割り込み許可レジスタ（EDMACn.EESIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesipr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CERFIP;
			bit_rw_t<io_, bitpos::B1>  PREIP;
			bit_rw_t<io_, bitpos::B2>  RTSFIP;
			bit_rw_t<io_, bitpos::B3>  RTLFIP;
			bit_rw_t<io_, bitpos::B4>  RRFIP;

			bit_rw_t<io_, bitpos::B7>  RMAFIP;
			bit_rw_t<io_, bitpos::B8>  TROIP;
			bit_rw_t<io_, bitpos::B9>  CDIP;
			bit_rw_t<io_, bitpos::B10> DLCIP;
			bit_rw_t<io_, bitpos::B11> CNDIP;

			bit_rw_t<io_, bitpos::B16> RFOFIP;
			bit_rw_t<io_, bitpos::B17> RDEIP;
			bit_rw_t<io_, bitpos::B18> FRIP;
			bit_rw_t<io_, bitpos::B19> TFUFIP;
			bit_rw_t<io_, bitpos::B20> TDEIP;
			bit_rw_t<io_, bitpos::B21> TCIP;
			bit_rw_t<io_, bitpos::B22> ECIIP;
			bit_rw_t<io_, bitpos::B23> ADEIP;
			bit_rw_t<io_, bitpos::B24> RFCOFIP;
			bit_rw_t<io_, bitpos::B25> RABTIP;
			bit_rw_t<io_, bitpos::B26> TABTIP;

			bit_rw_t<io_, bitpos::B30> TWBIP;
		};
		static inline eesipr_t<base + 0x30> EESIPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC 送受信ステータスコピー指示レジスタ（EDMACn.TRSCER）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct trscer_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>  PRFCE;

			bit_rw_t<io_, bitpos::B7>  RMAFCE;
		};
		static inline trscer_t<base + 0x38> TRSCER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  個別出力信号設定レジスタ（IOSR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iosr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ELB;
		};
		static inline iosr_t<base + 0x6C> IOSR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ptpedmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct ptpedmac_t : public edmac_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PTP/EDMAC ステータスレジスタ（PTPEDMAC.EESR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> TYPE;
			bit_rw_t<io_, bitpos::B4>     PVER;

			bit_rw_t<io_, bitpos::B7>     RPORT;
			bit_rw_t<io_, bitpos::B8>     MACE;

			bit_rw_t<io_, bitpos::B16>    RFOF;
			bit_rw_t<io_, bitpos::B17>    RDE;
			bit_rw_t<io_, bitpos::B18>    FR;
			bit_rw_t<io_, bitpos::B19>    TFUF;
			bit_rw_t<io_, bitpos::B20>    TDE;
			bit_rw_t<io_, bitpos::B21>    TC;

			bit_rw_t<io_, bitpos::B23>    ADE;
			bit_rw_t<io_, bitpos::B24>    RFCOF;

			bit_rw_t<io_, bitpos::B26>    TABT;

			bit_rw_t<io_, bitpos::B30>    TWB;
		};
		static inline eesr_t<base + 0x28> EESR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PTP/EDMAC ステータス割り込み許可レジスタ（PTPEDMAC.EESIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesipr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>  PVERIP;

			bit_rw_t<io_, bitpos::B7>   RPORTIP;
			bit_rw_t<io_, bitpos::B8>   MACEIP;

			bit_rw_t<io_, bitpos::B16>  RFOFIP;
			bit_rw_t<io_, bitpos::B17>  RDEIP;
			bit_rw_t<io_, bitpos::B18>  FRIP;
			bit_rw_t<io_, bitpos::B19>  TFUFIP;
			bit_rw_t<io_, bitpos::B20>  TDEIP;
			bit_rw_t<io_, bitpos::B21>  TCIP;

			bit_rw_t<io_, bitpos::B23>  ADEIP;
			bit_rw_t<io_, bitpos::B24>  RFCOFIP;

			bit_rw_t<io_, bitpos::B26>  TABTIP;

			bit_rw_t<io_, bitpos::B30>  TWBIP;
		};
		static inline eesipr_t<base + 0x30> EESIPR;
	};

#if defined(SIG_RX62N) || defined(SIG_RX63N)
	typedef edmac_t<0x000C'0000, peripheral::EDMAC, ICU::VECTOR, ICU::VECTOR::EINT> EDMAC;
#elif defined(SIG_RX621) || defined(SIG_RX631)
#else
	typedef edmac_t<0x000C'0000, peripheral::EDMAC0, ICU::GROUPAL1, ICU::GROUPAL1::EINT0> EDMAC0;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef edmac_t<0x000C'0200, peripheral::EDMAC1, ICU::GROUPAL1, ICU::GROUPAL1::EINT1> EDMAC1;
	typedef ptpedmac_t<0x000C'0400, peripheral::PTPEDMAC> PTPEDMAC;
#endif
}
