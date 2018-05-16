#pragma once
//=====================================================================//
/*!	@file
	@brief	FT5206 Capacitive Touch Panel Controller ドライバー @n
			※この IC の仕様はかなり腐っている、I2C のスレーブアドレス @n
			に内臓レジスター全てをアサインしている為、I2C バスを共有出 @n
			来ない。@n
			又、スレーブアドレス＝内臓レジスターなので、通常の I2C @n
			ドライバーは使えない。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/iica_io.hpp"
#include "common/time.h"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FT5206 テンプレートクラス
		@param[in]	I2C	I2C 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C>
	class FT5206 {

		static const uint8_t	FT5206_ADR = 0x38;

		I2C&	i2c_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c	i2c 制御クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		FT5206(I2C& i2c) : i2c_(i2c) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start() {
//			uint8_t reg[3];
//			reg[0] = 0x07;	/// address
//			reg[1] = 0x00;
//			reg[2] = 0x00;
//			return i2c_.send(DS1371_ADR_, reg, 3);
			return false;
		}

#if 0
	FT5206(uint8_t CTP_INT);
	void 				begin(enum FT5206isr init=INTRL);
	uint8_t 			getTScoordinates(uint16_t (*touch_coordinates)[2], uint8_t *reg);
	void 				getTSregisters(uint8_t *registers);
	bool 				touched();
	uint8_t 			getGesture(uint8_t *reg);
	uint8_t 			getTSflag(uint8_t *reg);
	void 				writeRegister(uint8_t reg,uint8_t val);
	void 				setTouchLimit(uint8_t limit);
	uint8_t 			getTouchLimit(void);
	void 				rearmISR(void);
#endif

	};
}
