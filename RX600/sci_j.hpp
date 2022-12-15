#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCIj 定義
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
		@brief  SCIj クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		typename ICUT, ICUT tei, ICUT eri>
	struct scij_t : public sci_gj_t<base> {

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
		static constexpr bool SEMR_ABCSE = true;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF  = true;		///< SSR.RDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB   = true;		///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB   = true;		///< 簡易 SPI が利用可能な場合「true」
	};

#if defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef scij_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1> SCI1;
	typedef scij_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5> SCI5;
	typedef scij_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6> SCI6;
	typedef scij_t<0x0008'A100, peripheral::SCI8, ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI8, ICU::GROUPBL1::ERI8> SCI8;
	typedef scij_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::GROUPBL1, ICU::GROUPBL1::TEI9, ICU::GROUPBL1::ERI9> SCI9;
#elif defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef scij_t<0x0008'A000, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI0, ICU::GROUPBL0::ERI0> SCI0;
	typedef scij_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI1, ICU::GROUPBL0::ERI1> SCI1;
	typedef scij_t<0x0008'A040, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI2, ICU::GROUPBL0::ERI2> SCI2;
	typedef scij_t<0x0008'A060, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI3, ICU::GROUPBL0::ERI3> SCI3;
	typedef scij_t<0x0008'A080, peripheral::SCI4, ICU::VECTOR::TXI4, ICU::VECTOR::RXI4,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI4, ICU::GROUPBL0::ERI4> SCI4;
	typedef scij_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI5, ICU::GROUPBL0::ERI5> SCI5;
	typedef scij_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::GROUPBL0, ICU::GROUPBL0::TEI6, ICU::GROUPBL0::ERI6> SCI6;
#endif
}
