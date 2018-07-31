

drw_2d
=========

Overview
--------
DRW2D Driver for RX.

Release history
----------------
DD.MM.YYYY Version Description
26.03.2018 1.02    First release.

File Structure
--------------
drw_2d
+---ReadMe.txt
|
+---doc (TES's DRW2D documents)
|
+---inc
|    +-- dave_driver.h (TES's driver version 3.17)
+---src
     +-- rx (Source code depending on RX)
     |
     +-- tes (TES's driver source code)

Limitation
----------
¥This driver does not support big endian.

Usage Note
----------
¥Making program changes when the same group interrupt is used by DRW2D and another peripheral device.

 When the same group interrupt is used by DRW2D and another peripheral device, it is 
 necessary to make changes to the DRW2D program. The procedure for making program changes 
 using the BSP for the peripheral device (for example, GLCDC) that uses the same group
 interrupts as the DRW2D is described below.

 1) Comment out the DRW2D Excep_ICU_GROUPAL1 function (near line 300 of dave_base_rx.c). 
    /* <<< comment out start >>>
    #pragma interrupt Excep_ICU_GROUPAL1(vect=113)
    static void Excep_ICU_GROUPAL1(void)
    {
        unsigned long isflag;

        isflag = d1_grpal1_get();

        if (0x00000800UL == isflag)
        {
            drw_int_isr();
        }
    }
    <<< comment out end >>> */

 2) For functions created by the user, use the BSP API to register the interrupt handler
    for DRW2D. 
    /* Add an include statement for platform.h. */
    #include "platform.h"

    /* Add an extern declaration for the DRW2D interrupt handler to the registered function. */
    extern void drw_int_isr(void);

    user_function()
    {
        bsp_int_ctrl_t grpal1;

        /* Specify the priority of the group interrupt. */
        grpal1.ipl = 7;

        /* Use the BSP API to register the interrupt handler for DRW2D. */
        R_BSP_InterruptWrite(BSP_INT_SRC_AL1_DRW2D_DRW_IRQ, (bsp_int_cb_t)drw_int_isr);

        /* Use the BSP API to enable the group interrupt. */
        R_BSP_InterruptControl(BSP_INT_SRC_AL1_DRW2D_DRW_IRQ, BSP_INT_CMD_GROUP_INTERRUPT_ENABLE, (void *)&group_priority);
        ¥
        ¥
        ¥
    }


 3) In the DRW2D program, set the group interrupt priority based on the define macro 
    below (near line 26 of dave_irq_rx.c).

    If it is necessary to adjust the priority of the group interrupt, change the value of
    the define macro below. (The setting range is 0 to 15, with 0 specifying interrupt 
    disabled.)

    Note that the group interrupt has the same priority for the other peripheral device 
    using the same group interrupt as DRW2D.

    #define DAVE_IRQ_IPR     (7)

 Note: For details of BSP APIs, refer to the BSP application note (R01AN1685).

END OF DOCUMENT