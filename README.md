Renesas RX マイコン
=========
![R5F564ML](RXchipS.jpg)

## RX 各ディレクトリー、及び概要など

 これはルネサス RX マイコンと、そのコンパイラである rx-elf-gcc,g++ によるプログラムです。   
   
 現在は、Windows、OS-X、Linux で動作確認が済んだ、専用書き込みプログラムも実装してあり、   
 複数の環境で、開発が出来るようになっています。   
 ※現在サポートされ、動作確認済みデバイスは RX24T、RX64M、RX65N、RX71M となっており、   
 デバイスクラスを日々拡張しています。（RX63T、RX621、RX62N は保留状態です）   
 ※ディレクトリー構成など日々アップデートしており、乖離も発生するので注意下さい。   
 ※不明な点などあったら気軽にメールか、BBS にて質問を下さい。
   
 プロジェクトは、Makefile、及び、関連ヘッダー、ソースコードからなり、専用のスタートアップ   
 ルーチン、リンカースクリプトで構成されています。   
 テンプレートデザインパターンによるデバイス制御クラスは、柔軟で、簡潔、自在な機能を提供します。   
 その機能性により、難解で複雑な設定や、別プログラムによるコード生成を必要としません。   
   
 通常「make」コマンド一発で、従属規則生成から、コンパイル、リンクまで完了する為、IDE を   
 必要としません。  
 その為、専用のブートプログラムやローダーは必要なく、作成したバイナリーをそのまま ROM へ   
 書いて実行できます。   
   
 デバイスＩ／Ｏ操作では、C++ で実装されたテンプレート・クラス・ライブラリーを活用して専用の   
 ヘッダーを用意してあり、ユーティリティー的クラス・ライブラリーの充実も行っています。   
 ※一部、ルネサス製のライブラリを利用しています。   
   
## RX プロジェクト・リスト
 - /RX600　　　　　　　---> RX マイコン共通デバイス定義クラス
 - /RX24T　　　　　　　---> RX24T 専用のデバイス定義クラス、リンカースクリプト
 - /RX63T　　　　　　　---> RX63T 専用のデバイス定義クラス、リンカースクリプト
 - /RX64M　　　　　　　---> RX64M 専用のデバイス定義クラス、リンカースクリプト
 - /RX71M　　　　　　　---> RX71M 専用のデバイス定義クラス、リンカースクリプト
 - /RX65x　　　　　　　---> RX651, RX65N 専用デバイス定義クラス、リンカースクリプト
 - /RX66T　　　　　　　---> RX66T 専用デバイス定義クラス、リンカースクリプト
 - /ff12b　　　　　　　---> ChaN 氏作成の fatfs ソースコードと RX マイコン向けハンドラ
 - [common](./common)　　　　　　 ---> 共有クラス、ヘッダーなど
 - [chip](./chip)　　　　　　　 ---> I2C、SPI、など各種デバイス固有制御ライブラリ
 - [graphics](./graphics)　　　　　 ---> グラフィックス関係操作クラス
 - [sound](./sound)　　　　　　　---> サウンド関係操作クラス
 - /r_net　　　　　　　---> ルネサス T4(TCP/UDP) ライブラリと、C++ ハンドラ、ラッパー
 - /libmad　　　　　　 ---> MP3 デコード、mad ライブラリ
 - /jpeg-6b　　　　　　---> JPEG ライブラリ
 - [rxprog](./rxprog)　　　　　　 ---> RX フラッシュへのプログラム書き込みツール（Windows、OS-X、Linux 対応）
 - [FIRST_sample](./FIRST_sample)　　　　---> 各プラットホーム対応 LED 点滅プログラム
 - [RAYTRACER_sample](./RAYTRACER_sample)　　　---> 各プラットホーム対応 レイトレーシング・ベンチマーク
 - [SCI_sample](./SCI_sample)　　　　　---> 各プラットホーム対応 SCI サンプルプログラム
 - /rx24t_SDC_sample　 ---> RX24T を使った SD カードの動作サンプル
 - /rx24t_GPS_sample　 ---> RX24T を使った GPS の動作サンプル
 - /rx24t_DATA_FLASH_sample ---> RX24T を使った内臓データ・フラッシュ操作サンプル
 - /rx24t_LOGGER　　　 ---> RX24T を使ったデータロガー・プロジェクト
 - /rx64m_SDRAM_sample ---> RX64M を使った SDRAM の制御サンプル（128Mビット×2、32ビットバス）
 - /rx64m_RTC_sample　 ---> RX64M を使った 内臓 RTC の動作サンプル
 - /rx64m_TPU_sample　 ---> RX64M を使った TPU の制御サンプル（タイマー割り込み）
 - /rx64m_DMAC_sample　---> RX64M を使った DMAC 制御のサンプル（メモリー操作）
 - /rx64m_DA_sample　　---> RX64M を使った 内臓 D/A 変換、TPU、DMAC のサンプル
 - /rx64m_AUDIO_sample ---> RX64M を使った SD カード上のオーディオファイルを内臓 D/A で再生する 
 - /GR-KAEDE_ftps　　　---> ルネサス製の RX64M 搭載マイコンボード向けサンプル（FTP サーバー）
 - /GR-KAEDE_http　　　---> ルネサス製の RX64M 搭載マイコンボード向けサンプル（http サーバー）
 - /RTK5_AUDIO_sample　---> ルネサス製 RTK5RX65N マイコンボード オーディオプレイヤー
 - /RTK5_SIDE　　　　　---> ルネサス製 RTK5RX65N マイコンボード Space Invaders エミュレーター
 - /RTK5_NESEMU　　　　---> ルネサス製 RTK5RX65N マイコンボード NES エミュレーター
 - [/LICENSE](./LICENSE)　---> ライセンス表記ファイル
   
