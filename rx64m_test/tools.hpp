#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 tools クラス
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"
#include <string>
#include <set>
#include <cstdlib>
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/input.hpp"
#include "preference.hpp"
#include "nets.hpp"

namespace seeda {

	nets& at_nets();

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  tools クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class tools {

		class cmt1_task {

		public:
			cmt1_task() { }

			void operator() () {
			}
		};
		typedef device::cmt_io<device::CMT1, cmt1_task> CMT1;
		CMT1		cmt1_;

		CMD			cmd_;

		uint32_t	flash_org_;
		uint32_t	flash_end_;

#ifdef SEEDA
		void adc_capture_(int ch, int rate, int num, const char* fname)
		{
			seeda::enable_eadc_server(false);

			// utils::format("ch:   %d\n") % ch;
			// utils::format("rate: %d\n") % rate;
			// utils::format("num:  %d\n") % num;
			// utils::format("name: '%s'\n") % fname;
			if(rate > 10000) {
				utils::format("Sample rate over: %d (Max: 10000)\n") % rate;
				return;
			}
			if((num * 2) > (1024 * 300)) {  // 300K バイト以上の場合
				utils::format("Memory not available: %d (Max: 300KBytes)\n") % (num * 2);
				return;
			}

			cmt1_.start(rate, 3);

			int16_t* buff = new int16_t[num];
			for(int i = 0; i < num; ++i) {
				cmt1_.sync();
				at_eadc().convert();
				uint16_t v = at_eadc().get_value(ch);
				buff[i] = v - 32768;
			}
			cmt1_.destroy();

			// write file
			FIL fp;
			if(!at_sdc().open(&fp, fname, FA_WRITE | FA_CREATE_ALWAYS)) {
				utils::format("Can't create file: '%s'\n") % fname;
				delete[] buff;
				seeda::enable_eadc_server();
				return;
			}

			UINT bw;
			f_write(&fp, buff, num * 2, &bw);
			f_close(&fp);

			delete[] buff;
			seeda::enable_eadc_server();
		}
#endif

		bool get_int_(uint8_t argc, int& val) {
			char tmp[32];
			if(cmd_.get_word(argc, sizeof(tmp), tmp)) {
				if((utils::input("%d", tmp) % val).status()) {
					return true;
				}
			}
			return false;
		}

		void param_error_(uint8_t argc)
		{
			char tmp[32];
			tmp[0] = 0;
			cmd_.get_word(argc, sizeof(tmp), tmp);					
			utils::format("param error: '%s'\n") % tmp;
		}

		const char* get_dec_(const char* p, char tmch, int& value) {
			int v = 0;
			char ch;
			while((ch = *p) != 0) {
				++p;
				if(ch == tmch) {
					break;
				} else if(ch >= '0' && ch <= '9') {
					v *= 10;
					v += ch - '0';
				} else {
					return nullptr;
				}
			}
			value = v;
			return p;
		}


		void set_time_date_()
		{
			time_t t = get_time();
			if(t == 0) return;

			struct tm *m = localtime(&t);
			bool err = false;
			if(cmd_.get_words() == 3) {
				char buff[12];
				if(cmd_.get_word(1, sizeof(buff), buff)) {
					const char* p = buff;
					int vs[3];
					uint8_t i;
					for(i = 0; i < 3; ++i) {
						p = get_dec_(p, '/', vs[i]);
						if(p == nullptr) {
							break;
						}
					}
					if(p != nullptr && p[0] == 0 && i == 3) {
						if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
						if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
						if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];		
					} else {
						err = true;
					}
				}

				if(cmd_.get_word(2, sizeof(buff), buff)) {
					const char* p = buff;
					int vs[3];
					uint8_t i;
					for(i = 0; i < 3; ++i) {
						p = get_dec_(p, ':', vs[i]);
						if(p == nullptr) {
							break;
						}
					}
					if(p != nullptr && p[0] == 0 && (i == 2 || i == 3)) {
						if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
						if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
						if(i == 3 && vs[2] >= 0 && vs[2] < 60) m->tm_sec = vs[2];
						else m->tm_sec = 0;
					} else {
						err = true;
					}
				}
			}

			if(err) {
				utils::format("Can't analize Time/Date input.\n");
				return;
			}

			time_t tt = mktime(m);
			set_time(tt);
		}


