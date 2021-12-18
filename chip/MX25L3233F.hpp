#pragma once
//=====================================================================//
/*!	@file
	@brief	MX25L3233F class @n
			Macronix International Co.,Ltd. @n
			3V, 32M-BIT [x 1/x 2/x 4] FLASH MEMORY ドライバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MX25L3233F テンプレートクラス
		@param[in]	QSPI_IO	QSPI 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class QSPI_IO>
	class MX25L3233F {

		QSPI_IO&	qspi_io_;

		enum class CMD : uint8_t {
			READ = 0x03,	// read (4 + n)
			FAST_READ = 0x0B,	// fast read (4 + n)
			READ2 = 0xBB,	// 2 x I/O read
			READD = 0x3B,	// 1l / 2O read
			READ4 = 0xEB,	// 4 x I/O read
			READQ = 0x6B,	// 1l / 4O read

			WREN  = 0x06,	// write enable (1)
		};

		void send_command_(CMD cmd, uint32_t adr) noexcept
		{
			qspi_io_.xchg(static_cast<uint8_t>(cmd));


		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	qspi_io	qspi 制御クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		MX25L3233F(QSPI_IO& qspi_io) noexcept : qspi_io_(qspi_io) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return 正常なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			if(!qspi_io_.start(4'000'000, QSPI_IO::PHASE::MODE0, QSPI_IO::DLEN::W8)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み出し
			@param[in]	adr	読み出しアドレス
			@param[out]	dst	先
			@param[in]	len	長さ
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool read(uint32_t adr, void* dst, uint32_t len) const
		{
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み
			@param[in]	adr	書き込みアドレス
			@param[out]	src	元
			@param[in]	len	長さ
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool write(uint32_t adr, const void* src, uint32_t len) const
		{
			return true;
		}
	};
}
