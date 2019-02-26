//=====================================================================//
/*!	@file
	@brief	標準ライブラリーハード依存「syscalls」モジュール @n
			通常は libc.a にアーカイブされているモジュールを @n
			置き換える。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2015, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void sci_putch(char ch) __attribute__((weak));
void sci_putch(char ch) { }
char sci_getch(void) __attribute__((weak));
char sci_getch(void) { return 0; }

void utf8_to_sjis(const char* src, char* dst, uint32_t dsz);

// FatFS を使う場合有効にする（通常 Makefile で定義）
// #define FAT_FS

// ファイル・システム関係のログギングを有効にする場合（通常 Makefile で定義）
// #define LOGGING_FS

#ifdef LOGGING_FS
unsigned long millis(void) __attribute__((weak));
unsigned long millis(void) { return 0; }
#endif

#ifdef FAT_FS
#include "ff12b/src/diskio.h"
#include "ff12b/src/ff.h"

int fatfs_get_mount(void) __attribute__((weak));
int fatfs_get_mount(void) { return 1; }

// stdin, stdout, stderr のオフセット
#define STD_OFS_ (3)

// 同時にオープンできる標準的な数（３）
#if defined(FAT_FS_NUM)
#define OPEN_MAX_ (STD_OFS_ + FAT_FS_NUM)
#else
#define OPEN_MAX_ (STD_OFS_ + 3)
#endif

static FIL file_obj_[OPEN_MAX_ - STD_OFS_];
static char fd_pads_[OPEN_MAX_];

#endif

// システムコール関係のデバッグ用
// #define SYSCALLS_DEBUG
// read 関数の詳細デバッグ
// #define SYSCALLS_READ_DEBUG

#ifdef SYSCALLS_DEBUG
static char debug_tmp_[256];
#endif

#ifdef LOGGING_FS
uint32_t fs_open_w_max = 0;
uint32_t fs_open_w_cnt = 0;
uint32_t fs_open_r_max = 0;
uint32_t fs_open_r_cnt = 0;
uint32_t fs_close_max = 0;
uint32_t fs_close_cnt = 0;
#endif

//-----------------------------------------------------------------//
/*!
	@brief	読取りまたは書込み用にファイルをオープンする、または作成する @n
		   	予約、stdin: 0, stdout: 1, stderr: 2
	@param[in]	path	ファイル名
	@param[in]	flags	オープン・モード
	@return		正常に完了すると、ファイル記述子である負でない整数 @n
	            を返します。@n
				処理に失敗すると -1 が返され、エラーを示すために @n
				errno が設定されます。
*/
//-----------------------------------------------------------------//
int open(const char *path, int flags, ...)
{
#ifdef LOGGING_FS
	uint32_t orgt = millis();
#endif

	if(path == NULL) {
		errno = EFAULT;
		return -1;
	}

	int file = -1;
#ifdef FAT_FS
	if(fatfs_get_mount() == 0) {
#ifdef SYSCALLS_DEBUG
		sprintf(debug_tmp_, "syscalls: open mount(%d)\n", fatfs_get_mount());
		sci_puts(debug_tmp_);
#endif
		errno = EFAULT;
		return -1;
	}

	for(int i = 3; i < OPEN_MAX_; ++i) {
		if(fd_pads_[i] == 0) {
			file = i;
			break;
		}
	}
	if(file < 0) {
		errno = ENFILE;
		return -1;
	}

//	printf("flags: %08X\n", flags);

	BYTE mode = 0;
	int rwm = flags & O_ACCMODE;
	if(rwm == O_RDONLY) mode = FA_READ | FA_OPEN_EXISTING;
	else if(rwm == O_WRONLY) mode = FA_WRITE;
	else if(rwm == O_RDWR) mode = FA_READ | FA_WRITE;

	if(flags & O_APPEND) mode |= FA_OPEN_APPEND;

	if(flags & O_TRUNC) mode |= FA_CREATE_ALWAYS;
	else if(flags & O_CREAT) mode |= FA_CREATE_NEW;

#if _USE_LFN != 0
	char tmp[_MAX_LFN + 1];
	utf8_to_sjis(path, tmp, sizeof(tmp));
	FRESULT res = f_open(&file_obj_[file - STD_OFS_], tmp, mode);
#else
	FRESULT res = f_open(&file_obj_[file - STD_OFS_], path, mode);
#endif
	if(res == FR_OK) {
		fd_pads_[file] = 1;
		errno = 0;
#ifdef SYSCALLS_DEBUG
		sprintf(debug_tmp_, "syscalls: open ok.(%d): '%s' at 0x%08X\n", file, path, mode);
		sci_puts(debug_tmp_);
#endif
	} else {
#ifdef SYSCALLS_DEBUG
		sprintf(debug_tmp_, "(%d)f_open error: (%d) at 0x%08X\n", file, (int)res, mode);
		sci_puts(debug_tmp_);
#endif
		errno = EIO;
		file = -1;
	}
#endif

#ifdef LOGGING_FS
	uint32_t t = millis() - orgt;
	if(mode & FA_WRITE) {
		if(fs_open_w_max < t) fs_open_w_max = t;
		++fs_open_w_cnt;
	} else {
		if(fs_open_r_max < t) fs_open_r_max = t;
		++fs_open_r_cnt;
	}
#endif

	return file;
}