		bool check_mount_() {
			auto f = at_sdc().get_mount();
			if(!f) {
				utils::format("SD card not mount.\n");
			}
			return f;
		}

#ifdef SEEDA
		bool eadc_conv_(uint8_t cmdn)
		{
			bool f = false;
			if(cmdn == 1) {
///				if(eadc_.convert()) {
				for(int i = 0; i < 8; ++i) {
					uint32_t v = at_eadc().get_data(i);
					float fv = at_eadc().get_voltage(i);
					utils::format("LTC2348-16(%d): CHID: %d, SPAN: %03b, %6.3f [V] (%d)\n")
						% i % ((v >> 3) & 7) % (v & 7) % fv % (v >> 8);
				}
///				} else {
///					utils::format("LTC2348-16 convert error\n");
///				}
				return true;
			} else if(cmdn > 1) {
				char tmp[16];
				if(cmd_.get_word(1, sizeof(tmp), tmp)) {
					if(tmp[0] >= '0' && tmp[0] <= '7' && tmp[1] == 0) {
						if(at_eadc().convert()) {
							int ch = tmp[0] - '0';
							uint32_t v = at_eadc().get_value(ch);
							float fv = at_eadc().get_voltage(ch);
							utils::format("LTC2348-16(%d): %6.3f [V] (%d)\n") % ch % fv % v;
						} else {
							utils::format("LTC2348-16 convert error\n");
						}
					} else {
						utils::format("convert param error: '%s'\n") % tmp;
					}
					f = true;
				}
			}
			return f;
		}


		bool eadc_span_(uint8_t cmdn)
		{
			seeda::enable_eadc_server(false);

			if(cmdn >= 3) {
				int ch;
				if(get_int_(1, ch)) {
					int span;
					if(get_int_(2, span)) {
						at_eadc().set_span(ch, static_cast<EADC::span_type>(span));
					} else {
						param_error_(2);
					}
				} else {
					param_error_(1);
				}
			} else if(cmdn == 2) {
				int ch;
				if(get_int_(1, ch)) {
					auto span = at_eadc().get_span(ch);
					utils::format("LTC2348-16(%d): SPAN: %03b\n") % ch % static_cast<uint32_t>(span);
				} else {
					char tmp[32];
					tmp[0] = 0;
					cmd_.get_word(1, sizeof(tmp), tmp);					
					utils::format("param error: '%s'\n") % tmp;
				}
			} else {
				for(int i = 0; i < 8; ++i) {
					auto span = at_eadc().get_span(i);
					utils::format("LTC2348-16(%d): SPAN: %03b\n") % i % static_cast<uint32_t>(span);
				}			
			}

			seeda::enable_eadc_server();

			return true;
		}


		bool eadc_sample_(uint8_t cmdn)
		{
			if(cmdn < 8) {
				utils::format("sample param error...\n"); 
			} else {
				int mode = 0;
				int ch = -1;
				int rate = -1;
				int num = -1;
				char fname[32];
				fname[0] = 0;
				for(uint8_t i = 1; i < cmdn; ++i) {
					char tmp[32];
					if(cmd_.get_word(i, sizeof(tmp), tmp)) {
						if(tmp[0] == '-') {
							if(strcmp(tmp, "-ch") == 0) {
								mode = 1;
							} else if(strcmp(tmp, "-rate") == 0) {
								mode = 2;
							} else if(strcmp(tmp, "-num") == 0) {
								mode = 3;
							} else {
								utils::format("sample option error: '%s'\n") % tmp;
								return true;
							}
						} else {
							bool f = false;
							switch(mode) {
							case 0:
								strcpy(fname, tmp);
								f = true;
								break;
							case 1:
								f = (utils::input("%d", tmp) % ch).status();
								break;
							case 2:
								f = (utils::input("%d", tmp) % rate).status();
								break;
							case 3:
								f = (utils::input("%d", tmp) % num).status();
								break;
							}
							mode = 0;
							if(!f) {
								utils::format("sample option value error: '%s'\n") % tmp;
								return true;
							}
						}
					} else {
						return false;
					}
				}
				if(ch > 7 || ch < 0) {
					utils::format("sample chanel out range: %d\n") % ch;
				}
				adc_capture_(ch, rate, num, fname);
			}
			return true;
		}
#endif

