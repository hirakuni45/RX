#pragma once
//=============================================================================//
/*!	@file
	@brief	EtherCAT Slave Controller / EtherCAT スレーブコントローラ @n
			RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  EtherCAT class
		@param[in]	base	ベース・アドレス
		@param[in]	base2	ベース・アドレス 2
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, uint32_t base2, peripheral per>
	struct ethercat_t {

		static constexpr auto PERIPHERAL = per;			///< ペリフェラル型
		static constexpr auto SYNC0 = ICU::SELECTA::SYNC0;	///< Sync0 割り込み
		static constexpr auto SYNC1 = ICU::SELECTA::SYNC1;	///< Sync1 割り込み
		static constexpr auto ESCI  = ICU::GROUPAL1::ESCI;	///< EtherCAT 割り込み
		static constexpr auto SOF   = ICU::SELECTA::SOF;	///< Start-of-Frame 割り込み
		static constexpr auto _EOF  = ICU::SELECTA::_EOF;	///< End-of-Frame 割り込み
		static constexpr auto WDT   = ICU::SELECTA::WDT;	///< Process Data Watchdog 割り込み
		static constexpr auto RESET = ICU::SELECTA::RESET;	///< RESET 割り込み

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC リセット制御レジスタ (ESCRST)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escrst_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ESCRST;
			bit_rw_t<io_, bitpos::B1>  PHYRST;
		};
		static inline escrst_t<base + 0x00> ESCRST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY LINK 極性設定レジスタ (PHYLINK)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct phylink_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  LINKPOL0;
			bit_rw_t<io_, bitpos::B1>  LINKPOL1;
		};
		static inline phylink_t<base + 0x10> PHYLINK;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC 割り込み制御レジスタ (ESCICR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escicr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SYNC0C;
			bit_rw_t<io_, bitpos::B1>  SYNC1C;
			bit_rw_t<io_, bitpos::B2>  ESCIC;
		};
		static inline escicr_t<base + 0x14> ESCICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY アドレスオフセット設定レジスタ (PHYOFF)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct phyoff_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  OFFSET;
		};
		static inline phyoff_t<base + 0x18> PHYOFF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC 動作モード設定レジスタ (ESCMR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escmr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PROMSIZE;
		};
		static inline escmr_t<base + 0x1C> ESCMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  TX シフト設定レジスタ (TXSFTR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct txsftr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TXSFT0;
			bits_rw_t<io_, bitpos::B2, 2>  TXSFT1;
		};
		static inline txsftr_t<base + 0x20> TXSFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイプレジスタ (TYPE)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro8_t<base2 + 0x00> TYPE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リビジョンレジスタ (REVISION)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro8_t<base2 + 0x01> REVISION;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ビルドレジスタ (BUILD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro16_t<base2 + 0x02> BUILD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU 搭載チャネル数レジスタ (FMMUNUM)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro8_t<base2 + 0x04> FMMUNUM;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager 搭載チャネル数レジスタ (SMNUM)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro8_t<base2 + 0x05> SMNUM;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロセスデータ RAM サイズレジスタ (RAMSIZE)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro8_t<base2 + 0x06> RAMSIZE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポートディスクリプタレジスタ (PORTDESC)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct portdesc_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 2>  P0;
			bits_ro_t<in_, bitpos::B2, 2>  P1;
			bits_ro_t<in_, bitpos::B4, 2>  P2;
			bits_ro_t<in_, bitpos::B6, 2>  P3;
		};
		static inline portdesc_t<base2 + 0x07> PORTDESC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC 搭載機能表示レジスタ (FEATURE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct feature_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  FMMU;

			bit_ro_t<in_, bitpos::B2>  DC;
			bit_ro_t<in_, bitpos::B3>  DCWID;

			bit_ro_t<in_, bitpos::B6>  LINKDETMII;
			bit_ro_t<in_, bitpos::B7>  FCS;
			bit_ro_t<in_, bitpos::B8>  DCSYNC;
			bit_ro_t<in_, bitpos::B9>  LRW;
			bit_ro_t<in_, bitpos::B10> RWSUPP;
			bit_ro_t<in_, bitpos::B11> FSCONFIG;
		};
		static inline feature_t<base2 + 0x08> FEATURE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステーションアドレスレジスタ (STATIONADR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x10> STATIONADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステーションエイリアスレジスタ (STATIONALIAS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x12> STATIONALIAS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  レジスタライト許可レジスタ (REGWRENABLE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct regwrenable_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ENABLE;
		};
		static inline regwrenable_t<base2 + 0x20> REGWRENABLE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  レジスタライトプロテクトレジスタ (REGWRPROTECT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct regwrprotect_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PROTECT;
		};
		static inline regwrprotect_t<base2 + 0x21> REGWRPROTECT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC ライトイネーブルレジスタ (ESCWRENABLE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escwrenable_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ENABLE;
		};
		static inline escwrenable_t<base2 + 0x30> ESCWRENABLE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC ライトプロテクションレジスタ (ESCWRPROTECT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escwrprotect_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PROTECT;
		};
		static inline escwrprotect_t<base2 + 0x31> ESCWRPROTECT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ESC リセット ECAT レジスタ (ESCRESETECAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escresetecat_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 2>  RESETECAT;
		};
		static inline escresetecat_t<base2 + 0x40> ESCRESETECAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ESC リセット PDI レジスタ (ESCRESETPDI)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escresetpdi_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 2>  RESETPDI;
		};
		static inline escresetpdi_t<base2 + 0x41> ESCRESETPDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC DL コントロールレジスタ (ESCDLCONTROL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escdlcontrol_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      FWDRULE;
			bit_rw_t <io_, bitpos::B1>      TEMPUSE;

			bits_rw_t<io_, bitpos::B8,  2>  LP0;
			bits_rw_t<io_, bitpos::B10, 2>  LP1;
			bits_rw_t<io_, bitpos::B12, 2>  LP2;
			bits_rw_t<io_, bitpos::B14, 2>  LP3;
			bits_rw_t<io_, bitpos::B16, 3>  RXFIFO;

			bit_rw_t <io_, bitpos::B24>     STAALIAS;
		};
		static inline escdlcontrol_t<base2 + 0x100> ESCDLCONTROL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フィジカルリード / ライトオフセットレジスタ (PHYSICALRWOFST)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x108> PHYSICALRWOFST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC DL ステータスレジスタ (ESCDLSTATUS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escdlstatus_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>    PDIOPE;
			bit_ro_t <in_, bitpos::B1>    PDIWDST;
			bit_ro_t <in_, bitpos::B2>    ENHLINKD;

			bit_ro_t <in_, bitpos::B4>    PHYP0;
			bit_ro_t <in_, bitpos::B5>    PHYP1;
			bit_ro_t <in_, bitpos::B6>    PHYP2;
			bit_ro_t <in_, bitpos::B7>    PHYP3;
			bit_ro_t <in_, bitpos::B8>    LP0;
			bit_ro_t <in_, bitpos::B9>    COMP0;
			bit_ro_t <in_, bitpos::B10>   LP1;
			bit_ro_t <in_, bitpos::B11>   COMP1;
			bit_ro_t <in_, bitpos::B12>   LP2;
			bit_ro_t <in_, bitpos::B13>   COMP2;
			bit_ro_t <in_, bitpos::B14>   LP3;
			bit_ro_t <in_, bitpos::B15>   COMP3;
		};
		static inline escdlstatus_t<base2 + 0x110> ESCDLSTATUS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  AL コントロールレジスタ (ALCONTROL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct alcontrol_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  INSTATE;
			bit_rw_t <io_, bitpos::B4>      ERRINDACK;
			bit_rw_t <io_, bitpos::B5>      DEVICEID;
		};
		static inline alcontrol_t<base2 + 0x120> ALCONTROL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  AL ステータスレジスタ (ALSTATUS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct alstatus_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  ACTSTATE;
			bit_rw_t <io_, bitpos::B4>      ERR;
			bit_rw_t <io_, bitpos::B5>      DEVICEID;
		};
		static inline alstatus_t<base2 + 0x130> ALSTATUS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  AL ステータスコードレジスタ (ALSTATUSCODE)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x134> ALSTATUSCODE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RUN LED オーバライドレジスタ (RUNLEDOVERRIDE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct runledoverride_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  LEDCODE;
			bit_rw_t <io_, bitpos::B4>      OVERRIDEEN;
		};
		static inline runledoverride_t<base2 + 0x138> RUNLEDOVERRIDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ERR LED オーバライドレジスタ (ERRLEDOVERRIDE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct errledoverride_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  LEDCODE;
			bit_rw_t <io_, bitpos::B4>     OVERRIDEEN;
		};
		static inline errledoverride_t<base2 + 0x139> ERRLEDOVERRIDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDI コントロールレジスタ (PDICONTROL)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base2 + 0x140> PDICONTROL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ESC コンフィギュレーションレジスタ (ESCCONFIG)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct escconfig_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>    DEVEMU;
			bit_ro_t <in_, bitpos::B1>    ENLALLP;
			bit_ro_t <in_, bitpos::B2>    DCSYNC;
			bit_ro_t <in_, bitpos::B3>    DCLATCH;
			bit_ro_t <in_, bitpos::B4>    ENLP0;
			bit_ro_t <in_, bitpos::B5>    ENLP1;
			bit_ro_t <in_, bitpos::B6>    ENLP2;
			bit_ro_t <in_, bitpos::B7>    ENLP3;
		};
		static inline escconfig_t<base2 + 0x141> ESCCONFIG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDI コンフィギュレーションレジスタ (PDICONFIG)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pdiconfig_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 5>  ONCHIPBUSCLK;
			bits_ro_t<in_, bitpos::B5, 3>  ONCHIPBUS;
		};
		static inline pdiconfig_t<base2 + 0x150> PDICONFIG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC/LATCH PDI コンフィギュレーションレジスタ (SYNCLATCHCONFIG)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct synclatchconfig_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 2>  SYNC0OUT;
			bit_ro_t <in_, bitpos::B2>     SYNCLAT0;
			bit_ro_t <in_, bitpos::B3>     SYNC0MAP;
			bits_ro_t<in_, bitpos::B4, 2>  SYNC1OUT;
			bit_ro_t <in_, bitpos::B6>     SYNCLAT1;
			bit_ro_t <in_, bitpos::B7>     SYNC1MAP;
		};
		static inline synclatchconfig_t<base2 + 0x151> SYNCLATCHCONFIG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  拡張 PDI コンフィギュレーションレジスタ (EXTPDICONFIG)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct extpdiconfig_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 2>  DATABUSWID;
		};
		static inline extpdiconfig_t<base2 + 0x152> EXTPDICONFIG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ECAT イベントマスクレジスタ (ECATEVENTMASK)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x200> ECATEVENTMASK;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  AL イベントマスクレジスタ (ALEVENTMASK)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x204> ALEVENTMASK;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ECAT イベントリクエストレジスタ (ECATEVENTREQ)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ecateventreq_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>    DCLATCH;

			bit_ro_t<in_, bitpos::B2>    DLSTA;
			bit_ro_t<in_, bitpos::B3>    ALSTA;
			bit_ro_t<in_, bitpos::B4>    SMSTA0;
			bit_ro_t<in_, bitpos::B5>    SMSTA1;
			bit_ro_t<in_, bitpos::B6>    SMSTA2;
			bit_ro_t<in_, bitpos::B7>    SMSTA3;
			bit_ro_t<in_, bitpos::B8>    SMSTA4;
			bit_ro_t<in_, bitpos::B9>    SMSTA5;
			bit_ro_t<in_, bitpos::B10>   SMSTA6;
			bit_ro_t<in_, bitpos::B11>   SMSTA7;
		};
		static inline ecateventreq_t<base2 + 0x210> ECATEVENTREQ;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  AL イベントリクエストレジスタ (ALEVENTREQ)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct aleventreq_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>    ALCTRL;
			bit_ro_t<in_, bitpos::B1>    DCLATCH;
			bit_ro_t<in_, bitpos::B2>    DCSYNC0STA;
			bit_ro_t<in_, bitpos::B3>    DCSYNC1STA;
			bit_ro_t<in_, bitpos::B4>    SYNCACT;

			bit_ro_t<in_, bitpos::B6>    WDPD;

			bit_ro_t<in_, bitpos::B8>    SMINT0;
			bit_ro_t<in_, bitpos::B9>    SMINT1;
			bit_ro_t<in_, bitpos::B10>   SMINT2;
			bit_ro_t<in_, bitpos::B11>   SMINT3;
			bit_ro_t<in_, bitpos::B12>   SMINT4;
			bit_ro_t<in_, bitpos::B13>   SMINT5;
			bit_ro_t<in_, bitpos::B14>   SMINT6;
			bit_ro_t<in_, bitpos::B15>   SMINT7;
		};
		static inline aleventreq_t<base2 + 0x220> ALEVENTREQ;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート n 受信エラーカウントレジスタ (RXERRCOUNTn) (n = 0, 1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct rxerrcount_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  INVFRMCNT;
			bits_rw_t<io_, bitpos::B8, 8>  RXERRCNT;
		};
		static inline rxerrcount_t<base2 + 0x300> RXERRCOUNT0;
		static inline rxerrcount_t<base2 + 0x302> RXERRCOUNT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート n 転送エラーカウントレジスタ (FWDRXERRCOUNTn) (n = 0, 1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base2 + 0x308> FWDRXERRCOUNT0;
		static inline rw8_t<base2 + 0x309> FWDRXERRCOUNT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ECAT プロセッシングユニットエラーカウントレジスタ (EPUERRCOUNT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base2 + 0x30C> EPUERRCOUNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDI エラーカウントレジスタ (PDIERRCOUNT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base2 + 0x30D> PDIERRCOUNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート n ロストリンクカウントレジスタ (LOSTLINKCOUNTn) (n = 0, 1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base2 + 0x310> LOSTLINKCOUNT0;
		static inline rw8_t<base2 + 0x311> LOSTLINKCOUNT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ウォッチドッグディバイダレジスタ (WDDIVIDE)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x400> WDDIVIDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDI ウォッチドッグタイムレジスタ (WDTPDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x410> WDTPDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロセスデータウォッチドッグタイムレジスタ (WDTDATA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x420> WDTDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロセスデータウォッチドッグステータスレジスタ (WDSDATA)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct wdsdata_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>    WDSTAPD;
		};
		static inline wdsdata_t<base2 + 0x440> WDSDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロセスデータウォッチドッグカウンタレジスタ (WDCDATA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base2 + 0x442> WDCDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDI ウォッチドッグカウンタレジスタ (WDCPDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base2 + 0x443> WDCPDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EEPROM コンフィギュレーションレジスタ (EEPCONF)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eepconf_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CTRLPDI;
			bit_rw_t<io_, bitpos::B1>   FORCEECAT;
		};
		static inline eepconf_t<base2 + 0x500> EEPCONF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EEPROM PDI アクセスステートレジスタ (EEPSTATE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eepstate_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   PDIACCESS;
		};
		static inline eepstate_t<base2 + 0x501> EEPSTATE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EEPROM コントロール / ステータスレジスタ (EEPCONTSTAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eepcontstat_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ECATWREN;

			bit_ro_t <io_, bitpos::B6>     READBYTE;
			bit_ro_t <io_, bitpos::B7>     PROMSIZE;
			bits_rw_t<io_, bitpos::B8, 3>  COMMAND;
			bit_ro_t <io_, bitpos::B11>    CKSUMERR;
			bit_ro_t <io_, bitpos::B12>    LOADSTA;
			bit_ro_t <io_, bitpos::B13>    ACKCMDERR;
			bit_ro_t <io_, bitpos::B14>    WRENERR;
			bit_ro_t <io_, bitpos::B15>    BUSY;
		};
		static inline eepcontstat_t<base2 + 0x502> EEPCONTSTAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EEPROM アドレスレジスタ (EEPADR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base2 + 0x504> EEPADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EEPROM データレジスタ (EEPDATA)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct eepdata_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  LODATA;
			bits_ro_t<io_, bitpos::B16, 16>  HIDATA;
		};
		static inline eepdata_t<base2 + 0x508> EEPDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MII マネージメントコントロール / ステータスレジスタ (MIICONTSTAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct miicontstat_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     WREN;
			bit_ro_t <io_, bitpos::B1>     PDICTRL;
			bit_ro_t <io_, bitpos::B2>     MILINK;
			bits_ro_t<io_, bitpos::B3, 5>  PHYOFFSET;
			bits_ro_t<io_, bitpos::B8, 2>  COMMAND;

			bit_ro_t <io_, bitpos::B13>    READERR;
			bit_ro_t <io_, bitpos::B14>    CMDERR;
			bit_ro_t <io_, bitpos::B15>    BUSY;
		};
		static inline miicontstat_t<base2 + 0x510> MIICONTSTAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY アドレスレジスタ (PHYADR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct phyadr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  PHYADDR;
		};
		static inline phyadr_t<base2 + 0x512> PHYADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY レジスタアドレスレジスタ (PHYREGADR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct phyregadr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  PHYREGADDR;
		};
		static inline phyregadr_t<base2 + 0x513> PHYREGADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHY データレジスタ (PHYDATA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x514> PHYDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MII マネージメント ECAT アクセスステートレジスタ (MIIECATACSSTAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct miiecatacsstat_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ACSMII;
		};
		static inline miiecatacsstat_t<base2 + 0x516> MIIECATACSSTAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MII マネージメント PDI アクセスステートレジスタ (MIIPDIACSSTAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct miipdiacsstat_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ACSMII;
			bit_rw_t<io_, bitpos::B1>  FORPDI;
		};
		static inline miipdiacsstat_t<base2 + 0x517> MIIPDIACSSTAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU 論理スタートアドレスレジスタ m (FMMUmLSTARTADR) (m = 0 ～ 7) @n
												　   (FMMULSTARTADR[m]) (m = 0 ～ 7) 
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fmmulstartadr_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 0x10; } }

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline fmmulstartadr_t<base2 + 0x600> FMMULSTARTADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU 長レジスタ m (FMMUmLEN) (m = 0 ～ 7) @n
									 (FMMULEN[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fmmulstartbit_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 0x10; } }

			bits_rw_t<io_, bitpos::B0, 3>  LSTABIT;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline fmmulstartbit_t<base2 + 0x606> FMMULEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU 論理ストップビットレジスタ m (FMMUmLSTOPBIT) (m = 0 ～ 7) @n
												   (FMMULSTOPBIT[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fmmulstopbit_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 0x10; } }

			bits_rw_t<io_, bitpos::B0, 3>  LSTPBIT;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline fmmulstopbit_t<base2 + 0x607> FMMULSTOPBIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU 物理スタートアドレスレジスタ m (FMMUmPSTARTADR) (m = 0 ～ 7) @n
													 (FMMUPSTARTADR[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fmmupstartadr_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 0x10; } }

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline fmmupstartadr_t<base2 + 0x608> FMMUPSTARTADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU 物理スタートビットレジスタ m (FMMUmPSTARTBIT) (m = 0 ～ 7) @n
												   (FMMUPSTARTBIT[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fmmupstartbit_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 0x10; } }

			bits_rw_t<io_, bitpos::B0, 3>  PHYSTABIT;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline fmmupstartbit_t<base2 + 0x60A> FMMUPSTARTBIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU タイプレジスタ m (FMMUmTYPE) (m = 0 ～ 7) @n
										(FMMUTYPE[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fmmutype_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 0x10; } }

			bit_rw_t<io_, bitpos::B0>  READ;
			bit_rw_t<io_, bitpos::B1>  WRITE;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline fmmutype_t<base2 + 0x60B> FMMUTYPE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FMMU アクティベイトレジスタ m (FMMUmACT) (m = 0 ～ 7) @n
												(FMMUACT[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct fmmuact_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 0x10; } }

			bit_rw_t<io_, bitpos::B0>  ACTIVATE;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline fmmuact_t<base2 + 0x60C> FMMUACT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager 物理スタートアドレスレジスタ m (SMmPSTARTADR) (m = 0 ～ 7) @n
															(SMPSTARTADR[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct smpstartadr_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 8; } }

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline smpstartadr_t<base2 + 0x800> SMPSTARTADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager 長レジスタ m (SMmLEN) (m = 0 ～ 7) @n
											(SMLEN[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct smlen_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 8; } }

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline smlen_t<base2 + 0x802> SMLEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager コントロールレジスタ m (SMmCONTROL) (m = 0 ～ 7) @n
													 (SMCONTROL[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct smcontrol_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 8; } }

			bits_rw_t<io_, bitpos::B0, 2>  OPEMODE;
			bits_rw_t<io_, bitpos::B2, 2>  DIR;
			bit_rw_t <io_, bitpos::B4>     IRQECAT;
			bit_rw_t <io_, bitpos::B5>     IRQPDI;
			bit_rw_t <io_, bitpos::B6>     WDTRGEN;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline smcontrol_t<base2 + 0x804> SMCONTROL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager ステータスレジスタ m (SMmSTATUS) (m = 0 ～ 7) @n
												   (SMSTATUS[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct smstatus_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator ();

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 8; } }

			bit_ro_t <io_, bitpos::B0>     INTWR;
			bit_ro_t <io_, bitpos::B1>     INTRD;

			bit_ro_t <io_, bitpos::B3>     MAILBOX;
			bits_ro_t<io_, bitpos::B4, 2>  BUFFERED;
			bit_ro_t <io_, bitpos::B6>     RDBUF;
			bit_ro_t <io_, bitpos::B7>     WRBUF;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline smstatus_t<base2 + 0x805> SMSTATUS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager アクティベイトレジスタ m (SMmACT) (m = 0 ～ 7) @n
													   (SMACT[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct smact_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 8; } }

			bit_rw_t <io_, bitpos::B0>     SMEN;
			bit_rw_t <io_, bitpos::B1>     REPEATREQ;

			bit_rw_t <io_, bitpos::B6>     LATCHECAT;
			bit_rw_t <io_, bitpos::B7>     LATCHPDI;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline smact_t<base2 + 0x806> SMACT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager PDI コントロールレジスタ m (SMmPDICONT) (m = 0 ～ 7) @n
														 (SMPDICONT[m]) (m = 0 ～ 7)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct smpdicont_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 8) { io_::index = j * 8; } }

			bit_rw_t <io_, bitpos::B0>     DEACTIVE;
			bit_rw_t <io_, bitpos::B1>     REPEATACK;

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline smpdicont_t<base2 + 0x807> SMPDICONT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DC レシーブタイム設定レジスタ @n
					ポート 0 受信時刻レジスタ (DCRCVTIMEPORT0)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base2 + 0x900> DCRCVTIMEPORT0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DC レシーブタイム設定レジスタ @n
					ポート 1 受信時刻レジスタ (DCRCVTIMEPORT1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base2 + 0x904> DCRCVTIMEPORT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					システムタイムレジスタ (DCSYSTIME)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw64_t<base2 + 0x910> DCSYSTIME;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					レシーブタイム ECAT プロセッシングユニットレジスタ (DCRCVTIMEEPU)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw64_t<base2 + 0x918> DCRCVTIMEEPU;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					システムタイムオフセットレジスタ (DCSYSTIMEOFFSET)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw64_t<base2 + 0x920> DCSYSTIMEOFFSET;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					システムタイムディレイレジスタ (DCSYSTIMEDELAY)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base2 + 0x928> DCSYSTIMEDELAY;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					システムタイムディフレジスタ (DCSYSTIMEDIFF)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcsystimediff_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 31>  DIFF;
			bit_rw_t <io_, bitpos::B31>     LOCALCOPY;
		};
		static inline dcsystimediff_t<base2 + 0x92C> DCSYSTIMEDIFF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					スピードカウンタスタートレジスタ (DCSCSTART)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcscstart_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 15>  SCSTART;
		};
		static inline dcscstart_t<base2 + 0x930> DCSCSTART;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					スピードカウンタディフレジスタ (DCSCDIFF)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x932> DCSCDIFF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					システムタイムディフフィルタ深さレジスタ (DCSYSTIMEFILDP)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcsystimefildp_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  FILDP;
		};
		static inline dcsystimefildp_t<base2 + 0x934> DCSYSTIMEFILDP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムループコントロールユニット設定レジスタ @n
					スピードカウンタフィルタ深さレジスタ (DCSCFILDP)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcscfildp_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  FILDP;
		};
		static inline dcscfildp_t<base2 + 0x935> DCSCFILDP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サイクリックユニットコントロール設定レジスタ @n
					サイクリックユニットコントロールレジスタ (DCCYCCONT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dccyccont_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SYNCOUT;

			bit_rw_t<io_, bitpos::B4>  LATCH0;
			bit_rw_t<io_, bitpos::B5>  LATCH1;
		};
		static inline dccyccont_t<base2 + 0x980> DCCYCCONT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SYNC 出力ユニット設定レジスタ @n
					アクティベーションレジスタ (DCACT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcact_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SYNCACT;
			bit_rw_t<io_, bitpos::B1>  SYNC0;
			bit_rw_t<io_, bitpos::B2>  SYNC1;
			bit_rw_t<io_, bitpos::B3>  AUTOACT;
			bit_rw_t<io_, bitpos::B4>  EXTSTARTTIME;
			bit_rw_t<io_, bitpos::B5>  STARTTIME;
			bit_rw_t<io_, bitpos::B6>  NEARFUTURE;
			bit_rw_t<io_, bitpos::B7>  DBGPULSE;
		};
		static inline dcact_t<base2 + 0x981> DCACT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					SYNC 信号パルス長レジスタ (DCPULSELEN)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base2 + 0x982> DCPULSELEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SYNC 出力ユニット設定レジスタ @n
					アクティベーションステータスレジスタ (DCACTSTAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcactstat_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  SYNC0ACT;
			bit_ro_t<in_, bitpos::B1>  SYNC1ACT;
			bit_ro_t<in_, bitpos::B2>  STARTTIME;
		};
		static inline dcactstat_t<base2 + 0x984> DCACTSTAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SYNC 出力ユニット設定レジスタ @n
					SYNC0 ステータスレジスタ (DCSYNC0STAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcsync0stat_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  SYNC0STA;
		};
		static inline dcsync0stat_t<base2 + 0x98E> DCSYNC0STAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SYNC 出力ユニット設定レジスタ @n
					SYNC1 ステータスレジスタ (DCSYNC1STAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dcsync1stat_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  SYNC0STA;
		};
		static inline dcsync1stat_t<base2 + 0x98F> DCSYNC1STAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					スタートタイムサイクリックオペレーション @n
					/ ネクスト SYNC0 パルスレジスタ (DCCYCSTARTTIME)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw64_t<base2 + 0x990> DCCYCSTARTTIME;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					ネクスト SYNC1 パルスレジスタ (DCNEXTSYNC1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw64_t<base2 + 0x998> DCNEXTSYNC1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					SYNC0 サイクルタイムレジスタ (DCSYNC0CYCTIME)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base2 + 0x9A0> DCSYNC0CYCTIME;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					SYNC1 サイクルタイムレジスタ (DCSYNC1CYCTIME)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base2 + 0x9A4> DCSYNC1CYCTIME;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Latch 入力ユニット設定レジスタ @n
					ラッチ 0/1 コントロールレジスタ (DCLATCH0CONT / DCLATCH1CONT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dclatch0cont_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POSEDGE;
			bit_rw_t<io_, bitpos::B1>  NEGEDGE;
		};
		static inline dclatch0cont_t<base2 + 0x9A8> DCLATCH0CONT;
		static inline dclatch0cont_t<base2 + 0x9A9> DCLATCH1CONT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Latch 入力ユニット設定レジスタ @n
					ラッチ 0/1 ステータスレジスタ (DCLATCH0STAT / DCLATCH1STAT)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dclatch0stat_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  EVENTPOS;
			bit_ro_t<in_, bitpos::B1>  EVENTNEG;
			bit_ro_t<in_, bitpos::B2>  PINSTATE;
		};
		static inline dclatch0stat_t<base2 + 0x9AE> DCLATCH0STAT;
		static inline dclatch0stat_t<base2 + 0x9AF> DCLATCH1STAT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					ラッチ 0 タイムポジティブエッジレジスタ (DCLATCH0TIMEPOS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro64_t<base2 + 0x9B0> DCLATCH0TIMEPOS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					ラッチ 0 タイムネガティブエッジレジスタ (DCLATCH0TIMENEG)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro64_t<base2 + 0x9B8> DCLATCH0TIMENEG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					ラッチ 1 タイムポジティブエッジレジスタ (DCLATCH1TIMEPOS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro64_t<base2 + 0x9C0> DCLATCH1TIMEPOS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SYNC 出力ユニット設定レジスタ @n
					ラッチ 1 タイムネガティブエッジレジスタ (DCLATCH1TIMENEG)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro64_t<base2 + 0x9C8> DCLATCH1TIMENEG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager イベントタイム設定レジスタ @n
					EtherCAT バッファチェンジイベントタイムレジスタ (DCECATCHGTIME)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro32_t<base2 + 0x9F0> DCECATCHGTIME;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager イベントタイム設定レジスタ @n
					PDI バッファスタートイベントタイムレジスタ (DCPDISTARTTIME)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro32_t<base2 + 0x9F8> DCPDISTARTTIME;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SyncManager イベントタイム設定レジスタ @n
					PDI バッファチェンジイベントタイムレジスタ (DCPDICHGTIME)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro32_t<base2 + 0x9FC> DCPDICHGTIME;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロダクト ID レジスタ (PRODUCTID)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro64_t<base2 + 0xE00> PRODUCTID;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベンダ ID レジスタ (VENDORID)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro64_t<base2 + 0xE08> VENDORID;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ユーザ RAM (USERRAM) @n
					0x0008'8F80 - 0x0008'8FFF (128 bytes)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		// under constructions...


	};
	typedef ethercat_t<0x000E'3600, 0x000E'8000, peripheral::ESC> ESC;
}
