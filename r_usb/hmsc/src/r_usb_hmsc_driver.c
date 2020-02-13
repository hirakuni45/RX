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
 * Copyright (C) 2014(2017) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_hmsc_driver.c
 * Description  : USB Host MSC BOT driver
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Change USBA PIPE Buffer size. Fix usb_hmsc_data_act(),usb_hmsc_specified_path(),
 *                           usb_hmsc_get_csw_check(),usb_hmsc_strg_cmd_complete().
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_hmsc_if.h"
#include "r_usb_extern.h"
#include "r_usb_hmsc.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/* functions */
static uint16_t usb_hmsc_data_act (usb_utr_t *mess);
static void usb_hmsc_stall_err (usb_utr_t *mess);
static void usb_hmsc_specified_path (usb_utr_t *mess);
static void usb_hmsc_check_result (usb_utr_t *mess, uint16_t data1, uint16_t data2);
static void usb_hmsc_command_result (usb_utr_t *ptr, uint16_t result);
static uint16_t usb_hmsc_get_string_desc (usb_utr_t *ptr, uint16_t addr, uint16_t string, usb_cb_t complete);
static uint16_t usb_hmsc_send_cbw (usb_utr_t *ptr, uint16_t side);
static uint16_t usb_hmsc_send_cbw_check (usb_utr_t *ptr, uint16_t side, uint16_t hmsc_retval);
static uint16_t usb_hmsc_send_data (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t size);
static uint16_t usb_hmsc_send_data_check (usb_utr_t *ptr, uint16_t side, uint16_t hmsc_retval);
static uint16_t usb_hmsc_get_data (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t size);
static uint16_t usb_hmsc_get_data_check (usb_utr_t *ptr, uint16_t side, uint16_t hmsc_retval);
static uint16_t usb_hmsc_get_csw (usb_utr_t *ptr, uint16_t side);
static uint16_t usb_hmsc_get_csw_check (usb_utr_t *ptr, uint16_t side, uint16_t hmsc_retval);
static usb_er_t usb_hmsc_clear_stall (usb_utr_t *ptr, uint16_t Pipe, usb_cb_t complete);
static uint16_t usb_hmsc_std_req_check (uint16_t result);

/*uint16_t usb_hmsc_smp_pipe_info (usb_utr_t *ptr, uint8_t *table, uint16_t msgnum, uint16_t speed, uint16_t length);*/
static void usb_hmsc_class_check_result (usb_utr_t *mess, uint16_t data1, uint16_t data2);
static void usb_hmsc_class_check (usb_utr_t *mess);
static void usb_hmsc_configured (usb_utr_t *ptr, uint16_t addr, uint16_t data2);
static void usb_hmsc_detach (usb_utr_t *ptr, uint16_t addr, uint16_t data2);

