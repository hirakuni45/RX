#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ EPTPC 定義 @n
			RX72M/RX72N グループ EPTPCb
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	イーサネットコントローラ用 PTP コントローラ (EPTPC)
		@param[in]	per	ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct eptpc_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  MINT 割り込み要因ステータスレジスタ (MIESR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct miesr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ST;
			bit_rw_t<io_, bitpos::B1>   SY0;
			bit_rw_t<io_, bitpos::B2>   SY1;
			bit_rw_t<io_, bitpos::B3>   PRC;

			bit_rw_t<io_, bitpos::B16>  CYC0;
			bit_rw_t<io_, bitpos::B17>  CYC1;
			bit_rw_t<io_, bitpos::B18>  CYC2;
			bit_rw_t<io_, bitpos::B19>  CYC3;
			bit_rw_t<io_, bitpos::B20>  CYC4;
			bit_rw_t<io_, bitpos::B21>  CYC5;
		};
		typedef miesr_t<0x000C4000>  MIESR_;
		static  MIESR_ MIESR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MINT 割り込み要求許可レジスタ (MIEIPR)
		*/
		//-----------------------------------------------------------------//
		typedef miesr_t<0x000C4004>  MIEIPR_;
		static  MIEIPR_ MIEIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ELC 出力 /IPLS 割り込み要求許可レジスタ (ELIPPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct elippr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   CYCP0;
			bit_rw_t<io_, bitpos::B1>   CYCP1;
			bit_rw_t<io_, bitpos::B2>   CYCP2;
			bit_rw_t<io_, bitpos::B3>   CYCP3;
			bit_rw_t<io_, bitpos::B4>   CYCP4;
			bit_rw_t<io_, bitpos::B5>   CYCP5;

			bit_rw_t<io_, bitpos::B8>   CYCN0;
			bit_rw_t<io_, bitpos::B9>   CYCN1;
			bit_rw_t<io_, bitpos::B10>  CYCN2;
			bit_rw_t<io_, bitpos::B11>  CYCN3;
			bit_rw_t<io_, bitpos::B12>  CYCN4;
			bit_rw_t<io_, bitpos::B13>  CYCN5;

			bit_rw_t<io_, bitpos::B16>  PLSP;

			bit_rw_t<io_, bitpos::B24>  PLSN;
		};
		typedef elippr_t<0x000C4010>  ELIPPR_;
		static  ELIPPR_ ELIPPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ELC 出力 /IPLS 割り込み許可自動クリア設定レジスタ (ELIPACR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		typedef elippr_t<0x000C4010>  ELIPACR_;
		static  ELIPACR_ ELIPACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  STCA ステータスレジスタ (STSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stsr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SYNC;
			bit_rw_t<io_, bitpos::B1>  SYNCOUT;

			bit_rw_t<io_, bitpos::B3>  SYNTOUT;
			bit_rw_t<io_, bitpos::B4>  W10D;
		};
		typedef stsr_t<0x000C4040>  STSR_;
		static  STSR_ STSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  STCA ステータス通知許可レジスタ (STIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		typedef stsr_t<0x000C4044>  STIPR_;
		static  STIPR_ STIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	STCA クロック周波数設定レジスタ (STCFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stcfr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  STCF;
		};
		typedef stcfr_t<0x000C4050>  STCFR_;
		static  STCFR_ STCFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	STCA 動作モードレジスタ (STMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stmr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  WINT;

			bit_rw_t <io_, bitpos::B13>     CMOD;

			bit_rw_t <io_, bitpos::B15>     W10S;
			bits_rw_t<io_, bitpos::B16, 4>  SYTH;
			bits_rw_t<io_, bitpos::B20, 4>  DVTH;

			bit_rw_t <io_, bitpos::B28>     ALEN0;
			bit_rw_t <io_, bitpos::B29>     ALEN1;
		};
		typedef stmr_t<0x000C4054>  STMR_;
		static  STMR_ STMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Sync メッセージ受信タイムアウトレジスタ (SYNTOR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4058> SYNTOR_;
		static  SYNTOR_ SYNTOR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IPLS 割り込み要求タイマ選択レジスタ (IPTSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct iptselr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  IPTSEL0;
			bit_rw_t<io_, bitpos::B1>  IPTSEL1;
			bit_rw_t<io_, bitpos::B2>  IPTSEL2;
			bit_rw_t<io_, bitpos::B3>  IPTSEL3;
			bit_rw_t<io_, bitpos::B4>  IPTSEL4;
			bit_rw_t<io_, bitpos::B5>  IPTSEL5;
		};
		typedef iptselr_t<0x000C4060>  IPTSELR_;
		static  IPTSELR_ IPTSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MINT 割り込み要求タイマ選択レジスタ (MITSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mitselr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MINTEN0;
			bit_rw_t<io_, bitpos::B1>  MINTEN1;
			bit_rw_t<io_, bitpos::B2>  MINTEN2;
			bit_rw_t<io_, bitpos::B3>  MINTEN3;
			bit_rw_t<io_, bitpos::B4>  MINTEN4;
			bit_rw_t<io_, bitpos::B5>  MINTEN5;
		};
		typedef mitselr_t<0x000C4064>  MITSELR_;
		static  MITSELR_ MITSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ELC 出力タイマ選択レジスタ (ELTSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct eltselr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ELTDIS0;
			bit_rw_t<io_, bitpos::B1>  ELTDIS1;
			bit_rw_t<io_, bitpos::B2>  ELTDIS2;
			bit_rw_t<io_, bitpos::B3>  ELTDIS3;
			bit_rw_t<io_, bitpos::B4>  ELTDIS4;
			bit_rw_t<io_, bitpos::B5>  ELTDIS5;
		};
		typedef eltselr_t<0x000C4068>  ELTSELR_;
		static  ELTSELR_ ELTSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	時刻同期チャネル選択レジスタ (STCHSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stchselr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SYSEL;
		};
		typedef stchselr_t<0x000C406C>  STCHSELR_;
		static  STCHSELR_ STCHSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	スレーブ時刻同期スタートレジスタ (SYNSTARTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct synstartr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  STR;
		};
		typedef synstartr_t<0x000C4080>  SYNSTARTR_;
		static  SYNSTARTR_ SYNSTARTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値ロード指示レジスタ (LCIVLDR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lcivldr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  LOAD;
		};
		typedef lcivldr_t<0x000C4084>  LCIVLDR_;
		static  LCIVLDR_ LCIVLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ U (SYNTDARU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4090> SYNTDARU_;
		static  SYNTDARU_ SYNTDARU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ L (SYNTDARL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4094> SYNTDARL_;
		static  SYNTDARL_ SYNTDARL;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ U (SYNTDBRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4098> SYNTDBRU_;
		static  SYNTDBRU_ SYNTDBRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ L (SYNTDBRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C409C> SYNTDBRL_;
		static  SYNTDBRL_ SYNTDBRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ U (LCIVRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C40B0> LCIVRU_;
		static  LCIVRU_ LCIVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ M (LCIVRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C40B4> LCIVRM_;
		static  LCIVRM_ LCIVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ L (LCIVRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C40B8> LCIVRL_;
		static  LCIVRL_ LCIVRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ワースト 10 値取得指示レジスタ (GETW10R)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct getw10r_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GW10;
		};
		typedef getw10r_t<0x000C4124>  GETW10R_;
		static  GETW10R_ GETW10R;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ U (PLIMITRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4128> PLIMITRU_;
		static  PLIMITRU_ PLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ M (PLIMITRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C412C> PLIMITRM_;
		static  PLIMITRM_ PLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ L (PLIMITRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4130> PLIMITRL_;
		static  PLIMITRL_ PLIMITRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ U (MLIMITRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4134> MLIMITRU_;
		static  MLIMITRU_ MLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ M (MLIMITRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4138> MLIMITRM_;
		static  MLIMITRM_ MLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ L (MLIMITRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C413C> MLIMITRL_;
		static  MLIMITRL_ MLIMITRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	統計情報表示指示レジスタ (GETINFOR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct getinfor_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  INFO;
		};
		typedef getinfor_t<0x000C4140>  GETINFOR_;
		static  GETINFOR_ GETINFOR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ U (LCCVRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4170> LCCVRU_;
		static  LCCVRU_ LCCVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ M (LCCVRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4174> LCCVRM_;
		static  LCCVRM_ LCCVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ L (LCCVRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4178> LCCVRL_;
		static  LCCVRL_ LCCVRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ U (PW10VRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4210> PW10VRU_;
		static  PW10VRU_ PW10VRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ M (PW10VRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4214> PW10VRM_;
		static  PW10VRM_ PW10VRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ L (PW10VRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4218> PW10VRL_;
		static  PW10VRL_ PW10VRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ U (MW10RU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C42D0> MW10RU_;
		static  MW10RU_ MW10RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ M (MW10RM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C42D4> MW10RM_;
		static  MW10RM_ MW10RM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ L (MW10RL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C42D8> MW10RL_;
		static  MW10RL_ MW10RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRUm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4300> TMSTTRU0_;
		static  TMSTTRU0_ TMSTTRU0;
		typedef rw32_t<0x000C4310> TMSTTRU1_;
		static  TMSTTRU1_ TMSTTRU1;
		typedef rw32_t<0x000C4320> TMSTTRU2_;
		static  TMSTTRU2_ TMSTTRU2;
		typedef rw32_t<0x000C4330> TMSTTRU3_;
		static  TMSTTRU3_ TMSTTRU3;
		typedef rw32_t<0x000C4340> TMSTTRU4_;
		static  TMSTTRU4_ TMSTTRU4;
		typedef rw32_t<0x000C4350> TMSTTRU5_;
		static  TMSTTRU5_ TMSTTRU5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRLm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4304> TMSTTRL0_;
		static  TMSTTRL0_ TMSTTRL0;
		typedef rw32_t<0x000C4314> TMSTTRL1_;
		static  TMSTTRL1_ TMSTTRL1;
		typedef rw32_t<0x000C4324> TMSTTRL2_;
		static  TMSTTRL2_ TMSTTRL2;
		typedef rw32_t<0x000C4334> TMSTTRL3_;
		static  TMSTTRL3_ TMSTTRL3;
		typedef rw32_t<0x000C4344> TMSTTRL4_;
		static  TMSTTRL4_ TMSTTRL4;
		typedef rw32_t<0x000C4354> TMSTTRL5_;
		static  TMSTTRL5_ TMSTTRL5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ周期設定レジスタ m (TMCYCRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4308> TMCYCR0_;
		static  TMCYCR0_ TMCYCR0;
		typedef rw32_t<0x000C4318> TMCYCR1_;
		static  TMCYCR1_ TMCYCR1;
		typedef rw32_t<0x000C4328> TMCYCR2_;
		static  TMCYCR2_ TMCYCR2;
		typedef rw32_t<0x000C4338> TMCYCR3_;
		static  TMCYCR3_ TMCYCR3;
		typedef rw32_t<0x000C4348> TMCYCR4_;
		static  TMCYCR4_ TMCYCR4;
		typedef rw32_t<0x000C4358> TMCYCR5_;
		static  TMCYCR5_ TMCYCR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマパルス幅設定レジスタ m (TMPLSRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C430C> TMPLSR0_;
		static  TMPLSR0_ TMPLSR0;
		typedef rw32_t<0x000C431C> TMPLSR1_;
		static  TMPLSR1_ TMPLSR1;
		typedef rw32_t<0x000C432C> TMPLSR2_;
		static  TMPLSR2_ TMPLSR2;
		typedef rw32_t<0x000C433C> TMPLSR3_;
		static  TMPLSR3_ TMPLSR3;
		typedef rw32_t<0x000C434C> TMPLSR4_;
		static  TMPLSR4_ TMPLSR4;
		typedef rw32_t<0x000C435C> TMPLSR5_;
		static  TMPLSR5_ TMPLSR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ (TMSTARTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tmstartr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  EN0;
			bit_rw_t<io_, bitpos::B1>  EN1;
			bit_rw_t<io_, bitpos::B2>  EN2;
			bit_rw_t<io_, bitpos::B3>  EN3;
			bit_rw_t<io_, bitpos::B4>  EN4;
			bit_rw_t<io_, bitpos::B5>  EN5;
		};
		typedef tmstartr_t<0x000C437C>  TMSTARTR_;
		static  TMSTARTR_ TMSTARTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PRC-TC ステータスレジスタ (PRSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct prsr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   OVRE0;
			bit_rw_t<io_, bitpos::B1>   OVRE1;
			bit_rw_t<io_, bitpos::B2>   OVRE2;
			bit_rw_t<io_, bitpos::B3>   OVRE3;

			bit_rw_t<io_, bitpos::B8>   MACE;

			bit_rw_t<io_, bitpos::B28>  URE0;
			bit_rw_t<io_, bitpos::B29>  URE1;
		};
		typedef prsr_t<0x000C4400>  PRSR_;
		static  PRSR_ PRSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PRC-TC ステータス通知許可レジスタ (PRIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		typedef prsr_t<0x000C4404>  PRIPR_;
		static  PRIPR_ PRIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ U (PRMACRU0)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4410> PRMACRU0_;
		static  PRMACRU0_ PRMACRU0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ L (PRMACRL0)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4414> PRMACRL0_;
		static  PRMACRL0_ PRMACRL0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ U (PRMACRU1)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4418> PRMACRU1_;
		static  PRMACRU1_ PRMACRU1;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ L (PRMACRL1)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C441C> PRMACRL1_;
		static  PRMACRL1_ PRMACRL1;


		//-----------------------------------------------------------------//
		/*!
			@brief	パケット送信抑止制御レジスタ (TRNDISR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct trndisr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TDIS;
		};
		typedef trndisr_t<0x000C4420>  TRNDISR_;
		static  TRNDISR_ TRNDISR;


		//-----------------------------------------------------------------//
		/*!
			@brief	中継モードレジスタ (TRNMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct trnmr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MOD;

			bit_rw_t<io_, bitpos::B8>  FWD0;
			bit_rw_t<io_, bitpos::B9>  FWD1;
		};
		typedef trnmr_t<0x000C4430>  TRNMR_;
		static  TRNMR_ TRNMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	カットスルー転送開始しきい値レジスタ (TRNCTTDR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct trncttdr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11>  THVAL;
		};
		typedef trncttdr_t<0x000C4434>  TRNCTTDR_;
		static  TRNCTTDR_ TRNCTTDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP リセットレジスタ (PTRSTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ptrstr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   RESET;
		};
		typedef ptrstr_t<0x000C0500>  PTRSTR_;
		static  PTRSTR_ PTRSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	STCA クロック選択レジスタ (STCSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stcselr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   SCLKDIV;

			bits_rw_t<io_, bitpos::B8, 3>   SCLKSEL;
		};
		typedef stcselr_t<0x000C0504>  STCSELR_;
		static  STCSELR_ STCSELR;
	};
	template <peripheral per> typename eptpc_t<per>::MIESR_ eptpc_t<per>::MIESR;
	template <peripheral per> typename eptpc_t<per>::MIEIPR_ eptpc_t<per>::MIEIPR;
	template <peripheral per> typename eptpc_t<per>::ELIPPR_ eptpc_t<per>::ELIPPR;
	template <peripheral per> typename eptpc_t<per>::ELIPACR_ eptpc_t<per>::ELIPACR;
	template <peripheral per> typename eptpc_t<per>::STSR_ eptpc_t<per>::STSR;
	template <peripheral per> typename eptpc_t<per>::STIPR_ eptpc_t<per>::STIPR;
	template <peripheral per> typename eptpc_t<per>::STCFR_ eptpc_t<per>::STCFR;
	template <peripheral per> typename eptpc_t<per>::STMR_ eptpc_t<per>::STMR;
	template <peripheral per> typename eptpc_t<per>::SYNTOR_ eptpc_t<per>::SYNTOR;
	template <peripheral per> typename eptpc_t<per>::IPTSELR_ eptpc_t<per>::IPTSELR;
	template <peripheral per> typename eptpc_t<per>::MITSELR_ eptpc_t<per>::MITSELR;
	template <peripheral per> typename eptpc_t<per>::ELTSELR_ eptpc_t<per>::ELTSELR;
	template <peripheral per> typename eptpc_t<per>::STCHSELR_ eptpc_t<per>::STCHSELR;
	template <peripheral per> typename eptpc_t<per>::SYNSTARTR_ eptpc_t<per>::SYNSTARTR;
	template <peripheral per> typename eptpc_t<per>::LCIVLDR_ eptpc_t<per>::LCIVLDR;
	template <peripheral per> typename eptpc_t<per>::SYNTDARU_ eptpc_t<per>::SYNTDARU;
	template <peripheral per> typename eptpc_t<per>::SYNTDARL_ eptpc_t<per>::SYNTDARL;
	template <peripheral per> typename eptpc_t<per>::SYNTDBRU_ eptpc_t<per>::SYNTDBRU;
	template <peripheral per> typename eptpc_t<per>::SYNTDBRL_ eptpc_t<per>::SYNTDBRL;
	template <peripheral per> typename eptpc_t<per>::LCIVRU_ eptpc_t<per>::LCIVRU;
	template <peripheral per> typename eptpc_t<per>::LCIVRM_ eptpc_t<per>::LCIVRM;
	template <peripheral per> typename eptpc_t<per>::LCIVRL_ eptpc_t<per>::LCIVRL;
	template <peripheral per> typename eptpc_t<per>::GETW10R_ eptpc_t<per>::GETW10R;
	template <peripheral per> typename eptpc_t<per>::PLIMITRU_ eptpc_t<per>::PLIMITRU;
	template <peripheral per> typename eptpc_t<per>::PLIMITRM_ eptpc_t<per>::PLIMITRM;
	template <peripheral per> typename eptpc_t<per>::PLIMITRL_ eptpc_t<per>::PLIMITRL;
	template <peripheral per> typename eptpc_t<per>::MLIMITRU_ eptpc_t<per>::MLIMITRU;
	template <peripheral per> typename eptpc_t<per>::MLIMITRM_ eptpc_t<per>::MLIMITRM;
	template <peripheral per> typename eptpc_t<per>::MLIMITRL_ eptpc_t<per>::MLIMITRL;
	template <peripheral per> typename eptpc_t<per>::GETINFOR_ eptpc_t<per>::GETINFOR;
	template <peripheral per> typename eptpc_t<per>::LCCVRU_ eptpc_t<per>::LCCVRU;
	template <peripheral per> typename eptpc_t<per>::LCCVRM_ eptpc_t<per>::LCCVRM;
	template <peripheral per> typename eptpc_t<per>::LCCVRL_ eptpc_t<per>::LCCVRL;
	template <peripheral per> typename eptpc_t<per>::PW10VRU_ eptpc_t<per>::PW10VRU;
	template <peripheral per> typename eptpc_t<per>::PW10VRM_ eptpc_t<per>::PW10VRM;
	template <peripheral per> typename eptpc_t<per>::PW10VRL_ eptpc_t<per>::PW10VRL;
	template <peripheral per> typename eptpc_t<per>::MW10RU_ eptpc_t<per>::MW10RU;
	template <peripheral per> typename eptpc_t<per>::MW10RM_ eptpc_t<per>::MW10RM;
	template <peripheral per> typename eptpc_t<per>::MW10RL_ eptpc_t<per>::MW10RL;
	template <peripheral per> typename eptpc_t<per>::TMSTTRU0_ eptpc_t<per>::TMSTTRU0;
	template <peripheral per> typename eptpc_t<per>::TMSTTRU1_ eptpc_t<per>::TMSTTRU1;
	template <peripheral per> typename eptpc_t<per>::TMSTTRU2_ eptpc_t<per>::TMSTTRU2;
	template <peripheral per> typename eptpc_t<per>::TMSTTRU3_ eptpc_t<per>::TMSTTRU3;
	template <peripheral per> typename eptpc_t<per>::TMSTTRU4_ eptpc_t<per>::TMSTTRU4;
	template <peripheral per> typename eptpc_t<per>::TMSTTRU5_ eptpc_t<per>::TMSTTRU5;
	template <peripheral per> typename eptpc_t<per>::TMSTTRL0_ eptpc_t<per>::TMSTTRL0;
	template <peripheral per> typename eptpc_t<per>::TMSTTRL1_ eptpc_t<per>::TMSTTRL1;
	template <peripheral per> typename eptpc_t<per>::TMSTTRL2_ eptpc_t<per>::TMSTTRL2;
	template <peripheral per> typename eptpc_t<per>::TMSTTRL3_ eptpc_t<per>::TMSTTRL3;
	template <peripheral per> typename eptpc_t<per>::TMSTTRL4_ eptpc_t<per>::TMSTTRL4;
	template <peripheral per> typename eptpc_t<per>::TMSTTRL5_ eptpc_t<per>::TMSTTRL5;
	template <peripheral per> typename eptpc_t<per>::TMCYCR0_ eptpc_t<per>::TMCYCR0;
	template <peripheral per> typename eptpc_t<per>::TMCYCR1_ eptpc_t<per>::TMCYCR1;
	template <peripheral per> typename eptpc_t<per>::TMCYCR2_ eptpc_t<per>::TMCYCR2;
	template <peripheral per> typename eptpc_t<per>::TMCYCR3_ eptpc_t<per>::TMCYCR3;
	template <peripheral per> typename eptpc_t<per>::TMCYCR4_ eptpc_t<per>::TMCYCR4;
	template <peripheral per> typename eptpc_t<per>::TMCYCR5_ eptpc_t<per>::TMCYCR5;
	template <peripheral per> typename eptpc_t<per>::TMPLSR0_ eptpc_t<per>::TMPLSR0;
	template <peripheral per> typename eptpc_t<per>::TMPLSR1_ eptpc_t<per>::TMPLSR1;
	template <peripheral per> typename eptpc_t<per>::TMPLSR2_ eptpc_t<per>::TMPLSR2;
	template <peripheral per> typename eptpc_t<per>::TMPLSR3_ eptpc_t<per>::TMPLSR3;
	template <peripheral per> typename eptpc_t<per>::TMPLSR4_ eptpc_t<per>::TMPLSR4;
	template <peripheral per> typename eptpc_t<per>::TMPLSR5_ eptpc_t<per>::TMPLSR5;
	template <peripheral per> typename eptpc_t<per>::TMSTARTR_ eptpc_t<per>::TMSTARTR;
	template <peripheral per> typename eptpc_t<per>::PRSR_ eptpc_t<per>::PRSR;
	template <peripheral per> typename eptpc_t<per>::PRIPR_ eptpc_t<per>::PRIPR;
	template <peripheral per> typename eptpc_t<per>::PRMACRU0_ eptpc_t<per>::PRMACRU0;
	template <peripheral per> typename eptpc_t<per>::PRMACRL0_ eptpc_t<per>::PRMACRL0;
	template <peripheral per> typename eptpc_t<per>::PRMACRU1_ eptpc_t<per>::PRMACRU1;
	template <peripheral per> typename eptpc_t<per>::PRMACRL1_ eptpc_t<per>::PRMACRL1;
	template <peripheral per> typename eptpc_t<per>::TRNDISR_ eptpc_t<per>::TRNDISR;
	template <peripheral per> typename eptpc_t<per>::TRNMR_ eptpc_t<per>::TRNMR;
	template <peripheral per> typename eptpc_t<per>::TRNCTTDR_ eptpc_t<per>::TRNCTTDR;
	template <peripheral per> typename eptpc_t<per>::PTRSTR_ eptpc_t<per>::PTRSTR;
	template <peripheral per> typename eptpc_t<per>::STCSELR_ eptpc_t<per>::STCSELR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	イーサネットコントローラ用 PTP コントローラ x (EPTPCx)
		@param[in]	ofs	 オフセット
		@param[in]	per	ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t ofs, peripheral per>
	struct eptpcx_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ステータスレジスタ (SYSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sysr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   OFMUD;
			bit_rw_t<io_, bitpos::B1>   INTCHG;
			bit_rw_t<io_, bitpos::B2>   MPDUD;

			bit_rw_t<io_, bitpos::B4>   DRPTO;
			bit_rw_t<io_, bitpos::B5>   INTDEV;
			bit_rw_t<io_, bitpos::B6>   DRQOVR;

			bit_rw_t<io_, bitpos::B12>  RECLP;

			bit_rw_t<io_, bitpos::B14>  INFABT;

			bit_rw_t<io_, bitpos::B16>  RESDN;
			bit_rw_t<io_, bitpos::B17>  GENDN;
		};
		typedef sysr_t<0x000C4800 + ofs>  SYSR_;
		static  SYSR_ SYSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ステータス通知許可レジスタ (SYIPR)
		*/
		//-----------------------------------------------------------------//
		typedef sysr_t<0x000C4804 + ofs>  SYIPR_;
		static  SYIPR_ SYIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ U (SYMACRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4810 + ofs> SYMACRU_;
		static  SYMACRU_ SYMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ L (SYMACRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4814 + ofs> SYMACRL_;
		static  SYMACRL_ SYMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP LLC-CTL 値レジスタ (SYLLCCTLR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syllcctlr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  CTL;
		};
		typedef syllcctlr_t<0x000C4818 + ofs>  SYLLCCTLR_;
		static  SYLLCCTLR_ SYLLCCTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局 IP アドレスレジスタ (SYIPADDRR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C481C + ofs> SYIPADDRR_;
		static  SYIPADDRR_ SYIPADDRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 仕様・バージョン設定レジスタ (SYSPVRR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syspvrr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  VER;
			bits_rw_t<io_, bitpos::B4, 4>  TRSP;
		};
		typedef syspvrr_t<0x000C4840 + ofs>  SYSPVRR_;
		static  SYSPVRR_ SYSPVRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ドメイン番号設定レジスタ (SYDOMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sydomr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  DNUM;
		};
		typedef sydomr_t<0x000C4844 + ofs>  SYDOMR_;
		static  SYDOMR_ SYDOMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	アナウンスメッセージフラグフィールド設定レジスタ (ANFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct anfr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   FLAG0;
			bit_rw_t<io_, bitpos::B1>   FLAG1;
			bit_rw_t<io_, bitpos::B2>   FLAG2;
			bit_rw_t<io_, bitpos::B3>   FLAG3;
			bit_rw_t<io_, bitpos::B4>   FLAG4;
			bit_rw_t<io_, bitpos::B5>   FLAG5;

			bit_rw_t<io_, bitpos::B8>   FLAG8;

			bit_rw_t<io_, bitpos::B10>  FLAG10;

			bit_rw_t<io_, bitpos::B13>  FLAG13;
			bit_rw_t<io_, bitpos::B14>  FLAG14;
		};
		typedef anfr_t<0x000C4850 + ofs>  ANFR_;
		static  ANFR_ ANFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Sync メッセージフラグフィールド設定レジスタ (SYNFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct synfr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   FLAG8;
			bit_rw_t<io_, bitpos::B9>   FLAG9;
			bit_rw_t<io_, bitpos::B10>  FLAG10;

			bit_rw_t<io_, bitpos::B13>  FLAG13;
			bit_rw_t<io_, bitpos::B14>  FLAG14;
		};
		typedef synfr_t<0x000C4854 + ofs>  SYNFR_;
		static  SYNFR_ SYNFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Delay_Req メッセージフラグフィールド設定レジスタ (DYRQFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dyrqfr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B10>  FLAG10;

			bit_rw_t<io_, bitpos::B13>  FLAG13;
			bit_rw_t<io_, bitpos::B14>  FLAG14;
		};
		typedef dyrqfr_t<0x000C4858 + ofs>  DYRQFR_;
		static  DYRQFR_ DYRQFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Delay_Resp メッセージフラグフィールド設定レジスタ (DYRPFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dyrpfr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   FLAG8;
			bit_rw_t<io_, bitpos::B9>   FLAG9;
			bit_rw_t<io_, bitpos::B10>  FLAG10;

			bit_rw_t<io_, bitpos::B13>  FLAG13;
			bit_rw_t<io_, bitpos::B14>  FLAG14;
		};
		typedef dyrpfr_t<0x000C485C + ofs>  DYRPFR_;
		static  DYRPFR_ DYRPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ U (SYCIDRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4860 + ofs> SYCIDRU_;
		static  SYCIDRU_ SYCIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ L (SYCIDRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4864 + ofs> SYCIDRL_;
		static  SYCIDRL_ SYCIDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局ポート番号レジスタ (SYPNUMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sypnumr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   PNUM;
		};
		typedef sypnumr_t<0x000C4868 + ofs>  SYPNUMR_;
		static  SYPNUMR_ SYPNUMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP レジスタ値ロード指示レジスタ (SYRVLDR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrvldr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   BMIP;
			bit_rw_t<io_, bitpos::B1>   STUP;
			bit_rw_t<io_, bitpos::B2>   ANUP;
		};
		typedef syrvldr_t<0x000C4880 + ofs>  SYRVLDR_;
		static  SYRVLDR_ SYRVLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 受信フィルタレジスタ 1 (SYRFL1R)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrfl1r_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  ANCE;
			bits_rw_t<io_, bitpos::B4,  3>  SYNC;
			bits_rw_t<io_, bitpos::B8,  3>  FUP;
			bits_rw_t<io_, bitpos::B12, 3>  DRQ;
			bits_rw_t<io_, bitpos::B16, 3>  DRP;
			bits_rw_t<io_, bitpos::B20, 3>  PDRQ;
			bits_rw_t<io_, bitpos::B24, 3>  PDRP;
			bits_rw_t<io_, bitpos::B28, 3>  PDFUP;
		};
		typedef syrfl1r_t<0x000C4890 + ofs>  SYRFL1R_;
		static  SYRFL1R_ SYRFL1R;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 受信フィルタレジスタ 2 (SYRFL2R)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrfl2r_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  MAN;
			bits_rw_t<io_, bitpos::B4,  2>  SIG;
			bits_rw_t<io_, bitpos::B28, 2>  ILL;
		};
		typedef syrfl2r_t<0x000C4894 + ofs>  SYRFL2R_;
		static  SYRFL2R_ SYRFL2R;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 送信許可レジスタ (SYTRENR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sytrenr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ANCE;
			bit_rw_t<io_, bitpos::B4>   SYNC;
			bit_rw_t<io_, bitpos::B8>   DRQ;
			bit_rw_t<io_, bitpos::B12>  PDRQ;
		};
		typedef sytrenr_t<0x000C4894 + ofs>  SYTRENR_;
		static  SYTRENR_ SYTRENR;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ U (MTCIDU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48A0 + ofs> MTCIDU_;
		static  MTCIDU_ MTCIDU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ L (MTCIDL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48A4 + ofs> MTCIDL_;
		static  MTCIDL_ MTCIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロックポート番号レジスタ (MTPID)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mtpid_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  PNUM;
		};
		typedef mtpid_t<0x000C48A8 + ofs>  MTPID_;
		static  MTPID_ MTPID;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 送信間隔設定レジスタ (SYTLIR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sytlir_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  ANCE;
			bits_rw_t<io_, bitpos::B8,  8>  SYNC;
			bits_rw_t<io_, bitpos::B16, 8>  DREQ;
		};
		typedef sytlir_t<0x000C48C0 + ofs>  SYTLIR_;
		static  SYTLIR_ SYTLIR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 受信 logMessageIntervel 値表示レジスタ (SYRLIR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrlir_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  ANCE;
			bits_rw_t<io_, bitpos::B8,  8>  SYNC;
			bits_rw_t<io_, bitpos::B16, 8>  DRESP;
		};
		typedef syrlir_t<0x000C48C4 + ofs>  SYRLIR_;
		static  SYRLIR_ SYRLIR;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ U (OFMRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48C8 + ofs> OFMRU_;
		static  OFMRU_ OFMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ L (OFMRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48CC + ofs> OFMRL_;
		static  OFMRL_ OFMRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ U (MPDRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48D0 + ofs> MPDRU_;
		static  MPDRU_ MPDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ L (MPDRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48D4 + ofs> MPDRL_;
		static  MPDRL_ MPDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterPriority フィールド設定レジスタ (GMPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct gmpr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  GMPR2;

			bits_rw_t<io_, bitpos::B16, 8>  GMPR1;
		};
		typedef gmpr_t<0x000C48E0 + ofs>  GMPR_;
		static  GMPR_ GMPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterClockQuality フィールド設定レジスタ (GMCQR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48E4 + ofs> GMCQR_;
		static  GMCQR_ GMCQR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ U (GMIDRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48E8 + ofs> GMIDRU_;
		static  GMIDRU_ GMIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ L (GMIDRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48EC + ofs> GMIDRL_;
		static  GMIDRL_ GMIDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	currentUtcOffset/timeSource フィールド設定レジスタ (CUOTSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cuotsr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>   TSRC;

			bits_rw_t<io_, bitpos::B16, 16>  CUTO;
		};
		typedef cuotsr_t<0x000C48F0 + ofs>  CUOTSR_;
		static  CUOTSR_ CUOTSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	stepsRemoved フィールド設定レジスタ (SRR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct srr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   SRMV;
		};
		typedef srr_t<0x000C48F4 + ofs>  SRR_;
		static  SRR_ SRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ U (PPMACRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4900 + ofs> PPMACRU_;
		static  PPMACRU_ PPMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ L (PPMACRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4904 + ofs> PPMACRL_;
		static  PPMACRL_ PPMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ U (PDMACRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4908 + ofs> PDMACRU_;
		static  PDMACRU_ PDMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ L (PDMACRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C490C + ofs> PDMACRL_;
		static  PDMACRL_ PDMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP メッセージ EtherType 設定レジスタ (PETYPER)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct petyper_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   TYPE;
		};
		typedef petyper_t<0x000C4910 + ofs>  PETYPER_;
		static  PETYPER_ PETYPER;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 IP アドレス設定レジスタ (PPIPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4920 + ofs> PPIPR_;
		static  PPIPR_ PPIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用宛先 IP アドレス設定レジスタ (PDIPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4924 + ofs> PDIPR_;
		static  PDIPR_ PDIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP event メッセージ用 TOS 設定レジスタ (PETOSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct petosr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   EVTO;
		};
		typedef petosr_t<0x000C4928 + ofs>  PETOSR_;
		static  PETOSR_ PETOSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP general メッセージ用 TOS 設定レジスタ (PGTOSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pgtosr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   GETO;
		};
		typedef pgtosr_t<0x000C492C + ofs>  PGTOSR_;
		static  PGTOSR_ PGTOSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用 TTL 設定レジスタ (PPTTLR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ppttlr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   PRTL;
		};
		typedef ppttlr_t<0x000C4930 + ofs>  PPTTLR_;
		static  PPTTLR_ PPTTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 TTL 設定レジスタ (PDTTLR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pdttlr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   PDTL;
		};
		typedef pdttlr_t<0x000C4934 + ofs>  PDTTLR_;
		static  PDTTLR_ PDTTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP event メッセージ用 UDP 宛先ポート番号設定レジスタ (PEUDPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct peudpr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   EVUPT;
		};
		typedef peudpr_t<0x000C4938 + ofs>  PEUDPR_;
		static  PEUDPR_ PEUDPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP general メッセージ用 UDP 宛先ポート番号設定レジスタ (PGUDPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pgudpr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   GEUPT;
		};
		typedef pgudpr_t<0x000C493C + ofs>  PGUDPR_;
		static  PGUDPR_ PGUDPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ設定レジスタ (FFLTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ffltr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   SEL;
			bit_rw_t<io_, bitpos::B1>   PRT;
			bit_rw_t<io_, bitpos::B2>   ENB;

			bit_rw_t<io_, bitpos::B16>  EXTPRM;
		};
		typedef ffltr_t<0x000C4940 + ofs>  FFLTR_;
		static  FFLTR_ FFLTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ U (FMAC0RU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4960 + ofs> FMAC0RU_;
		static  FMAC0RU_ FMAC0RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ L (FMAC0RL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4964 + ofs> FMAC0RL_;
		static  FMAC0RL_ FMAC0RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ U (FMAC1RU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4968 + ofs> FMAC1RU_;
		static  FMAC1RU_ FMAC1RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ L (FMAC1RL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C496C + ofs> FMAC1RL_;
		static  FMAC1RL_ FMAC1RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ U (DASYMRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C49C0 + ofs> DASYMRU_;
		static  DASYMRU_ DASYMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ L (DASYMRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C49C4 + ofs> DASYMRL_;
		static  DASYMRL_ DASYMRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイムスタンプ遅延値設定レジスタ (TSLATR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tslatr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  EGP;
			bits_rw_t<io_, bitpos::B16, 16>  INGP;
		};
		typedef tslatr_t<0x000C49C8 + ofs>  TSLATR_;
		static  TSLATR_ TSLATR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 動作設定レジスタ (SYCONFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syconfr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  TCYC;

			bit_rw_t <io_, bitpos::B12>      SBDIS;

			bit_rw_t <io_, bitpos::B16>      FILDIS;

			bit_rw_t <io_, bitpos::B20>      TCMOD;
		};
		typedef syconfr_t<0x000C49CC + ofs>  SYCONFR_;
		static  SYCONFR_ SYCONFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP フレームフォーマット設定レジスタ (SYFORMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syformr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   FORM0;
			bit_rw_t <io_, bitpos::B1>   FORM1;
		};
		typedef syformr_t<0x000C49D0 + ofs>  SYFORMR_;
		static  SYFORMR_ SYFORMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	レスポンスメッセージ受信タイムアウトレジスタ (RSTOUTR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C49D4 + ofs> RSTOUTR_;
		static  RSTOUTR_ RSTOUTR;
	};
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYSR_ eptpcx_t<base, per>::SYSR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYIPR_ eptpcx_t<base, per>::SYIPR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYMACRU_ eptpcx_t<base, per>::SYMACRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYMACRL_ eptpcx_t<base, per>::SYMACRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYLLCCTLR_ eptpcx_t<base, per>::SYLLCCTLR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYIPADDRR_ eptpcx_t<base, per>::SYIPADDRR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYSPVRR_ eptpcx_t<base, per>::SYSPVRR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYDOMR_ eptpcx_t<base, per>::SYDOMR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::ANFR_ eptpcx_t<base, per>::ANFR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYNFR_ eptpcx_t<base, per>::SYNFR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::DYRQFR_ eptpcx_t<base, per>::DYRQFR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::DYRPFR_ eptpcx_t<base, per>::DYRPFR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYCIDRU_ eptpcx_t<base, per>::SYCIDRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYCIDRL_ eptpcx_t<base, per>::SYCIDRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYPNUMR_ eptpcx_t<base, per>::SYPNUMR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYRVLDR_ eptpcx_t<base, per>::SYRVLDR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYRFL1R_ eptpcx_t<base, per>::SYRFL1R;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYRFL2R_ eptpcx_t<base, per>::SYRFL2R;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYTRENR_ eptpcx_t<base, per>::SYTRENR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::MTCIDU_ eptpcx_t<base, per>::MTCIDU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::MTCIDL_ eptpcx_t<base, per>::MTCIDL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::MTPID_ eptpcx_t<base, per>::MTPID;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYTLIR_ eptpcx_t<base, per>::SYTLIR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYRLIR_ eptpcx_t<base, per>::SYRLIR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::OFMRU_ eptpcx_t<base, per>::OFMRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::OFMRL_ eptpcx_t<base, per>::OFMRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::MPDRU_ eptpcx_t<base, per>::MPDRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::MPDRL_ eptpcx_t<base, per>::MPDRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::GMPR_ eptpcx_t<base, per>::GMPR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::GMCQR_ eptpcx_t<base, per>::GMCQR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::GMIDRU_ eptpcx_t<base, per>::GMIDRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::GMIDRL_ eptpcx_t<base, per>::GMIDRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::CUOTSR_ eptpcx_t<base, per>::CUOTSR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SRR_ eptpcx_t<base, per>::SRR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PPMACRU_ eptpcx_t<base, per>::PPMACRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PPMACRL_ eptpcx_t<base, per>::PPMACRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PDMACRU_ eptpcx_t<base, per>::PDMACRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PDMACRL_ eptpcx_t<base, per>::PDMACRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PETYPER_ eptpcx_t<base, per>::PETYPER;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PPIPR_ eptpcx_t<base, per>::PPIPR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PDIPR_ eptpcx_t<base, per>::PDIPR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PETOSR_ eptpcx_t<base, per>::PETOSR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PGTOSR_ eptpcx_t<base, per>::PGTOSR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PPTTLR_ eptpcx_t<base, per>::PPTTLR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PDTTLR_ eptpcx_t<base, per>::PDTTLR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PEUDPR_ eptpcx_t<base, per>::PEUDPR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::PGUDPR_ eptpcx_t<base, per>::PGUDPR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::FFLTR_ eptpcx_t<base, per>::FFLTR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::FMAC0RU_ eptpcx_t<base, per>::FMAC0RU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::FMAC0RL_ eptpcx_t<base, per>::FMAC0RL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::FMAC1RU_ eptpcx_t<base, per>::FMAC1RU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::FMAC1RL_ eptpcx_t<base, per>::FMAC1RL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::DASYMRU_ eptpcx_t<base, per>::DASYMRU;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::DASYMRL_ eptpcx_t<base, per>::DASYMRL;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::TSLATR_ eptpcx_t<base, per>::TSLATR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYCONFR_ eptpcx_t<base, per>::SYCONFR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::SYFORMR_ eptpcx_t<base, per>::SYFORMR;
	template <uint32_t base, peripheral per> typename eptpcx_t<base, per>::RSTOUTR_ eptpcx_t<base, per>::RSTOUTR;


	typedef eptpc_t<peripheral::EPTPC> EPTPC;
	typedef eptpcx_t<0x000, peripheral::EPTPC0> EPTPC0;
	typedef eptpcx_t<0x400, peripheral::EPTPC1> EPTPC1;
}
