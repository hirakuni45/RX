
Renesas RX microcontroller FreeRTOS kernel (V202011.00)
=========

<img src="../docs/Logo_freeRTOS.png" width="50%">

[Japanese](READMEja.md)

## Overview

Code porting the Amazon FreeRTOS kernel for RX microcomputers, the body of the kernel and modified code.      
   
The original code is aimed at the genuine Renesas compiler CC-RX/GNU-RX and frameworks.   
The original code is for the genuine Renesas compilers CC-RX/GNU-RX and frameworks, so we have removed the related code from the kernel source to reduce the dependency of the development environment.   

The code is basically for gcc.   

---

## About the RX24T heap size

There is a project for the RX24T, but be aware that the RX24T's internal memory is small, so be careful when using it in practice.   
The size can be changed in the RX24T/Makefile's environment variable settings.   
　　　
```
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( RTOS_HEAP_SIZE * 1024 ) )
``` 
   
This setting is valid if you use the memory model "Source/portable/MemMang/heap_1.c".   

Other microcontrollers use malloc/free memory allocation, so memory is allocated dynamically.   

---

## Project List


- FreeRTOSConfig.h
- main.cpp
- READMEja.md
- README.md
- Source (FreeRTOS Kernel)
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX66T/Makefile
- RX65N/Makefile
- RX72N/Makefile
   
---

## Kernel Modifiers

### port.c

- Source/portable/GCC/RX600/port.c
- Source/portable/GCC/RX600v2/port.c
- Source/portable/GCC/RX700v3_DPFPU/port.c

```
/* Hardware specifics. */
#if ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    #include "platform.h"

#else /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

///    #include "iodefine.h"

#endif /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

...

BaseType_t xPortStartScheduler( void )
{
    extern void vApplicationSetupTimerInterrupt( void );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    if( pxCurrentTCB != NULL )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        vApplicationSetupTimerInterrupt();

        /* Enable the software interrupt. */
///        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
///        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
///        _IPR( _ICU_SWINT ) = configKERNEL_INTERRUPT_PRIORITY;

        /* Start the first task. */
        prvStartFirstTask();
    }

    /* Should not get here. */
    return pdFAIL;
}
```

- In "vApplicationSetupTimerInterrupt();", we also set up the software interrupt.
- So, we comment out the SWINT-related settings.
- We don't need to include the "iodefine.h" because we don't access the SWINT-related resources.
- In the application, after the timer-related (CMT) settings are finished, the SWINT-related settings are done.

```
    void vApplicationSetupTimerInterrupt(void)
    {
        uint8_t intr = configKERNEL_INTERRUPT_PRIORITY;
        cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

        device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
        device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, configKERNEL_INTERRUPT_PRIORITY);
    }
```

---

### portmacro.h

- Source/portable/GCC/RX600/portmacro.h
- Source/portable/GCC/RX600v2/portmacro.h
- Source/portable/GCC/RX700v3_DPFPU/portmacro.h

```
#define portYIELD()                         \
    __asm volatile                          \
    (                                       \
        "PUSH.L R10                 \n"     \
        "MOV.L  #0x872E0, R10       \n"     \
        "MOV.B  #0x1, [R10]         \n"     \
        "MOV.L  [R10], R10          \n"     \
        "POP    R10                 \n"     \
    )

```
Previously, I used "CMP [R10].UB, R10" because "MOV.L [R10], R10" was strange.   However
But the original code is prioritized and restored.   
I think this 32-bit transfer is a bad idea because it violates the precautions in the hardware manual.   
It may be a structural problem with the RX microcomputer, so it may make sense to do so.   
I've asked this question before, but I haven't gotten a clear answer as to why it's happening.   
   
---
   
## CPU Clock Settings

In FreeRTOSConfig.h, there is a CPU clock setting, There are changes, as follows   
It depends on the clock frequency set by Makefile.   
By this modification, even different CPUs can share the source code by giving the compile time constant.    
   
```
#define configCPU_CLOCK_HZ             ( F_ICLK )
#define configPERIPHERAL_CLOCK_HZ      ( F_PCLKB )
```

---

## Sample Programs

- In the sample, it outputs a string over a serial connection.
- Different microcontrollers use different channels, so check the settings in main.cpp.
- The sample program creates and launches three tasks.
- Task1 outputs a count value every 500 milliseconds
- Task2 outputs a count every 100 milliseconds
- Task3 outputs a count every 1000 milliseconds

The FrrRTOS uses a timer interrupt CMT as a hardware resource.

In this example, we have assigned CMT0.

```
    typedef device::cmt_mgr<device::CMT0> CMT;
    CMT         cmt_;
```

The setting is done in the "vApplicationSetupTimerInterrupt" function called from FreeRTOS.   
It is a timer interrupt of 1000 Hz (1 ms).   

---

## License

hirakuni45 RX C++ framework: MIT

FreeRTOS: MIT
