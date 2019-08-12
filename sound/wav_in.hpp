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
#include "common/file_io.hpp"
#include "common/format.hpp"
#include "sound/tag.hpp"
#include "sound/af_play.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	WAV 形式ファイルクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class wav_in : public af_play {

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
		uint32_t	data_pos_;

		uint32_t	rate_;
		uint8_t		channel_;
		uint8_t		bits_;

		uint32_t	time_;


		bool list_tag_(utils::file_io& fi, uint16_t size, char* dst, uint32_t dstlen) noexcept
		{
			while(size > 0) {
				char ch = 0;
				if(fi.read(&ch, 1) != 1) {
					return false;
				}
				--size;
				if(ch != 0) {
					if(dst != nullptr && dstlen > 1) {
						*dst++ = ch;
						dstlen--;
					}
				}
			}
			*dst = 0;
			return true;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		wav_in() noexcept : data_top_(0), data_size_(0), data_pos_(0),
			rate_(0), channel_(0), bits_(0), time_(0) { }


		//-------------------------------------------------------------//
		/*!
			@brief	ヘッダーをロードして、フォーマット、サイズを取得する
			@param[in]	path	ファイル・パス
			@param[in]	tag		タグの参照
		*/
		//-------------------------------------------------------------//
		bool load_header(utils::file_io& fi, tag_t& tag) noexcept
		{
			uint32_t ofs = 0;
			{
				WAVEFILEHEADER wh;
				if(fi.read(&wh, sizeof(wh)) != sizeof(wh)) {
					return false;
				}
				if(std::strncmp(wh.szRIFF, "RIFF", 4) == 0 &&
				   std::strncmp(wh.szWAVE, "WAVE", 4) == 0) ;
				else return false;
				ofs += sizeof(wh);
			}

			while(1) {
				RIFFCHUNK rc;
				if(fi.read(&rc, sizeof(rc)) != sizeof(rc)) {
					return false;
				}
				ofs += sizeof(rc);

				if(std::strncmp(rc.szChunkName, "fmt ", 4) == 0) {
					WAVEFMT wf;
					if(fi.read(&wf, sizeof(wf)) != sizeof(wf)) {
						return false;
					}
					rate_ = wf.ulSamplesPerSec;
					channel_ = wf.usChannels;
					bits_ = wf.usBitsPerSample;
				} else if(std::strncmp(rc.szChunkName, "data", 4) == 0) {
					data_size_ = rc.ulChunkSize;
					break;
				} else if(std::strncmp(rc.szChunkName, "LIST", 4) == 0) {
					uint16_t sz = rc.ulChunkSize;
					char key[4];
					if(fi.read(&key, sizeof(key)) != sizeof(key)) {
						return false;
					}
					if(std::strncmp(key, "INFO", 4) == 0) {
						sz -= 4;
						while(sz > 0) {
							RIFFCHUNK rch;
							if(fi.read(&rch, sizeof(rch)) != sizeof(rch)) {
								return false;
							}
							sz -= sizeof(rch);
							char* dst = nullptr;
							uint32_t dstlen = 0;
							if(std::strncmp(rch.szChunkName, "IART", 4) == 0) {
								dst    = tag.at_album().begin();
								dstlen = tag.at_album().capacity();
							} else if(std::strncmp(rch.szChunkName, "INAM", 4) == 0) {
								dst    = tag.at_title().begin();
								dstlen = tag.at_title().capacity();
							} else if(std::strncmp(rch.szChunkName, "IPRD", 4) == 0) {
								dst    = tag.at_artist().begin();
								dstlen = tag.at_artist().capacity();
							} else if(std::strncmp(rch.szChunkName, "ICRD", 4) == 0) {
								dst    = tag.at_year().begin();
								dstlen = tag.at_year().capacity();
							} else if(std::strncmp(rch.szChunkName, "IPRT", 4) == 0) {
								dst    = tag.at_track().begin();
								dstlen = tag.at_track().capacity();
							} else {
//								utils::format("TAG: %c%c%c%c\n")
//									% rch.szChunkName[0] % rch.szChunkName[1]
//									% rch.szChunkName[2] % rch.szChunkName[3];
							}
							uint16_t n = rch.ulChunkSize;
							if(n & 1) ++n;
//							char tmp[256];
//							if(dst == nullptr) {
//								dst = tmp;
//								dstlen = sizeof(tmp);
//							}
							if(!list_tag_(fi, n, dst, dstlen)) {
								return false;
							}
//							if(tmp == dst) {
//								utils::format("  '%s'\n") % dst;
//							}
							sz -= n;
						}
					}
				}
				ofs += rc.ulChunkSize;
				fi.seek(utils::file_io::SEEK::SET, ofs);
			}
			data_top_ = fi.tell();

			data_pos_ = 0;

			return true;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	デコード
			@param[in]	fi	ファイルＩ／Ｏ
			@return 正常終了なら「true」
		*/
		//-------------------------------------------------------------//
		template <class SOUND_OUT>
		bool decode(utils::file_io& fin, SOUND_OUT& out) noexcept
		{
			tag_t tag;
			if(!load_header(fin, tag)) {
				return false;
			}
			if(tag_task_) {
				tag_task_(fin, tag);
			}

			bool status = true;
			bool pause = false;
			uint32_t pos = 0;
			time_ = 0;
			while(data_pos_ < data_size_) {
				CTRL ctrl = CTRL::NONE;
				if(ctrl_task_) {
					ctrl = ctrl_task_();
				}
				if(ctrl == CTRL::STOP) {
					out.mute();
					status = false;
					break;
				} else if(ctrl == CTRL::REPLAY) {
					out.mute();
					fin.seek(utils::file_io::SEEK::SET, data_top_);
					pos = 0;
					time_ = 0;
					status = true;
					pause = false;
					continue;
				} else if(ctrl == CTRL::PAUSE) {
					out.mute();
					pause = !pause;
				}
				if(pause) {
					utils::delay::milli_second(2);
					continue;
				}

				uint32_t unit = (bits_ / 8) * channel_;
				uint8_t tmp[1024];
				if(fin.read(tmp, unit * 256) != (unit * 256)) {
//					utils::format("Read fail abort...\n");
					out.mute();
//					status = false;
					break;
				}
				if(bits_ == 16) {
					const uint16_t* src = reinterpret_cast<const uint16_t*>(tmp);
					for(uint32_t i = 0; i < 256; ++i) {
						while((out.at_fifo().size() - out.at_fifo().length()) < 8) {
						}
						sound::wave_t t;
						if(get_channel() == 2) {
							t.l_ch = src[0];
							t.r_ch = src[1];
							src += 2;
						} else {
							t.l_ch = src[0];
							t.r_ch = t.l_ch;
							++src;
						}
						out.at_fifo().put(t);
						++pos;
					}
				} else {  // 8 bits
					const uint8_t* src = reinterpret_cast<const uint8_t*>(tmp);
					for(uint32_t i = 0; i < 256; ++i) {
						while((out.at_fifo().size() - out.at_fifo().length()) < 8) {
						}
						sound::wave_t t;
						if(get_channel() == 2) {
							t.l_ch = static_cast<uint16_t>(src[0] ^ 0x80) << 8;
							t.l_ch |= (src[0] & 0x7f) << 1;
							t.r_ch = static_cast<uint16_t>(src[1] ^ 0x80) << 8;
							t.r_ch |= (src[1] & 0x7f) << 1;
							src += 2;
						} else {
							t.l_ch = static_cast<uint16_t>(src[0] ^ 0x80) << 8;
							t.l_ch |= (src[0] & 0x7f) << 1;
							t.r_ch = t.l_ch;
							++src;
						}
						out.at_fifo().put(t);
						++pos;
					}
				}

				{
					uint32_t s = pos / rate_;
					if(s != time_) {
						if(update_task_) {
							update_task_(s);
						}
						time_ = s;
					}
				}
				data_pos_ += unit;
			}
			return status;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	データ先頭のファイル位置を返す
			@return ファイル位置
		*/
		//-------------------------------------------------------------//
		uint32_t get_top() const noexcept { return data_top_; }


		//-------------------------------------------------------------//
		/*!
			@brief	データサイズを取得
			@return データサイズ
		*/
		//-------------------------------------------------------------//
		uint32_t get_size() const noexcept { return data_size_; }


		//-------------------------------------------------------------//
		/*!
			@brief	サンプルレートを取得
			@return サンプルレート
		*/
		//-------------------------------------------------------------//
		uint32_t get_rate() const noexcept { return rate_; }


		//-------------------------------------------------------------//
		/*!
			@brief	チャネル数を取得
			@return チャネル数
		*/
		//-------------------------------------------------------------//
		uint8_t get_channel() const noexcept { return channel_; }


		//-------------------------------------------------------------//
		/*!
			@brief	量子化数を取得
			@return 量子化数
		*/
		//-------------------------------------------------------------//
		uint8_t get_bits() const noexcept { return  bits_; }


		//-------------------------------------------------------------//
		/*!
			@brief	時間を取得（秒）
			@return 時間
		*/
		//-------------------------------------------------------------//
		uint32_t get_time() const noexcept { return data_size_ / (channel_ * bits_ / 8) / rate_; }
	};
}
