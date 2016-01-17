//========================================================================//
/*! @file	mmc_rspi.c
    @brief	AKI-RX62(RX621 シリーズマイコン): R5F56218BNFP　@n
			FatFS SPI driver
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//========================================================================//
/*------------------------------------------------------------------------*/
/*
/  Copyright (C) 2012, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/
#include <cstdlib>
#include "diskio.h"		/* Common include file for ff.c and disk layer */
#include "mmc_rspi.hpp"
#include "rx62x_system.hpp"
#include "rx62x_rspi.hpp"
#include "rx62x_port.hpp"

/// RSPI channel: 0:RSPIA-A, 1:RSPIB-A, 10:RSPIA-B, 11:RSPIB-B
/// RSPI0 or RSPI1
static device::RSPI0 rspi_;

// Card Detect switch
// BIT.B2: 0 ---> Card Detected. (1)
// BIT.B2: 1 ---> Card Open. (0)
// Card WriteProtect switch
// BIT.B3: 0 ---> Write Enable. (1)
// BIT.B3: 1 ---> Write Disable.Protected (0)
static inline void card_sense_init_()
{
	static char init_ = 0;
	if(init_) return;

	device::PORTC::ICR |= 0x0c;		///< 入力指定
	device::PORTC::PCR |= 0x0c;		///< プルアップ有効

	init_ = 1;
}

static inline int card_dt_() {
	if(device::PORTC::PORT.B2()) return 0;
	else return 1;
}

static inline int card_wp_() {
	if(device::PORTC::PORT.B3()) return 0;
	else return 1; 
}

/// Set CS Low
static inline void cs_low_() {
	device::PORTC::DR.B4 = 0;
}

/// Set CS High
static inline void cs_high_() {
	device::PORTC::DR.B4 = 1;
}

/// Initialize CS,INS,WP control port
static void ctrl_init_()
{	
	///< CS=OUT
	device::PORTC::DR.B4 = 1;
	///< CS=H
	device::PORTC::DDR.B4 = 1;
	///< INS=IN
	device::PORTC::ICR.B7 = 1;
}

#define F_PCLK		48000000UL	/* PCLK frequency (configured by SCKCR.PCK) */
#define SCLK_FAST	12000000UL	/* SCLK frequency (R/W) */
#define	SCLK_SLOW	400000UL	/* SCLK frequency (Init) */

static inline void rspi_attach_()
{
	// RSPI0 のストップ状態解除(MSTPB17)
	// RSPI1 のストップ状態解除(MSTPB16)
	if(rspi_.get_chanel() == 0) {

		device::PORTC::ICR.B7 = 1;
		device::IOPORT::PFGSPI = 0x0E;

		device::SYSTEM::MSTPCRB.MSTPB17 = 0;
	} else {
		device::PORT3::ICR.B0 = 1;
		device::IOPORT::PFHSPI = 0x0E;

		device::SYSTEM::MSTPCRB.MSTPB16 = 0;
	}
}

#if 0
// B port
static inline void rspi_attach_(void) {
//	PORTA.ICR.BIT.B7 = 1;
	PORTA.ICR.BYTE |= 0x80;
	IOPORT.PFGSPI.BYTE = 0x0F;
	device::SYSTEM::MSTPCRB.MSTPB17 = 0;
}

static inline void rspi_attach_(void) {
//	PORTE.ICR.BIT.B7 = 1;
	PORTE.ICR.BYTE |= 0x80;
	IOPORT.PFHSPI.BYTE = 0x0F;
	MSTP_RSPI1 = 0;
}
#endif

static inline void FCLK_FAST_()
{
	rspi_.SPCR.SPE = 0;
	rspi_.SPBR = F_PCLK / 2 / SCLK_FAST - 1;
	rspi_.SPCR.SPE = 1;
}


/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

/* MMC/SD command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */

static volatile DSTATUS stat_ = STA_NOINIT;	///< Physical drive status

