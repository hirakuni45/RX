#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・MTU2 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/mtu_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU ベース・クラス（各 MTU 共通）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mtux_base_t {

		static constexpr auto PCLK = clock_profile::PCLK;	///< MTU master clock

		static constexpr bool TGR32 = false;	///< 32 ビットカウンタ機能（全チャネル利用不可）

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
			switch(ch) {
			case CH::A: return port_map_mtu::CHANNEL::A;
			case CH::B: return port_map_mtu::CHANNEL::B;
			default:    return port_map_mtu::CHANNEL::NONE;
			}
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
			switch(ch) {
			case CH::A: return port_map_mtu::CHANNEL::A;
			case CH::B: return port_map_mtu::CHANNEL::B;
			case CH::C: return port_map_mtu::CHANNEL::C;
			case CH::D: return port_map_mtu::CHANNEL::D;
			default:    return port_map_mtu::CHANNEL::NONE;
			}
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename CH>
		static auto conv_port_map_channel_uvw(CH ch)
		{
			switch(ch) {
			case CH::U: return port_map_mtu::CHANNEL::U;
			case CH::V: return port_map_mtu::CHANNEL::V;
			case CH::W: return port_map_mtu::CHANNEL::W;
			default:    return port_map_mtu::CHANNEL::NONE;
			}
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
			@brief  タイマコントロールレジスタ 2（TCR2）ダミー
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr2_t : public rw8_null_t<base> {
			typedef rw8_null_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC2;
		};
		static inline tcr2_t<0x0000'0000> TCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 1（TMDR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr_t : public rw8_t<base> {
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
			@brief	タイマ I/O コントロールレジスタ（TIORx）MTU5, MTU11
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiorx_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> IOC;
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

			typedef rw8_t<0x0008'860A> io3_;
			bit_rw_t<io3_, bitpos::B0> OE3B;
			bit_rw_t<io3_, bitpos::B1> OE4A;
			bit_rw_t<io3_, bitpos::B2> OE4B;
			bit_rw_t<io3_, bitpos::B3> OE3D;
			bit_rw_t<io3_, bitpos::B4> OE4C;
			bit_rw_t<io3_, bitpos::B5> OE4D;

			typedef rw8_t<0x0008'8A0A> io4_;
			bit_rw_t<io4_, bitpos::B0> OE9B;
			bit_rw_t<io4_, bitpos::B1> OE10A;
			bit_rw_t<io4_, bitpos::B2> OE10B;
			bit_rw_t<io4_, bitpos::B3> OE9D;
			bit_rw_t<io4_, bitpos::B4> OE10C;
			bit_rw_t<io4_, bitpos::B5> OE10D;


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
				case peripheral::MTU9:
					OE9B = 0;
					OE9D = 0;
					break;
				case peripheral::MTU10:
					OE10A = 0;
					OE10B = 0;
					OE10C = 0;
					OE10D = 0;
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
					case peripheral::MTU10:
						OE10A = val != 0;
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
					case peripheral::MTU9:
						OE9B = val != 0;
						break;
					case peripheral::MTU10:
						OE10B = val != 0;
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
					case peripheral::MTU10:
						OE10C = val != 0;
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
					case peripheral::MTU9:
						OE9D = val != 0;
						break;
					case peripheral::MTU10:
						OE10D = val != 0;
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
			@brief	タイマ I/O コントロールレジスタ（TIOR_uvw_t）
			@param[in]	TIORU	TIORU クラス
			@param[in]	TIORV	TIORV クラス
			@param[in]	TIORW	TIORW クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TIORU, class TIORV, class TIORW, typename CH>
		struct tior_uvw_t {

			typedef rw8_t<TIORU::address> iou_;
			bits_rw_t<iou_, bitpos::B0, 5> IOU;
			typedef rw8_t<TIORV::address> iov_;
			bits_rw_t<iov_, bitpos::B0, 5> IOV;
			typedef rw8_t<TIORW::address> iow_;
			bits_rw_t<iow_, bitpos::B0, 5> IOW;

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR 全てのチャネルを無効
			*/
			//-------------------------------------------------------------//
			void disable()
			{
				IOU = 0;
				IOV = 0;
				IOW = 0;
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
				case CH::U:
					IOU = val;
					break;
				case CH::V:
					IOV = val;
					break;
				case CH::W:
					IOW = val;
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
				case CH::U:
					return IOU();
				case CH::V:
					return IOV();
				case CH::W:
					return IOW();
				default:
					return 0x00;
				}
			}

			uint8_t operator() (CH ch) { return get(ch); }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）MTU5/MTU11
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tier_t : public rw8_t<base> {
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
			bit_rw_t<io_, bitpos::B5> TCIEU;
			bit_rw_t<io_, bitpos::B6> TTGE2;
			bit_rw_t<io_, bitpos::B7> TTGE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ 2（TIER2）MTU0, MTU1
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
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ X（TIERx）MTU5, MTU11
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

			bit_rw_t<io_, bitpos::B0> TGIE5W;
			bit_rw_t<io_, bitpos::B1> TGIE5V;
			bit_rw_t<io_, bitpos::B2> TGIE5U;
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
			@brief	タイマバッファ動作転送モードレジスタ（TBTM）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbtm_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TTSA;
			bit_rw_t<io_, bitpos::B1> TTSB;
			bit_rw_t<io_, bitpos::B2> TTSE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）MTU1/MTU7
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


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）MTU4/MTU10
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマジェネラルレジスタ（TGR A, B）
			@param[in]	TGRA	TGRA クラス
			@param[in]	TGRB	TGRB クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRA, class TGRB, typename CH>
		struct tgr_ab_t {

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
			@brief  タイマジェネラルレジスタ（TGR A, B, C, D）
			@param[in]	TGRA	TGRA クラス
			@param[in]	TGRB	TGRB クラス
			@param[in]	TGRC	TGRC クラス
			@param[in]	TGRD	TGRD クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRA, class TGRB, class TGRC, class TGRD, typename CH>
		struct tgr_abcd_t {

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
			@brief  タイマジェネラルレジスタ（TGR A, B, C, D, E, F）
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
		struct tgr_abcdef_t {

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
			@brief  タイマジェネラルレジスタ（TGR U, V, W）
			@param[in]	TGRU	TGRU クラス
			@param[in]	TGRV	TGRV クラス
			@param[in]	TGRW	TGRW クラス
			@param[in]	CH		チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <class TGRU, class TGRV, class TGRW, typename CH>
		struct tgr_uvw_t {

			static uint32_t address(CH ch)
			{
				switch(ch) {
				case CH::U: return TGRU::address;
				case CH::V: return TGRV::address;
				case CH::W: return TGRW::address;
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
	};
	typedef mtux_base_t MTU;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU[AB] ベース・クラス（MTU0 ~ MTU4/MTU6 ~ MTU10)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct mtu_ab_t {

		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tstr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CST0;
			bit_rw_t<io_, bitpos::B1> CST1;
			bit_rw_t<io_, bitpos::B2> CST2;

			bit_rw_t<io_, bitpos::B6> CST3;
			bit_rw_t<io_, bitpos::B7> CST4;
		};
		static inline tstr_t<base + 0x00> TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tsyr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SYNC0;
			bit_rw_t<io_, bitpos::B1> SYNC1;
			bit_rw_t<io_, bitpos::B2> SYNC2;

			bit_rw_t<io_, bitpos::B6> SYNC3;
			bit_rw_t<io_, bitpos::B7> SYNC4;
		};
		static inline tsyr_t<base + 0x01> TSYR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWER）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct trwer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RWE;

			static inline uint8_t pad_ = 0;
		};
		static inline trwer_t<base + 0x04> TRWER;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットマスタイネーブルレジスタ（TOER）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct toer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline toer_t<base + 0x0A> TOER;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tocr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline tocr1_t<base + 0x0E> TOCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tocr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline tocr2_t<base + 0x0F> TOCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tolbr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline tolbr_t<base + 0x36> TOLBR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマゲートコントロールレジスタ（TGCR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tgcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
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
		static inline tgcr_t<base + 0x0D> TGCR;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTS）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x20> TCNTS;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x16> TDDR;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x14> TCDR;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x22> TCBR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ（TITCR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct titcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T4VCOR;
			bit_rw_t <io_, bitpos::B3>     T4VEN;
			bits_rw_t<io_, bitpos::B4, 3>  T3ACOR;
			bit_rw_t <io_, bitpos::B7>     T3AEN;
		};
		static inline titcr_t<base + 0x30> TITCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ（TITCNT）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct titcnt_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T4VCNT;
			bits_rw_t<io_, bitpos::B4, 3>  T3ACNT;
		};
		static inline titcnt_t<base + 0x31> TITCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTER）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tbter_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 2>  BTE;
		};
		static inline tbter_t<base + 0x32> TBTER;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDER）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tder_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  TDER;
		};
		static inline tder_t<base + 0x34> TDER;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct twcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  WRE;

			bit_rw_t <io_, bitpos::B7>  CCE;
		};
		static inline twcr_t<base + 0x60> TWCR;
	};
	typedef mtu_ab_t<0x0008'8680> MTUA;
	typedef mtu_ab_t<0x0008'8A80> MTUB;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU0 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu0_t : public mtu_base_t, MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T0;	///< クロック分周能力


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
			@brief  有効にする (MTU0)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			TSTR.CST0 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
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
		static inline tcr_t<0x0008'8700> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8701> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8702> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8703> TIORL_;
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
		static inline tier_t<0x0008'8704> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ 2（TIER2）
		*/
		//-----------------------------------------------------------------//
		static inline tier2_t<0x0008'8724> TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8705> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<0x0008'8726> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8706> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8708> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'870A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'870C> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'870E> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8720> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8722> TGRF_;
		static inline TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ (TGR)
		*/
		//-----------------------------------------------------------------//
		static inline tgr_abcdef_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, TGRF_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU1 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu1_t : public mtu_base_t, MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T1;	///< クロック分周能力


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
			@brief  有効にする (MTU1)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			TSTR.CST1 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
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
		static inline tcr_t<0x0008'8780> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8781> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8782> TIORH_;
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
		static inline tier_t<0x0008'8784> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8785> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）
		*/
		//-----------------------------------------------------------------//
		static inline ticcr_t<0x0008'8790> TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8786> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8788> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'878A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_ab_t<TGRA_, TGRB_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu2_t : public mtu_base_t, MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T2;	///< クロック分周能力


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
			@brief  有効にする (MTU2)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			TSTR.CST2 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
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
		static inline tcr_t<0x0008'8800> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8801> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8802> TIORH_;
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
		static inline tier_t<0x0008'8804> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8805> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8806> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8808> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'880A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_ab_t<TGRA_, TGRB_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU3 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu3_t : public mtu_base_t, MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T3;	///< クロック分周能力


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
			@brief  有効にする (MTU3)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			TSTR.CST3 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
			TRWER.pad_ &= ~0b01;
			TRWER.pad_ |= ena;
			TRWER.RWE = (TRWER.pad_ & 0b11) != 0;
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
		static inline tcr_t<0x0008'8600> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8602> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8604> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8605> TIORL_;
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
		static inline tier_t<0x0008'8608> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'862C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<0x0008'8638> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8610> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8618> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'861A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8624> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8626> TGRD_;
		static inline TGRD_ TGRD;

		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU4 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu4_t : public mtu_base_t, MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T3;	///< クロック分周能力


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
			@brief  有効にする (MTU4)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			TSTR.CST4 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
			TRWER.pad_ &= ~0b10;
			TRWER.pad_ |= ena;
			TRWER.RWE = (TRWER.pad_ & 0b11) != 0;
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
		static inline tcr_t<0x0008'8601> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8603> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8606> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8607> TIORL_;
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
		static inline tier_t<0x0008'8609> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'862D> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<0x0008'8639> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
		*/
		//-----------------------------------------------------------------//
		static inline tadcr_t<0x0008'8640> TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA、TADCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8644> TADCORA;
		static inline rw16_t<0x0008'8646> TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA、TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8648> TADCOBRA;
		static inline rw16_t<0x0008'864A> TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8612> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'861C> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'861E> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8628> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'862A> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU5 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu5_t : mtu_base_t, MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T0;	///< クロック分周能力


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
			@brief  有効にする (MTU5)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			// TSTR.CSTW5 = ena;
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
			return conv_port_map_channel_uvw<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x0008'8884> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORU）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'8886> TIORU_;
		static inline TIORU_ TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'8896> TIORV_;
		static inline TIORV_ TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'88A6> TIORW_;
		static inline TIORW_ TIORW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_uvw_t<TIORU_, TIORV_, TIORW_, CHANNEL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）
		*/
		//-----------------------------------------------------------------//
		static inline tcntcmpclr_t<0x0008'88B6> TCNTCMPCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static inline tierx_t<0x0008'88B2> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8880> TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8890> TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'88A0> TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8882> TGRU_;
		static inline TGRU_ TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8892> TGRV_;
		static inline TGRV_ TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'88A2> TGRW_;
		static inline TGRW_ TGRW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_uvw_t<TGRU_, TGRV_, TGRW_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU6 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu6_t : public mtu_base_t, MTU, MTUB {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA6;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB6;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC6;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID6;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::TGIE6;	///< 割り込み genr-E
		static constexpr auto TGIF = INT::TGIF6;	///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV6;	///< 割り込み ovef-V

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T0;	///< クロック分周能力


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
			@brief  有効にする (MTU6)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			// MTUB group CST0(CST6)
			TSTR.CST0 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
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
		static inline tcr_t<0x0008'8B00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8B01> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8B02> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8B03> TIORL_;
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
		static inline tier_t<0x0008'8B04> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8B05> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<0x0008'8B26> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8B06> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B08> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B0A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B0C> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B0E> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B10> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B12> TGRF_;
		static inline TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_abcdef_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, TGRF_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU7 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu7_t : public mtu_base_t, MTU, MTUB {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA7;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB7;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::NONE;		///< 割り込み genr-C
		static constexpr auto TGID = INT::NONE;		///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::TCIU7;	///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV7;	///< 割り込み ovef-V

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T1;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< P94 / MTIOC7A (LFQFP100:46)
			B   ///< P93 / MTIOC7B (LFQFP100:47)
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
			@brief  有効にする (MTU7)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			// MTUB group CST1(CST7)
			TSTR.CST1 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
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
		static inline tcr_t<0x0008'8B80> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8B81> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8B82> TIORH_;
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
		static inline tier_t<0x0008'8B84> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8B85> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）
		*/
		//-----------------------------------------------------------------//
		static inline ticcr_t<0x0008'8B90> TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8B86> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B88> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8B8A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_ab_t<TGRA_, TGRB_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU8 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu8_t : public mtu_base_t, MTU, MTUB {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA8;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB8;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::NONE;		///< 割り込み genr-C
		static constexpr auto TGID = INT::NONE;		///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::TCIU8;	///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV8;	///< 割り込み ovef-V

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T2;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU8)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< P94 / MTIOC7A (LFQFP100:46)
			B,  ///< P93 / MTIOC7B (LFQFP100:47)
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
			@brief  有効にする (MTU8)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			// MTUB group CST8(CST2)
			TSTR.CST2 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
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
		static inline tcr_t<0x0008'8C00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8C01> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8C02> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_ab_t<TIORH_, CHANNEL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8C05> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static inline tier_t<0x0008'8C04> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8C06> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8C08> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x0008'8C0A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_ab_t<TGRA_, TGRB_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU9 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu9_t : public mtu_base_t, MTU, MTUB {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA9;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB9;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC9;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID9;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV9;	///< 割り込み ovef-V

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T3;	///< クロック分周能力


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
			@brief  有効にする (MTU9)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			// MTUB group CST3(CST9)
			TSTR.CST3 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
			TRWER.pad_ &= ~0b01;
			TRWER.pad_ |= ena;
			TRWER.RWE = (TRWER.pad_ & 0b11) != 0;
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
		static inline tcr_t<0x0008'8A00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8A02> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8A04> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8A05> TIORL_;
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
		static inline tier_t<0x0008'8A08> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8A2C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<0x0008'8A38> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8A10> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A18> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A1A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A1C> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A1E> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU10 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu10_t : public mtu_base_t, MTU, MTUB {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::TGIA10;	///< 割り込み genr-A
		static constexpr auto TGIB = INT::TGIB10;	///< 割り込み genr-B
		static constexpr auto TGIC = INT::TGIC10;	///< 割り込み genr-C
		static constexpr auto TGID = INT::TGID10;	///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::NONE;		///< 割り込み genr-U
		static constexpr auto TGIV = INT::NONE;		///< 割り込み genr-V
		static constexpr auto TGIW = INT::NONE;		///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::TCIV10;	///< 割り込み ovef-V

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T3;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU10)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< PD7 / MTIOC9A (LFQFP100:18)
			B,  ///< PE0 / MTIOC9B (LFQFP100:17)
			C,  ///< PD6 / MTIOC9C (LFQFP100:19)
			D,  ///< PE1 / MTIOC9D (LFQFP100:16)
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
			@brief  有効にする (MTU9)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			// MTUB group CST10(CST4) 
			TSTR.CST4 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  R/W enable の設定 @n
					MTU3, MTU4, MTU9, MTU10 の場合のみ有効
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void rw_enable(bool ena = true)
		{
			TRWER.pad_ &= ~0b10;
			TRWER.pad_ |= ena;
			TRWER.RWE = (TRWER.pad_ & 0b11) != 0;
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
		static inline tcr_t<0x0008'8A01> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8A03> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8A06> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8A08> TIORL_;
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
		static inline tier_t<0x0008'8A09> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<0x0008'8A2D> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<0x0008'8A39> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
		*/
		//-----------------------------------------------------------------//
		static inline tadcr_t<0x0008'8A40> TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA、TADCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8A44> TADCORA;
		static inline rw16_t<0x0008'8A46> TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA、TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8A48> TADCOBRA;
		static inline rw16_t<0x0008'8A4A> TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8A12> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A1C> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A1E> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A28> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8A2A> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU11 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu11_t : mtu_base_t, MTU, MTUB {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TGIA = INT::NONE;		///< 割り込み genr-A
		static constexpr auto TGIB = INT::NONE;		///< 割り込み genr-B
		static constexpr auto TGIC = INT::NONE;		///< 割り込み genr-C
		static constexpr auto TGID = INT::NONE;		///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;		///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;		///< 割り込み genr-F
		static constexpr auto TGIU = INT::TGIU11;	///< 割り込み genr-U
		static constexpr auto TGIV = INT::TGIV11;	///< 割り込み genr-V
		static constexpr auto TGIW = INT::TGIW11;	///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;		///< 割り込み undf-U
		static constexpr auto TCIV = INT::NONE;		///< 割り込み ovef-V

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::T0;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU11)
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
			@brief  有効にする (MTU11)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			// TSTR.CSTW5 = ena;
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
			return conv_port_map_channel_uvw<CHANNEL>(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static inline tcr_t<0x0008'8CA4> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORU）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'8C86> TIORU_;
		static inline TIORU_ TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'8C96> TIORV_;
		static inline TIORV_ TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'8CA6> TIORW_;
		static inline TIORW_ TIORW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		static inline tior_uvw_t<TIORU_, TIORV_, TIORW_, CHANNEL> TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）
		*/
		//-----------------------------------------------------------------//
		static inline tcntcmpclr_t<0x0008'8CB6> TCNTCMPCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static inline tierx_t<0x0008'8CB2> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8C80> TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8C90> TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'8CA0> TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8C82> TGRU_;
		static inline TGRU_ TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8C92> TGRV_;
		static inline TGRV_ TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8CA2> TGRW_;
		static inline TGRW_ TGRW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_uvw_t<TGRU_, TGRV_, TGRW_, CHANNEL> TGR;
	};

	typedef mtu0_t<peripheral::MTU0, ICU::VECTOR> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::VECTOR> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::VECTOR> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::VECTOR> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::VECTOR> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::VECTOR> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::VECTOR> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::VECTOR> MTU7;
	typedef mtu8_t<peripheral::MTU8, ICU::VECTOR> MTU8;
	typedef mtu9_t<peripheral::MTU9, ICU::VECTOR> MTU9;
	typedef mtu10_t<peripheral::MTU10, ICU::VECTOR> MTU10;
	typedef mtu11_t<peripheral::MTU11, ICU::VECTOR> MTU11;
}