	void list_arp_() const
	{
		auto n = ether_arp_num();
		for(uint32_t i = 0; i < n; ++i) {
			const auto* p = ether_arp_get(i);
			if(p->ae_state == AS_FREE) continue;

			utils::format("(%d) %d.%d.%d.%d  --->  %02X:%02X:%02X:%02X:%02X:%02X\n")
				% i
				% static_cast<uint32_t>(p->ae_pra[0])
				% static_cast<uint32_t>(p->ae_pra[1])
				% static_cast<uint32_t>(p->ae_pra[2])
				% static_cast<uint32_t>(p->ae_pra[3])
				% static_cast<uint32_t>(p->ae_hwa[0])
				% static_cast<uint32_t>(p->ae_hwa[1])
				% static_cast<uint32_t>(p->ae_hwa[2])
				% static_cast<uint32_t>(p->ae_hwa[3])
				% static_cast<uint32_t>(p->ae_hwa[4])
				% static_cast<uint32_t>(p->ae_hwa[5]);
		}
	}


	// データ flash の操作コマンド　
	void cmd_flash_(uint8_t cmdn)
	{
		typedef device::flash_io FLASH_IO;

		if(cmdn <= 1) {
			auto& fio = at_pre().at_fio();
	 		uint32_t n = 0;
			for(uint32_t i = 0; i < FLASH_IO::data_flash_size; i += FLASH_IO::data_flash_block) {
				if((n & 15) == 0) {
					utils::format("Flash bank (0x%06X): ") % i;
				}
				if((n & 3) == 0) {
					utils::format(" ");
				}
				utils::format("%c") % (fio.erase_check(i) ? 'e' : '-');
				if((n & 15) == 15) {
					utils::format("\n");
				}
				++n;
			}
			return;
		}

		uint8_t n = 1;
		uint32_t rdn = 0;
		uint8_t wrd[64];
		uint32_t wrn = 0;
		bool wm = false;
		bool erase = false;
		while(n < cmdn) {
			char tmp[128];
			cmd_.get_word(n, sizeof(tmp), tmp);
			if(std::strcmp(tmp, ":") == 0) {
				wm = true;
				++n;
				continue;
			} else if(std::strcmp(tmp, "-e") == 0) {
				erase = true;
				++n;
				continue;
			}
			const char* p = tmp;
			if(p[0] == ':') {
				++p;
				wm = true;
			}
			if(wm || wrn > 0) {
				uint32_t d;
				if(!(utils::input("%x", p) % d).status()) {
					utils::format("Flash data fail (%d): '%s'\n") % (n - 1) % tmp;
					return;
				}
				wrd[wrn] = d;
				++wrn;
			} else {
				uint32_t d;
				if(!(utils::input("%x", p) % d).status()) {
					utils::format("Flash address fail: %s\n") % tmp;
					return;
				}
				flash_org_ = flash_end_;
				flash_end_ = d;
				++rdn;
			}
			++n;
		}
		if(rdn == 1 || wrn > 0) {
			flash_org_ = flash_end_;
		}

		auto& fio = at_pre().at_fio();
		if(erase) {
			if(fio.erase_check(flash_org_)) {
				utils::format("Flash allready erase: 0x%06X\n") % flash_org_;
			} else {
				fio.erase(flash_org_);
			}
			return;
		}

		if(wrn > 0) {
//			utils::format("Write flash: %08X (%d)\n") % flash_org_ % wrn;
//			for(uint32_t i = 0; i < wrn; ++i) {
//				utils::format("(%06X) %02X\n") % (i + flash_org_) % static_cast<uint32_t>(wrd[i]);
//			}
			fio.write(flash_org_, wrd, wrn);
			flash_org_ += wrn;
		} else {
			if(flash_org_ > flash_end_) {
				utils::format("Flash read address area fail: 0x%06X to 0x%06X\n") % flash_org_ % flash_end_; 
				return;
			}
//			utils::format("Read flash: %08X to %08X\n") % flash_org_ % flash_end_;
			bool adrd = true;
			while(flash_org_ <= flash_end_) {
				if(adrd) {
					utils::format("%06X: ") % flash_org_;
					adrd = false;
				}
				auto d = fio.read(flash_org_);
				if((flash_org_ & 15) == 8) {
					utils::format(" - ");
				} else {
					utils::format(" ");
				}
				utils::format("%02X") % d;
				++flash_org_;
				if((flash_org_ & 15) == 0) {
					utils::format("\n");
					adrd = true;
				}
			}
			if((flash_org_ & 15) != 0) utils::format("\n");
		}
	}


