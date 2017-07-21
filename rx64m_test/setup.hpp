#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 setup クラス
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "client.hpp"
#include "write_file.hpp"

#include "chip/EUI_XX.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  setup クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class setup {

		write_file&	write_file_;

		client&		client_;

		uint8_t		mac_[6];

		bool		dhcp_;
		uint8_t		ip_[4];

#ifdef SEEDA
		// mac address rom I/F
		typedef device::PORT<device::PORT1, device::bitpos::B5> MISO;
		typedef device::PORT<device::PORT1, device::bitpos::B6> MOSI;
		typedef device::PORT<device::PORT1, device::bitpos::B7> SPCK;
		typedef device::spi_io<MISO, MOSI, SPCK> SPI;

		typedef device::PORT<device::PORT1, device::bitpos::B4> EUI_CS;
		typedef device::PORT<device::PORT8, device::bitpos::B0> EUI_HOLD;
		typedef chip::EUI_XX<SPI, EUI_CS> EUI;
		SPI		spi_;
		EUI		eui_;

		void write_eui_()
		{
			eui_.write(0x00, "SEDA03", 6);
			uint8_t tmp[1];
			tmp[0] = dhcp_ ? 0x01 : 0x00;
			eui_.write(0x08, tmp, 1);
			eui_.write(0x0A, ip_, 4);
		}
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		setup(write_file& wf, client& cl) : write_file_(wf), client_(cl),
			mac_{ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }, dhcp_(true), ip_{ 192, 168, 3, 20 }
#ifdef SEEDA
			, spi_(), eui_(spi_)
