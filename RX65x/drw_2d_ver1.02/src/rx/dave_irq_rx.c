//--------------------------------------------------------------------------
// Project: D/AVE
// File:    dave_irq_rx.c (%version: 8 %)
//          created Tue Aug 23 09:26:54 2005 by hh04027
//
// Description:
//  %date_modified: Thu Oct 18 13:28:42 2007 %  (%derived_by:  hh74040 %)
//
// Changes:
//  2006-01-04 CSe  adapted to changes in dave_base.h
//  2005-04-12 CSe  fully implemented missing d1 driver functionality
//  2007-10-18 ASc  added ifdefs to allow compilation without altera lcd
//  2009-03-17 MMa  added support for TES Display Controller
//  2012-08-03 CSe  clearing interrupt before calling registered IRQ handler
//  2018-01-24      added support for RX
//--------------------------------------------------------------------------

#include <stdlib.h>
#include <stdbool.h>
#include "dave_base.h"
#include "dave_base_rx.h"

#define DAVE_STAT        (0x0)  /* STATUS register offset              */
#define DAVE_IRQ_CTRL    (0x30) /* IRQCTL register offset              */
#define DAVE_IRQ_IPR     (7)    /* Interrupt priority of DRW2D         */
#define DAVE_IRQ_GRP_NUM (11)   /* Interrupt request bit of DRW2D      */
#define ICU_GROUPAL1     (113)  /* Interrupt vector number of GROUPAL1 */

//--------------------------------------------------------------------------

enum d1_irqslots
{
    d1_irqslot_break = 0, 
    d1_irqslot_vbi = 1, 
    d1_irqslot_dlist = 2, 
    d1_irqcount
};

//--------------------------------------------------------------------------

static d1_interrupt g_irq_handler[d1_irqcount];
static void *g_irq_data[d1_irqcount];
static volatile int g_irq_triggered[d1_irqcount];
static d1_device_rx *context;

static void d1_ir_set(bool enable, int vector);
static void d1_ipr_set(unsigned char priority, int vector);
static void d1_ien_set(bool enable, int vector);
static void d1_genal1_set(bool enable, int grp_num);

static unsigned char d1_ipr_get(int vector);
static unsigned long d1_genal1_get();
static unsigned long d1_grpal1_get();

static void excep_icu_groupal1_isr(void);

static int d1_mapirq_intern(int irqtype)
{
    int index;

    /* map irqtype bit to slot index */
    switch (irqtype)
    {
    case d1_irq_break:
        index = d1_irqslot_break;
    break;

    case d1_irq_vbi:
        index = d1_irqslot_vbi;
    break;

    case d1_irq_dlist:
        index = d1_irqslot_dlist;
    break;

    default:
        index = -1;
    break;
    }

    return index;
}

//--------------------------------------------------------------------------
// initializaton + deinitialization
int d1_initirq_intern(d1_device_rx *handle)
{
    unsigned char tmp_ipr;

    context = handle;

    /* clear DAVE irq's, enable dlist irq */
    WRITE_REG(DAVE2D_0_BASE, DAVE_IRQ_CTRL, 0xe);

    /* enable DAVE irq */
    d1_genal1_set(true, DAVE_IRQ_GRP_NUM);

    /* group interrupt request is disabled */
    d1_ien_set(false, ICU_GROUPAL1);

    /* interrupt request is cleared */
    d1_ir_set(false, ICU_GROUPAL1);

    /* group interrupt request priority level is set */
    tmp_ipr = (unsigned char)((DAVE_IRQ_IPR > d1_ipr_get(ICU_GROUPAL1)) ? DAVE_IRQ_IPR : d1_ipr_get(ICU_GROUPAL1));
    d1_ipr_set(tmp_ipr, ICU_GROUPAL1);

    /* group interrupt request is enabled */
    d1_ien_set(true, ICU_GROUPAL1);

    return 1;
}

//--------------------------------------------------------------------------
//
void d1_setirqhandler(d1_device *handle, int irqtype, d1_interrupt code, void *data)
{
    int irqslot;

    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* get slot */
    irqslot = d1_mapirq_intern(irqtype);
    if (irqslot < 0)
    {
        return;
    }

    /* store irq handler and pointer */
    g_irq_handler[irqslot] = code;
    g_irq_data[irqslot] = data;
}

