#pragma once
//=====================================================================//
/*!	@file
	@brief	ロータリー・エンコーダーデコード クラス @n
			※入力のプルアップ抵抗は外部に取り付ける（マイコン内蔵プルアップは、抵抗値が大きいので適さない） @n
			※外部接続の抵抗は、通常５Ｋ～１０Ｋ、ロータリーエンコーダーのマニュアルを参照
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/R8C/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ロータリー・エンコーダー ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ENCODER_BASE {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  デコード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DECODE {
			PHA_POS,		///< PHA の立ち上がりエッジで評価する
			PHA_POS_NEG,	///< PHA の立ち上がり、立下りエッジで評価する
			ALL,			///< PHA, PHB 全てのエッジで評価する
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ロータリー・エンコーダー テンプレートクラス
		@param[in]	PHA		Ａ相入力
		@param[in]	PHB		Ｂ相入力
		@param[in]	VTYPE	カウンターの型
		@param[in]	decode	デコードの仕様
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PHA, class PHB, typename VTYPE = uint32_t, ENCODER_BASE::DECODE decode = ENCODER_BASE::DECODE::PHA_POS>
	class ENCODER : public ENCODER_BASE {

		volatile VTYPE	count_;
		uint8_t	lvl_;

		uint8_t input_() { return static_cast<uint8_t>(PHA::P()) | (static_cast<uint8_t>(PHB::P()) << 1); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			PHA::DIR = 0;
			PHB::DIR = 0;
			count_ = 0;
			lvl_ = input_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス @n
					※通常割り込みから呼ばれる。 @n
					ロータリーエンコーダーのチャタリング仕様により、呼び出す周期を調整する。
		 */
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			uint8_t lvl = input_();
			uint8_t pos = ~lvl_ &  lvl;
			uint8_t neg =  lvl_ & ~lvl; 
			lvl_ = lvl;

			if((pos & 0b01) != 0) {  // A 相の立ち上がり
				if((lvl & 0b10) != 0) count_--;
				else count_++;
			}
			if(decode == DECODE::PHA_POS_NEG || decode == DECODE::ALL) {
				if((neg & 0b01) != 0) {  // A 相の立ち下がり
					if((lvl & 0b10) != 0) count_++;
					else count_--;
				}
			}
			if(decode == DECODE::ALL) {
				if((pos & 0b10) != 0) {  // B 相の立ち上がり
					if((lvl & 0b01) != 0) count_++;
					else count_--;
				}
				if((neg & 0b10) != 0) {  // B 相の立ち下がり
					if((lvl & 0b01) != 0) count_--;
					else count_++;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カウンターの取得
			@return カウンター
		 */
		//-----------------------------------------------------------------//
		auto get_count() const noexcept { return count_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	() オペレーター
		 */
		//-----------------------------------------------------------------//
		void operator () () {
			service();
		}
	};
}
