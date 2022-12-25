#pragma once
//=====================================================================//
/*!	@file
	@brief	RX220/RX631/RX63N グループ・MTU2a 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU ベース・クラス（各 MTU 共通）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct mtu_base_t {

		static constexpr auto PCLK = clock_profile::PCLKB;	///< MTU master clock

		static constexpr bool TGR32 = false;	///< 32 ビットカウンタ機能（全チャネル利用不可）

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
		typedef tcr2_t<0x0000'0000> TCR2_;
		static TCR2_ TCR2;


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
			@brief	タイマ I/O コントロールレジスタ（TIORx）MTU5
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

//			bool operator[] (CH ch) { return set(ch); }


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

//			bool operator[] (CH ch) { return set(ch); }


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

//			bool operator[] (CH ch) { return set(ch); }


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
			@brief	タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）MTU5
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
			@brief	タイマインタラプトイネーブルレジスタ 2（TIER2）MTU0
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
			@brief	タイマインタラプトイネーブルレジスタ X（TIERx）MTU5
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
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）MTU1
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
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）MTU4
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
	template <class _> typename mtu_base_t<_>::TCR2_ mtu_base_t<_>::TCR2;

	typedef mtu_base_t<void> MTU;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU[AB] ベース・クラス（MTU0 ~ MTU4)
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
		typedef tstr_t<base + 0x00> TSTR_;
		static TSTR_ TSTR;


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
		typedef tsyr_t<base + 0x01> TSYR_;
		static  TSYR_ TSYR;


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
		};
		typedef trwer_t<base + 0x04> TRWER_;
		static  TRWER_ TRWER;


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
		typedef toer_t<base + 0x0A> TOER_;
		static  TOER_ TOER; 


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
		typedef tocr1_t<base + 0x0E> TOCR1_;
		static  TOCR1_ TOCR1; 


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
		typedef tocr2_t<base + 0x0F> TOCR2_;
		static  TOCR2_ TOCR2; 


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
		typedef tolbr_t<base + 0x36> TOLBR_;
		static  TOLBR_ TOLBR; 


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
		typedef tgcr_t<base + 0x0D> TGCR_;
		static  TGCR_ TGCR; 


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTS）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20> TCNTS_;
		static  TCNTS_ TCNTS;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x16> TDDR_;
		static  TDDR_ TDDR;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x14> TCDR_;
		static  TCDR_ TCDR;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBR）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x22> TCBR_;
		static  TCBR_ TCBR;


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
		typedef titcr_t<base + 0x30> TITCR_;
		static  TITCR_ TITCR;


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
		typedef titcnt_t<base + 0x31> TITCNT_;
		static  TITCNT_ TITCNT;


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
		typedef tbter_t<base + 0x32> TBTER_;
		static  TBTER_ TBTER;


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
		typedef tder_t<base + 0x34> TDER_;
		static  TDER_ TDER;


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
		typedef twcr_t<base + 0x60> TWCR_;
		static  TWCR_ TWCR;
	};
	template <uint32_t base> typename mtu_ab_t<base>::TSTR_ mtu_ab_t<base>::TSTR;
	template <uint32_t base> typename mtu_ab_t<base>::TSYR_ mtu_ab_t<base>::TSYR;
	template <uint32_t base> typename mtu_ab_t<base>::TRWER_ mtu_ab_t<base>::TRWER;
	template <uint32_t base> typename mtu_ab_t<base>::TOER_ mtu_ab_t<base>::TOER;
	template <uint32_t base> typename mtu_ab_t<base>::TOCR1_ mtu_ab_t<base>::TOCR1;
	template <uint32_t base> typename mtu_ab_t<base>::TOCR2_ mtu_ab_t<base>::TOCR2;
	template <uint32_t base> typename mtu_ab_t<base>::TOLBR_ mtu_ab_t<base>::TOLBR;
	template <uint32_t base> typename mtu_ab_t<base>::TGCR_ mtu_ab_t<base>::TGCR;
	template <uint32_t base> typename mtu_ab_t<base>::TCNTS_ mtu_ab_t<base>::TCNTS;
	template <uint32_t base> typename mtu_ab_t<base>::TDDR_ mtu_ab_t<base>::TDDR;
	template <uint32_t base> typename mtu_ab_t<base>::TCDR_ mtu_ab_t<base>::TCDR;
	template <uint32_t base> typename mtu_ab_t<base>::TCBR_ mtu_ab_t<base>::TCBR;
	template <uint32_t base> typename mtu_ab_t<base>::TITCR_ mtu_ab_t<base>::TITCR;
	template <uint32_t base> typename mtu_ab_t<base>::TITCNT_ mtu_ab_t<base>::TITCNT;
	template <uint32_t base> typename mtu_ab_t<base>::TBTER_ mtu_ab_t<base>::TBTER;
	template <uint32_t base> typename mtu_ab_t<base>::TDER_ mtu_ab_t<base>::TDER;
	template <uint32_t base> typename mtu_ab_t<base>::TWCR_ mtu_ab_t<base>::TWCR;


	typedef mtu_ab_t<0x0008'8680> MTUA;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU0 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu0_t : public MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU2;	///< クロック分周能力


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
		typedef tcr_t<0x0008'8700> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8701> TMDR_;
		static  TMDR_ TMDR;
		static  TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8702> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8703> TIORL_;
		static  TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		typedef tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR_;
		static TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tier_t<0x0008'8704> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ 2（TIER2）
		*/
		//-----------------------------------------------------------------//
		typedef tier2_t<0x0008'8724> TIER2_;
		static  TIER2_ TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x0008'8705> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtm_t<0x0008'8726> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8706> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8708> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'870A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'870C> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'870E> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8720> TGRE_;
		static  TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8722> TGRF_;
		static  TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ (TGR)
		*/
		//-----------------------------------------------------------------//
		typedef tgr_abcdef_t<TGRA_, TGRB_, TGRC_, TGRD_, TGRE_, TGRF_, CHANNEL> TGR_;
		static TGR_ TGR;
	};
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TCR_ mtu0_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TMDR_ mtu0_t<per, INT>::TMDR;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TMDR_ mtu0_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIORH_ mtu0_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIORL_ mtu0_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIOR_ mtu0_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIER_ mtu0_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TSR_ mtu0_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TBTM_ mtu0_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TCNT_ mtu0_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRA_ mtu0_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRB_ mtu0_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRC_ mtu0_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRD_ mtu0_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRE_ mtu0_t<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRF_ mtu0_t<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGR_ mtu0_t<per, INT>::TGR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU1 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu1_t : public MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU2_EXT1;	///< クロック分周能力


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
		typedef tcr_t<0x0008'8780> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8781> TMDR_;
		static  TMDR_ TMDR;
		static  TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8782> TIORH_;
		static  TIORH_ TIORH;

		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		typedef tior_ab_t<TIORH_, CHANNEL> TIOR_;
		static TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tier_t<0x0008'8784> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x0008'8785> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）
		*/
		//-----------------------------------------------------------------//
		typedef ticcr_t<0x0008'8790> TICCR_;
		static  TICCR_ TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8786> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8788> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'878A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		typedef tgr_ab_t<TGRA_, TGRB_, CHANNEL> TGR_;
		static TGR_ TGR;
	};
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TCR_ mtu1_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TMDR_ mtu1_t<per, INT>::TMDR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TMDR_ mtu1_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TIORH_ mtu1_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TIOR_ mtu1_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TIER_ mtu1_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TSR_ mtu1_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TICCR_ mtu1_t<per, INT>::TICCR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TCNT_ mtu1_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TGRA_ mtu1_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TGRB_ mtu1_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TGR_ mtu1_t<per, INT>::TGR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu2_t : public MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU2_EXT2;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,
			B,
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
		typedef tcr_t<0x0008'8800> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8801> TMDR_;
		static  TMDR_ TMDR;
		static  TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8802> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		typedef tior_ab_t<TIORH_, CHANNEL> TIOR_;
		static TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tier_t<0x0008'8804> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x0008'8805> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8806> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8808> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'880A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		typedef tgr_ab_t<TGRA_, TGRB_, CHANNEL> TGR_;
		static TGR_ TGR;
	};
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TCR_ mtu2_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TMDR_ mtu2_t<per, INT>::TMDR;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TMDR_ mtu2_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TIORH_ mtu2_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TIOR_ mtu2_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TIER_ mtu2_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TSR_ mtu2_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TCNT_ mtu2_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TGRA_ mtu2_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TGRB_ mtu2_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TGR_ mtu2_t<per, INT>::TGR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU3 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu3_t : public MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU2_EXT3;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,
			B,
			C,
			D,
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
		typedef tcr_t<0x0008'8600> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8602> TMDR_;
		static  TMDR_ TMDR;
		static  TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8604> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8605> TIORL_;
		static  TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		typedef tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR_;
		static TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tier_t<0x0008'8608> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x0008'862C> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtm_t<0x0008'8638> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8610> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8618> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'861A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8624> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8626> TGRD_;
		static  TGRD_ TGRD;

		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		typedef tgr_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR_;
		static TGR_ TGR;
	};
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TCR_ mtu3_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TMDR_ mtu3_t<per, INT>::TMDR;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TMDR_ mtu3_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIORH_ mtu3_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIORL_ mtu3_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIOR_ mtu3_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIER_ mtu3_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TSR_ mtu3_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TBTM_ mtu3_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TCNT_ mtu3_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRA_ mtu3_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRB_ mtu3_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRC_ mtu3_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRD_ mtu3_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGR_ mtu3_t<per, INT>::TGR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU4 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu4_t : public MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU2_EXT3;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル型 (MTU4)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			A,  ///< P72 / MTIOC4A
			B,  ///< P73 / MTIOC4B
			C,  ///< P75 / MTIOC4C
			D,  ///< P76 / MTIOC4D
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
		typedef tcr_t<0x0008'8601> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x0008'8603> TMDR_;
		static  TMDR_ TMDR;
		static  TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x0008'8606> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x0008'8607> TIORL_;
		static  TIORL_ TIORL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		typedef tior_abcd_t<TIORH_, TIORL_, CHANNEL, PERIPHERAL> TIOR_;
		static TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tier_t<0x0008'8609> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x0008'862D> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtm_t<0x0008'8639> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
		*/
		//-----------------------------------------------------------------//
		typedef tadcr_t<0x0008'8640> TADCR_;
		static  TADCR_ TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA、TADCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8644> TADCORA_;
		static  TADCORA_ TADCORA;
		typedef rw16_t<0x0008'8646> TADCORB_;
		static  TADCORB_ TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA、TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8648> TADCOBRA_;
		static  TADCOBRA_ TADCOBRA;
		typedef rw16_t<0x0008'864A> TADCOBRB_;
		static  TADCOBRB_ TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8612> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'861C> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'861E> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8628> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'862A> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		typedef tgr_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR_;
		static TGR_ TGR;
	};
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TCR_ mtu4_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TMDR_ mtu4_t<per, INT>::TMDR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TMDR_ mtu4_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIORH_ mtu4_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIORL_ mtu4_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIOR_ mtu4_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIER_ mtu4_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TSR_ mtu4_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TBTM_ mtu4_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCR_ mtu4_t<per, INT>::TADCR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCORA_ mtu4_t<per, INT>::TADCORA;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCORB_ mtu4_t<per, INT>::TADCORB;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCOBRA_ mtu4_t<per, INT>::TADCOBRA;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCOBRB_ mtu4_t<per, INT>::TADCOBRB;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TCNT_ mtu4_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRA_ mtu4_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRB_ mtu4_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRC_ mtu4_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRD_ mtu4_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGR_ mtu4_t<per, INT>::TGR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU5 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu5_t : MTU, MTUA {

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

		static constexpr auto DIVIDE_AVILITY = CLOCK_DIVIDER::MTU2;	///< クロック分周能力


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			U,   ///< P24 / MTIOC5U
			V,   ///< P23 / MTIOC5V
			W,   ///< P22 / MTIOC5W
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
		typedef tcr_t<0x0008'8884> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORU）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'8886> TIORU_;
		static  TIORU_ TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'8896> TIORV_;
		static  TIORV_ TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<0x0008'88A6> TIORW_;
		static  TIORW_ TIORW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIOR）
		*/
		//-----------------------------------------------------------------//
		typedef tior_uvw_t<TIORU_, TIORV_, TIORW_, CHANNEL> TIOR_;
		static TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）
		*/
		//-----------------------------------------------------------------//
		typedef tcntcmpclr_t<0x0008'88B6> TCNTCMPCLR_;
		static TCNTCMPCLR_ TCNTCMPCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		typedef tierx_t<0x0008'88B2> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8880> TCNTU_;
		static TCNTU_ TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8890> TCNTV_;
		static TCNTV_ TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'88A0> TCNTW_;
		static TCNTW_ TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8882> TGRU_;
		static TGRU_ TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'8892> TGRV_;
		static TGRV_ TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'88A2> TGRW_;
		static TGRW_ TGRW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		typedef tgr_uvw_t<TGRU_, TGRV_, TGRW_, CHANNEL> TGR_;
		static TGR_ TGR;
	};
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCR_ mtu5_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIORU_ mtu5_t<per, INT>::TIORU;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIORV_ mtu5_t<per, INT>::TIORV;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIORW_ mtu5_t<per, INT>::TIORW;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIOR_ mtu5_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTCMPCLR_ mtu5_t<per, INT>::TCNTCMPCLR;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIER_ mtu5_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTU_ mtu5_t<per, INT>::TCNTU;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTV_ mtu5_t<per, INT>::TCNTV;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTW_ mtu5_t<per, INT>::TCNTW;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TGRU_ mtu5_t<per, INT>::TGRU;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TGRV_ mtu5_t<per, INT>::TGRV;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TGRW_ mtu5_t<per, INT>::TGRW;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TGR_ mtu5_t<per, INT>::TGR;


	typedef mtu0_t<peripheral::MTU0, ICU::VECTOR> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::VECTOR> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::VECTOR> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::VECTOR> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::VECTOR> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::VECTOR> MTU5;
}
