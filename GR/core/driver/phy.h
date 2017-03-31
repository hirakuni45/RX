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
* File Name    : phy.h
* Version      : 3.00
* Description  : Ethernet PHY device driver
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.02.2010 1.00     First Release
*         : 17.03.2010 1.01     Modification of macro definitions for access timing
*         : 06.04.2010 1.02     RX62N changes 
*         : 08.07.2011 2.00     Second release 
*         : 21.08.2012 3.00     Third release
***********************************************************************************************************************/

#ifndef PHY_H
#define PHY_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdint.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* PHY return definitions */
#define R_PHY_OK        (0)
#define R_PHY_ERROR     (-1)

#if 0
#define MICREL_KSZ8041NL  /* Please define the macro when you use KSZ8041NL of the Micrel, Inc. */
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
enum LinkStatE
{
    PHY_NO_LINK = 0,
    PHY_LINK_10H,
    PHY_LINK_10F,
    PHY_LINK_100H,
    PHY_LINK_100F,
};

typedef enum LinkStatE linkstat_e;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
int16_t Phy_Init(void);
void    Phy_Start_Autonegotiate(void);
int16_t Phy_Set_Autonegotiate(uint16_t *line_speed_duplex, uint16_t *local_pause, uint16_t *partner_pause);
int16_t Phy_GetLinkStatus(void);

#endif /* PHY_H */

