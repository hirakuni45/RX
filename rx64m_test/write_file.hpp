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
#include "common/format.hpp"

// #define WF_DEBUG

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  write_file class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class write_file {

#ifdef WF_DEBUG
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
		write_file() : limit_(5), count_(0), path_{ "00000" },
			enable_(false), state_(false),
			fp_(nullptr), time_ref_(0) { }


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
					debug_format("Write file aborted\n");
					fclose(fp_);
					fp_ = nullptr;
				}
				return;
			}

			time_t t = get_time();
			{
				if(time_ref_ != t) {
					time_ref_ = t;
//					utils::format("Write data injection...\n");

					if(fp_ == nullptr) {
						struct tm *m = localtime(&time_ref_);
						char file[256];
						utils::sformat("%s_%04d%02d%02d%02d%02d.csv", file, sizeof(file))
							% path_
							% static_cast<uint32_t>(m->tm_year + 1900)
							% static_cast<uint32_t>(m->tm_mon + 1)
							% static_cast<uint32_t>(m->tm_mday)
							% static_cast<uint32_t>(m->tm_hour)
							% static_cast<uint32_t>(m->tm_min);
						fp_ = fopen(file, "wb");
						if(fp_ == nullptr) {  // error then disable write.
							debug_format("File open error: '%s'\n") % file;
							enable_ = false;
						} else {
							debug_format("Start write file: '%s'\n") % file;
						}
						char data[1024];
						utils::sformat("DATE,TIME", data, sizeof(data));
						for(int i = 0; i < 8; ++i) {
							utils::sformat(",CH,MAX,MIN,AVE,MEDIAN,COUNTUP", data, sizeof(data), true);
						}
						utils::sformat("\n", data, sizeof(data), true);

						fwrite(data, 1, utils::sformat::chaout().size(), fp_);
						fifo_.clear();
					}
					for(int i = 0; i < 8; ++i) {
						auto smp = get_sample(i);
						smp.time_ = t;
						smp.ch_ = i;
						fifo_.put(smp);
					}
				}
			}

			if(fifo_.length() == 0) return;

			sample_t smp = fifo_.get();

			char data[2048];
			struct tm *m = localtime(&smp.time_);
			if(smp.ch_ == 0) {
				utils::sformat("%04d/%02d/%02d,%02d:%02d:%02d,", data, sizeof(data))
					% static_cast<uint32_t>(m->tm_year + 1900)
					% static_cast<uint32_t>(m->tm_mon + 1)
					% static_cast<uint32_t>(m->tm_mday)
					% static_cast<uint32_t>(m->tm_hour)
					% static_cast<uint32_t>(m->tm_min)
					% static_cast<uint32_t>(m->tm_sec);
			} else {
				utils::sformat(",", data, sizeof(data));
			}
			smp.make_csv2(data, sizeof(data), true);
			if(smp.ch_ == 7) {
				utils::sformat("\n", data, sizeof(data), true);
			}
			fwrite(data, 1, utils::sformat::chaout().size(), fp_);
//			utils::format("Write ch: %d\n") % t.ch_;

			if(smp.ch_ == 7) {  // last channnel
				if(m->tm_sec == 59) {  // change file.
					fclose(fp_);
					fp_ = nullptr;
					++count_;
				}

				if(count_ >= limit_) {
					fclose(fp_);
					fp_ = nullptr;
					debug_format("Fin write file: %d sec\n") % count_;
					enable_ = false;
				}
			}
		}
	};
}
