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
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_ether.c
* Version      : 3.00
* Description  : Ethernet module device driver
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.02.2010 1.00     First Release
*         : 03.03.2010 1.01     Buffer size is aligned on the 32-byte boundary.
*         : 08.03.2010 1.02     Modification of receiving method
*         : 06.04.2010 1.03     RX62N changes
*         : 29.03.2011 1.04     Enhancements for better link detection,
*                               autonegotiation, and more.
*         : 08.07.2011 2.00     Second release
*         : 21.08.2012 3.00     Third release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdio.h>
#include <stddef.h>
#if defined(__GNUC__) || defined(GRSAKURA)
#include "../T4_src/t4define.h"
#else
#include <machine.h>
#endif
#include "rx64m/iodefine.h"
#include "r_ether.h"
#include "phy.h"
#include "r_ether_local.h"

#if defined(__GNUC__) || defined(GRSAKURA)
void lan_inthdr(void);
#endif

#define ETHC_DEBUG
/// #define LINK_DEBUG

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
/* 
 * The flag which controls the pause frame.
 * 
 * Value and state of flag
 * ETHER_FLAG_OFF (0): The pause frame is not used (default). 
 * ETHER_FLAG_ON  (1): The pause frame is used. 
 */
volatile uint8_t g_ether_PauseFrameEnableFlag = ETHER_FLAG_OFF;

/*
 * The flag indicatives of the state that the interrupt of Link Up/Down occur.
 * 
 * Value and state of flag
 * ETHER_FLAG_OFF         (0) : The Link up/down interrupt has not been generated. 
 * ETHER_FLAG_ON_LINK_OFF (2) : The Link down interrupt was generated. 
 * ETHER_FLAG_ON_LINK_ON  (3) : The Link up interrupt was generated. 
 * 
 * If the R_ETHER_LinkProcess function is called, and the interrupt processing of Link Up/Down is done,
 * this flag becomes ETHER_FLAG_OFF(0). 
 */
volatile uint8_t g_ether_LchngFlag;

/*
 * The flag indicatives of the state that the interrupt of Link Up/Down occur.
 * 
 * Value and state of flag
 * ETHER_FLAG_OFF (0): It is not possible to communicate. 
 * ETHER_FLAG_ON  (1): It is possible to communicate. 
 */
volatile uint8_t g_ether_TransferEnableFlag;

/* This variable is for the sample program. */
volatile uint8_t g_magic_packet_detect;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/**
 * Private global function prototyes
 */
static void    _R_Ether_ResetMAC(void);
static void    _R_Ether_InitDescriptors(void);
static void    _R_Ether_ConfigEthernet(const uint8_t mode);
static void    _R_Ether_PauseResolution(uint8_t local_ability, uint8_t partner_ability,
                              uint16_t *tx_pause, uint16_t *rx_pause);
static void    ether_configure_mac(const uint8_t *mac_addr, const uint8_t mode);
static int32_t ether_do_link(const uint8_t mode);

/**
 * Private global variables
 */

/* Pointer to the receive descriptors */
static descriptor_s * app_rx_desc = NULL;

/* Pointer to the transmit descriptors */
static descriptor_s * app_tx_desc = NULL;

/*
 * The flag indicatives of the state that the interrupt of magic packet detection occur.
 *
 * Value and state of flag
 * ETHER_FLAG_OFF (0): The interrupt of the magic packet detection has not been generated. 
 * ETHER_FLAG_ON  (1): The interrupt of the magic packet detection was generated. 
 *
 * If the R_ETHER_LinkProcess function is called, and the interrupt processing of the magic packet detection is done,
 * this flag becomes ETHER_FLAG_OFF(0). 
 */
static uint8_t  g_ether_MpdFlag;

static uint8_t  mac_addr_buf[6];


/**
 * PAUSE Resolution as documented in IEEE 802.3-2008_section2 Annex
 * 28B, Table 28B-3. The following table codify logic that
 * determines how the PAUSE is configured for local transmitter
 * and receiver and partner transmitter and receiver.
 */