/// 100Hz decrement timer stopped at zero (driven by fatfs_timerproc())
static volatile WORD timer1_;
static volatile WORD timer2_;

static BYTE card_type_;			///< Card type flags

/*-----------------------------------------------------------------------*/
/* Control SPI module                                                    */
/*-----------------------------------------------------------------------*/
/* Only these five functions are platform dependent. Any other functions */
/* are portable to different system.                                     */

/*---------------------------------*/
/* Enable SPI and MMC/SDC controls */
/*---------------------------------*/
static void power_on_()
{
	/* Initialize CS/INS/WP port */
	ctrl_init_();

	/* Attach RSPI module to I/O pads, disable module stop */
	rspi_attach_();

	/* Initialize RSPI module */
	rspi_.SPCR = 0;		/* Stop RSPI module */
	rspi_.SPPCR = 0;	/* Fixed idle value, disable loop-back mode */
	rspi_.SPSCR = 0;	/* Disable sequence control */
	rspi_.SPDCR = 0x20;	/* SPLW=1 */
	rspi_.SPCMD0 = 0x0700;	/* LSBF=0, SPB=7, BRDV=0, CPOL=0, CPHA=0 */
	rspi_.SPBR = F_PCLK / 2 / SCLK_SLOW - 1;	/* Bit rate */
	rspi_.SPCR = 0x49;	/* Start RSPI in master mode */
}


/*---------------------*/
/*    Disable SPI      */
/*---------------------*/
static void power_off_()	/* Disable MMC/SDC interface */
{
	rspi_.SPCR = 0;		/* Stop RSPI module */
}


/*---------------------*/
/* Send/Receive a byte */
/*---------------------*/
static BYTE xchg_spi_(BYTE dat)
{
	rspi_.SPDR = dat;			/* Start transmission (lower 8bits) */
	while(!rspi_.SPSR.SPRF()) ;
	return rspi_.SPDR();			/* Returen received byte (lower 8bits) */
}


/*---------------------*/
/* Send multiple bytes */
/*---------------------*/
static void xmit_spi_multi_(
	const BYTE *buff,	/* Pointer to the data */
	UINT btx			/* Number of bytes to send (multiple of 4) */
)
{
	while(btx > 0) {
		xchg_spi_(*buff++);
		--btx;
	}
#if 0
	const DWORD *lp = (const DWORD*)buff;
	RSPI.SPCMD0.BIT.SPB = 3;	/* Set 32-bit mode */
	do {
		RSPI.SPDR.LONG = LDDW(*lp++);	/* Send four data bytes */
		while (!RSPI.SPSR.BIT.SPRF) ;	/* Wait for end of transfer */
		RSPI.SPDR.LONG;					/* Discard four received bytes */
	} while (btx -= 4);					/* Repeat until all data sent */

	RSPI.SPCMD0.BIT.SPB = 7;	/* Set 8-bit mode */
#endif
}

/*------------------------*/
/* Receive multiple bytes */
/*------------------------*/
static void rcvr_spi_multi_(
	BYTE *buff,		/* Pointer to data buffer */
	UINT btr		/* Number of bytes to receive (multiple of 4) */
)
{
	while(btr > 0) {
		*buff++ = xchg_spi_(0xff);
		--btr;
	}

#if 0
	DWORD *lp = (DWORD*)buff;

	RSPI.SPCMD0.BIT.SPB = 3;	/* Set 32-bit mode */

	do {
		RSPI.SPDR.LONG = 0xFFFFFFFF;	/* Send four 0xFFs */
		while (!RSPI.SPSR.BIT.SPRF) ;	/* Wait for end of transfer */
		*lp++ = LDDW(RSPI.SPDR.LONG);	/* Store four received bytes */
	} while (btr -= 4);					/* Repeat until all data received */

	RSPI.SPCMD0.BIT.SPB = 7;	/* Set 8-bit mode */
#endif
}


