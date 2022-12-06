#pragma once
//=========================================================================//
/*!	@file
	@brief	IRQ マネージャー @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IRQ マネージャー・テンプレート・クラス
		@param[in]	PER		ペリフェラル型
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral PER, class TASK>
	class irq_man {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	入力エッジ・タイプ 
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class edge : uint8_t {
			LEVEL,		///< レベル（Low）
			NEGATIVE,	///< 立下りエッジ
			POSITIVE,	///< 立ち上がりエッジ
			ALL,		///< 両エッジ
		};

	private:
		static TASK	task_;
		static ICU::LEVEL level_;

		static INTERRUPT_FUNC void irq_task_()
		{
			switch(PER) {
			case peripheral::IRQ0:
				ICU::IER.enable(ICU::VECTOR::IRQ0, false);
				ICU::IR[ICU::VECTOR::IRQ0] = 0;
				break;
			case peripheral::IRQ1:
				ICU::IER.enable(ICU::VECTOR::IRQ1, false);
				ICU::IR[ICU::VECTOR::IRQ1] = 0;
				break;
			case peripheral::IRQ2:
				ICU::IER.enable(ICU::VECTOR::IRQ2, false);
				ICU::IR[ICU::VECTOR::IRQ2] = 0;
				break;
			case peripheral::IRQ3:
				ICU::IER.enable(ICU::VECTOR::IRQ3, false);
				ICU::IR[ICU::VECTOR::IRQ3] = 0;
				break;
			case peripheral::IRQ4:
				ICU::IER.enable(ICU::VECTOR::IRQ4, false);
				ICU::IR[ICU::VECTOR::IRQ4] = 0;
				break;
			case peripheral::IRQ5:
				ICU::IER.enable(ICU::VECTOR::IRQ5, false);
				ICU::IR[ICU::VECTOR::IRQ5] = 0;
				break;
			case peripheral::IRQ6:
				ICU::IER.enable(ICU::VECTOR::IRQ6, false);
				ICU::IR[ICU::VECTOR::IRQ6] = 0;
				break;
			case peripheral::IRQ7:
				ICU::IER.enable(ICU::VECTOR::IRQ7, false);
				ICU::IR[ICU::VECTOR::IRQ7] = 0;
				break;
			}
			task_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		irq_man() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  グループ割り込みを設定する @n
					※割り込みは「不許可」の状態
			@param[in]	lvl		割り込みレベル（０の場合、割り込み禁止）
			@param[in]	egt		エッジタイプ
			@param[in]	opt		ポート選択権
		*/
		//-----------------------------------------------------------------//
		bool start(ICU::LEVEL lvl, edge egt, port_map::ORDER opt)
		{
			auto vd = static_cast<uint32_t>(PER) - static_cast<uint32_t>(peripheral::IRQ0);
			auto vec = static_cast<ICU::VECTOR>(static_cast<uint32_t>(ICU::VECTOR::IRQ0) + vd);

			icu_mgr::set_level(vec, ICU::LEVEL::NONE);

			if(!port_map::turn(PER, true, opt)) {
				return false;
			}

			switch(PER) {
			case peripheral::IRQ0:
				ICU::IRQCR0.IRQMD = static_cast<uint8_t>(egt);
				break;
			case peripheral::IRQ1:
				ICU::IRQCR1.IRQMD = static_cast<uint8_t>(egt);
				break;
			case peripheral::IRQ2:
				ICU::IRQCR2.IRQMD = static_cast<uint8_t>(egt);
				break;
			case peripheral::IRQ3:
				ICU::IRQCR3.IRQMD = static_cast<uint8_t>(egt);
				break;
			case peripheral::IRQ4:
				ICU::IRQFLTE0.FLTEN4 = 0;
				ICU::IRQFLTC0.FCLKSEL4 = 3;
				ICU::IRQCR4.IRQMD = static_cast<uint8_t>(egt);
				break;
			case peripheral::IRQ5:
				ICU::IRQCR5.IRQMD = static_cast<uint8_t>(egt);
				break;
			case peripheral::IRQ6:
				ICU::IRQCR6.IRQMD = static_cast<uint8_t>(egt);
				break;
			case peripheral::IRQ7:
				ICU::IRQCR7.IRQMD = static_cast<uint8_t>(egt);
				break;
			default:
				return false;
			}

			
			icu_mgr::set_task(vec, irq_task_);

			level_ = lvl;

			icu_mgr::set_level(vec, level_);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  許可／不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			switch(PER) {
			case peripheral::IRQ0:
				ICU::IR[ICU::VECTOR::IRQ0] = 0;
				ICU::IER.enable(ICU::VECTOR::IRQ0, ena);
				break;
			case peripheral::IRQ1:
				ICU::IR[ICU::VECTOR::IRQ1] = 0;
				ICU::IER.enable(ICU::VECTOR::IRQ1, ena);
				break;
			case peripheral::IRQ2:
				ICU::IR[ICU::VECTOR::IRQ2] = 0;
				ICU::IER.enable(ICU::VECTOR::IRQ2, ena);
				break;
			case peripheral::IRQ3:
				ICU::IR[ICU::VECTOR::IRQ3] = 0;
				ICU::IER.enable(ICU::VECTOR::IRQ3, ena);
				break;
			case peripheral::IRQ4:
				ICU::IR[ICU::VECTOR::IRQ4] = 0;
				ICU::IRQFLTE0.FLTEN4 = 1;
				ICU::IER.enable(ICU::VECTOR::IRQ4, ena);
				break;
			case peripheral::IRQ5:
				ICU::IR[ICU::VECTOR::IRQ5] = 0;
				ICU::IER.enable(ICU::VECTOR::IRQ5, ena);
				break;
			case peripheral::IRQ6:
				ICU::IR[ICU::VECTOR::IRQ6] = 0;
				ICU::IER.enable(ICU::VECTOR::IRQ6, ena);
				break;
			case peripheral::IRQ7:
				ICU::IR[ICU::VECTOR::IRQ7] = 0;
				ICU::IER.enable(ICU::VECTOR::IRQ7, ena);
				break;
			}
		}
	};

	template <peripheral PER, class TASK> TASK irq_man<PER, TASK>::task_;
	template <peripheral PER, class TASK> ICU::LEVEL irq_man<PER, TASK>::level_ = ICU::LEVEL::NONE;
}
