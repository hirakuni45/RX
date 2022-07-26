GUI Widgets フレームワーク
=========

[英語版](./README.txt)

## 概要

- GUI Widget は、モダンで判りやすい操作を提供するフレームワーク。
- C++17 の機能を利用して、なるべく簡単な手続きと判りやすさで、機能を実装する事が出来るように設計しています。
- タッチパネルによる GUI 操作。
- ソフトウェアー、又は、DRW2D エンジンによるレンダリングに対応出来る構成。
- 記憶割り当てを利用しない、スタテック構造。（テンプレートパラメーターにより扱う widget 数を定義）
- リソースの消費を抑えた設計。
- 描画を最適化させる為の仕組み。
- 良く使われるであろう場面を想定した Widget 各種。
- 各部品の使い方や実装方法が判るようにサンプルプログラム「[GUI_sample](../GUI_sample/)」が用意されています。

---

## widget の基本構成

- 以下のようなファイル（クラス）により構成されます。
- 全体を統合する「widget_director.hpp」と、各部品となっています。
- 各部品は、「widget.hpp」基本クラスを継承しています。
- 機能を使う場合、「widget_director.hpp」をインクルードして使います。

|ファイル名|機能|
|---|---|
|[widget.hpp](./widget.hpp)|Widget 基本クラス|
|[button.hpp](./button.hpp)|Widget ボタン|
|[check.hpp](./check.hpp)|Widget チェックボックス|
|[group.hpp](./group.hpp)|Widget グループ|
|[radio.hpp](./radio.hpp)|Widget ラジオボタン|
|[frame.hpp](./frame.hpp)|Widget フレーム|
|[dialog.hpp](./dialog.hpp)|Widget ダイアログ|
|[term.hpp](./term.hpp)|Widget ターミナルクラス|
|[box.hpp](./box.hpp)|Widget ボックス|
|[text.hpp](./text.hpp)|Widget テキスト|
|[textbox.hpp](./textbox.hpp)|Widget テキストボックス|
|[slider.hpp](./slider.hpp)|Widget スライダー|
|[menu.hpp](./menu.hpp)|Widget メニュー|
|[spinbox.hpp](./spinbox.hpp)|Widget スピンボックス|
|[toggle.hpp](./spinbox.hpp)|Widget トグルスイッチ|
|[progress.hpp](./spinbox.hpp)|Widget プログレスバー|
|[filer.hpp](./filer.hpp)|ファイル選択クラス|
|[key_asc.hpp](./key_asc.hpp)|ASCII ソフトキーボード|
|[widget_director.hpp](./widget_director.hpp)|Widget ディレクター|

### widget における座標の設定と大きさの設定

- 座標は、int16_t 型で定義されています。
- 「vtx::srect(x, y, w, h)」型は、(x)Ｘ座標、(y)Ｙ座標、(w)Ｘサイズ、(h)Ｙサイズになっています。

### ボタン

- widget button は、シンプルな押しボタンの機能を提供します。
- 座標、大きさ、ボタン文字列 を指定します。
- 文字列、基本色は、いつでも変更が可能です。

定義：

```C++
	typedef gui::button BUTTON;
	BUTTON	button_(vtx::srect(10, 10, 80, 32), "OK");
```

※上記例では、10,10 の位置に、横 80、高さ 32 のボタン、ボタン内文字 "OK" を定義しています。

制御：

```C++
	button_.enable();
	button_.at_select_func() = [=](uint32_t id) {
		utils::format("Select Button: %d\n") % id;
	};
```

※ボタンが押される度に、"Select Button: " と、ID 番号がコンソールに出力されます。

### チェックボックス

### グループ

### ラジオボタン

---

License
---

MIT
