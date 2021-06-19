#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX651/RX65N/RX66T/RX72T/RX72N/RX72M グループ・システム制御 @n
			※RX24T は構成が大きく異なるので、RX24T/system_io.hpp に分離しています。@n
			※ USB を使う場合：96MHz, 144MHz, 192MHz, 240MHz のいづれか @n
			※ 通常ベースクロックは、12MHz、24MHz を使います。@n
			RX72x 系では、内部 PLL 回路が追加され、Ethernet などに必要な 25MHz を得る為 @n
			16MHz を使います。@n
			(16MHz x 12.5 -> 200MHz, 16MHz x 15 -> 240MHz)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/system.hpp"

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T) || defined(SIG_RX65N) || defined(SIG_RX72T) || defined(SIG_RX72N) || defined(SIG_RX72M)
#elif
#  error "system_io.hpp: Not available on RX24T"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_base クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO を使う場合、同時に、BASE_CLOCK_ に周波数を設定します。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE {
			XTAL,		///< クリスタル接続
			EXT,		///< クロック入力
			HOCO,		///< 高速オンチップオシレーター
			LOCO,		///< 低速オンチップオシレーター (240KHz)
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス @n
				INTR_CLOCK は、内部 PLL で扱える最大速度です、@n
				外部クリスタルを微妙な周波数にする場合、その整数倍にしなければなりません。 @n
				RX71M はスーパーバイザモードでの変更が必要なので、「start.s」内で行う。 @n
				RX71M の場合、アセンブラにオプション「--defsym MEMWAIT=1」を渡す。
		@param[in]	BASE_CLOCK_	ベース・クロック周波数
		@param[in]	INTR_CLOCK	内臓クロック周波数 @n
								※USB を使う場合、「INTR_CLOCK」は48の倍数である事
		@param[in]	OSC_TYPE	発信器タイプを設定（通常、XTAL）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <auto OSC_TYPE_ = system_base::OSC_TYPE::XTAL>
	struct system_io : public system_base {

		static uint8_t clock_div_(uint32_t clk) noexcept
		{
			uint8_t div = 0;
			while(clk < clock_profile::PLL_BASE) {
				++div;
				clk <<= 1;
			}
			if(div > 0b0110) div = 0b0110;
			return div;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  マスター・クロックのブースト @n
					インストラクション・クロックを最大速度にブーストする。
		*/
		//-------------------------------------------------------------//
		static void boost_master_clock() noexcept
		{
			device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

			device::SYSTEM::MOSCWTCR = 9;	// 1ms wait

			// メインクロック強制発振とドライブ能力設定
			if(OSC_TYPE_ == OSC_TYPE::XTAL) {
				uint8_t modrv2 = 0b11;
				if(clock_profile::BASE > 20'000'000) modrv2 = 0b00;
				else if(clock_profile::BASE > 16'000'000) modrv2 = 0b01;
				else if(clock_profile::BASE > 8'000'000) modrv2 = 0b10;
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(modrv2);
				device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
				while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }
			} else if(OSC_TYPE_ == OSC_TYPE::EXT) {
				device::SYSTEM::MOSCCR.MOSTP = 1;		// メインクロック発振器停止
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MOSEL.b();
			} else if(OSC_TYPE_ == OSC_TYPE::HOCO) {  // 高速オンチップオシレータ
				device::SYSTEM::MOSCCR.MOSTP = 1;
				device::SYSTEM::HOCOCR = device::SYSTEM::HOCOCR.HCSTP.b(1);  // 停止
				uint8_t frq;
				if(clock_profile::BASE == 16'000'000) frq = 0b00;
				else if(clock_profile::BASE == 18'000'000) frq = 0b01;
				else if(clock_profile::BASE == 20'000'000) frq = 0b10;
				else frq = 0b00;
				device::SYSTEM::HOCOCR2.HCFRQ = frq;
				device::SYSTEM::HOCOCR = device::SYSTEM::HOCOCR.HCSTP.b(0);  // 動作
				while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }
			} else {
				device::SYSTEM::PRCR = 0xA500;
				return;
			}

#if defined(SIG_RX65N)
			if(clock_profile::ICLK >= 120'000'000) {  // 120MHz 以上の場合設定
				device::SYSTEM::ROMWT = 0b10;
			} else if(clock_profile::ICLK >= 100'000'000) {
				device::SYSTEM::ROMWT = 0b01;
			} else if(clock_profile::ICLK >= 50'000'000) {
				device::SYSTEM::ROMWT = 0b00;
			}
#endif
			// RX71M はスーパーバイザモードでの変更が必要なので、「start.s」内で行う。
			// RX71M の場合、アセンブラにオプション「--defsym MEMWAIT=1」を渡す。
#if defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72T) || defined(SIG_RX72N)
			if(clock_profile::ICLK > 120'000'000) {  // 120MHz 以上の場合設定
				device::SYSTEM::MEMWAIT = 1;
				volatile auto tmp = device::SYSTEM::MEMWAIT();  // 読み出しを行う
			}
#endif
			// (x10.0) 0b010011, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// ... MAX x30.0
			uint32_t n = clock_profile::PLL_BASE * 2 / clock_profile::BASE;
			if(n < 20) n = 20;
			else if(n > 60) n = 60;
			n -= 20;
			device::SYSTEM::PLLCR.STC = n + 0b010011;  // base x10
			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.BCK.b(clock_div_(clock_profile::BCLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
								  | device::SYSTEM::SCKCR.PCKC.b(clock_div_(clock_profile::PCLKC))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD));
			{  // USB Master Clock の設定
				auto usb_div = clock_profile::PLL_BASE / 48'000'000;
				if(usb_div >= 2 && usb_div <= 5) {
					// 1/2, 1/3, 1/4, 1/5
					device::SYSTEM::SCKCR2.UCK = usb_div - 1;
				}
			}

			if(OSC_TYPE_ == OSC_TYPE::HOCO) {
				device::SYSTEM::PLLCR.PLLSRCSEL = 1;
			}

			device::SYSTEM::SCKCR3.CKSEL = 0b100;   ///< PLL 選択

			if(OSC_TYPE_ == OSC_TYPE::XTAL || OSC_TYPE_ == OSC_TYPE::EXT) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  ///< 低速オンチップオシレータ停止
				device::SYSTEM::HOCOCR.HCSTP = 1;  ///< 高速オンチップオシレータ停止
				device::SYSTEM::HOCOPCR.HOCOPCNT = 1;  ///< 高速オンチップオシレーター電源 OFF
			}

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;