static const pauseresolution_s pause_resolution[PAUSE_TABLE_ENTRIES] =
{
    { PAUSE_MASKC, PAUSE_VAL0, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
    { PAUSE_MASKE, PAUSE_VAL4, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
    { PAUSE_MASKF, PAUSE_VAL6, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
    { PAUSE_MASKF, PAUSE_VAL7, XMIT_PAUSE_ON,  RECV_PAUSE_OFF },
    { PAUSE_MASKE, PAUSE_VAL8, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
    { PAUSE_MASKA, PAUSE_VALA, XMIT_PAUSE_ON,  RECV_PAUSE_ON  },
    { PAUSE_MASKF, PAUSE_VALC, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
    { PAUSE_MASKF, PAUSE_VALD, XMIT_PAUSE_OFF, RECV_PAUSE_ON  }
};

/**
 * Receive, transmit descriptors and their buffer.  They are
 * defined with section pragma directives to easly locate them
 * on the memory map.
 */
#if defined(__GNUC__) || defined(GRSAKURA)
static descriptor_s rx_descriptors[EMAC_NUM_RX_DESCRIPTORS] __attribute__ ((aligned(32)));
static descriptor_s tx_descriptors[EMAC_NUM_TX_DESCRIPTORS] __attribute__ ((aligned(32)));
static etherbuffer_s ether_buffers __attribute__ ((aligned(32)));
#else
#pragma section _RX_DESC
static descriptor_s    rx_descriptors[EMAC_NUM_RX_DESCRIPTORS];
#pragma section _TX_DESC
static descriptor_s    tx_descriptors[EMAC_NUM_TX_DESCRIPTORS];
#pragma section _ETHERNET_BUFFERS
/* 
 * As for Ethernet buffer, the size of total buffer which are use for transmission and the reception is secured.
 * The total buffer's size which the value is integrated from  EMAC_NUM_BUFFERS (buffer number) and 
 * EMAC_BUFSIZE (the size of one buffer).
 * The EMAC_BUFSIZE and EMAC_NUM_BUFFERS are defined by macro in the file "r_ether_local.h".
 * It is sequentially used from the head of the buffer as a receive buffer or a transmission buffer.
 */
static etherbuffer_s   ether_buffers;
#pragma section
#endif

static uint16_t link_proc_count_;
static int link_proc_loop_;

/**
 * Renesas Ethernet API functions
 */

/***********************************************************************************************************************
* Function Name: R_ETHER_Open_ZC2
* Description  : After ETHERC, EDMAC, and PHY-LSI are reset in software, an auto negotiation of PHY-LSI is begun.
*                Afterwards, the link signal change interrupt is permitted. 
* Arguments    : ch - Ethernet channel number
*                mac_addr - MAC address
* Return Value : R_ETHER_OK
*                R_ETHER_ERROR
***********************************************************************************************************************/
int32_t R_ETHER_Open_ZC2(const uint8_t *mac_addr)
{
    int16_t phy_ret;
    int32_t ret;

    /* Initialize the flags */
    g_ether_TransferEnableFlag = ETHER_FLAG_OFF;
    g_ether_MpdFlag            = ETHER_FLAG_OFF;
    g_ether_LchngFlag          = ETHER_FLAG_OFF;

    mac_addr_buf[0] = mac_addr[0];
    mac_addr_buf[1] = mac_addr[1];
    mac_addr_buf[2] = mac_addr[2];
    mac_addr_buf[3] = mac_addr[3];
    mac_addr_buf[4] = mac_addr[4];
    mac_addr_buf[5] = mac_addr[5];

    /* Software reset */
    _R_Ether_ResetMAC();

    /* Software reset the PHY */
    phy_ret = phy_init();
    if (R_PHY_OK == phy_ret)
    {
        phy_start_autonegotiate();

        /* Clear all ETHERC status BFR, PSRTO, LCHNG, MPD, ICD */
        ETHERC0.ECSR.LONG = 0x00000037;
        /* Clear all EDMAC status bits */
        EDMAC0.EESR.LONG  = 0x47FF0F9F;

        /* Enable interrupts of interest only. */
        ETHERC0.ECSIPR.BIT.LCHNGIP = 1;
        EDMAC0.EESIPR.BIT.ECIIP    = 1;
        
        /* Set Ethernet interrupt level and enable */
        ICU.IPR[IPR_ICU_GROUPAL1].BIT.IPR = ETHER_INTERRUPT_LEVEL;
        ICU.GENAL1.BIT.EN4 = 1;
        ICU.IER[IER_ICU_GROUPAL1].BIT.IEN1 = 1;

        ret = R_ETHER_OK;
    }
    else
    {
        ret = R_ETHER_ERROR;
    }

    return ret;
} /* End of function R_ETHER_Open_ZC2() */

/***********************************************************************************************************************
* Function Name: R_ETHER_Close_ZC2
* Description  : Disables Ethernet peripheral
* Arguments    : ch - Ethernet channel number
* Return Value : R_ETHER_OK
*                R_ETHER_ERROR
***********************************************************************************************************************/
int32_t R_ETHER_Close_ZC2(void)
{
    /* Disable Ethernet interrupt. */
    ICU.IER[IER_ICU_GROUPAL1].BIT.IEN1 = 0;
    ICU.GENAL1.BIT.EN4 = 0;

    /* Disable TE and RE  */
    ETHERC0.ECMR.LONG = 0x00000000;

    /* Initialize the flags */
    g_ether_TransferEnableFlag   = ETHER_FLAG_OFF;
    g_ether_MpdFlag              = ETHER_FLAG_OFF;
    g_ether_LchngFlag            = ETHER_FLAG_OFF;

    return R_ETHER_OK;
} /* End of function R_ETHER_Close_ZC2() */




/***********************************************************************************************************************
* Function Name: R_ETHER_Read_ZC2
* Description  : Receives an Ethernet frame.  Sets the passed
*                buffer pointer to the Ethernet frame buffer
*                from the driver. This makes the data available to
*                the caller as a zero-copy operation.
* Arguments    : ch - Ethernet channel number
*                buf - pointer to the Ethernet driver buffer
* Return Value : Number of bytes received (Value greater than zero)
*                R_ETHER_NO_DATA
*                R_ETHER_ERROR_LINK - 
*                    The auto negotiation processing is not completed and sending and receiving is not permitted. 
*                R_ETHER_ERROR_MPDE -
*                    Doesn't receive the data to the receive buffer for the detection mode of magic packet. 
***********************************************************************************************************************/
int32_t R_ETHER_Read_ZC2(void **buf)
{
    int32_t num_recvd;
    int32_t ret;
    /* When the Link up processing is not completed, return error */
    if (ETHER_FLAG_OFF == g_ether_TransferEnableFlag)
    {
        ret = R_ETHER_ERROR_LINK;
    }
    /* In case of detection mode of magic packet, return error. */
    else if (1 ==ETHERC0.ECMR.BIT.MPDE)
    {
        ret = R_ETHER_ERROR_MPDE;
    }
    /* When the Link up processing is completed */
    else
    {
        while (1)
        {
            /* When receive data exists. */
            if (RACT != (app_rx_desc->status & RACT))
            {
                if (app_rx_desc->status & RFE)
                {
                    /* The buffer is released at the error.  */
                    ret = R_ETHER_Read_ZC2_BufRelease();
                }
                else
                {
                    /**
                     * Pass the pointer to received data to application.  This is
                     * zero-copy operation.
                     */
                    *buf = (void *)app_rx_desc->buf_p;

                    /* Get bytes received */
                    num_recvd = app_rx_desc->size;
                    ret = num_recvd;
                    break;
                }
            }
            else
            {
                ret = R_ETHER_NO_DATA;
                break;
            }
        }
    }
    return ret;
} /* End of function R_ETHER_Read_ZC2() */

/***********************************************************************************************************************
* Function Name: R_ETHER_Read_ZC2_BufRelease
* Description  : Release the receive buffer.
* Arguments    : ch - Ethernet channel number
* Return Value : R_ETHER_OK
*                R_ETHER_ERROR_LINK - 
*                    The auto negotiation processing is not completed and sending and receiving is not permitted. 
*                R_ETHER_ERROR_MPDE -
*                   Doesn't receive the data to the receive buffer for the detection mode of magic packet. 
***********************************************************************************************************************/
int32_t R_ETHER_Read_ZC2_BufRelease(void)
{
    int32_t ret;
    /* When the Link up processing is not completed, return error */
    if (ETHER_FLAG_OFF == g_ether_TransferEnableFlag)
    {
        ret = R_ETHER_ERROR_LINK;
    }
    /* In case of detection mode of magic packet, return error. */
    else if (1 == ETHERC0.ECMR.BIT.MPDE)
    {
        ret = R_ETHER_ERROR_MPDE;
    }
    /* When the Link up processing is completed */
    else
    {
        /* When receive data exists */
        if (RACT != (app_rx_desc->status & RACT))
        {
            /* Move to next descriptor */
            app_rx_desc->status |= RACT;
            app_rx_desc->status &= ~(RFP1 | RFP0 | RFE | RFS9_RFOVER | RFS8_RAD | RFS7_RMAF | \
                                     RFS4_RRF | RFS3_RTLF | RFS2_RTSF | RFS1_PRE | RFS0_CERF);
            app_rx_desc = app_rx_desc->next;
        }
        if (0x00000000L == EDMAC0.EDRRR.LONG)
        {
            /* Restart if stopped */
            EDMAC0.EDRRR.LONG = 0x00000001L;
        }
        ret = R_ETHER_OK;
    }
    return ret;
} /* End of function R_ETHER_Read_ZC2_BufRelease() */


/***********************************************************************************************************************
* Function Name: R_ETHER_Write_ZC2_GetBuf
* Description  : Get Points to the buffer pointer used by the stack.
* Arguments    : ch - Ethernet channel number
*                buf - buffer pointer
*                buf_size - buffer size
* Return Value : R_ETHER_OK
*                R_ETHER_ERROR_LINK - 
*                    The auto negotiation processing is not completed and sending and receiving is not permitted. 
*                R_ETHER_ERROR_MPDE - 
*                    The transmission is not permitted because of the detection mode of magic packet. 
*                R_ETHER_ERROR_TACT - 
*                    There is not becoming empty of the transmission buffer. 
***********************************************************************************************************************/
int32_t R_ETHER_Write_ZC2_GetBuf(void **buf, uint16_t *buf_size)
{
    int32_t ret;

    /* When the Link up processing is not completed, return error */
    if (ETHER_FLAG_OFF == g_ether_TransferEnableFlag)
    {
        ret = R_ETHER_ERROR_LINK;
    }
    /* In case of detection mode of magic packet, return error. */
    else if (1 == ETHERC0.ECMR.BIT.MPDE)
    {
        ret = R_ETHER_ERROR_MPDE;
    }
    /* When the Link up processing is completed */
    else
    {
        /* All transmit buffers are full */
        if (TACT == (app_tx_desc->status & TACT))
        {
            ret = R_ETHER_ERROR_TACT;
        }
        else
        {
            /* Give application another buffer to work with */
            *buf = app_tx_desc->buf_p;
            *buf_size = app_tx_desc->size;
            ret = R_ETHER_OK;
        }
    }
    return ret;
} /* End of function R_ETHER_Write_ZC2_GetBuf() */

/***********************************************************************************************************************
* Function Name: R_ETHER_Write_ZC2_SetBuf
* Description  : Transmits an Ethernet frame. 
*                The transmit descriptor points to the data to transmit. 
*                Data is sent directly from memory as a "zero copy" operation.
* Arguments    : ch - Ethernet channel number
*                len - length of data, in bytes, to transmit
* Return Value : R_ETHER_OK
*                R_ETHER_ERROR_LINK - 
*                    The auto negotiation processing is not completed and sending and receiving is not permitted. 
*                R_ETHER_ERROR_MPDE - 
*                    The transmission is not permitted because of the detection mode of magic packet. 
***********************************************************************************************************************/
int32_t R_ETHER_Write_ZC2_SetBuf(const uint32_t len)
{
    int32_t ret;

    /* When the Link up processing is not completed, return error */
    if (ETHER_FLAG_OFF == g_ether_TransferEnableFlag)
    {
        ret = R_ETHER_ERROR_LINK;
    }
    /* In case of detection mode of magic packet, return error. */
    else if (1 == ETHERC0.ECMR.BIT.MPDE)
    {
        ret = R_ETHER_ERROR_MPDE;
    }
    /* When the Link up processing is completed */
    else
    {
        /* The data of the buffer is made active.  */
        app_tx_desc->bufsize = len;
        app_tx_desc->status &= ~(TFP1 | TFP0);
        app_tx_desc->status |= (TFP1 | TFP0 | TACT);
        app_tx_desc = app_tx_desc->next;
        
        if (0x00000000L == EDMAC0.EDTRR.LONG)
        {
            /* Restart if stopped */
            EDMAC0.EDTRR.LONG = 0x00000001L;
        }
        
        ret = R_ETHER_OK;
    }
    return ret;
} /* End of function R_ETHER_Write_ZC2_SetBuf() */



/***********************************************************************************************************************
* Function Name: R_Ether_CheckLink
* Description  : Verifies the Etherent link is up or not.
* Arguments    : ch - Ethernet channel number
* Return Value : R_ETHER_OK (Link is up)
*                R_ETHER_ERROR (Link is down)
***********************************************************************************************************************/
int32_t R_Ether_CheckLink_ZC(void)
{
    int16_t status;

    status = phy_get_link_status();

    if (R_PHY_ERROR == status)
    {
        /* Link is down */
        return R_ETHER_ERROR;
    }
    else
    {
        /* Link is up */
        return R_ETHER_OK;
    }
} /* End of function R_Ether_CheckLink_ZC() */

/***********************************************************************************************************************
* Function Name: R_ETHER_LinkProcess
* Description  : The Link up processing, the Link down processing, and the magic packet detection processing are executed. 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ETHER_LinkProcess(void)
{
    int32_t ret;
    /* When the magic packet is detected. */
    if (ETHER_FLAG_ON == g_ether_MpdFlag)
    {
        g_ether_MpdFlag = ETHER_FLAG_OFF;
        R_ETHER_Callback_WakeOnLAN();
    }
    /* When the link is up */
    if (ETHER_FLAG_ON_LINK_ON == g_ether_LchngFlag)
    {
        g_ether_LchngFlag = ETHER_FLAG_OFF;
        
        /* 
         * The Link Up/Down is confirmed by the Link Status bit of PHY register1, 
         * because the LINK signal of PHY-LSI is used for LED indicator, and 
         * isn't used for notifing the Link Up/Down to external device.
         */
        ret = R_Ether_CheckLink_ZC();
        if (R_ETHER_OK == ret)
        {
            /*
             * ETHERC and EDMAC are set after ETHERC and EDMAC are reset in software
             * and sending and receiving is permitted. 
             */
            ether_configure_mac(mac_addr_buf, NO_USE_MAGIC_PACKET_DETECT);
            ether_do_link(NO_USE_MAGIC_PACKET_DETECT);
            
            g_ether_TransferEnableFlag = ETHER_FLAG_ON;
            R_ETHER_Callback_Link_On();
        }
        else
        {
///			printf("+");
            /* no proccess */
        }
    }
    /* When the link is down */
    else if (ETHER_FLAG_ON_LINK_OFF == g_ether_LchngFlag)
    {
        g_ether_LchngFlag = ETHER_FLAG_OFF;
        /* 
         * The Link Up/Down is confirmed by the Link Status bit of PHY register1, 
         * because the LINK signal of PHY-LSI is used for LED indicator, and 
         * isn't used for notifing the Link Up/Down to external device.
         */
        ret = R_Ether_CheckLink_ZC();
        if (R_ETHER_ERROR == ret)
        {
            /* Disable receive and transmit. */
            ETHERC0.ECMR.BIT.RE = 0;
            ETHERC0.ECMR.BIT.TE = 0;
            
            g_ether_TransferEnableFlag = ETHER_FLAG_OFF;
            R_ETHER_Callback_Link_Off();
        }
        else
        {
///			printf(".");
            /* no proccess */
        }
    }
    else
    {
#ifdef LINK_DEBUG
		link_proc_count_++;
		if(link_proc_count_ >= 100000) {
			printf("Link no proccess (%d)\n", link_proc_loop_);
			link_proc_loop_++;
			link_proc_count_ = 0;
		}
#endif
        /* no proccess */
    }
} /* End of function R_ETHER_LinkProcess() */

/***********************************************************************************************************************
* Function Name: R_ETHER_WakeOnLAN
* Description  : The setting of ETHERC is changed from a usual sending and
*                receiving mode to the magic packet detection mode. 
* Arguments    : ch - Ethernet channel number
* Return Value : R_ETHER_OK
*                R_ETHER_ERROR - Became Link down while changing the setting. 
*                R_ETHER_ERROR_LINK - 
*                    The auto negotiation processing is not completed and sending and receiving is not permitted. 
***********************************************************************************************************************/
int32_t R_ETHER_WakeOnLAN(void)
{
    int32_t ret;

    /* When the Link up processing is not completed, return error */
    if (ETHER_FLAG_OFF == g_ether_TransferEnableFlag)
    {
        ret = R_ETHER_ERROR_LINK;
    }
    /* When the Link up processing is completed */
    else
    {
        /* Change to the magic packet detection mode.  */
        ether_configure_mac(mac_addr_buf, USE_MAGIC_PACKET_DETECT);
        ret = ether_do_link(USE_MAGIC_PACKET_DETECT);
        if (R_ETHER_OK == ret)
        {
            /* It is confirmed not to become Link down while changing the setting. */
            if (LINK_PRESENT == ETHERC0.PSR.BIT.LMON)
            {
                ret = R_ETHER_OK;
            }
            else
            {
                ret = R_ETHER_ERROR;
            }
        }
        else
        {
            ret = R_ETHER_ERROR;
        }
    }
    return ret;
} /* End of function R_ETHER_WakeOnLAN() */

/***********************************************************************************************************************
* Function Name: R_ETHER_Callback_Link_On
* Description  : Callback function that notifies user to have become Link up.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ETHER_Callback_Link_On(void)
{
    /* Please add necessary processing when becoming Link up. */
} /* End of function R_ETHER_Callback_Link_On() */


/***********************************************************************************************************************
* Function Name: R_ETHER_Callback_Link_Off
* Description  : Callback function that notifies user to have become Link down.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ETHER_Callback_Link_Off(void)
{
    /* Please add necessary processing when becoming Link down. */
} /* End of function R_ETHER_Callback_Link_Off() */


/***********************************************************************************************************************
* Function Name: R_ETHER_Callback_WakeOnLAN
* Description  : Callback function that notifies user to have detected magic packet.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ETHER_Callback_WakeOnLAN(void)
{
    /* Please add necessary processing when magic packet is detected.  */
    /*
     * After the close function is called, the open function is called 
     * to have to set ETHERC to a usual operational mode
     * to usually communicate after magic packet is detected. 
     */
    R_ETHER_Close_ZC2();
    R_ETHER_Open_ZC2(mac_addr_buf);
    
    /* This code is for the sample program. */
    g_magic_packet_detect = 1;
    
} /* End of function R_ETHER_Callback_WakeOnLAN() */



/**
 * Private functions
 */

/***********************************************************************************************************************
* Function Name: _R_Ether_ResetMAC
* Description  : The EDMAC and EtherC are reset through the software reset.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void _R_Ether_ResetMAC(void)
{
    uint32_t i;

    /* Software reset */
    EDMAC0.EDMR.BIT.SWR = 1;

    /* Delay */
    /*
     * Waiting time until the initialization of ETHERC and EDMAC is completed is 64 cycles
     * in the clock conversion of an internal bus of EDMAC. 
     */
    for (i = 0; i < 0x00000100; i++)
    {
		asm("nop");
    }
} /* End of function _R_Ether_ResetMAC() */

