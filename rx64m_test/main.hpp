#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) メイン
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/rspi_io.hpp"
#include "common/spi_io.hpp"
#include "common/spi_io2.hpp"
#include "common/sdc_io.hpp"
#include "common/command.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/time.h"
#include "common/fixed_fifo.hpp"

#include "chip/LTC2348_16.hpp"
#include "sample.hpp"
#include "preference.hpp"

#include "chip/EUI_XX.hpp"

#include "r_net/http_server.hpp"
#include "r_net/ftp_server.hpp"

#ifdef DEBUG
/// #define CLIENT_DEBUG
#define NETS_DEBUG
#define WRITE_FILE_DEBUG
#endif

namespace seeda {

	static const int seeda_version_ = 519;
	static const uint32_t build_id_ = B_ID;

	typedef utils::command<256> CMD;

#ifdef SEEDA
	typedef device::PORT<device::PORT6, device::bitpos::B7> SW1;
	typedef device::PORT<device::PORT6, device::bitpos::B6> SW2;
#endif

	// Soft SDC 用　SPI 定義（SPI）
#ifdef SEEDA
	typedef device::PORT<device::PORTD, device::bitpos::B6> MISO;
	typedef device::PORT<device::PORTD, device::bitpos::B4> MOSI;
	typedef device::PORT<device::PORTD, device::bitpos::B5> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SPI;

	typedef device::PORT<device::PORTD, device::bitpos::B3> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTE, device::bitpos::B6> SDC_DETECT;	///< カード検出
#else
	// SDC 用　SPI 定義（RSPI）
	typedef device::rspi_io<device::RSPI> SPI;
	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< カード検出
#endif
	typedef utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;

#ifdef SEEDA
	// LTC2348-16 A/D 制御ポート定義
	typedef device::PORT<device::PORT4, device::bitpos::B0> LTC_CSN;   // P40(141)
	typedef device::PORT<device::PORTC, device::bitpos::B6> LTC_CNV;   // PC6(61)
	typedef device::PORT<device::PORTD, device::bitpos::B0> LTC_BUSY;  // PD0/IRQ0(126)
	typedef device::PORT<device::PORT5, device::bitpos::B3> LTC_PD;    // P53(53)
	typedef device::PORT<device::PORT5, device::bitpos::B6> LTC_SDI;   // P56(50)
	typedef device::PORT<device::PORT8, device::bitpos::B6> LTC_SCKO;  // P86(41)
	typedef device::PORT<device::PORT8, device::bitpos::B7> LTC_SCKI;  // P87(39)
	typedef device::PORT<device::PORT2, device::bitpos::B0> LTC_SDO0;  // P20(37)
	typedef device::PORT<device::PORT2, device::bitpos::B1> LTC_SDO2;  // P21(36)
	typedef device::PORT<device::PORT2, device::bitpos::B2> LTC_SDO4;  // P22(35)
	typedef device::PORT<device::PORT2, device::bitpos::B3> LTC_SDO6;  // P23(34)
	typedef struct chip::LTC2348_SDO_t<LTC_SCKO, LTC_SDO0, LTC_SDO2, LTC_SDO4, LTC_SDO6> LTC_SDO;
	typedef chip::LTC2348_16<LTC_CSN, LTC_CNV, LTC_BUSY, LTC_PD, LTC_SDI, LTC_SCKI, LTC_SDO> EADC;
#endif

	typedef net::http_server<SDC, 16, 8192> HTTP;
	typedef HTTP::http_format http_format;	

	typedef net::ftp_server<SDC> FTPS;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ＳＤカード速度構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct sd_speed_t {
		uint32_t	w_open_;
		uint32_t	write_;
		uint32_t	w_close_;
		uint32_t	r_open_;
		uint32_t	read_;
		uint32_t	r_close_;
		uint32_t	dirlist_num_;
		uint32_t	dirlist_;
	};


	//-----------------------------------------------------------------//
	/*!
		@brief  SDC_IO クラスへの参照
		@return SDC_IO クラス
	*/
	//-----------------------------------------------------------------//
	SDC& at_sdc();


	//-----------------------------------------------------------------//
	/*!
		@brief  プリファレンスへの参照
		@return プリファレンス
	*/
	//-----------------------------------------------------------------//
	const preference& get_pre();


	//-----------------------------------------------------------------//
	/*!
		@brief  プリファレンスへの参照
		@return プリファレンス
	*/
	//-----------------------------------------------------------------//
	preference& at_pre();


#ifdef SEEDA
	//-----------------------------------------------------------------//
	/*!
		@brief  EADC クラスへの参照
		@return EADC クラス
	*/
	//-----------------------------------------------------------------//
	EADC& at_eadc();
#endif


	//-----------------------------------------------------------------//
	/*!
		@brief  EADC サーバー
	*/
	//-----------------------------------------------------------------//
	void eadc_server();


