#pragma once
//=====================================================================//
/*!	@file
	@brief	Flash memory マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  flash_man class @n
				データ列の構造：@n
				+0: ID (2 bytes) @n
				+2: TM (2 bytes) タイムスタンプ（数値が一番大きいものが最新）@n
				+4: SZ (2 bytes) サイズ
		@param[in]	FIO		フラッシュ I/O
		@param[in]	OMAX	オープン最大
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class FIO, uint32_t OMAX = 4>
	class flash_man {

		FIO&	fio_;

		// 制限：　１ファイル、最大３２Ｋバイトまで
		struct head_t {
			uint16_t	id;		///< file ID
			uint16_t	nx_sz;	///< (B15:1)next block, (B15:0)total size
		};


		uint32_t free_()
		{
			uint32_t pos = 0;
			while(pos < FIO::data_flash_size) {
				if(fio_.erase_check(pos)) {
					return pos;
				}
				pos += FIO::data_flash_block;
			}
			return FIO::data_flash_size;
		}


		uint32_t scan_(uint16_t id) const
		{
			uint32_t pos = 0;
			uint32_t match = FIO::data_flash_size;
			while(pos < FIO::data_flash_size) {
				uint32_t d = FIO::data_flash_block;
				if(!fio_.erase_check(pos)) {
					head_t h;
					fio_.read(pos, &h, sizeof(head_t));
					if(h.id == id) {
						match = pos;
						uint16_t s = h.size;
						d = s / (FIO::data_flash_block - sizeof(head_t));
						if(d == 0) ++d;
						d *= FIO::data_flash_block;
					}
				}
				pos += d;
			}
			return match;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		flash_man(FIO& fio) : fio_(fio) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  FIO の参照
			@return FIO
		*/
		//-----------------------------------------------------------------//
		FIO& at_fio() { return fio_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  フリー領域の取得
			@return フリー領域の取得
		*/
		//-----------------------------------------------------------------//
		uint32_t get_free() const {
			uint32_t space = 0;
			for(uint32_t i = 0; i < FIO::data_flash_bank; ++i) {
				if(fio_.erase_check(i)) {
					space += FIO::data_flash_block - sizeof(head_t);
				}
			}
			return space;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ファイルがあるか？
			@param[in]	id	ファイルＩＤ
			@return ある場合「true」
		*/
		//-----------------------------------------------------------------//
		bool probe(uint16_t id) const
		{
			return scan_(id) < FIO::data_flash_size;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	id		ＩＤ
			@param[in]	src		ソース
			@param[in]	size	サイズ（バイト）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint16_t id, const void* src, uint32_t size)
		{
			uint32_t pos = free_();
			if(pos >= FIO::data_flash_size) {
				return false;
			}
			uint32_t fsb = (FIO::data_flash_size - pos) / FIO::data_flash_block;
			uint32_t fs  = fsb * (FIO::data_flash_block - sizeof(head_t));
			if(fs < size) {
				return false;
			}

			head_t t;
			t.id = id;
//			t.size = 



			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み込み
			@param[in]	id		ＩＤ
			@param[in]	dst		転送先
			@param[in]	size	サイズ（バイト）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool read(int desc, void* dst, uint32_t size)
		{
			return false;
		}
	};
}
