#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・ICUb 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ICUb 定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct VECTOR {
			enum type {
				BUSERR = 16,

				FIFERR = 21,

				FRDYI = 23,

				SWINT = 27,

				CMI0 = 28,
				CMI1 = 29,
				CMI2 = 30,
				CMI3 = 31,

				D0FIFO0 = 33,
				D1FIFO0 = 34,
				USBI0 = 35,

				FERRF = 36,
				MENDF = 37,
				OVFF = 38,

				SPRI0 = 39,
				SPTI0 = 40,
				SPII0 = 41,

				SPRI1 = 42,
				SPTI1 = 43,
				SPII1 = 44,

				RXF1 = 45,
				TXF1 = 46,
				RXM1 = 47,
				TXM1 = 48,

				GTCIA7 = 49,
				GTCIB7 = 50,
				GTCIC7 = 51,
				GTCIE7 = 52,
				GTCIV7 = 53,

				CMP4 = 54,
				CMP5 = 55,
				CMP6 = 56,

				DOPCF = 57,

				IRQ0 = 64,
				IRQ1 = 65,
				IRQ2 = 66,
				IRQ3 = 67,
				IRQ4 = 68,
				IRQ5 = 69,
				IRQ6 = 70,
				IRQ7 = 71,

				USBR0 = 90,

				ADI0 = 98,

				S12ADI = 102,
				S12GBADI = 103,
				S12ADI1 = 104,
				S12GBADI1 = 105,

				GROUP0 = 106,

				GROUP12 = 114,

				SCIX0 = 122,
				SCIX1 = 123,
				SCIX2 = 124,
				SCIX3 = 125,

				TGIA0 = 126,
				TGIB0 = 127,
				TGIC0 = 128,
				TGID0 = 129,
				TGIV0 = 130,
				TGIE0 = 131,
				TGIF0 = 132,

				TGIA1 = 133,
				TGIB1 = 134,
				TGIV1 = 135,
				TGIU1 = 136,

				TGIA2 = 137,
				TGIB2 = 138,
				TGIV2 = 139,
				TGIU2 = 140,

				TGIA3 = 141,
				TGIB3 = 142,
				TGIC3 = 143,
				TGID3 = 144,
				TGIV3 = 145,

				TGIA4 = 146,
				TGIB4 = 147,
				TGIC4 = 148,
				TGID4 = 149,
				TGIV4 = 150,

				TGIU5 = 151,
				TGIV5 = 152,
				TGIW5 = 153,

				TGIA6 = 154,
				TGIB6 = 155,
				TGIC6 = 156,
				TGID6 = 157,
				TGIV6 = 158,

				TGIA7 = 161,
				TGIB7 = 162,
				TGIC7 = 163,
				TGID7 = 164,
				TGIV7 = 165,

				OEI1 = 166,
				OEI2 = 167,
				OEI3 = 168,
				OEI4 = 169,
				OEI5 = 170,

				CMP0 = 171,
				CMP1 = 172,
				CMP2 = 173,

				GTCIA4 = 174,
				GTCIB4 = 175,
				GTCIC4 = 176,
				GTCIE4 = 177,
				GTCIV4 = 178,
				LOCOI4 = 179,

				GTCIA5 = 180,
				GTCIB5 = 181,
				GTCIC5 = 182,
				GTCIE5 = 183,
				GTCIV5 = 184,

				GTCIA6 = 185,
				GTCIB6 = 186,
				GTCIC6 = 187,
				GTCIE6 = 188,
				GTCIV6 = 189,

				ICEEI1 = 190,
				ICRXI1 = 191,
				ICTXI1 = 192,
				ICTEI1 = 193,

				ICEEI0 = 194,
				ICRXI0 = 195,
				ICTXI0 = 196,
				ICTEI0 = 197,

				DMAC0I = 198,
				DMAC1I = 199,
				DMAC2I = 200,
				DMAC3I = 201,

				RXI0 = 214,
				TXI0 = 215,
				TEI0 = 216,

				RXI1 = 217,
				TXI1 = 218,
				TEI1 = 219,

				RXI2 = 220,
				TXI2 = 221,
				TEI2 = 222,

				RXI3 = 223,
				TXI3 = 224,
				TEI3 = 225,

				GTCIA0 = 226,
				GTCIB0 = 227,
				GTCIC0 = 228,
				GTCIE0 = 229,
				GTCIV0 = 230,
				LOCOI0 = 231,

				GTCIA1 = 232,
				GTCIB1 = 233,
				GTCIC1 = 234,
				GTCIE1 = 235,
				GTCIV1 = 236,

				GTCIA2 = 238,
				GTCIB2 = 239,
				GTCIC2 = 240,
				GTCIE2 = 241,
				GTCIV2 = 242,

				GTCIA3 = 244,
				GTCIB3 = 245,
				GTCIC3 = 246,
				GTCIE3 = 247,
				GTCIV3 = 248,

				RXI12 = 250,
				TXI12 = 251,
				TEI12 = 252,
			};
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {
			io8<base + 28> CMI0;
			io8<base + 29> CMI1;
			io8<base + 30> CMI2;
			io8<base + 31> CMI3;

			io8<base + 64> IRQ0;
			io8<base + 65> IRQ1;
			io8<base + 66> IRQ2;
			io8<base + 67> IRQ3;
			io8<base + 68> IRQ4;
			io8<base + 69> IRQ5;
			io8<base + 70> IRQ6;
			io8<base + 71> IRQ7;

			io8<base + 214> RXI0;
			io8<base + 215> TXI0;
			io8<base + 216> TEI0;

			io8<base + 217> RXI1;
			io8<base + 218> TXI1;
			io8<base + 219> TEI1;

			io8<base + 220> RXI2;
			io8<base + 221> TXI2;
			io8<base + 222> TEI2;

			io8<base + 223> RXI3;
			io8<base + 224> TXI3;
			io8<base + 225> TEI3;

			io8<base + 226> GTCIA0;
			io8<base + 227> GTCIB0;
			io8<base + 228> GTCIC0;
			io8<base + 229> GTCIE0;
			io8<base + 230> GTCIV0;
			io8<base + 231> LOCOI0;

			io8<base + 232> GTCIA1;
			io8<base + 233> GTCIB1;
			io8<base + 234> GTCIC1;
			io8<base + 235> GTCIE1;
			io8<base + 236> GTCIV1;

			io8<base + 238> GTCIA2;
			io8<base + 239> GTCIB2;
			io8<base + 240> GTCIC2;
			io8<base + 241> GTCIE2;
			io8<base + 242> GTCIV2;

			io8<base + 244> GTCIA3;
			io8<base + 245> GTCIB3;
			io8<base + 246> GTCIC3;
			io8<base + 247> GTCIE3;
			io8<base + 248> GTCIV3;
		};
		static ir_t<0x00087010> IR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ier_t {
			typedef io8<base + 0x02> ier02;
			bit_t<ier02, 0>	BUSERR;
			bit_t<ier02, 5>	FIFERR;
			bit_t<ier02, 7>	FRDYI;

			typedef io8<base + 0x03> ier03;
			bit_t<ier03, 3>	SWINT;
			bit_t<ier03, 4>	CMI0;
			bit_t<ier03, 5>	CMI1;
			bit_t<ier03, 6>	CMI2;
			bit_t<ier03, 7>	CMI3;

			typedef io8<base + 0x08> ier08;
			bit_t<ier08, 0>	IRQ0;
			bit_t<ier08, 1>	IRQ1;
			bit_t<ier08, 2>	IRQ2;
			bit_t<ier08, 3>	IRQ3;
			bit_t<ier08, 4>	IRQ4;
			bit_t<ier08, 5>	IRQ5;
			bit_t<ier08, 6>	IRQ6;
			bit_t<ier08, 7>	IRQ7;

			typedef io8<base + 0x1a> ier1a;
			bit_t<ier1a, 6>	RXI0;
			bit_t<ier1a, 7>	TXI0;
			typedef io8<base + 0x1b> ier1b;
			bit_t<ier1b, 0>	TEI0;
			bit_t<ier1b, 1>	RXI1;
			bit_t<ier1b, 2>	TXI1;
			bit_t<ier1b, 3>	TEI1;
			bit_t<ier1b, 4>	RXI2;
			bit_t<ier1b, 5>	TXI2;
			bit_t<ier1b, 6>	TEI2;
			bit_t<ier1b, 7>	RXI3;
			typedef io8<base + 0x1c> ier1c;
			bit_t<ier1c, 0>	TXI3;
			bit_t<ier1c, 1>	TEI3;
			bit_t<ier1c, 2>	GTCIA0;
			bit_t<ier1c, 3>	GTCIB0;
			bit_t<ier1c, 4>	GTCIC0;
			bit_t<ier1c, 5>	GTCIE0;
			bit_t<ier1c, 6>	GTCIV0;
			bit_t<ier1c, 7>	LOCOI0;

			typedef io8<base + 0x1d> ier1d;
			bit_t<ier1d, 0>	GTCIA1;
			bit_t<ier1d, 1>	GTCIB1;
			bit_t<ier1d, 2>	GTCIC1;
			bit_t<ier1d, 3>	GTCIE1;
			bit_t<ier1d, 4>	GTCIV1;

			bit_t<ier1d, 6>	GTCIA2;
			bit_t<ier1d, 7>	GTCIB2;
			typedef io8<base + 0x1e> ier1e;
			bit_t<ier1e, 0>	GTCIC2;
			bit_t<ier1e, 1>	GTCIE2;
			bit_t<ier1e, 2>	GTCIV2;

			bit_t<ier1e, 4>	GTCIA3;
			bit_t<ier1e, 5>	GTCIB3;
			bit_t<ier1e, 6>	GTCIC3;
			bit_t<ier1e, 7>	GTCIE3;
			typedef io8<base + 0x1f> ier1f;
			bit_t<ier1f, 0>	GTCIV3;
		};
		static ier_t<0x00087200> IER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IPR レジスタ @n
					全て、下位４ビットが有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ipr_t {
			io8<base + 0> BUSERR;

			io8<base + 1> FIFERR;
			io8<base + 2> FRDIY;

			io8<base + 3> SWINT;

			io8<base + 4> CMI0;
			io8<base + 5> CMI1;
			io8<base + 6> CMI2;
			io8<base + 7> CMI3;

			io8<base + 64> IRQ0;
			io8<base + 65> IRQ1;
			io8<base + 66> IRQ2;
			io8<base + 67> IRQ3;
			io8<base + 68> IRQ4;
			io8<base + 69> IRQ5;
			io8<base + 70> IRQ6;
			io8<base + 71> IRQ7;

			io8<base + 214> SCI0;
			io8<base + 217> SCI1;
			io8<base + 220> SCI2;
			io8<base + 223> SCI3;

			io8<base + 226> GTCIA0;
			io8<base + 226> GTCIB0;
			io8<base + 226> GTCIC0;
			io8<base + 229> GTCIE0;
			io8<base + 229> GTCIV0;
			io8<base + 229> LOCOI0;

			io8<base + 232> GTCIA1;
			io8<base + 232> GTCIB1;
			io8<base + 232> GTCIC1;
			io8<base + 235> GTCIE1;
			io8<base + 235> GTCIV1;

			io8<base + 238> GTCIA2;
			io8<base + 238> GTCIB2;
			io8<base + 238> GTCIC2;
			io8<base + 241> GTCIE2;
			io8<base + 241> GTCIV2;

			io8<base + 244> GTCIA3;
			io8<base + 244> GTCIB3;
			io8<base + 244> GTCIC3;
			io8<base + 247> GTCIE3;
			io8<base + 247> GTCIV3;
		};
		static ipr_t<0x00087300> IPR;

