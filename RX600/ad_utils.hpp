#pragma once
//=========================================================================//
/*!	@file
	@brief	AD, S12AD Utils @n
			A/D 変換関係ユーティリティ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  AD Utils
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ad_utils {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D データレジスタ定義
			@param[in]	AN	アナログ型
			@param[in]	R0	レジスタ０アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0>
		struct addr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (AN an) noexcept
			{
				return rd16_(R0 + static_cast<uint32_t>(an) * 2);
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D データレジスタ定義（基準電圧）
			@param[in]	AN		アナログ型
			@param[in]	R0		レジスタ０アドレス
			@param[in]	RRNO	基準電圧型
			@param[in]	RR		基準電圧アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, AN RRNO, uint32_t RR> 
		struct addr_r_t {

			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (AN an) noexcept
			{
				if(an == RRNO) {
					return rd16_(RR);
				} else {
					return rd16_(R0 + static_cast<uint32_t>(an) * 2);
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D データレジスタ定義（温度センサ、基準電圧）
			@param[in]	AN		アナログ型
			@param[in]	R0		レジスタ０アドレス
			@param[in]	RTNO	温度センサ型
			@param[in]	RT		温度センサアドレス
			@param[in]	RRNO	基準電圧型
			@param[in]	RR		基準電圧アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, AN RTNO, uint32_t RT, AN RRNO, uint32_t RR> 
		struct addr_tr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  データレジスタアクセスオペレーター
				@param[in]	an	アナログ入力型
				@return A/D データレジスタ値
			*/
			//-------------------------------------------------------------//
			uint16_t operator() (AN an) noexcept
			{
				if(an == RTNO) {
					return rd16_(RT);
				} else if(an == RRNO) {
					return rd16_(RR);
				} else {
					return rd16_(R0 + static_cast<uint32_t>(an) * 2);
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義(1) (ADANS)
			@param[in]	AN	アナログ型
			@param[in]	R0	レジスタ０アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0>
		struct adans1_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル選択
				@param[in]	an	アナログ入力型
				@param[in]	ena	チャネルを無効にする場合「false」
			*/
			//-------------------------------------------------------------//
			void set(AN an, bool ena = true) noexcept
			{
				auto shift = static_cast<uint32_t>(an) & 0x0f;
				if(ena) {
					wr16_(R0, rd16_(R0) |  (static_cast<uint16_t>(1) << shift));
				} else {
					wr16_(R0, rd16_(R0) & ~(static_cast<uint16_t>(1) << shift));
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル選択オペレーター
				@param[in]	an	アナログ入力型
				@return A/D チャネル選択
			*/
			//-------------------------------------------------------------//
			bool operator() (AN an) const noexcept
			{
				auto shift = static_cast<uint32_t>(an) & 0x0f;
				return (rd16_(R0) >> shift) & 1;
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義(2) (ADANS)
			@param[in]	AN	アナログ型
			@param[in]	R0	レジスタ０アドレス
			@param[in]	R1	レジスタ１アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, uint32_t R1>
		struct adans2_t {

			void adr_shift_(AN an, uint32_t& adr, uint32_t& shift) noexcept
			{
				auto s = static_cast<uint32_t>(an);
				if(s < 16) {
					adr = R0;
				} else {
					adr = R1;
				}
				shift = s & 15;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル選択
				@param[in]	an	アナログ入力型
				@param[in]	ena	チャネルを無効にする場合「false」
			*/
			//-------------------------------------------------------------//
			void set(AN an, bool ena = true) noexcept
			{
				uint32_t adr;
				uint32_t shift;
				adr_shift_(an, adr, shift);
				if(ena) {
					wr16_(adr, rd16_(adr) |  (static_cast<uint16_t>(1) << shift));
				} else {
					wr16_(adr, rd16_(adr) & ~(static_cast<uint16_t>(1) << shift));
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル選択オペレーター
				@param[in]	an	アナログ入力型
				@return A/D チャネル選択
			*/
			//-------------------------------------------------------------//
			bool operator() (AN an) const noexcept
			{
				uint32_t adr;
				uint32_t shift;
				adr_shift_(an, adr, shift);
				return (rd16_(adr) >> shift) & 1;
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ定義 1
			@param[in]	AN	アナログ型
			@param[in]	R0	レジスタ０アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0>
		struct adsstr1_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, uint8_t v) noexcept
			{
				auto ofs = static_cast<uint32_t>(an);
				if(ofs < 16) {
					wr8_(R0 + ofs, v);
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (AN an) const noexcept
			{
				auto ofs = static_cast<uint32_t>(an);
				return rd8_(R0 + (ofs & 15));
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ定義 1i
			@param[in]	AN	アナログ型
			@param[in]	R0	レジスタ０アドレス(0)
			@param[in]	RN	レジスタＮアドレス(1 to n)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, uint32_t RN>
		struct adsstr1i_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, uint8_t v) noexcept
			{
				auto ofs = static_cast<uint32_t>(an);
				if(ofs < 16) {
					if(ofs == 0) {
						wr8_(R0, v);
					} else {
						wr8_(RN - 1 + ofs, v);
					}
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (AN an) const noexcept
			{
				auto ofs = static_cast<uint32_t>(an);
				if(ofs < 16) {
					if(ofs == 0) {
						return rd8_(R0);
					} else {
						return rd8_(RN - 1 + ofs);
					}
				} else {
					return 0;
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ定義 1i+Temp+Ref
			@param[in]	AN		アナログ型
			@param[in]	R0		レジスタ０アドレス(0)
			@param[in]	RN		レジスタＮアドレス(1 to n)
			@param[in]	RTNO	温度センサ型
			@param[in]	RT		温度センサアドレス
			@param[in]	RRNO	基準電圧型
			@param[in]	RR		基準電圧アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, uint32_t RN, AN RT_NO, uint32_t RT, AN RR_NO, uint32_t RR>
		struct adsstr1i_tr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, uint8_t v) noexcept
			{
				if(an == RT_NO) {
					wr8_(RT, v);
				} else if(an == RR_NO) {
					wr8_(RR, v);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 16) {
						if(ofs == 0) {
							wr8_(R0, v);
						} else {
							wr8_(RN - 1 + ofs, v);
						}
					}
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (AN an) const noexcept
			{
				if(an == RT_NO) {
					return rd8_(RT);
				} else if(an == RR_NO) {
					return rd8_(RR);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 16) {
						if(ofs == 0) {
							return rd8_(R0);
						} else {
							return rd8_(RN - 1 + ofs);
						}
					} else {
						return 0;
					}
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ定義 1il+Temp+Ref
			@param[in]	AN		アナログ型
			@param[in]	R0		レジスタ０アドレス(0)
			@param[in]	RN		レジスタＮアドレス(1 to 7)
			@param[in]	RL		レジスタＮアドレス(8 ~)
			@param[in]	RRNO	基準電圧型
			@param[in]	RR		基準電圧アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, uint32_t RN, uint32_t RL, AN RR_NO, uint32_t RR>
		struct adsstr1il_r_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, uint8_t v) noexcept
			{
				if(an == RR_NO) {
					wr8_(RR, v);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 8) {
						if(ofs == 0) {
							wr8_(R0, v);
						} else {
							wr8_(RN - 1 + ofs, v);
						}
					} else {
						wr8_(RL, v);
					}
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (AN an) const noexcept
			{
				if(an == RR_NO) {
					return rd8_(RR);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 8) {
						if(ofs == 0) {
							return rd8_(R0);
						} else {
							return rd8_(RN - 1 + ofs);
						}
					} else {
						return rd8_(RL);
					}
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ定義 1il+Temp+Ref
			@param[in]	AN		アナログ型
			@param[in]	R0		レジスタ０アドレス(0)
			@param[in]	RN		レジスタＮアドレス(1 to 7)
			@param[in]	RL		レジスタＮアドレス(8 ~)
			@param[in]	RTNO	温度センサ型
			@param[in]	RT		温度センサアドレス
			@param[in]	RRNO	基準電圧型
			@param[in]	RR		基準電圧アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, uint32_t RN, uint32_t RL,
			AN RT_NO, uint32_t RT, AN RR_NO, uint32_t RR>
		struct adsstr1il_tr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, uint8_t v) noexcept
			{
				if(an == RT_NO) {
					wr8_(RT, v);
				} else if(an == RR_NO) {
					wr8_(RR, v);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 8) {
						if(ofs == 0) {
							wr8_(R0, v);
						} else {
							wr8_(RN - 1 + ofs, v);
						}
					} else {
						wr8_(RL, v);
					}
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (AN an) const noexcept
			{
				if(an == RT_NO) {
					return rd8_(RT);
				} else if(an == RR_NO) {
					return rd8_(RR);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 8) {
						if(ofs == 0) {
							return rd8_(R0);
						} else {
							return rd8_(RN - 1 + ofs);
						}
					} else {
						return rd8_(RL);
					}
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ定義 1l+Temp+Ref
			@param[in]	AN		アナログ型
			@param[in]	R0		レジスタアドレス０～１５
			@param[in]	RL		レジスタアドレス１６～
			@param[in]	RTNO	温度センサ型
			@param[in]	RT		温度センサアドレス
			@param[in]	RRNO	基準電圧型
			@param[in]	RR		基準電圧アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, uint32_t RL,
			AN RT_NO, uint32_t RT, AN RR_NO, uint32_t RR>
		struct adsstr1l_tr_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, uint8_t v) noexcept
			{
				if(an == RT_NO) {
					wr8_(RT, v);
				} else if(an == RR_NO) {
					wr8_(RR, v);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 16) {
						wr8_(R0 + ofs, v);
					} else {
						wr8_(RL, v);
					}
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (AN an) const noexcept
			{
				if(an == RT_NO) {
					return rd8_(RT);
				} else if(an == RR_NO) {
					return rd8_(RR);
				} else {
					auto ofs = static_cast<uint32_t>(an);
					if(ofs < 16) {
						return rd8_(R0 + ofs);
					} else {
						return rd8_(RL);
					}
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ定義 2 @n
					R0: + 0 to 7 @n
					R1: + 0
			@param[in]	AN	アナログ型
			@param[in]	R0	レジスタ０アドレス
			@param[in]	R1	レジスタ１アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <typename AN, uint32_t R0, uint32_t R1>
		struct adsstr2_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, uint8_t v) noexcept
			{
				auto ofs = static_cast<uint32_t>(an);
				if(ofs < 8) {
					wr8_(R0 + ofs, v);
				} else {
					wr8_(R1, v);
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D サンプリングステートレジスタ取得
				@param[in]	an	アナログ入力型
				@return サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator() (AN an) const noexcept
			{
				auto ofs = static_cast<uint32_t>(an);
				if(ofs < 8) {
					return rd8_(R0 + ofs);
				} else {
					return rd8_(R1);
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル変換順序設定レジスタ定義
			@param[in]	AN	アナログ型
			@param[in]	MAX	アナログ型最大
			@param[in]	R0	レジスタ０アドレス			
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<typename AN, AN MAX, uint32_t R0>
		struct adscs_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル変換順序設定
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			void set(AN an, AN v) noexcept
			{
				if(an <= MAX) {
					wr8_(R0 + static_cast<uint32_t>(an), static_cast<uint8_t>(v));
				}
			}


			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル変換順序取得
				@param[in]	an	アナログ入力型
				@param[in]	v	サンプリングステート
			*/
			//-------------------------------------------------------------//
			uint8_t operator () (AN an) noexcept
			{
				if(an <= MAX) {
					return rd8_(R0 + static_cast<uint32_t>(an));
				} else {
					return 0;
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D データ格納バッファレジスタ (ADBUF)
			@param[in]	R0	レジスタ０アドレス
			@param[in]	MAX	バッファ最大インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t R0, uint32_t MAX>
		struct adbuf_t {

			//-------------------------------------------------------------//
			/*!
				@brief  A/D チャネル変換順序取得
				@param[in]	idx	インデックス
			*/
			//-------------------------------------------------------------//
			uint16_t operator () (uint32_t idx) noexcept
			{
				if(idx <= MAX) {
					return rd16_(R0 + idx * 2);
				} else {
					return 0;
				}
			}
		};
	};
}
