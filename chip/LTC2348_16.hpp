#pragma once
//=====================================================================//
/*!	@file
	@brief	LTC2348-16 ドライバー
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  LTC2348-16 シリアルデータ定義
		@param[in]	SDO0	SDO0 定義
		@param[in]	SDO2	SDO2 定義
		@param[in]	SDO4	SDO4 定義
		@param[in]	SDO5	SDO6 定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDO0, class SDO2, class SDO4, class SDO6>
	struct LTC2348_SDO_t {
		SDO0	sdo0_;
		SDO2	sdo2_;
		SDO4	sdo4_;
		SDO6	sdo6_;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  LTC2348-16 テンプレートクラス
		@param[in]	CSN		デバイス選択
		@param[in]	CNV		コンバート制御
		@param[in]	BUSY	ビジー信号
		@param[in]	SDI		制御入力
		@param[in]	SCKI	制御クロック
		@param[in]	SDO		シリアルデータ出力定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CSN, class CNV, class BUSY, class SDI, class SCKI, class SDO>
	class LTC2348_16 {
		CSN		csn_;
		CNV		cnv_;
		BUSY	busy_;
		SDI		sdi_;
		SCKI	scki_;
		SDO		sdo_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		LTC2349_16() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
		}

#if 0
// 標準的なSPIバス動作の場
// 合は、SCKIの立ち上がりエッジでレシーバの出力データを捕
// 捉してください。
#endif

	};
}
