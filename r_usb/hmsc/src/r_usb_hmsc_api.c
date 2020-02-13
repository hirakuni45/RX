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
 * File Name    : r_usb_hmsc_api.c
 * Description  : USB Host MSC Driver API
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Support USB_ATAPI_MODE_SELECT10, Non support MODE_SELECT6.
 *                           Change Arguments for "R_USB_HmscDriverStart()","R_USB_HmscModeSense10()"
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_hmsc_if.h"
#include "r_usb_extern.h"
#include "r_usb_hmsc.h"

/******************************************************************************
 Renesas Host MSC Driver API functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscTask
 Description     : USB HMSC Task
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void R_USB_HmscTask (void)
{
    usb_hmsc_task();
}
/******************************************************************************
 End of function R_USB_HmscTask
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscDriverStart
 Description     : USB Host Initialize process
 Arguments       : uint16_t ip_no  : USB IP No. (USB_IP0/USB_IP1)
 Return          : none
 ******************************************************************************/
void R_USB_HmscDriverStart (uint16_t ip_no)
{
    uint16_t i;
    static uint16_t init_flag = 0;

    for (i = 0; i < USB_MAXSTRAGE; i++)
    {
        if (0 == init_flag)
        {
            g_usb_hmsc_drvno_tbl[i].use_flag = USB_NOUSE;
        }

        g_usb_hmsc_in_pipe[ip_no][i] = USB_NOPORT;  /* Pipenumber */
        g_usb_hmsc_out_pipe[ip_no][i] = USB_NOPORT; /* Pipenumber */

        g_usb_hmsc_csw_tag_no[ip_no][i] = (uint16_t) 1;

        g_usb_hmsc_cbw[ip_no][i].dcbw_signature = USB_MSC_CBW_SIGNATURE;
        g_usb_hmsc_cbw[ip_no][i].dcbw_tag = g_usb_hmsc_csw_tag_no[ip_no][i];
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_lo = 0;
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_ml = 0;
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_mh = 0;
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_hi = 0;
        g_usb_hmsc_cbw[ip_no][i].bm_cbw_flags.cbw_dir = 0;
        g_usb_hmsc_cbw[ip_no][i].bm_cbw_flags.reserved7 = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbw_lun.bcbw_lun = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbw_lun.reserved4 = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbwcb_length.bcbwcb_length = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbwcb_length.reserved3 = 0;

        g_usb_hmsc_cbw[ip_no][i].cbwcb[0] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[1] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[2] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[3] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[4] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[5] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[6] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[7] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[8] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[9] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[10] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[11] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[12] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[13] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[14] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[15] = 0;
    }

    if (0 == init_flag)
    {
        usb_cstd_set_task_pri(USB_HMSC_TSK, USB_PRI_3);
        usb_cstd_set_task_pri(USB_HSTRG_TSK, USB_PRI_3);
    }

    init_flag = 1;
}
/******************************************************************************
 End of function R_USB_HmscDriverStart
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscClassCheck
 Description     : check connected device
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t **table     : Pointer to the class information table
 Return value    : none
 ******************************************************************************/
