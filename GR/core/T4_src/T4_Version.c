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
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : T4_Version.c
* Version      : 1.0
* Description  : middleware version information definition
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.07.2012 1.00     First Release
***********************************************************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#include "t4define.h"
#endif
#include "r_stdint.h"
#include "r_mw_version.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define __COMPLIER_VER_UNDEFINED__ 0xFFFFFFFF
#define __T4_VERSION__ "2.02"

#if defined (GRSAKURA)
#define __TARGET_CPU__ "RX600 LITTLE endian"
#define __COMPILER_VER__ __COMPLIER_VER_UNDEFINED__
#elif (defined (__RXV2) && defined (__BIG))
#define __TARGET_CPU__ "RXV2 BIG endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (__RXV2) && defined (__LIT))
#define __TARGET_CPU__ "RXV2 LITTLE endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (__RXV1) && defined (__BIG))
#define __TARGET_CPU__ "RXV1 BIG endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (__RXV1) && defined (__LIT))
#define __TARGET_CPU__ "RXV1 LITTLE endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (__RX600) && defined (__BIG))
#define __TARGET_CPU__ "RX600 BIG endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (__RX600) && defined (__LIT))
#define __TARGET_CPU__ "RX600 LITTLE endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (__RX200) && defined (__BIG))
#define __TARGET_CPU__ "RX200 BIG endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (__RX200) && defined (__LIT))
#define __TARGET_CPU__ "RX200 LITTLE endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (_SH4A) && defined(_BIG))
#define __TARGET_CPU__ "SH-4A BIG endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (_SH4A) && defined(_LIT))
#define __TARGET_CPU__ "SH-4A LITTLE endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif defined (_SH2AFPU)
#define __TARGET_CPU__ "SH2A-FPU"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif defined (_SH2A)
#define __TARGET_CPU__ "SH-2A"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (_SH2) && defined(_BIG))
#define __TARGET_CPU__ "SH-2 BIG endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif (defined (_SH2) && defined(_LIT))
#define __TARGET_CPU__ "SH-2 LITTLE endian"
#define __COMPILER_VER__ __RENESAS_VERSION__
#elif defined (__v850) && (__v850e2v3)
#define __TARGET_CPU__ "V850E2V3"
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (__v850) && (__v850e2)
#define __TARGET_CPU__ "V850E2"
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (__v850) && (__v850e)
#define __TARGET_CPU__ "V850E"
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (__v850)
#define __TARGET_CPU__ "V850"
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (__K0__)
#define __TARGET_CPU__ "78K0"
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (__K0R__)
#if defined (__RL78__)
#if defined (__K0R_SMALL__)
#define __MEMORY_MODEL__ "SMALL"
#elif defined (__K0R_MEDIUM__)
#define __MEMORY_MODEL__ "MEDIUM"
#elif defined (__K0R_LARGE__)
#define __MEMORY_MODEL__ "LARGE"
#else
#error "Undefined memory model."
#endif
#define __TARGET_CPU__ "RL78 ("__MEMORY_MODEL__")"
#else
#define __TARGET_CPU__ "78K0R"
#endif
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (__ICCRL78__)
#if __CORE__==__RL78_1__
#define __CORE_NAME__ "core 1"
#else
#define __CORE_NAME__ "core 2"
#endif
#if __CODE_MODEL__==__CODE_MODEL_NEAR__
#define __CODE_MODEL_NAME__ "code_model=near"
#else
#define __CODE_MODEL_NAME__ "code_model=far"
#endif
#if __DATA_MODEL__==__DATA_MODEL_NEAR__
#define __DATA_MODEL_NAME__ "data_model=near"
#else
#define __DATA_MODEL_NAME__ "data_model=far"
#endif
#define __TARGET_CPU__ "RL78 (IAR, "__CORE_NAME__", "__CODE_MODEL_NAME__", "__DATA_MODEL_NAME__")"
#define __COMPILER_VER__   __VER__
#elif defined (M16C) && defined(__R8C__)
#define __TARGET_CPU__ "R8C"
#ifdef __RENESAS_VERSION__
#define __COMPILER_VER__ __RENESAS_VERSION__
#else
#define __COMPILER_VER__ __COMPLIER_VER_UNDEFINED__
#endif
#elif defined (M16C) && !defined(__R8C__)
#define __TARGET_CPU__ "M16C"
#ifdef __RENESAS_VERSION__
#define __COMPILER_VER__ __RENESAS_VERSION__
#else
#define __COMPILER_VER__ __COMPLIER_VER_UNDEFINED__
#endif
#elif defined (M32C80)
#define __TARGET_CPU__ "M32C/80"
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (R32C100)
#define __TARGET_CPU__ "R32C/100"
#define __COMPILER_VER__   __COMPLIER_VER_UNDEFINED__
#elif defined (__H8__) && defined(__2600A__)
#define __TARGET_CPU__ "H8S/2600 Advanced mode"
#define __COMPILER_VER__ __RENESAS_VERSION__
#else
#error "None-support combination of CPU and endian"
#endif

#if defined(_ETHER)
#define __DATA_LINK__ "Ethernet"
#elif defined(_PPP)
#define __DATA_LINK__ "PPP"
#endif

const mw_version_t R_t4_version =
{
    __COMPILER_VER__ ,
    "M3S-T4-Tiny("__DATA_LINK__") version "__T4_VERSION__" for "__TARGET_CPU__".("__DATE__", "__TIME__")\n"
};
