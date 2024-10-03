#pragma once
//=====================================================================//
/*!	@file
	@brief	NMEA デコード・クラス（GPS 測位コードパース）@n
			for GTPA013 @n
			初期ボーレートは９６００で行う。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include <cstring>
#include "common/time.h"
#include "common/format.hpp"
#include "common/input.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  NMEA デコード・クラス
		@param[in]	SCI_IO	シリアルＩ／Ｏ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI_IO>
	class nmea_dec {

		static constexpr uint32_t FAST_BAUDRATE = 57600;
		static constexpr uint32_t UPDATE_FAST_RATE = 10;	///< 10Hz

	public:
		static constexpr uint32_t SINFO_MAX = 14;		///< 衛星情報の最大数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  衛星パラメーター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct sat_info {
			char	no_[4] ;  		///< 衛星番号
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

		uint16_t	sci_errc_;

		uint16_t	pos_;
		char		line_[256];

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
		sat_info	sinfo_[SINFO_MAX];	// 衛星情報

		uint32_t	id_;
		uint32_t	iid_;

		device::ICU::LEVEL	intr_;
		uint16_t	update_real_rate_;
		uint16_t	update_fast_rate_;
		uint16_t	no_recv_cnt_;
		uint32_t	baud_real_rate_;
		uint32_t	baud_fast_rate_;

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


		bool parse_()
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
			} else if(std::strncmp(&line_[1], "GPGSV,", 6) == 0) {  // 衛星情報
				const char* p = &line_[7];
				uint16_t sidx = 0;
				uint16_t n = 0;
				uint16_t l;
				while((l = word_(p)) != 0) {
					if(n == 1) {
						char tmp[4];
						copy_word_(tmp, p, l - 1);
						sidx = get_dec_(tmp);
						sidx *= 4;
					} else if(n >= 3) {
						if(*(p - 1) == '*') break;
						auto& t = sinfo_[sidx % SINFO_MAX];
						auto mod = (n - 3) % 4;
						if(mod == 0) {
							copy_word_(t.no_, p, l - 1);
						} else if(mod == 1) copy_word_(t.elv_, p, l - 1);
						else if(mod == 2) copy_word_(t.azi_, p, l - 1);
						else if(mod == 3) {
							copy_word_(t.cn_, p, l - 1);
							++sidx;
						}
					}
					p += l;
					++n;
				}
				++iid_;
			} else if(std::strncmp(&line_[1], "GPVTG,", 6) == 0) {
				++id_;
				return true;
			} else {
//				utils::format("ND: '%s'\n") % line_;
			}
			return false;
		}


		static uint8_t sum_(const char* str)
		{
			if(*str == '$') ++str;
			char ch;
			uint8_t sum = 0;
			while((ch = *str) != 0) {
				if(ch == '*') break;
				sum ^= static_cast<uint8_t>(ch);
				++str;
			}
			return sum;
		}


		void init_()
		{
			no_recv_cnt_ = 0;
			sci_.auto_crlf(false);
			line_[0] = 0;
			pos_ = 0;
		}

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		nmea_dec(SCI_IO& sci) noexcept : sci_(sci), sci_errc_(0), pos_(0), line_{ 0 },
			time_{ 0 }, lat_{ 0 }, ns_{ 0 }, lon_{ 0 },
			ew_{ 0 }, q_{ 0 }, satellite_{ 0 }, hq_{ 0 },
			alt_{ 0 }, alt_unit_{ 0 }, date_{ 0 },
			sidx_(0), id_(0), iid_(0), intr_(device::ICU::LEVEL::NONE),
			update_real_rate_(0), update_fast_rate_(0),
			no_recv_cnt_(0),
			baud_real_rate_(0), baud_fast_rate_(0)
		{ }


        //-----------------------------------------------------------------//
        /*!
            @brief  処理ＩＤを取得
			@return 処理ＩＤ
        */
        //-----------------------------------------------------------------//
		uint32_t get_id() const noexcept { return id_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  情報処理ＩＤを取得
			@return 情報処理ＩＤ
        */
        //-----------------------------------------------------------------//
		uint32_t get_iid() const noexcept { return iid_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  時間を取得 (hhmmss.ss) 000000.00 to 235959.99
			@return 時間
        */
        //-----------------------------------------------------------------//
		const char* get_time() const noexcept { return time_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  日付を取得 (ddmmyy)
			@return 日付
        */
        //-----------------------------------------------------------------//
		const char* get_date() const noexcept { return date_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  GMT 時間「time_t」を取得（グリニッチ標準時間）
			@return 時間「time_t」
        */
        //-----------------------------------------------------------------//
		time_t get_gmtime() const noexcept {
			if(time_[0] == 0) {
				return 0;
			}
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
            @brief  緯度を取得 (dddmm.mmmm)
			@return 緯度
        */
        //-----------------------------------------------------------------//
		const char* get_lat() const noexcept { return lat_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  経度を取得 (dddmm.mmmm)
			@return 経度
        */
        //-----------------------------------------------------------------//
		const char* get_lon() const noexcept { return lon_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  軽度、緯度情報を、google などで使える形式に変換
			@param[in]	src	ddmm.mmmm 度形式
			@param[out]	up	ddd 度表記
			@param[out]	dn	.dddd 度表記
			@return 成功なら「true」
        */
        //-----------------------------------------------------------------//
		static bool conv_latlon(const char* src, int32_t& up, int32_t& dn) noexcept
		{
			const char* p = strchr(src, '.');
			if(p == nullptr) return false;
			if((p - src) < 3) return false;
			p -= 2;
			char tmp[8];
			strncpy(tmp, src, p - src);
			tmp[p - src] = 0;
			if(!(utils::input("%d", tmp) % up).status()) {
				return false;
			}

			tmp[0] = p[0];
			tmp[1] = p[1];
			tmp[2] = p[3];
			tmp[3] = p[4];
			tmp[4] = p[5];
			tmp[5] = p[6];
			tmp[6] = 0;
			if(!(utils::input("%d", tmp) % dn).status()) {
				return false;
			}
			dn /= 60;
			return true;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  軽度、緯度情報を、google などで使える形式に変換
			@param[in]	src	ddmm.mmmm 度形式
			@param[out]	dst	ddd.dddd 度表記
			@param[in]	len	dst のサイズ
			@return 成功なら「true」
        */
        //-----------------------------------------------------------------//
		static bool conv_latlon(const char* src, char* dst, uint32_t len) noexcept
		{
			if(src == nullptr || dst == nullptr || len < 8) return false;

			int32_t up = 0;
			int32_t dn = 0;
			auto ret = conv_latlon(src, up, dn);
			utils::sformat("%d.%d", dst, len) % up % dn;
			return ret;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  品質を取得
			@return 品質
        */
        //-----------------------------------------------------------------//
		const char* get_quality() const noexcept { return q_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  衛星数を取得
			@return 衛星数
        */
        //-----------------------------------------------------------------//
		int get_satellite_num() const noexcept
		{
			int n = 0;
			utils::input("%d", satellite_) % n;
			return n;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  水平品質を取得
			@return 水平品質
        */
        //-----------------------------------------------------------------//
		const char* get_holizontal_quality() const noexcept { return hq_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  海抜高度を取得
			@return 海抜高度
        */
        //-----------------------------------------------------------------//
		const char* get_altitude() const noexcept { return alt_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  海抜高度単位を取得
			@return 海抜高度単位
        */
        //-----------------------------------------------------------------//
		const char* get_altitude_unit() const noexcept { return alt_unit_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  衛星情報の取得
			@param[in]	idx	衛星インデックス
			@return 衛星情報
        */
        //-----------------------------------------------------------------//
		const sat_info& get_satellite_info(uint16_t idx) const noexcept
		{
			if(idx < SINFO_MAX) {
				return sinfo_[idx];
			} else {
				static sat_info si;
				return si;
			}
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  GPS 情報の表示
        */
        //-----------------------------------------------------------------//
		void list_all() const noexcept
		{
			utils::format("ID: %d, IID: %d %s %s\n")
				% get_id() % get_iid() % get_date() % get_time();
			char lat[10];
			if(!conv_latlon(get_lat(), lat, sizeof(lat))) {
				return;
			}
			char lon[10];
			if(!conv_latlon(get_lon(), lon, sizeof(lon))) {
				return;
			}
			utils::format("(%d)LatLon: %s,%s (%s m)\n")
				% get_satellite_num() % lat % lon % get_altitude();
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  スタート @n
					・開始時はボーレートは「９６００ＢＰＳ」になっている。@n
					・GPS モジュールがバッテリーバックアップされている場合、@n
					最後に設定したボーレートになっている可能性がある。
			@param[in]	intr	シリアルの割り込みレベル
			@param[in]	fast	高速ボーレート
			@param[in]	rate	更新レート（最大１０Ｈｚ）
        */
        //-----------------------------------------------------------------//
		void start(device::ICU::LEVEL intr = device::ICU::LEVEL::_1, uint32_t fast = FAST_BAUDRATE, uint16_t rate = 10) noexcept
		{
			intr_ = intr;
			baud_real_rate_ = 9600;
			baud_fast_rate_ = fast;
			update_real_rate_ = 1;
			update_fast_rate_ = rate;
			init_();
			sci_.start(baud_real_rate_, intr);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  サービス @n
					情報量に応じて呼ぶ（通常毎フレーム呼ぶ）
			@return 更新されたら「true」
        */
        //-----------------------------------------------------------------//
		bool service() noexcept
		{
			auto errc = sci_.get_fer_count();
			if(errc != sci_errc_) {
				sci_errc_ = errc;
				sci_.flush_recv();
				++no_recv_cnt_;
				if(no_recv_cnt_ >= (60 * 5)) {  // ５秒間受信が無い場合、ボーレートを変更
					if(baud_real_rate_ == 9600) {  // 9600 で通信出来てないので、高速になってるかも
//						sci_.start(baud_fast_rate_, intr_);
//						init_();
//						baud_real_rate_ = baud_fast_rate_;
					}
					no_recv_cnt_ = 0;
				}
				return false;
			}

			bool ret = false;
			auto len = sci_.recv_length();
			if(len > 0) {
				if(baud_real_rate_ == 9600) {  // 9600 で通信出来てる場合、高速にキック
//					set_baudrate(baud_fast_rate_);
				}
			}
			no_recv_cnt_ = 0;
			while(len > 0) {
				auto ch = sci_.getch();
				if(ch == 0x0d) {
					line_[pos_] = 0;
					ret = parse_();
					pos_ = 0;
				} else {
					if(ch >= ' ' && ch <= 0x7f) {  // CTRL コードは無視する。
						if(pos_ < (sizeof(line_) - 1)) {
							line_[pos_] = ch;
							++pos_;
						} else {
							pos_ = 0;
						}
					}
				}
				--len;
			}
			if(ret && baud_real_rate_ == baud_fast_rate_) {  // fast rate なら、10Hz にする。
				if(update_real_rate_ == 1) {
///					set_update_rate(UPDATE_FAST_RATE);
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	G.P.S. のボーレートを設定
			@param[in]	baud	ボーレート
		 */
		//-----------------------------------------------------------------//
		void set_baudrate(uint32_t baud) noexcept
		{
//			"PMTK251,9600",
//			"PMTK251,14400",
//			"PMTK251,19200",
//			"PMTK251,38400",
//			"PMTK251,57600",
//			"PMTK251,115200",

			if(baud_real_rate_ == baud) return;
			baud_real_rate_ = baud;

			char tmp[24];
			utils::sformat("PMTK251,%u", tmp, sizeof(tmp)) % baud_real_rate_;
			uint32_t sum = sum_(tmp);
			char tmp2[24];
			utils::sformat("$%s*%02X\r\n", tmp2, sizeof(tmp2)) % tmp % sum;
			sci_.puts(tmp2);
			sci_.start(baud_real_rate_, intr_);
			init_();
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	通信中のボーレートを取得
			@return	通信中のボーレート
		 */
		//-----------------------------------------------------------------//
		uint32_t get_baudrate() const noexcept { return baud_real_rate_; }


		//-----------------------------------------------------------------//
		/*!
			@breif	位置更新レートの設定 @n
					※高いレートを使う場合、事前にボーレートを高く設定する必要がある。
			@param[in]	rate	更新レート
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool set_update_rate(uint32_t rate) noexcept
		{
			if(rate < 1 || rate > 10) return false;

			// "$PMTK220,1000*1F"	// 1Hz [ms]
			// "$PMTK220,500*2B"	// 2Hz [ms]
			// "$PMTK220,200*2C"	// 5Hz [ms]
			// "$PMTK220,100*2F"	// 10Hz [ms]
			char tmp[16];
			uint32_t r = 1000 / rate;
			utils::sformat("PMTK220,%u", tmp, sizeof(tmp)) % r;
			uint32_t sum = sum_(tmp);
			char tmp2[24];
			utils::sformat("$%s*%02X\r\n", tmp2, sizeof(tmp2)) % tmp % sum;
			sci_.puts(tmp2);
			update_real_rate_ = rate;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	位置更新レートの取得
			@return 位置更新レート
		 */
		//-----------------------------------------------------------------//
		uint32_t get_update_rate() const noexcept { return update_real_rate_; }


#if 0
// Position fix update rate commands.
#define PMTK_API_SET_FIX_CTL_100_MILLIHERTZ  "$PMTK300,10000,0,0,0,0*2C" // Once every 10 seconds, 100 millihertz.
#define PMTK_API_SET_FIX_CTL_200_MILLIHERTZ  "$PMTK300,5000,0,0,0,0*18"  // Once every 5 seconds, 200 millihertz.
#define PMTK_API_SET_FIX_CTL_1HZ  "$PMTK300,1000,0,0,0,0*1C"
#define PMTK_API_SET_FIX_CTL_5HZ  "$PMTK300,200,0,0,0,0*2F"
// Can't fix position faster than 5 times a second!
#endif


#if 0
// turn on only the second sentence (GPRMC)
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
// turn on GPRMC and GGA
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// turn on ALL THE DATA
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// turn off output
#define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

// to generate your own sentences, check out the MTK command datasheet and use a checksum calculator
// such as the awesome http://www.hhhh.org/wiml/proj/nmeaxor.html

#define PMTK_LOCUS_STARTLOG  "$PMTK185,0*22"
#define PMTK_LOCUS_STOPLOG "$PMTK185,1*23"
#define PMTK_LOCUS_STARTSTOPACK "$PMTK001,185,3*3C"
#define PMTK_LOCUS_QUERY_STATUS "$PMTK183*38"
#define PMTK_LOCUS_ERASE_FLASH "$PMTK184,1*22"
#define LOCUS_OVERLAP 0
#define LOCUS_FULLSTOP 1

#define PMTK_ENABLE_SBAS "$PMTK313,1*2E"
#define PMTK_ENABLE_WAAS "$PMTK301,2*2E"

// standby command & boot successful message
#define PMTK_STANDBY "$PMTK161,0*28"
// Not needed currently
#define PMTK_STANDBY_SUCCESS "$PMTK001,161,3*36"
#define PMTK_AWAKE "$PMTK010,002*2D"

// ask for the release and version
#define PMTK_Q_RELEASE "$PMTK605*31"

// request for updates on antenna status 
#define PGCMD_ANTENNA "$PGCMD,33,1*6C" 
#define PGCMD_NOANTENNA "$PGCMD,33,0*6D" 

// センテンス例：
$GPGSV,3,1,12,26,72,352,28,05,65,066,37,15,50,268,35,27,33,189,37*7F
 単語例 	説明 	意味
3 	総GSVセンテンス数 	総GSVセンテンス数：3個
1 	このセンテンスの番号 	3個中の１個目のセンテンス
12 	ビュー内の総衛星数 	ビュー内の総衛星数：12個
26 	衛星番号 	衛星番号：26
72 	衛星仰角。00～90度 	衛星仰角：72度
352 	衛星方位角。000～359度 	衛星方位角：352度
28 	C/No（キャリア／ノイズ比）。00～99dB 	C/No：28dB
05 	衛星番号 	衛星番号：05
65 	衛星仰角。00～90度 	衛星仰角：65度
066 	衛星方位角。000～359度 	衛星方位角：66度
37 	C/No（キャリア／ノイズ比）。00～99dB 	C/No：37dB
15 	衛星番号 	衛星番号：15
50 	衛星仰角。00～90度 	衛星仰角：50度
268 	衛星方位角。000～359度 	衛星方位角：268度
35 	C/No（キャリア／ノイズ比）。00～99dB 	C/No：35dB
27 	衛星番号 	衛星番号：27
33 	衛星仰角。00～90度 	衛星仰角：33度
189 	衛星方位角。000～359度 	衛星方位角：189度
37 	C/No（キャリア／ノイズ比）。00～99dB 	C/No：37dB
*7F 	チェックサム 	チェックサム値：7F
#endif
	};
}
