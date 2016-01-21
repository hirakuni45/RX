#pragma once
//=====================================================================//
/*!	@file
	@brief	RX チップ選択ヘッダー @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#if defined(CHIP_RX621) | defined(CHIP_RX62N) | defined(CHIP_RX62G) | defined(CHIP_RX63T) | defined(CHIP_RX630)
#ifdef CHIP_RX621
#include "RX621/system.hpp"
#include "RX621/sci.hpp"
#include "RX621/icu.hpp"
#endif

#ifdef CHIP_RX62N
#endif

#ifdef CHIP_RX62G
#endif

#ifdef CHIP_RX63T
#include "RX63T/system.hpp"
#include "RX63T/sci.hpp"
#include "RX63T/icu.hpp"
#endif

#ifdef CHIP_RX630
#endif

#else
#  error "Requires CHIP_XXXXX to be defined"
#endif