/***********************************************************************************************************************
* Function Name: _R_Ether_InitDescriptors
* Description  : The EDMAC descriptors and the driver buffers are initialized.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void _R_Ether_InitDescriptors(void)
{
    descriptor_s *descriptor;
    uint32_t i;

    /* Initialize the receive descriptors */
    for(i = 0; i < EMAC_NUM_RX_DESCRIPTORS; i++)
    {
        descriptor = &(rx_descriptors[i]);
        descriptor->buf_p = &(ether_buffers.buffer[i][0]);
        descriptor->bufsize = EMAC_BUFSIZE;
        descriptor->size = 0;
        descriptor->status = RACT;
        descriptor->next = (descriptor_s *) &rx_descriptors[i + 1];
    }

    /* The last descriptor points back to the start */
    descriptor->status |= RDLE;
    descriptor->next = (descriptor_s *) &rx_descriptors[0];

    /* Initialize application receive descriptor pointer */
    app_rx_desc  = &(rx_descriptors[0]);


    /* Initialize the transmit descriptors */
    for (i = 0; i < EMAC_NUM_TX_DESCRIPTORS; i++)
    {
        descriptor = &(tx_descriptors[i]);
        descriptor->buf_p = &(ether_buffers.buffer[EMAC_NUM_RX_DESCRIPTORS + i][0]);;
        descriptor->bufsize = 0;
        descriptor->size = EMAC_BUFSIZE;
        descriptor->status = 0;
        descriptor->next = (descriptor_s *) &(tx_descriptors[i + 1]);
    }

    /* The last descriptor points back to the start */
    descriptor->status |= TDLE;
    descriptor->next = (descriptor_s *) &(tx_descriptors[0]);

    /* Initialize application transmit descriptor pointer */
    app_tx_desc  = &(tx_descriptors[0]);
} /* End of function _R_Ether_InitDescriptors() */

