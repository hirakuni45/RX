#pragma once
//=====================================================================//
/*!	@file
	@brief	NMEA デコード・クラス @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <cstring>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  NMEA デコード・クラス
		@param[in]	SCI_IO	シリアルＩ／Ｏ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI_IO>
	class nmea_dec {

		SCI_IO&		sci_;

		uint16_t	pos_;
		char		line_[128];

		char		time_[11];
		char		lat_[11];  // 緯度(latitude)
		char		ns_[2];    // 北緯、南緯
		char		lon_[11];  // 経度(longitude)
		char		ew_[2];    // 東経、西経
		char		q_[2];     // 品質
		char		satellite_[3];  // 衛星数

		uint32_t	id_;

		uint16_t word_(const char* src)
		{
			const char* top = src;
			char ch;
			while((ch = *src++) != 0) {
				if(ch == ',') return src - top;
			}
			return 0;
		}

		bool decode_()
		{
			if(line_[0] != '$') return false;
			if(std::strncmp(&line_[1], "GPGGA,", 6) == 0) {
				const char* p = &line_[7];
				uint16_t n = 0;
				uint16_t l;
				while((l = word_(p)) != 0) {
					if(n == 0) std::strncpy(time_, p, l - 1);
					else if(n == 1) std::strncpy(lat_, p, l - 1);
					else if(n == 2) std::strncpy(ns_, p, l - 1);
					else if(n == 3) std::strncpy(lon_, p, l - 1);
					else if(n == 4) std::strncpy(ew_, p, l - 1);
					else if(n == 5) std::strncpy(q_, p, l - 1);
					else if(n == 6) std::strncpy(satellite_, p, l - 1);
					else {
						++id_;
						return true;
					}
					p += l;
					++n;
				}
			}
			return false;
		}

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		nmea_dec(SCI_IO& sci) : sci_(sci), pos_(0), id_(0) {
			line_[0] = 0;
			time_[0] = 0;
			lat_[0] = 0;
			ns_[0] = 0;
			lon_[0] = 0;
			ew_[0] = 0;
			q_[0] = 0;
			satellite_[0] = 0;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  処理ＩＤを取得
			@return 処理ＩＤ
        */
        //-----------------------------------------------------------------//
		uint32_t get_id() const { return id_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  時間を取得
			@return 時間
        */
        //-----------------------------------------------------------------//
		const char* get_time() const { return time_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  緯度を取得
			@return 緯度
        */
        //-----------------------------------------------------------------//
		const char* get_lat() const { return lat_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  経度を取得
			@return 経度
        */
        //-----------------------------------------------------------------//
		const char* get_lon() const { return lon_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  衛星数を取得
			@return 衛星数
        */
        //-----------------------------------------------------------------//
		const char* get_satellite() const { return satellite_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  スタート
        */
        //-----------------------------------------------------------------//
		void start()
		{
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  サービス
			@return 更新されたら「true」
        */
        //-----------------------------------------------------------------//
		bool service()
		{
			char ch;
			bool ret = false;
			while(sci_.recv_length() > 0) {
				ch = sci_.getch();
				if(ch == 0x0d) {
					line_[pos_] = 0;
					ret = decode_();
					pos_ = 0;
				} else {
					if(ch >= ' ' && ch <= 0x7f) {
						if(pos_ < sizeof(line_)) {
							line_[pos_] = ch;
							++pos_;
						}
					}
				}
			}
			return ret;
		}
	};
}

