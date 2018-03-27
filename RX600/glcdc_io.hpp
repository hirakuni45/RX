#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　GLCDC　I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/glcdc.hpp"
#include "common/delay.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GLCDC I/O 制御
		@param[in]	GLC		glcdc クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC>
	class glcdc_io {

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		glcdc_io() noexcept
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			// Set the BGEN.SWRST bit to 1 to release the GLCDC from a software reset
			GLC::BGEN.SWRST = 0;
			utils::delay::milli_second(10);
			GLC::BGEN.SWRST = 1;

			// Set the frequency of the LCD_CLK and PXCLK to suit the format
			// and set the PANELCLK.CLKEN bit to 1
			// Select PLL clock, 240 / 24 = 10 MHz, No frequency division, Enable LCD_CLK output
			GLC::PANELCLK = GLC::PANELCLK.DCDR.b(0b011000) | GLC::PANELCLK.CLKEN.b() |
				GLC::PANELCLK.CLKSEL.b();

			// Definition of Background Screen
			// Horizontal cycle (whole control screen)
			// Vertical cycle (whole control screen)

			// glcdc_cfg.output.htiming.front_porch = 5;
			GLC::TCONSTHA1.HS = 5;  // Horizontal Synchronization Signal Assertion Position

			// glcdc_cfg.output.vtiming.front_porch = 8;
			GLC::TCONSTVA1.VS = 8;  // Vertical Synchronization Signal Assertion Position

			// glcdc_cfg.output.htiming.back_porch = 40;
			GLC::TCONSTHA1.HW = 40;
                        // Horizontal Active Pixel Start Position (min. 6 pixels)


#if 0  
  glcdc_cfg.output.vtiming.back_porch = 8;
  glcdc_cfg.output.htiming.display_cyc = XSIZE_PHYS;              // Horizontal Active Pixel Width
  glcdc_cfg.output.vtiming.display_cyc = YSIZE_PHYS;              // Vertical Active Display Width
  glcdc_cfg.output.htiming.sync_width = 1;        				  // Vertical Active Display Start Position (min. 3 lines)
  glcdc_cfg.output.vtiming.sync_width = 1;

  //
  // Graphic 1 configuration
  //
  glcdc_cfg.input[GLCDC_FRAME_LAYER_1].p_base = NULL;			  // Disable Graphics 1

  //
  // Graphic 2 configuration
  //
  													  	  	  	  // Enable reading of the frame buffer
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].p_base = (uint32_t *)_aBufferPTR[0];   // Specify the start address of the frame buffer
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].offset = LINE_OFFSET;      // Offset value from the end address of the line to the start address of the next line
  																  // Single Line Data Transfer Count
  																  // Single Frame Line Count
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].format = COLOR_FORMAT;     // Frame Buffer Color Format RGB565
  glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].visible = true;
  glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].blend_control = GLCDC_BLEND_CONTROL_NONE;	// Display Screen Control (current graphics)
  glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].frame_edge = false;        // Rectangular Alpha Blending Area Frame Display Control
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].frame_edge = false;        // Graphics Area Frame Display Control
  																  // Alpha Blending Control (Per-pixel alpha blending)
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].coordinate.y = 0;          // Graphics Area Vertical Start Position
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].vsize = YSIZE_PHYS;        // Graphics Area Vertical Width
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].coordinate.x = 0;          // Graphics Area Horizontal Start Position
  glcdc_cfg.input[GLCDC_FRAME_LAYER_2].hsize = XSIZE_PHYS;        // Graphics Area Horizontal Width
  glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].start_coordinate.x = 0;    // Rectangular Alpha Blending Area Vertical Start Position
  glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].end_coordinate.x= YSIZE_PHYS; // Rectangular Alpha Blending Area Vertical Width
  glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].start_coordinate.y = 0;    // Rectangular Alpha Blending Area Horizontal Start Position
  glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].end_coordinate.y= XSIZE_PHYS; // Rectangular Alpha Blending Area Horizontal Width
  																  // Graphic 2 Register Value Reflection Enable
  //
  // Timing configuration
  //
  //   Horizontal Synchronization Signal Reference Timing Offset (not support)
  //   Signal Reference Timing Select (not support)
  //   STVB Signal Assertion Timing
  //   STVB Signal Pulse Width
  //   STHB Signal Pulse Width
  glcdc_cfg.output.tcon_vsync = GLCDC_TCON_PIN_0;           // TCON0 Output Signal Select STVA (VSYNC)
  glcdc_cfg.output.tcon_hsync = GLCDC_TCON_PIN_2;           // TCON2 Output Signal Select STHA (HSYNC)
  glcdc_cfg.output.tcon_de    = GLCDC_TCON_PIN_3;           // TCON3 Output Signal Select DE (DEN)
  glcdc_cfg.output.data_enable_polarity = GLCDC_SIGNAL_POLARITY_HIACTIVE;
  glcdc_cfg.output.hsync_polarity = GLCDC_SIGNAL_POLARITY_LOACTIVE;
  glcdc_cfg.output.vsync_polarity = GLCDC_SIGNAL_POLARITY_LOACTIVE;
  glcdc_cfg.output.sync_edge = GLCDC_SIGNAL_SYNC_EDGE_RISING;
  //
  // Output interface
  //
  //   Serial RGB Data Output Delay Control (0 cycles) (not support)
  //   Serial RGB Scan Direction Select (forward) (not support)
  //   Pixel Clock Division Control (no division)
  glcdc_cfg.output.format = GLCDC_OUT_FORMAT_16BITS_RGB565; // Output Data Format Select (RGB565)
  glcdc_cfg.output.color_order = GLCDC_COLOR_ORDER_RGB; ///**/GLCDC_COLOR_ORDER_BGR;  	// Pixel Order Control (B-G-R)
  glcdc_cfg.output.endian = GLCDC_ENDIAN_LITTLE;  			// Bit Endian Control (Little endian)
  //
  // Brightness Adjustment
  //
  glcdc_cfg.output.brightness.b = _BRIGHTNESS;  // B
  glcdc_cfg.output.brightness.g = _BRIGHTNESS;  // G
  glcdc_cfg.output.brightness.r = _BRIGHTNESS;  // R
  //
  // Contrast Adjustment Value
  //
  glcdc_cfg.output.contrast.b = _CONTRAST;  // B
  glcdc_cfg.output.contrast.g = _CONTRAST;  // G
  glcdc_cfg.output.contrast.r = _CONTRAST;  // R
  //
  // Disable Gamma
  //
  glcdc_cfg.output.gamma.enable = false;
  //
  // Disable Chromakey
  //
  glcdc_cfg.chromakey[GLCDC_FRAME_LAYER_2].enable = false;
  //
  // Disable Dithering
  //
  glcdc_cfg.output.dithering.dithering_on = false;
  //
  // CLUT Adjustment Value
  //
  glcdc_cfg.clut[GLCDC_FRAME_LAYER_2].enable = false;
  //
  // Enable VPOS ISR
  //
  //   Detecting Scanline Setting
  glcdc_cfg.detection.vpos_detect = true;		         	// Enable detection of specified line notification in graphic 2
  glcdc_cfg.interrupt.vpos_enable = true;		           	// Enable VPOS interrupt request
  //   Interrupt Priority Level (r_glcdc_rx_config.h)
  //   Interrupt Request Enable
  //   Clears the STMON.VPOS flag
  //   VPOS (line detection)
  glcdc_cfg.detection.gr1uf_detect = false;
  glcdc_cfg.detection.gr2uf_detect = false;
  glcdc_cfg.interrupt.gr1uf_enable = false;
  glcdc_cfg.interrupt.gr2uf_enable = false;
  //
  // Set function to be called on VSYNC
  //
  glcdc_cfg.p_callback = (void (*)(glcdc_callback_args_t *))_VSYNC_ISR;

  runtime_cfg.blend = glcdc_cfg.blend[GLCDC_FRAME_LAYER_2];
  runtime_cfg.input = glcdc_cfg.input[GLCDC_FRAME_LAYER_2];
  runtime_cfg.chromakey = glcdc_cfg.chromakey[GLCDC_FRAME_LAYER_2];
  //
  // Register Dave2D interrupt
  //
  R_BSP_InterruptWrite(BSP_INT_SRC_AL1_DRW2D_DRW_IRQ, (bsp_int_cb_t)drw_int_isr);
  //
  // Register Reflection
  //
  ret = R_GLCDC_Open(&glcdc_cfg);
  if (ret != GLCDC_SUCCESS) {
	  while(1);
  }
  //
  // Init DMA
  //
  R_DMACA_Init();
  //
  // Extended Bus Master Priority Control Register
  //
  BSC.EBMAPCR.BIT.PR1SEL = 0;
  BSC.EBMAPCR.BIT.PR2SEL = 3;
  BSC.EBMAPCR.BIT.PR3SEL = 1;
  BSC.EBMAPCR.BIT.PR4SEL = 2;
  BSC.EBMAPCR.BIT.PR5SEL = 4;
}
#endif
		}

	};
}

