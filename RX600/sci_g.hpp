#pragma once
//=========================================================================//
/*!	@file
	@brief	Serial Communications Interface g / シリアルコミュニケーションインタフェース g
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/sci_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIg class
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	ICUT	送信終了、受信エラー、割り込み型
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		typename ICUT, ICUT tei, ICUT eri>
	struct scig_t : public sci_gj_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKB;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME  = true;	///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM  = true;	///< SEMR.BGDM が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN  = true;	///< SEMR.NFEN が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = false;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF   = true;	///< SSR.RDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB    = true;	///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB    = true;	///< 簡易 SPI が利用可能な場合「true」
		// FIFO 機能の有無
		static constexpr bool FIFO_FUNC  = false;	///< FIFO バッファ機能が有効な場合「true」
	};

#if defined(SIG_RX13T) || defined(SIG_RX23T)
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, ICU::VECTOR::ERI1> SCI1;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, ICU::VECTOR::ERI5> SCI5;
#elif defined(SIG_RX130)
	typedef scig_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR, ICU::VECTOR::TEI0, ICU::VECTOR::ERI0> SCI0;
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, ICU::VECTOR::ERI1> SCI1;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, ICU::VECTOR::ERI5> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, ICU::VECTOR::ERI6> SCI6;
	typedef scig_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::VECTOR, ICU::VECTOR::TEI8, ICU::VECTOR::ERI8> SCI8;
	typedef scig_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR, ICU::VECTOR::TEI9, ICU::VECTOR::ERI9> SCI9;
#elif defined(SIG_RX140)
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, ICU::VECTOR::ERI6> SCI6;
	typedef scig_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::VECTOR, ICU::VECTOR::TEI8, ICU::VECTOR::ERI8> SCI8;
	typedef scig_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR, ICU::VECTOR::TEI9, ICU::VECTOR::ERI9> SCI9;
#elif defined(SIG_RX231)
	typedef scig_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR, ICU::VECTOR::TEI0, ICU::VECTOR::ERI0> SCI0;
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, ICU::VECTOR::ERI1> SCI1;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, ICU::VECTOR::ERI5> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, ICU::VECTOR::ERI6> SCI6;
	typedef scig_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::VECTOR, ICU::VECTOR::TEI8, ICU::VECTOR::ERI8> SCI8;
	typedef scig_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR, ICU::VECTOR::TEI9, ICU::VECTOR::ERI9> SCI9;
#elif defined(SIG_RX24T)
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, ICU::VECTOR::ERI1> SCI1;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, ICU::VECTOR::ERI5> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, ICU::VECTOR::ERI6> SCI6;
#elif defined(SIG_RX24U)
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR, ICU::VECTOR::TEI1, ICU::VECTOR::ERI1> SCI1;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR, ICU::VECTOR::TEI5, ICU::VECTOR::ERI5> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR, ICU::VECTOR::TEI6, ICU::VECTOR::ERI6> SCI6;
	typedef scig_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::VECTOR, ICU::VECTOR::TEI8, ICU::VECTOR::ERI8> SCI8;
	typedef scig_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR, ICU::VECTOR::TEI9, ICU::VECTOR::ERI9> SCI9;
	typedef scig_t<0x000D'0000, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::VECTOR, ICU::VECTOR::TEI11, ICU::VECTOR::ERI11> SCI11;
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef scig_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI0, ICU::GROUPBL0::ERI0> SCI0;
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1> SCI1;
	typedef scig_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI2, ICU::GROUPBL0::ERI2> SCI2;
	typedef scig_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI3, ICU::GROUPBL0::ERI3> SCI3;
	typedef scig_t<0x0008'A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI4, ICU::GROUPBL0::ERI4> SCI4;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6> SCI6;
	typedef scig_t<0x0008'A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI7, ICU::GROUPBL0::ERI7> SCI7;
#elif defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX660) || defined(SIG_RX671)
	typedef scig_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI0, ICU::GROUPBL0::ERI0> SCI0;
	typedef scig_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1> SCI1;
	typedef scig_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI2, ICU::GROUPBL0::ERI2> SCI2;
	typedef scig_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI3, ICU::GROUPBL0::ERI3> SCI3;
	typedef scig_t<0x0008'A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI4, ICU::GROUPBL0::ERI4> SCI4;
	typedef scig_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5> SCI5;
	typedef scig_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6> SCI6;
	typedef scig_t<0x0008'A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI7, ICU::GROUPBL0::ERI7> SCI7;
	typedef scig_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI8, ICU::GROUPBL1::ERI8> SCI8;
	typedef scig_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI9, ICU::GROUPBL1::ERI9> SCI9;
#endif
}
