#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・MTU3x 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mtu_base_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  TYPE 型（全体の種別なので、チャネルとは異なる）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TYPE : uint8_t {
			MTU2,	///< MTU2:  RX621 / RX62N
			MTU3,	///< MTU3:  RX63T
			MTU3a,	///< MTU3a: RX64M / RX71M / RX651 / RX65N / RX671 / RX72N / RX72M
			MTU3d,	///< MTU3d: RX24T / RX26T / RX66T / RX72T
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロック分周器型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CLOCK_DIVIDER : uint8_t {
			MTU2,		///< MTU2 標準型 (1/1, 1/4, 1/16, 1/64)
			MTU2_EXT1,	///< MTU2 拡張型１(1/1, 1/4, 1/16, 1/64, 1/256) 
			MTU2_EXT2,	///< MTU2 拡張型１(1/1, 1/4, 1/16, 1/64, 1/1024)
			MTU2_EXT3,	///< MTU2 拡張型１(1/1, 1/4, 1/16, 1/64, 1/256, 1/1024)  
			MTU3,		///< MTU3 型 (1/1, 1/2, 1/4, 1/8, 1/16, 1/32, 1/64, 1/256, 1/1024)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CLOCK_SOURCE : uint8_t {
			PCLK,

			MTIOCA,
			MTIOCB,

			MTCLKA,
			MTCLKB,
			MTCLKC,
			MTCLKD
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル変換 AB
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename CH>
		static auto conv_port_map_channel_ab(CH ch)
		{
			auto ret = port_map_mtu::CHANNEL::NONE;
			switch(ch) {
			case CH::A:
				ret = port_map_mtu::CHANNEL::A;
				break;
			case CH::B:
				ret = port_map_mtu::CHANNEL::B;
				break;
			default:
				break;
			}
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル変換 ABCD
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename CH>
		static auto conv_port_map_channel_abcd(CH ch)
		{
			auto ret = port_map_mtu::CHANNEL::NONE;
			switch(ch) {
			case CH::A:
				ret = port_map_mtu::CHANNEL::A;
				break;
			case CH::B:
				ret = port_map_mtu::CHANNEL::B;
				break;
			case CH::C:
				ret = port_map_mtu::CHANNEL::C;
				break;
			case CH::D:
				ret = port_map_mtu::CHANNEL::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC;
			bits_rw_t<io_, bitpos::B3, 2> CKEG;
			bits_rw_t<io_, bitpos::B5, 3> CCLR;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC2;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2x）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr2x_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC2;
			bits_rw_t<io_, bitpos::B3, 2> PCB;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1x）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr1x_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MD;
			bit_rw_t <io_, bitpos::B4>    BFA;
			bit_rw_t <io_, bitpos::B5>    BFB;
			bit_rw_t <io_, bitpos::B6>    BFE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1y）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr1y_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MD;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1z）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr1z_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MD;
			bit_rw_t <io_, bitpos::B4>    BFA;
			bit_rw_t <io_, bitpos::B5>    BFB;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2A, TMDR2B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  DRS;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2A）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr2_t<0x000C'1270> TMDR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2B）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr2_t<0x000C'1A70> TMDR2B;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiorh_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IOA;
			bits_rw_t<io_, bitpos::B4, 4> IOB;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiorl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IOC;
			bits_rw_t<io_, bitpos::B4, 4> IOD;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR_ab_t）
			@param[in]	TIORH	TIORH クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TIORH, typename CH>
		struct tior_ab_t {

			typedef rw8_t<TIORH::address> ioh_;
			bits_rw_t<ioh_, bitpos::B0, 4> IOA;
			bits_rw_t<ioh_, bitpos::B4, 4> IOB;


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR 全てのチャネルを無効
			*/
			//-------------------------------------------------------------//
			void disable()
			{
				IOA = 0;
				IOB = 0;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(CH ch, uint8_t val)
			{
				switch(ch) {
				case CH::A:
					IOA = val;
					break;
				case CH::B:
					IOB = val;
					break;
				default:
					return false;
				}
				return true;
			}

			bool operator[] (CH ch) { return set(ch); }


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(CH ch)
			{
				switch(ch) {
				case CH::A:
					return IOA();
				case CH::B:
					return IOB();
				default:
					return 0x00;
				}
			}

			uint8_t operator() (CH ch) { return get(ch); }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR_abcd_t）
			@param[in]	TIORH	TIORH クラス
			@param[in]	TIORL	TIORL クラス
			@param[in]	CH		チャネル型
			@param[in]	PER		ペリフェラル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TIORH, class TIORL, typename CH, peripheral PER>
		struct tior_abcd_t {

			typedef rw8_t<TIORH::address> ioh_;
			bits_rw_t<ioh_, bitpos::B0, 4> IOA;
			bits_rw_t<ioh_, bitpos::B4, 4> IOB;

			typedef rw8_t<TIORL::address> iol_;
			bits_rw_t<iol_, bitpos::B0, 4> IOC;
			bits_rw_t<iol_, bitpos::B4, 4> IOD;

			typedef rw8_t<0x000C'120A> io3_;
			bit_rw_t<io3_, bitpos::B0> OE3B;
			bit_rw_t<io3_, bitpos::B1> OE4A;
			bit_rw_t<io3_, bitpos::B2> OE4B;
			bit_rw_t<io3_, bitpos::B3> OE3D;
			bit_rw_t<io3_, bitpos::B4> OE4C;
			bit_rw_t<io3_, bitpos::B5> OE4D;

			typedef rw8_t<0x000C'1A0A> io4_;
			bit_rw_t<io4_, bitpos::B0> OE6B;
			bit_rw_t<io4_, bitpos::B1> OE7A;
			bit_rw_t<io4_, bitpos::B2> OE7B;
			bit_rw_t<io4_, bitpos::B3> OE6D;
			bit_rw_t<io4_, bitpos::B4> OE7C;
			bit_rw_t<io4_, bitpos::B5> OE7D;


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR 全てのチャネルを無効
			*/
			//-------------------------------------------------------------//
			void disable()
			{
				IOA = 0;
				IOB = 0;
				IOC = 0;
				IOD = 0;
				switch(PER) {
				case peripheral::MTU3:
					OE3B = 0;
					OE3D = 0;
					break;
				case peripheral::MTU4:
					OE4A = 0;
					OE4B = 0;
					OE4C = 0;
					OE4D = 0;
					break;
				case peripheral::MTU6:
					OE6B = 0;
					OE6D = 0;
					break;
				case peripheral::MTU7:
					OE7A = 0;
					OE7B = 0;
					OE7C = 0;
					OE7D = 0;
					break;
				default:
					break;
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(CH ch, uint8_t val)
			{
				switch(ch) {
				case CH::A:
					switch(PER) {
					case peripheral::MTU4:
						OE4A = val != 0;
						break;
					case peripheral::MTU7:
						OE7A = val != 0;
						break;
					default:
						break;
					}
					IOA = val;
					break;
				case CH::B:
					switch(PER) {
					case peripheral::MTU3:
						OE3B = val != 0;
						break;
					case peripheral::MTU4:
						OE4B = val != 0;
						break;
					case peripheral::MTU6:
						OE6B = val != 0;
						break;
					case peripheral::MTU7:
						OE7B = val != 0;
						break;
					default:
						break;
					}
					IOB = val;
					break;
				case CH::C:
					switch(PER) {
					case peripheral::MTU4:
						OE4C = val != 0;
						break;
					case peripheral::MTU7:
						OE7C = val != 0;
						break;
					default:
						break;
					}
					IOC = val;
					break;
				case CH::D:
					switch(PER) {
					case peripheral::MTU3:
						OE3D = val != 0;
						break;
					case peripheral::MTU4:
						OE4D = val != 0;
						break;
					case peripheral::MTU6:
						OE6D = val != 0;
						break;
					case peripheral::MTU7:
						OE7D = val != 0;
						break;
					default:
						break;
					}
					IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}

			bool operator[] (CH ch) { return set(ch); }


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(CH ch)
			{
				switch(ch) {
				case CH::A:
					return IOA();
				case CH::B:
					return IOB();
				case CH::C:
					return IOC();
				case CH::D:
					return IOD();
				default:
					return 0x00;
				}
			}

			uint8_t operator() (CH ch) { return get(ch); }
		};



		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIERx）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tierx_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;

			bit_rw_t<io_, bitpos::B4> TCIEV;
			bit_rw_t<io_, bitpos::B5> TCIEU;

			bit_rw_t<io_, bitpos::B7> TTGE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIERy）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiery_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;
			bit_rw_t<io_, bitpos::B2> TGIEC;
			bit_rw_t<io_, bitpos::B3> TGIED;
			bit_rw_t<io_, bitpos::B4> TCIEV;

			bit_rw_t<io_, bitpos::B7> TTGE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIERz）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tierz_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;
			bit_rw_t<io_, bitpos::B2> TGIEC;
			bit_rw_t<io_, bitpos::B3> TGIED;
			bit_rw_t<io_, bitpos::B4> TCIEV;

			bit_rw_t<io_, bitpos::B6> TTGE2;
			bit_rw_t<io_, bitpos::B7> TTGE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIER8）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tier8_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;
			bit_rw_t<io_, bitpos::B2> TGIEC;
			bit_rw_t<io_, bitpos::B3> TGIED;
			bit_rw_t<io_, bitpos::B4> TCIEV;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIER2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tier2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEE;
			bit_rw_t<io_, bitpos::B1> TGIEF;

			bit_rw_t<io_, bitpos::B7> TTGE2;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマジェネラルレジスタ（TGR16）
			@param[in]	TGRA	TGRA クラス
			@param[in]	TGRB	TGRB クラス
			@param[in]	TGRC	TGRC クラス
			@param[in]	TGRD	TGRD クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRA, class TGRB, class TGRC, class TGRD, typename CH>
		struct tgr16_abcd_t {

			static uint32_t address(CH ch)
			{
				switch(ch) {
				case CH::A: return TGRA::address;
				case CH::B: return TGRB::address;
				case CH::C: return TGRC::address;
				case CH::D: return TGRD::address;
				}
				return 0;
			}

			uint16_t operator () (CH ch) {
				return device::rd16_(address(ch));
			}

			uint16_t& operator [] (CH ch) {
				return *reinterpret_cast<uint16_t*>(address(ch));
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマジェネラルレジスタ（TGR16）
			@param[in]	TGRA	TGRA クラス
			@param[in]	TGRB	TGRB クラス
			@param[in]	TGRC	TGRC クラス
			@param[in]	TGRD	TGRD クラス
			@param[in]	TGRE	TGRE クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRA, class TGRB, class TGRC, class TGRD, class TGRE, typename CH>
		struct tgr16_abcde_t {

			static uint32_t address(CH ch)
			{
				switch(ch) {
				case CH::A: return TGRA::address;
				case CH::B: return TGRB::address;
				case CH::C: return TGRC::address;
				case CH::D: return TGRD::address;
				case CH::E: return TGRE::address;
				}
				return 0;
			}

			uint16_t operator () (CH ch) {
				return device::rd16_(address(ch));
			}

			uint16_t& operator [] (CH ch) {
				return *reinterpret_cast<uint16_t*>(address(ch));
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマジェネラルレジスタ（TGR16）
			@param[in]	TGRA	TGRA クラス
			@param[in]	TGRB	TGRB クラス
			@param[in]	TGRC	TGRC クラス
			@param[in]	TGRD	TGRD クラス
			@param[in]	TGRE	TGRE クラス
			@param[in]	TGRF	TGRF クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRA, class TGRB, class TGRC, class TGRD, class TGRE, class TGRF, typename CH>
		struct tgr16_abcdef_t {

			static uint32_t address(CH ch)
			{
				switch(ch) {
				case CH::A: return TGRA::address;
				case CH::B: return TGRB::address;
				case CH::C: return TGRC::address;
				case CH::D: return TGRD::address;
				case CH::E: return TGRE::address;
				case CH::F: return TGRF::address;
				}
				return 0;
			}

			uint16_t operator () (CH ch) {
				return device::rd16_(address(ch));
			}

			uint16_t& operator [] (CH ch) {
				return *reinterpret_cast<uint16_t*>(address(ch));
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマジェネラルレジスタ（TGR16）
			@param[in]	TGRA	TGRA クラス
			@param[in]	TGRB	TGRB クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRA, class TGRB, typename CH>
		struct tgr16_ab_t {

			static uint32_t address(CH ch)
			{
				switch(ch) {
				case CH::A: return TGRA::address;
				case CH::B: return TGRB::address;
				}
				return 0;
			}

			uint16_t operator () (CH ch) {
				return device::rd16_(address(ch));
			}

			uint16_t& operator [] (CH ch) {
				return *reinterpret_cast<uint16_t*>(address(ch));
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマジェネラルレジスタ（TGR32）
			@param[in]	TGRA	TGRA クラス
			@param[in]	TGRB	TGRB クラス
			@param[in]	TGRC	TGRC クラス
			@param[in]	TGRD	TGRD クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRA, class TGRB, class TGRC, class TGRD, typename CH>
		struct tgr32_abcd_t {

			static uint32_t address(CH ch)
			{
				switch(ch) {
				case CH::A: return TGRA::address;
				case CH::B: return TGRB::address;
				case CH::C: return TGRC::address;
				case CH::D: return TGRD::address;
				}
				return 0;
			}

			uint32_t operator () (CH ch) {
				return device::rd32_(address(ch));
			}

			uint32_t& operator [] (CH ch) {
				return *reinterpret_cast<uint32_t*>(address(ch));
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマステータスレジスタ（TSR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7> TCFD;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマバッファ動作転送モードレジスタ（TBTMx）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbtmx_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TTSA;
			bit_rw_t<io_, bitpos::B1> TTSB;
			bit_rw_t<io_, bitpos::B2> TTSE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマバッファ動作転送モードレジスタ（TBTMy）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbtmy_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TTSA;
			bit_rw_t<io_, bitpos::B1> TTSB;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstra_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CST0;
			bit_rw_t<io_, bitpos::B1> CST1;
			bit_rw_t<io_, bitpos::B2> CST2;
			bit_rw_t<io_, bitpos::B3> CST8;
			bit_rw_t<io_, bitpos::B4> CST9;

			bit_rw_t<io_, bitpos::B6> CST3;
			bit_rw_t<io_, bitpos::B7> CST4;
		};
		static inline tstra_t<0x000C'1280> TSTRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstrb_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> CST6;
			bit_rw_t<io_, bitpos::B7> CST7;
		};
		static inline tstrb_t<0x000C'1A80> TSTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CSW5;
			bit_rw_t<io_, bitpos::B1> CSV5;
			bit_rw_t<io_, bitpos::B2> CSU5;
		};
		static inline tstr_t<0x000C'1CB4> TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tsyra_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SYNC0;
			bit_rw_t<io_, bitpos::B1> SYNC1;
			bit_rw_t<io_, bitpos::B2> SYNC2;
			bit_rw_t<io_, bitpos::B3> SYNC9;

			bit_rw_t<io_, bitpos::B6> SYNC3;
			bit_rw_t<io_, bitpos::B7> SYNC4;
		};
		static inline tsyra_t<0x000C'1281> TSYRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tsyrb_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> SYNC6;
			bit_rw_t<io_, bitpos::B7> SYNC7;
		};
		static inline tsyrb_t<0x000C'1A81> TSYRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマカウンタシンクロスタートレジスタ（TCSYSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tcsystr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SCH7;
			bit_rw_t<io_, bitpos::B1> SCH6;
			bit_rw_t<io_, bitpos::B2> SCH9;
			bit_rw_t<io_, bitpos::B3> SCH4;
			bit_rw_t<io_, bitpos::B4> SCH3;
			bit_rw_t<io_, bitpos::B5> SCH2;
			bit_rw_t<io_, bitpos::B6> SCH1;
			bit_rw_t<io_, bitpos::B7> SCH0;
		};
		static inline tcsystr_t<0x000C'1282> TCSYSTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWER）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct trwer_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RWE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWERA）
		*/
		//-----------------------------------------------------------------//
		static inline trwer_t<0x000C'1284> TRWERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWERB）
		*/
		//-----------------------------------------------------------------//
		static inline trwer_t<0x000C'1A84> TRWERB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットマスタイネーブルレジスタ（TOERA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct toera_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OE3B;
			bit_rw_t<io_, bitpos::B1> OE4A;
			bit_rw_t<io_, bitpos::B2> OE4B;
			bit_rw_t<io_, bitpos::B3> OE3D;
			bit_rw_t<io_, bitpos::B4> OE4C;
			bit_rw_t<io_, bitpos::B5> OE4D;
		};
		static inline toera_t<0x000C'120A> TOERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットマスタイネーブルレジスタ（TOERB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct toerb_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OE6B;
			bit_rw_t<io_, bitpos::B1> OE7A;
			bit_rw_t<io_, bitpos::B2> OE7B;
			bit_rw_t<io_, bitpos::B3> OE6D;
			bit_rw_t<io_, bitpos::B4> OE7C;
			bit_rw_t<io_, bitpos::B5> OE7D;
		};
		static inline toerb_t<0x000C'1A0A> TOERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1A, TOCR1B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tocr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OLSP;
			bit_rw_t<io_, bitpos::B1> OLSN;
			bit_rw_t<io_, bitpos::B2> TOCS;
			bit_rw_t<io_, bitpos::B3> TOCL;

			bit_rw_t<io_, bitpos::B6> PSYE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1A）
		*/
		//-----------------------------------------------------------------//
		static inline tocr1_t<0x000C'120E> TOCR1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1B）
		*/
		//-----------------------------------------------------------------//
		static inline tocr1_t<0x000C'1A0E> TOCR1B;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2A, TOCR2B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tocr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    OLS1P;
			bit_rw_t <io_, bitpos::B1>    OLS1N;
			bit_rw_t <io_, bitpos::B2>    OLS2P;
			bit_rw_t <io_, bitpos::B3>    OLS2N;
			bit_rw_t <io_, bitpos::B4>    OLS3P;
			bit_rw_t <io_, bitpos::B5>    OLS3N;
			bits_rw_t<io_, bitpos::B6, 2> BF;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2A）
		*/
		//-----------------------------------------------------------------//
		static inline tocr2_t<0x000C'120F> TOCR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2B）
		*/
		//-----------------------------------------------------------------//
		static inline tocr2_t<0x000C'1A0F> TOCR2B;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRA, TOLBRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tolbr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    OLS1P;
			bit_rw_t <io_, bitpos::B1>    OLS1N;
			bit_rw_t <io_, bitpos::B2>    OLS2P;
			bit_rw_t <io_, bitpos::B3>    OLS2N;
			bit_rw_t <io_, bitpos::B4>    OLS3P;
			bit_rw_t <io_, bitpos::B5>    OLS3N;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRA）
		*/
		//-----------------------------------------------------------------//
		static inline tolbr_t<0x000C'1236> TOLBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRB）
		*/
		//-----------------------------------------------------------------//
		static inline tolbr_t<0x000C'1A36> TOLBRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマゲートコントロールレジスタ（TGCRA, TGCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tgcra_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  UF;
			bit_rw_t <io_, bitpos::B1>  VF;
			bit_rw_t <io_, bitpos::B2>  WF;
			bit_rw_t <io_, bitpos::B3>  FB;
			bit_rw_t <io_, bitpos::B4>  P;
			bit_rw_t <io_, bitpos::B5>  N;
			bit_rw_t <io_, bitpos::B6>  BDC;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマゲートコントロールレジスタ（TGCRA）
		*/
		//-----------------------------------------------------------------//
		static inline tgcra_t<0x000C'120D> TGCRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマゲートコントロールレジスタ（TGCRB）
		*/
		//-----------------------------------------------------------------//
		static inline tgcra_t<0x000C'1A0D> TGCRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1220> TCNTSA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A20> TCNTSB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1214> TCDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A14> TCDRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1222> TCBRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A22> TCBRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1216> TDDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A16> TDDRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERA, TDERB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tder_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  TDER;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERA）
		*/
		//-----------------------------------------------------------------//
		static inline tder_t<0x000C'1234> TDERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERB）
		*/
		//-----------------------------------------------------------------//
		static inline tder_t<0x000C'1A34> TDERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERA, TBTERB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbter_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 2>  BTE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERA）
		*/
		//-----------------------------------------------------------------//
		static inline tbter_t<0x000C'1232> TBTERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERB）
		*/
		//-----------------------------------------------------------------//
		static inline tbter_t<0x000C'1A32> TBTERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRA, TWCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct twcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  WRE;
			bit_rw_t <io_, bitpos::B1>  SCC;

			bit_rw_t <io_, bitpos::B7>  CCE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRA）
		*/
		//-----------------------------------------------------------------//
		static inline twcr_t<0x000C'1260> TWCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRB）
		*/
		//-----------------------------------------------------------------//
		static inline twcr_t<0x000C'1A60> TWCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ノイズフィルタコントロールレジスタ n（NFCRn）（n = 0 ～ 4, 6, 7, 9）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nfcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     NFAEN;
			bit_rw_t <io_, bitpos::B1>     NFBEN;
			bit_rw_t <io_, bitpos::B2>     NFCEN;
			bit_rw_t <io_, bitpos::B3>     NFDEN;

			bits_rw_t<io_, bitpos::B4, 2>  NFCS;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRA, TITMRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct titmr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  TITM;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRA）
		*/
		//-----------------------------------------------------------------//
		static inline titmr_t<0x000C'123A> TITMRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRB）
		*/
		//-----------------------------------------------------------------//
		static inline titmr_t<0x000C'1A3A> TITMRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 1（TITCR1A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr1a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T4VCOR;
			bit_rw_t <io_, bitpos::B3>     T4VEN;
			bits_rw_t<io_, bitpos::B4, 3>  T3ACOR;
			bit_rw_t <io_, bitpos::B7>     T3AEN;
		};
		static inline titcr1a_t<0x000C'1230> TITCR1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 1（TITCR1B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr1b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T7VCOR;
			bit_rw_t <io_, bitpos::B3>     T7VEN;
			bits_rw_t<io_, bitpos::B4, 3>  T6ACOR;
			bit_rw_t <io_, bitpos::B7>     T6AEN;
		};
		static inline titcr1b_t<0x000C'1230> TITCR1B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 1（TITCNT1A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt1a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T4VCNT;
			bits_rw_t<io_, bitpos::B4, 3>  T3ACNT;
		};
		static inline titcnt1a_t<0x000C'1231> TITCNT1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 1（TITCNT1B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt1b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T7VCNT;
			bits_rw_t<io_, bitpos::B4, 3>  T6ACNT;
		};
		static inline titcnt1b_t<0x000C'1A31> TITCNT1B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 2（TITCR2A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr2a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG4COR;
		};
		static inline titcr2a_t<0x000C'123B> TITCR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 2（TITCR2B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr2b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG7COR;
		};
		static inline titcr2b_t<0x000C'1A3B> TITCR2B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 2（TITCNT2A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt2a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG4CNT;
		};
		static inline titcnt2a_t<0x000C'123C> TITCNT2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 2（TITCNT2B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt2b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG7CNT;
		};
		static inline titcnt2b_t<0x000C'1A3C> TITCNT2B;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求選択レジスタ 0（TADSTRGR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadstrgr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  TADSTRS0;
		};
		static inline tadstrgr0_t<0x000C'1D30> TADSTRGR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求選択レジスタ 1（TADSTRGR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadstrgr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  TADSTRS1;
		};
		static inline tadstrgr1_t<0x000C'1D32> TADSTRGR1;
	};
	typedef mtu_base_t MTU;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU0 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu0_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA0;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB0;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC0;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID0;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::TGIE0;	///< 割り込み genr-E
		static constexpr auto TGIF = INT::TGIF0;	///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV1;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル型(MTU0)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,
			B,
			C,
			D,
			E,
			F,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			case CHANNEL::C: return TGIC;
			case CHANNEL::D: return TGID;
			case CHANNEL::E: return TGIE;
			case CHANNEL::F: return TGIF;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU0)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST0 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネル型を取得
			@param[in]	ch	チャネル型
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_abcd<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1300> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2_t<0x000C'1328> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1x_t<0x000C'1301> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1302> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C'1303> TIORL_;
		static inline TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tiery_t<0x000C'1304> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER2）
		*/
		//-----------------------------------------------------------------//
		static inline tier2_t<0x000C'1324> TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtmx_t<0x000C'1326> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1306> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1308> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'130A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'130C> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'130E> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1320> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1322> TGRF_;
		static inline TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ (TGR)
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_abcdef_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, TGRF_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1290> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタクロック（NFCRC）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1299> NFCRC;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU1 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu1_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA1;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB1;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::NONE;		///< 割り込み genr-C
		static constexpr auto TGID = INT::NONE;		///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::TCIU1;	///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV1;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< MTIOC1A
			B,  ///< MTIOC1B
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU1)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST1 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_ab<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1380> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2x_t<0x000C'1394> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1y_t<0x000C'1381> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 3（TMDR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tmdr3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LWA;
			bit_rw_t<io_, bitpos::B1> PHCKSEL;
		};
		static inline tmdr3_t<0x000C'1391> TMDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1382> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_ab_t<TIORH_, CHANNEL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tierx_t<0x000C'1384> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x000C'1385> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ticcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> I1AE;
			bit_rw_t<io_, bitpos::B1> I1BE;
			bit_rw_t<io_, bitpos::B2> I2AE;
			bit_rw_t<io_, bitpos::B3> I2BE;
		};
		static inline ticcr_t<0x000C'1390> TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1386> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマロングワードカウンタ（TCNTLW）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'13A0> TCNTLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1388> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'138A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_ab_t<TGRA_, TGRB_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRALW）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'13A4> TGRALW;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRBLW）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'13A8> TGRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1291> NFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu2_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA2;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB2;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::NONE;		///< 割り込み genr-C
		static constexpr auto TGID = INT::NONE;		///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::TCIU2;	///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV2;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< PA3 / MTIOC2A (LFQFP100:38)
			B,  ///< PA2 / MTIOC2B (LFQFP100:39)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU2)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST2 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_ab<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1400> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2x_t<0x000C'140C> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1y_t<0x000C'1401> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1402> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_ab_t<TIORH_, CHANNEL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tierx_t<0x000C'1404> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x000C'1405> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1406> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1408> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'140A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_ab_t<TGRA_, TGRB_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1292> NFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU3 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu3_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA3;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB3;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC3;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID3;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV3;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< P33 / MTIOC3A (LFQFP100:58)
			B,  ///< P71 / MTIOC3B (LFQFP100:56)
			C,  ///< P32 / MTIOC3C (LFQFP100:59)
			D,  ///< P74 / MTIOC3D (LFQFP100:53)
			E,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			case CHANNEL::C: return TGIC;
			case CHANNEL::D: return TGID;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU3)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST3 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_abcd<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1200> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2_t<0x000C'124C> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1z_t<0x000C'1202> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1204> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C'1205> TIORL_;
		static inline TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tiery_t<0x000C'1208> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x000C'122C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtmy_t<0x000C'1238> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1210> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1218> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'121A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1224> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1226> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1272> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_abcde_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1293> NFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU4 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu4_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA4;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB4;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC4;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID4;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV4;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル型 (MTU4)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< P72 / MTIOC4A (LFQFP100:55)
			B,  ///< P73 / MTIOC4B (LFQFP100:54)
			C,  ///< P75 / MTIOC4C (LFQFP100:52)
			D,  ///< P76 / MTIOC4D (LFQFP100:51)
			E,
			F,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			case CHANNEL::C: return TGIC;
			case CHANNEL::D: return TGID;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU4)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST4 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_abcd<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1201> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2_t<0x000C'124D> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1z_t<0x000C'1203> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1206> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C'1207> TIORL_;
		static inline TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tierz_t<0x000C'1209> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x000C'122D> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtmy_t<0x000C'1239> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1212> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'121C> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'121E> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1228> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'122A> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1274> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1276> TGRF_;
		static inline TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_abcdef_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, TGRF_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1294> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ITB4VE;
			bit_rw_t<io_, bitpos::B1> ITB3AE;
			bit_rw_t<io_, bitpos::B2> ITA4VE;
			bit_rw_t<io_, bitpos::B3> ITA3AE;
			bit_rw_t<io_, bitpos::B4> DT4BE;
			bit_rw_t<io_, bitpos::B5> UT4BE;
			bit_rw_t<io_, bitpos::B6> DT4AE;
			bit_rw_t<io_, bitpos::B7> UT4AE;

			bits_rw_t<io_, bitpos::B14, 2> BF;
		};
		static inline tadcr_t<0x000C'1240> TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1244> TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1246> TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1248> TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'124A> TADCOBRB;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU5 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu5_t : MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::NONE;		///< 割り込み genr-A
		static constexpr auto TGIB = INT::NONE;		///< 割り込み genr-B
		static constexpr auto TGIC = INT::NONE;		///< 割り込み genr-C
		static constexpr auto TGID = INT::NONE;		///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::TGIU5;	///< 割り込み genr-U
		static constexpr auto TGIV = INT::TGIV5;	///< 割り込み genr-V
		static constexpr auto TGIW = INT::TGIW5;	///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::NONE;		///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			U,   ///< P24 / MTIOC5U (LFQFP100:64)
			V,   ///< P23 / MTIOC5V (LFQFP100:65)
			W,   ///< P22 / MTIOC5W (LFQFP100:66)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::U: return TGIU;
			case CHANNEL::V: return TGIV;
			case CHANNEL::W: return TGIW;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			auto ret = port_map_mtu::CHANNEL::NONE;
			switch(ch) {
			case CHANNEL::U:
				ret = port_map_mtu::CHANNEL::U;
				break;
			case CHANNEL::V:
				ret = port_map_mtu::CHANNEL::V;
				break;
			case CHANNEL::W:
				ret = port_map_mtu::CHANNEL::W;
				break;
			default:
				break;
			}
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ（TCR[UVW]）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> TPSC;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRU）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1C84> TCRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRV）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1C94> TCRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRW）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1CA4> TCRW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		struct tgr_t {

			static uint32_t address(CHANNEL ch)
			{
				switch(ch) {
				case CHANNEL::U:
					return TGRU.address;
				case CHANNEL::V:
					return TGRV.address;
				case CHANNEL::W:
					return TGRW.address;
				}
				return 0;
			}

			uint16_t operator () (CHANNEL ch) {
				return device::rd16_(address(ch));
			}

			uint16_t& operator [] (CHANNEL ch) {
				return *reinterpret_cast<uint16_t*>(address(ch));
			}
		};
		static inline tgr_t TGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIOR[UVW]）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tior_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> IOC;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORU）
		*/
		//-----------------------------------------------------------------//
		static inline tior_t<0x000C'1C86> TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		static inline tior_t<0x000C'1C96> TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		static inline tior_t<0x000C'1CA6> TIORW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tcntcmpclr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPCLR5W;
			bit_rw_t<io_, bitpos::B1> CMPCLR5V;
			bit_rw_t<io_, bitpos::B2> CMPCLR5U;
		};
		static inline tcntcmpclr_t<0x000C'1CB6> TCNTCMPCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tier_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIE5W;
			bit_rw_t<io_, bitpos::B1> TGIE5V;
			bit_rw_t<io_, bitpos::B2> TGIE5U;
		};
		static inline tier_t<0x000C'1CB2> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1C80> TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1C90> TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1CA0> TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1C82> TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1C92> TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1CA2> TGRW;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CSTW5;
			bit_rw_t<io_, bitpos::B1> CSTV5;
			bit_rw_t<io_, bitpos::B2> CSTU5;
		};
		static inline tstr_t<0x000C'1CB4> TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ノイズフィルタコントロールレジスタ（NFCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nfcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      NFUEN;
			bit_rw_t <io_, bitpos::B1>      NFVEN;
			bit_rw_t <io_, bitpos::B2>      NFWEN;

			bits_rw_t <io_, bitpos::B4, 2>  NFCS;
		};
		static inline nfcr_t<0x000C'1A95> NFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU6 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu6_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA6;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB6;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC6;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID6;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV6;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< PA1 / MTIOC6A (LFQFP100:40)
			B,  ///< P95 / MTIOC6B (LFQFP100:45)
			C,  ///< PA0 / MTIOC6C (LFQFP100:41)
			D,  ///< P92 / MTIOC6D (LFQFP100:48)
			E,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			case CHANNEL::C: return TGIC;
			case CHANNEL::D: return TGID;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU6)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRB.CST6 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_abcd<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1A00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2_t<0x000C'1A4C> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1z_t<0x000C'1A02> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1A04> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C'1A05> TIORL_;
		static inline TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tiery_t<0x000C'1A08> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x000C'1A2C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtmy_t<0x000C'1A38> TBTM;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマシンクロクリアレジスタ（TSYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tsycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CE2B;
			bit_rw_t<io_, bitpos::B1> CE2A;
			bit_rw_t<io_, bitpos::B2> CE1B;
			bit_rw_t<io_, bitpos::B3> CE1A;
			bit_rw_t<io_, bitpos::B4> CE0C;
			bit_rw_t<io_, bitpos::B5> CE0D;
			bit_rw_t<io_, bitpos::B6> CE0B;
			bit_rw_t<io_, bitpos::B7> CE0A;
		};
		static inline tsycr_t<0x000C'1A50> TSYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A10> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A18> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A1A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A24> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A26> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A72> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_abcde_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C1A93> NFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU7 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu7_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA7;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB7;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC7;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID7;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV7;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< P94 / MTIOC7A (LFQFP100:46)
			B,  ///< P93 / MTIOC7B (LFQFP100:47)
			C,  ///< P91 / MTIOC7C (LFQFP100:49)
			D,  ///< P90 / MTIOC7D (LFQFP100:50)
			E,
			F,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			case CHANNEL::C: return TGIC;
			case CHANNEL::D: return TGID;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU7)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRB.CST7 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_abcd<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1A01> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2_t<0x000C'1A4D> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1z_t<0x000C'1A03> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1A06> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C'1A07> TIORL_;
		static inline TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tierz_t<0x000C'1A09> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x000C'1A2D> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtmy_t<0x000C'1A39> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A12> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A1C> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A1E> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A28> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A2A> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A74> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1A76> TGRF_;
		static inline TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_abcdef_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, TGRF_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1A94> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ITB7VE;
			bit_rw_t<io_, bitpos::B1> ITB6AE;
			bit_rw_t<io_, bitpos::B2> ITA7VE;
			bit_rw_t<io_, bitpos::B3> ITA6AE;
			bit_rw_t<io_, bitpos::B4> DT7BE;
			bit_rw_t<io_, bitpos::B5> UT7BE;
			bit_rw_t<io_, bitpos::B6> DT7AE;
			bit_rw_t<io_, bitpos::B7> UT7AE;

			bits_rw_t<io_, bitpos::B14, 2> BF;
		};
		static inline tadcr_t<0x000C'1A40> TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A44> TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A46> TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A48> TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1A4A> TADCOBRB;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU8 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu8_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA8;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB8;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC8;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID8;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV8;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = true;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< P94 / MTIOC7A (LFQFP100:46)
			B,  ///< P93 / MTIOC7B (LFQFP100:47)
			C,  ///< P91 / MTIOC7C (LFQFP100:49)
			D,  ///< P90 / MTIOC7D (LFQFP100:50)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			case CHANNEL::C: return TGIC;
			case CHANNEL::D: return TGID;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU7)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST8 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_abcd<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1600> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2_t<0x000C'1606> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1z_t<0x000C'1601> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1602> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C'1603> TIORL_;
		static inline TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tier8_t<0x000C'1604> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'1608> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C'160C> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C'1610> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C'1614> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C'1618> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr32_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C1298> NFCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU9 定義クラス（RX24T/RX66T/RX72T）
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	pclk	マスタークロック周期
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT, uint32_t pclk>
	struct mtu9_t : public MTU {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA9;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB9;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC9;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID9;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::TGIE9;	///< 割り込み genr-E
		static constexpr auto TGIF = INT::TGIF9;	///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV9;	///< 割り込み ovef-V

		static constexpr auto PCLK = pclk;			///< マスタークロック周期

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU3;	///< クロック分周能力

		static constexpr bool TGR32 = false;		///< TGR register 32 bits word


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU9)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< PD7 / MTIOC9A (LFQFP100:18)
			B,  ///< PE0 / MTIOC9B (LFQFP100:17)
			C,  ///< PD6 / MTIOC9C (LFQFP100:19)
			D,  ///< PE1 / MTIOC9D (LFQFP100:16)
			E,
			F,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みベクター取得
			@param[in] ch	チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static auto get_vector(CHANNEL ch)
		{
			switch(ch) {
			case CHANNEL::A: return TGIA;
			case CHANNEL::B: return TGIB;
			case CHANNEL::C: return TGIC;
			case CHANNEL::D: return TGID;
			case CHANNEL::E: return TGIE;
			case CHANNEL::F: return TGIF;
			default: return INT::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU9)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST9 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(CHANNEL ch)
		{
			return conv_port_map_channel_abcd<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x000C'1580> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static inline tcr2_t<0x000C'15A8> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static inline tmdr1x_t<0x000C'1581> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C'1582> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C'1583> TIORL_;
		static inline TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tiery_t<0x000C'1584> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtmx_t<0x000C'15A6> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000C'1586> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'1588> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'158A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'158C> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'158E> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'15A0> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C'15A2> TGRF_;
		static inline TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr16_abcdef_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, TGRF_, CHANNEL> TGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static inline nfcr_t<0x000C'1296> NFCR;
	};

#if defined(SIG_RX63T) || defined(SIG_RX63T_S)  // MTU3
	typedef mtu0_t<peripheral::MTU0, ICU::VECTOR, clock_profile::PCLKA> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::VECTOR, clock_profile::PCLKA> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::VECTOR, clock_profile::PCLKA> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::VECTOR, clock_profile::PCLKA> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::VECTOR, clock_profile::PCLKA> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::VECTOR, clock_profile::PCLKA> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::VECTOR, clock_profile::PCLKA> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::VECTOR, clock_profile::PCLKA> MTU7;

#elif defined(SIG_RX24T)  // MTU3d
	typedef mtu0_t<peripheral::MTU0, ICU::VECTOR, clock_profile::PCLKA> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::VECTOR, clock_profile::PCLKA> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::VECTOR, clock_profile::PCLKA> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::VECTOR, clock_profile::PCLKA> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::VECTOR, clock_profile::PCLKA> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::VECTOR, clock_profile::PCLKA> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::VECTOR, clock_profile::PCLKA> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::VECTOR, clock_profile::PCLKA> MTU7;
	typedef mtu9_t<peripheral::MTU9, ICU::VECTOR, clock_profile::PCLKA> MTU9;
#elif defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)  // MTU3d 選択型割り込み
	typedef mtu0_t<peripheral::MTU0, ICU::SELECTA, clock_profile::PCLKC> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::SELECTA, clock_profile::PCLKC> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::SELECTA, clock_profile::PCLKC> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::SELECTA, clock_profile::PCLKC> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::SELECTA, clock_profile::PCLKC> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::SELECTA, clock_profile::PCLKC> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::SELECTA, clock_profile::PCLKC> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::SELECTA, clock_profile::PCLKC> MTU7;
	typedef mtu9_t<peripheral::MTU9, ICU::SELECTA, clock_profile::PCLKC> MTU9;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72M) || defined(SIG_RX72N)  // MTU3a
	typedef mtu0_t<peripheral::MTU0, ICU::SELECTA, clock_profile::PCLKA> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::SELECTA, clock_profile::PCLKA> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::SELECTA, clock_profile::PCLKA> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::SELECTA, clock_profile::PCLKA> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::SELECTA, clock_profile::PCLKA> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::SELECTA, clock_profile::PCLKA> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::SELECTA, clock_profile::PCLKA> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::SELECTA, clock_profile::PCLKA> MTU7;
	typedef mtu8_t<peripheral::MTU8, ICU::SELECTA, clock_profile::PCLKA> MTU8;
#endif
}
