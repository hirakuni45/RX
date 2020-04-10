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

		//-----------------------------------------------------------------//
		/*!
			@brief  MINT 割り込み要因ステータスレジスタ (MIESR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct miesr_t_ : public rw32_t<base> {
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
		typedef miesr_t_<0x000C4000> miesr_t;
		static miesr_t MIESR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MINT 割り込み要求許可レジスタ (MIEIPR)
		*/
		//-----------------------------------------------------------------//
		typedef miesr_t_<0x000C4004> mieipr_t;
		static mieipr_t MIEIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ELC 出力 /IPLS 割り込み要求許可レジスタ (ELIPPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct elippr_t_ : public rw32_t<base> {
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
		typedef elippr_t_<0x000C4010> elippr_t;
		static elippr_t ELIPPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ELC 出力 /IPLS 割り込み許可自動クリア設定レジスタ (ELIPACR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		typedef elippr_t_<0x000C4010> elipacr_t;
		static elipacr_t ELIPACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  STCA ステータスレジスタ (STSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stsr_t_ : public rw32_t<base> {
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
		typedef stsr_t_<0x000C4040> stsr_t;
		static stsr_t STSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  STCA ステータス通知許可レジスタ (STIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		typedef stsr_t_<0x000C4044> stipr_t;
		static stipr_t STIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	STCA クロック周波数設定レジスタ (STCFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stcfr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  STCF;
		};
		typedef stcfr_t_<0x000C4050> stcfr_t;
		static stcfr_t STCFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	STCA 動作モードレジスタ (STMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stmr_t_ : public rw32_t<base> {
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
		typedef stmr_t_<0x000C4054> stmr_t;
		static stmr_t STMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Sync メッセージ受信タイムアウトレジスタ (SYNTOR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4058> syntor_t;
		static syntor_t SYNTOR;


		//-----------------------------------------------------------------//
		/*!
			@brief	IPLS 割り込み要求タイマ選択レジスタ (IPTSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct iptselr_t_ : public rw32_t<base> {
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
		typedef iptselr_t_<0x000C4060> iptselr_t;
		static iptselr_t IPTSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MINT 割り込み要求タイマ選択レジスタ (MITSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mitselr_t_ : public rw32_t<base> {
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
		typedef mitselr_t_<0x000C4064> mitselr_t;
		static mitselr_t MITSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ELC 出力タイマ選択レジスタ (ELTSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct eltselr_t_ : public rw32_t<base> {
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
		typedef eltselr_t_<0x000C4068> eltselr_t;
		static eltselr_t ELTSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	時刻同期チャネル選択レジスタ (STCHSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stchselr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SYSEL;
		};
		typedef stchselr_t_<0x000C406C> stchselr_t;
		static stchselr_t STCHSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	スレーブ時刻同期スタートレジスタ (SYNSTARTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct synstartr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  STR;
		};
		typedef synstartr_t_<0x000C4080> synstartr_t;
		static synstartr_t SYNSTARTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値ロード指示レジスタ (LCIVLDR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lcivldr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  LOAD;
		};
		typedef lcivldr_t_<0x000C4084> lcivldr_t;
		static lcivldr_t LCIVLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ U (SYNTDARU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4090> syntdaru_t;
		static syntdaru_t SYNTDARU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期外れ検出しきい値レジスタ L (SYNTDARL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4094> syntdarl_t;
		static syntdarl_t SYNTDARL;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ U (SYNTDBRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4098> syntdbru_t;
		static syntdbru_t SYNTDBRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	同期検出しきい値レジスタ L (SYNTDBRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C409C> syntdbrl_t;
		static syntdbrl_t SYNTDBRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ U (LCIVRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C40B0> lcivru_t;
		static lcivru_t LCIVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ M (LCIVRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C40B4> lcivrm_t;
		static lcivrm_t LCIVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ初期値レジスタ L (LCIVRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C40B8> lcivrl_t;
		static lcivrl_t LCIVRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ワースト 10 値取得指示レジスタ (GETW10R)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct getw10r_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GW10;
		};
		typedef getw10r_t_<0x000C4124> getw10r_t;
		static getw10r_t GETW10R;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ U (PLIMITRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4128> plimitru_t;
		static plimitru_t PLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ M (PLIMITRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C412C> plimitrm_t;
		static plimitrm_t PLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾き制限値レジスタ L (PLIMITRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4130> plimitrl_t;
		static plimitrl_t PLIMITRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ U (MLIMITRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4134> mlimitru_t;
		static mlimitru_t MLIMITRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ M (MLIMITRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4138> mlimitrm_t;
		static mlimitrm_t MLIMITRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾き制限値レジスタ L (MLIMITRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C413C> mlimitrl_t;
		static mlimitrl_t MLIMITRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	統計情報表示指示レジスタ (GETINFOR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct getinfor_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  INFO;
		};
		typedef getinfor_t_<0x000C4140> getinfor_t;
		static getinfor_t GETINFOR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ U (LCCVRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4170> lccvru_t;
		static lccvru_t LCCVRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ M (LCCVRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4174> lccvrm_t;
		static lccvrm_t LCCVRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	ローカルクロックカウンタ L (LCCVRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4178> lccvrl_t;
		static lccvrl_t LCCVRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ U (PW10VRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4210> pw10vru_t;
		static pw10vru_t PW10VRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ M (PW10VRM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4214> pw10vrm_t;
		static pw10vrm_t PW10VRM;


		//-----------------------------------------------------------------//
		/*!
			@brief	プラス側傾きワースト 10 値レジスタ L (PW10VRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4218> pw10vrl_t;
		static pw10vrl_t PW10VRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ U (MW10RU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C42D0> mw10ru_t;
		static mw10ru_t MW10RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ M (MW10RM)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C42D4> mw10rm_t;
		static mw10rm_t MW10RM;


		//-----------------------------------------------------------------//
		/*!
			@brief	マイナス側傾きワースト 10 値レジスタ L (MW10RL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C42D8> mw10rl_t;
		static mw10rl_t MW10RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRUm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4300> tmsttru0_t;
		static tmsttru0_t TMSTTRU0;
		typedef rw32_t<0x000C4310> tmsttru1_t;
		static tmsttru1_t TMSTTRU1;
		typedef rw32_t<0x000C4320> tmsttru2_t;
		static tmsttru2_t TMSTTRU2;
		typedef rw32_t<0x000C4330> tmsttru3_t;
		static tmsttru3_t TMSTTRU3;
		typedef rw32_t<0x000C4340> tmsttru4_t;
		static tmsttru4_t TMSTTRU4;
		typedef rw32_t<0x000C4350> tmsttru5_t;
		static tmsttru5_t TMSTTRU5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタート時刻設定レジスタ m (TMSTTRLm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4304> tmsttrl0_t;
		static tmsttrl0_t TMSTTRL0;
		typedef rw32_t<0x000C4314> tmsttrl1_t;
		static tmsttrl1_t TMSTTRL1;
		typedef rw32_t<0x000C4324> tmsttrl2_t;
		static tmsttrl2_t TMSTTRL2;
		typedef rw32_t<0x000C4334> tmsttrl3_t;
		static tmsttrl3_t TMSTTRL3;
		typedef rw32_t<0x000C4344> tmsttrl4_t;
		static tmsttrl4_t TMSTTRL4;
		typedef rw32_t<0x000C4354> tmsttrl5_t;
		static tmsttrl5_t TMSTTRL5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ周期設定レジスタ m (TMCYCRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4308> tmcycr0_t;
		static tmcycr0_t TMCYCR0;
		typedef rw32_t<0x000C4318> tmcycr1_t;
		static tmcycr1_t TMCYCR1;
		typedef rw32_t<0x000C4328> tmcycr2_t;
		static tmcycr2_t TMCYCR2;
		typedef rw32_t<0x000C4338> tmcycr3_t;
		static tmcycr3_t TMCYCR3;
		typedef rw32_t<0x000C4348> tmcycr4_t;
		static tmcycr4_t TMCYCR4;
		typedef rw32_t<0x000C4358> tmcycr5_t;
		static tmcycr5_t TMCYCR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマパルス幅設定レジスタ m (TMPLSRm) (m=0~5)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C430C> tmplsr0_t;
		static tmplsr0_t TMPLSR0;
		typedef rw32_t<0x000C431C> tmplsr1_t;
		static tmplsr1_t TMPLSR1;
		typedef rw32_t<0x000C432C> tmplsr2_t;
		static tmplsr2_t TMPLSR2;
		typedef rw32_t<0x000C433C> tmplsr3_t;
		static tmplsr3_t TMPLSR3;
		typedef rw32_t<0x000C434C> tmplsr4_t;
		static tmplsr4_t TMPLSR4;
		typedef rw32_t<0x000C435C> tmplsr5_t;
		static tmplsr5_t TMPLSR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ (TMSTARTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tmstartr_t_ : public rw32_t<base> {
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
		typedef tmstartr_t_<0x000C437C> tmstartr_t;
		static tmstartr_t TMSTARTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PRC-TC ステータスレジスタ (PRSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct prsr_t_ : public rw32_t<base> {
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
		typedef prsr_t_<0x000C4400> prsr_t;
		static prsr_t PRSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PRC-TC ステータス通知許可レジスタ (PRIPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		typedef prsr_t_<0x000C4404> pripr_t;
		static pripr_t PRIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ U (PRMACRU0)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4410> prmacru0_t;
		static prmacru0_t PRMACRU0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 0 自局 MAC アドレスレジスタ L (PRMACRL0)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4414> prmacrl0_t;
		static prmacrl0_t PRMACRL0;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ U (PRMACRU1)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4418> prmacru1_t;
		static prmacru1_t PRMACRU1;


		//-----------------------------------------------------------------//
		/*!
			@brief	チャネル 1 自局 MAC アドレスレジスタ L (PRMACRL1)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C441C> prmacrl1_t;
		static prmacrl1_t PRMACRL1;


		//-----------------------------------------------------------------//
		/*!
			@brief	パケット送信抑止制御レジスタ (TRNDISR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct trndisr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TDIS;
		};
		typedef trndisr_t_<0x000C4420> trndisr_t;
		static trndisr_t TRNDISR;


		//-----------------------------------------------------------------//
		/*!
			@brief	中継モードレジスタ (TRNMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct trnmr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MOD;

			bit_rw_t<io_, bitpos::B8>  FWD0;
			bit_rw_t<io_, bitpos::B9>  FWD1;
		};
		typedef trnmr_t_<0x000C4430> trnmr_t;
		static trnmr_t TRNMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	カットスルー転送開始しきい値レジスタ (TRNCTTDR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct trncttdr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11>  THVAL;
		};
		typedef trncttdr_t_<0x000C4434> trncttdr_t;
		static trncttdr_t TRNCTTDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP リセットレジスタ (PTRSTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ptrstr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   RESET;
		};
		typedef ptrstr_t_<0x000C0500> ptrstr_t;
		static ptrstr_t PTRSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	STCA クロック選択レジスタ (STCSELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct stcselr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   SCLKDIV;

			bits_rw_t<io_, bitpos::B8, 3>   SCLKSEL;
		};
		typedef stcselr_t_<0x000C0504> stcselr_t;
		static stcselr_t STCSELR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
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

		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ステータスレジスタ (SYSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sysr_t_ : public rw32_t<base> {
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
		typedef sysr_t_<0x000C4800 + ofs> sysr_t;
		static sysr_t SYSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ステータス通知許可レジスタ (SYIPR)
		*/
		//-----------------------------------------------------------------//
		typedef sysr_t_<0x000C4804 + ofs> syipr_t;
		static syipr_t SYIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ U (SYMACRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4810 + ofs> symacru_t;
		static symacru_t SYMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP MAC アドレスレジスタ L (SYMACRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4814 + ofs> symacrl_t;
		static symacrl_t SYMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP LLC-CTL 値レジスタ (SYLLCCTLR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syllcctlr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  CTL;
		};
		typedef syllcctlr_t_<0x000C4818 + ofs> syllcctlr_t;
		static syllcctlr_t SYLLCCTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局 IP アドレスレジスタ (SYIPADDRR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C481C + ofs> syipaddrr_t;
		static syipaddrr_t SYIPADDRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 仕様・バージョン設定レジスタ (SYSPVRR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syspvrr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  VER;
			bits_rw_t<io_, bitpos::B4, 4>  TRSP;
		};
		typedef syspvrr_t_<0x000C4840 + ofs> syspvrr_t;
		static syspvrr_t SYSPVRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP ドメイン番号設定レジスタ (SYDOMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sydomr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  DNUM;
		};
		typedef sydomr_t_<0x000C4844 + ofs> sydomr_t;
		static sydomr_t SYDOMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	アナウンスメッセージフラグフィールド設定レジスタ (ANFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct anfr_t_ : public rw32_t<base> {
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
		typedef anfr_t_<0x000C4850 + ofs> anfr_t;
		static anfr_t ANFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Sync メッセージフラグフィールド設定レジスタ (SYNFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct synfr_t_ : public rw32_t<base> {
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
		typedef synfr_t_<0x000C4854 + ofs> synfr_t;
		static synfr_t SYNFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Delay_Req メッセージフラグフィールド設定レジスタ (DYRQFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dyrqfr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B10>  FLAG10;

			bit_rw_t<io_, bitpos::B13>  FLAG13;
			bit_rw_t<io_, bitpos::B14>  FLAG14;
		};
		typedef dyrqfr_t_<0x000C4858 + ofs> dyrqfr_t;
		static dyrqfr_t DYRQFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	Delay_Resp メッセージフラグフィールド設定レジスタ (DYRPFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dyrpfr_t_ : public rw32_t<base> {
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
		typedef dyrpfr_t_<0x000C485C + ofs> dyrpfr_t;
		static dyrpfr_t DYRPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ U (SYCIDRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4860 + ofs> sycidru_t;
		static sycidru_t SYCIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局クロック ID レジスタ L (SYCIDRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4864 + ofs> sycidrl_t;
		static sycidrl_t SYCIDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 自局ポート番号レジスタ (SYPNUMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sypnumr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   PNUM;
		};
		typedef sypnumr_t_<0x000C4868 + ofs> sypnumr_t;
		static sypnumr_t SYPNUMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP レジスタ値ロード指示レジスタ (SYRVLDR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrvldr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   BMIP;
			bit_rw_t<io_, bitpos::B1>   STUP;
			bit_rw_t<io_, bitpos::B2>   ANUP;
		};
		typedef syrvldr_t_<0x000C4880 + ofs> syrvldr_t;
		static syrvldr_t SYRVLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 受信フィルタレジスタ 1 (SYRFL1R)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrfl1r_t_ : public rw32_t<base> {
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
		typedef syrfl1r_t_<0x000C4890 + ofs> syrfl1r_t;
		static syrfl1r_t SYRFL1R;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 受信フィルタレジスタ 2 (SYRFL2R)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrfl2r_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  MAN;
			bits_rw_t<io_, bitpos::B4,  2>  SIG;
			bits_rw_t<io_, bitpos::B28, 2>  ILL;
		};
		typedef syrfl2r_t_<0x000C4894 + ofs> syrfl2r_t;
		static syrfl2r_t SYRFL2R;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 送信許可レジスタ (SYTRENR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sytrenr_t_ : public rw32_t<base> {
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
		typedef sytrenr_t_<0x000C4894 + ofs> sytrenr_t;
		static sytrenr_t SYTRENR;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ U (MTCIDU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48A0 + ofs> mtcidu_t;
		static mtcidu_t MTCIDU;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロック ID レジスタ L (MTCIDL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48A4 + ofs> mtcidl_t;
		static mtcidl_t MTCIDL;


		//-----------------------------------------------------------------//
		/*!
			@brief	マスタクロックポート番号レジスタ (MTPID)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mtpid_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  PNUM;
		};
		typedef mtpid_t_<0x000C48A8 + ofs> mtpid_t;
		static mtpid_t MTPID;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 送信間隔設定レジスタ (SYTLIR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sytlir_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  ANCE;
			bits_rw_t<io_, bitpos::B8,  8>  SYNC;
			bits_rw_t<io_, bitpos::B16, 8>  DREQ;
		};
		typedef sytlir_t_<0x000C48C0 + ofs> sytlir_t;
		static sytlir_t SYTLIR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 受信 logMessageIntervel 値表示レジスタ (SYRLIR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syrlir_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  ANCE;
			bits_rw_t<io_, bitpos::B8,  8>  SYNC;
			bits_rw_t<io_, bitpos::B16, 8>  DRESP;
		};
		typedef syrlir_t_<0x000C48C4 + ofs> syrlir_t;
		static syrlir_t SYRLIR;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ U (OFMRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48C8 + ofs> ofmru_t;
		static ofmru_t OFMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	offsetFromMaster 値レジスタ L (OFMRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48CC + ofs> ofmrl_t;
		static ofmrl_t OFMRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ U (MPDRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48D0 + ofs> mpdru_t;
		static mpdru_t MPDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	meanPathDelay 値レジスタ L (MPDRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48D4 + ofs> mpdrl_t;
		static mpdrl_t MPDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterPriority フィールド設定レジスタ (GMPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct gmpr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  GMPR2;

			bits_rw_t<io_, bitpos::B16, 8>  GMPR1;
		};
		typedef gmpr_t_<0x000C48E0 + ofs> gmpr_t;
		static gmpr_t GMPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterClockQuality フィールド設定レジスタ (GMCQR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48E4 + ofs> gmcqr_t;
		static gmcqr_t GMCQR;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ U (GMIDRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48E8 + ofs> gmidru_t;
		static gmidru_t GMIDRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	grandmasterIdentity フィールド設定レジスタ L (GMIDRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C48EC + ofs> gmidrl_t;
		static gmidrl_t GMIDRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	currentUtcOffset/timeSource フィールド設定レジスタ (CUOTSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cuotsr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>   TSRC;

			bits_rw_t<io_, bitpos::B16, 16>  CUTO;
		};
		typedef cuotsr_t_<0x000C48F0 + ofs> cuotsr_t;
		static cuotsr_t CUOTSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	stepsRemoved フィールド設定レジスタ (SRR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct srr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   SRMV;
		};
		typedef srr_t_<0x000C48F4 + ofs> srr_t;
		static srr_t SRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ U (PPMACRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4900 + ofs> ppmacru_t;
		static ppmacru_t PPMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 MAC アドレス設定レジスタ L (PPMACRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4904 + ofs> ppmacrl_t;
		static ppmacrl_t PPMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ U (PDMACRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4908 + ofs> pdmacru_t;
		static pdmacru_t PDMACRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 MAC アドレス設定レジスタ L (PDMACRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C490C + ofs> pdmacrl_t;
		static pdmacrl_t PDMACRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP メッセージ EtherType 設定レジスタ (PETYPER)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct petyper_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   TYPE;
		};
		typedef petyper_t_<0x000C4910 + ofs> petyper_t;
		static petyper_t PETYPER;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用宛先 IP アドレス設定レジスタ (PPIPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4920 + ofs> ppipr_t;
		static ppipr_t PPIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用宛先 IP アドレス設定レジスタ (PDIPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4924 + ofs> pdipr_t;
		static pdipr_t PDIPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP event メッセージ用 TOS 設定レジスタ (PETOSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct petosr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   EVTO;
		};
		typedef petosr_t_<0x000C4928 + ofs> petosr_t;
		static petosr_t PETOSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP general メッセージ用 TOS 設定レジスタ (PGTOSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pgtosr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   GETO;
		};
		typedef pgtosr_t_<0x000C492C + ofs> pgtosr_t;
		static pgtosr_t PGTOSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-primary メッセージ用 TTL 設定レジスタ (PPTTLR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ppttlr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   PRTL;
		};
		typedef ppttlr_t_<0x000C4930 + ofs> ppttlr_t;
		static ppttlr_t PPTTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP-pdelay メッセージ用 TTL 設定レジスタ (PDTTLR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pdttlr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   PDTL;
		};
		typedef pdttlr_t_<0x000C4934 + ofs> pdttlr_t;
		static pdttlr_t PDTTLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP event メッセージ用 UDP 宛先ポート番号設定レジスタ (PEUDPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct peudpr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   EVUPT;
		};
		typedef peudpr_t_<0x000C4938 + ofs> peudpr_t;
		static peudpr_t PEUDPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	PTP general メッセージ用 UDP 宛先ポート番号設定レジスタ (PGUDPR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pgudpr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   GEUPT;
		};
		typedef pgudpr_t_<0x000C493C + ofs> pgudpr_t;
		static pgudpr_t PGUDPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ設定レジスタ (FFLTR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ffltr_t_ : public rw32_t<base> {
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
		typedef ffltr_t_<0x000C4940 + ofs> ffltr_t;
		static ffltr_t FFLTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ U (FMAC0RU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4960 + ofs> fmac0ru_t;
		static fmac0ru_t FMAC0RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 0 設定レジスタ L (FMAC0RL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4964 + ofs> fmac0rl_t;
		static fmac0rl_t FMAC0RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ U (FMAC1RU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C4968 + ofs> fmac1ru_t;
		static fmac1ru_t FMAC1RU;


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム受信フィルタ用 MAC アドレス 1 設定レジスタ L (FMAC1RL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C496C + ofs> fmac1rl_t;
		static fmac1rl_t FMAC1RL;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ U (DASYMRU)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C49C0 + ofs> dasymru_t;
		static dasymru_t DASYMRU;


		//-----------------------------------------------------------------//
		/*!
			@brief	非対称遅延値設定レジスタ L (DASYMRL)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C49C4 + ofs> dasymrl_t;
		static dasymrl_t DASYMRL;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイムスタンプ遅延値設定レジスタ (TSLATR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tslatr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  EGP;
			bits_rw_t<io_, bitpos::B16, 16>  INGP;
		};
		typedef tslatr_t_<0x000C49C8 + ofs> tslatr_t;
		static tslatr_t TSLATR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP 動作設定レジスタ (SYCONFR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syconfr_t_ : public rw32_t<base> {
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
		typedef syconfr_t_<0x000C49CC + ofs> syconfr_t;
		static syconfr_t SYCONFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	SYNFP フレームフォーマット設定レジスタ (SYFORMR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syformr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   FORM0;
			bit_rw_t <io_, bitpos::B1>   FORM1;
		};
		typedef syformr_t_<0x000C49D0 + ofs> syformr_t;
		static syformr_t SYFORMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	レスポンスメッセージ受信タイムアウトレジスタ (RSTOUTR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C49D4 + ofs> rstoutr_t;
		static rstoutr_t RSTOUTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};
	typedef eptpc_t<peripheral::EPTPC> EPTPC;
	typedef eptpcx_t<0x000, peripheral::EPTPC0> EPTPC0;
	typedef eptpcx_t<0x400, peripheral::EPTPC1> EPTPC1;

	template<peripheral per> typename eptpc_t<per>::miesr_t eptpc_t<per>::MIESR;
	template<peripheral per> typename eptpc_t<per>::mieipr_t eptpc_t<per>::MIEIPR;
	template<peripheral per> typename eptpc_t<per>::elippr_t eptpc_t<per>::ELIPPR;
	template<peripheral per> typename eptpc_t<per>::elipacr_t eptpc_t<per>::ELIPACR;
	template<peripheral per> typename eptpc_t<per>::stsr_t eptpc_t<per>::STSR;
	template<peripheral per> typename eptpc_t<per>::stipr_t eptpc_t<per>::STIPR;
	template<peripheral per> typename eptpc_t<per>::stcfr_t eptpc_t<per>::STCFR;
	template<peripheral per> typename eptpc_t<per>::stmr_t eptpc_t<per>::STMR;
	template<peripheral per> typename eptpc_t<per>::syntor_t eptpc_t<per>::SYNTOR;
	template<peripheral per> typename eptpc_t<per>::iptselr_t eptpc_t<per>::IPTSELR;
	template<peripheral per> typename eptpc_t<per>::mitselr_t eptpc_t<per>::MITSELR;
	template<peripheral per> typename eptpc_t<per>::eltselr_t eptpc_t<per>::ELTSELR;
	template<peripheral per> typename eptpc_t<per>::stchselr_t eptpc_t<per>::STCHSELR;
	template<peripheral per> typename eptpc_t<per>::synstartr_t eptpc_t<per>::SYNSTARTR;
	template<peripheral per> typename eptpc_t<per>::lcivldr_t eptpc_t<per>::LCIVLDR;
	template<peripheral per> typename eptpc_t<per>::syntdaru_t eptpc_t<per>::SYNTDARU;
	template<peripheral per> typename eptpc_t<per>::syntdarl_t eptpc_t<per>::SYNTDARL;
	template<peripheral per> typename eptpc_t<per>::syntdbru_t eptpc_t<per>::SYNTDBRU;
	template<peripheral per> typename eptpc_t<per>::syntdbrl_t eptpc_t<per>::SYNTDBRL;
	template<peripheral per> typename eptpc_t<per>::lcivru_t eptpc_t<per>::LCIVRU;
	template<peripheral per> typename eptpc_t<per>::lcivrm_t eptpc_t<per>::LCIVRM;
	template<peripheral per> typename eptpc_t<per>::lcivrl_t eptpc_t<per>::LCIVRL;
	template<peripheral per> typename eptpc_t<per>::getw10r_t eptpc_t<per>::GETW10R;
	template<peripheral per> typename eptpc_t<per>::plimitru_t eptpc_t<per>::PLIMITRU;
	template<peripheral per> typename eptpc_t<per>::plimitrm_t eptpc_t<per>::PLIMITRM;
	template<peripheral per> typename eptpc_t<per>::plimitrl_t eptpc_t<per>::PLIMITRL;
	template<peripheral per> typename eptpc_t<per>::mlimitru_t eptpc_t<per>::MLIMITRU;
	template<peripheral per> typename eptpc_t<per>::mlimitrm_t eptpc_t<per>::MLIMITRM;
	template<peripheral per> typename eptpc_t<per>::mlimitrl_t eptpc_t<per>::MLIMITRL;
	template<peripheral per> typename eptpc_t<per>::getinfor_t eptpc_t<per>::GETINFOR;
	template<peripheral per> typename eptpc_t<per>::lccvru_t eptpc_t<per>::LCCVRU;
	template<peripheral per> typename eptpc_t<per>::lccvrm_t eptpc_t<per>::LCCVRM;
	template<peripheral per> typename eptpc_t<per>::lccvrl_t eptpc_t<per>::LCCVRL;
	template<peripheral per> typename eptpc_t<per>::pw10vru_t eptpc_t<per>::PW10VRU;
	template<peripheral per> typename eptpc_t<per>::pw10vrm_t eptpc_t<per>::PW10VRM;
	template<peripheral per> typename eptpc_t<per>::pw10vrl_t eptpc_t<per>::PW10VRL;
	template<peripheral per> typename eptpc_t<per>::mw10ru_t eptpc_t<per>::MW10RU;
	template<peripheral per> typename eptpc_t<per>::mw10rm_t eptpc_t<per>::MW10RM;
	template<peripheral per> typename eptpc_t<per>::mw10rl_t eptpc_t<per>::MW10RL;
	template<peripheral per> typename eptpc_t<per>::tmsttru0_t eptpc_t<per>::TMSTTRU0;
	template<peripheral per> typename eptpc_t<per>::tmsttru1_t eptpc_t<per>::TMSTTRU1;
	template<peripheral per> typename eptpc_t<per>::tmsttru2_t eptpc_t<per>::TMSTTRU2;
	template<peripheral per> typename eptpc_t<per>::tmsttru3_t eptpc_t<per>::TMSTTRU3;
	template<peripheral per> typename eptpc_t<per>::tmsttru4_t eptpc_t<per>::TMSTTRU4;
	template<peripheral per> typename eptpc_t<per>::tmsttru5_t eptpc_t<per>::TMSTTRU5;
	template<peripheral per> typename eptpc_t<per>::tmsttrl0_t eptpc_t<per>::TMSTTRL0;
	template<peripheral per> typename eptpc_t<per>::tmsttrl1_t eptpc_t<per>::TMSTTRL1;
	template<peripheral per> typename eptpc_t<per>::tmsttrl2_t eptpc_t<per>::TMSTTRL2;
	template<peripheral per> typename eptpc_t<per>::tmsttrl3_t eptpc_t<per>::TMSTTRL3;
	template<peripheral per> typename eptpc_t<per>::tmsttrl4_t eptpc_t<per>::TMSTTRL4;
	template<peripheral per> typename eptpc_t<per>::tmsttrl5_t eptpc_t<per>::TMSTTRL5;
	template<peripheral per> typename eptpc_t<per>::tmcycr0_t eptpc_t<per>::TMCYCR0;
	template<peripheral per> typename eptpc_t<per>::tmcycr1_t eptpc_t<per>::TMCYCR1;
	template<peripheral per> typename eptpc_t<per>::tmcycr2_t eptpc_t<per>::TMCYCR2;
	template<peripheral per> typename eptpc_t<per>::tmcycr3_t eptpc_t<per>::TMCYCR3;
	template<peripheral per> typename eptpc_t<per>::tmcycr4_t eptpc_t<per>::TMCYCR4;
	template<peripheral per> typename eptpc_t<per>::tmcycr5_t eptpc_t<per>::TMCYCR5;
	template<peripheral per> typename eptpc_t<per>::tmplsr0_t eptpc_t<per>::TMPLSR0;
	template<peripheral per> typename eptpc_t<per>::tmplsr1_t eptpc_t<per>::TMPLSR1;
	template<peripheral per> typename eptpc_t<per>::tmplsr2_t eptpc_t<per>::TMPLSR2;
	template<peripheral per> typename eptpc_t<per>::tmplsr3_t eptpc_t<per>::TMPLSR3;
	template<peripheral per> typename eptpc_t<per>::tmplsr4_t eptpc_t<per>::TMPLSR4;
	template<peripheral per> typename eptpc_t<per>::tmplsr5_t eptpc_t<per>::TMPLSR5;
	template<peripheral per> typename eptpc_t<per>::tmstartr_t eptpc_t<per>::TMSTARTR;
	template<peripheral per> typename eptpc_t<per>::prsr_t eptpc_t<per>::PRSR;
	template<peripheral per> typename eptpc_t<per>::pripr_t eptpc_t<per>::PRIPR;
	template<peripheral per> typename eptpc_t<per>::prmacru0_t eptpc_t<per>::PRMACRU0;
	template<peripheral per> typename eptpc_t<per>::prmacrl0_t eptpc_t<per>::PRMACRL0;
	template<peripheral per> typename eptpc_t<per>::prmacru1_t eptpc_t<per>::PRMACRU1;
	template<peripheral per> typename eptpc_t<per>::prmacrl1_t eptpc_t<per>::PRMACRL1;
	template<peripheral per> typename eptpc_t<per>::trndisr_t eptpc_t<per>::TRNDISR;
	template<peripheral per> typename eptpc_t<per>::trnmr_t eptpc_t<per>::TRNMR;
	template<peripheral per> typename eptpc_t<per>::trncttdr_t eptpc_t<per>::TRNCTTDR;
	template<peripheral per> typename eptpc_t<per>::ptrstr_t eptpc_t<per>::PTRSTR;
	template<peripheral per> typename eptpc_t<per>::stcselr_t eptpc_t<per>::STCSELR;

	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::sysr_t eptpcx_t<ofs, per>::SYSR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syipr_t eptpcx_t<ofs, per>::SYIPR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::symacru_t eptpcx_t<ofs, per>::SYMACRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::symacrl_t eptpcx_t<ofs, per>::SYMACRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syllcctlr_t eptpcx_t<ofs, per>::SYLLCCTLR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syipaddrr_t eptpcx_t<ofs, per>::SYIPADDRR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syspvrr_t eptpcx_t<ofs, per>::SYSPVRR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::sydomr_t eptpcx_t<ofs, per>::SYDOMR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::anfr_t eptpcx_t<ofs, per>::ANFR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::synfr_t eptpcx_t<ofs, per>::SYNFR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::dyrqfr_t eptpcx_t<ofs, per>::DYRQFR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::dyrpfr_t eptpcx_t<ofs, per>::DYRPFR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::sycidru_t eptpcx_t<ofs, per>::SYCIDRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::sycidrl_t eptpcx_t<ofs, per>::SYCIDRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::sypnumr_t eptpcx_t<ofs, per>::SYPNUMR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syrvldr_t eptpcx_t<ofs, per>::SYRVLDR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syrfl1r_t eptpcx_t<ofs, per>::SYRFL1R;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syrfl2r_t eptpcx_t<ofs, per>::SYRFL2R;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::sytrenr_t eptpcx_t<ofs, per>::SYTRENR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::mtcidu_t eptpcx_t<ofs, per>::MTCIDU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::mtcidl_t eptpcx_t<ofs, per>::MTCIDL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::mtpid_t eptpcx_t<ofs, per>::MTPID;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::sytlir_t eptpcx_t<ofs, per>::SYTLIR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syrlir_t eptpcx_t<ofs, per>::SYRLIR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::ofmru_t eptpcx_t<ofs, per>::OFMRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::ofmrl_t eptpcx_t<ofs, per>::OFMRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::mpdru_t eptpcx_t<ofs, per>::MPDRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::mpdrl_t eptpcx_t<ofs, per>::MPDRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::gmpr_t eptpcx_t<ofs, per>::GMPR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::gmcqr_t eptpcx_t<ofs, per>::GMCQR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::gmidru_t eptpcx_t<ofs, per>::GMIDRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::gmidrl_t eptpcx_t<ofs, per>::GMIDRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::cuotsr_t eptpcx_t<ofs, per>::CUOTSR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::srr_t eptpcx_t<ofs, per>::SRR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::ppmacru_t eptpcx_t<ofs, per>::PPMACRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::ppmacrl_t eptpcx_t<ofs, per>::PPMACRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::pdmacru_t eptpcx_t<ofs, per>::PDMACRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::pdmacrl_t eptpcx_t<ofs, per>::PDMACRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::petyper_t eptpcx_t<ofs, per>::PETYPER;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::ppipr_t eptpcx_t<ofs, per>::PPIPR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::pdipr_t eptpcx_t<ofs, per>::PDIPR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::petosr_t eptpcx_t<ofs, per>::PETOSR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::pgtosr_t eptpcx_t<ofs, per>::PGTOSR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::ppttlr_t eptpcx_t<ofs, per>::PPTTLR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::pdttlr_t eptpcx_t<ofs, per>::PDTTLR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::peudpr_t eptpcx_t<ofs, per>::PEUDPR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::pgudpr_t eptpcx_t<ofs, per>::PGUDPR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::ffltr_t eptpcx_t<ofs, per>::FFLTR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::fmac0ru_t eptpcx_t<ofs, per>::FMAC0RU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::fmac0rl_t eptpcx_t<ofs, per>::FMAC0RL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::fmac1ru_t eptpcx_t<ofs, per>::FMAC1RU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::fmac1rl_t eptpcx_t<ofs, per>::FMAC1RL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::dasymru_t eptpcx_t<ofs, per>::DASYMRU;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::dasymrl_t eptpcx_t<ofs, per>::DASYMRL;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::tslatr_t eptpcx_t<ofs, per>::TSLATR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syconfr_t eptpcx_t<ofs, per>::SYCONFR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::syformr_t eptpcx_t<ofs, per>::SYFORMR;
	template<uint32_t ofs, peripheral per> typename eptpcx_t<ofs, per> ::rstoutr_t eptpcx_t<ofs, per>::RSTOUTR;
}
