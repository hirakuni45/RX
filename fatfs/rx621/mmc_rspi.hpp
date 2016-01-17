//========================================================================//
/*! @file
    @brief	AKI-RX62(RX621 シリーズマイコン): R5F56218BNFP　@n
			FatFS SPI driver
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//========================================================================//

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------//
/*!
    @brief  Device timer function @n
			This function must be called from system timer process @n
			in period of 10 ms to generate card control timing.
*/
//-----------------------------------------------------------------//
void disk_timerproc(void);


//---------------------------------------------------------------------//
/*!
    @brief  disk card status @n
			カードがソケットに接続された場合を検出する
	@return カードが無い場合「０」
*/
//---------------------------------------------------------------------//
int disk_card_detection(void);


#ifdef __cplusplus
}
#endif
