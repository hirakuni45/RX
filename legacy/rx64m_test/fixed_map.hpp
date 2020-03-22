#pragma once
//=====================================================================//
/*!	@file
	@brief	Fixed MAP (固定長 MAP) テンプレート
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

#define FIXED_MAP_SORT

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  fixed map クラス
		@param[in]	KEY		比較キー
		@param[in]	PAD		格納パッド
		@param[in]	SIZE	バッファサイズ（最大 65535）
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#ifdef FIXED_MAP_SORT
	template <typename KEY, typename PAD, uint32_t SIZE>
	class fixed_map {

		struct core_t {
			KEY	key;
			PAD	pad;
		};

		core_t		core_[SIZE];
		uint32_t	size_;

		KEY			cen_key_;
		uint32_t	cen_org_;

		void move_(uint32_t org)
		{
			if(org >= SIZE) return;

			uint32_t i = size_;
			while(i > org) {
				core_[i] = core_[i - 1];
				--i;
			}
		}

	public:

		fixed_map() : size_(0), cen_key_(0), cen_org_(0) { }


		uint32_t size() const { return size_; }


		void clear()
		{
			size_ = 0;
			cen_key_ = 0;
			cen_org_ = 0;
		}


		bool insert(KEY key, PAD pad)
		{
			if(size_ >= SIZE) return false;

			uint32_t i = 0;
			if(key >= cen_key_) i = cen_org_;

			while(i < size_) {
				if(key < core_[i].key) {
					move_(i);
					break;
				} else if(key == core_[i].key) {
					++core_[i].pad;
					return true;
				}
				++i;
			}
			core_[i].key = key;
			core_[i].pad = 1;
			++size_;

			cen_key_ = core_[size_ / 2].key;
			cen_org_ = size_ / 2;
			return false;
		}


		KEY get_key(uint32_t idx) const { return core_[idx].key; }
		PAD get_pad(uint32_t idx) const { return core_[idx].pad; }

#if 0
		void list()
		{
			for(T i = 0; i < size_; ++i) {
			   std::cout << i << " V: " << core_[i].value << ", C: " << core_[i].count << std::endl;
			}
		}
#endif

#else
	template <typename KEY, typename PAD, uint16_t SIZE>
	class fixed_map {

		struct bst
		{
    		KEY			key_;
			PAD			pad_;
			int16_t		left_;
			int16_t		right_;
		};

		uint32_t	size_;
		bst			mem_[SIZE];

		void set_left_(int16_t curr_index, KEY key, PAD pad)
		{
			if(size_ >= SIZE) return;

			int16_t left_index = size_;
			mem_[curr_index].left_ = left_index;
			mem_[size_] = { key, pad, -1, -1 };
			++size_;
		}


		void set_right_(int16_t curr_index, KEY key, PAD pad)
		{
			if(size_ >= SIZE) return;

			int16_t right_index = size_;
			mem_[curr_index].right_ = right_index;
			mem_[size_] = { key, pad, -1, -1 };
			++size_;
		}


		void make_node_(KEY key, PAD pad)
		{
    		mem_[size_] = { key, pad, -1, -1 };
			++size_;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		fixed_map() : size_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サイズを取得
			@return サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const { return size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  クリア
		*/
		//-----------------------------------------------------------------//
		void clear() { size_ = 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  値を挿入
			@param[in]	key	比較キー
			@param[in]	pad	連想パッド
			@return 挿入できたら「true」、値があれば「false」
		*/
		//-----------------------------------------------------------------//
		bool insert(KEY key, PAD pad)
		{
			if(size_ == 0) {
				make_node_(key, pad);
				return true;
			}

			uint32_t idx = 0;
			while(idx < size_) {
				if(key == mem_[idx].key_) {
					++mem_[idx].pad_;
					return false;
				} else if(key < mem_[idx].key_) {
					if(mem_[idx].left_ == -1) {
						set_left_(idx, key, pad);
						break;
					} else {
						idx = mem_[idx].left_;
					}
				} else {
					if(mem_[idx].right_ == -1) {
						set_right_(idx, key, pad);
						break;
					} else {
						idx = mem_[idx].right_;
					}
				}
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  KEY の取得
			@param[in]	idx	インデックス
			@return KEY
		*/
		//-----------------------------------------------------------------//
		KEY get_key(uint16_t idx) const { return mem_[idx].key_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  PAD の取得
			@param[in]	idx	インデックス
			@return PAD
		*/
		//-----------------------------------------------------------------//
		PAD get_pad(uint16_t idx) const { return mem_[idx].pad_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  左の取得
			@param[in]	idx	インデックス
			@return 左
		*/
		//-----------------------------------------------------------------//
		int16_t get_left(uint16_t idx) const
		{
			return mem_[idx].left_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  右の取得
			@param[in]	idx	インデックス
			@return 右
		*/
		//-----------------------------------------------------------------//
		int16_t get_right(uint16_t idx) const
		{
			return mem_[idx].right_;
		}



		void in_trav(uint16_t idx) const
		{
			if(mem_[idx].left_ != -1) {
				in_trav(mem_[idx].left_);
			}

			std::cout << "(" << idx << ") Key: " << mem_[idx].key_ << " Pad: " << mem_[idx].pad_ << std::endl;

			if(mem_[idx].right_ != -1) {
				in_trav(mem_[idx].right_);
			}
		}


#if 0
		void pre_trav(uint16_t idx) const
		{
			std::cout << "(" << idx << ") Key: " << mem_[idx].key_ << " Pad: " << mem_[idx].pad_ << std::endl;

			if(mem_[idx].left_ != -1) {
				pre_trav(mem_[idx].left_);
			}

			if(mem_[idx].right_ != -1) {
				pre_trav(mem_[idx].right_);
			}
		}


		void post_trav(uint16_t idx)
		{
			if(mem_[idx].left_ != -1) {
				post_trav(mem_[idx].left_);
			}

			if(mem_[idx].right_ != -1) {
				post_trav(mem_[idx].right_);
			}

			std::cout << "(" << idx << ") Key: " << mem_[idx].key_ << " Pad: " << mem_[idx].pad_ << std::endl;
		}
#endif
#endif

	};
}
