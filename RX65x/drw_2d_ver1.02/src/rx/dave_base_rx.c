//--------------------------------------------------------------------------
// Project: D/AVE
// File:    dave_base_rx.c (%version: 8 %)
//          created Fri Aug 19 15:32:32 2005 by hh04027
//
// Description:
//  %date_modified: Thu Oct 18 13:18:03 2007 %  (%derived_by:  hh74040 %)
//
// Changes:
//  2005-04-12 CSe  fully implemented missing d1 driver functionality
//  2006-10-18 ASc  add ifdefs to allow compilation with no altera lcd
//  2009-03-17 MMa  added support for TES Display Controller
//  2011-08-03 CSe  additional ifdefs in case single SOPC components not used
//  2011-10-04 CSe  removed references to BT656 generator (component no longer used)
//  2018-03-26      added support for RX
//
//--------------------------------------------------------------------------

#include <stdlib.h>
#include <stdbool.h>
#include "dave_base.h"
#include "dave_base_rx.h"

static void d1_registerprotectenable();
static void d1_registerprotectdisable();
static void d1_mstp_set(bool enable, int mstp_char, int mstp_num);

//--------------------------------------------------------------------------
//
d1_device * d1_opendevice(long flags)
{
    d1_device_rx *handle;

    /* unused arguments */
    INTERNAL_NOT_USED(flags);

    /* get new device context structure */
    handle = (d1_device_rx *)malloc(sizeof(d1_device_rx));
    if (!handle)
    {
        return NULL;
    }

    /* init device data */
    handle->dlist_indirect = 0;

    /* apply power to peripheral */
    d1_registerprotectdisable();
    d1_mstp_set (true, MSTP_C, DAVE2D_MSTP_NUM);
    d1_registerprotectenable();

    /* reset irq handlers */
    d1_initirq_intern(handle);

    return (d1_device *)handle;
}

//--------------------------------------------------------------------------
//
int d1_closedevice(d1_device *handle)
{
    int ret = 0;

    if (!handle)
    {
        return 0;
    }

    /* close irq handlers */
    ret = d1_shutdownirq_intern((d1_device_rx *) handle);

    /* power down peripheral */
    d1_registerprotectdisable();
    d1_mstp_set (false, MSTP_C, DAVE2D_MSTP_NUM);
    d1_registerprotectenable();

    free (handle);
    return ret;
}

//--------------------------------------------------------------------------
//
void d1_setregister(d1_device *handle, int deviceid, int index, long value)
{
    d1_device_rx *dev = (d1_device_rx*) handle;

    switch (deviceid)
    {
    case D1_DAVE2D:
        if ((index == D2_DLISTSTART) && (dev->dlist_indirect))
        {
            int *dlistp = (int*)value;
            dev->dlist_start = (long*)(dlistp + 1);
            WRITE_REG(DAVE2D_0_BASE, index, (unsigned long)(*dlistp));
        }
        else
        {
            WRITE_REG(DAVE2D_0_BASE, index, (unsigned long)value);
        }
    break;

    case D1_DLISTINDIRECT:
#if RX_USE_DLIST_INDIRECT
        dev->dlist_indirect = value;
#else
        dev->dlist_indirect = 0;
#endif
    break;

    default:
        
        /* unknown device */
    break;
    }
}

//--------------------------------------------------------------------------
//
long d1_getregister(d1_device *handle, int deviceid, int index)
{
    d1_device_rx *dev = (d1_device_rx*)handle;

    switch (deviceid)
    {
    case D1_DAVE2D:
        return READ_REG(DAVE2D_0_BASE, index);

    case D1_DLISTINDIRECT:
        return dev->dlist_indirect;

    default:

        /* unknown device */
        return 0;
    }
}

//--------------------------------------------------------------------------
//
int d1_devicesupported(d1_device *handle, int deviceid)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    switch (deviceid)
    {
    case D1_DAVE2D:
#if RX_USE_DLIST_INDIRECT
    case D1_DLISTINDIRECT:
#endif
        return 1;

    default:

        /* unknown device */
        return 0;
    }
}

/***********************************************************************
 * Function Name: d1_mstp_set
 * Description  : Write the MSTP register.
 * Arguments    : enable
 *                    Enable or disable the register bit.
 *                mstp_char
 *                    MSTP register offset position. 
 *                mstp_num
 *                    The register bit position.
 * Return Value : none
 **********************************************************************/
static void d1_mstp_set(bool enable, int mstp_char, int mstp_num)
{
    unsigned long *p_mstp_addr;

    /* The address offset from the address of the base register is cast to match the size of the register. */
    p_mstp_addr = ((unsigned long *)MSTP_0_BASE) + mstp_char;

    if (true == enable)
    {
        *p_mstp_addr = ((*p_mstp_addr) & (~(1 << mstp_num)));
    }
    else
    {
        *p_mstp_addr = ((*p_mstp_addr) | (1 << mstp_num));
    }
} /* End of function d1_mstp_set() */

/***********************************************************************
 * Function Name: d1_registerprotectenable
 * Description  : Enable protect bit 1 of PRCR register.
 * Arguments    : none
 * Return Value : none
 **********************************************************************/
static void d1_registerprotectenable()
{
    unsigned short *p_prcr_addr;

    /* The address of the base register is cast to match the size of the register. */
    p_prcr_addr = (unsigned short *)PRCR_0_BASE;
    *p_prcr_addr = (((*p_prcr_addr) | PRCR_KEY) & (~PRCR_PRC1));
} /* End of function d1_registerprotectenable() */

/***********************************************************************
 * Function Name: d1_registerprotectdisable
 * Description  : Disable protect bit 1 of PRCR register.
 * Arguments    : none
 * Return Value : none
 **********************************************************************/
static void d1_registerprotectdisable()
{
    unsigned short *p_prcr_addr;

    /* The address of the base register is cast to match the size of the register. */
    p_prcr_addr = (unsigned short *)PRCR_0_BASE;
    *p_prcr_addr = (((*p_prcr_addr) | PRCR_KEY) | PRCR_PRC1);
} /* End of function d1_registerprotectdisable() */
