#pragma once
//=====================================================================//
/*!	@file
	@brief	AD9833 class @n
			ANALOG DEVICES @n
			Interface: SPI, Vcc: 3.3V to 5V
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/R8C/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  AD9833 テンプレートクラス
		@param[in]	SPI	spi クラス
		@param[in]	SEL	デバイス・セレクト(FSYNC)
		@param[in]	REFCLK	リファレンス・クロック（通常25MHz）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SPI, class SEL, uint32_t REFCLK = 25000000>
	class AD9833 {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  レジスター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class REGISTERS : uint8_t {
			REG0,
			REG1,
			SAME_AS_REG0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  波形型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class WAVE_FORM : uint8_t {
			SINE,			///< サイン波
			TRIANGLE,		///< 三角波
			SQUARE,			///< 矩形波
			HALF_SQUARE		///< 半矩形波
		};

	private:
		static const uint32_t POW2_28 = 268435456;		// 2^28 used in frequency word calculation
		static constexpr float BITS_PER_DEG = 11.3777777777778f;	// 4096 / 360

		static const uint16_t RESET_CMD = 0x0100;		// Reset enabled

		static const uint16_t DISABLE_DAC       = 0x0040;
		static const uint16_t DISABLE_INT_CLK   = 0x0080;

		static const uint16_t PHASE1_OUTPUT_REG	= 0x0400;	// Output is based off REG0/REG1
		static const uint16_t FREQ1_OUTPUT_REG  = 0x0800;	// ditto

		static const uint16_t PHASE1_WRITE_REG	= 0x2000;	// Which phase register

		static const uint16_t FREQ0_WRITE_REG   = 0x4000;
		static const uint16_t FREQ1_WRITE_REG   = 0x8000;

		static const uint16_t PHASE_WRITE_CMD	= 0xC000;	// Setup for Phase write

		static const uint16_t SINE_WAVE         = 0x2000;
		static const uint16_t TRIANGLE_WAVE     = 0x2002;
		static const uint16_t SQUARE_WAVE       = 0x2028;
		static const uint16_t HALF_SQUARE_WAVE  = 0x2020;

		SPI&	spi_;

		uint16_t	wave_form0_;
		uint16_t	wave_form1_;

		float		freq0_;
		float		freq1_;
		float		phase0_;
		float		phase1_;

		REGISTERS	active_freq_;
		REGISTERS	active_phase_;

		bool		output_enabled_;
		bool		dac_disabled_;
		bool		int_clk_disabled_;

		void write_(uint16_t cmd)
		{
			SEL::P = 0;	// FSYNC = low
			spi_.xchg(cmd >> 8);
			spi_.xchg(cmd);
			SEL::P = 1;
		}


		void write_ctrl_()
		{
			uint16_t wave_form;

			// TODO: can speed things up by keeping a writeReg0 and writeReg1
			// that presets all bits during the various setup function calls
			// rather than setting flags. Then we could just call WriteRegister
			// directly.
			if(active_freq_ == REGISTERS::REG0) {
				wave_form = wave_form0_;
				wave_form &= ~FREQ1_OUTPUT_REG;
			} else {
				wave_form = wave_form1_;
				wave_form |=  FREQ1_OUTPUT_REG;
			}

			if(active_phase_ == REGISTERS::REG0) {
				wave_form &= ~PHASE1_OUTPUT_REG;
			} else {
				wave_form |=  PHASE1_OUTPUT_REG;
			}

			if(output_enabled_) {
				wave_form &= ~RESET_CMD;
			} else {
				wave_form |=  RESET_CMD;
			}

			if(dac_disabled_) {
				wave_form |=  DISABLE_DAC;
			} else {
				wave_form &= ~DISABLE_DAC;
			}

			if(int_clk_disabled_) {
				wave_form |=  DISABLE_INT_CLK;
			} else {
				wave_form &= ~DISABLE_INT_CLK;
			}
			write_(wave_form);
		}


		uint16_t get_form_(WAVE_FORM form) const
		{
			switch(form) {
			case WAVE_FORM::SINE:
				return SINE_WAVE;
			case WAVE_FORM::TRIANGLE:
				return TRIANGLE_WAVE;
			case WAVE_FORM::SQUARE:
				return SQUARE_WAVE;
			case WAVE_FORM::HALF_SQUARE:
				return HALF_SQUARE_WAVE;
			}
			return 0;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		 */
		//-----------------------------------------------------------------//
		AD9833(SPI& spi) noexcept : spi_(spi),
			wave_form0_(SINE_WAVE), wave_form1_(SINE_WAVE),
			freq0_(1.0f), freq1_(1.0f), phase0_(0.0f), phase1_(0.0f),
			active_freq_(REGISTERS::REG0), active_phase_(REGISTERS::REG0),
			output_enabled_(false), dac_disabled_(false), int_clk_disabled_(false)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start()
		{
			SEL::DIR = 1;  // output
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスをリセットする
		 */
		//-----------------------------------------------------------------//
		void reset()
		{
			write_(RESET_CMD);
			utils::delay::milli_second(10);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	周波数を設定
			@param[in]	regs	レジスター
			@param[in]	freq	周波数（０＜＝１２．５ＭＨｚ）
		 */
		//-----------------------------------------------------------------//
		void set_frequency(REGISTERS regs, float freq)
		{
			if(freq > 12.5e6 ) {
				freq = 12.5e6;
			}
			if(freq < 0.0f) {
				freq = 0.0f;
			}
	
			// Save frequency for use by IncrementFrequency function
			if(regs == REGISTERS::REG0) {
				freq0_ = freq;
			} else {
				freq1_ = freq;
			}

			uint32_t fword = freq * POW2_28 / static_cast<float>(REFCLK);
			uint16_t upper14 = static_cast<uint16_t>((fword & 0x0FFFC000) >> 14);
			uint16_t lower14 = static_cast<uint16_t>( fword & 0x00003FFF);
			uint16_t reg = (regs == REGISTERS::REG0) ? FREQ0_WRITE_REG : FREQ1_WRITE_REG;
			lower14 |= reg;
			upper14 |= reg;   

			write_ctrl_();

			write_(lower14);
			write_(upper14);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フェーズを設定
			@param[in]	regs	レジスター
			@param[in]	phase	フェーズ [0 to 360]
		 */
		//-----------------------------------------------------------------//
		void set_phase(REGISTERS regs, float phase)
		{
			float ph = fmod(phase, 360.0f);
			if(ph < 0.0f) ph += 360.0f;

			// Phase is in float degrees ( 0.0 - 360.0 )
			// Convert to a number 0 to 4096 where 4096 = 0 by masking
			uint16_t phi = static_cast<uint16_t>(BITS_PER_DEG * ph) & 0x0FFF;

			phi |= PHASE_WRITE_CMD;
			// Save phase for use by IncrementPhase function
			if(regs == REGISTERS::REG0)	{
				phase0_ = ph;
			} else {
				phase1_ = ph;
				phi |= PHASE1_WRITE_REG;
			}
			write_(phi);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	波形を設定
			@param[in]	regs	レジスター選択
			@param[in]	form	波形タイプ
		 */
		//-----------------------------------------------------------------//
		void set_waveform(REGISTERS regs, WAVE_FORM form)
		{
			if(regs == REGISTERS::REG0) {
				wave_form0_ = get_form_(form);
			} else {
				wave_form1_ = get_form_(form);
			}
			write_ctrl_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	出力を許可
			@param[in]	ena		無効にする場合「false」
		 */
		//-----------------------------------------------------------------//
		void enable_output(bool ena = true)
		{
			output_enabled_ = ena;
			write_ctrl_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	出力ソースを設定
			@param[in]	fq_regs	周波数レジスタ選択
			@param[in]	ph_regs	フェーズレジスタ選択
		 */
		//-----------------------------------------------------------------//
		void set_output_source(REGISTERS fq_regs, REGISTERS ph_regs)
		{
			active_freq_ = fq_regs;
			if(ph_regs == REGISTERS::SAME_AS_REG0) {
				active_phase_ = active_freq_;
			} else {
				active_phase_ = ph_regs;
			}
			write_ctrl_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	基本設定
			@param[in]	form	波形タイプ
			@param[in]	fq_regs	周波数レジスタ選択 [Hz]
			@param[in]	freq	周波数
			@param[in]	ph_regs	フェーズレジスタ選択 [0 to 360]
			@param[in]	phase	フェーズ
		 */
		//-----------------------------------------------------------------//
		void setup(WAVE_FORM form, REGISTERS fq_regs, float freq, REGISTERS ph_regs, float phase)
		{
			set_frequency(fq_regs, freq);
			set_phase(ph_regs, phase);
			set_waveform(fq_regs, form);
			set_output_source(fq_regs, ph_regs);
		}
	};
}
