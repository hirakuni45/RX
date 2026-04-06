#pragma once
//=========================================================================//
/*!	@file
	@brief	RX21A 24-Bit ∆ΣA/D Converter / 24 ビット ∆ΣA/D コンバータ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX600/ad_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DSAD 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct dsad_t {

		static constexpr auto PERIPHERAL = peripheral::DSAD;		///< ペリフェラル型
		static constexpr auto DSADI0	 = ICU::VECTOR::DSADI0;		///< チャネル０変換終了割り込みベクター
		static constexpr auto DSADI1	 = ICU::VECTOR::DSADI1;		///< チャネル１変換終了割り込みベクター
		static constexpr auto DSADI2	 = ICU::VECTOR::DSADI2;		///< チャネル２変換終了割り込みベクター
		static constexpr auto DSADI3	 = ICU::VECTOR::DSADI3;		///< チャネル３変換終了割り込みベクター
		static constexpr auto DSADI4	 = ICU::VECTOR::DSADI4;		///< チャネル４変換終了割り込みベクター
		static constexpr auto DSADI5	 = ICU::VECTOR::DSADI5;		///< チャネル５変換終了割り込みベクター
		static constexpr auto DSADI6	 = ICU::VECTOR::DSADI6;		///< チャネル６変換終了割り込みベクター
		static constexpr auto DSADORI	 = ICU::VECTOR::DSADORI;	///< チャネル０～６データレジスタ上書き割り込みベクター

		static constexpr auto PCLK = clock_profile::PCLKB;			///< 変換クロック元
		static constexpr auto DSADCLK = clock_profile::PCLKC;		///< DSADクロック元
		static constexpr uint32_t CONV_TIME_NS = 8192;				///< 変換時間 81.92uS、単位「ns」(CLK: 25MHz)

//		static constexpr uint32_t ANALOG_NUM = 16;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型 (S12AD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AN000,		///< P40 (LFQFP64: 60) (LFQFP100:  95)
			AN001,		///< P41 (LFQFP64: 58) (LFQFP100:  93)
			AN002,		///< P42 (LFQFP64: 57) (LFQFP100:  92)
			AN003,		///< P43 (LFQFP64: 56) (LFQFP100:  91)
			AN004,		///< P44 (LFQFP64: 55) (LFQFP100:  90)
			AN005,		///< P45 (LFQFP64: --) (LFQFP100:  89)
			AN006,		///< P46 (LFQFP64: 53) (LFQFP100:  88)
			AN007,		///< P47 (LFQFP64: --) (LFQFP100:  87)
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D コントロールレジスタ 0 ～ 6（DSADCR0 ～ 6）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadcrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  ADSE;
		};
		static inline dsadcrn_t<base + 0x10>  DSADCR0;
		static inline dsadcrn_t<base + 0x20>  DSADCR1;
		static inline dsadcrn_t<base + 0x30>  DSADCR2;
		static inline dsadcrn_t<base + 0x40>  DSADCR3;
		static inline dsadcrn_t<base + 0x50>  DSADCR4;
		static inline dsadcrn_t<base + 0x60>  DSADCR5;
		static inline dsadcrn_t<base + 0x70>  DSADCR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D リセットレジスタ（DSADRSTR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadrstr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  DSRST;
		};
		static inline dsadrstr_t<base + 0x01>  DSADRSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D コントロール / ステータスレジスタ 0 ～ 6（DSADCSR0 ～ 6）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadcsrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B3>  TRGE;
			bit_rw_t<io_, bitpos::B4>  ADIE;
			bit_rw_t<io_, bitpos::B5>  OVIE;
		};
		static inline dsadcsrn_t<base + 0x11>  DSADCSR0;
		static inline dsadcsrn_t<base + 0x21>  DSADCSR1;
		static inline dsadcsrn_t<base + 0x31>  DSADCSR2;
		static inline dsadcsrn_t<base + 0x41>  DSADCSR3;
		static inline dsadcsrn_t<base + 0x51>  DSADCSR4;
		static inline dsadcsrn_t<base + 0x61>  DSADCSR5;
		static inline dsadcsrn_t<base + 0x71>  DSADCSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D ゲイン選択レジスタ 0 ～ 3（DSADGSR0 ～ 3）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadgsrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  GAIN;
		};
		static inline dsadgsrn_t<base + 0x12>  DSADGSR0;
		static inline dsadgsrn_t<base + 0x22>  DSADGSR1;
		static inline dsadgsrn_t<base + 0x32>  DSADGSR2;
		static inline dsadgsrn_t<base + 0x42>  DSADGSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D ゲイン選択レジスタ 4 ～ 6（DSADGSR4 ～ 6）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadgsr4n_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  GAIN;
		};
		static inline dsadgsr4n_t<base + 0x52>  DSADGSR4;
		static inline dsadgsr4n_t<base + 0x62>  DSADGSR5;
		static inline dsadgsr4n_t<base + 0x72>  DSADGSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D 上書きフラグレジスタ 0 ～ 6（DSADFR0 ～ 6）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadfrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DSOFCL;
			bit_rw_t<io_, bitpos::B1>  DSOF;
		};
		static inline dsadfrn_t<base + 0x13>  DSADFR0;
		static inline dsadfrn_t<base + 0x23>  DSADFR1;
		static inline dsadfrn_t<base + 0x33>  DSADFR2;
		static inline dsadfrn_t<base + 0x43>  DSADFR3;
		static inline dsadfrn_t<base + 0x53>  DSADFR4;
		static inline dsadfrn_t<base + 0x63>  DSADFR5;
		static inline dsadfrn_t<base + 0x73>  DSADFR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D データレジスタ 0 ～ 6（DSADDR0 ～ 6）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x14>  DSADDR0;
		static inline rw16_t<base + 0x24>  DSADDR1;
		static inline rw16_t<base + 0x34>  DSADDR2;
		static inline rw16_t<base + 0x44>  DSADDR3;
		static inline rw16_t<base + 0x54>  DSADDR4;
		static inline rw16_t<base + 0x64>  DSADDR5;
		static inline rw16_t<base + 0x74>  DSADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D リファレンス制御レジスタ（DSADRCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadrcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  BGRE;
			bit_rw_t<io_, bitpos::B7>  EXREF;
		};
		static inline dsadrcr_t<base + 0x02>  DSADRCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D 制御拡張レジスタ（DSADCER）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadcer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ADC;
		};
		static inline dsadcer_t<base + 0x03>  DSADCER;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D 入力選択レジスタ 0 ～ 6（DSADISR0 ～ 6）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadisrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ISEL;
		};
		static inline dsadisrn_t<base + 0x18>  DSADISR0;
		static inline dsadisrn_t<base + 0x28>  DSADISR1;
		static inline dsadisrn_t<base + 0x38>  DSADISR2;
		static inline dsadisrn_t<base + 0x48>  DSADISR3;
		static inline dsadisrn_t<base + 0x58>  DSADISR4;
		static inline dsadisrn_t<base + 0x68>  DSADISR5;
		static inline dsadisrn_t<base + 0x78>  DSADISR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	∆ΣA/D 入力インピーダンス校正データレジスタ（DSADIIC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dsadiic_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B16, 16>  IICD;
		};
		static inline dsadiic_t<0xFEFF'FBD0>  DSADIIC;



	};
	typedef dsad_t<0x0008'B400>  DSAD;
}
