#pragma once
//=====================================================================//
/*! @file
    @brief  デバイス定義
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#if defined (_RX63T_)
#  include <rx63x/rx63x_defs.hpp>
#elif defined (_RX621_)
#  include <rx62x/rx62x_defs.hpp>
#else
#  error "device type not defined"
#endif
