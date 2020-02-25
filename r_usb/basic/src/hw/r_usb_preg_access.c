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
 * Copyright (C) 2015(2019) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_preg_access.c
 * Description  : USB IP Peripheral control register access code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 31.05.2019 1.26 Added support for GNUC and ICCRX.
 *         : 30.07.2019 1.27 RX72M is added.
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_reg_access.h"
#include "r_usb_bitdefine.h"
#include "r_usb_extern.h"


#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/******************************************************************************
 Function Name   : hw_usb_pset_dprpu
 Description     : Set DPRPU-bit SYSCFG0 register.
                 : (Enable D+Line pullup when PeripheralController function is selected)
 Arguments       : usb_utr_t *ptr  : USB internal structure. Selects USB channel.
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_dprpu(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.SYSCFG.WORD |= USB_DPRPU;
#else
    USB_M1.SYSCFG.WORD |= USB_DPRPU;
#endif
}
/******************************************************************************
 End of function hw_usb_pset_dprpu
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pclear_dprpu
 Description     : Clear DPRPU-bit of the SYSCFG0 register.
                 : (Disable D+Line pullup when PeripheralController function is
                 : selected.)
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_dprpu(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.SYSCFG.WORD &= (~USB_DPRPU);
#else
    USB_M1.SYSCFG.WORD &= (~USB_DPRPU);
#endif
}
/******************************************************************************
 End of function hw_usb_pclear_dprpu
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pset_wkup
 Description     : Set WKUP-bit DVSTCTR register.
                 : (Output Remote wakeup signal when PeripheralController function is selected)
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_wkup(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.DVSTCTR0.WORD |= USB_WKUP;
#else
    USB_M1.DVSTCTR0.WORD |= USB_WKUP;
#endif
}
/******************************************************************************
 End of function hw_usb_pset_wkup
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pset_enb_rsme
 Description     : Enable interrupt from RESUME
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_enb_rsme(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.INTENB0.WORD |= USB_RSME;
#else
    USB_M1.INTENB0.WORD |= USB_RSME;
#endif
}
/******************************************************************************
 End of function hw_usb_pset_enb_rsme
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pclear_enb_rsme
 Description     : Disable interrupt from RESUME
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_enb_rsme(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.INTENB0.WORD &= (~USB_RSME);
#else
    USB_M1.INTENB0.WORD &= (~USB_RSME);
#endif
}
/******************************************************************************
 End of function hw_usb_pclear_enb_rsme
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pclear_sts_resm
 Description     : Clear interrupt status of RESUME.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_sts_resm(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.INTSTS0.WORD = (uint16_t)~USB_RESM;
#else
    USB_M1.INTSTS0.WORD = (uint16_t)~USB_RESM;
#endif
}
/******************************************************************************
 End of function hw_usb_pclear_sts_resm
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pclear_sts_valid
 Description     : Clear the Setup Packet Reception interrupt flag.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_sts_valid(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.INTSTS0.WORD = (uint16_t)~USB_VALID;
#else
    USB_M1.INTSTS0.WORD = (uint16_t)~USB_VALID;
#endif
}
/******************************************************************************
 End of function hw_usb_pclear_sts_valid
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pset_ccpl
 Description     : Enable termination of control transfer status stage.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_ccpl(void)
{
#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.DCPCTR.WORD |= USB_CCPL;
#else
    USB_M1.DCPCTR.WORD |= USB_CCPL;
#endif
}
/******************************************************************************
 End of function hw_usb_pset_ccpl
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pmodule_init
 Description     : 
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pmodule_init( void )
{

#if USB_CFG_USE_USBIP == USB_CFG_IP0
    USB_M0.SYSCFG.WORD |= USB_SCKE;
    /* WAIT_LOOP */
    while (USB_SCKE != (USB_M0.SYSCFG.WORD & USB_SCKE))
    {
        /* Wait for Set of SCKE */
    }

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    USB_M0.PHYSLEW.LONG = 0x5;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

    USB_M0.SYSCFG.WORD &= (~USB_DRPD);

    USB_M0.SYSCFG.WORD |= USB_USBE;
    USB_M0.CFIFOSEL.WORD  = USB0_CFIFO_MBW;
    USB_M0.D0FIFOSEL.WORD = USB0_D0FIFO_MBW;
    USB_M0.D1FIFOSEL.WORD = USB0_D1FIFO_MBW;
