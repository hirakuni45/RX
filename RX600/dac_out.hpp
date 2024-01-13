#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T/RX64M/RX71M/RX72M/RX65N/RX66T/RX72T/RX72N グループ D/A 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  D/A 制御クラス
		@param[in]	DAC		D/A デバイス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class DAC>
	class dac_out {
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	出力タイプ
		 */
		//-----------------------------------------------------------------//
		enum class output : uint8_t {
			NONE,	///< 出力禁止
			CH0,	///< チャネル０
			CH1,	///< チャネル１
			CH0_CH1	///< チャネル０、１
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		dac_out() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	スタート @n
					※RX66T は ampe は機能なし。
			@param[in]	otype	出力タイプ
			@param[in]	ampe	アンプ許可の場合「true」
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(output otype, bool ampe) const noexcept
		{
			if(otype == output::NONE) {
				power_mgr::turn(DAC::PERIPHERAL);
				DAC::DACR.DAE = 0;
				DAC::DACR = DAC::DACR.DAE.b(0) | DAC::DACR.DAOE0.b(0) | DAC::DACR.DAOE1.b(0);
				power_mgr::turn(DAC::PERIPHERAL, false);
				return true;
			}

			power_mgr::turn(DAC::PERIPHERAL);

			DAC::DADPR.DPSEL = 1;  // 左詰め（下位４ビット無視）

			DAC::DACR.DAE = 0;

			bool ch0 = false;
			bool ch1 = false;
			if(otype == output::CH0) {
				ch0 = true;
			} else if(otype == output::CH1) {
				ch1 = true;
			} else if(otype == output::CH0_CH1) {
				ch0 = true;
				ch1 = true;
			} else {
				return false;
			}

			if(ch0) {
				DAC::DACR.DAOE0 = 1;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
				DAC::DAAMPCR.DAAMP0 = ampe;
#elif defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
				DAC::DADSELR.OUTDA0 = 1;
#endif
				DAC::enable(DAC::ANALOG::DA0);
			}
			if(ch1) {
				DAC::DACR.DAOE1 = 1;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
				DAC::DAAMPCR.DAAMP1 = ampe;
#elif defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
				DAC::DADSELR.OUTDA1 = 1;
#endif
				DAC::enable(DAC::ANALOG::DA1);
			}

			utils::delay::micro_second(3);  // amp start setup time

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０（１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out0(uint16_t value) const noexcept
		{
			DAC::DADR0 = value;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０ポートアドレスの取得
			@return 電圧出力０ポートアドレス
		 */
		//-----------------------------------------------------------------//
		uint32_t get_out0_adr() const noexcept
		{
			return DAC::DARD0.address;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力１（１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out1(uint16_t value) const noexcept
		{
			DAC::DADR1 = value;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０ポートアドレスの取得
			@return 電圧出力０ポートアドレス
		 */
		//-----------------------------------------------------------------//
		uint32_t get_out1_adr() const noexcept
		{
			return DAC::DARD1.address;
		}
	};
}
