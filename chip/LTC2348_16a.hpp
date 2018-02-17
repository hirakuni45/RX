#pragma once
//=====================================================================//
/*!	@file
	@brief	LTC2348-16a ドライバー @n
			LTC2348/16 bits A/D コンバーター
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/delay.hpp"
#include "common/format.hpp"

/// F_ICLK は速度パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_ICLK
#  error "LTC2348_16a.hpp requires F_ICLK to be defined"
#endif

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  LTC2348-16 テンプレートクラス @n
				※PD パワーダウン制御は０で使う事（1: PowerDown）@n
				※SCKO は使わない
		@param[in]	CSN		デバイス選択
		@param[in]	CNV		コンバート制御
		@param[in]	BUSY	ビジー信号
		@param[in]	SPI		SPI チャネル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CSN, class CNV, class BUSY, class SPI>
	class LTC2348_16a {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフト・スパン種別 @n
					Internal VREFBUF: 4.096V
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class span_type : uint8_t {
			DISABLE,  		///< 000, Chanel Disable
			P5_12,			///< 001, 1.25 * VREFBUF          (+0      to +5.12V)
			M5P5,			///< 010, 2.5  * VREFBUF / 1.024  (-5V     to +5V)
			P5_12M5_12,		///< 011, 2.5  * VREFBUF          (-5.12V  to +5.12V)
			P10,			///< 100, 2.5  * VREFBUF / 1.024  (+0      to +10V)
			P10_24,			///< 101, 2.5  * VREFBUF          (+0      to +10.24V)
			M10P10,			///< 110, 5.0  * VREFBUF / 1.024  (-10V    to +10V)
			M10_24P10_24,	///< 111, 5.0  * VREFBUF          (-10.24V to +10.24V)
		};

	private:
		SPI			spi_;

		uint32_t	span_;

///		uint32_t	data_[8];
		uint16_t	data_[2];

		uint16_t	busy_loop_;
		uint16_t	cnv_loop_;

		bool		device_;

#if 0
		void get_data_loop_(uint32_t ofs, uint32_t span)
		{
			SDI::P = 0;
			uint32_t mask = 0x00800000;
			uint32_t d0 = 0;
			while(mask > 0) {
				d0 <<= 1;
				d0 |= SDO0::P();

				SCKI::P = 0;

				SDI::P = span & mask;
				mask >>= 1;

				SCKI::P = 1;
			}
			data_[0 + ofs] = d0;
		}
#endif

		inline uint16_t get_data_loop_(uint32_t span)
		{
#if 0
			uint8_t a = spi_.xchg(span >> 16);
			uint8_t b = spi_.xchg(span >> 8);
			spi_.xchg(span);
			return (static_cast<uint16_t>(a) << 8) | static_cast<uint16_t>(b); 
#else
			return spi_.xchg32(span) >> 8;
#endif
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		LTC2348_16a() : span_(0), busy_loop_(0), cnv_loop_(0), device_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスの開始 @n
					制御線を初期化して、デバイスのゆ有無を確認
			@param[in]	speed	制御クロック速度（ソフトループなので正確ではない）
			@param[in]	span	変換スパン種別（全てのチャネルに同一のスパンが設定される）
			@return デバイスが有効なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t speed, span_type span)
		{
#if 0
			{
				uint32_t cnt = static_cast<uint32_t>(F_ICLK) / speed;
				float a = static_cast<float>(cnt);
				a /= 10.974f;
				cnt = static_cast<uint32_t>(a);
				if(cnt > 65535) return false;
				clk_loop_ = cnt;
			}
#endif
			{  // BUSY loop 200ns (5MHz)
				uint32_t cnt = static_cast<uint32_t>(F_ICLK) / 5000000;
				if(cnt > 65535) return false;
				busy_loop_ = cnt;
			}
			{  // tCONV: 500ns/ch 200ksps
				uint32_t cnt = static_cast<uint32_t>(F_ICLK) / 200000;
				if(cnt > 65535) return false;
				cnv_loop_ = cnt * 2;
			}

			uint32_t ss = 0;
//			for(int i = 0; i < 8; ++i) {
			for(int i = 0; i < 2; ++i) {
				ss <<= 3;
				ss |= static_cast<uint32_t>(span);
			}
			span_ = ss;

			CSN::DIR  = 1;
			CSN::P    = 1;
			CNV::DIR  = 1;
			CNV::P    = 0;
			BUSY::DIR = 0;

			uint8_t int_level = 0;
			if(!spi_.start(59375000, SPI::PHASE::TYPE1, SPI::DLEN::W24, int_level)) {
				utils::format("Fail EADC SPI...\n");
			}

			utils::delay::milli_second(1);
			device_ = convert();

			return device_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスの応答確認
			@return デバイスが接続されている場合「true」
		*/
		//-----------------------------------------------------------------//
		bool probe() const {
			return device_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルにスパン種別を設定
			@param[in]	ch		チャネル
			@param[in]	span	スパン種別
		*/
		//-----------------------------------------------------------------//
		void set_span(uint8_t ch, span_type span)
		{
			span_ &= ~(0b111 << (ch * 3));
			span_ |= static_cast<uint32_t>(span) << (ch * 3);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルのスパン種別を取得
			@param[in]	ch		チャネル
			@return スパン種別
		*/
		//-----------------------------------------------------------------//
		span_type get_span(uint8_t ch) const
		{
			return static_cast<span_type>((span_ >> (ch * 3)) & 0b111);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  変換を開始
			@return 変換正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool convert()
		{
			CNV::P = 0;

			CSN::P = 0;
			data_[0] = get_data_loop_(span_);
			data_[1] = get_data_loop_(0x000000);
			CSN::P = 1;

			CNV::P = 1;  // 変換開始

			return true;
		}

		// convert first step
		inline void convert_0()
		{
			CNV::P = 0;
			CSN::P = 0;
			spi_.xchg32_start(span_);
		}

		inline uint16_t convert_1()
		{
			uint16_t data = spi_.xchg32_sync() >> 8;
			spi_.xchg32_start(0x00000000);
			return data;
		}


		inline uint16_t convert_2()
		{
			uint16_t data = spi_.xchg32_sync() >> 8;
			CSN::P = 1;
			CNV::P = 1;  // 変換開始
			return data;
		}

#if 0
		// convert final step
		inline uint16_t convert1()
		{
			uint16_t d = get_data_loop_(0x000000);
			CSN::P = 1;
			CNV::P = 1;  // 変換開始
			return d;
		}
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief  Ａ／Ｄ変換値を取得（０～６５５３５）
			@param[in]	ch	チャネル（０～１）
			@return 変換値
		*/
		//-----------------------------------------------------------------//
		uint16_t get_value(uint8_t ch) const {
			return data_[ch & 1];
		}


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  変換データ（２４ビット生データ）を取得
			@param[in]	ch	チャネル（０～７）
			@return 変換値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_data(uint8_t ch) const {
			return data_[ch & 7];
		}
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief  変換電圧に変換して取得
			@param[in]	ch	チャネル（０～７）
			@return 変換電圧
		*/
		//-----------------------------------------------------------------//
		float get_voltage(uint8_t ch) const {
			uint32_t span = (span_ >> (ch * 3)) & 7;
			float ofs = 0.0f;
			if(span == 2 || span == 3 || span == 6 || span == 7) {
				ofs = 0.5f;
			}
			static const float gain[8] = { 0.0f, 5.12f, 5.0f, 5.12f, 10.0f, 10.24f, 10.0f, 10.24f };
			return ((static_cast<float>(data_[ch & 7] >> 8) / 65535.0f) - ofs) * gain[span];
		}
	};
}
