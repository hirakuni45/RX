//=========================================================================//
/*! @file
    @brief  ブートモード ID コードプロテクト定義 @n
			RX140 @n
			RX220 @n
			RX230/RX231 @n
			RX24T/RX24U @n
			RX260/RX261 @n
			RX621/RX62N @n
			RX631/RX63N/RX63T @n
			このテーブルは、第三者がシリアルプログラマを接続したときの @n
			ユーザ領域とデータ領域の読み出し、書き換えを禁止する機能です @n
			詳しくは、ハードウェアーマニュアルの「ブートモード ID コードプロテクト」 @n
			を参照して下さい @n
			制御コード（1バイト）と、15バイトのパスフレーズから構成され @n
			32ビット長、4ワードのデータとして設定します @n
			セクション名「.passphrase」はリンカファイルで定義してあります @n
			設定内容によっては、書き換えが出来なくなる場合もあるので、十分注意してください @n
			プロジェクトの Makefile で、「CSOURCES」に、このソースコードを追加して下さい
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include<stdint.h>

// 制御コード(1 Byte), パスフレーズ(15 Bytes)
__attribute__((section(".passphrase")))
uint32_t id[4] = { 0x45112233, 0x44556677, 0x8899AABB, 0xCCDDEEFF };
// rx_prog --id=45:11:22:33:44:55:66:77:88:99:AA:BB:CC:DD:EE:FF
