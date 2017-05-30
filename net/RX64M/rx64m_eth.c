/**
 * @file rx64m_eth.c
 * @brief Renesas RX64M Ethernet MAC controller
 *
 * @section License
 *
 * Copyright (C) 2010-2017 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneTCP Open.
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
 * @author Hiramatsu Kunihito (hira@rvf-rc45.net)
 * @version 1.7.6
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL NIC_TRACE_LEVEL

//Dependencies
#include "iodefine.h"

#define ETHERC	ETHERC0
#define EDMAC	EDMAC0
#define MSTP_EDMAC	MSTP_EDMAC0

#include "core/net.h"
#include "rx64m_eth.h"
#include "debug.h"

//Underlying network interface
static NetInterface *nicDriverInterface;

//IAR EWRX compiler?
#if defined(__ICCRX__)

//Transmit buffer
#pragma data_alignment = 32
static uint8_t txBuffer[RX64M_ETH_TX_BUFFER_COUNT][RX64M_ETH_TX_BUFFER_SIZE];
//Receive buffer
#pragma data_alignment = 32
static uint8_t rxBuffer[RX64M_ETH_RX_BUFFER_COUNT][RX64M_ETH_RX_BUFFER_SIZE];
//Transmit DMA descriptors
#pragma data_alignment = 32
static Rx64mTxDmaDesc txDmaDesc[RX64M_ETH_TX_BUFFER_COUNT];
//Receive DMA descriptors
#pragma data_alignment = 32
static Rx64mRxDmaDesc rxDmaDesc[RX64M_ETH_RX_BUFFER_COUNT];

//GCC compiler?
#else

#define __interrupt __attribute__ ((interrupt))

//Transmit buffer
static uint8_t txBuffer[RX64M_ETH_TX_BUFFER_COUNT][RX64M_ETH_TX_BUFFER_SIZE]
   __attribute__((aligned(32)));
//Receive buffer
static uint8_t rxBuffer[RX64M_ETH_RX_BUFFER_COUNT][RX64M_ETH_RX_BUFFER_SIZE]
   __attribute__((aligned(32)));
//Transmit DMA descriptors
static Rx64mTxDmaDesc txDmaDesc[RX64M_ETH_TX_BUFFER_COUNT]
   __attribute__((aligned(32)));
//Receive DMA descriptors
static Rx64mRxDmaDesc rxDmaDesc[RX64M_ETH_RX_BUFFER_COUNT]
   __attribute__((aligned(32)));

#endif

//Current transmit descriptor
static uint_t txIndex;
//Current receive descriptor
static uint_t rxIndex;


/**
 * @brief RX64M Ethernet MAC driver
 **/

const NicDriver rx64mEthDriver =
{
   NIC_TYPE_ETHERNET,
   ETH_MTU,
   rx64mEthInit,
   rx64mEthTick,
   rx64mEthEnableIrq,
   rx64mEthDisableIrq,
   rx64mEthEventHandler,
   rx64mEthSendPacket,
   rx64mEthSetMulticastFilter,
   rx64mEthUpdateMacConfig,
   rx64mEthWritePhyReg,
   rx64mEthReadPhyReg,
   TRUE,
   TRUE,
   TRUE,
   TRUE
};


