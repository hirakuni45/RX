#ifndef SYSCALLS_H
#define SYSCALLS_H
//=====================================================================//
/*!	@file
	@brief	標準ライブラリーハード依存「syscalls」モジュール
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <time.h>
#include "sh72620_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/// stdin、stdout シリアル・ボーレート
#define STDIO_SIO_BAUD		115200

/// stdin, stdout シリアル・チャネル
#define STDIO_SIO_CHANEL	2

/// External I/O Processor シリアル・ボーレート
#define IOP_SIO_BAUD		96000

/// External I/O Processor シリアル・チャネル
#define IOP_SIO_CHANEL		3


typedef struct {
	unsigned short adc_value[8];
} ADC_UNIT;

//-----------------------------------------------------------------//
/*!
	@brief	syscall 関係の初期化
*/
//-----------------------------------------------------------------//
void init_syscalls(void);


//-----------------------------------------------------------------//
/*!
	@brief	syscalls のサービスルーチン@n
	        毎フレーム程度呼び出す事
	@return 時間をサブプロセッサーからロードしたら「０」以外
*/
//-----------------------------------------------------------------//
int service_syscalls(void);


//-----------------------------------------------------------------//
/*!
	@brief	システム時間を設定
	@param[in]	t	設定時刻（time_t）
*/
//-----------------------------------------------------------------//
void set_system_time(time_t t);


//-----------------------------------------------------------------//
/*!
	@brief	システム時間を得る
	@return	現在の時刻（time_t）
*/
//-----------------------------------------------------------------//
time_t get_system_time(void);


//-----------------------------------------------------------------//
/*!
	@brief	I/O プロセッサの A/D 変換値を受け取る
	@param[in]	chanel	A/D のチャネル（０～７）
	@return	0 ～ 4095 の A/D 値
*/
//-----------------------------------------------------------------//
unsigned short get_adc_value(int chanel);



//-----------------------------------------------------------------//
/*!
	@brief	ディレクトリを作成する
	@param[in]	pathname	ディレクトリ名
	@return	成功した場合「０」、失敗したら「-1」
*/
//-----------------------------------------------------------------//
int mkdir(const char *pathname, mode_t mode);


#ifdef __cplusplus
}
#endif

#endif
