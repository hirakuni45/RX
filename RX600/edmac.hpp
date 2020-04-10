#pragma once
//=====================================================================//
/*!	@file
	@brief	イーサネットコントローラ用 DMA コントローラ (EDMACa) @n
			RX64M/RX71M/RX65N
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

/// CMPC モジュールが無いデバイスでエラーとする
#if defined(SIG_RX24T) || defined(SIG_RX66T)
#  error "edmac.hpp: This module does not exist"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac core 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct edmac_core_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC モードレジスタ（EDMR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SWR;

			bits_rw_t<io_, bitpos::B4, 2> DL;
			bit_rw_t<io_, bitpos::B6> DE;

		};
		typedef edmr_t_<base + 0x00> edmr_t;
		static edmr_t EDMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC 送信要求レジスタ（EDTRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edtrr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TR;

		};
		typedef edtrr_t_<base + 0x08> edtrr_t;
		static edtrr_t EDTRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EDMAC 受信要求レジスタ（EDRRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edrrr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RR;
		};
		typedef edrrr_t_<base + 0x10> edrrr_t;
		static edrrr_t EDRRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信ディスクリプタリスト先頭アドレスレジスタ（TDLAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> tdlar_t;
		static tdlar_t TDLAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信ディスクリプタリスト先頭アドレスレジスタ（RDLAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x20> rdlar_t;
		static rdlar_t RDLAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ミスドフレームカウンタレジスタ（RMFCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rmfcr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> MFC;
		};
		typedef rmfcr_t_<base + 0x40> rmfcr_t;
		static rmfcr_t RMFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信 FIFO しきい値指定レジスタ（TFTR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tftr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> TFT;
		};
		typedef tftr_t_<base + 0x48> tftr_t;
		static tftr_t TFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FIFO 容量指定レジスタ（FDR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fdr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> RFD;
			bits_rw_t<io_, bitpos::B8, 5> TFD;
		};
		typedef fdr_t_<base + 0x50> fdr_t;
		static fdr_t FDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信方式制御レジスタ（RMCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rmcr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RNR;
		};
		typedef rmcr_t_<base + 0x58> rmcr_t;
		static rmcr_t RMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信 FIFO アンダフローカウント（TFUCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tfucr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> UNDER;
		};
		typedef tfucr_t_<base + 0x64> tfucr_t;
		static tfucr_t TFUCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信 FIFO オーバフローカウント（RFOCR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rfocr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> OVER;
		};
		typedef rfocr_t_<base + 0x68> rfocr_t;
		static rfocr_t RFOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フロー制御開始 FIFO しきい値設定レジスタ（FCFTR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fcftr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  RFDO;

			bits_rw_t<io_, bitpos::B16, 3> RFFO;
		};
		typedef fcftr_t_<base + 0x70> fcftr_t;
		static fcftr_t FCFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信データパディング挿入設定レジスタ（RPADIR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rpadir_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  PADR;

			bits_rw_t<io_, bitpos::B16, 2> PADS;
		};
		typedef rpadir_t_<base + 0x78> rpadir_t;
		static rpadir_t RPADIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信割り込み設定レジスタ（TRIMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct trimd_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TIS;

			bit_rw_t<io_, bitpos::B4> TIM;
		};
		typedef trimd_t_<base + 0x7C> trimd_t;
		static trimd_t TRIMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信バッファライトアドレスレジスタ（RBWAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xC8> rbwar_t;
		static rbwar_t RBWAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信ディスクリプタフェッチアドレスレジスタ（RDFAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xCC> rdfar_t;
		static rdfar_t RDFAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信バッファリードアドレスレジスタ（TBRAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD4> tbrar_t;
		static tbrar_t TBRAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信ディスクリプタフェッチアドレスレジスタ（TDFAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD8> tdfar_t;
		static tdfar_t TDFAR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct edmac_t : public edmac_core_t<base> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC ステータスレジスタ（EDMACn.EESR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesr_t_ : public rw32_t<ofs> {
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
		typedef eesr_t_<base + 0x28> eesr_t;
		static eesr_t EESR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC ステータス割り込み許可レジスタ（EDMACn.EESIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesipr_t_ : public rw32_t<ofs> {
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
		typedef eesipr_t_<base + 0x30> eesipr_t;
		static eesipr_t EESIPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC/EDMAC 送受信ステータスコピー指示レジスタ（EDMACn.TRSCER）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct trscer_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>  PRFCE;

			bit_rw_t<io_, bitpos::B7>  RMAFCE;
		};
		typedef trscer_t_<base + 0x38> trscer_t;
		static trscer_t TRSCER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  個別出力信号設定レジスタ（IOSR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iosr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ELB;
		};
		typedef iosr_t_<base + 0x6C> iosr_t;
		static iosr_t IOSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
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

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PTP/EDMAC ステータスレジスタ（PTPEDMAC.EESR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesr_t_ : public rw32_t<ofs> {
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
		typedef eesr_t_<base + 0x28> eesr_t;
		static eesr_t EESR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PTP/EDMAC ステータス割り込み許可レジスタ（PTPEDMAC.EESIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eesipr_t_ : public rw32_t<ofs> {
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
		typedef eesipr_t_<base + 0x30> eesipr_t;
		static eesipr_t EESIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};

	typedef edmac_t<0x000C0000, peripheral::EDMAC0>      EDMAC0;
	typedef edmac_t<0x000C0200, peripheral::EDMAC1>      EDMAC1;
	typedef ptpedmac_t<0x000C0400, peripheral::PTPEDMAC> PTPEDMAC;

	template<uint32_t base> typename edmac_core_t<base>::edmr_t edmac_core_t<base>::EDMR;
	template<uint32_t base> typename edmac_core_t<base>::edtrr_t edmac_core_t<base>::EDTRR;
	template<uint32_t base> typename edmac_core_t<base>::edrrr_t edmac_core_t<base>::EDRRR;
	template<uint32_t base> typename edmac_core_t<base>::tdlar_t edmac_core_t<base>::TDLAR;
	template<uint32_t base> typename edmac_core_t<base>::rdlar_t edmac_core_t<base>::RDLAR;
	template<uint32_t base> typename edmac_core_t<base>::rmfcr_t edmac_core_t<base>::RMFCR;
	template<uint32_t base> typename edmac_core_t<base>::tftr_t edmac_core_t<base>::TFTR;
	template<uint32_t base> typename edmac_core_t<base>::fdr_t edmac_core_t<base>::FDR;
	template<uint32_t base> typename edmac_core_t<base>::rmcr_t edmac_core_t<base>::RMCR;
	template<uint32_t base> typename edmac_core_t<base>::tfucr_t edmac_core_t<base>::TFUCR;
	template<uint32_t base> typename edmac_core_t<base>::rfocr_t edmac_core_t<base>::RFOCR;
	template<uint32_t base> typename edmac_core_t<base>::fcftr_t edmac_core_t<base>::FCFTR;
	template<uint32_t base> typename edmac_core_t<base>::rpadir_t edmac_core_t<base>::RPADIR;
	template<uint32_t base> typename edmac_core_t<base>::trimd_t edmac_core_t<base>::TRIMD;
	template<uint32_t base> typename edmac_core_t<base>::rbwar_t edmac_core_t<base>::RBWAR;
	template<uint32_t base> typename edmac_core_t<base>::rdfar_t edmac_core_t<base>::RDFAR;
	template<uint32_t base> typename edmac_core_t<base>::tbrar_t edmac_core_t<base>::TBRAR;
	template<uint32_t base> typename edmac_core_t<base>::tdfar_t edmac_core_t<base>::TDFAR;

	template<uint32_t base, peripheral per> typename edmac_t<base, per>::eesr_t edmac_t<base, per>::EESR;
	template<uint32_t base, peripheral per> typename edmac_t<base, per>::eesipr_t edmac_t<base, per>::EESIPR;
	template<uint32_t base, peripheral per> typename edmac_t<base, per>::trscer_t edmac_t<base, per>::TRSCER;
	template<uint32_t base, peripheral per> typename edmac_t<base, per>::iosr_t edmac_t<base, per>::IOSR;

	template<uint32_t base, peripheral per> typename ptpedmac_t<base, per>::eesr_t ptpedmac_t<base, per>::EESR;
	template<uint32_t base, peripheral per> typename ptpedmac_t<base, per>::eesipr_t ptpedmac_t<base, per>::EESIPR;
}