/**
 * @brief RX64M Ethernet MAC initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t rx64mEthInit(NetInterface *interface)
{
   error_t error;

   //Debug message
   TRACE_INFO("Initializing RX64M Ethernet MAC...\r\n");

   //Save underlying network interface
   nicDriverInterface = interface;

   //Disable protection
///   SYSTEM.PRCR.WORD = 0xA50B;
   //Cancel EDMAC module stop state
///   MSTP(EDMAC) = 0;
   //Enable protection
///   SYSTEM.PRCR.WORD = 0xA500;

   //GPIO configuration
   rx64mEthInitGpio(interface);

   //Reset EDMAC module
   EDMAC.EDMR.BIT.SWR = 1;
   system_sleep(10);

   //PHY transceiver initialization
   error = interface->phyDriver->init(interface);
   //Failed to initialize PHY transceiver?
   if(error)
      return error;

   //Initialize DMA descriptor lists
   rx64mEthInitDmaDesc(interface);

   //Maximum frame length that can be accepted
   ETHERC.RFLR.LONG = 1518;
   //Set default inter packet gap (96-bit time)
   ETHERC.IPGR.LONG = 0x14;

   //Set the upper 32 bits of the MAC address
   ETHERC.MAHR = (interface->macAddr.b[0] << 24) | (interface->macAddr.b[1] << 16) |
      (interface->macAddr.b[2] << 8) | interface->macAddr.b[3];

   //Set the lower 16 bits of the MAC address
   ETHERC.MALR.BIT.MA = (interface->macAddr.b[4] << 8) | interface->macAddr.b[5];

   TRACE_INFO("MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",
		interface->macAddr.b[0], interface->macAddr.b[1], interface->macAddr.b[2],
		interface->macAddr.b[3], interface->macAddr.b[4], interface->macAddr.b[5]
   );

   //Set descriptor length (16 bytes)
   EDMAC.EDMR.BIT.DL = 0;
   //Select little endian mode
   EDMAC.EDMR.BIT.DE = 1;
   //Use store and forward mode
   EDMAC.TFTR.BIT.TFT = 0;

   //Set transmit FIFO size (2048 bytes)
   EDMAC.FDR.BIT.TFD = 7;
   //Set receive FIFO size (2048 bytes)
   EDMAC.FDR.BIT.RFD = 7;

   //Enable continuous reception of multiple frames
   EDMAC.RMCR.BIT.RNR = 1;

   //Accept transmit interrupt notifications
   EDMAC.TRIMD.BIT.TIM = 0;
   EDMAC.TRIMD.BIT.TIS = 1;

   //Disable all EDMAC interrupts
   EDMAC.EESIPR.LONG = 0;
   //Enable only the desired EDMAC interrupts
   EDMAC.EESIPR.BIT.TWBIP = 1;
   EDMAC.EESIPR.BIT.FRIP = 1;

   //Configure EDMAC interrupt priority
///   IPR(ETHER, EINT) = RX64M_ETH_IRQ_PRIORITY;
	ICU.IPR[IPR_ICU_GROUPAL1].BIT.IPR = RX64M_ETH_IRQ_PRIORITY;

   //Enable transmission and reception
   ETHERC.ECMR.BIT.TE = 1;
   ETHERC.ECMR.BIT.RE = 1;

   //Instruct the DMA to poll the receive descriptor list
   EDMAC.EDRRR.BIT.RR = 1;

   //Accept any packets from the upper layer
   osSetEvent(&interface->nicTxEvent);

   //Successful initialization
   return NO_ERROR;
}


//RX64M Demonstration Kit?
#if defined(USE_RX64M)

/**
 * @brief GPIO configuration
 * @param[in] interface Underlying network interface
 **/

void rx64mEthInitGpio(NetInterface *interface)
{
}

#endif


/**
 * @brief Initialize DMA descriptor lists
 * @param[in] interface Underlying network interface
 **/

void rx64mEthInitDmaDesc(NetInterface *interface)
{
   uint_t i;

   //Initialize TX descriptors
   for(i = 0; i < RX64M_ETH_TX_BUFFER_COUNT; i++)
   {
      //The descriptor is initially owned by the application
      txDmaDesc[i].td0 = 0;
      //Transmit buffer length
      txDmaDesc[i].td1 = 0;
      //Transmit buffer address
      txDmaDesc[i].td2 = (uint32_t) txBuffer[i];
      //Clear padding field
      txDmaDesc[i].padding = 0;
   }

   //Mark the last descriptor entry with the TDLE flag
   txDmaDesc[i - 1].td0 |= EDMAC_TD0_TDLE;
   //Initialize TX descriptor index
   txIndex = 0;

   //Initialize RX descriptors
   for(i = 0; i < RX64M_ETH_RX_BUFFER_COUNT; i++)
   {
      //The descriptor is initially owned by the DMA
      rxDmaDesc[i].rd0 = EDMAC_RD0_RACT;
      //Receive buffer length
      rxDmaDesc[i].rd1 = (RX64M_ETH_RX_BUFFER_SIZE << 16) & EDMAC_RD1_RBL;
      //Receive buffer address
      rxDmaDesc[i].rd2 = (uint32_t) rxBuffer[i];
      //Clear padding field
      rxDmaDesc[i].padding = 0;
   }

   //Mark the last descriptor entry with the RDLE flag
   rxDmaDesc[i - 1].rd0 |= EDMAC_RD0_RDLE;
   //Initialize RX descriptor index
   rxIndex = 0;

   //Start address of the TX descriptor list
   EDMAC.TDLAR = txDmaDesc;
   //Start address of the RX descriptor list
   EDMAC.RDLAR = rxDmaDesc;
}


