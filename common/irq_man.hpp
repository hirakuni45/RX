#pragma once
//=========================================================================//
/*!	@file
	@brief	IRQ マネージャー @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
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
		static uint8_t level_;

		static INTERRUPT_FUNC void irq_task_()
		{
			switch(PER) {
			case peripheral::IRQ0:
				ICU::IER.IRQ0 = 0;
				ICU::IR.IRQ0  = 0;
				break;
			case peripheral::IRQ1:
				ICU::IER.IRQ1 = 0;
				ICU::IR.IRQ1  = 0;
				break;
			case peripheral::IRQ2:
				ICU::IER.IRQ2 = 0;
				ICU::IR.IRQ2  = 0;
				break;
			case peripheral::IRQ3:
				ICU::IER.IRQ3 = 0;
				ICU::IR.IRQ3  = 0;
				break;
			case peripheral::IRQ4:
				ICU::IER.IRQ4 = 0;
				ICU::IR.IRQ4  = 0;
				break;
			case peripheral::IRQ5:
				ICU::IER.IRQ5 = 0;
				ICU::IR.IRQ5  = 0;
				break;
			case peripheral::IRQ6:
				ICU::IER.IRQ6 = 0;
				ICU::IR.IRQ6  = 0;
				break;
			case peripheral::IRQ7:
				ICU::IER.IRQ7 = 0;
				ICU::IR.IRQ7  = 0;
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
		bool start(uint8_t lvl, edge egt, port_map::option opt)
		{
			icu_mgr::set_level(PER, 0);

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

			uint32_t vec = static_cast<uint32_t>(ICU::VECTOR::IRQ0);
			vec += static_cast<uint32_t>(PER) - static_cast<uint32_t>(peripheral::IRQ0);
			icu_mgr::set_task(static_cast<ICU::VECTOR>(vec), irq_task_);

			level_ = lvl;

			icu_mgr::set_level(PER, level_);

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
				ICU::IR.IRQ0  = 0;
				ICU::IER.IRQ0 = ena;
				break;
			case peripheral::IRQ1:
				ICU::IR.IRQ1  = 0;
				ICU::IER.IRQ1 = ena;
				break;
			case peripheral::IRQ2:
				ICU::IR.IRQ2  = 0;
				ICU::IER.IRQ2 = ena;
				break;
			case peripheral::IRQ3:
				ICU::IR.IRQ3  = 0;
				ICU::IER.IRQ3 = ena;
				break;
			case peripheral::IRQ4:
				ICU::IR.IRQ4  = 0;
				ICU::IRQFLTE0.FLTEN4 = 1;
				ICU::IER.IRQ4 = ena;
				break;
			case peripheral::IRQ5:
				ICU::IR.IRQ5  = 0;
				ICU::IER.IRQ5 = ena;
				break;
			case peripheral::IRQ6:
				ICU::IR.IRQ6  = 0;
				ICU::IER.IRQ6 = ena;
				break;
			case peripheral::IRQ7:
				ICU::IR.IRQ7  = 0;
				ICU::IER.IRQ7 = ena;
				break;
			}
		}
	};

	template <peripheral PER, class TASK> TASK irq_man<PER, TASK>::task_;
	template <peripheral PER, class TASK> uint8_t irq_man<PER, TASK>::level_ = 0;
}
