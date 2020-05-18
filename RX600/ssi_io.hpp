#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・SSI I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSI（シリアルサウンドインターフェース）基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ssi_io_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ビット列フォーマット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BFORM : uint8_t {
			I2S_16,		///< I2S 16 ビットフォーマット
			I2S_24,		///< I2S 24 ビットフォーマット
			I2S_32,		///< I2S 32 ビットフォーマット
			LEFT_16,	///< MSB 左詰め 16 ビットフォーマット
			LEFT_24,	///< MSB 左詰め 24 ビットフォーマット
			LEFT_32,	///< MSB 左詰め 32 ビットフォーマット
			RIGHT_16,	///< MSB 右詰め 16 ビットフォーマット
			RIGHT_24,	///< MSB 右詰め 24 ビットフォーマット
			RIGHT_32,	///< MSB 右詰め 32 ビットフォーマット
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSI（シリアルサウンドインターフェース）制御クラス
		@param[in]	SSI	ハードウェアーリソース
		@param[in]	DMAC		DMAC デバイス・コンテキスト(DMAC0 - DMAC7)
		@param[in]	SOUND_OUT	サウンド出力オブジェクト型
		@param[in]	MASTER		スレーブの場合「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SSI, class DMAC, class SOUND_OUT, bool MASTER = true>
	class ssi_io : public ssi_io_base {
	public:

		typedef SSI value_type;
		typedef DMAC dmac_type;

	private:

		SOUND_OUT&	sound_out_;

		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	sound_out	サウンド出力オブジェクト
		*/
		//-----------------------------------------------------------------//
		ssi_io(SOUND_OUT& sound_out) noexcept : sound_out_(sound_out)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始 @n
					※送信動作、受信動作、ミュート、初期状態を維持
			@param[in]	aclk	オーディオ入力周波数
			@param[in]	lrclk	LR クロック周波数（サンプルレート）
			@param[in]	bform	ビット列フォーマット
			@param[in]	intl	割り込みレベル
			@return 初期化出来ない場合「false」（パラメータの異常など）
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t aclk, uint32_t lrclk, BFORM bform, uint8_t intl) noexcept
		{
			power_mgr::turn(SSI::PERIPHERAL);

			if(!port_map::turn(SSI::PERIPHERAL, true)) {
				return false;
			}

			// ソフトリセット
			SSI::SSIFCR.SSIRST = 1;
			SSI::SSIFCR.SSIRST = 0;
			while(SSI::SSIFCR.SSIRST() != 0) {
				utils::delay::loop(1);
			}

			SSI::SSICR.SWSD = MASTER;
			SSI::SSICR.SCKD = MASTER;






			return true;
		}
	};
}

