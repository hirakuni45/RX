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
			@brief  動作モード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MODE : uint8_t {
			PWM_S_HL,		///< のこぎり波 PWM (AB: H --> L) 
			PWM_S_LH,		///< のこぎり波 PWM (AB: L --> H)
			PWM_S_HL_LH,	///< のこぎり波 PWM (A: H --> L, B: L --> H)
			PWM_S_LH_HL,	///< のこぎり波 PWM (A: L --> H, B: H --> L)
			SINGLE,			///< ワンショット・パルス
			PWM_T1,			///< 三角波 PWM 1（谷32ビット転送）
			PWM_T2,			///< 三角波 PWM 2（山/谷32ビット転送）
			PWM_T3,			///< 三角波 PWM 3（谷64ビット転送）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力型 @n
					※反転出力は、RX66T、RX72T の場合にのみ有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class  OUTPUT : uint8_t {
			NONE,	///< 無効

			A,		///< A を利用
			B,		///< B を利用
			AB,		///< AB

			NA,		///< 反転 A を利用
			NB,		///< 反転 B を利用
			NA_B,	///< 反転 A, 正 B を利用
			A_NB,	///< 正 A, 反転 B を利用
			NA_NB,	///< 反転 A, 反転 B を利用
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW マネージャー・クラス
		@param[in]	GPTWn	GPTW[n] ユニット
		@param[in]	CMTASK	コンペアマッチタスク型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GPTWn, class CMTASK = utils::null_task>
		class gptw_mgr : public gptw_base {
	public:
		typedef GPTWn value_type;

	private:
		// ※必要なら、実装する
		void sleep_() { }

		uint32_t	freq_;
		uint32_t	base_;
		uint8_t		ilvl_;
		bool		buffer_;
		ICU::VECTOR	cm_vec_;

		static CMTASK	cmtask_;

		static INTERRUPT_FUNC void cmp_match_task_()
		{
			cmtask_();
		}


		void protect_enable_(bool ena = true) noexcept
		{
			GPTWn::GTWP = GPTWn::GTWP.PRKEY.b(0xA5) | GPTWn::GTWP.WP.b(ena);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		gptw_mgr() noexcept : freq_(0), base_(0), ilvl_(0), buffer_(false), cm_vec_(ICU::VECTOR::NONE)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mode	動作モード
			@param[in]	out		出力型
			@param[in]	freq	周期
			@param[in]	ord_a	ポート候補Ａ
			@param[in]	ord_b	ポート候補Ｂ
			@param[in]	ilvl	割り込みレベル（0 なら割り込み無し）
			@param[in]	buffer	バッファー動作を無効にする場合「false」
			@return 設定が適正なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(MODE mode, OUTPUT out, uint32_t freq, typename port_map_gptw::ORDER ord_a, typename port_map_gptw::ORDER ord_b,
			uint8_t ilvl = 0, bool buffer = true) noexcept
		{
			if(freq == 0) return false;

			if(!power_mgr::turn(GPTWn::PERIPHERAL)) {
				return false;
			}

			bool outa = false;
			bool outb = false;
			bool nega = false;
			bool negb = false;
			switch(out) {
			case OUTPUT::NONE:
				break;
			case OUTPUT::A:
				outa = true;
				break;
			case OUTPUT::B:
				outb = true;
				break;
			case OUTPUT::AB:
				outa = true;
				outb = true;
				break;
			case OUTPUT::NA:
				outa = true;
				nega = true;
				break;
			case OUTPUT::NB:
				outb = true;
				negb = true;
				break;
			case OUTPUT::NA_B:
				outa = outb = true;
				nega = true;
				break;
			case OUTPUT::A_NB:
				outa = outb = true;
				negb = true;
				break;
			case OUTPUT::NA_NB:
				outa = outb = true;
				nega = negb = true;
				break;
			}
			if(outa) {
				if(!port_map_gptw::turn(GPTWn::PERIPHERAL, port_map_gptw::CHANNEL::A, true, nega, ord_a)) {
					power_mgr::turn(GPTWn::PERIPHERAL, false);
					return false;
				}
			}
			if(outb) {
				if(!port_map_gptw::turn(GPTWn::PERIPHERAL, port_map_gptw::CHANNEL::B, true, negb, ord_b)) {
					power_mgr::turn(GPTWn::PERIPHERAL, false);
					return false;
				}
			}

			freq_ = freq;
			auto n = GPTWn::PCLK / freq;
			if(n == 0) {
				power_mgr::turn(GPTWn::PERIPHERAL, false);
				return false;
			}
			uint8_t md = 0;
			uint8_t sign_a = 0;
			uint8_t sign_b = 0;
			switch(mode) {
			case MODE::PWM_S_HL:
				md = 0b000;
				sign_a = 0b01001;
				sign_b = 0b01001;
				break;
			case MODE::PWM_S_LH:
				md = 0b000;
				sign_a = 0b00110;
				sign_b = 0b00110;
				break;
			case MODE::PWM_S_HL_LH:
				md = 0b000;
				sign_a = 0b01001;
				sign_b = 0b00110;
				break;
			case MODE::PWM_S_LH_HL:
				md = 0b000;
				sign_a = 0b00110;
				sign_b = 0b01001;
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
			base_ = n;

			protect_enable_(false);
			GPTWn::GTPR = n - 1;  // +1 が周期になるので１引く

			buffer_ = buffer;
			if(buffer) {
				GPTWn::GTBER = GPTWn::GTBER.BD0.b(0) | GPTWn::GTBER.CCRA.b(0b01) | GPTWn::GTBER.CCRB.b(0b01);
			}
			GPTWn::GTCR  = GPTWn::GTCR.MD.b(md) | GPTWn::GTCR.CST.b();
			GPTWn::GTIOR = GPTWn::GTIOR.OAE.b(outa) | GPTWn::GTIOR.OBE.b(outb)
				| GPTWn::GTIOR.GTIOA.b(sign_a) | GPTWn::GTIOR.GTIOB.b(sign_b);

			ilvl_ = ilvl;
			if(ilvl > 0) {
				cm_vec_ = icu_mgr::set_interrupt(GPTWn::GTCIV, cmp_match_task_, ilvl);
				GPTWn::GTINTAD.GTINTPR = 0b01;
			}

			GPTWn::GTSTP = ~(1 << GPTWn::CHANNEL_NO);  // 停止解除
			GPTWn::GTSTR =   1 << GPTWn::CHANNEL_NO;   // 開始

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
			if(ilvl_ > 0) {

			} else {

			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルのコンペア・マッチ、リミットを取得
			@return リミットを値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_base() const noexcept { return base_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  A チャネルのコンペア・マッチを設定
			@param[in] value	設定値
		*/
		//-----------------------------------------------------------------//
		void set_a(uint32_t value) noexcept
		{
			protect_enable_(false);
			if(buffer_) {
				GPTWn::GTCCRC = value - 1;
			} else {
				GPTWn::GTCCRA = value - 1;
			}
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
			if(buffer_) {
				GPTWn::GTCCRE = value - 1;
			} else {
				GPTWn::GTCCRB = value - 1;
			}
			protect_enable_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A チャネルの DUTY を設定 (PWM 時) @n
					※浮動小数点のレンジに注意する事
			@param[in] value	設定値(0.0 to 1.0)
		*/
		//-----------------------------------------------------------------//
		void set_duty_a(float value) noexcept
		{
			protect_enable_(false);
			auto n = static_cast<uint32_t>(value * static_cast<float>(base_)) - 1;
			if(buffer_) {
				GPTWn::GTCCRC = n;
			} else {
				GPTWn::GTCCRA = n;
			}
			protect_enable_();			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  B チャネルの DUTY を設定 (PWM 時) @n
					※浮動小数点のレンジに注意する事
			@param[in] value	設定値(0.0 to 1.0)
		*/
		//-----------------------------------------------------------------//
		void set_duty_b(float value) noexcept
		{
			protect_enable_(false);
			auto n = static_cast<uint32_t>(value * static_cast<float>(base_)) - 1;
			if(buffer_) {
				GPTWn::GTCCRE = n;
			} else {
				GPTWn::GTCCRB = n;
			}
			protect_enable_();			
		}
	};

	template <class GPTWn, class CMTASK> CMTASK gptw_mgr<GPTWn, CMTASK>::cmtask_;
}
