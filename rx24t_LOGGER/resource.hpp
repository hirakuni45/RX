#pragma once
//=====================================================================//
/*!	@file
	@brief	リソース・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/time.h"

namespace app {

	extern const uint8_t* nmb12[];

	extern const uint8_t nmb12_a[];
	extern const uint8_t nmb12_b[];
	extern const uint8_t nmb12_c[];
	extern const uint8_t nmb12_v[];
	extern const uint8_t nmb12_x[];
	extern const uint8_t nmb12_po[];
	extern const uint8_t nmb12_do[];
	extern const uint8_t nmb12_co[];
	extern const uint8_t nmb12_sl[];

	extern const uint8_t* nmb32[];
	extern const uint8_t nmb32_p[];
	extern const uint8_t nmb32_x[];
	extern const uint8_t nmb32_kmh[];
	extern const uint8_t nmb32_rpm[];

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	リソース・クラス
		@param[in]	GR		描画クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GR>
	class resource {

		GR&	gr_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		resource(GR& gr) : gr_(gr) { }


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）を使ったキャラクター表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	ch	キャラクター・コード
		*/
		//-----------------------------------------------------------------//
		void draw_cha_12(short x, short y, char ch)
		{
			if(ch >= '0' && ch <= '9') {
				gr_.draw_mobj(x, y, nmb12[ch - '0']);
			} else if(ch == 'A') {
				gr_.draw_mobj(x, y, nmb12_a);
			} else if(ch == 'B') {
				gr_.draw_mobj(x, y, nmb12_b);
			} else if(ch == 'C') {
				gr_.draw_mobj(x, y, nmb12_c);
			} else if(ch == 'V') {
				gr_.draw_mobj(x, y, nmb12_v);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）を使った「電圧表示」
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	n	電圧（10倍値）
		*/
		//-----------------------------------------------------------------//
		void draw_volt_12(short x, short y, short n)
		{
			unsigned char m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*2+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*2, y, nmb12_po);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*1, y, nmb12[m]);

			m = n % 10;
			if(m) {
				gr_.draw_mobj(x+9*0, y, nmb12[m]);
			}

			gr_.draw_mobj(x+9*3+3, y, nmb12_v);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）を使った「温度表示」
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	n	温度（10倍値）
		*/
		//-----------------------------------------------------------------//
		void draw_temp_12(short x, short y, short n)
		{
			unsigned char m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*3+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*3, y, nmb12_po);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*2, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			if(n > 0 || m != 0) {
				gr_.draw_mobj(x+9*1, y, nmb12[m]);
			}

			m = n % 10;
			if(m) {
				gr_.draw_mobj(x+9*0, y, nmb12[m]);
			}

			gr_.draw_mobj(x+9*4+3+5, y, nmb12_c);
			gr_.draw_mobj(x+9*4+3, y, nmb12_do);

		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った時間表示（時：分）
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	t	時間（秒単位）
		*/
		//-----------------------------------------------------------------//
		void draw_time_hm_12(short x, short y, time_t t)
		{
			unsigned char	m;

			t /= 60;

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+9*3+3, y, nmb12[m]);

			m = t % 6;
			t /= 6;
			gr_.draw_mobj(x+9*2+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*2+0, y, nmb12_c);

			m = t % 24;
			gr_.draw_mobj(x+9*1+0, y, nmb12[m % 10]);
			m /= 10;
			gr_.draw_mobj(x+0*1+0, y, nmb12[m]);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った時間表示（時：分．秒）
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	t	時間（秒単位）
		*/
		//-----------------------------------------------------------------//
		void draw_time_hms_12(short x, short y, time_t t)
		{
			unsigned char	m;

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+9*5+3+3, y, nmb12[m]);

			m = t % 6;
			t /= 6;
			gr_.draw_mobj(x+9*4+3+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*4+3+0, y, nmb12_po);

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+9*3+3, y, nmb12[m]);

			m = t % 6;
			t /= 6;
			gr_.draw_mobj(x+9*2+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*2+0, y, nmb12_co);

			m = t % 24;
			gr_.draw_mobj(x+9*1+0, y, nmb12[m % 10]);
			m /= 10;
			gr_.draw_mobj(x+0*1+0, y, nmb12[m]);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った時間表示（分：秒．1/100）@n
					※９分を超えたら「X」と表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	t	時間（1/100 秒単位）
		*/
		//-----------------------------------------------------------------//
		void draw_time_mst_12(short x, short y, time_t t)
		{
			unsigned char	m;

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+9*4+3+3, y, nmb12[m]);
			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+9*3+3+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*3+3+0, y, nmb12_po);

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+9*2+3, y, nmb12[m]);
			m = t % 6;
			t /= 6;
			gr_.draw_mobj(x+9*1+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*1+0, y, nmb12_co);

			if(t < 10) {
				gr_.draw_mobj(x+0*1+0, y, nmb12[t]);
			} else {
				gr_.draw_mobj(x+0*1+0, y, nmb12_x);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った３桁表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	n	週回数
		*/
		//-----------------------------------------------------------------//
		void draw_number3_12(short x, short y, unsigned short n)
		{
			unsigned char	m;

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*2, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*1, y, nmb12[m]);

			m = n % 10;
//	n /= 10;
			gr_.draw_mobj(x+9*0, y, nmb12[m]);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）フォント用「/」表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
		*/
		//-----------------------------------------------------------------//
		void draw_slash_12(short x, short y)
		{
			gr_.draw_mobj(x, y, nmb12_sl);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った６桁表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	n	週回数
		*/
		//-----------------------------------------------------------------//
		void draw_number6_12(short x, short y, unsigned long n)
		{
			unsigned char	m;

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*5, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*4, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*3, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*2, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*1, y, nmb12[m]);

			m = n % 10;
//	n /= 10;
			gr_.draw_mobj(x+9*0, y, nmb12[m]);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った４．１桁表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	n	週回数
		*/
		//-----------------------------------------------------------------//
		void draw_number4d1_12(short x, short y, unsigned long n)
		{
			unsigned char	m;

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*4+3, y, nmb12[m]);

			gr_.draw_mobj(x+9*4, y, nmb12_po);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*3, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*2, y, nmb12[m]);

			m = n % 10;
			n /= 10;
			gr_.draw_mobj(x+9*1, y, nmb12[m]);

			m = n % 10;
//	n /= 10;
			gr_.draw_mobj(x+9*0, y, nmb12[m]);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った４桁表示
			※ゼロサプレス有り
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void draw_number4z_12(short x, short y, unsigned short n)
		{
			unsigned char	m[4];
			char	f;

			f = 0;

			m[0] = n % 10;
			n /= 10;
			m[1] = n % 10;
			n /= 10;
			m[2] = n % 10;
			n /= 10;
			m[3] = n % 10;

			if(f != 0 || m[3] != 0) {
				gr_.draw_mobj(x+9*0, y, nmb12[m[3]]);
				f++;
			}
			if(f != 0 || m[2] != 0) {
				gr_.draw_mobj(x+9*1, y, nmb12[m[2]]);
				f++;
			}
			if(f != 0 || m[1] != 0) {
				gr_.draw_mobj(x+9*2, y, nmb12[m[1]]);
			}
			gr_.draw_mobj(x+9*3, y, nmb12[m[0]]);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）数字を使った５桁表示
			※ゼロサプレス有り
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void draw_number5z_12(short x, short y, uint32_t n)
		{
			unsigned char m[5];
			char	f;

			f = 0;

			m[0] = n % 10;
			n /= 10;
			m[1] = n % 10;
			n /= 10;
			m[2] = n % 10;
			n /= 10;
			m[3] = n % 10;
			n /= 10;
			m[4] = n % 10;

			if(m[4] != 0) {
				gr_.draw_mobj(x+9*0, y, nmb12[m[4]]);
				f++;
			}
			if(f != 0 || m[3] != 0) {
				gr_.draw_mobj(x+9*1, y, nmb12[m[3]]);
				f++;
			}
			if(f != 0 || m[2] != 0) {
				gr_.draw_mobj(x+9*2, y, nmb12[m[2]]);
				f++;
			}
			if(f != 0 || m[3] != 0) {
				gr_.draw_mobj(x+9*3, y, nmb12[m[1]]);
			}
			gr_.draw_mobj(x+9*4, y, nmb12[m[0]]);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	３２ピクセル（高さ）数字を使った時間（ラップタイム）の表示@n
			※９分を超えたら「X」と表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	t	1/100 秒単位の整数
		*/
		//-----------------------------------------------------------------//
		void draw_time_32(short x, short y, time_t t)
		{
			unsigned char m;

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+20*4+6+6, y, nmb32[m]);

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+20*3+6+6, y, nmb32[m]);

			gr_.draw_mobj(x+20*3+6, y, nmb32_p);

			m = t % 10;
			t /= 10;
			gr_.draw_mobj(x+20*2+6, y, nmb32[m]);

			m = t % 6;
			t /= 6;
			gr_.draw_mobj(x+20*1+6, y, nmb32[m]);

			gr_.draw_mobj(x+20*1, y, nmb32_p);

			if(t < 10) {
				gr_.draw_mobj(x, y, nmb32[t]);
			} else 		{
				gr_.draw_mobj(x, y, nmb32_x);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	３２ピクセル（高さ）数字を使った３桁表示（速度表示用）
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	v	値
		*/
		//-----------------------------------------------------------------//
		void draw_speed_32(short x, short y, unsigned short v)
		{
			unsigned char m[3];
			char zf;

			m[2] = v % 10;
			v /= 10;
			m[1] = v % 10;
			v /= 10;
			m[0] = v % 10;

			if(m[0] != 0) {
				gr_.draw_mobj(x+20*0, y, nmb32[m[0]]);
				zf = 1;
			} else {
				zf = 0;
			}

			if(zf != 0 || m[1] != 0) {
				gr_.draw_mobj(x+20*1, y, nmb32[m[1]]);
			}

			gr_.draw_mobj(x+20*2, y, nmb32[m[2]]);

			gr_.draw_mobj(x+20*3, y+20, nmb32_kmh);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	３２ピクセル（高さ）数字を使った５桁表示（ゼロサプレス）
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	v	値
		*/
		//-----------------------------------------------------------------//
		void draw_number5_32(short x, short y, unsigned long v)
		{
			unsigned char m[5];
			char zf;
			unsigned char i;

			m[4] = v % 10;
			v /= 10;
			m[3] = v % 10;
			v /= 10;
			m[2] = v % 10;
			v /= 10;
			m[1] = v % 10;
			v /= 10;
			m[0] = v % 10;

			zf = 0;
			for(i = 0; i < 5; ++i) 		{
				if(i == (5 - 1)) ++zf;
				if(zf != 0 || m[i] != 0) 		{
					gr_.draw_mobj(x, y, nmb32[m[i]]);
					++zf;
				}
				x += 20;
			}

			gr_.draw_mobj(x, y+18, nmb32_rpm);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	タイトル描画
		*/
		//-----------------------------------------------------------------//
		void draw_title()
		{
#ifdef TITLE_ENABLE
			gr_.draw_mobj(0, 0, g_title_bmp);
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	バッテリー・アイコン描画
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	t	タイプ（0 to 15: level, -1: ext)
		*/
		//-----------------------------------------------------------------//
		void draw_batt(short x, short y, char t)
		{
			if(t >= 0) 		{
//				gr_.draw_mobj(x, y, g_batt_icon);
				gr_.fill(x + 2, y + 2, t, 6, 1);
			} else {
//				gr_.draw_mobj(x, y, g_batt_ext);
			}
		}
	};
}