//-----------------------------------------------------------------//
/*!
	@brief	ファイル記述子で指定されたファイルから指定バイトを読む
	@param[in]	file	ファイル記述子
	@param[in]	ptr		読み込み先
	@param[in]	len		読み込みバイト数
	@return		読み込みバイト数
*/
//-----------------------------------------------------------------//
_READ_WRITE_RETURN_TYPE read(int file, void *ptr, size_t len)
{
	if(ptr == NULL) return 0;

	_READ_WRITE_RETURN_TYPE l = 0;
	if(file >= 0 && file <= 2) {
		// stdin
		if(file == STDIN_FILENO) {
			char *p = ptr;
			for(int i = 0; i < len; ++i) {
				char ch = sci_getch();
				sci_putch(ch);  // エコーバック
				// 改行コードを変換する
				if(ch == '\r') ch = '\n';
				*p++ = ch;
			}
			errno = 0;
			l = len;
		}
	}
#ifdef FAT_FS
	else if(file < OPEN_MAX_) {
		if(fatfs_get_mount() != 0 && fd_pads_[file] != 0) {
			UINT rl;
			FRESULT res;
#ifdef SYSCALLS_READ_DEBUG
			sprintf(debug_tmp_, "syscalls: read(%d): request: %d at %08X\n", file, len, (int)ptr);
			sci_puts(debug_tmp_);
#endif
			res = f_read(&file_obj_[file - STD_OFS_], ptr, len, &rl);
			if(res == FR_OK) {
#ifdef SYSCALLS_READ_DEBUG
				sprintf(debug_tmp_, "syscalls: read(%d): bytes: %d->%d\n", file, len, rl);
				sci_puts(debug_tmp_);
#endif
				errno = 0;
				l = (int)rl;
			} else {
#ifdef SYSCALLS_DEBUG
				sprintf(debug_tmp_, "syscalls: read(%d) error: %x\n", file, (int)res);
				sci_puts(debug_tmp_);
#endif
				errno = EIO;
				l = -1;
			}
		} else {
			errno = EBADF;
			l = -1;
		}
	} else {
		errno = EBADF;
		l = -1;
	}
#endif
	return l;
}


//-----------------------------------------------------------------//
/*!
	@brief	ファイル記述子で指定されたファイルから指定バイトを書く
	@param[in]	file	ファイル記述子
	@param[in]	ptr		書き込み元
	@param[in]	len		書き込みバイト数
	@return		書き込みバイト数
*/
//-----------------------------------------------------------------//
_READ_WRITE_RETURN_TYPE write(int file, const void *ptr, size_t len)
{
	if(ptr == NULL) return 0;

	_READ_WRITE_RETURN_TYPE l = -1;
	if(file >= 0 && file <= 2) {
		if(file == 1 || file == 2) {
			const char *p = ptr;
			for(int i = 0; i < len; ++i) {
				char ch = *p++;
				sci_putch(ch);
			}
			l = len;
			errno = 0;
		}
	}
#ifdef FAT_FS
	else if(file < OPEN_MAX_) {
		if(fatfs_get_mount() != 0 && fd_pads_[file] != 0) {
			UINT rl;
			FRESULT res = f_write(&file_obj_[file - STD_OFS_], ptr, len, &rl);
			if(res == FR_OK) {
				errno = 0;
				l = (int)rl;
			} else {
#ifdef SYSCALLS_DEBUG
				sprintf(debug_tmp_, "(%d)write error: %x\n", file, (int)res);
				sci_puts(debug_tmp_);
#endif
				errno = EIO;
				l = -1;
			}
		} else {
			errno = EBADF;
			l = -1;
		}
	} else {
		errno = EBADF;
		l = -1;
	}
#endif
	return l;
}


