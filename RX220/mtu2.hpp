#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・MTU2a 定義 @n
			RX110/RX111/RX113 @n
			RX130/RX140 @n
			RX220/RX231 @n
			RX631/RX63N 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU ベース・クラス（各 MTU 共通）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mtu_base_t {

#if defined(SIG_RX231)
		static constexpr auto PCLK = clock_profile::PCLKA;	///< MTU master clock
#else
		static constexpr auto PCLK = clock_profile::PCLKB;	///< MTU master clock
#endif

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
				@return TIOR の値
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
#if defined(SIG_RX110)
#else
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
#endif
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
#if defined(SIG_RX110)
#else
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
#endif
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
	typedef mtu_base_t MTU;


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
#if defined(SIG_RX110) || defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130) || defined(SIG_RX140) || defined(SIG_RX220) || defined(SIG_RX631) || defined(SIG_RX63N)
	typedef mtu_ab_t<0x0008'8680> MTUA;
#elif defined(SIG_RX231)
	typedef mtu_ab_t<0x000D'0A80> MTUA;
#endif

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU0 定義クラス
		@param[in]	base	ベースアドレス
		@param[in]	INTN	割り込み型 N
		@param[in]	INTM	割り込み型 M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, typename INTN, typename INTM>
	struct mtu0_t : public MTU, MTUA {

		static constexpr auto PERIPHERAL = peripheral::MTU0;	///< ペリフェラル型
		static constexpr auto TGIA = INTN::TGIA0;				///< 割り込み genr-A
		static constexpr auto TGIB = INTN::TGIB0;				///< 割り込み genr-B
		static constexpr auto TGIC = INTN::TGIC0;				///< 割り込み genr-C
		static constexpr auto TGID = INTN::TGID0;				///< 割り込み genr-D
		static constexpr auto TGIE = INTN::TGIE0;				///< 割り込み genr-E
		static constexpr auto TGIF = INTN::TGIF0;				///< 割り込み genr-F
		static constexpr auto TGIU = INTN::NONE;				///< 割り込み genr-U
		static constexpr auto TGIV = INTN::NONE;				///< 割り込み genr-V
		static constexpr auto TGIW = INTN::NONE;				///< 割り込み genr-W
		static constexpr auto TCIU = INTN::NONE;				///< 割り込み undf-U
		static constexpr auto TCIV = INTM::TCIV0;				///< 割り込み ovef-V

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
			default: return INTN::NONE;
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
		static inline tcr_t<base + 0x00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<base + 0x01> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<base + 0x02> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<base + 0x03> TIORL_;
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
		static inline tier_t<base + 0x04> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ 2（TIER2）
		*/
		//-----------------------------------------------------------------//
		static inline tier2_t<base + 0x24> TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<base + 0x05> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<base + 0x26> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x06> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x08> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0C> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0E> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20> TGRE_;
		static inline TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x22> TGRF_;
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
		@param[in]	base	ベースアドレス
		@param[in]	INTN	割り込み型 N
		@param[in]	INTM	割り込み型 M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, typename INTN, typename INTM>
	struct mtu1_t : public MTU, MTUA {

		static constexpr auto PERIPHERAL = peripheral::MTU1;	///< ペリフェラル型
		static constexpr auto TGIA = INTN::TGIA1;				///< 割り込み genr-A
		static constexpr auto TGIB = INTN::TGIB1;				///< 割り込み genr-B
		static constexpr auto TGIC = INTN::NONE;				///< 割り込み genr-C
		static constexpr auto TGID = INTN::NONE;				///< 割り込み genr-D
		static constexpr auto TGIE = INTN::NONE;				///< 割り込み genr-E
		static constexpr auto TGIF = INTN::NONE;				///< 割り込み genr-F
		static constexpr auto TGIU = INTN::NONE;				///< 割り込み genr-U
		static constexpr auto TGIV = INTN::NONE;				///< 割り込み genr-V
		static constexpr auto TGIW = INTN::NONE;				///< 割り込み genr-W
		static constexpr auto TCIU = INTM::TCIU1;				///< 割り込み undf-U
		static constexpr auto TCIV = INTM::TCIV1;				///< 割り込み ovef-V

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
			default: return INTN::NONE;
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
		static inline tcr_t<base + 0x00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<base + 0x01> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<base + 0x02> TIORH_;
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
		static inline tier_t<base + 0x04> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<base + 0x05> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）
		*/
		//-----------------------------------------------------------------//
		static inline ticcr_t<base + 0x10> TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x06> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x08> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0A> TGRB_;
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
		@param[in]	base	ベースアドレス
		@param[in]	INTN	割り込み型 N
		@param[in]	INTM	割り込み型 M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, typename INTN, typename INTM>
	struct mtu2_t : public MTU, MTUA {

		static constexpr auto PERIPHERAL = peripheral::MTU2;	///< ペリフェラル型
		static constexpr auto TGIA = INTN::TGIA2;				///< 割り込み genr-A
		static constexpr auto TGIB = INTN::TGIB2;				///< 割り込み genr-B
		static constexpr auto TGIC = INTN::NONE;				///< 割り込み genr-C
		static constexpr auto TGID = INTN::NONE;				///< 割り込み genr-D
		static constexpr auto TGIE = INTN::NONE;				///< 割り込み genr-E
		static constexpr auto TGIF = INTN::NONE;				///< 割り込み genr-F
		static constexpr auto TGIU = INTN::NONE;				///< 割り込み genr-U
		static constexpr auto TGIV = INTN::NONE;				///< 割り込み genr-V
		static constexpr auto TGIW = INTN::NONE;				///< 割り込み genr-W
		static constexpr auto TCIU = INTM::TCIU2;				///< 割り込み undf-U
		static constexpr auto TCIV = INTM::TCIV2;				///< 割り込み ovef-V

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
			default: return INTN::NONE;
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
		static inline tcr_t<base + 0x00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<base + 0x01> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<base + 0x02> TIORH_;
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
		static inline tier_t<base + 0x04> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<base + 0x05> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x06> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x08> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_ab_t<TGRA_, TGRB_, CHANNEL> TGR;
	};

#if defined(SIG_RX110)
#else
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU3 定義クラス
		@param[in]	base	ベースアドレス
		@param[in]	INTN	割り込み型 N
		@param[in]	INTM	割り込み型 M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, typename INTN, typename INTM>
	struct mtu3_t : public MTU, MTUA {

		static constexpr auto PERIPHERAL = peripheral::MTU3;	///< ペリフェラル型
		static constexpr auto TGIA = INTN::TGIA3;				///< 割り込み genr-A
		static constexpr auto TGIB = INTN::TGIB3;				///< 割り込み genr-B
		static constexpr auto TGIC = INTN::TGIC3;				///< 割り込み genr-C
		static constexpr auto TGID = INTN::TGID3;				///< 割り込み genr-D
		static constexpr auto TGIE = INTN::NONE;				///< 割り込み genr-E
		static constexpr auto TGIF = INTN::NONE;				///< 割り込み genr-F
		static constexpr auto TGIU = INTN::NONE;				///< 割り込み genr-U
		static constexpr auto TGIV = INTN::NONE;				///< 割り込み genr-V
		static constexpr auto TGIW = INTN::NONE;				///< 割り込み genr-W
		static constexpr auto TCIU = INTN::NONE;				///< 割り込み undf-U
		static constexpr auto TCIV = INTM::TCIV3;				///< 割り込み ovef-V

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
			default: return INTN::NONE;
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
		static inline tcr_t<base + 0x00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<base + 0x02> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<base + 0x04> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<base + 0x05> TIORL_;
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
		static inline tier_t<base + 0x08> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<base + 0x2C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<base + 0x38> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x10> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x18> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1A> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x24> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x26> TGRD_;
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
		@param[in]	base	ベースアドレス
		@param[in]	INTN	割り込み型 N
		@param[in]	INTN	割り込み型 M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, typename INTN, typename INTM>
	struct mtu4_t : public MTU, MTUA {

		static constexpr auto PERIPHERAL = peripheral::MTU4;	///< ペリフェラル型
		static constexpr auto TGIA = INTN::TGIA4;				///< 割り込み genr-A
		static constexpr auto TGIB = INTN::TGIB4;				///< 割り込み genr-B
		static constexpr auto TGIC = INTN::TGIC4;				///< 割り込み genr-C
		static constexpr auto TGID = INTN::TGID4;				///< 割り込み genr-D
		static constexpr auto TGIE = INTN::NONE;				///< 割り込み genr-E
		static constexpr auto TGIF = INTN::NONE;				///< 割り込み genr-F
		static constexpr auto TGIU = INTN::NONE;				///< 割り込み genr-U
		static constexpr auto TGIV = INTN::NONE;				///< 割り込み genr-V
		static constexpr auto TGIW = INTN::NONE;				///< 割り込み genr-W
		static constexpr auto TCIU = INTN::NONE;				///< 割り込み undf-U
		static constexpr auto TCIV = INTM::TCIV4;				///< 割り込み ovef-V

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
			default: return INTN::NONE;
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
		static inline tcr_t<base + 0x00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMDR）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<base + 0x02> TMDR_;
		static inline TMDR_ TMDR;
		static inline TMDR_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<base + 0x05> TIORH_;
		static inline TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<base + 0x06> TIORL_;
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
		static inline tier_t<base + 0x08> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static inline tsr_t<base + 0x2C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static inline tbtm_t<base + 0x38> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
		*/
		//-----------------------------------------------------------------//
		static inline tadcr_t<base + 0x3F> TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA、TADCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x43> TADCORA;
		static inline rw16_t<base + 0x45> TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA、TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x47> TADCOBRA;
		static inline rw16_t<base + 0x49> TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x11> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1B> TGRA_;
		static inline TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1D> TGRB_;
		static inline TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x27> TGRC_;
		static inline TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x29> TGRD_;
		static inline TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_abcd_t<TGRA_, TGRB_, TGRC_, TGRD_, CHANNEL> TGR;
	};
#endif

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU5 定義クラス
		@param[in]	base	ベースアドレス
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, typename INT>
	struct mtu5_t : MTU, MTUA {

		static constexpr auto PERIPHERAL = peripheral::MTU5;	///< ペリフェラル型
		static constexpr auto TGIA = INT::NONE;					///< 割り込み genr-A
		static constexpr auto TGIB = INT::NONE;					///< 割り込み genr-B
		static constexpr auto TGIC = INT::NONE;					///< 割り込み genr-C
		static constexpr auto TGID = INT::NONE;					///< 割り込み genr-D
		static constexpr auto TGIE = INT::NONE;					///< 割り込み genr-E
		static constexpr auto TGIF = INT::NONE;					///< 割り込み genr-F
		static constexpr auto TGIU = INT::TGIU5;				///< 割り込み genr-U
		static constexpr auto TGIV = INT::TGIV5;				///< 割り込み genr-V
		static constexpr auto TGIW = INT::TGIW5;				///< 割り込み genr-W
		static constexpr auto TCIU = INT::NONE;					///< 割り込み undf-U
		static constexpr auto TCIV = INT::NONE;					///< 割り込み ovef-V

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
		static inline tcr_t<base + 0x04> TCRU;
		static inline tcr_t<base + 0x14> TCRV;
		static inline tcr_t<base + 0x24> TCRW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORU）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<base + 0x06> TIORU_;
		static inline TIORU_ TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<base + 0x16> TIORV_;
		static inline TIORV_ TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		typedef tiorx_t<base + 0x26> TIORW_;
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
		static inline tcntcmpclr_t<base + 0xB6 - 0x80> TCNTCMPCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static inline tierx_t<base + 0xB2 - 0x80> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x00> TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x10> TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x20> TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x02> TGRU_;
		static inline TGRU_ TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x12> TGRV_;
		static inline TGRV_ TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x22> TGRW_;
		static inline TGRW_ TGRW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGR）
		*/
		//-----------------------------------------------------------------//
		static inline tgr_uvw_t<TGRU_, TGRV_, TGRW_, CHANNEL> TGR;
	};

#if defined(SIG_RX110)
	typedef mtu0_t<0x0008'8700, ICU::VECTOR, ICU::VECTOR> MTU0;
	typedef mtu1_t<0x0008'8780, ICU::VECTOR, ICU::VECTOR> MTU1;
	typedef mtu2_t<0x0008'8800, ICU::VECTOR, ICU::VECTOR> MTU2;
	typedef mtu5_t<0x0008'8880, ICU::VECTOR> MTU5;
#elif defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130) || defined(SIG_RX140) || defined(SIG_RX220)
	typedef mtu0_t<0x0008'8700, ICU::VECTOR, ICU::VECTOR> MTU0;
	typedef mtu1_t<0x0008'8780, ICU::VECTOR, ICU::VECTOR> MTU1;
	typedef mtu2_t<0x0008'8800, ICU::VECTOR, ICU::VECTOR> MTU2;
	typedef mtu3_t<0x0008'8600, ICU::VECTOR, ICU::VECTOR> MTU3;
	typedef mtu4_t<0x0008'8601, ICU::VECTOR, ICU::VECTOR> MTU4;
	typedef mtu5_t<0x0008'8880, ICU::VECTOR> MTU5;
#elif defined(SIG_RX231)
	typedef mtu0_t<0x000D'0B00, ICU::VECTOR, ICU::VECTOR> MTU0;
	typedef mtu1_t<0x000D'0B80, ICU::VECTOR, ICU::VECTOR> MTU1;
	typedef mtu2_t<0x000D'0C00, ICU::VECTOR, ICU::VECTOR> MTU2;
	typedef mtu3_t<0x000D'0A00, ICU::VECTOR, ICU::VECTOR> MTU3;
	typedef mtu4_t<0x000D'0A01, ICU::VECTOR, ICU::VECTOR> MTU4;
	typedef mtu5_t<0x000D'0C80, ICU::VECTOR> MTU5;
#elif defined(SIG_RX631) || defined(SIG_RX63N)
	typedef mtu0_t<0x0008'8700, ICU::VECTOR, ICU::GROUP1> MTU0;
	typedef mtu1_t<0x0008'8780, ICU::VECTOR, ICU::GROUP1> MTU1;
	typedef mtu2_t<0x0008'8800, ICU::VECTOR, ICU::GROUP2> MTU2;
	typedef mtu3_t<0x0008'8600, ICU::VECTOR, ICU::GROUP2> MTU3;
	typedef mtu4_t<0x0008'8601, ICU::VECTOR, ICU::VECTOR> MTU4;
	typedef mtu5_t<0x0008'8880, ICU::VECTOR> MTU5;
#endif
}
