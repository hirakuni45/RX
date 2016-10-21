#pragma once
//=====================================================================//
/*!	@file
	@brief	VS1063 VLSI Audio Codec ドライバー
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "G13/port.hpp"
#include "common/csi_io.hpp"
#include "common/delay.hpp"
#include "common/format.hpp"
#include "ff12a/src/ff.h"

extern "C" {
	char sci_getch(void);
	uint16_t sci_length();
}

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  VS1063 テンプレートクラス
		@param[in]	CSI	CSI(SPI) 制御クラス
		@param[in]	SEL	/xCS 制御クラス
		@param[in]	DCS /xDCS 制御クラス
		@param[in]	REQ	DREQ 入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CSI, class SEL, class DCS, class REQ>
	class VS1063 {

		CSI&	csi_;

		uint8_t	frame_;

		uint8_t buff_[256];

		/// VS1063a コマンド表
		enum class CMD {
			MODE,			///< モード制御
			STATUS,			///< ステータス
			BASS,			///< 内臓の低音／高音強調
			CLOCKF,			///< クロック周波数＋逓倍器
			DECODE_TIME,	///< 再生時間［秒］
			AUDATA,			///< 各種オーディオ・データ
			WRAM,			///< RAM リード／ライト
			WRAMADDR,		///< RAM リード／ライト・アドレス
			HDAT0,			///< ストリーム・ヘッダ・データ０
			HDAT1,			///< ストリーム・ヘッダ・データ１
			AIADDR,			///< アプリケーション開始アドレス
			VOL,			///< ボリューム制御
			AICTRL0,   		///< アプリケーション制御レジスタ０
			AICTRL1,		///< アプリケーション制御レジスタ１
			AICTRL2,		///< アプリケーション制御レジスタ２
			AICTRL3			///< アプリケーション制御レジスタ３
		};

		bool	pause_;

		inline void sleep_() { asm("nop"); }


		inline bool get_status_()
		{
			return REQ::P();
		}


		inline void wait_ready_()
		{
			while(REQ::P() == 0) sleep_();
		}


		void write_(CMD cmd, uint16_t data)
		{
			wait_ready_();

			SEL::P = 0;
			csi_.xchg(0x02);	// Write command (0x02)
			csi_.xchg(static_cast<uint8_t>(cmd));
			csi_.xchg(data >> 8);
			csi_.xchg(data & 0xff);
			SEL::P = 1;
		}


		uint16_t read_(CMD cmd)
		{
			wait_ready_();

			uint16_t data;
			SEL::P = 0;
			csi_.xchg(0x03);	// Read command (0x03)
			csi_.xchg(static_cast<uint8_t>(cmd));
			data  = static_cast<uint16_t>(CSI::xchg()) << 8;
			data |= csi_.xchg();
			SEL::P = 1;
			return data;
		}

		bool probe_mp3_(FIL* fp)
		{
			UINT len;
			if(f_read(fp, buff_, 10, &len) != FR_OK) {
				return false;
			}
			if(len != 10) {
				return false;
			}

			if(buff_[0] == 'I' && buff_[1] == 'D' && buff_[2] == '3') ;
			else {
				return false;
			}

			// skip TAG
			uint32_t ofs = static_cast<uint32_t>(buff_[6]) << 21;
			ofs |= static_cast<uint32_t>(buff_[7]) << 14;
			ofs |= static_cast<uint32_t>(buff_[8]) << 7;
			ofs |= static_cast<uint32_t>(buff_[9]);
			f_lseek(fp, ofs);

			utils::format("Find ID3 tag skip: %d\n") % ofs;

			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		VS1063(CSI& csi) : csi_(csi), frame_(0), pause_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始（初期化）
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			SEL::PM = 0;
			SEL::PU = 0;

			DCS::PM = 0;
			DCS::PU = 0;

			REQ::PM = 1;
			REQ::PU = 0;
	
			SEL::P = 1;  // /xCS = H
			DCS::P = 1;  // /xDCS = H

			uint8_t intr_level = 0;
			if(!csi_.start(500000, CSI::PHASE::TYPE4, intr_level)) {
				utils::format("CSI1 Start fail ! (Clock spped over range)\n");
				return;
			}

///	   		write_(CMD::MODE, 0x4840);
	   		write_(CMD::MODE, 0x4800);
			write_(CMD::VOL,  0x4040);  // volume

			write_(CMD::CLOCKF, 0x9800);  // 12.288MHz 
//			write_(CMD::CLOCKF, 0x8BE8);  // 12MHz OSC 補正

			utils::delay::milli_second(10);

			if(!csi_.start(8000000, CSI::PHASE::TYPE4, intr_level)) {
				utils::format("CSI1 Start fail ! (Clock spped over range)\n");
				return;
			}
			utils::delay::milli_second(10);

			set_volume(255);
		}


		//----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//----------------------------------------------------------------//
		bool service(FIL* fp)
		{
			UINT len;
			if(f_read(fp, buff_, sizeof(buff_), &len) != FR_OK) {
				return false;
			}
			if(len == 0) return false;

			const uint8_t* p = buff_;
			while(len > 0) {
				while(get_status_() == 0) ;
				uint16_t l = 32;
				if(l > len) l = len; 
				csi_.send(p, l);
				p += l;
				len -= l;
			}

			return true;
		}


		//----------------------------------------------------------------//
		/*!
			@brief  再生
			@param[in]	fp	ファイル・ディスクリプタ
			@return エラーなら「false」
		*/
		//----------------------------------------------------------------//
		bool play(FIL* fp)
		{
			if(fp == nullptr) return false;

			// ファイル・フォーマットを確認
			if(!probe_mp3_(fp)) {
				f_close(fp);
				return false;
			}

			{
				frame_ = 0;
				pause_ = false;
				DCS::P = 0;
				while(1) {
					if(!pause_) {
						if(!service(fp)) break;

						++frame_;
						if(frame_ >= 40) {
							device::P4.B3 = !device::P4.B3();
							frame_ = 0;
						}
					} else {
						if(frame_ < 192) {
							device::P4.B3 = (frame_ >> 5) & 1;
						} else {
							device::P4.B3 = 1;
						}
						utils::delay::milli_second(2);
						++frame_;
					}

					if(sci_length()) {
						auto ch = sci_getch();
						if(ch == '>') {
							break;
						} else if(ch == ' ') {
							pause_ = !pause_;
						}
					}
				}
				DCS::P = 1;
			}

			f_close(fp);

			return true;
		}


		//----------------------------------------------------------------//
		/*!
			@brief  ボリュームを設定
			@param[in]	ボリューム（２５５が最大、０が最小）
		*/
		//----------------------------------------------------------------//
		void set_volume(uint8_t vol)
		{
			vol ^= 0xff;
			write_(CMD::VOL, (vol << 8) | vol);
		}


		//----------------------------------------------------------------//
		/*!
			@brief  ボリュームを取得
			@return	ボリューム（２５５が最大、０が最小）
		*/
		//----------------------------------------------------------------//
		uint8_t get_volume()
		{
			return (read_(CMD::VOL) & 255) ^ 0xff;
		}
	};
}