#endif
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  DHCP への参照
			@return DHCP
		*/
		//-----------------------------------------------------------------//
		bool& at_dhcp() { return dhcp_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  DHCP への参照
			@return DHCP
		*/
		//-----------------------------------------------------------------//
		bool get_dhcp() const { return dhcp_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  MAC アドレスへの参照
			@return 配列への参照
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get_mac() const { return mac_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスへの参照
			@param[in]	idx	0 to 3
			@return 配列への参照
		*/
		//-----------------------------------------------------------------//
		uint8_t& at_ip(uint8_t idx) { return ip_[idx]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスのポインター
			@return 配列ポインター
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get_ip() const { return ip_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  EUI デバイス初期化
			@param[in]	dev	開発モードの場合「true」
		*/
		//-----------------------------------------------------------------//
		void init_eui(bool dev)
		{
#ifdef SEEDA
			spi_.start_sdc(500000);  // Clock 500KHz
			EUI_HOLD::DIR = 1;
			EUI_HOLD::P = 1;
			eui_.start();

			// check magic ID
			{
				char tmp[6];
				eui_.read(0x00, tmp, 6);
				if(strncmp("SEDA03", tmp, 6) == 0) {
					uint8_t dhcp[1];
					eui_.read(0x08, dhcp, 1);
					dhcp_ = dhcp[0] != 0;
					eui_.read(0x0A, ip_, 4);
				} else {
					if(!dev) {
						ip_[0] = 192;
						ip_[1] = 168;
						ip_[2] = 1;
						ip_[3] = 22;
						dhcp_ = false;
					}
					write_eui_();
				}
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
				dhcp_ = true;
			}
#endif
			utils::format("EEPROM EUI-48 Node Identity list\n"); 
			utils::format("  DHCP: %s\n") % (dhcp_ ? "Enable" : "Disable");
			utils::format("  IP:   %d.%d.%d.%d\n")
				% static_cast<uint32_t>(ip_[0])
				% static_cast<uint32_t>(ip_[1])
				% static_cast<uint32_t>(ip_[2])
				% static_cast<uint32_t>(ip_[3]);
			utils::format("  MAC:  %02X:%02X:%02X:%02X:%02X:%02X\n\n")
				% static_cast<uint32_t>(mac_[0])
				% static_cast<uint32_t>(mac_[1])
				% static_cast<uint32_t>(mac_[2])
				% static_cast<uint32_t>(mac_[3])
				% static_cast<uint32_t>(mac_[4])
				% static_cast<uint32_t>(mac_[5]);
		}


		//-----------------------------------------------------------------//
		/*
			@brief  EUI デバイスへＩＰ書き込み
			@param[in]	dhcp	DHCP フラグ
			@param[in]	ip		IP 値
		*/
		//-----------------------------------------------------------------//
		void write_eui(bool dhcp, const uint8_t* ip)
		{
			dhcp_ = dhcp;
			ip_[0] = ip[0];
			ip_[1] = ip[1];
			ip_[2] = ip[2];
			ip_[3] = ip[3];
#ifdef SEEDA
			write_eui_();
#endif
		}


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

			auto mount = at_sdc().get_mount();

			http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");

			if(dev) {
				http_format("Develope mode<br>");
				http_format("<hr align=\"left\" width=\"400\" size=\"3\">\n");
			}

			// クライアント機能設定
			http_format("<form method=\"POST\" action=\"/cgi/set_client.cgi\">\n");
			http_format("<table><tr><td>接続先 IP：</td>"
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
			@brief  レンダリング・メイン設定ページ
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

			{  // 内臓 A/D 表示
				float v = static_cast<float>(get_adc(5)) / 4095.0f * 3.3f;
				http_format("バッテリー電圧： %4.2f [V]<br>\n") % v;
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
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			// IP 設定
			{
				http_format("<form method=\"POST\" action=\"/cgi/set_ip.cgi\">\n");
				http_format("<table><tr>"
					   "<td><input type=\"checkbox\" name=\"dhcp\" value=\"on\"%s>ＤＨＣＰ</td>")
						% (dhcp_ ? " checked=\"checked\"" : "");
				for(int i = 0; i < 4; ++i) {
					http_format("<td><input type=\"text\" name=\"ip%d\" size=\"3\" value=\"%d\"></td>")
						% i
						% static_cast<uint32_t>(ip_[i]);
				}
				http_format("<td><input type=\"submit\" value=\"ＩＰ設定\"></td>\n");
				http_format("</table></form>\n");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
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

			auto mount = at_sdc().get_mount();

			// Ａ／Ｄ変換設定
			{
				http_format("<form method=\"POST\" action=\"/cgi/set_adc.cgi\"><table>\n");
				for(int ch = 0; ch < 8; ++ch) {
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
				http_format("<tr><td><input type=\"submit\" value=\"設定\"%s></td></tr>"
						   "</table></form>") % (mount ? "" : " disabled=\"disabled\"");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			{  // ＳＤカードステータス・ボタン
				http_format("<input type=\"button\" onclick=\"location.href='/sdc_state'\""
							" value=\"ＳＤカード情報\"%s>") % (mount ? "" : " disabled=\"disabled\"");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			{  // プリファレンス消去ボタン
				http_format("<input type=\"button\" onclick=\"location.href='/preference'\""
							" value=\"プリファレンス消去\"%s>") % (mount ? "" : " disabled=\"disabled\"");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			{  // クライアント機能設定ボタン
				http_format("<input type=\"button\" onclick=\"location.href='/client'\""
							" value=\"クライアント機能\">");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}

			// ファイル書き込み設定
			{
				http_format("<form method=\"POST\" action=\"/cgi/set_write.cgi\">\n");
				http_format("<table><tr><td>ファイル名(ベース)：</td>");
				if(!write_file_.get_enable()) {
					http_format("<td><input type=\"text\" name=\"fname\" size=\"16\" value=\"%s\"></td></tr>\n")
						% write_file_.get_path();
				} else {
					http_format("<td>%s</td></tr>\n") % write_file_.get_path();
				}
				http_format("<tr><td>書き込み数：</td>");
				if(!write_file_.get_enable()) {
					http_format("<td><input type=\"text\" name=\"count\" size=\"16\" value=\"%d\"></td></tr>\n")
						% write_file_.get_limit();
					http_format("<tr><td><input type=\"submit\" value=\"書き込み開始\"%s></td></tr>")
						% (mount ? "" : " disabled=\"disabled\"");
				} else {
					http_format("<td>%d/%d</td></tr>\n") % write_file_.get_resume() % write_file_.get_limit();
					http_format("<tr><td><input type=\"submit\" value=\"書き込み停止\"%s></td></tr>")
						% (mount ? "" : " disabled=\"disabled\"");
				}
				http_format("</table></form>\n");

				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}
			if(!mount) {
				http_format("ＳＤカードがありません。<br>");
				http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
			}
		}
	};
}
