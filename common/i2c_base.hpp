#pragma once
//=========================================================================//
/*!	@file
	@brief	I2C 制御ベースクラス @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>
#include <functional>
#include "common/format.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I2C base クラス（iica_io、si2c_io、sci_i2c_io 共通）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct i2c_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信、受信関数型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef std::function<void(void)> FUNC_TYPE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  速度タイプ型 @n
					※簡易 I2C では誤差が大きい。 @n
					※設定出来ない速度では、初期化で失敗する。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED : uint32_t {
			_50K      =    50'000,	///<  50K b.p.s.
			STANDARD  =   100'000,	///< 100K b.p.s. (Standard mode)
			_100K     =   100'000,
			_150K     =   150'000,	///< 150K b.p.s.
			_200K     =   200'000,	///< 200K b.p.s.
			_250K     =   250'000,	///< 250K b.p.s.
			_300K     =   300'000,	///< 300K b.p.s.
			_350K     =   350'000,	///< 350K b.p.s.
			FAST      =   400'000,	///< 400K b.p.s. (Fast mode) 60MHz では、対応していません。
            FAST_PLUS = 1'000'000   ///<   1M b.p.s.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作モード
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MODE : uint8_t {
            MASTER,       ///< マスターモード
            SLAVE,        ///< スレーブモード
        };


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C のエラー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		#ifdef ERROR
		#undef ERROR
		#endif
		enum class ERROR : uint8_t {
			NONE,		///< エラー無し
			START,		///< スタート（初期化）
			BUS_OPEN,	///< バス・オープン
			ADDRESS,	///< アドレス転送
            ACK,        ///< ACK エラー
			SEND_DATA,	///< 送信データ転送
			RECV_DATA,	///< 受信データ転送
			STOP,		///< ストップ・コンディション
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C のエラー表示
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static void ListError(ERROR err) noexcept
		{
			switch(err) {
			case ERROR::START:
				utils::format("I2C Fail: Start\n");
				break;
			case ERROR::BUS_OPEN:
				utils::format("I2C Fail: BUS Open\n");
				break;
			case ERROR::ADDRESS:
				utils::format("I2C Fail: Address\n");
				break;
			case ERROR::ACK:
				utils::format("I2C Fail: ACK\n");
				break;
			case ERROR::SEND_DATA:
				utils::format("I2C Fail: Send data\n");
				break;
			case ERROR::RECV_DATA:
				utils::format("I2C Fail: Recv data\n");
				break;
			case ERROR::STOP:
				utils::format("I2C Fail: Stop\n");
				break;
			default:
				break;
			}
		}
    };
}
