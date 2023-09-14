#pragma once
//=========================================================================//
/*!	@file
	@brief	ポート・マッピング・オーダー型 @n
            ポートの機能設定において、どのピンを利用するかを、選択する「型」
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・オーダー型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_order {
    public:
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

			FIRST_I2C,		///< SCI ポートを簡易 I2C として使う場合、第１候補
			SECOND_I2C,		///< SCI ポートを簡易 I2C として使う場合、第２候補
			THIRD_I2C,		///< SCI ポートを簡易 I2C として使う場合、第３候補
			FOURTH_I2C,		///< SCI ポートを簡易 I2C として使う場合、第４候補

			FIRST_SPI,		///< SCI ポートを簡易 SPI として使う場合、第１候補
			SECOND_SPI,		///< SCI ポートを簡易 SPI として使う場合、第２候補
			THIRD_SPI,		///< SCI ポートを簡易 SPI として使う場合、第３候補
			FOURTH_SPI,		///< SCI ポートを簡易 SPI として使う場合、第４候補

			FIRST_MII,		///< ETHERC MII 接続、第１候補
			SECOND_MII,		///< ETHERC MII 接続、第２候補

			FIRST_RMII,		///< ETHERC RMII 接続、第１候補
			SECOND_RMII,	///< ETHERC RMII 接続、第２候補

			LOCAL0,			///< 独自の特殊な設定０
			LOCAL1,			///< 独自の特殊な設定１
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SCI ポート・マッピング・グループ @n
					CTS/RTS はどちらか片方しか利用出来ない
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct sci_port_t {
			ORDER		cts_;	///< CTSx 端子の選択権
			ORDER		rts_;	///< RTSx 端子の選択権
			ORDER		rxd_;	///< RXDx 端子の選択権
			ORDER		sck_;	///< SCKx 端子の選択権
			ORDER		txd_;	///< TXDx 端子の選択権
			constexpr sci_port_t(ORDER rxd = ORDER::BYPASS, ORDER txd = ORDER::BYPASS) noexcept :
				cts_(ORDER::BYPASS), rts_(ORDER::BYPASS),
				rxd_(rxd),  sck_(ORDER::BYPASS),  txd_(txd)
			{ }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー・チャネル型（MTUx, TPUx, GPTx, GPTWx）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,		///< MTIOCxA(MTUx), TIOCAx(TPUx), GPTWx A (GTIOCxA)
			B,		///< MTIOCxB(MTUx), TIOCBx(TPUx), GPTWx B (GTIOCxB)
			C,		///< MTIOCxC(MTUx), TIOCCx(TPUx)
			D,		///< MTIOCxD(MTUx), TIOCDx(TPUx)
			U,		///< MTICyU(MTUx)
			V,		///< MTICyV(MTUx)
			W,		///< MTICyW(MTUx)
			CLK_A,	///< MTCLKA(MTUx), TCLKA(TPUx)
			CLK_B,	///< MTCLKB(MTUx), TCLKB(TPUx)
			CLK_C,	///< MTCLKC(MTUx), TCLKC(TPUx)
			CLK_D,	///< MTCLKD(MTUx), TCLKD(TPUx)
			CLK_E,	///< MTCLKE (MTU2, TPU 系)
			CLK_F,	///< MTCLKF (MTU2, TPU 系)
			CLK_G,	///< MTCLKG (MTU2, TPU 系)
			CLK_H,	///< MTCLKH (MTU2, TPU 系)
			NONE,	///< 無効なチャネル
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
			REF50CK,		///< REF50CK input
			CRS_DV,			///< CRS_DV input
			TXD0,			///< TXD0 output
			TXD1,			///< TXD1 output
			RXD0,			///< RXD0 input
			RXD1,			///< RXD1 input
			TXD_EN,			///< TXD_EN output
			RX_ER,			///< RX_ER input
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ETHER MII 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ETHER_MII : uint8_t {
			CRS,			///< REF50CK input
			RX_DV,			///< CRS_DV input
			EX_OUT,			///< EX_OUT output
			LINKSTA,		///< LINKSTA input
			ETXD0,			///< ETXD0 output
			ETXD1,			///< ETXD1 output
			ETXD2,			///< ETXD2 output
			ETXD3,			///< ETXD3 output
			ERXD0,			///< ERXD0 input
			ERXD1,			///< ERXD1 input
			ERXD2,			///< ERXD2 input
			ERXD3,			///< ERXD3 input
			TX_EN,			///< TX_EN output
			TX_ER,			///< TX_ER input
			RX_ER,			///< RX_ER input
			TX_CLK,			///< TX_CLK input
			RX_CLK,			///< RX_CLK input
			COL,			///< COL input
			WOL,			///< WOL output
			MDC,			///< MDC output
			MDIO,			///< MDIO input/output
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

			ether_rmii_t() noexcept :
				ref50ck_(ORDER::BYPASS),
				crs_dv_(ORDER::BYPASS),
				txd0_(ORDER::BYPASS),
				txd1_(ORDER::BYPASS),
				rxd0_(ORDER::BYPASS),
				rxd1_(ORDER::BYPASS),
				txd_en_(ORDER::BYPASS),
				rx_er_(ORDER::BYPASS),
				mdc_(ORDER::BYPASS),
				mdio_(ORDER::BYPASS)
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

			ether_mii_t() noexcept :
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
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート・マッピング・ルネサス型 @n
					ルネサス社が提供するボードに対する型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class RENESAS : uint8_t {
			RX72N_ENVISION_KIT,			///< RX72N Envision Kit に対する設定
		};
    };
}
