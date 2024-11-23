#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220/RX26T/RX62x/RX63x グループ FLASH 制御 @n
			・RX220 @n
			・RX26T @n
			・RX621/RX62N @n
			・RX631/RX63N @n
			このファイルは、「renesas.hpp」でインクルードされる前提なので、 @n
			個別にインクルードしない事。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "common/delay.hpp"
#include "common/format.hpp"

#define FIO_DEBUG

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class flash_io {

#ifdef FIO_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif
	public:
		enum class ERROR : uint8_t {
			NONE,		///< エラー無し
			START,		///< 開始不良
			CLOCK,		///< クロック設定不良
			ADDRESS,	///< アドレス不良
			LENGTH,		///< 長さ不良
			BANK,		///< バンク数不良
			TIMEOUT,	///< タイムアウト
			WRITE,		///< 書き込みエラー
			ST_ILGL,	///< ILGL ステータス検出
			ST_ERS,		///< ERS ステータス検出
			ST_PRG,		///< PRG ステータス検出
		};

		static constexpr uint32_t DATA_SIZE = FLASH::DATA_SIZE;	///< データ・フラッシュの容量
		static constexpr uint32_t DATA_BLOCK_SIZE = FLASH::DATA_BLOCK_SIZE;	///< データ・フラッシュのブロックサイズ
		static constexpr uint32_t DATA_BLOCK_NUM  = FLASH::DATA_SIZE / DATA_BLOCK_SIZE;	///< データ・フラッシュのバンク数

	private:

#if defined(SIG_RX26T)
		bool FSTATR_FRDY() noexcept { return FLASH::FSTATR.FRDY(); }
		bool FSTATR_ILGLERR() noexcept { return FLASH::FSTATR.ILGLERR(); }
		bool FSTATR_ERSERR() noexcept { return FLASH::FSTATR.ERSERR(); }
		bool FSTATR_PRGERR() noexcept { return FLASH::FSTATR.PRGERR(); }
		bool ERASE_STATE() noexcept { return FLASH::FBCSTAT.BCST() == 0; }

		void enable_read_(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
		}

		void enable_write_(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			FLASH::FSADDR = org;
			FLASH::FEADDR = org + len - 1;
		}
#else
		bool FSTATR_FRDY() noexcept { return FLASH::FSTATR0.FRDY(); }
		bool FSTATR_ILGLERR() noexcept { return FLASH::FSTATR0.ILGLERR(); }
		bool FSTATR_ERSERR() noexcept { return FLASH::FSTATR0.ERSERR(); }
		bool FSTATR_PRGERR() noexcept { return FLASH::FSTATR0.PRGERR(); }
		bool ERASE_STATE() noexcept { return FLASH::DFLBCSTAT.BCST() == 0; }
#if defined(SIG_RX220)
		void enable_read_(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			FLASH::DFLRE0 = 0x2D0F;
		}

		void enable_write_(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			FLASH::DFLWE0 = 0x2D0F;
		}
#else
		void enable_read_(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			FLASH::DFLRE0 = 0x2DFF;
			FLASH::DFLRE1 = 0xD2FF;
		}

		void enable_write_(uint32_t org, uint32_t len, bool ena = true) noexcept
		{
			FLASH::DFLWE0 = 0x2DFF;
			FLASH::DFLWE1 = 0xD2FF;
		}
#endif
#endif

		ERROR	error_;

		enum class MODE : uint8_t {
			NONE,
			RD,
			PE,
		};

		MODE	mode_;

		bool	trans_farm_;

		bool step_frdy_(uint32_t timeout_micro_sec) noexcept
		{
			while(FSTATR_FRDY() == 0) {
				utils::delay::micro_second(1);
				--timeout_micro_sec;
				if(timeout_micro_sec == 0) {
#if defined(SIG_RX26T)
					FLASH::FSUINITR = FLASH::FSUINITR.KEY.b(0x2D) | FLASH::FSUINITR.SUINIT.b(1);
#else
					// FCU 初期化
					FLASH::FRESETR.FRESET = 1;
					utils::delay::micro_second(35 * 2);  // Min: 35uS
					FLASH::FRESETR.FRESET = 0;
#endif
					return false;
				}
			}
			return true;
		}


		bool set_clock_() noexcept
		{
#if defined(SIG_RX26T)
			auto hz = clock_profile::FCLK / 1'000'000;
			if((clock_profile::FCLK % 1'000'000) != 0) ++hz;
			FLASH::FPCKAR = FLASH::FPCKAR.KEY.b(0x1E) | FLASH::FPCKAR.PCKA.b(hz);
			return true;
#else
			auto n = clock_profile::FCLK / 1'000'000;
			if((clock_profile::FCLK % 1'000'000) != 0) ++n;
			FLASH::PCKAR = n;
			FLASH::FCU_DATA_CMD8  = 0xE9;
			FLASH::FCU_DATA_CMD8  = 0x03;
			FLASH::FCU_DATA_CMD16 = 0x0F0F;
			FLASH::FCU_DATA_CMD16 = 0x0F0F;
			FLASH::FCU_DATA_CMD16 = 0x0F0F;
			FLASH::FCU_DATA_CMD8  = 0xD0;
			auto ret = step_frdy_(n / 10 + n);
			if(!ret) {
				debug_format("set_clock: timeout...\n");
			}
			return ret;
#endif
		}

		void turn_rd_() noexcept
		{
			if(mode_ == MODE::RD) {
				return;
			}

			if(!step_frdy_(20000)) {  // 20[ms]
				// timeout...
				debug_format("turn_rd_: timeout...\n");
				return;
			}

			FLASH::FENTRYR = 0xAA00;
			while(1) {
				auto tmp = FLASH::FENTRYR();
				if(tmp == 0x0000) break;
			}
			FLASH::FWEPROR = 0b10;

			mode_ = MODE::RD;
		}

		void turn_pe_() noexcept
		{
			if(mode_ == MODE::PE) {
				return;
			}

			FLASH::FENTRYR = 0xAA80;
#if defined(SIG_RX26T)
			while(FLASH::FENTRYR() != 0x0080) ;
#endif
			FLASH::FWEPROR = 0b01;

			mode_ = MODE::PE;
		}

		bool check_error_() noexcept
		{
			bool ret = false;
			if(FSTATR_ILGLERR() != 0) {
				error_ = ERROR::ST_ILGL;
				debug_format("ILGLERR..., STAT: %02X\n") % static_cast<uint16_t>(FLASH::FASTAT());
				if(FLASH::FASTAT() != 0x10) {
					FLASH::FASTAT = 0x10;
				}
				ret = true;
			}
			if(FSTATR_ERSERR() != 0) {
				error_ = ERROR::ST_ERS;
				debug_format("ERSERR...\n");
				ret = true;
			}
			if(FSTATR_PRGERR() != 0) {
				error_ = ERROR::ST_PRG;
				debug_format("PRGERR...\n");
				ret = true;
			}
			if(ret) {
				wr8_(FLASH::DATA_ORG, 0x50);
			}
			return ret;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() noexcept : error_(ERROR::NONE), mode_(MODE::NONE), trans_farm_(false)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	最終エラー型を取得
			@return 最終エラー型
		 */
		//-----------------------------------------------------------------//
		auto get_last_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	FCU を初期化して開始する
			@return 正常なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			error_ = ERROR::NONE;

			if(!trans_farm_) {
				FLASH::transfer_farm();
				trans_farm_ = true;
			}

			turn_pe_();
			if(check_error_()) {
				error_ = ERROR::START;
				debug_format("start: turn_pe_()...\n");
				return false;
			}

			auto ret = set_clock_();
			if(ret) {
				turn_rd_();
			} else {
				error_ = ERROR::CLOCK;
				debug_format("start: set_clock_()...\n");
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@return データ
		*/
		//-----------------------------------------------------------------//
		uint8_t read(uint32_t org) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return 0;
			}

			turn_rd_();
	
			enable_read_(org, 1);

			return rd8_(FLASH::DATA_ORG + org);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@param[in]	len	バイト数
			@param[out]	dst	先
			@return 読出しサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t read(uint32_t org, uint32_t len, void* dst) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return 0;
			}
			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}

			turn_rd_();

			enable_read_(org, len);

			const void* src = reinterpret_cast<const void*>(FLASH::DATA_ORG + org);
			std::memcpy(dst, src, len);
			return len;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase_check(uint32_t bank) noexcept
		{
			error_ = ERROR::NONE;

			if(bank >= DATA_BLOCK_NUM) {
				error_ = ERROR::BANK;
				debug_format("erase_check: Out of bank...\n");
				return false;
			}

			turn_pe_();

			auto cmd = FLASH::DATA_ORG + bank * FLASH::DATA_BLOCK_SIZE;
			enable_write_(cmd, FLASH::DATA_BLOCK_SIZE);
#if defined(SIG_RX26T)
#else
			FLASH::FMODR.FRDMD = FLASH::FMODR.FRDMD.b(1);
			FLASH::DFLBCCNT.BCSIZE = 1;  // setup 2K block
#endif
			wr8_(cmd, 0x71);
			wr8_(cmd, 0xD0);
			if(!step_frdy_(33 * FLASH::DATA_BLOCK_SIZE / 2)) {  // 2 bytes / 30 us x 1.1
				error_ = ERROR::TIMEOUT;
				debug_format("erase_check: time out...\n");
				return false;
			}
			if(check_error_()) {
				debug_format("erase_check: status error...\n");
				return false;
			}
			return ERASE_STATE();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase(uint32_t bank) noexcept
		{
			error_ = ERROR::NONE;

			if(bank >= DATA_BLOCK_NUM) {
				error_ = ERROR::BANK;
				debug_format("erase: Out of bank...\n");
				return false;
			}

			turn_pe_();

			auto cmd = FLASH::DATA_ORG + bank * FLASH::DATA_BLOCK_SIZE;
			enable_write_(cmd, FLASH::DATA_BLOCK_SIZE);

			wr8_(cmd, 0x20);
			wr8_(cmd, 0xD0);
			if(!step_frdy_(220000)) {  // 20 ms: 32 bytes erase 時間 x 1.1
				error_ = ERROR::TIMEOUT;
				debug_format("erase: time out...\n");
				return false;
			}
			bool ret = check_error_();
			if(ret) {
				debug_format("erase: status error...\n");
				return false;
			}
			return !ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	src ソース
			@param[in]	org	開始オフセット
			@param[in]	len	バイト数
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint32_t org, const void* src, uint32_t len) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				debug_format("write: invaild address...\n");
				return false;
			}

			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}

			if(len < FLASH::DATA_WORD_SIZE || (len % FLASH::DATA_WORD_SIZE) != 0) {
				error_ = ERROR::LENGTH;
				debug_format("write: invaild length...\n");
				return false;
			}

			turn_pe_();

			enable_write_(org, len);

			const uint8_t* p = static_cast<const uint8_t*>(src);
			uint32_t n = 0;
			uint8_t d[8];
			uint32_t i = 0;
			while(i < len) {
				d[n] = *p++;
				++n;
				if(n >= FLASH::DATA_WORD_SIZE) {
					FLASH::FCU_DATA_CMD8 = 0xE8;
					FLASH::FCU_DATA_CMD8 = FLASH::DATA_PROG_CMD_2ND;
					uint32_t j = 0;
					while(j < n) {
						wr16_(FLASH::DATA_ORG + org + i, (d[j + 1] << 8) | d[j]);
						j += 2;
						i += 2;
					}
					FLASH::FCU_DATA_CMD8 = 0xD0;
					if(!step_frdy_(20000)) {  // 2[ms]
						error_ = ERROR::TIMEOUT;
						debug_format("write: time out...\n");
						return false;
					}
					n = 0;
				}
			}
			bool ret = check_error_();
			if(ret) {
				error_ = ERROR::WRITE;
				debug_format("write: status error...\n");
				return false;
			}
			return !ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ユニーク ID 数を取得 @n
					ユニーク ID をサポートしない場合は「０」が返る。
			@return ユニーク ID 数
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_uid_num() noexcept
		{
			return FLASH::ID_NUM;
		} 


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ユニーク ID の取得 @n
					ユニーク ID をサポートしない場合、特定の ROM 領域を返す。 @n
					各マイコン「flash.hpp」を参照 
			@param[in]	idx		ID 番号（０～３）
			@return ID 値
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_uid(uint32_t idx) noexcept
		{
			switch(idx) {
			case 0:
				return FLASH::UIDR0();
			case 1:
				return FLASH::UIDR1();
			case 2:
				return FLASH::UIDR2();
			case 3:
				return FLASH::UIDR3();
			default:
				return 0;
			}
		}
	};
}