#if 0
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  FIR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io16<0x000872f0> fir_io;
		struct fir_t : public fir_io {
			using fir_io::operator =;
			using fir_io::operator ();
			using fir_io::operator |=;
			using fir_io::operator &=;
			
			bits_t<fir_io, 0, 8> FVCT;
			bit_t<fir_io, 15> FIEN;
		};
		static fir_t FIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SWINTR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x000872e0> swintr_io;
		struct swintr_t : public swintr_io {
			using swintr_io::operator =;
			using swintr_io::operator ();
			using swintr_io::operator |=;
			using swintr_io::operator &=;
			
			bit_t<swintr_io, 0> SWINT;
		};
		static swintr_t SWINTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DTC レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct dtc_t {

			template <uint32_t base>
			struct dtce_t : public io8<base> {
				typedef io8<base> io8_;				
				using io8_::operator =;
				using io8_::operator ();
				using io8_::operator |=;
				using io8_::operator &=;

				bit_t<io8_, 0>	DTCE;
			};
			dtce_t<0x00087100 + 27> DTCER027;
			dtce_t<0x00087100 + 28> DTCER028;
			dtce_t<0x00087100 + 29> DTCER029;
			dtce_t<0x00087100 + 30> DTCER030;
			dtce_t<0x00087100 + 31> DTCER031;

			dtce_t<0x00087100 + 36> DTCER036;
			dtce_t<0x00087100 + 37> DTCER037;

			dtce_t<0x00087100 + 40> DTCER040;
			dtce_t<0x00087100 + 41> DTCER041;

			dtce_t<0x00087100 + 45> DTCER045;
			dtce_t<0x00087100 + 46> DTCER046;

			dtce_t<0x00087100 + 49> DTCER049;
			dtce_t<0x00087100 + 50> DTCER050;

			dtce_t<0x00087100 + 64> DTCER064;
			dtce_t<0x00087100 + 65> DTCER065;
			dtce_t<0x00087100 + 66> DTCER066;
			dtce_t<0x00087100 + 67> DTCER067;
			dtce_t<0x00087100 + 68> DTCER068;
			dtce_t<0x00087100 + 69> DTCER069;
			dtce_t<0x00087100 + 70> DTCER070;
			dtce_t<0x00087100 + 71> DTCER071;
			dtce_t<0x00087100 + 72> DTCER072;
			dtce_t<0x00087100 + 73> DTCER073;
			dtce_t<0x00087100 + 74> DTCER074;
			dtce_t<0x00087100 + 75> DTCER075;
			dtce_t<0x00087100 + 76> DTCER076;
			dtce_t<0x00087100 + 77> DTCER077;
			dtce_t<0x00087100 + 78> DTCER078;
			dtce_t<0x00087100 + 79> DTCER079;

			dtce_t<0x00087100 + 98> DTCER098;
			dtce_t<0x00087100 + 99> DTCER099;

			dtce_t<0x00087100 + 102> DTCER102;

			dtce_t<0x00087100 + 114> DTCER114;
			dtce_t<0x00087100 + 115> DTCER115;
			dtce_t<0x00087100 + 116> DTCER116;
			dtce_t<0x00087100 + 117> DTCER117;

			dtce_t<0x00087100 + 121> DTCER121;
			dtce_t<0x00087100 + 122> DTCER122;

			dtce_t<0x00087100 + 125> DTCER125;
			dtce_t<0x00087100 + 126> DTCER126;

			dtce_t<0x00087100 + 129> DTCER129;
			dtce_t<0x00087100 + 130> DTCER130;
			dtce_t<0x00087100 + 131> DTCER131;
			dtce_t<0x00087100 + 132> DTCER132;
			dtce_t<0x00087100 + 133> DTCER133;
			dtce_t<0x00087100 + 134> DTCER134;
			dtce_t<0x00087100 + 135> DTCER135;
			dtce_t<0x00087100 + 136> DTCER136;
			dtce_t<0x00087100 + 137> DTCER137;
			dtce_t<0x00087100 + 138> DTCER138;
			dtce_t<0x00087100 + 139> DTCER139;
			dtce_t<0x00087100 + 140> DTCER140;
			dtce_t<0x00087100 + 141> DTCER141;
			dtce_t<0x00087100 + 142> DTCER142;
			dtce_t<0x00087100 + 143> DTCER143;
			dtce_t<0x00087100 + 144> DTCER144;
			dtce_t<0x00087100 + 145> DTCER145;

			dtce_t<0x00087100 + 149> DTCER149;
			dtce_t<0x00087100 + 150> DTCER150;

			dtce_t<0x00087100 + 153> DTCER153;
			dtce_t<0x00087100 + 154> DTCER154;

			dtce_t<0x00087100 + 157> DTCER157;
			dtce_t<0x00087100 + 158> DTCER158;
			dtce_t<0x00087100 + 159> DTCER159;
			dtce_t<0x00087100 + 160> DTCER160;

			dtce_t<0x00087100 + 162> DTCER162;
			dtce_t<0x00087100 + 163> DTCER163;
			dtce_t<0x00087100 + 164> DTCER164;
			dtce_t<0x00087100 + 165> DTCER165;
			dtce_t<0x00087100 + 166> DTCER166;
			dtce_t<0x00087100 + 167> DTCER167;
			dtce_t<0x00087100 + 168> DTCER168;
			dtce_t<0x00087100 + 169> DTCER169;

			dtce_t<0x00087100 + 174> DTCER174;
			dtce_t<0x00087100 + 175> DTCER175;

			dtce_t<0x00087100 + 177> DTCER177;
			dtce_t<0x00087100 + 178> DTCER178;

			dtce_t<0x00087100 + 180> DTCER180;
			dtce_t<0x00087100 + 181> DTCER181;

			dtce_t<0x00087100 + 183> DTCER183;
			dtce_t<0x00087100 + 184> DTCER184;

			dtce_t<0x00087100 + 198> DTCER198;
			dtce_t<0x00087100 + 199> DTCER199;
			dtce_t<0x00087100 + 200> DTCER200;
			dtce_t<0x00087100 + 201> DTCER201;
			dtce_t<0x00087100 + 202> DTCER202;
			dtce_t<0x00087100 + 203> DTCER203;

			dtce_t<0x00087100 + 215> DTCER215;
			dtce_t<0x00087100 + 216> DTCER216;

			dtce_t<0x00087100 + 219> DTCER219;

			dtce_t<0x00087100 + 220> DTCER220;

			dtce_t<0x00087100 + 223> DTCER223;
			dtce_t<0x00087100 + 224> DTCER224;

			dtce_t<0x00087100 + 227> DTCER227;
			dtce_t<0x00087100 + 228> DTCER228;

			dtce_t<0x00087100 + 235> DTCER235;
			dtce_t<0x00087100 + 236> DTCER236;

			dtce_t<0x00087100 + 239> DTCER239;
			dtce_t<0x00087100 + 240> DTCER240;

			dtce_t<0x00087100 + 247> DTCER247;
			dtce_t<0x00087100 + 248> DTCER248;

			dtce_t<0x00087100 + 251> DTCER251;
			dtce_t<0x00087100 + 252> DTCER252;
		};
		static dtc_t DTC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMACA レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct dmaca_t {
			io8<0x00087400 + 0x00> DMRSR0;
			io8<0x00087400 + 0x04> DMRSR1;
			io8<0x00087400 + 0x08> DMRSR2;
			io8<0x00087400 + 0x0c> DMRSR3;
		};
		static dmaca_t DMACA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqcr_t : public io8<base> {
			typedef io8<base> io8_;
			using io8_::operator =;
			using io8_::operator ();
			using io8_::operator |=;
			using io8_::operator &=;

			bits_t<io8_, 2, 2>	IRQMD;
		};
		static irqcr_t<0x00087500 + 0x00> IRQCR0;
		static irqcr_t<0x00087500 + 0x01> IRQCR1;
		static irqcr_t<0x00087500 + 0x02> IRQCR2;
		static irqcr_t<0x00087500 + 0x03> IRQCR3;
		static irqcr_t<0x00087500 + 0x04> IRQCR4;
		static irqcr_t<0x00087500 + 0x05> IRQCR5;
		static irqcr_t<0x00087500 + 0x06> IRQCR6;
		static irqcr_t<0x00087500 + 0x07> IRQCR7;
		static irqcr_t<0x00087500 + 0x08> IRQCR8;
		static irqcr_t<0x00087500 + 0x09> IRQCR9;
		static irqcr_t<0x00087500 + 0x0a> IRQCR10;
		static irqcr_t<0x00087500 + 0x0b> IRQCR11;
		static irqcr_t<0x00087500 + 0x0c> IRQCR12;
		static irqcr_t<0x00087500 + 0x0d> IRQCR13;
		static irqcr_t<0x00087500 + 0x0e> IRQCR14;
		static irqcr_t<0x00087500 + 0x0f> IRQCR15;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMISR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x00087580> nmisr_io;
		struct nmisr_t : public nmisr_io {
			using nmisr_io::operator =;
			using nmisr_io::operator ();
			using nmisr_io::operator |=;
			using nmisr_io::operator &=;

			bit_t<nmisr_io, 0>	NMIST;
			bit_t<nmisr_io, 1>	LVDST;
			bit_t<nmisr_io, 2>	OSTST;
		};
		static nmisr_t NMISR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMIER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x00087581> nmier_io;
		struct nmier_t : public nmier_io {
			using nmier_io::operator =;
			using nmier_io::operator ();
			using nmier_io::operator |=;
			using nmier_io::operator &=;

			bit_t<nmier_io, 0>	NMIEN;
			bit_t<nmier_io, 1>	LVDEN;
			bit_t<nmier_io, 2>	OSTEN;
		};
		static nmier_t NMIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMICLR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x00087582> nmiclr_io;
		struct nmiclr_t : public nmiclr_io {
			using nmiclr_io::operator =;
			using nmiclr_io::operator ();
			using nmiclr_io::operator |=;
			using nmiclr_io::operator &=;

			bit_t<nmiclr_io, 0>	NMICLR;
			bit_t<nmiclr_io, 2>	OSTCLR;
		};
		static nmiclr_t NMICLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMICR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<0x00087583> nmicr_io;
		struct nmicr_t : public nmicr_io {
			using nmicr_io::operator =;
			using nmicr_io::operator ();
			using nmicr_io::operator |=;
			using nmicr_io::operator &=;

			bit_t<nmicr_io, 3>	NMIMD;
		};
		static nmicr_t NMICR;
#endif
	};
	typedef icu_t ICU;
}
