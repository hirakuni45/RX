#pragma once
//=====================================================================//
/*!	@file
	@brief	ディレクトリ・リスト・クラス @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include <functional>
#include "common/format.hpp"
#include "common/string_utils.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SD カード・ディレクトリー・リスト・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class dir_list {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DIR リスト関数型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef std::function<void (const char* name, const FILINFO* fi, bool dir, void* option)> loop_func;


	private:
		DIR			dir_;
		uint32_t	total_;
		char		nmb_[256];

		bool		init_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		dir_list() noexcept : dir_(), total_(0), nmb_{ 0 }, init_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	プローブ（状態）
			@return 取得中なら「true」
		 */
		//-----------------------------------------------------------------//
		bool probe() const noexcept { return init_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル数を取得
			@return ファイル数
		 */
		//-----------------------------------------------------------------//
		uint32_t get_total() const noexcept { return total_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ディレクトリーリスト開始 @n
					※「probe()」関数が「false」になるまで「service()」を呼ぶ
			@param[in]	root	ルート・パス
			@return エラー無ければ「true」
		 */
		//-----------------------------------------------------------------//
		bool start(const char* root) noexcept
		{
			total_ = 0;

			auto st = f_opendir(&dir_, root);
			if(st != FR_OK) {
				return false;
			}

			init_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	取得を停止する
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool stop() noexcept
		{
			if(!init_) return false;

			init_ = false;
			f_closedir(&dir_);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ディレクトリーリスト、ループ
			@param[in]	num		ループ回数
			@param[in]	func	実行関数
			@param[in]	todir  「true」の場合、ディレクトリーも関数を呼ぶ
			@param[in]	option	オプション・ポインター
			@return エラー無ければ「true」
		 */
		//-----------------------------------------------------------------//
		bool service(uint32_t num, loop_func func, bool todir = false, void* option = nullptr) noexcept
		{
			if(!init_) return false;

			for(uint32_t i = 0; i < num; ++i) {
				FILINFO fi;
				// Read a directory item
				if(f_readdir(&dir_, &fi) != FR_OK) {
					init_ = false;
					return false;
				}
				if(!fi.fname[0]) {
					stop();
					break;
				}

				if(func) {
					std::strcpy(nmb_, fi.fname);
					if(fi.fattrib & AM_DIR) {
						if(todir) {
							func(nmb_, &fi, true, option);
						}
					} else {
						func(nmb_, &fi, false, option);
					}
				}
				++total_;
			}
			return true;
		}
	};
}
