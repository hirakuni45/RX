#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ D/A 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/power_cfg.hpp"
#include "RX600/icu_mgr.hpp"
#include "RX600/r12da.hpp"
#include "common/delay.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  D/A 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		dac_out() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	スタート
			@param[in]	otype	出力タイプ
			@param[in]	ampe	アンプ許可の場合「true」
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(output otype, bool ampe)
		{
			if(otype == output::NONE) {
				R12DA::DACR = R12DA::DACR.DAE.b(0) | R12DA::DACR.DAOE0.b(0) | R12DA::DACR.DAOE1.b(0);
				power_cfg::turn(R12DA::get_peripheral(), false);
				return true;
			}

			power_cfg::turn(R12DA::get_peripheral());

			R12DA::DADPR.DPSEL = 1;  // 左詰め（上位１２ビット無視）

			R12DA::DACR.DAE = 0;

			if(otype == output::CH0) {
				R12DA::DACR.DAOE0 = 1;
				R12DA::DAAMPCR.DAAMP0 = ampe;

				MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
				MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
				MPC::P03PFS.ASEL = 1;
				MPC::PWPR = device::MPC::PWPR.B0WI.b();
			} else if(otype == output::CH1) {
				R12DA::DACR.DAOE1 = 1;
				R12DA::DAAMPCR.DAAMP1 = ampe;

				MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
				MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
				MPC::P05PFS.ASEL = 1;
				MPC::PWPR = device::MPC::PWPR.B0WI.b();
			} else {
				return false;
			}

			utils::delay::micro_second(3);  // amp start setup time

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０（下位４ビットが無効な１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out0(uint16_t value)
		{
			R12DA::DADR0 = value;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力１（下位４ビットが無効な１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out1(uint16_t value)
		{
			R12DA::DADR1 = value;
		}
	};
}
