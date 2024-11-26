#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220/RX26T/RX62x/RX63x/RX63T グループ FLASH 制御 @n
			・RX220 @n
			・RX26T (他と構成が異なるものの、同じ部分も多いので共有している) @n
			・RX621/RX62N @n
			・RX631/RX63N @n
			・RX63T（実装中） @n
			このファイルは、「renesas.hpp」でインクルードされる前提なので、 @n
			個別にインクルードしない事
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "RX600/flash_io_base.hpp"
#include "common/delay.hpp"

// デバッグメッセージを表示するには、以下の定義を有効にする
#define FIO_DEBUG

#ifdef FIO_DEBUG
#include "common/format.hpp"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class flash_io : public flash_io_base {

#ifdef FIO_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

	public:
		static constexpr uint32_t DATA_SIZE = FLASH::DATA_SIZE;				///< データ・フラッシュの容量
		static constexpr uint32_t DATA_BLOCK_SIZE = FLASH::DATA_BLOCK_SIZE;	///< データ・フラッシュのブロックサイズ
		static constexpr uint32_t DATA_BLOCK_NUM  = FLASH::DATA_SIZE / DATA_BLOCK_SIZE;	///< データ・フラッシュのバンク数

	private:
		enum class MODE : uint8_t {
			NONE,
			RD,
			PE,
		};
		MODE	mode_;
		ERROR	error_;
		bool	trans_farm_;

		bool step_frdy_(uint32_t timeout_micro_sec) noexcept
		{
			while(FLASH::FSTATR_FRDY() == 0) {
				utils::delay::micro_second(1);
				--timeout_micro_sec;
				if(timeout_micro_sec == 0) {
					FLASH::reset_fcu();
					return false;
				}
			}
			return true;
		}

		void turn_rd_() noexcept
		{
			if(mode_ == MODE::RD) {
				return;
			}

			if(!step_frdy_(20000)) {  // 20[ms]
				// timeout...
				debug_format("turn_rd_(): FRDY timeout...\n");
				return;
			}

			FLASH::FENTRYR = 0xAA00;
			uint32_t n = 1000;
			while(n > 0) {
				utils::delay::micro_second(1);
				if(FLASH::FENTRYR() == 0x0000) break;
				--n;
			}
			if(n == 0) {
				debug_format("turn_rd_(): check timeout...\n");
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
			uint32_t n = 1000;
			while(n > 0) {
				utils::delay::micro_second(1);
				if(FLASH::FENTRYR() == 0x0080) break;
				--n;
			}
			if(n == 0) {
				debug_format("turn_pe_(): check timeout...\n");
			}
			FLASH::FWEPROR = 0b01;

			mode_ = MODE::PE;
		}

		bool check_error_() noexcept
		{
			bool ret = false;
			if(FLASH::FSTATR_ILGLERR() != 0) {
				error_ = ERROR::ST_ILGL;
				debug_format("ILGLERR..., STAT: %02X\n") % static_cast<uint16_t>(FLASH::FASTAT());
				if(FLASH::FASTAT() != 0x10) {
					FLASH::FASTAT = 0x10;
				}
				ret = true;
			}
			if(FLASH::FSTATR_ERSERR() != 0) {
				error_ = ERROR::ST_ERS;
				debug_format("ERSERR...\n");
				ret = true;
			}
			if(FLASH::FSTATR_PRGERR() != 0) {
				error_ = ERROR::ST_PRG;
				debug_format("PRGERR...\n");
				ret = true;
			}
			if(FLASH::FASTAT.CMDLK()) {
				debug_format("CMDLK, reset status clear...\n");
				wr8_(FLASH::CODE_ORG, 0x50);
			}
			return ret;
		}

		bool erase_check_(uint32_t ofs, uint32_t len) noexcept
		{
			turn_pe_();

#if defined(SIG_RX26T)
			FLASH::FSADDR = ofs;
			FLASH::FEADDR = ofs + len;
			auto cmd = FLASH::FACI_CMD_ORG;
#else
			FLASH::enable_read(ofs, len);
			FLASH::enable_write(ofs, len);
			FLASH::FMODR.FRDMD = FLASH::FMODR.FRDMD.b(1);
			if(len <= FLASH::DATA_WORD_SIZE) {
				FLASH::DFLBCCNT = FLASH::DFLBCCNT.BCADR.b(ofs);  // setup word check
			} else {
				FLASH::DFLBCCNT = FLASH::DFLBCCNT.BCSIZE.b(1);  // setup block check
			}
			auto cmd = FLASH::DATA_ORG + ofs;
#endif

			wr8_(cmd, 0x71);
			wr8_(cmd, 0xD0);
			auto wait = (len <= FLASH::DATA_WORD_SIZE) ? FLASH::CHECK_WORD_TIME : FLASH::CHECK_BLOCK_TIME; 
			if(!step_frdy_(wait + wait / 10)) {  // wait x 1.1
				error_ = ERROR::TIMEOUT;
				debug_format("erase_check: time out...\n");
				return false;
			}
			if(check_error_()) {
				debug_format("erase_check: status error...\n");
				return false;
			}
			FLASH::enable_read(ofs, len, false);
			FLASH::enable_write(ofs, len, false);
			return FLASH::ERASE_STATE();
		}

		bool erase_(uint32_t ofs, uint32_t len) noexcept
		{
			turn_pe_();

#if defined(SIG_RX26T)
			FLASH::FSADDR = ofs;
			auto cmd = FLASH::FACI_CMD_ORG;
#else
			FLASH::enable_read(ofs, FLASH::DATA_BLOCK_SIZE);
			FLASH::enable_write(ofs, FLASH::DATA_BLOCK_SIZE);
			auto cmd = FLASH::DATA_ORG + ofs;
#endif
			wr8_(cmd, 0x20);
			wr8_(cmd, 0xD0);
			auto wait = FLASH::ERASE_BLOCK_TIME;
			if(!step_frdy_(wait + wait / 10)) {  // wait x 1.1
				error_ = ERROR::TIMEOUT;
				debug_format("erase: time out...\n");
				return false;
			}
			bool ret = check_error_();
			if(ret) {
				debug_format("erase: status error...\n");
				return false;
			}
			FLASH::enable_read(ofs, len, false);
			FLASH::enable_write(ofs, len, false);
			return !ret;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() noexcept : mode_(MODE::NONE), error_(ERROR::NONE), trans_farm_(false)
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

			FLASH::reset_fcu();

			turn_pe_();

			if(check_error_()) {
				error_ = ERROR::START;
				debug_format("start(): turn_pe_()...\n");
				return false;
			}

			auto n = clock_profile::FCLK / 1'000'000;
			if((clock_profile::FCLK % 1'000'000) != 0) ++n;
			FLASH::set_clock(n);
			auto ret = step_frdy_(n / 10 + n);
			if(ret) {
				turn_rd_();
			} else {
				error_ = ERROR::CLOCK;
				debug_format("start(): set_clock()...\n");
			}
			if(check_error_()) {
				error_ = ERROR::CLOCK;
				debug_format("start(): set_clock() status...\n");
				return false;
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
				debug_format("read(): Out of address...\n");
				return 0;
			}

			turn_rd_();
	
			FLASH::enable_read(org, 1);
			auto data = rd8_(FLASH::DATA_ORG + org);
			FLASH::enable_read(org, 1, false);
			return data;
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
				debug_format("read(): Out of address...\n");
				return 0;
			}
			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}

			turn_rd_();

			FLASH::enable_read(org, len);
			const void* src = reinterpret_cast<const void*>(FLASH::DATA_ORG + org);
			std::memcpy(dst, src, len);
			FLASH::enable_read(org, len, false);
			return len;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック（ワード単位）
			@param[in]	adrs	アドレス
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase_check_w(uint32_t adrs) noexcept
		{
			error_ = ERROR::NONE;

			if(adrs >= FLASH::DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				debug_format("erase_check_w(): Out of address...\n");
				return false;
			}
			if((adrs & (FLASH::DATA_WORD_SIZE - 1)) != 0) {
				error_ = ERROR::ADDRESS;
				debug_format("erase_check_w(): Word mod address...\n");
				return false;
			}
			return erase_check_(adrs, FLASH::DATA_WORD_SIZE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック（バンク単位）
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase_check(uint32_t bank) noexcept
		{
			error_ = ERROR::NONE;

			if(bank >= DATA_BLOCK_NUM) {
				error_ = ERROR::BANK;
				debug_format("erase_check(): Out of bank...\n");
				return false;
			}
			auto ofs = bank * FLASH::DATA_BLOCK_SIZE;
			return erase_check_(ofs, FLASH::DATA_BLOCK_SIZE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去（バンク単位）
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase(uint32_t bank) noexcept
		{
			error_ = ERROR::NONE;

			if(bank >= DATA_BLOCK_NUM) {
				error_ = ERROR::BANK;
				debug_format("erase(): Out of bank...\n");
				return false;
			}
			auto ofs = bank * FLASH::DATA_BLOCK_SIZE;
			return erase_(ofs, FLASH::DATA_BLOCK_SIZE);
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
#if defined(SIG_RX26T)
#else
			FLASH::enable_read(org, len);
			FLASH::enable_write(org, len);
#endif
			const uint8_t* p = static_cast<const uint8_t*>(src);
			uint32_t n = 0;
			uint8_t d[FLASH::DATA_WORD_SIZE];
			uint32_t i = 0;
			while(i < len) {
#if defined(SIG_RX26T)
				FLASH::FSADDR = org + i;
#endif
				d[n] = *p++;
				++n;
				if(n >= FLASH::DATA_WORD_SIZE) {
					FLASH::FCU_DATA_CMD8 = 0xE8;
					FLASH::FCU_DATA_CMD8 = FLASH::DATA_PROG_CMD_2ND;
					uint32_t j = 0;
					while(j < n) {
#if defined(SIG_RX26T)
						wr16_(FLASH::FACI_CMD_ORG, (d[j + 1] << 8) | d[j]);
#else
						wr16_(FLASH::DATA_ORG + org + i, (d[j + 1] << 8) | d[j]);
#endif
						j += 2;
						i += 2;
					}
					FLASH::FCU_DATA_CMD8 = 0xD0;
					if(!step_frdy_(FLASH::WRITE_WORD_TIME + FLASH::WRITE_WORD_TIME / 10)) {
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
			FLASH::enable_read(org, len, false);
			FLASH::enable_write(org, len, false);
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
