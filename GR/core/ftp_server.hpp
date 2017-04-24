#pragma once
//=====================================================================//
/*!	@file
	@brief	FTP server class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ethernet_server.hpp"

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
			main,
		};

		task	task_;

		uint32_t	time_out_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
        ftp_server(ethernet& e) : eth_(e), ctrl_(e), data_(e),
			task_(task::connection), time_out_(0)
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

			switch(task_) {
			case task::connection:
				if(ctrl_.connected()) {
					utils::format("new FTP client\n");
					task_ = task::main;
				}
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
