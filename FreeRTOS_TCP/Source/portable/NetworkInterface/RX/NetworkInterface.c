/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
/// #include "FreeRTOS_DNS.h"
#include "NetworkBufferManagement.h"
#include "NetworkInterface.h"

/***********************************************************************************************************************
 * Function Name: xNetworkInterfaceInitialise ()
 * Description  : Initialization of Ethernet driver.
 * Arguments    : none
 * Return Value : pdPASS, pdFAIL
 **********************************************************************************************************************/
BaseType_t xNetworkInterfaceInitialise( void )
{
	BaseType_t xReturn;

	xReturn = pdFAIL;

    FreeRTOS_printf( ( "xNetworkInterfaceInitialise returns %d\n", xReturn ) );

    return xReturn;
}


/***********************************************************************************************************************
 * Function Name: xNetworkInterfaceOutput ()
 * Description  : Simple network output interface.
 * Arguments    : pxDescriptor, xReleaseAfterSend
 * Return Value : pdTRUE, pdFALSE
 **********************************************************************************************************************/
BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxDescriptor,
                                    BaseType_t xReleaseAfterSend )
{
    BaseType_t xReturn = pdFALSE;


    return xReturn;
}


/***********************************************************************************************************************
 * Function Name: prvEMACDeferredInterruptHandlerTask ()
 * Description  : The deferred interrupt handler is a standard RTOS task.
 * Arguments    : pvParameters
 * Return Value : none
 **********************************************************************************************************************/
static void prvEMACDeferredInterruptHandlerTask( void * pvParameters )
{
}


/***********************************************************************************************************************
 * Function Name: vNetworkInterfaceAllocateRAMToBuffers ()
 * Description  : .
 * Arguments    : pxNetworkBuffers
 * Return Value : none
 **********************************************************************************************************************/
void vNetworkInterfaceAllocateRAMToBuffers( NetworkBufferDescriptor_t pxNetworkBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ] )
{
}


/***********************************************************************************************************************
 * Function Name: prvLinkStatusChange ()
 * Description  : Function will be called when the Link Status of the phy has changed ( see ether_callback.c )
 * Arguments    : xStatus : true when statyus has become high
 * Return Value : void
 **********************************************************************************************************************/
void prvLinkStatusChange( BaseType_t xStatus )
{
}