/* variables */
static usb_utr_t usb_hmsc_trans_data[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Send data transfer message */
static usb_utr_t usb_hmsc_receive_data[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Receive data transfer message */
static uint32_t usb_hmsc_trans_size[USB_NUM_USBIP];
static uint8_t *pusb_hmsc_buff[USB_NUM_USBIP];
static uint16_t usb_shmsc_process[USB_NUM_USBIP];
static uint16_t usb_shmsc_data_seq[USB_NUM_USBIP];
static uint16_t usb_shmsc_stall_err_seq[USB_NUM_USBIP];
static uint16_t usb_hmsc_csw_err_loop[USB_NUM_USBIP];

uint32_t    g_usb_hmsc_cmd_data_length[USB_NUM_USBIP];

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

const uint16_t g_usb_hmsc_devicetpl[] =
{
    USB_CFG_TPLCNT,        /* Number of tpl table */
    0,                  /* Reserved */
    USB_CFG_TPL             /* Vendor ID, Product ID */
};


uint16_t g_usb_hmsc_tmp_ep_tbl[USB_NUM_USBIP][USB_MAXSTRAGE][2][USB_EPL] =
{
  { /* IP No.0 */
    {
        /* MSC Device 1 */
        {
            USB_PIPE1,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */

        /*    USB_D0DMA */
        },
        {
            USB_PIPE1,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */

        /*    USB_D0DMA */
        }
    },
    {
        /* MSC Device 2 */
        {
            USB_PIPE2,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */

        /*    USB_D0DMA */
        },
        {
            USB_PIPE2,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */

        /*    USB_D0DMA */
        }
    },
    {
        /* MSC Device 3 */
        {
            USB_PIPE3,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE,   /* FIFO Access mode */

        /*    USB_D0DMA, */
        },
        {
            USB_PIPE3,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE,   /* FIFO Access mode */

        /*    USB_D0DMA, */
        }
    },
    {
        /* MSC Device 4 */
        {
            USB_PIPE4,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */

        /*    USB_D0DMA */
        },
        {
            USB_PIPE4,  /* Pipe No. */

            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
            USB_NULL,   /* PIPEBUF(for USBA USE) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */

        /*   USB_D0DMA */
        }
    }
  },
#if USB_NUM_USBIP == 2
  {
    /* IP No.1 */
    {
        /* MSC Device 1 */
        {
            USB_PIPE1,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
        /*   USB_D0DMA */
        },
        {
            USB_PIPE1,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
            /*    USB_D0DMA */
        }
    },
    {
        /* MSC Device 2 */
        {
            USB_PIPE2,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
            /*    USB_D0DMA */
        },
        {
            USB_PIPE2,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
            /*    USB_D0DMA */
        }
    },
    {
        /* MSC Device 3 */
        {
            USB_PIPE3,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
            /*    USB_D0DMA */
        },
        {
            USB_PIPE3,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
            /*    USB_D0DMA */
        }
    },
    {
        /* MSC Device 4 */
        {
            USB_PIPE4,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
            /*    USB_D0DMA */
        },
        {
            USB_PIPE4,  /* Pipe No. */
            /* TYPE    / BFRE        / DBLB       / CNTMD       / SHTNAK       / DIR      / EPNUM */
            USB_NULL | USB_BFREOFF | USB_CFG_DBLB   | USB_CFG_CNTMD   | USB_CFG_SHTNAK   | USB_NULL | USB_NULL, /* PIPECFG */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
  #if USB_CFG_DTC == USB_CFG_ENABLE
            USB_BUF_SIZE(1024u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #else     /* USB_CFG_DTC == USB_CFG_ENABLE */
            USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u),             /* PIPEBUF(for USBA USE) */
  #endif    /* USB_CFG_DTC == USB_CFG_ENABLE */
#else   /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,                                           /* PIPEBUF(for USBA USE) */
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            USB_NULL,   /* PIPEMAXP */
            USB_NULL,   /* PIPEPERI */
            USB_CUSE    /* FIFO Access mode */
        /*    USB_D0DMA */
        }
    }
  }
#endif /* USB_NUM_USBIP == 2 */
};

uint16_t g_usb_hmsc_def_ep_tbl[USB_NUM_USBIP][USB_EPL+1] =
{
  {  /* USB IP No.0 */
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_PDTBLEND /* Pipe end */
  },
#if USB_NUM_USBIP == 2
  {  /* USB IP No.1 */
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_NULL,
    USB_PDTBLEND /* Pipe end */
  }
#endif /* USB_NUM_USBIP == 2 */
};

drive_management_t g_usb_hmsc_drvno_tbl[USB_MAXSTRAGE]; /* Drive no. management table */
uint16_t g_usb_hmsc_out_pipe[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Pipenumber */
uint16_t g_usb_hmsc_in_pipe[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Pipenumber */
uint16_t g_usb_hmsc_out_pipectr[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Pipectr(SQTGL) */
uint16_t g_usb_hmsc_in_pipectr[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Pipectr(SQTGL) */
usb_msc_cbw_t g_usb_hmsc_cbw[USB_NUM_USBIP][USB_MAXSTRAGE]; /* CBW headder */
usb_msc_csw_t g_usb_hmsc_csw[USB_NUM_USBIP][USB_MAXSTRAGE]; /* CSW headder */
uint32_t g_usb_hmsc_csw_tag_no[USB_NUM_USBIP][USB_MAXSTRAGE]; /* CBW tag number */
uint8_t g_usb_hmsc_sub_class[USB_NUM_USBIP][USB_MAXSTRAGE];
uint8_t g_usb_hmsc_tmp_sub_class[USB_NUM_USBIP];

uint16_t g_usb_hmsc_init_seq[USB_NUM_USBIP];

uint8_t *g_p_usb_hmsc_device_table[USB_NUM_USBIP];
uint8_t *g_p_usb_hmsc_config_table[USB_NUM_USBIP];
uint8_t *g_p_usb_hmsc_interface_table[USB_NUM_USBIP];
uint16_t g_usb_hmsc_devaddr[USB_NUM_USBIP];

usb_utr_t g_usb_hmsc_class_control[USB_NUM_USBIP];
uint8_t g_usb_hmsc_class_data[USB_NUM_USBIP][USB_HMSC_CLSDATASIZE];

uint16_t g_usb_shmsc_data_stall_seq[USB_NUM_USBIP];
uint16_t g_usb_hmsc_speed[USB_NUM_USBIP];

uint8_t g_drive_search_que[USB_MAXSTRAGE];
uint8_t g_drive_search_que_cnt;
uint8_t g_drive_search_lock;


/******************************************************************************
 Renesas Abstracted HMSC Driver functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_task
 Description     : USB HMSC Task
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_hmsc_task (void)
{
    usb_utr_t *pmess;
    usb_er_t err;

    /* Receive message */
    err = USB_RCV_MSG(USB_HMSC_MBX, (usb_msg_t** )&pmess);
    if (USB_OK != err)
    {
        return;
    }

    switch (pmess->msginfo)
    {
        case USB_MSG_CLS_INIT :
            usb_hmsc_class_check(pmess);
        break;
        case USB_MSG_HMSC_NO_DATA :
        case USB_MSG_HMSC_DATA_IN :
        case USB_MSG_HMSC_DATA_OUT :
            usb_hmsc_data_act(pmess);
        break;
        case USB_MSG_HMSC_CBW_ERR :
        case USB_MSG_HMSC_CSW_PHASE_ERR :
            usb_hmsc_stall_err(pmess);
        break;
        default :
        break;
    }
    err = USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t )pmess);
    if (USB_OK != err)
    {
        USB_PRINTF0("### USB hmsc Task rel_blk error\n");
    }
}
/******************************************************************************
 End of function usb_hmsc_task
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_class_check
 Description     : check class
 Arguments       : usb_utr_t *mess   : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_class_check (usb_utr_t *mess)
{
    uint16_t retval;
    uint16_t result;
    uint16_t iproduct;

    result = USB_OK;
    switch (g_usb_hmsc_init_seq[mess->ip])
    {
        case USB_SEQ_0 :

            /* Check Interface Descriptor (deviceclass) */
            if (USB_IFCLS_MAS != g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACECLASS])
            {
                USB_PRINTF1("### Interface deviceclass is %x , not support.\n",
                        g_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACECLASS]);
                result = USB_ERROR;
            }

            /* Check Interface Descriptor (subclass) */
            g_usb_hmsc_tmp_sub_class[mess->ip] = g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACESUBCLASS];
            if (USB_ATAPI == g_usb_hmsc_tmp_sub_class[mess->ip])
            {
                USB_PRINTF0("    Interface subclass  : SFF-8070i\n");
            }
            else if (USB_SCSI == g_usb_hmsc_tmp_sub_class[mess->ip])
            {
                USB_PRINTF0(
                        "Interface subclass  : SCSI transparent command set\n");
            }
            else if (USB_ATAPI_MMC5 == g_usb_hmsc_tmp_sub_class[mess->ip])
            {
                USB_PRINTF0("   Interface subclass   : ATAPI command set\n");
            }
            else
            {
                USB_PRINTF1("### Interface subclass is %x , not support.\n", g_usb_hmsc_tmp_sub_class[mess->ip]);
                result = USB_ERROR;
            }

            /* Check Interface Descriptor (protocol) */
            if (USB_BOTP == g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACEPROTOCOL])
            {
                USB_PRINTF0("   Interface protocol   : BOT \n");
            }
            else
            {
                USB_PRINTF1("### Interface protocol is %x , not support.\n",
                        g_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACEPROTOCOL]);
                result = USB_ERROR;
            }

            /* Check Endpoint number */
            if (g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_NUMENDPOINTS] < 2)
            {
                USB_PRINTF1("### Endpoint number is %x , less than 2.\n",
                        g_usb_hmsc_interface_table[mess->ip][USB_IF_B_NUMENDPOINTS]);
                result = USB_ERROR;
            }

            /* Send GetDescriptor(Stirng) */
            if (USB_ERROR != result)
            {
                retval = usb_hmsc_get_string_desc(mess, g_usb_hmsc_devaddr[mess->ip], 0, usb_hmsc_class_check_result);
                g_usb_hmsc_init_seq[mess->ip]++;
            }
        break;

        case USB_SEQ_1 :
            retval = usb_hmsc_std_req_check(mess->result);
            if (USB_ERROR == retval)
            {
                result = USB_ERROR;
            }
            else
            {
                /* Send GetDescriptor(Stirng) */
                iproduct = g_p_usb_hmsc_device_table[mess->ip][USB_DEV_I_PRODUCT];
                retval = usb_hmsc_get_string_desc(mess, g_usb_hmsc_devaddr[mess->ip], iproduct,
                        usb_hmsc_class_check_result);
                g_usb_hmsc_init_seq[mess->ip]++;
            }
        break;

        case USB_SEQ_2 :
            retval = usb_hmsc_std_req_check(mess->result);
            if (USB_ERROR == retval)
            {
                result = USB_ERROR;
            }

            if (USB_ERROR != result)
            {
                /* Return to MGR */
                usb_hstd_return_enu_mgr(mess, retval);
                g_usb_hmsc_init_seq[mess->ip] = USB_SEQ_0;
            }
        break;

        default :
            result = USB_ERROR;
        break;
    }

    if (USB_ERROR == result)
    {
        /* Return to MGR */
        usb_hstd_return_enu_mgr(mess, USB_ERROR);
        g_usb_hmsc_init_seq[mess->ip] = USB_SEQ_0;
    }
}
/******************************************************************************
 End of function usb_hmsc_class_check
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_set_rw_cbw
 Description     : CBW parameter initialization for the READ10/WRITE10 command
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
                 : uint16_t     command     : ATAPI command
                 : uint32_t     secno       : Sector number
                 : uint16_t     seccnt      : Sector count
                 : uint32_t     trans_byte  : Transfer size
                 : uint16_t     side        : Driver number
 Return value    : none
 ******************************************************************************/
void usb_hmsc_set_rw_cbw (usb_utr_t *ptr, uint16_t command, uint32_t secno, uint16_t seccnt, uint32_t trans_byte,
        uint16_t side)
{
    /* CBW parameter set */
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag = g_usb_hmsc_csw_tag_no[ptr->ip][side];
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_lo = (uint8_t) trans_byte;
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_ml = (uint8_t) (trans_byte >> 8);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_mh = (uint8_t) (trans_byte >> 16);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_hi = (uint8_t) (trans_byte >> 24);
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.reserved7 = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.bcbw_lun = 0; /*** Support LUN0 ONLY ***/
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.reserved4 = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.reserved3 = 0;

    /* ATAPI_COMMAND */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[0] = (uint8_t) command;

    /* LUN */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[1] = 0x00;

    /* sector address */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[2] = (uint8_t) (secno >> 24);
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[3] = (uint8_t) (secno >> 16);
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[4] = (uint8_t) (secno >> 8);
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[5] = (uint8_t) secno;

    /* Reserved */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[6] = 0x00;

    /* Sector length */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[7] = (uint8_t) (seccnt >> 8);

    /* Block address */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[8] = (uint8_t) seccnt;

    /* Control data */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[9] = (uint8_t) 0x00;

    /* ATAPI command check */
    switch (command)
    {
        case USB_ATAPI_TEST_UNIT_READY :
        case USB_ATAPI_REQUEST_SENSE :
        case USB_ATAPI_INQUIRY :
        case USB_ATAPI_MODE_SELECT6 :
        case USB_ATAPI_MODE_SENSE6 :
        case USB_ATAPI_START_STOP_UNIT :
        case USB_ATAPI_PREVENT_ALLOW :
        case USB_ATAPI_READ_FORMAT_CAPACITY :
        case USB_ATAPI_READ_CAPACITY :
            USB_PRINTF0("### Non-mounted command demand generating !\n");
        break;

            /* Initialized READ CBW TAG */
        case USB_ATAPI_READ10 :
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 1;

            /* 10bytes */
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
        break;

            /* Initialized WRITE CBW TAG */
        case USB_ATAPI_WRITE10 :
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 0;

            /* 10bytes */
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
        break;
        case USB_ATAPI_SEEK :
        case USB_ATAPI_WRITE_AND_VERIFY :
        case USB_ATAPI_VERIFY10 :
        case USB_ATAPI_MODE_SELECT10 :
        case USB_ATAPI_MODE_SENSE10 :
        default :
            USB_PRINTF0("### Non-mounted command demand generating !\n");
        break;
    }

    if (USB_ATAPI == g_usb_hmsc_sub_class[ptr->ip][side])
    {
        /* 12bytes */
        g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = USB_MSC_CBWCB_LENGTH;
    }
}
/******************************************************************************
 End of function usb_hmsc_set_rw_cbw
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_set_els_cbw
 Description     : CBW parameter initialization for other commands
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
                 : uint8_t      *cbwcb      : Pointer to the CBW area
                 : uint32_t     trans_byte  : Transfer size
                 : uint16_t     side        : Drive number
 Return value    : none
 ******************************************************************************/
