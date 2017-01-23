#pragma once
//=====================================================================//
/*!	@file
	@brief	データ・ロガー・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/sdc_io.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	データ・ロガー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class datalogger {

		enum class TASK : uint8_t {
			NONE,
			FILE_OPEN,
			FILE_WRITE,
			FILE_CLOSE,
		};


		TASK		log_task_;
		FIL 		fil_;
		int 		log_count_;
		uint32_t	log_frame_;
		char 		root_path_[16];

		FIL*		fd_;

		static int get_n_(const char *t)
		{
			int v = 0;
			char ch;
			while((ch = *t++) != 0) {
				if(ch >= '0' && ch <= '9') {
					v *= 10;
					v += ch - '0';
				} else {
					break;
				}
			}
			return v;
		}

	public:

		//-----------------------------------------------------------------//
		/*!
			@breif	日付を使ってディレクトリーを作成
			@param[in]	path	日付名のパスを返す
			@return	成功した場合「０」、失敗したら「-1」
		*/
		//-----------------------------------------------------------------//
		int mkdir_date(char *path)
		{
#if 0
			const struct tm *sttm = get_time();
			int year = sttm->tm_year + 1900;
			if(year < 2011 || sttm->tm_mday <= 0 || sttm->tm_mday > 31 || sttm->tm_mon >= 12) {
				strcpy_P(path, PSTR("20XX-XX-XX"));
			} else {
				sprintf_P(path, PSTR("%04d-%02d-%02d"), year, sttm->tm_mon + 1, sttm->tm_mday);
			}
			return f_mkdir(path);
#endif
			return 0;
		}


#if 0
//-----------------------------------------------------------------//
/*!
	@breif	ルートパスの作成
	@param[in]	path	生成したパスの格納先
	@param[in]	base	ベース名
	@param[in]	count	インデックス
*/
//-----------------------------------------------------------------//
void create_root_path(char *path, const char *base, int count)
{
	sprintf_P(path, PSTR("%s/%s_%03d.LOG"), g_root_path, base, count);
}


//-----------------------------------------------------------------//
/*!
	@breif	データ・ロガー・サーバー初期化
*/
//-----------------------------------------------------------------//
void datalogger_init(void)
{
	g_log_task = LOG_NONE;
	g_log_count = 1;
	g_root_path[0] = 0;
	g_fd = NULL;
}


//-----------------------------------------------------------------//
/*!
	@breif	データ・ロガー・サーバー・サービス
*/
//-----------------------------------------------------------------//
void datalogger_service(void)
{
	if((fileio_get_status() & FILEIO_DISK_MOUNT) == 0) return;

	if(g_log_task == LOG_FILE_OPEN) {
		char path[40];
		if(g_log_gps_enable | g_log_adc_enable | g_log_puls_enable) {
			sprintf_P(path, PSTR("%s/GPAD_%03d.LOG"), g_root_path, g_log_count);
			if(f_open(&g_fil, path, FA_CREATE_ALWAYS | FA_WRITE) != 0) {
				g_log_task = LOG_NONE;
			} else {
				g_fd = &g_fil;
				if(g_log_adc_enable) {
					mcp3208_fifo_enable(1);
				}
				g_log_task = LOG_FILE_WRITE;
				g_log_frame = 0;
			}
		}
	} else if(g_log_task == LOG_FILE_CLOSE) {
		if(g_fd != NULL) {
			f_close(g_fd);
			g_fd = NULL;
		}
		g_log_task = LOG_NONE;
	}
}
#endif

		//-----------------------------------------------------------------//
		/*!
			@breif	データ・ロガー・サービス・リクエスト
			@param[in]	task	タスク識別
		*/
		//-----------------------------------------------------------------//
		void request(TASK task)
		{
			log_task_ = task;

			if(task == TASK::FILE_OPEN) { // 新規フォルダーとファイル名のインデックスなどを用意する
				root_path_[0] = 0;
				if(mkdir_date(root_path_)) {
					// 一番最後の番号を取得
#if 0
					FILINFO fno;
					char lfn[_MAX_LFN + 1];
					fno.fname = lfn;
					fno.fsize = sizeof(lfn);
					DIR d;
					if(f_opendir(&d, root_path_) == FR_OK) {
						for( ; ; ) {
							FRESULT res = f_readdir(&d, &fno);
							const char *fn = *fno.lfname ? fno.lfname : fno.fname;
							if(res != FR_OK || fn[0] == 0) break;
							if(fn[0] == '.') continue;
							if(std::strncmp(fn, "GPAD_", 5) == 0) {
								int n = get_n_(fn + 5) + 1;
								if(log_count_ < n) log_count_ = n;
							}
						}
					}
#endif
				} else {
					log_count_ = 1;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	ロギングの開始手続き
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			request(TASK::FILE_OPEN);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	ロギングの終了手続き
		*/
		//-----------------------------------------------------------------//
		void finsh()
		{
			request(TASK::FILE_CLOSE);
		}
	};
}
