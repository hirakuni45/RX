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

#ifdef BIG_ENDIAN
#elif LITTLE_ENDIAN
#else
#error "ether_io.hpp requires BIG_ENDIAN or LITTLE_ENDIAN be defined."
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  stat_t クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ether_stat_t {

		enum class error_type {
			LEN,
			NETWORK_LAYER,
			TRANSPORT_LAYER,
			ARP_HEADER1,
			ARP_HEADER2,
			IP_HEADER1,
			IP_HEADER2,
			IP_HEADER3,
			IP_HEADER4,
			IP_HEADER5,
			IP_HEADER6,
			IP_HEADER7,
			IP_HEADER8,
			IP_HEADER9,
			TCP_HEADER1,
			TCP_HEADER2,
			UDP_HEADER1,
			UDP_HEADER2,
			UDP_HEADER3,
			ICMP_HEADER1,

			none,
			num_
		};

		uint32_t	recv_request_;
		uint32_t	recv_bytes_;
		uint32_t	send_request_;
		uint32_t	send_bytes_;

		uint32_t	count_[static_cast<int>(error_type::num_)];


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ether_stat_t() :
			recv_request_(0), recv_bytes_(0), send_request_(0), send_bytes_(0),
			count_{ 0 } { }


		//-----------------------------------------------------------------//
		/*!
			@brief  リセット（変数初期化）
		*/
		//-----------------------------------------------------------------//
		void reset() {
			recv_request_ = 0;
			recv_bytes_   = 0;
			send_request_ = 0;
			send_bytes_   = 0;
			for(int i = 0; i < static_cast<int>(error_type::num_); ++i) {
				count_[i] = 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  エラー・カウントを進める
			@param[in]	t	エラー・タイプ
		*/
		//-----------------------------------------------------------------//
		void inc_error_count(error_type t) {
			++count_[static_cast<int>(t)];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  エラー・カウントを取得
			@return エラー・カウント
		*/
		//-----------------------------------------------------------------//
		uint32_t get_error_count(error_type t) const {
			return count_[static_cast<int>(t)];
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Ethernet I/O 制御クラス
		@param[in]	ETHRC	インサーネット・コントローラー
		@param[in]	EDMAC	インサーネットＤＭＡコントローラー
		@param[in]	PHY		物理層コントローラー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHRC, class EDMAC, class PHY>
	class ether_io {

		static const int EMAC_BUFSIZE = 1536;  			// Must be 32-byte aligned
		static const int EMAC_NUM_RX_DESCRIPTORS = 4;	// The number of RX descriptors.
		static const int EMAC_NUM_TX_DESCRIPTORS = 4;	// The number of TX descriptors.

	private:
		// Bit definitions of status member of DescriptorS
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

		enum class magic_packet_mode : uint8_t {
			no_use,
			use,
		};

	public:
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

		 // Please define the level of the LINKSTA signal when Link becomes up.
		static const int LINK_PRESENT    = 0;
		// Please define the level of the LINKSTA signal when Link becomes down.
		static const int LINK_NOTPRESENT = 1;

		struct descriptor_s {
    		uint32_t	status;
#ifdef LITTLE_ENDIAN
			uint16_t	size;
			uint16_t	bufsize;
#else
			uint16_t	bufsize;
			uint16_t	size;
#endif
			volatile void*	buf_p;
			volatile descriptor_s*	next;
		};

		struct etherbuffer_s {
			uint8_t  buffer[EMAC_NUM_RX_DESCRIPTORS + EMAC_NUM_TX_DESCRIPTORS][EMAC_BUFSIZE];
		};

	private:
		// アライメントを使う場合、注意
		volatile descriptor_s rx_descriptors_[EMAC_NUM_RX_DESCRIPTORS] __attribute__ ((aligned(32)));
		volatile descriptor_s tx_descriptors_[EMAC_NUM_TX_DESCRIPTORS] __attribute__ ((aligned(32)));
		volatile etherbuffer_s ether_buffers_ __attribute__ ((aligned(32)));
		volatile descriptor_s* app_rx_desc_;
		volatile descriptor_s* app_tx_desc_;

		static volatile uint8_t	mpd_flag_;
		static volatile void*	intr_task_;

		PHY		phy_;

		uint8_t	intr_level_;

		uint8_t	mac_addr_[6];

		volatile bool					pause_frame_enable_flag_;
		volatile magic_packet_mode		magic_packet_detect_;
		volatile uint8_t				lchng_flag_;
		volatile uint8_t				transfer_enable_flag_;

		bool			link_stat_;

		ether_stat_t	stat_;

		const uint8_t*	recv_ptr_;
		uint32_t		recv_mod_;

		const void*		err_data_;

		void reset_mac_() {
			// Software reset
			EDMAC::EDMR.SWR = 1;

			// Delay
			// Waiting time until the initialization of ETHERC and EDMAC is completed is 64 cycles
			// in the clock conversion of an internal bus of EDMAC. 
			for(int i = 0; i < 0x00000100; i++) {
				asm("nop");
			}
		}


		void init_descriptors_()
		{
			volatile descriptor_s* descriptor;

			// Initialize the receive descriptors
			for(int i = 0; i < EMAC_NUM_RX_DESCRIPTORS; i++) {
				descriptor = &rx_descriptors_[i];
				descriptor->buf_p = &ether_buffers_.buffer[i][0];
				descriptor->bufsize = EMAC_BUFSIZE;
				descriptor->size = 0;
				descriptor->status = RACT;
				descriptor->next = &rx_descriptors_[i + 1];
			}

			// The last descriptor points back to the start
			descriptor->status |= RDLE;
			descriptor->next = &rx_descriptors_[0];

			// Initialize application receive descriptor pointer
			app_rx_desc_ = &rx_descriptors_[0];

			// Initialize the transmit descriptors
			for(int i = 0; i < EMAC_NUM_TX_DESCRIPTORS; i++) {
				descriptor = &tx_descriptors_[i];
				descriptor->buf_p = &ether_buffers_.buffer[EMAC_NUM_RX_DESCRIPTORS + i][0];
				descriptor->bufsize = 0;
				descriptor->size = EMAC_BUFSIZE;
				descriptor->status = 0;
				descriptor->next = &tx_descriptors_[i + 1];
			}

			// The last descriptor points back to the start
			descriptor->status |= TDLE;
			descriptor->next = &tx_descriptors_[0];

			// Initialize application transmit descriptor pointer
			app_tx_desc_ = &tx_descriptors_[0];
		}


		void config_ethernet_(magic_packet_mode mode)
		{
			// Magic packet detecion mode
			if(mode == magic_packet_mode::use) {
				ETHRC::ECSIPR = 0x00000006;
				EDMAC::EESIPR = 0x00400000;
			} else {  // Normal mode
				// LINK Signal Change Interrupt Enable
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

			uint32_t rxa = reinterpret_cast<uint32_t>(app_rx_desc_);
			if(rxa & 0x1f) {  // 32 bytes aligned test
				utils::format("Alignd error: Ether RX adr: %08X\n") % rxa;
			}
			uint32_t txa = reinterpret_cast<uint32_t>(app_tx_desc_);
			if(txa & 0x1f) {  // 32 bytes aligned test
				utils::format("Alignd error: Ether TX adr: %08X\n") % txa;
			}
			EDMAC::RDLAR = rxa;
			EDMAC::TDLAR = txa;

//			utils::format("Ether RX adr: %08X\n") % EDMAC::RDLAR();
//			utils::format("Ether TX adr: %08X\n") % EDMAC::TDLAR();

			// Don't reflect the EESR.RMAF bit status in the RD0.RFS bit in the receive descriptor
			EDMAC::TRSCER = 0x00000080;
			// Threshold of Tx_FIFO
			// To prevent a transmit underflow, setting the initial value (store and forward modes)
			// is recommended.
			EDMAC::TFTR = 0x00000000;
			// transmit fifo & receive fifo is 2048 bytes
			EDMAC::FDR  = 0x00000707;
			// Configure receiving method
			// b0      RNR - Receive Request Bit Reset - Continuous reception of multiple frames is possible.
			// b1      RNC - Receive Request Bit Non-Reset Mode - The RR bit is automatically reset.
			// b31:b2  Reserved set to 0
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
			for(int i = 0; i < PAUSE_TABLE_ENTRIES; ++i) {
				if((ability_compare & static_cast<uint8_t>(pause_resolution[i].mask))
				  == static_cast<uint8_t>(pause_resolution[i].value)) {
					tx_pause = pause_resolution[i].transmit;
					rx_pause = pause_resolution[i].receive;
					return;
				}
			}
		}


		int32_t do_link_(magic_packet_mode mode)
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

			// Full duplex link
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

			// At the communicate mode usually
			if(mode == magic_packet_mode::no_use) {
				// When pause frame is used
				if(full_duplex && pause_frame_enable_flag_) {
					// Set automatic PAUSE for 512 bit-time
					ETHRC::APR = 0x0000FFFF;
					// Set unlimited retransmit of PAUSE frames
					ETHRC::TPAUSER = 0;
					// PAUSE flow control FIFO settings.
					EDMAC::FCFTR = 0x00000000;
					// Control of a PAUSE frame whose TIME parameter value is 0 is enabled.
					ETHRC::ECMR.ZPF = 1;

					 // Enable PAUSE for full duplex link depending on
					 // the pause resolution results
					uint16_t transmit_pause_set = 0;
					uint16_t receive_pause_set  = 0;
					pause_resolution_(local_pause_bits, partner_pause_bits,
                                      transmit_pause_set, receive_pause_set);
			
					if(XMIT_PAUSE_ON == transmit_pause_set) {
						// Enable automatic PAUSE frame transmission
						ETHRC::ECMR.TXF = 1;
					} else {
						// Disable automatic PAUSE frame transmission
						ETHRC::ECMR.TXF = 0;
					}

					if(RECV_PAUSE_ON == receive_pause_set) {
						// Enable reception of PAUSE frames
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

				// Enable receive and transmit.
				ETHRC::ECMR.RE = 1;
				ETHRC::ECMR.TE = 1;

				// Enable EDMAC receive
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
		

		void configure_mac_(const uint8_t* mac_addr, magic_packet_mode mode)
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

			// Initialize receive and transmit descriptors
			init_descriptors_();

			// Perform rest of hardware interface configuration
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

			if(intr_task_ != nullptr) {
				void (*task)() = reinterpret_cast<void(*)()>(intr_task_);
				task();
			}

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
		ether_io() :
			app_rx_desc_(nullptr), app_tx_desc_(nullptr),
			intr_level_(0), mac_addr_{ 0 },
			pause_frame_enable_flag_(false), magic_packet_detect_(magic_packet_mode::no_use),
			lchng_flag_(FLAG_OFF), transfer_enable_flag_(FLAG_OFF),
			link_stat_(false), stat_(), recv_ptr_(nullptr), recv_mod_(0), err_data_(nullptr)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みタスクを設定（EDMAC)
			@param[in]	task	割り込みタスク
		*/
		//-----------------------------------------------------------------//
		static void set_intr_task(void (*task)(void)) {
			intr_task_ = reinterpret_cast<volatile void*>(task);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  物理層クラスへの参照
			@return 物理層クラス
		*/
		//-----------------------------------------------------------------//
		PHY& at_phy() { return phy_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	MAC アドレスの取得
			@return MAC アドレス
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get_mac() const { return mac_addr_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	状態の取得
			@return ether_stat_t の参照
		*/
		//-----------------------------------------------------------------//
		const ether_stat_t& get_stat() const { return stat_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コントローラーを有効にしてスタート
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
			@brief	インサーネット・ドライバーをオープン
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

				stat_.reset();

				recv_ptr_ = nullptr;
				recv_mod_ = 0;

				return true;
			} else {
				return false;    
			}
		}


		int32_t recv_buff_release()
		{
    		int32_t ret;

			// When the Link up processing is not completed, return error
			if(FLAG_OFF == transfer_enable_flag_) {
				ret = ERROR_LINK;
			} else if(1 == ETHRC::ECMR.MPDE()) {  // In case of detection mode of magic packet, return error.
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


		int32_t recv(void** buf)
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
							ret = recv_buff_release();
						} else {
							// Pass the pointer to received data to application.  This is
							// zero-copy operation.
							*buf = (void*)app_rx_desc_->buf_p;

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


		int32_t send_buff(void** buf, uint16_t& buf_size)
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
					// Give application another buffer to work with
					*buf = (void*)app_tx_desc_->buf_p;
					buf_size = app_tx_desc_->size;
					ret = OK;
				}
			}
			return ret;
		}


		int32_t send(uint32_t len)
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
			@brief	リード・データ
			@param[in]	dst	転送先
			@param[in]	len	リード長
			@return リード数
		*/
		//-----------------------------------------------------------------//
		uint32_t read(void* dst, uint32_t len)
		{
			uint32_t ret = 0;

			// バッファー残がある。
			if(recv_ptr_ != nullptr && recv_mod_ > 0) {
				if(len >= recv_mod_) {
					ret = recv_mod_;
					memcpy(dst, recv_ptr_, recv_mod_);
					recv_ptr_ = nullptr;
					recv_mod_ = 0;
					recv_buff_release();
					return ret;
				} else {
					memcpy(dst, recv_ptr_, len);
					recv_ptr_ += len;
					recv_mod_ -= len;
   					return len;
				}
			}

			void* ptr;
			auto l = recv(&ptr);
			if(l > 0) {
				if(l > static_cast<int32_t>(len)) {
					l -= len;
					recv_mod_ = l;
					recv_ptr_ = static_cast<const uint8_t*>(ptr);
					l = len;
					recv_ptr_ += l;
				}
				stat_.recv_request_++;
				stat_.recv_bytes_ += l;
				ret = l;
				memcpy(dst, ptr, l);
				if(recv_ptr_ == nullptr) {
					recv_buff_release();
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・データ
			@param[in]	hsrc	ヘッダー転送元
			@param[in]	hlen	ヘッダー長さ
			@param[in]	bsrc	ボディー転送元
			@param[in]	blen	ボディー長さ
			@return ライト数
		*/
		//-----------------------------------------------------------------//
		uint32_t write(const void* hsrc, uint32_t hlen, const void* bsrc, uint32_t blen)
		{
			void* buf;
			uint16_t buf_size;
			int32_t ret = send_buff(&buf, buf_size);
			if(OK == ret) {
				if(buf_size >= (hlen + blen)) {
					memcpy(buf, hsrc, hlen);
					memcpy(static_cast<uint8_t*>(buf) + hlen, bsrc, blen);
					ret =  send(hlen + blen);
					if(OK == ret) {
						stat_.send_request_++;
						stat_.send_bytes_ += hlen + blen;
						return 0;
					}
				}
			}
			return -5;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・データ
			@param[in]	src	転送元
			@param[in]	len	長さ
			@return ライト数
		*/
		//-----------------------------------------------------------------//
		uint32_t write(const void* src, uint32_t len)
		{
			void* ptr;
			uint16_t maxlen;
			uint32_t ret = 0;
    		if(send_buff(&ptr, maxlen) == OK) {
				if(len > maxlen) {
					memcpy(ptr, src, maxlen);
					ret = maxlen;
				} else {
					memcpy(ptr, src, len);
					ret = len;
				}
				if(send(ret) == OK) {
					stat_.send_request_++;
					stat_.send_bytes_ += ret;
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	インサーネット・ドライバーをクローズ
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
					configure_mac_(mac_addr_, magic_packet_mode::no_use);
					do_link_(magic_packet_mode::no_use);

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
				configure_mac_(mac_addr_, magic_packet_mode::use);
				auto ret = do_link_(magic_packet_mode::use);
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
			magic_packet_detect_ = magic_packet_mode::use;
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


		//-----------------------------------------------------------------//
		/*!
			@brief	レポート・エラー
			@param[in]	err_code	エラー・コード
			@param[in]	err_data	エラー・データ
		*/
		//-----------------------------------------------------------------//
		void report_error(ether_stat_t::error_type err_code, const void* err_data)
		{
			err_data_ = err_data;
			stat_.inc_error_count(err_code);
		}
	};

	template <class ETHRC, class EDMAC, class PHY>
		volatile uint8_t ether_io<ETHRC, EDMAC, PHY>::mpd_flag_;

	template <class ETHRC, class EDMAC, class PHY>
		volatile void* ether_io<ETHRC, EDMAC, PHY>::intr_task_;

}
