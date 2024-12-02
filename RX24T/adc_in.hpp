#pragma once
//=========================================================================//
/*!	@file
	@brief	RX1xx/RX2xx S12ADE 系 A/D 変換制御 @n
			・RX130 @n
			・RX140 @n
			・RX230/RX231 @n
			・RX260/RX261 @n
			start() ---> enable() ---> scan() の順番で変換を行う
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "common/intr_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADE A/D 制御クラス
		@param[in]	ADCU	A/D チャネル・ユニット
		@param[in]	TASK	割り込みタスククラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ADCU, class TASK = utils::null_task>
	struct adc_in {

		typedef ADCU value_type;

		enum class SCAN_MODE : uint8_t {
			SINGLE     = 0b00,	///< シングルスキャンモード
			GROUP      = 0b01,	///< グループスキャンモード
			CONTINUOUS = 0b10,	///< 連続スキャンモード
		};

		enum class GROUP : uint8_t {
			A,		///< グループＡ
			B,		///< グループＢ
		};
#if defined(SIG_RX140)
		enum class CONV_CYCLE : uint8_t {
			_32,	///< 32 サイクル/bit（標準）
			_41,	///< 41 サイクル/bit
			_22,	///< 22 サイクル/bit
			_28,	///< 28 サイクル/bit
		};

		enum class VREFL_SEL : uint8_t {
			AVSS0,	///< 低電位基準電圧を AVSS0 を選択
			VREFL0	///< 低電位基準電圧を VREFL0 を選択
		};

		enum class VREFH_SEL : uint8_t {
			AVCC0,	///< 高電位基準電圧を AVCC0 を選択
			VREFH0	///< 高電位基準電圧を VREFH0 を選択
		};
#endif
	private:

		SCAN_MODE	scmd_;
#if defined(SIG_RX140)
		CONV_CYCLE	conv_cycle_;
		VREFL_SEL	vrefl_;
		VREFH_SEL	vrefh_;
#endif
		static inline TASK task_;

		static INTERRUPT_FUNC void adi_task_()
		{
			task_();
		}

		static inline void sleep_() { asm("nop"); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		adc_in() noexcept :
			scmd_(SCAN_MODE::SINGLE)
#if defined(SIG_RX140)
			, conv_cycle_(CONV_CYCLE::_32),
			vrefl_(VREFL_SEL::VREFL0),
			vrefh_(VREFH_SEL::VREFH0)
#endif
		{ }

#if defined(SIG_RX140)
		//-----------------------------------------------------------------//
		/*!
			@brief	変換サイクルの指定
			@param[in]	cnvcyc	変換サイクル型
		 */
		//-----------------------------------------------------------------//
		void set(CONV_CYCLE cnvcyc) noexcept { conv_cycle_ = cnvcyc; }


		//-----------------------------------------------------------------//
		/*!
			@brief	低電位基準電圧指定
			@param[in]	vref	低電位基準電圧型
		 */
		//-----------------------------------------------------------------//
		void set(VREFL_SEL vref) noexcept { vrefl_ = vref; }


		//-----------------------------------------------------------------//
		/*!
			@brief	高電位基準電圧指定
			@param[in]	vref	高電位基準電圧型
		 */
		//-----------------------------------------------------------------//
		void set(VREFH_SEL vref) noexcept { vrefh_ = vref; }
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief	スタート
			@param[in]	scmd	スキャンモード
			@param[in]	level	割り込みレベル、０の場合はポーリング
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(SCAN_MODE scmd, ICU::LEVEL level = ICU::LEVEL::NONE) noexcept
		{
			scmd_ = scmd;

			power_mgr::turn(ADCU::PERIPHERAL);
#if defined(SIG_RX140)
			// 基準電圧の指定
			ADCU::ADHVREFCNT.HVSEL = static_cast<uint8_t>(vrefh_);
			ADCU::ADHVREFCNT.LVSEL = static_cast<uint8_t>(vrefl_);

			// 変換サイクルの設定
			ADCU::ADHVREFCNT.ADSLP = 1;
			utils::delay::micro_second(1);
			ADCU::ADCSR.ADHSC = static_cast<uint8_t>(conv_cycle_) & 1;
			ADCU::ADCCR.CCS = (static_cast<uint8_t>(conv_cycle_) >> 1) & 1;
			utils::delay::micro_second(5);
			ADCU::ADHVREFCNT.ADSLP = 0;
#endif
			//　スキャンモードの指定
			ADCU::ADCSR.ADCS = static_cast<uint8_t>(scmd);

			if(level != device::ICU::LEVEL::NONE) {
				icu_mgr::set_task(ADCU::ADI, adi_task_);
				icu_mgr::set_level(ADCU::ADI, level);
				ADCU::ADCSR.ADIE = 1;
			} else {
				ADCU::ADCSR.ADIE = 0;
				icu_mgr::set_level(ADCU::ADI, ICU::LEVEL::NONE);
				icu_mgr::set_task(ADCU::ADI, nullptr);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	変換アナログチャネルの設定、解除
			@param[in]	ana		アナログチャネル型
			@param[in]	grp		グループ型
			@param[in]	ena		不許可の場合「false」
		 */
		//-----------------------------------------------------------------//
		void enable(typename ADCU::ANALOG ana, GROUP grp = GROUP::A, bool ena = true) noexcept
		{
			ADCU::enable(ana, ena);
			if(!ena) {
				return;
			}

			if(ADCU::ADCSR.ADCS() != 0b01) {  // グループスキャン以外
				grp = GROUP::A;
			}

			switch(grp) {
			case GROUP::A:
				ADCU::ADANSA.set(ana);
				break;
			case GROUP::B:
				ADCU::ADANSB.set(ana);
				break;
			}

			// サンプリングステート値
			uint32_t n = ADCU::PCLK * 1000 / 1'000'000;
			n += ADCU::CONV_TIME_NS - 1;
			n /= ADCU::CONV_TIME_NS;
			if(n > 255) n = 255;
			ADCU::ADSSTR.set(ana, n);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	スキャン開始
		 */
		//-----------------------------------------------------------------//
		void scan() noexcept
		{
			if(ADCU::ADCSR.ADST()) {
				sync();
			}
			ADCU::ADCSR.ADST = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	変換状態の取得
			@return 変換中なら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_state() const noexcept
		{
			return ADCU::ADCSR.ADST();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	変換終了を待つ
		 */
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			while(ADCU::ADCSR.ADST() != 0) sleep_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換結果を取得
			@param[in]	ana		変換チャネル
			@return 変換結果（上位１０・１２ビットが有効な値）
		 */
		//-----------------------------------------------------------------//
		uint16_t get(typename ADCU::ANALOG ana) const noexcept
		{
			return ADCU::ADDR(ana);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	停止
		 */
		//-----------------------------------------------------------------//
		void stop() noexcept
		{
			ADCU::ADCSR.ADST = 0;
			ADCU::ADANSA0 = 0;
			ADCU::ADANSA1 = 0;
			ADCU::ADANSB0 = 0;
			ADCU::ADANSB1 = 0;
			power_mgr::turn(ADCU::PERIPHERAL, false);
		}
	};
}
