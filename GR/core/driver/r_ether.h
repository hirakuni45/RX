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
* File Name    : r_ether.h
* Version      : 3.00
* Description  : Ethernet module device driver
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.02.2010 1.00     First Release
*         : 03.03.2010 1.01     Buffer size is aligned on the 32-byte boundary.
*         : 06.04.2010 1.02     RX62N changes
*         : 28.02.2011 1.03     RX62N enhancements for PAUSE frame generation 
*         : 08.07.2011 2.00     Second release 
*         : 21.08.2012 3.00     Third release
***********************************************************************************************************************/

#ifndef R_ETHER_H
#define R_ETHER_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdint.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* r_ether return definitions */
#define R_ETHER_OK           (0)
#define R_ETHER_ERROR        (-1)
#define R_ETHER_ERROR_LINK   (-2)
#define R_ETHER_ERROR_MPDE   (-3)   /* Error of operation mode of ETHERC. Sending and receiving is a prohibition 
                                       because of the detection mode of magic packet. */
#define R_ETHER_ERROR_TACT   (-4)   /* Transmission buffer dryness error. 
                                       Transmission buffer is prohibited to write because there is not empty in it. */
#define R_ETHER_NO_DATA      (0)

/*  Ether Interface definitions */
#define ETH_RMII_MODE        (0)
#define ETH_MII_MODE         (1)
/*  Select Ether Interface Mode     */
#define ETH_MODE_SEL         ETH_RMII_MODE	/* for GR-SAKURA (RX63N) */

#define ETHER_FLAG_OFF         (0)
#define ETHER_FLAG_ON          (1)
#define ETHER_FLAG_ON_LINK_ON  (3)
#define ETHER_FLAG_ON_LINK_OFF (2)

/* Channel definition of Ethernet */
#define ETHER_CHANNEL_0         (0)
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
/* 
 * The flag which control the pause frame.
 *
 * The value of flag and the situation which is indicatived of by the value.
 * ETHER_FLAG_OFF (0): Don't use the pause frame (default). 
 * ETHER_FLAG_ON  (1): Use the pause frame. 
 */
extern volatile uint8_t g_ether_PauseFrameEnableFlag;

/*
 * The flag which indicatived of the situation that the interrupt of Link Up/Down occur.
 *
 * The value of flag and the situation which is indicatived of by the value.
 * ETHER_FLAG_OFF (0) : Don't generate a Link up/down interrupt. 
 * ETHER_FLAG_ON_LINK_OFF (2) : Generated a Link down interrupt. 
 * ETHER_FLAG_ON_LINK_ON  (3) :  Generated a Link up interrupt. 
 *
 * The flag has gone of ETHER_FLAG_OFF(0) when the function of R_ETHER_LinkProcess is called and
 * the interrupt process of Link Up/Down is carried out.
 */
extern volatile uint8_t g_ether_LchngFlag;

/*
 * The flag indicatives of the situation that the communication is possible.
 * 
 * The value of flag and the situation which is indicatived of by the value.
 * ETHER_FLAG_OFF (0): Impossible to communicate.
 * ETHER_FLAG_ON  (1): Possible to communicate. 
 */
extern volatile uint8_t g_ether_TransferEnableFlag;

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
int32_t R_ETHER_Open_ZC2(uint32_t ch, const uint8_t mac_addr[]);
int32_t R_ETHER_Close_ZC2(uint32_t ch);
int32_t R_ETHER_Read_ZC2(uint32_t ch, void **buf);
int32_t R_ETHER_Read_ZC2_BufRelease(uint32_t ch);
int32_t R_ETHER_Write_ZC2_GetBuf(uint32_t ch, void **buf, uint16_t *buf_size);
int32_t R_ETHER_Write_ZC2_SetBuf(uint32_t ch, const uint32_t len);
int32_t R_Ether_CheckLink_ZC(uint32_t ch);
#if defined(__GNUC__) || defined(GRSAKURA)
#if defined(__cplusplus)
extern "C" {
#endif
void    R_ETHER_LinkProcess(void);
#if defined(__cplusplus)
}
#endif
void    R_ETHER_LinkProcess(void);
#endif
int32_t R_ETHER_WakeOnLAN(uint32_t ch);
void    R_ETHER_Callback_WakeOnLAN(void);
void    R_ETHER_Callback_Link_On(void);
void    R_ETHER_Callback_Link_Off(void);

#endif /* R_ETHER_H */
