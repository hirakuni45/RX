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
#include "main.hpp"
#include "common/format.hpp"

// #define WRITE_FILE_DEBUG

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  write_file class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class write_file {

		static const uint8_t OPEN_RETRY_LIMIT = 3;

#ifdef WRITE_FILE_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

///		uint32_t	limit_;
		uint32_t	count_;

		char		path_[128];

		bool		enable_;
		bool		state_;
		bool		req_close_;

		FILE	*fp_;

		uint32_t	ch_loop_;

		enum class task : uint8_t {
			wait_request,
			make_filename,
			make_dir_path,
			open_retry_wait,
			open_file,
			write_header,
			make_data,
			write_body,
			next_data,
			next_file,
		};

		task	task_;

		bool	last_channel_;
		uint8_t	second_;

		char	filename_[256];

		char		data_[512];
		uint32_t	data_len_;

		uint8_t		open_retry_;
		uint8_t		open_retry_delay_;


		void cancel_write_()
		{
			enable_ = false;
			task_ = task::wait_request;
//			logs_.add(get_time(), "*");
			at_pre().at().write_enable_ = false;
			at_pre().write();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		write_file() : count_(0), path_{ "/00000" },
			enable_(false), state_(false), req_close_(false),
			fp_(nullptr),
			ch_loop_(0),
			task_(task::wait_request), last_channel_(false), second_(0),
			open_retry_(OPEN_RETRY_LIMIT), open_retry_delay_(0)
			{ }


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
			if(path == nullptr) return;
			if(path[0] == '/') ++path;
			utils::sformat("/%s", path_, sizeof(path_)) % path;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込みパス取得
			@param[in]	path	ファイルパス
		*/
		//-----------------------------------------------------------------//
		const char* get_path() const { return path_; }


#if 0
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
#endif


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
			if(back && !state_ && fp_ != nullptr) {
				req_close_ = true;
			}

			switch(task_) {
			case task::wait_request:  // 書き込みトリガー検出
				if(enable_ && !back) {
					task_ = task::make_filename;
					reset_wf_fifo();
				}
				break;

			case task::make_filename:
				if(get_wf_fifo().length() > 0) {
					time_t t = get_wf_fifo().get_at().time_;
					struct tm *m = localtime(&t);
					utils::sformat("%s_%04d%02d%02d%02d%02d.csv", filename_, sizeof(filename_))
						% path_
						% static_cast<uint32_t>(m->tm_year + 1900)
						% static_cast<uint32_t>(m->tm_mon + 1)
						% static_cast<uint32_t>(m->tm_mday)
						% static_cast<uint32_t>(m->tm_hour)
						% static_cast<uint32_t>(m->tm_min);
					last_channel_ = false;
					second_ = 0;
					task_ = task::make_dir_path;
				}
				break;

			case task::make_dir_path:
				at_sdc().build_dir_path(filename_);
				task_ = task::open_file;
				break;

			case task::open_retry_wait:
				if(open_retry_delay_ > 0) {
					--open_retry_delay_;
				} else {
					task_ = task::open_file;
				}
				break;

			case task::open_file:
				if(!at_sdc().get_mount()) {
					debug_format("Write open: 'unmounted'\n");
					cancel_write_();
					break;					
				}
				fp_ = fopen(filename_, "wb");
				if(fp_ == nullptr) {  // error then disable write.
					char tmp[64];
					utils::sformat("File open error: '%s'", tmp, sizeof(tmp)) % filename_;
					debug_format("%s\n") % tmp;
					if(open_retry_ > 0) {
						--open_retry_;
						open_retry_delay_ = 60;
						debug_format("Write Open Retry: %d\n")
							% static_cast<uint32_t>(open_retry_);
						task_ = task::open_retry_wait;
					} else {
						at_logs().add(get_time(), "WOP");
						set_restart_delay(60 * 1);
						enable_ = false;
						task_ = task::wait_request;
					}
				} else {
///					at_logs().add(get_time(), "WOP");  // for log test
					debug_format("Start write file: '%s'\n") % filename_;
					open_retry_ = OPEN_RETRY_LIMIT;
					task_ = task::write_header;
				}
				break;

			case task::write_header:
				{
					if(!at_sdc().get_mount()) {
						debug_format("Write data header: 'unmounted'\n");
						cancel_write_();
						break;
					}
					char data[1024];
					utils::sformat("DATE,TIME", data, sizeof(data));
					for(uint32_t i = 0; i < get_channel_num(); ++i) {
						utils::sformat(",CH,MAX,MIN,AVE,MEDIAN,COUNTUP", data, sizeof(data), true);
					}
					utils::sformat("\n", data, sizeof(data), true);

					uint32_t sz = utils::sformat::chaout().size();
					uint32_t tl = 0;
					uint32_t loop = 0;
					while(tl < sz) {
						tl += fwrite(&data[tl], 1, sz - tl, fp_);
						if(loop > 0) {
							debug_format("Write data retry: %d/%d in header\n") % tl % sz;
						}
						++loop;
						if(loop >= 10) break;
					}
					if(sz != tl) {
						char tmp[64];
						utils::sformat("File write error (header): '%s'", tmp, sizeof(tmp))
							% filename_;
						at_logs().add(get_time(), "WR");
						debug_format("%s\n") % tmp;
						set_restart_delay(60 * 1);
						enable_ = false;
						task_ = task::wait_request;
						break;
					}
					task_ = task::make_data;
					ch_loop_ = 0;
				}
				break;

			case task::make_data:
				if(get_wf_fifo().length() > 0) {
					time_t t = get_wf_fifo().get_at().time_;
					if(ch_loop_ == 0) {
						struct tm *m = localtime(&t);
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
					const sample_t& smp = get_wf_fifo().get_at().smp_[ch_loop_];
					smp.make_csv2(data_, sizeof(data_), true);
					++ch_loop_;
					if(ch_loop_ >= get_channel_num()) {
						utils::sformat("\n", data_, sizeof(data_), true);
						ch_loop_ = 0;
						last_channel_ = true;
					} else {
						last_channel_ = false;
					}
					data_len_ = utils::sformat::chaout().size();
					task_ = task::write_body;
				}
				break;

			case task::write_body:
				if(get_wf_fifo().length() > 0) {
					if(!at_sdc().get_mount()) {
						debug_format("Write data body: 'unmounted'\n");
						cancel_write_();
						break;
					}
					uint32_t tl = 0;
					uint32_t loop = 0;
					while(tl < data_len_) {
						tl += fwrite(&data_[tl], 1, data_len_ - tl, fp_);
						if(loop > 0) {
							debug_format("Write data retry: %d/%d in body\n") % tl % data_len_;
						}
						++loop;
						if(loop >= 10) break;
					}
					if(tl != data_len_) {
						char tmp[64];
						utils::sformat("File write error (body): '%s'", tmp, sizeof(tmp))
							% filename_;
						at_logs().add(get_time(), "WR");
						debug_format("%s\n") % tmp;
						set_restart_delay(60 * 1); 
						enable_ = false;
						task_ = task::wait_request;
						break;
					}
					if(last_channel_) {
						at_wf_fifo().get_go();

						// 書き込みがキャンセルされた場合。
						if(req_close_) {
							req_close_ = false;
							debug_format("Write file aborted\n");
							fclose(fp_);
							fp_ = nullptr;
							task_ = task::wait_request;
							break;
						}

						if(second_ == 59) {  // change file.
							task_ = task::next_file;
						} else {
							task_ = task::make_data;
						}
					} else {
						task_ = task::make_data;
					}
				}
				break;

			case task::next_file:
				fclose(fp_);
				fp_ = nullptr;
				++count_;
/// 書き込み数制限を廃止
///				if(count_ >= limit_) {
///					debug_format("Fin write file: %d files\n")
///						% count_;
///					enable_ = false;
///					task_ = task::wait_request;
///				} else {
					task_ = task::make_filename;
///				}
				break;

			default:
				break;
			}
		}
	};
}
