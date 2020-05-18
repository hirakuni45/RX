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
			@param[in]	base		ベース・アドレス
			@param[in]	VECTOR		割り込みベクター型
			@param[in]	INTR_SEL	割り込み要因型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, typename VECTOR, typename INTR_SEL>
		struct slixr_t {

			void set(VECTOR vec, INTR_SEL sel) noexcept {
				wr8_(base + static_cast<uint8_t>(vec), static_cast<uint8_t>(sel));
			}

			INTR_SEL get(VECTOR vec) noexcept {
				return static_cast<INTR_SEL>(rd8_(base + static_cast<uint8_t>(vec)));
			}

			volatile INTR_SEL& operator [] (VECTOR vec) {
				return *reinterpret_cast<volatile INTR_SEL*>(base + static_cast<uint8_t>(vec));
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
