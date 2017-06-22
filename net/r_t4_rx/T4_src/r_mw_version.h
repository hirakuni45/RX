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
* Copyright (C) 2012-2016 Renesas Electronics Corporation, All Rights Reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_mw_version.h
* Version      : 1.01
* Description  : Renesas Middleware library version information header file
* Website      : https://www.renesas.com/mw/t4
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 28.08.2012 1.00    First Release
*         : 30.11.2016 1.01    File Header maintenance
***********************************************************************************************************************/
#ifndef _R_MW_VERSION_H_
#define _R_MW_VERSION_H_

/**********************************************************************************
Macro Defines
***********************************************************************************/
/* Middleware version charactor size */
#define __VER_STIRNG_MAX__ 128

/**********************************************************************************
Type Defines
***********************************************************************************/
/* Middleware version information structure*/
typedef struct mw_version_tag
{
    uint32_t complier;
    uint8_t  library[__VER_STIRNG_MAX__];
}mw_version_t;

#endif /* _R_MW_VERSION_H_ */
