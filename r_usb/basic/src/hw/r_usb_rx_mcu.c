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
 * Copyright (C) 2015(2017) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_rx_mcu.c
 * Description  : RX MCU processing
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 Support DMAC Technical Update for RX71M/RX64M USBA.
 *         : 30.09.2017 1.22 RX62N/RX630/RX63T-H is added.
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
#include "r_usb_dmac.h"
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
 Macro definitions
 ******************************************************************************/

#if defined(USB_CFG_HHID_USE) || defined(USB_CFG_PHID_USE)
  #if USB_CFG_DTC == USB_CFG_ENABLE
    #error  In HID class, can not set USB_CFG_ENABLE to USB_CFG_DTC in r_usb_basic_config.h.
  #endif /* USB_CFG_DTC == USB_CFG_ENABLE */

  #if USB_CFG_DMA == USB_CFG_ENABLE
    #error  In HID class, can not set USB_CFG_ENABLE to USB_CFG_DMA in r_usb_basic_config.h.
  #endif /* USB_CFG_DMA == USB_CFG_ENABLE */

#endif /* defined(USB_CFG_HHID_USE) || defined(USB_CFG_PHID_USE) */


#if USB_CFG_MODE == USB_CFG_PERI
  #if USB_CFG_USE_USBIP == USB_CFG_MULTI
    #error  Can not set USB_CFG_MULTI to USB_CFG_USE_USBIP when setting USB_CFG_PERI to USB_CFG_MODE \
         in r_usb_basic_config.h.

  #endif /* USB_CFG_USE_USBIP == USB_CFG_MULTI */
#endif /* USB_CFG_MODE == USB_CFG_PERI */


#if USB_CFG_COMPLIANCE == USB_CFG_DISABLE
  #if USB_CFG_ELECTRICAL == USB_CFG_ENABLE
    #error  Can not set USB_CFG_DISABLE to USB_CFG_COMPLIANCE when setting USB_CFG_ENABLE to USB_CFG_ELECTRICAL \
         in r_usb_basic_config.h.

  #endif /* USB_CFG_ELECTRICAL == USB_CFG_ENABLE */
#endif /* USB_CFG_COMPLIANCE == USB_CFG_DISABLE */


#if USB_CFG_BC == USB_CFG_DISABLE
  #if USB_CFG_DCP == USB_CFG_ENABLE
    #error  Can not set USB_CFG_DISABLE to USB_CFG_BC when setting USB_CFG_ENABLE to USB_CFG_DCP \
         in r_usb_basic_config.h.

  #endif /* USB_CFG_DCP == USB_CFG_ENABLE */
#endif /* USB_CFG_BC == USB_CFG_DISABLE */


#if USB_CFG_DMA == USB_CFG_ENABLE
  #if USB_CFG_DTC == USB_CFG_ENABLE
    #error  Can not set USB_CFG_ENABLE to the definitions (USB_CFG_DMA and USB_CFG_DTC) at the same time \
         in r_usb_basic_config.h.

  #endif /* USB_CFG_DTC == USB_CFG_ENABLE */
#endif /* USB_CFG_DMA == USB_CFG_ENABLE */


#if USB_CFG_MODE == USB_CFG_HOST
  #if defined(USB_CFG_PCDC_USE) || defined(USB_CFG_PHID_USE) || defined(USB_CFG_PMSC_USE) || defined(USB_CFG_PVNDR_USE)
    #error  Can not enable these definitions(USB_CFG_PCDC_USE/USB_CFG_PHID_USE/USB_CFG_PMSC_USE/USB_CFG_PVNDR_USE) \
        when setting USB_HOST to USB_CFG_MODE in r_usb_basic_config.h.

  #endif /* defined(USB_CFG_PCDC_USE || USB_CFG_PHID_USE || USB_CFG_PMSC_USE || USB_CFG_PVNDR_USE) */
#endif /* USB_CFG_MODE == USB_HOST */


