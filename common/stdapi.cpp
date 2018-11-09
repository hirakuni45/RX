//=====================================================================//
/*!	@file
	@brief	stdc++ ライブラリの補助 @n
			libsupc++ ランタイムが最低限必要な関数、定義など
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw_app/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdlib>

namespace std {

    void __throw_bad_function_call()
    {
        abort();
    }

}