/**
 * @brief RX64M Ethernet MAC timer handler
 *
 * This routine is periodically called by the TCP/IP stack to
 * handle periodic operations such as polling the link state
 *
 * @param[in] interface Underlying network interface
 **/

void rx64mEthTick(NetInterface *interface)
{
   //Handle periodic operations
   interface->phyDriver->tick(interface);
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void rx64mEthEnableIrq(NetInterface *interface)
{
   //Enable Ethernet MAC interrupts
///   IEN(ETHER, EINT) = 1;
	ICU.GENAL1.BIT.EN4 = 1;
	ICU.IER[IER_ICU_GROUPAL1].BIT.IEN1 = 1;

   //Enable Ethernet PHY interrupts
   interface->phyDriver->enableIrq(interface);
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void rx64mEthDisableIrq(NetInterface *interface)
{
   //Disable Ethernet MAC interrupts
///   IEN(ETHER, EINT) = 0;
	ICU.GENAL1.BIT.EN4 = 0;
	ICU.IER[IER_ICU_GROUPAL1].BIT.IEN1 = 0;

   //Disable Ethernet PHY interrupts
   interface->phyDriver->disableIrq(interface);
}


/**
 * @brief RX64M Ethernet MAC interrupt service routine
 **/

#if defined(__ICCRX__)
#pragma vector = VECT_ETHER_EINT
#endif
__interrupt void rx64mEthIrqHandler(void)
{
   bool_t flag;
   uint32_t status;

   //Allow nested interrupts
///   __enable_interrupt();

   //This flag will be set if a higher priority task must be woken
   flag = FALSE;

   //Read interrupt status register
   status = EDMAC.EESR.LONG;

   //A packet has been transmitted?
   if(status & EDMAC_EESR_TWB)
   {
      //Clear TWB interrupt flag
      EDMAC.EESR.LONG = EDMAC_EESR_TWB;

      //Check whether the TX buffer is available for writing
      if(!(txDmaDesc[txIndex].td0 & EDMAC_TD0_TACT))
      {
         //Notify the TCP/IP stack that the transmitter is ready to send
         flag |= osSetEventFromIsr(&nicDriverInterface->nicTxEvent);
      }
   }

   //A packet has been received?
   if(status & EDMAC_EESR_FR)
   {
      //Disable FR interrupts
      EDMAC.EESIPR.BIT.FRIP = 0;

      //Set event flag
      nicDriverInterface->nicEvent = TRUE;
      //Notify the TCP/IP stack of the event
      flag |= osSetEventFromIsr(&netEvent);
   }

   //Leave interrupt service routine
   osExitIsr(flag);
}


/**
 * @brief RX64M Ethernet MAC event handler
 * @param[in] interface Underlying network interface
 **/

void rx64mEthEventHandler(NetInterface *interface)
{
   error_t error;

   //Packet received?
   if(EDMAC.EESR.LONG & EDMAC_EESR_FR)
   {
      //Clear FR interrupt flag
      EDMAC.EESR.LONG = EDMAC_EESR_FR;

      //Process all pending packets
      do
      {
         //Read incoming packet
         error = rx64mEthReceivePacket(interface);

         //No more data in the receive buffer?
      } while(error != ERROR_BUFFER_EMPTY);
   }

   //Re-enable EDMAC interrupts
   EDMAC.EESIPR.BIT.TWBIP = 1;
   EDMAC.EESIPR.BIT.FRIP = 1;
}


/**
 * @brief Send a packet
 * @param[in] interface Underlying network interface
 * @param[in] buffer Multi-part buffer containing the data to send
 * @param[in] offset Offset to the first data byte
 * @return Error code
 **/

error_t rx64mEthSendPacket(NetInterface *interface,
   const NetBuffer *buffer, size_t offset)
{
   //Retrieve the length of the packet
   size_t length = netBufferGetLength(buffer) - offset;

   //Check the frame length
   if(length > RX64M_ETH_TX_BUFFER_SIZE)
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
      //Report an error
      return ERROR_INVALID_LENGTH;
   }

   //Make sure the current buffer is available for writing
   if(txDmaDesc[txIndex].td0 & EDMAC_TD0_TACT)
      return ERROR_FAILURE;

   //Copy user data to the transmit buffer
   netBufferRead(txBuffer[txIndex], buffer, offset, length);

   //Write the number of bytes to send
   txDmaDesc[txIndex].td1 = (length << 16) & EDMAC_TD1_TBL;

   //Check current index
   if(txIndex < (RX64M_ETH_TX_BUFFER_COUNT - 1))
   {
      //Give the ownership of the descriptor to the DMA engine
      txDmaDesc[txIndex].td0 = EDMAC_TD0_TACT | EDMAC_TD0_TFP_SOF |
         EDMAC_TD0_TFP_EOF | EDMAC_TD0_TWBI;

      //Point to the next descriptor
      txIndex++;
   }
   else
   {
      //Give the ownership of the descriptor to the DMA engine
      txDmaDesc[txIndex].td0 = EDMAC_TD0_TACT | EDMAC_TD0_TDLE |
         EDMAC_TD0_TFP_SOF | EDMAC_TD0_TFP_EOF | EDMAC_TD0_TWBI;

      //Wrap around
      txIndex = 0;
   }

   //Instruct the DMA to poll the transmit descriptor list
   EDMAC.EDTRR.BIT.TR = 1;

   //Check whether the next buffer is available for writing
   if(!(txDmaDesc[txIndex].td0 & EDMAC_TD0_TACT))
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
   }

   //Successful write operation
   return NO_ERROR;
}


