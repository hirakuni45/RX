//=====================================================================//
/*!	@file
	@brief	PHY 制御 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdio.h>
#include "../T4_src/t4define.h"
#include "rx64m/iodefine.h"
#include "phy.h"
#include "r_ether.h"

/// PHY:DP83822 device is active
// #define TI_DP83822

#define PHY_DEBUG

/* Media Independent Interface */
#define PHY_MII_ST                      (1)
#define PHY_MII_READ                    (2)
#define PHY_MII_WRITE                   (1)

/*
 * PHY address selection.
 * Please select one of them.
 */
#ifdef TI_DP83822
#define PHY_MII_ADDR                    (1)  /* DP83822 default */
#else
#define PHY_MII_ADDR                    (0)  /* LAN8720A default */
#endif

#define PHY_MII_WAIT                    (2)

/* Standard PHY Registers */
#define PHY_REG_CONTROL                 (0)
#define PHY_REG_STATUS                  (1)
#define PHY_REG_IDENTIFIER1             (2)
#define PHY_REG_IDENTIFIER2             (3)
#define PHY_REG_AN_ADVERTISEMENT        (4)
#define PHY_REG_AN_LINK_PARTNER         (5)
#define PHY_REG_AN_EXPANSION            (6)

#ifdef TI_DP83822
#define PHY_REG_DP83822_REGCR     (0x0D)
#define PHY_REG_DP83822_ADDAR     (0x0E)
#define PHY_REG_DP83822_RCSR      (0x17)
#endif

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

/*==============================================================================*/
//  DP83822 Boot Strap:															//
//..............................................................................//
//    COL   (#29):  FX_EN:    0, PHY_AD0:   1									//
//    RX_D0 (#30):  AN_1:     1, PHY_AD1:   0									//
//    RX_D1 (#31):  EEE_EN:   0, PHY_AD2:   0									//
//    RX_D2 (#32):  FLD_EN:   0, PHY_AD3:   0									//
//    RX_D3 (# 1):  AN_EN:    1, PHY_AD4:   0									//
//    LED_0 (#17):  AN_0:     1													//
//    CRS   (#27):  LED_CFG:  1, LED_SPEED: 0									//
//    RX_ER (#28):  AMDIX_EN: 1, RGMII_EN:  0									//
//    RX_DV (#26):  XI_50:    0, RMII_EN:   0									//
//..............................................................................//
//  Force Modes:																//
//    FX_EN: 0, AN_EN: 0, AN_1: 0, AN_0: 0 --->  10BASE-Te, Half-Duplex			//
//    FX_EN: 0, AN_EN: 0, AN_1: 0, AN_0: 1 --->  10BASE-Te, Full-Duplex			//
//    FX_EN: 0, AN_EN: 0, AN_1: 1, AN_0: 0 ---> 100BASE-TX, Half-Duplex			//
//    FX_EN: 0, AN_EN: 0, AN_1: 1, AN_0: 1 ---> 100BASE-TX, Full-Duplex			//
//  Advertised Modes:															//
//    FX_EN: 0, AN_EN: 1, AN_1: 0, AN_0: 0 --->  10BASE-Te, Half-Duplex			//
//    FX_EN: 0, AN_EN: 1, AN_1: 0, AN_0: 1 --->  10BASE-Te, Half/Full-Duplex	//
//    FX_EN: 0, AN_EN: 1, AN_1: 1, AN_0: 0 --->  10BASE-Te, Half-Duplex			//
//                                              100BASE-TX, Half-Duplex			//
//   *FX_EN: 0, AN_EN: 1, AN_1: 1, AN_0: 1 --->  10BASE-Te, Half/Full-Duplex	//
//                                              100BASE-TX, Half/Full-Duplex	//
//  Fiber Modes:																//
//    FX_EN: 1, AN_EN: X, AN_1: X, AN_0: 0 ---> 100BASE-FX, Half-Duplex			//
//    FX_EN: 1, AN_EN: X, AN_1: X, AN_0: 1 ---> 100BASE-FX, Full-Duplex			//
/*==============================================================================*/


static void phy_mii_write1_(void)
{
    /*
     * The processing of one bit about frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
     * The data that 1 is output. 
     */
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000006;
    }
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000007;
    }
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000007;
    }
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000006;
    }
}


