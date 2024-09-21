#pragma once
//=====================================================================//
/*! @file
    @brief  単位変換クラス unit @n
			単位の変換 @n
			単位計算ＨＰ https://keisan.casio.jp/menu/system/000000000370 @n
			為替レート： https://finance.yahoo.co.jp/fx @n
			貨幣の変換のみ、レートの設定が可能
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単位ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct unit_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  単位種別
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TYPE : uint8_t {
			NIL,		///< 変換無し
			LENGTH,		///< 長さ
			SPEED,		///< 速度
			WEIGHT,		///< 重さ
			MONEY,		///< 貨幣
			_
		};

		enum class NIL : uint8_t {
			_
		};

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  長さ単位 (ベース：1 m)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class LENGTH : uint8_t {
			um,		///< マイクロメートル
			mm,		///< ミリメートル
			cm,		///< センチメートル
			m,		///< メートル
			km,		///< キロメートル
			mil,	///< ミル
			in,		///< インチ
			ft,		///< フィート
			yd,		///< ヤード
			mi,		///< マイル
			SUN,	///< 寸
			SYAK,	///< 尺
			KEN,	///< 間
			CYO,	///< 町
			RI,		///< 里
			KAIL,	///< 海里
			_
		};

		//-- 長さ --
		//メートル法:
		//	ピコメートル	1,000,000,000,000	pm
		//	オングストローム	10,000,000,000	Å
		//	ナノメートル	1,000,000,000	nm
		//	マイクロメートル	1,000,000	μm
		//	ミリメートル	1,000	mm
		//	センチメートル	100	cm
		//	メートル	1	m
		//	キロメートル	0.001	km
		//	メガメートル	1.E-6	Mm
		//	ギガメートル	1.E-9	Gm
		//	テラメートル	1.E-12	Tm
		//	ペタメートル	1.E-15	Pm
		//	エクサメートル	1.E-18	Em
		//	ゼタメートル	1.E-21	Zm
		//	ヨタメートル	1.E-24	Ym
		//ヤード・ポンド法:
		//	ミル	39,370.0787401574803149606299213	mil
		//	インチ	39.3700787401574803149606299213	in
		//	ハンド	9.84251968503937007874015748032	hh
		//	フィート	3.28083989501312335958005249344	ft
		//	ヤード	1.09361329833770778652668416448	yd
		//	チェーン	0.0497096953789867175693947347491	ch
		//	ハロン(ファーロング)	0.00497096953789867175693947347491	fur
		//	マイル	6.21371192237333969617434184363E-4	mi
		//尺貫法:
		//	寸(スン)	33	寸
		//	厘(リン)	3,300	厘
		//	尺(シャク)	3.3	尺
		//	鯨尺(クジラジャク)	2.64	鯨尺
		//	丈(ジョウ)	0.33	丈
		//	間(ケン)	0.55	間
		//	町(チョウ)	0.00916666666666666666666666666667	町
		//	里(リ)	2.5462962962962962962962962963E-4	里
		//天文:
		//	天文単位	6.68458712226844549599595337021E-12	AU
		//	光年	1.05700083402461546370946052449E-16	光年
		//	パーセク	3.24077903894710563139738289333E-17	pc
		//航海:
		//	海里	5.39956803455723542116630669546E-4	海里
		//	ファゾム	0.54680664916885389326334208224	fath
		static constexpr char length_tbl[] = {
			"1e6\0um\0"
			"1e3\0mm\0"
			"1e2\0cm\0"
			"1\0m\0"
			"1e-3\0km\0"
			"39370.0787401574803149606299213\0mil\0"
			"39.3700787401574803149606299213\0in\0"
			"3.28083989501312335958005249344\0ft\0"
			"1.09361329833770778652668416448\0yd\0"
			"6.21371192237333969617434184363E-4\0mi\0"
			"33\0SUN\0"
			"3.3\0SYAK\0"
			"0.55\0KEN\0"
			"0.00916666666666666666666666666667\0CHO\0"
			"2.5462962962962962962962962963E-4\0RI\0"
			"5.39956803455723542116630669546E-4\0KAIRI\0"
			"\0"
		};

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  速度単位 (ベース：mS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED : uint8_t {
			mS,		///< メートル毎秒
			mM,		///< メートル毎分
			mh,		///< メートル毎時
			kmh,	///< キロメートル毎時
			mph,	///< マイル毎時
			kn,		///< ノット（１時間に１海里）
			M,		///< マッハ
			c,		///< 真空中の光速度
			_
		};

		//-- 速度 --
		//メートル法:
		//	メートル/秒	1	m/s
		//	キロメートル毎時	3.6	km/h
		//ヤード・ポンド法:
		//	フィート毎秒	3.28083989501312335958005249344	fps
		//	フィート毎分	196.850393700787401574803149606	fpm
		//	フィート毎時	11,811.0236220472440944881889764	fph
		//	マイル毎秒	6.21371192237333969617434184363E-4	mps
		//	マイル毎分	0.0372822715342400381770460510618	mpm
		//	マイル毎時	2.23693629205440229062276306371	mph
		//航海:
		//	ノット	1.94384449244060475161987041037	kn
		//音:
		//	マッハ	0.00302114803625377643504531722054	M
		//	大気中の音速	0.00290697674418604651162790697674	s
		//光:
		//	真空中の光速度	3.33564095198152049575576714475E-9	c
		static constexpr char speed_tbl[] = {
			"1\0m/S\0"
			"60\0m/M\0"
			"3600\0m/h\0"
			"3.6\0km/h\0"
			"2.23693629205440229062276306371\0mph\0"
			"1.94384449244060475161987041037\0kn\0"
			"0.00302114803625377643504531722054\0M\0"
			"3.33564095198152049575576714475E-9\0c\0"
			"\0"
		};

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  重量単位 (ベース：kg)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class WEIGHT : uint8_t {
			mg,		///< ミリグラム
			ct,		///< カラット
			g,		///< グラム
			kg,		///< キログラム
			t,		///< トン
			gr,		///< グレーン
			oz,		///< オンス
			lb,		///< ポンド
			_
		};

		//-- 重さ --
		//メートル法:
		//	マイクログラム	1,000,000,000	μg
		//	ミリグラム	1,000,000	mg
		//	カラット	5,000	ct
		//	グラム	1,000	g
		//	キログラム	1	kg
		//	トン	0.001	t
		//ヤード・ポンド法:
		//	グレーン	15,432.3583529414306506081660942	gr
		//	ドラム	564.383391193286606650812931443	dr
		//	オンス	35.2739619495804129156758082152	oz
		//	ポンド	2.20462262184877580722973801345	lb
		//	ストーン	0.157473044417769700516409858104	stone
		//	トン(ロング)	9.84206527611060628227561613147E-4	ton
		//	トン(ショート)	0.00110231131092438790361486900673	sh tn
		//	ハンドレッドウェイト（ロング）	0.019684130552221212564551232263	l cwt
		//	ハンドレッドウェイト（ショート）	0.0220462262184877580722973801345	sh cwt
		//尺貫法:
		//	分(フン)	2,666.66666666666666666666666667	分
		//	匁(モンメ)	266.666666666666666666666666667	匁
		//	百目(ヒャクメ)	2.66666666666666666666666666667	百目
		//	斤(キン)	1.66666666666666666666666666667	斤
		//	貫(カン)	0.266666666666666666666666666667	貫
		static constexpr char weight_tbl[] = {
			"1000000\0mg\0"
			"5000\0ct\0"
			"1000\0g\0"
			"1\0kg\0"
			"0.001\0t\0"
			"15,432.3583529414306506081660942\0gr\0"
			"35.2739619495804129156758082152\0oz\0"
			"2.20462262184877580722973801345\0lb\0"
			"\0"
		};

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  貨幣単位 (ベース：YEN)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MONEY : uint8_t {
			YEN,	///< 日本 円
			USD,	///< 米 ドル
			TWD,	///< 台湾 ドル
			RUB,	///< ロシア ルーブル
			CAD,	///< カナダ ドル
			AUD,	///< オーストラリア ドル
			GBP,	///< 英 ポンド
			EUR,	///< 欧州 ユーロ
			NZD,	///< ニュージーランド ドル
			CHF,	///< スイス フラン
			CNY,	///< 中国 元
			INR,	///< インド ルピー
			KRW,	///< 韓国 ウォン
			_
		};

		/// このレートは、２０２４年９月２１日です
		static constexpr char money_tbl[] = {
			"1\0YEN\0"
			"0.0069\0USD\0"
			"0.2221\0TWD\0"
			"0.6416\0RUB\0"
			"0.0094\0CAD\0"
			"0.0102\0AUD\0"
			"0.0052\0GBP\0"
			"0.0062\0EUR\0"
			"0.0111\0NZD\0"
			"0.0059\0CHF\0"
			"0.0490\0CNY\0"
			"0.5801\0INR\0"
			"9.2526\0KRW\0"
			"\0"
		};

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  統合単位型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		union UNIT {
			uint8_t	val;
			NIL		nil;
			LENGTH	length;
			SPEED	speed;
			WEIGHT	weight;
			MONEY	money;
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単位クラス（シングルトン）
		@param[in]	NVAL	数値クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class NVAL>
	class unit : public unit_base {

		struct unit_t {
			const char*	val;
			const char*	ext;
			unit_t() noexcept : val(nullptr), ext(nullptr)
			{ } 
		};

		TYPE	type_;
		static constexpr uint32_t TYPE_N = static_cast<uint32_t>(TYPE::_);
		UNIT	inp_[TYPE_N];
		UNIT	out_[TYPE_N];

		static constexpr uint32_t LENGTH_N = static_cast<uint32_t>(LENGTH::_);
		static constexpr uint32_t LENGTH_O = 0;
		static constexpr uint32_t SPEED_N  = static_cast<uint32_t>(SPEED::_);
		static constexpr uint32_t SPEED_O  = LENGTH_O + LENGTH_N;
		static constexpr uint32_t WEIGHT_N = static_cast<uint32_t>(WEIGHT::_);
		static constexpr uint32_t WEIGHT_O = SPEED_O  + SPEED_N;
		static constexpr uint32_t MONEY_N  = static_cast<uint32_t>(MONEY::_);
		static constexpr uint32_t MONEY_O  = WEIGHT_O  + WEIGHT_N;
		unit_t	units_[LENGTH_N + SPEED_N + WEIGHT_N + MONEY_N];

		static constexpr uint32_t MONEY_BFN = 12;	///< 為替レートバッファサイズ
		char	money_[MONEY_BFN * MONEY_N];

		NVAL	val_;

		void get_no_(TYPE type, uint32_t& n, uint32_t& o) const noexcept
		{
			switch(type) {
			case TYPE::LENGTH:
				n = LENGTH_N;
				o = LENGTH_O;
				break;
			case TYPE::SPEED:
				n = SPEED_N;
				o = SPEED_O;
				break;
			case TYPE::WEIGHT:
				n = WEIGHT_N;
				o = WEIGHT_O;
				break;
			case TYPE::MONEY:
				n = MONEY_N;
				o = MONEY_O;
				break;
			default:
				break;
			}
		}

		NVAL get_(UNIT u) noexcept
		{
			uint32_t n = 0;
			uint32_t o = 0;
			get_no_(type_, n, o);
			uint32_t i = u.val;
			if(i >= n) i = n - 1;
			NVAL tmp;
			tmp.assign(units_[o + i].val);
			return tmp;
		}

		void make_const_value_(const char* p, uint32_t ofs, uint32_t num) noexcept
		{
			uint32_t i = 0;
			do {
				auto l = strlen(p);
				if(l != 0) {
					units_[ofs + i].val = p;
					p += l + 1;
					units_[ofs + i].ext = p;
					l = strlen(p);
					if(l == 0) break;
					p += l + 1;
					++i;
				} else {
					break;
				}
			} while(i < num) ;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		unit() noexcept :
			type_(TYPE::NIL)
		{
			out_[0].nil = inp_[0].nil = NIL::_;
			out_[1].length = inp_[1].length = LENGTH::m;
			out_[2].speed  = inp_[2].speed  = SPEED::kmh;
			out_[3].weight = inp_[3].weight = WEIGHT::kg;
			out_[4].money  = inp_[4].money  = MONEY::YEN;
			make_const_value_(unit_base::length_tbl, LENGTH_O, LENGTH_N);
			make_const_value_(unit_base::speed_tbl,  SPEED_O,  SPEED_N);
			make_const_value_(unit_base::weight_tbl, WEIGHT_O, WEIGHT_N);
			make_const_value_(unit_base::money_tbl,  MONEY_O,  MONEY_N);
			for(uint32_t i = 0; i < MONEY_N; ++i) {
				strncpy(&money_[MONEY_BFN * i], units_[MONEY_O + i].val, MONEY_BFN);
				units_[MONEY_O + i].val = &money_[MONEY_BFN * i];
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief  種別を設定
			@param[in]	type	種別型
		*/
		//-------------------------------------------------------------//
		void set_type(TYPE type) noexcept
		{
			type_ = type;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  種別を取得
			@return	種別型
		*/
		//-------------------------------------------------------------//
		auto get_type() const noexcept { return type_; }


		//-------------------------------------------------------------//
		/*!
			@brief  単位種別に対する登録個数を取得
			@param[in]	type	種別型
			@return	個数
		*/
		//-------------------------------------------------------------//
		auto get_num(TYPE type) const noexcept
		{
			uint32_t n = 0;
			uint32_t o = 0;
			get_no_(type, n, o);
			return n;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  単位種別に対する登録個数を取得（カレントタイプ）
			@return	個数
		*/
		//-------------------------------------------------------------//
		auto get_num() const noexcept
		{
			return get_num(get_type());
		}


		//-------------------------------------------------------------//
		/*!
			@brief  単位種別に対する文字列を取得
			@param[in]	type	種別型
			@param[in]	unit	各単位型
			@return	単位文字列
		*/
		//-------------------------------------------------------------//
		auto get_ext(TYPE type, UNIT unit) const noexcept
		{
			uint32_t n = 0;
			uint32_t o = 0;
			get_no_(type, n, o);
			uint32_t i = unit.val;
			if(i >= n) i = n - 1;
			return units_[o + i].ext;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  単位種別に対する文字列を取得（カレントタイプ）
			@param[in]	unit	各単位型
			@return	単位文字列
		*/
		//-------------------------------------------------------------//
		auto get_ext(UNIT unit) const noexcept
		{
			return get_ext(get_type(), unit);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  単位種別文字列に対する単位型を取得
			@param[in]	type	種別型
			@param[in]	ext		単位種別文字列
			@param[out]	u		ユニット型
			@return	マッチした場合「true」
		*/
		//-------------------------------------------------------------//
		bool match_ext(TYPE type, const char* ext, UNIT& u) const noexcept
		{
			uint32_t n = 0;
			uint32_t o = 0;
			get_no_(type, n, o);
			u.val = 0;
			for(uint32_t i = 0; i < n; ++i) {
				if(strcmp(units_[o + i].ext, ext) == 0) {
					u.val = i;
					return true;
				}
			}
			return false;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  単位種別文字列に対する単位型を取得
			@param[in]	ext		単位種別文字列
			@param[out]	u		ユニット型
			@return	マッチした場合「true」
		*/
		//-------------------------------------------------------------//
		bool match_ext(const char* ext, UNIT& u) const noexcept
		{
			return match_ext(get_type(), ext, u);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  入力単位を設定
			@param[in]	unit	単位型
		*/
		//-------------------------------------------------------------//
		void set_inp(UNIT unit) noexcept
		{
			uint32_t n = 0;
			uint32_t o = 0;
			get_no_(type_, n, o);
			if(unit.val >= n) {
				unit.val = 0;
			}
			inp_[static_cast<uint32_t>(type_)] = unit;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  入力単位を取得
			@return	単位型
		*/
		//-------------------------------------------------------------//
		auto get_inp() const noexcept { return inp_[static_cast<uint32_t>(type_)]; }


		//-------------------------------------------------------------//
		/*!
			@brief  出力単位を設定
			@param[in]	unit	単位型
		*/
		//-------------------------------------------------------------//
		void set_out(UNIT unit) noexcept { out_[static_cast<uint32_t>(type_)] = unit; }


		//-------------------------------------------------------------//
		/*!
			@brief  出力単位を取得
			@return	単位型
		*/
		//-------------------------------------------------------------//
		auto get_out() const noexcept { return out_[static_cast<uint32_t>(type_)]; }


		//-------------------------------------------------------------//
		/*!
			@brief  貨幣レートを取得
			@param[in]	type	貨幣タイプ
			@return レート文字列
		*/
		//-------------------------------------------------------------//
		const char* get_rate(MONEY type) const noexcept
		{
			return &money_[MONEY_BFN * static_cast<uint32_t>(type)];
		}


		//-------------------------------------------------------------//
		/*!
			@brief  貨幣レートを設定 @n
					円に対する貨幣レートを設定
			@param[in]	type	貨幣タイプ
			@param[in]	rate	レート（最大 'MONEY_BFN' 桁の数字文字列）
			@return 正常なら「true」
		*/
		//-------------------------------------------------------------//
		bool set_rate(MONEY type, const char* rate) noexcept
		{
			if(rate == nullptr) {
				return false;
			}
			strncpy(&money_[MONEY_BFN * static_cast<uint32_t>(type)], rate, MONEY_BFN);
			return true;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  単位の変換
			@param[in]	in	入力値
			@return	変換値を返す
		*/
		//-------------------------------------------------------------//
		const NVAL& operator () (const NVAL& in) noexcept
		{
			if(type_ == TYPE::NIL) {
				val_ = in;
			} else {
				NVAL v;
				v = in / get_(inp_[static_cast<uint32_t>(type_)]);
				val_ = v * get_(out_[static_cast<uint32_t>(type_)]);
			}
			return val_;
		}
	};
}
