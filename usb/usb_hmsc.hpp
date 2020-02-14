#pragma once
//=====================================================================//
/*!	@file
	@brief	USB Host Mass Strage Class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "ff13c/source/ff.h"
#include "ff13c/source/diskio.h"

#include "r_usb_hmsc.h"
#include "r_usb_extern.h"

namespace fatfs {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  HMSC class
		@param[in]	USB_IO	USB 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class USB_IO>
	class usb_hmsc {

		static const uint32_t SECTOR_SIZE = 512;

		typedef utils::format format;

		USB_IO&		usb_;

		FATFS		fatfs_;

		bool		mount_;

		void wait_loop_()
		{
			if(usb_cstd_check_schedule() == USB_FLGSET) {
				usb_hstd_hcd_task((usb_vp_int_t) 0);
				usb_hstd_mgr_task((usb_vp_int_t) 0);
				usb_hhub_task((usb_vp_int_t) 0);
				R_USB_HmscTask(); /* HMSC Task */
			}
			usb_cstd_scheduler();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		usb_hmsc(USB_IO& usb) : usb_(usb), fatfs_(), mount_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータス
			@param[in]	drv		Physical drive nmuber (0)
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_status(BYTE drv) const noexcept
		{
			if (drv) return STA_NOINIT;

			return mount_ ? RES_OK : RES_NOTRDY;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
			@param[in]	drv		Physical drive nmuber (0)
			@return SD のステータスを返す。
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_initialize(BYTE drv) noexcept
		{
			return RES_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・セクター
			@param[in]	drv		Physical drive nmuber (0)
			@param[out]	buff	Pointer to the data buffer to store read data
			@param[in]	sector	Start sector number (LBA)
			@param[in]	count	Sector count (1..128)
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_read(BYTE drv, void* buff, DWORD sector, UINT count) noexcept
		{
			uint32_t len = count * SECTOR_SIZE;

			usb_utr_t t;
			usb_hmsc_smp_drive2_addr(drv, &t);

			if(USB_FALSE == R_USB_HmscGetDevSts(drv)) {
				return RES_ERROR;
			}

			auto err = R_USB_HmscStrgReadSector(&t, drv, static_cast<uint8_t*>(buff), sector, count, len);
			if(USB_OK != err) {
        		return RES_ERROR;
    		}

			uint16_t res = 0;
			usb_utr_t* mess = nullptr;
			do {
				res = R_USB_HmscGetDevSts(drv);
				wait_loop_();
				err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t** ) &mess, (uint16_t )0);
			} while((err != USB_OK) && (res != USB_FALSE)) ;

			if(err == USB_OK) { // Complete R_USB_HmscStrgReadSector()
				err = mess->result;
				USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )mess);
			} else { // Device detach
				wait_loop_();
				err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t** ) & mess, (uint16_t )0);
				if(USB_OK == err) {
					USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )mess);
				}
				err = USB_ERROR;
			}

			if(err != USB_OK) {
				return RES_ERROR;
			}

			return RES_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・セクター
			@param[in]	drv		Physical drive nmuber (0)
			@param[in]	buff	Pointer to the data to be written	
			@param[in]	sector	Start sector number (LBA)
			@param[in]	count	Sector count (1..128)
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_write(BYTE drv, const void* buff, DWORD sector, UINT count) noexcept
		{
			uint32_t len = count * SECTOR_SIZE;

			usb_utr_t t;
			usb_hmsc_smp_drive2_addr(drv, &t);

			if(USB_FALSE == R_USB_HmscGetDevSts(drv)) {
				return RES_ERROR;
			}

			auto err = R_USB_HmscStrgWriteSector(&t, drv, static_cast<const uint8_t*>(buff), sector, count, len);
			if(USB_OK != err) {
				return RES_ERROR;
			}

			uint16_t res = 0;
			usb_utr_t* mess = nullptr;
			do {
				res = R_USB_HmscGetDevSts(drv);

				wait_loop_();

				err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t**) &mess, (uint16_t )0);
			} while ((err != USB_OK) && (res != USB_FALSE));

			if(USB_OK == err) {
				err = mess->result;
				USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t)mess);
			} else {
				wait_loop_();
				err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t**) &mess, (uint16_t )0);
				if(err == USB_OK) {
					USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t)mess);
				}
				err = USB_ERROR;
			}

			if(err != USB_OK) {
				return RES_ERROR;
			}

			return RES_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	I/O コントロール
			@param[in]	drv		Physical drive nmuber (0)
			@param[in]	ctrl	Control code
			@param[in]	buff	Buffer to send/receive control data
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) noexcept
		{
			return RES_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		 */
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			auto event = R_USB_GetEvent(&usb_.at_ctrl()); /* Get event code */
			switch (event) {
			case USB_STS_CONFIGURED:
///				format("USB: CONFIGURED\n");
				{
					uint8_t drvno;
					R_USB_HmscGetDriveNo(&usb_.at_ctrl(), &drvno);

					auto st = f_mount(&fatfs_, "", 0);
					if(st == FR_OK) mount_ = true;
					else mount_ = false;
				}
				break;

			case USB_STS_DETACH:
///				format("USB: DETACH\n");
				f_mount(nullptr, "", 0);
				mount_ = false;
				break;

			default :
				break;
			}
		}
	};
}
