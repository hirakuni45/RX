//=====================================================================//
/*! @file
    @brief  RX64M AUDIO サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			・DA0(P03):Left、DA1(P05):Right からアナログ出力する。@n
			・WAV 形式ファイルの再生
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/command.hpp"
#include "common/rspi_io.hpp"
#include "common/spi_io.hpp"
#include "common/spi_io2.hpp"
#include "common/sdc_man.hpp"
#include "common/string_utils.hpp"
#include "common/tpu_io.hpp"
#include "common/wav_in.hpp"

// #define SDHI_IF

namespace {

	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 256> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT8, device::bitpos::B2> SDC_POWER;	///< カード電源制御

#ifdef SDHI_IF
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER> SDHI;  ///< ハードウェアー定義
	SDHI	sdh_;
#else
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B3> MISO;
	typedef device::PORT<device::PORT7, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORT7, device::bitpos::B7> SPCK;

	typedef device::spi_io2<MISO, MOSI, SPCK> SPI;  ///< Soft SPI 定義
//	typedef device::rspi_io<device::RSPI> RSPI;  ///< Hard SPI 定義
//	RSPI rspi_;
	SPI		spi_;

	typedef device::PORT<device::PORTC, device::bitpos::B2> SDC_SELECT;  ///< カード選択信号
	typedef device::PORT<device::PORT8, device::bitpos::B1> SDC_DETECT;  ///< カード検出

	typedef fatfs::mmc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> MMC;   ///< ハードウェアー定義

	MMC		sdh_(spi_, 20000000);
#endif
	typedef utils::sdc_man SDC;
	SDC		sdc_;

	utils::command<256> cmd_;

	/// DMAC 終了割り込み
	class dmac_term_task {
	public:
		void operator() () {
			// DMA を再スタート
			device::DMAC0::DMCNT.DTE = 1;  // DMA を再開
		}
	};


	typedef device::dmac_mgr<device::DMAC0, dmac_term_task> DMAC_MGR;
	DMAC_MGR	dmac_mgr_;

	typedef device::R12DA DAC;
	typedef device::dac_out<DAC> DAC_OUT;
	DAC_OUT		dac_out_;

	struct wave_t {
		uint16_t	l;	///< D/A CH0
		uint16_t	r;	///< D/A CH1
	};

	// DMAC の転送最大値
	static const uint32_t WAVE_NUM = 1024;
	wave_t	wave_[WAVE_NUM];

	typedef device::tpu_io<device::TPU0, utils::null_task> TPU0;
	TPU0		tpu0_;

#if 0
	bool		init_ = false;
	float		freq_ = 100.0f;
	uint32_t	wpos_ = 0;
	imath::sincos_t sico_(0);
	void service_sin_cos_()
	{
		uint32_t pos = (dmac_mgr_.get_count() & 0x3ff) ^ 0x3ff;
		int32_t gain_shift = 16; 
		if(!init_) {
			sico_.x = static_cast<int64_t>(32767) << gain_shift;
			sico_.y = 0;
			wpos_ = pos & 0x3ff;
			init_ = true;
		}

		int32_t dt = static_cast<int32_t>(48000.0f / freq_);

		uint32_t d = pos - wpos_;
		if(d >= WAVE_NUM) d += WAVE_NUM;
		for(uint32_t i = 0; i < d; ++i) {
			wave_t w;
			w.l = (sico_.x >> gain_shift) + 32768;
			w.r = (sico_.y >> gain_shift) + 32768;
			wave_[(wpos_ + (WAVE_NUM / 2)) & (WAVE_NUM - 1)] = w;
			++wpos_;
			wpos_ &= WAVE_NUM - 1;
			imath::build_sincos(sico_, dt);
		}
	}
#endif
}


extern "C" {

	void bmp_putch(char ch)
	{
	}


	void bmp_locate(int8_t idx)
	{
	}


	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}


	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}


	char sci_getch(void)
	{
		return sci_.getch();
	}


	uint16_t sci_length()
	{
		return sci_.recv_length();
	}


	DSTATUS disk_initialize(BYTE drv) {
		return sdh_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return sdh_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdh_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdh_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdh_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		return 0;
	}


	void utf8_to_sjis(const char* src, char* dst, uint32_t len) {
		utils::str::utf8_to_sjis(src, dst, len);
	}


	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
	}
}


namespace {

	audio::wav_in	wav_in_;

	void play_(const char* fname);
	void play_loop_(const char*);


	void play_loop_func_(const char* name, const FILINFO* fi, bool dir, void* option)
	{
		if(dir) {
			play_loop_(name);
		} else {
			play_(name);
		}
	}


	void play_loop_(const char* root)
	{
///		sdc_.dir_loop(root, play_loop_func_);
	}


	void play_(const char* fname)
	{
		if(!sdc_.get_mount()) {
///			master_.at_task().set_param(4, 0, 2, 0x80);
			utils::format("SD Card unmount.\n");
			return;
		}

		FIL fil;
		if(!sdc_.open(&fil, fname, FA_READ)) {
///			master_.at_task().set_param(4, 0, 2, 0x80);
			utils::format("Can't open input file: '%s'\n") % fname;
			return;
		}

		if(!wav_in_.load_header(&fil)) {
///			master_.at_task().set_param(4, 0, 2, 0x80);
			f_close(&fil);
			utils::format("WAV file load fail: '%s'\n") % fname;
			return;
		}

		auto fsize = wav_in_.get_size();
		utils::format("File:   '%s'\n") % fname;
		utils::format("Size:   %d\n") % fsize;
		utils::format("Rate:   %d\n") % wav_in_.get_rate();
		utils::format("Chanel: %d\n") % static_cast<uint32_t>(wav_in_.get_chanel());
		utils::format("Bits:   %d\n") % static_cast<uint32_t>(wav_in_.get_bits());

		auto ti = wav_in_.get_time();
		utils::format("Time:   %02d:%02d:%02d\n") % (ti / 3600) % (ti / 60) % (ti % 60);

///		master_.at_task().set_rate(wav_in_.get_rate());
		uint8_t skip = 0;
		uint8_t l_ofs = 0;
		uint8_t r_ofs = 0;
		uint8_t wofs = 0;
		if(wav_in_.get_bits() == 8) {
			skip = wav_in_.get_chanel();
			if(wav_in_.get_chanel() == 1) {
				l_ofs = 0;
				r_ofs = 0;
			} else {
				l_ofs = 0;
				r_ofs = 1;
			}
		} else if(wav_in_.get_bits() == 16) {
			skip = wav_in_.get_chanel() * 2;
			if(wav_in_.get_chanel() == 1) {
				l_ofs = 1;
				r_ofs = 1;
			} else {
				l_ofs = 1;
				r_ofs = 3;
			}
			wofs = 0x80;
		} else {
			f_close(&fil);
			utils::format("Fail bits: '%s'\n") % fname;
			return;
		}
///		master_.at_task().set_param(skip, l_ofs, r_ofs, wofs);

		uint32_t fpos = 0;

///		uint16_t wpos = master_.at_task().get_pos();
		uint16_t wpos = 0;

		uint16_t pos = wpos;
		uint8_t n = 0;
		bool pause = false;
		uint8_t s_time = 0;
		uint8_t m_time = 0;
		uint8_t h_time = 0;
		uint16_t btime = 0;
		uint16_t dtime = 512 / (wav_in_.get_bits() / 8) / wav_in_.get_chanel();
		while(fpos < fsize) {
			if(!pause) {
///				while(((wpos ^ pos) & 512) == 0) {
///					pos = master_.at_task().get_pos();
///				}
///				uint8_t* buff = master_.at_task().get_buff();
///				UINT br;
///				if(f_read(&fil, &buff[wpos & 512], 512, &br) != FR_OK) {
///					utils::format("Abort: '%s'\n") % fname;
///					break;
///				}
				fpos += 512;
				wpos = pos;

				// LED モニターの点滅
				if(n >= 20) {  // play 時
					n = 0;
					LED::P = !LED::P();
				}
				++n;
			} else {  // pause 時
				if(n < 192) {
					LED::P = (n >> 5) & 1;
				} else {
					LED::P = 1;
				}
				utils::delay::milli_second(2);
				++n;
			}

			char ch = 0;
			if(sci_length() > 0) {
				ch = sci_getch();
			}

			if(ch == '>') {  // '>'
				break;
			} else if(ch == '<') {  // '<'
				fpos = 0;
				f_lseek(&fil, wav_in_.get_top());
			} else if(ch == ' ') {  // [space]
				if(pause) {
///					master_.at_task().pause(skip);
				} else {
///					master_.at_task().pause(0);
				}
				pause = !pause;
			}

			// 時間の積算と表示
			if(btime >= wav_in_.get_rate()) {
				btime -= wav_in_.get_rate();
				++s_time;
				if(s_time >= 60) { s_time = 0; ++m_time; }
				if(m_time >= 60) { m_time = 0; ++h_time; }
				utils::format("\r%02d:%02d:%02d")
					% static_cast<uint32_t>(h_time)
					% static_cast<uint32_t>(m_time)
					% static_cast<uint32_t>(s_time); 
			} else if(!pause) {
				btime += dtime;
			}
		}

///		master_.at_task().set_param(skip, l_ofs, r_ofs, wofs);

		f_close(&fil);

		utils::format("\n\n");
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

	{  // タイマー設定（１００Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(100, cmt_irq_level);
	}

	{  // SCI 設定
		uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

#ifdef SDHI_IF
	utils::format("RX64M SDHI SD-Card sample\n");
#else
	utils::format("RX64M Soft SPI SD-Card sample\n");
#endif
	{  // SD カード・クラスの初期化
		sdh_.start();
		sdc_.start();
	}

	{  // サンプリング・タイマー設定
		uint8_t intr_level = 5;
		if(!tpu0_.start(48000, intr_level)) {
			utils::format("TPU0 start error...\n");
		}
	}

	{  // 内臓１２ビット D/A の設定
		bool amp_ena = true;
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
	}

	{  // DMAC マネージャー開始
		uint8_t intr_level = 4;
		auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(wave_), DAC::DADR0.address(), WAVE_NUM, intr_level);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}

	cmd_.set_prompt("# ");

	LED::DIR = 1;

	uint32_t cnt = 0;
	char buff[16];
	while(1) {
		cmt_.sync();

		sdc_.service(sdh_.service());

		// コマンド入力と、コマンド解析
		if(cmd_.service()) {
			uint8_t cmdn = cmd_.get_words();
			if(cmdn >= 1) {
				char tmp[256];
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
				} else if(cmd_.cmp_word(0, "play")) {  // play [xxx]
					if(cmdn >= 2) {
						cmd_.get_word(1, sizeof(tmp), tmp);
						if(std::strcmp(tmp, "*") == 0) {
							play_loop_("");
						} else {
							play_(tmp);
						}
					} else {
						play_loop_("");
					}
///				} else if(cmd_.cmp_word(0, "power")) {
///					SDC_POWER::P = 0;
///					f = true;
				} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
					utils::format("dir [name]\n");
					utils::format("cd [directory-name]\n");
					utils::format("pwd\n");
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

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		device::PORT0::PODR.B7 = (cnt < 15) ? 0 : 1;
	}
}