	// write data 操作コマンド　
	bool write_data_(uint8_t cmdn)
	{
		if(cmdn == 1) {
			if(at_nets().at_write_file().get_enable()) {
				utils::format("write file: '%s' at %d/%d\n")
					% at_nets().at_write_file().get_path()
					% at_nets().at_write_file().get_resume()
					% at_nets().at_write_file().get_limit();
			} else {
				utils::format("write file: ready (no write file)\n");
			}
			return true;
		} else if(cmdn <= 3) {
			char tmp[128];
			int val = 0;
			if(cmd_.get_word(2, sizeof(tmp), tmp)) {
				if(!(utils::input("%d", tmp) % val).status()) {
					return false;
				}
				if(val <= 0) return false;
				if(cmd_.get_word(1, sizeof(tmp), tmp)) {
					at_nets().at_write_file().set_path(tmp);
					at_nets().at_write_file().set_limit(val);
					at_nets().at_write_file().enable();
					return true;
				}
			}
		}
		return false;
	}


	bool create_test_file_()
	{
		sd_speed_t t;
		utils::format("Start SD-CARD performance, wait for about 30 sec...\n");
		create_test_file("/write_test.bin", 1024 * 1024, t);
		utils::format("ライト・オープン： %d [ms]\n") % t.w_open_;
		utils::format("ライト： %3.2f [KB/Sec]\n") 
			% (1024.0f * 1000.0f / static_cast<float>(t.write_));
		utils::format("ライト・クローズ： %d [ms]\n") % t.w_close_;

		utils::format("リード・オープン： %d [ms]\n") % t.r_open_;
		utils::format("リード： %3.2f [KB/Sec]\n") 
			% (1024.0f * 1000.0f / static_cast<float>(t.read_));
		utils::format("リード・クローズ： %d [ms]\n") % t.r_close_;

		utils::format("ファイルリスト： %d [ms] / %d\n") % t.dirlist_ % t.dirlist_num_;
		return true;
	}



	bool cmd_setup_(uint8_t cmdn)
	{
		return false;
	}


