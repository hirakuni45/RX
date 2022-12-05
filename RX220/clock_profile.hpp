#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義 @n
			RX220 は PLL 回路が無いので、外部にクリスタルを接続する場合、 @n
			最大 20MHz 動作となる。 @n
			外部クロック入力でも最大は 20MHz となる。 @n
			最大速度を出す場合は、HOCO を利用する事になる。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  クロック・プロファイル・クラス @n
				・選択出来ない値を指定すると、コンパイルエラーとなる @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					LOCO は、起動時のモードなので、設定する事はない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,	///< クリスタル接続（1～20MHz）
			CERA,	///< セラミック発振子リード品（16MHz ～ 20MHz）
			EXT,	///< 外部クロック入力（最大 20MHz）
			HOCO,	///< 内蔵高速オンチップオシレーター（BASE: 32MHz, 36.864MHz, 40MHz, 50MHz）
			LOCO,	///< 内蔵低速オンチップオシレーター (125KHz)
		};

		static constexpr auto       OSCT        = OSC_TYPE::HOCO;	///< オシレーターの選択
		static constexpr uint32_t   BASE		= 32'000'000;		///< ベースクロック

		static constexpr uint32_t   ICLK		= 32'000'000;		///< ICLK 周波数（最大32MHz）
		static constexpr uint32_t   PCLKA		= 0;				///< PCLKA（互換性の為定義）
		static constexpr uint32_t   PCLKB		= 32'000'000;		///< PCLKB 周波数（最大32MHz）
		static constexpr uint32_t	PCLKC		= 0;				///< PCLKC（互換性の為定義）
		static constexpr uint32_t   PCLKD		= 32'000'000;		///< PCLKD 周波数（最大32MHz）
		static constexpr uint32_t   FCLK		= 32'000'000;		///< FCLK 周波数（最大4 ～ 32MHz）

		static constexpr uint32_t	DELAY_MS	= ICLK / 4444444;	///< ソフトウェアー遅延における定数（1マイクロ秒）
		static constexpr bool		DELAY_T1	= false;			///< 微調整として、「nop」を１つ追加
	};
}
