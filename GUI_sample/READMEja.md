Renesas RX65N/RX72N Envision Kit GUI サンプル
=========

<img src="../docs/gui_sample.jpg" width="50%">

[English](README.md)
   
## 概要

 - C++ GUI フレームワークを利用したサンプル
 - GUI のレンダリングは、ソフトウェアー、又は、DRW2D エンジンを選択出来ます。
 - 基本的に、RX65N/RX72N Envision Kit 向けにデザインされていますが、他のプラットホームでも使えます。
 - ソフトウェアーレンダラーでは、フレームバッファが必要です。
 - このサンプルでは、基本的な GUI フレームワークの利用方法や、操作に対する考え方が判ります。
 - GUI を使ったアプリを開発する場合の要領が判ります。
 - なるべく最小限の手間で、必要な GUI パーツを構成する事目的としています。
 - 標準的には、プリミティブの合成でパーツを描画する為、GUI のビットマップを用意する必要がありません。
 - C++ の機能を有効に使い、別ツールで GUI のデザインを行う必要がありません。

 ---
    
## プロジェクト・リスト

 - main.cpp
 - RX65N/Makefile
 - RX72N/Makefile
   
---

## GUI サンプルの機能

 - ボタン「Button」
 - ボタン「Active」
 - チェックボックス
 - ラジオボタン
 - 水平スライダー
 - 垂直スライダー
 - メニュー（ItemA, ItemB, ItemC, ItemD）
 - テキスト（自動スクロール）
 - テキストボックス（垂直アライメント：センター）
 - スピンボックス（数値の変更、-100、+100）
   
### 各動作

 - 各 widget を操作すると、シリアル出力で、対応する文字列を出力します。
 - 「Button」を押す度に、「Active」ボタンの状態が変化します。（ストール -> 許可）
 - チェックが有効になると、ラジオボタンの描画色を「白」にする。
 - ラジオボタンを操作すると、それに応じて、描画色が変化（Red, Green, Blue）
 - text widget には、表示領域より大きい文字列を登録してあり、それが自動でスクロールします。
 - スピンボックスを使って、設定数値を変更します。

---

## C++/GUI フレームワークの特徴

- 基本的に C++17 準拠で実装されています。
- GNU RX 8.3.0 以降でコンパイル可能。
- GUI の配置ツールなど、他のアプリを連携しない。（これはデメリットと感じる方もいます）
- MIT ライセンスでソースコードの全てが公開されているので、改造や拡張が自由に出来る。
- あまり複雑な場面より、単純な場面を想定して設計されている為、扱うのが簡単。
- 複雑な操作を行う GUI を実装する事も可能な自由度がある。
- リアルタイム処理にマッチするよう、画面描画を同期式で行っており、FreeRTOS などを使わなくても描画間隔の制御が簡単。
- もちろん、FreeRTOS を使う場合でも問題なく利用できる。
- C++ の機能を使って、より良い方法で実装が出来る。

GUI のアプリケーションを作成する場合、最初のハードルは、部品（Widget）のデザインや配置です。   
デザインに関しては、角をラウンドさせたシンプルなデザインを採用しており、プリミティブの合成により描画させています。   
※ビットマップデータでは無いので、コンパクトで柔軟性があります。   
   
C++ では、constexpr を積極利用する事ができ、配置の問題はかなり柔軟に対応出来ます。   
   
デザインに関しては、初期の段階で標準的なデザインを持った Widget（ボタン、スライダー、チェックボックスなど）を用意してありますので、当面は困らないと思います。   
もし、異なったデザインが必要なら、ビットマップ画像を利用する事も出来るし、既存のクラスをコピーして自分の気に入るデザインの部品を作る事も可能です。   
   
GUI のデザインツールや配置ツールは、かなり複雑な場合は必要かもしれませんが、携帯機器のように限られたサイズの液晶向けアプリケーションでは、あまり必要性を感じないと思います。   
又、そのようなツールを使う場合、そのツールが出力する中間ファイルなどの扱いが微妙で、ソースコードと隔離されてしまい、将来的に保守をする場合に、問題が発生する事になりますし、ソースコードの保守を難しくします。   

