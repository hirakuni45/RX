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
		@param[in]	QSPI	QSPI 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class QSPI>
	class MX25L3233F {

		QSPI&	qspi_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	qspi	qspi 制御クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		MX25L3233F(QSPI& qspi) noexcept : qspi_(qspi) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
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
