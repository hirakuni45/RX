//=========================================================================//
/*! @file
    @brief  ハードウェアー OFS 設定 @n
			RX63[1N], RX64M, RX71M, RX65N @n
			オプション機能選択レジスタのアドレスは、リンカーファイルに記述してある。 @n
			通常マイコンによりアドレスは異なる。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <stdint.h>
#include "common/byte_order.h"

// オプション機能選択レジスタ 0（OFS0）
// #define SECT_SPCC __attribute__ ((section (".spcc")))
// #define SECT_OSIC __attribute__ ((section (".osic")))
#define SECT_OFS0 __attribute__ ((section (".ofs0")))
#define SECT_OFS1 __attribute__ ((section (".ofs1")))

// オプション機能選択レジスタ 1（OFS1）
// b1-b0: VDSEL[1:0]        電圧検出0レベル選択ビット
//                          00: 予約
//                          01: 2.94V を選択
//                          10: 2.87V を選択
//                          11: 2.80V を選択
// b2   : LVDAS             電圧検出0回路起動ビット
//                          0:  リセット後、電圧監視0リセット有効
//                          1:  リセット後、電圧監視0リセット無効
// b8   : HOCOEN            HOCO発振有効ビット
//                          0:  リセット後、HOCO発振が有効
//                          1:  リセット後、HOCO発振が無効
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72N) || defined(SIG_RX72M)
const uint32_t OFS1_value SECT_OFS1 = 0xfffffff9;  // 2.97V, LVDAS 有効
#elif defined(SIG_RX631) || defined(SIG_RX63N)
const uint32_t OFS1_value SECT_OFS1 = 0xfffffffB;  // LVDAS 有効
#endif

#if 0
const unsigned long __SPCCreg SECT_SPCC = 0xffffffff;

// OSIC register (ID codes)
const unsigned long __OSISreg[4] OSIC = {
        0xffffffff,
        0xffffffff,
        0xffffffff,
        0xffffffff,
};

// MDE register (Single Chip Mode)
#ifdef BIG_ENDIAN
    const unsigned long __MDEreg OFS_REG = 0xfffffff8;    // big
#endif
#ifdef LITTLE_ENDIAN
    const unsigned long __MDEreg OFS_REG = 0xffffffff;    // little
#endif

// OFS0 register
const unsigned long __OFS0reg OFS_REG = 0xffffffff;

// OFS1 register
const unsigned long __OFS1reg OFS_REG = 0xffffffff;
#endif
