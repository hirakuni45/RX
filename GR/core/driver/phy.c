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
* File Name    : phy.c
* Version      : 3.00
* Description  : Ethernet PHY device driver
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.02.2010 1.00     First Release
*         : 06.04.2010 1.01     RX62N changes 
*         : 08.07.2011 2.00     Second release 
*         : 21.08.2012 3.00     Third release
***********************************************************************************************************************/


/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#include "../T4_src/t4define.h"
/// #include <arduino.h>
#else
#include <machine.h>
#endif
#include "rx64m/iodefine.h"
#include "phy.h"
#include "r_ether.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Media Independent Interface */
#define PHY_MII_ST                      (1)
#define PHY_MII_READ                    (2)
#define PHY_MII_WRITE                   (1)

/*
 * PHY address selection.
 * Please select one of them.
 */
#define PHY_MII_ADDR                    (0)  /* for GR-SAKURA (RX63N). */

#define PHY_MII_WAIT                    (2)

/* Standard PHY Registers */
#define PHY_REG_CONTROL                 (0)
#define PHY_REG_STATUS                  (1)
#define PHY_REG_IDENTIFIER1             (2)
#define PHY_REG_IDENTIFIER2             (3)
#define PHY_REG_AN_ADVERTISEMENT        (4)
#define PHY_REG_AN_LINK_PARTNER         (5)
#define PHY_REG_AN_EXPANSION            (6)

/* Vendor Specific PHY Registers */
#ifdef MICREL_KSZ8041NL
#define PHY_REG_PHY_CONTROL_1           (0x1E)
#endif /* MICREL_KSZ8041NL */

/* Basic Mode Control Register Bit Definitions */
#define PHY_CONTROL_RESET               (1 << 15)
#define PHY_CONTROL_LOOPBACK            (1 << 14)
#define PHY_CONTROL_100_MBPS            (1 << 13)
#define PHY_CONTROL_AN_ENABLE           (1 << 12)
#define PHY_CONTROL_POWER_DOWN          (1 << 11)
#define PHY_CONTROL_ISOLATE             (1 << 10)
#define PHY_CONTROL_AN_RESTART          (1 << 9)
#define PHY_CONTROL_FULL_DUPLEX         (1 << 8)
#define PHY_CONTROL_COLLISION           (1 << 7)

/* Basic Mode Status Register Bit Definitions */
#define PHY_STATUS_100_T4               (1 << 15)
#define PHY_STATUS_100F                 (1 << 14)
#define PHY_STATUS_100H                 (1 << 13)
#define PHY_STATUS_10F                  (1 << 12)
#define PHY_STATUS_10H                  (1 << 11)
#define PHY_STATUS_AN_COMPLETE          (1 << 5)
#define PHY_STATUS_RM_FAULT             (1 << 4)
#define PHY_STATUS_AN_ABILITY           (1 << 3)
#define PHY_STATUS_LINK_UP              (1 << 2)
#define PHY_STATUS_JABBER               (1 << 1)
#define PHY_STATUS_EX_CAPABILITY        (1 << 0)

/* Auto Negotiation Advertisement Bit Definitions */
#define PHY_AN_ADVERTISEMENT_NEXT_PAGE  (1 << 15)  
#define PHY_AN_ADVERTISEMENT_RM_FAULT   (1 << 13)
#define PHY_AN_ADVERTISEMENT_ASM_DIR    (1 << 11)
#define PHY_AN_ADVERTISEMENT_PAUSE      (1 << 10)
#define PHY_AN_ADVERTISEMENT_100_T4     (1 << 9)
#define PHY_AN_ADVERTISEMENT_100F       (1 << 8)
#define PHY_AN_ADVERTISEMENT_100H       (1 << 7)
#define PHY_AN_ADVERTISEMENT_10F        (1 << 6)
#define PHY_AN_ADVERTISEMENT_10H        (1 << 5)
#define PHY_AN_ADVERTISEMENT_SELECTOR   (1 << 0)

/* Auto Negostiate Link Partner Ability Bit Definitions */
#define PHY_AN_LINK_PARTNER_NEXT_PAGE   (1 << 15)
#define PHY_AN_LINK_PARTNER_ACK         (1 << 14)
#define PHY_AN_LINK_PARTNER_RM_FAULT    (1 << 13)
#define PHY_AN_LINK_PARTNER_ASM_DIR     (1 << 11)
#define PHY_AN_LINK_PARTNER_PAUSE       (1 << 10) 
#define PHY_AN_LINK_PARTNER_100_T4      (1 << 9) 
#define PHY_AN_LINK_PARTNER_100F        (1 << 8)
#define PHY_AN_LINK_PARTNER_100H        (1 << 7)
#define PHY_AN_LINK_PARTNER_10F         (1 << 6)
#define PHY_AN_LINK_PARTNER_10H         (1 << 5)
#define PHY_AN_LINK_PARTNER_SELECTOR    (1 << 0)

