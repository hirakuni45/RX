#pragma once
//=====================================================================//
/*!	@file
	@brief	ビットマップ・グラフィックス用ファイル選択クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/monograph.hpp"
#include "common/sdc_io.hpp"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイラー・クラス
		@param[in]	SDC_IO	SDC I/O クラスの型
		@param[in]	BITMAP	ビットマップの型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDC_IO, class BITMAP>
	class filer {

		SDC_IO& sdc_;
		BITMAP&	bitmap_;

		int16_t	file_num_;
		int16_t	file_ofs_;
		int16_t	file_pos_;

		enum class task : uint8_t {
			ready,
			create_list,
			ready_list,
		};
		task		task_;

		int16_t	shift_pos_;
		uint8_t	shift_wait_;

		int16_t select_size_;
		char	select_path_[256];

		struct option_t {
			BITMAP*		bmp_;
			int16_t		ofsy_;
			uint16_t	cnt_;
			uint16_t	match_;
			int16_t		size_;
			char*		path_;
		};

		static void dir_task_(const char* fname, const FILINFO* fi, bool dir, void* option)
		{
			option_t* t = reinterpret_cast<option_t*>(option);
			int16_t sz = 0;
			int16_t ox = 0;
			if(t->ofsy_ >= -t->bmp_->get_kfont_height() && t->ofsy_ < t->bmp_->get_height()) {
				if(fi->fattrib & AM_DIR) {
					t->bmp_->draw_font(0, t->ofsy_, '/');
					ox = t->bmp_->get_afont_width();
				}
				sz = t->bmp_->draw_text(ox, t->ofsy_, fname);
			}
			t->ofsy_ += t->bmp_->get_kfont_height();
			if(t->cnt_ == t->match_) {
				char* p = t->path_;
				if(p != nullptr && fname != nullptr) {
					if(fi->fattrib & AM_DIR) {
						*p++ = '/';
					}
					std::strncpy(p, fname, sizeof(select_path_) - 2);
				}
				t->size_ = sz;
			}
			++t->cnt_;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	sdc	sdc_io クラス参照
			@param[in]	bitmap	ビットマップ・クラス参照
		*/
		//-----------------------------------------------------------------//
		filer(SDC_IO& sdc, BITMAP& bitmap) : sdc_(sdc), bitmap_(bitmap),
			file_num_(0), file_ofs_(0), file_pos_(0),
			task_(task::ready), shift_pos_(0), shift_wait_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイラーの状態を取得
			@return 「ready」なら「true」
		*/
		//-----------------------------------------------------------------//
		bool ready() const { return task_ == task::ready ? true : false; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイラーを開始
			@return 開始したら「true」
		*/
		//-----------------------------------------------------------------//
		bool start() {
			file_num_ = sdc_.dir_loop("", nullptr, true);
			if(file_num_ > 0) {
				file_ofs_ = 0;
				file_pos_ = 0;
				task_ = task::create_list;
				shift_wait_ = 0;
				shift_pos_ = 0;
				return true;
			} else {
				task_ = task::ready;
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイラーを終了
		*/
		//-----------------------------------------------------------------//
		void close() {
			task_ = task::ready;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	表示フォーカスを変更
			@param[in]	ofs	フォーカス・オフセット
			@return 変更時「true」 
		*/
		//-----------------------------------------------------------------//
		bool set_focus(int16_t ofs) {
			if(task_ != task::ready_list) return false;

			int16_t newpos = file_pos_ + ofs;
			if(newpos < 0) newpos = 0;
			else if(newpos >= file_num_) newpos = file_num_ - 1;
			if(file_pos_ != newpos) {
				file_pos_ = newpos;
				shift_wait_ = 0;
				shift_pos_ = 0;
				int16_t o = file_ofs_ + file_pos_ * bitmap_.get_kfont_height();
				if(o < 0) {
					file_ofs_ += bitmap_.get_kfont_height();
				} else if(o > (bitmap_.get_height() - bitmap_.get_kfont_height())) {
					file_ofs_ -= bitmap_.get_kfont_height();
				}
				task_ = task::create_list;
				return true;
			} else {
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	表示フォーカスを取得
			@return 表示フォーカス
		*/
		//-----------------------------------------------------------------//
		int16_t get_focus() const {
			if(task_ == task::ready_list) {
				return file_pos_;
			} else {
				return 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ディレクトリー移動
			@param[in]	inc	戻る場合「false」
			@return 成功なら「true」 
		*/
		//-----------------------------------------------------------------//
		bool set_directory(bool inc = true) {
			if(task_ != task::ready_list) {
				return false;
			}

			bool f = false;
			if(inc) {
				if(select_path_[0] != '/') return false;
				f = sdc_.cd(&select_path_[1]);
			} else {
				f = sdc_.cd("..");
			}

			if(f) {
				f = start();
			}
			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス 表示、毎フレーム呼ぶ
			@param[in]	mount	マウント状態
			@param[in]	spd		シフト・スピード遅延
			@return 「true」が返る場合、フレームバッファの更新要求
		*/
		//-----------------------------------------------------------------//
		bool service(bool mount, int8_t spd)
		{
			if(!mount) {
				task_ = task::ready;
				return false;
			}

			if(file_num_ == 0 || task_ == task::ready) return false;

			bool fbcopy = false;
			if(task_ == task::create_list) {
				option_t opt;
				opt.bmp_ = &bitmap_;
				opt.ofsy_ = file_ofs_;
				opt.cnt_ = 0;
				opt.match_ = file_pos_;
				opt.size_ = 0;
				select_path_[0] = 0;
				opt.path_ = select_path_;
				sdc_.dir_loop("", dir_task_, true, &opt);
				select_size_ = opt.size_;
				int16_t y = file_pos_ * bitmap_.get_kfont_height() + file_ofs_;
				bitmap_.reverse(0, y, bitmap_.get_width() - 1, bitmap_.get_kfont_height() - 1);
				task_ = task::ready_list;
			} else if(task_ == task::ready_list) {
				if(select_size_ < bitmap_.get_width()) ;
				else if(shift_wait_ >= (60 * 4)) {
					--shift_pos_;
					int16_t y = file_pos_ * bitmap_.get_kfont_height() + file_ofs_;
					bitmap_.fill(0, y, bitmap_.get_width() - 1, bitmap_.get_kfont_height() - 1, 0);
					auto x = bitmap_.draw_text(shift_pos_, y, select_path_);
					if(x <= 0) {
						shift_pos_ = bitmap_.get_width();
					}
					shift_wait_ -= spd;  // shift speed delay
					fbcopy = true;
				} else {
					++shift_wait_;
				}
			}
			return fbcopy;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択されたパスを取得
			@return 選択されたパス
		*/
		//-----------------------------------------------------------------//
		const char* get_select_path() const {
			if(task_ == task::ready_list) {
				return select_path_;
			} else {
				return nullptr;
			}
		}
	};
}
