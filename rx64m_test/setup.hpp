#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 setup クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "client.hpp"
#include "write_file.hpp"
#include "net_tools.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  setup クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class setup {

		write_file&	write_file_;

		client&		client_;

		typedef utils::basic_format<net::eth_chaout> format;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		setup(write_file& wf, client& cl) : write_file_(wf), client_(cl) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  クライアント機能設定画面
		*/
		//-----------------------------------------------------------------//
		void render_client(int fd)
		{
			net_tools::send_info(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			net_tools::send_head(fd, "SetupClient");

			net_tools::render_version(fd);

			net_tools::render_date_time(fd);

			format("<hr align=\"left\" width=\"400\" size=\"3\">\n", fd);

			// クライアント機能設定
			format("<form method=\"POST\" action=\"/cgi/set_client.cgi\">\n", fd);
			format("<table><tr><td>接続先 IP：</td>"
				"<td><input type=\"text\" name=\"ip\" size=\"15\" value=\"%d.%d.%d.%d\"></td></tr>\n", fd)
				% static_cast<int>(client_.get_ip()[0])
				% static_cast<int>(client_.get_ip()[1])
				% static_cast<int>(client_.get_ip()[2])
				% static_cast<int>(client_.get_ip()[3]);
			format("<tr><td>接続先ポート：</td>"
				"<td><input type=\"text\" name=\"port\" size=\"5\" value=\"%d\"></td></tr>\n", fd)
				% static_cast<int>(client_.get_port());
			format("<tr><td><input type=\"submit\" value=\"接続先設定\"></td></tr>\n", fd);
			format("</table></form>\n", fd);

			format("<hr align=\"left\" width=\"400\" size=\"3\">\n", fd);

			format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定\">\n", fd);
			format("<hr align=\"left\" width=\"400\" size=\"3\">\n", fd);

			format("</html>\n", fd);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  レンダリング・メイン
		*/
		//-----------------------------------------------------------------//
		void render_main(int fd)
		{
			net_tools::send_info(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			net_tools::send_head(fd, "SetupMain");

			net_tools::render_version(fd);

			net_tools::render_date_time(fd);

			format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);

			format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"リロード\">\n", fd);
			format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);

			format("<input type=\"button\" onclick=\"location.href='/data'\" value=\"データ表示\">\n", fd);
			format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);

			{  // 内臓 A/D 表示
				float v = static_cast<float>(get_adc(5)) / 4095.0f * 3.3f;
				format("バックアップ電池電圧： %4.2f [V]<br>\n", fd) % v;
				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}

			// RTC 設定
			{
				format("<form method=\"POST\" action=\"/cgi/set_rtc.cgi\">\n", fd);
				auto t = get_time();
				struct tm *m = localtime(&t);
				format("<table><tr>"
					"<td>年月日(yyyy/mm/dd)：</td>"
					"<td><input type=\"text\" name=\"date\" size=\"10\" value=\"%d/%d/%d\"></td></tr>\n", fd)
					% static_cast<int>(m->tm_year + 1900)
					% static_cast<int>(m->tm_mon + 1) % static_cast<int>(m->tm_mday);
				format("<tr>"
					"<td>時間(hh:mm[:ss])：</td>"
					"<td><input type=\"text\" name=\"time\" size=\"8\" value=\"%d:%d\"></td></tr>\n", fd)
					% static_cast<int>(m->tm_hour) % static_cast<int>(m->tm_min);
				format("<tr><td><input type=\"submit\" value=\"ＲＴＣ設定\"></td></tr>\n", fd);
				format("</table></form>\n", fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}

			// Ａ／Ｄ変換設定
			{
				format("<form method=\"POST\" action=\"/cgi/set_adc.cgi\"><table>\n", fd);
				for(int ch = 0; ch < 8; ++ch) {
					const seeda::sample_t& t = at_sample(ch);
					format("<tr>"
						"<td>CH%d</td>"
						"<td><input type=\"radio\" name=\"mode%d\" value=\"none\"%s>数値</td>"
						"<td><input type=\"radio\" name=\"mode%d\" value=\"real\"%s>係数</td>"
						"<td>ゲイン：</td>"
						"<td><input type=\"text\" name=\"gain%d\" size=\"6\" value=\"%6.2f\"></td>"
						"<td>オフセット：</td>"
						"<td><input type=\"text\" name=\"offset%d\" size=\"6\" value=\"%6.2f\"></td>"
						"<td>下限：</td>"
						"<td><input type=\"text\" name=\"level_lo%d\" size=\"6\" value=\"%d\"></td>"
						"<td>上限：</td>"
						"<td><input type=\"text\" name=\"level_hi%d\" size=\"6\" value=\"%d\"></td>"
						"<td><input type=\"checkbox\" name=\"abs%d\" value=\"on\"%s>絶対値</td>"
						"</tr>\n", fd)
						% ch
						% ch % (t.mode_ == seeda::sample_t::mode::none ? " checked" : "")
						% ch % (t.mode_ == seeda::sample_t::mode::real ? " checked" : "")
						% ch % t.gain_
						% ch % t.offset_
						% ch % static_cast<int>(t.limit_lo_level_)
						% ch % static_cast<int>(t.limit_hi_level_)
						% ch % (t.abs_ ? " checked=\"checked\"" : "");
				}
				format("<tr><td><input type=\"submit\" value=\"設定\"></td></tr>\n", fd);
				format("</table></form>\n", fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}

			{  // ＳＤカード操作画面へのボタン
				format("<input type=\"button\" onclick=\"location.href='/files'\" value=\"ＳＤカード\">\n",
					fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}


			{  // プリファレンス消去ボタン
				format("<input type=\"button\" onclick=\"location.href='/cgi/del_pre.cgi'\" value=\"プリファレンス消去\">\n",
					fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}

			{  // クライアント機能設定ボタン
				format("<input type=\"button\" onclick=\"location.href='/client'\" value=\"クライアント機能\">\n",
					fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}

			{  // ファイル書き込み設定
				format("<form method=\"POST\" action=\"/cgi/set_write.cgi\">\n", fd);
				format("<table><tr><td>ファイル名(ベース)：</td>", fd);
				if(!write_file_.get_enable()) {
					format("<td><input type=\"text\" name=\"fname\" size=\"16\" value=\"%s\"></td></tr>\n", fd)
						% write_file_.get_path();
				} else {
					format("<td>%s</td></tr>\n", fd) % write_file_.get_path();
				}
				format("<tr><td>書き込み数：</td>", fd);
				if(!write_file_.get_enable()) {
					format("<td><input type=\"text\" name=\"count\" size=\"16\" value=\"%d\"></td></tr>\n", fd)
						% write_file_.get_limit();
					format("<tr><td><input type=\"submit\" value=\"書き込み開始\"></td></tr>\n", fd);
				} else {
					format("<td>%d/%d</td></tr>\n", fd) % write_file_.get_resume() % write_file_.get_limit();
					format("<tr><td><input type=\"submit\" value=\"書き込み停止\"></td></tr>\n", fd);
				}
				format("</table></form>\n", fd);

				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}

			format("</html>\n", fd);
		}
	};
}
