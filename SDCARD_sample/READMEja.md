Renesas RX24T, RX64M, RX65N SD-CARD アクセス・サンプル
=========

## 概要

SD カード・アクセス、サンプルプログラム   

- ファイルシステムには FatFs (Version ff13c) を利用
- SPI (SPI モード) 又は、RX 内臓 SDHI (SD モード) を利用したサンプル
- ディレクトリーのリスト (dir)
- ディレクトリーの移動 (cd)
- ディレクトリーパスの表示 (pwd)
- 容量、空き容量表示 (free)
- 時間の設定、表示 (time)
- SD カードの書き込み (write)
- SD カードの読み出し (read)

※「time」コマンドは、RTC がサポートされている場合に機能する。

SPI モード：   
ソフト SPI、又は RSPI を使ったもの   

SD モード：   
SDHI (4 ビット) を使ったもの   

|ターゲット|インターフェース|RTC|
|---------|---------------|---|
|RX24T|RSPI|△|
|RX64M|Soft SPI|○|
|RX65N|SDHI|×|

※RX24T では、I2C 接続の RTC を利用する事が出来ます。
※RX64M では、内臓 RTC を利用しています。
※RX65N Envision Kit では、内臓 RTC は無効になっています。

## RX マイコンにおける SDHI 内臓デバイス

主要な RX マイコンで SDHI を内臓するデバイスは以下のようになっています。

|デバイス|コア|SDHI|デフォルト|ハイスピード|
|----------------|---|---|------------|------------|
|R5F564MxDxxx|RX64M|○|10MBits/s|15MBits/s|
|R5F564MxHxxx|RX64M|○|10MBits/s|15MBits/s|
|R5F564MxCxxx|RX64M|×|-|-|
|R5F564MxGxxx|RX64M|×|-|-|
|R5F565xxAxxx|RX65x|×|-|-|
|R5F565xxBxxx|RX65x|○|12.5MBits/s|25MBits/s|
|R5F565xxDxxx|RX65x|○|12.5MBits/s|25MBits/s|
|R5F565xxExxx|RX65x|×|-|-|
|R5F565xxFxxx|RX65x|○|12.5MBits/s|25MBits/s|
|R5F565xxHxxx|RX65x|○|12.5MBits/s|25MBits/s|
|R5F571MxDxxx|RX71M|○|10MBits/s|15MBis/s|
|R5F571MxHxxx|RX71M|○|10MBits/s|15MBis/s|
|R5F571MxCxxx|RX71M|×|-|-|
|R5F571MxGxxx|RX71M|×|-|-|

RX65N Envision Kit:

<img src="../docs/RTK5RX65N.jpg" width="50%">

**RX65N Envision Kit には、R5F565NEDDFB が実装されており、SDHI を利用する事が出来ます。**

---

## SD カードソケットと電源制御の接続

### RX24T (RSPI-A)

|ピン名|LFQFP100|SD ピン|SD 機能|備考|
|---|---|---|---|---|
|P22/MISOA|66|DAT0(7)|SO|pull-up(22K)|
|P23/MOSIA|65|CMD(2)|SI||
|P24/RSPCKA|64|CLK(5)|SCLK|damping-register(22)|
|P65|69|DAT3(1)|SELECT||
|P64|70|-|Power CTRL|active-low|
|P63|74|-|CardDetect|active-low|

### RX65N (SDHI) for RX65N Envision Kit
RX65N Envision Kit は SD カードソケットと、電源制御 IC が未実装である為、実装する必要があります。   

SD カードソケットは、入手が困難で、購入出来てもコストが高いので、秋月電子で購入が可能なマイクロ SD 基板を流用します。   
また、電源制御 IC も入手性とコストの関係で、汎用の MOS-FET を使いました。   
※オリジナルＳＤカードソケット「SD/MMCカードソケット：101-00565-64（AMPHENOL COMMERCIAL PRODUCTS製）」   
※オリジナルＳＤカード電源用ゲートＩＣ「ISL61861BIBZ」   
※電源制御は、無くても動作が可能ですが、一応制御していますが、電源電圧の確認は省略しています。   

