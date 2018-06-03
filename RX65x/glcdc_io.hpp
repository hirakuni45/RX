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
#include "RX65x/glcdc.hpp"
#include "common/delay.hpp"
#include "glcdc_def.hpp"
#include "RX600/dmac_mgr.hpp"

#define BITS_PER_PIXEL 16  // Allowed values: 1, 4, 8, 16, 32

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GLCDC I/O 制御
		@param[in]	GLC		glcdc クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC>
	class glcdc_io {

		static const uint32_t XSIZE_PHYS = 480;		///< Physical display size by X
		static const uint32_t YSIZE_PHYS = 272;		///< Physical display size by Y

#if (BITS_PER_PIXEL == 16)
		static constexpr uint32_t BufferPTR[] = {
			0x00010000,  // Begin of On-Chip RAM
			0x00800000   // Begin of Expansion RAM
		};
#endif

#define FORMAT_RGB_565   (GLCDC_IN_FORMAT_16BITS_RGB565)
#define FORMAT_RGB_888   (GLCDC_IN_FORMAT_32BITS_RGB888)
#define FORMAT_ARGB_1555 (GLCDC_IN_FORMAT_16BITS_ARGB1555)
#define FORMAT_ARGB_4444 (GLCDC_IN_FORMAT_16BITS_ARGB4444)
#define FORMAT_ARGB_8888 (GLCDC_IN_FORMAT_32BITS_ARGB8888)
#define FORMAT_CLUT_8    (GLCDC_IN_FORMAT_CLUT8)
#define FORMAT_CLUT_4    (GLCDC_IN_FORMAT_CLUT4)
#define FORMAT_CLUT_1    (GLCDC_IN_FORMAT_CLUT1)

#if   (BITS_PER_PIXEL == 32)
  $define COLOR_CONVERSION GUICC_M8888I
  #define DISPLAY_DRIVER   GUIDRV_LIN_32
  #define COLOR_FORMAT     FORMAT_RGB_888
  #define NUM_BUFFERS      1
#elif (BITS_PER_PIXEL == 16)
  #define COLOR_CONVERSION GUICC_M565
  #define DISPLAY_DRIVER   GUIDRV_LIN_16
  #define COLOR_FORMAT     FORMAT_RGB_565
  #define NUM_BUFFERS      2
#elif (BITS_PER_PIXEL == 8)
  #define COLOR_CONVERSION GUICC_8666
  #define DISPLAY_DRIVER   GUIDRV_LIN_8
  #define COLOR_FORMAT     FORMAT_CLUT_8
  #define NUM_BUFFERS      2
#elif (BITS_PER_PIXEL == 4)
  #define COLOR_CONVERSION GUICC_16
  #define DISPLAY_DRIVER   GUIDRV_LIN_4
  #define COLOR_FORMAT     FORMAT_CLUT_4
  #define NUM_BUFFERS      3
#elif (BITS_PER_PIXEL == 1)
  #define COLOR_CONVERSION GUICC_1
  #define DISPLAY_DRIVER   GUIDRV_LIN_1
  #define COLOR_FORMAT     FORMAT_CLUT_1
  #define NUM_BUFFERS      3
#endif

		//
		// Buffer size and stride
		//
		static const uint32_t BYTES_PER_LINE   = ((BITS_PER_PIXEL * XSIZE_PHYS) / 8);
		static const uint32_t LINE_OFFSET      = (((BYTES_PER_LINE + 63) / 64) * 64);
		static const uint32_t VXSIZE_PHYS      = ((LINE_OFFSET * 8) / BITS_PER_PIXEL);
		static const uint32_t BYTES_PER_BUFFER = (LINE_OFFSET * YSIZE_PHYS);


		static const uint32_t BRIGHTNESS_ = 0x200;
		static const uint32_t CONTRAST_   = 0x80;

		static const uint32_t GLCDC_ADDRESS_ALIGNMENT_64B = 0x0000003F;

		/* Fixed margin by Hardware operation */
		static const uint32_t BG_PLANE_H_CYC_MARGIN_MIN  = 2;    /* Hsync signal margin is 2 */
		static const uint32_t BG_PLANE_V_CYC_MARGIN_MIN  = 1;    /* Vsync signal margin is 1 */

		/* Color correction setting threshold */
		// OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Mid=512)
		static const uint32_t GLCDC_BRIGHTNESS_DEFAULT  = 512;
		// OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Max=1023)
		static const uint32_t GLCDC_BRIGHTNESS_MAX      = 1023;
		// OUT_CONTRAST.CONTG and .CONTB and .CONTR (Mid=128)
		static const uint32_t GLCDC_CONTRAST_DEFAULT    = 128;
		// OUT_CONTRAST.CONTG and .CONTB and .CONTR (Max=255)
		static const uint32_t GLCDC_CONTRAST_MAX        = 255;
		// GAMx_LUTn.GAIN15 - GAIN0 (Max=2047)
		static const uint32_t GLCDC_GAMMA_GAIN_MAX      = 2047;
		// GAMx_AREAn.TH15  - TH0   (Max=1023)
		static const uint32_t GLCDC_GAMMA_THRESHOLD_MAX = 1023;



		/* Register bit definition for Graphics Frame Control Block */
		static const uint32_t GRn_FLM3_LNOFF_MASK   = 0x0000FFFF;
		static const uint32_t GRn_FLM5_LNNUM_MASK   = 0x000007FF;
		static const uint32_t GRn_FLM5_DATANUM_MASK = 0x0000FFFF;

		static const uint32_t GRn_AB1_DISPSEL_MASK  = 0x00000003;
		static const uint32_t GRn_AB2_GRCVS_MASK    = 0x000007FF;
		static const uint32_t GRn_AB2_GRCVW_MASK    = 0x07FF;
		static const uint32_t GRn_AB3_GRCHS_MASK    = 0x000007FF;
		static const uint32_t GRn_AB3_GRCHW_MASK    = 0x07FF;
		static const uint32_t GRn_AB4_ARCVS_MASK    = 0x000007FF;
		static const uint32_t GRn_AB4_ARCVW_MASK    = 0x07FF;
		static const uint32_t GRn_AB5_ARCHS_MASK    = 0x000007FF;
		static const uint32_t GRn_AB5_ARCHW_MASK    = 0x07FF;
		static const uint32_t GRn_AB6_ARCCOEF_MASK  = 0x000001FF;
		static const uint32_t GRn_AB7_ARCDEF_MASK   = 0x000000FF;
		static const uint32_t GRn_CLUTINT_LINE_MASK = 0x000007FF;

		/* Registers for Background Frame Control Block */
		static const uint32_t BG_PERI_FV_MASK  = 0x000007FF;
		static const uint32_t BG_PERI_FH_MASK  = 0x000007FF;
		static const uint32_t BG_SYNC_VP_MASK  = 0x000F;
		static const uint32_t BG_SYNC_HP_MASK  = 0x000F;
		static const uint32_t BG_VSIZE_VP_MASK = 0x07FF;
		static const uint32_t BG_VSIZE_VW_MASK = 0x07FF;
		static const uint32_t BG_HSIZE_HP_MASK = 0x07FF;
		static const uint32_t BG_HSIZE_HW_MASK = 0x07FF;


		static const uint32_t TCON_STHx1_HS_MASK   = 0x07FF;
		static const uint32_t TCON_STHx1_HW_MASK   = 0x07FF;
		static const uint32_t TCON_STVx1_VS_MASK   = 0x07FF;
		static const uint32_t TCON_STVx1_VW_MASK   = 0x07FF;


		static const uint32_t OUT_SET_FRQSEL_NO_DIVISION     = 0;
		static const uint32_t OUT_SET_FRQSEL_QUATER_DIVISION = 1;

		static const uint32_t OUT_BRIGHT1_BRTG_MASK  = 0x03FF;
		static const uint32_t OUT_BRIGHT2_BRTB_MASK  = 0x03FF;
		static const uint32_t OUT_BRIGHT2_BRTR_MASK  = 0x03FF;

		static const uint32_t OUT_CONTRAST_CONTG_MASK  = 0xFF;
		static const uint32_t OUT_CONTRAST_CONTB_MASK  = 0xFF;
		static const uint32_t OUT_CONTRAST_CONTR_MASK  = 0xFF;



		/* Panel timing, Minimum threshold */
		static const uint32_t BG_PLANE_H_CYC_MIN  = 24;  // BG_PERI.FH (Min=24)
		static const uint32_t BG_PLANE_V_CYC_MIN  = 20;  // BG_PERI.FV (Min=20)
		#define BG_PLANE_HSYNC_POS_MIN         (1)              /* BG_HSYNC.HP (Min=1) */
		#define BG_PLANE_VSYNC_POS_MIN         (1)              /* BG_HSYNC.VP (Min=1) */
		#define BG_PLANE_H_CYC_ACTIVE_SIZE_MIN (16)             /* BG_HSIZE.HW (Min=16) */
		#define BG_PLANE_V_CYC_ACTIVE_SIZE_MIN (16)             /* BG_VSIZE.VW (Min=16) */
		#define BG_PLANE_H_ACTIVE_POS_MIN      (6)              /* BG_HSIZE.HP (Min=6) */
		#define BG_PLANE_V_ACTIVE_POS_MIN      (3)              /* BG_VSIZE.VP (Min=3) */
		#define GR_PLANE_LNOFF_POS_MIN         (-32768)         /* GRn_FLM3_LNOFF(positive num min=-32768) */
#define GR_PLANE_H_CYC_ACTIVE_SIZE_MIN (16)             /* GRn_AB3.GRCHW (Min=16) */
#define GR_PLANE_V_CYC_ACTIVE_SIZE_MIN (16)             /* GRn_AB2.GRCVW (Min=16) */
#define GR_PLANE_H_ACTIVE_POS_MIN      (5)              /* GRn_AB2.GRCHS (Min=5) */
#define GR_PLANE_V_ACTIVE_POS_MIN      (2)              /* GRn_AB2.GRCVS (Min=2) */
#define BG_PLANE_H_FRONT_PORCH_MIN     (3)              /* Horizontal front porch parameter (MIN=3) */
#define BG_PLANE_V_FRONT_PORCH_MIN     (2)              /* Vertical front porch parameter (MIN=2) */
#define BG_PLANE_H_BACK_PORCH_MIN      (1)              /* Horizontal back porch parameter (MIN=1) */
#define BG_PLANE_V_BACK_PORCH_MIN      (1)              /* Vertical back porch parameter (MIN=1) */
#define BG_PLANE_H_SYNC_WIDTH_MIN      (4)              /* Horizontal sync signal width parameter (MIN=4) */
#define BG_PLANE_V_SYNC_WIDTH_MIN      (1)              /* Vertical sync signal width parameter (MIN=1) */
#define GR_BLEND_H_ACTIVE_POS_MIN      (5)              /* GRn_AB5_GRCHS (Min=5) */
#define GR_BLEND_V_ACTIVE_POS_MIN      (2)              /* GRn_AB4_GRCVS (Min=2) */
#define GR_BLEND_H_CYC_ACTIVE_SIZE_MIN (1)              /* GRn_AB5_GRCHW (Min=1) */
#define GR_BLEND_V_CYC_ACTIVE_SIZE_MIN (1)              /* GRn_AB4_GRCVW (Min=1) */



		static const uint32_t SYSCNT_PANEL_CLK_DCDR_MASK = 0x3F;



		/** Timing signals for driving the LCD panel */
		typedef enum e_glcdc_tcon_signal_select
		{
		    GLCDC_TCON_SIGNAL_SELECT_STVA_VS = 0,  // STVA/VS
		    GLCDC_TCON_SIGNAL_SELECT_STVB_VE = 1,  // STVB/VE
		    GLCDC_TCON_SIGNAL_SELECT_STHA_HS = 2,  // STH/SP/HS
		    GLCDC_TCON_SIGNAL_SELECT_STHB_HE = 3,  // STB/LP/HE
		    GLCDC_TCON_SIGNAL_SELECT_DE      = 7   // DE
		} glcdc_tcon_signal_select_t;


		/** Fade control initial value set */
		typedef enum e_glcd_fading_ctrl_initial_alpha
		{
			// Initial alpha value setting for a graphics plane is zero.
			GLCDC_FADING_CONTROL_INITIAL_ALPHA_MIN = 0,
			// Initial alpha value setting for a graphics plane is maximum.
			GLCDC_FADING_CONTROL_INITIAL_ALPHA_MAX = 0xff
		} glcdc_fade_ctrl_initial_alpha_t;

		/** Blend plane select */
		typedef enum e_glcdc_plane_blend
		{
    		GLCDC_PLANE_BLEND_TRANSPARENT = 1,     // Current graphics layer is transparent
												   // and the lower layer is displayed.
			GLCDC_PLANE_BLEND_NON_TRANSPARENT = 2, // Current graphics layer is displayed.
			GLCDC_PLANE_BLEND_ON_LOWER_LAYER = 3   // Current graphics layer is blended with
												   // the lower layer.
		} glcdc_plane_blend_t;


		/** Clut plane select */
		typedef enum e_glcdc_clut_plane
		{
			GLCDC_CLUT_PLANE_0 = 0,                // GLCD CLUT plane 0.
			GLCDC_CLUT_PLANE_1 = 1                 // GLCD CLUT plane 1.
		} glcdc_clut_plane_t;


		/** Dithering output format */
		typedef enum e_glcdc_dithering_output_format
		{
			GLCDC_DITHERING_OUTPUT_FORMAT_RGB888 = 0,  // Dithering output format RGB888.
			GLCDC_DITHERING_OUTPUT_FORMAT_RGB666 = 1,  // Dithering output format RGB666.
			GLCDC_DITHERING_OUTPUT_FORMAT_RGB565 = 2   // Dithering output format RGB565.
		} glcdc_dithering_output_format_t;


		/** Coordinate */
		struct glcdc_coordinate_t
		{
    		int16_t x;                           // Coordinate X, this allows to set signed value.
    		int16_t y;                           // Coordinate Y, this allows to set signed value.
			glcdc_coordinate_t(int16_t x_ = 0, int16_t y_ = 0) : x(x_), y(y_)
			{ }
		};


		/** GLCDC driver operation state */
		typedef enum e_glcdc_state
		{
			GLCDC_STATE_CLOSED = 0,                // GLCDC closed.
			GLCDC_STATE_NOT_DISPLAYING = 1,        // Not Displaying (opened).
			GLCDC_STATE_DISPLAYING = 2             // Displaying.
		} glcdc_operating_status_t;


		/** Interrupt enable setting */
		struct glcdc_interrupt_cfg_t {
			bool vpos_enable;                    // Line detection interrupt enable.
			bool gr1uf_enable;                   // Graphics plane1 underflow interrupt enable.
			bool gr2uf_enable;                   // Graphics plane2 underflow interrupt enable.
			glcdc_interrupt_cfg_t() :
				vpos_enable(false), gr1uf_enable(false), gr2uf_enable(false)
			{ }
		};


		// GLCD hardware specific control block
		struct glcdc_ctrl_t {
			glcdc_operating_status_t state;		  // Status of GLCD module.
			bool is_entry;						  // Flag of subcribed GLCDC interrupt function.
			glcdc_coordinate_t active_start_pos;  // Zero coordinate for gra phics plane.
			uint16_t hsize;                       // Horizontal pixel size in a line.
			uint16_t vsize;                       // Vertical pixel size in a frame.
			bool graphics_read_enable[GLCDC_FRAME_LAYER_NUM];  // Graphics data read enable.
			void (*p_callback)(void *);           // Pointer to callback function.
			bool first_vpos_interrupt_flag;       // First vpos interrupt after release 
												  // software reset.
			glcdc_interrupt_cfg_t interrupt;      // Interrupt setting values.
			glcdc_ctrl_t() :
				state(GLCDC_STATE_CLOSED),
				is_entry(false),
				active_start_pos(),
				hsize(0), vsize(0),
				graphics_read_enable{ false },
				p_callback(nullptr),
				first_vpos_interrupt_flag(false),
				interrupt()
			{ }
		};
		glcdc_ctrl_t	ctrl_blk_;





		void release_software_reset_()
		{
			/* ---- Releases software reset. ---- */
			/* BGEN - Background Generating Block Operation Control Register
			b31:b17 Reserved - These bits are read as 0. Writing to these bits have no effect.
			b16     SWRST    - GLCDC Software Reset Release. - Release GLCDC software reset.
			b15:b9  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b8      VEN      - Register Value Reflection Enable.
			b7:b1   Reserved - These bits are read as 0. Writing to these bits have no effect.
			b0      EN       - Background Generating Block Operation Enable. */
			GLC::BGEN.SWRST = 1;
		}


		void clock_set_(const glcdc_cfg_t& cfg)
		{
			/* PANELCLK - Panel Clock Control Register
			b31:b25 Reserved - These bits are read as 0. Writing to these bits have no effect.
			b24     Reserved - These bits are read as 1. Writing to this bit has no effect.
			b23:b21 Reserved - These bits are read as 0. Writing to these bits have no effect.
			b20     Reserved - These bits are read as 1. Writing to this bit has no effect.
			b19:b16 Reserved - These bits are read as 0. Writing to these bits have no effect.
			b15:b13 Reserved - These bits are read as 0. The write value should be 0.
			b12     PIXSEL   - Pixel Clock Select. - No frequency division (parallel RGB) or
							   Divided-by-4 (serial RGB)
			b11:b9  Reserved - These bits are read as 0. The write value should be 0.
			b8      CLKSEL   - Clock Source Select. - Select LCD_EXTCLK (external clock) or
							   Select PLL clock.
			b7      Reserved - This bit is read as 0. The write value should be 0.
			b6      CLKEN    - Panel Clock Output Enable. - Disable LCD_CLK output or
							   Enable LCD_CLK output.
			b5      DCDR[5:0]- Clock Division Ratio Setting. - Divide-by-2 to Divide-by-32. */

			// Selects input source for panel clock
			GLC::PANELCLK.CLKSEL = (uint32_t)cfg.output.clksrc;

			// Sets division ratio
			GLC::PANELCLK.DCDR = (uint32_t)cfg.output.clock_div_ratio & SYSCNT_PANEL_CLK_DCDR_MASK;

			// Selects pixel clock output
			if(GLCDC_OUT_FORMAT_8BITS_SERIAL != cfg.output.format) {
				GLC::PANELCLK.PIXSEL = 0; /* ParallelRGBSelect */
			} else {
				GLC::PANELCLK.PIXSEL = 1; /* SerialRGBSelect */
			}

			GLC::PANELCLK.CLKEN = 1; /* Panel Clock(LCD_CLK) Output Enable */

			/* Waiting for supply of panel clock(LCD_CLK) and pixel clock(PXCLK)
			 * The BGMON.SWRST bit is sampled with PXCLK. Therefore, if the CLKEN bit is set,
			 * the BGEN.SWRST bit is reflected on the BGMON.SWRST bit. */
			while(0 == GLC::BGMON.SWRST()) {
				asm("nop");
			}
		}

		void hsync_set_(glcdc_tcon_pin_t tcon, const glcdc_timing_t& timing,
			glcdc_signal_polarity_t polarity)
		{
			switch(tcon) {
			case GLCDC_TCON_PIN_1:
				/* Hsync(STHA) -> TCON1 */
				GLC::TCONSTVB2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS;
				break;
			case GLCDC_TCON_PIN_2:
				/* Hsync(STHA) ->  TCON2 */
				GLC::TCONSTHA2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS;
				break;
			case GLCDC_TCON_PIN_3:
				/* Hsync(STHA) -> TCON3 */
				GLC::TCONSTHB2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS;
				break;
			case GLCDC_TCON_PIN_0: /* Intentionally go though to the default case */
			default:
				/* Hsync(STHA) -> TCON0 */
				GLC::TCONSTVA2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS;
				break;
			}

			/* Polarity of a signal select */
			/* TCONSTHA2 - Horizontal Timing Setting Register A2
			b31:b9 Reserved - These bits are read as 0. Writing to these bits have no effect.
			b8     HSSEL    - STHy Signal Reference Timing Select. - Select HS signal or
							  the TCONTIM.OFFSET[10:0] bits as reference for signal generation.
			b7:b5  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b4     INV      - STHy Signal Polarity Inversion. - Do not invert the STHy signal
							  or Invert the STHy signal.
			b3     Reserved - These bits are read as 0. Writing to these bits have no effect.
			b2:b0  SEL[2:0] - Output Signal Select. - Select as STVA, STVB, STHA, STHB or DE */
			GLC::TCONSTHA2.INV = (uint32_t)polarity; /* Hsync(STHA) -> Invert or Not Invert */

			// Hsync beginning position
			GLC::TCONSTHA1.HS = 0;    /* No delay */
			GLC::TCONSTHA2.HSSEL = 0; /* Select input Hsync as reference */

			// HSync Width Setting
			GLC::TCONSTHA1.HW = timing.sync_width & TCON_STHx1_HW_MASK;
		}


		void vsync_set_(glcdc_tcon_pin_t tcon, const glcdc_timing_t& timing,
			glcdc_signal_polarity_t polarity)
		{

			switch(tcon) {
			case GLCDC_TCON_PIN_0:
				/* Vsync(STVA) -> TCON0 */
				GLC::TCONSTVA2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS;
				break;
			case GLCDC_TCON_PIN_2:
				/* Vsync(STVA) -> TCON2 */
				GLC::TCONSTHA2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS;
				break;
			case GLCDC_TCON_PIN_3:
				/* Vsync(STVA) -> TCON3 */
				GLC::TCONSTHB2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS;
				break;
			case GLCDC_TCON_PIN_1: /* Intentionally go though to the default case */
			default:
				/* Vsync(STVA) -> TCON1 */
				GLC::TCONSTVB2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS;
				break;
			}

			/* Vsync(STVA) -> Invert or Vsync(STVA) -> Not Invert */
			GLC::TCONSTVA2.INV = (uint32_t)polarity;

			/* Vsync beginning position */
			GLC::TCONSTVA1.VS = 0;      /* No delay. */

			/* VSync Width Setting */
			GLC::TCONSTVA1.VW = timing.sync_width & TCON_STVx1_VW_MASK;
		}


		void data_enable_set_(glcdc_tcon_pin_t tcon, const glcdc_timing_t& vtiming,
                              const glcdc_timing_t& htiming, glcdc_signal_polarity_t polarity)
		{
			switch (tcon) {
			case GLCDC_TCON_PIN_0:
				/* DE -> TCON0 */
				GLC::TCONSTVA2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE;
				break;
			case GLCDC_TCON_PIN_1:
				GLC::TCONSTVB2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE; /* DE -> TCON1 */
				break;
			case GLCDC_TCON_PIN_3:
				GLC::TCONSTHB2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE; /* DE -> TCON3 */
				break;
			case GLCDC_TCON_PIN_2: /* Intentionally go though to the default case */
			default:
				GLC::TCONSTHA2.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE; /* DE -> TCON2 */
				break;
			}

			GLC::TCONDE.INV = (uint32_t)polarity; /* DE -> Invert or Not Invert */

			/* Set data enable timing */
			GLC::TCONSTHB1.HS = (htiming.back_porch + htiming.sync_width) & TCON_STHx1_HS_MASK;
			GLC::TCONSTHB1.HW = htiming.display_cyc & TCON_STHx1_HW_MASK;
			GLC::TCONSTHB2.HSSEL = 0; /* Select input Hsync as reference */
			GLC::TCONSTVB1.VS = (vtiming.back_porch + vtiming.sync_width) & TCON_STVx1_VS_MASK;
			GLC::TCONSTVB1.VW = vtiming.display_cyc & TCON_STVx1_VW_MASK;
		}




		void sync_signal_set_(const glcdc_cfg_t& cfg)
		{
			/* CLKPHASE - Output Phase Control Register
			b31:b13 Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b12     FRONTGAM  - Correction Sequence Control.
			b11:b9  Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b8      LCDEDG    - DATA Output Phase Control. - synchronized with rising or falling
								edges of LCD_CLK
			b7      Reserved  - This bit is read as 0. The write value should be 0.
			b6      TCON0EDGE - TCON0 Output Phase Control. - synchronized with rising or falling
								edges of LCD_CLK
			b5      TCON1EDGE - TCON1 Output Phase Control. - synchronized with rising or falling
								edges of LCD_CLK
			b4      TCON2EDGE - TCON2 Output Phase Control. - synchronized with rising or falling
								edges of LCD_CLK
			b3      TCON3EDGE - TCON3 Output Phase Control. - synchronized with rising or falling
								edges of LCD_CLK
			b2:b0   Reserved  - These bits are read as 0. Writing to these bits have no effect. */
			GLC::CLKPHASE.LCDEDG = (uint32_t)cfg.output.sync_edge;
			GLC::CLKPHASE.TCON0EDG = (uint32_t)cfg.output.sync_edge;
			GLC::CLKPHASE.TCON1EDG = (uint32_t)cfg.output.sync_edge;
			GLC::CLKPHASE.TCON2EDG = (uint32_t)cfg.output.sync_edge;
			GLC::CLKPHASE.TCON3EDG = (uint32_t)cfg.output.sync_edge;

			/* TCONTIM - Reference Timing Setting Register
			b31:b27  Reserved     - These bits are read as 0. Writing to these bits have no effect.
			b26:b16  HALF[10:0]   - Vertical synchronization signal change timing setting.
			b15:b11  Reserved     - These bits are read as 0. Writing to these bits have no effect.
			b10:b0   OFFSET[10:0] - Horizontal synchronization signal generation reference timing.
			*/
			GLC::TCONTIM.OFFSET = 0; // 1 pixel
			GLC::TCONTIM.HALF = 0;   // 1 pixel (No delay)

			hsync_set_(cfg.output.tcon_hsync, cfg.output.htiming, cfg.output.hsync_polarity);
			vsync_set_(cfg.output.tcon_vsync, cfg.output.vtiming, cfg.output.vsync_polarity);
			data_enable_set_(cfg.output.tcon_de, cfg.output.vtiming, cfg.output.htiming,
				cfg.output.data_enable_polarity);
		}


		void background_screen_set_(const glcdc_cfg_t& cfg)
		{
			uint32_t hsync_total_cyc;
			uint32_t vsync_total_cyc;

			hsync_total_cyc = (((cfg.output.htiming.front_porch  + cfg.output.htiming.sync_width)
							  +  cfg.output.htiming.display_cyc) + cfg.output.htiming.back_porch);
			vsync_total_cyc = (((cfg.output.vtiming.front_porch  + cfg.output.vtiming.sync_width)
							  +  cfg.output.vtiming.display_cyc) + cfg.output.vtiming.back_porch);

			/* - Set number of total cycle for a line including Sync & Back poach, Front poach - */
			/* BGPERI - Free-Running Period Register
			b31:b27  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b26:b16  FV[10:0] - Vertical Synchronization Signal Period Setting.
			b15:b11  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b10:b0   FH[10:0] - Horizontal Synchronization Signal Period Setting. */
			GLC::BGPERI.FH = (hsync_total_cyc - 1) & BG_PERI_FH_MASK;
			GLC::BGPERI.FV = (vsync_total_cyc - 1) & BG_PERI_FV_MASK;

			/* BGSYNC - Synchronization Position Register
			b31:b20 Reserved - These bits are read as 0. Writing to these bits have no effect.
			b19:b16 VP[3:0]  - Vertical Synchronization Assertion Position Setting.
			b15:b4  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b3:b0   HP[3:0]  - Horizontal Synchronization Signal Assertion Position Setting. */
			GLC::BGSYNC.HP = (cfg.output.htiming.front_porch - BG_PLANE_H_CYC_MARGIN_MIN)
							 & BG_SYNC_HP_MASK;
			GLC::BGSYNC.VP = (cfg.output.vtiming.front_porch - BG_PLANE_V_CYC_MARGIN_MIN)
							 & BG_SYNC_VP_MASK;

			/* ---- Set the start position of Background screen ---- */
			/* BGHSIZE - Horizontal Size Register
			b31:b27  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b26:b16  HP[10:0] - Horizontal Active Pixel Start Position Setting.
			b15:b11  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b10:b0   HW[10:0] - Horizontal Active Pixel Width Setting. */
			GLC::BGHSIZE.HP = (uint16_t) ((cfg.output.htiming.front_porch
				- BG_PLANE_H_CYC_MARGIN_MIN)
				+ cfg.output.htiming.sync_width + cfg.output.htiming.back_porch)
				& BG_HSIZE_HP_MASK;

			/* BGVSIZE - Vertical Size Register
			b31:b27  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b26:b16  VP[10:0] - Vertical Active Pixel Start Position Setting.
			b15:b11  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b10:b0   VW[10:0] - Vertical Active Pixel Width Setting. */
			GLC::BGVSIZE.VP = (uint16_t) ((cfg.output.vtiming.front_porch
				- BG_PLANE_V_CYC_MARGIN_MIN)
				+ cfg.output.vtiming.sync_width + cfg.output.vtiming.back_porch)
				& BG_VSIZE_VP_MASK;
			/* ---- Set the width of Background screen ---- */
			/* BGHSIZE - Horizontal Size Register
			b10:b0   HW[10:0] - Horizontal Active Pixel Width Setting. */
			GLC::BGHSIZE.HW = cfg.output.htiming.display_cyc & BG_HSIZE_HW_MASK;

			/* BGVSIZE - Vertical Size Register
			b10:b0   VW[10:0] - Vertical Active Pixel Width Setting. */
			GLC::BGVSIZE.VW = cfg.output.vtiming.display_cyc & BG_VSIZE_VW_MASK;

			/* ---- Set the Background color ---- */
			/* BGCOLOR - Background Color Register
			b31:b24  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b23:b16  R[7:0] - Background Color R Value Setting.
			b15:b8   G[7:0] - Background Color G Value Setting.
			b7:b0    B[7:0] - Background Color B Value Setting. */
			GLC::BGCOLOR.R = cfg.output.bg_color.byte.r;
			GLC::BGCOLOR.G = cfg.output.bg_color.byte.g;
			GLC::BGCOLOR.B = cfg.output.bg_color.byte.b;
		}


		static uint16_t get_bit_size_(glcdc_in_format_t format)
		{
			uint16_t bit_size = 0;

			/* ---- Get bit size and set color format ---- */
			switch (format) {
			case GLCDC_IN_FORMAT_32BITS_ARGB8888:         ///< ARGB8888, 32bits
			case GLCDC_IN_FORMAT_32BITS_RGB888:           ///< RGB888,   32bits
				bit_size = 32;
				break;
			case GLCDC_IN_FORMAT_16BITS_RGB565:           ///< RGB565,   16bits
			case GLCDC_IN_FORMAT_16BITS_ARGB1555:         ///< ARGB1555, 16bits
			case GLCDC_IN_FORMAT_16BITS_ARGB4444:         ///< ARGB4444, 16bits
				bit_size = 16;
				break;
			case GLCDC_IN_FORMAT_CLUT8:                   ///< CLUT8
				bit_size = 8;
				break;
			case GLCDC_IN_FORMAT_CLUT4:                   ///< CLUT4
				bit_size = 4;
				break;
			case GLCDC_IN_FORMAT_CLUT1:                   ///< CLUT1
			default:
				bit_size = 1;
				break;
			}
			return bit_size;
		}


		void gr_plane_format_set_(glcdc_in_format_t format, glcdc_frame_layer_t frame)
		{
			/* GRnFLM6 - Graphic n Frame Buffer Control Register 6
			b31     Reserved    - This bit is read as 0. The write value should be 0.
			b30:b28 FORMAT[2:0] - Frame Buffer Color Format Setting.
			b27:b0  Reserved    - These bits are read as 0.
								  Writing to these bits have no effect. */
			if(frame == 0) {
				GLC::GR1FLM6.FORMAT = (uint32_t)format;
			} else { 
				GLC::GR2FLM6.FORMAT = (uint32_t)format;
			}
		}


		void graphics_layer_set_(const glcdc_input_cfg_t& input, glcdc_frame_layer_t frame)
		{
			uint32_t bit_size = get_bit_size_(input.format);

    		// If enable graphics data read from memory
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				return;
			}

			gr_plane_format_set_(input.format, frame);

			/* ---- Set the base address of graphics plane ---- */
			/* GRnFLM2 - Graphic n Frame Buffer Control Register 2 */
			// gp_gr[frame]->grxflm2 = (uint32_t)input.p_base;
			if(frame == 0) {
				GLC::GR1FLM2 = (uint32_t)input.p_base;
			} else {
				GLC::GR2FLM2 = (uint32_t)input.p_base;
			}

			/* ---- Set the background color on graphics plane ---- */
			/* GRnBASE - Graphic n Background Color Control Register
			b31:b24  Reserved - These bits are read as 0. Writing to these bits have no effect.
			b23:b16  G[7:0] - Background Color G Value Setting.
			b15:b8   B[7:0] - Background Color B Value Setting.
			b7:b0    R[7:0] - Background Color R Value Setting. */
			if(frame == 0) {
				GLC::GR1BASE.R = input.bg_color.byte.r;
				GLC::GR1BASE.G = input.bg_color.byte.g;
				GLC::GR1BASE.B = input.bg_color.byte.b;
			} else {
				GLC::GR2BASE.R = input.bg_color.byte.r;
				GLC::GR2BASE.G = input.bg_color.byte.g;
				GLC::GR2BASE.B = input.bg_color.byte.b;
			}

			// --- Set the number of data transfer times per line, 64 bytes are transferred
			//     in each transfer ----
			/* GRnFLM5 - Graphic n Frame Buffer Control Register 5
			b31:b27 Reserved - These bits are read as 0. Writing to these bits have no effect.
			b26:b16 LNNUM[10:0] - Single Frame Line Count Setting.
			b15:b0  DATANUM[15:0] - Single Line Data Transfer Count Setting */

			// Convert to byte size of Single line data transfer, round up fractions below
			// the decimal point
			uint32_t line_byte_num = ((bit_size * input.hsize) / 8);
			if(0 != ((bit_size * input.hsize) % 8)) {
				line_byte_num += 1;
			}

			// Convert to Single line data transfer count, round up fractions below the
			// decimal point
			uint32_t line_trans_num = (line_byte_num >> 6);
			if(0 != (line_byte_num & GLCDC_ADDRESS_ALIGNMENT_64B)) {
				line_trans_num += 1;
			}
			if(frame == 0) {
				GLC::GR1FLM5.DATANUM = (line_trans_num - 1) & GRn_FLM5_DATANUM_MASK;
			} else {
				GLC::GR2FLM5.DATANUM = (line_trans_num - 1) & GRn_FLM5_DATANUM_MASK;
			}

			/* ---- Set the line offset address for accessing the graphics data ---- */
			/* GRnFLM5 - Graphic n Frame Buffer Control Register 5
			b26:b16 LNNUM[10:0] - Single Frame Line Count Setting. */
			if(frame == 0) {
				GLC::GR1FLM5.LNNUM = ((uint32_t)(input.vsize - 1)) & GRn_FLM5_LNNUM_MASK;
			} else {
				GLC::GR2FLM5.LNNUM = ((uint32_t)(input.vsize - 1)) & GRn_FLM5_LNNUM_MASK;
			}

			// ---- Set the line offset address for accessing the graphics data on graphics
			// plane ----
			/* GRnFLM3 - Graphic n Frame Buffer Control Register 3
			b31:b16 LNOFF[15:0] - Macro Line Offset Setting. - Set the offset value from the
								  end address of the line on the frame buffer (macro line) to
								  the start address of the next macro line. */
			if(frame == 0) {
				GLC::GR1FLM3.LNOFF = (uint32_t)input.offset & GRn_FLM3_LNOFF_MASK;
			} else {
				GLC::GR2FLM3.LNOFF = (uint32_t)input.offset & GRn_FLM3_LNOFF_MASK;
			}

			/* GRnAB2 - Graphic n Alpha Blending Control Register 2
			b10:b0  GRCVW[10:0] - Graphics Area Vertical Width Setting. */
			if(frame == 0) {
				GLC::GR1AB2.GRCVW = input.vsize & GRn_AB2_GRCVW_MASK;
			} else {
				GLC::GR2AB2.GRCVW = input.vsize & GRn_AB2_GRCVW_MASK;
			}

			/* GRnAB2 - Graphic n Alpha Blending Control Register 2
			b26:b16 GRCVS[10:0] - Graphics Area Vertical Start Position Setting. */
			if(frame == 0) {
				GLC::GR1AB2.GRCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
									+ input.coordinate.y)) & GRn_AB2_GRCVS_MASK;
			} else {
				GLC::GR2AB2.GRCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
									+ input.coordinate.y)) & GRn_AB2_GRCVS_MASK;
			}

			/* ---- Set the width of the graphics layers ---- */
			/* GRnAB3 - Graphic n Alpha Blending Control Register 3
			b10:b0  GRCHW[10:0] - Graphics Area Horizontal Width Setting. */
			// gp_gr[frame]->grxab3.bit.grchw = input.hsize & GRn_AB3_GRCHW_MASK;
			if(frame == 0) {
				GLC::GR1AB3.GRCHW = input.hsize & GRn_AB3_GRCHW_MASK;
			} else {
				GLC::GR2AB3.GRCHW = input.hsize & GRn_AB3_GRCHW_MASK;
			}

			/* ---- Set the start position of the graphics layers ---- */
			/* GRnAB3 - Graphic n Alpha Blending Control Register 3
			b31:b27 Reserved    - These bits are read as 0. Writing to these bits have no effect.
			b26:b16 GRCHS[10:0] - Graphics Area Horizontal Start Position Setting.
			b15:b11 Reserved    - These bits are read as 0. Writing to these bits have no effect.
			b10:b0  GRCHW[10:0] - Graphics Area Horizontal Width Setting. */
			// gp_gr[frame]->grxab3.bit.grchs = ((uint32_t)(ctrl_blk_.active_start_pos.x
			//								 + input.coordinate.x)) & GRn_AB3_GRCHS_MASK;
			if(frame == 0) {
				GLC::GR1AB3.GRCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
									+ input.coordinate.x)) & GRn_AB3_GRCHS_MASK;
			} else {
				GLC::GR2AB3.GRCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
									+ input.coordinate.x)) & GRn_AB3_GRCHS_MASK;
			}

			/* GRnAB1 - Graphic n Alpha Blending Control Register 1
			b4      GRCDISPON - Graphics Area Frame Display Control.
                                  - Area Frame is displayed or not displayed. */
			if(frame == 0) {
				GLC::GR1AB1.GRCDISPON = input.frame_edge == true ? 1 : 0;
			} else {
				GLC::GR2AB1.GRCDISPON = input.frame_edge == true ? 1 : 0;
			}
		}


		void blend_condition_set_(const glcdc_blend_t& blend, glcdc_frame_layer_t frame)
		{

			/* if enable graphics data read from memory */
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				/* GRnAB1 - Graphic n Alpha Blending Control Register 1
				b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current
									   graphics with lower-layer graphics */
				/* Set layer transparent */
				if(frame == 0) {
					GLC::GR1AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT
										  & GRn_AB1_DISPSEL_MASK;
				} else {
					GLC::GR2AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT
										  & GRn_AB1_DISPSEL_MASK;
				}
				return;
			}

			switch(blend.blend_control)
			{
			case GLCDC_BLEND_CONTROL_NONE:
            /* GRnAB1 - Graphic n Alpha Blending Control Register 1
            b31:b13 Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b12     ARCON     - Alpha Blending Control. - Per-pixel alpha blending.
            b11:b9  Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b8      ARCDISPON - Rectangular Alpha Blending Area Frame Display Control.
                              - Area Frame is displayed or not displayed.
            b7:b5   Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b4      GRCDISPON - Graphics Area Frame Display Control.
                              - Area Frame is displayed or not displayed.
            b3:b2   Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b1:b0   DISPSEL[1:0] - Display Screen Control. - Displays the background, lower-layer,
                                   current graphics or blend graphics with lower-layer */

				if(frame == 0) {
					GLC::GR1AB1.ARCON = 0;
				} else {
					GLC::GR2AB1.ARCON = 0;
				}
				if(true == blend.visible) {
					/* GRnAB1 - Graphic n Alpha Blending Control Register 1
					b1:b0   DISPSEL[1:0] - Display Screen Control. - Displays current graphics */
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_NON_TRANSPARENT
						   					  & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_NON_TRANSPARENT
						   					  & GRn_AB1_DISPSEL_MASK;
					}
				} else {
					/* GRnAB1 - Graphic n Alpha Blending Control Register 1
					b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current
										   graphics with lower-layer graphics */
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT
											  & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT
											  & GRn_AB1_DISPSEL_MASK;
					}
				}
				break;
			case GLCDC_BLEND_CONTROL_FADEIN:
			case GLCDC_BLEND_CONTROL_FADEOUT:
			case GLCDC_BLEND_CONTROL_FIXED:
				/* ---- Set the start position of the rectangle area in the graphics layers ---- */
				/* GRnAB5 - Graphic n Alpha Blending Control Register 5
				b31:b27  Reserved    - These bits are read as 0. Writing to these bits have
									   no effect.
				b26:b16  ARCHS[10:0] - Rectangular Alpha Blending Area Horizontal Start
									   Position Setting.
				b15:b11  Reserved    - These bits are read as 0. Writing to these bits have
									   no effect.
				b10:b0   ARCHW[10:0] - Rectangular Alpha Blending Area Horizontal Width Setting. */
				// gp_gr[frame]->grxab5.bit.archs = 
                //    
				if(frame == 0) {
					GLC::GR1AB5.ARCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
										+ blend.start_coordinate.x)) & GRn_AB5_ARCHS_MASK;
				} else {
					GLC::GR2AB5.ARCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
										+ blend.start_coordinate.x)) & GRn_AB5_ARCHS_MASK;
				}

				/* GRnAB4 - Graphic n Alpha Blending Control Register 4
				b31:b27  Reserved    - These bits are read as 0. Writing to these bits have
									   no effect.
				b26:b16  ARCVS[10:0] - Rectangular Alpha Blending Area Vertical Start Position
									   Setting.
				b15:b11  Reserved    - These bits are read as 0. Writing to these bits have
									   no effect.
				b10:b0   ARCVW[10:0] - Rectangular Alpha Blending Area Vertical Width Setting. */
				if(frame == 0) {
					GLC::GR1AB4.ARCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
										+ blend.start_coordinate.y))& GRn_AB4_ARCVS_MASK;
				} else {
					GLC::GR2AB4.ARCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
										+ blend.start_coordinate.y))& GRn_AB4_ARCVS_MASK;
				}

				/* ---- Set the width of the graphics layers ---- */
				/* GRnAB5 - Graphic n Alpha Blending Control Register 5
				b10:b0   ARCHW[10:0] - Rectangular Alpha Blending Area Horizontal Width Setting. */
				if(frame == 0) {
					GLC::GR1AB5.ARCHW = (blend.end_coordinate.x - blend.start_coordinate.x)
										& GRn_AB5_ARCHW_MASK;
				} else {
					GLC::GR2AB5.ARCHW = (blend.end_coordinate.x - blend.start_coordinate.x)
										& GRn_AB5_ARCHW_MASK;
				}

				/* GRnAB4 - Graphic n Alpha Blending Control Register 4
				b10:b0   ARCVW[10:0] - Rectangular Alpha Blending Area Vertical Width Setting. */
				if(frame == 0) {
					GLC::GR1AB4.ARCVW = (blend.end_coordinate.y - blend.start_coordinate.y)
					                    & GRn_AB4_ARCVW_MASK;
				} else {
					GLC::GR2AB4.ARCVW = (blend.end_coordinate.y - blend.start_coordinate.y)
					                    & GRn_AB4_ARCVW_MASK;
				}

				/*---- Enable rectangular alpha blending ---- */
				/* GRnAB1 - Graphic n Alpha Blending Control Register 1
				b12     ARCON     - Alpha Blending Control. - Set rectangular alpha blending. */
				if(frame == 0) {
					GLC::GR1AB1.ARCON = 1;
				} else {
					GLC::GR2AB1.ARCON = 1;
				}

				/* GRnAB6 - Graphic n Alpha Blending Control Register 6
				b31:b25  Reserved    - These bits are read as 0. Writing to these bits have
									   no effect.
				b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting.
				b15:b8   Reserved    - These bits are read as 0. Writing to these bits have
									   no effect.
				b7:b0    ARCRATE[7:0]- Alpha Blending Updating Rate Setting. Set 1 frame. */
            	// gp_gr[frame]->grxab6.bit.arcrate = 0x00;
				if(frame == 0) {
					GLC::GR1AB6.ARCRATE = 0x00;
				} else {
					GLC::GR2AB6.ARCRATE = 0x00;
				}

	            if(GLCDC_BLEND_CONTROL_FADEIN == blend.blend_control) {
					/* GRnAB7 - Graphic n Alpha Blending Control Register 7
                	b31:b24 Reserved    - These bits are read as 0. Writing to these bits have
										  no effect.
					b23:b16 ARCDEF[7:0] - Initial Alpha Value Setting. - Set is 0.
                	b15:b1  Reserved    - These bits are read as 0. Writing to these bits have
										  no effect.
                	b0      CKON        - Chroma Key Compositing Control. */
					if(frame == 0) {
						GLC::GR1AB7.ARCDEF = (uint32_t)GLCDC_FADING_CONTROL_INITIAL_ALPHA_MIN
											 & GRn_AB7_ARCDEF_MASK;
					} else {
						GLC::GR2AB7.ARCDEF = (uint32_t)GLCDC_FADING_CONTROL_INITIAL_ALPHA_MIN
											 & GRn_AB7_ARCDEF_MASK;
					}
                	/* GRnAB6 - Graphic n Alpha Blending Control Register 6
                	b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting. */
					if(frame == 0) {
						GLC::GR1AB6.ARCCOEF = (uint32_t)blend.fade_speed & GRn_AB6_ARCCOEF_MASK;
					} else {
						GLC::GR2AB6.ARCCOEF = (uint32_t)blend.fade_speed & GRn_AB6_ARCCOEF_MASK;
					}
            	} else if (GLCDC_BLEND_CONTROL_FADEOUT == blend.blend_control) {
					/* GRnAB7 - Graphic n Alpha Blending Control Register 7
					b23:b16 ARCDEF[7:0] - Initial Alpha Value Setting. - Set is 0. */
					if(frame == 0) {
						GLC::GR1AB7.ARCDEF = (uint32_t)GLCDC_FADING_CONTROL_INITIAL_ALPHA_MAX
											 & GRn_AB7_ARCDEF_MASK;
					} else {
						GLC::GR2AB7.ARCDEF = (uint32_t)GLCDC_FADING_CONTROL_INITIAL_ALPHA_MAX
											 & GRn_AB7_ARCDEF_MASK;
					}

					/* GRnAB6 - Graphic n Alpha Blending Control Register 6
					b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting. */
					if(frame == 0) {
						GLC::GR1AB6.ARCCOEF = ((uint32_t) blend.fade_speed | (1 << 8))
											  & GRn_AB6_ARCCOEF_MASK;
					} else {
						GLC::GR2AB6.ARCCOEF = ((uint32_t) blend.fade_speed | (1 << 8))
											  & GRn_AB6_ARCCOEF_MASK;
					}
				} else {  /* ---- GLCDC_FADE_CONTROL_FIXED ---- */
					/* GRnAB7 - Graphic n Alpha Blending Control Register 7
					b23:b16 ARCDEF[7:0] - Initial Alpha Value Setting. - Set is 0. */
					if(frame == 0) {
						GLC::GR1AB7.ARCDEF = (uint32_t)blend.fixed_blend_value
											 & GRn_AB7_ARCDEF_MASK;
					} else {
						GLC::GR2AB7.ARCDEF = (uint32_t)blend.fixed_blend_value
											 & GRn_AB7_ARCDEF_MASK;
					}

					/* GRnAB6 - Graphic n Alpha Blending Control Register 6
					b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting. - Set is 0 */
					if(frame == 0) {
						GLC::GR1AB6.ARCCOEF = 0x000;
					} else {
						GLC::GR2AB6.ARCCOEF = 0x000;
					}
				}

				/* GRnAB1 - Graphic n Alpha Blending Control Register 1
				b8      ARCDISPON - Rectangular Alpha Blending Area Frame Display Control.
								  - Area Frame is displayed or not displayed. */
				/* Set the frame of the rectangular alpha blending area to displayed */
               	// gp_gr[frame]->grxab1.bit.arcdispon = 1;
				if(frame == 0) {
					GLC::GR1AB1.ARCDISPON = blend.frame_edge == true ? 1 : 0;
				} else {
					GLC::GR2AB1.ARCDISPON = blend.frame_edge == true ? 1 : 0;
				}

				/* GRnAB1 - Graphic n Alpha Blending Control Register 1
				b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current
									   graphics with lower-layer graphics */
				if(frame == 0) {
					GLC::GR1AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_ON_LOWER_LAYER
										  & GRn_AB1_DISPSEL_MASK;
				} else {
					GLC::GR2AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_ON_LOWER_LAYER
										  & GRn_AB1_DISPSEL_MASK;
				}
				break;
			case GLCDC_BLEND_CONTROL_PIXEL:
			default:
				/* GRnAB1 - Graphic n Alpha Blending Control Register 1
				b12     ARCON     - Alpha Blending Control. - Per-pixel alpha blending. */
				if(frame == 0) {
					GLC::GR1AB1.ARCON = 0;
				} else {
					GLC::GR2AB1.ARCON = 0;
				}

				if(true == blend.visible) {
					/* GRnAB1 - Graphic n Alpha Blending Control Register 1
					b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of
										   current graphics with lower-layer graphics */
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_ON_LOWER_LAYER
											  & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_ON_LOWER_LAYER
											  & GRn_AB1_DISPSEL_MASK;
					}
				} else {
					/* GRnAB1 - Graphic n Alpha Blending Control Register 1
					b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of
										   current graphics with lower-layer graphics */
					/* Set layer transparent */
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT
											  & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT
											  & GRn_AB1_DISPSEL_MASK;
					}
				}
				break;
			}
		}


		void graphics_chromakey_set_(const glcdc_chromakey_t& chromakey, glcdc_frame_layer_t frame)
		{
			/* if enable graphics data read from memory */
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				return;
			}

			if(true == chromakey.enable) {
				/* ---- Chroma key enable ---- */
				/* GRnAB7 - Graphic n Alpha Blending Control Register 7
				b0 CKON - Chroma Key Compositing Control. - Enable RGB reference chroma key
						  compositing. */
				if(frame == 0) {
					GLC::GR1AB7.CKON = 1;
				} else {
					GLC::GR2AB7.CKON = 1;
				}

				/* ---- Before ---- */
				/* GRnAB8 - Graphic n Alpha Blending Control Register 8
				b31:b24  Reserved - These bits are read as 0. Writing to these bits have no effect.
				b23:b16  CKKG[7:0] - Chroma Key Compositing Target G Value Setting.
				b15:b8   CKKB[7:0] - Chroma Key Compositing Target B Value Setting.
				b7:b0    CKKR[7:0] - Chroma Key Compositing Target R Value Setting. */
				if(frame == 0) {
					GLC::GR1AB8.CKKR = chromakey.before.byte.r;
					GLC::GR1AB8.CKKG = chromakey.before.byte.g;
					GLC::GR1AB8.CKKB = chromakey.before.byte.b;
				} else {
					GLC::GR2AB8.CKKR = chromakey.before.byte.r;
					GLC::GR2AB8.CKKG = chromakey.before.byte.g;
					GLC::GR2AB8.CKKB = chromakey.before.byte.b;
				}

				/* ---- After ---- */
				/* GRnAB9 - Graphic n Alpha Blending Control Register 9
				b31:b24  CKA[7:0] - Chroma Key Compositing Replacing A Value Setting.
				b23:b16  CKG[7:0] - Chroma Key Compositing Replacing G Value Setting.
				b15:b8   CKB[7:0] - Chroma Key Compositing Replacing B Value Setting.
				b7:b0    CKR[7:0] - Chroma Key Compositing Replacing R Value Setting. */
				if(frame == 0) {
					GLC::GR1AB9.CKA = chromakey.after.byte.a;
					GLC::GR1AB9.CKR = chromakey.after.byte.r;
					GLC::GR1AB9.CKG = chromakey.after.byte.g;
					GLC::GR1AB9.CKB = chromakey.after.byte.b;
				} else {
					GLC::GR2AB9.CKA = chromakey.after.byte.a;
					GLC::GR2AB9.CKR = chromakey.after.byte.r;
					GLC::GR2AB9.CKG = chromakey.after.byte.g;
					GLC::GR2AB9.CKB = chromakey.after.byte.b;
				}
			} else {
				/* ---- Chroma key disable ---- */
				/* GRnAB7 - Graphic n Alpha Blending Control Register 7
				b0 CKON - Chroma Key Compositing Control. - Disable RGB reference chroma key
						  compositing. */
				if(frame == 0) {
					GLC::GR1AB7.CKON = 0;
				} else {
					GLC::GR2AB7.CKON = 0;
				}
			}
		}


		glcdc_clut_plane_t is_clutplane_selected_(glcdc_frame_layer_t frame)
		{
			/* GRnCLUTINT - Graphic n CLUT/Interrupt Control Register
			b16 SEL - CLUT Control. - Select Color Look-up Table. */
			if(frame == 0) {
				return (glcdc_clut_plane_t)GLC::GR1CLUTINT.SEL();
			} else {
				return (glcdc_clut_plane_t)GLC::GR2CLUTINT.SEL();
			}
		}


		void clutplane_select_(glcdc_frame_layer_t frame, glcdc_clut_plane_t clut_plane)
		{
			/* GRnCLUTINT - Graphic n CLUT/Interrupt Control Register
			b16 SEL - CLUT Control. - Select Color Look-up Table. */
			if(frame == 0) {
				GLC::GR1CLUTINT.SEL = (uint32_t)clut_plane;
			} else {
				GLC::GR2CLUTINT.SEL = (uint32_t)clut_plane;
			}
		}


		void clut_set_(glcdc_frame_layer_t frame, glcdc_clut_plane_t clut_plane,
					   uint32_t entry, uint32_t data)
		{
			/* GRnCLUTm[k] - Color Look-up Table
			b31:b24 A[7:0] - Color Look-up Table A Value Setting.
			b23:b16 R[7:0] - Color Look-up Table R Value Setting.
			b15:b8  G[7:0] - Color Look-up Table G Value Setting.
			b7:b0   B[7:0] - Color Look-up Table B Value Setting. */
    		// gp_gr_clut[frame][clut_plane]->grxclut[entry].lsize = data;
			if(frame == 0) {
				if(clut_plane == 0) {
					GLC::GR1CLUT0[entry] = data;
				} else {
					GLC::GR1CLUT1[entry] = data;
				}
			} else {
				if(clut_plane == 0) {
					GLC::GR2CLUT0[entry] = data;
				} else {
					GLC::GR2CLUT1[entry] = data;
				}
			}
		}


		void clut_update_(const glcdc_clut_cfg_t& clut, glcdc_frame_layer_t frame)
		{
			/* If enable graphics data read from memory */
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				return;
			}

			if(true == clut.enable) {
				const uint32_t* p_base = clut.p_base;

				glcdc_clut_plane_t set_clutplane;
///				if(GLCDC_CLUT_PLANE_1 == is_clutplane_selected_(frame)) {
				if(GLCDC_CLUT_PLANE_0 == is_clutplane_selected_(frame)) {
					set_clutplane = GLCDC_CLUT_PLANE_0;
				} else {
					set_clutplane = GLCDC_CLUT_PLANE_1;
				}

				/* Copy the new CLUT data on the source memory to the CLUT SRAM in
				   the GLCD module */
				for(uint32_t i = clut.start; i < (clut.start + clut.size); ++i) {
					clut_set_(frame, set_clutplane, i, *p_base++);
				}

				/* Make the GLCD module read the new CLUT table data from the next frame */
				clutplane_select_(frame, set_clutplane);
			}
		}


		void output_block_set_(const glcdc_cfg_t& cfg)
		{
			/* OUTSET - Output Interface Register
			b31:b29 Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b28     ENDIANON   - Bit Endian Control. - Little endian or big endian.
			b27:b25 Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b24     SWAPON     - Pixel Order Control. - R-G-B order or B-G-R order.
			b23:b14 Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b13:b12 FORMAT[1:0]- Output Data Format Select. - RGB(888), RGB(666), RGB(565)
								 or Serial RGB.
			b11:b10 Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b9      FRQSEL[1:0]- Pixel Clock Division Control. - No division (parallel RGB)
								 or Divide-by-4 (serial RGB).
			b8      Reserved   - This bit is read as 0. The write value should be 0.
			b7:b5   Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b4      DIRSEL     - Serial RGB Scan Direction Select. - Forward scan or Reverse scan.
			b3:b2   Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b1:b0   PHASE[1:0] - Serial RGB Data Output Delay Control. - 0 to 3 cycles */

			// Selects big or little endian for output data
			GLC::OUTSET.ENDIANON = (uint32_t)cfg.output.endian;

			// Selects the output byte order swapping
			GLC::OUTSET.SWAPON = (uint32_t)cfg.output.color_order;

			// Selects the output format
			switch(cfg.output.format) {
			case GLCDC_OUT_FORMAT_8BITS_SERIAL: /* In case of serial RGB, set as RGB888 format */
				GLC::OUTSET.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_8BITS_SERIAL;
				GLC::OUTSET.PHASE = (uint32_t)cfg.output.serial_output_delay;
				GLC::OUTSET.DIRSEL = (uint32_t)cfg.output.serial_scan_direction;
				GLC::PANELDTHA.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB888;
				break;
			case GLCDC_OUT_FORMAT_16BITS_RGB565:
				GLC::OUTSET.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_16BITS_RGB565;
				GLC::PANELDTHA.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB565;
				break;
			case GLCDC_OUT_FORMAT_18BITS_RGB666:
				GLC::OUTSET.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_18BITS_RGB666;
				GLC::PANELDTHA.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB666;
				break;
			case GLCDC_OUT_FORMAT_24BITS_RGB888:
			default:
				GLC::OUTSET.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_24BITS_RGB888;
				GLC::PANELDTHA.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB888;
				break;
			}

			/* Sets the pixel clock (the GLCD internal signal) frequency in case that
			the output format is 8-bit serial RGB */
			if(GLCDC_OUT_FORMAT_8BITS_SERIAL == cfg.output.format) {
				GLC::OUTSET.FRQSEL = OUT_SET_FRQSEL_QUATER_DIVISION;
			} else {
				GLC::OUTSET.FRQSEL = OUT_SET_FRQSEL_NO_DIVISION;
			}

			/* Sets the Brightness/contrast and Gamma Correction processing order */
			/* CLKPHASE - Output Phase Control Register
			b12     FRONTGAM  - Correction Sequence Control. */
			GLC::CLKPHASE.FRONTGAM = (uint32_t)cfg.output.correction_proc_order;

			/* PANELDTHA - Panel Dither Control Register
			b31:b22 Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b21:b20 SEL[1:0]  - Rounding Mode Setting. - Truncate, Round-off, 2*2 pattern dither.
			b19:b18 Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b17:b16 FORM[1:0] - Output Format Select. - RGB(888), RGB(666), RGB(565).
			b15:b14 Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b13:b12 PA[1:0]   - Dither Pattern Value A Setting.
			b11:b10 Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b9:b8   PB[1:0]   - Dither Pattern Value B Setting.
			b7:b6   Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b5:b4   PC[1:0]   - Dither Pattern Value C Setting.
			b3:b2   Reserved  - These bits are read as 0. Writing to these bits have no effect.
			b1:b0   PD[1:0]   - Dither Pattern Value D Setting. */

			/* ---- Set the dithering mode ---- */
			if(true == cfg.output.dithering.dithering_on) {
				if(GLCDC_DITHERING_MODE_2X2PATTERN == cfg.output.dithering.dithering_mode) {
					GLC::PANELDTHA.PA = (uint32_t)cfg.output.dithering.dithering_pattern_a;
					GLC::PANELDTHA.PB = (uint32_t)cfg.output.dithering.dithering_pattern_b;
					GLC::PANELDTHA.PC = (uint32_t)cfg.output.dithering.dithering_pattern_c;
					GLC::PANELDTHA.PD = (uint32_t)cfg.output.dithering.dithering_pattern_d;
				}

				GLC::PANELDTHA.SEL = (uint32_t)cfg.output.dithering.dithering_mode;
			} else {
				GLC::PANELDTHA.SEL = (uint32_t)GLCDC_DITHERING_MODE_TRUNCATE;
			}
		}


		void brightness_correction_(const glcdc_brightness_t& brightness)
		{

			if(true == brightness.enable) {
				/* ---- Sets brightness correction register for each color in a pixel. ---- */
				/* BRIGHT1 - Brightness Adjustment Register 1
				b31:b10 Reserved  - These bits are read as 0. Writing to these bits have no effect.
				b9:b0   BRTG[9:0] - G Channel Brightness Adjustment Value Setting */
				GLC::BRIGHT1.BRTG = brightness.g & OUT_BRIGHT1_BRTG_MASK;

				/* BRIGHT2 - Brightness Adjustment Register 2
				b31:b26 Reserved  - These bits are read as 0. Writing to these bits have no effect.
				b25:b16 BRTB[9:0] - B Channel Brightness Adjustment Value Setting.
				b15:b10 Reserved  - These bits are read as 0. Writing to these bits have no effect.
				b9:b0   BRTR[9:0] - R Channel Brightness Adjustment Value Setting */
				GLC::BRIGHT2.BRTB = brightness.b & OUT_BRIGHT2_BRTB_MASK;
				GLC::BRIGHT2.BRTR = brightness.r & OUT_BRIGHT2_BRTR_MASK;
			} else {
				/* --- If brightness setting in configuration is 'off', apply default value --- */
				/* BRIGHT1 - Brightness Adjustment Register 1
				b9:b0   BRTG[9:0] - G Channel Brightness Adjustment Value Setting */
				GLC::BRIGHT1.BRTG = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT1_BRTG_MASK;

				/* BRIGHT2 - Brightness Adjustment Register 2
				b25:b16 BRTB[9:0] - B Channel Brightness Adjustment Value Setting.
				b9:b0   BRTR[9:0] - R Channel Brightness Adjustment Value Setting */
				GLC::BRIGHT2.BRTB = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT2_BRTB_MASK;
				GLC::BRIGHT2.BRTR = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT2_BRTR_MASK;
			}
		}


		void contrast_correction_(const glcdc_contrast_t& contrast)
		{

			if(true == contrast.enable) {
				/* ---- Sets the contrast correction register for each color in a pixel. ---- */
				/* CONTRAST - Contrast Adjustment Register
				b31:b24 Reserved  - These bits are read as 0. Writing to these bits have no effect.
				b23:b16 CONTG[7:0]- G Channel Contrast Adjustment Value Setting.
				b15:b8  CONTB[7:0]- B Channel Contrast Adjustment Value Setting.
				b7:b0   CONTR[7:0]- R Channel Contrast Adjustment Value Setting. */
				GLC::CONTRAST.CONTG = contrast.g & OUT_CONTRAST_CONTG_MASK;
				GLC::CONTRAST.CONTB = contrast.b & OUT_CONTRAST_CONTB_MASK;
				GLC::CONTRAST.CONTR = contrast.r & OUT_CONTRAST_CONTR_MASK;
			} else {
				/* ---- If the contrast setting in the configuration is set to 'off',
						apply default value ---- */
				/* CONTRAST - Contrast Adjustment Register
				b23:b16 CONTG[7:0]- G Channel Contrast Adjustment Value Setting.
				b15:b8  CONTB[7:0]- B Channel Contrast Adjustment Value Setting.
				b7:b0   CONTR[7:0]- R Channel Contrast Adjustment Value Setting. */
				GLC::CONTRAST.CONTG = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTG_MASK;
				GLC::CONTRAST.CONTB = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTB_MASK;
				GLC::CONTRAST.CONTR = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTR_MASK;
			}
		}


		void gamma_correction_(const glcdc_gamma_correction_t& gamma)
		{
			if(true == gamma.enable) {
				/* ---- Gamma correction enable and set gamma setting ---- */
				/* GAMSW - Gamma Correction Block Function Switch Register
				b31:b1 Reserved - These bits are read as 0. Writing to these bits have no effect.
				b0     GAMON    - Gamma Correction Enable. - Enables gamma correction. */
				GLC::GAMSW.GAMON = 1;
#if 0
				/* Green */
				uint32_t *p_lut_table;
				p_lut_table = (uint32_t*)(&GLCDC.GAMGLUT1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2) {
					/* GAMGLUTx - Gamma Correction G Table Setting Register x */
					*p_lut_table = ((((uint32_t)p_gamma->p_g->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
						| ((uint32_t)p_gamma->p_g->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
					p_lut_table++;
				}

				p_lut_table = (uint32_t *) (&GLCDC.GAMGAREA1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3) {
///////
            /* GAMGAREAx - Gamma Correction G Area Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_g->threshold[i] & GAMX_AREAX_MASK) << 20)
                    | (((uint32_t)p_gamma->p_g->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
                    | ((uint32_t)p_gamma->p_g->threshold[i + 2] & GAMX_AREAX_MASK));
            p_lut_table++;
        }


        /* Blue */
        p_lut_table = (uint32_t *)(&GLCDC.GAMBLUT1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2)
        {
            /* GAMBLUTx - Gamma Correction B Table Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_b->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
                    | ((uint32_t)p_gamma->p_b->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
            p_lut_table++;
        }

        p_lut_table = (uint32_t *) (&GLCDC.GAMBAREA1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3)
        {
            /* GAMBAREAx - Gamma Correction B Area Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_b->threshold[i] & GAMX_AREAX_MASK) << 20)
                    | (((uint32_t)p_gamma->p_b->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
                    | ((uint32_t)p_gamma->p_b->threshold[i + 2] & GAMX_AREAX_MASK));
            p_lut_table++;
        }


        /* Red */
        p_lut_table = (uint32_t *) (&GLCDC.GAMRLUT1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2)
        {
            /* GAMRLUTx - Gamma Correction R Table Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_r->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
                    | ((uint32_t)p_gamma->p_r->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
            p_lut_table++;
        }

        p_lut_table = (uint32_t *) (&GLCDC.GAMRAREA1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3)
        {
            /* GAMRAREAx - Gamma Correction R Area Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_r->threshold[i] & GAMX_AREAX_MASK) << 20)
                    | (((uint32_t)p_gamma->p_r->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
                    | ((uint32_t)p_gamma->p_r->threshold[i + 2] & GAMX_AREAX_MASK));
            p_lut_table++;
        }
#endif
			} else {
				/* ---- Gamma Correction Disable ---- */
				/* GAMSW - Gamma Correction Block Function Switch Register
				b0     GAMON    - Gamma Correction Enable. - Disables gamma correction. */
				GLC::GAMSW.GAMON = 0;
			}
		}


		void line_detect_number_set_(uint32_t line)
		{
			/* GR2CLUTINT - Graphic 2 CLUT/Interrupt Control Register
			b31:b17 Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b16     SEL        - CLUT Control. - Select Color Look-up Table.
			b15:b11 Reserved   - These bits are read as 0. Writing to these bits have no effect.
			b10:b0  LINE[10:0] - Detecting Scan line Setting. */
			GLC::GR2CLUTINT.LINE = line & GRn_CLUTINT_LINE_MASK;
		}


		void detect_setting_(const glcdc_detect_cfg_t& detection)
		{
			if(true == detection.vpos_detect) {
				// Set Graphic 2 Specified Line Notification Detection to enable
				GLC::DTCTEN.VPOSDTC = 1;
			} else {
				// Set Graphic 2 Specified Line Notification Detection to disable
				GLC::DTCTEN.VPOSDTC = 0;
			}

			if(true == detection.gr1uf_detect) {
				// Set Graphic 1 Underflow Detection to enable
				GLC::DTCTEN.GR1UFDTC = 1;
			} else {
				// Set Graphic 1 Underflow Detection to disable
				GLC::DTCTEN.GR1UFDTC = 0;
			}

			if(true == detection.gr2uf_detect) {
				// Set Graphic 2 Underflow Detection to enable
				GLC::DTCTEN.GR2UFDTC = 1;
			} else {
				// Set Graphic 2 Underflow Detection to disable
				GLC::DTCTEN.GR2UFDTC = 0;
			}
		}


		void interrupt_setting_(const glcdc_interrupt_cfg_t& interrupt)
		{
///			bsp_int_ctrl_t grpal1;

///			grpal1.ipl = GLCDC_CFG_INTERRUPT_PRIORITY_LEVEL;

			if(true == interrupt.vpos_enable) {
				/* INTEN - Interrupt Request Enable Control Register
				b31:b3 Reserved   - These bits are read as 0. Writing to these bits have no effect.
				b2     GR2UFINTEN - GR2UF Interrupt Enable.
				b1     GR1UFINTEN - GR1UF Interrupt Enable.
				b0     VPOSINTEN  - VPOS Interrupt Enable. - Enable VPOS interrupt request. */
				GLC::INTEN.VPOSINTEN = 1;

				/* GENAL1 - Group AL1 Interrupt Request Enable Register
				b8 EN8 - Interrupt Request Enable 8 - Interrupt request is enabled. */
///				EN(GLCDC,VPOS) = 1;
			} else {
				/* INTEN - Interrupt Request Enable Control Register
				b0 VPOSINTEN  - VPOS Interrupt Enable. - Disable VPOS interrupt request. */
				GLC::INTEN.VPOSINTEN = 0;

				/* GENAL1 - Group AL1 Interrupt Request Enable Register
				b8 EN8 - Interrupt Request Enable 8 - Interrupt request is disabled. */
///				EN(GLCDC,VPOS) = 0;

				/* GRPAL1 - Group AL1 Interrupt Request Register
				b8 IS8 - Interrupt Status Flag 8. */
///				while(0 != IS(GLCDC,VPOS)) {
///					asm("nop");
///				}
			}

			if(true == interrupt.gr1uf_enable) {
				/* INTEN - Interrupt Request Enable Control Register
				b1 GR1UFINTEN - GR1UF Interrupt enable. */
				GLC::INTEN.GR1UFINTEN = 1;

				/* GENAL1 - Group AL1 Interrupt Request Enable Register
				b9 EN9 - Interrupt Request Enable 9 - Interrupt request is enabled. */
///				EN(GLCDC,GR1UF) = 1;
			} else {
				/* INTEN - Interrupt Request Enable Control Register
				b1 GR1UFINTEN - GR1UF Interrupt disable. */
				GLC::INTEN.GR1UFINTEN = 0;

				/* GENAL1 - Group AL1 Interrupt Request Enable Register
				b9 EN9 - Interrupt Request Enable 9 - Interrupt request is disabled. */
///				EN(GLCDC,GR1UF) = 0;

				/* GRPAL1 - Group AL1 Interrupt Request Register
				b9 IS9 - Interrupt Status Flag 9. */
///				while(0 != IS(GLCDC,GR1UF)) {
///					asm("nop");
///				}
			}

			if(true == interrupt.gr2uf_enable) {
				/* INTEN - Interrupt Request Enable Control Register
				b2 GR2UFINTEN - GR2UF Interrupt enable. */
				GLC::INTEN.GR2UFINTEN = 1;

				/* GENAL1 - Group AL1 Interrupt Request Enable Register
				b10 EN10 - Interrupt Request Enable 10 - Interrupt request is enabled. */
///				EN(GLCDC,GR2UF) = 1;
			} else {
				/* INTEN - Interrupt Request Enable Control Register
				b2 GR2UFINTEN - GR2UF Interrupt disable. */
				GLC::INTEN.GR2UFINTEN = 0;

				/* GENAL1 - Group AL1 Interrupt Request Enable Register
				b10 EN10 - Interrupt Request Enable 10 - Interrupt request is disabled. */
///				EN(GLCDC,GR2UF) = 0;

				/* GRPAL1 - Group AL1 Interrupt Request Register
				b10 IS10 - Interrupt Status Flag 10. */
///				while (0 != IS(GLCDC,GR2UF)) {
///					asm("nop");
///				}
			}

			/* Set GROUPAL1 interrupt request to enable, if GLCDC interrupt parameter is enabled
			Set GROUPAL1 interrupt request to disable, if GLCDC interrupt parameter is disabled */
			if((true == interrupt.vpos_enable) || (true == interrupt.gr1uf_enable) ||
			   (true == interrupt.gr2uf_enable)) {
///				R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_ENABLE, (void *) &grpal1.ipl);
			} else {
///				R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_DISABLE, NULL);
			}
		}


		void graphics_read_enable_()
		{
			if(true == ctrl_blk_.graphics_read_enable[GLCDC_FRAME_LAYER_1]) {
				/* GR1FLMRD - Graphic 1 Frame Buffer Read Control Register
				b31:b1 Reserved   - These bits are read as 0. Writing to these bits have no effect.
				b0     RENB - Frame Buffer Read Enable. - Enable reading of the frame buffer. */
				GLC::GR1FLMRD.RENB = 1;    /* Enable reading. */
			} else {
				/* GR1FLMRD - Graphic 1 Frame Buffer Read Control Register
				b0     RENB - Frame Buffer Read Enable. - Disable reading of the frame buffer. */
				GLC::GR1FLMRD.RENB = 0;    /* Disable reading. */
			}

			if(true == ctrl_blk_.graphics_read_enable[GLCDC_FRAME_LAYER_2]) {
				/* GR2FLMRD - Graphic 2 Frame Buffer Read Control Register
				b0     RENB - Frame Buffer Read Enable. - Enable reading of the frame buffer. */
				GLC::GR2FLMRD.RENB = 1;    /* Enable reading. */
			} else {
				/* GR2FLMRD - Graphic 2 Frame Buffer Read Control Register
				b0     RENB - Frame Buffer Read Enable. - Enable reading of the frame buffer. */
				GLC::GR2FLMRD.RENB = 0;    /* Disable reading. */
			}
		}



		static void vsync_task_(void* ptr)
		{
#if 0
			glcdc_callback_args_t* t = static_cast<glcdc_callback_args_t*>(ptr);

#if (NUM_BUFFERS == 3)
			uint32_t Addr;
			glcdc_err_t ret;
#endif

			// Clears the STMON.VPOS flag (GLCDC FIT module clears STMON.VPOS flag)
#if (NUM_BUFFERS == 3)
			//
			// Makes the pending buffer visible
			//
  if (_PendingBuffer >= 0) {
    Addr = FRAMEBUFFER_START
         + BYTES_PER_BUFFER * _PendingBuffer;   // Calculate address of buffer to be used  as visible frame buffer
    runtime_cfg.input.p_base = (uint32_t *)Addr; // Specify the start address of the frame buffer
    ret = R_GLCDC_LayerChange(GLCDC_FRAME_LAYER_2, &runtime_cfg);	// Graphic 2 Register Value Reflection Enable
    if (ret != GLCDC_SUCCESS) {
    	while(1);
    }
    GUI_MULTIBUF_ConfirmEx(0, _PendingBuffer);  // Tell emWin that buffer is used
    _PendingBuffer = -1;                        // Clear pending buffer flag
  }
#elif (NUM_BUFFERS == 2)
  //
  // Sets a flag to be able to notice the interrupt
  //
  _PendingBuffer = 0;
#endif

#endif
		}


		bool open_(const glcdc_cfg_t& cfg)
		{
#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
			glcdc_err_t err = GLCDC_SUCCESS;
#endif

			// Status check
			if(GLCDC_STATE_CLOSED != ctrl_blk_.state) {
//				return GLCDC_ERR_INVALID_MODE;
				return false;
			}

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
			// Argument check
			if(nullptr == p_cfg) {
//				return GLCDC_ERR_INVALID_PTR;
				return false;
			}
#endif

			// Store position information to the control block
			// (it is necessary to set the layer and blending section later)
			ctrl_blk_.active_start_pos.x = static_cast<int16_t>(cfg.output.htiming.back_porch
				+ cfg.output.htiming.sync_width);
			ctrl_blk_.active_start_pos.y = static_cast<int16_t>(cfg.output.vtiming.back_porch
				+ cfg.output.vtiming.sync_width);
			ctrl_blk_.hsize = cfg.output.htiming.display_cyc;
			ctrl_blk_.vsize = cfg.output.vtiming.display_cyc;

			// Subscribe each interrupt function
			if(false == ctrl_blk_.is_entry) {
#if 0
		R_BSP_InterruptWrite (BSP_INT_SRC_AL1_GLCDC_VPOS, (bsp_int_cb_t) r_glcdc_line_detect_isr);
		R_BSP_InterruptWrite (BSP_INT_SRC_AL1_GLCDC_GR1UF, (bsp_int_cb_t) r_glcdc_underflow_1_isr);
		R_BSP_InterruptWrite (BSP_INT_SRC_AL1_GLCDC_GR2UF, (bsp_int_cb_t) r_glcdc_underflow_2_isr);
#endif
				ctrl_blk_.is_entry = true;
			}

			// Save status of frame buffer read enable
			if(nullptr == cfg.input[GLCDC_FRAME_LAYER_1].p_base) {
				ctrl_blk_.graphics_read_enable[GLCDC_FRAME_LAYER_1] = false;
			} else {
				ctrl_blk_.graphics_read_enable[GLCDC_FRAME_LAYER_1] = true;
			}

			if(nullptr == cfg.input[GLCDC_FRAME_LAYER_2].p_base) {
				ctrl_blk_.graphics_read_enable[GLCDC_FRAME_LAYER_2] = false;
			} else {
				ctrl_blk_.graphics_read_enable[GLCDC_FRAME_LAYER_2] = true;
			}

			// Save callback function
			ctrl_blk_.p_callback = cfg.p_callback;

			// Save setting of interrupt
			ctrl_blk_.interrupt.vpos_enable  = cfg.interrupt.vpos_enable;
			ctrl_blk_.interrupt.gr1uf_enable = cfg.interrupt.gr1uf_enable;
			ctrl_blk_.interrupt.gr2uf_enable = cfg.interrupt.gr2uf_enable;

			// If one of the interrupt setting is enable, setting value is
			// set after first vpos interrupt
			glcdc_interrupt_cfg_t initial_interrupt;
			if((true == cfg.interrupt.vpos_enable) || (true == cfg.interrupt.gr1uf_enable)
				|| (true == cfg.interrupt.gr2uf_enable)) {
				ctrl_blk_.first_vpos_interrupt_flag = false;
				initial_interrupt.vpos_enable = true;
				initial_interrupt.gr1uf_enable = false;
				initial_interrupt.gr2uf_enable = false;
			} else {
				ctrl_blk_.first_vpos_interrupt_flag = true;
				initial_interrupt.vpos_enable = false;
				initial_interrupt.gr1uf_enable = false;
				initial_interrupt.gr2uf_enable = false;
			}

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
			// Check parameters
			err = r_glcdc_open_param_check (p_cfg);
			if(GLCDC_SUCCESS != err) {
				return err;
			}
#endif

			// Check GLCDC resource is locked by another process
#if 0
			if(false == R_BSP_HardwareLock ((mcu_lock_t) BSP_LOCK_GLCDC)) {
				return GLCDC_ERR_LOCK_FUNC;
			}
			utils::format("R_GLCDC_Open: R_BSP_HardwareLock...\n");
#endif

			// Supply the peripheral clock to the GLCD module
			power_cfg::turn(GLC::get_peripheral());

			// Release GLCD from a SW reset status.
			release_software_reset_();

			// Set the dot clock frequency
			clock_set_(cfg);

			// Set the panel signal timing
			sync_signal_set_(cfg);

			// Configure the background screen
			background_screen_set_(cfg);

			// Configure the graphics plane layers
			for(uint32_t frame = 0; frame <= GLCDC_FRAME_LAYER_2; ++frame) {
				graphics_layer_set_(cfg.input[frame], (glcdc_frame_layer_t)frame);
				blend_condition_set_(cfg.blend[frame], (glcdc_frame_layer_t)frame);
				graphics_chromakey_set_(cfg.chromakey[frame], (glcdc_frame_layer_t)frame);
				clut_update_(cfg.clut[frame], (glcdc_frame_layer_t)frame);
			}

			// Configure the output control block
			output_block_set_(cfg);

			// Configure the color correction setting
			// (brightness, brightness and gamma correction)
			brightness_correction_(cfg.output.brightness);
			contrast_correction_(cfg.output.contrast);
			gamma_correction_(cfg.output.gamma);

			// Set the line number which is suppose to happen the line detect interrupt
			line_detect_number_set_(
				(uint16_t) (((cfg.output.vtiming.sync_width + cfg.output.vtiming.back_porch)
				+ cfg.output.vtiming.display_cyc) + BG_PLANE_HSYNC_POS_MIN));

			// Enable the GLCD detections and interrupts
			detect_setting_(cfg.detection);
			interrupt_setting_(initial_interrupt);

			// Allow reading of graphics data
			graphics_read_enable_();

			// Change GLCDC driver state
			ctrl_blk_.state = GLCDC_STATE_NOT_DISPLAYING;

			return true;
		}		


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start()
		{
			//
			// Release stop state of GLCDC
			//
			// R_GLCDC_Open function release stop state of GLCDC.
			//
			// Function select of multiplex pins (Display B)
			//
			port_map::turn(GLC::get_peripheral());

			glcdc_cfg_t glcdc_cfg;
			//
			// Set the BGEN.SWRST bit to 1 to release the GLCDC from a software reset
			//
			// R_GLCDC_Open function release the GLCDC from a software reset.
			//
			// Set the frequency of the LCD_CLK and PXCLK to suit the format
			// and set the PANELCLK.CLKEN bit to 1
			//
			glcdc_cfg.output.clksrc = GLCDC_CLK_SRC_INTERNAL;   			  // Select PLL clock
			glcdc_cfg.output.clock_div_ratio = GLCDC_PANEL_CLK_DIVISOR_24;    // 240 / 24 = 10 MHz
  																          // No frequency division
  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	          // Enable LCD_CLK output
			//
			// Definition of Background Screen
			//
			// Horizontal cycle (whole control screen)
			// Vertical cycle (whole control screen)
			// Horizontal Synchronization Signal Assertion Position
			glcdc_cfg.output.htiming.front_porch = 5;
			// Vertical Synchronization Assertion Position
			glcdc_cfg.output.vtiming.front_porch = 8;
			// Horizontal Active Pixel Start Position (min. 6 pixels)
			glcdc_cfg.output.htiming.back_porch = 40;
			glcdc_cfg.output.vtiming.back_porch = 8;
			// Horizontal Active Pixel Width
			glcdc_cfg.output.htiming.display_cyc = XSIZE_PHYS;
			// Vertical Active Display Width
			glcdc_cfg.output.vtiming.display_cyc = YSIZE_PHYS;
			// Vertical Active Display Start Position (min. 3 lines)
			glcdc_cfg.output.htiming.sync_width = 1;
			glcdc_cfg.output.vtiming.sync_width = 1;
			//
			// Graphic 1 configuration
			//
			glcdc_cfg.input[GLCDC_FRAME_LAYER_1].p_base = nullptr;	  // Disable Graphics 1

			//
			// Graphic 2 configuration
			//
  			// Enable reading of the frame buffer
			// Specify the start address of the frame buffer
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].p_base = (uint32_t *)BufferPTR[0];
			// Offset value from the end address of the line to the start address of the next line
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].offset = LINE_OFFSET;
			// Single Line Data Transfer Count
			// Single Frame Line Count

			// Frame Buffer Color Format RGB565
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].format = COLOR_FORMAT;
			glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].visible = true;
			// Display Screen Control (current graphics)
			glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].blend_control = GLCDC_BLEND_CONTROL_NONE;
			// Rectangular Alpha Blending Area Frame Display Control
			glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].frame_edge = false;
			// Graphics Area Frame Display Control
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].frame_edge = false;

  			// Alpha Blending Control (Per-pixel alpha blending)
			// Graphics Area Vertical Start Position
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].coordinate.y = 0;
			// Graphics Area Vertical Width
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].vsize = YSIZE_PHYS;
			// Graphics Area Horizontal Start Position
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].coordinate.x = 0;
			// Graphics Area Horizontal Width
			glcdc_cfg.input[GLCDC_FRAME_LAYER_2].hsize = XSIZE_PHYS;
			// Rectangular Alpha Blending Area Vertical Start Position
			glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].start_coordinate.x = 0;
			// Rectangular Alpha Blending Area Vertical Width
			glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].end_coordinate.x= YSIZE_PHYS;
			// Rectangular Alpha Blending Area Horizontal Start Position
			glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].start_coordinate.y = 0;
			// Rectangular Alpha Blending Area Horizontal Width
			glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].end_coordinate.y= XSIZE_PHYS;
  			// Graphic 2 Register Value Reflection Enable

			//
			// Timing configuration
			//
			//   Horizontal Synchronization Signal Reference Timing Offset (not support)
			//   Signal Reference Timing Select (not support)
			//   STVB Signal Assertion Timing
			//   STVB Signal Pulse Width
			//   STHB Signal Pulse Width
			// TCON0 Output Signal Select STVA (VSYNC)
			glcdc_cfg.output.tcon_vsync = GLCDC_TCON_PIN_0;
			// TCON2 Output Signal Select STHA (HSYNC)
			glcdc_cfg.output.tcon_hsync = GLCDC_TCON_PIN_2;
			// TCON3 Output Signal Select DE (DEN)
			glcdc_cfg.output.tcon_de    = GLCDC_TCON_PIN_3;
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
			// Output Data Format Select (RGB565)
			glcdc_cfg.output.format = GLCDC_OUT_FORMAT_16BITS_RGB565;
			// Pixel Order Control (B-G-R)
			glcdc_cfg.output.color_order = GLCDC_COLOR_ORDER_RGB;	// GLCDC_COLOR_ORDER_BGR;
			// Bit Endian Control (Little endian)
			glcdc_cfg.output.endian = GLCDC_ENDIAN_LITTLE;
			//
			// Brightness Adjustment
			//
			glcdc_cfg.output.brightness.b = BRIGHTNESS_;  // B
			glcdc_cfg.output.brightness.g = BRIGHTNESS_;  // G
			glcdc_cfg.output.brightness.r = BRIGHTNESS_;  // R
			//
			// Contrast Adjustment Value
			//
			glcdc_cfg.output.contrast.b = CONTRAST_;  // B
			glcdc_cfg.output.contrast.g = CONTRAST_;  // G
			glcdc_cfg.output.contrast.r = CONTRAST_;  // R

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
			// Enable detection of specified line notification in graphic 2
			glcdc_cfg.detection.vpos_detect = true;
			// Enable VPOS interrupt request
			glcdc_cfg.interrupt.vpos_enable = true;
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
			glcdc_cfg.p_callback = vsync_task_;
#if 0
			runtime_cfg.blend = glcdc_cfg.blend[GLCDC_FRAME_LAYER_2];
			runtime_cfg.input = glcdc_cfg.input[GLCDC_FRAME_LAYER_2];
			runtime_cfg.chromakey = glcdc_cfg.chromakey[GLCDC_FRAME_LAYER_2];
			//
			// Register Dave2D interrupt
			//
			R_BSP_InterruptWrite(BSP_INT_SRC_AL1_DRW2D_DRW_IRQ, (bsp_int_cb_t)drw_int_isr);
#endif
			//
			// Register Reflection
			//
			auto ret = open_(glcdc_cfg);
			if(!ret) {
				return false;
			}
			//
			// Init DMA
			//
#if 0
			R_DMACA_Init();
			//
			// Extended Bus Master Priority Control Register
			//
			BSC.EBMAPCR.BIT.PR1SEL = 0;
			BSC.EBMAPCR.BIT.PR2SEL = 3;
			BSC.EBMAPCR.BIT.PR3SEL = 1;
			BSC.EBMAPCR.BIT.PR4SEL = 2;
			BSC.EBMAPCR.BIT.PR5SEL = 4;
#endif
			return true;
		}
	};
}