/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/
static int wait_ready_(	/* 1:Ready, 0:Timeout */
	UINT wt			/* Timeout [ms] */
)
{
	timer2_ = (WORD)wt;

	xchg_spi_(0xFF);	/* Read a byte (Force enable DO output) */
	do {
		if (xchg_spi_(0xFF) == 0xFF) return 1;	/* Card goes ready */
		/* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */
	} while (timer2_);	/* Wait until card goes ready or timeout */

	return 0;	/* Timeout occured */
}


/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/
static void deselect_(void)
{
	cs_high_();		/* CS = H */
	xchg_spi_(0xFF);	/* Dummy clock (force DO hi-z) */
}

/*-----------------------------------------------------------------------*/
/* Select card and wait for ready                                        */
/*-----------------------------------------------------------------------*/
static int select_(void)	/* 1:OK, 0:Timeout */
{
	cs_low_();		/* CS = H */
	if (!wait_ready_(500)) {
		deselect_();
		return 0;	/* Failed to select the card due to timeout */
	}
	return 1;	/* OK */
}

/*-----------------------------------------------------------------------*/
/* Receive a data packet from the MMC                                    */
/*-----------------------------------------------------------------------*/
static int rcvr_datablock_(	/* 1:OK, 0:Error */
	BYTE *buff,			/* Data buffer */
	UINT btr			/* Data block length (byte) */
)
{
	BYTE token;

	timer1_ = 20;
	do {							/* Wait for DataStart token in timeout of 200ms */
		token = xchg_spi_(0xFF);
		/* This loop will take a time. Insert rot_rdq() here for multitask envilonment. */
	} while ((token == 0xFF) && timer1_);
	if (token != 0xFE) return 0;	/* Function fails if invalid DataStart token or timeout */

	rcvr_spi_multi_(buff, btr);		/* Store trailing data to the buffer */
	xchg_spi_(0xFF); xchg_spi_(0xFF);	/* Discard CRC */

	return 1;						/* Function succeeded */
}

/*-----------------------------------------------------------------------*/
/* Send a data packet to the MMC                                         */
/*-----------------------------------------------------------------------*/
#if _USE_WRITE
static int xmit_datablock_(	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* Ponter to 512 byte data to be sent */
	BYTE token			/* Token */
)
{
	BYTE resp;

	if (!wait_ready_(500)) return 0;	/* Wait for card ready */

	xchg_spi_(token);					/* Send token */
	if (token != 0xFD) {				/* Send data if token is other than StopTran */
		xmit_spi_multi_(buff, 512);		/* Data */
		xchg_spi_(0xFF); xchg_spi_(0xFF);	/* Dummy CRC */

		resp = xchg_spi_(0xFF);			/* Receive data resp */
		if ((resp & 0x1F) != 0x05)		/* Function fails if the data packet was not accepted */
			return 0;
	}
	return 1;
}
#endif /* _USE_WRITE */

/*-----------------------------------------------------------------------*/
/* Send a command packet to the MMC                                      */
/*-----------------------------------------------------------------------*/
static BYTE send_cmd_(		/* Return value: R1 resp (bit7==1:Failed to send) */
	BYTE cmd,		/* Command index */
	DWORD arg		/* Argument */
)
{
	BYTE n, res;

	if (cmd & 0x80) {	/* Send a CMD55 prior to ACMD<n> */
		cmd &= 0x7F;
		res = send_cmd_(CMD55, 0);
		if (res > 1) return res;
	}

	/* Select card */
	deselect_();
	if (!select_()) return 0xFF;

	/* Send command packet */
	xchg_spi_(0x40 | cmd);			/* Start + command index */
	xchg_spi_((BYTE)(arg >> 24));	/* Argument[31..24] */
	xchg_spi_((BYTE)(arg >> 16));	/* Argument[23..16] */
	xchg_spi_((BYTE)(arg >> 8));		/* Argument[15..8] */
	xchg_spi_((BYTE)arg);			/* Argument[7..0] */
	n = 0x01;						/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;		/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;		/* Valid CRC for CMD8(0x1AA) */
	xchg_spi_(n);

	/* Receive command resp */
	if (cmd == CMD12) xchg_spi_(0xFF);	/* Diacard stuff byte on CMD12 */
	n = 10;							/* Wait for response (10 bytes max) */
	do {
		res = xchg_spi_(0xFF);
	} while ((res & 0x80) && --n);

	return res;						/* Return received response */
}


