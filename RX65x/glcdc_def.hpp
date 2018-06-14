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

/**********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/** Correction Command */
typedef enum e_glcdc_correction_cmd
{
    GLCDC_CORRECTION_CMD_SET_ALL,          // All correction setting command.
    GLCDC_CORRECTION_CMD_BRIGHTNESS,       // Brightness setting command.
    GLCDC_CORRECTION_CMD_CONTRAST,         // Contrast setting command.
    GLCDC_CORRECTION_CMD_GAMMA,            // Gamma setting command.
} glcdc_correction_cmd_t;


/** Input format select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_in_format
{
    GLCDC_IN_FORMAT_16BITS_RGB565   = 0,   // Input format RGB565,   16 bits.
    GLCDC_IN_FORMAT_32BITS_RGB888   = 1,   // Input format RGB888,   32 bits.
    GLCDC_IN_FORMAT_16BITS_ARGB1555 = 2,   // Input format ARGB1555, 16 bits.
    GLCDC_IN_FORMAT_16BITS_ARGB4444 = 3,   // Input format ARGB4444, 16 bits.
    GLCDC_IN_FORMAT_32BITS_ARGB8888 = 4,   // Input format ARGB8888, 32 bits.
    GLCDC_IN_FORMAT_CLUT8           = 5,   // Input format CLUT8,     8 bits.
    GLCDC_IN_FORMAT_CLUT4           = 6,   // Input format CLUT4,     4 bits.
    GLCDC_IN_FORMAT_CLUT1           = 7,   // Input format CLUT1,     1 bits.
} glcdc_in_format_t;

/** Output format select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_out_format
{
    GLCDC_OUT_FORMAT_24BITS_RGB888 = 0,    // Output format RGB888, 24 bits.
    GLCDC_OUT_FORMAT_18BITS_RGB666 = 1,    // Output format RGB666, 18 bits.
    GLCDC_OUT_FORMAT_16BITS_RGB565 = 2,    // Output format RGB565, 16 bits.
    GLCDC_OUT_FORMAT_8BITS_SERIAL  = 3     // Output format SERIAL,  8 bits (this function is not supported).
} glcdc_out_format_t;

/** Data endian select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_endian
{
    GLCDC_ENDIAN_LITTLE = 0,               // Little endian.
    GLCDC_ENDIAN_BIG    = 1,               // Big endian.
} glcdc_endian_t;

/** RGB color order select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_color_order
{
    GLCDC_COLOR_ORDER_RGB = 0,             // Color order RGB.
    GLCDC_COLOR_ORDER_BGR = 1              // Color order BGR.
} glcdc_color_order_t;

/** Polarity of a signal select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_signal_polarity
{
    GLCDC_SIGNAL_POLARITY_HIACTIVE = 0,    // High active signal.
    GLCDC_SIGNAL_POLARITY_LOACTIVE = 1     // Low active signal.
} glcdc_signal_polarity_t;

/** Signal synchronization edge select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_sync_edge
{
    GLCDC_SIGNAL_SYNC_EDGE_RISING = 0,     // Signal is synchronized to rising edge.
    GLCDC_SIGNAL_SYNC_EDGE_FALLING = 1     // Signal is synchronized to falling edge.
} glcdc_sync_edge_t;

/** Blending control select */
typedef enum e_glcdc_blend_control
{
    GLCDC_BLEND_CONTROL_NONE = 0,          // Applying no fading control.
    GLCDC_BLEND_CONTROL_FADEIN = 1,        // Applying fade-in control.
    GLCDC_BLEND_CONTROL_FADEOUT = 2,       // Applying fade-out control.
    GLCDC_BLEND_CONTROL_FIXED = 3,         // Applying fixed blend control.
    GLCDC_BLEND_CONTROL_PIXEL = 4          // Applying pixel blend control.
} glcdc_blend_control_t;

/** Fading status */
typedef enum e_glcdc_fade_status
{
    GLCDC_FADE_STATUS_NOT_UNDERWAY,        // Fade-in/fade-out is not in progress.
    GLCDC_FADE_STATUS_FADING_UNDERWAY,     // Fade-in or fade-out is in progress.
    GLCDC_FADE_STATUS_UNCERTAIN            // Fade-in/fade-out status is uncertain just before hardware working.
} glcdc_fade_status_t;

/** Clock source select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_clk_src
{
    GLCDC_CLK_SRC_EXTERNAL = 0,            // External clock (LCD_EXTCLK) (this function is not supported).
    GLCDC_CLK_SRC_INTERNAL = 1             // Internal clock (PLL).
} glcdc_clk_src_t;

/** Clock frequency division ratio ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_panel_clk_div
{
    GLCDC_PANEL_CLK_DIVISOR_1  = 1,        // Division Ratio 1/1.
    GLCDC_PANEL_CLK_DIVISOR_2  = 2,        // Division Ratio 1/2.
    GLCDC_PANEL_CLK_DIVISOR_3  = 3,        // Division Ratio 1/3.
    GLCDC_PANEL_CLK_DIVISOR_4  = 4,        // Division Ratio 1/4.
    GLCDC_PANEL_CLK_DIVISOR_5  = 5,        // Division Ratio 1/5.
    GLCDC_PANEL_CLK_DIVISOR_6  = 6,        // Division Ratio 1/6.
    GLCDC_PANEL_CLK_DIVISOR_7  = 7,        // Division Ratio 1/7.
    GLCDC_PANEL_CLK_DIVISOR_8  = 8,        // Division Ratio 1/8.
    GLCDC_PANEL_CLK_DIVISOR_9  = 9,        // Division Ratio 1/9.
    GLCDC_PANEL_CLK_DIVISOR_12 = 12,       // Division Ratio 1/12.
    GLCDC_PANEL_CLK_DIVISOR_16 = 16,       // Division Ratio 1/16.
    GLCDC_PANEL_CLK_DIVISOR_24 = 24,       // Division Ratio 1/24.
    GLCDC_PANEL_CLK_DIVISOR_32 = 32,       // Division Ratio 1/32.
} glcdc_panel_clk_div_t;

/** LCD TCON output pin select */
typedef enum e_glcdc_tcon_pin
{
    GLCDC_TCON_PIN_0 = 0,                  // LCD_TCON0.
    GLCDC_TCON_PIN_1 = 1,                  // LCD_TCON1.
    GLCDC_TCON_PIN_2 = 2,                  // LCD_TCON2.
    GLCDC_TCON_PIN_3 = 3                   // LCD_TCON3.
} glcdc_tcon_pin_t;

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

