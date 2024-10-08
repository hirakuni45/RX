#pragma once
//=========================================================================//
/*!	@file
	@brief	RX プログラミング・プロトコル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <iostream>
#include <vector>
#include <string>
#include <boost/format.hpp>

namespace rx {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct protocol {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	device 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct device {
			uint32_t	code_ = 0;
			std::string	name_;

			void info(const std::string& head = "") const {
				std::cout << head << (boost::format("Device: %s") % name_) << std::endl;
				std::cout << head << (boost::format("Device ID: 0x%0X") % code_) << std::endl;
			}
		};
		typedef std::vector<device> devices;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	device_type 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct device_type {
			uint8_t		TYP[8];
			uint32_t	OSA;
			uint32_t	OSI;
			uint32_t	CPA;
			uint32_t	CPI;

			device_type() : TYP{ 0 }, OSA(0), OSI(0), CPA(0), CPI(0) { }

			void info(const std::string& head = "") const {
				std::cout << head << "Device Type TYP:";
				for(int i = 0; i < 8; ++i) {
					std::cout << boost::format(" %02X") % static_cast<uint32_t>(TYP[i]);
				}
				std::cout << std::endl;
				std::cout << head << (boost::format("Device Type OSA: %d") % OSA) << std::endl;
				std::cout << head << (boost::format("Device Type OSI: %d") % OSI) << std::endl;
				std::cout << head << (boost::format("Device Type CPA: %d") % CPA) << std::endl;
				std::cout << head << (boost::format("Device Type CPI: %d") % CPI) << std::endl;
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	clock_mode 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct clock_mode {
			uint8_t	type_ = 0;

			void info(const std::string& head = "") const {
				std::cout << head << (boost::format("Clock Mode: 0x%02X") % static_cast<int>(type_))
					<< std::endl;
			}
		};
		typedef std::vector<clock_mode> clock_modes;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	multiplier 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct multiplier {
			typedef std::vector<uint8_t> list;
			list	list_;

			void info(const std::string& head = "") const {
				std::cout << head << "Multiplier: ";
				uint32_t i = 0;
				for(auto v : list_) {
					std::cout << static_cast<int>(v);
					++i;
					if(i < list_.size()) {
						std::cout << ", ";
					}
				}
				std::cout << std::endl;
			}
		};
		typedef std::vector<multiplier> multipliers;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	frequency 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct frequency {
			uint16_t	min_ = 0;
			uint16_t	max_ = 0;

			void info(const std::string& head = "") const {
				std::cout << head << "Frequency Min: "
					<< (static_cast<float>(min_) / 100.0f) << " MHz, Max: "
					<< (static_cast<float>(max_) / 100.0f) << " MHz"
					<< std::endl;
			}
		};
		typedef std::vector<frequency> frequencies;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	area 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct area {
			uint32_t	org_ = 0;
			uint32_t	end_ = 0;

			void info(const std::string& head = "") const {
				std::cout << head << (boost::format("Area: %08X, %08X") % org_ % end_) << std::endl;
			}
		};
		typedef std::vector<area> areas;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	block 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct block {
			uint32_t	org_ = 0;
			uint32_t	size_ = 0;
			uint32_t	num_ = 0;

			void info(const std::string& head = "") const {
				std::cout << head << (boost::format("Block: %08X, %08X, %08X") % org_ % size_ % num_) << std::endl;
			}
		};
		typedef std::vector<block> blocks;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	rx_t 構造体 @n
					※ RX62x, RX63T 標準設定：　12.00MHz、8(96MHz)、4(48MHz)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct rx_t {
			bool	verbose_ = false;

			std::string	cpu_type_;			///< CPU タイプ

			uint32_t	master_ = 1200;		///< マスター・クロック（MHz 単位で、小数第２位、１００倍）
			uint32_t	iclk_multi_ = 8;	///< インストラクション・マルチプライヤー設定
			uint32_t	pclk_multi_ = 4;	///< 周辺機器・マルチプライヤー設定

			uint8_t		id_[16] = { 0xff };	///< ID 
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	erase_page ステート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class erase_state {
			ERROR,		///< エラー
			CHECK_OK,	///< 消去チェックが OK の場合
			ERASE_OK,	///< ブロック消去が OK の場合
		};
	};
}