//-----------------------------------------------------------------//
/*!
    @brief  Initialize disk drive
	@param[in]	drv	Physical drive number (0)
	@return status bits field
 */
//-----------------------------------------------------------------//
DSTATUS disk_initialize (BYTE drv)
{
	BYTE n, cmd, ty, ocr[4];

	if (drv) return STA_NOINIT;			/* Supports only drive 0 */

	power_on_();						/* Initialize RSPI */
	for (n = 10; n; n--) xchg_spi_(0xFF);/* Send 80 dummy clocks */

	ty = 0;
	if (send_cmd_(CMD0, 0) == 1) {			/* Put the card SPI/Idle state */
		timer1_ = 100;						/* Initialization timeout = 1 sec */
		if (send_cmd_(CMD8, 0x1AA) == 1) {	/* SDv2? */
			for (n = 0; n < 4; n++) ocr[n] = xchg_spi_(0xFF);	/* Get 32 bit return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* Is the card supports vcc of 2.7-3.6V? */
				while (timer1_ && send_cmd_(ACMD41, 1UL << 30)) ;	/* Wait for end of initialization with ACMD41(HCS) */
				if (timer1_ && send_cmd_(CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = xchg_spi_(0xFF);
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* Card id SDv2 */
				}
			}
		} else {	/* Not SDv2 card */
			if (send_cmd_(ACMD41, 0) <= 1) 	{	/* SDv1 or MMC? */
				ty = CT_SD1; cmd = ACMD41;	/* SDv1 (ACMD41(0)) */
			} else {
				ty = CT_MMC; cmd = CMD1;	/* MMCv3 (CMD1(0)) */
			}
			while (timer1_ && send_cmd_(cmd, 0)) ;		/* Wait for end of initialization */
			if (!timer1_ || send_cmd_(CMD16, 512) != 0)	/* Set block length: 512 */
				ty = 0;
		}
	}
	card_type_ = ty;	/* Card type */
	deselect_();

	if (ty) {			/* OK */
		FCLK_FAST_();			/* Set fast clock */
		stat_ &= ~STA_NOINIT;	/* Clear STA_NOINIT flag */
	} else {			/* Failed */
		power_off_();
		stat_ = STA_NOINIT;
	}

	return stat_;
}


//-----------------------------------------------------------------//
/*!
    @brief  Get disk status
	@param[in]	drv	Physical drive number (0)
	@return status bits field
 */
//-----------------------------------------------------------------//
DSTATUS disk_status (BYTE drv)
{
	if (drv) return STA_NOINIT;		/* Supports only drive 0 */

	return stat_;	/* Return disk status */
}


//-----------------------------------------------------------------//
/*!
    @brief  Read sector(s)
	@param[in]	drv	Physical drive number (0)
	@param[in]	buff Pointer to the data buffer to store read data
	@param[in]	sector Start sector number (LBA)
	@param[in]	count  Number of sectors to read (1..128)
	@return status bits field
 */
