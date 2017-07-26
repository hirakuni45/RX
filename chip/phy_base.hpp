#pragma once
//=====================================================================//
/*!	@file
	@brief	PHY（イーサーネット物理層デバイス） ベース・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/format.hpp"

// #define PHY_DEBUG

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PHY リンク・ステート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class phy_link_state : uint16_t {
		NO_LINK = 0,	///< リンク無し
		LINK_10H,		///< 10MBPS / Half
		LINK_10F,		///< 10MBPS / Full
		LINK_100H,		///< 100MBPS / Half
		LINK_100F,		///< 100MBPS / Full
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PHY オプショナル・デバイス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class phy_option {
		BASE,				///< 一般、標準仕様（Ex: LAN8720）
		TI_DP83822,			///< TI/DP83822
		MICREL_KSZ8041NL,	///< MICREL/KSZ8041NL
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PHY ベース・テンプレート・クラス
		@param[in]	ETHERC	インサーネット・コントローラー・クラス
		@param[in]	DEV_ADR	PHY デバイス・アドレス
		@param[in]	DEV_OPT	オプションデバイス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHERC, uint16_t DEV_ADR = 0, phy_option DEV_OPT = phy_option::BASE>
	class phy_base {

#ifndef PHY_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		static const uint16_t REG_CONTROL          = 0;
		static const uint16_t REG_STATUS           = 1;
		static const uint16_t REG_IDENTIFIER1      = 2;
		static const uint16_t REG_IDENTIFIER2      = 3;
		static const uint16_t REG_AN_ADVERTISEMENT = 4;
		static const uint16_t REG_AN_LINK_PARTNER  = 5;
		static const uint16_t REG_AN_EXPANSION     = 6;

		static const uint16_t MII_ST     = 1;
		static const uint16_t MII_READ   = 2;
		static const uint16_t MII_WRITE  = 1;

		static const int MII_WAIT = 2;

		// Basic Mode Control Register Bit Definitions
		static const uint16_t CONTROL_RESET        = (1 << 15);
		static const uint16_t CONTROL_LOOPBACK     = (1 << 14);
		static const uint16_t CONTROL_100_MBPS     = (1 << 13);
		static const uint16_t CONTROL_AN_ENABLE    = (1 << 12);
		static const uint16_t CONTROL_POWER_DOWN   = (1 << 11);
		static const uint16_t CONTROL_ISOLATE      = (1 << 10);
		static const uint16_t CONTROL_AN_RESTART   = (1 << 9);
		static const uint16_t CONTROL_FULL_DUPLEX  = (1 << 8);
		static const uint16_t CONTROL_COLLISION    = (1 << 7);

		// Basic Mode Status Register Bit Definitions
		static const uint16_t STATUS_100_T4        = (1 << 15);
		static const uint16_t STATUS_100F          = (1 << 14);
		static const uint16_t STATUS_100H          = (1 << 13);
		static const uint16_t STATUS_10F           = (1 << 12);
		static const uint16_t STATUS_10H           = (1 << 11);
		static const uint16_t STATUS_AN_COMPLETE   = (1 << 5);
		static const uint16_t STATUS_RM_FAULT      = (1 << 4);
		static const uint16_t STATUS_AN_ABILITY    = (1 << 3);
		static const uint16_t STATUS_LINK_UP       = (1 << 2);
		static const uint16_t STATUS_JABBER        = (1 << 1);
		static const uint16_t STATUS_EX_CAPABILITY = (1 << 0);

		// Auto Negotiation Advertisement Bit Definitions
		static const uint16_t AN_ADVERTISEMENT_NEXT_PAGE = (1 << 15);  
		static const uint16_t AN_ADVERTISEMENT_RM_FAULT  = (1 << 13);
		static const uint16_t AN_ADVERTISEMENT_ASM_DIR   = (1 << 11);
		static const uint16_t AN_ADVERTISEMENT_PAUSE     = (1 << 10);
		static const uint16_t AN_ADVERTISEMENT_100_T4    = (1 << 9);
		static const uint16_t AN_ADVERTISEMENT_100F      = (1 << 8);
		static const uint16_t AN_ADVERTISEMENT_100H      = (1 << 7);
		static const uint16_t AN_ADVERTISEMENT_10F       = (1 << 6);
		static const uint16_t AN_ADVERTISEMENT_10H       = (1 << 5);
		static const uint16_t AN_ADVERTISEMENT_SELECTOR  = (1 << 0);

		// Auto Negostiate Link Partner Ability Bit Definitions
		static const uint16_t AN_LINK_PARTNER_NEXT_PAGE  = (1 << 15);
		static const uint16_t AN_LINK_PARTNER_ACK        = (1 << 14);
		static const uint16_t AN_LINK_PARTNER_RM_FAULT   = (1 << 13);
		static const uint16_t AN_LINK_PARTNER_ASM_DIR    = (1 << 11);
		static const uint16_t AN_LINK_PARTNER_PAUSE      = (1 << 10);
		static const uint16_t AN_LINK_PARTNER_100_T4     = (1 << 9);
		static const uint16_t AN_LINK_PARTNER_100F       = (1 << 8);
		static const uint16_t AN_LINK_PARTNER_100H       = (1 << 7);
		static const uint16_t AN_LINK_PARTNER_10F        = (1 << 6);
		static const uint16_t AN_LINK_PARTNER_10H        = (1 << 5);
		static const uint16_t AN_LINK_PARTNER_SELECTOR   = (1 << 0);

		// Delay constants
		static const uint32_t DELAY_RESET     = 0x00020000L;
		static const uint32_t DELAY_AN        = 0x00800000L;

		// for MICREL/KSZ8041NL Vender special register
		static const uint16_t REG_PHY_CONTROL_1    = 0x1E;

		/*==============================================================================*/
		//  DP83822 Boot Strap:															//
		//..............................................................................//
		//    COL   (#29):  FX_EN:    0, PHY_AD0:   1									//
		//    RX_D0 (#30):  AN_1:     1, PHY_AD1:   0									//
		//    RX_D1 (#31):  EEE_EN:   0, PHY_AD2:   0									//
		//    RX_D2 (#32):  FLD_EN:   0, PHY_AD3:   0									//
		//    RX_D3 (# 1):  AN_EN:    1, PHY_AD4:   0									//
		//    LED_0 (#17):  AN_0:     1													//
		//    CRS   (#27):  LED_CFG:  1, LED_SPEED: 0									//
		//    RX_ER (#28):  AMDIX_EN: 1, RGMII_EN:  0									//
		//    RX_DV (#26):  XI_50:    0, RMII_EN:   0									//
		//..............................................................................//
		//  Force Modes:																//
		//    FX_EN: 0, AN_EN: 0, AN_1: 0, AN_0: 0 --->  10BASE-Te, Half-Duplex			//
		//    FX_EN: 0, AN_EN: 0, AN_1: 0, AN_0: 1 --->  10BASE-Te, Full-Duplex			//
		//    FX_EN: 0, AN_EN: 0, AN_1: 1, AN_0: 0 ---> 100BASE-TX, Half-Duplex			//
		//    FX_EN: 0, AN_EN: 0, AN_1: 1, AN_0: 1 ---> 100BASE-TX, Full-Duplex			//
		//  Advertised Modes:															//
		//    FX_EN: 0, AN_EN: 1, AN_1: 0, AN_0: 0 --->  10BASE-Te, Half-Duplex			//
		//    FX_EN: 0, AN_EN: 1, AN_1: 0, AN_0: 1 --->  10BASE-Te, Half/Full-Duplex	//
		//    FX_EN: 0, AN_EN: 1, AN_1: 1, AN_0: 0 --->  10BASE-Te, Half-Duplex			//
		//                                              100BASE-TX, Half-Duplex			//
		//   *FX_EN: 0, AN_EN: 1, AN_1: 1, AN_0: 1 --->  10BASE-Te, Half/Full-Duplex	//
		//                                              100BASE-TX, Half/Full-Duplex	//
		//  Fiber Modes:																//
		//    FX_EN: 1, AN_EN: X, AN_1: X, AN_0: 0 ---> 100BASE-FX, Half-Duplex			//
		//    FX_EN: 1, AN_EN: X, AN_1: X, AN_0: 1 ---> 100BASE-FX, Full-Duplex			//
		/*==============================================================================*/
		static const uint16_t REG_DP83822_REGCR   = 0x000D;
		static const uint16_t REG_DP83822_ADDAR   = 0x000E;
		static const uint16_t REG_DP83822_RCSR    = 0x0017;
		static const uint16_t REG_DP83822_LEDCR   = 0x0018;
		static const uint16_t REG_DP83822_PHYCR   = 0x0019;
		static const uint16_t REG_DP83822_IOCTRL1 = 0x0462;

		uint16_t local_advertise_;

		void mii_write1_()
		{
			// The processing of one bit about frame format of MII Management Interface which is 
			// provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
			// The data that 1 is output. 
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000006;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000007;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000007;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000006;
			}
		}


		void mii_write0_()
		{
			// The processing of one bit about frame format of MII Management Interface which is 
			// provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
			// The data that 0 is output. 
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000002;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000003;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000003;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000002;
			}
		}


		void trans_1_to_0_()
		{
	    	// The processing of TA (turnaround) about writing of the frame format of
			// MII Management Interface which is provided by "Table 22-12" of "22.2.4.5"
			// of "IEEE 802.3-2008_section2".
			mii_write1_();
			mii_write0_();
		}


		void trans_z_to_0_()
		{
			// The processing of TA (turnaround) about reading of the frame format of
			// MII Management Interface which is provided by "Table 22-12" of "22.2.4.5"
			// of "IEEE 802.3-2008_section2".
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000000;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000001;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000001;
			}
			for(int j = MII_WAIT; j > 0; j--) {
				ETHERC::PIR = 0x00000000;
			}
		}


		void reg_set_(uint16_t reg_addr, int32_t option)
		{
			// The processing of ST (start of frame),OP (operation code), PHYAD (PHY Address), and 
			// REGAD (Register Address)  about the frame format of MII Management Interface which is 
			// provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
			uint16_t data = (MII_ST << 14);          /* ST code    */

			if(option == MII_READ ) {
				data |= (MII_READ << 12);	// OP code(RD)
			} else {
				data |= (MII_WRITE << 12);	// OP code(WT)
			}

			data |= (DEV_ADR << 7);			// PHY Address
			data |= (reg_addr << 2);		// Reg Address

			int i = 14;
			while( i > 0 ) {
				if((data & 0x8000) == 0) {
					mii_write0_();
				} else {
					mii_write1_();
				}
				data <<= 1;
				i--;
			}
		}


		uint16_t reg_read_()
		{
			// The processing of DATA (data) about reading of the frame format of MII Management
			// Interface which is provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
			uint16_t data = 0;
			int i = 16;
			while( i > 0 ) {
				for(int j = MII_WAIT; j > 0; j--) {
					ETHERC::PIR = 0x00000000;
				}
				for(int j = MII_WAIT; j > 0; j--) {
					ETHERC::PIR = 0x00000001;
				}

				data <<= 1;
				// MDI read
				data |= static_cast<uint16_t>((ETHERC::PIR() & 0x00000008) >> 3);

				for(int j = MII_WAIT; j > 0; j--) {
					ETHERC::PIR = 0x00000001;
				}
				for(int j = MII_WAIT; j > 0; j--) {
					ETHERC::PIR = 0x00000000;
				}
				i--;
			}
			return data;
		}


		void reg_write_(uint16_t data)
		{
			// The processing of DATA (data) about writing of the frame format of MII Management
			// Interface which is provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
			int i = 16;
			while( i > 0 ) {
				if((data & 0x8000) == 0) {
					mii_write0_();
				} else {
					mii_write1_();
				}
				i--;
				data <<= 1;
			}
		}


		void preamble_()
		{
			// The processing of PRE (preamble) about the frame format of MII Management
			// Interface which is provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
			int i = 32;
			while(i > 0) {
				mii_write1_();
				i--;
			}
		}


		uint16_t read_sub_(uint16_t reg_addr)
		{
			// The value is read from the PHY register by the frame format of MII Management
			// Interface provided for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
			preamble_();
			reg_set_(reg_addr, MII_READ);
			trans_z_to_0_();
			uint16_t data = reg_read_();
			trans_z_to_0_();
			return data;
		}


		void write_sub_(uint16_t reg_addr, uint16_t data)
		{
			// The value is read from the PHY register by the frame format of MII Management
			// Interface provided for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
			preamble_();
			reg_set_(reg_addr, MII_WRITE);
			trans_1_to_0_();
			reg_write_(data);
			trans_z_to_0_();
		}


		uint16_t read_(uint16_t addr)
		{
			if(addr > 0x1f) {  // 拡張アドレスの場合
				if(DEV_OPT == phy_option::TI_DP83822) {
					write_sub_(REG_DP83822_REGCR, 0x001F);  // address command
					write_sub_(REG_DP83822_ADDAR, addr);
					write_sub_(REG_DP83822_REGCR, 0x401F);  // read/write command
					return read_sub_(REG_DP83822_ADDAR);
				}
				utils::format("PHY Address Range Error: %04X\n") % static_cast<int>(addr);
				return 0;
			} else {
				return read_sub_(addr);
			}
		}


		void write_(uint16_t addr, uint16_t data)
		{
			if(addr > 0x1f) {  // 拡張アドレスの場合
				if(DEV_OPT == phy_option::TI_DP83822) {
					write_sub_(REG_DP83822_REGCR, 0x001F);  // address command
					write_sub_(REG_DP83822_ADDAR, addr);
					write_sub_(REG_DP83822_REGCR, 0x401F);  // read/write command
					write_sub_(REG_DP83822_ADDAR, data);
					return;
				}
				utils::format("PHY Address Range Error: %04X\n") % static_cast<int>(addr);
			} else {
				write_sub_(addr, data);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ethc	インサーネット・コントローラー
		*/
		//-----------------------------------------------------------------//
		phy_base() : local_advertise_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY 初期化
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool init(void)
		{
			uint16_t reg;

			debug_format("Start PHY init: ADR: %d\n") % static_cast<int>(DEV_ADR);
			reg = read_(REG_IDENTIFIER1);
			reg = read_(REG_IDENTIFIER1);
			debug_format("PHY Identifier1: 0x%04X\n") % static_cast<int>(reg);
			reg = read_(REG_IDENTIFIER2);
			reg = read_(REG_IDENTIFIER2);
			debug_format("PHY Identifier2: 0x%04X\n") % static_cast<int>(reg);

			// Reset PHY
			write_(REG_CONTROL, CONTROL_RESET);

			uint32_t count = 0;
			do {  // Reset completion waiting
				reg = read_(REG_CONTROL);
				count++;
			} while((reg & CONTROL_RESET) && (count < DELAY_RESET));

			debug_format("PHY init: reset loop: %d/%d\n")
				% static_cast<int>(count)
				% static_cast<int>(DELAY_RESET);

			if(count < DELAY_RESET) {
				// When KSZ8041NL of the Micrel, Inc. is used, 
				// the pin that outputs the state of LINK is used combinedly with ACTIVITY in default. 
				// The setting of the pin is changed so that only the state of LINK is output. 
				if(DEV_OPT == phy_option::MICREL_KSZ8041NL) {
					reg = read_(REG_PHY_CONTROL_1);
					reg &= ~0x8000;
					reg |= 0x4000;
					write_(REG_PHY_CONTROL_1, reg);
				} else if(DEV_OPT == phy_option::TI_DP83822) {

					debug_format("DP83822 Boot Strap Latch in  (0x0462): 0x%04X\n")
						% static_cast<int>(read_(0x0462));
					debug_format("DP83822 Boot Strap Latch in #1(SOR1): 0x%04X\n")
						% static_cast<int>(read_(0x0467));
					debug_format("DP83822 Boot Strap Latch in #2(SOR2): 0x%04X\n")
						% static_cast<int>(read_(0x0468));

					// LED_0: Blink Rate: 10Hz, Active High
					// LED_1: 10M/100M, Active High
					write_(REG_DP83822_LEDCR,   0b0000001010000000);
					write_(REG_DP83822_PHYCR,   0b0000000000000001);
					write_(REG_DP83822_IOCTRL1, 0b0100001100000001);
					write_(REG_DP83822_RCSR,    0b0000000001100001);

					debug_format("DP83822 Boot Strap Latch out (0x0462): 0x%04X\n")
						% static_cast<int>(read_(0x0462));
				}

				debug_format("PHY init OK !\n");
				return true;
			}
			debug_format("PHY Init NG !\n");
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY 自動速度調整
			@param[in]	pause_frame	ETHER_FLAG_OFF なら「true」
		*/
		//-----------------------------------------------------------------//
		void start_autonegotiate(bool pause_frame)
		{
			// Set local ability When pause frame is not used
			if(pause_frame) {
				local_advertise_ = (AN_ADVERTISEMENT_100F
					| AN_ADVERTISEMENT_100H
					| AN_ADVERTISEMENT_10F
					| AN_ADVERTISEMENT_10H
					| AN_ADVERTISEMENT_SELECTOR);
			} else {  // When pause frame is used
				local_advertise_ = (AN_ADVERTISEMENT_ASM_DIR
					| AN_ADVERTISEMENT_PAUSE
					| AN_ADVERTISEMENT_100F
					| AN_ADVERTISEMENT_100H
					| AN_ADVERTISEMENT_10F
					| AN_ADVERTISEMENT_10H
					| AN_ADVERTISEMENT_SELECTOR);
			}
    
			// Configure what the PHY and the Ethernet controller on this board supports
			write_(REG_AN_ADVERTISEMENT, local_advertise_);
			write_(REG_CONTROL, (CONTROL_AN_ENABLE | CONTROL_AN_RESTART));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY 自動速度調整結果取得
			@param[out]	local_pause		store the local pause bits
			@param[out]	partner_pause	store the partner pause bits
			@return		リンク・ステート
		*/
		//-----------------------------------------------------------------//
		phy_link_state get_autonegotiate(uint16_t& local_pause, uint16_t& partner_pause)
		{
			phy_link_state speed_duplex = phy_link_state::NO_LINK;

			// Because reading the first time shows the previous state, the Link status bit is read twice.
			uint16_t reg = read_(REG_STATUS);
			reg = read_(REG_STATUS);

			// When the link isn't up, return error
			if(!(reg & STATUS_LINK_UP)) {
				asm("nop");
				return speed_duplex;
			}

			// Establish local pause capability
			if(local_advertise_ & AN_ADVERTISEMENT_PAUSE) {
				local_pause |= (1 << 1);
			}
    
			if(local_advertise_ & AN_ADVERTISEMENT_ASM_DIR) {
				local_pause |= 1;
			}

			// When the auto-negotiation isn't completed, return error
			if(!(reg & STATUS_AN_COMPLETE)) {
				return speed_duplex;
			} else {
				// Get the link partner response
				reg = read_(REG_AN_LINK_PARTNER);

				// Establish partner pause capability
				if((reg & AN_LINK_PARTNER_PAUSE) == AN_LINK_PARTNER_PAUSE) {
					partner_pause = ( 1 << 1 );
				}

				if((reg & AN_LINK_PARTNER_ASM_DIR) == AN_LINK_PARTNER_ASM_DIR) {
					partner_pause |= 1;
				}

				// Establish the line speed and the duplex
				if(reg & AN_LINK_PARTNER_10H) {
					speed_duplex = phy_link_state::LINK_10H;
				}

				if(reg & AN_LINK_PARTNER_10F) {
					speed_duplex = phy_link_state::LINK_10F;
				}

				if(reg & AN_LINK_PARTNER_100H) {
					speed_duplex = phy_link_state::LINK_100H;
				}

				if(reg & AN_LINK_PARTNER_100F) {
					speed_duplex = phy_link_state::LINK_100F;
				}
		        return speed_duplex;
    		}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY リンクステータス取得
			@return リンク・アップなら「true」 
		*/
		//-----------------------------------------------------------------//
		bool get_link_status()
		{
			// Because reading the first time shows the previous state, the Link status bit is read twice.
			uint16_t reg = read_(REG_STATUS);
			reg = read_(REG_STATUS);

			// When the link isn't up, return error
			if(reg & STATUS_LINK_UP) {  // Link is up
				return true;
			} else {  // Link is down
				return false;
			}
		}
	};
}
