#pragma once
//=========================================================================//
/*!	@file
	@brief	MAX7219 ドライバー @n
			LED Display Driver (VCC: 4V to 5.5V) @n
			※輝度を大きく設定すると、消費電流が大きくなるので注意が必要。 @n
			※初期化前は、レジスター値が不定なので、大きな消費電流が流れる恐れがある @n
			※デージーチェイン接続した場合のバッファ配置に注意
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MAX7219 テンプレートクラス
		@param[in]	SPI		SPI クラス（出力のみ）
		@param[in]	SELECT	デバイス選択
		@param[in]	CHAIN	デージーチェーン数（通常１）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SPI, class SELECT, uint8_t CHAIN = 1>
	class MAX7219 {

		SPI&		spi_;

		uint8_t		fb_[8 * CHAIN];

		enum class COMMAND : uint8_t {
			NO_OP        = 0x00,
			DIGIT_0      = 0x01,
			DIGIT_1      = 0x02,
			DIGIT_2      = 0x03,
			DIGIT_3      = 0x04,
			DIGIT_4      = 0x05,
			DIGIT_5      = 0x06,
			DIGIT_6      = 0x07,
			DIGIT_7      = 0x08,
			DECODE_MODE  = 0x09,
			INTENSITY    = 0x0A,
			SCAN_LIMIT   = 0x0B,
			SHUTDOWN     = 0x0C,
			DISPLAY_TEST = 0x0F,
		};


		// MAX7212 MSB first, 2 bytes
		void out_(COMMAND cmd, uint8_t dat) noexcept
		{
			SELECT::P = 0;
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(cmd);
			tmp[1] = dat;
			for(uint8_t i = 0; i < CHAIN; ++i) {
				spi_.send(tmp, 2);
			}
			SELECT::P = 1;  // load
		}


		void out_digit_(COMMAND cmd, uint8_t idx) noexcept
		{
			SELECT::P = 0;
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(cmd);
			for(uint8_t i = 0; i < CHAIN; ++i) {
				tmp[1] = fb_[8 * (CHAIN - i - 1) + idx];
				spi_.send(tmp, 2);
			}
			SELECT::P = 1;  // load
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	spi	SPI クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		MAX7219(SPI& spi) noexcept : spi_(spi), fb_{ 0 } { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーなら「false」を返す
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			SELECT::DIR = 1;  // output;
			SELECT::PU  = 0;  // pull-up disable
			SELECT::P = 1;    // LOAD = H

			out_(COMMAND::NO_OP, 0x00);  // ダミー（NOP)
			out_(COMMAND::DISPLAY_TEST, 0x00);  // TEST off
			out_(COMMAND::SHUTDOWN, 0x01);  // ノーマル・モード
			out_(COMMAND::DECODE_MODE, 0x00);  // デコード・モード
			out_(COMMAND::SCAN_LIMIT, 7);  // 表示桁設定

			set_intensity(0);  // 輝度（最低）

			service();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief 輝度の設定
			@param[in]	inten	輝度値（最小：０、最大：１５）
			@return エラー（初期化不良）なら「false」
		 */
		//-----------------------------------------------------------------//
		bool set_intensity(uint8_t inten) noexcept
		{
			out_(COMMAND::INTENSITY, inten);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief サービス @n
				   フレームバッファを転送
		 */
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			auto cmd = COMMAND::DIGIT_0;
			for(uint8_t i = 0; i < 8; ++i) {
				out_digit_(cmd, i);
				cmd = static_cast<COMMAND>(static_cast<uint8_t>(cmd) + 1);					
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief 値の設定
			@param[in]	idx	インデックス
			@param[in]	val	値
		 */
		//-----------------------------------------------------------------//
		void set(uint8_t idx, uint8_t val) noexcept
		{
			if(idx >= (CHAIN * 8)) return;

			fb_[idx] = val;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief 値の取得
			@param[in]	idx	インデックス
			@return 値
		 */
		//-----------------------------------------------------------------//
		uint8_t get(uint8_t idx) const noexcept
		{
			if(idx >= (CHAIN * 8)) return 0;

			return fb_[idx];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief キャラクターの設定
			@param[in]	idx	インデックス
			@param[in]	cha	キャラクターコード
			@param[in]	dp	小数点
		 */
		//-----------------------------------------------------------------//
		void set_cha(uint8_t idx, char cha, bool dp = false) noexcept {
			uint8_t d = 0;
			switch(cha) {
			case ' ':
				break;
			case '-':
				d = 0b0000001;
				break;
			case '_':
				d = 0b0001000;
				break;
			case '~':
				d = 0b1000000;
				break;
			case '0':
				d = 0b1111110;
				break;
			case '1':
				d = 0b0110000;
				break;
			case '2':
				d = 0b1101101;
				break;
			case '3':
				d = 0b1111001;
				break;
			case '4':
				d = 0b0110011;
				break;
			case '5':
				d = 0b1011011;
				break;
			case '6':
				d = 0b1011111;
				break;
			case '7':
				d = 0b1110000;
				break;
			case '8':
				d = 0b1111111;
				break;
			case '9':
				d = 0b1111011;
				break;
			case 'A':
			case 'a':
				d = 0b1110111;
				break;
			case 'B':
			case 'b':
				d = 0b0011111;
				break;
			case 'C':
				d = 0b1001110;
				break;
			case 'c':
				d = 0b0001101;
				break;
			case 'D':
			case 'd':
				d = 0b0111101;
				break;
			case 'E':
			case 'e':
				d = 0b1001111;
				break;
			case 'F':
			case 'f':
				d = 0b1000111;
				break;
			case 'G':
			case 'g':
				d = 0b1011110;
				break;
			case 'H':
			case 'h':
				d = 0b0010111;
				break;
			case 'I':
			case 'i':
				d = 0b0000100;
				break;
			case 'J':
			case 'j':
				d = 0b0111100;
				break;
			case 'K':
			case 'k':
				d = 0b1010111;
				break;
			case 'L':
			case 'l':
				d = 0b0001110;
				break;
			case 'M':
			case 'm':
				d = 0b1110110;
				break;
			case 'N':
			case 'n':
				d = 0b0010101;
				break;
			case 'O':
			case 'o':
				d = 0b0011101;
				break;
			case 'P':
			case 'p':
				d = 0b1100111;
				break;
			case 'Q':
			case 'q':
				d = 0b1101111;
				break;
			case 'R':
			case 'r':
				d = 0b0000101;
				break;
			case 'S':
			case 's':
				d = 0b0011011;
				break;
			case 'T':
			case 't':
				d = 0b0001111;
				break;
			case 'U':
			case 'u':
				d = 0b0011100;
				break;
			case 'V':
			case 'v':
				d = 0b0111110;
				break;
			case 'W':
			case 'w':
				d = 0b0111111;
				break;
			case 'X':
			case 'x':
				d = 0b0110111;
				break;
			case 'Y':
			case 'y':
				d = 0b0111011;
				break;
			case 'Z':
			case 'z':
				d = 0b1101100;
				break;
			default:
				break;
			}
			if(dp) d |= 0x80;
			set(idx, d);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief シフト、バッファ先頭
			@param[in]  fill    埋めるデータ
			@return シフトによりあふれたデータ
		 */
		//-----------------------------------------------------------------//
		uint8_t shift_top(uint8_t fill = 0) noexcept
		{
			uint8_t full = fb_[0];
			std::memmove(&fb_[1], &fb_[0], CHAIN * 8 - 1);
			fb_[0] = fill;
			return full;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief シフト、バッファ終端
			@param[in]  fill    埋めるデータ
			@return シフトによりあふれたデータ
		 */
		//-----------------------------------------------------------------//
		uint8_t shift_end(uint8_t fill = 0) noexcept
		{
			uint8_t full = fb_[CHAIN * 8 - 1];
			std::memmove(&fb_[0], &fb_[1], CHAIN * 8 - 1);
			fb_[CHAIN * 8 - 1] = fill;
			return full;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief [] オペレーター
			@return 参照値
		 */
		//-----------------------------------------------------------------//
		uint8_t& operator [] (uint8_t idx)
		{
			if(idx >= (CHAIN * 8)) {
				idx %= CHAIN * 8;
			}
			return fb_[idx];
		}
	};
}