## widget の基本的な使い方

RX65N/RX72N Envision Kit についての解説ですが、他のハードウェアーでも同じように利用できるように工夫した構造と構成になっています。   
   
画像表示機能が無いマイコンで利用する場合には、メインメモリをフレームバッファとしてアロケートし、それを LCD に転送するような方法が必要です。   
RX マイコンの場合、DMAC があるので、それらを利用する事で、同じような構成にする事が出来ると思います。   
   
---
   
### RX65N/RX72N 描画ハードウェアー定義と設定

RX65N/RX72N では、LCD に表示を行うハードウェアー（GLCDC）を内蔵しており、その設定を行う事で簡単に表示環境を構築出来ます。   
基本的に、ドットクロック、画素データ、水平同期信号、垂直同期信号を生成します。   
   
以下の例は、RX65N/RX72N Envision Kit に搭載された LCD の表示設定を行うものです。

```C++
	// LCD 定義
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static const auto PIX = graphics::pixel::TYPE::RGB565;

#if defined(SIG_RX65N)
	// GLCDC 関係定義
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0000'0100;
#elif defined(SIG_RX72N)
	// GLCDC 関係定義
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0080'0000;
#endif

	// GLCDC 関係リソース
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC;
    GLCDC		glcdc_(nullptr, reinterpret_cast<void*>(LCD_ORG));

...

	{  // GLCDC の初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_.control(GLCDC::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("GLCDC Fail\n");
		}
	}
```

- LCD_DISP は、LCD 表示を「有効／無効」にする制御ポートです。
- LCD_LIGHT は、バックライトの「ON、OFF」です。
- glcdc_mgr クラスは、内部で、480x272 サイズの液晶用パラメータをハードコードしており、他のサイズ液晶を定義する場合、パラメータを修正する必要があります。
- この構造は良くありませんので、将来的には改善する予定です。

```C++
		//
		// Definition of LCD for 480x272 LCD by 60Hz
		//
		// Horizontal cycle (whole control screen) 529
		// Vertical cycle (whole control screen) 315
		// Horizontal Synchronization Signal Assertion Position
		cfg.output.htiming.front_porch = 8;
		// Vertical Synchronization Assertion Position
		cfg.output.vtiming.front_porch = 10;
		// Horizontal Active Pixel Start Position (min. 6 pixels)
		cfg.output.htiming.back_porch = 39;
		cfg.output.vtiming.back_porch = 32;
		// Horizontal Active Pixel Width
		cfg.output.htiming.display_cyc = XSIZE;
		// Vertical Active Display Width
		cfg.output.vtiming.display_cyc = YSIZE;
		// Vertical Active Display Start Position (min. 3 lines)
		cfg.output.htiming.sync_width = 2;
		cfg.output.vtiming.sync_width = 1;
```

---

### 描画リソースの定義と設定

描画を行うリソースとして、ビットマップフォントを設定する必要があります。

```C++
	// フォントの定義
	typedef graphics::font8x16 AFONT;
// 	for cash into SD card /kfont16.bin
//	typedef graphics::kfont<16, 16, 64> KFONT;
	typedef graphics::kfont<16, 16> KFONT;
	typedef graphics::font<AFONT, KFONT> FONT;

	AFONT		afont_;
	KFONT		kfont_;
	FONT		font_(afont_, kfont_);
```

上記の例では、アスキーフォントとして８ｘ１６ピクセルフォント、漢字フォントとして１６ｘ１６ピクセルフォントを定義しています。   
漢字ビットマップを含めたく無い場合、SD カードに「kfont16.bin」などを置いて、キャッシュして利用する事も出来ます。   
この場合、SD カード関係のマネージメントを実装する必要があります。   
※上記の例でコメントアウトされた typedef を代わりに有効にします。（６４は、キャッシュするフォント数です）
   
漢字フォントのコード体型は UTF-8 を標準としていますが、内部では、Shift-JIS との相互変換が必要です。   
※漢字フォントのデータは、配置効率を重視して Shift-JIS の並びになっている為です。   
その変換で、FatFS に含まれる変換 API を利用する為、FatFS 関係のソースコードなど一式をリンクする必要があります。 

