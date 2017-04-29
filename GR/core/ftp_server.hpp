#pragma once
//=====================================================================//
/*!	@file
	@brief	FTP server class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstring>
#include "ethernet_server.hpp"

#include "common/time.h"
#include "common/format.hpp"
#include "common/string_utils.hpp"

extern "C" {
	time_t get_time(void);
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
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDC>
	class ftp_server {

		// デバッグ以外で出力を無効にする
		struct null_chaout {
			null_chaout(char* out = nullptr, uint16_t len = 0) { } 
			void operator() (char ch) {
			}
		};
//		typedef utils::basic_format<null_chaout> ftp_debug;
		typedef utils::basic_format<utils::def_chaout> ftp_debug;

		static const uint16_t CTRL_PORT = 21;
		static const uint16_t DATA_PORT = 20;
		static const uint16_t DATA_PORT_PASV = 55600;

		static const ftp_key_t key_tbl_[];

		ethernet&		eth_;

		SDC&			sdc_;

		ethernet_server	ctrl_;
		ethernet_server	data_;

		enum class task {
			connection,
			user_identity,
			password,

			start_pasv,
			data_connection,

			command,

			disconnect,
			disconnect_main,
		};

		task	task_;

		typedef utils::line_manage<1024, 1> LINE_MAN;
		LINE_MAN	line_man_;

		char		user_[16];
		char		pass_[16];

		uint32_t	time_out_;
		uint32_t	delay_loop_;

		const char*	param_;

		ip_address	data_ip_;
		uint16_t	data_port_;

		bool		data_enable_;

		// -------------------------------------------------------------------- //
		typedef utils::basic_format<eth_chaout> format;

		static void disp_time_(time_t t, char* dst, uint32_t size)
		{
			struct tm *m = localtime(&t);
			utils::format("%s %s %d %02d:%02d:%02d  %4d", dst, size)
				% get_wday(m->tm_wday)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec)
				% static_cast<uint32_t>(m->tm_year + 1900);
		}


		// Create string YYYYMMDDHHMMSS
		static void make_date_time_(time_t t, char* dst, uint32_t size)
		{
			struct tm *m = localtime(&t);
		 	utils::format("%04u%02u%02u%02u%02u%02u", dst, size)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% static_cast<uint32_t>(m->tm_mon + 1)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec);
		}


		static void dir_list_func_(const char* name, const FILINFO* fi, bool dir, void* option)
		{
			if(fi == nullptr) return;

			ethernet_server* data = static_cast<ethernet_server*>(option);
			int fd = data->get_cepid();
#if 0
			if(dir) {
				format("+/;", fd);			
			} else {
				format("+r,s%d,\t%s\n", fd) % fi->fsize % name;
			}
#else
			time_t t = utils::str::fatfs_time_to(fi->fdate, fi->ftime);
			char tmp[32];
			make_date_time_(t, tmp, sizeof(tmp));
			format("Type=%s;Size=%d;Modify=%s; %s", data->get_cepid())
				% (dir ? "dir" : "file")
				% fi->fsize
				% tmp
				% name;
			data->service();
#endif
		}


		ftp_command scan_command_(const char* para) {
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


		bool service_line_()
		{
			char tmp[256];
			int len = ctrl_.read(tmp, sizeof(tmp));

			for(int i = 0; i < len; ++i) {
				char ch = tmp[i];
				if(ch == 0 || ch == 0x0d) continue;
				if(!line_man_.add(ch)) {
					utils::format("line_man: memory over\n");
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

			switch(cmd) {

			case ftp_command::ABOR:
#if 0
  //
  //  ABOR - Abort
  //
  else if( ! strcmp( command, "ABOR" ))
  {
    abortTransfer();
    client << "226 Data connection closed" << "\r\n";
  }
#endif
				break;

			case ftp_command::ACCT:
				break;

			case ftp_command::ALLO:
				break;

			case ftp_command::APPE:
				break;

			case ftp_command::CDUP:
#if 0
  //
  //  CDUP - Change to Parent Directory 
  //
  if( ! strcmp( command, "CDUP" ))
  {
    boolean ok = false;
    
    if( strlen( cwdName ) > 1 )            // do nothing if cwdName is root
    {
      // if cwdName ends with '/', remove it (must not append)
      if( cwdName[ strlen( cwdName ) - 1 ] == '/' )
        cwdName[ strlen( cwdName ) - 1 ] = 0;
      // search last '/'
      char * pSep = strrchr( cwdName, '/' );
      ok = pSep > cwdName;
      // if found, ends the string on its position
      if( ok )
      {
        * pSep = 0;
        ok = FAT.exists( cwdName );
      }
    }
    // if an error appends, move to root
    if( ! ok )
      strcpy( cwdName, "/" );
    client << "200 Ok. Current directory is " << cwdName << "\r\n";
  }
#endif
				break;

			case ftp_command::CWD:
				{
// if( strcmp( parameters, "." ) == 0 )  // 'CWD .' is the same as PWD command
// client << "257 \"" << cwdName << "\" is your current directory\r\n";     
					if(sdc_.cd(param_)) {
						format("250 Ok. Current directory is '%s'\n", ctrl_.get_cepid()) % sdc_.get_current();
					} else {
						format("550 Can't change directory to '%s'\n", ctrl_.get_cepid()) % param_;
						ret = false;
					}
				}
				break;

			case ftp_command::DELE:
				if(param_ == nullptr || strlen(param_) == 0) {
					format("501 No file name\n", ctrl_.get_cepid());
					break;
				}
				if(!sdc_.probe(param_)) {
					format("550 File %s not found\n", ctrl_.get_cepid()) % param_;
					break;
				}
				if(sdc_.remove(param_)) {
					format("250 \"%s\" deleted\n", ctrl_.get_cepid()) % param_;
				} else {
					format("450 Can't delete %s\n", ctrl_.get_cepid()) % param_;
				}
				break;

			case ftp_command::HELP:
				break;

			case ftp_command::LIST:
				if(!data_.connected()) {
					format("425 No data connection\n", ctrl_.get_cepid());
					break;
				}
				format("150 Accepted data connection\n", ctrl_.get_cepid());
				if(sdc_.get_mount()) {
					int n = sdc_.dir_loop(sdc_.get_current(), dir_list_func_, true, &data_);
					format("226 %d matches total\n", ctrl_.get_cepid()) % n;
				} else {
					format("550 Can't open directory %s\n", ctrl_.get_cepid()) % sdc_.get_current();
				}
//				data_.stop();
				break;

			case ftp_command::MKD:
				if(param_ == nullptr || strlen(param_) == 0) {
					format("501 No directory name\n", ctrl_.get_cepid());
					break;
				}
				if(sdc_.probe(param_)) {
					format("521 \"%s\" directory already exists\n", ctrl_.get_cepid()) % param_;
					break;
				}
				if(sdc_.mkdir(param_)) {
					format("257 \"%s\" created\n", ctrl_.get_cepid()) % param_;
				} else {
					format("550 Can't create \"%s\"\n", ctrl_.get_cepid()) % param_;
				}
				break;

			case ftp_command::NLST:
				break;

			case ftp_command::NOOP:
				break;

			case ftp_command::MODE:
#if 0
  //
  //  MODE - Transfer Mode 
  //
  else if( ! strcmp( command, "MODE" ))
  {
    if( ! strcmp( parameters, "S" ))
      client << "200 S Ok\r\n";
    // else if( ! strcmp( parameters, "B" ))
    //  client << "200 B Ok\r\n";
    else
      client << "504 Only S(tream) is suported\r\n";
  }
#endif
				break;

			case ftp_command::PASS:
				break;

			case ftp_command::PASV:
				{
					const auto& ip = eth_.get_local_ip();
					format("227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)\n", ctrl_.get_cepid())
						% ip[0] % ip[1] % ip[2] % ip[3] % (DATA_PORT_PASV >> 8) % (DATA_PORT_PASV & 255);
					task_ = task::start_pasv;
				}
				break;

			case ftp_command::PORT:
				int v[6];
				if((utils::input("%d,%d,%d,%d,%d,%d", param_)
					% v[0] % v[1] % v[2] % v[3] % v[4] % v[5]).status()) {
					data_ip_.set(v[0], v[1], v[2], v[3]);
					data_port_ = (v[4] << 8) | v[5];
					utils::format("PORT: '%s' (%d)\n") % data_ip_.c_str() % data_port_;
					format("200 PORT command successful\n", ctrl_.get_cepid());
				} else {
					format("501 PORT parameters NG!\n", ctrl_.get_cepid());
				}
				break;

			case ftp_command::PWD:
			case ftp_command::XPWD:
				format("257 \"%s\" is your current directory\n", ctrl_.get_cepid()) % sdc_.get_current();
				break;

			case ftp_command::QUIT:
				ret = false;
				break;

			case ftp_command::REIN:
				break;

			case ftp_command::REST:
				break;

			case ftp_command::RETR:
				if(param_ == nullptr) {
					format("501 No file name\n", ctrl_.get_cepid());
					ret = false;
					break;
				}
				{
					char path[256+1];
					sdc_.make_full_path(param_, path);
					if(!sdc_.probe(path)) {
						format("550 File '%s' not found\n", ctrl_.get_cepid()) % path;
						ret = false;
						break;
					}
					
#if 0
      else if( ! file.open( path, O_READ ))
        client << "450 Can't open " << parameters << "\r\n";
      else if( ! dataConnect())
        client << "425 No data connection\r\n";
      else
      {
        #ifdef FTP_DEBUG
          Serial << "Sending " << parameters << endl;
        #endif
        client << "150-Connected to port " << dataPort << "\r\n";
        client << "150 " << file.fileSize() << " bytes to download\r\n";
        millisBeginTrans = millis();
        bytesTransfered = 0;
        transferStatus = 1;
      }
    }
#endif
				}
				break;

			case ftp_command::RMD:
				if(param_ == nullptr || strlen(param_) == 0) {
					format("501 No directory name\n", ctrl_.get_cepid());
					break;
				}
				if(!sdc_.probe(param_)) {
					format("550 File %s not found\n", ctrl_.get_cepid()) % param_;
					break;
				}
				if(sdc_.remove(param_)) {
					format("250 \"%s\" deleted\n", ctrl_.get_cepid()) % param_;
				} else {
					format("501 Can't delete %s\n", ctrl_.get_cepid()) % param_;
				}
				break;

			case ftp_command::RNFR:
				break;

			case ftp_command::RNTO:
				break;

			case ftp_command::SITE:
				break;

			case ftp_command::SMNT:
				break;

			case ftp_command::STAT:
				break;

			case ftp_command::STOR:
				break;

			case ftp_command::STOU:
				break;

			case ftp_command::STRU:
#if 0
  //
  //  STRU - File Structure
  //
  else if( ! strcmp( command, "STRU" ))
  {
    if( ! strcmp( parameters, "F" ))
      client << "200 F Ok\r\n";
    // else if( ! strcmp( parameters, "R" ))
    //  client << "200 B Ok\r\n";
    else
      client << "504 Only F(ile) is suported\r\n";
  }
#endif
				break;

			case ftp_command::SYST:
				break;

			case ftp_command::TYPE:
				if(param_ == nullptr) {
					format("504 Unknow TYPE\n", ctrl_.get_cepid());
					ret = false;
				} else if(strcmp(param_, "A") == 0) {
					format("200 TYPE is now ASCII\n", ctrl_.get_cepid());
				} else if(strcmp(param_, "I") == 0) {
			    	format("200 TYPE is now BINARY\n", ctrl_.get_cepid());
				} else {
					format("504 Unknow TYPE\n", ctrl_.get_cepid());
					ret = false;
				}
				break;

			case ftp_command::USER:
				break;

			case ftp_command::FEAT:
				format("211-Extensions suported:\n", ctrl_.get_cepid());
				format(" MDTM\n", ctrl_.get_cepid());
				format(" MLSD\n", ctrl_.get_cepid());
				format(" SIZE\n", ctrl_.get_cepid());
				format(" SITE FREE\n", ctrl_.get_cepid());
				format("211 End.\n", ctrl_.get_cepid());
 				break;

			case ftp_command::MDTM:
#if 0
  //
  //  MDTM - File Modification Time (see RFC 3659)
  //
  else if( ! strcmp( command, "MDTM" ))
  {
    char path[ FTP_CWD_SIZE ];
    char * fname = parameters;
    uint16_t year;
    uint8_t month, day, hour, minute, second, setTime;
    setTime = getDateTime( & year, & month, & day, & hour, & minute, & second );
    // fname point to file name
    fname += setTime;
    if( strlen( fname ) <= 0 )
      client << "501 No file name\r\n";
    else if( makePath( path, fname ))
    {
      if( ! FAT.exists( path ))
        client << "550 No such file " << parameters << "\r\n";
      else if( setTime ) // set file modification time
      {
        if( FAT.timeStamp( path, year, month, day, hour, minute, second ))
          client << "200 Ok\r\n";
        else
          client << "550 Unable to modify time\r\n";
      }
      else // get file modification time
      {
        uint16_t date, time;
        if( FAT.getFileModTime( path, & date, & time ))
        {
          char dtStr[ 15 ];
          client << "213 " << makeDateTimeStr( dtStr, date, time ) << "\r\n";
        }
        else
          client << "550 Unable to retrieve time\r\n";
      }
    }
  }
#endif

			case ftp_command::MLSD:
			    if(!data_.connected()) {
					format("425 No data connection\n", ctrl_.get_cepid());
					ret = false;
				} else {
      				format("150 Accepted data connection\n", ctrl_.get_cepid());

					if(sdc_.get_mount()) {
						int n = sdc_.dir_loop(sdc_.get_current(), dir_list_func_, true, &data_);
						format("226-options: -a -l\n", ctrl_.get_cepid());
						format("226 %d matches total\n", ctrl_.get_cepid()) % n;
					} else {
						format("550 File system not mount\n", ctrl_.get_cepid());
						ret = false;
					}
				}
				break;

			case ftp_command::SIZE:
				if(param_ == nullptr || strlen(param_) == 0) {
					format("501 No file name\n", ctrl_.get_cepid());
					break;
				}
				if(!sdc_.probe(param_)) {
					format("550 No such file %s\n", ctrl_.get_cepid()) % param_;
					break;
				}
				{
					uint32_t sz = sdc_.size(param_);
///					format("450 Can't open %s\n", ctrl_.get_cepid()) % param_;
					format("213 %u\n", ctrl_.get_cepid()) % sz;
				}
				break;

			case ftp_command::NONE_:
				ftp_debug("FTP Server: Fail: '%s'\n") % line_man_[0];
			default:
				break;
			}

			ftp_debug("FTP command: %s, '%s'\n") % line_man_[0] % param_;

			return ret;
		}

#if 0
  ///////////////////////////////////////
  //                                   //
  //        FTP SERVICE COMMANDS       //
  //                                   //
  ///////////////////////////////////////
  //
  //  NLST - Name List 
  //
  else if( ! strcmp( command, "NLST" ))
  {
    if( ! dataConnect())
      client << "425 No data connection\r\n";
    else
    {
      client << "150 Accepted data connection\r\n";
      uint16_t nm = 0;
      FAT_DIR dir;
      if( ! dir.openDir( cwdName ))
        client << "550 Can't open directory " << parameters << "\r\n";
      else
      {
        while( dir.nextFile())
        {
          data << dir.fileName() << "\r\n";
          nm ++;
        }
        client << "226 " << nm << " matches total\r\n";
      }
      data.stop();
    }
  }
  //
  //  NOOP
  //
  else if( ! strcmp( command, "NOOP" ))
  {
    // dataPort = 0;
    client << "200 Zzz...\r\n";
  }
  //
  //  STOR - Store
  //
  else if( ! strcmp( command, "STOR" ))
  {
    char path[ FTP_CWD_SIZE ];
    if( strlen( parameters ) == 0 )
      client << "501 No file name\r\n";
    else if( makePath( path ))
    {
      if( ! file.open( path, O_CREAT | O_WRITE ))
        client << "451 Can't open/create " << parameters << "\r\n";
      else if( ! dataConnect())
      {
        client << "425 No data connection\r\n";
        file.close();
      }
      else
      {
        #ifdef FTP_DEBUG
          Serial << "Receiving " << parameters << endl;
        #endif
        client << "150 Connected to port " << dataPort << "\r\n";
        millisBeginTrans = millis();
        bytesTransfered = 0;
        transferStatus = 2;
      }
    }
  }
  //
  //  RNFR - Rename From 
  //
  else if( ! strcmp( command, "RNFR" ))
  {
    buf[ 0 ] = 0;
    if( strlen( parameters ) == 0 )
      client << "501 No file name\r\n";
    else if( makePath( buf ))
    {
      if( ! FAT.exists( buf ))
        client << "550 File " << parameters << " not found\r\n";
      else
      {
        #ifdef FTP_DEBUG
          Serial << "Renaming " << buf << endl;
        #endif
        client << "350 RNFR accepted - file exists, ready for destination\r\n";     
        rnfrCmd = true;
      }
    }
  }
  //
  //  RNTO - Rename To 
  //
  else if( ! strcmp( command, "RNTO" ))
  {
  Serial << buf << endl;
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

  ///////////////////////////////////////
  //                                   //
  //   EXTENSIONS COMMANDS (RFC 3659)  //
  //                                   //
  ///////////////////////////////////////
  //
  //  SITE - System command
  //
  else if( ! strcmp( command, "SITE" ))
  {
    if( ! strcmp( parameters, "FREE" ))
      client << "200 " << FAT.free() << " MB free of " 
             << FAT.capacity() << " MB capacity\r\n";
    else
      client << "500 Unknow SITE command " << parameters << "\r\n";
  }
  //
  //  Unrecognized commands ...
  //
  else
    client << "500 Unknow command\r\n";
  
  return true;
}
#endif



#if 0
void FtpServer::service()
{
  if((int32_t) ( millisDelay - millis() ) > 0 )
    return;

  if( cmdStatus == 0 )
  {
    if( client.connected())
      disconnectClient();
    cmdStatus = 1;
  }
  else if( cmdStatus == 1 )         // Ftp server waiting for connection
  {
    abortTransfer();
    iniVariables();
    #ifdef FTP_DEBUG
      Serial << "Ftp server waiting for connection on port " << FTP_CTRL_PORT << endl;
    #endif
    cmdStatus = 2;
  }
  else if( cmdStatus == 2 )         // Ftp server idle
  {
    client = ftpServer.connected();
    if( client > 0 )                // A client connected
    {
      clientConnected();      
      millisEndConnection = millis() + 10 * 1000 ; // wait client id during 10 s.
      cmdStatus = 3;
    }
  }
  else if( readChar() > 0 )         // got response
  {
    if( cmdStatus == 3 )            // Ftp server waiting for user identity
      if( userIdentity() )
        cmdStatus = 4;
      else
        cmdStatus = 0;
    else if( cmdStatus == 4 )       // Ftp server waiting for user registration
      if( userPassword() )
      {
        cmdStatus = 5;
        millisEndConnection = millis() + millisTimeOut;
      }
      else
        cmdStatus = 0;
    else if( cmdStatus == 5 )       // Ftp server waiting for user command
      if( ! processCommand())
        cmdStatus = 0;
      else
        millisEndConnection = millis() + millisTimeOut;
  }
  else if( ! client.connected() )
    cmdStatus = 1;

  if( transferStatus == 1 )         // Retrieve data
  {
    if( ! doRetrieve())
      transferStatus = 0;
  }
  else if( transferStatus == 2 )    // Store data
  {
    if( ! doStore())
      transferStatus = 0;
  }
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
		*/
		//-----------------------------------------------------------------//
        ftp_server(ethernet& e, SDC& sdc) : eth_(e), sdc_(sdc), ctrl_(e), data_(e),
			task_(task::connection), line_man_('\n'),
			user_{ "SEEDA03" }, pass_{ "SEEDA03" }, time_out_(0), delay_loop_(0),
			param_(nullptr), data_enable_(false)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			ctrl_.begin(CTRL_PORT);
			task_ = task::connection;
			utils::format("Start FTP Server (CTRL): %s (%d) fd(%d)\n")
				% eth_.get_local_ip().c_str() % ctrl_.get_port() % ctrl_.get_cepid();


