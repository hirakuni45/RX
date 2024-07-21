//=====================================================================//
/*! @file
    @brief  CAN サンプル @n
			シリアルターミナルを接続して、対話式で、通信を行う @n
			※使い方は、コマンド「help」を参照 @n
			「MULTI」を有効にするとマルチチャネルサポート @n
			「LEGACY」モードの場合、メールボックス直接操作
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2023 Kunihito Hiramatsu @n
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
#include "common/can_analize.hpp"

#include "common/command.hpp"

// #define VALID_FILTER

#ifdef VALID_FILTER
#include <boost/unordered_set.hpp>
// #include <unordered_set>
// #include <set>
#endif

namespace {

	static constexpr uint32_t can_cmd_ver_ = 100;

#if defined(SIG_RX71M)
	#define MULTI
#elif defined(SIG_RX64M)
//	#define MULTI
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT		cmt_;

	//
	// CAN 関連定義
	//
	typedef device::can_io_def CAN;

	// CAN 受信バッファの定義
	typedef utils::fixed_fifo<device::can_frame, 256> CAN_RXB;
	// CAN 送信バッファの定義
	typedef utils::fixed_fifo<device::can_frame, 256> CAN_TXB;

	typedef device::can_io<board_profile::CAN0_CH, CAN_RXB, CAN_TXB, board_profile::CAN0_PORT> CAN0;
	CAN0	can0_;

	// CAN の解析機能は CAN0 のみとする
	typedef utils::can_analize<CAN0> ANALIZE;
	ANALIZE	analize_(can0_);

	uint32_t	cur_ch_ = 0;

#ifdef MULTI
	typedef device::can_io<board_profile::CAN1_CH, CAN_RXB, CAN_TXB, board_profile::CAN1_PORT> CAN1;
	CAN1	can1_;

#ifdef VALID_FILTER
	// 有効な ID だけ通すフィルター
	// std:: を使う場合、Makefile の USER_LIBS を変更する
	typedef boost::unordered_set<uint32_t> VALID;
//	typedef std::set<uint32_t> VALID;
//	typedef std::unordered_set<uint32_t> VALID;
//	typedef const boost::unordered_set<uint32_t> VALID;
	VALID	valid_{ 0x123, 0x200, 0x300, 0xaaa, 15, 21, 33 };
	bool	ena_valid_ = true;
#endif
#endif

	uint32_t	cur_id_;
	bool		ext_id_;

	typedef utils::command<256> CMD;
	CMD		cmd_;


	bool get_cmd_id_(uint32_t i, uint32_t& id)
	{
		uint32_t v = 0;
		char tmp[64];
		cmd_.get_word(i, tmp, sizeof(tmp));
		if(!(utils::input("%a", tmp) % v).status()) {
			utils::format("ID parse error: '%s'\n") % tmp;
			return false;
		} else {
			id = v;
			return true;
		}
	}


	bool get_cmd_data_(uint32_t top, uint8_t* dst, uint32_t num)
	{
		if(num > 8) num = 8;

		for(uint32_t i = top; i < (top + num); ++i) {
			char tmp[64];
			cmd_.get_word(i, tmp, sizeof(tmp));
			uint32_t val = 0;
			if(!(utils::input("%a", tmp) % val).status()) {
				utils::format("DATA parse error: '%s'\n") % tmp;
				return false;
			} else {
				dst[i - top] = val;
			}
		}
		return true;
	}


	void stat_(uint32_t idx)
	{
		uint8_t ret = 0;
		if(cur_ch_ == 0) {
			ret = can0_.stat_mb(idx);
		} else if(cur_ch_ == 1) {
#ifdef MULTI
			ret = can1_.stat_mb(idx);
#endif
		}
		utils::format("MCTL: 0x%02X (0b%08b)\n")
			% static_cast<uint16_t>(ret) % static_cast<uint16_t>(ret);
	}


	void list_(uint32_t idx)
	{
		if(cur_ch_ == 0) {
			can0_.list_mb(idx);
		} else if(cur_ch_ == 1) {
#ifdef MULTI
			can1_.list_mb(idx);
#endif
		}
	}


	void status_()
	{
		utils::format("CAN0: Send error = %d, Recv error = %d\n")
			% can0_.get_send_error_count() % can0_.get_recv_error_count();
#ifdef MULTI
		utils::format("CAN0: Send error = %d, Recv error = %d\n")
			% can1_.get_send_error_count() % can1_.get_recv_error_count();
#endif
	}


	void send_data_(uint32_t id, const uint8_t* src, uint32_t len)
	{
		if(cur_ch_ == 0) {
			can0_.send(id, src, len, ext_id_);
		} else if(cur_ch_ == 1) {
#ifdef MULTI
			can1_.send(id, src, len, ext_id_);
#endif
		}
	}


	void send_loop_(uint32_t count, bool rtr = false)
	{
		for(uint32_t i = 0; i < count; ++i) {
			uint32_t id;
			if(ext_id_) {
				id = (rand() % 0x1fffffff) + 1;  // 0 を含まない
			} else {
				id = (rand() % 0x7ff) + 1;  // 0 を含まない
			}
			if(rtr) {
				send_data_(id, nullptr, 0);
			} else {
				uint32_t len = (rand() % 7) + 1;  // 1 to 8 bytes
				uint8_t tmp[8];
				for(uint8_t j = 0; j < len; ++j) tmp[j] = rand();
				send_data_(id, tmp, len);
			}
		}
	}


	// 高位コマンド操作系（標準）
	void command_()
	{
		if(!cmd_.service()) {
			return;
		}

		auto cmdn = cmd_.get_words();

		bool error = false;
		if(cmdn == 0) {
#ifdef MULTI
		} else if(cmd_.cmp_word(0, "ch")) { // set current channel
			if(cmdn >= 2) {
				int32_t val;
				if(!cmd_.get_integer(1, val)) {
					error = true;
				} else {
					if(val == 0 || val == 1) {
						cur_ch_ = val;
					} else {
						error = true;
					}
				}
			} else {
				utils::format("Current device CAN%d\n") % cur_ch_;
			}
#ifdef VALID_FILTER
		} else if(cmd_.cmp_word(0, "valid")) { // valid ID disable/enable
			if(cmdn >= 2) {
				if(cmd_.cmp_word(1, "0")) {
					ena_valid_ = false;
				} else if(cmd_.cmp_word(1, "1")) {
					ena_valid_ = true;
				}
			} else {
				utils::format("Valid ID filter: %d\n") % static_cast<int>(ena_valid_);
			}
		} else if(cmd_.cmp_word(0, "valist")) { // list valid ID
			utils::format("Valid filter ID: ");
			for(auto n : valid_) {
				utils::format("%d, ") % n;
			}
			utils::format("\n");
#endif
#endif
		} else if(cmd_.cmp_word(0, "ext")) { // ext-id mode
			ext_id_ = true;
		} else if(cmd_.cmp_word(0, "std")) { // std-id mode
			ext_id_ = false;
		} else if(cmd_.cmp_word(0, "send")) { // データ送信
			if(cmdn >= 2) {
				uint32_t id = 0;
				uint8_t data[8];
				if(!get_cmd_id_(1, id)) {
					error = true;
				} else if(cmdn >= 3) {
					if(!get_cmd_data_(2, data, cmdn - 2)) {
						error = true;
					}
				}
				if(!error) {
					send_data_(id, data, cmdn - 2);
				}
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "status")) { // status
			status_();
		} else if(cmd_.cmp_word(0, "stat")) { // stat
			if(cmdn == 2) {
				int32_t val;
				if(!cmd_.get_integer(1, val, false)) {
					error = true;
				} else {
					stat_(val);
				}
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "list")) { // get frame, list frame
			if(cmdn >= 2) {
				int32_t val;
				if(!cmd_.get_integer(1, val, false)) {
					error = true;
				} else {
					list_(val);
				}
			}
		} else if(cmd_.cmp_word(0, "map")) {
			if(cmdn >= 2) {
				int32_t val;
				if(!cmd_.get_integer(1, val, false)) {
					error = true;
				} else {
					analize_.list(val);
				}				
			} else {
				analize_.list_all();
			}
		} else if(cmd_.cmp_word(0, "clear")) {
			if(cmdn >= 2) {
				int32_t val;
				if(!cmd_.get_integer(1, val, false)) {
					error = true;
				} else {
					analize_.clear(val);
				}				
			} else {
				analize_.clear_all();
			}
		} else if(cmd_.cmp_word(0, "dump")) {
			if(cmdn >= 2) {
				int32_t val;
				if(!cmd_.get_integer(1, val, false)) {
					error = true;
				} else {
					if(!analize_.dump(val)) {
						utils::format("Can't find ID: x%07X (%u)\n") % val % val;
					}
				}				
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "send_loop")) {
			if(cmdn >= 2) {
				int32_t val;
				if(!cmd_.get_integer(1, val, false)) {
					error = true;
				} else {
					bool rtr = false;
					if(cmdn >= 3 && cmd_.cmp_word(2, "-rtr")) {
						rtr = true;
					}
					send_loop_(val, rtr);
				}
			} else {
				error = true;
			}
		} else if(cmd_.cmp_word(0, "help")) { // help
			utils::format("CAN command version: %d.%02d\n")
				% (can_cmd_ver_ / 100) % (can_cmd_ver_ % 100);
#ifdef MULTI
			utils::format("    ch CH-no               set current CAN channel (CH-no: 0, 1)\n");
#ifdef VALID_FILTER
			utils::format("    valid [0/1]            valid ID-filter 0:disable/1:enable\n");
			utils::format("    valist                 list valid filter IDs\n");
#endif
#endif
			utils::format("    ext                    set ext-id mode\n");
			utils::format("    std                    set std-id mode\n");
			utils::format("    send CAN-ID [data...]  send data frame\n");
			utils::format("    stat MB-no             stat MCTLx register (MB-no: 0 to 31)\n");
			utils::format("    list MB-no             list MBx register (MB-no: 0 to 31)\n");
			utils::format("    status                 list recv/send error count\n");
			utils::format("    clear [CAN-ID]         clear map\n");
			utils::format("    map [CAN-ID]           Display all collected IDs\n");
			utils::format("    dump CAN-ID            dump frame data\n");
			utils::format("    send_loop NUM [-rtr]   random ID, random DATA, send loop (RTR)\n");
			utils::format("    help                   command list (this)\n");
			utils::format("\n");
			utils::format("  Input number: nnn decimal, xnnn hexa-decimal, bnnn binary\n");
		} else {
			char tmp[64];
			cmd_.get_word(0, tmp, sizeof(tmp));
			utils::format("Command error: '%s'\n") % tmp;
		}

		if(error) {
			utils::format("Parameter error...\n");
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
	SYSTEM_IO::boost_master_clock();

	using namespace board_profile;

	{  // タイマー設定（100Hz）
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto clk = device::clock_profile::ICLK / 1000000;
	utils::format("Start CAN sample for '%s' %d[MHz]\n") % system_str_ % clk;
	utils::format("CAN command version: %d.%02d\n") % (can_cmd_ver_ / 100) % (can_cmd_ver_ % 100);

	{  // CAN 開始
		constexpr auto can_speed = CAN::SPEED::_1M;
		// コンパイル時、CAN 速度が設定可能か評価する。
		static_assert(CAN0::probe_speed(can_speed), "CAN divider indivisible.");
		if(!can0_.start(can_speed)) {
			utils::format("Can't start CAN0...\n");
		} else {
			utils::format("CAN0: SPEED: %u [bps], BRP: %u, TSEG1: %u, TSEG2: %u, SJW: %u\n")
				% can0_.get_speed()
				% can0_.get_bcr_brp() % can0_.get_bcr_tseg1() % can0_.get_bcr_tseg2()
				% can0_.get_bcr_sjw();
			utils::format("    RX Interrupt level: %u, TX Interrupt level: %u\n")
				% static_cast<uint16_t>(can0_.get_rxm_level())
				% static_cast<uint16_t>(can0_.get_txm_level());
		}
#ifdef MULTI
		if(!can1_.start(CAN::SPEED::_1M)) {
			utils::format("Can't start CAN1...\n");
		} else {
			utils::format("CAN1: SPEED: %u [bps], BRP: %u, TSEG1: %u, TSEG2: %u, SJW: %u\n")
				% can1_.get_speed()
				% can1_.get_bcr_brp() % can1_.get_bcr_tseg1() % can1_.get_bcr_tseg2()
				% can1_.get_bcr_sjw();
			utils::format("    RX Interrupt level: %u, TX Interrupt level: %u\n")
				% static_cast<uint16_t>(can1_.get_rxm_level())
				% static_cast<uint16_t>(can1_.get_txm_level());
		}
#endif
	}

	LED::DIR = 1;
	LED::P = 0;
	LED::P = 1;

	cmd_.set_prompt("# ");

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		command_();

		analize_.service();

#ifdef MULTI
		while(can1_.get_recv_num() > 0) {
			auto frm = can1_.get_recv_frame();
#ifdef VALID_FILTER
			if(ena_valid_) {
				if(valid_.find(frm.get_id()) != valid_.end()) {
					utils::format("\nCAN1:\n");
					CAN::list(frm, "  ");
				}
			}
#else
			utils::format("\nCAN1:\n");
			CAN::list(frm, "  ");
#endif
		}
#endif

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