#if USB_CFG_MODE == USB_CFG_PERI
  #if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HVNDR_USE)
    #error  Can not enable these definitions(USB_CFG_HCDC_USE/USB_CFG_HHID_USE/USB_CFG_HMSC_USE/USB_CFG_HVNDR_USE) \
        when setting USB_PERI to USB_CFG_MODE in r_usb_basic_config.h.

  #endif /* defined(USB_CFG_HCDC_USE || USB_CFG_HHID_USE || USB_CFG_HMSC_USE || USB_CFG_HVNDR_USE) */
#endif /* USB_CFG_MODE == USB_PERI */


#if defined(BSP_MCU_RX62N)
  #if USB_CFG_DMA == USB_CFG_ENABLE
    #error  Can not set USB_CFG_ENABLE to USB_CFG_DMA when using RX62N/RX621 MCU in r_usb_basic_config.h.

  #endif /* USB_CFG_DTC == USB_CFG_ENABLE */
#endif /* defined(BSP_MCU_RX62N) */


#if defined(BSP_MCU_RX630)
  #if USB_CFG_MODE == USB_CFG_HOST
    #error  Can not set USB_CFG_HOST to USB_CFG_MODE when using RX630 MCU in r_usb_basic_config.h.

  #endif /* USB_CFG_MODE == USB_CFG_HOST */

  #if USB_CFG_MODE == USB_CFG_HOST_PERI
    #error  Can not set USB_CFG_HOST_PERI to USB_CFG_MODE when using RX630 MCU in r_usb_basic_config.h.

  #endif /* USB_CFG_MODE == USB_CFG_HOST_PERI */

  #if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HVNDR_USE)
    #error  Can not enable these definitions(USB_CFG_HCDC_USE/USB_CFG_HHID_USE/USB_CFG_HMSC_USE/USB_CFG_HVNDR_USE) \
        when using RX630 MCU in r_usb_basic_config.h.

  #endif /* defined(USB_CFG_HCDC_USE || USB_CFG_HHID_USE || USB_CFG_HMSC_USE || USB_CFG_HVNDR_USE) */
#endif /* defined(BSP_MCU_RX630) */


#if defined(BSP_MCU_RX63T)
  #if (USB_CFG_USE_USBIP == USB_CFG_IP1) || (USB_CFG_USE_USBIP == USB_CFG_MULTI)
    #error  Can not set USB_CFG_IP1/USB_CFG_MULTI to USB_CFG_USE_USBIP when using RX63T MCU in r_usb_basic_config.h.

  #endif /* (USB_CFG_USE_USBIP == USB_CFG_IP1) || (USB_CFG_USE_USBIP == USB_CFG_MULTI) */
#endif /* defined(BSP_MCU_RX63T) */


#if !defined(BSP_MCU_RX71M)
  #if USB_CFG_ELECTRICAL == USB_CFG_ENABLE
    #error  Can not set USB_CFG_ENABLE to USB_CFG_ELECTRICAL when using MCU other than RX71M in r_usb_basic_config.h.
  #endif /* USB_CFG_ELECTRICAL == USB_CFG_ENABLE */

#endif /* !defined(BSP_MCU_RX71M) */


/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
extern uint16_t g_usb_usbmode;

#if 0
/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
#pragma interrupt usbfs_usbi_isr(vect = VECT(USB0, USBI0))

#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    #pragma interrupt usbhs_usbir_isr(vect = VECT(USBA, USBAR))

#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) || defined (BSP_MCU_RX630) || defined (BSP_MCU_RX63T)
        #pragma interrupt usb_cpu_usb_int_hand_isr(vect = VECT(USB, USBR0))
#endif /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) || defined (BSP_MCU_RX630) || defined (BSP_MCU_RX63T) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        #pragma interrupt usbhs_usbir_isr(vect = VECT(USB1, USBI1))
    #if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        #pragma interrupt usb2_cpu_usb_int_hand_isr(vect = VECT(USB, USBR1))
    #endif /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N)
    #if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        #pragma interrupt usb_cpu_usb_int_hand_isr(vect = VECT(USB0, USBR0))
    #endif /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
