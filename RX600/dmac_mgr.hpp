#pragma once
//=========================================================================//
/*!	@file
	@brief	DMAC マネージャー @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC マネージャー、定数クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct dmac_mgr_def {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  転送タイプ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TRANS_TYPE : uint8_t {
			SN_DP_8,		///< ソース固定、ディストネーション＋（8 bits）
			SP_DN_8,		///< ソース＋、ディストネーション固定（8 bits）
			SN_DP_16,		///< ソース固定、ディストネーション＋（16 bits）
			SP_DN_16,		///< ソース＋、ディストネーション固定（16 bits）
			SN_DP_32,		///< ソース固定、ディストネーション＋（32 bits）
			SP_DN_32,		///< ソース＋、ディストネーション固定（32 bits）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  転送モード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TRANS_MODE : uint8_t {
			NORMAL = 0b00, 	///< ノーマル転送モード（回数：１～６５５３５）
			REPEAT = 0b01,	///< リピート転送モード（回数：１～１０２４）
			BLOCK  = 0b10	///< ブロック転送モード（回数：１～１０２４）
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC マネージャー・クラス
		@param[in]	DMAC	DMAC コントローラー
		@param[in]	TASK	DMA 終了割り込みファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class DMAC, class TASK = utils::null_task>
	class dmac_mgr : public dmac_mgr_def {
	public:
		typedef DMAC value_type;	///< DMAC チャネルの型

		static constexpr uint32_t BLOCK_SIZE_MAX = 1024;	///< データ転送最大ブロック数

	private:
		static inline TASK	task_;
		ICU::LEVEL	level_;

		static INTERRUPT_FUNC void dmac_task_() noexcept
		{
			task_();
			DMAC::DMSTS.DTIF = 0;
		}

		void set_vector_(ICU::VECTOR vec) const noexcept
		{
			if(level_ != ICU::LEVEL::NONE) {
				icu_mgr::set_task(vec, dmac_task_);
			} else {
				icu_mgr::set_task(vec, nullptr);
			}
			icu_mgr::set_level(DMAC::IVEC, level_);
		}


		static bool trans_inc_(uint32_t src_adr, uint32_t dst_adr, uint32_t len) noexcept
		{
			uint8_t sz = 0;
			if(len < 4) ;
			else if((src_adr & 3) == 0 && (dst_adr & 3) == 0 && (len & 3) == 0) {  // 32 bits DMA
				sz = 2;
				len >>= 2;
			} else if((src_adr & 1) == 0 && (dst_adr & 1) == 0 && (len & 1) == 0) {  // 16 bits DMA
				sz = 1;
				len >>= 1;
			}
			if(len > 65535) return false;

			// 転送元 (+1)、転送先 (+1)
			DMAC::DMAMD = DMAC::DMAMD.DM.b(0b10) | DMAC::DMAMD.SM.b(0b10);

			DMAC::DMTMD = DMAC::DMTMD.DCTG.b(0b00) | DMAC::DMTMD.SZ.b(sz) |
						  DMAC::DMTMD.DTS.b(0b10)  | DMAC::DMTMD.MD.b(0b00);

			DMAC::DMSAR = src_adr;
			DMAC::DMDAR = dst_adr;
			DMAC::DMCRA = len;

			return true;
		}


		static bool trans_dec_(uint32_t src_adr, uint32_t dst_adr, uint32_t len) noexcept
		{
			uint8_t sz = 0;
			if(len < 4) ;
			else if((src_adr & 3) == 0 && (dst_adr & 3) == 0 && (len & 3) == 0) {  // 32 bits DMA
				sz = 2;
				len >>= 2;
			} else if((src_adr & 1) == 0 && (dst_adr & 1) == 0 && (len & 1) == 0) {  // 16 bits DMA
				sz = 1;
				len >>= 1;
			}
			if(len > 65535) return false;

			// 転送元 (-1)、転送先 (-1)
			DMAC::DMAMD = DMAC::DMAMD.DM.b(0b11) | DMAC::DMAMD.SM.b(0b11);

			DMAC::DMTMD = DMAC::DMTMD.DCTG.b(0b00) | DMAC::DMTMD.SZ.b(sz) |
						  DMAC::DMTMD.DTS.b(0b10)  | DMAC::DMTMD.MD.b(0b00);

			DMAC::DMSAR = src_adr + len - sz;
			DMAC::DMDAR = dst_adr + len - sz;
			DMAC::DMCRA = len;

			return true;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		dmac_mgr() noexcept : level_(ICU::LEVEL::NONE) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始（メモリー操作関係）
			@param[in]	lvl		転送完了割り込みレベル
		 */
		//-----------------------------------------------------------------//
		void start(ICU::LEVEL lvl = ICU::LEVEL::NONE) noexcept
		{
			power_mgr::turn(DMAC::PERIPHERAL);

			level_ = lvl;
			set_vector_(DMAC::IVEC);

			DMAC::DMAST.DMST = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	割り込み要因による転送開始
			@param[in]	trm		転送モード型
			@param[in]	trt		転送タイプ型
			@param[in]	trg		転送開始要因
			@param[in]	src		転送元アドレス
			@param[in]	dst		転送先アドレス
			@param[in]	siz		MODE_REPEAT:リンピート・サイズ、 @n
								MODE_BLOCK:ブロック・サイズ
			@param[in]	cnt		転送カウント
			@param[in]	ilvl	転送完了割り込みレベル（０以上） @n
								※無指定（０）なら割り込みを起動しない。
			@param[in]	isel	CPU にも割り込みをかける場合は「true」にする。
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(TRANS_MODE trm, TRANS_TYPE trt, ICU::VECTOR trg,
			uint32_t src, uint32_t dst, uint16_t siz, uint16_t cnt,
			ICU::LEVEL ilvl, bool isel = false) noexcept
		{
			if(trm == TRANS_MODE::REPEAT || trm == TRANS_MODE::BLOCK) {
				if(siz > 1024 || cnt > 1024) {
					return false;
				}
				siz &= 0x3ff;
				cnt &= 0x3ff;
			}

			power_mgr::turn(DMAC::PERIPHERAL);

			DMAC::DMCNT.DTE = 0;  // 念のため停止させる。

			auto md = static_cast<uint8_t>(trm);
			uint8_t sm = 0;
			uint8_t dm = 0;
			uint8_t sz = 0;
			switch(trt) {
			case TRANS_TYPE::SN_DP_8:
				sm = 0b00;  // n
				dm = 0b10;  // ++
				sz = 0;
				break;
			case TRANS_TYPE::SP_DN_8:
				sm = 0b10;  // ++
				dm = 0b00;  // n
				sz = 0;
				break;
			case TRANS_TYPE::SN_DP_16:
				sm = 0b00;  // n
				dm = 0b10;  // ++
				sz = 1;
				break;
			case TRANS_TYPE::SP_DN_16:
				sm = 0b10;  // ++
				dm = 0b00;  // n
				sz = 1;
				break;
			case TRANS_TYPE::SN_DP_32:
				sm = 0b00;  // n
				dm = 0b10;  // ++
				sz = 2;
				break;
			case TRANS_TYPE::SP_DN_32:
				sm = 0b10;  // ++
				dm = 0b00;  // n
				sz = 2;
				break;
			default:
				break;
			}

			DMAC::DMAMD = DMAC::DMAMD.DM.b(dm) | DMAC::DMAMD.SM.b(sm);
			DMAC::DMTMD = DMAC::DMTMD.DCTG.b(0b01) | DMAC::DMTMD.SZ.b(sz) |
						  DMAC::DMTMD.DTS.b(0b01)  | DMAC::DMTMD.MD.b(md);
			DMAC::DMSAR = src;
			DMAC::DMDAR = dst;

			DMAC::DMCRA = (siz << 16) | cnt;
			DMAC::DMCRB = 1;

			level_ = ilvl;
			set_vector_(DMAC::IVEC);
			if(level_ != ICU::LEVEL::NONE) {
				icu_mgr::set_dmac(DMAC::PERIPHERAL, trg);
				DMAC::DMINT = DMAC::DMINT.DTIE.b();
				DMAC::DMCSL.DISEL = isel;
			} else {
				DMAC::DMINT = 0x00;
				DMAC::DMCSL.DISEL = isel;
			}

			DMAC::DMCNT.DTE = 1;

			DMAC::DMAST.DMST = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	転送再開 @n
					※設定をしていない状態で呼んではいけない。
		 */
		//-----------------------------------------------------------------//
		void restart() const noexcept
		{
			DMAC::DMCNT.DTE = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	停止
			@param[in]	power	電源も切断する場合「true」
		 */
		//-----------------------------------------------------------------//
		void stop(bool power = false) noexcept
		{
			DMAC::DMCNT.DTE = 0;

			if(power) {
				power_mgr::turn(DMAC::PERIPHERAL, false);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	DMA カウンタの取得
			@return DMA カウンタ
		 */
		//-----------------------------------------------------------------//
		uint32_t get_count() const noexcept {
			return DMAC::DMCRA();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	DMA 動作中か検査
			@return 動作中なら「true」
		 */
		//-----------------------------------------------------------------//
		bool probe() const noexcept {
			return DMAC::DMSTS.ACT();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	定数で埋める
			@param[out]	org		定数先頭 @n
								定数をあらかじめ先頭に書き込んでおく
			@param[in]	frz		定数サイズ（バイト）
			@param[in]	len		埋める数（バイト）
			@param[in]	tae		終了時タスクを起動する場合「true」
			@return 出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool fill(void* org, uint32_t frz, uint32_t len, bool tae = false) noexcept
		{
			if(org == nullptr || frz == 0 || len == 0 || frz > len) return false;

			DMAC::DMCNT.DTE = 0;  // 念のため停止させる。

			uint32_t src_adr = reinterpret_cast<uint32_t>(org);
			uint32_t dst_adr = src_adr + frz;
			len -= frz;

			if(!trans_inc_(src_adr, dst_adr, len)) {
				return false;
			}

			if(tae && level_ != ICU::LEVEL::NONE) {
				DMAC::DMINT.DTIE = 1;
			} else {
				DMAC::DMINT = 0x00;
			}

			DMAC::DMCNT.DTE = 1;

			// CLRS=0 の場合、１回の転送で終了
			DMAC::DMREQ = DMAC::DMREQ.SWREQ.b() | DMAC::DMREQ.CLRS.b();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	定数で埋める（８ビット）
			@param[out]	org		定数先頭
			@param[in]	val		定数
			@param[in]	len		埋める数（バイト）
			@param[in]	tae		終了時タスクを起動する場合「true」
			@return 出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool memset(void* org, uint8_t val, uint32_t len, bool tae = false) noexcept
		{
			if(org == nullptr || len == 0) return false;

			uint8_t* dst = static_cast<uint8_t*>(org);
			*dst++ = val;
			uint32_t frz = 1;
			uint32_t adr = reinterpret_cast<uint32_t>(org);
			if((adr & 1) == 0 && (len & 1) == 0 && len > 2) {
				++frz;
				*dst++ = val;
			}
			if((adr & 3) == 0 && (len & 3) == 0 && len > 4) {
				frz += 2;
				*dst++ = val;
				*dst++ = val;
			}
			return fill(org, frz, len, tae);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	定数で埋める（１６ビット）
			@param[out]	org		定数先頭
			@param[in]	val		定数
			@param[in]	len		埋める数（バイト）
			@param[in]	tae		終了時タスクを起動する場合「true」
			@return 出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool memset16(void* org, uint16_t val, uint32_t len, bool tae = false) noexcept
		{
			if(org == nullptr || len < 2) return false;
			uint32_t adr = reinterpret_cast<uint32_t>(org);
			if(adr & 1) return false;  // 奇数アドレスはNG

			uint16_t* dst = static_cast<uint16_t*>(org);
			*dst++ = val;
			uint32_t frz = 2;

			if((adr & 3) == 0 && (len & 3) == 0 && len > 4) {
				frz += 2;
				*dst++ = val;
			}
			return fill(org, frz, len, tae);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	定数で埋める（３２ビット）
			@param[out]	org		定数先頭
			@param[in]	val		定数
			@param[in]	len		埋める数（バイト）
			@param[in]	tae		終了時タスクを起動する場合「true」
			@return 出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool memset32(void* org, uint32_t val, uint32_t len, bool tae = false) noexcept
		{
			if(org == nullptr || len < 4) return false;

			uint32_t adr = reinterpret_cast<uint32_t>(org);
			if((adr & 3) != 0 || (len & 4) != 0) return false;  // 32ビット境界がNGの場合・・

			uint32_t* dst = static_cast<uint32_t*>(org);
			*dst = val;
			uint32_t frz = 4;

			return fill(org, frz, len, tae);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コピー・メモリー @n
					オーバーラップする場合は、コピーする順番を自動で変更 @n
					※特定の値で埋める場合は「fill」を使う。
			@param[in]	src		コピー元
			@param[in]	dst		コピー先
			@param[in]	len		コピー数（バイト単位）@n
								※アドレスが 32 ビット単位の場合、最大 65535 x4 バイト
								※アドレスが 16 ビット単位の場合、最大 65535 x2 バイト
								※アドレスが 8  ビット単位の場合、最大 65535 x1 バイト
			@param[in]	tae		終了時タスクを起動する場合「true」
			@return コピーが出来ない場合「false」（パラメーターが異常）
		 */
		//-----------------------------------------------------------------//
		bool copy(const void* src, void* dst, uint32_t len, bool tae = false) const noexcept
		{
			if(len == 0 || src == nullptr || dst == nullptr) return false;

			DMAC::DMCNT.DTE = 0;  // 念のため停止させる。

			uint32_t src_adr = reinterpret_cast<uint32_t>(src);
			uint32_t dst_adr = reinterpret_cast<uint32_t>(dst);

			bool ret = false;
			if(dst_adr < (src_adr + len)) {
				ret = trans_dec_(src_adr, dst_adr, len);
			} else {
				ret = trans_inc_(src_adr, dst_adr, len);
			}
			if(!ret) {
				return false;
			}

			if(tae && level_ != ICU::LEVEL::NONE) {
				DMAC::DMINT.DTIE = 1;
			} else {
				DMAC::DMINT = 0x00;
			}

			DMAC::DMCNT.DTE = 1;

			// CLRS=0 の場合、１回の転送で終了
			DMAC::DMREQ = DMAC::DMREQ.SWREQ.b() | DMAC::DMREQ.CLRS.b();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() noexcept { return task_; }
	};
}
