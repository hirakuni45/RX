#pragma once
//=====================================================================//
/*!	@file
	@brief	メイン・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"
#include "common/iica_io.hpp"
#include "common/rspi_io.hpp"
#include "common/sdc_io.hpp"
#include "chip/ST7565.hpp"
#include "graphics/monograph.hpp"
#include "graphics/font6x12.hpp"
#include "graphics/menu.hpp"

#include "common/format.hpp"
#include "common/command.hpp"

#include "common/adc_io.hpp"
#include "common/bitset.hpp"
#include "common/switch_man.hpp"

#include "common/nmea_dec.hpp"

#include "scene_id.hpp"
#include "resource.hpp"
#include "datalogger.hpp"

extern "C" {
	void string_reset(void);
	void string_chaout(char ch);
	void laptimer_service(uint8_t pitflag);
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
/*!
	@brief	リソース・クラス
	@param[in]	GR		描画クラス
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
struct core_t {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	１００Ｈｚタイマー割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class cmt_task {
		uint8_t	cnt_;
		volatile uint8_t sync3_;
	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		cmt_task() : cnt_(0), sync3_(0) { }


		//-------------------------------------------------------------//
		/*!
			@brief	100Hz タイマー・タスク
		*/
		//-------------------------------------------------------------//
		void operator() () {

			laptimer_service(0);

			++cnt_;
			if(cnt_ >= 3) {
				cnt_ = 0;
				++sync3_;
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief	33.33... Hz 同期
		*/
		//-------------------------------------------------------------//
		void sync3() const {
			volatile uint8_t n = sync3_;
			while(n == sync3_) ;
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 256> fifo256;
	device::sci_io<device::SCI1, fifo256, fifo256> sci1_;

	typedef utils::fifo<uint16_t, 512> fifo512;
	typedef device::sci_io<device::SCI5, fifo512, fifo256> SCI5;
	SCI5	sci5_;

	utils::nmea_dec<SCI5> nmea_;


	typedef device::iica_io<device::RIIC0> I2C;
	I2C 	i2c_;

	// SPI 定義（RSPI0）
	typedef device::rspi_io<device::RSPI0> SPI;
	SPI 	spi_;

	typedef device::PORT<device::PORT6, device::bitpos::B5> SDC_SELECT;	///< カード選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORT6, device::bitpos::B3> SDC_DETECT;	///< カード検出

	utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> sdc_;

	typedef device::PORT<device::PORT6, device::bitpos::B1> LCD_SEL;	///< LCD 選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B2> LCD_A0;	    ///< LCD レジスター選択

	chip::ST7565<SPI, LCD_SEL, LCD_A0> lcd_;

	// モノクロ・グラフィックス
	graphics::kfont_null kfont_;
	typedef graphics::font6x12 AFONT;
	typedef graphics::monograph<128, 64, AFONT> BITMAP;
	BITMAP bitmap_;

	app::resource<BITMAP> resource_;

	typedef graphics::menu<BITMAP, 5> MENU;
	MENU menu_;

	class adc_task {
		uint32_t adc_cnt_;
	public:
		void operator() () {
			++adc_cnt_;
		}
	};

	typedef device::S12AD ADC;
	typedef device::adc_io<ADC, adc_task> ADC_IO;
	ADC_IO adc_io_;

	enum class SWITCH : uint8_t {
		RIGHT,
		UP,
		DOWN,
		LEFT,
		PIT,
		CANCEL
	};

	typedef utils::bitset<uint32_t, SWITCH> switch_bits;
	utils::switch_man<switch_bits> switch_man_;

	int16_t		menu_run_;

	utils::command<128> command_;

	uint16_t	loop_count_;

	bool		fbc_enable_;

	app::datalogger	datalogger_;

	//-----------------------------------------------------------------//
	/*!
		@brief	コンストラクター
	*/
	//-----------------------------------------------------------------//
	core_t() :
			   nmea_(sci5_),
			   sdc_(spi_, 15000000),
			   lcd_(spi_),
			   bitmap_(kfont_),
			   resource_(bitmap_),
			   menu_(bitmap_),
			   menu_run_(-1)
	{ }


	//-----------------------------------------------------------------//
	/*!
		@brief	クロックなどシステム関係初期化
	*/
	//-----------------------------------------------------------------//
	void init()
	{
		device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

		device::SYSTEM::MEMWAIT = 0b10; // 80MHz 動作 wait 設定

		while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");
		device::SYSTEM::OPCCR = 0;  // 高速モード選択
		while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");

		// clock osc 10MHz
		device::SYSTEM::MOSCWTCR = 9;	// 4ms wait
		// メインクロック・ドライブ能力設定、内部発信
		device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(1);
		device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
		while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

		device::SYSTEM::PLLCR.STC = 0b001111;		// PLL input: 1, PLL 8 倍(80MHz)
		device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
		while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

		device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/4 (80/4=20)
							  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (80/1=80)
							  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (80/1=80)
							  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (80/2=40)
							  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
		device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	デバイス関係初期化
	*/
	//-----------------------------------------------------------------//
	void init_device()
	{
		{  // タイマー設定（１００Ｈｚ）
			uint8_t intr_level = 4;
			cmt_.start(100, intr_level);
		}

		{  // SCI1 設定
			uint8_t intr_level = 2;
			sci1_.start(115200, intr_level);
		}

		{  // SCI5 設定 (GPS)
			uint8_t intr_level = 2;
			sci5_.start(9600, intr_level);
		}

		{  // IICA(I2C) の開始
			uint8_t intr_level = 0;
			if(!i2c_.start(I2C::speed::fast, intr_level)) {
				utils::format("IICA start error (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
			}
		}

		{  // SD カード・クラスの初期化
			sdc_.start();
		}


		{  // NMEA 開始
			nmea_.start();
		}

		{  // LCD 開始
			spi_.start(8000000, SPI::PHASE::TYPE4, SPI::DLEN::W8);  // LCD 用設定、速度
			bool comrvs = true;
			lcd_.start(0x10, comrvs);
			bitmap_.clear(0);
		}

		{  // A/D 設定
			uint8_t intr_level = 1;
			if(!adc_io_.start(ADC::analog::AIN000, intr_level)) {
				utils::format("A/D start fail AIN000\n");
			}
			if(!adc_io_.start(ADC::analog::AIN001, intr_level)) {
				utils::format("A/D start fail AIN001\n");
			}
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	時間を取得 @n
				※ G.P.S. が無い場合、RTC から取得
		@return 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time() const
	{
		auto t = nmea_.get_gmtime();
		return t;
	}


	//-----------------------------------------------------------------//
	/*!
		@breif	日付表示 YYYY/MM/DD を行う
		@param[in]	x	開始点Ｘ軸を指定
		@param[in]	y	開始点Ｙ軸を指定
		@param[in]	t	tm 構造体のポインター
	*/
	//-----------------------------------------------------------------//
	void draw_date(int16_t x, int16_t y, const struct tm *t)
	{
		char tmp[128];
		utils::sformat("%04u/%02u/%02u", tmp, sizeof(tmp)) % static_cast<uint32_t>(t->tm_year + 1900)
			% static_cast<uint32_t>(t->tm_mon + 1) % static_cast<uint32_t>(t->tm_mday);
 		bitmap_.draw_text(x, y, tmp);
	}


	//-----------------------------------------------------------------//
	/*!
		@breif	時間表示 HH/MM/SS を行う
		@param[in]	x	開始点Ｘ軸を指定
		@param[in]	y	開始点Ｙ軸を指定
		@param[in]	t	tm 構造体のポインター
	*/
	//-----------------------------------------------------------------//
	void draw_time(short x, short y, const struct tm* t)
	{
		char tmp[128];
		utils::sformat("%02u:%02u.%02u", tmp, sizeof(tmp)) % static_cast<uint32_t>(t->tm_hour)
			% static_cast<uint32_t>(t->tm_min) % static_cast<uint32_t>(t->tm_sec);
		bitmap_.draw_text(x, y, tmp);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	時間表示
		@param[in]	t	時間
	*/
	//-----------------------------------------------------------------//
	void disp_time(time_t t)
	{
		struct tm *m = localtime(&t);
		utils::format("%s %s %d %02d:%02d:%02d  %4d\n")
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
		@brief	数字入力
	*/
	//-----------------------------------------------------------------//
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


	//-----------------------------------------------------------------//
	/*!
		@brief	マウント検査
		@return マウント済みなら「true」
	*/
	//-----------------------------------------------------------------//
	bool check_mount()
	{
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	コマンド・サービス
	*/
	//-----------------------------------------------------------------//
	void command_service()
	{
		// コマンド入力と、コマンド解析
		if(command_.service()) {
			auto cmdn = command_.get_words();
			if(cmdn >= 1) {
				bool f = false;
				if(command_.cmp_word(0, "dir")) {  // dir [xxx]
					if(check_mount()) {
						if(cmdn >= 2) {
							char tmp[128];
							command_.get_word(1, sizeof(tmp), tmp);
							sdc_.dir(tmp);
						} else {
							sdc_.dir("");
						}
					}
					f = true;
				} else if(command_.cmp_word(0, "cd")) {  // cd [xxx]
					if(check_mount()) {
						if(cmdn >= 2) {
							char tmp[128];
							command_.get_word(1, sizeof(tmp), tmp);
							sdc_.cd(tmp);						
						} else {
							sdc_.cd("/");
						}
					}
					f = true;
				} else if(command_.cmp_word(0, "pwd")) { // pwd
					utils::format("%s\n") % sdc_.get_current();
					f = true;
				} else if(command_.cmp_word(0, "next")) {
					menu_.focus_next();
					f = true;
				} else if(command_.cmp_word(0, "prev")) {
					menu_.focus_prev();
					f = true;
				} else if(command_.cmp_word(0, "help")) { // help
					utils::format("dir [name]\n");
					utils::format("cd [directory-name]\n");
					utils::format("pwd\n");
					f = true;
				}

				if(!f) {
					char tmp[128];
					command_.get_word(0, sizeof(tmp), tmp);
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	メニュー選択サービス
	*/
	//-----------------------------------------------------------------//
	void menu_item_service()
	{
		if(switch_man_.get_positive().get(SWITCH::UP)) {
			menu_.focus_prev();
		}
		if(switch_man_.get_positive().get(SWITCH::DOWN)) {
			menu_.focus_next();
		}
		if(switch_man_.get_negative().get(SWITCH::RIGHT)) {
			menu_run_ = menu_.get_pos();
		}
	}

};


//---------------------------------------------------------------------//
/*!
	@brief	コアの参照
	@return コア
*/
//---------------------------------------------------------------------//
core_t& at_core();


//---------------------------------------------------------------------//
/*!
	@brief	シーンを選択
	@param[in]	id	シーンＩＤ
*/
//---------------------------------------------------------------------//
void select_scene(app::scene_id id);