#endif /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N) */

#if USB_CFG_DTC == USB_CFG_ENABLE
#pragma interrupt usb_cpu_d0fifo_int_hand(vect = VECT(USB0, D0FIFO0))
#pragma interrupt usb_cpu_d1fifo_int_hand(vect = VECT(USB0, D1FIFO0))

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
#pragma interrupt usb2_cpu_d0fifo_int_hand(vect = VECT(USBA, D0FIFO2))
#pragma interrupt usb2_cpu_d1fifo_int_hand(vect = VECT(USBA, D1FIFO2))

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

#if defined(BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
#pragma interrupt usb2_cpu_d0fifo_int_hand(vect = VECT(USB1, D0FIFO1))
#pragma interrupt usb2_cpu_d1fifo_int_hand(vect = VECT(USB1, D1FIFO1))

#endif  /* defined(BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */



#endif



/******************************************************************************
 Renesas Abstracted RSK functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_module_start
 Description     : USB module start
 Arguments       : uint8_t ip_type  : USB_IP0/USB_IP1
 Return value    : none
 ******************************************************************************/
#if 0
usb_err_t usb_module_start (uint8_t ip_type)
{

    if (USB_IP0 == ip_type)
    {
        if (0 == MSTP(USB0))
        {
            return USB_ERR_BUSY;
        }

        /* Enable writing to MSTP registers */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

        /* Enable power for USB0 */
        MSTP(USB0) = 0;

        /* Disable writing to MSTP registers */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
    }
    else
    {
#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        if (0 == MSTP(USBA))
        {
            return USB_ERR_BUSY;
        }

        /* Enable writing to MSTP registers */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

        /* Enable power for USBA */
        MSTP(USBA) = 0;

        /* Disable writing to MSTP registers */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        if (0 == MSTP(USB1))
        {
            return USB_ERR_BUSY;
        }

        /* Enable writing to MSTP registers */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

        /* Enable power for USB1 */
        MSTP(USB1) = 0;

        /* Disable writing to MSTP registers */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

    }
    return USB_SUCCESS;
}
#endif
/******************************************************************************
End of function usb_module_start
******************************************************************************/

/******************************************************************************
 Function Name   : usb_module_stop
 Description     : USB module stop
 Arguments       : uint8_t ip_type  : USB_IP0/USB_IP1
 Return value    : none
 ******************************************************************************/
#if 0
usb_err_t usb_module_stop (uint8_t ip_type)
{
    if (USB_IP0 == ip_type)
    {
        if (0 != MSTP(USB0))
        {
            return USB_ERR_NOT_OPEN;
        }

        /* Enable writing to MSTP registers */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

        /* Disable power for USB0 */
        MSTP(USB0) = 1;

        /* Disable writing to MSTP registers */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
    }
    else if (USB_IP1 == ip_type)
    {
#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        if (0 != MSTP(USBA))
        {
            return USB_ERR_NOT_OPEN;
        }

        /* Enable writing to MSTP registers */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

        /* Disable power for USBA */
        MSTP(USBA) = 1;

        /* Disable writing to MSTP registers */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        if (0 != MSTP(USB1))
        {
            return USB_ERR_NOT_OPEN;
        }
        /* Enable writing to MSTP registers */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

        /* Disable power for USB1 */
        MSTP(USB1) = 1;

        /* Disable writing to MSTP registers */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */
    }
    else
    {
        return USB_ERR_PARA;
    }
    return USB_SUCCESS;
}
#endif
/******************************************************************************
End of function usb_module_stop
******************************************************************************/

/******************************************************************************
 Function Name   : usb_cpu_usbint_init
 Description     : USB interrupt Initialize
 Arguments       : uint8_t ip_type  : USB_IP0/USB_IP1
 Return value    : void
 ******************************************************************************/