void usb_hmsc_set_els_cbw (usb_utr_t *ptr, uint8_t *cbwcb, uint32_t trans_byte, uint16_t side)
{
    uint8_t i;

    /* CBW parameter set */
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag = g_usb_hmsc_csw_tag_no[ptr->ip][side];
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_lo = (uint8_t) trans_byte;
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_ml = (uint8_t) (trans_byte >> 8);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_mh = (uint8_t) (trans_byte >> 16);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_hi = (uint8_t) (trans_byte >> 24);

    /* Receive */
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.reserved7 = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.bcbw_lun = 0; /*** Support LUN0 ONLY ***/
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.reserved4 = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.reserved3 = 0;

    for (i = 0; i < 12; i++)
    {
        g_usb_hmsc_cbw[ptr->ip][side].cbwcb[i] = cbwcb[i];
    }

    /* ATAPI command check */
    switch (cbwcb[0])
    {
        /* No data */
        case USB_ATAPI_TEST_UNIT_READY :
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
        break;

            /* Receive */
        case USB_ATAPI_REQUEST_SENSE :
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
        break;

            /* Send */
        case USB_ATAPI_FORMAT_UNIT :
            USB_PRINTF0("### Non-mounted command demand generating !\n");
        break;

            /* Receive */
        case USB_ATAPI_INQUIRY :
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
        break;
        case USB_ATAPI_MODE_SELECT6 :
        case USB_ATAPI_MODE_SENSE6 :
        break;

            /* No data */
        case USB_ATAPI_START_STOP_UNIT :
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
        break;

            /* No data */
        case USB_ATAPI_PREVENT_ALLOW :
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
        break;

            /* Receive */
        case USB_ATAPI_READ_FORMAT_CAPACITY :
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
        break;

            /* Receive */
        case USB_ATAPI_READ_CAPACITY :
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
        break;
        case USB_ATAPI_READ10 :
        case USB_ATAPI_WRITE10 :
            USB_PRINTF0("### Non-mounted command demand generating !\n");
        break;
        case USB_ATAPI_SEEK :
        case USB_ATAPI_WRITE_AND_VERIFY :
        case USB_ATAPI_VERIFY10 :
            USB_PRINTF0("### Non-mounted command demand generating !\n");
        break;

            /* Send */
        case USB_ATAPI_MODE_SELECT10 :
            USB_PRINTF0("### Non-mounted command demand generating !\n");
        break;

            /* Receive */
        case USB_ATAPI_MODE_SENSE10 :
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
        break;
        default :
            USB_PRINTF0("### Non-mounted command demand generating !\n");
        break;
    }

    if (USB_ATAPI == g_usb_hmsc_sub_class[ptr->ip][side])
    {
        /* 12bytes */
        g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = USB_MSC_CBWCB_LENGTH;
    }
}
/******************************************************************************
 End of function usb_hmsc_set_els_cbw
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_clr_data
 Description     : data clear
 Arguments       : uint16_t len : Clear size
                 : uint8_t *buf : Pointer to the area to clear
 Return value    : none
 ******************************************************************************/
void usb_hmsc_clr_data (uint16_t len, uint8_t *buf)
{
    uint16_t i;

    for (i = 0; i < len; ++i)
    {
        *buf++ = 0x00;
    }
}
/******************************************************************************
 End of function usb_hmsc_clr_data
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_no_data
 Description     : HMSC No data
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Driver number
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t usb_hmsc_no_data (usb_utr_t *ptr, uint16_t side)
{
    usb_utr_t mess;

    mess.ip = ptr->ip;
    mess.ipp = ptr->ipp;
    mess.keyword = side;
    usb_shmsc_process[ptr->ip] = USB_MSG_HMSC_NO_DATA;
    usb_hmsc_specified_path(&mess);
    usb_shmsc_data_seq[ptr->ip] = USB_SEQ_0;

    return USB_OK;
}
/******************************************************************************
 End of function usb_hmsc_no_data
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_data_in
 Description     : HMSC Data In
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Driver number
                 : uint8_t      *buff   : Pointer to the buffer area
                 : uint32_t     size    : Data size
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t usb_hmsc_data_in (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t size)
{
    usb_utr_t mess;

    mess.ip = ptr->ip;
    mess.ipp = ptr->ipp;
    mess.keyword = side;
    pusb_hmsc_buff[ptr->ip] = buff;
    usb_hmsc_trans_size[ptr->ip] = size;
    usb_shmsc_process[ptr->ip] = USB_MSG_HMSC_DATA_IN;
    usb_hmsc_specified_path(&mess);
    usb_shmsc_data_seq[ptr->ip] = USB_SEQ_0;

    return USB_OK;
}
/******************************************************************************
 End of function usb_hmsc_data_in
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_data_out
 Description     : HMSC Data Out
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Driver number
                 : uint8_t      *buff   : Pointer to the buffer area
                 : uint32_t     size    : Data size
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t usb_hmsc_data_out (usb_utr_t *ptr, uint16_t side, const uint8_t *buff, uint32_t size)
{
    usb_utr_t mess;

    mess.ip = ptr->ip;
    mess.ipp = ptr->ipp;
    mess.keyword = side;
    pusb_hmsc_buff[ptr->ip] = (uint8_t *)buff;
    usb_hmsc_trans_size[ptr->ip] = size;
    usb_shmsc_process[ptr->ip] = USB_MSG_HMSC_DATA_OUT;
    usb_hmsc_specified_path(&mess);
    usb_shmsc_data_seq[ptr->ip] = USB_SEQ_0;

    return USB_OK;
}
/******************************************************************************
 End of function usb_hmsc_data_out
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_data_act
 Description     : Send Data request
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 Return value    : uint16_t : 
 ******************************************************************************/
