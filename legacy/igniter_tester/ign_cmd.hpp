#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・コマンド解析、応答
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/string_utils.hpp"
#include "common/fixed_fifo.hpp"
#include <stdio.h>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コマンド解析、応答
		@param[in]	TELNTES	TELNET サーバー型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TELNETS>
	class ign_cmd {

		static const uint32_t VERSION = 20;

		static const uint32_t WAVE_CH_SIZE = 2048;
		static const uint32_t WAVE_CH_NUM = 4;

		TELNETS&	telnets_;

		uint32_t	pos_;
		char		line_[256];

		char		crm_ans_[16];
		uint32_t	crm_ans_pos_;

		char		dc2_ans_[16];
		uint32_t	dc2_ans_pos_;

		uint32_t	delay_;

		uint16_t	wave_buff_[WAVE_CH_SIZE * WAVE_CH_NUM];
		uint32_t	send_idx_;
		uint32_t	send_ch_;

		uint16_t	treg_buff_[WAVE_CH_SIZE * 2];
		// WDM 通信用データバッファ
		char		wdm_buff_[WAVE_CH_SIZE * 2 + 1024];

		enum class task {
			idle,
			wdm_wait,
			wdm_send,
			treg_wait1,  // 熱抵抗測定待ち1
			treg_wait2,
			treg_send,
			
		};
		task		task_;

		uint32_t	wdm_emu_wait_;

		char		file_path_[32];

		void read_wave_file_()
		{
			FILE* fp = fopen(file_path_, "rb");
			if(fp == nullptr) return;
			for(uint32_t i = 0; i < 4; ++i) {
				uint32_t ofs = WAVE_CH_SIZE * i;
				uint32_t h = WAVE_CH_SIZE / 2;
				uint32_t hlen = WAVE_CH_SIZE;
				fread(&wave_buff_[ofs + h], 1, hlen, fp);
				fread(&wave_buff_[ofs + 0], 1, hlen, fp);
			}
			fclose(fp);
		}

		void filter9_(char* buf)
		{
			uint32_t len = strlen(buf);
			for(uint32_t i = len; i < 9; ++i) {
				buf[i] = 0x20;
			}
			buf[9] = 0;
		}

		void analize_()
		{
			auto n = str::get_words(line_);
			if(n >= 1) {
				char cmd[128];
				if(!str::get_word(line_, 0, cmd, sizeof(cmd))) {
					return;
				}
				char para[64];
				char para9[64];
				para[0] = 0;
				if(n >= 2 && str::get_word(line_, 1, para, sizeof(para))) {
					if(n >= 3) {  // エミュレーション拡張用
						file_path_[0] = 0;
						str::get_word(line_, 2, file_path_, sizeof(file_path_));
					}
					strcpy(para9, para);
					filter9_(para9);
//					utils::format("%s: '%s'\n") % cmd % para;
					para9[9] = '\n';
					para9[10] = 0;
				}

				if(strcmp(cmd, "help") == 0) {
					utils::format("Ignitor command shell Version %d.%02d\n")
						% (VERSION / 100) % (VERSION % 100);
					utils::format("  help\n");
					utils::format("  delay [n]\n");
					utils::format("  crm ...\n");
					utils::format("  wdm ...\n");
					utils::format("  dc2 ...\n");
					utils::format("  dc1 ...\n");
					utils::format("  wgm ...\n");
					utils::format("  icm ...\n");
				} else if(strcmp(cmd, "delay") == 0) {
					delay_ = 0;
					utils::input("%d", para) % delay_;
					if(delay_ > 10) delay_ = 10;
				} else if(strcmp(cmd, "crm") == 0) {
///					crm_out(para9);
				} else if(strcmp(cmd, "wdm") == 0) {
					uint32_t cmd = 0;
					utils::input("%x", para) % cmd;
					wdm_emu_wait_ = 10;
					if((cmd >> 19) == 0b00100) {
						utils::format("WDM Trigger Wait: '%s'\n") % file_path_;
						if(std::strlen(file_path_) > 0) {
							read_wave_file_();
						}
						if((cmd >> 8) & 0x02) {  // 熱抵抗トリガ待ち（外部トリガ）
							task_ = task::treg_wait1;
						} else {  // 通常波形トリガ待ち
							task_ = task::wdm_wait;
						}
					}
				} else if(strcmp(cmd, "dc2") == 0) {
///					dc2_out(para9);
				} else if(strcmp(cmd, "dc1") == 0) {
///					dc1_out(para9);
				} else if(strcmp(cmd, "wgm") == 0) {
///					wgm_out(para9);
				} else if(strcmp(cmd, "icm") == 0) {
///					icm_out(para9);
				} else {
					utils::format("Command error: '%s'\n") % cmd;
				}
			}
			utils::format("recv command: '%s'\n") % line_;
		}


		void wdm_capture_(uint32_t ch, int ofs)
		{
#if 0
//			wdmc_.set_wave_pos(ch + 1, ofs);
uint16_t vv = 32768;
			for(uint32_t i = 0; i < WAVE_CH_SIZE; ++i) {
//				wave_buff_[ch * WAVE_CH_SIZE + i] = wdmc_.get_wave(ch + 1);
				wave_buff_[ch * WAVE_CH_SIZE + i] = vv;
++vv;
				utils::delay::micro_second(1);
			}
#endif
		}


		void treg_capture_(uint32_t ch, int ofs, uint32_t dst)
		{
#if 0
//			wdmc_.set_wave_pos(ch + 1, ofs);
uint16_t vv = 32768;
			for(uint32_t i = 0; i < WAVE_CH_SIZE; ++i) {
//				treg_buff_[dst * WAVE_CH_SIZE + i] = wdmc_.get_wave(ch + 1);
				treg_buff_[dst * WAVE_CH_SIZE + i] = vv;
++vv;
				utils::delay::micro_second(1);
			}
#endif
		}


		void wdm_send_ch_(uint32_t ch)
		{
			char tmp[16];
			utils::sformat("WDCH%d\n", tmp, sizeof(tmp)) % ch;
			telnets_.puts(tmp);
		}


		void treg_send_ch_(uint32_t ch)
		{
			char tmp[16];
			utils::sformat("TRCH%d\n", tmp, sizeof(tmp)) % ch;
			telnets_.puts(tmp);
		}


		void wdm_send_size_(uint32_t size)
		{
			char tmp[16];
			utils::sformat("WDSZ%d\n", tmp, sizeof(tmp)) % size;
			telnets_.puts(tmp);
		}


		void wdm_send_(uint32_t ch, uint32_t num)
		{
			memcpy(wdm_buff_, "WDMW", 4);
			const uint16_t* src = &wave_buff_[ch * WAVE_CH_SIZE];
			uint32_t idx = 4;
			for(uint32_t i = 0; i < num; ++i) {
				char tmp[8];
				utils::sformat("%04X", tmp, sizeof(tmp))
					% src[send_idx_ % WAVE_CH_SIZE];
				++send_idx_;
				memcpy(&wdm_buff_[idx], tmp, 4);
				idx += 4;
					if(idx >= (sizeof(wdm_buff_) - 4)) {
					wdm_buff_[idx] = '\n';
					wdm_buff_[idx + 1] = 0;
					telnets_.puts(wdm_buff_);
					idx = 0;
				}
			}
			if(idx > 0) {
				wdm_buff_[idx] = '\n';
				wdm_buff_[idx + 1] = 0;
				telnets_.puts(wdm_buff_);
			}
		}


		void treg_send_(uint32_t ch, uint32_t num)
		{
			memcpy(wdm_buff_, "TRMW", 4);
			const uint16_t* src = &treg_buff_[ch * WAVE_CH_SIZE];
			uint32_t idx = 4;
			for(uint32_t i = 0; i < num; ++i) {
				char tmp[8];
				utils::sformat("%04X", tmp, sizeof(tmp))
					% src[send_idx_ % WAVE_CH_SIZE];
				++send_idx_;
				memcpy(&wdm_buff_[idx], tmp, 4);
				idx += 4;
					if(idx >= (sizeof(wdm_buff_) - 4)) {
					wdm_buff_[idx] = '\n';
					wdm_buff_[idx + 1] = 0;
					telnets_.puts(wdm_buff_);
					idx = 0;
				}
			}
			if(idx > 0) {
				wdm_buff_[idx] = '\n';
				wdm_buff_[idx + 1] = 0;
				telnets_.puts(wdm_buff_);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	telnets	TELNETサーバー・インスタンス
		*/
		//-----------------------------------------------------------------//
		ign_cmd(TELNETS& telnets) : telnets_(telnets),
			pos_(0), line_{ 0 },
			crm_ans_{ 0, }, crm_ans_pos_(0),
			dc2_ans_{ 0, }, dc2_ans_pos_(0),
			delay_(0), send_idx_(0), send_ch_(0),
			task_(task::idle), wdm_emu_wait_(0), file_path_{ 0 }
			{ }

		void start_treg()
		{
			task_ = task::treg_wait1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			switch(task_) {
			case task::idle:
				break;

			case task::wdm_wait:
//				if(wdmc_.get_status() & 0b010) {  // end record
				if(wdm_emu_wait_ > 0) {
					--wdm_emu_wait_;
					break;
				}
				{
					int ofs = -WAVE_CH_SIZE / 2;
					wdm_capture_(0, ofs);
					wdm_capture_(1, ofs);
					wdm_capture_(2, ofs);
					wdm_capture_(3, ofs);
//					wdmc_.output(0b00100000 << 16);  // trg off
					send_ch_ = 0;
					wdm_send_ch_(send_ch_);
					send_idx_ = 0;
					task_ = task::wdm_send;
				}
				break;

			case task::wdm_send:
				if(send_idx_ < WAVE_CH_SIZE) {
					wdm_send_(send_ch_, 512);  // 1 turn 512 ワード
				} else {
					++send_ch_;
					if(send_ch_ < 4) {
						wdm_send_ch_(send_ch_);
						send_idx_ = 0;
						task_ = task::wdm_send;
					} else {
						task_ = task::idle;
					}
				}
				break;

			case task::treg_wait1:
//				if(wdmc_.get_status() & 0b010) {  // end record
				if(wdm_emu_wait_ > 0) {
					--wdm_emu_wait_;
					break;
				}
				{
					int ofs = -WAVE_CH_SIZE / 2;
					treg_capture_(1, ofs, 0);
//					wdmc_.output(0x200201);  // trg off
					utils::delay::micro_second(1);
//					wdmc_.output(0x200281);
					task_ = task::treg_wait2;
				}
				break;

			case task::treg_wait2:
//				if(wdmc_.get_status() & 0b010) {  // end record
				if(0) {
					int ofs = -WAVE_CH_SIZE / 2;
					treg_capture_(1, ofs, 1);
//					wdmc_.output(0b00100000 << 16);  // trg off
					send_ch_ = 0;
					treg_send_ch_(0);
					send_idx_ = 0;
					task_ = task::treg_send;
				}
				break;

			case task::treg_send:
				if(send_idx_ < WAVE_CH_SIZE) {
					treg_send_(send_ch_, 512);  // 1 turn 512 ワード
				} else {
					++send_ch_;
					if(send_ch_ < 2) {
						treg_send_ch_(send_ch_);
						send_idx_ = 0;
						task_ = task::treg_send;
					} else {
						task_ = task::idle;
					}
				}
				break;

			default:
				break;
			}

			// 遅延タイマー
			if(delay_ > 0) {
				--delay_;
				return;
			}

			if(!telnets_.probe()) return;

			auto len = telnets_.length();
			if(len == 0) return;

			while(len > 0) {
				char ch = telnets_.getch();
				--len;
				if(ch == '\r') continue;
				else if(ch == '\n') {  // LF code
					ch = 0;
				}
				line_[pos_] = ch;
				++pos_;
				if(ch == 0 || pos_ >= (sizeof(line_) - 1)) {
					analize_();
					pos_ = 0;
					line_[pos_] = 0;
					if(delay_ > 0) break;
				}
			}
		}
	};
}
