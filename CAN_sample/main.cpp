//=====================================================================//
/*! @file
    @brief  CAN サンプル @n
			RX64M, RX71M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
			RX65N (Renesas Envision kit RX65N): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
			RX24T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する @n
			RX66T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

#include "common/can_io.hpp"

#include "common/command.hpp"

namespace {

#if defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M" };
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const auto CAN0_PORT = device::port_map::option::FIRST;
	static const auto CAN1_PORT = device::port_map::option::FIRST;
	#define LOOP
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M" };
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const auto CAN0_PORT = device::port_map::option::FIRST;
	static const auto CAN1_PORT = device::port_map::option::FIRST;
	#define LOOP
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N" };
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T" };
	typedef device::system_io<10000000, 160000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const auto CAN0_PORT = device::port_map::option::FIRST;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N" };
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;
	static const auto CAN0_PORT = device::port_map::option::SECOND;
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	// CAN 関連定義
	typedef device::can_io_def CAN;

	volatile uint32_t send_tic_;
	volatile uint32_t recv_tic_;

	class rx_task {
	public:
		void operator () (device::peripheral per, uint32_t mbi)
		{
		}
	};

	class tx_task {
	public:
		void operator () (device::peripheral per, uint32_t mbi)
		{
		}
	};

	typedef device::can_io<device::CAN0, CAN0_PORT, rx_task, tx_task> CAN0;
	CAN0	can0_;

#ifdef LOOP
	typedef device::can_io<device::CAN1, CAN1_PORT, rx_task, tx_task> CAN1;
	CAN1	can1_;

	uint32_t	cur_ch_;
#endif

	uint32_t	cur_id_;
	bool		ext_id_;

	typedef utils::command<256> CMD;
	CMD		cmd_;

	void reset_(uint32_t idx)
	{
#ifdef LOOP
		if(cur_ch_ == 0) {
			can0_.reset_box(idx);
		} else if(cur_ch_ == 1) {
			can1_.reset_box(idx);
		}
#else
		can0_.reset_box(idx);
#endif
	}


	void recv_(uint32_t idx)
	{
#ifdef LOOP
		if(cur_ch_ == 0) {
			can0_.recv_box(idx);
		} else if(cur_ch_ == 1) {
			can1_.recv_box(idx);
		}
#else
		can0_.recv_box(idx);
#endif
	}


	void send_(uint32_t idx)
	{
#ifdef LOOP
		if(cur_ch_ == 0) {
			can0_.send_box(idx);
		} else if(cur_ch_ == 1) {
			can1_.send_box(idx);
		}
#else
		can0_.send_box(idx);
#endif
	}


	void stat_(uint32_t idx)
	{
		uint8_t ret = 0;
#ifdef LOOP
		if(cur_ch_ == 0) {
			ret = can0_.stat_box(idx);
		} else if(cur_ch_ == 1) {
			ret = can1_.stat_box(idx);
		}
#else
		ret = can0_.stat_box(idx);
#endif
		utils::format("MCTL: 0x%02X (0b%08b)\n")
			% static_cast<uint16_t>(ret) % static_cast<uint16_t>(ret);
	}


	void legacy_command_()
	{
		if(!cmd_.service()) {
			return;
		}

		auto cmdn = cmd_.get_words();

		bool error = false;
		if(cmdn == 0) {

		} else if(cmd_.cmp_word(0, "id")) { // set current ID
			if(cmdn >= 2) {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				if(!(utils::input("%a", tmp) % cur_id_).status()) {
					error = true;
				} else {
					if(cur_id_ >= 0x800) {
						ext_id_ = true;
					}
				}
			} else {
				utils::format("ID: 0x%X (%d)\n") % cur_id_ % cur_id_;
			}
#ifdef LOOP
		} else if(cmd_.cmp_word(0, "ch")) { // set current channel
			if(cmdn >= 2) {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				if(!(utils::input("%a", tmp) % cur_ch_).status()) {
					error = true;
				}
			} else {
				utils::format("Current device CAN%d\n") % cur_ch_;
			}
#endif			
		} else if(cmd_.cmp_word(0, "ext")) { // ext-id mode
			ext_id_ = true;
		} else if(cmd_.cmp_word(0, "std")) { // std-id mode
			ext_id_ = false;
		} else if(cmd_.cmp_word(0, "reset")) { // reset MB
			if(cmdn == 2) {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				int idx = 0;
				if(!(utils::input("%a", tmp) % idx).status()) {
					error = true;
				} else {
					reset_(idx);
				}
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "recv")) { // recv
			if(cmdn == 2) {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				int idx = 0;
				if(!(utils::input("%a", tmp) % idx).status()) {
					error = true;
				} else {
					recv_(idx);
				}
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "send")) { // send data
			if(cmdn == 2) {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				int idx = 0;
				if(!(utils::input("%a", tmp) % idx).status()) {
					error = true;
				} else {
					send_(idx);
				}
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "stat")) { // stat
			if(cmdn == 2) {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				int idx = 0;
				if(!(utils::input("%a", tmp) % idx).status()) {
					error = true;
				} else {
					stat_(idx);
				}
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "data")) { // set frame data
			if(cmdn < 2) {
				error = true;
			} else {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				int idx = 0;
				if(!(utils::input("%a", tmp) % idx).status()) {
					error = true;
				} else {
					CAN::frame f;
					f.id = cur_id_;
					f.ide = ext_id_;
					f.ts = 0;
					if(cmdn > 2) {  // data frame
						f.rtr = 0;
						f.dlc = cmdn - 2;
						for(uint32_t i = 2; i < cmdn; ++i) {
							char tmp[64];
							cmd_.get_word(i, tmp, sizeof(tmp));
							uint32_t val;
							if(!(utils::input("%a", tmp) % val).status()) {
								error = true;
								break;
							} else {
								f.data[i - 2] = val;
							}
						}
					} else {  // リモートフレーム
						f.rtr = 1;
						f.dlc = 0;
					}
					if(!error) {
#ifdef LOOP
						if(cur_ch_ == 0) {
							can0_.set_mb(idx, f);
						} else if(cur_ch_ == 1) {
							can1_.set_mb(idx, f);
						}
#else
						can0_.set_mb(idx, f);
#endif
					}
				}
			}
		} else if(cmd_.cmp_word(0, "list")) { // get frame, list frame
			if(cmdn >= 2) {
				char tmp[64];
				cmd_.get_word(1, tmp, sizeof(tmp));
				int idx = 0;
				if(!(utils::input("%a", tmp) % idx).status()) {
					error = true;
				} else {
#ifdef LOOP
					if(cur_ch_ == 0) {
						can0_.list(idx);
					} else if(cur_ch_ == 1) {
						can1_.list(idx);
					}
#else
					can0_.list(idx);
#endif
				}				
			}
		} else if(cmd_.cmp_word(0, "state")) { // report state
			utils::format("CAN0: Recv error: %u, Send error: %u\n")
				% static_cast<uint16_t>(can0_.get_recv_error_count())
				% static_cast<uint16_t>(can0_.get_send_error_count());
#ifdef LOOP
			utils::format("CAN1: Recv error: %u, Send error: %u\n")
				% static_cast<uint16_t>(can1_.get_recv_error_count())
				% static_cast<uint16_t>(can1_.get_send_error_count());
#endif
		} else if(cmd_.cmp_word(0, "help")) { // help
#ifdef LOOP
			utils::format("    ch CH-no               set current CAN channel (CH-no: 0, 1)\n");
#endif
			utils::format("    id number              set current ID number\n");
			utils::format("    ext                    set ext-id mode\n");
			utils::format("    std                    set std-id mode\n");
			utils::format("    data MB-no [byte ...]  set frame data (MB-no: 0 to 31)\n");
			utils::format("    list MB-no             list frame (MB-no: 0 to 31)\n");
			utils::format("    reset MB-no            reset MB (MB-no: 0 to 31)\n");
			utils::format("    send MB-no             send frame (MB-no: 0 to 31)\n");
			utils::format("    recv MB-no             recv frame (MB-no: 0 to 31)\n");
			utils::format("    stat MB-no             stat frame (MB-no: 0 to 31)\n");
			utils::format("    state                  report CAN state\n");
			utils::format("    help                   command list (this)\n");
		} else {
			char tmp[64];
			cmd_.get_word(0, tmp, sizeof(tmp));
			utils::format("Command error: '%s'\n") % tmp;
		}
		if(error) {
			char tmp[64];
			tmp[0] = 0;
			cmd_.get_word(1, tmp, sizeof(tmp));
			utils::format("parameter error: '%s'\n") % tmp;
		}
	}
}


extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}


	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}


	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		return sci_.getch();
	}


	uint16_t sci_length()
	{
		return sci_.recv_length();
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定（100Hz）
		uint8_t intr = 4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto clk = F_ICLK / 1000000;
	utils::format("Start CAN sample for '%s' %d[MHz]\n") % system_str_ % clk;

	{  // CAN 開始
		CAN::mb_property prop;
		CAN::interrupt_t intr;
//		intr.txm_level = 1;
//		intr.rxm_level = 1;
		if(!can0_.start(CAN::SPEED::_1M, prop, intr)) {
			utils::format("Can't start CAN0...\n");
		} else {
			utils::format("CAN0: SPEED: %u [bps], BRP: %u, TSEG1: %u, TSEG2: %u, SJW: %u\n")
				% can0_.get_speed()
				% can0_.get_bcr_brp() % can0_.get_bcr_tseg1() % can0_.get_bcr_tseg2()
				% can0_.get_bcr_sjw();
		}
#ifdef LOOP
		if(!can1_.start(CAN::SPEED::_1M, prop, intr)) {
			utils::format("Can't start CAN1...\n");
		} else {
			utils::format("CAN1: SPEED: %u [bps], BRP: %u, TSEG1: %u, TSEG2: %u, SJW: %u\n")
				% can1_.get_speed()
				% can1_.get_bcr_brp() % can1_.get_bcr_tseg1() % can1_.get_bcr_tseg2()
				% can1_.get_bcr_sjw();
		}
#endif
	}

	LED::DIR = 1;
	LED::P = 0;
	LED::P = 1;

	cmd_.set_prompt("# ");

	auto send_tic = send_tic_;
	auto recv_tic = recv_tic_;
	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		legacy_command_();

		if(send_tic != send_tic_) {
			utils::format("Send OK.\n");
			send_tic = send_tic_;
		}
		if(recv_tic != recv_tic_) {
			utils::format("Recv OK.\n");
			recv_tic = recv_tic_;
		}

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
