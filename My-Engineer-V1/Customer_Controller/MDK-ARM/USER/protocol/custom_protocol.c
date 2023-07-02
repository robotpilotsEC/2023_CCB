/**
  ******************************************************************************
  * @file           : custom_potocol.c
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */

#include "custom_protocol.h"
#include "stdbool.h"
#include "string.h"
#include "usart.h"
#include "crc.h"
#include "imu.h"

custom_tx_info_t custom_tx_info = 
{
	.SOF = 0xA5,
	.mode = 1,
};


uint8_t custom_txBuf[30];

void custom_data_update(custom_tx_info_t *tx)
{
	tx->roll_speed = imu.info->rate_x;
	tx->pitch_speed = imu.info->rate_y;
	tx->yaw_speed = imu.info->rate_z;
	
	tx->x_speed = imu.info->speed_x_pass;
	tx->y_speed = imu.info->speed_y_pass;
	tx->z_speed = imu.info->speed_z_pass;
	
}

uint32_t custom_tx_cnt = 0;
uint8_t custom_data_tx(void)
{	
	custom_tx_cnt ++;
	memcpy(custom_txBuf, &custom_tx_info, sizeof(custom_tx_info_t));
	Append_CRC8_Check_Sum(custom_txBuf, 3);
	Append_CRC16_Check_Sum(custom_txBuf, sizeof(custom_tx_info_t));
	
	if(custom_tx_cnt>=1000/30)
	{
		if(HAL_UART_Transmit_DMA(&huart1,custom_txBuf,sizeof(custom_tx_info_t)) == HAL_OK)
			return DEV_OK;
		custom_tx_cnt = 0;
	}
	else
		custom_tx_cnt ++;
	
	return DEV_NO;
}

