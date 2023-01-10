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
			@brief  A/D サンプリングステートレジスタ定義 2
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
				if(ofs < 16) {
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
				if(ofs < 16) {
					return rd8_(R0 + ofs);
				} else {
					return rd8_(R1);
				}
			}
		};
	};
}