アスキーフォントは、私が作成したもので、MIT ライセンスです。   
１６ピクセル漢字フォントは、「東雲16ドット」を利用しています。   
※ライセンスは、[graphics/kfont16.cpp](graphics/kfont16.cpp) を参照下さい。   
   
Makefile に、

```
CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				$(FATFS_VER)/ff.c \
				$(FATFS_VER)/ffsystem.c \
				$(FATFS_VER)/ffunicode.c \

...

USER_DEFS	=	SIG_RX72N \
				FAT_FS FAT_FS_NUM=16
```

「FATFS のソースコード、FAT_FS 関係の外部変数など」を追加します。
   
描画クラスは、ソフト描画か、ＲＸマイコンに含まれる、ＤＲＷ２Ｄエンジンを使う事が出来ます。   
※DRW2D エンジンでの描画は、マイコンの動作と非同期に行われるので、注意が必要です。   
   
```C++
	// DRW2D レンダラー
//	typedef device::drw2d_mgr<GLCDC, FONT> RENDER;
	// ソフトウェアーレンダラー
	typedef graphics::render<GLCDC, FONT> RENDER;

	GLCDC		glcdc_(nullptr, reinterpret_cast<void*>(LCD_ORG));
	AFONT		afont_;
	KFONT		kfont_;
	FONT		font_(afont_, kfont_);
	RENDER		render_(glcdc_, font_);
```

上記のように、GLCDC、フォントリソース、レンダラーなどの実態を定義します。   
コンストラクターの引数として、描画ハードウェアー（GLCDC）、フォントリソース、などが必要です。   
   
FONT クラスは、アスキーフォント、漢字フォントを含めたクラスで、描画クラスのインスタンスとして使います。   
   
---

### タッチハードウェアーの定義と設定

RX65N/RX72N Envision Kit には、I2C 接続の静電容量タイプのタッチセンサ（FT5206）が搭載されています。   
この定義と設定は以下のようになります。    
※タッチセンサの「RESET」信号を制御する必要があります。   

```C++
	// SCI_I2C バッファ定義
	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;
#if defined(SIG_RX65N)
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::FIRST_I2C> FT5206_I2C;
#elif defined(SIG_RX72N)
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::THIRD_I2C> FT5206_I2C;
#endif
	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH		touch_(ft5206_i2c_);
```

タッチセンサの初期化は以下のように行います。

```C++
	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		uint8_t intr_lvl = 1;
		if(!ft5206_i2c_.start(FT5206_I2C::SPEED::STANDARD, FT5206_I2C::MODE::MASTER, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		}
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		}
	}
```

※現状の SCI_I2C ドライバーでは、改修中の為、割り込み処理を行っていません（ポーリング）が問題無く使用できます。   

---

### 主な widget クラスと描画クラス

名前空間は 'gui' となっています。

|ソース|主な機能|
|-----|-------|
|[RX600/drw2d_mgr.hap](RX600/drw2d_mgr.hpp)|DRW2D エンジンによる描画クラス|
|[graphics/graphics.hap](graphics/graphics.hpp)|ソフトによる描画クラス|
|[graphics/font.hpp](graphics/font.hpp)|フォント設定(ASCII+漢字ビットマップ)|
|[graphics/afont.hpp](graphics/afont.hpp)|ASCII フォント|
|[graphics/font8x16.hpp](graphics/font8x16.hpp)|8 x 16 ピクセルフォント定義（ヘッダー）|
|[graphics/font8x16.cpp](graphics/font8x16.cpp)|8 x 16 ピクセルフォント定義（ソース）|
|[graphics/kfont.hpp](graphics/kfont.hpp)|漢字フォント|
|[graphics/kfont16.cpp](graphics/kfont16.cpp)|16 x 16 ピクセル漢字フォントデータ|
|[graphics/color.hpp](graphics/color.hpp)|基本カラー定義|
|[graphics/widget_director.hpp](graphics/widget_director.hpp)|Widget ディレクター（管理）|
|[graphics/widget.hpp](graphics/widget.hpp)|widget 基本クラス|
|[graphics/group.hpp](graphics/group.hpp)|Widget グループ・クラス|
|[graphics/button.hpp](graphics/button.hpp)|Widget ボタン・クラス|
|[graphics/check.hpp](graphics/check.hpp)|Widget チェックボックス・クラス|
|[graphics/radio.hpp](graphics/radio.hpp)|Widget ラジオボタン・クラス|
|[graphics/slider.hpp](graphics/slider.hpp)|Widget スライダー・クラス|
|[graphics/menu.hpp](graphics/menu.hpp)|Widget メニュー・クラス|
|[graphics/text.hpp](graphics/text.hpp)|Widget テキスト・クラス|
|[graphics/textbox.hpp](graphics/textbox.hpp)|Widget テキスト・ボックス・クラス|
|[graphics/spinbox.hpp](graphics/spinbox.hpp)|Widget スピン・ボックス・クラス|
   
