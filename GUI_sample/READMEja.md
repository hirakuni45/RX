Renesas RX65N/RX72N Envision Kit GUI サンプル
=========

<img src="../docs/gui_sample.jpg" width="50%">

[English](README.md)
   
## 概要

 - C++ GUI フレームワークを利用したサンプル
 - GUI のレンダリングは、ソフトウェアー、DRW2D エンジンを選択出来ます。
 - ソフトウェアーレンダラーでは、プラットホームを選びません。
 - 基本的な GUI フレームワークの利用方法や、操作に対する考え方が判ります。
    
## プロジェクト・リスト

 - main.cpp
 - RX65N/Makefile
 - RX72N/Makefile
   
---

## widget の基本的な使い方

RX65N Envision Kit と、RX72N Envision Kit についての解説ですが、他のハードウェアーでも同じように利用できるように工夫した構造と構成になっています。   

### 描画ハードウェアー定義と設定

RX65N/RX72N では、LCD に表示を行うハードウェアー（GLCDC）を内蔵しており、その設定を行う事で簡単に表示環境を構築出来ます。   
基本的に、ドットクロック、水平同期信号、垂直同期信号を生成します。   
   
以下の例は、RX65N/RX72N Envision Kit に搭載された TFT-LCD の表示設定を行うものです。

```
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

- LCD_DISP は、TFT-LCD 表示を「有効／無効」にする制御ポートです。
- LCD_LIGHT は、バックライトの「ON、OFF」です。
- glcdc_mgr クラスは、内部で、480x272 サイズの液晶用パラメータをハードコードしており、他のサイズ液晶を定義する場合、パラメータを修正する必要があります。
   
```
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

```
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
   
漢字フォントのコード体型は UTF-8 を利用していますが、内部では、ShiftJIS との相互変換が必要です。   
その変換で、FatFS に含まれる変換 API を利用する為、FatFS 関係のソースコードなど一式をリンクする必要があります。   
   
描画クラスは、ソフト描画と、ＲＸマイコンに含まれる、ＤＲＷ２Ｄエンジンを使う事が出来ます。   

```
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
上記のように、ＧＬＣＤＣ、フォントリソース、レンダラーなどの実態を定義します。   
コンストラクターの引数として、フォントや、ＧＬＣＤＣなどが必要です。   

---

### タッチハードウェアーの定義と設定

RX65N/RX72N Envision Kit には、I2C 接続の静電容量タイプのタッチセンサ（FT5206）が搭載されています。   
この定義と設定は以下のようになります。    
※タッチセンサの「RESET」信号を制御する必要があります。   

```
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

```
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

---

### 主な widget クラスと描画クラス

|ソース|主な機能|
|-----|-------|
|[graphics/graphics.hap](graphics/graphics.hpp)|ソフトによる描画クラス|
|[RX600/drw2d_mgr.hap](RX600/drw2d_mgr.hpp)|DRW2D エンジンによる描画クラス|
|[graphics/font.hpp](graphics/font.hpp)|フォント設定(ASCII+漢字ビットマップ)|
|[graphics/afont.hpp](graphics/afont.hpp)|ASCII フォント|
|[graphics/font8x16.hpp](graphics/font8x16.hpp)|8 x 16 ピクセルフォント定義（ヘッダー）|
|[graphics/font8x16.cpp](graphics/font8x16.cpp)|8 x 16 ピクセルフォント定義（ソース）|
|[graphics/kfont.hpp](graphics/kfont.hpp)|漢字フォント|
|[graphics/kfont16.cpp](graphics/kfont16.cpp)|16 x 16 ピクセル漢字フォントデータ|
|[graphics/color.hpp](graphics/color.hpp)|基本カラー定義|
|[graphics/widget_director.hpp](graphics/widget_director.hpp)|Widget ディレクター（管理）|
|[graphics/widget.hpp](graphics/widget.hpp)|widget 基本クラス|
|[graphics/group.hpp](graphics/group.hpp)|Widget グループクラス|
|[graphics/button.hpp](graphics/button.hpp)|Widget ボタンクラス|
|[graphics/check.hpp](graphics/check.hpp)|Widget チェックボックス|
|[graphics/radio.hpp](graphics/radio.hpp)|Widget ラジオボタン|
|[graphics/slider.hpp](graphics/slider.hpp)|Widget スライダー|
|[graphics/menu.hpp](graphics/menu.hpp)|Widget メニュー|
|[graphics/text.hpp](graphics/text.hpp)|Widget テキスト|
|[graphics/textbox.hpp](graphics/textbox.hpp)|Widget テキスト・ボックス|
   
---

### widget ディレクターの定義

widget ディレクターは、テンプレートクラスになっており、アプリケーションで扱う widget 数をテンプレートパラメータとして受け付けます。   
また、パラメータとして、レンダークラス、タッチクラスの型を定義し、コンストラクターにはインスタンスを渡す必要があります。   
widget ディレクターは、管理数を固定数とする事で、記憶割り当てを使用しない設計となっています。   
   
```
	// 最大３２個の Widget 管理
	typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
	WIDD		widd_(render_, touch_);
```

widget ディレクターは、widget の追加、削除 API をグローバル関数として定義しておく必要があります。   
これは、widget_director はテンプレートクラスなので、このインスタンスにアクセスするには、「型」を知っている必要があります。   

```
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

### widget の定義

widget の定義では、コンストラクターで表示座標などを設定します。   
※座標で位置を指定しますが、「constexpr」で関数を指定して、かなり複雑な計算をコンパイル時に行う事も出来る為、かなり自由度のある自動的な配置を行う事も出来ます。   
※「cal_sample（関数電卓サンプル）」を参照して下さい。   

```
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
```

コンストラクターで、widget は、widget ディレクターに取り込まれます。   
※取り込まれるだけで、表示は不許可となっています。   
   
アプリケーションが開始したら、各 widget の表示設定などを行います。
   
「at_select_func」は、挙動に関係したコールバック関数を設定しますが、ラムダ式を受け付けるので、widget に対する挙動を簡潔に定義出来ます。   
   
```
	void setup_gui_()
	{
		button_.enable();
		button_.at_select_func() = [=](uint32_t id) {
			utils::format("Select Button: %d\n") % id;
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
	}
```

### メインループ

widget ディレクターは、同期式描画を前提に設計されています。   
   
以下のように、表示の同期に合わせて、毎フレーム呼びます。   
※各 widget の描画は、必要な場合のみ行います。   
   
```
	while(1) {
		render_.sync_frame();
		touch_.update();			

		widd_.update();

    ...

    }
```

---

## ビルド方法

 - ターゲットディレクトリーに移動
 - make する。
 - GUI_sample.mot ファイルをマイコンに書き込む。

## GUI widget フレームワークの概要

- 比較的小さな、液晶用に、機能を絞った GUI を提供します。
- C++17 を使い、少ない手順で通常やりたい事が出来るように工夫しています。
- 小メモリーで、小さなフットプリントでも実装が出来るように工夫しています。
- 基本的に記憶割り当てを使わないようにしています。
- シンプルで見やすい表示を行い、リッチな表示も可能になるようにしています。

-----
   
License
----
   
MIT open source license   