void R_USB_HmscClassCheck (usb_utr_t *ptr, uint16_t **table)
{
    usb_utr_t *pblf;
    usb_er_t err;

    g_p_usb_hmsc_device_table[ptr->ip] = (uint8_t*) (table[0]);
    g_p_usb_hmsc_config_table[ptr->ip] = (uint8_t*) (table[1]);
    g_p_usb_hmsc_interface_table[ptr->ip] = (uint8_t*) (table[2]);
    g_usb_hmsc_speed[ptr->ip] = *table[6];
    g_usb_hmsc_devaddr[ptr->ip] = *table[7];
    *table[3] = USB_OK;

    /* Get mem pool blk */
    if ( USB_PGET_BLK(USB_HMSC_MPL,&pblf) == USB_OK)
    {
        pblf->msginfo = USB_MSG_CLS_INIT;
        g_usb_hmsc_init_seq[ptr->ip] = USB_SEQ_0;

        pblf->ip = ptr->ip;
        pblf->ipp = ptr->ipp;

        /* Send message */
        err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t* )pblf);
        if (USB_OK != err)
        {
            err = USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t )pblf);
            USB_PRINTF0("### ClassCheck function snd_msg error\n");
        }
    }
    else
    {
        USB_PRINTF0("### ClassCheck function pget_blk error\n");
    }
}
/******************************************************************************
 End of function R_USB_HmscClassCheck
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscRead10
 Description     : Read10
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t side        : Side
                 : uint8_t  *buff       : Buffer address
                 : uint32_t secno       : Sector number
                 : uint16_t seccnt      : Sector count
                 : uint32_t trans_byte  : Trans byte
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscRead10 (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte)
{
    uint16_t hmsc_retval;

    /* set CBW parameter */
    usb_hmsc_set_rw_cbw(ptr, (uint16_t) USB_ATAPI_READ10, secno, seccnt, trans_byte, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, trans_byte);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscRead10
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscWrite10
 Description     : Write10
 Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
                 : uint16_t side       : Drive number
                 : uint8_t *buff       : Buffer address
                 : uint32_t secno      : Sector number
                 : uint16_t seccnt     : Sector count
                 : uint32_t trans_byte : Trans byte
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscWrite10 (usb_utr_t *ptr, uint16_t side, const uint8_t *buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte)
{
    uint16_t hmsc_retval;

    /* set CBW parameter */
    usb_hmsc_set_rw_cbw(ptr, (uint16_t) USB_ATAPI_WRITE10, secno, seccnt, trans_byte, side);

    /* Data OUT */
    hmsc_retval = usb_hmsc_data_out(ptr, side, buff, trans_byte);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscWrite10
 ******************************************************************************/


/******************************************************************************
 Function Name   : R_USB_HmscTestUnit
 Description     : TestUnit
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscTestUnit (usb_utr_t *ptr, uint16_t side)
{
    uint8_t cbwcb[12];
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_TEST_UNIT_READY;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) 0, side);

    /* No Data */
    hmsc_retval = usb_hmsc_no_data(ptr, side);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscTestUnit
 ******************************************************************************/


/******************************************************************************
 Function Name   : R_USB_HmscRequestSense
 Description     : RequestSense
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
                 : uint8_t      *buff   : Pointer to the buffer area
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscRequestSense (usb_utr_t *ptr, uint16_t side, uint8_t *buff)
{
    uint8_t cbwcb[12];
    uint8_t length = 18;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_REQUEST_SENSE;

    /* Allocation length */
    cbwcb[4] = length;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscRequestSense
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscInquiry
 Description     : Inquiry
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
                 : uint8_t      *buff   : Pointer to the buffer area
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscInquiry (usb_utr_t *ptr, uint16_t side, uint8_t *buff)
{
    uint8_t cbwcb[12];
    uint8_t length = 36;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_INQUIRY;

    /* Allocation length */
    cbwcb[4] = length;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscInquiry
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscReadCapacity
 Description     : ReadCapacity
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
                 : uint8_t      *buff   : Pointer to the buffer area
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscReadCapacity (usb_utr_t *ptr, uint16_t side, uint8_t *buff)
{
    uint8_t cbwcb[12];
    uint8_t length = 8;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_READ_CAPACITY;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscReadCapacity
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscReadFormatCapacity
 Description     : ReadFormatCapacity
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
                 : uint8_t      *buff   : Pointer to the buffer area
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscReadFormatCapacity (usb_utr_t *ptr, uint16_t side, uint8_t *buff)
{
    uint8_t cbwcb[12];
    uint8_t length = 0x20;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_READ_FORMAT_CAPACITY;

    /* Allocation length */
    cbwcb[8] = length;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscReadFormatCapacity
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscGetMaxUnit
 Description     : Get Max LUN request
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     addr    : Device address
                 : uint8_t      *buff   : Pointer to the buffer area
                 : usb_cb_t     complete: CallBack Function
 Return value    : usb_er_t                  : Error Code
 ******************************************************************************/
usb_er_t R_USB_HmscGetMaxUnit (usb_utr_t *ptr, uint16_t addr, uint8_t *buff, usb_cb_t complete)
{
    usb_er_t err;
    static usb_ctrl_trans_t get_max_lun_table;

    get_max_lun_table.setup.type = 0xFEA1;
    get_max_lun_table.setup.value = 0x0000;
    get_max_lun_table.setup.index = 0x0000;
    get_max_lun_table.setup.length = 0x0001;
    get_max_lun_table.address = addr;

    /* Recieve MaxLUN */
    g_usb_hmsc_class_control[ptr->ip].keyword = USB_PIPE0;
    g_usb_hmsc_class_control[ptr->ip].p_tranadr = buff;
    g_usb_hmsc_class_control[ptr->ip].tranlen = get_max_lun_table.setup.length;
    g_usb_hmsc_class_control[ptr->ip].p_setup = (uint16_t *) &get_max_lun_table;
    g_usb_hmsc_class_control[ptr->ip].complete = complete;
    g_usb_hmsc_class_control[ptr->ip].segment = USB_TRAN_END;
    g_usb_hmsc_class_control[ptr->ip].ip = ptr->ip;
    g_usb_hmsc_class_control[ptr->ip].ipp = ptr->ipp;

    err = usb_hstd_transfer_start(&g_usb_hmsc_class_control[ptr->ip]);
    return err;
}
/******************************************************************************
 End of function R_USB_HmscGetMaxUnit
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscMassStorageReset
 Description     : Mass Strage Reset request
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     addr    : Device address
                 : usb_cb_t     complete: CallBack Function
 Return value    : usb_er_t                 : Error Code
 ******************************************************************************/
usb_er_t R_USB_HmscMassStorageReset (usb_utr_t *ptr, uint16_t addr, usb_cb_t complete)
{
    usb_er_t err;

    static usb_ctrl_trans_t mass_storage_reset_table;

    mass_storage_reset_table.setup.type = 0xFF21;
    mass_storage_reset_table.setup.value = 0x0000;
    mass_storage_reset_table.setup.index = 0x0000;
    mass_storage_reset_table.setup.length = 0x0000;
    mass_storage_reset_table.address = addr;

    /* Set MassStorageReset */
    g_usb_hmsc_class_control[ptr->ip].keyword = USB_PIPE0;
    g_usb_hmsc_class_control[ptr->ip].p_tranadr = USB_NULL;
    g_usb_hmsc_class_control[ptr->ip].tranlen = mass_storage_reset_table.setup.length;
    g_usb_hmsc_class_control[ptr->ip].p_setup = (uint16_t *) &mass_storage_reset_table;
    g_usb_hmsc_class_control[ptr->ip].complete = complete;
    g_usb_hmsc_class_control[ptr->ip].segment = USB_TRAN_END;
    g_usb_hmsc_class_control[ptr->ip].ip = ptr->ip;
    g_usb_hmsc_class_control[ptr->ip].ipp = ptr->ipp;

    err = usb_hstd_transfer_start(&g_usb_hmsc_class_control[ptr->ip]);
    return err;
}
/******************************************************************************
 End of function R_USB_HmscMassStorageReset
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscPreventAllow
 Description     : PreventAllow
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
                 : uint8_t      *buff   : Pointer to the buffer area
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscPreventAllow (usb_utr_t *ptr, uint16_t side, uint8_t *buff)
{
    uint8_t cbwcb[12];
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_PREVENT_ALLOW;

    /* Reserved */
    cbwcb[4] = buff[0];

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) 0, side);

    /* No Data */
    hmsc_retval = usb_hmsc_no_data(ptr, side);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscPreventAllow
 ******************************************************************************/


/******************************************************************************
 Function Name   : R_USB_HmscModeSense10
 Description     : ModeSense10
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
                 : uint8_t      *buff   : [OUT]Pointer to the buffer area/[IN]buff[0] Page Code
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscModeSense10 (usb_utr_t *ptr, uint16_t side, uint8_t *buff)
{
    uint8_t cbwcb[12];
    uint8_t length;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_MODE_SENSE10;

    /* Set LUN / DBD=1 */
    /* b7-b5:LUN (=0),b4-b0:Reserved */
    cbwcb[1] = 0x00;

    /* b7-b6:PageControl = Current values(=0),b5-b0:PageCode */
    cbwcb[2] = buff[0];

    switch (buff[0])    /* [IN]buff[0] Page Code */
    {
        case 0x01:  /* Read-Write Error Recovery Page */
        case 0x08:  /* Caching Page */
        case 0x1B:  /* Removable Block Access Capacities Page */
            length = 20;    /* 8 + 12 */
        break;
        case 0x1C:  /* Timer & Protect Page */
            length = 16;    /* 8 + 8 */
        break;
        case 0x3F:  /* Return all pages(valid only for MODE SENSE command) */
            length = 44;    /* 8 + 12 + 12 +12 */
        break;
        default:
            return USB_PAR;
        break;
    }

    /* Allocation length */
    cbwcb[7] = 0x00;    /* MSB */
    cbwcb[8] = length;  /* LSB */

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscModeSense10
 ******************************************************************************/


/******************************************************************************
 Function Name   : R_USB_HmscModeSelect10
 Description     : ModeSelect6
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     side    : Drive number
                 : uint8_t      *buff   : Pointer to the buffer area
                 :              buff[0]-[7]:Mode Parameter Header
                 :              buff[8]-[n]:Page(s)
                 :               buff[8] b7:Parameter Savable(PS)
                 :               buff[8] b6:Reserved
                 :               buff[8] b5-b0:Page Code
 Return value    : uint16_t : 
 ******************************************************************************/
uint16_t R_USB_HmscModeSelect10 (usb_utr_t *ptr, uint16_t side, uint8_t *buff)
{
    uint8_t cbwcb[12];
    uint8_t length = 18;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_MODE_SELECT10;

    /* Logical Unit Number = 0/ Save Pages(SP) = 0 */
    cbwcb[1] = 0x10;

    switch ((buff[8] & 0x3f))
    {
        case 0x01:  /* Read-Write Error Recovery Page */
        case 0x08:  /* Caching Page */
        case 0x1B:  /* Removable Block Access Capacities Page */
            length = 20;    /* 8 + 12 */
        break;
        case 0x1C:  /* Timer & Protect Page */
            length = 16;    /* 8 + 8 */
        break;
        default:
            return USB_PAR;
        break;
    }

    /* Parameter list length */
    cbwcb[7] = 0x00;    /* MSB */
    cbwcb[8] = length;  /* LSB */

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t*) &cbwcb, (uint32_t) length, side);

    /* Data OUT */
    hmsc_retval = usb_hmsc_data_out(ptr, side, buff, (uint32_t) length);
    return (hmsc_retval);
}
/******************************************************************************
 End of function R_USB_HmscModeSelect10
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscGetDevSts
 Description     : Responds to HMSCD operation state
 Arugments       : uint16_t     side    : Drive number
 Return value    : uint16_t :
 ******************************************************************************/
