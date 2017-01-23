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
#include "common/time.h"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  NMEA デコード・クラス
		@param[in]	SCI_IO	シリアルＩ／Ｏ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI_IO>
	class nmea_dec {

	public:

		enum class BAUDRATE : uint8_t {
			B4800,
			B9600,
			B14400,
			B19200,
			B38400,
			B57600,
			B115200,
		};

		static const uint32_t sinfo_num_ = 12;		///< 衛星情報の最大数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  衛星パラメーター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct sat_info {
			char	no_[4];  	///< 衛星番号
			char	elv_[4];	///< 衛星仰角(Elevation)、０～９０度
			char	azi_[4];	///< 衛星方位角(Azimuth)、０～３５９度
			char	cn_[4];		///< キャリア／ノイズ比、０～９９dB

			sat_info() {
				no_[0] = 0;
				elv_[0] = 0;
				azi_[0] = 0;
				cn_[0] = 0;
			}
		};

	private:
		SCI_IO&		sci_;

		uint16_t	pos_;
		char		line_[128];

		char		time_[12];  // 時間
		char		lat_[12];   // 緯度(latitude)
		char		ns_[2];     // 北緯、南緯
		char		lon_[12];   // 経度(longitude)
		char		ew_[2];     // 東経、西経
		char		q_[2];      // 品質
		char		satellite_[4];  // 衛星数
		char		hq_[4];		// 水平精度低下率
		char		alt_[6];	// 海抜高度(Altitude above sea level)
		char		alt_unit_[2];	// 海抜高度単位

		char		date_[8];   // 日付

		uint16_t	sidx_;
		sat_info	sinfo_[sinfo_num_];	// 衛星情報

		uint32_t	id_;
		uint32_t	iid_;

		static uint16_t word_(const char* src)
		{
			const char* top = src;
			char ch;
			while((ch = *src++) != 0) {
				if(ch == ',' || ch == '*') return src - top;
			}
			return 0;
		}

		static void copy_word_(char* dst, const char* src, uint16_t len)
		{
			std::strncpy(dst, src, len);
			dst[len] = 0;
		}

		static int32_t get_dec_(const char* t, uint16_t n = 0)
		{
			int32_t val = 0;
			char ch;
			while((ch = *t++) != 0) {
				if('0' <= ch && ch <= '9') {
					val *= 10;
					val += ch - '0';
				} else {
					break;
				}
				if(n > 0) {
					--n;
					if(n == 0) break;
				}
			}
			return val;
		}

		bool decode_()
		{
			if(line_[0] != '$') return false;

			if(std::strncmp(&line_[1], "GPGGA,", 6) == 0) {
				const char* p = &line_[7];
				uint16_t n = 0;
				uint16_t l;
				while((l = word_(p)) != 0) {
					if(n == 0) copy_word_(time_, p, l - 1);
					else if(n == 1) copy_word_(lat_, p, l - 1);
					else if(n == 2) copy_word_(ns_, p, l - 1);
					else if(n == 3) copy_word_(lon_, p, l - 1);
					else if(n == 4) copy_word_(ew_, p, l - 1);
					else if(n == 5) copy_word_(q_, p, l - 1);
					else if(n == 6) copy_word_(satellite_, p, l - 1);
					else if(n == 7) copy_word_(hq_, p, l - 1);
					else if(n == 8) copy_word_(alt_, p, l - 1);
					else if(n == 9) copy_word_(alt_unit_, p, l - 1);
					else {
						break;
					}
					p += l;
					++n;
				}
			} else if(std::strncmp(&line_[1], "GPRMC,", 6) == 0) {
				const char* p = &line_[7];
				uint16_t n = 0;
				uint16_t l;
				while((l = word_(p)) != 0) {
					if(n == 8) copy_word_(date_, p, l - 1);
					p += l;
					++n;
				}
			} else if(std::strncmp(&line_[1], "GPGSV,", 6) == 0) {
				const char* p = &line_[7];
				uint16_t n = 0;
				uint16_t l;
				while((l = word_(p)) != 0) {
					if(n == 0) ;
					else if(n == 1) ;
// std::strncpy(date_, p, l - 1);
					p += l;
					++n;
				}
				++iid_;
			} else if(std::strncmp(&line_[1], "GPVTG,", 6) == 0) {
				++id_;
				return true;
			}
			return false;
		}

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		nmea_dec(SCI_IO& sci) : sci_(sci), pos_(0), sidx_(0), id_(0), iid_(0) {
			line_[0] = 0;
			time_[0] = 0;
			lat_[0] = 0;
			ns_[0] = 0;
			lon_[0] = 0;
			ew_[0] = 0;
			q_[0] = 0;
			satellite_[0] = 0;
			hq_[0] = 0;
			alt_[0] = 0;
			alt_unit_[0] = 0;

			date_[0] = 0;
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
            @brief  情報処理ＩＤを取得
			@return 情報処理ＩＤ
        */
        //-----------------------------------------------------------------//
		uint32_t get_iid() const { return iid_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  時間を取得
			@return 時間
        */
        //-----------------------------------------------------------------//
		const char* get_time() const { return time_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  日付を取得
			@return 日付
        */
        //-----------------------------------------------------------------//
		const char* get_date() const { return date_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  時間「time_t」を取得（グリニッチ時間）
			@return 時間「time_t」
        */
        //-----------------------------------------------------------------//
		time_t get_gmtime() const {
			tm ts;
			ts.tm_sec  = get_dec_(&time_[4], 2);
			ts.tm_min  = get_dec_(&time_[2], 2);
			ts.tm_hour = get_dec_(&time_[0], 2);
			ts.tm_mday = get_dec_(&date_[0], 2);
			ts.tm_mon  = get_dec_(&date_[2], 2) - 1;
			ts.tm_year = get_dec_(&date_[4], 2);
			ts.tm_year += 100;  // 起点１９００年
			return mktime_gmt(&ts);
		}


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
            @brief  品質を取得
			@return 品質
        */
        //-----------------------------------------------------------------//
		const char* get_quality() const { return q_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  衛星数を取得
			@return 衛星数
        */
        //-----------------------------------------------------------------//
		const char* get_satellite() const { return satellite_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  水平品質を取得
			@return 水平品質
        */
        //-----------------------------------------------------------------//
		const char* get_holizontal_quality() const { return hq_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  海抜高度を取得
			@return 海抜高度
        */
        //-----------------------------------------------------------------//
		const char* get_altitude() const { return alt_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  海抜高度単位を取得
			@return 海抜高度単位
        */
        //-----------------------------------------------------------------//
		const char* get_altitude_unit() const { return alt_unit_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  衛星情報の取得
			@param[in]	idx	衛星インデックス
			@return 衛星情報
        */
        //-----------------------------------------------------------------//
		const sat_info& get_satellite_info(uint16_t idx) const
		{
			if(idx < sinfo_num_) {
				return sinfo_[idx];
			} else {
				static sat_info si;
				return si;
			}
		}


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
            @brief  サービス @n
					情報量に応じて呼ぶ（通常毎フレーム呼ぶ）
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


		//-----------------------------------------------------------------//
		/*!
			@breif	G.P.S. のボーレートを設定
			@param[in]	bpsno	ボーレート番号
		 */
		//-----------------------------------------------------------------//
		void set_baudrate(BAUDRATE bpsno)
		{
//			"$PMTK251,38400*27\r\n"
// SUP500 GPS
#if 0
			sci_.putch(0xA0);
			sci_.putch(0xA1);
			sci_.putch(0x00);

			sci_.putch(0x04);	// メッセージ数

			sci_.putch(0x05);	// メッセージID
			sci_.putch(0x00);	// COM port 0  以外はない
			sci_.putch(bpsno); 	// 0: 4800, 1: 9600, 2: 19200, 3: 38400, 4: 57600, 5: 115200
			sci_.putch(0x00);	// 0: update to SRAM, 1: update to both SRAM & FLASH
			uint8_t sum = 0x05 ^ bpsno;
			sci_.putch(sum);

			sci_.putch(0x0D);
			sci_.putch(0x0A);
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	G.P.S. の１０Ｈｚ測位の設定@n
					※事前にボーレートを高く設定する必要がある
		 */
		//-----------------------------------------------------------------//
		void set_rate10()
		{
// $PMTK220,1000*1F<CR><LF> 1Hz
// $PMTK220, 200*2C<CR><LF> 5Hz
// $PMTK220,100*2F<CR><LF> 10Hz
// SUP500 GPS
#if 0
			sci_.putch(0xA0);
			sci_.putch(0xA1);
			sci_.putch(0x00);

			sci_.putch(0x03);

			sci_.putch(0x0E);
			sci_.putch(0x0A);
			sci_.putch(0x00);
			sci_.putch(0x04);

			sci_.putch(0x0D);
			sci_.putch(0x0A);
#endif
		}
	};
}

