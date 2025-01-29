#pragma once
//=========================================================================//
/*!	@file
	@brief	Battery Backup Function / バッテリバックアップ機能 @n
			・RX230/RX231 (VBATT) @n
			・RX23W (VBATT) @n
			・RX671 (VBATTB)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

#if defined(SIG_RX230) || defined(SIG_RX231) || defined(SIG_RX23W)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  VBATT class
		@param[in]	per		ペリフェラル型
		@param[in]	IVT		割り込み型
		@param[in]	ivec	割り込みベクタ型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename IVT, IVT ivec>
	struct vbatt_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto IVEC = ivec;			///< 割り込みベクター

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	VBATT 制御レジスタ（VBATTCR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct vbattcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    VBATTDIS;

			bit_rw_t <io_, bitpos::B4>    VBTLVDEN;

			bits_rw_t<io_, bitpos::B6, 2> VBTLVDLVL;
		};
		static inline vbattcr_t<0x0008'C29D> VBATTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	VBATT ステータスレジスタ（VBATTSR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct vbattsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    VBATRLVDETF;
			bit_ro_t <io_, bitpos::B1>    VBATVDMON;
		};
		static inline vbattsr_t<0x0008'C29E> VBATTSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	VBATT 端子電圧低下検出割り込み制御レジスタ（VBTLVDICR）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct vbtlvdicr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    VBTLVDIE;
			bit_ro_t <io_, bitpos::B1>    VBTLVDISEL;
		};
		static inline vbtlvdicr_t<0x0008'C29F> VBTLVDICR;
	};
	typedef vbatt_t<peripheral::VBATT, ICU::VECTOR, ICU::VECTOR::VBTLVDI> VBATT;

#elif defined(SIG_RX671)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バッテリバックアップ機能 (VBATTB)
		@param[in]	per		ペリフェラル型
		@param[in]	IVT		割り込み型
		@param[in]	ivec	割り込みベクタ型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename IVT, IVT ivec>
	struct vbattb_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto IVEC = ivec;			///< 割り込みベクター

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バックアップ領域電源ステータスレジスタ (BKPSR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bkpsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   PDDF;
		};
		static inline bkpsr_t<0x0008'CC46> BKPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タンパステータスレジスタ (TAMPSR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tampsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   TAMP0F;
			bit_rw_t<io_, bitpos::B1>   TAMP1F;
			bit_rw_t<io_, bitpos::B2>   TAMP2F;
		};
		static inline tampsr_t<0x0008'CC48> TAMPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タンパ制御レジスタ (TAMPCR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tampcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   TAMP0IE;
			bit_rw_t<io_, bitpos::B1>   TAMP1IE;
			bit_rw_t<io_, bitpos::B2>   TAMP2IE;

			bit_rw_t<io_, bitpos::B4>   TAMP0EE;
			bit_rw_t<io_, bitpos::B5>   TAMP1EE;
			bit_rw_t<io_, bitpos::B6>   TAMP2EE;
		};
		static inline tampcr_t<0x0008'CC49> TAMPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	時間キャプチャイベント制御レジスタ (TCECR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tcecr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   TCE0S;
			bit_rw_t<io_, bitpos::B1>   TCE1S;
			bit_rw_t<io_, bitpos::B2>   TCE2S;
		};
		static inline tcecr_t<0x0008'CC4A> TCECR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タンパ /RTCIC 入力制御レジスタ 1 (TAMPICR1)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tampicr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CH0EN;
			bit_rw_t<io_, bitpos::B1>   CH1EN;
			bit_rw_t<io_, bitpos::B2>   CH2EN;
		};
		static inline tampicr1_t<0x0008'CC4C> TAMPICR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タンパ /RTCIC 入力制御レジスタ 2 (TAMPICR2)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tampicr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CH0NFE;
			bit_rw_t<io_, bitpos::B1>   CH1NFE;
			bit_rw_t<io_, bitpos::B2>   CH2NFE;

			bit_rw_t<io_, bitpos::B4>   CH0TRG;
			bit_rw_t<io_, bitpos::B5>   CH1TRG;
			bit_rw_t<io_, bitpos::B6>   CH2TRG;
		};
		static inline tampicr2_t<0x0008'CC4D> TAMPICR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タンパ /RTCIC 入力モニタレジスタ (TAMPIMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tampimr_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>   CH0LVL;
			bit_ro_t<in_, bitpos::B1>   CH1LVL;
			bit_ro_t<in_, bitpos::B2>   CH2LVL;
		};
		static inline tampimr_t<0x0008'CC4E> TAMPIMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックアップレジスタ n (BKR[n]) (n = 0 ～ 127)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bkr_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 128) { io_::index = j; } }

			auto& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline bkr_t<0x0008'CE00> BKR;
	};
	typedef vbattb_t<peripheral::VBATT, ICU::VECTOR, ICU::VECTOR::TAMPDI> VBATT;
#endif
}
