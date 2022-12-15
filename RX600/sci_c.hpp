#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCIc 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/sci_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIe クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR tei,
		typename ICUT, ICUT eri>
	struct scic_t : public sci_ce_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKB;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME  = false;	///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM  = false;	///< SEMR.BGDM  が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN  = true;	///< SEMR.NFEN　が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = false;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF   = true;	///< SSR.RRDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB    = true;	///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB    = true;	///< 簡易 SPI が利用可能な場合「true」
	};

#if defined(SIG_RX631) || defined(SIG_RX63N)
	typedef scic_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0, ICU::VECTOR::TEI0,
		ICU::GROUP12, ICU::GROUP12::ERI0> SCI0;
	typedef scic_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1, ICU::VECTOR::TEI1, 
		ICU::GROUP12, ICU::GROUP12::ERI1> SCI1;
	typedef scic_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2, ICU::VECTOR::TEI2,
		ICU::GROUP12, ICU::GROUP12::ERI2> SCI2;
	typedef scic_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3, ICU::VECTOR::TEI3,
		ICU::GROUP12, ICU::GROUP12::ERI3> SCI3;
	typedef scic_t<0x0008'A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4, ICU::VECTOR::TEI4,
		ICU::GROUP12, ICU::GROUP12::ERI4> SCI4;
	typedef scic_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5, ICU::VECTOR::TEI5, 
		ICU::GROUP12, ICU::GROUP12::ERI5> SCI5;
	typedef scic_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6, ICU::VECTOR::TEI6,
		ICU::GROUP12, ICU::GROUP12::ERI6> SCI6;
	typedef scic_t<0x0008'A0E0, peripheral::SCI7, ICU::VECTOR::TXI7, ICU::VECTOR::RXI7, ICU::VECTOR::TEI7,
		ICU::GROUP12, ICU::GROUP12::ERI7> SCI7;
	typedef scic_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8, ICU::VECTOR::TEI8,
		ICU::GROUP12, ICU::GROUP12::ERI8> SCI8;
	typedef scic_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9, ICU::VECTOR::TEI9, 
		ICU::GROUP12, ICU::GROUP12::ERI9> SCI9;
	typedef scic_t<0x0008'A140, peripheral::SCI10, ICU::VECTOR::TXI10, ICU::VECTOR::RXI10, ICU::VECTOR::TEI10,
		ICU::GROUP12, ICU::GROUP12::ERI10> SCI10;
	typedef scic_t<0x0008'A160, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11, ICU::VECTOR::TEI11,
		ICU::GROUP12, ICU::GROUP12::ERI11> SCI11;
	typedef scic_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12, ICU::VECTOR::TEI12,
		ICU::GROUP12, ICU::GROUP12::ERI12> SCI12;
#elif defined(SIG_RX63T)
	typedef scic_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0, ICU::VECTOR::TEI0,
		ICU::GROUP12, ICU::GROUP12::ERI0> SCI0;
	typedef scic_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1, ICU::VECTOR::TEI1, 
		ICU::GROUP12, ICU::GROUP12::ERI1> SCI1;
	typedef scic_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2, ICU::VECTOR::TEI2,
		ICU::GROUP12, ICU::GROUP12::ERI2> SCI2;
	typedef scic_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3, ICU::VECTOR::TEI3,
		ICU::GROUP12, ICU::GROUP12::ERI3> SCI3;
#endif
}