//-----------------------------------------------------------------//
DRESULT disk_read(BYTE drv, BYTE *buff, DWORD sector, BYTE count)
{
	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (stat_ & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	if (!(card_type_ & CT_BLOCK)) sector *= 512;	/* LBA ot BA conversion (byte addressing cards) */

	if (count == 1) {	/* Single sector read */
		if ((send_cmd_(CMD17, sector) == 0)	/* READ_SINGLE_BLOCK */
			&& rcvr_datablock_(buff, 512))
			count = 0;
	}
	else {				/* Multiple sector read */
		if (send_cmd_(CMD18, sector) == 0) {	/* READ_MULTIPLE_BLOCK */
			do {
				if (!rcvr_datablock_(buff, 512)) break;
				buff += 512;
			} while (--count);
			send_cmd_(CMD12, 0);				/* STOP_TRANSMISSION */
		}
	}
	deselect_();

	return count ? RES_ERROR : RES_OK;	/* Return result */
}


#if _USE_WRITE
//-----------------------------------------------------------------//
/*!
    @brief  Write sector(s)
	@param[in]	drv	Physical drive number (0)
	@param[in]	buff Ponter to the data to write
	@param[in]	sector Start sector number (LBA)
	@param[in]	count  Number of sectors to read (1..128)
	@return status bits field
 */
//-----------------------------------------------------------------//
DRESULT disk_write (BYTE drv, const BYTE *buff, DWORD sector, BYTE count)
{
	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (stat_ & STA_NOINIT) return RES_NOTRDY;	/* Check drive status */
	if (stat_ & STA_PROTECT) return RES_WRPRT;	/* Check write protect */

	if (!(card_type_ & CT_BLOCK)) sector *= 512;	/* LBA ==> BA conversion (byte addressing cards) */

	if (count == 1) {	/* Single sector write */
		if ((send_cmd_(CMD24, sector) == 0)	/* WRITE_BLOCK */
			&& xmit_datablock_(buff, 0xFE))
			count = 0;
	}
	else {				/* Multiple sector write */
		if (card_type_ & CT_SDC) send_cmd_(ACMD23, count);
		if (send_cmd_(CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
			do {
				if (!xmit_datablock_(buff, 0xFC)) break;
				buff += 512;
			} while (--count);
			if (!xmit_datablock_(0, 0xFD))	/* STOP_TRAN token */
				count = 1;
		}
	}
	deselect_();

	return count ? RES_ERROR : RES_OK;	/* Return result */
}
#endif /* _USE_WRITE */


#if _USE_IOCTL
//-----------------------------------------------------------------//
/*!
    @brief  Miscellaneous drive controls other than data read/write
	@param[in]	drv	Physical drive number (0)
	@param[in]	ctrl Control command code	
	@param[in]	buff Pointer to the conrtol data
	@return status bits field
 */
//-----------------------------------------------------------------//
DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void *buff)
{
	DRESULT res;
	BYTE n, csd[16];
	BYTE* ptr = static_cast<BYTE*>(buff);
	DWORD* dp;
	DWORD st, ed, csz;

	if (drv) return RES_PARERR;					/* Check parameter */
	if (stat_ & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	res = RES_ERROR;

	switch (ctrl) {
	case CTRL_SYNC :		/* Wait for end of internal write process of the drive */
		if (select_()) res = RES_OK;
		break;

	case GET_SECTOR_COUNT :	/* Get drive capacity in unit of sector (DWORD) */
		if ((send_cmd_(CMD9, 0) == 0) && rcvr_datablock_(csd, 16)) {
			if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
				csz = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
				*(DWORD*)buff = csz << 10;
			} else {					/* SDC ver 1.XX or MMC ver 3 */
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				csz = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
				*(DWORD*)buff = csz << (n - 9);
			}
			res = RES_OK;
		}
		break;

	case GET_SECTOR_SIZE :	/* Get sector size in unit of byte (WORD) */
		*(WORD*)buff = 512;
		res = RES_OK;
		break;

	case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
		if (card_type_ & CT_SD2) {	/* SDC ver 2.00 */
			if (send_cmd_(ACMD13, 0) == 0) {	/* Read SD status */
				xchg_spi_(0xFF);	/* Discard 2nd byte of R2 resp. */
				if (rcvr_datablock_(csd, 16)) {					/* Read partial block */
					for (n = 64 - 16; n; n--) xchg_spi_(0xFF);	/* Purge trailing data */
					*(DWORD*)buff = 16UL << (csd[10] >> 4);
					res = RES_OK;
				}
			}
		} else {					/* SDC ver 1.XX or MMC */
			if ((send_cmd_(CMD9, 0) == 0) && rcvr_datablock_(csd, 16)) {	/* Read CSD */
				if (card_type_ & CT_SD1) {	/* SDC ver 1.XX */
					*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
				} else {					/* MMC */
					*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
				}
				res = RES_OK;
			}
		}
		break;

	case CTRL_ERASE_SECTOR :	/* Erase a block of sectors (used when _USE_ERASE == 1) */
		if (!(card_type_ & CT_SDC)) break;				/* Check if the card is SDC */
		if (disk_ioctl(drv, MMC_GET_CSD, csd)) break;	/* Get CSD */
		if (!(csd[0] >> 6) && !(csd[10] & 0x40)) break;	/* Check if sector erase can be applied to the card */
		dp = static_cast<DWORD*>(buff);
		st = dp[0];
		ed = dp[1];				/* Load sector block */
		if (!(card_type_ & CT_BLOCK)) {
			st *= 512; ed *= 512;
		}
		if (send_cmd_(CMD32, st) == 0 && send_cmd_(CMD33, ed) == 0 && send_cmd_(CMD38, 0) == 0 && wait_ready_(30000))	/* Erase sector block */
			res = RES_OK;
		break;

	/* Following command are not used by FatFs module */

	case MMC_GET_TYPE :		/* Get MMC/SDC type (BYTE) */
		*ptr = card_type_;
		res = RES_OK;
		break;

	case MMC_GET_CSD :		/* Read CSD (16 bytes) */
		if (send_cmd_(CMD9, 0) == 0		/* READ_CSD */
			&& rcvr_datablock_(ptr, 16))
			res = RES_OK;
		break;

	case MMC_GET_CID :		/* Read CID (16 bytes) */
		if (send_cmd_(CMD10, 0) == 0		/* READ_CID */
			&& rcvr_datablock_(ptr, 16))
			res = RES_OK;
		break;

	case MMC_GET_OCR :		/* Read OCR (4 bytes) */
		if (send_cmd_(CMD58, 0) == 0) {	/* READ_OCR */
			for (n = 4; n; n--) *ptr++ = xchg_spi_(0xFF);
			res = RES_OK;
		}
		break;

	case MMC_GET_SDSTAT :	/* Read SD status (64 bytes) */
		if (send_cmd_(ACMD13, 0) == 0) {	/* SD_STATUS */
			xchg_spi_(0xFF);
			if (rcvr_datablock_(ptr, 64))
				res = RES_OK;
		}
		break;

	default:
		res = RES_PARERR;
	}

	deselect_();

	return res;
}
#endif /* _USE_IOCTL */


//-----------------------------------------------------------------//
/*!
    @brief  Device timer function @n
			This function must be called from system timer process @n
			in period of 10 ms to generate card control timing.
*/
//-----------------------------------------------------------------//
void disk_timerproc(void)
{
	if(timer1_) --timer1_;
	if(timer2_) --timer2_;

	card_sense_init_();

	if(card_wp_()) stat_ |= STA_PROTECT;
	if(card_dt_()) stat_ &= ~STA_NODISK;
	else stat_ |= (STA_NODISK | STA_NOINIT);
}


//---------------------------------------------------------------------//
/*!
    @brief  disk card status @n
			カードがソケットに接続された場合を検出する
	@return カードが無い場合「０」
*/
//---------------------------------------------------------------------//
int disk_card_detection(void)
{
	return card_dt_();
}

