#pragma once
//=====================================================================//
/*!	@file
	@brief	ポート・マッピング・オーダー型 @n
            ポートの機能設定において、どのピンを利用するかを、選択する「型」
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
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

			FIRST_SPI,		///< SCI ポートを簡易 SPI として使う場合、第１候補
			SECOND_SPI,		///< SCI ポートを簡易 SPI として使う場合、第２候補
			THIRD_SPI,		///< SCI ポートを簡易 SPI として使う場合、第３候補

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
			@brief  ポート・マッピング・ルネサス型 @n
					ルネサス社が提供するボードに対する型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class RENESAS : uint8_t {
			RX72N_ENVISION_KIT,			///< RX72N Envision Kit に対する設定
		};
    };
}