static uint16_t usb_hmsc_data_act (usb_utr_t *mess)
{
    static uint16_t side;
    uint16_t hmsc_retval;
    uint16_t result;
    uint8_t *pbuff;
    uint32_t size;

    pbuff = pusb_hmsc_buff[mess->ip];
    size = usb_hmsc_trans_size[mess->ip];
    result = mess->result;

    switch (usb_shmsc_data_seq[mess->ip])
    {
        case USB_SEQ_0 : /* CBW */
            side = mess->keyword;
            hmsc_retval = usb_hmsc_send_cbw(mess, side);
            usb_shmsc_data_seq[mess->ip]++;
        break;

        case USB_SEQ_1 : /* Check CBW and Send Data */
            hmsc_retval = usb_hmsc_send_cbw_check(mess, side, result);
            if (USB_HMSC_STALL == hmsc_retval)
            {
                usb_shmsc_process[mess->ip] = USB_MSG_HMSC_CBW_ERR;
                usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
                mess->keyword = g_usb_hmsc_drvno_tbl[side].devadr;
                usb_hmsc_specified_path((usb_utr_t *) mess);
                usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
            }
            else if (hmsc_retval != USB_HMSC_OK)
            {
                USB_PRINTF1("### Data : SendCBW error(drive:%d) \n", side);
                usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
                usb_hmsc_command_result(mess, hmsc_retval);
            }

            else /* Success */
            {
                switch (usb_shmsc_process[mess->ip])
                {
                    case USB_MSG_HMSC_NO_DATA :
                        hmsc_retval = usb_hmsc_get_csw(mess, side);
                        usb_shmsc_data_seq[mess->ip] = USB_SEQ_4;
                    break;
                    case USB_MSG_HMSC_DATA_OUT :
                        hmsc_retval = usb_hmsc_send_data(mess, side, pbuff, size);
                        usb_shmsc_data_seq[mess->ip]++;
                    break;
                    case USB_MSG_HMSC_DATA_IN :
                        g_usb_hmsc_cmd_data_length[mess->ip] = 0;
                        hmsc_retval = usb_hmsc_get_data(mess, side, pbuff, size);
                        usb_shmsc_data_seq[mess->ip]++;
                    break;
                    default :
                    break;
                }
            }
        break;

        case USB_SEQ_2 : /* Check Data and Send CSW*/
            if ( USB_MSG_HMSC_DATA_OUT == usb_shmsc_process[mess->ip])
            {
                hmsc_retval = usb_hmsc_send_data_check(mess, side, result);
                if (hmsc_retval == USB_HMSC_STALL)
                {
                    usb_hmsc_clear_stall(mess, g_usb_hmsc_out_pipe[mess->ip][side], usb_hmsc_check_result);
                    usb_shmsc_data_seq[mess->ip]++;
                }
                else if (hmsc_retval != USB_HMSC_OK)
                {
                    USB_PRINTF1("### Data : SendData error(drive:%d) \n", side);
                    usb_hmsc_command_result(mess, hmsc_retval);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
                }
                else /* Success */
                {
                    hmsc_retval = usb_hmsc_get_csw(mess, side);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_4;
                }
            }
            else if ( USB_MSG_HMSC_DATA_IN == usb_shmsc_process[mess->ip])
            {
                hmsc_retval = usb_hmsc_get_data_check(mess, side, result);
                if (hmsc_retval == USB_HMSC_STALL)
                {
                    usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], usb_hmsc_check_result);
                    usb_shmsc_data_seq[mess->ip]++;
                }
                else if (hmsc_retval != USB_HMSC_OK)
                {
                    USB_PRINTF1("### Data : SendData error(drive:%d) \n", side);
                    usb_hmsc_command_result(mess, hmsc_retval);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
                }
                else /* Success */
                {
                    g_usb_hmsc_cmd_data_length[mess->ip] = mess->tranlen;
                    hmsc_retval = usb_hmsc_get_csw(mess, side);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_4;
                }
            }
            else
            {
                /* Non */
            }

        break;

        case USB_SEQ_3 : /* Check ClearStall and Send CSW */
            usb_hmsc_std_req_check(result);
            hmsc_retval = usb_hmsc_get_csw(mess, side);
            usb_shmsc_data_seq[mess->ip]++;
        break;

        case USB_SEQ_4 : /* Check CSW */
            usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
            hmsc_retval = usb_hmsc_get_csw_check(mess, side, result);
            switch (hmsc_retval)
            {
                case USB_HMSC_OK : /* Success */
                    if (usb_hmsc_csw_err_loop[mess->ip] == USB_ON)
                    {
                        usb_hmsc_csw_err_loop[mess->ip] = USB_OFF;
                        hmsc_retval = USB_HMSC_CSW_ERR;
                    }
                    usb_hmsc_command_result(mess, hmsc_retval);
                break;

                case USB_HMSC_CSW_ERR :
                    USB_PRINTF1("*** Data : CSW-NG(drive:%d) \n", side);

                    if (USB_MSG_HMSC_STRG_USER_COMMAND != g_usb_hmsc_strg_process[mess->ip])
                    {
                        usb_hmsc_csw_err_loop[mess->ip] = USB_ON;
                        R_USB_HmscRequestSense(mess, side, pbuff);
                    }
                    else
                    {
                        if (usb_hmsc_csw_err_loop[mess->ip] == USB_ON)
                        {
                            usb_hmsc_csw_err_loop[mess->ip] = USB_OFF;
                        }
                        usb_hmsc_command_result(mess, hmsc_retval);
                    }
                break;

                case USB_HMSC_STALL :
                    USB_PRINTF1("*** Data : CSW-STALL(drive:%d) \n", side);
                    g_usb_hmsc_in_pipectr[mess->ip][side] = 0;
                    usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], usb_hmsc_check_result);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_3;
                break;

                case USB_HMSC_CSW_PHASE_ERR :
                    USB_PRINTF1("*** Data : CSW-PhaseError(drive:%d) \n", side);
                    usb_shmsc_process[mess->ip] = USB_MSG_HMSC_CSW_PHASE_ERR;
                    usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
                    mess->keyword = g_usb_hmsc_drvno_tbl[side].devadr;
                    usb_hmsc_specified_path((usb_utr_t *) mess);
                break;

                default :
                    /* Non */
                break;
            }

        break;

        default :
            while (1)
            {
                /* Non */
            }
        break;
    }

    /* Data read error */
    return (hmsc_retval);
}
/******************************************************************************
 End of function usb_hmsc_data_act
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_stall_err
 Description     : HMSC Stall Error
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_stall_err (usb_utr_t *mess)
{
    static uint16_t devadr;
    uint16_t side;
    uint16_t result;
    usb_er_t err;

    result = mess->status;

    switch (usb_shmsc_stall_err_seq[mess->ip])
    {
        case USB_SEQ_0 :
            devadr = mess->keyword;
            err = R_USB_HmscMassStorageReset(mess, devadr, (usb_cb_t) usb_hmsc_check_result);

            /* Control Transfer overlaps */
            if (USB_QOVR == err)
            {
                usb_hmsc_message_retry( USB_HMSC_MBX, mess);
            }
            else
            {
                /* Control Transfer not overlaps */
                usb_shmsc_stall_err_seq[mess->ip]++;
            }
        break;

        case USB_SEQ_1 :
            usb_hmsc_std_req_check(result);
            if ( USB_IP1 == mess->ip)
            {
                devadr |= USBA_ADDRESS_OFFSET;
            }
            side = R_USB_HmscRefDrvno(devadr);

            if (USB_ERROR == side)
            {
                usb_hmsc_command_result(mess, USB_HMSC_CBW_ERR);
                usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
                return;
            }

            usb_hmsc_clear_stall(mess, g_usb_hmsc_out_pipe[mess->ip][side], usb_hmsc_check_result);
            usb_shmsc_stall_err_seq[mess->ip]++;
            g_usb_hmsc_out_pipectr[mess->ip][side] = 0;
        break;

        case USB_SEQ_2 :
            if ( USB_IP1 == mess->ip)
            {
                devadr |= USBA_ADDRESS_OFFSET;
            }
            side = R_USB_HmscRefDrvno(devadr);

            if (USB_ERROR == side)
            {
                usb_hmsc_command_result(mess, USB_HMSC_CBW_ERR);
                usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
                return;
            }

            usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], usb_hmsc_check_result);
            usb_shmsc_stall_err_seq[mess->ip]++;
            g_usb_hmsc_in_pipectr[mess->ip][side] = 0;
        break;

        case USB_SEQ_3 :
            if (USB_MSG_HMSC_CSW_PHASE_ERR == mess->msginfo)
            {
                result = USB_HMSC_CSW_PHASE_ERR;
            }
            else
            {
                result = USB_HMSC_CBW_ERR;
            }
            usb_hmsc_command_result(mess, result);
            usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
        break;

        default :
            if (USB_MSG_HMSC_CSW_PHASE_ERR == mess->msginfo)
            {
                result = USB_HMSC_CSW_PHASE_ERR;
            }
            else
            {
                result = USB_HMSC_CBW_ERR;
            }
            usb_hmsc_command_result(mess, result);
            usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
        break;
    }
}
/******************************************************************************
 End of function usb_hmsc_stall_err
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_specified_path
 Description     : Next Process Selector
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_specified_path (usb_utr_t *mess)
{
    usb_utr_t *pblf;
    usb_er_t err;

    /* Get mem pool blk */
    if ( USB_PGET_BLK(USB_HMSC_MPL, &pblf) == USB_OK)
    {
        pblf->msginfo = usb_shmsc_process[mess->ip];
        pblf->keyword = mess->keyword;
        pblf->result = mess->result;
        pblf->ip = mess->ip;
        pblf->ipp = mess->ipp;
        pblf->tranlen = mess->tranlen;

        /* Send message */
        err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t* )pblf);
        if (USB_OK != err)
        {
            err = USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t )pblf);
            USB_PRINTF0("### SpecifiedPass function snd_msg error\n");
        }
    }
    else
    {
        USB_PRINTF0("### SpecifiedPass function pget_blk error\n");
    }
}
/******************************************************************************
 End of function usb_hmsc_specified_path
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_check_result
 Description     : Hub class check result
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_check_result (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    mess->result = mess->status;
    usb_hmsc_specified_path(mess);
}
/******************************************************************************
 End of function usb_hmsc_check_result
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_command_result
 Description     : Hub class check result
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
                 : uint16_t     result  : Command Result
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_command_result (usb_utr_t *ptr, uint16_t result)
{
    usb_utr_t *pblf;
    usb_er_t err;

    /* Get mem pool blk */
    if ( USB_PGET_BLK(USB_HSTRG_MPL,&pblf) == USB_OK)
    {
        pblf->msginfo = g_usb_hmsc_strg_process[ptr->ip];
        pblf->result = result;
        pblf->ip = ptr->ip;
        pblf->ipp = ptr->ipp;
        pblf->tranlen = ptr->tranlen;

        /* Send message */
        err = USB_SND_MSG(USB_HSTRG_MBX, (usb_msg_t* )pblf);
        if (USB_OK != err)
        {
            err = USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )pblf);
            USB_PRINTF0("### CheckResult function snd_msg error\n");
        }
    }
    else
    {
        USB_PRINTF0("### CheckResult function pget_blk error\n");
    }
}
/******************************************************************************
 End of function usb_hmsc_command_result
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_get_string_desc
 Description     : Set GetDescriptor
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     addr        : Device address
                 : uint16_t     string      : String Descriptor index
                 : usb_cb_t     complete    : callback function
 Return value    : uint16_t                 : error info
 ******************************************************************************/
