#pragma once
//=====================================================================//
/*!	@file
	@brief	イーサネットコントローラ用 DMA コントローラ (EDMACa) @n
			RX64M/RX71M/RX65N/RX72M/RX72N/RX66N
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

/// EDMAC モジュールが無いデバイスでエラーとする
#if defined(SIG_RX24T) || defined(SIG_RX66T)
#  error "edmac.hpp: This module does not exist"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac core 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct edmac_core_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC モードレジスタ（EDMR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef edmr_t<base + 0x00> EDMR_;
		static  EDMR_ EDMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC 送信要求レジスタ（EDTRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edtrr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TR;

		};
		typedef edtrr_t<base + 0x08> EDTRR_;
		static  EDTRR_ EDTRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC 受信要求レジスタ（EDRRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edrrr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RR;
		};
		typedef edrrr_t<base + 0x10> EDRRR_;
		static  EDRRR_ EDRRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信ディスクリプタリスト先頭アドレスレジスタ（TDLAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> TDLAR_;
		static  TDLAR_ TDLAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信ディスクリプタリスト先頭アドレスレジスタ（RDLAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x20> RDLAR_;
		static  RDLAR_ RDLAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ミスドフレームカウンタレジスタ（RMFCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rmfcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> MFC;
		};
		typedef rmfcr_t<base + 0x40> RMFCR_;
		static  RMFCR_ RMFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信 FIFO しきい値指定レジスタ（TFTR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tftr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> TFT;
		};
		typedef tftr_t<base + 0x48> TFTR_;
		static  TFTR_ TFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FIFO 容量指定レジスタ（FDR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef fdr_t<base + 0x50> FDR_;
		static  FDR_ FDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信方式制御レジスタ（RMCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rmcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RNR;
		};
		typedef rmcr_t<base + 0x58> RMCR_;
		static  RMCR_ RMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信 FIFO アンダフローカウント（TFUCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tfucr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> UNDER;
		};
		typedef tfucr_t<base + 0x64> TFUCR_;
		static  TFUCR_ TFUCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信 FIFO オーバフローカウント（RFOCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rfocr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> OVER;
		};
		typedef rfocr_t<base + 0x68> RFOCR_;
		static  RFOCR_ RFOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フロー制御開始 FIFO しきい値設定レジスタ（FCFTR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef fcftr_t<base + 0x70> FCFTR_;
		static  FCFTR_ FCFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信データパディング挿入設定レジスタ（RPADIR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef rpadir_t<base + 0x78> RPADIR_;
		static  RPADIR_ RPADIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信割り込み設定レジスタ（TRIMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef trimd_t<base + 0x7C> TRIMD_;
		static  TRIMD_ TRIMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信バッファライトアドレスレジスタ（RBWAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xC8> RBWAR_;
		static  RBWAR_ RBWAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信ディスクリプタフェッチアドレスレジスタ（RDFAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xCC> RDFAR_;
		static  RDFAR_ RDFAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信バッファリードアドレスレジスタ（TBRAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD4> TBRAR_;
		static  TBRAR_ TBRAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信ディスクリプタフェッチアドレスレジスタ（TDFAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD8> TDFAR_;
		static  TDFAR_ TDFAR;
	};
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::EDMR_ edmac_core_t<base, per>::EDMR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::EDTRR_ edmac_core_t<base, per>::EDTRR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::EDRRR_ edmac_core_t<base, per>::EDRRR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::TDLAR_ edmac_core_t<base, per>::TDLAR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::RDLAR_ edmac_core_t<base, per>::RDLAR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::RMFCR_ edmac_core_t<base, per>::RMFCR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::TFTR_ edmac_core_t<base, per>::TFTR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::FDR_ edmac_core_t<base, per>::FDR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::RMCR_ edmac_core_t<base, per>::RMCR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::TFUCR_ edmac_core_t<base, per>::TFUCR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::RFOCR_ edmac_core_t<base, per>::RFOCR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::FCFTR_ edmac_core_t<base, per>::FCFTR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::RPADIR_ edmac_core_t<base, per>::RPADIR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::TRIMD_ edmac_core_t<base, per>::TRIMD;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::RBWAR_ edmac_core_t<base, per>::RBWAR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::RDFAR_ edmac_core_t<base, per>::RDFAR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::TBRAR_ edmac_core_t<base, per>::TBRAR;
	template <uint32_t base, peripheral per> typename edmac_core_t<base, per>::TDFAR_ edmac_core_t<base, per>::TDFAR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_AL1 eint>
	struct edmac_t : public edmac_core_t<base, per> {

		static const auto EINT = eint;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC ステータスレジスタ（EDMACn.EESR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef eesr_t<base + 0x28> EESR_;
		static  EESR_ EESR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC ステータス割り込み許可レジスタ（EDMACn.EESIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef eesipr_t<base + 0x30> EESIPR_;
		static  EESIPR_ EESIPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC 送受信ステータスコピー指示レジスタ（EDMACn.TRSCER）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef trscer_t<base + 0x38> TRSCER_;
		static  TRSCER_ TRSCER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  個別出力信号設定レジスタ（IOSR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iosr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ELB;
		};
		typedef iosr_t<base + 0x6C> IOSR_;
		static  IOSR_ IOSR;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR_AL1 eint>
		typename edmac_t<base, per, eint>::EESR_ edmac_t<base, per, eint>::EESR;
	template <uint32_t base, peripheral per, ICU::VECTOR_AL1 eint>
		typename edmac_t<base, per, eint>::EESIPR_ edmac_t<base, per, eint>::EESIPR;
	template <uint32_t base, peripheral per, ICU::VECTOR_AL1 eint>
		typename edmac_t<base, per, eint>::TRSCER_ edmac_t<base, per, eint>::TRSCER;
	template <uint32_t base, peripheral per, ICU::VECTOR_AL1 eint>
		typename edmac_t<base, per, eint>::IOSR_ edmac_t<base, per, eint>::IOSR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ptpedmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct ptpedmac_t : public edmac_core_t<base, per> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PTP/EDMAC ステータスレジスタ（PTPEDMAC.EESR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef eesr_t<base + 0x28> EESR_;
		static  EESR_ EESR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PTP/EDMAC ステータス割り込み許可レジスタ（PTPEDMAC.EESIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef eesipr_t<base + 0x30> EESIPR_;
		static  EESIPR_ EESIPR;
	};
	template <uint32_t base, peripheral per>
		typename ptpedmac_t<base, per>::EESR_ ptpedmac_t<base, per>::EESR;
	template <uint32_t base, peripheral per>
		typename ptpedmac_t<base, per>::EESIPR_ ptpedmac_t<base, per>::EESIPR;

	typedef edmac_t<0x000C0000, peripheral::EDMAC0, ICU::VECTOR_AL1::EINT0> EDMAC0;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef edmac_t<0x000C0200, peripheral::EDMAC1, ICU::VECTOR_AL1::EINT1> EDMAC1;
#endif
	typedef ptpedmac_t<0x000C0400, peripheral::PTPEDMAC> PTPEDMAC;
}
