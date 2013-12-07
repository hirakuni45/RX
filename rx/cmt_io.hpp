#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621, RX63T グループ・CMT I/O 制御 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "cmt.hpp"
#include "rx63x/system.hpp"
#include "rx63x/icu.hpp"
#include "vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT I/O クラス
		@param[in]	CMTx	CMT チャネルクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMTx>
	class cmt_io {

		uint32_t	clock_;

		void sleep_() { }

		static volatile uint32_t counter_;
		static void (*task_)();
		static INTERRUPT_FUNC void cmt_task_() {
			++counter_;
			if(task_) (*task_)();
			switch(CMTx::get_chanel()) {
			case 0:
				ICU::IR.CMI0 = 0;
				break;
			case 1:
				ICU::IR.CMI1 = 0;
				break;
			case 2:
				ICU::IR.CMI2 = 0;
				break;
			case 3:
				ICU::IR.CMI3 = 0;
				break;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		cmt_io() : clock_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  ベースクロックの設定
			@param[in]	clock	ベース周波数
		*/
		//-----------------------------------------------------------------//
		void set_clock(uint32_t clock) { clock_ = clock; }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool initialize(uint32_t freq, uint8_t level) const {
			if(freq == 0 || clock_ == 0) return false;

			uint32_t cmcor = clock_ / freq / 8;
			uint8_t cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 2;
				++cks;
			}
			if(cks > 3 || cmcor == 0) {
				return false;
			}

			uint32_t chanel = CMTx::get_chanel();
			task_ = 0;
			switch(chanel) {
			case 0:
				set_interrupt_task(cmt_task_, ICU::VECTOR::CMI0);
				CMTx::CMSTR0.STR0 = 0;
				SYSTEM::MSTPCRA.MSTPA15 = 0;
				ICU::IPR.CMI0 = level;
				ICU::IER.CMI0 = true;
				ICU::IR.CMI0 = 0;
				break;
			case 1:
				CMTx::CMSTR0.STR1 = 0;
				SYSTEM::MSTPCRA.MSTPA15 = 0;
				set_interrupt_task(cmt_task_, ICU::VECTOR::CMI1);
				ICU::IPR.CMI1 = level;
				ICU::IER.CMI1 = true;
				ICU::IR.CMI1 = 0;
				break;
			case 2:
				CMTx::CMSTR1.STR2 = 0;
				SYSTEM::MSTPCRA.MSTPA14 = 0;
				set_interrupt_task(cmt_task_, ICU::VECTOR::CMI2);
				ICU::IPR.CMI2 = level;
				ICU::IER.CMI2 = true;
				ICU::IR.CMI2 = 0;
				break;
			case 3:
				CMTx::CMSTR1.STR3 = 0;
				SYSTEM::MSTPCRA.MSTPA14 = 0;
				set_interrupt_task(cmt_task_, ICU::VECTOR::CMI3);
				ICU::IPR.CMI3 = level;
				ICU::IER.CMI3 = true;
				ICU::IR.CMI3 = 0;
				break;
			}

		    CMTx::CMCR = CMTx::CMCR.CMIE.b() | CMTx::CMCR.CKS.b(cks);
		    CMTx::CMCOR = cmcor - 1;

			switch(chanel) {
			case 0:
			    CMTx::CMSTR0.STR0 = 1;
				break;
			case 1:
			    CMTx::CMSTR0.STR1 = 1;
				break;
			case 2:
			    CMTx::CMSTR1.STR2 = 1;
				break;
			case 3:
			    CMTx::CMSTR1.STR3 = 1;
				break;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みタスクを設定
			@param[in]	task	設定タスク
		*/
		//-----------------------------------------------------------------//
		void set_task(void (*task)()) const {
			cmt_task_ = task;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() {
			volatile uint32_t cnt = counter_;
			while(cnt == counter_) ;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を取得
		*/
		//-----------------------------------------------------------------//
		uint32_t get_count() const {
			return counter_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CMT カウンターの値を取得
		*/
		//-----------------------------------------------------------------//
		uint16_t get_cmt_count() const {
			return CMTx::CMCNT();
		}
	};

	template <class CMTx> volatile uint32_t cmt_io<CMTx>::counter_;
	template <class CMTx> void (*cmt_io<CMTx>::task_)();
}