<a href="http://akizukidenshi.com/catalog/g/gK-05488/" target="_blank">秋月電子、マイクロ SD スロット基板</A>   
<img src="../docs/SD_CARD.jpg" width="40%">   
<a href="http://akizukidenshi.com/catalog/g/gI-03942/" target="_blank">秋月電子、ＰｃｈチップＭＯＳＦＥＴ　ＤＭＧ３４１５Ｕ（２０Ｖ４Ａ）:</A>   
<img src="../docs/I-03942.jpg" width="40%">

![RTK5_MicroSD_PSW.jpg](../docs/RTK5_MicroSD_PSW.jpg)

<img src="../docs/RTK5_SD_Circuit.png" width="75%">

※ライトプロテクトは利用していません。   
SD カードの制御信号や、バスはプルアップされており、電源制御からプルアップ電圧の供給を受けています。   
※これは、結構「キモ」な部分で、常に内臓電源でプルアップすると、SD カードの電源を切断しても、内蔵電源から、プルアップ抵抗を経由して、電流が流れてしまい、微妙な電圧が SD カードに供給される状態となり、再初期化を行う場合に失敗する場合があるかもしれません。   
※クロック信号、コマンド信号には、インピーダンスのマッチング用に抵抗が直列に入っています。   
※クロック信号だけ、プルアップ抵抗が省略されていますが、パターンはあり、場合により抵抗を実装可能なようですが、必要無いと思います。   

### RX64M (Soft SPI)

|ピン名|LFQFP176|SD ピン|SD 機能|備考|
|---|---|---|---|---|
|PC3(MISO)|83|DAT0(7)|SO|pull-up(22K)|
|P76(MOSI)|85|CMD(2)|SI||
|P77(SPCK)|84|CLK(5)|SCLK|damping-register(22)|
|PC2|86|DAT3(1)|SELECT||
|P82|79|-|Power CTRL|active-low|
|P81|80|-|CardDetect|active-low|

## SD モードと SPI モードの違い

|モード|CLK|CMD|D0|D1|D2|D3|CRC|
|---|---|---|---|---|---|---|---|
|SPI モード|CLK(SCLK)|Din(MOSI)|Dout(MISO)|×|×|CS|不要|
|SD モード|クロック|双方向|D0|D1|D2|D3|必要|

SD モードでの大きな違いは、コマンド制御線 (CMD) と、R/W データバス（D0 ～ D3) が分離しており、CMD は双方向になっています。   
※コマンドのレスポンスを受け取る場合。   
※エラー検出を行う為、CRC 多項式による演算が必要です。   
SPI モードでは、コマンド、データバスは共有しており、データは一方向に流れる為、より簡単な構成で、CRC のエラー検査も省略されます。   

SDHC 以降のカードでは、電源電圧を下げ (1.8V)、より高速な転送速度を実現する為のモードが用意されています。   
※クロックとデータの遅延を整合するような機能もあります。   
※これらは、RX マイコンの SDHI では扱えない為サポートしていません。   
(1.8V のポート電圧をサポートしておらず、クロック速度の上限にも制限がある)   

通常、SD カードの電圧範囲は、2.7V ～ 3.6V です。   

SD モードでは、４ビットバスと１ビットバスを選択可能ですが、カードによっては１ビットバスをサポートしていない場合があるようです。   

## SPI モードの初期化プロセス