/***********************************************************************************************************************
* Function Name: _R_Ether_ConfigEthernet
* Description  : Configure the Ethernet Controller (EtherC) and the Ethernet
*                Direct Memory Access controller (EDMAC).
* Arguments    : mode - 
*                   The operational mode is specified. 
*                   NO_USE_MAGIC_PACKET_DETECT (0) - Communicate mode usually
*                   USE_MAGIC_PACKET_DETECT    (1) - Magic packet detection mode
* Return Value : None
***********************************************************************************************************************/
static void _R_Ether_ConfigEthernet(const uint8_t mode)
{
    /* Magic packet detecion mode */
    if (USE_MAGIC_PACKET_DETECT == mode)
    {
        ETHERC0.ECSIPR.LONG = 0x00000006;
        EDMAC0.EESIPR.LONG  = 0x00400000;
    }
    /* Normal mode */
    else
    {
        /* LINK Signal Change Interrupt Enable */
        ETHERC0.ECSIPR.BIT.LCHNGIP = 1;
        EDMAC0.EESIPR.BIT.ECIIP    = 1;
        
        /**
         * This is sample code.
         * Sets up interrupt when you use interrupts.
         * Enable interrupts of interest only.
         */
#if 1
        EDMAC0.EESIPR.BIT.FRIP = 1;
        EDMAC0.EESIPR.BIT.TCIP = 1;
#endif
    }

    /* Ethernet length 1514bytes + CRC and intergap is 96-bit time */
    ETHERC0.RFLR.LONG = 1518;
    ETHERC0.IPGR.LONG = 0x00000014;

#ifdef __LIT
    /* Set little endian mode */
    EDMAC0.EDMR.BIT.DE = 1;
#endif

#if defined(__GNUC__) || defined(GRSAKURA)
    EDMAC0.RDLAR = app_rx_desc;
    EDMAC0.TDLAR = app_tx_desc;
#else
    /* Initialize Rx descriptor list address */
    /* Casting the pointer to a uint32_t type is valid because the Renesas Compiler uses 4 bytes per pointer. */
    EDMAC.RDLAR = (uint32_t) app_rx_desc;
    /* Initialize Tx descriptor list address */
    /* Casting the pointer to a uint32_t type is valid because the Renesas Compiler uses 4 bytes per pointer. */
    EDMAC.TDLAR = (uint32_t) app_tx_desc;
#endif
    /* Don't reflect the EESR.RMAF bit status in the RD0.RFS bit in the receive descriptor */
    EDMAC0.TRSCER.LONG = 0x00000080;
    /* Threshold of Tx_FIFO */
    /* To prevent a transmit underflow, setting the initial value (store and forward modes) is recommended. */
    EDMAC0.TFTR.LONG = 0x00000000;
    /* transmit fifo & receive fifo is 2048 bytes */
    EDMAC0.FDR.LONG  = 0x00000707;
    /*  Configure receiving method
    b0      RNR - Receive Request Bit Reset - Continuous reception of multiple frames is possible.
    b1      RNC - Receive Request Bit Non-Reset Mode - The RR bit is automatically reset.
    b31:b2  Reserved set to 0
    */
    EDMAC0.RMCR.LONG  = 0x00000001;

} /* End of function _R_Ether_ConfigEthernet() */

