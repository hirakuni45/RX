#pragma once
//=====================================================================//
/*!	@file
	@brief	WAV 音声ファイルを扱うクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include "ff12b/src/ff.h"
#include "common/format.hpp"

extern "C" {	
	void bmp_putch(char ch);
	void bmp_locate(int8_t idx);
};

namespace audio {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	WAV 形式ファイルクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class wav_in {

		struct WAVEFILEHEADER {
			char	   	szRIFF[4];
			uint32_t	ulRIFFSize;
			char	   	szWAVE[4];
		};

		struct RIFFCHUNK {
			char   		szChunkName[4];
			uint32_t	ulChunkSize;
		};

		struct WAVEFMT {
			uint16_t	usFormatTag;
			uint16_t	usChannels;
			uint32_t	ulSamplesPerSec;
			uint32_t	ulAvgBytesPerSec;
			uint16_t	usBlockAlign;
			uint16_t	usBitsPerSample;
			uint16_t	usSize;
			uint16_t	usReserved;
			uint32_t	ulChannelMask;
			uint32_t	guidSubFormat;
		};

		uint32_t	data_top_;
		uint32_t	data_size_;

		uint32_t	rate_;
		uint8_t		channel_;
		uint8_t		bits_;

		bool list_tag_(FIL* fp, uint16_t size, int8_t idx) {
			if(idx >= 0) bmp_locate(idx);
			while(size > 0) {
				char ch = 0;
				UINT br;
				if(f_read(fp, &ch, 1, &br) != FR_OK) {
					return false;
				}
				--size;
				if(ch != 0) {
					utils::format("%c") % ch;
					if(idx >= 0) {
						bmp_putch(ch);
					}
				}
			}
			return true;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		wav_in() : data_top_(0), data_size_(0), rate_(0), channel_(0), bits_(0) { }


		//-------------------------------------------------------------//
		/*!
			@brief	ヘッダーをロードして、フォーマット、サイズを取得する
			@param[in]	path	ファイル・パス
			@param[in]	lcd		LCD 向け表示の場合「true」
		*/
		//-------------------------------------------------------------//
		bool load_header(FIL* fil, bool lcd = false)
		{
			uint32_t ofs = 0;
			{
				WAVEFILEHEADER wh;
				UINT br;
				if(f_read(fil, &wh, sizeof(wh), &br) != FR_OK) {
					return false;
				}
				if(br != sizeof(wh)) return false;
				if(std::strncmp(wh.szRIFF, "RIFF", 4) == 0 && std::strncmp(wh.szWAVE, "WAVE", 4) == 0) ;
				else return false;
				ofs += sizeof(wh);
			}

			while(1) {
				RIFFCHUNK rc;
				UINT br;
				if(f_read(fil, &rc, sizeof(rc), &br) != FR_OK) {
					return false;
				}
				if(br != sizeof(rc)) return false;
				ofs += sizeof(rc);

				if(std::strncmp(rc.szChunkName, "fmt ", 4) == 0) {
					WAVEFMT wf;
					if(f_read(fil, &wf, sizeof(wf), &br) != FR_OK) {
						return false;
					}
					if(br != sizeof(wf)) return false;
					rate_ = wf.ulSamplesPerSec;
					channel_ = wf.usChannels;
					bits_ = wf.usBitsPerSample;
				} else if(std::strncmp(rc.szChunkName, "data", 4) == 0) {
					data_size_ = rc.ulChunkSize;
					break;
				} else if(std::strncmp(rc.szChunkName, "LIST", 4) == 0) {
					uint16_t sz = rc.ulChunkSize;
					char key[4];
					if(f_read(fil, &key, sizeof(key), &br) != FR_OK) {
						return false;
					}
					if(std::strncmp(key, "INFO", 4) == 0) {
						sz -= 4;
						while(sz > 0) {
							RIFFCHUNK tag;
							UINT br;
							if(f_read(fil, &tag, sizeof(tag), &br) != FR_OK) {
								return false;
							}
							sz -= sizeof(tag);
							utils::format("%c%c%c%c: ") % tag.szChunkName[0] % tag.szChunkName[1]
								% tag.szChunkName[2] % tag.szChunkName[3];
							int8_t idx = -1;
							if(lcd) {
								if(std::strncmp(tag.szChunkName, "IART", 4) == 0) idx = 0;
								else if(std::strncmp(tag.szChunkName, "INAM", 4) == 0) idx = 1;
								else if(std::strncmp(tag.szChunkName, "IPRD", 4) == 0) idx = 2;
							}
							uint16_t n = tag.ulChunkSize;
							if(n & 1) ++n;
							if(!list_tag_(fil, n, idx)) {
								return false;
							}
							utils::format("\n");
							sz -= n;
						}
					}
				}
				ofs += rc.ulChunkSize;
				f_lseek(fil, ofs);
			}
			data_top_ = f_tell(fil);

			return true;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	データ先頭のファイル位置を返す
			@return ファイル位置
		*/
		//-------------------------------------------------------------//
		uint32_t get_top() const { return data_top_; }


		//-------------------------------------------------------------//
		/*!
			@brief	データサイズを取得
			@return データサイズ
		*/
		//-------------------------------------------------------------//
		uint32_t get_size() const { return data_size_; }


		//-------------------------------------------------------------//
		/*!
			@brief	サンプルレートを取得
			@return サンプルレート
		*/
		//-------------------------------------------------------------//
		uint32_t get_rate() const { return rate_; }


		//-------------------------------------------------------------//
		/*!
			@brief	チャネル数を取得
			@return チャネル数
		*/
		//-------------------------------------------------------------//
		uint8_t get_channel() const { return channel_; }


		//-------------------------------------------------------------//
		/*!
			@brief	量子化数を取得
			@return 量子化数
		*/
		//-------------------------------------------------------------//
		uint8_t get_bits() const { return  bits_; }


		//-------------------------------------------------------------//
		/*!
			@brief	時間を取得（秒）
			@return 時間
		*/
		//-------------------------------------------------------------//
		uint32_t get_time() const { return data_size_ / (channel_ * bits_ / 8) / rate_; }
	};
}