/**
 * @brief Receive a packet
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t rx64mEthReceivePacket(NetInterface *interface)
{
   error_t error;
   size_t n;

   //The current buffer is available for reading?
   if(!(rxDmaDesc[rxIndex].rd0 & EDMAC_RD0_RACT))
   {
      //SOF and EOF flags should be set
      if((rxDmaDesc[rxIndex].rd0 & EDMAC_RD0_RFP_SOF) &&
         (rxDmaDesc[rxIndex].rd0 & EDMAC_RD0_RFP_EOF))
      {
         //Make sure no error occurred
         if(!(rxDmaDesc[rxIndex].rd0 & (EDMAC_RD0_RFS_MASK & ~EDMAC_RD0_RFS_RMAF)))
         {
            //Retrieve the length of the frame
            n = rxDmaDesc[rxIndex].rd1 & EDMAC_RD1_RFL;
            //Limit the number of data to read
            n = MIN(n, RX64M_ETH_RX_BUFFER_SIZE);

            //Pass the packet to the upper layer
            nicProcessPacket(interface, rxBuffer[rxIndex], n);

            //Valid packet received
            error = NO_ERROR;
         }
         else
         {
            //The received packet contains an error
            error = ERROR_INVALID_PACKET;
         }
      }
      else
      {
         //The packet is not valid
         error = ERROR_INVALID_PACKET;
      }

      //Check current index
      if(rxIndex < (RX64M_ETH_RX_BUFFER_COUNT - 1))
      {
         //Give the ownership of the descriptor back to the DMA
         rxDmaDesc[rxIndex].rd0 = EDMAC_RD0_RACT;
         //Point to the next descriptor
         rxIndex++;
      }
      else
      {
         //Give the ownership of the descriptor back to the DMA
         rxDmaDesc[rxIndex].rd0 = EDMAC_RD0_RACT | EDMAC_RD0_RDLE;
         //Wrap around
         rxIndex = 0;
      }

      //Instruct the DMA to poll the receive descriptor list
      EDMAC.EDRRR.BIT.RR = 1;
   }
   else
   {
      //No more data in the receive buffer
      error = ERROR_BUFFER_EMPTY;
   }

   //Return status code
   return error;
}


/**
 * @brief Configure multicast MAC address filtering
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t rx64mEthSetMulticastFilter(NetInterface *interface)
{
   uint_t i;
   bool_t acceptMulticast;

   //This flag will be set if multicast addresses should be accepted
   acceptMulticast = FALSE;

   //The MAC filter table contains the multicast MAC addresses
   //to accept when receiving an Ethernet frame
   for(i = 0; i < MAC_MULTICAST_FILTER_SIZE; i++)
   {
      //Valid entry?
      if(interface->macMulticastFilter[i].refCount > 0)
      {
         //Accept multicast addresses
         acceptMulticast = TRUE;
         //We are done
         break;
      }
   }

   //Enable the reception of multicast frames if necessary
   if(acceptMulticast)
      EDMAC.EESR.BIT.RMAF = 1;
   else
      EDMAC.EESR.BIT.RMAF = 0;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Adjust MAC configuration parameters for proper operation
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t rx64mEthUpdateMacConfig(NetInterface *interface)
{
   //10BASE-T or 100BASE-TX operation mode?
   if(interface->linkSpeed == NIC_LINK_SPEED_100MBPS)
      ETHERC.ECMR.BIT.RTM = 1;
   else
      ETHERC.ECMR.BIT.RTM = 0;

   //Half-duplex or full-duplex mode?
   if(interface->duplexMode == NIC_FULL_DUPLEX_MODE)
      ETHERC.ECMR.BIT.DM = 1;
   else
      ETHERC.ECMR.BIT.DM = 0;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Write PHY register
 * @param[in] phyAddr PHY address
 * @param[in] regAddr Register address
 * @param[in] data Register value
 **/

