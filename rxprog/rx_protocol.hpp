#pragma once
//=====================================================================//
/*!	@file
	@brief	RX プログラミング・プロトコル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
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
	class protocol {
	public:
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
			uint32_t	OSA = 0;
			uint32_t	OSI = 0;
			uint32_t	CPA = 0;
			uint32_t	CPI = 0;

			void info(const std::string& head = "") const {
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
					※ RX63T 標準設定：　12.00MHz、8(96MHz)、4(48MHz)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct rx_t {
			bool	verbose_ = false;

			std::string	cpu_type_;		///< CPU タイプ

			uint32_t	master_ = 1200;	///< マスター・クロック（MHz 単位で、小数第２位、１００倍）
			uint32_t	sys_div_ = 8;	///< システム・ディバイダー設定
			uint32_t	ext_div_ = 4;	///< 周辺ディバイダー設定
		};
	};
}
