#pragma once
//=============================================================================//
/*!	@file
	@brief	Ethernet Controller / イーサネットコントローラ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ETHERC base class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct etherc_base_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC モードレジスタ（ECMR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ecmr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PRM;
			bit_rw_t<io_, bitpos::B1> DM;
			bit_rw_t<io_, bitpos::B2> RTM;
			bit_rw_t<io_, bitpos::B3> ILB;

			bit_rw_t<io_, bitpos::B5> TE;
			bit_rw_t<io_, bitpos::B6> RE;

			bit_rw_t<io_, bitpos::B9> MPDE;

			bit_rw_t<io_, bitpos::B12> PRCEF;

			bit_rw_t<io_, bitpos::B16> TXF;
			bit_rw_t<io_, bitpos::B17> RXF;
			bit_rw_t<io_, bitpos::B18> PFR;
			bit_rw_t<io_, bitpos::B19> ZPF;
			bit_rw_t<io_, bitpos::B20> TPC;
		};
		static inline ecmr_t<base + 0x00> ECMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信フレーム長上限レジスタ（RFLR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rflr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12> RFL;
		};
		static inline rflr_t<base + 0x08> RFLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC ステータスレジスタ（ECSR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ecsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ICD;
			bit_rw_t<io_, bitpos::B1> MPD;
			bit_rw_t<io_, bitpos::B2> LCHNG;

			bit_rw_t<io_, bitpos::B4> PSRTO;
			bit_rw_t<io_, bitpos::B5> BFR;
		};
		static inline ecsr_t<base + 0x10> ECSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC 割り込み許可レジスタ（ECSIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ecsipr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ICDIP;
			bit_rw_t<io_, bitpos::B1> MPDIP;
			bit_rw_t<io_, bitpos::B2> LCHNGIP;

			bit_rw_t<io_, bitpos::B4> PSRTOIP;
			bit_rw_t<io_, bitpos::B5> BFSIPR;
		};
		static inline ecsipr_t<base + 0x18> ECSIPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY 部インタフェースレジスタ（PIR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pir_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MDC;
			bit_rw_t<io_, bitpos::B1> MMD;
			bit_rw_t<io_, bitpos::B2> MDO;
			bit_rw_t<io_, bitpos::B3> MDI;
		};
		static inline pir_t<base + 0x20> PIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY 部ステータスレジスタ（PSR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct psr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0> LMON;
		};
		static inline psr_t<base + 0x28> PSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  乱数生成カウンタ上限値設定レジスタ（RDMLR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rdmlr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 20> RMD;
		};
		static inline rdmlr_t<base + 0x40> RDMLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Interpacket Gap 設定レジスタ（IPGR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ipgr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> IPG;
		};
		static inline ipgr_t<base + 0x50> IPGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  自動 PAUSE フレーム設定レジスタ（APR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct apr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> AP;
		};
		static inline apr_t<base + 0x54> APR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  手動 PAUSE フレーム設定レジスタ（MPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct mpr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> MP;
		};
		static inline mpr_t<base + 0x58> MPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信 PAUSE フレームカウンタ（RFCF）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rfcf_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8> RPAUSE;
		};
		static inline rfcf_t<base + 0x60> RFCF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  自動 PAUSE フレーム再送回数設定レジスタ（TPAUSER）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tpauser_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> TPAUSE;
		};
		static inline tpauser_t<base + 0x64> TPAUSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAUSE フレーム再送回数カウンタ（TPAUSECR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tpausecr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8> TXP;
		};
		static inline tpausecr_t<base + 0x68> TPAUSECR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Broadcast フレーム受信回数設定レジスタ（BCFRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bcfrr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> BCF;
		};
		static inline bcfrr_t<base + 0x6C> BCFRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MAC アドレス上位設定レジスタ（MAHR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xC0> MAHR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MAC アドレス下位設定レジスタ（MALR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xC8> MALR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信リトライオーバカウンタレジスタ（TROCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xD0> TROCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  遅延衝突検出カウンタレジスタ（CDCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xD4> CDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャリア消失カウンタレジスタ（LCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xD8> LCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャリア未検出カウンタレジスタ（CNDCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xDC> CNDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CRC エラーフレーム受信カウンタレジスタ（CEFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xE4> CEFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フレーム受信エラーカウンタレジスタ（FRECR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xE8> FRECR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ショートフレーム受信カウンタレジスタ（TSFRCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xEC> TSFRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ロングフレーム受信カウンタレジスタ（TLFRCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xF0> TLFRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端数ビットフレーム受信カウンタレジスタ（RFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xF4> RFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  マルチキャストアドレスフレーム受信カウンタレジスタ（MAFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0xF8> MAFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ETHERC 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct etherc_t : public etherc_base_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

	};
#if defined(SIG_RX62N) || defined(SIG_RX63N)
	typedef etherc_t<0x000C'0100, peripheral::ETHERC> ETHERC;
#elif defined(SIG_RX621) || defined(SIG_RX631)
#else
	typedef etherc_t<0x000C'0100, peripheral::ETHERC0> ETHERC0;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef etherc_t<0x000C'0300, peripheral::ETHERC1> ETHERC1;
#endif
#endif
}
