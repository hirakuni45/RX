#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・ICU ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みユーティリテー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_utils {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み要因選択レジスタ・テンプレート
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct slixr_t {

			void set(uint16_t idx, uint8_t val) noexcept {
				wr8_(base + idx, val);
			}

			uint8_t get(uint16_t idx) noexcept {
				return rd8_(base + idx);
			}

			volatile uint8_t& operator [] (uint8_t idx) {
				return *reinterpret_cast<volatile uint8_t*>(base + idx);
			}
		};


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  選択型割り込みテンプレート
			@param[in]	vec		割り込み要因
			@param[in]	task	割り込みタスク
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		template <class ICU, typename VEC_TYPE, typename TASK_TYPE, uint8_t org, uint8_t end>
		typename ICU::VECTOR set_interrupt(VEC_TYPE vec, TASK_TYPE task, uint8_t lvl) noexcept
		{
			for(uint8_t i = org; i <= end; ++i) {
				if(lvl > 0) {
					if(ICU::SLIAR[i] == 0) {
						ICU::IER.enable(i, 0);
						set_task(static_cast<typename ICU::VECTOR>(i), task);
						ICU::IPR[i] = lvl;
						ICU::SLIXR[i] = static_cast<uint8_t>(vec);
						ICU::IR[i] = 0;
						ICU::IER.enable(i, 1);
						return static_cast<typename ICU::VECTOR>(i);
					}
				} else if(ICU::SLIAR[i] == static_cast<uint8_t>(vec)) {
					ICU::IER.enable(i, 0);
					set_task(static_cast<typename ICU::VECTOR>(i), nullptr);
					ICU::SLIXR[i] = 0;
					ICU::IR[i] = 0;
					return static_cast<typename ICU::VECTOR>(i);
				}
			}
			return ICU::VECTOR::NONE;
		}
#endif
	};
}
