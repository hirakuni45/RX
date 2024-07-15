#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCIh 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/sci_e.hpp"

namespace device {

#if defined(SIG_RX13T) || defined(SIG_RX140) || defined(SIG_RX231)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIh 定義クラス（通常ベクター版）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		ICU::VECTOR tei, ICU::VECTOR eri>
	struct scih_t : public sci_gj_t<base>, sci_ext_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKB;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME = true;		///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM = true;		///< SEMR.BGDM  が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN = true;		///< SEMR.NFEN　が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = false;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF  = true;		///< SSR.RDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB   = true;		///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB   = true;		///< 簡易 SPI が利用可能な場合「true」
	};

	typedef scih_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::VECTOR::TEI12, ICU::VECTOR::ERI12> SCI12;
#elif defined(SIG_RX26T) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX660) || defined(SIG_RX671) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIh 定義クラス（通常ベクター、グループベクター版）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
		@param[in]	pclk	PCLK 周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		ICU::GROUPBL0 tei, ICU::GROUPBL0 eri>
	struct scih_t : public sci_gj_t<base>, sci_ext_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKB;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME = true;		///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM = true;		///< SEMR.BGDM  が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN = true;		///< SEMR.NFEN　が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = false;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF  = true;		///< SSR.RDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB   = true;		///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB   = true;		///< 簡易 SPI が利用可能な場合「true」
	};

	typedef scih_t<0x0008'B300, peripheral::SCI12, ICU::VECTOR::TXI12, ICU::VECTOR::RXI12,
		ICU::GROUPBL0::TEI12, ICU::GROUPBL0::ERI12> SCI12;
#endif
}