static uint16_t usb_hmsc_get_string_desc (usb_utr_t *ptr, uint16_t addr, uint16_t string, usb_cb_t complete)
{
    uint16_t i;
    static usb_ctrl_trans_t string_setup[USB_NUM_USBIP];

    if (0 == string)
    {
        string_setup[ptr->ip].setup.index = (uint16_t) 0x0000;
        string_setup[ptr->ip].setup.length = (uint16_t) 0x0004;
    }
    else
    {
        /* Set LanguageID */
        string_setup[ptr->ip].setup.index = (uint16_t) (g_usb_hmsc_class_data[ptr->ip][2]);
        string_setup[ptr->ip].setup.index |= (uint16_t) ((uint16_t) (g_usb_hmsc_class_data[ptr->ip][3]) << 8);
        string_setup[ptr->ip].setup.length = (uint16_t) USB_HMSC_CLSDATASIZE;
    }
    string_setup[ptr->ip].setup.type = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    string_setup[ptr->ip].setup.value = (uint16_t) (USB_STRING_DESCRIPTOR + string);
    string_setup[ptr->ip].address = addr;

    for (i = 0; i < string_setup[ptr->ip].setup.length; i++)
    {
        g_usb_hmsc_class_data[ptr->ip][i] = (uint8_t) 0xFF;
    }

    g_usb_hmsc_class_control[ptr->ip].p_tranadr = (void *) g_usb_hmsc_class_data[ptr->ip];
    g_usb_hmsc_class_control[ptr->ip].complete = complete;
    g_usb_hmsc_class_control[ptr->ip].tranlen = (uint32_t) string_setup[ptr->ip].setup.length;
    g_usb_hmsc_class_control[ptr->ip].keyword = USB_PIPE0;
    g_usb_hmsc_class_control[ptr->ip].p_setup = (uint16_t *) &string_setup[ptr->ip];
    g_usb_hmsc_class_control[ptr->ip].segment = USB_TRAN_END;

    g_usb_hmsc_class_control[ptr->ip].ip = ptr->ip;
    g_usb_hmsc_class_control[ptr->ip].ipp = ptr->ipp;

    return (usb_hstd_transfer_start(&g_usb_hmsc_class_control[ptr->ip]));
}
/******************************************************************************
 End of function usb_hmsc_get_string_desc
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_send_cbw
 Description     : Send CBW
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
 Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_cbw (usb_utr_t *ptr, uint16_t side)
{
    usb_er_t err;
    uint16_t toggle;

    /* Set CBW TAG usb_hmsc_CbwTagCount()*/
    g_usb_hmsc_csw_tag_no[ptr->ip][side]++;
    if ((uint16_t) 0 == g_usb_hmsc_csw_tag_no[ptr->ip][side])
    {
        g_usb_hmsc_csw_tag_no[ptr->ip][side] = (uint16_t) 1;
    }

    /* pipe number */
    usb_hmsc_trans_data[ptr->ip][side].keyword = g_usb_hmsc_out_pipe[ptr->ip][side];

    /* Transfer data address */
    usb_hmsc_trans_data[ptr->ip][side].p_tranadr = (void*) &g_usb_hmsc_cbw[ptr->ip][side];

    /* Transfer data length */
    usb_hmsc_trans_data[ptr->ip][side].tranlen = (uint32_t) USB_MSC_CBWLENGTH;

    /* Call Back Function Info */
    usb_hmsc_trans_data[ptr->ip][side].complete = &usb_hmsc_check_result;

    /* Not control transfer */
    usb_hmsc_trans_data[ptr->ip][side].p_setup = 0;
    usb_hmsc_trans_data[ptr->ip][side].segment = USB_TRAN_END;

    usb_hmsc_trans_data[ptr->ip][side].ip = ptr->ip;
    usb_hmsc_trans_data[ptr->ip][side].ipp = ptr->ipp;

    usb_hstd_set_pipe_info((uint16_t*) &g_usb_hmsc_def_ep_tbl[0], (uint16_t*) &g_usb_hmsc_tmp_ep_tbl[ptr->ip][side][1],
            (uint16_t) USB_EPL);
    usb_hstd_set_pipe_registration(ptr, (uint16_t*) &g_usb_hmsc_def_ep_tbl, g_usb_hmsc_out_pipe[ptr->ip][side]);

    if ((USB_SQMON & g_usb_hmsc_out_pipectr[ptr->ip][side]) == USB_SQMON)
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }

    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, g_usb_hmsc_out_pipe[ptr->ip][side]);
    err = usb_hstd_transfer_start(&usb_hmsc_trans_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);
        return USB_HMSC_SUBMIT_ERR;
    }

    return (err);
}
/******************************************************************************
 End of function usb_hmsc_send_cbw
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_send_cbw_check
 Description     : Check send CBW 
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
                 : uint16_t     result      : Transfer Result
 Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_cbw_check (usb_utr_t *ptr, uint16_t side, uint16_t result)
{
    switch (result)
    {
        case USB_DATA_NONE : /* Send CBW */
            g_usb_hmsc_out_pipectr[ptr->ip][side] = usb_hmsc_trans_data[ptr->ip][side].pipectr;
            return USB_HMSC_OK;
        break;
        case USB_DATA_STALL : /* Stall */
            USB_PRINTF1("*** CBW Transfer STALL(drive:%d) !\n", side);

