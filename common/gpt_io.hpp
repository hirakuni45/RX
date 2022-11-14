#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・GPT I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 基本クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct gpt_io_base {

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
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GPT,
		port_map_gpt::ORDER ASEL = port_map_gpt::ORDER::FIRST,
		port_map_gpt::ORDER BSEL = port_map_gpt::ORDER::FIRST>
	class gpt_io : public gpt_io_base {
	public:
		typedef typename GPT::CHANNEL CHANNEL;

	private:
//		MTASK		mtask_;

		uint32_t	freq_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		gpt_io() noexcept : freq_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  有効ビットに対する周波数を求める
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
			@param[in]	freq	PWM 周波数[Hz]
			@param[in]	outa	A 出力タイプ
			@param[in]	outb	B 出力タイプ
			@param[in]	intr	割り込みレベル（0: ポーリング）
			@return エラーが無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, OUTPUT outa, OUTPUT outb, uint8_t intr = 0) noexcept
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

			GPT::GTIOR.GTIOA = static_cast<uint8_t>(outa);
			GPT::GTONCR = GPT::GTONCR.OAE.b(ena);
			GPT::GTCCRA = 0;
			GPT::GTIOR.GTIOB = static_cast<uint8_t>(outb);
			GPT::GTONCR = GPT::GTONCR.OBE.b(enb);
			GPT::GTCCRB = 0;

			GPT::GTUDC = GPT::GTUDC.UD.b() | GPT::GTUDC.UDF.b(); // UP カウント設定

			uint8_t md = 0b000;
			GPT::GTCR = GPT::GTCR.MD.b(md) | GPT::GTCR.TPCS.b(shift) | GPT::GTCR.CCLR.b(0);
			GPT::GTPR = pr - 1;

			if(intr > 0) {

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
			@brief	周期を取得
			@param[in]	real	「true」にした場合、実際に設定された周波数
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_rate(bool real = false) const noexcept
		{
			if(real) {
				uint32_t rate = (GPT::PCLK >> GPT::GTCR.TPCS()) / (GPT::PR() + 1);
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
			GPT::enable(false);
			port_map_gpt::turn(GPT::PERIPHERAL, port_map_gpt::CHANNEL::A, false, ASEL);
			port_map_gpt::turn(GPT::PERIPHERAL, port_map_gpt::CHANNEL::B, false, BSEL);
			power_mgr::turn(GPT::PERIPHERAL, false);
			freq_ = 0;
		}
	};
}
