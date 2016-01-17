//=====================================================================//
/*! @file
    @brief  RX 起動前、初期化
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
int main(int argc, char**argv);

extern int _preinit_array_start;
extern int _preinit_array_end;
extern int _init_array_start;
extern int _init_array_end;
extern int _fini_array_start;
extern int _fini_array_end;

extern void rx_run_init_array(void);
extern void rx_run_fini_array(void);
extern void rx_run_preinit_array(void);

extern void (*interrupt_vectors[256])(void);

extern void null_task_(void);

int init(void)
{
	// 割り込みベクターテーブルの初期化
	for(int i = 0; i < 256; ++i) {
		interrupt_vectors[i] = null_task_;
	}

	rx_run_fini_array();
	rx_run_init_array();

	// main の起動
	static int argc = 0;
	static char **argv = 0;
	int ret = main(argc, argv);

	rx_run_preinit_array();

	return ret;
}

// EOF