/*        return USB_DATA_STALL;*/
            return USB_HMSC_STALL;
        break;
        case USB_DATA_ERR :
            USB_PRINTF1("### CBW Transfer ERROR(drive:%d) !\n", side);
        break;
        default :
            USB_PRINTF2("### CBW Transfer error(drive:%d) result:%d !\n", side, result);
        break;
    }
    return USB_HMSC_CBW_ERR;
}
/******************************************************************************
 End of function usb_hmsc_send_cbw_check
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_get_data
 Description     : Receive Data request
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
                 : uint8_t      *buff       : Pointer to the area to store the data
                 : uint32_t     size        : Receive Data Size
 Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_data (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t size)
{
    usb_er_t err;
    uint16_t toggle;

    /* pipe number */
    usb_hmsc_receive_data[ptr->ip][side].keyword = g_usb_hmsc_in_pipe[ptr->ip][side];

    /* Transfer data address */
    usb_hmsc_receive_data[ptr->ip][side].p_tranadr = (void*) buff;

    /* Transfer data length */
    usb_hmsc_receive_data[ptr->ip][side].tranlen = size;

    /* Call Back Function Info */
    usb_hmsc_receive_data[ptr->ip][side].complete = &usb_hmsc_check_result;

    /* Not control transfer */
    usb_hmsc_receive_data[ptr->ip][side].p_setup = 0;
    usb_hmsc_receive_data[ptr->ip][side].segment = USB_TRAN_END;
    usb_hmsc_receive_data[ptr->ip][side].ip = ptr->ip;
    usb_hmsc_receive_data[ptr->ip][side].ipp = ptr->ipp;

    usb_hstd_set_pipe_info((uint16_t*) &g_usb_hmsc_def_ep_tbl[0], (uint16_t*) &g_usb_hmsc_tmp_ep_tbl[ptr->ip][side][0],
            (uint16_t) USB_EPL);
    usb_hstd_set_pipe_registration(ptr, (uint16_t*) &g_usb_hmsc_def_ep_tbl, g_usb_hmsc_in_pipe[ptr->ip][side]);

    if ((USB_SQMON & g_usb_hmsc_in_pipectr[ptr->ip][side]) == USB_SQMON)
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }
    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, g_usb_hmsc_in_pipe[ptr->ip][side]);

    err = usb_hstd_transfer_start(&usb_hmsc_receive_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);
        return USB_HMSC_SUBMIT_ERR;
    }

    return (err);
}
/******************************************************************************
 End of function usb_hmsc_get_data
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_get_data_check
 Description     : Check Get Data 
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
                 : uint16_t     result      : Transfer Result
 Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_data_check (usb_utr_t *ptr, uint16_t side, uint16_t result)
{
    switch (result)
    {
        case USB_DATA_SHT :

            /* Continue */
        case USB_DATA_OK :
            g_usb_hmsc_in_pipectr[ptr->ip][side] = usb_hmsc_receive_data[ptr->ip][side].pipectr;
            return USB_HMSC_OK;
        break;
        case USB_DATA_STALL :
            USB_PRINTF1("*** GetData STALL(drive:%d) !\n", side);
            g_usb_hmsc_in_pipectr[ptr->ip][side] = 0;
            return USB_HMSC_STALL;
        break;
        case USB_DATA_ERR :
            USB_PRINTF1("### GetData ERROR(drive:%d) !\n", side);
        break;
        case USB_DATA_OVR :
            USB_PRINTF1("### GetData over(drive:%d) !\n", side);
        break;
        default :
            USB_PRINTF1("### GetData error(drive:%d) !\n", side);
        break;
    }

    return USB_HMSC_DAT_RD_ERR;
}
/******************************************************************************
 End of function usb_hmsc_get_data_check
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_send_data
 Description     : Send Pipe Data
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
                 : uint8_t      *buff       : Pointer to the area to store the data
                 : uint32_t     size        : Receive Data Size
 Return value    : uint16_t                : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_data (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t size)
{
    usb_er_t err;
    uint16_t toggle;

    /* pipe number */
    usb_hmsc_trans_data[ptr->ip][side].keyword = g_usb_hmsc_out_pipe[ptr->ip][side];

    /* Transfer data address */
    usb_hmsc_trans_data[ptr->ip][side].p_tranadr = (void*) buff;

    /* Transfer data length */
    usb_hmsc_trans_data[ptr->ip][side].tranlen = size;

    /* Call Back Function Info */
    usb_hmsc_trans_data[ptr->ip][side].complete = &usb_hmsc_check_result;

    /* Not control transfer */
    usb_hmsc_trans_data[ptr->ip][side].p_setup = 0;
    usb_hmsc_trans_data[ptr->ip][side].segment = USB_TRAN_END;
    usb_hmsc_trans_data[ptr->ip][side].ip = ptr->ip;
    usb_hmsc_trans_data[ptr->ip][side].ipp = ptr->ipp;

    usb_hstd_set_pipe_info((uint16_t*) &g_usb_hmsc_def_ep_tbl[0], (uint16_t*) &g_usb_hmsc_tmp_ep_tbl[ptr->ip][side][1],
            (uint16_t) USB_EPL);
    usb_hstd_set_pipe_registration(ptr, (uint16_t*) &g_usb_hmsc_def_ep_tbl, g_usb_hmsc_out_pipe[ptr->ip][side]);

    if ((USB_SQMON & g_usb_hmsc_out_pipectr[ptr->ip][side]) == USB_SQMON)
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }
    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, g_usb_hmsc_out_pipe[ptr->ip][side]);
    err = usb_hstd_transfer_start(&usb_hmsc_trans_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);
        return USB_HMSC_SUBMIT_ERR;
    }

    return err;
}
/******************************************************************************
 End of function usb_hmsc_send_data
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_send_data_check
 Description     : Check Send Data
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
                 : uint16_t     result      : Transfer Result
 Return value    : uint16_t                  : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_data_check (usb_utr_t *ptr, uint16_t side, uint16_t result)
{
    switch (result)
    {
        case USB_DATA_NONE :
            g_usb_hmsc_out_pipectr[ptr->ip][side] = usb_hmsc_trans_data[ptr->ip][side].pipectr;
            return USB_HMSC_OK;
        break;
        case USB_DATA_STALL :
            USB_PRINTF1("*** SendData STALL(drive:%d) !\n", side);
            g_usb_hmsc_out_pipectr[ptr->ip][side] = 0;
            return USB_HMSC_STALL;
        break;
        case USB_DATA_ERR :
            USB_PRINTF1("### SendData ERROR(drive:%d) !\n", side);
        break;
        default :
            USB_PRINTF1("### SendData error(drive:%d) !\n", side);
        break;
    }
    return USB_HMSC_DAT_WR_ERR;
}
/******************************************************************************
 End of function usb_hmsc_send_data_check
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_get_csw
 Description     : Receive CSW
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
 Return value    : uint16_t                  : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_csw (usb_utr_t *ptr, uint16_t side)
{
    usb_er_t err;
    uint16_t toggle;

    /* pipe number */
    usb_hmsc_receive_data[ptr->ip][side].keyword = g_usb_hmsc_in_pipe[ptr->ip][side];

    /* Transfer data address */
    usb_hmsc_receive_data[ptr->ip][side].p_tranadr = (void*) &g_usb_hmsc_csw[ptr->ip][side];

    /* Transfer data length */
    usb_hmsc_receive_data[ptr->ip][side].tranlen = (uint32_t) USB_MSC_CSW_LENGTH;

    /* Call Back Function Info */
    usb_hmsc_receive_data[ptr->ip][side].complete = &usb_hmsc_check_result;
    usb_hmsc_receive_data[ptr->ip][side].p_setup = 0;

    /* Not control transfer */
    usb_hmsc_receive_data[ptr->ip][side].segment = USB_TRAN_END;
    usb_hmsc_receive_data[ptr->ip][side].ip = ptr->ip;
    usb_hmsc_receive_data[ptr->ip][side].ipp = ptr->ipp;

    usb_hstd_set_pipe_info((uint16_t*) &g_usb_hmsc_def_ep_tbl[0], (uint16_t*) &g_usb_hmsc_tmp_ep_tbl[ptr->ip][side][0],
            (uint16_t) USB_EPL);
    usb_hstd_set_pipe_registration(ptr, (uint16_t*) &g_usb_hmsc_def_ep_tbl, g_usb_hmsc_in_pipe[ptr->ip][side]);

    if ((USB_SQMON & g_usb_hmsc_in_pipectr[ptr->ip][side]) == USB_SQMON)
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }
    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, g_usb_hmsc_in_pipe[ptr->ip][side]);

    err = usb_hstd_transfer_start(&usb_hmsc_receive_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);
        return USB_HMSC_SUBMIT_ERR;
    }

    return err;
}
/******************************************************************************
 End of function usb_hmsc_get_csw
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_get_csw_check
 Description     : Check Receive CSW
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     side        : Drive Number
                 : uint16_t     result      : Transfer Result
 Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_csw_check (usb_utr_t *ptr, uint16_t side, uint16_t result)
{
    uint32_t    request_size;

    ptr->tranlen = 0;
    ptr->status = g_usb_hmsc_csw[ptr->ip][side].dcsw_status;

    switch (result)
    {
        case USB_DATA_SHT :

            /* Continue */
        case USB_DATA_OK :
            g_usb_hmsc_in_pipectr[ptr->ip][side] = usb_hmsc_receive_data[ptr->ip][side].pipectr;

            request_size = g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_lo;
            request_size |= (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_ml << 8);
            request_size |= (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_mh << 16);
            request_size |= (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_hi << 24);
            ptr->tranlen = request_size - g_usb_hmsc_cmd_data_length[ptr->ip];

            /* CSW Check */
            if (USB_MSC_CSW_SIGNATURE != g_usb_hmsc_csw[ptr->ip][side].dcsw_signature)
            {
                USB_PRINTF2("### CSW signature error 0x%08x:SIGN=0x%08x.\n",
                        g_usb_hmsc_csw[ptr->ip][side].dcsw_signature, USB_MSC_CSW_SIGNATURE);
                return USB_HMSC_CSW_ERR;
            }
            if (g_usb_hmsc_csw[ptr->ip][side].dcsw_tag != g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag)
            {
                USB_PRINTF2("### CSW Tag error 0x%08x:CBWTAG=0x%08x.\n",
                        g_usb_hmsc_csw[ptr->ip][side].dcsw_tag, g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag);
                return USB_HMSC_CSW_ERR;
            }
            switch (g_usb_hmsc_csw[ptr->ip][side].dcsw_status)
            {
                case USB_MSC_CSW_OK :
                    return USB_HMSC_OK;
                break;
                case USB_MSC_CSW_NG :
                    return USB_HMSC_CSW_ERR;
                break;
                case USB_MSC_CSW_PHASE_ERR :
                    return USB_HMSC_CSW_PHASE_ERR;
                break;
                default :
                break;
            }
            return USB_HMSC_CSW_ERR;
        break;
        case USB_DATA_STALL :

            /* Stall */
            USB_PRINTF1("*** GetCSW Transfer STALL(drive:%d) !\n", side);
            return USB_HMSC_STALL;
        break;
        case USB_DATA_ERR :
            USB_PRINTF1("### GetCSW Transfer ERROR(drive:%d) !\n", side);
        break;
        case USB_DATA_OVR :
            USB_PRINTF1("### GetCSW receive over(drive:%d) !\n", side);
        break;
        default :
            USB_PRINTF1("### GetCSW Transfer error(drive:%d) !\n", side);
        break;
    }
    return USB_HMSC_CSW_ERR;
}
/******************************************************************************
 End of function usb_hmsc_get_csw_check
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_clear_stall
 Description     : Clear Stall
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
                 : uint16_t     pipe        : Pipe number
                 : usb_cb_t     complete    : Callback function
 Return value    : uint16_t
 ******************************************************************************/
