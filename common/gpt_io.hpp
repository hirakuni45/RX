#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ GPT 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct gpt_io_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TYPE : uint8_t {
			NORMAL,		///< 標準型
			BUFFER,		///< A/B バッファー動作
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプット型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OUTPUT : uint8_t {
			NONE        = 0,		///< 出力しない
			LOW_TO_HIGH = 0b001010,	///< 初期０で、マッチで１
			HIGH_TO_LOW = 0b011001,	///< 初期１で、マッチで０
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT I/O 制御クラス
		@param[in]	GPT		GPTx デバイス・クラス
		@param[in]	ASEL	GTIOA ポートオーダー
		@param[in]	BSEL	GTIOB ポートオーダー
		@param[in]	TASK	GTPR 割り込みタスク（ファンクタ）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GPT,
		port_map_gpt::ORDER ASEL = port_map_gpt::ORDER::FIRST,
		port_map_gpt::ORDER BSEL = port_map_gpt::ORDER::FIRST,
		class TASK = utils::null_task>
	class gpt_io : public gpt_io_base {

		static TASK		task_;

		uint32_t	freq_;

		uint8_t		intr_lvl_;
		ICU::VECTOR	intr_vec_;

		static INTERRUPT_FUNC void pr_task_()
		{
			task_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		gpt_io() noexcept :
			freq_(0),
			intr_lvl_(0), intr_vec_(ICU::VECTOR::NONE)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  有効ビットに対する周波数を求める @n
					Ex: bits_to_freq(10);  // 10 ビット(1024 分周)に対する周波数
			@param[in]	bits	有効ビット数
			@return	周波数
		*/
		//-----------------------------------------------------------------//
		static uint32_t bits_to_freq(uint32_t bits) noexcept
		{
			return GPT::PCLK / (1 << bits);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始 (PWM)
			@param[in]	type	動作型
			@param[in]	freq	PWM 周波数[Hz]
			@param[in]	outa	A 出力タイプ
			@param[in]	outb	B 出力タイプ
			@param[in]	intr	割り込みレベル（0: ポーリング）
			@return エラーが無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(TYPE type, uint32_t freq, OUTPUT outa, OUTPUT outb, uint8_t intr = 0) noexcept
		{
			uint32_t pr = GPT::PCLK / freq;
			uint8_t shift = 0;
			if(pr > 65535) {
				pr >>= 1;
				++shift;
			}
			if(pr == 0 || shift > 3) {  // 分周器の能力を超えた場合
				return false;
			}

			if(!power_mgr::turn(GPT::PERIPHERAL)) {
				return false;
			}
			freq_ = freq;

			auto ena = outa != OUTPUT::NONE;
			if(!port_map_gpt::turn(GPT::PERIPHERAL, port_map_gpt::CHANNEL::A, ena, ASEL)) {
				return false;
			}
			auto enb = outb != OUTPUT::NONE;
			if(!port_map_gpt::turn(GPT::PERIPHERAL, port_map_gpt::CHANNEL::B, enb, BSEL)) {
				return false;
			}

			GPT::GTUDC = 3;
			GPT::GTUDC = 1; // UP カウント設定

			uint8_t md = 0b000;
			GPT::GTCR = GPT::GTCR.MD.b(md) | GPT::GTCR.TPCS.b(shift) | GPT::GTCR.CCLR.b(0);
			GPT::GTPR = pr - 1;
			GPT::GTCNT = 0;
			GPT::GTCCRA = 0;
			GPT::GTCCRB = 0;

			GPT::GTIOR.GTIOA = static_cast<uint8_t>(outa);
			GPT::GTIOR.GTIOB = static_cast<uint8_t>(outb);
			GPT::GTONCR = GPT::GTONCR.OBE.b(enb) | GPT::GTONCR.OAE.b(ena);

			if(intr > 0) {
				intr_lvl_ = intr;
				intr_vec_ = icu_mgr::set_interrupt(GPT::GTCIV, pr_task_, intr_lvl_);
				if(intr_vec_ != ICU::VECTOR::NONE) {
					GPT::GTITC.IVTT = 0;  // 間引き回数
					GPT::GTITC.IVTC = 0b00;
					GPT::GTINTAD.GTINTPR = 0b01;
				}
			}

			GPT::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  Ａレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_a(uint16_t n) noexcept { GPT::GTCCRA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  Ｂレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_b(uint16_t n) noexcept { GPT::GTCCRB = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  Ｃレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_c(uint16_t n) noexcept { GPT::GTCCRC = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  Ｄレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_d(uint16_t n) noexcept { GPT::GTCCRD = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  Ｅレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_e(uint16_t n) noexcept { GPT::GTCCRE = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＦレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_f(uint16_t n) noexcept { GPT::GTCCRF = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスターＡ設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_ad_a(uint16_t n) noexcept { GPT::GTADTRA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスターＢ設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_ad_b(uint16_t n) noexcept { GPT::GTADTRB = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief	出力遅延を許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable_delay(bool ena = true) noexcept
		{
			GPT::GTDLYCR = GPT::GTDLYCR.DLLEN.b(ena) | GPT::GTDLYCR.DLYEN.b(ena); 
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	出力遅延をリセット
		*/
		//-----------------------------------------------------------------//
		void reset_delay() noexcept
		{
			GPT::GTDLYCR.DLYRST = 1;
			GPT::GTDLYRA = 0;
			GPT::GTDLYFA = 0;
			GPT::GTDLYRB = 0;
			GPT::GTDLYFB = 0;
			GPT::GTDLYCR.DLYRST = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	出力 A 立ち上がり出力遅延設定
			@param[in]	n	値（PCLK の 1/n）
		*/
		//-----------------------------------------------------------------//
		void set_positive_delay_a(uint16_t n) noexcept { GPT::GTDLYRA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief	出力 A 立ち下がり出力遅延設定
			@param[in]	n	値（PCLK の 1/n）
		*/
		//-----------------------------------------------------------------//
		void set_negative_delay_a(uint16_t n) noexcept { GPT::GTDLYFA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief	出力 B 立ち上がり出力遅延設定
			@param[in]	n	値（PCLK の 1/n）
		*/
		//-----------------------------------------------------------------//
		void set_positive_delay_b(uint16_t n) noexcept { GPT::GTDLYRB = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief	出力 B 立ち下がり出力遅延設定
			@param[in]	n	値（PCLK の 1/n）
		*/
		//-----------------------------------------------------------------//
		void set_negative_delay_b(uint16_t n) noexcept { GPT::GTDLYFB = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief	周期を取得
			@param[in]	real	「true」にした場合、実際に設定された周波数
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_rate(bool real = false) const noexcept
		{
			if(real) {
				uint32_t rate = (GPT::PCLK >> GPT::GTCR.TPCS()) / (GPT::GTPR() + 1);
				return rate;
			} else {
				return freq_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  停止
		*/
		//-----------------------------------------------------------------//
		void stop() noexcept
		{
			GPT::GTINTAD = 0;
			GPT::enable(false);
			// icu_mgr::set_interrupt(GPT::GTCIV, , 0);
			port_map_gpt::turn(GPT::PERIPHERAL, port_map_gpt::CHANNEL::A, false, ASEL);
			port_map_gpt::turn(GPT::PERIPHERAL, port_map_gpt::CHANNEL::B, false, BSEL);
			power_mgr::turn(GPT::PERIPHERAL, false);
			freq_ = 0;
			intr_lvl_ = 0;
			intr_vec_ = ICU::VECTOR::NONE;
		}
	};
}
