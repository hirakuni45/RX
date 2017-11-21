//=====================================================================//
/*! @file
    @brief  GR-KAEDE(RX64M) http_server サンプル @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/rspi_io.hpp"
#include "common/sdc_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/time.h"

#include "r_net/ethernet.hpp"
#include "r_net/http_server.hpp"

extern "C" {
	void INT_Excep_ICU_GROUPAL1(void);
}

namespace {

	class cmt_task {
		void (*task_10ms_)();

		volatile unsigned long millis_;
		volatile unsigned long delay_;
		volatile uint32_t millis10x_;
		volatile uint32_t cmtdiv_;

	public:
		cmt_task() : task_10ms_(nullptr),
			millis_(0), delay_(0), millis10x_(0), cmtdiv_(0) { }

		void operator() () {

			++millis_;
			++cmtdiv_;
			if(cmtdiv_ >= 10) {
				if(task_10ms_ != nullptr) (*task_10ms_)();
				cmtdiv_ = 0;
				++millis10x_;
			}
			if(delay_) {
				--delay_;
			}
			
		}

		void set_task_10ms(void (*task)(void)) {
			task_10ms_ = task;
		}

		void sync_100hz()
		{
			volatile uint32_t tmp = millis10x_;
			while(tmp == millis10x_) ;
		}

		volatile unsigned long get_millis() const { return millis_; }

		volatile unsigned long get_delay() const { return delay_; }

		void set_delay(volatile unsigned long n) { delay_ = n; }
	};

	typedef device::cmt_io<device::CMT0, cmt_task> CMT0;
	CMT0	cmt0_;

	typedef utils::fifo<uint8_t, 2048> BUFFER;
	typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;

	SCI		sci_;


	// SDC 用　SPI 定義（RSPI）
	typedef device::rspi_io<device::RSPI> SPI;
	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< カード検出

	SPI		spi_;

	typedef utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;
	SDC		sdc_(spi_, 20000000);

	typedef utils::rtc_io RTC;
	RTC		rtc_;

	net::ethernet		ethernet_;

	typedef net::http_server<SDC, 16, 8192> HTTP_SERVER;
	HTTP_SERVER			http_(ethernet_, sdc_);

	typedef HTTP_SERVER::http_format format;	


	uint32_t loop_ = 0;


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の設定
		@param[in]	t	GMT 時間
	*/
	//-----------------------------------------------------------------//
	void set_time(time_t t)
	{
		if(!rtc_.set_time(t)) {
			utils::format("Stall RTC write...\n");
		}
	}


	static void dir_list_func_(const char* name, const FILINFO* fi, bool dir, void* option)
	{
		if(fi == nullptr) return;

//		++loop_;
//		if(loop_ >= 50) return;

		char cdir = '-';
		if(dir) {
			cdir = 'd';
		}
		int block = fi->fsize / 512;
		if(block == 0 && fi->fsize > 0) ++block;

		time_t t = utils::str::fatfs_time_to(fi->fdate, fi->ftime);
		struct tm *m = localtime(&t);
		format("%crw-rw-rw- %d user root %d %s %d %02d:%02d %s<br>\n")
			% cdir % block % fi->fsize
			% get_mon(m->tm_mon)
			% static_cast<int>(m->tm_mday)
			% static_cast<int>(m->tm_hour)
			% static_cast<int>(m->tm_min)
			% name;
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
		sci_.putch(ch);
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
		return cmt0_.at_task().get_millis();
	}


	void delay(unsigned long ms)
	{
		cmt0_.at_task().set_delay(ms);
		while(cmt0_.at_task().get_delay() != 0) ;		
	}


	void set_task_10ms(void (*task)(void)) {
		cmt0_.at_task().set_task_10ms(task);
	}

}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::PORT3::PCR.B5 = 1; // P35(NMI) pull-up

	// GR-KAEDE の SPI 端子のハードバグ回避
	// ※PC3 から、PC7 へ １K オームで接続
	device::PORTC::PDR.B3 = 1; // output
	device::PORTC::PODR.B3 = 1;

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12MHz
	// PLLDIV: 1/1, STC: 16 倍(198MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(0) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/2 (198/4=48)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (198/2=96)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/2 (198/4=48)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (198/2=96)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (198/4=48)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (198/4=48)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (198/4=48)
	device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.UCK.b(0b0011) | 1;  // USB Clock: 1/4 (198/4=48)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{  // タイマー設定、１０００Ｈｚ（１ｍｓ）
		uint8_t int_level = 1;
		cmt0_.start(1000, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	{
		utils::format("\nStart GR-KAEDE http sample\n");
		uint8_t mde = device::SYSTEM::MDE.MDE();
		utils::format("Endian: %3b (%s)") % static_cast<uint32_t>(mde) % (mde == 0b111 ? "Little" : "Big");
		utils::format(", PCLKA: %u [Hz]") % static_cast<uint32_t>(F_PCLKA);
		utils::format(", PCLKB: %u [Hz]\n") % static_cast<uint32_t>(F_PCLKB);
	}

	// SD カード・クラスの初期化
	sdc_.start();

	device::power_cfg::turn(device::peripheral::ETHERC0);
	device::port_map::turn(device::peripheral::ETHERC0);

	set_interrupt_task(INT_Excep_ICU_GROUPAL1, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

	ethernet_.start();
	{
		static const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		net::ip_address ipa(192, 168, 3, 20);  // 固定アドレス
		bool dhcp = true;
		if(dhcp) {
			if(ethernet_.begin(mac) == 0) {
				utils::format("Ethernet Fail: begin (DHCP)...\n");
				utils::format("SetIP (DHCP fail): ");
				ethernet_.begin(mac, ipa);
			} else {
				utils::format("SetIP  DHCP): ");
			}
		} else {
			ethernet_.begin(mac, ipa);
			utils::format("SetIP (Direct): ");
		}
		utils::format("%s\n") % ethernet_.get_local_ip().c_str();
	}

	http_.start("GR-KAEDE HTTP Server");

	http_.set_link("/", "", [=](void) {
		time_t t = get_time();
		struct tm *m = localtime(&t);
		format("%s %s %d %02d:%02d:%02d  %4d<br>\n")
			% get_wday(m->tm_wday)
			% get_mon(m->tm_mon)
			% static_cast<uint32_t>(m->tm_mday)
			% static_cast<uint32_t>(m->tm_hour)
			% static_cast<uint32_t>(m->tm_min)
			% static_cast<uint32_t>(m->tm_sec)
			% static_cast<uint32_t>(m->tm_year + 1900);

		http_.tag_hr(500, 3);

		loop_ = 0;
//		sdc_.dir_loop("", dir_list_func_, true, nullptr);
	} );

	uint32_t cnt = 0;
	while(1) {
		cmt0_.at_task().sync_100hz();

		ethernet_.service();

		http_.service(100);

		sdc_.service();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}

		device::PORTC::PDR.B0 = 1; // output
		device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
