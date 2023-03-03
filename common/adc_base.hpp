#pragma once
//=========================================================================//
/*!	@file
	@brief	A/D 変換共通クラス
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
		@brief  A/D 変換共通クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class adc_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換チャネルホルダーテンプレート
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename ANALOG>
		struct channels_t {

			uint16_t	channels_;

			//-------------------------------------------------------------//
			/*!
				@brief  コンストラクター
			*/
			//-------------------------------------------------------------//
			channels_t() noexcept : channels_(0) { }
 

 			//-------------------------------------------------------------//
			/*!
				@brief  セット
				@param[in]	an		アナログチャネル型
				@param[in]	on		不許可にする場合「false」		
			*/
			//-------------------------------------------------------------//
			void set(ANALOG an, bool on = true) noexcept
			{
				if(on) {
					channels_ |= 1 << static_cast<uint8_t>(an);
				} else {
					channels_ &= ~(1 << static_cast<uint8_t>(an));
				}
			}


 			//-------------------------------------------------------------//
			/*!
				@brief  取得
				@param[in]	an		アナログチャネル型
				@return 状態
			*/
			//-------------------------------------------------------------//
			bool get(ANALOG an) const noexcept
			{
				return (channels_ & (1 << static_cast<uint8_t>(an))) != 0;
			}


			bool operator() (ANALOG an) const noexcept
			{
				return get(an);
			}
		};
	};
}
