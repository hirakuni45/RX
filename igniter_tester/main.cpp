//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・テスター・コントローラー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "main.hpp"
#include "http.hpp"
#include "ign_server.hpp"
#include "ign_cmd.hpp"

namespace {

	static const int version_ = 50;
	static const uint32_t build_id_ = B_ID;

	class cmt_task
	{
		void (*task_10ms_)();

//		volatile unsigned long delay_;
		volatile uint32_t millis10x_;

	public:
		cmt_task() : task_10ms_(nullptr),
//			delay_(0),
			millis10x_(0) { }

		void operator() () {

			if(task_10ms_ != nullptr) (*task_10ms_)();
			++millis10x_;

//			if(delay_) {
//				--delay_;
//			}
			
		}

		void set_task_10ms(void (*task)(void)) {
			task_10ms_ = task;
		}

		volatile unsigned long get_millis() const { return millis10x_ * 10; }

//		volatile unsigned long get_delay() const { return delay_; }
//		void set_delay(volatile unsigned long n) { delay_ = n; }
	};

	typedef device::cmt_io<device::CMT0, cmt_task> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 128> BUFFER;
#ifdef KAEDE
	typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;
#else
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
#endif
	SCI		sci_;

	typedef utils::rtc_io RTC;
	RTC		rtc_;

	SPI		spi_;

	SDC		sdc_(spi_, 20000000);

	net::ethernet	ethernet_;

	HTTP_SERVER		https_(ethernet_, sdc_);

	FTP_SERVER		ftps_(ethernet_, sdc_);

	TELNETS			telnets_(ethernet_);

	utils::ign_cmd<TELNETS>	ign_cmd_(telnets_);

	// 文字列表示、割り込み対応ロック／アンロック機構
	volatile bool putch_lock_ = false;
	utils::fixed_fifo<char, 1024> putch_tmp_;

	void service_putch_tmp_()
	{
		dis_int();
		while(putch_tmp_.length() > 0) {
			auto ch = putch_tmp_.get();
			sci_.putch(ch);
			telnets_.putch(ch);
		}
		ena_int();
	}

	utils::command<256> cmd_;

	http<HTTP_SERVER>	http_(https_);


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
		telnets_.putch(ch);
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
		return sdc_.at_mmc().disk_initialize(drv);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へステータスを提供
		@param[in]	drv		Physical drive nmuber (0)
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_status(BYTE drv) {
		return sdc_.at_mmc().disk_status(drv);
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
		return sdc_.at_mmc().disk_read(drv, buff, sector, count);
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
		return sdc_.at_mmc().disk_write(drv, buff, sector, count);
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
		return sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
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


#if 0
	void delay(unsigned long ms)
	{
		cmt_.at_task().set_delay(ms);
		while(cmt_.at_task().get_delay() != 0) ;		
	}
#endif

	void set_task_10ms(void (*task)(void)) {
		cmt_.at_task().set_task_10ms(task);
	}


	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
#ifdef KAEDE
	device::PORT3::PCR.B5 = 1; // P35(NMI) pull-up

	// GR-KAEDE の SPI 端子のハードバグ回避
	// ※PC3 から、PC7 へ １K オームで接続
	device::PORTC::PDR.B3 = 1; // output
	device::PORTC::PODR.B3 = 1;
#endif

	device::system_io<12000000>::setup_system_clock();

	{  // タイマー設定１００Ｈｚ（１０ｍｓ）
		uint8_t int_level = 4;
		cmt_.start(100, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	{  // RTC 開始
		rtc_.start();
	}

#ifdef KAEDE
	device::PORTC::PDR.B0 = 1;
	device::PORTC::PDR.B1 = 1;
	device::PORT0::PDR.B2 = 1;
	device::PORT0::PDR.B3 = 1;
	utils::format("\nRX64M Igniter tester (for GR-KAEDE)");
#else
	utils::format("\nRX71M Igniter tester");
#endif
	{
		utils::format(" Start Build: %u Version %d.%02d\n") % build_id_
			% (version_ / 100) % (version_ % 100);

		uint8_t mde = device::SYSTEM::MDE.MDE();
		utils::format("Endian: %3b (%s)") % static_cast<uint32_t>(mde) % (mde == 0b111 ? "Little" : "Big");
		utils::format(", PCLKA: %u [Hz]") % static_cast<uint32_t>(F_PCLKA);
		utils::format(", PCLKB: %u [Hz]\n") % static_cast<uint32_t>(F_PCLKB);
	}

	// SD カード・クラスの初期化
	sdc_.start();

	device::power_mgr::turn(device::peripheral::ETHERC0);
	device::port_map::turn(device::peripheral::ETHERC0);

	set_interrupt_task(INT_Excep_ICU_GROUPAL1, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

	ethernet_.start();

	{
		static const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		net::ip_address ipa(192, 168, 3, 20);
		bool dhcp = true;
		if(dhcp) {
			if(ethernet_.begin(mac) == 0) {
				utils::format("Ethernet Fail: begin (DHCP)...\n");
				utils::format("SetIP: ");
				ethernet_.begin(mac, ipa);
			} else {
				utils::format("DHCP: ");
			}
		} else {
			ethernet_.begin(mac, ipa);
			utils::format("SetIP: ");
		}
		utils::format("%s\n") % ethernet_.get_local_ip().c_str();
	}

	http_.start();

	ftps_.start("GR-KAEDE", "Renesas_RX64M", "KAEDE", "KAEDE");

	telnets_.start("SEEDA03");

	cmd_.set_prompt("# ");

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		ethernet_.service();

		https_.service(100);
		ftps_.service(100);
		telnets_.service(100);

		ign_cmd_.service();

		sdc_.service();

		if(cmd_.service()) {
			uint8_t cmdn = cmd_.get_words();
			if(cmdn >= 1) {
				bool f = false;
				if(cmd_.cmp_word(0, "dir")) {  // dir [xxx]
					if(check_mount_()) {
						if(cmdn >= 2) {
							char tmp[128];
							cmd_.get_word(1, tmp, sizeof(tmp));
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
							cmd_.get_word(1, tmp, sizeof(tmp));
							sdc_.cd(tmp);						
						} else {
							sdc_.cd("/");
						}
					}
					f = true;
				} else if(cmd_.cmp_word(0, "pwd")) { // pwd
					utils::format("%s\n") % sdc_.get_current();
					f = true;
				} else if(cmd_.cmp_word(0, "help")) {
					utils::format("    dir [path]\n");
					utils::format("    cd [path]\n");
					utils::format("    pwd\n");
					f = true;
				}
				if(!f) {
					char tmp[128];
					if(cmd_.get_word(0, tmp, sizeof(tmp))) {
						utils::format("Command error: '%s'\n") % tmp;
					}
				}
			}
		}

#ifdef KAEDE
		++cnt;
		if(cnt >= 32) {
			cnt = 0;
		}

		device::PORTC::PODR.B0 = (((cnt + 0)  & 31) < 8) ? 1 : 0;
		device::PORTC::PODR.B1 = (((cnt + 8)  & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B2 = (((cnt + 16) & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B3 = (((cnt + 24) & 31) < 8) ? 1 : 0;
#endif
	}
}