//--------------------------------------------------------------------------
//
d1_interrupt d1_getirqhandler(d1_device *handle, int irqtype)
{
    int irqslot;

    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* get slot */
    irqslot = d1_mapirq_intern(irqtype);
    if (irqslot < 0)
    {
        return NULL;
    }

    return g_irq_handler[irqslot];
}

//--------------------------------------------------------------------------
//
void * d1_getirqdata(d1_device *handle, int irqtype)
{
    int irqslot;

    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* get slot */
    irqslot = d1_mapirq_intern(irqtype);
    if (irqslot < 0)
    {
        return NULL;
    }

    return g_irq_data[irqslot];
}

int d1_shutdownirq_intern(d1_device_rx *handle)
{
    unsigned long tmp_gen;

    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* disable DAVE irq */
    d1_genal1_set(false, DAVE_IRQ_GRP_NUM);

    /* clear DAVE irq's, disable dlist irq */
    WRITE_REG(DAVE2D_0_BASE, DAVE_IRQ_CTRL, 0xc);

    tmp_gen = d1_genal1_get();
    if (0 == tmp_gen)
    {
        /* group interrupt request is disabled */
        d1_ien_set(false, ICU_GROUPAL1);

        /* group interrupt request priority level is cleared */
        d1_ipr_set(0, ICU_GROUPAL1);
    }

    return 1;
}

//--------------------------------------------------------------------------
//
int d1_queryirq(d1_device *handle, int irqmask, int timeout)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* break + vip + vbi interrupts are not supported */
    if (irqmask & ~d1_irq_break & ~d1_irq_vip & ~d1_irq_vbi)
    {
        if ((irqmask & d1_irq_dlist) && g_irq_triggered[d1_irqslot_dlist])
        {
            g_irq_triggered[d1_irqslot_dlist] = 0;
            return d1_irq_dlist;
        }

        if (timeout == d1_to_no_wait)
        {
            return 0;
        }

        /* wait for irq */
        while(1)
        {
            if ((irqmask & d1_irq_dlist) && g_irq_triggered[d1_irqslot_dlist])
            {
                g_irq_triggered[d1_irqslot_dlist] = 0;
                return d1_irq_dlist;
            }
        }
    }

    return 0;
}

int d1_callirqhandler(d1_device *handle, int irqtype, void *irqdata)
{
    int irqslot;

    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* get slot */
    irqslot = d1_mapirq_intern(irqtype);
    if (irqslot < 0)
    {
        return 0;
    }

    if (!g_irq_handler[irqslot])
    {
        return 1;
    }

    /* call irq handler */
    g_irq_handler[irqslot](irqtype, irqdata, g_irq_data[irqslot]);

    return 1;
}

void drw_int_isr(void)
{
    unsigned long intReg;

    intReg = READ_REG(DAVE2D_0_BASE, DAVE_STAT);

    /* any DAVE interrupt? */
    if (intReg & 0x30)
    {
        /* clear/enable all DAVE interrupts */
        WRITE_REG(DAVE2D_0_BASE, DAVE_IRQ_CTRL, 0xe);

        /* display list interrupt? */
        if (intReg & 0x20)
        {
            if (context->dlist_indirect && *(context->dlist_start) != 0)
            {
                long dlist_addr;
                dlist_addr = *(context->dlist_start);

                /* get next dlist start address */
                context->dlist_start++;

                /* starting Dave */
                WRITE_REG(DAVE2D_0_BASE, D2_DLISTSTART, dlist_addr);
            }
            else
            {
                if (g_irq_handler[d1_irqslot_dlist])
                {
                    g_irq_handler[d1_irqslot_dlist] (d1_irq_dlist, 0, g_irq_data[d1_irqslot_dlist]);
                }

                g_irq_triggered[d1_irqslot_dlist] = 1;
            }
        }
    }
}

/// #pragma interrupt excep_icu_groupal1_isr(vect=113)
/***********************************************************************
 * Function Name: excep_icu_groupal1_isr
 * Description  : GRPAL1 interrupt routine for DRW2D.
 * Arguments    : none
 * Return Value : none
 **********************************************************************/
static void excep_icu_groupal1_isr(void)
{
    unsigned long isflag;

    isflag = d1_grpal1_get();

    if (0x00000800UL == isflag)
    {
        drw_int_isr();
    }
} /* End of function excep_icu_groupal1_isr() */

/***********************************************************************
 * Function Name: d1_ir_set
 * Description  : Write the IR register.
 * Arguments    : enable
 *                    Enable or disable the register bit.
 *                vector
 *                    Interrupt vector number.
 * Return Value : none
 **********************************************************************/