/***********************************************************************************************************************
* Function Name: _R_Ether_PauseResolution
* Description  : Determines PAUSE frame generation and handling. Uses
*                the resolution Table 28B-3 of IEEE 802.3-2008.
* Arguments    : local_ability - local PAUSE capability (2 least significant bits)
*                partner_ability - link partner PAUSE capability (2 least significant bits)
*                *tx_pause - pointer to location to store the
*                            result of the table lookup for transmit
*                            PAUSE. 1 is enable, 0 is disable.
*                *rx_pause - pointer to location to store the
*                            result of the table lookup for receive
*                            PAUSE. 1 is enable, 0 is disable.
* Return Value : None
***********************************************************************************************************************/
static void _R_Ether_PauseResolution(uint8_t local_ability, uint8_t partner_ability,
                              uint16_t *tx_pause, uint16_t *rx_pause)
{
    uint32_t i;
    uint8_t  ability_compare;

    /**
     * Arrange the bits so that they correspond to the Table 28B-3
     * of the IEEE 802.3 values.
     */
    ability_compare = ((local_ability & LINK_RES_ABILITY_MASK) << LINK_RES_LOCAL_ABILITY_BITSHIFT) |
                       (partner_ability & LINK_RES_ABILITY_MASK);

    /* Walk through the look up table */
    for (i = 0; i < PAUSE_TABLE_ENTRIES; i++)
    {
        if ( (ability_compare & pause_resolution[i].mask) == pause_resolution[i].value )
        {
            *tx_pause = pause_resolution[i].transmit;
            *rx_pause = pause_resolution[i].receive;
            return;
        }
   }
} /* End of function _R_Ether_PauseResolution() */


