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
			@brief	出力タイプ型
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
			@brief	基準電圧型（RX231 専用）
		 */
		//-----------------------------------------------------------------//
		enum class VREF : uint8_t {
			NONE = 0b000,		///< 非選択
			AVCC0 = 0b001,///< AVCC0/AVSS0
			INTERNAL = 0b011,	///< 内部基準電圧/AVSS0
			VREFH_VREFL = 0b110	///< VREFH/VREFL
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
					※RX231 の場合 vref は基準電圧選択 @n
					※RX66T の場合 ampe は機能なし。
			@param[in]	otype	出力タイプ
			@param[in]	ampe	アンプ許可の場合「true」
			@param[in]	vref	基準電圧選択
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(output otype, bool ampe, VREF vref = VREF::AVCC0) const noexcept
		{
			if(otype == output::NONE) {
				power_mgr::turn(DAC::PERIPHERAL);
				DAC::DACR = DAC::DACR.RESERVE.b(0b11111);
				power_mgr::turn(DAC::PERIPHERAL, false);
				return true;
			}

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

			power_mgr::turn(DAC::PERIPHERAL);

#if defined(SIG_RX231)
			{
				DAC::DAVREFCR.REF = static_cast<uint8_t>(vref);
				volatile auto tmp = DAC::DAVREFCR();
			}   
#endif

			if(DAC::DACR_DAE) {
				DAC::DACR = DAC::DACR.DAE.b(0) | DAC::DACR.RESERVE.b(0b11111);
			}

			DAC::DADPR.DPSEL = 1;  // 左詰め（下位４ビット無視）

			if(ch0) {
				DAC::DACR = DAC::DACR.DAOE0.b(1) | DAC::DACR.RESERVE.b(0b11111);
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
				DAC::DAAMPCR.DAAMP0 = ampe;
#elif defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
				DAC::DADSELR.OUTDA0 = 1;
#endif
				DAC::enable(DAC::ANALOG::DA0);
			}
			if(ch1) {
				DAC::DACR = DAC::DACR.DAOE1.b(1) | DAC::DACR.RESERVE.b(0b11111);
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
