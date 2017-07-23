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
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"

// #define WRITE_FILE_DEBUG

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  write_file class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class write_file {

#ifdef WRITE_FILE_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		uint32_t	limit_;
		uint32_t	count_;

		char		path_[128];

		bool		enable_;
		bool		state_;

		static const uint32_t BUF_SIZE = 64;

		typedef utils::fixed_fifo<sample_t, BUF_SIZE> FIFO;
		FIFO	fifo_;

		FILE	*fp_;

		time_t	time_ref_;
		time_t	time_loop_;

		enum class task : uint8_t {
			wait_request,
			sync_first,
			make_filename,
			open_file,
			write_header,
			make_data,
			write_body,
			next_data,
			next_file,
		};

		task	task_;

		bool	last_data_;

		uint8_t	second_;

		char	filename_[256];

		char		data_[512];
		uint32_t	data_len_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		write_file() : limit_(5), count_(0), path_{ "00000" },
			enable_(false), state_(false),
			fp_(nullptr), time_ref_(0), time_loop_(0),
			task_(task::wait_request), last_data_(false), second_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み許可
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) {
			enable_ = ena;
			count_ = 0;
		}


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
			utils::sformat("%s", path_, sizeof(path_)) % path;
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
			@brief  サービス
			@param[in]	cycle	サービス・サイクル（通常１００Ｈｚ）
		*/
		//-----------------------------------------------------------------//
		void service(uint32_t cycle)
		{
			bool back = state_;
			state_ = enable_;
			if(!enable_) {
				if(back && fp_ != nullptr) {
					debug_format("Write file aborted\n");
					fclose(fp_);
					fp_ = nullptr;
					task_ = task::wait_request;
				}
				return;
			}

			// データを詰め込む
			const sample_data& smd = get_sample_data();
			bool sync = false;
			if(time_ref_ != smd.time_) {
				time_ref_ = smd.time_;
				sync = true;
			}

			switch(task_) {
			case task::wait_request:  // 書き込みトリガー検出
				if(enable_ && !back) {
					task_ = task::sync_first;
				}
				break;

			case task::sync_first:
				if(sync) {
					fifo_.clear();
					task_ = task::make_filename;
				}
				break;

			case task::make_filename:
				{
					time_loop_ = time_ref_;
					struct tm *m = localtime(&time_loop_);
					utils::sformat("%s_%04d%02d%02d%02d%02d.csv", filename_, sizeof(filename_))
						% path_
						% static_cast<uint32_t>(m->tm_year + 1900)
						% static_cast<uint32_t>(m->tm_mon + 1)
						% static_cast<uint32_t>(m->tm_mday)
						% static_cast<uint32_t>(m->tm_hour)
						% static_cast<uint32_t>(m->tm_min);
					task_ = task::open_file;
				}
				break;

			case task::open_file:
				fp_ = fopen(filename_, "wb");
				if(fp_ == nullptr) {  // error then disable write.
					debug_format("File open error: '%s'\n") % filename_;
					enable_ = false;
					task_ = task::wait_request;
				} else {
					debug_format("Start write file: '%s'\n") % filename_;
					task_ = task::write_header;
				}
				break;

			case task::write_header:
				{
					char data[1024];
					utils::sformat("DATE,TIME", data, sizeof(data));
					for(int i = 0; i < 8; ++i) {
						utils::sformat(",CH,MAX,MIN,AVE,MEDIAN,COUNTUP", data, sizeof(data), true);
					}
					utils::sformat("\n", data, sizeof(data), true);

					fwrite(data, 1, utils::sformat::chaout().size(), fp_);
					task_ = task::make_data;
				}
				break;

			case task::make_data:
				if(fifo_.length() > 0) {
					sample_t smp = fifo_.get();
					if(smp.ch_ == 0) {
						struct tm *m = localtime(&time_loop_);
						utils::sformat("%04d/%02d/%02d,%02d:%02d:%02d,", data_, sizeof(data_))
							% static_cast<uint32_t>(m->tm_year + 1900)
							% static_cast<uint32_t>(m->tm_mon + 1)
							% static_cast<uint32_t>(m->tm_mday)
							% static_cast<uint32_t>(m->tm_hour)
							% static_cast<uint32_t>(m->tm_min)
							% static_cast<uint32_t>(m->tm_sec);
						second_ = m->tm_sec;
					} else {
						utils::sformat(",", data_, sizeof(data_));
					}
					smp.make_csv2(data_, sizeof(data_), true);
					if(smp.ch_ == 7) {
						++time_loop_;
						utils::sformat("\n", data_, sizeof(data_), true);
						last_data_ = true;
					} else {
						last_data_ = false;
					}
					data_len_ = utils::sformat::chaout().size();
					task_ = task::write_body;
				}
				break;

			case task::write_body:
				fwrite(data_, 1, data_len_, fp_);
				if(last_data_) {
					if(second_ == 59) {  // change file.
						task_ = task::next_file;
					} else {
						task_ = task::make_data;
					}
				} else {
					task_ = task::make_data;
				}
				break;

			case task::next_file:
				fclose(fp_);
				fp_ = nullptr;
				++count_;
				if(count_ >= limit_) {
					fp_ = nullptr;
					debug_format("Fin write file: %d files\n") % count_;
					enable_ = false;
					task_ = task::wait_request;
				} else {
					task_ = task::make_filename;
				}
				break;

			default:
				break;
			}

			if(sync) {
				if((BUF_SIZE - fifo_.length()) > 8) {
					for(int i = 0; i < 8; ++i) {
						fifo_.put(smd.smp_[i]);
					}
				}
			}
		}
	};
}
