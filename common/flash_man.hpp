#pragma once
//=====================================================================//
/*!	@file
	@brief	Flash memory マネージャー @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
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
		@param[in]	IO		フラッシュ I/O
		@param[in]	OMAX	オープン最大
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class IO, uint32_t OMAX = 4>
	class flash_man {

		IO&		io_;

		int		fd_[OMAX];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		flash_man(IO& io) : io_(io), fd_{ -1 } { }


		//-----------------------------------------------------------------//
		/*!
			@brief  フリー領域の取得
			@return フリー領域の取得
		*/
		//-----------------------------------------------------------------//
		uint32_t get_free() const {
			uint32_t space = 0;
			for(uint32_t i = 0; i < IO::data_flash_bank; ++i) {
				if(io_.erase_check(i)) {
					space += IO::data_flash_block;
				}
			}
			return space;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ファイルがあるか？
			@return ある場合「true」
		*/
		//-----------------------------------------------------------------//
		bool probe(uint16_t id) const {
			for(uint32_t i = 0; i < IO::data_flash_bank; ++i) {
				if(!io_.erase_check(i)) {
					uint16_t tmp;
					io_.read(i * IO::data_flash_block, &tmp, sizeof(tmp));
					if(tmp == id) return true;
				}
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	id		ファイル ID
			@param[in]	size	ファイルサイズ
			@return ディスクリプタ（負の値ならエラー）
		*/
		//-----------------------------------------------------------------//
		int open(uint16_t id, uint32_t size)
		{
//			for(int i = 0; i < OMAX; ++i) {				
//			}
			int ret = -1;


			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	fd		ディスクリプタ
			@param[in]	src		ソース
			@param[in]	size	サイズ（バイト）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool write(int fd, const void* src, uint32_t size)
		{
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み込み
			@param[in]	fd		ディスクリプタ
			@param[in]	dst		転送先
			@param[in]	size	サイズ（バイト）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool read(int fd, void* dst, uint32_t size)
		{
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クローズ
			@param[in]	fd		ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		void close(int fd)
		{
		}
	};
}