	//-----------------------------------------------------------------//
	/*!
		@brief  EADC サーバー許可
		@param[in]	ena	「false」の場合不許可
	*/
	//-----------------------------------------------------------------//
	void enable_eadc_server(bool ena = true);


	//-----------------------------------------------------------------//
	/*!
		@brief  時間の作成
		@param[in]	date	日付
		@param[in]	time	時間
	*/
	//-----------------------------------------------------------------//
	size_t make_time(const char* date, const char* time);


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の設定
		@param[in]	t	GMT 時間
	*/
	//-----------------------------------------------------------------//
	void set_time(time_t t);


	//-----------------------------------------------------------------//
	/*!
		@brief  ウォッチドッグ時間の設定
		@param[in]	limit	時間（１０ミリ秒単位）
		@param[in]	ena		許可
	*/
	//-----------------------------------------------------------------//
	void set_watchdog(uint32_t limit, bool ena);


	//-----------------------------------------------------------------//
	/*!
		@brief  リスタート時間の設定
		@param[in]	rest	リスタート時間（単位１０ミリ秒）
	*/
	//-----------------------------------------------------------------//
	void set_restart_delay(uint32_t rest);


	//-----------------------------------------------------------------//
	/*!
		@brief  駆動時間の取得
		@return 駆動時間
	*/
	//-----------------------------------------------------------------//
	time_t get_operating_time();


	//-----------------------------------------------------------------//
	/*!
		@brief  時間の表示
		@param[in]	t		時間
		@param[in]	dst		出力文字列
		@param[in]	size	文字列の大きさ
		@return 生成された文字列の長さ
	*/
	//-----------------------------------------------------------------//
	int disp_time(time_t t, char* dst, uint32_t size);


	//-----------------------------------------------------------------//
	/*!
		@brief	開発モードの取得 @n
				2: OFF:DEV, ON:通常
		@return 開発モードの場合「true」
	*/
	//-----------------------------------------------------------------//
	bool get_develope()
	{
#ifdef SEEDA
		return SW2::P();
#else
		return true;  // for only develope mode
#endif
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  チャネル数を取得 @n
				1: OFF:CH4, ON:CH8
		@return 設定スイッチの状態
	*/
	//-----------------------------------------------------------------//
	uint32_t get_channel_num()
	{
#ifdef SEEDA
		return SW1::P() ? 4 : 8;
#else
		return 8;  // for only 8 chanels
#endif
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  A/D サンプルの参照
		@param[in]	ch	チャネル（０～７）
		@return A/D サンプル
	*/
	//-----------------------------------------------------------------//
	sample_t& at_sample(uint8_t ch);


	//-----------------------------------------------------------------//
	/*!
		@brief  A/D サンプルの取得
		@return A/D サンプル
	*/
	//-----------------------------------------------------------------//
	const sample_data& get_sample_data();


	//-----------------------------------------------------------------//
	/*!
		@brief  Write File FIFO の RESET
	*/
	//-----------------------------------------------------------------//
	void reset_wf_fifo();


	//-----------------------------------------------------------------//
	/*!
		@brief  Write File FIFO の取得
		@return Write File FIFO
	*/
	//-----------------------------------------------------------------//
	const EADC_FIFO& get_wf_fifo();


	//-----------------------------------------------------------------//
	/*!
		@brief  Write File FIFO の取得
		@return Write File FIFO
	*/
	//-----------------------------------------------------------------//
	EADC_FIFO& at_wf_fifo();


	//-----------------------------------------------------------------//
	/*!
		@brief  Write File のロストを取得（秒）
		@return Write File のロスト
	*/
	//-----------------------------------------------------------------//
	uint32_t get_wf_lost();


	//-----------------------------------------------------------------//
	/*!
		@brief  Write File FIFO の最大値を取得（秒）
		@return Write File FIFO の最大値
	*/
	//-----------------------------------------------------------------//
	uint32_t get_wf_max();


	//-----------------------------------------------------------------//
	/*!
		@brief  内臓 A/D 変換値の取得
		@param[in]	ch	チャネル（５、６、７）
		@return A/D 変換値
	*/
	//-----------------------------------------------------------------//
	uint16_t get_adc(uint32_t ch);


	//-----------------------------------------------------------------//
	/*!
		@brief  ファイル作成テスト
		@param[in]	fname	ファイル名
		@param[in]	size	作成サイズ
		@return 成功なら「true」
	*/
	//-----------------------------------------------------------------//
	bool create_test_file(const char* fname, uint32_t size, sd_speed_t& t);


	//-----------------------------------------------------------------//
	/*!
		@brief  write data
		@return OK: true, NG: false
	*/
	//-----------------------------------------------------------------//
	bool start_write_data(const char* path, uint32_t limit);
}

extern "C" {

	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time();

};
