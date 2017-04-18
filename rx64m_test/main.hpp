#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/rspi_io.hpp"
#include "common/spi_io.hpp"
#include "common/sdc_io.hpp"
#include "common/command.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/time.h"

#include "chip/LTC2348_16.hpp"

#include "sample.hpp"

namespace seeda {

	typedef utils::command<256> CMD;

	typedef device::PORT<device::PORT6, device::bitpos::B7> SW1;
	typedef device::PORT<device::PORT6, device::bitpos::B6> SW2;

	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTD, device::bitpos::B6> MISO;
	typedef device::PORT<device::PORTD, device::bitpos::B4> MOSI;
	typedef device::PORT<device::PORTD, device::bitpos::B5> SPCK;
	typedef device::spi_io<MISO, MOSI, SPCK> SPI;

	typedef device::PORT<device::PORTD, device::bitpos::B3> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTE, device::bitpos::B6> SDC_DETECT;	///< カード検出

	typedef utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;


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


	//-----------------------------------------------------------------//
	/*!
		@brief  SDC_IO クラスへの参照
		@return SDC_IO クラス
	*/
	//-----------------------------------------------------------------//
	SDC& at_sdc();


	//-----------------------------------------------------------------//
	/*!
		@brief  EADC クラスへの参照
		@return EADC クラス
	*/
	//-----------------------------------------------------------------//
	EADC& at_eadc();


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
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time();


	//-----------------------------------------------------------------//
	/*!
		@brief  時間の表示
		@param[in]	t		時間
		@param[in]	dst		出力文字列
		@param[in]	size	文字列の大きさ
	*/
	//-----------------------------------------------------------------//
	void disp_time(time_t t, char* dst = nullptr, uint32_t size = 0);


	//-----------------------------------------------------------------//
	/*!
		@brief  設定スイッチの状態を取得
		@return 設定スイッチの状態
	*/
	//-----------------------------------------------------------------//
	uint8_t get_switch()
	{
		return static_cast<uint8_t>(!SW1::P()) | (static_cast<uint8_t>(!SW2::P()) << 1);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  A/D サンプルの設定
		@param[in]	ch	チャネル（０～７）
		@param[in]	t	サンプル構造体
	*/
	//-----------------------------------------------------------------//
	void set_sample(uint8_t ch, const sample_t& t);


	//-----------------------------------------------------------------//
	/*!
		@brief  A/D サンプルの取得
		@param[in]	ch	チャネル（０～７）
		@return A/D サンプル
	*/
	//-----------------------------------------------------------------//
	const sample_t& get_sample(uint8_t ch);
}