#if 0
void usb_cpu_usbint_init (uint8_t ip_type)
{
    if ( USB_IP0 == ip_type)
    {
#ifndef BSP_MCU_RX63T
        /* Deep standby USB monitor register
         b0      SRPC0    USB0 single end control
         b3-b1   Reserved 0
         b4      FIXPHY0  USB0 transceiver output fix
         b7-b5   Reserved 0
         b8      SRPC1    USB1 single end control
         b11-b9  Reserved 0
         b12     FIXPHY1  USB1 transceiver output fix
         b15-b13 Reserved 0
         b16     DP0      USB0 DP input
         b17     DM0      USB0 DM input
         b19-b18 Reserved 0
         b20     DOVCA0   USB0 OVRCURA input
         b21     DOVCB0   USB0 OVRCURB input
         b22     Reserved 0
         b23     DVBSTS0  USB1 VBUS input
         b24     DP1      USB1 DP input
         b25     DM1      USB1 DM input
         b27-b26 Reserved 0
         b28     DOVCA1   USB1 OVRCURA input
         b29     DOVCB1   USB1 OVRCURB input
         b30     Reserved 0
         b31     DVBSTS1  USB1 VBUS input
         */
        USB.DPUSR0R.BIT.FIXPHY0 = 0u; /* USB0 Transceiver Output fixed */
#endif /* defined BSP_MCU_RX63T */

        /* Interrupt enable register
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        IEN( USB0, D0FIFO0 ) = 1u;    /* D0FIFO0 Enable */
        IEN( USB0, D1FIFO0 ) = 1u;    /* D1FIFO0 Enable */

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N)
        IEN( USB0, USBR0 )= 1u; /* USBR0 enable */

#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        IEN( USB, USBR0 ) = 1u; /* USBR0 enable */

#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

        /* Interrupt priority register
         b3-b0 IPR      Interrupt priority
         b7-b4 Reserved 0
         */
#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N)
        IPR( USB0, USBR0 )= 0x00; /* USBR0 */

#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        IPR( USB, USBR0 ) = 0x00; /* USBR0 */

#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

        IPR( USB0, USBI0 )= USB_CFG_INTERRUPT_PRIORITY; /* USBI0 in vector 128 */
        IEN( USB0, USBI0 )= 1u; /* USBI0 enable in vector 128 */
    }

    if (USB_IP1 == ip_type)
    {
#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        /* Interrupt enable register
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        IEN( USBA, D0FIFO2 ) = 1u;   /* Enable D0FIF2 interrupt */
        IEN( USBA, D1FIFO2 ) = 1u;   /* Enable D1FIF2 interrupt */

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        IEN( USBA, USBAR ) = 1u; /* Enable  USBA  interrupt */

        /* Priority D0FIFO0=0(Disable)
         b3-b0 IPR      Interrupt priority
         b7-b4 Reserved 0
         */
        IPR( USBA, USBAR ) = USB_CFG_INTERRUPT_PRIORITY; /* USBA */

#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

#if defined(BSP_MCU_RX62N)
        /* Deep standby USB monitor register
        b0      SRPC0    USB0 single end control
        b3-b1   Reserved 0
        b4      FIXPHY0  USB0 transceiver output fix
        b7-b5   Reserved 0
        b8      SRPC1    USB1 single end control
        b11-b9  Reserved 0
        b12     FIXPHY1  USB1 transceiver output fix
        b15-b13 Reserved 0
        b16     DP0      USB0 DP input
        b17     DM0      USB0 DM input
        b19-b18 Reserved 0
        b20     DOVCA0   USB0 OVRCURA input
        b21     DOVCB0   USB0 OVRCURB input
        b22     Reserved 0
        b23     DVBSTS0  USB1 VBUS input
        b24     DP1      USB1 DP input
        b25     DM1      USB1 DM input
        b27-b26 Reserved 0
        b28     DOVCA1   USB1 OVRCURA input
        b29     DOVCB1   USB1 OVRCURB input
        b30     Reserved 0
        b31     DVBSTS1  USB1 VBUS input
        */
        USB.DPUSR0R.BIT.FIXPHY1 = 0u;   /* USB1 Transceiver Output fixed */

#endif /* defined(BSP_MCU_RX62N) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        /* Interrupt enable register
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        IEN( USB1, D0FIFO1 ) = 1u;   /* Enable D0FIF1 interrupt */
        IEN( USB1, D1FIFO1 ) = 1u;   /* Enable D1FIF1 interrupt */

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        IEN( USB1, USBI1 ) = 1u; /* Enable  USB1  interrupt */
        IEN( USB, USBR1 ) = 1u; /* Enable  USB1  interrupt */

        /* Priority D0FIFO0=0(Disable)
         b3-b0 IPR      Interrupt priority
         b7-b4 Reserved 0
         */
        IPR( USB1, USBI1 ) = USB_CFG_INTERRUPT_PRIORITY; /* USB1 */
        IPR( USB, USBR1 ) = USB_CFG_INTERRUPT_PRIORITY; /* USB1 */

#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

    }
}
#endif
/******************************************************************************
 End of function usb_cpu_usbint_init
 ******************************************************************************/

