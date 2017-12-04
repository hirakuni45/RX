//=====================================================================//
/*! @file
    @brief  GR-KAEDE EFO (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace {

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
#if 0
		if(putch_lock_) {
			if((putch_tmp_.size() - putch_tmp_.length()) >= 2) {
				putch_tmp_.put(ch);
			}
			return;
		}
		putch_lock_ = true;
		core_.sci_.putch(ch);
		putch_lock_ = false;
#endif
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列出力
		@param[in]	s	文字列
	*/
	//-----------------------------------------------------------------//
	void sci_puts(const char* s)
	{
//		core_.sci_.puts(s);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字入力
		@return	文字
	*/
	//-----------------------------------------------------------------//
	char sci_getch(void)
	{
//		return core_.sci_.getch();
		return 0;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列長の取得
		@return	文字列長
	*/
	//-----------------------------------------------------------------//
	uint16_t sci_length(void)
	{
//		return core_.sci_.recv_length();
		return 0;
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
#if 0
	using namespace seeda;

	device::PORTC::PDR.B0 = 1; // output
	device::PORTC::PDR.B1 = 1; // output
	device::PORT0::PDR.B2 = 1; // output
	device::PORT0::PDR.B3 = 1; // output

	device::PORT3::PCR.B5 = 1; // P35(NMI) pull-up

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12MHz
	device::SYSTEM::PLLCR.STC = 0b010011;		// PLL 10 倍(120MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
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

	nets_.init();
	nets_.title();

	enable_eadc_server();

	uint32_t cnt = 0;
	while(1) {
		core_.sync();

		sample_data_.time_ = get_time();

		core_.service();
		tools_.service();

		sdc_.service();

		service_putch_tmp_();

		nets_.service();

		++cnt;
		if(cnt >= 32) {
			cnt = 0;
		}

		device::PORTC::PODR.B0 = (((cnt + 0)  & 31) < 8) ? 1 : 0;
		device::PORTC::PODR.B1 = (((cnt + 8)  & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B2 = (((cnt + 16) & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B3 = (((cnt + 24) & 31) < 8) ? 1 : 0;
	}
#endif
}
