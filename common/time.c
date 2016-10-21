//=====================================================================//
/*!	@file
	@brief	時間関数
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdlib.h>
#include <string.h>
#include "time.h"

// 各月に対する日数（通常年）
static const char mday_tbl_[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/// 大阪、札幌、東京のタイムゾーン +9 hour
static char timezone_offset_ = 9;
static struct tm time_st_;
static const char* wday_[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" 
};
static const char* mon_[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static const char* null_ = { "" };

//-----------------------------------------------------------------//
/*!
	@brief	西暦から、その年がうるう年かを判定
	@param[in]	year	西暦
	@return		うるう年なら「0」以外
*/
//-----------------------------------------------------------------//
char check_leap_year(short year)
{
	if((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0)) return 1;
	return 0;
}


//-----------------------------------------------------------------//
/*!
	@brief	西暦と、月から、その月の最大日数を得る。
	@param[in]	year	西暦
	@param[in]	mon		月（0 to 11)
	@return		「月」に対応する最大日数
*/
//-----------------------------------------------------------------//
char get_mday(short year, char mon)
{
	char	d;

	d = mday_tbl_[(int)mon];
	if(mon == 1) {	// 2月
		if(check_leap_year(year)) d++;
	}
	return d;
}


//-----------------------------------------------------------------//
/*!
	@brief	西暦から、その年の総日数を得る。
	@param[in]	year	西暦
	@return		「年」に対応する総日数
*/
//-----------------------------------------------------------------//
short get_yday(short year)
{
	if(check_leap_year(year)) return 366;
	else return 365;
}


//-----------------------------------------------------------------//
/*!
	@brief	西暦、月から、1970 年からの総日数を得る。
	@param[in]	year	西暦 1970 〜
	@param[in]	mon		月	[0..11]
	@param[in]	day		日	[1..31]
	@return		1970 年1月1日からの総日数
*/
//-----------------------------------------------------------------//
long get_total_day(short year, char mon, char day)
{
	if(year < 1970) return -1L;

	long d = 0;
	short i = 1970;
	while(i < year) {
		d += (long)get_yday(i);
		i++;
	}

	i = 0;
	while(i < mon) {
		d += get_mday(year, i);
		i++;
	}

	d += day - 1;

	return d;
}


//-----------------------------------------------------------------//
/*!
	@brief	世界標準時間（グリニッジ）からのオフセットを取得
	@return	オフセット時間（秒）
*/
//-----------------------------------------------------------------//
time_t get_timezone_offset(void)
{
	return (time_t)timezone_offset_ * 3600;
}


//-----------------------------------------------------------------//
/*!
	@brief	グリニッジ標準時への変換
	@param[in]	timer 
	@return		グローバル tm 構造体のポインター
*/
//-----------------------------------------------------------------//
struct tm *gmtime(const time_t *tp)
{
	time_t	t;
	short	i, j, k;

	t = *tp;

	time_st_.tm_sec  = t % (time_t)60;
	t /= (time_t)60;

	time_st_.tm_min  = t % (time_t)60;
	t /= (time_t)60;

	time_st_.tm_hour = t % (time_t)24;
	t /= (time_t)24;

	time_st_.tm_wday = (t + 4) % 7;

	j = 1970;
	while(t >= (i = get_yday(j))) {
		t -= (time_t)i;
		j++;
	}
	time_st_.tm_year = j - 1900;

	time_st_.tm_yday = t;

	k = 0;
	while(t >= (i = get_mday(j, k))) {
		t -= (time_t)i;
		k++;
	}
	time_st_.tm_mon = k;
	time_st_.tm_mday = t + 1;

	return &time_st_;
}


//-----------------------------------------------------------------//
/*!
	@brief	現地時間に変換
	@param[in]	timer	現地時間
	@return		tm 構造体のポインター
*/
//-----------------------------------------------------------------//
struct tm *localtime(const time_t *timer)
{
	time_t t;

	if(timer == NULL) return NULL;

	t = *timer;

// GMT から ローカル時間へ
	t += (time_t)(timezone_offset_) * 3600;

	gmtime(&t);

	return &time_st_;
}


//-----------------------------------------------------------------//
/*!
	@brief	tm 構造体から、世界標準(グリニッジ)時間を得る@n
			※メンバー変数 tm_yday は再計算される。@n
			※メンバー変数 tm_wday は再計算される。@n
			※ tm_isdgt は無視される。
	@param[in]	tmp	tm 構造体のポインター@n
				※NULLの場合は、システムの構造体が使われる
	@return		GMT:1970年1月1日0時0分0秒(4:THU)からの経過時間（秒）
*/
//-----------------------------------------------------------------//
time_t mktime(const struct tm *tmp)
{
	time_t	t;
	long	td;

	if(tmp == NULL) tmp = &time_st_;

	t  = (time_t)tmp->tm_sec;
	t += (time_t)(tmp->tm_min * 60);
	t += (time_t)tmp->tm_hour * 3600L;
	td = get_total_day(tmp->tm_year + 1900, tmp->tm_mon, tmp->tm_mday);
	t += (time_t)td * 86400L;

// GMT からの偏差(-9時間）
	t -= (time_t)timezone_offset_ * 3600;

	return t;
}


//-----------------------------------------------------------------//
/*!
	@brief	このモジュールで利用している tm 構造体のポインターを得る。
	@return		tm 構造体のポインター
*/
//-----------------------------------------------------------------//
struct tm *get_tm(void)
{
	return &time_st_;
}


//-----------------------------------------------------------------//
/*!
	@brief	tm 構造体のコピー
	@param[in]	src	コピー元
	@param[out]	dst	コピー先
*/
//-----------------------------------------------------------------//
void copy_tm(const struct tm *src, struct tm *dst)
{
	if(src == NULL || dst == NULL) return;
	memcpy(dst, src, sizeof(struct tm));
}


//-----------------------------------------------------------------//
/*!
	@brief	「曜日」文字列を取得
	@param[in]	idx	インデックス
	@return 文字列（３文字）
*/
//-----------------------------------------------------------------//
const char* get_wday(uint8_t idx)
{
	if(idx >= 7) return null_;
	return wday_[idx];
}


//-----------------------------------------------------------------//
/*!
	@brief	「月」文字列を取得
	@param[in]	idx	インデックス
	@return 文字列（３文字）
*/
//-----------------------------------------------------------------//
const char* get_mon(uint8_t idx)
{
	if(idx >= 12) return null_;
	return mon_[idx];
}


#if 0
//-----------------------------------------------------------------//
/*!
	@brief	時間と日付の表示
	@param[in]	sttm	時間構造体
*/
//-----------------------------------------------------------------//
void xprint_date(const struct tm* sttm)
{
	xprintf(get_week_text(sttm->tm_wday));
	xprintf(PSTR(" "));
	xprintf(get_mon_text(sttm->tm_mon));
	xprintf(PSTR(" "));
	xprintf(PSTR("%d %02d:%02d.%02d %d"),
			sttm->tm_mday, sttm->tm_hour, sttm->tm_min, sttm->tm_sec, sttm->tm_year + 1900);
}
#endif

/* ----- End Of File "time.c" ----- */
