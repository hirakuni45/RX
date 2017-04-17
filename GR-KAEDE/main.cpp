//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"
#include "core.hpp"
#include "tools.hpp"
#include "../rx64m_test/net.hpp"

namespace {

	seeda::core 	core_;
	seeda::tools	tools_;
	seeda::net		net_;

	seeda::SPI		spi_;
	seeda::SDC		sdc_(spi_, 20000000);

	typedef utils::rtc_io RTC;
	RTC		rtc_;

#ifdef SEEDA
	seeda::EADC		eadc_;
#endif

	uint32_t		sample_count_;
	seeda::sample	sample_[8];
	seeda::sample_t	sample_t_[8];

///	bool	config_;

	void main_init_()
	{
		// RTC 設定
		rtc_.start();

#ifdef SEEDA
		{  // LTC2348ILX-16 初期化
			// 内臓リファレンスと内臓バッファ
			// VREFIN: 2.024V、VREFBUF: 4.096V、Analog range: 0V to 5.12V
			if(!eadc_.start(2000000, seeda::EADC::span_type::P5_12)) {
				utils::format("LTC2348_16 not found...\n");
			}
		}
#endif
	}
}

namespace seeda {

	//-----------------------------------------------------------------//
	/*!
		@brief  SDC_IO クラスへの参照
		@return SDC_IO クラス
	*/
	//-----------------------------------------------------------------//
	SDC& at_sdc() { return sdc_; }


#ifdef SEEDA
	//-----------------------------------------------------------------//
	/*!
		@brief  EADC クラスへの参照
		@return EADC クラス
	*/
	//-----------------------------------------------------------------//
	EADC& at_eadc() { return eadc_; }
#endif

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
		@brief  時間の表示
		@param[in]	t		時間
		@param[in]	dst		出力文字列
		@param[in]	size	文字列の大きさ
	*/
	//-----------------------------------------------------------------//
	void disp_time(time_t t, char* dst, uint32_t size)
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

#ifdef SEEDA
	//-----------------------------------------------------------------//
	/*!
		@brief  EADC サーバー
	*/
	//-----------------------------------------------------------------//
	void eadc_server()
	{
		eadc_.convert();
		for(int i = 0; i < 8; ++i) {
			sample_[i].add(eadc_.get_value(i));
		}
		++sample_count_;
		if(sample_count_ >= 1000) {
			for(int i = 0; i < 8; ++i) {
				sample_[i].collect();
				sample_t_[i] = sample_[i].get();
				sample_[i].clear();
			}
			sample_count_ = 0;
		}
	}
#endif

	//-----------------------------------------------------------------//
	/*!
		@brief  A/D サンプルの取得
		@param[in]	ch	チャネル（０～７）
		@return A/D サンプル
	*/
	//-----------------------------------------------------------------//
	const sample_t& get_sample(uint8_t ch)
	{
		return sample_t_[ch];
	}
}

extern "C" {

	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字出力
		@param[in]	ch	文字
	*/
	//-----------------------------------------------------------------//
	void sci_putch(char ch)
	{
		core_.sci_.putch(ch);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列出力
		@param[in]	s	文字列
	*/
	//-----------------------------------------------------------------//
	void sci_puts(const char* s)
	{
		core_.sci_.puts(s);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字入力
		@return	文字
	*/
	//-----------------------------------------------------------------//
	char sci_getch(void)
	{
		return core_.sci_.getch();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列長の取得
		@return	文字列長
	*/
	//-----------------------------------------------------------------//
	uint16_t sci_length(void)
	{
		return core_.sci_.recv_length();
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
		auto t = seeda::get_time();
		return utils::str::get_fattime(t);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-8 から ShiftJIS への変換
		@param[in]	src	UTF-8 文字列ソース
		@param[out]	dst	ShiftJIS 文字列出力
	 */
	//-----------------------------------------------------------------//
	void utf8_to_sjis(const char* src, char* dst) {
		utils::str::utf8_to_sjis(src, dst);
	}


	unsigned long millis(void)
	{
		return core_.cmt0_.at_task().get_millis();
	}


	void delay(unsigned long ms)
	{
		core_.cmt0_.at_task().set_delay(ms);
		while(core_.cmt0_.at_task().get_delay() != 0) ;		
	}


	void set_task_10ms(void (*task)(void)) {
		core_.cmt0_.at_task().set_task_10ms(task);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	using namespace seeda;

	device::PORT3::PCR.B5 = 1; // P35(NMI) pull-up

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12.5MHz
	// PLLDIV: 1/1, STC: 16 倍(200MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(0) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/2 (200/4=50)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (200/2=100)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/2 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (200/2=100)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (200/4=50)
	device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.UCK.b(0b0011) | 1;  // USB Clock: 1/4 (200/4=50)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	main_init_();

	sample_count_ = 0;

	core_.init();

	// SD カード・クラスの初期化
	sdc_.start();

	// 設定ファイルの確認
///	config_ = sdc_.probe("seeda.cfg");
	core_.title();

	tools_.init();
	tools_.title();

	net_.init();
	net_.title();

	uint32_t cnt = 0;
	while(1) {
		core_.sync();

		core_.service();
		tools_.service();

		sdc_.service();

		net_.service();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
///		if(config_) {
#ifdef SEEDA
			device::PORTA::PDR.B0 = 1; // output
			device::PORTA::PODR.B0 = (cnt < 10) ? 0 : 1;
#else
			device::PORTC::PDR.B0 = 1; // output
			device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
#endif
///		}
	}
}