/******************************************************************************
 TIMER function
 ******************************************************************************/
/******************************************************************************
 Function Name   : usb_cpu_delay_1us
 Description     : 1us Delay timer
 Arguments       : uint16_t  time        ; Delay time(*1us)
 Return value    : none
 Note            : Please change for your MCU
 ******************************************************************************/
#if 0
void usb_cpu_delay_1us (uint16_t time)
{
    R_BSP_SoftwareDelay((uint32_t)time, BSP_DELAY_MICROSECS);
}
#endif
/******************************************************************************
 End of function usb_cpu_delay_1us
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cpu_delay_xms
 Description     : xms Delay timer
 Arguments       : uint16_t  time        ; Delay time(*1ms)
 Return value    : void
 Note            : Please change for your MCU
 ******************************************************************************/
#if 0
void usb_cpu_delay_xms (uint16_t time)
{
    R_BSP_SoftwareDelay((uint32_t)time, BSP_DELAY_MILLISECS);
}

/******************************************************************************
 End of function usb_cpu_delay_xms
 ******************************************************************************/
#endif

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
#if 0
/******************************************************************************
 Function Name   : usb_cpu_int_enable
 Description     : USB Interrupt Enable
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 Return value    : void
 ******************************************************************************/
void usb_cpu_int_enable (usb_utr_t *ptr)
{
    if (USB_USBIP_0 == ptr->ip)
    {
        /* Interrupt enable register (USB0 USBIO enable)
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
///        IEN( USB0, USBI0 )= 1; /* Enable USB0 interrupt */
    }

    if (ptr->ip == USB_USBIP_1)
    {
#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        /* Interrupt enable register (USB1 USBIO enable)
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
        IEN( USBA, USBAR ) = 1u; /* Enable USBA interrupt */

#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        /* Interrupt enable register (USB1 USBIO enable)
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
        IEN( USB, USBR1 ) = 1u; /* Enable USB1 interrupt */

#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

    }
}
/******************************************************************************
 End of function usb_cpu_int_enable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cpu_int_disable
 Description     : USB Interrupt disable
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 Return value    : void
 ******************************************************************************/
void usb_cpu_int_disable (usb_utr_t *ptr)
{
    if (USB_USBIP_0 == ptr->ip)
    {
        /* Interrupt enable register (USB0 USBIO disable)
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
        IEN( USB0, USBI0 )= 0; /* Disnable USB0 interrupt */
    }

    if (USB_USBIP_1 == ptr->ip)
    {
#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        /* Interrupt enable register (USB1 USBIO disable)
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
        IEN( USBA, USBAR ) = 0u; /* Disnable USBA interrupt */

#endif  /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
        /* Interrupt enable register (USB1 USBIO disable)
         b0 IEN0 Interrupt enable bit
         b1 IEN1 Interrupt enable bit
         b2 IEN2 Interrupt enable bit
         b3 IEN3 Interrupt enable bit
         b4 IEN4 Interrupt enable bit
         b5 IEN5 Interrupt enable bit
         b6 IEN6 Interrupt enable bit
         b7 IEN7 Interrupt enable bit
         */
        IEN( USB, USBR1 ) = 0u; /* Disnable USB1 interrupt */

#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

    }
}

