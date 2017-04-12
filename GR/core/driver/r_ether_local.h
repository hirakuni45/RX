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
* File Name	   : r_ether_local.h
* Version      : 1.00
* Description  : File that defines macro and structure seen only in "r_ether.c" file.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 21.08.2012 1.00     First Release
***********************************************************************************************************************/

#ifndef R_ETHER_LOCAL_H
#define R_ETHER_LOCAL_H

#include "../T4_src/t4define.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Please define the size of the sending and receiving buffer in the value where one frame can surely be stored 
   because the driver is single-frame/single-buffer processing.  */
#define EMAC_BUFSIZE                (1536)  /* Must be 32-byte aligned */
/* The number of Rx descriptors. */
#define EMAC_NUM_RX_DESCRIPTORS     (1)
/* The number of Tx descriptors. */
#define EMAC_NUM_TX_DESCRIPTORS     (1)

/**
 * The total number of EMAC buffers to allocate. The number of
 * total buffers is simply the sum of the number of transmit and
 * receive buffers.
 */
#define EMAC_NUM_BUFFERS   (EMAC_NUM_RX_DESCRIPTORS + (EMAC_NUM_TX_DESCRIPTORS))

/* Bit definition of interrupt factor of Ethernet interrupt */
#define EMAC_LCHNG_INT     (1UL << 2)
#define EMAC_MPD_INT       (1UL << 1)

#define EMAC_RFCOF_INT     (1UL << 24)
#define EMAC_ECI_INT       (1UL << 22)
#define EMAC_TC_INT        (1UL << 21)
#define EMAC_FR_INT        (1UL << 18)
#define EMAC_RDE_INT       (1UL << 17)
#define EMAC_RFOF_INT      (1UL << 16)

/* Bit definitions of status member of DescriptorS */
#define  TACT               (0x80000000)
#define  RACT               (0x80000000)
#define  TDLE               (0x40000000)
#define  RDLE               (0x40000000)
#define  TFP1               (0x20000000)
#define  RFP1               (0x20000000)
#define  TFP0               (0x10000000)
#define  RFP0               (0x10000000)
#define  TFE                (0x08000000)
#define  RFE                (0x08000000)

#define  RFS9_RFOVER        (0x00000200)
#define  RFS8_RAD           (0x00000100)
#define  RFS7_RMAF          (0x00000080)
#define  RFS4_RRF           (0x00000010)
#define  RFS3_RTLF          (0x00000008)
#define  RFS2_RTSF          (0x00000004)
#define  RFS1_PRE           (0x00000002)
#define  RFS0_CERF          (0x00000001)

#define  TWBI               (0x04000000)
#define  TFS8_TAD           (0x00000100)
#define  TFS3_CND           (0x00000008)
#define  TFS2_DLC           (0x00000004)
#define  TFS1_CD            (0x00000002)
#define  TFS0_TRO           (0x00000001)

/* Number of entries in PAUSE resolution table */
#define PAUSE_TABLE_ENTRIES (8)
/* Local device and link partner PAUSE settings */
#define XMIT_PAUSE_OFF      (0) /* The pause frame transmission is prohibited. */
#define RECV_PAUSE_OFF      (0) /* The pause frame reception is prohibited.    */
#define XMIT_PAUSE_ON       (1) /* The pause frame transmission is permitted.  */
#define RECV_PAUSE_ON       (1) /* The pause frame reception is permitted.     */
/* PAUSE link mask and shift values */
/*
 * The mask value and shift value which are for that shift the bits form a line and 
 * for comparing the bit information of PAUSE function which support the local device and 
 * Link partner with the assorted table(pause_resolution) which enable or disable the PAUSE frame. 
 */
#define LINK_RES_ABILITY_MASK           (3)
#define LINK_RES_LOCAL_ABILITY_BITSHIFT (2)

/**
 * Link status read from LMON bit of ETHERC PSR register.  The state is hardware dependent.
 */
#define LINK_PRESENT        (0) /* Please define the level of the LINKSTA signal when Link becomes up.   */
#define LINK_NOTPRESENT     (1) /* Please define the level of the LINKSTA signal when Link becomes down. */

/* Etherc mode */
#define NO_USE_MAGIC_PACKET_DETECT (0)
#define USE_MAGIC_PACKET_DETECT    (1)

/* Ethernet interrupt level definition */
#define ETHER_INTERRUPT_LEVEL      (1)  /* Please define the interruption level within the range of 1-15. */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/**
 * EDMAC descriptor as defined in the hardware manual. It is
 * modifed to support little endian CPU mode.
 */
struct DescriptorS
{
    __evenaccess uint32_t   status;
#if __LIT
/* Little endian */
    __evenaccess uint16_t   size;
    __evenaccess uint16_t   bufsize;
#else
/* Big endian */
    __evenaccess uint16_t   bufsize;
    __evenaccess uint16_t   size;

#endif
    uint8_t                 *buf_p;
    struct DescriptorS      *next;
};
typedef struct DescriptorS   descriptor_s;

/**
 * Ethernet buffer type definition.  
 */
struct EtherBufferS
{
    uint8_t  buffer[EMAC_NUM_BUFFERS][EMAC_BUFSIZE];
};
typedef struct EtherBufferS etherbuffer_s;

/**
 * PauseMaskE, PauseValE and pause_resolutionS are use to create
 * PAUSE resolution Table 28B-3 in IEEE 802.3-2008 standard.
 */
enum PauseMaskE
{
    PAUSE_MASK0, PAUSE_MASK1, PAUSE_MASK2, PAUSE_MASK3, PAUSE_MASK4, PAUSE_MASK5, PAUSE_MASK6, PAUSE_MASK7,
    PAUSE_MASK8, PAUSE_MASK9, PAUSE_MASKA, PAUSE_MASKB, PAUSE_MASKC, PAUSE_MASKD, PAUSE_MASKE, PAUSE_MASKF
};
typedef enum PauseMaskE  pausemask_e;

enum PauseValE
{
    PAUSE_VAL0, PAUSE_VAL1, PAUSE_VAL2, PAUSE_VAL3, PAUSE_VAL4, PAUSE_VAL5, PAUSE_VAL6, PAUSE_VAL7,
    PAUSE_VAL8, PAUSE_VAL9, PAUSE_VALA, PAUSE_VALB, PAUSE_VALC, PAUSE_VALD, PAUSE_VALE, PAUSE_VALF
};
typedef enum PauseValE   pauseval_e;

struct pause_resolutionS
{
    pausemask_e mask;
    pauseval_e  value;
    uint8_t     transmit;
    uint8_t     receive;
};
typedef struct pause_resolutionS  pauseresolution_s;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

#endif /* R_ETHER_LOCAL_H */
