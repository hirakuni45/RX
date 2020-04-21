#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　ETHERC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ETHERC 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct etherc_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型

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
		typedef ecmr_t<base + 0x00> ECMR_;
		static  ECMR_ ECMR;


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
		typedef rflr_t<base + 0x08> RFLR_;
		static  RFLR_ RFLR;


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
		typedef ecsr_t<base + 0x10> ECSR_;
		static  ECSR_ ECSR;


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
		typedef ecsipr_t<base + 0x18> ECSIPR_;
		static  ECSIPR_ ECSIPR;


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
		typedef pir_t<base + 0x20> PIR_;
		static  PIR_ PIR;


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
		typedef psr_t<base + 0x28> PSR_;
		static  PSR_ PSR;


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
		typedef rdmlr_t<base + 0x40> RDMLR_;
		static  RDMLR_ RDMLR;


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
		typedef ipgr_t<base + 0x50> IPGR_;
		static  IPGR_ IPGR;


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
		typedef apr_t<base + 0x54> APR_;
		static  APR_ APR;


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
		typedef mpr_t<base + 0x58> MPR_;
		static  MPR_ MPR;


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
		typedef rfcf_t<base + 0x60> RFCF_;
		static  RFCF_ RFCF;


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
		typedef tpauser_t<base + 0x64> TPAUSER_;
		static  TPAUSER_ TPAUSER;


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
		typedef tpausecr_t<base + 0x68> TPAUSECR_;
		static  TPAUSECR_ TPAUSECR;


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
		typedef bcfrr_t<base + 0x6C> BCFRR_;
		static  BCFRR_ BCFRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MAC アドレス上位設定レジスタ（MAHR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xC0> MAHR_;
		static  MAHR_ MAHR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MAC アドレス下位設定レジスタ（MALR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xC8> MALR_;
		static  MALR_ MALR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信リトライオーバカウンタレジスタ（TROCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD0> TROCR_;
		static  TROCR_ TROCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  遅延衝突検出カウンタレジスタ（CDCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD4> CDCR_;
		static  CDCR_ CDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャリア消失カウンタレジスタ（LCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD8> LCCR_;
		static  LCCR_ LCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャリア未検出カウンタレジスタ（CNDCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xDC> CNDCR_;
		static  CNDCR_ CNDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CRC エラーフレーム受信カウンタレジスタ（CEFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xE4> CEFCR_;
		static  CEFCR_ CEFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フレーム受信エラーカウンタレジスタ（FRECR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xE8> FRECR_;
		static  FRECR_ FRECR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ショートフレーム受信カウンタレジスタ（TSFRCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xEC> TSFRCR_;
		static  TSFRCR_ TSFRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ロングフレーム受信カウンタレジスタ（TLFRCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xF0> TLFRCR_;
		static  TLFRCR_ TLFRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端数ビットフレーム受信カウンタレジスタ（RFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xF4> RFCR_;
		static  RFCR_ RFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  マルチキャストアドレスフレーム受信カウンタレジスタ（MAFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xF8> MAFCR_;
		static  MAFCR_ MAFCR;
	};
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::ECMR_ etherc_t<base, per>::ECMR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::RFLR_ etherc_t<base, per>::RFLR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::ECSR_ etherc_t<base, per>::ECSR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::ECSIPR_ etherc_t<base, per>::ECSIPR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::PIR_ etherc_t<base, per>::PIR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::PSR_ etherc_t<base, per>::PSR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::RDMLR_ etherc_t<base, per>::RDMLR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::IPGR_ etherc_t<base, per>::IPGR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::APR_ etherc_t<base, per>::APR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::MPR_ etherc_t<base, per>::MPR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::RFCF_ etherc_t<base, per>::RFCF;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::TPAUSER_ etherc_t<base, per>::TPAUSER;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::TPAUSECR_ etherc_t<base, per>::TPAUSECR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::BCFRR_ etherc_t<base, per>::BCFRR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::MAHR_ etherc_t<base, per>::MAHR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::MALR_ etherc_t<base, per>::MALR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::TROCR_ etherc_t<base, per>::TROCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::CDCR_ etherc_t<base, per>::CDCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::LCCR_ etherc_t<base, per>::LCCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::CNDCR_ etherc_t<base, per>::CNDCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::CEFCR_ etherc_t<base, per>::CEFCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::FRECR_ etherc_t<base, per>::FRECR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::TSFRCR_ etherc_t<base, per>::TSFRCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::TLFRCR_ etherc_t<base, per>::TLFRCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::RFCR_ etherc_t<base, per>::RFCR;
	template <uint32_t base, peripheral per> typename etherc_t<base, per>::MAFCR_ etherc_t<base, per>::MAFCR;


	typedef etherc_t<0x000C0100, peripheral::ETHERC0> ETHERC0;
	typedef etherc_t<0x000C0300, peripheral::ETHERC1> ETHERC1;
}