static void phy_mii_write0_(void)
{
    /*
     * The processing of one bit about frame format of MII Management Interface which is 
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
     * The data that 0 is output. 
     */
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000002;
    }
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000003;
    }
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000003;
    }
    for(int j = PHY_MII_WAIT; j > 0; j--)
    {
        ETHERC0.PIR.LONG = 0x00000002;
    }
}


static void phy_trans_1_to_0_(void)
{
    /*
     * The processing of TA (turnaround) about writing of the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    phy_mii_write1_();
    phy_mii_write0_();
}


static void phy_trans_z_to_0_(void)
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
}


static void phy_reg_set_(uint16_t reg_addr, int32_t option)
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
            phy_mii_write0_();
        }
        else
        {
            phy_mii_write1_();
        }
        data <<= 1;
        i--;
    }
}


static void phy_reg_read_(uint16_t *data)
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
}


static void phy_reg_write_(uint16_t data)
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
            phy_mii_write0_();
        }
        else
        {
            phy_mii_write1_();
        }
        i--;
        data <<= 1;
    }
}


static void phy_preamble_(void)
{
	/*
	 * The processing of PRE (preamble) about the frame format of MII Management Interface which is 
	 * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
	 */
	int i = 32;
	while(i > 0) {
		phy_mii_write1_();
		i--;
	}
}

static uint16_t phy_read_sub_(uint16_t reg_addr)
{
    /*
     * The value is read from the PHY register by the frame format of MII Management Interface provided 
     * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
     */
    phy_preamble_();
    phy_reg_set_(reg_addr, PHY_MII_READ);
    phy_trans_z_to_0_();
    uint16_t data;
    phy_reg_read_(&data);
    phy_trans_z_to_0_();

    return data;
}


static void phy_write_sub_(uint16_t reg_addr, uint16_t data)
{
    /*
     * The value is read from the PHY register by the frame format of MII Management Interface provided
     * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
     */
    phy_preamble_();
    phy_reg_set_(reg_addr, PHY_MII_WRITE);
    phy_trans_1_to_0_();
    phy_reg_write_(data);
    phy_trans_z_to_0_();
}


static uint16_t phy_read_(uint16_t reg_addr)
{
	if(reg_addr > 0x1f) {
#ifdef TI_DP83822
		phy_write_sub_(PHY_REG_DP83822_REGCR, 0x001F);  // address command
		phy_write_sub_(PHY_REG_DP83822_ADDAR, reg_addr);
		phy_write_sub_(PHY_REG_DP83822_REGCR, 0x401F);  // read/write command
		return phy_read_sub_(PHY_REG_DP83822_ADDAR);
#else
		printf("PHY Address Range Error: %04X\n", reg_addr);
		return 0;
#endif
	} else {
		return phy_read_sub_(reg_addr);
	}
}


static void phy_write_(uint16_t reg_addr, uint16_t data)
{
	if(reg_addr > 0x1f) {
#ifdef TI_DP83822
		phy_write_sub_(PHY_REG_DP83822_REGCR, 0x001F);  // address command
		phy_write_sub_(PHY_REG_DP83822_ADDAR, reg_addr);
		phy_write_sub_(PHY_REG_DP83822_REGCR, 0x401F);  // read/write command
		phy_write_sub_(PHY_REG_DP83822_ADDAR, data);
#else
		printf("PHY Address Range Error: %04X\n", reg_addr);
		return 0;
#endif
	} else {
		return phy_write_sub_(reg_addr, data);
	}
}

extern volatile uint8_t g_ether_PauseFrameEnableFlag;

static uint16_t local_advertise; /* the capabilities of the local link as PHY data */