## RX 開発環境準備（Windows、MSYS2）
   
 - Windows では、事前に MSYS2 環境をインストールしておきます。
 - MSYS2 には、msys2、mingw32、mingw64 と３つの異なった環境がありますが、RX マイコン用 gcc    
   の構築を行う必要があるので、msys2 で行います。
   
 - msys2 のアップグレード

```
   pacman -Sy pacman
   pacman -Syu
```

 - コンソールを開きなおす。（コンソールを開きなおすように、メッセージが表示されるはずです）

```
   pacman -Su
```
 - アップデートは、複数回行われ、その際、コンソールの指示に従う事。
 - ※複数回、コンソールを開きなおす必要がある。

 - gcc、texinfo、gmp、mpfr、mpc、diffutils、automake、zlib、tar、make、unzip、git コマンドなどをインストール
```
   pacman -S gcc
   pacman -S texinfo
   pacman -S mpc-devel
   pacman -S diffutils
   pacman -S automake
   pacman -S zlib
   pacman -S tar
   pacman -S make
   pacman -S unzip
   pacman -S zlib-devel
   pacman -S git
```
   
---
## RX 開発環境準備（OS-X）

 - OS-X では、事前に macports をインストールしておきます。（brew は柔軟性が低いのでお勧めしません）
 - OS−X のバージョンによっては、事前に X−Code、Command Line Tools などのインストールが必要になるかもしれません）

 - macports のアップグレード

```
   sudo port -d self update
```

 - ご存知とは思いますが、OS−X では初期段階では、gcc の呼び出しで llvm が起動するようになっています。
 - しかしながら、現状では llvm では、gcc のクロスコンパイラをビルドする事は出来ません。
 - そこで、macports で gcc をインストールします、バージョンは５系を使う事とします。
```
   sudo port install gcc5
   sudo ln -sf /opt/local/bin/gcc-mp-5  /usr/local/bin/gcc
   sudo ln -sf /opt/local/bin/g++-mp-5  /usr/local/bin/g++
   sudo ln -sf /opt/local/bin/g++-mp-5  /usr/local/bin/c++
```
 - 再起動が必要かもしれません。
 - 一応、確認してみて下さい。
