#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・汎用 PWM タイマー（GPTW）マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

/// F_PCLKC タイマーのクロックが必要なので定義が無い場合エラーにします。
#ifndef F_PCLKC
#  error "gptw_mgr.hpp requires F_PCLKC to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW マネージャー・ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class gptw_base {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作モード
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MODE : uint8_t {
			PWM_S,		///< のこぎり波 PWM
			SINGLE,		///< ワンショット・パルス
			PWM_T1,		///< 三角波 PWM 1（谷32ビット転送）
			PWM_T2,		///< 三角波 PWM 2（山/谷32ビット転送）
			PWM_T3,		///< 三角波 PWM 3（谷64ビット転送）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力設定
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OUTPUT : uint8_t {
			PA,		///< チャネル A 正出力
			PB,		///< チャネル B 正出力
			NA,		///< チャネル A 逆出力
			NB,		///< チャネル B 逆出力
			PA_PB,	///< チャネル A, B 正出力
			PA_NB,	///< チャネル A 正出力、B 逆出力
			NA_PB,	///< チャネル A 逆出力、B 正出力
			NA_NB,	///< チャネル A, B 逆出力
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW マネージャー・クラス
		@param[in]	GPTWX	GPTW[0-9] ユニット
		@param[in]	PSEL	入出力ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GPTWX, port_map_gptw::option PSEL = port_map_gptw::option::FIRST>
	class gptw_mgr : public gptw_base {

		// ※必要なら、実装する
		void sleep_() { }

		uint32_t	base_;
		uint8_t		ilvl_;

		void protect_enable_(bool ena = true) noexcept
		{
			GPTWX::GTWP = GPTWX::GTWP.PRKEY.b(0xA5) | GPTWX::GTWP.WP.b(ena);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		gptw_mgr() noexcept : base_(0), ilvl_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mode	動作モード
			@param[in]	out		出力設定
			@param[in]	freq	周期
			@param[in]	ilvl	割り込みレベル（0 なら割り込み無し）
		*/
		//-----------------------------------------------------------------//
		bool start(MODE mode, OUTPUT out, uint32_t freq, uint8_t ilvl = 0) noexcept
		{
			if(!power_mgr::turn(GPTWX::PERIPHERAL)) {
				return false;
			}

			bool nega = false;
			bool negb = false;
			bool outa = false;
			bool outb = false;
			switch(out) {
			case OUTPUT::PA:
				outa = true;
				break;
			case OUTPUT::NA:
				nega = true;
				outa = true;
				break;
			case OUTPUT::PB:
				outb = true;
				break;
			case OUTPUT::NB:
				negb = true;
				outb = true;
				break;

			case OUTPUT::PA_PB:
				outa = true;
				outb = true;
				break;
			case OUTPUT::PA_NB:
				outa = true;
				outb = true;
				negb = true;
				break;
			case OUTPUT::NA_PB:
				outa = true;
				outb = true;
				nega = true;
				break;
			case OUTPUT::NA_NB:
				outa = true;
				outb = true;
				nega = true;
				negb = true;
				break;
			}
			if(outa) {
				if(!port_map_gptw::turn(GPTWX::PERIPHERAL, port_map_gptw::channel::A, true, nega, PSEL)) {
					power_mgr::turn(GPTWX::PERIPHERAL, false);
					return false;
				}
			}
			if(outb) {
				if(!port_map_gptw::turn(GPTWX::PERIPHERAL, port_map_gptw::channel::B, true, negb, PSEL)) {
					power_mgr::turn(GPTWX::PERIPHERAL, false);
					return false;
				}
			}

			auto n = F_PCLKC / freq;
			uint8_t md = 0;
			switch(mode) {
			case MODE::PWM_S:
				md = 0b000;
				break;
			case MODE::SINGLE:
				md = 0b001;
				break;
			case MODE::PWM_T1:
				n /= 2;
				md = 0b100;
				break;
			case MODE::PWM_T2:
				n /= 2;
				md = 0b101;
				break;
			case MODE::PWM_T3:
				n /= 2;
				md = 0b110;
				break;
			}

			protect_enable_(false);
			base_ = n;
			GPTWX::GTPR = n - 1;

			GPTWX::GTCR = GPTWX::GTCR.MD.b(md) | GPTWX::GTCR.CST.b();
			GPTWX::GTIOR = GPTWX::GTIOR.OAE.b(outa) | GPTWX::GTIOR.OBE.b(outb)
				| GPTWX::GTIOR.GTIOA.b(0b00110) | GPTWX::GTIOR.GTIOB.b(0b00110);

		GPTWX::GTCCRA = n / 3;
		GPTWX::GTCCRB = n * 2 / 3;

			ilvl_ = ilvl;
			if(ilvl > 0) {

			}

			GPTWX::GTSTP = ~(1 << GPTWX::get_channel());  // 停止解除
			GPTWX::GTSTR =   1 << GPTWX::get_channel();   // 開始

			protect_enable_();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  同期
		*/
		//-----------------------------------------------------------------//
		void sync() noexcept
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A チャネルのコンペア・マッチを設定
			@param[in] value	設定値
		*/
		//-----------------------------------------------------------------//
		void set_a(uint32_t value) noexcept
		{
			protect_enable_(false);
			GPTWX::GTCCRA = value;
			protect_enable_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  B チャネルのコンペア・マッチを設定
			@param[in] value	設定値
		*/
		//-----------------------------------------------------------------//
		void set_b(uint32_t value) noexcept
		{
			protect_enable_(false);
			GPTWX::GTCCRB = value;
			protect_enable_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A チャネルの DUTY を設定 (PWM 時)
			@param[in] value	設定値(0.0 to 1.0)
		*/
		//-----------------------------------------------------------------//
		void set_duty_a(float value) noexcept
		{
			protect_enable_(false);
			GPTWX::GTCCRA = static_cast<uint32_t>(value * static_cast<float>(base_) / static_cast<float>(base_));
			protect_enable_();			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  B チャネルの DUTY を設定 (PWM 時)
			@param[in] value	設定値(0.0 to 1.0)
		*/
		//-----------------------------------------------------------------//
		void set_duty_b(float value) noexcept
		{
			protect_enable_(false);
			GPTWX::GTCCRB = static_cast<uint32_t>(value * static_cast<float>(base_) / static_cast<float>(base_));
			protect_enable_();			
		}
	};
}
