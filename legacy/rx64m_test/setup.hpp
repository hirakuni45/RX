#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 setup クラス
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <random>
#include "client.hpp"
#include "write_file.hpp"
#include "chip/EUI_XX.hpp"

#ifdef LOGGING_FS
extern uint32_t fs_open_w_max;
extern uint32_t fs_open_r_max;
extern uint32_t fs_open_w_cnt;
extern uint32_t fs_open_r_cnt;
extern uint32_t fs_close_max;
extern uint32_t fs_close_cnt;
#endif

namespace seeda {

	uint32_t get_wf_lost();

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  setup クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class setup {

		static std::mt19937& at_rand_mt_()
		{
			static std::mt19937 mt(static_cast<int>(get_time()));
			return mt;
		}

		static uint32_t rand_(uint32_t mask = 0xffffffff) {
			auto& r = at_rand_mt_();
			return r() & mask;
		}


	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ＩＰ設定構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct ip_t {
			bool		dhcp_;
			uint8_t		ip_[4];
			uint8_t		gw_[4];
			uint8_t		mask_[4];

			ip_t() :
				dhcp_(false),
				ip_{ 192, 168, 3, 20 },
				gw_{ 192, 168, 3, 1 },
				mask_{ 255, 255, 255, 0 }
			{ }
		};

	private:
		static const uint8_t EUI_DHCP = 0x08;	// DHCP offset
		static const uint8_t EUI_IP   = 0x0A;	// IP offset
		static const uint8_t EUI_GW   = 0x10;	// GW offset
		static const uint8_t EUI_MASK = 0x14;	// MASK offset

		write_file&	write_file_;

		client&		client_;

		uint8_t		mac_[6];

		ip_t		ipt_;

		bool		signal_;

		uint32_t	restart_time_;
		char		restart_key_[8];

#ifdef SEEDA
		// mac address rom I/F
		typedef device::PORT<device::PORT1, device::bitpos::B5> MISO;
		typedef device::PORT<device::PORT1, device::bitpos::B6> MOSI;
		typedef device::PORT<device::PORT1, device::bitpos::B7> SPCK;
		typedef device::spi_io<MISO, MOSI, SPCK, device::soft_spi_mode::CK01> SPI;

		typedef device::PORT<device::PORT1, device::bitpos::B4> EUI_CS;
		typedef chip::EUI_XX<SPI, EUI_CS> EUI;
		SPI		spi_;
		EUI		eui_;

		static const uint16_t key_len = 7;
		const char* get_magic_() const {
			static const char* key = { "SEEDA03" };
			return key;
		}

		bool probe_magic_() {
			char tmp[16];
			eui_.read(0x00, tmp, key_len);
			tmp[key_len] = 0;
//utils::format("EUI Key: %02X %02X %02X %02X %02X %02X\n")
//	% static_cast<uint16_t>(tmp[0]) % static_cast<uint16_t>(tmp[1]) % static_cast<uint16_t>(tmp[2])
//	% static_cast<uint16_t>(tmp[3]) % static_cast<uint16_t>(tmp[4]) % static_cast<uint16_t>(tmp[5]);
			return strncmp(get_magic_(), tmp, key_len) == 0;
		}
#endif

		void disp_time_(time_t t, char* dst, uint32_t size)
		{
			uint32_t s = t % 60;
			t /= 60;
			uint32_t m = t % 60;
			t /= 60;
			uint32_t h = t % 24;
			t /= 24;
			utils::sformat("%d %02u:%02u:%02u", dst, size) % t % h % m % s;
		}


		// ログ表示
		void output_log_()
		{
			http_format("<table>");
			http_format("<tr><td>書き込み時間:</td><td>%u [分]</td></tr>") % write_file_.get_resume();
			http_format("<tr><td>ロスト時間:</td><td>%u [秒]</td></tr>") % get_wf_lost();
			http_format("<tr><td>FIFO バッファ:</td><td>%u / %u [秒]</td></tr>")
				% get_wf_fifo().length()
				% (get_wf_fifo().size() - 2);
			http_format("<tr><td>FIFO バッファ最大:</td><td>%u [秒]</td></tr>")
				% get_wf_max();
			http_format("</table>\n");

			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");

			http_format("<table>");
			char tmp[64];
			disp_time_(get_operating_time(), tmp, sizeof(tmp));
			http_format("<tr><td>稼動時間:</td><td>%s</td></tr>") % tmp;
			http_format("</table>\n");

#ifdef LOGGING_FS
			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");

			http_format("<table>");
			http_format("<tr><td>Ｗオープン最大時間:</td><td>%d [ms]</td></tr>") % fs_open_w_max;
			http_format("<tr><td>Ｗオープン回数:</td><td>%d</td></tr>") % fs_open_w_cnt;
			http_format("<tr><td>Ｒオープン最大時間:</td><td>%d [ms]</td></tr>") % fs_open_r_max;
			http_format("<tr><td>Ｒオープン回数:</td><td>%d</td></tr>") % fs_open_r_cnt;
			http_format("<tr><td>クローズ最大時間:</td><td>%d [ms]</td></tr>") % fs_close_max;
			http_format("<tr><td>クローズ回数:</td><td>%d</td></tr>") % fs_close_cnt;
			http_format("</table>\n");
#endif
		}

		static const uint32_t RES_MAGIC_ID_ = 0xA501;
		static const uint16_t RES_MAGIC_ = 0x0000;
		static const uint16_t RES_COUNT_ = 0x0004;

		uint32_t get_reset_count_() const {
			uint32_t n;
			at_sram().get32(RES_COUNT_, n);
			return n;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		setup(write_file& wf, client& cl) : write_file_(wf), client_(cl),
			mac_{ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED },
			ipt_(),
			signal_(false),
			restart_time_(5), restart_key_{ 0 }
#ifdef SEEDA
			, spi_(), eui_(spi_)
#endif
		{ }

		void init()
		{
			at_sram().start();
			uint32_t magic;
			at_sram().get32(RES_MAGIC_, magic);
			if(magic != RES_MAGIC_ID_) {
				at_sram().put32(RES_MAGIC_, RES_MAGIC_ID_);
				at_sram().put32(RES_COUNT_, 0x0001);
				at_logs().clear();
			} else {
				uint32_t cnt;
				at_sram().get32(RES_COUNT_, cnt);
				++cnt;
				at_sram().put32(RES_COUNT_, cnt);
			}
			
			at_logs().add(get_time(), "UN");  // リセット記録
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シグナルの参照
			@return シグナル
		*/
		//-----------------------------------------------------------------//
		bool& at_signal() { return signal_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  シグナルの取得
			@return シグナル
		*/
		//-----------------------------------------------------------------//
		bool get_signal() const { return signal_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  MAC アドレスへの参照
			@return 配列への参照
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get_mac() const { return mac_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ip_t への参照
			@return ip_t
		*/
		//-----------------------------------------------------------------//
		ip_t& at_ipt() { return ipt_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ip_t の取得
			@return ip_t
		*/
		//-----------------------------------------------------------------//
		const ip_t& get_ipt() const { return ipt_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  EUI デバイスの表示
		*/
		//-----------------------------------------------------------------//
		void list_eui() const
		{
			utils::format("EEPROM EUI-48 Node Identity List\n"); 
			utils::format("  DHCP: %s\n") % (ipt_.dhcp_ ? "Enable" : "Disable");
			utils::format("  IP:   %d.%d.%d.%d\n")
				% static_cast<uint32_t>(ipt_.ip_[0])
				% static_cast<uint32_t>(ipt_.ip_[1])
				% static_cast<uint32_t>(ipt_.ip_[2])
				% static_cast<uint32_t>(ipt_.ip_[3]);
			utils::format("  GW:   %d.%d.%d.%d\n")
				% static_cast<uint32_t>(ipt_.gw_[0])
				% static_cast<uint32_t>(ipt_.gw_[1])
				% static_cast<uint32_t>(ipt_.gw_[2])
				% static_cast<uint32_t>(ipt_.gw_[3]);
			utils::format("  MASK: %d.%d.%d.%d\n")
				% static_cast<uint32_t>(ipt_.mask_[0])
				% static_cast<uint32_t>(ipt_.mask_[1])
				% static_cast<uint32_t>(ipt_.mask_[2])
				% static_cast<uint32_t>(ipt_.mask_[3]);
			utils::format("  MAC:  %02X:%02X:%02X:%02X:%02X:%02X\n\n")
				% static_cast<uint32_t>(mac_[0])
				% static_cast<uint32_t>(mac_[1])
				% static_cast<uint32_t>(mac_[2])
				% static_cast<uint32_t>(mac_[3])
				% static_cast<uint32_t>(mac_[4])
				% static_cast<uint32_t>(mac_[5]);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  EUI デバイス初期化
			@param[in]	dev	開発モードの場合「true」
		*/
		//-----------------------------------------------------------------//
		void init_eui(bool dev)
		{
#ifdef SEEDA
			// ソフトループなので、設定値より高目となり、実測で８３３ＫＨｚ
			spi_.start(5000000);  // Clock 500KHz
			eui_.start();  // EUI デバイス初期化

			{  // state
				uint8_t st = eui_.get_state();
				utils::format("EUI State: %02X\n") % static_cast<uint16_t>(st);
			}

			{  // check magic ID
				if(probe_magic_()) {
					uint8_t dhcp[1];
					eui_.read(EUI_DHCP, dhcp, 1);
					ipt_.dhcp_ = dhcp[0] != 0;
					eui_.read(EUI_IP,   ipt_.ip_, 4);
					eui_.read(EUI_GW,   ipt_.gw_, 4);
					eui_.read(EUI_MASK, ipt_.mask_, 4);
				} else {
					ipt_.dhcp_ = false;
					ipt_.ip_[0] = 192;
					ipt_.ip_[1] = 168;
					ipt_.ip_[2] = 1;
					ipt_.ip_[3] = 22;
					ipt_.gw_[0] = 192;
					ipt_.gw_[1] = 168;
					ipt_.gw_[2] = 1;
					ipt_.gw_[3] = 1;
					ipt_.mask_[0] = 255;
					ipt_.mask_[1] = 255;
					ipt_.mask_[2] = 255;
					ipt_.mask_[3] = 0;
					write_eui();
					utils::format("EUI Magic code: false (then first write)\n");
				}
			}

			if(0) {
				char tmp[8];
				eui_.read(0x00, tmp, key_len);
				tmp[key_len] = 0;
utils::format("EUI load: %02X %02X %02X %02X %02X %02X\n")
	% static_cast<uint16_t>(tmp[0]) % static_cast<uint16_t>(tmp[1]) % static_cast<uint16_t>(tmp[2])
	% static_cast<uint16_t>(tmp[3]) % static_cast<uint16_t>(tmp[4]) % static_cast<uint16_t>(tmp[5]);
			}

			{
				// read EUI-48
				uint8_t tmp[6];
				eui_.read(EUI::eui48_org, tmp, 6);
				if(  tmp[0] == 0xff && tmp[1] == 0xff && tmp[2] == 0xff
				  && tmp[3] == 0xff && tmp[4] == 0xff && tmp[5] == 0xff) {

				} else if(tmp[0] == 0x00 && tmp[1] == 0x00 && tmp[2] == 0x00
					   && tmp[3] == 0x00 && tmp[4] == 0x00 && tmp[5] == 0x00) {

				} else {
					for(int i = 0; i < 6; ++i) {
						mac_[i] = tmp[i];
					}
				}
			}

			// develope の場合、常に DHCP は有効
			if(dev) {
				ipt_.dhcp_ = true;
			}
#endif
			list_eui();
		}


		//-----------------------------------------------------------------//
		/*
			@brief  EUI デバイスへＩＰ書き込み
		*/
		//-----------------------------------------------------------------//
		void write_eui()
		{
#ifdef SEEDA
			eui_.write(0x00, get_magic_(), key_len);
			char tmp[1];
			tmp[0] = ipt_.dhcp_ ? 0x01 : 0x00;
			eui_.write(EUI_DHCP, tmp, 1);
			eui_.write(EUI_IP,   ipt_.ip_,   4);
			eui_.write(EUI_GW,   ipt_.gw_,   4);
			eui_.write(EUI_MASK, ipt_.mask_, 4);
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リスタート・キーの取得
			@return リスタート・キー
		*/
		//-----------------------------------------------------------------//
		const char* get_restart_key() const { return restart_key_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  クライアント機能設定画面
			@param[in]	dev	develope の場合「true」
		*/
		//-----------------------------------------------------------------//
		void render_client(bool dev)
		{
			net_tools::render_version();
			net_tools::render_date_time();

			/// auto mount = at_sdc().get_mount();
			bool mount = true;

			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");

			if(dev) {
				http_format("Develope mode<br>");
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

			// ARP list
			{
				auto n = ether_arp_num();
				for(uint32_t i = 0; i < n; ++i) {
					const auto* p = ether_arp_get(i);
					if(p->ae_state == AS_FREE) continue;

					http_format("(%d) %d.%d.%d.%d  --->  %02X:%02X:%02X:%02X:%02X:%02X<br>\n")
						% i
						% static_cast<uint32_t>(p->ae_pra[0])
						% static_cast<uint32_t>(p->ae_pra[1])
						% static_cast<uint32_t>(p->ae_pra[2])
						% static_cast<uint32_t>(p->ae_pra[3])
						% static_cast<uint32_t>(p->ae_hwa[0])
						% static_cast<uint32_t>(p->ae_hwa[1])
						% static_cast<uint32_t>(p->ae_hwa[2])
						% static_cast<uint32_t>(p->ae_hwa[3])
						% static_cast<uint32_t>(p->ae_hwa[4])
						% static_cast<uint32_t>(p->ae_hwa[5]);
				}
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

			// クライアント機能設定
			http_format("<form method=\"POST\" action=\"/cgi/set_client.cgi\">\n");
			http_format("<table><tr><td>クライアント機能：</td>"
			   "<td><input type=\"checkbox\" name=\"enable\" value=\"on\"%s>有効</td></tr>\n")
					% (client_.get_enable() ? " checked=\"checked\"" : "");
			http_format("<tr><td>接続先 IP：</td>"
				"<td><input type=\"text\" name=\"ip\" size=\"15\" value=\"%d.%d.%d.%d\"></td></tr>\n")
				% static_cast<int>(client_.get_ip()[0])
				% static_cast<int>(client_.get_ip()[1])
				% static_cast<int>(client_.get_ip()[2])
				% static_cast<int>(client_.get_ip()[3]);
			http_format("<tr><td>接続先ポート：</td>"
				"<td><input type=\"text\" name=\"port\" size=\"5\" value=\"%d\"></td></tr>\n")
				% static_cast<int>(client_.get_port());
			http_format("<tr><td><input type=\"submit\" value=\"接続先設定\"%s></td></tr>\n")
				% (mount ? "" : " disabled=\"disabled\"");
			http_format("</table></form>\n");

			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");

			http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定画面\">\n");
			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  設定ページ、レンダリング・メイン
			@param[in]	dev	develope の場合「true」
		*/
		//-----------------------------------------------------------------//
		void render_main(bool dev)
		{
			net_tools::render_version();
			net_tools::render_date_time();
			http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");

			if(dev) {
				http_format("Develope mode<br>");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"リロード\">\n");
			http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");

			http_format("<input type=\"button\" onclick=\"location.href='/data'\" value=\"データ表示\">\n");
			http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");

			if(0) {  // 内臓 A/D 表示
				float v = static_cast<float>(get_adc(5)) / 4095.0f * 3.3f;
				http_format("バッテリー電圧： %4.2f [V]<br>") % v;
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">");
			}

			// RTC 設定
			{
				http_format("<form method=\"POST\" action=\"/cgi/set_rtc.cgi\">\n");
				auto t = get_time();
				struct tm *m = localtime(&t);
				http_format("<table><tr>"
					"<td>年月日(yyyy/mm/dd)：</td>"
					"<td><input type=\"text\" name=\"date\" size=\"10\" value=\"%d/%d/%d\"></td></tr>\n")
					% static_cast<int>(m->tm_year + 1900)
					% static_cast<int>(m->tm_mon + 1) % static_cast<int>(m->tm_mday);
				http_format("<tr>"
					"<td>時間(hh:mm[:ss])：</td>"
					"<td><input type=\"text\" name=\"time\" size=\"8\" value=\"%d:%d\"></td></tr>\n")
					% static_cast<int>(m->tm_hour) % static_cast<int>(m->tm_min);
				http_format("<tr><td><input type=\"submit\" value=\"ＲＴＣ設定\"></td></tr>\n");
				http_format("</table></form>\n");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			// MAC アドレス表示
			{
				http_format("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X<br>")
					% static_cast<uint32_t>(mac_[0])
					% static_cast<uint32_t>(mac_[1])
					% static_cast<uint32_t>(mac_[2])
					% static_cast<uint32_t>(mac_[3])
					% static_cast<uint32_t>(mac_[4])
					% static_cast<uint32_t>(mac_[5]);
			}

			// IP 設定
			{
				http_format("<form method=\"POST\" action=\"/cgi/set_ip.cgi\">\n");
				http_format("<table>"
					   "<tr><td><input type=\"checkbox\" name=\"dhcp\" value=\"on\"%s>ＤＨＣＰ</td></tr>")
						% (ipt_.dhcp_ ? " checked=\"checked\"" : "");
				http_format("<tr><td>IP:</td>");
				for(int i = 0; i < 4; ++i) {
					http_format("<td><input type=\"text\" name=\"ip%d\" size=\"3\" value=\"%d\"></td>")
						% i
						% static_cast<uint32_t>(ipt_.ip_[i]);
				}
				http_format("</tr><tr><td>GW:</td>");
				for(int i = 0; i < 4; ++i) {
					http_format("<td><input type=\"text\" name=\"gw%d\" size=\"3\" value=\"%d\"></td>")
						% i
						% static_cast<uint32_t>(ipt_.gw_[i]);
				}
				http_format("</tr><tr><td>MASK:</td>");
				for(int i = 0; i < 4; ++i) {
					http_format("<td><input type=\"text\" name=\"mask%d\" size=\"3\" value=\"%d\"></td>")
						% i
						% static_cast<uint32_t>(ipt_.mask_[i]);
				}
				http_format("</tr>");
				http_format("<td><input type=\"submit\" value=\"ＩＰ設定\"></td>\n");
				http_format("</table></form>\n");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			// 検査用Ａ／Ｄ設定
			if(dev) {
				http_format("<form method=\"POST\" action=\"/cgi/dev_adc.cgi\"><table>\n");
				http_format("<tr>"
					"<td><input type=\"radio\" name=\"mode\" value=\"normal\"%s>通常変換</td>"
					"<td><input type=\"radio\" name=\"mode\" value=\"signal\"%s>信号生成</td>"
					"</tr>\n")
					% (!signal_ ? " checked" : "")
					% ( signal_ ? " checked" : "");

				http_format("<tr><td><input type=\"submit\" value=\"設定\"></td></tr></table></form>");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			// Ａ／Ｄ変換設定
			{
				http_format("<form method=\"POST\" action=\"/cgi/set_adc.cgi\"><table>\n");
				for(uint32_t ch = 0; ch < get_channel_num(); ++ch) {
					const seeda::sample_t& t = at_sample(ch);
					http_format("<tr>"
						"<td>CH%d</td>"
						"<td><input type=\"radio\" name=\"mode%d\" value=\"none\"%s>数値</td>"
						"<td><input type=\"radio\" name=\"mode%d\" value=\"real\"%s>係数値</td>"
						"<td><input type=\"radio\" name=\"mode%d\" value=\"abs\"%s>絶対値</td>"
						"<td>　ゲイン：</td>"
						"<td><input type=\"text\" name=\"gain%d\" size=\"6\" value=\"%6.2f\"></td>"
						"<td>中心値：</td>"
						"<td><input type=\"text\" name=\"center%d\" size=\"6\" value=\"%d\"></td>"
						"<td>下限：</td>"
						"<td><input type=\"text\" name=\"level_lo%d\" size=\"6\" value=\"%d\"></td>"
						"<td>上限：</td>"
						"<td><input type=\"text\" name=\"level_hi%d\" size=\"6\" value=\"%d\"></td>"
						"</tr>\n")
						% ch
						% ch % (t.mode_ == seeda::sample_t::mode::none ? " checked" : "")
						% ch % (t.mode_ == seeda::sample_t::mode::real ? " checked" : "")
						% ch % (t.mode_ == seeda::sample_t::mode::abs  ? " checked" : "")
						% ch % t.gain_
						% ch % static_cast<int>(t.center_)
						% ch % static_cast<int>(t.limit_lo_level_)
						% ch % static_cast<int>(t.limit_hi_level_);
				}
///				http_format("<tr><td><input type=\"submit\" value=\"設定\"%s></td></tr>"
///						   "</table></form>") % (mount ? "" : " disabled=\"disabled\"");
				http_format("<tr><td><input type=\"submit\" value=\"設定\"></td></tr>"
						   "</table></form>");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			{  // クライアント機能設定ボタン
				http_format("<input type=\"button\" onclick=\"location.href='/client'\""
							" value=\"クライアント機能\">");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			auto mount = at_sdc().get_mount();

			// ファイル書き込み設定
			if(at_logs().find("*")) {
				http_format("システム障害（自動リセット・リミット）<br>");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">");
			} else {
				http_format("<form method=\"POST\" action=\"/cgi/set_write.cgi\">\n");
				http_format("<table><tr><td>ファイルパス：</td>");
				if(!write_file_.get_enable()) {
					http_format("<td><input type=\"text\" name=\"fname\" size=\"32\" value=\"%s\"></td></tr>\n")
						% write_file_.get_path();
				} else {
					http_format("<td>%s</td></tr>\n") % write_file_.get_path();
				}

				if(!write_file_.get_enable()) {
					http_format("<tr><td><input type=\"submit\" value=\"書き込み開始\"%s></td></tr>")
						% (mount ? "" : " disabled=\"disabled\"");
				} else {
#if 0
					char tmp[256];
					strcpy(tmp, write_file_.get_filename());
					char* p = strrchr(tmp, '/');
					if(p != nullptr) *p = 0;
					http_format("<tr><td>書き込みパス：</td><td>%s</td></tr>") % tmp;
#endif
					http_format("<tr><td>書き込み数：</td><td>%d 回</td></tr>")
						% write_file_.get_resume();
					http_format("<tr><td>ロスト時間：</td><td>%u 秒</td></tr>")
						% get_wf_lost();
					http_format("<tr><td><input type=\"submit\" value=\"書き込み停止\"></td></tr>");
				}
				http_format("</table></form>");

				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			// システム設定
			{
				http_format("<input type=\"button\" onclick=\"location.href='/system'\""
							" value=\"システム設定\">");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			if(!mount) {
				http_format("ＳＤカードがありません。<br>");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  システム設定画面
		*/
		//-----------------------------------------------------------------//
		void render_system()
		{
			net_tools::render_version();
			net_tools::render_date_time();

			auto mount = at_sdc().get_mount();

			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");

			{  // リセット情報表示
				http_format("<table>");
				http_format("<tr><td>リセット回数:</td><td>%u</td></tr>") % get_reset_count_();
				http_format("</table>\n");
			}

			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");

			{  // プリファレンス消去ボタン
///				http_format("<input type=\"button\" onclick=\"location.href='/preference'\""
///							" value=\"プリファレンス消去\"%s>") % (mount ? "" : " disabled=\"disabled\"");
				http_format("<input type=\"button\" onclick=\"location.href='/preference'\""
							" value=\"プリファレンス消去\">");
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

			{  // ＳＤカード・ステータス・ボタン
				http_format("<input type=\"button\" onclick=\"location.href='/sdc_state'\""
							" value=\"ＳＤカード情報\"%s>") % (mount ? "" : " disabled=\"disabled\"");
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

			{  // ＳＤカード・ログ表示・ボタン
				http_format("<input type=\"button\" onclick=\"location.href='/sdc_elog'\""
							" value=\"ＳＤカードログ\">");
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

			// 各種情報表示
			{
				output_log_();
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

#ifdef WATCH_DOG
			{
				http_format("<form method=\"POST\" action=\"/cgi/watchdog.cgi\">\n");
				http_format("<table><tr><td>ウオッチドッグ：</td>"
				   "<td><input type=\"checkbox\" name=\"enable\" value=\"on\"%s>有効</td></tr>")
						% (get_pre().get().watchdog_enable_  ? " checked=\"checked\"" : "");
				http_format("<tr><td>規定時間（分）：</td>"
					"<td><input type=\"text\" name=\"wdtime\" size=\"3\" value=\"%d\"></td></tr>")
					% get_pre().get().watchdog_time_;
				http_format("<tr><td><input type=\"submit\" value=\"規定設定\"></td></tr>");
				http_format("</table></form>\n");

				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}
#endif
			{
				for(int i = 0; i < 6; ++i) {
					char o = rand_() & 0xffff;
					if(o & 1) { o >>= 1; o %= 10; o += '0'; }
					else { o >>= 1; o %= 26; o += 'A'; }
					restart_key_[i] = o;
				}
				restart_key_[6] = 0;

				http_format("<form method=\"POST\" action=\"/cgi/restart.cgi\"><table>");
				http_format("<tr><td>リセット（秒）：</td>");
				http_format("<td><input type=\"text\" name=\"restime\" size=\"3\" value=\"%d\"></td>")
					% restart_time_;
				http_format("<td>キー：</td>");
				http_format("<td><input type=\"text\" name=\"reskey\" size=\"6\" value=\"------\"></td>");
				http_format("<td>　%s</td></tr>") % restart_key_;
				http_format("<tr><td><input type=\"submit\" value=\"予約設定\"></td></tr>");
				http_format("</table></form>\n");
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

#if 0
			// TELNET 接続
			http_format("<form method=\"POST\" action=\"/cgi/set_telnet.cgi\">\n");
			http_format("<table><tr><td>TELNET 機能：</td>"
			   "<td><input type=\"checkbox\" name=\"enable\" value=\"on\"%s>有効</td></tr>\n")
					% (client_.get_enable() ? " checked=\"checked\"" : "");
			http_format("<tr><td>接続先ポート：</td>"
				"<td><input type=\"text\" name=\"port\" size=\"5\" value=\"%d\"></td></tr>")
				% static_cast<int>(client_.get_port());
			http_format("<tr><td><input type=\"submit\" value=\"TELNET 設定\"%s></td></tr>")
				% (mount ? "" : " disabled=\"disabled\"");
			http_format("</table></form>\n");
#endif

			http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定画面\">\n");
			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  システム・エラー画面
		*/
		//-----------------------------------------------------------------//
		void render_system_error()
		{
			net_tools::render_version();
			net_tools::render_date_time();

			http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			http_format("ファイルパスは31文字以内で入力して下さい<br>");
			http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定画面\">\n");
			http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
		}
	};
}