/***********************************************************************************************************************
* Function Name: ether_configure_mac
* Description  : Software reset is executed, and ETHERC and EDMAC are configured. 
* Arguments    : mac_addr - MAC address
*                mode - 
*                   The operational mode is specified. 
*                   NO_USE_MAGIC_PACKET_DETECT (0) - Communicate mode usually
*                   USE_MAGIC_PACKET_DETECT    (1) - Magic packet detection mode
* Return Value : None
***********************************************************************************************************************/
static void ether_configure_mac(const uint8_t *mac_addr, const uint8_t mode)
{
    uint32_t    mac_h, mac_l;

    /* Software reset */
    _R_Ether_ResetMAC();

    /* Set MAC address */
    mac_h = ((uint32_t)mac_addr[0] << 24) | \
            ((uint32_t)mac_addr[1] << 16) | \
            ((uint32_t)mac_addr[2] << 8 ) | \
            (uint32_t)mac_addr[3];

    mac_l = ((uint32_t)mac_addr[4] << 8 ) | \
             (uint32_t)mac_addr[5];

    ETHERC0.MAHR = mac_h;
    ETHERC0.MALR.LONG = mac_l;

    /* Initialize receive and transmit descriptors */
    _R_Ether_InitDescriptors();

    /* Perform rest of hardware interface configuration */
    _R_Ether_ConfigEthernet(mode);

} /* End of function ether_configure_mac() */


