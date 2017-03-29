//=====================================================================//
/*! @file
    @brief  RX 起動前、初期化 @n
			Copyright 2016, 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
int main(int argc, char**argv);

extern void rx_run_fini_array(void);
extern void rx_run_preinit_array(void);
extern void rx_run_init_array(void);

extern void init_interrupt(void);

extern void set_intr_level(int);

extern void null_task_(void);

int init(void)
{
	init_interrupt();

	// C++ constractor
	rx_run_fini_array();
	rx_run_preinit_array();
	rx_run_init_array();

	set_intr_level(15);

	// main の起動
	static int argc = 0;
	static char **argv = 0;
	int ret = main(argc, argv);

	return ret;
}

// EOF