```
   gcc --version
```
   
```
   gcc (MacPorts gcc5 5.4.0_0) 5.4.0
   Copyright (C) 2015 Free Software Foundation, Inc.
   This is free software; see the source for copying conditions.  There is NO
   warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
   
 - texinfo、gmp、mpfr、mpc、diffutils、automake コマンドなどをインストール
```
   sudo port install texinfo
   sudo port install gmp
   sudo port install mpfr
   sudo port install libmpc
   sudo port install diffutils
   sudo port install automake
```

---
## RX 開発環境準備（Ubuntu）

Linux 環境は、複数あるので、ここでは「Ubuntu 16.04 LTS」環境の場合を書いておきます。

 - texinfo、gmp、mpfr、mpc、diffutils、automake コマンドなどをインストール
```
   sudo apt-get install texinfo
   sudo apt-get install libgmp-dev
   sudo apt-get install libmpfr-dev
   sudo apt-get install libmpc-dev
   sudo apt-get install diffutils
   sudo apt-get install automake
   sudo apt-get install zlib1g-dev
```

---
## RX 開発環境構築

 - RX 用コンパイラ（rx-elf-gcc,g++）は gcc-6.4.0 を使います。   
 - binutils-2.30.tar.gz をダウンロードしておく。   
 - gcc-6.4.0.tar.gz をダウンロードしておく。   
 - newlib-2.4.0.tar.gz をダウンロードしておく。   
 - binutils, gcc, newlib には複数のバージョンがありますが、組み合わせによっては   
   不適格なバイナリー（微妙に動作に問題がある）がビルドされる事が判っています。   
 - この不具合は、ルネサスのネットワークスタック（net_T4）を使った場合に起こります。
 - 何故そのような動作不良を起こすのかは、原因を特定出来ていません。
 - 現状で調査した組み合わせを列挙しておきます。
```
   binutils-2.27, gcc-4.9.4, newlib-2.2.0 ---> OK
   binutils-2.27, gcc-5.5.0, newlib-2.2.0 ---> OK
   binutils-2.27, gcc-5.5.0, newlib-2.4.0 ---> OK
   binutils-2.27, gcc-6.4.0, newlib-2.4.0 ---> OK
   binutils-2.28, gcc-6.4.0, newlib-2.4.0 ---> OK
   binutils-2.30, gcc-6.4.0, newlib-2.4.0 ---> OK (current)
   binutils-2.30, gcc-6.4.0, newlib-3.0.0 ---> NG 
```
 - 最新の gcc を使った方がより高速なコードになるようで、C++ の場合に特に効果が大きいです。
   
---
   
#### binutils-2.30 をビルド
```
   cd
   tar xfvz binutils-2.30.tar.gz
   cd binutils-2.30
   mkdir rx_build
   cd rx_build
   ../configure --target=rx-elf --prefix=/usr/local/rx-elf --disable-nls
   make
   make install     OS-X,Linux: (sudo make install)
```

 -  /usr/local/rx-elf/bin へパスを通す（.bash_profile を編集して、パスを追加）

```
   PATH=$PATH:/usr/local/rx-elf/bin
```

 -  コンソールを開きなおす。

```
   rx-elf-as --version
```

 -  アセンブラコマンドを実行してみて、パスが有効か確かめる。
  
#### C コンパイラをビルド
```
    cd
    tar xfvz gcc-6.4.0.tar.gz
    cd gcc-6.4.0
    mkdir rx_build
	cd rx_build
    ../configure --prefix=/usr/local/rx-elf --target=rx-elf --enable-languages=c --disable-libssp --with-newlib --disable-nls --disable-threads --disable-libgomp --disable-libmudflap --disable-libstdcxx-pch --disable-multilib --enable-lto
    make
    make install     OS-X,Linux: (sudo make install)
```
  
#### newlib をビルド
```
    cd
    tar xfvz newlib-2.4.0.tar.gz
	cd newlib-2.4.0
    mkdir rx_build
    cd rx_build
    ../configure --target=rx-elf --prefix=/usr/local/rx-elf
	make
    make install     OS-X: (sudo make install)
