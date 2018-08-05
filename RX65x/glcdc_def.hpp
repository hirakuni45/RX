#pragma once
//=====================================================================//
/*!	@file
	@brief	RX65x グループ　GLCDC　制御定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//

namespace device {

	/** Correction Command */
	enum class GLCDC_CORRECTION_CMD {
		SET_ALL,          // All correction setting command.
		BRIGHTNESS,       // Brightness setting command.
		CONTRAST,         // Contrast setting command.
		GAMMA,            // Gamma setting command.
	};


	/** Input format select ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_IN_FORMAT {
		RGB565   = 0,   // Input format RGB565,   16 bits.
		RGB888   = 1,   // Input format RGB888,   32 bits.
		ARGB1555 = 2,   // Input format ARGB1555, 16 bits.
		ARGB4444 = 3,   // Input format ARGB4444, 16 bits.
		ARGB8888 = 4,   // Input format ARGB8888, 32 bits.
		CLUT8    = 5,   // Input format CLUT8,     8 bits.
		CLUT4    = 6,   // Input format CLUT4,     4 bits.
		CLUT1    = 7,   // Input format CLUT1,     1 bits.
	};


	/** Output format select ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_OUT_FORMAT {
		RGB888 = 0,    // Output format RGB888, 24 bits.
		RGB666 = 1,    // Output format RGB666, 18 bits.
		RGB565 = 2,    // Output format RGB565, 16 bits.
		SERIAL = 3     // Output format SERIAL,  8 bits (this function is not supported).
	};


	/** Data endian select ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_ENDIAN
	{
		LITTLE = 0,     // Little endian.
		BIG    = 1,     // Big endian.
	};


	/** RGB color order select ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_COLOR_ORDER
	{
		RGB = 0,         // Color order RGB.
		BGR = 1          // Color order BGR.
	};


	/** Polarity of a signal select ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_SIGNAL_POLARITY
	{
		HIACTIVE = 0,    // High active signal.
		LOACTIVE = 1     // Low active signal.
	};


	/** Signal synchronization edge select ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_SIGNAL_SYNC_EDGE
	{
		RISING = 0,     // Signal is synchronized to rising edge.
		FALLING = 1     // Signal is synchronized to falling edge.
	};


	/** Blending control select */
	enum class GLCDC_BLEND_CONTROL
	{
		NONE    = 0,     // Applying no fading control.
		FADEIN  = 1,     // Applying fade-in control.
		FADEOUT = 2,     // Applying fade-out control.
		FIXED   = 3,     // Applying fixed blend control.
		PIXEL   = 4      // Applying pixel blend control.
	};


	/** Fading status */
	enum class GLCDC_FADE_STATUS
	{
		NOT_UNDERWAY,    // Fade-in/fade-out is not in progress.
		FADING_UNDERWAY, // Fade-in or fade-out is in progress.
		UNCERTAIN        // Fade-in/fade-out status is uncertain just before hardware working.
	};


	/** Clock source select ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_CLK_SRC
	{
		EXTERNAL = 0,    // External clock (LCD_EXTCLK) (this function is not supported).
		INTERNAL = 1     // Internal clock (PLL).
	};


/** Clock frequency division ratio ( Don't change this value, because this value is set to the register ) */
	enum class GLCDC_PANEL_CLK_DIVISOR
	{
		_1  = 1,        // Division Ratio 1/1.
		_2  = 2,        // Division Ratio 1/2.
		_3  = 3,        // Division Ratio 1/3.
		_4  = 4,        // Division Ratio 1/4.
		_5  = 5,        // Division Ratio 1/5.
		_6  = 6,        // Division Ratio 1/6.
		_7  = 7,        // Division Ratio 1/7.
		_8  = 8,        // Division Ratio 1/8.
		_9  = 9,        // Division Ratio 1/9.
		_12 = 12,       // Division Ratio 1/12.
		_16 = 16,       // Division Ratio 1/16.
		_24 = 24,       // Division Ratio 1/24.
		_32 = 32,       // Division Ratio 1/32.
	};


	/** LCD TCON output pin select */
	enum class GLCDC_TCON_PIN
	{
		_0 = 0,         // LCD_TCON0.
		_1 = 1,         // LCD_TCON1.
		_2 = 2,         // LCD_TCON2.
		_3 = 3          // LCD_TCON3.
	};


}


/** Correction circuit sequence control select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_correction_proc_order
{
    GLCDC_BRIGHTNESS_CONTRAST_TO_GAMMA = 0, // Brightness, contrast -> gamma correction.
    GLCDC_GAMMA_TO_BRIGHTNESS_CONTRAST = 1  // Gamma correction -> brightness, contrast.
} glcdc_correction_proc_order_t;

/** Dithering mode select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_dithering_mode
{
    GLCDC_DITHERING_MODE_TRUNCATE   = 0,   // No dithering (truncate).
    GLCDC_DITHERING_MODE_ROUND_OFF  = 1,   // Dithering with round off.
    GLCDC_DITHERING_MODE_2X2PATTERN = 2    // Dithering with 2x2 pattern.
} glcdc_dithering_mode_t;

/** Dithering 2x2 pattern ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_dithering_pattern
{
    GLCDC_DITHERING_PATTERN_00 = 0,        // 2x2 pattern '00'.
    GLCDC_DITHERING_PATTERN_01 = 1,        // 2x2 pattern '01'.
    GLCDC_DITHERING_PATTERN_10 = 2,        // 2x2 pattern '10'.
    GLCDC_DITHERING_PATTERN_11 = 3         // 2x2 pattern '11'.
} glcdc_dithering_pattern_t;

