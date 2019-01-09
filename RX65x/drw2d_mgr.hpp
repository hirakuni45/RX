#pragma once
//=====================================================================//
/*!	@file
	@brief	RX65N/RX651 DRW2D マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX65x/drw2d.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DRW2D 制御／マネージャー
		@param[in]	DRW		DRW2D クラス
		@param[in]	XSIZE	X 方向ピクセルサイズ
		@param[in]	YSIZE	Y 方向ピクセルサイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class DRW, int16_t XSIZE, int16_t YSIZE>
	class drw2d_mgr {

		uint32_t	fba_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		*/
		//-----------------------------------------------------------------//
		drw2d_mgr() noexcept : fba_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ハードウェアーバージョンを取得
			@return ハードウェアーバージョン
		*/
		//-----------------------------------------------------------------//
		uint16_t get_version() const noexcept { return DRW::HWVER.REV(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	ハードウェアー仕様の表示
		*/
		//-----------------------------------------------------------------//
		void list_info() const noexcept
		{
			utils::format("REV:             0x%03X\n") % get_version();
			utils::format("Alpha Blend:       %d\n") % static_cast<uint16_t>(DRW::HWVER.ACBLD());
			utils::format("Clomakey:          %d\n") % static_cast<uint16_t>(DRW::HWVER.COLKEY());
			utils::format("Texture CLUT:      %s\n") % (DRW::HWVER.TEXCLUT256() ? "256" : "16");
			utils::format("RLE unit:          %d\n") % static_cast<uint16_t>(DRW::HWVER.RLEUNIT());
			utils::format("Texture CLUT func: %d\n") % static_cast<uint16_t>(DRW::HWVER.TEXCLUT());
			utils::format("Pefrmance CNT:     %d\n") % static_cast<uint16_t>(DRW::HWVER.PERFCNT());
			utils::format("Texture CASH:      %d\n") % static_cast<uint16_t>(DRW::HWVER.TXCACHE());
			utils::format("FB CASH:           %d\n") % static_cast<uint16_t>(DRW::HWVER.FBCACHE());
			utils::format("Display List R:    %d\n") % static_cast<uint16_t>(DRW::HWVER.DLR());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	fba		フレーム・バッファ・アドレス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t fba) noexcept
		{
			// DRW2D power management
			power_mgr::turn(DRW::get_peripheral());

			DRW::SIZE.X = XSIZE;
			DRW::SIZE.Y = YSIZE;

			fba_ = fba;




			return true;
		}


	};
}
