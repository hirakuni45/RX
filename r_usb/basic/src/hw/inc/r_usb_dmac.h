/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016(2017) Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_usb_dmac.h
* Description  : DMA Difinition for USB
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.09.2016 1.00    First Release
*         : 26.01.2017 1.21 Support DMAC Technical Update for RX71M/RX64M USBA.
*         : 30.09.2017 1.22    Change functions name "usb_dma_buf2fifo_restart"->"usb_dma_buf_to_fifo_restart"
***********************************************************************************************************************/

#ifndef R_USB_DMAC_H
#define R_USB_DMAC_H

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define USB_DMA_USE_CH_MAX          (4)     /* MAX USE DMAC CH for USB */
#define USB_DMA_CH_PRI              (3)     /* DMACmI interrupt priority level for USB Pipe : DxFIFO->buff */
#define USB_DMA_CH2_PRI             (3)     /* DMACmI interrupt priority level for USB Pipe : buff->DxFIFO */

#define USB_FIFO_TYPE_D0DMA         (0)                             /* D0FIFO Select */
#define USB_FIFO_TYPE_D1DMA         (1)                             /* D1FIFO Select */
#define USB_DMA_FIFO_TYPE_NUM       (USB_FIFO_TYPE_D1DMA + 1)       /*  */

#define USB_FIFO_ACCESS_TYPE_32BIT  (0)                             /* FIFO port 32bit access */
#define USB_FIFO_ACCESS_TYPE_16BIT  (1)                             /* FIFO port 16bit access */
#define USB_FIFO_ACCESS_TYPE_8BIT   (2)                             /* FIFO port 8bit access */

#define USB_FIFO_ACCSESS_TYPE_NUM   (USB_FIFO_ACCESS_TYPE_8BIT + 1) /*  */

#define USB_BIT_MBW32            (3UL)                             /* Mod 4(4Byte=32Bit) */
#define USB_BIT_MBW16            (1UL)                             /* Mod 2(2Byte=16Bit) */

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
extern uint32_t g_usb_cstd_dma_size[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 buffer size */
extern uint16_t g_usb_cstd_dma_fifo[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 FIFO buffer size */
extern uint16_t g_usb_cstd_dma_pipe[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 pipe number */

void        usb_dma_driver(void);
uint16_t    usb_dma_get_crtb(uint16_t use_port);
uint16_t    usb_dma_get_dxfifo_ir_vect(usb_utr_t *ptr, uint16_t useport);
void        usb_dma_clear_dxfifo_ir(usb_utr_t *ptr, uint16_t useport);
void        usb_dma_dxfifo2buf_setting(usb_utr_t *ptr, uint32_t src_adr, uint16_t useport, uint32_t transfer_size);
void        usb_dma_buf2dxfifo_setting(usb_utr_t *ptr, uint32_t src_adr, uint16_t useport, uint32_t transfer_size);
void        usb_dma_stop_dxfifo(uint8_t ip_type, uint16_t fifo_mode);
void        usb_cstd_dxfifo_stop(usb_utr_t *ptr, uint16_t useport);
uint32_t    hw_usb_get_dxfifo_adr(usb_utr_t *ptr, uint16_t fifo_mode, uint16_t bit_width);

uint8_t     usb_dma_ref_ch_no(uint16_t ip_no, uint16_t use_port);
void        usb_dma_set_ch_no(uint16_t ip_no, uint16_t use_port, uint8_t dma_ch_no);
void        usb_dma_buf2dxfifo_complete(usb_utr_t *ptr, uint16_t useport);

void        usb_cstd_dxfifo2buf_start_dma(usb_utr_t *ptr, uint16_t pipe, uint16_t useport, uint32_t length);
void        usb_cstd_buf2dxfifo_start_dma(usb_utr_t *ptr, uint16_t pipe, uint16_t useport);
void        usb_dma_buf_to_fifo_restart(usb_utr_t *ptr, uint32_t src, uint32_t data_size, uint8_t pipe);
void        usb_dma_buf2dxfifo_complete_event_set(uint16_t ip_no, uint16_t use_port);

void        usb_ip0_d0fifo_callback (void);
void        usb_ip0_d1fifo_callback (void);
void        usb_ip1_d0fifo_callback (void);
void        usb_ip1_d1fifo_callback (void);

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#endif /* R_USB_DMAC_H */
/******************************************************************************
End  Of File
******************************************************************************/
