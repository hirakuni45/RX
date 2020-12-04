Renesas RX マイコン FreeRTOS (V202011.00)
=========

[Japanese](READMEja.md)

## 概要

Amazon FreeRTOS の カーネルを RX マイコン用にポーティングしたコード、本体です。   
   
RX24T 用のプロジェクトがありますが、RX24T の内蔵メモリは少なく、実際に利用する場合は、注意して下さい。
※FreeRTOSConfig.h で、ヒープサイズに注意して下さい。

```
#if defined(SIG_RX24T)
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 10 * 1024 ) )
#else
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 45 * 1024 ) )
#endif
```
   
オリジナルのコードは、ルネサス社純正コンパイラやフレームワーク向けになっています。
その為、それらの関係コードをカーネルソースから追い出して、最低限の修正をしています。   
   
---
## プロジェクト・リスト

- FreeRTOSConfig.h
- main.cpp
- READMEja.md
- README.md
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX66T/Makefile
- RX65N/Makefile
- RX72N/Makefile
   
---
## カーネル修正箇所

Source/portable/GCC/RX600/port.c
Source/portable/GCC/RX600v2/port.c
Source/portable/GCC/RX700v2/port.c

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

- 「vApplicationSetupTimerInterrupt();」内で、ソフトウェアー割り込みの設定を行います。
- なので、SWINT 関係の設定をコメントアウトしています。
- SWINT 関係のリソースにアクセスしないので、「iodefine.h」のインクルードが必要ありません。

```
    void vApplicationSetupTimerInterrupt(void)
    {
        uint8_t intr = configKERNEL_INTERRUPT_PRIORITY;
        cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

        device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
        device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, configKERNEL_INTERRUPT_PRIORITY);
    }
```

アプリケーション内で、タイマー関係（CMT）の設定を終えた後に、SWINT 関係の設定を行っています。

---
## CPU クロック設定

FreeRTOSConfig.h 内で、CPU クロックの設定がありますが、以下のように、変更してあります。
※Makefile で設定するクロック周波数に依存するようにしています。   

```
#define configCPU_CLOCK_HZ             ( F_ICLK )
#define configPERIPHERAL_CLOCK_HZ      ( F_PCLKB )
```

## ライセンス

MIT

