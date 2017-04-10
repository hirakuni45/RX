#pragma once
//=====================================================================//
/*! @file
    @brief  seeda tools クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <string>
#include "common/renesas.hpp"

#include "common/rspi_io.hpp"
#include "common/spi_io.hpp"
#include "common/sdc_io.hpp"
#include "common/command.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/cmt_io.hpp"

#include "common/time.h"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  tools クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class tools {

		typedef utils::rtc_io RTC;
		RTC		rtc_;

		// Soft SDC 用　SPI 定義（SPI）
		typedef device::PORT<device::PORTD, device::bitpos::B6> MISO;
		typedef device::PORT<device::PORTD, device::bitpos::B4> MOSI;
		typedef device::PORT<device::PORTD, device::bitpos::B5> SPCK;
		typedef device::spi_io<MISO, MOSI, SPCK> SPI;
		SPI		spi_;

		typedef device::PORT<device::PORTD, device::bitpos::B3> SDC_SELECT;	///< カード選択信号
		typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
		typedef device::PORT<device::PORTE, device::bitpos::B6> SDC_DETECT;	///< カード検出

		typedef utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;
		SDC		sdc_;

		utils::command<256> cmd_;

		typedef device::PORT<device::PORT7, device::bitpos::B0> LAN_RESN;
		typedef device::PORT<device::PORT7, device::bitpos::B3> LAN_PDN;

		// LTC2348-16 A/D 制御ポート定義
		typedef device::PORT<device::PORT4, device::bitpos::B0> LTC_CSN;   // P40(141)
		typedef device::PORT<device::PORTC, device::bitpos::B6> LTC_CNV;   // PC6(61)
		typedef device::PORT<device::PORTD, device::bitpos::B0> LTC_BUSY;  // PD0/IRQ0(126)
		typedef device::PORT<device::PORT5, device::bitpos::B3> LTC_PD;    // P53(53)
		typedef device::PORT<device::PORT5, device::bitpos::B6> LTC_SDI;   // P56(50)
		typedef device::PORT<device::PORT8, device::bitpos::B6> LTC_SCKO;  // P86(41)
		typedef device::PORT<device::PORT8, device::bitpos::B7> LTC_SCKI;  // P87(39)
		typedef device::PORT<device::PORT2, device::bitpos::B0> LTC_SDO0;  // P20(37)
		typedef device::PORT<device::PORT2, device::bitpos::B1> LTC_SDO2;  // P21(36)
		typedef device::PORT<device::PORT2, device::bitpos::B2> LTC_SDO4;  // P22(35)
		typedef device::PORT<device::PORT2, device::bitpos::B3> LTC_SDO6;  // P23(34)
		typedef struct chip::LTC2348_SDO_t<LTC_SCKO, LTC_SDO0, LTC_SDO2, LTC_SDO4, LTC_SDO6> LTC_SDO;
		typedef chip::LTC2348_16<LTC_CSN, LTC_CNV, LTC_BUSY, LTC_PD, LTC_SDI, LTC_SCKI, LTC_SDO> EADC;
		EADC	eadc_;

		class null_task {
		public:
			void operator() () { }
		};
		typedef device::cmt_io<device::CMT1, null_task> CMT1;
		CMT1	cmt1_;


		void adc_capture_(int ch, int rate, int num, const char* fname)
		{
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
				eadc_.convert();
				uint16_t v = eadc_.get_value(ch);
				buff[i] = v - 32768;
			}
			cmt1_.destroy();

			// write file
			FIL fp;
			if(!sdc_.open(&fp, fname, FA_WRITE | FA_CREATE_ALWAYS)) {
				utils::format("Can't create file: '%s'\n") % fname;
				delete[] buff;
				return;
			}

			UINT bw;
			f_write(&fp, buff, num * 2, &bw);
			f_close(&fp);

			delete[] buff;
		}


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
			if(!rtc_.set_time(tt)) {
				utils::format("Stall RTC write...\n");
			}
		}


		bool check_mount_() {
			auto f = sdc_.get_mount();
			if(!f) {
				utils::format("SD card not mount.\n");
			}
			return f;
		}


		bool reset_signal_(uint8_t cmdn)
		{
			bool f = false;
			if(cmdn == 1) {
				bool v = LAN_RESN::P();
				utils::format("LAN-RESN: %d\n") % static_cast<int>(v);
				return true;
			} else if(cmdn > 1) {
				char tmp[16];
				if(cmd_.get_word(1, sizeof(tmp), tmp)) {
					// Reset signal
					if(strcmp(tmp, "0") == 0) {
						device::PORT7::PODR.B0 = 0;
						f = true;
					} else if(strcmp(tmp, "1") == 0) {
						device::PORT7::PODR.B0 = 1;
						f = true;
					} else {
						utils::format("reset param error: '%s'\n") % tmp;
					}
				}
			}
			return f;
		}


		bool eadc_conv_(uint8_t cmdn)
		{
			bool f = false;
			if(cmdn == 1) {
				if(eadc_.convert()) {
					for(int i = 0; i < 8; ++i) {
						uint32_t v = eadc_.get_data(i);
						float fv = eadc_.get_voltage(i);
						utils::format("LTC2348-16(%d): CHID: %d, SPAN: %03b, %6.3f [V] (%d)\n")
							% i % ((v >> 3) & 7) % (v & 7) % fv % (v >> 8);
					}
				} else {
					utils::format("LTC2348-16 convert error\n");
				}
				return true;
			} else if(cmdn > 1) {
				char tmp[16];
				if(cmd_.get_word(1, sizeof(tmp), tmp)) {
					if(tmp[0] >= '0' && tmp[0] <= '7' && tmp[1] == 0) {
						if(eadc_.convert()) {
							int ch = tmp[0] - '0';
							uint32_t v = eadc_.get_value(ch);
							float fv = eadc_.get_voltage(ch);
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
			if(cmdn >= 3) {
				int ch;
				if(get_int_(1, ch)) {
					int span;
					if(get_int_(2, span)) {
						eadc_.set_span(ch, static_cast<EADC::span_type>(span));
					} else {
						param_error_(2);
					}
				} else {
					param_error_(1);
				}
			} else if(cmdn == 2) {
				int ch;
				if(get_int_(1, ch)) {
					auto span = eadc_.get_span(ch);
					utils::format("LTC2348-16(%d): SPAN: %03b\n") % ch % static_cast<uint32_t>(span);
				} else {
					char tmp[32];
					tmp[0] = 0;
					cmd_.get_word(1, sizeof(tmp), tmp);					
					utils::format("param error: '%s'\n") % tmp;
				}
			} else {
				for(int i = 0; i < 8; ++i) {
					auto span = eadc_.get_span(i);
					utils::format("LTC2348-16(%d): SPAN: %03b\n") % i % static_cast<uint32_t>(span);
				}			
			}
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

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		tools() : sdc_(spi_, 10000000) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  時間の取得
			@return 時間
		*/
		//-----------------------------------------------------------------//
		time_t get_time() const {
			time_t t = 0;
			rtc_.get_time(t);
			return t;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  時間の表示
			@param[in]	t		時間
			@param[in]	dst		出力文字列
			@param[in]	size	文字列の大きさ
		*/
		//-----------------------------------------------------------------//
		void disp_time(time_t t, char* dst = nullptr, uint32_t size = 0)
		{
			struct tm *m = localtime(&t);
			utils::format("%s %s %d %02d:%02d:%02d  %4d\n", dst, size)
				% get_wday(m->tm_wday)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec)
				% static_cast<uint32_t>(m->tm_year + 1900);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void init()
		{
			// RTC 設定
			rtc_.start();

			// SD カード・クラスの初期化
			sdc_.start();

			{  // LAN initialize (PHY reset, PHY POWER-DOWN
				LAN_PDN::DIR = 1;  // output;
				LAN_PDN::P = 1;    // Not Power Down Mode..
				LAN_RESN::DIR = 1; // output;

				LAN_RESN::P = 0;
				utils::delay::milli_second(200); /// reset time
				LAN_RESN::P = 1;
			}

			{  // LTC2348ILX-16 初期化
				// 内臓リファレンスと内臓バッファ
				// VREFIN: 2.024V、VREFBUF: 4.096V、Analog range: 0V to 5.12V
				if(!eadc_.start(1000000, EADC::span_type::P5_12)) {
					utils::format("LTC2348_16 not found...\n");
				}
			}

			cmd_.set_prompt("# ");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  LTC2348 A/D Converter ステート表示
		*/
		//-----------------------------------------------------------------//
		void list_eadc()
		{
			if(eadc_.probe()) {
				utils::format("Device LTC2348-16: Ready\n");
			} else {
				utils::format("Device LTC2348-16: Not Ready\n");
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			sdc_.service();

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
								sdc_.dir(tmp);
							} else {
								sdc_.dir("");
							}
						}
						f = true;
					} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
						if(check_mount_()) {
							if(cmdn >= 2) {
								char tmp[128];
								cmd_.get_word(1, sizeof(tmp), tmp);
								sdc_.cd(tmp);						
							} else {
								sdc_.cd("/");
							}
						}
						f = true;
					} else if(cmd_.cmp_word(0, "pwd")) { // pwd
						utils::format("%s\n") % sdc_.get_current();
						f = true;
					} else if(cmd_.cmp_word(0, "date")) {
						if(cmdn == 1) {
							time_t t = get_time();
							if(t != 0) {
								disp_time(t);
							}
						} else {
							set_time_date_();
						}
						f = true;
					} else if(cmd_.cmp_word(0, "reset")) {
						f = reset_signal_(cmdn);
					} else if(cmd_.cmp_word(0, "eadc")) {
						f = eadc_conv_(cmdn);
					} else if(cmd_.cmp_word(0, "span")) {
						f = eadc_span_(cmdn);
					} else if(cmd_.cmp_word(0, "sample")) {
						f = eadc_sample_(cmdn);
					} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
						utils::format("date\n");
						utils::format("date yyyy/mm/dd hh:mm[:ss]\n");
						utils::format("dir [name]\n");
						utils::format("cd [directory-name]\n");
						utils::format("pwd\n");
						utils::format("reset [01]  (PHY reset signal)\n");
						utils::format("eadc [0-7]  (LTC2348 A/D conversion)\n");
						utils::format("span CH(0-7) SPAN(0-7)  (LTC2348 A/D span setting)\n"); 
						utils::format("sample -ch 0-7 -rate FRQ -num SAMPLE-NUM file-name (LTC2348 A/D sample)\n");
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


		DSTATUS disk_initialize(BYTE drv)
		{
			return sdc_.at_mmc().disk_initialize(drv);
		}


		DSTATUS disk_status(BYTE drv)
		{
			return sdc_.at_mmc().disk_status(drv);
		}


		DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count)
		{
			return sdc_.at_mmc().disk_read(drv, buff, sector, count);
		}


		DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count)
		{
			return sdc_.at_mmc().disk_write(drv, buff, sector, count);
		}


		DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff)
		{
			return sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
		}
	};
}
