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

/* Version Number of API. */
#define GLCDC_RX_VERSION_MAJOR         (1)
#define GLCDC_RX_VERSION_MINOR         (0)

/* Number of Gamma correction setting items  */
#define GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM      (16)
#define GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM (15)

/* Number of graphics layers */
#define GLCDC_FRAME_LAYER_NUM                   (2)

/* Number of color palletes for each graphic */
#define GLCDC_CLUT_PLANE_NUM                    (2)

/* Number of clock division ratio setting items */
#define GLCDC_PANEL_CLKDIV_NUM                  (13)

/**********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/** Return value */
typedef enum e_glcdc_err
{
    GLCDC_SUCCESS = 0,                     // Success.
    GLCDC_ERR_INVALID_PTR,                 // Pointer points to invalid memory location.
    GLCDC_ERR_LOCK_FUNC,                   // GLCDC resource is in use by another process.
    GLCDC_ERR_INVALID_ARG,                 // Invalid input parameter.
    GLCDC_ERR_INVALID_MODE,                // Unsupported or incorrect mode.
    GLCDC_ERR_NOT_OPEN,                    // Requested channel is not configured or API not open.
    GLCDC_ERR_INVALID_TIMING_SETTING,      // Invalid timing parameter.
    GLCDC_ERR_INVALID_LAYER_SETTING,       // Invalid layer parameter.
    GLCDC_ERR_INVALID_ALIGNMENT,           // Invalid memory alignment found.
    GLCDC_ERR_INVALID_GAMMA_SETTING,       // Invalid gamma correction parameter.
    GLCDC_ERR_INVALID_UPDATE_TIMING,       // Invalid timing for register update.
    GLCDC_ERR_INVALID_CLUT_ACCESS,         // Invalid access to CLUT entry.
    GLCDC_ERR_INVALID_BLEND_SETTING,       // Invalid blending setting.
} glcdc_err_t;

/** Correction Command */
typedef enum e_glcdc_correction_cmd
{
    GLCDC_CORRECTION_CMD_SET_ALL,          // All correction setting command.
    GLCDC_CORRECTION_CMD_BRIGHTNESS,       // Brightness setting command.
    GLCDC_CORRECTION_CMD_CONTRAST,         // Contrast setting command.
    GLCDC_CORRECTION_CMD_GAMMA,            // Gamma setting command.
} glcdc_correction_cmd_t;

/** Control Command */
typedef enum e_glcdc_control_cmd
{
    GLCDC_CMD_START_DISPLAY,               // Start display command.
    GLCDC_CMD_STOP_DISPLAY,                // Stop display command.
    GLCDC_CMD_SET_INTERRUPT,               // Interrupt setting command.
    GLCDC_CMD_CLR_DETECTED_STATUS,         // Detected status clear command.
    GLCDC_CMD_CHANGE_BG_COLOR,             // Change background color in background screen.
} glcdc_control_cmd_t;

/** Graphics frame number */
typedef enum e_glcdc_frame_layer
{
    GLCDC_FRAME_LAYER_1 = 0,               // Frame layer 1.
    GLCDC_FRAME_LAYER_2 = 1                // Frame layer 2.
} glcdc_frame_layer_t;

/** GLCDC driver operation state */
typedef enum e_glcdc_state
{
    GLCDC_STATE_CLOSED = 0,                // GLCDC closed.
    GLCDC_STATE_NOT_DISPLAYING = 1,        // Not Displaying (opened).
    GLCDC_STATE_DISPLAYING = 2             // Displaying.
} glcdc_operating_status_t;

/** Detected event codes */
typedef enum e_glcdc_event
{
    GLCDC_EVENT_GR1_UNDERFLOW = 1,         // Graphics plane1 underflow occurs
    GLCDC_EVENT_GR2_UNDERFLOW = 2,         // Graphics plane2 underflow occurs
    GLCDC_EVENT_LINE_DETECTION = 3,        // Designated line is processed.
} glcdc_event_t;

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
    GLCDC_OUT_FORMAT_8BITS_SERIAL =3       // Output format SERIAL,  8 bits (this function is not supported).
} glcdc_out_format_t;

