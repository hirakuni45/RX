//=====================================================================//
/*! @file
    @brief  RX64M AUDIO（WAV ファイルの再生） サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			・DA0(P03):Left、DA1(P05):Right からアナログ出力する。@n
			・WAV 形式ファイルの再生 @n
			※GR-KAEDE で動かす場合、GR_KAEDE を有効にする。@n
			GR-KAEDE の SD カードハードウェアーには致命的な問題がある @n
			（SD カードを SPI モードで使う場合「DO」端子をプルアップ @n
			しておく必要があるのだが、プルダウンされている、なので、@n
			それを回避する為、PC3 を制御ポートして使う、PC3 から、PC7 @n
			へ １K オームで接続しておく。 @n
			また、GR-KAEDE の D/A-0 出力(P03)はボード上の LED4 に接続 @n
			されている。 @n
			コンソール出力は、J14（SCI7）を使う。
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

// GR-KAEDE の場合有効にする。
// #define GR_KAEDE

// MP3 のデコードを有効にする場合
#define MP3

#ifdef MP3
#include "common/mp3_in.hpp"
#endif

namespace {

#ifdef GR_KAEDE
	typedef device::PORT<device::PORTC, device::bitpos::B0> LED;
#else
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#endif

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 256> BUFFER;
#ifdef GR_KAEDE
	typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;
#else
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
#endif
	SCI		sci_;

#ifdef GR_KAEDE
	// SDC 用　SPI 定義（RSPI）
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< カード選択信号
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< カード検出

	typedef device::rspi_io<device::RSPI> SPI;
#else
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B3> MISO;
	typedef device::PORT<device::PORT7, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORT7, device::bitpos::B7> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SPI;  ///< Soft SPI 定義

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT8, device::bitpos::B2> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORTC, device::bitpos::B2> SDC_SELECT;  ///< カード選択信号
	typedef device::PORT<device::PORT8, device::bitpos::B1> SDC_DETECT;  ///< カード検出
#endif
	SPI		spi_;

	typedef fatfs::mmc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> MMC;   ///< ハードウェアー定義

	MMC		sdh_(spi_, 20000000);

	typedef utils::sdc_man SDC;
	SDC		sdc_;

	utils::command<256> cmd_;

	volatile uint32_t	wpos_;

	/// DMAC 終了割り込み
	class dmac_term_task {
	public:
		void operator() () {
			device::DMAC0::DMCNT.DTE = 1;  // DMA を再スタート
			wpos_ = 0;
		}
	};

	typedef device::dmac_mgr<device::DMAC0, dmac_term_task> DMAC_MGR;
	DMAC_MGR	dmac_mgr_;

	uint32_t get_wave_pos_() { return (dmac_mgr_.get_count() & 0x3ff) ^ 0x3ff; }

	typedef device::R12DA DAC;
	typedef device::dac_out<DAC> DAC_OUT;
	DAC_OUT		dac_out_;

	typedef utils::audio_out<16384> AUDIO_OUT;
	AUDIO_OUT	audio_out_;

	class tpu_task {
	public:
		void operator() () {
			uint32_t tmp = wpos_;
			++wpos_;
			if((tmp ^ wpos_) & 64) {
				audio_out_.service(64);
			}
		}
	};

	typedef device::tpu_io<device::TPU0, tpu_task> TPU0;
	TPU0		tpu0_;	
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
	void play_wav_(const char* fname);

#ifdef MP3
	audio::mp3_in	mp3_in_;
	void play_mp3_(const char* fname);
#endif

	void play_loop_(const char*);


	void play_loop_func_(const char* name, const FILINFO* fi, bool dir, void* option)
	{
		if(dir) {
			play_loop_(name);
		} else {
			const char* ext = strrchr(name, '.');
			if(ext != nullptr) {
				if(strcmp(ext, ".wav") == 0) {
					play_wav_(name);
				} else if(strcmp(ext, ".mp3") == 0) {
					play_mp3_(name);
				}
			}
		}
	}


	void play_loop_(const char* root)
	{
		sdc_.set_dir_list_limit(1);
		sdc_.start_dir_list(root, play_loop_func_);
	}


	void play_wav_(const char* fname)
	{
		if(!sdc_.get_mount()) {
///			master_.at_task().set_param(4, 0, 2, 0x80);
			utils::format("SD Card unmount.\n");
			return;
		}

		FIL fil;
		if(!sdc_.open(&fil, fname, FA_READ)) {
			audio_out_.mute();
			utils::format("Can't open input file: '%s'\n") % fname;
			return;
		}

		if(!wav_in_.load_header(&fil)) {
			audio_out_.mute();
			f_close(&fil);
			utils::format("WAV file load fail: '%s'\n") % fname;
			return;
		}

		auto fsize = wav_in_.get_size();
		utils::format("File:  '%s'\n") % fname;
		utils::format("Size:   %d\n") % fsize;
		utils::format("Rate:   %d\n") % wav_in_.get_rate();
		utils::format("Chanel: %d\n") % static_cast<uint32_t>(wav_in_.get_chanel());
		utils::format("Bits:   %d\n") % static_cast<uint32_t>(wav_in_.get_bits());

		auto ti = wav_in_.get_time();
		utils::format("Time:   %02d:%02d:%02d\n") % (ti / 3600) % (ti / 60) % (ti % 60);

		{
			uint8_t intr_level = 5;
			if(!tpu0_.start(wav_in_.get_rate(), intr_level)) {
				utils::format("TPU0 init fail...\n");
				return;
			}
		}
		{  // Supports: 8/16 bits, 1(mono)/2(stereo) chennel
			auto ch = wav_in_.get_chanel();
			auto bt = wav_in_.get_bits();
			if(bt == 8 && ch <= 2) {
			} else if(bt == 16 && ch <= 2) {
			} else {
				f_close(&fil);
				utils::format("Fail WAV file format (8 or 16 bits, mono/stereo): '%s'\n") % fname;
				return;
			}
		}

		uint32_t fpos = 0;
		uint16_t wpos = get_wave_pos_();
		uint16_t pos = wpos;
		uint8_t n = 0;
		bool pause = false;
		uint8_t s_time = 0;
		uint8_t m_time = 0;
		uint8_t h_time = 0;
		uint16_t btime = 0;
		uint16_t dtime = 512 / (wav_in_.get_bits() / 8) / wav_in_.get_chanel();
		uint16_t nnn = wpos & 0x380;
		while(fpos < fsize) {
			if(!pause) {
				while(((wpos ^ pos) & 128) == 0) {
					pos = get_wave_pos_();
				}
				uint32_t unit = (wav_in_.get_bits() / 8) * wav_in_.get_chanel();
				UINT br;
				uint8_t tmp[512];
				if(f_read(&fil, tmp, unit * 128, &br) != FR_OK) {
					utils::format("f_read fail abort: '%s'\n") % fname;
					audio_out_.mute();
					break;
				}
				audio::wave_t* dst = audio_out_.get_wave((nnn + 512) & 0x3ff);
				if(wav_in_.get_bits() == 16) {
					const uint16_t* src = reinterpret_cast<const uint16_t*>(tmp);
					for(uint32_t i = 0; i < 128; ++i) {
						if(wav_in_.get_chanel() == 2) {
							dst[i].l_ch = src[0] ^ 0x8000;
							dst[i].r_ch = src[1] ^ 0x8000;
							src += 2;
						} else {
							dst[i].l_ch = src[0] ^ 0x8000;
							dst[i].r_ch = dst[i].l_ch;
							++src;
						}
					}
				} else {  // 8 bits
					const uint8_t* src = reinterpret_cast<const uint8_t*>(tmp);
					for(uint32_t i = 0; i < 128; ++i) {
						if(wav_in_.get_chanel() == 2) {
							dst[i].l_ch = static_cast<uint16_t>(src[0] ^ 0x80) << 8;
							dst[i].l_ch |= (src[0] & 0x7f) << 1;
							dst[i].r_ch = static_cast<uint16_t>(src[1] ^ 0x80) << 8;
							dst[i].l_ch |= (src[1] & 0x7f) << 1;
							src += 2;
						} else {
							dst[i].l_ch = static_cast<uint16_t>(src[0] ^ 0x80) << 8;
							dst[i].l_ch |= (src[0] & 0x7f) << 1;
							dst[i].r_ch = dst[i].l_ch;
							++src;
						}
					}
				}
				nnn += 128;
				fpos += unit * 128;  // file position
				wpos = pos;   // wave memory position

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
				nnn = get_wave_pos_() & 0x380;
			}

			char ch = 0;
			if(sci_length() > 0) {
				ch = sci_getch();
			}

			if(ch == '>') {  // '>'
				audio_out_.mute();
				break;
			} else if(ch == '<') {  // '<'
				audio_out_.mute();
				fpos = 0;
				f_lseek(&fil, wav_in_.get_top());
				s_time = m_time = h_time = 0;
			} else if(ch == ' ') {  // [space]
				pause = !pause;
				if(pause) {  // pause になった・・
					audio_out_.mute();
				}
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
		f_close(&fil);

		utils::format("\n\n");
	}

#ifdef MP3

	void play_mp3_(const char* fname)
	{
		utils::file_io fin(sdc_);

		if(!fin.open(fname, "rb")) {
			return;
		}

		utils::format("%s\n") % fname;

		mp3_in_.decode(fin, audio_out_);

		fin.close();

		utils::format("\n");
	}

#endif
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
#ifdef GR_KAEDE
	// GR-KAEDE の SD カードバグ回避
	// ※PC3 から、PC7 へ １K オームで接続
	device::PORTC::PDR.B3 = 1; // output
	device::PORTC::PODR.B3 = 1;
#endif

	device::system_io<12000000>::setup_system_clock();

	{  // タイマー設定（１００Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(100, cmt_irq_level);
	}

	{  // SCI 設定
		uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // 内臓１２ビット D/A の設定
		bool amp_ena = true;
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
		dac_out_.out0(0x8000);
		dac_out_.out1(0x8000);
	}

#ifdef GR_KAEDE
	utils::format("\nRX64M (GR-KAEDE) AUDIO Player sample\n");
#else
	utils::format("\nRX64M AUDIO Player sample\n");
#endif

	{  // SD カード・クラスの初期化
		sdh_.start();
		sdc_.start();
	}

	// 波形メモリーの無音状態初期化
	audio_out_.mute();

	{  // サンプリング・タイマー設定
		uint8_t intr_level = 5;
		if(!tpu0_.start(44100, intr_level)) {
			utils::format("TPU0 start error...\n");
		}
	}

	{  // DMAC マネージャー開始
		uint8_t intr_level = 4;
		auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(audio_out_.get_wave()), DAC::DADR0.address(),
			audio_out_.size(), intr_level);
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
							play_wav_(tmp);
						}
					} else {
						play_loop_("");
					}
					f = true;
				} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
					utils::format("dir [name]\n");
					utils::format("cd [directory-name]\n");
					utils::format("pwd\n");
					utils::format("play file-name\n");
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
		LED::P = (cnt < 15) ? 0 : 1;
	}
}
