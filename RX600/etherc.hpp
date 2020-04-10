#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　ETHERC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
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

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC モードレジスタ（ECMR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ecmr_t_ : public rw32_t<ofs> {
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
		typedef ecmr_t_<base + 0x00> ecmr_t;
		static ecmr_t ECMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信フレーム長上限レジスタ（RFLR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rflr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12> RFL;
		};
		typedef rflr_t_<base + 0x08> rflr_t;
		static rflr_t RFLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC ステータスレジスタ（ECSR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ecsr_t_ : public rw32_t<ofs> {
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
		typedef ecsr_t_<base + 0x10> ecsr_t;
		static ecsr_t ECSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHERC 割り込み許可レジスタ（ECSIPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ecsipr_t_ : public rw32_t<ofs> {
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
		typedef ecsipr_t_<base + 0x18> ecsipr_t;
		static ecsipr_t ECSIPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY 部インタフェースレジスタ（PIR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pir_t_ : public rw32_t<ofs> {
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
		typedef pir_t_<base + 0x20> pir_t;
		static pir_t PIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY 部ステータスレジスタ（PSR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct psr_t_ : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0> LMON;
		};
		typedef psr_t_<base + 0x28> psr_t;
		static psr_t PSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  乱数生成カウンタ上限値設定レジスタ（RDMLR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rdmlr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 20> RMD;
		};
		typedef rdmlr_t_<base + 0x40> rdmlr_t;
		static rdmlr_t RDMLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Interpacket Gap 設定レジスタ（IPGR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ipgr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> IPG;
		};
		typedef ipgr_t_<base + 0x50> ipgr_t;
		static ipgr_t IPGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  自動 PAUSE フレーム設定レジスタ（APR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct apr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> AP;
		};
		typedef apr_t_<base + 0x54> apr_t;
		static apr_t APR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  手動 PAUSE フレーム設定レジスタ（MPR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct mpr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> MP;
		};
		typedef mpr_t_<base + 0x58> mpr_t;
		static mpr_t MPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  受信 PAUSE フレームカウンタ（RFCF）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rfcf_t_ : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8> RPAUSE;
		};
		typedef rfcf_t_<base + 0x60> rfcf_t;
		static rfcf_t RFCF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  自動 PAUSE フレーム再送回数設定レジスタ（TPAUSER）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tpauser_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> TPAUSE;
		};
		typedef tpauser_t_<base + 0x64> tpauser_t;
		static tpauser_t TPAUSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAUSE フレーム再送回数カウンタ（TPAUSECR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tpausecr_t_ : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 8> TXP;
		};
		typedef tpausecr_t_<base + 0x68> tpausecr_t;
		static tpausecr_t TPAUSECR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Broadcast フレーム受信回数設定レジスタ（BCFRR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bcfrr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16> BCF;
		};
		typedef bcfrr_t_<base + 0x6C> bcfrr_t;
		static bcfrr_t BCFRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MAC アドレス上位設定レジスタ（MAHR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xC0> mahr_t;
		static mahr_t MAHR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MAC アドレス下位設定レジスタ（MALR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xC8> malr_t;
		static malr_t MALR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信リトライオーバカウンタレジスタ（TROCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD0> trocr_t;
		static trocr_t TROCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  遅延衝突検出カウンタレジスタ（CDCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD4> cdcr_t;
		static cdcr_t CDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャリア消失カウンタレジスタ（LCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xD8> lccr_t;
		static lccr_t LCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャリア未検出カウンタレジスタ（CNDCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xDC> cndcr_t;
		static cndcr_t CNDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CRC エラーフレーム受信カウンタレジスタ（CEFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xE4> cefcr_t;
		static cefcr_t CEFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フレーム受信エラーカウンタレジスタ（FRECR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xE8> frecr_t;
		static frecr_t FRECR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ショートフレーム受信カウンタレジスタ（TSFRCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xEC> tsfrcr_t;
		static tsfrcr_t TSFRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ロングフレーム受信カウンタレジスタ（TLFRCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xF0> tlfrcr_t;
		static tlfrcr_t TLFRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端数ビットフレーム受信カウンタレジスタ（RFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xF4> rfcr_t;
		static rfcr_t RFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  マルチキャストアドレスフレーム受信カウンタレジスタ（MAFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0xF8> mafcr_t;
		static mafcr_t MAFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};

	typedef etherc_t<0x000C0100, peripheral::ETHERC0> ETHERC0;
	typedef etherc_t<0x000C0300, peripheral::ETHERC1> ETHERC1;

	template<uint32_t base, peripheral per> typename etherc_t<base, per>::ecmr_t etherc_t<base, per>::ECMR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::rflr_t etherc_t<base, per>::RFLR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::ecsr_t etherc_t<base, per>::ECSR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::ecsipr_t etherc_t<base, per>::ECSIPR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::pir_t etherc_t<base, per>::PIR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::psr_t etherc_t<base, per>::PSR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::rdmlr_t etherc_t<base, per>::RDMLR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::ipgr_t etherc_t<base, per>::IPGR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::apr_t etherc_t<base, per>::APR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::mpr_t etherc_t<base, per>::MPR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::rfcf_t etherc_t<base, per>::RFCF;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::tpauser_t etherc_t<base, per>::TPAUSER;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::tpausecr_t etherc_t<base, per>::TPAUSECR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::bcfrr_t etherc_t<base, per>::BCFRR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::mahr_t etherc_t<base, per>::MAHR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::malr_t etherc_t<base, per>::MALR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::trocr_t etherc_t<base, per>::TROCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::cdcr_t etherc_t<base, per>::CDCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::lccr_t etherc_t<base, per>::LCCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::cndcr_t etherc_t<base, per>::CNDCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::cefcr_t etherc_t<base, per>::CEFCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::frecr_t etherc_t<base, per>::FRECR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::tsfrcr_t etherc_t<base, per>::TSFRCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::tlfrcr_t etherc_t<base, per>::TLFRCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::rfcr_t etherc_t<base, per>::RFCR;
	template<uint32_t base, peripheral per> typename etherc_t<base, per>::mafcr_t etherc_t<base, per>::MAFCR;
}
