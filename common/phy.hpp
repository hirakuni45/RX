#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・PHY 定義 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PHY 定義クラス
		@param[in]	ETHC	インサーネット・コントローラー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHC>
	class phy_t {

	public:
		enum LinkStatE
		{
			PHY_NO_LINK = 0,
			PHY_LINK_10H,
			PHY_LINK_10F,
			PHY_LINK_100H,
			PHY_LINK_100F,
		};


	private:

		// Media Independent Interface
		static const int PHY_MII_ST    = 1;
		static const int PHY_MII_READ  = 2;
		static const int PHY_MII_WRITE = 1;

		/*
 		 * PHY address selection.
		 * Please select one of them.
		 */
		static const int PHY_MII_ADDR = 0;  /* for GR-SAKURA (RX63N). */

		static const int PHY_MII_WAIT = 2;

		/* Standard PHY Registers */
		static const int PHY_REG_CONTROL          = 0;
		static const int PHY_REG_STATUS           = 1;
		static const int PHY_REG_IDENTIFIER1      = 2;
		static const int PHY_REG_IDENTIFIER2      = 3;
		static const int PHY_REG_AN_ADVERTISEMENT = 4;
		static const int PHY_REG_AN_LINK_PARTNER  = 5;
		static const int PHY_REG_AN_EXPANSION     = 6;

		/* Vendor Specific PHY Registers */
		#ifdef MICREL_KSZ8041NL
		static const uint16_t PHY_REG_PHY_CONTROL_1 = (0x1E);
		#endif /* MICREL_KSZ8041NL */

		/* Basic Mode Control Register Bit Definitions */
		static const uint16_t PHY_CONTROL_RESET        = (1 << 15);
		static const uint16_t PHY_CONTROL_LOOPBACK     = (1 << 14);
		static const uint16_t PHY_CONTROL_100_MBPS     = (1 << 13);
		static const uint16_t PHY_CONTROL_AN_ENABLE    = (1 << 12);
		static const uint16_t PHY_CONTROL_POWER_DOWN   = (1 << 11);
		static const uint16_t PHY_CONTROL_ISOLATE      = (1 << 10);
		static const uint16_t PHY_CONTROL_AN_RESTART   = (1 << 9);
		static const uint16_t PHY_CONTROL_FULL_DUPLEX  = (1 << 8);
		static const uint16_t PHY_CONTROL_COLLISION    = (1 << 7);

		/* Basic Mode Status Register Bit Definitions */
		static const uint16_t PHY_STATUS_100_T4        = (1 << 15);
		static const uint16_t PHY_STATUS_100F          = (1 << 14);
		static const uint16_t PHY_STATUS_100H          = (1 << 13);
		static const uint16_t PHY_STATUS_10F           = (1 << 12);
		static const uint16_t PHY_STATUS_10H           = (1 << 11);
		static const uint16_t PHY_STATUS_AN_COMPLETE   = (1 << 5);
		static const uint16_t PHY_STATUS_RM_FAULT      = (1 << 4);
		static const uint16_t PHY_STATUS_AN_ABILITY    = (1 << 3);
		static const uint16_t PHY_STATUS_LINK_UP       = (1 << 2);
		static const uint16_t PHY_STATUS_JABBER        = (1 << 1);
		static const uint16_t PHY_STATUS_EX_CAPABILITY = (1 << 0);

		/* Auto Negotiation Advertisement Bit Definitions */
		static const uint16_t PHY_AN_ADVERTISEMENT_NEXT_PAGE = (1 << 15);
		static const uint16_t PHY_AN_ADVERTISEMENT_RM_FAULT  = (1 << 13);
		static const uint16_t PHY_AN_ADVERTISEMENT_ASM_DIR   = (1 << 11);
		static const uint16_t PHY_AN_ADVERTISEMENT_PAUSE     = (1 << 10);
		static const uint16_t PHY_AN_ADVERTISEMENT_100_T4    = (1 << 9);
		static const uint16_t PHY_AN_ADVERTISEMENT_100F      = (1 << 8);
		static const uint16_t PHY_AN_ADVERTISEMENT_100H      = (1 << 7);
		static const uint16_t PHY_AN_ADVERTISEMENT_10F       = (1 << 6);
		static const uint16_t PHY_AN_ADVERTISEMENT_10H       = (1 << 5);
		static const uint16_t PHY_AN_ADVERTISEMENT_SELECTOR  = (1 << 0);

		/* Auto Negostiate Link Partner Ability Bit Definitions */
		static const uint16_t PHY_AN_LINK_PARTNER_NEXT_PAGE = (1 << 15);
		static const uint16_t PHY_AN_LINK_PARTNER_ACK       = (1 << 14);
		static const uint16_t PHY_AN_LINK_PARTNER_RM_FAULT  = (1 << 13);
		static const uint16_t PHY_AN_LINK_PARTNER_ASM_DIR   = (1 << 11);
		static const uint16_t PHY_AN_LINK_PARTNER_PAUSE     = (1 << 10);
		static const uint16_t PHY_AN_LINK_PARTNER_100_T4    = (1 << 9);
		static const uint16_t PHY_AN_LINK_PARTNER_100F      = (1 << 8);
		static const uint16_t PHY_AN_LINK_PARTNER_100H      = (1 << 7);
		static const uint16_t PHY_AN_LINK_PARTNER_10F       = (1 << 6);
		static const uint16_t PHY_AN_LINK_PARTNER_10H       = (1 << 5);
		static const uint16_t PHY_AN_LINK_PARTNER_SELECTOR  = (1 << 0);


		/* Delay constants */
		static const uint32_t PHY_DELAY_RESET               = 0x00020000L; 
		static const uint32_t PHY_DELAY_AN                  = 0x00800000L;

		uint16_t	local_advertise_;

		/*
		 * The value is read from the PHY register by the frame format of MII Management Interface provided 
		 * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
		 */
		uint16_t read_(uint16_t reg_addr)
		{
			preamble_();
			reg_set_(reg_addr, PHY_MII_READ);
			trans_Zto0_();
			uint16_t data = reg_read_();
			trans_Zto0_();
			return data;
		}


		/*
		 * The value is read from the PHY register by the frame format of MII Management Interface provided
		 * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2. 
		 */
		void write_(uint16_t reg_addr, uint16_t data)
		{
			preamble_();
			reg_set_(reg_addr, PHY_MII_WRITE);
			trans_1to0_();
			reg_write_(data);
			trans_Zto0_();
		}


		/*
		 * The processing of PRE (preamble) about the frame format of MII Management Interface which is 
		 * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
		 */
		void preamble_()
		{
			int i = 32;
			while( i > 0 )
			{
				mii_write1_();
				i--;
			}
		}


		/*
		 * The processing of ST (start of frame),OP (operation code), PHYAD (PHY Address), and 
		 * REGAD (Register Address)  about the frame format of MII Management Interface which is 
		 * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
		 */
		void reg_set_(uint16_t reg_addr, int32_t option)
		{
			uint16_t data = 0;
			data = (PHY_MII_ST << 14);          /* ST code    */

			if( option == PHY_MII_READ ) {
				data |= (PHY_MII_READ << 12);   /* OP code(RD)  */
			} else {
				data |= (PHY_MII_WRITE << 12);  /* OP code(WT)  */
			}

			data |= (PHY_MII_ADDR << 7);        /* PHY Address  */
			data |= (reg_addr << 2);            /* Reg Address  */

			int i = 14;
			while( i > 0 ) {
				if( (data & 0x8000) == 0 ) {
					mii_write0_();
				} else {
					mii_write1_();
				}
				data <<= 1;
				i--;
			}
		}


		/*
		 * The processing of DATA (data) about reading of the frame format of MII Management Interface which is 
		 * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
		 */
		uint16_t reg_read_()
		{
			uint16_t reg_data = 0;
			int i = 16;
			while( i > 0 ) {
				for(int j = PHY_MII_WAIT; j > 0; j--) {
					ETHC::PIR = 0x00000000;
				}
				for(int j = PHY_MII_WAIT; j > 0; j--) {
					ETHC::PIR = 0x00000001;
				}

				reg_data <<= 1;
				reg_data |= (ETHC::PIR() & 0x00000008) >> 3;  /* MDI read  */

				for(int j = PHY_MII_WAIT; j > 0; j--) {
					ETHC::PIR = 0x00000001;
				}
				for(int j = PHY_MII_WAIT; j > 0; j--) {
					ETHC::PIR = 0x00000000;
				}
				i--;
			}
			return reg_data;
		}


		/*
		 * The processing of DATA (data) about writing of the frame format of MII Management Interface which is 
		 * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
		 */
		void reg_write_(uint16_t data)
		{
    		int i = 16;
			while( i > 0 ) {
				if( (data & 0x8000) == 0 ) {
					mii_write0_();
				} else {
					mii_write1_();
				}
				i--;
				data <<= 1;
			}
		}


		/*
		 * The processing of TA (turnaround) about reading of the frame format of MII Management Interface
		 * which is provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
		 */
		void trans_Zto0_()
		{
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000000;
			}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000001;
			}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000001;
			}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000000;
			}
		}


		/*
		 * The processing of TA (turnaround) about writing of the frame format of MII Management Interface
		 * which is provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
		 */
		void trans_1to0_() {
			mii_write1_();
			mii_write0_();
		}


		/*
		 * The processing of one bit about frame format of MII Management Interface which is 
		 * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
		 * The data that 1 is output. 
		 */
		void mii_write1_()
		{
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000006;
			}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000007;
			}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000007;
			}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000006;
			}
		}


		/*
		 * The processing of one bit about frame format of MII Management Interface which is 
		 * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2". 
		 * The data that 0 is output. 
		 */
		void mii_write0_()
		{
			for(int j = PHY_MII_WAIT; j > 0; j--) {
		        ETHC::PIR = 0x00000002;
    		}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
		        ETHC::PIR = 0x00000003;
    		}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR = 0x00000003;
			}
			for(int j = PHY_MII_WAIT; j > 0; j--) {
				ETHC::PIR.LONG = 0x00000002;
			}
		}

		void nop_() const {
			asm("nop");
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		phy_t() : local_advertise_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  Resets Ethernet PHY device
			@return OK: true, ERROR: false
		*/
		//-----------------------------------------------------------------//
		bool init()
		{
			/* Reset PHY */
			write_(PHY_REG_CONTROL, PHY_CONTROL_RESET);

			uint16_t count = 0;
			uint16_t reg;
			/* Reset completion waiting */
			do {
				reg = read_(PHY_REG_CONTROL);
				count++;
			} while ( (reg & PHY_CONTROL_RESET) && (count < PHY_DELAY_RESET) );

			if( count < PHY_DELAY_RESET ) {
				/* 
				 * When KSZ8041NL of the Micrel, Inc. is used, 
				 * the pin that outputs the state of LINK is used combinedly with ACTIVITY in default. 
				 * The setting of the pin is changed so that only the state of LINK is output. 
				 */
#ifdef MICREL_KSZ8041NL
				reg = read_(PHY_REG_PHY_CONTROL_1);
				reg &= ~0x8000;
				reg |= 0x4000;
				write_(PHY_REG_PHY_CONTROL_1, reg);
#endif
				return true;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  Starts autonegotiate
			@param[in]	PauseFrameEnableFlag
		*/
		//-----------------------------------------------------------------//
		void start_autonegotiate(bool PauseFrameEnableFlag)
		{
			/* Set local ability */
			/* When pause frame is not used */
			if (PauseFrameEnableFlag) {
				local_advertise_ = (PHY_AN_ADVERTISEMENT_100F    |
									PHY_AN_ADVERTISEMENT_100H    |
									PHY_AN_ADVERTISEMENT_10F     |
									PHY_AN_ADVERTISEMENT_10H     |
									PHY_AN_ADVERTISEMENT_SELECTOR);
			} else {
				local_advertise_ = (PHY_AN_ADVERTISEMENT_ASM_DIR |
									PHY_AN_ADVERTISEMENT_PAUSE   |
									PHY_AN_ADVERTISEMENT_100F    |
									PHY_AN_ADVERTISEMENT_100H    |
									PHY_AN_ADVERTISEMENT_10F     |
									PHY_AN_ADVERTISEMENT_10H     |
									PHY_AN_ADVERTISEMENT_SELECTOR);
			}
    
			/* Configure what the PHY and the Ethernet controller on this board supports */
			write_(PHY_REG_AN_ADVERTISEMENT, local_advertise_);
			write_(PHY_REG_CONTROL, (PHY_CONTROL_AN_ENABLE | PHY_CONTROL_AN_RESTART) );
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  reports the other side's physical capability
			@param[in]	line_speed_duplex	both the line speed and the duplex
			@param[in]	local_pause			store the local pause bits.
			@param[in]	partner_pause		store the partner pause bits.
			@return OK: true, ERROR: false
		*/
		//-----------------------------------------------------------------//
		bool set_autonegotiate(uint16_t& line_speed_duplex, uint16_t& local_pause, uint16_t& partner_pause)
		{
			/* Because reading the first time shows the previous state, the Link status bit is read twice. */
			uint16_t reg = read_(PHY_REG_STATUS);
			reg = read_(PHY_REG_STATUS);

			/* When the link isn't up, return error */
			if (!(reg & PHY_STATUS_LINK_UP)) {
				nop_();
				return false;
			}

			/* Establish local pause capability */    
			if (local_advertise_ & PHY_AN_ADVERTISEMENT_PAUSE) {
				local_pause |= (1 << 1);
    		}
    
			if (local_advertise_ & PHY_AN_ADVERTISEMENT_ASM_DIR) {
				local_pause |= 1;
			}
    
			/* When the auto-negotiation isn't completed, return error */
			if (!(reg & PHY_STATUS_AN_COMPLETE)) {
				return false;
			} else {
				/* Get the link partner response */
				reg = read_(PHY_REG_AN_LINK_PARTNER);

				/* Establish partner pause capability */
				if ( (reg & PHY_AN_LINK_PARTNER_PAUSE) == PHY_AN_LINK_PARTNER_PAUSE ) {
					partner_pause = ( 1 << 1 );
				}

				if ( (reg & PHY_AN_LINK_PARTNER_ASM_DIR) == PHY_AN_LINK_PARTNER_ASM_DIR ) {
					partner_pause |= 1;
				}

				/* Establish the line speed and the duplex */
				if ( reg & PHY_AN_LINK_PARTNER_10H ) {
					line_speed_duplex = PHY_LINK_10H;
				}

				if ( reg & PHY_AN_LINK_PARTNER_10F ) {
					line_speed_duplex = PHY_LINK_10F;
				}

				if ( reg & PHY_AN_LINK_PARTNER_100H ) {
					line_speed_duplex = PHY_LINK_100H;
				}

				if ( reg & PHY_AN_LINK_PARTNER_100F ) {
					line_speed_duplex = PHY_LINK_100F;
				}

			return true;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  Returns the status of the physical link
			@return false: links is down, true: otherwise 
		*/
		//-----------------------------------------------------------------//
		bool get_link_status()
		{
			/* Because reading the first time shows the previous state, the Link status bit is read twice. */
			uint16_t reg = read_(PHY_REG_STATUS);
			reg = read_(PHY_REG_STATUS);

			/* When the link isn't up, return error */
			if (!(reg & PHY_STATUS_LINK_UP)) {
				nop_();
				/* Link is down */
				return false;
			} else {
				/* Link is up */
				return true;
			}
		}

	};
}
