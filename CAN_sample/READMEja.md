Renesas RX64M, RX71M, RX66T, RX72N CAN 通信サンプル
=========
   
[English](README.md)
   
## 概要
RX マイコンを使った CAN 通信サンプルプログラム   
CAN ポートに CAN バス・トランシーバーを接続する必要があります。   
CAN が複数チャネルある場合、チャネルを切り替えて通信する事が出来ます。   
※「main.cpp」で、環境変数「LOOP」を有効にします。
   
## プロジェクト・リスト

- main.cpp
- RX64M/Makefile
- RX71M/Makefile
- RX66T/Makefile
- RX72N/Makefile
- README.md
- READMEja.md
   
## ハードウェアーの準備

- ベースクリスタルが異なる場合は、typedef のパラメーターを変更する。
- Makefile で、各モジュール別の設定周波数を宣言している。
- RX64M: 120MHz (12MHz)
- RX71M: 240MHz (12MHz)
- RX66T: 160MHz (10MHz)
- RX72N: 240MHz (16MHz) for 'RX72N Envision Kit'
- LED を指定のポートに接続する。
- RX72N Envision kit の場合は、ボード上の青色 LED を利用する。
- CAN ポートに、CAN バス・トランシーバーを接続します。
- CAN バス・トランシーバーには適切なターミネーター抵抗を接続します。
- CAN バス・トランシーバーは、3.3V で動作する品種が必要です。
   
### CAN バス・トランシーバーの代表的な品種

Texas Instruments: SN65HVD23x
   
### RX64M/RX71M の場合

- 複数チャネル対応
   
### RX66T の場合

- シングルチャネル

### RX72N Envision Kit の場合

- プログラムは複数チャネルに対応していますが、CAN ポートにアクセス出来ない為、シングルチャネルです。

## リソースの準備

- 特に無し
   
## ビルド方法

- 各プラットホームディレクトリーに移動、make する。
- can_sample.mot ファイルを書き込む。
   
## 動作

- LED が 0.25 秒間隔で点滅する。
- ターミナルでシリアル接続を行い、対話式コマンドで通信を行う。

## 対話コマンド

対話形式で、CAN データ送信、受信の確認等が出来ます。

- プログラムを起動すると、常に全ての ID を受信します。
- ID の数が限界を超えると、メモリ不足でクラッシュするかもしれません。
- send_loop コマンドにより、乱数で生成した ID、データを連続で送信します。
- ID を補足する機能（map）は、チャネル０番のみに備わっています。
- RX64M/RX71M では、２チャネルの CAN を有効にします。
- CAN1（２チャネル）の受信は、受信したデータを常に表示します。
- MB-no はメールボックスの番号です。
- メールボックス関係のコマンドは、デバッグ用です。

```
    ch CH-no               set current CAN channel (CH-no: 0, 1)
    send CAN-ID [data...]  send data frame
    stat MB-no             stat mail-box (MB-no: 0 to 31)
    list MB-no             list mail-box (MB-no: 0 to 31)
    map [CAN-ID]           receiving CAN-ID list
    clear                  clear map
    dump CAN-ID            dump frame data
    send_loop NUM          random ID, random DATA, send loop
    help                   command list (this)
```
   
-----
   
License
----

[MIT](../LICENSE)
