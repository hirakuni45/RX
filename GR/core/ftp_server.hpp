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

extern "C" {
	time_t get_time(void);
};

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ftp_server class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ftp_server {

		static const uint16_t CTRL_PORT = 21;
		static const uint16_t DATA_PORT = 20;
		static const uint16_t DATA_PORT_PASV = 55600;

		ethernet&		eth_;
		ethernet_server	ctrl_;
		ethernet_server	data_;

		enum class task {
			connection,
			user_name,
			password,
			main,
		};

		task	task_;

		typedef utils::line_manage<512, 1> LINE_MAN;
		LINE_MAN	line_man_;

		uint32_t	time_out_;

#if 0
boolean FtpServer::userIdentity()
{
  if( strcmp( command, "USER" ))
    client << "500 Syntax error\r\n";
  if( strcmp( parameters, FTP_USER ))
    client << "530 \r\n";
  else
  {
    client << "331 OK. Password required\r\n";
    strcpy( cwdName, "/" );
    return true;
  }
  millisDelay = millis() + 100;  // delay of 100 ms
  return false;
}
#endif

		bool command_service_()
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


		void disp_time_(time_t t, char* dst, uint32_t size)
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


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
        ftp_server(ethernet& e) : eth_(e), ctrl_(e), data_(e),
			task_(task::connection), line_man_('\n'), time_out_(0)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			ctrl_.begin(CTRL_PORT);
			data_.begin(DATA_PORT);
			task_ = task::connection;
			utils::format("Start FTP Server (CTRL): %s (%d)\n")
				% eth_.get_local_ip().c_str() % ctrl_.get_port();
			utils::format("Start FTP Server (DATA): %s (%d)\n")
				% eth_.get_local_ip().c_str() % data_.get_port();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ミリ秒毎に呼ばれるサービス）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			ctrl_.service();

			switch(task_) {
			case task::connection:
				if(ctrl_.connected()) {
					utils::format("new FTP client form: %s\n") % ctrl_.get_from_ip().c_str();
					char tmp[64];
					utils::format("220 %s SEEDA03 FTP server ", tmp, sizeof(tmp))
						% eth_.get_local_ip().c_str();
					ctrl_.print(tmp);
					time_t t = get_time();
					disp_time_(t, tmp, sizeof(tmp));
					ctrl_.println(tmp);
					task_ = task::user_name;
					line_man_.clear();
				}
				break;

			case task::user_name:
				if(command_service_()) {
					if(!line_man_.empty()) {
//						const auto& t = line_man_[0];
//						if(strcmp(t, "USER") == 0) {
//							
//						}
					}
				}
				break;

			case task::password:
				break;

			case task::main:


				break;
			}

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

		}
	};
}
