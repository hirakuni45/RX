#pragma once
//=====================================================================//
/*!	@file
	@brief	FTP server class @n
			・SFTP などの暗号化通信は、未サポート @n
			・FFFTP: PASV(有効):OK、PASV(無効):NG @n
			※PASV(無効) では PORT モードで接続するが、ネットワーク @n
			が複数（WiFiやセカンダリーネットワーク）ある機種では、利用 @n
			している IP アドレスを正しく取得しない為、正常に接続できない @n
			ようだ、これは、FFFTP のバグ（仕様）と思える。@n
			・FileZilla: 既定値 (PORT): OK、アクティブ： NG、パッシブ (PASV)： OK @n
			※「アクティブ」の仕様が不明 @n
			・ftp（MSYS2）:（PORT）OK
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdio>
#include <cstring>
#include "ethernet_server.hpp"
#include "ethernet_client.hpp"

#include "common/time.h"
#include "common/format.hpp"
#include "common/string_utils.hpp"

#define FTPS_DEBUG

extern "C" {
	time_t get_time(void);			///< GMT 時間の取得
	unsigned long millis(void);		///< ミリ秒単位の経過時間
};

namespace net {

	enum class ftp_command {
		NONE_,

		// RFC 959
		ABOR,	///< ファイルの転送を中止する。
		ACCT,	///< アカウント情報。引数はユーザアカウントを示す文字列。
		ALLO,	///< ファイルを受け取るために十分なディスクスペースを割り当てる。引数は予約するサイズ。
		APPE,	///< 引数に示したファイルに対して追記する。
		CDUP,	///< 親ディレクトリに移動する。
		CWD,	///< 作業ディレクトリの変更。引数は移動するディレクトリ。
		DELE,	///< ファイルを削除する。引数は削除するファイル。
		HELP,	///< コマンドの一覧。引数を指定するとより詳しいコマンド情報を返す。
		LIST,	///< 引数に指定したファイルの情報やディレクトリの一覧。
					//   指定しない場合、現在のディレクトリの情報を一覧。
		MKD,	///< 引数に指定した名前のディレクトリを作成する。
		NLST,	///< 引数に指定したディレクトリのファイル一覧を返す。
		NOOP,	///< 何もしない。接続維持のためダミーパケットとして使われることがほとんど。
		MODE,	///< 転送モードの設定（ストリーム、ブロック、圧縮）。
		PASS,	///< 認証パスワード。
		PASV,	///< パッシブモードに移行する。
		PORT,	///< サーバが接続すべきポートとアドレスを指定する。
		PWD,	///< 作業ディレクトリを取得する。
		XPWD,	///< 作業ディレクトリを取得する。（拡張）
		QUIT,	///< 接続を終了する。
		REIN,	///< 接続を再初期化する。
		REST,	///< ファイルの転送を指定した箇所から再開する。
		RETR,	///< リモートファイルをダウンロード（Retrieve）する。
		RMD,	///< 引数に指定したディレクトリを削除する。
		RNFR,	///< 引数に指定した名前のファイル（ディレクトリ）をリネームする。
		RNTO,	///< 引数に指定した名前のファイル（ディレクトリ）にリネームする。
		SITE,	///< RFCで定義されていないようなリモートサーバ特有のコマンドを送信する。
		SMNT,	///< ファイル構造をマウントする
		STAT,	///< 現在の状態を取得する。
		STOR,	///< ファイルをアップロード（Stor）する。
		STOU,	///< ファイル名が重複しないようにファイルをアップロードする。
		STRU,	///< 転送するファイルの構造を設定する。
		SYST,	///< システムの種別を返す。
		TYPE,	///< 転送モードを設定する（アスキーモード、バイナリモード）。
		USER,	///< 認証するユーザー名

		// RFC 2389
		FEAT,	///< サーバに実装されている拡張コマンドのリストを取得する。 
		OPTS,	///< 拡張機能の設定。 

		// RFC 3659
		MDTM,	///< 引数に指定したファイルの最終更新時間の詳細を返す。
		MLSD,	///< 引数に指定したディレクトリのファイル一覧を詳細な最終更新時間をつけて返す。
		MLST,	///< 引数に指定したディレクトリの詳細な情報を返す。
		SIZE,	///< ファイルサイズを返す 
	};


	struct ftp_key_t {
		const char*	key;
		ftp_command	cmd;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ftp_server class
		@param[in]	SDC	ＳＤカードファイル操作関係
		@param[in]	RWBSZ	リード／ライト・バッファサイズ（最低５１２）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDC, uint32_t RWBSZ = 2048>
	class ftp_server {

		typedef utils::basic_format<ether_string<ethernet::format_id::ftps_ctrl, 256 > > ctrl_format;
		typedef utils::basic_format<ether_string<ethernet::format_id::ftps_data, 1024> > data_format;

		void ctrl_flush() { ctrl_format::chaout().flush(); }
		void data_flush() { data_format::chaout().flush(); }

		static const uint32_t	login_timeout_    = 30;  ///< 30 sec.
		static const uint32_t	transfer_timeout_ = 10;  ///< 10 sec.
		static const uint32_t	data_connection_timeout_ = 10;  ///< 10 sec.

		// デバッグ以外で出力を無効にする
#ifdef FTPS_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif
		static const uint16_t CTRL_PORT = 21;
		static const uint16_t DATA_PORT = 20;
		static const uint16_t DATA_PORT_PASV = 55600;

		static const ftp_key_t key_tbl_[];

		ethernet&		eth_;

		SDC&			sdc_;

		ethernet_server	ctrl_;
		ethernet_server	data_;
		ethernet_client	port_;

		enum class task {
			begin,
			connection,
			user_identity,
			password,

			start_pasv,
			data_connection,

			start_port,
			port_connection,

			send_file,	///< Server ---> Client
			recv_file,	///< Client ---> Server

			close_port,	///< ポートをクローズ

			recv_rename,	///< Client ---> Server (rename file name)

			command,
			dir_list,
			dir_nlst,
			dir_mlsd,
			dir_loop,

			disconnect,
			disconnect_main,
		};

		task	task_;

		typedef utils::line_manage<1024, 1> LINE_MAN;
		LINE_MAN	line_man_;

		char		host_[16];
		char		user_[16];
		char		pass_[16];
		char		syst_[16];

		uint32_t	time_out_;
		uint32_t	delay_loop_;

		const char*	param_;

		ip_address	data_ip_;
		uint16_t	data_port_;
		uint32_t	data_connect_loop_;

		FILE*		file_fp_;
		uint32_t	file_total_;
		uint32_t	file_frame_;
		uint32_t	file_wait_;

		uint32_t	rw_limit_;

		uint8_t		rw_buff_[RWBSZ];

		uint32_t	elapsed_time_;

		bool		pasv_enable_;

		static void disp_time_(time_t t)
		{
			struct tm *m = gmtime(&t);
			ctrl_format("%s %s %d %02d:%02d:%02d  %4d")
				% get_wday(m->tm_wday)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec)
				% static_cast<uint32_t>(m->tm_year + 1900);
		}


		// Create string YYYYMMDDHHMMSS
		static void make_date_time_(time_t t, char* tmp, uint32_t size)
		{
			struct tm *m = gmtime(&t);
		 	utils::sformat("%04u%02u%02u%02u%02u%02u", tmp, size)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% static_cast<uint32_t>(m->tm_mon + 1)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec);
		}


		static bool parse_YYYYMMDDHHMMSS_(const char* str)
		{
			if(str == nullptr) return false;
			if(strlen(str) != 14) return false;

			char ch;
			while((ch = *str) != 0) {
				if(ch >= '0' && ch <= '9') {
				} else {
					return false;
				}
				++str;
			}

			return true;
		}


		static void dir_nlst_func_(const char* name, const FILINFO* fi, bool dir, void* option)
		{
			if(fi == nullptr) return;

			data_format("%s\n") % name;
		}


		static void dir_list_func_(const char* name, const FILINFO* fi, bool dir, void* option)
		{
			if(fi == nullptr) return;

			char cdir = '-';
			if(dir) {
				cdir = 'd';
			}
			int block = fi->fsize / 512;
			if(block == 0 && fi->fsize > 0) ++block;

			time_t t = utils::str::fatfs_time_to(fi->fdate, fi->ftime);
			struct tm *m = gmtime(&t);
			data_format("%crw-rw-rw- %d user root %d %s %d %02d:%02d %s\n")
				% cdir % block % fi->fsize
				% get_mon(m->tm_mon)
				% static_cast<int>(m->tm_mday)
				% static_cast<int>(m->tm_hour)
				% static_cast<int>(m->tm_min)
				% name;
		}


		static void dir_mlsd_func_(const char* name, const FILINFO* fi, bool dir, void* option)
		{
			if(fi == nullptr) return;

			time_t t = utils::str::fatfs_time_to(fi->fdate, fi->ftime);
			t -= get_timezone_offset();
			char tmp[32];
			make_date_time_(t, tmp, sizeof(tmp));
			data_format("Type=%s;Size=%d;Modify=%s; %s\n")
				% (dir ? "dir" : "file")
				% fi->fsize
				% tmp
				% name;
		}


		ftp_command scan_command_(const char* para)
		{
			const char* term = strchr(para, ' ');
			param_ = nullptr;

			for(const ftp_key_t& t : key_tbl_) {
				if(t.key == nullptr) break;  // end of..

				if(term == nullptr) {
					if(strcmp(t.key, para) == 0) {
						return t.cmd;
					}
				} else {
					uint32_t len = term - para;
					if(len != 3 && len != 4) return ftp_command::NONE_;
					if(strncmp(t.key, para, len) == 0) {
						param_ = term + 1;
						return t.cmd;
					}
				}
			}
			return ftp_command::NONE_;
		}


		void debug_dump_(const char* ptr, int len)
		{
			debug_format("(%d)") % len;
			for(int i = 0; i < len; ++i) {
				char ch = ptr[i];
				if(ch >= 0 && ch < 0x20) {
					debug_format(",%02X ") % static_cast<int>(ch);
				} else {
					debug_format("%c") % ch;
				}
			}
			debug_format("\n");
		}


		bool service_line_()
		{
			char tmp[256];
			int len  = 0;
			if(ctrl_.available() > 0) {	
				len = ctrl_.read(tmp, sizeof(tmp));
				if(len <= 0) return false;
///				debug_dump_(tmp, len);
			} else {
				return false;
			}

			for(int i = 0; i < len; ++i) {
				char ch = tmp[i];
				if(ch == 0 || ch == 0x0d) continue;
				if(!line_man_.add(ch)) {
					debug_format("line_man: memory over\n");
					return false;
				}
			}
			if(static_cast<size_t>(len) < sizeof(tmp)) {
				line_man_.set_term();
				return true;
			}
			return false;
		}


		bool service_command_()
		{
			bool ret = true;

			ftp_command cmd = scan_command_(line_man_[0]);

			bool exec = true;

			switch(cmd) {
			case ftp_command::ABOR:
				ctrl_format("226 Data connection closed\n");
				ctrl_flush();
				task_ = task::disconnect;
				break;

			case ftp_command::ACCT:
			case ftp_command::ALLO:
			case ftp_command::APPE:
				debug_format("Not service: '%s'\n") % line_man_[0];
				exec = false;
				break;

			case ftp_command::CDUP:
				sdc_.cd("..");
				ctrl_format("200 Ok. Current directory is %s\n") % sdc_.get_current();
				ctrl_flush();
				break;

			case ftp_command::CWD:
				{
					if(strcmp(param_, ".") == 0) {
						ctrl_format("257 \"%s\" is your current directory\n") % param_;     
					} else if(sdc_.cd(param_)) {
						debug_format("SDC: Current Path: '%s'\n") % sdc_.get_current();
						ctrl_format("250 Ok. Current directory is '%s'\n") % sdc_.get_current();
					} else {
						ctrl_format("550 Can't change directory to '%s'\n") % param_;
					}
					ctrl_flush();
				}
				break;

			case ftp_command::DELE:
				if(param_ == nullptr || strlen(param_) == 0) {
					ctrl_format("501 No file name\n");
					ctrl_flush();
					break;
				}
#if 0
				if(!sdc_.probe(param_)) {
					ctrl_format("550 File %s not found\n") % param_;
					ctrl_flush();
					break;
				}
#endif
				if(sdc_.remove(param_)) {
					ctrl_format("550 File %s not found\n") % param_;
///					ctrl_format("250 \"%s\" deleted\n") % param_;
				} else {
					ctrl_format("450 Can't delete %s\n") % param_;
				}
				ctrl_flush();
				break;

			case ftp_command::HELP:
				ctrl_format("214 Help list none...\n");
				ctrl_flush();
				break;

			case ftp_command::LIST:
				{
					if(!sdc_.get_mount()) {
						ctrl_format("425 No mount SD-CARD\n");
						ctrl_flush();
						break;
					}
					bool con;
					if(pasv_enable_) {
						con = data_.connected();
					} else {
						con = port_.connected();
					}
					if(!con) {
						ctrl_format("425 No data connection\n");
						ctrl_flush();
						break;
					}
					ctrl_format("150 Accepted data connection\n");
					ctrl_flush();
					task_ = task::dir_list;
				}
				break;

			case ftp_command::MKD:
				if(param_ == nullptr || strlen(param_) == 0) {
					ctrl_format("501 No directory name\n");
					ctrl_flush();
					break;
				}
#if 0
				if(sdc_.probe(param_)) {
					ctrl_format("521 \"%s\" directory already exists\n") % param_;
					ctrl_flush();
					break;
				}
#endif
				if(sdc_.mkdir(param_)) {
					ctrl_format("521 \"%s\" directory already exists\n") % param_;
///					ctrl_format("257 \"%s\" created\n") % param_;
				} else {
					ctrl_format("550 Can't create \"%s\"\n") % param_;
				}
				ctrl_flush();
				break;

			case ftp_command::NLST:
				{
					if(!sdc_.get_mount()) {
						ctrl_format("425 No mount SD-CARD\n");
						ctrl_flush();
						break;
					}
					bool con;
					if(pasv_enable_) {
						con = data_.connected();
					} else {
						con = port_.connected();
					}
					if(!con) {
						ctrl_format("425 No data connection\n");
						ctrl_flush();
						break;
					}
					ctrl_format("150 Accepted data connection\n");
					ctrl_flush();
					task_ = task::dir_nlst;
				}
				break;

			case ftp_command::NOOP:
				ctrl_format("200 ...\n");
				ctrl_flush();
				break;

			case ftp_command::MODE:
#if 0
  {
    if( ! strcmp( parameters, "S" ))
      client << "200 S Ok\r\n";
    // else if( ! strcmp( parameters, "B" ))
    //  client << "200 B Ok\r\n";
    else
      client << "504 Only S(tream) is suported\r\n";
  }
#endif
				debug_format("Not service: '%s'\n") % line_man_[0];
				exec = false;
				break;

			case ftp_command::PASS:
				break;

			case ftp_command::PASV:
				{
					const auto& ip = eth_.get_local_ip();
					ctrl_format("227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)\n")
						% ip[0] % ip[1] % ip[2] % ip[3] % (DATA_PORT_PASV >> 8) % (DATA_PORT_PASV & 255);
					ctrl_flush();
					task_ = task::start_pasv;
				}
				break;

			case ftp_command::PORT:
				int v[6];
				if((utils::input("%d,%d,%d,%d,%d,%d", param_)
					% v[0] % v[1] % v[2] % v[3] % v[4] % v[5]).status()) {
					data_ip_.set(v[0], v[1], v[2], v[3]);
					data_port_ = (v[4] << 8) | v[5];
					debug_format("PORT: '%s' (%d)\n") % data_ip_.c_str() % data_port_;
					ctrl_format("220 PORT command successful\n");
					task_ = task::start_port;
				} else {
					ctrl_format("501 PORT parameters error.\n");
				}
				ctrl_flush();
				break;

			case ftp_command::PWD:
			case ftp_command::XPWD:
				ctrl_format("257 \"%s\" is your current directory\n") % sdc_.get_current();
				ctrl_flush();
				break;

			case ftp_command::QUIT:
				debug_format("FTP Server 'QUIT'\n");
				ret = false;
				break;

			case ftp_command::REIN:
			case ftp_command::REST:
				debug_format("Not service: '%s'\n") % line_man_[0];
				exec = false;
				break;

			case ftp_command::RETR:
				if(param_ == nullptr) {
					ctrl_format("501 No file name\n");
					ctrl_flush();
					task_ = task::close_port;
					break;
				}
				{
					auto t = millis();
					char path[256 + 1];
					sdc_.make_full_path(param_, path);
					file_fp_ = fopen(path, "rb");
					if(file_fp_ == nullptr) {
						ctrl_format("550 File '%s' not found\n") % path;
						ctrl_flush();
						task_ = task::close_port;
						break;
					}
					if(pasv_enable_) {
						ctrl_format("150-Connected to port %d\n") % data_.get_port();
					} else {
						ctrl_format("150-Connected to port %d\n") % port_.get_port();
					}
					ctrl_format("150 download file\n");
					ctrl_flush();
					file_total_ = 0;
					file_frame_ = 0;
					file_wait_ = 0;
					task_ = task::send_file;
					elapsed_time_ = millis() - t;
					debug_format("RETR Read open: '%s' (%d [ms])\n") % path % elapsed_time_;
				}
				break;

			case ftp_command::RMD:
				if(param_ == nullptr || strlen(param_) == 0) {
					ctrl_format("501 No directory name\n");
					ctrl_flush();
					break;
				}
#if 0
				if(!sdc_.probe(param_)) {
					ctrl_format("550 File %s not found\n") % param_;
					ctrl_flush();
					break;
				}
#endif
				if(sdc_.remove(param_)) {
					ctrl_format("550 File %s not found\n") % param_;
///					ctrl_format("250 \"%s\" deleted\n") % param_;
				} else {
					ctrl_format("501 Can't delete %s\n") % param_;
				}
				ctrl_flush();
				break;

			// 引数に指定した名前のファイル（ディレクトリ）をリネームする。
			case ftp_command::RNFR:
				if(param_ == nullptr || strlen(param_) == 0) {
					ctrl_format("501 No file name\n");
					ctrl_flush();
					break;
				}
				if(!sdc_.probe(param_)) {
					ctrl_format("550 File %s not found\n") % param_;
				} else {
					ctrl_format("350 RNFR accepted - file exists, ready for destination\n");     
					task_ = task::recv_rename;
				}
				ctrl_flush();
				break;

			case ftp_command::RNTO:
//				if(param_ == nullptr || strlen(param_) == 0) {
//					format("501 No file name\n", ctrl_.get_cepid());
//				}
#if 0
    char path[ FTP_CWD_SIZE ];
    char dir[ FTP_FIL_SIZE ];
    if( strlen( buf ) == 0 || ! rnfrCmd )
      client << "503 Need RNFR before RNTO\r\n";
    else if( strlen( parameters ) == 0 )
      client << "501 No file name\r\n";
    else if( makePath( path ))
    {
      if( FAT.exists( path ))
        client << "553 " << parameters << " already exists\r\n";
      else
      {
        strcpy( dir, path );
        char * psep = strrchr( dir, '/' );
        boolean fail = psep == NULL;
        if( ! fail )
        {
          if( psep == dir )
            psep ++;
          * psep = 0;
          #if FAT_SYST == 0
            fail = ! file.open( dir ) || ! file.isDir();
            file.close();
          #else
            fail = ! FAT.isDir( dir );
          #endif
          if( fail )
            client << "550 \"" << dir << "\" is not directory\r\n";
          else
          {
            #ifdef FTP_DEBUG
              Serial << "Renaming " << buf << " to " << path << endl;
            #endif
            if( FAT.rename( buf, path ))
              client << "250 File successfully renamed or moved\r\n";
            else
              fail = true;
          }
        }
        if( fail )
          client << "451 Rename/move failure\r\n";
      }
    }
    rnfrCmd = false;
  }
#endif
				debug_format("Not service: '%s'\n") % line_man_[0];
				exec = false;
				break;

			case ftp_command::SITE:
				if(strcmp(param_, "FREE") == 0) {
					uint32_t free;
					uint32_t capa;
					if(sdc_.get_disk_space(free, capa)) {
						ctrl_format("200 %u MB free of %u MB capacity\n")
							% (free / 1024) % (capa / 1024);
					} else {
						ctrl_format("550 disk not available\n") % param_;
					}
				} else {
					ctrl_format("500 Unknow SITE command %s\n") % param_;
				}
				ctrl_flush();
				break;

			case ftp_command::SMNT:
			case ftp_command::STAT:
				debug_format("Not service: '%s'\n") % line_man_[0];
				exec = false;
				break;

			case ftp_command::STOR:
				if(param_ == nullptr) {
					ctrl_format("501 No file name\n");
					ctrl_flush();
					task_ = task::close_port;
					break;
				}
				{
					auto t = millis();
					char path[256 + 1];
					sdc_.make_full_path(param_, path);
					file_fp_ = fopen(path, "wb");
					if(file_fp_ == nullptr) {
						ctrl_format("451 Can't open/create %s\n") % path;
						ctrl_flush();
						task_ = task::close_port;
						break;
					}
					if(pasv_enable_) {
						ctrl_format("150 Connected to port %d\n") % data_.get_port();
					} else {
						ctrl_format("150 Connected to port %d\n") % port_.get_port();
					}
					ctrl_flush();
					file_total_ = 0;
					file_frame_ = 0;
					file_wait_ = 0;
					task_ = task::recv_file;
					elapsed_time_ = millis() - t;
					debug_format("STOR Write open: '%s' (%d [ms])\n") % path % elapsed_time_;
				}
				break;

			case ftp_command::STOU:
				debug_format("Not service: '%s'\n") % line_man_[0];
				exec = false;
				break;

			case ftp_command::STRU:
				if(strcmp(param_, "F") == 0) {
					ctrl_format("200 F Ok\n");
				} else {
					ctrl_format("504 no suport %s\n") % param_;
				}
				ctrl_flush();
				break;

			case ftp_command::SYST:
				ctrl_format("215 %s single task OS.\n") % syst_;
				ctrl_flush();
				break;

			case ftp_command::TYPE:
				if(param_ == nullptr) {
					ctrl_format("504 Unknow TYPE\n");
				} else if(strcmp(param_, "A") == 0) {
					ctrl_format("200 TYPE is now ASCII\n");
				} else if(strcmp(param_, "I") == 0) {
					ctrl_format("200 TYPE is now BINARY\n");
				} else {
					ctrl_format("504 Unknow TYPE\n");
				}
				ctrl_flush();
				break;

			case ftp_command::USER:
				break;

			case ftp_command::FEAT:
				ctrl_format("211-Extensions suported:\n");
				ctrl_format(" MDTM\n");
				ctrl_format(" MLSD\n");
				ctrl_format(" SIZE\n");
				ctrl_format(" SITE FREE\n");
				ctrl_format("211 End.\n");
				ctrl_flush();
 				break;

			case ftp_command::MDTM:
				if(param_ == nullptr || strlen(param_) == 0) {
					ctrl_format("501 No file name\n");
					ctrl_flush();
					break;
				}
				{
					// check Date/Time param
					if(parse_YYYYMMDDHHMMSS_(param_)) {
						ctrl_format("200 Ok\n");
						ctrl_flush();
						break;
					}
					char path[256 + 1];
					sdc_.make_full_path(param_, path);
					if(!sdc_.probe(path)) {
						ctrl_format("550 No such file %s\n") % path;
						ctrl_flush();
						break;
					}
					time_t t = sdc_.get_time(path);
					if(t != 0) {
						struct tm *m = gmtime(&t);
						ctrl_format("213 %04d%02d%02d%02d%02d%02d\n")
							% static_cast<int>(m->tm_year + 1900)
							% static_cast<int>(m->tm_mon + 1)
							% static_cast<int>(m->tm_mday)
							% static_cast<int>(m->tm_hour)
							% static_cast<int>(m->tm_min)
							% static_cast<int>(m->tm_sec);
					} else {
						ctrl_format("550 Unable to retrieve time\n");
						ctrl_flush();
					}
				}
				break;

			case ftp_command::MLSD:
				{
					if(!sdc_.get_mount()) {
						ctrl_format("425 No mount SD-CARD\n");
						ctrl_flush();
						break;
					}
					bool con;
					if(pasv_enable_) {
						con = data_.connected();
					} else {
						con = port_.connected();
					}
				    if(!con) {
						ctrl_format("425 No data connection\n");
						ctrl_flush();
					} else {
						ctrl_format("150 Accepted data connection\n");
						ctrl_flush();
						task_ = task::dir_mlsd;
					}
				}
				break;

			case ftp_command::SIZE:
				if(param_ == nullptr || strlen(param_) == 0) {
					ctrl_format("501 No file name\n");
					ctrl_flush();
					break;
				}
				if(!sdc_.probe(param_)) {
					ctrl_format("550 No such file %s\n") % param_;
					ctrl_flush();
					break;
				}
				{
					uint32_t sz = sdc_.size(param_);
					ctrl_format("213 %u\n") % sz;
					ctrl_flush();
				}
				break;

			case ftp_command::NONE_:
			default:
				exec = false;
				break;
			}

			if(!exec) {
				debug_format("FTP Server: command table search out: '%s'\n") % line_man_[0];
    			ctrl_format("500 Unknow command %s\n") % line_man_[0];
				ctrl_flush();
			}

			debug_format("FTP command: %s, '%s'\n") % line_man_[0] % param_;
			return ret;
		}

#if 0
  else if( cmdStatus > 2 && ! ((int32_t) ( millisEndConnection - millis() ) > 0 ))
  {
    client << "530 Timeout\r\n";
    millisDelay = millis() + 200;    // delay of 200 ms
    cmdStatus = 0;
  }
}
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	e	イーサーネット・コンテキスト
			@param[in]	sdc	SDC コンテキスト
		*/
		//-----------------------------------------------------------------//
        ftp_server(ethernet& e, SDC& sdc) : eth_(e), sdc_(sdc),
			ctrl_(e), data_(e), port_(e, DATA_PORT),
			task_(task::begin), line_man_('\n'),
			user_{ 0 }, pass_{ 0 }, time_out_(0), delay_loop_(0),
			param_(nullptr), data_ip_(), data_port_(0),
			data_connect_loop_(0),
			file_fp_(nullptr), file_total_(0), file_frame_(0), file_wait_(0),
			rw_limit_(RWBSZ),
			elapsed_time_(0),
			pasv_enable_(false)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	host	ホスト名
			@param[in]	syst	システム名
			@param[in]	user	ユーザー名
			@param[in]	pass	パスワード
		*/
		//-----------------------------------------------------------------//
		void start(const char* host, const char* syst, const char* user, const char* pass)
		{
			if(host == nullptr || syst == nullptr || user == nullptr || pass == nullptr) {
				return;
			}
			strncpy(host_, host, sizeof(host_) - 1);
			strncpy(syst_, host, sizeof(syst_) - 1);
			strncpy(user_, user, sizeof(user_) - 1);
			strncpy(pass_, pass, sizeof(pass_) - 1);

			sdc_.set_dir_list_limit(5);

			sdc_.cd("/");

			task_ = task::begin;

			ctrl_format::chaout().set_fd(0);
			data_format::chaout().set_fd(0);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リード・ライト操作リミット
			@param[in]	limit	最大操作サイズ
		*/
		//-----------------------------------------------------------------//
		void set_rw_limit(uint32_t limit = RWBSZ)
		{
			if(limit > RWBSZ) limit = RWBSZ;
			else if(limit < 512) limit = 512;  // 最低サイズ
			rw_limit_ = limit;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	cycle	サービス・サイクル（通常１００Ｈｚ）
		*/
		//-----------------------------------------------------------------//
		void service(uint32_t cycle)
		{
			switch(task_) {
			case task::begin:
				ctrl_.begin(CTRL_PORT);
				debug_format("Start FTP Server (CTRL): %s (%d), fd(%d)\n")
					% eth_.get_local_ip().c_str() % ctrl_.get_port() % ctrl_.get_cepid();
				task_ = task::connection;
				ctrl_format::chaout().set_fd(ctrl_.get_cepid());
				data_.stop();
				port_.stop();
				break;

			case task::connection:
				if(ctrl_.connected()) {
					debug_format("FTP Server (CTRL): connect form: '%s'\n") % ctrl_.get_from_ip().c_str();
					ctrl_format("220 %s FTP server %s ") % host_ % eth_.get_local_ip().c_str();
					time_t t = get_time();
					disp_time_(t);
					ctrl_format("\n");
					ctrl_flush();
					line_man_.clear();
					task_ = task::user_identity;
				}
				break;

			case task::user_identity:
				if(!service_line_()) break;
				if(!line_man_.empty()) {
					ftp_command cmd = scan_command_(line_man_[0]);
					if(cmd == ftp_command::SYST) {
						line_man_.clear();
						ctrl_format("215 %s single task OS.\n") % syst_;
					} else if(cmd == ftp_command::USER) {
						if(strcmp(param_, user_) == 0) {
							debug_format("FTP Server user OK: '%s'\n") % param_;
							ctrl_format("331 OK. %s User password required\n") % param_;
							line_man_.clear();
							task_ = task::password;
						} else {
							debug_format("FTP Server user NG: '%s'\n") % param_;
							ctrl_format("530 %s User not found\n") % param_;
							task_ = task::disconnect;
						}
					} else {
						debug_format("Error: 'task::user_identity', '%s'\n") % line_man_[0];
					    ctrl_format("500 USER Certification Error\n");
						task_ = task::disconnect;
					}
					ctrl_flush();
				}
				break;

			case task::password:
				if(!service_line_()) break;
				if(!line_man_.empty()) {
					ftp_command cmd = scan_command_(line_man_[0]);
					if(cmd == ftp_command::PASS) {
						if(strcmp(param_, pass_) == 0) {
							debug_format("FTP Server password OK: '%s'\n") % param_;
							ctrl_format("230 Login ok %s\n") % user_;
							line_man_.clear();
							task_ = task::command;
						} else {
							debug_format("FTP Server password NG: '%s'\n") % param_;
							ctrl_format("530 Password fail %s\n") % user_;
							task_ = task::disconnect;
						}
					} else {
						debug_format("Error: 'task::password', '%s'\n") % line_man_[0];
					    ctrl_format("500 PASS Certification Error\n");
						task_ = task::disconnect;
					}
					ctrl_flush();
				}
				break;

			case task::start_pasv:
				data_.begin(DATA_PORT_PASV);
				debug_format("Start FTP Server data (PASV): '%s' (%d) fd(%d)\n")
					% eth_.get_local_ip().c_str() % data_.get_port() % data_.get_cepid();
				data_connect_loop_ = data_connection_timeout_ * cycle;
				data_format::chaout().set_fd(data_.get_cepid());
				task_ = task::data_connection;
				pasv_enable_ = true;
				break;

			case task::data_connection:  // PASV
				if(data_connect_loop_) {
					--data_connect_loop_;
				} else {
					ctrl_format("425 No data connection (timeout)\n");
					ctrl_flush();
					task_ = task::command;
				}
				if(data_.connected()) {
					debug_format("Connection FTP Server data (PASV): '%s' %d [ms] (%d)\n")
						% data_.get_from_ip().c_str()
						% static_cast<int>((data_connection_timeout_ * cycle) - data_connect_loop_)
						% data_.get_port();
					task_ = task::command;
					line_man_.clear();
					break;
				}
				break;

			case task::start_port:
				port_.connect(data_ip_, data_port_, TMO_NBLK);
				debug_format("Start FTP Server data (PORT): '%s' (%d) fd(%d)\n")
					% data_ip_.c_str() % data_port_ % port_.get_cepid();
				data_connect_loop_ = data_connection_timeout_ * cycle;
				data_format::chaout().set_fd(port_.get_cepid());
				task_ = task::port_connection;
				break;

			case task::port_connection:  // PORT
				if(data_connect_loop_) {
					--data_connect_loop_;
				} else {
					ctrl_format("425 No data connection (timeout)\n");
					ctrl_flush();
					task_ = task::command;
				}
				if(port_.connected()) {
					debug_format("Connection FTP Server data (PORT): '%s' %d [ms] (%d)\n")
						% port_.get_from_ip().c_str()
						% static_cast<int>((data_connection_timeout_ * cycle) - data_connect_loop_)
						% port_.get_port();
					task_ = task::command;
					line_man_.clear();
					pasv_enable_ = false;
					break;
				}
				break;

			//----  Send File ----------------------//
			case task::send_file:
				{
					auto t = millis();
					uint32_t sz = fread(rw_buff_, 1, rw_limit_, file_fp_);
					if(sz > 0) {
						if(pasv_enable_) {
							data_.write(rw_buff_, sz);
						} else {
							port_.write(rw_buff_, sz);
						}
						file_total_ += sz;
						file_wait_ = 0;
					} else {
						++file_wait_;
					}
					++file_frame_;
					if(sz < rw_limit_) {
						uint32_t krate = file_total_ * cycle / file_frame_ / 1024;
						ctrl_format("226 File successfully transferred (%u KBytes/Sec)\n") % krate;
						ctrl_flush();
						fclose(file_fp_);
						file_fp_ = nullptr;
						if(pasv_enable_) {
							data_.stop();
						} else {
							port_.stop();
						}
						task_ = task::command;
						elapsed_time_ += millis() - t;
						debug_format("Data send %u Bytes, %u Kbytes/Sec (Total: %d [ms])\n")
							% file_total_ % krate % elapsed_time_;
						break;
					}
					if(file_wait_ >= (transfer_timeout_ * cycle)) {
						ctrl_format("421 Data timeout. Reconnect. Sorry\n");
						ctrl_flush();
						fclose(file_fp_);
						file_fp_ = nullptr;
						if(pasv_enable_) {
							data_.stop();
						} else {
							port_.stop();
						}
						elapsed_time_ += millis() - t;
						debug_format("Data send timeout: (%d [ms])\n") % elapsed_time_;
						task_ = task::command;
						break;
					}
					elapsed_time_ += millis() - t;
				}
				break;

			//--------------------------//
			case task::recv_file:
				{
					auto t = millis();
					int32_t sz;
					if(pasv_enable_) {
						sz = data_.read(rw_buff_, rw_limit_);
					} else {
						sz = port_.read(rw_buff_, rw_limit_);
					}
					if(sz > 0) {
						fwrite(rw_buff_, 1, sz, file_fp_);
						file_total_ += sz;
						file_wait_ = 0;
					} else {
						++file_wait_;
					}
					++file_frame_;
					bool con;
					if(pasv_enable_) con = data_.connected();
					else con = port_.connected();
					if(!con || sz < 0) {
						uint32_t krate = file_total_ * cycle / file_frame_ / 1024;
						ctrl_format("226 File successfully transferred (%u KBytes/Sec)\n") % krate;
						ctrl_flush();
						fclose(file_fp_);
						file_fp_ = nullptr;
						if(pasv_enable_) {
							data_.stop();
						} else {
							port_.stop();
						}
						elapsed_time_ += millis() - t;
						debug_format("Data recv %u Bytes, %u Kbytes/Sec (Total: %d [ms])\n")
							% file_total_ % krate % elapsed_time_;
						task_ = task::command;
						break;
					}
					if(file_wait_ >= (transfer_timeout_ * cycle)) {
						ctrl_format("421 Data timeout. Reconnect. Sorry\n");
						ctrl_flush();
						fclose(file_fp_);
						file_fp_ = nullptr;
						if(pasv_enable_) {
							data_.stop();
						} else {
							port_.stop();
						}
						elapsed_time_ += millis() - t;
						debug_format("Data recv timeout: %d [ms]\n") % elapsed_time_;
						task_ = task::command;
						break;
					}
					elapsed_time_ += millis() - t;
				}
				break;

			case task::close_port:
				if(pasv_enable_) {
					data_.stop();
				} else {
					port_.stop();
				}
				task_ = task::command;
				break;

			//--------------------------//
			case task::recv_rename:
				{
					uint8_t tmp[256];
					int32_t rds;
					if(pasv_enable_) {
						rds = data_.read(tmp, sizeof(tmp));
					} else {
						rds = port_.read(tmp, sizeof(tmp));
					}
					if(rds > 0) {

					}
//					if(!data_.connected() || rds < 0) {
//
//					}
				}
				break;

			//--------------------------//
			case task::command:
				if(!ctrl_.connected()) {
					task_ = task::disconnect;
				}
				if(!service_line_()) break;
				if(!line_man_.empty()) {
					if(!service_command_()) {
						task_ = task::disconnect;
					}
					line_man_.clear();
				}
				break;

			case task::dir_list:
				{
					auto t = millis();
					if(!sdc_.start_dir_list("", dir_list_func_, true, nullptr)) {
						ctrl_format("550 Can't open directory %s\n") % sdc_.get_current();
						ctrl_flush();
						task_ = task::command;
						break;
					}
					elapsed_time_ = millis() - t;
					task_ = task::dir_loop;
				}
				break;

			case task::dir_nlst:
				{
					auto t = millis();
					if(!sdc_.start_dir_list("", dir_nlst_func_, true, nullptr)) {
						ctrl_format("550 Can't open directory %s\n") % sdc_.get_current();
						ctrl_flush();
						task_ = task::command;
						break;
					}
					elapsed_time_ = millis() - t;
					task_ = task::dir_loop;
				}
				break;

			case task::dir_mlsd:
				{
					auto t = millis();
					if(!sdc_.start_dir_list("", dir_mlsd_func_, true, nullptr)) {
						ctrl_format("550 Can't open directory %s\n") % sdc_.get_current();
						ctrl_flush();
						task_ = task::command;
						break;
					}
					elapsed_time_ = millis() - t;
					task_ = task::dir_loop;
				}
				break;

			case task::dir_loop:
				{
					uint32_t n;
					if(!sdc_.probe_dir_list(n)) {
						data_flush();
						ctrl_format("226 %d matches total\n") % n;
						ctrl_flush();
						if(pasv_enable_) {
							data_.stop();
						} else {
							port_.stop();
						}
						task_ = task::command;
///						debug_format("DIR loop for (total): %d [ms]\n") % elapsed_time_;
					}
				}
				break;

			case task::disconnect:
			default:
				if(pasv_enable_) {
					data_.stop();
					debug_format("FTP Server data (PASV): disconnect\n");
				} else {
					port_.stop();
					debug_format("FTP Server data (PORT): disconnect\n");
				}
				ctrl_.stop();
				debug_format("FTP Server (CTRL): disconnect\n");
				delay_loop_ = 4;
				task_ = task::disconnect_main;
				break;
			case task::disconnect_main:
				if(delay_loop_) {
					--delay_loop_;
				} else {
					task_ = task::begin;
				}
				break;
			}
		}
	};

	template<class SDC, uint32_t RWBSZ> const ftp_key_t ftp_server<SDC, RWBSZ>::key_tbl_[] = {
		// RFC 959
		{ "ABOR", ftp_command::ABOR },
		{ "ACCT", ftp_command::ACCT },
		{ "ALLO", ftp_command::ALLO },
		{ "APPE", ftp_command::APPE },
		{ "CDUP", ftp_command::CDUP },
		{ "CWD",  ftp_command::CWD  },
		{ "DELE", ftp_command::DELE },
		{ "HELP", ftp_command::HELP },
		{ "LIST", ftp_command::LIST },
		{ "MKD",  ftp_command::MKD  },
		{ "NLST", ftp_command::NLST },
		{ "NOOP", ftp_command::NOOP },
		{ "MODE", ftp_command::MODE },
		{ "PASS", ftp_command::PASS },
		{ "PASV", ftp_command::PASV },
		{ "PORT", ftp_command::PORT },
		{ "PWD",  ftp_command::PWD  },
		{ "QUIT", ftp_command::QUIT },
		{ "REIN", ftp_command::REIN },
		{ "REST", ftp_command::REST },
		{ "RETR", ftp_command::RETR },
		{ "RMD",  ftp_command::RMD  },
		{ "RNFR", ftp_command::RNFR },
		{ "RNTO", ftp_command::RNTO },
		{ "SITE", ftp_command::SITE },
		{ "SMNT", ftp_command::SMNT },
		{ "STAT", ftp_command::STAT },
		{ "STOR", ftp_command::STOR },
		{ "STOU", ftp_command::STOU },
		{ "STRU", ftp_command::STRU },
		{ "SYST", ftp_command::SYST },
		{ "TYPE", ftp_command::TYPE },
		{ "USER", ftp_command::USER },

		// RFC 2389
		{ "FEAT", ftp_command::FEAT },

		// RFC 3659
		{ "MDTM", ftp_command::MDTM },
		{ "MLSD", ftp_command::MLSD },
		{ "MLST", ftp_command::MLST },
		{ "SIZE", ftp_command::SIZE },

		{ "XPWD", ftp_command::XPWD },

		{ nullptr, ftp_command::NONE_ },
	};
}
