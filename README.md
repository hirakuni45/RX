Renesas RX マイコン
=========

RX sources 

## RX 各ディレクトリー、及び概要など

> これはルネサス RX マイコンと、そのコンパイラである rx-elf-gcc,g++ によるプログラムです。
>
> 現在では、Windows、OS-X（Linuxでも多分動作する） で動作確認が済んだ、専用書き込みプログラムも実装
> してあり、複数の環境で、開発が出来るようになっています。
>
> プロジェクトは、Makefile、及び、関連ヘッダー、ソースコードからなり、専用のスタートアップルーチン、
> リンカースクリプトで構成されています。
> その為、専用のブートプログラムやローダーは必要なく、作成したバイナリーをそのまま ROM へ書いて実行
> できます。
>
> デバイスＩ／Ｏ操作では、C++ で構成されたテンプレートクラスライブラリーを活用出来るように専用の
> ヘッダーを用意してあり、各種デバイス用の小さなクラスライブラリーの充実も行っています。

## RX プロジェクト・リスト
 - /RX63T          --->   RX63T 専用のデバイス定義クラス
 - /RX621          --->   RX621 専用のデバイス定義クラス
 - /fatfs          --->   ChaN 氏作成の fatfs ソースコードと RX マイコン向け RSPI コード
 - /common         --->   共有クラス、ヘッダーなど
 - /rxprog         --->   RX フラッシュへのプログラム書き込みツール（Windows、OS-X、※Linux 対応）
 - /rx63t_chager   --->   RX63T を使ったモバイルバッテリー・プロジェクト

## RX 開発環境

 - RX 用コンパイラ（rx-elf）は gcc-4.9.3 を使っています。 
 - Windows では、事前に MSYS2 環境をインストールしておきます。

 - msys のアップグレード

```sh
   update-core
```

 - コンソールを開きなおす

```sh
   pacman -Su
```

コンパイラのビルド方法：（MSYS2）

 - gcc、texinfo、gmp、mpfr、mpc、diffutils コマンドなどをインストール
```sh
   pacman -S gcc
   pacman -S texinfo
   pacman -S mpc-devel
   pacman -S diffutils
   pacman -S automake
```

 - binutils-2.25.1 をビルド
```sh
   cd
   tar xfvz binutils-2.25.1.tar.gz
   cd binutils-2.25.1
   mkdir rx_build
   cd rx_build
   ../configure --target=rx-elf --prefix=/usr/local/rx-elf --disable-nls
   make
   make install
```

 -  /usr/local/rx-elf/bin へパスを通す
 -  コンソールを開きなおす。
 -  C コンパイラをビルド
 -  ※少し古い gcc では、MSYS2 環境を認識しない為、automake の設定をコピーする
``` sh
    cd
    tar xfvz gcc-4.9.3.tar.gz
    cd gcc-4.9.3
    cp /usr/share/automake-1.15/config.guess .
    mkdir rx_build
	cd rx_build
    ../configure --prefix=/usr/local/rx-elf --target=rx-elf --enable-languages=c --disable-libssp --with-newlib --disable-nls --disable-threads --disable-libgomp --disable-libmudflap --disable-libstdcxx-pch --disable-multilib --disable-bootstrap
    make
    make install
```

 -  newlib をビルド
``` sh
    cd
    tar xfvz newlib-2.2.0.tar.gz
	cd newlib-2.2.0
    mkdir rx_build
    cd rx_build
    ../configure --target=rx-elf --prefix=/usr/local/rx-elf
	make
    make install
```

 -  C++ コンパイラをビルド
``` sh
    cd
    cd gcc-4.9.3
    cd rx_build
    ../configure --prefix=/usr/local/rx-elf --target=rx-elf --enable-languages=c,c++ --disable-libssp --with-newlib --disable-nls --disable-threads --disable-libgomp --disable-libmudflap --disable-libstdcxx-pch --disable-multilib --disable-bootstrap
    make
    make install
```

 - rxprog のビルド（MSYS2）
``` sh
    cd rxprog
    make
    mkdir ~/bin
    cp rx_prog.exe ~/bin/.
    cp rx_prog.conf ~/bin/.
　　※~/bin にパスを通しておく。
```
 - rx_prog.conf を編集して、接続する COM ポート、ボーレートの設定をする。
 - /dev/ttyS10 ---> COM11 に相当します。（数字に＋１する）

## 各プロジェクトの動作

 - 各プロジェクトのリストを参考に、プロジェクトのディレクトリーに移動します。

 - ビルドします。（自動で、従属規則が生成されます）
``` sh
    make
```

 - プログラムの書き込み（rx_prog が必要）
``` sh
    make run
```

License
----

MIT