※他に、画像ローダーなど、色々なクラスがあり、利用出来ます。   

---

### widget ディレクターの定義

widget ディレクターは、テンプレートクラスになっており、アプリケーションで扱う widget 数をテンプレートパラメータとして受け付けます。   
また、パラメータとして、レンダークラス、タッチクラスの型を定義し、コンストラクターにはインスタンスを渡す必要があります。   
widget ディレクターは、管理数を固定とする事で、記憶割り当てを使用しない設計となっています。   
   
```C++
	// 最大３２個の Widget 管理
	typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
	WIDD		widd_(render_, touch_);
```

- widget ディレクターは、widget の追加、削除 API をグローバル関数として定義しておく必要があります。
- widget_director はテンプレートクラスなので、このインスタンスにアクセスするには、「型」を知っている必要があります。
- 通常、widget_director の実態があるソースで、グローバル関数として定義しておきます。
- サンプルでは、main.cpp に widget_director のインスタンスがあり、そこで定義してあります。
- widget のインサート、削除は、各 widget のコンストラクター、デストラクターから呼ばれます。

```C++
/// widget の登録・グローバル関数
bool insert_widget(gui::widget* w)
{
    return widd_.insert(w);
}

/// widget の解除・グローバル関数
void remove_widget(gui::widget* w)
{
    widd_.remove(w);
}
```
      
---
   
### widget の定義

- widget の定義では、コンストラクターで表示座標、文字列などを設定します。   
- 座標で位置を指定しますが、「constexpr」で関数を指定して、かなり複雑な計算や分岐をコンパイル時に行う事も出来る為、かなり自由度のある自動的な配置を行う事も出来ます。   
- 「cal_sample（関数電卓サンプル）」を参照して下さい。   
- サイズを「０」とした場合、内部で設定された標準サイズを利用します。（標準サイズを設定しない部品もあります。）   
- 各部品のコンストラクターで、widget は、widget ディレクターに取り込まれます。（管理対象となる）   
- 初期の状態では、管理対象となるだけで、表示は不許可となっています。   

```C++
	typedef gui::button BUTTON;
	BUTTON		button_(vtx::srect(10, 10, 80, 32), "Button");
	BUTTON		button_stall_(vtx::srect(100, 10, 80, 32), "Stall");
	typedef gui::check CHECK;
	CHECK		check_(vtx::srect(   10, 10+50, 0, 0), "Check");  // サイズ０指定で標準サイズ
	typedef gui::group<3> GROUP3;
	GROUP3		group_(vtx::srect(   10, 10+50+40, 0, 0));
	typedef gui::radio RADIO;
	RADIO		radioR_(vtx::srect(   0, 40*0, 0, 0), "Red");
	RADIO		radioG_(vtx::srect(   0, 40*1, 0, 0), "Green");
	RADIO		radioB_(vtx::srect(   0, 40*2, 0, 0), "Blue");
	typedef gui::slider SLIDER;
	SLIDER		sliderh_(vtx::srect(200, 20, 200, 0), 0.5f);
	SLIDER		sliderv_(vtx::srect(460, 20, 0, 200), 0.0f);
	typedef gui::menu MENU;
	MENU		menu_(vtx::srect(120, 70, 100, 0), "ItemA,ItemB,ItemC,ItemD");
	typedef gui::text TEXT;
	TEXT		text_(vtx::srect(240, 70, 150, 20), "１６ピクセル漢字の表示サンプル～");
	typedef gui::textbox TEXTBOX;
	TEXTBOX		textbox_(vtx::srect(240, 100, 160, 80), "");
	typedef gui::spinbox SPINBOX;
	SPINBOX		spinbox_(vtx::srect(20, 220, 120, 0),
					{ .min = -100, .value = 0, .max = 100, .step = 1, .accel = true });
```
   