[mmc_io.hpp / disk_initialize(BYTE drv)](https://github.com/hirakuni45/RX/blob/master/ff13c/mmc_io.hpp?ts=4) を参照

## SD モードの初期化プロセス

1GB 以下の容量が小さい、カードは、別の初期化プロセスが必要ですが、最近では、そのようなカードは既に入手が難しい事もあり、サポートしていません。   
※1GB のカードでも、古い製造のカードは別の初期化プロセスが必要な場合があり、初期化に失敗します。   

- SD カード電源投入
- 電源が安定するまで待つ（実装では、１秒待っています）
- SDHI の初期化を行い、初期化用クロック速度を設定（400KHz 以下）
- ダミークロックを７４個入れる
- CMD0, 0x00000000 を送信
- 1 ミリ秒待つ
- CMD8, 0x000001AA を送信
- 下位１２ビットに 0x1AA が返る事を確認
- ACMD41, 0x40FF8000 を送信
- レスポンスで、B31 が「１」になるまで繰り返す（１秒間投げ続けても「０」ならエラー）
- レスポンスで、B30が「１」なら、ブロックアクセス（4GB 以上のカード）
- CMD2, 0x00000000 を送信（カード識別コマンド）
- レスポンスで返るカード識別 ID を取得
- CMD3, 0x00000000 を送信（RCA を読み出す）
- レスポンスで返る RCA（B31～B16）を取得
- CMD7, RCA を送信（カード選択）
- CMD16, 512（ブロックサイズを５１２に設定）
- ACMD6, 0x00000002 を送信（バス幅を４ビットに変更）
- SDHI のバス幅を４ビットに変更
- SDHI のクロック速度をブースト

ACMDxx は、CMD55、CMDxx を送る。（SDHI では、ACMD ビットを「１」にする）   

詳細な手順は、[sdhi_io.hpp / disk_initialize(BYTE drv)](https://github.com/hirakuni45/RX/blob/master/RX600/sdhi_io.hpp?ts=4) を参照

## セクター、リード・ライト

FatFs の関数プロトタイプは以下のようなもので、セクター単位（５１２バイト）でデータをやり取りします。   

```
    //-----------------------------------------------------------------//
    /*!
        @brief  リード・セクター
        @param[in]  drv     Physical drive nmuber (0)
        @param[out] buff    Pointer to the data buffer to store read data
        @param[in]  sector  Start sector number (LBA)
        @param[in]  count   Sector count (1..128)
     */
    //-----------------------------------------------------------------//
    DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) noexcept

    //-----------------------------------------------------------------//
    /*!
        @brief  ライト・セクター
        @param[in]  drv     Physical drive nmuber (0)
        @param[in]  buff    Pointer to the data to be written
        @param[in]  sector  Start sector number (LBA)
        @param[in]  count   Sector count (1..128)
     */
    //-----------------------------------------------------------------//
    DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) noexcept
```

初期化の時、ACMD41 のレスポンスで、B30 が「0」の場合は、実アドレスとなる為、「sector」を 512 倍する必要があります。   
※1GB、2GB の SD カード

```
    // Convert LBA to byte address if needed
    if(!(card_type_ & CT_BLOCK)) sector *= 512;
```

シングルセクターと複数セクターでコマンドが異なります。

```
    // read command
    command cmd = count > 1 ? command::CMD18 : command::CMD17;

    // write command
    command cmd = count > 1 ? command::CMD25 : command::CMD24;
```

SDHI では、内臓バッファは５１２バイトで、３２ビット単位に格納される為、格納先が、３２ビット単位では無い場合に工夫する必要があります。

```
    if((reinterpret_cast<uint32_t>(buff) & 0x3) == 0) {
        uint32_t* p = static_cast<uint32_t*>(buff);
        for(uint32_t n = 0; n < (512 / 4); ++n) {
            *p++ = SDHI::SDBUFR();
        }
        buff = static_cast<void*>(p);
    } else {
        uint8_t* p = static_cast<uint8_t*>(buff);
        for(uint32_t n = 0; n < (512 / 4); ++n) {
            uint32_t tmp = SDHI::SDBUFR();
            std::memcpy(p, &tmp, 4);
            p += 4;
        }
        buff = static_cast<void*>(p);
    }
```

又、内臓バッファの並びは、リトルエンディアンを想定したものになっている為、RX マイコンをビッグエンディアンで動かす場合（めずらしい）は、SWAPする必要がありますが、ハードウェアーの機能として用意されています。

```
#ifdef BIG_ENDIAN
    debug_format("Turn SWAP mode for Big Endian\n");
    SDHI::SDSWAP = SDHI::SDSWAP.BWSWP.b(1) | SDHI::SDSWAP.BRSWP.b(1);
#endif

```

## 速度比較

<img src="../docs/MicroSD.jpg" width="60%">

### SPI モード RX24T (RSPI)
```
QIDIAN MLC 32GB (SDHC) Class10
Write Open:  0 [ms]
Write: 250 KBytes/Sec
Write Close: 21 [ms]

Read Open:  1 [ms]
Read: 444 KBytes/Sec
Read Close: 0 [ms]
```

### SPI モード RX64M (ソフト SPI)
```
QIDIAN MLC 32GB (SDHC) Class10
Write Open:  0 [ms]
Write: 150 KBytes/Sec
Write Close: 15 [ms]

Read Open:  2 [ms]
Read: 237 KBytes/Sec
Read Close: 0 [ms]
```

### SD モード RX65N Envision Kit (SDHI)
```
QIDIAN MLC 32GB (SDHC) Class10
WriteOpen:  0 [ms]
Write: 430 KBytes/Sec
WriteClose: 5 [ms]

ReadOpen:  0 [ms]
Read: 1024 KBytes/Sec
ReadClose: 0 [ms]

-----------------------------
Lexar 633x 8GB (SDHC) Class10
WriteOpen:  170 [ms]
Write: 210 KBytes/Sec
WriteClose: 12 [ms]

ReadOpen:  2 [ms]
Read: 1272 KBytes/Sec
ReadClose: 0 [ms]

-------------------------------------
SanDisk Industrial 8GB (SDHC) Class10
WriteOpen:  3 [ms]
Write: 330 KBytes/Sec
WriteClose: 98 [ms]

ReadOpen:  1 [ms]
Read: 1706 KBytes/Sec
ReadClose: 0 [ms]

--------------------------------------
SanDisk Industrial 16GB (SDHC) Class10
WriteOpen:  6 [ms]
Write: 388 KBytes/Sec
WriteClose: 5 [ms]

ReadOpen:  2 [ms]
Read: 1199 KBytes/Sec
ReadClose: 0 [ms]

-----------------------------------------
TOSHIBA 40MB/s Taiwan 32GB (SDHC) Class10
WriteOpen:  1 [ms]
Write: 200 KBytes/Sec
WriteClose: 46 [ms]

Open:  1 [ms]
Read: 1065 KBytes/Sec
ReadClose: 0 [ms]
```

テストは５１２バイト単位である為、連続で行う場合、もっと高速だと思います。   
現状の実装は、ポーリングによるもので、ソフトウェア転送を行っています、割り込みや DMA は利用しておらず、チューニングもほとんどされていません。   

## まとめ

ドライバー、ハードウェア定義は、C++ テンプレートを活用しています。   
以下のように、「SDHI を使った SD モード」と「ソフト SPI を使った SPI モード」を簡単に切り替え出来ます。   

```
    // 定義部

    // カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
//  typedef device::NULL_PORT SDC_POWER;
    typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;

#ifdef SDHI_IF
    // RX65N Envision Kit の SDHI ポートは、候補３になっている
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, device::port_map::option::THIRD> SDC;
    SDC         sdc_;
#else
    // Soft SDC 用　SPI 定義（SPI）
    typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;  // DAT0
    typedef device::PORT<device::PORT2, device::bitpos::B0> MOSI;  // CMD
    typedef device::PORT<device::PORT2, device::bitpos::B1> SPCK;  // CLK

    typedef device::spi_io2<MISO, MOSI, SPCK> SPI;  ///< Soft SPI 定義

    SPI         spi_;

    typedef device::PORT<device::PORT1, device::bitpos::B7> SDC_SELECT;  // DAT3 カード選択信号
    typedef device::PORT<device::PORT2, device::bitpos::B5> SDC_DETECT;  // CD   カード検出

    typedef fatfs::mmc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;   // ハードウェアー定義

    SDC         sdc_(spi_, 35000000);
#endif

    // メイン部

    // 1/60 毎に呼ばれるサービス
    while(1) {
        render_.sync_frame();

...

        sdc_.service();
    }
```

参照：   
RX65N Envision Kit:   
[RTK5_LCD_sample / main.cpp](https://github.com/hirakuni45/RX/tree/master/RTK5_LCD_sample/main.cpp?ts=4)

RX24T, RX64M, RX65N/RX651:   
[SDCARD_sample / main.cpp](https://github.com/hirakuni45/RX/tree/master/SDCARD_sample/main.cpp?ts=4)
