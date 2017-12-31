//=====================================================================//
/*! @file
    @brief  EFO 2ND (RX64M) メイン @n
			・A/D 入力は、内臓 A/D 変換を使う。@n
			・トリガー入力も内臓 A/D 変換を使う。
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"
#include "common/tpu_io.hpp"
#include "common/fixed_fifo.hpp"

// GR-KAEDE を使う場合有効にする（通常 Makefile で設定）
//#define GR_KAEDE

namespace {

	static const int main_version_ = 10;
	static const uint32_t build_id_ = B_ID;

	enum class CMD : uint8_t {
		START = 0x01,
		END   = 0x03,
		MODE_SELECT = 0x11,
		MODE_SENSE  = 0x12,
		VER   = 0x21,

		ASC_CNVTEST = 'T',
		ASC_CNVTESTS = 't',
	};

	enum class TASK : uint8_t {
		STATE,	// コマンド待ち
		LENGTH,	// 長さ取得
		VOLT,	// トリガー電圧取得
	};

	enum class SEND_TASK : uint8_t {
		READY,
		SINGLE,
		MULTI,
		ASCII,		///< T コマンド（１０２４サンプルテスト）
		ASCII2,		///< t コマンド（１サンプルテスト）
	};

#ifdef GR_KAEDE
	typedef device::PORT<device::PORTC, device::bitpos::B0> LED0;
	typedef device::PORT<device::PORTC, device::bitpos::B1> LED1;
	typedef device::PORT<device::PORT0, device::bitpos::B2> LED2;
	typedef device::PORT<device::PORT0, device::bitpos::B3> LED3;

	typedef utils::fifo<uint8_t, 4096> BUFFER;
	typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;

	SCI		sci_;
#else


#endif

	typedef device::cmt_io<device::CMT0, utils::null_task> CMT;
	CMT		cmt_;

	typedef device::tpu_io<device::TPU0, utils::null_task> TPU;
	TPU		tpu_;

	uint16_t ch0_src_[1024+1];
	uint16_t ch1_src_[1024+1];

	TASK	task_ = TASK::STATE;

	SEND_TASK  	send_task_;



	// 文字列表示、割り込み対応ロック／アンロック機構
	volatile bool putch_lock_ = false;
	utils::fixed_fifo<char, 1024> putch_tmp_;

	void service_putch_tmp_()
	{
///		dis_int();
		while(putch_tmp_.length() > 0) {
			auto ch = putch_tmp_.get();
			sci_.putch(ch);
			// telnet_putch(ch);
		}
///		ena_int();
	}


#if 0
	void capture_request_(uint16_t num)
	{
		if(num > 1024) num = 1024;
		else if(num == 0) return;
		cap_pos_ = 0;
		cap_num_ = num + 1;
	}


	volatile uint16_t cap_count_;
	volatile uint16_t irq_count_;
	uint16_t irq_state_;

	// trigger task
	class irq_task {
	public:
		void operator() ()
		{
			if(cap_count_ > 0) {
				capture_request_(cap_count_);
			}
			++irq_count_;
		}
	};


	void send_wave_(char ch, uint16_t src)
	{
		m_sci_.putch(0x01);  // A/D 通知
		m_sci_.putch(ch);    // chanel NO
		m_sci_.putch(src >> 8);
		m_sci_.putch(src & 0xff);
	}


	void send_wave_(char ch, uint16_t len, const uint16_t* src)
	{
		m_sci_.putch(0x01);  // A/D 通知
		m_sci_.putch(ch);    // chanel NO

		for(uint16_t i = 0; i < len; ++i) {
			m_sci_.putch(src[i] >> 8);
			m_sci_.putch(src[i] & 0xff);
		}
	}

	void setup_irq_(bool positive)
	{
		uint8_t int_level = 2;

		IRQ::edge edge = IRQ::edge::POSITIVE;
		if(!positive) edge = IRQ::edge::NEGATIVE;
		bool ret = irq_.start(int_level, edge, device::port_map::option::SECOND);
		if(!ret) {
			utils::format("IRQ start fail...\n");
			return;
		}
	}
#endif
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
		if(putch_lock_) {
			if((putch_tmp_.size() - putch_tmp_.length()) >= 2) {
				putch_tmp_.put(ch);
			}
			return;
		}
		putch_lock_ = true;
		sci_.putch(ch);
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
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::PORT3::PCR.B5 = 1; // P35(NMI) pull-up

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

#ifdef GR_KAEDE
	// Base Clock 12.0MHz
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

	LED0::DIR = 1;
	LED1::DIR = 1;
	LED2::DIR = 1;
	LED3::DIR = 1;
#else
	// Base Clock 12.5MHz
	// PLLDIV: 1/1, STC: 16 倍(200MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(0) |
							device::SYSTEM::PLLCR.STC.b(0b100011);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/2 (200/4=50)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (200/2=100)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/2 (200.5/4=50)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (200.5/2=100)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (200.5/4=50)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (200.5/4=50)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (200.5/4=50)
	device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.UCK.b(0b0100) | 1;  // USB Clock: 1/5 (200/5=40)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択
#endif

	{
		// タイマー設定（100Hz）
		uint8_t cmt_irq_level = 3;
		cmt_.start(100, cmt_irq_level);
	}

	{  // MAIN SCI 設定
		uint8_t int_level = 1;
		sci_.start(115200, int_level);
		sci_.auto_crlf(false);
	}

#ifdef GR_KAEDE
	utils::format("Start EFO (GR-KAEDE) Version %d.%02d Build: %d\r\n")
		% (main_version_ / 100) % (main_version_ % 100) % B_ID;
#else
	utils::format("Start EFO Version %d.%02d Build: %d\r\n")
		% (main_version_ / 100) % (main_version_ % 100) % B_ID;
#endif

#if 0
	{  // TPU0 設定
		uint8_t int_level = 4;
		if(!tpu0_.start(100000, int_level)) {
			utils::format("TPU0 not start ...\n");
		}
	}

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		switch(task_) {
		case TASK::STATE:
			if(m_sci_.recv_length() >= 1) {
				CMD cmd = static_cast<CMD>(m_sci_.getch());
				if(cmd == CMD::START) {
					task_ = TASK::LENGTH;
				} else if(cmd == CMD::ASC_CNVTEST) {
					capture_request_(1024);
					send_task_ = SEND_TASK::ASCII;
				} else if(cmd == CMD::ASC_CNVTESTS) {
					capture_request_(1);
					send_task_ = SEND_TASK::ASCII2;
				} else if(cmd == CMD::END) {
					if(send_task_ == SEND_TASK::MULTI) {  // 波形取得を強制終了
						send_task_ = SEND_TASK::READY;
					}
				} else if(cmd == CMD::MODE_SELECT) {


				} else if(cmd == CMD::MODE_SENSE) {


				} else if(cmd == CMD::VER) {


				}
			}
			break;

		case TASK::LENGTH:
			if(m_sci_.recv_length() >= 2) {
				length_  = static_cast<uint8_t>(m_sci_.getch());
				length_ <<= 8;
				length_ |= static_cast<uint8_t>(m_sci_.getch());
				task_ = TASK::VOLT;
			}
			break;

		case TASK::VOLT:
			if(m_sci_.recv_length() >= 2) {
				volt_  = static_cast<uint8_t>(m_sci_.getch());
				volt_ <<= 8;
				volt_ |= static_cast<uint8_t>(m_sci_.getch());
				task_ = TASK::STATE;
				dac_.out0(volt_);  // トリガー電圧設定
				bool trg = true;
				if(volt_ < 32768) trg = false;
				cap_count_ = length_;
				 setup_irq_(trg);
				irq_state_ = irq_count_;
				irq_.enable();
				if(length_ == 0) {
					send_task_ = SEND_TASK::SINGLE;
				} else {
					send_task_ = SEND_TASK::MULTI;
				}
			}
			break;

		default:
			break;
		}

		switch(send_task_) {

		case SEND_TASK::SINGLE:
			if(cap_num_ > 0) break;
			eadc_.convert();
			send_wave_(0x01, eadc_.get_value(0));
			send_wave_(0x02, eadc_.get_value(1));
			send_task_ = SEND_TASK::READY;
			break;

		case SEND_TASK::MULTI:
			if(irq_state_ == irq_count_) break;
			if(cap_num_ > 0) break;
			send_wave_(0x01, length_, ch0_src_ + 1);
			send_wave_(0x02, length_, ch1_src_ + 1);
			send_task_ = SEND_TASK::READY;
			break;

		case SEND_TASK::ASCII:
			if(cap_num_ > 0) break;
			for(uint16_t i = 1; i <= 1024; ++i) {
				char tmp[128];
				utils::sformat("%d,%d,%d\r\n", tmp, sizeof(tmp)) % i % ch0_src_[i] % ch1_src_[i];
				m_sci_.puts(tmp);
			}
			send_task_ = SEND_TASK::READY;
			break;
		case SEND_TASK::ASCII2:
			if(cap_num_ > 0) break;
			{
				char tmp[128];
				utils::sformat("%d,%d\r\n", tmp, sizeof(tmp)) % ch0_src_[1] % ch1_src_[1];
				m_sci_.puts(tmp);
			}
			send_task_ = SEND_TASK::READY;
			break;


		default:
			break;
		}

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt >= 35) {
			LED::P = 1;
		} else {
			LED::P = 0;
		}
#endif

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();



		++cnt;
		if(cnt >= 40) {
			cnt = 0;
		}
		auto sel = cnt / 10;
		static const uint8_t ledtbl[4] = {
			0b0001, 0b0010, 0b0100, 0b1000
		}; 
		LED0::P = (ledtbl[sel]     ) & 1;
		LED1::P = (ledtbl[sel] >> 1) & 1;
		LED2::P = (ledtbl[sel] >> 2) & 1;
		LED3::P = (ledtbl[sel] >> 3) & 1;
	}
}