#if USB_CFG_ENDIAN == USB_CFG_BIG
    USB_M0.CFIFOSEL.WORD  |= USB_BIGEND;
    USB_M0.D0FIFOSEL.WORD |= USB_BIGEND;
    USB_M0.D1FIFOSEL.WORD |= USB_BIGEND;
#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */
    USB_M0.INTENB0.WORD = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
#if USB_CFG_CLKSEL == USB_CFG_20MHZ
    USB_M1.PHYSET.WORD &= ~USB_CLKSEL;
    USB_M1.PHYSET.WORD |= USB_CLKSEL_20;

#endif  /* USB_CFG_CLKSEL == USB_CFG_20MHZ */

#if USB_CFG_CLKSEL == USB_CFG_OTHER
    USB_M1.PHYSET.WORD |= USB_HSEB;

#endif  /* USB_CFG_OTHER == USB_CFG_OTHER */

    usb_cpu_delay_1us((uint16_t) 1);                    /* wait 1usec */

    USB_M1.PHYSET.WORD &= (~USB_DIRPD);
    usb_cpu_delay_xms(1); /* wait 1msec */

#if ((USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))
    USB_M1.PHYSET.WORD &= (~USB_PLLRESET);

#endif  /* (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */
    USB_M1.SYSCFG.WORD &= (~USB_DRPD);

    USB_M1.SYSCFG.WORD |= USB_USBE;

    USB_M1.LPSTS.WORD |= USB_SUSPENDM;

#if ((USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))
    /* WAIT_LOOP */
    while (USB_PLLLOCK != (USB_M1.PLLSTA.WORD & USB_PLLLOCK ))
    {
        /* Wait for PLL Lock */
    }

#endif  /* (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */

    USB_M1.BUSWAIT.WORD = (USB_CFG_BUSWAIT | 0x0F00);

    USB_M1.PHYSET.WORD |= USB_REPSEL_16;

    USB_M1.CFIFOSEL.WORD  = USB1_CFIFO_MBW;
    USB_M1.D0FIFOSEL.WORD = USB1_D0FIFO_MBW;
    USB_M1.D1FIFOSEL.WORD = USB1_D1FIFO_MBW;

#if USB_CFG_ENDIAN == USB_CFG_BIG
    USB_M1.CFIFOSEL.WORD  |= USB_BIGEND;
    USB_M1.D0FIFOSEL.WORD |= USB_BIGEND;
    USB_M1.D1FIFOSEL.WORD |= USB_BIGEND;

#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */

    USB_M1.INTENB0.WORD = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
    USB_M1.SYSCFG.WORD |= USB_SCKE;
    /* WAIT_LOOP */
    while (USB_SCKE != (USB_M1.SYSCFG.WORD & USB_SCKE))
    {
        /* Wait for Set of SCKE */
    }
    USB_M1.SYSCFG.WORD &= (~USB_DRPD);

    USB_M1.SYSCFG.WORD |= USB_USBE;

    USB_M1.CFIFOSEL.WORD  = USB1_CFIFO_MBW;
    USB_M1.D0FIFOSEL.WORD = USB1_D0FIFO_MBW;
    USB_M1.D1FIFOSEL.WORD = USB1_D1FIFO_MBW;
#if USB_CFG_ENDIAN == USB_CFG_BIG
    USB_M1.CFIFOSEL.WORD  |= USB_BIGEND;
    USB_M1.D0FIFOSEL.WORD |= USB_BIGEND;
    USB_M1.D1FIFOSEL.WORD |= USB_BIGEND;
#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */

    USB_M1.INTENB0.WORD = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);
/*    hw_usb_set_mbw(USB_NULL, USB_CUSE, USB1_CFIFO_MBW); */

#endif  /* defined(BSP_MCU_RX63N) */
#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
}
/******************************************************************************
 End of function hw_usb_pmodule_init
 ******************************************************************************/

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 End of file
 ******************************************************************************/

