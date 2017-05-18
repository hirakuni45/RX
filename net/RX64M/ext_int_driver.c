/**
 * @file ext_int_driver.c
 * @brief External interrupt line driver
 *
 * @section License
 *
 * Copyright (C) 2010-2017 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.7.6
 **/

//Dependencies
#include "iodefine.h"
#include "core/net.h"
#include "ext_int_driver.h"
#include "debug.h"


/**
 * @brief External interrupt line driver
 **/

const ExtIntDriver extIntDriver =
{
   extIntInit,
   extIntEnableIrq,
   extIntDisableIrq
};


/**
 * @brief EXTI configuration
 * @return Error code
 **/

error_t extIntInit(void)
{
   //Configure reset pin as an output
   //PORTC.PDR.BIT.B3 = 1;
   //Reset the PHY transceiver by asserting RST pin
   //PORTC.PODR.BIT.B3 = 1;
   //sleep(10);
   //Take the PHY transceiver out of reset
   //PORTC.PODR.BIT.B3 = 0;

   //Make sure IQR15 interrupt is disabled
   IEN(ICU, IRQ15) = 0;
   //Disable digital filter
   ICU.IRQFLTE1.BIT.FLTEN15 = 0;

   //Unlock MPC registers
   MPC.PWPR.BIT.B0WI = 0;
   MPC.PWPR.BIT.PFSWE = 1;

   //Configure IRQ15 (P07) as an input
   PORT0.PDR.BIT.B7 = 0;
   PORT0.PMR.BIT.B7 = 0;
   MPC.P07PFS.BYTE  = 0x40;

   //Lock MPC registers
   MPC.PWPR.BIT.PFSWE = 0;
   MPC.PWPR.BIT.B0WI = 0;

   //Set digital filter sampling clock (PCLK)
   ICU.IRQFLTC1.BIT.FCLKSEL15 = 0;
   //Enable digital filter
   ICU.IRQFLTE1.BIT.FLTEN15 = 1;
   //Configure IRQ15 polarity (falling edge)
   ICU.IRQCR[15].BIT.IRQMD = 1;

   //Configure IRQ15 interrupt priority
   IPR(ICU, IRQ15) = 1;
   //Clear interrupt flag
   IR(ICU, IRQ15) = 0;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Enable external interrupts
 **/

void extIntEnableIrq(void)
{
   //Enable IRQ15 interrupt
   IEN(ICU, IRQ15) = 1;
}


/**
 * @brief Disable external interrupts
 **/

void extIntDisableIrq(void)
{
   //Disable IRQ15 interrupt
   IEN(ICU, IRQ15) = 0;
}


/**
 * @brief External interrupt handler
 **/

#if defined(__ICCRX__)
#pragma vector = VECT_ICU_IRQ15
#else
#define __interrupt __attribute__ ((interrupt))
#endif
__interrupt void extIntHandler(void)
{
   bool_t flag;
   NetInterface *interface;

   //Allow nested interrupts
///   __enable_interrupt();

   //Point to the structure describing the network interface
   interface = &netInterface[0];

   //Set event flag
   interface->phyEvent = TRUE;
   //Notify the TCP/IP stack of the event
   flag = osSetEventFromIsr(&netEvent);

   //Leave interrupt service routine
   osExitIsr(flag);
}