/***********************************************************************************************************************
* Function Name: ether_do_link
* Description  : Determines the partner PHY capability through
*                auto-negotiation process. The link abilities
*                are handled to determine duplex, speed and flow
*                control (PAUSE frames).
* Arguments    : mode - 
*                   The operational mode is specified. 
*                   NO_USE_MAGIC_PACKET_DETECT (0) - Communicate mode usually
*                   USE_MAGIC_PACKET_DETECT    (1) - Magic packet detection mode
* Return Value : R_ETHER_OK
*                R_ETHER_ERROR
***********************************************************************************************************************/
static int32_t ether_do_link(const uint8_t mode)
{
    int32_t  ret;
    uint16_t link_speed_duplex  = 0;
    uint16_t local_pause_bits   = 0;
    uint16_t partner_pause_bits = 0;
    uint16_t transmit_pause_set = 0;
    uint16_t receive_pause_set  = 0;
    uint16_t full_duplex        = 0;
    uint16_t link_result        = 0;

    /* Set the link status */
    link_result = phy_get_autonegotiate(&link_speed_duplex, &local_pause_bits, &partner_pause_bits);
    if (R_PHY_OK == link_result)
    {
        switch (link_speed_duplex)
        {
            /* Half duplex link */
            case PHY_LINK_100H:
                ETHERC0.ECMR.BIT.DM  = 0;
                ETHERC0.ECMR.BIT.RTM = 1;
                ret = R_ETHER_OK;
#ifdef ETHC_DEBUG
				printf("PHY Half duplex 100M\n");
#endif
                break;

            case PHY_LINK_10H:
                ETHERC0.ECMR.BIT.DM  = 0;
                ETHERC0.ECMR.BIT.RTM = 0;
                ret = R_ETHER_OK;
#ifdef ETHC_DEBUG
				printf("PHY Half duplex 10M\n");
#endif
                break;

            /* Full duplex link */
            case PHY_LINK_100F:
                ETHERC0.ECMR.BIT.DM  = 1;
                ETHERC0.ECMR.BIT.RTM = 1;
                full_duplex = 1;
                ret = R_ETHER_OK;
#ifdef ETHC_DEBUG
				printf("PHY Full duplex 100M\n");
#endif
                break;

            case PHY_LINK_10F:
                ETHERC0.ECMR.BIT.DM  = 1;
                ETHERC0.ECMR.BIT.RTM = 0;
                full_duplex = 1;
                ret = R_ETHER_OK;
#ifdef ETHC_DEBUG
				printf("PHY Full duplex 10M\n");
#endif
                break;

            default:
                ret = R_ETHER_ERROR;
                break;
        }

        /* At the communicate mode usually */
        if (NO_USE_MAGIC_PACKET_DETECT == mode)
        {
            
            /* When pause frame is used */
            if ((full_duplex) && (ETHER_FLAG_ON == g_ether_PauseFrameEnableFlag))
            {
                /* Set automatic PAUSE for 512 bit-time */
                ETHERC0.APR.LONG = 0x0000FFFF;
                /* Set unlimited retransmit of PAUSE frames */
                ETHERC0.TPAUSER.LONG = 0;
                /* PAUSE flow control FIFO settings. */
                EDMAC0.FCFTR.LONG = 0x00000000;
                /* Control of a PAUSE frame whose TIME parameter value is 0 is enabled. */
#if defined(__GNUC__) || defined(GRSAKURA)
                ETHERC0.ECMR.BIT.ZPF = 1;
#else
                ETHERC.ECMR.BIT.ZPE = 1;
#endif

                /**
                 * Enable PAUSE for full duplex link depending on
                 * the pause resolution results
                 */
                _R_Ether_PauseResolution(local_pause_bits, partner_pause_bits,
                                         &transmit_pause_set, &receive_pause_set);

                if (XMIT_PAUSE_ON == transmit_pause_set)
                {
                    /* Enable automatic PAUSE frame transmission */
                    ETHERC0.ECMR.BIT.TXF = 1;
                }
                else
                {
                    /* Disable automatic PAUSE frame transmission */
                    ETHERC0.ECMR.BIT.TXF = 0;
                }

                if (RECV_PAUSE_ON == receive_pause_set)
                {
                    /* Enable reception of PAUSE frames */
                    ETHERC0.ECMR.BIT.RXF = 1;
                }
                else
                {
                    /* Disable reception of PAUSE frames */
                    ETHERC0.ECMR.BIT.RXF = 0;
                }
            }
            /* When pause frame is not used */
            else
            {
                /* Disable PAUSE for half duplex link */
                ETHERC0.ECMR.BIT.TXF = 0;
                ETHERC0.ECMR.BIT.RXF = 0;
            }

            /* Enable receive and transmit. */
            ETHERC0.ECMR.BIT.RE = 1;
            ETHERC0.ECMR.BIT.TE = 1;

            /* Enable EDMAC receive */
            EDMAC0.EDRRR.LONG = 0x1;
        }
        /* At the magic packet detection mode */
        else
        {
            /* The magic packet detection is permitted. */
            ETHERC0.ECMR.BIT.MPDE = 1;
            /* Because data is not transmitted for the magic packet detection waiting, 
               only the reception is permitted. */
            ETHERC0.ECMR.BIT.RE = 1;
            
            /*
             * The reception function of EDMAC keep invalidity 
             * because the receive data don't need to be read when the magic packet detection mode.
             */
        }
    }
    else
    {
        ret = R_ETHER_ERROR;
    }

    return ret;
} /* End of function ether_do_link() */


