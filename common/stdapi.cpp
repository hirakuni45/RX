//=====================================================================//
/*!	@file
	@brief	stdc++ ライブラリの補助 @n
			libsupc++ ランタイムが最低限必要な関数、定義など
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw_app/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdlib>

extern "C" {
	void sci_puts(const char *) __attribute__((weak));
	void sci_puts(const char *) { }

	void kill(int pid, int sig) __attribute__((weak));
	void kill(int pid, int sig) { }
	int getpid() __attribute__((weak));
	int getpid() { return 1; }
}

namespace std {

    void __throw_bad_function_call()
    {
		sci_puts("bad_function_call\n");
        abort();
    }

	void __throw_bad_alloc()
	{
		sci_puts("bad_alloc\n");
		abort();
	}

	void __throw_logic_error(char const* e)
	{
		sci_puts("logic_error\n");
        abort();
	}

#if 0
void __throw_length_error(char const* e)
	{
		Serial.print("Length Error :");
		Serial.println(e);
	}
#endif
}
