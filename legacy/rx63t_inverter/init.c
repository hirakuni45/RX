//=====================================================================//
/*! @file
    @brief  RX 起動前、初期化
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
int main(int argc, char**argv);

extern int _datainternal;
extern int _datastart;
extern int _dataend;

extern int _bssstart;
extern int _bssend;

extern int _preinit_array_start;
extern int _preinit_array_end;
extern int _init_array_start;
extern int _init_array_end;

extern void (*interrupt_vectors[256])(void);

extern void null_task_(void);

int init(void)
{
	// 割り込みベクターテーブルの初期化
	for(int i = 0; i < 256; ++i) {
		interrupt_vectors[i] = null_task_;
	}

	// R/W-data セクションのコピー
	{
		int *src = &_datainternal;
		int *dst = &_datastart;
		while(dst < &_dataend) {
			*dst++ = *src++;
		}
	}

	// bss セクションのクリア
	{
		int *dst = &_bssstart;
		while(dst < &_bssend) {
			*dst++ = 0;
		}
	}

	// 静的コンストラクターの実行（C++ ）
	{
		int *p = &_preinit_array_start;
		while(p < &_preinit_array_end) {
			void (*prog)(void) = (void *)*p++;
			(*prog)();
		}
	}
	{
		int *p = &_init_array_start;
		while(p < &_init_array_end) {
			void (*prog)(void) = (void *)*p++;
			(*prog)();
		}
	}

	// main の起動
	static int argc = 0;
	static char **argv = 0;
	int ret = main(argc, argv);

	return ret;
}

void __dso_handle(void)
{

}

// EOF