uint16_t R_USB_HmscGetDevSts (uint16_t side)
{
    return (g_usb_hmsc_drvno_tbl[side].use_flag);
}
/******************************************************************************
 End of function R_USB_HmscGetDevSts
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscAllocDrvno
 Description     : Alloc Drive no.
 Arguments       : uint16_t devadr       : Device address
 Return value    : Drive no.
 ******************************************************************************/
uint16_t R_USB_HmscAllocDrvno (uint16_t devadr)
{
    uint16_t side;
    uint16_t ipno;

    if (USBA_ADDRESS_OFFSET == (devadr & USB_IP_MASK))
    {
        ipno = USB_IP1;
    }
    else
    {
        ipno = USB_IP0;
    }
    devadr &= USB_ADDRESS_MASK;

    for (side = 0; side < USB_MAXSTRAGE; side++)
    {
        if ( USB_NOUSE == g_usb_hmsc_drvno_tbl[side].use_flag)
        {
            g_usb_hmsc_drvno_tbl[side].use_flag = USB_TRUE;
            g_usb_hmsc_drvno_tbl[side].devadr = devadr;
            g_usb_hmsc_drvno_tbl[side].ip = ipno;
            return side;
        }
    }

    USB_PRINTF0("DRIVE ALLOC ERROR");
    return USB_ERROR;
}
/******************************************************************************
 End of function R_USB_HmscAllocDrvno
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscFreeDrvno
 Description     : Release Drive no.
 Arugments       : uint16_t     side    : Drive number
 Return value    : result
 ******************************************************************************/
