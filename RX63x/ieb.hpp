#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N IEB 定義
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
		@brief  IEB 定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct ieb_t {

		static constexpr auto PERIPHERAL = peripheral::IEB;
		static constexpr auto IEBINT     = ICU::VECTOR::IEBINT;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus コントロールレジスタ（IECTR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iectr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B3>     RE;

			bit_rw_t <io_, bitpos::B5>     DEE;
			bit_rw_t <io_, bitpos::B6>     IOL;
		};
		typedef iectr_t<0x0008'A800> IECTR_;
		static  IECTR_ IECTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus コマンドレジスタ（IECMR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iecmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CMD;
		};
		typedef iecmr_t<0x0008'A801> IECMR_;
		static  IECMR_ IECMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus マスタコントロールレジスタ（IEMCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iemcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CTL;
			bits_rw_t<io_, bitpos::B4, 3>  RN;
			bit_rw_t <io_, bitpos::B7>     SS;
		};
		typedef iemcr_t<0x0008'A802> IEMCR_;
		static  IEMCR_ IEMCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 自局アドレスレジスタ 1（IEAR1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iear1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     STE;

			bits_rw_t<io_, bitpos::B2, 2>  IMD;
			bits_rw_t<io_, bitpos::B4, 4>  IARL;
		};
		typedef iear1_t<0x0008'A803> IEAR1_;
		static  IEAR1_ IEAR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 自局アドレスレジスタ 2（IEAR2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iear2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  IARU8;
		};
		typedef iear2_t<0x0008'A804> IEAR2_;
		static  IEAR2_ IEAR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus スレーブアドレス設定レジスタ 1（IESA1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iesa1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 4>  ISAL;
		};
		typedef iesa1_t<0x0008'A805> IESA1_;
		static  IESA1_ IESA1;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus スレーブアドレス設定レジスタ 2（IESA2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iesa2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  ISAU8;
		};
		typedef iesa2_t<0x0008'A806> IESA2_;
		static  IESA2_ IESA2;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 送信電文長レジスタ（IETBFL）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ietbfl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  IBFL;
		};
		typedef ietbfl_t<0x0008'A807> IETBFL_;
		static  IETBFL_ IETBFL;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 受信マスタアドレスレジスタ 1（IEMA1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iema1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 4>  IMAL4;
		};
		typedef iema1_t<0x0008'A809> IEMA1_;
		static  IEMA1_ IEMA1;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 受信マスタアドレスレジスタ 2（IEMA2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iema2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  IMAU8;
		};
		typedef iema2_t<0x0008'A80A> IEMA2_;
		static  IEMA2_ IEMA2;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 受信コントロールフィールドレジスタ（IERCTL）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ierctl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  RCTL;
		};
		typedef ierctl_t<0x0008'A80B> IERCTL_;
		static  IERCTL_ IERCTL;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 受信電文長レジスタ（IERBFL）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ierbfl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  RBFL;
		};
		typedef ierbfl_t<0x0008'A80C> IERBFL_;
		static  IERBFL_ IERBFL;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus ロックアドレスレジスタ 1（IELA1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iela1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  ILAL8;
		};
		typedef iela1_t<0x0008'A80E> IELA1_;
		static  IELA1_ IELA1;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus ロックアドレスレジスタ 2（IELA2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iela2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  ILAU4;
		};
		typedef iela2_t<0x0008'A80F> IELA2_;
		static  IELA2_ IELA2;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus ゼネラルフラグレジスタ（IEFLG）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ieflg_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> io_;
			using io_::operator ();

			bit_rw_t<io_, bitpos::B0>  GG;
			bit_rw_t<io_, bitpos::B1>  RSS;

			bit_rw_t<io_, bitpos::B3>  LCK;
			bit_rw_t<io_, bitpos::B4>  SRE;
			bit_rw_t<io_, bitpos::B5>  SRQ;
			bit_rw_t<io_, bitpos::B6>  MRQ;
			bit_rw_t<io_, bitpos::B7>  CMX;
		};
		typedef ieflg_t<0x0008'A810> IEFLG_;
		static  IEFLG_ IEFLG;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 送信ステータスレジスタ（IETSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ietsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  TXEACK;
			bit_rw_t<io_, bitpos::B1>  TXERO;
			bit_rw_t<io_, bitpos::B2>  TXETIME;
			bit_rw_t<io_, bitpos::B3>  TXEAL;

			bit_rw_t<io_, bitpos::B5>  TXF;
			bit_rw_t<io_, bitpos::B6>  TXS;
		};
		typedef ietsr_t<0x0008'A811> IETSR_;
		static  IETSR_ IETSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 送信割り込み許可レジスタ（IEIET）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ieiet_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  TXEACKE;
			bit_rw_t<io_, bitpos::B1>  TXEROE;
			bit_rw_t<io_, bitpos::B2>  TXETIMEE;
			bit_rw_t<io_, bitpos::B3>  TXEALE;

			bit_rw_t<io_, bitpos::B5>  TXFE;
			bit_rw_t<io_, bitpos::B6>  TXSE;
		};
		typedef ieiet_t<0x0008'A812> IEIET_;
		static  IEIET_ IEIET;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 受信ステータスレジスタ（IERSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iersr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RXEPE;
			bit_rw_t<io_, bitpos::B1>  RXEDLE;
			bit_rw_t<io_, bitpos::B2>  RXERTME;
			bit_rw_t<io_, bitpos::B3>  RXEOVE;
			bit_rw_t<io_, bitpos::B4>  RXEDE;
			bit_rw_t<io_, bitpos::B5>  RXF;
			bit_rw_t<io_, bitpos::B6>  RXS;
			bit_rw_t<io_, bitpos::B7>  RXBSY;
		};
		typedef iersr_t<0x0008'A814> IERSR_;
		static  IERSR_ IERSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 受信割り込み許可レジスタ（IEIER）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ieier_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RXEPEE;
			bit_rw_t<io_, bitpos::B1>  RXEDLEE;
			bit_rw_t<io_, bitpos::B2>  RXERTMEE;
			bit_rw_t<io_, bitpos::B3>  RXEOVEE;
			bit_rw_t<io_, bitpos::B4>  RXEDEE;
			bit_rw_t<io_, bitpos::B5>  RXFE;
			bit_rw_t<io_, bitpos::B6>  RXSE;
			bit_rw_t<io_, bitpos::B7>  RXBSYE;
		};
		typedef ieier_t<0x0008'A815> IEIER_;
		static  IEIER_ IEIER;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus クロック選択レジスタ（IECKSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct iecksr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> CKS;
			bit_rw_t <io_, bitpos::B3>    SRSTP;
			bit_rw_t <io_, bitpos::B4>    CKS3;
			bits_rw_t<io_, bitpos::B5, 2> FCKS;
			bit_rw_t <io_, bitpos::B7>    FLT;
		};
		typedef iecksr_t<0x0008'A818> IECKSR_;
		static  IECKSR_ IECKSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 送信データバッファレジスタ 0 ～ 31（IETB[0] ～ IETB[31]）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ietb_t {
			volatile uint8_t& operator[] (uint32_t idx) {
				if(idx >= 32) idx = 31;
				return *reinterpret_cast<volatile uint8_t*>(ofs + idx);
			}
		};
		typedef ietb_t<0x0008'A900> IETB_;
		static  IETB_ IETB;


		//-----------------------------------------------------------------//
		/*!
			@brief	IEBus 受信データバッファレジスタ 0 ～ 31（IERB[0] ～ IERB[31]）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ierb_t {
			volatile uint8_t& operator[] (uint32_t idx) {
				if(idx >= 32) idx = 31;
				return *reinterpret_cast<volatile uint8_t*>(ofs + idx);
			}
		};
		typedef ierb_t<0x0008'AA00> IERB_;
		static  IERB_ IERB;
	};
	template <class _> typename ieb_t<_>::IECTR_ ieb_t<_>::IECTR;
	template <class _> typename ieb_t<_>::IECMR_ ieb_t<_>::IECMR;
	template <class _> typename ieb_t<_>::IEMCR_ ieb_t<_>::IEMCR;
	template <class _> typename ieb_t<_>::IEAR1_ ieb_t<_>::IEAR1;
	template <class _> typename ieb_t<_>::IEAR2_ ieb_t<_>::IEAR2;
	template <class _> typename ieb_t<_>::IESA1_ ieb_t<_>::IESA1;
	template <class _> typename ieb_t<_>::IESA2_ ieb_t<_>::IESA2;
	template <class _> typename ieb_t<_>::IETBFL_ ieb_t<_>::IETBFL;
	template <class _> typename ieb_t<_>::IEMA1_ ieb_t<_>::IEMA1;
	template <class _> typename ieb_t<_>::IEMA2_ ieb_t<_>::IEMA2;
	template <class _> typename ieb_t<_>::IERCTL_ ieb_t<_>::IERCTL;
	template <class _> typename ieb_t<_>::IERBFL_ ieb_t<_>::IERBFL;
	template <class _> typename ieb_t<_>::IELA1_ ieb_t<_>::IELA1;
	template <class _> typename ieb_t<_>::IELA2_ ieb_t<_>::IELA2;
	template <class _> typename ieb_t<_>::IEFLG_ ieb_t<_>::IEFLG;
	template <class _> typename ieb_t<_>::IETSR_ ieb_t<_>::IETSR;
	template <class _> typename ieb_t<_>::IEIET_ ieb_t<_>::IEIET;
	template <class _> typename ieb_t<_>::IERSR_ ieb_t<_>::IERSR;
	template <class _> typename ieb_t<_>::IEIER_ ieb_t<_>::IEIER;
	template <class _> typename ieb_t<_>::IECKSR_ ieb_t<_>::IECKSR;
	template <class _> typename ieb_t<_>::IETB_ ieb_t<_>::IETB;
	template <class _> typename ieb_t<_>::IERB_ ieb_t<_>::IERB;
}
