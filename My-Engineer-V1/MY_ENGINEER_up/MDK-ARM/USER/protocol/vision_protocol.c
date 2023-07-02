/**
  ******************************************************************************
  * @file           : vision_potocol.c
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */

#include "vision_protocol.h"
#include "stdbool.h"
#include "string.h"
#include "usart.h"
#include "crc.h"

vision_tx_info_t vision_tx_info = 
{
	.SOF = 0xA5,
	.mode = 1,
};

vision_rx_info_t vision_rx_info;

uint8_t vision_txBuf[30];

uint8_t vision_data_rx(uint8_t *rxBuf)
{
	/* 帧首字节是否为0xA5 */
	if(rxBuf[0] == 0xA5)
	{
		/* 帧头CRC8校验*/
		if(Verify_CRC8_Check_Sum(rxBuf, 3) == true)
		{
			/* 帧尾CRC16校验 */
			if(Verify_CRC16_Check_Sum(rxBuf, sizeof(vision_rx_info_t)) == true)
			{
				memcpy(&vision_rx_info, rxBuf, sizeof(vision_rx_info_t));
				return DEV_OK;
			}
		}
	}
	return DEV_NO;
}

uint32_t vision_tx_cnt = 0;
uint8_t vision_data_tx(void)
{	
	vision_tx_cnt ++;
	memcpy(vision_txBuf, &vision_tx_info, sizeof(vision_tx_info_t));
	Append_CRC8_Check_Sum(vision_txBuf, 3);
	Append_CRC16_Check_Sum(vision_txBuf, sizeof(vision_tx_info_t));
	
//	if(vision_tx_cnt%4==0)
//	{
		if(HAL_UART_Transmit_DMA(&huart1,vision_txBuf,sizeof(vision_tx_info_t)) == HAL_OK)
			return DEV_OK;
		vision_tx_cnt = 0;
//	}
	
	return DEV_NO;
}

