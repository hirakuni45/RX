#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ EPTPC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
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
		static miesr_t<0x000C4000>  MIESR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MINT 割り込み要求許可レジスタ (MIEIPR)
		*/
		//-----------------------------------------------------------------//
		static miesr_t<0x000C4004>  MIEIPR;


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
		static elippr_t<0x000C4010>  ELIPPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ELC 出力 /IPLS 割り込み許可自動クリア設定レジスタ (ELIPACR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static elippr_t<0x000C4010>  ELIPACR;


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
		static stsr_t<0x000C4040>  STSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  STCA ステータス通知許可レジスタ (STIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static stsr_t<0x000C4044>  STIPR;


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
		static stcfr_t<0x000C4050>  STCFR;


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
		static stmr_t<0x000C4054>  STMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Sync メッセージ受信タイムアウトレジスタ (SYNTOR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4058> SYNTOR;


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
		static iptselr_t<0x000C4060>  IPTSELR;


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
		static mitselr_t<0x000C4064>  MITSELR;


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
		static eltselr_t<0x000C4068>  ELTSELR;


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
		static stchselr_t<0x000C406C>  STCHSELR;


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
		static synstartr_t<0x000C4080>  SYNSTARTR;


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
		static lcivldr_t<0x000C4084>  LCIVLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ U (SYNTDARU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4090> SYNTDARU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ L (SYNTDARL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4094> SYNTDARL;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ U (SYNTDBRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4098> SYNTDBRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ L (SYNTDBRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C409C> SYNTDBRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ U (LCIVRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C40B0> LCIVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ M (LCIVRM)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C40B4> LCIVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ L (LCIVRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C40B8> LCIVRL;


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
		static getw10r_t<0x000C4124>  GETW10R;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ U (PLIMITRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4128> PLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ M (PLIMITRM)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C412C> PLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ L (PLIMITRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4130> PLIMITRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ U (MLIMITRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4134> MLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ M (MLIMITRM)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4138> MLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ L (MLIMITRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C413C> MLIMITRL;


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
		static getinfor_t<0x000C4140>  GETINFOR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ U (LCCVRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4170> LCCVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ M (LCCVRM)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4174> LCCVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ L (LCCVRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4178> LCCVRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ U (PW10VRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4210> PW10VRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ M (PW10VRM)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4214> PW10VRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ L (PW10VRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4218> PW10VRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ U (MW10RU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C42D0> MW10RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ M (MW10RM)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C42D4> MW10RM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ L (MW10RL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C42D8> MW10RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRUm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4300> TMSTTRU0;
		static rw32_t<0x000C4310> TMSTTRU1;
		static rw32_t<0x000C4320> TMSTTRU2;
		static rw32_t<0x000C4330> TMSTTRU3;
		static rw32_t<0x000C4340> TMSTTRU4;
		static rw32_t<0x000C4350> TMSTTRU5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRLm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4304> TMSTTRL0;
		static rw32_t<0x000C4314> TMSTTRL1;
		static rw32_t<0x000C4324> TMSTTRL2;
		static rw32_t<0x000C4334> TMSTTRL3;
		static rw32_t<0x000C4344> TMSTTRL4;
		static rw32_t<0x000C4354> TMSTTRL5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ周期設定レジスタ m (TMCYCRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4308> TMCYCR0;
		static rw32_t<0x000C4318> TMCYCR1;
		static rw32_t<0x000C4328> TMCYCR2;
		static rw32_t<0x000C4338> TMCYCR3;
		static rw32_t<0x000C4348> TMCYCR4;
		static rw32_t<0x000C4358> TMCYCR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマパルス幅設定レジスタ m (TMPLSRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C430C> TMPLSR0;
		static rw32_t<0x000C431C> TMPLSR1;
		static rw32_t<0x000C432C> TMPLSR2;
		static rw32_t<0x000C433C> TMPLSR3;
		static rw32_t<0x000C434C> TMPLSR4;
		static rw32_t<0x000C435C> TMPLSR5;


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
		static tmstartr_t<0x000C437C>  TMSTARTR;


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
		static prsr_t<0x000C4400>  PRSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PRC-TC ステータス通知許可レジスタ (PRIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static prsr_t<0x000C4404>  PRIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ U (PRMACRU0)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4410> PRMACRU0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ L (PRMACRL0)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4414> PRMACRL0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ U (PRMACRU1)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4418> PRMACRU1;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ L (PRMACRL1)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C441C> PRMACRL1;


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
		static trndisr_t<0x000C4420>  TRNDISR;


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
		static trnmr_t<0x000C4430>  TRNMR;


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
		static trncttdr_t<0x000C4434>  TRNCTTDR;


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
		static ptrstr_t<0x000C0500>  PTRSTR;


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
		static stcselr_t<0x000C0504>  STCSELR;
	};


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
		static sysr_t<0x000C4800 + ofs>  SYSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ステータス通知許可レジスタ (SYIPR)
		*/
		//-----------------------------------------------------------------//
		static sysr_t<0x000C4804 + ofs>  SYIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ U (SYMACRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4810 + ofs> SYMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ L (SYMACRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4814 + ofs> SYMACRL;


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
		static syllcctlr_t<0x000C4818 + ofs>  SYLLCCTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局 IP アドレスレジスタ (SYIPADDRR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C481C + ofs> SYIPADDRR;


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
		static syspvrr_t<0x000C4840 + ofs>  SYSPVRR;


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
		static sydomr_t<0x000C4844 + ofs>  SYDOMR;


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
		static anfr_t<0x000C4850 + ofs>  ANFR;


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
		static synfr_t<0x000C4854 + ofs>  SYNFR;


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
		static dyrqfr_t<0x000C4858 + ofs>  DYRQFR;


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
		static dyrpfr_t<0x000C485C + ofs>  DYRPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ U (SYCIDRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4860 + ofs> SYCIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ L (SYCIDRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4864 + ofs> SYCIDRL;


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
		static sypnumr_t<0x000C4868 + ofs>  SYPNUMR;


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
		static syrvldr_t<0x000C4880 + ofs>  SYRVLDR;


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
		static syrfl1r_t<0x000C4890 + ofs>  SYRFL1R;


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
		static syrfl2r_t<0x000C4894 + ofs>  SYRFL2R;


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
		static sytrenr_t<0x000C4894 + ofs>  SYTRENR;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ U (MTCIDU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48A0 + ofs> MTCIDU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ L (MTCIDL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48A4 + ofs> MTCIDL;


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
		static mtpid_t<0x000C48A8 + ofs>  MTPID;


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
		static sytlir_t<0x000C48C0 + ofs>  SYTLIR;


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
		static syrlir_t<0x000C48C4 + ofs>  SYRLIR;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ U (OFMRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48C8 + ofs> OFMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ L (OFMRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48CC + ofs> OFMRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ U (MPDRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48D0 + ofs> MPDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ L (MPDRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48D4 + ofs> MPDRL;


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
		static gmpr_t<0x000C48E0 + ofs>  GMPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterClockQuality フィールド設定レジスタ (GMCQR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48E4 + ofs> GMCQR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ U (GMIDRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48E8 + ofs> GMIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ L (GMIDRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C48EC + ofs> GMIDRL;


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
		static cuotsr_t<0x000C48F0 + ofs>  CUOTSR;


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
		static srr_t<0x000C48F4 + ofs>  SRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ U (PPMACRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4900 + ofs> PPMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ L (PPMACRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4904 + ofs> PPMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ U (PDMACRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4908 + ofs> PDMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ L (PDMACRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C490C + ofs> PDMACRL;


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
		static petyper_t<0x000C4910 + ofs>  PETYPER;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 IP アドレス設定レジスタ (PPIPR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4920 + ofs> PPIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用宛先 IP アドレス設定レジスタ (PDIPR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4924 + ofs> PDIPR;


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
		static petosr_t<0x000C4928 + ofs>  PETOSR;


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
		static pgtosr_t<0x000C492C + ofs>  PGTOSR;


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
		static ppttlr_t<0x000C4930 + ofs>  PPTTLR;


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
		static pdttlr_t<0x000C4934 + ofs>  PDTTLR;


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
		static peudpr_t<0x000C4938 + ofs>  PEUDPR;


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
		static pgudpr_t<0x000C493C + ofs>  PGUDPR;


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
		static ffltr_t<0x000C4940 + ofs>  FFLTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ U (FMAC0RU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4960 + ofs> FMAC0RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ L (FMAC0RL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4964 + ofs> FMAC0RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ U (FMAC1RU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C4968 + ofs> FMAC1RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ L (FMAC1RL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C496C + ofs> FMAC1RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ U (DASYMRU)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C49C0 + ofs> DASYMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ L (DASYMRL)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C49C4 + ofs> DASYMRL;


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
		static tslatr_t<0x000C49C8 + ofs>  TSLATR;


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
		static syconfr_t<0x000C49CC + ofs>  SYCONFR;


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
		static syformr_t<0x000C49D0 + ofs>  SYFORMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	レスポンスメッセージ受信タイムアウトレジスタ (RSTOUTR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C49D4 + ofs> RSTOUTR;
	};
	typedef eptpc_t<peripheral::EPTPC> EPTPC;
	typedef eptpcx_t<0x000, peripheral::EPTPC0> EPTPC0;
	typedef eptpcx_t<0x400, peripheral::EPTPC1> EPTPC1;
}