uint16_t R_USB_HmscFreeDrvno (uint16_t side)
{
    if (side > USB_MAXSTRAGE)
    {
        return USB_ERROR;
    }

    g_usb_hmsc_drvno_tbl[side].use_flag = USB_NOUSE;
    g_usb_hmsc_drvno_tbl[side].ip = USB_NOUSE;
    g_usb_hmsc_drvno_tbl[side].devadr = USB_NOUSE;
    return USB_OK;
}
/******************************************************************************
 End of function R_USB_HmscFreeDrvno
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_HmscRefDrvno
 Description     : Get Drive no.
 Arguments       : uint16_t devadr       : Device address
 Return value    : Drive no.
 ******************************************************************************/
uint16_t R_USB_HmscRefDrvno (uint16_t devadr)
{
    uint16_t side;
    uint16_t ipno;

    if ((devadr & USB_IP_MASK) == USBA_ADDRESS_OFFSET)
    {
        ipno = USB_IP1;
    }
    else
    {
        ipno = USB_IP0;
    }
    devadr &= USB_ADDRESS_MASK;

    for (side = 0; side < USB_MAXSTRAGE; side++)
    {
        if ((devadr == g_usb_hmsc_drvno_tbl[side].devadr) && (ipno == g_usb_hmsc_drvno_tbl[side].ip))
        {
            return side;
        }
    }
    return USB_ERROR;
}
/******************************************************************************
 End of function R_USB_HmscRefDrvno
 ******************************************************************************/

