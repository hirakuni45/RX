#pragma once
//=========================================================================//
/*!	@file
	@brief	SD カード・マネージャー @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "common/format.hpp"
#include "common/string_utils.hpp"
#include "ff12b/mmc_io.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SD カード・マネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class sdc_man {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DIR リスト関数型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef void (*dir_loop_func)(const char* name, const FILINFO* fi, bool dir, void* option);

	private:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SD カード・ディレクトリー・リスト・クラス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		class dir_list {
			DIR			dir_;
			uint32_t	total_;
			uint32_t	limit_;
			char*		ptr_;

			bool		init_;

			char full_[_MAX_LFN + 1];

		public:
			//-----------------------------------------------------------------//
			/*!
				@brief	コンストラクター
			 */
			//-----------------------------------------------------------------//
			dir_list() noexcept : total_(0), limit_(10), ptr_(nullptr), init_(false) { }


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

				std::strcpy(full_, root);

				auto st = f_opendir(&dir_, full_);
				if(st != FR_OK) {
					return false;
				}

				std::strcat(full_, "/");
				ptr_ = &full_[std::strlen(full_)];
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
			bool service(uint32_t num, dir_loop_func func = nullptr, bool todir = false,
						 void* option = nullptr) noexcept
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
						f_closedir(&dir_);
						init_ = false;
						break;
					}

					if(func != nullptr) {
#if _USE_LFN != 0
						str::sjis_to_utf8(fi.fname, ptr_);
#else
						std::strcpy(ptr_, fi.fname);
#endif
						if(fi.fattrib & AM_DIR) {
							if(todir) {
								func(ptr_, &fi, true, option);
							}
						} else {
							func(ptr_, &fi, false, option);
						}
					}
					++total_;
				}
				return true;
			}
		};

		char			current_[_MAX_LFN + 1];
		bool			cdet_;
		bool			mount_;
		uint16_t		mount_delay_;

		dir_list		dir_list_;

		uint32_t		dir_list_limit_;
		dir_loop_func	dir_func_;
		bool			dir_todir_;
		void* 			dir_option_;

		struct match_t {
			const char* key_;
			char* 		dst_;
			uint32_t	dstlen_;
			uint16_t 	cnt_;
			uint16_t 	no_;
		};

		struct copy_t {
			uint16_t	idx_;
			uint16_t	match_;
			char*		dst_;
			uint32_t	dstlen_;
		};


		static void dir_list_func_(const char* name, const FILINFO* fi, bool dir, void* option) {
			if(fi == nullptr) return;

			time_t t = str::fatfs_time_to(fi->fdate, fi->ftime);
			struct tm *m = localtime(&t);
			if(dir) {
				format("           ");
			} else {
				format("%10d ") % fi->fsize;
			}
			format("%s %2d %4d %02d:%02d ") 
				% get_mon(m->tm_mon)
				% static_cast<int>(m->tm_mday)
				% static_cast<int>(m->tm_year + 1900)
				% static_cast<int>(m->tm_hour)
				% static_cast<int>(m->tm_min);
			if(dir) {
				format("/");
			} else {
				format(" ");
			}
			format("%s\n") % name;
		}


		static void match_func_(const char* name, const FILINFO* fi, bool dir, void* option) noexcept
		{
			match_t* t = reinterpret_cast<match_t*>(option);
			if(std::strncmp(name, t->key_, std::strlen(t->key_)) == 0) {
				if(t->dst_ != nullptr && t->cnt_ == t->no_) {
					std::strncpy(t->dst_, name, t->dstlen_);
				}
				++t->cnt_;
			}
		}


		static void path_copy_func_(const char* name, const FILINFO* fi, bool dir, void* option)
			noexcept
		{
			copy_t* t = reinterpret_cast<copy_t*>(option);
			if(t->idx_ == t->match_) {
				if(t->dst_ != nullptr && t->dstlen_ > 0) {
					std::strncpy(t->dst_, name, t->dstlen_);
					std::strncat(t->dst_, "/", t->dstlen_);
				}
			}
			++t->idx_;
		}


		void create_full_path_(const char* path, char* full, uint32_t len) const noexcept
		{
			std::strncpy(full, current_, len);

			if(path == nullptr || path[0] == 0) {
				if(full[0] == 0) {
					std::strncpy(full, "/", len);
				}
			} else if(std::strcmp(path, "..") == 0) {
				char* p = std::strrchr(full, '/');
				if(p != nullptr) {
					if(&full[0] == p) {
						p[1] = 0;
					} else {
						*p = 0;
					}
				}
			} else if(path[0] == '/') {
				std::strncpy(full, path, len);
			} else {
				uint32_t l = strlen(full);
				if(l > 0 && full[l - 1] != '/') {
					std::strncat(full, "/", len);
				}
				std::strncat(full, path, len);
			}
		}


		// FATFS で認識できるパス（文字コード）へ変換
		void create_fatfs_path_(const char* path, char* full, uint32_t len) const noexcept {
#if _USE_LFN != 0
			char tmp[_MAX_LFN + 1];
			create_full_path_(path, tmp, sizeof(tmp));
			str::utf8_to_sjis(tmp, full, len);
#else
			create_full_path_(path, full, len);
#endif
		}


		// パス中のディレクトリーが無かったら生成
		bool build_dir_path_(const char* path) const noexcept
		{
			char tmp[_MAX_LFN + 1];
			std::strcpy(tmp, path);
			char* p = tmp;
			if(p[0] == '/') ++p;
			while(p[0] != 0) {
				p = std::strchr(p, '/');
				if(p == nullptr) break;
				p[0] = 0;
#if _USE_LFN != 0
				char sjis[_MAX_LFN + 1];
				str::utf8_to_sjis(tmp, sjis, sizeof(sjis));
				auto ret = f_mkdir(sjis);
#else
				auto ret = f_mkdir(tmp);
#endif
				if(ret == FR_OK) ;
				else if(ret == FR_EXIST) ;
				else {
					return false;
				}
				p[0] = '/';
				++p;
			}
			return true;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		sdc_man() noexcept : current_{ 0 }, cdet_(false), mount_(false), mount_delay_(0),
			dir_list_(), dir_list_limit_(10),
			dir_func_(nullptr), dir_todir_(false), dir_option_(nullptr) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始（初期化）
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			mount_ = false;
			strcpy(current_, "/");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイルの存在を検査
			@param[in]	path	ファイル名
			@return ファイルがある場合「true」
		 */
		//-----------------------------------------------------------------//
		bool probe(const char* path) const
		{
			if(!mount_) return false;

			FIL fp;
			bool ret = open(&fp, path, FA_READ | FA_OPEN_EXISTING);
			if(ret) {
				if(f_close(&fp) != FR_OK) {
					return false;
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	パス中のディレクトリーを生成
			@param[in]	path	ファイル名
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool build_dir_path(const char* path) noexcept
		{
			if(!mount_) return false;
			if(path == nullptr) return false;

			char full[_MAX_LFN + 1];
			create_full_path_(path, full, sizeof(full));

			if(!build_dir_path_(full)) {
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・ファイルのオープン
			@param[in]	fp		ファイル構造体ポインター
			@param[in]	path	ファイル名
			@param[in]	mode	オープン・モード
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool open(FIL* fp, const char* path, BYTE mode) const noexcept
		{
			if(!mount_) return false;
			if(fp == nullptr || path == nullptr) return false;

			char full[_MAX_LFN + 1];
			create_fatfs_path_(path, full, sizeof(full));

			if(f_open(fp, full, mode) != FR_OK) {
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クローズ
			@param[in]	fp		ファイル構造体ポインター
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool close(FIL* fp) const
		{
			if(!mount_) return false;
			if(fp == nullptr) return false;

			return f_close(fp) == FR_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル・サイズを返す @n
					※アクセス出来ない場合も「０」を返すので、存在確認に使えない
			@param[in]	path	ファイル名
			@return ファイル・サイズ
		 */
		//-----------------------------------------------------------------//
		uint32_t size(const char* path) const
		{
			if(!mount_) return false;
			if(path == nullptr) return false;

			char full[_MAX_LFN + 1];
			create_fatfs_path_(path, full, sizeof(full));

			FILINFO fno;
			if(f_stat(full, &fno) != FR_OK) {
				return 0;
			}

			return fno.fsize;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイルの更新時間を取得
			@param[in]	path	ファイル名
			@return ファイルの更新時間（０の場合エラー）
		 */
		//-----------------------------------------------------------------//
		time_t get_time(const char* path) const
		{
			if(!mount_) return 0;
			if(path == nullptr) return 0;

			char full[_MAX_LFN + 1];
			create_fatfs_path_(path, full, sizeof(full));

			FILINFO fno;
			if(f_stat(full, &fno) != FR_OK) {
				return 0;
			}

			return str::fatfs_time_to(fno.fdate, fno.ftime);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイルの削除
			@param[in]	path	相対パス、又は、絶対パス
			@return 削除成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool remove(const char* path)
		{
			if(!mount_) return false;
			if(path == nullptr) return false;

			char full[_MAX_LFN + 1];
			create_fatfs_path_(path, full, sizeof(full));

			return f_unlink(full) == FR_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル名の変更
			@param[in]	org_path	元名
			@param[in]	new_path	新名
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool rename(const char* org_path, const char* new_path)
		{
			if(!mount_) return false;
			if(org_path == nullptr || new_path == nullptr) return false;

			char org_full[_MAX_LFN + 1];
			create_fatfs_path_(org_path, org_full, sizeof(org_full));
			char new_full[_MAX_LFN + 1];
			create_fatfs_path_(new_path, new_full, sizeof(new_full));

			return f_rename(org_full, new_full) == FR_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ディレクトリーの作成
			@param[in]	path	相対パス、又は、絶対パス
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool mkdir(const char* path)
		{
			if(!mount_) return false;
			if(path == nullptr) return false;

			char full[_MAX_LFN + 1];
			create_fatfs_path_(path, full, sizeof(full));

			return f_mkdir(full) == FR_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ディスク空き容量の取得
			@param[in]	fspc	フリー・スペース（単位Ｋバイト)
			@param[in]	capa	最大容量（単位Ｋバイト）
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_disk_space(uint32_t& fspc, uint32_t& capa) const
		{
			if(!get_mount()) return false;

			FATFS* fs;
			DWORD nclst = 0;
			if(f_getfree("", &nclst, &fs) == FR_OK) {

				// 全セクタ数と空きセクタ数を計算（５１２バイトセクタ）
				capa = (fs->n_fatent - 2) * fs->csize / 2;
				fspc = nclst * fs->csize / 2;
				return true;
			} else {
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・パスの移動
			@param[in]	path	相対パス、又は、絶対パス
			@return 移動成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool cd(const char* path)
		{
			if(!mount_) return false;

			if(path == nullptr) return false;

			char full[_MAX_LFN + 1];
			create_full_path_(path, full, sizeof(full));

#if _USE_LFN != 0
			char oem[_MAX_LFN + 1];
			str::utf8_to_sjis(full, oem, sizeof(oem));
			DIR dir;
			auto st = f_opendir(&dir, oem);
#else
			DIR dir;
			auto st = f_opendir(&dir, full);
#endif
			if(st != FR_OK) {
				format("Can't open dir(%d): '%s'\n") % static_cast<uint32_t>(st) % full;
				return false;
			}
			std::strncpy(current_, full, sizeof(current_));

			f_closedir(&dir);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ディレクトリー・リストのフレーム単位での最大数を設定
			@param[in]	limit	フレーム毎の最大数
		 */
		//-----------------------------------------------------------------//
		void set_dir_list_limit(uint32_t limit) { dir_list_limit_ = limit; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ディレクトリー・リストの状態を取得
			@param[in]	num	リスト数
			@return ディレクトリー・リスト処理中なら「true」
		 */
		//-----------------------------------------------------------------//
		bool probe_dir_list(uint32_t& num) const
		{
			num = dir_list_.get_total();
			return dir_list_.probe();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SD カードのディレクトリーリストでタスクを実行する
			@param[in]	root	ルート・パス
			@param[in]	func	実行関数
			@param[in]	todir  「true」の場合、ディレクトリーも関数を呼ぶ
			@param[in]	option	オプション・ポインター
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start_dir_list(const char* root, dir_loop_func func = nullptr, bool todir = false,
			void* option = nullptr)
		{
			dir_func_ = func;
			dir_todir_ = todir;
			dir_option_ = option;

			char full[256];
			create_full_path_(root, full, sizeof(full));
#if _USE_LFN != 0
			str::utf8_to_sjis(full, full, sizeof(full));
#endif
			return dir_list_.start(full);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ディレクトリー・リストが実行中なら停止させる。
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool stall_dir_list() noexcept
		{
			return dir_list_.stop();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SD カードのディレクトリから、ファイル名の取得
			@param[in]	root	ルート・パス
			@param[in]	match	所得パスのインデックス
			@param[out]	dst		パスのコピー先
			@param[in]	dstlen	コピー先サイズ
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_dir_path(const char* root, uint16_t match, char* dst, uint32_t dstlen)
		{
			copy_t t;
			t.idx_ = 0;
			t.match_ = match;
			t.dst_ = dst;
			t.dstlen_ = dstlen;
			start_dir_list(root, path_copy_func_, true, &t);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SD カードのディレクトリーをリストする
			@param[in]	root	ルート・パス
			@return ファイル数
		 */
		//-----------------------------------------------------------------//
		uint32_t dir(const char* root) noexcept
		{
			dir_list dl;
			char full[256];
			create_full_path_(root, full, sizeof(full));
#if _USE_LFN != 0
			str::utf8_to_sjis(full, full, sizeof(full));
#endif
			if(!dl.start(full)) return 0;

			do {
				dl.service(10, dir_list_func_, true);
			} while(dl.probe()) ;
			auto n = dl.get_total();
			utils::format("Total %d file%s\n") % n % (n > 1 ? "s" : "");
			return n;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル名候補の取得（ディレクトリも含む）
			@param[in]	name	候補のキー
			@param[in]	no		候補の順番
			@param[in]	dst		候補の格納先
			@param[in]	dstlen	格納先サイズ
			@return 候補の数
		 */
		//-----------------------------------------------------------------//
		uint16_t match(const char* key, uint8_t no, char* dst, uint32_t dstlen) noexcept
		{
			match_t t;
			t.key_ = key;
			t.dst_ = dst;
			t.dstlen_ = dstlen;
			t.cnt_ = 0;
			t.no_ = no;
			start_dir_list(current_, match_func_, true, &t);
			return t.cnt_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SD カードアクセス・サービス（毎フレーム呼ぶ）
			@param[in]	mount	マウント時「true」
		 */
		//-----------------------------------------------------------------//
		void service(bool mount) noexcept
		{
			if(mount && !mount_) {
				strcpy(current_, "/");				
			}
			mount_ = mount;

			if(mount_) {
				dir_list_.service(dir_list_limit_, dir_func_, dir_todir_, dir_option_);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フル・パスを生成
			@param[in]	src		生成元
			@param[out]	dst		生成先
			@param[in]	dsz		生成先サイズ
			@return 正常コピー出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool make_full_path(const char* src, char* dst, uint16_t dsz) const
		{
			if(src == nullptr || dst == nullptr) return false;

			if(src[0] == '/') {  // フルパスの場合
				for(uint16_t i = 0; i < (dsz - 1); ++i) {
					auto ch = src[i];
					dst[i] = ch;
					if(ch == 0) {
						return true;
					}
				}
				dst[dsz - 1] = 0;
				return false;
			}

			uint16_t pos = 0;
			for(pos = 0; pos < (dsz - 1); ++pos) {
				auto ch = current_[pos];
				dst[pos] = ch;
				if(ch == 0) {
					break;
				}
			}
			if(pos == (dsz - 1)) {  // サイズ最大か？
				dst[pos] = 0;
				return false;
			}

			if(std::strlen(src) == 0) return true;  // 追加無し

			if(pos == 1 && dst[0] == '/' && dst[1] == 0) ;  // ルート・パスなので、何もしない
			else if(pos > 2 && dst[pos - 1] != '/') {  // [/] を追加する必要がある場合 
				dst[pos] = '/';
				++pos;
				dst[pos] = 0;
			}

			while(pos < (dsz - 1)) {
				auto ch = *src++;
				dst[pos] = ch;
				if(ch == 0) {
					return true;
				}
				++pos;
			}
			dst[dsz - 1] = 0;
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・パスを取得
			@return カレント。パス
		 */
		//-----------------------------------------------------------------//
		const char* get_current() const noexcept { return current_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	カードのマウント状態を取得
			@return 「true」ならマウント状態
		 */
		//-----------------------------------------------------------------//
		bool get_mount() const noexcept { return mount_; }
	};
}