/* Delay constants */
#define PHY_DELAY_RESET                 0x00020000L 
#define PHY_DELAY_AN                    0x00800000L 

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/
extern volatile uint8_t g_ether_PauseFrameEnableFlag;

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static uint16_t _Phy_Read(uint16_t reg_addr);
static void     _Phy_Write(uint16_t reg_addr, uint16_t data);
static void     _Phy_Preamble(void);
static void     _Phy_RegSet(uint16_t reg_addr, int32_t option);
static void     _Phy_RegRead(uint16_t *data);
static void     _Phy_RegWrite(uint16_t data);
static void     _Phy_TransZto0(void);
static void     _Phy_Trans1to0(void);
static void     _Phy_MiiWrite1(void);
static void     _Phy_MiiWrite0(void);

static uint16_t local_advertise; /* the capabilities of the local link as PHY data */



/**
 * Public functions
 */

/***********************************************************************************************************************
* Function Name: Phy_Init
* Description  : Resets Ethernet PHY device
* Arguments    : none
* Return Value : R_PHY_ERROR
*                R_PHY_OK
***********************************************************************************************************************/
int16_t  Phy_Init(void)
{
    uint16_t reg;
    uint32_t count;

    /* Reset PHY */
    _Phy_Write(PHY_REG_CONTROL, PHY_CONTROL_RESET);

    count = 0;
    /* Reset completion waiting */
    do
    {
        reg = _Phy_Read(PHY_REG_CONTROL);
        count++;
    } while ( (reg & PHY_CONTROL_RESET) && (count < PHY_DELAY_RESET) );

    if( count < PHY_DELAY_RESET )
    {     
        /* 
         * When KSZ8041NL of the Micrel, Inc. is used, 
         * the pin that outputs the state of LINK is used combinedly with ACTIVITY in default. 
         * The setting of the pin is changed so that only the state of LINK is output. 
         */
#ifdef MICREL_KSZ8041NL
        reg = _Phy_Read(PHY_REG_PHY_CONTROL_1);
        reg &= ~0x8000;
        reg |= 0x4000;
        _Phy_Write(PHY_REG_PHY_CONTROL_1, reg);
#endif /* MICREL_KSZ8041NL */
        
        return R_PHY_OK;
    }

    return R_PHY_ERROR;
} /* End of function Phy_Init() */


/***********************************************************************************************************************
* Function Name: Phy_Start_Autonegotiate
* Description  : Starts autonegotiate
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void Phy_Start_Autonegotiate(void)
{
    /* Set local ability */
    /* When pause frame is not used */
    if (ETHER_FLAG_OFF == g_ether_PauseFrameEnableFlag)
    {
        local_advertise = (PHY_AN_ADVERTISEMENT_100F    |
                           PHY_AN_ADVERTISEMENT_100H    |
                           PHY_AN_ADVERTISEMENT_10F     |
                           PHY_AN_ADVERTISEMENT_10H     |
                           PHY_AN_ADVERTISEMENT_SELECTOR);
    }
    /* When pause frame is used */
    else
    {
        local_advertise = (PHY_AN_ADVERTISEMENT_ASM_DIR |
                           PHY_AN_ADVERTISEMENT_PAUSE   |
                           PHY_AN_ADVERTISEMENT_100F    |
                           PHY_AN_ADVERTISEMENT_100H    |
                           PHY_AN_ADVERTISEMENT_10F     |
                           PHY_AN_ADVERTISEMENT_10H     |
                           PHY_AN_ADVERTISEMENT_SELECTOR);
    }
    
    /* Configure what the PHY and the Ethernet controller on this board supports */
    _Phy_Write(PHY_REG_AN_ADVERTISEMENT, local_advertise);
    _Phy_Write(PHY_REG_CONTROL, (PHY_CONTROL_AN_ENABLE |
                                 PHY_CONTROL_AN_RESTART) );

} /* End of function Phy_Start_Autonegotiate() */

