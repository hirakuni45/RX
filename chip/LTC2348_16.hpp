#pragma once
//=====================================================================//
/*!	@file
	@brief	LTC2348-16 ドライバー @n
			LTC2348/16 bits A/D コンバーター @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/delay.hpp"
#include "common/format.hpp"

/// F_ICK は速度パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_ICK
#  error "LTC2348_16.hpp requires F_ICK to be defined"
#endif

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  LTC2348-16 データ出力定義
		@param[in]	CK	SCKO 定義
		@param[in]	O0	SDO0 定義
		@param[in]	O2	SDO2 定義
		@param[in]	O4	SDO4 定義
		@param[in]	O5	SDO6 定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CK, class O0, class O2, class O4, class O6>
	struct LTC2348_SDO_t {
		typedef CK	SCKO;
		typedef O0	SDO0;
		typedef O2	SDO2;
		typedef O4	SDO4;
		typedef O6	SDO6;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  LTC2348-16 テンプレートクラス
		@param[in]	CSN		デバイス選択
		@param[in]	CNV		コンバート制御
		@param[in]	BUSY	ビジー信号
		@param[in]	PD		パワーダウン制御（1: PowerDown）
		@param[in]	SDI		制御データ
		@param[in]	SCKI	制御クロック
		@param[in]	SDO		データ出力定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CSN, class CNV, class BUSY, class PD, class SDI, class SCKI, class SDO>
	class LTC2348_16 {

		uint32_t	span_;

		uint32_t	data_[8];

		uint16_t	busy_loop_;
		uint16_t	clk_loop_;
		uint16_t	cnv_loop_;

		bool		device_;


		void get_data_loop_(uint32_t ofs, uint32_t span)
		{
			SDI::P = 0;
			uint32_t mask = 0x00800000;
			while(mask > 0) {
				data_[0 + ofs] <<= 1;
				if(SDO::SDO0::P()) ++data_[0 + ofs];
				data_[2 + ofs] <<= 1;
				if(SDO::SDO2::P()) ++data_[2 + ofs];
				data_[4 + ofs] <<= 1;
				if(SDO::SDO4::P()) ++data_[4 + ofs];
				data_[6 + ofs] <<= 1;
				if(SDO::SDO6::P()) ++data_[6 + ofs];

				volatile uint16_t l = clk_loop_ >> 1;
				while(l > 0) { --l; }
				SCKI::P = 0;

				if(span & mask) {
					SDI::P = 1;
				} else {
					SDI::P = 0;
				}
				mask >>= 1;

				volatile uint16_t h = clk_loop_ >> 1;
				while(h > 0) { --h; }
				SCKI::P = 1;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		LTC2348_16() : span_(0), busy_loop_(0), clk_loop_(0), cnv_loop_(0), device_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  スパンデータの取得
			@return スパンデータ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_span() const { return span_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスの開始 @n
					制御線を初期化して、デバイスのゆ有無を確認
			@param[in]	speed	制御クロック速度
			@param[in]	span	変換スパン
			@return デバイスが有効なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t speed, uint8_t span)
		{
			{
				uint32_t cnt = static_cast<uint32_t>(F_ICK) / speed;
				cnt /=  2;  // ループ命令によるマシンサイクル補正
				if(cnt > 65535) return false;
				clk_loop_ = cnt;
			}
			{  // BUSY loop 200ns (5MHz)
				uint32_t cnt = static_cast<uint32_t>(F_ICK) / 5000000;
				if(cnt > 65535) return false;
				busy_loop_ = cnt;
			}
			{  // tCONV: 500ns/ch 200ksps
				uint32_t cnt = static_cast<uint32_t>(F_ICK) / 200000;
				if(cnt > 65535) return false;
				cnv_loop_ = cnt;
			}

			uint32_t ss = 0;
			for(int i = 0; i < 8; ++i) {
				ss <<= 3;
				ss |= static_cast<uint32_t>(span & 7);
			}
			span_ = ss;

			CSN::DIR = 1;
			CSN::P = 1;
//			CSN::PU =1;
			CNV::DIR = 1;
			CNV::P = 0;
//			CNV::PU = 1;
			BUSY::DIR = 0;
//			BUSY::PU = 1;
			PD::DIR = 1;
			PD::P = 0;
//			PD::PU = 1;
			SDI::DIR = 1;
			SDI::P = 0;
//			SDI::PU = 1;
			SCKI::DIR = 1;
			SCKI::P = 0;
//			SCKI::PU = 1;

			SDO::SCKO::DIR = 0;
//			SDO::SCKO::PU = 1;

			SDO::SDO0::DIR = 0;
//			SDO::SDO0::PU = 1;
			SDO::SDO2::DIR = 0;
//			SDO::SDO2::PU = 1;
			SDO::SDO4::DIR = 0;
//			SDO::SDO4::PU = 1;
			SDO::SDO6::DIR = 0;
//			SDO::SDO6::PU = 1;

			utils::delay::milli_second(1);
			device_ = convert();

			return device_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスの応答確認
			@return デバイスが接続されている場合「true」
		*/
		//-----------------------------------------------------------------//
		bool probe() const {
			return device_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  変換を開始
			@return 変換正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool convert()
		{
			SCKI::P = 0;
			SDI::P = 0;

			data_[0] = 0;
			data_[1] = 0;
			data_[2] = 0;
			data_[3] = 0;
			data_[4] = 0;
			data_[5] = 0;
			data_[6] = 0;
			data_[7] = 0;

			if(BUSY::P() != 0) {
				return false;
			}

			// tBUSYLH: CNV=1 で BUSY が応答する最大時間 (max 30ns) @n
			// tCNVH: CNV 要求パルス (min 40ns)
			{
				CNV::P = 1;
				uint16_t n = busy_loop_;
				while(n > 0) {
					if(BUSY::P() == 1) {
						break;
					}
					--n;
				}
				if(n == 0) {
					CNV::P = 0;
					CSN::P = 1;
					return false;
				}
			}

			CSN::P = 0;

			// 変換待ち 最大 500ns
			{
				uint16_t n = cnv_loop_;
				while(n > 0) {
					if(BUSY::P() == 0) break;
					--n;
				}
/// 			utils::format("Conversion count: %d\n") % static_cast<int>(cnv_loop_ - n);
				CNV::P = 0;
				if(n == 0) {
					CSN::P = 1;
					return false;
				}
			}

			get_data_loop_(0, span_);
			get_data_loop_(1, 0x000000);

			CSN::P = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  変換値を取得
			@param[in]	ch	チャネル（０～７）
			@return 変換値
		*/
		//-----------------------------------------------------------------//
		uint16_t get_value(uint8_t ch) const {
			return data_[ch & 7] >> 8;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  変換値を取得
			@param[in]	ch	チャネル（０～７）
			@return 変換値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_data(uint8_t ch) const {
			return data_[ch & 7];
		}
	};
}