/***********************************************************************************************************************
* Function Name: Excep_Ether_isr
* Description  : Interrupt handler for Ethernet receive and transmit interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
void INT_Excep_ICU_GROUPAL1(void) __attribute__ ((interrupt));
void INT_Excep_ICU_GROUPAL1(void)
#else
#pragma interrupt (Excep_Ether_isr(vect = VECT_ETHER_EINT, enable))
static void Excep_Ether_isr(void)
#endif
{
    uint32_t status_ecsr = ETHERC0.ECSR.LONG;
    uint32_t status_eesr = EDMAC0.EESR.LONG;
                                      
    /* When the ETHERC status interrupt is generated */
    if (status_eesr & EMAC_ECI_INT)
    {
#if 0  /* If ET_LINKSTA is not connected, LINK status is decected by using software polling. */
       /* When the link signal change interrupt is generated */
        if (status_ecsr & EMAC_LCHNG_INT)
        {
            /* The state of the link signal is confirmed and Link Up/Down is judged. */
            /* When becoming Link up */
            if (ETHERC.PSR.BIT.LMON == LINK_PRESENT)
            {
                g_ether_LchngFlag = ETHER_FLAG_ON_LINK_ON;
            }
            /* When Link becomes down */
            else
            {
                g_ether_LchngFlag = ETHER_FLAG_ON_LINK_OFF;
            }
        }
#endif
        /* When the Magic Packet detection interrupt is generated */
        if (status_ecsr & EMAC_MPD_INT)
        {
            g_ether_MpdFlag = ETHER_FLAG_ON;
        }
        /*
         * Because each bit of the ECSR register is cleared when one is written, 
         * the value read from the register is written and the bit is cleared. 
         */
        /* Clear all ETHERC status BFR, PSRTO, LCHNG, MPD, ICD */
        ETHERC0.ECSR.LONG = status_ecsr;
    }
    EDMAC0.EESR.LONG  = status_eesr; /* Clear EDMAC status bits */
	lan_inthdr();
    
    /* This is sample code */
#if 0
    if (status_eesr & EMAC_RFCOF_INT)
    {
    }
    if (status_eesr & EMAC_TC_INT)
    {
    }
    if (status_eesr & EMAC_FR_INT)
    {
    }
    if (status_eesr & EMAC_RDE_INT)
    {
    }
    if (status_eesr & EMAC_RFOF_INT)
    {
    }
    /*
     * Because each bit of the EESR register is cleared when one is written, 
     * the value read from the register is written and the bit is cleared. 
     */
    EDMAC.EESR.LONG  = status_eesr; /* Clear EDMAC status bits */
#endif

} /* End of function Excep_Ether_isr() */