static void d1_ir_set(bool enable, int vector)
{
    unsigned char *p_ir_addr;

    /* The address offset from the address of the base register is cast to match the size of the register. */
    p_ir_addr = ((unsigned char *)IR_0_BASE) + vector;

    if (true == enable)
    {
        *p_ir_addr = 1;
    }
    else
    {
        *p_ir_addr = 0;
    }
} /* End of function d1_ir_set() */

/***********************************************************************
 * Function Name: d1_ipr_set
 * Description  : Write the IPR register.
 * Arguments    : priority
 *                    Interrupt priority.
 *                vector
 *                    Interrupt vector number.
 * Return Value : none
 **********************************************************************/
static void d1_ipr_set(unsigned char priority, int vector)
{
    unsigned char *p_ipr_addr;

    /* The address offset from the address of the base register is cast to match the size of the register. */
    p_ipr_addr = ((unsigned char *)IPR_0_BASE) + vector;
    *p_ipr_addr = priority;
} /* End of function d1_ipr_set() */

/***********************************************************************
 * Function Name: d1_ipr_get
 * Description  : Read the IPR register.
 * Arguments    : vector
 *                    Interrupt vector number.
 * Return Value : Value of IPR register.
 **********************************************************************/
static unsigned char d1_ipr_get(int vector)
{
    unsigned char *p_ipr_addr;

    /* The address offset from the address of the base register is cast to match the size of the register. */
    p_ipr_addr = ((unsigned char *)IPR_0_BASE) + vector;

    return (*p_ipr_addr);
} /* End of function d1_ipr_get() */

/***********************************************************************
 * Function Name: d1_ien_set
 * Description  : Write the IER register.
 * Arguments    : enable
 *                    Enable or disable the register bit.
 *                vector
 *                    Interrupt vector number.
 * Return Value : none
 **********************************************************************/
static void d1_ien_set(bool enable, int vector)
{
    unsigned char *p_ien_addr;
    unsigned char tmp_ier;
    unsigned char tmp_ien;

    tmp_ier = vector / 8;
    tmp_ien = vector % 8;

    /* The address offset from the address of the base register is cast to match the size of the register. */
    p_ien_addr = ((unsigned char *)IEN_0_BASE) + tmp_ier;

    if (true == enable)
    {
        *p_ien_addr = ((*p_ien_addr) | (1 << tmp_ien));
    }
    else
    {
        *p_ien_addr = ((*p_ien_addr) & (~(1 << tmp_ien)));
    }
} /* End of function d1_ien_set() */

/***********************************************************************
 * Function Name: d1_genal1_set
 * Description  : Write the GENAL1 register.
 * Arguments    : enable
 *                    Enable or disable the register bit.
 *                grp_num
 *                    The register bit position.
 * Return Value : none
 **********************************************************************/
static void d1_genal1_set(bool enable, int grp_num)
{
    unsigned long *p_genal1_addr;

    /* The address of the base register is cast to match the size of the register. */
    p_genal1_addr = ((unsigned long *)GENAL1_0_BASE);

    if (true == enable)
    {
        *p_genal1_addr = ((*p_genal1_addr) | (1 << grp_num));
    }
    else
    {
        *p_genal1_addr = ((*p_genal1_addr) & (~(1 << grp_num)));
    }
} /* End of function d1_genal1_set() */

/***********************************************************************
 * Function Name: d1_genal1_get
 * Description  : Read the GENAL1 register.
 * Arguments    : none
 * Return Value : Value of GENAL1 register.
 **********************************************************************/
static unsigned long d1_genal1_get()
{
    unsigned long *p_genal1_addr;

    /* The address of the base register is cast to match the size of the register. */
    p_genal1_addr = ((unsigned long *)GENAL1_0_BASE);

    return (*p_genal1_addr);
} /* End of function d1_genal1_get() */

/***********************************************************************
 * Function Name: d1_grpal1_get
 * Description  : Read the GRPAL1 register.
 * Arguments    : none
 * Return Value : Value of GRPAL1 register.
 **********************************************************************/
static unsigned long d1_grpal1_get()
{
    unsigned long *p_grpal1_addr;

    /* The address of the base register is cast to match the size of the register. */
    p_grpal1_addr = ((unsigned long *)GRPAL1_0_BASE);

	return (*p_grpal1_addr);
} /* End of function d1_grpal1_get() */