※「button_」では、X 座標：１０、Y 座標：１０、横幅：８０、高さ：３２、表示文字「Button」で登録しています。   
   
アプリケーションを開始したら、各 widget の表示設定などを行います。
   
- 「at_select_func」は、widget の挙動に関係したコールバック関数を設定します。
- ラムダ式を受け付けるので、widget に対する挙動を簡潔に実装する事が出来ます。   
   
```C++
	void setup_gui_()
	{
		button_.enable();    ///< 表示を有効にする。
		button_.at_select_func() = [=](uint32_t id) {
			utils::format("Select Button: %d\n") % id;
			// button_stall_ の状態を変える。
			if(button_stall_.get_state() == BUTTON::STATE::STALL) {
				button_stall_.set_state(BUTTON::STATE::ENABLE);
				button_stall_.set_title("Active");
			} else if(button_stall_.get_state() == BUTTON::STATE::ENABLE) {
				button_stall_.set_state(BUTTON::STATE::STALL);
				button_stall_.set_title("Stall");
			}
		};
		button_stall_.enable();
		button_stall_.set_state(BUTTON::STATE::STALL);

		check_.enable();
		check_.at_select_func() = [=](bool ena) {
			utils::format("Select Check: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::White);
				radioG_.set_base_color(DEF_COLOR::White);
				radioB_.set_base_color(DEF_COLOR::White);
				radioR_.set_font_color(DEF_COLOR::White);
				radioG_.set_font_color(DEF_COLOR::White);
				radioB_.set_font_color(DEF_COLOR::White);
			}
		};

		// グループにラジオボタンを登録
		group_ + radioR_ + radioG_ + radioB_;
		group_.enable();  // グループ登録された物が全て有効になる。
		radioR_.at_select_func() = [=](bool ena) {
			utils::format("Select Red: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::Red);
				radioG_.set_base_color(DEF_COLOR::Red);
				radioB_.set_base_color(DEF_COLOR::Red);
				radioR_.set_font_color(DEF_COLOR::Red);
				radioG_.set_font_color(DEF_COLOR::Red);
				radioB_.set_font_color(DEF_COLOR::Red);
			}
		};
		radioG_.at_select_func() = [=](bool ena) {
			utils::format("Select Green: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::Green);
				radioG_.set_base_color(DEF_COLOR::Green);
				radioB_.set_base_color(DEF_COLOR::Green);
				radioR_.set_font_color(DEF_COLOR::Green);
				radioG_.set_font_color(DEF_COLOR::Green);
				radioB_.set_font_color(DEF_COLOR::Green);
			}
		};
		radioB_.at_select_func() = [=](bool ena) {
			utils::format("Select Blue: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::Blue);
				radioG_.set_base_color(DEF_COLOR::Blue);
				radioB_.set_base_color(DEF_COLOR::Blue);
				radioR_.set_font_color(DEF_COLOR::Blue);
				radioG_.set_font_color(DEF_COLOR::Blue);
				radioB_.set_font_color(DEF_COLOR::Blue);
			}
		};
		radioG_.exec_select();  // 最初に選択されるラジオボタン

		sliderh_.enable();
		sliderh_.at_select_func() = [=](float val) {
			utils::format("Slider H: %3.2f\n") % val;
		};
		sliderv_.enable();
		sliderv_.at_select_func() = [=](float val) {
			utils::format("Slider V: %3.2f\n") % val;
		};

		menu_.enable();
		menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
			char tmp[32];
			menu_.get_select_text(tmp, sizeof(tmp));
			utils::format("Menu: '%s', %u/%u\n") % tmp % pos % num;
		};

		text_.enable();

		textbox_.enable();
		textbox_.set_title("(1) 項目\n(2) GUI サンプルについて。\n(3) まとめ");
		textbox_.set_vertical_alignment(TEXTBOX::V_ALIGNMENT::CENTER);

		spinbox_.enable();
		spinbox_.at_select_func() = [=](SPINBOX::TOUCH_AREA area, int16_t value) {
			static const char* st[3] = { "Minus", "Stay", "Plus" };
			utils::format("Spinbox: %s Value: %d\n")
				% st[static_cast<uint8_t>(area)] % value;
		};
	}
```
   