#if defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72T) || defined(SIG_RX72N)
			// ROM キャッシュを有効（標準）
			device::SYSTEM::ROMCE = 1;
#endif
#if defined(__TFU)
			__init_tfu();
#endif
		}


#if defined(SIG_RX72M) || defined(SIG_RX72N)
		//-------------------------------------------------------------//
		/*!
			@brief  PPLL 制御を使って PHY 向け 25MHz を出力する。
			@return 成功なら「true」
		*/
		//-------------------------------------------------------------//
		static bool setup_phy25() noexcept
		{
			if(clock_profile::BASE != 16'000'000) {  // ベースクロックが 16MHz 以外は、生成不可とする。 
				return false;
			}

			bool ret = true;
			device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

			device::SYSTEM::PACKCR.OUTCKSEL = 1;

			// PPLIDIV: 1/2, PPLSTC: x12.5 (100MHz)
			device::SYSTEM::PPLLCR  = device::SYSTEM::PPLLCR.PPLIDIV.b(0b01)
								    | device::SYSTEM::PPLLCR.PPLSTC.b(0b011000);
			device::SYSTEM::PPLLCR2 = device::SYSTEM::PPLLCR2.PPLLEN.b(1);  // 発信許可

			// PPLL 安定待ち
			while(device::SYSTEM::OSCOVFSR.PPLOVF() == 0) { asm("nop"); }

			// PPLLCR3: 1/4 (25MHz)
			device::SYSTEM::PPLLCR3 = device::SYSTEM::PPLLCR3.PPLCK.b(0b0011);

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;

			// ポート・マッピングを行う必要があるが、あえて、ここでは許可しない。
			// ※このヘッダーに、port_map.hpp の依存を無くす為。
			// deveice::port_map::turn_CLKOUT25M();

			return true;
		}
#endif
	};


	//-------------------------------------------------------------//
	/*!
		@brief  ソフト・リセットの起動
	*/
	//-------------------------------------------------------------//
	inline void assert_soft_reset()
	{
		device::SYSTEM::PRCR = 0xA502;
		device::SYSTEM::SWRR = 0xA501;
		device::SYSTEM::PRCR = 0xA500;
	}


	//-------------------------------------------------------------//
	/*!
		@brief  MTU マスタークロック取得
		@return MTU マスタークロック
	*/
	//-------------------------------------------------------------//
	inline uint32_t get_mtu_master_clock() noexcept
	{
#if defined(SIG_RX66T) || defined(SIG_RX72T)
		return clock_profile::PCLKC;
#else
		return clock_profile::PCLKA;
#endif
	}
}