//			data_.begin(DATA_PORT_PASV);
#if 0
			data_.begin(DATA_PORT);
			utils::format("Start FTP Server (DATA): %s (%d) fd(%d)\n")
				% eth_.get_local_ip().c_str() % data_.get_port() % data_.get_cepid();
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ミリ秒毎に呼ばれるサービス）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			ctrl_.service();
			data_.service();

			switch(task_) {
			case task::connection:
				if(ctrl_.connected()) {
					ftp_debug("FTP Server (CTRL): connect form: '%s'\n") % ctrl_.get_from_ip().c_str();
					time_t t = get_time();
					char tmp[128];
					disp_time_(t, tmp, sizeof(tmp));
					format("220 %s SEEDA03 FTP server %s\n", ctrl_.get_cepid())
						% eth_.get_local_ip().c_str() % tmp;
					line_man_.clear();
					task_ = task::user_identity;
				}
				break;

			case task::user_identity:
				if(!service_line_()) break;
				if(!line_man_.empty()) {
					ftp_command cmd = scan_command_(line_man_[0]);
					if(cmd == ftp_command::USER) {
						if(strcmp(param_, user_) == 0) {
							ftp_debug("FTP Server: USER OK: '%s'\n") % param_;
							format("331 OK. %s User password required\n", ctrl_.get_cepid()) % param_;
							line_man_.clear();
							task_ = task::password;
						} else {
							ftp_debug("FTP Server: USER NG: '%s'\n") % param_;
							format("530 %s User not found\n", ctrl_.get_cepid()) % param_;
							task_ = task::disconnect;
						}
					} else {
					    format("500 USER Certification Error\n", ctrl_.get_cepid());
						task_ = task::disconnect;
					}
				}
				break;

			case task::password:
				if(!service_line_()) break;
				if(!line_man_.empty()) {
					ftp_command cmd = scan_command_(line_man_[0]);
					if(cmd == ftp_command::PASS) {
						if(strcmp(param_, pass_) == 0) {
							ftp_debug("FTP Server: password OK: '%s'\n") % param_;
							format("230 Login ok %s\n", ctrl_.get_cepid()) % user_;
							line_man_.clear();
							task_ = task::command;
						} else {
							ftp_debug("FTP Server: password NG: '%s'\n") % param_;
							format("530 Password fail %s\n", ctrl_.get_cepid()) % user_;
							task_ = task::disconnect;
						}
					} else {
					    format("500 PASS Certification Error\n", ctrl_.get_cepid());
						task_ = task::disconnect;
					}
				}
				break;

			case task::start_pasv:
				if(!data_enable_) {
					data_.begin(DATA_PORT_PASV);
					utils::format("Start FTP Server (DATA): %s (%d) fd(%d)\n")
						% eth_.get_local_ip().c_str() % data_.get_port() % data_.get_cepid();
					data_enable_ = true;					
					task_ = task::data_connection;
				} else if(!data_.connected()) {
					task_ = task::data_connection;
				} else {
					task_ = task::command;
				}
				break;

			case task::data_connection:
				if(data_.connected()) {
					ftp_debug("FTP Server (DATA): connect form: '%s' (%d)\n")
						% ctrl_.get_from_ip().c_str() % data_.get_port();
					task_ = task::command;
				}
				break;

			case task::command:
				if(!service_line_()) break;
				if(!line_man_.empty()) {
					if(!service_command_()) {
						task_ = task::disconnect;
					}
					line_man_.clear();
				}
				break;

			case task::disconnect:
			default:
				delay_loop_ = 10;
				break;
			case task::disconnect_main:
				if(delay_loop_) {
					--delay_loop_;
				} else {
					ftp_debug("FTP Server (CTRL/DATA): disconnect\n");
					data_.stop();
					ctrl_.stop();
					task_ = task::connection;
				}
				break;
			}
		}
	};

	template<class SDC> const ftp_key_t ftp_server<SDC>::key_tbl_[] = {
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