static usb_er_t usb_hmsc_clear_stall (usb_utr_t *ptr, uint16_t pipe, usb_cb_t complete)
{
    usb_er_t err;

    err = usb_hstd_change_device_state(ptr, complete, USB_DO_CLR_STALL, pipe);

    return err;
}
/******************************************************************************
 End of function usb_hmsc_clear_stall
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_std_req_check
 Description     : Sample Standard Request Check
 Arguments       : uint16_t result        : Transfer Result
 Return value    : uint16_t               : error info
 ******************************************************************************/
static uint16_t usb_hmsc_std_req_check (uint16_t result)
{
    if (USB_DATA_STALL == result)
    {
        USB_PRINTF0("*** Standard Request STALL !\n");
        return USB_ERROR;
    }
    else if (USB_CTRL_END != result)
    {
        USB_PRINTF0("*** Standard Request error !\n");
        return USB_ERROR;
    }
    else
    {
        /* Non */
    }
    return USB_OK;
}
/******************************************************************************
 End of function usb_hmsc_std_req_check
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_class_check_result
 Description     : Hub class check result
 Arguments       : usb_utr_t    *mess       : Pointer to usb_utr_t structure
                 : uint16_t     data1       : Not used
                 : uint16_t     data2       : Not used
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_class_check_result (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_utr_t *pblf;
    usb_er_t err;

    /* Get mem pool blk */
    if ( USB_PGET_BLK(USB_HMSC_MPL, &pblf) == USB_OK)
    {
        pblf->msginfo = USB_MSG_CLS_INIT;
        pblf->keyword = mess->keyword;
        pblf->result = mess->status;

        pblf->ip = mess->ip;
        pblf->ipp = mess->ipp;

        USB_PRINTF0("### usb_hmsc_class_check_resultn snd_msg \n");

        /* Send message */
        err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t* )pblf);
        if (USB_OK != err)
        {
            err = USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t )pblf);
            USB_PRINTF0("### usb_hmsc_class_check_resultn snd_msg error\n");
        }
    }
    else
    {
        USB_PRINTF0("### usb_hmsc_class_check_result pget_blk error\n");
    }
}
/******************************************************************************
 End of function usb_hmsc_class_check_result
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_smp_pipe_info
 Description     : Pipe Information
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
                 : uint8_t      *table  : Pointer to the pipe information table
                 : uint16_t     side    : Drive number
                 : uint16_t     speed   : USB speed
                 : uint16_t     length  : Data size
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t usb_hmsc_smp_pipe_info (usb_utr_t *ptr, uint8_t *table, uint16_t side, uint16_t speed, uint16_t length)
{
    uint16_t epcnt = 0;
    uint16_t ofdsc;
    uint16_t ip;
    uint8_t *pdescriptor;

    ip = ptr->ip;
    if (USB_DT_INTERFACE != table[1]) /* Check Descriptor */
    {
        USB_PRINTF0("### Not Interface pdescriptor.\n"); /* Configuration Descriptor */
        return USB_ERROR;
    }

/*    offset = (uint16_t)(2u * USB_EPL * side);*/
    ofdsc = table[0]; /* Check Endpoint Descriptor */
    g_usb_hmsc_out_pipe[ip][side] = USB_NOPORT; /* Pipe initial */
    g_usb_hmsc_in_pipe[ip][side] = USB_NOPORT;
    while (ofdsc < (length - table[0]))
    {
        if (USB_DT_ENDPOINT == table[ofdsc + 1]) /* Search within Interface */
        {
            if (USB_EP_BULK == (table[ofdsc + 3] & USB_EP_TRNSMASK)) /* Bulk Endpoint */
            {
                pdescriptor = &table[ofdsc];
                if (USB_EP_IN == (pdescriptor[2] & USB_EP_DIRMASK))
                {
                    usb_hstd_chk_pipe_info(speed, &g_usb_hmsc_tmp_ep_tbl[ip][side][0][0], &table[ofdsc]);
                    g_usb_hmsc_in_pipe[ip][side] = g_usb_hmsc_tmp_ep_tbl[ip][side][0][0];
                }
                else
                {
                    usb_hstd_chk_pipe_info(speed, &g_usb_hmsc_tmp_ep_tbl[ip][side][1][0], &table[ofdsc]);
                    g_usb_hmsc_out_pipe[ip][side] = g_usb_hmsc_tmp_ep_tbl[ip][side][1][0];
                }

                if ((USB_NOPORT != g_usb_hmsc_in_pipe[ip][side]) && (USB_NOPORT != g_usb_hmsc_out_pipe[ip][side]))
                {
                    return USB_OK;
                }
                epcnt++;
                if (epcnt >= 2)
                {
                    USB_PRINTF0("### Endpoint Descriptor error.\n");
                    return USB_ERROR;
                }
            }
        }
        ofdsc += table[ofdsc];
    }
    return USB_ERROR;
}
/******************************************************************************
 End of function usb_hmsc_smp_pipe_info
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_configured
 Description     : Callback function for MSC device configured
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
                 : uint16_t     devadr  : Device Address
                 : uint16_t     data2   : Not used
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_configured (usb_utr_t *ptr, uint16_t devadr, uint16_t data2)
{
    uint16_t ret;
    uint16_t side;

    ret = R_USB_HmscStrgDriveOpen(ptr, devadr, &side);
    if (USB_ERROR == ret)
    {
        USB_PRINTF1("### R_USB_HmscStrgDriveOpen error (%x)\n", ret);
    }
}
/******************************************************************************
 End of function usb_hmsc_configured
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_detach
 Description     : Callback function for MSC device detach
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
                 : uint16_t     addr    : Device Address
                 : uint16_t     data2   : Not used
 Return value    : none
 ******************************************************************************/