```
 - Linux 環境では、sudo コマンドで、ローカルで設定した binutils のパスを認識しないので、
「make install」が失敗します、その為、以下のようなスクリプトを書いて実行します。
```
#!/bin/sh
# file: rx_install.sh

PATH=${PATH}:/usr/local/rx-elf/bin
make install
```
   
```
    sudo rx_install.sh
```
   
---
     
#### C++ コンパイラをビルド
```
    cd
    cd gcc-6.4.0
    cd rx_build
    ../configure --prefix=/usr/local/rx-elf --target=rx-elf --enable-languages=c,c++ --disable-libssp --with-newlib --disable-nls --disable-threads --disable-libgomp --disable-libmudflap --disable-libstdcxx-pch --disable-multilib --enable-lto --with-system-zlib
    make
    make install     OS-X,Linux: (sudo make install)
```

---
   
 - ビルドしたコンパイラーコレクションを以下のリンクに上げてある。（MSYS2のみ）   
http://www.rvf-rc45.net/Renesas_GNU_Tools/ 

---
   
## RX プロジェクトのソースコードを取得
   
```
    git clone git://github.com/hirakuni45/RX.git
```
   
## RX 全プロジェクトのビルド
   
```
    sh all_project_build.sh [clean]
```
   
--- 
   
## RX デバイスへのプログラム書き込み方法

幾つかの方法がありますが、最も簡単で、コストがかからない方法は、シリアルインターフェースを使って   
書き込む方法です。   
※但し、書き込み速度は、あまり上がりません。   
USB インターフェース内臓の RX マイコンの場合は、USB でブートして接続する事もできますが、ドライバー   
は、Windows 版しか対応しないようです。（この辺りの事情は詳しく調査していない為間違っているかもしれません）   
   
また、全ての RX マイコンが USB インターフェースを内臓しているわけでは無い為、もっとも一般的な、   
シリアルインターフェースを使って書き込む方法を紹介します。   
シリアルインターフェースでの書き込みは、速度はそれなりですが、簡単確実で、接続も簡単。   
   
※シリアルポートとの接続、ブートモードへの切り替えについては、ハードウェアマニュアルに書かれていま   
すので参考にして下さい。   
通常、ＭＤ端子を、Ｌ又はＨにする事で、プログラムと内臓ＲＯＭの実行を切り替えできます。   
   
※USB シリアル変換モジュールなどを使うと、電源も取れて簡単です。   
※（秋月電子、シリアル変換モジュール）http://akizukidenshi.com/catalog/g/gK-06894/   
※（CP2102 シリアル変換モジュール）https://www.amazon.co.jp/%E3%80%90%E3%83%8E%E3%83%BC%E3%83%96%E3%83%A9%E3%83%B3%E3%83%89%E5%93%81%E3%80%91USB%E2%86%92TTL-%E3%82%B3%E3%83%B3%E3%83%90%E3%83%BC%E3%82%BF%E3%83%BC%E3%83%A2%E3%82%B8%E3%83%A5%E3%83%BC%E3%83%AB-%E3%82%A2%E3%83%80%E3%83%97%E3%82%BF%E3%83%BC-CP2102-%E3%82%B7%E3%83%AA%E3%82%A2%E3%83%AB%E5%A4%89%E6%8F%9B/dp/B008RF73CS/ref=sr_1_1?ie=UTF8&qid=1477589109&sr=8-1&keywords=%EF%BD%83%EF%BD%90%EF%BC%92%EF%BC%91%EF%BC%90%EF%BC%92
(1) RXD シリアル受信   
(2) TXD シリアル送信   
(3) VCC 電源（５Ｖ又は３．３Ｖ）   
(4) GND 電源 ０Ｖ   
※３．３Ｖは限られた電流しか取り出せない為、必ずレギュレーターが必要です。   
※中国製の格安なモジュールは、品質が安定していない為、お勧めしません、それらの事   
項を理解していて対処出来る人だけ利用すると良いと思います。   
   
 - 接続方法、ブートモードの設定などは、各デバイスのハードウェアー・マニュアルに詳細があります。   
   
## RX フラッシュプログラマーの構築

 - 現在、RX63T、RX24T、RX64M へのフラッシュ書き込みを確認しています。
 - リセットは、制御していないので、書き込み時にリセット信号をアサートする必要があります。
 - 現在のバージョンでは、消去、書き込み、比較 の動作のみ実装されています。
 - コードプロテクトの ID 設定や比較などは未実装です。
 - RX24T、RX63T では、接続が確立した時に、消去が自動で行われる為、消去動作は無視されます。
 - rx_prog のビルドには「boost」が必要です。（通常最新バージョンを使う）
 - boost はヘッダーのみ利用なので、ビルドの必要はありません。
 - mingw64 環境などに pacman を使い boost をインストールして使っています。

``` 
    pacman -S mingw-w64-x86_64-boost   
