#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・IICA 制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "vect.h"

/// F_PCKB はボーレートパラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKB
#  error "iica_io.hpp requires F_PCKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IICA 制御クラス（I2C)
		@param[in]	IICA	IICA 定義基底クラス 
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class IICA>
	class iica_io {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C の速度タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class speed : uint8_t {
			standard,	///< 100K b.p.s. (Standard mode)
			fast,		///< 400K b.p.s. (Fast mode)
			fast_plus,	///< 1M b.p.s. (Fast plus mode)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C エラー・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			none,		///< エラー無し
			start,		///< スタート（初期化）
			bus_open,	///< バス・オープン
			address,	///< アドレス転送
			send_data,	///< 送信データ転送
			recv_data,	///< 受信データ転送
			stop,		///< ストップ・コンディション
		};

	private:
		uint8_t		intr_lvl_;
		uint8_t		sadr_;
		uint8_t		speed_;
		error		error_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	sadr	スレーブ・アドレス
		*/
		//-----------------------------------------------------------------//
		iica_io(uint8_t sadr = 0x00) : intr_lvl_(0), sadr_(sadr), speed_(0), error_(error::none) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	動作開始
			@param[in]	spd_type	速度タイプ（メインクロックが 32MHz）
			@param[in]	intr_lvl	割り込みレベル（１、２）０の場合ポーリング
			@return 速度範囲エラーの場合「false」	
		 */
		//-----------------------------------------------------------------//
		bool start(speed spd_type, uint8_t intr_lvl)
		{
			intr_lvl_ = intr_lvl;

			port_map::turn(IICA::get_peripheral());

			power_cfg::turn(IICA::get_peripheral());

			IICA::ICCR1.ICE = 0;		// ICE(B7)=0 I2C 停止
			IICA::ICCR1.IICRST = 1;	// IICRST(B6)=1 RESET assert
			IICA::ICCR1.IICRST = 0;	// IICRST(B6)=0 RESET negate

			IICA::ICSER &=
				~(IICA::ICSER.SAR0E.b() | IICA::ICSER.SAR1E.b() | IICA::ICSER.SAR2E.b());

			// ビットレート設定(400kbps)
			// CKS = 010b
			IICA::ICMR1 = 0x28;
			IICA::ICBRH = 0xe0 | 7;
			IICA::ICBRL = 0xe0 | 16;

			IICA::ICCR1.ICE = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	最終エラーの取得
			@return エラー・タイプ
		 */
		//-----------------------------------------------------------------//
		error get_last_error() const { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	送信
			@param[in]	adr	７ビットアドレス
			@param[in]	src	転送先
			@param[in]	len	受信バイト数
			@return 送信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, const uint8_t* src, uint8_t len)
		{
			while((IICA::ICCR2() & 0x80) != 0) ;	// ICCR2.BBSY(B7) == 0?

			IICA::ICCR2 |= 0x02;	// ICCR2.ST(B1) ST = 1

			bool ret = true;
			char slave = 1;
			while(len > 0) {

				if((IICA::ICSR2() & 0x10) != 0) {	// ICSR2.NACKF(B4) == 0?
					ret = false;
					break;
				}

				while((IICA::ICSR2() & 0x80) == 0) ;	// ICSR2.TDRE(B7)

				if(slave) {
					IICA::ICDRT = (adr << 1);
					slave = 0;
				} else {
					IICA::ICDRT = *src++;
					--len;
				}
			}

//	printf("TEND Wait...\n");
			while((IICA::ICSR2() & 0x40) == 0) ;	// ICSR2.TEND(B6) == 1?

			IICA::ICSR2 &= ~0x08;	// ICSR2.STOP(B3) = 0
			IICA::ICCR2 |=  0x08;	// ICCR2.SP(B3) = 1

//	printf("STOP Wait...\n");
			while((IICA::ICSR2() & 0x08) == 0) ;	// ICSR2.STOP(B3) == 1?

			IICA::ICSR2 &= ~0x10;	// ICSR2.NACKF(B4) = 0
			IICA::ICSR2 &= ~0x08;	// ICSR2.STOP(B3) = 0

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	受信
			@param[in]	adr	７ビットアドレス
			@param[out]	dst	転送先
			@param[in]	len	受信バイト数
			@return 受信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool recv(uint8_t adr, uint8_t* dst, uint8_t len)
		{
			while((IICA::ICCR2() & 0x80) != 0) ;	// BBSY(B7) == 0?

			IICA::ICCR2 |= 0x02;				// ICCR2.ST(B1) = 1
			while((IICA::ICSR2() & 0x80) == 0) ;	// ICSR2.TDRE(B7) == 1?

			IICA::ICDRT = (adr << 1) | 0x01;	// Slave Address

			while((IICA::ICSR2() & 0x20) == 0) ;	// ICSR2.RDRF(B5) == 1?

			bool ret = true;
			int8_t da;
			if((IICA::ICSR2() & 0x10) == 0) {	// ICSR2.NACKF(B4)

				da = IICA::ICDRR();	///< dummy read

				for( ; ; ) {

					while((IICA::ICSR2() & 0x20) == 0) ;	// ICSR2.RDRF(B5) == 1?

					if(len <= 1) {
						break;
					}

					if(len <= 2) {
						IICA::ICMR3 |= 0x40;	// WAIT(B6) = 1
					}

					da = IICA::ICDRR();
					*dst++ = da;
//			printf("(%d) Read Data: %02X\n", len, da);
					--len;
				}

				// NACK を返す必要がある場合
				if((IICA::ICMR3() & 0x20) == 0) {	// ICMR3.RDRFS == 0?
					IICA::ICMR3 |=  0x10;	// ICMR3.ACKWP(B4) = 0;
					IICA::ICMR3 |=  0x08;	// ICMR3.ACKBT(B3) = 1
					IICA::ICMR3 &= ~0x10;	// ICMR3.ACKWP(B4) = 1;
				}

				da = IICA::ICDRR();			// read data
				if(len) {
					*dst++ = da;
//			printf("(%d) Read Data: %02X\n", len, da);
					--len;
				}

				while((IICA::ICSR2() & 0x20) == 0) ;	/// ICSR2.RDRF(B5) = 1?

				IICA::ICSR2 &= ~0x08;	// ICSR2.STOP(B3) = 0
				IICA::ICCR2 |=  0x08;	// ICCR2.SP(B3) = 1

				da = IICA::ICDRR();			// read data
				if(len) {
					*dst = da;
//			printf("(%d) Read Data: %02X\n", len, da);
				}
				IICA::ICMR3 &= ~0x40;	// WAIT(B6) = 0

			} else {
				IICA::ICSR2 &= ~0x08;	// ICSR2.STOP(B3) = 0
				IICA::ICCR2 |=  0x08;	// ICCR2.SP(B3) = 1
				da = IICA::ICDRR();			///< dummy read
				ret = false;
			}

//	printf("STOP Wait...\n");
			while((IICA::ICSR2() & 0x08) == 0) {	// ICSR2.STOP(B3) == 1?
			}

			IICA::ICSR2 &= ~0x10;	// ICSR2.NACKF(B4) = 0
			IICA::ICSR2 &= ~0x08;	// ICSR2.STOP(B3) = 0

			return ret;
		}

	};
}
