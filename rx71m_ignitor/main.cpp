//=====================================================================//
/*! @file
    @brief  RX71M イグナイター
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/scif_io.hpp"
#include "common/sci_io.hpp"
#include "common/rspi_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"

#include "common/sdc_io.hpp"

#include "main.hpp"
#include "http.hpp"

#include "ign_cmd.hpp"
#include "wdmc.hpp"

namespace {

	static const int MAIN_VERSION = 85;

	typedef device::PORT<device::PORT0, device::bitpos::B2> LED0;
	typedef device::PORT<device::PORT0, device::bitpos::B3> LED1;
	typedef device::PORT<device::PORTC, device::bitpos::B0> LED2;
	typedef device::PORT<device::PORTC, device::bitpos::B1> LED3;

	class cmt_task
	{
		void (*task_10ms_)();

		volatile uint32_t millis10x_;

	public:
		cmt_task() : task_10ms_(nullptr),
			millis10x_(0) { }

		void operator() () {
			if(task_10ms_ != nullptr) (*task_10ms_)();
			++millis10x_;
		}

		void set_task_10ms(void (*task)(void)) {
			task_10ms_ = task;
		}

		volatile unsigned long get_millis() const { return millis10x_ * 10; }
	};

	typedef device::cmt_io<device::CMT0, cmt_task> CMT;
	CMT		cmt_;

	utils::wdmc		wdmc_;

	typedef utils::fixed_fifo<char, 128> RX_BUF;
	typedef utils::fixed_fifo<char, 256> TX_BUF;

	typedef utils::fixed_fifo<char, 1024> RX_SCI;
	typedef utils::fixed_fifo<char, 4096> TX_SCI;

	typedef device::sci_io<device::SCI12, RX_SCI, TX_SCI> SCI;
	SCI		sci_;

	// CRM interface (SCIF10, FIRST)
	typedef device::scif_io<device::SCIF10, RX_BUF, TX_BUF> CRM;
	CRM		crm_(false);

	// DC2 interface (SCI2, SECOND)
	typedef device::sci_io<device::SCI2, RX_BUF, TX_BUF, device::port_map::option::SECOND> DC2;
	DC2		dc2_(false);

	// DC1 interface (SCI6, FIRST)
	typedef device::sci_io<device::SCI6, RX_BUF, TX_BUF> DC1;
	DC1		dc1_(false);

	// WGM interface (SCI7, FIRST)
	typedef device::sci_io<device::SCI7, RX_BUF, TX_BUF> WGM;
	WGM		wgm_(false);

	// ICM interface (SCI3, FIRST)
	typedef device::sci_io<device::SCI3, RX_BUF, TX_BUF> ICM;
	ICM		icm_(false);

	utils::command<256> cmd_;

	typedef utils::rtc_io RTC;
	RTC		rtc_;

//	SDC_RSPI	sdc_spi_;
//	typedef utils::sdc_io<SDC_RSPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;
//	SDC		sdc_(sdc_spi_, 20000000);

	net::ethernet   ethernet_;
	HTTP_SERVER     https_(ethernet_);
	TELNETS			telnets_(ethernet_, false);

	http<HTTP_SERVER>	http_(https_);

	utils::ign_cmd<TELNETS>	ign_cmd_(telnets_, wdmc_);

	char	wdm_buff_[8192];

	uint16_t	wave_buff_[2048];
	uint32_t	send_idx_;

	bool		send_all_;

	// 文字列表示、割り込み対応ロック／アンロック機構
	volatile bool putch_lock_ = false;
	utils::fixed_fifo<char, 1024> putch_tmp_;

	void service_putch_tmp_()
	{
		dis_int();
		while(putch_tmp_.length() > 0) {
			auto ch = putch_tmp_.get();
			sci_.putch(ch);
		}
		ena_int();
	}

	//-----------------------------------------------------------------//
	/*!
		@brief  時間の作成
		@param[in]	date	日付
		@param[in]	time	時間
	*/
	//-----------------------------------------------------------------//
	size_t make_time(const char* date, const char* time)
	{
		time_t t = get_time();
		struct tm *m = localtime(&t);
		int vs[3];
		if((utils::input("%d/%d/%d", date) % vs[0] % vs[1] % vs[2]).status()) {
			if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
			if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
			if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];		
		} else {
			return 0;
		}

		if((utils::input("%d:%d:%d", time) % vs[0] % vs[1] % vs[2]).status()) {
			if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
			if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
			if(vs[2] >= 0 && vs[2] < 60) m->tm_sec = vs[2];
		} else if((utils::input("%d:%d", time) % vs[0] % vs[1]).status()) {
			if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
			if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
			m->tm_sec = 0;
		} else {
			return 0;
		}
		return mktime(m);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の設定
		@param[in]	t	GMT 時間
	*/
	//-----------------------------------------------------------------//
	void set_time(time_t t)
	{
		if(t != 0) {
			rtc_.set_time(t);
		}
	}


	void crm_out(const char* out)
	{
		crm_.puts(out);
	}


	uint32_t crm_len()
	{
		return crm_.recv_length();
	}


	char crm_inp()
	{
		return crm_.getch();
	}


	void dc2_out(const char* out)
	{
		dc2_.puts(out);
	}


	uint32_t dc2_len()
	{
		return dc2_.recv_length();
	}


	char dc2_inp()
	{
		return dc2_.getch();
	}


	void dc1_out(const char* out)
	{
		dc1_.puts(out);
	}


	void wgm_out(const char* out)
	{
		wgm_.puts(out);
	}


	void icm_out(const char* out)
	{
		icm_.puts(out);
	}


	void wdm_out(uint32_t cmd)
	{
		wdmc_.output(cmd);
	}


	void wdm_capture(uint32_t ch)
	{
		wdmc_.set_wave_pos(ch, -1024);
		for(int i = 0; i < 2048; ++i) {
			wave_buff_[i] = wdmc_.get_wave(ch + 1);
		}
	}


	void wdm_send_(uint32_t num)
	{
		memcpy(wdm_buff_, "WDMW", 4);
		uint32_t idx = 4;
		for(uint32_t i = 0; i < num; ++i) {
			char tmp[8];
			utils::sformat("%04X", tmp, sizeof(tmp)) % wave_buff_[send_idx_ & 2047];
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
}

extern "C" {

	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time()
	{
		time_t t = 0;
		rtc_.get_time(t);
		return t;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字出力
		@param[in]	ch	文字
	*/
	//-----------------------------------------------------------------//
	void sci_putch(char ch)
	{
		if(putch_lock_) {
			if((putch_tmp_.size() - putch_tmp_.length()) >= 2) {
				putch_tmp_.put(ch);
			}
			return;
		}
		putch_lock_ = true;
		sci_.putch(ch);
///		telnets_.putch(ch);
		putch_lock_ = false;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列出力
		@param[in]	s	文字列
	*/
	//-----------------------------------------------------------------//
	void sci_puts(const char* s)
	{
		sci_.puts(s);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字入力
		@return	文字
	*/
	//-----------------------------------------------------------------//
	char sci_getch(void)
	{
		return sci_.getch();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列長の取得
		@return	文字列長
	*/
	//-----------------------------------------------------------------//
	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へ初期化関数を提供
		@param[in]	drv		Physical drive nmuber (0)
		@return ステータス
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_initialize(BYTE drv) {
//		return sdc_.at_mmc().disk_initialize(drv);
		return RES_OK;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へステータスを提供
		@param[in]	drv		Physical drive nmuber (0)
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_status(BYTE drv) {
//		return sdc_.at_mmc().disk_status(drv);
		return RES_OK;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へリード・セクターを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[out]	buff	Pointer to the data buffer to store read data
		@param[in]	sector	Start sector number (LBA)
		@param[in]	count	Sector count (1..128)
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
//		return sdc_.at_mmc().disk_read(drv, buff, sector, count);
		return RES_OK;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へライト・セクターを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[in]	buff	Pointer to the data to be written	
		@param[in]	sector	Start sector number (LBA)
		@param[in]	count	Sector count (1..128)
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
//		return sdc_.at_mmc().disk_write(drv, buff, sector, count);
		return RES_OK;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へI/O コントロールを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[in]	ctrl	Control code
		@param[in]	buff	Buffer to send/receive control data
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
//		return sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
		return RES_OK;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へ時間を提供
		@return FatFs 時間
	 */
	//-----------------------------------------------------------------//
	DWORD get_fattime(void) {
		auto t = get_time();
		return utils::str::get_fattime(t);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-8 から ShiftJIS への変換
		@param[in]	src	UTF-8 文字列ソース
		@param[out]	dst	ShiftJIS 文字列出力
		@param[in]	dsz	文字列出力サイズ
	 */
	//-----------------------------------------------------------------//
	void utf8_to_sjis(const char* src, char* dst, uint16_t dsz) {
		utils::str::utf8_to_sjis(src, dst, dsz);
	}


	unsigned long millis(void)
	{
		return cmt_.at_task().get_millis();
	}


	void set_task_10ms(void (*task)(void)) {
		cmt_.at_task().set_task_10ms(task);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

	LED0::DIR = 1;
	LED1::DIR = 1;
	LED2::DIR = 1;
	LED3::DIR = 1;

	{  // タイマー設定 (100Hz) 10ms
		uint8_t int_level = 4;
		cmt_.start(100, int_level);
	}

	{  // RTC 開始
		rtc_.start();
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);

		crm_.start(115200, int_level);
		dc2_.start(115200, int_level);
		dc1_.start(115200, int_level);
		wgm_.start(115200, int_level);
		icm_.start(115200, int_level);
	}

	wdmc_.start();

	send_all_ = false;

	utils::format("\nStart RX71M Ignitor Build: %d Verision %d.%02d\n") % BUILD_ID
		% (MAIN_VERSION / 100) % (MAIN_VERSION % 100);
	cmd_.set_prompt("# ");

	// SD カード・クラスの初期化
//	sdc_.start();

	device::power_cfg::turn(device::peripheral::ETHERC0);
	device::port_map::turn(device::peripheral::ETHERC0);

	set_interrupt_task(INT_Excep_ICU_GROUPAL1,
		static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

	ethernet_.start();
	{
		static const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		net::ip_address ipa(192, 168, 0, 20);
		bool dhcp = true;
		if(dhcp) {
			if(ethernet_.begin(mac) == 0) {
				utils::format("Ethernet Fail: begin (DHCP)...\n");
				utils::format("Direct IP: ");
				ethernet_.begin(mac, ipa);
			} else {
				utils::format("Get DHCP: ");
			}
		} else {
			ethernet_.begin(mac, ipa);
			utils::format("Direct IP: ");
		}
		utils::format("%s\n") % ethernet_.get_local_ip().c_str();
	}

	https_.start("Graviton HTTP Server");
	telnets_.start("Graviton TELNET Server");
//	ftps_.start("Graviton FTP Server", "Renesas_RX71M", "GRAVITON", "GRAVITON");

	http_.start();

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		service_putch_tmp_();

		ethernet_.service();

		https_.service(100);
		telnets_.service(100);
//		ftps_.service(100);

		ign_cmd_.service();

//		sdc_.service();

		if(send_all_) {
			if(send_idx_ < 2048) {
				wdm_send_(512);
			} else {
				send_all_ = false;
			}
		}

		if(cmd_.service()) {
			uint8_t cmdn = cmd_.get_words();
			if(cmdn >= 1) {
				char tmp[128];
				tmp[0] = 0;
				if(cmdn >= 2) {
					cmd_.get_word(1, tmp, sizeof(tmp));
				}
				if(cmd_.cmp_word(0, "st")) {  // get status
					auto st = wdmc_.get_status();
					utils::format("WDM st: %04X\n") % st;
				} else if(cmd_.cmp_word(0, "get")) {
					int num = 0;
					if(cmdn >= 2 && (utils::input("%d", tmp) % num).status()) {
						for(int i = 0; i < num; ++i) {
							auto w = wdmc_.get_wave(0);
							utils::format("%d\n") % w;
						}
					}
				} else if(cmd_.cmp_word(0, "ttt")) {
					wdmc_.set_wave_pos(1 + 1, 0);
					auto w = wdmc_.get_wave(1 + 1);
					utils::format("%d\n") % w;

				} else if(cmd_.cmp_word(0, "cap")) {
					wdmc_.set_wave_pos(0, 0);
					for(int i = 0; i < 2048; ++i) {
						wave_buff_[i] = wdmc_.get_wave(1);
					}
					send_idx_ = 0;
				} else if(cmd_.cmp_word(0, "pgw")) {
					int num = 0;
					if(cmdn >= 2 && (utils::input("%d", tmp) % num).status()) {
						wdm_send_(num);
					}					
				} else if(cmd_.cmp_word(0, "mtw")) {
					int num = 0;
					uint16_t d = 0;
					if(cmdn >= 2 && (utils::input("%d", tmp) % num).status()) {
						for(int i = 0; i < 2048; ++i) {
							wave_buff_[i] = d;
							d += num;
						}
						send_idx_ = 0;
					}					
				} else if(cmd_.cmp_word(0, "all")) {
					send_idx_ = 0;
					send_all_ = true;
				} else if(cmd_.cmp_word(0, "crr")) {
					crm_.puts("CRR?1    \n");
				} else if(cmd_.cmp_word(0, "thr")) {
					wdmc_.output(0x080000);
					utils::delay::micro_second(100);
					wdmc_.output(0x08F000);
					wdmc_.output(0x104300);
					wdmc_.output(0x204280);
					ign_cmd_.start_treg();
					utils::format("WDM THR First Trigger Request\n");
				} else if(cmd_.cmp_word(0, "help")) {
					utils::format("WDM command help\n");
					utils::format("  st           read status\n");
					utils::format("  get [num]    get wave data\n");
					utils::format("  cap          capture\n");
					utils::format("  pgw [num]    put wave data\n");
					utils::format("  mtw [dlt]    make test wave data\n");
					utils::format("  all          all capture and send\n");
					utils::format("  crr          CRR\n");
					utils::format("  thr          thrmal registance request\n");
				} else {
					cmd_.get_word(0, tmp, sizeof(tmp));
					utils::format("command error: '%s'\n") % tmp;
				}
			}
		}

		++cnt;
		if(cnt >= 32) {
			cnt = 0;
		}
		LED0::P = (((cnt + 0)  & 31) < 8) ? 1 : 0;
		LED1::P = (((cnt + 8)  & 31) < 8) ? 1 : 0;
		LED2::P = (((cnt + 16) & 31) < 8) ? 1 : 0;
		LED3::P = (((cnt + 24) & 31) < 8) ? 1 : 0;
	}
}