/***********************************************************************************************************************
* Function Name: Phy_Set_Autonegotiate
* Description  : reports the other side's physical capability
* Arguments    : *line_speed_duplex - 
*                    a pointer to the location of both the line speed and the duplex
*                *local_pause - 
*                    a pointer to the location to store the local pause bits.
*                *partner_pause - 
*                    a pointer to the location to store the partner pause bits.
* Return Value : R_PHY_ERROR
*                R_PHY_OK
* Note         : The value returned to local_pause and patner_pause is used 
*                as it is as an argument of _ R_Ether_PauseResolution function. 
***********************************************************************************************************************/
int16_t Phy_Set_Autonegotiate(uint16_t *line_speed_duplex, uint16_t *local_pause, uint16_t *partner_pause)
{
    uint16_t reg;
    
    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    reg = _Phy_Read(PHY_REG_STATUS);
    reg = _Phy_Read(PHY_REG_STATUS);
    /* When the link isn't up, return error */
    if (!(reg & PHY_STATUS_LINK_UP))
    {
#if defined(__GNUC__) || defined(GRSAKURA)
        asm("nop");
#else
        nop();
#endif
        return R_PHY_ERROR;
    }

    /* Establish local pause capability */    
    if (local_advertise & PHY_AN_ADVERTISEMENT_PAUSE)
    {
        *local_pause |= (1 << 1);
    }
    
    if (local_advertise & PHY_AN_ADVERTISEMENT_ASM_DIR)
    {
        *local_pause |= 1;
    }
    
    
    /* When the auto-negotiation isn't completed, return error */
    if (!(reg & PHY_STATUS_AN_COMPLETE))
    {
        return R_PHY_ERROR;
    }
    else
    {
        /* Get the link partner response */
        reg = (int16_t)_Phy_Read(PHY_REG_AN_LINK_PARTNER);

        /* Establish partner pause capability */
        if ( (reg & PHY_AN_LINK_PARTNER_PAUSE) == PHY_AN_LINK_PARTNER_PAUSE )
        {
            *partner_pause = ( 1 << 1 );
        }

        if ( (reg & PHY_AN_LINK_PARTNER_ASM_DIR) == PHY_AN_LINK_PARTNER_ASM_DIR )
        {
            *partner_pause |= 1;
        }

        /* Establish the line speed and the duplex */
        if ( reg & PHY_AN_LINK_PARTNER_10H )
        {
            *line_speed_duplex = PHY_LINK_10H;
        }

        if ( reg & PHY_AN_LINK_PARTNER_10F )
        {
            *line_speed_duplex = PHY_LINK_10F;
        }

        if ( reg & PHY_AN_LINK_PARTNER_100H )
        {
            *line_speed_duplex = PHY_LINK_100H;
        }

        if ( reg & PHY_AN_LINK_PARTNER_100F )
        {
            *line_speed_duplex = PHY_LINK_100F;
        }

        return R_PHY_OK;
    }
} /* End of function Phy_Set_Autonegotiate() */


/***********************************************************************************************************************
* Function Name: Phy_GetLinkStatus 
* Description  : Returns the status of the physical link 
* Arguments    : none 
* Return Value : -1 if links is down, 0 otherwise 
***********************************************************************************************************************/
int16_t Phy_GetLinkStatus(void)
{
    uint16_t reg;

    
    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    reg = _Phy_Read(PHY_REG_STATUS);
    reg = _Phy_Read(PHY_REG_STATUS);

    /* When the link isn't up, return error */
    if (!(reg & PHY_STATUS_LINK_UP))
    {
#if defined(__GNUC__) || defined(GRSAKURA)
        asm("nop");
#else
        nop();
#endif
        /* Link is down */
        return R_PHY_ERROR;
    }
    else
    {
        /* Link is up */
        return R_PHY_OK;
    }
} /* End of function Phy_GetLinkStatus() */


/**
 * Private functions
 */

/***********************************************************************************************************************
* Function Name: _Phy_Read
* Description  : Reads a PHY register
* Arguments    : reg_addr - address of the PHY register
* Return Value : read value
***********************************************************************************************************************/
static uint16_t _Phy_Read(uint16_t reg_addr)
{
    uint16_t data;

    /*
     * The value is read from the PHY register by the frame format of MII Management Interface provided 
     * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
     */
    _Phy_Preamble();
    _Phy_RegSet(reg_addr, PHY_MII_READ);
    _Phy_TransZto0();
    _Phy_RegRead(&data);
    _Phy_TransZto0();

    return(data);
} /* End of function _Phy_Read() */

/***********************************************************************************************************************
* Function Name: _Phy_Write
* Description  : Writes to a PHY register
* Arguments    : reg_addr - address of the PHY register
*                data - value
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_Write(uint16_t reg_addr, uint16_t data)
{
    /*
     * The value is read from the PHY register by the frame format of MII Management Interface provided
     * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
     */
    _Phy_Preamble();
    _Phy_RegSet(reg_addr, PHY_MII_WRITE);
    _Phy_Trans1to0();
    _Phy_RegWrite(data);
    _Phy_TransZto0();
} /* End of function _Phy_Write() */

/***********************************************************************************************************************
* Function Name: _Phy_Preamble
* Description  : As preliminary preparation for access to the PHY module register,
*                "1" is output via the MII management interface.                  
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_Preamble(void)
{
    int16_t i;

    /*
     * The processing of PRE (preamble) about the frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    i = 32;
    while( i > 0 )
    {
        _Phy_MiiWrite1();
        i--;
    }
} /* End of function _Phy_Preamble() */