/******************************************************************************
 End of function usb_cpu_int_disable
 ******************************************************************************/
#endif

/******************************************************************************
 Function Name   : usb_chattaring
 Description     : Remove chattaring processing
 Arguments       : uint16_t *syssts : SYSSTS register value
 Return value    : LNST bit value
 ******************************************************************************/
uint16_t usb_chattaring (uint16_t *syssts)
{
    uint16_t lnst[4];

    while (1)
    {
        lnst[0] = (*syssts) & USB_LNST;
        usb_cpu_delay_xms((uint16_t) 1); /* 1ms wait */
        lnst[1] = (*syssts) & USB_LNST;
        usb_cpu_delay_xms((uint16_t) 1); /* 1ms wait */
        lnst[2] = (*syssts) & USB_LNST;
        if ((lnst[0] == lnst[1]) && (lnst[0] == lnst[2]))
        {
            break;
        }
    }
    return lnst[0];
}
/******************************************************************************
End of function usb_chattaring
******************************************************************************/

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */


/*******************************************************************************
 * Function Name: usbfs_usbi_isr
 * Description  : Interrupt service routine of USBF
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
static void usbfs_usbi_isr (void)
{
    /* Call USB interrupt routine */
    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        usb_hstd_usb_handler(); /* Call interrupt routine */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        usb_pstd_usb_handler(); /* Call interrupt routine */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    ICU.PIBR7.BYTE |= 0x40; /* Flag clear */

#endif /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
}
/******************************************************************************
 End of function usbfs_usbi_isr
 ******************************************************************************/


#if defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
/*******************************************************************************
 * Function Name: usbhs_usbir_isr
 * Description  : Interrupt service routine of USBF
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
static void usbhs_usbir_isr (void)
{
    /* Condition compilation by the difference of USB function */
    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
#if USB_NUM_USBIP == 2
        usb2_hstd_usb_handler(); /* Call interrupt routine */

#endif /* USB_NUM_USBIP == 2 */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        usb_pstd_usb_handler();

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
}
/******************************************************************************
 End of function usbhs_usbir_isr
 ******************************************************************************/
#endif /* defined (BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )

#if defined (BSP_MCU_RX64M) || defined (BSP_MCU_RX71M) || defined (BSP_MCU_RX65N)
/******************************************************************************
 Function Name   : usb_cpu_usb_int_hand_isr
 Description     :
 Arguments       : none
 Return value    : none
 ******************************************************************************/
static void usb_cpu_usb_int_hand_isr (void)
{
    hw_usb_pclear_sts_resm();
    ICU.IPR[IPR_USB0_USBR0].BYTE = 0x00; /* Priority Resume1=0 */
    ICU.IR[IR_USB0_USBR0].BIT.IR = 0; /* Interrupt Request USB_resume USBR1 Clear */
} /* End of function usb_cpu_usb_int_hand_isr */

#else  /* defined (BSP_MCU_RX64M) || defined (BSP_MCU_RX71M) || defined (BSP_MCU_RX65N) */
/******************************************************************************
 Function Name   : usb_cpu_usb_int_hand_isr
 Description     :
 Arguments       : none
 Return value    : none
 ******************************************************************************/
static void usb_cpu_usb_int_hand_isr (void)
{
    hw_usb_pclear_sts_resm();
    ICU.IPR[IPR_USB_USBR0].BYTE = 0x00; /* Priority Resume1=0 */
    ICU.IR[IR_USB_USBR0].BIT.IR = 0; /* Interrupt Request USB_resume USBR1 Clear */
} /* End of function usb_cpu_usb_int_hand_isr */

