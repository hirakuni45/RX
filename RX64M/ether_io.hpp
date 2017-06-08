#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・Etherenet I/O 制御 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "common/format.hpp"
#include "chip/phy_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Ethernet I/O 制御クラス
		@param[in]	ETHRC	インサーネット・コントローラー
		@param[in]	EDMAC	インサーネットＤＭＡコントローラー
		@param[in]	PHY		物理層コントローラー
		@param[in]	INTR_TASK	割り込みタスク型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHRC, class EDMAC, class PHY, class INTR_TASK>
	class ether_io {
	public:
		static const int EMAC_BUFSIZE = 1536;  			// Must be 32-byte aligned
		static const int EMAC_NUM_RX_DESCRIPTORS = 1;	// The number of RX descriptors.
		static const int EMAC_NUM_TX_DESCRIPTORS = 1;	// The number of TX descriptors.

		// The total number of EMAC buffers to allocate. The number of
		// total buffers is simply the sum of the number of transmit and
		// receive buffers.
		static const int  EMAC_NUM_BUFFERS = EMAC_NUM_RX_DESCRIPTORS + EMAC_NUM_TX_DESCRIPTORS;

		/* Bit definitions of status member of DescriptorS */
		static const uint32_t TACT = 0x80000000;
		static const uint32_t RACT = 0x80000000;
		static const uint32_t TDLE = 0x40000000;
		static const uint32_t RDLE = 0x40000000;
		static const uint32_t TFP1 = 0x20000000;
		static const uint32_t RFP1 = 0x20000000;
		static const uint32_t TFP0 = 0x10000000;
		static const uint32_t RFP0 = 0x10000000;
		static const uint32_t TFE  = 0x08000000;
		static const uint32_t RFE  = 0x08000000;

		static const uint32_t RFS9_RFOVER = 0x00000200;
		static const uint32_t RFS8_RAD    = 0x00000100;
		static const uint32_t RFS7_RMAF   = 0x00000080;
		static const uint32_t RFS4_RRF    = 0x00000010;
		static const uint32_t RFS3_RTLF   = 0x00000008;
		static const uint32_t RFS2_RTSF   = 0x00000004;
		static const uint32_t RFS1_PRE    = 0x00000002;
		static const uint32_t RFS0_CERF   = 0x00000001;

		static const uint32_t TWBI        = 0x04000000;
		static const uint32_t TFS8_TAD    = 0x00000100;
		static const uint32_t TFS3_CND    = 0x00000008;
		static const uint32_t TFS2_DLC    = 0x00000004;
		static const uint32_t TFS1_CD     = 0x00000002;
		static const uint32_t TFS0_TRO    = 0x00000001;

		static const int PAUSE_TABLE_ENTRIES = 8;	///< Number of entries in PAUSE resolution table

		/* Local device and link partner PAUSE settings */
		static const int XMIT_PAUSE_OFF = 0; ///< The pause frame transmission is prohibited.
		static const int RECV_PAUSE_OFF = 0; ///< The pause frame reception is prohibited.   
		static const int XMIT_PAUSE_ON  = 1; ///< The pause frame transmission is permitted.
		static const int RECV_PAUSE_ON  = 1; ///< The pause frame reception is permitted.   

		/* PAUSE link mask and shift values */
		/*
		 * The mask value and shift value which are for that shift the bits form a line and 
		 * for comparing the bit information of PAUSE function which support the local device and 
		 * Link partner with the assorted table(pause_resolution) which enable or disable the PAUSE frame. 
		 */
		static const int LINK_RES_ABILITY_MASK = 3;
		static const int LINK_RES_LOCAL_ABILITY_BITSHIFT = 2;


		// Bit definition of interrupt factor of Ethernet interrupt
		static const uint32_t EMAC_LCHNG_INT  =   (1UL << 2);
		static const uint32_t EMAC_MPD_INT    =   (1UL << 1);

		static const uint32_t EMAC_RFCOF_INT  =   (1UL << 24);
		static const uint32_t EMAC_ECI_INT    =   (1UL << 22);
		static const uint32_t EMAC_TC_INT     =   (1UL << 21);
		static const uint32_t EMAC_FR_INT     =   (1UL << 18);
		static const uint32_t EMAC_RDE_INT    =   (1UL << 17);
		static const uint32_t EMAC_RFOF_INT   =   (1UL << 16);


		enum class pausemask_e : uint8_t {
			MASK0, MASK1, MASK2, MASK3,
			MASK4, MASK5, MASK6, MASK7,
			MASK8, MASK9, MASKA, MASKB,
			MASKC, MASKD, MASKE, MASKF
		};

		enum class pauseval_e : uint8_t {
			VAL0, VAL1, VAL2, VAL3,
			VAL4, VAL5, VAL6, VAL7,
			VAL8, VAL9, VALA, VALB,
			VALC, VALD, VALE, VALF
		};

		struct pause_resolution_t {
			pausemask_e mask;
			pauseval_e  value;
			uint8_t     transmit;
			uint8_t     receive;
		};

		static const int OK    = 0;
		static const int ERROR = -1;
		static const int ERROR_LINK = -2;
		static const int ERROR_MPDE = -3;
		static const int ERROR_TACT = -4;	///< Transmission buffer dryness error. 

		static const int NO_DATA = 0;

		static const int FLAG_OFF         = 0;
		static const int FLAG_ON          = 1;
		static const int FLAG_ON_LINK_ON  = 3;
		static const int FLAG_ON_LINK_OFF = 2;

		static const int NO_USE_MAGIC_PACKET_DETECT = 0;
		static const int USE_MAGIC_PACKET_DETECT    = 1;

		 // Please define the level of the LINKSTA signal when Link becomes up.
		static const int LINK_PRESENT    = 0;
		// Please define the level of the LINKSTA signal when Link becomes down.
		static const int LINK_NOTPRESENT = 1;

		struct descriptor_s {
    		uint32_t	status;
			uint16_t	size;
			uint16_t	bufsize;
			uint8_t*	buf_p;
			descriptor_s*	next;
		};

		struct etherbuffer_s {
			uint8_t  buffer[EMAC_NUM_BUFFERS][EMAC_BUFSIZE];
		};

	private:
		static INTR_TASK	intr_task_;
		static volatile uint8_t  mpd_flag_;

		PHY		phy_;

		uint8_t	intr_level_;

		uint8_t	mac_addr_[6];

		bool	pause_frame_enable_flag_;
		volatile uint8_t	lchng_flag_;
		volatile uint8_t	transfer_enable_flag_;
		volatile uint8_t	magic_packet_detect_;

		descriptor_s rx_descriptors_[EMAC_NUM_RX_DESCRIPTORS] __attribute__ ((aligned(32)));
		descriptor_s tx_descriptors_[EMAC_NUM_TX_DESCRIPTORS] __attribute__ ((aligned(32)));
		etherbuffer_s ether_buffers_ __attribute__ ((aligned(32)));

		descriptor_s* app_rx_desc_;
		descriptor_s* app_tx_desc_;

		bool	link_stat_;

		// ※必要なら、実装する
		void sleep_() { asm("nop"); }


		void reset_mac_() {
			/* Software reset */
			EDMAC::EDMR.SWR = 1;

			/* Delay */
			/*
			 * Waiting time until the initialization of ETHERC and EDMAC is completed is 64 cycles
			 * in the clock conversion of an internal bus of EDMAC. 
			 */
			for(int i = 0; i < 0x00000100; i++) {
				asm("nop");
			}
		}


		void init_descriptors_()
		{
    		descriptor_s* descriptor;

			/* Initialize the receive descriptors */
			for(int i = 0; i < EMAC_NUM_RX_DESCRIPTORS; i++) {
				descriptor = &(rx_descriptors_[i]);
				descriptor->buf_p = &(ether_buffers_.buffer[i][0]);
				descriptor->bufsize = EMAC_BUFSIZE;
				descriptor->size = 0;
				descriptor->status = RACT;
				descriptor->next = (descriptor_s *) &rx_descriptors_[i + 1];
			}

			/* The last descriptor points back to the start */
			descriptor->status |= RDLE;
			descriptor->next = &rx_descriptors_[0];

			/* Initialize application receive descriptor pointer */
			app_rx_desc_  = &(rx_descriptors_[0]);

			/* Initialize the transmit descriptors */
			for (int i = 0; i < EMAC_NUM_TX_DESCRIPTORS; i++) {
				descriptor = &(tx_descriptors_[i]);
				descriptor->buf_p = &(ether_buffers_.buffer[EMAC_NUM_RX_DESCRIPTORS + i][0]);
				descriptor->bufsize = 0;
				descriptor->size = EMAC_BUFSIZE;
				descriptor->status = 0;
				descriptor->next = &tx_descriptors_[i + 1];
			}

			/* The last descriptor points back to the start */
			descriptor->status |= TDLE;
			descriptor->next = &tx_descriptors_[0];

			/* Initialize application transmit descriptor pointer */
			app_tx_desc_  = &tx_descriptors_[0];
		}


		void config_ethernet_(const uint8_t mode)
		{
			/* Magic packet detecion mode */
			if (USE_MAGIC_PACKET_DETECT == mode) {
				ETHRC::ECSIPR = 0x00000006;
				EDMAC::EESIPR = 0x00400000;
			} else {  // Normal mode
				/* LINK Signal Change Interrupt Enable */
				ETHRC::ECSIPR.LCHNGIP = 1;
				EDMAC::EESIPR.ECIIP   = 1;

				// This is sample code.
				// Sets up interrupt when you use interrupts.
				// Enable interrupts of interest only.
				EDMAC::EESIPR.FRIP = 1;
				EDMAC::EESIPR.TCIP = 1;
	    	}

			// Ethernet length 1514bytes + CRC and intergap is 96-bit time
			ETHRC::RFLR = 1518;
			ETHRC::IPGR = 0x00000014;

			// Set little endian mode
    		EDMAC::EDMR.DE = 1;

			EDMAC::RDLAR = reinterpret_cast<uint32_t>(app_rx_desc_);
			EDMAC::TDLAR = reinterpret_cast<uint32_t>(app_tx_desc_);

			// Don't reflect the EESR.RMAF bit status in the RD0.RFS bit in the receive descriptor
			EDMAC::TRSCER = 0x00000080;
			// Threshold of Tx_FIFO
			// To prevent a transmit underflow, setting the initial value (store and forward modes)
			// is recommended.
			EDMAC::TFTR = 0x00000000;
			// transmit fifo & receive fifo is 2048 bytes
			EDMAC::FDR  = 0x00000707;
			/*  Configure receiving method
				b0      RNR - Receive Request Bit Reset - Continuous reception of multiple frames is possible.
				b1      RNC - Receive Request Bit Non-Reset Mode - The RR bit is automatically reset.
				b31:b2  Reserved set to 0
			 */
			EDMAC::RMCR  = 0x00000001;
		}


		void pause_resolution_(uint8_t local_ability, uint8_t partner_ability,
                              uint16_t& tx_pause, uint16_t& rx_pause)
		{
			// Arrange the bits so that they correspond to the Table 28B-3
			// of the IEEE 802.3 values.
			uint8_t ability_compare = ((local_ability & LINK_RES_ABILITY_MASK) << LINK_RES_LOCAL_ABILITY_BITSHIFT) | (partner_ability & LINK_RES_ABILITY_MASK);

			static const pause_resolution_t pause_resolution[PAUSE_TABLE_ENTRIES] = {
				{ pausemask_e::MASKC, pauseval_e::VAL0, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
				{ pausemask_e::MASKE, pauseval_e::VAL4, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
				{ pausemask_e::MASKF, pauseval_e::VAL6, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
				{ pausemask_e::MASKF, pauseval_e::VAL7, XMIT_PAUSE_ON,  RECV_PAUSE_OFF },
				{ pausemask_e::MASKE, pauseval_e::VAL8, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
				{ pausemask_e::MASKA, pauseval_e::VALA, XMIT_PAUSE_ON,  RECV_PAUSE_ON  },
				{ pausemask_e::MASKF, pauseval_e::VALC, XMIT_PAUSE_OFF, RECV_PAUSE_OFF },
				{ pausemask_e::MASKF, pauseval_e::VALD, XMIT_PAUSE_OFF, RECV_PAUSE_ON  }
			};
			// Walk through the look up table
			for(int i = 0; i < PAUSE_TABLE_ENTRIES; i++) {
				if((ability_compare & static_cast<uint8_t>(pause_resolution[i].mask))
				  == static_cast<uint8_t>(pause_resolution[i].value)) {
					tx_pause = pause_resolution[i].transmit;
					rx_pause = pause_resolution[i].receive;
					return;
				}
			}
		}


		int32_t do_link_(const uint8_t mode)
		{
    		int32_t ret = OK;

			// Set the link status
			uint16_t local_pause_bits   = 0;
			uint16_t partner_pause_bits = 0;
			bool full_duplex = false;
			uint16_t speed = 0;
			auto speed_duplex = phy_.get_autonegotiate(local_pause_bits, partner_pause_bits);
			switch(speed_duplex) {

			// Half duplex link
			case chip::phy_link_state::LINK_100H:
				ETHRC::ECMR.DM  = 0;
				ETHRC::ECMR.RTM = 1;
				ret = OK;
				utils::format("PHY Link 100Mbps / Half\n");
				break;

			case chip::phy_link_state::LINK_10H:
				ETHRC::ECMR.DM  = 0;
				ETHRC::ECMR.RTM = 0;
				ret = OK;
				utils::format("PHY Link 10Mbps / Half\n");
				break;

			/* Full duplex link */
			case chip::phy_link_state::LINK_100F:
				ETHRC::ECMR.DM  = 1;
				ETHRC::ECMR.RTM = 1;
				full_duplex = true;
				ret = OK;
				utils::format("PHY Link 100Mbps / Full\n");
				break;

			case chip::phy_link_state::LINK_10F:
				ETHRC::ECMR.DM  = 1;
				ETHRC::ECMR.RTM = 0;
				full_duplex = true;
				ret = OK;
				utils::format("PHY Link 10Mbps / Full\n");
				break;

			default:
				utils::format("PHY No Link\n");
				ret = ERROR;
				break;
			}

			/* At the communicate mode usually */
			if(NO_USE_MAGIC_PACKET_DETECT == mode) {
				/* When pause frame is used */
				if(full_duplex && pause_frame_enable_flag_) {
					/* Set automatic PAUSE for 512 bit-time */
					ETHRC::APR = 0x0000FFFF;
					/* Set unlimited retransmit of PAUSE frames */
					ETHRC::TPAUSER = 0;
					/* PAUSE flow control FIFO settings. */
					EDMAC::FCFTR = 0x00000000;
					/* Control of a PAUSE frame whose TIME parameter value is 0 is enabled. */
					ETHRC::ECMR.ZPF = 1;

					 // Enable PAUSE for full duplex link depending on
					 // the pause resolution results
					uint16_t transmit_pause_set = 0;
					uint16_t receive_pause_set  = 0;
					pause_resolution_(local_pause_bits, partner_pause_bits,
                                      transmit_pause_set, receive_pause_set);
			
					if (XMIT_PAUSE_ON == transmit_pause_set) {
						/* Enable automatic PAUSE frame transmission */
						ETHRC::ECMR.TXF = 1;
					} else {
						/* Disable automatic PAUSE frame transmission */
						ETHRC::ECMR.TXF = 0;
					}

					if (RECV_PAUSE_ON == receive_pause_set) {
						/* Enable reception of PAUSE frames */
						ETHRC::ECMR.RXF = 1;
					} else {
						/* Disable reception of PAUSE frames */
						ETHRC::ECMR.RXF = 0;
					}
				} else {
					// Disable PAUSE for half duplex link
					ETHRC::ECMR.TXF = 0;
					ETHRC::ECMR.RXF = 0;
				}

				/* Enable receive and transmit. */
				ETHRC::ECMR.RE = 1;
				ETHRC::ECMR.TE = 1;

				/* Enable EDMAC receive */
				EDMAC::EDRRR = 0x1;
			} else {
				// The magic packet detection is permitted.
				ETHRC::ECMR.MPDE = 1;
				// Because data is not transmitted for the magic packet detection waiting, 
				// only the reception is permitted.
				ETHRC::ECMR.RE = 1;

				// The reception function of EDMAC keep invalidity 
				// because the receive data don't need to be read when the magic packet detection mode.
			}
			return ret;
		}
		

		void configure_mac_(const uint8_t* mac_addr, const uint8_t mode)
		{
			// Software reset
			reset_mac_();

			// Set MAC address
			uint32_t mac_h = (static_cast<uint32_t>(mac_addr[0]) << 24) |
					         (static_cast<uint32_t>(mac_addr[1]) << 16) |
					         (static_cast<uint32_t>(mac_addr[2]) << 8 ) |
					         (static_cast<uint32_t>(mac_addr[3]));

			uint32_t mac_l = (static_cast<uint32_t>(mac_addr[4]) << 8) |
					         (static_cast<uint32_t>(mac_addr[5]));

			ETHRC::MAHR = mac_h;
			ETHRC::MALR = mac_l;

			/* Initialize receive and transmit descriptors */
			init_descriptors_();

			/* Perform rest of hardware interface configuration */
			config_ethernet_(mode);
		}


		// EDMA task
		static void dmac_task_() __attribute__ ((interrupt))
		{
			uint32_t status_ecsr = ETHRC::ECSR();
			uint32_t status_eesr = EDMAC::EESR();

			// When the ETHERC status interrupt is generated
			if(status_eesr & EMAC_ECI_INT) {
#if 0
				// If ET_LINKSTA is not connected, LINK status is decected by using software polling.
				// When the link signal change interrupt is generated
				if(status_ecsr & EMAC_LCHNG_INT) {
					// The state of the link signal is confirmed and Link Up/Down is judged.
					// When becoming Link up
					if(ETHERC::PSR.LMON() == LINK_PRESENT) {
						lchng_flag_ = FLAG_ON_LINK_ON;
					} else {  // When Link becomes down
						lchng_flag_ = FLAG_ON_LINK_OFF;
					}
				}
#endif
			// When the Magic Packet detection interrupt is generated
				if(status_ecsr & EMAC_MPD_INT) {
					mpd_flag_ = FLAG_ON;
				}
				// Because each bit of the ECSR register is cleared when one is written, 
				// the value read from the register is written and the bit is cleared. 

				// Clear all ETHERC status BFR, PSRTO, LCHNG, MPD, ICD
				ETHRC::ECSR = status_ecsr;
			}
			EDMAC::EESR = status_eesr;  // Clear EDMAC status bits

			intr_task_();

			// This is sample code
#if 0
			if(status_eesr & EMAC_RFCOF_INT) {
			}
			if(status_eesr & EMAC_TC_INT) {
			}
			if(status_eesr & EMAC_FR_INT) {
			}
			if(status_eesr & EMAC_RDE_INT) {
			}
			if(status_eesr & EMAC_RFOF_INT) {
			}
			// Because each bit of the EESR register is cleared when one is written, 
			// the value read from the register is written and the bit is cleared. 
			EDMAC::EESR.LONG = status_eesr;  // Clear EDMAC status bits
#endif
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ether_io() : intr_level_(0),
			mac_addr_{ 0 },
			pause_frame_enable_flag_(false),
			app_rx_desc_(nullptr), app_tx_desc_(nullptr),
			link_stat_(false)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  物理層クラスへの参照
			@return 物理層クラス
		*/
		//-----------------------------------------------------------------//
		PHY& at_phy() { return phy_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	割り込みクラスへの参照
			@return 割り込みクラス
		*/
		//-----------------------------------------------------------------//
		static INTR_TASK& at_task() { return intr_task_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	MAC アドレスの取得
			@return MAC アドレス
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get_mac() { return mac_addr_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コントローラーを有効にして起動
			@param[in]	level	割り込みレベル
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t level)
		{
			power_cfg::turn(ETHRC::get_peripheral());
			port_map::turn(ETHRC::get_peripheral());

			intr_level_ = level;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	After ETHERC, EDMAC, and PHY-LSI are reset in software, @n
					an auto negotiation of PHY-LSI is begun. @n
					Afterwards, the link signal change interrupt is permitted.
			@param[in]	mac_addr	MAC address 48 (6 bytes)
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool open(const uint8_t* mac_addr)
		{
			/* Initialize the flags */
			transfer_enable_flag_ = FLAG_OFF;
			mpd_flag_             = FLAG_OFF;
			lchng_flag_           = FLAG_OFF;

			mac_addr_[0] = mac_addr[0];
			mac_addr_[1] = mac_addr[1];
			mac_addr_[2] = mac_addr[2];
			mac_addr_[3] = mac_addr[3];
			mac_addr_[4] = mac_addr[4];
			mac_addr_[5] = mac_addr[5];

			// Software reset
    		reset_mac_();

			// Software reset the PHY
			bool phy_ret = phy_.init();
			if(phy_ret) {
				phy_.start_autonegotiate(pause_frame_enable_flag_);

				/* Clear all ETHERC status BFR, PSRTO, LCHNG, MPD, ICD */
				ETHRC::ECSR = 0x00000037;
				/* Clear all EDMAC status bits */
				EDMAC::EESR = 0x47FF0F9F;

				/* Enable interrupts of interest only. */
				ETHRC::ECSIPR.LCHNGIP = 1;
				EDMAC::EESIPR.ECIIP  = 1;

				// Set Ethernet interrupt level and enable
				ICU::IPR.GROUPAL1 = intr_level_;
				ICU::GENAL1.EN4   = 1;
				ICU::IER.GROUPAL1 = 1;
				set_interrupt_task(dmac_task_, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));
				return true;
			} else {
				return false;    
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Disables Ethernet peripheral
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool close()
		{
			// Disable Ethernet interrupt.
			ICU::GENAL1.EN4 = 0;
			ICU::IER.GROUPAL1 = 0;
			ICU::IPR.GROUPAL1 = 0;  // intr level

			// Disable TE and RE
			ETHRC::ECMR = 0x00000000;

			// Initialize the flags
			transfer_enable_flag_  = FLAG_OFF;
			mpd_flag_              = FLAG_OFF;
			lchng_flag_            = FLAG_OFF;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Receives an Ethernet frame.  Sets the passed @n
					buffer pointer to the Ethernet frame buffer @n
					from the driver. This makes the data available to @n
					the caller as a zero-copy operation.
			@param[in]	buf	pointer to the Ethernet driver buffer
			@return Number of bytes received (Value greater than zero) @n
					NO_DATA
					ERROR_LINK: The auto negotiation processing @n
						is not completed and sending and receiving is not permitted. 
					ERROR_MPDE: Doesn't receive the data to the receive buffer @n
						for the detection mode of magic packet. 
		*/
		//-----------------------------------------------------------------//
		int32_t get_read(void** buf)
		{
			int32_t num_recvd;
			int32_t ret;

			// When the Link up processing is not completed, return error
			if(FLAG_OFF == transfer_enable_flag_) {
				ret = ERROR_LINK;
			} else if(1 == ETHRC::ECMR.MPDE()) {  // In case of detection mode of magic packet, return error.
				ret = ERROR_MPDE;
			} else {  // When the Link up processing is completed
				while(1) {
					// When receive data exists.
					if(RACT != (app_rx_desc_->status & RACT)) {
						if(app_rx_desc_->status & RFE) {  // The buffer is released at the error.
							ret = read_buf_release();
						} else {
							// Pass the pointer to received data to application.  This is
							// zero-copy operation.
							*buf = app_rx_desc_->buf_p;

							// Get bytes received
							num_recvd = app_rx_desc_->size;
							ret = num_recvd;
							break;
						}
					} else {
						ret = NO_DATA;
						break;
					}
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Release the receive buffer.
			@return OK @n
					ERROR_LINK: The auto negotiation processing is not @n
								completed and sending and receiving is not permitted. @n
					ERROR_MPDE: Doesn't receive the data to the receive buffer @n
								for the detection mode of magic packet. 
		*/
		//-----------------------------------------------------------------//
		int32_t read_buf_release()
		{
    		int32_t ret;

			// When the Link up processing is not completed, return error
			if (FLAG_OFF == transfer_enable_flag_) {
				ret = ERROR_LINK;
			} else if (1 == ETHRC::ECMR.MPDE()) {  // In case of detection mode of magic packet, return error.
				ret = ERROR_MPDE;
			} else {  // When the Link up processing is completed
				if(RACT != (app_rx_desc_->status & RACT)) {  // When receive data exists
					// Move to next descriptor
					app_rx_desc_->status |= RACT;
					app_rx_desc_->status &= ~(RFP1 | RFP0 | RFE | RFS9_RFOVER | RFS8_RAD | RFS7_RMAF | \
                                     RFS4_RRF | RFS3_RTLF | RFS2_RTSF | RFS1_PRE | RFS0_CERF);
					app_rx_desc_ = app_rx_desc_->next;
				}
				if(0x00000000L == EDMAC::EDRRR()) {
					// Restart if stopped
					EDMAC::EDRRR = 0x00000001L;
				}
				ret = OK;
			}
    		return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Get Points to the buffer pointer used by the stack.
			@param[in]	buf			buffer pointer
			@param[in]	buf_size	buffer size
			@return OK @n
					ERROR_LINK: The auto negotiation processing is not @n
								completed and sending and receiving is not permitted. @n
					ERROR_MPDE: The transmission is not permitted because @n
								of the detection mode of magic packet. @n
        			ERROR_TACT: There is not becoming empty of the transmission buffer. 
		*/
		//-----------------------------------------------------------------//
		int32_t write_get_buf(void** buf, uint16_t& buf_size)
		{
			int32_t ret;
			// When the Link up processing is not completed, return error
			if (FLAG_OFF == transfer_enable_flag_) {
				ret = ERROR_LINK;
			} else if(1 == ETHRC::ECMR.MPDE()) {  // In case of detection mode of magic packet, return error.
				ret = ERROR_MPDE;
			} else {  // When the Link up processing is completed
				// All transmit buffers are full
				if(TACT == (app_tx_desc_->status & TACT)) {
					ret = ERROR_TACT;
				} else {
					/* Give application another buffer to work with */
					*buf = app_tx_desc_->buf_p;
					buf_size = app_tx_desc_->size;
					ret = OK;
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Transmits an Ethernet frame. @n
					The transmit descriptor points to the data to transmit. @n
					Data is sent directly from memory as a "zero copy" operation.
			@param[in]	len		length of data, in bytes, to transmit	
			@return OK @n
					ERROR_LINK: The auto negotiation processing is not @n
								completed and sending and receiving is not permitted. @n
					ERROR_MPDE: The transmission is not permitted because @n
								of the detection mode of magic packet.
		*/
		//-----------------------------------------------------------------//
		int32_t write_set_buf(uint32_t len)
		{
			int32_t ret;
			// When the Link up processing is not completed, return error
			if(FLAG_OFF == transfer_enable_flag_) {
				ret = ERROR_LINK;
			} else if(1 == ETHRC::ECMR.MPDE()) {  // In case of detection mode of magic packet, return error.
				ret = ERROR_MPDE;
			} else {  // When the Link up processing is completed
				// The data of the buffer is made active.
				app_tx_desc_->bufsize = len;
				app_tx_desc_->status &= ~(TFP1 | TFP0);
				app_tx_desc_->status |= (TFP1 | TFP0 | TACT);
				app_tx_desc_ = app_tx_desc_->next;

				if(0x00000000L == EDMAC::EDTRR()) {
					// Restart if stopped
					EDMAC::EDTRR = 0x00000001L;
				}
				ret = OK;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	read
			@param[out]	org	リード・ポインター
			@return 正の値なら読み込みバイト数、負ならエラー
		*/
		//-----------------------------------------------------------------//
		int32_t read(void** org)
		{
			int32_t ret;
			// H return_code;
			int32_t state = get_read(org);
			if(state > 0) {
				// t4_stat[lan_port_no].t4_rec_cnt++;
				// t4_stat[lan_port_no].t4_rec_byte += (UW)driver_ret;
				ret = state;
			} else if(state == 0) {
				// get_read() returns "0" when receiving data is nothing
				ret = state;
			} else {
				// R_Ether_Read() returns "negative values" when error occurred
				ret = -2; // Return code "-2" notifies "Ether controller disable" to T4.
//				return_code = -5; // Return code "-5" notifies "reset request" to T4.
//				return_code = -6; // Return code "-6" notifies "CRC error" to T4.
			}

#if defined (_T4_TEST)
		    ret = lan_read_for_test(lan_port_no, buf, return_code);
#endif
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	write
			@param[in]	head_org	ヘッダー
			@param[in]	head_len	ヘッダー長
			@param[in]	body_org	ボディー
			@param[in]	body_len	ボディー長
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool write(const void* head_org, uint16_t head_len, const void* body_org, uint16_t body_len)
		{
    		uint16_t len;
			void* ptr;
    		auto ret = write_get_buf(&ptr, len);
			if(ret == OK) {
				uint32_t all = head_len;
				all += body_len;
				if(static_cast<uint32_t>(len) >= all) {
					memcpy(ptr, head_org, head_len);
					uint8_t* p = static_cast<uint8_t*>(ptr);
					p += head_len;
					memcpy(p, body_org, body_len);

					ret = write_set_buf(all);
					if(ret == OK) {
//						t4_stat[lan_port_no].t4_snd_cnt++;
//						t4_stat[lan_port_no].t4_snd_byte += (head_len + body_len);
						return true;
					}
				}
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Verifies the Etherent link is up or not.
			@return Link is up: true, Link is down: false
		*/
		//-----------------------------------------------------------------//
		bool check_link()
		{
			return phy_.get_link_status();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	The Link up processing, the Link down processing, @n
					and the magic packet detection processing are executed. 
			@return リンク・アップなら「true」
		*/
		//-----------------------------------------------------------------//
		bool link_process()
		{
			// When the magic packet is detected.
			if(FLAG_ON == mpd_flag_) {
				mpd_flag_ = FLAG_OFF;
				callback_wake_on_lan();
			}

			// When the link is up
			bool f = false;
			if(FLAG_ON_LINK_ON == lchng_flag_) {
				f = true;
				lchng_flag_ = FLAG_OFF;

				// The Link Up/Down is confirmed by the Link Status bit of PHY register1, 
				// because the LINK signal of PHY-LSI is used for LED indicator, and 
				// isn't used for notifing the Link Up/Down to external device.
				auto ret = check_link();
				if(ret) {
					// ETHERC and EDMAC are set after ETHERC and EDMAC are reset in software
					// and sending and receiving is permitted. 
					configure_mac_(mac_addr_, NO_USE_MAGIC_PACKET_DETECT);
					do_link_(NO_USE_MAGIC_PACKET_DETECT);

					transfer_enable_flag_ = FLAG_ON;
					callback_link_on();
				} else {
					// no proccess
				}
			} else if(FLAG_ON_LINK_OFF == lchng_flag_) {  // When the link is down
				lchng_flag_ = FLAG_OFF;
				// The Link Up/Down is confirmed by the Link Status bit of PHY register1, 
				// because the LINK signal of PHY-LSI is used for LED indicator, and 
				// isn't used for notifing the Link Up/Down to external device.
				auto ret = check_link();
				if(ret) {
					// Disable receive and transmit.
					ETHRC::ECMR.RE = 0;
					ETHRC::ECMR.TE = 0;
            
					transfer_enable_flag_ = FLAG_OFF;
					callback_link_off();
				} else {
					// no proccess
				}
			} else {
				// no proccess
			}
			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	The setting of ETHERC is changed from a usual sending and @n
					receiving mode to the magic packet detection mode. 
			@return OK: ok @n
					ERROR: Became Link down while changing the setting. @n
					ERROR_LINK: The auto negotiation processing is not @n
								completed and sending and receiving is not permitted. 
		*/
		//-----------------------------------------------------------------//
		int32_t wake_on_lan()
		{
    		int32_t ret;
			// When the Link up processing is not completed, return error
			if(FLAG_OFF == transfer_enable_flag_) {
				ret = ERROR_LINK;
			} else {  // When the Link up processing is completed
				// Change to the magic packet detection mode.
				configure_mac_(mac_addr_, USE_MAGIC_PACKET_DETECT);
				auto ret = do_link_(USE_MAGIC_PACKET_DETECT);
				if(OK == ret) {
					// It is confirmed not to become Link down while changing the setting.
					if(LINK_PRESENT == ETHRC::PSR.LMON()) {
						ret = OK;
					} else {
						ret = ERROR;
					}
				} else {
					ret = ERROR;
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Callback function that notifies user to have become Link up.
		*/
		//-----------------------------------------------------------------//
		void callback_link_on()
		{
			utils::format("EtherC Link-ON (callback)\n");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Callback function that notifies user to have become Link down.
		*/
		//-----------------------------------------------------------------//
		void callback_link_off()
		{
			utils::format("EtherC Link-OFF (callback)\n");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	Callback function that notifies user to have detected magic packet.
		*/
		//-----------------------------------------------------------------//
		void callback_wake_on_lan()
		{
			utils::format("EtherC Wake On Lan (callback)\n");
			// Please add necessary processing when magic packet is detected.
			//
			// After the close function is called, the open function is called 
			// to have to set ETHERC to a usual operational mode
			// to usually communicate after magic packet is detected. 
			close();
			open(mac_addr_);

			// This code is for the sample program.
			magic_packet_detect_ = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ポーリングによるリンク・ステータスの更新
		*/
		//-----------------------------------------------------------------//
		void polling_link_status()
		{
			bool stat = phy_.get_link_status();
			if(link_stat_ != stat) {
				if(stat) {
					lchng_flag_ = FLAG_ON_LINK_ON;
				} else {
					lchng_flag_ = FLAG_ON_LINK_OFF;
				}
				link_stat_ = stat;
			}
		}
	};

	template <class ETHRC, class EDMAC, class PHY, class INTR_TASK>
		volatile uint8_t ether_io<ETHRC, EDMAC, PHY, INTR_TASK>::mpd_flag_;

	template <class ETHRC, class EDMAC, class PHY, class INTR_TASK>
		INTR_TASK ether_io<ETHRC, EDMAC, PHY, INTR_TASK>::intr_task_;
}