```

 - rxprog のビルド（MSYS2）
 - ビルドした実行ファイルは、/usr/local/bin に配置します。

```
    cd rxprog
    make
    make install
　　※/usr/local/bin にパスを通しておく。
```
 - rx_prog.conf を編集して、接続する COM ポート、ボーレートの設定をする。
 - /dev/ttyS10 -> COM11 に相当します。（数字に＋１する）
 - 「rx_prog.conf」には、標準のシリアルポートを記述できます、自分の環境に合わせて設定しておくと良いでしょう。
 - ポートの設定は、開発環境の違いに対応できるように、Windows、OS-X、Linux と環境別のポートを設定できます。
 - 各プロジェクトの「Makefile」には、「make run」で書き込めるスクリプトが設定されています。
   
---
   
## Renesus ENVISION KIT-RX65N を使った開発
![R5F564ML](RTK5RX65N.jpg)

 - ルネサスが販売する「RTK5RX65N」は、LCD 付きでありながら低価格で高機能なボードです。   
 - もちろんラズベリーPiなどとは比較はできませんが、スタンドアロンで動かす事の出来る手頃なマイコンボードだと思えます。
 - また、このボードには、「E1 Lite エミュレーター」が内臓されており、USB 接続で、簡単にプログラムを書き込む事が出来ます。（Windows 環境で、Renesus Flash Programmer を使って書き込める）
 - DIP SW 1, 1 を「ON」にする事で、内臓エミュレーターが有効になり、「Renesas Flash Programmer」
   実行バイナリーを書き込めます。
 - DIP SW 1, 1 を「OFF」にする事で、書き込んだプログラムが単独で実行します。
 - 初期状態では、SD カード、イーサーネット関係の部品などが抜けていますが、後から自分で取り付ける事が出来ると思います。
 - このボード標準の SD カードソケットは、製造が終了しており、日本では入手性が悪く、価格も高い為、別の方法を推奨します。
 - 秋月電子製のマイクロ SD ソケットアダプタを介して接続するのが簡単です。   
![R5F564ML](RTK5_MSD.jpg)
![R5F564ML](RTK5_side.jpg)

---
## 何故、独自の開発環境（フレームワーク）を使うのか？

現在、ルネサス社が提供する gcc ベースの IDE 環境を使う事が出来ますが、私は、IDE が嫌いです。   
マウスでメニューを操作する必要があり、操作の方法を新たに覚える必要があるのには、抵抗があり   
ます。   
それと、gcc と言っても、独自の改造がしてあり、完全に「素」の gcc とは言えないのが問題と   
思います。   
※ルネサス社には独自の「開発環境」に対する考え方がありますが、必ずしも、それが、自分のス   
タイルに合うとは限りません。   
   
自分は、昔ながらの CUI 環境の方が手っ取り早く、操作性や見通しが良く扱いやすいです。   
emacs、gcc、make、があれば十分なのです。   
また、歴史的に、開発ツールは「有償であるべきである」との考えがあります。（サポートも含む）   
しかしながら、現代においては、数十万円のコンパイラに投資して製品を開発する事が出来るのは   
大量生産が可能な機器に絞られると思います、それゆえ、gcc で開発をするのは、当然の結果と言   
えるのだと思えます。   
※公開してある「Makefile」には独自の工夫がしてあり、最小限の編集で、プロジェクトをビルド   
出来るように自動化の為のスクリプトが入れてあります。   
※通常の「Makefile」は、従属規則を書くのは「自動」ではありません、新規にファイルを追加し   
たら、それに伴って、従属規則を更新しなければなりません。   
また、ソースファイルにインクルードしているローカルなファイルを変更した場合にもこれを怠る   
と、関係するソースファイルが適切にコンパイルされず、古いオブジェクトをリンクしてしまう事   
があります。   
この「Makefile」では、「従属規則」の生成は、ほぼ自動化してあり、そのようなトラブルが起こ   
る事を最小限にする事が出来ます。   
※事前に、何かファイルを生成したりする必要が全く無いように工夫してあります。   
ユーザーは、ターゲット名、リンクするソースを適宜編集するだけです。   
後は「make」と打てば、従属規則（どのソースがどのヘッダーをインクルードしているか？）は自動   
で生成します。   
また C++ では、ヘッダーと実装を分ける必要がほぼ無くなる為、Makefile を編集してソースを追加
する事がほぼ無くなります。   
   
---
   
次の問題は、ルネサス社が提供する、ハードウェアー定義、デバイスドライバーです。   
これらは、多くの場合、ルネサス社の標準コンパイラ向けのコードで、gcc ではコンパイルできな   
い場合があり、また、Ｃ言語をベースにした物であり、不満があります。   
また、公開されているデバイスドライバーも、ファイル名、構成、見通し、など、かなり不満があ   
ります。   
※C++ から、C 言語の関数を呼ぶ事は可能なのだから、自分でわざわざデバイスドライバーを作る   
のは、無意味だと言った人もいますが、その人の考え方と、私は根本的に異なります。   
「より良い」と思う物を作りたいだけです。   
Arduino は C++ がベースとは言え、C++ の優れた機能をあまり活用していません C++ を前面にし   
た、新しい試みを開拓したいと思っていました。   
   
最初にルネサス社のマイコンを始めた段階で、まず gcc の構築から初めて、十分実用になる事を確   
認しました。   
次に、C++ の理解を深める学習の一環で、デバイス定義をクラス化して、C++ ぽく、デバイスにアク   
セスするクラスを実装しました。   
デバイスドライバも、より簡単に、少ない手順で、使いたいので、多くを独自に実装しています。   
※ルネサス社が提供する、ハードウェアー定義の「iodefine.h」は、独自の環境でしかコンパイルす   
る事ができず、また、可読性が非常に悪いです、本来モジュール定義コードに詳細なハードウェアー   
マニュアルを添付すべきと思っているくらいです。   
※ビットフィールドを定義する方法は、標準化委員会では、「バイト」単位では認めていても、それ   
以外は規約違反（バイトオーダーで表現が異なる為）です。   
私が提供する C++ ベースのデバイス定義クラスは、C++14以降なら、どの環境でも、特殊な定義無し   
で完全にコンパイルする事が可能です。   
※現在、最適化無しでコンパイルした場合、リンクに失敗します、修正中です。   
   
※ルネサス社純正コンパイラは、独自の拡張がされており、それらは標準化委員会が定めた規約から   
逸脱する場合もあるように思います、そのような独自拡張されたコンパイラ向けに書かれたソースは   
他のコンパイラではそのままコンパイル出来ない場合もあり、あまりメリットを感じません。   
   
「gcc 環境ではまともなデバッグが出来ない」
と言う人がいますが、本当にそうでしょうか？   
確かに IDE には、見た目と操作性が良い GUI があり、そのような場合は時間の短縮になる場合もあ   
りますが、自分の経験では、そのような環境がどうしても必要と感じた事はほぼ無く、シュミレータ   
ーを使ったり、PC 上でエミュレーションするなど、工夫次第でどうにでもなります。   
   
---
## 何故、C++ なのか？
   
コンピューター言語は、マシンの為にあるのでは無く、人間の可読性の為に存在すると思っています。   
それなら、マシンに媚びた構成では無く、より人間が理解しやすく間違いが少ない方が良いと思いま   
す。   
C++ は、C 言語に文法が似ていますが全く異なったコンピュータ言語です。   
※多くの C 言語プログラマーがこの事実を受け入れないでいます、C++ を習得するには、全く新しい   
言語を習得する覚悟と時間（コスト）が必要だと思います。（それに見合う価値があると思います）   
   
RX71M は 240MHz で動作し、512KB のメモリを内蔵しています、この「進化」はこれからも加速して   
いく事と思います、そんな状況なのに、何故、開発者がマシンに寄った環境に甘んじて開発を行わな   
ければいけないのでしょうか？   
C++ での実装は、それら対する一つの回答です、また、コンパイラの進化により、ますます最適化が   
加速する事と思います。   
   
---
   
☆以下は C++ 的 LED を点滅するプログラム例です。   
(1) マイコン接続のクリスタルは 12MHz   
(2) LED の接続ポートは、PORT0、B7   
(3) 点滅間隔は 0.25 秒   
※マイコンの動作速度は、Makefile で設定   
※他、シリアル通信、ＳＤカードアクセスなど豊富なサンプルがあります。   
```C++
#include "common/renesas.hpp"