#endif /* defined (BSP_MCU_RX64M) || defined (BSP_MCU_RX71M) || defined (BSP_MCU_RX65N) */

#if defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N)
/******************************************************************************
Function Name   : usb2_cpu_usb_int_hand_isr
Description     :
Arguments       : none
Return value    : none
******************************************************************************/
void usb2_cpu_usb_int_hand_isr(void)
{
    hw_usb_pclear_sts_resm();
    ICU.IPR[IPR_USB_USBR1].BYTE = 0x00;   /* Priority Resume1=0 */
    ICU.IR[IR_USB_USBR1].BIT.IR = 0;      /* Interrupt Request USB_resume USBR1 Clear */
}   /* eof usb2_cpu_usb_int_hand_isr() */
#endif  /* defined (BSP_MCU_RX63N) || defined (BSP_MCU_RX62N) */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */


#if USB_CFG_DTC == USB_CFG_ENABLE
/******************************************************************************
Function Name   : usb_cpu_d0fifo_int_hand
Description     : D0FIFO interrupt Handler
Arguments       : none
Return value    : none
******************************************************************************/
static void usb_cpu_d0fifo_int_hand(void)
{
    IPR(USB0,D0FIFO0) = 0;
    usb_dma_buf2dxfifo_complete_event_set(USB_IP0, USB_D0DMA);
}
/******************************************************************************
End of function usb_cpu_d0fifo_int_hand
******************************************************************************/

/******************************************************************************
Function Name   : usb_cpu_d1fifo_int_hand
Description     : D0FIFO interrupt Handler
Arguments       : none
Return value    : none
******************************************************************************/
static void usb_cpu_d1fifo_int_hand(void)
{
    IPR(USB0,D1FIFO0) = 0;
    usb_dma_buf2dxfifo_complete_event_set(USB_IP0, USB_D1DMA);
}
/******************************************************************************
End of function usb_cpu_d1fifo_int_hand
******************************************************************************/

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX63N)
/******************************************************************************
Function Name   : usb2_cpu_d0fifo_int_hand
Description     : D0FIFO interrupt Handler
Arguments       : none
Return value    : none
******************************************************************************/
static void usb2_cpu_d0fifo_int_hand(void)
{
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    IPR(USBA,D0FIFO2) = 0;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
    IPR(USB1,D0FIFO1) = 0;

#endif  /* defined(BSP_MCU_RX63N) */
    usb_dma_buf2dxfifo_complete_event_set(USB_IP1, USB_D0DMA);
}
/******************************************************************************
End of function usb2_cpu_d0fifo_int_hand
******************************************************************************/

/******************************************************************************
Function Name   : usb2_cpu_d1fifo_int_hand
Description     : D0FIFO interrupt Handler
Arguments       : none
Return value    : none
******************************************************************************/
static void usb2_cpu_d1fifo_int_hand(void)
{
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    IPR(USBA,D1FIFO2) = 0;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
    IPR(USB1,D1FIFO1) = 0;

#endif  /* defined(BSP_MCU_RX63N) */
    usb_dma_buf2dxfifo_complete_event_set(USB_IP1, USB_D1DMA);
}
/******************************************************************************
End of function usb2_cpu_d1fifo_int_hand
******************************************************************************/
#endif /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX63N) */


#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */

/******************************************************************************
Function Name   : usb_check_use_usba_module
Description     : 
Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
Return value    : 
******************************************************************************/
bool usb_check_use_usba_module(usb_utr_t *ptr)
{
    bool    ret_code = false;

#if defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX64M)
    if (USB_NULL == ptr)
    {
    #if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        #if USB_CFG_USE_USBIP == USB_CFG_IP1
        ret_code = true;
        #endif  
    #endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
        if (USB_IP1 == ptr->ip)
        {
            ret_code = true;
        }
    }
#endif  /* !defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX64M) */

    return ret_code;
}   /* End of function usb_check_use_usba_module */

/******************************************************************************
 End  Of File
 ******************************************************************************/
