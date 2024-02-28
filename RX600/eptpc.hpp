#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ EPTPC 定義 @n
			RX72M/RX72N グループ EPTPCb
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
		@brief	イーサネットコントローラ用 PTP コントローラ (EPTPC)
		@param[in]	per	ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct eptpc_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

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
		static inline miesr_t<0x000C'4000>  MIESR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MINT 割り込み要求許可レジスタ (MIEIPR)
		*/
		//-----------------------------------------------------------------//
		static inline miesr_t<0x000C'4004>  MIEIPR;


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
		static inline elippr_t<0x000C'4010>  ELIPPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ELC 出力 /IPLS 割り込み許可自動クリア設定レジスタ (ELIPACR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static inline elippr_t<0x000C'4010>  ELIPACR;


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
		static inline stsr_t<0x000C'4040>  STSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  STCA ステータス通知許可レジスタ (STIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static inline stsr_t<0x000C'4044>  STIPR;


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
		static inline stcfr_t<0x000C'4050>  STCFR;


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
		static inline stmr_t<0x000C'4054>  STMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Sync メッセージ受信タイムアウトレジスタ (SYNTOR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4058> SYNTOR;


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
		static inline iptselr_t<0x000C'4060>  IPTSELR;


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
		static inline mitselr_t<0x000C'4064>  MITSELR;


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
		static inline eltselr_t<0x000C'4068>  ELTSELR;


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
		static inline stchselr_t<0x000C'406C>  STCHSELR;


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
		static inline synstartr_t<0x000C'4080>  SYNSTARTR;


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
		static inline lcivldr_t<0x000C'4084>  LCIVLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ U (SYNTDARU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4090> SYNTDARU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ L (SYNTDARL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4094> SYNTDARL;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ U (SYNTDBRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4098> SYNTDBRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ L (SYNTDBRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'409C> SYNTDBRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ U (LCIVRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'40B0> LCIVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ M (LCIVRM)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'40B4> LCIVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ L (LCIVRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'40B8> LCIVRL;


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
		static inline getw10r_t<0x000C'4124>  GETW10R;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ U (PLIMITRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4128> PLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ M (PLIMITRM)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'412C> PLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ L (PLIMITRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4130> PLIMITRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ U (MLIMITRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4134> MLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ M (MLIMITRM)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4138> MLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ L (MLIMITRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'413C> MLIMITRL;


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
		static inline getinfor_t<0x000C'4140>  GETINFOR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ U (LCCVRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4170> LCCVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ M (LCCVRM)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4174> LCCVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ L (LCCVRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4178> LCCVRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ U (PW10VRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4210> PW10VRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ M (PW10VRM)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4214> PW10VRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ L (PW10VRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4218> PW10VRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ U (MW10RU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'42D0> MW10RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ M (MW10RM)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'42D4> MW10RM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ L (MW10RL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'42D8> MW10RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRUm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4300> TMSTTRU0;
		static inline rw32_t<0x000C'4310> TMSTTRU1;
		static inline rw32_t<0x000C'4320> TMSTTRU2;
		static inline rw32_t<0x000C'4330> TMSTTRU3;
		static inline rw32_t<0x000C'4340> TMSTTRU4;
		static inline rw32_t<0x000C'4350> TMSTTRU5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRLm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4304> TMSTTRL0;
		static inline rw32_t<0x000C'4314> TMSTTRL1;
		static inline rw32_t<0x000C'4324> TMSTTRL2;
		static inline rw32_t<0x000C'4334> TMSTTRL3;
		static inline rw32_t<0x000C'4344> TMSTTRL4;
		static inline rw32_t<0x000C'4354> TMSTTRL5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ周期設定レジスタ m (TMCYCRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4308> TMCYCR0;
		static inline rw32_t<0x000C'4318> TMCYCR1;
		static inline rw32_t<0x000C'4328> TMCYCR2;
		static inline rw32_t<0x000C'4338> TMCYCR3;
		static inline rw32_t<0x000C'4348> TMCYCR4;
		static inline rw32_t<0x000C'4358> TMCYCR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマパルス幅設定レジスタ m (TMPLSRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'430C> TMPLSR0;
		static inline rw32_t<0x000C'431C> TMPLSR1;
		static inline rw32_t<0x000C'432C> TMPLSR2;
		static inline rw32_t<0x000C'433C> TMPLSR3;
		static inline rw32_t<0x000C'434C> TMPLSR4;
		static inline rw32_t<0x000C'435C> TMPLSR5;


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
		static inline tmstartr_t<0x000C'437C>  TMSTARTR;


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
		static inline prsr_t<0x000C'4400>  PRSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PRC-TC ステータス通知許可レジスタ (PRIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static inline prsr_t<0x000C'4404>  PRIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ U (PRMACRU0)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4410> PRMACRU0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ L (PRMACRL0)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4414> PRMACRL0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ U (PRMACRU1)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4418> PRMACRU1;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ L (PRMACRL1)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'441C> PRMACRL1;


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
		static inline trndisr_t<0x000C'4420>  TRNDISR;


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
		static inline trnmr_t<0x000C'4430>  TRNMR;


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
		static inline trncttdr_t<0x000C'4434>  TRNCTTDR;


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
		static inline ptrstr_t<0x000C'0500>  PTRSTR;


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
		static inline stcselr_t<0x000C'0504>  STCSELR;
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

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

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
		static inline sysr_t<0x000C'4800 + ofs>  SYSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ステータス通知許可レジスタ (SYIPR)
		*/
		//-----------------------------------------------------------------//
		static inline sysr_t<0x000C'4804 + ofs>  SYIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ U (SYMACRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4810 + ofs> SYMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ L (SYMACRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4814 + ofs> SYMACRL;


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
		static inline syllcctlr_t<0x000C'4818 + ofs>  SYLLCCTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局 IP アドレスレジスタ (SYIPADDRR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'481C + ofs> SYIPADDRR;


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
		static inline syspvrr_t<0x000C'4840 + ofs>  SYSPVRR;


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
		static inline sydomr_t<0x000C'4844 + ofs>  SYDOMR;


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
		static inline anfr_t<0x000C'4850 + ofs>  ANFR;


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
		static inline synfr_t<0x000C'4854 + ofs>  SYNFR;


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
		static inline dyrqfr_t<0x000C'4858 + ofs>  DYRQFR;


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
		static inline dyrpfr_t<0x000C'485C + ofs>  DYRPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ U (SYCIDRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4860 + ofs> SYCIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ L (SYCIDRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4864 + ofs> SYCIDRL;


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
		static inline sypnumr_t<0x000C'4868 + ofs>  SYPNUMR;


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
		static inline syrvldr_t<0x000C'4880 + ofs>  SYRVLDR;


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
		static inline syrfl1r_t<0x000C'4890 + ofs>  SYRFL1R;


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
		static inline syrfl2r_t<0x000C'4894 + ofs>  SYRFL2R;


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
		static inline sytrenr_t<0x000C'4894 + ofs>  SYTRENR;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ U (MTCIDU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48A0 + ofs> MTCIDU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ L (MTCIDL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48A4 + ofs> MTCIDL;


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
		static inline mtpid_t<0x000C'48A8 + ofs>  MTPID;


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
		static inline sytlir_t<0x000C'48C0 + ofs>  SYTLIR;


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
		static inline syrlir_t<0x000C'48C4 + ofs>  SYRLIR;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ U (OFMRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48C8 + ofs> OFMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ L (OFMRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48CC + ofs> OFMRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ U (MPDRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48D0 + ofs> MPDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ L (MPDRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48D4 + ofs> MPDRL;


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
		static inline gmpr_t<0x000C'48E0 + ofs>  GMPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterClockQuality フィールド設定レジスタ (GMCQR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48E4 + ofs> GMCQR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ U (GMIDRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48E8 + ofs> GMIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ L (GMIDRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'48EC + ofs> GMIDRL;


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
		static inline cuotsr_t<0x000C'48F0 + ofs>  CUOTSR;


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
		static inline srr_t<0x000C'48F4 + ofs>  SRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ U (PPMACRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4900 + ofs> PPMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ L (PPMACRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4904 + ofs> PPMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ U (PDMACRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4908 + ofs> PDMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ L (PDMACRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'490C + ofs> PDMACRL;


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
		static inline petyper_t<0x000C'4910 + ofs>  PETYPER;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 IP アドレス設定レジスタ (PPIPR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4920 + ofs> PPIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用宛先 IP アドレス設定レジスタ (PDIPR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4924 + ofs> PDIPR;


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
		static inline petosr_t<0x000C'4928 + ofs>  PETOSR;


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
		static inline pgtosr_t<0x000C'492C + ofs>  PGTOSR;


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
		static inline ppttlr_t<0x000C'4930 + ofs>  PPTTLR;


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
		static inline pdttlr_t<0x000C'4934 + ofs>  PDTTLR;


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
		static inline peudpr_t<0x000C'4938 + ofs>  PEUDPR;


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
		static inline pgudpr_t<0x000C'493C + ofs>  PGUDPR;


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
		static inline ffltr_t<0x000C'4940 + ofs>  FFLTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ U (FMAC0RU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4960 + ofs> FMAC0RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ L (FMAC0RL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4964 + ofs> FMAC0RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ U (FMAC1RU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'4968 + ofs> FMAC1RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ L (FMAC1RL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'496C + ofs> FMAC1RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ U (DASYMRU)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'49C0 + ofs> DASYMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ L (DASYMRL)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'49C4 + ofs> DASYMRL;


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
		static inline tslatr_t<0x000C'49C8 + ofs>  TSLATR;


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
		static inline syconfr_t<0x000C'49CC + ofs>  SYCONFR;


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
		static inline syformr_t<0x000C'49D0 + ofs>  SYFORMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	レスポンスメッセージ受信タイムアウトレジスタ (RSTOUTR)
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000C'49D4 + ofs> RSTOUTR;
	};
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef eptpc_t<peripheral::EPTPC> EPTPC;
	typedef eptpcx_t<0x000, peripheral::EPTPC0> EPTPC0;
	typedef eptpcx_t<0x400, peripheral::EPTPC1> EPTPC1;
#endif
}