	void list_service_() const
	{		
	}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		tools() : flash_org_(0), flash_end_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void init()
		{
			cmd_.set_prompt("# ");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイトル表示 @n
					LTC2348 A/D Converter ステート表示
		*/
		//-----------------------------------------------------------------//
		void title()
		{
#ifdef SEEDA
			if(at_eadc().probe()) {
				utils::format("Device LTC2348-16: Ready\n");
			} else {
				utils::format("Device LTC2348-16: Not Ready\n");
			}
#endif
			{
				time_t t = get_time();
				char tmp[128];
				disp_time(t, tmp, sizeof(tmp));
				utils::format("%s\n") % tmp;
			}

//			while(1) {
//				eadc_.convert();
//			}			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  データ列の評価
		*/
		//-----------------------------------------------------------------//
		void analize()
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			// コマンド入力と、コマンド解析
			if(cmd_.service()) {
				uint8_t cmdn = cmd_.get_words();
				if(cmdn >= 1) {
					bool f = false;
					if(cmd_.cmp_word(0, "dir")) {  // dir [xxx]
						if(check_mount_()) {
							if(cmdn >= 2) {
								char tmp[128];
								cmd_.get_word(1, sizeof(tmp), tmp);
								at_sdc().dir(tmp);
							} else {
								at_sdc().dir("");
							}
						}
						f = true;
					} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
						if(check_mount_()) {
							if(cmdn >= 2) {
								char tmp[128];
								cmd_.get_word(1, sizeof(tmp), tmp);
								at_sdc().cd(tmp);						
							} else {
								at_sdc().cd("/");
							}
						}
						f = true;
					} else if(cmd_.cmp_word(0, "pwd")) { // pwd
						utils::format("%s\n") % at_sdc().get_current();
						f = true;
					} else if(cmd_.cmp_word(0, "date")) {
						if(cmdn == 1) {
							time_t t = get_time();
							if(t != 0) {
								char tmp[128];
								disp_time(t, tmp, sizeof(tmp));
								utils::format("%s\n") % tmp;
							} else {
								utils::format("Stall RTC (no setting)\n");
							}
						} else {
							set_time_date_();
						}
						f = true;
					} else if(cmd_.cmp_word(0, "arp")) {  // arp table
						list_arp_();
						f = true;
					} else if(cmd_.cmp_word(0, "flash")) {
						cmd_flash_(cmdn);
						f = true;
					} else if(cmd_.cmp_word(0, "writedata")) {
						f = write_data_(cmdn);
					} else if(cmd_.cmp_word(0, "setup")) {
						f = cmd_setup_(cmdn);
					} else if(cmd_.cmp_word(0, "service")) {
						list_service_();
						f = true;
					} else if(cmd_.cmp_word(0, "fifo")) {
						utils::format("Write File FIFO: %d\n") % get_wf_fifo().length();
						f = true;
					} else if(cmd_.cmp_word(0, "testsd")) {
						f = create_test_file_();
#ifdef SEEDA
					} else if(cmd_.cmp_word(0, "eadc")) {
						f = eadc_conv_(cmdn);
					} else if(cmd_.cmp_word(0, "span")) {
						f = eadc_span_(cmdn);
					} else if(cmd_.cmp_word(0, "sample")) {
						f = eadc_sample_(cmdn);
//					} else if(cmd_.cmp_word(0, "reset")) {
//						f = reset_signal_(cmdn);
#endif
					} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
						utils::format("date\n");
						utils::format("date yyyy/mm/dd hh:mm[:ss]\n");
						utils::format("dir [name]\n");
						utils::format("cd [directory-name]\n");
						utils::format("pwd\n");
						utils::format("arp\n");
						utils::format("fifo\n");
						utils::format("testsd\n");
						utils::format("flash xxxx [:xx]  (Read/Wite data)\n");
#ifdef SEEDA
						utils::format("eadc [0-7]  (LTC2348 A/D conversion)\n");
						utils::format("span CH(0-7) SPAN(0-7)  (LTC2348 A/D span setting)\n"); 
						utils::format("sample -ch 0-7 -rate FRQ -num SAMPLE-NUM file-name (LTC2348 A/D sample)\n");
///						utils::format("reset [01]  (PHY reset signal)\n");
#endif
						utils::format("writedata base-str num(minits)\n");
						utils::format("setup\n");
						f = true;
					}
					if(!f) {
						char tmp[128];
						if(cmd_.get_word(0, sizeof(tmp), tmp)) {
							utils::format("Command error: '%s'\n") % tmp;
						}
					}
				}
			}
		}
	};
}
