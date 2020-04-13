#pragma once
//=====================================================================//
/*! @file
	@brief  NSF Player クラス @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
// #include "main.hpp"
// #include <vector>
#include "common/file_io.hpp"
#include "common/format.hpp"

#include "emu/cpu/nes6502.h"
#include "emu/nes/nes_rom.h"
#include "emu/nes/nes_mmc.h"

namespace emu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	nesemu シーン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class nsfplay {

		struct info_t {
			char		sig_[5];		///< シグネチュア（"MESM", 0x1A）
			uint8_t		version_;		///< バージョン番号 (現在は 01h 固定)
			uint8_t		music_num_;		///< 全曲数 (1=1 全１曲, 2=2 全２曲, etc)
			uint8_t		start_no_;		///< 開始曲番号 (1=1番目の曲, 2=2番目の曲, etc)
			uint16_t	load_org_;		///< (low/high) ロード開始アドレス (8000 〜 FFFF)
			uint16_t	init_org_;		///< (low/high) 初期化開始アドレス (8000 〜 FFFF)
			uint16_t	play_org_;		///< (low/high) 曲再生開始アドレス (8000 〜 FFFF)
			char		m_name_[32];	///< 曲名（null終端文字列）
			char		m_artist_[32];	///< アーティスト名[分かっている場合のみ]（null終端文字列）
			char		m_cpr_[32];		///< 著作者情報（null終端文字列）
			uint16_t	speed_ntsc_;	///< (low/high) スピード, 1 / 1,000,000回/秒 NTSC用 (曲の再生の項目参照)
			uint8_t		init_bank_[8];	///< バンク切り替え用初期値 (後述の説明参照, FDSの項目)
			uint16_t	speed_pal_;		///< (low/high) スピード, 1 / 1,000,000回/秒 PAL用  (曲の再生の項目参照)
			uint8_t		pal_ntsc_;		///< PAL/NTSCの設定:
										///  bit 0    : 0の時、NTSCモード
										///  bit 0    : 1の時、PALモード
										///  bit 1    : 1の時、デュアルモード（PAL/NTSC）
										///  bit 2〜7 : 未使用（0で固定）
			uint8_t		ext_chip_;		///< 拡張サウンドチップサポート
										///  bit 0    : 1の時、VRCVI
										///  bit 1    : 1の時、VRCVII
										///  bit 2    : 1の時、FDS Sound
										///  bit 3    : 1の時、MMC5 audio
										///  bit 4    : 1の時、Namco 106
										///  bit 5    : 1の時、Sunsoft FME-07
										///  bit 6・7 : 将来の拡張用（0で固定）
			uint8_t		ext_[4];		///< 拡張用バイト列（0で固定）

			bool probe() const {
				if(sig_[0] == 'N' && sig_[1] == 'E' && sig_[2] == 'S' && sig_[3] == 'M' && sig_[4] == 0x1a) {
					return true;
				} else {
					return false;
				}
			}

			void list() const {
				utils::format("NSF file:\n");
				utils::format("Music Num: %d\n") % static_cast<uint32_t>(music_num_);
				utils::format("Load ORG: %04X\n") % static_cast<uint32_t>(load_org_);
				utils::format("Init ORG: %04X\n") % static_cast<uint32_t>(init_org_);
				utils::format("Play ORG: %04X\n") % static_cast<uint32_t>(play_org_);
			}
		};

		info_t		info_;

		nes6502_context* 	cpu_;
		nes6502_memread		read_handler_[MAX_MEM_HANDLERS];
		nes6502_memwrite	write_handler_[MAX_MEM_HANDLERS];

		rominfo_t			rominfo_;
		mmc_t*				mmc_;

		static uint8_t ram_read_(uint32_t address) {
///			return nes_ram_[address & (sizeof(nes_ram_) - 1)];
			return 0;
		}

		static void ram_write_(uint32_t address, uint8_t value) {
///			nes_ram_[address & (sizeof(nes_ram_) - 1)] = value;
		}

		static uint8_t read_protect_(uint32_t address) {
			return 0xFF;
		}

		static void write_protect_(uint32_t address, uint8_t value) {
		}

		void build_address_handlers_()
		{
			memset(read_handler_, 0, sizeof(read_handler_));
			memset(write_handler_, 0, sizeof(write_handler_));

			int num = 0;

			read_handler_[num].min_range = 0x0800;
			read_handler_[num].max_range = 0x1FFF;
			read_handler_[num].read_func = ram_read_;
			num++;
			read_handler_[num].min_range = 0x4000;
			read_handler_[num].max_range = 0x4015;
			read_handler_[num].read_func = apu_read;
			num++;

			const mapintf_t *intf = mmc_->intf;
#if 0
			if(intf->sound_ext) {
				if(NULL != intf->sound_ext->mem_read) {
					for(int i = 0; num < MAX_MEM_HANDLERS; i++, num++) {
						if(NULL == intf->sound_ext->mem_read[count].read_func) break;
						memcpy(&read_handler_[num], &intf->sound_ext->mem_read[count], sizeof(nes6502_memread));
					}
				}
			}
#endif
			if(NULL != intf->mem_read) {
				for(int i = 0; num < MAX_MEM_HANDLERS; i++, num++) {
					if(NULL == intf->mem_read[i].read_func) break;
					memcpy(&read_handler_[num], &intf->mem_read[i], sizeof(nes6502_memread));
				}
			}

			read_handler_[num].min_range = 0x4018;
			read_handler_[num].max_range = 0x5FFF;
			read_handler_[num].read_func = read_protect_;
			num++;
			read_handler_[num].min_range = -1;
			read_handler_[num].max_range = -1;
			read_handler_[num].read_func = NULL;


			num = 0;
			write_handler_[num].min_range = 0x0800;
			write_handler_[num].max_range = 0x1FFF;
			write_handler_[num].write_func = ram_write_;
			num++;
			write_handler_[num].min_range = 0x4000;
			write_handler_[num].max_range = 0x4013;
			write_handler_[num].write_func = apu_write;
			num++;
			write_handler_[num].min_range = 0x4015;
			write_handler_[num].max_range = 0x4015;
			write_handler_[num].write_func = apu_write;
			num++;
#if 0
			if(intf->sound_ext) {
				if(NULL != intf->sound_ext->mem_write) {
					for(count = 0; num_handlers < MAX_MEM_HANDLERS; count++, num_handlers++) {
						if(NULL == intf->sound_ext->mem_write[count].write_func) break;
						memcpy(&nes_.writehandler[num_handlers], &intf->sound_ext->mem_write[count],
							sizeof(nes6502_memwrite));
					}
				}
			}
#endif
			if(NULL != intf->mem_write) {
				for(int i = 0; num < MAX_MEM_HANDLERS; i++, num++) {
					if(NULL == intf->mem_write[i].write_func) break;
					memcpy(&write_handler_[num], &intf->mem_write[i], sizeof(nes6502_memwrite));
				}
			}

			write_handler_[num].min_range = 0x4018;
			write_handler_[num].max_range = 0x5FFF;
			write_handler_[num].write_func = write_protect_;
			num++;
			write_handler_[num].min_range = 0x8000;
			write_handler_[num].max_range = 0xFFFF;
			write_handler_[num].write_func = write_protect_;
			num++;
			write_handler_[num].min_range = -1;
			write_handler_[num].max_range = -1;
			write_handler_[num].write_func = NULL;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		nsfplay() : info_(), cpu_(nullptr) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	filename	ファイル名
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool open(const char* filename)
		{
			utils::file_io fi;
			if(!fi.open(filename, "rb")) {
				return false;
			}

			auto fsz = fi.get_file_size();

			if(fi.read(&info_, 128) != 128) {
				return false;
			}

			if(!info_.probe()) {
				return false;
			}

			uint32_t csz = fsz - 128;
			uint8_t* code = (uint8_t*)malloc(csz);	
			if(fi.read(code, csz) != csz) {
				return false;
			}

			info_.list();

			rominfo_.rom = code;
			rominfo_.vrom = nullptr;
			rominfo_.sram = (uint8_t*)malloc(0x800);
			rominfo_.vram = nullptr;

			rominfo_.rom_banks = csz / 0x4000;
			rominfo_.vrom_banks = 0;
			rominfo_.sram_banks = 2;  // 0x800 / 0x400
			rominfo_.vram_banks = 0;

			rominfo_.mapper_number = 0;

			nes6502_init();
			cpu_ = nes6502_getcontext();

			mmc_create(&rominfo_);
			mmc_ = mmc_getcontext();

			cpu_->mem_page[0] = rominfo_.sram;
			cpu_->read_handler  = read_handler_;
			cpu_->write_handler = write_handler_;

			nes6502_setup_page();

			build_address_handlers_();

			nes6502_reset();

			return true;
		}

	};
}