「ボタン」の場合、ボタンを触れて、離した時に、「at_select_func」に設定されたコールバックが呼び出されます。   
※ストール状態の場合、呼ばれません。   
「スライダー」の場合は、スライダーの値が変化した場合に呼び出されます。   
   
通常、widget には３つの状態があります。   
- Disable（表示されていない）
- Enable（表示されている）
- Stall（薄く表示され、無効状態）
   
---

### メインループ

- widget ディレクターは、同期式描画を前提に設計されています。   
-「同期」とは、LCD の表示（60Hz）に同期してアプリケーションを動かす事です。   
- この方法は、主にリアルタイム性が要求されるアプリに最適な方法です。   
- 本来なら、RTOS などでスレッド管理して平行動作させるのが理想的ではありますが、同期式なら、簡易的にかなり広範囲な平行動作をさせる事が可能です。   
- この方式はゲームのアプリケーションに見られる方法です。   
         
以下のように、表示の同期に合わせて、毎フレーム呼びます。   
※各 widget の描画は、内部で必要な場合のみ行い、余分な描画をなるべく行わないようにしています。   
   
タッチ関係のアップデートも毎フレーム呼び出します。   
   
```C++
	setup_gui_();  ///< GUI の設定を行う。

	while(1) {
		render_.sync_frame();
		touch_.update();			

		widd_.update();

    ...

    }
```
   
例えば、widget_director とは関係無く、フレームバッファを消去すると、今まで描画されていた widget は再描画されません。   
※部品がある座標をタッチするなど、Widget の状態を変える操作をすれば、必要に応じて描画されます。   
   
以下の API をコールすれば、全体を再描画出来ます。   

```
	widd_.redraw_all();
```
   
このテクニックは、ファイル選択機能など、widget_director とは異なるポリシーで動作するクラスとの併用時に行います。   
   
---

## 特有の挙動など

この GUI フレームワークでは、省メモリでの動作を行う為、リソースの扱いとして、管理方法が一般的な方法と異なる場合があります。   
   
たとえば、button widget で、ボタン名のテキストは、ポインターで管理しています。   
※一般的には、記憶割り当てを行い、コピーを行う。   
   
```C++
	button_.set_title("Abcd");
```
    
上記の API では、「Abcd」は、内部バッファにコピーされるのではなく、ポインターのみが取り込まれます。   
ディレクター内では、ポインターを管理しており、ポインターが以前と異なったタイミングで再描画を行います。   
その為、スタックで文字列を作成して、そのポインターを渡すような方法は許容されませんので注意が必要です。   
   
```C++
	void make_button_title(int no)
	{
		char tmp[16];

		utils::sformat("No%d", tmp, sizeof(tmp)) % no;
		button_.set_title(tmp);
	}
```
   
↑このようなやり方はＮＧ！   
   
```C++
	void make_button_title(int no)
	{
		static char tmp[16];

		utils::sformat("No%d", tmp, sizeof(tmp)) % no;
		button_.set_title(tmp);
		button_.set_update();
	}
```
   
安全な、グローバル領域のポインターを利用する。   
ポインターの変化が無い為、「set_update」関数で、再描画を指定する。   
   
---

## ビルド方法

 - ターゲットディレクトリーに移動
 - make する。
 - GUI_sample.mot ファイルをマイコンに書き込む。

-----
   
License
----
   
MIT open source license   
