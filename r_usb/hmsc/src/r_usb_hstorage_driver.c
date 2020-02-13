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
 * File Name    : r_usb_hstorage_driver.c
 * Description  : USB Host Storage Driver
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 usb_hmsc_strg_drive_search_act is fixed.(Add MBR(sect0) dummy read)
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_hmsc_if.h"
#include "r_usb_hmsc.h"

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
uint16_t g_usb_hmsc_strg_process[USB_NUM_USBIP];

/* static uint8_t g_usb_hmsc_data[USB_NUM_USBIP][64];*/     /* Full-Speed MAXPS */
static uint8_t g_usb_hmsc_data[USB_NUM_USBIP][512];    /* Hi-Speed MAXPS */

/* Partition */
static uint16_t g_usb_hmsc_read_partition_retry_count[USB_NUM_USBIP];


/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 Renesas Abstracted Peripheral Driver functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_strg_drive_search_act
 Description     : Storage drive search
 Arguments       : usb_utr_t *mess   : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void usb_hmsc_strg_drive_search_act (usb_utr_t *mess)
{
    static uint16_t side;
    uint16_t addr;
    usb_er_t err;
    uint16_t ipno_devaddr;

    switch (g_usb_hmsc_drive_search_seq[mess->ip])
    {
        case USB_SEQ_0 : /* Get MAX_LUN */
            USB_PRINTF0("\n*** Drive search !\n");
            g_usb_hmsc_strg_process[mess->ip] = USB_MSG_HMSC_STRG_DRIVE_SEARCH;
            addr = mess->keyword;
            ipno_devaddr = addr;
            if ( USB_IP1 == mess->ip)
            {
                ipno_devaddr |= USBA_ADDRESS_OFFSET;
            }
            side = R_USB_HmscRefDrvno(ipno_devaddr);

            if (USB_ERROR == side)
            {
                g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
                g_usb_hmsc_strg_process[mess->ip] = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
                usb_hmsc_strg_specified_path(mess);
            }
            else
            {
                err = R_USB_HmscGetMaxUnit(mess, addr, g_usb_hmsc_data[mess->ip], usb_hmsc_strg_check_result);
                if (USB_QOVR == err)
                {
                    usb_hmsc_message_retry( USB_HSTRG_MBX, mess);
                }
                else
                {
                    g_usb_hmsc_drive_search_seq[mess->ip]++;
                }
            }
        break;

        case USB_SEQ_1 : /* Check result */
            if ( USB_CTRL_END != mess->result)
            {
                USB_PRINTF0("### GetMaxLUN error\n");
            }
            USB_PRINTF1(" Unit number is %d\n", g_usb_hmsc_data[mess->ip][0] );
            USB_PRINTF0("\nPlease wait device ready\n");
            usb_cpu_delay_xms(100);

            /* Inquiry */
            R_USB_HmscInquiry(mess, side, (uint8_t*) &g_usb_hmsc_data[mess->ip]);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
        break;

        case USB_SEQ_2 : /* Check result */
            if (mess->result != USB_HMSC_OK)
            {
                USB_PRINTF0("### Inquiry error\n");
            }
            /* Read Format Capacity */
            R_USB_HmscReadFormatCapacity(mess, side, (uint8_t*) &g_usb_hmsc_data[mess->ip]);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
        break;

        case USB_SEQ_3 : /* Read Capacity */
            R_USB_HmscReadCapacity(mess, side, (uint8_t*) &g_usb_hmsc_data[mess->ip]);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
        break;

        case USB_SEQ_4 :
            if (mess->result != USB_HMSC_OK)
            {
                /* TestUnitReady */
                R_USB_HmscTestUnit(mess, side);
                g_usb_hmsc_drive_search_seq[mess->ip]++;
            }
            else
            {
                /* Pass TestUnitReady  */
                g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_6;
                g_usb_hmsc_read_partition_retry_count[mess->ip] = 0;
                usb_hmsc_strg_specified_path(mess);
            }
        break;

        case USB_SEQ_5 :
            if (mess->result != USB_HMSC_OK)
            {
                /* TestUnitReady (Retry) */
                R_USB_HmscTestUnit(mess, side);
            }
            else
            {
                /* Read Capacity (Retry) */
                R_USB_HmscReadCapacity(mess, side, (uint8_t*) &g_usb_hmsc_data[mess->ip]);
                g_usb_hmsc_read_partition_retry_count[mess->ip] = 0;
                g_usb_hmsc_drive_search_seq[mess->ip]++;
            }
        break;

        case USB_SEQ_6 :
            /* Don't delete the following processing!! */
            /* (This is necessary for the specific USB memory.) */
            /* Read10 secno = 0, seccnt = 1 */
            R_USB_HmscRead10 (mess, side, (uint8_t*)&g_usb_hmsc_data[mess->ip], 0, 1, USB_HMSC_STRG_SECTSIZE);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
        break;

        case USB_SEQ_7 :
            if (USB_HMSC_OK == mess->result)
            {
                g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
                g_usb_hmsc_strg_process[mess->ip] = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
            }
            else
            {
                g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_6;
                /* Drive read error */
                USB_PRINTF0 ("### drive read error  (times ).\n");
                g_usb_hmsc_read_partition_retry_count[mess->ip]++;   /* Update Retry count */
                /* Max Retry count = 10 */
                if ((uint32_t)10 == g_usb_hmsc_read_partition_retry_count[mess->ip])
                {
                    /* Retry end. */
                    g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
                    g_usb_hmsc_strg_process[mess->ip] = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
                }
            }
            usb_hmsc_strg_specified_path ((usb_utr_t *)mess);
        break;

        default :
            g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
            g_usb_hmsc_strg_process[mess->ip] = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
            usb_hmsc_strg_specified_path(mess);
        break;
    }
}
/******************************************************************************
 End of function usb_hmsc_strg_drive_search_act
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_strg_specified_path
 Description     : Next Process Selector
 Arguments       : usb_utr_t *mess   : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void usb_hmsc_strg_specified_path (usb_utr_t *mess)
{
    usb_utr_t *pblf;
    usb_er_t err;

    /* Get mem pool blk */
    if ( USB_PGET_BLK(USB_HSTRG_MPL,&pblf) == USB_OK)
    {
        pblf->msginfo = g_usb_hmsc_strg_process[mess->ip];
        pblf->keyword = mess->keyword;
        pblf->result = mess->result;

        pblf->ip = mess->ip;
        pblf->ipp = mess->ipp;

        /* Send message */
        err = USB_SND_MSG(USB_HSTRG_MBX, (usb_msg_t* )pblf);
        if (USB_OK != err)
        {
            err = USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )pblf);
            USB_PRINTF0("### SpecifiedPass function snd_msg error\n");
        }
    }
    else
    {
        USB_PRINTF0("### SpecifiedPass function pget_blk error\n");
    }
}
/******************************************************************************
 End of function usb_hmsc_strg_specified_path
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hmsc_strg_check_result
 Description     : Hub class check result
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return value    : none
 ******************************************************************************/
void usb_hmsc_strg_check_result (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    mess->result = mess->status;
    usb_hmsc_strg_specified_path(mess);
}
/******************************************************************************
 End of function usb_hmsc_strg_check_result
 ******************************************************************************/

/******************************************************************************
 End  Of File
 ******************************************************************************/
