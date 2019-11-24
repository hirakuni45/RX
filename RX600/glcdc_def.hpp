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
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GLCDC 関係定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct glcdc_def {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Correction Command
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CORRECTION_CMD {
			SET_ALL,          ///< All correction setting command.
			BRIGHTNESS,       ///< Brightness setting command.
			CONTRAST,         ///< Contrast setting command.
			GAMMA,            ///< Gamma setting command.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Input format select @n
					Don't change this value, because this value is set to the register
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class IN_FORMAT {
			RGB565   = 0,   // Input format RGB565,   16 bits.
			RGB888   = 1,   // Input format RGB888,   32 bits.
			ARGB1555 = 2,   // Input format ARGB1555, 16 bits.
			ARGB4444 = 3,   // Input format ARGB4444, 16 bits.
			ARGB8888 = 4,   // Input format ARGB8888, 32 bits.
			CLUT8    = 5,   // Input format CLUT8,     8 bits.
			CLUT4    = 6,   // Input format CLUT4,     4 bits.
			CLUT1    = 7,   // Input format CLUT1,     1 bits.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Output format select ( Don't change this value, @n
					because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OUT_FORMAT {
			RGB888 = 0,    // Output format RGB888, 24 bits.
			RGB666 = 1,    // Output format RGB666, 18 bits.
			RGB565 = 2,    // Output format RGB565, 16 bits.
			SERIAL = 3     // Output format SERIAL,  8 bits (this function is not supported).
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Data endian select ( Don't change this value, @n
					because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ENDIAN
		{
			LITTLE = 0,     // Little endian.
			BIG    = 1,     // Big endian.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RGB color order select ( Don't change this value, @n
					because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class COLOR_ORDER
		{
			RGB = 0,         // Color order RGB.
			BGR = 1          // Color order BGR.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Polarity of a signal select ( Don't change this value, @n
					because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SIGNAL_POLARITY
		{
			HIACTIVE = 0,    // High active signal.
			LOACTIVE = 1     // Low active signal.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Signal synchronization edge select ( Don't change @n
					this value, because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SIGNAL_SYNC_EDGE
		{
			RISING = 0,     // Signal is synchronized to rising edge.
			FALLING = 1     // Signal is synchronized to falling edge.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Blending control select
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BLEND_CONTROL
		{
			NONE    = 0,     // Applying no fading control.
			FADEIN  = 1,     // Applying fade-in control.
			FADEOUT = 2,     // Applying fade-out control.
			FIXED   = 3,     // Applying fixed blend control.
			PIXEL   = 4      // Applying pixel blend control.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Fading status
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class FADE_STATUS
		{
			NOT_UNDERWAY,    // Fade-in/fade-out is not in progress.
			FADING_UNDERWAY, // Fade-in or fade-out is in progress.
			UNCERTAIN        // Fade-in/fade-out status is uncertain just before hardware working.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Clock source select ( Don't change this value, @n
					because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CLK_SRC
		{
			EXTERNAL = 0,    // External clock (LCD_EXTCLK) (this function is not supported).
			INTERNAL = 1     // Internal clock (PLL).
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Clock frequency division ratio ( Don't change this @n
					value, because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PANEL_CLK_DIVISOR
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  LCD TCON output pin select
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TCON_PIN
		{
			_0 = 0,         // LCD_TCON0.
			_1 = 1,         // LCD_TCON1.
			_2 = 2,         // LCD_TCON2.
			_3 = 3          // LCD_TCON3.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Correction circuit sequence control select @n
					( Don't change this value, because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CORRECTION_PROC_ORDER
		{
			BRIGHTNESS_CONTRAST_TO_GAMMA = 0, // Brightness, contrast -> gamma correction.
			GAMMA_TO_BRIGHTNESS_CONTRAST = 1  // Gamma correction -> brightness, contrast.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Dithering mode select ( Don't change this value, @n
					because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DITHERING_MODE
		{
			TRUNCATE   = 0,   // No dithering (truncate).
			ROUND_OFF  = 1,   // Dithering with round off.
			PATTERN2X2 = 2    // Dithering with 2x2 pattern.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Dithering 2x2 pattern ( Don't change this value, @n
					because this value is set to the register )
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DITHERING_PATTERN
		{
			_00 = 0,        // 2x2 pattern '00'.
			_01 = 1,        // 2x2 pattern '01'.
			_10 = 2,        // 2x2 pattern '10'.
			_11 = 3         // 2x2 pattern '11'.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  オペレーション・ステータス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OPERATING_STATUS {
			CLOSED = 0,                ///< GLCDC closed.
			NOT_DISPLAYING = 1,        ///< Not Displaying (opened).
			DISPLAYING = 2             ///< Displaying.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Interrupt enable setting
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct interrupt_cfg_t
		{
			bool vpos_enable;          // Line detection interrupt enable.
			bool gr1uf_enable;         // Graphics plane1 underflow interrupt enable.
			bool gr2uf_enable;         // Graphics plane2 underflow interrupt enable.
			interrupt_cfg_t() : vpos_enable(false), gr1uf_enable(false), gr2uf_enable(false)
			{ }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Display output signal timing setting
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct timing_t
		{
			uint16_t display_cyc;		///< Active video cycles or lines.
			uint16_t front_porch;		///< Front poach cycles or lines.
			uint16_t back_porch;		///< Back poach cycles or lines.
			uint16_t sync_width;		///< Sync signal asserting width.
			timing_t() : display_cyc(0), front_porch(0), back_porch(0), sync_width(0) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Coordinate
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct coordinate_t
		{
		    int16_t x;              // Coordinate X, this allows to set signed value.
		    int16_t y;              // Coordinate Y, this allows to set signed value.
			coordinate_t() : x(0), y(0) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RGBA Color
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct color_t
		{
			uint8_t		b;
			uint8_t		g;
			uint8_t		r;
			uint8_t		a;
			color_t(uint8_t r_ = 0, uint8_t g_ = 0, uint8_t b_ = 0, uint8_t a_ = 255) :
				b(b_), g(g_), r(r_), a(a_) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	GLCD hardware specific control block
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct ctrl_t {
			OPERATING_STATUS	state;						// Status of GLCD module.
			bool				is_entry;			// Flag of subcribed GLCDC interrupt function.
			coordinate_t		active_start_pos;			// Zero coordinate for gra phics plane.
			uint16_t			hsize;              		// Horizontal pixel size in a line.
			uint16_t			vsize;              		// Vertical pixel size in a frame.
			bool				graphics_read_enable[2];	// Graphics data read enable.
			void (*callback)(void *);						// Pointer to callback function.
			bool				first_vpos_interrupt_flag;  // First vpos interrupt after release 
											  				// software reset.
			interrupt_cfg_t		interrupt;					// Interrupt setting values.

			volatile uint32_t	vpos_count;

			ctrl_t() :
				state(OPERATING_STATUS::CLOSED),
				is_entry(false),
				active_start_pos(),
				hsize(0), vsize(0),
				graphics_read_enable{ false },
				callback(nullptr),
				first_vpos_interrupt_flag(false),
				interrupt(),
				vpos_count(0)
			{ }
		};
	};
}