static void usb_hmsc_detach (usb_utr_t *ptr, uint16_t addr, uint16_t data2)
{
    uint16_t i;
    uint16_t j;
    uint16_t side;
    uint16_t que_cnt;
    usb_ctrl_t ctrl;
    uint16_t ipno_devaddr;

    ipno_devaddr = addr;
    if ( USB_IP1 == ptr->ip)
    {
        ipno_devaddr |= USBA_ADDRESS_OFFSET;
    }

    if (g_drive_search_lock == ipno_devaddr)
    {
        g_drive_search_lock = USB_FALSE;
    }

    que_cnt = g_drive_search_que_cnt;
    for (i = 0; i < que_cnt; i++)
    {
        if (g_drive_search_que[i] == ipno_devaddr)
        {
            g_drive_search_que[i] = USB_FALSE;
            for (j = i; j < que_cnt; j++)
            {
                g_drive_search_que[j] = g_drive_search_que[j + 1];
            }
            g_drive_search_que_cnt--;
        }
    }

    side = R_USB_HmscRefDrvno(ipno_devaddr);
    if (USB_ERROR != side)
    {
        R_USB_HmscStrgDriveClose(ptr, side); /* Callback when device is detached. */
    }

    ctrl.module = ptr->ip; /* Module number setting */
    ctrl.address = addr;
    usb_set_event(USB_STS_DETACH, &ctrl); /* Set Event()  */
}
/******************************************************************************
 End of function usb_hmsc_detach
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_drive_complete
 Description     : Next Process Selector
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
                 : uint16_t     addr    : Device Address
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_hmsc_drive_complete (usb_utr_t *ptr, uint16_t addr, uint16_t data2)
{
    uint16_t i;
    uint16_t que_cnt;
    usb_ctrl_t ctrl;

    que_cnt = g_drive_search_que_cnt;
    if (g_drive_search_que_cnt)
    {
        g_drive_search_que[0] = USB_NULL;
        for (i = 0; i < que_cnt; i++)
        {
            g_drive_search_que[i] = g_drive_search_que[i + 1];
        }
        g_drive_search_que_cnt--;
    }
    g_drive_search_lock = USB_FALSE;

    ctrl.module = ptr->ip; /* Module number setting */
    ctrl.address = addr;

    usb_set_event(USB_STS_CONFIGURED, &ctrl); /* Set Event()  */
}
/******************************************************************************
 End of function usb_hmsc_drive_complete
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_registration
 Description     : registration of Host msc driver.
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void usb_hmsc_registration (usb_utr_t *ptr)
{
    usb_hcdreg_t driver;
    uint8_t i;

    /* Driver registration */
    driver.ifclass = (uint16_t) USB_IFCLS_MAS; /* Use Interface class for MSC. */
    driver.p_tpl = (uint16_t*) &g_usb_hmsc_devicetpl; /* Target peripheral list. */
    driver.classinit = &usb_hstd_dummy_function; /* Driver init. */
    driver.classcheck = &R_USB_HmscClassCheck; /* Driver check. */
    driver.devconfig = &usb_hmsc_configured; /* Callback when device is configured. */
    driver.devdetach = &usb_hmsc_detach; /* Callback when device is detached. */
    driver.devsuspend = &usb_hstd_dummy_function; /* Callback when device is suspended. */
    driver.devresume = &usb_hstd_dummy_function; /* Callback when device is resumed. */

    for (i = 0; i < USB_MAXSTRAGE; i++) /* Loop support HID device count */
    {
        driver.p_pipetbl = (uint16_t*) &g_usb_hmsc_tmp_ep_tbl[ptr->ip][0]; /* Pipe def. table address. */
        usb_hstd_driver_registration(ptr, &driver); /* Host MSC class driver registration. */
    }
    usb_cstd_set_task_pri(USB_HUB_TSK, USB_PRI_3); /* Hub Task Priority set */
    usb_hhub_registration(ptr, (usb_hcdreg_t *) USB_NULL); /* Hub registration. */
}
/******************************************************************************
 End of function usb_hmsc_registration
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_message_retry
 Description     : Message transfer retry for Que Over
 Arguments       : uint16_t     id      : Message ID
                 : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 usb_utr_t *mess
 Return value    : none
 ******************************************************************************/
void usb_hmsc_message_retry (uint16_t id, usb_utr_t *mess)
{
    usb_er_t err;
    usb_utr_t *pblf;

    /* Resend message */
    if ( USB_HSTRG_MBX == id)
    {
        err = USB_PGET_BLK(USB_HSTRG_MPL, &pblf);
    }
    if (USB_OK == err)
    {
        pblf->msginfo = mess->msginfo;
        pblf->keyword = mess->keyword;
        pblf->result = mess->result;
        pblf->complete = mess->complete;
        pblf->ip = mess->ip;
        pblf->ipp = mess->ipp;

        /* Send message */
        err = USB_SND_MSG(id, (usb_msg_t* )pblf);
        if (USB_OK != err)
        {
            USB_PRINTF1("### snd_msg error (%ld)\n", err);
            err = USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )pblf);
            if (USB_OK != err)
            {
                USB_PRINTF1("### rel_blk error (%ld)\n", err);
            }
        }
    }
    else
    {
        USB_PRINTF1("### pget_blk error (%ld)\n", err);
    }

}
/******************************************************************************
 End of function usb_hmsc_message_retry
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_smp_drive2_addr
 Description     : Retrieves device address
 Arguments       : uint16_t     side    : Drive number
                 : usb_utr_t    *devadr : Pointer to usb_utr_t structure
 Return value    : uint16_t             : Device address
 ******************************************************************************/
void usb_hmsc_smp_drive2_addr (uint16_t side, usb_utr_t *devadr)
{
    devadr->keyword = g_usb_hmsc_drvno_tbl[side].devadr; /* Device Address */
    devadr->ip = g_usb_hmsc_drvno_tbl[side].ip; /* USB IP No.     */
    devadr->ipp = usb_hstd_get_usb_ip_adr(devadr->ip);
}
/******************************************************************************
 End of function usb_hmsc_smp_drive2_addr
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_strg_cmd_complete
 Description     : Serial state receive complete call-back.
 Argument        : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     devadr  : Device address
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_hmsc_strg_cmd_complete (usb_utr_t *mess, uint16_t devadr, uint16_t data2)
{
    usb_ctrl_t ctrl;
    ctrl.module = mess->ip; /* Module number setting */
    ctrl.pipe = mess->keyword; /* Pipe number setting */
    ctrl.address = usb_hstd_get_devsel(mess, ctrl.pipe) >> 12;
    ctrl.size = 0;
    switch (mess->result)
    {
        case USB_HMSC_OK:
            ctrl.size = mess->tranlen;
            ctrl.status = USB_CSW_SUCCESS;
        break;

        case USB_HMSC_CSW_ERR:
            ctrl.status = USB_CSW_FAIL;
        break;

        case USB_HMSC_CSW_PHASE_ERR:
            ctrl.status = USB_CSW_PHASE;
        break;

        default:
            ctrl.status = USB_CSW_FAIL;
        break;
    }

    usb_set_event(USB_STS_MSC_CMD_COMPLETE, &ctrl); /* Set Event(USB receive complete)  */
}
/******************************************************************************
 End of function usb_hmsc_strg_cmd_complete
 ******************************************************************************/

/******************************************************************************
 End  Of File
 ******************************************************************************/