namespace {
    typedef device::system_io<12000000> SYSTEM_IO;
    typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
    SYSTEM_IO::setup_system_clock();

    LED::DIR = 1;
    while(1) {
        utils::delay::milli_second(250);
        LED::P = 0;
        utils::delay::milli_second(250);
        LED::P = 1;
    }
}
```
   
---
   
☆以下は C++ 的 SCI で通信するプログラム例です。   
(1) SCI の設定に関する部分のみで、他は LED 点滅プログラムと共通です。   
(2) SCI の標準ポートは、port_map.hpp により定義されており、選択するポートが複数ある場合   
「第二候補」や「第三候補」を設定すればよく、面倒な設定を行う必要はありません。   
(3) ボーレートは整数で設定すれば良く、内部で、設定周波数から自動的に計算されます。   
(4) 割り込みを使う場合でも、使わない場合（ポーリング）でも使う事が出来ます。   
(5) 送信、受信は、固定長 FIFO クラスを通して行われ、サイズは、自由に定義する事が出来ます。
(6) sci_putch、sci_getch 関数は、POSIX のファイル関数から呼ばれるので、外部からリンクできるようにしておきます。
(7) 上記関数は、stdout、stdin、stderr ディスクリプタからアクセスされます、従って、printf 関数も使う事が出来ますが、色々な理由で推奨しません「utils::format」を使って下さい、その方がサイズが小さくなり、自由度が大きく便利で安全です。   
```
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"

namespace {

//  SCI9 を使用
    typedef device::SCI9 SCI_CH;

    typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
    typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

    typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::option::SECOND> SCI;
    SCI     sci_;
}

extern "C" {

    // syscalls.c から呼ばれる、標準出力（stdout, stderr）
    void sci_putch(char ch) { sci_.putch(ch); }

    void sci_puts(const char* str) { sci_.puts(str); }

    // syscalls.c から呼ばれる、標準入力（stdin）
    char sci_getch(void) { return sci_.getch(); }

    uint16_t sci_length() { return sci_.recv_length(); }
}

//-----

{  // メイン、SCI 開始
    uint8_t intr = 2;        // 割り込みレベル
    uint32_t baud = 115200;  // ボーレート
    sci_.start(baud, intr);
}

//-----
{  // メイン、SCI 出力
    utils::format("Start SCI\n");
}
```
   
-----
   
License
----

MIT
