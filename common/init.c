//=====================================================================//
/*! @file
    @brief  RX 起動前、初期化
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
int main(int argc, char**argv);

extern void rx_run_fini_array(void);
extern void rx_run_preinit_array(void);
extern void rx_run_init_array(void);

extern void init_interrupt(void);

void init(void)
{
	// setup interrupt vector
	init_interrupt();

	// C++ static constractor
	rx_run_preinit_array();
	rx_run_init_array();
	rx_run_fini_array();

	// main の起動
	static int argc = 0;
	static char **argv = 0;
	int ret = main(argc, argv);

	// メイン関数の「return」
	while(1) ;
}