//-----------------------------------------------------------------//
/*!
	@brief  PHY 初期化
	@return R_PHY_ERROR, R_PHY_OK
*/
//-----------------------------------------------------------------//
int16_t phy_init(void)
{
	uint16_t reg;

#ifdef PHY_DEBUG
	printf("Start PHY Init: ADR: %d\n", (int)PHY_MII_ADDR);
    reg = phy_read_(PHY_REG_IDENTIFIER1);
    reg = phy_read_(PHY_REG_IDENTIFIER1);
	printf("PHY Identifier1: 0x%04X\n", (int)reg);
    reg = phy_read_(PHY_REG_IDENTIFIER2);
    reg = phy_read_(PHY_REG_IDENTIFIER2);
	printf("PHY Identifier2: 0x%04X\n", (int)reg);
#endif

	/* Reset PHY */
	phy_write_(PHY_REG_CONTROL, PHY_CONTROL_RESET);

    uint32_t count = 0;
    /* Reset completion waiting */
    do
    {
        reg = phy_read_(PHY_REG_CONTROL);
        count++;
    } while ( (reg & PHY_CONTROL_RESET) && (count < PHY_DELAY_RESET) );
#ifdef PHY_DEBUG
	printf("PHY Init: reset loop: %d/%d\n", (int)count, (int)PHY_DELAY_RESET);
#endif

    if( count < PHY_DELAY_RESET )
    {
        /* 
         * When KSZ8041NL of the Micrel, Inc. is used, 
         * the pin that outputs the state of LINK is used combinedly with ACTIVITY in default. 
         * The setting of the pin is changed so that only the state of LINK is output. 
         */
#ifdef MICREL_KSZ8041NL
        reg = phy_read_(PHY_REG_PHY_CONTROL_1);
        reg &= ~0x8000;
        reg |= 0x4000;
        phy_write_(PHY_REG_PHY_CONTROL_1, reg);
#endif /* MICREL_KSZ8041NL */

#ifdef TI_DP83822
#ifdef PHY_DEBUG
    reg = phy_read_(0x0467);
	printf("DP83822 Boot Strap Latch #1(SOR1): 0x%04X\n", (int)reg);
    reg = phy_read_(0x0468);
	printf("DP83822 Boot Strap Latch #2(SOR2): 0x%04X\n", (int)reg);
#endif
///	phy_write_(0x0000, 0b0011000100000000);
///	phy_write_(0x0004, 0b0000000111100001);
//	reg = read_ext_(0x000A);
//	printf("DP83822 0x000A: 0x%04X\n", (int)reg);

	phy_write_(0x0018, 0b0000010001000000);
	phy_write_(0x0019, 0b0000000000100001);
///	phy_write_(0x0462, 0b0100001100000000);
	phy_write_(0x0462, 0b0100001100000000);

	phy_write_(PHY_REG_DP83822_RCSR, 0b0000000001100001);

#endif
#ifdef PHY_DEBUG
		printf("PHY Init OK...\n");
#endif
        return R_PHY_OK;
    }

#ifdef PHY_DEBUG
	printf("PHY Init NG...\n");
#endif

    return R_PHY_ERROR;
}


//-----------------------------------------------------------------//
/*!
	@brief  PHY 自動速度調整
*/
//-----------------------------------------------------------------//
void phy_start_autonegotiate(void)
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
    phy_write_(PHY_REG_AN_ADVERTISEMENT, local_advertise);
    phy_write_(PHY_REG_CONTROL, (PHY_CONTROL_AN_ENABLE |
                                 PHY_CONTROL_AN_RESTART) );

}


//-----------------------------------------------------------------//
/*!
	@brief  PHY 自動速度調整結果取得
	@param[out]	line_speed_duplex	both the line speed and the duplex
	@param[out]	local_pause			store the local pause bits
	@param[out]	partner_pause		store the partner pause bits
	@return		R_PHY_ERROR, R_PHY_OK
*/
//-----------------------------------------------------------------//
int16_t phy_get_autonegotiate(uint16_t *line_speed_duplex, uint16_t *local_pause, uint16_t *partner_pause)
{
    uint16_t reg;
    
    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    reg = phy_read_(PHY_REG_STATUS);
    reg = phy_read_(PHY_REG_STATUS);
    /* When the link isn't up, return error */
    if (!(reg & PHY_STATUS_LINK_UP))
    {
        asm("nop");
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
        reg = (int16_t)phy_read_(PHY_REG_AN_LINK_PARTNER);

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
}


//-----------------------------------------------------------------//
/*!
	@brief  PHY リンクステータス取得
	@return -1 if links is down, 0 otherwise 
*/
//-----------------------------------------------------------------//
int16_t phy_get_link_status(void)
{
    uint16_t reg;

    
    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    reg = phy_read_(PHY_REG_STATUS);
    reg = phy_read_(PHY_REG_STATUS);

    /* When the link isn't up, return error */
    if (!(reg & PHY_STATUS_LINK_UP))
    {
        asm("nop");
        /* Link is down */
        return R_PHY_ERROR;
    }
    else
    {
        /* Link is up */
        return R_PHY_OK;
    }
}
