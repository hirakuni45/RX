#pragma once

#include "common/format.hpp"

// 20211216_MandelbroBench （マンデルブロベンチ）for Arduino environment
// 計算条件は参考サイトと同じ：ASCIIART(マンデルブロ集合)ベンチマーク http://haserin09.la.coocan.jp/asciiart.html
// 計算速度を正確に測定するため結果を配列に一旦保存し、最後にまとめて出力
// 2021/12/16 ラジオペンチ http://radiopench.blog96.fc2.com/

extern "C" {
	uint32_t micros();
}

struct mandelbrot {

	typedef uint8_t byte;

	byte result[25][79];                  // 計算結果保存配列
	int calcCount = 0;

	void setup() {
		int   i, x, y;
		float a, b, ca, cb, t;
//		unsigned long t0, t1;
		uint32_t t0, t1;
//		Serial.begin(115200);
//		while(!Serial){                     // シリアルがレディになるまで待つ
//		}
//		Serial.println(); Serial.println();
		t0 = micros();                      // 開始時間を記録
		for (y = -12; y <= 12; y++) {       // y方向は±12
			for (x = -39; x <= 39; x++) {     // X方向は±39
				ca = x * 0.0458;                // マンデルブロ集合の計算と判定
				cb = y * 0.08333;
				a  = ca;
				b  = cb;
				for (i = 0; i <= 15; i++) {     // 1座標毎に16回下記の計算を行い、
					calcCount++;
					t = a * a - b * b + ca;
					b = 2.0f * a * b + cb;
					a = t;
					if ((a * a + b * b) > 4.0) {  // 値が4以上だったら発散したとみなして
						break;                      // 計算中止してループを抜ける
					}
				}
			result[y + 12][x + 39] = i;     // 結果を配列に保存
			}                                 // next x
		}                                   // next y

		t1 = micros();
//		Serial.print("time = ");
//		Serial.print(t1 - t0);              // 計算時間を出力
//		Serial.print(" us, calc count = "); 
//		Serial.println(calcCount);          // 計算回数を出力
		utils::format("time = %u  us, calc count = %u\n") % (t1 - t0) % calcCount;
		printOut();                         // マンデルブロ集合アスキーアートを出力
	}  

	void loop() {
	}

	void printOut() {                     // 配列に保存した結果の出力
		static constexpr char cx[] = "0123456789ABCDEF ";    // 表示文字変換テーブル
		for (int i = 0; i < 25; i++) {      // 行カウンタ
			for (int j = 0; j < 79; j++) {    // 列カウンタ
//				Serial.print(cx[result[i][j]]); // テーブルから該当文字を出力
				utils::format("%c") % cx[result[i][j]];
			}
//			Serial.println();                 // 行末で改行
			utils::format("\n");
		}
//		Serial.println();                   // AAの最後で改行
		utils::format("\n");
	}
};
