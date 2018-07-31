//--------------------------------------------------------------------------
// Project: D/AVE
// File:    dave_base_rx.h (%version: 4 %)
//          created Mon Aug 22 12:50:45 2005 by hh04027
//
// Description:
//  %date_modified: Wed Apr 18 15:42:41 2007 %  (%derived_by:  hh74040 %)
//
// Changes:
//  2005-04-12 CSe  fully implemented missing d1 driver functionality
//  2018-03-26      added support for RX
//
//--------------------------------------------------------------------------

#ifndef __1_dave_base_rx_h_H
#define __1_dave_base_rx_h_H

#define PRCR_KEY                (0xA500)       /* PRC Key Code            */
#define PRCR_PRC1               (0x0002)       /* PRCR bit 1 position     */
#define MSTP_C                  (2)            /* MSTPC offset position   */
#define DAVE2D_MSTP_NUM         (28)           /* DRW2D bit in MSTPC      */

#define PRCR_0_BASE             (0x000803FEUL) /* PRCR base address       */
#define MSTP_0_BASE             (0x00080010UL) /* MSTP base address       */
#define DAVE2D_0_BASE           (0x000E3000UL) /* DAVE2D base address     */
#define IR_0_BASE               (0x00087000UL) /* IR base address         */
#define IEN_0_BASE              (0x00087200UL) /* IER base address        */
#define IPR_0_BASE              (0x00087300UL) /* IPR base address        */
#define GRPAL1_0_BASE           (0x00087834UL) /* GRPAL1 base address     */
#define GENAL1_0_BASE           (0x00087874UL) /* GENAL1 base address     */

#define RX_USE_DLIST_INDIRECT   (1)

//--------------------------------------------------------------------------
//
#define WRITE_REG( BASE, OFFSET, DATA ) \
        (((unsigned long *)(BASE))[OFFSET] = DATA)

#define READ_REG( BASE, OFFSET ) \
        (((unsigned long *)(BASE))[OFFSET])

#define INTERNAL_NOT_USED(p)    ((void)(p))
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

typedef struct _d1_device_rx
{
    volatile long *dlist_start; /* dlist start addresses */
    int dlist_indirect;
} d1_device_rx;

//---------------------------------------------------------------------------

extern int d1_initirq_intern(d1_device_rx *handle);
extern int d1_shutdownirq_intern(d1_device_rx *handle);

//---------------------------------------------------------------------------

#define D2_DLISTSTART   (50)                   /* DLISTST register offset  */

#endif