#if defined(USB_CFG_HMSC_USE)
/******************************************************************************
Function Name   : R_USB_HmscStrgCmd
Description     : Processing for MassStorage(ATAPI) command.
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : uint8_t       *buf    : Pointer to the buffer area to store the transfer data
                : uint16_t      command : ATAPI command
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t   R_USB_HmscStrgCmd(usb_ctrl_t *p_ctrl, uint8_t *buf, uint16_t command)
{
    usb_err_t   err;
    usb_info_t  info;
    usb_utr_t   utr;
    uint8_t     side;
    uint16_t    ret;

    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if( (USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) )
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX63N)
    if( USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX63N) */

#endif /* #if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    err = R_USB_HmscGetDriveNo(p_ctrl, &side);
    if (USB_SUCCESS != err)
    {
        return USB_ERR_NG;
    }

    ret = R_USB_HmscStrgUserCommand(&utr, side, command, buf, usb_hmsc_strg_cmd_complete);
    if (USB_PAR == ret)
    {
#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
        return USB_ERR_PARA;
#endif /* #if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */
    }
    if (USB_OK != ret)
    {
        return USB_ERR_NG;
    }
    return USB_SUCCESS;

}
/******************************************************************************
 End of function R_USB_HmscStrgCmd
 ******************************************************************************/


/******************************************************************************
Function Name   : R_USB_HmscGetDriveNo
Description     : Get number of Storage drive.
Arguments       : usb_ctrl_t    *p_ctrl     : Pointer to usb_ctrl_t structure
                : uint8_t       *p_drive    : Store address for Drive No.
Return value    : usb_err_t error code      : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t     R_USB_HmscGetDriveNo(usb_ctrl_t *p_ctrl, uint8_t *p_drive)
{
    usb_info_t  info;
    usb_utr_t   utr;
    volatile uint16_t   address;

    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if( (USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) )
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) ||  defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T)
    if( USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    address = p_ctrl->address;
    if (USB_IP1 == p_ctrl->module)
    {
        address |= USBA_ADDRESS_OFFSET;
    }

    *p_drive = (uint8_t)R_USB_HmscRefDrvno(address);
    if (USB_ERROR == *p_drive)
    {
        return USB_ERR_NG;
    }

    return USB_SUCCESS;

}
/******************************************************************************
 End of function R_USB_HmscGetDriveNo
 ******************************************************************************/

#endif  /* defined(USB_CFG_HMSC_USE) */

/******************************************************************************
 End  Of File
 ******************************************************************************/