/** Data endian select ( Don't change this value, because this value is set to the register ) */
typedef enum e_glcdc_endian
{
    GLCDC_ENDIAN_LITTLE = 0,               // Little endian.
    GLCDC_ENDIAN_BIG = 1,                  // Big endian.
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

/** Detected status */
typedef enum e_glcdc_detected_status
{
    GLCDC_NOT_DETECTED,                    // Not Detected.
    GLCDC_DETECTED                         // Detected.
} glcdc_detected_status_t;

/** Serial RGB data output delay cycles select (this function is not supported) */
typedef enum e_glcdc_serial_output_delay
{
    GLCDC_SERIAL_DELAY_0_CYCLE = 0,        // 0 cycles delay.
    GLCDC_SERIAL_DELAY_1_CYCLE = 1,        // 1 cycle delay.
    GLCDC_SERIAL_DELAY_2_CYCLE = 2,        // 2 cycles delay.
    GLCDC_SERIAL_DELAY_3_CYCLE = 3,        // 3 cycles delay.
} glcdc_serial_output_delay_t;

/** Serial RGB scan direction select (this function is not supported) */
typedef enum e_glcdc_serial_scan_direction
{
    GLCDC_SERIAL_FORWARD_SCAN = 0,         // Forward scan.
    GLCDC_SERIAL_REVERSE_SCAN = 1,         // Reverse scan.
} glcdc_serial_scan_direction_t;

/** Display output signal timing setting */
typedef struct st_glcdc_timing
{
    uint16_t display_cyc;                  // Active video cycles or lines.
    uint16_t front_porch;                  // Front poach cycles or lines.
    uint16_t back_porch;                   // Back poach cycles or lines.
    uint16_t sync_width;                   // Sync signal asserting width.
} glcdc_timing_t;

/** RGB Color setting */
// #pragma bit_order left
// #pragma unpack
typedef struct st_glcdc_color
{
    union
    {
        uint32_t argb;
        struct
        {
            uint32_t a:8;                  // alpha.
            uint32_t r:8;                  // red.
            uint32_t g:8;                  // green.
            uint32_t b:8;                  // blue.
        } byte;
    };
} glcdc_color_t;
// #pragma bit_order
// #pragma packoption

/** Coordinate */
typedef struct st_glcdc_coordinate
{
    int16_t x;                           // Coordinate X, this allows to set signed value.
    int16_t y;                           // Coordinate Y, this allows to set signed value.
} glcdc_coordinate_t;

/** Brightness (DC) correction setting */
typedef struct st_glcdc_brightness
{
    bool enable;                         // Brightness Correction On/Off.
    uint16_t r;                          // Brightness (DC) adjustment for R channel.
    uint16_t g;                          // Brightness (DC) adjustment for G channel.
    uint16_t b;                          // Brightness (DC) adjustment for B channel.
} glcdc_brightness_t;

/** Contrast (gain) correction setting */
typedef struct st_glcdc_contrast
{
    bool enable;                         // Contrast Correction On/Off.
    uint8_t r;                           // Contrast (gain) adjustment for R channel.
    uint8_t g;                           // Contrast (gain) adjustment for G channel.
    uint8_t b;                           // Contrast (gain) adjustment for B channel.
} glcdc_contrast_t;

/** Gamma correction setting for gain and threshold  */
typedef struct st_gamma_correction
{
    uint16_t gain[GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM];               // Gain adjustment.
    uint16_t threshold[GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM];     // Start threshold.
} gamma_correction_t;

/** Gamma correction setting */
typedef struct st_glcdc_gamma_correction
{
    bool enable;                         // Gamma Correction On/Off.
    gamma_correction_t * p_r;            // Gamma correction for R channel.
    gamma_correction_t * p_g;            // Gamma correction for G channel.
    gamma_correction_t * p_b;            // Gamma correction for B channel.
} glcdc_gamma_correction_t;

/** Chroma key setting */
typedef struct st_glcdc_chromakey
{
    bool enable;                         // Chroma key On/Off.
    glcdc_color_t before;                // Compare Color for -RGB.
    glcdc_color_t after;                 // Replace Color for ARGB.
} glcdc_chromakey_t;

/** Color correction setting */
typedef struct st_glcdc_correction
{
    glcdc_brightness_t brightness;       // Brightness setting.
    glcdc_contrast_t contrast;           // Contrast setting.
    glcdc_gamma_correction_t gamma;      // Gamma setting.
} glcdc_correction_t;

/** Dithering setup parameter */
typedef struct st_glcdc_dithering
{
    bool dithering_on;                               // Dithering on/off.
    glcdc_dithering_mode_t dithering_mode;           // Dithering mode.
    glcdc_dithering_pattern_t dithering_pattern_a;   // Dithering pattern A.
    glcdc_dithering_pattern_t dithering_pattern_b;   // Dithering pattern B.
    glcdc_dithering_pattern_t dithering_pattern_c;   // Dithering pattern C.
    glcdc_dithering_pattern_t dithering_pattern_d;   // Dithering pattern D.
}glcdc_dithering_t;

/** Graphics plane input configuration */
typedef struct st_glcdc_input_cfg
{
    uint32_t * p_base;                   // Base address to the frame buffer.
    uint16_t hsize;                      // Horizontal pixel size in a line.
    uint16_t vsize;                      // Vertical pixel size in a frame.
    int32_t offset;                      // offset value to next line.
    glcdc_in_format_t format;            // Input format setting.
    bool frame_edge;                     // Show/hide setting of the frame of the graphics area.
    glcdc_coordinate_t coordinate;       // Starting point of image.
    glcdc_color_t bg_color;              // Color outside region.
} glcdc_input_cfg_t;


/** Display output configuration */
typedef struct st_glcdc_output_cfg
{
    glcdc_timing_t                 htiming;                // Horizontal display cycle setting.
    glcdc_timing_t                 vtiming;                // Vertical display cycle setting.
    glcdc_out_format_t             format;                 // Output format setting.
    glcdc_endian_t                 endian;                 // Bit order of output data.
    glcdc_color_order_t            color_order;            // Color order in pixel.
    glcdc_sync_edge_t              sync_edge;              // Signal sync edge selection.

    glcdc_color_t                  bg_color;               // Background color.

    glcdc_brightness_t             brightness;             // Brightness setting.
    glcdc_contrast_t               contrast;               // Contrast setting.
    glcdc_gamma_correction_t       gamma;                  // Gamma correction setting.
    glcdc_correction_proc_order_t  correction_proc_order;  // Correction control route select.

    glcdc_dithering_t              dithering;              // Dithering setting.

    glcdc_tcon_pin_t               tcon_hsync;             // GLCD TCON output pin select.
    glcdc_tcon_pin_t               tcon_vsync;             // GLCD TCON output pin select.
    glcdc_tcon_pin_t               tcon_de;                // GLCD TCON output pin select.
    glcdc_signal_polarity_t        data_enable_polarity;   // Data Enable signal polarity.
    glcdc_signal_polarity_t        hsync_polarity;         // Horizontal sync signal polarity.
    glcdc_signal_polarity_t        vsync_polarity;         // Vertical sync signal polarity.

    glcdc_clk_src_t                clksrc;                 // Clock Source selection.
    glcdc_panel_clk_div_t          clock_div_ratio;        // Clock divide ratio for dot clock.

    glcdc_serial_output_delay_t    serial_output_delay;    // Serial RGB Data output delay cycle select (this function is not supported).
    glcdc_serial_scan_direction_t  serial_scan_direction;  // Serial RGB Scan direction select (this function is not supported).

} glcdc_output_cfg_t;

/** Graphics layer blend setup parameter */
typedef struct st_glcdc_blend
{
    glcdc_blend_control_t blend_control;   // Layer fade-in/out , blending on/off.
    bool visible;                          // Visible or hide graphics.
    bool frame_edge;                       // Show/hide setting of the frame of rectangular alpha blending area.
    uint8_t fixed_blend_value;             // Blend value. Valid only when blend_control is _FIXED.
    uint8_t fade_speed;                    // Layer fade-in/out frame rate.
    glcdc_coordinate_t  start_coordinate;  // Start coordinate of rectangle blending.
    glcdc_coordinate_t  end_coordinate;    // End coordinate of rectangle blending.
} glcdc_blend_t;

/** CLUT configuration */
typedef struct st_glcdc_clut_cfg
{
    bool enable;                         // CLUT update enable/disable.
    uint32_t * p_base;                   // Pointer to CLUT source data.
    uint16_t start;                      // Beginning of CLUT entry to be updated.
    uint16_t size;                       // Size of CLUT entry to be updated.
} glcdc_clut_cfg_t;

/** Interrupt enable setting */
typedef struct st_glcdc_interrupt_cfg
{
    bool vpos_enable;                    // Line detection interrupt enable.
    bool gr1uf_enable;                   // Graphics plane1 underflow interrupt enable.
    bool gr2uf_enable;                   // Graphics plane2 underflow interrupt enable.
} glcdc_interrupt_cfg_t;

/** Detect enable setting */
typedef struct st_glcdc_detect_cfg
{
    bool vpos_detect;           // Line detection enable.
    bool gr1uf_detect;          // Graphics plane1 underflow detection enable.
    bool gr2uf_detect;          // Graphics plane2 underflow detection enable.
} glcdc_detect_cfg_t;

/** Display callback parameter definition */
typedef struct st_glcdc_callback_args
{
    glcdc_event_t event;                 // Event code.
} glcdc_callback_args_t;

/** GLCDC main configuration */
typedef struct st_glcdc_cfg
{
    /** Generic configuration for display devices */
    glcdc_input_cfg_t input[GLCDC_FRAME_LAYER_NUM];     // Graphics input frame setting.
    glcdc_output_cfg_t output;                          // Graphics output frame setting.
    glcdc_blend_t blend[GLCDC_FRAME_LAYER_NUM];         // Graphics layer blend setting.
    glcdc_chromakey_t chromakey[GLCDC_FRAME_LAYER_NUM]; // Graphics chroma key setting.
    glcdc_clut_cfg_t clut[GLCDC_FRAME_LAYER_NUM];       // Graphics CLUT setting.

    /** Interrupt setting*/
    glcdc_detect_cfg_t     detection;                   // Detection enable/disable setting.
    glcdc_interrupt_cfg_t  interrupt;                   // Interrupt enable/disable setting.

    /** Configuration for display event processing */
    void (*p_callback)(void *);                         // Pointer to callback function.

} glcdc_cfg_t;

/** Runtime configuration */
typedef struct st_glcdc_runtime_cfg
{
    /** Generic configuration for display devices */
    glcdc_input_cfg_t input;             // Graphics input frame setting
    glcdc_blend_t blend;                 // Graphics layer blend setting.
    glcdc_chromakey_t chromakey;         // Graphics chroma key setting.
} glcdc_runtime_cfg_t;

/** GLCDC status */
typedef struct st_glcdc_status
{
    glcdc_operating_status_t state;                          // Status of GLCD module
    glcdc_detected_status_t state_vpos;                      // Status of line detection.
    glcdc_detected_status_t state_gr1uf;                     // Status of graphics plane1 underflow.
    glcdc_detected_status_t state_gr2uf;                     // Status of graphics plane2 underflow.
    glcdc_fade_status_t fade_status[GLCDC_FRAME_LAYER_NUM];  // Status of fade-in/fade-out status
} glcdc_status_t;