void rx64mEthWritePhyReg(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
   //Synchronization pattern
   rx64mEthWriteSmi(SMI_SYNC, 32);
   //Start of frame
   rx64mEthWriteSmi(SMI_START, 2);
   //Set up a write operation
   rx64mEthWriteSmi(SMI_WRITE, 2);
   //Write PHY address
   rx64mEthWriteSmi(phyAddr, 5);
   //Write register address
   rx64mEthWriteSmi(regAddr, 5);
   //Turnaround
   rx64mEthWriteSmi(SMI_TA, 2);
   //Write register value
   rx64mEthWriteSmi(data, 16);
   //Release MDIO
   rx64mEthReadSmi(1);
}


/**
 * @brief Read PHY register
 * @param[in] phyAddr PHY address
 * @param[in] regAddr Register address
 * @return Register value
 **/

uint16_t rx64mEthReadPhyReg(uint8_t phyAddr, uint8_t regAddr)
{
   uint16_t data;

   //Synchronization pattern
   rx64mEthWriteSmi(SMI_SYNC, 32);
   //Start of frame
   rx64mEthWriteSmi(SMI_START, 2);
   //Set up a read operation
   rx64mEthWriteSmi(SMI_READ, 2);
   //Write PHY address
   rx64mEthWriteSmi(phyAddr, 5);
   //Write register address
   rx64mEthWriteSmi(regAddr, 5);
   //Turnaround to avoid contention
   rx64mEthReadSmi(1);
   //Read register value
   data = rx64mEthReadSmi(16);
   //Force the PHY to release the MDIO pin
   rx64mEthReadSmi(1);

   //Return PHY register contents
   return data;
}


/**
 * @brief SMI write operation
 * @param[in] data Raw data to be written
 * @param[in] length Number of bits to be written
 **/

void rx64mEthWriteSmi(uint32_t data, uint_t length)
{
   //Skip the most significant bits since they are meaningless
   data <<= 32 - length;

   //Configure MDIO as an output
   ETHERC.PIR.BIT.MMD = 1;

   //Write the specified number of bits
   while(length--)
   {
      //Write MDIO
      if(data & 0x80000000)
         ETHERC.PIR.BIT.MDO = 1;
      else
         ETHERC.PIR.BIT.MDO = 0;

      //Assert MDC
      system_usleep(1);
      ETHERC.PIR.BIT.MDC = 1;
      //Deassert MDC
      system_usleep(1);
      ETHERC.PIR.BIT.MDC = 0;

      //Rotate data
      data <<= 1;
   }
}


/**
 * @brief SMI read operation
 * @param[in] length Number of bits to be read
 * @return Data resulting from the MDIO read operation
 **/

uint32_t rx64mEthReadSmi(uint_t length)
{
   uint32_t data = 0;

   //Configure MDIO as an input
   ETHERC.PIR.BIT.MMD = 0;

   //Read the specified number of bits
   while(length--)
   {
      //Rotate data
      data <<= 1;

      //Assert MDC
      ETHERC.PIR.BIT.MDC = 1;
      system_usleep(1);
      //Deassert MDC
      ETHERC.PIR.BIT.MDC = 0;
      system_usleep(1);

      //Check MDIO state
      if(ETHERC.PIR.BIT.MDI)
         data |= 0x00000001;
   }

   //Return the received data
   return data;
}
