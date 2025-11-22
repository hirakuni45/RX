#pragma once
//=========================================================================//
/*!	@file
	@brief	ポート・マッピング・オーダー型 @n
            ポート指定において、どのピンを利用するかを、選択する「型」
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>
#include <functional>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・オーダー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct port_map_order {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GR-KAEDE (RX64M) 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class RX64M_GR_KAEDE {
			_
		};

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RX65N Envision Kit 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class RX65N_ENVISION_KIT {
			_
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RX72N Envision Kit 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class RX72N_ENVISION_KIT {
			_
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート・マッピング・オーダー型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ORDER : uint8_t {
			BYPASS,			///< ポートマップの設定をバイパスする場合

			FIRST,			///< 第１候補
			SECOND,			///< 第２候補
			THIRD,			///< 第３候補
			FOURTH,			///< 第４候補
			FIFTH,			///< 第５候補
			SIXTH,			///< 第６候補
			SEVENTH,		///< 第７候補
			EIGHTH,			///< 第８候補
			NINTH,			///< 第９候補
			TENTH,			///< 第１０候補
			ELEVENTH,		///< 第１１候補
			TWELVETH,		///< 第１２候補

			USER,			///< ユーザー設定

			LOCAL0,			///< 独自の特殊な設定０
			LOCAL1,			///< 独自の特殊な設定１
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート・マッピング・オプショナル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OPTIONAL : uint8_t {
			NONE,		///< 無し
			SCI_I2C,	///< SCI 簡易 I2C 通信
			SCI_SPI,	///< SCI 簡易 SPI 通信
			RSCI_DE,	///< RSCI DE 信号制御（RS-485）
			RSPI_SSL0,	///< RSPI SSL0 制御
			RSPI_SSL1,	///< RSPI SSL1 制御
			RSPI_SSL2,	///< RSPI SSL2 制御
			RSPI_SSL3,	///< RSPI SSL3 制御
			CMTW_TOC0,	///< CMTW TOC0/TOC2
			CMTW_TOC1,	///< CMTW TOC1/TOC3
			CMTW_TIC0,	///< CMTW TIC0/TIC2
			CMTW_TIC1,	///< CMTW TIC1/TIC3
			ETH_RMII,	///< EtherNET/RMII
			ETH_MII,	///< EtherNET/MII
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class RSPI : uint8_t {
			NONE,	///< 無効なチャネル
			SSL0,		///< SSL0 制御
			SSL1,		///< SSL1 制御
			SSL2,		///< SSL2 制御
			SSL3,		///< SSL3 制御
		};


		/// ポート・マッピング・ユーザー設定関数型
		typedef std::function<bool (peripheral per, bool ena)> USER_FUNC_TYPE;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル型（MTUx, TPUx, GPTx, GPTWx）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			NONE,		///< 無効なチャネル
			A,			///< MTIOCxA (MTUx), TIOCAx (TPUx), GTIOCxA (GPTW)
			B,			///< MTIOCxB (MTUx), TIOCBx (TPUx), GTIOCxB (GPTW)
			C,			///< MTIOCxC (MTUx), TIOCCx (TPUx)
			D,			///< MTIOCxD (MTUx), TIOCDx (TPUx)
			U,			///< MTICyU (MTUx), GTIU (GPTWx)
			V,			///< MTICyV (MTUx), GTIV (GPTWx)
			W,			///< MTICyW (MTUx), GTIW (GPTWx)
			CLKA,		///< MTCLKA (MTUx), TCLKA(TPUx)
			CLKB,		///< MTCLKB (MTUx), TCLKB(TPUx)
			CLKC,		///< MTCLKC (MTUx), TCLKC(TPUx)
			CLKD,		///< MTCLKD (MTUx), TCLKD(TPUx)
			CLKE,		///< MTCLKE (MTU2, TPU 系)
			CLKF,		///< MTCLKF (MTU2, TPU 系)
			CLKG,		///< MTCLKG (MTU2, TPU 系)
			CLKH,		///< MTCLKH (MTU2, TPU 系)
			ADSM0,		///< ADSM0 (MTU3d)
			ADSM1,		///< ADSM1 (MTU3d)
			TRG,		///< GTETRG (GPTx)
			TRG0,		///< GTETRG0 (GPTx)
			TRG1,		///< GTETRG1 (GPTx)
			TRGA,		///< GTETRGA (GPTWx)
			TRGB,		///< GTETRGB (GPTWx)
			TRGC,		///< GTETRGC (GPTWx)
			TRGD,		///< GTETRGD (GPTWx)
			DSM0,		///< GTADSM0 (GPTWx)
			DSM1,		///< GTADSM1 (GPTWx)
			PPO0,		///< GTCPPO0 (GPTWx)
			PPO4,		///< GTCPPO4 (GPTWx)
			ULO,		///< GTOULO (GPTW)
			UUP,		///< GTOUUP (GPTW)
			VLO,		///< GTOVLO (GPTW)
			VUP,		///< GTOVUP (GPTW)
			WLO,		///< GTOWLO (GPTW)
			WUP,		///< GTOWUP (GPTW)
			TMO,		///< TMOx  (TMR)
			TMCI,		///< TMCIx (TMR)
			TMRI,		///< TMRIx (TMR)
		};

#if 0
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RSPI ポート・チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class RSPI_PORT : uint8_t {
			CLK,		///< SPCK
			MOSI,		///< MOSI
			MISO,		///< MISO
			SSL0,		///< SSL0
			SSL1,		///< SSL1
			SSL2,		///< SSL2
			SSL3,		///< SSL3
		};
#endif

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ポート・チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class QSPI_PORT : uint8_t {
			CLK,		///< QSPCLK
			SSL,		///< QSSL
			IO0,		///< QMO/QIO0
			IO1,		///< GMI/QIO1
			IO2,		///< QIO2
			IO3,		///< QIO3
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB ポート型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class USB_PORT : uint8_t {
			VBUS,		///< VBUS input
			EXICEN,		///< EXICEN output
			VBUSEN,		///< VBUSEN output
			OVRCURA,	///< OVRCURA input
			OVRCURB,	///< OVRCURB input
			ID,			///< ID input
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHER RMII 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ETHER_RMII : uint8_t {
			REF50CK,	///< REF50CK input
			CRS_DV,		///< CRS_DV input
			TXD0,		///< TXD0 output
			TXD1,		///< TXD1 output
			RXD0,		///< RXD0 input
			RXD1,		///< RXD1 input
			TXD_EN,		///< TXD_EN output
			RX_ER,		///< RX_ER input
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHER MII 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ETHER_MII : uint8_t {
			CRS,		///< REF50CK input
			RX_DV,		///< CRS_DV input
			EX_OUT,		///< EX_OUT output
			LINKSTA,	///< LINKSTA input
			ETXD0,		///< ETXD0 output
			ETXD1,		///< ETXD1 output
			ETXD2,		///< ETXD2 output
			ETXD3,		///< ETXD3 output
			ERXD0,		///< ERXD0 input
			ERXD1,		///< ERXD1 input
			ERXD2,		///< ERXD2 input
			ERXD3,		///< ERXD3 input
			TX_EN,		///< TX_EN output
			TX_ER,		///< TX_ER input
			RX_ER,		///< RX_ER input
			TX_CLK,		///< TX_CLK input
			RX_CLK,		///< RX_CLK input
			COL,		///< COL input
			WOL,		///< WOL output
			MDC,		///< MDC output
			MDIO,		///< MDIO input/output
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDHI ステート型 @n
					SDHI ポートの状態に応じたグループ・マッピング
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SDHI_STATE : uint8_t {
			START,		///< 開始時（カード挿入を待っている状態）
 			INSERT,		///< カード挿入時（カードが挿入された時）
			BUS,		///< カードのバスを有効にする
			EJECT,		///< カード排出時（カードが排出された時）
			DESTROY,	///< カード廃止
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SCI ポート・マッピング・グループ @n
					CTS/RTS はどちらか片方しか利用出来ない
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct sci_port_t {
			ORDER	cts_;	///< CTSx 端子の選択権
			ORDER	rts_;	///< RTSx 端子の選択権
			ORDER	sck_;	///< SCKx 端子の選択権
			ORDER	rxd_;	///< RXDx 端子の選択権
			ORDER	txd_;	///< TXDx 端子の選択権
			constexpr sci_port_t(ORDER rxd = ORDER::BYPASS, ORDER txd = ORDER::BYPASS) noexcept :
				cts_(ORDER::BYPASS), rts_(ORDER::BYPASS),
				sck_(ORDER::BYPASS),
				rxd_(rxd), txd_(txd)
			{ }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ポート・マッピング・グループ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct qspi_port_t {
			ORDER	clk;
			ORDER	ssl;
			ORDER	io0;
			ORDER	io1;
			ORDER	io2;
			ORDER	io3;

			constexpr qspi_port_t(ORDER odr = ORDER::BYPASS) noexcept :
				clk(odr),
				ssl(odr),
				io0(odr),
				io1(odr),
				io2(odr),
				io3(odr)
			{ }

			constexpr qspi_port_t(RX65N_ENVISION_KIT _) noexcept :
				clk(ORDER::SECOND),	///< PD5
				ssl(ORDER::SECOND),	///< PD4
				io0(ORDER::SECOND),	///< PD6
				io1(ORDER::SECOND),	///< PD7
				io2(ORDER::SECOND),	///< PD2
				io3(ORDER::SECOND)	///< PD3
			{ }

			constexpr qspi_port_t(RX72N_ENVISION_KIT _) noexcept :
				clk(ORDER::SECOND),	///< PD5
				ssl(ORDER::SECOND),	///< PD4
				io0(ORDER::SECOND),	///< PD6
				io1(ORDER::SECOND),	///< PD7
				io2(ORDER::THIRD),	///< PD2
				io3(ORDER::THIRD)	///< PD3
			{ }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHER RMII ポート・マッピング・グループ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct ether_rmii_t {
			ORDER	ref50ck_;
			ORDER	crs_dv_;
			ORDER	txd0_;
			ORDER	txd1_;
			ORDER	rxd0_;
			ORDER	rxd1_;
			ORDER	txd_en_;
			ORDER	rx_er_;
			ORDER	mdc_;
			ORDER	mdio_;

			constexpr ether_rmii_t(ORDER odr = ORDER::BYPASS) noexcept :
				ref50ck_(odr),
				crs_dv_(odr),
				txd0_(odr),
				txd1_(odr),
				rxd0_(odr),
				rxd1_(odr),
				txd_en_(odr),
				rx_er_(odr),
				mdc_(odr),
				mdio_(odr)
			{ }

			constexpr ether_rmii_t(RX65N_ENVISION_KIT t) noexcept :
				ref50ck_(ORDER::FIRST),
				crs_dv_(ORDER::FIRST),
				txd0_(ORDER::FIRST),
				txd1_(ORDER::FIRST),
				rxd0_(ORDER::FIRST),
				rxd1_(ORDER::FIRST),
				txd_en_(ORDER::FIRST),
				rx_er_(ORDER::FIRST),
				mdc_(ORDER::FIRST),
				mdio_(ORDER::FIRST)
			{ }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHER MII ポート・マッピング・グループ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct ether_mii_t {
			ORDER	crs_;
			ORDER	rx_dv_;
			ORDER	exout_;
			ORDER	linksta_;
			ORDER	etxd0_;
			ORDER	etxd1_;
			ORDER	etxd2_;
			ORDER	etxd3_;
			ORDER	erxd0_;
			ORDER	erxd1_;
			ORDER	erxd2_;
			ORDER	erxd3_;
			ORDER	tx_en_;
			ORDER	tx_er_;
			ORDER	rx_er_;
			ORDER	tx_clk_;
			ORDER	rx_clk_;
			ORDER	col_;
			ORDER	wol_;
			ORDER	mdc_;
			ORDER	mdio_;

			constexpr ether_mii_t() noexcept :
				crs_(ORDER::BYPASS),
				rx_dv_(ORDER::BYPASS),
				exout_(ORDER::BYPASS),
				linksta_(ORDER::BYPASS),
				etxd0_(ORDER::BYPASS),
				etxd1_(ORDER::BYPASS),
				etxd2_(ORDER::BYPASS),
				etxd3_(ORDER::BYPASS),
				erxd0_(ORDER::BYPASS),
				erxd1_(ORDER::BYPASS),
				erxd2_(ORDER::BYPASS),
				erxd3_(ORDER::BYPASS),
				tx_en_(ORDER::BYPASS),
				tx_er_(ORDER::BYPASS),
				rx_er_(ORDER::BYPASS),
				tx_clk_(ORDER::BYPASS),
				rx_clk_(ORDER::BYPASS),
				col_(ORDER::BYPASS),
				wol_(ORDER::BYPASS),
				mdc_(ORDER::BYPASS),
				mdio_(ORDER::BYPASS)
			{ }

			constexpr ether_mii_t(RX72N_ENVISION_KIT t) noexcept :
				crs_(ORDER::FIRST),
				rx_dv_(ORDER::FIRST),
				exout_(ORDER::BYPASS),
				linksta_(ORDER::BYPASS),
				etxd0_(ORDER::FIRST),
				etxd1_(ORDER::FIRST),
				etxd2_(ORDER::FIRST),
				etxd3_(ORDER::FIRST),
				erxd0_(ORDER::FIRST),
				erxd1_(ORDER::FIRST),
				erxd2_(ORDER::FIRST),
				erxd3_(ORDER::FIRST),
				tx_en_(ORDER::FIRST),
				tx_er_(ORDER::FIRST),
				rx_er_(ORDER::FIRST),
				tx_clk_(ORDER::FIRST),
				rx_clk_(ORDER::FIRST),
				col_(ORDER::FIRST),
				wol_(ORDER::BYPASS),
				mdc_(ORDER::FIRST),
				mdio_(ORDER::FIRST)
			{ }
		};
    };
}
