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
#include "RX600/dmac_mgr.hpp"
#include "glcdc_def.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GLCDC ピクセル・タイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class PIX_TYPE {
		CLUT1,		///<  1 bits / pixel
		CLUT4,		///<  4 bits / pixel
		CLUT8,		///<  8 bits / pixel
		RGB565,		///< 16 bits / pixel
		RGB888,		///< 32 bits / pixel
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  オペレーション・ステート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class glcdc_operating_status {
		CLOSED = 0,                ///< GLCDC closed.
		NOT_DISPLAYING = 1,        ///< Not Displaying (opened).
		DISPLAYING = 2             ///< Displaying.
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Interrupt enable setting
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct glcdc_interrupt_cfg_t
	{
    	bool vpos_enable;          // Line detection interrupt enable.
    	bool gr1uf_enable;         // Graphics plane1 underflow interrupt enable.
    	bool gr2uf_enable;         // Graphics plane2 underflow interrupt enable.
		glcdc_interrupt_cfg_t() : vpos_enable(false), gr1uf_enable(false), gr2uf_enable(false)
		{ }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Display output signal timing setting
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct glcdc_timing_t
	{
		uint16_t display_cyc;		///< Active video cycles or lines.
		uint16_t front_porch;		///< Front poach cycles or lines.
		uint16_t back_porch;		///< Back poach cycles or lines.
		uint16_t sync_width;		///< Sync signal asserting width.
	};


	/** Coordinate */
	struct glcdc_coordinate_t
	{
	    int16_t x;              // Coordinate X, this allows to set signed value.
	    int16_t y;              // Coordinate Y, this allows to set signed value.
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	GLCD hardware specific control block
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct glcdc_ctrl_t {
		glcdc_operating_status	state;		  // Status of GLCD module.
		bool			   is_entry;		  // Flag of subcribed GLCDC interrupt function.
		glcdc_coordinate_t active_start_pos;  // Zero coordinate for gra phics plane.
		uint16_t hsize;                       // Horizontal pixel size in a line.
		uint16_t vsize;                       // Vertical pixel size in a frame.
///		bool graphics_read_enable[FRAME_LAYER_NUM];  // Graphics data read enable.
		bool graphics_read_enable[2];  // Graphics data read enable.
		void (*callback)(void *);           // Pointer to callback function.
		bool first_vpos_interrupt_flag;       // First vpos interrupt after release 
											  // software reset.
		glcdc_interrupt_cfg_t interrupt;      // Interrupt setting values.

		volatile uint32_t	vpos_count;

		glcdc_ctrl_t() :
			state(glcdc_operating_status::CLOSED),
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


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GLCDC I/O 制御
		@param[in]	GLC		glcdc クラス
		@param[in]	XSIZE	X 方向ピクセルサイズ
		@param[in]	YSIZE	Y 方向ピクセルサイズ
		@param[in]	PXT		ピクセル・タイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC, int32_t XSIZE, int32_t YSIZE, PIX_TYPE PXT>
	class glcdc_io {

		static const uint32_t PIX_WIDTH  = 16;		///< 16 bits / pixel

		/* Number of graphics layers */
		static const uint32_t FRAME_LAYER_NUM  = 2;

		/* Number of color palletes for each graphic */
		static const uint32_t CLUT_PLANE_NUM   = 2;

		/* Number of clock division ratio setting items */
		static const uint32_t PANEL_CLKDIV_NUM = 13;






		/** Serial RGB data output delay cycles select (this function is not supported) */
		enum class SERIAL_OUTPUT_DELAY
		{
		    CYCLE_0 = 0,        // 0 cycles delay.
		    CYCLE_1 = 1,        // 1 cycle delay.
		    CYCLE_2 = 2,        // 2 cycles delay.
		    CYCLE_3 = 3,        // 3 cycles delay.
		};


		/** Serial RGB scan direction select (this function is not supported) */
		enum class SERIAL_SCAN_DIRECTION
		{
			FORWARD = 0,     // Forward scan.
			REVERSE = 1,     // Reverse scan.
		};


		/** RGB Color setting */
		struct color_t
		{
			// little endian
		    union
		    {
		        uint32_t argb;
		        struct
		        {
		            uint32_t b:8;      // blue.
		            uint32_t g:8;      // green.
		            uint32_t r:8;      // red.
		            uint32_t a:8;      // alpha.
		        } byte;
		    };
		};


		struct gamma_correction_t
		{
			static const uint32_t GAMMA_CURVE_GAIN_ELEMENT_NUM      = 16;
			static const uint32_t GAMMA_CURVE_THRESHOLD_ELEMENT_NUM = 15;

			struct correction_t
			{
				uint16_t gain[GAMMA_CURVE_GAIN_ELEMENT_NUM];               // Gain adjustment.
				uint16_t threshold[GAMMA_CURVE_THRESHOLD_ELEMENT_NUM];     // Start threshold.
			};

			bool enable;                  // Gamma Correction On/Off.
			correction_t* p_r;            // Gamma correction for R channel.
			correction_t* p_g;            // Gamma correction for G channel.
			correction_t* p_b;            // Gamma correction for B channel.
		};


		struct contrast_t
		{
			bool enable;			// Contrast Correction On/Off.
			uint8_t r;				// Contrast (gain) adjustment for R channel.
			uint8_t g;				// Contrast (gain) adjustment for G channel.
			uint8_t b;				// Contrast (gain) adjustment for B channel.
		};


		/** Brightness (DC) correction setting */
		struct brightness_t
		{
		    bool enable;        // Brightness Correction On/Off.
		    uint16_t r;         // Brightness (DC) adjustment for R channel.
		    uint16_t g;         // Brightness (DC) adjustment for G channel.
		    uint16_t b;         // Brightness (DC) adjustment for B channel.
		};


		/** Chroma key setting */
		struct chromakey_t
		{
		    bool enable;                         // Chroma key On/Off.
		    color_t before;                // Compare Color for -RGB.
		    color_t after;                 // Replace Color for ARGB.
		};


		/** Color correction setting */
		struct correction_t
		{
		    brightness_t brightness;       // Brightness setting.
		    contrast_t contrast;           // Contrast setting.
		    gamma_correction_t gamma;      // Gamma setting.
		};


		/** Dithering setup parameter */
		struct dithering_t
		{
		    bool dithering_on;                               // Dithering on/off.
		    glcdc_dithering_mode_t dithering_mode;           // Dithering mode.
		    glcdc_dithering_pattern_t dithering_pattern_a;   // Dithering pattern A.
		    glcdc_dithering_pattern_t dithering_pattern_b;   // Dithering pattern B.
		    glcdc_dithering_pattern_t dithering_pattern_c;   // Dithering pattern C.
		    glcdc_dithering_pattern_t dithering_pattern_d;   // Dithering pattern D.
		};


		/** Graphics plane input configuration */
		struct input_cfg_t
		{
			void*	 base;                 // Base address to the frame buffer.
			uint16_t hsize;                // Horizontal pixel size in a line.
			uint16_t vsize;                // Vertical pixel size in a frame.
			int32_t offset;                // offset value to next line.
			glcdc_in_format_t format;      // Input format setting.
			bool frame_edge;               // Show/hide setting of the frame of the graphics area.
			glcdc_coordinate_t coordinate; // Starting point of image.
			color_t bg_color;              // Color outside region.
		};


		/** Display output configuration */
		struct output_cfg_t
		{
			glcdc_timing_t                 htiming;                // Horizontal display cycle setting.
			glcdc_timing_t                 vtiming;                // Vertical display cycle setting.
			glcdc_out_format_t             format;                 // Output format setting.
			glcdc_endian_t                 endian;                 // Bit order of output data.
			glcdc_color_order_t            color_order;            // Color order in pixel.
			glcdc_sync_edge_t              sync_edge;              // Signal sync edge selection.

			color_t                  bg_color;               // Background color.

			brightness_t             brightness;             // Brightness setting.
			contrast_t               contrast;               // Contrast setting.
			gamma_correction_t       gamma;                  // Gamma correction setting.
			glcdc_correction_proc_order_t  correction_proc_order;  // Correction control route select.

			dithering_t              dithering;              // Dithering setting.

			glcdc_tcon_pin_t               tcon_hsync;             // GLCD TCON output pin select.
			glcdc_tcon_pin_t               tcon_vsync;             // GLCD TCON output pin select.
			glcdc_tcon_pin_t               tcon_de;                // GLCD TCON output pin select.
			glcdc_signal_polarity_t        data_enable_polarity;   // Data Enable signal polarity.
			glcdc_signal_polarity_t        hsync_polarity;         // Horizontal sync signal polarity.
			glcdc_signal_polarity_t        vsync_polarity;         // Vertical sync signal polarity.

			glcdc_clk_src_t                clksrc;                 // Clock Source selection.
			glcdc_panel_clk_div_t          clock_div_ratio;        // Clock divide ratio for dot clock.

			SERIAL_OUTPUT_DELAY		serial_output_delay;    // Serial RGB Data output delay cycle select (this function is not supported).
			SERIAL_SCAN_DIRECTION	serial_scan_direction;  // Serial RGB Scan direction select (this function is not supported).
		};


		/** Graphics layer blend setup parameter */
		struct blend_t
		{
			glcdc_blend_control_t blend_control;   // Layer fade-in/out , blending on/off.
			bool visible;                          // Visible or hide graphics.
			bool frame_edge;                       // Show/hide setting of the frame of rectangular alpha blending area.
			uint8_t fixed_blend_value;             // Blend value. Valid only when blend_control is _FIXED.
			uint8_t fade_speed;                    // Layer fade-in/out frame rate.
			glcdc_coordinate_t  start_coordinate;  // Start coordinate of rectangle blending.
			glcdc_coordinate_t  end_coordinate;    // End coordinate of rectangle blending.
		};


		/** CLUT configuration */
		struct clut_cfg_t
		{
			bool enable;        // CLUT update enable/disable.
			uint32_t * p_base;  // Pointer to CLUT source data.
			uint16_t start;     // Beginning of CLUT entry to be updated.
			uint16_t size;      // Size of CLUT entry to be updated.
		};


		/** Detect enable setting */
		struct detect_cfg_t
		{
			bool vpos_detect;   // Line detection enable.
			bool gr1uf_detect;  // Graphics plane1 underflow detection enable.
			bool gr2uf_detect;  // Graphics plane2 underflow detection enable.
		};


		/** Display callback parameter definition */
		struct callback_args_t
		{
			enum class EVENT {
				GR1_UNDERFLOW = 1,         // Graphics plane1 underflow occurs
				GR2_UNDERFLOW = 2,         // Graphics plane2 underflow occurs
				LINE_DETECTION = 3,        // Designated line is processed.
			};
			EVENT event;      // Event code.
		};


	public:
		static const uint32_t FRAME_LAYER_1 = 0;	///< Frame layer 1.
		static const uint32_t FRAME_LAYER_2 = 1;	///< Frame layer 2.

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Control Command
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class control_cmd {
			START_DISPLAY,			///< Start display command.
			STOP_DISPLAY,			///< Stop display command.
			SET_INTERRUPT,			///< Interrupt setting command.
			CLR_DETECTED_STATUS,	///< Detected status clear command.
			CHANGE_BG_COLOR,		///< Change background color in background screen.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エラー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error_t {
			SUCCESS = 0,                 ///< Success.
			INVALID_PTR,             ///< Pointer points to invalid memory location.
			LOCK_FUNC,               ///< GLCDC resource is in use by another process.
			INVALID_ARG,             ///< Invalid input parameter.
			INVALID_MODE,            ///< Unsupported or incorrect mode.
			NOT_OPEN,                ///< Requested channel is not configured or API not open.
			INVALID_TIMING_SETTING,      // Invalid timing parameter.
			INVALID_LAYER_SETTING,       // Invalid layer parameter.
			INVALID_ALIGNMENT,           // Invalid memory alignment found.
			INVALID_GAMMA_SETTING,       // Invalid gamma correction parameter.
			INVALID_UPDATE_TIMING,       // Invalid timing for register update.
			INVALID_CLUT_ACCESS,         // Invalid access to CLUT entry.
			INVALID_BLEND_SETTING,       // Invalid blending setting.
		};




		struct cfg_t
		{
		    /** Generic configuration for display devices */
		    input_cfg_t input[FRAME_LAYER_NUM];     // Graphics input frame setting.
		    output_cfg_t output;                    // Graphics output frame setting.
		    blend_t blend[FRAME_LAYER_NUM];         // Graphics layer blend setting.
		    chromakey_t chromakey[FRAME_LAYER_NUM]; // Graphics chroma key setting.
		    clut_cfg_t clut[FRAME_LAYER_NUM];       // Graphics CLUT setting.

		    /** Interrupt setting*/
		    detect_cfg_t     detection;           // Detection enable/disable setting.
		    glcdc_interrupt_cfg_t  interrupt;           // Interrupt enable/disable setting.

		    /** Configuration for display event processing */
		    void (*callback)(void *);                 // Pointer to callback function.
		};


		/** Runtime configuration */
		struct runtime_cfg_t
		{
		    /** Generic configuration for display devices */
		    input_cfg_t input;             // Graphics input frame setting
		    blend_t blend;                 // Graphics layer blend setting.
		    chromakey_t chromakey;         // Graphics chroma key setting.
		};


		/** status */
		struct status_t
		{
			glcdc_operating_status state;               // Status of GLCD module
		    bool state_vpos;           // Status of line detection.
		    bool state_gr1uf;          // Status of graphics plane1 underflow.
		    bool state_gr2uf;          // Status of graphics plane2 underflow.
		    glcdc_fade_status_t fade_status[FRAME_LAYER_NUM];  // Status of fade-in/fade-out status
		};

		private:

		static const uint32_t BYTES_PER_LINE   = ((PIX_WIDTH * XSIZE) / 8);
		static const uint32_t LINE_OFFSET      = (((BYTES_PER_LINE + 63) / 64) * 64);
		static const uint32_t VXSIZE_PHYS      = ((LINE_OFFSET * 8) / PIX_WIDTH);
		static const uint32_t BYTES_PER_BUFFER = (LINE_OFFSET * YSIZE);

		static const uint32_t BRIGHTNESS_ = 0x200;
		static const uint32_t CONTRAST_   = 0x80;

		static const uint32_t ADDRESS_ALIGNMENT_64B = 0x0000003F;

		static const uint32_t GAMMA_CURVE_GAIN_ELEMENT_NUM      = 16;
		static const uint32_t GAMMA_CURVE_THRESHOLD_ELEMENT_NUM = 15;

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
		static const int32_t BG_PLANE_H_CYC_MIN  = 24;             // BG_PERI.FH (Min=24)
		static const int32_t BG_PLANE_V_CYC_MIN  = 20;             // BG_PERI.FV (Min=20)
		static const int32_t BG_PLANE_HSYNC_POS_MIN = 1;           // BG_HSYNC.HP (Min=1)
		static const int32_t BG_PLANE_VSYNC_POS_MIN = 1;           // BG_HSYNC.VP (Min=1)
		static const int32_t BG_PLANE_H_CYC_ACTIVE_SIZE_MIN = 16;  // BG_HSIZE.HW (Min=16)
		static const int32_t BG_PLANE_V_CYC_ACTIVE_SIZE_MIN = 16;  // BG_VSIZE.VW (Min=16)
		static const int32_t BG_PLANE_H_ACTIVE_POS_MIN = 6;        // BG_HSIZE.HP (Min=6)
		static const int32_t BG_PLANE_V_ACTIVE_POS_MIN = 3;        // BG_VSIZE.VP (Min=3)

		// GRn_FLM3_LNOFF(positive num min=-32768)
		static const int32_t GR_PLANE_LNOFF_POS_MIN = -32768;
		static const int32_t GR_PLANE_H_CYC_ACTIVE_SIZE_MIN = 16;  // GRn_AB3.GRCHW (Min=16)
		static const int32_t GR_PLANE_V_CYC_ACTIVE_SIZE_MIN = 16;  // GRn_AB2.GRCVW (Min=16)
		static const int32_t GR_PLANE_H_ACTIVE_POS_MIN = 5;        // GRn_AB2.GRCHS (Min=5)
		static const int32_t GR_PLANE_V_ACTIVE_POS_MIN = 2;        // GRn_AB2.GRCVS (Min=2)
		// Horizontal front porch parameter (MIN=3)
		static const int32_t BG_PLANE_H_FRONT_PORCH_MIN = 3;
		// Vertical front porch parameter (MIN=2)
		static const int32_t BG_PLANE_V_FRONT_PORCH_MIN = 2;
		// Horizontal back porch parameter (MIN=1)
		static const int32_t BG_PLANE_H_BACK_PORCH_MIN = 1;
		// Vertical back porch parameter (MIN=1)
		static const int32_t BG_PLANE_V_BACK_PORCH_MIN = 1;
		// Horizontal sync signal width parameter (MIN=4)
		static const int32_t BG_PLANE_H_SYNC_WIDTH_MIN = 4;
		// Vertical sync signal width parameter (MIN=1)
		static const int32_t BG_PLANE_V_SYNC_WIDTH_MIN = 1;  
		static const int32_t GR_BLEND_H_ACTIVE_POS_MIN = 5;       // GRn_AB5_GRCHS (Min=5)
		static const int32_t GR_BLEND_V_ACTIVE_POS_MIN = 2;       // GRn_AB4_GRCVS (Min=2)
		static const int32_t GR_BLEND_H_CYC_ACTIVE_SIZE_MIN = 1;  // GRn_AB5_GRCHW (Min=1)
		static const int32_t GR_BLEND_V_CYC_ACTIVE_SIZE_MIN = 1;  // GRn_AB4_GRCVW (Min=1)

		static const uint32_t SYSCNT_PANEL_CLK_DCDR_MASK = 0x3F;


		struct TCON_SIGNAL_SELECT {
		    static const uint32_t STVA_VS = 0;  // STVA/VS
		    static const uint32_t STVB_VE = 1;  // STVB/VE
		    static const uint32_t STHA_HS = 2;  // STH/SP/HS
		    static const uint32_t STHB_HE = 3;  // STB/LP/HE
		    static const uint32_t DE      = 7;  // DE
		};


		struct FADING_CONTROL_INITIAL_ALPHA {
			// Initial alpha value setting for a graphics plane is zero.
			static const uint32_t MIN = 0x00;
			// Initial alpha value setting for a graphics plane is maximum.
			static const uint32_t MAX = 0xff;
		};


		struct PLANE_BLEND {
    		static const uint32_t TRANSPARENT     = 1; // Current graphics layer is transparent
								 					   // and the lower layer is displayed.
			static const uint32_t NON_TRANSPARENT = 2; // Current graphics layer is displayed.
			static const uint32_t ON_LOWER_LAYER  = 3; // Current graphics layer is blended with
								 					   // the lower layer.
		};


		static const uint32_t CLUT_PLANE_0 = 0;    // GLCD CLUT plane 0.
		static const uint32_t CLUT_PLANE_1 = 1;    // GLCD CLUT plane 1.


		struct DITHERING_OUTPUT_FORMAT {
			static const uint32_t RGB888 = 0;  // Dithering output format RGB888.
			static const uint32_t RGB666 = 1;  // Dithering output format RGB666.
			static const uint32_t RGB565 = 2;  // Dithering output format RGB565.
		};


		static glcdc_ctrl_t	ctrl_blk_;
		uint8_t				intr_lvl_;
		error_t				last_error_;


		void release_software_reset_()
		{
			GLC::BGEN.SWRST = 1;
		}


		void clock_set_(const cfg_t& cfg)
		{
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
				GLC::TCONSTVB2.SEL = TCON_SIGNAL_SELECT::STHA_HS;
				break;
			case GLCDC_TCON_PIN_2:
				/* Hsync(STHA) ->  TCON2 */
				GLC::TCONSTHA2.SEL = TCON_SIGNAL_SELECT::STHA_HS;
				break;
			case GLCDC_TCON_PIN_3:
				/* Hsync(STHA) -> TCON3 */
				GLC::TCONSTHB2.SEL = TCON_SIGNAL_SELECT::STHA_HS;
				break;
			case GLCDC_TCON_PIN_0: /* Intentionally go though to the default case */
			default:
				/* Hsync(STHA) -> TCON0 */
				GLC::TCONSTVA2.SEL = TCON_SIGNAL_SELECT::STHA_HS;
				break;
			}

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
				GLC::TCONSTVA2.SEL = TCON_SIGNAL_SELECT::STVA_VS;
				break;
			case GLCDC_TCON_PIN_2:
				/* Vsync(STVA) -> TCON2 */
				GLC::TCONSTHA2.SEL = TCON_SIGNAL_SELECT::STVA_VS;
				break;
			case GLCDC_TCON_PIN_3:
				/* Vsync(STVA) -> TCON3 */
				GLC::TCONSTHB2.SEL = TCON_SIGNAL_SELECT::STVA_VS;
				break;
			case GLCDC_TCON_PIN_1: /* Intentionally go though to the default case */
			default:
				/* Vsync(STVA) -> TCON1 */
				GLC::TCONSTVB2.SEL = TCON_SIGNAL_SELECT::STVA_VS;
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
			switch(tcon) {
			case GLCDC_TCON_PIN_0:
				/* DE -> TCON0 */
				GLC::TCONSTVA2.SEL = TCON_SIGNAL_SELECT::DE;
				break;
			case GLCDC_TCON_PIN_1:
				// DE -> TCON1
				GLC::TCONSTVB2.SEL = TCON_SIGNAL_SELECT::DE;
				break;
			case GLCDC_TCON_PIN_3:
				// DE -> TCON3
				GLC::TCONSTHB2.SEL = TCON_SIGNAL_SELECT::DE;
				break;
			case GLCDC_TCON_PIN_2: /* Intentionally go though to the default case */
			default:
				// DE -> TCON2
				GLC::TCONSTHA2.SEL = TCON_SIGNAL_SELECT::DE;
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


		void sync_signal_set_(const cfg_t& cfg)
		{
			GLC::CLKPHASE.LCDEDG   = cfg.output.sync_edge;
			GLC::CLKPHASE.TCON0EDG = cfg.output.sync_edge;
			GLC::CLKPHASE.TCON1EDG = cfg.output.sync_edge;
			GLC::CLKPHASE.TCON2EDG = cfg.output.sync_edge;
			GLC::CLKPHASE.TCON3EDG = cfg.output.sync_edge;

			GLC::TCONTIM.OFFSET = 0; // 1 pixel
			GLC::TCONTIM.HALF   = 0; // 1 pixel (No delay)

			hsync_set_(cfg.output.tcon_hsync, cfg.output.htiming, cfg.output.hsync_polarity);
			vsync_set_(cfg.output.tcon_vsync, cfg.output.vtiming, cfg.output.vsync_polarity);
			data_enable_set_(cfg.output.tcon_de, cfg.output.vtiming, cfg.output.htiming,
				cfg.output.data_enable_polarity);
		}


		void background_screen_set_(const cfg_t& cfg)
		{
			uint32_t hsync_total_cyc;
			uint32_t vsync_total_cyc;

			hsync_total_cyc = (((cfg.output.htiming.front_porch  + cfg.output.htiming.sync_width)
							  +  cfg.output.htiming.display_cyc) + cfg.output.htiming.back_porch);
			vsync_total_cyc = (((cfg.output.vtiming.front_porch  + cfg.output.vtiming.sync_width)
							  +  cfg.output.vtiming.display_cyc) + cfg.output.vtiming.back_porch);
//			utils::format("Total LCD count: %d, %d\n") % hsync_total_cyc % vsync_total_cyc;
			GLC::BGPERI.FH = (hsync_total_cyc - 1) & BG_PERI_FH_MASK;
			GLC::BGPERI.FV = (vsync_total_cyc - 1) & BG_PERI_FV_MASK;

			GLC::BGSYNC.HP = (cfg.output.htiming.front_porch - BG_PLANE_H_CYC_MARGIN_MIN)
							 & BG_SYNC_HP_MASK;
			GLC::BGSYNC.VP = (cfg.output.vtiming.front_porch - BG_PLANE_V_CYC_MARGIN_MIN)
							 & BG_SYNC_VP_MASK;

			GLC::BGHSIZE.HP = (uint16_t) ((cfg.output.htiming.front_porch
				- BG_PLANE_H_CYC_MARGIN_MIN)
				+ cfg.output.htiming.sync_width + cfg.output.htiming.back_porch)
				& BG_HSIZE_HP_MASK;

			GLC::BGVSIZE.VP = (uint16_t) ((cfg.output.vtiming.front_porch
				- BG_PLANE_V_CYC_MARGIN_MIN)
				+ cfg.output.vtiming.sync_width + cfg.output.vtiming.back_porch)
				& BG_VSIZE_VP_MASK;
			/* ---- Set the width of Background screen ---- */
			GLC::BGHSIZE.HW = cfg.output.htiming.display_cyc & BG_HSIZE_HW_MASK;
			GLC::BGVSIZE.VW = cfg.output.vtiming.display_cyc & BG_VSIZE_VW_MASK;

			/* ---- Set the Background color ---- */
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


		void gr_plane_format_set_(glcdc_in_format_t format, uint32_t frame)
		{
			if(frame == 0) {
				GLC::GR1FLM6.FORMAT = (uint32_t)format;
			} else { 
				GLC::GR2FLM6.FORMAT = (uint32_t)format;
			}
		}


		void graphics_layer_set_(const input_cfg_t& input, uint32_t frame)
		{
			uint32_t bit_size = get_bit_size_(input.format);

    		// If enable graphics data read from memory
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				return;
			}

			gr_plane_format_set_(input.format, frame);

			/* ---- Set the base address of graphics plane ---- */
			if(frame == 0) {
				GLC::GR1FLM2 = (uint32_t)input.base;
			} else {
				GLC::GR2FLM2 = (uint32_t)input.base;
			}

			/* ---- Set the background color on graphics plane ---- */
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
			// Convert to byte size of Single line data transfer, round up fractions below
			// the decimal point
			uint32_t line_byte_num = ((bit_size * input.hsize) / 8);
			if(0 != ((bit_size * input.hsize) % 8)) {
				line_byte_num += 1;
			}

			// Convert to Single line data transfer count, round up fractions below the
			// decimal point
			uint32_t line_trans_num = (line_byte_num >> 6);
			if(0 != (line_byte_num & ADDRESS_ALIGNMENT_64B)) {
				line_trans_num += 1;
			}
			if(frame == 0) {
				GLC::GR1FLM5.DATANUM = (line_trans_num - 1) & GRn_FLM5_DATANUM_MASK;
			} else {
				GLC::GR2FLM5.DATANUM = (line_trans_num - 1) & GRn_FLM5_DATANUM_MASK;
			}

			/* ---- Set the line offset address for accessing the graphics data ---- */
			if(frame == 0) {
				GLC::GR1FLM5.LNNUM = ((uint32_t)(input.vsize - 1)) & GRn_FLM5_LNNUM_MASK;
			} else {
				GLC::GR2FLM5.LNNUM = ((uint32_t)(input.vsize - 1)) & GRn_FLM5_LNNUM_MASK;
			}

			// ---- Set the line offset address for accessing the graphics data on graphics
			// plane ----
			if(frame == 0) {
				GLC::GR1FLM3.LNOFF = (uint32_t)input.offset & GRn_FLM3_LNOFF_MASK;
			} else {
				GLC::GR2FLM3.LNOFF = (uint32_t)input.offset & GRn_FLM3_LNOFF_MASK;
			}

			if(frame == 0) {
				GLC::GR1AB2.GRCVW = input.vsize & GRn_AB2_GRCVW_MASK;
			} else {
				GLC::GR2AB2.GRCVW = input.vsize & GRn_AB2_GRCVW_MASK;
			}

			if(frame == 0) {
				GLC::GR1AB2.GRCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
									+ input.coordinate.y)) & GRn_AB2_GRCVS_MASK;
			} else {
				GLC::GR2AB2.GRCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
									+ input.coordinate.y)) & GRn_AB2_GRCVS_MASK;
			}

			/* ---- Set the width of the graphics layers ---- */
			if(frame == 0) {
				GLC::GR1AB3.GRCHW = input.hsize & GRn_AB3_GRCHW_MASK;
			} else {
				GLC::GR2AB3.GRCHW = input.hsize & GRn_AB3_GRCHW_MASK;
			}

			/* ---- Set the start position of the graphics layers ---- */
			// gp_gr[frame]->grxab3.bit.grchs = ((uint32_t)(ctrl_blk_.active_start_pos.x
			//								 + input.coordinate.x)) & GRn_AB3_GRCHS_MASK;
			if(frame == 0) {
				GLC::GR1AB3.GRCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
									+ input.coordinate.x)) & GRn_AB3_GRCHS_MASK;
			} else {
				GLC::GR2AB3.GRCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
									+ input.coordinate.x)) & GRn_AB3_GRCHS_MASK;
			}

			if(frame == 0) {
				GLC::GR1AB1.GRCDISPON = input.frame_edge ? 1 : 0;
			} else {
				GLC::GR2AB1.GRCDISPON = input.frame_edge ? 1 : 0;
			}
		}


		void blend_condition_set_(const blend_t& blend, uint32_t frame)
		{
			/* if enable graphics data read from memory */
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				/* Set layer transparent */
				if(frame == 0) {
					GLC::GR1AB1.DISPSEL = PLANE_BLEND::TRANSPARENT & GRn_AB1_DISPSEL_MASK;
				} else {
					GLC::GR2AB1.DISPSEL = PLANE_BLEND::TRANSPARENT & GRn_AB1_DISPSEL_MASK;
				}
				return;
			}

			switch(blend.blend_control)
			{
			case GLCDC_BLEND_CONTROL_NONE:

				if(frame == 0) {
					GLC::GR1AB1.ARCON = 0;
				} else {
					GLC::GR2AB1.ARCON = 0;
				}
				if(true == blend.visible) {
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = PLANE_BLEND::NON_TRANSPARENT & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = PLANE_BLEND::NON_TRANSPARENT & GRn_AB1_DISPSEL_MASK;
					}
				} else {
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = PLANE_BLEND::TRANSPARENT & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = PLANE_BLEND::TRANSPARENT & GRn_AB1_DISPSEL_MASK;
					}
				}
				break;
			case GLCDC_BLEND_CONTROL_FADEIN:
			case GLCDC_BLEND_CONTROL_FADEOUT:
			case GLCDC_BLEND_CONTROL_FIXED:
				// gp_gr[frame]->grxab5.bit.archs = 
                //    
				if(frame == 0) {
					GLC::GR1AB5.ARCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
										+ blend.start_coordinate.x)) & GRn_AB5_ARCHS_MASK;
				} else {
					GLC::GR2AB5.ARCHS = ((uint32_t)(ctrl_blk_.active_start_pos.x
										+ blend.start_coordinate.x)) & GRn_AB5_ARCHS_MASK;
				}

				if(frame == 0) {
					GLC::GR1AB4.ARCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
										+ blend.start_coordinate.y))& GRn_AB4_ARCVS_MASK;
				} else {
					GLC::GR2AB4.ARCVS = ((uint32_t)(ctrl_blk_.active_start_pos.y
										+ blend.start_coordinate.y))& GRn_AB4_ARCVS_MASK;
				}

				/* ---- Set the width of the graphics layers ---- */
				if(frame == 0) {
					GLC::GR1AB5.ARCHW = (blend.end_coordinate.x - blend.start_coordinate.x)
										& GRn_AB5_ARCHW_MASK;
				} else {
					GLC::GR2AB5.ARCHW = (blend.end_coordinate.x - blend.start_coordinate.x)
										& GRn_AB5_ARCHW_MASK;
				}
				if(frame == 0) {
					GLC::GR1AB4.ARCVW = (blend.end_coordinate.y - blend.start_coordinate.y)
					                    & GRn_AB4_ARCVW_MASK;
				} else {
					GLC::GR2AB4.ARCVW = (blend.end_coordinate.y - blend.start_coordinate.y)
					                    & GRn_AB4_ARCVW_MASK;
				}

				/*---- Enable rectangular alpha blending ---- */
				if(frame == 0) {
					GLC::GR1AB1.ARCON = 1;
				} else {
					GLC::GR2AB1.ARCON = 1;
				}

            	// gp_gr[frame]->grxab6.bit.arcrate = 0x00;
				if(frame == 0) {
					GLC::GR1AB6.ARCRATE = 0x00;
				} else {
					GLC::GR2AB6.ARCRATE = 0x00;
				}

	            if(GLCDC_BLEND_CONTROL_FADEIN == blend.blend_control) {
					if(frame == 0) {
						GLC::GR1AB7.ARCDEF
							= FADING_CONTROL_INITIAL_ALPHA::MIN & GRn_AB7_ARCDEF_MASK;
					} else {
						GLC::GR2AB7.ARCDEF
							= FADING_CONTROL_INITIAL_ALPHA::MIN & GRn_AB7_ARCDEF_MASK;
					}

					if(frame == 0) {
						GLC::GR1AB6.ARCCOEF = (uint32_t)blend.fade_speed & GRn_AB6_ARCCOEF_MASK;
					} else {
						GLC::GR2AB6.ARCCOEF = (uint32_t)blend.fade_speed & GRn_AB6_ARCCOEF_MASK;
					}
            	} else if (GLCDC_BLEND_CONTROL_FADEOUT == blend.blend_control) {
					if(frame == 0) {
						GLC::GR1AB7.ARCDEF
							= FADING_CONTROL_INITIAL_ALPHA::MAX & GRn_AB7_ARCDEF_MASK;
					} else {
						GLC::GR2AB7.ARCDEF
							= FADING_CONTROL_INITIAL_ALPHA::MAX & GRn_AB7_ARCDEF_MASK;
					}

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

					if(frame == 0) {
						GLC::GR1AB6.ARCCOEF = 0x000;
					} else {
						GLC::GR2AB6.ARCCOEF = 0x000;
					}
				}

               	// gp_gr[frame]->grxab1.bit.arcdispon = 1;
				if(frame == 0) {
					GLC::GR1AB1.ARCDISPON = blend.frame_edge == true ? 1 : 0;
				} else {
					GLC::GR2AB1.ARCDISPON = blend.frame_edge == true ? 1 : 0;
				}

				if(frame == 0) {
					GLC::GR1AB1.DISPSEL = PLANE_BLEND::ON_LOWER_LAYER & GRn_AB1_DISPSEL_MASK;
				} else {
					GLC::GR2AB1.DISPSEL = PLANE_BLEND::ON_LOWER_LAYER & GRn_AB1_DISPSEL_MASK;
				}
				break;
			case GLCDC_BLEND_CONTROL_PIXEL:
			default:
				if(frame == 0) {
					GLC::GR1AB1.ARCON = 0;
				} else {
					GLC::GR2AB1.ARCON = 0;
				}

				if(true == blend.visible) {
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = PLANE_BLEND::ON_LOWER_LAYER & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = PLANE_BLEND::ON_LOWER_LAYER & GRn_AB1_DISPSEL_MASK;
					}
				} else {
					/* Set layer transparent */
					if(frame == 0) {
						GLC::GR1AB1.DISPSEL = PLANE_BLEND::TRANSPARENT & GRn_AB1_DISPSEL_MASK;
					} else {
						GLC::GR2AB1.DISPSEL = PLANE_BLEND::TRANSPARENT & GRn_AB1_DISPSEL_MASK;
					}
				}
				break;
			}
		}


		void graphics_chromakey_set_(const chromakey_t& chromakey, uint32_t frame)
		{
			/* if enable graphics data read from memory */
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				return;
			}

			if(true == chromakey.enable) {
				/* ---- Chroma key enable ---- */
				if(frame == 0) {
					GLC::GR1AB7.CKON = 1;
				} else {
					GLC::GR2AB7.CKON = 1;
				}

				/* ---- Before ---- */
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
				if(frame == 0) {
					GLC::GR1AB7.CKON = 0;
				} else {
					GLC::GR2AB7.CKON = 0;
				}
			}
		}


		uint32_t is_clutplane_selected_(uint32_t frame)
		{
			if(frame == 0) {
				return GLC::GR1CLUTINT.SEL();
			} else {
				return GLC::GR2CLUTINT.SEL();
			}
		}


		void clutplane_select_(uint32_t frame, uint32_t clut_plane)
		{
			if(frame == 0) {
				GLC::GR1CLUTINT.SEL = clut_plane;
			} else {
				GLC::GR2CLUTINT.SEL = clut_plane;
			}
		}


		void clut_set_(uint32_t frame, uint32_t clut_plane, uint32_t entry, uint32_t data)
		{
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


		void clut_update_(const clut_cfg_t& clut, uint32_t frame)
		{
			/* If enable graphics data read from memory */
			if(false == ctrl_blk_.graphics_read_enable[frame]) {
				return;
			}

			if(true == clut.enable) {
				const uint32_t* p_base = clut.p_base;

				uint32_t set_clutplane;
				if(CLUT_PLANE_1 == is_clutplane_selected_(frame)) {
					set_clutplane = CLUT_PLANE_0;
				} else {
					set_clutplane = CLUT_PLANE_1;
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


		void output_block_set_(const cfg_t& cfg)
		{
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
				GLC::PANELDTHA.FORM = DITHERING_OUTPUT_FORMAT::RGB888;
				break;
			case GLCDC_OUT_FORMAT_16BITS_RGB565:
				GLC::OUTSET.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_16BITS_RGB565;
				GLC::PANELDTHA.FORM = DITHERING_OUTPUT_FORMAT::RGB565;
				break;
			case GLCDC_OUT_FORMAT_18BITS_RGB666:
				GLC::OUTSET.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_18BITS_RGB666;
				GLC::PANELDTHA.FORM = DITHERING_OUTPUT_FORMAT::RGB666;
				break;
			case GLCDC_OUT_FORMAT_24BITS_RGB888:
			default:
				GLC::OUTSET.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_24BITS_RGB888;
				GLC::PANELDTHA.FORM = DITHERING_OUTPUT_FORMAT::RGB888;
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


		void brightness_correction_(const brightness_t& brightness)
		{

			if(true == brightness.enable) {
				/* ---- Sets brightness correction register for each color in a pixel. ---- */
				GLC::BRIGHT1.BRTG = brightness.g & OUT_BRIGHT1_BRTG_MASK;
				GLC::BRIGHT2.BRTB = brightness.b & OUT_BRIGHT2_BRTB_MASK;
				GLC::BRIGHT2.BRTR = brightness.r & OUT_BRIGHT2_BRTR_MASK;
			} else {
				/* --- If brightness setting in configuration is 'off', apply default value --- */
				GLC::BRIGHT1.BRTG = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT1_BRTG_MASK;
				GLC::BRIGHT2.BRTB = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT2_BRTB_MASK;
				GLC::BRIGHT2.BRTR = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT2_BRTR_MASK;
			}
		}


		void contrast_correction_(const contrast_t& contrast)
		{
			if(true == contrast.enable) {
				/* ---- Sets the contrast correction register for each color in a pixel. ---- */
				GLC::CONTRAST.CONTG = contrast.g & OUT_CONTRAST_CONTG_MASK;
				GLC::CONTRAST.CONTB = contrast.b & OUT_CONTRAST_CONTB_MASK;
				GLC::CONTRAST.CONTR = contrast.r & OUT_CONTRAST_CONTR_MASK;
			} else {
				/* ---- If the contrast setting in the configuration is set to 'off',
						apply default value ---- */
				GLC::CONTRAST.CONTG = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTG_MASK;
				GLC::CONTRAST.CONTB = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTB_MASK;
				GLC::CONTRAST.CONTR = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTR_MASK;
			}
		}


		void gamma_correction_(const gamma_correction_t& gamma)
		{
			if(true == gamma.enable) {
				/* ---- Gamma correction enable and set gamma setting ---- */
				GLC::GAMSW.GAMON = 1;
#if 0
				/* Green */
				uint32_t* lut_table;
				p_lut_table = (uint32_t*)(&GLCDC.GAMGLUT1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2) {
					/* GAMGLUTx - Gamma Correction G Table Setting Register x */
					*lut_table = ((((uint32_t)p_gamma->p_g->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
						| ((uint32_t)p_gamma->p_g->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
					lut_table++;
				}

				lut_table = (uint32_t*)(&GLCDC.GAMGAREA1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3) {
					/* GAMGAREAx - Gamma Correction G Area Setting Register x */
					*lut_table = ((((uint32_t)p_gamma->p_g->threshold[i] & GAMX_AREAX_MASK) << 20)
							| (((uint32_t)p_gamma->p_g->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
							| ((uint32_t)p_gamma->p_g->threshold[i + 2] & GAMX_AREAX_MASK));
					lut_table++;
				}

				/* Blue */
				lut_table = (uint32_t *)(&GLCDC.GAMBLUT1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2) {
					/* GAMBLUTx - Gamma Correction B Table Setting Register x */
					*lut_table = ((((uint32_t)p_gamma->p_b->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
                    		| ((uint32_t)p_gamma->p_b->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
					lut_table++;
				}

				lut_table = (uint32_t*)(&GLCDC.GAMBAREA1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3) {
					/* GAMBAREAx - Gamma Correction B Area Setting Register x */
					*lut_table = ((((uint32_t)p_gamma->p_b->threshold[i] & GAMX_AREAX_MASK) << 20)
							| (((uint32_t)p_gamma->p_b->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
							| ((uint32_t)p_gamma->p_b->threshold[i + 2] & GAMX_AREAX_MASK));
					lut_table++;
				}

				/* Red */
				lut_table = (uint32_t*)(&GLCDC.GAMRLUT1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2) {
					/* GAMRLUTx - Gamma Correction R Table Setting Register x */
					*lut_table = ((((uint32_t)p_gamma->p_r->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
							| ((uint32_t)p_gamma->p_r->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
					lut_table++;
				}

				lut_table = (uint32_t*)(&GLCDC.GAMRAREA1);
				for(uint32_t i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3) {
					/* GAMRAREAx - Gamma Correction R Area Setting Register x */
					*lut_table = ((((uint32_t)p_gamma->p_r->threshold[i] & GAMX_AREAX_MASK) << 20)
							| (((uint32_t)p_gamma->p_r->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
							| ((uint32_t)p_gamma->p_r->threshold[i + 2] & GAMX_AREAX_MASK));
					lut_table++;
				}
#endif
			} else {
				/* ---- Gamma Correction Disable ---- */
				GLC::GAMSW.GAMON = 0;
			}
		}


		void line_detect_number_set_(uint32_t line)
		{
			GLC::GR2CLUTINT.LINE = line & GRn_CLUTINT_LINE_MASK;
		}


		void detect_setting_(const detect_cfg_t& detection)
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


		static void interrupt_setting_(const glcdc_interrupt_cfg_t& interrupt)
		{
			if(interrupt.vpos_enable) {
				GLC::INTEN.VPOSINTEN = 1;
			} else {
				GLC::INTEN.VPOSINTEN = 0;
				// 割り込みを止める場合は注意
///				EN(GLCDC,VPOS) = 0;
///				while(0 != IS(GLCDC,VPOS)) {
///					asm("nop");
///				}
			}

			if(interrupt.gr1uf_enable) {
				GLC::INTEN.GR1UFINTEN = 1;
			} else {
				GLC::INTEN.GR1UFINTEN = 0;
///				EN(GLCDC,GR1UF) = 0;
///				while(0 != IS(GLCDC,GR1UF)) {
///					asm("nop");
///				}
			}

			if(interrupt.gr2uf_enable) {
				GLC::INTEN.GR2UFINTEN = 1;
			} else {
				GLC::INTEN.GR2UFINTEN = 0;
///				while (0 != IS(GLCDC,GR2UF)) {
///					asm("nop");
///				}
			}

			/* Set GROUPAL1 interrupt request to enable, if GLCDC interrupt parameter is enabled
			Set GROUPAL1 interrupt request to disable, if GLCDC interrupt parameter is disabled */
			if(interrupt.vpos_enable || interrupt.gr1uf_enable || interrupt.gr2uf_enable) {
///				R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_ENABLE, (void *) &grpal1.ipl);
			} else {
///				R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_DISABLE, NULL);
			}
		}


		void graphics_read_enable_()
		{
			if(true == ctrl_blk_.graphics_read_enable[FRAME_LAYER_1]) {
				GLC::GR1FLMRD.RENB = 1;    /* Enable reading. */
			} else {
				GLC::GR1FLMRD.RENB = 0;    /* Disable reading. */
			}

			if(true == ctrl_blk_.graphics_read_enable[FRAME_LAYER_2]) {
				GLC::GR2FLMRD.RENB = 1;    /* Enable reading. */
			} else {
				GLC::GR2FLMRD.RENB = 0;    /* Disable reading. */
			}
		}


		static void gr_plane_update_(uint32_t frame)
		{
			if(frame = 0) {
				GLC::GR1VEN.VEN = 1;
			} else {
				GLC::GR2VEN.VEN = 1;
			}
		}


		static bool is_gr_plane_updating_(uint32_t frame)
		{
			if(frame == 0) {
				return GLC::GR1VEN.VEN();
			} else {
				return GLC::GR2VEN.VEN();
			}
		}


		static void gamma_update_()
		{
			GLC::GAMGVEN.VEN = 1;
			GLC::GAMBVEN.VEN = 1;
			GLC::GAMRVEN.VEN = 1;
		}


		static bool is_gamma_updating_()
		{
			return (GLC::GAMGVEN.VEN() | GLC::GAMBVEN.VEN() | GLC::GAMRVEN.VEN());
		}


		static bool vpos_int_status_check_()
		{
			return GLC::STMON.VPOS();
		}


		static bool gr1uf_int_status_check_()
		{
			return GLC::STMON.GR1UF();
		}


		static bool gr2uf_int_status_check_()
		{
			return GLC::STMON.GR2UF();
		}


		static void vpos_int_status_clear_()
		{
			GLC::STCLR.VPOSCLR = 1;
		}


		static void gr1uf_int_status_clear_()
		{
			GLC::STCLR.GR1UFCLR = 1;
		}


		static void gr2uf_int_status_clear_()
		{
			GLC::STCLR.GR2UFCLR = 1;
		}


		static void output_ctrl_update_()
		{
			GLC::OUTVEN.VEN = 1;
		}


		static bool is_output_ctrl_updating_()
		{
			return GLC::OUTVEN.VEN();
		}


		static bool is_register_reflecting_()
		{
			return GLC::BGEN.VEN();
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
    ret = R_GLCDC_LayerChange(FRAME_LAYER_2, &runtime_cfg);	// Graphic 2 Register Value Reflection Enable
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


		static void line_detect_isr_()
		{
			callback_args_t args;

			if(ctrl_blk_.callback != nullptr) {
				args.event = callback_args_t::EVENT::LINE_DETECTION;
				ctrl_blk_.callback((void *)&args);
			}

			vpos_int_status_clear_();

			if(!ctrl_blk_.first_vpos_interrupt_flag) {
				// Clear interrupt flag in the register of the GLCD module
				gr1uf_int_status_clear_();
				gr2uf_int_status_clear_();

				// Set the GLCD interrupts
				interrupt_setting_(ctrl_blk_.interrupt);

				// Set the first VPOS interrupt flag
				ctrl_blk_.first_vpos_interrupt_flag = true;
			}

			++ctrl_blk_.vpos_count;
		}


		static void underflow_1_isr_()
		{
			callback_args_t args;

			if(ctrl_blk_.callback != nullptr) {
				args.event = callback_args_t::EVENT::GR1_UNDERFLOW;
				ctrl_blk_.callback((void *)&args);
			}

			// Clear interrupt flag in the register of the GLCD module
			gr1uf_int_status_clear_();
		}


		static void underflow_2_isr_()
		{
			callback_args_t args;

			if(ctrl_blk_.callback != nullptr) {
				args.event = callback_args_t::EVENT::GR2_UNDERFLOW;
				ctrl_blk_.callback ((void *)&args);
			}

			// Clear interrupt flag in the register of the GLCD module
			gr2uf_int_status_clear_();
		}


		bool open_(const cfg_t& cfg)
		{
			last_error_ = error_t::SUCCESS;

			// Status check
			if(glcdc_operating_status::CLOSED != ctrl_blk_.state) {
				last_error_ = error_t::INVALID_MODE;
				return false;
			}

			// Store position information to the control block
			// (it is necessary to set the layer and blending section later)
			ctrl_blk_.active_start_pos.x = static_cast<int16_t>(cfg.output.htiming.back_porch
				+ cfg.output.htiming.sync_width);
			ctrl_blk_.active_start_pos.y = static_cast<int16_t>(cfg.output.vtiming.back_porch
				+ cfg.output.vtiming.sync_width);
			ctrl_blk_.hsize = cfg.output.htiming.display_cyc;
			ctrl_blk_.vsize = cfg.output.vtiming.display_cyc;

			// Save status of frame buffer read enable
			if(cfg.input[FRAME_LAYER_1].offset == 0) {
				ctrl_blk_.graphics_read_enable[FRAME_LAYER_1] = false;
			} else {
				ctrl_blk_.graphics_read_enable[FRAME_LAYER_1] = true;
			}

			if(cfg.input[FRAME_LAYER_2].offset == 0) {
				ctrl_blk_.graphics_read_enable[FRAME_LAYER_2] = false;
			} else {
				ctrl_blk_.graphics_read_enable[FRAME_LAYER_2] = true;
			}

			// Save callback function
			ctrl_blk_.callback = cfg.callback;

			// Save setting of interrupt
			ctrl_blk_.interrupt.vpos_enable  = cfg.interrupt.vpos_enable;
			ctrl_blk_.interrupt.gr1uf_enable = cfg.interrupt.gr1uf_enable;
			ctrl_blk_.interrupt.gr2uf_enable = cfg.interrupt.gr2uf_enable;

			// If one of the interrupt setting is enable, setting value is
			// set after first vpos interrupt
			glcdc_interrupt_cfg_t initial_interrupt;
			if(cfg.interrupt.vpos_enable || cfg.interrupt.gr1uf_enable
			  || cfg.interrupt.gr2uf_enable) {
				ctrl_blk_.first_vpos_interrupt_flag = false;
				initial_interrupt.vpos_enable  = true;
				initial_interrupt.gr1uf_enable = false;
				initial_interrupt.gr2uf_enable = false;
			} else {
				ctrl_blk_.first_vpos_interrupt_flag = true;
				initial_interrupt.vpos_enable  = false;
				initial_interrupt.gr1uf_enable = false;
				initial_interrupt.gr2uf_enable = false;
			}

			// Check parameters
//			err = r_glcdc_open_param_check (p_cfg);
//			if(GLCDC_SUCCESS != err) {
//				return err;
//			}

// この中で行うべきでない処理
#if 0
			// Check GLCDC resource is locked by another process
			if(false == R_BSP_HardwareLock ((mcu_lock_t) BSP_LOCK_GLCDC)) {
				return GLCDC_ERR_LOCK_FUNC;
			}
#endif

			// Supply the peripheral clock to the GLCD module
			power_cfg::turn(GLC::get_peripheral());

			// LCD_DATA0 to LCD_DATA15, LCD_CLK, LCD_TCON0, LCD_TCON2, LCD_TCON3
			if(!port_map::turn(GLC::get_peripheral())) {
				utils::format("GLCDC: port map fail...\n");
				return false;
			}

			// Release GLCD from a SW reset status.
			release_software_reset_();

			// Set the dot clock frequency
			clock_set_(cfg);

			// Set the panel signal timing
			sync_signal_set_(cfg);

			// Configure the background screen
			background_screen_set_(cfg);

			// Configure the graphics plane layers
			for(uint32_t frame = 0; frame <= FRAME_LAYER_2; ++frame) {
				graphics_layer_set_(cfg.input[frame], frame);
				blend_condition_set_(cfg.blend[frame], frame);
				graphics_chromakey_set_(cfg.chromakey[frame], frame);
				clut_update_(cfg.clut[frame], frame);
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
			if(!ctrl_blk_.is_entry) {
				icu_mgr::set_level(ICU::VECTOR::GROUPAL1, intr_lvl_);
				if(intr_lvl_ > 0) {
					icu_mgr::install_group_task(ICU::VECTOR_AL1::VPOS,  line_detect_isr_);
					icu_mgr::install_group_task(ICU::VECTOR_AL1::GR1UF, underflow_1_isr_);
					icu_mgr::install_group_task(ICU::VECTOR_AL1::GR2UF, underflow_2_isr_);
				}
				ctrl_blk_.is_entry = true;
			}

			detect_setting_(cfg.detection);
			interrupt_setting_(initial_interrupt);

			// Allow reading of graphics data
			graphics_read_enable_();

			// Change GLCDC driver state
			ctrl_blk_.state = glcdc_operating_status::NOT_DISPLAYING;

			return true;
		}		


		void bg_color_setting_(const color_t& color)
		{
			GLC::BGCOLOR.R = color.byte.r;
			GLC::BGCOLOR.G = color.byte.g;
			GLC::BGCOLOR.B = color.byte.b;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		*/
		//-----------------------------------------------------------------//
		glcdc_io(uint8_t intr_lvl = 5) noexcept :
			intr_lvl_(intr_lvl), last_error_(error_t::SUCCESS)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	X 軸幅を取得
			@return X 軸幅
		*/
		//-----------------------------------------------------------------//
		int32_t get_xsize() const noexcept { return XSIZE; }


		//-----------------------------------------------------------------//
		/*!
			@brief	Y 軸幅を取得
			@return Y 軸幅
		*/
		//-----------------------------------------------------------------//
		int32_t get_ysize() const noexcept { return YSIZE; }


		//-----------------------------------------------------------------//
		/*!
			@brief	BG の許可（不許可）
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void bg_operation_enable(bool ena = true) noexcept
		{
			if(ena) {
				GLC::BGEN = 0x00010101;
			} else {
				GLC::BGEN.EN = 1;
				while(GLC::BGMON.EN() != 0) {
					asm("nop");
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	ly1		レイヤー１アドレス
			@param[in]	ly2		レイヤー２アドレス
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(void* ly1 = reinterpret_cast<void*>(0x0),
			void* ly2 = reinterpret_cast<void*>(0x0)) noexcept
		{
			cfg_t cfg;
			cfg.output.clksrc = GLCDC_CLK_SRC_INTERNAL;   			  // Select PLL clock
			cfg.output.clock_div_ratio = GLCDC_PANEL_CLK_DIVISOR_24;  // 240 / 24 = 10 MHz
  																      // No frequency division
  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	      // Enable LCD_CLK output
			//
			// Definition of LCD for 480x272 LCD by 60Hz
			//
			// Horizontal cycle (whole control screen) 529
			// Vertical cycle (whole control screen) 315
			// Horizontal Synchronization Signal Assertion Position
			cfg.output.htiming.front_porch = 8;
			// Vertical Synchronization Assertion Position
			cfg.output.vtiming.front_porch = 10;
			// Horizontal Active Pixel Start Position (min. 6 pixels)
			cfg.output.htiming.back_porch = 39;
			cfg.output.vtiming.back_porch = 32;
			// Horizontal Active Pixel Width
			cfg.output.htiming.display_cyc = XSIZE;
			// Vertical Active Display Width
			cfg.output.vtiming.display_cyc = YSIZE;
			// Vertical Active Display Start Position (min. 3 lines)
			cfg.output.htiming.sync_width = 2;
			cfg.output.vtiming.sync_width = 1;

			//
			// Graphic 1 configuration
			//
			cfg.input[FRAME_LAYER_1].base = ly1;
			cfg.input[FRAME_LAYER_2].offset = 0;	  // Disable Graphics 1

			//
			// Graphic 2 configuration
			//
  			// Enable reading of the frame buffer
			// Specify the start address of the frame buffer
			cfg.input[FRAME_LAYER_2].base = ly2;
			// Offset value from the end address of the line to the start address of the next line
			cfg.input[FRAME_LAYER_2].offset = LINE_OFFSET;

			// Single Line Data Transfer Count
			// Single Frame Line Count

			switch(PXT) {
			case PIX_TYPE::CLUT1:
				cfg.input[FRAME_LAYER_2].format = GLCDC_IN_FORMAT_CLUT1;
				break;
			case PIX_TYPE::CLUT4:
				cfg.input[FRAME_LAYER_2].format = GLCDC_IN_FORMAT_CLUT4;
				break;
			case PIX_TYPE::CLUT8:
				cfg.input[FRAME_LAYER_2].format = GLCDC_IN_FORMAT_CLUT8;
				break;
			case PIX_TYPE::RGB565:
				cfg.input[FRAME_LAYER_2].format = GLCDC_IN_FORMAT_16BITS_RGB565;
				break;
//  (GLCDC_IN_FORMAT_16BITS_ARGB1555)
//  (GLCDC_IN_FORMAT_16BITS_ARGB4444)
			case PIX_TYPE::RGB888:
				cfg.input[FRAME_LAYER_2].format = GLCDC_IN_FORMAT_32BITS_RGB888;
				break;
//  (GLCDC_IN_FORMAT_32BITS_ARGB8888)
			}
			cfg.blend[FRAME_LAYER_2].visible = true;
			// Display Screen Control (current graphics)
			cfg.blend[FRAME_LAYER_2].blend_control = GLCDC_BLEND_CONTROL_NONE;
			// Rectangular Alpha Blending Area Frame Display Control
			cfg.blend[FRAME_LAYER_2].frame_edge = false;
			// Graphics Area Frame Display Control
			cfg.input[FRAME_LAYER_2].frame_edge = false;

  			// Alpha Blending Control (Per-pixel alpha blending)
			// Graphics Area Vertical Start Position
			cfg.input[FRAME_LAYER_2].coordinate.y = 0;
			// Graphics Area Vertical Width
			cfg.input[FRAME_LAYER_2].vsize = YSIZE;
			// Graphics Area Horizontal Start Position
			cfg.input[FRAME_LAYER_2].coordinate.x = 0;
			// Graphics Area Horizontal Width
			cfg.input[FRAME_LAYER_2].hsize = XSIZE;
			// Rectangular Alpha Blending Area Vertical Start Position
			cfg.blend[FRAME_LAYER_2].start_coordinate.x = 0;
			// Rectangular Alpha Blending Area Vertical Width
			cfg.blend[FRAME_LAYER_2].end_coordinate.x= YSIZE;
			// Rectangular Alpha Blending Area Horizontal Start Position
			cfg.blend[FRAME_LAYER_2].start_coordinate.y = 0;
			// Rectangular Alpha Blending Area Horizontal Width
			cfg.blend[FRAME_LAYER_2].end_coordinate.y= XSIZE;
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
			cfg.output.tcon_vsync = GLCDC_TCON_PIN_0;
			// TCON2 Output Signal Select STHA (HSYNC)
			cfg.output.tcon_hsync = GLCDC_TCON_PIN_2;
			// TCON3 Output Signal Select DE (DEN)
			cfg.output.tcon_de    = GLCDC_TCON_PIN_3;
			cfg.output.data_enable_polarity = GLCDC_SIGNAL_POLARITY_HIACTIVE;
			cfg.output.hsync_polarity = GLCDC_SIGNAL_POLARITY_LOACTIVE;
			cfg.output.vsync_polarity = GLCDC_SIGNAL_POLARITY_LOACTIVE;
			cfg.output.sync_edge = GLCDC_SIGNAL_SYNC_EDGE_RISING;
			//
			// Output interface
			//
			//   Serial RGB Data Output Delay Control (0 cycles) (not support)
			//   Serial RGB Scan Direction Select (forward) (not support)
			//   Pixel Clock Division Control (no division)
			// Output Data Format Select (RGB565)
			cfg.output.format = GLCDC_OUT_FORMAT_16BITS_RGB565;
			// Pixel Order Control (B-G-R)
			cfg.output.color_order = GLCDC_COLOR_ORDER_RGB;	// GLCDC_COLOR_ORDER_BGR;
			// Bit Endian Control (Little endian)
			cfg.output.endian = GLCDC_ENDIAN_LITTLE;
			//
			// Brightness Adjustment
			//
			cfg.output.brightness.b = BRIGHTNESS_;  // B
			cfg.output.brightness.g = BRIGHTNESS_;  // G
			cfg.output.brightness.r = BRIGHTNESS_;  // R
			//
			// Contrast Adjustment Value
			//
			cfg.output.contrast.b = CONTRAST_;  // B
			cfg.output.contrast.g = CONTRAST_;  // G
			cfg.output.contrast.r = CONTRAST_;  // R

			//
			// Disable Gamma
			//
			cfg.output.gamma.enable = false;
			//
			// Disable Chromakey
			//
			cfg.chromakey[FRAME_LAYER_2].enable = false;
			//
			// Disable Dithering
			//
			cfg.output.dithering.dithering_on = false;
			//
			// CLUT Adjustment Value
			//
			cfg.clut[FRAME_LAYER_2].enable = false;
			//
			// Enable VPOS ISR
			//
			//   Detecting Scanline Setting
			// Enable detection of specified line notification in graphic 2
			cfg.detection.vpos_detect = true;
			// Enable VPOS interrupt request
			cfg.interrupt.vpos_enable = true;
			//   Interrupt Priority Level (r_glcdc_rx_config.h)
			//   Interrupt Request Enable
			//   Clears the STMON.VPOS flag
			//   VPOS (line detection)
			cfg.detection.gr1uf_detect = false;
			cfg.detection.gr2uf_detect = false;
			cfg.interrupt.gr1uf_enable = false;
			cfg.interrupt.gr2uf_enable = false;
			//
			// Set function to be called on VSYNC
			//
			cfg.callback = vsync_task_;
#if 0
			runtime_cfg.blend = cfg.blend[FRAME_LAYER_2];
			runtime_cfg.input = cfg.input[FRAME_LAYER_2];
			runtime_cfg.chromakey = cfg.chromakey[FRAME_LAYER_2];
#endif
			//
			// Register Dave2D interrupt
			//
///			R_BSP_InterruptWrite(BSP_INT_SRC_AL1_DRW2D_DRW_IRQ, (bsp_int_cb_t)drw_int_isr);

			//
			// Register Reflection
			//
			auto ret = open_(cfg);
			if(!ret) {
				return false;
			}

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

			if(cfg.input[FRAME_LAYER_1].offset != 0) {
				memset(cfg.input[FRAME_LAYER_1].base, 0x00, BYTES_PER_BUFFER);
			}
			if(cfg.input[FRAME_LAYER_2].offset != 0) {
				memset(cfg.input[FRAME_LAYER_2].base, 0x00, BYTES_PER_BUFFER);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  制御
			@param[in]	cmd		制御種別
			@param[in]	args	パラメーター
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool control(control_cmd cmd, const void* args = nullptr) noexcept
		{
			if(glcdc_operating_status::CLOSED == ctrl_blk_.state) {
				last_error_ = error_t::NOT_OPEN;
				return false;
			}

			switch(cmd) {
			case control_cmd::START_DISPLAY:

				if(glcdc_operating_status::DISPLAYING == ctrl_blk_.state) {
					last_error_ = error_t::INVALID_MODE;
					return false;
				}

				/* Change GLCDC driver state */
				ctrl_blk_.state = glcdc_operating_status::DISPLAYING;

				/* Start to output the vertical and horizontal synchronization signals and
				   screen data. */
				bg_operation_enable();
				break;

			case control_cmd::STOP_DISPLAY:

				if(glcdc_operating_status::NOT_DISPLAYING == ctrl_blk_.state) {
					last_error_ = error_t::INVALID_MODE;
					return false;
				}
				/* Return immediately if the register is being updated */
				if(is_gr_plane_updating_(FRAME_LAYER_1)) {
					last_error_ = error_t::INVALID_UPDATE_TIMING;
					return false;
				}
				if(is_gr_plane_updating_(FRAME_LAYER_2)) {
					last_error_ = error_t::INVALID_UPDATE_TIMING;
					return false;
				}
				if(is_output_ctrl_updating_()) {
					last_error_ = error_t::INVALID_UPDATE_TIMING;
					return false;
				}
				if(is_gamma_updating_()) {
					last_error_ = error_t::INVALID_UPDATE_TIMING;
					return false;
				}
				if(is_register_reflecting_()) {
					last_error_ = error_t::INVALID_UPDATE_TIMING;
					return false;
				}

				/* Stop outputting the vertical and horizontal synchronization signals
				   and screen data. */
				bg_operation_enable(false);

				/* status update */
				ctrl_blk_.state = glcdc_operating_status::NOT_DISPLAYING;

				break;

			case control_cmd::SET_INTERRUPT:
#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
				if(NULL == args) {
					last_error_ = error_t::INVALID_PTR;
					return false;
				}
#endif

				if(false == ctrl_blk_.first_vpos_interrupt_flag) {
                	last_error_ = error_t::INVALID_UPDATE_TIMING;
					return false;
				}

				/* interrupt setting */
				{
					const glcdc_interrupt_cfg_t* t =
						static_cast<const glcdc_interrupt_cfg_t*>(args);
					interrupt_setting_(*t);
				}
				break;

	        case control_cmd::CLR_DETECTED_STATUS:

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
				if (NULL == args) {
					return GLCDC_ERR_INVALID_PTR;
				}
#endif
				{
					const detect_cfg_t* p_detection;
					p_detection = static_cast<const detect_cfg_t*>(args);

					if(true == p_detection->vpos_detect) {
						vpos_int_status_clear_();
					}
					if(true == p_detection->gr1uf_detect) {
						gr1uf_int_status_clear_();
					}
					if(true == p_detection->gr2uf_detect) {
						gr2uf_int_status_clear_();
					}
				}
				break;

			case control_cmd::CHANGE_BG_COLOR:
				{
					const color_t* t = static_cast<const color_t*>(args);
					if(t != nullptr) {
						bg_color_setting_(*t);
					} else {
						last_error_ = error_t::INVALID_PTR;
						return false;
					}
				}
				break;

			default:
				last_error_ = error_t::INVALID_ARG;
				return false;
			}

			last_error_ = error_t::SUCCESS;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  VPOS との同期
		*/
		//-----------------------------------------------------------------//
		void sync_vpos() const noexcept
		{
			volatile auto n = ctrl_blk_.vpos_count;
			while(n == ctrl_blk_.vpos_count) {
				asm("nop");
			}
		}
	};

	template <class GLC, int32_t XSIZE, int32_t YSIZE, PIX_TYPE PXT>
		glcdc_ctrl_t glcdc_io<GLC, XSIZE, YSIZE, PXT>::ctrl_blk_;
}
