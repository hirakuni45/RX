#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・汎用 GPTW タイマー・マネージャー
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
			@brief  位相計数型モード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PHASE_MODE : uint8_t {
			AB_ENC,			///< 位相計数（モード１）A/B 相入力（エンコーダー入力）
			A_POS_B_DIR,	///< 位相計数（モード２）A:Positive, B:Directional
			A_NEG_B_DIR,	///< 位相計数（モード２）A:Nagative, B:Directional
			A_TRG_B_DIR,	///< 位相計数（モード２）A:Positive/Nagative, B:Directional
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力型 @n
					※反転出力は、RX66T、RX72T の場合にのみ有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class  OUTPUT : uint8_t {
			NONE,	///< 無効（出力を使用しない）

			A,		///< A を利用（GTIOCxA）
			B,		///< B を利用（GTIOCxB）
			AB,		///< AB（GTIOCxA, GTIOCxB）

			NA,		///< 反転 A を利用（GTIOCxA#）
			NB,		///< 反転 B を利用（GTIOCxB#）
			NA_B,	///< 反転 A, 正 B を利用（GTIOCxA#, GTIOCxB）
			A_NB,	///< 正 A, 反転 B を利用（GTIOCxA,  GTIOCxB#）
			NA_NB,	///< 反転 A, 反転 B を利用（GTIOCxA#, GTIOCxB#）
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW マネージャー・クラス
		@param[in]	GPTWn	GPTW[n] ユニット
		@param[in]	ITASK	割り込みタスク型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GPTWn, class ITASK = utils::null_task>
		class gptw_mgr : public gptw_base {
	public:
		typedef GPTWn value_type;

	private:
		uint32_t	freq_;
		uint32_t	base_;
		uint8_t		ilvl_;
		port_map_gptw::ORDER	ord_a_;
		port_map_gptw::ORDER	ord_b_;
		bool		buffer_;
		bool		used_;

		ICU::VECTOR	cm_vec_;

		static ITASK	itask_;

		static INTERRUPT_FUNC void intr_task_()
		{
			itask_();
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
		gptw_mgr() noexcept : freq_(0), base_(0), ilvl_(0),
			ord_a_(port_map_gptw::ORDER::BYPASS), ord_b_(port_map_gptw::ORDER::BYPASS),
			buffer_(false), used_(false),
			cm_vec_(ICU::VECTOR::NONE)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  基本動作開始
			@param[in]	mode	動作モード型
			@param[in]	out		出力型
			@param[in]	freq	周期（０はエラー）
			@param[in]	ord_a	ポート候補Ａ
			@param[in]	ord_b	ポート候補Ｂ
			@param[in]	ilvl	割り込みレベル（0 なら割り込み無し）
			@param[in]	idiv	割り込みを間引く回数（1 to 7）
			@param[in]	buffer	バッファー動作を無効にする場合「false」
			@return 設定が適正なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(MODE mode, OUTPUT out, uint32_t freq, typename port_map_gptw::ORDER ord_a, typename port_map_gptw::ORDER ord_b,
			uint8_t ilvl = 0, uint8_t idiv = 0, bool buffer = true) noexcept
		{
			if(freq == 0) {
				return false;
			}
			if(idiv > 7) {
				return false;
			}

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
			ord_a_ = ord_a;
			ord_b_ = ord_b;

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
			default:
				power_mgr::turn(GPTWn::PERIPHERAL, false);
				return false;
			}
			base_ = n;

			protect_enable_(false);

			GPTWn::GTUPSR = 0;
			GPTWn::GTDNSR = 0;

			GPTWn::GTPR = n - 1;  // +1 が周期になるので１引く

			buffer_ = buffer;
			if(buffer) {
				GPTWn::GTBER = GPTWn::GTBER.BD0.b(0) | GPTWn::GTBER.CCRA.b(0b01) | GPTWn::GTBER.CCRB.b(0b01);
			}
			GPTWn::GTCR  = GPTWn::GTCR.MD.b(md);
			GPTWn::GTIOR = GPTWn::GTIOR.OAE.b(outa) | GPTWn::GTIOR.OBE.b(outb)
				| GPTWn::GTIOR.GTIOA.b(sign_a) | GPTWn::GTIOR.GTIOB.b(sign_b);

			ilvl_ = ilvl;
			if(ilvl > 0) {  // GTPR のオーバーフローによる割り込み (V)
				if(idiv != 0) {  // 割り込み間引きカウント（１～７）
					GPTWn::GTITC = GPTWn::GTITC.IVTC.b(0b01) | GPTWn::GTITC.IVTT.b(idiv);
				}
				cm_vec_ = icu_mgr::set_interrupt(GPTWn::GTCIV, intr_task_, ilvl);
				GPTWn::GTINTAD.GTINTPR = 0b01;
			}

			GPTWn::GTCR.CST = 1;

			protect_enable_();

			used_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプットキャプチャ開始
			@param[in]	ord		ポート候補
			@param[in]	ilvl	割り込みレベル
			@return 設定が適正なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(typename port_map_gptw::ORDER ord, uint8_t ilvl = 0) noexcept
		{




			if(!power_mgr::turn(GPTWn::PERIPHERAL)) {
				return false;
			}




			used_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  位相計数開始
			@param[in]	mode	位相計数モード型
			@param[in]	ord_a	ポート候補Ａ
			@param[in]	ord_b	ポート候補Ｂ
			@return 設定が適正なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(PHASE_MODE mode, typename port_map_gptw::ORDER ord_a, typename port_map_gptw::ORDER ord_b) noexcept
		{
			uint32_t gtupsr = 0;
			uint32_t gtdnsr = 0;
			switch(mode) {
			case PHASE_MODE::AB_ENC:
				gtupsr = 0x0000'6900;
				gtdnsr = 0x0000'9600;
				break;
			case PHASE_MODE::A_POS_B_DIR:
				gtupsr = 0x0000'0200;
				gtdnsr = 0x0000'0100;
				break;
			case PHASE_MODE::A_NEG_B_DIR:
				gtupsr = 0x0000'0800;
				gtdnsr = 0x0000'0400;
				break;
			case PHASE_MODE::A_TRG_B_DIR:
				gtupsr = 0x0000'0A00;
				gtdnsr = 0x0000'0500;
				break;
			}

			if(!power_mgr::turn(GPTWn::PERIPHERAL)) {
				return false;
			}

			bool nega = false;
			bool negb = false;
			if(!port_map_gptw::turn(GPTWn::PERIPHERAL, port_map_gptw::CHANNEL::A, true, nega, ord_a)) {
				power_mgr::turn(GPTWn::PERIPHERAL, false);
				return false;
			}
			if(!port_map_gptw::turn(GPTWn::PERIPHERAL, port_map_gptw::CHANNEL::B, true, negb, ord_b)) {
				power_mgr::turn(GPTWn::PERIPHERAL, false);
				return false;
			}
			ord_a_ = ord_a;
			ord_b_ = ord_b;

			protect_enable_(false);

			GPTWn::GTCR = 0;
			GPTWn::GTIOR = 0;

			GPTWn::GTCNT = 0;
			GPTWn::GTUPSR = gtupsr;
			GPTWn::GTDNSR = gtdnsr;

			GPTWn::GTCR.CST = 1;

			protect_enable_();

			used_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	廃棄
		*/
		//-----------------------------------------------------------------//
		void destroy() noexcept
		{
			if(!used_) return;

			protect_enable_(false);

			GPTWn::GTCR.CST = 0;

			if(ilvl_ > 0) {
				GPTWn::GTINTAD.GTINTPR = 0;
				ilvl_ = 0;
				icu_mgr::set_interrupt(GPTWn::GTCIV, nullptr, ilvl_);
			}

			GPTWn::GTCR  = 0;
			GPTWn::GTIOR = 0;
			GPTWn::GTUPSR = 0;
			GPTWn::GTDNSR = 0;

			protect_enable_();

			port_map_gptw::turn(GPTWn::PERIPHERAL, port_map_gptw::CHANNEL::A, false, false, ord_a_);
			port_map_gptw::turn(GPTWn::PERIPHERAL, port_map_gptw::CHANNEL::B, false, false, ord_b_);

			power_mgr::turn(GPTWn::PERIPHERAL, false);

			used_ = false;
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
			@brief  カウンタ値を取得（位相計数モード用）
			@return GTCNT レジスタ値を取得
		*/
		//-----------------------------------------------------------------//
		int32_t get_cnt() const noexcept { return static_cast<int32_t>(GPTWn::GTCNT()); }


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

	template <class GPTWn, class ITASK> ITASK gptw_mgr<GPTWn, ITASK>::itask_;
}