//-----------------------------------------------------------------//
/*!
	@brief	ファイルの読み書きオフセットの位置を変える
	@param[in]	file	ファイル記述子
	@param[in]	offset	位置オフセット
	@param[in]	dir		方向タイプ
	@return		成功した場合、先頭からの位置で返す、失敗したら「-1」
*/
//-----------------------------------------------------------------//
off_t lseek(int file, off_t offset, int dir)
{
	int pos = -1;
	if(file >= 0 && file <= 2) {
		errno = 0;
		pos = 0;
	}
#ifdef FAT_FS
	else if(file < OPEN_MAX_) {
		if(fatfs_get_mount() != 0 && fd_pads_[file] != 0) {
			FRESULT res;
			DWORD ofs;
			FIL *fp;
			fp = &file_obj_[file - STD_OFS_];
			if(dir == SEEK_SET) {
				ofs = (DWORD)offset;
			} else if(dir == SEEK_CUR) {
				ofs = fp->fptr + (DWORD)offset;
			} else if(dir == SEEK_END) {
				ofs = f_size(fp) + (DWORD)offset;
			} else {
				errno = EINVAL;
				return -1;
			}
			if(ofs < 0 || ofs > f_size(fp)) {
				errno = EINVAL;
				return -1;
			}
			res = f_lseek(fp, ofs);
			if(res == FR_OK) {
				pos = fp->fptr;	// seek 後のファイル位置
				errno = 0;
			} else {
#ifdef SYSCALLS_DEBUG
				sprintf(debug_tmp_, "(%d)lseek error: %x\n", file, (int)res);
				sci_puts(debug_tmp_);
#endif
				errno = EIO;
			}
		} else {
			errno = EBADF;
		}
	} else {
		errno = EBADF;
	}
#endif
	return (off_t)pos;
}


//-----------------------------------------------------------------//
/*!
	@brief	ファイルの新しい名前を作成する@n
	        link API と厳密には違う動作だけど、内部的には rename
	@param[in]	oldpath	古いファイル名
	@param[in]	newpath	新しいファイル名
	@return		成功なら「０」を返す。
*/
//-----------------------------------------------------------------//
int link(const char *oldpath, const char *newpath)
{
#ifdef FAT_FS
	if(fatfs_get_mount() == 0) {
		errno = EIO;
		return -1;
	}
#if _USE_LFN != 0
	char oldtmp[_MAX_LFN + 1];
	utf8_to_sjis(oldpath, oldtmp, sizeof(oldtmp));
	char newtmp[_MAX_LFN + 1];
	utf8_to_sjis(newpath, newtmp, sizeof(newtmp));
	FRESULT res = f_rename(oldtmp, newtmp);
#else
	FRESULT res = f_rename(oldpath, newpath);
#endif
	if(res == FR_OK) {

		errno = 0;
		return 0;
	} else {
#ifdef SYSCALLS_DEBUG
		sprintf(debug_tmp_, "syscalls: '%s' -> '%s' link error: %x\n", oldpath, newpath, (int)res);
		sci_puts(debug_tmp_);
#endif
		errno = EIO;
		return -1;
	}
#else
	errno = EIO;
	return -1;
#endif
}


//-----------------------------------------------------------------//
/*!
	@brief	名前を削除し、場合によってはそれが参照しているファイルも削除する
	@param[in]	path	ファイル名
	@return		成功なら「０」を返す。
*/
//-----------------------------------------------------------------//
int unlink(const char *path)
{
#ifdef FAT_FS
	if(fatfs_get_mount() == 0) {
		errno = EIO;
		return -1;
	}
#if _USE_LFN != 0
	char tmp[_MAX_LFN + 1];
	utf8_to_sjis(path, tmp, sizeof(tmp));
	FRESULT res = f_unlink(tmp);
#else
	FRESULT res = f_unlink(path);
#endif
	if(res == FR_OK) {
		errno = 0;
		return 0;
	} else {
		errno = EIO;
		return -1;
	}
#else
	errno = EIO;
	return -1;
#endif
}


