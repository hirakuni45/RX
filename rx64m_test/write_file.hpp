#pragma once
//=====================================================================//
/*! @file
    @brief  ファイル書き込みクラス@n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cstring>
#include "common/fifo.hpp"
// #include "main.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  write_file class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class write_file {

		uint32_t	limit_;
		uint32_t	count_;

		char		path_[128];

		bool		enable_;
		bool		state_;

		static const uint32_t BUF_SIZE = 64;

		typedef utils::fifo<uint16_t, BUF_SIZE, sample_t> FIFO;
		FIFO	fifo_;

		FILE	*fp_;

		time_t		time_ref_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		write_file() : limit_(60), count_(0), path_{ "test.csv" },
			enable_(false), state_(false),
			fp_(nullptr), time_ref_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み許可
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) { enable_ = ena; }


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み許可取得
			@return 書き込み許可
		*/
		//-----------------------------------------------------------------//
		bool get_enable() const { return enable_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込みパス設定
			@param[in]	path	ファイルパス
		*/
		//-----------------------------------------------------------------//
		void set_path(const char* path)
		{
			strcpy(path_, path);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込みパス取得
			@param[in]	path	ファイルパス
		*/
		//-----------------------------------------------------------------//
		const char* get_path() const { return path_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み回数の設定
			@param[in]	limit	書き込み回数
		*/
		//-----------------------------------------------------------------//
		void set_limit(uint32_t limit)
		{
			limit_ = limit;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み時間設定
			@return	書き込み時間（秒）
		*/
		//-----------------------------------------------------------------//
		uint32_t get_limit() const { return limit_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  経過時間の取得
			@return 経過時間
		*/
		//-----------------------------------------------------------------//
		uint32_t get_resume() const { return count_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  インジェクション
			@param[in]	data	データ
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool injection(const sample_t& data)
		{
			if(fifo_.length() >= (BUF_SIZE -2)) { // スペースが無い場合
				return false;
			}
			fifo_.put(data);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			bool back = state_;
			state_ = enable_;
			if(!enable_) {
				if(back && fp_ != nullptr) {
					utils::format("Write file aborted\n");
					fclose(fp_);
					fp_ = nullptr;
				}
				return;
			}

			{
				time_t t = get_time();
				if(time_ref_ != t) {
					time_ref_ = t;
					for(int i = 0; i < 8; ++i) {
						at_sample(i).time_ = t;
						at_sample(i).ch_ = i;
						fifo_.put(get_sample(i));
					}
//					utils::format("Write data injection...\n");
				}
			}

			if(fp_ == nullptr) {
				fp_ = fopen(path_, "wb");
				count_ = 0;
				if(fp_ == nullptr) {  // error then disable write.
					utils::format("File open error: '%s'\n") % path_;
					enable_ = false;
				} else {
					utils::format("Start write file: '%s'\n") % path_;
				}
				return;
			}

			if(fifo_.length() == 0) return;

			sample_t t = fifo_.get();
			char tmp[256];
			if(t.ch_ == 0) {
				auto tsz = disp_time(t.time_, tmp, sizeof(tmp));
				tmp[tsz] = '\n';
				++tsz;
				fwrite(tmp, 1, tsz, fp_);
			}

			int sz = t.make_csv("\n", tmp, sizeof(tmp));
			fwrite(tmp, 1, sz, fp_);
//			utils::format("Write ch: %d\n") % t.ch_;

			if(t.ch_ == 7) {  // last channnel
				++count_;
				if(count_ >= limit_) {
					fclose(fp_);
					fp_ = nullptr;
					utils::format("Close write file: %d sec\n") % count_;
					enable_ = false;
				}
			}
		}
	};
}