/***********************************************************************************************************************
* Function Name: _Phy_RegSet
* Description  : Sets a PHY device to read or write mode
* Arguments    : reg_addr - address of the PHY register
*                option - mode
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_RegSet(uint16_t reg_addr, int32_t option)
{
    int32_t    i;
    uint16_t data;

    /*
     * The processing of ST (start of frame),OP (operation code), PHYAD (PHY Address), and 
     * REGAD (Register Address)  about the frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    data = 0;
    data = (PHY_MII_ST << 14);          /* ST code    */

    if( option == PHY_MII_READ )
    {
        data |= (PHY_MII_READ << 12);   /* OP code(RD)  */
    }
    else
    {
        data |= (PHY_MII_WRITE << 12);  /* OP code(WT)  */
    }

    data |= (PHY_MII_ADDR << 7);        /* PHY Address  */
    data |= (reg_addr << 2);            /* Reg Address  */

    i = 14;
    while( i > 0 )
    {
        if( (data & 0x8000) == 0 )
        {
            _Phy_MiiWrite0();
        }
        else
        {
            _Phy_MiiWrite1();
        }
        data <<= 1;
        i--;
    }
} /* End of function _Phy_RegSet() */

/***********************************************************************************************************************
* Function Name: _Phy_RegRead
* Description  : Reads PHY register through MII interface
* Arguments    : data - pointer to store the data read
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_RegRead(uint16_t *data)
{
    int32_t      i, j;
    uint16_t   reg_data;

    /*
     * The processing of DATA (data) about reading of the frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    reg_data = 0;
    i = 16;
    while( i > 0 )
    {
        for(j = PHY_MII_WAIT; j > 0; j--)
        {
            ETHERC0.PIR.LONG = 0x00000000;
        }
        for(j = PHY_MII_WAIT; j > 0; j--)
        {
            ETHERC0.PIR.LONG = 0x00000001;
        }

        reg_data <<= 1;
        reg_data |= (uint16_t)((ETHERC0.PIR.LONG & 0x00000008) >> 3);  /* MDI read  */

        for(j = PHY_MII_WAIT; j > 0; j--)
        {
            ETHERC0.PIR.LONG = 0x00000001;
        }
        for(j = PHY_MII_WAIT; j > 0; j--)
        {
            ETHERC0.PIR.LONG = 0x00000000;
        }
        i--;
    }
    *data = reg_data;
} /* End of function _Phy_RegRead() */

/***********************************************************************************************************************
* Function Name: _Phy_RegWrite
* Description  : Writes to PHY register through MII interface
* Arguments    : data - value to write
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_RegWrite(uint16_t data)
{
    int32_t  i;

    /*
     * The processing of DATA (data) about writing of the frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    i = 16;
    while( i > 0 )
    {
        if( (data & 0x8000) == 0 )
        {
            _Phy_MiiWrite0();
        }
        else
        {
            _Phy_MiiWrite1();
        }
        i--;
        data <<= 1;
    }
} /* End of function _Phy_RegWrite() */

/***********************************************************************************************************************
* Function Name: _Phy_TransZto0
* Description  : Performs bus release so that PHY can drive data
*              : for read operation 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_TransZto0(void)
{
    int32_t j;

    /*
     * The processing of TA (turnaround) about reading of the frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000000;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000001;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000001;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000000;
    }
} /* End of function _Phy_RegWrite() */

/***********************************************************************************************************************
* Function Name: _Phy_Trans1to0
* Description  : Switches data bus so MII interface can drive data
*              : for write operation 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void _Phy_Trans1to0(void)
{
    /*
     * The processing of TA (turnaround) about writing of the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    _Phy_MiiWrite1();
    _Phy_MiiWrite0();
} /* End of function _Phy_RegWrite() */

/***********************************************************************************************************************
* Function Name: _Phy_MiiWrite1
* Description  : Outputs 1 to the MII interface 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_MiiWrite1(void)
{
    int32_t j;

    /*
     * The processing of one bit about frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
     * The data that 1 is output. 
     */
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000006;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000007;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000007;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000006;
    }
} /* End of function _Phy_RegWrite() */

/***********************************************************************************************************************
* Function Name: _Phy_MiiWrite0
* Description  : Outputs 0 to the MII interface 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void  _Phy_MiiWrite0(void)
{
    int32_t j;

    /*
     * The processing of one bit about frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
     * The data that 0 is output. 
     */
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000002;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000003;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000003;
    }
    for(j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000002;
    }
} /* End of function _Phy_MiiWrite0() */