//-----------------------------------------------------------------//
/*!
	@brief	ファイルの状態を取得する
	@param[in]	file	ファイル記述子
	@param[in]	st		ファイル情報を格納する構造体のポインター
	@return		成功なら「０」を返す。
*/
//-----------------------------------------------------------------//
int fstat(int file, struct stat *st)
{
	int ret = -1;
	if(file >= 0 && file <= 2) {
		errno = 0;
		ret = 0;
	}
#if 0
	FILINFO finf;
	struct tm ttm;
	time_t tt;
	mode_t mdt;

	FRESULT res = f_stat(path, &finf);
	if(res == FR_OK) {
		st->st_dev = 0;		/* ファイルがあるデバイスの ID */
		st->st_ino = 0;		/* inode 番号 */

		mdt = 0;
		if(finf.fattrib & AM_HID) ;
		if(finf.fattrib & AM_SYS) ;
		if(finf.fattrib & AM_ARC) ;
		if(finf.fattrib & AM_DIR) mdt |= S_IFDIR;
		else {
			mdt |= S_IFREG | S_IRUSR | S_IRGRP | S_IROTH;
		}
		if((finf.fattrib & AM_RDO) == 0) mdt |= S_IWUSR | S_IWGRP | S_IWOTH;
		st->st_mode = mdt;	/* アクセス保護 */

		st->st_nlink = 0;	/* ハードリンクの数 */

		st->st_uid = 0;		/* 所有者のユーザ ID */
		st->st_gid = 0;		/* 所有者のグループ ID */

		st->st_rdev = 0;	/* デバイス ID (特殊ファイルの場合) */
		st->st_size = finf.fsize;	/* ファイルサイズ */
		st->st_blksize = 0;	/* ファイルシステム I/O でのブロックサイズ */
		st->st_blocks = 0;	/* 割り当てられた 512B のブロック数 */

/* ftime
   ファイルの変更された時刻、またはディレクトリの作成された時刻が格納されます。
   bit15:11 ---> 時が 0..23 の値で入ります。
   bit10:5  ---> 分が 0..59 の値で入ります。
   bit4:0   ---> 秒/2が 0..29 の値で入ります。
*/
		ttm.tm_sec  =  finf.ftime & 0x1f;
		ttm.tm_min  = (finf.ftime >> 5) & 0x3f;
		ttm.tm_hour = (finf.ftime >> 11) & 0x1f;

/* fdate
   ファイルの変更された日付、またはディレクトリの作成された日付が格納されます。
   bit15:9 ---> 1980年を起点とした年が 0..127 で入ります。
   bit8:5  ---> 月が 1..12 の値で入ります。
   bit4:0  ---> 日が 1..31 の値で入ります。
*/
		ttm.tm_mday =  finf.fdate & 0x1f;
		ttm.tm_mon  = (finf.fdate >> 5) & 0x1f;
		ttm.tm_year = ((finf.fdate >> 10) & 0x7f) + (1980 - 1900);

		tt = mktime(&ttm);
		st->st_atime = tt;	/* 最終アクセス時刻 */
		st->st_mtime = tt;	/* 最終修正時刻 */
		st->st_ctime = tt;	/* 最終状態変更時刻 */

		errno = 0;
		return 0;
	} else {
		errno = EIO;
		return -1;
	}
#endif
	return ret;
}


//-----------------------------------------------------------------//
/*!
	@brief	ファイル記述子で指定されたファイルをクローズする
	@param[in]	file	ファイル記述子
	@return		成功なら「０」を返す。
*/
//-----------------------------------------------------------------//
int close(int file)
{
#ifdef LOGGING_FS
	uint32_t orgt = millis();
#endif

#ifdef FAT_FS
	FRESULT res;
	if(file >= 0 && file <= 2) {
		errno = EBADF;
		return -1;
	} else if(fatfs_get_mount() != 0 && file < OPEN_MAX_) {
		fd_pads_[file] = 0;

		res = f_close(&file_obj_[file - STD_OFS_]);
		if(res == FR_OK) {
			errno = 0;
#ifdef SYSCALLS_DEBUG
			sprintf(debug_tmp_, "syscalls: close ok.(%d):\n", file);
			sci_puts(debug_tmp_);
#endif

#ifdef LOGGING_FS
			uint32_t t = millis() - orgt;
			if(fs_close_max < t) fs_close_max = t;
			++fs_close_cnt;
#endif

			return 0;
		} else {
#ifdef SYSCALLS_DEBUG
			sprintf(debug_tmp_, "(%d)close error: %x\n", file, (int)res);
			sci_puts(debug_tmp_);
#endif
			errno = EIO;
			return -1;
		}
	} else {
		errno = EBADF;
		return -1;
	}
#else
	errno = EBADF;
	return -1;
#endif
}


//-----------------------------------------------------------------//
/*!
	@brief	ファイルディスクリプタが端末を参照しているかをチェックする
	@param[in]	file	ファイル記述子
	@return		端末を参照するオープンされたファイルディスクリプタ @n
	            であれば 1 を返す。@n
				そうでなければ 0 を返し、 errno にエラーを示す値を設定する。
*/
//-----------------------------------------------------------------//
int isatty(int file)
{
	if(file >= 0 && file <= 2) {
		errno = 0;
		return 1;
	}
#ifdef FAT_FS
	else if(file < OPEN_MAX_) {
		errno = ENOTTY;
		return 0;
	}
#endif
	errno = EINVAL;
	return 0;
}


void kill(int n, int m)
{
}


pid_t getpid()
{
	return (pid_t)1;
}
